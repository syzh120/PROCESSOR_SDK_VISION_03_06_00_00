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
 *  \file     st_esmNormalMode.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_esm.h>
#include <st_esm.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ESM_INT_HIGH_M4                                  (34U)
#define APP_ESM_INT_LOW_M4                                   (35U)
#define APP_ESM_INT_HIGH_DSP                                 (32U)
#define APP_ESM_INT_LOW_DSP                                  (33U)
#define XBAR_HIGH_INTR_SOURCE                                (ESM_IRQ_HIGH)
#define XBAR_LOW_INTR_SOURCE                                 (ESM_IRQ_LOW)
#ifdef __TI_ARM_V7M4__
    #define APP_ESM_HIGH_INT                (APP_ESM_INT_HIGH_M4)
    #define APP_ESM_LOW_INT                 (APP_ESM_INT_LOW_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_HIGH_INTR_INST             (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_LOW_INTR_INST              (XBAR_INST_IPU1_IRQ_35)
#elif defined (_TMS320C6X)
    #define APP_ESM_HIGH_INT                (APP_ESM_INT_HIGH_DSP)
    #define APP_ESM_LOW_INT                 (APP_ESM_INT_LOW_DSP)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_HIGH_INTR_INST             (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_LOW_INTR_INST              (XBAR_INST_DSP1_IRQ_33)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t       isrFlag = 0U;
uint32_t                esmBaseAddr, esmMode;
st_ESMTestcaseParams_t *gtestParams;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function configures IRQ Xbar for esm high and low intr.
 *
 * \retval  none.
 */
static void AppESMXBarConfig(void);

/**
 * \brief   This Interrupt Service Routine for ESM High interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppESMHighIntrISR(void *handle);

/**
 * \brief   This Interrupt Service Routine for ESM Low interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppESMLowIntrISR(void *handle);

extern void ESMPlatformUARTInit(void);

extern int32_t ESMClockEnable(void);

extern int32_t ESMTestFunc(st_ESMTestcaseParams_t *testParams);

extern void cntrl_core_pad_configuration1(uint32_t            baseAdd,
                                          const pad_config_t *pad_config);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_esmNormalMode_main(st_ESMTestcaseParams_t *testParams)
{
    /* Testcase params */
    int32_t      configStatus, teststatus = STW_EFAIL;
    uint32_t     loopCnt, intrSrc, esmOutPin, numOfIntr;
    pad_config_t esm_pad_config = {CTRL_CORE_PAD_IO_MDIO_D,
                                   CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_ESM_ERROR_5,
                                   CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_ENABLE,
                                   CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_PULL_UP,
                                   CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_ENABLE,
                                   CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_FAST,
                                   0xff};

    isrFlag = 0U;
    /* Configure testcase params */
    esmBaseAddr = testParams->esmConfigParams.esmModule;
    esmMode     = testParams->esmConfigParams.esmMode;
    numOfIntr   = testParams->esmConfigParams.numOfIntr;
    gtestParams = testParams;

    /* Set result to fail */
    testParams->testResult = STW_EFAIL;

    /* Configure UARTStdioInit */
    ESMPlatformUARTInit();

    /* initialize the interrupt controller */
    Intc_Init();

    /* XBar configuration */
    AppESMXBarConfig();
    /* PAD config */
    cntrl_core_pad_configuration1(SOC_CORE_PAD_IO_REGISTERS_BASE,
                                  &esm_pad_config);

    /* Enable ESM module */
    configStatus = ESMClockEnable();
    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in ESM module enable.\n");
    }
    else
    {
        ESMSetMode(esmBaseAddr, esmMode);
        /* Enable and configure all the test-case interrupts */
        for (loopCnt = 1U;
             loopCnt <= testParams->esmConfigParams.esmChannels[0U][0U];
             loopCnt++)
        {
            intrSrc   = testParams->esmConfigParams.esmChannels[loopCnt][0U];
            esmOutPin = testParams->esmConfigParams.esmChannels[loopCnt][1U];
            if (ESM_OUT_ERROR_LOW_INTR == (esmOutPin & ESM_OUT_ERROR_LOW_INTR))
            {
                ESMClearIntrStatus(esmBaseAddr, intrSrc);
                ESMEnableIntr(esmBaseAddr, intrSrc);
                ESMSetIntrPriorityLvl(esmBaseAddr, intrSrc,
                                      ESM_INTR_PRIORITY_LEVEL_LOW);
            }
            if (ESM_OUT_ERROR_HIGH_INTR == (esmOutPin & ESM_OUT_ERROR_HIGH_INTR))
            {
                ESMClearIntrStatus(esmBaseAddr, intrSrc);
                ESMEnableIntr(esmBaseAddr, intrSrc);
                ESMSetIntrPriorityLvl(esmBaseAddr, intrSrc,
                                      ESM_INTR_PRIORITY_LEVEL_HIGH);
            }
            if (ESM_OUT_ERROR_ERR_PIN == (esmOutPin & ESM_OUT_ERROR_ERR_PIN))
            {
                ESMClearIntrStatus(esmBaseAddr, intrSrc);
                ESMSetInfluenceOnErrPin(esmBaseAddr, intrSrc, TRUE);
                ESMSetErrPinLowTimePreload(esmBaseAddr,
                                           testParams->esmConfigParams.esmLTCPR);
            }
        }
        /* Generate/trigger error condition here */
        UARTprintf("Wait here till any error is generated.\n");
        teststatus = ESMTestFunc(testParams);
        if (STW_SOK == teststatus)
        {
            if ((5U == testParams->testcaseId) ||
                (4U == testParams->testcaseId))
            {
                isrFlag++;
            }
            while (numOfIntr > isrFlag)
            {
                /* Wait here till interrupt happens */
            }
            for (loopCnt = 1U;
                 loopCnt <= gtestParams->esmConfigParams.esmChannels[0U][0U];
                 loopCnt++)
            {
                intrSrc =
                    testParams->esmConfigParams.esmChannels[loopCnt][0U];
                esmOutPin =
                    testParams->esmConfigParams.esmChannels[loopCnt][1U];
                if (ESM_OUT_ERROR_LOW_INTR ==
                    (esmOutPin & ESM_OUT_ERROR_LOW_INTR))
                {
                    ESMDisableIntr(esmBaseAddr, intrSrc);
                }
                if (ESM_OUT_ERROR_HIGH_INTR ==
                    (esmOutPin & ESM_OUT_ERROR_HIGH_INTR))
                {
                    ESMDisableIntr(esmBaseAddr, intrSrc);
                }
                if (ESM_OUT_ERROR_ERR_PIN == (esmOutPin & ESM_OUT_ERROR_ERR_PIN))
                {
                    ESMSetInfluenceOnErrPin(esmBaseAddr, intrSrc, FALSE);
                }
            }
            /* Set result to pass */
            testParams->testResult = STW_SOK;
        }
        else
        {
            /* Set result to FAIL */
            testParams->testResult = STW_EFAIL;
        }
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppESMHighIntrISR(void *handle)
{
    uint32_t loopCnt, intrSrc, esmOutPin;

    isrFlag++;
    UARTprintf("In High level Intr isr.\n");
    UARTprintf("Highest pending interrupt from High level interrupts is %d.\n",
           ESMGetHighPriorityLvlIntrStatus(
               esmBaseAddr));
    for (loopCnt = 1U;
         loopCnt <= gtestParams->esmConfigParams.esmChannels[0U][0U]; loopCnt++)
    {
        intrSrc   = gtestParams->esmConfigParams.esmChannels[loopCnt][0U];
        esmOutPin = gtestParams->esmConfigParams.esmChannels[loopCnt][1U];
        if (ESM_OUT_ERROR_HIGH_INTR == (esmOutPin & ESM_OUT_ERROR_HIGH_INTR))
        {
            if (1U == ESMGetIntrStatus(esmBaseAddr, intrSrc))
            {
                UARTprintf("Interrupt no.%d has happened.\n", intrSrc);
                ESMClearIntrStatus(esmBaseAddr, intrSrc);
            }
        }
    }
}

static void AppESMLowIntrISR(void *handle)
{
    uint32_t loopCnt, intrSrc, esmOutPin;

    isrFlag++;
    UARTprintf("In Low level Intr isr.\n");
    UARTprintf("Highest pending interrupt from Low level interrupts is %d.\n",
           ESMGetLowPriorityLvlIntrStatus(
               esmBaseAddr));
    for (loopCnt = 1U;
         loopCnt <= gtestParams->esmConfigParams.esmChannels[0U][0U]; loopCnt++)
    {
        intrSrc   = gtestParams->esmConfigParams.esmChannels[loopCnt][0U];
        esmOutPin = gtestParams->esmConfigParams.esmChannels[loopCnt][1U];
        if (ESM_OUT_ERROR_LOW_INTR == (esmOutPin & ESM_OUT_ERROR_LOW_INTR))
        {
            if (1U == ESMGetIntrStatus(esmBaseAddr, intrSrc))
            {
                UARTprintf("Interrupt no.%d has happened.\n", intrSrc);
                ESMClearIntrStatus(esmBaseAddr, intrSrc);
            }
        }
    }
}

static void AppESMXBarConfig(void)
{
    /* XBar configuration esm_high_intr */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_HIGH_INTR_INST,
                       XBAR_HIGH_INTR_SOURCE))
    {
        /* Successfully configured CrossBar */
        /* Enable Error interrupt for ESM */
        Intc_IntEnable(APP_ESM_HIGH_INT);

        /* Register ISR */
        Intc_IntRegister(APP_ESM_HIGH_INT,
                         (IntrFuncPtr) AppESMHighIntrISR, 0);
        Intc_IntPrioritySet(APP_ESM_HIGH_INT, 1, 0);
        Intc_SystemEnable(APP_ESM_HIGH_INT);
        UARTprintf(
            "XBar configuration successfully done for high level interrupt.\n");
    }
    else
    {
        UARTprintf("Error in configuring CrossBar.\n");
    }

    /* XBar configuration for esm_low_intr*/
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_LOW_INTR_INST,
                       XBAR_LOW_INTR_SOURCE))
    {
        /* Successfully configured CrossBar */
        /* Enable Error interrupt for ESM */
        Intc_IntEnable(APP_ESM_LOW_INT);

        /* Register ISR */
        Intc_IntRegister(APP_ESM_LOW_INT,
                         (IntrFuncPtr) AppESMLowIntrISR, 0);
        Intc_IntPrioritySet(APP_ESM_LOW_INT, 1, 0);
        Intc_SystemEnable(APP_ESM_LOW_INT);
        UARTprintf(
            "XBar configuration successfully done for low level interrupt.\n");
    }
    else
    {
        UARTprintf("Error in configuring CrossBar.\n");
    }
}

