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
/*     @file : vcop_grayscale_morphology.c                                  */
/*                                                                          */
/*     @brief : This file contains the wrapper functions for the following  */
/*     grayscale morphological processing with flat structuring elements    */
/*     (SE) : opening, closing, top hat, bottom hat and morphological       */
/*     gradient. The wrappers implement various connections of              */
/*     vcop_grayscale_dilate, vcop_grayscale_erode and                      */
/*     vcop_grayscale_morp_diff kernels to achieve the different            */
/*     morphological operations.                                            */
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

#include <stdint.h>

#include "vcop.h"

#if (!VCOP_HOST_EMULATION)
#include "vcop_grayscale_morphology_kernel.h"
#else
#include "vcop_grayscale_morphology_kernel.k"
#endif

#include "vcop_grayscale_morphology.h"

/* Parameter Block Initialization Functions */
#if (!VCOP_HOST_EMULATION)

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
   stblock_open_close_t *pblock_open)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_mask_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C, scratch_ptr_C,
        pblock_open->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_mask_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, refl_se_ptr_C, output_ptr_B,
        pblock_open->pblock_dilate);

    return nparam_blocks;

}

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
   stblock_open_close_t *pblock_close)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_mask_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C, scratch_ptr_C,
        pblock_close->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_mask_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, se_ptr_C,
        output_ptr_B, pblock_close->pblock_erode);

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_tophat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_mask_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C,
        output_ptr_B, pblock_tophat->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_mask_init(blk_w-(se_w-1U), line_ofst, blk_h-(se_h-1U),
        output_ptr_B, se_w, se_h, refl_se_ptr_A, scratch_ptr_C,
        pblock_tophat->pblock_dilate);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)), line_ofst, blk_h-((uint16_t)2*(se_h-1U)),
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)), scratch_ptr_C, output_ptr_B,
        pblock_tophat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_bottomhat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_mask_init(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h,refl_se_ptr_C, output_ptr_B,
        pblock_bottomhat->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_mask_init(blk_w-(se_w-1U),
        line_ofst, blk_h-(se_h-1U), output_ptr_B, se_w, se_h, se_ptr_A,
        scratch_ptr_C, pblock_bottomhat->pblock_erode);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)),
        line_ofst, blk_h-((uint16_t)2*(se_h-1U)), scratch_ptr_C,
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)),
        output_ptr_B, pblock_bottomhat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_morph_grad)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_mask_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C,
        scratch_ptr1_C, pblock_morph_grad->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_mask_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_B,
        scratch_ptr2_A, pblock_morph_grad->pblock_erode);

    nparam_blocks += vcop_grayscale_morp_diff_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B,
        pblock_morph_grad->pblock_img_diff);

    return nparam_blocks;
}


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
   stblock_open_close_t *pblock_open)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_rect_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr_C,
        pblock_open->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_rect_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, scratch_ptr_A, output_ptr_B,
        pblock_open->pblock_dilate);

    return nparam_blocks;

}

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
   stblock_open_close_t *pblock_close)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_rect_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr_C,
        pblock_close->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_rect_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, scratch_ptr_A,
        output_ptr_B, pblock_close->pblock_erode);

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_tophat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_rect_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, scratch_ptr_C,
        output_ptr_B, pblock_tophat->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_rect_init(blk_w-(se_w-1U), line_ofst, blk_h-(se_h-1U),
        output_ptr_B, se_w, se_h, scratch_ptr_A, scratch_ptr_C,
        pblock_tophat->pblock_dilate);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)), line_ofst, blk_h-((uint16_t)2*(se_h-1U)),
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)), scratch_ptr_C, output_ptr_B,
        pblock_tophat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_bottomhat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_rect_init(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h, scratch_ptr_C, output_ptr_B,
        pblock_bottomhat->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_rect_init(blk_w-(se_w-1U),
        line_ofst, blk_h-(se_h-1U), output_ptr_B, se_w, se_h, scratch_ptr_A,
        scratch_ptr_C, pblock_bottomhat->pblock_erode);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)),
        line_ofst, blk_h- ((uint16_t)2*(se_h-1U)), scratch_ptr_C,
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)),
        output_ptr_B, pblock_bottomhat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_morph_grad)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_rect_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B,
        scratch_ptr1_C, pblock_morph_grad->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_rect_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B,
        scratch_ptr2_A, pblock_morph_grad->pblock_erode);

    nparam_blocks += vcop_grayscale_morp_diff_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B,
        pblock_morph_grad->pblock_img_diff);

    return nparam_blocks;
}


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
   stblock_open_close_t *pblock_open)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_cross_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, output_ptr_B, scratch_ptr_C,
        pblock_open->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_cross_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_A, output_ptr_B,
        pblock_open->pblock_dilate);

    return nparam_blocks;

}

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
   stblock_open_close_t *pblock_close)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_cross_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, output_ptr_B, scratch_ptr_C,
        pblock_close->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_cross_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr_C, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_A,
        output_ptr_B, pblock_close->pblock_erode);

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_tophat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_erode_cross_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_C,
        output_ptr_B, pblock_tophat->pblock_erode);

    nparam_blocks += vcop_grayscale_dilate_cross_init(blk_w-(se_w-1U), line_ofst, blk_h-(se_h-1U),
        output_ptr_B, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_A, scratch_ptr_C,
        pblock_tophat->pblock_dilate);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)), line_ofst, blk_h-((uint16_t)2*(se_h-1U)),
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)), scratch_ptr_C, output_ptr_B,
        pblock_tophat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_bottomhat)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_cross_init(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_C, output_ptr_B,
        pblock_bottomhat->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_cross_init(blk_w-(se_w-1U),
        line_ofst, blk_h-(se_h-1U), output_ptr_B, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, scratch_ptr_A,
        scratch_ptr_C, pblock_bottomhat->pblock_erode);

    nparam_blocks += (vcop_grayscale_morp_diff_init(blk_w-((uint16_t)2*(se_w-1U)),
        line_ofst, blk_h-((uint16_t)2*(se_h-1U)), scratch_ptr_C,
        (__vptr_uint8 )(*((uint8_t (*)[])(void *)data_ptr_A) + ((se_w-1U)*line_ofst) + (se_w-1U)),
        output_ptr_B, pblock_bottomhat->pblock_img_diff));

    return nparam_blocks;
}

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
   stblock_morph_t *pblock_morph_grad)
{
    uint32_t nparam_blocks;

    nparam_blocks = vcop_grayscale_dilate_cross_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, output_ptr_B,
        scratch_ptr1_C, pblock_morph_grad->pblock_dilate);

    nparam_blocks += vcop_grayscale_erode_cross_init(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1U)/2U, (se_w-1U)/2U, output_ptr_B,
        scratch_ptr2_A, pblock_morph_grad->pblock_erode);

    nparam_blocks += vcop_grayscale_morp_diff_init(blk_w-(se_w-1U), line_ofst,
        blk_h-(se_h-1U), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B,
        pblock_morph_grad->pblock_img_diff);

    return nparam_blocks;
}


