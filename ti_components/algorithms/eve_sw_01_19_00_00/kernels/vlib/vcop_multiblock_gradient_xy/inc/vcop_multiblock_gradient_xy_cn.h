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
/*     @file : vcop_multiblock_gradient_xy_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing gradients of multiple blocks corresponding to */
/*     different feature/key point                                          */
/*                                                                          */
/*     vcop_multiblock_gradient_xy_cn                                       */
/*         This is the c-reference for the vcop_multiblock_gradient_xy      */
/*         kernel. This routine accepts an 8-bit input image and outputs    */
/*         16-bit gradients along X and Y directions in interleaved format  */
/*         for 'numblocks' wherein each output block is of dimension,       */
/*         4 * (blkWidth) x (blkHeight) wherein a factor of '4' bytes is    */
/*         to denote 2 bytes each for gradient along X and Y directions     */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_gradient_xy_cn                                  */
/*     (                                                                    */
/*         uint8_t     *pIn,                                          */
/*         int16_t             *pIntlvGradXY,                               */
/*         uint16_t     inputStride,                                        */
/*         uint16_t     blkWidth,                                           */
/*         uint16_t     blkHeight,                                          */
/*         uint16_t     blkOffset,                                          */
/*         uint16_t     numBlocks                                           */
/*     )                                                                    */
/*                                                                          */
/*     pInput         : Pointer to input image data                         */
/*     pIntlvGradXY   : Pointer to interleaved gradient output per block    */
/*     inputStride    : Stride in the input buffer                          */
/*     blkWidth       : Width of the block for which gradients is computed  */
/*     blkHeight      : Height of the block for which gradients is computed */
/*     blkOffset      : Offset to the start of next block from current block*/
/*     numBlocks      : Number of blocks for which gradients is computed    */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_MULTIBLOCK_GRADIENT_XY_CN
#define VCOP_MULTIBLOCK_GRADIENT_XY_CN  1
/*!

  @fn     vcop_multiblock_gradient_xy_cn

  @brief  This function is a C reference that is used to compute gradients along
          X and Y directions in interleaved format for multiple blocks
          corresponding to each feature or key point
  @param  *pIn             pointer to input image data
  @param  *pIntlvGradXY    pointer to interleaved gradient output per block
  @param  inputStride      stride in the input buffer
  @param  blkWidth         width of the block for which gradients is computed
  @param  blkHeight        height of the block for which gradients is computed
  @param  blkOffset        offset to the start of next block from current block
  @param  numBlocks        number of blocks for which gradients is computed

*/
void vcop_multiblock_gradient_xy_cn
(
    uint8_t     *pIn,                /* pointer to input image data                         */
    int16_t           *pIntlvGradXY,       /* pointer to interleaved gradient output per block    */
    uint16_t     inputStride,        /* stride in the input buffer                          */
    uint16_t     blkWidth,           /* width of the block for which gradients is computed  */
    uint16_t     blkHeight,          /* height of the block for which gradients is computed */
    uint16_t     blkOffset,          /* offset to the start of next block from current block*/
    uint16_t     numBlocks           /* number of blocks for which gradients is computed    */
);

#endif /* VCOP_MULTIBLOCK_GRADIENT_XY_CN */
