/*
* module name       :TI Lane Detection 
*
* module descripton :Lane Detection and departure warning using TI’s C66x DSP
*
*/
/*
 
Copyright (c) [2014] – [2017] Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.
 
Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
 
Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
 
*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
 
*       any redistribution and use are licensed by TI for use only with TI Devices.
 
*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
 
If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
 
*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
 
*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
 
Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
 
DISCLAIMER.
 
THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/

/**
 *  @file       ild_ti.h
 *  @author  Prashanth R V
 *  @brief     This file defines ivision interface for TI Lane Detection algorithm
 *  @version 1.0 (June 2014) : Base version.
 *  @version 2.0 (Jan 2015) : Updated version.- Included warning information paramenters
 */

/** @ingroup    ti_ivision_LD*/
/*@{*/
#ifndef ILD_TI_H
#define ILD_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The unique const funtion table for the LANE_DETECTION.
 */
extern const IVISION_Fxns LD_TI_VISION_FXNS;

/**
* @brief IRES interface of the LANE_DETECTION app
*/
extern const IRES_Fxns LD_TI_IRES;

/**
* @brief Max Lane points allowed by LD - Assuming 10% of points belong
* to lane, but it is lot lesser than this in reality
*/
#define LD_TI_MAXLANEPOINTS (10000)

/**
* @brief Max theta bins allowed by LD - Currently set to 160
* Accordingly the Cos and Sin tables have to be modified.
* The 160 bins cover angle in degrees from range (-80 to +79)
*/
#define LD_TI_MAXNUMTHETA   (160)

/**
* @brief Max Rho range allowed by LD -, as 
* maxRho = sqrt(srcW^2 + srcH^2) = sqrt(1920^2 + 1080^2) = 2203
* and Rho resolution = 2 (0,maxRho).
*/
#define LD_TI_MAXNUMRHO     (2203)

/**
* @brief Maximum number of edge pixels - Typically assumed
* that 10% of the image pixels would be edge pixels
* Hence, this is set to 10000
* Aligned to be a multiple of 128 
*/

#define LD_TI_MAXNUMEDGES   (10112)

/**
* @brief Max width allowed by LD
*/
#define LD_TI_MAXWIDTH      (1920)

/**
* @brief Max height allowed by LD
*/
#define LD_TI_MAXHEIGHT     (1080)

/**
* @brief Maximum number of Hough space maxima Detections 
* allowed by LD
*/

#define LD_MAX_DET_HOUGH_MAXIMAS (10)

/**
* @brief Maximum number of Hough space maximas to be tracked 
* allowed by LD
* This should be less than or equal to LD_MAX_DET_HOUGH_MAXIMAS
*/

#define LD_MAX_TRACK_HOUGH_MAXIMAS (5)

/**
* @brief Minimum number of Hough space maxima Detections 
* allowed by LD
*/

#define LD_MIN_DET_HOUGH_MAXIMAS (1)

/**
* @brief Minimum number of Hough space maximas to be tracked 
* allowed by LD
* In case tracking is disabled, the number of numHoughMaximasTrack
* is used for inverse Hough mapping. So, it can be set equal to 
* numHoughMaximasDet, but should be less than equal to
* LD_MAX_TRACK_HOUGH_MAXIMAS
*/

#define LD_MIN_TRACK_HOUGH_MAXIMAS (1)

