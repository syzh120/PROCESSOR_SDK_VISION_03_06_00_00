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

/*
 *******************************************************************************
 *
 * \file chains_common.h
 *
 * \brief This file contains common utility functions used by all use-cases
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_H_
#define _CHAINS_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <src/include/chains.h>
#include "include/link_api/system_common.h"
#ifndef RADAR_ONLY
#include <src/rtos/utils_common/include/utils_temperature.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/include/chains_common_surround_view.h>
#include "itidl_ti.h"
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define CHAINS_COMMON_FC_ANALYTICS_LAYOUT_VERT_STRIP        (0)
#define CHAINS_COMMON_FC_ANALYTICS_LAYOUT_HORZ_STRIP        (1)
#define CHAINS_COMMON_FC_ANALYTICS_LAYOUT_HORZ_AND_VERT     (2)

/**
 *******************************************************************************
 * \brief Macro to identify HOT Temperature Configuration
 *******************************************************************************
 */
#define CHAINS_HOT_TEMPERATURE (0U)
/**
 *******************************************************************************
 * \brief Macro to identify COLD Temperature Configuration
 *******************************************************************************
 */
#define CHAINS_COLD_TEMPERATURE (1U)

/**
 *******************************************************************************
 *
 *  \brief  Common information related to all use-case
 *
 *******************************************************************************
*/
typedef struct Chains_CommonObj_t {

    UInt32  lcdInstId;
    UInt32  displayCtrlLinkId;

    Lcd_CreateParams                        lcdPrm;
    HdmiTx_CreateParams                     hdmiTxPrm;

    DisplayCtrlLink_ConfigParams            dctrlCfgPrms;
    DisplayCtrlLink_OvlyPipeParams          pipeParams[4];
    DisplayCtrlLink_OvlyParams              ovlyParams;

} Chains_CommonObj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

Void ChainsCommon_Init();

Void ChainsCommon_DeInit();

Void ChainsCommon_Iss_Init();
Void ChainsCommon_Iss_DeInit();

Void ChainsCommon_SetDisplayPrms(
        DisplayLink_CreateParams *pPrm_Video,
        DisplayLink_CreateParams *pPrm_Grpx,
        Chains_DisplayType displayType,
        UInt32 displayWidth,
        UInt32 displayHeight
);

Int32 ChainsCommon_StartDisplayCtrl(UInt32 displayType,
        UInt32 displayWidth,
        UInt32 displayHeight
);

Int32 ChainsCommon_DualDisplay_StartDisplayCtrl (
        Chains_DisplayType lcdType,UInt32 displayLCDWidth, UInt32 displayLCDHeight);

Int32 ChainsCommon_StopDisplayCtrl();

Void ChainsCommon_InitCaptureDevice(Chains_CaptureSrc captureSrc);

Int32 ChainsCommon_StartCaptureDevice(Chains_CaptureSrc captureSrc,
        UInt32 captureOutWidth,
        UInt32 captureOutHeight);

Int32 ChainsCommon_MultiCam_StartCaptureDevice(Chains_CaptureSrc captureSrc,
        UInt32 portId[],
        UInt32 numLvdsCh
);

Int32 ChainsCommon_StopCaptureDevice(Chains_CaptureSrc captureSrc);

Int32 ChainsCommon_StartDisplayDevice(UInt32 displayType);
Int32 ChainsCommon_StopDisplayDevice(UInt32 displayType);

Void ChainsCommon_SetSystemL3DmmPri();

Void ChainsCommon_SingleCam_SetCapturePrms(
        CaptureLink_CreateParams *pPrm,
        UInt32 captureInWidth,
        UInt32 captureInHeight,
        UInt32 captureOutWidth,
        UInt32 captureOutHeight,
        Chains_CaptureSrc captureSrc
);

#ifndef RADAR_ONLY
Void ChainsCommon_SetAvbRxPrm(
        AvbRxLink_CreateParams *pAvbPrm,
        UInt32 maxWidth,
        UInt32 maxHeight,
        UInt32 numCh);

Void ChainsCommon_SetAvbTxPrm(
        AvbTxLink_CreateParams *pAvbPrm,
        UInt32 numCh,
        System_IVideoFormat codecType);
