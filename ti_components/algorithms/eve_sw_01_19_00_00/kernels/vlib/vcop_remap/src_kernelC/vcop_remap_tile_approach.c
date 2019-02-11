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
#include "vcop_bilinearInterpolateLumaPblockUpdate.h"
#include "vcop_chromaTLUIndexCalcPblockUpdate.h"
#include "vcop_nnInterpolate420SPchromaPblockUpdate.h"
#include "vcop_bilinearInterpolateYUV420SPchromaPblockUpdate.h"
#include "vcop_dsTLUindexAndFracPblockUpdate.h"
#include "vcop_nnInterpolate422IchromaPblockUpdate.h"
#include "vcop_bilinearInterpolateYUV422IchromaPblockUpdate.h"

#define LUMA_INDEX      (0U)
#define CHROMA_U_INDEX  (1U)
#define CHROMA_V_INDEX  (2U)
#define CHROMA_UV_INDEX (1U)


/* VCOP kernel initialization functions for bilinear, nearest neighbor interpolation methods and deinterleave of chroma and luma */
static void bilinearInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t maxOutputBlockSize, \
        uint16_t *numMappedPixels_ptr, uint16_t *numRestMappedPixels_ptr, uint8_t *xFracArray, uint8_t *yFracArray, \
        uint16_t *tluIndexArray,  uint16_t *tluScOffsetArray, uint8_t *scattered_ofst, uint8_t src_stride, \
        uint16_t *src_stride_ptr, Format format, uint8_t yuvComponent, \
        uint8_t mnQShift, uint8_t oQShift, uint16_t qScale, uint8_t *scratchWbuf, uint8_t *scratchIbuf, \
        uint16_t dst_end_offset, uint16_t inputTileSize, const RemapParms *params, VcopRemapContext *context);

static void nnInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t maxOutputBlockSize, \
        uint16_t *numMappedPixels_ptr, uint16_t *numRestMappedPixels_ptr, uint8_t *xFracArray, uint8_t *yFracArray, \
        uint16_t *tluIndexArray,  uint16_t *tluScOffsetArray, uint8_t src_stride, Format format, uint8_t yuvComponent, \
        uint8_t QShift, uint8_t *scratchWbuf, uint8_t *scratchIbuf, uint16_t dst_end_offset, uint16_t inputTileSize, \
        const RemapParms *params, VcopRemapContext *context);

static void deInterleaveYUV422I_init(uint8_t *src, uint8_t *dst, uint8_t *dst_u, uint8_t *dst_v, uint16_t size, \
        Format dstFormat, VcopRemapContext *context);

/* Dummy function */
static inline void vcop_remap_dummy(uint16_t* pblock)
{
}


/* Function initializing the kernel init functions for each scenario of remap function */
int32_t vcop_remap_tile_approach_init(
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
    uint8_t  *xFracArrayU = NULL, *xFracArrayV = NULL, *yFracArrayU = NULL, *yFracArrayV = NULL, *xFracArrayUV = NULL, *yFracArrayUV = NULL;
    uint8_t  *src, *src_y, *src_u, *src_v, *src_uv, *dst, *dst_y, *dst_uv, *dst_u, *dst_v, *scratch_y, *scratch_u, *scratch_v;
    uint8_t   mnQShift, oQShift, src_stride;
    uint16_t *tluIndexArray, *tluIndexArrayU, *tluIndexArrayV, *tluIndexArrayUV, *pblock, *pblockupdate, *src_stride_ptr, *src_chroma_stride_ptr;
    uint16_t  qScale, chromaDiv, outputBlockSize, dst_end_offset = 0, width, height, srcSize;
    Format    srcFormat;
    uint8_t  *tluFracArray;
    uint16_t   tileWidth, tileHeight, inputTileSize, numMappedPixels, numEvenMappedPixels;
    uint16_t   numOddMappedPixels, maxNumPixelsinTile, maxNumEvenPixelsinTile, src_stride_q16, output_stride_q16, maxNumOddPixelsinTile;
    uint16_t  *tluScOffsetArray, *tluScOffsetArrayUV, *tluScOffsetArrayU, *tluScOffsetArrayV, *numMappedPixels_ptr, *numOddMappedPixels_ptr;
    uint16_t  *numEvenMappedPixels_ptr;
    sTileLutHeader *lutHeader;
    uint8_t  (*scattered_ofst)[];
    int32_t   status= 0;


    width     = params->maps.outputBlockDim.width;
    height    = params->maps.outputBlockDim.height;
    srcFormat = params->maps.srcFormat;
    outputBlockSize= width*height;
    srcSize   = sizeofFormat(srcFormat);

    tileWidth        = params->maps.inputTileDim.width;
    tileHeight       = params->maps.inputTileDim.height;
    inputTileSize    = (tileWidth + HORZ_TILE_PADDING) * (tileHeight + VERT_TILE_PADDING);

    maxNumPixelsinTile      = params->maps.maxNumPixelsinTile;
    maxNumEvenPixelsinTile  = params->maps.maxNumEvenPixelsinTile;
    maxNumOddPixelsinTile   = params->maps.maxNumOddPixelsinTile;

    /* The LUT is 32B aligned. Hence the header is just above it. blockInfoPtr is also 32B aligned. */
    lutHeader               = (sTileLutHeader *)(blockInfoPtr + (32 - sizeof(sTileLutHeader)));
    numMappedPixels_ptr     = (uint16_t *)&(lutHeader->numPixels);
    numEvenMappedPixels_ptr = (uint16_t *)&(lutHeader->numEvenPixels);
    numOddMappedPixels_ptr  = (uint16_t *)&(lutHeader->numOddPixels);

    numMappedPixels     = lutHeader->numPixels;
    numEvenMappedPixels = lutHeader->numEvenPixels;

    tluIndexArray    = (uint16_t *)(*((sTileLutHeader (*)[])((void *)lutHeader)) + 1);
    tluFracArray     = (uint8_t  *)(*((uint16_t (*)[])((void *)tluIndexArray)) + ALIGN_TLU((uint32_t)maxNumPixelsinTile));
    tluScOffsetArray = (uint16_t *)(*((uint8_t  (*)[])((void *)tluFracArray))   + ALIGN_TLU((uint32_t)maxNumPixelsinTile));

    context->pBlockIdx= 0;
    context->pblockRunningMem= (uint16_t (*)[])(void *)context->pblockMem;

    /* Partitioning Scratch Memory for Chroma components to be fed into the Kernels */
    if (srcFormat== YUV_420SP) {

        /* tluIndexArrayU/V is memory needed to store TLU Index for Chroma calculated on the fly (in WBUF) */
        /* The Chroma TLU Index Calculate kernel will populate this memory */
        tluIndexArrayUV = (uint16_t *)ChromaTLUIndexPtr;
        tluIndexArrayU  = tluIndexArrayUV;
        tluIndexArrayV  = tluIndexArrayU;

        tluScOffsetArrayUV  = (uint16_t*)(*((uint16_t (*)[])((void *)tluIndexArrayV)) + ALIGN_2SIMD((uint32_t)maxNumEvenPixelsinTile));
        tluScOffsetArrayU   = tluScOffsetArrayUV;
        tluScOffsetArrayV   = tluScOffsetArrayUV;

        /* x/yFracArrayUV is memory needed to store TLU Fractional for Chroma (calculated on the fly) */
        /* The Down Sampling TLU Index and Fractional kernel will populate this memory */
        if (params->interpolationChroma== BILINEAR) {
            xFracArrayUV = (uint8_t*)(*((uint16_t (*)[])((void *)tluScOffsetArrayV)) + ALIGN_2SIMD((uint32_t)maxNumEvenPixelsinTile) + 32U);
            yFracArrayUV = (uint8_t*)(*((uint8_t (*)[])((void *)xFracArrayUV)) + ALIGN_2SIMD((uint32_t)maxNumEvenPixelsinTile));
        } else {
            xFracArrayUV = NULL;
            yFracArrayUV = NULL;
        }
        xFracArrayU = xFracArrayUV;
        xFracArrayV = xFracArrayUV;
        yFracArrayU = yFracArrayUV;
        yFracArrayV = yFracArrayUV;

        scattered_ofst   = (uint8_t (*)[])scatteredOffsetPtr;
        (*scattered_ofst)[0]= 0;  (*scattered_ofst)[1]= (uint8_t)1U;  (*scattered_ofst)[2]= 0;  (*scattered_ofst)[3]= (uint8_t)1U;
        (*scattered_ofst)[4]= 0;  (*scattered_ofst)[5]= (uint8_t)1U;  (*scattered_ofst)[6]= 0;  (*scattered_ofst)[7]= (uint8_t)1U;

    }
    else if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE)) {

        scattered_ofst = NULL;

        /* tluIndexArrayU/V is memory needed to store TLU Index for Chroma (calculated on the fly) */
        /* The Down Sampling TLU Index and Fractional kernel will populate this memory */
        tluIndexArrayU= (uint16_t*)(ChromaTLUIndexPtr);

        numOddMappedPixels = numMappedPixels - numEvenMappedPixels;

        tluIndexArrayV  = (uint16_t*)(*((uint16_t (*)[])((void *)tluIndexArrayU)) + ALIGN_2SIMD(maxNumEvenPixelsinTile));
        if (params->interpolationChroma== BILINEAR) {
            xFracArrayU     = (uint8_t*)(*((uint16_t (*)[])((void *)tluIndexArrayV)) + ALIGN_2SIMD(maxNumOddPixelsinTile));
            xFracArrayV     = (uint8_t*)(*((uint8_t (*)[])((void *)xFracArrayU))     + ALIGN_2SIMD(maxNumEvenPixelsinTile));
            yFracArrayU     = (uint8_t*)(*((uint8_t (*)[])((void *)xFracArrayV))     + ALIGN_2SIMD(maxNumOddPixelsinTile));
            yFracArrayV     = (uint8_t*)(*((uint8_t (*)[])((void *)yFracArrayU))     + ALIGN_2SIMD(maxNumEvenPixelsinTile));
        } else {
            xFracArrayU     = NULL;
            xFracArrayV     = NULL;
            yFracArrayU     = NULL;
            yFracArrayV     = NULL;
        }
        tluScOffsetArrayUV  = tluScOffsetArray;
        tluScOffsetArrayU   = tluScOffsetArrayUV;
#if (!VCOP_HOST_EMULATION)
        tluScOffsetArrayV   = tluScOffsetArrayUV;
#else
        tluScOffsetArrayV   = tluScOffsetArray + numEvenMappedPixels;
#endif

    }
    else
    {
        /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
    }


    src_stride  = (uint8_t)(tileWidth + HORZ_TILE_PADDING);
    /* src_stride not being a divisor of 2^16 leads to quantization error. It matters during TLUchroma calculation.
            TLUluma = i + j*src_stride. In cases when i = 0, TLUchroma computation results in chroma-i = stride and
            chroma-j = j-1. This along with the offset calculation based on i,j being odd/even creates a problem.
            To avoid this, ceil is done. ceil will work as long as stride < 56. For values >=56, quantization
            issues are observed for i = 55. */
    src_stride_q16    = (uint16_t)((((uint32_t)1 << 16U) + ((uint32_t)src_stride - 1U))/(uint32_t)src_stride); /* ceil((1<<16)/src_stride) */
    /* The above stated issue is observed for output chroma Scatter store calculation too. But i = stride, in this case
            simply points to i = 0 of the next row. Hence ceil is not needed here. */
    output_stride_q16 = (uint16_t)(((uint32_t)1 << 16U)/width);

    /* In Tile, the input stride was passed as unsigned short as it is a constant whereas in BB, the
            pointer to the stride is passed. To use the same kernel across BB and Tile, we need to pass stride
            to the kernel as a pointer. Hence we allocate the below memory to store stride. */
    src_stride_ptr = (uint16_t *)(interpolationBuf0Ptr + ((uint16_t)2 * (uint16_t)sizeof(uint16_t) * (uint16_t)ALIGN_2SIMD((uint32_t)maxNumPixelsinTile)));
    src_chroma_stride_ptr = (uint16_t*)(*((uint16_t (*)[])((void *)src_stride_ptr)) + 1);
    *(src_stride_ptr) = src_stride;


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
    src    = (uint8_t*)(inputImagePtr);
    src_uv = (uint8_t*)(*((uint8_t (*)[])((void *)src)) + ALIGN_TLU((uint32_t)inputTileSize));

    /* dst, dst_uv points to Remapped output Luma and Chroma block respectively (in IBUFH) */
    dst    = outputPtr;
    dst_uv = (uint8_t*)(*((uint8_t (*)[])((void *)dst)) + outputBlockSize);

     /* For 422, the Input Image block is De-interleaved and Y, U, V is stored into separate scratch buffers, each 32 bytes aligned in IBUFH */
    if ((srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE)) {
        scratch_y= (uint8_t*)src;
        scratch_u= (uint8_t*)chromaUVPtr;

        /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* This is required for pointer alignment to word/double_word boundary and can be waived.  */
        scratch_v= (uint8_t*)ALIGN_4SIMD((uintptr_t)chromaUVPtr + ALIGN_SIMD(((uint32_t)inputTileSize/2U) + 7U));
        /* RESET_MISRA("10.3")  -> Reset rule 10.3     */
        /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

        /* Initialize the Deinterleave kernel for 422 */
        deInterleaveYUV422I_init(src, scratch_y, scratch_u, scratch_v, inputTileSize, srcFormat, context);

    }

    /* Set src, dst for Y, U and V for all formats */
    if (srcFormat== YUV_422ILE) {
        src_y= scratch_y;
        src_u= scratch_u;
        src_v= scratch_v;
        dst_y= (uint8_t*)(*((uint8_t (*)[])((void *)dst)) + 1);
        dst_u= dst;
        dst_v= dst_u;
    }
    else if (srcFormat== YUV_422IBE) {
        src_y= scratch_y;
        src_u= scratch_u;
        src_v= scratch_v;
        dst_y= dst;
        dst_u= (uint8_t*)(*((uint8_t (*)[])((void *)dst)) + 1);
        dst_v= dst_u;
    }
    else { /* U8, U16, 420. For U8 and U16, src, dst for U, V is not used */
        src_y= src;
        src_u= src_uv;
        src_v= (uint8_t*)(*((uint8_t (*)[])((void *)src_uv)) + 1);
        dst_y= dst;
        dst_u= dst_uv;
        dst_v= (uint8_t*)(*((uint8_t (*)[])((void *)dst_uv)) + 1);
    }


    /* Bilinear or Nearest Neighbor Interpolation for Luma components */
    /* Supported formats for Bilinear Interpolation : U8, S8, U16, S16, 420 Luma, 422 Luma */
    if (params->interpolationLuma== BILINEAR) {

        bilinearInterpolate_init(src_y, dst_y, maxNumPixelsinTile, numMappedPixels_ptr, NULL, tluFracArray, NULL, \
                tluIndexArray, tluScOffsetArray, NULL, src_stride, src_stride_ptr, srcFormat, LUMA_INDEX, mnQShift, oQShift, qScale, \
                (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);
    }
    /* Supported formats for Nearest Neighbor Interpolation : U8, S8, 420 Luma */
    else {

        nnInterpolate_init(src_y, dst_y, maxNumPixelsinTile, numMappedPixels_ptr, NULL, tluFracArray, NULL, \
                tluIndexArray, tluScOffsetArray, src_stride, srcFormat, LUMA_INDEX, params->maps.qShift, \
                (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);
    }


    /* For Formats with Chroma components */
    if ((srcFormat == YUV_422ILE) || (srcFormat == YUV_422IBE) || (srcFormat == YUV_420SP)) {

        /* Pre-Interpolation of Chroma, On the Fly TLU Calculation for Chroma components is done below */
        /* For 422, Down Sampling TLU Index and Fractional kernel is initialized */
        if ((srcFormat == YUV_422ILE) || (srcFormat == YUV_422IBE)) {
            chromaDiv = 2U;
            *(src_chroma_stride_ptr) = src_stride/chromaDiv;

            /* reusing luma tlu index memory (in IBUFL) as scratch buffer for Chroma Interpolation */
            interpolationBuf1Ptr = (uint8_t *)(void *)tluIndexArray;

            if (params->interpolationChroma== BILINEAR) {
#if (!VCOP_HOST_EMULATION)
                pblockupdate = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_param_count());
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracBilInterpolate_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_dsTLUindexAndFracBilInterpolate_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops;
                context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
                context->pBlockIdx++;

                vcop_dsTLUindexAndFracBilInterpolate_init(tluIndexArray, tluFracArray, numEvenMappedPixels, numOddMappedPixels, xFracArrayU, yFracArrayU, \
                    tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, params->maps.qShift, pblock);

                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* Pointers need to be converted to integers for arithematic computation within the kernel. */
                vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, \
                    (uint16_t *)pblock, (uint32_t )tluIndexArray, (uint32_t )tluFracArray, (uint32_t *)(void *)pblock, pblockupdate);
                /* RESET_MISRA("11.3")  -> Reset rule 11.3     */
#else
                vcop_dsTLUindexAndFracBilInterpolate(tluIndexArray, tluFracArray, numEvenMappedPixels, numOddMappedPixels, xFracArrayU, yFracArrayU, \
                    tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, params->maps.qShift);
#endif
            } else { /* NN Chroma Interpolation */
#if (!VCOP_HOST_EMULATION)
                pblockupdate = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_param_count());
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_dsTLUindexAndFracNNInterpolate_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_dsTLUindexAndFracNNInterpolate_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops;
                context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
                context->pBlockIdx++;

                vcop_dsTLUindexAndFracNNInterpolate_init(tluIndexArray, tluFracArray, numEvenMappedPixels, numOddMappedPixels, tluIndexArrayU, \
                                                         tluIndexArrayV, src_stride, params->maps.qShift, pblock);

                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* Pointers need to be converted to integers for arithematic computation within the kernel. */
                vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, \
                    (uint16_t *)pblock, (uint32_t )tluIndexArray, (uint32_t )tluFracArray, (uint32_t *)(void *)pblock, pblockupdate);
                /* RESET_MISRA("11.3")  -> Reset rule 11.3     */
#else
                vcop_dsTLUindexAndFracNNInterpolate(tluIndexArray, tluFracArray, numEvenMappedPixels, numOddMappedPixels, tluIndexArrayU, \
                                                         tluIndexArrayV, src_stride, params->maps.qShift);
#endif
            }
        }
        /* For 420, Chroma TLU Index Calculate kernel is initialized */
        else {
            chromaDiv = 1U;

            if (params->interpolationChroma== BILINEAR) {
#if (!VCOP_HOST_EMULATION)
                pblockupdate = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_param_count());
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcBilInterpolate_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_chromaTLUIndexCalcBilInterpolate_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops;
                context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
                context->pBlockIdx++;

                vcop_chromaTLUIndexCalcBilInterpolate_init(tluIndexArray, tluFracArray, tluScOffsetArray, numEvenMappedPixels, (uint16_t)src_stride, \
                                     src_stride_q16, width, output_stride_q16, tluIndexArrayUV, xFracArrayUV, yFracArrayUV, tluScOffsetArrayUV, params->maps.qShift, pblock);

                vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init(numEvenMappedPixels_ptr, pblock, pblockupdate);

#else
                vcop_chromaTLUIndexCalcBilInterpolate(tluIndexArray, tluFracArray, tluScOffsetArray, numEvenMappedPixels, src_stride, \
                                     src_stride_q16, width, output_stride_q16, tluIndexArrayUV, xFracArrayUV, yFracArrayUV, tluScOffsetArrayUV, params->maps.qShift);

#endif
           } else { /* NN Chroma Interpolation */
#if (!VCOP_HOST_EMULATION)
                pblockupdate = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_param_count());
                pblock = (uint16_t *)*(context->pblockRunningMem);
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_chromaTLUIndexCalcNNInterpolate_param_count());

                context->vloopFuncList[context->pBlockIdx] = &vcop_chromaTLUIndexCalcNNInterpolate_vloops;
                context->pblockList[context->pBlockIdx]    = pblock;
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops;
                context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
                context->pBlockIdx++;

                vcop_chromaTLUIndexCalcNNInterpolate_init(tluIndexArray, tluScOffsetArray, numEvenMappedPixels, (uint16_t)src_stride, src_stride_q16, \
                                     width, output_stride_q16, tluIndexArrayUV, tluScOffsetArrayUV, pblock);

                vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init(numEvenMappedPixels_ptr, pblock, pblockupdate);

#else
                vcop_chromaTLUIndexCalcNNInterpolate(tluIndexArray, tluScOffsetArray, numEvenMappedPixels, src_stride, src_stride_q16, \
                                     width, output_stride_q16, tluIndexArrayUV, tluScOffsetArrayUV);
#endif
           }

        }

        if (srcFormat== YUV_420SP) {
            dst_end_offset = (outputBlockSize/2U) + 32U;
        }

        /* Bilinear or Nearest Neighbor Interpolation for Chroma components */
        /* Supported formats for Bilinear Interpolation : 420 Chroma, 422 Chroma */
        if (params->interpolationChroma== BILINEAR) {
            /* Bilinear interpolation for U of 422 or UV of 420 */
            bilinearInterpolate_init(src_u, dst_u, maxNumEvenPixelsinTile, numEvenMappedPixels_ptr, numOddMappedPixels_ptr, xFracArrayU, yFracArrayU, \
                        tluIndexArrayU,  tluScOffsetArrayU, *scattered_ofst, src_stride/(uint8_t)chromaDiv, src_chroma_stride_ptr, srcFormat, CHROMA_U_INDEX, mnQShift, oQShift, qScale, \
                        (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);

            if (srcFormat != YUV_420SP)
            {
                /* Bilinear interpolation for V of 422 */
                bilinearInterpolate_init(src_v, dst_v, maxNumOddPixelsinTile, numOddMappedPixels_ptr, numEvenMappedPixels_ptr, xFracArrayV, yFracArrayV, \
                            tluIndexArrayV,  tluScOffsetArrayV, *scattered_ofst, src_stride/(uint8_t)chromaDiv, src_chroma_stride_ptr, srcFormat, CHROMA_V_INDEX, mnQShift, oQShift, qScale, \
                            (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);
            }
        }
        /* Supported formats for Nearest Neighbor Interpolation : 420 Chroma, 422 Chroma*/
        else {
            /* Nearest neighbor interpolation for U of 422 or UV of 420 */
            nnInterpolate_init(src_u, dst_u, maxNumEvenPixelsinTile, numEvenMappedPixels_ptr, numOddMappedPixels_ptr, xFracArrayU, yFracArrayU, \
                    tluIndexArrayU,  tluScOffsetArrayU, src_stride/(uint8_t)chromaDiv, srcFormat, CHROMA_U_INDEX, params->maps.qShift, \
                    (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);

            if (srcFormat != YUV_420SP)
            {
                /* Nearest neighbor interpolation for V of 422  */
                nnInterpolate_init(src_v, dst_v, maxNumOddPixelsinTile, numOddMappedPixels_ptr, numEvenMappedPixels_ptr, xFracArrayV, yFracArrayV, \
                        tluIndexArrayV,  tluScOffsetArrayV, src_stride/(uint8_t)chromaDiv, srcFormat, CHROMA_V_INDEX, params->maps.qShift, \
                        (uint8_t*)interpolationBuf0Ptr, interpolationBuf1Ptr, dst_end_offset, inputTileSize, params, context);
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
static void nnInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t maxOutputBlockSize, uint16_t *numMappedPixels_ptr, \
        uint16_t *numRestMappedPixels_ptr, uint8_t *xFracArray, uint8_t *yFracArray, uint16_t *tluIndexArray,  uint16_t *tluScOffsetArray, \
        uint8_t src_stride, Format format, uint8_t yuvComponent, uint8_t QShift, uint8_t *scratchWbuf, uint8_t *scratchIbuf, \
        uint16_t dst_end_offset, uint16_t inputTileSize, const RemapParms *params, VcopRemapContext *context){

    uint16_t *pblock, *pblockupdate;
    uint16_t  numMappedPixels = *numMappedPixels_ptr;
    uint8_t  *tluFracArray = (uint8_t *)(*((uint16_t (*)[])((void *)tluIndexArray)) + numMappedPixels);

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
            /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
            /* Integer needs to be converted to pointer for ease of loading value within the kernel. */
            vcop_nnInterpolate8b_init(src, dst, numMappedPixels, tluIndexArray, tluFracArray, (uint16_t*)(void *)scratchWbuf, (uint16_t*)src_stride, \
                    QShift, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);
            /* RESET_MISRA("11.3")  -> Reset rule 11.3     */
#else
            vcop_nnInterpolate8b(src, dst, numMappedPixels, tluIndexArray, tluFracArray, (uint16_t*)scratchWbuf, (uint16_t*)src_stride, QShift,\
                    params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
    }
    /* Chroma Component */
    else {
        if (format == YUV_420SP) {

#if (!VCOP_HOST_EMULATION)
            pblockupdate = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate420SPchromaPblockUpdate_param_count());
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate420SPchroma_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_nnInterpolate420SPchroma_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_nnInterpolate420SPchromaPblockUpdate_vloops;
            context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
            context->pBlockIdx++;

            /* Initialize kernel for 420 chroma */
            vcop_nnInterpolate420SPchroma_init(src, (uint16_t*)(void *)dst, numMappedPixels, tluIndexArray, tluScOffsetArray, (uint8_t*)scratchIbuf, \
                            (uint16_t*)(void *)scratchIbuf, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, dst_end_offset, pblock);

            /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
            /* Pointers need to be converted to integers for arithematic computation within the kernel. */
            vcop_nnInterpolate420SPchromaPblockUpdate_init(numMappedPixels_ptr, (uint16_t *)pblock, (uint32_t )tluScOffsetArray, \
                            (uint32_t *)(void *)pblock, pblockupdate);
            /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

#else
            vcop_nnInterpolate420SPchroma(src, (uint16_t*)dst, numMappedPixels, tluIndexArray, tluScOffsetArray, (uint8_t*)scratchIbuf, \
                            (uint16_t*)scratchIbuf, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, dst_end_offset);
#endif
        }
        else if ((format== YUV_422ILE) || (format== YUV_422IBE)) {

#if (!VCOP_HOST_EMULATION)
            pblockupdate = (uint16_t *)*(context->pblockRunningMem);
            if (yuvComponent == CHROMA_U_INDEX) {
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate422IchromaUPblockUpdate_param_count());
            } else if (yuvComponent == CHROMA_V_INDEX) {
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate422IchromaVPblockUpdate_param_count());
            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_nnInterpolate422Ichroma_param_count());

            context->vloopFuncList[context->pBlockIdx]= &vcop_nnInterpolate422Ichroma_vloops;
            context->pblockList[context->pBlockIdx]   = pblock;
            if (yuvComponent == CHROMA_U_INDEX) {
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_nnInterpolate422IchromaUPblockUpdate_vloops;
            } else if (yuvComponent == CHROMA_V_INDEX) {
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_nnInterpolate422IchromaVPblockUpdate_vloops;
            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }

            context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
            context->pBlockIdx++;

            /* Initialize kernel for 422 chroma */
            vcop_nnInterpolate422Ichroma_init(src, dst, numMappedPixels, tluIndexArray, tluScOffsetArray, (uint8_t*)scratchIbuf, \
                    inputTileSize, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);

            if (yuvComponent == CHROMA_U_INDEX) {
                vcop_nnInterpolate422IchromaUPblockUpdate_init(numMappedPixels_ptr, (uint16_t *)pblock, pblockupdate);
            } else if (yuvComponent == CHROMA_V_INDEX) {
                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* Pointers need to be converted to integers for arithematic computation within the kernel. */
                vcop_nnInterpolate422IchromaVPblockUpdate_init(numMappedPixels_ptr, numRestMappedPixels_ptr, (uint16_t *)pblock, \
                    (uint32_t)tluScOffsetArray, (uint32_t *)(void *)pblock, pblockupdate);
                /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }


#else
            vcop_nnInterpolate422Ichroma(src, dst, numMappedPixels, tluIndexArray, tluScOffsetArray, (uint8_t*)scratchIbuf, \
                    inputTileSize, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
        else
        {
            /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
        }
    }
}

/* Initialization function for Bilinear Interpolation */
static void bilinearInterpolate_init(uint8_t *src, uint8_t *dst, uint16_t maxOutputBlockSize, uint16_t *numMappedPixels_ptr, \
        uint16_t *numRestMappedPixels_ptr, uint8_t *xFracArray, uint8_t *yFracArray, uint16_t *tluIndexArray,  \
        uint16_t *tluScOffsetArray, uint8_t *scattered_ofst, uint8_t src_stride, uint16_t *src_stride_ptr, Format format, uint8_t yuvComponent, \
        uint8_t mnQShift, uint8_t oQShift, uint16_t qScale, uint8_t *scratchWbuf, uint8_t *scratchIbuf, \
        uint16_t dst_end_offset, uint16_t inputTileSize, const RemapParms *params, VcopRemapContext *context){

    uint16_t *pblock, *pblockupdate;
    uint8_t  *tluFracArray = xFracArray;
    uint16_t  numMappedPixels = *numMappedPixels_ptr;

    if (yuvComponent == LUMA_INDEX) {

        if ((format== S16BIT) || (format== U16BIT)) {

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolate16b_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolate16b_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;

            /* Initialize kernel for 16 bit format */
            vcop_bilinearInterpolate16b_init((uint16_t*)(void *)src, (uint16_t*)(void *)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)(void *)scratchWbuf,  (uint16_t*)(void *)scratchIbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);
#else
            vcop_bilinearInterpolate16b((uint16_t*)src, (uint16_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)scratchWbuf,  (uint16_t*)scratchIbuf, src_stride_ptr,  \
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

            /* Initialize kernel for 422 luma */
            vcop_bilinearInterpolateYUV422Iluma_init((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)(void *)scratchWbuf, (uint8_t*)scratchIbuf, src_stride_ptr, \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);
#else
            vcop_bilinearInterpolateYUV422Iluma((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)scratchWbuf, (uint8_t*)scratchIbuf, src_stride_ptr, \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        } else { /* format = YUV_420SP or U8 or S8, same kernel used for 420 luma and 8 bit format */

#if (!VCOP_HOST_EMULATION)
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolate8b_param_count());

            context->vloopFuncList[context->pBlockIdx]            = &vcop_bilinearInterpolate8b_vloops;
            context->pblockList[context->pBlockIdx]               = pblock;

            /* Initialize kernel for 420 luma or 8 bit format */
            vcop_bilinearInterpolate8b_init((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)(void *)scratchWbuf, scratchIbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set, pblock);
#else
            vcop_bilinearInterpolate8b((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, tluFracArray, \
                    tluScOffsetArray, (uint16_t*)scratchWbuf, scratchIbuf, src_stride_ptr,  \
                    mnQShift, oQShift, qScale, params->rightShift, params->sat_high, params->sat_high_set,\
                    params->sat_low, params->sat_low_set);
#endif
        }

#if (!VCOP_HOST_EMULATION)
        /* Enable the pBlockUpdate kernel for Luma Bilinear Interpolation. This is needed because numMappedPixels is a variable. */
        pblockupdate = (uint16_t *)*(context->pblockRunningMem);
        context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateLumaPblockUpdate_param_count());

        context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_bilinearInterpolateLumaPblockUpdate_vloops;
        context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
        context->pBlockIdx++;

        vcop_bilinearInterpolateLumaPblockUpdate_init(numMappedPixels_ptr, pblock, pblockupdate);
#endif
    }
    /* Chroma Component */
    else {
        if ((format== YUV_422ILE) || (format== YUV_422IBE)) {

#if (!VCOP_HOST_EMULATION)
            pblockupdate = (uint16_t *)*(context->pblockRunningMem);
            if (yuvComponent == CHROMA_U_INDEX) {
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_param_count());
            } else if (yuvComponent == CHROMA_V_INDEX) {
                context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_param_count());
            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }

            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV422Ichroma_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolateYUV422Ichroma_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            if (yuvComponent == CHROMA_U_INDEX) {
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_vloops;
            } else if (yuvComponent == CHROMA_V_INDEX) {
                context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_vloops;
            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }

            context->pblockUpdatePblockList[context->pBlockIdx] = pblockupdate;
            context->pBlockIdx++;

            /* Initialize kernel for 422 Chroma */
            vcop_bilinearInterpolateYUV422Ichroma_init((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, \
                    xFracArray, yFracArray, tluScOffsetArray, (uint16_t*)(void *)scratchWbuf, scratchIbuf, src_stride_ptr, mnQShift, oQShift, qScale, \
                    params->rightShift, inputTileSize, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, pblock);

            if (yuvComponent == CHROMA_U_INDEX) {
                vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_init(numMappedPixels_ptr, (uint16_t *)pblock, pblockupdate);
            } else if (yuvComponent == CHROMA_V_INDEX) {
                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* Pointers need to be converted to integers for arithematic computation within the kernel. */
                vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_init(numMappedPixels_ptr, numRestMappedPixels_ptr, (uint16_t *)pblock, \
                    (uint32_t)tluScOffsetArray, (uint32_t *)(void *)pblock, pblockupdate);
                /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

            }
            else
            {
                /* The else is added to avoid MISRA RULE 14.10 MISRA.IF.NO_ELSE. */
            }

#else
            vcop_bilinearInterpolateYUV422Ichroma((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, \
                    xFracArray, yFracArray, tluScOffsetArray, (uint16_t*)scratchWbuf, scratchIbuf, src_stride_ptr, mnQShift, oQShift, qScale, \
                    params->rightShift, inputTileSize, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set);
#endif
        }
        else if (format== YUV_420SP) {

#if (!VCOP_HOST_EMULATION)
            pblockupdate = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_param_count());
            pblock = (uint16_t *)*(context->pblockRunningMem);
            context->pblockRunningMem = (uint16_t (*)[])(*context->pblockRunningMem + vcop_bilinearInterpolateYUV420SPchroma_param_count());

            context->vloopFuncList[context->pBlockIdx] = &vcop_bilinearInterpolateYUV420SPchroma_vloops;
            context->pblockList[context->pBlockIdx]    = pblock;
            context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_vloops;
            context->pblockUpdatePblockList[context->pBlockIdx]   = pblockupdate;
            context->pBlockIdx++;

            /* Initialize kernel for 420 Chroma */
            vcop_bilinearInterpolateYUV420SPchroma_init((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, \
                    xFracArray, yFracArray, tluScOffsetArray, scattered_ofst, (uint16_t*)(void *)scratchWbuf, scratchIbuf, src_stride, \
                    mnQShift, oQShift, qScale, params->rightShift, inputTileSize/2U, params->sat_high, params->sat_high_set, params->sat_low, \
                    params->sat_low_set,  dst_end_offset, pblock);

            /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
            /* Pointers need to be converted to integers for arithematic computation within the kernel. */
            vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_init(numMappedPixels_ptr, (uint16_t *)pblock, (uint32_t )tluScOffsetArray, \
                    (uint32_t *)(void *)pblock, pblockupdate);
            /* RESET_MISRA("11.3")  -> Reset rule 11.3     */

#else
            vcop_bilinearInterpolateYUV420SPchroma((uint8_t*)src, (uint8_t*)dst, maxOutputBlockSize, numMappedPixels, tluIndexArray, \
                    xFracArray, yFracArray, tluScOffsetArray, scattered_ofst, (uint16_t*)scratchWbuf, scratchIbuf, src_stride, \
                    mnQShift, oQShift, qScale, params->rightShift, inputTileSize/2U, params->sat_high, params->sat_high_set, params->sat_low, params->sat_low_set, dst_end_offset);
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

    context->pblockList[context->pBlockIdx]               = pblock;
    context->pblockUpdateFuncList[context->pBlockIdx]     = &vcop_remap_dummy;
    context->pblockUpdatePblockList[context->pBlockIdx]   = pblock;
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
int32_t vcop_remap_tile_approach(
        VcopRemapContext *context
){
    uint32_t i;

    for (i=0;i<context->numPblocks;i++) {
        context->pblockUpdateFuncList[i](context->pblockUpdatePblockList[i]);
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
