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
#include "chains_common_stereo_defines.h"

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

/**
 *******************************************************************************
 * \brief Number of buffers per channel per link
 *******************************************************************************
 */
#define LINK_NUM_BUFFERS                (6)


#define AUTO_REMAP_FEATURE_PTS          2500 // should be the same to SMALC_MAX_HARRIS_FEATURES - to revisit
#define AUTO_REMAP_FEAUTRE_HDR_SIZE     6
#define AUTO_REMAP_FEATURE_BUF_SIZE     (AUTO_REMAP_FEAUTRE_HDR_SIZE + AUTO_REMAP_FEATURE_PTS * 8) // 2 * sizeof (Int16)


char gChains_stereo_autoremap_Menu[] = {

    "\r\n "
    "\r\n ===================="
    "\r\n Chains Streo AutoRemap Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 1: Reset frame number and capture stereo"
    "\r\n "
    "\r\n 2: Capture stereo"
    "\r\n "
    "\r\n 3: Generate remap tables "
    "\r\n "
    "\r\n 4: Store remap tables (Only for TDA3x)"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


/**
 *******************************************************************************
 * \brief Global Structure of stereo params to be read from SD card
 *******************************************************************************
 */
Stereo_CreateParamsFromSD gStereoParamsFromSD;


/**
 *******************************************************************************
 * \brief Global Structure of stereo camera params to be read from SD card
 *******************************************************************************
 */
Stereo_CreateCamParamsFromSD gStereoCamParamsFromSD;


/**
 *******************************************************************************
 * \brief Global Structure for storing configurable stereo parameters
 *******************************************************************************
 */
Stereo_ConfigurableCreateParams gStereoParams;

/**
 *******************************************************************************
 * \brief Global Structure for storing different image dimensions used throughout the execution of the stereo-vision algorithm
 *******************************************************************************
 */
StereoImageDims gStereoImDims;

/**
 *******************************************************************************
 *
 * \brief   This function populates a structure StereoImageDims when the chain is started.
 *
 *  \param  imDim[OUT] Pointer to the StereoImageDims structure to be populated
 *          pStereoParams [IN] Pointer to the stereo parameters
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_initImageDims(StereoImageDims *imDim,
        Stereo_ConfigurableCreateParams *pStereoParams,
        Stereo_CreateParamsFromSD *pStereoParamsSD)
{

    Int32 remapBlockWidth = REMAP_OUTPUT_BLOCK_WIDTH;
    Int32 remapBlockHeight = REMAP_OUTPUT_BLOCK_HEIGHT;

#if READ_SPARAMS_FROM_SD
    if (pStereoParamsSD->numParams != 0)
    {
        pStereoParams->numDisparities = pStereoParamsSD->stereoParamsSD[NUM_DISPARITIES_SD];
        pStereoParams->disparityStepSize = pStereoParamsSD->stereoParamsSD[DISPARITY_STEP_SIZE_SD];
        pStereoParams->disparitySearchDir = pStereoParamsSD->stereoParamsSD[DISPARITY_SEARCH_DIR_SD];
        pStereoParams->disparitySupportWinWidth = pStereoParamsSD->stereoParamsSD[DISPARITY_WIN_WIDTH_SD];
        pStereoParams->disparitySupportWinHeight = pStereoParamsSD->stereoParamsSD[DISPARITY_WIN_HEIGHT_SD];
        pStereoParams->leftRightCheckEna = pStereoParamsSD->stereoParamsSD[DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP_SD];
        pStereoParams->censusWinWidth = pStereoParamsSD->stereoParamsSD[CENSUS_WIN_WIDTH_SD];
        pStereoParams->censusWinHeight = pStereoParamsSD->stereoParamsSD[CENSUS_WIN_WIDTH_SD];
        pStereoParams->censusWinHorzStep = pStereoParamsSD->stereoParamsSD[CENSUS_WIN_HORZ_STEP_SD];
        pStereoParams->censusWinVertStep = pStereoParamsSD->stereoParamsSD[CENSUS_WIN_VERT_STEP_SD];

        pStereoParams->postproc_colormap_index = pStereoParamsSD->stereoParamsSD[POSTPROC_COLORMAP_INDEX_SD];

        remapBlockWidth = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_WIDTH_SD];
        remapBlockHeight = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_HEIGHT_SD];

#if 0
        Vps_printf("Stereo Params: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
                pStereoParams->numDisparities,
                pStereoParams->disparityStepSize,
                pStereoParams->disparitySearchDir,
                pStereoParams->disparitySupportWinWidth,
                pStereoParams->disparitySupportWinHeight,
                pStereoParams->leftRightCheckEna,
                pStereoParams->censusWinWidth,
                pStereoParams->censusWinHeight,
                pStereoParams->censusWinHorzStep,
                pStereoParams->censusWinVertStep,
                pStereoParams->postproc_colormap_index);
        Vps_printf("Remap:%d, %d\n", remapBlockWidth, remapBlockHeight);
#endif

	}
#endif


    imDim->disparityInputImageWidth= ALIGN(imDim->disparityOutputRoiWidth + pStereoParams->numDisparities - 1 + pStereoParams->disparitySupportWinWidth - 1, 4);
    imDim->disparityInputImageHeight= ALIGN(imDim->disparityOutputRoiHeight + pStereoParams->disparitySupportWinHeight - 1, 3);

    if (pStereoParams->disparitySearchDir== DISPARITY_TI_RIGHT_TO_LEFT) {
        imDim->disparityInputLeftImageStartX= ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    }
    else {
        imDim->disparityInputLeftImageStartX= pStereoParams->numDisparities - 1 + ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    }

    imDim->disparityInputLeftImageStartY= ((pStereoParams->disparitySupportWinHeight - 1) >> 1);

    imDim->disparityInputRightImageStartX= ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    imDim->disparityInputRightImageStartY= ((pStereoParams->disparitySupportWinHeight - 1) >> 1);

    imDim->censusOutputRoiWidth= imDim->disparityInputImageWidth;
    imDim->censusOutputRoiHeight= imDim->disparityInputImageHeight;

    if (imDim->remapImageWidth== 0 || imDim->remapImageHeight== 0) {

        imDim->censusInputImageWidth= imDim->censusOutputRoiWidth + pStereoParams->censusWinWidth - 1;
        /* round up to multiple of REMAP_OUTPUT_BLOCK_WIDTH */
        imDim->censusInputImageWidth= ((imDim->censusInputImageWidth + (remapBlockWidth-1))/remapBlockWidth)*remapBlockWidth;

        imDim->censusInputImageHeight= imDim->censusOutputRoiHeight + pStereoParams->censusWinHeight - 1;
        /* round up to multiple of REMAP_OUTPUT_BLOCK_HEIGHT */
        imDim->censusInputImageHeight= ((imDim->censusInputImageHeight + (remapBlockHeight-1))/remapBlockHeight)*remapBlockHeight;
    }
    else {
        imDim->censusInputImageWidth= imDim->remapImageWidth;
        imDim->censusInputImageHeight= imDim->remapImageHeight;
    }

    imDim->censusInputImageStartX= ((pStereoParams->censusWinWidth - 1)>>1);
    imDim->censusInputImageStartY= ((pStereoParams->censusWinHeight - 1)>>1);

    imDim->remapImageWidth= imDim->censusInputImageWidth;
    imDim->remapImageHeight= imDim->censusInputImageHeight;

    imDim->origRoiStartX= imDim->censusInputImageStartX + imDim->disparityInputLeftImageStartX;
    imDim->origRoiStartY= imDim->censusInputImageStartY + imDim->disparityInputLeftImageStartY;

    // Print stereo parameters
    Vps_printf("imDim->disparityInputImageWidth:%d, imDim->disparityInputImageHeight:%d\n",  imDim->disparityInputImageWidth, imDim->disparityInputImageHeight);
    Vps_printf("imDim->disparityInputLeftImageStartX:%d, imDim->disparityInputLeftImageStartY:%d\n", imDim->disparityInputLeftImageStartX, imDim->disparityInputLeftImageStartY);
    Vps_printf("imDim->disparityInputRightImageStartX:%d, imDim->disparityInputRightImageStartY:%d \n", imDim->disparityInputRightImageStartX, imDim->disparityInputRightImageStartY);
    Vps_printf("imDim->censusOutputRoiWidth:%d, imDim->censusOutputRoiHeight:%d\n", imDim->censusOutputRoiWidth, imDim->censusOutputRoiHeight);
    Vps_printf("imDim->censusInputImageWidth:%d, imDim->censusInputImageHeight:%d \n", imDim->censusInputImageWidth, imDim->censusInputImageHeight);
    Vps_printf("imDim->censusInputImageStartX:%d, imDim->censusInputImageStartY:%d\n", imDim->censusInputImageStartX, imDim->censusInputImageStartY);
    Vps_printf("imDim->remapImageWidth:%d, imDim->remapImageHeight:%d\n", imDim->remapImageWidth, imDim->remapImageHeight);
    Vps_printf("imDim->origRoiStartX:%d, imDim->origRoiStartY:%d\n", imDim->origRoiStartX, imDim->origRoiStartY);
}

/**
 *******************************************************************************
 *
 * \brief   callback to handle user defined commands reaching system link
 *
 *  \param  cmd [IN] Command that needs to be handled
 *          pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_CmdHandler(UInt32 cmd, Void *pPrm)
{
    if(cmd == SYSTEM_LINK_CMD_STEREO_SET_PARAM)
    {
        Stereo_CreateParams_Init((Stereo_ConfigurableCreateParams *)pPrm);
    }
}

/**
 *******************************************************************************
 *
 * \brief   ChainsCommon_Stereo_Init
 *
 *          This function initializes the configurable stereo params.
 *          And it also registers a callback to handle user defined commands reaching system link
 * \param   NULL
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_Init()
{
    Stereo_CreateParams_Init(NULL);
    SystemLink_registerHandler(ChainsCommon_Stereo_CmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          chains_lvdsVipMultiCam_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 *          Scale each CH to 1/2x size
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetVpePrm(
        VpeLink_CreateParams *pIspPrm,
        VpeLink_CreateParams *pOrgPrm,
        VpeLink_CreateParams *pDisparityPrm,
        StereoImageDims *imDims,
        UInt32 numLvdsCh,
        UInt32 disparityWinWidth,
        UInt32 disparityWinHeight,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight
)
{
    UInt16 chId;

    if(pIspPrm)
        pIspPrm->enableOut[0] = TRUE;

    if(pOrgPrm)
        pOrgPrm->enableOut[0] = TRUE;

    if(pDisparityPrm)
        pDisparityPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < 2; chId++)
    {
        if(pIspPrm)
        {
            pIspPrm->chParams[chId].outParams[0].width = imDims->remapImageWidth;
            pIspPrm->chParams[chId].outParams[0].height = imDims->remapImageHeight;
            pIspPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
            pIspPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pIspPrm->chParams[chId].scCropCfg.cropStartX = 0;
            pIspPrm->chParams[chId].scCropCfg.cropStartY = 0;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pIspPrm->chParams[chId].scCropCfg.cropWidth = CAPTURE_SENSOR_WIDTH;
            pIspPrm->chParams[chId].scCropCfg.cropHeight = SOFTISP_OUTPUT_HEIGHT;
        }

        if(pOrgPrm)
        {
            pOrgPrm->chParams[chId].outParams[0].width   = orgVideoWinWidth;
            pOrgPrm->chParams[chId].outParams[0].height  = orgVideoWinHeight;
            pOrgPrm->chParams[chId].outParams[0].dataFormat
            = SYSTEM_DF_YUV420SP_UV;
            pOrgPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pOrgPrm->chParams[chId].scCropCfg.cropStartX = imDims->origRoiStartX;
            pOrgPrm->chParams[chId].scCropCfg.cropStartY = imDims->origRoiStartY;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pOrgPrm->chParams[chId].scCropCfg.cropWidth  = imDims->disparityOutputRoiWidth;
            pOrgPrm->chParams[chId].scCropCfg.cropHeight = imDims->disparityOutputRoiHeight;
        }

        if(pDisparityPrm)
        {
            pDisparityPrm->chParams[chId].outParams[0].width = disparityWinWidth;
            pDisparityPrm->chParams[chId].outParams[0].height = disparityWinHeight;
            pDisparityPrm->chParams[chId].outParams[0].dataFormat
            = SYSTEM_DF_YUV420SP_UV;
            pDisparityPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pDisparityPrm->chParams[chId].scCropCfg.cropStartX = 0;
            pDisparityPrm->chParams[chId].scCropCfg.cropStartY = 0;
            pDisparityPrm->chParams[chId].scCropCfg.cropWidth = imDims->disparityOutputRoiWidth;
            pDisparityPrm->chParams[chId].scCropCfg.cropHeight
            = imDims->disparityOutputRoiHeight;
        }
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          chains_lvdsVipMultiCam_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetSyncPrm(
        SyncLink_CreateParams *pSyncPrm1,
        SyncLink_CreateParams *pSyncPrm2,
        UInt32 numLvdsCh
)
{
    if(pSyncPrm1)
    {
        pSyncPrm1->syncDelta = SYNC_DELTA_IN_MSEC;
        pSyncPrm1->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
    }

    if(pSyncPrm2)
    {
        pSyncPrm2->syncDelta = SYNC_DELTA_IN_MSEC;
        pSyncPrm2->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
    }
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

 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
        AlgorithmLink_DmaSwMsCreateParams *pPrm,
        UInt32 numLvdsCh,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight,
        UInt32 orgVideoWinGap
)
{
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    if(pPrm)
    {
        UTILS_assert(numLvdsCh == 2);

        pPrm->maxOutBufWidth     = orgVideoWinWidth*2 + orgVideoWinGap;
        pPrm->maxOutBufHeight    = orgVideoWinHeight;
        pPrm->numOutBuf          = 4;
        pPrm->useLocalEdma       = FALSE;

        pPrm->initLayoutParams.numWin = 2;
        pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
        pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;


        pWinInfo = &pPrm->initLayoutParams.winInfo[0];
        pWinInfo->chId = 1;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width = orgVideoWinWidth;
        pWinInfo->height = orgVideoWinHeight;
        pWinInfo->outStartX = 0;
        pWinInfo->outStartY = 0;

        pWinInfo = &pPrm->initLayoutParams.winInfo[1];
        pWinInfo->chId = 0;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width = orgVideoWinWidth;
        pWinInfo->height = orgVideoWinHeight;
        pWinInfo->outStartX = pWinInfo->width + orgVideoWinGap;
        pWinInfo->outStartY = 0;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipStereoOnly_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetDisplayPrms(
        DisplayLink_CreateParams *pPrm_OrgVideo,
        DisplayLink_CreateParams *pPrm_DisparityVideo,
        DisplayLink_CreateParams *pPrm_Grpx,
        UInt32 disparityWinStartX,
        UInt32 disparityWinStartY,
        UInt32 disparityWinWidth,
        UInt32 disparityWinHeight,
        UInt32 orgVideoWinStartX,
        UInt32 orgVideoWinStartY,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight,
        UInt32 orgVideoWinGap
)
{
    if(pPrm_OrgVideo)
    {
        pPrm_OrgVideo->rtParams.tarWidth         = orgVideoWinWidth*2 + orgVideoWinGap;
        pPrm_OrgVideo->rtParams.tarHeight        = orgVideoWinHeight;
        pPrm_OrgVideo->rtParams.posX             = orgVideoWinStartX;
        pPrm_OrgVideo->rtParams.posY             = orgVideoWinStartY;
        pPrm_OrgVideo->displayId                 = DISPLAY_LINK_INST_DSS_VID3;
    }

    if(pPrm_DisparityVideo)
    {
        pPrm_DisparityVideo->rtParams.tarWidth  = disparityWinWidth;
        pPrm_DisparityVideo->rtParams.tarHeight = disparityWinHeight;
        pPrm_DisparityVideo->rtParams.posX      = disparityWinStartX;
        pPrm_DisparityVideo->rtParams.posY      = disparityWinStartY;
        pPrm_DisparityVideo->displayId          = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pPrm_Grpx)
    {
        pPrm_Grpx->displayId                  = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Graphics Create Parameters
 *
 *
 *          This function is used to set the Grtaphics Link params.
 *          It is called in Create function.
 *
 * \param   pPrm         [IN]    GrpxSrcLink_CreateParams
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetGrpxSrcPrms(
        GrpxSrcLink_CreateParams *pPrm,
        UInt32 displayWidth,
        UInt32 displayHeight)
{
    if(pPrm)
    {
        pPrm->grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
        pPrm->grpxBufInfo.height   = displayHeight;
        pPrm->grpxBufInfo.width    = displayWidth;

        pPrm->stereoDisparityLayoutEnable = TRUE;
        pPrm->statsDisplayEnable = TRUE;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Edge Detection Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetSoftIspAlgPrms(
        AlgorithmLink_SoftIspCreateParams *pPrm)
{

    pPrm->imageWidth    = CAPTURE_SENSOR_WIDTH;
    pPrm->imageHeight   = SOFTISP_CROPPED_INPUT_HEIGHT;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
}

/**
 *******************************************************************************
 *
 * \brief   Set Remap Merge Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetRemapMergeAlgPrms(
        AlgorithmLink_RemapMergeCreateParams *pPrm,
        StereoImageDims *imDims,
        Stereo_CreateParamsFromSD *pStereoParamsSD)
{
    UInt32 qspiBufHeader[SYSTEM_QSPI_READ_WRITE_SIZE];

    Int32 remapBlockWidth = REMAP_OUTPUT_BLOCK_WIDTH;
    Int32 remapBlockHeight = REMAP_OUTPUT_BLOCK_HEIGHT;

#if READ_SPARAMS_FROM_SD
    if (pStereoParamsSD->numParams != 0)
    {
        remapBlockWidth = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_WIDTH_SD];
        remapBlockHeight = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_HEIGHT_SD];
    }
#endif


    pPrm->imageWidth    = CAPTURE_SENSOR_WIDTH;
    pPrm->imageHeight   = SOFTISP_OUTPUT_HEIGHT;

    pPrm->coordMapList        = 1;
    pPrm->isSrcMapFloat       = 0;
    pPrm->srcFormat           = 0;  // U8
    pPrm->dstFormat           = 0;  // U8
    pPrm->srcStride           = pPrm->roiWidth  = pPrm->dstStride = imDims->remapImageWidth;
    pPrm->srcHeight           = pPrm->roiHeight = imDims->remapImageHeight;
    pPrm->blockWidthBB        = remapBlockWidth;
    pPrm->blockHeightBB       = remapBlockHeight;
    pPrm->blockWidthTile      = 80;  // dont bother
    pPrm->blockHeightTile     = 40;  // dont bother
    pPrm->tileWidth           = 40;  // dont bother
    pPrm->tileHeight          = 50;  // dont bother
    pPrm->enableMerge         = 0;
    pPrm->interpolationLuma   = 1;
    pPrm->interpolationChroma = 0;
    pPrm->mapQshift           = 2;
    pPrm->rightShift          = 0;
    pPrm->sat_high            = 255;
    pPrm->sat_high_set        = 255;
    pPrm->sat_low             = 0;
    pPrm->sat_low_set         = 0;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
    /* Reading calibration tables from QSPI */
    /* Read the Header first */
    System_qspiReadSector((UInt32)qspiBufHeader,
            STEREO_CALIB_LUT_QSPI_OFFSET,
            SystemUtils_align(STEREO_CALIB_LUT_HEADER_SIZE, SYSTEM_QSPI_READ_WRITE_SIZE));

    if (STEREO_CALIB_LUT_TAG_ID == qspiBufHeader[0])
    {
        /* Read bin file size */
        pPrm->calibLUTBufPrms.calibLUTBufSize
        = qspiBufHeader[1] - STEREO_CALIB_LUT_HEADER_SIZE;
        pPrm->calibLUTBufPrms.pCalibLUTBuf
        = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE), /* Padd with QSPI_READ_WRITE_SIZE as  System_qspiReadSector writes in granularity of QSPI_READ_WRITE_SIZE bytes*/
                32);
        UTILS_assert(pPrm->calibLUTBufPrms.pCalibLUTBuf!=NULL);
        pPrm->calibLUTBufPrms.isValid= TRUE;
        /* Read the binary file */
        System_qspiReadSector((UInt32)pPrm->calibLUTBufPrms.pCalibLUTBuf,
                STEREO_CALIB_LUT_QSPI_OFFSET+STEREO_CALIB_LUT_HEADER_SIZE,
                SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE));
    }
    else

    {
        pPrm->calibLUTBufPrms.isValid= FALSE;
    }
}



/**
 *******************************************************************************
 *
 * \brief   Set Remap Merge Alg parameters for TDA2x
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_TDA2x_Stereo_SetRemapMergeAlgPrms(
        AlgorithmLink_RemapMergeCreateParams *pPrm,
        StereoImageDims *imDims,
        Stereo_CreateParamsFromSD *pStereoParamsSD)
{
    UInt32 qspiBufHeader[SYSTEM_QSPI_READ_WRITE_SIZE];

    Int32 remapBlockWidth = REMAP_OUTPUT_BLOCK_WIDTH;
    Int32 remapBlockHeight = REMAP_OUTPUT_BLOCK_HEIGHT;

#if READ_SPARAMS_FROM_SD
    if (pStereoParamsSD->numParams != 0)
    {
        remapBlockWidth = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_WIDTH_SD];
        remapBlockHeight = pStereoParamsSD->stereoParamsSD[REMAP_OUTPUT_BLOCK_HEIGHT_SD];
    }
#endif


    pPrm->imageWidth    = imDims->remapImageWidth;
    pPrm->imageHeight   = imDims->remapImageHeight;

    pPrm->coordMapList        = 1;
    pPrm->isSrcMapFloat       = 0;
    pPrm->srcFormat           = 0;  // U8
    pPrm->dstFormat           = 0;  // U8
    pPrm->srcStride           = imDims->remapImageWidth;
    pPrm->srcHeight           = imDims->remapImageHeight;
    pPrm->dstStride           = pPrm->roiWidth = imDims->remapImageWidth;
    pPrm->roiHeight           = imDims->remapImageHeight;
    pPrm->blockWidthBB        = remapBlockWidth;
    pPrm->blockHeightBB       = remapBlockHeight;
    pPrm->blockWidthTile      = 80;  // dont bother
    pPrm->blockHeightTile     = 40;  // dont bother
    pPrm->tileWidth           = 40;  // dont bother
    pPrm->tileHeight          = 50;  // dont bother
    pPrm->enableMerge         = 0;
    pPrm->interpolationLuma   = 1;
    pPrm->interpolationChroma = 0;
    pPrm->mapQshift           = 2;
    pPrm->rightShift          = 0;
    pPrm->sat_high            = 255;
    pPrm->sat_high_set        = 255;
    pPrm->sat_low             = 0;
    pPrm->sat_low_set         = 0;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
    /* Reading calibration tables from QSPI */
    /* Read the Header first */
    System_qspiReadSector((UInt32)qspiBufHeader,
            STEREO_CALIB_LUT_QSPI_OFFSET,
            SystemUtils_align(STEREO_CALIB_LUT_HEADER_SIZE, SYSTEM_QSPI_READ_WRITE_SIZE));

    if (STEREO_CALIB_LUT_TAG_ID == qspiBufHeader[0])
    {
        /* Read bin file size */
        pPrm->calibLUTBufPrms.calibLUTBufSize
        = qspiBufHeader[1] - STEREO_CALIB_LUT_HEADER_SIZE;
        pPrm->calibLUTBufPrms.pCalibLUTBuf
        = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE), /* Padd with QSPI_READ_WRITE_SIZE as  System_qspiReadSector writes in granularity of QSPI_READ_WRITE_SIZE bytes*/
                32);
        UTILS_assert(pPrm->calibLUTBufPrms.pCalibLUTBuf!=NULL);
        pPrm->calibLUTBufPrms.isValid= TRUE;
        /* Read the binary file */
        System_qspiReadSector((UInt32)pPrm->calibLUTBufPrms.pCalibLUTBuf,
                STEREO_CALIB_LUT_QSPI_OFFSET+STEREO_CALIB_LUT_HEADER_SIZE,
                SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE));
    }
    else
    {
        pPrm->calibLUTBufPrms.isValid= FALSE;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Edge Detection Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetCensusAlgPrms(
        AlgorithmLink_CensusCreateParams *pPrm,
        StereoImageDims *imDims,
        Stereo_ConfigurableCreateParams *pStereoParams)
{
    pPrm->imageRoiWidth     = imDims->censusOutputRoiWidth;
    pPrm->imageRoiHeight     = imDims->censusOutputRoiHeight;

    pPrm->inputBitDepth     = CENSUS_INPUT_BIT_DEPTH;
    pPrm->winWidth          = pStereoParams->censusWinWidth;
    pPrm->winHeight         = pStereoParams->censusWinHeight;
    pPrm->winHorzStep       = pStereoParams->censusWinHorzStep;
    pPrm->winVertStep       = pStereoParams->censusWinVertStep;

    pPrm->srcImageWidth     = imDims->censusInputImageWidth;
    pPrm->srcImageHeight    = imDims->censusInputImageHeight;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
}

/**
 *******************************************************************************
 *
 * \brief   Set Edge Detection Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetDisparityAlgPrms(
        AlgorithmLink_DisparityHamDistCreateParams *pPrm,
        StereoImageDims *imDims,
        Stereo_ConfigurableCreateParams *pStereoParams)
{
    pPrm->imageRoiWidth       = imDims->disparityOutputRoiWidth;
    pPrm->imageRoiHeight      = imDims->disparityOutputRoiHeight;
    pPrm->inputBitDepth     = DISPARITY_INPUT_BIT_DEPTH;
    pPrm->winWidth          = pStereoParams->disparitySupportWinWidth;
    pPrm->winHeight         = pStereoParams->disparitySupportWinHeight;
    pPrm->numDisparities    = pStereoParams->numDisparities;
    pPrm->disparityStep     = pStereoParams->disparityStepSize;
    pPrm->searchDir         = pStereoParams->disparitySearchDir;
    pPrm->extraRightLeftMap = pStereoParams->leftRightCheckEna;

    pPrm->srcImageWidth = imDims->disparityInputImageWidth;
    pPrm->srcImageHeight = imDims->disparityInputImageHeight;

    pPrm->inputLeftImageStartX= imDims->disparityInputLeftImageStartX;
    pPrm->inputLeftImageStartY= imDims->disparityInputLeftImageStartY;
    pPrm->inputRightImageStartX= imDims->disparityInputRightImageStartX;
    pPrm->inputRightImageStartY= imDims->disparityInputRightImageStartY;

    pPrm->numOutBuffers             = LINK_NUM_BUFFERS;
}

/**
 *******************************************************************************
 *
 * \brief   Set Edge Detection Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_SoftIspCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetStereoPostProcessPrms(
        AlgorithmLink_StereoPostProcessCreateParams *pPrm,
        StereoImageDims *imDims,
        Stereo_ConfigurableCreateParams *pStereoParams,
        Stereo_CreateParamsFromSD *pStereoParamsSD)
{
#if READ_SPARAMS_FROM_SD
	if (pStereoParamsSD->numParams != 0)
	{
        pPrm->numOutBuffers             = LINK_NUM_BUFFERS;
        pPrm->maxImageRoiWidth      = imDims->disparityOutputRoiWidth;
        pPrm->maxImageRoiHeight     = imDims->disparityOutputRoiHeight;
        pPrm->inputBitDepth         = CENSUS_INPUT_BIT_DEPTH;
        pPrm->censusWinWidth        = pStereoParams->censusWinWidth;
        pPrm->censusWinHeight       = pStereoParams->censusWinHeight;
        pPrm->disparityWinWidth     = pStereoParams->disparitySupportWinWidth;
        pPrm->disparityWinHeight    = pStereoParams->disparitySupportWinHeight;
        pPrm->numDisparities    = pStereoParams->numDisparities;
        pPrm->disparityStep         = pStereoParams->disparityStepSize;
        pPrm->disparitySearchDir         = pStereoParams->disparitySearchDir;
        pPrm->costMaxThreshold        = pStereoParamsSD->stereoParamsSD[POSTPROC_COST_MAX_THRESHOLD_SD]; // POSTPROC_COST_MAX_THRESHOLD;
        pPrm->minConfidenceThreshold  = pStereoParamsSD->stereoParamsSD[POSTPROC_CONF_MIN_THRSESHOLD_SD]; //POSTPROC_CONF_MIN_THRSESHOLD;
        pPrm->holeFillingStrength  = pStereoParamsSD->stereoParamsSD[POSTPROC_HOLEFILLING_STRENGTH_SD]; // POSTPROC_HOLEFILLING_STRENGTH;
        pPrm->textureLumaLoThresh = pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_LUMALOTHRESH_SD]; // POSTPROC_TEXTURE_LUMALOTHRESH;
        pPrm->textureLumaHiThresh = pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_LUMAHITHRESH_SD]; // POSTPROC_TEXTURE_LUMAHITHRESH;
        pPrm->textureThreshold= pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_THRESHOLD_SD];  // POSTPROC_TEXTURE_THRESHOLD;
        pPrm->lrMaxDiffThreshold= pStereoParamsSD->stereoParamsSD[POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD_SD]; // POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD;
        pPrm->maxDispDissimilarity= pStereoParamsSD->stereoParamsSD[POSTPROC_MAX_DISP_DISSIMILARITY_SD]; // POSTPROC_MAX_DISP_DISSIMILARITY;
        pPrm->minConfidentNSegment = pStereoParamsSD->stereoParamsSD[POSTPROC_MIN_CONFIDENT_N_SEG_SD]; // POSTPROC_MIN_CONFIDENT_N_SEG;
        pPrm->numFracBits         = POSTPROC_NUM_FRAC_BITS;
        pPrm->censusSrcImageWidth = imDims->censusInputImageWidth;
        pPrm->censusSrcImageHeight = imDims->censusInputImageHeight;
        pPrm->temporalFilterNumFrames= pStereoParamsSD->stereoParamsSD[POSTPROC_TEMPORAL_FILTER_NUM_FRAMES_SD]; // POSTPROC_TEMPORAL_FILTER_NUM_FRAMES;
        pPrm->minDisparityToDisplay= pStereoParamsSD->stereoParamsSD[POSTPROC_MIN_DISPARITY_DISPLAY_SD]; // POSTPROC_MIN_DISPARITY_DISPLAY;
        pPrm->colorMapIndex= pStereoParams->postproc_colormap_index;
        pPrm->disparityExtraRightLeft= pStereoParams->leftRightCheckEna;
        pPrm->imageStartX= imDims->origRoiStartX;
        pPrm->imageStartY= imDims->origRoiStartY;
        pPrm->useGrayScale = FALSE;
        pPrm->enable16BitsDispOut = FALSE;

#if 0
        Vps_printf("Post Params: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
                pStereoParamsSD->stereoParamsSD[POSTPROC_COST_MAX_THRESHOLD_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_CONF_MIN_THRSESHOLD_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_HOLEFILLING_STRENGTH_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_LUMALOTHRESH_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_LUMAHITHRESH_SD],

                pStereoParamsSD->stereoParamsSD[POSTPROC_TEXTURE_THRESHOLD_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_MAX_DISP_DISSIMILARITY_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_MIN_CONFIDENT_N_SEG_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_TEMPORAL_FILTER_NUM_FRAMES_SD],
                pStereoParamsSD->stereoParamsSD[POSTPROC_MIN_DISPARITY_DISPLAY_SD]);
#endif
    } else
#endif
    {
        pPrm->numOutBuffers             = LINK_NUM_BUFFERS;
        pPrm->maxImageRoiWidth      = imDims->disparityOutputRoiWidth;
        pPrm->maxImageRoiHeight     = imDims->disparityOutputRoiHeight;
        pPrm->inputBitDepth         = CENSUS_INPUT_BIT_DEPTH;
        pPrm->censusWinWidth        = pStereoParams->censusWinWidth;
        pPrm->censusWinHeight       = pStereoParams->censusWinHeight;
        pPrm->disparityWinWidth     = pStereoParams->disparitySupportWinWidth;
        pPrm->disparityWinHeight    = pStereoParams->disparitySupportWinHeight;
        pPrm->numDisparities    = pStereoParams->numDisparities;
        pPrm->disparityStep         = pStereoParams->disparityStepSize;
        pPrm->disparitySearchDir         = pStereoParams->disparitySearchDir;
        pPrm->costMaxThreshold        = POSTPROC_COST_MAX_THRESHOLD;
        pPrm->minConfidenceThreshold  = POSTPROC_CONF_MIN_THRSESHOLD;
        pPrm->holeFillingStrength  = POSTPROC_HOLEFILLING_STRENGTH;
        pPrm->textureLumaLoThresh= POSTPROC_TEXTURE_LUMALOTHRESH;
        pPrm->textureLumaHiThresh= POSTPROC_TEXTURE_LUMAHITHRESH;
        pPrm->textureThreshold= POSTPROC_TEXTURE_THRESHOLD;
        pPrm->lrMaxDiffThreshold= POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD;
        pPrm->maxDispDissimilarity= POSTPROC_MAX_DISP_DISSIMILARITY;
        pPrm->minConfidentNSegment = POSTPROC_MIN_CONFIDENT_N_SEG;
        pPrm->numFracBits         = POSTPROC_NUM_FRAC_BITS;
        pPrm->censusSrcImageWidth = imDims->censusInputImageWidth;
        pPrm->censusSrcImageHeight = imDims->censusInputImageHeight;
        pPrm->temporalFilterNumFrames= POSTPROC_TEMPORAL_FILTER_NUM_FRAMES;
        pPrm->minDisparityToDisplay= POSTPROC_MIN_DISPARITY_DISPLAY;
        pPrm->colorMapIndex= pStereoParams->postproc_colormap_index;
        pPrm->disparityExtraRightLeft= pStereoParams->leftRightCheckEna;
        pPrm->imageStartX= imDims->origRoiStartX;
        pPrm->imageStartY= imDims->origRoiStartY;
        pPrm->useGrayScale = FALSE;
        pPrm->enable16BitsDispOut = FALSE;
    }
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
Void ChainsCommon_Stereo_SetPrms(
        CaptureLink_CreateParams *pCapturePrm,
        VpeLink_CreateParams *pVPE_softispPrm,
        VpeLink_CreateParams *pVPE_orgdispPrm,
        VpeLink_CreateParams *pVPE_disparityPrm,
        AlgorithmLink_SoftIspCreateParams *pAlg_SoftIspPrm,
        AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm,
        AlgorithmLink_CensusCreateParams *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm,
        SyncLink_CreateParams *pSync_orgPrm,
        SyncLink_CreateParams *pSync_dispPrm,
        AlgorithmLink_DmaSwMsCreateParams *pAlg_DmaSwMsPrm,
        GrpxSrcLink_CreateParams *pGrpxSrcPrm,
        DisplayLink_CreateParams *pDisplay_orgPrm,
        DisplayLink_CreateParams *pDisplay_disparityPrm,
        DisplayLink_CreateParams *pDisplay_GrpxPrm,
        Chains_CaptureSrc captureSrc,
        Chains_DisplayType displayType,
        UInt32 captureSensorWidth,
        UInt32 captureSensorHeight,
        UInt32 remapWidth,
        UInt32 remapHeight,
        UInt32 stereoOutputWidth,
        UInt32 stereoOutputHeight,
        UInt32 disparityWinStartX,
        UInt32 disparityWinStartY,
        UInt32 disparityWinWidth,
        UInt32 disparityWinHeight,
        UInt32 orgVideoWinStartX,
        UInt32 orgVideoWinStartY,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight,
        UInt32 orgVideoWinGap
)
{
    UInt32 captureOutWidth = 0, captureOutHeight = 0;
    UInt32 displayWidth = 0, displayHeight = 0;

    gStereoImDims.disparityOutputRoiWidth= stereoOutputWidth;
    gStereoImDims.disparityOutputRoiHeight= stereoOutputHeight;
    gStereoImDims.remapImageWidth= remapWidth;
    gStereoImDims.remapImageHeight= remapHeight;
    ChainsCommon_Stereo_initImageDims(&gStereoImDims, &gStereoParams, &gStereoParamsFromSD);

    if(displayType==CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        captureOutWidth  = captureSensorWidth;
        captureOutHeight = captureSensorHeight;
        displayWidth     = 1280;
        displayHeight    = 720;
    }
    else
        if(displayType==CHAINS_DISPLAY_TYPE_HDMI_1080P)
        {
            captureOutWidth  = captureSensorWidth;
            captureOutHeight = captureSensorHeight;
            displayWidth     = 1920;
            displayHeight    = 1080;
        }

    if(pCapturePrm)
    {
        ChainsCommon_StereoCam_SetCapturePrms(pCapturePrm,
                captureSensorWidth,
                captureSensorHeight,
                captureOutWidth,
                captureOutHeight,
                captureSrc
        );
    }

    ChainsCommon_Stereo_SetVpePrm(pVPE_softispPrm,
            pVPE_orgdispPrm,
            pVPE_disparityPrm,
            &gStereoImDims,
            2,
            disparityWinWidth,
            disparityWinHeight,
            orgVideoWinWidth,
            orgVideoWinHeight
    );

    ChainsCommon_Stereo_SetSyncPrm(
            pSync_orgPrm,
            pSync_dispPrm,
            2
    );

    if(pAlg_DmaSwMsPrm)
        ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
                pAlg_DmaSwMsPrm,
                2,
                orgVideoWinWidth,
                orgVideoWinHeight,
                orgVideoWinGap
        );

    ChainsCommon_Stereo_SetGrpxSrcPrms(pGrpxSrcPrm,
            displayWidth,
            displayHeight
    );

    ChainsCommon_Stereo_SetDisplayPrms(pDisplay_orgPrm,
            pDisplay_disparityPrm,
            pDisplay_GrpxPrm,
            disparityWinStartX,
            disparityWinStartY,
            disparityWinWidth,
            disparityWinHeight,
            orgVideoWinStartX,
            orgVideoWinStartY,
            orgVideoWinWidth,
            orgVideoWinHeight,
            orgVideoWinGap
    );

    if(pAlg_SoftIspPrm)
        ChainsCommon_Stereo_SetSoftIspAlgPrms (pAlg_SoftIspPrm);

    if(pAlg_RemapMergePrm)
        ChainsCommon_Stereo_SetRemapMergeAlgPrms (pAlg_RemapMergePrm, &gStereoImDims, &gStereoParamsFromSD);

    if(pAlg_CensusPrm)
        ChainsCommon_Stereo_SetCensusAlgPrms (pAlg_CensusPrm, &gStereoImDims,&gStereoParams);

    if(pAlg_DisparityHamDistPrm)
        ChainsCommon_Stereo_SetDisparityAlgPrms (pAlg_DisparityHamDistPrm, &gStereoImDims, &gStereoParams);

    if(pAlg_StereoPostProcessPrm)
        ChainsCommon_Stereo_SetStereoPostProcessPrms (pAlg_StereoPostProcessPrm, &gStereoImDims, &gStereoParams, &gStereoParamsFromSD);
}

/**
 *******************************************************************************
 *
 * \brief   Set global stereo parameters
 *
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetGlobalParams(
        UInt32 remapWidth,
        UInt32 remapHeight,
        UInt32 stereoOutputWidth,
        UInt32 stereoOutputHeight)
{
    gStereoImDims.disparityOutputRoiWidth= stereoOutputWidth;
    gStereoImDims.disparityOutputRoiHeight= stereoOutputHeight;
    gStereoImDims.remapImageWidth= remapWidth;
    gStereoImDims.remapImageHeight= remapHeight;
    ChainsCommon_Stereo_initImageDims(&gStereoImDims, &gStereoParams, &gStereoParamsFromSD);
}


/**
 *******************************************************************************
 *
 * \brief   Set Capture link Parameters for stereo
 *
 * \param pCapturePrm         [IN] capture params
 * \param captureSrc          [IN] capture src
 * \param displayType         [IN] display type
 * \param captureSensorWidth  [IN] sensor output width
 * \param captureSensorHeight [IN] sensor output height
 *
 *******************************************************************************
 */
Void ChainsCommon_TDA2x_Stereo_SetCapturePrms(
        CaptureLink_CreateParams *pCapturePrm,
        Chains_CaptureSrc captureSrc,
        Chains_DisplayType displayType,
        UInt32 captureSensorWidth,
        UInt32 captureSensorHeight
)
{
    UInt32 captureOutWidth = 0, captureOutHeight = 0;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];


    if(displayType==CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        captureOutWidth  = captureSensorWidth;
        captureOutHeight = captureSensorHeight;
    }
    else
        if(displayType==CHAINS_DISPLAY_TYPE_HDMI_1080P)
        {
            captureOutWidth  = captureSensorWidth;
            captureOutHeight = captureSensorHeight;
        }

    if(pCapturePrm)
    {
        ChainsCommon_MultiCam_StartCaptureDevice(
                    CHAINS_CAPTURE_SRC_OV10635,
                    portId,
                    2 // numLvdsCh
                    );

        ChainsCommon_TDA2x_StereoCam_SetCapturePrms(pCapturePrm,
                captureSensorWidth,
                captureSensorHeight,
                captureOutWidth,
                captureOutHeight,
                captureSrc,
                portId,
                2
        );
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set TDA2x stereo Algorithm link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pAlg_RemapMergePrm        [IN] Remap link params
 * \param pAlg_CensusPrm            [IN] Census transform link params
 * \param pAlg_DisparityHamDistPrm  [IN] Hamming distance link params
 * \param pAlg_StereoPostProcessPrm [IN] stereo post processing link params
 *******************************************************************************
 */
Void ChainsCommon_TDA2x_Stereo_AlgoParams(
        AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm,
        AlgorithmLink_CensusCreateParams *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm)
{
    if(pAlg_RemapMergePrm)
        ChainsCommon_TDA2x_Stereo_SetRemapMergeAlgPrms (pAlg_RemapMergePrm, &gStereoImDims,  &gStereoParamsFromSD);

    if(pAlg_CensusPrm)
        ChainsCommon_Stereo_SetCensusAlgPrms (pAlg_CensusPrm, &gStereoImDims,&gStereoParams);

    if(pAlg_DisparityHamDistPrm)
        ChainsCommon_Stereo_SetDisparityAlgPrms (pAlg_DisparityHamDistPrm, &gStereoImDims, &gStereoParams);

    if(pAlg_StereoPostProcessPrm)
        ChainsCommon_Stereo_SetStereoPostProcessPrms (pAlg_StereoPostProcessPrm, &gStereoImDims, &gStereoParams, &gStereoParamsFromSD);
}


/**
 *******************************************************************************
 *
 * \brief   read stereo params from SD card
 *
 *
 * \param sParamsBuffer    [IN] buffer to read stereo parameter
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_Read_Params(Int32 * sParamsBuffer)
{
    Int32 fp, i;
    UInt32 readSize;

    fp = File_open(STEREO_FILENAME_PARAM, "rb");

    if (0 > fp)
    {
        Vps_printf("STEREO_MEDIA: Cannot open file (%s)\n",
                STEREO_FILENAME_PARAM);
    }
    else
    {
        Vps_printf("STEREO_MEDIA: Reading Stereo Params for stereo input...\n");

        ChainsCommon_DeWarp_fileRead(
                            fp,
                            (UInt8*)sParamsBuffer,
                            STEREO_PARAM_SIZE,
                            &readSize);

        // copy params into gStereoParamsFromSD
        gStereoParamsFromSD.numParams = sParamsBuffer[0];

        // numParams should be 0 (i.e. stereo params from SD is not effective) or
        // NUM_SPARAMS_IN_SD (i.e. all params are effective
        UTILS_assert(gStereoParamsFromSD.numParams == 0 || gStereoParamsFromSD.numParams == NUM_SPARAMS_IN_SD);

        if (gStereoParamsFromSD.numParams == NUM_SPARAMS_IN_SD)
        {
            for (i = 0; i < NUM_SPARAMS_IN_SD; i++)
                gStereoParamsFromSD.stereoParamsSD[i] = sParamsBuffer[i+1];
        }
    }

    File_close(fp);
}


/**
 *******************************************************************************
 *
 * \brief   read stereo camera params from SD card
 *
 *
 * \param sCamParamsBuffer    [IN] buffer to read stereo camera parameter
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_Read_CamParams(float * sCamParamsBuffer)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    if(Utils_netIsNetworkEnabled())
    {

        gStereoCamParamsFromSD.stereoCamParamsSD[0] = BASELINE_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[1] = SCALE_FACTOR_X_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[2] = SCALE_FACTOR_Y_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[3] = DIST_CENTER_X_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[4] = DIST_CENTER_Y_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[5] = FOCAL_LENGTH_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[6] = CAL_MAT_0_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[7] = CAL_MAT_1_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[8] = CAL_MAT_2_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[9] = CAL_MAT_3_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[10] = CAL_MAT_4_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[11] = CAL_MAT_5_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[12] = CAL_MAT_6_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[13] = CAL_MAT_7_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[14] = CAL_MAT_8_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[15] = CAL_MAT_9_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[16] = CAL_MAT_10_FIXED;
        gStereoCamParamsFromSD.stereoCamParamsSD[17] = CAL_MAT_11_FIXED;
    }
    else
#endif
    {

        Int32 fp, i;
        UInt32 readSize;

        fp = File_open(STEREO_FILENAME_CAMPARAM, "rb");

        if (0 > fp)
        {
            Vps_printf("STEREO_MEDIA: Cannot open file (%s)\n",
                    STEREO_FILENAME_CAMPARAM);
        }
        else
        {
            Vps_printf("STEREO_MEDIA: Reading Stereo Camera Params for stereo input...\n");

            ChainsCommon_DeWarp_fileRead(
                                fp,
                                (UInt8*)sCamParamsBuffer,
                                STEREO_CAMPARAM_SIZE,
                                &readSize);

            // copy params into gStereoParamsFromSD
            gStereoCamParamsFromSD.numParams = (UInt32) sCamParamsBuffer[0];

            // numParams should be 0 (i.e. stereo params from SD is not effective) or
            // NUM_SPARAMS_IN_SD (i.e. all params are effective
            UTILS_assert(gStereoCamParamsFromSD.numParams == NUM_SCPARAMS_IN_SD);

            if (gStereoCamParamsFromSD.numParams == NUM_SCPARAMS_IN_SD)
            {
                for (i = 0; i < NUM_SCPARAMS_IN_SD; i++)
                    gStereoCamParamsFromSD.stereoCamParamsSD[i] = sCamParamsBuffer[i+1];
            }
        }

        File_close(fp);
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set TDA3x Stereo link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
 */
Void ChainsCommon_TDA3x_Stereo_SetPrms(
        SyncLink_CreateParams *pSync_censusInPrm,
        AlgorithmLink_CensusCreateParams *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm,
        UInt32 remapWidth,
        UInt32 remapHeight,
        UInt32 stereoOutputWidth,
        UInt32 stereoOutputHeight
)
{
    gStereoImDims.disparityOutputRoiWidth= stereoOutputWidth;
    gStereoImDims.disparityOutputRoiHeight= stereoOutputHeight;
    gStereoImDims.remapImageWidth= remapWidth;
    gStereoImDims.remapImageHeight= remapHeight;
    ChainsCommon_Stereo_initImageDims(&gStereoImDims, &gStereoParams, &gStereoParamsFromSD);

    if (pSync_censusInPrm != NULL)
    {
        ChainsCommon_Stereo_SetSyncPrm(
                NULL,
                pSync_censusInPrm,
                2
        );
    }

    if(pAlg_CensusPrm)
        ChainsCommon_Stereo_SetCensusAlgPrms (pAlg_CensusPrm, &gStereoImDims, &gStereoParams);

    if(pAlg_DisparityHamDistPrm)
        ChainsCommon_Stereo_SetDisparityAlgPrms (pAlg_DisparityHamDistPrm, &gStereoImDims, &gStereoParams);

    if(pAlg_StereoPostProcessPrm)
        ChainsCommon_Stereo_SetStereoPostProcessPrms (pAlg_StereoPostProcessPrm, &gStereoImDims, &gStereoParams, &gStereoParamsFromSD);
}


/**
 *******************************************************************************
 *
 * \brief   Set TDA3x Stereo link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_SetCamPrms(AlgorithmLink_StereoAppCreateParams *pAlg_StereoAppPrm)
{
    pAlg_StereoAppPrm->saParams.baseline   = gStereoCamParamsFromSD.stereoCamParamsSD[BASELINE_SD];
    pAlg_StereoAppPrm->saParams.scale_x    = gStereoCamParamsFromSD.stereoCamParamsSD[SCALE_FACTOR_X_SD];
    pAlg_StereoAppPrm->saParams.scale_y    = gStereoCamParamsFromSD.stereoCamParamsSD[SCALE_FACTOR_Y_SD];
    pAlg_StereoAppPrm->saParams.dc_x       = gStereoCamParamsFromSD.stereoCamParamsSD[DIST_CENTER_X_SD];
    pAlg_StereoAppPrm->saParams.dc_y       = gStereoCamParamsFromSD.stereoCamParamsSD[DIST_CENTER_Y_SD];
    pAlg_StereoAppPrm->saParams.ofst_x     = gStereoImDims.origRoiStartX;
    pAlg_StereoAppPrm->saParams.ofst_y     = gStereoImDims.origRoiStartY;
    pAlg_StereoAppPrm->saParams.f          = gStereoCamParamsFromSD.stereoCamParamsSD[FOCAL_LENGTH];

    pAlg_StereoAppPrm->saParams.calmat[0]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_0_SD];
    pAlg_StereoAppPrm->saParams.calmat[1]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_1_SD];
    pAlg_StereoAppPrm->saParams.calmat[2]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_2_SD];
    pAlg_StereoAppPrm->saParams.calmat[3]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_3_SD];
    pAlg_StereoAppPrm->saParams.calmat[4]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_4_SD];
    pAlg_StereoAppPrm->saParams.calmat[5]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_5_SD];
    pAlg_StereoAppPrm->saParams.calmat[6]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_6_SD];
    pAlg_StereoAppPrm->saParams.calmat[7]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_7_SD];
    pAlg_StereoAppPrm->saParams.calmat[8]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_8_SD];
    pAlg_StereoAppPrm->saParams.calmat[9]  = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_9_SD];
    pAlg_StereoAppPrm->saParams.calmat[10] = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_10_SD];
    pAlg_StereoAppPrm->saParams.calmat[11] = gStereoCamParamsFromSD.stereoCamParamsSD[CAL_MAT_11_SD];
}


/**
 *******************************************************************************
 *
 * \brief   Set Auto Remap Alg parameters
 *
 *          It is called in Create function.
 *          In this function alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *
 * \param   pPrm    [IN]    AlgorithmLink_AutoRemapCreateParams
 * \param   chainsCfg    [IN]    Chains_Ctrl
 *
 *******************************************************************************
 */
Void ChainsCommon_Single_Stereo_AutoRemapAlgPrms(AlgorithmLink_AutoRemapCreateParams* pPrm_AutoRemap,
                                                 UInt32 captureSeonsorWidth,
                                                 UInt32 captureSeonsorHeight,
                                                 UInt32 cropCaptureSeonsorWidth,
                                                 UInt32 cropCaptureSeonsorHeight,
                                                 UInt32 remapWidth,
                                                 UInt32 remapHeight,
                                                 UInt32 useRansac,
                                                 UInt32 numRansacIters,
                                                 UInt32 numRansacData,
                                                 float  roiReigionAroundCenter,
                                                 Bool   fishEyeRect,
                                                 Bool   tda2x)
{
    // for tda2x or tda3x?
    pPrm_AutoRemap->autoRemapForTDA2x = tda2x;

    pPrm_AutoRemap->numCameras = 2;

    pPrm_AutoRemap->inFrameWidth = cropCaptureSeonsorWidth;
    pPrm_AutoRemap->inFrameHeight = cropCaptureSeonsorHeight;

    pPrm_AutoRemap->cropOffsetX = (captureSeonsorWidth - cropCaptureSeonsorWidth) / 2;
    pPrm_AutoRemap->cropOffsetY = (captureSeonsorHeight - cropCaptureSeonsorHeight) / 2;

    pPrm_AutoRemap->fishEyeRect = fishEyeRect;

    /*
    pPrm_AutoRemap->lutWidth = gStereoImDims.remapImageWidth;
    pPrm_AutoRemap->lutHeight = gStereoImDims.remapImageHeight;
    */
    pPrm_AutoRemap->lutWidth = remapWidth;
    pPrm_AutoRemap->lutHeight = remapHeight;

    pPrm_AutoRemap->useRansac = useRansac;
    pPrm_AutoRemap->numRansacIters = numRansacIters;
    pPrm_AutoRemap->numRansacData = numRansacData;

    pPrm_AutoRemap->roiRegion = roiReigionAroundCenter;

    pPrm_AutoRemap->sfWidth  = pPrm_AutoRemap->inFrameWidth*1.0f / pPrm_AutoRemap->lutWidth;
    pPrm_AutoRemap->sfHeight = pPrm_AutoRemap->inFrameHeight*1.0f / pPrm_AutoRemap->lutHeight;

    pPrm_AutoRemap->blockWidthBB = REMAP_OUTPUT_BLOCK_WIDTH;
    pPrm_AutoRemap->blockHeightBB = REMAP_OUTPUT_BLOCK_HEIGHT;


    pPrm_AutoRemap->isSrcMapFloat       = 0U;
    pPrm_AutoRemap->srcFormat           = 0U;
    pPrm_AutoRemap->mapQshift           = 2U;
    pPrm_AutoRemap->interpolationLuma   = 1U;
    pPrm_AutoRemap->interpolationChroma = 0U;
    pPrm_AutoRemap->rightShift          = 0U;
    pPrm_AutoRemap->sat_high            = 255U;
    pPrm_AutoRemap->sat_high_set        = 255U;
    pPrm_AutoRemap->sat_low             = 0U;
    pPrm_AutoRemap->sat_low_set         = 0U;
    pPrm_AutoRemap->enableMerge         = 0U;
    pPrm_AutoRemap->dstFormat           = 0U;
    pPrm_AutoRemap->pairIdx             = 0U;


    // Allocation of CalibLUTBuf
    pPrm_AutoRemap->calibLUTBufPrms.isValid = FALSE;
    if (pPrm_AutoRemap->autoRemapForTDA2x)
    {
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTBufSize = STEREO_CALIB_LUT_SIZE;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTHeaderSize = STEREO_CALIB_LUT_HEADER_SIZE;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTQSPIOffset = STEREO_CALIB_LUT_QSPI_OFFSET;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTTagID = STEREO_CALIB_LUT_TAG_ID;
    } else
    {
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTBufSize = STEREO_CALIB_LUT_SIZE;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTHeaderSize = 0;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTQSPIOffset = 0;
        pPrm_AutoRemap->calibLUTBufPrms.calibLUTTagID = 0;
    }


    if (pPrm_AutoRemap->autoRemapForTDA2x)
    {
        // TDA2x
        pPrm_AutoRemap->calibLUTBufPrms.pCalibLUTBuf
                = Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        SystemUtils_align(pPrm_AutoRemap->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE), /* Padd with QSPI_READ_WRITE_SIZE as  System_qspiReadSector writes in granularity of QSPI_READ_WRITE_SIZE bytes*/
                        32);
        UTILS_assert(pPrm_AutoRemap->calibLUTBufPrms.pCalibLUTBuf != NULL);
    } else
    {
        // TDA3x
        pPrm_AutoRemap->calibLUTBufPrms.pCalibLUTBuf
                = Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        SystemUtils_align(pPrm_AutoRemap->calibLUTBufPrms.calibLUTBufSize, 128U),
                        32);
        UTILS_assert(pPrm_AutoRemap->calibLUTBufPrms.pCalibLUTBuf != NULL);
    }


    // For feature points plot
    pPrm_AutoRemap->featureBufPrms.featurePtsNum = AUTO_REMAP_FEATURE_PTS;
    pPrm_AutoRemap->featureBufPrms.featureHeaderSize = AUTO_REMAP_FEAUTRE_HDR_SIZE;
    pPrm_AutoRemap->featureBufPrms.featureBufSize = AUTO_REMAP_FEATURE_BUF_SIZE;
    pPrm_AutoRemap->featureBufPrms.pFeatureBuf
            = Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    SystemUtils_align(pPrm_AutoRemap->featureBufPrms.featureBufSize, 128),
                    32);

    UTILS_assert(pPrm_AutoRemap->featureBufPrms.pFeatureBuf != NULL);

}


char ChainsCommon_Stereo_AutoRemap_Menu()
{
   Vps_printf(gChains_stereo_autoremap_Menu);

   return Chains_readChar();
}

/**
 *******************************************************************************
 *
 * \brief   Delete
 *
 *
 *
 * \param pAlg_RemapMergePrm, Remap alg plugin create params. These contain the allocated
 * LUT param
 *
 *******************************************************************************
 */
Void ChainsCommon_Stereo_Delete(
        AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm)
{
    if(pAlg_RemapMergePrm->calibLUTBufPrms.isValid	)
    {
        Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pAlg_RemapMergePrm->calibLUTBufPrms.pCalibLUTBuf,
                pAlg_RemapMergePrm->calibLUTBufPrms.calibLUTBufSize);
    }
}


Void ChainsCommon_Stereo_AutoRemap_Delete(
            AlgorithmLink_AutoRemapCreateParams *pAlg_AutoRemapPrm)
{
    Vps_printf("pAlg_AutoRemapPrm Header:%x\n", pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf[0]);


    if (pAlg_AutoRemapPrm->autoRemapForTDA2x)
    {
        // write QSPI
        Vps_printf("QSPI WRITE while delete ....\n");
        Vps_printf("===========address autoRemapCreate:%x, %x, size:%d\n",
                pAlg_AutoRemapPrm, pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf, pAlg_AutoRemapPrm->calibLUTBufPrms.calibLUTBufSize);


        Vps_printf("remapTable:%d, %d, %d, %d\n",pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf[16], pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf[17],
                pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf[18], pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf[19]);

        System_qspiWriteSector(STEREO_CALIB_LUT_QSPI_OFFSET,
                                (UInt32) pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf,
                                SystemUtils_align(pAlg_AutoRemapPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE));
    } else {


    }


    Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pAlg_AutoRemapPrm->calibLUTBufPrms.pCalibLUTBuf,
            pAlg_AutoRemapPrm->calibLUTBufPrms.calibLUTBufSize);


    Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pAlg_AutoRemapPrm->featureBufPrms.pFeatureBuf,
            pAlg_AutoRemapPrm->featureBufPrms.featureBufSize);

}




