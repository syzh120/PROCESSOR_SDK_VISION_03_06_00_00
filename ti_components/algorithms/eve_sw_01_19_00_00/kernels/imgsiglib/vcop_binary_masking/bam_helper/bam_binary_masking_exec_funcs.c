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
 *  @file       bam_binary_masking_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary Masking
 *              kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_binary_masking_int.h"
#include "bam_binary_masking.h"
#include "vcop_binary_masking_kernel.h" /* compiler should take care of include path */




/***********************************************************************************************/
/*                        Below are the helper  functions related to Sobel X kernel                                */
/***********************************************************************************************/
static BAM_Status Bam_BinaryMasking_initFrame(void *kernelContext);

static BAM_Status Bam_BinaryMasking_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_BinaryMasking_initFrame(void *kernelContext)
{
  BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;


#if !VCOP_HOST_EMULATION
  vcop_binary_masking_init(
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT],
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT],
    context->pOutBlock[BAM_BINARY_MASKING_OUTPUT_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputByteDataPitch,
    context->kernelCtrlArgs.inputBitDataPitch,
    context->kernelCtrlArgs.outputPitch,
    context->pInternalBlock[BINARY_MASKING_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_BinaryMasking_computeFrame(void *kernelContext)
{
    BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *)kernelContext;

    vcop_binary_masking(
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT],
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT],
    context->pOutBlock[BAM_BINARY_MASKING_OUTPUT_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputByteDataPitch,
    context->kernelCtrlArgs.inputBitDataPitch,
    context->kernelCtrlArgs.outputPitch);

  return BAM_S_SUCCESS;
}
#endif

static BAM_Status Bam_BinaryMasking_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *) kernelContext;

  BAM_BinaryMasking_CtrlArgs * ctrlArgs = (BAM_BinaryMasking_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  if ( ( ctrlArgs->computeWidth * ctrlArgs->computeHeight )  <= (context->kernelInitArgs.maxBlockWidth * context->kernelInitArgs.maxBlockHeight) )
  {
    context->kernelCtrlArgs = *ctrlArgs;
  }
  else
  {
    status = BAM_E_FAIL;
  }

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_binaryMaskingExecFunc =
{
#if !VCOP_HOST_EMULATION
  NULL,
  &Bam_BinaryMasking_initFrame,
  NULL,
  NULL,
  &Bam_BinaryMasking_control,
  &vcop_binary_masking_vloops
#else
  NULL,
  &Bam_BinaryMasking_initFrame,
  &Bam_BinaryMasking_computeFrame,
  NULL,
  &Bam_BinaryMasking_control,
  NULL
#endif
};

