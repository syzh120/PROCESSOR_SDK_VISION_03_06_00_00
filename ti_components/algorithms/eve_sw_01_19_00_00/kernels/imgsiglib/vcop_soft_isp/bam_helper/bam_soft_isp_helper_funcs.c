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
 *  @file       bam_soft_isp_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating software
 *              Image Signal Processor (ISP) into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algframework.h"
#include "bam_soft_isp_int.h"
#include "vcop_soft_isp_kernel.h" /* compiler should take care of include path */


/* Function Prototypes */
static BAM_Status BAM_SoftIsp_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_SoftIsp_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs);

static BAM_Status BAM_SoftIsp_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_SoftIsp_Args *args = (const BAM_SoftIsp_Args *) kernelArgs;
    uint32_t outWidth, outHeight, outStride, bufSize;
    BAM_Status  status = BAM_S_SUCCESS;

    if((args->blockWidth > SOFT_ISP_MAX_BLOCK_WIDTH) || (args->blockHeight > SOFT_ISP_MAX_BLOCK_HEIGHT)
                                                     || (args->blockStride > SOFT_ISP_MAX_BLOCK_STRIDE))
    {
        status = BAM_E_UNSUPPORTED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2U*(vcop_decompand_piecewise_linear_param_count() +
                                        vcop_black_clamp_c_balance_param_count() +
                                        vcop_rccc_to_cccc_param_count() +
                                        MAX(vcop_gbce_simple_param_count(), vcop_gbce_interp_param_count()));

    if(args->enableExtractR== 1) {
      internalBlock[PARAMS_IDX].size += (2U*vcop_soft_isp_extract_r_param_count());
    }

    if(args->enableStats == 1) {
      internalBlock[PARAMS_IDX].size += (2U*vcop_stats_collector_dense_param_count());
    }
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    if(internalBlock[PARAMS_IDX].size > SOFT_ISP_MAX_PARAMS_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    internalBlock[GBCE_TC_IDX].size = 4U*4096U;
    internalBlock[GBCE_TC_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[GBCE_TC_IDX].space = BAM_MEMSPACE_WBUF;

    if(internalBlock[GBCE_TC_IDX].size > SOFT_ISP_MAX_GBCE_TC_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    outStride = 16U*((args->blockWidth + 15U)/16U);
    outWidth  = args->blockWidth - 4U;
    outHeight = args->blockHeight - 4U;

    bufSize = (((outWidth/2U)*(outHeight/2U)) + EXTRA_PIXELS(outWidth/2U, outWidth/2U, 8U));

    internalBlock[TEMP_RC_IDX].size = outStride*(args->blockHeight/2U)*sizeof(uint16_t);
    internalBlock[TEMP_RC_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[TEMP_RC_IDX].space = BAM_MEMSPACE_IBUFLA;
    if(internalBlock[TEMP_RC_IDX].size > SOFT_ISP_MAX_TEMP_RC_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    internalBlock[TEMP_CC_IDX].size = outStride*(args->blockHeight/2U)*sizeof(uint16_t);
    internalBlock[TEMP_CC_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[TEMP_CC_IDX].space = BAM_MEMSPACE_IBUFHA;
    if(internalBlock[TEMP_CC_IDX].size > SOFT_ISP_MAX_TEMP_CC_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    internalBlock[SCRATCH_A].size = 3U*bufSize;
    internalBlock[SCRATCH_A].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_A].space = BAM_MEMSPACE_IBUFLA;
    if(internalBlock[SCRATCH_A].size > SOFT_ISP_MAX_SCRATCH_A_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    internalBlock[SCRATCH_B].size = 4U*bufSize;
    internalBlock[SCRATCH_B].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_B].space = BAM_MEMSPACE_IBUFHA;
    if(internalBlock[SCRATCH_B].size > SOFT_ISP_MAX_SCRATCH_B_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    internalBlock[SCRATCH_C].size = 13U*bufSize;
    internalBlock[SCRATCH_C].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_C].space = BAM_MEMSPACE_WBUF;
    if(internalBlock[SCRATCH_C].size > SOFT_ISP_MAX_SCRATCH_C_SIZE)
    {
        status = BAM_E_INVALID_MEM_SIZE;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    outBlock[OUT_RC_IDX].size = (outWidth*(outHeight/2U)) + EXTRA_PIXELS(outWidth, outWidth, 4U);
    outBlock[OUT_RC_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_CC_IDX].size = (outWidth*(outHeight/2U)) + EXTRA_PIXELS(outWidth, outWidth, 4U);
    outBlock[OUT_CC_IDX].space = BAM_MEMSPACE_IBUFLA;

    if(args->enableExtractR == 1U) {
      outBlock[OUT_R_IDX].size = bufSize;
      outBlock[OUT_R_IDX].space = BAM_MEMSPACE_IBUFLA;
    }
    else {
      outBlock[OUT_R_IDX].size = 4U;
      outBlock[OUT_R_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    }

    if(args->enableStats == 1U) {
      outBlock[OUT_STATS_IDX].size = 34U;
      outBlock[OUT_STATS_IDX].space = BAM_MEMSPACE_IBUFLA;
    }
    else {
      outBlock[OUT_STATS_IDX].size = 4U;
      outBlock[OUT_STATS_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    }
EXIT:
    return (status);
}

static BAM_Status BAM_SoftIsp_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs)
{
  uint16_t i;
  const BAM_SoftIsp_Args *args = (const BAM_SoftIsp_Args *) kernelArgs;
  BAM_SoftIsp_Context *context = (BAM_SoftIsp_Context *) kernelContext;

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

  memcpy(&(context->kernelArgs), kernelArgs, gBAM_TI_softIspKernel.kernelArgSize);

  /* Communicate the buffer address of GBCE LUT via the pointer passed using Kernel Args structure */
  (*(uint32_t *(*)[])(void *)args->gbceToneCurveAddr)[0] = (uint32_t *)memRecInternal[GBCE_TC_IDX]->base;

  return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_softIspKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_SoftIsp_Context),
    sizeof(BAM_SoftIsp_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_softIspHelperFunc =
{ &BAM_SoftIsp_getMemRecFunc, &BAM_SoftIsp_setMemRecFunc};

