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
 *  \file     st_adcNormalMode.c
 *
 *  \brief    This file contains ADC test code.
 *
 *  \details  ADC operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_adc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_adc.h>
#include <st_adc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ADC_DIV             (8U)

#define APP_ADC_INT_M4                                  (34U)
#define APP_ADC_INT_DSP                                 (32U)
#define EDMA3_CC_REGION_M4                              (1U)
#define EDMA3_CC_REGION_DSP                             (1U)
#ifdef __TI_ARM_V7M4__
    #define APP_ADC_INT                     (APP_ADC_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (TSC_ADC_IRQ_GENINT)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
#elif defined (_TMS320C6X)
    #define APP_ADC_INT                     (APP_ADC_INT_DSP)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_INST                       (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (TSC_ADC_IRQ_GENINT)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_DSP)
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t          adcModBaseAddr;
volatile uint32_t isrFlag = 1U;
volatile uint32_t edmaTransferComplete;
uint32_t          edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber,
                  edmaInterruptNumber;
EDMA3CCPaRAMEntry edmaParam;
uint32_t          timeStampBeforeADC, timeStampAfterADC;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This Interrupt Service Routine for ADC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCIntrISR(void *handle);

extern int32_t ADCTestFunc(st_ADCTestcaseParams_t *testParams);

