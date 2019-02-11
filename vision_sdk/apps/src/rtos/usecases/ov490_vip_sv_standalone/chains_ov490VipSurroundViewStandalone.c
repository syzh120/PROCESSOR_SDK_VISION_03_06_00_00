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
#include "chains_ov490VipSurroundViewStandalone_priv.h"
#include <src/include/chains_common.h>

/* Use OV1063x based mult-deser setup - only for debug */
static volatile UInt32 gUseOv1063x = 0;
static UInt32 pinMuxBackup[50];

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char chains_ov490VipSurroundView_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 1: Use OV1063x mult-des setup (for debug only)"
    "\r\n "
    "\r\n 2: Toggle pix_clk polarity (try only in case of display artifacts)"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

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

    chains_ov490VipSurroundViewStandaloneObj ucObj;

    UInt32  useOV1063x;
    /**< Use OV1063x based multi-deser board */

    Chains_Ctrl *chainsCfg;

} Chains_Ov490VipSurroundViewStandaloneAppObj;

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define TIGHT_SYNC_DELTA_IN_MSEC              (16)
#define LOOSE_SYNC_DELTA_IN_MSEC              (0x7FFFFFFF)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC     (33)
#define LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC     (0x7FFFFFFF)

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
static Void chains_ov490VipSurroundViewStandalone_SetSyncPrm(
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
static Void chains_ov490VipSurroundViewStandalone_SetVpePrm(
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

static void chains_ov490VipSurroundViewStandalone_SetSelectPrm(
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
static Void chains_ov490VipSurroundViewStandalone_SetAlgDmaSwMsPrm(
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
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_ov490VipSurroundViewStandalone_SetAppPrms(chains_ov490VipSurroundViewStandaloneObj *pUcObj, Void *appObj)
{
    Chains_Ov490VipSurroundViewStandaloneAppObj *pObj
        = (Chains_Ov490VipSurroundViewStandaloneAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;
    UInt32 displayWidth, displayHeight;

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

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_svPrm, pObj->chainsCfg->numLvdsCh, 1); /* 1: Tight Sync */

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
    ChainsCommon_SurroundView_SetGAlignParams(
                                    &pUcObj->Alg_GeoAlignPrm,
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

    /* Display */
    ChainsCommon_SurroundView_SetDisplayPrm(
                                    &pUcObj->Display_svPrm,
                                    NULL,
                                    NULL,
                                    &pUcObj->Display_GrpxPrm,
                                    displayWidth,
                                    displayHeight);

    ChainsCommon_StartDisplayCtrl(
                                    pObj->chainsCfg->displayType,
                                    displayWidth,
                                    displayHeight);

    ChainsCommon_MultiCam_SetCapturePrms(&pUcObj->CapturePrm,
            2560,
            720,
            portId,
            2
            );

    chains_ov490VipSurroundViewStandalone_SetSelectPrm(
                    &pUcObj->SelectPrm);

    chains_ov490VipSurroundViewStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );
    chains_ov490VipSurroundViewStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );

    chains_ov490VipSurroundViewStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );
    chains_ov490VipSurroundViewStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );

    chains_ov490VipSurroundViewStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
    chains_ov490VipSurroundViewStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;

    pUcObj->Display_svPrm.rtParams.posX            = (float)520;
    pUcObj->Display_svPrm.rtParams.posY            = (float)0;

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
 * \param   pObj  [IN] Chains_Ov490VipSurroundViewStandaloneObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_ov490VipSurroundViewStandalone_StartApp(Chains_Ov490VipSurroundViewStandaloneAppObj *pObj)
{
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    portId[0] = 0;
    portId[1] = 1;
    portId[2] = 2;
    portId[3] = 3;

    if(TRUE == pObj->useOV1063x)
    {
        portId[0] = 0;
        portId[1] = 2;
        portId[2] = 4;
        portId[3] = 8;
    }

    Chains_memPrintHeapStatus();

    if(TRUE == pObj->useOV1063x)
    {
        ChainsCommon_MultiCam_StartCaptureDevice(
            CHAINS_CAPTURE_SRC_OV10635,
            portId,
            2
            );
    }
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_ov490VipSurroundViewStandalone_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_Ov490VipSurroundViewStandaloneObj
 *
 *******************************************************************************
*/
Void chains_ov490VipSurroundViewStandalone_StopAndDeleteApp(Chains_Ov490VipSurroundViewStandaloneAppObj *pObj)
{
    chains_ov490VipSurroundViewStandalone_Stop(&pObj->ucObj);
    chains_ov490VipSurroundViewStandalone_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    if(TRUE == pObj->useOV1063x)
    {
        ChainsCommon_StopCaptureDevice(CHAINS_CAPTURE_SRC_OV10635);
    }
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Set use-case specific pin-mux
 *
 *******************************************************************************
 */
Void chains_ov490VipSurroundViewStandalone_setPinMux()
{
    UInt32 isLocked[2];
    UInt32 i = 0;

    /* MMR_LOCK_5 */
    if (0x6F361E05 == *(volatile UInt32 *)(0x4A002550))
    {
        isLocked[0] = 0;
    }
    else
    {
        isLocked[0] = 1;
        *(volatile UInt32 *)(0x4A002550) = 0x6F361E05;
    }
    /* MMR_LOCK_1 */
    if (0x2FF1AC2B == *(volatile UInt32 *)(0x4A002540))
    {
        isLocked[1] = 0;
    }
    else
    {
        isLocked[1] = 1;
        *(volatile UInt32 *)(0x4A002540) = 0x2FF1AC2B;
    }

    /* VIN1A PCLK/H/V */
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034DC);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034EC);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034F0);

    /* VIN1A Dx */
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034F4);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034F8);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034FC);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003500);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003504);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003508);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A00350C);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003510);

    /* VIN1B PCLK/H/V */
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034E0);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034E4);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A0034E8);

    /* VIN1B Dx */
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003514);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003518);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A00351C);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003520);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003524);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003528);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A00352C);
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A003530);

    /* PCLK pol */
    pinMuxBackup[i++] = *(volatile UInt32 *)(0x4A002534);

    if(0 == gUseOv1063x)
    {
        /* VIN1A PCLK/H/V */
        *(volatile UInt32 *)(0x4A0034DC) = 0x40000;
        *(volatile UInt32 *)(0x4A0034EC) = 0x40000;
        *(volatile UInt32 *)(0x4A0034F0) = 0x40000;

        /* VIN1A Dx */
        *(volatile UInt32 *)(0x4A0034F4) = 0x40000;
        *(volatile UInt32 *)(0x4A0034F8) = 0x40000;
        *(volatile UInt32 *)(0x4A0034FC) = 0x40000;
        *(volatile UInt32 *)(0x4A003500) = 0x40000;
        *(volatile UInt32 *)(0x4A003504) = 0x40000;
        *(volatile UInt32 *)(0x4A003508) = 0x40000;
        *(volatile UInt32 *)(0x4A00350C) = 0x40000;
        *(volatile UInt32 *)(0x4A003510) = 0x40000;

        /* VIN1B PCLK/H/V */
        *(volatile UInt32 *)(0x4A0034E0) = 0xC0000;
        *(volatile UInt32 *)(0x4A0034E4) = 0x40001;
        *(volatile UInt32 *)(0x4A0034E8) = 0x40001;

        /* VIN1B Dx */
        *(volatile UInt32 *)(0x4A003514) = 0x40001;
        *(volatile UInt32 *)(0x4A003518) = 0x40001;
        *(volatile UInt32 *)(0x4A00351C) = 0x40001;
        *(volatile UInt32 *)(0x4A003520) = 0x40001;
        *(volatile UInt32 *)(0x4A003524) = 0x40001;
        *(volatile UInt32 *)(0x4A003528) = 0x40001;
        *(volatile UInt32 *)(0x4A00352C) = 0x40001;
        *(volatile UInt32 *)(0x4A003530) = 0x40001;

        /* PCLK pol */
        *(volatile UInt32 *)(0x4A002534) |= 0x5;
    }

    if(1 == isLocked[0])
    {
        /* MMR_LOCK_5 */
        *(volatile UInt32 *)(0x4A002550) = 0x143F832C;
    }
    if(1 == isLocked[1])
    {
        /* MMR_LOCK_1 */
        *(volatile UInt32 *)(0x4A002540) = 0x1A1C8144;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Restore original pinmux settings
 *
 *******************************************************************************
 */
Void chains_ov490VipSurroundViewStandalone_restorePinMux()
{
    UInt32 isLocked[2];
    UInt32 i = 0;

    /* MMR_LOCK_5 */
    if (0x6F361E05 == *(volatile UInt32 *)(0x4A002550))
    {
        isLocked[0] = 0;
    }
    else
    {
        isLocked[0] = 1;
        *(volatile UInt32 *)(0x4A002550) = 0x6F361E05;
    }
    /* MMR_LOCK_1 */
    if (0x2FF1AC2B == *(volatile UInt32 *)(0x4A002540))
    {
        isLocked[1] = 0;
    }
    else
    {
        isLocked[1] = 1;
        *(volatile UInt32 *)(0x4A002540) = 0x2FF1AC2B;
    }

    /* VIN1A PCLK/H/V */
    *(volatile UInt32 *)(0x4A0034DC) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034EC) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034F0) = pinMuxBackup[i++];

    /* VIN1A Dx */
    *(volatile UInt32 *)(0x4A0034F4) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034F8) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034FC) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003500) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003504) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003508) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A00350C) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003510) = pinMuxBackup[i++];

    /* VIN1B PCLK/H/V */
    *(volatile UInt32 *)(0x4A0034E0) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034E4) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A0034E8) = pinMuxBackup[i++];

    /* VIN1B Dx */
    *(volatile UInt32 *)(0x4A003514) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003518) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A00351C) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003520) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003524) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003528) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A00352C) = pinMuxBackup[i++];
    *(volatile UInt32 *)(0x4A003530) = pinMuxBackup[i++];

    /* PCLK pol */
    *(volatile UInt32 *)(0x4A002534) = pinMuxBackup[i++];

    if(1 == isLocked[0])
    {
        /* MMR_LOCK_5 */
        *(volatile UInt32 *)(0x4A002550) = 0x143F832C;
    }
    if(1 == isLocked[1])
    {
        /* MMR_LOCK_1 */
        *(volatile UInt32 *)(0x4A002540) = 0x1A1C8144;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Toggle PCLK polarity
 *
 *******************************************************************************
 */
static Void chains_ov490VipSurroundViewStandalone_togglePclkPol()
{
    /* PCLK pol */
    if(0x5 == *(volatile UInt32 *)(0x4A002534) & 0x5)
    {
        *(volatile UInt32 *)(0x4A002534) &= ~0x5U;
    }
    else
    {
        *(volatile UInt32 *)(0x4A002534) |= 0x5U;
    }
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
Void Chains_ov490VipSurroundViewStandalone(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev = '1';
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_Ov490VipSurroundViewStandaloneAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_ov490VipSurroundViewStandalone_setPinMux();

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        chains_ov490VipSurroundViewStandalone_Create(&chainsObj.ucObj, &chainsObj);
        chains_ov490VipSurroundViewStandalone_StartApp(&chainsObj);

        while(!done)
        {
            Vps_printf(chains_ov490VipSurroundView_runTimeMenu);
            ch = Chains_readChar();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_ov490VipSurroundViewStandalone_printStatistics(&chainsObj.ucObj);
                    break;
                case '1':
                    gUseOv1063x ^= 0x1;
                    done = TRUE;
                    break;
                case '2':
                    chains_ov490VipSurroundViewStandalone_togglePclkPol();
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_ov490VipSurroundViewStandalone_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
    } while(chPrev!='3');

    chains_ov490VipSurroundViewStandalone_restorePinMux();
}

