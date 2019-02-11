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
/*     @file : vcop_grayscale_morphology.h                                  */
/*                                                                          */
/*     @brief : This file contains declarations for the wrapper functions   */
/*     for the following grayscale morphological processing with flat       */
/*     structuring elements (SE): opening, closing, top hat, bottom hat     */
/*     and morphological gradient. The wrappers implement the connection    */
/*     of vcop_grayscale_dilate, vcop_grayscale_erode and                   */
/*     vcop_grayscale_morp_diff kernels to achieve the different            */
/*     operations.                                                          */
/*                                                                          */
/*     Wrappers for the following morphological operations are provided:    */
/*     1. vcop_grayscale_open_xxx                                           */
/*           Performs grayscale opening of an 8-bit grayscale input image   */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     2. vcop_grayscale_close_xxx                                          */
/*           Performs grayscale closing of an 8-bit grayscale input image   */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     3. vcop_grayscale_tophat_xxx                                         */
/*           Performs grayscale top hat of an 8-bit grayscale input image   */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     4. vcop_grayscale_bottomhat_xxx                                      */
/*           Performs grayscale bottom hat of an 8-bit grayscale image      */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     5. vcop_grayscale_morph_grad_xxx                                     */
/*           Performs grayscale morphological gradient of an 8-bit          */
/*           grayscale input image at data_ptr, of size blk_w by blk_h,     */
/*           with a flat structuring element of size se_w by se_h,          */
/*           specified with a mask of 1's and 0's at se_ptr. The output     */
/*           is written into output_ptr.                                    */
/*                                                                          */
/*     @author Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/*     @version 1.0 (February 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_GRAYSCALE_MORPHOLOGY
#define VCOP_GRAYSCALE_MORPHOLOGY  1

#include <vcop.h>


typedef struct
{
    uint16_t* pblock_dilate;
    uint16_t* pblock_erode;
} stblock_open_close_t;

typedef struct
{
    uint16_t* pblock_dilate;
    uint16_t* pblock_erode;
    uint16_t* pblock_img_diff;
} stblock_morph_t;

/* VCOP VLOOP Execution Functions */
#if (!VCOP_HOST_EMULATION)

/* Grayscale Mask Open */
void vcop_grayscale_open_mask_vloops(uint16_t *pblock);

/* Grayscale Mask Close */
void vcop_grayscale_close_mask_vloops(uint16_t *pblock);

/* Grayscale Mask Tophat Operation */
void vcop_grayscale_tophat_mask_vloops(uint16_t *pblock);

/* Grayscale Mask Bottom hat Operation */
void vcop_grayscale_bottomhat_mask_vloops(uint16_t *pblock);

/* Grayscale Mask Morphological Gradient */
void vcop_grayscale_morph_grad_mask_vloops(uint16_t *pblock);

/* Grayscale Rect Open */
void vcop_grayscale_open_rect_vloops(uint16_t *pblock);

/* Grayscale Rect Close */
void vcop_grayscale_close_rect_vloops(uint16_t *pblock);

/* Grayscale Rect Tophat Operation */
void vcop_grayscale_tophat_rect_vloops(uint16_t *pblock);

/* Grayscale Rect Bottom hat Operation */
void vcop_grayscale_bottomhat_rect_vloops(uint16_t *pblock);

/* Grayscale Rect Morphological Gradient */
void vcop_grayscale_morph_grad_rect_vloops(uint16_t *pblock);

/* Grayscale Cross Open */
void vcop_grayscale_open_cross_vloops(uint16_t *pblock);

/* Grayscale Cross Close */
void vcop_grayscale_close_cross_vloops(uint16_t *pblock);

/* Grayscale Cross Tophat Operation */
void vcop_grayscale_tophat_cross_vloops(uint16_t *pblock);

/* Grayscale Cross Bottom hat Operation */
void vcop_grayscale_bottomhat_cross_vloops(uint16_t *pblock);

