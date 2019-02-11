/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2016 - 2017 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_H_
#define VXLIB_WARPAFFINEBILINEAR_I8U_C32F_O8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_warpAffineBilinear_i8u_c32f_o8u */
/** @ingroup  VXLIB_warpAffineBilinear_i8u_c32f_o8u */
/* @{ */
/**
*  Performs affine warp transformation from input image (8-bit) to output
*  image (8-bit) using bilinear interpolation.  No border handling
*  in done in this function, so it is expected that appropriate padding
*  is done to the input buffer.
*
* @par Method:
*  The affine warp kernel is computed by using the following equation:
*
* @verbatim

   x0 = x * warpMatrix[0] + y * warpMatrix[2] + warpMatrix[4];
   y0 = x * warpMatrix[1] + y * warpMatrix[3] + warpMatrix[5];

   dst(x,y) = BilinearInterpolate(src(x0, y0))

  @endverbatim
*
*
* @par
*   @param [in]  src[]                  Pointer to array containing first input image (UQ8.0)
*   @param [in]  src_addr[]             Pointer to structure containing dimensional information of src
*   @param [out] dst[]                  Pointer to array containing output image (UQ8.0)
*   @param [in]  dst_addr[]             Pointer to structure containing dimensional information of dst
*   @param [in]  warpMatrix[]           Pointer to array containing the affine coefficients (F32)
*   @param [in]  srcOffsetX             Parameter indicating x offset of src pointer relative to start 
*                                        of valid data in broader image (SQ15.0)
*   @param [in]  srcOffsetY             Parameter indicating y offset of src pointer relative to start 
*                                        of valid data in broader image (SQ15.0)
*   @param [in]  dstOffsetX             Parameter indicating x offset of dst pointer relative to start 
*                                        of output valid data in broader image (SQ15.0)
*   @param [in]  dstOffsetY             Parameter indicating y offset of dst pointer relative to start 
*                                        of output valid data in broader image (SQ15.0)
*
* @par Assumptions:
*    - I/O buffer pointers are assumed to be not aliased.
*    - If a user wants to divide processing of the image into smaller blocks, then it can use the dstOffsetX and 
*      dstOffsetY to indicate the starting coordinate of the output block relative to the start of the full output
*      image, and srcOffsetX and srcOffsetY to indicate the starting coordinate of the input block relative to the
*      start of the full input image.
*    - Be sure to allocate padding around the border (or fetch enough pad pixels from the input
*      for interior edges when breaking into blocks), for the warp, or else the function may fetch from an out-of-bounds
*      memory location.  For each dimension, the required fetch amount depends on the warpMatrix coefficients.
*    - If padding has been applied to the start of the input image, then the src pointer should point to the start
*      of the image including the padding, and the srcOffsetX and srcOffsetY will be negative numbers (e.g. If 2
*      rows and 2 columns of padding have been added, then srcOffsetX and srcOffsetY will both be -2).
*/
VXLIB_STATUS VXLIB_warpAffineBilinear_i8u_c32f_o8u(const uint8_t src[restrict],
                                                  const VXLIB_bufParams2D_t *src_addr,
                                                  uint8_t dst[restrict],
                                                  const VXLIB_bufParams2D_t *dst_addr,
                                                  const VXLIB_F32 warpMatrix[6],
                                                  int16_t srcOffsetX,
                                                  int16_t srcOffsetY,
                                                  int16_t dstOffsetX,
                                                  int16_t dstOffsetY);

/**
* @par Description:
*  Checks the parameters for programming errors for the VXLIB_warpAffineBilinear_i8u_c32f_o8u function.
*
* @par Method:
*  The following checks are made:
*    - There shall be no NULL pointers
*    - The strides of each image shall be equal to or greater than the x dimension
*
* @par
*   @param [in]  src[]                  Pointer to array containing first input image (UQ8.0)
*   @param [in]  src_addr[]             Pointer to structure containing dimensional information of src
*   @param [out] dst[]                  Pointer to array containing output image (UQ8.0)
*   @param [in]  dst_addr[]             Pointer to structure containing dimensional information of dst
*   @param [in]  warpMatrix[]           Pointer to array containing the affine coefficients (F32)
*   @param [in]  srcOffsetX             Parameter indicating x offset of src pointer relative to start 
*                                        of valid data in broader image (SQ15.0)
*   @param [in]  srcOffsetY             Parameter indicating y offset of src pointer relative to start 
*                                        of valid data in broader image (SQ15.0)
*   @param [in]  dstOffsetX             Parameter indicating x offset of dst pointer relative to start 
*                                        of output valid data in broader image (SQ15.0)
*   @param [in]  dstOffsetY             Parameter indicating y offset of dst pointer relative to start 
*                                        of output valid data in broader image (SQ15.0)
*
*/
VXLIB_STATUS VXLIB_warpAffineBilinear_i8u_c32f_o8u_checkParams(const uint8_t src[restrict],
                                                              const VXLIB_bufParams2D_t *src_addr,
                                                              uint8_t dst[restrict],
                                                              const VXLIB_bufParams2D_t *dst_addr,
                                                              const VXLIB_F32 warpMatrix[6],
                                                              int16_t srcOffsetX,
                                                              int16_t srcOffsetY,
                                                              int16_t dstOffsetX,
                                                              int16_t dstOffsetY);
/** @} */
#endif

