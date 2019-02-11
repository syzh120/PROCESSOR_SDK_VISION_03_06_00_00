/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file st_dss.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the DSS UT applications.
 */

#ifndef _ST_DISPDSS_H_
#define _ST_DISPDSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Queue.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_lcdController.h>
#include <ti/drv/vps/include/devices/bsp_sii9022a.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Application name string used in print statements. */
#define UT_NAME                        "ST_DISPDSS"

// #define RT_TEST

/* Maximum number of buffers to allocate. */
#define ST_DISP_DSS_MAX_BUFFERS              (20U)

/* Worst case frames per handle */
#define ST_DISP_DSS_MAX_FRAMES_PER_HANDLE  (4u)

#define ST_DISP_DSS_MAX_HANDLE  (4u)

#define ST_DISP_DSS_TASK_MAX  (5u)

#define ST_DISP_DSS_NUM_TESTCASES  (300u)

/* Buffer width in pixels to allocate. */
 #define ST_DISP_DSS_BUF_WIDTH              (1920u)
// #define ST_DISP_DSS_BUF_WIDTH              (800u)
/* Buffer height in lines to allocate. */
 #define ST_DISP_DSS_BUF_HEIGHT             (1080u)
// #define ST_DISP_DSS_BUF_HEIGHT             (480u)

/* Padding required for allocating extra memory. */
#define ST_DISP_DSS_PADDING_LINES          (0u)
/**
 *  Maximum size of the string to hold file name along with path
 */
#define FILE_NAME_SIZE 255

/**
 *  Macro defining the maximum number of parameters to be parsed from the input
 *  configuration file
 */
#define MAX_ITEMS_TO_PARSE  3000

#define NUM_MESSAGES  7

/* Default values */
// #define DEF_LOOP_CNT_EVM                (60u)
#define DEF_LOOP_CNT_EVM                (10u)
#define DEF_LOOP_CNT                    (10u)   /* For Zebu/Sim */
#define DEF_START_STOP_CNT              (1u)
#define DEF_OPEN_CLOSE_CNT              (1u)
#define ST_DISP_DSS_USE_DEF             (0xFAFAFAFAu)

#define USE_DEF_LP_CNT                  (ST_DISP_DSS_USE_DEF)
#define USE_DEF_SS_CNT                  (ST_DISP_DSS_USE_DEF)
#define USE_DEF_OC_CNT                  (ST_DISP_DSS_USE_DEF)

/** \brief Forward declaration for common object. */
typedef struct st_DispDssAppObj_t st_DispDssAppObj;

/**
 *  \brief DispDss  Nodes
 */
typedef enum
{
    VID1    = 0x0,
    VID2    = 0x1,
    VID3    = 0x2,
    GFX1    = 0x3,
    LCD1    = 0x4,
    LCD2    = 0x5,
    LCD3    = 0x6,
    HDMI    = 0x7,
    DPI1    = 0x8,
    DPI2    = 0x9,
    DPI3    = 0xA,
    HDMIOUT = 0xB
} st_DispDssNodes;

/**
 *  \brief DispDss  Encoder Driver Id
 */
typedef enum
{
    ENC_NOT_REQUIRED = 0x0,
    ENC_ID_LCD       = 0x1,
    ENC_ID_SIL9022A  = 0x2
} st_DispDssEncDrvId;

/**
 *  \brief DispDss  Message Commands
 */
typedef enum
{
    CREATE          = 0x0,
    DELETE          = 0x1,
    START           = 0x2,
    STOP            = 0x3,
    CONTROL         = 0x4,
    QUEUE           = 0x5,
    DEQUEUE         = 0x6,
    ALLOC_AND_QUEUE = 0x7
} st_DispDssMsgCmd;

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
    ST_TT_MISC        = 0x80
} st_TestType;

/**
 *  \brief Test case types.
 */
typedef enum
{
    ST_DISP_DSS_TCT_LOAD_BUFFER = 0,
    ST_DISP_DSS_TCT_FREE_BUFFER,
    ST_DISP_DSS_TCT_MAIN,
    ST_DISP_DSS_TCT_HALT
} st_DispDssTestCaseType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

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
} st_DispDssLoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8               *bufAddr;
    /**< Buffer address. */
    UInt32               bufSize;
    /**< One buffer size in bytes. */
    UInt32               totalBufSize;
    /**< Total buffer size in bytes. */
    void                *yBufAddrEven[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to even luma for each buffer. */
    void                *yBufAddrOdd[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to odd luma for each buffer. */
    void                *cBufAddrEven[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to even chroma for each buffer. */
    void                *cBufAddrOdd[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to odd chroma for each buffer. */
    void                *bgrBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to BGR data for each buffer. */
    void                *abgrBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to ABGR data for each buffer. */
    void                *uyvyBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to even luma for each buffer. */
    void                *bgraBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to BGRA data for each buffer. */
    void                *xbgrBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to XBGR data for each buffer. */
    void                *bgrxBufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to XRGB data for each buffer. */
    void                *bgr16565BufAddr[ST_DISP_DSS_MAX_BUFFERS];
    /**< Pointer to BGR16565 data for each buffer. */
    st_DispDssLoadBufCfg bufCfg;
    /**< Buffer configuration. */
} st_DispDssBufInfo;

/**
 *  \brief Test case parameter structure.
 */
typedef struct
{
    UInt32         testCaseId;
    /**< Tesd case ID. */
    char          *reqId;
    /**< Requirements covered by this test case. */
    char          *testCaseName;
    /**< Reason string for disabling a test case. */
    UInt32         numEnc;
    /**< Number of Video Encoders to run with. */
    UInt32         encDrvId[VPS_DISP_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */
    Fvid2_Standard standard[VPS_DISP_INST_MAX];
    /**< Video encoder video standard. */
    UInt32         isSdVenc[VPS_DISP_INST_MAX];
    /**< True for SD VENC and false for others. Valid only for Tda3xx. */
    UInt32         dispNodeId[VPS_DISP_INST_MAX];
    /**< display Node connected to Venc. */
    UInt32         numHandles;
    /**< Number of handles to test. */
    Int32          drvInst[VPS_DISP_INST_MAX];
    /**< Instance ID of the driver. */
    UInt32         inWidth[VPS_DISP_INST_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32         inHeight[VPS_DISP_INST_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32         posx[VPS_DISP_INST_MAX];
    /**< Input buffer position x. */
    UInt32         posy[VPS_DISP_INST_MAX];
    /**< Input buffer position y. */
    UInt32         inScanFormat[VPS_DISP_INST_MAX];
    /**< In scan format. */
    UInt32         isFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */
    Int32          loopCount;
    Bsp_BoardMode  boardMode[VPS_DISP_INST_MAX];
    /**< Board mode param like 24-bit, 8-bit. */
} st_DispDssTestCaseParams;

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
    Vps_DssDispcAdvDmaConfig    advDmaCfg;
    /**< DMA cfg params for Vid pipe. */
    Vps_DssDispcVidVC1Config    vc1Cfg;
    /**< VC1 Range Config params. */

    Fvid2_Handle               drvHandle;
    /**< FVID2 disp driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    Vps_DssDispcOvlyPipeConfig ovlpipeconfig;
    /** <Pipe Config. */

    Fvid2_Frame                frames[ST_DISP_DSS_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for disp3. */
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

    UInt32                     videoNode;
    /**< videoNode */
    UInt32                     overlayNode;
    /**< overlayNode */
    UInt32                     dispNode;
    /**< dispNode */
    Fvid2_ModeInfo             mInfo;

    UInt32                     frameSwitchRate;
    st_DispDssAppObj          *appObj;
    /**< Reference pointer to application common object. */
} st_DispDssInstObj;

/**
 *  \brief Test application data structure.
 */
struct st_DispDssAppObj_t
{
    st_DispDssInstObj           instObj;
    /**< Driver instance objects. */
    st_DispDssTestCaseParams    testPrms;
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

    Fvid2_Handle                lcdCtrlhdl[VPS_DISP_INST_MAX];
    /** <LCD controller Driver handle. */
    Bsp_LcdCtrlPanelInfo        lcdPanelInfo;
    /**< LCD panel timing data. */

    UInt32                      maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                      maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                      totalFldCount;
    /**< Count of all frames disped. */
    UInt32                      totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                      cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32                      callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    Bool                        enableAutoRun;
    /**< Auto-run enable flag. */

    UInt32                      startTime;
    /**< Application start time in clock ticks. */

    UInt32                      traceMask;
    /**< Masks for the debug prints. */
    Bsp_PlatformId              platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev          cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId                 boardId;
    /**< Board identifier. */
    UInt32                      taskId;
    /**< Board identifier. */
    UInt32                      bufferIndex;

    st_DispDssBufInfo          *bufInfo;
    Int32                       taskResult;
    UInt32                      submittedFrames;
};
/**
 *  \brief Structure used for DSS UT control parameters.
 */
typedef struct
{
    Bool   skipHaltTests;
    /**< Flag to skip the halt test cases. */
    UInt32 loopCnt;
    /**< Default loop count. */
    UInt32 startStopCnt;
    /**< Start stop count for the app. */
    UInt32 openCloseCnt;
    /**< Number of times to do open/close operation. */
    UInt32 frameSwitchRate;
    UInt32 rtPrintEnable;
    /**< Enables runtime remote prints like VENC underflow status etc. */
} st_SystemCtrl;

/**
 *  \brief Structure used for Display DSS UT object common for all the tasks.
 */
typedef struct
{
    st_SystemCtrl       sysCtrl;
    /**< System control information. */

    UInt32              skipCount;
    /**< Number of test cases skipped because of platform/user settings. */
    UInt32              disableCount;
    /**< Number of test cases disabled because of any bug etc. */
    UInt32              traceMask;
    /**< Masks for the debug prints. */
    Bsp_PlatformId      platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev  cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId         boardId;
    /**< Board identifier. */
    UInt32              testCaseIdx;
    UInt32              numTescases;
    BspUtils_PrfTsHndl *prfTsHandle;
    /**< Performance utils handle. */
    UInt32              yuyv422BufCnt;
    UInt32              testCount;
} st_DispDssUtObj;

/**
 *  \brief DispDss Test Configuration data structure.
 */

typedef struct
{
    UInt32 enableTest;
    /**< Test case enabled for Tda2xx Platform */
    UInt32 testCaseId;
    /**< Tesd case ID. */
    UInt32 testCaseType;
    char   reqId[FILE_NAME_SIZE];
    /**< SW reqId for Tda2xx Platform */
    char   testCaseName[FILE_NAME_SIZE];
    /**< Test case name. */
    char   disableReason[FILE_NAME_SIZE];
    Bool   printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    UInt32 testType;
    /**< Type of test  - like BFT, stress etc... */
    Bool   isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32  testResult;
    /**< Test result. */
    UInt32 numInst;
    /**< Number of instance to test. */
} st_DispDssTestCfg;

/**
 *  \brief DssUt Test Instance Configuration data structure.
 */

typedef struct
{
    UInt32                      videoNode;
    /**< videoNode */
    UInt32                      overlayNode;
    /**< overlayNode */
    UInt32                      dispNode;
    /**< dispNode */
    Vps_DispDssParams           dssPrms;
    Vps_DssDispcVidConfig       vidCfg;
    Vps_DssDispcAdvDmaConfig    vidadvDmaCfg;
    Vps_DssDispcVidVC1Config    vidvc1Cfg;
    Vps_DssDispcGfxConfig       gfxCfg;
    Vps_DssDispcAdvDmaConfig    gfxadvDmaCfg;
    Vps_DssDispcOvlyPanelConfig panelCfg;
    Vps_DssDispcOvlyPipeConfig  ovlpipecfg;
    Fvid2_ModeInfo              mInfo;
    UInt32                      loopCnt;
    UInt32                      frameSwitchRate;
    /**< Default loop count. */
    Vps_DssDispcAdvLcdTdmConfig dispcAdvLcdTdmConfig;
    Vps_DctrlOutputInfo         dCtrlOutInfo;
    Bsp_BoardMode               boardMode;
    UInt32                      encDrvId;
    UInt32                      isSdVenc;
    /**< Board mode param like 24-bit, 8-bit. */
    UInt32                      platformSocId;
} st_DispDssTestInstCfg;

/**
 *  \brief Message Commads data structure.
 */

typedef struct
{
    Queue_Elem elem; /* first field for Queue */
    Int32      cmd;  /* Command id */
    UInt32     value;
    char      *val;  /* Command */
} st_DispDssMsgObj;

/* ========================================================================== */
/*                          Global Variables                            */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const st_DispDssLoadBufCfg gDispDssLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, scanFmt, fieldsMerged, numBuffers */
    {1920u, 1080u, 3840u, FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 5760u, FVID2_DF_BGR24_888,    FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 7680,  FVID2_DF_ABGR32_8888,  FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 3840u, FVID2_DF_YUV422I_UYVY, FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 7680,  FVID2_DF_BGRA32_8888,  FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 7680u, FVID2_DF_XBGR24_8888,  FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 7680u, FVID2_DF_BGRX24_8888,  FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 3840u, FVID2_DF_BGR16_565_A8, FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {1920u, 1080u, 1920u, FVID2_DF_YUV420SP_UV,  FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Parser functions
 */
Int32 st_dispDssParser(void);
Int32 st_dispDssParserTest(st_DispDssUtObj *utObj);
void st_printTestResult(const st_DispDssUtObj *utObj,
                        UInt32                 skipCount,
                        UInt32                 disableCount);

void st_logTestResult(const st_DispDssUtObj *utObj,
                      Int32                  testResult,
                      UInt32                 testCaseId,
                      char                  *testcaseInfo);

/*
 * DispDss task functions
 */

void st_dispDssVidPpl1TestTask(UArg arg0, UArg arg1);
void st_dispDssVidPpl2TestTask(UArg arg0, UArg arg1);
void st_dispDssVidPpl3TestTask(UArg arg0, UArg arg1);
void st_dispDssGfxPpl1TestTask(UArg arg0, UArg arg1);
void st_dispDssDctrlTestTask(UArg arg0, UArg arg1);

/*
 * DispDss common functions
 */

Int32 st_dispDssCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                              UInt32                        traceMask);
Int32 st_dispDssFreeBuf(st_DispDssUtObj            *utObj,
                        const st_DispDssLoadBufCfg *cfg);
Int32 st_dispDssLoadBuf(st_DispDssUtObj            *utObj,
                        const st_DispDssLoadBufCfg *cfg);
Int32 st_dispDssGetBufCfgId(UInt32 dataFmt,
                            UInt32 *bufCfgId);

st_DispDssBufInfo *st_dispDssGetBufInfo(st_DispDssAppObj *appObj,
                                        UInt32            dataFmt,
                                        UInt32            scanFmt,
                                        UInt32            fieldsMerged,
                                        UInt32            pitch);
Int32 st_dispDssCreatePhase(st_DispDssAppObj *appObj);
Int32 st_dispDssDeletePhase(st_DispDssAppObj *appObj);
Int32 st_dispDssControlPhase(st_DispDssAppObj *appObj);
Int32 st_dispDssAllocAndQueuePhase(st_DispDssAppObj *appObj);
Int32 st_dispDssStart(st_DispDssAppObj *appObj);
Int32 st_dispDssConfigDctrlPipe(st_DispDssAppObj *appObj);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _ST_DISPDSS_H_ */