/* Grayscale Cross Morphological Gradient */
void vcop_grayscale_morph_grad_cross_vloops(uint16_t *pblock);


/* Parameter Block Initialization Function */

/* Grayscale Mask Open */
uint32_t vcop_grayscale_open_mask_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_open);

/* Grayscale Mask Close */
uint32_t vcop_grayscale_close_mask_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_close);

/* Grayscale Mask Tophat Operation */
uint32_t vcop_grayscale_tophat_mask_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_A,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_tophat);

/* Grayscale Mask Bottom hat Operation */
uint32_t vcop_grayscale_bottomhat_mask_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_A,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_bottomhat);

/* Grayscale Mask Morphological Gradient */
uint32_t vcop_grayscale_morph_grad_mask_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_B,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_morph_grad);

/* Grayscale Rect Open */
uint32_t vcop_grayscale_open_rect_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_open);

/* Grayscale Rect Close */
uint32_t vcop_grayscale_close_rect_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_close);

/* Grayscale Rect Tophat Operation */
uint32_t vcop_grayscale_tophat_rect_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_tophat);

/* Grayscale Rect Bottom hat Operation */
uint32_t vcop_grayscale_bottomhat_rect_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_bottomhat);

/* Grayscale Rect Morphological Gradient */
uint32_t vcop_grayscale_morph_grad_rect_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_morph_grad);

/* Grayscale Cross Open */
uint32_t vcop_grayscale_open_cross_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_open);

/* Grayscale Cross Close */
uint32_t vcop_grayscale_close_cross_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_open_close_t *pblock_close);

/* Grayscale Cross Tophat Operation */
uint32_t vcop_grayscale_tophat_cross_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_tophat);

/* Grayscale Cross Bottom hat Operation */
uint32_t vcop_grayscale_bottomhat_cross_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_bottomhat);

/* Grayscale Cross Morphological Gradient */
uint32_t vcop_grayscale_morph_grad_cross_init(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B,
   stblock_morph_t *pblock_morph_grad);

#else

/* Grayscale Mask Open */
void vcop_grayscale_open_mask(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B);

/* Grayscale Mask Close */
void vcop_grayscale_close_mask(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B);

/* Grayscale Mask Tophat Operation */
void vcop_grayscale_tophat_mask(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_C,
   __vptr_uint8 refl_se_ptr_A,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B);

/* Grayscale Mask Bottom hat Operation */
void vcop_grayscale_bottomhat_mask(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_A,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 output_ptr_B);

/* Grayscale Mask Morphological Gradient */
void vcop_grayscale_morph_grad_mask(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 se_ptr_B,
   __vptr_uint8 refl_se_ptr_C,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Rect Open */
void vcop_grayscale_open_rect(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Rect Close */
void vcop_grayscale_close_rect(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Rect Tophat Operation */
void vcop_grayscale_tophat_rect(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Rect Bottom hat Operation */
void vcop_grayscale_bottomhat_rect(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Rect Morphological Gradient */
void vcop_grayscale_morph_grad_rect(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Cross Open */
void vcop_grayscale_open_cross(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Cross Close */
void vcop_grayscale_close_cross(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Cross Tophat Operation */
void vcop_grayscale_tophat_cross(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Cross Bottom hat Operation */
void vcop_grayscale_bottomhat_cross(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr_C,
   __vptr_uint8 scratch_ptr_A,
   __vptr_uint8 output_ptr_B);

/* Grayscale Cross Morphological Gradient */
void vcop_grayscale_morph_grad_cross(
   uint16_t blk_w,
   uint16_t line_ofst,
   uint16_t blk_h,
   __vptr_uint8 data_ptr_A,
   uint16_t se_w,
   uint16_t se_h,
   __vptr_uint8 scratch_ptr1_C,
   __vptr_uint8 scratch_ptr2_A,
   __vptr_uint8 output_ptr_B);


#endif
#endif /* VCOP_GRAYSCALE_MORPHOLOGY */
