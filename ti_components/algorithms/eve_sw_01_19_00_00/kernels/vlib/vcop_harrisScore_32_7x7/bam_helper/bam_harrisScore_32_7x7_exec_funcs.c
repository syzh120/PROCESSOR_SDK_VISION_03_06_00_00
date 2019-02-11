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
 *  @file       bam_harrisScore_32_7x7_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating harrisScore_32_7x7 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_harrisScore_32_7x7_int.h"
#include "bam_harrisScore_32_7x7.h"
#include "vcop_harrisScore_32_7x7_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_harrisScore_32_7x7_initFrame(void *kernelContext);
static BAM_Status BAM_harrisScore_32_7x7_compute(void *kernelContext);

static BAM_Status BAM_harrisScore_32_7x7_initFrame(void *kernelContext)
{
    BAM_HarrisScore_32_7x7_Context *context = (BAM_HarrisScore_32_7x7_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_harrisScore_32_7x7_1_init(
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADX_PORT], /* gradX */
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADY_PORT], /* gradY */
            (uint32_t)context->kernelArgs.width,                                          /* width */
            (uint32_t)context->kernelArgs.height,                                         /* height */
            (uint32_t)context->kernelArgs.inStride,                                       /* srcPitch */
            (context->kernelArgs.width - (context->kernelArgs.windowSize - 1u)),  /* dstPitch */
            (uint8_t)context->kernelArgs.windowSize, /* window Size */
            (int32_t*)context->pInternalBlock[XX_IDX],                          /* XX */
            (int32_t*)context->pInternalBlock[YY_IDX],                          /* YY */
            (int32_t*)context->pInternalBlock[XY_IDX],                          /* XY */
            (uint16_t*)context->pInternalBlock[PARAMS_IDX_1]);
    /* CHECK_MISRA("-17.1 17.4")  -> Disable rule 17.1 17.4 */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation is allowed for context->pInternalBlock[XX_IDX] + 1, context->pInternalBlock[YY_IDX] + 1, context->pInternalBlock[XY_IDX] + 1*/
    vcop_harrisScore_32_7x7_2_init(
            ((int32_t)context->kernelArgs.width - ((int32_t)context->kernelArgs.windowSize - 1)),    /* width */
            ((int32_t)context->kernelArgs.height - ((int32_t)context->kernelArgs.windowSize - 1)),   /* height */
            (context->kernelArgs.width - (context->kernelArgs.windowSize - 1u)),                  /* srcPitch */
            (uint32_t)context->kernelArgs.outStride,  /* dstPitch */
            (int32_t*)context->pOutBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT], /* outm */
            (uint16_t)context->kernelArgs.scaling,    /* k */
            (int32_t*)context->pInternalBlock[XX_IDX],  /* XX */
            (int32_t*)context->pInternalBlock[YY_IDX],  /* YY */
            (int32_t*)context->pInternalBlock[XY_IDX],  /* XY */
            (uint16_t*)context->pInternalBlock[XX_IDX], /* XXl */
            (uint16_t*)context->pInternalBlock[YY_IDX], /* YYl */
            (uint16_t*)context->pInternalBlock[XY_IDX], /* XYl */
            (int16_t*)context->pInternalBlock[XX_IDX] + 1,  /* XXh */
            (int16_t*)context->pInternalBlock[YY_IDX] + 1,  /* YYh */
            (int16_t*)context->pInternalBlock[XY_IDX] + 1,  /* XYh */
            (uint32_t*)context->pInternalBlock[DETL_IDX],   /* detL */
            (int32_t*)context->pInternalBlock[DETH_IDX],    /* detH */
            (uint16_t*)context->pInternalBlock[PARAMS_IDX_2]);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 */
#endif
    return status;
}

static BAM_Status BAM_harrisScore_32_7x7_compute(void *kernelContext)
{
    BAM_HarrisScore_32_7x7_Context *context = (BAM_HarrisScore_32_7x7_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_harrisScore_32_7x7_1_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX_1]);
    vcop_harrisScore_32_7x7_2_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX_2]);
#else
    vcop_harrisScore_32_7x7_1(
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADX_PORT], /* gradX */
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADY_PORT], /* gradY */
            context->kernelArgs.width,                                          /* width */
            context->kernelArgs.height,                                         /* height */
            context->kernelArgs.inStride,                                       /* srcPitch */
            context->kernelArgs.width - (context->kernelArgs.windowSize - 1),   /* dstPitch */
            context->kernelArgs.windowSize, /* window Size */
            (int32_t*)context->pInternalBlock[XX_IDX],                          /* XX */
            (int32_t*)context->pInternalBlock[YY_IDX],                          /* YY */
            (int32_t*)context->pInternalBlock[XY_IDX]);

    vcop_harrisScore_32_7x7_2(
            context->kernelArgs.width  - (context->kernelArgs.windowSize - 1),    /* width */
            context->kernelArgs.height - (context->kernelArgs.windowSize - 1),   /* height */
            context->kernelArgs.width  - (context->kernelArgs.windowSize - 1),                  /* srcPitch */
            context->kernelArgs.outStride,  /* dstPitch */
            (int32_t*)context->pOutBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT], /* outm */
            context->kernelArgs.scaling,    /* k */
            (int32_t*)context->pInternalBlock[XX_IDX],  /* XX */
            (int32_t*)context->pInternalBlock[YY_IDX],  /* YY */
            (int32_t*)context->pInternalBlock[XY_IDX],  /* XY */
            (uint16_t*)context->pInternalBlock[XX_IDX], /* XXl */
            (uint16_t*)context->pInternalBlock[YY_IDX], /* YYl */
            (uint16_t*)context->pInternalBlock[XY_IDX], /* XYl */
            (int16_t*)context->pInternalBlock[XX_IDX] + 1,  /* XXh */
            (int16_t*)context->pInternalBlock[YY_IDX] + 1,  /* YYh */
            (int16_t*)context->pInternalBlock[XY_IDX] + 1,  /* XYh */
            (uint32_t*)context->pInternalBlock[DETL_IDX],   /* detL */
            (int32_t*)context->pInternalBlock[DETH_IDX]);
#endif
    return status;

}

BAM_KernelExecFuncDef gBAM_TI_harrisScore_32_7x7_ExecFunc =
{ NULL, &BAM_harrisScore_32_7x7_initFrame, &BAM_harrisScore_32_7x7_compute, NULL, NULL, NULL };

