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
 *  @file       ifilter_2d_ti.h
 *
 *  @brief      This file defines ivision interface for 2D filter
 *
 *  @version 1.0 (Jan 2014) : Base version.
 */

/** @ingroup    ti_ivision_filter_2d*/
/*@{*/
#ifndef IFILTER_2D_TI_H
#define IFILTER_2D_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the FILTER_2D.
 */
extern const IVISION_Fxns FILTER_2D_TI_VISION_FXNS;

/**
* @brief IRES interface of the FILTER_2D app
*/
extern const IRES_Fxns FILTER_2D_TI_IRES;



typedef enum
{
  FILTER_2D_TI_ERRORTYPE_IMAGEFORMAT_UNSUPPORTED = IALG_CUSTOMFAILBASE,
  FILTER_2D_TI_ERRORTYPE_IMAGEFORMAT_MISMATCH,
  FILTER_2D_TI_ERRORTYPE_MAX_ERROR_CODE
} NMS_TI_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  FILTER_2D_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by algorithm. This buffer is expected to be
  in NV12 format with plane 0 as Luma and plane 1 as Chroma component.

  Restrictions : It is important that width is a multiple of 16 for this applet

  FILTER_2D_TI_BUFDESC_IN_TOTAL : This indicates total number of input
  buffers expected

*/
typedef enum
{
  FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  FILTER_2D_TI_BUFDESC_IN_TOTAL
} FILTER_2D_TI_InBufOrder ;


/**
  @brief These are the image format supported by this applet

  FILTER_2D_TI_IMAGE_FORMAT_GRAYSCALE: For a gray scale image

  FILTER_2D_TI_IMAGE_FORMAT_YUV420: YUV420 format image

  FILTER_2D_TI_BUFDESC_IN_TOTAL : This indicates total number of input
  buffers expected

*/
typedef enum
{
  FILTER_2D_TI_IMAGE_FORMAT_GRAYSCALE = 0,
  FILTER_2D_TI_IMAGE_FORMAT_YUV420,
  FILTER_2D_TI_IMAGE_FORMAT_TOTAL
} FILTER_2D_TI_ImageFormat;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  FILTER_2D_BUFDESC_OUT_IMAGE_BUFFER:
  This buffer will return filtered image in NV12 format with plane 0 as Luma and
  plane 1 as Chroma component.
*/

typedef enum
{
  FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER = 0,
  FILTER_2D_TI_BUFDESC_OUT_TOTAL
} FILTER_2D_TI_OutBufOrder ;

/**
  @brief Control command can be used to get/set some of the parameters for this
            applet. Below enums define the control commands supported for this applet

  FILTER_2D_CONTROL_GET_EFFECTIVE_OUTPUT_DIM:
    This control command can be used to get the effective dimension for both filter
    and histogram used inside this applet. User should provide input buffer as inParams
    and FILTER_2D_EffectiveDims as outParams while using this control command using control
    command API. This control command should be called to know the memory required for output buffer
    and region of image used for getting histogram.
*/

typedef enum
{
  FILTER_2D_CONTROL_GET_EFFECTIVE_OUTPUT_DIM,
  FILTER_2D_CONTROL_MAX
} IFILTER_2D_ControlCommand ;

/**

  @struct FILTER_2D_CreateParams
  @brief  This structure contains Parameters which tells user
            the actual region of image used by filter and histogram

  @param  effImageWidth
          Effective image width output by the filter. THis can be greater
          than input image dimension to satisfy internal constraints. User is
          expected to allocate the output/input buffers accordingly. Input buffer
          should contain extra border as compared to effImageWidth

  @param  effImageHeight
           Effective image height output by the filter. THis can be greater
          than input image dimension to satisfy internal constraints. User is
          expected to allocate the output/input buffers accordingly. Input buffer
          should contain extra border as compared to effImageHeight


  @param  activeHistImgWidth
          This is the actual image width used for histogram update

  @param  activeHistImgHeight
          This is the actual image height used for histogram update

*/
typedef struct
{
  uint16_t       effImageWidth;
  uint16_t       effImageHeight;
  uint16_t       activeHistImgWidth;
  uint16_t       activeHistImgHeight;
} FILTER_2D_EffectiveDims;

/**

  @struct FILTER_2D_CreateParams
  @brief  This structure contains all the parameters which controls
          2D filter applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param imageFormat
          Image format for the input buffers used. Refer FILTER_2D_TI_ImageFormat
          for valid valies

  @param  filterCoefWidth
          Width of the filter coefficient mask

  @param  filterCoefHeight
          Height of the filter coefficient mask

  @param  filterCoef
          Pointer Pointing to filter coefficients array of  filterCoefWidth x filterCoefHeight.
          For separable filter first filterCoefWidth elements will corrresponds to filter
          in Horizontal direction and last filterCoefHeight elements will corrresponds to filter
          in Vertical direction

  @param  separableFilter
          A value of 1 indicates filter is separable and 0 indicates its non-separable.
          Current Implementation is only for separable filter

@param  enableContrastStretching
        A value of 1 will enable contrast stretching for Y component of image.

@param  enableFilter
        A value of 1 will enable filter and 0 will disable filter operation. It is important to note that
        this will not have same performance as for the case when only contrast stretching alone done.
        The reason is that when we disable filer we still call the filter kernel with coefficients equal to 1.


@param minVal
        This parameter is only used when enableContrastStretching = 1. This is the minimum
        pixel value to be used for stretching the contrast

@param maxVal
        This parameter is only used when enableContrastStretching = 1. This is the maximum
        pixel value to be used for stretching the contrast

@param minPercentileThreshold
        This parameter is only used when enableContrastStretching = 1. This is the
        percentage to pixels used to determine the minimum value from histogram. For
        example a value of 1 means while calculating the minimum value of histogram we will
        find the minimum value which is greater than 1% of pixels

@param maxPercentileThreshold
        This parameter is only used when enableContrastStretching = 1. This is the
        percentage to pixels used to determine the maximum value from histogram. For
        example a value of 99 means while calculating the maximum value of histogram we will
        find the maximum value which is lessor than 99% of pixels

*/
typedef struct
{
  IVISION_Params visionParams;
  uint8_t        imageFormat;
  uint8_t        filterCoefWidth;
  uint8_t        filterCoefHeight;
  uint8_t        *filterCoef;
  uint8_t        separableFilter;
  uint8_t        enableContrastStretching;
  uint8_t        enableFilter;
  uint8_t       minVal;
  uint8_t       maxVal;
  uint8_t      minPercentileThreshold;
  uint8_t      maxPercentileThreshold;
} FILTER_2D_CreateParams;


/**

  @struct FILTER_2D_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to Filter at frame level
  @brief :  Minimum value of histogram above a certain percent to be applied for current frame.
              This field is only valid if enableContrastStretching is set to 1 during create time
  @brief :  Maximum value of histogram below a certain percent to be applied for current frame.
              This field is only valid if enableContrastStretching is set to 1 during create time

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules
*/
typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t         minVal;
  uint8_t         maxVal;
} FILTER_2D_InArgs;


/**

  @struct FILTER_2D_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Filter  at frame level
  @brief :  Minimum value of histogram above a certain percent for the current frame processed.
              This field is only valid if enableContrastStretching is set to 1 during create time
  @brief :  Maximum value of histogram below a certain percentfor the current frame processed.
              This field is only valid if enableContrastStretching is set to 1 during create time
  @param  iVisionOutArgs
          Common outArgs for all ivison based modules
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint8_t         minVal;
  uint8_t         maxVal;
} FILTER_2D_OutArgs;


/*@}*/
/* ti_ivision_filter_2d*/

#endif /*IFILTER_2D_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


