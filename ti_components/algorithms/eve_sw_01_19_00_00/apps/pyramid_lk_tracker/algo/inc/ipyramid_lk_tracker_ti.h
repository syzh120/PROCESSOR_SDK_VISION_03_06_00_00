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
 *  @file       ipyramid_lk_tracker_ti.h
 *
 *  @brief      This file defines the ivision interface for pyramid_lk_tracker Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    ti_ivision_PYRAMID_LK_TRACKER */
/*@{*/
#ifndef IPYRAMID_LK_TRACKER_TI_H
#define IPYRAMID_LK_TRACKER_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief Buffer index for current input image data in input buffer list
 */
#define PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX (0)

/**
 * @brief Buffer index for Previous input image data in input buffer list
 */
#define PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX (1)

/**
 * @brief Buffer index for key points co-ordinates in packed XY format for previous
 * frame in input buffer list
 */
#define PYRAMID_LK_TRACKER_TI_IN_KEY_POINTS_BUF_IDX (2)
/**
 * @brief Buffer index for estimated buffer co-ordinates of key points in packed XY format for
 * current frame in input buffer list
 */
#define PYRAMID_LK_TRACKER_TI_EST_KEY_POINTS_BUF_IDX (3)

/**
 * @brief Buffer index for tracked co-ordinate of key points in packed XY format for current
 * frame in output buffer list
 */
#define PYRAMID_LK_TRACKER_TI_OUT_KEY_POINTS_BUF_IDX (0)
/**
 * @brief Buffer index for error measure of key points being tracked for current
 * frame in output buffer list
 */
#define PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX (1)

/**
* @brief Using iVISION buf planes to get multiple pyramids so max value
         allowed (4) is dependent on iVISION
*/
#define PYRAMID_LK_TRACKER_TI_MAXLEVELS   (8)

/**
* @brief Using iVISION buf planes to get multiple pyramids so max value
         allowed (4) is dependent on iVISION
*/
#define PYRAMID_LK_TRACKER_TI_MAXLEVELS_PER_CALL   (IVISION_MAX_NUM_PLANES)

/**
 * @brief Maximum Iteration supported by Algorithm
 */
#define PYRAMID_LK_TRACKER_TI_MAXITERATION   (20)

/**
 * @brief Maximum search range in each diretcion supported by Algorithm
 */
#define PYRAMID_LK_TRACKER_TI_MAX_SEARCH_RANGE  (18)

/**
  @brief Error code returned by the PYRAMID_LK_TRACKER algorithm

  IPYRAMID_LK_TRACKER_ERRORTYPE_MAXLEVELS_EXCEEDED: The number of levels requested by user are
  more than supported by algorithm

  IPYRAMID_LK_TRACKER_ERRORTYPE_MAXITERATION_EXCEEDED: The maximum number of iteration
  requested by user are more than supported by algorithm

  IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_BUFFERS: The number of input/output buffers or size
  of them is not sufficient for algorithm

  IPYRAMID_LK_TRACKER_ERRORTYPE_NO_KEY_POINTS: Number of key points to be processed is requested as zero.

  IPYRAMID_LK_TRACKER_ERRORTYPE_NUMLEVELS_PER_CALL_EXCEEDED: Number of Levels to be
  processed is requested as zero or greater than  than PYRAMID_LK_TRACKER_TI_MAXLEVELS_PER_CALL

  IPYRAMID_LK_TRACKER_ERRORTYPE_START_LEVEL_EXCEEDED: Start Level to be
  processed is requested is greater than or equal to PYRAMID_LK_TRACKER_TI_MAXLEVELS

  IPYRAMID_LK_TRACKER_ERRORTYPE_INVALID_START_LEVEL_OR_NUMLEVELS :
  StartLevel and numLevels provided by the user is not a valid combination.
  Example : numLevels = 5 startLevel   = 2


  IPYRAMID_LK_TRACKER_ERRORTYPE_SEARCH_RANGE_EXCEEDED: Search range requiested is
  requested is greater than or equal to PYRAMID_LK_TRACKER_TI_MAX_SEARCH_RANGE or
  lesss than 1.

  IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_IM_SIZE: Image size (width or height)
  of the given level is smaller than the minimum suported image size 9


*/
typedef enum
{
  IPYRAMID_LK_TRACKER_ERRORTYPE_MAXLEVELS_EXCEEDED = IVISION_CUSTOMFAILBASE,
  IPYRAMID_LK_TRACKER_ERRORTYPE_MAXITERATION_EXCEEDED,
  IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_BUFFERS,
  IPYRAMID_LK_TRACKER_ERRORTYPE_NO_KEY_POINTS,
  IPYRAMID_LK_TRACKER_ERRORTYPE_NUMLEVELS_PER_CALL_EXCEEDED,
  IPYRAMID_LK_TRACKER_ERRORTYPE_START_LEVEL_EXCEEDED,
  IPYRAMID_LK_TRACKER_ERRORTYPE_INVALID_START_LEVEL_OR_NUMLEVELS,
  IPYRAMID_LK_TRACKER_ERRORTYPE_SEARCH_RANGE_EXCEEDED,
  IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_IM_SIZE
} IPYRAMID_LK_TRACKER_ErrorType;

