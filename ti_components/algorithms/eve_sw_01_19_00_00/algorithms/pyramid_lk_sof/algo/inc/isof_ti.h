/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/**
 *  @file       isof_ti.h
 *
 *  @brief      This file defines the ivision interface for SOF algorithm
 *  @version 0.0 (Aug 2014) : Base version.
 */

/** @ingroup    ti_ivision_SOF */
/*@{*/
#ifndef ISOF_TI_H
#define ISOF_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include "ipyramid_lk_tracker_ti.h"
#include "ifast9_best_feature_to_front_ti.h"
#include "iHarrisCornerDetection32_ti.h"

/**
 * @brief The unique const funtion table for the SOF_TI.
 */
extern const IVISION_Fxns SOF_TI_VISION_FXNS;

/**
* @brief IRES interface of the SOF_TI_ algorithm
*/
extern const IRES_Fxns SOF_TI_IRES;

/**
* @brief Max levels allowed by SOF
*/
#define SOF_TI_MAXLEVELS   (8)

/**
* @brief Max Width allowed by SOF
*/
#define SOF_TI_MAXWIDTH     (1920)

/**
* @brief Max Height allowed by SOF
*/
#define SOF_TI_MAXHEIGHT    (1088)


/**
  @brief Error code returned by the SOF algorithm

  ISOF_ERRORTYPE_MAXLEVELS_EXCEEDED: The number of levels request by user are
  more than supported by SOF algorithm

  ISOF_ERRORTYPE_INVALID_START_XY : The startX and Y are beyond the image boundary

  ISOF_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are beyond the supported

  ISOF_ERRORTYPE_IMGPYRAMID_CREATE_FAIL: Failure while creating image Pyramid

  ISOF_ERRORTYPE_FAST9_CORNER_CREATE_FAIL: Failure while creating fast9 corner detector

  ISOF_ERRORTYPE_FAST9_BFFT_CREATE_FAIL: Failure while creating fast9 best feature to front

  ISOF_ERRORTYPE_YUV_PADDING_CREATE_FAIL: Failure while creating  YUV Padding applet

  ISOF_ERRORTYPE_HARRIS_KD_CREATE_FAIL: Failure while creating  Harris corner detection applet

  ISOF_ERRORTYPE_NOT_VALID_KD_METHOD: Key Point detecttion method requisted user is not supported

  ISOF_ERRORTYPE_LK_TRACKER_CREATE_FAIL: Failure while creating Pyramidal LK tracker applet

  ISOF_ERRORTYPE_INSUFF_MEM_FOR_IO_BUFFS: Internal Memory requested by
  the algorithm is not sufficient for the given configurartion

*/

typedef enum
{
  ISOF_ERRORTYPE_MAXNUMFEATURES_EXCEEDED = IVISION_CUSTOMFAILBASE,
  ISOF_ERRORTYPE_MAXLEVELS_EXCEEDED,
  ISOF_ERRORTYPE_INVALID_START_XY,
  ISOF_ERRORTYPE_INVALID_IMAGE_DIMS,
  ISOF_ERRORTYPE_IMGPYRAMID_CREATE_FAIL,
  ISOF_ERRORTYPE_FAST9_CORNER_CREATE_FAIL,
  ISOF_ERRORTYPE_FAST9_BFFT_CREATE_FAIL,
  ISOF_ERRORTYPE_YUV_PADDING_CREATE_FAIL,
  ISOF_ERRORTYPE_HARRIS_KD_CREATE_FAIL,
  ISOF_ERRORTYPE_BIN_IMG_TO_LIST_CREATE_FAIL,
  ISOF_ERRORTYPE_NOT_VALID_KD_METHOD,
  ISOF_ERRORTYPE_LK_TRACKER_CREATE_FAIL,
  ISOF_ERRORTYPE_INSUFF_MEM_FOR_IO_BUFFS,
  ISOF_ERRORTYPE_MAX_ERROR_CODE

} ISOF_ErrorType;

/**
  @brief The key points in the image can be detetcted using
  any of the below suported methods

  SOF_EXTERNAL_KEY_POINTS: Key points are provided by the user through a input buffer

  SOF_HARRIS_KEY_POINTS: Harris key point detetctor method will be used by the algorithm

  SOF_FAST9_KEY_POINTS: Fast9 key point detetctor method along with best
  feature to front will be used by the algorithm

*/
typedef enum
{
  SOF_EXTERNAL_KEY_POINTS = 0,
  SOF_HARRIS_KEY_POINTS   = 1,
  SOF_FAST9_KEY_POINTS   = 2
} SOF_KeyPointDetectMethod;

