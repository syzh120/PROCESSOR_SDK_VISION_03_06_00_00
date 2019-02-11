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
/*     @file : vcop_multiblock_bilinear_interp_7x7_u8_cn.h                  */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of image pixels for    */
/*     multiple blocks centered around each feature/key point               */
/*                                                                          */
/*     vcop_multiblock_bilinear_interp_7x7_u8_cn                            */
/*         This is the c-reference for the vcop_multiblock_bilinear_interp  */
/*         _u8_cn kernel. This routine accepts multiple blocks of 8-bit     */
/*         image pixels centered around 'numKeyPoints' and the precomputed  */
/*         bilinear weights for each key point to compute the bilinear      */
/*         interpolation of image pixels wherein each output block is of    */
/*         dimension (blkWidth) x (blkHeight). pIn denotes the first pixel  */
/*         location in the first block from where bilinear interpolation is */
/*         computed for output block size and "blkOffset" denotes the offset*/
/*         to the first pixel of the next block for which bilinear          */
/*         interpolation is computed                                        */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_bilinear_interp_7x7_u8_cn                       */
/*     (                                                                    */
/*        uint8_t     *pIn,                                           */
/*        uint8_t     *pInpWts,                                       */
/*        uint8_t     *pOutBilinearInterpImg,                         */
/*        uint16_t     input1Stride,                                  */
/*        uint16_t     input2Stride,                                  */
/*        uint16_t     outputStride,                                  */
/*        uint16_t     blkWidth,                                      */
/*        uint16_t     blkHeight,                                     */
/*        uint16_t     blkOffset,                                     */
/*        uint16_t     numKeyPoints                                   */
/*     )                                                                    */
/*                                                                          */
/*     pInput         : Pointer to input image data                         */
/*     pInpWts        : Pointer to bilinear weights for each key point      */
/*     pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel */
/*     input1Stride   : Stride of the input buffer, pIn                     */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffer, pOutBilinearInterpImg  */
/*     blkWidth       : Width of the input block around each key point      */
/*     blkHeight      : Height of the input block around each key point     */
/*     blkOffset      : Offset to the start of next block from current block*/
/*     numKeyPoints   : Number of key points                                */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN
#define VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN  1
/*!

  @fn     vcop_multiblock_bilinear_interp_7x7_u8_cn

  @brief  This function is a C reference that is used for computing bilinear
          interpolation of image pixels for multiple blocks centered around
          each feature/key point

  @param  pInput                : Pointer to input image data
  @param  pInpWts               : Pointer to bilinear weights for each key point
  @param  pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel
  @param  input1Stride          : Stride of the input buffer, pIn
  @param  input2Stride          : Stride of the input buffer, pInpWts
  @param  outputStride          : Stride of the output buffer, pOutBilinearInterpImg
  @param  blkWidth              : Width of the input block around each key point
  @param  blkHeight             : Height of the input block around each key point
  @param  blkOffset             : Offset to the start of next block from current block
  @param  shiftValue            : Number of bits for trucnation
  @param  numKeyPoints          : Number of key points

*/
void vcop_multiblock_bilinear_interp_7x7_u8_cn
(
    uint8_t     *pIn,                     /* Pointer to input image data                         */
    uint16_t    *pInpWts,                 /* Pointer to bilinear weights for each key point      */
    uint8_t     *pOutBilinearInterpImg,   /* Pointer to bilinear interpolated image pixel        */
    uint16_t     input1Stride,            /* Stride of the input buffer, pIn                     */
    uint16_t     input2Stride,            /* Stride of the input buffer, pInpWts                 */
    uint16_t     outputStride,            /* Stride of the output buffer, pOutBilinearInterpImg  */
    uint16_t     blkWidth,                /* Width of the input block around each key point      */
    uint16_t     blkHeight,               /* Height of the input block around each key point     */
    uint16_t     blkOffset,               /* Offset to the start of next block from current block*/
    uint16_t     shiftValue,              /* Number of bits for trucnation                       */
    uint16_t     numKeyPoints             /* Number of key points                                */
);

#endif /* VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN */
