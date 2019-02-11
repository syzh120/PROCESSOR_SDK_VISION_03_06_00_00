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

#include "algframework.h"
#include "bam_gradXYmag_int.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gradXYmag_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_gradXYmag_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

    BAM_Status status= BAM_S_SUCCESS;

#if !(VCOP_HOST_EMULATION)
    const BAM_GradXYmag_Args *args = kernelArgs;
    if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
    {
        internalBlock[PARAMS_IDX].size = 2u*vcop_vec_gradients_xy_and_magnitude_param_count();
    }
    else {
        if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
        {
            internalBlock[PARAMS_IDX].size = 2u*vcop_vec_gradients_xy_magnitudeu8_param_count();
        }
    }
#else
    const BAM_GradXYmag_Args *args = (const BAM_GradXYmag_Args *)kernelArgs;
    internalBlock[PARAMS_IDX].size = 4u;
#endif

    if(args->gradientMethod >= (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_MAX)
    {
        status= BAM_E_FAIL;
    }
    else {
        /* The size of the output block size of args->width*(args->height-2) is rounded up to the next multiple of 2*SIMD_WIDTH
         * because the kernel-C implementation align the amount of produced output to 2*SIMD_WIDTH for best performance
         */
        outBlock[OUT_X_IDX].size = 2u*ALIGN_2SIMD((uint32_t)args->width*args->height);
        /* During performance fine-tuning of harris-corner applet, we concluded that larger blocks can be allocated if this output memory record goes to WBUF
         * This improvement may only be meaningful in the case of harris-corner applet. For other applet, try first with the below line removed.
         * */
        outBlock[OUT_X_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;
        outBlock[OUT_Y_IDX].size = 2u*ALIGN_2SIMD((uint32_t)args->width*args->height);
        outBlock[OUT_Y_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;

        if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_9BITS )
        {
            outBlock[OUT_MAG_IDX].size = 2u*ALIGN_2SIMD((uint32_t)args->width*args->height);
        }
        else {
            if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS )
            {
                outBlock[OUT_MAG_IDX].size = ALIGN_2SIMD((uint32_t)args->width*args->height);
            }
        }
        outBlock[OUT_MAG_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;
    }

    return status;
}

BAM_KernelInfo gBAM_TI_gradXYmagKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_GradXYmag_Context),
        sizeof(BAM_GradXYmag_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 3 */
        NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_gradXYmagHelperFunc =
{ &BAM_gradXYmag_getMemRecFunc, NULL};

