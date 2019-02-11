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
 * \file chains_lvdsVipMultiCam_Sgx3D_adaptive_srv.c
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
#include "chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>
#include <src/include/chains_common_osal.h>
#include <links_fw/src/hlos/osa/include/osa_timer.h>
#include <pthread.h>

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

/* Rear View information */
/* Change views every 3s */
#define CHANGE_VIEW_TIME (3000U)
#define BOWLCHANGE_TASK_PRI            (1U)
#define BOWLCHANGE_TASK_STACK_SIZE     (32U * 1024U)

//static UInt8 bowlChangeTaskStack[BOWLCHANGE_TASK_STACK_SIZE];

typedef struct {
    /**< Link Id's and device IDs to use for this use-case */
    chains_lvdsVipMultiCam_Sgx3D_adaptive_srvObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    Chains_Ctrl *chainsCfg;

    Sgx3DsrvLink_UpdateRenderCfgPrms renderCfgPrms;
    Chain_Common_SRV_CalibrationPrm calibrationPrm;

    Chains_CaptureSrc captureSrc;
    OSA_TimerHndl timerHndl;
    /**<Timer used to generate new data at a set interval*/

    Ptr bowlChangeCreate;
    /**< Synchronization mutex */
    OSA_ThrHndl bowlChangeTaskHndl;
    /**< DSP create task handle */

} Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj;

static struct control_srv_egl_ctx chainsEglParams = {
    .get_egl_native_display = gbm_allocator_get_native_display,
    .get_egl_native_buffer = gbm_allocator_get_native_buffer,
    .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
    .wrap_native_buffers = gbm_wrap_native_buffers,
    .wrapper_get_next_buffer = gbm_wrapper_get_next_buffer,
    .wrapper_put_buffer = gbm_wrapper_put_buffer,
    .unwrap_native_buffers = gbm_unwrap_native_buffers,
};

static char adaptiveSurroundViewCoordinatesMenu[] = {
"\n "
"\n ===================="
"\n Enter Bowl Coordinates"
"\n ===================="
"\n "
"\n L: Set left depth"
"\n R: Set right depth"
"\n B: Set back depth"
"\n F: Set front depth"
"\n D: Default bowl depth"
"\n A: Apply bowl depth"
"\n Q: Query bowl depth"
"\n 0: Exit"
"\n "
"\n Enter Choice: "
"\n "
};

static char bowlSizeMenu[] = {
"\n "
"\n ===================="
"\n Enter Bowl Size in centimeters"
"\n ===================="
"\n "
"\n Enter Value: "
"\n "
};

/**
 *******************************************************************************
 *
 * \brief   Unmount FAT File System
 *
 *******************************************************************************
*/
static Void unmountFatFs()
{
    char cmd[128U];

    sprintf(cmd, "umount /%s",MMCSD_MOUNT_PT);

    /* Unmount the SD card */
    system(cmd);
}

/**
 *******************************************************************************
 *
 * \brief   Mount the FAT File System
 *
 *******************************************************************************
*/
static Void mountFatFs()
{
    char cmd[128U];

    sprintf(cmd, "mount /dev/disk/by-path/platform-4809c000.mmc-part1 /%s",\
                                                            MMCSD_MOUNT_PT);

    /* Mount the SD card */
    system(cmd);
}

/**
 *******************************************************************************
 *
 * \brief   Allocate the buffers used in the Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/

static Void allocCalibUseCaseBufs(Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *pObj)
{
    pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf = \
        ChainsCommon_Osal_memAlloc((SRV_CALMAT_SIZE * SRV_NUM_CAMERAS),128U);
    UTILS_assert(NULL != pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf);
}

/**
 *******************************************************************************
 *
 * \brief   Free the buffers used in the Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void freeCalibUseCaseBufs(Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *pObj)
{
    if(pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf,
                        (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set SGX3D_adaptive_SRV Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetSgx3DsrvLinkPrms (
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
    prms->enableAdaptiveBowl = TRUE;
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
static Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

static Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetDisplayPosition(
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
Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetAppPrms(
            chains_lvdsVipMultiCam_Sgx3D_adaptive_srvObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth,displayHeight;
    Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *pObj
            = (Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj*)appObj;

    UInt32 svOutWidth, svOutHeight;

    pObj->vidSensorPrm.captureSrcId = pObj->captureSrc;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;

    pObj->vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                                &pObj->vidSensorPrm,
                                sizeof(VideoSensorCreateAndStartAppPrm),
                                TRUE);

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_MultiCam_SetCapturePrms(
                    &pUcObj->CapturePrm,
                    pObj->chainsCfg->numLvdsCh);

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

    /* Modify to use 2MP for input and output */
    ChainsCommon_SurroundView_SetAdaptiveBowlParams(
                                    &pUcObj->Alg_AdaptiveBowlPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    SRV_OUTPUT_WIDTH_TDA2X_3D,
                                    SRV_OUTPUT_HEIGHT_TDA2X_3D,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT);

    if (TRUE == pObj->calibrationPrm.isCalMatGenerated)
    {
        pUcObj->Alg_AdaptiveBowlPrm.calParams.calMatDDRPtr = pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf;
        pUcObj->Alg_AdaptiveBowlPrm.calParams.calMatSize = SRV_CALMAT_SIZE;
    }

    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetSyncPrm(
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

    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_SetDisplayPosition(
                    &pUcObj->Display_M4Prm,
                    520,
                    0);
    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        SGX3DSRV_OUTPUT_FRAME_WIDTH,
        SGX3DSRV_OUTPUT_FRAME_HEIGHT
        );

    /* Null Source Link used as dummy source for input Q1 of Synthesis */
    NullSrcLink_CreateParams_Init(&pUcObj->NullSourcePrm);
    pUcObj->NullSourcePrm.timerPeriodMilliSecs = 10000U;
    pUcObj->NullSourcePrm.outQueInfo.numCh = 1U;
    pUcObj->NullSourcePrm.channelParams[0].numBuffers = 2U;

    /* Setting USM device to be PGA460 */
    pUcObj->UltrasonicCapturePrm.numSensorsConnected = 4;
    pUcObj->UltrasonicCapturePrm.uartInstId = 2;
}

/* Post to bowl change semaphore */
/* Enters every 33 ms */
/*static int tracker1 = -450, tracker2 = -450;
static int view_tracker = 0;
static void bowlChangePrdFunc(union sigval arg)
{
    Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *prdObj = (Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *) arg.sival_ptr;
    AlgorithmLink_AdaptiveBowlControlParams gAlignControlParams;

    gAlignControlParams.offsetXleft = -400;
    gAlignControlParams.offsetXright = 400;
    gAlignControlParams.offsetYback = 450;
    gAlignControlParams.baseClassControl.controlCmd = ALGORITHM_LINK_CMD_CONFIG;
    gAlignControlParams.baseClassControl.size = sizeof(ALGORITHM_LINK_CMD_CONFIG);

    view_tracker++;
    if (150 == view_tracker)
    {
        tracker1 = -450;
        tracker2 = -450;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
    }
    else if ((view_tracker > 150) && (view_tracker <= 190))
    {
        tracker1 = tracker2 + 5;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
        tracker2 = tracker1;
    }
    else if ((view_tracker > 190) && (view_tracker < 210))
    {
        tracker1 = tracker2 + 6;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
        tracker2 = tracker1;
    }
    else if (210 == view_tracker)
    {
        tracker1 = -130;
        tracker2 = -130;
        gAlignControlParams.offsetYfront = tracker1;
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
    }
    else if (360 == view_tracker)
    {
        //Vps_printf("Starting bowl change--small to big\n");
    }
    else if ((view_tracker > 360) && (view_tracker <= 400))
    {
        tracker1 = tracker2 - 5;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
        tracker2 = tracker1;
    }
    else if ((view_tracker > 400) && (view_tracker < 420))
    {
        tracker1 = tracker2 - 6;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
        tracker2 = tracker1;
    }
    else if (420 == view_tracker)
    {
        view_tracker = 0;
        tracker1 = -450;
        tracker2 = -450;
        gAlignControlParams.offsetYfront = tracker1;
        //Vps_printf("tracker1 = %d\n", tracker1);
        System_linkControl(prdObj->ucObj.Alg_AdaptiveBowlLinkID,
                           ALGORITHM_LINK_CMD_CONFIG,
                           &gAlignControlParams,
                           sizeof(gAlignControlParams),
                           TRUE);
    }
}*/

/*static void createBowlChangeThread(
                        Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *chainsObj)
{
    union sigval sigevValue;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    sigevValue.sival_ptr = chainsObj;

    // Clock Create for interrupt
    status = OSA_timerCreate(&chainsObj->timerHndl, bowlChangePrdFunc, sigevValue);
    OSA_assert(status == OSA_SOK);

    // looks like there is a max period and 1000 is too large, tested up to 500
    chainsObj->timerHndl.period = 33;
    status = OSA_timerStart(&chainsObj->timerHndl);
    OSA_assert(status == OSA_SOK);
}*/

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
 * \param   pObj  [IN] Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_StartApp(Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();
    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_StopApp(Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj *pObj)
{
    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_Stop(&pObj->ucObj);

    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_Delete(&pObj->ucObj);

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
Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv(Chains_Ctrl *chainsCfg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char ch, chPrev;
    UInt32 done = FALSE;
    UInt32 bowlDone = FALSE;
    Bool startWithCalibration;
    Chains_lvdsVipMultiCam_Sgx3D_adaptive_srvAppObj chainsObj;
    /* Default values if left unchanged, all positive*/
    Int32 leftValue = 400;
    Int32 rightValue = 400;
    Int32 backValue = 450;
    Int32 frontValue = 450;
    AlgorithmLink_AdaptiveBowlControlParams gAlignControlParams;

    chainsObj.chainsCfg = chainsCfg;
    chPrev = '1';

    chainsObj.chainsCfg->numLvdsCh = 4;

    mountFatFs();

    do
    {
        done = FALSE;

        allocCalibUseCaseBufs(&chainsObj);
        chainsObj.calibrationPrm.calMatGenPrm3DSrv.displayWidth = \
                                    SRV_OUTPUT_WIDTH_TDA2X_2D;
        chainsObj.calibrationPrm.calMatGenPrm3DSrv.displayHeight = \
                                    SRV_OUTPUT_HEIGHT_TDA2X_2D;
        Chain_Common_SRV_generateCalMat(&chainsObj.calibrationPrm, \
                                                SRV_CALIB_TYPE_MANUAL);
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_Create(&chainsObj.ucObj, &chainsObj);

        chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_StartApp(&chainsObj);

        ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

        /* Creating thread for changing bowl shape */
        // Turning off bowl change, uncomment to change bowl dynamically
        /*if (OSA_SOK == status)
        {
            createBowlChangeThread(&chainsObj);
        }*/

        while(!done)
        {
            ch = Chains_menu3DSrvRunTime();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case '4':
                    bowlDone = FALSE;
                    while(!bowlDone)
                    {
                        Vps_printf(adaptiveSurroundViewCoordinatesMenu);
                        ch = Chains_readChar();

                        switch(ch)
                        {
                            case 'l':
                            case 'L':
                                Vps_printf("Selected Left\n");
                                Vps_printf(bowlSizeMenu);
                                leftValue = Chains_readInt();
                                Vps_printf("Value = %d\n", leftValue);
                                break;
                            case 'r':
                            case 'R':
                                Vps_printf("Selected Right\n");
                                Vps_printf(bowlSizeMenu);
                                rightValue = Chains_readInt();
                                Vps_printf("Value = %d\n", rightValue);

                                break;
                            case 'f':
                            case 'F':
                                Vps_printf("Selected Front\n");
                                Vps_printf(bowlSizeMenu);
                                frontValue = Chains_readInt();
                                Vps_printf("Value = %d\n", frontValue);
                                break;
                            case 'b':
                            case 'B':
                                Vps_printf("Selected Back\n");
                                Vps_printf(bowlSizeMenu);
                                backValue = Chains_readInt();
                                Vps_printf("Value = %d\n", backValue);
                                break;
                            case 'd':
                            case 'D':
                                Vps_printf("Setting default bowl depth\n");
                                gAlignControlParams.offsetXleft = -400;
                                gAlignControlParams.offsetXright = 400;
                                gAlignControlParams.offsetYback = 450;
                                gAlignControlParams.offsetYfront = -450;
                                gAlignControlParams.baseClassControl.controlCmd = ALGORITHM_LINK_CMD_CONFIG;
                                gAlignControlParams.baseClassControl.size = sizeof(ALGORITHM_LINK_CMD_CONFIG);
                                System_linkControl(chainsObj.ucObj.Alg_AdaptiveBowlLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &gAlignControlParams,
                                sizeof(gAlignControlParams),
                                TRUE);
                                Vps_printf("Default bowl set\n");
                                break;
                            case 'a':
                            case 'A':
                                Vps_printf("Applying bowl depth\n");
                                gAlignControlParams.offsetXleft = -1*leftValue;
                                gAlignControlParams.offsetXright = rightValue;
                                gAlignControlParams.offsetYback = backValue;
                                gAlignControlParams.offsetYfront = -1*frontValue;
                                gAlignControlParams.baseClassControl.controlCmd = ALGORITHM_LINK_CMD_CONFIG;
                                gAlignControlParams.baseClassControl.size = sizeof(ALGORITHM_LINK_CMD_CONFIG);
                                System_linkControl(chainsObj.ucObj.Alg_AdaptiveBowlLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &gAlignControlParams,
                                sizeof(gAlignControlParams),
                                TRUE);
                                Vps_printf("New bowl set\n");
                                break;
                            case 'q':
                            case 'Q':
                                Vps_printf("Left offset absolute value = %d\n", leftValue);
                                Vps_printf("Right offset absolute value = %d\n", rightValue);
                                Vps_printf("Back offset absolute value = %d\n", backValue);
                                Vps_printf("Front offset absolute value = %d\n", frontValue);
                                break;
                            case '0':
                                bowlDone = TRUE;
                                break;
                            default:
                                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                                break;
                        }
                    }
                    break;
                case 's':
                case 'S':
                    status = OSA_timerStart(&chainsObj.timerHndl);
                    OSA_assert(status == OSA_SOK);
                    break;
                case 'o':
                case 'O':
                    status = OSA_timerStop(&chainsObj.timerHndl);
                    OSA_assert(status == OSA_SOK);
                    break;
                case 'a':
                case 'A':
                case 'b':
                case 'B':
                case 'c':
                case 'C':
                case 'd':
                case 'D':
                case 'g':
                case 'G':
                case 'i':
                case 'I':
                case 'j':
                case 'J':
                case 'k':
                case 'K':
                case 'l':
                case 'L':
                case 'm':
                case 'M':
                case 'n':
                case 'N':
                case 'q':
                case 'Q':
                case 't':
                case 'T':
                case 'v':
                case 'V':
                case 'w':
                case 'W':
                case 'x':
                case 'X':
                case 'y':
                case 'Y':
                case 'z':
                case 'Z':
                case '<':
                case '>':
                case '1':
                case '2':
                case '3':
                    chainsObj.renderCfgPrms.inputChar = ch;
                    System_linkControl(
                        SYSTEM_LINK_ID_SGX3DSRV_0,
                        SYSTEM_COMMON_CMD_UPDATE_RENDER_VIEW,
                        &chainsObj.renderCfgPrms,
                        sizeof(Sgx3DsrvLink_UpdateRenderCfgPrms),
                        TRUE);
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_printStatistics(&chainsObj.ucObj);
                    chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_printBufferStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_lvdsVipMultiCam_Sgx3D_adaptive_srv_StopApp(&chainsObj);

        ChainsCommon_SurroundView_CalibDeInit();
        freeCalibUseCaseBufs(&chainsObj);

    } while(chPrev != '3');

    status = OSA_timerDelete(&chainsObj.timerHndl);
    OSA_assert(status == OSA_SOK);
    unmountFatFs();
}


