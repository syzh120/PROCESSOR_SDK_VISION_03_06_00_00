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
 *  \file st_vpe.h
 *
 *  \brief This file contains all the structures, macros, enums
 *  used by the VPE UT applications.
 */

#ifndef _ST_VPE_H_
#define _ST_VPE_H_

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

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vpe/vps_m2m.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of input buffers to allocate. */
#define VPE_MAX_IN_BUFFERS              (20u)

/* Number of output buffers to allocate. */
#define VPE_MAX_OUT_BUFFERS             (VPE_MAX_IN_BUFFERS)

/* Maximum number of handle for memory allocation. */
#define ST_VPE_MAX_HANDLE               (VPS_M2M_MAX_HANDLE_PER_INST * \
                                         VPS_M2M_VPE_INST_MAX)

/* Maximum number of channels for memory allocation. */
#define ST_VPE_MAX_CH                   (VPS_M2M_MAX_CH_PER_INST * \
                                         VPS_M2M_VPE_INST_MAX)

/* Maximum number of buffers to allocate. */
#define ST_VPE_MAX_BUFFERS              (20u)

/* File path size. */
#define ST_VPE_MAX_FILE_PATH_STRING     (100u)

/* Application name string used in print statements. */
#define APP_NAME                        "ST_VPE"

/* VPE processing clock in MHz */
#define ST_VPE_CLK_TI814X               (200u)
#define ST_VPE_CLK_TDA2XX               (266u)

/* Expected performance - in percentage of processing power of VPE */
#define ST_VPE_EXPECTED_PERFORMANCE     (85u)

/* Default values */
#define ST_VPE_USE_DEF                  (0xFAFAFAFAu)
#define DEF_LOOP_CNT_EVM                (2000u)
#define DEF_LOOP_CNT                    (10u)   /* For Zebu/Sim */
#define DEF_START_STOP_CNT              (1u)
#define DEF_OPEN_CLOSE_CNT              (1u)
#define DEF_FRAME_SWITCH_RATE           (1u)
#define DEF_QUEUE_LEN_PER_CH            (VPS_M2M_DEF_QUEUE_LEN_PER_CH)

/* Loop and start/stop count used for start/stop test case */
#define LOOP_CNT_SS                     (1u)
#define START_STOP_CNT_SS               (1000u)

/* Loop, start/stop and open/close count used for open/close test cases */
#define LOOP_CNT_OC                     (1u)
#define START_STOP_CNT_OC               (5u)
#define OPEN_CLOSE_CNT_OC               (200u)

/* Loop count used for timestamp test cases */
#define LOOP_CNT_TIMESTAMP              (10u)

#define ST_VPE_TEST                     (0x00000001)
#define ST_VPE_CTRL_TEST                (0x00000010)

/* Number of FVID2 frame list to allocate per process list. */
#define VPE_NUM_FRAMELIST_PER_PLIST     (2u)

/* Number of FVID2 frame object to allocate per framelist. */
#define VPE_NUM_FRAMES_PER_LIST         (VPS_M2M_MAX_CH_PER_HANDLE)

/* Maximum number of buffer that would required to be submitted before the
 * first buffer is returned back */
#define VPE_NO_OF_BUF_REQ_BEFORE_RES    (3u)

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
    ST_VPE_TCT_LOAD_BUFFER = 0,
    ST_VPE_TCT_FREE_BUFFER,
    ST_VPE_TCT_MAIN,
    ST_VPE_TCT_HALT
} st_VpeTestCaseType;

/**
 *  VPE UT channel config IDs.
 */
