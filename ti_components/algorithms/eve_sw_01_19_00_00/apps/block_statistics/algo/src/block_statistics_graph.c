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


/*============================================================================*/
/**
 *  @file:      block_statistics_graph.c
 *
 *  @brief:     This file defines the functions for block statistics
 *
 *  @version:   0.2 (Aug 2014) : Base version.
 */
/*============================================================================*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* #pragma RESET_MISRA ("required") */

#include "block_statistics_graph_int.h"
#include "edma_utils.h"

static int32_t BLOCK_STATS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

/* Definitions of the node identifier symbols  */
#define SOURCE_NODE                (0U)
#define BLOCK_STATISTICS_NODE      (1U)
#define SINK_NODE                  (2U)

typedef enum
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT  = 0,
    BAM_TI_KERNELID_BLOCK_STATISTICS       = 1,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT = 2
} BAM_BLOCK_STATISTICS_TI_KernelID;

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamBlockStatisticsKernelHostDB[] =
{
  {&gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  {&gBAM_TI_blockStatisticsKernel, &gBAM_TI_blockStatisticsHelperFunc, "ti_image_block_statistics", BAM_TI_KERNELID_BLOCK_STATISTICS},
  {&gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT}
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamBlockStatisticsKernelExecFuncDB[] =
{
  {&gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  {&gBAM_TI_blockStatisticsKernel, &gBAM_TI_blockStatisticsExecFunc, "ti_image_block_statistics", BAM_TI_KERNELID_BLOCK_STATISTICS},
  {&gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT}
};


BAM_KernelDBdef gBlockStatistics_TI_BAM_kernelDBdef =
{
  sizeof(bamBlockStatisticsKernelExecFuncDB) / sizeof(bamBlockStatisticsKernelExecFuncDB[0]),
  bamBlockStatisticsKernelHostDB,
  bamBlockStatisticsKernelExecFuncDB
};


int32_t BLOCK_STATS_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = BLOCK_STATS_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = BLOCK_STATS_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = BLOCK_STATS_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize     = sizeof(BLOCK_STATS_TI_graphArgs);
  return 0;
}


int32_t BLOCK_STATS_TI_graphCreate(const BAM_GraphMem * graphMem,
            BLOCK_STATS_TI_graphCreateParams * createParams)
{
  BAM_CreateGraphParams graphCreateParams;
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BLOCK_STATS_TI_graphArgs * graphArgs = (BLOCK_STATS_TI_graphArgs *)graphMem->graphArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  /*------------------------------------------------------------------------------*/
  /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
  /*------------------------------------------------------------------------------*/

  /* Definitions of the node paramaters */
  BAM_NodeParams NODELIST[]={\
          {SOURCE_NODE,           BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,  NULL},\
          {BLOCK_STATISTICS_NODE, BAM_TI_KERNELID_BLOCK_STATISTICS,       NULL},\
          {SINK_NODE,             BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT, NULL},\
          {BAM_END_NODE_MARKER,   0,                                      NULL},\
  };

  /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
  NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
  NODELIST[1].kernelArgs = (void *)(&graphArgs->blockStatKernelArgs);
  NODELIST[2].kernelArgs = (void *)(&graphArgs->dmaWriteKernelArgs);

  /* Definitions of the edge paramaters */
  BAM_EdgeParams EDGELIST[]= {\
          {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},                           {BLOCK_STATISTICS_NODE, BAM_BLOCK_STATISTICS_INPUT_PORT}},\
          {{BLOCK_STATISTICS_NODE, BAM_BLOCK_STATISTICS_OUTPUT_PORT_MIN},  {SINK_NODE, BAM_SINK_NODE_PORT1}},\
          {{BLOCK_STATISTICS_NODE, BAM_BLOCK_STATISTICS_OUTPUT_PORT_MAX},  {SINK_NODE, BAM_SINK_NODE_PORT2}},\
          {{BLOCK_STATISTICS_NODE, BAM_BLOCK_STATISTICS_OUTPUT_PORT_MEAN}, {SINK_NODE, BAM_SINK_NODE_PORT3}},\
          {{BLOCK_STATISTICS_NODE, BAM_BLOCK_STATISTICS_OUTPUT_PORT_VAR},  {SINK_NODE, BAM_SINK_NODE_PORT4}},\
          {{BAM_END_NODE_MARKER, 0},                                       {BAM_END_NODE_MARKER, 0}},\
  };

  /* Initialize the structure blockDimParams that lists the processing block
  * dimensions as well as the step increment sizes used during the block
  * dimension optimization if enabled
  */
  graphCreateParams.blockDimParams.blockWidth  = 8*createParams->statBlockWidth;
  graphCreateParams.blockDimParams.blockHeight = 8*createParams->statBlockHeight;
  graphCreateParams.blockDimParams.blockWidthStep  = createParams->statBlockWidth;
  graphCreateParams.blockDimParams.blockHeightStep = createParams->statBlockHeight;
  graphCreateParams.blockDimParams.blockWidthDivisorOf  = createParams->imageWidth;
  graphCreateParams.blockDimParams.blockHeightDivisorOf = createParams->imageHeight;
  graphCreateParams.blockDimParams.blockWidthMax  = createParams->imageWidth;
  graphCreateParams.blockDimParams.blockHeightMax = createParams->imageHeight;

  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  status = BAM_initKernelDB(&gBlockStatistics_TI_BAM_kernelDBdef);
  if(status != BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gBlockStatistics_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = BLOCK_STATS_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = BLOCK_STATS_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = BLOCK_STATS_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

  graphArgs->createParams = createParams;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &BLOCK_STATS_TI_initKernelsArgs;
  graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  status = BAM_createGraph(&graphCreateParams, &graphHandle);
  if(status != BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*
  PRINTF("Graph Memories: graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
  graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  */

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
    /* This is to prevent MISRA C Issue MISRA.IF.NO_ELSE Rule 14.10. */
  }
  return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static void assignDMAautoIncrementParams(
        EDMA_UTILS_autoIncrement_transferProperties * param,
        uint16_t    roiWidth,
        uint16_t    roiHeight,
        uint16_t    blkWidth,
        uint16_t    blkHeight,
        uint16_t    extBlkIncrementX,
        uint16_t    extBlkIncrementY,
        uint16_t    intBlkIncrementX,
        uint16_t    intBlkIncrementY,
        uint32_t    roiOffset,
        uint16_t    blkOffset,
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride,
        uint8_t     dmaQueNo
);

static void assignDMAautoIncrementParams(
        EDMA_UTILS_autoIncrement_transferProperties * param,
        uint16_t    roiWidth,
        uint16_t    roiHeight,
        uint16_t    blkWidth,
        uint16_t    blkHeight,
        uint16_t    extBlkIncrementX,
        uint16_t    extBlkIncrementY,
        uint16_t    intBlkIncrementX,
        uint16_t    intBlkIncrementY,
        uint32_t    roiOffset,
        uint16_t    blkOffset,
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride,
        uint8_t     dmaQueNo
)
{
    param->roiWidth             = roiWidth;
    param->roiHeight            = roiHeight;
    param->blkWidth             = blkWidth;
    param->blkHeight            = blkHeight;
    param->extBlkIncrementX     = extBlkIncrementX;
    param->extBlkIncrementY     = extBlkIncrementY;
    param->intBlkIncrementX     = intBlkIncrementX;
    param->intBlkIncrementY     = intBlkIncrementY;
    param->roiOffset            = roiOffset;
    param->blkOffset            = blkOffset;
    param->extMemPtr            = extMemPtr;
    param->extMemPtrStride      = extMemPtrStride ;
    param->interMemPtr          = interMemPtr;
    param->interMemPtrStride    = interMemPtrStride;
    param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t BLOCK_STATS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
  int32_t status = BAM_S_SUCCESS;
  int16_t imgFrameWidth, imgFrameHeight, imgOutWidth, imgOutHeight;
  int16_t blkWidthFinal= 0, blkHeightFinal= 0;
  int16_t blkOutWidth, blkOutHeight;

  BLOCK_STATS_TI_graphArgs *graphArgs = (BLOCK_STATS_TI_graphArgs*)args;
  BLOCK_STATS_TI_graphCreateParams *createParams = graphArgs->createParams;
  EDMA_UTILS_autoIncrement_initParam *dmaReadKernelArgs = &(graphArgs->dmaReadKernelArgs);
  EDMA_UTILS_autoIncrement_initParam *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);
  BAM_Block_Statistics_Args *blockStatKernelArgs = &(graphArgs->blockStatKernelArgs);

  imgOutWidth = createParams->imageWidth/createParams->statBlockWidth;
  imgOutHeight = createParams->imageHeight/createParams->statBlockHeight;

  imgFrameWidth = imgOutWidth*createParams->statBlockWidth;
  imgFrameHeight = imgOutHeight*createParams->statBlockHeight;

  blkWidthFinal = blockDimParams->blockWidth;
  while (((imgFrameWidth % blkWidthFinal) != 0) && (blkWidthFinal > blockDimParams->blockWidthStep)) {
      blkWidthFinal -= blockDimParams->blockWidthStep;
  }

  blkHeightFinal = blockDimParams->blockHeight;
  while (((imgFrameHeight % blkHeightFinal) != 0) && (blkHeightFinal > blockDimParams->blockHeightStep)) {
      blkHeightFinal -= blockDimParams->blockHeightStep;
  }

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if ((imgFrameWidth % blkWidthFinal) != 0) {
      PRINTF("imgFrameWidth = %d, must be a multiple of %d!!!",imgFrameWidth, blkWidthFinal);
      status = BAM_E_FAIL;
      goto Exit;
  }

  if ((imgFrameHeight % blkHeightFinal) != 0) {
      PRINTF("imgFrameHeight = %d, must be a multiple of %d!!!",imgFrameHeight, blkHeightFinal);
      status = BAM_E_FAIL;
      goto Exit;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  blkOutWidth = blkWidthFinal/createParams->statBlockWidth;
  blkOutHeight = blkHeightFinal/createParams->statBlockHeight;

  /*--------------------------------------------------------------------------*/
  /*Params Update for Source DMA node                                         */
  /*--------------------------------------------------------------------------*/
  dmaReadKernelArgs->numInTransfers  = 1;
  dmaReadKernelArgs->transferType    = EDMA_UTILS_TRANSFER_IN;

  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[BAM_SOURCE_NODE_PORT1],
          (uint16_t)imgFrameWidth,                 /* roiWidth */
          (uint16_t)imgFrameHeight,                /* roiHeight */
          (uint16_t)blkWidthFinal,                 /* blkWidth */
          (uint16_t)blkHeightFinal,                /* blkHeight */
          (uint16_t)blkWidthFinal,                 /* extBlkIncrementX */
          (uint16_t)blkHeightFinal,                /* extBlkIncrementY */
          0,                             /* intBlkIncrementX */
          0,                             /* intBlkIncrementY */
          0,                             /* roiOffset        */
          0,                             /* blkOffset        */
          NULL,                          /* extMemPtr        */
          (uint16_t)imgFrameWidth,                 /* extMemPtrStride  */
          NULL,                          /* interMemPtr      */
          (uint16_t)blkWidthFinal,                 /* interMemPtrStride */
          0);                            /* dmaQueNo          */

  /*--------------------------------------------------------------------------*/
  /*Params Update for Sink DMA node                                         */
  /*--------------------------------------------------------------------------*/
  dmaWriteKernelArgs->numOutTransfers  = 4;
  dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT1],
           (uint16_t)imgOutWidth,                   /* roiWidth */
           (uint16_t)imgOutHeight,                  /* roiHeight */
           (uint16_t)blkOutWidth,                   /* blkWidth */
           (uint16_t)blkOutHeight,                  /* blkHeight */
           (uint16_t)blkOutWidth,                   /* extBlkIncrementX */
           (uint16_t)blkOutHeight,                  /* extBlkIncrementY */
           0,                             /* intBlkIncrementX */
           0,                             /* intBlkIncrementY */
           0,                             /* roiOffset        */
           0,                             /* blkOffset        */
           NULL,                          /* extMemPtr        */
           (uint16_t)imgOutWidth,                   /* extMemPtrStride  */
           NULL,                          /* interMemPtr      */
           36U,                            /* interMemPtrStride */
           1U);                            /* dmaQueNo          */

  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT2],
           (uint16_t)imgOutWidth,                   /* roiWidth */
           (uint16_t)imgOutHeight,                  /* roiHeight */
           (uint16_t)blkOutWidth,                   /* blkWidth */
           (uint16_t)blkOutHeight,                  /* blkHeight */
           (uint16_t)blkOutWidth,                   /* extBlkIncrementX */
           (uint16_t)blkOutHeight,                  /* extBlkIncrementY */
           0,                             /* intBlkIncrementX */
           0,                             /* intBlkIncrementY */
           0,                             /* roiOffset        */
           0,                             /* blkOffset        */
           NULL,                          /* extMemPtr        */
           (uint16_t)imgOutWidth,                   /* extMemPtrStride  */
           NULL,                          /* interMemPtr      */
           36U,                            /* interMemPtrStride */
           1U);                            /* dmaQueNo          */

  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT3],
           (uint16_t)imgOutWidth*sizeof(uint16_t),     /* roiWidth */
           (uint16_t)imgOutHeight,                  /* roiHeight */
           (uint16_t)blkOutWidth*sizeof(uint16_t),     /* blkWidth */
           (uint16_t)blkOutHeight,                  /* blkHeight */
           (uint16_t)blkOutWidth*sizeof(uint16_t),     /* extBlkIncrementX */
           (uint16_t)blkOutHeight,                  /* extBlkIncrementY */
           0,                             /* intBlkIncrementX */
           0,                             /* intBlkIncrementY */
           0,                             /* roiOffset        */
           0,                             /* blkOffset        */
           NULL,                          /* extMemPtr        */
           (uint16_t)imgOutWidth*sizeof(uint16_t),     /* extMemPtrStride  */
           NULL,                          /* interMemPtr      */
           36U,                            /* interMemPtrStride */
           1U);                            /* dmaQueNo          */

  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT4],
           (uint16_t)imgOutWidth*sizeof(uint32_t),       /* roiWidth */
           (uint16_t)imgOutHeight,                  /* roiHeight */
           (uint16_t)blkOutWidth*sizeof(uint32_t),       /* blkWidth */
           (uint16_t)blkOutHeight,                  /* blkHeight */
           (uint16_t)blkOutWidth*sizeof(uint32_t),       /* extBlkIncrementX */
           (uint16_t)blkOutHeight,                  /* extBlkIncrementY */
           0,                             /* intBlkIncrementX */
           0,                             /* intBlkIncrementY */
           0,                             /* roiOffset        */
           0,                             /* blkOffset        */
           NULL,                          /* extMemPtr        */
           (uint16_t)imgOutWidth*sizeof(uint32_t),       /* extMemPtrStride  */
           NULL,                          /* interMemPtr      */
           (uint16_t)blkOutWidth*sizeof(uint32_t),       /* interMemPtrStride */
           1U);                            /* dmaQueNo          */

  /*--------------------------------------------------------------------------*/
  /*Params update for block statistics                                        */
  /*--------------------------------------------------------------------------*/
  blockStatKernelArgs->blockStride      = blkWidthFinal;
  blockStatKernelArgs->blockWidth       = blkWidthFinal;
  blockStatKernelArgs->blockHeight      = blkHeightFinal;
  blockStatKernelArgs->statBlockWidth   = createParams->statBlockWidth;
  blockStatKernelArgs->statBlockHeight  = createParams->statBlockHeight;

Exit:
  return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BLOCK_STATS_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{
  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority = BAM_COMPUTE_FIRST;

  status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;
}


int32_t BLOCK_STATS_TI_dmaControl(const BAM_GraphMem *graphMem,
                               const IVISION_BufDesc *inBufDesc,
                               const IVISION_BufDesc *outMinBufDesc,
                               const IVISION_BufDesc *outMaxBufDesc,
                               const IVISION_BufDesc *outMeanBufDesc,
                               const IVISION_BufDesc *outVarBufDesc)
{
  EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
  const IVISION_BufPlanes* ivisionInBufPlane = &inBufDesc->bufPlanes[0];
  const IVISION_BufPlanes* ivisionOutMinBufPlane = &outMinBufDesc->bufPlanes[0];
  const IVISION_BufPlanes* ivisionOutMaxBufPlane = &outMaxBufDesc->bufPlanes[0];
  const IVISION_BufPlanes* ivisionOutMeanBufPlane = &outMeanBufDesc->bufPlanes[0];
  const IVISION_BufPlanes* ivisionOutVarBufPlane = &outVarBufDesc->bufPlanes[0];
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  /* Initialize the control parameters for the SOURCE auto-increment DMA node */
  autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                             EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

  autoIncCtlArgs.updateParams[BAM_SOURCE_NODE_PORT1].extMemPtr = (uint8_t*)(*((uint8_t (*)[])ivisionInBufPlane->buf) +
    (ivisionInBufPlane->frameROI.topLeft.y * ivisionInBufPlane->width) +
    ivisionInBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SOURCE_NODE_PORT1].extMemPtrStride = ivisionInBufPlane->width;

  status = BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if (status!= BAM_S_SUCCESS) {
    goto Exit;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  /* Initialize the control parameters for the SINK auto-increment DMA node */
  autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                             EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT1].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionOutMinBufPlane->buf) +
    (ivisionOutMinBufPlane->frameROI.topLeft.y * ivisionOutMinBufPlane->width) +
    ivisionOutMinBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT1].extMemPtrStride = ivisionOutMinBufPlane->width;

  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT2].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionOutMaxBufPlane->buf) +
    (ivisionOutMaxBufPlane->frameROI.topLeft.y * ivisionOutMaxBufPlane->width) +
    ivisionOutMaxBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT2].extMemPtrStride = ivisionOutMaxBufPlane->width;

  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT3].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionOutMeanBufPlane->buf) +
    (ivisionOutMeanBufPlane->frameROI.topLeft.y * ivisionOutMeanBufPlane->width) +
    ivisionOutMeanBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT3].extMemPtrStride = ivisionOutMeanBufPlane->width;

  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT4].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionOutVarBufPlane->buf) +
    (ivisionOutVarBufPlane->frameROI.topLeft.y * ivisionOutVarBufPlane->width) +
    ivisionOutVarBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT4].extMemPtrStride = ivisionOutVarBufPlane->width;

  status = BAM_controlNode(graphHandle, SINK_NODE, &autoIncCtlArgs);

Exit:
  return status;
}
