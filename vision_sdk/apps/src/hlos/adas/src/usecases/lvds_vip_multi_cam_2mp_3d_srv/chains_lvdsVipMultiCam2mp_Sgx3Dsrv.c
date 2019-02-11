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
 * \file chains_lvdsVipMultiCam2mp_Sgx3Dsrv.c
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
#include "chains_lvdsVipMultiCam2mp_Sgx3Dsrv_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>

#define CAPTURE_SENSOR_WIDTH                 (1920)
#define CAPTURE_SENSOR_HEIGHT                (1080)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH          (1920)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT         (1080)
#define SRV_LVDS_CAPTURE_WIDTH_2MP           (1920U)
#define SRV_LVDS_CAPTURE_HEIGHT_2MP          (1080U)
#define CAPTURE_SENSOR_CROPSTARTX            (20)
#define CAPTURE_SENSOR_CROPSTARTY            (11)


/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC                   (50)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC          (100)

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
    chains_lvdsVipMultiCam2mp_Sgx3DsrvObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;
    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    Chains_Ctrl *chainsCfg;

    Sgx3DsrvLink_UpdateRenderCfgPrms renderCfgPrms;

} Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj;

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
static Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetSgx3DsrvLinkPrms (
                                  Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = CAPTURE_SENSOR_HEIGHT;
    prms->maxInputWidth = CAPTURE_SENSOR_WIDTH;
    prms->numViews = 1;
    prms->bAnimate = 1;
    prms->numInQue = SGX3DSRV_LINK_IPQID_MAXIPQ;
    prms->inputRes = SGX3DSRV_LINK_INPUTRES_2MP;
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
static Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

static Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetDisplayPosition(
                    DisplayLink_CreateParams *pPrm_Video,
                    UInt32 posX,
                    UInt32 posY
                    )
{
    pPrm_Video->rtParams.posX = posX;
    pPrm_Video->rtParams.posY = posY;
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
Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetAppPrms(
            chains_lvdsVipMultiCam2mp_Sgx3DsrvObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth,displayHeight;
    Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj *pObj
            = (Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj*)appObj;

    UInt32 svOutWidth, svOutHeight;

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_IMX290ISP;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = 4;

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
        UInt32 i, streamId;
        CaptureLink_VipInstParams *pInstPrm;
        for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pInstPrm = &pUcObj->CapturePrm.vipInst[i];
            pInstPrm->inParams.width      =   CAPTURE_SENSOR_WIDTH;
            pInstPrm->inParams.height     =   CAPTURE_SENSOR_HEIGHT;
            for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                    streamId++)
            {
                pInstPrm->outParams[streamId].width     =   CAPTURE_SENSOR_WIDTH;
                pInstPrm->outParams[streamId].height    =   CAPTURE_SENSOR_HEIGHT;
                pInstPrm->outParams[streamId].maxWidth  =   CAPTURE_SENSOR_WIDTH;
                pInstPrm->outParams[streamId].maxHeight =   CAPTURE_SENSOR_HEIGHT;
            }
            pInstPrm->scPrms.inCropCfg.cropWidth      =   CAPTURE_SENSOR_WIDTH;
            pInstPrm->scPrms.inCropCfg.cropHeight     =   CAPTURE_SENSOR_HEIGHT;
            pInstPrm->vipPortCfg.comCfg.expectedNumLines     =   CAPTURE_SENSOR_WIDTH;
            pInstPrm->vipPortCfg.comCfg.expectedNumPix       =   CAPTURE_SENSOR_HEIGHT;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropWidth      =   CAPTURE_SENSOR_WIDTH;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropHeight     =   CAPTURE_SENSOR_HEIGHT;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartX     =   CAPTURE_SENSOR_CROPSTARTX;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartY     =   CAPTURE_SENSOR_CROPSTARTY;

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
                                    SRV_LVDS_CAPTURE_WIDTH_2MP,
                                    SRV_LVDS_CAPTURE_HEIGHT_2MP,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode,
                                    pObj->chainsCfg->enableCarOverlayInAlg);

    pUcObj->Alg_SynthesisPrm.outputRes = ALGLINK_SYNTHESIS_OUTPUTRES_2MP;

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlign3DParams(
                                    &pUcObj->Alg_GeoAlign3DPrm,
                                    SRV_LVDS_CAPTURE_WIDTH_2MP,
                                    SRV_LVDS_CAPTURE_HEIGHT_2MP,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    pUcObj->Alg_GeoAlign3DPrm.inputRes = ALGLINK_GALIGN3D_INPUTRES_2MP;
    pUcObj->Alg_GeoAlign3DPrm.outputRes = ALGLINK_GALIGN3D_OUTPUTRES_2MP;

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH_2MP,
                                    SRV_LVDS_CAPTURE_HEIGHT_2MP,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Graphics Source */
    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                displayWidth,
                                displayHeight
                                );

    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->chainsCfg->numLvdsCh
                        );

    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewStandaloneLayout2Enable = TRUE;
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

    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_SetDisplayPosition(
                    &pUcObj->Display_M4Prm,
                    0,
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
 * \param   pObj  [IN] Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_StartApp(Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();
    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam2mp_Sgx3Dsrv_StopApp(Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj *pObj)
{
     chains_lvdsVipMultiCam2mp_Sgx3Dsrv_Stop(&pObj->ucObj);

     chains_lvdsVipMultiCam2mp_Sgx3Dsrv_Delete(&pObj->ucObj);

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
Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_lvdsVipMultiCam2mp_Sgx3DsrvAppObj chainsObj;

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

        chains_lvdsVipMultiCam2mp_Sgx3Dsrv_Create(&chainsObj.ucObj, &chainsObj);

        chains_lvdsVipMultiCam2mp_Sgx3Dsrv_StartApp(&chainsObj);

        ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

        while(!done)
        {
            ch = Chains_menu3DSrvRunTime();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_printStatistics(&chainsObj.ucObj);
                    chains_lvdsVipMultiCam2mp_Sgx3Dsrv_printBufferStatistics(&chainsObj.ucObj);
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
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_lvdsVipMultiCam2mp_Sgx3Dsrv_StopApp(&chainsObj);

        ChainsCommon_SurroundView_CalibDeInit();

    } while(chPrev != '3');
}


