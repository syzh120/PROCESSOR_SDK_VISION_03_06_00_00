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
 *  @file       bam_normalizedGradXyList_helper_funcs.c
 *
 *  @brief      This header defines helper function for integrating calculation of normalized
  *                  gradient X and Y into BAM

 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_normalizedGradXyList_int.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

#define BAM_NORMALIZED_GRADXY_LIST_IMG_BUF_A_B_OFFSET (0x20000U)
/* Function Prototypes */
static BAM_Status BAM_normalizedGradXyList_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_normalizedGradXyList_setMemRecFunc(const BAM_MemRec *memRecInternal[],
            const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[],
            uint8_t numRecInternal, uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
            void *kernelContext, const void *kernelArgs);

static BAM_Status BAM_normalizedGradXyList_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !VCOP_HOST_EMULATION
    const BAM_NormalizedGradXyList_Args *args = kernelArgs;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS].size =
                           (vcop_gradients_xy_list_param_count() +
                            vcop_gradients_xy_mag_lut_index_calulcation_param_count() +
                            vcop_reciprocal_sqrt_lookup_param_count() +
                            vcop_gradients_xy_unit_vecs_param_count() +
                            vcop_gradients_xy_update_param_block_param_count()) * sizeof(uint16_t);
#else
    const BAM_NormalizedGradXyList_Args *args = (const BAM_NormalizedGradXyList_Args *)kernelArgs;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS].size = 4;
#endif

    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS].space = BAM_MEMSPACE_WBUF;

    /* To store LUT table of reciprocal square roots and to store
     XSequence list which contains 0,1.... width values left shifted by 16
     To store the size of list in WBUF so that it can be used by next kernel*/
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF].size =
                            (sizeof(uint8_t) * RECI_SQRT_LUT_NUM_CPY * RECI_SQRT_LUT_SIZE) +
                            (sizeof(uint32_t) * args->maxWidth) +
                            (sizeof(uint8_t) * 8);
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF].space = BAM_MEMSPACE_WBUF;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF].alignment = 32;

    /* To store LUT Idx ptr  and Log4a ptr*/
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFLA].size =
                                      (args->maxWidth * args->maxHeight * sizeof(uint16_t)) +
                                      (args->maxWidth * args->maxHeight * sizeof(uint8_t));
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFLA].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFLA].space = BAM_MEMSPACE_IBUFLA;

    /* To store GradXy and Reciprocal Output */
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFHA].size =
                                      (args->maxWidth * args->maxHeight * sizeof(uint32_t)) +
                                      (args->maxWidth * args->maxHeight * sizeof(uint8_t));
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFHA].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFHA].space = BAM_MEMSPACE_IBUFHA;

    /* To store the pUpperLeftXy */
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_IBUFLA].size = sizeof(uint32_t);
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_IBUFLA].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_IBUFLA].space = BAM_MEMSPACE_IBUFLA;


    outBlock[BAM_NORMALIZED_GRADXY_LIST_UNIT_XY_PORT].size =
                            args->maxWidth * args->maxHeight * sizeof(uint32_t);
    outBlock[BAM_NORMALIZED_GRADXY_LIST_UNIT_XY_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_NORMALIZED_GRADXY_LIST_UNIT_XY_PORT].space = BAM_MEMSPACE_WBUF;

    outBlock[BAM_NORMALIZED_GRADXY_LIST_XY_PORT].size =
                            args->maxWidth * args->maxHeight * sizeof(uint32_t);
    outBlock[BAM_NORMALIZED_GRADXY_LIST_XY_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_NORMALIZED_GRADXY_LIST_XY_PORT].space = BAM_MEMSPACE_WBUF;

     /* To store the pListSize */
    outBlock[BAM_NORMALIZED_GRADXY_LIST_SIZE_PORT].size = VCOP_SIMD_WIDTH * sizeof(uint16_t);
    outBlock[BAM_NORMALIZED_GRADXY_LIST_SIZE_PORT].attrs.memAttrs = BAM_MEMATTRS_CONST;
    outBlock[BAM_NORMALIZED_GRADXY_LIST_SIZE_PORT].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}


