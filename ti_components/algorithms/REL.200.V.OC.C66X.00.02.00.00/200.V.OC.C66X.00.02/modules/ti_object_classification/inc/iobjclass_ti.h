/*
* module name       :TI Object Classification
*
* module descripton :Classification of German traffic signs using TI’s C66x DSP
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
 *  @file       iobjclass_ti.h
 *
 *  @brief      This file defines ivision interface for Object Classification
 *              Algorithms
 *
 *  @version 1.0 (Nov 2015) : Base version.
 */

/** @ingroup    ti_ivision_TI_OD*/
/*@{*/
#ifndef IOBJCLASS_TI_H
#define IOBJCLASS_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum number of objects.
 * This number includes total objects for PD, TSR, VD etc..
 */
#define TI_OC_MAX_NUM_OBJECTS  (32)

/**
 * Maximum number of image pyramid scales
 */
#define TI_OC_MAX_TOTAL_SCALES (32)

/**
 * Maximum number of classifer layers
 */
#define TI_OC_MAX_LAYERS       (16)

/**
 * @brief The unique const funtion table for object detection
 */
extern const IVISION_Fxns TI_OC_VISION_FXNS;

/**
* @brief IRES interface of the object classification app
*/
extern const IRES_Fxns TI_OC_IRES_FXNS;

/**
  @enum  TI_OC_InBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffer descriptor

         If 0, TI_OC_IN_BUFDESC_IMAGE_PYRAMID: This buffer descriptor provides the
               image pyramid.
         If 1, TI_OC_IN_BUFDESC_DETECTION_LIST: This buffer descriptor provides the
               list of detections from object detection module
         If 2, TI_OC_IN_BUFDESC_TOTAL

*/
typedef enum
{
  TI_OC_IN_BUFDESC_IMAGE_PYRAMID = 0,
  TI_OC_IN_BUFDESC_DETECTION_LIST,
  TI_OC_IN_BUFDESC_TOTAL

} TI_OC_InBufOrder;


/**
  @enum  TI_OC_OutBufOrder
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

         If 0, TI_OC_OUT_BUFDESC_OBJECT_LIST - Output buffer with a list
               of classified objects.
         If 1, TI_OC_OUT_BUFDESC_TOTAL
  */

typedef enum
{
  TI_OC_OUT_BUFDESC_OBJECT_LIST = 0,
  TI_OC_OUT_BUFDESC_IMAGE_LIST,
  TI_OC_OUT_BUFDESC_TOTAL

} TI_OC_OutBufOrder;

/**
  @enum   TI_OC_ObjectType
  @brief  Enum to indicate type of object classified.
          This is used to populate objType in
          TI_OC_output structure

          If 0, TI_OC_PEDESTRIAN
          If 1, TI_OC_TRAFFIC_SIGN
          If 3, TI_OC_VEHICLE
          If 2, TI_OC_MAX_OBJECTS
*/
typedef enum
{
    TI_OC_PEDESTRIAN = 0,
    TI_OC_TRAFFIC_SIGN,
    TI_OC_VEHICLE,
    TI_OC_MAX_OBJECTS

} TI_OC_ObjectType;

/**
  @enum  TI_OC_ObjectSubType
  @brief Enum to indicate sub type of object detected.

*/
typedef enum {
  TI_CLASS_NEGATIVE = 0,       /*0 - Object is a false positive */
  TI_TSR_SPEED_LIMIT_20,       /*1 - Traffic sign - speed limit 20 km/h */
  TI_TSR_SPEED_LIMIT_30,       /*2 - Traffic sign - speed limit 30 km/h */
  TI_TSR_SPEED_LIMIT_50,       /*3 - Traffic sign - speed limit 50 km/h */
  TI_TSR_SPEED_LIMIT_60,       /*4 - Traffic sign - speed limit 60 km/h */
  TI_TSR_SPEED_LIMIT_70,       /*5 - Traffic sign - speed limit 70 km/h */
  TI_TSR_SPEED_LIMIT_80,       /*6 - Traffic sign - speed limit 80 km/h */
  TI_TSR_SPEED_LIMIT_100,      /*7 - Traffic sign - speed limit 100 km/h  */
  TI_TSR_SPEED_LIMIT_120,      /*8 - Traffic sign - speed limit 120 km/h */
  TI_TSR_END_OF_SPEED_LIMIT_80,/*9 - Traffic sign – end of speed limit 80 km/h */
  TI_TSR_PRIORITY_ROAD,        /*10 - Traffic sign – priority road */
  TI_TSR_GIVE_WAY,             /*11 - Traffic sign – give way */
  TI_TSR_NO_ENTRY,             /*12 - Traffic sign – no entry */
  TI_TSR_TURN_RIGHT,           /*13 - Traffic sign – turn right */
  TI_TSR_TURN_LEFT,            /*14 - Traffic sign – turn left */
  TI_TSR_AHEAD_ONLY,           /*15 - Traffic sign – ahead only */
  TI_TSR_GO_STRAIGHT_OR_RIGHT, /*16 - Traffic sign – go straight or right */
  TI_TSR_GO_STRAIGHT_OR_LEFT,  /*17 - Traffic sign – go straight or left */
  TI_TSR_KEEP_RIGHT,           /*18 - Traffic sign – keep right */
  TI_TSR_KEEP_LEFT,            /*19 - Traffic sign – keep left */
  TI_TSR_ROUNDABOUT,           /*20 - Traffic sign – roundabout  */
  TI_TSR_SPEED_LIMIT_END,      /*21 - Traffic sign – End of all speed and passing limits */
  TI_TSR_NO_STOPPING,          /*22 - Traffic sign – no stopping */
  TI_TSR_NO_VEHICLES,          /*23 - Traffic sign – no vehicles */
  TI_TSR_BICYCLE_LANE,         /*24 - Traffic sign – bicycle lane */
  TI_TSR_CAUTION,              /*25 - Traffic sign – general caution */
  TI_TSR_STOP_AND_GIVEWAY,     /*26 - Traffic sign – stop and give way */
  TI_CLASS_OTHER,              /*27 - Other class */
  TI_CLASS_PEDESTRIAN,         /*28 - Pedestrian class */
  TI_CLASS_BICYCLIST,          /*29 - Bicyclist class */
  TI_CLASS_VEHICLE,            /*30 - Vehicle class */
  TI_CLASS_IGNORED,            /*31 - Ignored class */
  TI_MAX_SUB_TYPES

}TI_OC_ObjectSubType;

/**
  @enum  TI_OC_ErrorCodes
  @brief Enumeration of error codes returned by OC algorithm
*/
typedef enum
{
  TI_OC_UNSUPPORTED_IMAGE_WIDTH     = 16,
  TI_OC_UNSUPPORTED_IMAGE_HEIGHT    = 17,
  TI_OC_UNSUPPORTED_NUM_SCALES      = 18,
  TI_OC_UNSUPPORTED_CLASSIFIER_TYPE = 19,
  TI_OC_UNSUPPORTED_META_DATA       = 20,
  TI_OC_EDMA_MEMCPY_ERROR           = 21,
  TI_OC_EDMA_SCATTER_GATHER_ERROR   = 22,
  TI_OC_RESERVED_PARAMS_NOT_ZERO    = 23,
  TI_OC_UNSUPPORTED_PARAMETER       = 24

} TI_OC_ErrorCodes;

/**
  @struct TI_OC_CreateParams
  @brief  This structure contains all the parameters which controls
          the algorithm at create time

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

} TI_OC_CreateParams;

/**
  @struct TI_OC_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to OC algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  inputMode
          Type of input supplied to OC module

  @param  classifierType
          Type of classifier to be used by OC module

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
  uint8_t          inputMode;
  uint8_t          classifierType;

  uint32_t         reserved0;
  uint32_t         reserved1;
  uint32_t         reserved2;
  uint32_t         reserved3;

} TI_OC_InArgs;

/**
  @struct TI_OC_Stats
  @brief  This structure reports statistics of running OC.
          To be used only for debug purpose.

  @param  numCycles[TI_OC_MAX_LAYERS]
          Number of cycles taken by each OC layer

  @param  numLayers
          Number of CNN layers

*/

typedef struct
{
  uint32_t numCycles[TI_OC_MAX_LAYERS];
  int32_t  numLayers;

} TI_OC_Stats;

/**
  @struct TI_OC_OutArgs
  @brief  This structure contains all the parameters
          which are given as output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  ocStats
          Stats structure of type TI_OC_Stats

  @param  errorCode
          Type of error detected by the module see TI_OC_ErrorCodes
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  TI_OC_Stats     ocStats;
  uint32_t        errorCode;

} TI_OC_OutArgs;

/**
  @struct TI_OC_imgPyrData
  @brief  This structure contains the image pyramid
          data coming from resizer module

  @param  outBufs
          Array of IVISION_OutBufs containing pyramid scales
          A maximum of TI_OC_MAX_TOTAL_SCALES
*/
typedef struct
{
  IVISION_OutBufs outBufs[TI_OC_MAX_TOTAL_SCALES];

} TI_OC_imgPyrData;

/**
  @struct TI_OC_objectDescriptor

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
          Classifier score for the detected object.

  @param  objScale
          Scale at which the object was detected.
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

} TI_OC_objectDescriptor;

/**
  @struct TI_OC_inputList
  @brief  This is the input structure given out by object detector
          module. It contains the number of objects detected and
          TI_OC_MAX_NUM_OBJECTS instances of TI_OC_objectDescriptor
          structure. The number of valid descriptors is governed by
          numObjects variable.

  @param  numObjects
          Number of objects classified by the module.

  @param  errorCode
          Error Code returned for one process call. A value of 0
          indicates no error. Refer TI_OC_errorCodes enumeration
          for a list of errorCodes thrown by the module.

  @param  objDesc
          List of detected object descriptor.
          Max size TI_OC_MAX_NUM_OBJECTS

*/
typedef struct
{
  int32_t numObjects;
  int32_t errorCode;
  TI_OC_objectDescriptor objDesc[TI_OC_MAX_NUM_OBJECTS];

} TI_OC_inputList;

/**
  @struct TI_OC_outputList
  @brief  This is the output structure given out by object classification
          module. It contains the number of objects classified and
          TI_OC_MAX_NUM_OBJECTS instances of TI_OC_objectDescriptor
          structure. The number of valid descriptors is governed by
          numObjects variable.

  @param  numObjects
          Number of objects classified by the module.

  @param  errorCode
          Error Code returned for one process call. A value of 0
          indicates no error. Refer TI_OC_errorCodes enumeration
          for a list of errorCodes thrown by the module.

  @param  objDesc
          List of classified object descriptor.
          Max size TI_OC_MAX_NUM_OBJECTS

*/
typedef struct
{
  int32_t numObjects;
  int32_t errorCode;
  TI_OC_objectDescriptor objDesc[TI_OC_MAX_NUM_OBJECTS];

} TI_OC_outputList;

/*
 * Total output list size to be allocated by the application.
 */
#define TI_OC_OUTPUT_LIST_SIZE (sizeof(TI_OC_outputList))

/*
 * Total input list size to be allocated by the application.
 */
#define TI_OC_INPUT_LIST_SIZE (sizeof(TI_OC_inputList))

/*
 * Total image pyramid size to be allocated by the application.
 */
#define TI_OC_IMAGE_PYRAMID_SIZE (sizeof(TI_OC_imgPyrData))

/*@}*/
/* ti_ivision_TI_OC */

#ifdef __cplusplus
}
#endif

#endif /*IOBJCLASS_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


