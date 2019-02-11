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
 *  @file       bam_canny_non_maximum_suppression_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Canny NMS
 *               kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_canny_non_maximum_suppression_int.h"
#include "bam_canny_non_maximum_suppression.h"
#include "vcop_canny_non_maximum_suppression_kernel.h" /* compiler should take care of include path */



/***********************************************************************************************/
/*                        Below are the helper  functions related to Canny NMS kernels                                */
/***********************************************************************************************/
static BAM_Status Bam_CannyNonMaximumSuppression_initFrame(void *kernelContext);
static BAM_Status Bam_CannyNonMaximumSuppression_computeFrame(void *kernelContext);

static BAM_Status Bam_CannyNonMaximumSuppression_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_CannyNonMaximumSuppression_initFrame(void *kernelContext)
{
  BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;

#if (!VCOP_HOST_EMULATION)
  context->pBlockIndexBinning = (uint16_t *)context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_PARAMS_IDX];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockMaxCases     =  context->pBlockIndexBinning + vcop_canny_bin_indexing_param_count();
  context->pBlockDoubleThresholding = context->pBlockMaxCases + vcop_canny_nms_max_cases_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  vcop_canny_bin_indexing_init(
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT],
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->kernelCtrlArgs.computeWidth + 2U,
    context->kernelCtrlArgs.computeHeight + 2U,
    context->kernelCtrlArgs.inBlockPitch,
    context->pBlockIndexBinning );

  vcop_canny_nms_max_cases_init(
      context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
      context->kernelCtrlArgs.computeWidth,
      context->kernelCtrlArgs.computeHeight,
      context->kernelCtrlArgs.inBlockPitch,
      context->pBlockMaxCases);

  vcop_canny_nms_double_thresholding_init(
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
    context->pOutBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT],
    context->kernelCtrlArgs.lowThreshold,
    context->kernelCtrlArgs.highThreshold,
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inBlockPitch,
    context->kernelCtrlArgs.outBlockPitch,
    context->pBlockDoubleThresholding);

#endif
    return status;
}


static BAM_Status Bam_CannyNonMaximumSuppression_computeFrame(void *kernelContext)
{
    BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
   vcop_canny_bin_indexing(
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT],
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->kernelCtrlArgs.computeWidth + 2U,
    context->kernelCtrlArgs.computeHeight + 2U,
    context->kernelCtrlArgs.inBlockPitch);

  vcop_canny_nms_max_cases(
      context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
      context->kernelCtrlArgs.computeWidth,
      context->kernelCtrlArgs.computeHeight,
      context->kernelCtrlArgs.inBlockPitch);

  vcop_canny_nms_double_thresholding(
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
    context->pOutBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT],
    context->kernelCtrlArgs.lowThreshold,
    context->kernelCtrlArgs.highThreshold,
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inBlockPitch,
    context->kernelCtrlArgs.outBlockPitch);
#else
    /* Param block update to update the radius and current number of edge points */
    vcop_canny_bin_indexing_vloops(context->pBlockIndexBinning);
    vcop_canny_nms_max_cases_vloops(context->pBlockMaxCases);
    vcop_canny_nms_double_thresholding_vloops(context->pBlockDoubleThresholding);

#endif

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_CannyNonMaximumSuppression_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *) kernelContext;

  BAM_CannyNonMaximumSuppression_CtrlArgs * ctrlArgs = (BAM_CannyNonMaximumSuppression_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_cannyNonMaximumSuppressionExecFunc =
{
  NULL,
  &Bam_CannyNonMaximumSuppression_initFrame,
  &Bam_CannyNonMaximumSuppression_computeFrame,
  NULL,
  &Bam_CannyNonMaximumSuppression_control,
  NULL
};


