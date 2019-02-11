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
 * \version 0.0 (Jun 2014) : [YM] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include "chains_avbRxSgx3DSrv_priv.h"
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
#define SYNC_DELTA_IN_MSEC               (33)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC      (100)


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

    chains_avbRxSgx3DSrvObj ucObj;
    Chains_Ctrl *chainsCfg;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

} Chains_AvbRxSgx3DSrvAppObj;

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
static Void chains_avbRxSgx3DSrv_SetSgx3DsrvLinkPrms (
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
static Void chains_avbRxSgx3DSrv_SetSync1Prm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

static Void chains_avbRxSgx3DSrv_SetDisplayPosition(
                    DisplayLink_CreateParams *pPrm_Video,
                    UInt32 posX,
                    UInt32 posY
                    )
{
    pPrm_Video->rtParams.posX = posX;
    pPrm_Video->rtParams.posY = posY;
}

#if 0
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
static Void chains_avbRxSgx3DSrv_SetSync2Prm(
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
static Void chains_avbRxSgx3DSrv_SetVpePrm(
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

static void chains_avbRxSgx3DSrv_SetSelectPrm(
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
static Void chains_avbRxSgx3DSrv_SetAlgDmaSwMsPrm(
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
Void chains_avbRxSgx3DSrv_SetAppPrms(chains_avbRxSgx3DSrvObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth, displayHeight;
    UInt32 svOutWidth, svOutHeight;

    Chains_AvbRxSgx3DSrvAppObj *pObj
        = (Chains_AvbRxSgx3DSrvAppObj*)appObj;

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
                            SYSTEM_IVIDEO_MJPEG);

    pObj->captureOutWidth  = AVB_TALKER_MAX_FRAME_WIDTH;
    pObj->captureOutHeight = AVB_TALKER_MAX_FRAME_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

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
                                    displayWidth,
                                    displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    chains_avbRxSgx3DSrv_SetSync1Prm(
                        &pUcObj->SyncPrm,
                        pObj->chainsCfg->numLvdsCh
                        );
#if 0
    chains_avbRxSgx3DSrv_SetSelectPrm(
                    &pUcObj->SelectPrm);

    chains_avbRxSgx3DSrv_SetVpePrm(
                    &pUcObj->VPE_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );
    chains_avbRxSgx3DSrv_SetVpePrm(
                    &pUcObj->VPE_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );

    chains_avbRxSgx3DSrv_SetSync2Prm(
                    &pUcObj->Sync_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );

    chains_avbRxSgx3DSrv_SetSync2Prm(
                    &pUcObj->Sync_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );
    chains_avbRxSgx3DSrv_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
    chains_avbRxSgx3DSrv_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
#endif

        pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
        pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
        pUcObj->Display_GrpxPrm.rtParams.tarWidth       = displayWidth;
        pUcObj->Display_GrpxPrm.rtParams.tarHeight      = displayHeight;
        pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
        pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
        pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                SGX3DSRV_OUTPUT_FRAME_WIDTH,
                                SGX3DSRV_OUTPUT_FRAME_HEIGHT
                               );
#if 0
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
#endif
    chains_avbRxSgx3DSrv_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

    chains_avbRxSgx3DSrv_SetDisplayPosition(
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
 * \param   pObj  [IN] Chains_VipSingleCameraViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_avbRxSgx3DSrv_StartApp(Chains_AvbRxSgx3DSrvAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    chains_avbRxSgx3DSrv_Start(&pObj->ucObj);
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
Void chains_avbRxSgx3DSrv_StopAndDeleteApp(Chains_AvbRxSgx3DSrvAppObj *pObj)
{
    chains_avbRxSgx3DSrv_Stop(&pObj->ucObj);
    chains_avbRxSgx3DSrv_Delete(&pObj->ucObj);
    ChainsCommon_StopDisplayCtrl();

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);
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
Void Chains_AvbRxSgx3DSrv(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_AvbRxSgx3DSrvAppObj chainsObj;

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

        chains_avbRxSgx3DSrv_Create(&chainsObj.ucObj, &chainsObj);

        chains_avbRxSgx3DSrv_StartApp(&chainsObj);

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
                    chains_avbRxSgx3DSrv_printStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_avbRxSgx3DSrv_StopAndDeleteApp(&chainsObj);

        ChainsCommon_SurroundView_CalibDeInit();

    } while(chPrev != '3');
}




