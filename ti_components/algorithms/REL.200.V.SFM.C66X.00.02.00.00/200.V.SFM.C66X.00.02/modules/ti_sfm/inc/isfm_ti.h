/*
* module name : Structure From Motion
*
* module descripton : Generates sparse 3D points from optical flow information in camera captured images
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
    @file       isfm_ti.h

    @brief      This file defines ivision interface for Structure From Motion (SFM)
                Algorithm. This module expects multiple feature points tracked location
                (in 2D-image co-ordinates) of past few frames (minimum 2 , maximum
                MAX_NUM_FRAMES_TO_TRACK ) to be provided as input, and it will generate
                its 3-D positions (in current frame camera co-ordinate system).

    @version 1.0 (October 2014) : Base version.

  @version 2.0 (October 2015) : Added ground plane output filed.
 */

/** @ingroup    ti_ivision_TI_SFM*/
/*@{*/
#ifndef ISFM_TI_H
#define ISFM_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Size of the Camera Extrinsic parameters consisting of
 * rotation and translation parameters.
 */
#define SFM_TI_CAMERA_EXTRENSIC_PARAM_SIZE  (12)

/*
 * Size of Camera Intrinsic parameters.
 */
#define SFM_TI_CAMERA_INTRINSIC_PARAM_SIZE  (9)

/*
 * Maximum number of past frames for which a tracked feature
 * point location is provided to the SFM module.However in SFM
 * module actual usages of number of past points from one
 * track may be less than MAX_NUM_FRAMES_TO_TRACK.
*/
#define MAX_NUM_FRAMES_TO_TRACK  (16)

/**
 * @brief The unique constant function table for SFM
 */
extern const IVISION_Fxns SFM_TI_VISION_FXNS;

/**
* @brief IRES interface of the SFM app
*/
extern const IRES_Fxns SFM_TI_IRES_FXNS;


/**
  @brief User provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of buffer.

  @param SFM_TI_IN_BUFDESC_FEATURE_PLANE: This buffer descriptor provides the
         feature planes representing the track information. Input buffer is not
         image buffer. It is continuous array of objects of the structure
         /c SFM_TI_trackInfo. Where each object corresponds to track information
         of one particular feature point in image. inBufs :: bufDesc[SFM_TI_IN_BUFDESC_FEATURE_PLANE]
         :: bufPlanes[0] :: width should be greater than or equal to number of
         input tracks which should be equal to inArgs :: numTracks

*/
typedef enum
{
  SFM_TI_IN_BUFDESC_FEATURE_PLANE     = 0,
  SFM_TI_IN_BUFDESC_TOTAL
} SFM_TI_InBufOrder ;


/**
  @brief Process call provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  @param SFM_TI_OUT_BUFDESC_FEATURE_PLANES: This  buffer is filled up by SFM algorithm
         with a list of estimated 3D points location and their corresponding image pixel location.
         Output buffer is treated as continuous array of objects of the structure /c SFM_TI_output.
         Where each object corresponds to information related one reconstructed 3-D point from one
         track information /c SFM_TI_trackInfo. Output buffer is not image buffer, it is set
         of objects of 'SFM_TI_output' placed in linear memory. Since number of output buffer
         is not known at the time of process call, hence out buf should be allocated assuming maximum
         possible number of 3D output points. Maximum number of out 3D points can be equal to maxNumTracks*6.
         Hence user should set outBufs :: bufDesc[SFM_TI_OUT_BUFDESC_FEATURE_PLANES] :: bufPlanes[0]
         ::width greater than or equal to (maxNumTracks*6). maxNumTracks has to be set at the time of
         create API call.
  */

typedef enum
{
  SFM_TI_OUT_BUFDESC_FEATURE_PLANES = 0,
  SFM_TI_OUT_BUFDESC_TOTAL
} SFM_TI_OutBufOrder ;

/**
  @brief Defines the type 3D output data to be gnerated from SFM modules

  SFM_TI_OUT_CUR_3D_POINTS : Output only the 3D points generated from the
                             tracks provided in current process call

  SFM_TI_OUT_CUR_PREV_3D_POINTS_DEFAULT :
                             Output 3D points generated from the
                             tracks provided in current process call and
                             previous process calls. Previous 6 frames
                             tracks can be considered for generating
                             current output of 3D points. Not supported
                             currently
 */
typedef enum
{  

  SFM_TI_OUT_CUR_3D_POINTS              = 0,
  SFM_TI_OUT_CUR_PREV_3D_POINTS         = 1,
  SFM_TI_OUT_CUR_PREV_3D_POINTS_DEFAULT = SFM_TI_OUT_CUR_3D_POINTS

} SFM_TI_Out3DPointsType;

/**
  @brief Defines the type normalization to camera extrinsic parameters

  SFM_TI_CAM_EXT_PRM_NO_NORM : No Normalization is done, it is used as it is.

  SFM_TI_CAM_EXT_PRM_LOCAL_NORM : Internal Normalization is done

*/

typedef enum
{

  SFM_TI_CAM_EXT_PRM_NO_NORM              = 0,
  SFM_TI_CAM_EXT_PRM_LOCAL_NORM           = 1,
  SFM_TI_CAM_EXT_PRM_NORM_DEFAULT         = SFM_TI_CAM_EXT_PRM_NO_NORM

} SFM_TI_CamExtPramNormType;

/**
  @brief Defines the method to calculate/estimate Fundamental Matrix. It is recommended
         to use SFM_TI_FMAT_FROM_RT_PARAMS to save computation cycle.

  SFM_TI_FMAT_8POINT_RANSAC  : Estimate using 8 point algorithm with RANSAC iteration

  SFM_TI_FMAT_FROM_RT_PARAMS : Calculate it using available rotation and translation
                               parameters provided through extrinsic parameters
                 SFM_TI_InArgs :: camExtPrm

*/

typedef enum
{

  SFM_TI_FMAT_8POINT_RANSAC           = 0,
  SFM_TI_FMAT_FROM_RT_PARAMS          = 1,
  SFM_TI_FMAT_EXT_PRM_NORM_DEFAULT    = SFM_TI_FMAT_FROM_RT_PARAMS

} SFM_TI_FmatrixCalcType;

/**
  @struct SFM_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          SFM algorithm at create time

  @param  visionParams
          Common parameters for all ivison based modules

  @param  camExtPrmNormType
          Type of normalization done on extrnsic camera parameter. Refer /c SFM_TI_CamExtPramNormType.

  @param  maxNumTracks
          Maximum Number of tracks information provided in one process call

  @param  cameraIntParams
          Camera Intrinsic Parameters. Format of intrinsic parameter
          is [ax 0.0 x0 0 ay y0 0 0 1.0]. Where ax and ay are
          standard scaling parameter in x and y direction. Whereas
          (x0, y0) is the principal point , where optic axis
          intersects the image plane.

  @param  rsvd1
          For future expansion. Should be set as zero

  @param  rsvd2
          For future expansion. Should be set as zero


*/
typedef struct
{
  IVISION_Params visionParams;
  uint32_t camExtPrmNormType ;
  uint16_t maxNumTracks      ;
  float    camIntPrm[SFM_TI_CAMERA_INTRINSIC_PARAM_SIZE];
  uint16_t rsvd1             ;
  uint16_t rsvd2             ;
} SFM_TI_CreateParams;

/**

  @struct SFM_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to OD algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  numTracks
          Total number of input feature points tracks provided in current
          process call. This will be also used as to indicate maximum valid
      entris in input buffer /c SFM_TI_IN_BUFDESC_FEATURE_PLANE.

  @param  camExtPrm : Camera Extrinsic Parameters. Format of camera extrinsic parameters is [ r00
          r01 r02 t0 r10 r11 r12 t1 r20 r21 r22 t2], where rij are the rotation parameter,
          and ti are the translation parameter.
      If this pointer is provided as NULL, then these parameters are computed internally.

  @param  fMatCalcMethod
          This controls how Fundamental Matrix is estimated/calculated.
          There is possibility of estimating Fundamental matrix using
          feature point correspondence between two frames, whereas there
          could be another method to calculate using rotation and translation
          parameters provided.
          Refer @SFM_TI_FmatrixCalcType for various supported values and
          default values.

  @param  fMatrixPrunEn
          Control to enable or disable Fundamental matrix based pruning of
          the input tracks. User should set this as '1' to enable this
          pruning.

  @param  fMatrixInTh
          Inlier threshold used in Fundamental matrix based pruning.

  @param  maxRansacItr
          Maximum number of RANSAC iteration in F matrix iteration. Its
          Supported value is [0, 200]. User should set default value
          for this as 90. When value zero is set then algorithm does
          optimal number of iterations.

  @param  maxTriangItr
          Maximum number of iteration in triangulation. Supported value for
          this is [1,10]. User should set default value which is 4.

  @param  curPrev3DPtFlag
          Controls the preserving of 3D points for future output. Its valid
          value are SFM_TI_OUT_CUR_3D_POINTS and SFM_TI_OUT_CUR_PREV_3D_POINTS.

          SFM_TI_OUT_CUR_3D_POINTS : Only current points are given as output
          SFM_TI_OUT_CUR_PREV_3D_POINTS: Current points and previous points
                                         transformed to current frame are given
                                         as output
  @param  trackPtQfmt
          Q format in which tracked feature point image locations are provided.
          Supported value for this is [1,8].

  @param  pointPruneAngle
          Angle threshold used for angle based pruning. Supported Values is
          [0.0 10.0]

  @param  staticFrmTh
          Threshold to determine wheather current frame is static or not. Norm of 
          the current frame camera translation  with respect to previous frame should
          be less than this threshold to flag current frame as static frame.
          
  @param  reserved0
          Reserved 32-bit field. Must be set to 0 for normal operation.

  @param  reserved1
          Reserved 32-bit field. Must be set to 0 for normal operation.

*/
typedef struct
{
  IVISION_InArgs   iVisionInArgs      ;
  uint32_t         numTracks          ;
  float            camExtPrm[SFM_TI_CAMERA_EXTRENSIC_PARAM_SIZE];
  uint32_t         fMatrixCalcMethod  ;
  uint32_t         fMatrixPrunEn      ;
  uint32_t         fMatrixInTh        ;
  uint32_t         maxRansacItr       ;
  uint32_t         maxTriangItr       ;
  uint8_t          curPrev3DPtFlag    ;
  uint8_t          trackPtQfmt        ;
  float            pointPruneAngle    ;
  float            staticFrmTh        ;
  uint32_t         reserved0          ;
  uint32_t         reserved1          ;
} SFM_TI_InArgs;

/**

  @struct SFM_TI_Stats

  @brief  This structure reports statistics of running SFM

  @param  numIterFMat
          Number of actual RANSAC iteration in F matrix estimation

  @param  numInlierFmat
          Number of inlier determined by the pruning based
          on F matrix
          
  @param  isStatic
          if this is '1' then current frame has been declared as static
          frame.           

  @param  numCur3DPnts
          Number of 3D points generated from all the track info-
          rmation provided in current process call. This may not
          be the actual number of output 3D points.

*/

typedef struct
{
  uint32_t numIterFMat        ;
  uint32_t numInlierFmat      ;
  uint32_t numCur3DPnts       ;
  uint8_t  isStatic           ;
  uint32_t rsvd1              ;
  uint32_t rsvd2              ;
} SFM_TI_Stats;

/**
  @struct SFM_TI_OutArgs

  @brief  This structure contains all the parameters
          which are given as output.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  sfmStats
          Stats structure of type SFM_TI_Stats for SFM

  @param  outNumPoints
          Total number of output points. should be used to indicate
      maximum number of valid output entries in out buffer /c SFM_TI_OUT_BUFDESC_FEATURE_PLANES.
*/
typedef struct
{
  IVISION_OutArgs  iVisionOutArgs;
  SFM_TI_Stats     sfmStats      ;
  uint32_t         outNumPoints  ;
} SFM_TI_OutArgs;

/**
  @struct SFM_TI_output

  @brief  This structure defines the format of output buffer
          given out from algorithm.

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
          point was generated.

  @param  trackId
          Id of the track in the frame SFM_TI_output :: frmId from
          which this 3D point got generated.

*/
typedef struct
{
  float    point2dX;
  float    point2dY;
  float    point3dX;
  float    point3dY;
  float    point3dZ;
  uint16_t frmId;
  uint16_t trackId;

} SFM_TI_output;
/**

  @struct SFM_TI_trackInfo

  @brief  This structure defines the format in which SFM module expects a
          particular feature point's tracked location in image plane.

  @param  age : Age of the current key points that is being tracked.
                If the age is zero then the key point is assumed to be
                not valid.
                SFM Module assumes latest feature point in track to be present
                at index of age % MAX_NUM_FRAMES_TO_TRACK. And then past frame
                information are assumed to be present in back location from
                current location in circular fashion with circularity size as
                MAX_NUM_FRAMES_TO_TRACK. Location of track from frame to frame
                has to be fixed in inBuf :: SFM_TI_IN_BUFDESC_FEATURE_PLANE.
                Location of a particular track in inBuf is assumed to be same
                throught the frames, till it is getting tracked. All the tracks
                corresponding to the value set SFM_TI_InArgs :: numTracks,
                needs set properly in inBuf. If any track becomes invalid then its
                age should be set to zero or that location can be replaced with
                a new track which was not part of any of the previous known
                tracks.

  @param  x :   Array of horizontal image co-ordinates in Q format for
                MAX_NUM_FRAMES_TO_TRACK frames. Value of Q format has
                to be provided through SFM_TI_InArgs :: trackPtQfmt.

  @param  y :   Array of vertical image co-ordinates in Q format for
                MAX_NUM_FRAMES_TO_TRACK frames. Value of Q format has
                to be provided through SFM_TI_InArgs :: trackPtQfmt.

*/
typedef struct
{
  uint16_t age                       ;
  uint16_t x[MAX_NUM_FRAMES_TO_TRACK];
  uint16_t y[MAX_NUM_FRAMES_TO_TRACK];

}SFM_TI_trackInfo;

/*@}*/
/* ti_ivision_TI_SFM */

#ifdef __cplusplus
}
#endif

#endif /* ISFM_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


