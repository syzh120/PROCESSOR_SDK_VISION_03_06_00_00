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
/*     @file : vcop_grayscale_morphology_c.h                                */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     functions for grayscale morphological processing with flat           */
/*     structuring elements (SE).                                           */
/*                                                                          */
/*     The following basic morphological operations are provided:           */
/*     1. vcop_grayscale_dilate_mask_cn                                     */
/*           Performs grayscale dilation of an 8-bit grayscale input image  */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     2. vcop_grayscale_erode_mask_cn                                      */
/*           Performs grayscale erosion of an 8-bit grayscale input image   */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     3. vcop_grayscale_morp_diff_cn                                       */
/*           Performs image difference operation between two 8-bit gray-    */
/*           scale images at data_ptr and data2_ptr, both of size blk_w     */
/*           by blk_h, and writes the output into output_ptr. The function  */
/*           assumes that the image pixel values at data_ptr is greater     */
/*           than the corresponding pixel values at data2_ptr.              */
/*                                                                          */
/*     @author Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/*     @version 1.0 (February 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_GRAYSCALE_MORPHOLOGY_CN
#define _VCOP_GRAYSCALE_MORPHOLOGY_CN  1
void vcop_grayscale_dilate_mask_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned char         *se_ptr,       // structuring element data pointer
    unsigned char         *output_ptr    // output data pointer
);

void vcop_grayscale_erode_mask_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned char         *se_ptr,       // structuring element data pointer
    unsigned char         *output_ptr    // output data pointer
);

void vcop_grayscale_morp_diff_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input 1 data pointer (data >= data2)
    unsigned char         *data2_ptr,    // input 2 data pointer
    unsigned char         *output_ptr    // output data pointer
);


void vcop_grayscale_open_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B);


void vcop_grayscale_close_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B);


void vcop_grayscale_tophat_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_A,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B);


void vcop_grayscale_bottomhat_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_A,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B);


void vcop_grayscale_morph_grad_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_B,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr1_C,
   unsigned char *scratch_ptr2_A,
   unsigned char *output_ptr_B);


#endif /* _VCOP_GRAYSCALE_MORPHOLOGY_CN */
