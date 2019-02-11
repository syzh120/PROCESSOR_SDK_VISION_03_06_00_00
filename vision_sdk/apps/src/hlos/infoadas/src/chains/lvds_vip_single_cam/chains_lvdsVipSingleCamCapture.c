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

/**
 *******************************************************************************
 * \file chains_vipSingleCameraView.c
 *
 * \brief  Usecase file implementation of capture display usecase.
 *
 *         Usecase file for single camere view usecase.
 *
 *         Capture --> EpSink Link(A15)
 *
 *
 *         In this use-case we capture 1 CH of video from OV1063x 720p30
 *         and send it to A15 using IPC_OUT, IPC_IN. A15 is running SgxDisplay
 *         Link which will render the frames and display via DRM
 *
 *         The data flow daigram is shown below
 *
 *             Capture (VIP) 1CH 30fps 1280x720 or 60fp 1920x1080
 *                   |
 *                   |
 *                 IPC OUT
 *                   |
 *                 IPC IN
 *                   |
 *               EpSink (A15)
 *
 * \version 0.0 (Jun 2014) : [YM] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "chains_lvdsVipSingleCamCapture_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_preview.h>
#include "../../ti-plugins/include/preview_chain.h"

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_lvdsVipSingleCamCaptureObj ucObj;
    VideoSensorCreateAndStartAppPrm  vidSensorPrm;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

}chains_lvdsVipSingleCamCaptureAppObj;

chains_lvdsVipSingleCamCaptureAppObj gLvdsVipSingleCamObj;

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleCamCapture_SetAppPrms(chains_lvdsVipSingleCamCaptureObj *pUcObj,Void *appObj)
{
   EpLink_CreateParams  *pEndp;
   chains_lvdsVipSingleCamCaptureAppObj *pObj
            = (chains_lvdsVipSingleCamCaptureAppObj *)appObj;

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_OV10635;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = 1;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
            &pObj->vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_SingleCam_SetCapturePrms(&(pUcObj->CapturePrm),
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            CHAINS_CAPTURE_SRC_OV10635
            );
    /* We have one epLink in the chain; we will configure it now */
    /* sink1 */
    pEndp = &pUcObj->EpSinkPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = PREVIEW_LVDS_SINGLE_CAM;
    strcpy(pEndp->plugName, PREVIEW_PLUGIN_NAME);
}

Void chains_lvdsVipSingleCamCapture_InitApp(Void)
{
}

Int32 chains_lvdsVipSingleCamCapture_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    chains_lvdsVipSingleCamCaptureObj *pUcObj;

    chains_lvdsVipSingleCamCapture_InitApp();

    status = chains_lvdsVipSingleCamCapture_Create(&gLvdsVipSingleCamObj.ucObj, &gLvdsVipSingleCamObj);

    /* Let's set the epLink ids now */
    pUcObj = &gLvdsVipSingleCamObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSinkLinkID;

    return status;
}

Int32 chains_lvdsVipSingleCamCapture_StartApp(Void)
{
    chains_lvdsVipSingleCamCaptureAppObj *pObj
        = (chains_lvdsVipSingleCamCaptureAppObj *)&gLvdsVipSingleCamObj;

    return (chains_lvdsVipSingleCamCapture_Start(&pObj->ucObj));
}

Int32 chains_lvdsVipSingleCamCapture_StopApp(Void)
{
    chains_lvdsVipSingleCamCaptureAppObj *pObj
        = (chains_lvdsVipSingleCamCaptureAppObj *)&gLvdsVipSingleCamObj;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
            &pObj->vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);
    return (chains_lvdsVipSingleCamCapture_Stop(&pObj->ucObj));
}

Int32 chains_lvdsVipSingleCamCapture_DeleteApp(Void)
{
    chains_lvdsVipSingleCamCaptureAppObj *pObj
        = (chains_lvdsVipSingleCamCaptureAppObj *)&gLvdsVipSingleCamObj;

    return (chains_lvdsVipSingleCamCapture_Delete(&pObj->ucObj));
}
