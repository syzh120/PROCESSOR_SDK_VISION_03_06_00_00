/*
 *   Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file     adc_app_semicpu.c
 *
 *  \brief    This file contains ADC test code.
 *
 *  \details  ADC operational mode is set to Single shot.
 *            Following steps are enabled.
 *            Step ID       Input from Channel
 *            2             1
 *            3             3
 *            4             4
 *            5             5
 *            6             6
 *            Program uses SYNTIMER32k for timing calculations.
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_adc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_adc.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ADC_MODULE          (SOC_TSC_ADC_BASE)
#define APP_ADC_DIV             (1U)
/* Reference voltage for ADC - should be given in mV*/
#define APP_ADC_REF_VOLTAGE     (1800U)
#define APP_ADC_RANGE_MAX       (1024U)

#define APP_ADC_INT_M4                                  (34U)
#define APP_ADC_INT_DSP                                 (32U)
#if defined (__TI_ARM_V7M4__)
    #define APP_ADC_INT                     (APP_ADC_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_INST                       (CSL_XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_TSC_ADC_IRQ_GENINT)
#elif defined (_TMS320C6X)
    #define APP_ADC_INT                     (APP_ADC_INT_DSP)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_DSP1)
    #define XBAR_INST                       (CSL_XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_TSC_ADC_IRQ_GENINT)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

volatile uint32_t isrFlag = 1U;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This is Interrupt Service Routine for ADC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCIntrISR(void *handle);

/**
 * \brief   This function waits for 62.50us.
 *
 * \param   none.
 *
 * \retval  none.
 *
 * \note    Wait for 4 us before starting a conversion,after powering on
 *          ADC module.
 */
static void AppADCWait(void);

/**
 * \brief   This function initializes ADC module.
 *
 * \param   none.
 *
 * \retval  status          Initialization status.
 */
static int32_t AppADCInit(void);

/**
 * \brief   This function will start ADC conversion.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCStart(void);

/**
 * \brief   This function will stop ADC conversion
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCStop(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
#endif
}

int32_t main(void)
{
    int32_t         configStatus;
    uint32_t        loopcnt, fifoData, fifoWordCnt, stepID, voltageLvl;
    adcStepConfig_t adcConfig;

    /* Do Pad Config for UART */
    padConfig_prcmEnable();
    /* Initialize the UART Instance */
   /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr,"\nStarting application...\n", -1);

    /* XBar configuration */
    CSL_xbarIrqConfigure(XBAR_CPU,XBAR_INST,XBAR_INTR_SOURCE);
    /* Enable Error interrupt for ADC */
    Intc_Init();
    Intc_IntEnable(APP_ADC_INT);
    /* Register ISR */
    Intc_IntRegister(APP_ADC_INT,(IntrFuncPtr) AppADCIntrISR, 0);
    Intc_IntPrioritySet(APP_ADC_INT, 1, 0);
    Intc_SystemEnable(APP_ADC_INT);

    /* Enable ADC module */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_ADC_CLKCTRL,
                  CM_L4PER2_ADC_CLKCTRL_MODULEMODE,
                  CM_L4PER2_ADC_CLKCTRL_MODULEMODE_ENABLE);
    while (CM_L4PER2_ADC_CLKCTRL_IDLEST_FUNC !=
           HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_ADC_CLKCTRL,
                         CM_L4PER2_ADC_CLKCTRL_IDLEST))
    {
        /* Wait till ADC module is enabled */
    }
#endif
    /* Initialize ADC module */
    configStatus = AppADCInit();
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC divider configuration.\n", -1);
    }
    /* Initialize ADC configuration params */
    adcConfig.mode             = ADC_OPERATION_MODE_SINGLE_SHOT;
    adcConfig.channel          = ADC_CHANNEL_1;
    adcConfig.openDelay        = 0x1U;
    adcConfig.sampleDelay      = 0U;
    adcConfig.rangeCheckEnable = 0U;
    adcConfig.averaging        = ADC_AVERAGING_NONE;
    adcConfig.fifoNum          = ADC_FIFO_NUM_0;
    
    /* Enable interrupts */
    ADCEnableIntr(APP_ADC_MODULE, (ADC_INTR_SRC_END_OF_SEQUENCE |
                                   ADC_INTR_SRC_FIFO0_THRESHOLD |
                                   ADC_INTR_SRC_FIFO0_OVERRUN |
                                   ADC_INTR_SRC_FIFO0_UNDERFLOW |
                                   ADC_INTR_SRC_FIFO1_THRESHOLD |
                                   ADC_INTR_SRC_FIFO1_OVERRUN |
                                   ADC_INTR_SRC_FIFO1_UNDERFLOW |
                                   ADC_INTR_SRC_OUT_OF_RANGE));
    /* Configure ADC */
    /* step 2 configuration */
    configStatus = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_2, &adcConfig);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC step configuration.\n", -1);
    }
    /* step 3 configuration */
    adcConfig.channel = ADC_CHANNEL_3;
    configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_3,
                                         &adcConfig);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC step configuration.\n", -1);
    }
    /* step 4 configuration */
    adcConfig.channel = ADC_CHANNEL_4;
    configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_4,
                                         &adcConfig);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC step configuration.\n", -1);
    }
    /* step 5 configuration */
    adcConfig.channel = ADC_CHANNEL_5;
    configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_5,
                                         &adcConfig);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC step configuration.\n", -1);
    }
    /* step 6 configuration */
    adcConfig.channel = ADC_CHANNEL_6;
    configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_6,
                                         &adcConfig);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC step configuration.\n", -1);
    }
    ADCStepIdTagEnable(APP_ADC_MODULE, TRUE);
    configStatus =
        ADCSetCPUFIFOThresholdLevel(APP_ADC_MODULE, ADC_FIFO_NUM_0,
                                    40U);
    if (STW_SOK != configStatus)
    {
        UARTConfigPuts(uartBaseAddr,"Error in ADC CPU threshold configuration.\n", -1);
    }
    /* step enable */
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_2, TRUE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_3, TRUE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_4, TRUE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_5, TRUE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_6, TRUE);
    AppADCStart();
    while (1U == isrFlag)
    {}
    /*Get FIFO data */
    fifoWordCnt = ADCGetFIFOWordCount(APP_ADC_MODULE, ADC_FIFO_NUM_0);
    UARTConfigPuts(uartBaseAddr,"Number of samples in FIFO:",-1);
    UARTConfigPutNum(uartBaseAddr,(uint32_t)fifoWordCnt);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"FIFO Data:\n", -1);
    for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
    {
        fifoData = ADCGetFIFOData(APP_ADC_MODULE, ADC_FIFO_NUM_0);
        stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                    ADC_FIFODATA_ADCCHNLID_SHIFT);
        fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                    ADC_FIFODATA_ADCDATA_SHIFT);
        voltageLvl  = fifoData * (uint32_t) APP_ADC_REF_VOLTAGE;
        voltageLvl /= (uint32_t) APP_ADC_RANGE_MAX;
        UARTConfigPuts(uartBaseAddr,"Step ID:",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)(stepID + 1U));
        UARTConfigPuts(uartBaseAddr,"\n",-1);
        UARTConfigPuts(uartBaseAddr,"Voltage Level:",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)voltageLvl);
        UARTConfigPuts(uartBaseAddr,"mV\n",-1);
    }
    AppADCStop();
    /* Power down ADC */
    ADCPowerUp(APP_ADC_MODULE, FALSE);
    /* Disable ADC module */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_ADC_CLKCTRL,
                  CM_L4PER2_ADC_CLKCTRL_MODULEMODE,
                  CM_L4PER2_ADC_CLKCTRL_MODULEMODE_DISABLED);
    while (CM_L4PER2_ADC_CLKCTRL_IDLEST_DISABLE !=
           HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER2_ADC_CLKCTRL,
                         CM_L4PER2_ADC_CLKCTRL_IDLEST))
    {
        /* Wait till ADC module is disabled */
    }
