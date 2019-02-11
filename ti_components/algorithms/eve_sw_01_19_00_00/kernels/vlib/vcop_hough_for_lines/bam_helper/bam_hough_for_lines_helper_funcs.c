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
 *  @file       bam_hough_for_lines_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hough for lines
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_hough_for_lines_int.h"
#include "vcop_hough_for_lines_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_HoughForLines_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_HoughForLines_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    uint16_t      transposeStride;
    uint32_t      transposeBufSize;
    uint32_t      interimArraySize;
#if !VCOP_HOST_EMULATION
    internalBlock[HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX].size =
                      (sizeof(uint16_t) * vcop_hough_for_lines_param_count()) +
                      (sizeof(uint16_t) * vcop_merge_voted_rho_array_param_count());
#else
    internalBlock[HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    transposeStride = ((( ( (uint16_t)HOUGH_FOR_LINES_RHO_MAX_LENGTH * sizeof(uint16_t)) / 2U ) / 4U) + 1U ) * 4U;

    interimArraySize = HOUGH_FOR_LINES_MAX_LIST_SIZE * sizeof(uint16_t);
    transposeBufSize = 8U * (uint32_t)transposeStride ;

    /* This buffer is reused for second kernel of merging 8copy to single copy also ,
       hence maximum of  of it should be transposeBufSize  and  listSize*/

    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].size = max(transposeBufSize , interimArraySize);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].space = BAM_MEMSPACE_IBUFHA;


    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].size = 8U * HOUGH_FOR_LINES_RHO_MAX_LENGTH *
                                                                      sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].space = BAM_MEMSPACE_WBUF;


    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].size = transposeStride * 8U;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].size = 8U * sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].size = 2U  * sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_houghForLinesKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_HoughForLines_Context),
    NULL,
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,
    NUM_OUT_BLOCKS,
    NUM_INTERNAL_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_houghForLinesHelperFunc =
{ &BAM_HoughForLines_getMemRecFunc,
  NULL};


