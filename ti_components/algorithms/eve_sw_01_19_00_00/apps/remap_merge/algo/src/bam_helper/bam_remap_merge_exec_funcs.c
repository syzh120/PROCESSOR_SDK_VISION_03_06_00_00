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
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_remap_merge_int.h"
#include "bam_remap_merge.h"


extern int8_t remapNumTiles;


/* Function Prototypes */
static BAM_Status Bam_RemapMerge_initFrame(void *kernelContext);
static BAM_Status Bam_RemapMerge_compute(void *kernelContext);

static BAM_Status Bam_RemapMerge_initFrame(void *kernelContext)
{

    BAM_Remap_Merge_Context            *context               =  (BAM_Remap_Merge_Context *)kernelContext;
    BAM_Remap_Context                  *remapContext          = &(context->remapContext);
    BAM_Memcpy_Context                 *memcpyContext         = &(context->memcpyContext);
    BAM_Yuv_420nv12_to_422uyvy_Context *formatConvertContext  = &(context->formatConvertContext);
    BAM_Alpha_Blend_YUV420nv12_Context *mergeContext          = &(context->mergeContext);
    BAM_Remap_Merge_Args               *args                  = &(context->kernelArgs);
    uint8_t numKernel = 0U, enableMerge, enableMemcpy = 1U;
    Format  srcFormat, dstFormat;

    srcFormat       = remapContext->kernelArgs.maps.srcFormat;
    dstFormat       = args->dstFormat;
    enableMerge     = args->enableMerge;

    context->initFuncList[numKernel](remapContext);

    context->pblockList[numKernel]    = remapContext;
    numKernel++;

    if(srcFormat != dstFormat)
    {
        enableMemcpy = 0;
        context->pblockList[numKernel]    = formatConvertContext;
        context->initFuncList[numKernel](formatConvertContext);
        numKernel++;
    }

    if(enableMerge == 1U)
    {
        enableMemcpy = 0;
        context->pblockList[numKernel]    = mergeContext;
        context->initFuncList[numKernel](mergeContext);
        numKernel++;

    }

    if(enableMemcpy == 1U)
    {
        context->pblockList[numKernel]    = memcpyContext;
        context->initFuncList[numKernel](memcpyContext);

    }

    return BAM_S_SUCCESS;
}



static BAM_Status Bam_RemapMerge_compute(void *kernelContext)
{
    BAM_Remap_Merge_Context            *context               =  (BAM_Remap_Merge_Context *)kernelContext;
    uint8_t i;

    /* Remap kernel to be called for every tile */
    context->vloopFuncList[0](context->pblockList[0]);

    /* (Format Convert [+] Merge)/Memcpy kernel to be called for every output block */
    if(remapNumTiles == 1)
    {
        for (i = 1U; i < context->numInitFunc; i++)
        {
            context->vloopFuncList[i](context->pblockList[i]);
        }
    }

    return BAM_S_SUCCESS;
}

BAM_KernelExecFuncDef gBAM_TI_remapMergeExecFunc =
    { NULL, &Bam_RemapMerge_initFrame, &Bam_RemapMerge_compute, NULL, NULL, NULL };


