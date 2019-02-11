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


/** @file imagePyramid_u8_graph.c
 *
 *  @brief  This file implements an applet for image pyramid
 *
 *  @author TI
 *
 *  @date   19 Dec 2013
 *
 *  Description
 *    This file contains code to perform image pyramid on 8-bit grayscale image
 *    Contains implementation of IMAGE_PYRAMID_U8_TI_graphCreate() and IMAGE_PYRAMID_U8_TI_execute()
 *    at the frame level.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#pragma RESET_MISRA ("required")

#include "imagePyramid_u8_graph_int.h"

#include "bam_blockAverage2x2.h"
#include "bam_natcBlockAverage2x2.h"

#include "bam_gauss5x5Pyramid_8.h"
#include "bam_natcGauss5x5Pyramid_8.h"

#include "edma_utils.h"

#include "iImagePyramid_u8_ti.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

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

#define FIND_BEST_BLOCKDIM

#ifndef NULL
#define NULL        (void *)0
#endif

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
          "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_blockAverage2x2Kernel, &gBAM_TI_blockAverage2x2HelperFunc,
          "ti_image_blockAverage2x2", BAM_TI_KERNELID_BLOCK_AVERAGE2x2},
        { &gBAM_TI_gauss5x5PyramidKernel, &gBAM_TI_gauss5x5PyramidHelperFunc,
          "ti_image_gauss5x5Pyramid", BAM_TI_KERNELID_GAUSS5x5_PYRAMID},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcBlockAverage2x2Kernel, &gBAM_TI_natcBlockAverage2x2HelperFunc,
          "ti_image_natcBlockAverage2x2", BAM_TI_KERNELID_NATCBLOCK_AVERAGE2x2 },
        { &gBAM_TI_natcGauss5x5PyramidKernel, &gBAM_TI_natcGauss5x5PyramidHelperFunc,
          "ti_image_natcGauss5x5Pyramid", BAM_TI_KERNELID_NATCGAUSS5x5_PYRAMID},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
          "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_blockAverage2x2Kernel, &gBAM_TI_blockAverage2x2ExecFunc,
          "ti_image_blockAverage2x2", BAM_TI_KERNELID_BLOCK_AVERAGE2x2},
        { &gBAM_TI_gauss5x5PyramidKernel, &gBAM_TI_gauss5x5PyramidExecFunc,
           "ti_image_gauss5x5Pyramid", BAM_TI_KERNELID_GAUSS5x5_PYRAMID},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcBlockAverage2x2Kernel, &gBAM_TI_natcBlockAverage2x2ExecFunc,
          "ti_image_natcBlockAverage2x2", BAM_TI_KERNELID_NATCBLOCK_AVERAGE2x2 },
        { &gBAM_TI_natcGauss5x5PyramidKernel, &gBAM_TI_natcGauss5x5PyramidExecFunc,
          "ti_image_natcGauss5x5Pyramid", BAM_TI_KERNELID_NATCGAUSS5x5_PYRAMID},
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.7 */
/* Name visibility is too wide */
/* Deviation is allowed because we use static keyword to make it local to the file */
static BAM_KernelDBdef gIMAGE_PYRAMID_U8_TI_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};
/*RESET_MISRA("8.7")  -> Reset rule 8.7*/

static int32_t IMAGE_PYRAMID_U8_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0
#define DS_NODE1    1
#define DS_NODE2    2
#define DS_NODE3    3
#define DS_NODE4    4
#define DS_NODE5    5
#define SINK_NODE   6

int32_t IMAGE_PYRAMID_U8_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = IMAGE_PYRAMID_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = IMAGE_PYRAMID_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = IMAGE_PYRAMID_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(IMAGE_PYRAMID_U8_TI_graphArgs) ;
    return 0;
}



int32_t IMAGE_PYRAMID_U8_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        IMAGE_PYRAMID_U8_TI_graphCreateParams * createParams)
{
    uint16_t i;
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    IMAGE_PYRAMID_U8_TI_graphArgs * graphArgs = (IMAGE_PYRAMID_U8_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /* In the NODELISt we don't specify the kernel ID yet as it depends on the type of filter
     * being 2x2 average filter or Gaussian.
     */

    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,   BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT ,      NULL},
            {DS_NODE1,      0                                     ,      NULL},
            {DS_NODE2,      0                                     ,      NULL},
            {DS_NODE3,      0                                     ,      NULL},
            {DS_NODE4,      0                                     ,      NULL},
            {DS_NODE5,      0                                     ,      NULL},
            {SINK_NODE,     BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,      NULL},
            {BAM_END_NODE_MARKER,       0,                               NULL},\
    };

    /* The EDGE list actually is the same for 2x2 average filter of Gaussian even if BAM_BLOCKAVERAGE2x2_INPUT_PORT
     * and BAM_BLOCKAVERAGE2x2_OUTPUT_PORT are used for the gaussian case since BAM_GAUSS5x5PYRAMID_INPUT_PORT= BAM_BLOCKAVERAGE2x2_INPUT_PORT= 0
     * and BAM_GAUSS5x5PYRAMID_OUTPUT_PORT= 0 .
     */
    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {DS_NODE1,  BAM_BLOCKAVERAGE2x2_INPUT_PORT}},\
            {{DS_NODE1,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT1}},\
            {{DS_NODE1,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {DS_NODE2,  BAM_BLOCKAVERAGE2x2_INPUT_PORT}},\
            {{DS_NODE2,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT2}},\
            {{DS_NODE2,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {DS_NODE3,  BAM_BLOCKAVERAGE2x2_INPUT_PORT}},\
            {{DS_NODE3,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT3}},\
            {{DS_NODE3,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {DS_NODE4,  BAM_BLOCKAVERAGE2x2_INPUT_PORT}},\
            {{DS_NODE4,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT4}},\
            {{DS_NODE4,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {DS_NODE5,  BAM_BLOCKAVERAGE2x2_INPUT_PORT}},\
            {{DS_NODE5,     BAM_BLOCKAVERAGE2x2_OUTPUT_PORT},   {SINK_NODE, BAM_SINK_NODE_PORT5}},\
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };


    assert(createParams->numLevels <= IMGPYRAMID_MAX_NUM_LEVELS);

    if (createParams->filterType== IMAGE_PYRAMID_U8_TI_2x2_AVERAGE) {
        NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
        NODELIST[DS_NODE1].kernelArgs= &graphArgs->blockAverArgs.dsKernelArgs1;
        NODELIST[DS_NODE1].kernelId= BAM_TI_KERNELID_BLOCK_AVERAGE2x2;
        NODELIST[DS_NODE2].kernelArgs= &graphArgs->blockAverArgs.dsKernelArgs2;
        NODELIST[DS_NODE2].kernelId= BAM_TI_KERNELID_BLOCK_AVERAGE2x2;
        NODELIST[DS_NODE3].kernelArgs= &graphArgs->blockAverArgs.dsKernelArgs3;
        NODELIST[DS_NODE3].kernelId= BAM_TI_KERNELID_BLOCK_AVERAGE2x2;
        NODELIST[DS_NODE4].kernelArgs= &graphArgs->blockAverArgs.dsKernelArgs4;
        NODELIST[DS_NODE4].kernelId= BAM_TI_KERNELID_BLOCK_AVERAGE2x2;
        NODELIST[DS_NODE5].kernelArgs= &graphArgs->blockAverArgs.dsKernelArgs5;
        NODELIST[DS_NODE5].kernelId= BAM_TI_KERNELID_BLOCK_AVERAGE2x2;
        NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;
    }
    else if (createParams->filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {
        NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
        NODELIST[DS_NODE1].kernelArgs= &graphArgs->gauss5x5Args.dsKernelArgs1;
        NODELIST[DS_NODE1].kernelId= BAM_TI_KERNELID_GAUSS5x5_PYRAMID;
        NODELIST[DS_NODE2].kernelArgs= &graphArgs->gauss5x5Args.dsKernelArgs2;
        NODELIST[DS_NODE2].kernelId= BAM_TI_KERNELID_GAUSS5x5_PYRAMID;
        NODELIST[DS_NODE3].kernelArgs= &graphArgs->gauss5x5Args.dsKernelArgs3;
        NODELIST[DS_NODE3].kernelId= BAM_TI_KERNELID_GAUSS5x5_PYRAMID;
        NODELIST[DS_NODE4].kernelArgs= &graphArgs->gauss5x5Args.dsKernelArgs4;
        NODELIST[DS_NODE4].kernelId= BAM_TI_KERNELID_GAUSS5x5_PYRAMID;
        NODELIST[DS_NODE5].kernelArgs= &graphArgs->gauss5x5Args.dsKernelArgs5;
        NODELIST[DS_NODE5].kernelId= BAM_TI_KERNELID_GAUSS5x5_PYRAMID;
        NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;
    }
    else {
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* Both the node and edge lists in the present source code were designed for a number of pyramid levels equal to MAX_NUM_LEVELS
     * If the function's parameter numLevels has a smaller number of levels, then the graph description is updated.
     */
    if (createParams->numLevels < IMGPYRAMID_MAX_NUM_LEVELS) {
        NODELIST[createParams->numLevels+1]= NODELIST[SINK_NODE]; /* Move the sink node right after the downsample node for the last level */
        NODELIST[createParams->numLevels+1].nodeIndex= createParams->numLevels+1; /* this is the new sink node index */
        NODELIST[createParams->numLevels+2]= NODELIST[IMGPYRAMID_MAX_NUM_LEVELS+2U]; /* append BAM_END_NODE_MARKER at the end of the node list */
        EDGELIST[1 + ((createParams->numLevels-1)*2) + 1]= EDGELIST[2U*IMGPYRAMID_MAX_NUM_LEVELS];
        for (i=0;i<(uint16_t)((uint16_t)2u*(uint16_t)createParams->numLevels);i++) {
            if (EDGELIST[i].downStreamNode.id== SINK_NODE) {
                EDGELIST[i].downStreamNode.id= createParams->numLevels+1;
            }
        }
    }


    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gIMAGE_PYRAMID_U8_TI_BAM_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gIMAGE_PYRAMID_U8_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= IMAGE_PYRAMID_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= IMAGE_PYRAMID_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= IMAGE_PYRAMID_GRAPH_CONTEXT_SIZE;
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
    graphCreateParams.initKernelsArgsFunc= &IMAGE_PYRAMID_U8_TI_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */
    graphCreateParams.blockDimParams.blockWidth= IMAGE_PYRAMID_BLK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight= IMAGE_PYRAMID_BLK_HEIGHT;

    graphCreateParams.blockDimParams.blockWidthStep= IMAGE_PYRAMID_BLK_WIDTH_STEP;
    graphCreateParams.blockDimParams.blockHeightStep= IMAGE_PYRAMID_BLK_HEIGHT_STEP;

    graphCreateParams.blockDimParams.blockWidthDivisorOf= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= createParams->imgFrameHeight;

    graphCreateParams.blockDimParams.blockWidthMax= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightMax= createParams->imgFrameHeight;

    status = BAM_createGraph(&graphCreateParams, &graphHandle);

    createParams->outputBlockWidth= graphCreateParams.blockDimParams.blockWidth;
    createParams->outputBlockHeight= graphCreateParams.blockDimParams.blockHeight;

    if(status != BAM_S_SUCCESS) {
        goto Exit;
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

/* IMAGE_PYRAMID_U8_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
static int32_t IMAGE_PYRAMID_U8_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {

    uint16_t width[IMGPYRAMID_MAX_NUM_LEVELS];
    uint16_t height[IMGPYRAMID_MAX_NUM_LEVELS];
    uint16_t pitch[IMGPYRAMID_MAX_NUM_LEVELS];
    uint16_t totalHeight[IMGPYRAMID_MAX_NUM_LEVELS];
    uint16_t offset[IMGPYRAMID_MAX_NUM_LEVELS];
    uint16_t stride1, stride2, stride3, stride4, stride5;

    IMAGE_PYRAMID_U8_TI_graphArgs *graphArgs= (IMAGE_PYRAMID_U8_TI_graphArgs*)initKernelsArgs;

    int16_t blkWidthFinal= 0;
    int16_t blkHeightFinal= 0;
    uint16_t extraBorders= 0;

    uint16_t i= 0;
    uint16_t notEven=0;

    int32_t status = BAM_S_SUCCESS;

    stride1= 0;stride2= 0;stride3= 0;stride4= 0;stride5= 0;
    for (i=0; i < IMGPYRAMID_MAX_NUM_LEVELS; i++) {
        offset[i]= 0;
    }

    /* If at any level, the block width is not multiple of 2, readjust it by multiplying it by 2*/
    notEven= 0;
    for (i= 0; i< graphArgs->createParams->numLevels;i ++) {
        if ((((uint32_t)blockDimParams->blockWidth >> i) & 1U)) {
            notEven= 1u;
            break;
        }
    }

    while (notEven) {
        blockDimParams->blockWidth <<=1;

        notEven= 0;
        for (i= 0; i< graphArgs->createParams->numLevels;i ++) {
            if ((((uint32_t)blockDimParams->blockWidth >> i) & 1U)) {
                notEven= 1u;
                break;
            }
        }
    }

    /* If at any level, the block height is not multiple of 2, readjust it by multiplying it by 2*/

    notEven= 0;
    for (i= 0; i< graphArgs->createParams->numLevels;i ++) {
        if ((((uint32_t)blockDimParams->blockHeight >> i) & 1U)) {
            notEven= 1u;
        }
    }

    while (notEven) {
        blockDimParams->blockHeight <<=1;

        notEven= 0;
        for (i= 0; i< graphArgs->createParams->numLevels;i ++) {
            if ((((uint32_t)blockDimParams->blockHeight >> i) & 1U)) {
                notEven= 1u;
            }
        }
    }

    blkWidthFinal = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    if (graphArgs->createParams->imgFrameWidth % blkWidthFinal) {
        PRINTF("Block width found does not divide the image width: please make sure that the image width of each pyramid level is multiple of 2\n");
        status= BAM_E_FAIL;
        goto Exit;
    }

    if (graphArgs->createParams->imgFrameHeight % blkHeightFinal) {
        PRINTF("Block height found does not divide the image height: please make sure that the image height of each pyramid level is multiple of 2\n");
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* In case 5x5 gaussian filter, need to calculate extra borders and add it to the block dimensions */
    if (graphArgs->createParams->filterType== IMAGE_PYRAMID_U8_TI_2x2_AVERAGE) {

        /* 2x2 averaging is not implemented by a FIR filter so there is no extra borders to be added */
        extraBorders= 0;
        for (i=0;i<graphArgs->createParams->numLevels; i++) {
            offset[i]= 0;
            }

        graphArgs->blockAverArgs.dsKernelArgs1.width= (uint16_t)ALIGN_2SIMD((uint32_t)blkWidthFinal); /* blkWidthFinal should alreayd be multiple of 16 so normally not necessary */
        graphArgs->blockAverArgs.dsKernelArgs1.height= blkHeightFinal;
        graphArgs->blockAverArgs.dsKernelArgs1.in_stride= blkWidthFinal;
        stride1= graphArgs->blockAverArgs.dsKernelArgs1.out_stride= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs1.width>>1u); /* need to align to multiple of 16 because this output is fed to the 2nd downsample node which input block width must be multiple of 16*/

        graphArgs->blockAverArgs.dsKernelArgs2.width= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs1.width>>1u);
        graphArgs->blockAverArgs.dsKernelArgs2.height= graphArgs->blockAverArgs.dsKernelArgs1.height>>1;
        graphArgs->blockAverArgs.dsKernelArgs2.in_stride= graphArgs->blockAverArgs.dsKernelArgs2.width;
        stride2= graphArgs->blockAverArgs.dsKernelArgs2.out_stride= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs2.width>>1u); /* need to align to multiple of 16 because this output is fed to the 3rd downsample node which input block width must be multiple of 16*/

        graphArgs->blockAverArgs.dsKernelArgs3.width= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs2.width>>1u);
        graphArgs->blockAverArgs.dsKernelArgs3.height= graphArgs->blockAverArgs.dsKernelArgs2.height>>1;
        graphArgs->blockAverArgs.dsKernelArgs3.in_stride= graphArgs->blockAverArgs.dsKernelArgs3.width;
        stride3= graphArgs->blockAverArgs.dsKernelArgs3.out_stride= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs3.width>>1u);

        graphArgs->blockAverArgs.dsKernelArgs4.width= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs3.width>>1u);
        graphArgs->blockAverArgs.dsKernelArgs4.height= graphArgs->blockAverArgs.dsKernelArgs3.height>>1;
        graphArgs->blockAverArgs.dsKernelArgs4.in_stride= graphArgs->blockAverArgs.dsKernelArgs4.width;
        stride4= graphArgs->blockAverArgs.dsKernelArgs4.out_stride= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs4.width>>1u);

        graphArgs->blockAverArgs.dsKernelArgs5.width= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs4.width>>1u);
        graphArgs->blockAverArgs.dsKernelArgs5.height= graphArgs->blockAverArgs.dsKernelArgs4.height>>1;
        graphArgs->blockAverArgs.dsKernelArgs5.in_stride= graphArgs->blockAverArgs.dsKernelArgs5.width;
        stride5= graphArgs->blockAverArgs.dsKernelArgs5.out_stride= (uint16_t)ALIGN_2SIMD(graphArgs->blockAverArgs.dsKernelArgs5.width>>1u);
    }
    else {
        if (graphArgs->createParams->filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {
            /* calculate extra borders which is made of 4 pixels per level, which are scaled back to the original image */
            extraBorders= 0;
            for (i=0;i<graphArgs->createParams->numLevels;i++){
                extraBorders+= (uint16_t)((uint16_t)((uint16_t)1U<<(uint16_t)i)*(uint16_t)4U);
            }

            width[0]= ((uint16_t)blkWidthFinal + (extraBorders - 4u));
            height[0]= ((uint16_t)blkHeightFinal + (extraBorders - 4u));
            pitch[0]= ((uint16_t)blkWidthFinal + (extraBorders - 4u))/2u;
            totalHeight[0]= ((uint16_t)blkHeightFinal + (extraBorders - 4u))/2u;
            offset[0]= (uint16_t)((((uint32_t)pitch[0] - ((uint32_t)blkWidthFinal>>1U))/2u) + ((((uint32_t)totalHeight[0] - ((uint32_t)blkHeightFinal>>1U))/2u)*ALIGN_2SIMD((uint32_t)pitch[0])));

            for (i=1u;i<(uint16_t)graphArgs->createParams->numLevels; i++) {
                width[i]= (width[i-1u]/2u) - 4u;
                height[i]= (height[i-1u]/2u) - 4u;
                pitch[i]= (pitch[i-1u] - 4u)/2u;
                totalHeight[i]= (totalHeight[i-1u] - 4u)/2u;
                offset[i]= (uint16_t)((((uint32_t)pitch[i] - ((uint32_t)blkWidthFinal>>(i+1u)))/2u) + ((((uint32_t)totalHeight[i] - ((uint32_t)blkHeightFinal>>(i+1u)))/2u)*ALIGN_2SIMD((uint32_t)pitch[i])));
            }

            graphArgs->gauss5x5Args.dsKernelArgs1.width= ALIGN_2SIMD(width[0]); /* blkWidthFinal should alreayd be multiple of 16 so normally alignment not necessary */
            graphArgs->gauss5x5Args.dsKernelArgs1.height= height[0];
            graphArgs->gauss5x5Args.dsKernelArgs1.in_stride= (uint16_t)blkWidthFinal + (uint16_t)extraBorders;
            stride1= graphArgs->gauss5x5Args.dsKernelArgs1.out_stride= (uint16_t)(ALIGN_2SIMD(pitch[0])); /* need to align to multiple of 16 because this output is fed to the 2nd downsample node which input block width must be multiple of 16*/

            graphArgs->gauss5x5Args.dsKernelArgs2.width= ALIGN_2SIMD(width[1]);
            graphArgs->gauss5x5Args.dsKernelArgs2.height= height[1];
            graphArgs->gauss5x5Args.dsKernelArgs2.in_stride= stride1;
            stride2= graphArgs->gauss5x5Args.dsKernelArgs2.out_stride= (uint16_t)(ALIGN_2SIMD(pitch[1])); /* need to align to multiple of 16 because this output is fed to the 3rd downsample node which input block width must be multiple of 16*/

            graphArgs->gauss5x5Args.dsKernelArgs3.width= ALIGN_2SIMD(width[2]);
            graphArgs->gauss5x5Args.dsKernelArgs3.height= height[2];
            graphArgs->gauss5x5Args.dsKernelArgs3.in_stride= stride2;
            stride3= graphArgs->gauss5x5Args.dsKernelArgs3.out_stride= (uint16_t)(ALIGN_2SIMD(pitch[2]));

            graphArgs->gauss5x5Args.dsKernelArgs4.width= ALIGN_2SIMD(width[3]);
            graphArgs->gauss5x5Args.dsKernelArgs4.height= height[3];
            graphArgs->gauss5x5Args.dsKernelArgs4.in_stride= stride3;
            stride4= graphArgs->gauss5x5Args.dsKernelArgs4.out_stride= (uint16_t)(ALIGN_2SIMD(pitch[3]));

            graphArgs->gauss5x5Args.dsKernelArgs5.width=(uint16_t)( ALIGN_2SIMD(width[4]));
            graphArgs->gauss5x5Args.dsKernelArgs5.height= height[4];
            graphArgs->gauss5x5Args.dsKernelArgs5.in_stride= stride4;
            stride5= graphArgs->gauss5x5Args.dsKernelArgs5.out_stride= (uint16_t)(ALIGN_2SIMD(pitch[4]));
        }
    }

    graphArgs->createParams->activeImgWidth= graphArgs->createParams->imgFrameWidth + extraBorders;
    graphArgs->createParams->activeImgHeight= graphArgs->createParams->imgFrameHeight + extraBorders;

    graphArgs->dmaReadKernelArgs.numInTransfers                                           = 1;
    graphArgs->dmaReadKernelArgs.transferType                                             = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(
            &graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth + extraBorders, /* roiWidth */
            graphArgs->createParams->imgFrameHeight + extraBorders, /* roiHeight */
            (uint16_t)blkWidthFinal + extraBorders,                 /* blkWidth */
            (uint16_t)blkHeightFinal + extraBorders,                /* blkHeight */
            (uint16_t)blkWidthFinal,                                /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                                                   /* extBlkIncrementY */
            0,                                                                          /* intBlkIncrementX */
            0,                                                                          /* intBlkIncrementY */
            0,                                                                          /* roiOffset        */
            0,                                                                          /* blkOffset        */
            NULL,                                                                       /* extMemPtr        */
            0,                                                                          /* extMemPtrStride  */
            NULL,                                                                       /* interMemPtr      */
            (uint16_t)blkWidthFinal + extraBorders,                         /* interMemPtrStride */
            0);                                                                         /* dmaQueNo          */

    graphArgs->dmaWriteKernelArgs.numOutTransfers = graphArgs->createParams->numLevels;
    graphArgs->dmaWriteKernelArgs.transferType    = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(
            &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth>>1u, /* roiWidth */
            graphArgs->createParams->imgFrameHeight>>1u, /* roiHeight */
            (uint16_t)blkWidthFinal>>1u,                         /* blkWidth */
            (uint16_t)blkHeightFinal>>1u,                                           /* blkHeight */
            (uint16_t)blkWidthFinal>>1u,                                              /* extBlkIncrementX */
            (uint16_t)blkHeightFinal>>1u,                                                             /* extBlkIncrementY */
            0,                                                                          /* intBlkIncrementX */
            0,                                                                          /* intBlkIncrementY */
            0,                                                                          /* roiOffset        */
            offset[0],                                                                  /* blkOffset        */
            NULL,                                                                       /* extMemPtr        */
            0,                                                                          /* extMemPtrStride  */
            NULL,                                                                       /* interMemPtr      */
            stride1,                                                                    /* interMemPtrStride */
            1U);                                                                         /* dmaQueNo          */

    assignDMAautoIncrementParams(
               &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT2],
               graphArgs->createParams->imgFrameWidth>>2u, /* roiWidth */
               graphArgs->createParams->imgFrameHeight>>2u, /* roiHeight */
               (uint16_t)blkWidthFinal>>2u,                         /* blkWidth */
               (uint16_t)blkHeightFinal>>2u,                                           /* blkHeight */
               (uint16_t)blkWidthFinal>>2u,                                              /* extBlkIncrementX */
               (uint16_t)blkHeightFinal>>2u,                                                             /* extBlkIncrementY */
               0,                                                                          /* intBlkIncrementX */
               0,                                                                          /* intBlkIncrementY */
               0,                                                                          /* roiOffset        */
               offset[1],                                                                  /* blkOffset        */
               NULL,                                                                       /* extMemPtr        */
               0,                                                                          /* extMemPtrStride  */
               NULL,                                                                       /* interMemPtr      */
               stride2,                         /* interMemPtrStride */
               0U);                                                                         /* dmaQueNo          */

    assignDMAautoIncrementParams(
                  &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT3],
                  graphArgs->createParams->imgFrameWidth>>3u, /* roiWidth */
                  graphArgs->createParams->imgFrameHeight>>3u, /* roiHeight */
                  (uint16_t)blkWidthFinal>>3u,                         /* blkWidth */
                  (uint16_t)blkHeightFinal>>3u,                                           /* blkHeight */
                  (uint16_t)blkWidthFinal>>3u,                                              /* extBlkIncrementX */
                  (uint16_t)blkHeightFinal>>3u,                                                             /* extBlkIncrementY */
                  0,                                                                          /* intBlkIncrementX */
                  0,                                                                          /* intBlkIncrementY */
                  0,                                                                          /* roiOffset        */
                  offset[2],                                                                  /* blkOffset        */
                  NULL,                                                                       /* extMemPtr        */
                  0,                                                                          /* extMemPtrStride  */
                  NULL,                                                                       /* interMemPtr      */
                  stride3,                         /* interMemPtrStride */
                  1U);                                                                         /* dmaQueNo          */

    assignDMAautoIncrementParams(
                      &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT4],
                      graphArgs->createParams->imgFrameWidth>>4u, /* roiWidth */
                      graphArgs->createParams->imgFrameHeight>>4u, /* roiHeight */
                      (uint16_t)blkWidthFinal>>4u,                         /* blkWidth */
                      (uint16_t)blkHeightFinal>>4u,                                           /* blkHeight */
                      (uint16_t)blkWidthFinal>>4u,                                              /* extBlkIncrementX */
                      (uint16_t)blkHeightFinal>>4u,                                                             /* extBlkIncrementY */
                      0,                                                                          /* intBlkIncrementX */
                      0,                                                                          /* intBlkIncrementY */
                      0,                                                                          /* roiOffset        */
                      offset[3],                                                                  /* blkOffset        */
                      NULL,                                                                       /* extMemPtr        */
                      0,                                                                          /* extMemPtrStride  */
                      NULL,                                                                       /* interMemPtr      */
                      stride4,                         /* interMemPtrStride */
                      0U);                                                                         /* dmaQueNo          */

    assignDMAautoIncrementParams(
                       &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT5],
                       graphArgs->createParams->imgFrameWidth>>5u,     /* roiWidth */
                       graphArgs->createParams->imgFrameHeight>>5u,    /* roiHeight */
                       (uint16_t)blkWidthFinal>>5u,                        /* blkWidth */
                       (uint16_t)blkHeightFinal>>5u,                       /* blkHeight */
                       (uint16_t)blkWidthFinal>>5u,                        /* extBlkIncrementX */
                       (uint16_t)blkHeightFinal>>5u,                       /* extBlkIncrementY */
                       0,                                       /* intBlkIncrementX */
                       0,                                       /* intBlkIncrementY */
                       0,                                       /* roiOffset        */
                       offset[4],                               /* blkOffset        */
                       NULL,                                    /* extMemPtr        */
                       0,                                       /* extMemPtrStride  */
                       NULL,                                    /* interMemPtr      */
                       stride5,                                 /* interMemPtrStride */
                       1U);                                      /* dmaQueNo          */

    Exit:
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t IMAGE_PYRAMID_U8_TI_execute(
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

int32_t IMAGE_PYRAMID_U8_TI_dmaControl(const BAM_GraphMem *graphMem, const IMAGE_PYRAMID_U8_TI_Handle intAlgHandle, IVISION_BufDesc *inBufDesc, IVISION_BufDesc *outBufDesc)
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    uint8_t (*buf)[];
    IVISION_BufPlanes (*bufPlane)[];
    IVISION_BufPlanes * ivisionBufPlane= &inBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;
    uint32_t extraBorders= 0;
    uint32_t i=0;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    buf= (uint8_t (*)[])ivisionBufPlane->buf;

    /* In case gaussian filter is used, we rewind topLeft.x and topLeft.y by the exact border width and height required for a 5x5 gaussian
     * This is to ensure that the pointer for EDMA read points exactly to the upper left corner of the region composed
     * by the ROI augmented by the filtering border.
     * */
    if (intAlgHandle->filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {

        extraBorders= 0;
        for (i=0;i<intAlgHandle->numLevels;i++){
            extraBorders+= (((uint32_t)1u<<i)*(uint32_t)4u);
        }

        autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[((ivisionBufPlane->frameROI.topLeft.y - (extraBorders/2u)) * ivisionBufPlane->width) + (ivisionBufPlane->frameROI.topLeft.x - (extraBorders/2u))]);
        autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

    }
    else {
        autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x]);
        autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;
    }

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }

    /* Initialize the control parameters for the SINK auto-increment DMA node */
    ivisionBufPlane= &outBufDesc->bufPlanes[0];
    bufPlane = (IVISION_BufPlanes (*)[])(void*)ivisionBufPlane;

    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    for (i=0;i<intAlgHandle->numLevels;i++){
        buf= (uint8_t (*)[])(*bufPlane)[i].buf;
        autoIncCtlArgs.updateParams[i].extMemPtr= &((*buf)[((*bufPlane)[i].frameROI.topLeft.y * (*bufPlane)[i].width) + (*bufPlane)[i].frameROI.topLeft.x]);
        autoIncCtlArgs.updateParams[i].extMemPtrStride = (*bufPlane)[i].width;
    }

    /* Here we pass createParams->numLevels+1 as the index of the SINK node. We don't use SINK_NODE because it is set to 6, which is for 5 level of pyramid
     * and wouldn't work if the graph was reconfigured to fewer levels than 5.
     */
    status= BAM_controlNode(graphHandle, intAlgHandle->numLevels+1u, &autoIncCtlArgs);

 Exit:
    return status;
}


/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */


