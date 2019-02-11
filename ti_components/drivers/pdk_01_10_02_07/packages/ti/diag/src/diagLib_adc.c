/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_adc.c
 * \brief    This file contains ADC software test APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/hw_types.h>
#include <ti/diag/diagLib_adc.h>
#include <diagLib_utils.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Default FIFO threshold value */
#define DIAGLIB_ADC_FIFO_THRLD_DEFAULT   (0x00000000U)
/**
 * \brief  Macro defines all the interrupts used by DiagLib
 */
#define DIAGLIB_ADC_IRQBITS     (ADC_INTR_SRC_END_OF_SEQUENCE | \
                                ADC_INTR_SRC_FIFO0_THRESHOLD | \
                                ADC_INTR_SRC_FIFO0_OVERRUN | \
                                ADC_INTR_SRC_FIFO0_UNDERFLOW | \
                                ADC_INTR_SRC_FIFO1_THRESHOLD | \
                                ADC_INTR_SRC_FIFO1_OVERRUN | \
                                ADC_INTR_SRC_FIFO1_UNDERFLOW | \
                                ADC_INTR_SRC_OUT_OF_RANGE)


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static int32_t DiagLib_adcCheckParams(const DiagLib_AdcTestParams_t *testParams);
static int32_t DiagLib_adcSetParams(const DiagLib_AdcTestParams_t *testParams);
static void DiagLib_adcStart(uint32_t baseAddr);
static void DiagLib_adcStop(uint32_t baseAddr);
static void DiagLib_adcSetDefReg(uint32_t baseAddr);
static void DiagLib_adcReadFifo(const DiagLib_AdcTestParams_t *testParams,
            DiagLib_AdcTestResultParams_t* outParams, DiagLib_AdcObj_t *adcObj);
static int32_t DiagLib_adcPoll(const DiagLib_AdcTestParams_t *testParams,
            DiagLib_AdcTestResultParams_t* outParams, DiagLib_AdcObj_t *adcObj);
static void DiagLib_adcSetState(const DiagLib_AdcTestParams_t *testParams,
                                 const DiagLib_AdcTestResultParams_t* outParams,
                                 DiagLib_AdcObj_t *adcObj);
static void DiagLib_adcEnableSteps(const DiagLib_AdcTestParams_t *testParams,
                                                        uint32_t stepEnable);
static void DiagLib_adcWait(void);

/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibAdcStartupParams_init(DiagLib_AdcStartupParams_t *startupParams)
{
    if (NULL != startupParams)
    {
        startupParams->baseAddr     = DIAGLIB_ADC_MODULE_0;
        startupParams->clkDiv       = DIAGLIB_ADC_DIV_DEFAULT;
    }
}

void DiagLibAdcTestParams_init(DiagLib_AdcTestParams_t *testParams)
{
    uint32_t loopCnt;

    if (NULL != testParams)
    {
        testParams->baseAddr     = DIAGLIB_ADC_MODULE_0;
        testParams->testType     = DIAGLIB_ADC_TEST_CONV;
        testParams->refVltg      = DIAGLIB_ADC_REF_VOLTAGE_DEFAULT;
        testParams->mode         = ADC_OPERATION_MODE_SINGLE_SHOT;
        testParams->numLoop      = DIAGLIB_ADC_NUMLOOP_DEFAULT;
        testParams->transferMode = DIAGLIB_ADC_INTERRUPT_MODE;
        testParams->numCh        = 0U;
        testParams->vltgDev      = 0U;
        testParams->verifyEnable = 1U;
        testParams->lowRange     = ADC_RANGE_MIN;
        testParams->highRange    = ADC_RANGE_MAX;
        testParams->fifoNum      = ADC_FIFO_NUM_0;
        testParams->timeout      = DIAGLIB_UTILS_DEFAULT_TIMEOUT;

        for (loopCnt = 0; loopCnt < DIAGLIB_ADC_MAX_NUM_CH; loopCnt++)
        {
            testParams->chCfg[loopCnt].openDelay        = 1U;
            testParams->chCfg[loopCnt].sampleDelay      = 0U;
            testParams->chCfg[loopCnt].rangeCheckEnable = 1U;
            testParams->chCfg[loopCnt].averaging        = ADC_AVERAGING_16_SAMPLES;
        }
    }
}

int32_t DiagLib_adcStartup(const DiagLib_AdcStartupParams_t *startupParams)
{

    int32_t status = STW_EFAIL;

    /* Clear All interrupt status */
    ADCClearIntrStatus(startupParams->baseAddr, ADC_INTR_STATUS_ALL);
    /* Power up AFE */
    ADCPowerUp(startupParams->baseAddr, (uint32_t) TRUE);
    /* Wait for 4us at least */
    DiagLib_adcWait();
    /* Do the internal calibration */
    ADCInit(startupParams->baseAddr, (uint32_t) FALSE, 0U, 0U);
    /* Configure ADC divider*/
    status = ADCSetClkDivider(startupParams->baseAddr, startupParams->clkDiv);

    return status;
}

int32_t DiagLib_adcStartTest(const DiagLib_AdcTestParams_t *testParams,
                              DiagLib_AdcTestResultParams_t* outParams,
                              DiagLib_AdcObj_t *adcObj)
{
    int32_t status = STW_EFAIL;
    uint32_t state;

    state = AdcIsPoweredUp(testParams->baseAddr);

    if (state == TRUE)
    {
        status = DiagLib_adcCheckParams(testParams);
    }

    if (status == STW_SOK)
    {
        /* Initialize ADC configuration params */
        status = DiagLib_adcSetParams(testParams);
    }

    if (status == STW_SOK)
    {
        outParams->verifyFailCnt = 0U;
        if(testParams->transferMode == DIAGLIB_ADC_INTERRUPT_MODE)
        {
            adcObj->testState = DIAGLIB_ADC_TEST_PENDING;
            ADCEnableIntr(testParams->baseAddr, DIAGLIB_ADC_IRQBITS);
            DiagLib_adcStart(testParams->baseAddr);
            status = adcObj->testState;
        }
        else if(testParams->transferMode == DIAGLIB_ADC_POLLED_MODE)
        {
            DiagLib_adcStart(testParams->baseAddr);
            while(adcObj->curLoop < testParams->numLoop)
            {
                status = DiagLib_adcPoll(testParams, outParams, adcObj);
                if (status != STW_SOK)
                {
                    break;
                }
            }
            if (status == STW_SOK)
            {
                DiagLib_adcSetState(testParams, outParams, adcObj);
                status = adcObj->testState;
            }
            DiagLib_adcStop(testParams->baseAddr);
            adcObj->curLoop = (uint32_t)0U;
        }
        else
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    return status;
}

/**
 * \brief   This is Interrupt Service Routine for ADC interrupt.
 *
 * \param   testParams  Input Params.
 *          outParams   OutParams to be filled.
 *          adcObj      Object Parameter to carry internal data.
 *
 * \retval  testStatus    status.
 */
int32_t DiagLib_adcProcISR(const DiagLib_AdcTestParams_t *testParams,
                            DiagLib_AdcTestResultParams_t* outParams,
                            DiagLib_AdcObj_t *adcObj)
{
    uint32_t intrStatus;
    int32_t status = DIAGLIB_ADC_TEST_PENDING;
    intrStatus = ADCGetIntrStatus(testParams->baseAddr);
    ADCClearIntrStatus(testParams->baseAddr, intrStatus);

    if (ADC_INTR_SRC_OUT_OF_RANGE == (intrStatus & ADC_INTR_SRC_OUT_OF_RANGE))
    {
        DiagLib_adcStop(testParams->baseAddr);
        status = DIAGLIB_ADC_TEST_FAIL;
    }
    else if ((ADC_INTR_SRC_FIFO0_OVERRUN ==
                                (intrStatus & ADC_INTR_SRC_FIFO0_OVERRUN)) ||
            (ADC_INTR_SRC_FIFO1_OVERRUN ==
                                (intrStatus & ADC_INTR_SRC_FIFO1_OVERRUN)) ||
            (ADC_INTR_SRC_FIFO0_UNDERFLOW ==
                                (intrStatus & ADC_INTR_SRC_FIFO0_UNDERFLOW)) ||
            (ADC_INTR_SRC_FIFO1_UNDERFLOW ==
                                (intrStatus & ADC_INTR_SRC_FIFO1_UNDERFLOW)))
    {
        DiagLib_adcStop(testParams->baseAddr);
        if(testParams->testType == DIAGLIB_ADC_TEST_CONV)
        {
            DiagLib_adcEnableSteps(testParams, (uint32_t) TRUE);
            ADCEnableIntr(testParams->baseAddr, DIAGLIB_ADC_IRQBITS);
            DiagLib_adcStart(testParams->baseAddr);
        }
        else
        {
            adcObj->testState = DIAGLIB_ADC_TEST_PASS;
        }
    }
    else if ((ADC_INTR_SRC_FIFO0_THRESHOLD ==
                                (intrStatus & ADC_INTR_SRC_FIFO0_THRESHOLD)) ||
            (ADC_INTR_SRC_FIFO1_THRESHOLD ==
                            (intrStatus & ADC_INTR_SRC_FIFO1_THRESHOLD)) ||
            (ADC_INTR_SRC_END_OF_SEQUENCE ==
                            (intrStatus & ADC_INTR_SRC_END_OF_SEQUENCE)))
    {
        if(testParams->testType == DIAGLIB_ADC_TEST_CONV)
        {
            DiagLib_adcReadFifo(testParams, outParams, adcObj);
            adcObj->curLoop++;
        }
    }
    else
    {
        /* Workaround for spurious interrupt that occurs when we stop ADC and
         * interrupt happened between interrupt disable and executing ADC stop
         * instruction. After we stop ADC, we clear all interrupt status.
         * So no status bits set means, this condition!!
         * Even though interrupts are cleared, we still get the interrupt
         * which was raised to the host processor. Set the appropriate return
         * status here.
         */
        if (adcObj->curLoop == 0U)
        {
            status = adcObj->testState;
        }
    }

    if(testParams->testType == DIAGLIB_ADC_TEST_CONV)
    {
        if (adcObj->curLoop == testParams->numLoop)
        {
            DiagLib_adcStop(testParams->baseAddr);
            DiagLib_adcSetState(testParams, outParams, adcObj);
            status = adcObj->testState;
            adcObj->curLoop = (uint32_t)0U;
        }
    }
    else
    {
        status = adcObj->testState;
        adcObj->curLoop = (uint32_t)0U;
    }

    ADCWriteEOI(testParams->baseAddr);
    return status;
}

void DiagLib_adcShutdown(const DiagLib_AdcTestParams_t *testParams)
{
    /* Power down AFE */
    ADCPowerUp(testParams->baseAddr, (uint32_t) FALSE);
}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t DiagLib_adcCheckParams(const DiagLib_AdcTestParams_t *testParams)
{

    int32_t status = STW_SOK;
    uint32_t loopCnt;

    if(testParams->testType >= DIAGLIB_ADC_TEST_MAX)
    {
        status = STW_EINVALID_PARAMS;
    }
    if (testParams->testType == DIAGLIB_ADC_TEST_OVERRUN)
    {
        if (testParams->transferMode == DIAGLIB_ADC_POLLED_MODE)
        {
            status = STW_EINVALID_PARAMS;
        }
        if (testParams->mode == ADC_OPERATION_MODE_SINGLE_SHOT)
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    if (testParams->mode == ADC_OPERATION_MODE_SINGLE_SHOT)
    {
        if(testParams->numLoop > DIAGLIB_ADC_NUMLOOP_DEFAULT)
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    if ((testParams->numCh == 0U) || (testParams->numCh >
                                            DIAGLIB_ADC_MAX_NUM_CH))
    {
        status = STW_EINVALID_PARAMS;
    }
    if (testParams->numLoop == 0U)
    {
        status = STW_EINVALID_PARAMS;
    }
    if (status == STW_SOK)
    {
        for (loopCnt = 0; loopCnt < testParams->numCh; loopCnt++)
        {
            if ((testParams->chCfg[loopCnt].openDelay >
                                                ADC_OPENDELAY_MAX) ||
               (testParams->chCfg[loopCnt].sampleDelay >
                                                ADC_SAMPLEDELAY_MAX) ||
               (testParams->chCfg[loopCnt].averaging >
                                                ADC_AVERAGING_16_SAMPLES))
            {
                status = STW_EINVALID_PARAMS;
            }
        }
    }
    return status;
}
/**
 * \brief   This functions sets the input parameters recieved from the user.
 *
 * \param   testParams    Structure user provided input.
 *
 * \retval  status.
 */
static int32_t DiagLib_adcSetParams(const DiagLib_AdcTestParams_t *testParams)
{

    int32_t status = STW_EFAIL;
    uint32_t loopCnt, setRange = (uint32_t)FALSE;
    adcStepConfig_t configParams;

    DiagLib_adcSetDefReg(testParams->baseAddr);

    configParams.mode = testParams->mode;
    configParams.fifoNum = testParams->fifoNum;


    for (loopCnt = 0; loopCnt < testParams->numCh; loopCnt++)
    {
        configParams.channel = testParams->chCfg[loopCnt].channel;
        configParams.rangeCheckEnable =
                        testParams->chCfg[loopCnt].rangeCheckEnable;
        configParams.averaging = testParams->chCfg[loopCnt].averaging;
        configParams.openDelay = testParams->chCfg[loopCnt].openDelay;
        configParams.sampleDelay = testParams->chCfg[loopCnt].sampleDelay;

        status = ADCSetStepParams(testParams->baseAddr,
                    testParams->chCfg[loopCnt].channel , &configParams);
        if (STW_SOK == status)
        {
            ADCStepEnable(testParams->baseAddr,
                    testParams->chCfg[loopCnt].channel, (uint32_t) TRUE);
        }
        if (configParams.rangeCheckEnable == TRUE)
        {
            setRange = (uint32_t)TRUE;
        }
    }

    if (STW_SOK == status)
    {
        if (testParams->transferMode == DIAGLIB_ADC_INTERRUPT_MODE)
        {
            status = ADCSetCPUFIFOThresholdLevel(testParams->baseAddr,
                    configParams.fifoNum, testParams->numCh);
        }
    }
    if (STW_SOK == status)
    {
        ADCStepIdTagEnable(testParams->baseAddr, (uint32_t) TRUE);
    }

    if (STW_SOK == status)
    {
        if (TRUE == setRange)
        {
            status = ADCSetRange(testParams->baseAddr, testParams->highRange,
                    testParams->lowRange);
        }
    }
    return status;
}

/**
 * \brief   This functions enables the steps from user parameters.
 *
 * \param   testParams      Structure user provided input.
 *          stepEnable      Set TRUE to enable steps.
 *
 * \retval  None.
 */
static void DiagLib_adcEnableSteps(const DiagLib_AdcTestParams_t *testParams,
                                                        uint32_t stepEnable)
{
    uint32_t loopCnt;

    for (loopCnt = 0; loopCnt < testParams->numCh; loopCnt++)
    {
        ADCStepEnable(testParams->baseAddr,
                    testParams->chCfg[loopCnt].channel, stepEnable);
    }

}
/**
 * \brief   This function will start ADC conversion.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DiagLib_adcStart(uint32_t baseAddr)
{
    adcSequencerStatus_t status;

    /* Clear all previous interrupt status */
    ADCClearIntrStatus(baseAddr, DIAGLIB_ADC_IRQBITS);
    /* Enable interrupts */
    /* Check if FSM is idle */
    ADCGetSequencerStatus(baseAddr, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           (ADC_ADCSTAT_STEP_ID_IDLE != status.stepId))
    {
        ADCGetSequencerStatus(baseAddr, &status);
    }
    /* Start ADC conversion */
    ADCStart(baseAddr, (uint32_t) TRUE);
}

/**
 * \brief   This function will stop ADC conversion
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DiagLib_adcStop(uint32_t baseAddr)
{
    adcSequencerStatus_t status;

    /* Clear all steps */
    ADCClearAllSteps(baseAddr);
    /* Disable interrupts */
    ADCDisableIntr(baseAddr, DIAGLIB_ADC_IRQBITS);
    /* Clear all previous interrupt status */
    ADCClearIntrStatus(baseAddr, DIAGLIB_ADC_IRQBITS);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(baseAddr, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           (ADC_ADCSTAT_STEP_ID_IDLE != status.stepId))
    {
        ADCGetSequencerStatus(baseAddr, &status);
    }
    /* Stop ADC */
    ADCStart(baseAddr, (uint32_t) FALSE);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(baseAddr, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           (ADC_ADCSTAT_STEP_ID_IDLE != status.stepId))
    {
        ADCGetSequencerStatus(baseAddr, &status);
    }
    return;

}

static void DiagLib_adcSetDefReg(uint32_t baseAddr)
{
    uint32_t index;
    adcStepConfig_t diagLib_adcConfig;

    /*
     * Init all registers to default value
     */
    /* Clear all steps */
    ADCClearAllSteps(baseAddr);

    diagLib_adcConfig.mode             = ADC_OPERATION_MODE_SINGLE_SHOT;
    diagLib_adcConfig.channel          = ADC_CHANNEL_1;
    diagLib_adcConfig.openDelay        = 0U;
    diagLib_adcConfig.sampleDelay      = 0U;
    diagLib_adcConfig.rangeCheckEnable = 0U;
    diagLib_adcConfig.averaging        = ADC_AVERAGING_NONE;
    diagLib_adcConfig.fifoNum          = ADC_FIFO_NUM_0;
    for (index = 0U; index < ADC_STEPCONFIG_NUM_ELEMS; index++)
    {
        ADCSetStepParams(baseAddr, index, &diagLib_adcConfig);
    }
    for (index = 0U; index < ADC_FIFOCOUNT_NUM_ELEMS; index++)
    {
        ADCSetCPUFIFOThresholdLevel(baseAddr,
                    index, DIAGLIB_ADC_FIFO_THRLD_DEFAULT);
    }
    /* Clear all previous interrupt status */
    ADCClearIntrStatus(baseAddr, DIAGLIB_ADC_IRQBITS);
    return;
}

static void DiagLib_adcReadFifo(const DiagLib_AdcTestParams_t *testParams,
            DiagLib_AdcTestResultParams_t* outParams, DiagLib_AdcObj_t *adcObj)
{
    uint32_t loopcnt, num, fifoData, voltageLvl, stepID;
    uint32_t fifoMax, fifoMin;

    for (loopcnt = 0U; loopcnt < testParams->numCh; loopcnt++)
    {
        fifoData = ADCGetFIFOData(testParams->baseAddr, testParams->fifoNum);
        stepID   = (fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                        ADC_FIFODATA_ADCCHNLID_SHIFT;
        fifoData = (fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                    ADC_FIFODATA_ADCDATA_SHIFT;
        voltageLvl  = fifoData * testParams->refVltg;
        voltageLvl /= (uint32_t) DIAGLIB_ADC_RESLN;

        for (num = 0; num < testParams->numCh; num++)
        {
            if(stepID == testParams->chCfg[num].channel)
            {
                fifoMax = testParams->chCfg[num].expVltg +
                                            testParams->vltgDev;
                fifoMin = testParams->chCfg[num].expVltg -
                                            testParams->vltgDev;
                outParams[num].channel = stepID;
                outParams[num].outVltg = voltageLvl;

                if ((voltageLvl < fifoMin) || (voltageLvl > fifoMax))
                {
                    outParams[num].verifyFailCnt++;
                }
                break;
            }
        }
    }
}

static int32_t DiagLib_adcPoll(const DiagLib_AdcTestParams_t *testParams,
            DiagLib_AdcTestResultParams_t* outParams, DiagLib_AdcObj_t *adcObj)
{
    int32_t status = STW_SOK;
    uint32_t timeStart, elapsedTime = 0U;
    uint32_t fifoWordCnt = 0U;

    timeStart = DiagLibUtils_getCurTimeInMsec();

    do
    {
        fifoWordCnt = ADCGetFIFOWordCount(testParams->baseAddr, testParams->fifoNum);
        elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);
    }
    while((fifoWordCnt < testParams->numCh) &&
                (elapsedTime <= testParams->timeout));

    if(elapsedTime <= testParams->timeout)
    {
        DiagLib_adcReadFifo(testParams, outParams, adcObj);
        adcObj->curLoop++;

        if(fifoWordCnt > ADC_FIFO_SIZE)
        {
            DiagLib_adcStop(testParams->baseAddr);
            DiagLib_adcEnableSteps(testParams, (uint32_t) TRUE);
            DiagLib_adcStart(testParams->baseAddr);
        }
    }
    else
    {
        adcObj->testState = DIAGLIB_ADC_TEST_TIMEOUT;
        status = STW_ETIMEOUT;
    }
    return status;
}

static void DiagLib_adcSetState(const DiagLib_AdcTestParams_t *testParams,
                                 const DiagLib_AdcTestResultParams_t* outParams,
                                 DiagLib_AdcObj_t *adcObj)
{
    uint32_t loopcnt;

    for (loopcnt = 0U; loopcnt < testParams->numCh; loopcnt++)
    {
        if(outParams[loopcnt].verifyFailCnt > 0U)
        {
            adcObj->testState = DIAGLIB_ADC_TEST_FAIL;
            break;
        }
    }
    if (((loopcnt == testParams->numCh) &&
            (adcObj->testState != DIAGLIB_ADC_TEST_FAIL)) ||
            (testParams->verifyEnable == 0U))
    {
        adcObj->testState = DIAGLIB_ADC_TEST_PASS;
    }

}

static void DiagLib_adcWait(void)
{
    uint32_t timetick;

    /* One tick of 32kHz is 31.25us */
    timetick  = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    timetick += 2U;
    while (timetick == (HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR)))
    {}
}
