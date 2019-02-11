/*
 *  Copyright (c) Texas Instruments Incorporated 2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

/**
 *  \file MonitorRadar_main.c
 *
 *  \brief Monitor Radar sample application.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <MonitorRadar_main.h>

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

static void MonitorRadar_createTsk(void);
static void MonitorRadar_tskMain(UArg arg0, UArg arg1);
static Void MonitorRadar_CalcResolution(UInt32 profileId, float *range,
                                        float *velocity);
EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gMonitorRadarTskStackMain, 32)
#pragma DATA_SECTION(gMonitorRadarTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8             gMonitorRadarTskStackMain[MONITOR_APP_TSK_STACK_MAIN];

/* Test application object */
MonitorRadar_Ar12xxConfigOut       gMonitorRadarObj;

static volatile UInt32   gExitApp;

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle gEdmaHandle;

Bsp_Ar12xxInitParams gAr12xx_initParams;

/* When Advanced frame configuration is set this is ignored */
rlFrameCfg_t   gMONITOR_RADARFrmArgs =
{
    .chirpStartIdx = (rlUInt16_t) 0,
    .chirpEndIdx   = (rlUInt16_t) 0,
    .numLoops      = (rlUInt16_t) MONITOR_RADAR_RADAR_HEIGHT,
    .numFrames     = (rlUInt16_t) 0,
    /* profileCfgArgs[1].numAdcSamples * 2 - 512 * 2*/
    .numAdcSamples     = (rlUInt16_t) MONITOR_RADAR_PROFILE1_RADAR_WIDTH * (rlUInt16_t)2,
    .framePeriodicity  = (rlUInt32_t) MONITOR_RADAR_TIME_MS_TO_5NS(33U), /* 33 ms / 30 FPS, 20 ms / 50fps */
    .triggerSelect     = (rlUInt16_t) RL_FRAMESTRT_API_TRIGGER,
    .reserved0         = (rlUInt32_t) 0,
    .reserved1         = (rlUInt32_t) 0,
    .frameTriggerDelay = (rlUInt32_t) 0
};

rlProfileCfg_t gMONITOR_RADARProfileArgs[] = {
    {
        .profileId             = (rlUInt16_t) 0,
        .pfVcoSelect           = (rlUInt8_t) 0,
        .pfCalLutUpdate        = (rlUInt8_t) 0,
        .startFreqConst        = (rlUInt32_t) MONITOR_RADAR_FREQ_GHZ_CONV(77),
        .idleTimeConst         = (rlUInt32_t) MONITOR_RADAR_TIME_US_TO_10NS(100U),
        .adcStartTimeConst     = (rlUInt32_t) MONITOR_RADAR_TIME_US_TO_10NS(6U),
        .rampEndTime           = (rlUInt32_t) MONITOR_RADAR_TIME_US_TO_10NS(60U),
        .txOutPowerBackoffCode = (rlUInt32_t) 0,
        .txPhaseShifter        = (rlUInt32_t) 0,
        .freqSlopeConst        = (rlInt16_t) MONITOR_RADAR_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(60U),
        .txStartTime           = (rlInt16_t) MONITOR_RADAR_TIME_US_TO_10NS(0U),
        .numAdcSamples         = (rlUInt16_t) MONITOR_RADAR_PROFILE1_RADAR_WIDTH,
        .digOutSampleRate      = (rlUInt16_t) 10000, /* Kilo Samples per second */
        .hpfCornerFreq1        = (rlUInt8_t) RL_RX_HPF1_175_KHz,
        .hpfCornerFreq2        = (rlUInt8_t) RL_RX_HPF2_350_KHz,
        .txCalibEnCfg          = (rlUInt16_t) 0,
        .rxGain = (rlUInt16_t) 38
    }
};

rlChirpCfg_t   gMONITOR_RADARChirpCfgArgs[] =
{
    {
        .chirpStartIdx   = (rlUInt16_t) 0x0,
        .chirpEndIdx     = (rlUInt16_t) 0x0,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlUInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x1, /* TX1 */
        .reserved        = (rlUInt16_t) 0x0
    }
};

rlBpmChirpCfg_t   gMONITOR_RADARBpmChirpCfgArgs[] =
{
    {
        .chirpStartIdx = (rlUInt16_t) 0x0,
        .chirpEndIdx   = (rlUInt16_t) 0x0,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    }
};

/**< \brief Sensor configuration for the MONITOR_RADAR Radar Sensor  */
Bsp_Ar12xxConfigObj   gAr12xx_config =
{
    .rfChanCfgArgs            = {
        .rxChannelEn = (rlUInt16_t) (1<<MONITOR_RADAR_NUM_RX_ANTENNA) - 1,
        .txChannelEn = (rlUInt16_t) (1<<MONITOR_RADAR_NUM_TX_ANTENNA) - 1,
        .cascading   = (rlUInt16_t) 0x0,
        .cascadingPinoutCfg = (rlUInt16_t) 0x0
    },
    .adcOutCfgArgs            = {
        .fmt                  = {
            .b2AdcBits    = MONITOR_RADAR_DATA_FORMAT_CONFIG,
            .b6Reserved0 = (rlUInt32_t) 0x0,
            .b8FullScaleReducFctr = (rlUInt32_t) 0x0,
            .b2AdcOutFmt  = RL_ADC_FORMAT_COMPLEX_1X,
            .b14Reserved1 = (rlUInt32_t) 0x0
        },
        .reserved0     = (rlUInt16_t) 0x0
    },
    .dataFmtCfgArgs           = {
        .rxChannelEn  = (rlUInt16_t) (1<<MONITOR_RADAR_NUM_RX_ANTENNA) - 1,
        .adcBits      = (rlUInt16_t) MONITOR_RADAR_DATA_FORMAT_CONFIG,
        .adcFmt       = (rlUInt16_t) RL_ADC_FORMAT_COMPLEX_1X,
        .iqSwapSel    = (rlUInt8_t) RL_DEV_I_FIRST,
        .chInterleave = (rlUInt8_t) RL_DEV_CH_NON_INTERLEAVED,
        .reserved     = (rlUInt32_t) 0x0
    },
    .rfLpModeCfgArgs          = {
        .reserved      = (rlUInt16_t) 0,
        .lpAdcMode     = (rlUInt16_t) RL_ADC_MODE_REGULAR
    },
    .chirpCfgArgs      = gMONITOR_RADARChirpCfgArgs,
    .numChirpCfgArgs   = sizeof(gMONITOR_RADARChirpCfgArgs)/sizeof(rlChirpCfg_t),
    .profileCfgArgs    = gMONITOR_RADARProfileArgs,
    .numProfileCfgArgs = sizeof(gMONITOR_RADARProfileArgs)/sizeof(rlProfileCfg_t),
    .frameCfgArgs      = &gMONITOR_RADARFrmArgs,
    .dataPathCfgArgs   = {
        .intfSel         = (rlUInt8_t) 0,
        .transferFmtPkt0 = (rlUInt8_t) 1, /**< Data out Format, \n
                                      b5:0 Packet 0 content selection\n
                                      000001 - ADC_DATA_ONLY \n
                                      000110 - CP_ADC_DATA \n
                                      001001 - ADC_CP_DATA \n
                                      110110 - CP_ADC_CQ_DATA
                                      b7:6 Packet 0 virtual channel number (valid only for CSI2)\n
                                      00 Virtual channel number 0 (Default)\n
                                      01 Virtual channel number 1\n
                                      02 Virtual channel number 2\n
                                      03 Virtual channel number 3 \n*/
        .transferFmtPkt1 = (rlUInt8_t) 0,/**< Data out Format, \n
                                      b5:0 Packet 0 content selection\n
                                      000000 - Suppress Packet 1 \n
                                      001110 - CP_CQ_DATA \n
                                      001011 - CQ_CP_DATA \n
                                      b7:6 Packet 1 virtual channel number (valid only for CSI2)\n
                                      00 Virtual channel number 0 (Default)\n
                                      01 Virtual channel number 1\n
                                      02 Virtual channel number 2\n
                                      03 Virtual channel number 3\n*/
        .cqConfig        = (rlUInt8_t) 2,
        .cq0TransSize    = (rlUInt8_t) 64,
        .cq1TransSize    = (rlUInt8_t) 64,
        .cq2TransSize    = (rlUInt8_t) 64,
        .reserved        = (rlUInt8_t) 0
    },
    .dataPathClkCfgArgs           = {
        .laneClkCfg = (rlUInt8_t) 1,
        .dataRate   = (rlUInt8_t) MONITOR_RADAR_CSI_DATA_RATE_VALUE,
        .reserved   = (rlUInt16_t) 0
    },
    .hsiClkgs                 = {
        .hsiClk   = (rlUInt16_t) MONITOR_RADAR_DDR_HSI_CLK,
        .reserved = (rlUInt16_t) 0x0
    },
    .laneEnCfgArgs            = {
        .laneEn   = (rlUInt16_t)
            #if MONITOR_RADAR_CSI_DATA1LANE_POS
                ((rlUInt16_t) 0x1) |
            #endif
            #if MONITOR_RADAR_CSI_DATA2LANE_POS
                ((rlUInt16_t) 0x2) |
            #endif
            #if MONITOR_RADAR_CSI_DATA3LANE_POS
                ((rlUInt16_t) 0x4) |
            #endif
            #if MONITOR_RADAR_CSI_DATA4LANE_POS
                ((rlUInt16_t) 0x8) |
            #endif
                ((rlUInt16_t) 0x0),
        .reserved = (rlUInt16_t) 0x0
    },
    .ldoBypassCfgArgs = {0, 0},
    .bpmCommnCfgArgs = {
        .mode.b2SrcSel    = 0,
        .mode.b1Reserved0  = 0,
        .mode.b13Reserved1 = 0,
        .reserved0        = (rlUInt16_t) 0,
        .reserved1        = (rlUInt16_t) 0,
        .reserved2        = (rlUInt16_t) 0,
        .reserved3        = (rlUInt32_t) 0,
        .reserved4        = (rlUInt32_t) 0
    },
    .bpmChirpCfgArgs = gMONITOR_RADARBpmChirpCfgArgs,
    .numBpmChirpCfgArgs = sizeof(gMONITOR_RADARBpmChirpCfgArgs)/sizeof(rlBpmChirpCfg_t),
    .csiConfigArgs = {
        .lanePosPolSel = ((MONITOR_RADAR_CSI_CLOCKLANE_POS << 16U) | /* Polarity Always */
                         (MONITOR_RADAR_CSI_DATA4LANE_POS << 12U) | /* assumed to be 0 */
                         (MONITOR_RADAR_CSI_DATA3LANE_POS << 8U) |
                         (MONITOR_RADAR_CSI_DATA2LANE_POS << 4U) |
                         (MONITOR_RADAR_CSI_DATA1LANE_POS)),
        .reserved1 = (rlUInt32_t) 0U,
    },
    .calibEnArgs = {
        .calibEnMask   = (rlUInt32_t) 0x17f0,
        .reserved0     = (rlUInt8_t) 0x0,
        .reserved1     = (rlUInt8_t) 0x0,
        .reserved2     = (rlUInt16_t) 0x0,
        .reserved3     = (rlUInt32_t) 0x0
  },
};