/**
 * @brief The unique const funtion table for the PYRAMID_LK_TRACKER_TI.
 */
extern const IVISION_Fxns PYRAMID_LK_TRACKER_TI_VISION_FXNS;

/**
* @brief IRES interface of the PYRAMID_LK_TRACKER_TI_ algorithm
*/
extern const IRES_Fxns PYRAMID_LK_TRACKER_TI_IRES;

/**
  @struct PYRAMID_LK_TRACKER_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          PYRAMID_LK_TRACKER corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imWidth
          Width in bytes for the input image

  @param  imHeight
          Height in bytes for the input image

  @param  numLevels
          Number of levels for the pyramid

  @param  maxItersLK
          Maximum number of iteration for each level

  @param  minErrValue
          Minimum flow vector difference value that needs to be
          considered as no motion and exit the iteration for
          each level

  @param  numKeyPoints
          Number of key points to be tracked

@param  searchRange
         Search range in pixel for each level

*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t imWidth  ;
  uint16_t imHeight ;
  uint16_t numLevels;
  uint16_t maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint16_t minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint16_t numKeyPoints;
  uint8_t searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
} PYRAMID_LK_TRACKER_TI_CreateParams;

/**
  @struct PYRAMID_LK_TRACKER_TI_InArgs
  @brief  This structure contains all the parameters which controls
          the applet at process time

  @param  iVisionInArgs
          Common InArgs for all ivison based modules

  @param  numKeyPoints
          Total number of Key points (corners) to be tracked

  @param  numLevels
          Total number of levels to be processed in the current call

  @param  startLevel
          Start level indicates the level of the lowest resolution
          that needs to be processed in the current process call.
          Level numbering are in increasing order for decreasing
          resolution. Level 0 means the highest resolution of all
          the pyramid levels that user is intend to process.
          Example: User want to process total of 8 levels
          and the levels are 0,1,2,3,4,5,6,7
          then user can call the LK tracker applet twice for
          each frame with below parameters.
          First call with startLevel = 7 and numLevels = 5 (Will process 7,6,5,4,3)
          Second call with startLevel = 2 and numLevels = 3 (Will process 2,1,0)

  @param SADthreshold
          Threshold for SAD to be applied to get the number of
          points below the this thresold
 */

typedef struct
{
    IVISION_InArgs iVisionInArgs;
    uint16_t numKeyPoints;
    uint8_t  numLevels;
    uint8_t  startLevel;
    uint16_t SADthreshold;
} PYRAMID_LK_TRACKER_TI_InArgs;

/**
  @struct PYRAMID_LK_TRACKER_TI_OutArgs
  @brief  This structure contains all the parameters which controls
          the applet at process time

  @param  iVisionOutArgs
             Common outArgs for all ivison based modules

  @param  numValidPoints
          Total number of valid key points after applying
          SAD threshold. This value is calculated only for the
          base level and is invalid if this applet is called without
          the base level.
 */

typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint16_t numValidPoints;
} PYRAMID_LK_TRACKER_TI_OutArgs;

/*@}*/
/* ti_ivision_PYRAMID_LK_TRACKER */

#endif /*IPYRAMID_LK_TRACKER_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/
