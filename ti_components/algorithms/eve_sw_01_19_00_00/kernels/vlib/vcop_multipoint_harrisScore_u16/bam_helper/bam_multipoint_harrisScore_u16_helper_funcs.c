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
 *  @file       bam_multipoint_harrisScore_u16_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating multi-point
 *              16-bit Harris score kernel into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algframework.h"
#include "bam_multipoint_harrisScore_u16_int.h"
#include "vcop_multipoint_harrisScore_u16_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Multipoint_Harris_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Multipoint_Harris_Score_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs);


static BAM_Status BAM_Multipoint_Harris_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Multipoint_Harris_Score_Args *args = (const BAM_Multipoint_Harris_Score_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_multipoint_harrisScore_7x7_u16_param_count();
#else
    /* Since the kernel contains param block update, this field should be at-least size
       of actual param block */
    internalBlock[PARAMS_IDX].size = 320U;
#endif

    internalBlock[SEQ_ARRAY_IDX].size = 8U*sizeof(uint16_t);
    internalBlock[SEQ_ARRAY_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[SEQ_ARRAY_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[SCRATCH_A].size = 2U*(ALIGN_2SIMD((uint32_t)args->numPoints)*sizeof(int32_t));
    internalBlock[SCRATCH_A].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_A].space = BAM_MEMSPACE_IBUFLA;

    internalBlock[SCRATCH_B].size = (2U*(((7U*36U*ALIGN_2SIMD((uint32_t)args->numPoints))/8U) + 32U)) +
                                    (2U*(ALIGN_SIMD((uint32_t)args->numPoints)*sizeof(uint32_t)));
    internalBlock[SCRATCH_B].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_B].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[SCRATCH_C].size = (((7U*36U*ALIGN_2SIMD((uint32_t)args->numPoints))/8U) + 32U) +
                                    (ALIGN_2SIMD((uint32_t)args->numPoints)*sizeof(uint32_t));
    internalBlock[SCRATCH_C].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_C].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IDX].size = 2U*sizeof(uint16_t)*args->totalNumPoints;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}


static BAM_Status BAM_Multipoint_Harris_Score_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs)
{
  uint16_t i;
  const BAM_Multipoint_Harris_Score_Args *args = (const BAM_Multipoint_Harris_Score_Args *) kernelArgs;
  BAM_Multipoint_Harris_Score_Context *context = (BAM_Multipoint_Harris_Score_Context *) kernelContext;

  /* Populate context with buffer details and kernel args */
  for(i = 0; i < numRecInternal; i++) {
      context->pInternalBlock[i] = memRecInternal[i]->base;
  }

  for(i = 0; i < numRecInputDataBlock; i++) {
      context->pInBlock[i] = memRecInputDataBlock[i]->base;
  }

  for(i = 0; i < numRecOutputDataBlock; i++) {
      context->pOutBlock[i] = memRecOutputDataBlock[i]->base;
  }

  memcpy(&(context->kernelArgs), kernelArgs, gBAM_TI_multipointHarrisScoreKernel.kernelArgSize);

  /* Communicate the address of the output buffer via the pointer passed using Kernel Args structure */
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* Function pointers converted to uint32_t */
  *(args->pOutScoreBuffer) = (uintptr_t)memRecOutputDataBlock[OUT_IDX]->base;
  /* RESET_MISRA("11.3")  -> Reset rule 11.3  */

  return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_multipointHarrisScoreKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Multipoint_Harris_Score_Context),
    sizeof(BAM_Multipoint_Harris_Score_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 5 */
};

BAM_KernelHelperFuncDef gBAM_TI_multipointHarrisScoreHelperFunc =
{ &BAM_Multipoint_Harris_Score_getMemRecFunc, &BAM_Multipoint_Harris_Score_setMemRecFunc};

