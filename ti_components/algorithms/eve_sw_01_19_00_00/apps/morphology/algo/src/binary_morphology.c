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
/*     @file : binary_morphology.c                                          */
/*                                                                          */
/*     @brief : This file contains the wrapper functions for the following  */
/*     binary morphological processing with flat structuring elements    */
/*     (SE) : opening, closing, top hat, bottom hat and morphological       */
/*     gradient. The wrappers implement various connections of              */
/*     vcop_binary_dilate, vcop_binary_erode and                      */
/*     vcop_binary_morp_diff kernels to achieve the different            */
/*     morphological operations.                                            */
/*                                                                          */
/*     Wrappers for the following morphological operations are provided:    */
/*     1. vcop_binary_open_xxx                                           */
/*           Performs binary opening of an 8-bit binary input image   */
/*           at data_ptr, of size blkWidth by blkHeight, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     2. Binary_close_xxx                                          */
/*           Performs binary closing of an 8-bit binary input image   */
/*           at data_ptr, of size blkWidth by blkHeight, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     3. Binary_tophat_xxx                                         */
/*           Performs binary top hat of an 8-bit binary input image   */
/*           at data_ptr, of size blkWidth by blkHeight, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     4. Binary_bottomhat_xxx                                      */
/*           Performs binary bottom hat of an 8-bit binary image      */
/*           at data_ptr, of size blkWidth by blkHeight, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     5. Binary_morph_grad_xxx                                     */
/*           Performs binary morphological gradient of an 8-bit          */
/*           binary input image at data_ptr, of size blkWidth by blkHeight,     */
/*           with a flat structuring element of size se_w by se_h,          */
/*           specified with a mask of 1's and 0's at se_ptr. The output     */
/*           is written into output_ptr.                                    */
/*                                                                          */
/*     @version 1.0 (december 2014) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#include <stdint.h>
#include <stdint.h>
#include <vcop.h>
#include "xdais_types.h"
#include <stdio.h>

#include "vcop_vec_bin_image_dilate_cross_kernel.h"
#include "vcop_vec_bin_image_dilate_mask_kernel.h"
#include "vcop_vec_bin_image_dilate_square_kernel.h"
#include "vcop_vec_bin_image_erode_cross_kernel.h"
#include "vcop_vec_bin_image_erode_mask_kernel.h"
#include "vcop_vec_bin_image_erode_square_kernel.h"
#include "vcop_vec_bin_image_morph_diff_kernel.h"

#include "imorphology_ti.h"
#include "morphology_dma_auto_incr.h"
#include "binary_morphology.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN_U(x,y)         (((x) + (y) - 1U)/(y))*(y)
#define ALIGN_S(x,y)         (((x) + (y) - 1 )/(y))*(y)

#define MAX_BLOCK_WIDTH    (BIN_MORPH_MAX_IMAGE_WIDTH)
#define MAX_BLOCK_HEIGHT   (32U)
#define MAX_BLOCK_SIZE     (MAX_BLOCK_WIDTH * MAX_BLOCK_HEIGHT)

#define PACKED_PIXEL_COUNT (8U)
#define BLOCK_OVERLAP      (MORPHOLOGY_TI_BINARY_SE_HEIGHT - 1U)

#if (VCOP_HOST_EMULATION)
#define Binary_Morphology_malloc(heap, size)   malloc(size)
#define Binary_Morphology_free(ptr)            free(ptr)
#else
#define Binary_Morphology_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define Binary_Morphology_free(ptr)            (vcop_free(ptr))
#endif
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

/* Parameter Block Initialization Functions  - Prototypes */
void Binary_open_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open);

void Binary_close_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close);

void Binary_tophat_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat);

void Binary_bottomhat_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat);

void Binary_morph_grad_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad);

void Binary_open_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open);

void Binary_close_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close);

void Binary_tophat_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat);

void Binary_bottomhat_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat);

void Binary_morph_grad_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad);


void Binary_open_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open);

void Binary_close_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close);


void Binary_tophat_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat);

void Binary_bottomhat_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat);


void Binary_morph_grad_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad);

#if (!VCOP_HOST_EMULATION)
void Binary_open_mask_vloops(EVELIB_KernelContextType pblock);
void Binary_close_mask_vloops(EVELIB_KernelContextType pblock);
void Binary_tophat_mask_vloops(EVELIB_KernelContextType pblock);
void Binary_bottomhat_mask_vloops(EVELIB_KernelContextType pblock);
void Binary_morph_grad_mask_vloops(EVELIB_KernelContextType pblock);
void Binary_open_square_vloops(EVELIB_KernelContextType pblock);
void Binary_close_square_vloops(EVELIB_KernelContextType pblock);
void Binary_tophat_square_vloops(EVELIB_KernelContextType pblock);
void Binary_bottomhat_square_vloops(EVELIB_KernelContextType pblock);
void Binary_morph_grad_square_vloops(EVELIB_KernelContextType pblock);
void Binary_open_cross_vloops(EVELIB_KernelContextType pblock);
void Binary_close_cross_vloops(EVELIB_KernelContextType pblock);
void Binary_tophat_cross_vloops(EVELIB_KernelContextType pblock);
void Binary_bottomhat_cross_vloops(EVELIB_KernelContextType pblock);
void Binary_morph_grad_cross_vloops(EVELIB_KernelContextType pblock);
#endif

