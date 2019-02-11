/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file st_crcSemiCPU.c
 *
 *  \brief Common across test-cases using CRC Semi-CPU mode.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dcc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_dcc.h>
#include <ti/drv/pm/pmhal.h>
#include <st_dcc.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_DCC_ERROR_INT_M4                 (44U)
#define APP_DCC_DONE_INT_M4                  (45U)

#ifdef __TI_ARM_V7M4__
    #define BUID_CORE                           (1U)
    #define APP_XBAR_CPU                        (CPU_IPU1)
#endif

#define APP_SYS_CLK1_FREQ_KHZ                   ((uint32_t)20000)
#define APP_SYS_CLK2_FREQ_KHz                   ((uint32_t)22579)
#define APP_XREF_FREQ_KHz                       ((uint32_t)50000)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t gIsrFlag = 0U, gLastIntr = 3U;
uint32_t gModule;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   module          DCC module.
 *
 * \param   intrType        Interrupt for which crossbar is to be configured.
 *                          Refer enum #dccIntrType_t.
 *
 * \retval  status          Configuration status.
 */
uint32_t DCCContAppXBarConfig(uint32_t module, uint32_t intrType);

/**
 * \brief   This Interrupt Service Routine for DCC error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCContAppErrorIntrISR(void *handle);

extern int32_t DCCClockEnable(uint32_t module);
extern uint32_t DCCAppGetTestClkfreqKHz(uint32_t testClk, pmhalPrcmNodeId_t *dpllId,
                                pmhalPrcmPllPostDivValue_t *dpllPostDivider);
extern uint32_t DCCAppGetSrc1SeedVal(uint32_t testClk, uint32_t testClkCnt,
                              uint32_t testClkFreq);
extern int32_t DCCAppTestClkFreqChange(pmhalPrcmNodeId_t *dpllId,
                                pmhalPrcmPllPostDivValue_t *dpllPostDivider,
                                uint32_t testClk);
extern void DCCAppUARTConfig(void);
extern void DCCAppMiscConfig(uint32_t clksrc);
extern int32_t DCCAppDPLLConfig(uint32_t testClk,
                         pmhalPrcmNodeId_t *dpllId,
                         pmhalPrcmPllPostDivValue_t *dpllPostDivider);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void st_cont_main(st_DCCTestcaseParams_t *testParams)
{
    int32_t configStatus = 0, getCharRetVal;
    char option;
    uint32_t status = 0, testClkFreq, testClkCnt, dpllId, refClkFreqKHz;
    uint32_t refClkCnt;
    pmhalPrcmPllPostDivValue_t dpllPostDivider;
    volatile uint32_t timeOutms = 2000U;
    dccConfigParams_t configParams;
    dccRevisionId_t revId;

    /* Set reesult to fail */
    testParams->testResult = STW_EFAIL;
    gIsrFlag = 0U;
    gLastIntr = 3U;

    /* initialize the interrupt controller */
    Intc_Init();

    /* Configure UART console */
    //DCCAppUARTConfig();
    DCCAppMiscConfig(testParams->dccConfigParams.dccClkSrc1);
    if(STW_SOK != DCCAppDPLLConfig(testParams->dccConfigParams.dccClkSrc1,
                                   &dpllId,
                                   &dpllPostDivider))
    {
        status++;
    }

    if(DCC_CLK_SRC0_SYS_CLK1 == testParams->dccConfigParams.dccClkSrc0)
    {
        refClkFreqKHz = APP_SYS_CLK1_FREQ_KHZ;
    }
    else if(DCC_CLK_SRC0_SYS_CLK2 == testParams->dccConfigParams.dccClkSrc0)
    {
        refClkFreqKHz = APP_SYS_CLK2_FREQ_KHz;
    }
    else
    {
        refClkFreqKHz = APP_XREF_FREQ_KHz;
    }
    /* Get the test clock frequency */
    testClkFreq = DCCAppGetTestClkfreqKHz(testParams->dccConfigParams.dccClkSrc1,
                                         &dpllId, &dpllPostDivider);
    if(0U == testClkFreq)
    {
        UARTprintf("Error in calculating Frequency.\n");
        //return;
    }
    refClkCnt = (testParams->dccConfigParams.dccSeedSrc0 +
                (testParams->dccConfigParams.dccSeedValid0 / 2));
    /* Get the test clock seed value */
    testClkCnt = DCCAppGetSrc1SeedVal(refClkFreqKHz,
                                      refClkCnt, testClkFreq);

    /* Initialize DCC configuration parameters */
    gModule = testParams->dccConfigParams.dccModule;
    configParams.mode = testParams->dccConfigParams.dccMode;
    configParams.clkSrc0 = testParams->dccConfigParams.dccClkSrc0;
    configParams.clkSrc1 = testParams->dccConfigParams.dccClkSrc1;
    configParams.seedSrc0 = testParams->dccConfigParams.dccSeedSrc0;
    configParams.seedValid0 = testParams->dccConfigParams.dccSeedValid0;
    configParams.alternateClkSrc1 = testParams->dccConfigParams.alternateClkSrc1;
    configParams.seedSrc1 = testClkCnt;

    /* Configure XBar and interrupt */
    if(STW_SOK == DCCContAppXBarConfig(gModule, DCC_INTERRUPTS_ERROR))
    {
        status++;
    }
    if(STW_SOK == DCCContAppXBarConfig(gModule, DCC_INTERRUPTS_DONE))
    {
        status++;
    }
    if(0U < status)
    {
        /* Enable DCC module */
        configStatus = DCCClockEnable(gModule);
        if(STW_SOK == configStatus)
        {
            UARTprintf("Module enabled.\n");
            /* Get revision ID */
            DCCGetRevisionId(gModule, &revId);
            UARTprintf("Scheme :0x%x\n", revId.scheme);
            UARTprintf("Functional release number :0x%x\n", revId.func);
            UARTprintf("Design Release Number :0x%x\n", revId.rtlReleaseNum);
            UARTprintf("Major Revision Number :0x%x\n", revId.major);
            UARTprintf("Minor revision number :0x%x\n", revId.minor);
            UARTprintf("Special version of the module  :0x%x\n", revId.custom);
            /* Configure DCC module */
            configStatus = DCCSetConfig(gModule, &configParams);
            if(STW_EFAIL == configStatus)
            {
                UARTprintf("ERROR in DCC configuration.\n");
            }
            else
            {
                DCCEnableIntr(gModule, DCC_INTERRUPTS_ERROR);
                /* Enable DCC operation/module */
                DCCEnable(gModule, TRUE);
                /* Wait here till interrupt is generated */
                UARTprintf("\n Wait for %d us.\n",(((configParams.seedValid0 + configParams.seedSrc0) * 1000U) / refClkFreqKHz));
                /*UARTprintf("Then change 'timeOutms' variable value to '0' to proceed...\n");
                UARTprintf("This will change the test clock frequency to inject the error.\n");*/
                UARTprintf("Press any character or test will end in %ms.\n", timeOutms);
                getCharRetVal = StwUtils_appGetCharTimeout(
                        (int8_t *) &option,
                        timeOutms);
                if (STW_EFAIL == getCharRetVal)
                {
                    /* Timeout - Enable Auto run Option */
                    UARTprintf("\r\nUART read timeout %dms!!", timeOutms);
                }
                UARTprintf("Changing Frequency of the test clock to inject error.\n");
                /* Change test clock frequency */
                if(FAIL == DCCAppTestClkFreqChange(&dpllId,
                                                   &dpllPostDivider,
                                                   testParams->dccConfigParams.dccClkSrc1))
                {
                    /* Error in configuration */
                    testParams->testResult = STW_EFAIL;
                    UARTprintf("Frequency changed wan not successful.\n");
                }
                else
                {
                    UARTprintf("Frequency changed successfully.\n");
                    while(0U == gIsrFlag);
                    if(2U == gLastIntr)
                    {
                        gIsrFlag = 0U;
                        gLastIntr = 0U;
                        testParams->testResult = STW_SOK;
                        UARTprintf("Application ran successfully.\n");
                    }
                    else
                    {
                        testParams->testResult = STW_EFAIL;
                        UARTprintf("Try to run application again.\n");
                    }
                }
            }
        }
        else
        {
            UARTprintf("ERROR in enabling DCC module.\n");
        }
    }
    testParams->isRun = STW_SOK;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
uint32_t DCCContAppXBarConfig(uint32_t module, uint32_t intrType)
{
    uint32_t xBarInstError;
    uint32_t dccErrorIntrCore;
    cpu_id_t xBarCPUId;
    xbar_irq_t xBarIntrSrcError = IRQ_XBAR_RSVD;
    int32_t status = STW_EFAIL;

    if(1U == BUID_CORE)
    {
        xBarInstError = XBAR_INST_IPU1_IRQ_44;
        dccErrorIntrCore = APP_DCC_ERROR_INT_M4;
        xBarCPUId = APP_XBAR_CPU;

        switch(module)
        {
            case SOC_DCC1_BASE:
                xBarIntrSrcError = DCC1_IRQ_ERROR;
            break;
            case SOC_DCC2_BASE:
                xBarIntrSrcError = DCC2_IRQ_ERROR;
            break;
            case SOC_DCC3_BASE:
                xBarIntrSrcError = DCC3_IRQ_ERROR;
            break;
            case SOC_DCC4_BASE:
                xBarIntrSrcError = DCC4_IRQ_ERROR;
            break;
            case SOC_DCC5_BASE:
                xBarIntrSrcError = DCC5_IRQ_ERROR;
            break;
            case SOC_DCC6_BASE:
                xBarIntrSrcError = DCC6_IRQ_ERROR;
            break;
            case SOC_DCC7_BASE:
                xBarIntrSrcError = DCC7_IRQ_ERROR;
            break;
            default:
                status = STW_EBADARGS;
            break;
        }
    }
    else if(2U == BUID_CORE)
    {
    }
    else
    {
    }
    switch(intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            if (irq_xbar_success ==
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                           xBarCPUId, xBarInstError,
                           xBarIntrSrcError))
            {
                /* Successfully configured CrossBar */
                status = STW_SOK;
            }
            else
            {
                UARTprintf("Error in configuring CrossBar.\n");
            }
            if(STW_SOK == status)
            {
                /* Enable Error interrupt for DCC */
                Intc_IntEnable(dccErrorIntrCore);

                /* Register ISR */
                Intc_IntRegister(dccErrorIntrCore,
                                (IntrFuncPtr) DCCContAppErrorIntrISR, 0);
                Intc_IntPrioritySet(dccErrorIntrCore, 1, 0);
                Intc_SystemEnable(dccErrorIntrCore);
            }
        break;
        default:
            status = STW_EBADARGS;
        break;
    }
    return status;
}

