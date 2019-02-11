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
 * \brief  Usecase file implementation of multi-ch AVB capture+3D SRV+display
 *
 *         The data flow daigram is shown below
 *
 *                 AvbRx 4CH 30fps 1280x720
 *                   |
 *                 Decode
 *                   |
 *                 Sync
 *                   |
 *                 SGX 3d SRV
 *                   |
 *                Display (M4)
 *
 * \version 0.0 (Jun 2014) : [CM] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include "chains_avbrxSrvDisplayAvbtx_priv.h"
#include <src/hlos/system/system_gbm_allocator.h>

#define AVB_TALKER_MAX_FRAME_WIDTH       (1280)
#define AVB_TALKER_MAX_FRAME_HEIGHT      (720)

#define SGX3DSRV_OUTPUT_FRAME_WIDTH      (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT     (1080)
/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC               (0x7FFFFFFF)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC      (150)


/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_avbrxSrvDisplayAvbtxObj ucObj;
    Chains_Ctrl *chainsCfg;
    System_IVideoFormat codecType;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32 displayWidth;
    UInt32 displayHeight;


} chains_avbrxSrvDisplayAvbtxAppObj;

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
 * \brief   Set Save Display Frame Use case Link Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_avbrxSrvDisplayAvbtx_SetDispWbPrms(
                                CaptureLink_CreateParams *pPrm,
                                chains_avbrxSrvDisplayAvbtxAppObj *pObj)
{
    /* Capture DSS WB params */
    pPrm->numVipInst = 0;
    pPrm->numDssWbInst = 1;

    pPrm->dssWbInst[0].dssWbInstId = 33U; /* Only supported id */
    System_VideoScanFormat scanFormat = SYSTEM_SF_PROGRESSIVE;

    pPrm->dssWbInst[0].dssWbInputPrms.inNode = SYSTEM_WB_IN_NODE_TV;

    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceWidth = pObj->displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceHeight = pObj->displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInWidth = pObj->displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInHeight = pObj->displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosx = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosy = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceDataFmt = SYSTEM_DF_BGR24_888;
    pPrm->dssWbInst[0].dssWbInputPrms.wbScanFormat = scanFormat;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbWidth = pObj->displayWidth;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbHeight = pObj->displayHeight;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbDataFmt = SYSTEM_DF_YUV420SP_UV;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbScanFormat = scanFormat;

    pPrm->dssWbInst[0].numBufs = 3U;

}