static BAM_Status BAM_normalizedGradXyList_setMemRecFunc(const BAM_MemRec *memRecInternal[],
            const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[],
            uint8_t numRecInternal, uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
            void *kernelContext, const void *kernelArgs)
{
#if !VCOP_HOST_EMULATION
  const BAM_NormalizedGradXyList_Args *args = kernelArgs;
#else
  const BAM_NormalizedGradXyList_Args *args = (const BAM_NormalizedGradXyList_Args *)kernelArgs;
#endif
  BAM_NormalizedGradXyList_Context *context = (BAM_NormalizedGradXyList_Context *)kernelContext;

  int32_t status = BAM_S_SUCCESS;
#if 0
  for ( i = 0; i < numRecInternal; i++ )
  {
    if ( memRecInternal[i]->base == NULL )
    {
      status = BAM_E_FAIL;
      goto EXIT;
    }
    context->pInternalBlock[i] = memRecInternal[i]->base;
  }

  for ( i = 0; i < numRecInputDataBlock; i++ )
  {
    if ( memRecInputDataBlock[i]->base == NULL )
    {
      status = BAM_E_FAIL;
      goto EXIT;
    }
    context->pInBlock[i] = memRecInputDataBlock[i]->base;
  }

  for ( i = 0; i < numRecOutputDataBlock; i++ )
  {
    if ( memRecOutputDataBlock[i]->base == NULL )
    {
      status = BAM_E_FAIL;
      goto EXIT;

    }
    context->pOutBlock[i] = memRecOutputDataBlock[i]->base;
  }
#endif
  context->kernelArgs = *args;

/* CHECK_MISRA("17.1 17.4")  -> Disable rule 17.1 17.4 */
/* Rule 17.1 17.4: Pointer is used in arithmetic or array index expressionv*/
/* Deviation is allowed because we hav to calculate these pointers  */
#if !VCOP_HOST_EMULATION
  context->pBlockGradientsXyList = context->pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS];
  context->pBlockGradientsXyMagLutIndexCalulcation = context->pBlockGradientsXyList +
                                         (vcop_gradients_xy_list_param_count() * sizeof(uint16_t));
  context->pBlockReciprocalSqrtLookup = context->pBlockGradientsXyMagLutIndexCalulcation +
                                         (vcop_gradients_xy_mag_lut_index_calulcation_param_count() * sizeof(uint16_t));
  context->pBlockGradientsXyUnitVecs  = context->pBlockReciprocalSqrtLookup +
                                         (vcop_reciprocal_sqrt_lookup_param_count() * sizeof(uint16_t));
  context->pBlockListSizeUpdate       = context->pBlockGradientsXyUnitVecs +
                                         (vcop_gradients_xy_unit_vecs_param_count() * sizeof(uint16_t));
#endif

  context->pLutIdxPtr = (uint8_t*)context->pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFLA];
  context->pLog4aPtr  = context->pLutIdxPtr  + (args->maxWidth * args->maxHeight * sizeof(uint16_t));

  context->pGradXyPtr = (uint8_t*)context->pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFHA];
  context->pReciprocalLutOutput = context->pGradXyPtr + (args->maxWidth * args->maxHeight * sizeof(uint32_t));

  context->pReciSqrtLut = (uint8_t*)context->pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF];
  context->pXsequence   = context->pReciSqrtLut + (RECI_SQRT_LUT_NUM_CPY * RECI_SQRT_LUT_SIZE);
  context->pListSizeWbufPtr = (uint16_t *)(void*)(context->pXsequence + (sizeof(uint32_t) * args->maxWidth));

  context->pUpperLeftXyPtr[0] = (uint32_t *)context->pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_IBUFLA];
#if !VCOP_HOST_EMULATION
  context->pUpperLeftXyPtr[1] = context->pUpperLeftXyPtr[0] + (BAM_NORMALIZED_GRADXY_LIST_IMG_BUF_A_B_OFFSET /sizeof(uint32_t));
#else
  context->pUpperLeftXyPtr[1] = context->pUpperLeftXyPtr[0];
#endif

  context->pListSizePtr       = (uint16_t *)context->pOutBlock[BAM_NORMALIZED_GRADXY_LIST_SIZE_PORT];

  /*RESET_MISRA("17.1")  -> Reset rule 17.1 */

  return status;
}

BAM_KernelInfo gBAM_TI_normalizedGradXyListKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_NormalizedGradXyList_Context),
        sizeof(BAM_NormalizedGradXyList_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        BAM_NORMALIZED_GRADXY_LIST_NUM_INPUT_BLOCKS,                          /* 1 */
        BAM_NORMALIZED_GRADXY_LIST_NUM_OUTPUT_BLOCKS,                         /* 3 */
        BAM_NORMALIZED_GRADXY_LIST_INTERNAL_NUM_BLOCK                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_normalizedGradXyListHelperFunc =
{
  &BAM_normalizedGradXyList_getMemRecFunc,
  &BAM_normalizedGradXyList_setMemRecFunc
};

