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
 *  @file       bam_remap_bilinear_interpolateUV_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_remap_bilinear_interpolateUV_int.h"
#include "bam_remap_bilinear_interpolateUV.h"
#include "vcop_bilinearInterpolateUV.h"
#include "vcop_memcpy.h"
#include "remap_common.h"

#define BLOCK_MAP_16_BITS (0U)

/* Function Prototypes */
static BAM_Status Bam_RemapBilinearinterpolateUV_initFrame(void *kernelContext);

static BAM_Status Bam_RemapBilinearinterpolateUV_initFrame(void *kernelContext)
{
    BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION)
    uint8_t *actualLutPtr = (uint8_t *)((*(uint8_t (*)[])context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_LUT_IDX]) +
                                 sizeof(convertMapBlockInfo));

#if !BLOCK_MAP_16_BITS
    uint8_t *actualfracPtr = (uint8_t *)((*(uint8_t (*)[])((void *)actualLutPtr)) +
                              (2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight));
#endif

   if(context->kernelArgs.ctrlArgs.byPassInput == 0)
   {
    vcop_bilinearInterpolateUV_init((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)(void *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_INDATA_LUT],
                    context->kernelArgs.mnQShift,
                    context->kernelArgs.oQShift,
                    context->kernelArgs.qScale,
                    context->kernelArgs.mult,
                    context->kernelArgs.rightShift,
                    context->kernelArgs.sat_high,
                    context->kernelArgs.sat_high_set,
                    context->kernelArgs.sat_low,
                    context->kernelArgs.sat_low_set,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);
       context->kernelCustom = &vcop_bilinearInterpolateUV_vloops;
  }
   else
   {
     vcop_memcpy2d_init((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth*2U,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);

      context->kernelCustom = &vcop_memcpy2d_vloops;
   }
#endif

    return status;
}

static BAM_Status Bam_RemapBilinearinterpolateUV_compute(void *kernelContext);

static BAM_Status Bam_RemapBilinearinterpolateUV_compute(void *kernelContext)
{
    BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
    BAM_Status status = 0;
#if (VCOP_HOST_EMULATION)
    uint8_t * actualLutPtr = (uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_LUT_IDX] +
                                 sizeof(convertMapBlockInfo);
#if !BLOCK_MAP_16_BITS
   uint8_t * actualfracPtr = actualLutPtr +  2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight;
#endif

   if(context->kernelArgs.ctrlArgs.byPassInput == 0)
   {
    vcop_bilinearInterpolateUV((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_INDATA_LUT],
                    context->kernelArgs.mnQShift,
                    context->kernelArgs.oQShift,
                    context->kernelArgs.qScale,
                    context->kernelArgs.mult,
                    context->kernelArgs.rightShift,
                    context->kernelArgs.sat_high,
                    context->kernelArgs.sat_high_set,
                    context->kernelArgs.sat_low,
                    context->kernelArgs.sat_low_set);
   }
   else
   {
     vcop_memcpy2d((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth*2U,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride);
   }
#else
    context->kernelCustom(context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);

#endif
    return status;
}

static BAM_Status Bam_RemapBilinearinterpolateUV_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_RemapBilinearinterpolateUV_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
  BAM_RemapBilinearinterpolateUV_ctrlArgs *args   = (BAM_RemapBilinearinterpolateUV_ctrlArgs *) ctlArg;
  context->kernelArgs.ctrlArgs = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_remapBilinearinterpolateUVExecFunc =
    { NULL, &Bam_RemapBilinearinterpolateUV_initFrame, &Bam_RemapBilinearinterpolateUV_compute, NULL, &Bam_RemapBilinearinterpolateUV_control, NULL };