/**
  @brief Error code returned by the LD algorithm

  ILD_ERRORTYPE_MAXNUMEDGES_EXCEEDED: The number of
  edges are more than edges allocated by LD algorithm

  ILD_ERRORTYPE_MAXNUMTHETA_EXCEEDED: The max theta
  is beyond LD_TI_MAXNUMTHETA

  ILD_ERRORTYPE_MAXNUMRHO_EXCEEDED: The max rho
  is beyond LD_TI_MAXNUMRHO

  ILD_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are
  beyond supported

  ILD_ERRORTYPE_INVALID_ROI_DIMS: ROI dimensions are
  beyond image dimensions

  ILD_ERRORTYPE_INVALID_THETA_RANGE: The theta range
  specified by user is invalid, example if start theta is greater than
  end theta or if start/end theta is greater than max theta
  supported

  ILD_ERRORTYPE_INVALID_RHO_RANGE: The rho range
  specified by user is invalid, example if departRhoMax/Min is greater than
  greater than max rho supported

  ILD_ERRORTYPE_INVALID_CANNY_THRESHOLD: The canny
  threshold specified is invalid, example if low-threshold is
  greater than high-threshold

  ILD_ERRORTYPE_LD_CREATE_FAIL: Failure while creating LD

  ILD_ERRORTYPE_INVALID_KF_PARAMS: Failure to indicate
  invalid Kalman Filter params

  ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMASDET: Error to
  indicate that the user defined Hough maximas to be detected is greater
  than the max supported by LD given by LD_MAX_DET_HOUGH_MAXIMAS
  or less than LD_MIN_DET_HOUGH_MAXIMAS

    ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMASTRACK: Error to
  indicate that the user defined Hough maximas to be tracked is greater
  than the max supported by LD given by LD_MAX_TRACK_HOUGH_MAXIMAS
  or less than LD_MIN_TRACK_HOUGH_MAXIMAS

  ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMAS: Error to indicate
  that the user has defined more Hough maximas to be tracked than detected
*/
typedef enum
{
  ILD_ERRORTYPE_MAXNUMEDGES_EXCEEDED = IVISION_CUSTOMFAILBASE,
  ILD_ERRORTYPE_MAXNUMTHETA_EXCEEDED,
  ILD_ERRORTYPE_MAXNUMRHO_EXCEEDED,
  ILD_ERRORTYPE_INVALID_IMAGE_DIMS,
  ILD_ERRORTYPE_INVALID_ROI_DIMS,
  ILD_ERRORTYPE_INVALID_THETA_RANGE,
  ILD_ERRORTYPE_INVALID_RHO_RANGE,
  ILD_ERRORTYPE_INVALID_CANNY_THRESHOLD,
  ILD_ERRORTYPE_LD_CREATE_FAIL,
  ILD_ERRORTYPE_INVALID_KF_PARAMS,
  ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMASDET,
  ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMASTRACK,
  ILD_ERRORTYPE_INVALID_MAXHOUGHMAXIMAS,
  ILD_ERRORTYPE_MAX_ERROR_CODE
} ILD_ErrorType;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  LD_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by algorithm. For lane detection algorithm, only luma data is sufficient
  
*/
typedef enum
{
  LD_BUFDESC_IN_IMAGEBUFFER = 0,
  LD_BUFDESC_IN_TOTAL
} ILD_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  LD_BUFDESC_OUT_XY_LIST:
  This  buffer is filled up by algorithm and will contain all the
  XY points of the lanes detected. The (X,Y) is in packed 32-bit format.
  The outbuf contains the (X,Y) locations of points belonging to ROI 1,
  which is left ROI (ideally left lane) in our case followed by points belonging to ROI 2,
  which is right ROI (ideally right lane) in our case.
  In order to determine the number of points in each ROI and offset to the ROI 2 points,
  the number of points in each ROI are output as part of the outArgs.
  
*/
typedef enum
{
  LD_BUFDESC_OUT_XY_LIST = 0,
  LD_BUFDESC_OUT_TOTAL
} ILD_OutBufOrder ;

/**

  @struct LD_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          LD algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxImageWidth
          Max input width of image

  @param  maxImageHeight
         Max input height of image
   
  @param maxRho
          Max input Rho for Hough space

  @param maxTheta
          Max input Theta for Hough space

  @param edma3RmLldHandle
          Pointer to the edma3lld resource manager handle
*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t maxImageWidth;
  uint16_t maxImageHeight;
  uint16_t maxRho;
  uint16_t maxTheta;
  void    * edma3RmLldHandle;
} LD_TI_CreateParams;



/**
  @brief User information to indicate if tracking method

  LD_TI_TRACK_DISABLE: Disable tracking

  LD_TI_TRACK_KF: Enable Kalman fitler based tracking

*/

typedef enum
{
  LD_TI_TRACK_DISABLE=0,
  LD_TI_TRACK_KF
}LD_TI_TRACKMETHOD;


/**
  @brief User information to enable lane departure warning

  LD_TI_WARNING_DISABLE: Disable warning

  LD_TI_WARNING_ENABLE: Enable warning

*/