extern Bsp_Ar12xxMonConfigObj gAr1243RadarMonConfig;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    MonitorRadar_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
static void spiEdmaInit(void)
{
    gEdmaHandle = (EDMA3_DRV_Handle) BspUtils_appGetEdmaHandle();
}
/*
 * Create test task
 */
static void MonitorRadar_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = RADAR_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gMonitorRadarTskStackMain;
    tskPrms.stackSize     = sizeof (gMonitorRadarTskStackMain);
    tskPrms.arg0          = (UArg) & gMonitorRadarObj;
    gMonitorRadarObj.tskHandle = Task_create(MonitorRadar_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gMonitorRadarObj.tskHandle != NULL));

    return;
}

Void MonitorRadar_ar12xxInit(void)
{
    char customName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        MONITOR_RADAR_CONFIG_NAME;
    Int32 retVal = BSP_SOK;

    /* Get the initial default parameters for the radar link configuration */
    Bsp_ar12xxInitParams_init (&gAr12xx_initParams);

    spiEdmaInit();
    gAr12xx_initParams.numRadarDevicesInCascade = 1;
    gAr12xx_initParams.masterDevId = 0;
    gAr12xx_initParams.devParams[0].uartDevInst = 0xFF;

    Utils_mcspiInit(MONITOR_RADAR_MCSPI_INST0);
    Utils_mcspiInit(MONITOR_RADAR_MCSPI_INST2);

    retVal = Bsp_ar12xxRegisterConfig(customName, &gAr12xx_config);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    strcpy(gAr12xx_initParams.devParams[0].radarConfigName, customName);

    /* Set the EDMA Handle */
    gAr12xx_initParams.devParams[0].edmaHandle = gEdmaHandle;

    retVal = Bsp_ar12xxInit(&gAr12xx_initParams);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    /* This is an optional step if the only a single MONITOR_RADAR configuration is used.
     * If there are more than one configurations used then one can use the following API to
     * switch between configurations after performing Bsp_ar12xxInit.
     */
    retVal = Bsp_ar12xxSwitchConfig(0, customName);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
}

Void MonitorRadar_ar12xxDeInit()
{
    Int32 retVal = BSP_SOK;
    char customName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        MONITOR_RADAR_CONFIG_NAME;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx De-initing Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxDeInit();
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    retVal = Bsp_ar12xxUnRegisterConfig(customName);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx De-initing McSPI ...\n\r");

    Utils_mcspiDeinit(MONITOR_RADAR_MCSPI_INST0);
    Utils_mcspiDeinit(MONITOR_RADAR_MCSPI_INST2);
}

