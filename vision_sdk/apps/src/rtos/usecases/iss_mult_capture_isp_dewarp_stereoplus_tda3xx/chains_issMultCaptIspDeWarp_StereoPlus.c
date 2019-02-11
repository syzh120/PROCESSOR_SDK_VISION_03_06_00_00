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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains_common.h>
#include <src/include/chains_common_dewarp.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
//#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#include "chains_issMultCaptIspDeWarp_StereoPlus_priv.h"
#include "chains_issMultCaptIspDeWarp_StereoPlus.h"
#include "../common/chains_common_stereo_defines.h"


/* Media Thread */
#define STEREO_MEDIA_TASK_PRI            (4U)
#define STEREO_MEDIA_TASK_STACK_SIZE     (32U * 1024U)
#pragma DATA_ALIGN(stereoMediaTaskStack, 32)
#pragma DATA_SECTION(stereoMediaTaskStack, ".bss:taskStackSection")
static UInt8 stereoMediaTaskStack[STEREO_MEDIA_TASK_STACK_SIZE];


static chains_issMultCaptIspDeWarp_StereoPlusAppObj chainsObj;


/*******************************************************************************
 *  FUNCTION DEFINITIONS
 *******************************************************************************
 */

static Void updateIspDeWarpWithDefaultParams(
        chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj)
{
    Int32 status;
    UInt32 numCh;

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

    /* Changing Dewarp Configuration as required for this usecase */
    if (pObj->bypassLdc == TRUE)
    {
        pObj->ldcCfg.pixelPad = 0;
    }
    else
    {
        pObj->ldcCfg.pixelPad = 4U;
    }
    pObj->ldcCfg.advCfg.outputBlockWidth = STEREO_LDC_BLOCK_WIDTH;
    pObj->ldcCfg.advCfg.outputBlockHeight = STEREO_LDC_BLOCK_HEIGHT;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BICUBIC;

    for (numCh = 0U; numCh < pObj->ucObj.IssCapturePrm.numCh; numCh++)
    {
        pObj->simcopConfig.chNum = numCh;

        /* Configure the LDC Luts */
        pObj->ldcCfg.lutCfg.downScaleFactor = \
                                            VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
        pObj->ldcCfg.lutCfg.lineOffset = \
                STEREO_ISP_LDC_MESH_TABLE_PITCH(REMAP_WIDTH, \
                        (1U << pObj->ldcCfg.lutCfg.downScaleFactor));

        /*
        pObj->ldcCfg.advCfg.outputFrameWidth =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
        pObj->ldcCfg.advCfg.outputFrameHeight =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];
        */
        pObj->ldcCfg.advCfg.outputFrameWidth = REMAP_WIDTH;
        pObj->ldcCfg.advCfg.outputFrameHeight = REMAP_HEIGHT;

        pObj->ldcCfg.advCfg.outputBlockWidth = STEREO_LDC_BLOCK_WIDTH;
        pObj->ldcCfg.advCfg.outputBlockHeight = STEREO_LDC_BLOCK_HEIGHT;

        pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
        pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
        pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;

        /* Frame a plugin command and sent it out */
        pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
        pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);
        status = System_linkControl(pObj->ucObj.Alg_DeWarpLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
}


static Int32 createStereoMediaThread(
                        chains_issMultCaptIspDeWarp_StereoPlusAppObj *chainsObj)
{
    Int32 status;

    chainsObj->startStereoDemo = BspOsal_semCreate(0, (Bool) TRUE);
    UTILS_assert(NULL != chainsObj->startStereoDemo);

    chainsObj->mediaTaskHndl = BspOsal_taskCreate((BspOsal_TaskFuncPtr)
                                    chains_issMultCaptIspDeWarpStereoPlus_MediaTask,
                                    "ChainsCommon_IssStereoPlus_MediaTsk",
                                    STEREO_MEDIA_TASK_PRI,
                                    stereoMediaTaskStack,
                                    sizeof(stereoMediaTaskStack),
                                    chainsObj,
                                    UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(NULL != chainsObj->mediaTaskHndl);

    status = Utils_prfLoadRegister(chainsObj->mediaTaskHndl,
                                   "STEREO_MEDIA_TSK");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    return (status);
}

static Void deleteStereoMediaThread(
                        chains_issMultCaptIspDeWarp_StereoPlusAppObj *chainsObj)

{
    Utils_prfLoadUnRegister(chainsObj->mediaTaskHndl);
    BspOsal_taskDelete(chainsObj->mediaTaskHndl);
    BspOsal_semDelete(chainsObj->startStereoDemo);
}


static AlgLink_DeWarpViewPointParams *provideViewParams (UInt32 processedCount)
{

    /*
     * Always provide the first view points
     */
    return (&chainsObj.algViewParams[0U]);
}


/**
 *******************************************************************************
 * \brief   Set create parameters for NetworkTx Link
 *******************************************************************************
*/
Void chains_issMultCaptIspDewarp_StereoPlus_SetNetworkTxPrms(
        NetworkTxLink_CreateParams *pPrm0,
        NetworkTxLink_CreateParams *pPrm1,
        NetworkTxLink_CreateParams *pPrm2)
{
    if (pPrm0 != NULL)
    {
        pPrm0->networkServerPort = NETWORK_TX_SERVER_PORT;

        /* Select network mode for null link */
        pPrm0->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP;
        /* no. of retry count */
        pPrm0->retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
    }

    if (pPrm1 != NULL)
    {
        pPrm1->networkServerPort = NETWORK_TX_SERVER_PORT + 1;

        /* Select network mode for null link */
        pPrm1->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP;
        /* no. of retry count */
        pPrm1->retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
    }

    if (pPrm2 != NULL)
    {
        pPrm2->networkServerPort = NETWORK_TX_SERVER_PORT + 2;

        /* Select network mode for null link */
        pPrm2->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP;
        /* no. of retry count */
        pPrm2->retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
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
Void chains_issMultCaptIspDewarp_StereoPlus_SetDisplayPrms(
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


Void chains_issMultCaptIspDewarp_StereoPlus_SetIssRszPrms(
        IssRszLink_CreateParams *issM2mRszCapturePrms,
        IssRszLink_CreateParams *issM2mRszOrgPrms,
        IssRszLink_CreateParams *issM2mRszDisparityPrms,
        StereoImageDims *imDims,
        UInt32  captureOutWidth,
        UInt32  captureOutHeight,
        UInt32  orgVideoWinWidth,
        UInt32  orgVideoWinHeight,
        UInt32  disparityWinWidth,
        UInt32  disparityWinHeight)
{
    UInt16 chId;
    IssRszLink_ChannelParams *chPrms;

    if(issM2mRszCapturePrms)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &issM2mRszCapturePrms->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = imDims->remapImageWidth;
            chPrms->outParams.heightRszA  = imDims->remapImageHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = 0;
            chPrms->inCropCfg.cropStartY = 0;
            chPrms->inCropCfg.cropWidth = captureOutWidth;
            chPrms->inCropCfg.cropHeight = captureOutHeight;
        }
    }

    if(issM2mRszOrgPrms)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &issM2mRszOrgPrms->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = orgVideoWinWidth;
            chPrms->outParams.heightRszA  = orgVideoWinHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = imDims->origRoiStartX;
            chPrms->inCropCfg.cropStartY = imDims->origRoiStartY;
            chPrms->inCropCfg.cropWidth = imDims->disparityOutputRoiWidth;
            chPrms->inCropCfg.cropHeight = imDims->disparityOutputRoiHeight;
        }
    }

    if(issM2mRszDisparityPrms)
    {
        for(chId = 0; chId < 2; chId++)
        {
            chPrms = &issM2mRszDisparityPrms->channelParams[chId];

            chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
            chPrms->outParams.widthRszA   = disparityWinWidth;
            chPrms->outParams.heightRszA  = disparityWinHeight;
            chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
            chPrms->numBuffersPerCh = 4U;

            chPrms->enableCrop = 1U;
            chPrms->inCropCfg.cropStartX = 0;
            chPrms->inCropCfg.cropStartY = 0;
            chPrms->inCropCfg.cropWidth = imDims->disparityOutputRoiWidth;
            chPrms->inCropCfg.cropHeight = imDims->disparityOutputRoiHeight;
        }
    }
}

Void chains_issMultCaptIspDewarp_StereoPlus_SetSyncPrms(SyncLink_CreateParams *pPrm)
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;

}

