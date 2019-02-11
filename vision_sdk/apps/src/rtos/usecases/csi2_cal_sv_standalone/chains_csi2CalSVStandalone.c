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
#include "chains_csi2CalSVStandalone_priv.h"
#include "chains_csi2CalSVStandalone_issRsz_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_surround_view.h>

/**< Width & Height */
#define CAPTURE_SENSOR_WIDTH        (1280)
/**< Width & Height */
#define CAPTURE_SENSOR_HEIGHT       (720)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK    (800U)
/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH      (5U)

/**< Menu options supported */
char gSrvUc2dRunTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n 1: Store / Erase Calibration LUT"
"\r\n "
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

    chains_csi2CalSVStandaloneObj ucObj;
    chains_csi2CalSVStandalone_issRszObj ucObjIssRsz;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
    VidSensor_CreateParams sensorCreateParam;
    VidSensor_CreateStatus sensorCreateStatus;

    Chains_Ctrl *chainsCfg;

    Bsp_PlatformSocId socId;

} chains_csi2CalSVAppObj;

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
#ifndef SV_DISPLAY_PRE_VIEW
static Void csi2CalSVStandalone_SetVpeSv_CscPrm(VpeLink_CreateParams *pPrm,
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

#ifdef ISS_INCLUDE
static Void csi2CalSVStandalone_SetIssM2MRszSv_CscPrm(
                    IssRszLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 OutWidth,
                    UInt32 OutHeight)
{
    UInt32 chId;
    IssRszLink_ChannelParams *chPrms;

    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->channelParams[chId];

        chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
        chPrms->outParams.widthRszA   = OutWidth;
        chPrms->outParams.heightRszA  = OutHeight;
        chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
        chPrms->numBuffersPerCh = 4U;
    }
}
#endif /* ISS_INCLUDE */
#endif /* SV_DISPLAY_PRE_VIEW */

#ifdef SV_DISPLAY_PRE_VIEW
static Void csi2CalSVStandalone_SetSyncPrm(SyncLink_CreateParams *pPrm,
                                            UInt32 numLvdsCh,
                                            UInt32 syncMode)
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
static Void csi2CalSVStandalone_SetVpePrm(VpeLink_CreateParams *pPrm,
                                            UInt32 numLvdsCh,
                                            UInt32 OutWidth,
                                            UInt32 OutHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;

    pPrm->procCore = VPE_PROCCORE_VPE;
    if (BSP_PLATFORM_SOC_ID_TDA3XX == Bsp_platformGetSocId())
    {
        pPrm->procCore = VPE_PROCCORE_ISS;
    }

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
        chPrms->scCropCfg.cropWidth  = CAPTURE_SENSOR_WIDTH;
        chPrms->scCropCfg.cropHeight = CAPTURE_SENSOR_HEIGHT;
    }
}

static void csi2CalSVStandalone_SetSelectPrm(SelectLink_CreateParams *pPrm)
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
static Void csi2CalSVStandalone_SetAlgDmaSwMsPrm(
                                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                                    UInt32 numLvdsCh,
                                    UInt32 channelWidth,
                                    UInt32 channelHeight,
                                    UInt32 channelSpacingHor,
                                    UInt32 channelSpacingVer)
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
#endif /* SV_DISPLAY_PRE_VIEW */

static Void csi2CalSVStandalone_SetCaptureParams(
                        chains_csi2CalSVAppObj *pObj,
                        IssCaptureLink_CreateParams *pCaptPrm)
{
    UInt32 idx;
    IssCaptureLink_Csi2Params   *pCsi2Prm;
    IssCaptureLink_OutParams    *pOutPrm;
    System_VideoDataFormat      inOutDataFormat;

    memset((void*) pCaptPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pCaptPrm->videoIfMode            = SYSTEM_VIFM_SCH_CSI2;
    pCaptPrm->videoIfWidth           = SYSTEM_VIFW_4LANES;
    pCaptPrm->bufCaptMode            = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;

    for (idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
    {
        pCsi2Prm = &pCaptPrm->csi2Params[idx];

        pCsi2Prm->isCmplxIoCfgValid = FALSE;
        pCsi2Prm->csi2PhyClk        = CAPTURE_UB964_CSI2_CLOCK;

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
    if (BSP_PLATFORM_SOC_ID_TDA3XX == Bsp_platformGetSocId())
    {
        inOutDataFormat = SYSTEM_DF_YUV422I_UYVY;
    }

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
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_LvdsVipSurroundViewStandaloneObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void csi2CalSVStandalone_StartApp(chains_csi2CalSVAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_MultiCam_StartCaptureDevice(pObj->chainsCfg->captureSrc,
                                            NULL,
                                            pObj->numCsi2Ch);

    if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
    {
        chains_csi2CalSVStandalone_Start(&pObj->ucObj);
    }
    else
    {
#ifdef ISS_INCLUDE
        chains_csi2CalSVStandalone_issRsz_Start(&pObj->ucObjIssRsz);
#endif
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
 * \param   pObj   [IN]   Chains_LvdsVipSurroundViewStandaloneObj
 *
 *******************************************************************************
*/
static Void csi2CalSVStandalone_StopAndDeleteApp(chains_csi2CalSVAppObj *pObj)
{
    if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
    {
        chains_csi2CalSVStandalone_Stop(&pObj->ucObj);
        chains_csi2CalSVStandalone_Delete(&pObj->ucObj);
    }
    else
    {
#ifdef ISS_INCLUDE
        chains_csi2CalSVStandalone_issRsz_Stop(&pObj->ucObjIssRsz);
        chains_csi2CalSVStandalone_issRsz_Delete(&pObj->ucObjIssRsz);
#endif
    }

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/*******************************************************************************
 *  Interface Functions
 *******************************************************************************
 */

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
Void chains_csi2CalSVStandalone_SetAppPrms(
                                        chains_csi2CalSVStandaloneObj *pUcObj,
                                        Void *appObj)
{
    chains_csi2CalSVAppObj *pObj
        = (chains_csi2CalSVAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;
    UInt32 displayWidth, displayHeight;

    csi2CalSVStandalone_SetCaptureParams(pObj, &pUcObj->IssCapturePrm);

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
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
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
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
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

#ifdef SV_DISPLAY_PRE_VIEW
    csi2CalSVStandalone_SetSelectPrm(
                    &pUcObj->SelectPrm);

    csi2CalSVStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );
    csi2CalSVStandalone_SetVpePrm(
                    &pUcObj->VPE_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440
                    );

    csi2CalSVStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );

    csi2CalSVStandalone_SetSyncPrm(
                    &pUcObj->Sync_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    FALSE
                    );
    csi2CalSVStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org1Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
    csi2CalSVStandalone_SetAlgDmaSwMsPrm(
                    &pUcObj->Alg_DmaSwMs_sv_org2Prm,
                    pObj->chainsCfg->numLvdsCh/2,
                    520,
                    440,
                    0,
                    0
                    );
#endif /* SV_DISPLAY_PRE_VIEW */

#ifndef SV_DISPLAY_PRE_VIEW
    csi2CalSVStandalone_SetVpeSv_CscPrm(
                    &pUcObj->VPE_sv_cscPrm,
                    pObj->chainsCfg->numLvdsCh,
                    pObj->captureOutWidth,
                    pObj->captureOutHeight
                    );
#endif /* SV_DISPLAY_PRE_VIEW */

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.disablePreview = TRUE;

    pUcObj->Display_svPrm.rtParams.posX            = (float)520;
    pUcObj->Display_svPrm.rtParams.posY            = (float)0;

#ifdef SV_DISPLAY_PRE_VIEW
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
#endif /* SV_DISPLAY_PRE_VIEW */

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
#ifdef ISS_INCLUDE
Void chains_csi2CalSVStandalone_issRsz_SetAppPrms(
                                        chains_csi2CalSVStandalone_issRszObj *pUcObj,
                                        Void *appObj)
{
    chains_csi2CalSVAppObj *pObj
        = (chains_csi2CalSVAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;
    UInt32 displayWidth, displayHeight;

    csi2CalSVStandalone_SetCaptureParams(pObj, &pUcObj->IssCapturePrm);

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
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
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
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    CAPTURE_SENSOR_WIDTH,
                                    CAPTURE_SENSOR_HEIGHT,
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

    csi2CalSVStandalone_SetIssM2MRszSv_CscPrm(
                                    &pUcObj->IssM2mResizer_sv_cscPrm,
                                    pObj->chainsCfg->numLvdsCh,
                                    pObj->captureOutWidth,
                                    pObj->captureOutHeight);

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.disablePreview = TRUE;

    pUcObj->Display_svPrm.rtParams.posX            = (float)520;
    pUcObj->Display_svPrm.rtParams.posY            = (float)0;
}
#endif

/**
 *******************************************************************************
 *
 * \brief   4 Channel 2D Surround view display based on
 *                                          OV10635/SAT0088 & UB960 with TDA2Ex
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
Void Chains_csi2CalSVStandalone(Chains_Ctrl *chainsCfg)
{
    Int32 chDirRet;
    char ch;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    chains_csi2CalSVAppObj chainsObj;
    Bool ucCreated = FALSE;

    chainsObj.chainsCfg = chainsCfg;

    chDirRet = ChainsCommon_Osal_fileChDir(SRV_DIR_2X);

    if ((CHAINS_CAPTURE_SRC_UB964_OV1063X != chainsCfg->captureSrc) ||
        (4U != chainsCfg->numLvdsCh))
    {
        Vps_printf("\n Camera Selected or Number of LVDS Channels or Display is "
                    " not 1080P60, Please try again \n");
        done = TRUE;
    }

    if (BSPUTILS_UB964_VERSION_ID != BspUtils_appGetUb96xVersion(0U))
    {
        Vps_printf("\n Requires an UB964!!! Cannot stream out YUV422I (8 bit)");
        done = TRUE;
    }
    chainsObj.socId = Bsp_platformGetSocId();
    if ((BSP_PLATFORM_SOC_ID_TDA3XX != chainsObj.socId) &&
        (BSP_PLATFORM_SOC_ID_TDA2EX != chainsObj.socId))
    {
        Vps_printf("\n CSI2 Based usecases not supported on this SoC \n");
        done = TRUE;
    }

    if (FALSE == done)
    {
        /*  On TDA2EX
            4 Channels of 1.2 MP video could be received on 2 lanes, following
            changes would be required
            1. Set numLanesOnPhy0Csi2 to 2
            2. Set UB960 to stream on 2 lanes

            On J6 Entry
            There are only 2 lanes available, set numLanesOnPhy0Csi2 to 2
            UB960 is configured for 2 lanes for J6 E
         */
        chainsObj.numLanesOnPhy0Csi2 = 4U;
        if (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType())
        {
            chainsObj.numLanesOnPhy0Csi2 = 2U;
        }

        chainsObj.captureOutWidth   = CAPTURE_SENSOR_WIDTH;
        chainsObj.captureOutHeight  = CAPTURE_SENSOR_HEIGHT;
        chainsObj.numCsi2Ch         = chainsCfg->numLvdsCh;

        /* Set startWithCalibration = TRUE to start the demo with
            calibration. Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(startWithCalibration,
                                        chainsObj.chainsCfg->svOutputMode);

        if(BSP_PLATFORM_SOC_ID_TDA2EX == chainsObj.socId)
        {
            chains_csi2CalSVStandalone_Create(&chainsObj.ucObj, &chainsObj);
        }
        else
        {
#ifdef ISS_INCLUDE
            chains_csi2CalSVStandalone_issRsz_Create(&chainsObj.ucObjIssRsz, &chainsObj);
#endif
        }

        csi2CalSVStandalone_StartApp(&chainsObj);

        ucCreated = TRUE;
    }

    while(FALSE == done)
    {
        Vps_printf(gSrvUc2dRunTimeMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                ChainsCommon_SurroundView_MenuCalibration();
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();

                if(BSP_PLATFORM_SOC_ID_TDA2EX == chainsObj.socId)
                {
                    chains_csi2CalSVStandalone_printStatistics(&chainsObj.ucObj);
                }
                else
                {
#ifdef ISS_INCLUDE
                    chains_csi2CalSVStandalone_issRsz_printStatistics(
                                                                &chainsObj.ucObjIssRsz);
#endif
                }
                break;
            default:
                Vps_printf("\nUnsupported option '%c'."
                                            " Please try again\n", ch);
                break;
        }
    }

    if(TRUE == ucCreated)
    {
        csi2CalSVStandalone_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
    }

    if (SYSTEM_LINK_STATUS_SOK == chDirRet)
    {
        File_chDir("/\0");
    }
}

