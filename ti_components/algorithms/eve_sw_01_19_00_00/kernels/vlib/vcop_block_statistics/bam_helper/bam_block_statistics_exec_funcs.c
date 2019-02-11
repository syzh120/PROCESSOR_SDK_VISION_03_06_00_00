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
 *  @file       bam_block_statistics_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block statistics
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_block_statistics_int.h"
#include "bam_block_statistics.h"
#include "vcop_block_statistics_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Block_Statistics_initFrame(void *kernelContext);

static BAM_Status Bam_Block_Statistics_initFrame(void *kernelContext)
{
    BAM_Block_Statistics_Context *context = (BAM_Block_Statistics_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied */
    if(( (context->kernelArgs.blockWidth/context->kernelArgs.statBlockWidth) > 8U) ||
        ( (context->kernelArgs.blockHeight/context->kernelArgs.statBlockHeight) > 8U) ||
        ( (context->kernelArgs.statBlockHeight*context->kernelArgs.statBlockWidth) > 256U)) {
        status = 1;
    }
#if !(VCOP_HOST_EMULATION)
    if(status == 0) {
        vcop_block_statistics_init((uint8_t*)context->pInBlock[IN_IDX],
                               context->kernelArgs.blockStride,
                               context->kernelArgs.blockWidth,
                               context->kernelArgs.blockHeight,
                               context->kernelArgs.statBlockWidth,
                               context->kernelArgs.statBlockHeight,
                               (uint8_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX],
                               (uint16_t*)context->pInternalBlock[SCRATCH_SUM_IDX],
                               (uint32_t*)context->pInternalBlock[SCRATCH_SUMSQ_B_IDX],
                               (uint32_t*)(*((uint32_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*9U)),
                               (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*18U)),
                               (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*18U) + 1U),
                               (uint8_t*)context->pOutBlock[OUT_MIN_IDX],
                               (uint8_t*)context->pOutBlock[OUT_MAX_IDX],
                               (uint16_t*)context->pOutBlock[OUT_MEAN_IDX],
                               (uint32_t*)context->pOutBlock[OUT_VAR_IDX],
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Block_Statistics_compute(void *kernelContext)
{
    BAM_Block_Statistics_Context *context = (BAM_Block_Statistics_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_block_statistics((uint8_t*)context->pInBlock[IN_IDX],
                               context->kernelArgs.blockStride,
                               context->kernelArgs.blockWidth,
                               context->kernelArgs.blockHeight,
                               context->kernelArgs.statBlockWidth,
                               context->kernelArgs.statBlockHeight,
                               (uint8_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX],
                               (uint16_t*)context->pInternalBlock[SCRATCH_SUM_IDX],
                               (uint32_t*)context->pInternalBlock[SCRATCH_SUMSQ_B_IDX],
                               (uint32_t*)((uint32_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*9U),
                               (uint16_t*)((uint16_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*18U),
                               (uint16_t*)((uint16_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*18U + 1U),
                               (uint8_t*)context->pOutBlock[OUT_MIN_IDX],
                               (uint8_t*)context->pOutBlock[OUT_MAX_IDX],
                               (uint16_t*)context->pOutBlock[OUT_MEAN_IDX],
                               (uint32_t*)context->pOutBlock[OUT_VAR_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_blockStatisticsExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &Bam_Block_Statistics_initFrame, NULL, NULL, NULL, &vcop_block_statistics_vloops };
#else
{ NULL, &Bam_Block_Statistics_initFrame, &Bam_Block_Statistics_compute, NULL, NULL, NULL };
#endif
