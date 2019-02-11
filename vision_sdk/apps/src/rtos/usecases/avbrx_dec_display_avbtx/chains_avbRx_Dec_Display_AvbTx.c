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
#include "chains_avbRx_Dec_Display_AvbTx_priv.h"
#include "chains_avbRx_Dec_AvbTx_priv.h"
#include <src/include/chains_common.h>

#define AVB_TALKER_MAX_FRAME_WIDTH 1280
#define AVB_TALKER_MAX_FRAME_HEIGHT 720
#define NUMBER_OF_CHANNELS 4
#define MAX_NUMBER_OF_CHANNELS 4

#define ENABLE_NUM_CH_SELECTION (0)
#define ENABLE_CODEC_SELECTION  (0)

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (66)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (150)

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

    chains_avbRx_Dec_Display_AvbTxObj ucDisplayObj;
    chains_avbRx_Dec_AvbTxObj ucAvbTxObj;

    System_IVideoFormat codecType;
    UInt32  numOfChannels;
    UInt32  displayWidth;
    UInt32  displayHeight;
    UInt32  enableDisplayFlag;
    UInt32  netProcId;

    Chains_Ctrl *chainsCfg;

} Chains_AvbRx_Dec_Display_AvbTxAppObj;

void chains_avbRx_Dec_Display_AvbTx_SetUseCaseCfg(Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj);
/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          chains_avbRx_Dec_Display_AvbTx_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 *          Scale each CH to 1/2x size
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_SetVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numChannels,
                    UInt32 displayWidth,
                    UInt32 displayHeight,
                    System_IVideoFormat codecType
                    )
{
    UInt16 chId;
    UInt32 widthFactor, heightFactor;
    VpeLink_ChannelParams *chPrms;

    pPrm->enableOut[0] = TRUE;

    switch (numChannels)
    {
        case 1:
            widthFactor  = 1;
            heightFactor = 1;
            break;
        case 2:
            widthFactor  = 2;
            heightFactor = 1;
            break;
        case 3:
        case 4:
            widthFactor  = 2;
            heightFactor = 2;
            break;
        case 5:
        case 6:
            widthFactor  = 2;
            heightFactor = 3;
            break;
        default:
            widthFactor  = 2;
            heightFactor = 2;
            break;
    }

    for(chId = 0; chId < numChannels; chId++)
    {
        pPrm->chParams[chId].outParams[0].width
            = SystemUtils_floor(displayWidth/widthFactor, 16);

        pPrm->chParams[chId].outParams[0].height
            = displayHeight/heightFactor;

        pPrm->chParams[chId].outParams[0].dataFormat
            = SYSTEM_DF_YUV420SP_UV;
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 4;

       chPrms = &pPrm->chParams[chId];

       chPrms->scCfg.bypass       = FALSE;
       chPrms->scCfg.nonLinear    = FALSE;
       chPrms->scCfg.stripSize    = 0;

       if (SYSTEM_IVIDEO_MJPEG == codecType)
       {
           chPrms->scCropCfg.cropStartX = 0;
           chPrms->scCropCfg.cropStartY = 0;
       }
       else /*SYSTEM_IVIDEO_H264HP*/
       {
           /* for H264 frame extra data needs to be cropped before displaying */
           chPrms->scCropCfg.cropStartX = 32;
           chPrms->scCropCfg.cropStartY = 24;
       }
       chPrms->scCropCfg.cropWidth  = AVB_TALKER_MAX_FRAME_WIDTH - 32;
       chPrms->scCropCfg.cropHeight = AVB_TALKER_MAX_FRAME_HEIGHT - 24;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          chains_avbRx_Dec_Display_AvbTx_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_SetSyncPrm( SyncLink_CreateParams *pPrm,
                                            UInt32 nunChannel )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
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

 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_SetAlgDmaSwMsPrm(
                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                    UInt32 numChannel,
                    UInt32 displayWidth,
                    UInt32 displayHeight
                   )
{
    UInt32 winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;
    UInt32 widthFactor, heightFactor;

    useLocalEdma = FALSE;

    pPrm->baseClassCreate.algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->maxOutBufWidth     = displayWidth;
    pPrm->maxOutBufHeight    = displayHeight;
    pPrm->numOutBuf          = 4;
    pPrm->useLocalEdma       = useLocalEdma;

    pPrm->initLayoutParams.numWin = numChannel;
    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;

    switch (numChannel)
    {
        case 1:
            widthFactor  = 1;
            heightFactor = 1;
            pPrm->initLayoutParams.numWin = 1;
            break;
        case 2:
            widthFactor  = 2;
            heightFactor = 1;
            pPrm->initLayoutParams.numWin = 2;
            break;
        case 3:
        case 4:
            widthFactor  = 2;
            heightFactor = 2;
            pPrm->initLayoutParams.numWin = 4;
            break;
        case 5:
        case 6:
            widthFactor  = 2;
            heightFactor = 3;
            pPrm->initLayoutParams.numWin = 6;
            break;
        default:
            widthFactor  = 2;
            heightFactor = 2;
            pPrm->initLayoutParams.numWin = 4;
            break;
    }

    /* assuming 4Ch and 2x2 layout */
    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];

        pWinInfo->chId = winId;

        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;

        pWinInfo->width     =
            SystemUtils_floor(pPrm->initLayoutParams.outBufWidth/widthFactor, 16);
        pWinInfo->height    =
            pPrm->initLayoutParams.outBufHeight/heightFactor;

        /* winId == 0 */
        pWinInfo->outStartX = 0;
        pWinInfo->outStartY = 0;

        if(winId==1)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = 0;
        } else
        if(winId==2)
        {
            pWinInfo->outStartX = 0;
            pWinInfo->outStartY = pWinInfo->height;
        } else
        if(winId==3)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = pWinInfo->height;
        } else
        if(winId==4)
        {
            pWinInfo->outStartX = 0;
            pWinInfo->outStartY = 2 * pWinInfo->height;
        } else
        if(winId==5)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = 2 * pWinInfo->height;
        }
    }
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
static Void chains_avbRx_Dec_Display_AvbTx_SetEncPrms(
                   EncLink_CreateParams *pPrm,
                   Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj)
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

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters AVBRx+Decode+Display/AVBTx use-case
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcDisplayObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_SetAppPrms(chains_avbRx_Dec_Display_AvbTxObj *pUcDisplayObj, Void *appObj)
{
    Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj
        = (Chains_AvbRx_Dec_Display_AvbTxAppObj*)appObj;
    /*
     * In use-case.txt AVB is configured on IPU1_1. This needs change/tweak it
     * to run on core where networking(NDK) is enabled by user via config file
     * (cfg.mk). Below code connects links such a way that AVB links gets assigned
     * to core running networking stack. This way user don’t have to change
     * use-case every time networking is moved.
     */
    pUcDisplayObj->IPCOut_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcDisplayObj->IPCOut_IPU1_1_IPU1_0_0LinkID);

    pUcDisplayObj->AvbRxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcDisplayObj->AvbRxLinkID);

    pUcDisplayObj->IPCIn_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcDisplayObj->IPCIn_IPU1_1_IPU1_0_0LinkID);

    pUcDisplayObj->AvbTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcDisplayObj->AvbTxLinkID);

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SetAvbRxPrm(
        &pUcDisplayObj->AvbRxPrm,
        AVB_TALKER_MAX_FRAME_WIDTH,
        AVB_TALKER_MAX_FRAME_HEIGHT,
        pObj->numOfChannels
            );

    ChainsCommon_SetDecodePrm(
                            &pUcDisplayObj->DecodePrm,
                            AVB_TALKER_MAX_FRAME_WIDTH,
                            AVB_TALKER_MAX_FRAME_HEIGHT,
                            pObj->numOfChannels,
                            pObj->codecType);

    chains_avbRx_Dec_Display_AvbTx_SetVpePrm(
        &pUcDisplayObj->VPEPrm,
        pObj->numOfChannels,
        pObj->displayWidth,
        pObj->displayHeight,
        pObj->codecType
        );

    chains_avbRx_Dec_Display_AvbTx_SetSyncPrm(
        &pUcDisplayObj->SyncPrm,
        pObj->numOfChannels
        );

    chains_avbRx_Dec_Display_AvbTx_SetAlgDmaSwMsPrm(
        &pUcDisplayObj->Alg_DmaSwMsPrm,
        pObj->numOfChannels,
        AVB_TALKER_MAX_FRAME_WIDTH,
        AVB_TALKER_MAX_FRAME_HEIGHT
        );

    ChainsCommon_SetGrpxSrcPrms(&pUcDisplayObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    ChainsCommon_SetDisplayPrms(&pUcDisplayObj->Display_VideoPrm,
                                               &pUcDisplayObj->Display_GrpxPrm,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                                );

    chains_avbRx_Dec_Display_AvbTx_SetEncPrms(&pUcDisplayObj->EncodePrm, pObj);

    ChainsCommon_SetAvbTxPrm(&pUcDisplayObj->AvbTxPrm,
                             AVB_TX_LINK_MAX_TALKERS_DEFAULT,
                             pObj->codecType);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters for AVBRx+Decode+AVBTx use-case
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcDisplayObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_AvbTx_SetAppPrms(chains_avbRx_Dec_AvbTxObj *pUcAvbTxObj, Void *appObj)
{
    Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj
        = (Chains_AvbRx_Dec_Display_AvbTxAppObj*)appObj;

    /*
     * In use-case.txt AVB is configured on IPU1_1. This needs change/tweak it
     * to run on core where networking(NDK) is enabled by user via config file
     * (cfg.mk). Below code connects links such a way that AVB links gets assigned
     * to core running networking stack. This way user don’t have to change
     * use-case every time networking is moved.
     */
    pUcAvbTxObj->IPCOut_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcAvbTxObj->IPCOut_IPU1_1_IPU1_0_0LinkID);

    pUcAvbTxObj->AvbRxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcAvbTxObj->AvbRxLinkID);

    pUcAvbTxObj->IPCIn_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcAvbTxObj->IPCIn_IPU1_1_IPU1_0_0LinkID);

    pUcAvbTxObj->AvbTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcAvbTxObj->AvbTxLinkID);

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SetAvbRxPrm(
        &pUcAvbTxObj->AvbRxPrm,
        AVB_TALKER_MAX_FRAME_WIDTH,
        AVB_TALKER_MAX_FRAME_HEIGHT,
        pObj->numOfChannels
            );

    ChainsCommon_SetDecodePrm(
                            &pUcAvbTxObj->DecodePrm,
                            AVB_TALKER_MAX_FRAME_WIDTH,
                            AVB_TALKER_MAX_FRAME_HEIGHT,
                            pObj->numOfChannels,
                            pObj->codecType);

    chains_avbRx_Dec_Display_AvbTx_SetVpePrm(
        &pUcAvbTxObj->VPEPrm,
        pObj->numOfChannels,
        pObj->displayWidth,
        pObj->displayHeight,
        pObj->codecType
        );

    chains_avbRx_Dec_Display_AvbTx_SetSyncPrm(
        &pUcAvbTxObj->SyncPrm,
        pObj->numOfChannels
        );

    chains_avbRx_Dec_Display_AvbTx_SetAlgDmaSwMsPrm(
        &pUcAvbTxObj->Alg_DmaSwMsPrm,
        pObj->numOfChannels,
        AVB_TALKER_MAX_FRAME_WIDTH,
        AVB_TALKER_MAX_FRAME_HEIGHT
        );


    chains_avbRx_Dec_Display_AvbTx_SetEncPrms(&pUcAvbTxObj->EncodePrm, pObj);

    ChainsCommon_SetAvbTxPrm(&pUcAvbTxObj->AvbTxPrm,
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
 * \param   pObj  [IN] Chains_AvbRx_Dec_DisplayObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_StartApp(Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj)
{
    Chains_memPrintHeapStatus();

/*Select Ethernet port depending on TDA2ex board revision*/
#if defined (TDA2EX_BUILD) && !defined(TDA2EX_ETHSRV_BOARD)
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
        chains_avbRx_Dec_Display_AvbTx_Start(&pObj->ucDisplayObj);
        ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    }
    else
    {
        chains_avbRx_Dec_AvbTx_Start(&pObj->ucAvbTxObj);
    }

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
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
 * \param   pObj   [IN]   Chains_AvbRx_Dec_DisplayObj
 *
 *******************************************************************************
*/
Void chains_avbRx_Dec_Display_AvbTx_StopAndDeleteApp(Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj)
{
    if (TRUE == pObj->enableDisplayFlag)
    {
        chains_avbRx_Dec_Display_AvbTx_Stop(&pObj->ucDisplayObj);
        chains_avbRx_Dec_Display_AvbTx_Delete(&pObj->ucDisplayObj);

        ChainsCommon_StopDisplayCtrl();
        ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);
    }
    else
    {
        chains_avbRx_Dec_AvbTx_Stop(&pObj->ucAvbTxObj);
        chains_avbRx_Dec_AvbTx_Delete(&pObj->ucAvbTxObj);
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
char chains_avbRx_Dec_Display_AvbTx_codecTypeSelectMenu[] = {
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
    "\r\n 2: HDMI Display + AVB TX "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

void chains_avbRx_Dec_Display_AvbTx_SetUseCaseCfg(Chains_AvbRx_Dec_Display_AvbTxAppObj *pObj)
{
    char ch;
    UInt32 done = FALSE;

#if (1 == ENABLE_NUM_CH_SELECTION)
    Vps_printf("\n Please Enter No. of channels.Max supported is 4 \n");
    ch = Chains_readChar();
    pObj->numOfChannels = ch - '0';
#else
    pObj->numOfChannels = NUMBER_OF_CHANNELS;
#endif

    if(pObj->numOfChannels > MAX_NUMBER_OF_CHANNELS)
    {
        Vps_printf("\n Number of channel entered is greater than Max number of \
                        supported Channel, setting num of channel to 4 \n");
        pObj->numOfChannels = MAX_NUMBER_OF_CHANNELS;
    }


#if (1 == ENABLE_CODEC_SELECTION)
    while(!done)
    {

        Vps_printf(chains_avbRx_Dec_Display_AvbTx_codecTypeSelectMenu);
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
Void Chains_avbRx_Dec_Display_AvbTx(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_AvbRx_Dec_Display_AvbTxAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_avbRx_Dec_Display_AvbTx_SetUseCaseCfg(&chainsObj);

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

    if (TRUE == chainsObj.enableDisplayFlag)
    {
        chains_avbRx_Dec_Display_AvbTx_Create(&chainsObj.ucDisplayObj, &chainsObj);
    }
    else
    {
        chains_avbRx_Dec_AvbTx_Create(&chainsObj.ucAvbTxObj, &chainsObj);
    }

    chains_avbRx_Dec_Display_AvbTx_StartApp(&chainsObj);

    done = FALSE;
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
                if (TRUE == chainsObj.enableDisplayFlag)
                {
                    chains_avbRx_Dec_Display_AvbTx_printStatistics(&chainsObj.ucDisplayObj);
                }
                else
                {
                    chains_avbRx_Dec_AvbTx_printStatistics(&chainsObj.ucAvbTxObj);
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

    chains_avbRx_Dec_Display_AvbTx_StopAndDeleteApp(&chainsObj);
}

