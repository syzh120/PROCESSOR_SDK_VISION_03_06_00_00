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
 *  \file displayDss_main.h
 *
 *  \brief DSS Display driver sample application private header file.
 *
 */

#ifndef DISPLAY_DSS_MAIN_H_
#define DISPLAY_DSS_MAIN_H_

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
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_lcdController.h>
#include <ti/drv/vps/include/devices/bsp_sii9022a.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define DISP_APP_TSK_STACK_MAIN         (10U * 1024U)

/* Test application task priority */
#define DISP_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "DISP_DSS_APP"

/* Worst case frames per handle */
#define DISP_APP_MAX_FRAMES_PER_HANDLE  (4U)

/* Padding required for allocating extra memory. */
#define DISP_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define DISP_APP_RUN_COUNT              (30U)

/* Buffer width in pixels to allocate. */
#define DISP_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define DISP_APP_BUF_HEIGHT             (1080U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define DISP_APP_USE_LCD_WIDTH          (800U)
#define DISP_APP_USE_LCD_HEIGHT         (480U)

/* Functinal Clk Frequency of DSS */
#define DISP_APP_DSS_FUNC_CLK           (192000U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief RT parameters update configuration.
 *  This structures holds the parameters to change the DSS configuration per
 *  frame before queueing to the DSS driver. Driver is expected to display the
 *  frame with the updated configuration.
 */
typedef struct
{
    Int32  inWidthDecCnt;
    /**<  number of pixels to be decremented from inWidth in RT Params. */
    Int32  inHeightDecCnt;
    /**<  number of pixels to be decremented from inHeight in RT Params. */
    Int32  outWidthDecCnt;
    /**<  number of pixels to be decremented from outWidth in RT Params. */
    Int32  outHeightDecCnt;
    /**<  number of pixels to be decremented from outHeight in RT Params. */
    Int32  posxIncCnt;
    /**<  position count to be incremented from previous posX in RT Params. */
    Int32  posyIncCnt;
    /**<  position count to be incremented from previous posY in RT Params. */
    UInt32 rtPramDisplayFrameCnt;
    /**<  number of frames to be displayed with current pattern. */
    UInt32 currentFrameCnt;
    /**<  varaible to hold current frame count with current pattern. */
    UInt32 patternNum;
    /**<  variable to hold the current pattern number. */
}DispApp_rtParamPattern;

