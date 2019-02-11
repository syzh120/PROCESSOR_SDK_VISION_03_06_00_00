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
 *  @file       bam_fast9_score_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 score
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_fast9_score_int.h"
#include "bam_fast9_score.h"
#include "vcop_fast9_score_kernel.h" /* compiler should take care of include path */
#include "edma_utils_memcpy.h"

/* Function Prototypes */

static BAM_Status Bam_Fast9_Score_initInstance(void *kernelContext);
static BAM_Status Bam_Fast9_Score_initFrame(void *kernelContext);
static BAM_Status Bam_Fast9_Score_compute(void *kernelContext);

static BAM_Status Bam_Fast9_Score_initInstance(void *kernelContext)
{
  BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
  /* Take back up of output pointer as it gets incremented by kernel and we need to reset across ivision process */
  context->pOutBlockBase_OUT_SCORE_IDX = context->pOutBlock[OUT_SCORE_IDX];
  return 0;
}

static BAM_Status Bam_Fast9_Score_initFrame(void *kernelContext)
{
    BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
    BAM_Status status = 0;
    SCORE_INTERNAL_MEMORY_IBUFHA * internalIbufha = (SCORE_INTERNAL_MEMORY_IBUFHA *)context->pInternalBlock[SCORE_INTERNAL_IBUFHA_IDX];

if (context->kernelArgs.score_method)
    {
        EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX],
                            (const void *)LUT_EXT_IDX_SAD,
                            (uint16_t)sizeof(LUT_EXT_IDX_SAD),
                            1U,
                            0,
                            0);
    }
else
    {
        EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX],
                            (const void *)LUT_EXT_IDX_THR,
                            (uint16_t)sizeof(LUT_EXT_IDX_THR),
                            1U,
                            0,
                            0);
    }
    /* Since the kernel is updating the pointer during execute - need to reset at Frame Init */
    context->pOutBlock[OUT_SCORE_IDX] = context->pOutBlockBase_OUT_SCORE_IDX ;


#if (!VCOP_HOST_EMULATION)
if(context->kernelArgs.score_method)
    {
        vcop_fast9_score_kernel_init((uint32_t*)context->pInBlock[IN_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                              (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                              context->kernelArgs.num_features,
                              context->kernelArgs.thr,
                              (uint8_t*)context->pInternalBlock[LUT_IDX],
                              (uint8_t*)internalIbufha->offset_out,
                              (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                              (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                              (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                              (uint32_t*)context->pInternalBlock[PARAMS_IDX],
                              (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
else
    {
        vcop_fast9_thresh_score_init((uint32_t*)context->pInBlock[IN_IDX],
                                    (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                                    (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                                    (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                                    context->kernelArgs.num_features,
                                    context->kernelArgs.thr,
                                    (uint8_t*)context->pInternalBlock[LUT_IDX],
                                    (uint8_t*)internalIbufha->offset_out,
                                    (uint8_t*)context->pInternalBlock[BSCORE_IDX],
                                    (uint8_t*)internalIbufha->Dscore,
                                    (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                                    (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                                    (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                                    (uint32_t*)context->pInternalBlock[PARAMS_IDX],
                                    (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
#endif

    return status;
}

static BAM_Status Bam_Fast9_Score_compute(void *kernelContext)
{
    BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
    BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
    uint16_t *pUpdate;
    SCORE_INTERNAL_MEMORY_IBUFHA * internalIbufha = (SCORE_INTERNAL_MEMORY_IBUFHA *)context->pInternalBlock[SCORE_INTERNAL_IBUFHA_IDX];

if(context->kernelArgs.score_method)
    {
        vcop_fast9_score_kernel((uint32_t*)context->pInBlock[IN_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                              (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                              context->kernelArgs.num_features,
                              context->kernelArgs.thr,
                              (uint8_t*)context->pInternalBlock[LUT_IDX],
                              (uint8_t*)internalIbufha->offset_out,
                              (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                              (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                              (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                              NULL);

         pUpdate = (uint16_t *)(context->pOutBlock[OUT_SCORE_IDX])+((context->kernelArgs.num_features));

         context->pOutBlock[OUT_SCORE_IDX] = pUpdate;
    }
else
    {
         vcop_fast9_thresh_score((uint32_t*)context->pInBlock[IN_IDX],
                                 (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                                 (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                                 (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                                 context->kernelArgs.num_features,
                                 context->kernelArgs.thr,
                                 (uint8_t*)context->pInternalBlock[LUT_IDX],
                                 (uint8_t*)internalIbufha->offset_out,
                                 (uint8_t*)context->pInternalBlock[BSCORE_IDX],
                                 (uint8_t*)internalIbufha->Dscore,
                                 (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                                 (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                                 (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                                 NULL);

         pUpdate = (uint16_t *)(context->pOutBlock[OUT_SCORE_IDX])+((context->kernelArgs.num_features));

         context->pOutBlock[OUT_SCORE_IDX] = pUpdate;
    }
#else
    if(context->kernelArgs.score_method) {
        vcop_fast9_score_kernel_vloops(context->pInternalBlock[PARAMS_IDX]);
    }
    else {
        vcop_fast9_thresh_score_vloops(context->pInternalBlock[PARAMS_IDX]);
    }
#endif
    return status;
}

BAM_KernelExecFuncDef gBAM_TI_fast9scoreExecFunc =
    { &Bam_Fast9_Score_initInstance, &Bam_Fast9_Score_initFrame, &Bam_Fast9_Score_compute, NULL, NULL, NULL };

