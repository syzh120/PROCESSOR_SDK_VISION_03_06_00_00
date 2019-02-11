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
 * \version 0.0 (May 2014) : [YM] First version ported to linux
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

#include <src/hlos/common/chains_common.h>

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
typedef enum {

    CHAINS_CAPTURE_INTF_VIP,
     /**< LVDS Capture Interface
      */
    CHAINS_CAPTURE_INTF_CSI2CAL,
     /**< CSI2 CAL Interface
      */
    CHAINS_CAPTURE_INTF_ISS,
    /**< CSI2 CAL Interface with ISS
         Supported on TDA2PX */
} Chains_CaptureIntf;

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

/**
 *******************************************************************************
 *
 *  \brief  Chain Parameters.
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 algProcId;
    /**<  Processor ID on which algorithm runs for
     *    - Frame copy algorithm use-case
     *    - DMA SW MS algorithm use-case
     */

    UInt32 numLvdsCh;
    /**< Number of channels of LVDS to enable */

    Chains_DisplayType displayType;
    /**< LCD/HDM display */

    Chains_CaptureSrc captureSrc;
    /**< OV/HDMI-720p/HDMI-1080p capture */

    AlgorithmLink_SrvOutputModes svOutputMode;
    /**< To slect 2D vs 3D Surround View (SRV) Alg */
    UInt32 numPyramids;
    /**< numPyramids - used to select Alg with One/Two Pyramid Mode in  Dense Optical Flow*/
    Bool enableCarOverlayInAlg;
    /**< Set to 1, if DSP need to create the car image, apply only for 2D SRV */

    Bool enableAutoCalib;
    /**< Set to 1, if auto calibration is called to get initial calibration matrix */

    Bool enablePersmatUpdate;
    /**< Set to 1, if initial calibration matrix is updated by Harris corner detection + BRIEF */

    Chains_AutoCalibrationParams calibrationParams;
    /* Advanced Settings for AutoCalibration */

    char sensorName[ISS_SENSORS_MAX_NAME];
    /**< Name of the sensor, used by the ISS usecases */
    IssM2mIspLink_OperatingMode ispOpMode;
    /**< ISP Operation Mode */
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
 * \brief   Single Channel Capture to Frame Copy on A15 to Sgx Display usecase function
 *
 *          This functions creates capture Link on IPU and Alg link on A15
 *          connects them through IPC links
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/

Void chains_vipSingleCamFrameCopySgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to OpenCL Frame Copy on A15 to Sgx Display
 *         usecase function
 *
 *          This functions creates capture Link on IPU and Alg link on A15
 *          connects them through IPC links
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/

Void chains_vipSingleCamOpenCLFrameCopySgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to OpenCV Canny on A15 to Sgx Display usecase function
 *
 *          This functions creates capture Link on IPU and Alg link on A15
 *          connects them through IPC links
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/

Void chains_vipSingleCamOpenCVCannySgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to Sgx Display usecase function
 *
 *          This functions creates capture Link on IPU and NULL link on A15
 *          connects them through IPC links
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to Sgx Display usecase with Autosar function
 *
 *          This functions creates capture Link on IPU and NULL link on A15
 *          connects them through IPC links
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_SgxDisplay_Autosar(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   8ch Channel LVDS Capture to Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_8ch_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   1ch Channel LVDS Capture to Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleCam_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel LVDS Capture to Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
*******************************************************************************
*
* \brief   4ch Channel LVDS Capture Scale Encode Null usecase function
*
* \param   chainsCfg         [IN] Chains_Ctrl
*
*******************************************************************************
*/
Void chains_lvdsVipMultiCam_vpeEncNull(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel LVDS Capture, 3D SRV, DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_Sgx3Dsrv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel LVDS Capture, Adaptive 3D SRV,
 *              DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_Sgx3D_adaptive_srv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel LVDS 2 MP Capture, 3D SRV, DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam2mp_Sgx3Dsrv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel CSI2 Capture, 3D SRV, DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_Sgx3Dsrv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel CSI2 Capture, M4 Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_View(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel CSI2 Capture, SRV Calibration
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_csi2Cal_srvCalibration_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel LVDS Capture, SRV Calibration use case function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_srvCalibration_Display(
                Chains_Ctrl *chainsCfg,
                Chains_CaptureIntf captureIntf);

/**
 *******************************************************************************
 *
 * \brief   4ch Channel CSI2 Capture, 3D SRV, Car Black Box DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   3D Perception demo (4 channel Structure from motion (SfM))
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_3d_perception(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   2ch 2560x720 OV490 Capture, 3D SRV, DRM Display usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_ov490VipMultiCam_Sgx3Dsrv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Creates capture + encode + Decoder + sgxDisplay chain
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_Enc_Dec_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   AvbRx + Decoder + sgxDisplay chain
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_AvbRxDecodeSgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   AvbRx + Decoder + sgx 3D SRV Display chain
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_AvbRxSgx3DSrv(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   AvbRx + Decoder + sgx 3D SRV Display + 264 encode + Null
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_avbrxSrvDisplayAvbtx(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   CApture + EVE framecopy + sgxDisplay chain
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCamFrmcpyEve_SgxDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to Sgx to display on IPU usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_Sgx_IpuDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to Sgx to dual display on IPU usecase function
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void chains_vipSingleCam_SGX_IpuDualDisplay(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture to Sgx with all connector links and framecopy
 *
 * \param   chainsCfg         [IN] Chains_Ctrl
 *
 *******************************************************************************
 */
Void chains_vipSingleCamConnectorLinksA15SgxDisplay(Chains_Ctrl *chainsCfg);

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
Char Chains_menuRunTime();

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for 3D SRV
 *
 *          This functions displays the run time options available for 3D SRV
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *
 * \return  char input by uart on success
 *******************************************************************************
*/
Char Chains_menu3DSrvRunTime();

/**
 *******************************************************************************
 *
 * \brief   Adaptive SRV Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *
 * \return  char input by uart on success
 *******************************************************************************
*/
Char Chains_adaptiveMenuRunTime();

/**
 *******************************************************************************
 *
 * \brief   Single Channel ISS usecase
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issIspSimcop_Display(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Multi Channel ISS 3D SRV using SGX
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_issMultiCamIspSgx3DSrv_SgxDisplay(Chains_Ctrl *chainsCfg);

Void chains_issMultiCaptIsp2mp_Sgx3Dsrv(Chains_Ctrl *chainsCfg);

Void chains_issMultiCaptIsp2mp_Sgx3Dsrv_adaptive(Chains_Ctrl *chainsCfg);


Void Chains_nullSrc_DecodeDisplay(Chains_Ctrl *chainsCfg);
Void Chains_dispDistSrc_Display(Chains_Ctrl *chainsCfg);

Void Chains_cascadeRadarCapture(Chains_Ctrl *chainsCfg);
Void Chains_cascadeRadarDataCollect(Chains_Ctrl *chainsCfg);

#if defined(OPENVX_INCLUDE)
/**
 *******************************************************************************
 *
 * \brief   Function to run openvx conformance test
 *
 *******************************************************************************
*/
int vx_conformance_test_main(int argc, char* argv[]);
void TestModuleRegister();
void TestModuleUnRegister();
void vx_tutorial_run_interactive();
#endif


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
    pPrm->captureSrc = CHAINS_CAPTURE_SRC_OV10635;
    /* TBD : Initialize numLvdsCh */
    pPrm->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
    pPrm->numPyramids = 0;
    pPrm->enableCarOverlayInAlg = 0;
    pPrm->enableAutoCalib = 0;
    pPrm->enablePersmatUpdate = 0;
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

