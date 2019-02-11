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

/* -------------------------------------------------------------------- */
/* NAME : evelib_fir_filter_2d.c                                        */
/*                                                                      */
/* DESCRIPTION:                                                         */
/*                                                                      */
/* This file contains an FIR filter implementaion                       */
/*                                                                      */
/* Author: Manu Mathew <mathew.manu@ti.com>                             */
/* -------------------------------------------------------------------- */
#include <stdint.h>
#include <vcop/vcop.h>
#include "common/eve_algo_dma_auto_incr.h"
#include "evelib_fir_filter_2d.h"
#include "vcop_filter_kernel.h"


/**
*  @brief      Apply 2D FIR filter on a given grayscale image
*
*  @param[in]  src             source image pointer
*  @param[in]  srcImageWidth   source image width in pixels
*  @param[in]  srcImageHeight  source image height in pixels
*  @param[in]  srcBufferPitch  source image picth in bytes
*  @param[in]  srcBufferHeight source image picth in bytes
*  @params[i]  srcBytesPP      source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst             destimation image pointer
*  @param[in]  dstImageWidth   destination image width in pixels
*  @param[in]  dstImageHeight  destination image height in pixels
*  @param[in]  dstBufferPitch  destination image picth in bytes
*  @param[in]  dstBufferHeight destination image picth in bytes
*  @params[in] dstBytesPP      dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @params[in] coeff           filter coefficitents array pointer
*  @params[in] coeffH          horizontal filter taps (=M in an MxN filter)
*  @params[in] coeffV          horizontal filter taps (=N in an MxN filter)
*  @params[in] dnsmplVert      vertical downsample factor
*  @params[in] dnsmplHorz      horizontal downsample factor (only 1 is supported currently)
*  @params[in] rndShift        Shift factor for the given set of coefficients.
*
*  @remarks    Grayscale filtering function - 2D FIR filter.
*  @remarks    The performance of this algorithm is best when either the srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 64 or 32.
*
*  @sa         EVELIB_algoDMAAutoIncrInit(), EVELIB_algoDMAAutoIncrProcess(), EVELIB_algoDMAAutoIncrDeInit()
*/
void EVELIB_firFilter2D(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcBufferPitch,
    int                 srcBufferHeight,
    unsigned int        srcBytesPP,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstBufferPitch,
    int                 dstBufferHeight,
    unsigned int        dstBytesPP,
    char                coeff[],
    unsigned int        coeffH,
    unsigned int        coeffW,
    unsigned int        dnsmplVert,
    unsigned int        dnsmplHorz,
    int                 rndShift
    )
{
    uint8_t *srcBlk;
    uint8_t *dstBlk;
    char *coeffBlk;

    uint32_t srcBlkPadX = 2;
    uint32_t srcBlkPadY = 2;

    uint32_t srcImageWidthBytes = srcImageWidth * srcBytesPP; //convert to bytes
    uint32_t dstImageWidthBytes = dstImageWidth * dstBytesPP; //convert to bytes

    uint32_t srcBlkWidth = 0;
    uint32_t srcBlkHeight= 0;

    uint32_t srcProcWidth = 0;
    uint32_t srcProcHeight= 0;

    uint32_t perfVal = EVELIB_getBestBlockDimensions(srcImageWidthBytes, srcImageHeight, srcBufferPitch, srcBufferHeight,
        &srcProcWidth, &srcProcHeight, &srcBlkWidth, &srcBlkHeight);

    uint32_t srcBlkPitch = (srcBlkWidth+srcBlkPadX);
    uint32_t srcBlkHeightTot = (srcBlkHeight+srcBlkPadY);

    uint32_t dstBlkWidth  = (srcBlkWidth);
    uint32_t dstBlkHeight = (srcBlkHeight);
    uint32_t dstBlkPitch  = (dstBlkWidth);

    EVELIB_KernelFuncType execFunc[] = {(EVELIB_KernelFuncType)vcop_filter_uchar_char_uchar_vloops};
    EVELIB_KernelContextType context[] = {(EVELIB_KernelContextType)__pblock_vcop_filter_uchar_char_uchar};
    unsigned int numKernels = 1;

    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    srcBlk = (unsigned char *)vcop_malloc(VCOP_IBUFLA, srcBlkPitch * srcBlkHeightTot);
    dstBlk = (unsigned char *)vcop_malloc(VCOP_IBUFHA, dstBlkPitch * dstBlkHeight);
    coeffBlk = (char *)vcop_malloc(VCOP_WMEM, coeffH * coeffW);

    memcpy(coeffBlk, coeff, coeffH * coeffW);

    vcop_filter_uchar_char_uchar_init(srcBlk, coeffBlk, dstBlk, srcBlkPitch, coeffW, coeffH, srcBlkWidth,
        srcBlkHeight, dnsmplVert, dnsmplHorz, rndShift, __pblock_vcop_filter_uchar_char_uchar);

    EVELIB_algoDMAAutoIncrInit(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst,
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY);

    EVELIB_algoDMAAutoIncrProcess(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst,
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY,
        execFunc,
        context,
        numKernels,
        0);

    EVELIB_algoDMAAutoIncrDeInit( );


    vcop_free(srcBlk);
    vcop_free(dstBlk);
    vcop_free(coeffBlk);
}

