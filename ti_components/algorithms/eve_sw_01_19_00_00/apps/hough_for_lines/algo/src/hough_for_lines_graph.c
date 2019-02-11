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
 *  @file      hough_for_lines_graph.c
 *
 *  @brief      This file defines the functions for hough_for_lines graph
 *  @version 0.0 (Dec 2013) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ihough_for_lines_ti.h"
#include "hough_for_lines_graph_int.h"
#include "edma_utils.h"



static int32_t HOUGH_FOR_LINES_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE           (0)
#define HOUGH_FOR_LINES_NODE  (1U)
#define SINK_NODE             (2)


typedef enum hough_for_linesCorenerDetectbam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_IN_NODE,
    BAM_TI_KERNELID_HOUGH_FOR_LINES,
    BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_OUT_NODE
} BAM_HOUGH_FOR_LINES_CORNDER_DETECT_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamHoughForLinesCornerDetectKernelHostDB[] =
{
  { &gBAM_TI_dmaCustomHoughForLinesNodeReadKernel,  &gBAM_TI_dmaCustomHoughForLinesNodeReadKernelHelperFunc,
                                  "ti_dma_custom_hough_for_lines_in_node", BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_IN_NODE},
  { &gBAM_TI_houghForLinesKernel, &gBAM_TI_houghForLinesHelperFunc,
                                 "ti_image_hough_for_lines", BAM_TI_KERNELID_HOUGH_FOR_LINES},
  { &gBAM_TI_dmaCustomHoughForLinesNodeWriteKernel, &gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelHelperFunc,
                                 "ti_dma_custom_hough_for_lines_out_node", BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_OUT_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamHoughForLinesCornerDetectKernelExecFuncDB[] =
{
  { &gBAM_TI_dmaCustomHoughForLinesNodeReadKernel,  &gBAM_TI_dmaCustomHoughForLinesNodeReadKernelExecFunc,
                            "ti_dma_custom_hough_for_lines_in_node", BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_IN_NODE},
  { &gBAM_TI_houghForLinesKernel, &gBAM_TI_houghForLinesExecFunc,
                            "ti_image_hough_for_lines", BAM_TI_KERNELID_HOUGH_FOR_LINES},
  { &gBAM_TI_dmaCustomHoughForLinesNodeWriteKernel, &gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelExecFunc,
                            "ti_dma_custom_hough_for_lines_out_node", BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_OUT_NODE},
};

BAM_KernelDBdef gHoughForLinesCornerDetect_TI_BAM_kernelDBdef =
{
  sizeof(bamHoughForLinesCornerDetectKernelExecFuncDB) / sizeof(bamHoughForLinesCornerDetectKernelExecFuncDB[0]),
  bamHoughForLinesCornerDetectKernelHostDB,
  bamHoughForLinesCornerDetectKernelExecFuncDB
};


int32_t HOUGH_FOR_LINES_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = HOUGH_FOR_LINES_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = HOUGH_FOR_LINES_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = HOUGH_FOR_LINES_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(HOUGH_FOR_LINES_TI_graphArgs) ;
  return 0;
}

int32_t HOUGH_FOR_LINES_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      HOUGH_FOR_LINES_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    HOUGH_FOR_LINES_TI_graphArgs * graphArgs = (HOUGH_FOR_LINES_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]=
    {
        {SOURCE_NODE,               BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_IN_NODE,      NULL},
        {HOUGH_FOR_LINES_NODE,      BAM_TI_KERNELID_HOUGH_FOR_LINES,                     NULL},
        {SINK_NODE,                 BAM_TI_KERNELID_CUSTOM_HOUGH_FOR_LINES_OUT_NODE,     NULL},
        {BAM_END_NODE_MARKER,       0,                                        NULL},
    };

    BAM_EdgeParams EDGELIST[]=
    {
          {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},    {HOUGH_FOR_LINES_NODE,  BAM_HOUGH_FOR_LINES_EDGE_LIST_PORT}},\
          {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT2},    {HOUGH_FOR_LINES_NODE,  BAM_HOUGH_FOR_LINES_VOTED_RHO_THETA_IN_PORT}},\
          {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT2},    {SINK_NODE, BAM_SINK_NODE_PORT1}},\
          {{BAM_END_NODE_MARKER, 0},                 {BAM_END_NODE_MARKER, 0}},\
    };

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/

  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;
  graphCreateParams.blockDimParams.blockWidth  = 0;
  graphCreateParams.blockDimParams.blockHeight = 0;

  status = BAM_initKernelDB(&gHoughForLinesCornerDetect_TI_BAM_kernelDBdef);
  if(status != BAM_S_SUCCESS)
  {
    PRINTF("Hough For Lines BAM_initKernelDB failed!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gHoughForLinesCornerDetect_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = HOUGH_FOR_LINES_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = HOUGH_FOR_LINES_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = HOUGH_FOR_LINES_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

  graphArgs->createParams = createParams;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &HOUGH_FOR_LINES_TI_initKernelsArgs;
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
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-------------------------------------------------------------------------*/
  /* error message handling and return of error code                         */
  /*-------------------------------------------------------------------------*/
Exit:
  if (status== BAM_E_INVALID_MEM_SIZE)
  {
    PRINTF("Hough For Lines graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Hough For Lines graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
      graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
  }
  else if (status != BAM_S_SUCCESS)
  {
    PRINTF("Hough For Lines graph construction failed!!!");
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
static int32_t HOUGH_FOR_LINES_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  /* Not needed as all allocations are happening for maximum list possible */


  return (status);

}


int32_t HOUGH_FOR_LINES_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const HOUGH_FOR_LINES_InArgs * inArgs,
        uint8_t * ptrToList,
        uint8_t * ptrToRhoThetaSpace,
        uint16_t  currListSize)
{
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    int32_t status = BAM_S_SUCCESS;
    BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs ctrlArgs;


    ctrlArgs.listSize                 = currListSize;
    ctrlArgs.rhoMaxLength             = inArgs->rhoMaxLength;
    ctrlArgs.thetaStart               = inArgs->thetaStart;
    ctrlArgs.thetaEnd                 = inArgs->thetaEnd;
    ctrlArgs.thetaStepSize            = inArgs->thetaStepSize;
    ctrlArgs.ptrToList                = ptrToList;
    ctrlArgs.ptrToVotedRhoThetaSpace  = ptrToRhoThetaSpace;

    status = BAM_controlNode(graphHandle, SOURCE_NODE, (void *)&ctrlArgs);

    if (status != BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

 Exit:
    return status;
}

int32_t HOUGH_FOR_LINES_TI_graphKernelControl(const BAM_GraphMem *graphMem,
        const HOUGH_FOR_LINES_InArgs * inArgs,
        uint16_t  currListSize)
{
  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  BAM_HoughForLines_CtrlArgs ctrlArgs;
  int32_t status = BAM_S_SUCCESS;

  ctrlArgs.imgWidth       = inArgs->imgWidth;
  ctrlArgs.imgHeight      = inArgs->imgHeight;
  ctrlArgs.listSize       = currListSize;
  ctrlArgs.thetaStart     = inArgs->thetaStart;
  ctrlArgs.thetaEnd       = inArgs->thetaEnd;
  ctrlArgs.thetaStepSize  = inArgs->thetaStepSize;
  ctrlArgs.rhoMaxLength   = inArgs->rhoMaxLength;

  status = BAM_controlNode(graphHandle, HOUGH_FOR_LINES_NODE, (void *)&ctrlArgs);

  if (status != BAM_S_SUCCESS)
  {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

Exit:
  return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t HOUGH_FOR_LINES_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}