/**
 *******************************************************************************
 *
 * \brief   Set Encoder Create Parameters
 *
 * \param   pPrm         [IN]  EncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_avbrxSrvDisplayAvbtx_SetEncPrms(
                   EncLink_CreateParams *pPrm,
                   chains_avbrxSrvDisplayAvbtxAppObj *pObj)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 3;
    }

    for (chId = 0; chId < 1; chId++)
    {
        pLinkChPrm  = &pPrm->chCreateParams[chId];
        pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

        UTILS_assert (chId < ENC_LINK_MAX_CH);

        switch (pObj->codecType)
        {
          case SYSTEM_IVIDEO_MJPEG: /* MJPEG */
            pLinkChPrm->format                 = SYSTEM_IVIDEO_MJPEG;
            pLinkChPrm->profile                = 0;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = 0;
            pLinkChPrm->encodingPreset         = 0;
            pLinkChPrm->rateControlPreset      = 0;
            pLinkChPrm->enableHighSpeed        = 0;
            pLinkChPrm->enableSVCExtensionFlag = 0;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;

            pLinkDynPrm->intraFrameInterval    = 0;
            pLinkDynPrm->targetBitRate         = 10*1000*1000;
            pLinkDynPrm->interFrameInterval    = 0;
            pLinkDynPrm->mvAccuracy            = 0;
            pLinkDynPrm->inputFrameRate        = 30;
            pLinkDynPrm->rcAlg                 = 0;
            pLinkDynPrm->qpMin                 = 0;
            pLinkDynPrm->qpMax                 = 0;
            pLinkDynPrm->qpInit                = -1;
            pLinkDynPrm->vbrDuration           = 0;
            pLinkDynPrm->vbrSensitivity        = 0;
            Vps_printf(" \n Codec is MJPEG \n");
            break;

          case SYSTEM_IVIDEO_H264HP: /* H264 */
            pLinkChPrm->format                 = SYSTEM_IVIDEO_H264HP;
            pLinkChPrm->profile                = 100;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = -1;
            pLinkChPrm->encodingPreset         = SYSTEM_XDM_MED_SPEED_HIGH_QUALITY;
            /* Set to SYSTEM_XDM_USER_DEFINED if SEI/meta data needs to be enabled */
            pLinkChPrm->encodingPreset         = SYSTEM_XDM_USER_DEFINED;
            pLinkChPrm->rateControlPreset      = SYSTEM_IVIDEO_LOW_DELAY;
            pLinkChPrm->enableHighSpeed        = FALSE;
            pLinkChPrm->enableSVCExtensionFlag = FALSE;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;
            pLinkChPrm->IDRFrameInterval       = 30;

            pLinkDynPrm->intraFrameInterval    = 1;
            pLinkDynPrm->targetBitRate         = 10*1000*1000;
            pLinkDynPrm->interFrameInterval    = 1;
            pLinkDynPrm->mvAccuracy            = SYSTEM_IVIDENC2_MOTIONVECTOR_QUARTERPEL;
            pLinkDynPrm->inputFrameRate        = 30;
            pLinkDynPrm->rcAlg                 = 0;
            pLinkDynPrm->qpMin                 = 0;
            pLinkDynPrm->qpMax                 = 51;
            pLinkDynPrm->qpInit                = 25;
            pLinkDynPrm->vbrDuration           = 8;
            pLinkDynPrm->vbrSensitivity        = 0;
            pLinkDynPrm->maxPicSizeRatioI      = 1;
            break;

          default: /* D1 */
            printf("\r\nCodec Type: %d, returning \n", pObj->codecType);
            UTILS_assert(FALSE);
            break;
        }
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set SGX3DSRV Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_avbrxSrvDisplayAvbtx_SetSgx3DsrvLinkPrms (
                                 Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = AVB_TALKER_MAX_FRAME_HEIGHT;
    prms->maxInputWidth = AVB_TALKER_MAX_FRAME_WIDTH;
    prms->numViews = 1;
    prms->bAnimate = 1;
    prms->numInQue = SGX3DSRV_LINK_IPQID_MAXIPQ;
    prms->inBufType[0] = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->inBufType[1] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[2] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[3] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->bEglInfoInCreate = TRUE;
    prms->EglInfo = (void *)&chainsEglParams;
}

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
static Void chains_avbrxSrvDisplayAvbtx_SetSync1Prm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

