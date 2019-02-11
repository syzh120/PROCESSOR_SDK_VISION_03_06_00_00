/*
 
Copyright (c) [2015] – [2017] Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI ("TI Devices").  No hardware patent is licensed hereunder.
 
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
 *  @file       iclr_ti.h
 *  @brief     This file defines ivision interface for TI Circular
 *              Light Recognition algorithm

 *  @version 1.0 (Aug 2015) : Base version.
 */

/** @ingroup    ti_ivision_CLR*/
/*@{*/
#ifndef ITI_CLR_H
#define ITI_CLR_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The unique const funtion table for the CIRCULAR LIGHT RECOGNITION.
 */
extern const IVISION_Fxns TI_CLR_VISION_FXNS;

/**
* @brief IRES interface of the  CIRCULAR LIGHT RECOGNITION
*/
extern const IRES_Fxns TI_CLR_IRES;

/**
  @brief Error code returned by the CIRCULAR LIGHT RECOGNITION algorithm

  TI_CLR_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are
  beyond supported

  TI_CLR_ERRORTYPE_INVALID_ROI_DIMS: ROI dimensions are
  beyond image dimensions

  TI_CLR_ERRORTYPE_MAXNUMRADIUS_EXCEEDED: Number of radius is 
  beyond supported

  TI_CLR_ERRORTYPE_RADIUS_BEYOND_RANGE: Radius value is 
  beyond supported

  TI_CLR_ERRORTYPE_MAXNUMCOLORS_EXCEEDED: Number of color lights 
  exceeded the supported value

  TI_CLR_ERRORTYPE_SCALING_FACTOR_BEYOND_RANGE: Hough spcae 
  scaling factor is beyond supported value

  TI_CLR_ERRORTYPE_TRACK_METHOD_BEYOND_RANGE: track method
  is beyond supported value

  TI_CLR_ERRORTYPE_INVALID_LIGHT_SELCTION: Light selction method
  is invalid

  TI_CLR_ERRORTYPE_INVALID_PRIMARY_COLOR: Primary color selction
  is invalid

  TI_CLR_ERRORTYPE_INVALID_VOTING_METHOD: Hough space voting method
  is invalid

  TI_CLR_ERRORTYPE_INVALID_GROUP_WIN_SIZE: Grouping window size
  is invalid

  TI_CLR_ERRORTYPE_INVALID_MORPH_METHOD: Morphology method
  is invalid

*/
typedef enum
{
  TI_CLR_ERRORTYPE_INVALID_IMAGE_DIMS = IVISION_CUSTOMFAILBASE,
  TI_CLR_ERRORTYPE_INVALID_ROI_DIMS,
  TI_CLR_ERRORTYPE_MAXNUMRADIUS_EXCEEDED,
  TI_CLR_ERRORTYPE_RADIUS_BEYOND_RANGE,
  TI_CLR_ERRORTYPE_MAXNUMCOLORS_EXCEEDED,
  TI_CLR_ERRORTYPE_SCALING_FACTOR_BEYOND_RANGE,
  TI_CLR_ERRORTYPE_TRACK_METHOD_BEYOND_RANGE,
  TI_CLR_ERRORTYPE_INVALID_LIGHT_SELCTION,
  TI_CLR_ERRORTYPE_INVALID_PRIMARY_COLOR,
  TI_CLR_ERRORTYPE_INVALID_VOTING_METHOD,
  TI_CLR_ERRORTYPE_INVALID_GROUP_WIN_SIZE,
  TI_CLR_ERRORTYPE_INVALID_MORPH_METHOD,
  TI_CLR_ERRORTYPE_EDMA_INIT
} TI_CLR_ErrorType;


/**
* @brief Maximum number of color lights to be dected

*/
#define TI_CLR_MAX_NUM_COLOR_LIGHTS   (2)


/**
* @brief Maximum radius value for which CLR will be performed

*/
#define TI_CLR_MAX_RADIUS   (32)


/**
* @brief Maximum number of radii for which CLR will be performed

*/
#define TI_CLR_MAX_NUM_RADIUS   (32)

/**
* @brief Max width allowed by CLR
*/
#define TI_CLR_MAXWIDTH      (1920)

/**
* @brief Max height allowed by CLR
*/
#define TI_CLR_MAXHEIGHT     (1080)

/**
* @brief Maximum value for grouping Window Size
*/
#define TI_CLR_MAX_GROUP_WIN_SIZE   (64)



/**
  @brief Downscaling to be performed in the output Hough space during Circle detection.

  TI_CLR_HS_NO_SCALING : No averaging in Hough space
  TI_CLR_HS_SCALE_2x2  : Averaging on a 2x2 grid.
  TI_CLR_HS_SCALE_4x4  : Averaging on a 4x4 grid.

*/
typedef enum
{
  TI_CLR_HS_NO_SCALING = 0,
  TI_CLR_HS_SCALE_2x2  = 1,
  TI_CLR_HS_SCALE_4x4  = 2,
  TI_CLR_HS_SCALE_MAX
} TI_CLR_HoughSpaceScaling;

/**
  @brief Voting method for Hough circle transform.

  TI_CLR_HSV_DEFAULT         : TI_CLR_HSV_GRAD_MAGNITUDE
  TI_CLR_HSV_GRAD_MAGNITUDE  : Increament by gradient magnitude.
  TI_CLR_HS_MAX.
*/
typedef enum
{
  TI_CLR_HSV_DEFAULT = 0,
  TI_CLR_HSV_GRAD_MAGNITUDE  = 1,
  TI_CLR_HSV_MAX
} TI_CLR_HoughSpaceVotingMethod;

/**
  @brief List of suported tracking methods

  TI_CLR_TRACKING_NONE       : No tracking/tracking disables
  TI_CLR_TRACKING_KALMAN     : Kalman filter based tracking
*/
typedef enum
{
  TI_CLR_TRACKING_NONE    = 0,
  TI_CLR_TRACKING_KALMAN  = 1,
  TI_CLR_TRACKING_MAX
} TI_CLR_TrackingMethod;

/**
  @struct TI_CLR_CreateParams
  @brief  This structure contains all the parameters which controls
          CLR algorithm at create time

  @param  edma3RmLldHandle
          Handle to EDMA3 resource manager.

  @param  maxImageWidth
          Max input width of image

  @param  maxImageHeight
          Max input height of image

  @param  maxNumColors
          Maximum number of color lights to be detected

  @param  maxRadius
          Maximum value for Radius

  @param  maxNumRadius
          Maximum value for number of radii

  @param  minScalingFactor
          Minim value for hough Space Scaling Factor, Refer TI_CLR_HoughSpaceScaling

  @param trackingMethod
          Tracking CL between frames, refer TI_CLR_TrackingMethod for list of suported tracking methods

*/
typedef struct
{
  IVISION_Params visionParams;
  void    *edma3RmLldHandle;

  int32_t maxImageWidth;
  int32_t maxImageHeight;
  int32_t maxNumColors;
  int32_t maxRadius;
  int32_t maxNumRadius;
  int32_t minScalingFactor;
  int32_t trackingMethod;
} TI_CLR_CreateParams;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  TI_CLR_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by algorithm.

*/
typedef enum
{
  TI_CLR_BUFDESC_IN_IMAGEBUFFER = 0,
  TI_CLR_BUFDESC_IN_TOTAL
} TI_CLR_InBufOrder ;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 output buffer descriptor

  TI_CLR_BUFDESC_OUT_OBJ_BUFFER: This buffer descriptor has the
  details/properties of all the detected circuler lights

*/
typedef enum
{
  TI_CLR_BUFDESC_OUT_OBJ_BUFFER = 0,
  TI_CLR_BUFDESC_OUT_TOTAL
} TI_CLR_OutBufOrder ;


/**
  @brief List of Primary color types suported.

  TI_CLR_PC_RED    : RED light
  TI_CLR_PC_GREEN  : GREEN Light

*/
typedef enum
{
  TI_CLR_PC_RED   = 0,
  TI_CLR_PC_GREEN = 1,
  TI_CLR_PC_MAX
} TI_CLR_PrimaryColor;


/**
  @brief List of Light selection methods suported.

  TI_CLR_LSM_DEFAULT    : TI_CLR_LSM_RED_GREEN
  TI_CLR_LSM_RED_GREEN  : RED and GREEN Light
  TI_CLR_LSM_CUSTOM     : lightBrightnessThr, lightColor etc will be used for 
                          Light selection

*/
typedef enum
{
  TI_CLR_LSM_DEFAULT     = 0,
  TI_CLR_LSM_RED_GREEN   = TI_CLR_LSM_DEFAULT,
  TI_CLR_LSM_CUSTOM      = 1,
  TI_CLR_LSM_MAX
} TI_CLR_LightSelectionMethod;

/**

  @struct TI_CLR_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to CLR algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  lightSelection
          list of circular lights selection method, refer TI_CLR_LightSelectionMethod

  @param lightBrightnessThr
          Bright ness level threshold for each type of light

  @param lightColor
          Primary color of each light, refer TI_CLR_PrimaryColor

  @param lightThr1
          First threshold for Color segmentation.Threshol used for Cr/V segmentation

  @param lightThr2
          Second threshold for Color segmentation.Threshol used for Cb/U segmentation

  @param falseFilterThr
         Threshold (dark pixels values) for filtering false passitive

  @param numColors
         Number of colors to be searched

  @param numRadius
         Number of radii to be searched

  @param radius
          list of radius Values

  @param circleDetectionThr
          Detection threshold during Hough circle transform

  @param scalingFactor
          Scaling factor for Hough Space, refer TI_CLR_HoughSpaceScaling

  @param morphologyMethod
          0 : Disable Morphology, 1: 3x3 Dilation on Binary Image

  @param houghSpaceVotingMethod
          Voting method for Hough Space, Refer TI_CLR_HoughSpaceVotingMethod

  @param groupingWindowSize
          Minimum distance between two dtected lights in pixels

  @param reserved
          reserved parameter for algorithm debug, 
          shall be set zero for normal processing

*/
typedef struct
{
  IVISION_InArgs     iVisionInArgs;
  int32_t            lightSelection;
  int32_t            lightBrightnessThr[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  int32_t            lightColor[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  int32_t            lightThr1[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  int32_t            lightThr2[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  int32_t            falseFilterThr[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  int32_t            numColors;
  int32_t            numRadius;
  int32_t            radius[TI_CLR_MAX_NUM_RADIUS];
  int32_t            circleDetectionThr[TI_CLR_MAX_NUM_RADIUS];
  int32_t            scalingFactor[TI_CLR_MAX_NUM_RADIUS];
  int32_t            morphologyMethod;
  int32_t            houghSpaceVotingMethod;
  int32_t            groupingWindowSize;
  int32_t            reserved;

} TI_CLR_InArgs;


/**

  @struct TI_CLR_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by CLR algorithm at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param numCLs
          number of detected Circular lights for each color and sizes

  @param numSegPixels
          Number of pixels segmented for each color in the frame. 
          This information may not be used by the application. This is just a statistics about processed frame.

*/
typedef struct
{
  IVISION_OutArgs  iVisionOutArgs;
  int32_t          numCLs[TI_CLR_MAX_NUM_COLOR_LIGHTS];
  uint32_t         numSegPixels[TI_CLR_MAX_NUM_COLOR_LIGHTS];
} TI_CLR_OutArgs;

/**
 * Maximum number of output string messages per detection.
 */
#define MAX_NUM_OUTPUT_STRINGS           (10)

/**
 * Maximum size of string message
 */
#define MAX_STRING_SIZE                 (50)

/**
 * Maximum of objects that can be detected in frame
 */
#define TI_CLR_MAX_DETECTIONS_PER_FRAME (32)

/**
  @brief List of OBJECT Types.

  TI_CLR_OBJ_RED_TRAFFIC_LIGHT      : Red Traffic Light
  TI_CLR_OBJ_GREEN_TRAFFIC_LIGHT    : Green Traffic Light
  TI_CLR_OBJ_VEHICLE                : Vehicle

*/
typedef enum
{
  TI_CLR_OBJ_RED_TRAFFIC_LIGHT   = 128,
  TI_CLR_OBJ_GREEN_TRAFFIC_LIGHT,
  TI_CLR_OBJ_VEHICLE,
  TI_CLR_OBJ_MAX
} TI_CLR_ObjectType;

/**
  @struct TI_CLR_objectDescriptor
  @brief  This structure contains the detected object properties
          such as location-(x, y), size-(height, width), confidence (score)

  @param  objTag
          Unique value to identify the object across frames

  @param  objType
          Indicates the type of object detected.

  @param  objSubType
          Indicates the sub-type of object detected.

  @param  xPos
          Location of the detected object in pixels along X direction.

  @param  yPos
          Location of the detected object in pixels along Y direction.

  @param  objWidth
          Width of the located object in pixels. Does not indicate actual
          width of the object.

  @param  objHeight
          Width of the located object in pixels. Does not indicate actual
          height of the object.

  @param  objScore
          Adaboost classifier score for the detected object.

  @param  objScale
          Scale at which the object was detected. A lower number indicates that
          an object far from the camera was detected. A higher number indicates
          that the object close to the camera was detected. This number may not
          correspond to original image pyramid scale ratio. The numbers may come
          out interpolated between scales.
          IEEE 32-bit single precision floating point format.

  @param  reserved0
          Reserved field to be ignored

  @param  reserved1
          Reserved field to be ignored

  @param  reserved2
          Reserved field to be ignored

*/
typedef struct
{
  uint32_t objTag;

  uint32_t objType;
  uint32_t objSubType;

  uint32_t xPos;
  uint32_t yPos;

  uint32_t objWidth;
  uint32_t objHeight;

  float    objScore;
  float    objScale;

  float    reserved0;
  float    reserved1;
  float    reserved2;

} TI_CLR_objectDescriptor;

/**
  @struct TI_CLR_output
  @brief  This is the output structure given out by object detection
          module. It contains the number of objects detected and
          TI_CLR_MAX_DETECTIONS_PER_FRAME instances of TI_CLR_objectDescriptor
          structure. The number of valid descriptors is governed by
          numObjects variable.

  @param  numObjects
          Number of objects detected by the module.

  @param  errorCode
          Error Code returned for one process call. A value of 0
          indicates no error. Refer TI_OD_errorCodes enumeration
          for a list of errorCodes thrown by OD.

  @param  objDesc
          List of detected object descriptor.
          Max size TI_OD_MAX_DETECTIONS_PER_OBJECT

*/
typedef struct
{
  int32_t numObjects;
  int32_t errorCode;
  TI_CLR_objectDescriptor objDesc[TI_CLR_MAX_DETECTIONS_PER_FRAME];
} TI_CLR_output;

/*
 * Total size of the output buffer to be allocated by the application.
 */
#define TI_CLR_OUT_BUFDESC_LIST_SIZE (sizeof(TI_CLR_output))


/*@}*/
/* ti_ivision_CLR */

#ifdef __cplusplus
}
#endif

#endif /*ITI_CLR_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


