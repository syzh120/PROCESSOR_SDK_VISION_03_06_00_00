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
/*     @file : vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn.h          */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of image pixels for    */
/*     multiple blocks centered around each feature/key point               */
/*                                                                          */
/*     vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn                    */
/*         This is the c-reference for the vcop_foreach_multiblock_bilinear */
/*         _interp_7x7_u8_cn kernel. This routine accepts multiple blocks   */
/*         of 8-bit image pixels centered around 'numKeyPoints', precomputed*/
/*         bilinear weights for each key point and the updated base address */
/*         corresponding to the start pixel of the output block for which   */
/*         bilinear interpolation has to be performed. It should be noted   */
/*         that the output block lies within the input block wherein the    */
/*         output block is of dimension outBlkWidth x outBlkHeight.         */
/*         Each input block has a stride of input1Stride.                   */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn               */
/*     (                                                                    */
/*        unsigned char     *pIn[],                                         */
/*        unsigned char     *pInpWts,                                       */
/*        unsigned char     *pOutBilinearInterpImg,                         */
/*        unsigned short     input1Stride,                                  */
/*        unsigned short     input2Stride,                                  */
/*        unsigned short     outputStride,                                  */
/*        unsigned short     outBlkWidth,                                   */
/*        unsigned short     outBlkHeight,                                  */
/*        unsigned short     shiftValue,                                    */
/*        unsigned short     numKeyPoints                                   */
/*     )                                                                    */
/*                                                                          */
/*     pIn            : List of Pointers to input image data,               */
/*                      output from "vcop_weight_address_bilinear_          */
/*                      interpolation_cn"                                   */
/*     pInpWts        : Pointer to bilinear weights for each key point,     */
/*                      output from "vcop_weight_address_bilinear_          */
/*                      interpolation_cn"                                   */
/*     pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel */
/*     input1Stride   : Stride of the input buffer, pIn                     */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffer, pOutBilinearInterpImg  */
/*     outBlkWidth    : Width of the output block around each key point     */
/*     outBlkHeight   : Height of the output block around each key point    */
/*     numKeyPoints   : Number of key points                                */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN
#define _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN  1
/*!

  @fn     vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn

  @brief  This function is a C reference that is used for computing bilinear
          interpolation of image pixels for multiple blocks centered around
          each feature/key point. It should be noted that each key point need
          not be in the center of the input block of dimensions

  @param  pIn[]                 : List of Pointers to input image data,          
                                  output from "vcop_weight_address_bilinear_     
                                  interpolation_cn"                              
  @param  pInpWts               : Pointer to bilinear weights for each key point,
                                  output from "vcop_weight_address_bilinear_     
                                  interpolation_cn"                              
  @param  pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel
  @param  input1Stride          : Stride of the input buffer, pIn                   
  @param  input2Stride          : Stride of the input buffer, pInpWts               
  @param  outputStride          : Stride of the output buffer, pOutBilinearInterpImg
  @param  outBlkWidth           : Width of the output block around each key point   
  @param  outBlkHeight          : Height of the output block around each key point  
  @param  numKeyPoints          : Number of key points                              

*/
void vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn
(
    unsigned char     *pIn[],                   /* List of Pointers to input image data,               */
                                                /* output from "vcop_weight_address_bilinear_          */
                                                /* interpolation_cn"                                   */
    unsigned short    *pInpWts,                 /* Pointer to bilinear weights for each key point,     */
                                                /* output from "vcop_weight_address_bilinear_          */
                                                /* interpolation_cn"                                   */
    unsigned char     *pOutBilinearInterpImg[],   /* Pointer to bilinear interpolated image pixel        */
    unsigned short     input1Stride,            /* Stride of the input buffer, pIn                     */
    unsigned short     input2Stride,            /* Stride of the input buffer, pInpWts                 */
    unsigned short     outputStride,            /* Stride of the output buffer, pOutBilinearInterpImg  */
    unsigned short     outBlkWidth,             /* Width of the output block around each key point     */
    unsigned short     outBlkHeight,            /* Height of the output block around each key point    */
    unsigned short     shiftValue,              /* Shift Value for trucncation                         */
    unsigned short     numKeyPoints             /* Number of key points                                */
);

#endif /* _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN */
