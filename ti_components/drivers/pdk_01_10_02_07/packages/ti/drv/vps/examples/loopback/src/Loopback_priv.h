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
 *  \file Loopback_priv.h
 *
 *  \brief Loopback sample application private header file.
 *
 */

#ifndef LOOPBACK_PRIV_H_
#define LOOPBACK_PRIV_H_

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
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_lcdController.h>
#include <ti/drv/vps/include/devices/bsp_sii9022a.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_lvds.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define LPBK_APP_TSK_STACK_MAIN         (10U * 1024U)

/* Test application task priority */
#define LPBK_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "LOOPBACK_APP"

/* Frames allocated per channel */
#define LPBK_APP_FRAMES_PER_CH          (6U)

/* Worst case frames per handle */
#define LPBK_APP_CAPT_MAX_FRM           (VPS_CAPT_STREAM_ID_MAX *   \
                                         VPS_CAPT_CH_PER_PORT_MAX * \
                                         LPBK_APP_FRAMES_PER_CH)

/* Worst case frames per handle - used for blank frames */
#define LPBK_APP_DISP_MAX_FRM           (1U)

/* Padding required for allocating extra memory. */
#define LPBK_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define LPBK_APP_RUN_COUNT              (30U)
/* Channel switch rate in seconds used in case of multi-channel capture */
#define LPBK_APP_CH_SWITCH_RATE         (5U)

/* Buffer width in pixels to allocate. */
#define LPBK_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define LPBK_APP_BUF_HEIGHT             (1080U)

/* SC enable/disable for different streams */
#define LPBK_APP_SC_DISABLE_ALL         (0x00U)
#define LPBK_APP_SC_ENABLE_0            (0x01U)
#define LPBK_APP_SC_ENABLE_1            (0x02U)
#define LPBK_APP_SC_ENABLE_ALL          (LPBK_APP_SC_ENABLE_0 | \
                                         LPBK_APP_SC_ENABLE_1)

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
#define LPBK_APP_MAXSIZE_1_WIDTH        (LPBK_APP_BUF_WIDTH)
#define LPBK_APP_MAXSIZE_2_WIDTH        (1920U)
#define LPBK_APP_MAXSIZE_3_WIDTH        (1280U)
#define LPBK_APP_MAXSIZE_1_HEIGHT       (LPBK_APP_BUF_HEIGHT)
#define LPBK_APP_MAXSIZE_2_HEIGHT       (540U)
#define LPBK_APP_MAXSIZE_3_HEIGHT       (800U)

/* Capture frame skip pattern - No skip by default */
#define LPBK_APP_FRAME_SKIP_PATTERN     (0x00000000U)

/* Other hard coded parameters */
#define LPBK_APP_NUM_CAPT_CH            (1U)
#define LPBK_APP_NUM_CAPT_STREAM        (1U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define LPBK_APP_USE_LCD_WIDTH          (800U)
#define LPBK_APP_USE_LCD_HEIGHT         (480U)

#if defined (__GNUC__) && !defined (__ti__)
/* GCC */
#define DATA_SECTION(section_name)     __attribute__((section(section_name)))
#define DATA_ALIGN(x)                  __attribute__((aligned(x)))
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct LpbkApp_Obj_t LpbkApp_Obj;

/** \brief Forward declaration for instance object. */
typedef struct LpbkApp_InstObj_t LpbkApp_InstObj;

