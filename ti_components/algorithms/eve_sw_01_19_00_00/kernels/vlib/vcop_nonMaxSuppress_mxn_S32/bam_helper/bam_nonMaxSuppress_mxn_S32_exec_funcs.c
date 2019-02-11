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
 *  @file       bam_nonMaxSuppress_mxn_S32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nonMaxSuppress_mxn_S32_int.h"
#include "bam_nonMaxSuppress_mxn_S32.h"
#include "vcop_nonMaxSuppress_mxn_32s_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S32_initFrame(void *kernelContext);
static BAM_Status BAM_nonMaxSuppress_mxn_S32_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_nonMaxSuppress_mxn_S32_control(void *kernelContext, void *kernelCtlArg){

    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_NonMaxSuppress_mxn_S32_CtlArgs *ctlArg= (BAM_NonMaxSuppress_mxn_S32_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_NONMAXSUPPRESS_MxN_S32_CMD_SET_THRESHOLD){
        context->kernelArgs.threshold= ctlArg->threshold;
    }
    else if (ctlArg->ctlCmdId== BAM_NONMAXSUPPRESS_MxN_S32_CMD_GET_THRESHOLD){
        ctlArg->threshold= context->kernelArgs.threshold;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status BAM_nonMaxSuppress_mxn_S32_initFrame(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)

    if ( context->kernelArgs.outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP)
    {
      vcop_nonMaxSuppress_mxn_32s_init
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold,
          (uint16_t*)context->pInternalBlock[PARAMS_IDX]
      );
    }
    else
    {
      vcop_nonMaxSuppress_mxn_32s_bitPack_init
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold,
          (uint16_t*)context->pInternalBlock[PARAMS_IDX]
      );
    }
#endif
    return status;
}
#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_nonMaxSuppress_mxn_S32_compute(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_Status status = 0;
    if ( context->kernelArgs.outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP)
    {
      vcop_nonMaxSuppress_mxn_32s
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold);
    }
    else
    {
      vcop_nonMaxSuppress_mxn_32s_bitPack
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold);
    }

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, NULL, NULL, &BAM_nonMaxSuppress_mxn_S32_control, &vcop_nonMaxSuppress_mxn_32s_vloops };
#else
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, &BAM_nonMaxSuppress_mxn_S32_compute, NULL, &BAM_nonMaxSuppress_mxn_S32_control, NULL };
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_binPack_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, NULL, NULL, &BAM_nonMaxSuppress_mxn_S32_control, &vcop_nonMaxSuppress_mxn_32s_bitPack_vloops };
#else
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, &BAM_nonMaxSuppress_mxn_S32_compute, NULL, &BAM_nonMaxSuppress_mxn_S32_control, NULL };
#endif

