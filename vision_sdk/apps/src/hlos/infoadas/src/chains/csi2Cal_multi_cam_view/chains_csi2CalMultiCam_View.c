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
 * \file chains_csi2CalMultiCam_View.c
 *
 * \brief  Usecase file implementation
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_csi2CalMultiCam_View_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <vivi_preview.h>
#include "../../ti-plugins/include/preview_chain.h"

#define CAPTURE_SENSOR_WIDTH                (1280)
#define CAPTURE_SENSOR_HEIGHT               (720)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK            (800U)

/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH              (5U)

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC                   (16)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC          (33)

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
    /**< Link Id's and device IDs to use for this use-case */
    chains_csi2CalMultiCam_ViewObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;
    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    UInt32  numLvdsCh;

    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
} Chains_csi2CalMultiCam_ViewAppObj;

Chains_csi2CalMultiCam_ViewAppObj gCsi2CalMultiCamObj; 

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          Chains_lvdsMultiVipCaptureDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_csi2CalMultiCam_View_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}


/**
 *******************************************************************************
 *
 * \brief   Set ISS Capture parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setCaptureParams(Chains_csi2CalMultiCam_ViewAppObj *pObj)
{
    UInt32 idx;
    IssCaptureLink_CreateParams *pCaptPrm;
    IssCaptureLink_Csi2Params *pCsi2Prm;
    IssCaptureLink_OutParams *pOutPrm;
    System_VideoDataFormat inOutDataFormat;

    pCaptPrm = &pObj->ucObj.IssCapturePrm;
    memset((void*) pCaptPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pCaptPrm->videoIfMode = SYSTEM_VIFM_SCH_CSI2;
    pCaptPrm->videoIfWidth = SYSTEM_VIFW_4LANES;
    pCaptPrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;

    for (idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
    {
        pCsi2Prm = &pCaptPrm->csi2Params[idx];

        pCsi2Prm->isCmplxIoCfgValid = FALSE;
        pCsi2Prm->csi2PhyClk = CAPTURE_UB964_CSI2_CLOCK;

        pCsi2Prm->cmplxIoCfg.clockLane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.clockLane.position = 1U;
        pCsi2Prm->cmplxIoCfg.data1Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data1Lane.position = 2U;
        pCsi2Prm->cmplxIoCfg.data2Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data2Lane.position = 3U;
        pCsi2Prm->cmplxIoCfg.data3Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data3Lane.position = 4U;
        pCsi2Prm->cmplxIoCfg.data4Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data4Lane.position = 5U;
    }
    /* UB964 Can support only 1 interface*/
    pCaptPrm->csi2Params[0U].isCmplxIoCfgValid = TRUE;

    if (2U == pObj->numLanesOnPhy0Csi2)
    {
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data3Lane.position = 0U;
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data4Lane.position = 0U;
    }

    pCaptPrm->numCh = pObj->numCsi2Ch;

    inOutDataFormat = SYSTEM_DF_YUV422I_YUYV;

    for (idx = 0U; idx < pCaptPrm->numCh; idx++)
    {
        pOutPrm = &pCaptPrm->outParams[idx];
        pOutPrm->width          = pObj->captureOutWidth;
        pOutPrm->height         = pObj->captureOutHeight;
        pOutPrm->dataFormat     = inOutDataFormat;
        pOutPrm->inCsi2DataFormat       = SYSTEM_CSI2_YUV422_8B;
        pOutPrm->inCsi2VirtualChanNum   = idx;
        pOutPrm->maxWidth       = pObj->captureOutWidth;
        pOutPrm->maxHeight      = pObj->captureOutHeight;
        pOutPrm->numOutBuf      = CAPTURE_NUM_BUF_PER_CH;
        pOutPrm->outDataFormat  = inOutDataFormat;
    }

    pCaptPrm->allocBufferForRawDump  = FALSE;

    return;
}

/**
 *******************************************************************************
 * *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_View_SetAppPrms(
            chains_csi2CalMultiCam_ViewObj *pUcObj, Void *appObj)
{
    EpLink_CreateParams  *pEndp;
    Chains_csi2CalMultiCam_ViewAppObj *pObj
            = (Chains_csi2CalMultiCam_ViewAppObj*)appObj;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    setCaptureParams(pObj);

    chains_csi2CalMultiCam_View_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->numLvdsCh
                        );

    /* We have one epLink in the chain; we will configure it now */
    /* sink1 */
    pEndp = &pUcObj->EpSinkPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = PREVIEW_CSI2CAL_MULTI_CAM;
    strcpy(pEndp->plugName, PREVIEW_PLUGIN_NAME);

    /* Enable clock for the CAL and CSI2 */
    system("omapconf write 0x4A009028 0x00040001");
    system("msleep 10");
    system("omapconf write 0x4A009038 0x00030000");
    system("msleep 10");
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
Void chains_csi2CalMultiCam_View(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_csi2CalMultiCam_ViewAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.chainsCfg->numLvdsCh = 4;
#ifndef TDA2EX_17X17
        chainsObj.numLanesOnPhy0Csi2 = 4U;
#else
        chainsObj.numLanesOnPhy0Csi2 = 2U;
#endif
        chainsObj.numCsi2Ch = chainsObj.chainsCfg->numLvdsCh;
}
*/

Int32 chains_csi2CalMultiCam_View_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    chains_csi2CalMultiCam_ViewObj *pUcObj;
    Chains_csi2CalMultiCam_ViewAppObj *pObj
        = (Chains_csi2CalMultiCam_ViewAppObj *)&gCsi2CalMultiCamObj;

    pObj->numLvdsCh = 4;
#ifndef TDA2EX_17X17
    pObj->numLanesOnPhy0Csi2 = 4U;
#else
    pObj->numLanesOnPhy0Csi2 = 2U;
#endif
    pObj->numCsi2Ch = pObj->numLvdsCh;

    status = chains_csi2CalMultiCam_View_Create(&gCsi2CalMultiCamObj.ucObj, &gCsi2CalMultiCamObj);

    /* Let's set the epLink ids now */
    pUcObj = &gCsi2CalMultiCamObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSinkLinkID;

    return status;
}

Int32 chains_csi2CalMultiCam_View_StartApp(Void)
{
    Chains_csi2CalMultiCam_ViewAppObj *pObj
        = (Chains_csi2CalMultiCam_ViewAppObj *)&gCsi2CalMultiCamObj;

    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = pObj->numLvdsCh;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

    return chains_csi2CalMultiCam_View_Start(&pObj->ucObj);
}

Int32 chains_csi2CalMultiCam_View_StopApp(Void)
{
    UInt32 ret;
    Chains_csi2CalMultiCam_ViewAppObj *pObj
        = (Chains_csi2CalMultiCam_ViewAppObj *)&gCsi2CalMultiCamObj;

    ret = chains_csi2CalMultiCam_View_Stop(&pObj->ucObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);
    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);
    return ret;
}

Int32 chains_csi2CalMultiCam_View_DeleteApp(Void)
{
    Chains_csi2CalMultiCam_ViewAppObj *pObj
        = (Chains_csi2CalMultiCam_ViewAppObj *)&gCsi2CalMultiCamObj;

    return (chains_csi2CalMultiCam_View_Delete(&pObj->ucObj));
}
