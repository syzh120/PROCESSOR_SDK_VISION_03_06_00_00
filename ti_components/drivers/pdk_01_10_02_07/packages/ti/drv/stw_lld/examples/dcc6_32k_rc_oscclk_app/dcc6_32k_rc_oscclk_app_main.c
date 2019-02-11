/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     dcc_app.c
 *
 *  \brief    This file contains DCC test code for single shot mode.
 *            DPLLDSP_GMAC_H12 clock is used as clock to be tested against
 *            SYS_CLK1 which is reference clock.
 *
 *  \details  DCC operational mode is set to single shot mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdlib.h>
#include <string.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_dcc.h>

#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_DCC_MODULE_INST             (SOC_DCC6_BASE)
#define APP_DCC_MODE                    (DCC_OPERATION_MODE_CONTINUOUS)
#define APP_DCC_CLK_SRC0                (DCC_CLK_SRC0_SYS_CLK2)
#define APP_DCC_CLK_SRC1                (DCC_CLK_SRC1_ALTERNATE_CLK)
#define APP_DCC_CLK_SRC1_DRIFT          (5U)
#define APP_SYS_CLK1_FREQ_KHZ           ((uint32_t) 20000)
#define DCC_SRC0_COUNT_MAX              (0xFFFFFU)
#define DCC_SRC0_VALID_MAX              (0x0FFFFU)
#define DCC_SRC1_COUNT_MAX              (0xFFFFFU)

#define APP_DCC_ERROR_INT_M4                 (44U)
#define APP_DCC_DONE_INT_M4                  (45U)
#ifdef __TI_ARM_V7M4__
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INST_DONE                  (XBAR_INST_IPU1_IRQ_45)
    #define APP_XBAR_INTR_SOURCE_ERROR          (DCC6_IRQ_ERROR)
    #define APP_XBAR_INTR_SOURCE_DONE           (DCC6_IRQ_DONE)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag     = 0U, lastIntr = 2;
int32_t           gTestStatus = STW_SOK;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   intrType        Interrupt for which crossbar is to be configured.
 *                          Refer enum #dccIntrType_t.
 *
 * \retval  status          Configuration status.
 */
static int32_t DCCAppXBarConfig(uint32_t intrType);

/**
 * \brief   This Interrupt Service Routine for DCC error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppErrorIntrISR(void *handle);

/**
 * \brief   This Interrupt Service Routine for DCC DONE interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppDoneIntrISR(void *handle);

/**
 * \brief   This function returns seed value for COUNT1.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 * \param   drfitPer        Allowed drift in test clock in percentage.
 * \param   configParams    DCC configuration parameters.
 *                          Refer enum #dccConfigParams_t.
 *
 * \retval  None.
 */
static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams);

/**
 * \brief   This function returns least integral ratio for given clocks.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 *
 * \retval  None.
 */
static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum);

/**
 * \brief   This function is used for misc configuration needed by DCC App.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCAppMiscConfig(uint32_t clksrc);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t           configStatus, xBarStatus, getCharRetVal = 0U;
    uint32_t          testClkFreq, refClkRatioNum,
                      testClkRatioNum, refClkFreq;
    dccConfigParams_t configParams;
    volatile uint32_t timeOutms = 5000U;
    char option;
    uint32_t siliconRev;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    siliconRev = PlatformGetSiliconRev();
    /* DCC APP is supported on TDA3xx SR2.0 only */
    if(siliconRev >= 2U)
    {
        UARTPuts("\nDetected Silicon Revision is 2.0 or above.", -1);
         UARTPuts("\nTest Application will only run on TI EVM Rev. D\n", -1);
         UARTPuts("\nBoard Modification shall be done to bring-in the RC Oscillator clock before running this application\n", -1);
        UARTPuts("\nDCC Test Application\n", -1);

        /* initialize the interrupt controller */
        Intc_Init();

        configStatus = PlatformGetRCOscFreq(&refClkFreq);
        if(STW_EFAIL == configStatus)
        {
            UARTPuts("Error in Reading RC Oscillator Frequency.\n", -1);
            gTestStatus = STW_EFAIL;
        }
        /* Get the test clock frequency */
        testClkFreq = APP_SYS_CLK1_FREQ_KHZ;
        /* Convert frequency into KHz */
        refClkFreq /= 1000U;
        if (0U == testClkFreq)
        {
            UARTPuts("Error in calculating Frequency.\n", -1);
            gTestStatus = STW_EFAIL;
        }
        /* Get clock ratio */
        DCCAppGetClkRatio(refClkFreq,
                          testClkFreq,
                          &refClkRatioNum,
                          &testClkRatioNum);

        DCCAppMiscConfig(APP_DCC_CLK_SRC1);
        /* Initialize DCC configuration parameters */
        configParams.mode    = APP_DCC_MODE;
        configParams.clkSrc0 = APP_DCC_CLK_SRC0;
        configParams.clkSrc1 = APP_DCC_CLK_SRC1;
        configParams.alternateClkSrc1 = TRUE;
        /* Get the seed values for given clock selections and allowed drift */
        DCCAppSetSeedVals(refClkFreq,
                          testClkFreq,
                          refClkRatioNum,
                          testClkRatioNum,
                          APP_DCC_CLK_SRC1_DRIFT,
                          &configParams);

        /* Configure XBar and interrupt */
        xBarStatus  = DCCAppXBarConfig(DCC_INTERRUPTS_ERROR);
        xBarStatus |= DCCAppXBarConfig(DCC_INTERRUPTS_DONE);
        if (STW_SOK == xBarStatus)
        {
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC6,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                UARTPuts("Module enabled.\n", -1);
                /* Configure DCC module */
                configStatus = DCCSetConfig(APP_DCC_MODULE_INST, &configParams);
                if (STW_EFAIL == configStatus)
                {
                    UARTPuts("ERROR in DCC configuration.\n", -1);
                    gTestStatus = STW_EFAIL;
                }
                else
                {
                    lastIntr = 4U;
                    /* Enable DCC interrupts */
                    DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
                    DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
                    /* Enable DCC operation/module */
                    DCCEnable(APP_DCC_MODULE_INST, TRUE);
                    /* Wait here till interrupt is generated */
                    UARTprintf("Press any character or test will end in %dms.\n",
                                                                    timeOutms);
                    getCharRetVal = StwUtils_appGetCharTimeout(
                            (int8_t *) &option,
                            timeOutms);
                    if (STW_EFAIL == getCharRetVal)
                    {
                        /* Timeout - Enable Auto run Option */
                        UARTprintf("\nUART read timeout %dms!!", timeOutms);
                    }
                    if (4U != lastIntr)
                    {
                        UARTPuts("Try to run application again.\n", -1);
                        gTestStatus = STW_EFAIL;
                    }
                    else
                    {
                        UARTPuts("\nSince no error interrupt is generated,", -1);
                        UARTPuts("\nApplication successfully executed.\n", -1);
                    }
                }
            }
            else
            {
                UARTPuts("ERROR in enabling DCC module.\n", -1);
                gTestStatus = STW_EFAIL;
            }
        }

        if (gTestStatus == STW_SOK)
        {
            StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
            UARTPuts("\n DCC Test Pass", -1);
        }
        else
        {
            StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
            UARTPuts("\n DCC Test Fail", -1);
        }
    }
    else
    {
        UARTPuts("\n Detected Silicon Revision is not 2.0 or above.", -1);
        UARTPuts("\n This application can not be run this silicon revision.",
                 -1);
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t DCCAppXBarConfig(uint32_t intrType)
{
    int32_t status = STW_EFAIL;

    /* Configure Cross bar instance and interrupt */
    PlatformUnlockMMR();
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            if (irq_xbar_success ==
                IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                               APP_XBAR_CPU, APP_XBAR_INST_ERROR,
                               APP_XBAR_INTR_SOURCE_ERROR))
            {
                /* Successfully configured CrossBar */
                status = STW_SOK;
            }
            else
            {
                UARTPuts("Error in configuring CrossBar.\n", -1);
                gTestStatus = STW_EFAIL;
            }
            if (STW_SOK == status)
            {
                /* Enable Error interrupt for DCC */
                Intc_IntEnable(APP_DCC_ERROR_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_ERROR_INT_M4,
                                 (IntrFuncPtr) DCCAppErrorIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_ERROR_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_ERROR_INT_M4);
            }
            break;
        case DCC_INTERRUPTS_DONE:
            if (irq_xbar_success ==
                IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                               APP_XBAR_CPU, APP_XBAR_INST_DONE,
                               APP_XBAR_INTR_SOURCE_DONE))
            {
                /* Successfully configured CrossBar */
                status = STW_SOK;
            }
            else
            {
                UARTPuts("Error in configuring CrossBar.\n", -1);
                gTestStatus = STW_EFAIL;
            }
            if (STW_SOK == status)
            {
                /* Enable Done and Error interrupt for DCC */
                Intc_IntEnable(APP_DCC_DONE_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_DONE_INT_M4,
                                 (IntrFuncPtr) DCCAppDoneIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_DONE_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_DONE_INT_M4);
            }
            break;
        default:
            status = STW_EFAIL;
            break;
    }
    return status;
}