Void ChainsCommon_SetDecodePrm(
        DecLink_CreateParams *pDecPrm,
        UInt32 maxWidth,
        UInt32 maxHeight,
        UInt32 numCh,
        System_IVideoFormat codecType);
Void ChainsCommon_SurroundView_SetAdaptiveBowlParams(
                            AlgorithmLink_AdaptiveBowlCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight);

Void ChainsCommon_StereoCam_SetCapturePrms(
        CaptureLink_CreateParams *pPrm,
        UInt32 captureInWidth,
        UInt32 captureInHeight,
        UInt32 captureOutWidth,
        UInt32 captureOutHeight,
        Chains_CaptureSrc captureSrc
);

Void ChainsCommon_TDA2x_StereoCam_SetCapturePrms(
        CaptureLink_CreateParams *pPrm,
        UInt32 captureInWidth,
        UInt32 captureInHeight,
        UInt32 captureOutWidth,
        UInt32 captureOutHeight,
        Chains_CaptureSrc captureSrc,
        UInt32 portId[],
        UInt32 numLvdsCh
);

Void ChainsCommon_MultiCam_SetCapturePrms(
        CaptureLink_CreateParams *pPrm,
        UInt32 captureInWidth,
        UInt32 captureInHeight,
        UInt32 portId[],
        UInt32 numLvdsCh
);


Void ChainsCommon_MultiCam_SetCroppingPrms(
                        CaptureLink_CreateParams *pPrm,
                        Uint32 inWidth,
                        Uint32 inHeight,
                        Uint32 outWidth,
                        Uint32 outHeight);
#endif

Void ChainsCommon_PrintStatistics();

Void ChainsCommon_PrintPMStatistics();

Void ChainsCommon_GetDisplayWidthHeight(
        Chains_DisplayType displayType,
        UInt32 *displayWidth,
        UInt32 *displayHeight
);



Void ChainsCommon_SetGrpxSrcPrms(
        GrpxSrcLink_CreateParams *pPrm,
        UInt32 displayWidth,
        UInt32 displayHeight
);

#ifndef RADAR_ONLY
Void ChainsCommon_Analytics_SetPrms(
        CaptureLink_CreateParams                *pCapturePrm,
        NullSrcLink_CreateParams                *pNullSrcPrm,
        DecLink_CreateParams                    *pDecPrm,
        AlgorithmLink_LaneDetectCreateParams    *pAlg_LaneDetectPrm,
        AlgorithmLink_ObjectDrawCreateParams *pAlg_LaneDetectDrawPrm,
        SyncLink_CreateParams                   *pSync_ldPrm,
        AlgorithmLink_FeaturePlaneComputationCreateParams *pAlg_FeaturePlaneComputationPrm,
        AlgorithmLink_ObjectDetectionCreateParams *pAlg_ObjectDetectionPrm,
        AlgorithmLink_ObjectDrawCreateParams    *pAlg_ObjectDrawPrm,
        SyncLink_CreateParams                   *pSync_pd_tsrPrm,
        AlgorithmLink_SparseOpticalFlowCreateParams *pSofAlgPrm,
        AlgorithmLink_ObjectDrawCreateParams *pSofDrawPrm,
        SyncLink_CreateParams                   *pSync_sofPrm,
        SyncLink_CreateParams                   *pSync_algPrm,
        AlgorithmLink_DmaSwMsCreateParams       *pAlg_DmaSwMsPrm,
        DisplayLink_CreateParams                *pDisplay_algPrm,
        GrpxSrcLink_CreateParams                *pGrpxSrcPrm,
        DisplayLink_CreateParams                *pDisplay_GrpxPrm,
        Chains_CaptureSrc captureSrc,
        Chains_DisplayType displayType,
        UInt32 Alg_FeaturePlaneComputationLinkID,
        UInt32 Alg_ObjectDetectionLinkID,
        UInt32 Alg_ObjectDrawLinkID,
        UInt32 dmaSwMsLayoutType
);

Void ChainsCommon_SetNetworkRxPrms(
        NetworkRxLink_CreateParams *pPrm,
        DecLink_CreateParams *pDecPrm,
        UInt32 maxWidth,
        UInt32 maxHeight,
        UInt32 numCh,
        UInt32 fps /* in msecs */
);

