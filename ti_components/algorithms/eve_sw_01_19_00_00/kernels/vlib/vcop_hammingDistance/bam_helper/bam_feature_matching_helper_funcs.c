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
 *  @file       bam_feature_matching_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Hamming distance
 *              based corrrespondence matching computation into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_feature_matching_int.h"
#include "vcop_feature_matching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_featureMatching_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_featureMatching_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
  const BAM_featureMatching_Args *args = (const BAM_featureMatching_Args *)kernelArgs;

#if !VCOP_HOST_EMULATION
  internalBlock[PARAMS_IDX].size = 2U*(vcop_featureMatch_initialize_param_count() +
                                      vcop_findTwoBestMatches_param_count() +
                                      vcop_pickConfidentMatches_param_count() +
                                      (2U*vcop_twoBestMatches_update_n_param_count()));

  if(args->descriptorSize == 32U) {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_32_param_count() +
                                         vcop_featureMatch_32_pblk_update_param_count() +
                                         vcop_featureMatch_32_pblk_reset_param_count()));
  }
  else if(args->descriptorSize < 32U) {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_lt_32_param_count() +
                                         vcop_featureMatch_lt_32_pblk_update_param_count() +
                                         vcop_featureMatch_lt_32_pblk_reset_param_count()));
  }
  else {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_gt_32_param_count() +
                                         vcop_featureMatch_gt_32_pblk_update_param_count() +
                                         vcop_featureMatch_gt_32_pblk_reset_param_count()));
  }
#else
  internalBlock[PARAMS_IDX].size = 4U;
#endif

  internalBlock[SCRATCH_HAM_IDX].size  = ((args->descriptorSize <= 32U) ? 36U : 68U)*8U*((args->numDescriptors2 + 1U)/2U);
  internalBlock[SCRATCH_HAM_IDX].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_DESCRIPTOR_MASK].size = (args->descriptorSize != 32U) ? 32U*((args->descriptorSize + 31U)/32U) : 4U;
  internalBlock[SCRATCH_DESCRIPTOR_MASK].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_SCATTER_OFST].size = (args->descriptorSize > 32U) ? 8U*sizeof(uint16_t) : 4U;
  internalBlock[SCRATCH_SCATTER_OFST].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_HAM_DIST_IDX].size = 2U*((args->numDescriptors2 + 1U)/2U)*16U* sizeof(uint32_t);
  internalBlock[SCRATCH_HAM_DIST_IDX].space = BAM_MEMSPACE_IBUFLA;

  internalBlock[SCRATCH_MINDIST0_IDX].size = 16U*((args->numDescriptors1 + 15U)/16U)* sizeof(uint32_t);
  internalBlock[SCRATCH_MINDIST0_IDX].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_MINDIST1_IDX].size = 16U*((args->numDescriptors1 + 15U)/16U)* sizeof(uint32_t);
  internalBlock[SCRATCH_MINDIST1_IDX].space = BAM_MEMSPACE_WBUF;

  outBlock[OUT_IDX].size = sizeof(uint16_t)*8U*((args->numDescriptors1 + 7U)/8U);
  outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFHA;

  return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_featureMatchingKernel =
{
  0,                                      /* kernelId */
  sizeof(BAM_featureMatching_Context),
  sizeof(BAM_featureMatching_Args),
  BAM_EVE,                                /* coreType */
  BAM_NODE_COMPUTE,                       /* nodeType */
  NUM_IN_BLOCKS,                          /* 1 */
  NUM_OUT_BLOCKS,                         /* 1 */
  NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_featureMatchingHelperFunc =
  {&BAM_featureMatching_getMemRecFunc, NULL};

