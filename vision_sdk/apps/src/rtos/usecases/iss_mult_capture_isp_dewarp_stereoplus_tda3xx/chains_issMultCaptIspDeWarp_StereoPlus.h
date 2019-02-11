/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/


#ifndef CHAINS_ISSMULTICAPTDEWARP_STEREOPLUS_H_
#define CHAINS_ISSMULTICAPTDEWARP_STEREOPLUS_H_

#include "chains_issMultCaptIspDeWarp_StereoPlus_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/app_util_iss.h>

#define STEREO_ISP_LDC_MESH_TABLE_PITCH(w, r) \
                                        ((((((w)/(r))+1) + 15U) & ~15U) * (4U))


/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (16)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (33)



#define REMAP_WIDTH                     736
#define REMAP_HEIGHT                    384

#define STEREO_OUTPUT_WIDTH             640
#define STEREO_OUTPUT_HEIGHT            360

#define LIVE_CAMERA_DISPLAY_WIDTH       640
#define LIVE_CAMERA_DISPLAY_HEIGHT      360


/* Max dewarp channel for stereo */
#define STEREO_DEWARP_MAX_CH                 (2U)

/* Number of cameras for dewarp in stereo */
#define STEREO_DEWARP_NUM_CAMERAS            (STEREO_DEWARP_MAX_CH)

/* Maximum No of view points */
#define STEREO_MAX_NUM_VIEW_POINTS           (1U)

#define STEREO_DEWARP_NUM_OUTPUT_BUFS        (3U)
/**< Number of output buffer that would be allocated at DeWarp */

#define STEREO_ISP_NUM_OUTPUT_BUFS           (3U)
/**< Number of output buffer that would be allocated at ISP */

/* Capture Resolution of AR0140 sensor */
#define STEREO_CAPT_SENSOR_AR140_WIDTH             (1280U)
#define STEREO_CAPT_SENSOR_AR140_HEIGHT            (800U)

/* Capture Resolution of OV10640 sensor */
#define STEREO_CAPT_SENSOR_OV10640_WIDTH           (1280U)
#define STEREO_CAPT_SENSOR_OV10640_HEIGHT          (720U)

#define STEREO_ISP_OUTPUT_WIDTH_W_PAD              (STEREO_CAPT_SENSOR_OV10640_WIDTH)
#define STEREO_ISP_OUTPUT_HEIGHT_W_PAD             (STEREO_CAPT_SENSOR_OV10640_HEIGHT)

/* Maximum output size from LDC / SIMCOP */
#define STEREO_LDC_OUTPUT_WIDTH_MAX                (1280U)
#define STEREO_LDC_OUTPUT_HEIGHT_MAX               (720U)

/* LDC Frm size and other parameters */
#define STEREO_LDC_BLOCK_WIDTH                     (16U)
#define STEREO_LDC_BLOCK_HEIGHT                    (16U)



/**
 *******************************************************************************
 *
 *  \brief  chains_issMultCaptIspDeWarp_StereoPlusAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issMultCaptIspDeWarp_StereoPlusObj ucObj;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    AppUtils_Obj                  appObjPrms;

    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;
    AlgLink_DeWarpConfigParams    deWarpSimcopCfg;

    UInt32 numCh;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    UInt32  netProcId;

    Chains_Ctrl *chainsCfg;

    Bool bypassVtnf;
    Bool bypassLdc;


    AlgorithmLink_SrvCommonViewPointParams algViewParams[STEREO_MAX_NUM_VIEW_POINTS];
    System_VideoFrameCompositeBuffer ldcMeshTableContainer[STEREO_MAX_NUM_VIEW_POINTS];

    BspOsal_SemHandle startStereoDemo;
    /**< Synchronization semaphore used to signal start computing LDC LUTs */
    BspOsal_TaskHandle mediaTaskHndl;
    /**< Media task handle */

    UInt32  numViewPoints;

    UInt32  lutFilePresent;
    /**< Flag to indicate if LUT file is present on MMCSD card */

    Int8  * steroParamsBuffer;
    /**< Stereo params buffer */

    Int8  * steroCamParamsBuffer;
    /**< Stereo camera params buffer */

} chains_issMultCaptIspDeWarp_StereoPlusAppObj;



Void chains_issMultCaptIspDeWarpStereoPlus_MediaTask(UArg arg1, UArg arg2);

/**< Task to interface to media */
Int32 chains_issMultCaptIspDeWarpStereoPlus_FreeBufs(
                chains_issMultCaptIspDeWarp_StereoPlusAppObj *pChainsObj);

#endif /* CHAINS_ISSMULTICAPTDEWARP_STEREOPLUS_H_ */