Void ChainsCommon_SetFileRxPrms(
        NullSrcLink_CreateParams *pPrm,
        DecLink_CreateParams *pDecPrm,
        UInt32 maxWidth,
        UInt32 maxHeight,
        UInt32 numCh,
        UInt32 fps /* in msecs */
);


Void ChainsCommon_Analytics_Start(Bool useVipCapture);

Void ChainsCommon_Analytics_Stop(Bool useVipCapture);

/*Stereo*/

Void ChainsCommon_Stereo_Init();

Void ChainsCommon_Stereo_Delete( AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm);

Void ChainsCommon_Stereo_AutoRemap_Delete(
        AlgorithmLink_AutoRemapCreateParams *pAlg_AutoRemapPrm);

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
        DisplayLink_CreateParams *pDisplay_GrpxPrm,
        DisplayLink_CreateParams *pDisplay_disparityPrm,
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
);

Void ChainsCommon_Stereo_SetGlobalParams(
        UInt32 remapWidth,
        UInt32 remapHeight,
        UInt32 stereoOutputWidth,
        UInt32 stereoOutputHeight);

Void ChainsCommon_TDA2x_Stereo_SetCapturePrms(
        CaptureLink_CreateParams *pCapturePrm,
        Chains_CaptureSrc captureSrc,
        Chains_DisplayType displayType,
        UInt32 captureSensorWidth,
        UInt32 captureSensorHeight);

Void ChainsCommon_TDA2x_Stereo_AlgoParams(
        AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm,
        AlgorithmLink_CensusCreateParams *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm);

/*
 * Read stereo parameters from SD card, which are used by
 * stereo matching and post processing.
 */
Void ChainsCommon_Stereo_Read_Params(Int32 * sParamsBuffer);

/*
 * Read stereo camera parameters from SD card, which are used to construct 3D points
 */
Void ChainsCommon_Stereo_Read_CamParams(float *sCamParamsBuffer);


Void ChainsCommon_TDA3x_Stereo_SetPrms(
        SyncLink_CreateParams *pSync_censusInPrm,
        AlgorithmLink_CensusCreateParams *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm,
        UInt32 remapWidth,
        UInt32 remapHeight,
        UInt32 stereoOutputWidth,
        UInt32 stereoOutputHeight
);

Void ChainsCommon_Stereo_SetCamPrms(AlgorithmLink_StereoAppCreateParams *pAlg_StereoAppPrm);


Void ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
        AlgorithmLink_DmaSwMsCreateParams *pPrm,
        UInt32 numLvdsCh,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight,
        UInt32 orgVideoWinGap
);

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
);

Void ChainsCommon_Stereo_SetGrpxSrcPrms(
        GrpxSrcLink_CreateParams *pPrm,
        UInt32 displayWidth,
        UInt32 displayHeight);

Void ChainsCommon_Stereo_SetSyncPrm(
        SyncLink_CreateParams *pSyncPrm1,
        SyncLink_CreateParams *pSyncPrm2,
        UInt32 numLvdsCh);

Void ChainsCommon_Single_Stereo_AutoRemapAlgPrms(
        AlgorithmLink_AutoRemapCreateParams* pPrm_AutoRemap,
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
        Bool   tda2x);

char ChainsCommon_Stereo_AutoRemap_Menu();

char ChainsCommon_menuRunTime_SingleCamAnalytics();

Void ChainsCommon_thermalConfig();

Void ChainsCommon_modifyTemperatureThreshold(char ch_temp, UInt32 eventType);

Void ChainsCommon_readTemperatureThreshold(UInt32 eventType);

Void ChainsCommon_modifyTempThresholdStepSize(char ch_temp);

Void ChainsCommon_tempHotEventHandler(UInt32 captureLinkId, Void* pPrm);

Void ChainsCommon_tempColdEventHandler(UInt32 captureLinkId, Void* pPrm);

