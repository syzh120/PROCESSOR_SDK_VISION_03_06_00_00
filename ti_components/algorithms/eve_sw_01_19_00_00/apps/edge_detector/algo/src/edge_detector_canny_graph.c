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
 *  @file      edge_detector_canny_graph.c
 *
 *  @brief     This file defines the functions for graph for Canny Edge Detection applet
 *
 *  @version 0.0 (Dec 2014) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "iedge_detector_ti.h"

#include "edma_utils.h"

#include "edge_detector_canny_graph_int.h"

#include "edge_detector_alg_int.h"
#include "bam_sobel_xy.h"

static int32_t EDGE_DETECTOR_CANNY_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE       (0)
#define FILTER_2D_NODE    (1U)
#define GRADIENT_XY_NODE  (2U)
#define CANNY_NMS_NODE    (3U)
#define SINK_NODE         (4U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_FILTER_2D,
    BAM_TI_KERNELID_GRADIENT_XY,
    BAM_TI_KERNELID_CANNY_NMS,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_EDGE_DETECTOR_CANNY_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamEdgeDetectorCannyKernelHostDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_yuv420Fir2dSeparableYKernel, &gBAM_TI_yuv420Fir2dSeparableYHelperFunc,
            "ti_filter2d", BAM_TI_KERNELID_FILTER_2D },

    { &gBAM_TI_gradXYmagKernel, &gBAM_TI_gradXYmagHelperFunc,
            "ti_gradient_xy", BAM_TI_KERNELID_GRADIENT_XY },

    { &gBAM_TI_cannyNonMaximumSuppressionKernel, &gBAM_TI_cannyNonMaximumSuppressionHelperFunc,
            "ti_canny_nms", BAM_TI_KERNELID_CANNY_NMS },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamEdgeDetectorCannyKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_yuv420Fir2dSeparableYKernel, &gBAM_TI_yuv420Fir2dSeparableYExecFunc,
              "ti_filter2d", BAM_TI_KERNELID_FILTER_2D},

    { &gBAM_TI_gradXYmagKernel, &gBAM_TI_gradXYmagExecFunc,
            "ti_gradient_xy", BAM_TI_KERNELID_GRADIENT_XY },

    { &gBAM_TI_cannyNonMaximumSuppressionKernel, &gBAM_TI_cannyNonMaximumSuppressionExecFunc,
            "ti_canny_nms", BAM_TI_KERNELID_CANNY_NMS },

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};


BAM_KernelDBdef gEdgeDetectorCanny_BAM_TI_kernelDBdef =
{
    sizeof(bamEdgeDetectorCannyKernelExecFuncDB) / sizeof(bamEdgeDetectorCannyKernelExecFuncDB[0]),
    bamEdgeDetectorCannyKernelHostDB,
    bamEdgeDetectorCannyKernelExecFuncDB
};



int32_t EDGE_DETECTOR_CANNY_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = EDGE_DETECTOR_CANNY_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = EDGE_DETECTOR_CANNY_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = EDGE_DETECTOR_CANNY_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(EDGE_DETECTOR_CANNY_TI_graphArgs) ;
  return 0;
}

int32_t EDGE_DETECTOR_CANNY_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      EDGE_DETECTOR_CANNY_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    EDGE_DETECTOR_CANNY_TI_graphArgs * graphArgs = (EDGE_DETECTOR_CANNY_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint8_t  filterCoeff[9] = { 1, 2, 1, 1, 2, 1, 0, 0, 0};

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
            {FILTER_2D_NODE,      BAM_TI_KERNELID_FILTER_2D,          NULL},\
            {GRADIENT_XY_NODE,      BAM_TI_KERNELID_GRADIENT_XY,          NULL},\
            {CANNY_NMS_NODE,      BAM_TI_KERNELID_CANNY_NMS,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[FILTER_2D_NODE].kernelArgs       = (void *)&graphArgs->filter2dArgs;
    NODELIST[GRADIENT_XY_NODE].kernelArgs       = (void *)&graphArgs->gradientXyArgs;
    NODELIST[CANNY_NMS_NODE].kernelArgs       = (void *)&graphArgs->cannyNmsArgs;
    NODELIST[SINK_NODE].kernelArgs       = (void *)&graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {FILTER_2D_NODE, BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT}},\

            {{FILTER_2D_NODE, BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT},
                            {GRADIENT_XY_NODE, BAM_GRADXYMAG_INPUT_PORT}},\

            {{GRADIENT_XY_NODE, BAM_GRADXYMAG_X_OUTPUT_PORT},
                            {CANNY_NMS_NODE, BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT}},\

            {{GRADIENT_XY_NODE, BAM_GRADXYMAG_Y_OUTPUT_PORT},
                            {CANNY_NMS_NODE, BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT}},\

            {{GRADIENT_XY_NODE, BAM_GRADXYMAG_MAG_OUTPUT_PORT},
                            {CANNY_NMS_NODE, BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT}},\

            {{CANNY_NMS_NODE, BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gEdgeDetectorCanny_BAM_TI_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* Copy the filter coefficients to the graph memory */
    memcpy( graphArgs->filterCoeff, filterCoeff, sizeof(filterCoeff));

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gEdgeDetectorCanny_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = EDGE_DETECTOR_CANNY_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = EDGE_DETECTOR_CANNY_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = EDGE_DETECTOR_CANNY_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &EDGE_DETECTOR_CANNY_TI_initKernelsArgs;
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
      PRINTF("Canny Edge Detector : Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("Canny Edge Detector: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("Canny Edge Detector  : Graph construction failed!!!");
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
static int32_t EDGE_DETECTOR_CANNY_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  EDGE_DETECTOR_CANNY_TI_graphArgs              *graphArgs          = (EDGE_DETECTOR_CANNY_TI_graphArgs*)args;
  EDMA_UTILS_autoIncrement_initParam  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_Yuv420_fir2dseparable_Args      *filter2dArgs   = &(graphArgs->filter2dArgs);
  BAM_GradXYmag_Args                  *gradientXyArgs = &(graphArgs->gradientXyArgs);
  BAM_CannyNonMaximumSuppression_Args *cannyNmsArgs   = &(graphArgs->cannyNmsArgs);

  EDMA_UTILS_autoIncrement_initParam  *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);

  uint16_t outBlockWidth;
  uint16_t outBlockHeight;
  uint16_t blockWidth;
  uint16_t blockHeight;

  outBlockWidth  = EDGE_DETECTOR_CANNY_OUT_BLOCK_WIDTH;
  outBlockHeight = EDGE_DETECTOR_CANNY_OUT_BLOCK_HEIGHT;

  blockWidth  = outBlockWidth  + EDGE_DETECTOR_CANNY_BORDER;
  blockHeight = outBlockHeight + EDGE_DETECTOR_CANNY_BORDER;

  /* allocate maximum input block size */
  dmaReadKernelArgs->numInTransfers   = 1U;
  dmaReadKernelArgs->transferType     = EDMA_UTILS_TRANSFER_IN;

  /* Update dma node properties before executing the filter applet*/
  /* First transfer is for Y component of image buffer */
  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    blockWidth,/*blkWidth */
    blockHeight,/*blkHeight*/
    outBlockWidth,/* extBlkIncrementX */
    outBlockHeight,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    0,/* blkOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    blockWidth,/* interMemPtrStride */
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
    outBlockWidth + (EDGE_DETECTOR_CANNY_BORDER - EDGE_DETECTOR_CANNY_NMS_BORDER),/* interMemPtrStride */
    1U /* dmaQueNo */
    );

  filter2dArgs->blockWidth  = blockWidth  - EDGE_DETECTOR_CANNY_FILTER_BORDER;
  filter2dArgs->blockHeight = blockHeight - EDGE_DETECTOR_CANNY_FILTER_BORDER;
  filter2dArgs->coefWidth   = EDGE_DETECTOR_CANNY_FILTER_SIZE;
  filter2dArgs->coefHeight  = EDGE_DETECTOR_CANNY_FILTER_SIZE;
  filter2dArgs->pitch       = blockWidth;
  filter2dArgs->coefPtr     = (uint8_t (*)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE])(void *)graphArgs->filterCoeff;
  filter2dArgs->rndBits     = 4U;

  blockWidth  = blockWidth  - EDGE_DETECTOR_CANNY_FILTER_BORDER;
  blockHeight = blockHeight - EDGE_DETECTOR_CANNY_FILTER_BORDER;

  gradientXyArgs->width           = (uint16_t)ALIGN_2SIMD( (uint32_t)blockWidth - (uint32_t)EDGE_DETECTOR_CANNY_GRADIENT_BORDER);
  gradientXyArgs->height          = blockHeight - EDGE_DETECTOR_CANNY_GRADIENT_BORDER;
  gradientXyArgs->pitch           = blockWidth;
  gradientXyArgs->gradientMethod  = EVE_VLIB_GRADIENT_MAGNITUDE_9BITS;

  cannyNmsArgs->maxBlockWidth   = outBlockWidth  + EDGE_DETECTOR_CANNY_BORDER;
  cannyNmsArgs->maxBlockHeight  = outBlockHeight + EDGE_DETECTOR_CANNY_BORDER;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t EDGE_DETECTOR_CANNY_TI_execute(
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
#define EDGE_DETECTOR_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

int32_t EDGE_DETECTOR_CANNY_TI_kernelControl(const BAM_GraphMem * graphMem,
                                  uint8_t lowThreshold,
                                  uint8_t highThreshold
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  BAM_CannyNonMaximumSuppression_CtrlArgs cannyCtrlArgs;
  uint16_t outBlockWidth;
  uint16_t outBlockHeight;

  outBlockWidth  = EDGE_DETECTOR_CANNY_OUT_BLOCK_WIDTH;
  outBlockHeight = EDGE_DETECTOR_CANNY_OUT_BLOCK_HEIGHT;

  cannyCtrlArgs.computeWidth      = outBlockWidth;
  cannyCtrlArgs.computeHeight     = outBlockHeight;
  cannyCtrlArgs.inBlockPitch      = outBlockWidth + (EDGE_DETECTOR_CANNY_BORDER - EDGE_DETECTOR_CANNY_NMS_BORDER);
  cannyCtrlArgs.outBlockPitch     = outBlockWidth + (EDGE_DETECTOR_CANNY_BORDER - EDGE_DETECTOR_CANNY_NMS_BORDER);
  cannyCtrlArgs.lowThreshold      = lowThreshold;
  cannyCtrlArgs.highThreshold     = highThreshold;



  status = BAM_controlNode( graphHandle, CANNY_NMS_NODE, &cannyCtrlArgs);

  return status;
}




int32_t EDGE_DETECTOR_CANNY_TI_dmaControl(
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
#if 1
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint16_t effImageWidth;
    uint16_t effImageHeight;
    uint16_t blockWidth;
    uint16_t blockHeight;
    uint16_t outEffImgWidth;

    blockWidth  = EDGE_DETECTOR_CANNY_OUT_BLOCK_WIDTH;
    blockHeight = EDGE_DETECTOR_CANNY_OUT_BLOCK_HEIGHT;


    effImageWidth  = EDGE_DETECTOR_CEIL(imageWidth  - EDGE_DETECTOR_CANNY_BORDER, blockWidth);
    effImageHeight = EDGE_DETECTOR_CEIL(imageHeight - EDGE_DETECTOR_CANNY_BORDER, blockHeight);

    outEffImgWidth = effImageWidth;

    dmaReadUpdateParams.transferType = EDMA_UTILS_TRANSFER_IN;
    dmaReadUpdateParams.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    assignDMAautoIncrementParams(&dmaReadUpdateParams.updateParams[0],
      effImageWidth  + EDGE_DETECTOR_CANNY_BORDER,/* roiWidth : This will come during Process call via bufDesc */
      effImageHeight + EDGE_DETECTOR_CANNY_BORDER,/* roiHeight : This will come during Process call via bufDesc */
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

#endif
 Exit:
    return status;
}