typedef enum
{
    ST_VPE_CCID_NONE,
    /**< No channel configuration. */

    /*
     * YUYV422I to YUYV422I, DEI OFF
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_WXGA_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
    ST_VPE_CCID_CIF_YUYV422I_TO_D1_YUYV422I_P_TO_P,
    ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUYV422I_P_TO_P_4SUBFRM,

    /*
     * YUYV422I to YUYV422I, DEI ON
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_I_TO_P,

    /*
     * YUV420SPUV to YUYV422I, DEI OFF
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_WXGA_YUV420SPUV_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P,
    ST_VPE_CCID_CIF_YUV420SPUV_TO_D1_YUYV422I_P_TO_P,

    /*
     * YUV420SPUV to YUYV422I, DEI ON
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUYV422I_I_TO_P,

    /*
     * YUV422SPUV to YUYV422I, DEI OFF
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_P_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_WXGA_YUV422SPUV_TO_1080P_YUYV422I_P_TO_P,
    ST_VPE_CCID_CIF_YUV422SPUV_TO_D1_YUYV422I_P_TO_P,

    /*
     * YUV422SPUV to YUYV422I, DEI ON
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_I_TO_P,
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUYV422I_I_TO_P,

    /*
     * YUYV422I to YUV420SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_P_TO_P,

    /*
     * YUYV422I to YUV420SPUV, DEI ON
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_I_TO_P,

    /*
     * YUYV422I to YUV422SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_P_TO_P,

    /*
     * YUYV422I to YUV422SPUV, DEI ON
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_I_TO_P,

    /*
     * YUYV422I to RGB888, DEI OFF
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_P_TO_P,
    ST_VPE_CCID_1080P_YUYV422I_TO_1080P_RGB888_P_TO_P,

    /*
     * YUYV422I to RGB888, DEI ON
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_I_TO_P,

    /*
     * YUYV422I to YUV444I, DEI OFF
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_P_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_P_TO_P,
    ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUV444I_P_TO_P,

    /*
     * YUYV422I to YUV444I, DEI ON
     */
    ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_I_TO_P,
    ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_I_TO_P,

    /*
     * YUV420SPUV to YUV420SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV420SPUV_P_TO_P,

    /*
     * YUV420SPUV to YUV422SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV422SPUV_P_TO_P,

    /*
     * YUV420SPUV to RGB888, DEI OFF
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_RGB888_P_TO_P,

    /*
     * YUV420SPUV to YUV444I, DEI OFF
     */
    ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV444I_P_TO_P,

    /*
     * YUV422SPUV to YUV420SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV420SPUV_P_TO_P,

    /*
     * YUV422SPUV to YUV422SPUV, DEI OFF
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV422SPUV_P_TO_P,

    /*
     * YUV422SPUV to RGB888, DEI OFF
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_RGB888_P_TO_P,

    /*
     * YUV422SPUV to YUV444I, DEI OFF
     */
    ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV444I_P_TO_P
} st_VpeChCfgId;

/**
 *  VPE UT handle config IDs.
 */
typedef enum
{
    ST_VPE_HCID_NONE,
    ST_VPE_HCID_DEFAULT,
    ST_VPE_HCID_START_STOP,
    ST_VPE_HCID_OPEN_CLOSE,
    ST_VPE_HCID_MISC_ISR_CTX,
    ST_VPE_HCID_MISC_TIMESTAMP,
    ST_VPE_HCID_MISC_ASYNCQ,
    ST_VPE_HCID_MISC_FRAMEDROP_ALTERNATE
} st_VpeHandleCfgId;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Forward declaration. */
typedef struct st_SystemCtrl_t st_SystemCtrl;

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
    UInt32 numBuffers;
    /**< Number of buffers. */
} st_VpeLoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8           *bufAddr;
    /**< Buffer address. */
    UInt32           bufSize;
    /**< One buffer size in bytes. */
    UInt32           totalBufSize;
    /**< Total buffer size in bytes. */
    void            *yBufAddrEven[ST_VPE_MAX_BUFFERS];
    /**< Pointer to even luma for each buffer. */
    void            *yBufAddrOdd[ST_VPE_MAX_BUFFERS];
    /**< Pointer to odd luma for each buffer. */
    void            *cBufAddrEven[ST_VPE_MAX_BUFFERS];
    /**< Pointer to even chroma for each buffer. */
    void            *cBufAddrOdd[ST_VPE_MAX_BUFFERS];
    /**< Pointer to odd chroma for each buffer. */
    st_VpeLoadBufCfg bufCfg;
    /**< Buffer configuration. */
} st_VpeBufInfo;

/**
 *  \brief Test parameters for a channel.
 */
typedef struct
{
    st_VpeChCfgId      chCfgId;
    /**< Channel configuration ID. */

    UInt32             inWidth;
    /**< Input width in pixels. */
    UInt32             inHeight;
    /**< Input height. */
    UInt32             inDataFmt;
    /**< VPE input data format. */

    UInt32             outWidth;
    /**< VPE output width in pixels. */
    UInt32             outHeight;
    /**< VPE output height. */
    UInt32             outDataFmt;
    /**< VPE output data format. */

    UInt32             inScanFmt;
    /**< VPE input scan format. */
    UInt32             outScanFmt;
    /**< VPE output scan format. */

    UInt32             inMemType;
    /**< VPDMA Memory type for the VPE input frame.
     *   For valid values see #Vps_VpdmaMemoryType. */
    UInt32             outMemType;
    /**< VPDMA Memory type for the VPE writeback output frame.
     *   For valid values see #Vps_VpdmaMemoryType. */

    Vps_DeiConfig      deiCfg;
    /**< Pointer to the deinterlacer configuration used for
     *  VPE drivers. */

    Vps_ScConfig       scCfg;
    /**< Pointer to the scaler parameters like crop and scaler type for the
     *   scaler in VPE path. */
    Fvid2_CropConfig   scCropCfg;
    /**< Pointer to the cropping configuration for the VPE scaler. */
    Vps_SubFrameParams subFrmPrms;
    /**< SubFrame mode parameters. */
    UInt32             numSubFrmPerFrm;
    /**< Number of sub frames in a frame. */
} st_VpeChCfg;