/**
  @brief This enum defines the methods which can be used for different methods in which
  tracks can be formed

  SOF_TRACK_OFFSET_METHOD_IMAGE_ORIGIN: Tracks coordinates will be with respect to the image
  origin

  SOF_TRACK_OFFSET_METHOD_ROI_ORIGIN: Tracks coordinates will be with respect to the ROI
  origin

*/
typedef enum
{
  SOF_TRACK_OFFSET_METHOD_IMAGE_ORIGIN = 0,
  SOF_TRACK_OFFSET_METHOD_ROI_ORIGIN  = 1
} SOF_TrackOffsetMethod;


/**
* @brief Number of frames for which the tracking
information needs to be maintained by the algorithm
This value shall be power of 2
*/
#define MAX_NUM_FRAMES_TO_TRACK  (16)

/**

  @struct strackInfo

  @brief  This structure contains tracking information for each key points

  @param  age
          Age of the current key points that is being tracked.
          If the age is zero then the key point is not valid.
          After 65535 (2^16 - 1) age will be set to (65535 - MAX_NUM_FRAMES_TO_TRACK)

  @param  x
          Array of horizontal co-oridinates in Q4 format for MAX_NUM_FRAMES_TO_TRACK frames

  @param  y
          Array of vertical co-oridinates in Q4 format for MAX_NUM_FRAMES_TO_TRACK frames

*/
typedef struct
{
  uint16_t age;
  int16_t x[MAX_NUM_FRAMES_TO_TRACK];
  int16_t y[MAX_NUM_FRAMES_TO_TRACK];
}strackInfo;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  SOF_TI_BUFDESC_IN_CURR_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by algorithm.

  SOF_TI_BUFDESC_IN_KEY_POINTS_BUFFER: Input key points buffer.
  This buffer will only be used when the
  SOF_KeyPointDetectMethod is SOF_EXTERNAL_KEY_POINTS

*/
typedef enum
{
  SOF_TI_BUFDESC_IN_CURR_IMAGEBUFFER = 0,
  SOF_TI_BUFDESC_IN_KEY_POINTS_BUFFER,
  SOF_TI_BUFDESC_IN_TOTAL
} ISOF_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  SOF_TI_BUFDESC_OUT_KEY_POINTS_BUFFER:
  This buffer descriptor should point to a plane capable of holding XY
  list of tracked Key points current location in the current frame.
  so the size of this buffer is maxNumKeyPoints*(4) bytes. This buffer
  holds the output of the LK tracker modules without any pruning. This
  buffer is mostly meant to be used for the cases when we provide input
  key points externally. It is also important to note that this buffer may not
  be in sync with the trackInfo buffer because trackInfo buffer is populated
  after pruning the output of LK tracker based of errEstimate or to limit the number
  of output tracks

  SOF_TI_BUFDESC_OUT_ERR_ESTIMATE_BUFFER:
  This buffer descriptor should point to a plane capable of holding
  esitmated error measure (SAD based) for each key point that is being tracked.
  so the size of this buffer is maxNumKeyPoints*(2) bytes. This buffer
  holds the errEstimate output of the LK tracker modules before any pruing. This buffer
  will be in sync with the SOF_TI_BUFDESC_OUT_KEY_POINTS_BUFFER. This
  buffer is mostly meant to be used for the cases when we provide input
  key points externally. It is also important to note that this buffer may not
  be in sync with the trackInfo buffer because trackInfo buffer is populated
  after pruning the output of LK tracker based of errEstimate or to limit the number
  of output tracks

  SOF_TI_BUFDESC_OUT_TRACK_INFO_BUFFER:
  This buffer descriptor should point to a plane capable of holding
  tracking infomation for each key point that is being tracked across MAX_NUM_FRAMES_TO_TRACK frames.
  so the size of this buffer is maxNumKeyPoints*sizeof(strackInfo) bytes. The format in which
  trach info coordinates will be generated will depend on trackOffsetMethod which is part of
  SOF createparams

*/

typedef enum
{
  SOF_TI_BUFDESC_OUT_KEY_POINTS_BUFFER = 0,
  SOF_TI_BUFDESC_OUT_ERR_ESTIMATE_BUFFER,
  SOF_TI_BUFDESC_OUT_TRACK_INFO_BUFFER,
  SOF_TI_BUFDESC_OUT_TOTAL
} ISOF_OutBufOrder ;



