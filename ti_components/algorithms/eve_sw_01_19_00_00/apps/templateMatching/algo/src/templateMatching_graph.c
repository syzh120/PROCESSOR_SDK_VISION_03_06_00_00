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


/** @file templateMatching_graph.c
 *
 *  @brief  This file implements an applet for template matching
 *
 *  @author TI
 *
 *  @date   Jan 2016
 *
 *  Description
 *    This file contains code to perform templateMatching transform on 8-bits or 16-bits image
 *    Contains implementation of TEMPLATE_MATCHING_TI_graphCreate() and TEMPLATE_MATCHING_TI_execute()
 *    at the frame level.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#pragma RESET_MISRA ("required")

#include "templateMatching_graph_int.h"

#include "bam_ncc.h"
#include "bam_natcNcc.h"

#include "edma_utils.h"

#include "iTemplateMatching_ti.h"

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
        { &gBAM_TI_ncc_Kernel, &gBAM_TI_ncc_HelperFunc,
          "ti_vision_ncc", BAM_TI_KERNELID_NCC},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcNcc_Kernel, &gBAM_TI_natcNcc_HelperFunc,
          "ti_vision_natcNcc", BAM_TI_KERNELID_NATCNCC},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
          "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_ncc_Kernel, &gBAM_TI_ncc_ExecFunc,
          "ti_vision_ncc", BAM_TI_KERNELID_NCC},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcNcc_Kernel, &gBAM_TI_natcNcc_ExecFunc,
          "ti_vision_natcNcc", BAM_TI_KERNELID_NATCNCC},
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.8 */
/* Name visibility is too wide */
/* Deviation is allowed because we use static keyword to make it local to the file */
static BAM_KernelDBdef gTEMPLATE_MATCHING_TI_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};
/*RESET_MISRA("8.7")  -> Reset rule 8.7 for GOTO */

static int32_t TEMPLATE_MATCHING_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0
#define NCC_NODE 1
#define SINK_NODE   2

int32_t TEMPLATE_MATCHING_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = TEMPLATE_MATCHING_TI_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = TEMPLATE_MATCHING_TI_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = TEMPLATE_MATCHING_TI_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(TEMPLATE_MATCHING_TI_graphArgs) ;
    return 0;
}



int32_t TEMPLATE_MATCHING_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        TEMPLATE_MATCHING_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    TEMPLATE_MATCHING_TI_graphArgs * graphArgs = (TEMPLATE_MATCHING_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,   BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT ,      NULL},
#if (VCOP_HOST_EMULATION) /* If we are compiling for Host emulation, use the natural C version as it is much faster */
            {NCC_NODE,   BAM_TI_KERNELID_NATCNCC,                NULL},
#else
            {NCC_NODE,   BAM_TI_KERNELID_NCC,                NULL},
#endif
            {SINK_NODE,     BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,      NULL},
            {BAM_END_NODE_MARKER,       0,                               NULL},\
    };

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {NCC_NODE, BAM_NCC_INPUT_PORT}},\
            {{NCC_NODE,  BAM_NCC_NUMCC_OUTPUT_PORT},            {SINK_NODE, BAM_SINK_NODE_PORT1}},\
            {{NCC_NODE,  BAM_NCC_DENOMVAR_OUTPUT_PORT},         {SINK_NODE, BAM_SINK_NODE_PORT2}},\
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };


    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[NCC_NODE].kernelArgs= &graphArgs->templateMatchingArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gTEMPLATE_MATCHING_TI_BAM_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gTEMPLATE_MATCHING_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= TEMPLATE_MATCHING_TI_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= TEMPLATE_MATCHING_TI_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= TEMPLATE_MATCHING_TI_GRAPH_CONTEXT_SIZE;
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
    graphCreateParams.initKernelsArgsFunc= &TEMPLATE_MATCHING_TI_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */
    graphCreateParams.blockDimParams.blockWidth= TEMPLATE_MATCHING_TI_BLK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight= TEMPLATE_MATCHING_TI_BLK_HEIGHT;

    graphCreateParams.blockDimParams.blockWidthStep= TEMPLATE_MATCHING_TI_BLK_WIDTH_STEP;
    graphCreateParams.blockDimParams.blockHeightStep= TEMPLATE_MATCHING_TI_BLK_HEIGHT_STEP;

    graphCreateParams.blockDimParams.blockWidthDivisorOf= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= createParams->imgFrameHeight;

    graphCreateParams.blockDimParams.blockWidthMax= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightMax= createParams->imgFrameHeight;

    /* These output members will be filled by BAM_createGraph() but we initialize them to 0 beforehand */
    graphCreateParams.graphMemConsumed= 0;
    graphCreateParams.onChipScratchMemConsumed= 0;
    graphCreateParams.extMemConsumed= 0;

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

/* TEMPLATE_MATCHING_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t TEMPLATE_MATCHING_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {
    /*RESET_MISRA("16.7")  -> Reset rule 16.7  */
    int16_t srcBlockWidth, srcBlockHeight, sinkBlockWidth;

    TEMPLATE_MATCHING_TI_graphArgs *graphArgs= (TEMPLATE_MATCHING_TI_graphArgs*)initKernelsArgs;

    int16_t blkWidthFinal= 0;
    int16_t blkHeightFinal= 0;

    int32_t status = BAM_S_SUCCESS;

    blkWidthFinal = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    if (graphArgs->createParams->imgFrameWidth % blkWidthFinal) {
        PRINTF("Block width found does not divide the image width\n");
        status= BAM_E_FAIL;
        goto Exit;
    }

    if (graphArgs->createParams->imgFrameHeight % blkHeightFinal) {
        PRINTF("Block height found does not divide the image height\n");
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* The width of the block transferred by the source EDMA includes overlapping region required by the fact that templateMatching transform operates like a filter
     * blkWidthFinal and blkHeightFinal just represents the dimension of the final block after all the filtering have been applied
     * */
    srcBlockWidth= blkWidthFinal + ((int16_t)graphArgs->createParams->templateWidth - 1);
    srcBlockHeight= blkHeightFinal + ((int16_t)graphArgs->createParams->templateHeight - 1);

    graphArgs->templateMatchingArgs.outputWidth= blkWidthFinal;
    graphArgs->templateMatchingArgs.outputHeight= blkHeightFinal;
    graphArgs->templateMatchingArgs.templateWidth= graphArgs->createParams->templateWidth;
    graphArgs->templateMatchingArgs.templateHeight= graphArgs->createParams->templateHeight;
    graphArgs->templateMatchingArgs.inPitch= srcBlockWidth;
    graphArgs->templateMatchingArgs.outPitch= blkWidthFinal;
    graphArgs->templateMatchingArgs.qShift= graphArgs->createParams->qShift;
    graphArgs->templateMatchingArgs.sizeQshift= graphArgs->createParams->sizeQshift;

    sinkBlockWidth= graphArgs->templateMatchingArgs.outPitch;

    graphArgs->createParams->activeImgWidth=  graphArgs->createParams->imgFrameWidth  + (graphArgs->createParams->templateWidth  - 1);
    graphArgs->createParams->activeImgHeight= graphArgs->createParams->imgFrameHeight + (graphArgs->createParams->templateHeight - 1);

    graphArgs->dmaReadKernelArgs.numInTransfers                                           = 1;
    graphArgs->dmaReadKernelArgs.transferType                                             = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(
            &graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT1],
            graphArgs->createParams->activeImgWidth,                                     /* roiWidth */
            graphArgs->createParams->activeImgHeight,                                    /* roiHeight */
            (uint16_t)srcBlockWidth,                                                     /* blkWidth */
            (uint16_t)srcBlockHeight,                                                    /* blkHeight */
            (uint16_t)blkWidthFinal,                                                     /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                                                    /* extBlkIncrementY */
            0U,                                                                          /* intBlkIncrementX */
            0U,                                                                          /* intBlkIncrementY */
            0U,                                                                          /* roiOffset        */
            0U,                                                                          /* blkOffset        */
            (uint8_t*)NULL,                                                              /* extMemPtr        */
            0U,                                                                          /* extMemPtrStride  */
            (uint8_t*)NULL,                                                              /* interMemPtr      */
            (uint16_t)srcBlockWidth,                                                     /* interMemPtrStride */
            0U);                                                                         /* dmaQueNo          */

    graphArgs->dmaWriteKernelArgs.numOutTransfers = 2;
    graphArgs->dmaWriteKernelArgs.transferType    = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(
            &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*4U, /* roiWidth */
            graphArgs->createParams->imgFrameHeight,   /* roiHeight */
            (uint16_t)((uint32_t)blkWidthFinal*4U),          /* blkWidth */
            (uint16_t)blkHeightFinal,                           /* blkHeight */
            (uint16_t)((uint32_t)blkWidthFinal*4U),          /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                           /* extBlkIncrementY */
            0U,                                        /* intBlkIncrementX */
            0U,                                        /* intBlkIncrementY */
            0U,                                        /* roiOffset        */
            0U,                                        /* blkOffset        */
            NULL,                                     /* extMemPtr        */
            0U,                                        /* extMemPtrStride  */
            NULL,                                     /* interMemPtr      */
            ((uint16_t)sinkBlockWidth*4U),                           /* interMemPtrStride */
            1U);                                       /* dmaQueNo          */

    assignDMAautoIncrementParams(
            &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT2],
            graphArgs->createParams->imgFrameWidth*4U, /* roiWidth */
            graphArgs->createParams->imgFrameHeight,   /* roiHeight */
            (uint16_t)((uint32_t)blkWidthFinal*4U),          /* blkWidth */
            (uint16_t)blkHeightFinal,                           /* blkHeight */
            (uint16_t)((uint32_t)blkWidthFinal*4U),          /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                           /* extBlkIncrementY */
            0U,                                        /* intBlkIncrementX */
            0U,                                        /* intBlkIncrementY */
            0U,                                        /* roiOffset        */
            0U,                                        /* blkOffset        */
            NULL,                                     /* extMemPtr        */
            0U,                                        /* extMemPtrStride  */
            NULL,                                     /* interMemPtr      */
            ((uint16_t)sinkBlockWidth*4U),                           /* interMemPtrStride */
            1U);                                       /* dmaQueNo          */

    Exit:
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_execute(
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

int32_t TEMPLATE_MATCHING_TI_dmaControl(const BAM_GraphMem *graphMem, const TEMPLATE_MATCHING_TI_Handle intAlgHandle, const IVISION_BufDesc *inBufDesc[], const IVISION_BufDesc *outBufDesc[])
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    BAM_Ncc_CtlArgs nccCtrlArgs;

    uint8_t (*buf)[];
    int16_t (*buf16)[];

    const IVISION_BufPlanes * ivisionBufPlane= &inBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_IN]->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    if (((ivisionBufPlane->frameROI.width % intAlgHandle->outputBlockWidth)!= 0) ||  ((ivisionBufPlane->frameROI.height % intAlgHandle->outputBlockHeight)!= 0)) {
        status= TEMPLATE_MATCHING_TI_ERROR_INVALID_ROI_DIM;
        goto Exit;
    }

    buf= (uint8_t (*)[])ivisionBufPlane->buf;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    /* We rewind topLeft.x and topLeft.y by the exact border width and height required to include border pixels necessary for the templateMatching transform.
     * This is to ensure that the pointer for EDMA read points exactly to the upper left corner of the region composed
     * by the ROI augmented by the templateMatching window border.
     * */
    autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[((ivisionBufPlane->frameROI.topLeft.y * (int32_t)ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x)]);
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;
    autoIncCtlArgs.updateParams[0].roiWidth= (uint16_t)((uint32_t)((uint32_t)ivisionBufPlane->frameROI.width + ((uint32_t)(intAlgHandle->templateWidth) - 1U)));
    autoIncCtlArgs.updateParams[0].roiHeight= ivisionBufPlane->frameROI.height + (intAlgHandle->templateHeight - 1U);

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }

    intAlgHandle->activeImgWidth= autoIncCtlArgs.updateParams[0].roiWidth;
    intAlgHandle->activeImgHeight= autoIncCtlArgs.updateParams[0].roiHeight;

    /* Initialize the control parameters for the SINK auto-increment DMA node */
    ivisionBufPlane= &outBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_OUT]->bufPlanes[0];
    buf= (uint8_t (*)[])ivisionBufPlane->buf;

    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[4*((ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x)]);
    autoIncCtlArgs.updateParams[0].extMemPtrStride = 4*ivisionBufPlane->width;
    autoIncCtlArgs.updateParams[0].roiWidth= 4 * ivisionBufPlane->frameROI.width;
    autoIncCtlArgs.updateParams[0].roiHeight= ivisionBufPlane->frameROI.height;

    ivisionBufPlane= &outBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_OUT]->bufPlanes[1];
    buf= (uint8_t (*)[])ivisionBufPlane->buf;

    autoIncCtlArgs.updateParams[1].extMemPtr= &((*buf)[4*((ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x)]);
    autoIncCtlArgs.updateParams[1].extMemPtrStride = 4*ivisionBufPlane->width;
    autoIncCtlArgs.updateParams[1].roiWidth= 4 * ivisionBufPlane->frameROI.width;
    autoIncCtlArgs.updateParams[1].roiHeight= ivisionBufPlane->frameROI.height;

    status= BAM_controlNode(graphHandle, (uint8_t)SINK_NODE, (void*)&autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }

    ivisionBufPlane= &inBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_IN_TEMPLATE]->bufPlanes[0];
    nccCtrlArgs.ctlCmdId= BAM_NCC_CMD_SET_TEMPLATE_PTR;

    buf16= (int16_t (*)[])ivisionBufPlane->buf;
    nccCtrlArgs.pExtTemplate= &((*buf16)[((ivisionBufPlane->frameROI.topLeft.y * (int32_t)ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x)]);
    nccCtrlArgs.templateExtPitch= ivisionBufPlane->width;
    status= (int32_t)BAM_controlNode(graphHandle, (uint8_t)NCC_NODE, &nccCtrlArgs);

    Exit:
    return status;
}





