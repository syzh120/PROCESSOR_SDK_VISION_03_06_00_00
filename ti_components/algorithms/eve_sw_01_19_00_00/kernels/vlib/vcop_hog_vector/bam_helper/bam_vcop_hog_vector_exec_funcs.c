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
 *  @file       bam_vcop_hog_vector_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hog vector compute kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vcop_hog_vector_int.h"
#include "bam_vcop_hog_vector.h"
#include "vcop_hog_vector_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_sliding_2x2_sum_initFrame(void *kernelContext);
static BAM_Status BAM_sliding_2x2_sum_compute(void *kernelContext);

static BAM_Status Bam_sliding_2x2_sum_initFrame(void *kernelContext)
{
    BAM_sliding_2x2_sum_Context *context = (BAM_sliding_2x2_sum_Context *) kernelContext;
    BAM_Status status = 0;
    if(context->kernelArgs.sun2x2outFormat >= EVE_VLIB_SLIDING_2x2_SUM_MAX)
    {
      status = BAM_E_FAIL;
    }
    else 
    {
#if !(VCOP_HOST_EMULATION)
    if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED)
    {
      vcop_ti_pd_2x2_sum_init((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                              (uint16_t*)context->pOutBlock[OUT_IDX2],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride,
                                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_ti_pd_2x2_sum_vloops;
    }
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* Currently sun2x2outFormat will not be grater than EVE_VLIB_SLIDING_2x2_SUM_PLANAR, hence code is unreachable but  */
    /* as the implementation of the function changes, it will not be unreachable.   */
    /* UNREACH.GEN or INVARIANT_CONDITION.UNREACH */
    else if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_PLANAR)
    {
      vcop_ti_pd_2x2_sum_planar_init((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride,
                                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_ti_pd_2x2_sum_planar_vloops;
    }
    else
    {
      status = BAM_E_FAIL;
   }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1      */
#endif
   }
    return status;
}

static BAM_Status BAM_sliding_2x2_sum_compute(void *kernelContext)
{
    BAM_sliding_2x2_sum_Context *context = (BAM_sliding_2x2_sum_Context *) kernelContext;
    BAM_Status status = 0;
#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED)
    {
      vcop_ti_pd_2x2_sum((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                              (uint16_t*)context->pOutBlock[OUT_IDX2],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride);
    }
    else if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_PLANAR)
    {
      vcop_ti_pd_2x2_sum_planar((uint16_t*)context->pInBlock[IN_IDX],
                                (uint16_t*)context->pOutBlock[OUT_IDX1],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride);
    }
#else
    context->kernelCustom((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif
    return status;

}

BAM_KernelExecFuncDef gBAM_TI_sliding2x2SumExecFunc =
{ NULL, &Bam_sliding_2x2_sum_initFrame, &BAM_sliding_2x2_sum_compute, NULL, NULL, NULL};
