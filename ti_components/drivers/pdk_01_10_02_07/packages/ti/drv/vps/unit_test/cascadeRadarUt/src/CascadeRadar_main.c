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
 *  \file CascadeRadar_main.c
 *
 *  \brief Cascade Radar sample application.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CascadeRadar_main.h>

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

static void CascadeRadar_createTsk(void);
static void CascadeRadar_tskMain(UArg arg0, UArg arg1);
static Void CascadeRadar_CalcResolution(UInt32 profileId, float *range,
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
#pragma DATA_ALIGN(gCascadeRadarTskStackMain, 32)
#pragma DATA_SECTION(gCascadeRadarTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8             gCascadeRadarTskStackMain[CASCADE_APP_TSK_STACK_MAIN];

/* Test application object */
CascadeRadar_Ar12xxConfigOut       gCascadeRadarObj;

static volatile UInt32   gExitApp;

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle gEdmaHandle;

Bsp_Ar12xxInitParams gAr12xx_initParams;

UInt32 gCascadeRadarFrmRecdNum[4] = {0};
UInt32 gCascadeRadarFrmError[4] = {0};

/* When Advanced frame configuration is set this is ignored */
rlFrameCfg_t   gCASCADE_RADARFrmArgsMaster =
{
    .chirpStartIdx = (rlUInt16_t) 0,
    .chirpEndIdx   = (rlUInt16_t) 0,
    .numLoops      = (rlUInt16_t) CASCADE_RADAR_RADAR_HEIGHT,
    .numFrames     = (rlUInt16_t) 0,
    /* profileCfgArgs[1].numAdcSamples * 2 - 512 * 2*/
    .numAdcSamples     = (rlUInt16_t) CASCADE_RADAR_PROFILE1_RADAR_WIDTH * (rlUInt16_t)2,
    .framePeriodicity  = (rlUInt32_t) CASCADE_RADAR_TIME_MS_TO_5NS(33U), /* 33 ms / 30 FPS, 20 ms / 50fps */
    .triggerSelect     = (rlUInt16_t) RL_FRAMESTRT_API_TRIGGER,
    .reserved0         = (rlUInt32_t) 0,
    .reserved1         = (rlUInt32_t) 0,
    .frameTriggerDelay = (rlUInt32_t) 0
};

rlFrameCfg_t   gCASCADE_RADARFrmArgsSlave =
{
    .chirpStartIdx = (rlUInt16_t) 0,
    .chirpEndIdx   = (rlUInt16_t) 0,
    .numLoops      = (rlUInt16_t) CASCADE_RADAR_RADAR_HEIGHT,
    .numFrames     = (rlUInt16_t) 0,
    /* profileCfgArgs[1].numAdcSamples * 2 - 512 * 2*/
    .numAdcSamples     = (rlUInt16_t) CASCADE_RADAR_PROFILE1_RADAR_WIDTH * (rlUInt16_t)2,
    .framePeriodicity  = (rlUInt32_t) CASCADE_RADAR_TIME_MS_TO_5NS(66.6), /* 33 ms / 30 FPS, 20 ms / 50fps */
    .triggerSelect     = (rlUInt16_t) RL_FRAMESTRT_SYNCIN_TRIGGER,
    .reserved0         = (rlUInt32_t) 0,
    .reserved1         = (rlUInt32_t) 0,
    .frameTriggerDelay = (rlUInt32_t) 0
};

rlProfileCfg_t gCASCADE_RADARProfileArgs[] = {
    {
        .profileId             = (rlUInt16_t) 0,
        .pfVcoSelect           = (rlUInt8_t) 0,
        .pfCalLutUpdate        = (rlUInt8_t) 0,
        .startFreqConst        = (rlUInt32_t) CASCADE_RADAR_FREQ_GHZ_CONV(77),
        .idleTimeConst         = (rlUInt32_t) CASCADE_RADAR_TIME_US_TO_10NS(100U),
        .adcStartTimeConst     = (rlUInt32_t) CASCADE_RADAR_TIME_US_TO_10NS(6U),
        .rampEndTime           = (rlUInt32_t) CASCADE_RADAR_TIME_US_TO_10NS(60U),
        .txOutPowerBackoffCode = (rlUInt32_t) 0,
        .txPhaseShifter        = (rlUInt32_t) 0,
        .freqSlopeConst        = (rlInt16_t) CASCADE_RADAR_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(60U),
        .txStartTime           = (rlInt16_t) CASCADE_RADAR_TIME_US_TO_10NS(0U),
        .numAdcSamples         = (rlUInt16_t) CASCADE_RADAR_PROFILE1_RADAR_WIDTH,
        .digOutSampleRate      = (rlUInt16_t) 10000, /* Kilo Samples per second */
        .hpfCornerFreq1        = (rlUInt8_t) RL_RX_HPF1_175_KHz,
        .hpfCornerFreq2        = (rlUInt8_t) RL_RX_HPF2_350_KHz,
        .txCalibEnCfg          = (rlUInt16_t) 0,
        .rxGain = (rlUInt16_t) 30
    }
};

rlChirpCfg_t   gCASCADE_RADARChirpCfgArgsMaster[] =
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
rlChirpCfg_t   gCASCADE_RADARChirpCfgArgsSlave[] =
{
    {
        .chirpStartIdx   = (rlUInt16_t) 0x0,
        .chirpEndIdx     = (rlUInt16_t) 0x0,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlUInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x0, /* TX1 */
        .reserved        = (rlUInt16_t) 0x0
    }
};

rlBpmChirpCfg_t   gCASCADE_RADARBpmChirpCfgArgs[] =
{
    {
        .chirpStartIdx = (rlUInt16_t) 0x0,
        .chirpEndIdx   = (rlUInt16_t) 0x0,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    }
};

/**< \brief Sensor configuration for the CASCADE_RADAR Radar Sensor  */
Bsp_Ar12xxConfigObj   gAr12xx_config_master =
{
    .rfChanCfgArgs            = {
        .rxChannelEn = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_RX_ANTENNA) - 1,
        .txChannelEn = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_TX_ANTENNA) - 1,
        .cascading   = (rlUInt16_t) 0x1,
        .cascadingPinoutCfg = (rlUInt16_t) 0x0
    },
    .adcOutCfgArgs            = {
        .fmt                  = {
            .b2AdcBits    = CASCADE_RADAR_DATA_FORMAT_CONFIG,
            .b6Reserved0 = (rlUInt32_t) 0x0,
            .b8FullScaleReducFctr = (rlUInt32_t) 0x0,
            .b2AdcOutFmt  = RL_ADC_FORMAT_COMPLEX_1X,
            .b14Reserved1 = (rlUInt32_t) 0x0
        },
        .reserved0      = (rlUInt16_t) 0x0
    },
    .dataFmtCfgArgs           = {
        .rxChannelEn  = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_RX_ANTENNA) - 1,
        .adcBits      = (rlUInt16_t) CASCADE_RADAR_DATA_FORMAT_CONFIG,
        .adcFmt       = (rlUInt16_t) RL_ADC_FORMAT_COMPLEX_1X,
        .iqSwapSel    = (rlUInt8_t) RL_DEV_I_FIRST,
        .chInterleave = (rlUInt8_t) RL_DEV_CH_NON_INTERLEAVED,
        .reserved     = (rlUInt32_t) 0x0
    },
    .rfLpModeCfgArgs          = {
        .reserved      = (rlUInt16_t) 0,
        .lpAdcMode     = (rlUInt16_t) RL_ADC_MODE_REGULAR
    },
    .chirpCfgArgs      = gCASCADE_RADARChirpCfgArgsMaster,
    .numChirpCfgArgs   = sizeof(gCASCADE_RADARChirpCfgArgsMaster)/sizeof(rlChirpCfg_t),
    .profileCfgArgs    = gCASCADE_RADARProfileArgs,
    .numProfileCfgArgs = sizeof(gCASCADE_RADARProfileArgs)/sizeof(rlProfileCfg_t),
    .frameCfgArgs      = &gCASCADE_RADARFrmArgsMaster,
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
        .dataRate   = (rlUInt8_t) CASCADE_RADAR_CSI_DATA_RATE_VALUE,
        .reserved   = (rlUInt16_t) 0
    },
    .hsiClkgs                 = {
        .hsiClk   = (rlUInt16_t) CASCADE_RADAR_DDR_HSI_CLK,
        .reserved = (rlUInt16_t) 0x0
    },
    .laneEnCfgArgs            = {
        .laneEn   = (rlUInt16_t)
            #if CASCADE_RADAR_CSI_DATA1LANE_POS
                ((rlUInt16_t) 0x1) |
            #endif
            #if CASCADE_RADAR_CSI_DATA2LANE_POS
                ((rlUInt16_t) 0x2) |
            #endif
            #if CASCADE_RADAR_CSI_DATA3LANE_POS
                ((rlUInt16_t) 0x4) |
            #endif
            #if CASCADE_RADAR_CSI_DATA4LANE_POS
                ((rlUInt16_t) 0x8) |
            #endif
                ((rlUInt16_t) 0x0),
        .reserved = (rlUInt16_t) 0x0
    },
    .ldoBypassCfgArgs = {1, 0},
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
    .bpmChirpCfgArgs = gCASCADE_RADARBpmChirpCfgArgs,
    .numBpmChirpCfgArgs = sizeof(gCASCADE_RADARBpmChirpCfgArgs)/sizeof(rlBpmChirpCfg_t),
    .csiConfigArgs = {
        .lanePosPolSel = ((CASCADE_RADAR_CSI_CLOCKLANE_POS << 16U) | /* Polarity Always */
                         (CASCADE_RADAR_CSI_DATA4LANE_POS << 12U) | /* assumed to be 0 */
                         (CASCADE_RADAR_CSI_DATA3LANE_POS << 8U) |
                         (CASCADE_RADAR_CSI_DATA2LANE_POS << 4U) |
                         (CASCADE_RADAR_CSI_DATA1LANE_POS)),
        .reserved1 = (rlUInt32_t) 0U,
    }
};

/**< \brief Sensor configuration for the CASCADE_RADAR Radar Sensor  */
Bsp_Ar12xxConfigObj   gAr12xx_config_slave =
{
    .rfChanCfgArgs            = {
        .rxChannelEn = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_RX_ANTENNA) - 1,
        .txChannelEn = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_TX_ANTENNA) - 1,
        .cascading   = (rlUInt16_t) 0x0,
        .cascadingPinoutCfg = (rlUInt16_t) 0x0
    },
    .adcOutCfgArgs            = {
        .fmt                  = {
            .b2AdcBits    = CASCADE_RADAR_DATA_FORMAT_CONFIG,
            .b6Reserved0 = (rlUInt32_t) 0x0,
            .b8FullScaleReducFctr = (rlUInt32_t) 0x0,
            .b2AdcOutFmt  = RL_ADC_FORMAT_COMPLEX_1X,
            .b14Reserved1 = (rlUInt32_t) 0x0
        },
        .reserved0      = (rlUInt16_t) 0x0
    },
    .dataFmtCfgArgs           = {
        .rxChannelEn  = (rlUInt16_t) (1<<CASCADE_RADAR_NUM_RX_ANTENNA) - 1,
        .adcBits      = (rlUInt16_t) CASCADE_RADAR_DATA_FORMAT_CONFIG,
        .adcFmt       = (rlUInt16_t) RL_ADC_FORMAT_COMPLEX_1X,
        .iqSwapSel    = (rlUInt8_t) RL_DEV_I_FIRST,
        .chInterleave = (rlUInt8_t) RL_DEV_CH_NON_INTERLEAVED,
        .reserved     = (rlUInt32_t) 0x0
    },
    .rfLpModeCfgArgs          = {
        .reserved      = (rlUInt16_t) 0,
        .lpAdcMode     = (rlUInt16_t) RL_ADC_MODE_REGULAR
    },
    .chirpCfgArgs      = gCASCADE_RADARChirpCfgArgsSlave,
    .numChirpCfgArgs   = sizeof(gCASCADE_RADARChirpCfgArgsSlave)/sizeof(rlChirpCfg_t),
    .profileCfgArgs    = gCASCADE_RADARProfileArgs,
    .numProfileCfgArgs = sizeof(gCASCADE_RADARProfileArgs)/sizeof(rlProfileCfg_t),
    .frameCfgArgs      = &gCASCADE_RADARFrmArgsSlave,
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
        .dataRate   = (rlUInt8_t) CASCADE_RADAR_CSI_DATA_RATE_VALUE,
        .reserved   = (rlUInt16_t) 0
    },
    .hsiClkgs                 = {
        .hsiClk   = (rlUInt16_t) CASCADE_RADAR_DDR_HSI_CLK,
        .reserved = (rlUInt16_t) 0x0
    },
    .laneEnCfgArgs            = {
        .laneEn   = (rlUInt16_t)
            #if CASCADE_RADAR_CSI_DATA1LANE_POS
                ((rlUInt16_t) 0x1) |
            #endif
            #if CASCADE_RADAR_CSI_DATA2LANE_POS
                ((rlUInt16_t) 0x2) |
            #endif
            #if CASCADE_RADAR_CSI_DATA3LANE_POS
                ((rlUInt16_t) 0x4) |
            #endif
            #if CASCADE_RADAR_CSI_DATA4LANE_POS
                ((rlUInt16_t) 0x8) |
            #endif
                ((rlUInt16_t) 0x0),
        .reserved = (rlUInt16_t) 0x0
    },
    .ldoBypassCfgArgs = {1, 0},
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
    .bpmChirpCfgArgs = gCASCADE_RADARBpmChirpCfgArgs,
    .numBpmChirpCfgArgs = sizeof(gCASCADE_RADARBpmChirpCfgArgs)/sizeof(rlBpmChirpCfg_t),
    .csiConfigArgs = {
        .lanePosPolSel = ((CASCADE_RADAR_CSI_CLOCKLANE_POS << 16U) | /* Polarity Always */
                         (CASCADE_RADAR_CSI_DATA4LANE_POS << 12U) | /* assumed to be 0 */
                         (CASCADE_RADAR_CSI_DATA3LANE_POS << 8U) |
                         (CASCADE_RADAR_CSI_DATA2LANE_POS << 4U) |
                         (CASCADE_RADAR_CSI_DATA1LANE_POS)),
        .reserved1 = (rlUInt32_t) 0U,
    }
};

/* Test application object */
CascadeRadar_vipObj              gCaptAppObj;

uint32_t frameDone[BSP_AR12XX_MAX_DEVICES_SUPPORTED] = {0};

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
    CascadeRadar_createTsk();

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
    EDMA3_DRV_Result edmaResult = 0;

    gEdmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME " EDMA driver initialization FAIL\r\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME " EDMA driver initialization PASS.\r\n");
    }
}
/*
 * Create test task
 */
static void CascadeRadar_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = RADAR_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gCascadeRadarTskStackMain;
    tskPrms.stackSize     = sizeof (gCascadeRadarTskStackMain);
    tskPrms.arg0          = (UArg) & gCascadeRadarObj;
    gCascadeRadarObj.tskHandle = Task_create(CascadeRadar_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gCascadeRadarObj.tskHandle != NULL));

    return;
}

Void CascadeRadar_ar12xxInit(void)
{
    char customNameMaster[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        CASCADE_RADAR_CONFIG_NAME_MASTER;
    char customNameSlave[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        CASCADE_RADAR_CONFIG_NAME_SLAVE;
    Int32 retVal = BSP_SOK;
    UInt32 i = 0;
    CascadeRadar_InitPadMuxAR12();
    /* Get the initial default parameters for the radar link configuration */
    Bsp_ar12xxInitParams_init (&gAr12xx_initParams);

    gAr12xx_initParams.numRadarDevicesInCascade = 4;
    gAr12xx_initParams.masterDevId = 0;
    gAr12xx_initParams.devParams[0].uartDevInst = 0xFF;
    gAr12xx_initParams.devParams[1].uartDevInst = 0xFF;
    gAr12xx_initParams.devParams[2].uartDevInst = 0xFF;
    gAr12xx_initParams.devParams[3].uartDevInst = 0xFF;

    GT_0trace(BspAppTrace, GT_INFO,
        APP_NAME " AR12xx Initializing FPGA ...\n\r");

    if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
    {
        /* On Rev A, only one GPIO to lift the CRESET and power on ALL FPGA */
        retVal = Utils_fgpaPowerUp(0);
        GT_assert(BspAppTrace, BSP_SOK == retVal);
    }

    for (i = 0; i < gAr12xx_initParams.numRadarDevicesInCascade; i++)
    {
        /* Lift the CRESET and power on each FPGA */
        if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
        {
            retVal = Utils_fgpaPowerUp(i);
            GT_assert(BspAppTrace, BSP_SOK == retVal);
        }
        /* Lift the Logic reset for each FPGA. FPGA will now be ready to accept
         * CSI Data.
         */
        retVal = Utils_fpgaStart(i);
        GT_assert(BspAppTrace, BSP_SOK == retVal);
    }

    GT_0trace(BspAppTrace, GT_INFO,
        APP_NAME " AR12xx Initializing FPGA Done...\n\r");
    /* Master AR1243 */
    {
        Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
        {(UInt8) 6, (UInt8) 24, (UInt16) 51};     /* GPIO7, Pin 24, CPU Intr 51 */
        Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
        = {
            /* GPIO2, PIN 2 BSP_AR12XX_GPIO_OUTPUT_NRESET */
            {(UInt8) 1,    (UInt8) 2},
            /* GPIO2, PIN 12: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
            {(UInt8) 1, (UInt8) 12},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
            {(UInt8) 0xFF, (UInt8) 5 },
            /* GPIO1, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
            {(UInt8) 1, (UInt8) 22},
            /* GPIO1 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
            {(UInt8) 1, (UInt8) 25},
            /* GPIO1 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
            {(UInt8) 1, (UInt8) 13},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
            {(UInt8) 0, (UInt8) 16},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
            {(UInt8) 0, (UInt8) 17}
        };
        memcpy(&gAr12xx_initParams.devParams[0].inGpioParams, &inGpioParamsDef,
               sizeof (inGpioParamsDef));
        memcpy(&gAr12xx_initParams.devParams[0].outGpioParams, outGpioParamsDef,
               sizeof (outGpioParamsDef));

        /* Use McSPI1 */
        gAr12xx_initParams.devParams[0].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST0;
        gAr12xx_initParams.devParams[0].mcspiChannel = 0U;
    }
    /* Slave 1 AR1243 */
    {
        Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
#if defined (CUSTOM_BOARD)
        {(UInt8) 7, (UInt8) 16, (UInt16) 52};  /* GPIO8, Pin 16, CPU Intr 52 */
#else
        {(UInt8) 4, (UInt8) 10, (UInt16) 52};  /* GPIO5, Pin 10, CPU Intr 52 */
#endif
        Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
        = {
            /* GPIO2, PIN 9 BSP_AR12XX_GPIO_OUTPUT_NRESET */
            {(UInt8) 1,    (UInt8) 9},
            /* GPIO2, PIN 15: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
            {(UInt8) 1, (UInt8) 12 },
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
            {(UInt8) 0xFF, (UInt8) 19 },
            /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
            {(UInt8) 1, (UInt8) 22},
            /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
            {(UInt8) 1, (UInt8) 25},
            /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
            {(UInt8) 1, (UInt8) 13},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
            {(UInt8) 0xFF, (UInt8) 0},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
            {(UInt8) 0xFF, (UInt8) 0}
        };
        memcpy(&gAr12xx_initParams.devParams[1].inGpioParams, &inGpioParamsDef,
               sizeof (inGpioParamsDef));
        memcpy(&gAr12xx_initParams.devParams[1].outGpioParams, outGpioParamsDef,
               sizeof (outGpioParamsDef));

        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            /* Use McSPI3 */
            gAr12xx_initParams.devParams[1].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST2;
            gAr12xx_initParams.devParams[1].mcspiChannel = 0U;
        }
        else
        {
            /* Use McSPI2 */
            gAr12xx_initParams.devParams[1].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST1;
            gAr12xx_initParams.devParams[1].mcspiChannel = 0U;
        }
    }
    /* Slave 2 AR1243 */
    {
        Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
#if defined (CUSTOM_BOARD)
        {(UInt8) 7, (UInt8) 17, (UInt16) 52}; /* GPIO8, Pin 17, CPU Intr 52 */
#else
        {(UInt8) 4, (UInt8) 11, (UInt16) 52}; /* GPIO5, Pin 11, CPU Intr 52 */
#endif
        Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
        =
        {
            /* GPIO2, PIN 10 BSP_AR12XX_GPIO_OUTPUT_NRESET */
            {(UInt8) 1,    (UInt8) 10},
            /* GPIO2, PIN 12: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
            {(UInt8) 1, (UInt8) 12 },
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
            {(UInt8) 0xFF, (UInt8) 19 },
            /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
            {(UInt8) 1, (UInt8) 22},
            /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
            {(UInt8) 1, (UInt8) 25},
            /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
            {(UInt8) 1, (UInt8) 13},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
            {(UInt8) 0xFF, (UInt8) 0},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
            {(UInt8) 0xFF, (UInt8) 0}
        };
        memcpy(&gAr12xx_initParams.devParams[2].inGpioParams, &inGpioParamsDef,
               sizeof (inGpioParamsDef));
        memcpy(&gAr12xx_initParams.devParams[2].outGpioParams, outGpioParamsDef,
               sizeof (outGpioParamsDef));

        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            /* Use McSPI3 */
            gAr12xx_initParams.devParams[2].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST2;
            gAr12xx_initParams.devParams[2].mcspiChannel = 1U;
        }
        else
        {
            /* Use McSPI3 */
            gAr12xx_initParams.devParams[2].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST2;
            gAr12xx_initParams.devParams[2].mcspiChannel = 0U;
        }
    }
    /* Slave 3 AR1243 */
    {
        Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
        {(UInt8) 6, (UInt8) 25, (UInt16) 51}; /* GPIO7, Pin 25, CPU Intr 51 */
        Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
        =
        {
            /* GPIO2, PIN 11 BSP_AR12XX_GPIO_OUTPUT_NRESET */
            {(UInt8) 1,    (UInt8) 11},
            /* GPIO2, PIN 15: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
            {(UInt8) 1, (UInt8) 12 },
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
            {(UInt8) 0xFF, (UInt8) 19 },
            /* GPIO2, PIN 22: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
            {(UInt8) 1, (UInt8) 22},
            /* GPIO2 PIN 25:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
            {(UInt8) 1, (UInt8) 25},
            /* GPIO2 PIN 13:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
            {(UInt8) 1, (UInt8) 13},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
            {(UInt8) 0xFF, (UInt8) 0},
            /* Not Used: BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB*/
            {(UInt8) 0xFF, (UInt8) 0}
        };
        memcpy(&gAr12xx_initParams.devParams[3].inGpioParams, &inGpioParamsDef,
               sizeof (inGpioParamsDef));
        memcpy(&gAr12xx_initParams.devParams[3].outGpioParams, outGpioParamsDef,
               sizeof (outGpioParamsDef));

        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            /* Use McSPI1 */
            gAr12xx_initParams.devParams[3].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST0;
            gAr12xx_initParams.devParams[3].mcspiChannel = 1U;
        }
        else
        {
            /* Use McSPI4 */
            gAr12xx_initParams.devParams[3].mcSpiDevInst = CASCADE_RADAR_MCSPI_INST3;
            gAr12xx_initParams.devParams[3].mcspiChannel = 0U;
        }
    }
    Utils_mcspiInit(CASCADE_RADAR_MCSPI_INST0);
    Utils_mcspiInit(CASCADE_RADAR_MCSPI_INST2);
    if (Bsp_boardGetBaseBoardRev() >= BSP_BOARD_REV_E)
    {
        Utils_mcspiInit(CASCADE_RADAR_MCSPI_INST1);
        Utils_mcspiInit(CASCADE_RADAR_MCSPI_INST3);
    }

    retVal = Bsp_ar12xxRegisterConfig(customNameMaster, &gAr12xx_config_master);
    retVal += Bsp_ar12xxRegisterConfig(customNameSlave, &gAr12xx_config_slave);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    strcpy(gAr12xx_initParams.devParams[0].radarConfigName, customNameMaster);
    strcpy(gAr12xx_initParams.devParams[1].radarConfigName, customNameSlave);
    strcpy(gAr12xx_initParams.devParams[2].radarConfigName, customNameSlave);
    strcpy(gAr12xx_initParams.devParams[3].radarConfigName, customNameSlave);

    /* Set the EDMA Handle */
    gAr12xx_initParams.devParams[0].edmaHandle = gEdmaHandle;
    gAr12xx_initParams.devParams[1].edmaHandle = gEdmaHandle;
    gAr12xx_initParams.devParams[2].edmaHandle = gEdmaHandle;
    gAr12xx_initParams.devParams[3].edmaHandle = gEdmaHandle;

    retVal = Bsp_ar12xxInit(&gAr12xx_initParams);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    /* This is an optional step if the only a single CASCADE_RADAR configuration is used.
     * If there are more than one configurations used then one can use the following API to
     * switch between configurations after performing Bsp_ar12xxInit.
     */
    retVal = Bsp_ar12xxSwitchConfig(0, customNameMaster);
    retVal += Bsp_ar12xxSwitchConfig(1, customNameSlave);
    retVal += Bsp_ar12xxSwitchConfig(2, customNameSlave);
    retVal += Bsp_ar12xxSwitchConfig(3, customNameSlave);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
}

Void CascadeRadar_ar12xxDeInit()
{
    Int32 retVal = BSP_SOK;
    char customNameMaster[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        CASCADE_RADAR_CONFIG_NAME_MASTER;
    char customNameSlave[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH] =
        CASCADE_RADAR_CONFIG_NAME_SLAVE;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx De-initing Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxDeInit();
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    retVal = Bsp_ar12xxUnRegisterConfig(customNameMaster);
    retVal += Bsp_ar12xxUnRegisterConfig(customNameSlave);
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx De-initing McSPI ...\n\r");

    Utils_mcspiDeinit(CASCADE_RADAR_MCSPI_INST0);
    Utils_mcspiDeinit(CASCADE_RADAR_MCSPI_INST2);
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
Int32 CascadeRadar_ar12xxEnableTestSource(Void)
{
#if (CASCADE_RADAR_NUM_TX_ANTENNA == 1)
    Bsp_Ar12xxTestSource tsArgs = {0};
    Int32 retVal = BSP_SOK;

    tsArgs.testObj[0].posX = 0;

    tsArgs.testObj[0].posY = 100;
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
    tsArgs.testObj[0].posY = 200;
    retVal = Bsp_ar12xxEnableDummySource(1, &tsArgs);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    tsArgs.testObj[0].posY = 300;
    retVal = Bsp_ar12xxEnableDummySource(2, &tsArgs);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    tsArgs.testObj[0].posY = 400;
    retVal = Bsp_ar12xxEnableDummySource(3, &tsArgs);
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    retVal = Bsp_ar12xxSetTestSourceSeeds();
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    return retVal;
#else
    return BSP_SOK;
#endif

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
Void CascadeRadar_ar12xxConfig(CascadeRadar_Ar12xxConfigOut *pCfgOut)
{
    Int32 retVal;
    UInt32 i;
    Bsp_BoardId boardId;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init AR12xx ... \n\r");
    CascadeRadar_ar12xxInit();
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
    COMPILE_TIME_ASSERT(sizeof(gCASCADE_RADARChirpCfgArgsMaster)/sizeof(rlChirpCfg_t) > 512);
    COMPILE_TIME_ASSERT(sizeof(gCASCADE_RADARChirpCfgArgsSlave)/sizeof(rlChirpCfg_t) > 512);
    COMPILE_TIME_ASSERT(
        sizeof(gCASCADE_RADARProfileArgs)/sizeof(rlProfileCfg_t) >
        CASCADE_RADAR_MAX_PROFILES);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Configuring the parameters for Normal Frame \n\r");
    retVal = Bsp_ar12xxConfigParams(BSP_AR12XX_CONFIG_ALL);
    pCfgOut->numProfiles = 1U;

    GT_assert(BspAppTrace, BSP_SOK == retVal);

#if defined(ENABLE_TEST_SOURCE)
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Enabling test source ...\n\r");
    CascadeRadar_ar12xxEnableTestSource();
#endif
    for (i = 0; i < pCfgOut->numProfiles; i++)
    {
        pCfgOut->radarWidth[i] = gCASCADE_RADARProfileArgs[i].numAdcSamples;
        pCfgOut->radarHeight[i] = CASCADE_RADAR_RADAR_HEIGHT;
        if (gAr12xx_config_master.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 6)
        {
            pCfgOut->inBufAddrOffset = 4U;
            pCfgOut->offsetBwAntennas [i] = pCfgOut->radarWidth[i] * sizeof(UInt32) + 4U;
        }
        else if (gAr12xx_config_master.dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 9)
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
    pCfgOut->numTxAntenna = CASCADE_RADAR_NUM_TX_ANTENNA;
    pCfgOut->numRxAntenna = CASCADE_RADAR_NUM_RX_ANTENNA;

    for (i = 0; i < pCfgOut->numProfiles; i++)
    {
        CascadeRadar_CalcResolution(i, &pCfgOut->rangeRes[i], &pCfgOut->velocityRes[i]);
    }

    pCfgOut->numValidBits = CASCADE_RADAR_ADC_DATA_FORMAT;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init AR12xx ... DONE !!!\n\r");
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
Void CascadeRadar_ar12xxStart(void)
{
    Int32 retVal = BSP_SOK;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Starting Radar Sensor ...\n\r");
    retVal = Bsp_ar12xxStartRadar();
    GT_assert(BspAppTrace, BSP_SOK == retVal);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Starting Radar Sensor ... DONE !!!\n\r");
}

Void CascadeRadar_ar12xxStop()
{
    Int32 retVal = BSP_SOK;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Stopping Radar Sensor ...\n\r");

    retVal = Bsp_ar12xxStopRadar();
    GT_assert(BspAppTrace, BSP_SOK == retVal);

    Task_sleep(100);
    CascadeRadar_ar12xxDeInit();
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " AR12xx Stopping Radar Sensor ... DONE !!!\n\r");
}

static Void CascadeRadar_CalcResolution(UInt32 profileId, float *range, float *velocity)
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
    sampling_rate = gCASCADE_RADARProfileArgs[profileId].digOutSampleRate * 100.0;
    slope = gCASCADE_RADARProfileArgs[profileId].freqSlopeConst * 48.0;
    speedOfLight = 3.0;
    *range = (sampling_rate * speedOfLight)/
                    (2.0 * slope * (float)gCASCADE_RADARProfileArgs[profileId].numAdcSamples);

    /* Velocity Resolution is derived using the formula:
    *                         1                    speed of light
    * deltaV = ----------------------------- x ------------------------ (in m/s)
    *          Doppler Dimention x Chirp Time    2 x Starting Frequency
    */
    startFreq = gCASCADE_RADARProfileArgs[profileId].startFreqConst * 54.0;
    chirpRepetitionTime = (gCASCADE_RADARProfileArgs[profileId].rampEndTime
                    + gCASCADE_RADARProfileArgs[profileId].idleTimeConst)
                    * 10.0/1000000000;
    *velocity = (speedOfLight * 100000000.0)/
                            (CASCADE_RADAR_RADAR_HEIGHT * 2.0 * chirpRepetitionTime * startFreq);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 CascadeRadar_vipAllocAndQueueFrames(const CascadeRadar_vipObj *appObj,
                                         CascadeRadar_vipInstObj   *instObj,
                                         UInt32             fieldMerged)
{
    Int32               retVal = FVID2_SOK;
    UInt32              streamId, chId, frmId, idx;
    UInt32              yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format       *fmt;
    Fvid2_Frame        *frm;
    Fvid2_FrameList     frmList;
    Vps_CaptVipOutInfo *outInfo;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
        {
            outInfo = &instObj->vipPrms.outStreamInfo[streamId];
            fmt     = &instObj->allocFmt[streamId];
            Fvid2Format_init(fmt);
                        /* base index for instObj->frames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * CAPT_APP_FRAMES_PER_CH
                 * streamId) + (CAPT_APP_FRAMES_PER_CH * chId);

            if (idx >= CAPT_APP_MAX_FRAMES_PER_HANDLE)
            {
                idx = 0U;
            }
            frm = &instObj->frames[idx];

            /* fill format with channel specific values  */
            fmt->chNum  = Vps_captMakeChNum(instObj->instId, streamId, chId);
            fmt->width  = appObj->maxWidth;
            fmt->height = appObj->maxHeight + CAPT_APP_PADDING_LINES;
            if (fieldMerged)
            {
                fmt->height *= 2;
            }
            fmt->pitch[0]       = outInfo->outFmt.pitch[0];
            fmt->pitch[1]       = outInfo->outFmt.pitch[1];
            fmt->pitch[2]       = outInfo->outFmt.pitch[2];
            fmt->fieldMerged[0] = FALSE;
            fmt->fieldMerged[1] = FALSE;
            fmt->fieldMerged[2] = FALSE;
            fmt->dataFormat     = outInfo->outFmt.dataFormat;
            fmt->scanFormat     = FVID2_SF_PROGRESSIVE;
            fmt->bpp = FVID2_BPP_BITS8; /* ignored */

            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                BspUtils_memClearOnAlloc(TRUE);
            }

            /*
             * alloc memory based on 'format'
             * Allocated frame info is put in frames[]
             * CAPT_APP_FRAMES_PER_CH is the number of buffers per channel to
             * allocate
             */
            retVal = BspUtils_memFrameAlloc(fmt, frm, CAPT_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Frame Alloc Failed!!!\r\n");
                break;
            }

            for (frmId = 0U; frmId < CAPT_APP_FRAMES_PER_CH; frmId++)
            {
                frm[frmId].fid        = FVID2_FID_FRAME;
                frm[frmId].appData    = instObj;
                frmList.frames[frmId] = &frm[frmId];

                if (TRUE == fieldMerged)
                {
                    /* Since BspUtils_memFrameAlloc is setting the address
                     * for only top field, set addresses for bottom fields. */
                    if (Fvid2_isDataFmtYuv422I(fmt->dataFormat))
                    {
                        yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                                      fmt->pitch[0U];
                        frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                    }
                    if (Fvid2_isDataFmtSemiPlanar(fmt->dataFormat))
                    {
                        yFld1Offset =
                            (UInt32) frm[frmId].addr[0U][0U] + fmt->pitch[0U];
                        cbCrFld0Offset =
                            (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                                      (fmt->pitch[0U] * appObj->maxHeight * 2U));
                        cbCrFld1Offset =
                            (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
                        frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
                        frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                        frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
                    }
                }
            }

            /* Set number of frame in frame list */
            frmList.numFrames = CAPT_APP_FRAMES_PER_CH;

            /*
             * queue the frames in frmList
             * All allocate frames are queued here as an example.
             * In general atleast 2 frames per channel need to queued
             * before starting capture,
             * else frame will get dropped until frames are queued
             */
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Queue Failed!!!\r\n");
                break;
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief Free frames
 */
static Int32 CascadeRadar_vipFreeFrames(CascadeRadar_vipObj     *appObj,
                                CascadeRadar_vipInstObj *instObj,
                                UInt32           fieldMerged)
{
    Int32         retVal = FVID2_SOK;
    UInt32        streamId, chId, idx;
    Fvid2_Format *fmt;
    Fvid2_Frame  *frm;
    Char          fileStr[50U];
    Char          fileNameString[100U];
    UInt32        bufSize;

    GT_assert(BspAppTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));

    /* for every stream and channel in a capture handle */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
        {
            fmt = &instObj->allocFmt[streamId];

            /* base index for instObj->frames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * CAPT_APP_FRAMES_PER_CH
                 * streamId) + (CAPT_APP_FRAMES_PER_CH * chId);

            if (idx >= CAPT_APP_MAX_FRAMES_PER_HANDLE)
            {
                idx = 0U;
            }
            frm = &instObj->frames[idx];

            snprintf(fileStr, sizeof (fileStr),
                     "captureOption%dInst%uCh%uStr%u",
                     (unsigned int) appObj->testPrms.testId,
                     (unsigned int) instObj->instId,
                     (unsigned int) chId,
                     (unsigned int) streamId);
            BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
            BspUtils_appGetFileName(fileNameString,
                                    sizeof (fileNameString),
                                    fileStr,
                                    fmt->dataFormat,
                                    fmt->width,
                                    fmt->height);
            BspOsal_cacheInv(frm[0].addr[0][0],
                             (CAPT_APP_FRAMES_PER_CH * bufSize),
                             BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
            retVal |= BspUtils_memFrameFree(fmt, frm, CAPT_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Frame Free Failed!!!\r\n");
            }
        }
        }

    return (retVal);
}

static void CascadeRadar_vipInit(CascadeRadar_vipObj *appObj)
{
    Int32  retVal = FVID2_SOK;
    /* Create global capture handle, used for common driver configuration */
    appObj->fvidHandleAll = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ALL,
            NULL,                       /* NULL for VPS_CAPT_INST_ALL */
            NULL,                       /* NULL for VPS_CAPT_INST_ALL */
            NULL);                      /* NULL for VPS_CAPT_INST_ALL */
    if (NULL == appObj->fvidHandleAll)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Global Handle Create Failed!!!\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": CascadeRadar_vipInit() - DONE !!!\r\n");
    }

    return;
}

/**
 *  CascadeRadar_vipCbFxn
 *  \brief Driver callback function.
 */
static Int32 CascadeRadar_vipCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32            retVal = FVID2_SOK;
    UInt32           streamId;
    CascadeRadar_vipInstObj *instObj = (CascadeRadar_vipInstObj *) appData;
    Fvid2_FrameList  frmList;

    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        retVal = Fvid2_dequeue(
            instObj->drvHandle,
            &frmList,
            streamId,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK == retVal)
        {
            #if defined (ENABLE_TEST_SOURCE)
            uint8_t *buffer = (uint8_t *)frmList.frames[0]->addr[0][0];
            uint32_t sizeToCheck = CASCADE_RADAR_PROFILE1_RADAR_WIDTH
                                * 2U * sizeof(int16_t);
            uint32_t chirpToCheck;
            #endif
            switch(instObj->instId)
            {
                case 0: gCascadeRadarFrmRecdNum[0]++;
                #if defined (ENABLE_TEST_SOURCE)
                        chirpToCheck = gCascadeRadarFrmRecdNum[0] % CASCADE_RADAR_RADAR_HEIGHT;
                #if defined (CUSTOM_BOARD)
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice1_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[0]++;
                        }
                #else
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice4_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[0]++;
                        }
                #endif
                #endif
                        break;
                case 2: gCascadeRadarFrmRecdNum[1]++;
                #if defined (ENABLE_TEST_SOURCE)
                #if defined (CUSTOM_BOARD)
                        chirpToCheck = gCascadeRadarFrmRecdNum[1] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice2_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[1]++;
                        }
                #else
                        chirpToCheck = gCascadeRadarFrmRecdNum[1] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice1_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[1]++;
                        }
                #endif
                #endif
                        break;
                case 4: gCascadeRadarFrmRecdNum[2]++;
                #if defined (ENABLE_TEST_SOURCE)
                #if defined (CUSTOM_BOARD)
                        chirpToCheck = gCascadeRadarFrmRecdNum[2] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice3_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[2]++;
                        }
                #else
                        chirpToCheck = gCascadeRadarFrmRecdNum[2] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice2_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[2]++;
                        }
                #endif
                #endif
                        break;
                case 6: gCascadeRadarFrmRecdNum[3]++;
                #if defined (ENABLE_TEST_SOURCE)
                #if defined (CUSTOM_BOARD)
                        chirpToCheck = gCascadeRadarFrmRecdNum[3] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice4_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[3]++;
                        }
                #else
                        chirpToCheck = gCascadeRadarFrmRecdNum[3] % CASCADE_RADAR_RADAR_HEIGHT;
                        if (0 != memcmp(
                                &buffer[sizeToCheck * chirpToCheck], gDevice3_reference, sizeToCheck))
                        {
                            gCascadeRadarFrmError[3]++;
                        }
                #endif
                #endif
                        break;
                default:
                    break;
            }
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Queue Failed!!!\r\n");
            }
        }
    }

    instObj->appObj->callBackCount++;
    frameDone[instObj->instId/2]++;

    return (retVal);
}

/**
 *  CascadeRadar_vipInitParams
 *  Initialize the global variables and frame pointers.
 */
static void CascadeRadar_vipInitParams(CascadeRadar_vipObj *appObj)
{
    UInt32 streamId, chId, instCnt, plId;
    Vps_CaptCreateParams *createPrms;
    Vps_CaptVipParams    *vipPrms;
    Vps_CaptVipScParams  *scPrms;
    Vps_CaptVipOutInfo   *outInfo;
    CascadeRadar_vipInstObj      *instObj;

    appObj->maxWidth      = CASCADE_RADAR_PROFILE1_RADAR_WIDTH * CASCADE_RADAR_NUM_RX_ANTENNA * 2;
    appObj->maxHeight     = CASCADE_RADAR_RADAR_HEIGHT * CASCADE_RADAR_NUM_TX_ANTENNA;
    appObj->callBackCount = 0U;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj            = &appObj->instObj[instCnt];
        instObj->instId    = appObj->testPrms.instId[instCnt];
        instObj->drvHandle = NULL;
        Fvid2CbParams_init(&instObj->cbPrms);
        instObj->cbPrms.cbFxn   = &CascadeRadar_vipCbFxn;
        instObj->cbPrms.appData = instObj;
        instObj->appObj         = appObj;

        createPrms = &instObj->createPrms;
        VpsCaptCreateParams_init(&instObj->createPrms);
        createPrms->videoIfMode  = appObj->testPrms.videoIfMode;
        createPrms->videoIfWidth = appObj->testPrms.videoIfWidth;
        createPrms->bufCaptMode  = VPS_CAPT_BCM_LAST_FRM_REPEAT;
        createPrms->numCh        = appObj->testPrms.numCh;
        createPrms->numStream    = appObj->testPrms.numStream;

        vipPrms = &instObj->vipPrms;
        VpsCaptVipParams_init(&instObj->vipPrms);
        vipPrms->inFmt.chNum           = 0U;
        vipPrms->inFmt.width           = appObj->testPrms.inWidth;
        vipPrms->inFmt.height          = appObj->testPrms.inHeight;
        vipPrms->inFmt.pitch[0U]       = 0U;
        vipPrms->inFmt.pitch[1U]       = 0U;
        vipPrms->inFmt.pitch[2U]       = 0U;
        vipPrms->inFmt.fieldMerged[0U] = FALSE;
        vipPrms->inFmt.fieldMerged[1U] = FALSE;
        vipPrms->inFmt.fieldMerged[2U] = FALSE;
        vipPrms->inFmt.dataFormat      = appObj->testPrms.inDataFmt;
        vipPrms->inFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
        #ifdef CASCADE_RADAR_VIP_ONLY_TEST
        vipPrms->inFmt.bpp      = FVID2_BPP_BITS8;
        #else
        vipPrms->inFmt.bpp      = FVID2_BPP_BITS16;
        #endif
        vipPrms->inFmt.reserved = NULL;
        vipPrms->scPrms         = &instObj->scPrms;
        VpsCaptVipScParams_init(&instObj->scPrms);
        scPrms = &instObj->scPrms;
        scPrms->inCropCfg.cropStartX   = 0U;
        scPrms->inCropCfg.cropStartY   = 0U;
        scPrms->inCropCfg.cropWidth    = vipPrms->inFmt.width;
        scPrms->inCropCfg.cropHeight   = vipPrms->inFmt.height;
        scPrms->scCfg.bypass           = FALSE;
        scPrms->scCfg.nonLinear        = FALSE;
        scPrms->scCfg.stripSize        = 0U;
        scPrms->scCfg.enableEdgeDetect = TRUE;
        scPrms->scCfg.enablePeaking    = TRUE;
        scPrms->scCfg.advCfg           = NULL;
        scPrms->scCoeffCfg      = NULL;
        scPrms->enableCoeffLoad = FALSE;
        vipPrms->vipPortCfg     = NULL;

        Bsp_platformSetVipClkInversion(instObj->instId, FALSE);
        vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol     = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol      = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol      = FVID2_POL_LOW;
            instObj->vipPortCfg.comCfg.pixClkEdgePol = FVID2_EDGE_POL_FALLING;
        Bsp_platformSetVipClkInversion(instObj->instId, TRUE);
        vipPrms->cscCfg = NULL;

        for (streamId = 0U; streamId < appObj->testPrms.numStream; streamId++)
        {
            for (chId = 0U; chId < VPS_CAPT_CH_PER_PORT_MAX; chId++)
            {
                createPrms->chNumMap[streamId][chId] =
                    Vps_captMakeChNum(instObj->instId, streamId, chId);
            }
            outInfo = &vipPrms->outStreamInfo[streamId];
            outInfo->outFmt.chNum = 0U;
            outInfo->outFmt.width =
                appObj->testPrms.outWidth[streamId];
            outInfo->outFmt.height =
                appObj->testPrms.outHeight[streamId];
            outInfo->outFmt.fieldMerged[0U] = FALSE;
            outInfo->outFmt.fieldMerged[1U] = FALSE;
            outInfo->outFmt.fieldMerged[2U] = FALSE;
            outInfo->outFmt.dataFormat      =
                appObj->testPrms.outDataFmt[streamId];
            outInfo->outFmt.scanFormat = FVID2_SF_PROGRESSIVE;
            #ifdef CASCADE_RADAR_VIP_ONLY_TEST
            outInfo->outFmt.bpp        = FVID2_BPP_BITS8;
            #else
            outInfo->outFmt.bpp        = FVID2_BPP_BITS16;
            #endif
            outInfo->outFmt.pitch[0U]  = 0U;
            outInfo->outFmt.pitch[1U]  = 0U;
            outInfo->outFmt.pitch[2U]  = 0U;
            if (Fvid2_isDataFmtSemiPlanar(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
                outInfo->outFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                    outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX];
            }
            else if (Fvid2_isDataFmtYuv422I(outInfo->outFmt.dataFormat) ||
                     (FVID2_DF_RAW16 == outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
            }
            else if (FVID2_DF_RAW08 == outInfo->outFmt.dataFormat)
            {
                outInfo->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
            }
            else
            {
                /* Align the pitch to BPP boundary as well since the pitch
                 * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
                 * bytes (1 pixel) */
                outInfo->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                    VpsUtils_align(
                        appObj->maxWidth * 3U, (VPS_BUFFER_ALIGNMENT * 3U));
            }
            outInfo->bufFmt  = FVID2_BUF_FMT_FRAME;
            outInfo->memType = VPS_VPDMA_MT_NONTILEDMEM;
            if (!Bsp_platformIsTI814xFamilyBuild())
            {
                outInfo->maxOutWidth[0U]  = VPS_VPDMA_MAX_OUT_WIDTH_REG1;
                outInfo->maxOutHeight[0U] = VPS_VPDMA_MAX_OUT_HEIGHT_REG1;
                for (plId = 1U; plId < FVID2_MAX_PLANES; plId++)
                {
                    outInfo->maxOutWidth[plId]  = VPS_VPDMA_MAX_OUT_WIDTH_REG2;
                    outInfo->maxOutHeight[plId] =
                        VPS_VPDMA_MAX_OUT_HEIGHT_REG2;
                }
            }
            else
            {
                for (plId = 0U; plId < FVID2_MAX_PLANES; plId++)
                {
                    outInfo->maxOutWidth[plId] =
                        VPS_VPDMA_MAX_OUT_WIDTH_1920_PIXELS;
                    outInfo->maxOutHeight[plId] =
                        VPS_VPDMA_MAX_OUT_HEIGHT_1080_LINES;
                }
            }

            outInfo->scEnable = FALSE;
            if (CAPT_APP_SC_ENABLE_ALL == appObj->testPrms.scEnable)
            {
                outInfo->scEnable = TRUE;
            }
            if ((0U == streamId) &&
                (CAPT_APP_SC_ENABLE_0 == appObj->testPrms.scEnable))
            {
                outInfo->scEnable = TRUE;
            }
            if ((1U == streamId) &&
                (CAPT_APP_SC_ENABLE_1 == appObj->testPrms.scEnable))
            {
                outInfo->scEnable = TRUE;
            }
            outInfo->subFrmPrms.subFrameEnable      = FALSE;
            outInfo->subFrmPrms.numLinesPerSubFrame = 0U;
            outInfo->subFrmPrms.subFrameCb          = NULL;
        }

        instObj->maxOutWidth[0U]  = CAPT_APP_MAXSIZE_1_WIDTH;
        instObj->maxOutHeight[0U] = CAPT_APP_MAXSIZE_1_HEIGHT;
        instObj->maxOutWidth[1U]  = CAPT_APP_MAXSIZE_2_WIDTH;
        instObj->maxOutHeight[1U] = CAPT_APP_MAXSIZE_2_HEIGHT;
        instObj->maxOutWidth[2U]  = CAPT_APP_MAXSIZE_3_WIDTH;
        instObj->maxOutHeight[2U] = CAPT_APP_MAXSIZE_3_HEIGHT;
    }

    return;
}

