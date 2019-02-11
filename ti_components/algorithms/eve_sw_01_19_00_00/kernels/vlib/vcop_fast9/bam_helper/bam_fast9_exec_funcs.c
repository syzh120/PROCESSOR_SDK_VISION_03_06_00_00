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
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_fast9_int.h"
#include "bam_fast9.h"
#include "vcop_fast9_kernel.h"

/* Function Prototypes */
static BAM_Status Bam_Fast9_initFrame(void *kernelContext);

static BAM_Status Bam_Fast9_initFrame(void *kernelContext)
{
    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    vcop_fast9_init((uint8_t *)context->pInBlock[FAST9_IN_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT0_PTR_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT1_PTR_IDX],
                    (uint16_t *)context->pInternalBlock[FAST9_SCRATCH_OUT4_PTR_IDX],
                    (uint8_t *)context->pOutBlock[FAST9_OUT_IDX],
                    context->kernelArgs.threshold,
                    context->kernelArgs.pitch,
                    context->kernelArgs.in_w,
                    context->kernelArgs.in_h,
                    context->pInternalBlock[FAST9_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Fast9_compute(void *kernelContext);

static BAM_Status Bam_Fast9_compute(void *kernelContext)
{
    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_fast9((uint8_t *)context->pInBlock[FAST9_IN_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT0_PTR_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT1_PTR_IDX],
                    (uint16_t *)context->pInternalBlock[FAST9_SCRATCH_OUT4_PTR_IDX],
                    (uint8_t *)context->pOutBlock[FAST9_OUT_IDX],
                    context->kernelArgs.threshold,
                    context->kernelArgs.pitch,
                    context->kernelArgs.in_w,
                    context->kernelArgs.in_h);

    return status;
}
#endif

static BAM_Status Bam_Fast9_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status Bam_Fast9_control(void *kernelContext, void *kernelCtlArg){

    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Fast9_ctrlArgs *ctlArg= (BAM_Fast9_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.threshold  = ctlArg->threshold;
    context->kernelArgs.pitch      = ctlArg->pitch;
    context->kernelArgs.in_w       = ctlArg->in_w;
    context->kernelArgs.in_h       = ctlArg->in_h;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_fast9ExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL, &Bam_Fast9_initFrame, NULL, NULL, &Bam_Fast9_control, &vcop_fast9_vloops };
#else
    { NULL, &Bam_Fast9_initFrame, &Bam_Fast9_compute, NULL, &Bam_Fast9_control, NULL };
#endif

