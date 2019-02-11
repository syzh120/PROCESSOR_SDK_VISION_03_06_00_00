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
 *  @file       bam_select_list_elements_exec_funcs.c
 *
 *  @brief      This file implements interfaces for integrating select list elements
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <vcop.h>

#include "bam_select_list_elements_int.h"
#include "vcop_select_list_elements_kernel.h" /* compiler should take care of include path */

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define BAM_SELECT_LIST_ELEMENTS_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

/* Function Prototypes */
static BAM_Status Bam_Select_list_elements_initFrame(void *kernelContext);

static BAM_Status Bam_Select_list_elements_initFrame(void *kernelContext)
{
    BAM_Select_list_elements_Context *context = (BAM_Select_list_elements_Context *) kernelContext;
    BAM_Status status = BAM_S_SUCCESS;
    uint16_t pReg4Val;
    uint16_t pReg14Val;

    if ( (context->ctrlArgs.selectionMaskSize % VCOP_SIMD_WIDTH) != 0 )
    {
      status = BAM_E_FAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    }
    memcpy( context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
            context->ctrlArgs.selectionMaskPtr,
            context->ctrlArgs.selectionMaskSize * sizeof(uint8_t));

    context->blkIdx = 0;
    context->numBlks = BAM_SELECT_LIST_ELEMENTS_CEIL(context->ctrlArgs.listSize, context->ctrlArgs.listChunkSize) /
                          context->ctrlArgs.listChunkSize;

    context->numElemsInLaskBlk = context->ctrlArgs.listSize -
            ((context->numBlks - 1U) * context->ctrlArgs.listChunkSize);

    /* make the last list chunk size to be multiple of selectionMaskSize as per the requirement of the kernel */
    /* Because of this few extra corners will be detected whcih we should take care */
    context->numElemsInLaskBlk = BAM_SELECT_LIST_ELEMENTS_CEIL(context->numElemsInLaskBlk, context->ctrlArgs.selectionMaskSize);

#if (!VCOP_HOST_EMULATION)
      pReg4Val = ((context->numElemsInLaskBlk / context->ctrlArgs.selectionMaskSize))- (uint16_t)1U;
      pReg14Val = (uint16_t)0 - ((uint16_t)1U * (((context->ctrlArgs.selectionMaskSize*sizeof(uint32_t))*(((context->numElemsInLaskBlk /
                        context->ctrlArgs.selectionMaskSize))- (uint16_t)1U)) - (((uint16_t) 8U * sizeof(uint32_t)) *
                        (((context->ctrlArgs.selectionMaskSize / (uint16_t)(8U)))- (uint16_t)1U))));

      vcop_select_list_elements_init((uint32_t*)context->pInBlock[BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT],
                                 (uint32_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT],
                                 (uint8_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
                                 (uint16_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT],
                                 context->ctrlArgs.listChunkSize,
                                 context->ctrlArgs.selectionMaskSize,
                                 (uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX]);
      vcop_select_list_elements_param_block_update_init((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX],
                                                        pReg4Val,
                                                        pReg14Val,
                                                        (uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX]);

#endif
EXIT:

    return status;
}

static BAM_Status Bam_Select_list_elements_computeFrame(void *kernelContext);

static BAM_Status Bam_Select_list_elements_computeFrame(void *kernelContext)
{
    BAM_Select_list_elements_Context *context = (BAM_Select_list_elements_Context *) kernelContext;
#if VCOP_HOST_EMULATION
    uint16_t numElemsPerBlock;
    numElemsPerBlock = (context->blkIdx == context->numBlks - 1) ?
                         context->numElemsInLaskBlk :
                         context->ctrlArgs.listChunkSize;

    vcop_select_list_elements((uint32_t*)context->pInBlock[BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT],
                                 (uint32_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT],
                                 (uint8_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
                                 (uint16_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT],
                                 numElemsPerBlock,
                                 context->ctrlArgs.selectionMaskSize);

#else
    vcop_select_list_elements_vloops((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX]);

    if( context->blkIdx == (context->numBlks - 2) )
    {
      vcop_select_list_elements_param_block_update_vloops((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX]);
    }
#endif
    context->blkIdx++;

    return 0;

}


static BAM_Status Bam_Select_list_elements_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status Bam_Select_list_elements_control(void *kernelContext, void *kernelCtlArg){

    BAM_Select_list_elements_Context *context   = (BAM_Select_list_elements_Context *) kernelContext;
    BAM_Select_list_elements_ctrlArgs *ctrlArgs = (BAM_Select_list_elements_ctrlArgs *) kernelCtlArg;
    BAM_Status status = BAM_S_SUCCESS;

    if ( (ctrlArgs->listChunkSize <= context->kernelArgs.maxListChunkSize) &&
          (ctrlArgs->selectionMaskSize <= context->kernelArgs.maxSelectionMaxSize) )
    {
      context->ctrlArgs = *ctrlArgs;
    }
    else
    {
      status = BAM_E_FAIL;
    }

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_selecListElementsExecFunc =
{
    NULL,
    &Bam_Select_list_elements_initFrame,
    &Bam_Select_list_elements_computeFrame,
    NULL,
    &Bam_Select_list_elements_control,
    NULL
};