/** \brief Forward declaration for common object. */
typedef struct DispApp_Obj_t DispApp_Obj;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    UInt32           testCaseId;
    /**< Test case id. */
    Char            *testDescStr;
    /**< Test description. */

    UInt32           numEnc;
    /**< Number of Video Encoders to run with. */
    UInt32           encDrvId[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */
    UInt32           vencId[VPS_DISP_ENC_INST_MAX];
    /**< Venc ID for each handle. */
    Fvid2_Standard   standard[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder video standard. */
    UInt32           isSdVenc;
    /**< True for SD VENC and false for others. Valid only for Tda3xx. */
    UInt32           isRtParamUpdateTest;
    /**< True for RT Param Update testcases and false for others. */

    UInt32           numHandles;
    /**< Number of display handles to run with. */
    UInt32           instId[VPS_DISP_INST_MAX];
    /**< Instance ID to open for each handle. */

    Fvid2_DataFormat inDataFmt[VPS_DISP_INST_MAX];
    /**< YUV or RGB data format. */

    UInt32           inWidth[VPS_DISP_INST_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32           inHeight[VPS_DISP_INST_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32           posx[VPS_DISP_INST_MAX];
    /**< Input buffer position x. */
    UInt32           posy[VPS_DISP_INST_MAX];
    /**< Input buffer position y. */
    UInt32           inScanFormat[VPS_DISP_INST_MAX];
    /**< In scan format. */
    UInt32           isFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */
    Int32            runCount;
    /**< Number of frames to display. */
    Bsp_BoardMode    boardMode;
    /**< Board mode param like 24-bit, 8-bit. */
    UInt32           boardId;
    /**< List of valid boards to run the test case. */
} DispApp_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32                     instId;
    /**< Instance ID. */
    UInt32                     encDrvId;
    /**< Encoder driver ID. */

    Vps_DispCreateParams       createPrms;
    /**< Create time parameters. */
    Vps_DispCreateStatus       createStatus;
    /**< Create status returned by driver during Fvid2_create(). */

    Vps_DispDssParams          dssPrms;
    /**< DSS driver parameters. */
    Vps_DssDispcVidConfig      vidCfg;
    /**< DSS video configuration. */
    Vps_DssDispcGfxConfig      gfxCfg;
    /**< DSS graphics configuration. */

    Fvid2_Handle               drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    Vps_DssDispcOvlyPipeConfig ovlpipeconfig;
    /** <Pipe Config. */

    Fvid2_Frame                frames[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for display3. */
    Vps_DssDispcRtParams       rtParam[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< RT Param to be passed with each of FVID2 Frames. */
    DispApp_rtParamPattern     rtParamPattern;
    /**< RT Param Pattern to be displayed. */
    Fvid2_Format               allocFmt;
    /**< Format passed to utils frame alloc function. */

    UInt32                     pitch[FVID2_MAX_PLANES];
    /**< Buffer pitch - used for buffer allocation for this instance. */

    UInt32                     isFieldMerge;
    /**< Field merge or field separated. */

    UInt32                     inWidth;
    /**< Input buffer resolution width in pixels. */

    UInt32                     inHeight;
    /**< Input buffer resolution height in lines. */

    Fvid2_DataFormat           inDataFmt;
    /**< YUV or RGB data format. */

    UInt32                     posx;
    /**< Input buffer position x. */

    UInt32                     posy;
    /**< Input buffer position y. */

    UInt32                     inScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */
    /* Bsp_VidEncCreateParams    encCreatePrms; */
    /**< Video encoder create params. */
    /* Bsp_VidEncVideoModeParams encVideoModePrms; */
    /**< Video encoder mode params. */

    DispApp_Obj               *appObj;
    /**< Reference pointer to application common object. */
} DispApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct DispApp_Obj_t
{
    DispApp_InstObj             instObj[VPS_DISP_INST_MAX];
    /**< Driver instance objects. */
    DispApp_TestParams          testPrms;
    /**< Current test parameters. */

    Fvid2_Handle                dctrlHandle;
    /**< DCTRL handle. */
    Fvid2_Handle                hdmiHandle;
    /**< Off-Chip HDMI handle. */
    Task_Handle                 tskHandle;
    /**< Test task handle. */

    Vps_DctrlConfig             dctrlCfg;
    /**< DCTRL path config. */

    Vps_DssDispcOvlyPanelConfig panelCfg;
    /** <Panel Config. */

    Bsp_LcdCtrlCreateParams     lcdCtrlCreatePrms;
    /** <LCD controller Create params. */

    Fvid2_Handle                lcdCtrlhdl;
    /**< LCD controller Driver handle. */
    Bsp_LcdCtrlPanelInfo        lcdPanelInfo;
    /**< LCD panel timing data. */

    UInt32                      maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                      maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                      totalFldCount;
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
};

/**
 *  \brief Buffer configuration structure for buffer allocation.
 */
typedef struct
{
    UInt32 width;
    /**< Buffer width in pixels. */
    UInt32 height;
    /**< Buffer height. */
    UInt32 pitch;
    /**< Pitch in bytes. */
    UInt32 dataFmt;
    /**< Data format. */
    UInt32 scanFmt;
    /**< Scan format - interlaced or progressive. */
    Bool   fieldsMerged;
    /**< Fields are merged or separated for the interlaced scan format. */
    UInt32 numBuffers;
    /**< Number of buffers. */
} DispApp_LoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8             *bufAddr;
    /**< Buffer address. */
    UInt32             bufSize;
    /**< One buffer size in bytes. */
    UInt32             totalBufSize;
    /**< Total buffer size in bytes. */
    void              *yBufAddrEven[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to even luma for each buffer. */
    void              *yBufAddrOdd[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to odd luma for each buffer. */
    void              *cBufAddrEven[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to even chroma for each buffer. */
    void              *cBufAddrOdd[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to odd chroma for each buffer. */
    void              *bgrBufAddr[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to BGR data for each buffer. */
    DispApp_LoadBufCfg bufCfg;
    /**< Buffer configuration. */
} DispApp_BufInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const DispApp_LoadBufCfg gDispDssLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, scanFmt, fieldsMerged, numBuffers */
    {1920u, 1080u, 3840u, FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE,
     FALSE,
     DISP_APP_MAX_FRAMES_PER_HANDLE},
    {1920u, 1080u, 5760u, FVID2_DF_BGR24_888,    FVID2_SF_PROGRESSIVE,
     FALSE,
     DISP_APP_MAX_FRAMES_PER_HANDLE},
};

/* None */
static const DispApp_TestParams gDispAppTestPrms[] =
{
    {
        /* Test case id. */
        0U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
    {
        /* Test case id. */
        1U,
        /* testDescStr */
        "DSS                        GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_GFX1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
    {
        /* Test case id. */
        2U,
        /* testDescStr */
        "DSS Video1     (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        2U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_GFX1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
    {
        /* Test case id. */
        3U,
        /* testDescStr */
        "DSS Video1,2   (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        3U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_VID2,
            VPS_DISP_INST_DSS_GFX1
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            360U,
            360U,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            360U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            0U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
    {
        /* Test case id. */
        4U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@1080P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_1080P_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        5U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@480P60(TDM)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_480P,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720U,
        },
        {
            /* inHeight */
            480U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT_TDM,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        6U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@720P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_720P_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1280U,
        },
        {
            /* inHeight */
            720U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        7U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@XGAP60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_XGA_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1024U,
        },
        {
            /* inHeight */
            768U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        8U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@XGAP60 (TDM)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_XGA_DSS_TDM_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1024U,
        },
        {
            /* inHeight */
            768U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        9U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@WXGAP60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_WXGA_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1280U,
        },
        {
            /* inHeight */
            800U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
    {
        /* Test case id. */
        10U,
        /* testDescStr */
        "DSS Video1,2,3 (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        4U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_VID2,
            VPS_DISP_INST_DSS_VID3,
            VPS_DISP_INST_DSS_GFX1
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
            100U,
            100U,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            100U,
            100U,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            150U,
            550U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            300U,
            300U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT * 2,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },

    {
        /* Test case id. */
        11U,
        /* testDescStr */
        "DSS Video2     (YUY422I)                   -> TV   -> HDMI@1080P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_HDMI,
        },
        /* standard[] */
        {
            FVID2_STD_1080P_60,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID2,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA2EX |
         BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
    {

        /* Test case id. */
        12U,
        /* testDescStr */
        "DSS Video2     (YUY422I)                   -> TV   -> HDMI@1080I60",
        /* Num of encoders */
        1U,
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_HDMI,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID2,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA2EX |
         BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
#endif
#if defined (SOC_TDA3XX)
    {
        /* Test case id. */
        13U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SD-VENC(NTSC)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_NTSC,
        },
        /* isSdVenc */
        TRUE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            480,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        14U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SD-VENC(PAL)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_PAL,
        },
        /* isSdVenc */
        TRUE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            576,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        15U,
        /* testDescStr */
        "DSS Video1     (BGR888)                    -> DPI1 -> SD-VENC(NTSC)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_NTSC,
        },
        /* isSdVenc */
        TRUE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            480,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {
        /* Test case id. */
        16U,
        /* testDescStr */
        "DSS Video1     (BGR888)                    -> DPI1 -> SD-VENC(PAL)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_PAL,
        },
        /* isSdVenc */
        TRUE,
        /* isRtParamUpdateTest */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            576,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
#endif
    {
        /* Test case id. */
        17U,
        /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> LCD (RT Param Test)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* isRtParamUpdateTest */
        TRUE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        150,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX | BSP_BOARD_GP_AM572X | BSP_BOARD_IDK_AM57XX),
    },
};

#define DISP_APP_NUM_TESTS              (sizeof (gDispAppTestPrms) / \
                                         sizeof (gDispAppTestPrms[0U]))
#define DISP_APP_AUTORUN_OPT            (50U)
#define DISP_APP_EXIT_OPT               (100U)

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef DISPLAY_DSS_MAIN_H_ */