static void DCCAppErrorIntrISR(void *handle)
{
    UARTPuts("In ISR...\n", -1);
    UARTPuts("ERROR interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
    isrFlag  = 1U;
    lastIntr = 0U;
}

static void DCCAppDoneIntrISR(void *handle)
{
    UARTPuts("In ISR...\n", -1);
    UARTPuts("DONE interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
    isrFlag  = 1U;
    lastIntr = 1U;
}

static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams)
{
    uint32_t maxFreqKHz, maxCntLimit;
    uint32_t maxRefCnt, minRefCnt;
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
                  (uint32_t) (testClkRatioNum));
        configParams->seedSrc1   = (uint32_t) (mulVar / refClkRatioNum);
        configParams->seedValid0 = refClkRatioNum;
    }
    else
    {
        configParams->seedSrc1 = maxCntLimit / testClkRatioNum;
        configParams->seedSrc1 = configParams->seedSrc1 * testClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc1) *
                  (uint32_t) (refClkRatioNum));
        configParams->seedSrc0   = (uint32_t) (mulVar / testClkRatioNum);
        configParams->seedValid0 = 1U;
    }
    /* Applying allowed drift */
    if (((DCC_SRC0_COUNT_MAX + DCC_SRC0_VALID_MAX) <
         (configParams->seedSrc0 * (100U + drfitPer) / 100U)))
    {
        /* Seed values with drift exceeds maximum range */
        UARTPuts("Seed values with drift exceeds allowed range.\n", -1);
        UARTPuts("Application will run with 0% allowed drift.\n", -1);
    }
    else if (100U < drfitPer)
    {
        /* Error percentage is greater than 100 */
        UARTPuts("Wrong drift percentage. Not applying drift.\n", -1);
        UARTPuts("Application will run with 0% allowed drift.\n", -1);
    }
    else
    {
        maxRefCnt = (configParams->seedSrc0 * (100U + drfitPer) / 100U);
        minRefCnt = (configParams->seedSrc0 * (100U - drfitPer) / 100U);
        if (DCC_SRC0_VALID_MAX < (maxRefCnt - minRefCnt))
        {
            UARTPuts("Seed value for valid count exceeds allowed range.\n", -1);
            UARTPuts("Application will run with 0% allowed drift.\n", -1);
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
    UARTPuts("Seed values calculation done.\n", -1);
}

static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum)
{
    uint64_t loopCnt, hcf = 1U;

    for (loopCnt = 1;
         (loopCnt <= refClkFreq) || (loopCnt <= testClkFreq);
         loopCnt++)
    {
        if ((refClkFreq % loopCnt == 0) && (testClkFreq % loopCnt == 0))
        {
            hcf = loopCnt;
        }
    }
    *refClkRatioNum  = (refClkFreq / hcf);
    *testClkRatioNum = (testClkFreq / hcf);
}

void DCCAppMiscConfig(uint32_t clksrc)
{
    /* Enable RC Oscillator by enabling Dummy Module 2 */
    HW_WR_REG32 (SOC_COREAON_CM_CORE_BASE + CM_COREAON_DUMMY_MODULE2_CLKCTRL,
                 0x00000100);
    /* Configure IO PAD to bring-out the RC Oscillator Clock */
    PlatformUnlockMMR();
    PlatformClkOut2SetPinMux();
    PlatformLockMMR();
    /* Select RC Oscillator clock in CLKOUTMUX2 */
    HW_WR_REG32 (0x4AE06160U, 0x14U);
}
