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
 * \brief  Usecase file implementation of multi-ch capture display
 *
 *         The data flow diagram is shown below
 *
 *          Capture (VIP) 2CH 30fps 2560x720
 *                        |
 *              Split 4CH 30fps 1280x720
 *                        |
 *                      Sync
 *                        |
 *                      IPC OUT
 *                        |
 *                      IPC IN
 *                        |
 *                     Sgx3Dsrv (A15)
 *
 * \version 0.0 (Jun 2014) : [YM] First version ported for linux.
 * \version 0.1 (Jan 2016) : [MM] use Galign3D instead of Galign link
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_ov490VipMultiCam_Sgx3Dsrv_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>

/* Use OV1063x based mult-deser setup - only for debug */
static volatile UInt32 gUseOv1063x = 0;

#define CAPTURE_SENSOR_WIDTH                 (1280)
#define CAPTURE_SENSOR_HEIGHT                (720)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH          (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT         (1080)

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
    chains_ov490VipMultiCam_Sgx3DsrvObj ucObj;

    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  useOV1063x;

    Chains_Ctrl *chainsCfg;
} Chains_ov490VipMultiCam_Sgx3DsrvAppObj;

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
 * \brief   Set SGX3DSRV Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_ov490VipMultiCam_Sgx3Dsrv_SetSgx3DsrvLinkPrms (
                                  Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = CAPTURE_SENSOR_HEIGHT;
    prms->maxInputWidth = CAPTURE_SENSOR_WIDTH;
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
 *          Chains_ov490MultiVipCaptureDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_ov490VipMultiCam_Sgx3Dsrv_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

static Void chains_lvdsVipMultiCam_Sgx3Dsrv_SetDisplayPosition(
                    DisplayLink_CreateParams *pPrm_Video,
                    UInt32 posX,
                    UInt32 posY
                    )
{
    pPrm_Video->rtParams.posX = 520;
    pPrm_Video->rtParams.posY = 0;
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVipSurroundViewStandalone_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 syncMode
                    )
{
    if(syncMode == 1)
    {
        pPrm->syncDelta = TIGHT_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC;
    }
    else
    {
        pPrm->syncDelta = LOOSE_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC;
    }

}

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
static Void chains_lvdsVipSurroundViewStandalone_SetVpePrm(
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
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

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

static void chains_lvdsVipSurroundViewStandalone_SetSelectPrm(
                                      SelectLink_CreateParams *pPrm)
{
    pPrm->numOutQue = 2;

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 2;
    pPrm->outQueChInfo[0].inChNum[0] = 0;
    pPrm->outQueChInfo[0].inChNum[1] = 1;

    pPrm->outQueChInfo[1].outQueId   = 1;
    pPrm->outQueChInfo[1].numOutCh   = 2;
    pPrm->outQueChInfo[1].inChNum[0] = 2;
    pPrm->outQueChInfo[1].inChNum[1] = 3;
}

/**
 *******************************************************************************
 *
 * \brief   Set DMA SW Mosaic Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void chains_lvdsVipSurroundViewStandalone_SetAlgDmaSwMsPrm(
                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 channelWidth,
                    UInt32 channelHeight,
                    UInt32 channelSpacingHor,
                    UInt32 channelSpacingVer
                   )
{
    UInt32 algId, winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    useLocalEdma = FALSE;
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->baseClassCreate.algId   = algId;
    pPrm->numOutBuf               = 4;
    pPrm->useLocalEdma            = useLocalEdma;
    pPrm->initLayoutParams.numWin = numLvdsCh;

    pPrm->maxOutBufWidth     = channelWidth;
    pPrm->maxOutBufHeight    = (channelHeight*(numLvdsCh)) +
                               (channelSpacingVer*(numLvdsCh-1));

    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
        pWinInfo->chId = winId;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width    = channelWidth;
        pWinInfo->height   = channelHeight;
        pWinInfo->outStartX = 0;
        pWinInfo->outStartY = winId*(channelHeight+channelSpacingVer);
     }

    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;

}

/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for multi camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_ov490VipMultiCam_Sgx3Dsrv_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 portId[],
                        UInt32 numLvdsCh
                        )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrm;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));

    pPrm->numVipInst = numLvdsCh;

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];

        UTILS_assert(portId != NULL);
        pInstPrm->vipInstId     =   portId[i];

        pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
        pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
        pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
        pInstPrm->numStream     =   1;

        pInprms = &pInstPrm->inParams;

        pInprms->width      =   captureInWidth;
        pInprms->height     =   captureInHeight;
        pInprms->dataFormat =   SYSTEM_DF_YUV422P;
        pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   pInprms->width;
            pOutprms->height        =   pInprms->height;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            pOutprms->scEnable      =   FALSE;

            /* sub-frame not supported, set to FALSE */
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

        }
        pScPrm = &pInstPrm->scPrms;
        pScPrm->inCropCfg.cropStartX = 0;
        pScPrm->inCropCfg.cropStartY = 0;
        pScPrm->inCropCfg.cropWidth = pInprms->width;
        pScPrm->inCropCfg.cropHeight = pInprms->height;

        pScPrm->scCfg.bypass       = FALSE;
        pScPrm->scCfg.nonLinear    = FALSE;
        pScPrm->scCfg.stripSize    = 0;

        pScPrm->userCoeff = FALSE;

        /* pScPrm->scCoeffCfg is not reuquired in case
         * pScPrm->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;

        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                            SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;

        pPortCfg->actCropEnable                         =   TRUE;
        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
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
Void chains_ov490VipMultiCam_Sgx3Dsrv_SetAppPrms(
            chains_ov490VipMultiCam_Sgx3DsrvObj *pUcObj, Void *appObj)
{

    UInt32 displayWidth,displayHeight;
    Chains_ov490VipMultiCam_Sgx3DsrvAppObj *pObj
            = (Chains_ov490VipMultiCam_Sgx3DsrvAppObj*)appObj;

    UInt32 svOutWidth, svOutHeight;

    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    portId[0] = 0;
    portId[1] = 1;
    portId[2] = 2;
    portId[3] = 3;

    pObj->useOV1063x = gUseOv1063x;
    if(TRUE == pObj->useOV1063x)
    {
        portId[0] = 0;
        portId[1] = 2;
        portId[2] = 4;
        portId[3] = 8;
    }

#ifdef BOARD_TYPE_TDA2XX_RVP
    portId[0] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    portId[1] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTA;
    portId[2] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    portId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    portId[4] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    portId[5] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    portId[6] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
    portId[7] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;

#endif
    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    chains_ov490VipMultiCam_Sgx3Dsrv_SetCapturePrms(
            &pUcObj->CapturePrm,
            2560,
            720,
            portId,
            2
            );

    {
        UInt32 i;
        CaptureLink_VipInstParams *pInstPrm;
        for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pInstPrm = &pUcObj->CapturePrm.vipInst[i];
            pInstPrm->numBufs = 5;
            /* skip alternate frame to make it 15fps output for Front camera */
            if (i >= 4)
                pInstPrm->outParams[0].frameSkipMask = 0x2AAAAAAA;
        }
    }

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
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
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    displayWidth,
                                    displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    chains_ov490VipMultiCam_Sgx3Dsrv_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->chainsCfg->numLvdsCh
                        );
    chains_lvdsVipSurroundViewStandalone_SetSelectPrm(
                    &pUcObj->SelectPrm);

    chains_lvdsVipSurroundViewStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );
    chains_lvdsVipSurroundViewStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );

    chains_lvdsVipSurroundViewStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );

    chains_lvdsVipSurroundViewStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );
    chains_lvdsVipSurroundViewStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
    chains_lvdsVipSurroundViewStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
    pUcObj->Display_GrpxPrm.rtParams.tarWidth       = displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight      = displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
    pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

    chains_ov490VipMultiCam_Sgx3Dsrv_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                SGX3DSRV_OUTPUT_FRAME_WIDTH,
                                SGX3DSRV_OUTPUT_FRAME_HEIGHT
                               );

    pUcObj->Display_sv_org1Prm.rtParams.tarWidth   = (float)520;
    pUcObj->Display_sv_org1Prm.rtParams.tarHeight  = (float)880;
    pUcObj->Display_sv_org1Prm.rtParams.posX       = (float)0;
    pUcObj->Display_sv_org1Prm.rtParams.posY       = (float)200;
    pUcObj->Display_sv_org1Prm.displayId           = DISPLAY_LINK_INST_DSS_VID2;

    pUcObj->Display_sv_org2Prm.rtParams.tarWidth   = (float)520;
    pUcObj->Display_sv_org2Prm.rtParams.tarHeight  = (float)880;
    pUcObj->Display_sv_org2Prm.rtParams.posX       = (float)520+880;
    pUcObj->Display_sv_org2Prm.rtParams.posY       = (float)200;
    pUcObj->Display_sv_org2Prm.displayId           = DISPLAY_LINK_INST_DSS_VID3;

    chains_lvdsVipMultiCam_Sgx3Dsrv_SetDisplayPosition(
                    &pUcObj->Display_M4Prm,
                    520,
                    0);
    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        SGX3DSRV_OUTPUT_FRAME_WIDTH,
        SGX3DSRV_OUTPUT_FRAME_HEIGHT
        );


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
 * \param   pObj  [IN] Chains_ov490VipMultiCam_Sgx3DsrvAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_ov490VipMultiCam_Sgx3Dsrv_StartApp(Chains_ov490VipMultiCam_Sgx3DsrvAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();
    chains_ov490VipMultiCam_Sgx3Dsrv_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_ov490VipMultiCam_Sgx3DsrvAppObj
 *
 *******************************************************************************
*/
void chains_ov490VipMultiCam_Sgx3Dsrv_StopApp(Chains_ov490VipMultiCam_Sgx3DsrvAppObj *pObj)
{
     chains_ov490VipMultiCam_Sgx3Dsrv_Stop(&pObj->ucObj);

     chains_ov490VipMultiCam_Sgx3Dsrv_Delete(&pObj->ucObj);

     ChainsCommon_StopDisplayCtrl();

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
Void chains_ov490VipMultiCam_Sgx3Dsrv(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_ov490VipMultiCam_Sgx3DsrvAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;
    chPrev = '1';

    chainsObj.chainsCfg->numLvdsCh = 4;

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        chains_ov490VipMultiCam_Sgx3Dsrv_Create(&chainsObj.ucObj, &chainsObj);

        chains_ov490VipMultiCam_Sgx3Dsrv_StartApp(&chainsObj);

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
                    chains_ov490VipMultiCam_Sgx3Dsrv_printStatistics(&chainsObj.ucObj);
                    chains_ov490VipMultiCam_Sgx3Dsrv_printBufferStatistics(&chainsObj.ucObj);
                    break;
                case 'o':
                case 'O':
                    Vps_printf("Debug option- toggling between OV1063x and OV490 capture\n");
                    Task_sleep(2000U);
                    gUseOv1063x ^= 0x1;
                    done = TRUE;
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_ov490VipMultiCam_Sgx3Dsrv_StopApp(&chainsObj);

        ChainsCommon_SurroundView_CalibDeInit();

    } while(chPrev != '3');
}


