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
 *  \file CaptureIssOtf_main.h
 *
 *  \brief Defines various structures / defines needed by capture demo app.
 *
 */

#ifndef CAPTURE_ISS_MAIN_H_
#define CAPTURE_ISS_MAIN_H_

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

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>

#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/include/iss/vps_captureIss.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>
#include <ti/drv/vps/include/iss/vps_cfgisp.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgglbce.h>

#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Demo application stack size */
#define CAPT_APP_TSK_STACK_MAIN         (10U * 1024U)

/**< Demo application task priority */
#define CAPT_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CAPT_ISS_APP"

/**< Default run count in seconds in case of EVM else this is in frame count. */
#define CAPT_APP_RUN_COUNT              (1000U)

/**< Number of frames per stream */
#define CAPT_APP_FRAMES_PER_STREAM      (6U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Specify different config that would be used to capture
 */
typedef struct appCaptCfg
{
    Char                   *testDescStr;
    /**< Test description. */
    UInt32                  cfgId;
    /**< Config identifier */
    UInt32                  useIt;
    /**< Capture with this config, could be bypassed, by set this to FALSE */
    Fvid2_VideoIfMode       interfaceType;
    /**< Either CSI2, LVDS, Parallel */
    Fvid2_VideoIfWidth      interfacewidth;
    /**< 1,2,3,4 lanes for CSI2, 4 lane for LVDS, 8-16 bits for parallel */
    UInt32                  numStreams;
    /**< Currently this should be 1 */
    UInt32                  virtualChannel;
    /**< In case of CSI2 - specify the virtual channel */
    vpsissCalCsi2DataFormat inCsi2DataFormat;
    /**< Specify input data format */
    Fvid2_BitsPerPixel      inBpp;
    /**< Number of bits / pixel */
    UInt32                  numFrames;
    /**< Specify number of frames to capture */
    UInt32                  width;
    /**< Expected frame width that requires to be captured. If sensor streams
     *      frames with greater width, the extra pixels would not be written.
     *      If sensors streams frames with less line length, the received
     *      lines are written. */
    UInt32                  height;
    /**< Expected frame height requires to be captured. If sensor streams
     *      frames with higher number of lines, the extra lines would not be
     *      written / captured.*/
    UInt32                  pitch;
    UInt32                  sensorDrvId;
    /**< Associated sensor driver, that would stream */
    Fvid2_Standard          standard;
    /**< Resolution */
    Fvid2_DataFormat        dataFormat;
    /**< Standard FVID2 resolution that sensor would be configured to stream */
    Fvid2_BitsPerPixel      bpp;
    /**< bits / pixel */
    Bsp_BoardMode           boardMode;
    /**< Interface width in case of parallel capture. NA for CSI2*/
    UInt32                  calInstId;
    /**< CAL Instance IDs, VPS_CAPT_INST_ISS_CAL_A or
     *      VPS_CAPT_INST_ISS_CAL_A_OTF */
    vpsissGlbcePath_t       glbcePath;
    /**< GLBCE on CAL, ISP or disabled. VPS_ISS_GLBCE_PATH_DISABLED
     *      VPS_ISS_GLBCE_PATH_ISP, */
    vpsissNsf3Path_t        nsf3Path;
    /**< NSF3 on CAL, ISP or disabled. VPS_ISS_NSF3_PATH_DISABLED
     *      VPS_ISS_NSF3_PATH_ISP, */

    Fvid2_DataFormat        outFmt;
    /**< Output data format FVID2_DF_YUV422I_UYVY FVID2_DF_YUV420SP_UV */
    UInt32                  enaRszB;
    /**< TRUE enables RSZ B output, FALSE disables the same.
     *      Output of RSZ is always YUV420
     *      Height = RSZ A height / 2
     *      Width = RSZ A width / 2 */
}appCaptCfg_t;

/**
 *  \brief Capture application object.
 */
typedef struct appCaptObj
{
    Task_Handle                tskHandle;
    /**< Test task handle. */

    Vps_CaptIssOpenParams_t    issOpenPrms;
    /**< ISS create time parameters */
    vpsissIspOpenParams_t      ispOpenPrms;
    /**< ISP open params */
    Fvid2_VideoIfMode          videoIfMode;
    /**< CSI2, LVDS, Parallel etc... */
    Fvid2_VideoIfWidth         videoIfWidth;
    /**< Number of lanes in case CSI2 and number of bits in case of parallel */
    UInt32                     numStream;
    /**< Number of channel in multi-ch case, must be 1 for single channel. */
    UInt32                     virtualChannel;
    /**< Virtual channel of CSI2, if mode is CSI2 */
    vpsissCalCsi2DataFormat    dataFormat;
    /**< Data format of CSI2 stream */
    UInt32                     instId;
    /**< ISS Instance ID. As defined in bspdrivers_\include\vps\vps_capture.h*/

    /* FVID2 Capture Driver parameters */
    Vps_CaptCreateParams       createPrms;
    /**< Create time parameters. */
    Vps_CaptCreateStatus       createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Fvid2_Handle               drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    vpsissCalCfg_t             cfg;
    /**< TODO currently done for 1 stream, update for multiple streams */
    UInt32                     numFramesToCapture;
    /**< Number of frames to receive for a given configuration */

    /* Sensor Parameters */
    Fvid2_Handle               sensorHandle;
    /**< Handle to the Sensor driver */
    UInt32                     sensorDrvId;
    /**< Sensor FVID2 Id */
    Bsp_VidSensorCreateParams  sensorCreatePrms;
    /**< Sensor create parameters */
    appCaptCfg_t               testPrms;
    /**< Test configuration / options */
    UInt32                     totalFrmCount;
    /**< Count of all frames captured. */
    UInt32                     totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                     cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */

    UInt32                     captIssAppMaxBSSMemHeapUS;
    /**< Heap usage by demo application */

    Fvid2_Frame                frames[CAPT_APP_FRAMES_PER_STREAM * \
                                      VPS_ISS_CAL_MAX_STREAMS];
    /**< Pool of FVID2 Frames containers */
    UInt32                     ts[CAPT_APP_RUN_COUNT + 10U];
    /**< Array to store the time stamps of the received frames */
    UInt32                     tsIdx;
    /**< Index into time stamp array */

    Fvid2_Format               allocFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Format passed to utils frame alloc function. */

    volatile UInt32            rcvedFramesCount;
    /**< Received frames for a given config */

    UInt32                     numCalStreams;
    /**< Number of CAL streams */
    UInt32                     rszOutStrmId;
    /**< ISP Resizer output stream ID */
    vpsissCalOtfStreamMapCfg_t otfStrmMap;
    /**< A map that indicates which streams of ISP would be written out */
    UInt32                     expectedFrameRate;
    /**< Expected frame rate from the sensor, will be used to determine
     *  if capture has dropped / delayed capture */
    vpsissIspParams_t          ispPrms;
    /**< ISP Parameters */
    vpsissRszCtrl_t            rszCtrl;
    vpsissRszCfg_t             rszCfg;
    /**< ISP Resizer */
    vpsissIsifGainOfstConfig_t isifWbCfg;
    /**< White balance configuration of ISIF */
    vpsissIsifCtrl_t           isifCtrl;
    /**< ISIF Control structure containing pointer to the
     *   ISIF configuration */
    vpsissIpipeCtrl_t          ipipeCtrl;
    vpsissIpipeInConfig_t      inputCfg;
    vpsissIpipeDpcLutConfig_t  dpcLutCfg;
    vpsissIpipeGammaConfig_t   gammaCfg;
    vpsissIpipe3DLutConfig_t   lut3d;
    vpsissIpipeEeConfig_t      eeCfg;
    vpsissIpipeGicConfig_t     gicCfg;
    vpsissIpipeLscConfig_t     lscCfg;
    vpsissIpipeNf2Config_t     nf1Cfg;
    vpsissIpipeNf2Config_t     nf2Cfg;
    vpsissIpipeLutFmtCnvt_t    lutFmtCnvt;
    /**< IPIPE Config / control structures */
    vpsissCnfConfig_t          cnfCfg;
    vpsissNsf3Config_t         nsf3vCfg;
    vpsissGlbceConfig_t        glbceCfg;
    vpsissGlbceCtrl_t          glbceCtrl;
    vpsissGlbcePerceptConfig_t glbcePerceptCfg;

    uint32_t                   enableCnf;
    uint32_t                   enableDpc;
    uint32_t                   enableLsc;
    uint32_t                   enableGic;
    uint32_t                   enableYee;
    uint32_t                   enable3dLut;
    uint32_t                   enableGamma;
    uint32_t                   enableNf1;
    uint32_t                   enableNf2;

    vpsissIpipeDpcOtfConfig_t  dpcOtfCfg;
    vpsissH3aAewbConfig_t      h3aCfg;
    /**< AEWB / AF Config */
}appCaptObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CAPTURE_ISS_MAIN_H_ */
