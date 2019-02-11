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
 *  @file       bam_ncc_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating ncc kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_ncc_int.h"
#include "vcop_ncc_kernel.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */
#define ALIGN_SIMD2(a)   (((a) + 2U*(uint32_t)VCOP_SIMD_WIDTH-1U) & ~(2U*(uint32_t)VCOP_SIMD_WIDTH-1U))

/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

/* Function Prototypes */
static BAM_Status BAM_Ncc_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter kernelArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
static BAM_Status BAM_Ncc_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */
{
    uint16_t scratchStride, sumStride;
    BAM_Status status= BAM_S_SUCCESS;
#if (!VCOP_HOST_EMULATION)
    const BAM_Ncc_Args *args= kernelArgs;
#else
    const BAM_Ncc_Args *args= (const BAM_Ncc_Args*)kernelArgs;
#endif

#if (!VCOP_HOST_EMULATION)
    internalBlock[NCC_SLIDING_SUM_PARAMS_IDX].size = 2U*vcop_slidingSum_param_count();
    internalBlock[NCC_PARAMS_IDX].size = 2U*vcop_ncc_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[NCC_SLIDING_SUM_PARAMS_IDX].size = 4U;
    internalBlock[NCC_PARAMS_IDX].size = 4U;
#endif

    internalBlock[NCC_TEMPLATE_IDX].size = 2*args->templateHeight * args->templateWidth;
    internalBlock[NCC_TEMPLATE_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[NCC_TEMPLATE_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[NCC_TEMPLATE_IDX].alignment         = 4U;

    scratchStride= ((uint16_t)((((uint16_t)4*args->outputHeight) + (uint16_t)31U) & (uint16_t)(~(uint16_t)31U)) + (uint16_t)4U); /* This line is taken from init_slidingSum_params(), line #40. It makes sure that the stride is such that there is no bank conflict when using p-scatter */
    internalBlock[NCC_SCRATCH_IDX].size = scratchStride*((args->outputWidth + (uint16_t)args->templateWidth) - (uint16_t)1);
    internalBlock[NCC_SCRATCH_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[NCC_SCRATCH_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[NCC_SCRATCH_IDX].alignment         = 32U;

    internalBlock[NCC_OFFSET_IDX].size = 32U;
    internalBlock[NCC_OFFSET_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[NCC_OFFSET_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[NCC_OFFSET_IDX].alignment        = 4U;

    internalBlock[NCC_SCRATCH_LINE_IDX].size = (uint32_t)MAX(ALIGN_SIMD2(((uint32_t)args->outputWidth + (uint32_t)args->templateWidth) - (uint32_t)1), ALIGN_SIMD2((uint32_t)args->outputHeight));
    internalBlock[NCC_SCRATCH_LINE_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[NCC_SCRATCH_LINE_IDX].space             = BAM_MEMSPACE_IBUFLA;
    internalBlock[NCC_SCRATCH_LINE_IDX].alignment         = 4U;

    sumStride= ((uint16_t)((((uint16_t)4*args->outputWidth) + (uint16_t)31U) & (uint16_t)(~(uint16_t)31U)) + (uint16_t)4U); /* This line is taken from init_slidingSum_params(), line #41. It makes sure that the stride is such that there is no bank conflict when using p-scatter */
    internalBlock[NCC_SUM_IDX].size = (sumStride + (uint16_t)4)*args->outputHeight;
    internalBlock[NCC_SUM_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[NCC_SUM_IDX].space             = BAM_MEMSPACE_IBUFHA;
    internalBlock[NCC_SUM_IDX].alignment         = 32U;

    outBlock[NCC_NUMCC_OUT_IDX].size = 4*args->outputWidth*args->outputHeight;
    outBlock[NCC_DENOMVAR_OUT_IDX].size = 4*args->outputWidth*args->outputHeight;

    return status;
}


BAM_KernelInfo gBAM_TI_ncc_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_Ncc_Context),
        sizeof(BAM_Ncc_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 6 */
};

BAM_KernelHelperFuncDef gBAM_TI_ncc_HelperFunc =
{ &BAM_Ncc_getMemRecFunc, NULL};

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */
