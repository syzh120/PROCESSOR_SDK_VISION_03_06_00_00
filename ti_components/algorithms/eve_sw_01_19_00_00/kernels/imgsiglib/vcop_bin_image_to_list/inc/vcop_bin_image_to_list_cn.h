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
/*     @file : vcop_bin_image_to_list_cn.h                                  */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for generating (X, Y) co-ordinate list of non-zero      */
/*         pixels from an input binary image.                               */
/*                                                                          */
/*     vcop_bin_image_to_list_cn                                            */
/*         This is the C-reference for the vcop_bin_image_to_list kernel.   */
/*         This routine accepts an 8-bit binary input image and outputs a   */
/*         list of (X, Y) co-ordinates of non-zero pixel locations in the   */
/*         image. The X and Y co-ordinates are both 16-bit and are packed   */
/*         into a 32-bit number. The lower 16-bits contain Y co-ordinate    */
/*         and upper 16-bits contain the X co-oridinate. The locations are  */
/*         reported in raster scan order in the input block.                */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bin_image_to_list_cn                                       */
/*     (                                                                    */
/*         uint8_t  *img,                                                   */
/*         uint32_t *upperLeftXY,                                           */
/*         uint32_t *outXY_list,                                            */
/*         uint32_t *list_size,                                             */
/*         uint16_t  width,                                                 */
/*         uint16_t  height,                                                */
/*         uint16_t  stride                                                 */
/*     )                                                                    */
/*                                                                          */
/*     img           : 8-bit binary input image. The exact format of the    */
/*                     binary bit mask in image is as shown below:          */
/*                     Pix7  Pix6  Pix5  ... Pix0  Pix15 Pix14 ... Pix8     */
/*                     Pix23 Pix22 Pix21 ... Pix16 ...                      */
/*     upperLeftXY   : (X, Y) location of the upper left pixel in the block */
/*                     X co-ordinate is expected in the upper 16-bits and   */
/*                     the Y co-ordinate is expected in the lower 16-bits.  */
/*     outXY_list    : (X, Y) co-ordinates of locations of non-zero pixels. */
/*                     Here lower 16-bits contain Y co-ordinate and upper   */
/*                     16-bits contain the X co-oridinate.                  */
/*     list_size     : Number of (X, Y) pairs in the output list            */
/*     width         : Width of the input image                             */
/*     height        : Height of the input image                            */
/*     stride        : Stride for the input image. This should be a         */
/*                     multiple of 8.                                       */
/*     outputQformat : Output Q format, ie amount of shift to be given to the coordniates */
/*                         before storing it */
/*     xyOrder : if xyOrder ==1 , then output witll have x in msb and y in lsb */
/*                       xyOrder == 0 , then output witll have y in msb and x in lsb */
/*                                                                          */
/*     Returns       :  None or void.                                       */
/*                                                                          */
/*     @version 1.0 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_BIN_IMAGE_TO_LIST_CN
#define _VCOP_BIN_IMAGE_TO_LIST_CN

void vcop_bin_image_to_list_cn
(
    uint8_t  *img,
    uint32_t *upperLeftXY,
    uint32_t *outXY_list,
    uint32_t *list_size,
    uint16_t  width,
    uint16_t  height,
    uint16_t  stride,
    uint16_t  outputQformat,
    uint8_t   xyOrder

);

#endif /* _VCOP_BIN_IMAGE_TO_LIST_CN */
