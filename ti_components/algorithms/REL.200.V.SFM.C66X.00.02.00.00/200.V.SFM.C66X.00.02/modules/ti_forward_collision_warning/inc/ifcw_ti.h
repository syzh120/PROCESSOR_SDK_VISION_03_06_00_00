/*
* module name : Forward Collision Warning
*
* module descripton : Generates distance of objects presents in scene
*
*/
/*
 
Copyright (c) 2009-2017 Texas Instruments Incorporated
 
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
    @file       iFCW_ti.h

    @brief      This file defines ivision interface for Object Distance and 
                Time To Collision (TTC) Algorithm. This module expects already
                detected objects and ground plane information to be provided as
                input, and it will generate Object Distance from host vehicle 
                and time to collision (FCW).

    @version 1.0 (October 2015) : Base version.

 */

/** @ingroup    ti_ivision_FCW_TI*/
/*@{*/
#ifndef IFCW_TI_H
#define IFCW_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**
  * Maximum number of input objects supported.
  */
#define FCW_TI_MAX_INPUT_OBJECTS                  (32)

  /**
  * @brief The unique constant function table for FCW
  */
  extern const IVISION_Fxns FCW_TI_VISION_FXNS;

  /**
  * @brief IRES interface of the FCW app
  */
  extern const IRES_Fxns FCW_TI_IRES_FXNS;

  /**
  @enum  FCW_TI_ObjectType
  
  @brief Enum to indicate type of object given to FCW algorithm.
         This is used to populate objType in FCW_TI_objectDescriptor structure.

  @param FCW_TI_OBJ_PEDESTRIAN : Pedestrian objects
  @param FCW_TI_OBJ_TRAFFIC_SIGN : traffic sign objects
  @param FCW_TI_OBJ_VEHICLE : vehicle objects
  */
  typedef enum
  {
    FCW_TI_OBJ_PEDESTRIAN = 0,
    FCW_TI_OBJ_TRAFFIC_SIGN = 1,
    FCW_TI_OBJ_VEHICLE = 2,
    FCW_TI_OBJ_MAX_OBJECTS

  } FCW_TI_ObjectType;

  /**
  @enum  FCW_TI_InBufOrder

  @brief User provides most of the information through buffer descriptor during
         process call. Below enums define the purpose of buffer.

  @param FCW_TI_IN_BUFDESC_OBJECT_PLANE : This buffer represents the buffer 
         which needs to be provided as input to algorithm, containing already 
         detected objects information.

  */
  typedef enum
  {
    FCW_TI_IN_BUFDESC_OBJECT_PLANE     = 0,
    FCW_TI_IN_BUFDESC_TOTAL
  } FCW_TI_InBufOrder ;


  /**
  @enum FCW_TI_OutBufOrder

  @brief Process call provides most of the information through buffer descriptor 
         during process call. Below enums define the purpose of out buffer.

  @param FCW_TI_OUT_BUFDESC_FEATURE_PLANES: This  buffer is filled up by FCW 
         algorithm and it provides the information about the various output 
         generated for each object e.g. distance from camera, time to collision, 
         velocity etc. 
  */
  typedef enum
  {
    FCW_TI_OUT_BUFDESC_TTC_PLANES = 0,
    FCW_TI_OUT_BUFDESC_TOTAL
  } FCW_TI_OutBufOrder ;

  /**
  @enum  FCW_TI_PrmStatus

  @brief Status of various parameters returned from algorithm. 

  @param FCW_ALG_PRM_INVALID: This paramter is not populated by the algorithm or
         its value is in invaide state.
  */  
  typedef enum
  {
    FCW_ALG_PRM_INVALID = -1
  } FCW_TI_PrmStatus;
  
  /**
  @enum  FCW_TI_ErrorCodes

  @brief Enumeration of error codes returned by FCW algorithm process call
  
  @param FCW_TI_ERRORTYPE_NUM_INBUF_LESS         : Number of input buffers 
         provides are less than required
  @param FCW_TI_ERRORTYPE_MAXNUMOBJECTS_EXCEEDED : Number of input objects 
         exceeds the maximum number of objects supported by FCW algorithm.
  @param FCW_TI_ERRORTYPE_INVALID_KF_PARAMS      : Kalman filter parameters 
         are invalid.
  @param FCW_TI_UNSUPPORTED_PARAMETER            : Unsupported parameter is 
         used by the algorithm
  */
  typedef enum
  {
    FCW_TI_ERRORTYPE_NUM_INBUF_LESS = IVISION_CUSTOMFAILBASE,
    FCW_TI_ERRORTYPE_MAXNUMOBJECTS_EXCEEDED,    
    FCW_TI_ERRORTYPE_INVALID_KF_BUF,
    FCW_TI_UNSUPPORTED_PARAMETER
  } FCW_TI_ErrorCodes;

  /**
  @enum  FCW_TI_ObjInfo
  
  @brief ObjInfo returned by FCW algorithm

  @param FCW_TI_OBJ_INFO_FAR_FROM_CAMERA  : Object is very far from camera
  @param FCW_TI_OBJ_INFO_NEAR_FROM_CAMERA : Object is very near to camera
  @param FCW_TI_OBJ_INFO_HIGH_FROM_GROUND : Object is very high from ground
  @param FCW_TI_OBJ_INFO_LOW_FROM_GROUND  : Object is very low from ground
  @param FCW_TI_OBJ_INFO_CAMERA_LANE      : Object in the lane in which camera 
                                            is moving.
  @param FCW_TI_OBJ_INFO_ERRONEOUS        : Object info given is error.

  */
  typedef enum
  {
    FCW_TI_OBJ_INFO_FAR_FROM_CAMERA = 0,
    FCW_TI_OBJ_INFO_NEAR_FROM_CAMERA,
    FCW_TI_OBJ_INFO_HIGH_FROM_GROUND,
    FCW_TI_OBJ_INFO_LOW_FROM_GROUND,
    FCW_TI_OBJ_INFO_CAMERA_LANE,
    FCW_TI_OBJ_INFO_ERRONEOUS 
  } FCW_TI_ObjInfo;


  /**
  @struct FCW_TI_CreateParams
  @brief  This structure contains all the parameters which controls FCW 
          algorithm at create time

  @param  visionParams
          Common parameters for all ivison based modules

  @param  maxNumObjects
          Maximum number of objects that can be processed by the module.
          
  @param  minObjDist
          Minimum object distance from camera to be considered by FCW algorithm. 
          This is in meters.
  
  @param  maxObjDist
          Maximum object distance from camera to be considered by FCW algorithm.
          This is in meters.
  
  @param  minObjHeight
          Minimum object height of the detected object to be considered by FCW 
          algorithm. This is in meters.  
  
  @param  maxObjHeight 
          Maximum object height of the detected object to be considered by FCW 
          algorithm. This is in meters.          

  @param  camIntPrm  
          3x3 floating point intrinsic camera parameters matrix  is given below.
                    _                 _
                   |   fx   0.0   x0   |
                   |   0.0   fy   y0   |
                   |_  0.0  0.0   1.0 _|
          
          Where fx and fy are standard scaling parameter in x and y direction. 
          Whereas (x0, y0) is the principal point , where optic axis intersects 
          the image plane.

  @param  rsvd1
          For future expansion. Should be set as zero

  @param  rsvd2
          For future expansion. Should be set as zero
  */
  typedef struct
  {
    IVISION_Params visionParams;
    uint16_t maxNumObjects     ;
    float    minObjDist        ;
    float    maxObjDist        ;
    float    minObjHeight      ;
    float    maxObjHeight      ;    
    float    camIntPrm[3][3]   ;
    uint16_t rsvd1             ;
    uint16_t rsvd2             ;
  } FCW_TI_CreateParams;

  /**
  @struct FCW_TI_objectDescriptor
  @brief  This structure contains the detected object properties such as 
          location-(x, y), size-(height, width), confidence (score) string 
          messages etc. Has been made compatible with object detection module
          
  @param  objTag
          Value or index to indicate, colour in case of pedestrian tracking or 
          traffic sign type.
          
  @param  objType
          Indicates the type of object detected. See enum FCW_TI_ObjectType for 
          supported object types.
          
  @param  objSubType
          Indicates the subtype of an object a defined type.

          This field is not used by FCW algorithm. It has been just put to make 
          object descriptor compatible to object detection algorithm          

  @param  xPos
          Location of the detected object in pixels along X direction.

  @param  yPos
          Location of the detected object in pixels along Y direction.

  @param  objWidth
          Width of the located object in pixels. Does not indicate actual width 
          of the object.

  @param  objHeight
          Width of the located object in pixels. Does not indicate actual height
          of the object. 

  @param  objScore
          Adaboost classifier score for the detected object.

          This field is not used by FCW algorithm. It has been just put to make 
          object descriptor compatible to object detection algorithm

  @param  objScale
          Scale at which the object was detected. A lower number indicates that 
          an object far from the camera was detected. A higher number indicates 
          that the object close to the camera was detected. This number may not 
          correspond to original image pyramid scale ratio. The numbers may 
          come out interpolated between scales. IEEE 32-bit single precision 
          floating point format.

          This field is not used by FCW algorithm. It has been just put to make 
          object descriptor compatible to object detection algorithm.

  @param  reserved0
          Reserved 32-bit field. Must be set to 0 for normal operation. 
          
  @param  reserved1
          Reserved 32-bit field. Must be set to 0 for normal operation.
  
  @param  reserved2
          Reserved 32-bit field. Must be set to 0 for normal operation.        

  */
  
  typedef struct
  {   
    uint32_t objTag;
    uint32_t objType;
    uint32_t objSubType;    
    int32_t  xPos;
    int32_t  yPos;    
    uint32_t objWidth;
    uint32_t objHeight;    
    float    objScore;
    float    objScale;    
    float    reserved0;
    float    reserved1;
    float    reserved2;
  } FCW_TI_objectDescriptor;


  /**
  @struct FCW_TI_OD_input
  
  @brief  This is the output structure given out by object detection algorithm 
          which is taken as input for FCW algorithm. It contains the number of 
          objects detected and FCW_TI_MAX_INPUT_OBJECTS instances of 
          FCW_TI_objectDescriptor structure. The number of valid descriptors is 
          governed by numObjects variable.

  @param  numObjects
          Number of objects provided to FCW algorithm.

  @param  errorCode
          Error Code returned for one process call by Object Detection module. 
          A value of 0 indicates no error. 
          
          This field is not used by FCW algorithm. It has been just put to make 
          object descriptor compatible to object detection algorithm

  @param  objDesc
          List of detected object descriptor.
          Max size FCW_TI_MAX_INPUT_OBJECTS
  */
  typedef struct
  {
    int32_t numObjects;
    int32_t errorCode;
    FCW_TI_objectDescriptor objDesc[FCW_TI_MAX_INPUT_OBJECTS];
  } FCW_TI_OD_input;

  /**

  @struct FCW_TI_InArgs
  
  @brief  This structure contains all the parameters which are given as an 
          input to FCW algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  camExtPrm 
          3x4 floating point extrinsic camera parameters matrix  is given below.
                    _                       _
                   |   r00  r01   r02   t0   |
                   |   r10  r11   r12   t1   |
                   |_  r20  r21   r22   t2  _|
          
          where rij are the rotation parameter and ti are the translation 
          parameter.
          
  @param  grndPlaneEq
          Computed ground plane equation in the form of A*X + B*Y + C*Z = 1.
          where X,Y,Z are three dimensional co-ordinates and A = grndPlaneEq[0],
          B = grndPlaneEq[1], C = grndPlaneEq[2].

  @param camHeightInMeter
         Camera height from ground plane in meters

  @param camOffsetInMeter
         Camera offset from from car front edge in meters
         
  @param  fps
          Frame per second of camera.

  @param  imgHeight
          Height of the input image.
          
  @param  reserved1
          Reserved 32-bit field. Must be set to 0 for normal operation.
  
  @param  reserved2
          Reserved 32-bit field. Must be set to 0 for normal operation.

  */
  typedef struct
  {
    IVISION_InArgs   iVisionInArgs      ;
    float            camExtPrm[3][4]    ;
    float            grndPlaneEq[3]     ;
    float            camHeightInMeter   ;
    float            camOffsetInMeter   ;
    float            fps                ;
    int16_t          imgHeight          ;    
    uint32_t         reserved1          ;
    uint32_t         reserved2          ;
  } FCW_TI_InArgs;

  /**
  @struct FCW_TI_Stats

  @brief  This structure reports statistics of running FCW algorithm

  @param  rsvd1
          Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  rsvd2
          Reserved 32-bit field. Must be set to 0 for normal operation.
  */

  typedef struct
  {
    uint32_t rsvd1              ; 
    uint32_t rsvd2              ;
  } FCW_TI_Stats;

  /**
  @struct FCW_TI_OutArgs

  @brief  This structure contains all the parameters which are given as 
  output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  FCWStats
          statistics output from FCW algorithm

  */
  typedef struct
  {
    IVISION_OutArgs  iVisionOutArgs;
    FCW_TI_Stats     FCWStats      ;
  } FCW_TI_OutArgs;

  /**
  @struct FCW_TI_objectWorldInfo

  @brief  This structure defines the format of output buffer given out from
          FCW algorithm.

  @param  objTag
          object tag identifier to relate with input object
  
  @param  distFrmCamera
          Distance between object and camera in meters.

  @param  timeToCollision
          Time to collide with the object in seconds.

  @param  objLocInWorld
          Location of object in terms of world co-ordinates.[X,Y,Z].

  @param  objLocInCamera
          Location of object in terms of camera co-ordinates.[X,Y,Z].

  @param  objVelcoity
          Estimated velocity of object. objVelcoity[0], objVelcoity[1],
          objVelcoity[2] represent velocity component in X,Y,Z direction
          respectively
  
  @param  objInfo
          It can be used as the first parameter check  if the object information
          is erroneous or not. Then only rest of the paramters may be used.
          Refer @FCW_TI_ObjInfo
  */
  typedef struct
  {
    uint16_t objTag;
    float    distFrmCamera;
    float    timeToCollision;
    float    objLocInWorld[3];
    float    objLocInCamera[3];
    float    objVelcoity[3];
    uint32_t objInfo;
  } FCW_TI_objectWorldInfo;

  /**
  @struct FCW_TI_output
  
  @brief  This is output structure given out by FCW module. It contains the
          number of objects detected and FCW_TI_MAX_INPUT_OBJECTS instances of 
          FCW_TI_objectWorldInfo structure. The number of valid descriptors is 
          governed by numObjects variable.

  @param  numObjects
          Number of objects for which information is generated

  @param  errorCode
          Error Code returned for one process call by FCW module. A value of 0 
          indicates no error.

  @param  cameraVelocity
          Estimated velocity of camera. cameraVelocity[0], cameraVelocity[1],
          cameraVelocity[2] represent velocity component in X,Y,Z direction
          respectively

  @param  cameraLocInWorld
          Camera location in world co-ordinates. [X,Y,Z].
  
  @param  objWorldInfo
          List of detected object descriptors for which information is 
          generated by FCW algorithm. Currently for all input objects 
          information is generated, and order of the output object information
          is same as input objects.
          
          Maximum size FCW_TI_MAX_INPUT_OBJECTS
  */

  typedef struct
  {
    int32_t numObjects;
    int32_t errorCode;
    float   cameraVelocity[3];
    float   cameraLocInWorld[3];
    FCW_TI_objectWorldInfo objWorldInfo[FCW_TI_MAX_INPUT_OBJECTS];
  } FCW_TI_output;

/*@}*/
/* ti_ivision_FCW_TI */

#ifdef __cplusplus
}
#endif

#endif /* IFCW_TI_H */
/*===========================================================================*/
/*     END of the FILE                                                       */
/*===========================================================================*/


