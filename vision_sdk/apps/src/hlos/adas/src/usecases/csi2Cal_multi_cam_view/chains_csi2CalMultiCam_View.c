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
#include <src/hlos/system/system_gbm_allocator.h>

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

    Chains_Ctrl *chainsCfg;

    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
} Chains_csi2CalMultiCam_ViewAppObj;

static struct control_srv_egl_ctx chainsEglParams = {
   .get_egl_native_display = gbm_allocator_get_native_display,
   .get_egl_native_buffer = gbm_allocator_get_native_buffer,
   .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
   .wrap_native_buffers = gbm_wrap_native_buffers,
   .wrapper_get_next_buffer = gbm_wrapper_get_next_buffer,
   .wrapper_put_buffer = gbm_wrapper_put_buffer,
   .unwrap_native_buffers = gbm_unwrap_native_buffers,
};

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
        pOutPrm->outBpp         = SYSTEM_BPP_BITS16;
    }

    pCaptPrm->allocBufferForRawDump  = FALSE;

    return;
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE for CSC parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setVpeSv_CscPrm(
                        VpeLink_CreateParams *pPrm,
                        UInt32 numLvdsCh,
                        UInt32 OutWidth,
                        UInt32 OutHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;
    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
        chPrms->outParams[outId].numBufsPerCh =
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;

        chPrms->scCropCfg.cropStartX = 0;
        chPrms->scCropCfg.cropStartY = 0;
        chPrms->scCropCfg.cropWidth  = OutWidth;
        chPrms->scCropCfg.cropHeight = OutHeight;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set SGXDISPLAY Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_csi2CalMultiCam_View_SetSgxDisplayLinkPrms (
                                  SgxFrmcpyLink_CreateParams *prms,
                                  UInt32 width, UInt32 height)
{
    prms->displayWidth = width;
    prms->displayHeight = height;
    prms->renderType = SGXFRMCPY_RENDER_TYPE_2x2;
    prms->inBufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->bEglInfoInCreate = TRUE;
    prms->EglInfo = (void *)&chainsEglParams;
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
    UInt32 displayWidth,displayHeight;
    Chains_csi2CalMultiCam_ViewAppObj *pObj
            = (Chains_csi2CalMultiCam_ViewAppObj*)appObj;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    setCaptureParams(pObj);

    setVpeSv_CscPrm(
                &pUcObj->VPE_sv_cscPrm,
                pObj->chainsCfg->numLvdsCh,
                pObj->captureOutWidth,
                pObj->captureOutHeight);


    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    displayWidth,
                                    displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    chains_csi2CalMultiCam_View_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->chainsCfg->numLvdsCh
                        );

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.disablePreview = TRUE;
    pUcObj->Display_GrpxPrm.rtParams.tarWidth       = displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight      = displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
    pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

    chains_csi2CalMultiCam_View_SetSgxDisplayLinkPrms
                                 (&pUcObj->SgxFrmcpyPrm,
                                  displayWidth,
                                  displayHeight
                                 );

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                displayWidth,
                                displayHeight
                               );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        displayWidth,
        displayHeight
        );

    /* Enable clock for the CAL and CSI2 */
    system("omapconf write 0x4A009028 0x00040001");
    system("msleep 10");
    system("omapconf write 0x4A009038 0x00030000");
    system("msleep 10");
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_csi2CalMultiCam_ViewAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_csi2CalMultiCam_View_StartApp(Chains_csi2CalMultiCam_ViewAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

    chains_csi2CalMultiCam_View_Start(&pObj->ucObj);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_csi2CalMultiCam_ViewAppObj
 *
 *******************************************************************************
*/
void chains_csi2CalMultiCam_View_StopApp(Chains_csi2CalMultiCam_ViewAppObj *pObj)
{
    chains_csi2CalMultiCam_View_Stop(&pObj->ucObj);

    chains_csi2CalMultiCam_View_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);
    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);
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
*/
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

        done = FALSE;

        chains_csi2CalMultiCam_View_Create(&chainsObj.ucObj, &chainsObj);

        chains_csi2CalMultiCam_View_StartApp(&chainsObj);

        ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

        while(!done)
        {
            ch = Chains_menuRunTime();

            switch(ch)
            {
                case '0':
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_csi2CalMultiCam_View_printStatistics(&chainsObj.ucObj);
                    chains_csi2CalMultiCam_View_printBufferStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_csi2CalMultiCam_View_StopApp(&chainsObj);
}