Void chains_issMultCaptIspDewarp_StereoPlus_SetStereoAppPrms(AlgorithmLink_StereoAppCreateParams *pStereoAppPrm)
{
    pStereoAppPrm->numPairs = 1;
    pStereoAppPrm->numOutputBuffers = 4;

    pStereoAppPrm->maxInputWidth = STEREO_OUTPUT_WIDTH;
    pStereoAppPrm->maxInputHeight = STEREO_OUTPUT_HEIGHT;

    pStereoAppPrm->bDataStreaming = TRUE; // streaming PCL and OG Map
    pStereoAppPrm->bSenseAvoid = FALSE;
    pStereoAppPrm->dispRoiParams.useDispRoiForPCL = FALSE;

}

/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj,
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
static setMuxes(chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj)
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
 * \brief   Set Calibration Use case Link Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_issMultCaptIspDeWarp_StereoPlus_SetAppPrms(
                chains_issMultCaptIspDeWarp_StereoPlusObj *pUcObj, Void *appObj)
{
    UInt32 chId;
    chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj
        = (chains_issMultCaptIspDeWarp_StereoPlusAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;

    /*
    AlgorithmLink_SrvCommonViewPointParams *pDefViewCfg;
    pDefViewCfg = &chainsObj.algViewParams[SRV_UC_3D_DEFAULT_VIEW_TO_USE];
    */

    /* set network params */
    chains_issMultCaptIspDewarp_StereoPlus_SetNetworkTxPrms(
            &pUcObj->NetworkTx_0Prm,
            &pUcObj->NetworkTx_1Prm,
            &pUcObj->NetworkTx_2Prm);

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

    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = FALSE;

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* check what ispOpMode - it should be default (= 0)? */
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

    /*  Override the capture and ISP parameters for multi channel and
        disable resizer B */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight);

    /* Enable frame dump in M2M ISP link */
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    /* deWarp create params */
    pUcObj->Alg_DeWarpPrm.allocBufferForDump = FALSE;
    for(chId = 0U; chId < STEREO_DEWARP_MAX_CH; chId++)
    {
        pUcObj->Alg_DeWarpPrm.channelParams[chId].operatingMode
                                                    = ALGLINK_DEWARP_OPMODE_LDC;

        pUcObj->Alg_DeWarpPrm.channelParams[chId].numBuffersPerCh = 3U;
    }

    /* AEWB parameters */
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
#if READ_SPARAMS_FROM_SD
        ChainsCommon_Stereo_Read_Params((Int32 *)pObj->steroParamsBuffer);
#endif
    }

    // Read stereo camera params from SD card
    ChainsCommon_Stereo_Read_CamParams((float *)pObj->steroCamParamsBuffer);


    ChainsCommon_TDA3x_Stereo_SetPrms(
        NULL, /*&pUcObj->Sync_CensusInPrm, */
        &pUcObj->Alg_CensusPrm,
        &pUcObj->Alg_DisparityHamDistPrm,
        &pUcObj->Alg_StereoPostProcessPrm,
        REMAP_WIDTH,
        REMAP_HEIGHT,
        STEREO_OUTPUT_WIDTH,
        STEREO_OUTPUT_HEIGHT
        );

    // SHOULD BE CALLED after ChainsCommon_TDA3x_Stereo_SetPrms()
    ChainsCommon_Stereo_SetCamPrms(&pUcObj->Alg_StereoAppPrm);


    // enable 16-bit disparity output
    pUcObj->Alg_StereoPostProcessPrm.enable16BitsDispOut = TRUE;

    ChainsCommon_Stereo_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
            pObj->displayWidth,
            pObj->displayHeight);


    chains_issMultCaptIspDewarp_StereoPlus_SetIssRszPrms(
            &pUcObj->IssM2mResizer_CapturePrm,
            NULL, //&pUcObj->VPE_OrgPrm,
            NULL, //&pUcObj->VPE_DisparityPrm,
            &gStereoImDims,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            1280,
            720);

    chains_issMultCaptIspDewarp_StereoPlus_SetSyncPrms(&pUcObj->Sync_DewarpPrm);

    ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMsPrm,
            2,
            REMAP_WIDTH, // LIVE_CAMERA_DISPLAY_WIDTH,
            REMAP_HEIGHT, //LIVE_CAMERA_DISPLAY_HEIGHT,
            0);


    chains_issMultCaptIspDewarp_StereoPlus_SetDisplayPrms(
            &pUcObj->Display_OrgPrm,
            &pUcObj->Display_DisparityPrm,
            &pUcObj->Display_GrpxPrm,
            pObj->chainsCfg->displayType,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            1280,
            720);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    chains_issMultCaptIspDewarp_StereoPlus_SetStereoAppPrms(&pUcObj->Alg_StereoAppPrm);

    /* ISP */
    for (chId = 0U; chId < pUcObj->IssCapturePrm.numCh; chId ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[chId].useBufSizePrmsFlag = TRUE;
        pUcObj->IssM2mIspPrm.channelParams[chId].maxBufWidth =
                                            STEREO_ISP_OUTPUT_WIDTH_W_PAD;
        pUcObj->IssM2mIspPrm.channelParams[chId].maxBufHeight =
                                            STEREO_ISP_OUTPUT_HEIGHT_W_PAD;

        pUcObj->IssM2mIspPrm.channelParams[chId].numBuffersPerCh =
            STEREO_ISP_NUM_OUTPUT_BUFS;
    }

    /* De Warp */
    pUcObj->Alg_DeWarpPrm.provideViewPointParams = &provideViewParams;


    for (chId = 0U; chId < /*STEREO_DEWARP_MAX_CH*/pUcObj->IssCapturePrm.numCh; chId ++)
    {
        pUcObj->Alg_DeWarpPrm.channelParams[chId].numBuffersPerCh =
            STEREO_DEWARP_NUM_OUTPUT_BUFS;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].overrideInFrmSize = FALSE;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].inputFrameWidth =
                                            REMAP_WIDTH; //STEREO_ISP_OUTPUT_WIDTH_W_PAD;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].inputFrameHeight =
                                            REMAP_HEIGHT; //STEREO_ISP_OUTPUT_HEIGHT_W_PAD;

        pUcObj->Alg_DeWarpPrm.channelParams[chId].useMaxOutputFrameSize = FALSE;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].maxOutputFrameWidth =
                                                STEREO_LDC_OUTPUT_WIDTH_MAX;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].maxOutputFrameHeight =
                                                STEREO_LDC_OUTPUT_HEIGHT_MAX;

        pUcObj->Alg_DeWarpPrm.channelParams[chId].useOutputFrameSize = FALSE;
        /*
        pUcObj->Alg_DeWarpPrm.channelParams[chId].outputFrameWidth =
                                        pDefViewCfg->ldcOutFrameWidth[numCh];
        pUcObj->Alg_DeWarpPrm.channelParams[chId].outputFrameHeight =
                                        pDefViewCfg->ldcOutFrameHeight[numCh];
         */
        pUcObj->Alg_DeWarpPrm.channelParams[chId].outputFrameWidth =
                                        REMAP_WIDTH;
        pUcObj->Alg_DeWarpPrm.channelParams[chId].outputFrameHeight =
                                        REMAP_HEIGHT;

    }

    for (chId = 0U; chId < STEREO_DEWARP_MAX_CH; chId ++)
    {
        /* Enable filling of output buffers for the dewarp algorithm */
        /* The filling can be enabled based on the camera */
        pUcObj->Alg_DeWarpPrm.fillOutBuf[chId] = ALGLINK_DEWARP_FILLTYPE_NONE;
    }

    pUcObj->Alg_DeWarpPrm.fillValueY = 0x00;
    pUcObj->Alg_DeWarpPrm.fillValueUV = 0x80;

    /*
     *  A strip which is portion of the output buffer is filled.
     *  1: Whole buffer,2: half of the buffer,4:quarter of the buffer
     */
    pUcObj->Alg_DeWarpPrm.fillRatio = 8;

    /* Disable OCMC RAM for LDC LUT */
    pUcObj->Alg_DeWarpPrm.useOcmcLdcLut = FALSE;

}


