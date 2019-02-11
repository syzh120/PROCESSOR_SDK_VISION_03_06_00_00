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
 *  @file      integral_image_graph.c
 *
 *  @brief      This file defines the functions for integral image graph
 *  @version 0.0 (Jul 2013) : Base version.
 */

#define FIND_BEST_BLOCKDIM

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#pragma RESET_MISRA ("required")

#include "integral_image_graph_int.h"

#include "bam_image_integralimage_u8.h"
#include "edma_utils.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

static int32_t INTEGRAL_IMAGE_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel , &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc , "ti_dma_read_autoincrement" , BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT },
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_integralImage_u8Kernel   , &gBAM_TI_integralImage_u8HelperFunc         , "ti_integral_image_u8"      , BAM_TI_KERNELID_INTEGRAL_IMAGE_TI_U8  },
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel , &gBAM_TI_dmaReadAutoIncrementKernelExecFunc , "ti_dma_read_autoincrement" , BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT },
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_integralImage_u8Kernel   , &gBAM_TI_integralImage_u8KernelExecFunc   , "ti_integral_image_u8"      , BAM_TI_KERNELID_INTEGRAL_IMAGE_TI_U8  },
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.8 */
/* Name visibility is too wide */
/* Deviation is allowed because we use static keyword to make it local to the file */
static BAM_KernelDBdef gINTEGRAL_IMAGE_TI_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};
/*RESET_MISRA("8.7")  -> Reset rule 8.7 */


#define SOURCE_NODE                     0
#define SINK_NODE                       2
#define INTEGRAL_IMAGE_TI_NODE          1

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

int32_t INTEGRAL_IMAGE_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = INTEGRAL_IMAGE_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = INTEGRAL_IMAGE_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = INTEGRAL_IMAGE_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(INTEGRAL_IMAGE_TI_graphArgs) ;
    return 0;
}

int32_t INTEGRAL_IMAGE_TI_graphCreate(const BAM_GraphMem * graphMem, INTEGRAL_IMAGE_TI_graphCreateParams * createParams)
{

    BAM_CreateGraphParams graphCreateParams;
    int32_t status = IALG_EOK;

    /* initilize the sub-handles inside the main handle */
    INTEGRAL_IMAGE_TI_graphArgs * graphArgs = (INTEGRAL_IMAGE_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/
    BAM_NodeParams NODELIST[]=
    {
            {SOURCE_NODE            , BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT , NULL},
            {INTEGRAL_IMAGE_TI_NODE , BAM_TI_KERNELID_INTEGRAL_IMAGE_TI_U8  , NULL},
            {SINK_NODE              , BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT, NULL},
            {BAM_END_NODE_MARKER    , 0                                     , NULL                                         },
    };

    BAM_EdgeParams EDGELIST[]=
    {
            {{SOURCE_NODE           , BAM_SOURCE_NODE_PORT1                       }, {INTEGRAL_IMAGE_TI_NODE, BAM_INTEGRAL_IMAGE_TI_U8_INPUT_PORT_IN    }},
            {{SOURCE_NODE           , BAM_SOURCE_NODE_PORT2                       }, {INTEGRAL_IMAGE_TI_NODE, BAM_INTEGRAL_IMAGE_TI_U8_INPUT_PORT_ACC_H }},
            {{INTEGRAL_IMAGE_TI_NODE, BAM_INTEGRAL_IMAGE_TI_U8_OUTPUT_PORT_OUT1 }, {SINK_NODE             , BAM_SINK_NODE_PORT1                         }},
            {{INTEGRAL_IMAGE_TI_NODE, BAM_INTEGRAL_IMAGE_TI_U8_OUTPUT_PORT_OUT2 }, {SINK_NODE             , BAM_SINK_NODE_PORT2                         }},
            {{BAM_END_NODE_MARKER   , 0                                           }, {BAM_END_NODE_MARKER   , 0                                           }},
    };

    if (((uint32_t)createParams->imgFrameWidth * createParams->imgFrameHeight) >= 16777216U) {
        PRINTF("Graph construction failed!!! createParams->imgFrameWidth * createParams->imgFrameHeight >= 16777216");
        status= IALG_EFAIL;
        goto Exit;
    }

    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[INTEGRAL_IMAGE_TI_NODE].kernelArgs= &graphArgs->integralImagekernelArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    /*---------------------------------------------------------------*/
    /* Initialize the kernel Database that will be used by the graph */
    /*---------------------------------------------------------------*/
    BAM_initKernelDB(&gINTEGRAL_IMAGE_TI_BAM_kernelDBdef);

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gINTEGRAL_IMAGE_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = INTEGRAL_IMAGE_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = INTEGRAL_IMAGE_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = INTEGRAL_IMAGE_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
#ifdef FIND_BEST_BLOCKDIM
    graphCreateParams.optimizeBlockDim= 1U;
#else
    graphCreateParams.optimizeBlockDim= 0;
#endif

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphArgs->createParams                 = createParams;
    graphCreateParams.initKernelsArgsFunc   = &INTEGRAL_IMAGE_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /*-------------------------------------------------------------------------*/
    /* Initialize the structure blockDimParams that lists the processing block */
    /* dimensions as well as the step increment sizes used during the block    */
    /* dimension optimization if enabled                                       */
    /*-------------------------------------------------------------------------*/
    graphCreateParams.blockDimParams.blockWidth           = INTEGRAL_IMAGE_TI_BLK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight          = INTEGRAL_IMAGE_TI_BLK_HEIGHT;
    graphCreateParams.blockDimParams.blockWidthStep       = INTEGRAL_IMAGE_TI_BLK_WIDTH_STEP;
    graphCreateParams.blockDimParams.blockHeightStep      = INTEGRAL_IMAGE_TI_BLK_HEIGHT_STEP;
    graphCreateParams.blockDimParams.blockWidthDivisorOf  = createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightDivisorOf = createParams->imgFrameHeight;
    graphCreateParams.blockDimParams.blockWidthMax  = createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightMax = createParams->imgFrameHeight;

    /*-------------------------------------------------------------------------*/
    /* Creation of graph                                                       */
    /*-------------------------------------------------------------------------*/
    status = BAM_createGraph(&graphCreateParams, &graphHandle);

    createParams->blockWidth= graphCreateParams.blockDimParams.blockWidth;
    createParams->blockHeight= graphCreateParams.blockDimParams.blockHeight;

    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
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
                createParams->blockWidth,createParams->blockHeight);
    }
    else {
        if (status != BAM_S_SUCCESS)
        {
        PRINTF("Graph construction failed!!!");
        }
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
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t INTEGRAL_IMAGE_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
/* RESET_MISRA("16.7")  -> Reset rule 16.7  */
{

    int16_t blkWidthFinal  = 0;
    int16_t blkHeightFinal = 0;

    int32_t status = IALG_EOK;

    INTEGRAL_IMAGE_TI_graphArgs *graphArgs                         = (INTEGRAL_IMAGE_TI_graphArgs*)args;
    EDMA_UTILS_autoIncrement_initParam *dmaReadKernelArgs          = &(graphArgs->dmaReadKernelArgs);
    EDMA_UTILS_autoIncrement_initParam *dmaWriteKernelArgs         = &(graphArgs->dmaWriteKernelArgs);
    BAM_Image_integralImage_u8_Args *integralImagekernelArgs     = &(graphArgs->integralImagekernelArgs);

    blkWidthFinal  = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;


    if ((graphArgs->createParams->imgFrameWidth % blkWidthFinal) != 0)
    {
        status = IALG_EFAIL;
        goto Exit;
    }

    if ((graphArgs->createParams->imgFrameHeight % blkHeightFinal) != 0)
    {
        status = IALG_EFAIL;
        goto Exit;
    }

    /*--------------------------------------------------------------------------*/
    /*Params Update for DMA                                                     */
    /*--------------------------------------------------------------------------*/
    dmaReadKernelArgs->numInTransfers    = 2;
    dmaReadKernelArgs->transferType      = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[BAM_SOURCE_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth,              /*  roiWidth          */
            graphArgs->createParams->imgFrameHeight,             /*  roiHeight         */
            (uint16_t)blkWidthFinal,                            /*  blkWidth          */
            (uint16_t)blkHeightFinal,                           /*  blkHeight         */
            (uint16_t)blkWidthFinal,                            /*  extBlkIncrementX  */
            (uint16_t)blkHeightFinal,                           /*  extBlkIncrementY  */
            0u,                                        /*  intBlkIncrementX  */
            0u,                                        /*  intBlkIncrementY  */
            0u,                                        /*  roiOffset         */
            0u,                                        /*  blkOffset         */
            (uint8_t*)NULL,                                     /*  extMemPtr         */
            graphArgs->createParams->imgFrameWidth,              /*  extMemPtrStride   */
            (uint8_t*)NULL,                                     /*  interMemPtr       */
           (uint16_t)blkWidthFinal,                            /*  interMemPtrStride */
            0U                                         /*  dmaQueNo          */
    );

    assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[BAM_SOURCE_NODE_PORT2],
            graphArgs->createParams->imgFrameWidth * sizeof(int32_t), /*  roiWidth          */
            1u,                                         /*  roiHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),               /*  blkWidth          */
            1u,                                         /*  blkHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),               /*  extBlkIncrementX  */
            0u,                                         /*  extBlkIncrementY  */
            0u,                                         /*  intBlkIncrementX  */
            0u,                                         /*  intBlkIncrementY  */
            0u,                                         /*  roiOffset         */
            0u,                                         /*  blkOffset         */
            (uint8_t*)NULL,                                      /*  extMemPtr         */
            (uint16_t)(graphArgs->createParams->imgFrameWidth * sizeof(int32_t)), /*  extMemPtrStride   */
            (uint8_t*)NULL,                                      /*  interMemPtr       */
            (uint16_t)blkWidthFinal * sizeof(int32_t),               /*  interMemPtrStride */
            0                                          /*  dmaQueNo          */
    );


    dmaWriteKernelArgs->numOutTransfers  = 2;
    dmaWriteKernelArgs->transferType     = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth * sizeof(int32_t),  /*  roiWidth          */
            graphArgs->createParams->imgFrameHeight,               /*  roiHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  blkWidth          */
            (uint16_t)blkHeightFinal,                             /*  blkHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  extBlkIncrementX  */
            (uint16_t)blkHeightFinal,                             /*  extBlkIncrementY  */
            0,                                          /*  intBlkIncrementX  */
            0,                                          /*  intBlkIncrementY  */
            0,                                          /*  roiOffset         */
            0,                                          /*  blkOffset         */
            (uint8_t*)NULL,                                       /*  extMemPtr         */
            (uint16_t)(graphArgs->createParams->imgFrameWidth * sizeof(int32_t)),  /*  extMemPtrStride   */
            (uint8_t*)NULL,                                       /*  interMemPtr       */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  interMemPtrStride */
            1U                                           /*  dmaQueNo          */
    );

    assignDMAautoIncrementParams(&dmaWriteKernelArgs->transferProp[BAM_SINK_NODE_PORT2],
            graphArgs->createParams->imgFrameWidth * sizeof(int32_t),  /*  roiWidth          */
            1u,                                          /*  roiHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  blkWidth          */
            1u,                                          /*  blkHeight         */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  extBlkIncrementX  */
            0,                                          /*  extBlkIncrementY  */
            0,                                          /*  intBlkIncrementX  */
            0,                                          /*  intBlkIncrementY  */
            0,                                          /*  roiOffset         */
            0,                                          /*  blkOffset         */
            (uint8_t*)NULL,                                       /*  extMemPtr         */
            (uint16_t)graphArgs->createParams->imgFrameWidth * sizeof(int32_t),  /*  extMemPtrStride   */
            (uint8_t*)NULL,                                       /*  interMemPtr       */
            (uint16_t)blkWidthFinal * sizeof(int32_t),                /*  interMemPtrStride */
            1U                                           /*  dmaQueNo          */
    );

    /*--------------------------------------------------------------------------*/
    /*Params Update for IntegralImage                                           */
    /*--------------------------------------------------------------------------*/
    integralImagekernelArgs->blk_width       = blkWidthFinal;
    integralImagekernelArgs->blk_height      = blkHeightFinal;
    integralImagekernelArgs->input_stride    = blkWidthFinal;
    integralImagekernelArgs->num_hor_blocks  = graphArgs->createParams->imgFrameWidth / blkWidthFinal;

    Exit:
    return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/

