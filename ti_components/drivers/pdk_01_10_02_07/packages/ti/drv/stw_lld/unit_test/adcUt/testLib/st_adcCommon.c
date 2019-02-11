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
 *  \file st_adcCommon.c
 *
 *  \brief Common code that can be shared across test case files.
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
#include <ti/csl/cslr_adc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_adc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_dcc.h>
#include <st_adc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for ADC module.
 *
 * \retval  status          configuration status.
 */
void ADCPlatformUARTInit(void);

/**
 * \brief   This API is used to introduce error.
 *
 * \param   testParams      test case parameters.
 *
 * \retval  status          Run status.
 */
int32_t ADCTestFunc(st_ADCTestcaseParams_t *testParams);

/**
 * \brief   This API is used to introduce some dealy.
 *
 * \param   None.
 *
 * \retval  None.
 */
void AppADCWait(void);

/**
 * \brief   This API will check calculated voltage against expected.
 *
 * \param   testParams      test case parameters.
 *
 * \param   stepID          Step ID for ADC module.
 *
 * \param   voltLvl         Measured voltage level for given Step.
 *
 * \retval  status          STW_SOK: If calculated voltage matches with
 **expected.
 *                          STW_EFAIL: Otherwise
 */
int32_t ADCCheckVoltage(st_ADCTestcaseParams_t *testParams,
                        uint32_t                stepID,
                        uint32_t                voltLvl);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void ADCPlatformUARTInit(void)
{
    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
}

int32_t ADCTestFunc(st_ADCTestcaseParams_t *testParams)
{
    uint32_t  adcModBaseAddr = 0x4A264000U, voltLvl;
    uint32_t  fifoWordCnt, fifoData, stepID, loopcnt;
    uint32_t *srcMemory = (uint32_t *) SOC_EMIF1_BASE;
    uint32_t  testId    = testParams->testcaseId;
    int32_t   status    = STW_EFAIL, failCount = 0U;

    switch (testId)
    {
        case 1:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 2:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 3:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 4:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 5:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 6:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 9:
            fifoWordCnt = 0U;
            loopcnt     = 0U;
            while (0xFFFFFFFFU != srcMemory[loopcnt++])
            {
                fifoWordCnt++;
            }
            UARTprintf("Number of samples stored @0x%x:%d.\n", SOC_EMIF1_BASE,
                       fifoWordCnt);
            for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
            {
                fifoData = srcMemory[loopcnt];
                stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                            ADC_FIFODATA_ADCCHNLID_SHIFT);
                fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                            ADC_FIFODATA_ADCDATA_SHIFT);
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        case 10:
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
                voltLvl = ((fifoData * ADC_REFERENCE_VOLTAGE_MV) /
                           ADC_RANGE_MAX);
                status = ADCCheckVoltage(testParams, stepID, voltLvl);
                if (STW_SOK != status)
                {
                    failCount++;
                }
                UARTprintf("Step ID : %d.    Data : %dmV.\n", stepID + 1,
                           voltLvl);
            }
            break;
        default:
            failCount = 0U;
            break;
    }
    if (0 == failCount)
    {
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

void AppADCWait(void)
{
    uint32_t time;

    /* One tick of 32kHz is 31.25us */
    time  = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    time += 2;
    while (time > (HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR)))
    {}
}

int32_t ADCCheckVoltage(st_ADCTestcaseParams_t *testParams,
                        uint32_t                stepID,
                        uint32_t                voltLvl)
{
    uint32_t loopCnt;
    uint32_t channelId;
    uint32_t expectedVolmV;
    int32_t  status = STW_EFAIL;

    for (loopCnt = 1U; loopCnt <= testParams->adcConfigParams.adcSteps[0U][0U];
         loopCnt++)
    {
        if (stepID == testParams->adcConfigParams.adcSteps[loopCnt][0U])
        {
            break;
        }
    }
    if (loopCnt <= testParams->adcConfigParams.adcSteps[0U][0U])
    {
        channelId     = testParams->adcConfigParams.adcSteps[loopCnt][1U];
        expectedVolmV = ADCGetExpectedVol(channelId);
        if ((voltLvl <= (expectedVolmV + ADC_VOLTAGE_ERR_OFFSET_MV)) &&
            (voltLvl >= (expectedVolmV - ADC_VOLTAGE_ERR_OFFSET_MV)))
        {
            status = STW_SOK;
        }
        else
        {
            UARTprintf("Voltage Matching failed for Step ID/Channel ID:%d/%d\n",
                       (stepID + 1U), (channelId + 1U));
            UARTprintf("Expected Voltage: %d vs. Observed Voltage%d\n",
                       expectedVolmV,
                       voltLvl);
            status = STW_EFAIL;
        }
    }
    return status;
}

uint32_t ADCGetExpectedVol(uint32_t channelId)
{
    uint32_t voltLvl;

    switch (channelId)
    {
        case ADC_CHANNEL_1:
            voltLvl = ADC_CHANNEL_1_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_2:
            voltLvl = ADC_CHANNEL_2_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_3:
            voltLvl = ADC_CHANNEL_3_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_4:
            voltLvl = ADC_CHANNEL_4_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_5:
            voltLvl = ADC_CHANNEL_5_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_6:
            voltLvl = ADC_CHANNEL_6_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_7:
            voltLvl = ADC_CHANNEL_7_VOLTAGE_MV;
            break;
        case ADC_CHANNEL_8:
            voltLvl = ADC_CHANNEL_8_VOLTAGE_MV;
            break;
        default:
            voltLvl = 0U;
    }
    return voltLvl;
}

