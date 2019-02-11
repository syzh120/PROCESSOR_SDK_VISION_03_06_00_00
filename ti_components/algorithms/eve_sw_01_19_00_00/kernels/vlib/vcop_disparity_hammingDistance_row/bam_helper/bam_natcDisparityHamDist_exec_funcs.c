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
 *  @file       bam_ntacDisparityHamDist_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hammind distance based disparity calculation 
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_disparityHamDist_int.h"
#include "bam_natcDisparityHamDist.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_postprocess_kernel.h"
#include "vcop_disparity_hammingDistance_row_cn.h"
#include "init_disparity_hammingDistance_row_params.h"

static BAM_Status Bam_natcDisparityHamDist_initFrame(void *kernelContext);
static BAM_Status Bam_natcDisparityHamDist_compute(void *kernelContext);
static BAM_Status BAM_natcDisparityHamDist_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_natcDisparityHamDist_control(void *kernelContext, void *kernelCtlArg){

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

static BAM_Status Bam_natcDisparityHamDist_initFrame(void *kernelContext)
{
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

    context->horzBlockIdx= 0;
    context->vertBlockIdx= 0;

    return status;
}

static BAM_Status Bam_natcDisparityHamDist_compute(void *kernelContext)
{
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

    /* For the first row, we call vcop_disparity_hammingDistance32_first_row_circ_cn() */
    if (context->vertBlockIdx== 0) {
        wrapper_vcop_disparity_hammingDistance32_first_row_circ_cn(
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4,
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4,
                context->kernelArgs.leftStride,
                context->kernelArgs.rightStride,
                context->kernelArgs.winWidth,
                context->kernelArgs.winHeight,
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                context->kernelArgs.width,
                context->kernelArgs.width,
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                context->vertBlockIdx,
                context->kernelArgs.winHeight + 1U,
                context->kernelArgs.direction
        );
    }
    else { /* Subsequent row call vcop_disparity_hammingDistance32_first_row_circ_cn() which is more optimized as it makes use of previous computations results */
        wrapper_vcop_disparity_hammingDistance32_nth_row_circ_cn(
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4,
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4,
                context->kernelArgs.leftStride,
                context->kernelArgs.rightStride,
                context->kernelArgs.winWidth,
                context->kernelArgs.winHeight,
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                context->kernelArgs.width,
                context->kernelArgs.width,
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                context->vertBlockIdx,
                context->kernelArgs.winHeight + 1U,
                context->kernelArgs.direction
        );
    }

    if (context->kernelArgs.adjacentCosts== 1) {

        uint8_t prevIdx, nextIdx;

        if (context->kernelArgs.direction== 1) {
            prevIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            nextIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }
        else {
            nextIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            prevIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }


        vcop_disparity_genPrevAndNextMinCost_cn
        (
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                (uint16_t*)context->pOutBlock[prevIdx],
                (uint16_t*)context->pOutBlock[nextIdx],
                context->kernelArgs.width, /* width */
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep
        );
    }

    context->vertBlockIdx++;
    if (context->vertBlockIdx== context->kernelArgs.numRows){
        context->vertBlockIdx= 0;
        context->horzBlockIdx++;
    }

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_natcDisparityHamDist_ExecFunc =
{ NULL, &Bam_natcDisparityHamDist_initFrame, &Bam_natcDisparityHamDist_compute, NULL, &BAM_natcDisparityHamDist_control, NULL };

