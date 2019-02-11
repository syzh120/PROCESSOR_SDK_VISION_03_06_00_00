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
#include "chains_issMultCaptIspSimcop_Stereo_priv.h"

#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>

#define STEREO_ISP_LDC_MESH_TABLE_PITCH(w, r) \
                                        ((((((w)/(r))+1) + 15U) & ~15U) * (4U))

#define CAPTURE_SENSOR_WIDTH            (1280)
#define CAPTURE_SENSOR_HEIGHT           (720)

#define CAPTURE_SENSOR_AR140_WIDTH      (1280)
#define CAPTURE_SENSOR_AR140_HEIGHT     (800)

#define REMAP_WIDTH                     800
#define REMAP_HEIGHT                    384

#define LIVE_CAMERA_DISPLAY_WIDTH       640 //960
#define LIVE_CAMERA_DISPLAY_HEIGHT      360 //540

#define STEREO_OUTPUT_WIDTH             640
#define STEREO_OUTPUT_HEIGHT            360

#define SIMCOP_OUTPUT_NUM_BUFFERS       (6U)
#define ISP_OUTPUT_NUM_BUFFERS          (4U)


#pragma DATA_ALIGN(chainsIssStereoLdcTable, 32)

#ifdef ISS_INCLUDE /* LDC table included only if ISS is included */
UInt8 chainsIssStereoLdcTable[] =
{
    #include "iss_tables_stereo_ldc_lut.h"
};
#else
UInt8 chainsIssStereoLdcTable[1];
#endif


/**
 *******************************************************************************
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


/*
 * AEWB algorithm memory requirement cannot be calculated upfront.
 * This size is known by running the use-case once with large size
 * and then checking the log for unused memory in AEWB algorithm
 */
#define ALG_AEWB_MEM_SIZE                           (896*1024)

//#define ENABLE_WDR_MERGE_PARAMS_CFG

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraFrameCopyObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issMultCaptIspSimcop_StereoObj ucObj;

    IssIspConfigurationParameters ispConfig;
    AppUtils_Obj                    appObjPrms;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;

    UInt32  numCh;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    IssM2mSimcopLink_OperatingMode simcopMode;
    Bool bypassVtnf;
    Bool bypassLdc;

    /* Sensor and ISS parameters */
    IssSensor_CreateParams sensorCreatePrms;
    IssSensor_AeParams sensorAePrms;
    IssSensor_ExposureParams sensorExpPrms;
    IssSensor_Info sensorInfo;
    ChainsCommon_IssSensorIf sensorIntfInfo;
    IssAewbAlgOutParams issAewbPrms;
} chains_issMultCaptIspSimcop_StereoAppObj;


#ifdef ENABLE_WDR_MERGE_PARAMS_CFG
/* Function to get the exposure parameters from the sensor and update
   the merge parameters in the ISP. Called only when WDR merge is enabled. */
Void chains_issMultCaptIspSimcop_Stereo_Config_Merge(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pIspCfg, Void *appData)
{
    chains_issMultCaptIspSimcop_StereoAppObj *pObj =
        (chains_issMultCaptIspSimcop_StereoAppObj *)appData;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pAewbAlgOut);

    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    /* Get Exposure ratio parameters from the sensor */
    ChainsCommon_IssGetExposureParams(pAewbAlgOut);

    /* When dgain is applied only to long after split, there is a
        different ratio for split and merge */
    /* setting up merge parameters even for 2 pass wdr mode when AE is
       not enabled because merge parameter calculation uses digital gain
       for the calculation */
    if ((TRUE == pAewbAlgOut->outPrms[0].useAeCfg) ||
        ((pIssM2mIspPrm->channelParams[0].operatingMode ==
            ISSM2MISP_LINK_OPMODE_2PASS_WDR) &&
         (ALGORITHMS_ISS_AEWB_MODE_AWB == pAlg_IssAewbPrm->mode)))
    {
        System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS,
            pAewbAlgOut,
            sizeof(IssAewbAlgOutParams),
            TRUE);
    }
}
#endif


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
Void chains_issMultCaptIspSimcop_Stereo_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Org,
                                    DisplayLink_CreateParams *pPrm_Disparity,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    Chains_DisplayType displayType,
                                    UInt32 orgWinWidth,
                                    UInt32 orgWinHeight,
                                    UInt32 dispWinWidth,
                                    UInt32 dispWinHeight)
{

    if(pPrm_Org)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Org->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Org->rtParams.tarWidth  = orgWinWidth*2;
        pPrm_Org->rtParams.tarHeight = orgWinHeight;
        pPrm_Org->rtParams.posX      = 0;
        pPrm_Org->rtParams.posY      = 720;

        pPrm_Org->displayId          = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pPrm_Disparity)
    {
        pPrm_Disparity->rtParams.tarWidth  = dispWinWidth;
        pPrm_Disparity->rtParams.tarHeight = dispWinHeight;
        pPrm_Disparity->rtParams.posX      = 0;
        pPrm_Disparity->rtParams.posY      = 0;

        pPrm_Disparity->displayId          = DISPLAY_LINK_INST_DSS_VID1;
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

Void chains_issMultCaptIspSimcop_Stereo_SetIspConfig(
            chains_issMultCaptIspSimcop_StereoAppObj *pObj)
{
    Int32 status;

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
            pObj->bypassLdc,
            pObj->bypassVtnf);

    /* MUST be called after link create and before link start */
    pObj->simcopConfig.chNum = 0;

    /* Configure the LDC Luts */
    pObj->simcopConfig.ldcConfig->lutCfg.address = (UInt32)&chainsIssStereoLdcTable;

    pObj->ldcCfg.lutCfg.downScaleFactor =
                                        VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;

    /* REMAP width - the simcop output width */
    pObj->ldcCfg.lutCfg.lineOffset =
                    STEREO_ISP_LDC_MESH_TABLE_PITCH(REMAP_WIDTH, \
                                (1U << pObj->ldcCfg.lutCfg.downScaleFactor));

    pObj->ldcCfg.advCfg.outputFrameWidth = REMAP_WIDTH;
    pObj->ldcCfg.advCfg.outputFrameHeight = REMAP_HEIGHT;
    pObj->ldcCfg.advCfg.outputBlockWidth = 16;
    pObj->ldcCfg.advCfg.outputBlockHeight = 16;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BICUBIC;

    status = System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
    UTILS_assert(0 == status);

}

Void chains_issMultCaptIspSimcop_Stereo_SetIssRszPrms(
        IssRszLink_CreateParams *issM2mRszCapturePrms,
        UInt32  captureInWidth,
        UInt32  captureInHeight,
        UInt32  captureOutWidth,
        UInt32  captureOutHeight,
        IssRszLink_CreateParams *issM2mRszDisplayPrms,
        UInt32  displayInWidth,
        UInt32  displayInHeight,
        UInt32  displayOutWidth,
        UInt32  displayOutHeight)
{
    UInt16 chId;
    IssRszLink_ChannelParams *chPrms;

    if(issM2mRszCapturePrms)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &issM2mRszCapturePrms->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = captureOutWidth;
            chPrms->outParams.heightRszA  = captureOutHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = 0;
            chPrms->inCropCfg.cropStartY = 0;
            chPrms->inCropCfg.cropWidth = captureInWidth;
            chPrms->inCropCfg.cropHeight = captureInHeight;
        }
    }

    if(issM2mRszDisplayPrms)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &issM2mRszCapturePrms->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = displayOutWidth;
            chPrms->outParams.heightRszA  = displayOutHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = 136;
            chPrms->inCropCfg.cropStartY = 9;
            chPrms->inCropCfg.cropWidth = displayInWidth;
            chPrms->inCropCfg.cropHeight = displayInHeight;
        }
    }

}

Void chains_issMultCaptIspSimcop_Stereo_SetSelectPrm(SelectLink_CreateParams *pPrm)
{
    // pPrm
    UTILS_assert(pPrm->numOutQue == 2);

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 1;
    pPrm->outQueChInfo[0].inChNum[0] = 0;

    pPrm->outQueChInfo[1].outQueId   = 1;
    pPrm->outQueChInfo[1].numOutCh   = 1;
    pPrm->outQueChInfo[1].inChNum[0] = 1;

}


Void chains_issMultCaptIspSimcop_Stereo_SetSyncPrm(SyncLink_CreateParams *pPrm)
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;

}

