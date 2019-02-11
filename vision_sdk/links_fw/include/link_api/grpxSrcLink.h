/*
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
*/

/**
 *******************************************************************************
 *
 *   \ingroup SAMPLE_MODULE_API
 *   \defgroup GRPX_SRC_LINK_API Grpx Source Link API
 *
 *   Grpx source Link can be used for the following  purposes
 *     1. For testing a link that doesnot take capture data
 *     2. For generating logo and sending it to Display
 *     3. For printing stats on the display
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file grpxSrcLink.h
 *
 * \brief Grpx Src link API public header file.
 *
 * \version 0.0 (Oct 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef GRPX_SRC_LINK_H_
#define GRPX_SRC_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>
#include <include/link_api/system_const.h>

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Max input queues supported by Grpx Src Link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define GRPX_SRC_LINK_MAX_IN_QUE        (1U)

/**
 *******************************************************************************
 *
 * \brief Max output queues supported by Grpx Src Link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define GRPX_SRC_LINK_MAX_OUT_QUE        (1U)

/* @} */

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup GRPXSRC_LINK_API_CMD Grpx Src Link Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *   \brief Link CMD: Print the passed string on display
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param GrpxSrcLink_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define GRPX_SRC_LINK_CMD_PRINT_STRING              (0x5001U)

/**
 *******************************************************************************
 *   \brief Link CMD: Print the passed string on display with out clear
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param GrpxSrcLink_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define GRPX_SRC_LINK_CMD_PRINT_STRING_WO_CLEAR     (0x5002U)

/**
 *******************************************************************************
 *   \brief Link CMD: SRV Calibration Graphics Parameters
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param GrpxSrcLink_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define GRPX_SRC_LINK_CMD_SRV_CALIB_PARAM           (0x5003U)

/**
 *******************************************************************************
 *   \brief Link CMD: Print the passed image on display
 *
 *   Command used to change the overlay to be printed
 *******************************************************************************
 */
#define GRPX_SRC_LINK_CMD_NEW_OVERLAY (0x5004U)


/**
 *******************************************************************************
 *   \brief Link CMD: Stereo Calibration Graphics Parameters
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param GrpxSrcLink_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM     (0x5005U)

/* @} */



/******************************************************************************
 *
 *  Data structures
 *
*******************************************************************************
*/

/**
*******************************************************************************
 * \brief Grpx src link create parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 dataFormat;
    /**< Valid values of type System_VideoDataFormat
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     *   - SYSTEM_DF_BGRA16_4444
     */

    UInt32 width;
    /**< channel resolution - width */

    UInt32 height;
    /**< channel resolution - height */

} GrpxSrcLink_BufferInfo;

/**
*******************************************************************************
 * \brief Grpx src logo parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 startX;
    /**< X position where the logo starts */

    UInt32 startY;
    /**< Y position where the logo starts */
} GrpxSrcLink_LogoParameters;

/**
*******************************************************************************
 * \brief Grpx src Optical Flow Legend parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 lutId;
    /**< LUT bitmap to use */

    UInt32 fps;
    /**< Optical flow frame-rate */

} GrpxSrcLink_OpticalFlowParameters;


/**
*******************************************************************************
 * \brief Grpx src Stats Print parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 startX;
    /**< X position where the stats print starts */

    UInt32 startY;
    /**< Y position where the stats print starts */

} GrpxSrcLink_StatsPrintParams;

/**
*******************************************************************************
 * \brief Grpx src String properties
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 startX;
    /**< X position where the stats print starts */

    UInt32 startY;
    /**< Y position where the stats print starts */

    UInt32 fontType;
    /**< font type */

    char string[128U];
    /**< String to be displayed */

} GrpxSrcLink_StringInfo;

/**
*******************************************************************************
 * \brief Grpx src string runtime print cmd params.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    Int32 duration_ms;
    /**< Duration in ms string should be displayed */

    GrpxSrcLink_StringInfo stringInfo;
    /**< Strings to be displayed */

} GrpxSrcLink_StringRunTimePrintParams;

/**
*******************************************************************************
 * \brief Grpx src link create parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/

typedef struct
{
    UInt32 enable;
    /**< TRUE: draw ultrasonic results generated by link ID,
               ultrasonicResultsLinkId
     */

    UInt32 windowStartX;
    /**< Display window start position */

    UInt32 windowStartY;
    /**< Display window start position */

    UInt32 windowWidth;
    /**< Width of ultrasonic overlay data */

    UInt32 windowHeight;
    /**< Width of ultrasonic overlay data */

} GrpxSrcLink_UltrasonicParams;

typedef struct
{
    Int32 *cornerPointsBuf;
    /**< Corner Point Buffer Address */

    UInt32 cornerPointBufSize;
    /**< Corner Point Buffer Size */

} GrpxSrcLink_SrvCalibPrm;

typedef struct
{
    UInt32 startX;
    /**< StartX */

    UInt32 startY;
    /**< StartY */

    UInt32 width;
    /**< Width */

    UInt32 height;
    /**< Height */

    UInt32 srvOutWidth;
    /**< SRV Output Width */

    UInt32 srvOutHeight;
    /**< SRV Output Height */

} GrpxSrcLink_SrvDisplayPrm;


typedef struct
{
    Int16 *featurePointBuf;
    /**< Feature Point Buffer Address */

    UInt32 featurePointBufSize;
    /**< Feature Point Buffer Size */

    Int16 startIdx;

    Int16 endIdx;

} GrpxSrcLink_StereoCalibPrm;

typedef struct
{
    UInt32                     stereoCalibLayout;
    /**< Flag to enable/disable stereo calibration layout */

    UInt32                     stereoCalibCaptureWidth;
    /**< Width of captured image for stereo calibration */

    UInt32                     stereoCalibCaptureHeight;
    /**< Width of captured image for stereo calibration */

    UInt32                     stereoCalibDisplayWidth;
    /**< Height of displayed image for stereo calibration */

    UInt32                     stereoCalibDisplayHeight;
    /**< Width of displayed image for stereo calibration */

    UInt32                     stereoCalibDisplayStartX;
    /**< Horizontal position of displayed image for stereo calibration */

    UInt32                     stereoCalibDisplayStartY;
    /**< Vertical position of displayed image for stereo calibration */

} GrpxSrcLink_StereoCalibDisplayPrm;



typedef struct
{
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */

    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */

    GrpxSrcLink_BufferInfo      grpxBufInfo;
    /**< Instance of channel information */

    GrpxSrcLink_LogoParameters   logoParams;
    /**< Instance of Logo Parameters */

    GrpxSrcLink_StatsPrintParams   statsPrintParams;
    /**< Instance of stats Parameters */

    GrpxSrcLink_OpticalFlowParameters opticalFlowParams;
    /**< Instance of OF Legend Parameters */

    GrpxSrcLink_UltrasonicParams ultrasonicParams;
    /**< Ultraosnic drawing params */

    UInt32                     logoDisplayEnable;
    /**< Flag to enable/disable logo */

    UInt32                     statsDisplayEnable;
    /**< Flag to enable/disable stats */

    UInt32                     surroundViewEdgeDetectLayoutEnable;
    /**< Flag to enable/disable surround view layout */

    UInt32                     surroundViewPdTsrLayoutEnable;
    /**< Flag to enable/disable surround view + PD/TSR layout */

    UInt32                     surroundViewLdLayoutEnable;
    /**< Flag to enable/disable surround view + LD layout */

    UInt32                     enableJeepOverlay;
    /**< Enable for 2D SRV, Disable for 3D SRV  */

    UInt32                     surroundViewDOFLayoutEnable;
    /**< Flag to enable/disable surround view + dof layout */

    UInt32                     opticalFlowLayoutEnable;
    /**< Flag to enable/disable of Legend */

    UInt32                     pdTsrLdLayoutEnable;
    /**< Flag to enable/disable of specific layout */

    UInt32                     pdTsrLdSofLayoutEnable;
    /**< Flag to enable/disable of specific layout */

    UInt32                     pdTsrLdSofStereoLayoutEnable;
    /**< Flag to enable/disable of specific layout */

    UInt32                     stereoDisparityLayoutEnable;
    /**< Flag to enable/disable stereo view layout */

    UInt32                     tda3xxSvFsRotLayoutEnable;
    /**< Flag to enable/disable surround view + SOF layout */

    UInt32                     tda3xx3DSvLayoutEnable;
    /**< Flag to enable/disable 3D surround viewlayout */

    UInt32                     tda3xxRearView3DSvLayoutEnable;
    /**< Flag to enable/disable RearView + 3D surround viewlayout */

    UInt32                     tda3xx2D3DSvLayoutEnable;
    /**< Flag to enable/disable 3D surround viewlayout */

    System_Standard            tda3x3DSvSrcResolution;
    /**< Will be used print the input stream resolution */

    UInt32                     surroundViewStandaloneLayoutEnable;
    /**< Flag to enable/disable 2D/3D surround view standalone layout */

    UInt32                     disablePreview;
    /**< Applicable only when surroundViewStandaloneLayoutEnable is TRUE.
            TRUE disables the preview and FALSE enables the same. */

    UInt32                     fcAnalytics2LayoutEnable;
    /**< Flag to enable/disable Front Camera Anlytics 2 layout */

    UInt32                     sfmLayoutEnable;
    /**< Flag to enable/disable 3D Perception (SfM) demo layout */

    UInt32                     enableRearViewPanoramaLayout;
    /**< Flag to enable/disable rear view panorama layout */

    UInt32                     enableRVPDisparityLayout;
    /**< Flag to enable/disable rear view panorama disparity layout */

    UInt32                     enableCarOverlay;
    /**< Flag to enable/disable car overlay*/

    UInt32 dataVisDataBwDisplayEnable;
    /**< Draw Data BW visualization on display */

    UInt32 srvCalibLayout;
    /**< Surround View Calibration Layout */

    UInt32 captureWidth;
    /**< Capture Frame Width */

    UInt32 captureHeight;
    /**< Capture Frame Height */

    GrpxSrcLink_SrvDisplayPrm displaySrv2D;
    /**< Surround View Display Parameters for 2D */

    GrpxSrcLink_SrvDisplayPrm displaySrv3D;
    /**< Surround View Display Parameters for 3D */

    GrpxSrcLink_StereoCalibDisplayPrm stereoCalibDisplayPrms;
    /**< Stereo calibration parameters */

    UInt32 surroundViewStandaloneLayout2Enable;
    /**< Flag to enable/disable 2D/3D surround view standalone layout */

    UInt32 semSegOverlay;
    /**< Semantic Segmentation Overlay */

    UInt32 tidlOdOverlay;
    /**< Semantic Segmentation Overlay */

    Bool is2mp;
    /**< Flag to indicate if 2MP Calibration is being used */

} GrpxSrcLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void GrpxSrcLink_CreateParams_Init(
                                GrpxSrcLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief Grpx Src link register and init
 *
 *    - Creates link task
 *    - Registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_init(void);

/**
*******************************************************************************
 *
 * \brief Grpx Src link de-register and init
 *
 *    - deletes link task
 *    - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Grpx src link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 * \param  pPrm  [OUT]  GrpxLink Src Create time Params
 *
 *******************************************************************************
 */
static inline void GrpxSrcLink_CreateParams_Init(GrpxSrcLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(GrpxSrcLink_CreateParams));
    pPrm->enableJeepOverlay = (UInt32) TRUE;
#if defined (DATA_VIS_INCLUDE)
    pPrm->dataVisDataBwDisplayEnable = (UInt32) TRUE;
#else
    pPrm->dataVisDataBwDisplayEnable = (UInt32) FALSE;
#endif
    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
