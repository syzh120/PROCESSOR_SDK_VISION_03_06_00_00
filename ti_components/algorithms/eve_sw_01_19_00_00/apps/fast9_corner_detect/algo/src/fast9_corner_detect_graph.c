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
 *  @file      fast9_corner_detect_graph.c
 *
 *  @brief      This file defines the functions for FAST9 corner detect graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

/* #define FIND_BEST_BLOCKDIM */

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/* #pragma RESET_MISRA ("required") */

#include "fast9_corner_detect_graph_int.h"
#include "edma_utils.h"

static int32_t FAST9_CORNER_DETECT_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0U
#define FAST9_NODE  1U
#define SINK_NODE   2U

#define MAX_KERNEL_ID 255

typedef enum fast9CorenerDetectbam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_FAST9,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_FAST9_CORNDER_DETECT_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamFast9CornerDetectKernelHostDB[] =
{
  { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
                  "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  { &gBAM_TI_fast9Kernel, &gBAM_TI_fast9HelperFunc,
                 "ti_image_fast9", BAM_TI_KERNELID_FAST9},
  { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
                 "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamFast9CornerDetectKernelExecFuncDB[] =
{
  { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
                "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
  { &gBAM_TI_fast9Kernel, &gBAM_TI_fast9ExecFunc,
                "ti_image_fast9", BAM_TI_KERNELID_FAST9},
  { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
                "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.7  */
/* It is good to have all static variables at one place to increase readability and maintenance of code.
     Hence, if there are 2 functions in a file and one of them need some data to be static
     he/she will keep it at top of file. As result of this the static data is also visible to another
     function though the function does not need to see it. So the rule is voilated.
*/
static BAM_KernelDBdef gFast9CornerDetect_TI_BAM_kernelDBdef =
{
  sizeof(bamFast9CornerDetectKernelExecFuncDB) / sizeof(bamFast9CornerDetectKernelExecFuncDB[0]),
  bamFast9CornerDetectKernelHostDB,
  bamFast9CornerDetectKernelExecFuncDB
};
/* RESET_MISRA("8.7")  -> Reset rule 8.7  */

int32_t FAST9_CORNER_DETECT_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = FAST9_CORNER_DETECT_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = FAST9_CORNER_DETECT_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = FAST9_CORNER_DETECT_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(FAST9_CORNER_DETECT_TI_graphArgs) ;
  return 0;
}

int32_t FAST9_CORNER_DETECT_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      FAST9_CORNER_DETECT_TI_graphArgs * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    FAST9_CORNER_DETECT_TI_graphArgs * graphArgs = (FAST9_CORNER_DETECT_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]=
    {
        {SOURCE_NODE,               BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,      NULL},
        {FAST9_NODE,                BAM_TI_KERNELID_FAST9,                                     NULL},
        {SINK_NODE,                 BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,     NULL},
        {BAM_END_NODE_MARKER,       0,                                          NULL},
    };
    /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
    NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
    NODELIST[1].kernelArgs = (void *)(&graphArgs->fast9KernelArgs);
    NODELIST[2].kernelArgs = (void *)(&graphArgs->dmaWriteKernelArgs);

    BAM_EdgeParams EDGELIST[]=
    {
          {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {FAST9_NODE,  BAM_FAST9_INPUT_PORT}},\
          {{FAST9_NODE,     BAM_FAST9_OUTPUT_PORT},           {SINK_NODE, BAM_SINK_NODE_PORT1}},\
          {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gFast9CornerDetect_TI_BAM_kernelDBdef);

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
  graphCreateParams.kernelDB             = &gFast9CornerDetect_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = FAST9_CORNER_DETECT_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = FAST9_CORNER_DETECT_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = FAST9_CORNER_DETECT_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &FAST9_CORNER_DETECT_TI_initKernelsArgs;
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
    PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth  or blockHeight ");
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
  uint32_t    blkOffset,
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
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}


/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t FAST9_CORNER_DETECT_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
    int32_t status = BAM_S_SUCCESS;
    FAST9_CORNER_DETECT_TI_graphArgs    *graphArgs          = (FAST9_CORNER_DETECT_TI_graphArgs*)args;
    EDMA_UTILS_autoIncrement_initParam  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
    EDMA_UTILS_autoIncrement_initParam  *dmaWriteKernelArgs = &(graphArgs->dmaWriteKernelArgs);

    dmaReadKernelArgs->numInTransfers   = 1;
    dmaReadKernelArgs->transferType     = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[0],
      0U,/* roiWidth : This will come during Process call via bufDesc */
      0U,/* roiHeight : This will come during Process call via bufDesc */
      FAST9_TI_BLK_WIDTH_MAX,/*blkWidth */
      FAST9_TI_BLK_HEIGHT_MAX,/*blkHeight*/
      0U,/* extBlkIncrementX */
      0U,/* extBlkIncrementY */
      0U,/* intBlkIncrementX */
      0U,/* intBlkIncrementY */
      0U,/* roiOffset */
      0U,/*blockOffset */
      NULL,/* extMemPtr : This will come during process call */
      0U,/* extMemPtrStride : This will be populated during process call using bufDesc */
      NULL,/* DMA node will be populating this field */
      0U,/* interMemPtrStride */
      0U /* dmaQueNo */
      );

    dmaWriteKernelArgs->numOutTransfers  = 1U;
    dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[0],
      0U,/* roiWidth : This will come during Process call via bufDesc */
      0U,/* roiHeight : This will come during Process call via bufDesc */
      FAST9_TI_BLK_WIDTH_MAX,/*blkWidth */
      FAST9_TI_BLK_HEIGHT_MAX,/*blkHeight*/
      0U,/* extBlkIncrementX */
      0U,/* extBlkIncrementY */
      0U,/* intBlkIncrementX */
      0U,/* intBlkIncrementY */
      0U,/* roiOffset */
      0U,/*blockOffset */
      NULL,/* extMemPtr : This will come during process call */
      0U,/* extMemPtrStride : This will be populated during process call using bufDesc */
      NULL,/* DMA node will be populating this field */
      0U,/* interMemPtrStride */
      1U /* dmaQueNo */
      );

    return (status);

}

int32_t FAST9_CORNER_DETECT_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Fast9_ctrlArgs * fast9KernelCtrlArgs
        )
{
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    status = BAM_controlNode(graphHandle, FAST9_NODE, fast9KernelCtrlArgs);

    return status;
}

int32_t FAST9_CORNER_DETECT_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc,
        const FAST9_CORNER_DETECT_TI_dmaCtrlArgs * dmaCtrlParams)
{
    const IVISION_BufPlanes * ivisionBufPlane;
    EDMA_UTILS_autoIncrement_updateParams updateParams;
    int32_t status = BAM_S_SUCCESS;
    int16_t                 compWidth;
    int16_t                 compHeight;
    int16_t                 outImageWidth;
    int16_t                 outImageHeight;
    uint8_t                 *extMemPtr;
    uint16_t                effectiveX;
    uint16_t                effectiveY;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    ivisionBufPlane = &inBufDesc->bufPlanes[dmaCtrlParams->level];

    compWidth   = (int16_t)dmaCtrlParams->blkWidth  - ( 2 * (int16_t)FAST9_TI_BORDER_X);
    compHeight  = (int16_t)dmaCtrlParams->blkHeight - ( 2 * (int16_t)FAST9_TI_BORDER_Y);

    outImageWidth   = (int16_t)dmaCtrlParams->activeImageWidth - ( 2 * (int16_t)FAST9_TI_BORDER_X);
    /* Since output is packed data so divide by 8 */
    outImageWidth   = outImageWidth/8;
    outImageHeight  = (int16_t)dmaCtrlParams->activeImageHeight  - ( 2 * (int16_t)FAST9_TI_BORDER_Y);


    updateParams.transferType = EDMA_UTILS_TRANSFER_IN;

    updateParams.updateMask =
            (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ALL &
              ((uint32_t)~(EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTR));


    effectiveX = ivisionBufPlane->frameROI.topLeft.x +
                    dmaCtrlParams->dx;

    effectiveY = ivisionBufPlane->frameROI.topLeft.y +
                    dmaCtrlParams->dy;

    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    extMemPtr = (uint8_t*)ivisionBufPlane->buf +
                          (( effectiveY *
                          ivisionBufPlane->width) +
                          effectiveX);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    assignDMAautoIncrementParams(&(updateParams.updateParams[0]),
          dmaCtrlParams->activeImageWidth,    /* roiWidth */
          dmaCtrlParams->activeImageHeight,   /* roiHeight */
          dmaCtrlParams->blkWidth,            /* blkWidth */
          dmaCtrlParams->blkHeight,           /* blkHeight */
          (uint16_t)compWidth,                /* extBlkIncrementX */
          (uint16_t)compHeight,               /* extBlkIncrementY */
          0U,                                 /* intBlkIncrementX */
          0U,                                 /* intBlkIncrementY */
          0U,                                 /* roiOffset */
          0U,                                 /* blockoffset */
          extMemPtr,                          /* extMemPtr */
          (uint16_t)ivisionBufPlane->width,   /* extMemPtrStride */
          NULL,                               /* interMemPtr */
          (uint16_t)dmaCtrlParams->blkWidth,  /* interMemPtrStride */
          0U                                  /* dmaQueNo */
          );

    status = BAM_controlNode(graphHandle, SOURCE_NODE, &updateParams);

    if (status != BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    ivisionBufPlane= &outBufDesc->bufPlanes[0];

    /* External memory pointer for out transfer */
    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    extMemPtr = (uint8_t*)ivisionBufPlane->buf +
                        ((ivisionBufPlane->frameROI.topLeft.y *
                        ivisionBufPlane->width) +
                        ivisionBufPlane->frameROI.topLeft.x);
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    assignDMAautoIncrementParams(&(updateParams.updateParams[0]),
      (uint16_t)outImageWidth,                /* roiWidth */
      (uint16_t)outImageHeight,               /* roiHeight */
      ((uint16_t)compWidth)/8U,               /* blkWidth */
      (uint16_t)compHeight,                   /* blkHeight */
      ((uint16_t)compWidth)/8U,               /* extBlkIncrementX */
      (uint16_t)compHeight,                   /* extBlkIncrementY */
      0U,                                     /* intBlkIncrementX */
      0U,                                     /* intBlkIncrementY */
      0U,                                     /* roiOffset */
      0U,                                     /* blockoffset */
      extMemPtr,                              /* extMemPtr */
      (uint16_t)ivisionBufPlane->width,       /* extMemPtrStride */
      NULL,                                   /* interMemPtr */
      ((uint16_t)compWidth)/8U,               /* interMemPtrStride */
      1U                                      /* dmaQueNo */
      );

    status= BAM_controlNode(graphHandle, SINK_NODE, &updateParams);

 Exit:
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_execute(
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


