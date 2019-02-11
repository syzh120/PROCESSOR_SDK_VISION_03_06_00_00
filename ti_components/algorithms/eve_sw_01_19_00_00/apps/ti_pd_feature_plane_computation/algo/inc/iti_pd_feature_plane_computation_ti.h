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
 *  @file       iti_pd_feature_plane_computation_ti.h
 *
 *  @brief      This file defines ivision interface for Feature Plane computation
 *              for TI Pedestrian Detection algorithm
 *  @version 1.0 (Jan 2014) : Base version.
 */

/** @ingroup    ti_ivision_TI_PD*/
/*@{*/
#ifndef ITI_PD_FEATURE_PLANE_COMPUTATION_TI_H
#define ITI_PD_FEATURE_PLANE_COMPUTATION_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the PD_FEATURE_PLANE_COMPUTATION.
 */
extern const IVISION_Fxns PD_FEATURE_PLANE_COMPUTATION_TI_VISION_FXNS;

/**
* @brief IRES interface of the PD_FEATURE_PLANE_COMPUTATION app
*/
extern const IRES_Fxns PD_FEATURE_PLANE_COMPUTATION_TI_IRES;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There is 1 input buffers descriptor

  PD_FEATURE_PLANE_COMPUTATION_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by algorithm. This buffer is expected to be
  in NV12 format with plane 0 as Luma and plane 1 as Chroma component.

*/
typedef enum
{
  PD_FEATURE_PLANE_COMPUTATION_BUFDESC_IN_IMAGEBUFFER = 0,
  PD_FEATURE_PLANE_COMPUTATION_BUFDESC_IN_TOTAL
} IPD_FEATURE_PLANE_COMPUTATION_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  PD_FEATURE_PLANE_COMPUTATION__BUFDESC_OUT_FEATURE_PLANEBUFFER:
  This  buffer is filled up by algorithm and will contain all the
  10 feature planes computed by algorithms.
*/

typedef enum
{
  PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_FEATURE_PLANES_BUFFER = 0,
  PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_TOTAL
} IPD_FEATURE_PLANE_COMPUTATION_OutBufOrder ;

/**
  @brief  Below enums define the Gradient Magnitude Method

  TI_PD_GRADIENT_MAGNITUDE_SAT_8BITS: Uses stauration get 8 bit magnitude
  TI_PD_GRADIENT_MAGNITUDE_9BITS: abs(x) + abs(y) 9 bit magnitude
*/
typedef enum
{
  TI_PD_GRADIENT_MAGNITUDE_SAT_8BITS,
  TI_PD_GRADIENT_MAGNITUDE_9BITS,
  TI_PD_GRADIENT_MAGNITUDE_MAX
} TI_PD_GradientMagnitudeMethod ;


/**
  @brief  Below enums define the control commands

  TI_PD_CONTROL_GET_OUTPUT_BUF_SIZE: Control command to get the output buffer size

*/typedef enum
{
  TI_PD_CONTROL_GET_OUTPUT_BUF_SIZE,
  TI_PD_CONTROL_MAX
} TI_PD_ControlCommand ;

#define FEATURE_PLANE_COMP_MAX_TOTAL_SCALES          (32)


/**

  @struct scalePrams
  @brief  This structure contains all the parameters image to be processed in a given scale

  @param  width
          image width to be processed in current scale
  @param  height
          image height to be processed in current scale
  @param  x
          Start x in the current scale
  @param  y
          Start Y in the current scale
*/typedef struct
{
  uint16_t orgWidth;
  uint16_t orgHeight;
  uint16_t width;
  uint16_t height;
  uint16_t x;
  uint16_t y;
}scalePrams_t;


/**

  @struct PD_FEATURE_PLANE_COMPUTATION_CreateParams
  @brief  This structure contains all the parameters which controls
          PD algorithm at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Max input width of image

  @param  imgFrameHeight
          Max input height of image

  @param  cellSize
          cell Size in Pixels for HOG computation

  @param  blockSize
          Block size in Pexels

  @param  blockOverlap
          Block overlap in Pexels

  @param  sreachStep
          Pedestrian model sreach step size (sliding window offset) in pixels

  @param  maxNumScales
          Maximu number of scales to be processed

  @param  numBins
          number of Gradient orientation bins

  @param  gradMagMethod
          Gradient Magnitude comaputation Method

  @param  additionalPlaneFLag
          Deatils about addition planes other than HOG planes
          bit - 0  Manitude plane |
          bit - 1  Y Plane |
          bit - 2  U and V Plane |
          bit 3-31 Unused|
  @param  outPutBufSize
          This is is ouput from control call. Gives the number bytes in the output buffer
  @param  outFormat
          0 - Planar Output, 1 - De-interleaved Output

*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t imgFrameWidth;
  uint16_t imgFrameHeight;
  uint16_t leftPadPels;
  uint16_t topPadPels;
  uint8_t  cellSize;
  uint8_t  blockSize;
  uint8_t  blockOverlap;
  uint8_t  sreachStep;
  uint8_t  maxNumScales;
  uint8_t  numBins;
  uint8_t  gradientMethod;
  uint8_t  enableCellSum;
  uint16_t scaleRatioQ12;
  uint32_t additionalPlaneFLag;
  uint32_t outPutBufSize;
  uint8_t  outFormat;
  scalePrams_t scaleParams[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];
} PD_FEATURE_PLANE_COMPUTATION_CreateParams;

/**
  @struct PD_FEATURE_PLANE_COMPUTATION_scaleMetaData

  @brief  This structure contains all the meta data containing 
  informtion about the eache scale feature  ( width height etc)

  @param  scaleOffset
          Offset from the base output pointer

  @param  imCols
          Image width in pixels

  @param  imRows
          Image height in pixels

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

} PD_FEATURE_PLANE_COMPUTATION_scaleMetaData;

/**

  @struct PD_FEATURE_PLANE_COMPUTATION_outputMetaData

  @brief  This structure contains all the meta data containing 
  informtion about the feature output (num scales, size, data layout etc)

  @param  size
          Size of this stucture to validate the version check

  @param  outBufSize
          Total output buffer size in bytes

  @param  numScales
          Total number of (pyramid levles) fearture scales in this output

  @param  numPlanes
          Number of scales in each scale

  @param  outFormat
          output layout information

  @param  scaleInfo
          Information about each scale feture plane
*/

typedef struct
{
  uint32_t          size;
  uint32_t          outBufSize;
  uint8_t           numScales;
  uint8_t           numPlanes;
  uint8_t           outFormat;
  uint16_t          leftPadPels;
  uint16_t          topPadPels;
  uint8_t           computeCellSum;
  PD_FEATURE_PLANE_COMPUTATION_scaleMetaData scaleInfo[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];
} PD_FEATURE_PLANE_COMPUTATION_outputMetaData;

/**

  @struct PD_FEATURE_PLANE_COMPUTATION_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to PD algorithm at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules
*/
typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t  numScales;
} PD_FEATURE_PLANE_COMPUTATION_InArgs;


/**

  @struct PD_FEATURE_PLANE_COMPUTATION_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by PD algorithm at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules
*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} PD_FEATURE_PLANE_COMPUTATION_OutArgs;


/*@}*/
/* ti_ivision_TI_PD */

#endif /*ITI_PD_FEATURE_PLANE_COMPUTATION_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


