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

/*                                                                          */
/*     @file : vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn.h           */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of gradient pixels     */
/*     which includes gradient along X and Y stored in interleaved format   */
/*     for multiple blocks centered around each feature/key point           */
/*                                                                          */
/*     vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn                     */
/*         This is the c-reference for the vcop_multiblock_bilinear_interp  */
/*         _intlv_7x7_s16_cn kernel. This routine accepts multiple blocks   */
/*         of 16 bit gradient pixels centered around 'numKeyPoints' and     */
/*         the precomputed bilinear weights for each key point to compute   */
/*         the bilinear interpolation of gradient pixels wherein each       */
/*         output block is of dimension (blkWidth) x (blkHeight)            */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn                */
/*     (                                                                    */
/*        int16_t             *pIntlvGradXY,                                  */
/*        uint16_t    *pInpWts,                                       */
/*        int16_t             *pGradXBilinearInterpImg,                       */
/*        int16_t             *pGradYBilinearInterpImg,                       */
/*        uint16_t     input1Stride,                                  */
/*        uint16_t     input2Stride,                                  */
/*        uint16_t     outputStride,                                  */
/*        uint16_t     blkWidth,                                      */
/*        uint16_t     blkHeight,                                     */
/*        uint16_t     blkOffset,                                     */
/*        uint16_t     shiftValue,                                    */
/*        uint16_t     numKeyPoints                                   */
/*     )                                                                    */
/*                                                                          */
/*     pIntlvGradXY   : Pointer to interleaved gradient pixel data          */
/*     pInpWts        : Pointer to bilinear weights for each key point      */
/*     pGradXBilinearInterpImg : Pointer to bilinear interpolated GradX     */
/*     pGradYBilinearInterpImg : Pointer to bilinear interpolated GradY     */
/*     input1Stride   : Stride of the input buffer, pIntlvGradXY            */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffers, GradX & GradY         */
/*     blkWidth       : Width of the output block around each key point     */
/*                      in pixels for which bilinear interpolation is       */
/*                      computed                                            */
/*     blkHeight      : Height of the output block around each key point    */
/*                      in pixels for which bilinear interpolation is       */
/*                      computed                                            */
/*     blkOffset      : Offset to the start of next block from current block*/
/*                      in pixels                                           */
/*     numKeyPoints   : Number of key points                                */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_CN
#define VCOP_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_CN  1
/*!

  @fn     vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn

  @brief  This function is a C reference that is used for computing bilinear
          interpolation of gradient pixels which includes gradient along X and
          Y stored in interleaved format for multiple blocks centered around
          each feature/key point

  @param  pIntlvGradXY            : Pointer to interleaved gradient pixel data
  @param  pInpWts                 : Pointer to bilinear weights for each key point
  @param  pGradXBilinearInterpImg : Pointer to bilinear interpolated GradX
  @param  pGradYBilinearInterpImg : Pointer to bilinear interpolated GradY
  @param  input1Stride            : Stride of the input buffer, pIntlvGradXY
  @param  input2Stride            : Stride of the input buffer, pInpWts
  @param  outputStride            : Stride of the output buffers, GradX & GradY
  @param  blkWidth                : Width of the output block around each key point
                                    in pixels for which bilinear interpolation is computed
  @param  blkHeight               : Height of the output block around each key point
                                    in pixels for which bilinear interpolation is computed
  @param  blkOffset               : Offset to the start of next block from current block in pixels
  @param  numKeyPoints            : Number of key points

*/
void vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn
(
    int16_t            *pIntlvGradXY,            /* Pointer to interleaved gradient pixel data             */
    uint16_t     *pInpWts,                 /* Pointer to bilinear weights for each key point         */
    int16_t            *pGradXBilinearInterpImg, /* Pointer to bilinear interpolated GradX                 */
    int16_t            *pGradYBilinearInterpImg, /* Pointer to bilinear interpolated GradY                 */
    uint16_t     input1Stride,            /* Stride of the input buffer, pIntlvGradXY               */
    uint16_t     input2Stride,            /* Stride of the input buffer, pInpWts                    */
    uint16_t     outputStride,            /* Stride of the output buffers, GradX & GradY            */
    uint16_t     blkWidth,                /* Width of the output block around each key point        */
                                                /* in pixels for which bilinear interpolation is computed */
    uint16_t     blkHeight,               /* Height of the output block around each key point       */
                                                /* in pixels for which bilinear interpolation is computed */
    uint16_t     blkOffset,               /* Offset to the start of next block from current block   */
                                                /* in pixels                                              */
    uint16_t     shiftValue,              /* Number of bits for trucnation                       */
    uint16_t     numKeyPoints             /* Number of key points                                   */
);

#endif /* VCOP_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_CN */
