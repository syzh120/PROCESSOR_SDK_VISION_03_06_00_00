/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file st_eccDiagLibTests.c
 *
 *  \brief Common across test-cases with DiagLib.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <st_ecc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define EDMA3_CC_REGION                 (1U)

#define APP_EMIF_INST_0             (SOC_EMIF1_CONF_REGS_BASE)
#define APP_EMIF_START_ADDR         (0x80000000)
#define APP_EMIF_ECC_START_ADDR     (0x90000000)
#define APP_EMIF_ECC_END_ADDR       (0x9001FFFF)
#define APP_EMIF_ECC_ERR_THRSH_VAL  (0x1)

#define EMIF_ECC_ERR_INT            (35U)
#define OCMC_RAM_ECC_ERR_INT        (25U)
#define IPU_L2RAM_SEC_ERR_INT       (84U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static DiagLib_EccTestParams_t *gEccTestParams;
static DiagLib_EccObj_t gEccObj;
static volatile int32_t gTestStatus;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief Function to enable ECC interrupt.
 *
 * \param   intrNum     Interrupt line number to be enabled.
 * \param   enable      Enable/disable interrupt.
 *
 * \retval  none.
 */
static void eccEnableIntr(uint32_t intrNum, uint32_t enable);
/**
 * \brief   This Interrupt Service Routine for ECC error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppEccIsr(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibEccTest_main(st_ECCTestcaseParams_t *testPrms)
{
    emifEccCfgPrm_t          cfgPrm;
    emifEccAddrRangeCfgPrm_t addrRangeCfgPrm;

    /* Unlock Pad Config Registers */
    PlatformUnlockMMR();

    /* initialize the interrupt controller */
    Intc_Init();

    gEccTestParams = &testPrms->diagLibTestParams;

    if((gEccTestParams->testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR) ||
    (gEccTestParams->testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE) ||
    (gEccTestParams->testType == DIAGLIB_ECC_TEST_EMIF_SEC) ||
    (gEccTestParams->testType == DIAGLIB_ECC_TEST_EMIF_DED))
    {
        if(gEccTestParams->eccErrCheckMode == DIAGLIB_ECC_INTERRUPT_MODE)
        {
            if((gEccTestParams->testType != DIAGLIB_ECC_TEST_EMIF_DED))
            {
                IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                                XBAR_INST_IPU1_IRQ_35, EMIF1_IRQ);
                eccEnableIntr(EMIF_ECC_ERR_INT, TRUE);
            }
            else
            {
                eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, TRUE);
            }
        }

        cfgPrm.addrRangeCfgPrm = &addrRangeCfgPrm;

        cfgPrm.emifStartAddr = APP_EMIF_START_ADDR;
        cfgPrm.addrRangeCfgPrm->startAddr       = APP_EMIF_ECC_START_ADDR;
        cfgPrm.addrRangeCfgPrm->endAddr         = APP_EMIF_ECC_END_ADDR;
        cfgPrm.addrRangeCfgPrm->addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_1;
        cfgPrm.addrRangeCfgPrm->addrRangeType   = EMIF_ECC_ADDR_RANGE_WITHIN;
        cfgPrm.addrRangeCfgPrm->enableAddrRange = TRUE;
        cfgPrm.thresholdVal = APP_EMIF_ECC_ERR_THRSH_VAL;

        EMIFConfigECCInitECCParams(APP_EMIF_INST_0, &cfgPrm);
    }
    else if((gEccTestParams->testType == DIAGLIB_ECC_TEST_OCMC_SEC) ||
            (gEccTestParams->testType == DIAGLIB_ECC_TEST_OCMC_DED) ||
            (gEccTestParams->testType == DIAGLIB_ECC_TEST_OCMC_ADDR))
    {
        EDMAsetRegion(EDMA3_CC_REGION);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

        if(gEccTestParams->eccErrCheckMode == DIAGLIB_ECC_INTERRUPT_MODE)
        {
            /*XBAR Configuration for OCMC*/
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                       XBAR_INST_IPU1_IRQ_25, OCMC_RAM1_IRQ);

            eccEnableIntr(OCMC_RAM_ECC_ERR_INT, TRUE);
        }
    }

    gTestStatus = DiagLib_eccStartTest(gEccTestParams, &gEccObj);
    while (gTestStatus == 1U)
    {}

    testPrms->testResult = gTestStatus;

    eccEnableIntr(OCMC_RAM_ECC_ERR_INT, FALSE);
    eccEnableIntr(EMIF_ECC_ERR_INT, FALSE);
    eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, FALSE);
}

uint32_t DiagLibEccTest_skipTest(st_ECCTestcaseParams_t *testPrms)
{
    uint32_t                 skipTest = FALSE;
    #if defined (SOC_TDA2EX)
    /* On TDA2Ex 17x17 board EMIF ECC is not supported. */
    if((PlatformGetSiliconPackageType() == PLATFORM_SILICON_PACKAGE_TYPE_17X17) &&
       ((testPrms->diagLibTestParams.testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR) ||
       (testPrms->diagLibTestParams.testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE) ||
       (testPrms->diagLibTestParams.testType == DIAGLIB_ECC_TEST_EMIF_SEC) ||
       (testPrms->diagLibTestParams.testType == DIAGLIB_ECC_TEST_EMIF_DED)))
    {
            skipTest = TRUE;
    }
    #endif
    return skipTest;
}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void eccEnableIntr(uint32_t intrNum, uint32_t enable)
{

    if(TRUE == enable)
    {
        /* Enable the given interrupt */
        Intc_IntEnable(0);

        Intc_IntRegister(intrNum, (IntrFuncPtr) AppEccIsr, NULL);

        Intc_IntPrioritySet(intrNum, 1, 0);
        Intc_SystemEnable(intrNum);
    }
    else
    {
        /* Disable the interrupt */
        Intc_SystemDisable(intrNum);

        /* Unregister the interrupt */
        Intc_IntUnregister(intrNum);

        Intc_IntDisable();
    }

}

static void AppEccIsr(void *handle)
{
    gTestStatus = DiagLib_eccISR(gEccTestParams, &gEccObj);
}
