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
#include <src/hlos/osa/include/osa.h>

#include <src/include/draw2d.h> // TBD : Remove dependency on bios examples
#include <src/include/chains_common_srv_calib.h>
#include <src/include/link_stats_monitor.h>

#include <include/link_api/system.h>
#include <include/link_api/system_common.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/vpeLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/sgxFrmcpyLink.h>
#include <include/link_api/sgx3DsrvLink.h>
#include <include/link_api/sgx3DsfmLink.h>
#include <include/link_api/ipcLink.h>

#include <include/alglink_api/algorithmLink_opencvCanny.h>

#include <include/alglink_api/algorithmLink_frameCopy.h>
#include <include/alglink_api/algorithmLink_edgeDetection.h>
#include <include/alglink_api/algorithmLink_dmaSwMs.h>
#include <include/alglink_api/algorithmLink_geometricAlignment.h>
#include <include/alglink_api/algorithmLink_geometricAlignment3D.h>
#include <include/alglink_api/algorithmLink_adaptiveBowl.h>
#include <include/alglink_api/algorithmLink_photoAlignment.h>
#include <include/alglink_api/algorithmLink_synthesis.h>
#include <include/alglink_api/algorithmLink_sfmMain.h>
#include <include/alglink_api/algorithmLink_sfmLinearTwoView.h>
#include <include/alglink_api/algorithmLink_sfmMap.h>
#include <include/alglink_api/algorithmLink_denseOpticalFlow.h>
#include <include/alglink_api/algorithmLink_vectorToImage.h>
#include <include/alglink_api/algorithmLink_featurePlaneComputation.h>
#include <include/alglink_api/algorithmLink_objectDetection.h>
#include <include/alglink_api/algorithmLink_sparseOpticalFlow.h>
#include <include/alglink_api/algorithmLink_objectDraw.h>
#include <include/alglink_api/algorithmLink_laneDetect.h>
#include <include/alglink_api/algorithmLink_autoChartDetect.h>
#include <include/alglink_api/algorithmLink_poseEstimate.h>
#include <include/link_api/ultrasonicCaptureLink.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/avbRxLink.h>
#include <include/link_api/avbTxLink.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <include/link_api/displayCtrlLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/decLink.h>
#include <include/link_api/encLink.h>
#include <include/alglink_api/algorithmLink_clr.h>
#include <include/alglink_api/algorithmLink_imagePreProcess.h>
#include <include/alglink_api/algorithmLink_imgPyramid.h>
#include <include/alglink_api/algorithmLink_fpCompute.h>
#include <include/alglink_api/algorithmLink_objectClassification.h>
#include <include/alglink_api/algorithmLink_sfm.h>
#include <include/alglink_api/algorithmLink_fcw.h>
#include <src/hlos/common/appCtrlLink.h>
#include <src/include/chains_common_surround_view.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Maximum Number of LVDS cameras supported by the board
 *
 *******************************************************************************
 */
#define SV_NUM_VIEWS                    (SRV_NUM_VIEWS)
#define VIDEO_SENSOR_MAX_LVDS_CAMERAS   (8)
#define LVDS_CAPTURE_WIDTH              (SRV_LVDS_CAPTURE_WIDTH)
#define LVDS_CAPTURE_HEIGHT             (SRV_LVDS_CAPTURE_HEIGHT)

#define SV_INPUT_WIDTH                  (LVDS_CAPTURE_WIDTH)
#define SV_INPUT_HEIGHT                 (LVDS_CAPTURE_HEIGHT)

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define TIGHT_SYNC_DELTA_IN_MSEC              (16)
#define LOOSE_SYNC_DELTA_IN_MSEC              (0x7FFFFFFF)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC     (33)
#define LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC     (0x7FFFFFFF)


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

 typedef enum {
     CHAINS_DISPLAY_TYPE_LCD_7_INCH = 0,
     /**< Output displayed on 7 inch LCD */
     CHAINS_DISPLAY_TYPE_LCD_10_INCH,
     /**< Output displayed on 10-inch LCD */
     CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200,
     /**< Output is displayed on 10Inch 1920x1200 LDC */
     CHAINS_DISPLAY_TYPE_HDMI_720P,
     /**< Output displayed on HDMI in 720P resolution */
     CHAINS_DISPLAY_TYPE_HDMI_1080P,
     /**< Output displayed on HDMI in 1080P resolution */
     CHAINS_DISPLAY_TYPE_FPD
     /**< Output displayed via FPD resolution */
 } Chains_DisplayType;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */
Void ChainsCommon_SingleCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight,
                        Chains_CaptureSrc captureSrc
                        );

Void ChainsCommon_MultiCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 numLvdsCh);

Void ChainsCommon_GetDisplayWidthHeight(
                            Chains_DisplayType displayType,
                            UInt32 *displayWidth,
                            UInt32 *displayHeight
                            );

Void ChainsCommon_StructureFromMotion_SetParams(
        SfmMain_CreateParams *mainprms,
        SfmLinearTwoView_CreateParams *ltvprms,
        SfmMap_CreateParams *mapprms,
        UInt32 numCams,
        UInt32 maxNumPoints
        );

Void ChainsCommon_SetGrpxSrcPrms(
                                GrpxSrcLink_CreateParams *pPrm,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                );

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Char Chains_readChar();

/**
 *******************************************************************************
 *
 * \brief   Read an integer from UART or CCS console
 *
 * \return integer that is read
 *
 *******************************************************************************
*/
Int32 Chains_readInt();
/**
 *******************************************************************************
 *
 * \brief   Load Calculation enable/disable
 *
 *          This functions enables load profiling. A control command
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START is passed to chianed links.
 *          If parameter Enable is set true Load profiling is enabled.
 *          If printStatus is set true a System CMD to Print CPU load,
 *          Task Laod and Heap status information is sent
 *          While creating enable = TRUE , printStatus & printTskLoad = FALSE
 *          While deleting enable = FALSE , printStatus & printTskLoad = TRUE
 *
 * \param   enable               [IN]   is set true Load profiling
 *
 * \param   printStatus          [IN] true a System CMD
 *
 * \param   printTskLoad         [IN]  true a Print CPU load
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Chains_prfLoadCalcEnable(Bool enable,
                               Bool printStatus,
                               Bool printTskLoad);

/**
 *******************************************************************************
 *
 * \brief   Print Memory Heap Statistics
 *
 *          This function send a system control message
 *           to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_memPrintHeapStatus();
Void ChainsCommon_PrintStatistics();
/**
 *******************************************************************************
 *
 * \brief   common APP CTRL Link commands for initialization
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_appCtrlCommonInit();

/**
 *******************************************************************************
 *
 * \brief   common APP CTRL Link commands for de intialization
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_appCtrlCommonDeInit();

Int32 ChainsCommon_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad);
Int32 ChainsCommon_prfCpuLoadPrint();
Int32 ChainsCommon_memPrintHeapStatus();
Int32 ChainsCommon_statCollectorPrint();
Int32 ChainsCommon_statCollectorReset();
void  ChainsCommon_printCpuStatus();

Int32 ChainsCommon_DualDisplay_StartDisplayCtrl(
Chains_DisplayType lcdType, UInt32 displayLCDWidth, UInt32 displayLCDHeight);

Void ChainsCommon_SetDisplayPrms(
                                DisplayLink_CreateParams *pPrm_Video,
                                DisplayLink_CreateParams *pPrm_Grpx,
                                Chains_DisplayType displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight);
Int32 ChainsCommon_StartDisplayCtrl(UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight);
Int32 ChainsCommon_StopDisplayCtrl();

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

Void ChainsCommon_SurroundView_SetAdaptiveBowlParams(
                            AlgorithmLink_AdaptiveBowlCreateParams *pPrm,
                            UInt16 svInWidth,
                            UInt16 svInHeight,
                            UInt16 svOutWidth,
                            UInt16 svOutHeight,
                            UInt16 svNumViews,
                            Int16  svCarBoxWidth,
                            Int16  svCarBoxHeight);

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

