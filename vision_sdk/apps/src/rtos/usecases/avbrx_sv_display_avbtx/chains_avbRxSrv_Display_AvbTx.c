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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_avbRxSrvAvbTx_priv.h"
#include "chains_avbRxSrvDisplay_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common.h>
#include <src/include/chains_common_osal.h>

/* To enable DMA Mosaic view uncomment below and change chains_avbRxSrvDisplay.txt */
// #define ENABLE_DMAMOSAIC_VIEW

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

    chains_avbRxSrvDisplayObj ucDisplayObj;
    chains_avbRxSrvAvbTxObj   ucAvbTxObj;

    System_IVideoFormat codecType;
    UInt32 displayWidth;
    UInt32 displayHeight;
    UInt32 enableDisplayFlag;
    UInt32  netProcId;

    Chains_Ctrl *chainsCfg;

} chains_avbRxSrv_Display_AvbTxAppObj;

void chains_avbRxSrv_Display_AvbTx_SetUseCaseCfg(chains_avbRxSrv_Display_AvbTxAppObj *pObj);

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (0x7FFFFFFF)
#define SYNC_DROP_THRESHOLD_IN_MSEC     (150)

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
static Void chains_avbRxSrv_Display_AvbTx_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh)
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

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
Void chains_avbRxSrv_Display_AvbTx_SetDispWbPrms(
                                CaptureLink_CreateParams *pPrm,
                                chains_avbRxSrv_Display_AvbTxAppObj *pObj)
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
    pPrm->dssWbInst[0].dssWbOutputPrms.wbWidth = 1280;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbHeight = 720;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbDataFmt = SYSTEM_DF_YUV420SP_UV;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbScanFormat = scanFormat;

    pPrm->dssWbInst[0].numBufs = 4U;

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
static Void chains_avbRxSrv_Display_AvbTx_SetEncPrms(
                   EncLink_CreateParams *pPrm,
                   chains_avbRxSrv_Display_AvbTxAppObj *pObj)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 4;
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

Void chains_avbRxSrv_Display_AvbTx_SetAvbTxPrms( AvbTxLink_CreateParams *pPrm,
                                        chains_avbRxSrv_Display_AvbTxAppObj *pObj)
{
}

#ifdef ENABLE_DMAMOSAIC_VIEW
/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          chains_avbRxSurroundView_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 * \param   pPrm         [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_avbRxSurroundView_SetVpePrm(
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
#endif

#ifdef ENABLE_DMAMOSAIC_VIEW
static void chains_avbRxSurroundView_SetSelectPrm(
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
#endif

#ifdef ENABLE_DMAMOSAIC_VIEW
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
static Void chains_avbRxSurroundView_SetAlgDmaSwMsPrm(
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
#endif

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
Void chains_avbRxSrvDisplay_SetAppPrms(chains_avbRxSrvDisplayObj *pUcObj, Void *appObj)
{
    chains_avbRxSrv_Display_AvbTxAppObj *pObj
        = (chains_avbRxSrv_Display_AvbTxAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;

    /*
     * In use-case.txt AVB is configured on IPU1_1. This needs change/tweak it
     * to run on core where networking(NDK) is enabled by user via config file
     * (cfg.mk). Below code connects links such a way that AVB links gets assigned
     * to core running networking stack. This way user don’t have to change
     * use-case every time networking is moved.
     */
    pUcObj->IPCOut_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCOut_IPU1_1_IPU1_0_0LinkID);

    pUcObj->AvbRxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->AvbRxLinkID);

    pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID);

    pUcObj->AvbTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->AvbTxLinkID);


    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &pObj->displayWidth,
                                    &pObj->displayHeight);

    ChainsCommon_SetAvbRxPrm(
                            &pUcObj->AvbRxPrm,
                            SRV_LVDS_CAPTURE_WIDTH,
                            SRV_LVDS_CAPTURE_HEIGHT,
                            pObj->chainsCfg->numLvdsCh);

    ChainsCommon_SetDecodePrm(
                            &pUcObj->DecodePrm,
                            SRV_LVDS_CAPTURE_WIDTH,
                            SRV_LVDS_CAPTURE_HEIGHT,
                            pObj->chainsCfg->numLvdsCh,
                            pObj->codecType);

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_svPrm, pObj->chainsCfg->numLvdsCh, 0); /* 0: Loose Sync */

    chains_avbRxSrv_Display_AvbTx_SetSyncPrm(
                    &pUcObj->Sync_svPrm,
                    pObj->chainsCfg->numLvdsCh);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode,
                                    pObj->chainsCfg->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlignParams(
                                    &pUcObj->Alg_GeoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode);

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    /* Display */
    ChainsCommon_SurroundView_SetDisplayPrm(
                                    &pUcObj->Display_svPrm,
                                    NULL,
                                    NULL,
                                    &pUcObj->Display_GrpxPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    ChainsCommon_StartDisplayCtrl(
                                    pObj->chainsCfg->displayType,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

#ifdef ENABLE_DMAMOSAIC_VIEW
    chains_avbRxSurroundView_SetSelectPrm(
                    &pUcObj->SelectPrm);

    chains_avbRxSurroundView_SetVpePrm(
                    &pUcObj->VPE_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );
    chains_avbRxSurroundView_SetVpePrm(
                    &pUcObj->VPE_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );

    chains_avbRxSrv_Display_AvbTx_SetSyncPrm(
                    &pUcObj->Sync_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2);

    chains_avbRxSrv_Display_AvbTx_SetSyncPrm(
                    &pUcObj->Sync_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2);

    chains_avbRxSurroundView_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
    chains_avbRxSurroundView_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
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

#endif // #ifdef ENABLE_DMAMOSAIC_VIEW

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.enableJeepOverlay = TRUE;

    pUcObj->Display_svPrm.rtParams.posX            = (float)520;
    pUcObj->Display_svPrm.rtParams.posY            = (float)0;



    chains_avbRxSrv_Display_AvbTx_SetDispWbPrms(&pUcObj->Capture_dsswbPrm, pObj);

    chains_avbRxSrv_Display_AvbTx_SetEncPrms(&pUcObj->EncodePrm, pObj);

    ChainsCommon_SetAvbTxPrm(&pUcObj->AvbTxPrm,
                             AVB_TX_LINK_MAX_TALKERS_DEFAULT,
                             pObj->codecType);
    chains_avbRxSrv_Display_AvbTx_SetAvbTxPrms(&pUcObj->AvbTxPrm, pObj);

}


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
Void chains_avbRxSrvAvbTx_SetAppPrms(chains_avbRxSrvAvbTxObj *pUcObj, Void *appObj)
{
    chains_avbRxSrv_Display_AvbTxAppObj *pObj
        = (chains_avbRxSrv_Display_AvbTxAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;

    /*
     * In use-case.txt AVB is configured on IPU1_1. This needs change/tweak it
     * to run on core where networking(NDK) is enabled by user via config file
     * (cfg.mk). Below code connects links such a way that AVB links gets assigned
     * to core running networking stack. This way user don’t have to change
     * use-case every time networking is moved.
     */
    pUcObj->IPCOut_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCOut_IPU1_1_IPU1_0_0LinkID);

    pUcObj->AvbRxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->AvbRxLinkID);

    pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID);

    pUcObj->AvbTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->AvbTxLinkID);


    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &pObj->displayWidth,
                                    &pObj->displayHeight);

    ChainsCommon_SetAvbRxPrm(
                            &pUcObj->AvbRxPrm,
                            SRV_LVDS_CAPTURE_WIDTH,
                            SRV_LVDS_CAPTURE_HEIGHT,
                            pObj->chainsCfg->numLvdsCh);

    ChainsCommon_SetDecodePrm(
                            &pUcObj->DecodePrm,
                            SRV_LVDS_CAPTURE_WIDTH,
                            SRV_LVDS_CAPTURE_HEIGHT,
                            pObj->chainsCfg->numLvdsCh,
                            pObj->codecType);

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_svPrm, pObj->chainsCfg->numLvdsCh, 0); /* 0: Loose Sync */

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode,
                                    pObj->chainsCfg->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlignParams(
                                    &pUcObj->Alg_GeoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    190,
                                    360,
                                    pObj->chainsCfg->svOutputMode);

   chains_avbRxSrv_Display_AvbTx_SetSyncPrm(
                    &pUcObj->Sync_svPrm,
                    pObj->chainsCfg->numLvdsCh);

    chains_avbRxSrv_Display_AvbTx_SetEncPrms(&pUcObj->EncodePrm, pObj);

    ChainsCommon_SetAvbTxPrm(&pUcObj->AvbTxPrm,
                             AVB_TX_LINK_MAX_TALKERS_DEFAULT,
                             pObj->codecType);
    chains_avbRxSrv_Display_AvbTx_SetAvbTxPrms(&pUcObj->AvbTxPrm, pObj);

}

/**
 *******************************************************************************
 *
 * \brief   Start the avbSurroundView display Links
 *
 *          Function sends a control command to avb  and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_avbRxSrv_Display_AvbTxAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_avbRxSrv_Display_AvbTx_StartApp(chains_avbRxSrv_Display_AvbTxAppObj *pObj)
{
    Chains_memPrintHeapStatus();

#if defined (TDA2EX_BUILD) && !defined(TDA2EX_ETHSRV_BOARD)
    /*Select Ethernet port depending on TDA2ex board revision*/
    ChainsCommon_tda2exSelectPHY(pObj->chainsCfg->captureSrc);
#endif

#if defined(TDA2EX_ETHSRV_BOARD)
    /* For Eth camera we don't use captureOutHeight and captureOutWidth params */
    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        0U /* captureOutWidth */,
        0U /* captureOutHeight */
        );
#endif

    if (TRUE == pObj->enableDisplayFlag)
    {
        chains_avbRxSrvDisplay_Start(&pObj->ucDisplayObj);
        ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    }
    else
    {
        chains_avbRxSrvAvbTx_Start(&pObj->ucAvbTxObj);
    }

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the avb display Links
 *
 *          Function sends a control command to all link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_avbRxSrv_Display_AvbTxAppObj
 *
 *******************************************************************************
*/
Void chains_avbRxSrv_Display_AvbTx_StopAndDeleteApp(chains_avbRxSrv_Display_AvbTxAppObj *pObj)
{
    if (TRUE == pObj->enableDisplayFlag)
    {
        chains_avbRxSrvDisplay_Stop(&pObj->ucDisplayObj);
        chains_avbRxSrvDisplay_Delete(&pObj->ucDisplayObj);

        ChainsCommon_StopDisplayCtrl();
        ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);
    }
    else
    {
        chains_avbRxSrvAvbTx_Stop(&pObj->ucAvbTxObj);
        chains_avbRxSrvAvbTx_Delete(&pObj->ucAvbTxObj);
    }

#if defined(TDA2EX_ETHSRV_BOARD)
    /* For Eth camera we don't use captureOutHeight and captureOutWidth params */
    ChainsCommon_StopCaptureDevice( pObj->chainsCfg->captureSrc );
#endif

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string for codec Type Selection.
 *******************************************************************************
 */
char chains_avbRxSrv_Display_AvbTx_codecTypeSelectMenu[] = {
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
 * \brief Run Time Menu string for Use-case mode
 *******************************************************************************
 */
static char gChains_menuUseCaseMode[] = {
    "\r\n "
    "\r\n Select Use-case Config, "
    "\r\n --------------------"
    "\r\n 1: AVB TX Only "
    "\r\n 2: HDMI Display "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

void chains_avbRxSrv_Display_AvbTx_SetUseCaseCfg(chains_avbRxSrv_Display_AvbTxAppObj *pObj)
{
    char ch;
    UInt32 done = FALSE;

#ifdef ENABLE_CODEC_SELECTION
    while(!done)
    {

        Vps_printf(chains_avbRxSrv_Display_AvbTx_codecTypeSelectMenu);
        ch = Chains_readChar();
        switch(ch)
        {
            case '0':
                pObj->codecType = SYSTEM_IVIDEO_MJPEG;
                done = TRUE;
            break;
            case '1':
                pObj->codecType = SYSTEM_IVIDEO_H264HP;
                done = TRUE;
            break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                       pObj->codecType);
            break;
        }
    }
#else
    pObj->codecType = SYSTEM_IVIDEO_H264HP;
#endif
    done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuUseCaseMode);

        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                pObj->enableDisplayFlag = FALSE;
                done = TRUE;
                break;
            case '2':
                pObj->enableDisplayFlag = TRUE;
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief   AVB Surround view Display usecase function
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
Void Chains_avbRxSrv_Display_AvbTx(Chains_Ctrl *chainsCfg)
{
    Int32 chDirRet;
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    chains_avbRxSrv_Display_AvbTxAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chDirRet = ChainsCommon_Osal_fileChDir(SRV_DIR_2X);

    chains_avbRxSrv_Display_AvbTx_SetUseCaseCfg(&chainsObj);

    chainsObj.netProcId = Utils_netGetProcId();
    if(chainsObj.netProcId==System_getSelfProcId())
    {
        Vps_printf(" \n");
        Vps_printf(" CHAINS: ERROR: Networking/NDK MUST be run on different CPU"
                   " than IPU1-0.\n");
        Vps_printf(" CHAINS: ERROR: If you need to run this use-case with NDK"
                   " on IPU1-0 then regenerate the use-case with NullSrc/Null"
                   " links on IPU1-0.\n"
                   );
        Vps_printf(" \n");
        return;
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

        if (TRUE == chainsObj.enableDisplayFlag)
        {
            chains_avbRxSrvDisplay_Create(&chainsObj.ucDisplayObj, &chainsObj);
        }
        else
        {
            chains_avbRxSrvAvbTx_Create(&chainsObj.ucAvbTxObj, &chainsObj);
        }

        chains_avbRxSrv_Display_AvbTx_StartApp(&chainsObj);

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
                    if (TRUE == chainsObj.enableDisplayFlag)
                    {
                        chains_avbRxSrvDisplay_printStatistics(&chainsObj.ucDisplayObj);
                    }
                    else
                    {
                        chains_avbRxSrvAvbTx_printStatistics(&chainsObj.ucAvbTxObj);
                    }

                    /* Show IVA load */
                    System_linkControl(SYSTEM_LINK_ID_VDEC_0,
                                    SYSTEM_CMD_PRINT_STATISTICS, NULL, 0, TRUE);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_avbRxSrv_Display_AvbTx_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
    } while(chPrev!='3');

    if (SYSTEM_LINK_STATUS_SOK == chDirRet)
    {
        File_chDir("/\0");
    }
}