/**
 *  \brief Capture application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char              *testDescStr;
    /**< Test description. */

    UInt32             numCaptHandles;
    /**< Number of capture handles to run with. */
    UInt32             numDispHandles;
    /**< Number of display handles to run with. */

    UInt32             captInstId[VPS_CAPT_INST_MAX];
    /**< Instance ID to open for each handle. */
    UInt32             dispInstId[VPS_DISP_INST_MAX];
    /**< Display instance ID to open for each handle. */

    UInt32             decDrvId[VPS_CAPT_INST_MAX];
    /**< Video decoder driver ID to open for each handle. */
    UInt32             encDrvId[VPS_DISP_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */

    UInt32             vencId[VPS_DISP_ENC_INST_MAX];
    /**< Venc ID for each handle. */
    UInt32             isSdVenc;
    /**< True for SD VENC and false for others. Valid only for Tda3xx. */

    Fvid2_Standard     captStandard;
    /**< Video decoder video standard. */
    Fvid2_Standard     dispStandard[VPS_DISP_INST_MAX];
    /**< Video encoder video standard. */

    Fvid2_VideoIfMode  captVideoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth captVideoIfWidth;
    /**< 8/16/24-bit mode. */
    Fvid2_ScanFormat   captScanFormat;
    /**< Capture scan format - interlaced/progressive */
    Fvid2_DataFormat   captInDataFmt;
    /**< YUV or RGB data format. */
    Fvid2_DataFormat   captOutDataFmt;
    /**< Output format of capture - This will be the input data format for
     *   display. */

    UInt32             captScEnable;
    /**< Enable scaler in capture path.
     *   LPBK_APP_SC_DISABLE_ALL: SC Disabled,
     *   LPBK_APP_SC_ENABLE_0: SC enabled for stream 0
     *   LPBK_APP_SC_ENABLE_1: SC enable for stream 1
     *   LPBK_APP_SC_ENABLE_ALL: SC enabled for stream 0 and 1. */
    UInt32             captInWidth;
    /**< Input resolution width in pixels - used in case scaler is used. */
    UInt32             captInHeight;
    /**< Input resolution height in lines - used in case scaler is used. */
    UInt32             captOutWidth;
    /**< Scaler output resolution width in pixels - used in case scaler is
     *   used. Otherwise this should be same as that of input width. */
    UInt32             captOutHeight;
    /**< Scaler output resolution height in lines - used in case scaler is
     *   used. Otherwise this should be same as that of input height. */

    UInt32             dispInWidth;
    /**< Display width in pixels. */
    UInt32             dispInHeight;
    /**< Display height in lines. */

    Uint32             tarWidth;
    /**<Target width in pixels. Output to display*/
    Uint32             tarHeight;
    /**<Target height in pixels. Output to display*/

    Int32              runCount;
    /**< Number of frames to capture. */

    Bsp_BoardMode      captBoardMode;
    /**< Capture board mode param like 24-bit, 8-bit. */
    Bsp_BoardMode      dispBoardMode;
    /**< Display board mode param like 24-bit, 8-bit. */
    UInt32             boardId;
    /**< List of valid boards to run the test case. */

    UInt32             testId;
    /**< Test ID for print purpose. This is initialized in the code */
} LpbkApp_TestParams;

/**
 *  \brief Frame information - used for handling field merge capture.
 */
typedef struct
{
    Fvid2_Fid        bufFid;
    /**< This frame buffer is even or odd field. */
    Fvid2_Frame     *bufPair;
    /**< Corresponding field pair - pointer to even buffer if this is odd
     *   field buffer or vice versa. */
    LpbkApp_InstObj *instObj;
    /**< Reference to instance object. */
} LpbkApp_FrameInfo;

/**
 *  \brief Driver instance information.
 */
struct LpbkApp_InstObj_t
{
    UInt32                captInstId;
    /**< Capture Instance ID. */
    UInt32                dispInstId;
    /**< Display Instance ID. */

    UInt32                decDrvId;
    /**< Decoder driver ID. */
    UInt32                encDrvId;
    /**< Encoder driver ID. */

    Vps_CaptCreateParams  captCreatePrms;
    /**< Capture create time parameters. */
    Vps_CaptCreateStatus  captCreateStatus;
    /**< Capture create status returned by driver during Fvid2_create(). */

    Vps_DispCreateParams  dispCreatePrms;
    /**< Display create time parameters. */
    Vps_DispCreateStatus  dispCreateStatus;
    /**< Display create status returned by driver during Fvid2_create(). */

    Vps_CaptVipParams     vipPrms;
    /**< VIP hardware specific parameters. */
    Vps_VipPortConfig     vipPortCfg;
    /**< VIP port configuration. */
    Vps_CaptVipScParams   vipScPrms;
    /**< SC configuration. */

    Vps_DispDssParams     dispDssPrms;
    /**< DSS driver parameters. */
    Vps_DssDispcVidConfig dispVidCfg;
    /**< DSS video configuration. */
    Vps_DssDispcGfxConfig dispGfxCfg;
    /**< DSS graphics configuration. */

