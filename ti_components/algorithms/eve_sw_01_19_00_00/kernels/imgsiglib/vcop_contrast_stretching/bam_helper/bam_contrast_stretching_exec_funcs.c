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
 *  @file       bam_contrast_stretching_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_contrast_stretching_int.h"
#include "bam_contrast_stretching.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_ContrastStretching_initFrame(void *kernelContext);
static BAM_Status Bam_ContrastStretching_control(void *kernelContext,
                                                        void * kernelCtlArg);

static BAM_Status Bam_ContrastStretching_initFrame(void *kernelContext)
{
  BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;

#if (!VCOP_HOST_EMULATION)
  vcop_contrast_stretching_init(
    context->pInBlock[BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT],
    context->pOutBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->kernelArgs.outPitch,
    context->kernelArgs.minVal,
    context->kernelArgs.scaleFactorQ16,
    context->pInternalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX]
  );
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_ContrastStretching_computeFrame(void *kernelContext)
{
    BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;

#if (!VCOP_HOST_EMULATION)
  vcop_contrast_stretching_vloops(context->pInternalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX]);
#else
  vcop_contrast_stretching(
    context->pInBlock[BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT],
    context->pOutBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->kernelArgs.outPitch,
    context->kernelArgs.minVal,
    context->kernelArgs.scaleFactorQ16);
#endif
    return 0;
}

#endif

static BAM_Status Bam_ContrastStretching_control(void *kernelContext,
                                                        void * kernelCtlArg)
{
  BAM_Status status = BAM_S_SUCCESS;

  BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;

  BAM_ContrastStretching_CtrlArgs * args = (BAM_ContrastStretching_CtrlArgs *)kernelCtlArg;

  context->kernelArgs.minVal          = args->minVal;
  context->kernelArgs.scaleFactorQ16  = args->scaleFactorQ16;

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_contrastStretchingExecFunc =
#if (!VCOP_HOST_EMULATION)
{
  NULL,
  &Bam_ContrastStretching_initFrame,
  NULL,
  NULL,
  &Bam_ContrastStretching_control,
  &vcop_contrast_stretching_vloops
};
#else
{
  NULL,
  &Bam_ContrastStretching_initFrame,
  &Bam_ContrastStretching_computeFrame,
  NULL,
  &Bam_ContrastStretching_control,
  NULL
};

#endif

