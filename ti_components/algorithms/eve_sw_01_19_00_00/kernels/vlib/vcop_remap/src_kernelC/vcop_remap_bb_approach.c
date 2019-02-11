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

/*                                                                          */
/*     @file : vcop_remap.c                                                 */
/*                                                                          */
/*     @brief : This file contains VCOP implementation for remap            */
/*              kernel                                                      */
/*                                                                          */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (October 2013) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

/* Include the lib interface header files */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "vcop.h"

#include "remap.h"
#include "remap_common.h"
#include "vcop_remap.h"

#include "vcop_deInterleaveYUV422IBE.h"
#include "vcop_deInterleaveYUV422ILE.h"
#include "vcop_bilinearInterpolate8b.h"
#include "vcop_bilinearInterpolate16b.h"
#include "vcop_bilinearInterpolateYUV422Ichroma.h"
#include "vcop_bilinearInterpolateYUV420SPchroma.h"
#include "vcop_bilinearInterpolateYUV422Iluma.h"
#include "vcop_dsTLUindexAndFrac.h"
#include "vcop_chromaTLUIndexCalc.h"
#include "vcop_nnInterpolate8b.h"
#include "vcop_nnInterpolate420SPchroma.h"
#include "vcop_nnInterpolate422Ichroma.h"

#define LUMA_INDEX      (0U)
#define CHROMA_U_INDEX  (1U)
#define CHROMA_V_INDEX  (2U)
#define CHROMA_UV_INDEX (1U)


/* VCOP kernel initialization functions for bilinear, nearest neighbor interpolation methods and deinterleave of chroma and luma */
static void bilinearInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t outputBlockSize, \
        uint8_t *xFracArray, uint8_t *yFracArray, uint16_t *tluIndexArray,  uint8_t *scattered_ofst, \
        uint16_t *src_stride_ptr, Format format, uint8_t yuvComponent, uint8_t mnQShift, uint8_t oQShift, \
        uint16_t qScale, uint8_t *scratchWbuf, uint8_t *scratchIbuf, \
        const RemapParms *params, VcopRemapContext *context);

static void nnInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t outputBlockSize, uint8_t *xFracArray, \
        uint8_t *yFracArray, uint16_t *tluIndexArray,  uint8_t *scattered_ofst, uint16_t *src_stride_ptr, \
        Format format, uint8_t yuvComponent, uint8_t QShift, uint8_t *scratchWbuf, \
        uint8_t *scratchIbuf, const RemapParms *params, VcopRemapContext *context);

static void deInterleaveYUV422I_init(uint8_t *src, uint8_t *dst, uint8_t *dst_u, uint8_t *dst_v, \
        uint16_t size, Format dstFormat, VcopRemapContext *context);



/* Function initializing the kernel init functions for each scenario of remap function */
int32_t vcop_remap_bb_approach_init(
                uint8_t blockInfoPtr[],
                uint8_t inputImagePtr[],
                uint8_t interpolationBuf0Ptr[],
                uint8_t interpolationBuf1Ptr[],
                uint8_t ChromaTLUIndexPtr[],
                uint8_t scatteredOffsetPtr[],
                uint8_t chromaUVPtr[],
                uint8_t outputPtr[],
                const RemapParms *params,
                VcopRemapContext *context
){

    convertMapBlockInfo (*blockInfo)[];
    uint16_t            (*tluIndexArray)[], (*tluIndexArrayUV)[], (*tluIndexArrayU)[], (*tluIndexArrayV)[], (*s_scatterOffset_temp)[];
    uint8_t             (*xFracArrayUV)[], (*yFracArrayUV)[], (*scattered_ofst)[];
    uint8_t             (*xFracArrayU)[], (*xFracArrayV)[], (*yFracArrayU)[], (*yFracArrayV)[];
    uint8_t             (*src)[], (*src_uv)[], (*dst)[], (*dst_uv)[];
    uint16_t *src_stride_ptr, *src_stride_div2_ptr, *src_stride_q16_ptr, *stride_ptr;
    uint8_t  *src_y, *src_u, *src_v;
    uint8_t  *dst_y, *dst_u, *dst_v;
    uint8_t  *scratch_y, *scratch_u, *scratch_v;
    uint8_t   mnQShift, oQShift;
    uint16_t  qScale, chromaDiv;
    uint16_t  outputBlockSize;
    uint16_t  width, height;
    uint16_t  srcSize, i;
    Format    srcFormat;
    uint16_t *pblock, *s_scatterOffset_luma, *s_scatterOffset_chroma;
    int32_t   status= 0;
    uint8_t  *tluFracArray;

    width     = params->maps.outputBlockDim.width;
    height    = params->maps.outputBlockDim.height;
    srcFormat = params->maps.srcFormat;
    outputBlockSize= width*height;
    srcSize= sizeofFormat(srcFormat);

    /* blockInfo points to ConvertMapBlockInfo structure (in IBUFL) */
    blockInfo= (convertMapBlockInfo (*)[])blockInfoPtr;
    /* tluIndexArray points to TLU Index of Luma block (in IBUFL) */
    tluIndexArray= (uint16_t (*)[])((*blockInfo) + 1);
    tluFracArray = (uint8_t *)((*tluIndexArray) + outputBlockSize);

    context->pBlockIdx= 0;
    context->pblockRunningMem = (uint16_t (*)[])(void *)context->pblockMem;

    /* In BB, the output is filled with interpolated data in raster scan order. we can use npt() to fill
         the output. But to use the same kernel across BB and Tile approach, we are forced to use s_scatter().
         Hence, below we create the scatter offsets (1,2,3 ....) to be used by s_scatter.
         Since the kernel is compute intensive, the usage of s_scatter() will not led to performance degradation. */
    s_scatterOffset_luma = (uint16_t *)(interpolationBuf0Ptr + ((uint16_t)2 * (uint16_t)sizeof(uint16_t) * (uint16_t)ALIGN_2SIMD(outputBlockSize)));
    s_scatterOffset_temp = (uint16_t (*)[])(void *)s_scatterOffset_luma;
    for(i = 0; i < outputBlockSize; i++)
    {
        (*s_scatterOffset_temp)[i] = i;
    }
    s_scatterOffset_temp = (uint16_t (*)[])(void *)&(*s_scatterOffset_temp)[i];

    s_scatterOffset_chroma = *s_scatterOffset_temp;
    if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE))
    {
        for(i = 0; i < (uint16_t)(ALIGN_2SIMD((uint32_t)outputBlockSize/(uint32_t)2U)); i++)
        {
            (*s_scatterOffset_temp)[i] = 2U*i;
        }
        s_scatterOffset_temp = (uint16_t (*)[])(void *)&(*s_scatterOffset_temp)[i];

    }


    /* Partitioning Scratch Memory for Chroma components to be fed into the Kernels */
    if (srcFormat== YUV_420SP) {

        /* tluIndexArrayU/V is memory needed to store TLU Index for Chroma calculated on the fly (in IBUFL) */
        /* The Chroma TLU Index Calculate kernel will populate this memory */
        tluIndexArrayUV = (uint16_t (*)[])ChromaTLUIndexPtr;
        tluIndexArrayU  = tluIndexArrayUV;
        tluIndexArrayV  = tluIndexArrayU;

        /* x/yFracArrayUV is memory needed to store TLU Fractional for Chroma (calculated on the fly) */
        /* The Down Sampling TLU Index and Fractional kernel will populate this memory */
        xFracArrayUV= (uint8_t (*)[])((*tluIndexArrayV) + (outputBlockSize/4U));
        yFracArrayUV= (uint8_t (*)[])((*xFracArrayUV) + (outputBlockSize/4U));
        xFracArrayU = xFracArrayUV;
        xFracArrayV = xFracArrayUV;
        yFracArrayU = yFracArrayUV;
        yFracArrayV = yFracArrayUV;

        scattered_ofst  = NULL;
    }
    else if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE)) {

        /* scattered_ofst stores the relative position of U or V in 422 (in WMEM) */
        scattered_ofst   = (uint8_t (*)[])scatteredOffsetPtr;
        (*scattered_ofst)[0]= 0;  (*scattered_ofst)[1]= (uint8_t)4;  (*scattered_ofst)[2]= (uint8_t)8;  (*scattered_ofst)[3]= (uint8_t)12;
        (*scattered_ofst)[4]= (uint8_t)16; (*scattered_ofst)[5]= (uint8_t)20; (*scattered_ofst)[6]= (uint8_t)24; (*scattered_ofst)[7]= (uint8_t)28;

        /* tluIndexArrayU/V is memory needed to store TLU Index for Chroma (calculated on the fly) */
        /* The Down Sampling TLU Index and Fractional kernel will populate this memory */
        tluIndexArrayU= (uint16_t (*)[])(ChromaTLUIndexPtr);
        tluIndexArrayV= (uint16_t (*)[])((*tluIndexArrayU) + (outputBlockSize/2U));

        /* x/yFracArrayU/V is memory needed to store TLU Fractional for Chroma (calculated on the fly) */
        /* The Down Sampling TLU Index and Fractional kernel will populate this memory */
        xFracArrayU= (uint8_t (*)[])((*tluIndexArrayV) + (outputBlockSize/2U));
        xFracArrayV= (uint8_t (*)[])(*xFracArrayU + (outputBlockSize/2U));
        yFracArrayU= (uint8_t (*)[])(*xFracArrayV + (outputBlockSize/2U));
        yFracArrayV= (uint8_t (*)[])(*yFracArrayU + (outputBlockSize/2U));
    }
    else
    {
        /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
    }


    src_stride_ptr= &(*blockInfo)->inputBlockWidth;
    src_stride_div2_ptr= &(*blockInfo)->inputBlockWidthDiv2;
    src_stride_q16_ptr= &(*blockInfo)->inputBlockWidthQ16;

    if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE) || (srcFormat== YUV_420SP)) {
        mnQShift= 0;
        oQShift= (uint8_t)(params->maps.qShift << 1U);
    } else {
        if (srcSize== 2U) {
            /* U16/S16 Format */
            mnQShift= params->maps.qShift;
            oQShift= params->maps.qShift;
        }
        else {
            /* U8/S8 Format */
            mnQShift= 0;
            oQShift= (uint8_t)(params->maps.qShift << 1U);
        }
    }
    qScale= (uint16_t)((uint16_t)1 << params->maps.qShift);

    /* src, src_uv points to Input Image Luma and Chroma block respectively (in IBUFL) */
    src    = (uint8_t (*)[])(inputImagePtr);
    src_uv = (uint8_t (*)[])(*src + ALIGN_TLU(params->maps.maxInputBlockSize));

    /* dst, dst_uv points to Remapped output Luma and Chroma block respectively (in IBUFH) */
    dst    = (uint8_t (*)[])outputPtr;
    dst_uv = (uint8_t (*)[])(*dst + outputBlockSize);

    /* For 422, the Input Image block is De-interleaved and Y, U, V is stored into separate scratch buffers, each 32 bytes aligned in IBUFH */
    if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE)) {
        scratch_y= (uint8_t*)*src;
        scratch_u= (uint8_t*)chromaUVPtr;

        /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* This is required for pointer alignment to word/double_word boundary and can be waived.  */
        scratch_v= (uint8_t*)ALIGN_4SIMD((uintptr_t)chromaUVPtr + ALIGN_SIMD((params->maps.maxInputBlockSize/2U) + 7U));
        /* RESET_MISRA("10.3")  -> Reset rule 10.3     */
        /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

        /* Initialize the Deinterleave kernel for 422 */
        deInterleaveYUV422I_init(*src, scratch_y, scratch_u, scratch_v, params->maps.maxInputBlockSize, srcFormat, context);

    }

    /* Set src, dst for Y, U and V for all formats */
    if (srcFormat== YUV_422ILE) {
        src_y= scratch_y;
        src_u= scratch_u;
        src_v= scratch_v;
        dst_y= *dst+1;
        dst_u= *dst;
        dst_v= *dst+2;
    }
    else if (srcFormat== YUV_422IBE) {
        src_y= scratch_y;
        src_u= scratch_u;
        src_v= scratch_v;
        dst_y= *dst;
        dst_u= *dst+1;
        dst_v= *dst+3;
    }
    else { /* U8, U16, 420. For U8 and U16, src, dst for U, V is not used */
        src_y= *src;
        src_u= *src_uv;
        src_v= *src_uv+1;
        dst_y= *dst;
        dst_u= *dst_uv;
        dst_v= *dst_uv+1;
    }


    /* Bilinear or Nearest Neighbor Interpolation for Luma components */
    /* Supported formats for Bilinear Interpolation : U8, S8, U16, S16, 420 Luma, 422 Luma */
    if (params->interpolationLuma== BILINEAR) {

        bilinearInterpolate_init(src_y, dst_y, outputBlockSize, NULL, NULL, \
                *tluIndexArray,  (uint8_t *)(void *)s_scatterOffset_luma, src_stride_ptr, srcFormat, LUMA_INDEX, mnQShift, \
                oQShift, qScale, (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);
    }
    /* Supported formats for Nearest Neighbor Interpolation : U8, S8, 420 Luma */
    else {

        nnInterpolate_init(src_y, dst_y, outputBlockSize, NULL, NULL, \
                *tluIndexArray,  NULL, src_stride_ptr, srcFormat, LUMA_INDEX, params->maps.qShift, \
                (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);
    }


    /* For Formats with Chroma components */
    if ((srcFormat == YUV_422ILE) || (srcFormat == YUV_422IBE) || (srcFormat == YUV_420SP)) {

        /* Pre-Interpolation of Chroma, On the Fly TLU Calculation for Chroma components is done below */
        /* For 422, Down Sampling TLU Index and Fractional kernel is initialized */
        if ((srcFormat == YUV_422ILE) || (srcFormat == YUV_422IBE)) {
            chromaDiv =2U;
            /* stride is divided by 2 as U and V are de-interleaved and have a width of stride/2 each */
            stride_ptr = src_stride_div2_ptr;
            /* reusing luma tlu index memory (in IBUFL) as scratch buffer for Chroma Interpolation */
            interpolationBuf1Ptr = (uint8_t *)(*tluIndexArray);

            if (params->interpolationChroma== BILINEAR) {
#if (!VCOP_HOST_EMULATION)
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracBilInterpolateBB_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_dsTLUindexAndFracBilInterpolateBB_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pBlockIdx++;

                vcop_dsTLUindexAndFracBilInterpolateBB_init(*tluIndexArray, tluFracArray, *xFracArrayU, *yFracArrayU, \
                    *tluIndexArrayU, *xFracArrayV, *yFracArrayV, *tluIndexArrayV, params->maps.qShift, outputBlockSize, pblock);
#else
                vcop_dsTLUindexAndFracBilInterpolateBB(*tluIndexArray, tluFracArray, *xFracArrayU, *yFracArrayU, \
                    *tluIndexArrayU, *xFracArrayV, *yFracArrayV, *tluIndexArrayV, params->maps.qShift, outputBlockSize);
#endif
            } else { /* NN Chroma Interpolation */
#if (!VCOP_HOST_EMULATION)
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracNNInterpolateBB_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_dsTLUindexAndFracNNInterpolateBB_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pBlockIdx++;

                vcop_dsTLUindexAndFracNNInterpolateBB_init(*tluIndexArray, tluFracArray, *tluIndexArrayU, \
                         *tluIndexArrayV, src_stride_ptr, params->maps.qShift, outputBlockSize, pblock);
#else
                vcop_dsTLUindexAndFracNNInterpolateBB(*tluIndexArray, tluFracArray, *tluIndexArrayU, \
                        *tluIndexArrayV, src_stride_ptr, params->maps.qShift, outputBlockSize);
#endif
            }
        }
        /* For 420, Chroma TLU Index Calculate kernel is initialized */
        else {
            chromaDiv =4U;
            /* U and V are interleaved and have a width of stride together */
            stride_ptr = src_stride_ptr;

            if (params->interpolationChroma== BILINEAR) {
#if (!VCOP_HOST_EMULATION)
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcBilInterpolateBB_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_chromaTLUIndexCalcBilInterpolateBB_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pBlockIdx++;

                vcop_chromaTLUIndexCalcBilInterpolateBB_init(*tluIndexArray, tluFracArray, src_stride_ptr, src_stride_q16_ptr, *tluIndexArrayUV, \
                                     *xFracArrayUV, *yFracArrayUV, params->maps.qShift, width, height/2U, pblock);
#else
                vcop_chromaTLUIndexCalcBilInterpolateBB(*tluIndexArray, tluFracArray, src_stride_ptr, src_stride_q16_ptr, *tluIndexArrayUV, \
                                     *xFracArrayUV, *yFracArrayUV, params->maps.qShift, width, height/2U);
#endif
           } else { /* NN Chroma Interpolation */
#if (!VCOP_HOST_EMULATION)
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcNNInterpolateBB_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_chromaTLUIndexCalcNNInterpolateBB_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pBlockIdx++;

                vcop_chromaTLUIndexCalcNNInterpolateBB_init(*tluIndexArray, src_stride_ptr, src_stride_q16_ptr, *tluIndexArrayUV, \
                                     width, height/2U, pblock);
#else
                vcop_chromaTLUIndexCalcNNInterpolateBB(*tluIndexArray, src_stride_ptr, src_stride_q16_ptr, *tluIndexArrayUV, \
                                     width, height/2U);
#endif
           }

        }

        /* Bilinear or Nearest Neighbor Interpolation for Chroma components */
        /* Supported formats for Bilinear Interpolation : 420 Chroma, 422 Chroma */
        if (params->interpolationChroma== BILINEAR) {
            /* Bilinear interpolation for U of 422 or UV of 420 */
            bilinearInterpolate_init(src_u, dst_u, outputBlockSize/chromaDiv, *xFracArrayU, *yFracArrayU, \
                        *tluIndexArrayU, (uint8_t *)(void *)s_scatterOffset_chroma, stride_ptr, srcFormat, CHROMA_U_INDEX, mnQShift, oQShift, qScale, \
                        (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);

            if (srcFormat != YUV_420SP)
            {
                /* Bilinear interpolation for V of 422 */
                bilinearInterpolate_init(src_v, dst_v, outputBlockSize/chromaDiv, *xFracArrayV, *yFracArrayV, \
                            *tluIndexArrayV, (uint8_t *)(void *)s_scatterOffset_chroma, stride_ptr, srcFormat, CHROMA_V_INDEX, mnQShift, oQShift, qScale, \
                            (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);
            }
        }
        /* Supported formats for Nearest Neighbor Interpolation : 420 Chroma, 422 Chroma*/
        else {
            /* Nearest neighbor interpolation for U of 422 or UV of 420 */
            nnInterpolate_init(src_u, dst_u, outputBlockSize/chromaDiv, *xFracArrayU, *yFracArrayU, \
                    *tluIndexArrayU,  *scattered_ofst, stride_ptr, srcFormat, CHROMA_U_INDEX, params->maps.qShift, \
                    (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);

            if (srcFormat != YUV_420SP)
            {
                /* Nearest neighbor interpolation for V of 422  */
                nnInterpolate_init(src_v, dst_v, outputBlockSize/chromaDiv, *xFracArrayV, *yFracArrayV, \
                        *tluIndexArrayV,  *scattered_ofst, stride_ptr, srcFormat, CHROMA_V_INDEX, params->maps.qShift, \
                        (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, params, context);
            }

        }
    }

#if (!VCOP_HOST_EMULATION)
    if ((*(context->pblockRunningMem) > (*((uint16_t (*)[])((void *)context->pblockMem)) + (context->pblockSize>>1)))
        || (context->pBlockIdx != context->numPblocks))
    {
        status= -1;
    }
#endif
    return status;
}


/* Initialization function for Nearest neighbor Interpolation */
static void nnInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t outputBlockSize, uint8_t *xFracArray, uint8_t *yFracArray, \
        uint16_t *tluIndexArray,  uint8_t *scattered_ofst, uint16_t *src_stride_ptr, Format format, uint8_t yuvComponent, uint8_t QShift, \
        uint8_t *scratchWbuf, uint8_t *scratchIbuf, const RemapParms *params, VcopRemapContext *context){

    uint16_t *pblock;
    uint8_t  *tluFracArray = (uint8_t *)(*((uint16_t (*)[])((void *)tluIndexArray)) + outputBlockSize);

    if (yuvComponent == LUMA_INDEX) {
         /* format = YUV_420SP or U8 or S8, same kernel used for 420 luma and 8 bit format */
        if ((format== S8BIT) || (format== U8BIT) || (format== YUV_420SP)) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate8b_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_nnInterpolate8b_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 420 luma or 8 bit format */
            vcop_nnInterpolate8b_init(src, dst, outputBlockSize, tluIndexArray, tluFracArray, (uint16_t*)(void *)scratchWbuf, src_stride_ptr, QShift,\
                    params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);
#else
            vcop_nnInterpolate8b(src, dst, outputBlockSize, tluIndexArray, tluFracArray, (uint16_t*)scratchWbuf, src_stride_ptr, QShift,\
                    params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
    }
    /* Chroma Component */
    else {
        if (format == YUV_420SP) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate420SPchromaBB_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_nnInterpolate420SPchromaBB_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 420 chroma */
            vcop_nnInterpolate420SPchromaBB_init(src, dst, outputBlockSize, tluIndexArray, \
                            params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);
#else
            vcop_nnInterpolate420SPchromaBB(src, dst, outputBlockSize, tluIndexArray, \
                            params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
        else if ((format== YUV_422ILE) || (format== YUV_422IBE)) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate422IchromaBB_param_count());

            context->vloopFuncList[context->pBlockIdx]= &vcop_nnInterpolate422IchromaBB_vloops;
            context->pblockList[context->pBlockIdx]   = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 422 chroma */
            vcop_nnInterpolate422IchromaBB_init(src, dst, outputBlockSize, tluIndexArray, \
                    (uint8_t*)scratchIbuf, (uint8_t*)scattered_ofst, \
                    params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);
#else
            vcop_nnInterpolate422IchromaBB(src, dst, outputBlockSize, tluIndexArray, \
                    (uint8_t*)scratchIbuf, (uint8_t*)scattered_ofst, \
                    params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
        else
        {
            /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
        }

    }
}

/* Initialization function for Bilinear Interpolation */
static void bilinearInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t outputBlockSize, uint8_t *xFracArray, uint8_t *yFracArray, \
        uint16_t *tluIndexArray,  uint8_t *scattered_ofst, uint16_t *src_stride_ptr, Format format, uint8_t yuvComponent, \
        uint8_t mnQShift, uint8_t oQShift, uint16_t qScale, uint8_t *scratchWbuf, uint8_t *scratchIbuf,
        const RemapParms *params, VcopRemapContext *context){

    uint16_t *pblock, max_src_size;
    uint8_t  *tluFracArray = (uint8_t *)(*((uint16_t (*)[])((void *)tluIndexArray)) + outputBlockSize);

    if (yuvComponent == LUMA_INDEX) {

        if ((format== S16BIT) || (format== U16BIT)) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolate16b_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolate16b_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 16 bit format */
            vcop_bilinearInterpolate16b_init((uint16_t*)(void *)src, (uint16_t*)(void *)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)(void *)scattered_ofst, (uint16_t*)(void *)scratchIbuf, (uint16_t*)(void *)scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);

#else
            vcop_bilinearInterpolate16b((uint16_t*)src, (uint16_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)scattered_ofst, (uint16_t*)scratchIbuf, (uint16_t*)scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        }
        else if ((format== YUV_422ILE) || (format== YUV_422IBE)) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV422Iluma_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolateYUV422Iluma_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 422 luma */
            vcop_bilinearInterpolateYUV422Iluma_init((uint8_t*)(void *)src, (uint8_t*)(void *)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)(void *)scattered_ofst, (uint16_t*)(void *)scratchIbuf, scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);
#else
            vcop_bilinearInterpolateYUV422Iluma((uint8_t*)src, (uint8_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)scattered_ofst, (uint16_t*)scratchIbuf, scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        } else { /* format = YUV_420SP or U8 or S8, same kernel used for 420 luma and 8 bit format */

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolate8b_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolate8b_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 420 luma or 8 bit format */
            vcop_bilinearInterpolate8b_init((uint8_t*)src, (uint8_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)(void *)scattered_ofst, (uint16_t*)(void *)scratchIbuf, scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);

#else
            vcop_bilinearInterpolate8b((uint8_t*)src, (uint8_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, tluFracArray, \
                    (uint16_t*)scattered_ofst, (uint16_t*)scratchIbuf, scratchWbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        }
    }
    /* Chroma Component */
    else {
        if ((format== YUV_422ILE) || (format== YUV_422IBE)) {
            max_src_size = 128U*128U;
#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV422Ichroma_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolateYUV422Ichroma_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 422 Chroma */
            vcop_bilinearInterpolateYUV422Ichroma_init((uint8_t*)src, (uint8_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, \
                    xFracArray, yFracArray, (uint16_t*)(void *)scattered_ofst, (uint16_t*)(void *)scratchWbuf, scratchIbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, max_src_size, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);
#else
            vcop_bilinearInterpolateYUV422Ichroma((uint8_t*)src, (uint8_t*)dst, outputBlockSize, outputBlockSize, tluIndexArray, \
                    xFracArray, yFracArray, (uint16_t*)scattered_ofst, (uint16_t*)scratchWbuf, scratchIbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, max_src_size, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        }
        else if (format== YUV_420SP) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV420SPchromaBB_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolateYUV420SPchromaBB_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pBlockIdx++;

            /* Initialize kernel for 420 Chroma */
            vcop_bilinearInterpolateYUV420SPchromaBB_init((uint8_t*)src, (uint8_t*)dst, outputBlockSize, xFracArray, yFracArray, tluIndexArray, (uint16_t*)(void *)scratchWbuf, scratchIbuf, src_stride_ptr, \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set,  pblock);
#else
            vcop_bilinearInterpolateYUV420SPchromaBB((uint8_t*)src, (uint8_t*)dst, outputBlockSize, xFracArray, yFracArray, tluIndexArray, (uint16_t*)scratchWbuf, scratchIbuf, src_stride_ptr, \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
        else
        {
            /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
        }

    }
}

/* Function to deinterleave luma and chroma */
static void deInterleaveYUV422I_init(uint8_t *src, uint8_t *dst, uint8_t *dst_u, uint8_t *dst_v, uint16_t size, Format dstFormat, VcopRemapContext *context){

#if (!VCOP_HOST_EMULATION)
    uint16_t *pblock;

    pblock = (uint16_t *)*(context->pblockRunningMem);

    if (dstFormat== YUV_422IBE){
        context->vloopFuncList[context->pBlockIdx]= &vcop_deInterleaveYUV422IBE_vloops;
        context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_deInterleaveYUV422IBE_param_count());
    }
    else {
        context->vloopFuncList[context->pBlockIdx]= &vcop_deInterleaveYUV422ILE_vloops;
        context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_deInterleaveYUV422ILE_param_count());
    }
    context->pblockList[context->pBlockIdx] = pblock;
    context->pBlockIdx++;
#endif

    if (dstFormat== YUV_422IBE) {
#if (!VCOP_HOST_EMULATION)
        vcop_deInterleaveYUV422IBE_init(src, dst, dst_u, dst_v, size, pblock);
#else
        vcop_deInterleaveYUV422IBE(src, dst, dst_u, dst_v, size);
#endif
    } else {
#if (!VCOP_HOST_EMULATION)
        vcop_deInterleaveYUV422ILE_init(src, dst, dst_u, dst_v, size, pblock);
#else
        vcop_deInterleaveYUV422ILE(src, dst, dst_u, dst_v, size);
#endif
    }
}

/* Function triggering the vloops function for a given input */
int32_t vcop_remap_bb_approach(
        VcopRemapContext *context
){
    uint32_t i;

    for (i=0;i<context->numPblocks;i++) {
        context->vloopFuncList[i](context->pblockList[i]);
    }

    return 0;
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
