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


#include <stdint.h>
#include <vcop/vcop.h>
#include "common/eve_algo_dma_scatter_gather.h"
#include "evelib_fir_filter_2d_scatter_gather.h"
#include "vcop_filter_kernel.h"
#include "dma_funcs.h"
#include "dma_resource_allocator.h"

#define FRAME_WIDTH_MAX     1280
#define FRAME_HEIGHT_MAX     736
#define BLK_WIDTH   32
#define BLK_HEIGHT  32
#define NUM_TRANSFERS   2 /* transfer multiple blocks in single trigger*/

static     near uint8_t *srcPtrList[(FRAME_WIDTH_MAX/BLK_WIDTH)*(FRAME_HEIGHT_MAX/BLK_HEIGHT)];
static  near uint8_t *dstPtrList[(FRAME_WIDTH_MAX/BLK_WIDTH)*(FRAME_HEIGHT_MAX/BLK_HEIGHT)];

void EVELIB_firFilter2D_scatterGather(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    char                coeff[],
    unsigned int        coeffH,
    unsigned int        coeffW,
    unsigned int        dnsmplVert,
    unsigned int        dnsmplHorz,
    int                    rndShift
    )
{
    uint8_t *srcBlk = 0;
    uint8_t *dstBlk = 0;
    char *coeffBlk = 0;
    int32_t x = 0, y = 0, listId = 0, i =0;

    uint32_t srcBlkPadX = 2;
    uint32_t srcBlkPadY = 2;
    uint8_t numTransfersIn = NUM_TRANSFERS;
    uint8_t numTransfersOut = NUM_TRANSFERS;
    uint32_t numBlocks = 0;

    uint32_t srcBlkWidthDma = (BLK_WIDTH*numTransfersIn + srcBlkPadX)/numTransfersIn;
    uint32_t srcBlkHeightDma = BLK_HEIGHT;
    uint32_t srcBlkPitchDma = (BLK_WIDTH*numTransfersIn + srcBlkPadX);

    uint32_t dstBlkWidthDma = (BLK_WIDTH*numTransfersOut)/numTransfersOut;
    uint32_t dstBlkHeightDma = (srcBlkHeightDma);
    uint32_t dstBlkPitchDma = (BLK_WIDTH*numTransfersOut);

    uint8_t *srcBlkPtrList[4];
    uint8_t *dstBlkPtrList[4];

    uint32_t srcBlkWidthKer = BLK_WIDTH*numTransfersIn;
    uint32_t srcBlkHeightKer = BLK_HEIGHT;
    uint32_t srcBlkPitchKer = (srcBlkWidthKer+srcBlkPadX);
    uint32_t srcBlkHeightTotKer = (srcBlkHeightKer+srcBlkPadY);

    uint32_t dstBlkWidthKer = (srcBlkWidthKer);
    uint32_t dstBlkHeightKer = (srcBlkHeightKer);
    uint32_t dstBlkPitchKer = (dstBlkWidthKer);

    /*--------------------------------------------------------------------------*/
    /*  Declare a dma state structure                                           */
    /*--------------------------------------------------------------------------*/
    DMA_resourceStruct  edmaResources;

    /*--------------------------------------------------------------------------*/
    /*  Anchor edma_cc to the start of the EDMA CC0                             */
    /*--------------------------------------------------------------------------*/
    CSL_EdmaccRegsOvly edma_cc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);

    EVELIB_KernelFuncType execFunc[] = {(EVELIB_KernelFuncType)vcop_filter_uchar_char_uchar_vloops};
    EVELIB_KernelContextType context[] = {(EVELIB_KernelContextType)__pblock_vcop_filter_uchar_char_uchar};
    unsigned int numKernels = 1;

    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    srcBlk = (uint8_t *)vcop_malloc(VCOP_IBUFLA, srcBlkPitchKer * srcBlkHeightTotKer);
    dstBlk = (uint8_t *)vcop_malloc(VCOP_IBUFHA, dstBlkPitchKer * dstBlkHeightKer);
    coeffBlk = (char *)vcop_malloc(VCOP_WMEM, coeffH * coeffW);


    memcpy(coeffBlk, coeff, coeffH * coeffW);

    vcop_filter_uchar_char_uchar_init(srcBlk, coeffBlk, dstBlk, srcBlkPitchKer, coeffW, coeffH, srcBlkWidthKer,
        srcBlkHeightKer, dnsmplVert, dnsmplHorz, rndShift, __pblock_vcop_filter_uchar_char_uchar);

    EVELIB_algoDMAScatterGatherInit(&edmaResources,
        edma_cc,
        numTransfersIn,
        srcImageWidth,
        srcImageHeight,
        srcImagePitch,
        numTransfersOut,
        dstImageWidth,
        dstImageHeight,
        dstImagePitch,
        srcBlkWidthDma-srcBlkPadX, /*padding is added below */
        srcBlkHeightDma,
        srcBlkPitchDma,
        dstBlkWidthDma,
        dstBlkHeightDma,
        dstBlkPitchDma,
        srcBlkPadX,
        srcBlkPadY);

    /* generate pointer list */
    listId = 0;
    for(y=0; y<srcImageHeight; y+=BLK_HEIGHT)
    {
        for(x=0; x<srcImageWidth; x+=BLK_HEIGHT*numTransfersIn)
        {
            for(i=0; i<numTransfersIn; i++)
            {
                srcPtrList[listId] = src + (y*srcImagePitch)+x+(srcBlkWidthDma*i);
                listId++;
            }
        }
    }
    numBlocks = listId/numTransfersIn;

    listId = 0;
    for(y=0; y<dstImageHeight; y+=BLK_HEIGHT)
    {
        for(x=0; x<dstImageWidth; x+=BLK_HEIGHT*numTransfersOut)
        {
            for(i=0; i<numTransfersOut; i++)
            {
                dstPtrList[listId] = dst + (y*dstImagePitch)+x+(dstBlkWidthDma*i);
                listId++;
            }
        }
    }

    for(x=0; x<numTransfersIn; x++)
    {
        srcBlkPtrList[x] = srcBlk + srcBlkWidthDma*x;
    }

    for(x=0; x<numTransfersOut; x++)
    {
        dstBlkPtrList[x] = dstBlk + dstBlkWidthDma*x;
    }


    EVELIB_algoDMAScatterGatherProcess(&edmaResources,
        edma_cc,
        srcPtrList,
        numTransfersIn,
        srcImageWidth,
        srcImageHeight,
        srcImagePitch,
        dstPtrList,
        numTransfersOut,
        dstImageWidth,
        dstImageHeight,
        dstImagePitch,
        srcBlkPtrList,
        srcBlkWidthKer,
        srcBlkHeightKer,
        srcBlkPitchKer,
        dstBlkPtrList,
        dstBlkWidthKer,
        dstBlkHeightKer,
        dstBlkPitchKer,
        srcBlkPadX,
        srcBlkPadY,
        numBlocks,
        execFunc,
        context,
        numKernels,
        0);

    EVELIB_algoDMAScatterGatherDeInit(&edmaResources,
        edma_cc);


    vcop_free(srcBlk);
    vcop_free(dstBlk);
    vcop_free(coeffBlk);
}