/**
 *******************************************************************************
 *
 * \brief   Function to enable the dummy input of objects from AR12xx
 *
 * \param   None
 * /return  retVal   BSP_SOK if the test source is set correctly.
 *
 *******************************************************************************
*/
Int32 MonitorRadar_ar12xxEnableTestSource(Void)
{
#if (MONITOR_RADAR_NUM_TX_ANTENNA == 1)
    Bsp_Ar12xxTestSource tsArgs = {0};
    Int32 retVal = BSP_SOK;

    tsArgs.testObj[0].posX = 0;

    tsArgs.testObj[0].posY = 200;
    tsArgs.testObj[0].posZ = 0;

    tsArgs.testObj[0].velX = 0;
    tsArgs.testObj[0].velY = 0;
    tsArgs.testObj[0].velZ = 0;

    tsArgs.testObj[0].posXMin = -32700;
    tsArgs.testObj[0].posYMin = 0;
    tsArgs.testObj[0].posZMin = -32700;

    tsArgs.testObj[0].posXMax = 32700;
    tsArgs.testObj[0].posYMax = 32700;
    tsArgs.testObj[0].posZMax = 32700;

    tsArgs.testObj[0].sigLvl = 150;

    tsArgs.testObj[1].posX = 0;
    tsArgs.testObj[1].posY = 32700;
    tsArgs.testObj[1].posZ = 0;

    tsArgs.testObj[1].velX = 0;
    tsArgs.testObj[1].velY = 0;
    tsArgs.testObj[1].velZ = 0;

    tsArgs.testObj[1].posXMin = -32700;
    tsArgs.testObj[1].posYMin = 0;
    tsArgs.testObj[1].posZMin = -32700;

    tsArgs.testObj[1].posXMax = 32700;
    tsArgs.testObj[1].posYMax = 32700;
    tsArgs.testObj[1].posZMax = 32700;

    tsArgs.testObj[1].sigLvl = 948;

    tsArgs.rxAntPos[0].antPosX = 0;
    tsArgs.rxAntPos[0].antPosZ = 0;
    tsArgs.rxAntPos[1].antPosX = 32;
    tsArgs.rxAntPos[1].antPosZ = 0;
    tsArgs.rxAntPos[2].antPosX = 64;
    tsArgs.rxAntPos[2].antPosZ = 0;
    tsArgs.rxAntPos[3].antPosX = 96;
    tsArgs.rxAntPos[3].antPosZ = 0;

    tsArgs.txAntPos[0].antPosX = 0;
    tsArgs.txAntPos[0].antPosZ = 0;
    tsArgs.txAntPos[1].antPosX = 0;
    tsArgs.txAntPos[1].antPosZ = 0;
    tsArgs.txAntPos[2].antPosX = 0;
    tsArgs.txAntPos[2].antPosZ = 0;

    retVal = Bsp_ar12xxEnableDummySource(0, &tsArgs);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    return retVal;
#else
    return BSP_SOK;
#endif

}

static UInt32 monCount[26] = {0};
typedef struct MonitorRadar_Ar12xxReport_t
{
    rlRfRunTimeCalibReport_t    rfRunTimeCalibReport;
    rlMonTempReportData_t       monTempReportData;
    rlMonRxGainPhRep_t          monRxGainPhRep;
    rlMonRxNoiseFigRep_t        monRxNoiseFigRep;
    rlMonRxIfStageRep_t         monRxIfStageRep;
    rlMonTxPowRep_t             monTx0PowRep;
    rlMonTxPowRep_t             monTx1PowRep;
    rlMonTxBallBreakRep_t       monTx0BallBreakRep;
    rlMonTxBallBreakRep_t       monTx1BallBreakRep;
    rlMonReportHdrData_t        monReportHdrData;
    rlMonTxGainPhaMisRep_t      monTxGainPhaMisRep;
    rlMonTxBpmRep_t             monTx0BpmRep;
    rlMonTxBpmRep_t             monTx1BpmRep;
    rlMonSynthFreqRep_t         monSynthFreqRep;
    rlMonExtAnaSigRep_t         monExtAnaSigRep;
    rlMonTxIntAnaSigRep_t       monTx0IntAnaSigRep;
    rlMonTxIntAnaSigRep_t       monTx1IntAnaSigRep;
    rlMonRxIntAnaSigRep_t       monRxIntAnaSigRep;
    rlMonPmclkloIntAnaSigRep_t  monPmclkloIntAnaSigRep;
    rlMonGpadcIntAnaSigRep_t    monGpadcIntAnaSigRep;
    rlMonPllConVoltRep_t        monPllConVoltRep;
    rlMonDccClkFreqRep_t        monDccClkFreqRep;
} MonitorRadar_Ar12xxReport;
static MonitorRadar_Ar12xxReport report[20] = {0};
Void MonitorRadar_printReport()
{
    Int32 i = 0;
    for (i = 0; i < monCount[0]; i++)
    {
        rlRfRunTimeCalibReport_t * ptr =
            (rlRfRunTimeCalibReport_t *) &report[i].rfRunTimeCalibReport;
        GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
        GT_1trace(BspAppTrace, GT_INFO,
           " AR12XX: MON: Calibration Error = 0x%x\r\n",ptr->calibErrorFlag);
        GT_1trace(BspAppTrace, GT_INFO,
           " AR12XX: MON: calibUpdateStatus = 0x%x\r\n", ptr->calibUpdateStatus);
        GT_1trace(BspAppTrace, GT_INFO,
           " AR12XX: MON: Temperature = %d deg C\r\n", ptr->temperature);
        GT_1trace(BspAppTrace, GT_INFO,
           " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[1]; i++)
    {
         rlMonTempReportData_t * ptr =
            (rlMonTempReportData_t *) &report[i].monTempReportData;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Temperature Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_RX0 = %d deg C\r\n", ptr->tempValues[0]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_RX1 = %d deg C\r\n", ptr->tempValues[1]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_RX2 = %d deg C\r\n", ptr->tempValues[2]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_RX3 = %d deg C\r\n", ptr->tempValues[3]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_TX0 = %d deg C\r\n", ptr->tempValues[4]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_TX1 = %d deg C\r\n", ptr->tempValues[5]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_TX2 = %d deg C\r\n", ptr->tempValues[6]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_PM = %d deg C\r\n", ptr->tempValues[7]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TEMP_DIG1 = %d deg C\r\n", ptr->tempValues[8]);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[2]; i++)
    {
         rlMonRxGainPhRep_t * ptr =
            (rlMonRxGainPhRep_t *) &report[i].monRxGainPhRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: RX Gain Phase Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 12; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Rx Gain [%d] = %d\r\n", idCnt,
                ptr->rxGainVal[idCnt]);
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Rx Phase [%d] = %d\r\n", idCnt,
                ptr->rxPhaseVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[3]; i++)
    {
         rlMonRxNoiseFigRep_t * ptr =
            (rlMonRxNoiseFigRep_t *) &report[i].monRxNoiseFigRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: RX Noise Figure Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 12; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Noise Figure Value [%d] = %d\r\n", idCnt,
                ptr->rxNoiseFigVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[4]; i++)
    {
         rlMonRxIfStageRep_t * ptr =
            (rlMonRxIfStageRep_t *) &report[i].monRxIfStageRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: RX IF Stage Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 8; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: HPF Cutoff Error [%d] = %d\r\n", idCnt,
                ptr->hpfCutOffFreqEr[idCnt]);
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: LPF Cutoff Error [%d] = %d\r\n", idCnt,
                ptr->lpfCutOffFreqEr[idCnt]);
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: RX IFA Gain Error [%d] = %d\r\n", idCnt,
                ptr->rxIfaGainErVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[5]; i++)
    {
         rlMonTxPowRep_t * ptr =
            (rlMonTxPowRep_t *) &report[i].monTx0PowRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx0 Power Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 3; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX Power Value [%d] = %d\r\n", idCnt,
                ptr->txPowVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[6]; i++)
    {
         rlMonTxPowRep_t * ptr =
            (rlMonTxPowRep_t *) &report[i].monTx1PowRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx1 Power Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 3; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX Power Value [%d] = %d\r\n", idCnt,
                ptr->txPowVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[7]; i++)
    {
         rlMonTxBallBreakRep_t * ptr =
            (rlMonTxBallBreakRep_t *) &report[i].monTx0BallBreakRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx0 Ball Break Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TX reflection coefficient = %d\r\n", ptr->txReflCoefVal);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[8]; i++)
    {
         rlMonTxBallBreakRep_t * ptr =
            (rlMonTxBallBreakRep_t *) &report[i].monTx1BallBreakRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx1 Ball Break Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: TX reflection coefficient = %d\r\n", ptr->txReflCoefVal);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[9]; i++)
    {
         rlMonReportHdrData_t * ptr =
            (rlMonReportHdrData_t *) &report[i].monReportHdrData;
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Monitorring Report Header, Temp = %d\r\n",
            ptr->avgTemp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[10]; i++)
    {
         rlMonTxGainPhaMisRep_t * ptr =
            (rlMonTxGainPhaMisRep_t *) &report[i].monTxGainPhaMisRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx Gain Mismatch Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         for (idCnt = 0; idCnt < 9; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX Gain Value [%d] = %d\r\n", idCnt,
                ptr->txGainVal[idCnt]);
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX Phase Value [%d] = %d\r\n", idCnt,
                ptr->txPhaVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[11]; i++)
    {
         rlMonTxBpmRep_t * ptr =
            (rlMonTxBpmRep_t *) &report[i].monTx0BpmRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx0 BPM Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX output amplitude difference = %d\r\n",
                ptr->txBpmAmpDiff);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[12]; i++)
    {
         rlMonTxBpmRep_t * ptr =
            (rlMonTxBpmRep_t *) &report[i].monTx1BpmRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx1 BPM Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: TX output amplitude difference = %d\r\n",
                ptr->txBpmAmpDiff);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[13]; i++)
    {
         rlMonSynthFreqRep_t * ptr =
            (rlMonSynthFreqRep_t *) &report[i].monSynthFreqRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Synthesizer Frequency Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Maximum instantaneous frequency error = %d\r\n",
                ptr->maxFreqErVal);
         GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Frequency error threshold violation = %d\r\n",
                ptr->freqFailCnt);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[14]; i++)
    {
         rlMonExtAnaSigRep_t * ptr =
            (rlMonExtAnaSigRep_t *) &report[i].monExtAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx External Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         for (idCnt = 0; idCnt < 6; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: External Measured Value [%d] = %d\r\n", idCnt,
                ptr->extAnaSigVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[15]; i++)
    {
         rlMonTxIntAnaSigRep_t * ptr =
            (rlMonTxIntAnaSigRep_t *) &report[i].monTx0IntAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx0 Internal Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[16]; i++)
    {
         rlMonTxIntAnaSigRep_t * ptr =
            (rlMonTxIntAnaSigRep_t *) &report[i].monTx1IntAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Tx1 Internal Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[17]; i++)
    {
         rlMonRxIntAnaSigRep_t * ptr =
            (rlMonRxIntAnaSigRep_t *) &report[i].monRxIntAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Rx Internal Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[18]; i++)
    {
         rlMonPmclkloIntAnaSigRep_t * ptr =
            (rlMonPmclkloIntAnaSigRep_t *) &report[i].monPmclkloIntAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: PMCLKLO Internal Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Profile Index = %d\r\n", ptr->profIndex);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[19]; i++)
    {
         rlMonGpadcIntAnaSigRep_t * ptr =
            (rlMonGpadcIntAnaSigRep_t *) &report[i].monGpadcIntAnaSigRep;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: GPADC Internal Analog Signal Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: GP ADC Reference 1 Value = %d\r\n", ptr->gpadcRef1Val);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: GP ADC Reference 2 Value = %d\r\n", ptr->gpadcRef2Val);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[20]; i++)
    {
         rlMonPllConVoltRep_t * ptr =
            (rlMonPllConVoltRep_t *) &report[i].monPllConVoltRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: PLL Control Voltage Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         for (idCnt = 0; idCnt < 8; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: External Measured Value [%d] = %d\r\n", idCnt,
                ptr->pllContVoltVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
    GT_0trace(BspAppTrace, GT_INFO,
           "=======================================================\r\n");
    for (i = 0; i < monCount[21]; i++)
    {
         rlMonDccClkFreqRep_t * ptr =
            (rlMonDccClkFreqRep_t *) &report[i].monDccClkFreqRep;
         int32_t idCnt = 0;
         GT_1trace(BspAppTrace, GT_INFO,
           "-------------------------(%d)-------------------------\r\n",i);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: PLL Control Voltage Report Status = %d\r\n",
            ptr->statusFlags);
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Error Code = 0x%x\r\n", ptr->errorCode);
         for (idCnt = 0; idCnt < 8; idCnt++)
         {
             GT_2trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: External Measured Value [%d] = %d\r\n", idCnt,
                ptr->freqMeasVal[idCnt]);
         }
         GT_1trace(BspAppTrace, GT_INFO,
            " AR12XX: MON: Time Stamp = %d ms\r\n", ptr->timeStamp);
    }
}

Void MonitorRadar_Handler(UInt16 sbId, Void * payload)
{
    switch (sbId)
    {
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_RUN_TIME_CALIB_REPORT_SB):
        {
            memcpy((Void*)&report[monCount[0]].rfRunTimeCalibReport,
                   (Void*)payload, sizeof(rlRfRunTimeCalibReport_t));
            monCount[0]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_CPUFAULT_SB):
            GT_0trace(BspAppTrace, GT_ERR,
                " AR12XX: FAULT: BSS CPU fault!!\r\n");
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_ESMFAULT_SB):
            GT_0trace(BspAppTrace, GT_ERR, " AR12XX: FAULT: ESM fault!!\r\n");
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TEMPERATURE_REPORT_SB):
        {
            memcpy((Void*)&report[monCount[1]].monTempReportData,
                   (Void*)payload, sizeof(rlMonTempReportData_t));
            monCount[1]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_GAIN_PHASE_REPORT):
        {
            memcpy((Void*)&report[monCount[2]].monRxGainPhRep,
                   (Void*)payload, sizeof(rlMonRxGainPhRep_t));
            monCount[2]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_NOISE_FIG_REPORT):
        {
            memcpy((Void*)&report[monCount[3]].monRxNoiseFigRep,
                   (Void*)payload, sizeof(rlMonRxNoiseFigRep_t));
            monCount[3]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_IF_STAGE_REPORT):
        {
            memcpy((Void*)&report[monCount[4]].monRxIfStageRep,
                   (Void*)payload, sizeof(rlMonRxIfStageRep_t));
            monCount[4]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX0_POWER_REPORT):
        {
            memcpy((Void*)&report[monCount[5]].monTx0PowRep,
                   (Void*)payload, sizeof(rlMonTxPowRep_t));
            monCount[5]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX1_POWER_REPORT):
        {
            memcpy((Void*)&report[monCount[6]].monTx1PowRep,
                   (Void*)payload, sizeof(rlMonTxPowRep_t));
            monCount[6]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX0_BALLBREAK_REPORT):
        {
            memcpy((Void*)&report[monCount[7]].monTx0BallBreakRep,
                   (Void*)payload, sizeof(rlMonTxBallBreakRep_t));
            monCount[7]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX1_BALLBREAK_REPORT):
        {
            memcpy((Void*)&report[monCount[8]].monTx1BallBreakRep,
                   (Void*)payload, sizeof(rlMonTxBallBreakRep_t));
            monCount[8]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_REPORT_HEADER_SB):
        {
            memcpy((Void*)&report[monCount[9]].monReportHdrData,
                  (Void*)payload, sizeof(rlMonReportHdrData_t));
            monCount[9]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TIMING_FAIL_REPORT_SB):
        {
             rlCalMonTimingErrorReportData_t * ptr =
                (rlCalMonTimingErrorReportData_t *) payload;
             GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: Timing Fail code = %d\r\n", ptr->timingFailCode);
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_DEV_ASYNC_EVENT_MSG, RL_DEV_AE_MSS_ESMFAULT_SB):
        {
             rlMssEsmFault_t * ptr =
                (rlMssEsmFault_t *) payload;
             GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: MSS ESM Report ESM Group1 = %d\r\n",
                ptr->esmGrp1Err);
             GT_1trace(BspAppTrace, GT_INFO,
                " AR12XX: MON: MSS ESM Report ESM Group2 = 0x%x\r\n",
                ptr->esmGrp2Err);
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX_GAIN_MISMATCH_REPORT):
        {
            memcpy((Void*)&report[monCount[10]].monTxGainPhaMisRep,
                   (Void*)payload, sizeof(rlMonTxGainPhaMisRep_t));
            monCount[10]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX0_BPM_REPORT):
        {
            memcpy((Void*)&report[monCount[11]].monTx0BpmRep,
                   (Void*)payload, sizeof(rlMonTxBpmRep_t));
            monCount[11]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX1_BPM_REPORT):
        {
            memcpy((Void*)&report[monCount[12]].monTx1BpmRep,
                   (Void*)payload, sizeof(rlMonTxBpmRep_t));
            monCount[12]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_SYNTHESIZER_FREQ_REPORT):
        {
            memcpy((Void*)&report[monCount[13]].monSynthFreqRep,
                   (Void*)payload, sizeof(rlMonSynthFreqRep_t));
            monCount[13]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_EXT_ANALOG_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[14]].monExtAnaSigRep,
                   (Void*)payload, sizeof(rlMonExtAnaSigRep_t));
            monCount[14]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX0_INT_ANA_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[15]].monTx0IntAnaSigRep,
                   (Void*)payload, sizeof(rlMonTxIntAnaSigRep_t));
            monCount[15]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX1_INT_ANA_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[16]].monTx1IntAnaSigRep,
                   (Void*)payload, sizeof(rlMonTxIntAnaSigRep_t));
            monCount[16]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_RX_INT_ANALOG_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[17]].monRxIntAnaSigRep,
                   (Void*)payload, sizeof(rlMonRxIntAnaSigRep_t));
            monCount[17]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_PMCLKLO_INT_ANA_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[18]].monPmclkloIntAnaSigRep,
                   (Void*)payload, sizeof(rlMonPmclkloIntAnaSigRep_t));
            monCount[18]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_GPADC_INT_ANA_SIG_REPORT):
        {
            memcpy((Void*)&report[monCount[19]].monGpadcIntAnaSigRep,
                   (Void*)payload, sizeof(rlMonGpadcIntAnaSigRep_t));
            monCount[19]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_PLL_CONTROL_VOLT_REPORT):
        {
            memcpy((Void*)&report[monCount[20]].monPllConVoltRep,
                   (Void*)payload, sizeof(rlMonPllConVoltRep_t));
            monCount[20]++;
            break;
        }
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_DCC_CLK_FREQ_REPORT):
        {
            memcpy((Void*)&report[monCount[21]].monDccClkFreqRep,
                   (Void*)payload, sizeof(rlMonDccClkFreqRep_t));
            monCount[21]++;
            break;
        }
        default:
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to Initialize and configure the AR12 sensor.
 *
 * \param   pCfgOut Configuration parameters populated by the AR12 parameters.
 *
 * \return  None
 *
 *******************************************************************************
*/
Void MonitorRadar_ar12xxConfig(MonitorRadar_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal;
    UInt32 i;
    Bsp_BoardId boardId;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init AR12xx ... \n\r");
    MonitorRadar_ar12xxInit();
    boardId = Bsp_boardGetId();
    if (boardId == BSP_BOARD_TDA3XX_AR12XX_ALPS)
    {
        /* For the ALPS board assume the AR12 Flash is already programmed
         * with firmware. Hence not downloading firmware again through SPI.
         * If the firmware has to be downloaded through SPI, make the input to
         * this API as 1 and ensure the AR12 Flash is erased.
         */
        retVal = Bsp_ar12xxBoot(0U);
    }
    else if ((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
            || (boardId == BSP_BOARD_TDA3XX_RVP_A))
    {
        retVal = Bsp_ar12xxBoot(0U);
    }
    else
    {
        /* For the TDA3xx EVM + DIB + VAB + Booster Pack setup always load the
         * firmware via SPI.
         */
        retVal = Bsp_ar12xxBoot(1U);
    }
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    retVal = Bsp_ar12xxGetWidthHeight(0U, &pCfgOut->csi2OutWidth, &pCfgOut->csi2OutHeight);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Config AR12xx ... \n\r");
    /* Check for certain size limitations. This will show up as compile time
     * issues.
     */
    COMPILE_TIME_ASSERT(sizeof(gMONITOR_RADARChirpCfgArgs)/sizeof(rlChirpCfg_t) > 512);
    COMPILE_TIME_ASSERT(
        sizeof(gMONITOR_RADARProfileArgs)/sizeof(rlProfileCfg_t) >
        MONITOR_RADAR_MAX_PROFILES);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Configuring the parameters for Normal Frame \n\r");
    retVal = Bsp_ar12xxConfigParams(BSP_AR12XX_CONFIG_ALL);
    pCfgOut->numProfiles = 1U;

    GT_assert(BspAppTrace, BSP_SOK == retVal);

#if defined(ENABLE_TEST_SOURCE)
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Enabling test source ...\n\r");
    MonitorRadar_ar12xxEnableTestSource();
#endif
    for (i = 0; i < pCfgOut->numProfiles; i++)
    {
        pCfgOut->radarWidth[i] = gMONITOR_RADARProfileArgs[i].numAdcSamples;
        pCfgOut->radarHeight[i] = MONITOR_RADAR_RADAR_HEIGHT;
        if (gAr12xx_config.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 6)
        {
            pCfgOut->inBufAddrOffset = 4U;
            pCfgOut->offsetBwAntennas [i] = pCfgOut->radarWidth[i] * sizeof(UInt32) + 4U;
        }
        else if (gAr12xx_config.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 9)
        {
            pCfgOut->inBufAddrOffset = 0U;
            pCfgOut->offsetBwAntennas [i] = pCfgOut->radarWidth[i] * sizeof(UInt32) + 4U;
        }
        else
        {
            pCfgOut->inBufAddrOffset = 0U;
            pCfgOut->offsetBwAntennas [i] = pCfgOut->radarWidth[i] * sizeof(UInt32);
        }
    }
    pCfgOut->numTxAntenna = MONITOR_RADAR_NUM_TX_ANTENNA;
    pCfgOut->numRxAntenna = MONITOR_RADAR_NUM_RX_ANTENNA;

    for (i = 0; i < pCfgOut->numProfiles; i++)
    {
        MonitorRadar_CalcResolution(i, &pCfgOut->rangeRes[i], &pCfgOut->velocityRes[i]);
    }

    pCfgOut->numValidBits = MONITOR_RADAR_ADC_DATA_FORMAT;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init AR12xx ... DONE !!!\n\r");

    gAr1243RadarMonConfig.monReportCallBackFunc = MonitorRadar_Handler;
    retVal = Bsp_ar12xxConfigMonitor(0, &gAr1243RadarMonConfig);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    retVal = Bsp_ar12xxRestoreCalibData(0, gAr1243RadarMonConfig.calibDataStoreRestore);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
}
/**
 *******************************************************************************
 *
 * \brief   Function to Start the AR12 sensor
 *
 * \param   None
 *
 * \return  None
 *
 *******************************************************************************
*/
Void MonitorRadar_ar12xxStart(void)
{
    Int32 retVal = BSP_SOK;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Starting Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStartRadar();
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Starting Radar Sensor ... DONE !!!\n\r");
}

Void MonitorRadar_ar12xxStop()
{
    Int32 retVal = BSP_SOK;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Stopping Radar Sensor ...\n\r");

    retVal = Bsp_ar12xxStopRadar();
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    Task_sleep(100);
    MonitorRadar_ar12xxDeInit();
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Stopping Radar Sensor ... DONE !!!\n\r");
}

static Void MonitorRadar_CalcResolution(UInt32 profileId, float *range, float *velocity)
{
    float sampling_rate, slope, speedOfLight;
    float startFreq, chirpRepetitionTime;

    /* Range resolution is derived using the formula:
     * deltaR =       speed of light
     *          --------------------------- (in meters)
     *          (2 x Radar Chirp Bandwidth)
     * Radar Chirp Bandwidth = Chirp Slope * Number of samples per chirp
     *                         -----------------------------------------
     *                                     Sampling Rate
     */
    sampling_rate = gMONITOR_RADARProfileArgs[profileId].digOutSampleRate * 100.0;
    slope = gMONITOR_RADARProfileArgs[profileId].freqSlopeConst * 48.0;
    speedOfLight = 3.0;
    *range = (sampling_rate * speedOfLight)/
                    (2.0 * slope * (float)gMONITOR_RADARProfileArgs[profileId].numAdcSamples);

    /* Velocity Resolution is derived using the formula:
    *                         1                    speed of light
    * deltaV = ----------------------------- x ------------------------ (in m/s)
    *          Doppler Dimention x Chirp Time    2 x Starting Frequency
    */
    startFreq = gMONITOR_RADARProfileArgs[profileId].startFreqConst * 54.0;
    chirpRepetitionTime = (gMONITOR_RADARProfileArgs[profileId].rampEndTime
                    + gMONITOR_RADARProfileArgs[profileId].idleTimeConst)
                    * 10.0/1000000000;
    *velocity = (speedOfLight * 100000000.0)/
                            (MONITOR_RADAR_RADAR_HEIGHT * 2.0 * chirpRepetitionTime * startFreq);
}

/*
 * Test task main
 */
static void MonitorRadar_tskMain(UArg arg0, UArg arg1)
{
    /* System init */
    Int32 retVal = BspUtils_appDefaultInit(TRUE);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\r\n");
    }

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System Init Failed!!!\r\n");
        BspUtils_appLogTestResult(BSPUTILS_APP_TST_STATUS_FAIL);
        return;
    }

    MonitorRadar_ar12xxConfig(&gMonitorRadarObj);

    MonitorRadar_ar12xxStart();

    BspOsal_sleep(18000);

    MonitorRadar_ar12xxStop();

    MonitorRadar_printReport();

    BspOsal_sleep(500);

    return;
}
