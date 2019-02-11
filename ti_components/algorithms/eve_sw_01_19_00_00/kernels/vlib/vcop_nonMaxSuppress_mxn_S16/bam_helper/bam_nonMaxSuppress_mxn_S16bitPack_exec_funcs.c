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
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nonMaxSuppress_mxn_S16bitPack_int.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"
#include "vcop_nonMaxSuppress_mxn_16s_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_initFrame(void *kernelContext);
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_control(void *kernelContext, void *kernelCtlArg){

    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs *ctlArg= (BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->ctrlArgs = *ctlArg;


    return status;
}

static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_initFrame(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_nonMaxSuppress_mxn_16sbitPack_init
    (
        (int16_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT],
        (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2],
        context->ctrlArgs.computeWidth +  (context->ctrlArgs.winW - (uint16_t)1U),
        context->ctrlArgs.computeHeight + (context->ctrlArgs.winH - (uint16_t)1U),
        context->ctrlArgs.inStride,
        context->ctrlArgs.outStride / (uint16_t)8U,
        context->ctrlArgs.winW,
        context->ctrlArgs.winH,
        (int16_t)context->ctrlArgs.threshold,
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX]
    );
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_compute(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_Status status = 0;
    vcop_nonMaxSuppress_mxn_16sbitPack
    (
        (int16_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT],
        (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2],
        context->ctrlArgs.computeWidth + (context->ctrlArgs.winW - 1U),
        context->ctrlArgs.computeHeight + (context->ctrlArgs.winH - 1U),
        context->ctrlArgs.inStride,
        context->ctrlArgs.outStride / 8U,
        context->ctrlArgs.winW,
        context->ctrlArgs.winH,
        context->ctrlArgs.threshold
    );

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_initFrame,
  NULL,
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_control,
  &vcop_nonMaxSuppress_mxn_16sbitPack_vloops };
#else
{
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_initFrame,
  &BAM_nonMaxSuppress_mxn_S16bitPack_compute,
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_control,
  NULL };
#endif