/**

  @struct SOF_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          SOF algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imWidth
          Width in bytes for the input image

  @param  imHeight
          Height in bytes for the input image

  @param  roiWidth
          Processing region width

  @param  roiHeight
          Processing region height

  @param  startX
          X co-ordinate of the first (top-left) pixel in the image. Useful for a ROI processing
          in a bigger image. Though the information about ROI is supplied via iVISION buf
          desc but create time also this information is required as this algorithm use the XY
          value as some create time initialization. It is for base level only.

  @param  startY
          Y co-ordinate of the first (top-left) pixel in the image. Useful for a ROI processing
          in a bigger image. Though the information about ROI is supplied via iVISION buf
          desc but create time also this information is required as this algorithm use the XY
          value as some create time initialization. It is for base level only

  @param  numLevels
          Total number of pyramid levels including base level (1 means only base resolution)

  @param  keyPointDetectMethod
          The key points in the image can be detetcted can be selected using this parameter

  @param  keyPointDetectInterval
          key point detection interval in number of frames.
          Setting to zero detects the key points in each frame

  @param  maxNumKeyPoints
          Maximum number of key points that are tracked by LK tracker

  @param  maxPrevTrackPoints
          Maximum number of old tracks to keep for the next frame.

  @param  fast9Threshold
          Threshold on difference between intensity of the central pixel and pixels
          of a circle around this pixel for FAST9 corner detect applet.

  @param  scoreMethod
          Fast9 best feature to front applet supports more than one
          score calculation method. This paramer is used to select the score computation method

  @param  harrisScaling
          Scale foactor used in Harris score computation

  @param  nmsThreshold
          NMS threshold for harris corner detection applet

  @param harrisScoreMethod
         Method to use for Harris Score calculation. Refer to
         HARRIS_CORNER_DETECTION_32_TI_HarrisScoreMethod for valid values defined in
         "iHarrisCornerDetection32_ti.h" file

  @param harrisWindowSize
          Window size to be used for harris score calculation.  Considers a harrisWindowSize x harrisWindowSize
          neighborhood to calculate Harris Score. Kindly refer to HARRIS_CORNER_DETECTION_32_TI_HarrisWindowSize
          for valid values in "iHarrisCornerDetection32_ti.h" file

   @param suppressionMethod
          Suppression method to be used for non maximum suppression. Kindly refer to
          HARRIS_CORNER_DETECTION_32_TI_SuppressionMethod for valid values in
         "iHarrisCornerDetection32_ti.h" file

  @param trackOffsetMethod
          The method to be used for the output of track coordinates. Kindly refer to
          SOF_TrackOffsetMethod enum for valid values

  @param  maxItersLK
          Maximum number of iteration for each level

  @param  minErrValue
          Minimum flow vector difference value that needs to be
          considered as no motion and exit the iteration for
          each level

  @param  searchRange
         Search range in pixel for each level

*/

typedef struct
{
  IVISION_Params visionParams;

  uint16_t imWidth;
  uint16_t imHeight;
  uint16_t roiWidth;
  uint16_t roiHeight;
  uint16_t startX;
  uint16_t startY;
  uint8_t  numLevels;
  uint8_t  keyPointDetectMethod;
  uint8_t  keyPointDetectInterval;
  uint16_t maxNumKeyPoints;
  uint16_t maxPrevTrackPoints;
  uint8_t  fast9Threshold;
  uint8_t  scoreMethod;
  uint16_t harrisScaling;
  int32_t  nmsThreshold;
  uint8_t  harrisScoreMethod;
  uint8_t  harrisWindowSize;
  uint8_t  suppressionMethod;
  uint8_t  trackOffsetMethod;
  uint16_t maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint16_t minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint8_t  searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
} SOF_TI_CreateParams;


/**

  @struct SOF_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to SOF algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  numCorners
          Number of valid corners that need to be tracked. This parameter
          will be used only when SOF_KeyPointDetectMethod is SOF_EXTERNAL_KEY_POINTS

  @param  trackErrThr
          Estimated error of each key point will be compared
          against this threshold. If the error is below then
          this threshold then the key will be considred for
          tracking in next frame

  @param  trackMinFlowQ4
          Minimum flow absolute (abs(vx) + abs(vy)) flow
          vector of key point that needs to be considered
          for tracking in next frame

  @param  trackNmsWinSize
          Number of neighbouring pixel (in each direction) to be
          considred for non maximum suppression while considered
          key poits to track in next frame

  @param  reservered0
          This reserved parameter needs to be set to 0 for optimal performance

  @param  staticFrame
          A value of 1 Indicates if the current frame is static with respect to previous frame.
          A value of 0 indicates a non static frame */

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  int32_t           numCorners;
  uint32_t          trackErrThr;
  uint32_t          trackMinFlowQ4;
  uint32_t          trackNmsWinSize;
  uint8_t           reservered0;
  uint8_t           staticFrame;
} SOF_TI_InArgs;


/**

  @struct SOF_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by SOF algorithm at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  numCorners
          Total number of Key points (corners) that is beignt tracked in this frame.
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  int32_t numCorners;
} SOF_TI_OutArgs;


/*@}*/
/* ti_ivision_SOF */

#endif /*ISOF_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