#if 0
static Void chains_avbrxSrvDisplayAvbtx_SetDisplayPosition(
                    DisplayLink_CreateParams *pPrm_Video,
                    UInt32 posX,
                    UInt32 posY
                    )
{
    pPrm_Video->rtParams.posX = 520;
    pPrm_Video->rtParams.posY = 0;
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          Chains_lvdsMultiVipCaptureDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [OUT]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_avbrxSrvDisplayAvbtx_SetVpe1Prm(
                        VpeLink_CreateParams *pPrm,
                        UInt32 numLvdsCh,
                        UInt32 OutWidth,
                        UInt32 OutHeight
                    )
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;
    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
        chPrms->outParams[outId].numBufsPerCh =
                                 2;

        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;

        chPrms->scCropCfg.cropStartX = 0;
        chPrms->scCropCfg.cropStartY = 0;
        chPrms->scCropCfg.cropWidth  = 1280;
        chPrms->scCropCfg.cropHeight = 720;
    }
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
Void chains_avbrxSrvDisplayAvbtx_SetAppPrms(chains_avbrxSrvDisplayAvbtxObj *pUcObj, Void *appObj)
{
    UInt32 svOutWidth, svOutHeight;

    chains_avbrxSrvDisplayAvbtxAppObj *pObj
        = (chains_avbrxSrvDisplayAvbtxAppObj*)appObj;

    ChainsCommon_SetAvbRxPrm(
        &pUcObj->AvbRxPrm,
        AVB_TALKER_MAX_FRAME_WIDTH,
        AVB_TALKER_MAX_FRAME_HEIGHT,
        pObj->chainsCfg->numLvdsCh
            );

    ChainsCommon_SetDecodePrm(
                            &pUcObj->DecodePrm,
                            AVB_TALKER_MAX_FRAME_WIDTH,
                            AVB_TALKER_MAX_FRAME_HEIGHT,
                            pObj->chainsCfg->numLvdsCh,
                            pObj->codecType);

    pObj->captureOutWidth  = AVB_TALKER_MAX_FRAME_WIDTH;
    pObj->captureOutHeight = AVB_TALKER_MAX_FRAME_HEIGHT;

    chains_avbrxSrvDisplayAvbtx_SetVpe1Prm(
                                    &pUcObj->VPE_decodePrm,
                                    pObj->chainsCfg->numLvdsCh,
                                    AVB_TALKER_MAX_FRAME_WIDTH,
                                    AVB_TALKER_MAX_FRAME_HEIGHT);

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &pObj->displayWidth,
                                    &pObj->displayHeight);
    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    AVB_TALKER_MAX_FRAME_WIDTH,
                                    AVB_TALKER_MAX_FRAME_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode,
                                    pObj->chainsCfg->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlign3DParams(
                                    &pUcObj->Alg_GeoAlign3DPrm,
                                    AVB_TALKER_MAX_FRAME_WIDTH,
                                    AVB_TALKER_MAX_FRAME_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    AVB_TALKER_MAX_FRAME_WIDTH,
                                    AVB_TALKER_MAX_FRAME_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    chains_avbrxSrvDisplayAvbtx_SetSync1Prm(
                        &pUcObj->SyncPrm,
                        pObj->chainsCfg->numLvdsCh
                        );

        pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
        pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
        pUcObj->GrpxSrcPrm.disablePreview = TRUE;

        pUcObj->Display_GrpxPrm.rtParams.tarWidth       = pObj->displayWidth;
        pUcObj->Display_GrpxPrm.rtParams.tarHeight      = pObj->displayHeight;
        pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
        pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
        pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

#if 0
    ChainsCommon_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                SGX3DSRV_OUTPUT_FRAME_WIDTH,
                                SGX3DSRV_OUTPUT_FRAME_HEIGHT
                               );
#endif

    chains_avbrxSrvDisplayAvbtx_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

#if 0
    chains_avbrxSrvDisplayAvbtx_SetDisplayPosition(
                    &pUcObj->Display_M4Prm,
                    520,
                    0);
#endif

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        SGX3DSRV_OUTPUT_FRAME_WIDTH,
        SGX3DSRV_OUTPUT_FRAME_HEIGHT
        );

