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
 *  @file:      median_filter_graph.c
 *
 *  @brief:     This file defines the functions for median filtering
 *
 *  @version:   0.2 (July 2014) : Base version.
 */
/*============================================================================*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* #pragma RESET_MISRA ("required") */

#include "median_filter_graph_int.h"
#include "edma_utils.h"

static int32_t MEDIAN_FILTER_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

/* Definitions of the node identifier symbols  */
#define SOURCE_NODE                (0U)
#define MEDIAN_FILTER_NODE         (1U)
#define SINK_NODE                  (2U)

typedef enum
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_MEDIAN_FILTER,
    BAM_TI_KERNELID_3x3_MEDIAN,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_MEDIAN_FILTER_TI_KernelID;

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamMedianFilterKernelHostDB[] =
{
  { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  { &gBAM_TI_medianFilterKernel, &gBAM_TI_medianFilterHelperFunc, "ti_image_median_filter", BAM_TI_KERNELID_MEDIAN_FILTER},
  { &gBAM_TI_median3x3Kernel, &gBAM_TI_median3x3HelperFunc, "ti_image_3x3_median_filter", BAM_TI_KERNELID_3x3_MEDIAN},
  { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT}
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamMedianFilterKernelExecFuncDB[] =
{
  { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  { &gBAM_TI_medianFilterKernel, &gBAM_TI_medianFilterExecFunc, "ti_image_median_filter", BAM_TI_KERNELID_MEDIAN_FILTER},
  { &gBAM_TI_median3x3Kernel, &gBAM_TI_median3x3ExecFunc, "ti_image_3x3_median_filter", BAM_TI_KERNELID_3x3_MEDIAN},
  { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT}
};

BAM_KernelDBdef gMedianFilter_TI_BAM_kernelDBdef =
{
  sizeof(bamMedianFilterKernelExecFuncDB) / sizeof(bamMedianFilterKernelExecFuncDB[0]),
  bamMedianFilterKernelHostDB,
  bamMedianFilterKernelExecFuncDB
};


int32_t MEDIAN_FILTER_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = MEDIAN_FILTER_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = MEDIAN_FILTER_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = MEDIAN_FILTER_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize     = sizeof(MEDIAN_FILTER_TI_graphArgs);
  return 0;
}


int32_t MEDIAN_FILTER_TI_graphCreate(const BAM_GraphMem * graphMem,
            MEDIAN_FILTER_TI_graphCreateParams * createParams)
{
  BAM_CreateGraphParams graphCreateParams;
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  MEDIAN_FILTER_TI_graphArgs * graphArgs = (MEDIAN_FILTER_TI_graphArgs *)graphMem->graphArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  /*------------------------------------------------------------------------------*/
  /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
  /*------------------------------------------------------------------------------*/

  /* Definitions of the node paramaters */
  BAM_NodeParams NODELIST[]={\
          {SOURCE_NODE,           BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,  NULL},\
          {MEDIAN_FILTER_NODE,    BAM_TI_KERNELID_MEDIAN_FILTER,          NULL},\
          {SINK_NODE,             BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT, NULL},\
          {BAM_END_NODE_MARKER,   0,                                      NULL},\
  };

  /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
  NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
  NODELIST[1].kernelArgs = (void *)(&graphArgs->medianFilterKernelArgs);
  NODELIST[2].kernelArgs = (void *)(&graphArgs->dmaWriteKernelArgs);

  /* Definitions of the edge paramaters */
  BAM_EdgeParams EDGELIST[]= {\
          {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},                     {MEDIAN_FILTER_NODE, BAM_MEDIAN_FILTER_INPUT_PORT}},\
          {{MEDIAN_FILTER_NODE, BAM_MEDIAN_FILTER_OUTPUT_PORT},      {SINK_NODE, BAM_SINK_NODE_PORT1}},\
          {{BAM_END_NODE_MARKER, 0},                                 {BAM_END_NODE_MARKER, 0}},\
  };

  if((createParams->blockWidth == 3) && (createParams->blockHeight == 3) &&
     (createParams->stepSizeHorz == 1) && (createParams->stepSizeVert == 1)) {

    NODELIST[1].kernelId   = BAM_TI_KERNELID_3x3_MEDIAN;
    NODELIST[1].kernelArgs = (void *)(&graphArgs->median3x3KernelArgs);

    EDGELIST[0].downStreamNode.port = BAM_MEDIAN_3x3_INPUT_PORT;
    EDGELIST[1].upStreamNode.port   = BAM_MEDIAN_3x3_OUTPUT_PORT;
  }

  /* Initialize the structure blockDimParams that lists the processing block
  * dimensions as well as the step increment sizes used during the block
  * dimension optimization if enabled
  */
  graphCreateParams.blockDimParams.blockWidth  = MEDIAN_FILTER_MAX_BLK_WIDTH;
  graphCreateParams.blockDimParams.blockHeight = MEDIAN_FILTER_MAX_BLK_HEIGHT;

  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  status = BAM_initKernelDB(&gMedianFilter_TI_BAM_kernelDBdef);
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
  graphCreateParams.kernelDB             = &gMedianFilter_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = MEDIAN_FILTER_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = MEDIAN_FILTER_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = MEDIAN_FILTER_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

  graphArgs->createParams = createParams;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &MEDIAN_FILTER_TI_initKernelsArgs;
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
static int32_t MEDIAN_FILTER_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;
  uint16_t imgFrameWidth, imgFrameHeight;
  uint16_t imgOutWidth, imgOutHeight;
  uint16_t outBlkWidth, outBlkHeight;
  uint16_t blkWidth, blkHeight, extBlkIncX, extBlkIncY;

  MEDIAN_FILTER_TI_graphArgs *graphArgs = (MEDIAN_FILTER_TI_graphArgs*)args;
  MEDIAN_FILTER_TI_graphCreateParams *createParams = graphArgs->createParams;
  EDMA_UTILS_autoIncrement_initParam *dmaReadKernelArgs = &(graphArgs->dmaReadKernelArgs);
  EDMA_UTILS_autoIncrement_initParam *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);
  BAM_Median_Filter_Args *medianFilterKernelArgs = &(graphArgs->medianFilterKernelArgs);
  BAM_Median3x3_Args *median3x3KernelArgs = &(graphArgs->median3x3KernelArgs);


  if((createParams->blockWidth == 3) && (createParams->blockHeight == 3) &&
     (createParams->stepSizeHorz == 1) && (createParams->stepSizeVert == 1)) {

    blkWidth  = MIN(createParams->imageWidth, MEDIAN_FILTER_MAX_BLK_WIDTH);
    blkHeight = MIN(createParams->imageHeight, MEDIAN_FILTER_MAX_BLK_HEIGHT);

    imgFrameWidth  = ALIGNED_DIM(createParams->imageWidth, (uint16_t)blkWidth, (uint16_t)2);
    imgFrameHeight = ALIGNED_DIM(createParams->imageHeight, (uint16_t)blkHeight, (uint16_t)2);

    outBlkWidth  = blkWidth - 2U;
    outBlkHeight = blkHeight - 2U;

    imgOutWidth  = imgFrameWidth - 2U;
    imgOutHeight = imgFrameHeight - 2U;

    extBlkIncX = outBlkWidth;
    extBlkIncY = outBlkHeight;
  }
  else {

    imgOutWidth  = (uint16_t)1 + ((createParams->imageWidth-(uint16_t)createParams->blockWidth)/(createParams->stepSizeHorz));
    imgOutHeight = (uint16_t)1 + ((createParams->imageHeight-(uint16_t)createParams->blockHeight)/(createParams->stepSizeVert));

    imgFrameWidth  = createParams->blockWidth + ((imgOutWidth-1U)*(createParams->stepSizeHorz));
    imgFrameHeight = createParams->blockHeight + ((imgOutHeight-1U)*(createParams->stepSizeVert));

    blkWidth  = createParams->blockWidth;
    blkHeight = createParams->blockHeight;

    outBlkWidth  = 1U;
    outBlkHeight = 1U;

    extBlkIncX = createParams->stepSizeHorz;
    extBlkIncY = createParams->stepSizeVert;
  }

  /*--------------------------------------------------------------------------*/
  /*Params Update for Source DMA node                                         */
  /*--------------------------------------------------------------------------*/
  dmaReadKernelArgs->numInTransfers  = 1;
  dmaReadKernelArgs->transferType    = EDMA_UTILS_TRANSFER_IN;

  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[BAM_SOURCE_NODE_PORT1],
          (uint16_t)imgFrameWidth,                 /* roiWidth */
          (uint16_t)imgFrameHeight,                /* roiHeight */
          (uint16_t)blkWidth,                      /* blkWidth */
          (uint16_t)blkHeight,                     /* blkHeight */
          (uint16_t)extBlkIncX,                    /* extBlkIncrementX */
          (uint16_t)extBlkIncY,                    /* extBlkIncrementY */
          0,                             /* intBlkIncrementX */
          0,                             /* intBlkIncrementY */
          0,                             /* roiOffset        */
          0,                             /* blkOffset        */
          NULL,                          /* extMemPtr        */
          (uint16_t)imgFrameWidth,                 /* extMemPtrStride  */
          NULL,                          /* interMemPtr      */
          (uint16_t)blkWidth,                      /* interMemPtrStride */
          0);                            /* dmaQueNo          */

  /*--------------------------------------------------------------------------*/
  /*Params Update for Sink DMA node                                         */
  /*--------------------------------------------------------------------------*/
  dmaWriteKernelArgs->numOutTransfers  = 1;
  dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT1],
           (uint16_t)imgOutWidth,                   /* roiWidth */
           (uint16_t)imgOutHeight,                  /* roiHeight */
           (uint16_t)outBlkWidth,                   /* blkWidth */
           (uint16_t)outBlkHeight,                  /* blkHeight */
           (uint16_t)outBlkWidth,                   /* extBlkIncrementX */
           (uint16_t)outBlkHeight,                  /* extBlkIncrementY */
           0,                             /* intBlkIncrementX */
           0,                             /* intBlkIncrementY */
           0,                             /* roiOffset        */
           0,                             /* blkOffset        */
           NULL,                          /* extMemPtr        */
           (uint16_t)imgOutWidth,                   /* extMemPtrStride  */
           NULL,                          /* interMemPtr      */
           (uint16_t)outBlkWidth,                   /* interMemPtrStride */
           1U);                            /* dmaQueNo          */

  /*--------------------------------------------------------------------------*/
  /* Params update for median filter                                          */
  /*--------------------------------------------------------------------------*/
  if((createParams->blockWidth == 3) && (createParams->blockHeight == 3) &&
     (createParams->stepSizeHorz == 1) && (createParams->stepSizeVert == 1)) {

    median3x3KernelArgs->blockWidth = blkWidth;
    median3x3KernelArgs->blockHeight = blkHeight;
  }
  else {

    /* Currently processing only one block at a time */
    medianFilterKernelArgs->blockWidth       = createParams->blockWidth;
    medianFilterKernelArgs->blockHeight      = createParams->blockHeight;
    medianFilterKernelArgs->kernelWidth      = createParams->blockWidth;
    medianFilterKernelArgs->kernelHeight     = createParams->blockHeight;
    medianFilterKernelArgs->stepSizeHorz     = createParams->stepSizeHorz;
    medianFilterKernelArgs->stepSizeVert     = createParams->stepSizeVert;
  }

  return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t MEDIAN_FILTER_TI_execute(
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


int32_t MEDIAN_FILTER_TI_dmaControl(const BAM_GraphMem *graphMem,
                               const IVISION_BufDesc *inBufDesc,
                               const IVISION_BufDesc *outBufDesc)
{
  EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
  const IVISION_BufPlanes * ivisionInBufPlane = &inBufDesc->bufPlanes[0];
  const IVISION_BufPlanes * ivisionOutBufPlane = &outBufDesc->bufPlanes[0];
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  /* Initialize the control parameters for the SOURCE auto-increment DMA node */
  autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                             EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

  autoIncCtlArgs.updateParams[BAM_SOURCE_NODE_PORT1].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionInBufPlane->buf) +
    (ivisionInBufPlane->frameROI.topLeft.y * ivisionInBufPlane->width) +
    ivisionInBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SOURCE_NODE_PORT1].extMemPtrStride = ivisionInBufPlane->width;

  status = BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

  if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /* Initialize the control parameters for the SINK auto-increment DMA node */
  autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                             EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT1].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionOutBufPlane->buf) +
    (ivisionOutBufPlane->frameROI.topLeft.y * ivisionOutBufPlane->width) +
    ivisionOutBufPlane->frameROI.topLeft.x);
  autoIncCtlArgs.updateParams[BAM_SINK_NODE_PORT1].extMemPtrStride = ivisionOutBufPlane->width;

  status = BAM_controlNode(graphHandle, SINK_NODE, &autoIncCtlArgs);

Exit:
  return status;
}
