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
 *  @file       bam_ncc_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating normalized cross correlation kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_ncc_int.h"
#include "bam_ncc.h"
#include "vcop_ncc_kernel.h"
#include "init_slidingSum_params.h"
#include "edma_utils_memcpy.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

/* Function Prototypes */
static BAM_Status BAM_Ncc_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status Bam_Ncc_initFrame(void *kernelContext);
static BAM_Status BAM_Ncc_compute(void *kernelContext);

static BAM_Status BAM_Ncc_control(void *kernelContext, void *kernelCtlArg){

    BAM_Ncc_Context *context = (BAM_Ncc_Context *) kernelContext;
    BAM_Ncc_CtlArgs *ctlArg= (BAM_Ncc_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_NCC_CMD_SET_TEMPLATE_PTR){
        context->kernelArgs.pExtTemplate= ctlArg->pExtTemplate;
        context->kernelArgs.templateExtPitch= ctlArg->templateExtPitch;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status Bam_Ncc_initFrame(void *kernelContext)
{
    uint16_t sizeOfScratch, sizeOfSum;
    BAM_Ncc_Context *context = (BAM_Ncc_Context *) kernelContext;
    BAM_Status status = 0;

    EDMA_UTILS_memcpy2D(context->pInternalBlock[NCC_TEMPLATE_IDX],
                        (const void *)context->kernelArgs.pExtTemplate,
                        (uint16_t)context->kernelArgs.templateWidth*(uint16_t)sizeof(*(context->kernelArgs.pExtTemplate)),
                        (uint16_t)context->kernelArgs.templateHeight,
                        (int16_t)((int16_t)context->kernelArgs.templateWidth*(int16_t)sizeof(*(context->kernelArgs.pExtTemplate))),
                        (int16_t)((int16_t)context->kernelArgs.templateExtPitch*(int16_t)sizeof(*(context->kernelArgs.pExtTemplate))));

    status= init_slidingSum_params
            (
                    context->kernelArgs.templateWidth,       /*template image width*/
                    context->kernelArgs.templateHeight,      /*template image height*/
                    context->kernelArgs.outputWidth,         /*output width */
                    context->kernelArgs.outputHeight,        /*output height */
                    (uint16_t*)context->pInternalBlock[NCC_OFFSET_IDX], /* Point to an array of 32 bytes */
                    32U, /* Should be 32 */
                    &context->scratchStride,
                    &sizeOfScratch,
                    &context->sumStride,
                    &sizeOfSum);

    if (status !=0) {
        goto Exit;
    }

    if (context->scratchStride != ((uint16_t)((((uint16_t)4*context->kernelArgs.outputHeight) + (uint16_t)31U) & ((uint16_t)(~(uint16_t)31U))) + (uint16_t)4U)) {
        status= 1;
        goto Exit;
    }

    if (context->sumStride != ((uint16_t)((((uint16_t)4*context->kernelArgs.outputWidth) + (uint16_t)31U) & ((uint16_t)(~(uint16_t)31U))) + (uint16_t)4U)) {
        status= 1;
        goto Exit;
    }

#if (!VCOP_HOST_EMULATION)

    vcop_slidingSum_init(
            (uint8_t*)context->pInBlock[NCC_IN_IDX],
            context->kernelArgs.inPitch,        /*original input image pitch*/
            context->kernelArgs.templateWidth,       /*template image width*/
            context->kernelArgs.templateHeight,      /*template image height*/
            context->kernelArgs.outputWidth,
            context->kernelArgs.outputHeight,
            (int32_t*)context->pInternalBlock[NCC_SCRATCH_IDX],
            context->scratchStride,
            (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
            context->sumStride,
            (uint16_t*)context->pInternalBlock[NCC_OFFSET_IDX], /* Point to an array of 32 bytes. Call init_slidingSum_params() to initialize content pointed by pOffset*/
            (int32_t*)context->pInternalBlock[NCC_SCRATCH_LINE_IDX],
            context->pInternalBlock[NCC_SLIDING_SUM_PARAMS_IDX]
    );

    if (context->kernelArgs.qShift== 0) {
          /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
          /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
          /*  Pointer arithmetic is required as kernel code needs internal memory which is offset from the base pointer.
          The allocation of this memory is taking care that we dont access beyond the allocated region*/
        vcop_ncc_qShift0_init(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                (context->kernelArgs.outputWidth + (uint16_t)context->kernelArgs.templateWidth) - (uint16_t)1,
                (context->kernelArgs.outputHeight + (uint16_t)context->kernelArgs.templateHeight) - (uint16_t)1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch,           /*Out Score buffer pitch*/
                context->pInternalBlock[NCC_PARAMS_IDX]
        );
    }
    else if (context->kernelArgs.qShift== 8) {
        vcop_ncc_qShift8_init(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                (context->kernelArgs.outputWidth + (uint16_t)context->kernelArgs.templateWidth) - (uint16_t)1,
                (context->kernelArgs.outputHeight + (uint16_t)context->kernelArgs.templateHeight) - (uint16_t)1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch,           /*Out Score buffer pitch*/
                context->pInternalBlock[NCC_PARAMS_IDX]
        );
    }
    else {

        vcop_ncc_init(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                (context->kernelArgs.outputWidth + (uint16_t)context->kernelArgs.templateWidth) - (uint16_t)1,
                (context->kernelArgs.outputHeight + (uint16_t)context->kernelArgs.templateHeight) - (uint16_t)1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch,           /*Out Score buffer pitch*/
                context->pInternalBlock[NCC_PARAMS_IDX]
        );
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    }
#endif

    Exit:
    return status;
}


static BAM_Status BAM_Ncc_compute(void *kernelContext)
{
    BAM_Ncc_Context *context = (BAM_Ncc_Context *) kernelContext;
    BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    vcop_slidingSum_vloops((uint16_t*)context->pInternalBlock[NCC_SLIDING_SUM_PARAMS_IDX]);

    if (context->kernelArgs.qShift== 0) {
        vcop_ncc_qShift0_vloops((uint16_t*)context->pInternalBlock[NCC_PARAMS_IDX]);
    }
    else if (context->kernelArgs.qShift== 8) {
        vcop_ncc_qShift8_vloops((uint16_t*)context->pInternalBlock[NCC_PARAMS_IDX]);
    }
    else {
        vcop_ncc_vloops((uint16_t*)context->pInternalBlock[NCC_PARAMS_IDX]);
    }
#else
    vcop_slidingSum(
            (uint8_t*)context->pInBlock[NCC_IN_IDX],
            context->kernelArgs.inPitch,        /*original input image pitch*/
            context->kernelArgs.templateWidth,       /*template image width*/
            context->kernelArgs.templateHeight,      /*template image height*/
            context->kernelArgs.outputWidth,
            context->kernelArgs.outputHeight,
            (int32_t*)context->pInternalBlock[NCC_SCRATCH_IDX],
            context->scratchStride,
            (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
            context->sumStride,
            (uint16_t*)context->pInternalBlock[NCC_OFFSET_IDX], /* Point to an array of 32 bytes. Call init_slidingSum_params() to initialize content pointed by pOffset*/
            (int32_t*)context->pInternalBlock[NCC_SCRATCH_LINE_IDX]
    );

    if (context->kernelArgs.qShift== 0) {
        vcop_ncc_qShift0(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                context->kernelArgs.outputWidth + context->kernelArgs.templateWidth - 1,
                context->kernelArgs.outputHeight + context->kernelArgs.templateHeight - 1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch
        );
    }
    else if (context->kernelArgs.qShift== 8) {
        vcop_ncc_qShift8(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                context->kernelArgs.outputWidth + context->kernelArgs.templateWidth - 1,
                context->kernelArgs.outputHeight + context->kernelArgs.templateHeight - 1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch
        );
    }
    else {

        vcop_ncc(
                (uint8_t*)context->pInBlock[NCC_IN_IDX],
                context->kernelArgs.outputWidth + context->kernelArgs.templateWidth - 1,
                context->kernelArgs.outputHeight + context->kernelArgs.templateHeight - 1,
                context->kernelArgs.inPitch,        /*original input image pitch*/
                (int16_t*)context->pInternalBlock[NCC_TEMPLATE_IDX],           /*template image pointer*/
                context->kernelArgs.templateWidth,       /*template image width*/
                context->kernelArgs.templateHeight,      /*template image height*/
                context->kernelArgs.templateWidth,       /*template image pitch*/
                (uint32_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX],
                (uint16_t*)context->pInternalBlock[NCC_SUM_IDX] + 1,
                context->sumStride,
                context->kernelArgs.sizeQshift,
                context->kernelArgs.qShift,
                (int32_t*)context->pOutBlock[NCC_NUMCC_OUT_IDX],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                (uint32_t*)context->pOutBlock[NCC_DENOMVAR_OUT_IDX],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                context->kernelArgs.outPitch
        );
    }
#endif
    return status;
}


BAM_KernelExecFuncDef gBAM_TI_ncc_ExecFunc =
{ NULL, &Bam_Ncc_initFrame, &BAM_Ncc_compute, NULL, &BAM_Ncc_control, NULL };

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */
