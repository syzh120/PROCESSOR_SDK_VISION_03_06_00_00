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
 *              based corrrespondence matching computation into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_feature_matching_int.h"
#include "vcop_feature_matching_kernel.h" /* compiler should take care of include path */

static BAM_Status Bam_featureMatching_initFrame(void *kernelContext);

static BAM_Status Bam_featureMatching_initFrame(void *kernelContext)
{
  BAM_Status status = 0;
  BAM_featureMatching_Context *context = (BAM_featureMatching_Context *)kernelContext;
  uint16_t (*pScatterOffsets)[FEATURE_MATCHING_MAX_SCRATCH_SCATTER_OFST_SIZE/2U];
  uint8_t (*pDescriptorMask)[];
  uint32_t i;

  context->iter = 0;

  context->innerLoopCount = (context->kernelCtrlArgs.numDesc1PerIter + 15U)/16U;
  context->loopCount2 = (context->kernelCtrlArgs.numDescFullList2 +
      (context->kernelCtrlArgs.numDesc2PerIter - 1U))/context->kernelCtrlArgs.numDesc2PerIter;

  if(context->kernelArgs.descriptorSize != 32U) {
    pDescriptorMask = (uint8_t (*)[])context->pInternalBlock[SCRATCH_DESCRIPTOR_MASK];
    for(i = 0; i < (32U*((context->kernelArgs.descriptorSize + 31U)/32U)); i++) {
      (*pDescriptorMask)[i] = (i < context->kernelArgs.descriptorSize) ? 0xFFU : 0x00;
    }
  }

  if(context->kernelArgs.descriptorSize > 32U) {
    pScatterOffsets = (uint16_t (*)[FEATURE_MATCHING_MAX_SCRATCH_SCATTER_OFST_SIZE/2U])context->pInternalBlock[SCRATCH_SCATTER_OFST];
    for(i = 0; i < 8U; i++) {
      (*pScatterOffsets)[i] = (uint16_t)(68U * i);
    }
  }

#if (!VCOP_HOST_EMULATION)
  uint16_t (*pParamBlock)[FEATURE_MATCHING_MAX_PARAMS_SIZE];

  pParamBlock = (uint16_t (*)[FEATURE_MATCHING_MAX_PARAMS_SIZE])context->pInternalBlock[PARAMS_IDX];
  context->pblock_vcop_featureMatch_initialize = *pParamBlock;
  vcop_featureMatch_initialize_init(
    (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
    (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
    16U*((context->kernelCtrlArgs.numDesc1PerIter + 15U)/16U),
    context->pblock_vcop_featureMatch_initialize);
  pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_featureMatch_initialize_param_count());

  context->pblock_vcop_findTwoBestMatches = *pParamBlock;
  vcop_findTwoBestMatches_init(
    (uint32_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
    (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
    (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
    16U, context->kernelCtrlArgs.numDesc2PerIter,
    context->pblock_vcop_findTwoBestMatches);
  pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_findTwoBestMatches_param_count());

  context->pblock_vcop_featureMatching = *pParamBlock;
  if(context->kernelArgs.descriptorSize == 32U) {
    vcop_featureMatching_32_init((uint32_t *)context->pInBlock[STR2_IDX],
      (uint32_t *)context->pInBlock[STR1_IDX],
      (uint8_t*)context->pInternalBlock[SCRATCH_HAM_IDX],
      (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
      context->kernelCtrlArgs.numDesc2PerIter, context->kernelArgs.mode,
      context->kernelArgs.descriptorPitch, 0,
      context->pblock_vcop_featureMatching);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatching_32_param_count());
    context->vcop_featureMatching_vloops = &vcop_featureMatching_32_vloops;

    /* To update addresses of pSting2, pMinDist0 & pMinDist1 in the
       innermost loop */
    context->pblock_vcop_featureMatch_pblk_update = *pParamBlock;
    vcop_featureMatch_32_pblk_update_init(
      (uint32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      16U*context->kernelArgs.descriptorPitch, 4U*16U,
      context->pblock_vcop_featureMatch_pblk_update);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_32_pblk_update_param_count());
    context->vcop_featureMatch_pblk_update_vloops = &vcop_featureMatch_32_pblk_update_vloops;

    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* Pointers need to be converted to integers for arithematic computation within the kernel. */

    /* To restore addresses of pSting2, pMinDist0 & pMinDist1 after the
       innermost loop and increment the startIdx by numDescriptors2 */
    context->pblock_vcop_featureMatch_pblk_reset = *pParamBlock;
    vcop_featureMatch_32_pblk_reset_init(
      (int32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      context->kernelCtrlArgs.numDesc2PerIter,
      (context->loopCount2*context->kernelCtrlArgs.numDesc2PerIter) - 1U,
      (uint32_t)context->pInBlock[STR1_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
      context->pblock_vcop_featureMatch_pblk_reset);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_32_pblk_reset_param_count());
    context->vcop_featureMatch_pblk_reset_vloops = &vcop_featureMatch_32_pblk_reset_vloops;
  }
  else if(context->kernelArgs.descriptorSize < 32U) {
    vcop_featureMatching_lt_32_init((uint32_t *)context->pInBlock[STR2_IDX],
      (uint32_t *)context->pInBlock[STR1_IDX],
      (uint32_t *)context->pInternalBlock[SCRATCH_DESCRIPTOR_MASK],
      (uint8_t*)context->pInternalBlock[SCRATCH_HAM_IDX],
      (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
      context->kernelCtrlArgs.numDesc2PerIter, context->kernelArgs.mode,
      context->kernelArgs.descriptorPitch, 0,
      context->pblock_vcop_featureMatching);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatching_lt_32_param_count());
    context->vcop_featureMatching_vloops = &vcop_featureMatching_lt_32_vloops;

    /* To update addresses of pSting2, pMinDist0 & pMinDist1 in the
       innermost loop */
    context->pblock_vcop_featureMatch_pblk_update = *pParamBlock;
    vcop_featureMatch_lt_32_pblk_update_init(
      (uint32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      16U*context->kernelArgs.descriptorPitch, 4U*16U,
      context->pblock_vcop_featureMatch_pblk_update);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_lt_32_pblk_update_param_count());
    context->vcop_featureMatch_pblk_update_vloops = &vcop_featureMatch_lt_32_pblk_update_vloops;

    /* To restore addresses of pSting2, pMinDist0 & pMinDist1 after the
       innermost loop and increment the startIdx by numDescriptors2 */
    context->pblock_vcop_featureMatch_pblk_reset = *pParamBlock;
    vcop_featureMatch_lt_32_pblk_reset_init(
      (int32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      context->kernelCtrlArgs.numDesc2PerIter,
      (context->loopCount2*context->kernelCtrlArgs.numDesc2PerIter) - 1U,
      (uint32_t)context->pInBlock[STR1_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
      context->pblock_vcop_featureMatch_pblk_reset);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_lt_32_pblk_reset_param_count());
    context->vcop_featureMatch_pblk_reset_vloops = &vcop_featureMatch_lt_32_pblk_reset_vloops;
  }
  else {
    vcop_featureMatching_gt_32_init((uint32_t *)context->pInBlock[STR2_IDX],
      (uint32_t *)context->pInBlock[STR1_IDX],
      (uint32_t *)context->pInternalBlock[SCRATCH_DESCRIPTOR_MASK],
      (uint16_t *)context->pInternalBlock[SCRATCH_HAM_IDX],
      (uint16_t *)context->pInternalBlock[SCRATCH_SCATTER_OFST],
      (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
      context->kernelArgs.descriptorSize, context->kernelCtrlArgs.numDesc2PerIter,
      context->kernelArgs.mode, context->kernelArgs.descriptorPitch,
      0, context->pblock_vcop_featureMatching);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatching_gt_32_param_count());
    context->vcop_featureMatching_vloops = &vcop_featureMatching_gt_32_vloops;

    /* To update addresses of pSting2, pMinDist0 & pMinDist1 in the
       innermost loop */
    context->pblock_vcop_featureMatch_pblk_update = *pParamBlock;
    vcop_featureMatch_gt_32_pblk_update_init(
      (uint32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      16U*context->kernelArgs.descriptorPitch, 4U*16U,
      context->pblock_vcop_featureMatch_pblk_update);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_gt_32_pblk_update_param_count());
    context->vcop_featureMatch_pblk_update_vloops = &vcop_featureMatch_gt_32_pblk_update_vloops;

    /* To restore addresses of pSting2, pMinDist0 & pMinDist1 after the
       innermost loop and increment the startIdx by numDescriptors2 */
    context->pblock_vcop_featureMatch_pblk_reset = *pParamBlock;
    vcop_featureMatch_gt_32_pblk_reset_init(
      (int32_t*)(void *)context->pblock_vcop_featureMatching,
      (uint32_t*)(void *)context->pblock_vcop_findTwoBestMatches,
      context->kernelCtrlArgs.numDesc2PerIter,
      (context->loopCount2*context->kernelCtrlArgs.numDesc2PerIter) - 1U,
      (uint32_t)context->pInBlock[STR1_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
      (uint32_t)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
      context->pblock_vcop_featureMatch_pblk_reset);
    pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_featureMatch_gt_32_pblk_reset_param_count());
    context->vcop_featureMatch_pblk_reset_vloops = &vcop_featureMatch_gt_32_pblk_reset_vloops;
  }

  /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

  context->pblock_vcop_pickConfidentMatches = *pParamBlock;
  vcop_pickConfidentMatches_init(
    (uint16_t*)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
    (uint16_t*)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
    (uint16_t *)context->pOutBlock[OUT_IDX],
    context->kernelCtrlArgs.numDesc1PerIter,
    context->kernelCtrlArgs.minDistanceThres,
    context->kernelCtrlArgs.matchConfidence,
    context->pblock_vcop_pickConfidentMatches);
  pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_pickConfidentMatches_param_count());

  /* To take care of the case when numDescFullList2 is not a multiple
     of numDescriptors2*/
  context->pblock_vcop_twoBestMatches_update_n = *pParamBlock;
  vcop_twoBestMatches_update_n_init(
    (int16_t*)(void *)context->pblock_vcop_findTwoBestMatches,
    context->kernelCtrlArgs.numDescFullList2 -
    ((context->loopCount2 - 1U)*context->kernelCtrlArgs.numDesc2PerIter) - 1U,
    context->pblock_vcop_twoBestMatches_update_n);
  pParamBlock = (uint16_t (*)[])(*pParamBlock +  vcop_twoBestMatches_update_n_param_count());

  context->pblock_vcop_twoBestMatches_restore_n = *pParamBlock;
  vcop_twoBestMatches_update_n_init(
    (int16_t*)(void *)context->pblock_vcop_findTwoBestMatches,
    context->kernelCtrlArgs.numDesc2PerIter - 1U,
    context->pblock_vcop_twoBestMatches_restore_n);
#endif

  return status;
}

static BAM_Status BAM_featureMatching_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_featureMatching_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_featureMatching_Context *context = (BAM_featureMatching_Context *) kernelContext;
    BAM_featureMatching_CtlArgs *ctlArg= (BAM_featureMatching_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelCtrlArgs.numDescFullList1 = ctlArg->numDescFullList1;
    context->kernelCtrlArgs.numDescFullList2 = ctlArg->numDescFullList2;
    context->kernelCtrlArgs.minDistanceThres = ctlArg->minDistanceThres;
    context->kernelCtrlArgs.matchConfidence  = ctlArg->matchConfidence;

    /* Update actual number of descriptors in the two descriptor lists */
    context->kernelCtrlArgs.numDesc1PerIter = ctlArg->numDesc1PerIter;
    context->kernelCtrlArgs.numDesc2PerIter = ctlArg->numDesc2PerIter;

    if((ctlArg->numDesc1PerIter > context->kernelArgs.numDescriptors1) ||
       (ctlArg->numDesc2PerIter > context->kernelArgs.numDescriptors2)) {
      status = 1;
    }

    return status;
}

static BAM_Status Bam_featureMatching_computeFrame(void *kernelContext);

static BAM_Status Bam_featureMatching_computeFrame(void *kernelContext)
{
  BAM_featureMatching_Context *context = (BAM_featureMatching_Context *)kernelContext;
  uint16_t j, k;

  j = context->iter % context->loopCount2;

#if (!VCOP_HOST_EMULATION)
  if(j == 0) {
    vcop_featureMatch_initialize_vloops(context->pblock_vcop_featureMatch_initialize);
  }

  if(j == (context->loopCount2 - (uint16_t)1) ){
    vcop_twoBestMatches_update_n_vloops(context->pblock_vcop_twoBestMatches_update_n);
  }

  for(k = 0; k < context->innerLoopCount; k++) {
    context->vcop_featureMatching_vloops(context->pblock_vcop_featureMatching);
    vcop_findTwoBestMatches_vloops(context->pblock_vcop_findTwoBestMatches);
    context->vcop_featureMatch_pblk_update_vloops(context->pblock_vcop_featureMatch_pblk_update);
  }
  context->vcop_featureMatch_pblk_reset_vloops(context->pblock_vcop_featureMatch_pblk_reset);

  if(j == (context->loopCount2 - (uint16_t)1)) {
    vcop_pickConfidentMatches_vloops(context->pblock_vcop_pickConfidentMatches);
    vcop_twoBestMatches_update_n_vloops(context->pblock_vcop_twoBestMatches_restore_n);
  }
#else
  uint32_t numDesc2;
  numDesc2 = (j == context->loopCount2 - 1U) ? context->kernelCtrlArgs.numDescFullList2 -
             (context->loopCount2 - 1U)*context->kernelCtrlArgs.numDesc2PerIter :
             context->kernelCtrlArgs.numDesc2PerIter;

  if(j == 0) {
    context->startIdx = 0;
    vcop_featureMatch_initialize(
      (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
      (uint32_t*)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
      16U*((context->kernelCtrlArgs.numDesc1PerIter + 15U)/16U));
  }

  for(k = 0; k < context->innerLoopCount; k++) {
    if(context->kernelArgs.descriptorSize == 32U) {
      vcop_featureMatching_32((uint32_t *)context->pInBlock[STR2_IDX],
        (uint32_t *)((uint8_t *)context->pInBlock[STR1_IDX] +
        k*16U*context->kernelArgs.descriptorPitch),
        (uint8_t*)context->pInternalBlock[SCRATCH_HAM_IDX],
        (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
        context->kernelCtrlArgs.numDesc2PerIter, context->kernelArgs.mode,
        context->kernelArgs.descriptorPitch, context->startIdx);
    }
    else if(context->kernelArgs.descriptorSize < 32U) {
      vcop_featureMatching_lt_32((uint32_t *)context->pInBlock[STR2_IDX],
        (uint32_t *)((uint8_t *)context->pInBlock[STR1_IDX] +
        k*16U*context->kernelArgs.descriptorPitch),
        (uint32_t *)context->pInternalBlock[SCRATCH_DESCRIPTOR_MASK],
        (uint8_t*)context->pInternalBlock[SCRATCH_HAM_IDX],
        (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
        context->kernelCtrlArgs.numDesc2PerIter, context->kernelArgs.mode,
        context->kernelArgs.descriptorPitch, context->startIdx);
    }
    else {
      vcop_featureMatching_gt_32((uint32_t *)context->pInBlock[STR2_IDX],
        (uint32_t *)((uint8_t *)context->pInBlock[STR1_IDX] +
        k*16U*context->kernelArgs.descriptorPitch),
        (uint32_t *)context->pInternalBlock[SCRATCH_DESCRIPTOR_MASK],
        (uint16_t *)context->pInternalBlock[SCRATCH_HAM_IDX],
        (uint16_t *)context->pInternalBlock[SCRATCH_SCATTER_OFST],
        (uint16_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
        context->kernelArgs.descriptorSize, context->kernelCtrlArgs.numDesc2PerIter,
        context->kernelArgs.mode, context->kernelArgs.descriptorPitch,
        context->startIdx);
    }

    vcop_findTwoBestMatches((uint32_t *)context->pInternalBlock[SCRATCH_HAM_DIST_IDX],
      (uint32_t*)((uint8_t *)context->pInternalBlock[SCRATCH_MINDIST0_IDX] + k*16U*4U),
      (uint32_t*)((uint8_t *)context->pInternalBlock[SCRATCH_MINDIST1_IDX] + k*16U*4U),
      16U, numDesc2);
  }

  context->startIdx += context->kernelCtrlArgs.numDesc2PerIter;

  if(j == context->loopCount2 - 1U) {
    vcop_pickConfidentMatches(
      (uint16_t*)context->pInternalBlock[SCRATCH_MINDIST0_IDX],
      (uint16_t*)context->pInternalBlock[SCRATCH_MINDIST1_IDX],
      (uint16_t *)context->pOutBlock[OUT_IDX],
      context->kernelCtrlArgs.numDesc1PerIter,
      context->kernelCtrlArgs.minDistanceThres,
      context->kernelCtrlArgs.matchConfidence);
  }
#endif

  context->iter++;

  return 0;
}

BAM_KernelExecFuncDef gBAM_TI_featureMatchingExecFunc =
    {NULL, &Bam_featureMatching_initFrame, &Bam_featureMatching_computeFrame, NULL, &BAM_featureMatching_control, NULL};

