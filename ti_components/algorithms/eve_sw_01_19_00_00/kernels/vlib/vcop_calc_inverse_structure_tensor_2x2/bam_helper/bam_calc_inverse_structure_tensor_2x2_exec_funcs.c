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
 *  @file       bam_calc_inverse_structure_tensor_2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for kernel that computes
 *              inverse of the 2x2 structure tensor into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_calc_inverse_structure_tensor_2x2_int.h"
#include "bam_calc_inverse_structure_tensor_2x2.h"
#include "vcop_calc_inverse_structure_tensor_2x2_kernel.h" /* compiler should take care of include path */
#include "vcop_calc_inverse_structure_tensor_2x2_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame(void *kernelContext);
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame(void *kernelContext)
{
    BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t qFormatePel = ((uint16_t)VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);

    /* Return error if assumptions in kernel are not satisfied*/
    if(((context->kernelArgs.numKeyPoints) < 1) || ((context->kernelArgs.inputStride) < 1) ||
      ((context->kernelArgs.outputStride) < 1) || ((context->kernelArgs.inputStride) < (context->kernelArgs.numKeyPoints)) ||
      ((context->kernelArgs.outputStride) < (2*context->kernelArgs.numKeyPoints))) {
        status = 1;
    }

    if(status == 0) {
        vcop_calc_inverse_structure_tensor_2x2_init((int32_t*)context->pInBlock[IN_IDX1],
                               (uint16_t*)context->pInBlock[IN_IDX2],
                               (uint32_t*)context->pInBlock[IN_IDX3],
                                (int16_t*)context->pOutBlock[OUT_IDX1],
                               (int32_t*)context->pInternalBlock[SCRATCH_IDX1],
                               (uint32_t*)context->pInternalBlock[SCRATCH_IDX2],
                               context->kernelArgs.inputStride,
                               context->kernelArgs.outputStride,
                               qFormatePel,
                               context->kernelArgs.numKeyPoints,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame(void *kernelContext);

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame(void *kernelContext)
{
    BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t qFormatePel = ((uint16_t)VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);

    vcop_calc_inverse_structure_tensor_2x2_cn((int*)context->pInBlock[IN_IDX1],
                           (uint16_t*)context->pInBlock[IN_IDX2],
                           (uint32_t*)context->pInBlock[IN_IDX3],
                            (int16_t*)context->pOutBlock[OUT_IDX1],
                           context->kernelArgs.inputStride,
                           context->kernelArgs.outputStride,
                           qFormatePel,
                           context->kernelArgs.numKeyPoints);

    return status;
}
#endif

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
  BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args *args  = (BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args *) ctlArg;
  context->kernelArgs.ctrlPtr = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_calcInverseStructureTensor2x2ExecFunc =
#ifdef NATC
    { NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame, &Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame, NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_control, NULL };
#else
    { NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame, NULL, NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_control, &vcop_calc_inverse_structure_tensor_2x2_vloops };
#endif