typedef enum
{
  LD_TI_WARNING_DISABLE=0,
  LD_TI_WARNING_ENABLE
}LD_TI_WARNING_INFO;


/**

  @struct LD_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to LD algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param cannyHighThresh
          Higher threshold used in the double thresholding stage of 
          Canny edge detection stage

  @param cannyLowThresh
          Lower threshold used in the double thresholding stage of
          Canny edge detection stage

  @param houghNmsThresh
          Threshold used while apply NMS in the Hough space

  @param startThetaLeft
          Start angle bin to be considered for left lane

  @param endThetaLeft
           End angle bin to be considered for left lane

  @param startThetaRight
          Start angle bin to be considered for right lane

  @param endThetaRight
          End angle bin to be considered for right lane

  @param thetaStepSize
          Step size to increment theta

  @param numHoughMaximasDet
          Number of Hough Space maximas to be detected
          for each ROI

  @param numHoughMaximasTrack
          Number of Hough Space maximas to be tracked
          for each ROI

  @param trackingMethod
         0 - Disable tracking
         1 - Enable Kalman filter based tracking

  @param warningMethod
         0 - Departure warning disabled
         1 - Departure warning enabled

  @param departThetaLeftMin
        Minimum angle bin to be considered for left lane departure

  @param departThetaLeftMax
        Maximum angle bin to be considered for left lane departure

  @param departRhoLeftMin
        Minimum Rho bin to be considered for left lane departure

  @param departRhoLeftMax
        Maximum Rho bin to be considered for left lane departure

  @param departThetaRightMin
        Minimum angle bin to be considered for right lane departure

  @param departThetaRightMax
        Maximum angle bin to be considered for right lane departure

  @param departRhoRightMin
        Minimum Rho bin to be considered for right lane departure

@param departRhoRightMax
        Maximum Rho bin to be considered for right lane departure

@param resetLDAlg
        Resets the LD algorithm, mainly the rho,theta track information

*/
typedef struct
{
  IVISION_InArgs      iVisionInArgs;
  uint16_t            cannyHighThresh;
  uint16_t            cannyLowThresh;
  uint16_t            houghNmsThresh;
  uint16_t            startThetaLeft;
  uint16_t            endThetaLeft;
  uint16_t            startThetaRight;
  uint16_t            endThetaRight;
  uint16_t            thetaStepSize ;
  uint8_t             numHoughMaximasDet;
  uint8_t             numHoughMaximasTrack;
  uint8_t             trackingMethod;
  uint8_t             warningMethod;
  uint16_t            departThetaLeftMin;
  uint16_t            departThetaLeftMax;
  uint16_t            departRhoLeftMin;
  uint16_t            departRhoLeftMax;
  uint16_t            departThetaRightMin;
  uint16_t            departThetaRightMax;
  uint16_t            departRhoRightMin;
  uint16_t            departRhoRightMax;
  uint8_t             resetLDAlg;
} LD_TI_InArgs;


/**
  @brief Flag returned by the LD algorithm to indicate
  information such as lane change

  LD_TI_NO_LANE_CROSS: There is no lane change

  LD_TI_RIGHT_LANE_CROSS: Right lane has been crossed

  LD_TI_LEFT_LANE_CROSS: Left lane has been crossed

*/

typedef enum
{
  LD_TI_NO_LANE_CROSS=0,
  LD_TI_RIGHT_LANE_CROSS,
  LD_TI_LEFT_LANE_CROSS
}LD_TI_LANE_INFO;


/**

  @struct LD_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by LD algorithm at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  numLeftLanePoints
          Number of points belonging to left lane, detected in the image

  @param  numRightLanePoints
          Number of points belonging to right lane, detected in the image

   @param infoFlag
          Information flag, to indicate events such as lane departure and so on

*/
typedef struct
{
  IVISION_OutArgs  iVisionOutArgs;
  uint16_t         numLeftLanePoints ;
  uint16_t         numRightLanePoints ;
  uint8_t          infoFlag;
} LD_TI_OutArgs;




/**
* Output params
*/
typedef struct
{
  uint16_t y;
  uint16_t x;
} LD_TI_output;

/*@}*/
/* ti_ivision_LD */

#ifdef __cplusplus
}
#endif

#endif /*ILD_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                                                                           */
/*==========================================================================*/


