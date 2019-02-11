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
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"

#include "bam_remap_merge.h"
#include "bam_remap_merge_int.h"

static uint16_t remapMergePBlockOffset[2];

/* Function Prototypes */
static BAM_Status BAM_RemapMerge_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);
static BAM_Status BAM_RemapMerge_setMemRecFunc(const BAM_MemRec *memRecInternal[],
            const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[],
            uint8_t numRecInternal, uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
            void *kernelContext, const void *kernelArgs);


static BAM_Status BAM_RemapMerge_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
            BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (VCOP_HOST_EMULATION)
    const BAM_Remap_Merge_Args       *args                    = (const BAM_Remap_Merge_Args *)kernelArgs;
#else
    /* Typecasting by (const BAM_Remap_Merge_Args *) will lead to MISRA C 11.5. */
    const BAM_Remap_Merge_Args       *args                    = kernelArgs;
#endif
    const BAM_Remap_Args             *remapKernelArgs         = &(args->remapKernelArgs);
    const BAM_Memcpy_Args            *memcpyKernelArgs        = &(args->memcpyKernelArgs);
    const BAM_Yuv_420nv12_to_422uyvy_Args  *formatConvertKernelArgs = &(args->formatConvertKernelArgs);
    const BAM_Alpha_Blend_YUV420nv12_Args  *alphaBlendKernelArgs    = &(args->alphaBlendKernelArgs);
    BAM_MemRec                        internalBlockMemRec, *fcOutputBlock;
    BAM_Status                        status = BAM_S_SUCCESS;
    uint8_t                           enableMemcpy = 1U, enableMerge, numIntBlocks;
    Format                            srcFormat, dstFormat;

    srcFormat       = remapKernelArgs->maps.srcFormat;
    dstFormat       = args->dstFormat;
    enableMerge     = args->enableMerge;

    status = gBAM_TI_remapHelperFunc.getKernelMemRec(remapKernelArgs, internalBlock, internalBlock + REMAP_MERGE_KERNEL1_OUTPUT_PTR_IDX, \
                                     numInternalBlocks, numOutBlocks);
    numIntBlocks = REMAP_MERGE_KERNEL1_OUTPUT_PTR_IDX + 1U;
    remapMergePBlockOffset[0] = internalBlock[REMAP_MERGE_PBLOCK_PTR_IDX].size;
    remapMergePBlockOffset[1] = internalBlock[REMAP_MERGE_PBLOCK_PTR_IDX].size;

    /* If the src and dst formats are different, Format Convert Node is to be appended */
    if(srcFormat != dstFormat)
    {
        enableMemcpy = 0U;
        if(enableMerge == 1U)
        {
            fcOutputBlock   = internalBlock + REMAP_MERGE_KERNEL2_OUTPUT_PTR_IDX;
            numIntBlocks++;
        } else
        {
            fcOutputBlock   = outBlock;
        }
        if(srcFormat == YUV_420SP)
        {
            status = gBAM_TI_yuv420nv12_to_422uyvyHelperFunc.getKernelMemRec(formatConvertKernelArgs, \
                                                &internalBlockMemRec, fcOutputBlock, numInternalBlocks, numOutBlocks);
        }
        else if(srcFormat == YUV_422ILE)
        {
            status = gBAM_TI_yuv422uyvy_to_420nv12HelperFunc.getKernelMemRec(formatConvertKernelArgs, \
                                                &internalBlockMemRec, fcOutputBlock, numInternalBlocks, numOutBlocks);
        }
        else
        {
            status = BAM_E_UNSUPPORTED;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto EXIT;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }

        if(enableMerge == 1U)
        {
            fcOutputBlock->alignment      = 32;
            fcOutputBlock->attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
            fcOutputBlock->space          = BAM_MEMSPACE_IBUFHA;
        }

        /* P Block memory requirements */
        remapMergePBlockOffset[1] += internalBlockMemRec.size;
#if (!VCOP_HOST_EMULATION)
        internalBlock[REMAP_MERGE_PBLOCK_PTR_IDX].size += internalBlockMemRec.size;
#endif

    }
    if(enableMerge == 1U)
    {
        enableMemcpy = 0U;
        internalBlockMemRec.size = 0U;

        if(dstFormat == YUV_420SP)
        {
            status = gBAM_TI_alphaBlendYUV420nv12HelperFunc.getKernelMemRec(alphaBlendKernelArgs, &internalBlockMemRec, outBlock, \
                                             numInternalBlocks, numOutBlocks);
        }
        else if(dstFormat == YUV_422ILE)
        {
            status = gBAM_TI_alphaBlendYUV422iHelperFunc.getKernelMemRec(alphaBlendKernelArgs, &internalBlockMemRec, outBlock, \
                                             numInternalBlocks, numOutBlocks);
        }
        else
        {
            status = BAM_E_UNSUPPORTED;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto EXIT;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }

#if (!VCOP_HOST_EMULATION)
        internalBlock[REMAP_MERGE_PBLOCK_PTR_IDX].size += internalBlockMemRec.size;
#endif
    }

    if(enableMemcpy)
    {
        status = gBAM_TI_memcpyHelperFunc.getKernelMemRec(memcpyKernelArgs, &internalBlockMemRec, \
                                         outBlock, numInternalBlocks, numOutBlocks);
#if (!VCOP_HOST_EMULATION)
        internalBlock[REMAP_MERGE_PBLOCK_PTR_IDX].size += internalBlockMemRec.size;
#endif
    }

    /* The below code is reported as MISRA.BOOL.INVAR.TRUE or INVARIANT_CONDITION.GEN by KW tool
    But this is not true. KW tool is wrongly analyzing that numIntBlocks will never be less than 
    REMAP_MERGE_NUM_INTERNAL_BLOCKS. But this codndition could be tue for the cases where enableMerge is 1
    KW tool may the reporting this issue because of multiple test becnh used by Remap applet*/
    for(; numIntBlocks < REMAP_MERGE_NUM_INTERNAL_BLOCKS; numIntBlocks++)
    {
        internalBlock[numIntBlocks].size           = 4;
        internalBlock[numIntBlocks].alignment      = 4;
        internalBlock[numIntBlocks].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        internalBlock[numIntBlocks].space          = BAM_MEMSPACE_WBUF;
    }

    *numInternalBlocks = REMAP_MERGE_NUM_INTERNAL_BLOCKS;
    *numOutBlocks      = REMAP_MERGE_NUM_OUT_BLOCKS;

EXIT:
    return status;
}


static BAM_Status BAM_RemapMerge_setMemRecFunc(const BAM_MemRec *memRecInternal[],
            const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[],
            uint8_t numRecInternal, uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
            void *kernelContext, const void *kernelArgs)
{
    uint8_t i;
    BAM_Remap_Merge_Context            *context               =  (BAM_Remap_Merge_Context *)kernelContext;
    BAM_Remap_Context                  *remapContext          = &(context->remapContext);
    BAM_Memcpy_Context                 *memcpyContext         = &(context->memcpyContext);
    BAM_Yuv_420nv12_to_422uyvy_Context *formatConvertContext  = &(context->formatConvertContext);
    BAM_Alpha_Blend_YUV420nv12_Context *mergeContext          = &(context->mergeContext);
    BAM_Remap_Merge_Args             *args                    = &(context->kernelArgs);
    BAM_Remap_Args                   *remapKernelArgs         = &(args->remapKernelArgs);
    BAM_Memcpy_Args                  *memcpyKernelArgs        = &(args->memcpyKernelArgs);
    BAM_Yuv_420nv12_to_422uyvy_Args  *formatConvertKernelArgs = &(args->formatConvertKernelArgs);
    BAM_Alpha_Blend_YUV420nv12_Args  *alphaBlendKernelArgs    = &(args->alphaBlendKernelArgs);
    uint8_t                           enableMemcpy = 1U, enableMerge, numKernel = 0U;
    Format                            srcFormat, dstFormat;
    BAM_Status                        status = BAM_S_SUCCESS;

    srcFormat       = remapKernelArgs->maps.srcFormat;
    dstFormat       = args->dstFormat;
    enableMerge     = args->enableMerge;

    remapContext->pInBlock[REMAP_INPUT_IMAGE_BLOCK_PTR_IDX] = context->pInBlock[REMAP_INPUT_IMAGE_BLOCK_PTR_IDX];
    remapContext->pInBlock[REMAP_LUT_PTR_IDX] = context->pInBlock[REMAP_MERGE_LUT_PTR_IDX];
    remapContext->pOutBlock[REMAP_OUT_LUMA_IDX] = context->pInternalBlock[REMAP_MERGE_KERNEL1_OUTPUT_PTR_IDX];

    for(i = 0; i < REMAP_NUM_INTERNAL_BLOCKS; i++)
    {
        remapContext->pInternalBlock[i] = context->pInternalBlock[i];
    }

    context->initFuncList[numKernel]  = gBAM_TI_remapExecFunc.kernelInitFrame;
    context->kernelContext[numKernel] = remapContext;
    context->vloopFuncList[numKernel] = gBAM_TI_remapExecFunc.kernelCompute;
    context->pblockList[numKernel]    = remapContext;
    numKernel++;

    if(srcFormat != dstFormat)
    {
        enableMemcpy = 0U;
        formatConvertContext->pInBlock[BAM_YUV_420NV12_TO_422UYVY_INPUT_PORT_IMG] = remapContext->pOutBlock[REMAP_OUT_LUMA_IDX];

        formatConvertContext->pInternalBlock[PARAMS_IDX] = (void *)(*(uint8_t (*)[])context->pInternalBlock[REMAP_MERGE_PBLOCK_PTR_IDX]
                                                         + remapMergePBlockOffset[0]);

        if(enableMerge == 1U)
        {
            formatConvertContext->pOutBlock[BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT] = context->pInternalBlock[REMAP_MERGE_KERNEL2_OUTPUT_PTR_IDX];
        } else
        {
            formatConvertContext->pOutBlock[BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT] = context->pOutBlock[REMAP_MERGE_OUT_LUMA_IDX];
        }

        if(srcFormat == YUV_420SP)
        {
            context->initFuncList[numKernel]  = gBAM_TI_yuv420nv12_to_422uyvyExecFunc.kernelInitFrame;
            context->vloopFuncList[numKernel] = gBAM_TI_yuv420nv12_to_422uyvyExecFunc.kernelCompute;
        }
        else if(srcFormat == YUV_422ILE)
        {
            context->initFuncList[numKernel]  = gBAM_TI_yuv422uyvy_to_420nv12ExecFunc.kernelInitFrame;
            context->vloopFuncList[numKernel] = gBAM_TI_yuv422uyvy_to_420nv12ExecFunc.kernelCompute;
        }
        else
        {
            status = BAM_E_UNSUPPORTED;
        }

        context->kernelContext[numKernel] = formatConvertContext;
        context->pblockList[numKernel]    = formatConvertContext;
        numKernel++;
    }

    if(enableMerge == 1U)
    {
        enableMemcpy = 0U;
        if(srcFormat != dstFormat)
        {
            mergeContext->pInBlock[BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG1] = formatConvertContext->pOutBlock[BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT];
        } else
        {
            mergeContext->pInBlock[BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG1] = remapContext->pOutBlock[REMAP_OUT_LUMA_IDX];
        }
        mergeContext->pInBlock[BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG2] = context->pInBlock[BAM_REMAP_MERGE_INPUT_PORT_MERGE_BLOCK];
        mergeContext->pInBlock[BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_ALPHA] = context->pInBlock[BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK];

        mergeContext->pOutBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX] = context->pOutBlock[REMAP_MERGE_OUT_LUMA_IDX];

        mergeContext->pInternalBlock[MEMCPY_PBLOCK_PTR_IDX] = (void *)(*(uint8_t (*)[])context->pInternalBlock[REMAP_MERGE_PBLOCK_PTR_IDX]
                                                            + remapMergePBlockOffset[1]);

        if(dstFormat == YUV_420SP)
        {
            context->initFuncList[numKernel]  = gBAM_TI_alphaBlendYUV420nv12ExecFunc.kernelInitFrame;
            context->vloopFuncList[numKernel] = gBAM_TI_alphaBlendYUV420nv12ExecFunc.kernelCompute;
        }
        else if(dstFormat == YUV_422ILE)
        {
            context->initFuncList[numKernel]  = gBAM_TI_alphaBlendYUV422iExecFunc.kernelInitFrame;
            context->vloopFuncList[numKernel] = gBAM_TI_alphaBlendYUV422iExecFunc.kernelCompute;
        }
        else
        {
            status = BAM_E_UNSUPPORTED;
        }

        context->kernelContext[numKernel] = mergeContext;
        context->pblockList[numKernel]    = mergeContext;
        numKernel++;


    }
    if(enableMemcpy == 1U)
    {
        memcpyContext->pInBlock[MEMCPY_INPUT_BLOCK_PTR_IDX] = remapContext->pOutBlock[REMAP_OUT_LUMA_IDX];
        memcpyContext->pOutBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX] = context->pOutBlock[REMAP_MERGE_OUT_LUMA_IDX];

        memcpyContext->pInternalBlock[MEMCPY_PBLOCK_PTR_IDX] = (void *)(*(uint8_t (*)[])context->pInternalBlock[REMAP_MERGE_PBLOCK_PTR_IDX]
                                                             + remapMergePBlockOffset[0]);

        context->initFuncList[numKernel]  = gBAM_TI_memcpyExecFunc.kernelInitFrame;
        context->kernelContext[numKernel] = memcpyContext;
        context->vloopFuncList[numKernel] = gBAM_TI_memcpyExecFunc.kernelCompute;
        context->pblockList[numKernel]    = memcpyContext;
        numKernel++;
    }
    context->numInitFunc  = numKernel;
    context->numvloopFunc = numKernel;
    remapContext->kernelArgs  = *(remapKernelArgs);
    memcpyContext->kernelArgs = *(memcpyKernelArgs);
    formatConvertContext->kernelArgs  = *(formatConvertKernelArgs);
    mergeContext->kernelArgs = *(alphaBlendKernelArgs);

    return status;
}


BAM_KernelInfo gBAM_TI_remapMergeKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Remap_Merge_Context),
    sizeof(BAM_Remap_Merge_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    REMAP_MERGE_NUM_IN_BLOCKS,                    /* 2 */
    REMAP_MERGE_NUM_OUT_BLOCKS,                   /* 1 */
    REMAP_MERGE_NUM_INTERNAL_BLOCKS               /* 8 */
};

/* Remap and Merge Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_remapMergeHelperFunc =
{
  &BAM_RemapMerge_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_RemapMerge_setMemRecFunc  /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


