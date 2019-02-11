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
 *  @file      edge_detector_sobel_graph.c
 *
 *  @brief     This file defines the functions for graph forEdge Detection applet
 *
 *  @version 0.0 (Dec 2014) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "iedge_detector_ti.h"

#include "edma_utils.h"

#include "edge_detector_sobel_graph_int.h"

#include "edge_detector_alg_int.h"
#include "bam_sobel_xy.h"

static int32_t EDGE_DETECTOR_SOBEL_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE                    (0)
#define SOBEL_XY_NODE                  (1U)
#define SOBEL_MAG_THRESHOLDING_NODE    (2U)
#define SINK_NODE                      (3U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_SOBELXY,
    BAM_TI_KERNELID_SOBELMAG_THRESHOLDING,
    BAM_TI_KERNELID_SOBELMAG_THRESHOLDING_BIN_PACK,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_EDGE_DETECTOR_SOBEL_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamEdgeDetectorKernelHostDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_sobelXyKernel, &gBAM_TI_sobelXyHelperFunc,
            "ti_sobelXy", BAM_TI_KERNELID_SOBELXY },

    { &BAM_SobelXyMagThresholdingKernel, &gBAM_TI_sobelXyMagThresholdingHelperFunc,
            "ti_sobel_mag_thresholding", BAM_TI_KERNELID_SOBELMAG_THRESHOLDING },

    { &BAM_SobelXyMagThresholdingBinPackKernel, &gBAM_TI_sobelXyMagThresholdingBinPackHelperFunc,
            "ti_sobel_mag_thresholding_binPack", BAM_TI_KERNELID_SOBELMAG_THRESHOLDING_BIN_PACK },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamEdgeDetectorKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_sobelXyKernel, &gBAM_TI_sobelXyExecFunc,
              "ti_sobelXy", BAM_TI_KERNELID_SOBELXY},

    { &BAM_SobelXyMagThresholdingKernel, &BAM_SobelXyMagThresholdingExecFunc,
            "ti_sobel_mag_thresholding", BAM_TI_KERNELID_SOBELMAG_THRESHOLDING },

    { &BAM_SobelXyMagThresholdingBinPackKernel, &BAM_SobelXyMagThresholdingBinPackExecFunc,
            "ti_sobel_mag_thresholding_binPack", BAM_TI_KERNELID_SOBELMAG_THRESHOLDING_BIN_PACK },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};


BAM_KernelDBdef gEdgeDetector_BAM_TI_kernelDBdef =
{
    sizeof(bamEdgeDetectorKernelExecFuncDB) / sizeof(bamEdgeDetectorKernelExecFuncDB[0]),
    bamEdgeDetectorKernelHostDB,
    bamEdgeDetectorKernelExecFuncDB
};



int32_t EDGE_DETECTOR_SOBEL_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = EDGE_DETECTOR_SOBEL_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = EDGE_DETECTOR_SOBEL_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = EDGE_DETECTOR_SOBEL_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(EDGE_DETECTOR_SOBEL_TI_graphArgs) ;
  return 0;
}

int32_t EDGE_DETECTOR_SOBEL_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      EDGE_DETECTOR_SOBEL_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    EDGE_DETECTOR_SOBEL_TI_graphArgs * graphArgs = (EDGE_DETECTOR_SOBEL_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]= {\
            {SOURCE_NODE,           BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,  NULL},\
            {SOBEL_XY_NODE,      BAM_TI_KERNELID_SOBELXY,          NULL},\
            {SOBEL_MAG_THRESHOLDING_NODE,      BAM_TI_KERNELID_SOBELMAG_THRESHOLDING,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[SOBEL_XY_NODE].kernelArgs       = (void *)&graphArgs->sobelArgs;
    NODELIST[SOBEL_MAG_THRESHOLDING_NODE].kernelArgs       = (void *)&graphArgs->sobelMagThresholdingArgs;
    NODELIST[SINK_NODE].kernelArgs       = (void *)&graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {SOBEL_XY_NODE, BAM_SOBEL_XY_INPUT_IMAGE_PORT}},\

            {{SOBEL_XY_NODE, BAM_SOBEL_XY_OUTPUT_X_PORT},
                            {SOBEL_MAG_THRESHOLDING_NODE, BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT}},\

            {{SOBEL_XY_NODE, BAM_SOBEL_XY_OUTPUT_Y_PORT},
                            {SOBEL_MAG_THRESHOLDING_NODE, BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT}},\

            {{SOBEL_MAG_THRESHOLDING_NODE, BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /* for bin pack output just replace the sobel mag thresholding node with the bin pack kernel */
    if ( createParams->iEdgeDetectorCreateParams->outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK )
    {
      NODELIST[SOBEL_MAG_THRESHOLDING_NODE].kernelId = BAM_TI_KERNELID_SOBELMAG_THRESHOLDING_BIN_PACK;
    }
    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gEdgeDetector_BAM_TI_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gEdgeDetector_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = EDGE_DETECTOR_SOBEL_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = EDGE_DETECTOR_SOBEL_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = EDGE_DETECTOR_SOBEL_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &EDGE_DETECTOR_SOBEL_TI_initKernelsArgs;
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
      PRINTF("Hough Index Calculation : Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("Hough Index Calculation: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("Hough Index Calculation  : Graph construction failed!!!");
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
  uint32_t    blockOffset,
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
  param->blkOffset            = blockOffset;
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t EDGE_DETECTOR_SOBEL_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  EDGE_DETECTOR_SOBEL_TI_graphArgs              *graphArgs          = (EDGE_DETECTOR_SOBEL_TI_graphArgs*)args;
  EDMA_UTILS_autoIncrement_initParam  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_SobelXy_Args                    *sobelArgs = &(graphArgs->sobelArgs);
  BAM_SobelXyMagThresholding_Args     *sobelMagThresholdingArgs = &(graphArgs->sobelMagThresholdingArgs);
  EDMA_UTILS_autoIncrement_initParam  *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);
  uint16_t outBlockWidth;
  uint16_t outBlockHeight;

  outBlockWidth = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  outBlockHeight = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;

  if ( graphArgs->createParams->iEdgeDetectorCreateParams->outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK )
  {
    outBlockWidth = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH / 8U;
  }


  /* allocate maximum input block size */
  dmaReadKernelArgs->numInTransfers   = 1U;
  dmaReadKernelArgs->transferType     = EDMA_UTILS_TRANSFER_IN;

  /* Update dma node properties before executing the filter applet*/
  /* First transfer is for Y component of image buffer */
  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH  + EDGE_DETECTOR_SOBEL_BORDER_X,/*blkWidth */
    EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT + EDGE_DETECTOR_SOBEL_BORDER_Y,/*blkHeight*/
    EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH,/* extBlkIncrementX */
    EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    0,/* blkOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH  + EDGE_DETECTOR_SOBEL_BORDER_X,/* interMemPtrStride */
    0 /* dmaQueNo */
    );

  dmaWriteKernelArgs->numOutTransfers  = 1U;
  dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

  /* First transfer is for outputting Y component of image buffer */
  assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    outBlockWidth,/*blkWidth */
    outBlockHeight,/*blkHeight*/
    outBlockWidth,/* extBlkIncrementX */
    outBlockHeight,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    0,/* blkOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    outBlockWidth,/* interMemPtrStride */
    1U /* dmaQueNo */
    );

  sobelArgs->maxBlockWidth  = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  sobelArgs->maxBlockHeight = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;

  sobelMagThresholdingArgs->maxBlockWidth   = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  sobelMagThresholdingArgs->maxBlockHeight  = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t EDGE_DETECTOR_SOBEL_TI_execute(
        BAM_GraphMem * graphMem,
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
#define EDGE_DETECTOR_SOBEL_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

int32_t EDGE_DETECTOR_SOBEL_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint16_t threshold,
                                  uint8_t outputFormat
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_SobelXy_CtrlArgs                sobelXyArgs;
  BAM_SobelXyMagThresholding_CtrlArgs sobelXyMagThresholdArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  uint16_t outputPitch;

  outputPitch = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;

  if ( outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK )
  {
    outputPitch = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH / 8U;
  }

  sobelXyArgs.computeWidth  = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  sobelXyArgs.computeHeight = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;
  sobelXyArgs.inputPitch    = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH + EDGE_DETECTOR_SOBEL_BORDER_X;
  sobelXyArgs.outputPitch   = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;

  sobelXyMagThresholdArgs.computeWidth  = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  sobelXyMagThresholdArgs.computeHeight = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;
  sobelXyMagThresholdArgs.inputPitch    = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
  sobelXyMagThresholdArgs.outputPitch   = outputPitch;
  sobelXyMagThresholdArgs.threshold     = threshold;

  status = BAM_controlNode( graphHandle, SOBEL_XY_NODE, &sobelXyArgs);
  if ( status == BAM_S_SUCCESS )
  {
    status = BAM_controlNode( graphHandle, SOBEL_MAG_THRESHOLDING_NODE, &sobelXyMagThresholdArgs);
  }

  return status;
}




int32_t EDGE_DETECTOR_SOBEL_TI_dmaControl(
                                const BAM_GraphMem *graphMem,
                                uint16_t imageWidth,
                                uint16_t imageHeight,
                                uint16_t inputPitch,
                                uint16_t outputPitch,
                                uint8_t  *inputDataPtr,
                                uint8_t  *outputDataPtr,
                                uint8_t  outputFormat
                                )

{
    EDMA_UTILS_autoIncrement_updateParams  dmaReadUpdateParams;
    EDMA_UTILS_autoIncrement_updateParams  dmaWriteUpdateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint16_t effImageWidth;
    uint16_t effImageHeight;
    uint16_t blockWidth;
    uint16_t blockHeight;
    uint16_t outEffImgWidth;

    blockWidth  = EDGE_DETECTOR_SOBEL_COMPUTE_WIDTH;
    blockHeight = EDGE_DETECTOR_SOBEL_COMPUTE_HEIGHT;


    effImageWidth  = EDGE_DETECTOR_SOBEL_CEIL(imageWidth  - EDGE_DETECTOR_SOBEL_BORDER_X, blockWidth);
    effImageHeight = EDGE_DETECTOR_SOBEL_CEIL(imageHeight - EDGE_DETECTOR_SOBEL_BORDER_Y, blockHeight);

    outEffImgWidth = effImageWidth;

    if ( outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK )
    {
      outEffImgWidth = effImageWidth / 8U;
    }

    dmaReadUpdateParams.transferType = EDMA_UTILS_TRANSFER_IN;
    dmaReadUpdateParams.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    assignDMAautoIncrementParams(&dmaReadUpdateParams.updateParams[0],
      effImageWidth  + EDGE_DETECTOR_SOBEL_BORDER_X,/* roiWidth : This will come during Process call via bufDesc */
      effImageHeight + EDGE_DETECTOR_SOBEL_BORDER_Y,/* roiHeight : This will come during Process call via bufDesc */
      0,/*blkWidth */
      0,/*blkHeight*/
      0,/* extBlkIncrementX */
      0,/* extBlkIncrementY */
      0,/* intBlkIncrementX */
      0,/* intBlkIncrementY */
      0,/* roiOffset */
      0,/*blockOffset */
      inputDataPtr,/* extMemPtr : This will come during process call */
      inputPitch,/* extMemPtrStride */
      NULL,/*Int Mem Ptr DMA node will be populating this field */
      0,/* interMemPtrStride */
      0 /* dmaQueNo */
      );




    status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadUpdateParams);

    if (status!= BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    dmaWriteUpdateParams.transferType = EDMA_UTILS_TRANSFER_OUT;
    dmaWriteUpdateParams.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;


    assignDMAautoIncrementParams(&dmaWriteUpdateParams.updateParams[0],
     outEffImgWidth,/* roiWidth : This will come during Process call via bufDesc */
     effImageHeight,/* roiHeight : This will come during Process call via bufDesc */
     0,/*blkWidth */
     0,/*blkHeight*/
     0,/* extBlkIncrementX */
     0,/* extBlkIncrementY */
     0,/* intBlkIncrementX */
     0,/* intBlkIncrementY */
     0,/* roiOffset */
     0,/*blockOffset */
     outputDataPtr,/* extMemPtr : This will come during process call */
     outputPitch,/* extMemPtrStride */
     NULL,/*Int Mem Ptr DMA node will be populating this field */
     0,/* interMemPtrStride */
     0 /* dmaQueNo */
     );

    status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteUpdateParams);


 Exit:
    return status;
}