/**
 *******************************************************************************
 *
 * \brief   Start the Calibration Use case
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
static Void chains_issMultCaptIspDeWarp_StereoPlus_StartApp(
                            chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    updateIspDeWarpWithDefaultParams(pObj);

    setMuxes(pObj);
    appStartIssSensorSerDes(&pObj->appObjPrms);
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultCaptIspDeWarp_StereoPlus_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete the Calibration Use case
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspDeWarp_StereoPlus_StopAndDeleteApp(
                            chains_issMultCaptIspDeWarp_StereoPlusAppObj *pObj)
{
    chains_issMultCaptIspDeWarp_StereoPlus_Stop(&pObj->ucObj);
    chains_issMultCaptIspDeWarp_StereoPlus_Delete(&pObj->ucObj);

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
 * \brief   4 Channel surround view usecase entry function
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
Void Chains_issMultCaptIspDeWarp_StereoPlus(Chains_Ctrl *chainsCfg)
{
    char ch;
    Int32 status;
    UInt32 done = FALSE;

    if ((ISSM2MISP_LINK_OPMODE_1PASS_WDR != chainsCfg->ispOpMode) &&
        (ISSM2MISP_LINK_OPMODE_12BIT_LINEAR != chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: WDR should either be disabled or "
                    "in One Pass mode!!!\n");
        return;
    }

    chainsObj.chainsCfg = chainsCfg;
    chainsObj.numViewPoints = 1U;
    chainsObj.numCh = 2U;

    // for TFDTP - DO WE NEED IT?
    chainsObj.netProcId = Utils_netGetProcId();
    if(chainsObj.netProcId==System_getSelfProcId())
    {
        Vps_printf(" \n");
        Vps_printf(" CHAINS: ERROR: Networking/NDK MUST be run on different CPU"
                   " than IPU1-0.\n");
        Vps_printf(" CHAINS: ERROR: If you need to run this use-case with NDK"
                   " on IPU1-0 then regenerate the use-case with NetworkTx"
                   " links on IPU1-0.\n"
                   );
        Vps_printf(" \n");
        return;
    }


    // Dewarp for only one view, i.e. right camera in stereo
    memset((void*) &chainsObj.algViewParams, 0,
                    sizeof(AlgLink_DeWarpViewPointParams) * STEREO_MAX_NUM_VIEW_POINTS);
    memset((void*) &chainsObj.ldcMeshTableContainer, 0,
                        sizeof(System_VideoFrameCompositeBuffer) * STEREO_MAX_NUM_VIEW_POINTS);


    /*
     *  The SV files are present in the TDA3X folder
     */
