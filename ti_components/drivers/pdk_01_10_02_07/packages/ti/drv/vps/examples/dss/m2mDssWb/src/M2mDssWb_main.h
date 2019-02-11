/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file M2mDssWb_main.h
 *
 *  \brief DSS M2M driver sample application private header file.
 *
 */

#ifndef M2MDSSWB_MAIN_H_
#define M2MDSSWB_MAIN_H_

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
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/dss/vps_m2mDss.h>
#endif
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
#define M2MDSS_APP_TSK_STACK_MAIN           (10U * 1024U)

/* Test application task priority */
#define M2MDSS_APP_TSK_PRI_MAIN             (10U)

#define APP_NAME                            "M2M_DSS_APP"

/* Number of input buffers to allocate. */
#define M2MDSS_APP_NUM_IN_BUFFERS           (4U)
/* Number of output buffers to allocate. */
#define M2MDSS_APP_NUM_OUT_BUFFERS          (4U)

/* Padding required for allocating extra memory. */
#define M2MDSS_APP_PADDING_LINES            (0U)

/* Number of loop count. */
#define M2MDSS_APP_TOTAL_LOOP_COUNT         (1000U)

/* Buffer width in pixels to allocate. */
#define M2MDSS_APP_BUF_WIDTH                (1920U)
/* Buffer height in lines to allocate. */
#define M2MDSS_APP_BUF_HEIGHT               (1080U)

/* Functinal Clk Frequency of DSS */
#define M2MDSS_APP_DSS_FUNC_CLK             (192000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct M2mDssApp_Obj_t M2mDssApp_Obj;
typedef struct
{
    UInt32 idleNumber;
    /**<  Number of idles between the requests on L3 Interconnect.
     *    if idleSize is 0 - number of idle cycles = idle Number
     *          range 0 to 15
     *    if idleSize is 1 - number of idle clcles = idle Number * Burst Size.
     *          range 0 to 120 for value of burstSize = 2,
     *          range 0 to 60  for value of burstSize = 1,
     *          range 0 to 30  for value of burstSize = 0. */
    UInt32 idleSize;
    /**<  determines multiplication factor to idleNumber.
     *    refer comment for idleNumber. */
}M2mDssApp_bandwidthCtrl;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    UInt32                      testId;
    /**< Test Id. */
    Char                       *testDescStr;
    /**< Test description. */
    UInt32                      wbInNode;
    /**< Input pipe/overlay that is connected to writeback pipeline */
    UInt32                      numInPipeLines;
    /**< Number of input pipelines connected to the overlay */
    UInt32                      inPipeLines[VPS_DSS_DISPC_PIPE_MAX];
    /**< List of input pipelines */

    Fvid2_DataFormat            inDataFmt[VPS_DSS_DISPC_PIPE_MAX];
    /**< YUV or RGB data format. */
    UInt32                      inWidth[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32                      inHeight[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32                      inTarWidth[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input pipeline width at overlay. */
    UInt32                      inTarHeight[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input pipeline height at overlay. */

    Fvid2_DataFormat            outDataFmt;
    /**< YUV or RGB data format. */
    UInt32                      outWidth;
    /**< Output buffer resolution width in pixels. */
    UInt32                      outHeight;
    /**< Output buffer resolution height in lines. */

    UInt32                      ovlyWidth;
    /**< Width of overlay when WB is captured from an overlay */
    UInt32                      ovlyHeight;
    /**< Height of overlay when WB is captured from an overlay */

    UInt32                      cropEnable;
    /**< Set to TRUE if ovlyWidth and inCropCfg.cropWidth are not same and/or
     *   ovlyHeight and inCropCfg.cropHeight are not same
     *   Note: This is not applicable for TDA2xx/TDA2Ex. Set to FALSE. */
    Fvid2_CropConfig            cropCfg;
    /**< DSS WB input crop config. Not valid for TDA2XX/TDA2Ex platforms.
     *   For TDA3XX platform for full frame write back,
     *   height and width of crop config should be same as in ovlyHeight and
     *   ovlyWidth */
    M2mDssApp_bandwidthCtrl     bwCfg;
    /**< Bandwidth control parameter. */
    Int32                       runCount;
    /**< Number of frames to display. */
    UInt32                      crcValue;
    /**< Expected CRC value. */
} M2mDssApp_TestParams;

/**
 *  \brief Test application data structure.
 */
struct M2mDssApp_Obj_t
{
    Vps_M2mDssCreateParams      createPrms;
    /**< Create time parameters. */
    Vps_M2mDssCreateStatus      createStatus;
    /**< Create status returned by driver during Fvid2_create(). */

    Vps_M2mDssParams            dssPrms;
    /**< DSS driver parameters. */
    Fvid2_Handle                drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams              cbPrms;
    /**< Callback params. */

    Fvid2_Frame                 inFrames[VPS_DSS_DISPC_PIPE_MAX]
                                        [M2MDSS_APP_NUM_IN_BUFFERS];
    /**< FVID2 Frames that will be used for input. */
    Fvid2_Frame                 outFrames[M2MDSS_APP_NUM_OUT_BUFFERS];
    /**< FVID2 Frames that will be used for output. */

    UInt8                      *outSaveBuf;
    /**< DSS writeback out buffer used to store the output video frames. */
    UInt32                      outBufSize;

    UInt32                      inBufIdx;
    /**< Current input buffer index. Used to wrap around input buffer. */
    UInt32                      outBufIdx;
    /**< Current output buffer index. Used to wrap around output buffer. */
    Vps_DssDispcAdvDmaConfig    advDmaCfg;
    /**< DSS driver dma configuration parameters. */

    M2mDssApp_TestParams        testPrms;
    /**< Current test parameters. */
    Task_Handle                 tskHandle;
    /**< Test task handle. */
    UInt32                      completedLoopCnt;
    /**< Total number of completed frames. */
    Semaphore_Handle            reqCompleteSem;
    /**< Request complete semaphore used to sync between callback and task. */
    UInt32                      enableAutoRun;
    /**< Auto-run enable flag. */
};

/**
 *  \brief Buffer configuration structure for buffer allocation.
 */
typedef struct
{
    UInt32                      width;
    /**< Buffer width in pixels. */
    UInt32                      height;
    /**< Buffer height. */
    UInt32                      pitch;
    /**< Pitch in bytes. */
    UInt32                      dataFmt;
    /**< Data format. */
    UInt32                      numBuffers;
    /**< Number of buffers. */
} M2mDssApp_LoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8                      *bufAddr;
    /**< Buffer address. */
    UInt32                      bufSize;
    /**< One buffer size in bytes. */
    UInt32                      totalBufSize;
    /**< Total buffer size in bytes. */
    M2mDssApp_LoadBufCfg        bufCfg;
    /**< Buffer configuration. */
} M2mDssApp_BufInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 M2mDssApp_allocInBuf(void);
Int32 M2mDssApp_freeInBuf(void);

Int32 M2mDssApp_allocOutBuf(M2mDssApp_Obj *appObj);
Int32 M2mDssApp_freeOutBuf(M2mDssApp_Obj *appObj);

void M2mDssApp_initFrames(M2mDssApp_Obj *appObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef M2MDSSWB_MAIN_H_ */
