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
 *  \file SubFrmCaptureVip_main.h
 *
 *  \brief VIP capture driver sample application private header file.
 *
 */

#ifndef SUBFRM_CAPTURE_VIP_MAIN_H_
#define SUBFRM_CAPTURE_VIP_MAIN_H_

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

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif

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
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define CAPT_APP_TSK_STACK_MAIN         (10U * 1024U)

/* Test application task priority */
#define CAPT_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CAPT_VIP_APP"

/* Frames allocated per channel */
#define CAPT_APP_FRAMES_PER_CH          (4U)

/* Worst case frames per handle */
#define CAPT_APP_MAX_FRAMES_PER_HANDLE  (VPS_CAPT_STREAM_ID_MAX *   \
                                         VPS_CAPT_CH_PER_PORT_MAX * \
                                         CAPT_APP_FRAMES_PER_CH)

/* Padding required for allocating extra memory. */
#define CAPT_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define CAPT_APP_RUN_COUNT              (60U)

/* Number of slices per frame */
#define CAPT_APP_NUM_SLICE_PER_FRAME    (8U)

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
#define CAPT_APP_MAXSIZE_1_WIDTH        (1920U)
#define CAPT_APP_MAXSIZE_2_WIDTH        (1920U)
#define CAPT_APP_MAXSIZE_3_WIDTH        (1280U)
#define CAPT_APP_MAXSIZE_1_HEIGHT       (1080U)
#define CAPT_APP_MAXSIZE_2_HEIGHT       (540U)
#define CAPT_APP_MAXSIZE_3_HEIGHT       (800U)

/* Capture frame skip pattern - No skip by default */
#define CAPT_APP_FRAME_SKIP_PATTERN     (0x00000000U)

/* Number of log entries stored per slice interrupt. */
#define CAPT_APP_MAX_LOG (5000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct CaptApp_Obj_t CaptApp_Obj;

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

    UInt32             decDrvId[VPS_CAPT_INST_MAX];
    /**< Video decoder driver ID to open for each handle. */

    Fvid2_VideoIfMode  videoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth videoIfWidth;
    /**< 8/16/24-bit mode. */

    Fvid2_Standard     standard;
    /**< Video decoder video standard. */

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
    Bsp_BoardMode      boardMode;
    /**< Capture board mode param like 24-bit, 8-bit. */
    UInt32             boardId;
    /**< List of valid boards to run the test case. */

    UInt32             testId;
    /**< Test ID for print purpose. This is initialized in the code */
} CaptApp_TestParams;

/**
 *  \brief EOF log structure.
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
} CaptApp_CbLogInfo;

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
} CaptApp_SubFrmLogInfo;

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
    Fvid2_SubFrameInfo        subFrmInfo[VPS_CAPT_STREAM_ID_MAX]
    [CAPT_APP_FRAMES_PER_CH];
    /**< Subframe info to be passed to each frame. Number of channel is always
     *   one for sub frame mode. */
    Vps_CaptRtParams          rtPrms[VPS_CAPT_STREAM_ID_MAX]
    [CAPT_APP_FRAMES_PER_CH];
    Fvid2_Handle              decHandle;
    /**< FVID2 decoder/sensor driver handle. */
    Bsp_VidDecCreateParams    decCreatePrms;
    /**< Video decoder create params. */
    Bsp_VidDecVideoModeParams decVideoModePrms;
    /**< Video decoder mode params. */
    Bsp_VidSensorCreateParams sensorCreatePrms;
    /**< Video sensor create params. */

    CaptApp_Obj              *appObj;
    /**< Reference pointer to application common object. */

    CaptApp_CbLogInfo         cbLogInfo[CAPT_APP_MAX_LOG];
    /**< End of frame call back log. */
    UInt32                    cbIdx;
    /**< Callback ISR log index. */
    CaptApp_SubFrmLogInfo     sfLogInfo[CAPT_APP_MAX_LOG];
    /**< Sub frame log. */
    UInt32                    sfCbIdx;
    /**< Sub frame callback ISR log index. */
} CaptApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct CaptApp_Obj_t
{
    CaptApp_InstObj    instObj[VPS_CAPT_INST_MAX];
    /**< Driver instance objects. */
    CaptApp_TestParams testPrms;
    /**< Current test parameters. */

    Fvid2_Handle       fvidHandleAll;
    /**< Global capture handle. */
    Task_Handle        tskHandle;
    /**< Test task handle. */

    UInt32             maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32             maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32             totalFldCount;
    /**< Count of all frames captured. */
    UInt32             totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32             cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32             callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    UInt32             subFrmCallBackCount;
    /**< Subframe callback count. */
    UInt32             enableAutoRun;
    /**< Auto-run enable flag. */

    UInt32             startTime;
    /**< Application start time in clock ticks. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

static CaptApp_TestParams gCaptAppTestPrms[] =
{
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U},                            /* outWidth[] */
        {720U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "LI OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "LI OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_LI_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U},                            /* outWidth[] */
        {720U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION | BSP_BOARD_JAMR3 |
         BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_BASE_TDA2EX),
    },
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "Aptina AR0132->VIP1_S1_PORTA SCH 12-bit Discrete Sync (HSYNC/VSYNC), Bayer (GR) out",
#else
        "Aptina AR0132->VIP1_S0_PORTA SCH 12-bit Discrete Sync (HSYNC/VSYNC), Bayer (GR) out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_APT_AR0132_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_RAW16,
        1U,                                 /* numStream */
        {
            FVID2_DF_RAW16
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U},                            /* outWidth[] */
        {720U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_12BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    {
        "TVP7002->VIP1_S0_PORTA SCH 720p60 16-bit Embedded Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_DEC_TVP7002_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U},                            /* outWidth[] */
        {720U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT1120,
        (BSP_BOARD_VC | BSP_BOARD_CATALOG),
    },
    {
        "MT9V022->VIP1_S0_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_SENSOR_MT9V022_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_CUSTOM,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        480U,                               /* inHeight */
        {720U },                            /* outWidth[] */
        {480U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_16BIT,
        (BSP_BOARD_VISION_TI81XX),
    },
#endif
#ifdef PLATFORM_SIM
    {
        "Simulator: VIP1_S0_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            0U,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U },                            /* outWidth[] */
        {240U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_DEFAULT,
        (BSP_BOARD_UNKNOWN),
    },
#endif  /* #ifdef PLATFORM_SIM */
#ifdef PLATFORM_ZEBU
    {
        "Zebu: VIP1_S0_PORTA SCH D1 16-bit Discrete Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            0U,
        },
        FVID2_VIFM_SCH_DS_AVID_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_D1,
        FVID2_DF_RAW16,
        1U,                                 /* numStream */
        {
            FVID2_DF_RAW16
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U },                            /* outWidth[] */
        {240U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_DEFAULT,
        (BSP_BOARD_UNKNOWN),
    },
#endif  /* #ifdef PLATFORM_ZEBU */

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    {
#if defined (SOC_AM574x) || defined (SOC_AM572x)
        "OV2659->VIP1_S1_PORTB SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "OV2659->VIP1_S0_PORTB SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#if defined (SOC_AM574x) || defined (SOC_AM572x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#endif
        },
        {
            FVID2_VID_SENSOR_OV2659_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U},                            /* outWidth[] */
        {720U },                            /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_UNKNOWN | BSP_BOARD_IDK_AM57XX),
    },
#endif         /* #if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) */
};

#define CAPT_APP_NUM_TESTS              (sizeof (gCaptAppTestPrms) / \
                                         sizeof (gCaptAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef SUBFRM_CAPTURE_VIP_MAIN_H_ */