extern void AppADCWait(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_adcSingleShotMode_main(st_ADCTestcaseParams_t *testParams)
{
    /* Testcase params */
    int32_t         configStatus;
    uint32_t        loopCnt;
    adcStepConfig_t adcConfig;
    uint32_t        edmaRegion, destBuffer = SOC_EMIF1_BASE;
    uint32_t       *srcMemory = (uint32_t *) SOC_EMIF1_BASE;
    int32_t         status = STW_EFAIL;

    isrFlag = 1U;
    /* Initialize ADC configuration params */
    adcModBaseAddr = testParams->adcConfigParams.adcModule;

    UARTprintf("Starting Application.\n");
    /* Fill destination memory with data */
    for (loopCnt = 0; loopCnt < 300; loopCnt++)
    {
        srcMemory[loopCnt] = 0xFFFFFFFFU;
    }

    /* XBar configuration */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_INST,
                       XBAR_INTR_SOURCE))
    {
        /* Successfully configured CrossBar */
        /* Enable Error interrupt for ADC */
        Intc_IntEnable(APP_ADC_INT);
        Intc_Init();
        /* Register ISR */
        Intc_IntRegister(APP_ADC_INT,
                         (IntrFuncPtr) AppADCIntrISR, 0);
        Intc_IntPrioritySet(APP_ADC_INT, 1, 0);
        Intc_SystemEnable(APP_ADC_INT);
    }
    else
    {
        UARTprintf("Error in configuring CrossBar.\n");
    }

    /* Enable ADC module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                      PMHAL_PRCM_MODULE_MODE_ENABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != configStatus)
    {
        UARTprintf("Error in ADC module enable.\n");
    }
    /* Power down ADC */
    /* Power up ADC */
    ADCPowerUp(adcModBaseAddr, TRUE);
    /* Wait 4us */
    AppADCWait();
    /* Initialize ADC */
    ADCInit(adcModBaseAddr, FALSE, 0U, 0U);
    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in initialization of ADC.\n");
    }
    /* Configure Divider value */
    configStatus = ADCSetClkDivider(adcModBaseAddr, APP_ADC_DIV);
    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in ADC divider configuration.\n");
    }
    /* Configure ADC */

    /* ADC step configuration */
    configStatus = 0;
    for (loopCnt = 1; loopCnt <= testParams->adcConfigParams.adcSteps[0U][0U];
         loopCnt++)
    {
        adcConfig.channel =
            testParams->adcConfigParams.adcSteps[loopCnt][1U];
        adcConfig.openDelay =
            testParams->adcConfigParams.adcSteps[loopCnt][6U];
        adcConfig.sampleDelay =
            testParams->adcConfigParams.adcSteps[loopCnt][7U];
        adcConfig.rangeCheckEnable =
            testParams->adcConfigParams.adcSteps[loopCnt][5U];
        adcConfig.averaging =
            testParams->adcConfigParams.adcSteps[loopCnt][3U];
        adcConfig.fifoNum =
            testParams->adcConfigParams.adcSteps[loopCnt][2U];
        adcConfig.mode = testParams->adcConfigParams.adcSteps[loopCnt][4U];
        configStatus  += ADCSetStepParams(
            adcModBaseAddr, testParams->adcConfigParams.adcSteps[loopCnt][0U],
            &adcConfig);
    }
    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in ADC step configuration.\n");
    }
    if (TRUE == testParams->adcConfigParams.stepIdTagEnable)
    {
        ADCStepIdTagEnable(adcModBaseAddr, TRUE);
    }
    else
    {
        ADCStepIdTagEnable(adcModBaseAddr, FALSE);
    }
    configStatus = 0U;
    if ((1U == testParams->adcConfigParams.fifo[0U][0U]) &&
        (0U != testParams->adcConfigParams.fifo[0U][1U]))
    {
        configStatus += ADCSetCPUFIFOThresholdLevel(
            adcModBaseAddr, ADC_FIFO_NUM_0,
            testParams->adcConfigParams.fifo[0U][1U]);
    }
    if ((1U == testParams->adcConfigParams.fifo[0U][0U]) &&
        (0U != testParams->adcConfigParams.fifo[0U][2U]))
    {
        configStatus += ADCSetDMAFIFOThresholdLevel(
            adcModBaseAddr, ADC_FIFO_NUM_0,
            testParams->adcConfigParams.fifo[0U][2U]);
        /* Enable EDMA access */
        ADCFIFODMAAccessEnable(adcModBaseAddr, ADC_FIFO_NUM_0, TRUE);
        /* b count is set after DMA threshold interrupt */
        edmaParam.bCnt = testParams->adcConfigParams.fifo[0U][2U];
    }
    if ((1U == testParams->adcConfigParams.fifo[1U][0U]) &&
        (0U != testParams->adcConfigParams.fifo[1U][1U]))
    {
        configStatus += ADCSetCPUFIFOThresholdLevel(
            adcModBaseAddr, ADC_FIFO_NUM_1,
            testParams->adcConfigParams.fifo[1U][1U]);
    }
    if ((1U == testParams->adcConfigParams.fifo[1U][0U]) &&
        (0U != testParams->adcConfigParams.fifo[1U][2U]))
    {
        configStatus += ADCSetDMAFIFOThresholdLevel(
            adcModBaseAddr, ADC_FIFO_NUM_1,
            testParams->adcConfigParams.fifo[1U][2U]);
        /* Enable EDMA access */
        ADCFIFODMAAccessEnable(adcModBaseAddr, ADC_FIFO_NUM_1, TRUE);
        /* b count is set after DMA threshold interrupt */
        edmaParam.bCnt = testParams->adcConfigParams.fifo[1U][2U];
    }
    /* EDMA XBar configuration*/
    if (dma_xbar_success ==
        DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       EDMA, XBAR_INST_DMA_EDMA_DREQ_1,
                       TSC_ADC_DREQ_FIFO1))
    {
        /* Successfully configured EDMA CrossBar */
    }
    else
    {
        UARTprintf("Error in configuring EDMA CrossBar.\n");
    }
    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    /* Configure EDMA parameters */
    edmaChannelNumber  = 0x1U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 0x1U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (adcModBaseAddr + ADC_FIFODATA(1));
    edmaParam.destAddr = destBuffer;
    edmaParam.aCnt     = 4U;

    edmaParam.cCnt     = 1U;
    edmaParam.srcBIdx  = 0;
    edmaParam.destBIdx = 4U;
    edmaParam.srcCIdx  = 0U;
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
         EDMA3_OPT_ITCINTEN_MASK |
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* Configure EDMA */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber,
                        EDMA3_TRIG_MODE_EVENT);

    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in ADC CPU threshold configuration.\n");
    }
    /* step enable */
    for (loopCnt = 1U; loopCnt <= testParams->adcConfigParams.adcSteps[0U][0U];
         loopCnt++)
    {
        ADCStepEnable(adcModBaseAddr,
                      testParams->adcConfigParams.adcSteps[loopCnt][0U], TRUE);
    }
    timeStampBeforeADC = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    ADCSetRange(adcModBaseAddr,
                testParams->adcConfigParams.highRange,
                testParams->adcConfigParams.lowRange);
    /* Clear All interrupts */
    ADCClearIntrStatus(adcModBaseAddr, ADC_INTR_ALL);
    /* Enable interrupts */
    ADCEnableIntr(adcModBaseAddr, testParams->adcConfigParams.intrEnable);
    ADCStart(adcModBaseAddr, TRUE);
    while (1U == isrFlag)
    {}
    /*Get FIFO data */
    /* This function  gets FIFO data and does any other test-case specific
     *operation */
    status = ADCTestFunc(testParams);
    /* Disable All the steps */
    for (loopCnt = 0U; loopCnt < 16U; loopCnt++)
    {
        ADCStepEnable(adcModBaseAddr, loopCnt, FALSE);
    }
    ADCDisableIntr(adcModBaseAddr, testParams->adcConfigParams.intrEnable);
    ADCStart(adcModBaseAddr, FALSE);
    ADCPowerUp(adcModBaseAddr, FALSE);
    /* Disable ADC module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                      PMHAL_PRCM_MODULE_MODE_DISABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != configStatus)
    {
        UARTprintf("Error in ADC module disable.\n");
    }
    UARTprintf(
        "Time taken for conversion(in terms of clocks cycles of 32kHz clock) is %d.\n",
        (timeStampAfterADC - timeStampBeforeADC));
    testParams->testResult = status;
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppADCIntrISR(void *handle)
{
    uint32_t status;
    uint32_t fifoWordCnt, fifoData, stepID, loopcnt, highRange, lowRange;

    timeStampAfterADC = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    UARTprintf("In ISR...\n");
    status = ADCGetIntrRawStatus(adcModBaseAddr);
    UARTprintf("Interrupt RAW status:0x%x.\n", status);
    status = ADCGetIntrStatus(adcModBaseAddr);
    if (ADC_INTR_SRC_END_OF_SEQUENCE == (status & ADC_INTR_SRC_END_OF_SEQUENCE))
    {
        UARTprintf("End of sequence interrupt occurred.\n");
    }
    if (ADC_INTR_SRC_FIFO0_THRESHOLD == (status & ADC_INTR_SRC_FIFO0_THRESHOLD))
    {
        UARTprintf("FIFO 0 threshold interrupt occurred.\n");
        fifoWordCnt = ADCGetFIFOWordCount(adcModBaseAddr, ADC_FIFO_NUM_0);
        UARTprintf("Number of samples in FIFO:%d.\n", fifoWordCnt);
        if (0U != fifoWordCnt)
        {
            UARTprintf("FIFO Data:\n");
        }
        for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
        {
            fifoData = ADCGetFIFOData(adcModBaseAddr, ADC_FIFO_NUM_0);
            stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                        ADC_FIFODATA_ADCCHNLID_SHIFT);
            fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                        ADC_FIFODATA_ADCDATA_SHIFT);
            UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                   ((fifoData * 1800) / 1024));
        }
    }
    if (ADC_INTR_SRC_FIFO0_OVERRUN == (status & ADC_INTR_SRC_FIFO0_OVERRUN))
    {
        UARTprintf("FIFO 0 overrun interrupt occurred.\n");
    }
    if (ADC_INTR_SRC_FIFO0_UNDERFLOW == (status & ADC_INTR_SRC_FIFO0_UNDERFLOW))
    {
        UARTprintf("FIFO 0 underflow interrupt occurred.\n");
    }
    if (ADC_INTR_SRC_FIFO1_THRESHOLD == (status & ADC_INTR_SRC_FIFO1_THRESHOLD))
    {
        UARTprintf("FIFO 1 threshold interrupt occurred.\n");
        fifoWordCnt = ADCGetFIFOWordCount(adcModBaseAddr, ADC_FIFO_NUM_1);
        UARTprintf("Number of samples in FIFO:%d.\n", fifoWordCnt);
        if (0U != fifoWordCnt)
        {
            UARTprintf("FIFO Data:\n");
        }
        for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
        {
            fifoData = ADCGetFIFOData(adcModBaseAddr, ADC_FIFO_NUM_1);
            stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                        ADC_FIFODATA_ADCCHNLID_SHIFT);
            fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                        ADC_FIFODATA_ADCDATA_SHIFT);
            UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                   ((fifoData * 1800) / 1024));
        }
    }
    if (ADC_INTR_SRC_FIFO1_OVERRUN == (status & ADC_INTR_SRC_FIFO1_OVERRUN))
    {
        UARTprintf("FIFO 1 overrun interrupt occurred.\n");
    }
    if (ADC_INTR_SRC_FIFO1_UNDERFLOW == (status & ADC_INTR_SRC_FIFO1_UNDERFLOW))
    {
        UARTprintf("FIFO 1 underflow interrupt occurred.\n");
    }
    if (ADC_INTR_SRC_OUT_OF_RANGE == (status & ADC_INTR_SRC_OUT_OF_RANGE))
    {
        UARTprintf("Out of range interrupt occurred.\n");
        fifoWordCnt = ADCGetFIFOWordCount(adcModBaseAddr, ADC_FIFO_NUM_0);
        UARTprintf("Number of samples in FIFO:%d.\n", fifoWordCnt);
        if (0U != fifoWordCnt)
        {
            UARTprintf("FIFO Data:\n");
        }
        for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
        {
            fifoData = ADCGetFIFOData(adcModBaseAddr, ADC_FIFO_NUM_0);
            stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                        ADC_FIFODATA_ADCCHNLID_SHIFT);
            fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                        ADC_FIFODATA_ADCDATA_SHIFT);
            UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                   fifoData);
        }
        ADCGetRange(adcModBaseAddr, &highRange, &lowRange);
        UARTprintf("Programmed range:(%d,%d)\n", lowRange, highRange);
    }
    ADCClearIntrStatus(adcModBaseAddr, ADCGetIntrRawStatus(adcModBaseAddr));
    ADCWriteEOI(adcModBaseAddr);
    isrFlag = 0U;
}

