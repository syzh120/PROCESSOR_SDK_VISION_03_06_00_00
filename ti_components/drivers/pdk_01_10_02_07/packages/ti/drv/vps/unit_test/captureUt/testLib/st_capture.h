/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file st_capture.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the CAPTURE UT applications.
 */

#ifndef ST_CAPT_H_
#define ST_CAPT_H_

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
#include <ti/sysbios/knl/Semaphore.h>

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
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_lvds.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>

#if defined (SOC_AM574x) ||  defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#if defined(__GNUC__) && !defined(__ti__)
/* GCC */
#define DATA_SECTION(section_name)     __attribute__((section(section_name)))
#define DATA_ALIGN(x)                  __attribute__((aligned(x)))
#endif

/* Capture UT trace */
#define BspCaptUtTrace                  (GT_INFO | GT_TraceState_Enable)

/* Test application stack size */
#define ST_CAPT_TSK_STACK_MAIN         (10U * 1024U)

// #define ST_CAPT_TSK_STACK_RESET        (10U * 1024)

/* Test application task priority */
#define ST_CAPT_TSK_PRI_MAIN           (10U)

#define UT_NAME                        "CAPT_VIP_UT"

/* Frames allocated per channel */
#define ST_CAPT_APP_FRAMES_PER_CH          (4U)

/* Worst case frames per handle */
#define ST_CAPT_APP_MAX_FRAMES_PER_HANDLE  (VPS_CAPT_STREAM_ID_MAX *   \
                                            VPS_CAPT_CH_PER_PORT_MAX * \
                                            ST_CAPT_APP_FRAMES_PER_CH)

/* Padding required for allocating extra memory. */
#define ST_CAPT_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define ST_CAPT_RUN_COUNT              (5U)

/* SC enable/disable for different streams  */
#define ST_CAPT_SC_DISABLE_ALL         (0x00U)
#define ST_CAPT_SC_ENABLE_0            (0x01U)
#define ST_CAPT_SC_ENABLE_1            (0x02U)
#define ST_CAPT_SC_ENABLE_ALL          (ST_CAPT_SC_ENABLE_0 | \
                                        ST_CAPT_SC_ENABLE_1)

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
#define ST_CAPT_MAXSIZE_1_WIDTH        (1920U)
#define ST_CAPT_MAXSIZE_2_WIDTH        (1920U)
#define ST_CAPT_MAXSIZE_3_WIDTH        (1280U)
#define ST_CAPT_MAXSIZE_1_HEIGHT       (1080U)
#define ST_CAPT_MAXSIZE_2_HEIGHT       (540U)
#define ST_CAPT_MAXSIZE_3_HEIGHT       (800U)

/* Number of log entries stored per slice interrupt. */
#define ST_CAPT_LOG_MAX (5u)

/* Capture frame skip pattern - No skip by default */
#define ST_CAPT_FRAME_SKIP_PATTERN     (0x2AAAAAAAU)

/* Default values */
#define DEF_LOOP_CNT_EVM                (5U)
#define DEF_LOOP_CNT                    (1U)    /* For Zebu/Sim */
#define DEF_OPEN_CLOSE_CNT              (1U)
#define DEF_START_STOP_CNT              (1U)

/* Count used for open/close test cases */
#define LOOP_CNT_OC                     (1u)
#define OPEN_CLOSE_CNT_OC               (125U)

/* Loop and start/stop count used for start/stop test case */
#define LOOP_CNT_SS                     (1u)
#define START_STOP_CNT_SS               (1000u)

/* Maximum number of continuous interrupts*/
#define ST_CAPT_MAX_CONTI_OF_INTERRUPTS 2

#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)
#define SUBFRM_ENABLE                   (TRUE)
#define SUBFRM_DISABLE                  (FALSE)
#define SC_NONLINEAR_ENABLE             (TRUE)
#define SC_NONLINEAR_DISABLE            (FALSE)
#define SC_ADVCFG_ENABLE                (TRUE)
#define SC_ADVCFG_DISABLE               (FALSE)
#define BUF_CAPT_MODE_TEST_ENABLE       (TRUE)
#define BUF_CAPT_MODE_TEST_DISABLE      (FALSE)

#define USE_DEF_LP_CNT                  (DEF_LOOP_CNT_EVM)

#define ST_CAPT_PRINT_BUFSIZE           (300U)

/* Semaphore to sync between the reset and the callback function */
// BspOsal_SemHandle overflowSem;

/**
 *  \brief Test types.
 */
typedef enum
{
    ST_TT_SANITY      = 0x01,
    ST_TT_REGRESSION  = 0x02,
    ST_TT_FULL        = 0x04,
    ST_TT_FUNCTIONAL  = 0x08,
    ST_TT_STRESS      = 0x10,
    ST_TT_NEGATIVE    = 0x20,
    ST_TT_PERFORMANCE = 0x40,
    ST_TT_MISC        = 0x80,
    ST_TT_API         = 0x100
} st_CaptApp_TestType;

/**
 *  \brief Capture UT test case type.
 *  The test case is classified based on this value.
 */typedef enum
{
    ST_CAPT_TCT_MAIN = 0,
    ST_CAPT_TCT_DETECT,
    /* Detect test-cases */
    ST_CAPT_TCT_NON_MUX_FRAME,
    /* Single channel frame/field capture */
    ST_CAPT_TCT_MUX_FRAME,
    /* Multi channel (muxed mode) frame/field capture */
    ST_CAPT_TCT_NON_MUX_NSLICE,
    /* Single channel sub-frame/filed capture */
    ST_CAPT_TCT_MUX_NSLICE,
    /* Multi channel (muxed mode) sub-frame/filed capture */
    ST_CAPT_TCT_HALT
    /* Halt test-cases */
} st_CaptApp_TestCaseType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct st_CaptApp_Obj_t st_CaptApp_Obj;

/* Forward declaration. */
typedef struct st_SystemCtrl_t st_SystemCtrl;

/**
 *  \brief Structure used for CAPTURE UT control parameters.
 */
struct st_SystemCtrl_t
{
    UInt32 loopCnt;
    /**< Default loop count. */
    UInt32 openCloseCnt;
    /**< Number of times to do open/close operation.
     *  Default openClose count */
    UInt32 startStopCnt;
    /**< Number of times the instance handle shall be stopped and started
     *  Default startStop count */
    UInt32 rtPrintEnable;
    /**< Enables runtime remote prints like VENC underflow status etc.
     *  DEFAULT: 0 (OFF). */
    UInt32 skipDiscSyncTests;
    /**< Flag to Skip all the test cases related to Discrete Sync input.
     *  (TBD Disc Sync, Sensors, etc.)
     *  DEFAULT: 0 (OFF). */

    UInt32 skipEmbSyncTests;
    /**< Flag to Skip all the test cases related to Embedded Sync input.
     *  (TBD Emb Sync, TVP5158, etc.)
     *  DEFAULT: 0 (OFF). */

    UInt32 skipSliceModeTests;
    /**< Flag to Skip all the test cases related to Slice/Sub-Frame mode.
     *  DEFAULT: 0 (OFF). */

    UInt32 skipTvp5158Tests;
    /**< Flag to Skip all the test cases related to TVP5158 Video Decoder.
     *  DEFAULT: 0 (OFF). */
    UInt32 skipADV7611Tests;
    /**< Flag to Skip all the test cases related to ADV7611 Video Decoder.
     *  DEFAULT: 0 (OFF). */
    UInt32 skipSII9127Tests;
    /**< Flag to Skip all the test cases related to  SII9127 Video Decoder.
     *  DEFAULT: 0 (OFF). */

    UInt32 skipSensorTests;
    /**< Flag to Skip all the test cases related to Sensors Video Decoder.
     *  (Aptina Sensors such as AR0132,
     *   OmniVision Sensors such as 0V1063x, LI OV1063x,
     *   Multideserialiser Camera OV sensors)
     *  DEFAULT: 0 (OFF). */

    UInt32 skipAptinaSensorTests;
    /**< Flag to Skip all the test cases related to Sensors Video Decoder.
     *  (Aptina Sensors such as AR0132)
     *  DEFAULT: 0 (OFF). */

    UInt32 skipOVSensorTests;
    /**< Flag to Skip all the test cases related to Sensors Video Decoder.
     *  (Aptina Sensors such as 0V1063x, LI OV1063x, Multideserialiser Camera OV
     *   sensors )
     *  DEFAULT: 0 (OFF). */
    UInt32 skipMultiDesCamOVSensorTests;
    /**< Flag to Skip all the test cases related to Multideserialiser Camera OV
     * sensors Video Decoder.
     *  (Aptina Sensors such as AR0132,
     *   OmniVision Sensors such as 0V10630)
     *  DEFAULT: 0 (OFF). */
    UInt32 skipInterlacedTests;
    /**< Flag to Skip all the test cases related to Interlaced capture.
     *  DEFAULT: 0 (OFF). */

    UInt32 skipProgressiveTests;
    /**< Flag to Skip all the test cases related to Progressive capture.
     *  1080p and 720p capture.
     *  DEFAULT: 0 (OFF). */
    UInt32 skip720pTests;
    /**< Flag to Skip 720p capture.
     *  DEFAULT: 0 (OFF). */
    UInt32 skip1080pTests;
    /**< Flag to Skip 1080p capture.
     *  DEFAULT: 0 (OFF). */
    UInt32 skipHaltTests;
    /**< Flag to Skip Halt Test.
     *  DEFAULT: 0 (OFF). */
    UInt32 waitForBufSaveRDisplay;
    /**< Flag to wait for buffers to be saved or to be displayed.
     *  DEFAULT: 0 (OFF) - Will display the captureed buffer in LCD/HDMI */
};

/**
 *  \brief Capture UT Picture/Frame/Field resolution in terms of width & height
 */
typedef struct
{
    UInt32 width;
    UInt32 height;
} st_CaptApp_Resoultion;

/**
 *  \brief EOFrame log structure.
 */
typedef struct
{
    UInt32 timeStamp;
    /**< End of frame callback timestamp. */
    UInt32 timeStampDiff;
    /**< Difference between previous and current end of frame callback. */
    UInt32 fid;
    /**< FID of the frame as returned by the driver. */
    UInt32 capturedOutWidth;
    /**< Captured data width in pixels. */
    UInt32 capturedOutHeight;
    /**< Captured data height in lines. */
} st_CaptApp_CbLogInfo;

/**
 *  \brief Sub frame log structure.
 */
typedef struct
{
    UInt32 eofTimeStamp;
    /**< End of frame callback timestamp. */
    UInt32 eofTimeStampDiff;
    /**< Difference between previous and current end of frame callback. */
    UInt32 eofIdx;
    /**< End of frame index. */
    UInt32 timeStamp;
    /**< Sub-frame callback timestamp in OS ticks. */
    UInt32 timeStampDiff;
    /**< Difference between previous and current sub-frame callback. */
    UInt32 frmAddress;
    /**< Frame address. */
    UInt32 fid;
    /**< FID of the slice as returned by the driver. */
    UInt32 subFrameNum;
    /**< Current sub-frame number in this frame as returned by driver. */
    UInt32 numOutLines;
    /**< Number of lines generated in output buffer after processing
     *   current sub-frame as returned by driver. */
    UInt32 capturedOutWidth;
    /**< Captured data width in pixels. */
    UInt32 capturedOutHeight;
    /**< Captured data height in lines. */
} st_CaptApp_SubFrmLogInfo;

/**
 *  \brief Capture driver create arguments, used when calling Fvid2_create()
 */
typedef struct
{
    Fvid2_VideoIfMode      videoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth     videoIfWidth;
    /**< 8/16/24-bit mode. */
    Vps_CaptBufferCaptMode bufCaptMode;
    /**< Buffer capture mode. */
    UInt32                 numCh;
    /**< Number of channel for multi-channel modes,
     *   Must be 1 for FVID2_VIFM_SCH_NON_MUX_* capture modes. */
    UInt32                 numStream;
    /**< Number of output streams, MUST be <= VPS_CAPT_STREAM_ID_MAX. */
} st_CaptApp_CreateParams;

/**
 *  \brief Capture driver advanced scalar configuration parameters.
 */
typedef struct
{
    Fvid2_ScanFormat        inFrameMode;
    /**< Input Frame Mode i.e. Interlaced/progressive. */
    Fvid2_ScanFormat        outFrameMode;
    /**< Output Frame Mode i.e. interlaced or progressive. Input and
     *   output frame mode can be different so that scaler can convert
     *   one format to another. */
    Fvid2_FidPol            fidPol;
    /**< This is used to specify whether input FID will be inverted before use
     *   or not. Use #Fvid2_FidPol */
    Vps_ScSelfGenFid        selfGenFid;
    /**< Flag to indicate whether to use self Generate FID feature of the
     *   scaler. */
    Vps_ScBiLinearIntpType  biLinIntpType;
    /**< Variable to specify Bilinear Interpolation Type. */
    Vps_ScHorzScalerDcmType hsDcmType;
    /**< Choose which decimators are active. */
    UInt32                  hPolyBypass;
    /**< Flag to bypass horizontal scaler. When this flag is zero, polyphase
     *   scaler is always used regardless of the width configuration */
    Vps_ScVertScalerType    vsType;
    /**< This is used to specify vertical scaling algorithm. */
    UInt32                  phInfoMode;
    /**< Flag to indicate whether to program Scaler phase information from
     *  below values Or calculate locally from config.
     *  The variable polyPhaseValues and ravPhaseValues should be
     *  set appropriately in case of
     *  phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     *  Use #Vps_ScSetPhaseInfoMode
     */
    Vps_ScPolyPhaseInfo     polyphasePhInfo;
    /**< Scaler phase value for polyphase filter case - used only when
     * phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     */
    Vps_ScRavPhaseInfo      ravPhInfo;
    /**< Scaler phase value for RAV filter case - used only when
     * phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP
     */
} st_CaptApp_AdvScConfig;

/**
 *  \brief VIP parameters used in set/get VIP params.
 */
typedef struct
{
    UInt32                  inWidth;
    /**< Input resolution width in pixels - used in case scaler is used. */
    UInt32                  inHeight;
    /**< Input resolution height in lines - used in case scaler is used. */
    Fvid2_DataFormat        inDataFmt;
    /**< YUV or RGB data format. */
    Fvid2_ScanFormat        inScanFormat;
    /**< Scan Format. */
    Fvid2_BitsPerPixel      inBPP;
    /**< Number of bits per pixel. */

    /* ScParams */
    UInt32                  cropStartX;
    /**< Horizontal offset from which picture needs to be cropped. */
    UInt32                  cropStartY;
    /**< Vertical offset from which picture needs to be cropped. */
    UInt32                  cropWidth;
    /**< Width of the picture to be cropped. */
    UInt32                  cropHeight;
    /**< Height of the picture to be cropped. */
    UInt32                  nonLinear;
    /**< Flag to indicate whether linear or non-linear scaling is used for
     *   horizontal scaler. Non-linear scaling is available for polyphase
     *   filter only
     *   Example: Scaling from 16/9 aspect ratio to 4/3 aspect ratio.*/
    UInt32                  stripSize;
    /**< Size of left and right strip for nonlinear horizontal scaling in terms
     *   of pixel. It must be set to zero for linear horz scaling. */
    UInt32                  enableScAdvCfg;
    /**< Enable/Disable Scalar Advanced Configuration Parameters.
     *  If this is TRUE then the advCfg should be set to a
     *  valid data-structure. */
    st_CaptApp_AdvScConfig *advCfg;
    /**< Scalar Advanced Configuration Parameters.
     *  This shall be NULL if enableScAdvCfg is FALSE. */

    /* Csc Params */
    Vps_CscCoeff           *cscCoeff;
    /**< Set of user provided coefficients. Null if pre-calculated
     *   coefficients is to be used. */
} st_CaptApp_VipParams;

/**
 *  \brief Capture driver out stream arguments, used when calling
 *         Fvid2_create()
 */
typedef struct
{
    UInt32                outWidth;
    /**< Scaler output resolution width in pixels - used in case scaler is
     *   used. Otherwise this should be same as that of input width. */
    UInt32                outHeight;
    /**< Scaler output resolution height in lines - used in case scaler is
     *   used. Otherwise this should be same as that of input height. */
    Fvid2_DataFormat      outDataFmt;
    /**< Output format of each output. */
    Fvid2_ScanFormat      outScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */
    Fvid2_BitsPerPixel    outBPP;
    /**< Number of bits per pixel. For valid values see #Fvid2_BitsPerPixel. */
    Fvid2_BufferFormat    bufFmt;
    /**< Frame capture or field capture for interlaced scan format. */
    Vps_VpdmaMemoryType   memType;
    /**< Tiled or non-tiled memory selection for output. */
    Vps_VpdmaMaxOutWidth  maxOutWidth[FVID2_MAX_PLANES];
    /**< Set limit on the max possible width of the output frame. */
    Vps_VpdmaMaxOutHeight maxOutHeight[FVID2_MAX_PLANES];
    /**< Set limit on the max possible height of the output frame. */
    UInt32                scEnable;
    /**< TRUE: Use scaler before writing video data to memory,
     *   FALSE: Scaler is not used in capture path
     *   MUST be FALSE for line-multiplexed, pixel multiplexed modes. */
    UInt32                subFrameEnable;
    /**< Slice/Sub-Frame mode enabled. */
    UInt32                numSlicesPerFrame;
    /**< Number of slices per frame/field.
     *  This value is valid only if subFrameEnable is set to TRUE. */
    UInt32                frameSkipMask[VPS_CAPT_CH_PER_PORT_MAX];
    /**< Frame Skip information information. */
} st_CaptApp_OutStreamParams;

typedef struct
{
    UInt32 maxSizeRegWidth[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**< Set limit on the max possible width of the output frame. */
    UInt32 maxSizeRegHeight[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**< Set limit on the max possible height of the output frame. */
} st_CaptApp_MaxSizeRegs;

/**
 *  \brief Capture application test configuration.
 *  These are the capture config parameters for the test case.
 */
typedef struct
{
    Bool                    testEnable;
    /**< Test case is to be executed or not. */
    Bool                    bufCaptModeTestEnable;
    /**< Enable/Disable bufCaptModeTest. */
    Bool                    printEnable;
    /**< Enable/Disable print statements. */
    Char                   *swReqtId;
    /**< Software Requirement ID. */
    UInt32                  testCaseId;
    /**< Test Case ID. */
    st_CaptApp_TestType     testType;
    /**< Type of test like functional, regression, etc. */
    Int32                   runCount;
    /**< Number of frames to capture. */
    Char                   *testDescStr;
    /**< Test description. */
    st_CaptApp_TestCaseType testCaseType;
    /**< Type of the test case to be executed. */
    UInt32                  numHandles;
    /**< Number of capture handles to run with. */
    Char                   *userInfo;
    /**< Test case user Info. */
    Char                   *disableReason;
    /**< Reason string for disabling a test case. */
    UInt32                  platformId;
    /**< List of valid platform to run the test case. */
    UInt32                  socId;
    /**< List of valid SOC to run the test case. */
    UInt32                  boardId;
    /**< List of valid boards to run the test case. */
    Bsp_BoardMode           boardMode;
    /**< Capture board mode param like 24-bit, 8-bit. */
    UInt32                  strStpCntVal;
    /**< start stop count value. */
    st_CaptApp_MaxSizeRegs  maxSizeRegs[VPS_VIP_MAX];
    /**< Set limit on the max possible width and height of the output frame. */
} st_CaptApp_TestConfig;

/**
 *  \brief Capture application test parameters for a capture instance.
 *  These are the capture config parameters for the test case.
 */
typedef struct
{
    UInt32                     instId;
    /**< Instance ID to open for each handle. */
    UInt32                     decDrvId;
    /**< Video decoder driver ID to open for each handle. */
    Fvid2_Standard             standard;
    /**< Video decoder video standard. */

    st_CaptApp_CreateParams    createParams;
    /**< Capture Driver Create time parameters */
    st_CaptApp_VipParams       vipParams;
    /**< VIP configuration parameters. */
    st_CaptApp_OutStreamParams outStrmParams[VPS_CAPT_STREAM_ID_MAX];
    /**< Out stream information. */
} st_CaptApp_TestInstParams;

/**
 *  \brief Capture application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    st_CaptApp_TestConfig     testConfig;
    /**< Current test configuration. */
    st_CaptApp_TestInstParams testInstPrms[VPS_CAPT_INST_MAX];
    /**< Current test parameters for every instance. */
    /*
     * Below variables are initialized in code and not in table!!
     */
    Bool                      isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                     testResult;
    /**< Test result. */
} st_CaptApp_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32               instId;
    /**< Instance ID. */
    UInt32               decDrvId;
    /**< Decoder driver ID. */

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
    Vps_ScAdvConfig      scAdvCfg;
    /**< SC advanced configuration. */
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

    Fvid2_Frame               frames[ST_CAPT_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for capture. */
    Fvid2_Format              allocFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Format passed to utils frame alloc function. */

    Fvid2_Handle              decHandle;
    /**< FVID2 decoder/sensor driver handle. */
    Bsp_VidDecCreateParams    decCreatePrms;
    /**< Video decoder create params. */
    Bsp_VidDecVideoModeParams decVideoModePrms;
    /**< Video decoder mode params. */
    Bsp_VidSensorCreateParams sensorCreatePrms;
    /**< Video sensor create params. */

    st_CaptApp_Obj           *appObj;
    /**< Reference pointer to application common object. */
    UInt32                    overflowCount;
    /**< Store the count of the overflow. */
    st_CaptApp_CbLogInfo      cbLogInfo[ST_CAPT_LOG_MAX];
    /**< End of frame call back log. */
    UInt32                    cbIdx;
    /**< Callback ISR log index. */
    st_CaptApp_SubFrmLogInfo  sfLogInfo[ST_CAPT_LOG_MAX];
    /**< Sub frame log. */
    UInt32                    sfCbIdx;
    /**< Sub frame callback ISR log index. */
} st_CaptApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct st_CaptApp_Obj_t
{
    st_CaptApp_InstObj     instObj[VPS_CAPT_INST_MAX];
    /**< Driver instance objects. */
    st_CaptApp_TestParams *testPrms;
    /**< Current test parameters. */
    UInt32                 taskId;
    /**< Task ID. */
    Int32                  testResult;
    /**< Test Result. Based on this testbench will print Pass/Fail. */
    const st_SystemCtrl   *sysCtrl;
    /**< Pointer to system control. */
    UInt32                 traceMask;
    /**< Masks for the debug prints. */

    Fvid2_Handle           fvidHandleAll;
    /**< Global capture handle. */
    Task_Handle            tskHandle;
    /**< Test task handle. */
    Task_Handle            resetTskHandle;
    /**< Reset task handle. */

    UInt32                 maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                 maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                 totalFldCount;
    /**< Count of all frames captured. */
    UInt32                 totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                 cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32                 callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    UInt32                 subFrmCallBackCount;
    /**< Subframe callback count. */
    UInt32                 enableAutoRun;
    /**< Auto-run enable flag. */
    UInt32                 startTime;
    /**< Application start time in clock ticks. */
    Bsp_PlatformId         platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev     cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId            boardId;
    /**< Board identifier. */
};

/**
 *  \brief Structure used for CAPTURE UT object common for all the tasks.
 */
typedef struct
{
    st_SystemCtrl      sysCtrl;
    /**< System control information. */

    UInt32             skipCount;
    /**< Number of test cases skipped because of platform/user settings. */
    UInt32             disableCount;
    /**< Number of test cases disabled because of any bug etc. */

    UInt32             traceMask;
    /**< Masks for the debug prints. */

    Bsp_PlatformId     platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId        boardId;
    /**< Board identifier. */
} st_CaptUtObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void st_resetTestResult(void);

void st_printTestResult(UInt32 skipCount, UInt32 disableCount);

Int32 st_captCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                           UInt32                        traceMask);

void st_logTestResult(Int32  testResult,
                      UInt32 testCaseId,
                      char  *testcaseInfo);

Int32 st_captMainTestCase(st_CaptApp_Obj *appObj, st_CaptUtObj  *utObj);

Int32 st_captCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved);

Int32 st_captSubFrmCbFxn(Fvid2_Handle handle, Fvid2_Frame *subFrame);

Int32 st_captAllocAndQueueFrames(st_CaptApp_Obj     *appObj,
                                 st_CaptApp_InstObj *instObj,
                                 UInt32              fieldMerged,
                                 const st_CaptUtObj *utObj);

Int32 st_captCreateVidSensor(st_CaptApp_Obj     *appObj,
                             st_CaptApp_InstObj *instObj,
                             const st_CaptUtObj *utObj,
                             UInt32              instanceCnt);

Int32 st_captCreateVidDec(st_CaptApp_Obj     *appObj,
                          st_CaptApp_InstObj *instObj,
                          const st_CaptUtObj *utObj,
                          UInt32              instanceCnt);

Int32 st_captFreeFrames(st_CaptApp_Obj     *appObj,
                        st_CaptApp_InstObj *instObj,
                        UInt32              fieldMerged,
                        const st_CaptUtObj *utObj);

Int32 st_captOverflowCbFxn(st_CaptApp_InstObj *instObj);

void st_captPrintStatistics(st_CaptApp_Obj *appObj,
                            UInt32          execTimeInMsecs);

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ST_CAPT_H_ */
