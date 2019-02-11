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
 * \file chains_lvdsVipMultiCam_sfm4ch.c
 *
 *
 * \version 0.0 (Dec 2015) : [MM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_lvdsVipMultiCam_3d_perception_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>
#include <src/include/chains_lens.h>


//SHARED PARAMETERS
#define SFM_NUM_CAMS            (4) //cannot be changed freely!
#define MAX_NUM_POINTS_PER_CAM  (900)

//CAMERA/CAPTURE
#define CAPTURE_SENSOR_WIDTH    (1280)
#define CAPTURE_SENSOR_HEIGHT   (720)

//SPARSE OPTICAL FLOW
#define SOF_NUM_OUT_BUF         (16)
#define SOF_ALG_WIDTH           (CAPTURE_SENSOR_WIDTH)
#define SOF_ALG_HEIGHT          (CAPTURE_SENSOR_HEIGHT)

//DISPLAY
#define DISPLAY_WIDTH   (1920)
#define DISPLAY_HEIGHT  (1080)

//Sync
#define SYNC_TIGHT_DELTA_IN_MSEC            (16)
#define SYNC_TIGHT_DROP_THRESHOLD_IN_MSEC   (33)
#define SYNC_LOOSE_DELTA_IN_MSEC            (0x7FFFFFFF)
#define SYNC_LOOSE_DROP_THRESHOLD_IN_MSEC   (0x7FFFFFFF)

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
    chains_lvdsVipMultiCam_3d_perceptionObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    UInt32  appCtrlLinkId;

    Chains_Ctrl *chainsCfg;

    Chains_CaptureSrc captureSrc;

} Chains_lvdsVipMultiCam_3dPerceptionAppObj;

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
static Void chains_lvdsVipMultiCam_3d_perception_SetSgx3DsfmLinkPrms (
                                  Sgx3DsfmLink_CreateParams *prms)
{
    prms->inFramesHeight = CAPTURE_SENSOR_HEIGHT;
    prms->inFramesWidth = CAPTURE_SENSOR_WIDTH;
    prms->numCams = SFM_NUM_CAMS;

    prms->numInQue = SGX3DSFM_LINK_IPQID_MAXIPQ;
    prms->inBufType[SGX3DSFM_LINK_IPQID_MULTIVIEW] = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->inBufType[SGX3DSFM_LINK_IPQID_EGOPOSE]   = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[SGX3DSFM_LINK_IPQID_BOXES]     = SYSTEM_BUFFER_TYPE_METADATA;

    prms->bEglInfoInCreate = TRUE;
    prms->EglInfo = (void *)&chainsEglParams;

    prms->scale =1.0f; /*toy setup*/
}

/**
 *******************************************************************************
 *
 * \brief   Set Algorithm related parameters
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_3d_perception_SetSparseOpticalFlowPrm(
                    AlgorithmLink_SparseOpticalFlowCreateParams *pAlgPrm,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 syncChannel
                    )
{
    UInt8 i;

    pAlgPrm->numOutBuffers = SOF_NUM_OUT_BUF;
    pAlgPrm->enableRoi = FALSE;

    pAlgPrm->imgFrameStartX = startX;
    pAlgPrm->imgFrameStartY = startY;
    pAlgPrm->imgFrameWidth  = width;
    pAlgPrm->imgFrameHeight  = height;

    pAlgPrm->trackErrThr = 500;
    pAlgPrm->trackMinFlowQ4 = 0;
    pAlgPrm->trackNmsWinSize = 5;

    pAlgPrm->numLevels = 5;

    pAlgPrm->keyPointDetectInterval = 10;
    pAlgPrm->keyPointDetectMethod = 1;

    pAlgPrm->maxNumKeyPoints = MAX_NUM_POINTS_PER_CAM;
    pAlgPrm->maxPrevTrackPoints = MAX_NUM_POINTS_PER_CAM;

    pAlgPrm->fast9Threshold = 100;
    pAlgPrm->scoreMethod = 0;
    pAlgPrm->harrisScaling = 1310;
    pAlgPrm->nmsThreshold = 420000000;
    pAlgPrm->harrisScoreMethod = 0;
    pAlgPrm->harrisWindowSize = 0;
    pAlgPrm->suppressionMethod = 2;

    pAlgPrm->trackOffsetMethod = 0;

    pAlgPrm->maxItersLK[0]  = 20;
    pAlgPrm->maxItersLK[1]  = 20;
    pAlgPrm->maxItersLK[2]  = 10;
    pAlgPrm->maxItersLK[3]  = 10;
    pAlgPrm->maxItersLK[4]  = 10;
    pAlgPrm->maxItersLK[5]  = 10;
    pAlgPrm->maxItersLK[6]  = 10;
    pAlgPrm->maxItersLK[7]  = 10;

    for(i=0; i<PYRAMID_LK_TRACKER_TI_MAXLEVELS;i++)
    {
         pAlgPrm->minErrValue[i] = 64;
         pAlgPrm->searchRange[i] = 12;
    }

    pAlgPrm->compositeBufferInput = syncChannel;

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
Void chains_lvdsVipMultiCam_3d_perception_SetAppPrms(
            chains_lvdsVipMultiCam_3d_perceptionObj *pUcObj, Void *appObj)
{

    UInt32 displayWidth,displayHeight;

    Chains_lvdsVipMultiCam_3dPerceptionAppObj *pObj
            = (Chains_lvdsVipMultiCam_3dPerceptionAppObj*)appObj;
    ChainsCommon_SurroundView_GACalibrationInfo *pCalibPrm;

    pObj->vidSensorPrm.captureSrcId = pObj->captureSrc;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                                &pObj->vidSensorPrm,
                                sizeof(VideoSensorCreateAndStartAppPrm),
                                TRUE);

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
        }
    }

    /*Graphics*/
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height   = DISPLAY_HEIGHT;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width    = DISPLAY_WIDTH;

    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewDOFLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewPdTsrLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewLdLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.sfmLayoutEnable  = TRUE;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.enableJeepOverlay = FALSE;


    /*Sync before SOF*/
    pUcObj->Sync_1Prm.syncDelta = SYNC_TIGHT_DELTA_IN_MSEC;
    pUcObj->Sync_1Prm.syncThreshold = SYNC_TIGHT_DROP_THRESHOLD_IN_MSEC;

    /*Sync after SOF*/
    pUcObj->Sync_2Prm.syncDelta = SYNC_LOOSE_DELTA_IN_MSEC;
    pUcObj->Sync_2Prm.syncThreshold = SYNC_LOOSE_DROP_THRESHOLD_IN_MSEC;

    /*SGX link*/
    chains_lvdsVipMultiCam_3d_perception_SetSgx3DsfmLinkPrms(&pUcObj->Sgx3DsfmPrm);

    /*****************************
     * ALGORITHMS
     ****************************/
    //SOF 0
    chains_lvdsVipMultiCam_3d_perception_SetSparseOpticalFlowPrm(
        &pUcObj->Alg_SparseOpticalFlow_0Prm, 0, 0, SOF_ALG_WIDTH, SOF_ALG_HEIGHT, 0);

    //SOF 1
    chains_lvdsVipMultiCam_3d_perception_SetSparseOpticalFlowPrm(
        &pUcObj->Alg_SparseOpticalFlow_1Prm, 0, 0, SOF_ALG_WIDTH, SOF_ALG_HEIGHT, 1);

    //SOF 2
    chains_lvdsVipMultiCam_3d_perception_SetSparseOpticalFlowPrm(
        &pUcObj->Alg_SparseOpticalFlow_2Prm, 0, 0, SOF_ALG_WIDTH, SOF_ALG_HEIGHT, 2);

    //SOF 3
    chains_lvdsVipMultiCam_3d_perception_SetSparseOpticalFlowPrm(
        &pUcObj->Alg_SparseOpticalFlow_3Prm, 0, 0, SOF_ALG_WIDTH, SOF_ALG_HEIGHT, 3);


    //SFM
    ChainsCommon_StructureFromMotion_SetParams(
            &pUcObj->Alg_SfmMainPrm.algCreateParams,
            &pUcObj->Alg_SfmLinearTwoViewPrm.algCreateParams,
            &pUcObj->Alg_SfmMapPrm.algCreateParams,
            SFM_NUM_CAMS,
            MAX_NUM_POINTS_PER_CAM);

    //Sfm Calibration from File/QSPI
    pCalibPrm = ChainsCommon_SurroundView_getCalibPrm();
    pUcObj->Alg_SfmMainPrm.calmatAddr = (Int32 *)pCalibPrm->autoPersMatDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES/4 ;

    pUcObj->Alg_SfmMainPrm.pLensPrm = (Void*)Chains_lens_getLensPrm();

        ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &displayWidth,
        &displayHeight
        );

    pUcObj->Display_GrpxPrm.rtParams.tarWidth       = displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight      = displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
    pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                DISPLAY_WIDTH,
                                DISPLAY_HEIGHT
                               );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT
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
 * \param   pObj  [IN] Chains_lvdsVipMultiCam_3dPerceptionAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_3d_perception_StartApp(Chains_lvdsVipMultiCam_3dPerceptionAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();
    chains_lvdsVipMultiCam_3d_perception_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_lvdsVipMultiCam_3dPerceptionAppObj
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_3d_perception_StopApp(Chains_lvdsVipMultiCam_3dPerceptionAppObj *pObj)
{

    chains_lvdsVipMultiCam_3d_perception_Stop(&pObj->ucObj);

    chains_lvdsVipMultiCam_3d_perception_Delete(&pObj->ucObj);

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
 * \brief   Unmount FAT File System
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
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
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
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
Void chains_lvdsVipMultiCam_3d_perception(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_lvdsVipMultiCam_3dPerceptionAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.chainsCfg->numLvdsCh = 4;

    done = FALSE;

	/* 	Mount sd card fatfs
		The lesn parameters are read from the SD card */
	mountFatFs();

    ChainsCommon_SurroundView_CalibInit(
                                TRUE,
                                chainsObj.chainsCfg->svOutputMode);

    chainsObj.captureSrc = chainsCfg->captureSrc;

    chains_lvdsVipMultiCam_3d_perception_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipMultiCam_3d_perception_StartApp(&chainsObj);

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
                chains_lvdsVipMultiCam_3d_perception_printStatistics(&chainsObj.ucObj);
                chains_lvdsVipMultiCam_3d_perception_printBufferStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVipMultiCam_3d_perception_StopApp(&chainsObj);

    ChainsCommon_SurroundView_CalibDeInit();

	unmountFatFs();
}


