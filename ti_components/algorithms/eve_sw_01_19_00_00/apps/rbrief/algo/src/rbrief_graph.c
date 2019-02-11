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
 *  @file      rbrief_graph.c
 *
 *  @brief      This file defines the functions for rbrief graph
 *  @version 0.0 (Dec 2013) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "irbrief_ti.h"
#include "rbrief_graph_int.h"
#include "edma_utils.h"

static int32_t RBRIEF_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0
#define RBRIEF_NODE  (1U)
#define SINK_NODE     (2U)


typedef enum rbriefCorenerDetectbam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_RBRIEF_SCATTERGATHER_NODE,
    BAM_TI_KERNELID_RBRIEF,
    BAM_TI_KERNELID_CUSTOM_RBRIEF_AUTOINCREMENT_1D_NODE
} BAM_RBRIEF_CORNDER_DETECT_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamRbriefCornerDetectKernelHostDB[] =
{
  { &gBAM_TI_dmaCustomRbriefNodeReadKernel,  &gBAM_TI_dmaCustomRbriefNodeReadKernelHelperFunc,
                                  "ti_dma_custom_rbrif_scatterGather", BAM_TI_KERNELID_CUSTOM_RBRIEF_SCATTERGATHER_NODE},
  { &gBAM_TI_rBriefKernel, &gBAM_TI_rBriefHelperFunc,
                                 "ti_image_rbrief", BAM_TI_KERNELID_RBRIEF},
  { &gBAM_TI_dmaCustomRbriefNodeWriteKernel, &gBAM_TI_dmaCustomRbriefNodeWriteKernelHelperFunc,
                                 "ti_dma_custom_rbrif_autoincrement1d", BAM_TI_KERNELID_CUSTOM_RBRIEF_AUTOINCREMENT_1D_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamRbriefCornerDetectKernelExecFuncDB[] =
{
  { &gBAM_TI_dmaCustomRbriefNodeReadKernel,  &gBAM_TI_dmaCustomRbriefNodeReadKernelExecFunc,
                            "ti_dma_custom_rbrif_scatterGather", BAM_TI_KERNELID_CUSTOM_RBRIEF_SCATTERGATHER_NODE},
  { &gBAM_TI_rBriefKernel, &gBAM_TI_rBriefExecFunc,
                            "ti_image_rbrief", BAM_TI_KERNELID_RBRIEF},
  { &gBAM_TI_dmaCustomRbriefNodeWriteKernel, &gBAM_TI_dmaCustomRbriefNodeWriteKernelExecFunc,
                            "ti_dma_custom_rbrif_autoincrement1d", BAM_TI_KERNELID_CUSTOM_RBRIEF_AUTOINCREMENT_1D_NODE},
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.7  */
/* It is good to have all static variables at one place to increase readability and maintenance of code.
     Hence, if there are 2 functions in a file and one of them need some data to be static -
     he/she will keep it at top of file. As result of this the static data is also visible to another
     function though the function does not need to see it. So the rule is voilated.
*/
static BAM_KernelDBdef gRbriefCornerDetect_TI_BAM_kernelDBdef =
{
  sizeof(bamRbriefCornerDetectKernelExecFuncDB) / sizeof(bamRbriefCornerDetectKernelExecFuncDB[0]),
  bamRbriefCornerDetectKernelHostDB,
  bamRbriefCornerDetectKernelExecFuncDB
};
/* RESET_MISRA("8.7")  -> Reset rule 8.7     */


int32_t RBRIEF_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = RBRIEF_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = RBRIEF_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = RBRIEF_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(RBRIEF_TI_graphArgs) ;
  return 0;
}

int32_t RBRIEF_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      RBRIEF_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    RBRIEF_TI_graphArgs * graphArgs = (RBRIEF_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]=
    {
        {SOURCE_NODE,               BAM_TI_KERNELID_CUSTOM_RBRIEF_SCATTERGATHER_NODE,      NULL},
        {RBRIEF_NODE,               BAM_TI_KERNELID_RBRIEF,                    NULL},
        {SINK_NODE,                 BAM_TI_KERNELID_CUSTOM_RBRIEF_AUTOINCREMENT_1D_NODE,     NULL},
        {BAM_END_NODE_MARKER,       0,                                        NULL},
    };
    /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
    NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
    NODELIST[1].kernelArgs = (void *)(&graphArgs->rBriefKernelArgs);
    NODELIST[2].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
    BAM_EdgeParams EDGELIST[]=
    {
          {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},       {RBRIEF_NODE,  BAM_RBRIEF_INPUT_IMG_PORT}},\
          {{RBRIEF_NODE,     BAM_RBRIEF_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT1}},\
          {{BAM_END_NODE_MARKER, 0},                    {BAM_END_NODE_MARKER, 0}},\
    };

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;
  graphCreateParams.blockDimParams.blockWidth  = 0;
  graphCreateParams.blockDimParams.blockHeight = 0;

  status= BAM_initKernelDB(&gRbriefCornerDetect_TI_BAM_kernelDBdef);

  if(status != BAM_S_SUCCESS)
  {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gRbriefCornerDetect_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = RBRIEF_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = RBRIEF_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = RBRIEF_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

  graphArgs->createParams = createParams;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &RBRIEF_TI_initKernelsArgs;
  graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

  /* Initialize the structure blockDimParams that lists the processing block
  * dimensions as well as the step increment sizes used during the block
  * dimension optimization if enabled
  */
  graphCreateParams.blockDimParams.blockWidth           = RBRIEF_TI_BLOCK_WIDTH;
  graphCreateParams.blockDimParams.blockHeight          = RBRIEF_TI_BLOCK_HEIGHT;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  status = BAM_createGraph(&graphCreateParams, &graphHandle);
  if(status != BAM_S_SUCCESS)
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

  }

  /*-------------------------------------------------------------------------*/
  /* error message handling and return of error code                         */
  /*-------------------------------------------------------------------------*/
Exit:
  if (status== BAM_E_INVALID_MEM_SIZE)
  {
    PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
      graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
  }
  else if (status != BAM_S_SUCCESS)
  {
    PRINTF("Graph construction failed!!!");
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
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t RBRIEF_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */

    uint16_t blkWidthFinal  = 0;
    uint16_t blkHeightFinal = 0;

    int32_t status = BAM_S_SUCCESS;

    RBRIEF_TI_graphArgs *graphArgs                    = (RBRIEF_TI_graphArgs*)args;
    RBRIEF_TI_graphCreateParams *createParams         = graphArgs->createParams;
    BAM_DMA_CUSTOM_RBRIEF_NODE_args *dmaReadKernelArgs          = &(graphArgs->dmaReadKernelArgs);
    BAM_rBrief_Args *rbriefKernelArgs                                = &(graphArgs->rBriefKernelArgs);

    blkWidthFinal  = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    if ( ( blkWidthFinal != RBRIEF_TI_BLOCK_WIDTH ) || ( blkHeightFinal != RBRIEF_TI_BLOCK_HEIGHT ) )
    {
      PRINTF("RBRIEF_TI_initKernelsArgs : Unsupported block Width or height \
              rBrief assumes block width and height to be 48x48\n");
      status = BAM_E_UNSUPPORTED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    dmaReadKernelArgs->blockWidth     = blkWidthFinal;
    dmaReadKernelArgs->blockHeight    = blkHeightFinal;
    dmaReadKernelArgs->numFeatures    = RBRIEF_TI_NUM_FEATURE;
    dmaReadKernelArgs->maxNumFeatures = createParams->iRbriefCreateParams->maxNumFeatures;

  /*--------------------------------------------------------------------------*/
  /*Params Update for rbrief kernel                              */
  /*--------------------------------------------------------------------------*/
  rbriefKernelArgs->orbPattern    = (const int8_t (*)[1024])(void *)createParams->iRbriefCreateParams->orbPattern;


Exit:
  return (status);

}


int32_t RBRIEF_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *inBufDesc,
        const IVISION_BufDesc *xyListBufDesc,
        const IVISION_BufDesc *levelListBufDesc,
        const IVISION_OutBufs *outBuf)
{
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    int32_t status = BAM_S_SUCCESS;
    BAM_DMA_CUSTOM_RBRIEF_READ_ctrlArgs ctrlArgs;

    IVISION_OutBufs tempOutbuf = *outBuf;

    ctrlArgs.inBufDesc         = inBufDesc;
    ctrlArgs.xyListBufDesc     = xyListBufDesc;
    ctrlArgs.levelListBufDesc  = levelListBufDesc;

    status = BAM_controlNode(graphHandle, SOURCE_NODE, (void *)&ctrlArgs);

    if (status != BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    status= BAM_controlNode(graphHandle, SINK_NODE, (void *)&tempOutbuf);

 Exit:
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t RBRIEF_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}