/*    chains_avbrxSrvDisplayAvbtx_SetDispWbPrms(&pUcObj->Capture_dsswbPrm, pObj); */

    /* DSS M2M WB link */
    pUcObj->DssM2mWbPrm.enableOut = TRUE;
    pUcObj->DssM2mWbPrm.wbInNode = DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD2;
    pUcObj->DssM2mWbPrm.numInPipeLines = 1U;
    pUcObj->DssM2mWbPrm.inPipelines[0U] = DSSM2MWBLINK_DISPC_PIPE_VID3;

    /* input pipeline parameters */
    pUcObj->DssM2mWbPrm.inTarWidth[0U] = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    pUcObj->DssM2mWbPrm.inTarHeight[0U] = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    pUcObj->DssM2mWbPrm.inPosX[0U] = 0U;
    pUcObj->DssM2mWbPrm.inPosY[0U] = 0U;

    /* The overlay width and height are used only if 'wbInNode' is overlay node */
    pUcObj->DssM2mWbPrm.ovlyWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    pUcObj->DssM2mWbPrm.ovlyHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;

    /* Output parameters */
    /* Input format is ARGB32 and output format is YUV420SP_UV */
    pUcObj->DssM2mWbPrm.outDataFmt = SYSTEM_DF_YUV420SP_UV;
    pUcObj->DssM2mWbPrm.outWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    pUcObj->DssM2mWbPrm.outHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;

    pObj->codecType = SYSTEM_IVIDEO_H264HP;
    chains_avbrxSrvDisplayAvbtx_SetEncPrms(&pUcObj->EncodePrm, pObj);
    ChainsCommon_SetAvbTxPrm(
                            &pUcObj->AvbTxPrm,
                            AVB_TX_LINK_MAX_TALKERS_DEFAULT,
                            pObj->codecType);
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
 * \param   pObj  [IN] Chains_VipSingleCameraViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_avbrxSrvDisplayAvbtx_StartApp(chains_avbrxSrvDisplayAvbtxAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    chains_avbrxSrvDisplayAvbtx_Start(&pObj->ucObj);
    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);
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
 * \param   pObj   [IN]   Chains_VipSingleCameraViewObj
 *
 *******************************************************************************
*/
Void chains_avbrxSrvDisplayAvbtx_StopAndDeleteApp(chains_avbrxSrvDisplayAvbtxAppObj *pObj)
{
    chains_avbrxSrvDisplayAvbtx_Stop(&pObj->ucObj);
    chains_avbrxSrvDisplayAvbtx_Delete(&pObj->ucObj);
    ChainsCommon_StopDisplayCtrl();

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}


/**
 *******************************************************************************
 * \brief Run Time Menu string for codec Type Selection.
 *******************************************************************************
 */
char chains_avbrxSrvDisplayAvbtx_codecTypeSelectMenu[] = {
    "\r\n "
    "\r\n ========================================="
    "\r\n Chains Run-time Codec Type Selection Menu"
    "\r\n ========================================="
    "\r\n "
    "\r\n Enter '0' for MJPEG "
    "\r\n "
    "\r\n Enter '1' for H.264 "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

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
Void chains_avbrxSrvDisplayAvbtx(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    chains_avbrxSrvDisplayAvbtxAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;
    chPrev = '1';

    chainsObj.chainsCfg->numLvdsCh = 4;

    while(!done)
    {
        Vps_printf(chains_avbrxSrvDisplayAvbtx_codecTypeSelectMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                chainsObj.codecType = SYSTEM_IVIDEO_MJPEG;
                done = TRUE;
            break;
            case '1':
                chainsObj.codecType = SYSTEM_IVIDEO_H264HP;
                done = TRUE;
            break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                       chainsObj.codecType);
            break;
        }
    }

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        if(ALGLINK_GALIGN3D_CALMODE_FORCE_USERGASGXLUT != \
          (AlgorithmLink_GAlign3DCalibrationMode)\
                                        ChainsCommon_SurroundView_getCalMode())
        {
            Vps_printf(" CHAINS: -------------------------------------------------------------------- \n");
            Vps_printf(" CHAINS: Calibrated SGX LUT is NOT present \n");
            Vps_printf(" CHAINS: Generate SGX LUT by running the 'Surround View Calibration' use case \n");
            Vps_printf(" CHAINS: -------------------------------------------------------------------- \n");

            ChainsCommon_SurroundView_CalibDeInit();

            return;
        }

        chains_avbrxSrvDisplayAvbtx_Create(&chainsObj.ucObj, &chainsObj);

        chains_avbrxSrvDisplayAvbtx_StartApp(&chainsObj);

        ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

        while(!done)
        {
            ch = Chains_menuRunTime();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_avbrxSrvDisplayAvbtx_printStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_avbrxSrvDisplayAvbtx_StopAndDeleteApp(&chainsObj);

        ChainsCommon_SurroundView_CalibDeInit();

    } while(chPrev != '3');
}

