/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CHAINS_RADAR_NUM_RX_ANTENNA (4U)
#define CHAINS_RADAR_NUM_TX_ANTENNA (2U)

/** \brief Number of antennas Rx times tx*/
#define CHAINS_RADAR_NUM_ANTENNA (CHAINS_RADAR_NUM_RX_ANTENNA * \
                                    CHAINS_RADAR_NUM_TX_ANTENNA)

/** \brief Radar Sensor Height */
#define AR1243_RADAR_HEIGHT   (128U)

/** \brief Radar Sensor width */
#define AR1243_PROFILE1_RADAR_WIDTH   (128U)

/** \brief Radar Sensor width */
#define AR1243_PROFILE2_RADAR_WIDTH   (512U)

/** \brief Name of the configuration used */
#define CHAINS_AR1243_CONFIG_NAME "CHAINS_CAPT_FFT_DISP"

/** \brief CSI Data Rate for data transfer from AR12xx
 *         Valid Values are
 *         150 (for 150 Mbps)
 *         300 (for 300 Mbps)
 *         400 (for 400 Mbps)
 *         450 (for 450 Mbps)
 *         600 (for 600 Mbps)
 */
#define CHAINS_AR1243_CSI_DATA_RATE (300U)
#define CHAINS_UB960_CSI_DATA_RATE (800U)

#if (CHAINS_AR1243_CSI_DATA_RATE == (150U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CHAINS_AR1243_CSI_DATA_RATE_VALUE (6)       /* 150 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CHAINS_AR1243_DDR_HSI_CLK         (0xB)     /* 150 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CHAINS_AR1243_ISS_CSI_CLK         (75U)     /* 150 Mbps */
#elif (CHAINS_AR1243_CSI_DATA_RATE == (300U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CHAINS_AR1243_CSI_DATA_RATE_VALUE (4)       /* 300 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CHAINS_AR1243_DDR_HSI_CLK         (0xA)     /* 300 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CHAINS_AR1243_ISS_CSI_CLK         (150U)    /* 300 Mbps */
#elif (CHAINS_AR1243_CSI_DATA_RATE == (400U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CHAINS_AR1243_CSI_DATA_RATE_VALUE (3)       /* 400 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CHAINS_AR1243_DDR_HSI_CLK         (0x1)     /* 400 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CHAINS_AR1243_ISS_CSI_CLK         (200U)    /* 400 Mbps */
#elif (CHAINS_AR1243_CSI_DATA_RATE == (450U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CHAINS_AR1243_CSI_DATA_RATE_VALUE (2)       /* 450 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CHAINS_AR1243_DDR_HSI_CLK         (0x5)     /* 450 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CHAINS_AR1243_ISS_CSI_CLK         (225U)    /* 450 Mbps */
#elif (CHAINS_AR1243_CSI_DATA_RATE == (600U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CHAINS_AR1243_CSI_DATA_RATE_VALUE (1)       /* 600 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CHAINS_AR1243_DDR_HSI_CLK         (0x9)     /* 600 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CHAINS_AR1243_ISS_CSI_CLK         (300U)    /* 600 Mbps */
#else
    #warn "CHAINS_AR1243: No valid data rate specified!!"
#endif

/** \brief ADC Data Format for AR12
 *         Valid Values are
 *         12  (for 12 bit ADC)
 *         14  (for 14 bit ADC)
 *         16  (for 16 bit ADC)
 */
#define CHAINS_AR1243_ADC_DATA_FORMAT (16U)

#if (CHAINS_AR1243_ADC_DATA_FORMAT == (12U))
    /** \brief AR12 data format value set in the configuration */
    #define CHAINS_AR1243_DATA_FORMAT_CONFIG (RL_ADC_DATA_12_BIT)       /* 12 bit */
#elif (CHAINS_AR1243_ADC_DATA_FORMAT == (14U))
    /** \brief AR12 data format value set in the configuration */
    #define CHAINS_AR1243_DATA_FORMAT_CONFIG (RL_ADC_DATA_14_BIT)       /* 14 bit */
#elif (CHAINS_AR1243_ADC_DATA_FORMAT == (16U))
    /** \brief AR12 data format value set in the configuration */
    #define CHAINS_AR1243_DATA_FORMAT_CONFIG (RL_ADC_DATA_16_BIT)       /* 16 bit */
#else
    #warn "CHAINS_AR1243: No valid ADC data format specified!!"
#endif