Void chains_issMultCaptIspSimcop_Stereo_SetAlgDmaSwMsPrm(
        AlgorithmLink_DmaSwMsCreateParams *pPrm,
        UInt32 winWidth,
        UInt32 winHeight)
{

    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    pPrm->maxOutBufWidth     = winWidth*2;
    pPrm->maxOutBufHeight    = winHeight;
    pPrm->numOutBuf          = 4;
    pPrm->useLocalEdma       = FALSE;

    pPrm->initLayoutParams.numWin = 2;
    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;


    pWinInfo = &pPrm->initLayoutParams.winInfo[0];
    pWinInfo->chId = 1;
    pWinInfo->inStartX = 0;
    pWinInfo->inStartY = 0;
    pWinInfo->width = winWidth;
    pWinInfo->height = winHeight;
    pWinInfo->outStartX = 0;
    pWinInfo->outStartY = 0;

    pWinInfo = &pPrm->initLayoutParams.winInfo[1];
    pWinInfo->chId = 0;
    pWinInfo->inStartX = 0;
    pWinInfo->inStartY = 0;
    pWinInfo->width = winWidth;
    pWinInfo->height = winHeight;
    pWinInfo->outStartX = pWinInfo->width;
    pWinInfo->outStartY = 0;
}

/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_issMultCaptIspSimcop_StereoAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucObj.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucObj.IssM2mIspPrm;

    pCapturePrm->numCh = pObj->numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;

    /* Disable Resizer B */
    pIspPrm->channelParams[0U].\
                        enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;

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

        /* Disable Resizer B */
        pIspPrm->channelParams[ch].\
                            enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set the pin mux for the TDA3X EVM
 *
 *******************************************************************************
*/
static setMuxes(chains_issMultCaptIspSimcop_StereoAppObj *pObj)
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
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_issMultCaptIspSimcop_Stereo_SetAppPrms(chains_issMultCaptIspSimcop_StereoObj *pUcObj, Void *appObj)
{
    UInt32 numCh;
    chains_issMultCaptIspSimcop_StereoAppObj *pObj
        = (chains_issMultCaptIspSimcop_StereoAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC;
    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = FALSE;


    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    ispOpMode = pObj->chainsCfg->ispOpMode;

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = pObj->numCh;
    pObj->appObjPrms.ispOpMode = ispOpMode;
    pObj->appObjPrms.simcopOpMode = pObj->simcopMode;
    pObj->appObjPrms.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appObjPrms);

    appInitIssCaptParams(&pObj->appObjPrms, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appObjPrms, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appObjPrms, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);
    appInitIssSimcopParams(&pObj->appObjPrms, pUcObj->IssM2mSimcopLinkID,
        &pUcObj->IssM2mSimcopPrm);

    /*  Override the capture and ISP parameters for multi channel and
        disable resizer B */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight);

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    /* AEWB parameters */
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    ChainsCommon_TDA3x_Stereo_SetPrms(
        &pUcObj->Sync_CensusInPrm,
        &pUcObj->Alg_CensusPrm,
        &pUcObj->Alg_DisparityHamDistPrm,
        &pUcObj->Alg_StereoPostProcessPrm,
        REMAP_WIDTH,
        REMAP_HEIGHT,
        STEREO_OUTPUT_WIDTH,
        STEREO_OUTPUT_HEIGHT
        );


    ChainsCommon_Stereo_SetGrpxSrcPrms(
            &pUcObj->GrpxSrcPrm,
            pObj->displayWidth,
            pObj->displayHeight);

    chains_issMultCaptIspSimcop_Stereo_SetIssRszPrms(
        &pUcObj->IssM2mResizer_CapturePrm,
        CAPTURE_SENSOR_WIDTH,
        CAPTURE_SENSOR_HEIGHT,
        REMAP_WIDTH,
        REMAP_HEIGHT,
        NULL,
        STEREO_OUTPUT_WIDTH,
        STEREO_OUTPUT_HEIGHT,
        STEREO_OUTPUT_WIDTH,
        STEREO_OUTPUT_HEIGHT);

    chains_issMultCaptIspSimcop_Stereo_SetSelectPrm(&pUcObj->Select_CapturePrm);

#if 1
    chains_issMultCaptIspSimcop_Stereo_SetSyncPrm(&pUcObj->Sync_OrgPrm);
#endif
    /*
    chains_issMultCaptIspSimcop_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMsPrm,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT);
    */

#if 1
    chains_issMultCaptIspSimcop_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMsPrm,
            REMAP_WIDTH,
            REMAP_HEIGHT);
#endif


    /*
    pObj->captureOutWidth = pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->captureOutHeight = pUcObj->IssCapturePrm.outParams[0U].height;
    */

#if 1
    chains_issMultCaptIspSimcop_Stereo_SetDisplayPrms(
            &pUcObj->Display_OrgPrm,
            &pUcObj->Display_DisparityPrm,
            &pUcObj->Display_GrpxPrm,
            pObj->chainsCfg->displayType,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            1280,
            720);
#else
    ChainsCommon_Stereo_SetDisplayPrms(
            &pUcObj->Display_OrgPrm,
            &pUcObj->Display_DisparityPrm,
            &pUcObj->Display_GrpxPrm,
            0,
            0,
            1280,
            720,
            0,
            720,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0);

#endif

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    // ISP params
    for (numCh = 0U; numCh < pUcObj->IssCapturePrm.numCh; numCh ++)
    {

        /* Change maximum output buffer size in the ISP link as well */
        pUcObj->IssM2mIspPrm.channelParams[numCh].useBufSizePrmsFlag = FALSE;
        pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufWidth = CAPTURE_SENSOR_WIDTH;
        pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufHeight = CAPTURE_SENSOR_HEIGHT;

        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
                    ISP_OUTPUT_NUM_BUFFERS;

    }

    // Simcop params
    pUcObj->IssM2mSimcopPrm.channelParams[0].useOutputFrameSize = TRUE;

    pUcObj->IssM2mSimcopPrm.channelParams[0].outputFrameWidth =  REMAP_WIDTH;
    pUcObj->IssM2mSimcopPrm.channelParams[0].outputFrameHeight = REMAP_HEIGHT;

    pUcObj->IssM2mSimcopPrm.channelParams[0].overrideInFrmSize =  FALSE;

    pUcObj->IssM2mSimcopPrm.channelParams[0].inputFrameWidth = REMAP_WIDTH;
    pUcObj->IssM2mSimcopPrm.channelParams[0].inputFrameHeight = REMAP_HEIGHT;

    pUcObj->IssM2mSimcopPrm.channelParams[0].numBuffersPerCh =
            SIMCOP_OUTPUT_NUM_BUFFERS;

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
 * \param   pObj  [IN] chains_issMultCaptIspSimcop_StereoAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_issMultCaptIspSimcop_Stereo_StartApp(chains_issMultCaptIspSimcop_StereoAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_issMultCaptIspSimcop_Stereo_SetIspConfig(pObj);

    setMuxes(pObj);
    appStartIssSensorSerDes(&pObj->appObjPrms);
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultCaptIspSimcop_Stereo_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_issMultCaptIspSimcop_StereoAppObj
 *
 *******************************************************************************
*/
Void chains_issMultCaptIspSimcop_Stereo_StopAndDeleteApp(chains_issMultCaptIspSimcop_StereoAppObj *pObj)
{
    chains_issMultCaptIspSimcop_Stereo_Stop(&pObj->ucObj);
    chains_issMultCaptIspSimcop_Stereo_Delete(&pObj->ucObj);

#if 0
    chains_issMultCaptIspSimcop_Stereo_FreeMemory(pObj);
#endif

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
Void Chains_issMultCaptIspSimcop_Stereo(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_issMultCaptIspSimcop_StereoAppObj chainsObj;

    if (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Please make sure BSP is build with WDR and LDC enabled !!!\n");
    }

    chainsObj.chainsCfg = chainsCfg;
    chainsObj.numCh = 2U;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_issMultCaptIspSimcop_Stereo_Create(&chainsObj.ucObj, &chainsObj);
    ChainsCommon_SetIssCaptureErrorHandlingCb(chainsObj.ucObj.IssCaptureLinkID);
    chains_issMultCaptIspSimcop_Stereo_StartApp(&chainsObj);

    // set fps
    // reduce frame rate for test
    //ChainsCommon_SetIssSensorFps(FVID2_FPS_15);


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
                chains_issMultCaptIspSimcop_Stereo_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }


    chains_issMultCaptIspSimcop_Stereo_StopAndDeleteApp(&chainsObj);

}

