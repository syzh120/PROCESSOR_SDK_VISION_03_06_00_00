/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file utils_dcc.c
 *
 * \brief Utility functions for using DCC to monitor DPLL outputs
 *        To change any behaviour, all const variables in this file need to be
 *        changed in sync.
 *        This utility monitors DDR clocks using DCC in "Continuous" mode
 *        and assumes it is running at 532MHz.
 *        DCC cannot track DPLL outputs to modules which are in SLEEP mode or
 *        in-active - so tracking CPU frequency in continuous mode is not
 *        possible.
 *        DSP/EVE must not goto sleep if we want to track DSP/EVE clock.
 *        DCC error interrupts are monitored using ESM or direct interrupt
 *        connection to IPU based on whether USE_ESM is defined or not.
 *        USE_ESM is recommended to be defined to avoid multiple interrupt line
 *        usage on IPU.
 *        On TDA3x ES1.0, EVE cannot use TIMER5/6/7/8 when DCC is being used in
 *        SW by any other core. Ensure correct TIMER usage in EVE.cfg.
 *
 * \version 0.0 (Jan 2016) : [CSG] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_dcc.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/drv/pm/pmhal.h>
#include "utils_common/include/utils_dcc.h"
#include "utils_common/include/utils_esm.h"
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* Number of modules used in this file.
 * There are multiple arrays with size DCC_MAX_INST.
 * Any change in macro requires updates to all these arrays appropriately.
 */
#define DCC_MAX_INST            (1U)

#define DCC_SYSCLK1_FREQUENCY   (20000000U)
#define DCC_DDR_FREQUENCY       (532000000U)

/* Undefine USE_ESM only for debugging
 * When not defined, multiple interrupt lines will be required on IPU */
#define USE_ESM

static Void dcc_setupInterrupts(Void);
static Void dcc_setConfigAndEnable(Void);
static Void Utils_dccErrISR(UArg ctx);
static Void dcc_genConfig(UInt32             refClkFreq,
                          UInt32             testClkFreq,
                          UInt32             refClkRatioNum,
                          UInt32             testClkRatioNum,
                          UInt32             driftPercentage,
                          dccConfigParams_t *configParams);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Interrupt handles */
static BspOsal_IntrHandle gDccErrHwiHandle[DCC_MAX_INST] = {NULL};

/**
 * \brief Base Addresses for DCC modules, used for DCC HAL usage
 */
const UInt32 gDccModuleBaseAddr[DCC_MAX_INST] =
{
    SOC_DCC2_BASE
};

/**
 * \brief Module name for DCC module in PMHAL
 */
const pmhalPrcmModuleId_t gDccPmModule[DCC_MAX_INST] =
{
    PMHAL_PRCM_MOD_DCC2 /* DCC2 */
};

#ifdef USE_ESM
/**
 * \brief ESM line for DCC error
 */
const UInt32 gDccErrEsmEvtId[DCC_MAX_INST] =
{
    ESM_GROUP1_INTR_SRC_DCC2_IRQ_ERROR /* DCC2 */
};
#else
/**
 * \brief Interrupt lines for DCC error used on IPU1_C0/IPU1_C1
 *        Make sure interrupt lines are not used elsewhere.
 */
const UInt32 gDccErrIpuIntrId[DCC_MAX_INST] =
{
    66U /* DCC2 */
};
#endif

/**
 * \brief Crossbar instances for DCC Error Interrupts
 */
const UInt32 gDccErrXbarId[DCC_MAX_INST] =
{
    DCC2_IRQ_ERROR /* DCC2 */
};

/**
 * \brief Reference clocks for DCC modules
 *        Any change needs change in gDccRefClkVal[]
 */
const UInt32 gDccRefClkSrc[DCC_MAX_INST] =
{
    DCC_CLK_SRC0_SYS_CLK1 /* DCC2 */
};

/**
 * \brief Reference clocks for DCC modules
 *        Any change needs change in gDccRefTestHCF[]
 */
const UInt32 gDccRefClkVal[DCC_MAX_INST] =
{
    DCC_SYSCLK1_FREQUENCY /* DCC2 */
};

/**
 * \brief Clocks under test for DCC modules
 *        Defined in starterware_/include/tda3xx/soc_defines.h as
 *        enum #dccClkSrc1_t
 *        Any change needs change in gDccTestClkVal[]
 */
const UInt32 gDccTestClkSrc[DCC_MAX_INST] =
{
    /* DCC2
     * Monitor DDR CLK: DCC_CLK_SRC1_DCC2_DPLLDDR_M2 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_M2
};

/**
 * \brief Clocks under test for DCC modules
 *        Any change needs change in gDccRefTestHCF[]
 */
const UInt32 gDccTestClkVal[DCC_MAX_INST] =
{
    DCC_DDR_FREQUENCY /* DCC2 */
};

/**
 * \brief Highest common factor RefClk and TestClk
 *        Defining this as a static value to avoid run-time computation.
 */
const UInt32 gDccRefTestHCF[DCC_MAX_INST] =
{
    DCC_SYSCLK1_FREQUENCY/5U /* DCC2: HCF of 532M & 20M is 4M */
};

/**
 * \brief Drift percentage allowed for each DCC comparison
 */
const UInt32 gDccDriftPercentage[DCC_MAX_INST] =
{
    1U /* DCC2 */
};

/* ========================================================================== */
/*                         Function definitions                               */
/* ========================================================================== */

static Void dcc_genConfig(UInt32             refClkFreq,
                          UInt32             testClkFreq,
                          UInt32             refClkRatioNum,
                          UInt32             testClkRatioNum,
                          UInt32             driftPercentage,
                          dccConfigParams_t *configParams)
{
    UInt32 maxFreqKHz, maxCntLimit;
    UInt32 maxRefCnt, minRefCnt;
    uint64_t mulVar;

    /* Find maximum frequency between test and reference clock */
    if (refClkFreq > testClkFreq)
    {
        maxFreqKHz  = refClkFreq;
        maxCntLimit = DCC_SRC0_COUNT_MAX;
    }
    else
    {
        maxFreqKHz  = testClkFreq;
        maxCntLimit = DCC_SRC1_COUNT_MAX;
    }
    /* Calculate seed values for 0% drift */
    if (maxFreqKHz == refClkFreq)
    {
        configParams->seedSrc0 = maxCntLimit / refClkRatioNum;
        configParams->seedSrc0 = configParams->seedSrc0 * refClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc0) *
                  (uint64_t) (testClkRatioNum));
        configParams->seedSrc1   = (UInt32) (mulVar / refClkRatioNum);
        configParams->seedValid0 = refClkRatioNum;
    }
    else
    {
        configParams->seedSrc1 = maxCntLimit / testClkRatioNum;
        configParams->seedSrc1 = configParams->seedSrc1 * testClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc1) *
                  (uint64_t) (refClkRatioNum));
        configParams->seedSrc0   = (UInt32) (mulVar / testClkRatioNum);
        configParams->seedValid0 = 1U;
    }
    /* Applying allowed drift */
    if (((DCC_SRC0_COUNT_MAX + DCC_SRC0_VALID_MAX) <
         ((configParams->seedSrc0 * (100U + driftPercentage)) / 100U)))
    {
        /* Error percentage is greater than 100 */
        Vps_printf(" DCC-UTILS: Drift percentage too high - exiting!!\n");
        UTILS_assert(FALSE);
    }
    else if (100U < driftPercentage)
    {
        /* Error percentage is greater than 100 */
        Vps_printf(" DCC-UTILS: Drift percentage > 100% - exiting!!\n");
        UTILS_assert(FALSE);
    }
    else
    {
        maxRefCnt = ((configParams->seedSrc0 * (100U + driftPercentage)) / 100U);
        minRefCnt = ((configParams->seedSrc0 * (100U - driftPercentage)) / 100U);
        if (DCC_SRC0_VALID_MAX < (maxRefCnt - minRefCnt))
        {
            /* Error percentage is greater than 100 */
            Vps_printf(" DCC-UTILS: Drift percentage too high - exiting!!\n");
            UTILS_assert(FALSE);
        }
        else
        {
            if (maxRefCnt == minRefCnt)
            {
                configParams->seedValid0 = 1U;
            }
            else
            {
                configParams->seedSrc0   = minRefCnt;
                configParams->seedValid0 = (maxRefCnt - minRefCnt);
            }
        }
    }
}

static Void Utils_dccErrISR(UArg ctx)
{
    UInt32 i, delay = 10000000U;
    UInt32 dccModule;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * Passing pointer arguments to ISR and callback functions which
     * takes arguments as UInt32 for legacy reasons and vice-versa.
     */
    dccModule = (UInt32) ctx;
    for(i = 0U; i < DCC_MAX_INST; i++)
    {
        if(dccModule == gDccModuleBaseAddr[i])
        {
            Vps_printf(" DCC-UTILS: Error occurred on 0x%x!!\n", dccModule);
        }
        while (delay != 0U)
        {
            delay--;
        }
        DCCClearIntrStatus(dccModule, DCC_INTERRUPTS_ERROR);
        /* Enable DCC operation again */
        DCCEnable(dccModule, (UInt32)TRUE);
    }
}

static Void dcc_setupInterrupts(Void)
{
    UInt32 i;
    UInt32 dccModule;

    /* Enable interrupt in XBAR and register ISR */
    for(i = 0; i < DCC_MAX_INST; i++)
    {
        dccModule = gDccModuleBaseAddr[i];

        /* Error interrupt */
        if(NULL == gDccErrHwiHandle[i])
        {
            #ifdef USE_ESM
             /* MISRA.CAST.Func.Ptr
              * MISRAC_2004_Rule_11.1
              * MISRAC_WAIVER:
              * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
              */
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule_11.3
             * MISRAC_WAIVER:
             * Passing pointer arguments to ISR and callback functions which
             * takes arguments as UInt32 for legacy reasons and vice-versa.
             */
            gDccErrHwiHandle[i] =
                System_esmRegisterEvent(
                    gDccErrEsmEvtId[i],
                    (BspOsal_IntrFuncPtr) &Utils_dccErrISR,
                    (Void*)dccModule);
            #else
            IntXbar_connectIRQ(gDccErrIpuIntrId[i], gDccErrXbarId[i]);
            gDccErrHwiHandle[i] =
                BspOsal_registerIntr(gDccErrIpuIntrId[i],
                                     (BspOsal_IntrFuncPtr) &Utils_dccErrISR,
                                     (Void*)dccModule);
            #endif
        }
    }

}

static Void dcc_setConfigAndEnable(Void)
{
    Int32  status;
    UInt32 i, dccModule;
    UInt32 driftPercentage;
    UInt32 refClkFreq, testClkFreq;
    UInt32 refClkRatioNum, testClkRatioNum;
    dccConfigParams_t configParams;

    /* Enable interrupt in XBAR and register ISR */
    for(i = 0; i < DCC_MAX_INST; i++)
    {
        dccModule = gDccModuleBaseAddr[i];
        status = PMHALModuleModeSet((pmhalPrcmModuleId_t)gDccPmModule[i],
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        UTILS_assert(0 == status);

        /* Initialize DCC configuration parameters */
        configParams.mode    = DCC_OPERATION_MODE_CONTINUOUS;
        configParams.clkSrc0 = gDccRefClkSrc[i];
        configParams.clkSrc1 = gDccTestClkSrc[i];
        refClkFreq           = gDccRefClkVal[i];
        testClkFreq          = gDccTestClkVal[i];
        refClkRatioNum       = refClkFreq / gDccRefTestHCF[i];
        testClkRatioNum      = testClkFreq / gDccRefTestHCF[i];
        driftPercentage      = gDccDriftPercentage[i];

        /* Get the seed values for given clock selections and allowed drift */
        dcc_genConfig(refClkFreq,
                      testClkFreq,
                      refClkRatioNum,
                      testClkRatioNum,
                      driftPercentage,
                      &configParams);

        status = DCCSetConfig(dccModule, &configParams);
        UTILS_assert(0 == status);

        /* Enable DCC error interrupt */
        DCCEnableIntr(dccModule, DCC_INTERRUPTS_ERROR);
        /* Enable DCC operation */
        DCCEnable(dccModule, (UInt32)TRUE);
    }
}

void System_dccInit(void)
{
    dcc_setupInterrupts();
    dcc_setConfigAndEnable();
}

void System_dccDeInit(void)
{
    UInt32 i;
    UInt32 dccModule;

    for(i = 0; i < DCC_MAX_INST; i++)
    {
        dccModule = gDccModuleBaseAddr[i];

        /* Disable DCC operation and interrupt generation */
        DCCEnable(dccModule, (UInt32)FALSE);
        DCCClearIntrStatus(dccModule, DCC_INTERRUPTS_ERROR);
        DCCDisableIntr(dccModule, DCC_INTERRUPTS_ERROR);

        if(NULL != gDccErrHwiHandle[i])
        {
            /* De-register ISRs */
            #ifdef USE_ESM
            System_esmUnRegisterEvent(&gDccErrHwiHandle[i]);
            #else
            IntXbar_disconnectIRQ(gDccErrIpuIntrId[i]);
            BspOsal_unRegisterIntr(&gDccErrHwiHandle[i]);
            #endif
            gDccErrHwiHandle[i] = NULL;
        }
    }

}
