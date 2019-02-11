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
 *  @file       bam_vcop_yuv420_fir2d_separable.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 separable filter
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>

#include "bam_yuv420_fir2d_separable_int.h"
#include "bam_yuv420_fir2d_separable.h"
#include "vcop_yuv420_fir2d_separable_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Yuv420_fir2dseparable_Y_initFrame(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_Y_initFrame(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
           (*context->kernelArgs.coefPtr),
           context->kernelArgs.coefWidth);

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
           &(*context->kernelArgs.coefPtr)[context->kernelArgs.coefWidth],
           context->kernelArgs.coefHeight);

#if (!VCOP_HOST_EMULATION)
    vcop_yuv420_fir2d_separable_y_init((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits,
                    context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_Yuv420_fir2dseparable_Y_compute(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_Y_compute(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_yuv420_fir2d_separable_y((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits);

    return status;
}
#endif

static BAM_Status BAM_Yuv420_fir2dseparable_UV_initFrame(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_UV_initFrame(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
           (*context->kernelArgs.coefPtr),
           context->kernelArgs.coefWidth);

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
           &(*context->kernelArgs.coefPtr)[context->kernelArgs.coefWidth],
           context->kernelArgs.coefHeight);

#if (!VCOP_HOST_EMULATION)
    vcop_yuv420_fir2d_separable_uv_init((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits,
                    context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_Yuv420_fir2dseparable_UV_compute(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_UV_compute(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_yuv420_fir2d_separable_uv((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits);

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableYExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL,
      &BAM_Yuv420_fir2dseparable_Y_initFrame,
      NULL,
      NULL,
      NULL,
      &vcop_yuv420_fir2d_separable_y_vloops };
#else
    { NULL,
      &BAM_Yuv420_fir2dseparable_Y_initFrame,
      &BAM_Yuv420_fir2dseparable_Y_compute,
      NULL,
      NULL,
      NULL };
#endif


BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableUvExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL,
      &BAM_Yuv420_fir2dseparable_UV_initFrame,
      NULL,
      NULL,
      NULL,
      &vcop_yuv420_fir2d_separable_uv_vloops };
#else
    { NULL,
      &BAM_Yuv420_fir2dseparable_UV_initFrame,
      &BAM_Yuv420_fir2dseparable_UV_compute,
      NULL,
      NULL,
      NULL };
#endif


