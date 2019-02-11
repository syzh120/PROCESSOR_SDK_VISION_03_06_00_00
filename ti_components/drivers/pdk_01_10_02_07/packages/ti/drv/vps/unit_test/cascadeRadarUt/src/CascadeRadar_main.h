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
 *  \file CascadeRadar_main.h
 *
 *  \brief Cascade Radar sample application private header file.
 *
 */

#ifndef CASCADE_RADAR_MAIN_H_
#define CASCADE_RADAR_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/csl/soc.h>
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>
#include <ti/drv/vps/src/devices/radar_ar12xx/src/bspdrv_ar12xxPriv.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Maximum Number of profiles which is possible from the AR device */
#define CASCADE_RADAR_MAX_PROFILES  (4U)

/* Size of the Cascade Task stack */
#define CASCADE_APP_TSK_STACK_MAIN   (10U * 1024U)

/* Test application task priority */
#define RADAR_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CASCADE_RADAR_APP"
/* Name of the configuration used */
#define CASCADE_RADAR_CONFIG_NAME_MASTER       "CASCADE_RADAR_APP_CONFIG_MASTER"
#define CASCADE_RADAR_CONFIG_NAME_SLAVE        "CASCADE_RADAR_APP_CONFIG_MASTER"

/** \brief MCSPI Instance Number used to communicate with the radar sensor */
#define CASCADE_RADAR_MCSPI_INST0 (0U)
#define CASCADE_RADAR_MCSPI_INST1 (1U)
#define CASCADE_RADAR_MCSPI_INST2 (2U)
#define CASCADE_RADAR_MCSPI_INST3 (3U)

#define CASCADE_RADAR_NUM_RX_ANTENNA (4U)
/* Note: Binary Phase Modulation is enabled when Number of Tx Antenna is 3 */
#define CASCADE_RADAR_NUM_TX_ANTENNA (1U)

/** \brief Number of antennas Rx times tx*/
#define CASCADE_RADAR_NUM_ANTENNA (CASCADE_RADAR_NUM_RX_ANTENNA * \
                                    CASCADE_RADAR_NUM_TX_ANTENNA)

/* Uncomment below to enable synthetic input from the AR12x sensor. Kindly note
 * Test source is not available when CASCADE_RADAR_NUM_TX_ANTENNA > 1 */
#define ENABLE_TEST_SOURCE

/** \brief Radar Sensor Height */
#define CASCADE_RADAR_RADAR_HEIGHT   (128U)

/** \brief Radar Sensor width */
#define CASCADE_RADAR_PROFILE1_RADAR_WIDTH   (256U)

/** \brief CSI Data Rate for data transfer from AR12xx
 *         Valid Values are
 *         150 (for 150 Mbps)
 *         300 (for 300 Mbps)
 *         400 (for 400 Mbps)
 *         450 (for 450 Mbps)
 *         600 (for 600 Mbps)
 */
#define CASCADE_RADAR_CSI_DATA_RATE (300U)

#if (CASCADE_RADAR_CSI_DATA_RATE == (150U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CASCADE_RADAR_CSI_DATA_RATE_VALUE (6)       /* 150 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CASCADE_RADAR_DDR_HSI_CLK         (0xB)     /* 150 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CASCADE_RADAR_ISS_CSI_CLK         (75U)     /* 150 Mbps */
#elif (CASCADE_RADAR_CSI_DATA_RATE == (300U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CASCADE_RADAR_CSI_DATA_RATE_VALUE (4)       /* 300 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CASCADE_RADAR_DDR_HSI_CLK         (0xA)     /* 300 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CASCADE_RADAR_ISS_CSI_CLK         (150U)    /* 300 Mbps */
#elif (CASCADE_RADAR_CSI_DATA_RATE == (400U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CASCADE_RADAR_CSI_DATA_RATE_VALUE (3)       /* 400 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CASCADE_RADAR_DDR_HSI_CLK         (0x1)     /* 400 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CASCADE_RADAR_ISS_CSI_CLK         (200U)    /* 400 Mbps */
#elif (CASCADE_RADAR_CSI_DATA_RATE == (450U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CASCADE_RADAR_CSI_DATA_RATE_VALUE (2)       /* 450 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CASCADE_RADAR_DDR_HSI_CLK         (0x5)     /* 450 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CASCADE_RADAR_ISS_CSI_CLK         (225U)    /* 450 Mbps */
#elif (CASCADE_RADAR_CSI_DATA_RATE == (600U))
    /** \brief CSI Data rate value set in the AR12 parameters */
    #define CASCADE_RADAR_CSI_DATA_RATE_VALUE (1)       /* 600 Mbps */
    /** \brief CSI High speed clock set in the AR12 parameters */
    #define CASCADE_RADAR_DDR_HSI_CLK         (0x9)     /* 600 Mbps */
    /** \brief ISS CSI clock paramter set */
    #define CASCADE_RADAR_ISS_CSI_CLK         (300U)    /* 600 Mbps */
#else
    #warn "CASCADE_RADAR: No valid data rate specified!!"
#endif

/**
 * On the TDA3x EVM and the ALPS board the CSI data lane positions are
 * as below:
 *
 *        TDA                              AR
 *   ----------------                 ------------------
 *   csi2_0_dx/y0   |-----------------| dx/dy0
 *   csi2_0_dx/y1   |-----------------| dx/dy2 ** Note
 *   csi2_0_dx/y2   |-----------------| dx/dy1 ** Note
 *   csi2_0_dx/y3   |-----------------| dx/dy3
 *   csi2_0_dx/y4   |-----------------| dx/dy4
 *   ----------------                 ------------------
 */
/** \brief AR CSI clock lane position */
#define CASCADE_RADAR_CSI_CLOCKLANE_POS        (3U)
/** \brief AR CSI first data lane position */
#define CASCADE_RADAR_CSI_DATA1LANE_POS        (1U)
/** \brief AR CSI second data lane position */
#define CASCADE_RADAR_CSI_DATA2LANE_POS        (2U)
/** \brief AR CSI third data lane position */
#define CASCADE_RADAR_CSI_DATA3LANE_POS        (4U)
/** \brief AR CSI fourth data lane position */
#define CASCADE_RADAR_CSI_DATA4LANE_POS        (5U)

/** \brief TDA CSI clock lane position */
#define CASCADE_RADAR_TDA_CSI_CLOCKLANE_POS    (2U)
/** \brief TDA CSI first data lane position */
#define CASCADE_RADAR_TDA_CSI_DATA1LANE_POS    (1U)
/** \brief TDA CSI second data lane position */
#define CASCADE_RADAR_TDA_CSI_DATA2LANE_POS    (3U)
/** \brief TDA CSI third data lane position */
#define CASCADE_RADAR_TDA_CSI_DATA3LANE_POS    (4U)
/** \brief TDA CSI fourth data lane position */
#define CASCADE_RADAR_TDA_CSI_DATA4LANE_POS    (5U)

/** \brief ADC Data Format for AR12
 *         Valid Values are
 *         12  (for 12 bit ADC)
 *         14  (for 14 bit ADC)
 *         16  (for 16 bit ADC)
 */
#define CASCADE_RADAR_ADC_DATA_FORMAT (16U)

#if (CASCADE_RADAR_ADC_DATA_FORMAT == (12U))
    /** \brief AR12 data format value set in the configuration */
    #define CASCADE_RADAR_DATA_FORMAT_CONFIG (RL_ADC_DATA_12_BIT)       /* 12 bit */
    /** \brief CSI data format configuration */
    #define CASCADE_RADAR_CSI_CAPTURE_DATA_FORMAT  (SYSTEM_CSI2_RAW12)  /* 12 bit */
#elif (CASCADE_RADAR_ADC_DATA_FORMAT == (14U))
    /** \brief AR12 data format value set in the configuration */
    #define CASCADE_RADAR_DATA_FORMAT_CONFIG (RL_ADC_DATA_14_BIT)       /* 14 bit */
    /** \brief CSI data format configuration */
    #define CASCADE_RADAR_CSI_CAPTURE_DATA_FORMAT  (SYSTEM_CSI2_RAW14)  /* 14 bit */
#elif (CASCADE_RADAR_ADC_DATA_FORMAT == (16U))
    /** \brief AR12 data format value set in the configuration */
    #define CASCADE_RADAR_DATA_FORMAT_CONFIG (RL_ADC_DATA_16_BIT)       /* 16 bit */
    /** \brief CSI data format configuration */
    #define CASCADE_RADAR_CSI_CAPTURE_DATA_FORMAT  (SYSTEM_CSI2_RAW8)  /* 16 bit */
#else
    #warn "CASCADE_RADAR: No valid ADC data format specified!!"
#endif

/** \brief Advanced Frame Configurations */
#define CASCADE_RADAR_NUM_SUBFRAMES    (2U)
#define CASCADE_RADAR_NUM_BURSTS       (1U)
#define CASCADE_RADAR_NUM_BURST_LOOPS  (1U)

/** \brief Macros for time calculation */
#define CASCADE_RADAR_TIME_MS_TO_5NS(x) ((x * 1000000)/5)
#define CASCADE_RADAR_TIME_US_TO_10NS(x) (x * 100)

#define CASCADE_RADAR_TIME_5NS_TO_MS(x) ((x * 5)/1000000)

#define CASCADE_RADAR_FREQ_CONST (3.6 * 1000000000.0/67108864.0)

/** \brief Macro for Frequency Calculation. Input 'x' is in GHz */
#define CASCADE_RADAR_FREQ_GHZ_CONV(x) \
    ((rlUInt32_t)(((float)x * 1000000000.0 + \
    CASCADE_RADAR_FREQ_CONST)/CASCADE_RADAR_FREQ_CONST))

#define CASCADE_RADAR_FREQ_SLOPE_CONST (CASCADE_RADAR_FREQ_CONST * 900.0/1000.0)

/** \brief Macro for frequency slope conversion. Input 'x' is in MHz/us */
#define CASCADE_RADAR_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(x) \
    ((rlInt16_t)((x * 1000.0 + \
    CASCADE_RADAR_FREQ_SLOPE_CONST)/CASCADE_RADAR_FREQ_SLOPE_CONST))

/** \brief Compile time assert for the array size not correct */
#define COMPILE_TIME_ASSERT(expr) \
    extern UInt8 check_parameter_size[2]; \
    extern UInt8 check_parameter_size[expr? 1: 2]

#undef PULLUDENABLE_ENABLE
#undef PULLUDENABLE_DISABLE
#undef PULLTYPESELECT_PULL_UP
#undef PULLTYPESELECT_PULL_DOWN
#undef INPUTENABLE_ENABLE
#undef INPUTENABLE_DISABLE
#undef SLEWCONTROL_FAST_SLEW
#undef SLEWCONTROL_SLOW_SLEW
#undef WAKEUPENABLE_ENABLE
#undef WAKEUPENABLE_DISABLE

#define PULLUDENABLE_ENABLE         (1U)
#define PULLUDENABLE_DISABLE        (0U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (1U)
#define SLEWCONTROL_SLOW_SLEW       (0U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

/* Frames allocated per channel */
#define CAPT_APP_FRAMES_PER_CH          (4U)

/* Worst case frames per handle */
#define CAPT_APP_MAX_FRAMES_PER_HANDLE  (VPS_CAPT_STREAM_ID_MAX *   \
                                         VPS_CAPT_CH_PER_PORT_MAX * \
                                         CAPT_APP_FRAMES_PER_CH)

/* Padding required for allocating extra memory. */
#define CAPT_APP_PADDING_LINES          (0U)

/* SC enable/disable for different streams  */
#define CAPT_APP_SC_DISABLE_ALL         (0x00U)
#define CAPT_APP_SC_ENABLE_0            (0x01U)
#define CAPT_APP_SC_ENABLE_1            (0x02U)
#define CAPT_APP_SC_ENABLE_ALL          (CAPT_APP_SC_ENABLE_0 | \
                                         CAPT_APP_SC_ENABLE_1)

/**
 * There are 3 32-bit MAX_SIZE registers supported for TDA2XX platform family.
 * These registers provide two parameters width[31:16] and height[15:0].
 * The VPDMA transmits to external buffer the maximum out width number of
 * pixels and maximum out height number of pixel lines.
 * If the VIP receives data exceeding the maximum out width/height then it
 * continues to capture the data. VPDMA will not transfer it to the
 * external buffer.
 * This register (if used) should have valid range of values.
 * The valid range for maximum out width shall be [1, 4096]
 * The valid range for maximum out height shall be [1, 2048]
 * Example: For a YUV420SP capture,
 * For luma, the maximum out [width, height] can go up to [2048, 2048].
 * For chroma, the maximum out [width, height] can go up to [2048, 1024].
 * Example: For a YUV422I capture,
 * For luma, the maximum out [width, height] can go up to [4096, 2048].
 */
/* MAX SIZE Register Width and Height configurations */
#define CAPT_APP_MAXSIZE_1_WIDTH        (4096U)
#define CAPT_APP_MAXSIZE_2_WIDTH        (4096U)
#define CAPT_APP_MAXSIZE_3_WIDTH        (4096U)
#define CAPT_APP_MAXSIZE_1_HEIGHT       (1024U)
#define CAPT_APP_MAXSIZE_2_HEIGHT       (1024U)
#define CAPT_APP_MAXSIZE_3_HEIGHT       (1024U)

/* Capture frame skip pattern - No skip by default */
#define CAPT_APP_FRAME_SKIP_PATTERN     (0x00000000U)

/* Uncomment for Cascade Radar VIP Only Test */
/* #define CASCADE_RADAR_VIP_ONLY_TEST */

#ifdef CASCADE_RADAR_VIP_ONLY_TEST
#undef ENABLE_TEST_SOURCE
#endif

/* Default run count in seconds in case of EVM else this is in frame count. */
#ifdef CASCADE_RADAR_VIP_ONLY_TEST
#define CAPT_APP_RUN_COUNT              (120U)
#else
#define CAPT_APP_RUN_COUNT              (5U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
extern Bsp_Ar12xxConfigObj   gAr12xx_config;
extern rlChirpCfg_t   gAr1243ChirpCfgArgs[];
extern rlProfileCfg_t gAr1243ProfileArgs[];

#if defined (ENABLE_TEST_SOURCE)
extern int16_t gDevice1_reference[512];
extern int16_t gDevice2_reference[512];
extern int16_t gDevice3_reference[512];
extern int16_t gDevice4_reference[512];
#endif

/**
 * \brief Structure which holds the AR12xx configuration parameters.
 */
typedef struct {

    UInt32 csi2OutWidth;
    /**< CSI output width - Number of pixels */
    UInt32 csi2OutHeight;
    /**< CSI output height */
    UInt32 radarWidth [CASCADE_RADAR_MAX_PROFILES];
    /**< Radar Sensor chirp length */
    UInt32 radarHeight [CASCADE_RADAR_MAX_PROFILES];
    /**< Radar sensor number of chirps */
    UInt32 numTxAntenna;
    /**< Number of transmit antennas */
    UInt32 numRxAntenna;
    /**< Number of recieve antennas */
    float rangeRes [CASCADE_RADAR_MAX_PROFILES];
    /**< Range Resolution */
    float velocityRes [CASCADE_RADAR_MAX_PROFILES];
    /**< Velocity Resolution */
    UInt32 inBufAddrOffset;
    /**< Input buffer offset. This is set to a non-zero value only when
     *   the CP data comes before the ADC data.
     */
    UInt32 offsetBwAntennas [CASCADE_RADAR_MAX_PROFILES];
    /**< Input buffer offset between antenna data to take care of offsets
     *   for ADC data and the CP and CQ data.
     */
    UInt32 numProfiles;
    /**< Number of profiles being used in the usecase */
    UInt32 numValidBits;
    /**< Number of valid bits in input data. If numValidBits is 16 then
     *   sign extension is disabled.
     */
    Task_Handle        tskHandle;
    /**< Global task handle. */
} CascadeRadar_Ar12xxConfigOut;

/** \brief Forward declaration for common object. */
typedef struct CascadeRadar_vipObj_t CascadeRadar_vipObj;

/**
 *  \brief Capture application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char              *testDescStr;
    /**< Test description. */
    UInt32             numCh;
    /**< Number of channel in multi-ch case, must be 1 for single channel. */
    UInt32             numHandles;
    /**< Number of capture handles to run with. */
    UInt32             instId[VPS_CAPT_INST_MAX];
    /**< Instance ID to open for each handle. */

    Fvid2_VideoIfMode  videoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth videoIfWidth;
    /**< 8/16/24-bit mode. */

    Fvid2_DataFormat   inDataFmt;
    /**< YUV or RGB data format. */
    UInt32             numStream;
    /**< Number of outputs. */
    Fvid2_DataFormat   outDataFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Output format of each output. */
    UInt32             scEnable;
    /**< Enable scaler in capture path.
     *   CAPT_APP_SC_DISABLE_ALL: SC Disabled,
     *   CAPT_APP_SC_ENABLE_0: SC enabled for stream 0
     *   CAPT_APP_SC_ENABLE_1: SC enable for stream 1
     *   CAPT_APP_SC_ENABLE_ALL: SC enabled for stream 0 and 1. */

    UInt32             inWidth;
    /**< Input resolution width in pixels - used in case scaler is used. */
    UInt32             inHeight;
    /**< Input resolution height in lines - used in case scaler is used. */
    UInt32             outWidth[VPS_CAPT_STREAM_ID_MAX];
    /**< Scaler output resolution width in pixels - used in case scaler is
     *   used. Otherwise this should be same as that of input width. */
    UInt32             outHeight[VPS_CAPT_STREAM_ID_MAX];
    /**< Scaler output resolution height in lines - used in case scaler is
     *   used. Otherwise this should be same as that of input height. */

    Int32              runCount;
    /**< Number of frames to capture. */

    UInt32             testId;
    /**< Test ID for print purpose. This is initialized in the code */
} CascadeRadar_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32               instId;
    /**< Instance ID. */
    Vps_CaptCreateParams createPrms;
    /**< Create time parameters. */
    Vps_CaptCreateStatus createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Vps_CaptVipParams    vipPrms;
    /**< VIP hardware specific parameters. */
    Vps_VipPortConfig    vipPortCfg;
    /**< VIP port configuration. */
    Vps_CaptVipScParams  scPrms;
    /**< SC configuration. */

    UInt32               maxOutWidth[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutWidth:
     *   This the Maximum Width value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Width of the frame/field that shall be transmitted to the
     *   external buffer. If the captured width received exceeds this then
     *   only maxOutWidth number of pixels per line is transmitted to the
     *   external buffer. */
    UInt32               maxOutHeight[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutHeight:
     *   This the Maximum Height value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Height of the frame/field  that shall be transmitted to the
     *   external buffer. If the captured height received exceeds this then
     *   only maxOutHeight number of lines is transmitted to the external
     *   buffer.
     */

    Fvid2_Handle              drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams            cbPrms;
    /**< Callback params. */

    Fvid2_Frame               frames[CAPT_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for capture. */
    Fvid2_Format              allocFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Format passed to utils frame alloc function. */

    CascadeRadar_vipObj       *appObj;
    /**< Reference pointer to application common object. */
    UInt32                    overflowCount;
    /**< Store the count of the overflow. */
} CascadeRadar_vipInstObj;

/**
 *  \brief Test application data structure.
 */
struct CascadeRadar_vipObj_t
{
    CascadeRadar_vipInstObj    instObj[VPS_CAPT_INST_MAX];
    /**< Driver instance objects. */
    CascadeRadar_TestParams testPrms;
    /**< Current test parameters. */

    Fvid2_Handle       fvidHandleAll;
    /**< Global capture handle. */

    UInt32             maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32             maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */
    UInt32             callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static CascadeRadar_TestParams gCaptAppTestPrms[] =
{
    {
        "4 Channel 16-bit Capture",
        1U,                                 /* numCh */
        4U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        FVID2_VIFM_SCH_DS_AVID_VSYNC,
#ifdef CASCADE_RADAR_VIP_ONLY_TEST
        FVID2_VIFW_8BIT,
#else
        FVID2_VIFW_16BIT,
#endif
        FVID2_DF_YUV422I_YUYV,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        CASCADE_RADAR_PROFILE1_RADAR_WIDTH *
        CASCADE_RADAR_NUM_RX_ANTENNA * 2, /* inWidth */
        CASCADE_RADAR_RADAR_HEIGHT *
        CASCADE_RADAR_NUM_TX_ANTENNA,     /* inHeight */
        {CASCADE_RADAR_PROFILE1_RADAR_WIDTH
        * CASCADE_RADAR_NUM_RX_ANTENNA * 2 }, /* outWidth[] */
        {CASCADE_RADAR_RADAR_HEIGHT *
        CASCADE_RADAR_NUM_TX_ANTENNA  }, /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        1
    }
};
void configure_pad(const pad_config_t *pad_array, uint32_t elements);
Int32 Utils_fgpaPowerUp(UInt32 fpgaNum);
Int32 Utils_fpgaStart(UInt32 fpgaNum);
Void Utils_mcspiInit(UInt32 mcSpiInstNum);
Void Utils_mcspiDeinit(UInt32 mcSpiInstNum);
void CascadeRadar_InitPadMuxAR12 (void);
void CascadeRadar_InitPadMuxVip (void);
void Utils_fpgaClockTick (void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CASCADE_RADAR_MAIN_H_ */
