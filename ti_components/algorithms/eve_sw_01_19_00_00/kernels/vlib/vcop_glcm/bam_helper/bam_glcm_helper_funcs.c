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
 *  @file       bam_glcm_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gray-level
 *              co-occurrence matrix computation into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_glcm_int.h"
#include "vcop_glcm_kernel.h" /* compiler should take care of include path */

/* Maximum number of gray-levels (numLevels) that can be supported for GLCM analysis assuming
     24kB of WBUF is available for storing the output buffer */
uint8_t GLCM_TI_maxGLCMLevels_1c[BAM_GLCM_MAX_NUM_DIRECTIONS] = {110, 78, 64, 55, 49, 45, 41, 39};
uint8_t GLCM_TI_maxGLCMLevels_8c[BAM_GLCM_MAX_NUM_DIRECTIONS] = {39, 27, 22, 19, 17, 16, 14, 13};

/* Function Prototypes */
static BAM_Status BAM_Glcm_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Glcm_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    uint8_t numChannels;
    uint32_t n;
    int8_t maxColOffset, minColOffset, maxRowOffset, minRowOffset;
    uint8_t numRows, numCols;

    const BAM_Glcm_Args *args = (const BAM_Glcm_Args *) kernelArgs;

    numChannels = (args->numLevels > GLCM_TI_maxGLCMLevels_8c[args->numOffsets - 1U]) ? 1U : 8U;

    maxColOffset = 0;
    minColOffset = 0;
    maxRowOffset = 0;
    minRowOffset = 0;

    for(n = 0; n < args->numOffsets; n++) {
      maxColOffset = MAX(maxColOffset, args->colOffsets[n]);
      minColOffset = MIN(minColOffset, args->colOffsets[n]);
      maxRowOffset = MAX(maxRowOffset, args->rowOffsets[n]);
      minRowOffset = MIN(minRowOffset, args->rowOffsets[n]);
    }

    numRows = (uint8_t)(args->blockHeight - (maxRowOffset - minRowOffset));
    numCols = (uint8_t)(args->blockWidth - (maxColOffset - minColOffset));

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2U*((numChannels == 1U) ? vcop_glcm_compute_1c_param_count() : vcop_glcm_compute_8c_param_count());
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    internalBlock[SCRATCH_IDX].size = (sizeof(uint16_t)*args->numOffsets*numRows*((numCols + 1U)/2U)*2U) + 30U;
    internalBlock[SCRATCH_IDX].space = BAM_MEMSPACE_IBUFLA;

    internalBlock[WEIGHT_IDX].size = 8U;
    internalBlock[WEIGHT_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    internalBlock[WEIGHT_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[GLCM_BUFF_IDX].size = ((numChannels*args->numOffsets*args->numLevels*args->numLevels) + numChannels)*sizeof(uint16_t);
    internalBlock[GLCM_BUFF_IDX].alignment = 32U;
    internalBlock[GLCM_BUFF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[GLCM_BUFF_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IDX].size = 4U;
    outBlock[OUT_IDX].space = IBAMALG_MEMHEAP_EXTMEM;
    outBlock[OUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_glcmKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Glcm_Context),
    sizeof(BAM_Glcm_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_glcmHelperFunc =
{ &BAM_Glcm_getMemRecFunc, NULL};