    UInt32                maxOutWidth[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutWidth:
     *   This the Maximum Width value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Width of the frame/field that shall be transmitted to the
     *   external buffer. If the captured width received exceeds this then
     *   only maxOutWidth number of pixels per line is transmitted to the
     *   external buffer. */
    UInt32                maxOutHeight[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutHeight:
     *   This the Maximum Height value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Height of the frame/field  that shall be transmitted to the
     *   external buffer. If the captured height received exceeds this then
     *   only maxOutHeight number of lines is transmitted to the external
     *   buffer.
     */

    Fvid2_Handle               captDrvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams             captCbPrms;
    /**< Capture callback params. */

    Fvid2_Handle               dispDrvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams             dispCbPrms;
    /**< Display callback params. */

    Vps_DssDispcOvlyPipeConfig ovlPipeCfg;
    /** <Pipe Config. */

    Fvid2_Frame                captFrames[LPBK_APP_CAPT_MAX_FRM];
    /**< FVID2 Frames that will be used for capture. */
    LpbkApp_FrameInfo          captFrameInfo[LPBK_APP_CAPT_MAX_FRM];
    /**< Even field frame info. */
    Fvid2_Frame                captFramesOdd[LPBK_APP_CAPT_MAX_FRM];
    /**< FVID2 Frames to hold odd field address. */
    LpbkApp_FrameInfo          captFrameInfoOdd[LPBK_APP_CAPT_MAX_FRM];
    /**< Odd field frame info. */
    Fvid2_Format               captAllocFmt;
    /**< Capture format passed to utils frame alloc function. */
    Fvid2_Frame                captDropFrame;
    /**< Capture drop field to recover from field swap. */
    Bool                       isDropFrmWithDriver;
    /**< Flag to indicate whether drop frame is with driver or with app. */

    Fvid2_Frame                dispFrames[LPBK_APP_DISP_MAX_FRM];
    /**< FVID2 Frames that will be used for display. */
    Fvid2_Format               dispAllocFmt;
    /**< Display Format passed to utils frame alloc function. */

    Fvid2_Handle               decHandle;
    /**< FVID2 decoder/sensor driver handle. */
    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */

    Bsp_VidDecCreateParams     decCreatePrms;
    /**< Video decoder create params. */
    Bsp_VidDecVideoModeParams  decVideoModePrms;
    /**< Video decoder mode params. */
    Bsp_VidSensorCreateParams  sensorCreatePrms;
    /**< Video sensor create params. */

    LpbkApp_Obj               *appObj;
    /**< Reference pointer to application common object. */
    UInt32                     overflowCount;
};

/**
 *  \brief Test application data structure.
 */
struct LpbkApp_Obj_t
{
    LpbkApp_InstObj             instObj[VPS_CAPT_INST_MAX + VPS_DISP_INST_MAX];
    /**< Driver instance objects. */
    LpbkApp_TestParams          testPrms;
    /**< Current test parameters. */

    Fvid2_Handle                fvidHandleAll;
    /**< Global capture handle. */
    Fvid2_Handle                dctrlHandle;
    /**< DCTRL handle. */
    Fvid2_Handle                hdmiHandle;
    /**< Off-Chip HDMI handle. */

    Task_Handle                 tskHandle;
    /**< Test task handle. */

    Task_Handle                 resetTskHandle;
    /**< Reset task handle. */

    Vps_DctrlConfig             dctrlCfg;
    /**< DCTRL path config. */

    Vps_DssDispcOvlyPanelConfig panelCfg;
    /** <Panel Config. */

    Bsp_LcdCtrlCreateParams     lcdCtrlCreatePrms;
    /**< LCD controller Create params. */

    Fvid2_Handle                lcdCtrlHandle;
    /**< LCD controller Driver handle. */
    Bsp_LcdCtrlPanelInfo        lcdPanelInfo;
    /**< LCD panel timing data. */

    UInt32                      maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                      maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                      totalCaptFldCount;
    /**< Count of all frames captured. */
    UInt32                      totalDispCount;
    /**< Count of all frames displayed. */
    UInt32                      totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                      cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32                      callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    UInt32                      enableAutoRun;
    /**< Auto-run enable flag. */

    UInt32                      startTime;
    /**< Application start time in clock ticks. */

    volatile UInt32             curCaptInstance;
    /**< Current capture instance whihc goes to display -used in multi-capture
     *   to single display use case. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern BspOsal_SemHandle overflowSem;

void LpbkApp_runTest(LpbkApp_Obj *appObj, const LpbkApp_TestParams *testPrms);

Int32 LpbkApp_configureVideoPllAndClkSrc(LpbkApp_Obj *appObj, UInt32 pixelClk);

Int32 LpbkApp_overflowCbFxn(LpbkApp_InstObj *appObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef LOOPBACK_PRIV_H_ */
