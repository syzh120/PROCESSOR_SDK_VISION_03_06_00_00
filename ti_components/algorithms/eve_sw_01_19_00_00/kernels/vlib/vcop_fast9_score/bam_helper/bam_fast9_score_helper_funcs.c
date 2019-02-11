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
 *  @file       bam_fast9_score_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 score
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_fast9_score_int.h"
#include "vcop_fast9_score_kernel.h" /* compiler should take care of include path */

const uint8_t LUT_EXT_IDX_SAD[NUM_IND_SAD*NUM_BANKS] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
    27, 27, 27, 27, 27, 27, 27, 27
};

const uint8_t LUT_EXT_IDX_THR[NUM_IND_THR*NUM_BANKS] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    27, 27, 27, 27, 27, 27, 27, 27
};
/* Function Prototypes */
static BAM_Status BAM_Fast9_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Fast9_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Fast9_Score_Args *args = (const BAM_Fast9_Score_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
if (args->score_method)
{
    internalBlock[PARAMS_IDX].size = 2U*vcop_fast9_score_kernel_param_count();
}
else
{
    internalBlock[PARAMS_IDX].size = 2U*vcop_fast9_thresh_score_param_count();
}
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif

    internalBlock[PTEMP_BUF_IDX].size = args->num_features * 8U * 9U;
    internalBlock[PTEMP_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[PTEMP_BUF_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[PTEMP_IDX].size = args->num_features * 8U * 8U;
    internalBlock[PTEMP_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[PTEMP_IDX].space = BAM_MEMSPACE_IBUFLA;

    /* Make sure the LUT is placed in WBUF since we DMA this
       If not in WBUF, then make 2 copies, in A and B buffers so that it works in
       Aliased view */

if (args->score_method)
    {
        internalBlock[LUT_IDX].size = sizeof(LUT_EXT_IDX_SAD); /* fixed for LUT index */
        internalBlock[LUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
        internalBlock[LUT_IDX].space = BAM_MEMSPACE_WBUF;

        /* Dummy allocation */
        internalBlock[BSCORE_IDX].size = 4U;
        internalBlock[BSCORE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        internalBlock[BSCORE_IDX].space = BAM_MEMSPACE_IBUFLA;
    }
else
    {
        internalBlock[LUT_IDX].size = sizeof(LUT_EXT_IDX_THR); /* fixed for LUT index */
        internalBlock[LUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
        internalBlock[LUT_IDX].space = BAM_MEMSPACE_WBUF;

        internalBlock[BSCORE_IDX].size = args->num_features * 16U;
        internalBlock[BSCORE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        internalBlock[BSCORE_IDX].space = BAM_MEMSPACE_IBUFLA;
    }

    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].size = sizeof(SCORE_INTERNAL_MEMORY_IBUFHA);
    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].space = BAM_MEMSPACE_IBUFHA;
    
    internalBlock[SCORE_B_IDX].size = args->num_features * sizeof(uint16_t);
    internalBlock[SCORE_B_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_B_IDX].space = BAM_MEMSPACE_IBUFLA;

    internalBlock[SCORE_D_IDX].size = args->num_features * sizeof(uint16_t);
    internalBlock[SCORE_D_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_D_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_SCORE_IDX].size = args->total_features * sizeof(uint16_t);
    outBlock[OUT_SCORE_IDX].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_fast9scoreKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Fast9_Score_Context),
    sizeof(BAM_Fast9_Score_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 7(SAD method) or 9(thresh method) */
};

BAM_KernelHelperFuncDef gBAM_TI_fast9scoreHelperFunc =
{ &BAM_Fast9_Score_getMemRecFunc, NULL};

