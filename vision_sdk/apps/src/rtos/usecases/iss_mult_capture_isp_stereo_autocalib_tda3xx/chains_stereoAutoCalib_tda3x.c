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
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>
#include <src/include/chains_common_dewarp.h>
#include "chains_stereoAutoCalib_tda3x_priv.h"

/**
 ****************************************************f***************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (16)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (33)


#define ISP_OUTPUT_NUM_BUFFERS                  (4U)


#define REMAP_WIDTH                             (736U)
#define REMAP_HEIGHT                            (384U)

#define STEREO_OUTPUT_WIDTH                     (640U)
#define STEREO_OUTPUT_HEIGHT                    (360U)

#define LIVE_CAMERA_DISPLAY_WIDTH               (960U)
#define LIVE_CAMERA_DISPLAY_HEIGHT              (540U)

/* Capture Resolution of AR0140 sensor */
#define STEREO_CAPT_SENSOR_AR140_WIDTH          (1280U)
#define STEREO_CAPT_SENSOR_AR140_HEIGHT         (800U)

/* Capture Resolution of OV10640 sensor */
#define STEREO_CAPT_SENSOR_OV10640_WIDTH        (1280U)
#define STEREO_CAPT_SENSOR_OV10640_HEIGHT       (720U)

#define CROP_CAPTURE_SENSOR_WIDTH               (1280U)
#define CROP_CAPTURE_SENSOR_HEIGHT              (720U)

#define ORG_VIDEO_DISPLAY_START_X               (0U)
#define ORG_VIDEO_DISPLAY_START_Y               (270U)


#define USE_RANSAC                              (0)
#define NUM_RANSAC_ITERS                        (2000U)
#define NUM_RANSAC_DATA                         (5U)

#define ROI_REGION_AROUND_CENTER                (0.5)//(0.375)

#define FISH_EYE_RECT                           (0)



/**
 *******************************************************************************
 *
 *  \brief  chains_issMultCaptIspCalib3DSv_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_stereoAutoCalib_tda3xObj ucObj;
    AppUtils_Obj                    appObjPrms;

    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;
    IssM2mSimcopLink_ConfigParams simcopConfig;

    UInt32  numCh;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;


    Chains_Ctrl *chainsCfg;


    /*
    Bool isCalMatGenerated;
    UInt32 yuvDumpCount;
    UInt32 imgSize;
    Int8 *inChartPosBuf;
    Utils_DmaChObj dumpFramesDmaObj;
    */

} chains_issMultCaptIpsStereoAutoCalibAppObj;


/**
 *******************************************************************************
 *
 * \brief   Do the ISP Set Config
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIspSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void setIspConfig(chains_issMultCaptIpsStereoAutoCalibAppObj *pObj)
{
    /* ISP Config */
    appSetDefaultIspParams(&pObj->appObjPrms);
    appSetIspParamsFromDCC(&pObj->appObjPrms);

    /* Initialize Simcop Configuration */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Simcop/Dewarp Config */
    IssUtils_InitSimcopConfig(
            &pObj->simcopConfig,
            TRUE,
            TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE Link Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_stereoAutoCalib_tda3x_SetIssRszPrms(
        IssRszLink_CreateParams *pCapturePrm,
        IssRszLink_CreateParams *pOrgPrm,
        UInt32 captureSensorWidth,
        UInt32 captureSensorHeight,
        UInt32 cropCaptureSensorWidth,
        UInt32 cropCaptureSensorHeight)
{
    UInt16 chId;
    IssRszLink_ChannelParams *chPrms;

    if(pCapturePrm)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &pCapturePrm->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = cropCaptureSensorWidth;
            chPrms->outParams.heightRszA  = cropCaptureSensorHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = \
                                    (captureSensorWidth - cropCaptureSensorWidth) >> 1;
            chPrms->inCropCfg.cropStartY = \
                                    (captureSensorHeight - cropCaptureSensorHeight) >> 1;
            chPrms->inCropCfg.cropWidth = cropCaptureSensorWidth;
            chPrms->inCropCfg.cropHeight = cropCaptureSensorHeight;
        }
    }

    if(pOrgPrm)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &pOrgPrm->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = LIVE_CAMERA_DISPLAY_WIDTH;
            chPrms->outParams.heightRszA  = LIVE_CAMERA_DISPLAY_HEIGHT;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = 0;
            chPrms->inCropCfg.cropStartY = 0;
            chPrms->inCropCfg.cropWidth = cropCaptureSensorWidth;
            chPrms->inCropCfg.cropHeight = cropCaptureSensorHeight;
        }
    }


}

/**
 *******************************************************************************
 *
 * \brief   Set the Sync Link Paremeters
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
 */
Void chains_stereoAutoCalib_tda3x_SetSyncPrm(SyncLink_CreateParams *pOrgPrm,  SyncLink_CreateParams *pArPrm)
{
    // increase sync params before displaying captured frames
    // otherwise captured frames are not displayed
    pOrgPrm->syncDelta = SYNC_DELTA_IN_MSEC * 10;
    pOrgPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC *10;

    pArPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pArPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

/**
 *******************************************************************************
 *
 * \brief   Set Grpx Src Create Parameters
 *
 *          It is called in Create function.
 *
 *******************************************************************************
*/

Void chains_stereoAutoCalib_tda3x_SetGrpxSrcPrms(
        GrpxSrcLink_CreateParams *pPrm,
        UInt32 displayWidth,
        UInt32 displayHeight)
{
    if(pPrm)
    {
        pPrm->grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
        pPrm->grpxBufInfo.height   = displayHeight;
        pPrm->grpxBufInfo.width    = displayWidth;

        pPrm->statsDisplayEnable = TRUE;
        pPrm->stereoCalibDisplayPrms.stereoCalibLayout = TRUE;

        pPrm->stereoCalibDisplayPrms.stereoCalibCaptureWidth = CROP_CAPTURE_SENSOR_WIDTH;
        pPrm->stereoCalibDisplayPrms.stereoCalibCaptureHeight = CROP_CAPTURE_SENSOR_HEIGHT;
        pPrm->stereoCalibDisplayPrms.stereoCalibDisplayWidth = LIVE_CAMERA_DISPLAY_WIDTH;
        pPrm->stereoCalibDisplayPrms.stereoCalibDisplayHeight = LIVE_CAMERA_DISPLAY_HEIGHT;
        pPrm->stereoCalibDisplayPrms.stereoCalibDisplayStartX = ORG_VIDEO_DISPLAY_START_X;
        pPrm->stereoCalibDisplayPrms.stereoCalibDisplayStartY = ORG_VIDEO_DISPLAY_START_Y;
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_issMultCaptIspSimcop_Stereo_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_stereoAutoCalib_tda3x_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Org,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    Chains_DisplayType displayType,
                                    UInt32 orgWinStartX,
                                    UInt32 orgWinStartY,
                                    UInt32 orgWinWidth,
                                    UInt32 orgWinHeight)
{

    if(pPrm_Org)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Org->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Org->rtParams.tarWidth  = orgWinWidth * 2;
        pPrm_Org->rtParams.tarHeight = orgWinHeight;
        pPrm_Org->rtParams.posX      = orgWinStartX;
        pPrm_Org->rtParams.posY      = orgWinStartY;

        pPrm_Org->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }


    if(pPrm_Grpx)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
           (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set the pin mux for the TDA3X EVM
 *
 *******************************************************************************
*/
static setMuxes(chains_issMultCaptIpsStereoAutoCalibAppObj *pObj)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    /* Mux is configured only on TDA3X EVM */
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_issMultCaptIpsStereoAutoCalibAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight,
            UInt32 rszBOutWidth,
            UInt32 rszBOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucObj.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucObj.IssM2mIspPrm;

    pCapturePrm->numCh = pObj->numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;
    pIspPrm->channelParams[0U].outParams.widthRszB = rszBOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszB = rszBOutHeight;

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
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set stereo Rectification Use case Link Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_stereoAutoCalib_tda3x_SetAppPrms(
        chains_stereoAutoCalib_tda3xObj *pUcObj, Void *appObj)
{
    chains_issMultCaptIpsStereoAutoCalibAppObj *pObj
        = (chains_issMultCaptIpsStereoAutoCalibAppObj *)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;

    UInt32 numCh;

    pObj->captureOutWidth  = STEREO_CAPT_SENSOR_OV10640_WIDTH;
    pObj->captureOutHeight = STEREO_CAPT_SENSOR_OV10640_HEIGHT;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pObj->captureOutWidth  = STEREO_CAPT_SENSOR_AR140_WIDTH;
        pObj->captureOutHeight = STEREO_CAPT_SENSOR_AR140_HEIGHT;
    }

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ispOpMode = pObj->chainsCfg->ispOpMode;

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = pObj->numCh;
    pObj->appObjPrms.ispOpMode = ispOpMode;
    pObj->appObjPrms.simcopOpMode = ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;
    pObj->appObjPrms.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appObjPrms);

    appInitIssCaptParams(&pObj->appObjPrms, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appObjPrms, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appObjPrms, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    /*  Override the capture and ISP parameters for multi channel */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight,
                LIVE_CAMERA_DISPLAY_WIDTH,
                LIVE_CAMERA_DISPLAY_HEIGHT);

    /* Enable frame dump in M2M ISP link */
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    /* AEWB parameters */
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;


    // Set additional link params
    chains_stereoAutoCalib_tda3x_SetGrpxSrcPrms(
            &pUcObj->GrpxSrcPrm,
            pObj->displayWidth,
            pObj->displayHeight);

    chains_stereoAutoCalib_tda3x_SetSyncPrm(&pUcObj->Sync_orgPrm, &pUcObj->Sync_arPrm);

    chains_stereoAutoCalib_tda3x_SetIssRszPrms(
            &pUcObj->IssM2mResizer_CapturePrm,
            NULL,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT
            );

    ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMsPrm,
            2,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0);

    chains_stereoAutoCalib_tda3x_SetDisplayPrms(
            &pUcObj->Display_orgPrm,
            &pUcObj->Display_GrpxPrm,
            pObj->chainsCfg->displayType,
            ORG_VIDEO_DISPLAY_START_X,
            ORG_VIDEO_DISPLAY_START_Y,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT);

    ChainsCommon_Single_Stereo_AutoRemapAlgPrms(
            &pUcObj->Alg_AutoRemapPrm,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT,
            REMAP_WIDTH,
            REMAP_HEIGHT,
            USE_RANSAC,
            NUM_RANSAC_ITERS,
            NUM_RANSAC_DATA,
            ROI_REGION_AROUND_CENTER,
            FISH_EYE_RECT,
            0);


    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    for (numCh = 0U; numCh < pUcObj->IssCapturePrm.numCh; numCh ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
            ISP_OUTPUT_NUM_BUFFERS;
    }
}


Void stereoAutoCalib_tda3x_save_ldc_lut(AlgorithmLink_AutoRemapCreateParams* pPrm_AutoRemap)
{

    Int32 fp;

    fp = File_open(STEREO_FILENAME_LUT, "wb");
    UTILS_assert(0 <= fp);

    Vps_printf("STEREO_AUTO_CALIB: Writing remap table to the file %s ...\n", STEREO_FILENAME_LUT);

    Int32 lineOffset, ldcLutSize, sizeToRead;
    Int32 scaleShift = 3;


    lineOffset = (pPrm_AutoRemap->lutWidth / (1 << scaleShift)) + 1;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((pPrm_AutoRemap->lutHeight / (1 << scaleShift)) + 1);
    ldcLutSize = ((ldcLutSize + 128 - 1) / 128) * 128;

    sizeToRead = ldcLutSize * 2;

    ChainsCommon_DeWarp_fileWrite(
            fp,
            (UInt8*) pPrm_AutoRemap->calibLUTBufPrms.pCalibLUTBuf + pPrm_AutoRemap->calibLUTBufPrms.calibLUTHeaderSize,
            sizeToRead);

    File_close(fp);
}



/**
 *******************************************************************************
 *
 * \brief   Start the stereo Rectification Use case
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIpsStereoAutoCalibAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_stereoAutoCalib_tda3x_StartApp(
        chains_issMultCaptIpsStereoAutoCalibAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    setIspConfig(pObj);
    setMuxes(pObj);
    appStartIssSensorSerDes(&pObj->appObjPrms);
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_stereoAutoCalib_tda3x_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete the stereo rectification Use case
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIpsStereoAutoCalibAppObj
 *
 *******************************************************************************
*/
static Void chains_stereoAutoCalib_tda3x_StopAndDeleteApp(
        chains_issMultCaptIpsStereoAutoCalibAppObj *pObj)
{
    chains_stereoAutoCalib_tda3x_Stop(&pObj->ucObj);
    chains_stereoAutoCalib_tda3x_Delete(&pObj->ucObj);

    ChainsCommon_Stereo_AutoRemap_Delete(&pObj->ucObj.Alg_AutoRemapPrm);

    ChainsCommon_StopDisplayCtrl();

    appStopISSSensor(&pObj->appObjPrms);
    appDeleteISSSensor(&pObj->appObjPrms);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}




