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
 *  @file       bam_census_8bits_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating census 8-bits transform kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_census_8bits_int.h"
#include "vcop_census_8bits_kernel.h"
#include "vcop_census_8bits_cn.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

/* Function Prototypes */
static BAM_Status BAM_Census_8bits_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter kernelArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
static BAM_Status BAM_Census_8bits_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
    /*RESET_MISRA("16.7")  -> Reset rule 16.7 */
{
    int32_t numWinHiter, numWinWiter;
    uint16_t numCensusOrientations;
    uint16_t numBytesPerCensus;
    uint16_t scratchStride;
    BAM_Status status= BAM_S_SUCCESS;
#if (!VCOP_HOST_EMULATION)
    const BAM_Census_8bits_Args *args= kernelArgs;
#else
    const BAM_Census_8bits_Args *args= (const BAM_Census_8bits_Args*)kernelArgs;
#endif

    numCensusOrientations= _CENSUS_WIN_SIZE((uint16_t)args->winWidth, (uint16_t)args->winHeight, (uint16_t)args->winHorzStep, (uint16_t)args->winVertStep);
    numBytesPerCensus= (numCensusOrientations + 7u) / 8u;

    /* Make sure that out_pitch is multiple of 4 but not multiple of 32 */
    if ((args->out_pitch < (numBytesPerCensus*args->in_w)) || (((uint32_t)args->out_pitch & 3U)!= 0) || (((uint32_t)args->out_pitch & 31U)==0)) {
        status= BAM_E_FAIL;
        goto Exit;
    }

    numWinHiter= (args->winHeight + (args->winVertStep -1) )/ args->winVertStep;
    numWinWiter= (args->winWidth + (args->winHorzStep -1) )/ args->winHorzStep;

#if (!VCOP_HOST_EMULATION)
    internalBlock[CENSUS_8BITS_PARAMS_IDX].size = 2U*vcop_census_8bits_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[CENSUS_8BITS_PARAMS_IDX].size = 4U;
#endif
    /*
     * (2*NUM_WIN_W_ITER*NUM_WIN_H_ITER + 16)*((computeWidth+15)/16)*computeHeight bytes
     */
    internalBlock[CENSUS_8BITS_SCRATCH_BITMASK_IDX].size = ((2*numWinWiter*numWinHiter) + (2*(int32_t)VCOP_SIMD_WIDTH))*((args->in_w+((2*(int32_t)VCOP_SIMD_WIDTH)-1))/(2*(int32_t)VCOP_SIMD_WIDTH))*args->in_h;
    internalBlock[CENSUS_8BITS_SCRATCH_BITMASK_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[CENSUS_8BITS_SCRATCH_BITMASK_IDX].space             = BAM_MEMSPACE_IBUFHA;

    /* Size of scratch should be :
     * MAX(computeWidth*scratchStride*(NUM_WIN_W_ITER*NUM_WIN_H_ITER+7)/8, inStride * (computeHeight + winHeight -1 ) + 15) bytes
     */
    scratchStride= (uint16_t)((args->in_h + 31U) & ((uint16_t)(~(uint16_t)31U))) + 4U; /* This line is taken from init_census_8bits_params(), line #93. It makes sure that the stride is such that there is no bank conflict when using p-scatter */
    internalBlock[CENSUS_8BITS_SCRATCH_IDX].size = MAX((args->in_w*(int32_t)scratchStride*((numWinWiter*numWinHiter) + ((int32_t)VCOP_SIMD_WIDTH-1)))/(int32_t)VCOP_SIMD_WIDTH, (args->in_pitch * (args->in_h + (args->winHeight -1) )) + ((2*(int32_t)VCOP_SIMD_WIDTH)-1)) ;
    internalBlock[CENSUS_8BITS_SCRATCH_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[CENSUS_8BITS_SCRATCH_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[CENSUS_8BITS_SCRATCH_IDX].alignment         = 32;

    /* Size should be 32 bytes */
    internalBlock[CENSUS_8BITS_OFFSET_IDX].size = 32U;
    internalBlock[CENSUS_8BITS_OFFSET_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[CENSUS_8BITS_OFFSET_IDX].space             = BAM_MEMSPACE_WBUF;

    /*size should be (NUM_WIN_W_ITER*NUM_WIN_H_ITER+7)/8 bytes. */
    internalBlock[CENSUS_8BITS_CODEWORDMASK_IDX].size = ((numWinWiter*numWinHiter)+((int32_t)VCOP_SIMD_WIDTH-1))/(int32_t)VCOP_SIMD_WIDTH;
    internalBlock[CENSUS_8BITS_CODEWORDMASK_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[CENSUS_8BITS_CODEWORDMASK_IDX].space             = BAM_MEMSPACE_WBUF;

    /*size should be (computeHeight+7)/8 bytes bytes. */
    internalBlock[CENSUS_8BITS_ROWMASK_IDX].size = (args->in_h + ((int32_t)VCOP_SIMD_WIDTH - 1))/(int32_t)VCOP_SIMD_WIDTH;
    internalBlock[CENSUS_8BITS_ROWMASK_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[CENSUS_8BITS_ROWMASK_IDX].space             = BAM_MEMSPACE_WBUF;

    outBlock[CENSUS_8BITS_OUT_IDX].size = args->out_pitch*args->in_h;

Exit:
    return status;
}


BAM_KernelInfo gBAM_TI_census_8bits_Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Census_8bits_Context),
    sizeof(BAM_Census_8bits_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 6 */
};

BAM_KernelHelperFuncDef gBAM_TI_census_8bits_HelperFunc =
{ &BAM_Census_8bits_getMemRecFunc, NULL};

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */
