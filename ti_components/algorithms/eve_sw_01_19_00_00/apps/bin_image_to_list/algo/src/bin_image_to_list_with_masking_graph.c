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

#include "bin_image_to_list_with_masking_graph_int.h"

#include "edma_utils.h"
#include "bam_dma_autoincrement_node.h"

static int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


/* Graph1 is for using bin to list along with binary masking */
#define SOURCE_GRAPH1_NODE                     (0)
#define BINARY_MASKING_GRAPH1_NODE             (1U)
#define BIN_IMG_TO_LIST_GRAPH1_NODE            (2U)
#define SINK_GRAPH1_NODE                       (3U)

/* Graph2 is for using bin to list alone */
#define SOURCE_GRAPH2_NODE                 (0)
#define BIN_IMG_TO_LIST_GRAPH2_NODE        (1U)
#define SINK_GRAPH2_NODE                   (2U)

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE,
    BAM_TI_KERNELID_BINARY_MASKING,
    BAM_TI_KERNELID_BIN_IMAGE_TO_LIST,
    BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE
} BAM_BIN_IMAGE_TO_LIST_WITH_MASKING_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamBinToListKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomBinToListNodeReadKernel, &gBAM_TI_dmaCustomBinToListNodeReadKernelHelperFunc,
            "ti_custom_bin_to_list_dma_read", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE},

    { &gBAM_TI_binaryMaskingKernel,   &gBAM_TI_binaryMaskingHelperFunc,
            "ti_binary_masking",   BAM_TI_KERNELID_BINARY_MASKING },

    { &gBAM_TI_binImageToListKernel,   &gBAM_TI_binImageToListHelperFunc,
            "ti_image_bin_img_to_list",   BAM_TI_KERNELID_BIN_IMAGE_TO_LIST },

    { &gBAM_TI_dmaCustomBinToListNodeWriteKernel, &gBAM_TI_dmaCustomBinToListNodeWriteKernelHelperFunc,
            "ti_custom_bin_to_list_dma_write", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamBinToListKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomBinToListNodeReadKernel, &gBAM_TI_dmaCustomBinToListNodeReadKernelExecFunc,
            "ti_custom_bin_to_list_dma_read", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE},

    { &gBAM_TI_binaryMaskingKernel,   &gBAM_TI_binaryMaskingExecFunc,
            "ti_binary_masking",   BAM_TI_KERNELID_BINARY_MASKING },

    { &gBAM_TI_binImageToListKernel,   &gBAM_TI_binImageToListExecFunc,
            "ti_image_bin_img_to_list",   BAM_TI_KERNELID_BIN_IMAGE_TO_LIST },

    { &gBAM_TI_dmaCustomBinToListNodeWriteKernel, &gBAM_TI_dmaCustomBinToListNodeWriteKernelExecFunc,
            "ti_custom_bin_to_list_dma_write", BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE},
};


BAM_KernelDBdef gBinToList_BAM_TI_kernelDBdef =
{
    sizeof(bamBinToListKernelExecFuncDB) / sizeof(bamBinToListKernelExecFuncDB[0]),
    bamBinToListKernelHostDB,
    bamBinToListKernelExecFuncDB
};



int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs) ;
  return 0;
}

int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs * graphArgs = (BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    BAM_NodeParams * NODELIST;
    BAM_EdgeParams * EDGELIST;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST_GRAPH1[]= {\
            {SOURCE_GRAPH1_NODE,           BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE,  NULL},\
            {BINARY_MASKING_GRAPH1_NODE,   BAM_TI_KERNELID_BINARY_MASKING,          NULL},\
            {BIN_IMG_TO_LIST_GRAPH1_NODE,  BAM_TI_KERNELID_BIN_IMAGE_TO_LIST,          NULL},\
            {SINK_GRAPH1_NODE,             BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST_GRAPH1[SOURCE_GRAPH1_NODE].kernelArgs      = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST_GRAPH1[BINARY_MASKING_GRAPH1_NODE].kernelArgs      = (void *)&graphArgs->binaryMaskingKernelArgs;
    NODELIST_GRAPH1[BIN_IMG_TO_LIST_GRAPH1_NODE].kernelArgs      = (void *)&graphArgs->binImgToListKernelArgs;

    BAM_EdgeParams EDGELIST_GRAPH1[]= {\
            {{SOURCE_GRAPH1_NODE, BAM_SOURCE_NODE_PORT1},
                            {BINARY_MASKING_GRAPH1_NODE, BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT}},\

            {{SOURCE_GRAPH1_NODE, BAM_SOURCE_NODE_PORT2},
                            {BINARY_MASKING_GRAPH1_NODE, BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT}},\

            {{BINARY_MASKING_GRAPH1_NODE, BAM_BINARY_MASKING_OUTPUT_PORT},
                            {BIN_IMG_TO_LIST_GRAPH1_NODE, BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG}},\

            {{BIN_IMG_TO_LIST_GRAPH1_NODE, BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY},
                            {SINK_GRAPH1_NODE, BAM_SINK_NODE_PORT1}},\

            {{BIN_IMG_TO_LIST_GRAPH1_NODE, BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE},
                            {SINK_GRAPH1_NODE, BAM_SINK_NODE_PORT2}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /* Node list and edege list for the case when only bin to list is required without any masking */
    BAM_NodeParams NODELIST_GRAPH2[]= {\
            {SOURCE_GRAPH2_NODE,           BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAREAD_NODE,  NULL},\
            {BIN_IMG_TO_LIST_GRAPH2_NODE,  BAM_TI_KERNELID_BIN_IMAGE_TO_LIST,          NULL},\
            {SINK_GRAPH2_NODE,             BAM_TI_KERNELID_CUSTOM_BIN_TO_LIST_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST_GRAPH2[SOURCE_GRAPH2_NODE].kernelArgs      = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST_GRAPH2[BIN_IMG_TO_LIST_GRAPH2_NODE].kernelArgs      = (void *)&graphArgs->binImgToListKernelArgs;

    BAM_EdgeParams EDGELIST_GRAPH2[]= {\
            {{SOURCE_GRAPH2_NODE, BAM_SOURCE_NODE_PORT1},
                            {BIN_IMG_TO_LIST_GRAPH2_NODE, BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG}},\

            {{BIN_IMG_TO_LIST_GRAPH2_NODE, BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY},
                            {SINK_GRAPH2_NODE, BAM_SINK_NODE_PORT1}},\

            {{BIN_IMG_TO_LIST_GRAPH2_NODE, BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE},
                            {SINK_GRAPH2_NODE, BAM_SINK_NODE_PORT2}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /* Default case is without maskign */
    NODELIST = NODELIST_GRAPH2;
    EDGELIST = EDGELIST_GRAPH2;

    if ( createParams->icreateParams->enableMasking == 1)
    {
      NODELIST = NODELIST_GRAPH1;
      EDGELIST = EDGELIST_GRAPH1;
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gBinToList_BAM_TI_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gBinToList_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_SIZE;

    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &BIN_IMAGE_TO_LIST_WITH_MASKING_TI_initKernelsArgs;
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
static int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs              *graphArgs          = (BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs*)args;
  BAM_BinaryMasking_Args                     *binaryMaskingKernelArgs  = &(graphArgs->binaryMaskingKernelArgs);
  BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args       *dmaReadKernelArgs        = &(graphArgs->dmaReadKernelArgs);

  /* allocate maximum input block size */
  dmaReadKernelArgs->maxBlkWidth    = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_MAX_BLOCK_SIZE;
  dmaReadKernelArgs->maxBlkHeight   = 1;
  dmaReadKernelArgs->enableMasking  = graphArgs->createParams->icreateParams->enableMasking;

  binaryMaskingKernelArgs->maxBlockWidth    = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_MAX_BLOCK_SIZE;
  binaryMaskingKernelArgs->maxBlockHeight   = 1;


  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_execute(
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

int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint16_t computeWidth,
                                  uint16_t computeHeight,
                                  uint8_t  startX,
                                  uint8_t  startY,
                                  uint8_t  outputListQFormat,
                                  uint8_t  outputListOrder,
                                  uint8_t  enableMasking
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_BinaryMasking_CtrlArgs     binaryMaskingCtrlArgs;
  BAM_Bin_image_to_list_ctrlArgs binImgToListCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  uint8_t binToListNodeId;

  binaryMaskingCtrlArgs.computeWidth       = computeWidth;
  binaryMaskingCtrlArgs.computeHeight      = computeHeight;
  binaryMaskingCtrlArgs.inputBitDataPitch  = computeWidth / 8U;
  binaryMaskingCtrlArgs.inputByteDataPitch = computeWidth;
  binaryMaskingCtrlArgs.outputPitch        = computeWidth / 8U;

  /* Although input to this kernel is bin packed data. Its blockWidth and pitch is still given in terms of pixels and not in terms of bytes */
  binImgToListCtrlArgs.blkWidth       = computeWidth;
  binImgToListCtrlArgs.blkHeight      = computeHeight;
  binImgToListCtrlArgs.blkStride      = computeWidth;
  binImgToListCtrlArgs.frameStartX    = startX;
  binImgToListCtrlArgs.frameStartY    = startY;
  binImgToListCtrlArgs.outputQformat  = outputListQFormat;
  if ( outputListOrder == BIN_IMAGE_TO_LIST_TI_ORDER_XY)
  {
    binImgToListCtrlArgs.xyOrder        = BAM_BIN_IMAGE_TO_LIST_XY;
  }
  else
  {
    binImgToListCtrlArgs.xyOrder        = BAM_BIN_IMAGE_TO_LIST_YX;
  }

  binToListNodeId = BIN_IMG_TO_LIST_GRAPH2_NODE;

  if ( enableMasking == 1U )
  {
    status = BAM_controlNode( graphHandle, BINARY_MASKING_GRAPH1_NODE, &binaryMaskingCtrlArgs);
    if (status!= BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }
    binToListNodeId = BIN_IMG_TO_LIST_GRAPH1_NODE;
  }



  status = BAM_controlNode( graphHandle, binToListNodeId, &binImgToListCtrlArgs);
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


int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t * inputDataPtr,
                                uint8_t * inputMaskPtr,
                                uint8_t * outputListPtr,
                                uint8_t * ptrToListSize,
                                uint16_t  imageWidth,
                                uint16_t  imageHeight,
                                uint16_t  inputDataPitch,
                                uint16_t  inputMaskPitch,
                                uint16_t computeWidth,
                                uint16_t computeHeight,
                                uint8_t  enableMasking
                                )

{
    BAM_DMA_CUSTOM_BIN_TO_LIST_READ_ctrlArgs dmaReadUpdateParams;
    BAM_DMA_CUSTOM_BIN_TO_LIST_WRITE_ctrlArgs dmaWriteUpdateParams;

    int32_t status = BAM_S_SUCCESS;

    uint8_t sourceNodeId;
    uint8_t sinkNodeId;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint16_t effImageWidth;
    uint16_t effImageHeight;

    effImageWidth  = CEIL(imageWidth,  computeWidth);
    effImageHeight = CEIL(imageHeight, computeHeight);

    assignDMAautoIncrementParams(&dmaReadUpdateParams.inTransferProp[0],
      effImageWidth / 8U,/* roiWidth : This will come during Process call via bufDesc */
      effImageHeight,/* roiHeight : This will come during Process call via bufDesc */
      computeWidth / 8U,/*blkWidth */
      computeHeight,/*blkHeight*/
      computeWidth / 8U,/* extBlkIncrementX */
      computeHeight,/* extBlkIncrementY */
      0,/* intBlkIncrementX */
      0,/* intBlkIncrementY */
      0,/* roiOffset */
      0,/*blockOffset */
      inputDataPtr,/* extMemPtr : This will come during process call */
      inputDataPitch,/* extMemPtrStride */
      NULL,/*Int Mem Ptr DMA node will be populating this field */
      computeWidth  / 8U,/* interMemPtrStride */
      0 /* dmaQueNo */
      );

    assignDMAautoIncrementParams(&dmaReadUpdateParams.inTransferProp[1],
      effImageWidth,/* roiWidth : This will come during Process call via bufDesc */
      effImageHeight,/* roiHeight : This will come during Process call via bufDesc */
      computeWidth,/*blkWidth */
      computeHeight,/*blkHeight*/
      computeWidth,/* extBlkIncrementX */
      computeHeight,/* extBlkIncrementY */
      0,/* intBlkIncrementX */
      0,/* intBlkIncrementY */
      0,/* roiOffset */
      0,/*blockOffset */
      inputMaskPtr,/* extMemPtr : This will come during process call */
      inputMaskPitch,/* extMemPtrStride */
      NULL,/*Int Mem Ptr DMA node will be populating this field */
      computeWidth,/* interMemPtrStride */
      0 /* dmaQueNo */
      );

    sourceNodeId = SOURCE_GRAPH2_NODE;
    sinkNodeId   = SINK_GRAPH2_NODE;

    if ( enableMasking == 1U )
    {
      sourceNodeId = SOURCE_GRAPH1_NODE;
      sinkNodeId   = SINK_GRAPH1_NODE;
    }


    status= BAM_controlNode(graphHandle, sourceNodeId, &dmaReadUpdateParams);

    if (status!= BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    dmaWriteUpdateParams.ptrToXyListBuf = outputListPtr;
    dmaWriteUpdateParams.ptrToListSizeBuf = ptrToListSize;

    status= BAM_controlNode(graphHandle, sinkNodeId, &dmaWriteUpdateParams);


 Exit:
    return status;
}