#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
    {
        status = SYSTEM_LINK_STATUS_SOK;
    } else
#endif
    {
        status = File_chDir(STEREO_DIR_NAME);
        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            Vps_printf(" CHAINS: %s Folder not present in MMC/SD \n", STEREO_DIR_NAME);
            Vps_printf(" CHAINS: Requires LDC LUTs in %s folder \n", STEREO_DIR_NAME);
            return;
        }
    }

    /*
     * allocate memory to read stereo params from SD card
     */
#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
#if READ_SPARAMS_FROM_SD
        chainsObj.steroParamsBuffer = ChainsCommon_DeWarp_memAlloc(
                                                STEREO_PARAM_SIZE,
                                                128U);
#endif


        chainsObj.steroCamParamsBuffer = ChainsCommon_DeWarp_memAlloc(
                                                STEREO_CAMPARAM_SIZE,
                                                128U);
    }


    /* . Create a sem for media handshake
       . Wait for LDC LUTs read completion
       . Create the chain and proceed normally
       . DeWarp callback occurs at every frame, provide required LUTs
       */
    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        createStereoMediaThread(&chainsObj);

        /* Wait for LDC LUTs */
        BspOsal_semWait(chainsObj.startStereoDemo, BSP_OSAL_WAIT_FOREVER);
    }


    chains_issMultCaptIspDeWarp_StereoPlus_Create(
                                    &chainsObj.ucObj,
                                    &chainsObj);

    chains_issMultCaptIspDeWarp_StereoPlus_StartApp(&chainsObj);

    // set fps
    // reduce frame rate for test
    //ChainsCommon_SetIssSensorFps(FVID2_FPS_30);

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
                chains_issMultCaptIspDeWarp_StereoPlus_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_issMultCaptIspDeWarp_StereoPlus_StopAndDeleteApp(&chainsObj);

#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
        chains_issMultCaptIspDeWarpStereoPlus_FreeBufs(&chainsObj);
    }

    deleteStereoMediaThread(&chainsObj);


    /* free memory to read stereo params from SD */
#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
#if READ_SPARAMS_FROM_SD
        ChainsCommon_DeWarp_memFree(chainsObj.steroParamsBuffer,
                STEREO_PARAM_SIZE);
#endif

        ChainsCommon_DeWarp_memFree(chainsObj.steroCamParamsBuffer,
                STEREO_CAMPARAM_SIZE);
        /*
         *  Change to the root dir
         */
        status = File_chDir("/\0");
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

}
