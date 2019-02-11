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
 *  @file       bam_generateList_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating generate list kernel into BAM..
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_generateList_int.h"
#include "bam_generateList.h"
#include "vcop_generateList_kernel.h"
#include "../inc/get_generateListPtr.h"

/* Function Prototypes */
static BAM_Status BAM_generateList_initFrame(void *kernelContext);
static BAM_Status BAM_generateList_compute(void *kernelContext);

static BAM_Status BAM_generateList_initFrame(void *kernelContext)
{
    uint32_t i;
    uint32_t blkWidth, blkHeight;
    uint16_t (*xyVal)[];
    uint8_t (*endRowPadVal)[];
    BAM_GenerateList_Context *context = (BAM_GenerateList_Context *) kernelContext;
    BAM_Status status = 0;

    blkWidth=  (uint32_t)context->kernelArgs.width;
    blkHeight= (uint32_t)context->kernelArgs.height;

    context->endRowPadVal= (uint8_t*)context->pInternalBlock[VARIABLES_IDX];
    context->xVal= (uint16_t*)(void*)(context->endRowPadVal + (8u*sizeof(uint8_t)));
    context->yVal= context->xVal + ALIGN_SIMD((uint32_t)blkWidth);
    context->blockX= context->yVal + blkHeight;
    context->blockY= context->blockX + 1u;
    /* CHECK_MISRA("-17.1, -17.4")  -> Disable rule 17.1, 17.4 */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation is allowed because we need to add an offset to an existing pointer in order to obtain the desired pointer */
    context->numElmtsX= (uint16_t*)(context->blockY + 1u);
    context->numElmtsY= (uint16_t*)(context->numElmtsX + 1u);
    /* RESET_MISRA("17.1, 17.4")  -> Reset rule 17.1, 17.4*/

    xyVal= (uint16_t (*)[])(void*)context->xVal;
    for(i=0;i<(uint32_t)ALIGN_SIMD((uint32_t)blkWidth);i++) {
        (*xyVal)[i]= (uint16_t)i;
    }

    xyVal= (uint16_t (*)[])(void*)context->yVal;
    for(i=0;i<blkHeight;i++) {
        (*xyVal)[i]= (uint16_t)i;
    }

    endRowPadVal= (uint8_t (*)[])(void*)context->endRowPadVal;
    for(i=0;i< (uint32_t)(blkWidth - (ALIGN_SIMD((uint32_t)blkWidth) - ALIGN_SIMD((uint32_t)1u)));i++){
        (*endRowPadVal)[i]=(uint8_t)0xFF;
    }

    for(i=(uint32_t)(blkWidth - (ALIGN_SIMD((uint32_t)blkWidth) - ALIGN_SIMD((uint32_t)1u))); i<(uint32_t)ALIGN_SIMD((uint32_t)1u); i++){
        (*endRowPadVal)[i]= 0;
    }

  context->offsetX = context->kernelArgs.offsetX << context->kernelArgs.qShift;
  context->offsetY = context->kernelArgs.offsetY << context->kernelArgs.qShift;

  *(context->blockX)= 0;
  *(context->blockY)= 0;
  *(context->numElmtsX)= 0;
  *(context->numElmtsY)= 0;
  context->blockCount= context->kernelArgs.numHorzBlock*context->kernelArgs.numVertBlock;

#if !(VCOP_HOST_EMULATION)
    vcop_generateList_init(
            (uint8_t*)context->pInBlock[BAM_GENERATELIST_INPUT_PORT],
            context->endRowPadVal,
            context->xVal,
            context->yVal,
            context->blockX, /* pointer to X coordinate of the current block processed */
            context->blockY, /* pointer to Y coordinate of the current block processed */
            context->kernelArgs.numHorzBlock,   /* number of horizontal blocks in the frame */
            context->kernelArgs.numVertBlock,   /* number of vertical blocks in the frame */
            (uint16_t*)context->pInternalBlock[INTERNAL_X_IDX],
            (uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX],
            context->numElmtsX,
            context->numElmtsY,
            context->kernelArgs.maxNumElmts,
            (uint16_t)blkWidth,
            (uint16_t)blkHeight,
            context->kernelArgs.inStride,
            context->kernelArgs.qShift,
            (uint16_t*)context->pInternalBlock[GENERATELIST_PARAMS_IDX]
    );

    /* CHECK_MISRA("-17.4")  -> Disable rule 17.4 */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation is allowed because we must pass the pointer as integer value */
    status= get_generateListPtr(
            (const uint16_t*)context->pInternalBlock[GENERATELIST_PARAMS_IDX],
            (uint16_t)vcop_generateList_param_count(),
            (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_X_IDX]),
            (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX]),
            &context->listXoffset,
            &context->listYoffset);

    /* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
    /* Goto statement is used */
    if (status!=0) {
        goto Exit;
    }
    /*RESET_MISRA("15.1")  -> Reset rule 15.1 */

    vcop_updateGenerateList_init(
            context->pInternalBlock[GENERATELIST_PARAMS_IDX],
            (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_X_IDX]),
            (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX]),
            context->numElmtsX,
            context->listXoffset,
            context->listYoffset,
            (uint16_t*)context->pInternalBlock[UPDATE_PARAMS_IDX]);

   vcop_copyListToOutBuff_init(context->pInternalBlock[INTERNAL_X_IDX],
                               context->pInternalBlock[INTERNAL_Y_IDX],
                               context->pOutBlock[BAM_GENERATELIST_OUTPUT_XY_PORT],
                               context->numElmtsX,
                               context->pOutBlock[BAM_GENERATELIST_OUTPUT_NUM_ELMNTS_PORT],
                                (uint16_t)ALIGN_2SIMD((uint32_t)context->kernelArgs.maxNumElmts),
                                context->offsetX,
                                context->offsetY,
                                context->pInternalBlock[COPY_XY_PARAMS_IDX]);

   reset_generateListPtr(
           (uint16_t*)context->pInternalBlock[GENERATELIST_PARAMS_IDX],
           (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_X_IDX]),
           (uint32_t) ((uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX]),
           context->listXoffset,
           context->listYoffset);

     /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

#endif
    Exit:
    return status;
}

static BAM_Status BAM_generateList_compute(void *kernelContext) {

    BAM_GenerateList_Context *context = (BAM_GenerateList_Context *) kernelContext;
    BAM_Status status = 0;
#if !(VCOP_HOST_EMULATION)

    vcop_generateList_vloops((uint16_t*)context->pInternalBlock[GENERATELIST_PARAMS_IDX]);
    vcop_updateGenerateList_vloops((uint16_t*)context->pInternalBlock[UPDATE_PARAMS_IDX]);

    context->blockCount--;

    if (context->blockCount== 0) {
        vcop_copyListToOutBuff_vloops((uint16_t*)context->pInternalBlock[COPY_XY_PARAMS_IDX]);
    }

#else
    uint32_t offset = *(context->numElmtsX) > context->kernelArgs.maxNumElmts ? 0 : *(context->numElmtsX);
    vcop_generateList(
            (uint8_t*)context->pInBlock[BAM_GENERATELIST_INPUT_PORT],
            context->endRowPadVal,
            context->xVal,
            context->yVal,
            context->blockX, /* pointer to X coordinate of the current block processed */
            context->blockY, /* pointer to Y coordinate of the current block processed */
            context->kernelArgs.numHorzBlock,   /* number of horizontal blocks in the frame */
            context->kernelArgs.numVertBlock,   /* number of vertical blocks in the frame */
            (uint16_t*)context->pInternalBlock[INTERNAL_X_IDX] + offset,
            (uint16_t*)context->pInternalBlock[INTERNAL_Y_IDX] + offset,
            context->numElmtsX,
            context->numElmtsY,
            context->kernelArgs.maxNumElmts,
            context->kernelArgs.width,
            context->kernelArgs.height,
            context->kernelArgs.inStride,
            context->kernelArgs.qShift);

    context->blockCount--;

  if (context->blockCount== 0)
  {
   vcop_copyListToOutBuff(context->pInternalBlock[INTERNAL_X_IDX],
                               context->pInternalBlock[INTERNAL_Y_IDX],
                               context->pOutBlock[BAM_GENERATELIST_OUTPUT_XY_PORT],
                               context->numElmtsX,
                               context->pOutBlock[BAM_GENERATELIST_OUTPUT_NUM_ELMNTS_PORT],
                                ALIGN_2SIMD(context->kernelArgs.maxNumElmts),
                                context->offsetX,
                                context->offsetY);
  }
Exit:
#endif

    return status;

}

BAM_KernelExecFuncDef gBAM_TI_generateListExecFunc =
{ NULL, &BAM_generateList_initFrame, &BAM_generateList_compute, NULL, NULL, NULL};

