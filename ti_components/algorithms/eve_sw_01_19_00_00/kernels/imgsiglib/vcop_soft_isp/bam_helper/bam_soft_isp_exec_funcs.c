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
 *              Image Signal Processor (ISP) into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_soft_isp_int.h"
#include "bam_soft_isp.h"
#include "vcop_soft_isp_kernel.h" /* compiler should take care of include path */

#define SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE (MAX((SOFT_ISP_MAX_INBUF_SIZE), (SOFT_ISP_MAX_TEMP_RC_SIZE)))
#define SOFT_ISP_MAX_BLACK_CLAMP_OUT_CC_SIZE (MAX((SOFT_ISP_MAX_INBUF_SIZE), (SOFT_ISP_MAX_TEMP_CC_SIZE)))


static BAM_Status Bam_SoftIsp_initFrame(void *kernelContext);

static BAM_Status Bam_SoftIsp_initFrame(void *kernelContext)
{
  BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    BAM_SoftIsp_Context *context = (BAM_SoftIsp_Context *) kernelContext;
    uint16_t (*sum_c1)[SOFT_ISP_MAX_SCRATCH_C_SIZE], *sum_c2, *med, *low, *ov, *oh;
    uint16_t (*high)[SOFT_ISP_MAX_SCRATCH_A_SIZE];
    uint8_t (*edge_flag)[SOFT_ISP_MAX_SCRATCH_B_SIZE], *strip_flag, *c1_flag, *c2_flag, *flag_vert, *flag_horz;
    uint8_t start_x = 0, offset_cc = 0;
    uint32_t outWidth, outHeight, outStride, bufSize;
    uint32_t i, p2;
    uint8_t bitShift;
    uint16_t bufStride;

    uint16_t (*pDecompandOut_rc)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE], *pDecompandOut_cc;
    uint16_t (*pBlackClampOut_rc)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE], (*pBlackClampOut_cc)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_CC_SIZE];
    uint8_t  *pScratchOut_rc, *pScratchOut_cc;
    uint16_t (*pParamBlock)[SOFT_ISP_MAX_PARAMS_SIZE];

    outStride = 16U*((context->kernelArgs.blockWidth + 15U)/16U);
    outWidth  = context->kernelArgs.blockWidth - 4U;
    outHeight = context->kernelArgs.blockHeight - 4U;

    i = 0;

    bufSize = (((outWidth/2U)*(outHeight/2U)) + EXTRA_PIXELS(outWidth/2U, outWidth/2U, 8U));

    switch(context->kernelArgs.rPosition) {
      case 1:
        start_x = 2U;
        offset_cc = 0;
        break;

      case 2:
        start_x = 3U;
        offset_cc = 0;
        break;

      case 3:
        start_x = 2U;
        offset_cc = 1U;
        break;

      case 4:
        start_x = 3U;
        offset_cc = 1U;
        break;

      default:
        break;
    }

    high       = (uint16_t (*)[SOFT_ISP_MAX_SCRATCH_A_SIZE])context->pInternalBlock[SCRATCH_A];
    flag_horz  = (uint8_t *)(void *)(*high + bufSize);

    edge_flag  = (uint8_t (*)[SOFT_ISP_MAX_SCRATCH_B_SIZE])context->pInternalBlock[SCRATCH_B];
    strip_flag = *edge_flag +    bufSize;
    c1_flag    = *edge_flag + (2U*bufSize);
    c2_flag    = *edge_flag + (3U*bufSize);

    sum_c1     = (uint16_t (*)[SOFT_ISP_MAX_SCRATCH_C_SIZE])context->pInternalBlock[SCRATCH_C];
    sum_c2     = *sum_c1 +    bufSize;
    med        = *sum_c1 + (2U*bufSize);
    low        = *sum_c1 + (3U*bufSize);
    ov         = *sum_c1 + (4U*bufSize);
    oh         = *sum_c1 + (5U*bufSize);
    flag_vert  = (uint8_t *)(void *)(*sum_c1 + (6U*bufSize));

    pParamBlock = (uint16_t (*)[SOFT_ISP_MAX_PARAMS_SIZE])context->pInternalBlock[PARAMS_IDX];

    if(context->kernelArgs.enableDecompand == 1U) {
      pDecompandOut_rc  = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE])context->pInternalBlock[TEMP_RC_IDX];
      pDecompandOut_cc  = (uint16_t*)context->pInternalBlock[TEMP_CC_IDX];
      pBlackClampOut_rc = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE])context->pInBlock[IN_RC_IDX];
      pBlackClampOut_cc = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_CC_SIZE])context->pInBlock[IN_CC_IDX];
      pScratchOut_rc    = (uint8_t *)context->pInternalBlock[TEMP_CC_IDX];
      pScratchOut_cc    = (uint8_t *)context->pInternalBlock[TEMP_RC_IDX];
      bufStride         = (uint16_t )outStride;

      p2 = context->kernelArgs.p1 + ((context->kernelArgs.pk - context->kernelArgs.p1)*context->kernelArgs.r1);

      context->funcs_exec[i] = &vcop_decompand_piecewise_linear_vloops;
      context->ptr_params[i] = *pParamBlock;
      pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_decompand_piecewise_linear_param_count());

      vcop_decompand_piecewise_linear_init((uint16_t*)context->pInBlock[IN_RC_IDX],
          (uint16_t*)context->pInBlock[IN_CC_IDX], *pDecompandOut_rc, pDecompandOut_cc,
          context->kernelArgs.blockWidth, context->kernelArgs.blockHeight,
          context->kernelArgs.blockStride, (uint16_t)outStride, context->kernelArgs.p1, p2, context->kernelArgs.pk,
          context->kernelArgs.r1, context->kernelArgs.r1r2, context->kernelArgs.sensorBitDepth - 16U,
          context->ptr_params[i]);
      i++;
    }
    else {
      pDecompandOut_rc  = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE])context->pInBlock[IN_RC_IDX];
      pDecompandOut_cc  = (uint16_t*)context->pInBlock[IN_CC_IDX];
      pBlackClampOut_rc = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_RC_SIZE])context->pInternalBlock[TEMP_RC_IDX];
      pBlackClampOut_cc = (uint16_t (*)[SOFT_ISP_MAX_BLACK_CLAMP_OUT_CC_SIZE])context->pInternalBlock[TEMP_CC_IDX];
      pScratchOut_rc    = (uint8_t *)context->pInBlock[IN_CC_IDX];
      pScratchOut_cc    = (uint8_t *)context->pInBlock[IN_RC_IDX];
      bufStride         = context->kernelArgs.blockStride;
    }

    /* Black Clamp and C Balance */
    context->funcs_exec[i] = &vcop_black_clamp_c_balance_vloops;
    context->ptr_params[i] = *pParamBlock;
    pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_black_clamp_c_balance_param_count());

    vcop_black_clamp_c_balance_init((uint16_t*)*pDecompandOut_rc, (uint16_t*)pDecompandOut_cc,
        (uint16_t*)*pBlackClampOut_rc, *pBlackClampOut_cc,
        context->kernelArgs.blockWidth, context->kernelArgs.blockHeight, bufStride,
        (uint16_t )outStride, context->kernelArgs.blackClamp, context->kernelArgs.cBalanceGain,
        context->kernelArgs.cBalanceShift, context->ptr_params[i]);
    i++;

    /* Extract R pixels */
    if(context->kernelArgs.enableExtractR == 1U) {

      if(context->kernelArgs.enableDecompand == 1U) {
        bitShift = 8U;
      }
      else {
        bitShift = context->kernelArgs.sensorBitDepth - (uint8_t)8;
      }

      context->funcs_exec[i] = &vcop_soft_isp_extract_r_vloops;
      context->ptr_params[i] = *pParamBlock;
      pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_soft_isp_extract_r_param_count());

      vcop_soft_isp_extract_r_init((*pDecompandOut_rc + outStride + start_x),
          (uint8_t*)context->pOutBlock[OUT_R_IDX], context->kernelArgs.blockWidth - 4U,
          context->kernelArgs.blockHeight - 4U, (uint16_t)outStride, bitShift, context->ptr_params[i]);
      i++;
    }

    /* Statistics Collection */
    if(context->kernelArgs.enableStats == 1U) {
      context->funcs_exec[i] = &vcop_stats_collector_dense_vloops;
      context->ptr_params[i] = *pParamBlock;
      pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_stats_collector_dense_param_count());

      vcop_stats_collector_dense_init((*pBlackClampOut_rc + outStride + 2U),
          (*pBlackClampOut_cc + outStride + 2U),
          (uint32_t *)context->pInternalBlock[SCRATCH_C],
          (uint32_t *)context->pOutBlock[OUT_STATS_IDX],
          *(uint16_t (*)[])context->pOutBlock[OUT_STATS_IDX] + 16U,
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U,
          (uint16_t)outStride, 0, context->kernelArgs.saturationLimit, context->ptr_params[i]);
      i++;
    }

    /* CFA Interpolation */
    context->funcs_exec[i] = &vcop_rccc_to_cccc_vloops;
    context->ptr_params[i] = *pParamBlock;
    pParamBlock = (uint16_t (*)[])(*pParamBlock + vcop_rccc_to_cccc_param_count());

    vcop_rccc_to_cccc_init(*pBlackClampOut_rc, *pBlackClampOut_cc,
        context->kernelArgs.blockWidth, context->kernelArgs.blockHeight, (uint16_t)outStride, *sum_c1, sum_c2,
        med, low, *high, *edge_flag, strip_flag, c1_flag, c2_flag, ov, oh, flag_vert, flag_horz,
        start_x, offset_cc, context->ptr_params[i]);
    i++;

    /* Applying GBCE tone curve */
    if(context->kernelArgs.enableDecompand == 1U) {
      bitShift = 4U;
    }
    else {
      bitShift = (context->kernelArgs.sensorBitDepth > 12U) ? (context->kernelArgs.sensorBitDepth - 12U): 0;
    }
    context->ptr_params[i] = *pParamBlock;

    if(context->kernelArgs.gbceMethod == 0) {
      context->funcs_exec[i] = &vcop_gbce_simple_vloops;

      vcop_gbce_simple_init((*pBlackClampOut_rc + outStride + 2U),
          (*pBlackClampOut_cc + outStride + 2U),
          (uint8_t*)context->pOutBlock[OUT_RC_IDX], (uint8_t*)context->pOutBlock[OUT_CC_IDX],
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U, (uint16_t)outStride, bitShift,
          (uint8_t*)context->pInternalBlock[GBCE_TC_IDX], context->ptr_params[i]);
    }
    else {
      context->funcs_exec[i] = &vcop_gbce_interp_vloops;

      vcop_gbce_interp_init((*pBlackClampOut_rc + outStride + 2U),
          (*pBlackClampOut_cc + outStride + 2U),
          (uint8_t*)pScratchOut_rc, (uint8_t*)pScratchOut_cc,
          (uint8_t*)context->pOutBlock[OUT_RC_IDX], (uint8_t*)context->pOutBlock[OUT_CC_IDX],
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U, (uint16_t)outStride, bitShift,
          ((uint16_t)((uint16_t)1 << bitShift) - 1U), (uint8_t*)context->pInternalBlock[GBCE_TC_IDX],
          context->ptr_params[i]);
    }
    i++;

    context->num_funcs_exec = i;
#endif

    return status;
}


static BAM_Status BAM_SoftIsp_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_SoftIsp_control(void *kernelContext, void *kernelCtlArg){

    BAM_SoftIsp_Context *context = (BAM_SoftIsp_Context *) kernelContext;
    BAM_SoftIsp_CtlArgs *ctlArg= (BAM_SoftIsp_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.rPosition = ctlArg->rPosition;
    context->kernelArgs.sensorBitDepth = ctlArg->sensorBitDepth;
    context->kernelArgs.enableDecompand = ctlArg->enableDecompand;
    context->kernelArgs.p1 = ctlArg->p1;
    context->kernelArgs.pk = ctlArg->pk;
    context->kernelArgs.r1 = ctlArg->r1;
    context->kernelArgs.r1r2 = ctlArg->r1r2;
    context->kernelArgs.blackClamp = ctlArg->blackClamp;
    context->kernelArgs.cBalanceGain = ctlArg->cBalanceGain;
    context->kernelArgs.cBalanceShift = ctlArg->cBalanceShift;
    context->kernelArgs.enableExtractR = ctlArg->enableExtractR;
    context->kernelArgs.gbceMethod = ctlArg->gbceMethod;
    context->kernelArgs.gbceToneCurveAddr = ctlArg->gbceToneCurveAddr;
    context->kernelArgs.enableStats = ctlArg->enableStats;
    context->kernelArgs.saturationLimit = ctlArg->saturationLimit;

    return status;
}


static BAM_Status Bam_SoftIsp_computeFrame(void *kernelContext);

static BAM_Status Bam_SoftIsp_computeFrame(void *kernelContext)
{
    BAM_SoftIsp_Context *context = (BAM_SoftIsp_Context *) kernelContext;

#if (!VCOP_HOST_EMULATION)
    uint32_t i;

    for (i=0;i<context->num_funcs_exec; i++) {
        context->funcs_exec[i](context->ptr_params[i]);
    }
#else
    uint16_t *sum_c1, *sum_c2, *med, *low, *high, *ov, *oh;
    uint8_t *edge_flag, *strip_flag, *c1_flag, *c2_flag, *flag_vert, *flag_horz;
    uint32_t outWidth, outHeight, outStride, bufSize;
    uint8_t start_x, offset_cc, bitShift;
    uint16_t bufStride;
    uint32_t p2;

    uint16_t *pDecompandOut_rc, *pDecompandOut_cc;
    uint16_t *pBlackClampOut_rc, *pBlackClampOut_cc;
    uint8_t  *pScratchOut_rc, *pScratchOut_cc;

    outStride = 16U*((context->kernelArgs.blockWidth + 15U)/16U);
    outWidth  = context->kernelArgs.blockWidth - 4U;
    outHeight = context->kernelArgs.blockHeight - 4U;

    bufSize = ((outWidth/2U)*(outHeight/2U) + EXTRA_PIXELS(outWidth/2U, outWidth/2U, 8U));

    switch(context->kernelArgs.rPosition) {
      case 1:
        start_x = 2U;
        offset_cc = 0;
        break;

      case 2:
        start_x = 3U;
        offset_cc = 0;
        break;

      case 3:
        start_x = 2U;
        offset_cc = 1U;
        break;

      case 4:
        start_x = 3U;
        offset_cc = 1U;
        break;
    }

    high       = (uint16_t *)context->pInternalBlock[SCRATCH_A];
    flag_horz  = (uint8_t *)(high + bufSize);

    edge_flag  = (uint8_t *)context->pInternalBlock[SCRATCH_B];
    strip_flag = edge_flag + bufSize;
    c1_flag    = strip_flag + bufSize;
    c2_flag    = c1_flag + bufSize;

    sum_c1     = (uint16_t *)context->pInternalBlock[SCRATCH_C];
    sum_c2     = sum_c1 + bufSize;
    med        = sum_c2 + bufSize;
    low        = med + bufSize;
    ov         = low + bufSize;
    oh         = ov + bufSize;
    flag_vert  = (uint8_t *)(oh + bufSize);

    if(context->kernelArgs.enableDecompand == 1U) {
      pDecompandOut_rc  = (uint16_t*)context->pInternalBlock[TEMP_RC_IDX];
      pDecompandOut_cc  = (uint16_t*)context->pInternalBlock[TEMP_CC_IDX];
      pBlackClampOut_rc = (uint16_t*)context->pInBlock[IN_RC_IDX];
      pBlackClampOut_cc = (uint16_t*)context->pInBlock[IN_CC_IDX];
      pScratchOut_rc    = (uint8_t *)context->pInternalBlock[TEMP_CC_IDX];
      pScratchOut_cc    = (uint8_t *)context->pInternalBlock[TEMP_RC_IDX];
      bufStride         = outStride;

      p2 = context->kernelArgs.p1 + (context->kernelArgs.pk - context->kernelArgs.p1)*context->kernelArgs.r1;

      vcop_decompand_piecewise_linear((uint16_t*)context->pInBlock[IN_RC_IDX],
          (uint16_t*)context->pInBlock[IN_CC_IDX], pDecompandOut_rc, pDecompandOut_cc,
          context->kernelArgs.blockWidth, context->kernelArgs.blockHeight,
          context->kernelArgs.blockStride, outStride, context->kernelArgs.p1, p2, context->kernelArgs.pk,
          context->kernelArgs.r1, context->kernelArgs.r1r2, context->kernelArgs.sensorBitDepth - 16U);
    }
    else {
      pDecompandOut_rc  = (uint16_t*)context->pInBlock[IN_RC_IDX];
      pDecompandOut_cc  = (uint16_t*)context->pInBlock[IN_CC_IDX];
      pBlackClampOut_rc = (uint16_t*)context->pInternalBlock[TEMP_RC_IDX];
      pBlackClampOut_cc = (uint16_t*)context->pInternalBlock[TEMP_CC_IDX];
      pScratchOut_rc    = (uint8_t *)context->pInBlock[IN_CC_IDX];
      pScratchOut_cc    = (uint8_t *)context->pInBlock[IN_RC_IDX];
      bufStride         = context->kernelArgs.blockStride;
    }

    vcop_black_clamp_c_balance((uint16_t*)pDecompandOut_rc, (uint16_t*)pDecompandOut_cc,
        (uint16_t*)pBlackClampOut_rc, (uint16_t*)pBlackClampOut_cc,
        context->kernelArgs.blockWidth, context->kernelArgs.blockHeight, bufStride,
        outStride, context->kernelArgs.blackClamp, context->kernelArgs.cBalanceGain,
        context->kernelArgs.cBalanceShift);

    /* Extract R pixels */
    if(context->kernelArgs.enableExtractR == 1U) {
      if(context->kernelArgs.enableDecompand == 1U) {
        bitShift = 8U;
      }
      else {
        bitShift = context->kernelArgs.sensorBitDepth - 8U;
      }

      vcop_soft_isp_extract_r((uint16_t*)pDecompandOut_rc + outStride + start_x,
          (uint8_t*)context->pOutBlock[OUT_R_IDX], context->kernelArgs.blockWidth - 4U,
          context->kernelArgs.blockHeight - 4U, outStride, bitShift);
    }

    /* Statistics Collection */
    if(context->kernelArgs.enableStats == 1U) {
      vcop_stats_collector_dense((uint16_t *)pBlackClampOut_rc + outStride + 2U,
          (uint16_t *)pBlackClampOut_cc + outStride + 2U,
          (uint32_t *)context->pInternalBlock[SCRATCH_C],
          (uint32_t *)context->pOutBlock[OUT_STATS_IDX],
          (uint16_t *)context->pOutBlock[OUT_STATS_IDX] + 16U,
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U,
          outStride, 0, context->kernelArgs.saturationLimit);
    }

    vcop_rccc_to_cccc((uint16_t*)pBlackClampOut_rc, (uint16_t*)pBlackClampOut_cc,
        context->kernelArgs.blockWidth, context->kernelArgs.blockHeight, outStride, sum_c1, sum_c2,
        med, low, high, edge_flag, strip_flag, c1_flag, c2_flag, ov, oh, flag_vert, flag_horz,
        start_x, offset_cc);

    if(context->kernelArgs.enableDecompand == 1U) {
      bitShift = 4U;
    }
    else {
      bitShift = (context->kernelArgs.sensorBitDepth > 12U) ? (context->kernelArgs.sensorBitDepth - 12U): 0;
    }

    if(context->kernelArgs.gbceMethod == 0) {
      vcop_gbce_simple((uint16_t*)pBlackClampOut_rc + outStride + 2U,
          (uint16_t*)pBlackClampOut_cc + outStride + 2U,
          (uint8_t*)context->pOutBlock[OUT_RC_IDX], (uint8_t*)context->pOutBlock[OUT_CC_IDX],
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U, outStride, bitShift,
          (uint8_t*)context->pInternalBlock[GBCE_TC_IDX]);
    }
    else {
      vcop_gbce_interp((uint16_t*)pBlackClampOut_rc + outStride + 2U,
          (uint16_t*)pBlackClampOut_cc + outStride + 2U,
          (uint8_t*)pScratchOut_rc, (uint8_t*)pScratchOut_cc,
          (uint8_t*)context->pOutBlock[OUT_RC_IDX], (uint8_t*)context->pOutBlock[OUT_CC_IDX],
          context->kernelArgs.blockWidth - 4U, context->kernelArgs.blockHeight - 4U, outStride, bitShift,
          ((1U << bitShift) - 1U), (uint8_t*)context->pInternalBlock[GBCE_TC_IDX]);
    }
#endif

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_softIspExecFunc =
    { NULL, &Bam_SoftIsp_initFrame, &Bam_SoftIsp_computeFrame, NULL, &BAM_SoftIsp_control, NULL };

