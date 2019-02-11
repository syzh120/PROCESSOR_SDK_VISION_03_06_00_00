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
 *  @file       bam_contrast_stretching_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_contrast_stretching_int.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_ContrastStretching_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_ContrastStretching_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_ContrastStretching_Args *args = (const BAM_ContrastStretching_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX].size =
                      sizeof(uint16_t) * vcop_contrast_stretching_param_count();
#else
    internalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    outBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT].size =
                              ALIGN_2SIMD((uint32_t)args->blkWidth) * args->blkHeight;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_contrastStretchingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_ContrastStretching_Context),
    sizeof(BAM_ContrastStretching_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_contrastStretchingHelperFunc =
{ &BAM_ContrastStretching_getMemRecFunc, NULL};

