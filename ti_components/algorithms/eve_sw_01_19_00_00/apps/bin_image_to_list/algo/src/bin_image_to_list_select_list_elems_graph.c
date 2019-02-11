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
 *  @file      bin_image_to_list_with_masking_graph.c
 *
 *  @brief      This file defines the functions for graph for Bin Img To List applet
 *
 *  @version 0.0 (April 2015) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ibin_image_to_list_ti.h"

#include "bin_image_to_list_alg_int.h"

#include "bin_image_to_list_select_list_elems_graph_int.h"

#include "edma_utils.h"
#include "bam_dma_autoincrement_node.h"

static int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

/* Graph2 is for using bin to list alone */
#define SOURCE_NODE                 (0)
#define SELECT_LIST_ELEM_NODE       (1U)
#define SINK_NODE            (2U)

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE,
    BAM_TI_KERNELID_SELECT_LIST_ELEMENT,
    BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE
} BAM_BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamSelectListElemKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomSelectListElemNodeReadKernel, &gBAM_TI_dmaCustomSelectListElemNodeReadKernelHelperFunc,
            "ti_custom_bin_to_list_dma_read", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE},

    { &gBAM_TI_selecListElementsKernel,   &gBAM_TI_selecListElementsHelperFunc,
            "ti_select_list_elements",   BAM_TI_KERNELID_SELECT_LIST_ELEMENT },

    { &gBAM_TI_dmaCustomSelectListElemNodeWriteKernel, &gBAM_TI_dmaCustomSelectListElemNodeWriteKernelHelperFunc,
            "ti_custom_bin_to_list_dma_write", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamSelectListElemKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomSelectListElemNodeReadKernel, &gBAM_TI_dmaCustomSelectListElemNodeReadKernelExecFunc,
            "ti_custom_bin_to_list_dma_read", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE},

    { &gBAM_TI_selecListElementsKernel,   &gBAM_TI_selecListElementsExecFunc,
            "ti_select_list_elements",   BAM_TI_KERNELID_SELECT_LIST_ELEMENT },


    { &gBAM_TI_dmaCustomSelectListElemNodeWriteKernel, &gBAM_TI_dmaCustomSelectListElemNodeWriteKernelExecFunc,
            "ti_custom_bin_to_list_dma_write", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE},
};


BAM_KernelDBdef gSelectListElem_BAM_TI_kernelDBdef =
{
    sizeof(bamSelectListElemKernelExecFuncDB) / sizeof(bamSelectListElemKernelExecFuncDB[0]),
    bamSelectListElemKernelHostDB,
    bamSelectListElemKernelExecFuncDB
};



int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs) ;
  return 0;
}

int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs * graphArgs = (BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]= {\
            {SOURCE_NODE,           BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE,  NULL},\
            {SELECT_LIST_ELEM_NODE, BAM_TI_KERNELID_SELECT_LIST_ELEMENT,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs      = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[SELECT_LIST_ELEM_NODE].kernelArgs      = (void *)&graphArgs->selectListElemsKernelArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {SELECT_LIST_ELEM_NODE, BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT}},\

            {{SELECT_LIST_ELEM_NODE, BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{SELECT_LIST_ELEM_NODE, BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT2}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gSelectListElem_BAM_TI_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gSelectListElem_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_CONTEXT_SIZE;

    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    status = BAM_createGraph(&graphCreateParams, &graphHandle);
    if(status != BAM_S_SUCCESS)
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/
  Exit:
    if (status== BAM_E_INVALID_MEM_SIZE)
    {
      PRINTF("BIN_IMAGE_TO_LIST : Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("BIN_IMAGE_TO_LIST  : Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("BIN_IMAGE_TO_LIST  : Graph construction failed!!!");
    }
    else
    {
      /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs              *graphArgs          = (BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs*)args;
  BAM_Select_list_elements_Args                     *selectListElemKernelArgs  = &(graphArgs->selectListElemsKernelArgs);
  BAM_DMA_CUSTOM_SELECT_LIST_ELEM_READ_args       *dmaReadKernelArgs        = &(graphArgs->dmaReadKernelArgs);

  /* allocate maximum input block size */
  dmaReadKernelArgs->maxListSize = 4064;

  selectListElemKernelArgs->maxListChunkSize    = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_MAX_LIST_SIZE;
  selectListElemKernelArgs->maxSelectionMaxSize = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_execute(
        const BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  status  = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint32_t listSize,
                                  uint16_t listChunkSize,
                                  uint8_t  selectionMaskSize,
                                  uint8_t  *selectionMaskPtr
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_Select_list_elements_ctrlArgs     selectListElemCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  selectListElemCtrlArgs.listChunkSize      = listChunkSize;
  selectListElemCtrlArgs.listSize           = listSize;
  selectListElemCtrlArgs.selectionMaskSize  = selectionMaskSize;
  selectListElemCtrlArgs.selectionMaskPtr   = selectionMaskPtr;

  status = BAM_controlNode( graphHandle, SELECT_LIST_ELEM_NODE, &selectListElemCtrlArgs);
  if (status!= BAM_S_SUCCESS)
  {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

Exit:
  return status;
}


int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t * inputListPtr,
                                uint8_t * outputListPtr,
                                uint8_t * ptrToListSize,
                                uint32_t  listSize,
                                uint16_t  listChunkSize
                                )

{
    BAM_DMA_CUSTOM_SELECT_LIST_ELEM_READ_ctrlArgs dmaReadUpdateParams;
    BAM_DMA_CUSTOM_SELECT_LIST_ELEM_WRITE_ctrlArgs dmaWriteUpdateParams;

    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint32_t totalLength;

    totalLength  = CEIL(listSize,  listChunkSize);


    dmaReadUpdateParams.inTransferProp.totalLength      = totalLength * sizeof(uint32_t);
    dmaReadUpdateParams.inTransferProp.numBytes         = listChunkSize * sizeof(uint32_t);
    dmaReadUpdateParams.inTransferProp.extMemPtr        = inputListPtr;
    dmaReadUpdateParams.inTransferProp.extMemIncrement  = listChunkSize * sizeof(uint32_t);
    dmaReadUpdateParams.inTransferProp.intMemIncrement  = 0;
    dmaReadUpdateParams.inTransferProp.dmaQueNo         = 0;
    dmaReadUpdateParams.inTransferProp.numCircBuf       = 1U;

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadUpdateParams);

    if (status!= BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    dmaWriteUpdateParams.ptrToListBuf     = outputListPtr;
    dmaWriteUpdateParams.ptrToListSizeBuf = ptrToListSize;

    status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteUpdateParams);


 Exit:
    return status;
}