void vcop_grayscale_open_mask_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_erode_mask_vloops(pblock_open->pblock_erode);
    vcop_grayscale_dilate_mask_vloops(pblock_open->pblock_dilate);
}

void vcop_grayscale_close_mask_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_dilate_mask_vloops(pblock_close->pblock_dilate);
    vcop_grayscale_erode_mask_vloops(pblock_close->pblock_erode);
}

/* Grayscale Mask Tophat Operation */
void vcop_grayscale_tophat_mask_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_erode_mask_vloops(pblock_tophat->pblock_erode);
    vcop_grayscale_dilate_mask_vloops(pblock_tophat->pblock_dilate);
    vcop_grayscale_morp_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Grayscale Mask Bottom hat Operation */
void vcop_grayscale_bottomhat_mask_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_mask_vloops(pblock_bottomhat->pblock_dilate);
    vcop_grayscale_erode_mask_vloops(pblock_bottomhat->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Grayscale Mask Morphological Gradient */
void vcop_grayscale_morph_grad_mask_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_mask_vloops(pblock_morph_grad->pblock_dilate);
    vcop_grayscale_erode_mask_vloops(pblock_morph_grad->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_morph_grad->pblock_img_diff);
}

/* Grayscale Rect Open */
void vcop_grayscale_open_rect_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_erode_rect_vloops(pblock_open->pblock_erode);
    vcop_grayscale_dilate_rect_vloops(pblock_open->pblock_dilate);
}

/* Grayscale Rect Close */
void vcop_grayscale_close_rect_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_dilate_rect_vloops(pblock_close->pblock_dilate);
    vcop_grayscale_erode_rect_vloops(pblock_close->pblock_erode);
}

/* Grayscale Rect Tophat Operation */
void vcop_grayscale_tophat_rect_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_erode_rect_vloops(pblock_tophat->pblock_erode);
    vcop_grayscale_dilate_rect_vloops(pblock_tophat->pblock_dilate);
    vcop_grayscale_morp_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Grayscale Rect Bottom hat Operation */
void vcop_grayscale_bottomhat_rect_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_rect_vloops(pblock_bottomhat->pblock_dilate);
    vcop_grayscale_erode_rect_vloops(pblock_bottomhat->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Grayscale Rect Morphological Gradient */
void vcop_grayscale_morph_grad_rect_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_rect_vloops(pblock_morph_grad->pblock_dilate);
    vcop_grayscale_erode_rect_vloops(pblock_morph_grad->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_morph_grad->pblock_img_diff);
}

/* Grayscale Cross Open */
void vcop_grayscale_open_cross_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_erode_cross_vloops(pblock_open->pblock_erode);
    vcop_grayscale_dilate_cross_vloops(pblock_open->pblock_dilate);
}

/* Grayscale Cross Close */
void vcop_grayscale_close_cross_vloops(uint16_t *pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_grayscale_dilate_cross_vloops(pblock_close->pblock_dilate);
    vcop_grayscale_erode_cross_vloops(pblock_close->pblock_erode);
}

/* Grayscale Cross Tophat Operation */
void vcop_grayscale_tophat_cross_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_erode_cross_vloops(pblock_tophat->pblock_erode);
    vcop_grayscale_dilate_cross_vloops(pblock_tophat->pblock_dilate);
    vcop_grayscale_morp_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Grayscale Cross Bottom hat Operation */
void vcop_grayscale_bottomhat_cross_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_cross_vloops(pblock_bottomhat->pblock_dilate);
    vcop_grayscale_erode_cross_vloops(pblock_bottomhat->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Grayscale Cross Morphological Gradient */
void vcop_grayscale_morph_grad_cross_vloops(uint16_t *pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_grayscale_dilate_cross_vloops(pblock_morph_grad->pblock_dilate);
    vcop_grayscale_erode_cross_vloops(pblock_morph_grad->pblock_erode);
    vcop_grayscale_morp_diff_vloops(pblock_morph_grad->pblock_img_diff);
}


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
   __vptr_uint8 output_ptr_B)
{
    vcop_grayscale_erode_mask(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C, scratch_ptr_C);

    vcop_grayscale_dilate_mask(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, refl_se_ptr_C, output_ptr_B);

}

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
   __vptr_uint8 output_ptr_B)
{
    vcop_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C, scratch_ptr_C);

    vcop_grayscale_erode_mask(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, se_ptr_C, output_ptr_B);

}

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
   __vptr_uint8 output_ptr_B)
{

    vcop_grayscale_erode_mask(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C, output_ptr_B);

    vcop_grayscale_dilate_mask(blk_w-(se_w-1), line_ofst, blk_h-(se_h-1),
        output_ptr_B, se_w, se_h, refl_se_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1), line_ofst, blk_h-2*(se_h-1),
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), scratch_ptr_C, output_ptr_B);

}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_mask(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h,refl_se_ptr_C, output_ptr_B);

    vcop_grayscale_erode_mask(blk_w-(se_w-1),
        line_ofst, blk_h-(se_h-1), output_ptr_B, se_w, se_h, se_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1),
        line_ofst, blk_h-2*(se_h-1), scratch_ptr_C,
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C,scratch_ptr1_C);

    vcop_grayscale_erode_mask(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_B, scratch_ptr2_A);

    vcop_grayscale_morp_diff(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B);


}


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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_erode_rect(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr_C);

    vcop_grayscale_dilate_rect(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, scratch_ptr_A, output_ptr_B);



}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_rect(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr_C);

    vcop_grayscale_erode_rect(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, scratch_ptr_A, output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_erode_rect(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, scratch_ptr_C, output_ptr_B);

    vcop_grayscale_dilate_rect(blk_w-(se_w-1), line_ofst, blk_h-(se_h-1),
        output_ptr_B, se_w, se_h, scratch_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1), line_ofst, blk_h-2*(se_h-1),
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), scratch_ptr_C, output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_rect(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h, scratch_ptr_C, output_ptr_B);

    vcop_grayscale_erode_rect(blk_w-(se_w-1),
        line_ofst, blk_h-(se_h-1), output_ptr_B, se_w, se_h, scratch_ptr_A,
        scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1),
        line_ofst, blk_h-2*(se_h-1), scratch_ptr_C,
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_rect(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr1_C);

    vcop_grayscale_erode_rect(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, output_ptr_B, scratch_ptr2_A);

    vcop_grayscale_morp_diff(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B);


}


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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_erode_cross(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, output_ptr_B, scratch_ptr_C);

    vcop_grayscale_dilate_cross(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_A, output_ptr_B);



}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_cross(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, output_ptr_B, scratch_ptr_C);

    vcop_grayscale_erode_cross(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_A, output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_erode_cross(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_C, output_ptr_B);

    vcop_grayscale_dilate_cross(blk_w-(se_w-1), line_ofst, blk_h-(se_h-1),
        output_ptr_B, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1), line_ofst, blk_h-2*(se_h-1),
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), scratch_ptr_C, output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_cross(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_C, output_ptr_B);

    vcop_grayscale_erode_cross(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), output_ptr_B, se_w, se_h, (se_h-1)/2, (se_w-1)/2, scratch_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff(blk_w-2*(se_w-1),
        line_ofst, blk_h-2*(se_h-1), scratch_ptr_C,
        (uint8_t *)data_ptr_A.addr + (se_w-1)*line_ofst + (se_w-1), output_ptr_B);


}

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
   __vptr_uint8 output_ptr_B)
{


    vcop_grayscale_dilate_cross(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, output_ptr_B, scratch_ptr1_C);

    vcop_grayscale_erode_cross(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, (se_h-1)/2, (se_w-1)/2, output_ptr_B, scratch_ptr2_A);

    vcop_grayscale_morp_diff(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B);


}

#endif

