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
*  @file       bam_vcop_clahe_gen_lut_exec_funcs.c
*
*  @brief      This file defines interfaces for integrating clahe LUT generartion kernel
*              into BAM
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vcop_clahe_gen_lut_int.h"
#include "vcop_clahe_generate_lut_kernel.h"

static BAM_Status BAM_gen_lut_compute(void *kernelContext);
static BAM_Status BAM_gen_lut_initFrame(void *kernelContext);
static uint16_t* pBlock_1;
#define VCOP_CLAHE_CLIP_DIST_OFFSET (12)
#define VCOP_CLAHE_RESIDUAL_OFFSET (19)
#define VCOP_CLAHE_ENABLE_RES_OFFSET (4)
static BAM_Status BAM_gen_lut_control(void *kernelContext, void *ctlArg);

static BAM_Status BAM_gen_lut_initFrame(void *kernelContext)
{
  BAM_gen_lut_Context *context = (BAM_gen_lut_Context *) kernelContext;
  BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* We have a limitation BAM for number of memmory recors that can be used. This
    BAM node crosses the limit. To handle this case we are combinung multiple
    pointers a one memory record and using pointer arithmetic get each pointers later*/

      pBlock_1 = (uint16_t*)(void*)(((uint8_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_0]) + 
      ((((2U *  vcop_clahe_memset_param_count()) + 31U) /32U)*32U));

    vcop_clahe_memset_init(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX],
      0, 
      4U*256U*8U,
      (uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_0]);

    vcop_clahe_histogram_8c_word_init(
      (uint8_t*)context->pInBlock[BAM_CLAHE_GENLUT_INPUT_DATA_PORT],
      context->kernelArgs.blockWidth,
      context->kernelArgs.blockHeight,
      context->kernelArgs.inBlockPitch,
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX],
      pBlock_1);

    vcop_clahe_histogram_8c_word_sum_init(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_HIST_TEMP_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX],
      (uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_1]);


    vcop_clahe_clip_hist_init(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_WBUF_SCARCTH],
      (((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_3])  + VCOP_CLAHE_RESIDUAL_OFFSET),
      (((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_3])  + VCOP_CLAHE_CLIP_DIST_OFFSET),
      (((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_3])  + VCOP_CLAHE_ENABLE_RES_OFFSET),
      256U,
      context->ctrlArgs.clipValue,
      (uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_2]);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

    vcop_clahe_generate_lut_init(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX],
      (uint8_t*)context->pOutBlock[CLAHE_GENLUT_OUT_IDX],
      context->ctrlArgs.lutScale,
      256U,
      0,
      0,
      0,
      (uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_3]);

#endif
  context->subTileIdx = 0;

  return status;
}

static BAM_Status BAM_gen_lut_compute(void *kernelContext)
{
  BAM_gen_lut_Context *context = (BAM_gen_lut_Context *) kernelContext;
  BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
  uint32_t VclipDist;
  uint32_t VclipResidual;
  uint16_t ebaleResidual;

    if(context->subTileIdx == 0)
    {
      vcop_clahe_memset(
        (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX],
        0, 
        4*256*8);
    }


    vcop_clahe_histogram_8c_word(
      (uint32_t*)context->pInBlock[BAM_CLAHE_GENLUT_INPUT_DATA_PORT],
      context->kernelArgs.blockWidth,
      context->kernelArgs.blockHeight,
      context->kernelArgs.inBlockPitch,
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX]);


    if(context->subTileIdx == 3)
    {
    vcop_clahe_histogram_8c_word_sum(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_8_WAY_HIST_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_HIST_TEMP_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX]);

    vcop_clahe_clip_hist(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX],
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_WBUF_SCARCTH],
      &VclipResidual,
      &VclipDist,
      &ebaleResidual,
      256,
      context->ctrlArgs.clipValue);
      VclipResidual++;

    vcop_clahe_generate_lut(
      (uint32_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_1_WAY_HIST_IDX],
      (uint32_t*)context->pOutBlock[CLAHE_GENLUT_OUT_IDX],
      context->ctrlArgs.lutScale,
      256,
      VclipDist,
      VclipResidual,
      ebaleResidual);
    }

#else
    if(context->subTileIdx == 0)
    {
      vcop_clahe_memset_vloops((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_0]);
    }

    vcop_clahe_histogram_8c_word_vloops((uint16_t*)pBlock_1);

    if(context->subTileIdx == 3)
    {
    vcop_clahe_histogram_8c_word_sum_vloops((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_1]);
    vcop_clahe_clip_hist_vloops((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_2]);
    vcop_clahe_generate_lut_vloops((uint16_t*)context->pInternalBlock[CLAHE_GENLUT_INTERNAL_PARAMS_IDX_3]);
    }
  
#endif
  context->subTileIdx++;
 if(context->subTileIdx == 4)
  {
    context->subTileIdx = 0;
  }
 return status;
}

static BAM_Status BAM_gen_lut_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_gen_lut_Context *context = (BAM_gen_lut_Context *) kernelContext;
  BAM_gen_lut_Ctrl_Args *args  = (BAM_gen_lut_Ctrl_Args *) ctlArg;
  context->ctrlArgs = *args;
  return status;
}
BAM_KernelExecFuncDef gBAM_TI_gen_lutExecFunc =
{ 
  NULL,
  &BAM_gen_lut_initFrame,
  &BAM_gen_lut_compute,
  NULL,
  &BAM_gen_lut_control,
  NULL 
};



