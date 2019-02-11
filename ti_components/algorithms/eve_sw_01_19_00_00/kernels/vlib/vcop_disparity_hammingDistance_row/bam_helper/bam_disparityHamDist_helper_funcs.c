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
 *  @file       bam_disparityHamDist_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hamming-based disparity calculation kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_disparityHamDist_int.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_postprocess_kernel.h"
#include "init_disparity_hammingDistance_row_params.h"
#include "vcop_disparity_hammingDistance_row_cn.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

/* Function Prototypes */
static BAM_Status BAM_DisparityHamDist_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter kernelArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
static BAM_Status BAM_DisparityHamDist_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

    uint16_t scratchBufferSize, allCostOutputBufferSize;
    uint32_t pScatterStride;
    BAM_Status status= BAM_S_SUCCESS;
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Doesn't seem it is an issue here, probably a false positive */
    const BAM_DisparityHamDist_Args *args= (const BAM_DisparityHamDist_Args*)kernelArgs;
    /*RESET_MISRA("11.8")  -> Reset rule 11.8 for GOTO */
    
    /* Make sure that codeWordByteLen is 4, currently only 32-bits hamming distance is supported */
    if (args->codeWordByteLen != 4) {
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* Make sure that out_pitch is multiple of 4 but not multiple of 32 */
    if ((args->allCostOutputStride < (args->width*SIZE_COST)) || ((args->allCostOutputStride & 3U)!=0) || ((args->allCostOutputStride & 31U)==0)) {
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* Two lines below are extracted from init_disparity_hammingDistance_row_params(). Calculate size of one line used in the first p-scatter, need to be (n*8 + 1) banks or (n*8*4 + 4)=  n*32 + 4 bytes) wide to avoid p-scatter error*/
    /*pScatterStride= (uint16_t)((((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)*(uint32_t)SIZE_COST + 31UL) & (uint32_t)(~31UL)) + 4UL ;*/ /* Round up to next multiple of 32 and then add 4 bytes */ 
    pScatterStride= (((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)*(uint32_t)SIZE_COST) + 31UL;
    pScatterStride= ((uint32_t)pScatterStride & 0xFFFFFFE0U);
    pScatterStride+= 4UL;

    scratchBufferSize= (uint16_t)pScatterStride*args->width;

    /* Return the allCostOutput buffer size that needs to be allocated */
    allCostOutputBufferSize= (uint16_t)args->allCostOutputStride*(uint16_t)(2U + ((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)); /* The +2 is a requirement from  vcop_disparity_genPrevAndNextMinCost()  */

#if (!VCOP_HOST_EMULATION)
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].size = (uint32_t)DISPARITY_HAMDIST_PARAMS_SIZE;
#else
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].size = (uint32_t)DISPARITY_HAMDIST_PARAMS_SIZE;
#endif
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].space             = BAM_MEMSPACE_IBUFLA;

    /*
     * Will contain one byte of value 0x80 used as 'collate mask' and 32 bytes used for p-scatter's osffsets.
     */
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].size = 34U;
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].space             = BAM_MEMSPACE_WBUF;

    /* Size of scratch should be scratchBufferSize 
     */
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].size = (uint32_t)scratchBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].space             = BAM_MEMSPACE_IBUFHA;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].alignment         = 32;

    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].size = (uint32_t)scratchBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].alignment         = 32;

    /* Don't support for now
    if (args->extraRLdisparities== 1) {
        internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = MAX((args->numDisparities / args->disparityStep) * SIZE_COST * (args->width + args->numDisparities - 1), allCostOutputBufferSize);
    }
    else {
        internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = allCostOutputBufferSize;
    }
    */
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = allCostOutputBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].space             = BAM_MEMSPACE_IBUFLA;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].alignment         = 32;

    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].size = allCostOutputBufferSize;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].space= BAM_MEMSPACE_WBUF;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].alignment= 32;

    outBlock[DISPARITY_HAMDIST_DISP_OUT_IDX].size = args->width;
    outBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX].size = 2*args->width;
    outBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX].size = 2*(args->numDisparities/args->disparityStep);
    
    if (args->adjacentCosts== 1) {
        outBlock[DISPARITY_HAMDIST_PREV_ADJ_COST].size = 2*args->width;
        outBlock[DISPARITY_HAMDIST_NEXT_ADJ_COST].size = 2*args->width;
    }
    else {
        outBlock[DISPARITY_HAMDIST_PREV_ADJ_COST].size = 4;
        outBlock[DISPARITY_HAMDIST_NEXT_ADJ_COST].size = 4;
    }
    
    /* Don't support for now
    if (args->extraRLdisparities== 1) {
        outBlock[DISPARITY_HAMDIST_RL_DISP_OUT_IDX].size = ALIGN_2SIMD(args->width + args->numDisparities - 1);
        outBlock[DISPARITY_HAMDIST_RL_MINCOST_OUT_IDX].size = SIZE_COST * ALIGN_2SIMD(args->width + args->numDisparities - 1);
    }
    else {
        outBlock[DISPARITY_HAMDIST_RL_DISP_OUT_IDX].size = 4;
        outBlock[DISPARITY_HAMDIST_RL_MINCOST_OUT_IDX].size = 4;
    }
    */

    Exit:
    return status;
}


BAM_KernelInfo gBAM_TI_disparityHamDist_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_DisparityHamDist_Context),
        sizeof(BAM_DisparityHamDist_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 3 */
        NUM_OUT_BLOCKS,                         /* 5 */
        NUM_INTERNAL_BLOCKS                     /* 8 */
};

BAM_KernelHelperFuncDef gBAM_TI_disparityHamDist_HelperFunc =
{ &BAM_DisparityHamDist_getMemRecFunc, NULL};

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */


