/*
*
* Copyright (c) 2015-2017 Texas Instruments Incorporated
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
 *  @file       istereovision_ti.h
 *  @brief     This file defines ivision interface for TI StereoVision algorithm              
 *  @version 1.0 (March 2015) : Base version.
 */

/** @ingroup    ti_ivision_stereovision*/
/*@{*/
#ifndef ISTEREO_TI_H
#define ISTEREO_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/*#define _TEST_EDMA */

#ifdef __cplusplus
extern "C" {
#endif

/* Algorithm capability limited to frame width of 1440 pixels */
#define STEREOVISION_TI_MAXWIDTH 1440
/**
 * @brief The unique const funtion table for the Stereovision algorithm.
 */
extern const IVISION_Fxns STEREOVISION_TI_VISION_FXNS;

/**
 * @brief IRES interface of the STEREO algorithm
 */
extern const IRES_Fxns STEREOVISION_TI_IRES;

/**
  @brief Error code returned by the Stereo-vision algorithm

  ISTEREOVISION_ERRORTYPE: 

  ISTEREOVISION_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are
  beyond supported

  ISTEREOVISION_ERRORTYPE_INVALID_NUM_INPUTS: Invalid number of input frames

  ISTEREOVISION_TI_ERRORTYPE_INVALID_NUM_INPUTS: Invalid mumber of input buffers

  ISTEREOVISION_ERRORTYPE_CREATE_FAIL: algorithm creation failed


 */
typedef enum
{
    STEREOVISION_TI_ERRORTYPE_0 = IVISION_CUSTOMFAILBASE,
    STEREOVISION_TI_ERRORTYPE_INVALID_IMAGE_DIMS,
    STEREOVISION_TI_ERRORTYPE_INVALID_NUM_INPUTS,
    STEREOVISION_TI_ERRORTYPE_CREATE_FAIL,
    STEREOVISION_TI_ERRORTYPE_MAX_ERROR_CODE
} STEREOVISION_TI_ErrorType;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  STEREOVISION_BUFDESC_IN_IMAGE: This buffer descriptor provides the actual image 8-bits data required by the algorithm.
  This image either comes from left or right camera and is the same image used to produce the disparity map.
  If the disparity map was produced by using left to right correspondence search then the image MUST be the left camera,
  otherwise it MUST be the right camera.

  STEREOVISION_BUFDESC_IN_DISPARITY: This buffer descriptor provides the
  8-bits disparity map produced by the stereovision module executed before this post-processing module.

  STEREOVISION_BUFDESC_IN_PREV_COST: This buffer descriptor provides the 16-bits previous cost inputs. Used by the sub-pixel interpolation step.

  STEREOVISION_TI_BUFDESC_IN_COST: This buffer descriptor provides the 16-bits cost inputs used by the sub-pixel interpolation step.

  STEREOVISION_TI_BUFDESC_IN_NEXT_COST: This buffer descriptor provides the 16-bits next cost inputs used by the sub-pixel interpolation step.

  STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY: This buffer descriptor provides the 8-bits auxiliary disparity map used in left-right check.
 */
typedef enum
{
    STEREOVISION_TI_BUFDESC_IN_IMAGE = 0,
    STEREOVISION_TI_BUFDESC_IN_DISPARITY,
    STEREOVISION_TI_BUFDESC_IN_PREV_COST,
    STEREOVISION_TI_BUFDESC_IN_COST,
    STEREOVISION_TI_BUFDESC_IN_NEXT_COST,
    STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY,
    STEREOVISION_TI_BUFDESC_IN_TOTAL
} STEREOVISION_TI_InBufOrder ;


/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There are 2 output buffers descriptor

            STEREOVISION_TI_BUFDESC_OUT_DISPARITY: This buffer is filled up by StereoVision postprocessing algorithm with the post-processed disparity values.

            STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE: This buffer is filled up with the 16-bits confidence values.

            STEREOVISION_TI_BUFDESC_OUT_TEXTURE: This buffer is filled up with the 8-bits texture values.
 */
typedef enum 
{
    STEREOVISION_TI_BUFDESC_OUT_DISPARITY = 0,
    STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE,
    STEREOVISION_TI_BUFDESC_OUT_TEXTURE,
    STEREOVISION_TI_BUFDESC_OUT_COST,
    STEREOVISION_TI_BUFDESC_OUT_TOTAL
} STEREOVISION_TI_OutBufOrder;


/**
    @brief  This enum type defines the method used to caculate the cost of each disparity.

            STEREOVISION_TI_SAD: Sum of absolute difference. The left and right images are assumed to contain intensity pixel values of 8 or 16-bits.

            STEREOVISION_TI_HAM_DIST: Hamming distance. The left and right frames are assumed to hold codeword values of every pixel. Generally, census transform has been previously executed to produce the codewords.

 */
typedef enum {
    STEREOVISION_TI_SAD= 0,
    STEREOVISION_TI_HAM_DIST= 1
} STEREOVISION_TI_CostMethod;

/**
    @brief  This enum type defines the direction of the disparity search

            STEREOVISION_TI_LEFT_TO_RIGHT: Disparity search is done by fixing a pixel in left image and then searching for the minimum cost pixel in the right image, along the same epipolar line.

            STEREOVISION_TI_RIGHT_TO_LEFT: Disparity search is done by fixing a pixel in right image and then searching for the minimum cost pixel in the left image, along the same epipolar line.
 */
typedef enum {
    STEREOVISION_TI_LEFT_TO_RIGHT=0,
    STEREOVISION_TI_RIGHT_TO_LEFT=1
} STEREOVISION_TI_SearchDir;

/**
    @brief  This enum type defines the mode of processing of the function

            Currently only STEREOVISION_TI_POSTPROCESS_ONLY is supported.

            STEREOVISION_TI_ALL: the entire stereovision algorithm is executed: disparity followed by post-processing
            STEREOVISION_TI_DISPARITY_ONLY: Only disparity is executed
            STEREOVISION_TI_POSTPROCESS_ONLY: Only prost-processing is exeucted


 */
typedef enum {
    STEREOVISION_TI_ALL= 0,
    STEREOVISION_TI_DISPARITY_ONLY= 1,
    STEREOVISION_TI_POSTPROCESS_ONLY=2
} STEREOVISION_TI_ProcessingMode;

/**
    @brief  This structure defines options associated to disparity processing if enabled

  @param  censusWinWidth
         census transform kernel width

  @param  censusWinHeight
         census transform kernel height

  @param  costSupportWinWidth
         Width of the support window, that defines the neighbourhood in which SAD or hamming-distance based cost calculations are performed.

  @param  costSupportWinHeight
         Height of the support window, that defines the neighbourhood in which SAD or hamming-distance based cost calculations are performed.

  @param  minDisparity
          Minimum disparity for which the cost is calculated. For each pixel, the disparity corresponding to the minimum cost is returned. The disparity range is [minDisparity, maxDisparity].

  @param  maxDisparity
          Maximum disparity for which the cost is calculated. For each pixel, the disparity corresponding to the minimum cost is returned. The disparity range is [minDisparity, maxDisparity].

  @param  disparityStep
          Disparity step allows to down-sample the number of disparities for which the cost is calculated, resulting in faster computation in detriment to precision.

  @param costMethod
          See description of enum type DISPARITY_TI_CostMethod, which defines the method employed to calculate each disparity's cost.
          Currently only DISPARITY_TI_HAM_DIST is supported.

  @param  searchDir
          See description of enum type DISPARITY_TI_SearchDir, which defines the direction(s) of the disparity search.  
          Currently only DISPARITY_TI_LEFT_TO_RIGHT is supported.


 */
typedef struct {
    uint8_t censusWinWidth;
    uint8_t censusWinHeight;
    uint8_t costSupportWinWidth;
    uint8_t costSupportWinHeight;
    int16_t minDisparity;
    int16_t maxDisparity;
    uint8_t disparityStep;
    uint8_t costMethod;
    uint8_t searchDir;
} STEREOVISION_TI_DisparityOptions;

/**
  @brief This enum type lists the different smoothing strength

 */
typedef enum {
    STEREOVISION_TI_SMOOTHING_STRENGTH_NONE= 0,
    STEREOVISION_TI_SMOOTHING_STRENGTH_LO,
    STEREOVISION_TI_SMOOTHING_STRENGTH_MED,
    STEREOVISION_TI_SMOOTHING_STRENGTH_HI
} STEREOVISION_TI_SmoothingStrength;


/**
    @brief  This structure defines options associated to post-processing if enabled

  @param  disparityNumFracBits
          Number of fractional bits added to the disparity values by the sub-pixel interpolation.

  @param  textureLumaHiThresh
          Normalized higher bound threshold 0-100 for luma. If image is 8-bits then 0 maps to 0 and 100 maps to 255.
          This value acts as a saturation bound: any pixel whose luma value is above this threshold will have its texture value set 0.
          So very dark regions automatically get assigned a 0 value texture.

  @param  textureLumaLoThresh
          Normalized lower bound threshold 0-100 for luma. If image is 8-bits then 0 maps to 0 and 100 maps to 255.
          This value acts as a saturation bound: any pixel whose luma value is below this the threshold will have its texture value set 0.
          So very bright regions automatically get assign a 0 value texture.

  @param  disparityMinThreshold
          Minimum disparity threshold, Pixels whose disparity is below this threshold are marked invalid.

  @param  disparityMaxThreshold
          Maximum disparity threshold, pixels whose disparity is greater than this threshold are marked invalid.

  @param  costMaxThreshold
          Normalized threshold value in the range [0 100]. Pixels whose disparity cost are above this threshold are marked invalid.

  @param  minConfidenceThreshold
          Normalized threshold value in the range [0 100]. Pixels whose confidence value cost is below (100 – minConfidenceThreshold) are marked invalid.
          In other word, if minConfidenceThreshold= 100, all pixels are valid and if minConfidenceThreshold= 0, all pixels are invalid.

  @param  textureThreshold
          Normalized threshold value in the range [0 100].  Pixels whose texture value is cost is below (100 – textureThreshold) are marked invalid.
          In other word, if textureThreshold = 100, all pixels are valid and if textureThreshold = 0, all pixels are invalid.

  @param  holeFillingStrength
          Normalized value in the range [0 100] expressing the aggressiveness of the hole filling algorithm.

  @param  lrMaxDiffThreshold
          The maximum disparity difference between the main disparity map and the auxiliary disparity map, which can be tolerated.
          A large value means a large tolerance. This is used for left right check. A value of 255 disables the check.

  @param  maxDispDissimilarity
          The maximum disparity difference between a pixel and its neighbor before starting a new segment.
          Pixels within a segment have their confidence values examined in order to declare the segment as valid or invalid.

  @param  minConfidentNSegment
          Number of pixels within a segment whose confidence value must exceed  minConfidenceThreshold to keep the entire segment as valid.

  @param  auxDisparityHorzDsFactor
          Horizontal downsample factor of the auxiliary disparity map.

  @param  auxDisparityVertDsFactor
          Vertical downsample factor of the auxiliary disparity map.

  @param  smoothingStrength
          Smoothing filter strength.
 */
typedef struct {
    uint8_t disparityNumFracBits;
    uint8_t textureLumaHiThresh;  /* 0 - 100 */
    uint8_t textureLumaLoThresh;  /* 0 - 100 */
    uint8_t disparityMinThreshold; /* 0 - 100 */
    uint8_t disparityMaxThreshold; /* 0 - 100 */
    uint8_t costMaxThreshold; /* 0 - 100 */
    uint8_t minConfidenceThreshold; /* 0 - 100 */
    uint8_t textureThreshold; /* 0  - 100 */
    uint8_t holeFillingStrength; /* 0 - 100 */
    uint8_t lrMaxDiffThreshold; /* Number of disparities */
    uint8_t maxDispDissimilarity; /* Number of disparities */
    uint8_t minConfidentNSegment; /* Number of pixels */
    uint8_t auxDisparityHorzDsFactor; /* 1, 2 : horizontal downsample factor of the auxiliary disparity map */
    uint8_t auxDisparityVertDsFactor; /* 1, 2 : Vertical downsample factor of the auxiliary disparity map */
    uint8_t smoothingStrength; /* STEREOVISION_TI_SMOOTHING_STRENGTH_LO STEREOVISION_TI_SMOOTHING_STRENGTH_MED STEREOVISION_TI_SMOOTHING_STRENGTH_HI */
    uint8_t enable16BitsDispOut;
} STEREOVISION_TI_PostProcOptions;

/**

  @struct STEREOVISION_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          STEREOVISION algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxImageRoiWidth
          Max input roi width of image

  @param  maxImageHeight
         Max input roi height of image

  @param  inputBitDepth
         Bit depth of the input image

  @params processingMode
          See description of enum type STEREOVISION_TI_ProcessingMode, which defines the processing mode.  
          Currently only STEREOVISION_TI_POSTPROCESS_ONLY is supported.

  @params disparityOptions
          See description of enum type STEREOVISION_TI_DisparityOptions, which defines the disparity options  
          Currently ignored as processingMode only supports STEREOVISION_TI_POSTPROCESS_ONLY

  @param edma3RmLldHandle
          Pointer to the edma3lld resource manager handle
 */

typedef struct
{
    IVISION_Params visionParams;
    uint16_t maxImageRoiWidth;
    uint16_t maxImageRoiHeight;
    uint8_t inputBitDepth;
    STEREOVISION_TI_ProcessingMode processingMode;
    STEREOVISION_TI_DisparityOptions disparityOptions;
    void    * edma3RmLldHandle;
} STEREOVISION_TI_CreateParams;


/**

  @struct STEREOVISION_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to STEREOVISION algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param  postProcOptions
          Contain all the runtime parameters that control the post-processing. Can be updated at every frame.
 */
typedef struct
{
    IVISION_InArgs iVisionInArgs;
    STEREOVISION_TI_PostProcOptions postProcOptions;
} STEREOVISION_TI_InArgs;


/**

  @struct STEREOVISION_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Stereovision algorithm at frame level.
          They provide useful statistics pertaining to the disparity map.

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  maxDisparityVal
          maximum disparity value produced by the sub-pixel interpolation step

  @param  minDisparityVal
          minimum disparity value produced by the sub-pixel interpolation step

  @param  maxCostVal
          maximum cost value in the input cost map

  @param  maxCurveVal
          maximum confidence (curve) value produced by the sub-pixel interpolation step

 */
typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    int16_t maxDisparityVal;
    int16_t minDisparityVal;
    uint16_t maxCostVal;
    int16_t maxCurveVal;
    int32_t rsvd1;
} STEREOVISION_TI_OutArgs;


/*@}*/
/* ti_ivision_STEREOVISION */

#ifdef __cplusplus
}
#endif

#endif /*ISTEREOVISION_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                                                                           */
/*==========================================================================*/