/**
 *  \brief Test parameters for a handle.
 */
typedef struct
{
    st_VpeHandleCfgId handleCfgId;
    /**< Channel configuration ID. */

    UInt32            chInQueueLength;
    /**< Maximum number of request/frame per channel that can be submitted
     *   for M2M operation without having to dequeue the requests. */
    UInt32            isDeiFmdEnable;
    /**< Flag to indicate whether DEI FMD is enabled or not. */

    UInt32            loopCnt;
    /**< Loop count for the app. */
    UInt32            startStopCnt;
    /**< Start stop count for the app. */
    UInt32            openCloseCnt;
    /**< Number of times to do open/close operation. */
    UInt32            frameSwitchRate;
    /**< Input frames will be increment only every this many frames. */
    Bool              taskCtxEnable;
    /**< Queue dequeue from task context or ISR context. */
    Bool              timeStampEnable;
    /**< Bool for the timestamp print or not. */
    Bool              prfEnable;
    /**< Enable performance prints. */
    Bool              asyncQueEnable;
    /**< Aysnchrounous queue or synchronous queue. */
    Bool              frmDropEnable;
    /**< Frame drop enable test case for output buffer. */
    UInt32            frmDropPattern;
    /**< Each bit (0 to 29) represents whether to drop a frame or not for the
     *   corresponding queue count for a channel modulo 30
     *   1 - Drop frame
     *   0 - Process frame. */
} st_VpeHandleCfg;

/**
 *  \brief Test case parameter structure.
 */
typedef struct
{
    Bool                    enableTest;
    /**< Whether test case should be executed or not. */
    UInt32                  testCaseId;
    /**< Tesd case ID. */
    st_VpeTestCaseType      testCaseType;
    /**< Type of test case to run. */
    char                   *reqId;
    /**< Requirements covered by this test case. */
    char                   *testCaseName;
    /**< Test case name. */
    char                   *disableReason;
    /**< Reason string for disabling a test case. */
    UInt32                  numHandles;
    /**< Number of handles to test. */
    Int32                   drvInst[ST_VPE_MAX_HANDLE];
    /**< Instance ID of the driver. */
    st_VpeHandleCfgId       handleCfgId[ST_VPE_MAX_HANDLE];
    /**< VPE handle config IDs for each of the handle. */
    UInt32                  numCh[ST_VPE_MAX_HANDLE];
    /**< Number of channels per handle to test. */
    st_VpeChCfgId           chCfgId[ST_VPE_MAX_CH];
    /**< VPE channel config IDs for all the handles.
     *   Handle 0 channel configs will be first (0 to (numCh[0] - 1)),
     *   (numCh[0] to (numCh[1] - 1)) and so on. */
    const st_VpeLoadBufCfg *loadBufCfg;
    /**< Load/free buffer test case config. */
    UInt32                  lazyLoadingEnable;
    /**< Flag to indicate whether lazy loading of scaler coefficients is
     *   to be enabled. */
    Bool                    printEnable;
    /**< Enable/disable print statements, used for stress testing. */
    UInt32                  testType;
    /**< Type of test  - like BFT, stress etc... */
    Bool                    crcCheckEnable;
    /**< Flag to indicate whether to perform CRC check for this testcase. */
    UInt32                  crcValue[ST_VPE_MAX_CH];
    /**< Pre calculated CRC value of the output buffer. Used to check the
     *   content of the output buffers. */

    /*
     * Below variables are initialized in code and not in table!!
     */
    Bool                    isRun;
    /**< Flag to indicate whether the test case is run or not. */
    Int32                   testResult;
    /**< Test result. */
} st_VpeTestCaseParams;

/**
 *  \brief VPE channel object.
 */
typedef struct
{
    UInt32             chId;
    /**< Channel ID. */
    st_VpeChCfg        chCfg;
    /**< Channel configuration. */

    st_VpeBufInfo     *inBufInfo;
    /**< Input buffer information. */
    UInt32             numOutBuffers;
    /**< Number of output buffers. */
    UInt8             *outSaveBuf;
    /**< VPE writeback out buffer used to store the output video frames. */
    UInt32             outSaveBufSize;
    /**< Size of output buffer. */

    UInt32             outPitchY;
    /**< Luma output buffer pitch in bytes. */
    UInt32             outPitchCbCr;
    /**< Chroma output buffer pitch in bytes - used in semiplanar format. */

    UInt8             *outBufY[VPE_MAX_OUT_BUFFERS];
    /**< Output luma buffer. */
    UInt8             *outBufCbCr[VPE_MAX_OUT_BUFFERS];
    /**< Output chroma buffer. */

    Vps_M2mVpeParams   vpePrms;
    /**< M2M VPE driver channel parameter. */

    UInt32             inBufIdx;
    /**< Current input buffer index. Used to wrap around input buffer. */
    UInt32             outBufIdx;
    /**< Current output buffer index. Used to wrap around output buffer. */
    UInt32             fid;
    /**< Software FID. */
    UInt32             submittedFrames;
    /**< Number of submitted frames. */

    Fvid2_Frame        cntxFrames[VPE_NO_OF_BUF_REQ_BEFORE_RES];
    /**< Place holder for FVID2_frame containers. */
    UInt32             freeCntxFrameIndex;
    /**< Counter to indicate used FRAME containers. */

    UInt32             deiBypassFlag;
    /**< DEI bypass flag. */

    Fvid2_SubFrameInfo subFrameInfoIn;
    Fvid2_SubFrameInfo subFrameInfoOut;
    /**< Memory for SubFrame level processing information exchange between
     *   application and driver.*/
    UInt32             subFrmIdx;
    /**< To store the sub frame index within a frame - goes from 0 to
     *   (numSubFrmPerFrm - 1). */
    UInt64             processedPixels;
    /**< Number of pixels processed for this run. This is used in performance
     *   calculation. */
} st_VpeChObj;

/**
 *  \brief VPE handle object.
 */
typedef struct
{
    const st_VpeTestCaseParams *testPrms;
    /**< Pointer to test params for reference. */
    UInt32                      taskId;
    /**< Task ID. */
    Int32                       testResult;
    /**< Test Result. Based on this testbench will print Pass/Fail. */
    UInt32                      mps;
    /**< Mega pixels per second processed for this run. */

    Int32                       drvInst;
    /**< Instance ID of the driver to open. */
    st_VpeHandleCfg             handleCfg;
    /**< Handle configuration. */

    const st_SystemCtrl        *sysCtrl;
    /**< Pointer to system control. */
    UInt32                      traceMask;
    /**< Masks for the debug prints. */

    UInt32                      startChIdx;
    /**< Index into the channel config for all the handles. */
    UInt32                      numCh;
    /**< Number of channels for this handle. */
    st_VpeChObj                 chObj[VPS_M2M_MAX_CH_PER_HANDLE];
    /**< Channel object. */

    Fvid2_Handle                fvidHandle;
    /**< VPE driver handle. */
    BspUtils_PrfTsHndl         *prfTsHandle;
    /**< Performance utils handle. */
    Semaphore_Handle            reqCompleteSem;
    /**< Request complete semaphore used to sync between callback and task. */

    Vps_M2mCreateParams         createPrms;
    /**< M2M driver create parameters. */
    Vps_M2mCreateStatus         createStatus;
    /**< M2M driver create status. */

    Fvid2_CbParams              cbParams;
    /**< Callback params. */

    UInt32                      completedLoopCnt;
    /**< Total number of completed frames. */

    Fvid2_ProcessList           processList;
    /**< Process list used for queue/dequeue operations. */
    Fvid2_FrameList             frameList[VPE_NUM_FRAMELIST_PER_PLIST];
    /**< Frame list used for queue/dequeue operations. */
    Fvid2_Frame                 frames[VPE_NUM_FRAMELIST_PER_PLIST]
    [VPE_NUM_FRAMES_PER_LIST];
    /**< Frames used for queue/dequeue operations. */

    Fvid2_ProcessList           errProcessList;
    /**< Process list used for error operations. */

    UInt32                      drvPrevTimeStamp;
    /**< Previous frame time stamp in micro second. */
    UInt32                      minCbTime;
    /**< Minimum duration between driver callback in ms. */
    UInt32                      maxCbTime;
    /**< Maximum duration between driver callback in ms. */
    UInt32                      totalCbTime;
    /**< Summation of callback duration to calculate average in ms. */
    UInt32                      totalCbCount;
    /**< Total number of callback count to calculate average in ms. */
    Uint32                      lastCbTime;
    /**< Last callback duration in ms. */

    Clock_Handle                asyncClkHandle;
    /**< Clock Handle for Async Queue-Dequeu. */
    Bool                        asyncTimerOn;
    /**< Flag to indicate whether Async clock is on. */
    UInt32                      asyncCbCnt;
    /**< Number of times call back trigerred between timer expiry. */
    UInt32                      asyncTimerValue;
    /**< Timer value for asynchronous timer. */

    Bsp_PlatformId              platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev          cpuRev;
    /**< CPU version identifier. */
    Bsp_BoardId                 boardId;
    /**< Board identifier. */
} st_VpeHandleObj;

/**
 *  \brief Structure used for allocating RT params.
 */
typedef struct
{
    Vps_FrameParams  inFrmPrms;
    /**< Frame params for VPE input frame. */
    Vps_FrameParams  outFrmPrms;
    /**< Frame params for VPE writeback output frame. */
    Fvid2_CropConfig scCropCfg;
    /**< Scaler crop configuration for VPE scaler. */
    Vps_ScRtConfig   scRtCfg;
    /**< Scaler runtime configuration for VPE scaler. */
    Vps_DeiRtConfig  deiRtCfg;
    /**< DEI runtime configuration. */
} st_VpeRtObj;

/**
 *  \brief Structure used for VPE UT control parameters.
 */
struct st_SystemCtrl_t
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
    /**< Default frame switch rate. */
    UInt32 chInQueueLength;
    /**< Default channel input queue length. */
    UInt32 rtPrintEnable;
    /**< Enables runtime remote prints like VENC underflow status etc. */
    Bool   fileIoEnable;
    /**< Enables/disabled output file writes through CCS file I/O. */
    Char   filePath[ST_VPE_MAX_FILE_PATH_STRING];
    /**< File path. */
};

/**
 *  \brief Structure used for VPE UT object common for all the tasks.
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
} st_VpeUtObj;

/**
 *  \brief Structure used for storing AYSNC test case info.
 */
typedef struct
{
    UInt32       cbCnt;
    /**< Number of time call back triggered between timer ticks. */
    UInt32       timerOn;
    /**< Flag to indicate whether the clock is on or not. */
    Clock_Handle clkObj;
    /**< Clock handle. */
} st_VpeAsyncProcess;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Parser functions
 */
Int32 st_vpeParser(void);

/*
 * VPE test case functions
 */
Int32 st_vpeMainTestCase(st_VpeHandleObj *hObj);

/*
 * VPE common functions
 */
Int32 st_vpeInitVariables(st_VpeHandleObj *hObj);
void st_vpeFreeVariables(st_VpeHandleObj *hObj);

void st_vpePrintChPrms(const st_VpeHandleObj *hObj);
void st_vpePrintM2mVpeCreateStatus(const st_VpeHandleObj     *hObj,
                                   const Vps_M2mCreateStatus *createStatus);
Int32 st_vpeCalcPerformance(st_VpeHandleObj *hObj, UInt32 durationMs);
Int32 st_vpePrintTimeStatus(st_VpeHandleObj *hObj, Bool rtPrintEnable);
Int32 st_vpeCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                          UInt32                        traceMask);

Int32 st_vpeProgramScCoeff(st_VpeHandleObj *hObj);

Int32 st_vpeLoadBuf(const st_VpeUtObj *utObj, const st_VpeLoadBufCfg *cfg);
Int32 st_vpeFreeBuf(const st_VpeUtObj *utObj, const st_VpeLoadBufCfg *cfg);
st_VpeBufInfo *st_vpeGetBufInfo(UInt32 dataFmt,
                                UInt32 scanFmt,
                                UInt32 traceMask);

void st_logTestResult(const st_VpeUtObj *utObj,
                      Int32              testResult,
                      UInt32             testCaseId,
                      char              *testcaseInfo);
void st_printTestResult(const st_VpeUtObj *utObj,
                        UInt32             skipCount,
                        UInt32             disableCount);
void st_resetTestResult(void);
UInt32 st_calcBufferCrc(UInt8 *bufPtr, UInt32 numBytes);

static inline UInt32 st_vpeGetMax(UInt32 a, UInt32 b)
{
    UInt32 max;

    max = a;
    if (b > a)
    {
        max = b;
    }

    return (max);
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _ST_VPE_H_ */
