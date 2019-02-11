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
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/include/chains_common_surround_view.h>
#include <src/include/chains_lens.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
ChainsCommon_SurroundView_GACalibrationInfo gChains_surroundViewCalibInfo;

/**
 *******************************************************************************
 * \brief Menu for Camera position Calibration settings.
 *******************************************************************************
 */
char gChainsCommon_SurroundView_MenuCalibration[] = {
    "\r\n "
    "\r\n ================================================"
    "\r\n Chains Run-time Calibration Menu"
    "\r\n ================================================"
    "\r\n "
    "\r\n 1: Write back SRV Calibration LUTs to Flash/File "
    "\r\n "
    "\r\n 2: Erase/Delete SRV Calibration LUTs from Flash/File"
    "\r\n "
    "\r\n 3: Go to previous menu"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Set Synthesis Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetSynthParams(
                                    AlgorithmLink_SynthesisCreateParams *pPrm,
                                    UInt16 svInWidth,
                                    UInt16 svInHeight,
                                    UInt16 svOutWidth,
                                    UInt16 svOutHeight,
                                    UInt16 svNumViews,
                                    Int16  svCarBoxWidth,
                                    Int16  svCarBoxHeight,
                                    AlgorithmLink_SrvOutputModes svOutputMode,
                                    Bool enableCarOverlayInAlg)
{
    ChainsCommon_SurroundView_GACalibrationInfo *pGaCalibInfo = \
                                                &gChains_surroundViewCalibInfo;
    pPrm->useSuppliedLUT = 0;
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_SYNTHESIS;
    pPrm->maxOutputWidth = svOutWidth;
    pPrm->maxOutputHeight = svOutHeight;
    pPrm->maxInputWidth = svInWidth;
    pPrm->maxInputHeight = svInHeight;
    pPrm->numViews = svNumViews;
    pPrm->subsampleratio = 8;
    pPrm->carBoxWidth = svCarBoxWidth;
    pPrm->carBoxHeight = svCarBoxHeight;
    pPrm->numOutputFrames = 5;
    pPrm->numPhotometricStatisticsTables = 5;
    pPrm->numSgxBlendLUTables = 1;
    pPrm->synthesisMode = ALGORITHM_LINK_ALG_SIMPLESYNTHESIS;
    pPrm->svOutputMode = svOutputMode;
    pPrm->enableCarOverlayInAlg = enableCarOverlayInAlg;
    pPrm->synthLUTSize = (svOutHeight * svOutWidth * 4U);
    pPrm->synthLUTPtr = pGaCalibInfo->synthLUTPtr;
    pPrm->saveCalculatedLUT = 0;
    pPrm->earlyCreate = FALSE;
    pPrm->useUserBlendTable3DLDC = FALSE;
    pPrm->useStaticGALut = FALSE;
}

/**
 *******************************************************************************
 *
 * \brief   Set Adaptive Bowl Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetAdaptiveBowlParams(
                            AlgorithmLink_AdaptiveBowlCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight)
{
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_ADAPTIVEBOWL;
    pPrm->maxOutputWidth = svOutWidth;
    pPrm->maxOutputHeight = svOutHeight;
    pPrm->maxInputWidth = svInWidth;
    pPrm->maxInputHeight = svInHeight;
    pPrm->numViews = svNumViews;
    pPrm->carBoxWidth = svCarBoxWidth;
    pPrm->carBoxHeight = svCarBoxHeight;

    pPrm->numOutputTables = 3;
    pPrm->ignoreFirstNFrames = 0U;
    pPrm->defaultFocalLength = 455U;
    pPrm->pLensPrm = (Void*)Chains_lens_getLensPrm();
    pPrm->pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();

    /* Default sizes for XY offsets */
    pPrm->offsetXleft = -400;
    pPrm->offsetXright = 400;
    pPrm->offsetYfront = -450;
    pPrm->offsetYback = 450;
}

/**
 *******************************************************************************
 *
 * \brief   Set Geometric Alignment Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetGAlignParams(
                            AlgorithmLink_GAlignCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight,
                            AlgorithmLink_SrvOutputModes svOutputMode)
{
    ChainsCommon_SurroundView_GACalibrationInfo *pGaCalibInfo = \
                                                &gChains_surroundViewCalibInfo;

    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_GALIGNMENT;
    pPrm->maxOutputWidth = svOutWidth;
    pPrm->maxOutputHeight = svOutHeight;
    pPrm->maxInputWidth = svInWidth;
    pPrm->maxInputHeight = svInHeight;
    pPrm->numViews = svNumViews;
    pPrm->carBoxWidth = svCarBoxWidth;
    pPrm->carBoxHeight = svCarBoxHeight;
    pPrm->ldcLutOnlyMode = FALSE;
    pPrm->bypass_GA = FALSE;

    pPrm->numOutputTables = 3;
    pPrm->enablePixelsPerCm = 0;
    pPrm->svOutputMode = svOutputMode;
    pPrm->ignoreFirstNFrames = 2U;
    pPrm->defaultFocalLength = 455U;
    pPrm->pLensPrm = (Void*)Chains_lens_getLensPrm();
    pPrm->pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();

    UTILS_assert(NULL != pGaCalibInfo->gaLUTDDRPtr);
    UTILS_assert(NULL != pGaCalibInfo->persMatDDRPtr);

    pPrm->calParams.calMode = pGaCalibInfo->calMode;
    pPrm->calParams.gaLUTDDRPtr = \
            (pGaCalibInfo->gaLUTDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);
    pPrm->calParams.persMatDDRPtr = \
            (pGaCalibInfo->persMatDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);

}

/**
 *******************************************************************************
 *
 * \brief   Set Geometric Alignment 3D Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetGAlign3DParams(
                            AlgorithmLink_GAlign3DCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight,
                            AlgorithmLink_SrvOutputModes svOutputMode)
{
    ChainsCommon_SurroundView_GACalibrationInfo *pGaCalibInfo = \
                                                &gChains_surroundViewCalibInfo;

    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_GALIGNMENT_3D;
    pPrm->maxOutputWidth = svOutWidth;
    pPrm->maxOutputHeight = svOutHeight;
    pPrm->maxInputWidth = svInWidth;
    pPrm->maxInputHeight = svInHeight;
    pPrm->numViews = svNumViews;
    pPrm->carBoxWidth = svCarBoxWidth;
    pPrm->carBoxHeight = svCarBoxHeight;

    pPrm->numOutputTables = 3;
    pPrm->enablePixelsPerCm = 0;
    pPrm->svOutputMode = svOutputMode;
    pPrm->calmatInputBufferConnected = 0;
    pPrm->ignoreFirstNFrames = 0U;
    pPrm->defaultFocalLength = 455U;
    pPrm->pLensPrm = (Void*)Chains_lens_getLensPrm();
    pPrm->pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();

    UTILS_assert(NULL != pGaCalibInfo->gaLUTDDRPtr);
    UTILS_assert(NULL != pGaCalibInfo->persMatDDRPtr);
    UTILS_assert(NULL != pGaCalibInfo->autoPersMatDDRPtr);

    pPrm->calParams.calMode = \
                (AlgorithmLink_GAlign3DCalibrationMode)pGaCalibInfo->calMode;
    pPrm->calParams.gaLUTDDRPtr = \
            (pGaCalibInfo->gaLUTDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);
    pPrm->calParams.persMatDDRPtr = \
            (pGaCalibInfo->persMatDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);
    pPrm->calParams.autoPersMatDDRPtr = \
            (pGaCalibInfo->autoPersMatDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);
}


/**
 *******************************************************************************
 *
 * \brief   Set Auto Chart Detect Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetPAlignParams(
                                    AlgorithmLink_PAlignCreateParams *pPrm,
                                    UInt16 svInWidth,
                                    UInt16 svInHeight,
                                    UInt16 svOutWidth,
                                    UInt16 svOutHeight,
                                    UInt16 svNumViews,
                                    Int16  svCarBoxWidth,
                                    Int16  svCarBoxHeight,
                                    AlgorithmLink_SrvOutputModes svOutputMode)
{
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_PALIGNMENT;
    pPrm->maxOutputWidth = svOutWidth;
    pPrm->maxOutputHeight = svOutHeight;
    pPrm->maxInputWidth = svInWidth;
    pPrm->maxInputHeight = svInHeight;
    pPrm->numViews = svNumViews;
    pPrm->carBoxWidth = svCarBoxWidth;
    pPrm->carBoxHeight = svCarBoxHeight;
    pPrm->numOutputTables = 5;
    pPrm->dataFormat = SYSTEM_DF_YUV420SP_UV;
    pPrm->svOutputMode = svOutputMode;
}

/**
 *******************************************************************************
 *
 * \brief   Set Auto Chart Detect Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetACDetectParams(
                            AlgorithmLink_ACDetectCreateParams *pPrm)
{
    ChainsCommon_SurroundView_GACalibrationInfo *pGaCalibInfo = \
                                                &gChains_surroundViewCalibInfo;

    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_AUTO_CHART_DETECT;
    pPrm->maxInputWidth = SRV_LVDS_CAPTURE_WIDTH;
    pPrm->maxInputHeight = SRV_LVDS_CAPTURE_HEIGHT;
    pPrm->numViews = SRV_NUM_VIEWS;
    pPrm->numOutput = 1;
    pPrm->ignoreFirstNFrames = 2U;
    pPrm->defaultFocalLength = 455U;
    pPrm->pLensPrm = (Void*)Chains_lens_getLensPrm();

    UTILS_assert(NULL != pGaCalibInfo->featurePtDDRPtr);
    pPrm->acDetectParams.acDetectMode = ALGLINK_ACDETECT_MODE_ENABLE;

    pPrm->acDetectParams.featurePtDDRPtr =
    (void *)(pGaCalibInfo->featurePtDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);

}

/**
 *******************************************************************************
 *
 * \brief   Set Pose Estimate Create Parameters
 *
 * \param   syncMode [IN]    1 - Tight Sync, 0 - Loose Sync
 *          pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetPEstimateParams(
                            AlgorithmLink_PEstimateCreateParams *pPrm)
{
    ChainsCommon_SurroundView_GACalibrationInfo *pGaCalibInfo = \
                                                &gChains_surroundViewCalibInfo;

    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_POSE_ESTIMATE;
    pPrm->maxInputWidth = SRV_LVDS_CAPTURE_WIDTH;
    pPrm->maxInputHeight = SRV_LVDS_CAPTURE_HEIGHT;
    pPrm->numViews = SRV_NUM_VIEWS;
    pPrm->numOutput = 1;
    pPrm->defaultFocalLength = 455U;
    pPrm->pLensPrm = (Void*)Chains_lens_getLensPrm();

    UTILS_assert(NULL != pGaCalibInfo->persMatDDRPtr);
    UTILS_assert(NULL != pGaCalibInfo->featurePtDDRPtr);

    pPrm->pEstimateParams.pEstimateMode = ALGLINK_PESTIMATE_MODE_ENABLE;
    pPrm->pEstimateParams.pEstCalMatDRPtr =
    (void *)(pGaCalibInfo->persMatDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);
    pPrm->pEstimateParams.featurePtDDRPtr =
    (void *)(pGaCalibInfo->featurePtDDRPtr + GA_MAGIC_PATTERN_SIZE_IN_BYTES);

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
Void ChainsCommon_SurroundView_SetSyncPrm(
                                    SyncLink_CreateParams *pPrm,
                                    UInt32 numLvdsCh,
                                    UInt32 syncMode)
{
    if(syncMode == 1)
    {
        pPrm->syncDelta = SRV_TIGHT_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = SRV_TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC;
    }
    else
    {
        pPrm->syncDelta = SRV_LOOSE_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = SRV_LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC;
    }
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
Void ChainsCommon_SurroundView_SetSyncFcPrm(
                    SyncLink_CreateParams *pPrm)
{
    pPrm->syncDelta = 16;
    pPrm->syncThreshold = 0xFFFF;
}

#if !defined(LINUX_BUILD) && !defined(QNX_BUILD)
/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetDisplayPrm(
                                    DisplayLink_CreateParams *pSvDisplay,
                                    DisplayLink_CreateParams *pSvOrgDisplay,
                                    DisplayLink_CreateParams *pFrontCamDisplay,
                                    DisplayLink_CreateParams *pGrpxDisplay,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight)
{
    /*
     *  Default SRV Output resolutions:
     */
    #define SRV_OUTPUT_WIDTH_TDA3XX                 (640U)
    #define SRV_OUTPUT_HEIGHT_TDA3XX                (760U)
    #define SRV_OUTPUT_POSX_TDA3XX                  (1024U - 640U)
    #define SRV_OUTPUT_POSY_TDA3XX                  (4U) /* (768-760)/2 */

    #define SRV_OUTPUT_WIDTH_720P_RES_TDA3XX        (1280U)
    #define SRV_OUTPUT_HEIGHT_720P_RES_TDA3XX       (720U)
    #define SRV_OUTPUT_POSX_720P_RES_TDA3XX         (0U)
    #define SRV_OUTPUT_POSY_720P_RES_TDA3XX         (0U)

    #define SRV_OUTPUT_WIDTH_TDA2XX                 (880U)
    #define SRV_OUTPUT_HEIGHT_TDA2XX                (1080U)
    #define SRV_OUTPUT_POSX_TDA2XX                  (25 + 320 + 10)
    #define SRV_OUTPUT_POSY_TDA2XX                  (0U)

    float displayWidthScale = 1;
    float displayHeightScale = 1;
    UInt32 svOutWidth, svOutHeight;
    UInt32 svPosX, svPosY;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        displayWidthScale = (1024.0)/displayWidth;
        displayHeightScale = (768.0)/displayHeight;
        svOutWidth = SRV_OUTPUT_WIDTH_TDA3XX;
        svOutHeight = SRV_OUTPUT_HEIGHT_TDA3XX;
        svPosX = SRV_OUTPUT_POSX_TDA3XX;
        svPosY = SRV_OUTPUT_POSY_TDA3XX;
        if ((1280U == displayWidth) && (720U == displayHeight))
        {
            displayWidthScale = 1U;
            displayHeightScale = 1U;
            svOutWidth = SRV_OUTPUT_WIDTH_720P_RES_TDA3XX;
            svOutHeight = SRV_OUTPUT_HEIGHT_720P_RES_TDA3XX;
            svPosX = SRV_OUTPUT_POSX_720P_RES_TDA3XX;
            svPosY = SRV_OUTPUT_POSY_720P_RES_TDA3XX;
        }
        if ((1920U == displayWidth) && (1080U == displayHeight))
        {
            displayWidthScale = 1U;
            displayHeightScale = (1088.0)/displayHeight;
            svOutWidth = 896;
            svOutHeight = 1088;
            svPosX = 512;
            svPosY = 0;
        }
    }
    else
    {
        displayWidthScale = (1920.0)/displayWidth;
        displayHeightScale = (1080.0)/displayHeight;
        svOutWidth = SRV_OUTPUT_WIDTH_TDA2XX;
        svOutHeight = SRV_OUTPUT_HEIGHT_TDA2XX;
        svPosX = SRV_OUTPUT_POSX_TDA2XX;
        svPosY = SRV_OUTPUT_POSY_TDA2XX;
    }

    if(pSvDisplay)
    {
        pSvDisplay->rtParams.tarWidth = (float)svOutWidth / displayWidthScale;
        pSvDisplay->rtParams.tarHeight = \
                                        (float)svOutHeight / displayHeightScale;
        pSvDisplay->rtParams.posX = (float)svPosX / displayWidthScale;
        pSvDisplay->rtParams.posY = (float)svPosY / displayHeightScale;
        pSvDisplay->displayId = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pSvOrgDisplay)
    {
        pSvOrgDisplay->rtParams.tarWidth = \
                                (float)SVORG_MOSAIC_WIDTH / displayWidthScale;
        pSvOrgDisplay->rtParams.tarHeight = \
                                (float)SVORG_MOSAIC_HEIGHT / displayHeightScale;
        pSvOrgDisplay->rtParams.posX = \
                                (float)SVORG_MOSAIC_POSX / displayWidthScale;
        pSvOrgDisplay->rtParams.posY = \
                                (float)SVORG_MOSAIC_POSY / displayHeightScale;
        pSvOrgDisplay->displayId = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pFrontCamDisplay)
    {
        pFrontCamDisplay->rtParams.tarWidth = \
                            (float)FRONTCAM_MOSAIC_WIDTH / displayWidthScale;
        pFrontCamDisplay->rtParams.tarHeight  = \
                            (float)FRONTCAM_MOSAIC_HEIGHT / displayHeightScale;
        pFrontCamDisplay->rtParams.posX = \
                            (float)FRONTCAM_MOSAIC_POSX / displayWidthScale;
        pFrontCamDisplay->rtParams.posY = \
                            (float)FRONTCAM_MOSAIC_POSY / displayHeightScale;
        pFrontCamDisplay->displayId = DISPLAY_LINK_INST_DSS_VID3;
    }

    if(pGrpxDisplay)
    {
        pGrpxDisplay->rtParams.tarWidth = displayWidth;
        pGrpxDisplay->rtParams.tarHeight = displayHeight;
        pGrpxDisplay->rtParams.posX = 0;
        pGrpxDisplay->rtParams.posY = 0;
        pGrpxDisplay->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}
#endif

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
Void ChainsCommon_SurroundView_SetVpePrm(
                                    VpeLink_CreateParams *pSvOrgVpe,
                                    VpeLink_CreateParams *pFrontCamVpe,
                                    UInt32 frontCamAlgOutWidth,
                                    UInt32 frontCamAlgOutHeight)
{
    VpeLink_CreateParams *pPrm;
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    if(pSvOrgVpe)
    {
        pPrm = pSvOrgVpe;
        pPrm->enableOut[0] = TRUE;

        for (chId = 0; chId < 4; chId++)
        {
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh =
                                     VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

            chPrms->outParams[outId].width = SVORG_SCALED_WIDTH;
            chPrms->outParams[outId].height = SVORG_SCALED_HEIGHT;
            chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

            chPrms->scCfg.bypass       = FALSE;
            chPrms->scCfg.nonLinear    = FALSE;
            chPrms->scCfg.stripSize    = 0;

            chPrms->scCropCfg.cropStartX = 0;
            chPrms->scCropCfg.cropStartY = 0;
            chPrms->scCropCfg.cropWidth = SRV_LVDS_CAPTURE_WIDTH;
            chPrms->scCropCfg.cropHeight = SRV_LVDS_CAPTURE_HEIGHT;
        }
    }
    if(pFrontCamVpe)
    {
        pPrm = pFrontCamVpe;
        pPrm->enableOut[0] = TRUE;

        for (chId = 0; chId < 2; chId++)
        {
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh =
                                     VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

            chPrms->outParams[outId].width = FRONTCAM_SCALED_WIDTH;
            chPrms->outParams[outId].height = FRONTCAM_SCALED_HEIGHT;
            chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

            chPrms->scCfg.bypass       = FALSE;
            chPrms->scCfg.nonLinear    = FALSE;
            chPrms->scCfg.stripSize    = 0;


            chPrms->scCropCfg.cropStartX = 0;
            chPrms->scCropCfg.cropStartY = 0;
            chPrms->scCropCfg.cropWidth = SRV_LVDS_CAPTURE_WIDTH;
            chPrms->scCropCfg.cropHeight = SRV_LVDS_CAPTURE_HEIGHT;

            if(chId==1)
            {
                /* CH1 is front cam algorithm output,
                 * its size depends on the algo that is used
                 *
                 * For Edge detect, output size is sensor W/2 x H/2
                 * For Dense Optical flow, output size is sensor W x H
                 *   aligned to algo specific values
                 */
                chPrms->scCropCfg.cropWidth = frontCamAlgOutWidth;
                chPrms->scCropCfg.cropHeight = frontCamAlgOutHeight;
            }
        }
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set Select Link Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetSelectPrm(SelectLink_CreateParams *pPrm)
{
    pPrm->numOutQue = 2;

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 4;
    pPrm->outQueChInfo[0].inChNum[0] = 0;
    pPrm->outQueChInfo[0].inChNum[1] = 1;
    pPrm->outQueChInfo[0].inChNum[2] = 2;
    pPrm->outQueChInfo[0].inChNum[3] = 3;

    pPrm->outQueChInfo[1].outQueId   = 1;
    pPrm->outQueChInfo[1].numOutCh   = 1;
    pPrm->outQueChInfo[1].inChNum[0] = 4;
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
Void ChainsCommon_SurroundView_SetAlgDmaSwMsPrm(
                                        AlgorithmLink_DmaSwMsCreateParams *pPrm,
                                        UInt32 numLvdsCh,
                                        UInt32 channelWidth,
                                        UInt32 channelHeight,
                                        UInt32 layoutType,
                                        UInt32 channelSpacingHor,
                                        UInt32 channelSpacingVer)
{
    UInt32 algId, winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;
    UInt32 secondRowFlag, numLvdsChBy2;

    useLocalEdma = FALSE;
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->baseClassCreate.algId   = algId;
    pPrm->numOutBuf               = 4;
    pPrm->useLocalEdma            = useLocalEdma;
    pPrm->initLayoutParams.numWin = numLvdsCh;

    switch(layoutType)
    {
        default:
        case 0:
             /*
              * vertical strip
              */
            pPrm->maxOutBufWidth     = channelWidth;
            pPrm->maxOutBufHeight    = (channelHeight*(numLvdsCh)) +
                                       (channelSpacingVer*(numLvdsCh-1));

            for(winId = 0; winId < pPrm->initLayoutParams.numWin; winId++)
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

            break;
        case 1:
             /*
              * Horizontal strip
              */
            pPrm->maxOutBufWidth     = (channelWidth*(numLvdsCh)) +
                                       (channelSpacingHor*(numLvdsCh-1));
            pPrm->maxOutBufHeight    = channelHeight;

            for(winId = 0; winId < pPrm->initLayoutParams.numWin; winId++)
            {
                pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
                pWinInfo->chId = winId;
                pWinInfo->inStartX = 0;
                pWinInfo->inStartY = 0;
                pWinInfo->width    = channelWidth;
                pWinInfo->height   = channelHeight;
                pWinInfo->outStartX = winId*(channelWidth+channelSpacingHor);
                pWinInfo->outStartY = 0;
             }

            break;

        case 2:
             /*
              * Two Horizontal strips
              */
            numLvdsChBy2 = (numLvdsCh+1) / 2;
            pPrm->maxOutBufWidth     = (channelWidth*(numLvdsChBy2)) +
                                       (channelSpacingHor*(numLvdsChBy2-1));
            pPrm->maxOutBufHeight    = (channelHeight*2) + channelSpacingVer;

            for(winId = 0; winId < pPrm->initLayoutParams.numWin; winId++)
            {
                pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
                pWinInfo->chId = winId;
                pWinInfo->inStartX = 0;
                pWinInfo->inStartY = 0;
                pWinInfo->width    = channelWidth;
                pWinInfo->height   = channelHeight;
                secondRowFlag = ( winId>= numLvdsChBy2 ? 1 : 0);
                pWinInfo->outStartX = (winId % numLvdsChBy2) * \
                                            (channelWidth+channelSpacingHor);
                pWinInfo->outStartY = secondRowFlag * \
                                            (channelHeight+channelSpacingVer);
             }

            break;

    }

    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;
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
Void ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                           GrpxSrcLink_CreateParams *pPrm,
                                           UInt32 displayWidth,
                                           UInt32 displayHeight,
                                           AlgorithmLink_SrvOutputModes srvMode)
{
    pPrm->disablePreview = FALSE;

#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    pPrm->grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pPrm->grpxBufInfo.height = displayHeight;
    pPrm->grpxBufInfo.width = displayWidth;

    pPrm->surroundViewStandaloneLayoutEnable = TRUE;
    pPrm->statsDisplayEnable = TRUE;
    pPrm->enableJeepOverlay = FALSE;
#else
    pPrm->grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pPrm->grpxBufInfo.height = displayHeight;
    pPrm->grpxBufInfo.width = displayWidth;

    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pPrm->tda3xxSvFsRotLayoutEnable = FALSE;
        pPrm->tda3xx3DSvLayoutEnable = FALSE;

        pPrm->statsDisplayEnable = TRUE;
        pPrm->enableJeepOverlay = TRUE;

        if ((ALGORITHM_LINK_SRV_OUTPUT_2D == srvMode) ||
            (ALGORITHM_LINK_SRV_OUTPUT_2D_LDC == srvMode))
        {
            pPrm->tda3xxSvFsRotLayoutEnable = TRUE;
        }
        else if (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC == srvMode)
        {
            pPrm->tda3xx3DSvLayoutEnable = TRUE;

            if ((SYSTEM_STD_WXGA_30 != pPrm->tda3x3DSvSrcResolution) &&
                (SYSTEM_STD_720P_60 != pPrm->tda3x3DSvSrcResolution))
            {
                UTILS_assert(FALSE);
            }
        }
        else
        {
            UTILS_assert(FALSE);
        }
    }
    else
    {
        pPrm->surroundViewEdgeDetectLayoutEnable = TRUE;
        pPrm->statsDisplayEnable = TRUE;
        pPrm->enableJeepOverlay = TRUE;
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Set PD draw parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetObjectDrawPrms(
                                   AlgorithmLink_ObjectDrawCreateParams *pPrm,
                                   UInt32 width,
                                   UInt32 height)
{
    UTILS_assert(pPrm != NULL);

    pPrm->imgFrameWidth    = width;
    pPrm->imgFrameHeight   = height;
    pPrm->numOutBuffers = SRV_FEATUREPLANE_NUM_OUT_BUF;
    pPrm->objectRectThickness = 3;
}


/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Compute Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetFeaturePlaneComputeAlgPrms(
                       AlgorithmLink_FeaturePlaneComputationCreateParams *pPrm,
                       UInt32 width,
                       UInt32 height)
{
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
    pPrm->numOutBuffers  = SRV_FEATUREPLANE_NUM_OUT_BUF;
}


/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Classify Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetObjectDetectPrm(
                               AlgorithmLink_ObjectDetectionCreateParams *pPrm,
                               UInt32 width,
                               UInt32 height)
{
    pPrm->numOutBuffers  = SRV_FEATUREPLANE_NUM_OUT_BUF;
    pPrm->enablePD       = TRUE;
    pPrm->enableTSR      = TRUE;
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
}


/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetFCVpePrm(
                                    VpeLink_CreateParams *pPrm,
                                    UInt32 outWidth,
                                    UInt32 outHeight,
                                    UInt32 srcWidth,
                                    UInt32 srcHeight,
                                    System_VideoDataFormat dataFormat)
{
    pPrm->enableOut[0] = TRUE;

    pPrm->chParams[0].outParams[0].width = SystemUtils_floor(outWidth, 4);
    pPrm->chParams[0].outParams[0].height = SystemUtils_floor(outHeight, 2);
    pPrm->chParams[0].outParams[0].numBufsPerCh = 3;

    pPrm->chParams[0].scCropCfg.cropStartX = 0;
    pPrm->chParams[0].scCropCfg.cropStartY = 0;
    pPrm->chParams[0].scCropCfg.cropWidth  = srcWidth;
    pPrm->chParams[0].scCropCfg.cropHeight = srcHeight;

    pPrm->chParams[0].outParams[0].dataFormat = dataFormat;
    pPrm->chParams[0].outParams[0].numBufsPerCh = 8;
}


/**
 *******************************************************************************
 *
 * \brief   Set Algorithm related parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_SetLaneDetectPrm(
                                AlgorithmLink_LaneDetectCreateParams *pAlgPrm,
                                AlgorithmLink_ObjectDrawCreateParams *pDrawPrm,
                                UInt32 startX,
                                UInt32 startY,
                                UInt32 width,
                                UInt32 height)
{
    pAlgPrm->imgFrameStartX = startX;
    pAlgPrm->imgFrameStartY = startY;
    pAlgPrm->imgFrameWidth  = width;
    pAlgPrm->imgFrameHeight = height;

    pAlgPrm->roiStartX      = 32 - LD_FILTER_TAP_X;
    pAlgPrm->roiStartY      = 120;
    pAlgPrm->roiWidth       = 576 + 2*LD_FILTER_TAP_X;
    pAlgPrm->roiHeight      = 240;

    pDrawPrm->imgFrameStartX = startX;
    pDrawPrm->imgFrameStartY = startY;
    pDrawPrm->imgFrameWidth  = width;
    pDrawPrm->imgFrameHeight  = height;
    pDrawPrm->laneDrawLines = TRUE;
    pDrawPrm->numDrawAlg = 1;
    pDrawPrm->drawAlgId[0] = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_LD;

    pAlgPrm->cannyHighThresh        = 30;
    pAlgPrm->cannyLowThresh         = 20;
    pAlgPrm->houghNmsThresh         = 20;
    pAlgPrm->startThetaLeft         = 100;
    pAlgPrm->endThetaLeft           = 150;
    pAlgPrm->startThetaRight        = 10;
    pAlgPrm->endThetaRight          = 60;
    pAlgPrm->thetaStepSize          = 1;
}

/**
 *******************************************************************************
 *
 * \brief   Set Algorithm related parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_GetSrvOutputResolution(
                        AlgorithmLink_SrvOutputModes svOutputMode,
                        UInt32 *pSvOutWidth,
                        UInt32 *pSvOutHeight)
{
#ifdef TDA2XX_FAMILY_BUILD
    #ifdef TDA2PX_BUILD
        /* TDA2PX supports the following SRV modes */
        if(ALGORITHM_LINK_SRV_OUTPUT_2D == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_2D;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_2D;
        }
        else if(ALGORITHM_LINK_SRV_OUTPUT_3D == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA2X_3D;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA2X_3D;
        }
        else if(ALGORITHM_LINK_SRV_OUTPUT_2D_LDC == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_2D_LDC;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_2D_LDC;
        }
        else if(ALGORITHM_LINK_SRV_OUTPUT_3D_LDC == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_3D_LDC;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC;
        }
    #else
        /* TDA2XX and TDA2EX supports the following SRV modes */
        if(ALGORITHM_LINK_SRV_OUTPUT_2D == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA2X_2D;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA2X_2D;
        }
        else if(ALGORITHM_LINK_SRV_OUTPUT_3D == svOutputMode)
        {
            *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA2X_3D;
            *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA2X_3D;
        }
    #endif
#elif defined(TDA3XX_FAMILY_BUILD)
    /* TDA3XX supports the following SRV modes */
    if(ALGORITHM_LINK_SRV_OUTPUT_2D == svOutputMode)
    {
        *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_2D;
        *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_2D;
    }
    else if(ALGORITHM_LINK_SRV_OUTPUT_2D_LDC == svOutputMode)
    {
        *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_2D_LDC;
        *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_2D_LDC;
    }
    else if(ALGORITHM_LINK_SRV_OUTPUT_3D_LDC == svOutputMode)
    {
        *pSvOutWidth = SRV_OUTPUT_WIDTH_TDA3X_3D_LDC;
        *pSvOutHeight = SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC;
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Function to allocate intermediate GA OUTPUT LUT and
 *          Perspective Matrix tables.  QSPI flash read/write
 *          is from/to this memory.
 *          Also create as task to update the peraMat table into
 *          QSPI flash after 5 min
 *
 * \param   gaCalibInfo    [IN]  Chain_Common_SRV_GACalibrationInfo
 *
 *******************************************************************************
*/
static Int32 readPersMatFile(Void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, fp;
    UInt32 readSize;
    ChainsCommon_SurroundView_GACalibrationInfo *gaCalibInfo;
    UInt32 *ptr;

    gaCalibInfo = &gChains_surroundViewCalibInfo;

    fp = ChainsCommon_Osal_fileOpen(SRV_PERSMAT_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
    if (0 <= fp)
    {
        Vps_printf(" SRV: File read (%s) ... \n",SRV_PERSMAT_FILE);

        ChainsCommon_Osal_fileRead(
                            fp,
                            (Ptr)((UInt32)gaCalibInfo->persMatDDRPtr + \
                                GA_MAGIC_PATTERN_SIZE_IN_BYTES),
                            GA_PERSPECTIVE_MATRIX_SIZE,
                            &readSize);

        if (0 >= readSize)
        {
            Vps_printf(" SRV: File read (%s) failed\n",SRV_PERSMAT_FILE);
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
        else
        {
            ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                            (UInt32)gaCalibInfo->persMatDDRPtr);
            *ptr = GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE;

            Vps_printf(" SRV: File read (%s:%d bytes) DONE \n",\
                                                    SRV_PERSMAT_FILE, readSize);
        }

        ChainsCommon_Osal_fileClose (fp);
    }
    else
    {
        Vps_printf(" SRV: File open (%s) failed\n",SRV_PERSMAT_FILE);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}
/**
 *******************************************************************************
 *
 * \brief   Function to allocate intermediate GA OUTPUT LUT and
 *          Perspective Matrix tables.  QSPI flash read/write
 *          is from/to this memory.
 *          Also create as task to update the peraMat table into
 *          QSPI flash after 5 min
 *
 * \param   gaCalibInfo    [IN]  Chain_Common_SRV_GACalibrationInfo
 *
 *******************************************************************************
*/
static Void ChainsCommon_SurroundView_allocateGATbl(
                    ChainsCommon_SurroundView_GACalibrationInfo *gaCalibInfo)
{
    #define SRV_OUTPUT_MAX_WIDTH        (1080U)
    #define SRV_OUTPUT_MAX_HEIGHT       (1080U)

    UInt32 *ptr;
    UInt8 *persMatDDRPtr;

    gaCalibInfo->gaLUTDDRPtr = (UInt8 *)ChainsCommon_Osal_memAlloc(
                                            GA_OUTPUT_LUT_SIZE_MEM_ALLOC, 32U);
    UTILS_assert(gaCalibInfo->gaLUTDDRPtr != NULL);

    gaCalibInfo->persMatDDRPtr = (UInt8 *)ChainsCommon_Osal_memAlloc(
                                            GA_PERSPECTIVE_MATRIX_SIZE, 32U);
    UTILS_assert(gaCalibInfo->persMatDDRPtr != NULL);

    gaCalibInfo->featurePtDDRPtr = (UInt8 *)ChainsCommon_Osal_memAlloc(
                                            GA_FEATURE_PT_SIZE, 32);
    UTILS_assert(gaCalibInfo->featurePtDDRPtr != NULL);

    gaCalibInfo->autoPersMatDDRPtr = (UInt8 *)ChainsCommon_Osal_memAlloc(
                                            GA_PERSPECTIVE_MATRIX_SIZE, 32U);
    UTILS_assert(gaCalibInfo->autoPersMatDDRPtr != NULL);

#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    gaCalibInfo->synthLUTSize = \
                            SRV_OUTPUT_MAX_WIDTH * SRV_OUTPUT_MAX_HEIGHT * 4U;
    gaCalibInfo->synthLUTPtr = (UInt8 *)ChainsCommon_Osal_memAlloc(
                                            gaCalibInfo->synthLUTSize, 32U);
    UTILS_assert(gaCalibInfo->synthLUTPtr != NULL);
#else
    gaCalibInfo->synthLUTSize = 0U;
    gaCalibInfo->synthLUTPtr = NULL;
#endif

    gaCalibInfo->calMode = ALGLINK_GALIGN_CALMODE_USERGALUT;

    // set persmat pointer to read from QSPI
    if (ALGORITHM_LINK_SRV_OUTPUT_3D == gaCalibInfo->svOutputMode)
    {
        persMatDDRPtr = gaCalibInfo->autoPersMatDDRPtr;
    }
    else
    {
        persMatDDRPtr = gaCalibInfo->persMatDDRPtr;
    }

    if (ALGORITHM_LINK_SRV_OUTPUT_2D == gaCalibInfo->svOutputMode)
    {
        /*
         *  The pers mat is read from the MMC/SD file
         */
        if (readPersMatFile() != SYSTEM_LINK_STATUS_SOK)
        {
            /*
             *  If PERSMAT.BIN file is not present then try to read the
             *  pers mat from the flash/file
             */
            ChainsCommon_Osal_readSrvCalibTable(
                                    (UInt32)persMatDDRPtr,
                                    GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D,
                                    GA_PERSPECTIVE_MATRIX_SIZE_2D);

            ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                            (UInt32)persMatDDRPtr);
            if (*ptr == GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE)
            {
                Vps_printf(" Using Pers Mat read from QSPI\n");
                gaCalibInfo->calMode =
                                ALGLINK_GALIGN_CALMODE_FORCE_USERPERSMATRIX;
            }
            else
            {
                Vps_printf(" Pers Mat is neither present in %s file nor QSPI\n",
                                    SRV_PERSMAT_FILE);
                Vps_printf(" Using Default Pers Mat\n");

                gaCalibInfo->calMode =
                                ALGLINK_GALIGN_CALMODE_FORCE_DEFAULTPERSMATRIX;
            }
        }
        else
        {
            Vps_printf(" Using Pers Mat read from %s file\n", SRV_PERSMAT_FILE);
            gaCalibInfo->calMode =
                            ALGLINK_GALIGN_CALMODE_FORCE_USERPERSMATRIX;
        }
    }

    switch (gaCalibInfo->GACalibrationType)
    {
        case CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO:
            ChainsCommon_Osal_readSrvCalibTable(
                                        (UInt32)gaCalibInfo->gaLUTDDRPtr,
                                        GA_OUTPUT_LUT_FLASHMEM_OFFSET,
                                        GA_MAGIC_PATTERN_SIZE_IN_BYTES);

            ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                        (UInt32)gaCalibInfo->gaLUTDDRPtr);

            if (*ptr == GA_OUTPUT_LUT_MAGIC_SEQUENCE)
            {
                gaCalibInfo->calMode = ALGLINK_GALIGN_CALMODE_USERGALUT;
                ChainsCommon_Osal_readSrvCalibTable(
                                            (UInt32)gaCalibInfo->gaLUTDDRPtr,
                                            GA_OUTPUT_LUT_FLASHMEM_OFFSET,
                                            GA_OUTPUT_LUT_SIZE);
            }
            else
            {
                gaCalibInfo->calMode = ALGLINK_GALIGN_CALMODE_DEFAULT;
            }

            break;

        case CHAINS_SURROUND_VIEW_GA_CALIBRATION_FORCE:
            if (ALGORITHM_LINK_SRV_OUTPUT_2D != gaCalibInfo->svOutputMode)
            {
                ChainsCommon_Osal_readSrvCalibTable(
                                        (UInt32)persMatDDRPtr,
                                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET,
                                        GA_MAGIC_PATTERN_SIZE_IN_BYTES);

                ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                                        (UInt32)persMatDDRPtr);

                if (*ptr == GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE)
                {
                    gaCalibInfo->calMode = \
                                    ALGLINK_GALIGN_CALMODE_FORCE_USERPERSMATRIX;
                    ChainsCommon_Osal_readSrvCalibTable(
                                        (UInt32)persMatDDRPtr,
                                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET,
                                        GA_PERSPECTIVE_MATRIX_SIZE);
                }
                else
                {
                    gaCalibInfo->calMode = \
                                ALGLINK_GALIGN_CALMODE_FORCE_DEFAULTPERSMATRIX;
                }
            }

            break;

        case CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO_USERSGXLUT:
            ChainsCommon_Osal_readSrvCalibTable(
                                        (UInt32)persMatDDRPtr,
                                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET,
                                        GA_MAGIC_PATTERN_SIZE_IN_BYTES);

            ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr((UInt32)persMatDDRPtr);

            if (*ptr == GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE)
            {
                Vps_printf (" Pers mat read ...\n");

                ChainsCommon_Osal_readSrvCalibTable(
                                        (UInt32)persMatDDRPtr,
                                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET,
                                        GA_PERSPECTIVE_MATRIX_SIZE);

                Vps_printf (" Pers mat read (%d bytes) DONE\n",\
                                                GA_PERSPECTIVE_MATRIX_SIZE);

                /*
                 *  Read the GA SGX LUT
                 */
                ChainsCommon_Osal_readSrvCalibTable(
                                    (UInt32)gaCalibInfo->gaLUTDDRPtr,
                                    GA_OUTPUT_LUT_FLASHMEM_OFFSET,
                                    GA_MAGIC_PATTERN_SIZE_IN_BYTES);

                ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                            (UInt32)gaCalibInfo->gaLUTDDRPtr);

                if (*ptr == GA_OUTPUT_LUT_MAGIC_SEQUENCE)
                {
                    gaCalibInfo->calMode = \
                        (AlgorithmLink_GAlignCalibrationMode)\
                                    ALGLINK_GALIGN3D_CALMODE_FORCE_USERGASGXLUT;
                }
                else
                {
                    gaCalibInfo->calMode = \
                        (AlgorithmLink_GAlignCalibrationMode)\
                            ALGLINK_GALIGN3D_CALMODE_FORCE_DEFAULTPERSMATRIX;
                    Vps_printf(" User GA SGX LUT NOT found, using default LUT\n");
                }
            }
            else
            {
                gaCalibInfo->calMode = \
                  (AlgorithmLink_GAlignCalibrationMode)\
                          ALGLINK_GALIGN3D_CALMODE_FORCE_DEFAULTPERSMATRIX;
                Vps_printf (" Pers Mat NOT found, using default LUT\n");
            }

            break;

        default:
            UTILS_assert(0);

            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to de-allocate intermediate GA OUTPUT LUT and
 *          Perspective Matrix tables.
 *          - Also perform QSPI flash write after the succesful calibration
 *          - Delete the task to update the peraMat table into QSPI flash
 *
 * \param   gaCalibInfo    [IN]  Chain_Common_SRV_GACalibrationInfo
 *
 *******************************************************************************
*/
static Void ChainsCommon_SurroundView_freeGATbl(
                    ChainsCommon_SurroundView_GACalibrationInfo *gaCalibInfo)
{
    ChainsCommon_Osal_memFree(
                        (Ptr)gaCalibInfo->gaLUTDDRPtr,
                        GA_OUTPUT_LUT_SIZE_MEM_ALLOC);
    ChainsCommon_Osal_memFree(
                        (Ptr)gaCalibInfo->persMatDDRPtr,
                        GA_PERSPECTIVE_MATRIX_SIZE);
    ChainsCommon_Osal_memFree(
                        (Ptr)gaCalibInfo->featurePtDDRPtr,
                        GA_FEATURE_PT_SIZE);
    ChainsCommon_Osal_memFree(
                        (Ptr)gaCalibInfo->autoPersMatDDRPtr,
                        GA_PERSPECTIVE_MATRIX_SIZE);
#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    ChainsCommon_Osal_memFree(
                        (Ptr)gaCalibInfo->synthLUTPtr,
                        gaCalibInfo->synthLUTSize);
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Calibration Init
 *
 *          This functions set/implement follwing
 *          - Set calibartion option enable
 *          - Set calibartion option disable
 *          - Set QSPI Flash erase option
 *
 * \param   gaCalibInfo    [IN]  ChainsCommon_SurroundView_GACalibrationInfo
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_CalibInit(
                            Bool startWithCalibration,
                            AlgorithmLink_SrvOutputModes svOutputMode)

{
    gChains_surroundViewCalibInfo.svOutputMode = svOutputMode;

    if(startWithCalibration)
    {
        gChains_surroundViewCalibInfo.GACalibrationType = \
                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_FORCE;
        gChains_surroundViewCalibInfo.GACalibrationTypePrev = \
                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_FORCE;
    }
    else
    {
        gChains_surroundViewCalibInfo.GACalibrationType = \
                                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO;
        gChains_surroundViewCalibInfo.GACalibrationTypePrev = \
                                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO;
    }

    /*
     *  3D SRV on TDA2X using SGX will work only with the user provided
     *  SGX LUT
     *  The user SGX LUT is generated by running the SRV calibration use case
     *  Here 'FORCE' and 'NO' calibration options are invalid
     */
    if (ALGORITHM_LINK_SRV_OUTPUT_3D == svOutputMode)
    {
        gChains_surroundViewCalibInfo.GACalibrationType = \
                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO_USERSGXLUT;
        gChains_surroundViewCalibInfo.GACalibrationTypePrev = \
                        CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO_USERSGXLUT;
    }

    ChainsCommon_SurroundView_allocateGATbl(&gChains_surroundViewCalibInfo);

    Vps_printf(" Calibration Init with the mode = %d\n", \
                                        gChains_surroundViewCalibInfo.calMode);
}

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for the Calibration options
 *
 *          This functions set/implement follwing
 *          - Set calibartion option enable
 *          - Set calibartion option disable
 *          - Set QSPI Flash erase option
 *
 * \param   gaCalibInfo    [IN]  ChainsCommon_SurroundView_GACalibrationInfo
 *
 *******************************************************************************
*/
char ChainsCommon_SurroundView_MenuCalibration()
{
    char ch;
    UInt32 *ptr;
    ChainsCommon_SurroundView_GACalibrationInfo *gaCalibInfo;
    UInt32 done = FALSE;

    gaCalibInfo = &gChains_surroundViewCalibInfo;

    if (ALGORITHM_LINK_SRV_OUTPUT_3D == gaCalibInfo->svOutputMode)
    {
        /*
         *  3D SRV using SGX will always read the LUTs from the file
         *  Write back and erasing of the LUTs is not required
         */
        ch = '3';
    }
    else
    {
        while(!done)
        {
            Task_sleep(500);
            Vps_printf(gChainsCommon_SurroundView_MenuCalibration);
            Task_sleep(500);

            ch = 'a';
            ch = Chains_readChar();

            switch(ch)
            {
                case '1':
                    ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                            (UInt32)gaCalibInfo->gaLUTDDRPtr);
                    *ptr = GA_OUTPUT_LUT_MAGIC_SEQUENCE;
                    ChainsCommon_Osal_writeSrvCalibTable(
                                            (UInt32)gaCalibInfo->gaLUTDDRPtr,
                                            GA_OUTPUT_LUT_FLASHMEM_OFFSET,
                                            GA_OUTPUT_LUT_SIZE + \
                                                GA_MAGIC_PATTERN_SIZE_IN_BYTES);

                    ptr = (UInt32*)ChainsCommon_Osal_getVirtAddr(
                                            (UInt32)gaCalibInfo->persMatDDRPtr);
                    *ptr = GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE;
                    ChainsCommon_Osal_writeSrvCalibTable(
                                (UInt32)gaCalibInfo->persMatDDRPtr,
                                GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D,
                                GA_PERSPECTIVE_MATRIX_SIZE_2D + \
                                                GA_MAGIC_PATTERN_SIZE_IN_BYTES);

                    break;

                case '2':
                    ChainsCommon_Osal_eraseSrvCalibTable(
                                        GA_OUTPUT_LUT_FLASHMEM_OFFSET,
                                        GA_OUTPUT_LUT_SIZE);

                    ChainsCommon_Osal_eraseSrvCalibTable(
                                    GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D,
                                    GA_PERSPECTIVE_MATRIX_SIZE_2D);

                    break;

                case '3':
                    done = TRUE;
                    break;
            }
        }
    }

    return ch;
}

#if defined(LINUX_BUILD) || defined(QNX_BUILD)
Void ChainsCommon_Osal_readSrvCalibTable(
                                UInt32 readAddr,
                                UInt32 readOffset,
                                UInt32 readSize)
{
    UInt32 actualReadSize;

    OSA_fileReadFileOffset(
                    CALIBDATA_FILENAME,
                    (Ptr)ChainsCommon_Osal_getVirtAddr(readAddr),
                    readSize,
                    &actualReadSize,
                    readOffset);

    ChainsCommon_Osal_cacheWb(
                    ChainsCommon_Osal_getVirtAddr(readAddr),
                    readSize);
}

Void ChainsCommon_Osal_writeSrvCalibTable(
                                UInt32 writeAddr,
                                UInt32 writeOffset,
                                UInt32 writeSize)
{
    ChainsCommon_Osal_cacheInv(
                    ChainsCommon_Osal_getVirtAddr(writeAddr),
                    writeSize);

    OSA_fileWriteFileOffset(
                    CALIBDATA_FILENAME,
                    (UInt8*)ChainsCommon_Osal_getVirtAddr(writeAddr),
                    writeSize,
                    writeOffset);
}

#else
Void ChainsCommon_Osal_readSrvCalibTable(
                                UInt32 readAddr,
                                UInt32 readOffset,
                                UInt32 readSize)
{
    System_qspiReadSector(
                    readAddr,
                    readOffset,
                    readSize);

    ChainsCommon_Osal_cacheWb(
                    ChainsCommon_Osal_getVirtAddr(readAddr),
                    readSize);
}

Void ChainsCommon_Osal_writeSrvCalibTable(
                                UInt32 writeAddr,
                                UInt32 writeOffset,
                                UInt32 writeSize)
{
    ChainsCommon_Osal_cacheInv(
                    ChainsCommon_Osal_getVirtAddr(writeAddr),
                    writeSize);

    System_qspiWriteSector(
                    writeOffset,
                    ChainsCommon_Osal_getVirtAddr(writeAddr),
                    SystemUtils_align(writeSize, QSPIFLASH_BLOCKSIZE));
}
#endif
/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for the Calibration options
 *
 *          This functions set/implement follwing
 *          - Set calibartion option enable
 *          - Set calibartion option disable
 *          - Set QSPI Flash erase option
 *
 * \param   gaCalibInfo    [IN]  ChainsCommon_SurroundView_GACalibrationInfo
 *
 *******************************************************************************
*/
Void ChainsCommon_SurroundView_CalibDeInit()
{
    ChainsCommon_SurroundView_freeGATbl(&gChains_surroundViewCalibInfo);
    Vps_printf(" Calibration DeInit for the mode = %d\n", \
                                        gChains_surroundViewCalibInfo.calMode);
}

/**
 *******************************************************************************
 *
 * \brief   Return the Calibration Mode
 *
 *          This functions set/implement follwing
 *          - Set calibartion option enable
 *          - Set calibartion option disable
 *          - Set QSPI Flash erase option
 *
 * \param   gaCalibInfo    [IN]  ChainsCommon_SurroundView_GACalibrationInfo
 *
 *******************************************************************************
*/
AlgorithmLink_GAlignCalibrationMode ChainsCommon_SurroundView_getCalMode()
{
    return (gChains_surroundViewCalibInfo.calMode);
}

/**
 *******************************************************************************
 *
 * \brief   Return the Calibration Info Structure Pointer
 *
 *          This functions set/implement follwing
 *          - Set calibartion option enable
 *          - Set calibartion option disable
 *          - Set QSPI Flash erase option
 *
 * \param   gaCalibInfo    [IN]  ChainsCommon_SurroundView_GACalibrationInfo
 *
 *******************************************************************************
*/
ChainsCommon_SurroundView_GACalibrationInfo \
                                    *ChainsCommon_SurroundView_getCalibPrm()
{
    return (&gChains_surroundViewCalibInfo);
}
