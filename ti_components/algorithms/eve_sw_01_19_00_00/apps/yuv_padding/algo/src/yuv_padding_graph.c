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


/** @file yuv_padding_graph.c
 *
 *  @brief  This file implements an applet for yuv_padding
 *
 *  @author TI
 *
 *  @date   05 Mar 2014
 *
 *  Description
 *    This file contains code to perform yuv_padding
 */
/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "yuv_padding_graph_int.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "iyuv_padding_ti.h"

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
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride,
        uint8_t     dmaQueNo
);

/*#define FIND_BEST_BLOCKDIM*/

#ifndef NULL
#define NULL        (void *)0
#endif

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
          "ti_dma_read_autoincrement", BAM_TI_KERNELID_PADDING_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_yuvLeftRightPaddingKernel, &gBAM_TI_yuvLeftRightPaddingHelperFunc,
          "ti_image_yuv_padding", BAM_TI_KERNELID_YUV_PADDING},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_PADDING_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
          "ti_dma_read_autoincrement", BAM_TI_KERNELID_PADDING_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_yuvLeftRightPaddingKernel, &gBAM_TI_yuvLeftRightPaddingExecFunc,
          "ti_image_yuv_padding", BAM_TI_KERNELID_YUV_PADDING},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_PADDING_DMAWRITE_AUTOINCREMENT},
};

BAM_KernelDBdef gYUV_PADDING_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};

static int32_t YUV_PADDING_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0
#define YUV_PADDING_NODE    1
#define SINK_NODE   2

int32_t YUV_PADDING_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = YUV_PADDING_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = YUV_PADDING_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = YUV_PADDING_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(YUV_PADDING_TI_graphArgs) ;
    return 0;
}



int32_t YUV_PADDING_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        YUV_PADDING_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;
    uint16_t paddWidth;

    /* initilize the sub-handles inside the main handle */
    YUV_PADDING_TI_graphArgs * graphArgs = (YUV_PADDING_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*
     */

    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,               BAM_TI_KERNELID_PADDING_DMAREAD_AUTOINCREMENT,      NULL},
            {YUV_PADDING_NODE,      BAM_TI_KERNELID_YUV_PADDING,            NULL},
            {SINK_NODE,                 BAM_TI_KERNELID_PADDING_DMAWRITE_AUTOINCREMENT,     NULL},
            {BAM_END_NODE_MARKER,       0,                              NULL},\
    };

    NODELIST[SOURCE_NODE].kernelArgs          = &graphArgs->dmaReadKernelArgs;
    NODELIST[YUV_PADDING_NODE].kernelArgs = &graphArgs->kernelArgs;
    NODELIST[SINK_NODE].kernelArgs            = &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {YUV_PADDING_NODE,  BAM_YUV_PADDING_INPUT_PORT_LEFT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT2},             {YUV_PADDING_NODE,  BAM_YUV_PADDING_INPUT_PORT_RIGHT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT3},             {YUV_PADDING_NODE,  BAM_YUV_PADDING_CHROMA_INPUT_PORT_LEFT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT4},             {YUV_PADDING_NODE,  BAM_YUV_PADDING_CHROMA_INPUT_PORT_RIGHT}},\
            {{YUV_PADDING_NODE,     BAM_YUV_PADDING_OUTUT_PORT_LEFT},   {SINK_NODE, BAM_SINK_NODE_PORT1}},\
            {{YUV_PADDING_NODE,     BAM_YUV_PADDING_OUTUT_PORT_RIGHT},   {SINK_NODE, BAM_SINK_NODE_PORT2}},\
            {{YUV_PADDING_NODE,     BAM_YUV_PADDING_CHROMA_OUTUT_PORT_LEFT},   {SINK_NODE, BAM_SINK_NODE_PORT3}},\
            {{YUV_PADDING_NODE,     BAM_YUV_PADDING_CHROMA_OUTUT_PORT_RIGHT},   {SINK_NODE, BAM_SINK_NODE_PORT4}},\
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };


    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gYUV_PADDING_BAM_kernelDBdef);

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
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gYUV_PADDING_BAM_kernelDBdef;
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= YUV_PADDING_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= YUV_PADDING_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= YUV_PADDING_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc= 1U;
#ifdef FIND_BEST_BLOCKDIM
    graphCreateParams.optimizeBlockDim= 1U;
#else
    graphCreateParams.optimizeBlockDim= 0;
#endif
    graphArgs->createParams= createParams;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc= &YUV_PADDING_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */
    paddWidth = createParams->leftPadding > createParams->rightPadding ? createParams->leftPadding : createParams->rightPadding ;
    paddWidth = (((paddWidth + VCOP_SIMD_WIDTH)-1U)/VCOP_SIMD_WIDTH)*VCOP_SIMD_WIDTH;



    graphCreateParams.blockDimParams.blockWidth= paddWidth;
    graphCreateParams.blockDimParams.blockHeight= YUV_PADDING_BLOCK_HEIGHT;

    graphCreateParams.blockDimParams.blockWidthStep= 1;
    graphCreateParams.blockDimParams.blockHeightStep= 1;
    graphCreateParams.blockDimParams.blockWidthDivisorOf= 1;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= 1;
    graphCreateParams.blockDimParams.blockWidthMax= 1;
    graphCreateParams.blockDimParams.blockHeightMax= 1;

    status = BAM_createGraph(&graphCreateParams, &graphHandle);

    if(status != BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/

    Exit:
    if (status== BAM_E_INVALID_MEM_SIZE) {
        PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n", graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG) {
        PRINTF("Graph construction failed!!! Decrease the value of BLK_WIDTH or BLK_HEIGHT\n");
    } else if (status != BAM_S_SUCCESS)
    {
        PRINTF("Graph construction failed!!!\n");
    }
    else {
        /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
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

/* YUV_PADDING_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t YUV_PADDING_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */

    YUV_PADDING_TI_graphArgs *graphArgs= (YUV_PADDING_TI_graphArgs*)initKernelsArgs;

    uint16_t blkWidthFinal= 0;
    uint16_t blkHeightFinal= 0;

    int32_t status = BAM_S_SUCCESS;
    uint16_t leftPadding  = graphArgs->createParams->leftPadding ? graphArgs->createParams->leftPadding : 4;
    uint16_t rightPadding = graphArgs->createParams->rightPadding ? graphArgs->createParams->rightPadding : 4;

    blkWidthFinal  = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    graphArgs->kernelArgs.width        = blkWidthFinal;
    graphArgs->kernelArgs.height       = blkHeightFinal;
    graphArgs->kernelArgs.out_stride   = blkWidthFinal;

    graphArgs->dmaReadKernelArgs.numInTransfers                                           = 4;
    graphArgs->dmaReadKernelArgs.transferType                                             = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT1],
            (uint16_t    )1,                                                                          /* roiWidth */
            (uint16_t    )(blkHeightFinal*2U),                                                           /* roiHeight */
            (uint16_t    )1,                                                                          /* blkWidth */
            (uint16_t    )blkHeightFinal,                                                             /* blkHeight */
            (uint16_t    )1,                                                                          /* extBlkIncrementX */
            (uint16_t    )blkHeightFinal,                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )1,                                                                          /* interMemPtrStride */
            (uint8_t     )0);                                                                         /* dmaQueNo          */
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT2],
            (uint16_t    )1,                                                                          /* roiWidth */
            (uint16_t    )(blkHeightFinal*2U),                                                           /* roiHeight */
            (uint16_t    )1,                                                                          /* blkWidth */
            (uint16_t    )blkHeightFinal,                                                             /* blkHeight */
            (uint16_t    )1,                                                                          /* extBlkIncrementX */
            (uint16_t    )blkHeightFinal,                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )1,                                                                          /* interMemPtrStride */
            (uint8_t     )0);
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT3],
            (uint16_t    )2,                                                                          /* roiWidth */
            (uint16_t    )blkHeightFinal,                                                           /* roiHeight */
            (uint16_t    )2,                                                                          /* blkWidth */
            (uint16_t    )(blkHeightFinal/2U),                                                             /* blkHeight */
            (uint16_t    )2,                                                                          /* extBlkIncrementX */
            (uint16_t    )(blkHeightFinal/2U),                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )2,                                                                          /* interMemPtrStride */
            (uint8_t     )0);                                                                         /* dmaQueNo          */
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT4],
            (uint16_t    )2,                                                                          /* roiWidth */
            (uint16_t    )blkHeightFinal,                                                           /* roiHeight */
            (uint16_t    )2,                                                                          /* blkWidth */
            (uint16_t    )(blkHeightFinal/2U),                                                             /* blkHeight */
            (uint16_t    )2,                                                                          /* extBlkIncrementX */
            (uint16_t    )(blkHeightFinal/2U),                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )2,                                                                          /* interMemPtrStride */
            (uint8_t     )0);
    graphArgs->dmaWriteKernelArgs.numOutTransfers = 4;
    graphArgs->dmaWriteKernelArgs.transferType    = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            (uint16_t    )leftPadding,                                                                /* roiWidth */
            (uint16_t    )(blkHeightFinal*2U),                                                        /* roiHeight */
            (uint16_t    )leftPadding,                                                                /* blkWidth */
            (uint16_t    )blkHeightFinal,                                                             /* blkHeight */
            (uint16_t    )0,                                                                          /* extBlkIncrementX */
            (uint16_t    )blkHeightFinal,                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )blkWidthFinal,                                                              /* interMemPtrStride */
            (uint8_t     )0);                                                                         /* dmaQueNo          */
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT2],
            (uint16_t    )rightPadding,                                      /* roiWidth */
            (uint16_t    )(blkHeightFinal*2U),                                                        /* roiHeight */
            (uint16_t    )rightPadding,                                      /* blkWidth */
            (uint16_t    )blkHeightFinal,                                                             /* blkHeight */
            (uint16_t    )0,                                                                          /* extBlkIncrementX */
            (uint16_t    )blkHeightFinal,                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )blkWidthFinal,                                                              /* interMemPtrStride */
            (uint8_t     )0);
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT3],
            (uint16_t    )leftPadding,                                                                /* roiWidth */
            (uint16_t    )blkHeightFinal,                                                             /* roiHeight */
            (uint16_t    )leftPadding,                                                                /* blkWidth */
            (uint16_t    )(blkHeightFinal/2U),                                                        /* blkHeight */
            (uint16_t    )0,                                                                          /* extBlkIncrementX */
            (uint16_t    )(blkHeightFinal/2U),                                                        /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )blkWidthFinal,                                                              /* interMemPtrStride */
            (uint8_t     )0);                                                                         /* dmaQueNo          */
    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT4],
            (uint16_t    )rightPadding,                                      /* roiWidth */
            (uint16_t    )blkHeightFinal,                                                             /* roiHeight */
            (uint16_t    )rightPadding,                                      /* blkWidth */
            (uint16_t    )(blkHeightFinal/2U),                                                           /* blkHeight */
            (uint16_t    )0,                                                                          /* extBlkIncrementX */
            (uint16_t    )(blkHeightFinal/2U),                                                           /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )blkWidthFinal,                                                              /* interMemPtrStride */
            (uint8_t     )0);
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t YUV_PADDING_TI_execute(
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


int32_t YUV_PADDING_TI_dmaControl(const BAM_GraphMem *graphMem, uint16_t leftPadding, uint16_t rightPadding, const IVISION_BufPlanes ivisionBufPlane[], const IVISION_BufPlanes ivisionOutBufPlane[])
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    uint16_t procHeight;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    procHeight = ivisionBufPlane[0].frameROI.height;
    procHeight = ((((procHeight + YUV_PADDING_BLOCK_HEIGHT)-1U)/YUV_PADDING_BLOCK_HEIGHT)*YUV_PADDING_BLOCK_HEIGHT);

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    /* We do some adjustments to the coordinates of the upper left corner such that the DMA reads the ROI and its borders required for filtering */
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    autoIncCtlArgs.updateParams[0].extMemPtr= ((uint8_t *)ivisionBufPlane[0].buf + ((ivisionBufPlane[0].frameROI.topLeft.y) * ivisionBufPlane[0].width) +  (ivisionBufPlane[0].frameROI.topLeft.x));
    autoIncCtlArgs.updateParams[1].extMemPtr= ((uint8_t *)ivisionBufPlane[0].buf + ((ivisionBufPlane[0].frameROI.topLeft.y) * ivisionBufPlane[0].width) +  ((ivisionBufPlane[0].frameROI.topLeft.x + ivisionBufPlane[0].frameROI.width) - 1U));
    autoIncCtlArgs.updateParams[2].extMemPtr= ((uint8_t *)ivisionBufPlane[1].buf + ((ivisionBufPlane[1].frameROI.topLeft.y) * ivisionBufPlane[1].width) +  (ivisionBufPlane[1].frameROI.topLeft.x));
    autoIncCtlArgs.updateParams[3].extMemPtr= ((uint8_t *)ivisionBufPlane[1].buf + ((ivisionBufPlane[1].frameROI.topLeft.y) * ivisionBufPlane[1].width) +  ((ivisionBufPlane[1].frameROI.topLeft.x + ivisionBufPlane[1].frameROI.width) - 2U));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

    if(leftPadding == 0)
    {
        autoIncCtlArgs.updateParams[0].extMemPtr=autoIncCtlArgs.updateParams[1].extMemPtr;
        autoIncCtlArgs.updateParams[2].extMemPtr=autoIncCtlArgs.updateParams[3].extMemPtr;
    }
    if(rightPadding == 0)
    {
        autoIncCtlArgs.updateParams[1].extMemPtr=autoIncCtlArgs.updateParams[0].extMemPtr;
        autoIncCtlArgs.updateParams[3].extMemPtr=autoIncCtlArgs.updateParams[2].extMemPtr;
    }


    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane[0].width;
    autoIncCtlArgs.updateParams[0].roiWidth= 1;
    autoIncCtlArgs.updateParams[0].roiHeight= procHeight;

    autoIncCtlArgs.updateParams[1].extMemPtrStride = ivisionBufPlane[0].width;
    autoIncCtlArgs.updateParams[1].roiWidth= 1;
    autoIncCtlArgs.updateParams[1].roiHeight= procHeight;

    autoIncCtlArgs.updateParams[2].extMemPtrStride = ivisionBufPlane[1].width;
    autoIncCtlArgs.updateParams[2].roiWidth= 2;
    autoIncCtlArgs.updateParams[2].roiHeight= procHeight/2U;

    autoIncCtlArgs.updateParams[3].extMemPtrStride = ivisionBufPlane[1].width;
    autoIncCtlArgs.updateParams[3].roiWidth= 2;
    autoIncCtlArgs.updateParams[3].roiHeight= procHeight/2U;

    status= BAM_controlNode(graphHandle, (uint8_t)SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* In normal use case, we have all these flags _ONLY_GRAD_OUTPUT, _ONLY_HARRIS_OUTPUT, _ONLY_NMS_OUTPUT turned off so we initialize the control parameters for the SINK DMA node, which is one-shot EDMA */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    autoIncCtlArgs.updateParams[0].extMemPtr= ((uint8_t *)ivisionOutBufPlane[0].buf + (ivisionOutBufPlane[0].frameROI.topLeft.y * ivisionOutBufPlane[0].width) +  (ivisionOutBufPlane[0].frameROI.topLeft.x - (uint32_t)leftPadding));
    autoIncCtlArgs.updateParams[1].extMemPtr= ((uint8_t *)ivisionOutBufPlane[0].buf + (ivisionOutBufPlane[0].frameROI.topLeft.y * ivisionOutBufPlane[0].width) +  (ivisionOutBufPlane[0].frameROI.topLeft.x + ivisionOutBufPlane[0].frameROI.width));
    autoIncCtlArgs.updateParams[2].extMemPtr= ((uint8_t *)ivisionOutBufPlane[1].buf + (ivisionOutBufPlane[1].frameROI.topLeft.y * ivisionOutBufPlane[1].width) +  (ivisionOutBufPlane[1].frameROI.topLeft.x - (uint32_t)leftPadding));
    autoIncCtlArgs.updateParams[3].extMemPtr= ((uint8_t *)ivisionOutBufPlane[1].buf + (ivisionOutBufPlane[1].frameROI.topLeft.y * ivisionOutBufPlane[1].width) +  (ivisionOutBufPlane[1].frameROI.topLeft.x + ivisionOutBufPlane[1].frameROI.width));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

    if(leftPadding == 0)
    {
        autoIncCtlArgs.updateParams[0].extMemPtr=autoIncCtlArgs.updateParams[1].extMemPtr;
        autoIncCtlArgs.updateParams[2].extMemPtr=autoIncCtlArgs.updateParams[3].extMemPtr;
        leftPadding = 4U;
    }
    if(rightPadding == 0)
    {
        autoIncCtlArgs.updateParams[1].extMemPtr=autoIncCtlArgs.updateParams[0].extMemPtr;
        autoIncCtlArgs.updateParams[3].extMemPtr=autoIncCtlArgs.updateParams[2].extMemPtr;
        rightPadding = 4U;
    }

    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionOutBufPlane[0].width;
    autoIncCtlArgs.updateParams[0].roiWidth=  leftPadding;
    autoIncCtlArgs.updateParams[0].roiHeight=  procHeight;

    autoIncCtlArgs.updateParams[1].extMemPtrStride = ivisionOutBufPlane[0].width;
    autoIncCtlArgs.updateParams[1].roiWidth=  rightPadding;
    autoIncCtlArgs.updateParams[1].roiHeight=  procHeight;

    autoIncCtlArgs.updateParams[2].extMemPtrStride = ivisionOutBufPlane[1].width;
    autoIncCtlArgs.updateParams[2].roiWidth=  leftPadding;
    autoIncCtlArgs.updateParams[2].roiHeight=  procHeight/2U;

    autoIncCtlArgs.updateParams[3].extMemPtrStride = ivisionOutBufPlane[1].width;
    autoIncCtlArgs.updateParams[3].roiWidth=  rightPadding;
    autoIncCtlArgs.updateParams[3].roiHeight=  procHeight/2U;

    status= BAM_controlNode(graphHandle, (uint8_t)SINK_NODE, &autoIncCtlArgs);

 Exit:
    return status;
}


