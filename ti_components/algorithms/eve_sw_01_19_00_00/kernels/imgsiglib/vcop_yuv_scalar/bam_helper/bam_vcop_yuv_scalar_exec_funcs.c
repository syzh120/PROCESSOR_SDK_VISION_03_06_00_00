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
*  @file       bam_vcop_yuv_scalar_exec_funcs.cc
*
*  @brief      This file defines interfaces for integrating YUV Scalar
*              into BAM
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_yuv_scalar_int.h"
#include "bam_yuv_scalar.h"
#include "vcop_yuv_scalar_kernel.h"
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */
#define ALIGN_SIZE(x,y) ((((x) + ((y)-1U)) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

static BAM_Status BAM_YUV_Scalar_compute(void *kernelContext);
static BAM_Status BAM_YUV_Scalar_control(void *kernelContext, void *ctlArg);
static BAM_Status BAM_YUV_Scalar_initFrame(void *kernelContext);

static BAM_Status BAM_YUV_Scalar_initFrame(void *kernelContext)
{
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  uint32_t i;
  BAM_Status status = 0;
  uint16_t transposeBlkWidth    = ALIGN_SIZE((uint16_t)context->ctrlArgs.dstBlockHeight,(uint16_t)4);

  uint16_t (*offsetPtr)[8] ;
  if((transposeBlkWidth % 8U) == 0)
  {
    transposeBlkWidth += 4U;
  }
  context->transposeBlkWidth = transposeBlkWidth;
  offsetPtr = (uint16_t (*)[8])(void*)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX];
  for(i = 0; i < 8U; i++)
  {
    (*offsetPtr)[i] = (uint16_t)i*context->transposeBlkWidth;
  }

#if (!VCOP_HOST_EMULATION)
         yuv_scalar_pixels_look_up_kernel_init((uint32_t*)context->pInBlock[YUV_SCALAR_IN_IDX],
                                              (uint16_t*)context->pInBlock[YUV_SCALAR_INDEX_IDX],
                                              (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                              context->kernelArgs.numTaps,
                                              context->ctrlArgs.srcBlockPitch,
                                              context->ctrlArgs.dstBlockHeight,
                                              context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0]);

        yuv_scalar_interpolation_kernel_init((uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                        (uint8_t*)context->pInBlock[YUV_SCALAR_FRAC_IDX],
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                        (uint16_t *)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX],
                                        context->transposeBlkWidth,
                                        context->kernelArgs.fracBits,
                                        context->kernelArgs.numTaps,
                                        context->ctrlArgs.srcBlockWidth,
                                        context->ctrlArgs.srcBlockPitch,
                                        context->ctrlArgs.dstBlockHeight,
                                        context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1]);

        if(context->ctrlArgs.inputDataType == 0)
        {
          yuv_scalar_luma_copy_kernel_init((uint32_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX],
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                    context->transposeBlkWidth,
                                    context->ctrlArgs.srcBlockWidth,
                                    context->ctrlArgs.dstBlockHeight,
                                    context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);
            /* CHECK_MISRA("-11.1")  -> Disable rule 11.1     */
            /* This is auto generated fucntion by VCOP compiler tool */
          context->scalarCopyKenel = &yuv_scalar_luma_copy_kernel_vloops;
            /* RESET_MISRA("11.1")  -> Reset rule 11.1     */
        }
        else
        {
          yuv_scalar_chroma_copy_kernel_init((uint8_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX],
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                    context->transposeBlkWidth,
                                    context->ctrlArgs.srcBlockWidth,
                                    context->ctrlArgs.dstBlockHeight,
                                    context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);
            /* CHECK_MISRA("-11.1")  -> Disable rule 11.1     */
            /* This is auto generated fucntion by VCOP compiler tool */
          context->scalarCopyKenel = &yuv_scalar_chroma_copy_kernel_vloops;
            /* RESET_MISRA("11.1")  -> Reset rule 11.     */
        }
#endif

  return status;
}

static BAM_Status BAM_YUV_Scalar_compute(void *kernelContext)
{
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
        yuv_scalar_pixels_look_up_kernel((uint32_t*)context->pInBlock[YUV_SCALAR_IN_IDX],
                                              (uint16_t*)context->pInBlock[YUV_SCALAR_INDEX_IDX],
                                              (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                              context->kernelArgs.numTaps,
                                              context->ctrlArgs.srcBlockPitch,
                                              context->ctrlArgs.dstBlockHeight);

        yuv_scalar_interpolation_kernel((uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                        (uint8_t*)context->pInBlock[YUV_SCALAR_FRAC_IDX],
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                        (uint16_t *)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX],
                                        context->transposeBlkWidth,
                                        context->kernelArgs.fracBits,
                                        context->kernelArgs.numTaps,
                                        context->ctrlArgs.srcBlockWidth,
                                        context->ctrlArgs.srcBlockPitch,
                                        context->ctrlArgs.dstBlockHeight);

        if(context->ctrlArgs.inputDataType == 0)
        {
          yuv_scalar_luma_copy_kernel((uint32_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX],
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                    context->transposeBlkWidth,
                                    context->ctrlArgs.srcBlockWidth,
                                    context->ctrlArgs.dstBlockHeight);
        }
        else
        {
          yuv_scalar_chroma_copy_kernel((uint8_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX],
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX],
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX],
                                    context->transposeBlkWidth,
                                    context->ctrlArgs.srcBlockWidth,
                                    context->ctrlArgs.dstBlockHeight);
        }
#else
        yuv_scalar_pixels_look_up_kernel_vloops(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0]);
        yuv_scalar_interpolation_kernel_vloops(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1]);
        context->scalarCopyKenel(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);

#endif

  return status;
}


static BAM_Status BAM_YUV_Scalar_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  BAM_yuv_scalar_Ctrl_Args *args  = (BAM_yuv_scalar_Ctrl_Args *) ctlArg;
  context->ctrlArgs = *args;
  return status;
}


BAM_KernelExecFuncDef gBAM_TI_yuvScalarExecFunc =
{
  NULL,
  &BAM_YUV_Scalar_initFrame,
  &BAM_YUV_Scalar_compute,
  NULL,
  &BAM_YUV_Scalar_control,
  NULL
};



