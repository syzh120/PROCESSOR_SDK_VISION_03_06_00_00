/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
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
 *  \file Loopback_main.h
 *
 *  \brief ISS Integration Application Header file.
 *   Defines functions/macros used in all tasks/drivers
 *
 */

#ifndef ISS_LOOPBACK_APP_MAIN_H_
#define ISS_LOOPBACK_APP_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>

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

#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>

#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#include <ti/drv/vps/include/iss/vps_cfgglbce.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define ISS_LOOPBACK_APP_TSK_STACK_MAIN         (50U * 1024U)

/* Test application task priority */
#define ISS_LOOPBACK_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                                "IssLoopbackApp"

/* Number of frames to process */
#define ISS_LOOPBACK_APP_NUM_PROC_FRAMES        (1000U)

/*  \brief Maximum number of RAW buffers that driver allocates,
 *         Used between Capture and M2M WDR */
#define ISS_MAX_RAW_FRAMES                      (6U)

/*  \brief Maximum number of RAW buffers that driver allocates,
 *         Used in M2M WDR, Simcop and Display */
#define ISS_MAX_YUV_FRAMES                      (6U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Fvid2_Frame      rawFrames[ISS_MAX_RAW_FRAMES];
    /** Array of frames used for storing input and outputs of
     *  different driver */
    Fvid2_Frame      yuvFrames[ISS_MAX_YUV_FRAMES];
    /** Array of frames used for storing input and outputs of
     *  different driver */
    Fvid2_Frame     *pRawFrames[ISS_MAX_RAW_FRAMES];
    /**< Array of frames pointers, used for queueing and dequeueing process */
    Fvid2_Frame     *pYuvFrames[ISS_MAX_YUV_FRAMES];
    /**< Array of frames pointers, used for queueing and dequeueing process */
    Task_Handle      mainTaskHandle;
    /**< Main Task Handler */

    UInt32           processFrmCnt;
    /**< Count of number of frames processed */

    Semaphore_Handle semCaptWait;
    /**< Semaphore for waiting for waiting for the capture buffer in
     *   the main loop */
    Semaphore_Handle semDispWait;
    /**< Semaphore for waiting for waiting for the display buffer in
     *   the main loop */
    UInt32           maxHeapMemReq;
    UInt32           maxDescMemReq;
} LpbkApp_Obj;

typedef struct
{
    Char                    testDescStr[500];
    /**< Name of the Test case */

    UInt32                  enableWdrMode;

    UInt32                  runCount;

    /* Input Parameters */
    UInt32                  inWidth;
    UInt32                  inHeight;
    UInt32                  inDataFormat;
    UInt32                  inBpp;
    UInt32                  inPitch;

    /* Sensor Parametes */
    UInt32                  sensorId;
    UInt32                  intfType;

    /* CSI2 Parameters */
    UInt32                  csi2NumLanes;
    vpsissCalCsi2DataFormat csi2DataFormat;
    UInt32                  csi2VertChNum;

    /* Enables Output on HDMI, TRUE for HDMI, FALSE for LCD */
    UInt32                  hdmiLcdDisplay;

    /* Resizer output parameters,
     * also will be used for Simcop and display */
    UInt32                  outDataFormat;
    UInt32                  outWidth;
    UInt32                  outHeight;
    UInt32                  outBpp;
    UInt32                  outPitch;
} LpbkApp_testCfg;

typedef struct _aewDataEntry {
    UInt16 window_data[8][8];
    UInt16 unsat_block_ct[8];
}aewDataEntry;

typedef struct {
    UInt16 subSampleAcc[4];
    UInt16 saturatorAcc[4];
} H3aAewbOutSumModeOverlay;

typedef struct {
    UInt16 unsatCount[8];
} H3aAewbOutUnsatBlkCntOverlay;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Declaration of the functions for M2M WDR layer */
void LpbkApp_m2mIspCreate(LpbkApp_testCfg *testCfg);
void LpbkApp_m2mIspProcessFrame(Fvid2_Frame *inpFrm, Fvid2_Frame *outFrm);
void LpbkApp_m2mIspClose(void);

/* Declaration of the functions for M2M WDR layer */
void LpbkApp_m2mWdrCreate(LpbkApp_testCfg *testCfg);
void LpbkApp_m2mWdrProcessFrame(Fvid2_Frame *inpFrm, Fvid2_Frame *outFrm);
void LpbkApp_m2mWdrClose(void);
void LpbkApp_m2mWdrApplyWdrParams(float expRatio, float evRatio);

/* Declaration of the functions for M2M WDR layer */
void LpbkApp_m2mSimcopCreate(LpbkApp_testCfg *testCfg);
void LpbkApp_m2mSimcopClose(void);
void LpbkApp_m2mSimcopProcessFrame(
    Fvid2_Frame *inpFrm,
    Fvid2_Frame *prevFrm,
    Fvid2_Frame *outFrm);

/* Declaration of the functions for Capture layer */
void LpbkApp_captCreate(
    LpbkApp_testCfg  *testCfg,
    Semaphore_Handle *semHandle);
void LpbkApp_captPutFrames(
    UInt32 streamId,
    UInt32 numFrames,
    Fvid2_Frame * frames[]);
void LpbkApp_captGetFrames(
    UInt32 streamId,
    UInt32 * numFrames,
    Fvid2_Frame * frames[]);
void LpbkApp_captStart(void);
void LpbkApp_captStop(void);
void LpbkApp_captClose(void);
void LpbkApp_captGetExpRatio(UInt32 *expRatio);

/* Declaration of the functions for Display layer */
void LpbkApp_dispCreate(LpbkApp_testCfg *testCfg, Semaphore_Handle *semHandle);
void LpbkApp_dispPutFrames(
    UInt32 handleId,
    UInt32 numFrames,
    Fvid2_Frame * frames[]);
void LpbkApp_dispGetFrames(
    UInt32 handleId,
    UInt32 * numFrames,
    Fvid2_Frame * frames[]);
void LpbkApp_dispStart(void);
void LpbkApp_dispStop(void);
void LpbkApp_dispClose(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef ISS_INTG_APP_MAIN_H_ */
