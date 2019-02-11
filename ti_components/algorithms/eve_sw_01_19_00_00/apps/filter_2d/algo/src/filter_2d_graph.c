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
 *  @file      filter_2d_graph.c
 *
 *  @brief      This file defines the functions for graph for feature plane computation
 *              for Chroma component
 *  @version 0.0 (Jan 2014) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ifilter_2d_ti.h"

#include "filter_2d_alg_int.h"

#include "filter_2d_graph_int.h"

#include "edma_utils.h"
#include "bam_dma_autoincrement_node.h"

static int32_t FILTER_2D_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

static inline void fillNodeParams(BAM_NodeParams *nodeParams, uint8_t nodeIndex,
                                       BAM_KernelId    kernelId,   void   *kernelArgs)
{
    nodeParams->nodeIndex  = nodeIndex;
    nodeParams->kernelId   = kernelId;
    nodeParams->kernelArgs = kernelArgs;
}

static inline void fillEdgeParams(BAM_EdgeParams *edgeParams,
                                       uint8_t upStreamNodeId,   uint8_t upStreamNodePort,
                                       uint8_t downStreamNodeId, uint8_t downStreamNodePort)

{
    edgeParams->upStreamNode.id     = upStreamNodeId;
    edgeParams->upStreamNode.port   = upStreamNodePort;
    edgeParams->downStreamNode.id   = downStreamNodeId;
    edgeParams->downStreamNode.port = downStreamNodePort;
}


/* No of nodes: 5 (Source, Filter Y, Filter UV, Histogram Y , Contrast Stretching and Sink nodes) */
#define MAX_NO_OF_NODES     (6U)
#define MAX_NO_OF_EDGES     (7U)
#define SOURCE_NODE         (0)

#define HISTOGRAM_NODE        (1U)
#define CONTRAST_STRETCH_NODE (2U)
#define FILTER_Y_NODE         (3U)
#define FILTER_UV_NODE        (4U)
#define SINK_NODE             (5U)

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_HISTOGRAM,
    BAM_TI_KERNELID_CONTRAST_STRETCHING,
    BAM_TI_KERNELID_SEPARABLE_FILTER2D_Y,
    BAM_TI_KERNELID_SEPARABLE_FILTER2D_UV,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_FILTER_2D_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamFilter2DKernelHostDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
            "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_histogramKernel, &gBAM_TI_histogramHelperFunc,
            "ti_histogram_kernel", BAM_TI_KERNELID_HISTOGRAM },

    { &gBAM_TI_contrastStretchingKernel, &gBAM_TI_contrastStretchingHelperFunc,
            "ti_contrast_stretching_kernel", BAM_TI_KERNELID_CONTRAST_STRETCHING },

    { &gBAM_TI_yuv420Fir2dSeparableYKernel, &gBAM_TI_yuv420Fir2dSeparableYHelperFunc,
              "ti_sep_filter2D_y_kernel", BAM_TI_KERNELID_SEPARABLE_FILTER2D_Y},
    { &gBAM_TI_yuv420Fir2dSeparableUvKernel, &gBAM_TI_yuv420Fir2dSeparableUvHelperFunc,
            "ti_sep_filter2D_uv_kernel", BAM_TI_KERNELID_SEPARABLE_FILTER2D_UV },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
            "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamFilter2DKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
            "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_histogramKernel, &gBAM_TI_histogramExecFunc,
              "ti_histogram_kernel", BAM_TI_KERNELID_HISTOGRAM},
    { &gBAM_TI_contrastStretchingKernel, &gBAM_TI_contrastStretchingExecFunc,
            "ti_contrast_stretching_kernel", BAM_TI_KERNELID_CONTRAST_STRETCHING },

    { &gBAM_TI_yuv420Fir2dSeparableYKernel, &gBAM_TI_yuv420Fir2dSeparableYExecFunc,
              "ti_sep_filter2D_y_kernel", BAM_TI_KERNELID_SEPARABLE_FILTER2D_Y},
    { &gBAM_TI_yuv420Fir2dSeparableUvKernel, &gBAM_TI_yuv420Fir2dSeparableUvExecFunc,
            "ti_sep_filter2D_uv_kernel", BAM_TI_KERNELID_SEPARABLE_FILTER2D_UV },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
            "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};


BAM_KernelDBdef gFilter2D_BAM_TI_kernelDBdef =
{
    sizeof(bamFilter2DKernelExecFuncDB) / sizeof(bamFilter2DKernelExecFuncDB[0]),
    bamFilter2DKernelHostDB,
    bamFilter2DKernelExecFuncDB
};



int32_t FILTER_2D_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = FILTER_2D_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = FILTER_2D_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = FILTER_2D_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(FILTER_2D_TI_graphArgs) ;
  return 0;
}

int32_t FILTER_2D_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      FILTER_2D_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    FILTER_2D_TI_graphArgs * graphArgs = (FILTER_2D_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/


    uint8_t         sourceDmaNode, filterYNode, filterUVNode, histogramNode, contrastStretchingNode, sinkDmaNode;
    int8_t          nodelistParamIdxCurr, nodelistParamIdxPrev, edgelistParamIdx;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    /*
    Following is the graph connection for FILTER with contrast stretching. Similar graph is also used for
    the gray scale image format except that in the other case UV node is removed
    If contrast stretching is disabled then  HISTOGRAM_NODE and CONTRAST_STRETCH_NODE nodes
    are also removed from the graph. Rest of the graph remains same.

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {CONTRAST_STRETCH_NODE, BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT}},\

            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {HISTOGRAM_NODE, BAM_HISTOGRAM_INPUT_BLOCK_PORT}},\

            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT2},
                            {FILTER_UV_NODE, BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT}},\

            {{HISTOGRAM_NODE, BAM_HISTOGRAM_OUTPUT_HISTOGRAM8COPY_PORT},
                            {BAM_NULL_NODE, 0}},\

            {{CONTRAST_STRETCH_NODE, BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT},
                            {FILTER_Y_NODE, BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT}},\

            {{FILTER_Y_NODE, BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{FILTER_UV_NODE, BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT2}},\
            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };
    */
    BAM_NodeParams  NODELIST[MAX_NO_OF_NODES + 1U];
    BAM_EdgeParams  EDGELIST[MAX_NO_OF_EDGES + 1U];

    nodelistParamIdxCurr =  SOURCE_NODE;
    nodelistParamIdxPrev = (int8_t)-1;
    edgelistParamIdx     =  0;

    sourceDmaNode = (uint8_t)nodelistParamIdxCurr;
    fillNodeParams((NODELIST + sourceDmaNode), sourceDmaNode,
                    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
                   (void *)&(graphArgs->dmaReadKernelArgs));

    nodelistParamIdxCurr++;
    nodelistParamIdxPrev++;

    if ( createParams->ifilterCreateParams->enableContrastStretching )
    {
      histogramNode = (uint8_t)nodelistParamIdxCurr;
      fillNodeParams((NODELIST + histogramNode), histogramNode,
                      BAM_TI_KERNELID_HISTOGRAM,
                     (void *)&(graphArgs->histogramArgs));

      nodelistParamIdxCurr++;
      nodelistParamIdxPrev++;


      contrastStretchingNode = (uint8_t)nodelistParamIdxCurr;
      fillNodeParams((NODELIST + contrastStretchingNode), contrastStretchingNode,
                      BAM_TI_KERNELID_CONTRAST_STRETCHING,
                     (void *)&(graphArgs->contrastStretchingArgs));

      nodelistParamIdxCurr++;
      nodelistParamIdxPrev++;

    }

    filterYNode = (uint8_t)nodelistParamIdxCurr;
    fillNodeParams((NODELIST + filterYNode), filterYNode,
                    BAM_TI_KERNELID_SEPARABLE_FILTER2D_Y,
                   (void *)&(graphArgs->filter2dYArgs));

    nodelistParamIdxCurr++;
    nodelistParamIdxPrev++;


    if ( createParams->ifilterCreateParams->imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
    {
      filterUVNode = (uint8_t)nodelistParamIdxCurr;
      fillNodeParams((NODELIST + filterUVNode), filterUVNode,
                      BAM_TI_KERNELID_SEPARABLE_FILTER2D_UV,
                     (void *)&(graphArgs->filter2dUvArgs));

      nodelistParamIdxCurr++;
      nodelistParamIdxPrev++;
    }

    sinkDmaNode = (uint8_t)nodelistParamIdxCurr;
    fillNodeParams((NODELIST + sinkDmaNode), sinkDmaNode,
                    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,
                   (void *)&(graphArgs->dmaWriteKernelArgs));

    nodelistParamIdxCurr++;
    nodelistParamIdxPrev++;

    fillNodeParams((NODELIST + nodelistParamIdxCurr), (uint8_t)BAM_END_NODE_MARKER, 0, NULL);

    nodelistParamIdxCurr++;
    nodelistParamIdxPrev++;


    if ( createParams->ifilterCreateParams->enableContrastStretching )
    {
      fillEdgeParams((EDGELIST + edgelistParamIdx),
                          sourceDmaNode, BAM_SOURCE_NODE_PORT1,
                          contrastStretchingNode, BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT);
      edgelistParamIdx++;

      fillEdgeParams((EDGELIST + edgelistParamIdx),
                            sourceDmaNode, BAM_SOURCE_NODE_PORT1,
                            histogramNode,     BAM_HISTOGRAM_INPUT_BLOCK_PORT);
      edgelistParamIdx++;

    }
    else
    {
      fillEdgeParams((EDGELIST + edgelistParamIdx),
                              sourceDmaNode, BAM_SOURCE_NODE_PORT1,
                              filterYNode, BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT);
      edgelistParamIdx++;

    }

    if ( createParams->ifilterCreateParams->imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
    {
      fillEdgeParams((EDGELIST + edgelistParamIdx),
                    sourceDmaNode, BAM_SOURCE_NODE_PORT2,
                    filterUVNode,     BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT);
      edgelistParamIdx++;
    }

    if ( createParams->ifilterCreateParams->enableContrastStretching )
    {
      fillEdgeParams((EDGELIST + edgelistParamIdx),
                    histogramNode, BAM_HISTOGRAM_OUTPUT_DUMMY_PORT,
                    (uint8_t)BAM_NULL_NODE, 0);
      edgelistParamIdx++;

      fillEdgeParams((EDGELIST + edgelistParamIdx),
                    contrastStretchingNode, BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT,
                    filterYNode, BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT);
      edgelistParamIdx++;
    }

    fillEdgeParams((EDGELIST + edgelistParamIdx),
                    filterYNode, BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT,
                    sinkDmaNode, BAM_SINK_NODE_PORT1);
    edgelistParamIdx++;

    if ( createParams->ifilterCreateParams->imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
    {
      fillEdgeParams((EDGELIST + edgelistParamIdx),
                      filterUVNode, BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT,
                      sinkDmaNode, BAM_SINK_NODE_PORT2);
      edgelistParamIdx++;

    }

    fillEdgeParams((EDGELIST + edgelistParamIdx),
                    (uint8_t)BAM_END_NODE_MARKER, 0,
                    (uint8_t)BAM_END_NODE_MARKER, 0);
    edgelistParamIdx++;

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;
    graphCreateParams.blockDimParams.blockWidth  = 0;
    graphCreateParams.blockDimParams.blockHeight = 0;

    status= BAM_initKernelDB(&gFilter2D_BAM_TI_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gFilter2D_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = FILTER_2D_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = FILTER_2D_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = FILTER_2D_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &FILTER_2D_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /* Initialize the structure blockDimParams that lists the processing block
    * dimensions as well as the step increment sizes used during the block
    * dimension optimization if enabled
    */
    graphCreateParams.blockDimParams.blockWidth           = FILTER_2D_TI_BLOCK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight          = FILTER_2D_TI_BLOCK_HEIGHT;
    graphCreateParams.blockDimParams.blockWidthStep       = 16U;
    graphCreateParams.blockDimParams.blockHeightStep      = 1U;

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
      PRINTF("Filter 2D : Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("Filter 2D  : Graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
        graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("Filter 2D  : Graph construction failed!!!");
    }
    else
    {
      /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}

/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static inline void assignDMAautoIncrementParams(
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
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
  param->blkOffset            = 0;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t FILTER_2D_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */

  uint16_t blkWidthFinal  = 0;
  uint16_t blkHeightFinal = 0;
  int32_t status = BAM_S_SUCCESS;
  uint32_t roundBits;
  uint32_t sumW, sumH;
  uint32_t sumWH;
  uint8_t coefIdx=0;
  uint8_t filterCoeffWidth;
  uint8_t filterCoeffHeight;
  uint8_t (*filterCoeff)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE];


  FILTER_2D_TI_graphArgs              *graphArgs          = (FILTER_2D_TI_graphArgs*)args;
  EDMA_UTILS_autoIncrement_initParam  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  EDMA_UTILS_autoIncrement_initParam  *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);
  BAM_Yuv420_fir2dseparable_Args      *filter2dYArgs      = &(graphArgs->filter2dYArgs);
  BAM_Yuv420_fir2dseparable_Args      *filter2dUvArgs     = &(graphArgs->filter2dUvArgs);

  BAM_Histogram_Args                  *histogramArgs      = &(graphArgs->histogramArgs);
  BAM_ContrastStretching_Args         *contrastStretchingArgs = &(graphArgs->contrastStretchingArgs);
  FILTER_2D_TI_graphCreateParams      *createParams       = graphArgs->createParams;

  blkWidthFinal  = blockDimParams->blockWidth;
  blkHeightFinal = blockDimParams->blockHeight;

  filterCoeffWidth  = createParams->ifilterCreateParams->filterCoefWidth;
  filterCoeffHeight = createParams->ifilterCreateParams->filterCoefHeight;
  filterCoeff = (uint8_t (*)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE])(void *)createParams->ifilterCreateParams->filterCoef;

  dmaReadKernelArgs->numInTransfers   = 1;

  if ( createParams->ifilterCreateParams->imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
  {
    dmaReadKernelArgs->numInTransfers   = 2;
  }
  dmaReadKernelArgs->transferType     = EDMA_UTILS_TRANSFER_IN;

  /* Update dma node properties before executing the filter applet*/
  /* First transfer is for Y component of image buffer */
  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    blkWidthFinal  + ((uint16_t)filterCoeffWidth  - (uint16_t)1U),/*blkWidth */
    blkHeightFinal + ((uint16_t)filterCoeffHeight - (uint16_t)1U),/*blkHeight*/
    blkWidthFinal,/* extBlkIncrementX */
    blkHeightFinal,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    blkWidthFinal  + ((uint16_t)filterCoeffWidth  - (uint16_t)1U),/* interMemPtrStride */
    0 /* dmaQueNo */
    );

  /* Second transfer is for UV component of image buffer */
  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[1],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    blkWidthFinal  + (((uint16_t)2 * (uint16_t)filterCoeffWidth)  - (uint16_t)1),/*blkWidth */
    (blkHeightFinal / (uint16_t)2) + (((uint16_t)2 * (uint16_t)(filterCoeffHeight)) - (uint16_t)1),/*blkHeight*/
    blkWidthFinal,/* extBlkIncrementX */
    (blkHeightFinal / 2U),/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    blkWidthFinal  + (((uint16_t)2 * (filterCoeffWidth))  - (uint16_t)1),/* interMemPtrStride */
    0 /* dmaQueNo */
    );

  dmaWriteKernelArgs->numOutTransfers  = 1U;

  if ( createParams->ifilterCreateParams->imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
  {
    dmaWriteKernelArgs->numOutTransfers  = 2U;
  }

  dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

  /* First transfer is for outputting Y component of image buffer */
  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    blkWidthFinal,/*blkWidth */
    blkHeightFinal,/*blkHeight*/
    blkWidthFinal,/* extBlkIncrementX */
    blkHeightFinal,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    blkWidthFinal,/* interMemPtrStride */
    1U /* dmaQueNo */
    );

  /* Second transfer is for outputting UV component of image buffer */
  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[1],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    blkWidthFinal,/*blkWidth */
    blkHeightFinal/2U,/*blkHeight*/
    blkWidthFinal,/* extBlkIncrementX */
    blkHeightFinal/2U,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    blkWidthFinal,/* interMemPtrStride */
    1U /* dmaQueNo */
    );


  sumW = 0;
  sumH = 0;
  roundBits = 0;
  if ( createParams->ifilterCreateParams->separableFilter == 1U )
  {
    for ( coefIdx = 0 ; coefIdx < filterCoeffWidth; coefIdx++)
    {
      sumW += (*filterCoeff)[coefIdx];
    }

    for ( coefIdx = filterCoeffWidth ;
          coefIdx < (filterCoeffWidth +
          filterCoeffHeight); coefIdx++)
    {
      sumH += (*filterCoeff)[coefIdx];
    }
    sumWH = sumW * sumH;
    /* This is under the assumption that sumWH is power of 2 */
    roundBits = 0;
    if ( sumWH !=0 )
    {
      while ( sumWH != 1U )
      {
        sumWH = sumWH >> 1U;
        roundBits++;
      }
    }
  }

  filter2dYArgs->blockWidth     = blkWidthFinal;
  filter2dYArgs->blockHeight    = blkHeightFinal;
  filter2dYArgs->pitch          = blkWidthFinal + ((uint16_t)filterCoeffWidth - (uint16_t)1U);
  filter2dYArgs->coefWidth      = filterCoeffWidth;
  filter2dYArgs->coefHeight     = filterCoeffHeight;
  filter2dYArgs->coefPtr        = filterCoeff;
  filter2dYArgs->rndBits        = roundBits;

  filter2dUvArgs->blockWidth     = blkWidthFinal;
  filter2dUvArgs->blockHeight    = blkHeightFinal;
  filter2dUvArgs->pitch          = blkWidthFinal + (((uint16_t)2 * (uint16_t)filterCoeffWidth) - (uint16_t)1);
  filter2dUvArgs->coefWidth      = filterCoeffWidth;
  filter2dUvArgs->coefHeight     = filterCoeffHeight;
  filter2dUvArgs->coefPtr        = filterCoeff;
  filter2dUvArgs->rndBits        = roundBits;

  if ( createParams->ifilterCreateParams->enableContrastStretching)
  {
    uint32_t scaleFactorQ16;
    uint16_t minVal;
    uint16_t maxVal;

    minVal = createParams->ifilterCreateParams->minVal;
    maxVal = createParams->ifilterCreateParams->maxVal;
    if ( (maxVal - minVal) != 0 )
    {
      scaleFactorQ16 = (( (uint32_t)1U << 16U) / (( (uint32_t)maxVal - (uint32_t)minVal)));
    }
    else
    {
      scaleFactorQ16 = (uint32_t)((uint32_t)1U << 16U);
    }

    histogramArgs->blkWidth   = blkWidthFinal;
    histogramArgs->blkHeight  = blkHeightFinal;
    histogramArgs->inPitch    = blkWidthFinal + ((uint16_t)filterCoeffWidth  - (uint16_t)1U);

    contrastStretchingArgs->blkWidth  = blkWidthFinal +
                ((uint16_t)filterCoeffWidth  - (uint16_t)1U);
    contrastStretchingArgs->blkHeight =  blkHeightFinal +
                ((uint16_t)filterCoeffHeight - (uint16_t)1U);
    contrastStretchingArgs->inPitch = blkWidthFinal +
                ((uint16_t)filterCoeffWidth  - (uint16_t)1U);
    contrastStretchingArgs->outPitch = blkWidthFinal +
                ((uint16_t)filterCoeffWidth  - (uint16_t)1U);
    contrastStretchingArgs->minVal          = minVal;
    contrastStretchingArgs->scaleFactorQ16  = scaleFactorQ16;
  }

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t FILTER_2D_TI_execute(
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

int32_t FILTER_2D_TI_getEffectiveDimensionsUsed(
                                        uint16_t imageWidth,
                                        uint16_t imageHeight,
                                        FILTER_2D_EffectiveDims * effDims)
{
  effDims->effImageWidth = ((imageWidth + (FILTER_2D_TI_BLOCK_WIDTH - 1U))/
                                FILTER_2D_TI_BLOCK_WIDTH) *
                                  FILTER_2D_TI_BLOCK_WIDTH;

  effDims->effImageHeight = ((imageHeight + (FILTER_2D_TI_BLOCK_HEIGHT - 1U))/
                                FILTER_2D_TI_BLOCK_HEIGHT) *
                                  FILTER_2D_TI_BLOCK_HEIGHT;

  effDims->activeHistImgWidth = (imageWidth / FILTER_2D_TI_BLOCK_WIDTH) *
                                  FILTER_2D_TI_BLOCK_WIDTH;

  effDims->activeHistImgHeight = (imageHeight / FILTER_2D_TI_BLOCK_HEIGHT) *
                                  FILTER_2D_TI_BLOCK_HEIGHT;
  return BAM_S_SUCCESS;
}


uint32_t * FILTER_2D_TI_getHist8CopyBuf(const  BAM_GraphMem * graphMem)
{
  int32_t status = BAM_S_SUCCESS;
  BAM_Histogram_CtrlArgs controlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  uint32_t * hist8CopyBufPtr = NULL;

  controlArgs.cmdId = BAM_HISTOGRAM_CTRL_CMDID_GET_HISTOGRAM8COPY_WBUF;

  status = BAM_controlNode( graphHandle, 1U, &controlArgs);

  if ( status != BAM_S_SUCCESS )
  {
    hist8CopyBufPtr = NULL;
  }
  else
  {
    hist8CopyBufPtr = (uint32_t *) controlArgs.ctrlArgs;
  }

  return hist8CopyBufPtr;
}

int32_t FILTER_2D_TI_setHistogramImageDim(const  BAM_GraphMem * graphMem,
                                                  uint16_t imageWidth,
                                                  uint16_t imageHeight)
{
  int32_t status = BAM_S_SUCCESS;
  BAM_Histogram_CtrlArgs controlArgs;
  BAM_Histogram_ImageDim_CtrlArgs imageDims;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  imageDims.imageWidth  = imageWidth;
  imageDims.imageHeight = imageHeight;

  controlArgs.cmdId = BAM_HISTOGRAM_CTRL_CMDID_SET_IMAGE_HEIGHT;
  controlArgs.ctrlArgs = (void*) &imageDims;

  status = BAM_controlNode( graphHandle, 1U, &controlArgs);

  return status;
}

int32_t FILTER_2D_TI_setContrastStretchingArgs(const  BAM_GraphMem * graphMem,
                                                    uint32_t minVal,
                                                    uint32_t scaleFactorQ16)
{
  int32_t status = BAM_S_SUCCESS;
  BAM_ContrastStretching_CtrlArgs ctrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  ctrlArgs.minVal         = minVal;
  ctrlArgs.scaleFactorQ16 = scaleFactorQ16;

  status = BAM_controlNode( graphHandle, 2U , &ctrlArgs);

  return status;
}



int32_t FILTER_2D_TI_dmaControl(const BAM_GraphMem *graphMem,
                                          uint8_t filterCoefWidth,
                                          uint8_t filterCoefHeight,
                                          uint8_t sinkNodeId,
                                          const IVISION_BufDesc *inBufDesc,
                                          const IVISION_BufDesc *outBufDesc,
                                          uint16_t * effectiveImageWidth,
                                          uint16_t * effectiveImageHeight
                                          )

{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    FILTER_2D_EffectiveDims effDims;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;


    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    FILTER_2D_TI_getEffectiveDimensionsUsed(inBufDesc->bufPlanes[0].frameROI.width,
                        inBufDesc->bufPlanes[0].frameROI.height,
                        &effDims);


    /* We do some adjustments to the coordinates of the upper left corner such that the DMA reads the ROI and its borders required for filtering */
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
      rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    autoIncCtlArgs.updateParams[0].extMemPtr= (uint8_t*)inBufDesc->bufPlanes[0].buf +
                                      ((inBufDesc->bufPlanes[0].frameROI.topLeft.y) * inBufDesc->bufPlanes[0].width) +
                                      (inBufDesc->bufPlanes[0].frameROI.topLeft.x);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    autoIncCtlArgs.updateParams[0].extMemPtrStride = inBufDesc->bufPlanes[0].width;
    autoIncCtlArgs.updateParams[0].roiWidth= effDims.effImageWidth + (filterCoefWidth  - 1U);
    autoIncCtlArgs.updateParams[0].roiHeight= effDims.effImageHeight + (filterCoefHeight  - 1U);

      /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
      /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
      /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
      rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    autoIncCtlArgs.updateParams[1].extMemPtr= (uint8_t*)inBufDesc->bufPlanes[1].buf +
                            ((inBufDesc->bufPlanes[1].frameROI.topLeft.y) * inBufDesc->bufPlanes[1].width) +
                            (inBufDesc->bufPlanes[1].frameROI.topLeft.x);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    autoIncCtlArgs.updateParams[1].extMemPtrStride = inBufDesc->bufPlanes[1].width;
    autoIncCtlArgs.updateParams[1].roiWidth= effDims.effImageWidth + ( (2U*filterCoefWidth)  - 1U);
    autoIncCtlArgs.updateParams[1].roiHeight= (effDims.effImageHeight  / 2U) + ( (2U*filterCoefHeight)  - 1U);

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
      rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    autoIncCtlArgs.updateParams[0].extMemPtr= (uint8_t*)outBufDesc->bufPlanes[0].buf +
                                (outBufDesc->bufPlanes[0].frameROI.topLeft.y * outBufDesc->bufPlanes[0].width) +
                                  outBufDesc->bufPlanes[0].frameROI.topLeft.x;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    autoIncCtlArgs.updateParams[0].extMemPtrStride = outBufDesc->bufPlanes[0].width;
    autoIncCtlArgs.updateParams[0].roiWidth= effDims.effImageWidth;
    autoIncCtlArgs.updateParams[0].roiHeight= effDims.effImageHeight;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
      rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */

    autoIncCtlArgs.updateParams[1].extMemPtr= (uint8_t*)outBufDesc->bufPlanes[1].buf +
                (outBufDesc->bufPlanes[1].frameROI.topLeft.y * outBufDesc->bufPlanes[1].width) +
                outBufDesc->bufPlanes[1].frameROI.topLeft.x;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    autoIncCtlArgs.updateParams[1].extMemPtrStride = outBufDesc->bufPlanes[1].width;
    autoIncCtlArgs.updateParams[1].roiWidth= effDims.effImageWidth;
    autoIncCtlArgs.updateParams[1].roiHeight= effDims.effImageHeight/2U;

    status= BAM_controlNode(graphHandle, sinkNodeId, &autoIncCtlArgs);

    *effectiveImageWidth  = effDims.effImageWidth;
    *effectiveImageHeight = effDims.effImageHeight;

 Exit:
    return status;
}

