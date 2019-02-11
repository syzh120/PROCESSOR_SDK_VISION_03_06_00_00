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


/**
 *  @file       bam_hough_for_circles_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hough for
 *              circles kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_hough_for_circles_int.h"
#include "vcop_hough_for_circles_kernel.h" /* compiler should take care of include path */

/* For Compute Hough Space index BAM node */
static BAM_Status BAM_HoughForCircles_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);


static BAM_Status BAM_HoughForCircles_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    uint32_t numEdgePoints;
    const BAM_HoughForCircles_Args *args = (const BAM_HoughForCircles_Args *) kernelArgs;

    numEdgePoints = ALIGN_2SIMD((uint32_t)args->maxNumEdgePoints);

#if !VCOP_HOST_EMULATION
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) *
                      ( vcop_hough_circle_compute_idx_param_count() +
                      vcop_hough_circle_compute_idx_param_block_update_param_count() );
#else
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    /* Scratch for storing center co-ordinates (Cx, Cy)  and storing the pointer for radius for param block update*/
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX].size = 2U * numEdgePoints * sizeof(int16_t);
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX].size = 8U * sizeof(uint16_t);
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX].space = BAM_MEMSPACE_IBUFLA;

    /* Allocation requested for storing indexes of both bright and dark circles */
    outBlock[BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT].size = 2U * numEdgePoints * sizeof(uint16_t);
    outBlock[BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}

/* For Circle Detect BAM node */
static BAM_Status BAM_HoughForCirclesDetect_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);


static BAM_Status BAM_HoughForCirclesDetect_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_HoughForCirclesDetect_Args *args = (const BAM_HoughForCirclesDetect_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*
                      (vcop_hough_circle_init_hough_space_param_count() +
                       vcop_hough_circle_vote_to_hough_space_param_count() +
                       vcop_hough_for_circle_detect_param_count() +
                       vcop_hough_circle_vote_to_hough_space_param_block_update_param_count());
#else
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX].size = ALIGN_SIMD((uint32_t)args->maxHoughSpacePitch)*args->maxHoughSpaceHeight;
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX].size = sizeof(uint32_t);
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX].size = args->maxHoughSpacePitch*sizeof(uint32_t);
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT].size = args->numElemsPerBlock*sizeof(uint32_t);
    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT].space = BAM_MEMSPACE_IBUFHA;

    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT].size = args->numElemsPerBlock*sizeof(uint8_t);
    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT].space = BAM_MEMSPACE_IBUFLA;

    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT].size = 8U * sizeof(uint16_t);
    outBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}

/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_houghForCirclesKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_HoughForCircles_Context),
    sizeof(BAM_HoughForCircles_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_HOUGH_FOR_CIRCLES_NUM_INPUT_BLOCKS,
    BAM_HOUGH_FOR_CIRCLES_NUM_OUTPUT_BLOCKS,
    HOUGH_FOR_CIRCLES_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesHelperFunc =
{ &BAM_HoughForCircles_getMemRecFunc,
  NULL};

/* For Circle Detect BAM node */
BAM_KernelInfo gBAM_TI_houghForCirclesDetectKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_HoughForCirclesDetect_Context),
    sizeof(BAM_HoughForCirclesDetect_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_INPUT_BLOCKS,
    BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_OUTPUT_BLOCKS,
    HOUGH_FOR_CIRCLES_DETECT_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesDetectHelperFunc =
{ &BAM_HoughForCirclesDetect_getMemRecFunc,
  NULL};

