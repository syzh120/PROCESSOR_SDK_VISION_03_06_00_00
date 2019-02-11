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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file hains_issMultiCamIspSgx3DSrv_SgxDisplay.c
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
#include "chains_issMultiCaptIsp_Sgx3Dsrv_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <vivi_srv.h>
#include "../../ti-plugins/include/srv_chain.h"
#ifndef QNX_BUILD
#include <src/hlos/system/system_gbm_allocator.h>
#endif

#define CAPTURE_SENSOR_WIDTH                 (1280)
#define CAPTURE_SENSOR_HEIGHT                (720)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH          (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT         (1080)

/* Live Video Window Size */
#define LIVE_WIN_WIDTH                      (512)
#define LIVE_WIN_HEIGHT                     (440)

#define LIVE_VIEW_INCLUDED


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
#define SYNC_DROP_THRESHOLD_IN_MSEC          (40)

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
    chains_issMultiCaptIsp_Sgx3DsrvObj  ucObj;

    AppCtrl_IssParams                   appCtrlIssPrms;
    UInt32                              numCh;
    UInt32                              numLvdsCh;

    char                                sensorName[ISS_SENSORS_MAX_NAME];
    IssM2mIspLink_OperatingMode         ispOpMode;

    AlgorithmLink_SrvOutputModes        svOutputMode;
    Bool                                enableCarOverlayInAlg;
#ifndef QNX_BUILD
    Bool 								bEglInfoInCreate;
#endif

} Chains_issMultiCaptIsp_Sgx3DsrvAppObj;

Chains_issMultiCaptIsp_Sgx3DsrvAppObj gIssMultiCaptIsp_Sgx3DsrvObj;

#ifndef QNX_BUILD
static struct control_srv_egl_ctx chainsEglParams = {
    .get_egl_native_display = gbm_allocator_get_native_display,
    .get_egl_native_buffer = gbm_allocator_get_native_buffer,
    .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
};
#endif

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
static Void chains_issMultiCaptIsp_Sgx3Dsrv_SetSgx3DsrvLinkPrms (
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
static Void chains_issMultiCaptIsp_Sgx3Dsrv_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

Void updateParamsForMultiChannel(
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj,
    chains_issMultiCaptIsp_Sgx3DsrvObj *pUcObj,
    UInt32 rszAOutWidth, UInt32 rszAOutHeight,
    UInt32 rszBOutWidth, UInt32 rszBOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pUcObj->IssCapturePrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pUcObj->IssM2mIspPrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;

    pCapturePrm->numCh = pObj->numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;
    pIspPrm->channelParams[0U].outParams.widthRszB = rszBOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszB = rszBOutHeight;
    pIspPrm->channelParams[0U].enableOut
	[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0u;


    for(ch = 1;ch < pCapturePrm->numCh;ch++)
    {
        pOutPrm = &pCapturePrm->outParams[ch];

        pOutPrm->dataFormat = pOutPrm0->dataFormat;
        pOutPrm->width = pOutPrm0->width;
        pOutPrm->height = pOutPrm0->height;
        pOutPrm->maxWidth = pOutPrm0->maxWidth;
        pOutPrm->maxHeight = pOutPrm0->maxHeight;
        pOutPrm->numOutBuf = pOutPrm0->numOutBuf;
        pOutPrm->inCsi2DataFormat = pOutPrm0->inCsi2DataFormat;
        pOutPrm->inCsi2VirtualChanNum = ch;

        pIspPrm->channelParams[ch].outParams.widthRszA = rszAOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszA = rszAOutHeight;
        pIspPrm->channelParams[ch].outParams.widthRszB = rszBOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszB = rszBOutHeight;
	pIspPrm->channelParams[ch].enableOut
		[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0u;
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
Void chains_issMultiCaptIsp_Sgx3Dsrv_SetAppPrms(
            chains_issMultiCaptIsp_Sgx3DsrvObj *pUcObj, Void *appObj)
{
    AppCtrl_IssParams *pAppCtrlIssPrms;
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj
            = (Chains_issMultiCaptIsp_Sgx3DsrvAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;
    EpLink_CreateParams  *pEndp;


    pAppCtrlIssPrms = &pObj->appCtrlIssPrms;

    AppCtrlLink_IssParams_Init(pAppCtrlIssPrms);

    strncpy(pAppCtrlIssPrms->issSensorInfo.sensorName,
        pObj->sensorName, ISS_SENSORS_MAX_NAME);
    pAppCtrlIssPrms->issSensorInfo.numCh = pObj->numCh;
    pAppCtrlIssPrms->issSensorInfo.ispOpMode = pObj->ispOpMode;
    pAppCtrlIssPrms->issSensorInfo.simcopOpMode =
        ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;

    pAppCtrlIssPrms->issCaptLinkId = pUcObj->IssCaptureLinkID;
    pAppCtrlIssPrms->issIspLinkId = pUcObj->IssM2mIspLinkID;
    pAppCtrlIssPrms->issAewbLinkId = pUcObj->Alg_IssAewbLinkID;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_CREATE,
        &pObj->appCtrlIssPrms.issSensorInfo,
        sizeof(pObj->appCtrlIssPrms.issSensorInfo), TRUE);

    memcpy(&pAppCtrlIssPrms->issCaptLinkPrms, &pUcObj->IssCapturePrm,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issIspLinkPrms, &pUcObj->IssM2mIspPrm,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issAewbLinkPrms, &pUcObj->Alg_IssAewbPrm,
        sizeof(AlgorithmLink_IssAewbCreateParams));

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_INIT_ISS_PARAMS, pAppCtrlIssPrms,
        sizeof(AppCtrl_IssParams), TRUE);

    memcpy(&pUcObj->IssCapturePrm, &pAppCtrlIssPrms->issCaptLinkPrms,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pUcObj->IssM2mIspPrm, &pAppCtrlIssPrms->issIspLinkPrms,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pUcObj->Alg_IssAewbPrm, &pAppCtrlIssPrms->issAewbLinkPrms,
        sizeof(AlgorithmLink_IssAewbCreateParams));

    updateParamsForMultiChannel(pObj, pUcObj,
        CAPTURE_SENSOR_WIDTH, CAPTURE_SENSOR_HEIGHT,
        LIVE_WIN_WIDTH, LIVE_WIN_HEIGHT);

    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = FALSE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);
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
                                    pObj->svOutputMode,
                                    pObj->enableCarOverlayInAlg);

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
                                    pObj->svOutputMode);

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
                                    pObj->svOutputMode);

    chains_issMultiCaptIsp_Sgx3Dsrv_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->numLvdsCh
                        );

    chains_issMultiCaptIsp_Sgx3Dsrv_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

#ifndef QNX_BUILD
    if(pObj->bEglInfoInCreate == TRUE) {
        pUcObj->Sgx3DsrvPrm.bEglInfoInCreate = TRUE;
        pUcObj->Sgx3DsrvPrm.EglInfo = (void *)&chainsEglParams;
        Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv setting bEglInfoCreate = TRUE!\n");
    }
#endif

    /* We have two sink epLinks in the chain; we will configure them now */
    /* sink2 */
    pEndp = &pUcObj->EpSink_3dPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = CAL_ISS_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

    /* sink1 */
    pEndp = &pUcObj->EpSink_imPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = CAL_ISS_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

}

Void chains_issMultiCaptIsp_Sgx3Dsrv_InitApp()
{
    Bool startWithCalibration;
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj
        = (Chains_issMultiCaptIsp_Sgx3DsrvAppObj*)&gIssMultiCaptIsp_Sgx3DsrvObj;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_InitApp !!!\n");

    strncpy(pObj->sensorName, SENSOR_OMNIVISION_OV10640_IMI, ISS_SENSORS_MAX_NAME);
    /* SRV Algo related initialization */
    pObj->numLvdsCh = 4;
    pObj->numCh = 4;
    pObj->ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
    pObj->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
    pObj->enableCarOverlayInAlg = 0;
#ifndef QNX_BUILD
    pObj->bEglInfoInCreate = FALSE;
#endif
    /* Set startWithCalibration = TRUE to start the demo with calibration.
       Else it will use the previously calibrated LUTs */
    startWithCalibration = TRUE;
    ChainsCommon_SurroundView_CalibInit(
                                startWithCalibration,
                                pObj->svOutputMode);

    ChainsCommon_statCollectorReset();

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_InitApp DONE !!!\n");
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj
        = (Chains_issMultiCaptIsp_Sgx3DsrvAppObj*)&gIssMultiCaptIsp_Sgx3DsrvObj;
    chains_issMultiCaptIsp_Sgx3DsrvObj *pUcObj = &pObj->ucObj;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_CreateApp !!!\n");

    chains_issMultiCaptIsp_Sgx3Dsrv_InitApp();

#ifndef QNX_BUILD
    pObj->bEglInfoInCreate = sink->bEglInfoInCreate;
#endif

    status = chains_issMultiCaptIsp_Sgx3Dsrv_Create(&gIssMultiCaptIsp_Sgx3DsrvObj.ucObj, &gIssMultiCaptIsp_Sgx3DsrvObj);

    /* Let's set the epLink ids now */
    pUcObj = &gIssMultiCaptIsp_Sgx3DsrvObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSink_imLinkID;
    sink->eplink_id[1] = pUcObj->EpSink_3dLinkID;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_CreateApp DONE !!!\n");
    return status;
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_StartApp()
{
    Int32 status;
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj
        = (Chains_issMultiCaptIsp_Sgx3DsrvAppObj*)&gIssMultiCaptIsp_Sgx3DsrvObj;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_StartApp !!!\n");

    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    /* Sets Default ISP/SIMCOP Config from DCC */
    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_DEFAULT_CONFIG,
        &pObj->appCtrlIssPrms,
        sizeof(pObj->appCtrlIssPrms), TRUE);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_SET_BOARD_MUXES,
        &pObj->appCtrlIssPrms.issSensorInfo,
        sizeof(pObj->appCtrlIssPrms.issSensorInfo), TRUE);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_START,
        &pObj->appCtrlIssPrms.issSensorInfo,
        sizeof(pObj->appCtrlIssPrms.issSensorInfo), TRUE);

    status = chains_issMultiCaptIsp_Sgx3Dsrv_Start(&pObj->ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_StartApp DONE!!!\n");
    return status;
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_StopApp()
{
    Int32 status;
    Chains_issMultiCaptIsp_Sgx3DsrvAppObj *pObj
        = (Chains_issMultiCaptIsp_Sgx3DsrvAppObj*)&gIssMultiCaptIsp_Sgx3DsrvObj;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_StopApp !!!\n");
    status = chains_issMultiCaptIsp_Sgx3Dsrv_Stop(&pObj->ucObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_STOP_AND_DELETE,
        &pObj->appCtrlIssPrms.issSensorInfo,
        sizeof(pObj->appCtrlIssPrms.issSensorInfo), TRUE);

    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_StopApp DONE!!!\n");
    return status;
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_DeleteApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_DeleteApp !!!\n");

    status = chains_issMultiCaptIsp_Sgx3Dsrv_Delete(&gIssMultiCaptIsp_Sgx3DsrvObj.ucObj);

    ChainsCommon_SurroundView_CalibDeInit();

    Vps_printf(" CHAIN: chains_issMultiCaptIsp_Sgx3Dsrv_DeleteApp DONE!!!\n");
    return status;
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_PauseApp()
{
    Int32 status;
    chains_issMultiCaptIsp_Sgx3DsrvObj *pObj = &gIssMultiCaptIsp_Sgx3DsrvObj.ucObj;

    status = System_linkStop(pObj->IssCaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_ResumeApp()
{
    Int32 status;
    chains_issMultiCaptIsp_Sgx3DsrvObj *pObj = &gIssMultiCaptIsp_Sgx3DsrvObj.ucObj;

    status = System_linkStart(pObj->IssCaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}