int32_t INTEGRAL_IMAGE_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

    BAM_ProcessHints hints;
    int32_t status = BAM_S_SUCCESS;

    /*--------------------------------------------------------------------*/
    /* Specify which processing schedule is the best, unsupported for now */
    /*--------------------------------------------------------------------*/
    hints.priority= BAM_COMPUTE_FIRST;

    BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

    return status;

}

int32_t INTEGRAL_IMAGE_TI_dmaControl(const BAM_GraphMem *graphMem, const INTEGRAL_IMAGE_TI_Handle intAlgHandle, const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc)
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    uint8_t (*buf)[];

    const IVISION_BufPlanes * ivisionBufPlane= &inBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    buf= (uint8_t (*)[])ivisionBufPlane->buf;
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;
    autoIncCtlArgs.updateParams[0].extMemPtr= &(*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x];
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;
    autoIncCtlArgs.updateParams[1].extMemPtr= (uint8_t*)(void*)intAlgHandle->memRec[INTEGRAL_IMAGE_ACC_MEMREC].base;
    autoIncCtlArgs.updateParams[1].extMemPtrStride = ivisionBufPlane->width*sizeof(int32_t);

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }

    /* Initialize the control parameters for the SINK auto-increment DMA node */
    ivisionBufPlane= &outBufDesc->bufPlanes[0];
    buf= (uint8_t (*)[])ivisionBufPlane->buf;
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;
    autoIncCtlArgs.updateParams[0].extMemPtr= &(*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x];
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;
    autoIncCtlArgs.updateParams[1].extMemPtr= (uint8_t*)(void*)intAlgHandle->memRec[INTEGRAL_IMAGE_ACC_MEMREC].base;
    autoIncCtlArgs.updateParams[1].extMemPtrStride = ivisionBufPlane->width;

    /* Here we pass createParams->numLevels+1 as the index of the SINK node. We don't use SINK_NODE because it is set to 6, which is for 5 level of pyramid
     * and wouldn't work if the graph was reconfigured to fewer levels than 5.
     */
    status= BAM_controlNode(graphHandle, (uint8_t)SINK_NODE, &autoIncCtlArgs);

    Exit:
    return status;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

