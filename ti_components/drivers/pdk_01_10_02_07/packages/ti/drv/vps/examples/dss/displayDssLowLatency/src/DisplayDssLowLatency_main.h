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
 *  \file displayDssLowLatency_main.h
 *
 *  \brief DSS Display driver low latency sample application private header file.
 *
 */

#ifndef DISPLAY_DSS_LOW_LATENCY_MAIN_H_
#define DISPLAY_DSS_LOW_LATENCY_MAIN_H_

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
#define APP_NAME                        "DISP_DSS_LOW_LATENCY_APP"

/* Number of frames per handle to allocate */
#define DISP_APP_MAX_FRAMES_PER_HANDLE  (2U)
/* Number of frames per handle to prime before start */
#define DISP_APP_NUM_FRAMES_TO_PRIME    (1U)

/* LCD FPS */
#define DISP_APP_LCD_FPS                (60U)
/* Queue delay in ms - this replicates the procesing time */
#define DISP_APP_QUEUE_DELAY            (15U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define DISP_APP_RUN_COUNT              (2U)

/* Number of timestamp log - Total frame count + some extra */
#define DISP_APP_NUM_LOG_ENTRIES        ((DISP_APP_RUN_COUNT * DISP_APP_LCD_FPS) \
                                          + 10U)
#define DISP_APP_NUM_EVT_LOG_ENTRIES    (DISP_APP_NUM_LOG_ENTRIES * \
                                        DISP_APP_DSS_MAX_EVT)

/* Buffer width in pixels to allocate. */
#define DISP_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define DISP_APP_BUF_HEIGHT             (1080U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define DISP_APP_USE_LCD_WIDTH          (800U)
#define DISP_APP_USE_LCD_HEIGHT         (480U)

/* Padding required for allocating extra memory. */
#define DISP_APP_PADDING_LINES          (0U)

/* Functional Clk Frequency of DSS */
#define DISP_APP_DSS_FUNC_CLK           (192000U)

/* All event type */
#define DISP_APP_DSS_QUE_EVT            (0U)
#define DISP_APP_DSS_ISR_EVT            (1U)
#define DISP_APP_DSS_DQUE_EVT           (2U)
#define DISP_APP_DSS_MAX_EVT            (3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct DispApp_Obj_t DispApp_Obj;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char            *testDescStr;
    /**< Test description. */

    UInt32           encDrvId;
    /**< Video encoder driver ID to open for each handle. */
    UInt32           vencId;
    /**< Venc ID for each handle. */
    Fvid2_Standard   standard;
    /**< Video encoder video standard. */

    UInt32           instId;
    /**< Instance ID to open for each handle. */

    Fvid2_DataFormat inDataFmt;
    /**< YUV or RGB data format. */

    UInt32           inWidth;
    /**< Input buffer resolution width in pixels. */
    UInt32           inHeight;
    /**< Input buffer resolution height in lines. */
    UInt32           posx;
    /**< Input buffer position x. */
    UInt32           posy;
    /**< Input buffer position y. */
    UInt32           inScanFormat;
    /**< In scan format. */
    UInt32           isFieldMerge;
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

    Semaphore_Handle           cbSem;
    /**< Callback complete semaphore used to sync between callback and task. */

    Vps_DssDispcOvlyPipeConfig ovlpipeconfig;
    /** <Pipe Config. */

    Fvid2_Frame                frames[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for display. */
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
    UInt32                     inScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    UInt32                     posx;
    /**< Input buffer position x. */
    UInt32                     posy;
    /**< Input buffer position y. */

    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */

    DispApp_Obj               *appObj;
    /**< Reference pointer to application common object. */
} DispApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct DispApp_Obj_t
{
    DispApp_InstObj             instObj;
    /**< Driver instance objects. */
    DispApp_TestParams          testPrms;
    /**< Current test parameters. */

    Fvid2_Handle                dctrlHandle;
    /**< DCTRL handle. */
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
    UInt32                      allTime[DISP_APP_NUM_LOG_ENTRIES *
                                        DISP_APP_DSS_MAX_EVT];
    /**< Time stamp of all events. */
    UInt32                      evtType[DISP_APP_NUM_EVT_LOG_ENTRIES];
    /**< Event type. */
    UInt32                      isrTime[DISP_APP_NUM_LOG_ENTRIES];
    /**< ISR time stamp. */
    UInt32                      queueTime[DISP_APP_NUM_LOG_ENTRIES];
    /**< Queue time stamp. */
    UInt32                      dequeueTime[DISP_APP_NUM_LOG_ENTRIES];
    /**< De-Queue time stamp. */
    UInt32                      allTimeIdx;
    /**< All time stamp index. */
    UInt32                      isrTimeIdx;
    /**< ISR time stamp index. */
    UInt32                      queueTimeIdx;
    /**< Queue time stamp index. */
    UInt32                      dequeueTimeIdx;
    /**< De-Queue time stamp index. */
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
    {1920U, 1080U, 3840U, FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE,
     FALSE, DISP_APP_MAX_FRAMES_PER_HANDLE},
};

/* None */
static const DispApp_TestParams gDispAppTestPrms[] =
{
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> LCD",
        /* encDrvId */
        FVID2_LCD_CTRL_DRV,
        /* vencId */
        VPS_DCTRL_DSS_VENC_LCD1,
        /* standard */
        FVID2_STD_CUSTOM,
        /* instId */
        VPS_DISP_INST_DSS_VID1,
        /* inDataFmt */
        FVID2_DF_YUV422I_YUYV,
        /* inWidth */
        DISP_APP_USE_LCD_WIDTH,
        /* inHeight */
        DISP_APP_USE_LCD_HEIGHT,
        /* Posx*/
        0U,
        /* Poxy*/
        0U,
        /* Scan Format */
        FVID2_SF_PROGRESSIVE,
        /* Field Merge */
        FALSE,
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_BASE_TDA2PX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
};

#define DISP_APP_NUM_TESTS              (sizeof (gDispAppTestPrms) / \
                                         sizeof (gDispAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef DISPLAY_DSS_LOW_LATENCY_MAIN_H_ */