void Binary_Morphology_Init_Frame(void *args);


/* Parameter Block Initialization Functions */

/* Binary Mask Open */
void Binary_open_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_mask_init(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratchPtr_C, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_open->pblock_erode);

    vcop_vec_bin_image_dilate_mask_init(scratchPtr_C, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight, pblock_open->pblock_dilate);
#else
    vcop_vec_bin_image_erode_mask(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratchPtr_C, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_mask(scratchPtr_C, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Mask Close */
void Binary_close_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_mask_init(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratchPtr_C, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_close->pblock_dilate);

    vcop_vec_bin_image_erode_mask_init(scratchPtr_C, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        outputPtr_B, blkWidth, blkStride, blkHeight, pblock_close->pblock_erode);
#else
    vcop_vec_bin_image_dilate_mask(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratchPtr_C, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_mask(scratchPtr_C, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        outputPtr_B, blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Mask Tophat Operation */
void Binary_tophat_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_mask_init(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        outputPtr_B, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_tophat->pblock_erode);

    vcop_vec_bin_image_dilate_mask_init(outputPtr_B, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratchPtr_C, blkWidth, blkStride, blkHeight, pblock_tophat->pblock_dilate);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, scratchPtr_C, (uint16_t)0, outputPtr_B,
        pblock_tophat->pblock_img_diff);

#else
    vcop_vec_bin_image_erode_mask(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        outputPtr_B, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_mask(outputPtr_B, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratchPtr_C, blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2*blkStride)/32), 2, scratchPtr_C, 0, outputPtr_B);
#endif
}

/* Binary Mask Bottom hat Operation */
void Binary_bottomhat_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_mask_init(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_bottomhat->pblock_dilate);

    vcop_vec_bin_image_erode_mask_init(outputPtr_B, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratchPtr_C, blkWidth, blkStride, blkHeight, pblock_bottomhat->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratchPtr_C, (uint16_t)0,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, outputPtr_B,
        pblock_bottomhat->pblock_img_diff);

#else
    vcop_vec_bin_image_dilate_mask(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_mask(outputPtr_B, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratchPtr_C, blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight, scratchPtr_C, 0,
        dataPtr_A + ((2*blkStride)/32), 2, outputPtr_B);
#endif
}

/* Binary Mask Morphological Gradient */
void Binary_morph_grad_mask_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  seCompCol1Ptr_C[],
    uint32_t  seCompCol2Ptr_C[],
    uint32_t  seCompCol3Ptr_C[],
    uint32_t  seReflCol1Ptr_C[],
    uint32_t  seReflCol2Ptr_C[],
    uint32_t  seReflCol3Ptr_C[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_mask_init(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratch_ptr1_C, blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_dilate);

    vcop_vec_bin_image_erode_mask_init(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratch_ptr2_A, blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratch_ptr1_C, (uint16_t)0,
        scratch_ptr2_A, (uint16_t)0, outputPtr_B, pblock_morph_grad->pblock_img_diff);
#else
    vcop_vec_bin_image_dilate_mask(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
        seReflCol3Ptr_C, scratch_ptr1_C, blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_erode_mask(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C, seCompCol3Ptr_C,
        scratch_ptr2_A, blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        scratch_ptr1_C, 0, scratch_ptr2_A, 0, outputPtr_B);
#endif
}


/* Binary Square Open */
void Binary_open_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_square_init(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_open->pblock_erode);

    vcop_vec_bin_image_dilate_square_init(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight, pblock_open->pblock_dilate);
#else
    vcop_vec_bin_image_erode_square(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_square(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Square Close */
void Binary_close_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_square_init(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_close->pblock_dilate);

    vcop_vec_bin_image_erode_square_init(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight, pblock_close->pblock_erode);
#else
    vcop_vec_bin_image_dilate_square(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_square(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Square Tophat Operation */
void Binary_tophat_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_square_init(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_tophat->pblock_erode);

    vcop_vec_bin_image_dilate_square_init(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight, pblock_tophat->pblock_dilate);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, scratchPtr_C, (uint16_t)0, outputPtr_B,
        pblock_tophat->pblock_img_diff);
#else
    vcop_vec_bin_image_erode_square(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_square(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2*blkStride)/32), 2, scratchPtr_C, 0, outputPtr_B);
#endif
}

/* Binary Square Bottom hat Operation */
void Binary_bottomhat_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_square_init(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_bottomhat->pblock_dilate);

    vcop_vec_bin_image_erode_square_init(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight, pblock_bottomhat->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratchPtr_C, (uint16_t)0,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, outputPtr_B,
        pblock_bottomhat->pblock_img_diff);
#else
    vcop_vec_bin_image_dilate_square(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_square(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight, scratchPtr_C, 0,
        dataPtr_A + ((2*blkStride)/32), 2, outputPtr_B);
#endif
}

/* Binary Square Morphological Gradient */
void Binary_morph_grad_square_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_square_init(dataPtr_A, scratch_ptr1_C,
        blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_dilate);

    vcop_vec_bin_image_erode_square_init(dataPtr_A, scratch_ptr2_A,
        blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratch_ptr1_C, (uint16_t)0,
        scratch_ptr2_A, (uint16_t)0, outputPtr_B, pblock_morph_grad->pblock_img_diff);
#else
    vcop_vec_bin_image_dilate_square(dataPtr_A, scratch_ptr1_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_erode_square(dataPtr_A, scratch_ptr2_A,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        scratch_ptr1_C, 0, scratch_ptr2_A, 0, outputPtr_B);

#endif
}


/* Binary Cross Open */
void Binary_open_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_open)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_cross_init(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_open->pblock_erode);

    vcop_vec_bin_image_dilate_cross_init(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight, pblock_open->pblock_dilate);
#else
    vcop_vec_bin_image_erode_cross(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_cross(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Cross Close */
void Binary_close_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_open_close_t *pblock_close)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_cross_init(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_close->pblock_dilate);

    vcop_vec_bin_image_erode_cross_init(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight, pblock_close->pblock_erode);
#else
    vcop_vec_bin_image_dilate_cross(dataPtr_A, scratchPtr_C,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_cross(scratchPtr_C, outputPtr_B,
        blkWidth, blkStride, blkHeight);
#endif
}

/* Binary Cross Tophat Operation */
void Binary_tophat_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_tophat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_erode_cross_init(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_tophat->pblock_erode);

    vcop_vec_bin_image_dilate_cross_init(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight, pblock_tophat->pblock_dilate);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, scratchPtr_C, (uint16_t)0, outputPtr_B,
        pblock_tophat->pblock_img_diff);
#else
    vcop_vec_bin_image_erode_cross(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_dilate_cross(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        dataPtr_A + ((2*blkStride)/32), 2, scratchPtr_C, 0, outputPtr_B);
#endif
}

/* Binary Cross Bottom hat Operation */
void Binary_bottomhat_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratchPtr_C[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_bottomhat)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_cross_init(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP, pblock_bottomhat->pblock_dilate);

    vcop_vec_bin_image_erode_cross_init(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight, pblock_bottomhat->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratchPtr_C, (uint16_t)0,
        dataPtr_A + ((2U*blkStride)/32U), (uint16_t)2, outputPtr_B,
        pblock_bottomhat->pblock_img_diff);
#else
    vcop_vec_bin_image_dilate_cross(dataPtr_A, outputPtr_B,
        blkWidth, blkStride, blkHeight + BLOCK_OVERLAP);

    vcop_vec_bin_image_erode_cross(outputPtr_B, scratchPtr_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight, scratchPtr_C, 0,
        dataPtr_A + ((2*blkStride)/32), 2, outputPtr_B);
#endif
}

/* Binary Cross Morphological Gradient */
void Binary_morph_grad_cross_init(
    uint16_t  blkWidth,
    uint16_t  blkStride,
    uint16_t  blkHeight,
    uint32_t  dataPtr_A[],
    uint32_t  scratch_ptr1_C[],
    uint32_t  scratch_ptr2_A[],
    uint32_t  outputPtr_B[],
    stblock_morph_t *pblock_morph_grad)
{
#if (!VCOP_HOST_EMULATION)
    vcop_vec_bin_image_dilate_cross_init(dataPtr_A, scratch_ptr1_C,
        blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_dilate);

    vcop_vec_bin_image_erode_cross_init(dataPtr_A, scratch_ptr2_A,
        blkWidth, blkStride, blkHeight, pblock_morph_grad->pblock_erode);

    vcop_vec_bin_image_morph_diff_init(blkWidth, blkStride, blkHeight, scratch_ptr1_C, (uint16_t)0,
        scratch_ptr2_A, (uint16_t)0, outputPtr_B, pblock_morph_grad->pblock_img_diff);
#else
    vcop_vec_bin_image_dilate_cross(dataPtr_A, scratch_ptr1_C,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_erode_cross(dataPtr_A, scratch_ptr2_A,
        blkWidth, blkStride, blkHeight);

    vcop_vec_bin_image_morph_diff(blkWidth, blkStride, blkHeight,
        scratch_ptr1_C, 0, scratch_ptr2_A, 0, outputPtr_B);
#endif
}


#if (!VCOP_HOST_EMULATION)
/**********************************************************/
/*                                           EXEC FUNCTIONS                                           */
/**********************************************************/
void Binary_open_mask_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_erode_mask_vloops(pblock_open->pblock_erode);
    vcop_vec_bin_image_dilate_mask_vloops(pblock_open->pblock_dilate);

}

void Binary_close_mask_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_mask_vloops(pblock_close->pblock_dilate);
    vcop_vec_bin_image_erode_mask_vloops(pblock_close->pblock_erode);
}

/* Binary Mask Tophat Operation */
void Binary_tophat_mask_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_erode_mask_vloops(pblock_tophat->pblock_erode);
    vcop_vec_bin_image_dilate_mask_vloops(pblock_tophat->pblock_dilate);
    vcop_vec_bin_image_morph_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Binary Mask Bottom hat Operation */
void Binary_bottomhat_mask_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_mask_vloops(pblock_bottomhat->pblock_dilate);
    vcop_vec_bin_image_erode_mask_vloops(pblock_bottomhat->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Binary Mask Morphological Gradient */
void Binary_morph_grad_mask_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_mask_vloops(pblock_morph_grad->pblock_dilate);
    vcop_vec_bin_image_erode_mask_vloops(pblock_morph_grad->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_morph_grad->pblock_img_diff);
}

/* Binary Square Open */
void Binary_open_square_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_erode_square_vloops(pblock_open->pblock_erode);
    vcop_vec_bin_image_dilate_square_vloops(pblock_open->pblock_dilate);
}

/* Binary Square Close */
void Binary_close_square_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_square_vloops(pblock_close->pblock_dilate);
    vcop_vec_bin_image_erode_square_vloops(pblock_close->pblock_erode);
}

/* Binary Square Tophat Operation */
void Binary_tophat_square_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_erode_square_vloops(pblock_tophat->pblock_erode);
    vcop_vec_bin_image_dilate_square_vloops(pblock_tophat->pblock_dilate);
    vcop_vec_bin_image_morph_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Binary Square Bottom hat Operation */
void Binary_bottomhat_square_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_square_vloops(pblock_bottomhat->pblock_dilate);
    vcop_vec_bin_image_erode_square_vloops(pblock_bottomhat->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Binary Square Morphological Gradient */
void Binary_morph_grad_square_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_square_vloops(pblock_morph_grad->pblock_dilate);
    vcop_vec_bin_image_erode_square_vloops(pblock_morph_grad->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_morph_grad->pblock_img_diff);
}

/* Binary Cross Open */
void Binary_open_cross_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_open = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_erode_cross_vloops(pblock_open->pblock_erode);
    vcop_vec_bin_image_dilate_cross_vloops(pblock_open->pblock_dilate);
}

/* Binary Cross Close */
void Binary_close_cross_vloops(EVELIB_KernelContextType pblock)
{
    stblock_open_close_t *pblock_close = (stblock_open_close_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_cross_vloops(pblock_close->pblock_dilate);
    vcop_vec_bin_image_erode_cross_vloops(pblock_close->pblock_erode);
}

/* Binary Cross Tophat Operation */
void Binary_tophat_cross_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_tophat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_erode_cross_vloops(pblock_tophat->pblock_erode);
    vcop_vec_bin_image_dilate_cross_vloops(pblock_tophat->pblock_dilate);
    vcop_vec_bin_image_morph_diff_vloops(pblock_tophat->pblock_img_diff);
}

/* Binary Cross Bottom hat Operation */
void Binary_bottomhat_cross_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_bottomhat = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_cross_vloops(pblock_bottomhat->pblock_dilate);
    vcop_vec_bin_image_erode_cross_vloops(pblock_bottomhat->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_bottomhat->pblock_img_diff);
}

/* Binary Cross Morphological Gradient */
void Binary_morph_grad_cross_vloops(EVELIB_KernelContextType pblock)
{
    stblock_morph_t *pblock_morph_grad = (stblock_morph_t *)(void *)pblock;

    vcop_vec_bin_image_dilate_cross_vloops(pblock_morph_grad->pblock_dilate);
    vcop_vec_bin_image_erode_cross_vloops(pblock_morph_grad->pblock_erode);
    vcop_vec_bin_image_morph_diff_vloops(pblock_morph_grad->pblock_img_diff);
}
#endif

void Binary_Morphology_Init(Binary_Morphology_Obj *handle)
{
    uint32_t pBlock_dilate_size, pBlock_erode_size, pBlock_diff_size;
    int32_t  srcBlkPitch, srcBlkHeightTot;
    int32_t  dstBlkHeight, dstBlkPitch;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    srcBlkPitch     = ALIGN_S((int32_t)MAX_BLOCK_WIDTH, 4);
    srcBlkHeightTot = (int32_t)MAX_BLOCK_HEIGHT;

    dstBlkHeight    = srcBlkHeightTot;
    dstBlkPitch     = srcBlkPitch;

#if (!VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    pBlock_dilate_size = (vcop_vec_bin_image_dilate_mask_param_count()   * sizeof(__pblock_vcop_vec_bin_image_dilate_mask[0]))
                       + (vcop_vec_bin_image_dilate_square_param_count() * sizeof(__pblock_vcop_vec_bin_image_dilate_square[0]))
                       + (vcop_vec_bin_image_dilate_cross_param_count()  * sizeof(__pblock_vcop_vec_bin_image_dilate_cross[0]));

    pBlock_erode_size  = (vcop_vec_bin_image_erode_mask_param_count()   * sizeof(__pblock_vcop_vec_bin_image_erode_mask[0]))
                       + (vcop_vec_bin_image_erode_square_param_count() * sizeof(__pblock_vcop_vec_bin_image_erode_square[0]))
                       + (vcop_vec_bin_image_erode_cross_param_count()  * sizeof(__pblock_vcop_vec_bin_image_erode_cross[0]));

    pBlock_diff_size   = vcop_vec_bin_image_morph_diff_param_count() * sizeof(__pblock_vcop_vec_bin_image_morph_diff[0]);

    handle->stParamBlock.pblock_dilate   = (uint16_t *)Binary_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_dilate_size);
    handle->stParamBlock.pblock_erode    = (uint16_t *)Binary_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_erode_size);
    handle->stParamBlock.pblock_img_diff = (uint16_t *)Binary_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_diff_size);
    handle->stParamBlock_open_close.pblock_dilate = handle->stParamBlock.pblock_dilate;
    handle->stParamBlock_open_close.pblock_erode  = handle->stParamBlock.pblock_erode;
#endif

    /* sizeof(handle->seCompCol1Ptr_C[0]) = sizeof(uint32_t)  */
    handle->srcPtr_A     = (uint32_t *)Binary_Morphology_malloc(VCOP_IBUFLA, (int32_t)(srcBlkPitch * srcBlkHeightTot));

    handle->seCompCol1Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));
    handle->seCompCol2Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));
    handle->seCompCol3Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));

    handle->seReflCol1Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));
    handle->seReflCol2Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));
    handle->seReflCol3Ptr_C  = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,
                                                                    (int32_t)(VCOP_SIMD_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT)
                                                                    *sizeof(uint32_t));

    handle->scratchPtr_C = (uint32_t *)Binary_Morphology_malloc(VCOP_WMEM,   (int32_t)((srcBlkPitch*srcBlkHeightTot) + srcBlkPitch));
    handle->scratchPtr_A = (uint32_t *)Binary_Morphology_malloc(VCOP_IBUFLA, (int32_t)((srcBlkPitch*srcBlkHeightTot) + srcBlkPitch));
    handle->outputPtr_B  = (uint32_t *)Binary_Morphology_malloc(VCOP_IBUFHA, (int32_t)((dstBlkPitch*dstBlkHeight)    + dstBlkPitch));

    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */
}

typedef struct
{
    MORPHOLOGY_TI_StructuringElementShape  seShape;
    MORPHOLOGY_TI_Operation                morphologyMode;
    uint16_t   blkWidth;
    uint16_t   blkStride;
    uint16_t   blkHeight;
    uint32_t  *dataPtr_A;
    uint32_t  *seCompCol1Ptr_C;
    uint32_t  *seCompCol2Ptr_C;
    uint32_t  *seCompCol3Ptr_C;
    uint32_t  *seReflCol1Ptr_C;
    uint32_t  *seReflCol2Ptr_C;
    uint32_t  *seReflCol3Ptr_C;
    uint32_t  *scratchPtr_C;
    uint32_t  *scratchPtr_A;
    uint32_t  *outputPtr_B;
    stblock_morph_t          stParamBlock;
    stblock_open_close_t     stParamBlock_open_close;
    EVELIB_KernelFuncType    execFunc[1];
    EVELIB_KernelContextType context[1];
    uint8_t                  numKernels;
} Binary_Morphology_ExecParams;


void Binary_Morphology_Init_Frame(void *args)
{
    Binary_Morphology_ExecParams          *execParams     = (Binary_Morphology_ExecParams *)args;
    MORPHOLOGY_TI_StructuringElementShape  seShape        = execParams->seShape;
    MORPHOLOGY_TI_Operation                morphologyMode = execParams->morphologyMode;
    uint16_t   blkWidth         = execParams->blkWidth  *(uint16_t)PACKED_PIXEL_COUNT;
    uint16_t   blkStride        = execParams->blkStride *(uint16_t)PACKED_PIXEL_COUNT;
    uint16_t   blkHeight        = execParams->blkHeight;
    uint32_t  *dataPtr_A        = execParams->dataPtr_A;
    uint32_t  *seCompCol1Ptr_C  = execParams->seCompCol1Ptr_C;
    uint32_t  *seCompCol2Ptr_C  = execParams->seCompCol2Ptr_C;
    uint32_t  *seCompCol3Ptr_C  = execParams->seCompCol3Ptr_C;
    uint32_t  *seReflCol1Ptr_C  = execParams->seReflCol1Ptr_C;
    uint32_t  *seReflCol2Ptr_C  = execParams->seReflCol2Ptr_C;
    uint32_t  *seReflCol3Ptr_C  = execParams->seReflCol3Ptr_C;
    uint32_t  *scratchPtr_C     = execParams->scratchPtr_C;
    uint32_t  *scratchPtr_A     = execParams->scratchPtr_A;
    uint32_t  *outputPtr_B      = execParams->outputPtr_B;
    stblock_morph_t      *stParamBlock            = &execParams->stParamBlock;
    stblock_open_close_t *stParamBlock_open_close = &execParams->stParamBlock_open_close;
    EVELIB_KernelFuncType    execFunc[1];
    EVELIB_KernelContextType context[1];
    uint8_t   numKernels = 1U;

    execFunc[0] = NULL;
    context[0]  = NULL;

    switch( morphologyMode ) {
        case MORPHOLOGY_TI_DILATE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_dilate_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_vec_bin_image_dilate_mask_init(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
                        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight, stParamBlock->pblock_dilate);
#else
                    vcop_vec_bin_image_dilate_mask(dataPtr_A, seReflCol1Ptr_C, seReflCol2Ptr_C,
                        seReflCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight);
#endif
                break;
                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_dilate_square_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_vec_bin_image_dilate_square_init(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight, stParamBlock->pblock_dilate);
#else
                    vcop_vec_bin_image_dilate_square(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight);
#endif
                break;
                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_dilate_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_vec_bin_image_dilate_cross_init(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight, stParamBlock->pblock_dilate);
#else
                    vcop_vec_bin_image_dilate_cross(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight);
#endif
                break;
                default:
                break;
            }

            break;

        case MORPHOLOGY_TI_ERODE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_erode_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_vec_bin_image_erode_mask_init(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight, stParamBlock->pblock_erode);
#else
                    vcop_vec_bin_image_erode_mask(dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, outputPtr_B, blkWidth, blkStride, blkHeight);
#endif
                break;
                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_erode_square_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_vec_bin_image_erode_square_init(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight, stParamBlock->pblock_erode);
#else
                    vcop_vec_bin_image_erode_square(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight);
#endif
                break;
                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &vcop_vec_bin_image_erode_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_vec_bin_image_erode_cross_init(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight, stParamBlock->pblock_erode);
#else
                    vcop_vec_bin_image_erode_cross(dataPtr_A, outputPtr_B,
                        blkWidth, blkStride, blkHeight);
#endif
                break;
                default:
                break;
            }

            break;

        case MORPHOLOGY_TI_OPEN:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_open_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_open_mask_init(blkWidth, blkStride, blkHeight, dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, seReflCol1Ptr_C, seReflCol2Ptr_C, seReflCol3Ptr_C, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);

                break;

                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_open_square_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_open_square_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_open_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_open_cross_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_CLOSE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_close_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_close_mask_init(blkWidth, blkStride, blkHeight, dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, seReflCol1Ptr_C, seReflCol2Ptr_C, seReflCol3Ptr_C, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);
                break;

                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_close_square_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_close_square_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);

                break;

                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_close_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;
#endif
                    Binary_close_cross_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock_open_close);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_TOPHAT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_tophat_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_tophat_mask_init(blkWidth, blkStride, blkHeight, dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, seReflCol1Ptr_C, seReflCol2Ptr_C, seReflCol3Ptr_C, scratchPtr_C,
                        outputPtr_B, stParamBlock);

                break;

                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_tophat_square_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_tophat_square_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock);

                break;

                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_tophat_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_tophat_cross_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_BOTTOMHAT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_bottomhat_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_bottomhat_mask_init(blkWidth, blkStride, blkHeight, dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, seReflCol1Ptr_C, seReflCol2Ptr_C, seReflCol3Ptr_C, scratchPtr_C,
                        outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_bottomhat_square_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_bottomhat_square_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_bottomhat_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_bottomhat_cross_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        outputPtr_B, stParamBlock);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_GRADIENT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_morph_grad_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_morph_grad_mask_init(blkWidth, blkStride, blkHeight, dataPtr_A, seCompCol1Ptr_C, seCompCol2Ptr_C,
                        seCompCol3Ptr_C, seReflCol1Ptr_C, seReflCol2Ptr_C, seReflCol3Ptr_C, scratchPtr_C,
                        scratchPtr_A, outputPtr_B, stParamBlock);

                break;

                case MORPHOLOGY_TI_RECT_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_morph_grad_square_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_morph_grad_square_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        scratchPtr_A, outputPtr_B, stParamBlock);

                break;

                case MORPHOLOGY_TI_CROSS_SE:
#if (!VCOP_HOST_EMULATION)
                    execFunc[0] = &Binary_morph_grad_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;
#endif
                    Binary_morph_grad_cross_init(blkWidth, blkStride, blkHeight, dataPtr_A, scratchPtr_C,
                        scratchPtr_A, outputPtr_B, stParamBlock);

                break;
                default:
                break;
            }
            break;
            default:
            break;
    }

#if (!VCOP_HOST_EMULATION)
    execParams->execFunc[0] = execFunc[0];
    execParams->context[0]  = context[0];
    execParams->numKernels  = numKernels;
#endif

}


void Binary_Morphology_Process(
                         Binary_Morphology_Obj *handle,
                         uint8_t      *src,
                         uint16_t      srcImageWidth,
                         uint16_t      srcImageHeight,
                         uint16_t      srcImagePitch,
                         uint8_t      *dst,
                         uint16_t      dstImageWidth,
                         uint16_t      dstImageHeight,
                         uint16_t      dstImagePitch,
                         uint8_t       struct_elem[],
                         uint8_t       seShape,
                         uint8_t       operation)
{
    Binary_Morphology_ExecParams execParams;
    uint32_t  i, srcBlkPadX, srcBlkPadY;
    uint32_t  srcBlkWidth, srcBlkHeight, srcBlkPitch;
    uint32_t  dstBlkWidth, dstBlkHeight, dstBlkPitch;
    uint32_t (*seCompCol1Ptr_C)[], (*seCompCol2Ptr_C)[], (*seCompCol3Ptr_C)[];
    uint32_t (*seReflCol1Ptr_C)[], (*seReflCol2Ptr_C)[], (*seReflCol3Ptr_C)[];

    seCompCol1Ptr_C = (uint32_t (*)[])(void *)handle->seCompCol1Ptr_C;
    seCompCol2Ptr_C = (uint32_t (*)[])(void *)handle->seCompCol2Ptr_C;
    seCompCol3Ptr_C = (uint32_t (*)[])(void *)handle->seCompCol3Ptr_C;
    seReflCol1Ptr_C = (uint32_t (*)[])(void *)handle->seReflCol1Ptr_C;
    seReflCol2Ptr_C = (uint32_t (*)[])(void *)handle->seReflCol2Ptr_C;
    seReflCol3Ptr_C = (uint32_t (*)[])(void *)handle->seReflCol3Ptr_C;

    srcBlkPadX = 0;
    srcBlkPadY = ((operation == MORPHOLOGY_TI_DILATE) ||
                  (operation == MORPHOLOGY_TI_ERODE)  ||
                  (operation == MORPHOLOGY_TI_GRADIENT)) ? (MORPHOLOGY_TI_BINARY_SE_HEIGHT-1U) : 2U*(MORPHOLOGY_TI_BINARY_SE_HEIGHT-1U);


    srcBlkWidth     = srcImageWidth;
    /* kernel requires the pitch to be a multiple of 32 because word npt read has to be word aligned. */
    srcBlkPitch     = ALIGN_U(srcBlkWidth, 4U);

    srcBlkHeight    = MAX_BLOCK_HEIGHT - srcBlkPadY;

    /* For better performance if width is small. */
    if(srcBlkPitch <= (MAX_BLOCK_WIDTH/2U))
    {
        srcBlkHeight = (2U*MAX_BLOCK_HEIGHT) - srcBlkPadY;
    }

    if(srcBlkHeight > srcImageHeight)
    {
        srcBlkHeight = srcImageHeight - srcBlkPadY;
    }

    dstBlkWidth     = srcBlkWidth;
    dstBlkHeight    = srcBlkHeight;
    dstBlkPitch     = srcBlkPitch;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    if ( seShape == MORPHOLOGY_TI_CUSTOM_SE )
    {
        /*-----------------------------------------------------------------
              Generate Structuring Element.
              -----------------------------------------------------------------*/
        /* Erosion kernel requires the Complement (Bitwise not) of the Structuring Element. */
        for(i = 0U; i < 8U; i++)
        {
            (*seCompCol1Ptr_C)[i    ] = (struct_elem[0] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol2Ptr_C)[i    ] = (struct_elem[1] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol3Ptr_C)[i    ] = (struct_elem[2] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol1Ptr_C)[i+8U ] = (struct_elem[3] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol2Ptr_C)[i+8U ] = (struct_elem[4] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol3Ptr_C)[i+8U ] = (struct_elem[5] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol1Ptr_C)[i+16U] = (struct_elem[6] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol2Ptr_C)[i+16U] = (struct_elem[7] == 1U) ? 0x0 : 0xFFFFFFFFU;
            (*seCompCol3Ptr_C)[i+16U] = (struct_elem[8] == 1U) ? 0x0 : 0xFFFFFFFFU;
        }
        /* Generate refl of Structuring Element for the Dilation kernel. */
        for(i = 0U; i < 8U; i++)
        {
            (*seReflCol1Ptr_C)[i    ] = (struct_elem[8] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol2Ptr_C)[i    ] = (struct_elem[7] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol3Ptr_C)[i    ] = (struct_elem[6] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol1Ptr_C)[i+8U ] = (struct_elem[5] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol2Ptr_C)[i+8U ] = (struct_elem[4] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol3Ptr_C)[i+8U ] = (struct_elem[3] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol1Ptr_C)[i+16U] = (struct_elem[2] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol2Ptr_C)[i+16U] = (struct_elem[1] == 0U) ? 0x0 : 0xFFFFFFFFU;
            (*seReflCol3Ptr_C)[i+16U] = (struct_elem[0] == 0U) ? 0x0 : 0xFFFFFFFFU;
        }

    }
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

    execParams.morphologyMode  = (MORPHOLOGY_TI_Operation)operation;
    execParams.seShape         = (MORPHOLOGY_TI_StructuringElementShape)seShape;
    execParams.blkWidth        = srcBlkWidth;
    execParams.blkStride       = srcBlkPitch;
    execParams.blkHeight       = srcBlkHeight;
    execParams.dataPtr_A       = handle->srcPtr_A;
    execParams.seCompCol1Ptr_C = *seCompCol1Ptr_C;
    execParams.seCompCol2Ptr_C = *seCompCol2Ptr_C;
    execParams.seCompCol3Ptr_C = *seCompCol3Ptr_C;
    execParams.seReflCol1Ptr_C = *seReflCol1Ptr_C;
    execParams.seReflCol2Ptr_C = *seReflCol2Ptr_C;
    execParams.seReflCol3Ptr_C = *seReflCol3Ptr_C;
    execParams.scratchPtr_C    = handle->scratchPtr_C;
    execParams.scratchPtr_A    = handle->scratchPtr_A;
    execParams.outputPtr_B     = handle->outputPtr_B;
    execParams.stParamBlock            = handle->stParamBlock;
    execParams.stParamBlock_open_close = handle->stParamBlock_open_close;
    execParams.numKernels      = 1U;

#if (VCOP_HOST_EMULATION)
    execParams.execFunc[0] = (EVELIB_KernelFuncType)Binary_Morphology_Init_Frame;
    execParams.context[0]  = (EVELIB_KernelContextType)&execParams;
    execParams.numKernels  = 1U;
#else
    Binary_Morphology_Init_Frame((void *)&execParams);
#endif


    morphology_DMAAutoIncrInit(
        handle->autoIncrementContext,
        src,
        (uint32_t)srcImageWidth,
        (uint32_t)srcImageHeight,
        (int32_t) srcImagePitch,
        dst,
        (uint32_t)dstImageWidth,
        (uint32_t)dstImageHeight,
        (int32_t) dstImagePitch,
        (uint8_t *)(void *)handle->srcPtr_A,
        srcBlkWidth,
        srcBlkHeight,
        (int32_t)srcBlkPitch,
        (uint8_t *)(void *)handle->outputPtr_B,
        dstBlkWidth,
        dstBlkHeight,
        (int32_t)dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY);

    morphology_DMAAutoIncrExec(
        handle->autoIncrementContext,
        execParams.execFunc,
        execParams.context,
        execParams.numKernels);

    morphology_DMAAutoIncrDeInit();

}



void Binary_Morphology_Deinit(Binary_Morphology_Obj *handle)
{
#if (!VCOP_HOST_EMULATION)
      Binary_Morphology_free(handle->stParamBlock.pblock_dilate);
      Binary_Morphology_free(handle->stParamBlock.pblock_erode);
      Binary_Morphology_free(handle->stParamBlock.pblock_img_diff);
#endif
      Binary_Morphology_free(handle->srcPtr_A);
      Binary_Morphology_free(handle->seCompCol1Ptr_C);
      Binary_Morphology_free(handle->seCompCol2Ptr_C);
      Binary_Morphology_free(handle->seCompCol3Ptr_C);
      Binary_Morphology_free(handle->seReflCol1Ptr_C);
      Binary_Morphology_free(handle->seReflCol2Ptr_C);
      Binary_Morphology_free(handle->seReflCol3Ptr_C);
      Binary_Morphology_free(handle->scratchPtr_C);
      Binary_Morphology_free(handle->scratchPtr_A);
      Binary_Morphology_free(handle->outputPtr_B);
}

