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
 *  @file       bam_tensor_matrix_7x7_s16_grad_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for kernel that computes
 *              tensor matrix using the 7x7 patch window of signed gradient input into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_tensor_matrix_7x7_s16_grad_int.h"
#include "bam_tensor_matrix_7x7_s16_grad.h"
#include "vcop_tensor_matrix_7x7_s16_grad_kernel.h" /* compiler should take care of include path */
#include "vcop_tensor_matrix_7x7_s16_grad_cn.h"


/* Function Prototypes */
static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_initFrame(void *kernelContext);

static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_initFrame(void *kernelContext)
{
    BAM_Tensor_Matrix_7x7_S16_Grad_Context *context = (BAM_Tensor_Matrix_7x7_S16_Grad_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied*/
    if(((context->kernelArgs.n) < 1) || ((context->kernelArgs.stride) < 1)) {
        status = 1;
    }

    if(status == 0) {
      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      vcop_tensor_matrix_7x7_s16_grad_init((int16_t *)context->pInBlock[IN_IDX1],
                               (int16_t *)context->pInBlock[IN_IDX2],
                               context->kernelArgs.stride,
                               context->kernelArgs.n,
                               (int32_t *)context->pOutBlock[OUT_IDX1],
                               (int32_t *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n,
                               (int32_t *)context->pOutBlock[OUT_IDX1] + (context->kernelArgs.n*2),
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX1],
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX2],
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX3],
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame(void *kernelContext);

static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame(void *kernelContext)
{
    BAM_Tensor_Matrix_7x7_S16_Grad_Context *context = (BAM_Tensor_Matrix_7x7_S16_Grad_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_tensor_matrix_7x7_s16_grad_cn((int16_t *)context->pInBlock[IN_IDX1],
                           (int16_t *)context->pInBlock[IN_IDX2],
                           context->kernelArgs.stride,
                           context->kernelArgs.n,
                           (int *)context->pOutBlock[OUT_IDX1],
                           (int *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n,
                           (int *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n*2);

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_tensorMatrix7x7S16GradExecFunc =
#ifdef NATC
    { NULL, &Bam_Tensor_Matrix_7x7_S16_Grad_initFrame, &Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Tensor_Matrix_7x7_S16_Grad_initFrame, NULL, NULL, NULL, &vcop_tensor_matrix_7x7_s16_grad_vloops };
#endif