Void ChainsCommon_Analytics2_SetPrms(
            CaptureLink_CreateParams *pCapturePrm,
            AlgorithmLink_SparseOpticalFlowCreateParams *pSofPrm,
            AlgorithmLink_SfmCreateParams *pSfmPrm,
            AlgorithmLink_ImagePreProcessCreateParams  *pImgPreProcPrm,
            AlgorithmLink_ImgPyramidCreateParams *pImgPmd,
            AlgorithmLink_FPComputeCreateParams *pFpcPrm,
            AlgorithmLink_ObjectDetectionCreateParams *pOdPrm,
            AlgorithmLink_ObjectClassificationCreateParams *pOcPrm,
            SyncLink_CreateParams *pSyncFcwPrm,
            AlgorithmLink_FcwCreateParams *pFcwPrm,
            AlgorithmLink_LaneDetectCreateParams *pLdPrm,
            AlgorithmLink_ClrCreateParams *pClrPrm,
            SyncLink_CreateParams *pSyncAlgPrm,
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm,
            SyncLink_CreateParams *pSyncOdPrm,
            DisplayLink_CreateParams *pDisplayVideoPrm,
            GrpxSrcLink_CreateParams *pGrpxSrcPrm,
            DisplayLink_CreateParams *pDisplayGrpxPrm,
            Chains_CaptureSrc captureSrc,
            Chains_DisplayType displayType,
            UInt32 Alg_ImgPyramidLinkID,
            UInt32 Alg_FPComputeLinkID,
            UInt32 Alg_ObjectDrawinkID,
            UInt32 Alg_ObjectClassificationLinkID,
            UInt32 Alg_LaneDetectLinkID,
            UInt32 isInputModeFile
        );

Void ChainsCommon_Analytics2_Start(UInt32 isInputModeFile);
Void ChainsCommon_Analytics2_Stop(UInt32 isInputModeFile);

Void ChainsCommon_SetSOFConfig(
            AlgorithmLink_SparseOpticalFlowCreateParams *pAlgSofPrm,
            UInt32 startX,
            UInt32 startY,
            UInt32 width,
            UInt32 height,
            UInt32 sfmTrackPoints);

Void ChainsCommon_RVP_Delete( AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm);

Void ChainsCommon_RVP_SetParams(
            CaptureLink_CreateParams    *pCapturePrm,
            SelectLink_CreateParams     *pSelect_DisparityPrm,
            SelectLink_CreateParams     *pSelect_PanoramaPrm,
            SyncLink_CreateParams       *pSync_PanoramaPrm,
            SyncLink_CreateParams       *pSync_RemapOutPrm,
            VpeLink_CreateParams        *pVPE_RemapInPrm,
            VpeLink_CreateParams        *pVPE_PostProcOutPrm,
            VpeLink_CreateParams        *pVPE_ImgTransformOutPrm,
            VpeLink_CreateParams        *pVPE_ImgTransformInPrm,
            GrpxSrcLink_CreateParams    *pGrpxSrcPrm,
            DisplayLink_CreateParams    *pDisplay_PanoramaPrm,
            DisplayLink_CreateParams    *pDisplay_DisparityPrm,
            DisplayLink_CreateParams    *pDisplay_GrpxPrm,

            AlgorithmLink_ImageTransformCreateParams    *pAlg_ImageTransformPrm,
            AlgorithmLink_SeamDetectionCreateParams     *pAlg_SeamDetectionPrm,
            AlgorithmLink_StitchingCreateParams         *pAlg_StitchingPrm,
            AlgorithmLink_RemapMergeCreateParams        *pAlg_RemapMergePrm,
            AlgorithmLink_CensusCreateParams            *pAlg_CensusPrm,
            AlgorithmLink_DisparityHamDistCreateParams  *pAlg_DisparityHamDistPrm,
            AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm,
            AlgorithmLink_DmaSwMsCreateParams           *pAlg_DmaSwMPrm,

            Chains_CaptureSrc   captureSrc,
            Chains_DisplayType  displayType,

            unsigned char stitchingMode,
            unsigned char seamDetectionMode,
            unsigned char imageTransformMode,

            Bool enableDisparityLayout,
            Bool enableCarOverlay,
            UInt32 simcopOutputWidth,
            UInt32 simcopOutputHeight);

UInt32 ChainsCommon_displayLHMStatus();
#endif

Void Chains_vipSingleCamOpenCVCanny(Chains_Ctrl *chainsCfg);
Void Chains_vipSingleCamOpenCVOpenCLDilation(Chains_Ctrl *chainsCfg);

#ifndef RADAR_ONLY
Void ChainsCommon_SurroundView_CalibInit(
                                    Bool startWithCalibration,
                                    AlgorithmLink_SrvOutputModes svOutputMode);