void DCCContAppErrorIntrISR(void *handle)
{
    uint32_t status;
    dccConfigParams_t configParams;
    uint32_t srcCnt1, srcCnt0, srcValid0;

    status = DCCGetIntrStatus(gModule);
    UARTprintf("In ISR...\n");
    UARTprintf("Interrupt Status: 0x%x.\n", status);
    UARTprintf("ERROR interrupt generated.\n");
    DCCGetConfig(gModule, &configParams);
    srcCnt0 = HW_RD_REG32(gModule + DCC_DCCCNT0);
    srcValid0 = HW_RD_REG32(gModule + DCC_DCCVALID0);
    srcCnt1 = HW_RD_REG32(gModule + DCC_DCCCNT1);
    if(configParams.seedSrc0 == srcCnt0)
    {
        UARTprintf("Reference clock is not present.\n");
    }
    if(configParams.seedSrc1 == srcCnt1)
    {
        UARTprintf("Test clock is not present.\n");
    }
    else
    {
        UARTprintf("Test clock is drifted.\n");
        UARTprintf("Count0=>%d/%d\nValid0=>%d/%d\nCount1=>%d/%d\n",
                srcCnt0, configParams.seedSrc0, srcValid0,
                configParams.seedValid0, srcCnt1, configParams.seedSrc1);
    }
    DCCClearIntrStatus(gModule, DCC_INTERRUPTS_ERROR);
    gIsrFlag = 1U;
    gLastIntr = 2U;
}

