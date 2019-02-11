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
/*     @file : vcop_weight_computation_cn.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing weights corresponding to different feature/key*/
/*     point. These weights will be used during bilinear interpolation      */
/*                                                                          */
/*     vcop_weight_computation_cn                                           */
/*         This is the c-reference for the vcop_weight_computation_cn       */
/*         kernel. This routine accepts an X coordinate and Y coordinate    */
/*         lists of length 'numKeyPoints' and computes weights used for     */
/*         bilinear interpolation of image or gradient pixels               */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_weight_computation_cn                                      */
/*     (                                                                    */
/*        uint16_t    *pXYList,                                       */
/*        uint8_t     *pOutWts,                                       */
/*        uint16_t     numKeyPoints,                                  */
/*        uint16_t     qFormatMaxFactor                               */
/*        uint16_t     outputStride                                   */
/*     )                                                                    */
/*                                                                          */
/*     pXYList          : Pointer to (X,Y) Coordinate list of key points    */
/*     pOutWts          : Pointer to output weights for each key point      */
/*                        Buffer Size = 4 * outputStride                    */
/*                        w0, w1, w2, w3 are four outputs for key point     */
/*     numKeyPoints     : Number of key points                              */
/*     qFormatMaxFactor : Maximum scale factor for given Q format           */
/*                        Q4 format => 4 bits for fraction,                 */
/*                        qFormatMaxFactor = (2)^4 - 1 = 15                 */
/*     outputStride     : Stride in the output buffer, should be greater    */
/*                        than or equal to 'numKeyPoints'                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_WEIGHT_COMPUTATION_CN
#define VCOP_WEIGHT_COMPUTATION_CN  1
/*!

  @fn     vcop_weight_computation_cn

  @brief  This function is a C reference that is used to compute weights for
          each key point that need to be used during bilinear interpolation of
          image or gradient pixels
  @param  pXYList          : Pointer to (X,Y) Coordinate list of key points
  @param  pOutWts          : Pointer to output weights for each key point
  @param  numKeyPoints     : Number of key points
  @param  qFormatMaxFactor : Maximum scale factor for given Q format
                             Q4 format => 4 bits for fraction,
                             qFormatMaxFactor = (2)^4 - 1 = 15
  @param  outputStride     : Stride in the output buffer

*/
void vcop_weight_computation_cn
(
    uint16_t    *pXYList,            /* Pointer to (X,Y) Coordinate list of key points   */
    uint16_t    *pOutWts,            /* Pointer to output weights for each key point     */
    uint16_t     numKeyPoints,       /* Number of key points                             */
    uint16_t     qFormatMaxFactor,   /* Maximum scale factor for given Q format          */
    uint16_t     truncateBits,
    uint16_t     outputStride        /* Stride in the output buffer                      */
);

#endif /* VCOP_WEIGHT_COMPUTATION_CN */
