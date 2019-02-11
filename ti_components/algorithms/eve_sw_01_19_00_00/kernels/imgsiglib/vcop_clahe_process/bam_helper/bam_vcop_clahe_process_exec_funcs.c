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
*  @file       bam_vcop_clahe_process_exec_funcs.c
*
*  @brief      This file defines interfaces for integrating clahe interpolate kernel
*              into BAM
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vcop_clahe_process_int.h"
#include "vcop_clahe_process_kernel.h"

static BAM_Status BAM_claheInterpolate_compute(void *kernelContext);
static BAM_Status BAM_claheInterpolate_initFrame(void *kernelContext);

static BAM_Status BAM_claheInterpolate_initFrame(void *kernelContext)
{
  BAM_claheInterpolate_Context *context = (BAM_claheInterpolate_Context *) kernelContext;
  BAM_Status status = 0;
  uint16_t (*wgtPtr_0)[];
  uint16_t (*wgtPtr_1)[];

  uint16_t i, txf,tyf;

  wgtPtr_0 = (uint16_t (*)[])context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0];
  wgtPtr_1 = (uint16_t (*)[])context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1];
  for(i = 0; i < context->kernelArgs.blockWidth; i++)
  {
    txf = (i + context->kernelArgs.blockWidth);
    txf = (uint16_t)(((uint32_t)txf * 0xFFFFU)  / ((uint32_t)context->kernelArgs.blockWidth << 1U));
    (*wgtPtr_0)[2U*i] = (uint16_t)((uint16_t)0xFFFFU - txf);
    (*wgtPtr_0)[(2U*i)+1U] = txf;

    txf = (i);
    txf = (uint16_t)(((uint32_t)txf * 0xFFFFU) / ((uint32_t)context->kernelArgs.blockWidth << 1U));
    (*wgtPtr_1)[2U*i] = (uint16_t)((uint16_t)0xFFFFU - txf);
    (*wgtPtr_1)[(2U*i)+1U] = txf;

  }
  wgtPtr_0 = (uint16_t (*)[])context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0];
  wgtPtr_1 = (uint16_t (*)[])context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1];
  for(i = 0; i < context->kernelArgs.blockHeight; i++)
  {
    tyf = (i + context->kernelArgs.blockHeight);
    tyf = (uint16_t)(((uint32_t)tyf * 0xFFFFU) / ((uint32_t)context->kernelArgs.blockHeight <<1U));
    (*wgtPtr_0)[2U*i] = (uint16_t)((uint16_t)0xFFFFU - tyf);
    (*wgtPtr_0)[(2U*i)+1U] = tyf;

    tyf = (i);
    tyf = (uint16_t)(((uint32_t)tyf * 0xFFFFU) / ((uint32_t)context->kernelArgs.blockHeight <<1U));
    (*wgtPtr_1)[2U*i] = (uint16_t)((uint16_t)0xFFFFU - tyf);
    (*wgtPtr_1)[(2U*i)+1U] = tyf;
  }
#if (!VCOP_HOST_EMULATION)
  clahe_make_8way_look_up_kernel_init((uint32_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_LUT_PORT],
    (uint32_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    256U,
    context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_0]);

  clahe_look_up_and_interpolate_kernel_init((uint8_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_DATA_PORT],
    (uint8_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0],
    (uint8_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES],
    (uint8_t *)context->pOutBlock[CLAHE_INTERP_OUT_IDX],
    context->kernelArgs.blockWidth,
    context->kernelArgs.blockHeight,
    context->kernelArgs.inBlockPitch,
    256U*8U,4U,
    ((uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1]));
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* We have a limitation BAM for number of memmory recors that can be used. This
    BAM node crosses the limit. To handle this case we are combinung multiple
    pointers a one memory record and using pointer arithmetic get each pointers later*/
  clahe_look_up_and_interpolate_kernel_init((uint8_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_DATA_PORT],
    (uint8_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0],
    (uint8_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES],
    (uint8_t *)context->pOutBlock[CLAHE_INTERP_OUT_IDX],
    context->kernelArgs.blockWidth,
    context->kernelArgs.blockHeight,
    context->kernelArgs.inBlockPitch,
    256U*8U,4U,
    ((uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1]) + clahe_look_up_and_interpolate_kernel_param_count());
  clahe_look_up_and_interpolate_kernel_init((uint8_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_DATA_PORT],
    (uint8_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1],
    (uint8_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES],
    (uint8_t *)context->pOutBlock[CLAHE_INTERP_OUT_IDX],
    context->kernelArgs.blockWidth,
    context->kernelArgs.blockHeight,
    context->kernelArgs.inBlockPitch,
    256U*8U,4U,
    ((uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1])+ (2U*clahe_look_up_and_interpolate_kernel_param_count()));
  clahe_look_up_and_interpolate_kernel_init((uint8_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_DATA_PORT],
    (uint8_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1],
    (uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1],
    (uint8_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES],
    (uint8_t *)context->pOutBlock[CLAHE_INTERP_OUT_IDX],
    context->kernelArgs.blockWidth,
    context->kernelArgs.blockHeight,
    context->kernelArgs.inBlockPitch,
    256U*8U,4U,
    ((uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1])+ (3U*clahe_look_up_and_interpolate_kernel_param_count()));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

#endif
  context->subTileIdx = 0;

  return status;
}

static BAM_Status BAM_claheInterpolate_compute(void *kernelContext)
{
  BAM_claheInterpolate_Context *context = (BAM_claheInterpolate_Context *) kernelContext;
  BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
  uint16_t * xWgtPtr;
  uint16_t * yWgtPtr;

  if(context->subTileIdx == 3)
  {
    xWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1];
    yWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1];
  }
  else if(context->subTileIdx == 2)
  {
    xWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0];
    yWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1];
  }
  else if(context->subTileIdx == 1)
  {
    xWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1];
    yWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0];
  }
  else
  {
    xWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0];
    yWgtPtr = (uint16_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0];
  }

  clahe_make_8way_look_up_kernel((uint32_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_LUT_PORT],
    (uint32_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    256);

  clahe_look_up_and_interpolate_kernel((uint32_t*)context->pInBlock[BAM_CLAHE_INTERP_INPUT_DATA_PORT],
    (uint32_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX],
    (uint16_t*)xWgtPtr,
    (uint16_t*)yWgtPtr,
    (uint8_t *)context->pInternalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES],
    (uint8_t *)context->pOutBlock[CLAHE_INTERP_OUT_IDX],
    context->kernelArgs.blockWidth,
    context->kernelArgs.blockHeight,
    context->kernelArgs.inBlockPitch,
    256*8,4);

#else
  clahe_make_8way_look_up_kernel_vloops(context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_0]);
  clahe_look_up_and_interpolate_kernel_vloops((((uint16_t*)context->pInternalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1])+ (context->subTileIdx*clahe_look_up_and_interpolate_kernel_param_count())));
#endif
  context->subTileIdx++;
  if(context->subTileIdx == 4)
  {
    context->subTileIdx = 0;
  }

  return status;
}




BAM_KernelExecFuncDef gBAM_TI_claheInterpolateExecFunc =
{
  NULL,
  &BAM_claheInterpolate_initFrame,
  &BAM_claheInterpolate_compute,
  NULL,
  NULL,
  NULL
};



