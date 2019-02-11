/*
* module name : Ground Plane Estimation
*
* module descripton : Generates ground plane information from sparse 3D points
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
    @file       igpe_ti.h

    @brief      This file defines ivision interface for Ground Plane and Scale Estimation
                Algorithm. This module expects already detected 3D points and its image
                correspondence (say it point cloud) along with detected objects in each
                frame as input, and it will generate the equation of ground plane in 3D
                world co-ordinate assuming camera as origin in each frame, also it will
                generate the expected scale which can be used to correct the unknown
                scaling present in point cloud 3D locations.
                Ground plane estimated from this algorithm is scale corrected, and hence
                no need of extra correction for that.

    @version 1.0 (December 2015) : Base version.

 */

/** @ingroup    ti_ivision_GPE_TI*/
/*@{*/
#ifndef IGPE_TI_H
#define IGPE_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**
  * Maximum number of input objects supported.
  */
  #define GPE_TI_MAX_INPUT_OBJECTS                  (32)

  /**
  * @brief The unique constant function table for GPE
  */
  extern const IVISION_Fxns GPE_TI_VISION_FXNS;

  /**
  * @brief IRES interface of the GPE app
  */
  extern const IRES_Fxns GPE_TI_IRES_FXNS;

  /**
  @enum  GPE_TI_InBufOrder

  @brief User provides most of the information through buffer descriptor during
         process call. Below enums define the purpose of various input buffers.

  @param GPE_TI_IN_BUFDESC_OBJECT_PLANE : This buffer represents the information
         containing already detected objects information. This buffer holds single
         object of the structure /ref GPE_TI_OD_input.

  @param GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE : This buffer represents the information
         containing the point cloud information. This buffer holds multiple objects
         of the structure /ref GPE_TI_pCloudDesc. Number of objects is equal to number
         of 3D points provided to alogirithm and this information of number of 3D points
         is passed to algorithm by setting the filed /ref GPE_TI_InArgs :: numPointCloud.

  */
  typedef enum
  {
    GPE_TI_IN_BUFDESC_OBJECT_PLANE         = 0,
    GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE     = 1,
    GPE_TI_IN_BUFDESC_TOTAL
  } GPE_TI_InBufOrder ;


  /**
  @enum GPE_TI_OutBufOrder

  @brief Process call provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of out buffer.

         Currenlty there is no output buffer from this algorithm.

  */
  typedef enum
  {
    GPE_TI_OUT_BUFDESC_TOTAL = 0
  } GPE_TI_OutBufOrder ;


  /**
  @enum  GPE_TI_ErrorCodes

  @brief Enumeration of error codes returned by GPE algorithm process call

  @param GPE_TI_ERRORTYPE_NO_ERROR
         No Error.

  @param GPE_TI_ERRORTYPE_NUM_INBUF_LESS : Number of input buffers
         provides are less than required

  @param GPE_TI_ERRORTYPE_MAXNUMOBJECTS_EXCEEDED : Number of input objects
         exceeds the maximum number of objects set at create time.

  @param GPE_TI_ERRORTYPE_MAXNUMPOINTCLOUD_EXCEEDED : Number of input point
         cloud exceeds the create time set value of maximum point cloud.

  @param GPE_TI_ERRORTYPE_NULL_POINTER
         If any input buffers are provided with NULL.
         
  @param GPE_TI_ERRORTYPE_UNSUPPORTED_PARAMETER : Unsupported parameter is
         passed to algorithm
  */

  typedef enum
  {
    GPE_TI_ERRORTYPE_NO_ERROR = 0,
    GPE_TI_ERRORTYPE_NUM_INBUF_LESS,
    GPE_TI_ERRORTYPE_MAXNUMOBJECTS_EXCEEDED,
    GPE_TI_ERRORTYPE_MAXNUMPOINTCLOUD_EXCEEDED,
    GPE_TI_ERRORTYPE_NULL_POINTER,
    GPE_TI_ERRORTYPE_UNSUPPORTED_PARAMETER
  } GPE_TI_ErrorCodes;

  /**
  @struct GPE_TI_CreateParams
  @brief  This structure contains all the parameters which controls GPE
          algorithm at create time

  @param  visionParams
          Common parameters for all ivison based modules

  @param  maxNumPointCloud
          Maximum number of point cloud in point cloud input buffer.

  @param  maxNumObjects
          Maximum number of objects that can be processed by the module.
          This value should not exceed GPE_TI_MAX_INPUT_OBJECTS

  @param  rsvd1
          For future expansion. Should be set as zero

  @param  rsvd2
          For future expansion. Should be set as zero
  */
  typedef struct
  {
    IVISION_Params visionParams;
    uint16_t maxNumPointCloud  ;
    uint16_t maxNumObjects     ;
    uint8_t  enScaleCompute    ;
    uint8_t  scaleComputeMethod;
    uint16_t rsvd1             ;
    uint16_t rsvd2             ;
  } GPE_TI_CreateParams;

  /**
  @struct GPE_TI_objectDescriptor

  @brief  This structure contains the detected object properties such as
          location-(x, y), size-(height, width), confidence (score) string
          messages etc. This structure has been made compatible with object
          detection module output. Currently objecti location and its width
          and height is used by GPE algorithm, rest fields has been kept for
          compatibility purpose.

  @param  objTag
          Unique value or index to a particular object in scene.

  @param  objType
          Indicates the type of object detected. See enum GPE_TI_ObjectType for
          supported object types. This field is not used in GPE algorithm.

  @param  objSubType
          Indicates the subtype of an object a defined type. This field is
          not used in GPE algorithm.

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
          Adaboost classifier score for the detected object. This field is not
          used by GPE algorithm.

  @param  objScale
          Scale at which the object was detected. A lower number indicates that
          an object far from the camera was detected. A higher number indicates
          that the object close to the camera was detected. This number may not
          correspond to original image pyramid scale ratio. The numbers may
          come out interpolated between scales. IEEE 32-bit single precision
          floating point format. This field is not used by GPE algorithm.

  @param  reserved0
          Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved1
          Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved2
          Reserved 32-bit field. Must be set to 0 for normal operation.

  */

  typedef struct
  {
    uint32_t objTag    ;
    uint32_t objType   ;
    uint32_t objSubType;
    int32_t  xPos      ;
    int32_t  yPos      ;
    uint32_t objWidth  ;
    uint32_t objHeight ;
    float    objScore  ;
    float    objScale  ;
    float    reserved0 ;
    float    reserved1 ;
    float    reserved2 ;
  } GPE_TI_objectDescriptor;


  /**
  @struct GPE_TI_OD_input

  @brief  This is the output structure given out by object detection algorithm
          which is taken as input for GPE algorithm.

  @param  numObjects
          Number of objects provided to GPE algorithm.

  @param  errorCode
          Error Code returned for one process call by Object Detection module.
          A value of 0 indicates no error.

          This field is not used by GPE algorithm. It has been just put to make
          object descriptor compatible to object detection algorithm

  @param  objDesc
          List of detected object descriptor.
          Max size GPE_TI_MAX_INPUT_OBJECTS
  */
  typedef struct
  {
    int32_t numObjects;
    int32_t errorCode ;
    GPE_TI_objectDescriptor objDesc[GPE_TI_MAX_INPUT_OBJECTS];
  } GPE_TI_OD_input;

 /**
  @struct GPE_TI_pCloudDesc

  @brief  This structure defines the format of input point cloud
          information given to algorithm.

  @param  point2dX
          x co-ordinate of 2d point in image plane

  @param  point2dY
          y co-ordinate of 2d point in image plane

  @param  point3dX
          x co-ordinate of 3d point in current frame camera
          coordinate system

  @param  point3dY
          y co-ordinate of 3d point in current frame camera
          coordinate system

  @param  point3dZ
          z co-ordinate of 3d point in current frame camera
          coordinate system

  @param  frmId
          inArgs input buffer Id of the frame from which this 3D
          point was generated. Not used by GPE algorithm.

  @param  trackId
          Id of the track in the frame SFM_TI_output :: frmId from
          which this 3D point got generated. Not used by GPE algorithm.

*/

  typedef struct
  {
    float    point2dX;
    float    point2dY;
    float    point3dX;
    float    point3dY;
    float    point3dZ;
    uint16_t frmId   ;
    uint16_t trackId ;
  } GPE_TI_pCloudDesc;


  /**

  @struct GPE_TI_configParams

  @brief  This structure contains all the parameters which are given as an
          input to GPE algorithm at frame level through inArgs.

  @param  cameraHeight
          Camera Height from ground plane in meters. Supported range is
          [0.0, 5.0], default value is 1.58.

  @param  fracWidthTrpzd
          Width of trapezoid as fraction of image width at last row of image.
          Trapezoid should be assumed to be placed at the center of last row
          of image, and this fraction tells that how much fraction of row
          width is occupied by the Trapezoid.Supported range is [0.0, 1.0],
          default value is 0.5.

  @param  fracHeightTrpzd
          Height of trapezoid as fraction of image height from bottom of
          the row. Supported range is [0.0, 5.0], default value is 1.58.

  @param  ptOnPlaneDistTh
          Threshold to control the validitity of the point on plane.
          If distance of the point on the best detected plane from
          camera origin is more than this threshold then consider
          detected plane as not a good plane.

  @param  maxCostTh
          Cost(Gain) has to be higher than this threshold to qualify
          detected plane as good plane.

  @param  trpzdImpFac
          If a 3D point present in trapezoid turns out to be inlier
          for a estimated plane in RANSAC iteration, then this field
          indicates how much extra importance to be given for that
          inlier.

  @param  baseRoll
          Base roll of the ground plane of the input image

  @param  deltaRoll
          Accepted delta roll from frame to frame

  @param  basePitch
          Base pitch of the ground plane of the input image

  @param  deltaPitch
          Accepted delta pitch from frame to frame

  @param  pointsOnlyInTrpzd
          If this flag is enabled then condsider only the points
          present in trapezoid.

  @param  noMovingObjectPtCloud
          If set to true then do not consider points present on
          object detected by object detection module

  @param  startY
          start row number for ROI selection

  @param  minPtsForRansac
          Minimum points to start RANSAC iteration

  @param  numRansacIteration
          Total number of ransac iteration

  */

  typedef struct
  {
    float            cameraHeight  ;
    float            fracWidthTrpzd;
    float            fracHeightTrpzd;
    float            ptOnPlaneDistTh;
    float            maxCostTh;
    float            trpzdImpFac;
    float            baseRoll;
    float            deltaRoll;
    float            basePitch;
    float            deltaPitch;
    uint8_t          pointsOnlyInTrpzd;
    uint8_t          noMovingObjectPtCloud;
    uint16_t         startY;
    uint16_t         minPtsForRansac;
    uint16_t         numRansacIteration;
    uint32_t         rsvd1;
    float            rsvd2;
  } GPE_TI_configParams;

  /**

  @struct GPE_TI_InArgs

  @brief  This structure contains all the parameters which are given as an
          input to GPE algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  fps
          operating frame per second

  @param  imgWidth
          Width of the input image.

  @param  imgHeight
          Height of the input image.

  @param  numPointCloud
          Number of input point cloud.

  @param  gpeParams
          Input configuration parameters for GPE algorithm.

  @param  reserved1
          Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved2
          Reserved 32-bit field. Must be set to 0 for normal operation.

  */
  typedef struct
  {
    IVISION_InArgs      iVisionInArgs ;
    float               fps           ;
    int16_t             imgWidth      ;
    int16_t             imgHeight     ;
    uint16_t            numPointCloud ;
    GPE_TI_configParams gpeParams     ;
    uint32_t            reserved1     ;
    uint32_t            reserved2     ;
  } GPE_TI_InArgs;

  /**
  @struct GPE_TI_Stats

  @brief  This structure reports statistics of running GPE algorithm

  @param  numValidRansacItr
          Total number of RANSAC iteration executed inside GPE algorithm

  @param  outPlaneCost
          Final cost of the estimated plane

  @param  outPitch
          Pitch of the output plane

  @param  outRoll
          Roll of the output plane

  @param  outDistFromPlane
          distance of camera to output plane

  @param  rsvd
          Reserved 32-bit field. Must be set to 0 for normal operation
  */

  typedef struct
  {
    uint32_t numValidRansacItr;
    float    outPlaneCost;
    float    outPitch;
    float    outRoll;
    float    outDistFromPlane;
    uint32_t rsvd[10];
  } GPE_TI_Stats;

  /**
  @struct GPE_TI_OutArgs

  @brief  This structure contains all the parameters which are given as
  output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  errorCode
          Error Code returned for one process call by GPE module. A value of 0
          indicates no error. Refer /ref GPE_TI_ErrorCodes for various error
          codes.

  @param  grndPlaneEq
          Computed ground plane equation in the form of A*X + B*Y + C*Z = 1.
          where X,Y,Z are three dimensional co-ordinates and A = grndPlaneEq[0],
          B = grndPlaneEq[1], C = grndPlaneEq[2]. This ground plane is already
          scale corrected, and it is with respect to camera assuming that as origin.

  @param  GPEStats
          statistics output from GPE algorithm
  */
  typedef struct
  {
    IVISION_OutArgs  iVisionOutArgs;
    float   grndPlaneEq[3]         ;
    float   scale                  ;
    int32_t errorCode              ;
    GPE_TI_Stats gpeStats          ;
  } GPE_TI_OutArgs                 ;


/*@}*/
/* ti_ivision_GPE_TI */

#ifdef __cplusplus
}
#endif

#endif /* IGPE_TI_H */
/*===========================================================================*/
/*     END of the FILE                                                       */
/*===========================================================================*/
