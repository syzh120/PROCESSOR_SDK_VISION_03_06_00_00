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
 *  @file       bam_disparityHamDist_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hammind distance based disparity calculation
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <vcop.h>

#include "bam_disparityHamDist_int.h"
#include "bam_disparityHamDist.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_hammingDistance32_row_kernel_wrapper.h"
#include "vcop_disparity_postprocess_kernel.h"
#include "vcop_disparity_hammingDistance_row_cn.h"
#include "init_disparity_hammingDistance_row_params.h"
#include "vcop_disparity_hammingDistance32_getPtr.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

#if (!VCOP_HOST_EMULATION)
/* This macro symbol is used to support ping-pong buffering of param block between IBUFA/B */
#define IMBUF_GAP ((uint8_t*)ibuflb - (uint8_t*)ibufla)

static void Bam_DisparityHamDist32_updateParamRegs(BAM_DisparityHamDist_Context *context);
#endif

/* Function Prototypes */
static BAM_Status Bam_DisparityHamDist_initFrame(void *kernelContext);
static BAM_Status BAM_DisparityHamDist_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status BAM_DisparityHamDist_compute(void *kernelContext);


static BAM_Status BAM_DisparityHamDist_control(void *kernelContext, void *kernelCtlArg){

    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_DisparityHamDist_CtlArgs *ctlArg= (BAM_DisparityHamDist_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_DISPARITY_HAMDIST_CMD_SET_NUMROWS){
        context->kernelArgs.numRows= ctlArg->numRows;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status Bam_DisparityHamDist_initFrame(void *kernelContext)
{
    uint16_t scratchBufferSize, allCostOutputBufferSize;
    uint32_t pScatterStride;
    uint16_t (*internalBlock)[];
    uint16_t allCostOutputStride;
    uint8_t prevIdx, nextIdx;
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

    uint16_t leftPrevRowOffset[5];
    uint16_t leftLastRowOffset[5];
    uint16_t rightPrevRowOffset[5];
    uint16_t rightLastRowOffset[5];
    uint16_t i;
    uint16_t numLinesInBuf, numDisp;
    uint16_t disparityStepShift;

    /* Initialize counter indexes that will keep track of the position of the segment being processed. A segment is defined as a block of height 1 but
     * with a width that divides the frame's width */
    context->horzBlockIdx= 0;
    context->vertBlockIdx= 0;

    /* Initialize counter indexes that will keep track of the position of the segment being processed. The differences with previous indexes is that the following
     * indexes are used for updating the pblock in a ping-pong manner since we have chosen to store the pblocks in IBUF, not WMEM because of line circular buffer
     * support, which requires updating pointers at every call.
     * */
#if (!VCOP_HOST_EMULATION)
    context->updateHorzBlockIdx= 0;
    context->updateVertBlockIdx= 1;
    context->pingPongFlag= 1;
#else
    context->updateHorzBlockIdx= 0;
    context->updateVertBlockIdx= 0;
    context->pingPongFlag= 0;
#endif

    /* Line Circular buffer support: These variables are used to track the relative offset from beginning of the input block
     * to the previous or last rows from left or right images, required for the disparity computation.
     * Since a sliding window is used, these offsets change at every row iteration and eventually roll back when end of the buffer is reached.
     */
    numLinesInBuf= (uint16_t)context->kernelArgs.winHeight + 1U;
    context->prevRowLeftOffset= -(int16_t)context->kernelArgs.leftStride;
    context->prevRowLeftInitOffset= context->prevRowLeftOffset;
    context->prevRowRightOffset= -(int16_t)context->kernelArgs.rightStride;
    context->prevRowRightInitOffset= context->prevRowRightOffset;
    context->lastRowLeftOffset= (context->kernelArgs.winHeight - 1)*context->kernelArgs.leftStride;
    context->lastRowLeftInitOffset= context->lastRowLeftOffset;
    context->lastRowRightOffset= (context->kernelArgs.winHeight - 1)*context->kernelArgs.rightStride;
    context->lastRowRightInitOffset= context->lastRowRightOffset;

    context->leftEndMarker= numLinesInBuf*context->kernelArgs.leftStride;
    context->rightEndMarker= numLinesInBuf*context->kernelArgs.rightStride;


    /* Call function that initialize some the input parameters that will have to be passed to vcop_disparity_hammingDistance32_<...>_init
     * It is just easier to have a function derive all the constraints than following some documentation */
    status= init_disparity_hammingDistance_row_params (
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
            32U,
            (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
            (uint16_t*)&scratchBufferSize,
            (uint16_t*)&context->scratchBufferStride,
            (uint16_t*)&allCostOutputStride,
            (uint16_t*)&allCostOutputBufferSize,
            context->kernelArgs.width,
            context->kernelArgs.numDisparities,
            context->kernelArgs.disparityStep
    );

    if (status !=0) {
        goto Exit;
    }

    /* Just verify of the value context->scratchBufferStride returned is the same as the one we used in the getMemRec() helper function */
    pScatterStride= (((uint32_t)context->kernelArgs.numDisparities/(uint32_t)context->kernelArgs.disparityStep)*(uint32_t)SIZE_COST) + 31UL;
    pScatterStride= ((uint32_t)pScatterStride & 0xFFFFFFE0U);
    pScatterStride+= 4UL;
    if (context->scratchBufferStride != (uint16_t)pScatterStride ) {
        status= 1;
        goto Exit;
    }

    /* Initialize first row and last row of context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] with 65535
     * This is a requirement from vcop_disparity_genPrevAndNextMinCost()
     * */
    numDisp= context->kernelArgs.numDisparities/context->kernelArgs.disparityStep;
    internalBlock= (uint16_t (*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX];
    for(i=0;i<(uint16_t)(context->kernelArgs.allCostOutputStride/2U);i++) {
        (*internalBlock)[i]= 65535U; /* Should be 65535 */
        (*internalBlock)[(((numDisp+1U)*context->kernelArgs.allCostOutputStride)/2U) + i]= 65535U; /* Should be 65535 */
    }

#if (!VCOP_HOST_EMULATION)

    /* Store all the pblock pointers values into the context structure */
    context->pFirstRowFirstCallParams[0]= *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_FIRST_ROW_FIRST_CALL_PARAMS_OFST;
    context->pFirstRowParams[0]= *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_FIRST_ROW_PARAMS_OFST;
    context->pNthRowFirstCallParams[0]= *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_NTH_ROW_FIRST_CALL_PARAMS_OFST;
    context->pNthRowParams[0]= *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_NTH_ROW_PARAMS_OFST;
    context->pGenPrevAndNextMinCostParams[0]= *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_GEN_PREV_NEXT_MINCOST_OFST;
    /*
    context->pRLFirstCallParams[0]= (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_RL_FIRST_CALL_PARAMS_OFST;
    context->pRLParams[0]= (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_PARAMS_IDX] + DISPARITY_HAMDIST_RL_PARAMS_OFST;
     */
    /* When ping-pong buffering is enabled, we need to initialize the other side of the pointers also */
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1 */
    /*  Pointer is used in arithmetic or array index expression */
    /* Used to calculate address */
    context->pFirstRowFirstCallParams[1]= *(uint16_t(*)[])(void*)context->pFirstRowFirstCallParams[0] + (IMBUF_GAP>>1);
    context->pFirstRowParams[1]= *(uint16_t(*)[])(void*)context->pFirstRowParams[0] + (IMBUF_GAP>>1);
    context->pNthRowFirstCallParams[1]= *(uint16_t(*)[])(void*)context->pNthRowFirstCallParams[0] + (IMBUF_GAP>>1);
    context->pNthRowParams[1]= *(uint16_t(*)[])(void*)context->pNthRowParams[0] + (IMBUF_GAP>>1);
    context->pGenPrevAndNextMinCostParams[1]= *(uint16_t(*)[])(void*)context->pGenPrevAndNextMinCostParams[0] + (IMBUF_GAP>>1);
/*
    context->pRLFirstCallParams[1]= context->pRLFirstCallParams[0] + (IMBUF_GAP>>1);
    context->pRLParams[1]= context->pRLParams[0] + (IMBUF_GAP>>1);
*/
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 */

    /* Call all the kernels init functions that initialize the pblocks */
    wrapper_vcop_disparity_hammingDistance32_first_row_firstCall_init(
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4),
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4),
            context->kernelArgs.leftStride,
            context->kernelArgs.rightStride,
            context->kernelArgs.winWidth,
            context->kernelArgs.winHeight,
            (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
            (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
            context->kernelArgs.allCostOutputStride,
            context->kernelArgs.width,
            context->kernelArgs.numDisparities,
            context->kernelArgs.disparityStep,
            (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
            (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
            context->scratchBufferStride,
            context->pFirstRowFirstCallParams[0],
            context->kernelArgs.direction
    );

    /* Since we have placed the param entries in image buffer LA, need to copy them in image buffer LB also */
    memcpy((void*)context->pFirstRowFirstCallParams[1], (void*)context->pFirstRowFirstCallParams[0], PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall*2U);

    wrapper_vcop_disparity_hammingDistance32_first_row_init(
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4),
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4),
            context->kernelArgs.leftStride,
            context->kernelArgs.rightStride,
            context->kernelArgs.winWidth,
            context->kernelArgs.winHeight,
            (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
            (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
            context->kernelArgs.allCostOutputStride,
            context->kernelArgs.width,
            context->kernelArgs.numDisparities,
            context->kernelArgs.disparityStep,
            (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
            (int16_t*)context->pInBlock[DISPARITY_HAMDIST_CARRYOVER_IN_IDX],
            (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
            context->scratchBufferStride,
            context->pFirstRowParams[0],
            context->kernelArgs.direction
    );
    /* Since we have placed the param entries in image buffer LA, need to copy them in image buffer LB also */
    memcpy((void*)context->pFirstRowParams[1], (void*)context->pFirstRowParams[0], PARAM_SIZE_vcop_disparity_hammingDistance32_first_row*2U);

    wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall_init(
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            context->kernelArgs.leftStride,
            context->kernelArgs.rightStride,
            context->kernelArgs.winWidth,
            context->kernelArgs.winHeight,
            (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
            (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
            context->kernelArgs.allCostOutputStride,
            context->kernelArgs.width,
            context->kernelArgs.numDisparities,
            context->kernelArgs.disparityStep,
            (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX],
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
            (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
            context->scratchBufferStride,
            context->pNthRowFirstCallParams[0],
            context->kernelArgs.direction
    );
    /* Since we have placed the param entries in image buffer LA, need to copy them in image buffer LB also */
    memcpy((void*)context->pNthRowFirstCallParams[1], (void*)context->pNthRowFirstCallParams[0], PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall*2U);

    /* Call vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr() to get the exact location of the different pointers that will require updating during processing
     * Updating will be performed by vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr()
     * */
    status= vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr(
            context->pNthRowFirstCallParams[0],
            (uint16_t)PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall,
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint16_t)context->kernelArgs.winWidth,
            context->kernelArgs.disparityStep,
            leftPrevRowOffset,
            leftLastRowOffset,
            rightPrevRowOffset,
            rightLastRowOffset,
            (uint8_t)(sizeof(leftPrevRowOffset)/2U),
            context->kernelArgs.direction
    );

    if (status!=0) {
        goto Exit;
    }

    /*
     * vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr() returned offset values. We use them now to calculate the absolute
     * pointer values which will be used by vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr(). For this particular vcop_disparity_hammingDistance32_nth_row_firstCall(),
     * there are 5 locations per pointer that will need to be updated.
     */
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1 */
    /*  Pointer is used in arithmetic or array index expression */
    /* Used to calculate address */
    for(i=0;i<5U;i++) {
        context->nth_row_firstCall_leftPrevRowPtr[0][i]= (uint32_t*)(void*)context->pNthRowFirstCallParams[0] + (leftPrevRowOffset[i]/2U);
        context->nth_row_firstCall_leftLastRowPtr[0][i]= (uint32_t*)(void*)context->pNthRowFirstCallParams[0] + (leftLastRowOffset[i]/2U);
        context->nth_row_firstCall_rightPrevRowPtr[0][i]= (uint32_t*)(void*)context->pNthRowFirstCallParams[0] + (rightPrevRowOffset[i]/2U);
        context->nth_row_firstCall_rightLastRowPtr[0][i]= (uint32_t*)(void*)context->pNthRowFirstCallParams[0] + (rightLastRowOffset[i]/2U);
    }

    /* We also update the pong counterpart as the pblock is copied in both IBUFLA and IBUFLB */
    for(i=0;i<5U;i++) {
        context->nth_row_firstCall_leftPrevRowPtr[1][i]= context->nth_row_firstCall_leftPrevRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_firstCall_leftLastRowPtr[1][i]= context->nth_row_firstCall_leftLastRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_firstCall_rightPrevRowPtr[1][i]= context->nth_row_firstCall_rightPrevRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_firstCall_rightLastRowPtr[1][i]= context->nth_row_firstCall_rightLastRowPtr[0][i] + (IMBUF_GAP>>2);
    }
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 */

    wrapper_vcop_disparity_hammingDistance32_nth_row_init(
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint32_t*)(void*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            context->kernelArgs.leftStride,
            context->kernelArgs.rightStride,
            context->kernelArgs.winWidth,
            context->kernelArgs.winHeight,
            (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
            (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
            context->kernelArgs.allCostOutputStride,
            context->kernelArgs.width,
            context->kernelArgs.numDisparities,
            context->kernelArgs.disparityStep,
            (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
            *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX],
            (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
            (int16_t*)context->pInBlock[DISPARITY_HAMDIST_CARRYOVER_IN_IDX],
            (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
            context->scratchBufferStride,
            context->pNthRowParams[0],
            context->kernelArgs.direction
    );
    /* Since we have placed the param entries in image buffer LA, need to copy them in image buffer LB also */
    memcpy((void*)context->pNthRowParams[1], (void*)context->pNthRowParams[0], PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row*2U);

    /* Call vcop_disparity_hammingDistance32_nth_row_getPtr() to get the exact location of the different pointers that will require updating during processing
     * Updating will be performed by vcop_disparity_hammingDistance32_nth_row_setPtr()
     * */
    status= vcop_disparity_hammingDistance32_nth_row_getPtr(
            context->pNthRowParams[0],
            (uint16_t)PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row,
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
            (uint16_t)context->kernelArgs.winWidth,
            context->kernelArgs.disparityStep,
            leftPrevRowOffset,
            leftLastRowOffset,
            rightPrevRowOffset,
            rightLastRowOffset,
            (uint8_t)(sizeof(leftPrevRowOffset)/2U),
            context->kernelArgs.direction
    );

    if (status!=0) {
        goto Exit;
    }

    /*
     * vcop_disparity_hammingDistance32_nth_row_getPtr() returned offset values. We use them now to calculate the absolute
     * pointer values which will be used by vcop_disparity_hammingDistance32_nth_row_setPtr(). For this particular vcop_disparity_hammingDistance32_nth_row(),
     * there are 4 locations per pointer that will need to be updated.
     */
    for(i=0;i<4U;i++) {
        context->nth_row_leftPrevRowPtr[0][i]= *(uint32_t(*)[])(void*)context->pNthRowParams[0] + (leftPrevRowOffset[i]/2U);
        context->nth_row_leftLastRowPtr[0][i]= *(uint32_t(*)[])(void*)context->pNthRowParams[0] + (leftLastRowOffset[i]/2U);
        context->nth_row_rightPrevRowPtr[0][i]= *(uint32_t(*)[])(void*)context->pNthRowParams[0] + (rightPrevRowOffset[i]/2U);
        context->nth_row_rightLastRowPtr[0][i]= *(uint32_t(*)[])(void*)context->pNthRowParams[0] + (rightLastRowOffset[i]/2U);
    }

    /* We also update the pong counterpart as the pblock is copied in both IBUFLA and IBUFLB */
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1 */
    /*  Pointer is used in arithmetic or array index expression */
    /* Used to calculate address */
    for(i=0;i<4U;i++) {
        context->nth_row_leftPrevRowPtr[1][i]= context->nth_row_leftPrevRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_leftLastRowPtr[1][i]= context->nth_row_leftLastRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_rightPrevRowPtr[1][i]= context->nth_row_rightPrevRowPtr[0][i] + (IMBUF_GAP>>2);
        context->nth_row_rightLastRowPtr[1][i]= context->nth_row_rightLastRowPtr[0][i] + (IMBUF_GAP>>2);
    }
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 */

    /* If we want to produce the previous and next adjacent costsfor  subsequent post-processing */
    if (context->kernelArgs.adjacentCosts== 1) {

        i=1U;
        while (context->kernelArgs.disparityStep>>i) {
            i++;
        }
        disparityStepShift= i-1U;

        if (context->kernelArgs.direction== 1) {
            prevIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            nextIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }
        else {
            nextIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            prevIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }

        vcop_disparity_genPrevAndNextMinCost_init
        (
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                (uint16_t*)context->pOutBlock[prevIdx],
                (uint16_t*)context->pOutBlock[nextIdx],
                (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
                context->kernelArgs.width,
                context->kernelArgs.allCostOutputStride, /* allCostStride in bytes */
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                (uint8_t)disparityStepShift,
                context->pGenPrevAndNextMinCostParams[0]
        );

        /* Since we have placed the param entries in image buffer LA, need to copy them in image buffer LB also */
        memcpy((void*)context->pGenPrevAndNextMinCostParams[1], (void*)context->pGenPrevAndNextMinCostParams[0], PARAM_SIZE_vcop_disparity_genPrevAndNextMinCost*2U);

    }

    /* Since the update of pblock will be done with a forward phase shift of 1: we update the pblock of the next block while we process the current block,
     * we go ahead and update now all the row offsets in a circular buffer fashion to support the sliding window.
     * */
    context->prevRowLeftOffset+=  context->kernelArgs.leftStride;
    if (context->prevRowLeftOffset== context->leftEndMarker) {
        context->prevRowLeftOffset= 0;
    }

    context->lastRowLeftOffset+=  context->kernelArgs.leftStride;
    if (context->lastRowLeftOffset== context->leftEndMarker) {
        context->lastRowLeftOffset= 0;
    }

    context->prevRowRightOffset+=  context->kernelArgs.rightStride;
    if (context->prevRowRightOffset== context->rightEndMarker) {
        context->prevRowRightOffset= 0;
    }

    context->lastRowRightOffset+=  context->kernelArgs.rightStride;
    if (context->lastRowRightOffset== context->rightEndMarker) {
        context->lastRowRightOffset= 0;
    }

#endif

    Exit:
    return status;
}


static BAM_Status BAM_DisparityHamDist_compute(void *kernelContext)
{
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
    /* Below if executed when VCOP_HOST_EMULATION=1, meaning only in HOST (PC) mode */
    if (context->vertBlockIdx== 0) {
        if (context->horzBlockIdx== 0) {
            wrapper_vcop_disparity_hammingDistance32_first_row_firstCall(
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4),
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4),
                    context->kernelArgs.leftStride,
                    context->kernelArgs.rightStride,
                    context->kernelArgs.winWidth,
                    context->kernelArgs.winHeight,
                    (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                    (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + context->kernelArgs.allCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                    context->kernelArgs.allCostOutputStride,
                    context->kernelArgs.width,
                    context->kernelArgs.numDisparities,
                    context->kernelArgs.disparityStep,
                    (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
                    (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
                    context->scratchBufferStride,
                    context->kernelArgs.direction
            );
        }
        else {
            wrapper_vcop_disparity_hammingDistance32_first_row(
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4),
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4),
                    context->kernelArgs.leftStride,
                    context->kernelArgs.rightStride,
                    context->kernelArgs.winWidth,
                    context->kernelArgs.winHeight,
                    (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                    (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + context->kernelArgs.allCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                    context->kernelArgs.allCostOutputStride,
                    context->kernelArgs.width,
                    context->kernelArgs.numDisparities,
                    context->kernelArgs.disparityStep,
                    (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
                    (int16_t*)context->pInBlock[DISPARITY_HAMDIST_CARRYOVER_IN_IDX],
                    (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
                    context->scratchBufferStride,
                    context->kernelArgs.direction
            );
        }
    }
    else {
        if (context->horzBlockIdx== 0) {
            wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall(
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    context->kernelArgs.leftStride,
                    context->kernelArgs.rightStride,
                    context->kernelArgs.winWidth,
                    context->kernelArgs.winHeight,
                    (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                    (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + context->kernelArgs.allCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                    context->kernelArgs.allCostOutputStride,
                    context->kernelArgs.width,
                    context->kernelArgs.numDisparities,
                    context->kernelArgs.disparityStep,
                    (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX],
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
                    (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
                    context->scratchBufferStride,
                    context->kernelArgs.direction
            );
        }
        else {
            wrapper_vcop_disparity_hammingDistance32_nth_row(
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    (uint32_t*)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    context->kernelArgs.leftStride,
                    context->kernelArgs.rightStride,
                    context->kernelArgs.winWidth,
                    context->kernelArgs.winHeight,
                    (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                    (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + context->kernelArgs.allCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                    context->kernelArgs.allCostOutputStride,
                    context->kernelArgs.width,
                    context->kernelArgs.numDisparities,
                    context->kernelArgs.disparityStep,
                    (uint8_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX],
                    (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX] + 1,
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX],
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX],
                    (int16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
                    (int16_t*)context->pInBlock[DISPARITY_HAMDIST_CARRYOVER_IN_IDX],
                    (int16_t*)context->pOutBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX],
                    context->scratchBufferStride,
                    context->kernelArgs.direction
            );
        }
    }

    if (context->kernelArgs.adjacentCosts== 1) {

        uint16_t i;
        uint8_t prevIdx, nextIdx, disparityStepShift;

        if (context->kernelArgs.direction== 1) {
            prevIdx= DISPARITY_HAMDIST_NEXT_ADJ_COST;
            nextIdx= DISPARITY_HAMDIST_PREV_ADJ_COST;
        }
        else {
            nextIdx= DISPARITY_HAMDIST_NEXT_ADJ_COST;
            prevIdx= DISPARITY_HAMDIST_PREV_ADJ_COST;
        }

        i=1;
        while (context->kernelArgs.disparityStep>>i) {
            i++;
        }
        disparityStepShift= i-1;

        vcop_disparity_genPrevAndNextMinCost
        (
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + context->kernelArgs.allCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                (uint16_t*)context->pOutBlock[prevIdx],
                (uint16_t*)context->pOutBlock[nextIdx],
                (uint16_t*)context->pInternalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX],
                context->kernelArgs.width,
                context->kernelArgs.allCostOutputStride, /* allCostStride in bytes */
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                disparityStepShift
        );
    }

#else /* Below is executed in target mode */

    if (context->kernelArgs.direction== 0) {
        /* For the first segment of the first row, call vcop_disparity_hammingDistance32_first_row_firstCall_vloops()
         * Otherwise for the remaining segments of the first row, call vcop_disparity_hammingDistance32_first_row_vloops() */
        if (context->vertBlockIdx== 0) {
            if (context->horzBlockIdx== 0) {
                vcop_disparity_hammingDistance32_first_row_firstCall_vloops(context->pFirstRowFirstCallParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(context->pRLFirstCallParams[0]);
            }*/
            }
            else {
                vcop_disparity_hammingDistance32_first_row_vloops(context->pFirstRowParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                vcop_disparity_hammingDistance_row_right_left_vloops(context->pRLParams[0]);
            }*/
            }
        }
        else { /* For the first segment of the nth row (different than 1st row), call vcop_disparity_hammingDistance32_nth_row_firstCall_vloops */
            if (context->horzBlockIdx== 0) {
                vcop_disparity_hammingDistance32_nth_row_firstCall_vloops(context->pNthRowFirstCallParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(context->pRLFirstCallParams[0]);
            }*/
            }
            else { /* For the remaining segments of the nth row, call vcop_disparity_hammingDistance32_nth_row_vloops() */
                vcop_disparity_hammingDistance32_nth_row_vloops(context->pNthRowParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                vcop_disparity_hammingDistance_row_right_left_vloops(context->pRLParams[0]);
            }*/
            }
        }
    }
    else {
        /* For the first segment of the first row, call vcop_disparity_hammingDistance32_first_row_firstCall_vloops()
         * Otherwise for the remaining segments of the first row, call vcop_disparity_hammingDistance32_first_row_vloops() */
        if (context->vertBlockIdx== 0) {
            if (context->horzBlockIdx== 0) {
                vcop_disparity_hammingDistance32_RL_first_row_firstCall_vloops(context->pFirstRowFirstCallParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                        vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(context->pRLFirstCallParams[0]);
                    }*/
            }
            else {
                vcop_disparity_hammingDistance32_RL_first_row_vloops(context->pFirstRowParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                        vcop_disparity_hammingDistance_row_right_left_vloops(context->pRLParams[0]);
                    }*/
            }
        }
        else { /* For the first segment of the nth row (different than 1st row), call vcop_disparity_hammingDistance32_nth_row_firstCall_vloops */
            if (context->horzBlockIdx== 0) {
                vcop_disparity_hammingDistance32_RL_nth_row_firstCall_vloops(context->pNthRowFirstCallParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                        vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(context->pRLFirstCallParams[0]);
                    }*/
            }
            else { /* For the remaining segments of the nth row, call vcop_disparity_hammingDistance32_nth_row_vloops() */
                vcop_disparity_hammingDistance32_RL_nth_row_vloops(context->pNthRowParams[0]);
                /*if (context->kernelArgs.extraRLdisparities== 1) {
                        vcop_disparity_hammingDistance_row_right_left_vloops(context->pRLParams[0]);
                    }*/
            }
        }
    }

    if (context->kernelArgs.adjacentCosts== 1) {
        vcop_disparity_genPrevAndNextMinCost_vloops(context->pGenPrevAndNextMinCostParams[0]);
    }

    /* For sliding window in the circular buffer, update some of the pointer entries in the pblocks in the image buffer not being processed */
    Bam_DisparityHamDist32_updateParamRegs(context);

#endif /* VCOP_HOST_EMULATION */

    /* Update all the offsets in a circular buffer fashion */
    context->prevRowLeftOffset+=  context->kernelArgs.leftStride;
    if (context->prevRowLeftOffset== context->leftEndMarker) {
        context->prevRowLeftOffset= 0;
    }

    context->lastRowLeftOffset+=  context->kernelArgs.leftStride;
    if (context->lastRowLeftOffset== context->leftEndMarker) {
        context->lastRowLeftOffset= 0;
    }

    context->prevRowRightOffset+=  context->kernelArgs.rightStride;
    if (context->prevRowRightOffset== context->rightEndMarker) {
        context->prevRowRightOffset= 0;
    }

    context->lastRowRightOffset+=  context->kernelArgs.rightStride;
    if (context->lastRowRightOffset== context->rightEndMarker) {
        context->lastRowRightOffset= 0;
    }

    context->updateVertBlockIdx++;
    if (context->updateVertBlockIdx== context->kernelArgs.numRows){
        context->updateVertBlockIdx= 0;
        context->updateHorzBlockIdx++;

        context->prevRowLeftOffset= context->prevRowLeftInitOffset;
        context->prevRowRightOffset= context->prevRowRightInitOffset;
        context->lastRowLeftOffset= context->lastRowLeftInitOffset;
        context->lastRowRightOffset= context->lastRowRightInitOffset;

    }

    context->vertBlockIdx++;
    if (context->vertBlockIdx== context->kernelArgs.numRows){ /* Roll back vertBlockIdx if end of circular buffer reached */
        context->vertBlockIdx= 0;
        context->horzBlockIdx++;

    }
    context->pingPongFlag^=1U;

    return status;
}


#if (!VCOP_HOST_EMULATION)
/* The function below is defined only in target mode as it is not used in HOST mode */
static void Bam_DisparityHamDist32_updateParamRegs(BAM_DisparityHamDist_Context *context){

    if (context->updateVertBlockIdx!= 0) {
        if (context->updateHorzBlockIdx== 0) {
            vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr(
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    context->kernelArgs.winWidth,
                    context->kernelArgs.disparityStep,
                    (uint32_t**)(void*)&context->nth_row_firstCall_leftPrevRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_firstCall_leftLastRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_firstCall_rightPrevRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_firstCall_rightLastRowPtr[context->pingPongFlag],
                    context->kernelArgs.direction
            );
        }
        else {
            vcop_disparity_hammingDistance32_nth_row_setPtr(
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->prevRowLeftOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4 + context->lastRowLeftOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.leftStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->prevRowRightOffset),/*((context->vertBlockIdx - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    (uint32_t)(*(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4 + context->lastRowRightOffset),/*((context->vertBlockIdx + context->kernelArgs.winHeight - 1)%numLinesInBuf)*context->kernelArgs.rightStride),*/
                    context->kernelArgs.winWidth,
                    context->kernelArgs.disparityStep,
                    (uint32_t**)(void*)&context->nth_row_leftPrevRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_leftLastRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_rightPrevRowPtr[context->pingPongFlag],
                    (uint32_t**)(void*)&context->nth_row_rightLastRowPtr[context->pingPongFlag],
                    context->kernelArgs.direction
            );
        }
    }
}
#endif

BAM_KernelExecFuncDef gBAM_TI_disparityHamDist_ExecFunc =
{ NULL, &Bam_DisparityHamDist_initFrame, &BAM_DisparityHamDist_compute, NULL, &BAM_DisparityHamDist_control, NULL };

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

