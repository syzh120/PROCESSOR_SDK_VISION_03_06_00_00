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
 *  @file       bam_image_interleave_u8_exec_funcs.c
 *
 *  @brief       This file implements functions for integrating unsigned 8 bit interleave function into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_image_interleave_u8_int.h"
#include "vcop_image_interleave_kernel.h" /* compiler should take care of include path */


/* Function Prototypes */
static BAM_Status BAM_Image_interleave_u8_getMemRecFunc(const void *kernelArgs, BAM_MemRec *internalBlock,
        BAM_MemRec *outBlock, uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

#if 0
static BAM_Status BAM_Image_interleave_u8_setMemRecFunc(const BAM_MemRec *internalBlock[],
        const BAM_MemRec *inBlock[], const BAM_MemRec *outBlock[], uint8_t numInternalBlocks,
        uint8_t numInBlocks, uint8_t numOutBlocks, void *kernelContext, const void *kernelArgs);
#endif

static BAM_Status BAM_Image_interleave_u8_getMemRecFunc(const void *kernelArgs, BAM_MemRec *internalBlock,
        BAM_MemRec *outBlock, uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    BAM_Image_Interleave_U8_Args *args = (BAM_Image_Interleave_U8_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2 * vcop_image_interleave_u8_param_count();
    outBlock[0].size = (args->inRows) * (args->inCols) * 2;

    return BAM_S_SUCCESS;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0
static BAM_Status BAM_Image_interleave_u8_setMemRecFunc(const BAM_MemRec *internalBlock[],
        const BAM_MemRec *inBlock[], const BAM_MemRec *outBlock[], uint8_t numInternalBlocks,
        uint8_t numInBlocks, uint8_t numOutBlocks, void *kernelContext, const void *kernelArgs)
{
    BAM_Image_Interleave_U8_Args *args = (BAM_Image_Interleave_U8_Args *) kernelArgs;
    BAM_Image_Interleave_U8_Context *context = (BAM_Image_Interleave_U8_Context *) kernelContext;

    if (numInternalBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if (numInBlocks != 2)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if (numOutBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[Y_IDX] = inBlock[Y_IDX]->base;
    context->pInBlock[UV_IDX] = inBlock[UV_IDX]->base;
    context->pOutBlock[0] = outBlock[0]->base;
    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;

    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_interleaveu8Kernel =
{
    0,                  /* kernelId */
    sizeof(BAM_Image_Interleave_U8_Context),    /* CHECK: kernelContextSize = sizeof(EVE_EDMA_transfer_context) */
    sizeof(BAM_Image_Interleave_U8_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE,   /* nodeType */
    NUM_IN_BLOCKS,                  /* 2 */
    NUM_OUT_BLOCKS,                 /* 1 */
    NUM_INTERNAL_BLOCKS             /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_interleaveu8HelperFunc =
{ &BAM_Image_interleave_u8_getMemRecFunc, /*&BAM_Image_interleave_u8_setMemRecFunc*/ };