#endif

    UARTConfigPuts(uartBaseAddr,"\nApplication is completed.\n", -1);;
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppADCIntrISR(void *handle)
{
    uint32_t status;

    UARTConfigPuts(uartBaseAddr,"\nIn ISR...\n", -1);
    status = ADCGetIntrStatus(APP_ADC_MODULE);
    ADCClearIntrStatus(APP_ADC_MODULE, status);
    if (ADC_INTR_SRC_END_OF_SEQUENCE == (status & ADC_INTR_SRC_END_OF_SEQUENCE))
    {
        UARTConfigPuts(uartBaseAddr,"End of sequence interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_THRESHOLD == (status & ADC_INTR_SRC_FIFO0_THRESHOLD))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 0 threshold interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_OVERRUN == (status & ADC_INTR_SRC_FIFO0_OVERRUN))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 0 overrun interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_UNDERFLOW == (status & ADC_INTR_SRC_FIFO0_UNDERFLOW))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 0 underflow interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_THRESHOLD == (status & ADC_INTR_SRC_FIFO1_THRESHOLD))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 1 threshold interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_OVERRUN == (status & ADC_INTR_SRC_FIFO1_OVERRUN))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 1 overrun interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_UNDERFLOW == (status & ADC_INTR_SRC_FIFO1_UNDERFLOW))
    {
        UARTConfigPuts(uartBaseAddr,"FIFO 1 underflow interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_OUT_OF_RANGE == (status & ADC_INTR_SRC_OUT_OF_RANGE))
    {
        UARTConfigPuts(uartBaseAddr,"Out of range interrupt occurred.\n", -1);
    }
    isrFlag = 0U;
    ADCWriteEOI(APP_ADC_MODULE);
}

static int32_t AppADCInit(void)
{
    adcRevisionId_t revId;
    int32_t         configStatus = STW_EFAIL;

    /* Get ADC information */
    ADCGetRevisionId(APP_ADC_MODULE, &revId);
    UARTConfigPuts(uartBaseAddr,"ADC Revision ID:\n", -1);
    UARTConfigPuts(uartBaseAddr,"Scheme            :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.scheme);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"Functional number :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.func);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"RTL revision      :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.rtlRev);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"Major revision    :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.major);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"Minor revision    :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.minor);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    UARTConfigPuts(uartBaseAddr,"Custom revision   :",-1);
    UARTConfigPutHexNum(uartBaseAddr,(uint32_t)revId.custom);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    /* Clear All interrupt status */
    ADCClearIntrStatus(APP_ADC_MODULE, ADC_INTR_STATUS_ALL);
    /* Power up AFE */
    ADCPowerUp(APP_ADC_MODULE, TRUE);
    /* Wait for 4us at least */
    AppADCWait();
    /* Do the internal calibration */
    ADCInit(APP_ADC_MODULE, FALSE, 0U, 0U);
    /* Configure ADC divider*/
    configStatus = ADCSetClkDivider(APP_ADC_MODULE, APP_ADC_DIV);

    return configStatus;
}

static void AppADCStart(void)
{
    adcSequencerStatus_t status;

    /* Check if FSM is idle */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
    /* Start ADC conversion */
    ADCStart(APP_ADC_MODULE, TRUE);
}

static void AppADCStop(void)
{
    adcSequencerStatus_t status;

    /* Disable all/enabled steps */
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_2, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_3, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_4, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_5, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_6, FALSE);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
    /* Stop ADC */
    ADCStart(APP_ADC_MODULE, FALSE);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
}

static void AppADCWait(void)
{
    uint32_t time;

    /* One tick of 32kHz is 31.25us */
    time  = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    time += 2;
    while (time > (HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR)))
    {}
}
/********************************* End of file ******************************/
