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
 *
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_CHAIN APIs for selecting the usecase chain.
 *
 * \brief  APIs for selecting the required usecase chain and run
 *         time menu configurations .
 *         It also provide API's for instrumentation of load and heap usage
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains.h
 *
 * \brief APIs for selecting the required usecase chain.
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef _CHAINS_H_
#define _CHAINS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/nullSrcLink.h>
#include <include/link_api/networkTxLink.h>
#include <include/link_api/networkRxLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/displayLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/splitLink.h>
#include <include/link_api/gateLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/tfdtpRxLink.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <include/link_api/displayCtrlLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <include/link_api/grpxSrcLink.h>
#include <src/include/lcd.h>
#include <src/include/board.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <src/include/hdmi_tx.h>
#include <src/include/draw2d.h>
#include <src/include/chains_common_sensor.h>

#include <src/rtos/utils_common/include/utils_uart.h>
#include <src/rtos/utils_common/include/utils_qspi.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_l3_emif_bw.h>
#include <src/rtos/utils_common/include/utils_boot_slaves.h>
#include <src/rtos/utils_common/include/file_api.h>
#include <ti/sysbios/knl/Task.h>

#ifndef RADAR_ONLY
#include <include/link_api/vpeLink.h>
#include <include/link_api/avbRxLink.h>
#include <include/link_api/avbTxLink.h>
#include <include/link_api/decLink.h>
#include <include/link_api/encLink.h>
#include <include/link_api/displayMultiPipeLink.h>
#include <include/link_api/ultrasonicCaptureLink.h>
#include <include/alglink_api/algorithmLink_edgeDetection.h>
#include <include/alglink_api/algorithmLink_frameCopy.h>
#include <include/alglink_api/algorithmLink_safeFrameCopy.h>
#include <include/alglink_api/algorithmLink_dmaSwMs.h>
#include <include/alglink_api/algorithmLink_geometricAlignment.h>
#include <include/alglink_api/algorithmLink_geometricAlignment3D.h>
#include <include/alglink_api/algorithmLink_adaptiveBowl.h>
#include <include/alglink_api/algorithmLink_photoAlignment.h>
#include <include/alglink_api/algorithmLink_synthesis.h>
#include <include/alglink_api/algorithmLink_denseOpticalFlow.h>
#include <include/alglink_api/algorithmLink_vectorToImage.h>
#include <include/alglink_api/algorithmLink_featurePlaneComputation.h>
#include <include/alglink_api/algorithmLink_objectDetection.h>
#include <include/alglink_api/algorithmLink_objectClassification.h>
#include <include/alglink_api/algorithmLink_sparseOpticalFlow.h>
#include <include/alglink_api/algorithmLink_ultrasonicFusion.h>
#include <include/alglink_api/algorithmLink_imagePreProcess.h>
#include <include/alglink_api/algorithmLink_imgPyramid.h>
#include <include/alglink_api/algorithmLink_fpCompute.h>
#include <include/alglink_api/algorithmLink_sceneObstructionDetect.h>
#include <include/alglink_api/algorithmLink_objectDraw.h>
#include <include/alglink_api/algorithmLink_subframeCopy.h>
#include <include/alglink_api/algorithmLink_softIsp.h>
#include <include/alglink_api/algorithmLink_census.h>
#include <include/alglink_api/algorithmLink_stereoPostProcess.h>
#include <include/alglink_api/algorithmLink_disparityHamDist.h>
#include <include/alglink_api/algorithmLink_remapMerge.h>
#include <include/alglink_api/algorithmLink_laneDetect.h>
#include <include/alglink_api/algorithmLink_sfm.h>
#include <include/alglink_api/algorithmLink_fcw.h>
#include <include/alglink_api/algorithmLink_clr.h>
#include <include/alglink_api/algorithmLink_autoChartDetect.h>
#include <include/alglink_api/algorithmLink_poseEstimate.h>
#include <include/alglink_api/algorithmLink_stitching.h>
#include <include/alglink_api/algorithmLink_imageTransform.h>
#include <include/alglink_api/algorithmLink_seamDetection.h>
#include <include/alglink_api/algorithmLink_autoRemap.h>
#include <include/alglink_api/algorithmLink_stereoApp.h>
#ifdef ENABLE_OPENCV
#include <include/alglink_api/algorithmLink_opencvCanny.h>
#include <include/alglink_api/algorithmLink_opencvOpenCLDilation.h>
#ifdef ENABLE_OPENCV_TESTS
#include <include/alglink_api/algorithmLink_opencvTests.h>
#endif
#endif
#ifdef OPENCL_INCLUDE
#include <include/alglink_api/algorithmLink_openClframeCopy.h>
#include <include/alglink_api/algorithmLink_openClCannyEdge.h>
#endif
#include <src/rtos/video_sensor/include/video_sensor.h>
#include <src/rtos/video_sensor/include/video_decdr.h>
#include <src/rtos/video_sensor/include/hdmi_recvr.h>
#endif

#ifndef RADAR_ONLY
#ifdef ISS_INCLUDE
#include <src/rtos/iss/include/algorithmLink_issAewb.h>
#endif
#include <src/rtos/iss/include/iss_sensors.h>
#endif


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

 typedef enum {
     CHAINS_DISPLAY_TYPE_LCD_7_INCH = 0,
     /**< Output displayed on 7-inch LCD */

     CHAINS_DISPLAY_TYPE_LCD_10_INCH,
    /**< Output displayed on 10-inch LCD */

     CHAINS_DISPLAY_TYPE_HDMI_720P,
     /**< Output displayed on HDMI in 720P resolution */

     CHAINS_DISPLAY_TYPE_HDMI_1080P,
     /**< Output displayed on HDMI in 1080P resolution */

     CHAINS_DISPLAY_TYPE_SDTV_NTSC,
     /**< Output displayed on SD TV in NTSC format */

     CHAINS_DISPLAY_TYPE_SDTV_PAL,
     /**< Output displayed on SD TV in PAL format */

     CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM,
     /**< Output displayed on HDMI in XGA resolution using 8bit TDM mode */

     CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200,
     /**< Output is displayed on 10Inch 1920x1200 LDC */

     CHAINS_DISPLAY_TYPE_HDMI_WXGA
     /**< Output displayed on HDMI in WXGA, Supported only on TDA3xx */

 } Chains_DisplayType;

typedef enum {

    CHAINS_CAPTURE_INTF_ISS,
     /**< ISS Capture Interface
      */
    CHAINS_CAPTURE_INTF_VIP,
     /**< LVDS Capture Interface
      */
    CHAINS_CAPTURE_INTF_CSI2CAL,
     /**< CSI2 CAL Interface
      */
    CHAINS_CAPTURE_INTF_AVB,
     /**< AVB Capture Interface
      */
    CHAINS_CAPTURE_INTF_MAX
     /**< Max Capture Interface
      */
} Chains_CaptureIntf;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Chain Parameters.
 *
 *******************************************************************************
*/
typedef struct {
    UInt8 thresholdMode;
    /* Sets Bias for Adaptive Threshold for autocalibration usecase*/

    UInt8 windowMode;
    /* Sets window size for binarization's averager 0 - Original (50 for 720x1280) 1 - New (75 for 720x1280) */

    UInt8 Ransac;
    /* RANSAC for corner detect 1 - On 0 - Off*/

    UInt8 PoseRansac;
    /* RANSAC for Pose Estimation 1 - On 0 - Off*/

    UInt8 SingleChartPose;
    /* Single Chart Pose Estimation 1 - On 0 - Off (Default)*/
} Chains_AutoCalibrationParams;

typedef struct {

    UInt32 algProcId;
    /**<  Processor ID on which algorithm runs for
     *    - Frame copy algorithm use-case
     *    - DMA SW MS algorithm use-case
     */
    Chains_DisplayType displayType;
    /**< LCD/HDM display */
#ifndef RADAR_ONLY
    UInt32 numLvdsCh;
    /**< Number of channels of LVDS to enable */

    Chains_CaptureSrc captureSrc;
    /**< OV/HDMI-720p/HDMI-1080p capture */

    UInt32 numPyramids;
    /**< numPyramids - used to select Alg with One/Two Pyramid Mode in  Dense Optical Flow*/

    Bool   issLdcEnable;
    /**< TRUE: LDC is enabled in ISS use-cases
     *       ONLY applicable for TDA3x platform
     */

    Bool   issVtnfEnable;
    /**< TRUE: VTNF is enabled in ISS use-cases
     *       ONLY applicable for TDA3x platform
     */

    IssM2mIspLink_OperatingMode ispOpMode;
    /**< WDR mode, disabled, 2 pass or 1 pass
     *       ONLY applicable for TDA3x platform
     */

    AlgorithmLink_SrvOutputModes svOutputMode;
    /**< To slect 2D vs 3D Surround View (SRV) Alg */

    Bool enableCarOverlayInAlg;
    /**< Set to 1, if DSP need to create the car image, apply only for 2D SRV */

    char sensorName[ISS_SENSORS_MAX_NAME];

    Bool byPassSensorCfg;
    /**< Some of the sensor don't require explict programming. The required
            configurations are pre-stored. In such cases programming is to be
            by-passed */
#endif
    Chains_AutoCalibrationParams calibrationParams;
    /* Advanced Settings for AutoCalibration */
    
    Bool linux_InitComplete;
} Chains_Ctrl;

/*******************************************************************************
 *  Extern's
 *******************************************************************************
 */
extern Chains_Ctrl gChains_usecaseCfg;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 *******************************************************************************
*/
Void Chains_main();

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCam_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with Autosar function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCam_Display_Autosar(Chains_Ctrl *chainsCfg);

#ifdef ROBUST_RVC_INCLUDE
/**
 *******************************************************************************
 *
 * \brief   Single Channel RVC SWCRC :Capture Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleRvcCamCrc_Display(Chains_Ctrl *chainsCfg);
#endif

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Dual Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_DualDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Dual Display + ED usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_DualDisplayEdgeDetection(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with frame copy algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCameraFrameCopy(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with OpenCV Canny algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCamOpenCVCanny(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with OpenCV OpenCL Dilation
 *          algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCamOpenCVOpenCLDilation(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with OpenCV Tests
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCamOpenCVTests(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with frame copy algorithm
 *          with FFI example
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCameraSafeFrameCopy(Chains_Ctrl *chainsCfg);
/* OpenCL Use Case */
#ifdef OPENCL_INCLUDE
Void Chains_vipSingleCameraOpenCLFrameCopy(Chains_Ctrl *chainsCfg);
Void Chains_vipSingleCameraOpenCLCannyEdge(Chains_Ctrl *chainsCfg);
#endif
/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Edge Detection usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraEdgeDetection(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with Analytics algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCameraAnalyticsTda3xx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with Analytics algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCameraAnalytics2(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase with Analytics algorithm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_vipSingleCameraAnalyticsTda2xx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Optical Flow usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraDenseOpticalFlow(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Single camera Pedestrain + Traffic sign Detection
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraObjectDetect(Chains_Ctrl * chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Single camera Pedestrain + Traffic sign Detection
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraObjectDetect2Tda3xx(Chains_Ctrl * chainsCfg);


/**
 *******************************************************************************
 *
 * \brief Single camera Lane Detection
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraLaneDetect(Chains_Ctrl * chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Single camera Sfm
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraSfm(Chains_Ctrl * chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Single camera Clr
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraTlr(Chains_Ctrl * chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Single camera Sparse Optical Flow
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraSparseOpticalFlow(Chains_Ctrl * chainsCfg);


/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function for TDA2xx
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSingleCam_Display(Chains_Ctrl *chainsCfg);


/**
 *******************************************************************************
 *
 * \brief   Multi Channel Capture Display usecase function for TDA2xx
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipMultiCam_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   8 Channel Capture Display usecase function for TDA2xx
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVip8Cam_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Multi Channel Capture Display usecase function for TDA2xx
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipMultiCam_Display_tda3xx(Chains_Ctrl *chainsCfg);


/**
 *******************************************************************************
 *
 * \brief   Dual Channel Capture Dual Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipDualCam_DualDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Surround View of 4Ch LVDS capture on TDA2xx and TDA2Ex
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSurroundViewStandalone(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Surround View of 4Ch LVDS capture on TDA3x
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSurroundView(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Surround View of 4Ch LVDS capture + FrontCam Analytics + Ultrasound
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSurroundViewAnalyticsUltrasound(Chains_Ctrl *chainsCfg);


/**
 *******************************************************************************
 *
 * \brief   Single Stereo Camera Disparity Display for TDA2x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSingleStereo(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Stereo online stereo Calibration for TDA2x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSingleStereoAutoCalib(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Stereo offline stereo  Calibration for TDA2x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_lvdsVipSingleStereoCalibration(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief Avb Mcv Capture + Decode + Diaplay
 *
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_avbRx_Dec_Display_AvbTx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   AVB ED usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void Chains_avbRxSrv_Display_AvbTx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief 1Ch VIP Capture + AVB Tx
 *
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_avbTxVipSigleCam(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel capture DssWB CRC Display usecase function
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCam_DisplayWbCrc(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel capture Enc Dec VPE Display usecase function
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCam_EncDec_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Subframe Capture Display usecase function
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraSubFrameCopy(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   ISS Based capture, m2m isp processing, m2m simcop processing
 *          and display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issIspSimcop_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief TFDTP Capture + Diaplay
 *
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_tfdtpRx_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   ISS Based multi channel capture, m2m isp processing,
 *              m2m simcop processing & display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspSimcopSv_Display(Chains_Ctrl *chainsCfg);


/**
 *******************************************************************************
 *
 * \brief   ISS Based multi channel capture, m2m isp processing,
 *              & display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_srvCalibration_Display(
                    Chains_Ctrl *chainsCfg,
                    Chains_CaptureIntf captureIntf);


/**
 *******************************************************************************
 *
 * \brief   ISS Based multi channel capture, m2m isp processing,
 *              LDC based DeWarp, Synthesis & 3D + 2D surround view display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIsp2d3d3dSv_Display(Chains_Ctrl *chainsCfg);

#if defined(UC_iss_mult_capture_isp_dewarp_3dsv_tda3xx) \
    || defined(UC_iss_mult_capture_isp_simcop_sv_tda3xx) \
    || defined(UC_fast_boot_iss_capture_isp_simcop_pd_display)
/**
 *******************************************************************************
 *
 * \brief   ISS Based multi channel capture, m2m isp processing,
 *              LDC based DeWarp, Synthesis & 3D surround view display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspDewarp3dSv_Display(
                        Chains_Ctrl *chainsCfg,
                        AlgorithmLink_SrvOutputModes ucSrvOutMode);
#endif

/**
 *******************************************************************************
 *
 * \brief   ISS Based multi channel capture, m2m isp processing,
 *              LDC based DeWarp, Synthesis & RearView + 3D surround view display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspDeWarpRearView3dSv_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Simcop based stereo engine on TDA3x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspSimcop_Stereo(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   DeWarp based stereo engine on TDA3x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspDeWarp_Stereo(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   DeWarp based stereo engine on TDA3x with advanced features
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspDeWarp_StereoPlus(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Multi Channel video from ISS using multiple csi2 instance
 *          and display each channel separately
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_iss_multi_inst_capture_display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Online stereo rectification on TDA3x
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptSteroAutoCalib(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   ISS Based capture, m2m isp processing and display usecase
 *          It captures monochroma data from the sensor, processes it in
 *          ISP and displays the output of the ISP.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_monochrome_issIsp_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Fast boot usecase showing ISS Based capture, m2m isp processing,
 *          Pedestrian Detect algorithm integration and display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_fastBootIssIspSimcop_pd_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Stereo Camera Soft ISP and Display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipStereoOnlyDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Stereo Calibration
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipStereoCalibration(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Pre-recorded data input to Stereo
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_networkStereoDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network and display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkRxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network, decode and display
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkRxDecDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data from camera and stream over network
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkTxCapture(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data from camera, encode and stream over network
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkTxEncCapture(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Networking use-cases
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkRxTx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   NullSrc File read display use-case
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_nullSrc_DecodeDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   TIDA0455 + OV490 based capture + SV
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_ov490VipSurroundViewStandalone(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network, PD/TSR/LD/SOF with Stereo
 *          from live camera
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipStereoCameraAnalytics2(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network and do front cam analytics
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_networkRxCameraAnalyticsTda2xx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network and do front cam analytics
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_fileRxCameraAnalyticsTda2xx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over network or VIP and do front cam analytics
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_singleCameraAnalyticsTda2xx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Vehicle detect in night mode
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraOdNight(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture Data over Radar
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarDetectionOnly(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture and Process Radar Data
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarDataProcess(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture, Process Radar Data, and Overlay with camera image
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_radarCameraOverlay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Capture & Display, captures from SAT0088, OV10635 via UB964, CSI2
 *              interface of TDA2Ex and Displays the same.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_csi2CalMultiCam(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   DSP based surround view, captures from SAT0088, OV10635 via UB964,
 *              CSI2 interface of TDA2Ex, performs photometric alignment, uses
 *              DSP based SRV algorithim to construct SRV.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_csi2CalSVStandalone(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Rear View Panorama of 4Ch LVDS capture on TDA2x
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_RVP(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   VIP Capture and send frame id as metadata an dcapture it through
 *          DSS WB
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCam_Display_Metadata(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Rear View Panorama of 4Ch LVDS capture on TDA3x
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_RVP_TDA3X(Chains_Ctrl *chainsCfg);

/**
 * \brief   VIP Capture and run OpenVX Algo plugin on captured frame and
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_vipSingleCameraOpenVx(Chains_Ctrl *chainsCfg);

/**
 * \brief   TIDL File io usecase
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_tidl(Chains_Ctrl *chainsCfg);

/**
 * \brief   TIDL semantic segmentation
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_semSeg(Chains_Ctrl *chainsCfg);

/**
 * \brief   TIDL object detection
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_tidlOD(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Rear View Panorama of 4Ch LVDS capture on TDA3x RSVP LDC LUT Gen
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void manualRSVPLUTGen(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   nullSrc display
 *          This function run the usecase which read YUV frame, and displays it.
 *          It also duplicate the input from NullSrc and give it to null Link.
 *          This usecase will give an understanding about how nullSrc and null
 *          link is working.
 *
 *
 *******************************************************************************
*/
Void Chains_nullSrc_display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Camera/Radar data capture and Radar processing
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_cameraRadarCapture_display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   TIDL object detection and Radar Capture/Processing
 *          then display the output
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_tidlOD_radarProcess_display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   M4 based chain for Linux builds, with early capture and display
 *          followed by weston background disply after Linux is initialized
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_earlyCaptureLateWeston(Chains_Ctrl *chainsCfg);
/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *
 * \return  char input by uart on success
 *******************************************************************************
*/
char Chains_menuRunTime();

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

/**
 *******************************************************************************
 *
 * \brief   Reset Memory DDR Statistics
 *
 *          This function send a system control message
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_statCollectorReset();


/**
 *******************************************************************************
 *
 * \brief   Print Memory DDR Statistics
 *
 *          This function send a system control message
 *          SYSTEM_COMMON_CMD_PRINT_STAT_COLL to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_statCollectorPrint();

/**
 *******************************************************************************
 *
 * \brief   Print Load Calculation.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfCpuLoadPrint();

/**
 *******************************************************************************
 *
 * \brief   Get IP Addr for the system
 *
 * \param   ipAddr  [OUT] IP address as a string
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
 */
Int32 Chains_getIpAddr(char *ipAddr);

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
char Chains_readChar();


/**
 *******************************************************************************
 *
 * \brief   Run DMA standalone test
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_runDmaTest();

/**
 *******************************************************************************
 *
 * \brief   Radar Resolution Mode Menu selection
 *
 *          This functions displays the radar resolution mode options available
 *
 * \return  char input by uart on success
 *******************************************************************************
*/
char Chains_menuRadarResolutionMode();

#ifdef TDA2EX_BUILD
/**
 *******************************************************************************
 *
 * \brief   Ethernet PHY selection for TDA2Ex use-cases
 *
 *          This functions selects Ethernet PHY and Port for TDA2ex EVM.
 *
 * \return  None
 *******************************************************************************
*/
void ChainsCommon_tda2exSelectPHY(Chains_CaptureSrc captureSrc);
#endif

/**
 ******************************************************************************
 *
 * \brief Set Network Rx mode for Null Source link
 *
 * \param  pPrm  [IN]  NullSourceLink Create time Params
 *
 * \return  None
 ******************************************************************************
 */
void ChainsCommon_networkRxSetMode(NetworkRxLink_CreateParams *pPrm);

/**
 ******************************************************************************
 *
 * \brief Set Network Tx mode for Null link
 *
 * \param  pPrm  [IN]  NullLink Create time Params
 *
 * \return  None
 ******************************************************************************
 */
void ChainsCommon_networkTxSetMode(NetworkTxLink_CreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief   Set default values to chains control parameters
 *
 *******************************************************************************
*/
static inline Void Chains_Ctrl_Init(Chains_Ctrl *pPrm)
{
    memset(pPrm, 0, sizeof(Chains_Ctrl));

    pPrm->algProcId = SYSTEM_PROC_DSP1;
    pPrm->displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
#ifndef RADAR_ONLY
    pPrm->numLvdsCh = VIDEO_SENSOR_NUM_LVDS_CAMERAS;
    pPrm->captureSrc = CHAINS_CAPTURE_SRC_OV10635;
    pPrm->numPyramids = 0;
    pPrm->issLdcEnable = FALSE;
    pPrm->issVtnfEnable = FALSE;
    pPrm->ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
    pPrm->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
    pPrm->enableCarOverlayInAlg = 0;
#endif
    pPrm->calibrationParams.thresholdMode = 0;
    pPrm->calibrationParams.windowMode = 0;
    pPrm->calibrationParams.Ransac = 0;
    pPrm->calibrationParams.PoseRansac = 0;
    pPrm->calibrationParams.SingleChartPose = 0;
}


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

