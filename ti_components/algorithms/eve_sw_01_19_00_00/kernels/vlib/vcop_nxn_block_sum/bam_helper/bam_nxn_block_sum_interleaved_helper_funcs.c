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
* @file bam_nxn_block_sum_interleaved_helper_funcs.c
*
* @brief    This file contains all kernel helper functions for nxn_block_sum_interleaved
*           kernel
*
* @author Anshu Jain(anshu.jain@ti.com)
*
* @version 0.0 (Nov 2013) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_nxn_block_sum_interleaved_helper_funcs.h"
#include "vcop_nxn_block_sum_kernel.h"

#define NUM_BINS 6
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */	
#define ALIGN_SIZE(x,y) ((((x) + ((y)-(1U))) / (y)) * (y)) 
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */
BAM_Status BAM_nxn_block_sum_interleaved_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);
/**
*******************************************************************************
* @fn        BAM_nxn_block_sum_interleaved_getMemRecFunc
* @brief
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_nxn_block_sum_interleaved_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{
    const BAM_nxn_block_sum_interleaved_Args *args = (const BAM_nxn_block_sum_interleaved_Args *)kernelArgs;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t scratchBufSize;
    uint32_t nxnOutBufSize;
    uint32_t alignedWidth;
    uint32_t alignedHeight;
    if ( args->numBins == NUM_BINS)
    {
    alignedWidth  = ALIGN_SIZE(args->blockW,(args->nValue*VCOP_SIMD_WIDTH));
    alignedHeight = ALIGN_SIZE(args->blockH,(args->nValue*VCOP_SIMD_WIDTH));
    scratchBufSize =  (((((alignedWidth * alignedHeight)/(args->nValue))/(VCOP_SIMD_WIDTH * VCOP_SIMD_WIDTH)) *
                      VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1U) * sizeof(uint32_t)) +
                      ((((alignedWidth * alignedHeight)/(args->nValue * args->nValue))/
                      (VCOP_SIMD_WIDTH * VCOP_SIMD_WIDTH))* VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1U) *
                      sizeof(uint32_t)));
    nxnOutBufSize = (((args->blockW * args->blockH) / (args->nValue * args->nValue))* sizeof(uint16_t));

#if (!VCOP_HOST_EMULATION)
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*(vcop_nxn_sum_interleaved_param_count());
#else
    /* This field could be any non-zero number for host emulation, its not really used for host emualtion */
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].size = 4;
#endif
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].size = scratchBufSize;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].size = scratchBufSize;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].space = BAM_MEMSPACE_IBUFLA;

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].size = nxnOutBufSize ;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].space = BAM_MEMSPACE_IBUFLA;

    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].size = nxnOutBufSize;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].space = BAM_MEMSPACE_IBUFHA;

    }
    return status;
}

BAM_KernelInfo gBAM_TI_nxn_block_sum_interleavedKernel =
{
    0,  /*kernelId */
    sizeof(BAM_nxn_block_sum_interleaved_Context),/*kernelContextSize*/
    sizeof(BAM_nxn_block_sum_interleaved_Args),
    BAM_EVE, /* Core Type */
    BAM_NODE_COMPUTE, /*nodeType */
    NXN_BLOCK_SUM_INTERLEAVED_NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NXN_BLOCK_SUM_INTERLEAVED_NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NXN_BLOCK_SUM_INTERLEAVED_NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_nxn_block_sum_interleavedHelperFunc =
{
    &BAM_nxn_block_sum_interleaved_getMemRecFunc,
    NULL
};