/**
 *******************************************************************************
 *
 * \brief   Stereo auto calibration (rectification) entry function
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void Chains_issMultCaptSteroAutoCalib(Chains_Ctrl *chainsCfg)
{
    Int32 retVal;
    char ch;
    UInt32 done = FALSE;
    chains_issMultCaptIpsStereoAutoCalibAppObj chainsObj;

    Int16 * featureHeader;

    if ((ISSM2MISP_LINK_OPMODE_1PASS_WDR != chainsCfg->ispOpMode) &&
        (ISSM2MISP_LINK_OPMODE_12BIT_LINEAR != chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: WDR should either be disabled or "
                    "in One Pass mode!!!\n");
        return;
    }

    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
    chainsObj.chainsCfg = chainsCfg;
    chainsObj.numCh = 2U;

    /*
     *  The SV files are present in the TDA3X_3DSV folder
     */
    retVal = File_chDir(STEREO_DIR_NAME);
    if (SYSTEM_LINK_STATUS_SOK != retVal)
    {
        Vps_printf(" CHAINS: %s Folder not present in MMC/SD \n", STEREO_DIR_NAME);
        Vps_printf(" CHAINS: Requires LDC LUTs in %s folder \n", STEREO_DIR_NAME);
        return;
    }

    chains_stereoAutoCalib_tda3x_Create(
            &chainsObj.ucObj,
            &chainsObj);

    chains_stereoAutoCalib_tda3x_StartApp(&chainsObj);


    // feature point buffer
    featureHeader = (Int16 *) chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.pFeatureBuf;

    // set fps
//    ChainsCommon_SetIssSensorFps(FVID2_FPS_15);


    while(!done)
    {
        ch = ChainsCommon_Stereo_AutoRemap_Menu();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':

                // feature point detection is not done yet
                featureHeader[0] = 1;

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_FEATURE_COLLECT_NEW,
                        NULL,
                        0,
                        TRUE);

                break;
            case '2':

                // feature point detection is not done yet
                featureHeader[0] = 2;

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_FEATURE_COLLECT,
                        NULL,
                        0,
                        TRUE);

                break;
            case '3':

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_PERSMAT_CAL,
                        NULL,
                        0,
                        TRUE);


                break;
            case '4':

                stereoAutoCalib_tda3x_save_ldc_lut(&chainsObj.ucObj.Alg_AutoRemapPrm);

                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_stereoAutoCalib_tda3x_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_stereoAutoCalib_tda3x_StopAndDeleteApp(&chainsObj);

    /*
     *  Change to the root dir
     */
    retVal = File_chDir("/\0");
    UTILS_assert(0 == retVal);
}



