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
 *  @file       bam_natcBlockSortU32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of BlockSortU32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_sort_cn.h"
#include "bam_blockSortU32_int.h"
#include "bam_blockSortU32.h"
#include "../inc/merge_sort.h"

#if VCOP_HOST_EMULATION
static int32_t beg[1000];
static int32_t end[1000];
#else
/* CHECK_MISRA("-8.7")  -> Disable rule 8.7 */
/* Name visibility is too wide */
/* Deviation is allowed because these arrays must go to far sections */
static far int32_t beg[1000];
static far int32_t end[1000];
/*RESET_MISRA("8.7")  -> Reset rule 8.7  */
#endif


/* Function Prototypes */
static BAM_Status BAM_natcBlockSortU32_computeFrame(void *kernelContext);
static BAM_Status BAM_natcBlockSortU32_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_natcBlockSortU32_control(void *kernelContext, void *kernelCtlArg){

    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_BlockSortU32_CtlArgs *ctlArg= (BAM_BlockSortU32_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_BLOCKSORT_U32_CMD_SET_PTR){
        context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT]= ctlArg->inputPtr;
        context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT]= ctlArg->outputPtr;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status BAM_natcBlockSortU32_computeFrame(void *kernelContext)
{
    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT], context->kernelArgs.numElmts*4U);
    vcop_sort_cn(context->kernelArgs.numElmts, (uint32_t*)context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], beg, end);

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcBlockSortU32ExecFunc =
{ NULL, NULL, &BAM_natcBlockSortU32_computeFrame, NULL, &BAM_natcBlockSortU32_control, NULL };