/** \brief Advanced Frame Configurations */
#define CHAINS_AR1243_NUM_SUBFRAMES    (2U)
#define CHAINS_AR1243_NUM_BURSTS       (1U)
#define CHAINS_AR1243_NUM_BURST_LOOPS  (1U)

/* ========================================================================== */
/*                           Globals                                          */
/* ========================================================================== */

static char gChains_numRadarsMenu[] = {
    "\r\n "
    "\r\n ======================="
    "\r\n Select Number of Radars"
    "\r\n ======================="
    "\r\n "
    "\r\n Enter Number of Radars are connected: (1-4)"
    "\r\n "
};

/* When Advanced frame configuration is set this is ignored */
static rlFrameCfg_t   gAr1243FrmArgs =
{
    .chirpStartIdx = (rlUInt16_t) 0,
    .chirpEndIdx   = (rlUInt16_t) CHAINS_RADAR_NUM_TX_ANTENNA - (rlUInt16_t)1,
    .numLoops      = (rlUInt16_t) AR1243_RADAR_HEIGHT,
    .numFrames     = (rlUInt16_t) 0,
    /* profileCfgArgs[1].numAdcSamples * 2 - 512 * 2*/
    .numAdcSamples     = (rlUInt16_t) AR1243_PROFILE1_RADAR_WIDTH * (rlUInt16_t)2,
    .framePeriodicity  = (rlUInt32_t) CHAINS_AR1243_TIME_MS_TO_5NS(66U), /* 33 ms / 30 FPS, 20 ms / 50fps */
    .triggerSelect     = (rlUInt16_t) RL_FRAMESTRT_API_TRIGGER,
    .reserved0         = (rlUInt32_t) 0,
    .reserved1         = (rlUInt32_t) 0,
    .frameTriggerDelay = (rlUInt32_t) 0
};

static rlProfileCfg_t gAr1243ProfileArgs[] = {
    {
        .profileId             = (rlUInt16_t) 0,
        .pfVcoSelect           = (rlUInt8_t) 0,
        .pfCalLutUpdate        = (rlUInt8_t) 0,
        .startFreqConst        = (rlUInt32_t) CHAINS_AR1243_FREQ_GHZ_CONV(77),
        .idleTimeConst         = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(7U),
        .adcStartTimeConst     = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(2U),
        .rampEndTime           = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(62U),
        .txOutPowerBackoffCode = (rlUInt32_t) 0,
        .txPhaseShifter        = (rlUInt32_t) 0,
        .freqSlopeConst        = (rlInt16_t) CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(62.4),
        .txStartTime           = (rlInt16_t) CHAINS_AR1243_TIME_US_TO_10NS(1U),
        .numAdcSamples         = (rlUInt16_t) AR1243_PROFILE1_RADAR_WIDTH,
        .digOutSampleRate      = (rlUInt16_t) 3150, /* Kilo Samples per second */
        .hpfCornerFreq1        = (rlUInt8_t) RL_RX_HPF1_175_KHz,
        .hpfCornerFreq2        = (rlUInt8_t) RL_RX_HPF2_350_KHz,
        .txCalibEnCfg          = (rlUInt16_t) 0,
        .rxGain = (rlUInt16_t) 38
    },
    {
        .profileId             = (rlUInt16_t) 1,
        .pfVcoSelect           = (rlUInt8_t) 0,
        .pfCalLutUpdate        = (rlUInt8_t) 0,
        .startFreqConst        = (rlUInt32_t) CHAINS_AR1243_FREQ_GHZ_CONV(77),
        .idleTimeConst         = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(7U),
        .adcStartTimeConst     = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(2U),
        .rampEndTime           = (rlUInt32_t) CHAINS_AR1243_TIME_US_TO_10NS(62U),
        .txOutPowerBackoffCode = (rlUInt32_t) 0,
        .txPhaseShifter        = (rlUInt32_t) 0,
        .freqSlopeConst        = (rlInt16_t) CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(62.4),
        .txStartTime           = (rlInt16_t) CHAINS_AR1243_TIME_US_TO_10NS(1U),
        .numAdcSamples         = (rlUInt16_t) AR1243_PROFILE2_RADAR_WIDTH,
        .digOutSampleRate      = (rlUInt16_t) 16000, /* Kilo Samples per second */
        .hpfCornerFreq1        = (rlUInt8_t) RL_RX_HPF1_175_KHz,
        .hpfCornerFreq2        = (rlUInt8_t) RL_RX_HPF2_350_KHz,
        .txCalibEnCfg          = (rlUInt16_t) 0,
        .rxGain = (rlUInt16_t) 38
    }
};
static rlChirpCfg_t   gAr1243ChirpCfgArgs[] =
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
    },
#if (CHAINS_RADAR_NUM_TX_ANTENNA > 1)
    {
        .chirpStartIdx   = (rlUInt16_t) 0x1,
        .chirpEndIdx     = (rlUInt16_t) 0x1,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlUInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x2, /* TX2 */
        .reserved        = (rlUInt16_t) 0x0
    },
#endif
#if (CHAINS_RADAR_NUM_TX_ANTENNA > 2)
    {
        .chirpStartIdx   = (rlUInt16_t) 0x2,
        .chirpEndIdx     = (rlUInt16_t) 0x2,
        .profileId       = (rlUInt16_t) 0x0, /* First profile */
        .startFreqVar    = (rlUInt32_t) 0x0,
        .freqSlopeVar    = (rlUInt16_t) 0x0,
        .idleTimeVar     = (rlUInt16_t) 0x0,
        .adcStartTimeVar = (rlUInt16_t) 0x0,
        .txEnable        = (rlUInt16_t) 0x4, /* TX2 */
        .reserved        = (rlUInt16_t) 0x0
    },
#endif
};
static rlBpmChirpCfg_t   gAr1243BpmChirpCfgArgs[] =
{
    {
        .chirpStartIdx = (rlUInt16_t) 0x0,
        .chirpEndIdx   = (rlUInt16_t) 0x0,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    },
#if (CHAINS_RADAR_NUM_TX_ANTENNA > 1)
    {
        .chirpStartIdx = (rlUInt16_t) 0x1,
        .chirpEndIdx   = (rlUInt16_t) 0x1,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    },
#endif
#if (CHAINS_RADAR_NUM_TX_ANTENNA > 2)
    {
        .chirpStartIdx = (rlUInt16_t) 0x2,
        .chirpEndIdx   = (rlUInt16_t) 0x2,
        .constBpmVal   = (rlUInt16_t) 0x0,
        .reserved      = (rlUInt16_t) 0x0
    }
#endif
};

#define CHAINS_AR1243_CHIRPROW_SIZE         (sizeof(gAr1243ChirpCfgArgs)/sizeof(rlChirpCfg_t)) * \
                                            (sizeof(gAr1243ProfileArgs)/sizeof(rlProfileCfg_t)) * 16U
rlChirpRow_t      gAr1243ChirpRowArgs[CHAINS_MAX_NUM_RADARS][CHAINS_AR1243_CHIRPROW_SIZE] = {0};

/**< \brief Sensor configuration for the AR1243 Radar Sensor  */
Bsp_Ar12xxConfigObj   gAr12xx_sample_config =
{
    .rfChanCfgArgs            = {
        .rxChannelEn = (rlUInt16_t) (1<<CHAINS_RADAR_NUM_RX_ANTENNA) - 1,
        .txChannelEn = (rlUInt16_t) (1<<CHAINS_RADAR_NUM_TX_ANTENNA) - 1,
        .cascading   = (rlUInt16_t) 0x0,
        .cascadingPinoutCfg = (rlUInt16_t) 0x0
    },
    .adcOutCfgArgs            = {
        .fmt                  = {
            .b2AdcBits    = CHAINS_AR1243_DATA_FORMAT_CONFIG,
            .b6Reserved0 = (rlUInt32_t) 0x0,
            .b8FullScaleReducFctr = (rlUInt32_t) 0x0,
            .b2AdcOutFmt  = RL_ADC_FORMAT_COMPLEX_1X,
            .b14Reserved1 = (rlUInt32_t) 0x0
        },
        .reserved0      = (rlUInt16_t) 0x0
    },
    .dataFmtCfgArgs           = {
        .rxChannelEn  = (rlUInt16_t) (1<<CHAINS_RADAR_NUM_RX_ANTENNA) - 1,
        .adcBits      = (rlUInt16_t) CHAINS_AR1243_DATA_FORMAT_CONFIG,
        .adcFmt       = (rlUInt16_t) RL_ADC_FORMAT_COMPLEX_1X,
        .iqSwapSel    = (rlUInt8_t) RL_DEV_I_FIRST,
        .chInterleave = (rlUInt8_t) RL_DEV_CH_NON_INTERLEAVED,
        .reserved     = (rlUInt32_t) 0x0
    },
    .rfLpModeCfgArgs          = {
        .reserved      = (rlUInt16_t) 0,
        .lpAdcMode     = (rlUInt16_t) RL_ADC_MODE_REGULAR
    },
    .chirpCfgArgs      = gAr1243ChirpCfgArgs,
    .numChirpCfgArgs   = sizeof(gAr1243ChirpCfgArgs)/sizeof(rlChirpCfg_t),
    .profileCfgArgs    = gAr1243ProfileArgs,
    .numProfileCfgArgs = sizeof(gAr1243ProfileArgs)/sizeof(rlProfileCfg_t),
    .frameCfgArgs      = &gAr1243FrmArgs,
    .dataPathCfgArgs   = {
        .intfSel         = (rlUInt8_t) 0,
        .transferFmtPkt0 = (rlUInt8_t) 6, /**< Data out Format, \n
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
        .dataRate   = (rlUInt8_t) CHAINS_AR1243_CSI_DATA_RATE_VALUE,
        .reserved   = (rlUInt16_t) 0
    },
    .hsiClkgs                 = {
        .hsiClk   = (rlUInt16_t) CHAINS_AR1243_DDR_HSI_CLK,
        .reserved = (rlUInt16_t) 0x0
    },
    .laneEnCfgArgs            = {
        .laneEn   = (rlUInt16_t)
            #if CHAINS_AR1243_CSI_DATA1LANE_POS
                ((rlUInt16_t) 0x1) |
            #endif
            #if CHAINS_AR1243_CSI_DATA2LANE_POS
                ((rlUInt16_t) 0x2) |
            #endif
            #if CHAINS_AR1243_CSI_DATA3LANE_POS
                ((rlUInt16_t) 0x4) |
            #endif
            #if CHAINS_AR1243_CSI_DATA4LANE_POS
                ((rlUInt16_t) 0x8) |
            #endif
                ((rlUInt16_t) 0x0),
        .reserved = (rlUInt16_t) 0x0
    },
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
    .bpmChirpCfgArgs = gAr1243BpmChirpCfgArgs,
    .numBpmChirpCfgArgs = sizeof(gAr1243BpmChirpCfgArgs)/sizeof(rlBpmChirpCfg_t),
    .csiConfigArgs = {
        .lanePosPolSel = ((CHAINS_AR1243_CSI_CLOCKLANE_POS << 16U) | /* Polarity Always */
                         (CHAINS_AR1243_CSI_DATA4LANE_POS << 12U) | /* assumed to be 0 */
                         (CHAINS_AR1243_CSI_DATA3LANE_POS << 8U) |
                         (CHAINS_AR1243_CSI_DATA2LANE_POS << 4U) |
                         (CHAINS_AR1243_CSI_DATA1LANE_POS)),
        .reserved1 = (rlUInt32_t) 0U,
    },
    .advFrameCfgArgs = {
        .frameSeq = {
            .numOfSubFrames = (rlUInt8_t) CHAINS_AR1243_NUM_SUBFRAMES,
            .forceProfile   = (rlUInt8_t) 1,
            .loopBackCfg    = (rlUInt8_t) 0,
            .subFrameTrigger = (rlUInt8_t) 0,
            .subFrameCfg = {
                {
                    .forceProfileIdx     = (rlUInt16_t) 0,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) CHAINS_RADAR_NUM_TX_ANTENNA,
                    .numLoops            = (rlUInt16_t) AR1243_RADAR_HEIGHT,
                    .burstPeriodicity    = (rlUInt32_t) CHAINS_AR1243_TIME_MS_TO_5NS(33U),
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
                    .numOfBurst          = (rlUInt16_t) CHAINS_AR1243_NUM_BURSTS,
                    .numOfBurstLoops     = (rlUInt16_t) CHAINS_AR1243_NUM_BURST_LOOPS,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) CHAINS_AR1243_TIME_MS_TO_5NS(66U),
                    .reserved1           = (rlUInt32_t) 0,
                    .reserved2           = (rlUInt32_t) 0
                },
                {
                    .forceProfileIdx     = (rlUInt16_t) 1,
                    .chirpStartIdx       = (rlUInt16_t) 0,
                    .numOfChirps         = (rlUInt16_t) 1,
                    .numLoops            = (rlUInt16_t) AR1243_RADAR_HEIGHT,
                    .burstPeriodicity    = (rlUInt32_t) CHAINS_AR1243_TIME_MS_TO_5NS(33U),
                    .chirpStartIdxOffset = (rlUInt16_t) 0,
                    .numOfBurst          = (rlUInt16_t) CHAINS_AR1243_NUM_BURSTS,
                    .numOfBurstLoops     = (rlUInt16_t) CHAINS_AR1243_NUM_BURST_LOOPS,
                    .reserved0           = (rlUInt16_t) 0,
                    .subFramePeriodicity = (rlUInt32_t) CHAINS_AR1243_TIME_MS_TO_5NS(66U),
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
            .numSubFrames = (rlUInt8_t) CHAINS_AR1243_NUM_SUBFRAMES,
            .reserved0    = (rlUInt8_t) 0,
            .reserved1    = (rlUInt16_t) 0,
            .subframeDataCfg = {
                {
                    .totalChirps =
                        (rlUInt32_t) CHAINS_RADAR_NUM_TX_ANTENNA * AR1243_RADAR_HEIGHT * CHAINS_AR1243_NUM_BURSTS,
                    /* Number of Chirps in Sub-Frame =
                     *                     numOfChirps * numLoops * numOfBurst
                     */
                    .numAdcSamples = (rlUInt16_t) AR1243_PROFILE1_RADAR_WIDTH * (rlUInt16_t) 2,
                    .numChirpsInDataPacket = (rlUInt8_t) 1,
                    /* In AR12xx: Program this as 1 */
                    .reserved = (rlUInt8_t) 0,
                },
                {
                    .totalChirps =
                        (rlUInt32_t) AR1243_RADAR_HEIGHT * CHAINS_AR1243_NUM_BURSTS,
                    .numAdcSamples = (rlUInt16_t) AR1243_PROFILE2_RADAR_WIDTH * (rlUInt16_t) 2,
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
    .frameType = BSP_AR12XX_FRAME_TYPE_NORMAL
};

Int32 Chains_ar12xxGetSampleConfig(ChainsCommon_Ar12xxConfigOut *pCfgOut, UInt32 fusionEnabled)
{
    UInt32 i = 0U;
    UInt32 done = FALSE;
    char ch;
    if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_FPDLINK)
    {
        if (fusionEnabled == 0U)
        {
            while(!done)
            {
                ch = ChainsCommon_ar12xxRunTimeMenu(gChains_numRadarsMenu);
                switch(ch)
                {
                    case '1':
                        pCfgOut->numRadars = 1;
                        done = TRUE;
                        break;
                    case '2':
                        pCfgOut->numRadars = 2;
                        done = TRUE;
                        break;
                    case '3':
                        pCfgOut->numRadars = 3;
                        done = TRUE;
                        break;
                    case '4':
                        pCfgOut->numRadars = 4;
                        done = TRUE;
                        break;
                    default:
                        Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                        break;
                }
            }
        }
        else
        {
            pCfgOut->numRadars = 1;
        }
        Vps_printf(" CHAINS: %d AR12xx connected via FPD-Link... \n\r", pCfgOut->numRadars);
        done = FALSE;
    }
    else
    {
        pCfgOut->numRadars = 1;
    }
    pCfgOut->fusionEnabled = fusionEnabled;
    /* Check for certain size limitations. This will show up as compile time
     * issues.
     */
    COMPILE_TIME_ASSERT(sizeof(gAr1243ChirpCfgArgs)/sizeof(rlChirpCfg_t) > 512);
    COMPILE_TIME_ASSERT(
        sizeof(gAr1243ProfileArgs)/sizeof(rlProfileCfg_t) >
        CHAINS_AR1243_MAX_PROFILES);
    for (i = 0; i < pCfgOut->numRadars; i++)
    {
        /* Defaulting to macro as this not captured in the ar12xxConfig parameter */
        pCfgOut->radarParams[i].numValidBits = CHAINS_AR1243_ADC_DATA_FORMAT;
        pCfgOut->radarParams[i].bpmEnabled = 0U;
        pCfgOut->radarParams[i].numProfiles = sizeof(gAr1243ProfileArgs)/sizeof(rlProfileCfg_t);
    }

    for (i=0; i<CHAINS_MAX_NUM_RADARS; i++)
    {
        memcpy(&pCfgOut->radarParams[i].ar12xxConfig, &gAr12xx_sample_config, sizeof (gAr12xx_sample_config));
        sprintf(pCfgOut->radarParams[i].configName, "%s_%d", CHAINS_AR1243_CONFIG_NAME, i);
        pCfgOut->radarParams[i].chirpRow = &gAr1243ChirpRowArgs[i][0];
        pCfgOut->radarParams[i].numChirpRow = CHAINS_AR1243_CHIRPROW_SIZE;
    }
    /* Default to normal frame */
    pCfgOut->frameType = 0U;
    return SYSTEM_LINK_STATUS_SOK;
}