static Int32 CascadeRadar_vipCreate(CascadeRadar_vipObj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    UInt32 streamId, chId;
    CascadeRadar_vipInstObj       *instObj;
    Vps_VpdmaMaxSizeParams vipMaxSizePrms;
    Vps_CaptFrameSkip      frmSkipPrms;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->drvHandle = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            instObj->instId,
            &instObj->createPrms,
            &instObj->createStatus,
            &instObj->cbPrms);
        if ((NULL == instObj->drvHandle) ||
            (instObj->createStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Create Failed!!!\r\n");
            retVal = instObj->createStatus.retVal;
        }

        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_CAPT_SET_VIP_PARAMS,
                &instObj->vipPrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": VIP Set Params IOCTL Failed!!!\r\n");
                Fvid2_delete(instObj->drvHandle, NULL);
                return (retVal);
            }
        }
        if (FVID2_SOK == retVal)
        {
            /* Set frame skip for each channel */
            VpsCaptFrameSkip_init(&frmSkipPrms);
            for (streamId = 0U; streamId < instObj->createPrms.numStream;
                 streamId++)
            {
                for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
                {
                    /* This IOCTL is supported only for frame drop mode */
                    if (instObj->createPrms.bufCaptMode ==
                        VPS_CAPT_BCM_FRM_DROP)
                    {
                        frmSkipPrms.chNum =
                            Vps_captMakeChNum(instObj->instId, streamId, chId);
                        frmSkipPrms.frmSkipMask = CAPT_APP_FRAME_SKIP_PATTERN;
                        retVal = Fvid2_control(
                            instObj->drvHandle,
                            IOCTL_VPS_CAPT_SET_FRAME_SKIP,
                            &frmSkipPrms,
                            NULL);
                        if (retVal != FVID2_SOK)
                        {
                            GT_0trace(
                                BspAppTrace, GT_ERR,
                                APP_NAME
                                ": VIP Set frame skip IOCTL Failed!!\r\n");
                            break;
                        }
                    }
                }
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
                    if (!Bsp_platformIsTI814xFamilyBuild())
            {
                VpsVpdmaMaxSizeParams_init(&vipMaxSizePrms);
                vipMaxSizePrms.instId = Vps_captGetVipId(
                    instObj->instId);
                vipMaxSizePrms.maxOutWidth[0U]  = instObj->maxOutWidth[0U];
                vipMaxSizePrms.maxOutHeight[0U] = instObj->maxOutHeight[0U];
                vipMaxSizePrms.maxOutWidth[1U]  = instObj->maxOutWidth[1U];
                vipMaxSizePrms.maxOutHeight[1U] = instObj->maxOutHeight[1U];
                vipMaxSizePrms.maxOutWidth[2U]  = instObj->maxOutWidth[2U];
                vipMaxSizePrms.maxOutHeight[2U] = instObj->maxOutHeight[2U];

                retVal = Fvid2_control(
                    appObj->fvidHandleAll,
                    IOCTL_VPS_CAPT_SET_VIP_MAX_SIZE,
                    &vipMaxSizePrms,
                    NULL);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": VIP Set Max Frame Size Params IOCTL Failed!!!\r\n");
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            retVal = CascadeRadar_vipAllocAndQueueFrames(appObj, instObj, FALSE);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Alloc and Queue Failed!!!\r\n");
            }
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture create complete!!\r\n");

    return (retVal);
}
static void CascadeRadar_CaptureCreate(void)
{
    CascadeRadar_vipObj *appObj = &gCaptAppObj;
    Int32 retVal;

    CascadeRadar_InitPadMuxVip();

    BspUtils_memcpy(&appObj->testPrms, &gCaptAppTestPrms[0],
                    sizeof (appObj->testPrms));

    CascadeRadar_vipInitParams(appObj);

    CascadeRadar_vipInit(appObj);

    /* Print test case information */
    GT_6trace(BspAppTrace, GT_INFO,
              APP_NAME ": HANDLES %d: MODE %04x : CH %d: RUN COUNT %d: "
              "OUTPUT:%d:%d !!!\r\n",
              appObj->testPrms.numHandles,
              appObj->testPrms.videoIfMode,
              appObj->testPrms.numCh,
              appObj->testPrms.runCount,
              appObj->testPrms.outDataFmt[0],
              appObj->testPrms.outDataFmt[1]);

    /* Create driver */
    retVal = CascadeRadar_vipCreate(appObj);
    GT_assert(BspAppTrace, (FVID2_SOK == retVal));
}

static void CascadeRadar_CaptureRun(void)
{
    UInt32           loopCount = 0U;
    UInt32 instCnt;
    CascadeRadar_vipObj *appObj = &gCaptAppObj;
    CascadeRadar_vipInstObj *instObj;
    Int32 retVal = FVID2_SOK;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Starting capture ... !!!\r\n");

    /* Start driver */
    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        retVal = Fvid2_start(instObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Start Failed!!!\r\n");
            break;
        }
    }
    GT_assert(BspAppTrace, (FVID2_SOK == retVal));
    if (FVID2_SOK == retVal)
    {
        #if !defined(CASCADE_RADAR_VIP_ONLY_TEST)
        /* Start the AWR12 sensor */
        CascadeRadar_ar12xxStart();
        #endif

        /* Capture frames, check status */
        while (loopCount < appObj->testPrms.runCount)
        {
            /* check status every sec */
            BspOsal_sleep(1000);

            loopCount++;
        }

        /* Stop driver */
        for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal  = Fvid2_stop(instObj->drvHandle, NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Stop Failed!!!\r\n");
            }
        }
    }
}

static Int32 CascadeRadar_vipdelete()
{
    Int32            retVal = FVID2_SOK;
    UInt32           instCnt, streamId;
    CascadeRadar_vipInstObj *instObj;
    Fvid2_FrameList  frmList;
    CascadeRadar_vipObj *appObj = &gCaptAppObj;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        for (streamId = 0U;
             streamId < instObj->createPrms.numStream;
             streamId++)
        {
            /* Dequeue all the request from the driver */
            while (1U)
            {
                retVal = Fvid2_dequeue(
                    instObj->drvHandle,
                    &frmList,
                    streamId,
                    FVID2_TIMEOUT_NONE);
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }

        retVal = Fvid2_delete(instObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Delete Failed!!!\r\n");
        }

        /* free frame memory */
        retVal = CascadeRadar_vipFreeFrames(appObj, instObj, FALSE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Free Frames Failed!!!\r\n");
        }
    }
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture delete complete!!\r\n");

    return (retVal);
}


/*
 * Test task main
 */
static void CascadeRadar_tskMain(UArg arg0, UArg arg1)
{
    Int32 retVal;

    spiEdmaInit();
    retVal = BspUtils_appDefaultInit(TRUE);
    GT_assert(BspAppTrace, (BSP_SOK == retVal));

    #ifdef CASCADE_RADAR_VIP_ONLY_TEST
    UInt32 i = 0;
    Int32 retVal = BSP_SOK;
    GT_0trace(BspAppTrace, GT_INFO,
        APP_NAME " AR12xx Initializing FPGA ...\n\r");
    /* Lift the CRESET and power on all the FPGA */
    Utils_fgpaPowerUp();
    for (i = 0; i < 4; i++)
    {
        /* Lift the Logic reset for each FPGA. FPGA will now be ready to accept
         * CSI Data.
         */
        retVal = Utils_fpgaStart(i);
        GT_assert(BspAppTrace, BSP_SOK == retVal);
    }
    GT_0trace(BspAppTrace, GT_INFO,
        APP_NAME " AR12xx Initializing FPGA Done...\n\r");
    CascadeRadar_CaptureCreate();
    CascadeRadar_CaptureRun();
    CascadeRadar_vipdelete();
    #else
    CascadeRadar_ar12xxConfig(&gCascadeRadarObj);
    CascadeRadar_CaptureCreate();

    CascadeRadar_CaptureRun();

    CascadeRadar_vipdelete();
    CascadeRadar_ar12xxStop();
    #if defined (ENABLE_TEST_SOURCE)
    if ((gCascadeRadarFrmError[0] != 0U) ||
       (gCascadeRadarFrmError[1] != 0U) ||
       (gCascadeRadarFrmError[2] != 0U) ||
       (gCascadeRadarFrmError[3] != 0U))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": FAIL: Data Mismatch occurred....\r\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                          APP_NAME ": PASS: Data matched correctly....\r\n");
    }
    #endif
    #endif
    BspOsal_sleep(500);

    return;
}

/**
 *******************************************************************************
 *
 * \brief This function enables the IPU_CPU_0 Timer Ticks
 *
 * \param  arg [IN]
 *
 *******************************************************************************
 */
void mainIPU1_C0TimerTick(UArg arg)
{
    #ifdef CASCADE_RADAR_VIP_ONLY_TEST
    Utils_fpgaClockTick();
    #endif
}
