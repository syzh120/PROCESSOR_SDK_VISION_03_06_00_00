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
 *  @file       bam_gradXYmag_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gradXYmag into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_gradXYmag_int.h"
#include "bam_gradXYmag.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gradXYmag_initFrame(void *kernelContext);
static BAM_Status BAM_gradXYmag_Compute(void *kernelContext);


static BAM_Status BAM_gradXYmag_initFrame(void *kernelContext)
{
    BAM_GradXYmag_Context *context = (BAM_GradXYmag_Context *) kernelContext;
    BAM_Status status = 0;

    /* By the way the function is initialized, it will take a block of kernelArgs.width x kernelArgs.height pixels
     *  and calculate the gradient of of every pixel in the center region of dimension (kernelArgs.width-2)x(kernelArgs.height-2).
     *  The output is however written in a region of dimensions kernelArgs.width x (kernelArgs.height-2), so the last 2 pixels of each output row
     *  must be ignored.
     *  The function may also produce more data if kernelArgs.width x (kernelArgs.height-2) is not multiple of 16. That's why the getMemRec function asks
     *  for a total output size that is rounded up to the next multiple of 16. In any case only the first kernelArgs.width x (kernelArgs.height-2) elements
     *  in the output are to be considered. And within this, the two last pixels of each row of kernelArgs.width pixels must be ignored.
     */
#if !(VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
    {
      vcop_vec_gradients_xy_and_magnitude_init(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height,
            (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_vec_gradients_xy_and_magnitude_vloops;
    }
    else {
        if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
        {
          vcop_vec_gradients_xy_magnitudeu8_init(
                (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
                (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
                (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
                (uint8_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
                context->kernelArgs.pitch,
                context->kernelArgs.width,
                context->kernelArgs.height,
                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
          context->kernelCustom = &vcop_vec_gradients_xy_magnitudeu8_vloops;
        }
    }
#endif
    return status;
}

static BAM_Status BAM_gradXYmag_Compute(void *kernelContext)
{
    BAM_GradXYmag_Context *context = (BAM_GradXYmag_Context *) kernelContext;

    /* By the way the function is initialized, it will take a block of kernelArgs.width x kernelArgs.height pixels
     *  and calculate the gradient of of every pixel in the center region of dimension (kernelArgs.width-2)x(kernelArgs.height-2).
     *  The output is however written in a region of dimensions kernelArgs.width x (kernelArgs.height-2), so the last 2 pixels of each output row
     *  must be ignored.
     *  The function may also produce more data if kernelArgs.width x (kernelArgs.height-2) is not multiple of 16. That's why the getMemRec function asks
     *  for a total output size that is rounded up to the next multiple of 16. In any case only the first kernelArgs.width x (kernelArgs.height-2) elements
     *  in the output are to be considered. And within this, the two last pixels of each row of kernelArgs.width pixels must be ignored.
     */
#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
    {
    vcop_vec_gradients_xy_and_magnitude(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height);
    }
    else if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
    {
      vcop_vec_gradients_xy_magnitudeu8(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (uint8_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height);
    }
#else
    context->kernelCustom(context->pInternalBlock[PARAMS_IDX]);
#endif

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_gradXYmagExecFunc =
{ NULL, &BAM_gradXYmag_initFrame, &BAM_gradXYmag_Compute, NULL, NULL, NULL};
