/*
* module name       :TI Object Detection
*
* module descripton :Detection of pedestrians, traffic signs and vehicles using TI’s C66x DSP
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

/** @ingroup    ti_ivision_TI_OD*/
/*@{*/
#ifndef IOBJDET_TI_H
#define IOBJDET_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum number of objects per frame.
 * This number includes total detections for PD, TSR, VD etc..
 */
#define TI_OD_MAX_NUM_OBJECTS (32)

/**
 * Maximum number of scales supported
 */
#define TI_OD_MAX_TOTAL_SCALES  (32)

/**
 * @brief The unique const funtion table for object detection
 */
extern const IVISION_Fxns TI_OD_VISION_FXNS;

/**
* @brief IRES interface of the object detection app
*/
extern const IRES_Fxns TI_OD_IRES_FXNS;

/**
  @enum  TI_OD_InBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffer descriptor

         If 0, TI_OD_IN_BUFDESC_FEATURE_PLANES: This buffer descriptor provides the
               feature planes representing the image. The feature planes are
               assumed to be 16 bit data.
         If 1, TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS: This buffer descriptor is used
               to externally provide AdaBoost weights. If useExtPDWeights is set to 1
               then AdaBoost classifier will use weights in this buffer, else it will
               use default weights.
         If 2, TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS: This buffer descriptor is used
               to externally provide AdaBoost weights. If useExtTSRWeights is set to 1
               then AdaBoost classifier will use weights in this buffer, else it will
               use default weights.
         If 3, TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS: This buffer descriptor is used
               to externally provide AdaBoost weights. If useExtVDWeights is set to 1
               then AdaBoost classifier will use weights in this buffer, else it will
               use default weights.
         If 4, TI_OD_IN_BUFDESC_TOTAL

*/
typedef enum
{
  TI_OD_IN_BUFDESC_FEATURE_PLANES = 0,
  TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS,
  TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS,
  TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS,
  TI_OD_IN_BUFDESC_TOTAL

} TI_OD_InBufOrder;


/**
  @enum  TI_OD_OutBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

         If 0, TI_OD_OUT_BUFDESC_OBJECT_LIST - This  buffer is filled up by algorithm
               with a list of objects.
         If 1, TI_OD_OUT_BUFDESC_DETECTION_LIST - This  buffer is filled up by algorithm
               with a list of detections
         If 2, TI_OD_OUT_BUFDESC_TOTAL
  */

typedef enum
{
  TI_OD_OUT_BUFDESC_OBJECT_LIST= 0,
  TI_OD_OUT_BUFDESC_DETECTION_LIST,
  TI_OD_OUT_BUFDESC_TOTAL

} TI_OD_OutBufOrder;

/**
  @enum  TI_OD_ROIPreset
  @brief ROI processing presets supported by OD.
         If 0, TI_OD_ROI_FULL_FRAME
               This preset will enable search at every point in the provided
               feature data

         If 1, TI_OD_ROI_DYNAMIC
               This preset will enable search only a small region around a detected
               object in the previous frame. The previous frame could have been
               fully processed or processed based on detections.
  */

typedef enum
{
    TI_OD_ROI_FULL_FRAME = 0,
    TI_OD_ROI_DYNAMIC

}TI_OD_ROIPreset;

/**
  @enum   TI_OD_ObjectType
  @brief  Enum to indicate type of object detected.
          This is used to populate objType in
          TI_OD_output structure

          If 0, TI_OD_PEDESTRIAN
          If 1, TI_OD_TRAFFIC_SIGN
          If 3, TI_OD_VEHICLE
          If 2, TI_OD_MAX_OBJECTS
*/
typedef enum
{
    TI_OD_PEDESTRIAN = 0,
    TI_OD_TRAFFIC_SIGN,
    TI_OD_VEHICLE,
    TI_OD_MAX_OBJECTS

} TI_OD_ObjectType;

/**
  @enum  TI_OD_ErrorCodes
  @brief Enumeration of error codes returned by OD algorithm
*/
typedef enum
{
  TI_OD_UNSUPPORTED_IMAGE_WIDTH = 16,
  TI_OD_UNSUPPORTED_IMAGE_HEIGHT = 17,
  TI_OD_UNSUPPORTED_NUM_SCALES = 18,
  TI_OD_UNSUPPORTED_DETECTION_MODE = 19,
  TI_OD_UNSUPPORTED_ROI_PRESET = 20,
  TI_OD_UNSUPPORTED_REFRESH_INTERVAL = 21,
  TI_OD_UNSUPPORTED_CLASSIFIER_TYPE = 22,
  TI_OD_UNSUPPORTED_TRACKING_METHOD = 23,
  TI_OD_UNSUPPORTED_RECOGNITION_METHOD = 24,
  TI_OD_UNSUPPORTED_SOFT_CASCADE_THRESHOLD = 25,
  TI_OD_UNSUPPORTED_STRONG_CASCADE_THRESHOLD = 26,
  TI_OD_UNSUPPORTED_META_DATA = 27,
  TI_OD_EDMA_MEMCPY_ERROR = 28,
  TI_OD_EDMA_SCATTER_GATHER_ERROR = 29,
  TI_OD_RESERVED_PARAMS_NOT_ZERO = 20,
  TI_OD_UNSUPPORTED_PARAMETER = 31

} TI_OD_ErrorCodes;

/**
  @struct TI_OBJECT_FEATURES_scaleMetaData

  @brief  This structure contains all the meta data containing
          informtion about the each scale feature

  @param  scaleOffset
          Offset from the base output pointer

  @param  orgImCols
          Original image width in pixels

  @param  orgImRows
          Original image height in pixels

  @param  imCols
          ROI Image width in pixels, can be same as orgImCols for
          full image processing.

  @param  imRows
          ROI Image height in pixels, can be same as orgImRows for
          full image processing

  @param  startX
          ROI starting location in pixels along X direction

  @param  startY
          ROI starting location in pixels along Y direction

  @param  featCols
          number of valid features in each row of a feture plane

  @param  featRows
          number of features row per feture plane

  @param  featPitch
          Offset between each line of a feture plane (in Bytes)

  @param  planeOffset
          Offset between each feture plane (in Bytes)
*/
typedef struct
{
  uint32_t          scaleOffset;
  uint16_t          orgImCols;
  uint16_t          orgImRows;
  uint16_t          imCols;
  uint16_t          imRows;
  uint16_t          startX;
  uint16_t          startY;
  uint16_t          featCols;
  uint16_t          featRows;
  uint16_t          featPitch;
  uint32_t          planeOffset;

} TI_OBJECT_FEATURES_scaleMetaData;

/**
  @struct TI_OBJECT_FEATURES_outputMetaData

  @brief  This structure contains all the meta data containing
          informtion about the feature data set.

  @param  size
          Size of this stucture in bytes

  @param  featBufSize
          Total output buffer size in bytes

  @param  numScales
          Total number of (pyramid levles) fearture scales

  @param  numPlanes
          Number of feature planes/channels.

  @param  outFormat
          Feature data layout information.

  @param  leftPadPels
          Left padding of input image in pixels. Equal amount of
          padding will be applied on the right edge of the image.

  @param  topPadPels
          Top padding of input image in pixels. Equal amount of
          padding will be applied on the bottom edge of the image.

  @param  computeCellSum
          Flag to indicate of 2x2 cell sum is to be computed by OD
          algorithm or not
          0 - 2x2 cell sum computed outside OD.
          1 - 2x2 cell sum to be computed by OD.

  @param  scaleInfo
          Array of type TI_OBJECT_FEATURES_scaleMetaData. Maximum
          number of supported scales is TI_OD_MAX_TOTAL_SCALES
*/

typedef struct
{
  uint32_t          size;
  uint32_t          featBufSize;
  uint8_t           numScales;
  uint8_t           numPlanes;
  uint8_t           outFormat;
  uint16_t          leftPadPels;
  uint16_t          topPadPels;
  uint8_t           computeCellSum;
  TI_OBJECT_FEATURES_scaleMetaData scaleInfo[TI_OD_MAX_TOTAL_SCALES];
} TI_OBJECT_FEATURES_outputMetaData;

/**
  @struct TI_OD_CreateParams
  @brief  This structure contains all the parameters which controls
          OD algorithm at create time

  @param  edma3RmLldHandle
          Handle to EDMA3 resource manager.

  @param  maxImageWidth
          Max input width of image

  @param  maxImageHeight
          Max input height of image

  @param  maxScales
          Max number of supported scales
*/
typedef struct
{
  IVISION_Params visionParams;
  void    *edma3RmLldHandle;

  uint16_t maxImageWidth;
  uint16_t maxImageHeight;
  uint16_t maxScales;

} TI_OD_CreateParams;

/**
  @struct TI_OD_PDConfig
  @brief  This structure contains the PD specific
          config parameters.

  @param  enablePD
          Flag to enable or disable pedestrian detection
          0 - disable
          1 - enable (default)

  @param  detectorTypePD
          Flag to indicate type of classifier to be used.
          0 - Two level Adaboost (default)

  @param  trackingMethodPD
          Flag to enable / disable pedestrian tracking
          0 - disable tracking
          1 - enable  tracking (default)

  @param  useExtWeightsPD
          Flag to indicate if classifier should use default/external weights
          0 - Use default weights
          1 - User externally supplied weights

  @param  softCascadeThPD
          32-bit signed threshold value for AdaBoost.
          -1 (recommended)

  @param  strongCascadeThPD
          32-bit signed threshold value for AdaBoost
          -1 (recommended)

*/
typedef struct
{
  uint8_t enablePD;
  uint8_t detectorTypePD;
  uint8_t trackingMethodPD;
  uint8_t useExtWeightsPD;
  int32_t softCascadeThPD;
  int32_t strongCascadeThPD;

} TI_OD_PDConfig;

/**
  @struct TI_OD_TSRConfig
  @brief  This structure contains the TSR specific
          config parameters.

  @param  enableTSR
          Flag to enable or disable traffic sign detection
          0 - disable
          1 - enable (default)

  @param  detectorTypeTSR
          Flag to indicate type of classifier to be used
          0 - Two level Adaboost (default)

  @param  trackingMethodTSR
          Flag to enable / disable traffic sign tracking
          0 - disable tracking
          1 - enable  tracking (default)

  @param  recognitionMethodTSR
          Flag to enable / disable traffic sign recognition.
          0 - disable
          1 - enable LDA (default)

  @param  useExtWeightsTSR
          Flag to indicate if classifier should use default/external weights
          0 - Use default weights
          1 - User externally supplied weights

  @param  softCascadeThTSR
          32-bit signed threshold value for AdaBoost
          -1 (recommended)

  @param  strongCascadeThTSR
          32-bit signed threshold value for AdaBoost
          7 (recommended)

*/
typedef struct
{
  uint8_t enableTSR;
  uint8_t detectorTypeTSR;
  uint8_t trackingMethodTSR;
  uint8_t recognitionMethodTSR;
  uint8_t useExtWeightsTSR;
  int32_t softCascadeThTSR;
  int32_t strongCascadeThTSR;

} TI_OD_TSRConfig;

/**
  @struct TI_OD_VDConfig
  @brief  This structure contains the VD specific
          config parameters.

  @param  enableVD
          Flag to enable or disable vehicle detection
          0 - disable
          1 - enable (default)

  @param  detectorTypeVD
          Flag to indicate type of classifier to be used.
          0 - Two level Adaboost (default)

  @param  trackingMethodVD
          Flag to enable / disable vechicle tracking.
          0 - disable tracking
          1 - enable  tracking (default)

  @param  useExtWeightsVD
          Flag to indicate if classifier should use default/external weights
          0 - Use default weights
          1 - User externally supplied weights

  @param  softCascadeThVD
          32-bit signed threshold value for AdaBoost
          -1 (recommended)

  @param  strongCascadeThVD
          32-bit signed threshold value for AdaBoost
          7 (recommended)

*/
typedef struct
{
  uint8_t enableVD;
  uint8_t detectorTypeVD;
  uint8_t trackingMethodVD;
  uint8_t useExtWeightsVD;
  int32_t softCascadeThVD;
  int32_t strongCascadeThVD;

} TI_OD_VDConfig;


/**
  @struct TI_OD_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to OD algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  pdConfig
          Structure of type TI_OD_PDConfig

  @param  tsrConfig
          Structure of type TI_OD_TSRConfig

  @param  vdConfig
          Structure of type TI_OD_VDConfig

  @param  roiPreset
          Flag to enable or disable ROI processing on DSP
          0 - Searches each point in the feature vector every frame
          1 - Searches only regions around detected object in previous
              frames
          See enum TI_OD_ROIPreset

  @param  refreshInterval
          Specifies frame refresh rate when roiPreset is 1.
          Eg. A value of 2 will process every even frames fully and every
          odd frames only around detected object regions.
          Not applicable when roiPreset is 0.

  @param  detectionMode
          This is to control search points in feature plane.
          When,

          detectionMode = 0 => Search all points. HIGH_QUALITY mode. (default)
          detectionMode = 1 => Skip odd points in the horizontal direction

  @param  reserved0
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved1
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved2
           Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved3
           Reserved 32-bit field. Must be set to 0 for normal operation.

*/
typedef struct
{
  IVISION_InArgs   iVisionInArgs;
  TI_OD_PDConfig   pdConfig;
  TI_OD_TSRConfig  tsrConfig;
  TI_OD_VDConfig   vdConfig;
  uint8_t          detectionMode;
  uint8_t          roiPreset;
  uint8_t          refreshInterval;

  uint32_t         reserved0;
  uint32_t         reserved1;
  uint32_t         reserved2;
  uint32_t         reserved3;

} TI_OD_InArgs;

/**
  @struct TI_OD_Stats
  @brief  This structure reports cycles and other statistics
          of OD module. To be used only for debug purpose.

  @param  detectorCycles
          Total cycles taken by detector module

  @param  groupingCycles
          Total cycles taken by grouping module

  @param  trackingCycles
          Total cycles taken by tracker module

  @param  numDetected
          Total number of detections

  @param  numDetected
          Total number of grouped windows

  @param  numDetected
          Total number of tracks

  @param  reserved0
          Reserved field 0

  @param  reserved1
          Reserved field 0

  @param  reserved2
          Reserved field 0

  @param  reserved3
          Reserved field 0

*/

typedef struct
{
  uint32_t detectorCycles;
  uint32_t groupingCycles;
  uint32_t trackingCycles;

  uint32_t numDetected;
  uint32_t numGrouped;
  uint32_t numTracked;

  uint32_t reserved0;
  uint32_t reserved1;
  uint32_t reserved2;
  uint32_t reserved3;

} TI_OD_Stats;

/**
  @struct TI_OD_OutArgs
  @brief  This structure contains all the parameters
          which are given as output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  pdStats
          Stats structure of type TI_OD_PDStats for PD

  @param  tsrStats
          Stats structure of type TI_OD_TSRStats for TSR

  @param  vdStats
          Stats structure of type TI_OD_VDStats for VD

  @param  errorCode
          Type of error detected by the module see TI_OD_ErrorCodes
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  TI_OD_Stats     pdStats;
  TI_OD_Stats     tsrStats;
  TI_OD_Stats     vdStats;
  uint32_t        cellSumCycles;
  uint32_t        cellSumPoints;
  uint32_t        errorCode;

} TI_OD_OutArgs;

/**
  @struct TI_OD_objectDescriptor

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

} TI_OD_objectDescriptor;

/**
  @struct TI_OD_outputList
  @brief  This is the output structure given out by object detection
          module. It contains the number of objects detected and
          TI_OD_MAX_NUM_OBJECTS instances of TI_OD_objectDescriptor
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
          Max size TI_OD_MAX_NUM_OBJECTS

*/
typedef struct
{
  int32_t numObjects;
  int32_t errorCode;
  TI_OD_objectDescriptor objDesc[TI_OD_MAX_NUM_OBJECTS];

} TI_OD_outputList;

/*
 * Total size of the output buffer to be allocated by the application.
 */
#define TI_OD_OUT_BUFDESC_LIST_SIZE (sizeof(TI_OD_outputList))

/*@}*/
/* ti_ivision_TI_OD */

#ifdef __cplusplus
}
#endif

#endif /*IOBJDET_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