char ChainsCommon_SurroundView_MenuCalibration();
Void ChainsCommon_SurroundView_CalibDeInit();
AlgorithmLink_GAlignCalibrationMode ChainsCommon_SurroundView_getCalMode();
ChainsCommon_SurroundView_GACalibrationInfo \
                                    *ChainsCommon_SurroundView_getCalibPrm();

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
                            Bool enableCarOverlayInAlg);

Void ChainsCommon_SurroundView_SetGAlignParams(
                            AlgorithmLink_GAlignCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight,
                            AlgorithmLink_SrvOutputModes svOutputMode);

Void ChainsCommon_SurroundView_SetGAlign3DParams(
                            AlgorithmLink_GAlign3DCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight,
                            AlgorithmLink_SrvOutputModes svOutputMode);

Void ChainsCommon_SurroundView_SetPAlignParams(
                            AlgorithmLink_PAlignCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight,
                            AlgorithmLink_SrvOutputModes svOutputMode);

Void ChainsCommon_SurroundView_SetACDetectParams(
                            AlgorithmLink_ACDetectCreateParams *pPrm);

Void ChainsCommon_SurroundView_SetPEstimateParams(
                            AlgorithmLink_PEstimateCreateParams *pPrm);

Void ChainsCommon_SurroundView_SetSyncPrm(
                            SyncLink_CreateParams *pPrm,
                            UInt32 numLvdsCh,
                            UInt32 syncMode);

Void ChainsCommon_SurroundView_SetGrpxSrcPrms(
                           GrpxSrcLink_CreateParams *pPrm,
                           UInt32 displayWidth,
                           UInt32 displayHeight,
                           AlgorithmLink_SrvOutputModes srvMode);

Void ChainsCommon_SurroundView_SetDisplayPrm(
                            DisplayLink_CreateParams *pSvDisplay,
                            DisplayLink_CreateParams *pSvOrgDisplay,
                            DisplayLink_CreateParams *pFrontCamDisplay,
                            DisplayLink_CreateParams *pGrpxDisplay,
                            UInt32 displayWidth,
                            UInt32 displayHeight);

Void ChainsCommon_SurroundView_GetSrvOutputResolution(
                            AlgorithmLink_SrvOutputModes svOutputMode,
                            UInt32 *pSvOutWidth,
                            UInt32 *pSvOutHeight);

Void ChainsCommon_SurroundView_SetVpePrm(
                            VpeLink_CreateParams *pSvOrgVpe,
                            VpeLink_CreateParams *pFrontCamVpe,
                            UInt32 frontCamAlgOutWidth,
                            UInt32 frontCamAlgOutHeight);

Ptr ChainsCommon_SurroundView_memAlloc(UInt32 size, UInt32 align);
Void ChainsCommon_SurroundView_memFree(Ptr addr, UInt32 size);

Void ChainsCommon_SurroundView_SetSelectPrm(SelectLink_CreateParams *pPrm);

Void ChainsCommon_SurroundView_SetAlgDmaSwMsPrm(
                            AlgorithmLink_DmaSwMsCreateParams *pPrm,
                            UInt32 numLvdsCh,
                            UInt32 channelWidth,
                            UInt32 channelHeight,
                            UInt32 layoutType,
                            UInt32 channelSpacingHor,
                            UInt32 channelSpacingVer);

Void ChainsCommon_SurroundView_SetFCVpePrm(
                            VpeLink_CreateParams *pPrm,
                            UInt32 outWidth,
                            UInt32 outHeight,
                            UInt32 srcWidth,
                            UInt32 srcHeight,
                            System_VideoDataFormat dataFormat);

Void ChainsCommon_SurroundView_SetFeaturePlaneComputeAlgPrms(
                           AlgorithmLink_FeaturePlaneComputationCreateParams *pPrm,
                           UInt32 width,
                           UInt32 height);

Void ChainsCommon_SurroundView_SetObjectDetectPrm(
                           AlgorithmLink_ObjectDetectionCreateParams *pPrm,
                           UInt32 width,
                           UInt32 height);

Void ChainsCommon_SurroundView_SetSyncFcPrm(SyncLink_CreateParams *pPrm);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */

