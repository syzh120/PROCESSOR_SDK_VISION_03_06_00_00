/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file     epwm_app.c
 *
 *  \brief    This file contains PWM test application which sets a particular
 *            duty cycle in PWMSS1 output A (EHRPWM1A) which can be verified
 *            through external pin probing.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "epwm_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/*
 * Configurable parameters
 */
/**
 *  \brief PWM instance base address.
 *
 *  Note: If changed to other instance, PRCM and pinmux changes needs to be
 *  taken care in the application.
 */
#define APP_EHRPWM_INST_BASE_ADDR       (SOC_PWMSS1_IPWMSS_BASE)

/**
 *  \brief Output channel - A or B.
 *
 *  Note: If changed to channel B, pinmux changes needs to be taken care
 *  in the application.
 */
#define APP_EHRPWM_OUTPUT_CH            (CSL_EPWM_OUTPUT_CH_A)

/** \brief Frequency of PWM output signal in Hz - 1 KHz is selected */
#define APP_EHRPWM_OUT_FREQ             (1U * 1000U)

/** \brief Duty Cycle of PWM output signal in % - give value from 0 to 100 */
#define APP_EHRPWM_DUTY_CYCLE           (25U)

/** \brief APP run time in seconds */
#define APP_RUN_TIME                    (10U)

/** \brief APP run count in event equal zero ISR count */
#define APP_RUN_TIME_ISRCOUNT           (APP_RUN_TIME * APP_EHRPWM_OUT_FREQ)

/**
 *  \brief Functional clock to the PWMSS.
 *  Fixed for the platform - can't be changed.
 */
#define SOC_EHRPWM_MODULE_FREQ          (133U * 1000U * 1000U)

/** \brief TB frequency in Hz - so that /4 divider is used */
#define APP_EHRPWM_TB_FREQ              (SOC_EHRPWM_MODULE_FREQ / 4U)

/**
 *  \brief PRD value - this determines the period
 *
 *  PRD = (TBCLK/PWM FREQ) / 2
 *  NOTE: /2 is added becasue up&down counter is selected. So period is 2 times
 */
#define APP_EHRPWM_PRD_VAL              ((APP_EHRPWM_TB_FREQ                   \
                                            / APP_EHRPWM_OUT_FREQ) / 2U)
/**
 *  \brief COMPA value - this determines the duty cycle
 *
 *  COMPA = (PRD - ((dutycycle * PRD) / 100)
 */
#define APP_EHRPWM_COMPA_VAL            (APP_EHRPWM_PRD_VAL -                  \
                                            ((APP_EHRPWM_DUTY_CYCLE *          \
                                                APP_EHRPWM_PRD_VAL) / 100U))

#define APP_EHRPWM_INT                  (32U)
#define APP_EHRPWM_XBAR_CPU             (CSL_XBAR_IRQ_CPU_ID_IPU1)
#define APP_EHRPWM_XBAR_INST            (CSL_XBAR_INST_IPU1_IRQ_32)
#define APP_EHRPWM_XBAR_INTR_SOURCE     (CSL_XBAR_PWMSS1_IRQ_ePWM0INT)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief IP default configuration */
static CSL_EpwmAppPwmObj_t gAppPwmObj =
{
    APP_EHRPWM_OUTPUT_CH,                       /* pwmCh */
    APP_EHRPWM_INST_BASE_ADDR,                  /* instAddr */
    SOC_EHRPWM_MODULE_FREQ,                     /* funcClk */
    FALSE,                                      /* enableDeadband */
    FALSE,                                      /* enableChopper */
    FALSE,                                      /* enableTripzone */
    TRUE,                                       /* enableEventTrigger */
    FALSE,                                      /* enableHighResolution */
    /* CSL_EpwmAppPwmCfg_t*/
    {
        /* CSL_EpwmTimebaseCfg_t */
        {
            APP_EHRPWM_TB_FREQ,                 /* tbClk */
            APP_EHRPWM_OUT_FREQ,                /* pwmtbCounterFreqPrd */
            CSL_EPWM_TB_COUNTER_DIR_UP_DOWN,    /* tbCntrDirection */
            FALSE,                              /* enableSynchronization */
            PWMSS_EPWM_TBCTL_PHSDIR_COUNT_DOWN, /* cntDirAfterSync */
            0U,                                 /* phsCountAfterSync */
            PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC /* syncOutSrc */
        },
        /* CSL_EpwmCounterCmpCfg_t */
        {
            APP_EHRPWM_COMPA_VAL,               /* cmpAValue */
            APP_EHRPWM_COMPA_VAL                /* cmpBValue */
        },
        /* CSL_EpwmAqActionCfg_t */
        {
            CSL_EPWM_AQ_ACTION_DONOTHING,       /* zeroAction */
            CSL_EPWM_AQ_ACTION_DONOTHING,       /* prdAction */
            CSL_EPWM_AQ_ACTION_HIGH,            /* cmpAUpAction */
            CSL_EPWM_AQ_ACTION_LOW,             /* cmpADownAction */
            CSL_EPWM_AQ_ACTION_HIGH,            /* cmpBUpAction */
            CSL_EPWM_AQ_ACTION_LOW              /* cmpBDownAction */
        },
        /* CSL_EpwmDeadbandCfg_t */
        {
            CSL_EPWM_DB_IN_MODE_A_RED_A_FED,    /* inputMode */
            CSL_EPWM_DB_OUT_MODE_BYPASS,        /* outputMode */
            CSL_EPWM_DB_POL_SEL_ACTV_HIGH,      /* polaritySelect */
            0U,                                 /* risingEdgeDelay */
            0U                                  /* fallingEdgeDelay */
        },
        /* CSL_EpwmChopperCfg_t */
        {
            CSL_EPWM_CHP_DUTY_CYCLE_PERC_12PNT5,    /* dutyCycle */
            CSL_EPWM_CHP_CLK_FREQ_DIV_BY_1,         /* clkFrequency */
            CSL_EPWM_CHP_OSHT_WIDTH_1XSYSOUT_BY_8   /* oneShotPulseWidth */
        },
        /* CSL_EpwmTripzoneCfg_t */
        {
            CSL_EPWM_TZ_TRIP_ACTION_DO_NOTHING, /* tripAction */
            CSL_EPWM_TZ_EVENT_ONE_SHOT,         /* tripEvtType */
            0U,                                 /* tripPin */
            FALSE                               /* enableTripIntr */
        },
        /* CSL_EpwmEtCfg_t */
        {
            CSL_EPWM_ET_INTR_EVT_CNT_EQ_ZRO,    /* intrEvtSource */
            CSL_EPWM_ET_INTR_PERIOD_FIRST_EVT   /* intrPrd */
        }
    }
};

static volatile uint32_t gNumIsr = 0U;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
static uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
static uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void AppPwmIntrISR(void *handle);

static void CSL_epwmAppPwmCfg(CSL_EpwmAppPwmObj_t *pObj);
static void EpwmAppTimebaseModuleCfg(uint32_t baseAddr,
                                     uint32_t pwmFuncClk,
                                     CSL_EpwmTimebaseCfg_t *pTbCfg);
static void EpwmAppCounterComparatorCfg(uint32_t baseAddr,
                                        CSL_EpwmCounterCmpCfg_t *pCcCfg);

static void padConfig_prcmEnable(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(void)
{
    CSL_EpwmAppPwmObj_t *pObj = &gAppPwmObj;

    /* Do pad config amd PRCM enable for UART and PWM */
    padConfig_prcmEnable();

    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200,
                   UART_WORD_LENGTH_8, UART_STOP_BIT_1,
                   UART_NO_PARITY, UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr,
        "\nStarting EPWM duty cycle test application...\n", -1);
    UARTConfigPuts(
        uartBaseAddr, "Probe the PWM signal to verify...\n"
        "App will wait for 10 seconds (using  PWM period ISR)...\n", -1);
    UARTConfigPuts(uartBaseAddr,
        "Probe "
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
        "VIN2A_VSYNC0 pin (RU19 pin 12) "
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        "GPMC_BEN0 pin (R9017/M1 of VISU connector) "
#endif
        "for 1KHz @ 25% duty cycle waveform...\n", -1);

    /* Enable clocks for EPWM module inside the PWM sub system. */
    CSL_epwmClockEnable(pObj->instAddr);

    /* EPWM channel configuration */
    CSL_epwmAppPwmCfg(pObj);

    /* Wait for ISR count */
    while (gNumIsr < APP_RUN_TIME_ISRCOUNT);

    UARTConfigPuts(uartBaseAddr, "\nApplication is completed!!\n", -1);
    return 0;
}

static void AppPwmIntrISR(void *handle)
{
    uint16_t status = CSL_epwmEtIntrStatus(APP_EHRPWM_INST_BASE_ADDR);

    CSL_epwmEtIntrClear(APP_EHRPWM_INST_BASE_ADDR);
    gNumIsr++;
    return;
}

/**
 * \brief   This API configures the ePWM module
 *
 * \param   pObj             pointer to the ePwm object data structure.
 */
static void CSL_epwmAppPwmCfg(CSL_EpwmAppPwmObj_t *pObj)
{
    uint32_t baseAddr = pObj->instAddr;
    uint32_t pwmCh    = pObj->pwmCh;
    uint32_t pwmFuncClk = pObj->funcClk;
    CSL_EpwmAppPwmCfg_t *pPwmCfg = &pObj->pwmCfg;

    /* Configure the Time base Sub-Module */
    EpwmAppTimebaseModuleCfg(baseAddr, pwmFuncClk, &pPwmCfg->tbCfg);

    /* Counter-Comparator Sub-Module Configuration */
    EpwmAppCounterComparatorCfg(baseAddr, &pPwmCfg->ccCfg);

    /* Configure Action Qualifier */
    CSL_epwmAqActionOnOutputCfg(baseAddr, pwmCh, &pPwmCfg->aqCfg);

    /* Dead band sub-module configuration */
    if (TRUE == pObj->enableDeadband)
    {
       /* Enable and configure dead band sub module */
       CSL_epwmDeadbandCfg(baseAddr, &pPwmCfg->dbCfg);
    }
    else
    {
        /* Bypass dead band sub module */
        CSL_epwmDeadbandBypass(baseAddr);
    }

    /* Chopper sub-module configuration */
    if (TRUE == pObj->enableChopper)
    {
        /* Configure chopper sub - module */
        CSL_epwmChopperCfg(baseAddr, &pPwmCfg->chpCfg);

        /* Enable Chopper */
        CSL_epwmChopperEnable(baseAddr, TRUE);
    }
    else
    {
        /* Disable Chopper */
        CSL_epwmChopperEnable(baseAddr, FALSE);
    }

    /* Trip Zone Sub-Module Configuration */
    if (TRUE == pObj->enableTripZone)
    {
        /* Configure the Trip action */
        CSL_epwmTzTriggerTripAction(
            baseAddr, CSL_EPWM_TZ_TRIP_ACTION_HIGH, pwmCh);

        /* Enable the Trip event */
        CSL_epwmTzTripEventEnable(
            baseAddr, pPwmCfg->tzCfg.tripEvtType, pPwmCfg->tzCfg.tripPin);
    }
    else
    {
        /* Disable trip zone event handling and ignore all trip zone events */
        CSL_epwmTzTripEventDisable(
            baseAddr, CSL_EPWM_TZ_EVENT_ONE_SHOT, pPwmCfg->tzCfg.tripPin);
        CSL_epwmTzTripEventDisable(
            baseAddr, CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE, pPwmCfg->tzCfg.tripPin);
    }

    /* Event trigger sub - module configuration */
    if (TRUE == pObj->enableEventTrigger)
    {
        /* Configure the Event trigger processing */
        CSL_epwmEtIntrCfg(
            baseAddr, pPwmCfg->etCfg.intrEvtSource, pPwmCfg->etCfg.intrPrd);
        CSL_epwmEtIntrEnable(baseAddr);
    }
    else
    {
        /* Disable Event trigger interrupts */
        CSL_epwmEtIntrDisable(baseAddr);
    }

    /**
     * High resolution feature is supported only on PWM A channel. If channel
     * is A then proceed with High Resolution processing.
     */
    if (CSL_EPWM_OUTPUT_CH_A == pwmCh)
    {
        if (TRUE == pObj->enableHighResolution)
        {
            /* configure high resolution feature */
            CSL_epwmHighResolutionCfg(
                baseAddr,
                pPwmCfg->hrCfg.delayBusSelect,
                pPwmCfg->hrCfg.delayMode);

            if (CSL_EPWM_HR_DELAY_BUS_SEL_CMPAHR ==
               pPwmCfg->hrCfg.delayBusSelect)
            {
                /* Load comparator A High-resolution counter value */
                CSL_epwmHrLoadCmpAHrValue(
                    baseAddr,
                    pPwmCfg->hrCfg.cmpAHighResVal,
                    CSL_EPWM_HR_REG_ACT_LOAD_CNT_ZRO_PULSE);
            }
            else  /* CSL_EPWM_HR_DELAY_BUS_SEL_TBPHSHR */
            {
                /* Load Timebase phase high resolution value */
                CSL_epwmHrLoadTbPhaseHrValue(
                    baseAddr, pPwmCfg->hrCfg.tbPhaseHighResVal);
            }
        }
        else
        {
            /* Disable High Resolution Feature */
            CSL_epwmHighResolutionDisable(baseAddr);
        }
    }

    return;
}

/**
 * \brief   This API configures the Timebase Sub-module.
 *
 * \param   baseAddr        Base address of PWMSS instance used
 * \param   pwmFuncClk      PWM functional clock value in Hz
 * \param   pTbCfg          Pointer to the Time base sub-module configuration
 *                          data structure
 */
static void EpwmAppTimebaseModuleCfg(uint32_t baseAddr,
                                     uint32_t pwmFuncClk,
                                     CSL_EpwmTimebaseCfg_t *pTbCfg)
{
    /* Configure Time base clock */
    CSL_epwmTbTimebaseClkCfg(baseAddr, pTbCfg->tbClk, pwmFuncClk);

    /* Configure PWM time base counter frequency and direction */
    CSL_epwmTbPwmFreqCfg(
        baseAddr,
        pTbCfg->tbClk,
        pTbCfg->pwmtbCounterFreqPrd,
        pTbCfg->tbCntrDirection,
        CSL_EPWM_SHADOW_REG_CTRL_ENABLE);

    if (TRUE == pTbCfg->enableSynchronization)
    {
        /* Enable Synchronization */
        CSL_epwmTbSyncEnable(
            baseAddr, pTbCfg->phsCountAfterSync, pTbCfg->cntDirAfterSync);
    }
    else
    {
        /* Disable Synchronization */
        CSL_epwmTbSyncDisable(baseAddr);
    }

    /* Configure Sync out signal */
    CSL_epwmTbSetSyncOutMode(baseAddr, pTbCfg->syncOutSrc);

    /* Configure the emulation behaviour */
    CSL_epwmTbSetEmulationMode(baseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    return;
}

/**
 * \brief   This API configures the Counter-Comparator Sub-module.
 *
 * \param   baseAddr    Base address of PWMSS instance used
 * \param   pCcCfg      Pointer to the Counter-Comparator Sub-module
 *                      configuration data structure
 */
static void EpwmAppCounterComparatorCfg(uint32_t baseAddr,
                                        CSL_EpwmCounterCmpCfg_t *pCcCfg)
{
    /* Counter Comparator A configuration */
    CSL_epwmCounterComparatorCfg(
        baseAddr,
        CSL_EPWM_CC_CMP_A,
        pCcCfg->cmpAValue,
        CSL_EPWM_SHADOW_REG_CTRL_ENABLE,
        CSL_EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO,
        TRUE);

    /* Counter Comparator B configuration */
    CSL_epwmCounterComparatorCfg(
        baseAddr,
        CSL_EPWM_CC_CMP_B,
        pCcCfg->cmpBValue,
        CSL_EPWM_SHADOW_REG_CTRL_ENABLE,
        CSL_EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO,
        TRUE);

    return;
}

static void padConfig_prcmEnable(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
    /* UART Pad configurations */
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD, 0x00040000);
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD, 0x00000000);

    /* PWM Pad configurations - VIN2A_VSYNC0 -> EHRPWM1A */
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_VIN2A_VSYNC0, 0x0000000A);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* UART Pad configurations */
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK, 0x00040001);
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0, 0x00000001);

    /* PWM Pad configurations - GPMC_BEN0 -> EHRPWM1A */
    HW_WR_REG32(
        SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_BEN0, 0x00000004);
#endif

    /* Enable PRCM for PWMSS1 */
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS1_CLKCTRL, 0x2);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER2_PWMSS1_CLKCTRL) & (0x00030000)) != 0x0) ;
    /* Time base clock for PWMSS1 module */
    HW_WR_FIELD32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_CONTROL_IO_2,
        CTRL_CORE_CONTROL_IO_2_PWMSS1_TBCLKEN,
        1);

    /* XBar configuration */
    CSL_xbarIrqConfigure(
        APP_EHRPWM_XBAR_CPU, APP_EHRPWM_XBAR_INST, APP_EHRPWM_XBAR_INTR_SOURCE);

    /* Enable periodic interrupts for PWM period */
    Intc_Init();
    Intc_IntEnable(APP_EHRPWM_INT);

    /* Register ISR */
    Intc_IntRegister(APP_EHRPWM_INT, (IntrFuncPtr) AppPwmIntrISR, 0);
    Intc_IntPrioritySet(APP_EHRPWM_INT, 1, 0);
    Intc_SystemEnable(APP_EHRPWM_INT);

    return;
}
