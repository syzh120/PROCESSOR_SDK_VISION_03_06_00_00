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
 *  @file       bam_natcGenerateList_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of generateList into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_generateList_c.h"
#include "../inc/get_generateListPtr.h"
#include "bam_generateList_int.h"
#include "bam_generateList.h"
#include "vcop_generateList_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcGenerateList_computeFrame(void *kernelContext);
static BAM_Status BAM_natcGenerateList_initInstance(void *kernelContext);
static BAM_Status BAM_natcGenerateList_initFrame(void *kernelContext);

static BAM_Status BAM_natcGenerateList_initInstance(void *kernelContext)
{
    uint32_t blkWidth, blkHeight;
    BAM_GenerateList_Context *context = (BAM_GenerateList_Context *) kernelContext;
    BAM_Status status = 0;

    blkWidth= (uint32_t)context->kernelArgs.width;
    blkHeight= (uint32_t)context->kernelArgs.height;

    context->endRowPadVal= (uint8_t*)context->pInternalBlock[VARIABLES_IDX];
    context->xVal= (uint16_t*)(void*)(context->endRowPadVal + 8u*sizeof(uint8_t));
    context->yVal= context->xVal + ALIGN_SIMD(blkWidth);
    context->blockX= context->yVal + blkHeight;
    context->blockY= context->blockX + 1u;
    context->numElmtsX= (uint16_t*)(context->blockY + 1u);
    context->numElmtsY= (uint16_t*)(context->numElmtsX + 1u);
    return status;
}


static BAM_Status BAM_natcGenerateList_computeFrame(void *kernelContext)
{
    BAM_GenerateList_Context *context = (BAM_GenerateList_Context *) kernelContext;
    uint16_t i;
    BAM_Status status = 0;

    if (context->runningNumFeatures < context->kernelArgs.maxNumElmts) {
        context->runningNumFeatures+= vcop_generateList_cn
                (
                        (uint8_t*)context->pInBlock[BAM_GENERATELIST_INPUT_PORT],
                        context->blockX, /* pointer to X coordinate of the current block processed */
                        context->blockY, /* pointer to Y coordinate of the current block processed */
                        context->kernelArgs.numHorzBlock,   /* number of horizontal blocks in the frame */
                        context->kernelArgs.numVertBlock,   /* number of vertical blocks in the frame */
                        (uint16_t*)context->pInternalBlock[INTERNAL_X_IDX] + context->runningNumFeatures,
                        (uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX] + context->runningNumFeatures,
                        context->numElmtsX,
                        context->numElmtsY,
                        context->kernelArgs.maxNumElmts,
                        context->kernelArgs.width,
                        context->kernelArgs.height,
                        context->kernelArgs.inStride,
                        context->kernelArgs.qShift
                );
    }

    context->blockCount--;

    /* Do memcpy into output buffer once everyblocks have been processed, which happens when both blockX and blockY rolls back to 0 */
    if (context->blockCount==0){
        *((uint16_t*)context->pOutBlock[OUT_NUM_ELMNTS_IDX])= context->runningNumFeatures;
        if (context->runningNumFeatures) {
            for (i=0;i<context->runningNumFeatures;i++) {
                *((uint16_t*)context->pOutBlock[OUT_XY_IDX] + 2*i)= *((uint16_t*)context->pInternalBlock[INTERNAL_X_IDX] + i) + (context->kernelArgs.offsetX<<context->kernelArgs.qShift);
                *((uint16_t*)context->pOutBlock[OUT_XY_IDX] + 2*i + 1)= *((uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX] + i) + (context->kernelArgs.offsetY<<context->kernelArgs.qShift);
            }
        }
    }

    return status;
}

static BAM_Status BAM_natcGenerateList_initFrame(void *kernelContext)
{
    BAM_GenerateList_Context *context = (BAM_GenerateList_Context *) kernelContext;
    BAM_Status status = 0;

    *(context->blockX)= 0;
    *(context->blockY)= 0;
    *(context->numElmtsX)= 0;
    *(context->numElmtsY)= 0;
    context->runningNumFeatures= 0;
    context->blockCount= context->kernelArgs.numHorzBlock*context->kernelArgs.numVertBlock;
    return status;
}


BAM_KernelExecFuncDef gBAM_TI_natcGenerateListExecFunc =
{ &BAM_natcGenerateList_initInstance, &BAM_natcGenerateList_initFrame, &BAM_natcGenerateList_computeFrame, NULL, NULL, NULL };

