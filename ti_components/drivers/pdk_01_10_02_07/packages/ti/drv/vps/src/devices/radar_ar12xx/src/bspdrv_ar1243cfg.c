/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 */

/**
 *  \file   bspdrv_ar1243Cfg.c
 *
 *  \brief  AR1243 Radar sensor configuration file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * On the TDA3x EVM and the ALPS board the CSI data lane positions are
 * as below:
 *
 *        TDA                              AR
 *   ----------------                 ------------------
 *   csi2_0_dx/y0   |-----------------| dx/dy0          data1
 *   csi2_0_dx/y1   |-----------------| dx/dy2 ** Note  clock
 *   csi2_0_dx/y2   |-----------------| dx/dy1 ** Note  data2
 *   csi2_0_dx/y3   |-----------------| dx/dy3          data3
 *   csi2_0_dx/y4   |-----------------| dx/dy4          data4
 *   ----------------                 ------------------
 */
/** \brief AR CSI clock lane position */
#define BSP_AR1243_CSI_CLOCKLANE_POS        (3U)
/** \brief AR CSI first data lane position */
#define BSP_AR1243_CSI_DATA1LANE_POS        (1U)
/** \brief AR CSI second data lane position */
#define BSP_AR1243_CSI_DATA2LANE_POS        (2U)
/** \brief AR CSI third data lane position */
#define BSP_AR1243_CSI_DATA3LANE_POS        (4U)
/** \brief AR CSI fourth data lane position */
#define BSP_AR1243_CSI_DATA4LANE_POS        (5U)

/** \brief Radar Sensor Height */
#define BSP_AR1243_RADAR_HEIGHT   (32U)

/** \brief Radar Sensor width */
#define BSP_AR1243_RADAR_WIDTH   (224U)

/** \brief Number of Radar Subframes */
#define BSP_AR1243_NUM_SUBFRAMES  (1U)

/** \brief Number of chirp Loops */
#define BSP_AR1243_NUM_CHIRP_LOOPS  (BSP_AR1243_RADAR_HEIGHT)

/** \brief Number of burst Loops */
#define BSP_AR1243_NUM_BURST_LOOPS  (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static rlFrameCfg_t    gBspAr1243FrmArgs =
{
    .reserved0     = (rlUInt16_t) 0,
    .chirpStartIdx = (rlUInt16_t) 0,
    .chirpEndIdx   = (rlUInt16_t) 0,
    .numLoops      = (rlUInt16_t) BSP_AR1243_RADAR_HEIGHT,
    .numFrames     = (rlUInt16_t) 0,
    /* profileCfgArgs[0].numAdcSamples * 2 = 224 * 2*/
    .numAdcSamples     = (rlUInt16_t) BSP_AR1243_RADAR_WIDTH* (rlUInt16_t) 2,
    .framePeriodicity  = (rlUInt32_t) 8000000, /* 40 ms */
    .triggerSelect     = (rlUInt16_t) RL_FRAMESTRT_API_TRIGGER,
    .reserved1         = (rlUInt16_t) 0,
    .frameTriggerDelay = (rlUInt32_t) 0
};

static rlProfileCfg_t  gBspAr1243ProfileArgs =
{
    .profileId             = (rlUInt16_t) 0,
    .pfVcoSelect           = (rlUInt8_t) 0,
    .pfCalLutUpdate        = (rlUInt8_t) 0,
    .startFreqConst        = (rlUInt32_t) 1454025386,
    .idleTimeConst         = (rlUInt32_t) 2000,
    .adcStartTimeConst     = (rlUInt32_t) 600,
    .rampEndTime           = (rlUInt32_t) 3000,
    .txOutPowerBackoffCode = (rlUInt32_t) 0,
    .txPhaseShifter        = (rlUInt32_t) 0,
    .freqSlopeConst        = (rlInt16_t) 1657,
    .txStartTime           = (rlInt16_t) 100,
    .numAdcSamples         = (rlUInt16_t) BSP_AR1243_RADAR_WIDTH,
    .digOutSampleRate      = (rlUInt16_t) 10000,
    .hpfCornerFreq1        = (rlUInt8_t) RL_RX_HPF1_175_KHz,
    .hpfCornerFreq2        = (rlUInt8_t) RL_RX_HPF2_350_KHz,
    .txCalibEnCfg          = (rlUInt16_t) 0,
    .rxGain                = (rlUInt16_t) 30,
    .reserved              = (rlUInt16_t) 0
};

static rlChirpCfg_t    gBspAr1243ChirpCfgArgs =
{
    .chirpStartIdx   = (rlUInt16_t) 0x0,
    .chirpEndIdx     = (rlUInt16_t) 0x0,
    .profileId       = (rlUInt16_t) 0x0, /* First profile */
    .startFreqVar    = (rlUInt32_t) 0x0,
    .freqSlopeVar    = (rlUInt16_t) 0x0,
    .idleTimeVar     = (rlUInt16_t) 0x0,
    .adcStartTimeVar = (rlUInt16_t) 0x0,
    .txEnable        = (rlUInt16_t) 0x1,
    .reserved        = (rlUInt16_t) 0x0
};

static rlBpmChirpCfg_t gAr1243RadarBpmChirpCfg[1U] =
{
    {
        .chirpStartIdx = (rlUInt16_t) 0x0,
        .chirpEndIdx   = (rlUInt16_t) 0x0,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    }
};

/**< \brief Sensor configuration for the AR1243 Radar Sensor  */
Bsp_Ar12xxConfigObj    gAr1243RadarConfig =
{
    .rfChanCfgArgs            = {
        .rxChannelEn = (rlUInt16_t) 0x0F,
        .txChannelEn = (rlUInt16_t) 0x1,
        .cascading   = (rlUInt16_t) 0x0,
        .cascadingPinoutCfg = (rlUInt16_t) 0x0
    },
    .adcOutCfgArgs            = {
        .fmt                  = {
            .b2AdcBits    = RL_ADC_DATA_14_BIT,
            .b6Reserved0 = (rlUInt32_t) 0x0,
            .b8FullScaleReducFctr = (rlUInt32_t) 0x0,
            .b2AdcOutFmt  = RL_ADC_FORMAT_COMPLEX_1X,
            .b14Reserved1 = (rlUInt32_t) 0x0
        },
        .reserved0 = (rlUInt16_t) 0x0,
        .reserved1 = (rlUInt16_t) 0x0
    },
    .dataFmtCfgArgs           = {
        .rxChannelEn  = (rlUInt16_t) 0xF,
        .adcBits      = (rlUInt16_t) RL_ADC_DATA_14_BIT,
        .adcFmt       = (rlUInt16_t) RL_ADC_FORMAT_COMPLEX_1X,
        .iqSwapSel    = (rlUInt8_t) RL_DEV_I_FIRST,
        .chInterleave = (rlUInt8_t) RL_DEV_CH_INTERLEAVED,
        .reserved     = (rlUInt32_t) 0x0
    },
    .rfLpModeCfgArgs          = {
        .reserved      = (rlUInt16_t) 0,
        .lpAdcMode     = (rlUInt16_t) RL_ADC_MODE_REGULAR
    },
    .chirpCfgArgs      = &gBspAr1243ChirpCfgArgs,
    .numChirpCfgArgs   = 1U,
    .profileCfgArgs    = &gBspAr1243ProfileArgs,
    .numProfileCfgArgs = 1U,
    .frameCfgArgs      = &gBspAr1243FrmArgs,
    .dataPathCfgArgs   = {
        .intfSel         = (rlUInt8_t) 0,
        .transferFmtPkt0 = (rlUInt8_t) 1,
        .transferFmtPkt1 = (rlUInt8_t) 0,
        .cqConfig        = (rlUInt8_t) 2,
        .cq0TransSize    = (rlUInt8_t) 64,
        .cq1TransSize    = (rlUInt8_t) 64,
        .cq2TransSize    = (rlUInt8_t) 64,
        .reserved        = (rlUInt8_t) 0
    },
    .dataPathClkCfgArgs       = {
        .laneClkCfg = (rlUInt8_t) 1,
        .dataRate   = (rlUInt8_t) 4,     /* 300 MBps */
        .reserved   = (rlUInt16_t) 0
    },
    .hsiClkgs                 = {
        .hsiClk   = (rlUInt16_t) 0xA,   /* 300 MHz */
        .reserved = (rlUInt16_t) 0x0
    },
    .laneEnCfgArgs            = {
        .laneEn   = (rlUInt16_t) 0xF,
        .reserved = (rlUInt16_t) 0x0
    },
    .ldoBypassCfgArgs         = {0, 0, 0},
    .bpmCommnCfgArgs          = {
        .mode                 = {
            .b2SrcSel     = 0,
            .b1Reserved0  = 0,
            .b13Reserved1 = 0,
        },
        .reserved0        = (rlUInt16_t) 0,
        .reserved1        = (rlUInt16_t) 0,
        .reserved2        = (rlUInt16_t) 0,
        .reserved3        = (rlUInt32_t) 0,
        .reserved4        = (rlUInt32_t) 0,
    },
    .bpmChirpCfgArgs    = gAr1243RadarBpmChirpCfg,
    .numBpmChirpCfgArgs = 1,
    .csiConfigArgs = {
        .lanePosPolSel = (((rlUInt32_t) BSP_AR1243_CSI_CLOCKLANE_POS << 16U) |
                         ((rlUInt32_t) BSP_AR1243_CSI_DATA4LANE_POS << 12U) |
                         ((rlUInt32_t) BSP_AR1243_CSI_DATA3LANE_POS << 8U) |
                         ((rlUInt32_t) BSP_AR1243_CSI_DATA2LANE_POS << 4U) |
                         (BSP_AR1243_CSI_DATA1LANE_POS)),
                          /* Polarity Always assumed to be 0 */
        .reserved1 = (rlUInt32_t) 0U,
    },
    .advFrameCfgArgs = {
        .frameSeq = {
            .numOfSubFrames = (rlUInt8_t) BSP_AR1243_NUM_SUBFRAMES,
            .forceProfile   = (rlUInt8_t) 0,
            .loopBackCfg    = (rlUInt8_t) 0,
            .subFrameTrigger = (rlUInt8_t) 0,
            .subFrameCfg = {
                {
                    .forceProfileIdx     = (rlUInt16_t) 0,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) 1,
                    .numLoops            = (rlUInt16_t) BSP_AR1243_NUM_CHIRP_LOOPS,
                    .burstPeriodicity    = (rlUInt32_t) 4000000, /* 20 ms */
                    /* burstPeriodicity >=
                     * (numLoops)* (numOfChirps) * chirpTime + InterBurstBlankTime,
                     * where InterBurstBlankTime is primarily for sensor
                     * calibration / monitoring, thermal control, and some minimum
                     * time needed for triggering next burst.
                     * NOTE: Across bursts, if the value numOfChirps, is not a
                     * constant, then the actual available blank time can vary and
                     * needs to be accounted for 1 LSB = 5 ns
                     */
                    .chirpStartIdxOffset = (rlUInt16_t) 0,
                    .numOfBurst          = (rlUInt16_t) 1,
                    .numOfBurstLoops     = (rlUInt16_t) BSP_AR1243_NUM_BURST_LOOPS,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) 8000000, /* 40 ms */
                    .reserved1           = (rlUInt32_t) 0,
                    .reserved2           = (rlUInt32_t) 0
                },
                {
                    .forceProfileIdx     = (rlUInt16_t) 0,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) 0,
                    .numLoops            = (rlUInt16_t) 0,
                    .burstPeriodicity    = (rlUInt32_t) 0,
                    .chirpStartIdxOffset = (rlUInt16_t) 0,
                    .numOfBurst          = (rlUInt16_t) 0,
                    .numOfBurstLoops     = (rlUInt16_t) 0,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) 0,
                    .reserved1           = (rlUInt32_t) 0,
                    .reserved2           = (rlUInt32_t) 0
                },
                {
                    .forceProfileIdx     = (rlUInt16_t) 0,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) 0,
                    .numLoops            = (rlUInt16_t) 0,
                    .burstPeriodicity    = (rlUInt32_t) 0,
                    .chirpStartIdxOffset = (rlUInt16_t) 0,
                    .numOfBurst          = (rlUInt16_t) 0,
                    .numOfBurstLoops     = (rlUInt16_t) 0,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) 0,
                    .reserved1           = (rlUInt32_t) 0,
                    .reserved2           = (rlUInt32_t) 0
                },
                {
                    .forceProfileIdx     = (rlUInt16_t) 0,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) 0,
                    .numLoops            = (rlUInt16_t) 0,
                    .burstPeriodicity    = (rlUInt32_t) 0,
                    .chirpStartIdxOffset = (rlUInt16_t) 0,
                    .numOfBurst          = (rlUInt16_t) 0,
                    .numOfBurstLoops     = (rlUInt16_t) 0,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) 0,
                    .reserved1           = (rlUInt32_t) 0,
                    .reserved2           = (rlUInt32_t) 0
                }
            },
            .numFrames      = (rlUInt16_t) 0,
            .triggerSelect  = (rlUInt16_t) RL_FRAMESTRT_API_TRIGGER,
            .frameTrigDelay = (rlUInt32_t) 0,
            .reserved0      = (rlUInt32_t) 0,
            .reserved1      = (rlUInt32_t) 0
        },
        .frameData = {
            .numSubFrames = (rlUInt8_t) BSP_AR1243_NUM_SUBFRAMES,
            .reserved0                         = (rlUInt8_t) 0,
            .reserved1                         = (rlUInt16_t) 0,
            .subframeDataCfg = {
                {
                    .totalChirps =
                        (rlUInt32_t) BSP_AR1243_NUM_CHIRP_LOOPS * (rlUInt32_t) BSP_AR1243_NUM_BURST_LOOPS * (rlUInt32_t) 1,
                    /* Number of Chirps in Sub-Frame =
                     *                     numOfChirps * numLoops * numOfBurst
                     */
                    .numAdcSamples = (rlUInt16_t) BSP_AR1243_RADAR_WIDTH * (rlUInt16_t) 2,
                    .numChirpsInDataPacket = (rlUInt8_t) 1,
                    /* In AR12xx: Program this as 1 */
                    .reserved = (rlUInt8_t) 0,
                },
                {
                    .totalChirps = (rlUInt32_t) 0,
                    .numAdcSamples = (rlUInt16_t) 0,
                    .numChirpsInDataPacket = (rlUInt8_t) 1,
                    .reserved = (rlUInt8_t) 0,
                },
                {
                    .totalChirps = (rlUInt32_t) 0,
                    .numAdcSamples = (rlUInt16_t) 0,
                    .numChirpsInDataPacket = (rlUInt8_t) 1,
                    .reserved = (rlUInt8_t) 0,
                },
                {
                    .totalChirps = (rlUInt32_t) 0,
                    .numAdcSamples = (rlUInt16_t) 0,
                    .numChirpsInDataPacket = (rlUInt8_t) 1,
                    .reserved = (rlUInt8_t) 0,
                }
            }
        }
    },
    .calibEnArgs = {
        .calibEnMask   = (rlUInt32_t) 0x17f0,
        .reserved0     = (rlUInt8_t) 0x0,
        .reserved1     = (rlUInt8_t) 0x0,
        .reserved2     = (rlUInt16_t) 0x0,
        .reserved3     = (rlUInt32_t) 0x0
    },
    .contModeCfgArgs = {
        .startFreqConst         = (rlUInt32_t) 0x5471C71B,
        .txOutPowerBackoffCode  = (rlUInt32_t) 0x0,
        .txPhaseShifter         = (rlUInt32_t) 0x0,
        .digOutSampleRate       = (rlUInt16_t) 2000,
        .hpfCornerFreq1         = (rlUInt8_t ) 0x0,
        .hpfCornerFreq2         = (rlUInt8_t ) 0x0,
        .rxGain                 = (rlUInt8_t ) 30,
        .vcoSelect              = (rlUInt8_t ) 0x0,
        .reserved               = (rlUInt16_t) 0x0
    },
    .frameType = BSP_AR12XX_FRAME_TYPE_NORMAL
};

/* Analog monitoring configuration */
rlMonAnaEnables_t               gAr1243monAnaEnable =
{
        /*Bit   Analog monitoring control
                0   TEMPERATURE_MONITOR_EN
                1   RX_GAIN_PHASE_MONITOR_EN
                2   RX_NOISE_MONITOR_EN
                3   RX_IFSTAGE_MONITOR_EN
                4   TX0_POWER_MONITOR_EN
                5   TX1_POWER_MONITOR_EN
                6   TX2_POWER_MONITOR_EN
                7   TX0_BALLBREAK_MONITOR_EN
                8   TX1_BALLBREAK_MONITOR_EN
                9   TX2_BALLBREAK_MONITOR_EN
                10  TX_GAIN_PHASE_MONITOR_EN
                11  TX0_BPM_MONITOR_EN
                12  TX1_BPM_MONITOR_EN
                13  TX2_BPM_MONITOR_EN
                14  SYNTH_FREQ_MONITOR_EN
                15  EXTERNAL_ANALOG_SIGNALS_MONITOR_EN
                16  INTERNAL_TX0_SIGNALS_MONITOR_EN
                17  INTERNAL_TX1_SIGNALS_MONITOR_EN
                18  INTERNAL_TX2_SIGNALS_MONITOR_EN
                19  INTERNAL_RX_SIGNALS_MONITOR_EN
                20  INTERNAL_PMCLKLO_SIGNALS_MONITOR_EN
                21  INTERNAL_GPADC_SIGNALS_MONITOR_EN
                22  PLL_CONTROL_VOLTAGE_MONITOR_EN
                23  DCC_CLOCK_FREQ_MONITOR_EN
                24  RX_IF_SATURATION_MONITOR_EN
                25  RX_SIG_IMG_BAND_MONITORING_EN
                26  RX_MIXER_INPUT_POWER_MONITOR
                31:27   RESERVED
        */
        .enMask = (rlUInt32_t) 0x3FBFDBF,
        /**
         * LDO short circuit monitoring enable. There are no reports for these monitors.
           If there is any fault, the asyncevent RL_RF_AE_ANALOG_FAULT_SB will be sent.
             Bit    Description
             b0     APLL LDO short circuit monitoring
                    0 - disable, 1 - enable
             b1     SYNTH VCO LDO short circuit monitoring
                    0 - disable, 1 - enable
             b2     PA LDO short circuit monitoring
                    0 - disable, 1 - enable
             b31:3 RESERVED
         */
        .ldoScEn = (rlUInt32_t) 0x0
};
/* Temperature sensor monitoring configuration */
rlTempMonConf_t                 gAr1243tempMonCfg = {
    /*
     *          Value    Definition
                0      Report is sent every monitoring
                       period without threshold check
                1      Report is send only upon a failure
                       (after checking for thresholds)
                2      Report is sent every monitoring period with threshold check
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *          The temperatures read from near the sensors near the RF analog modules
                 are compared against a minimum threshold. The comparison result is part
                 of the monitoring report message (Error bit is set if any measurement
                 is outside this (minimum, maximum) range).
                 1 LSB = 1 degree Celsius, signed number
                 Valid range: TBD
                 Recommended value = TBD
     */
    .anaTempThreshMin = (rlInt16_t) -((rlInt16_t)10),
    /*
     *          The temperatures read from near the sensors near the RF analog modules
                 are compared against a maximum threshold. The comparison result is part
                 of the monitoring report message (Error bit is set if any measurement
                 is outside this (minimum, maximum) range).
                 1 LSB = 1 degree Celsius, signed number
                 Valid range: TBD
                 Recommended value = TBD
     */
    .anaTempThreshMax = (rlInt16_t) 60,
    /*
     *          The temperatures read from near the sensor near the digital module are
                  compared against a minimum threshold. The comparison result is part of
                  the monitoring report message (Error bit is set if any measurement is
                  outside this (minimum, maximum) range).
                  1 LSB = 1 degree Celsius, signed number
                  Valid range: TBD
                  Recommended value = TBD
     */
    .digTempThreshMin = (rlInt16_t) -((rlInt16_t)10),
    /*
     *          The temperatures read from near the sensor near the digital module are
                 compared against a maximum threshold. The comparison result is part of
                 the monitoring report message (Error bit is set if any measurement is
                 outside this (minimum, maximum) range).
                 1 LSB = 1 degree Celsius, signed number
                 Valid range: TBD
                 Recommended value = TBD
     */
    .digTempThreshMax = (rlInt16_t) 60,
    /*
     *          The maximum difference across temperatures read from all the enabled
                 sensors is compared against this threshold.The comparison result is part
                 of the monitoring report message(Error bit is set if the measured difference
                 exceeds this field).
                 1 LSB = 1o Celsius, signed number
                 Valid range : TBD
                 Recommended value = TBD
     */
    .tempDiffThresh = (rlUInt16_t) 20,
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
/* RX gain and phase monitoring configuration */
rlRxGainPhaseMonConf_t          gAr1243rxGainPhaseMonCfg = {
    /*
     *          This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *          This field indicates the RF frequencies inside the profile's RF band at which to
                 measure the required parameters. When each bit in this field is set, the
                 measurement at the corresponding RF frequency is enabled w.r.t. the profile's
                 RF band.
                 Bit number  RF frequency                        RF name
                     0       Lowest RF frequency                 RF1
                             in profile's sweep bandwidth
                     1       Center RF frequency in profile's    RF2
                             sweep bandwidth
                     2       Highest RF frequency in             RF3
                             profile's sweep bandwidth
                 The RF name column is mentioned here to set the convention for the
                 purpose of reporting and describing many monitoring packets.
     */
    .rfFreqBitMask = (rlUInt8_t) 7,
    /**
     * Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *          Value     Definition
                0       TX0 is used for generating loopback signal for RX gain measurement
                1       TX1 is used for generating loopback signal for RX gain measurement.
     */
    .txSel = (rlUInt8_t) 0,
    /*
     *          The magnitude of difference between the programmed and measured RX gain for each
                 enabled channel at each enabled RF frequency, is compared against this
                 threshold. The comparison result is part of the monitoring report message
                 (Error bit is set if any measurement is above this threshold). Before the
                 comparison, the measured gains for each RF and RX are adjusted by subtracting
                 the offset given in the RX_GAIN_MISMATCH_OFFSET_VALUE field
                 1 LSB = 0.1 dB
                 Valid range: TBD to 60
                 Recommended value = TBD
     */
    .rxGainAbsThresh = (rlUInt16_t) 20,
    /*
     *          The magnitude of difference between measured RX gains across the enabled channels
                 at each enabled RF frequency is compared against this threshold. The comparison
                 result is part of the monitoring report message (Error bit is set if the
                 measurement is above this threshold). Before the comparison, the measured gains
                 for each RF and RX are adjusted by subtracting the offset given in the
                 RX_GAIN_MISMATCH_OFFSET_VALUE field.
                 1 LSB = 0.1 dB
                 Valid range: TBD to 60
                 Recommended value = TBD
     */
    .rxGainMismatchErrThresh = (rlUInt16_t) 20,
    /*
     *          The magnitude of measured RX gain flatness error, for each enabled channel, is
                 compared against this threshold. The flatness error for a channel is defined as
                 the peak to peak variation across RF frequencies. The comparison result is part
                 of the monitoring report message (Error bit is set if any measurement is above
                 this threshold). Before the comparison, the measured gains for each RF and RX
                 are adjusted by subtracting the offset given in the
                 RX_GAIN_MISMATCH_OFFSET_VALUE field.
                 1 LSB = 0.1 dB
                 Valid range: TBD to 60
                 Recommended value = TBD
                 This flatness check is applicable only if multiple RF Frequencies are enabled,
                 i.e., RF_FREQ_BITMASK has bit numbers 0,1,2 set
     */
    .rxGainFlatnessErrThresh = (rlUInt16_t) 20,
    /*
     *          The magnitude of measured RX phase mismatch across the enabled channels at each
                 enabled RF frequency is compared against this threshold. The comparison result
                 is part of the monitoring report message (Error bit is set if any measurement
                 is above this threshold). Before the comparison, the measured phases for each
                 RF and RX are adjusted by subtracting the offset given in the
                 RX_PHASE_MISMATCH_OFFSET_VALUE field.
                 1 LSB = 360(degree) / 2^16 .
                 Valid range: corresponding to 2 (TBD) to 20 degree.
                 Recommended value = TBD
     */
    .rxGainPhaseMismatchErrThresh = (rlUInt16_t) (30U * 182U),
    /*
     *          The offsets to be subtracted from the measured RX gain for each RX and RF before
                 the relevant threshold comparisons are given here.
                 Byte numbers corresponding to different RX and RF, in this field are
                 here:
                         RF1     RF2     RF3
                 RX0    [1:0]   [9:8]    [17:16]
                 RX1    [3:2]   [11:10]  [19:18]
                 RX2    [5:4]   [13:12]  [21:20]
                 RX3    [7:6]   [15:14]  [23:22]
                 1 LSB = 0.1 dB, signed number
                 Only the entries of enabled RF Frequencies and enabled RX channels are
                 considered.
     */
    .rxGainMismatchOffsetVal = {
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0}
                               },
    /*
     **          The offsets to be subtracted from the measured RX phase for each RX and RF
                 before the relevant threshold comparisons are given here. Byte numbers
                 corresponding to different RX and RF, in this field are here:
                         RF1       RF2       RF3
                 RX0     [1:0]     [9:8]     [17:16]
                 RX1     [3:2]     [11:10]   [19:18]
                 RX2     [5:4]     [13:12]   [21:20]
                 RX3     [7:6]     [15:14]   [23:22]
                 1 LSB = 360(degree) / 2^16 , unsigned number
                 Only the entries of enabled RF Frequencies and enabled RX channels are
                 considered.
     */
    .rxGainPhaseMismatchOffsetVal = {
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0},
                                {(rlInt16_t) 0, (rlInt16_t) 0, (rlInt16_t) 0}
                               },
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt32_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
/* RX noise monitoring configuration */
rlRxNoiseMonConf_t              gAr1243rxNoiseMonCfg = {
    /*
     *          This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *          This field indicates the exact RF frequencies inside the profile's RF band at
                 which to measure the required parameters. When each bit in this field is set,
                 the measurement at the corresponding RF frequency is enabled w.r.t. the
                 profile's RF band.
                 Bit number   RF frequency                    RF name
                     0        Lowest RF frequency in          RF1
                             profile's sweep bandwidth
                     1        Center RF frequency in          RF2
                             profile's sweep bandwidth
                     2        Highest RF frequency in         RF3
                             profile's sweep bandwidth
                 The RF name column is mentioned here to set the convention for the purpose of
                 reporting and describing many monitoring packets.
     */
    .rfFreqBitMask = (rlUInt8_t) 7,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *          Value        Definition
                0          Report is sent every monitoring period without threshold check
                1          Report is send only upon a failure (after checking for thresholds)
                2          Report is sent every monitoring period with threshold check
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt8_t) 0,
    /*
     *          The measured RX input referred noise figure at the enabled RF frequencies, for
                 all channels, is compared against this threshold. The comparison result is part
                 of the monitoring report message (Error bit is set if any measurement is above
                 this threshold).
                 1 LSB = 0.1 dB
                 Valid range: TBD
                 Recommended value = TBD
     */
    .noiseThresh = (rlUInt16_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0,
};
/* RX IF stage monitoring configuration */
rlRxIfStageMonConf_t            gAr1243rxIfStageMonCfg = {
    /*
     *          This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *          Value       Definition
                 0        Report is sent every monitoring period without threshold check
                 1        Report is send only upon a failure (after checking for thresholds)
                 2        Report is sent every monitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt16_t) 0,
    /*
     *          The absolute values of RX IF HPF cutoff percentage frequency errors are
                 compared against the corresponding thresholds given in this field. The
                 comparison results are part of the monitoring report message (Error bit is set
                 if the absolute value of the errors exceeds respective thresholds).
                 1 LSB = 1%, unsigned number
                 Valid range: TBD to 255
                 Recommended value = TBD
     */
    .hpfCutoffErrThresh = (rlUInt16_t) 15,
    /*
     *          The absolute values of RX IF LPF cutoff percentage frequency errors are compared
                 against the corresponding thresholds given in this field. The comparison
                 results are part of the monitoring report message (Error bit is set if the
                 absolute value of the errors exceeds respective thresholds).
                 1 LSB = 1%, unsigned number
                 Valid range: TBD to 255
                 Recommended value = TBD
     */
    .lpfCutoffErrThresh = (rlUInt16_t) 15,
    /*
     *          The absolute deviation of RX IFA Gain from the expected gain for each enabled RX
                 channel is compared against the thresholds given in this field. The comparison
                 result is part of the monitoring report message (Error bit is set if the
                 absolute
                 value of the errors exceeds respective thresholds).
                 1 LSB = 0.1dB, unsigned number
                 Valid range: TBD to 255
                 Recommended value = TBD
     */
    .ifaGainErrThresh = (rlUInt16_t) 100,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
rlTxPowMonConf_t gAr1243tx0PowrMonCfg = {
    /*
     *     This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *     This field indicates the exact RF frequencies inside the profile's RF band at
                 which to measure the required parameters. When each bit in this field is set,
                 the measurement at the corresponding RF frequency is enabled w.r.t. the
                 profile's RF band.

                 Bit number      RF frequency                            RF
                     0           Lowest RF frequency in profile's        RF1
                                 sweep bandwidth
                     1           Center RF frequency in profile's        RF2
                                 sweep bandwidth
                     2           Highest RF frequency in profile's       RF3
                                 sweep bandwidth
                 The RF Name column is mentioned here to set the convention for the purpose
                 of reporting and describing many monitoring packets.
     */
    .rfFreqBitMask = (rlUInt8_t) 7,
    /*
     *     Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*!< Value    Definition
            0     Report is sent every monitoring period without threshold check
            1     Report is send only upon a failure (after checking for thresholds)
            2     Report is sent everymonitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *     Reserved for Future use
     */
    .reserved1 = (rlUInt8_t) 0,
    /*
     *     The magnitude of difference between the programmed and measured TX power for
                 each enabled channel at each enabled RF frequency, is compared against this
                 threshold. The comparison result is part of the monitoring report message(Error
                 bit is set if any measurement is above this threshold).
                 1 LSB = 0.1 dBm
                 Valid range: TBD to 60
                 Recommended value = TBD
     */
    .txPowAbsErrThresh = (rlUInt16_t) 30,
    /*
     *     The magnitude of measured TX power flatness error, for each enabled channel, is
                 compared against this threshold. The flatness error for a channel is defined as
                 the peak to peak variation across RF frequencies. The comparison result is part
                 of the monitoring report message(Error bit is set if any measurement is above
                 this threshold).
                 1 LSB = 0.1 dB
                 Valid range: TBD to 60
                 Recommended value = TBD
                 This flatness check is applicable only if multiple RF Frequencies are enabled.
     */
    .txPowFlatnessErrThresh = (rlUInt16_t) 30,
    /*
     *     Reserved for Future use
     */
    .reserved2 = (rlUInt16_t) 0,
    /*
     *     Reserved for Future use
     */
    .reserved3 = (rlUInt32_t) 0
};
rlTxPowMonConf_t gAr1243tx1PowrMonCfg = {
    /*
     *     This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *     This field indicates the exact RF frequencies inside the profile's RF band at
                 which to measure the required parameters. When each bit in this field is set,
                 the measurement at the corresponding RF frequency is enabled w.r.t. the
                 profile's RF band.

                 Bit number      RF frequency                            RF
                     0           Lowest RF frequency in profile's        RF1
                                 sweep bandwidth
                     1           Center RF frequency in profile's        RF2
                                 sweep bandwidth
                     2           Highest RF frequency in profile's       RF3
                                 sweep bandwidth
                 The RF Name column is mentioned here to set the convention for the purpose
                 of reporting and describing many monitoring packets.
     */
    .rfFreqBitMask = (rlUInt8_t) 7,
    /*
     *     Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*!< Value    Definition
            0     Report is sent every monitoring period without threshold check
            1     Report is send only upon a failure (after checking for thresholds)
            2     Report is sent everymonitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *     Reserved for Future use
     */
    .reserved1 = (rlUInt8_t) 0,
    /*
     *     The magnitude of difference between the programmed and measured TX power for
                 each enabled channel at each enabled RF frequency, is compared against this
                 threshold. The comparison result is part of the monitoring report message(Error
                 bit is set if any measurement is above this threshold).
                 1 LSB = 0.1 dBm
                 Valid range: TBD to 60
                 Recommended value = TBD
     */
    .txPowAbsErrThresh = (rlUInt16_t) 30,
    /*
     *     The magnitude of measured TX power flatness error, for each enabled channel, is
                 compared against this threshold. The flatness error for a channel is defined as
                 the peak to peak variation across RF frequencies. The comparison result is part
                 of the monitoring report message(Error bit is set if any measurement is above
                 this threshold).
                 1 LSB = 0.1 dB
                 Valid range: TBD to 60
                 Recommended value = TBD
                 This flatness check is applicable only if multiple RF Frequencies are enabled.
     */
    .txPowFlatnessErrThresh = (rlUInt16_t) 30,
    /*
     *     Reserved for Future use
     */
    .reserved2 = (rlUInt16_t) 0,
    /*
     *     Reserved for Future use
     */
    .reserved3 = (rlUInt32_t) 0
};
/* TX power monitoring configuration */
rlAllTxPowMonConf_t             gAr1243allTxPowMonCfg = {
    /*
     * Power Monitoring Configuration for Tx0
     */
    .tx0PowrMonCfg = (rlTxPowMonConf_t *)&gAr1243tx0PowrMonCfg,
    /*
     * Power Monitoring Configuration for Tx1
     */
    .tx1PowrMonCfg = (rlTxPowMonConf_t *)NULL,
    /*
     * Power Monitoring Configuration for Tx2
     */
    .tx2PowrMonCfg = (rlTxPowMonConf_t *) NULL
};
rlTxBallbreakMonConf_t gAr1243tx0BallBreakMonCfg = {
    /*
     *          Value    Definition
                0      Report is sent every monitoring period without threshold check
                1      Report is send only upon a failure (after checking for thresholds)
                2      Report is sent every monitoring.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*   The TX reflection coefficient's magnitude for each enabled channel is compared against
         the threshold given here. The comparison result is part of the monitoring report
         message (Error bit is set if the measurement is lower than this threshold, with the
         units of both quantities being the same).
         1 LSB = 0.1 dB, signed number
         Valid range: -90 (TBD) to -250
         Recommended value = TBD
     */
    .txReflCoeffMagThresh = (rlInt16_t) -((rlInt16_t)40),
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
rlTxBallbreakMonConf_t gAr1243tx1BallBreakMonCfg = {
/*
     *          Value    Definition
                0      Report is sent every monitoring period without threshold check
                1      Report is send only upon a failure (after checking for thresholds)
                2      Report is sent every monitoring.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*   The TX reflection coefficient's magnitude for each enabled channel is compared against
         the threshold given here. The comparison result is part of the monitoring report
         message (Error bit is set if the measurement is lower than this threshold, with the
         units of both quantities being the same).
         1 LSB = 0.1 dB, signed number
         Valid range: -90 (TBD) to -250
         Recommended value = TBD
     */
    .txReflCoeffMagThresh = (rlInt16_t) -((rlInt16_t)40),
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
/* TX ballbreak monitoring configuration */
rlAllTxBallBreakMonCfg_t        gAr1243allTxBallBreakMonCfg = {
    /*
     * Tx ballbreak monitoring config for Tx0
     */
    .tx0BallBrkMonCfg = (rlTxBallbreakMonConf_t *) &gAr1243tx0BallBreakMonCfg,
    /*
     * Tx ballbreak monitoring config for Tx1
     */
    .tx1BallBrkMonCfg = (rlTxBallbreakMonConf_t *) NULL,
    /*
     * Tx ballbreak monitoring config for Tx2.
     */
    .tx2BallBrkMonCfg = (rlTxBallbreakMonConf_t *) NULL
};
/* TX gain and phase mismatch monitoring configuration */
rlTxGainPhaseMismatchMonConf_t  gAr1243txGainPhaseMismatchMonCfg = {
    /*
     *       This field indicates the Profile Index for which this monitoring configuration
                 applies. The TX settings corresponding to this profile index are used during
                 the monitoring. The RX gain used in this measurement may differ from the given
                 profile's RX gain.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *       This field indicates the exact RF frequencies inside the profile's RF band at
                 which to measure the required parameters. When each bit in this field is set,
                 the measurement at the corresponding RF frequency is enabled wrt the profile's
                 RF band.
                 Bit         RF frequency                            RF
                 number                                              name
                 0           Lowest RF frequency in profile's        RF1
                             sweep bandwidth
                 1           Center RF frequency in profile's        RF2
                             sweep bandwidth
                 2           Highest RF frequency in profile's       RF3
                             sweep bandwidth
                 The RF Name column is mentioned here to set the convention for the purpose of
                 reporting and describing many monitoring packets.
     */
    .rfFreqBitMask = (rlUInt8_t) 7,
    /*
     *       This field indicates the TX channels that should be compared for gain and phase
                 balance. Setting the corresponding bit to 1 enables that channel for imbalance
                 measurement
                 Bit number     TX Channel
                     0          TX0
                     1          TX1
                     2          TX2
     */
    .txEn = (rlUInt8_t) 1,
    /*
     *       This field indicates the RX channels that should be enabled for TX to RX loopback
               measurement. Setting the corresponding bit to 1 enables that channel for imbalance
               measurement.
               Bit   RX Channel
                0    RX0
                1    RX1
                2    RX2
                3    RX3
     */
    .rxEn = (rlUInt8_t) 0xF,
    /*
     *       Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    .reserved1 = (rlUInt8_t) 0,
    /*
     *       The magnitude of difference between measured TX powers across the enabled
                 channels at each enabled RF frequency is compared against this threshold. The
                 comparison result is part of the monitoring report message(Error bit is set if
                 the measurement is above this threshold). Before the comparison, the measured
                 gains for each RF and RX are adjusted by subtracting the offset given in the
                 TX_GAIN_MISMATCH_OFFSET_VALUE field.
                 1 LSB = 0.1dB, signed number
                 Valid range: TBD to 60
                 Recommended value = TBD
     */
    .txGainMismatchThresh = (rlInt16_t) 50,
    /*
     *       The magnitude of measured TX phase mismatch across the enabled channels at each
                 enabled RF frequency is compared against this threshold. The comparison result
                 is part of the monitoring report message (Error bit is set if any measurement
                 is above this threshold). Before the comparison, the measured gains for each RF
                 and RX are adjusted by subtracting the offset given in the
                 TX_PHASE_MISMATCH_OFFSET_VALUE field.
                 1 LSB = 360(degree)/ 2^16 , signed number
                 Valid range: corresponding to 2 (TBD) to 20 degree.
                 Recommended value = TBD
     */
    .txPhaseMismatchThresh = (rlInt16_t) (30U * 182U),
    /*
     *       The offsets to be subtracted from the measured TX gain for each TX and RF before
                 the relevant threshold comparisons are given here. Byte numbers corresponding
                 to different RX and RF, in this field are here:
                         RF1      RF2        RF3
                TX0     [1:0]    [7:6]      [13:12]
                TX1     [3:2]    [9:8]      [15:14]
                TX2     [5:4]    [11:10]    [17:16]
                 1 LSB = 0.1 dB
                 Only the entries of enabled RF Frequencies and enabled TX
                 channels are considered.
     */
    .txGainMismatchOffsetVal = {{(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0},
                                {(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0},
                                {(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0}},
    /*
     *       The offsets to be subtracted from the measured TX phase for each TX and RF before
                 the
                 relevant threshold comparisons are given here. Byte numbers corresponding to
                 different RX and RF, in this field are here:
                         RF1      RF2      RF3
                 TX0     [1:0]    [7:6]    [13:12]
                 TX1     [3:2]    [9:8]    [15:14]
                 TX2     [5:4]    [11:10]  [17:16]
                 1 LSB = 360(degree)/216.
                 Only the entries of enabled RF Frequencies and enabled TX channels
                 are considered.
     */
    .txPhaseMismatchOffsetVal = {{(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0},
                                {(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0},
                                {(rlUInt16_t) 0, (rlUInt16_t) 0, (rlUInt16_t) 0}},
    /*
     *       Reserved for Future use
     */
    .reserved1 = (rlUInt16_t) 0,
    /*
     *       Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
rlTxBpmMonConf_t gAr1243tx0BpmMonCfg = {
    /*
     *          This field indicates the Profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /**
     * This field indicates the phase shifter monitoring configuration.
       Bit     Definition
       5:0     Phase shifter monitoring increment value
               1 LSB = 5.625 degree
       6       Phase shifter monitoring auto increment enabled. On each FTTI phase shift
               value increment by mentioned increment value at bit 0:5
       7       Phase shifter monitoring enabled
     */
    .phaseShifterMonCnfg = (rlUInt8_t) 0,
    /**
     * Phase1 of the phase shifter of TX which needs to be monitored
       1 LSB = 5.625 degree
     */
    .phaseShifterMon1 = (rlUInt8_t) 0,
    /**
     * Phase2 of the phase shifter of TX which needs to be monitored
       1 LSB = 5.625 degree
     */
    .phaseShifterMon2 = (rlUInt8_t) 0,
    /*
     *           Value      Definition
                 0       Report is sent every monitoring period without threshold check
                 1       Report is send only upon a failure after checking for thresholds)
                 2       Report is sent every monitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *           This field indicates the RX channels that should be enabled for TX to RX loopback
               measurement. Setting the corresponding bit to 1 enables that channel for imbalance
               measurement.
               Bit   RX Channel
                0    RX0
                1    RX1
                2    RX2
                3    RX3
     */
    .rxEn = (rlUInt8_t) 0xF,
    /*
     *           The deviation of the TX output phase difference between the two BPM settings from
                 the ideal 180o is compared against the threshold given here. The comparison
                 result is part of the monitoring report message (Error bit is set if the
                 measurement is lower than this threshold, with the units of both quantities
                 being the same).
                 1 LSB = 360(degree) /2^16.
                 Valid range: TBD
                 Recommended value = TBD
     */
    .txBpmPhaseErrThresh = (rlUInt16_t) 0x1555,
    /*
     *           The deviation of the TX output amplitude difference between the two BPM settings
                 is compared against the threshold given here. The comparison result is part of
                 the monitoring report message (Error bit is set if the measurement is lower
                 than this threshold, with the units of both quantities being the same).
                 1 LSB = 0.1 dB
                 Valid range: TBD
                 Recommended value = TBD
     */
    .txBpmAmplErrThresh = (rlUInt16_t) 30,
    /**
     * Maximum threshold for the difference in the 2 configured phase shift
     * values 1 LSB = 5.625 degree
     */
    .phaseShifterThreshMax = (rlUInt16_t) 10,
    /**
    * Minimum threshold for the difference in the 2 configured phase shift
    * values 1 LSB = 5.625 degree
    */
    .phaseShifterThreshMin = (rlUInt16_t ) 10,
    /**
     * Reserved for Future use
     */
    .reserved = (rlUInt16_t) 0
};
/* TX BPM monitoring configuration */
rlAllTxBpmMonConf_t             gAr1243allTxBpmMonCfg = {
    /*
     * Tx-0 BPM monitoring config
     */
    .tx0BpmMonCfg = (rlTxBpmMonConf_t *) &gAr1243tx0BpmMonCfg,
    /*
     * Tx-1 BPM monitoring config
     */
    .tx1BpmMonCfg = (rlTxBpmMonConf_t *) NULL,
    /*
     * Tx-2 BPM monitoring config
     */
    .tx2BpmMonCfg = (rlTxBpmMonConf_t *) NULL
};
/* Synthesizer frequency monitoring configuration */
rlSynthFreqMonConf_t            gAr1243synthFreqMonCfg = {
    /*
     *          This field indicates the Profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *          Value    Definition
                 0     Report is sent every monitoring period without threshold check
                 1     Report is send only upon a failure (after checking for thresholds)
                 2     Report is sent every monitoring period with threshold check
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          During the chirp, the error of the measured instantaneous chirp frequency w.r.t.
                 the desired value is continuously compared against this threshold.
                 The comparison result is part of the monitoring report message (Error bit is
                 set if the measurement is above this threshold, ever during the previous
                 monitoring period).
                 1 LSB = 1 kHz
                 Valid range: TBD
                 Recommended value = TBD
     */
    .freqErrThresh = (rlUInt16_t) 4000,
    /*
     *          This field determines when the monitoring starts in each
                 chirp relative to the start of the ramp.
                 1 LSB = 0.2us, signed number
                 Valid range: -25us to 25us
     */
    .monStartTime = (rlInt8_t) 10,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    .reserved1 = (rlUInt16_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
    /*
     *          Reserved for Future use
     */
};
/* External analog signals monitoring configuration */
rlExtAnaSignalsMonConf_t        gAr1243extAnaSigMonCfg = {
    /*
     *          Value    Definition
               0       Report is sent every monitoring period without threshold check
               1       Report is send only upon a failure (after checking for thresholds)
               2       Report is sent every monitoring period with threshold check
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *          This field indicates the sets of externally fed DC signals which are to be
                 monitored using GPADC. When each bit in this field is set, the corresponding
                 signal is monitored. The monitored signals are compared against programmed
                 limits. The comparison result is part of the monitoring report message.
                 Bit Location  SIGNAL
                     0         ANALOGTEST1
                     1         ANALOGTEST2
                     2         ANALOGTEST3
                     3         ANALOGTEST4
                     4         ANAMUX
                     5         VSENSE
                     Others    RESERVED
     */
    .signalInpEnables = (rlUInt8_t) 0,
    /*
     *          This field indicates the sets of externally fed DC signals which are to be
                 buffered before being fed to the GPADC. When each bit in this field is set, the
                 corresponding signal is buffered before the GPADC. The monitored signals are
                 compared against programmed limits. The comparison result is part of the
                 monitoring report message.
                 Bit      SIGNAL
                 0        ANALOGTEST1
                 1        ANALOGTEST2
                 2        ANALOGTEST3
                 3        ANALOGTEST4
                 4        ANAMUX
                 Others   RESERVED
     */
    .signalBuffEnables = (rlUInt8_t) 0,
    /*
     *          After connecting an external signal to the GPADC, the amount of time to wait for
                 it to settle before taking GPADC samples is programmed in this field. For each
                 signal, after that settling time, GPADC measurements take place for 6.4us
                 (averaging 4 samples of the GPADC output).The byte locations of the settling
                 times for each signal are tabulated here:
                 Byte Location   SIGNAL
                     0           ANALOGTEST1
                     1           ANALOGTEST2
                     2           ANALOGTEST3
                     3           ANALOGTEST4
                     4           ANAMUX
                     5           VSENSE
                     1 LSB = 0.8us
                 Valid range: 0 to 12us
                 Valid programming condition: all the signals that are enabled
                 should take a total of <100us, including the programmed settling
                 times and a fixed 6.4us of measurement time per enabled signal.
     */
    .signalSettlingTime = {(rlUInt8_t) 0,
                           (rlUInt8_t) 0,
                           (rlUInt8_t) 0,
                           (rlUInt8_t) 0,
                           (rlUInt8_t) 0,
                           (rlUInt8_t) 0
                           },
    /*
     *          The external DC signals measured on GPADC are compared against these minimum and
                 maximum thresholds. The comparison result is part of the monitoring report
                 message (Error bit is set if any measurement is outside this (minimum, maximum)
                 range).
                 Byte Location  Threshold     SIGNAL
                     0           Minimum      ANALOGTEST1
                     1           Minimum      ANALOGTEST2
                     2           Minimum      ANALOGTEST3
                     3           Minimum      ANALOGTEST4
                     4           Minimum      ANAMUX
                     5           Minimum      VSENSE
                     6           Maximum      ANALOGTEST1
                     7           Maximum      ANALOGTEST2
                     8           Maximum      ANALOGTEST3
                     9           Maximum      ANALOGTEST4
                     10          Maximum      ANAMUX
                     11          Maximum      VSENSE
                 1 LSB = 1.8V / 256
                 Valid range: 0 to 255
     */
    .signalThresh = {(rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0,
                     (rlUInt8_t) 0
                    },
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt16_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved3 = (rlUInt32_t) 0
};
rlTxIntAnaSignalsMonConf_t gAr1243tx0IntAnaSigMonCfg = {
    /*
     *        The RF analog settings corresponding to this profile are used for monitoring the
                 enabled signals, using test chirps (static frequency, at the center of the
                 profile's RF frequency band).
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *        Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure(after checking for thresholds)
                 2    Report is sent every monitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *        Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *        Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
rlTxIntAnaSignalsMonConf_t gAr1243tx1IntAnaSigMonCfg = {
    /*
     *        The RF analog settings corresponding to this profile are used for monitoring the
                 enabled signals, using test chirps (static frequency, at the center of the
                 profile's RF frequency band).
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *        Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure(after checking for thresholds)
                 2    Report is sent every monitoring period with threshold check.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *        Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *        Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
/* Internal signals in the TX path monitoring configuration */
rlAllTxIntAnaSignalsMonConf_t   gAr1243allTxIntAnaSigMonCfg = {
    /*
     * Internal signals in the Tx-0 path monitoring config
     */
    .tx0IntAnaSgnlMonCfg = (rlTxIntAnaSignalsMonConf_t *)&gAr1243tx0IntAnaSigMonCfg,
    /*
     * Internal signals in the Tx-1 path monitoring config
     */
    .tx1IntAnaSgnlMonCfg = (rlTxIntAnaSignalsMonConf_t *)NULL,
    /*
     * Internal signals in the Tx-2 path monitoring config
     */
    .tx2IntAnaSgnlMonCfg = (rlTxIntAnaSignalsMonConf_t *)NULL
};
/* Internal Analog signals monitoring configuration */
rlRxIntAnaSignalsMonConf_t      gAr1243rxIntAnaSigMonCfg = {
    /*
      *         The RF analog settings corresponding to this profile are used for monitoring the
                 enabled signals, using test chirps(static frequency,at the center of the
                 profile's RF frequency band).
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *         Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure (after checking internal thresholds)
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *         Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
/* Internal signals for PM, CLK and LO monitoring configuration */
rlPmClkLoIntAnaSignalsMonConf_t gAr1243pmClkLoIntAnaSigMonCfg = {
    /*
     *           The RF analog settings corresponding to this profile are used for monitoring the
                 enabled signals, using test chirps(static frequency, at the center of the
                 profile's RF frequency band).
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *          Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure (after checking internal thresholds)
     */
    .reportMode = (rlUInt8_t) 2,
    /**
     * Value   Definition \n
         0    20GHz sync monitoring disabled \n
         1    SYNC_IN monitoring enabled \n
         2    SYNC_OUT monitoring enabled \n
         3    SYNC_CLKOUT monitoring enabled \n
     */
    .sync20GSigSel = (rlUInt8_t) 0,
    /**
     * Minimum threshold for 20GHz monitoring\n
       1 LSB = 1 dBm
     */
    .sync20GMinThresh = (rlUInt8_t) 0,
    /**
     * Maximum threshold for 20GHz monitoring\n
       1 LSB = 1 dBm
     */
    .sync20GMaxThresh = (rlUInt8_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *          Reserved for Future use
     */
    .reserved1 = (rlUInt16_t) 0
};
/* Internal signals for GPADC monitoring configuration */
rlGpadcIntAnaSignalsMonConf_t   gAr1243gpadcIntAnaSigMonCfg = {
    /*
     *         Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure (after checking internal thresholds)
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     *         Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved1 = (rlUInt16_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved2 = (rlUInt32_t) 0
};
/* Internal signals for PLL control voltage monitoring configuration */
rlPllContrVoltMonConf_t         gAr1243pllControlVoltMonCfg = {
    /*
     * Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure (after checking for thresholds)
                 2    Report is sent every monitoring period with threshold chec.
     */
    .reportMode = (rlUInt8_t) 2,
    /*
     * Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     * This field indicates the sets of signals which are to be monitored. When each bit
                in this field is set, the corresponding signal set is monitored using test
                chirps. Rest of the RF analog may not be ON during these test chirps. The APLL
                VCO control voltage can be monitored. The Synthesizer VCO control voltage for
                both VCO1 and VCO2 can be monitored, while operating at their respective
                minimum and maximum frequencies, and their respective VCO slope (Hz/V) can be
                monitored if both frequencies are enabled for that VCO. The monitored signals
                are compared against internally chosen valid limits. The comparison results are
                part of the monitoring
                report message.
                        Bit Location   SIGNAL
                            0          APLL_VCTRL
                            1          SYNTH_VCO1_VCTRL
                            2          SYNTH_VCO2_VCTRL
                          15:3         RESERVED
                The synthesizer VCO extreme frequencies are:
                Synthesizer VCO      Frequency Limits (Min, Max)
                    VCO1             (76GHz, 78GHz)
                    VCO2             (77GHz, 81GHz)
                Synthesizer measurements are done with TX switched off to avoid emissions.
                For the failure reporting, the internally chosen valid limits are (tentative):
                for the measured control voltage levels: 0.15V to 1.25V;
                for the synthesizer VCO slope: -20 to +20% of 1.1GHz/V for VCO2 and 0.55GHz/V
                for VCO1.
     */
    .signalEnables = (rlUInt16_t) 7,
    /*
     * Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
/* Internal signals for DCC based clock monitoring configuration */
rlDualClkCompMonConf_t          gAr1243dualClkCompMonCfg = {
    /*
     *         Value   Definition
                 0    Report is sent every monitoring period without threshold check
                 1    Report is send only upon a failure (after checking internal thresholds)
     */
    .reportMode = (rlUInt8_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved0 = (rlUInt8_t) 0,
    /*
     *         This field indicates which pairs of clocks to monitor. When a bit in the field is
                 set to 1, the firmware monitors the corresponding clock pair by deploying the
                 hardware's Dual Clock Comparator in the corresponding DCC mode.
                 Bit  CLOCK PAIR
                 0    0
                 1    1
                 2    2
                 3    3
                 4    4
                 5    5
                 15:6 RESERVED
                 The comparison results are part of the monitoring report message. The
                 definition of the clock pairs and their error thresholds for failure reporting
                 are given in the table below the message definition.
     */
    .dccPairEnables = (rlUInt16_t) 63,
    /*
     *         Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
/* RX saturation monitoring configuration */
rlRxSatMonConf_t                gAr1243rxSatMonCfg = {
    /*
     *         This field indicates the profile Index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *         01 => Enable only the ADC saturation monitor
              10 => Enable only the IFA1 saturation monitor
              11 => Enable both the ADC and IFA1 saturation monitors
     */
    .satMonSel = (rlUInt8_t) 3,
    /*
     *         Reserved for Future use
     */
    .reserved0 = (rlUInt16_t) 0,
    /*
     *         It specifies the duration of each (primary) time slice.
                 1 LSB = 0.16us.
                 Valid range: 4 to floor(ADC sampling time us/0.16 us)
                 NOTES: The minimum allowed duration of each (primary) time slice is
                 4 LSBs = 0.64us. Also, the maximum number of (primary) time slices that will
                 be monitored in a chirp is 64 so the recommendation is to set this value to
                 correspond to (ADC sampling time / 64). If the slice is smaller, such that the
                 ADC sampling time is longer than 64 primary slices,some regions of the valid
                 duration of a chirp may go un-monitored.
     */
    .primarySliceDuration = (rlUInt16_t) 5,
    /*
     *         Number of (primary + secondary) time slices to monitor.
                 Valid range: 1 to 127
                 NOTE: Together with SAT_MON_PRIMARY_TIME_SLICE_DURATION, this determines the
                 full duration of the ADC valid time that gets covered by the monitor
     */
    .numSlices = (rlUInt16_t) 63,
    /*
     *         This field is applicable only for SAT_MON_MODE = 0 Masks RX channels used for
                 monitoring. In every slice, saturation counts for all unmasked channels are
                 added together, and the total is capped to 127. The 8 bits are mapped
                 (MSB->LSB) to:
                 [RX3Q, RX2Q, RX1Q, RX0Q, RX3I, RX2I, RX1I, RX0I]
                 00000000 => All channels unmasked
                 11111111 => All channels masked.
     */
    .rxChannelMask = (rlUInt8_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved1 = (rlUInt8_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved2 = (rlUInt16_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved3 = (rlUInt32_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved4 = (rlUInt32_t) 0
};
/* Signal and image band energy monitoring configuration */
rlSigImgMonConf_t               gAr1243sigImgMonCfg = {
    /*
     *         This field indicates the profile index for which this configuration applies.
     */
    .profileIndx = (rlUInt8_t) 0,
    /*
     *         Number of (primary + secondary) slices to monitor Valid range: 1 to 127.
     */
    .numSlices = (rlUInt8_t) 63,
    /*
     *         This field specifies the number of samples constituting each time slice. The
                 minimum allowed value for this parameter is 4.
                 Valid range: 4 to NUM_ADC_SAMPLES
                 NOTE: The maximum number of (primary) time slices that will be monitored in a
                 chirp is 64, so our recommendation is that this value should at least equal
                 (NUM_ADC_SAMPLES / 64). If the slice is smaller, such that the number of ADC
                 samples per chirp is larger than 64 primary slices, some regions of the valid
                 duration of a chirp may go un-monitored.
     */
    .timeSliceNumSamples = (rlUInt16_t) 8,
    /*
     *         Reserved for Future use
     */
    .reserved0 = (rlUInt32_t) 0,
    /*
     *         Reserved for Future use
     */
    .reserved1 = (rlUInt32_t) 0
};
rlRfCalMonFreqLimitConf_t       gAr1243calMonFreqLimitCfg = {
    .freqLimitLow     = (rlUInt16_t) 760,
    .freqLimitHigh    = (rlUInt16_t) 810,
    .reserved0        = (rlUInt32_t) 0x0,
    .reserved1        = (rlUInt32_t) 0x0
};
rlRunTimeCalibConf_t            gAr1243runTimeCalCfg = {
    .oneTimeCalibEnMask     = (rlUInt32_t) 0x0,
    .periodicCalibEnMask    = (rlUInt32_t) 0x610,
    .calibPeriodicity       = (rlUInt32_t) 1,
    .reportEn               = (rlUInt8_t) 1,
    .reserved0              = (rlUInt8_t) 0,
    .txPowerCalMode         = (rlUInt16_t)0x0,
    .reserved1              = (rlUInt32_t) 0x0
};
rlCalibrationData_t gAr1243calibDataStoreRestore;

rlRfCalMonTimeUntConf_t gAr1243monTimeUnitCfg =
{
    /**
     * Defines the basic time unit, in terms of which calibration and/or
       monitoring periodicities are to be defined.
       If any monitoring functions are desired and enabled, the monitoring
       infrastructure automatically inherits this time unit as the period
       over which the various monitors are cyclically executed, so this should
       be set to the desired FTTI. For calibrations, a separate
       rlRunTimeCalibConf.calibPeriodicity can be specified, as a multiple
       of this time unit, in rlRfRunTimeCalibConfig
       1 LSB = Duration of one frame.
     */
    .calibMonTimeUnit = (rlUInt16_t) 150,
    /**
     * Applicable only for 12xx devices, default value = 1
     */
    .numOfCascadeDev = (rlUInt8_t) 1,
    /**
     * Applicable only for 12xx devices, default value = 1
     */
    .devId = (rlUInt8_t) 1,
    /**
     * Reserved for Future use
     */
    .reserved = (rlUInt32_t) 0
};

Bsp_Ar12xxMonConfigObj gAr1243RadarMonConfig = {
    &gAr1243monAnaEnable,
    &gAr1243monTimeUnitCfg,
    &gAr1243tempMonCfg,
    &gAr1243rxGainPhaseMonCfg,
    &gAr1243rxNoiseMonCfg,
    &gAr1243rxIfStageMonCfg,
    &gAr1243allTxPowMonCfg,
    &gAr1243allTxBallBreakMonCfg,
    &gAr1243txGainPhaseMismatchMonCfg,
    &gAr1243allTxBpmMonCfg,
    &gAr1243synthFreqMonCfg,
    &gAr1243extAnaSigMonCfg,
    &gAr1243allTxIntAnaSigMonCfg,
    &gAr1243rxIntAnaSigMonCfg,
    &gAr1243pmClkLoIntAnaSigMonCfg,
    &gAr1243gpadcIntAnaSigMonCfg,
    &gAr1243pllControlVoltMonCfg,
    &gAr1243dualClkCompMonCfg,
    &gAr1243rxSatMonCfg,
    &gAr1243sigImgMonCfg,
    &gAr1243calMonFreqLimitCfg,
    &gAr1243runTimeCalCfg,
    &gAr1243calibDataStoreRestore,
    NULL
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */
