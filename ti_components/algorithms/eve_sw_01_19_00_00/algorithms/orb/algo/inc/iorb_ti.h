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
 *  @file       iorb_ti.h
 *
 *  @brief      This file defines the ivision interface for ORB algorithm
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    ti_ivision_ORB */
/*@{*/
#ifndef IORB_TI_H
#define IORB_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the ORB_TI.
 */
extern const IVISION_Fxns ORB_TI_VISION_FXNS;

/**
* @brief IRES interface of the ORB_TI_ algorithm
*/
extern const IRES_Fxns ORB_TI_IRES;

/**
* @brief Maximum number of features allowed by this applet across all levels
*/
#define ORB_TI_MAXNUMFEATURES   (2048)

/**
* @brief Max levels allowed by ORB
*/
#define ORB_TI_MAXLEVELS   (3)

/**
* @brief Max Width allowed by ORB - Currently validated for 400
*/
#define ORB_TI_MAXWIDTH     (1920)

/**
* @brief Max Height allowed by ORB - Currently validated for 400
*/
#define ORB_TI_MAXHEIGHT    (1088)


/**
  @brief Error code returned by the ORB algorithm 
  
  IORB_ERRORTYPE_MAXNUMFEATURES_EXCEEDED: The number of features desired by user
  are more than supported by ORB algorithm

  IORB_ERRORTYPE_MAXLEVELS_EXCEEDED: The number of levels request by user are
  more than supported by ORB algorithm

  IORB_ERRORTYPE_INVALID_START_XY : The startX and Y are beyond the image boundary

  IORB_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are beyond the supported

  IORB_ERRORTYPE_NULL_ORBPATTERN : NULL pointer of ORB pattern

  IORB_ERRORTYPE_IMGPYRAMID_CREATE_FAIL: Failure while creating image Pyramid

  IORB_ERRORTYPE_FAST9_CORNER_CREATE_FAIL: Failure while creating fast9 corner detector
  
  IORB_ERRORTYPE_FAST9_BFFT_CREATE_FAIL: Failure while creating fast9 best feature to front

  IORB_ERRORTYPE_HARRIS_BFFT_CREATE_FAIL: Failure while creating  harris best feature to front

  IORB_ERRORTYPE_RBRIEF_CREATE_FAIL: Failure while creating  compute rebrief 

*/

typedef enum
{
  IORB_ERRORTYPE_MAXNUMFEATURES_EXCEEDED = IVISION_CUSTOMFAILBASE,
  IORB_ERRORTYPE_MAXLEVELS_EXCEEDED,
  IORB_ERRORTYPE_INVALID_START_XY,
  IORB_ERRORTYPE_INVALID_IMAGE_DIMS,
  IORB_ERRORTYPE_NULL_ORBPATTERN,
  IORB_ERRORTYPE_IMGPYRAMID_CREATE_FAIL,
  IORB_ERRORTYPE_FAST9_CORNER_CREATE_FAIL,
  IORB_ERRORTYPE_FAST9_BFFT_CREATE_FAIL,
  IORB_ERRORTYPE_HARRIS_BFFT_CREATE_FAIL,
  IORB_ERRORTYPE_RBRIEF_CREATE_FAIL,
  IORB_ERRORTYPE_MAX_ERROR_CODE
  
} IORB_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor 
  
  ORB_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the 
  actual image data required by algorithm. The buffer is the highest level buffer

*/
typedef enum
{
  ORB_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  ORB_TI_BUFDESC_IN_TOTAL
} IORB_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  ORB_TI_BUFDESC_OUT_DESCRIPTOR: 
  This  buffer is filled up by algorithm and have 256 point descriptor for each 
  point in the same order as XY and Level list. so the size of this buffer is
  ORB_TI_MAXNUMFEATURES*(256/8) bytes
  
  ORB_TI_BUFDESC_OUT_XY_LIST: 
  This buffer descriptor (outBufs->bufDesc[ORB_TI_BUFDESC_OUT_XY_LIST]) should 
  point to a plane capable of holding XY list of bestNFeaturesOut. 
  so the size of this buffer is ORB_TI_MAXNUMFEATURES*(4) bytes

  ORB_TI_BUFDESC_OUT_LEVEL_ID: 
  This buffer descriptor (outBufs->bufDesc[ORB_TI_BUFDESC_OUT_LEVEL_ID]) should 
  point to a plane capable of holding level corresponding to XY list. 
  So the size of this buffer is ORB_TI_MAXNUMFEATURES*(1) bytes. 
  There is 1:1 mapping in XY array, level array and descriptor
  
*/

typedef enum
{
  ORB_TI_BUFDESC_OUT_DESCRIPTOR = 0,
  ORB_TI_BUFDESC_OUT_XY_LIST,
  ORB_TI_BUFDESC_OUT_LEVEL_ID,
  ORB_TI_BUFDESC_OUT_TOTAL
} IORB_OutBufOrder ;

/**
@brief 
  Since there is a limitation of number of Key points in the function chain after 
  corner detetct can handle. It is 2K per level after Fast9 corner detection and 
  then across level for the input of Harris best feature, the sum across all levels 
  has to be less than or equal to 2K.
  So after fast9 corner detect if the points are more than 2K then we need to 
  reduce the point. There are 2 mechanism to reduce: 
  (1) Pickup first 2K in the list - ORB_FAST9_CORNERS_INITIAL
  (2) Iteratively increase the fast9 threhold till it reaches a stage when points 
  are  < 2K - ORB_FAST9_CORNERS_ITERATIVE. This scheme is not advisable as it may 
  impact the performance if there are multiple iterations to reach the required
  key points

*/
typedef enum
{
  ORB_FAST9_CORNERS_INITIAL = 0,
  ORB_FAST9_CORNERS_ITERATIVE
} eORB_FAST9CornersSelectMethod ;


/** 
@brief 
  There are 2 methods to compute Fast9 score.
  (1) Threshold based method: This is similar to Opencv method
  (2) SAD based method
*/
typedef enum
{
   ORB_TI_THRESH_METHOD = 0,
   ORB_TI_SAD_METHOD = 1
} eORB_FAST9_BFTF_SCORE_METHOD ; 


/**

  @struct ORB_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          ORB algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image of highest level

  @param  imgFramePitch
          Pitch in bytes for the input image of highest level

  @param  imgFrameHeight
          Height in bytes for the input image of highest  level

  @param  numLevels
          Total number of pyramid levels including base level (1 means only base resolution)

  @param  fast9Threshold
          Threshold on difference between intensity of the central pixel and pixels
          of a circle around this pixel for FAST9 corner detect applet.

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

  @param  harrisSensitivityParam
          Value of sensitivity parameter (known as kappa in literature) for Harris score. 
          The format of this is Q1.15. Which means for a value of 0.04 you should 
          set 0.04*pow(2,15) =~ 1310

  @param  bestNFeaturesOut
          Total number of features to be generated across all levels

  @param  orbPattern
          This pattern defines the position of 256 pairs of src and dst to create 256 bit 
          rBRIEF descriptor. Total size of this memory are has to be 256*4. 
          For Exact format of this pattern - 
          256 bytes - X offset from center in src
          256 bytes - X offset from center in dst
          256 bytes - Y offset from center in src
          256 bytes - Y offset from center in dst
*/

typedef struct
{
  IVISION_Params visionParams;

  uint16_t imgFrameWidth;
  uint16_t imgFramePitch;
  uint16_t imgFrameHeight;
  uint8_t  numLevels; 
  uint8_t  fast9Threshold;
  uint16_t startX;
  uint16_t startY;
  uint16_t harrisSensitivityParam;
  uint16_t bestNFeaturesOut;
  uint8_t scoreMethod;
  const int8_t *orbPattern ;

} ORB_TI_CreateParams;


/**

  @struct ORB_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to ORB algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  fast9CornerSelectMethod
          Method of selecting fast9 corners if there are more corners 
          produced refer eORB_FAST9CornersSelectMethod. 

*/
typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t fast9CornerSelectMethod ;
} ORB_TI_InArgs;


/**

  @struct ORB_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by ORB algorithm at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  numCorners
          Total number of Key points (corners) detected. It can be 
          little different than configured value (totalFeatures) to 
          take care of alignments or if total points detected is less

  @param  activeImgWidth
          activeImgWidth is primarily <= imgFrameWidth and decided by
          applet to satisfy the internal DMA and kernel requirements. This
          is the actual number of horizontal pixels being processed. It is
          exported for user as informative

  @param  activeImgHeight
          activeImgHeight is primarily <= imgFrameHeight and decided by
          applet to satisfy the internal DMA and kernel requirements. This
          is the actual number of vertical lines being processed. It is
          exported for user as informative

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint16_t numCorners;
  uint16_t activeImgWidth [ORB_TI_MAXLEVELS];
  uint16_t activeImgHeight[ORB_TI_MAXLEVELS];
} ORB_TI_OutArgs;


/*@}*/
/* ti_ivision_ORB */

#endif /*IORB_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


