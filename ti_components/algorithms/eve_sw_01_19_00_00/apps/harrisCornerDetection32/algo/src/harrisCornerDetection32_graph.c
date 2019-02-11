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


/** @file harrisCornerDetection32_graph.c
 *
 *  @brief  This file implements an applet for harris corner detection
 *
 *  @author TI
 *
 *  @date   19 Dec 2013
 *
 *  Description
 *    This file contains code to perform harris corner detection on 8-bit grayscale image
 *    Contains implementation of EVELIB_harrisCornerDetection32_create() and EVELIB_harrisCornerDetection32_execute()
 *    at the frame level.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#pragma RESET_MISRA ("required")

#include "harrisCornerDetection32_graph_int.h"
#include "bam_gradXYmag.h"
#include "bam_harrisScore_32_7x7.h"
#include "bam_nonMaxSuppress_mxn_S32.h"
#include "bam_generateList.h"

#include "bam_natcGradXYmag.h"
#include "bam_natcHarrisScore_32_7x7.h"
#include "bam_natcNonMaxSuppress_mxn_S32.h"
#include "bam_natcGenerateList.h"

#include "bam_dma_one_shot_node.h"

#include "edma_utils.h"

#include "iHarrisCornerDetection32_ti.h"

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

static void assignOneShotDmaParams(
        BAM_DMA_OneShot_transferProperties * param,
        uint16_t    blkWidth,
        uint16_t    blkHeight,
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride
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
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_dmaOneShotWriteKernel, &gBAM_TI_dmaWriteOneShotKernelHelperFunc, "ti_dma_write_oneshot", BAM_TI_KERNELID_DMAWRITE_ONESHOT},

        { &gBAM_TI_gradXYmagKernel,             &gBAM_TI_gradXYmagHelperFunc, "ti_grad_xymag", BAM_TI_KERNELID_GRAD_XYMAG },
        { &gBAM_TI_harrisScore_32_7x7_Kernel,    &gBAM_TI_harrisScore_32_7x7_HelperFunc, "ti_harris_score_32_7x7", BAM_TI_KERNELID_HARRISSCORE_32_7x7 },
        { &gBAM_TI_harrisScore_32_methodB_Kernel,    &gBAM_TI_harrisScore_32_methodB_HelperFunc, "ti_harris_score_32_method_B", BAM_TI_KERNELID_HARRISSCORE_32_METHOD_B },
        { &gBAM_TI_nonMaxSuppress_mxn_S32_Kernel,    &gBAM_TI_nonMaxSuppress_mxn_S32_HelperFunc, "ti_nonMaxSuppress_mxn_S32", BAM_TI_KERNELID_NONMAXSUPPRESS_MxN },
        { &gBAM_TI_nonMaxSuppress_mxn_S32_binPack_Kernel,    &gBAM_TI_nonMaxSuppress_mxn_S32_HelperFunc, "ti_nonMaxSuppress_mxn_S32_binPack", BAM_TI_KERNELID_NONMAXSUPPRESS_MxN_BINPACK },
        { &gBAM_TI_generateListKernel,    &gBAM_TI_generateListHelperFunc, "ti_generateList_S32", BAM_TI_KERNELID_GENERATELIST },

        { &gBAM_TI_natcGradXYmagKernel,             &gBAM_TI_natcGradXYmagHelperFunc, "ti_natcGrad_xymag", BAM_TI_KERNELID_NATCGRAD_XYMAG },
        { &gBAM_TI_natcHarrisScore_32_7x7_Kernel,    &gBAM_TI_natcHarrisScore_32_7x7_HelperFunc, "ti_natcHarris_score_32_7x7", BAM_TI_KERNELID_NATCHARRISSCORE_32_7x7 },
        { &gBAM_TI_natcNonMaxSuppress_mxn_S32_Kernel,    &gBAM_TI_natcNonMaxSuppress_mxn_S32_HelperFunc, "ti_natcNonMaxSuppress_mxn_S32", BAM_TI_KERNELID_NATCNONMAXSUPPRESS_MxN },
        { &gBAM_TI_natcGenerateListKernel,    &gBAM_TI_natcGenerateListHelperFunc, "ti_natcGenerateList", BAM_TI_KERNELID_NATCGENERATELIST },
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc, "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc, "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_dmaOneShotWriteKernel, &gBAM_TI_dmaWriteOneShotKernelExecFunc, "ti_dma_write_oneshot", BAM_TI_KERNELID_DMAWRITE_ONESHOT},

        { &gBAM_TI_gradXYmagKernel,             &gBAM_TI_gradXYmagExecFunc, "ti_grad_xymag", BAM_TI_KERNELID_GRAD_XYMAG },
        { &gBAM_TI_harrisScore_32_7x7_Kernel,    &gBAM_TI_harrisScore_32_7x7_ExecFunc, "ti_harris_score_32_7x7", BAM_TI_KERNELID_HARRISSCORE_32_7x7 },
        { &gBAM_TI_harrisScore_32_methodB_Kernel,    &gBAM_TI_harrisScore_32_methodB_ExecFunc, "ti_harris_score_32_method_B", BAM_TI_KERNELID_HARRISSCORE_32_METHOD_B },
        { &gBAM_TI_nonMaxSuppress_mxn_S32_Kernel,    &gBAM_TI_nonMaxSuppress_mxn_S32_ExecFunc, "ti_nonMaxSuppress_mxn_S32", BAM_TI_KERNELID_NONMAXSUPPRESS_MxN },
        { &gBAM_TI_nonMaxSuppress_mxn_S32_binPack_Kernel,    &gBAM_TI_nonMaxSuppress_mxn_S32_binPack_ExecFunc, "ti_nonMaxSuppress_mxn_S32_binPack", BAM_TI_KERNELID_NONMAXSUPPRESS_MxN_BINPACK },
        { &gBAM_TI_generateListKernel,    &gBAM_TI_generateListExecFunc, "ti_generateList_S32", BAM_TI_KERNELID_GENERATELIST },

        { &gBAM_TI_natcGradXYmagKernel,         &gBAM_TI_natcGradXYmagExecFunc, "ti_natcgrad_xymag", BAM_TI_KERNELID_NATCGRAD_XYMAG },
        { &gBAM_TI_natcHarrisScore_32_7x7_Kernel,    &gBAM_TI_natcHarrisScore_32_7x7_ExecFunc, "ti_natcHarris_score_32_7x7", BAM_TI_KERNELID_NATCHARRISSCORE_32_7x7 },
        { &gBAM_TI_natcNonMaxSuppress_mxn_S32_Kernel,    &gBAM_TI_natcNonMaxSuppress_mxn_S32_ExecFunc, "ti_natcNonMaxSuppress_mxn_S32", BAM_TI_KERNELID_NATCNONMAXSUPPRESS_MxN },
        { &gBAM_TI_natcGenerateListKernel,    &gBAM_TI_natcGenerateListExecFunc, "ti_natcGenerateList", BAM_TI_KERNELID_NATCGENERATELIST },
};

static BAM_KernelDBdef gHARRIS_CORNER_DETECTION_32_TI_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};

static int32_t HARRIS_CORNER_DETECTION_32_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#ifdef _ONLY_GRAD_OUTPUT

#define SOURCE_NODE 0
#define GRAD_NODE   1
#define SINK_NODE   2

#elif defined(_ONLY_HARRIS_OUTPUT)

#define SOURCE_NODE 0
#define GRAD_NODE   1
#define HARRIS_NODE 2
#define SINK_NODE   3

#elif defined(_ONLY_NMS_OUTPUT)

#define SOURCE_NODE 0
#define GRAD_NODE   1
#define HARRIS_NODE 2
#define NMS_NODE    3
#define SINK_NODE   4

#else

#define SOURCE_NODE 0
#define GRAD_NODE   (1U)
#define HARRIS_NODE (2U)
#define NMS_NODE    (3U)
#define GENLIST_NODE (4U)
#define SINK_NODE    (5U)
#define SINK_NODE_BINPACK (GENLIST_NODE)
#endif

int32_t HARRIS_CORNER_DETECTION_32_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = HARRIS_CORNER_DETECTION_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = HARRIS_CORNER_DETECTION_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = HARRIS_CORNER_DETECTION_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(HARRIS_CORNER_DETECTION_32_TI_graphArgs) ;
    return 0;
}


/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used*/
int32_t HARRIS_CORNER_DETECTION_32_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        HARRIS_CORNER_DETECTION_32_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;
    /* initilize the sub-handles inside the main handle */
    HARRIS_CORNER_DETECTION_32_TI_graphArgs * graphArgs = (HARRIS_CORNER_DETECTION_32_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*-
     *
     */
    /* For debugging purpose, we can create one of these 3 graphs based on macro-symbol:
     * one graph that only produces X gradient
     * one graph that only produces harris score
     * one graph that produces the entire harris corner detection
     */
#ifdef _ONLY_GRAD_OUTPUT
    /* Partial graph of harris corner detection, up to gradient computation */
    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_GRAD_XYMAG,          NULL},
            {SINK_NODE,    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,  NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };

    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[GRAD_NODE].kernelArgs= &graphArgs->gradArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {GRAD_NODE,  BAM_GRADXYMAG_INPUT_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_X_OUTPUT_PORT},       {SINK_NODE, BAM_SINK_NODE_PORT1}}, /* We only capture the X gradient output for debugging purpose */
            {{GRAD_NODE,    BAM_GRADXYMAG_Y_OUTPUT_PORT},       {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_Y_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{GRAD_NODE,    BAM_GRADXYMAG_MAG_OUTPUT_PORT},     {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_MAG_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

#elif defined(_ONLY_HARRIS_OUTPUT)
    /* Partial graph of harris corner detection, up to harris score computation */
    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_GRAD_XYMAG,          NULL},
            {HARRIS_NODE,  BAM_TI_KERNELID_HARRISSCORE_32_7x7,  NULL},
            {SINK_NODE,    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,  NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };

    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[GRAD_NODE].kernelArgs= &graphArgs->gradArgs;
    NODELIST[HARRIS_NODE].kernelArgs= &graphArgs->harrisScoreArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {GRAD_NODE,  BAM_GRADXYMAG_INPUT_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_X_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADX_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_Y_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADY_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_MAG_OUTPUT_PORT},     {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_MAG_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{HARRIS_NODE,   BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT}, {SINK_NODE, BAM_SINK_NODE_PORT1}},
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

#elif defined(_ONLY_NMS_OUTPUT)
    /* Partial graph of harris corner detection up to NMS. For debugging, user can replace any kernel ID with its natural C counterpart picked from above. */
    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_GRAD_XYMAG,          NULL},
            {HARRIS_NODE,  BAM_TI_KERNELID_HARRISSCORE_32_7x7,  NULL},
            {NMS_NODE,     BAM_TI_KERNELID_NONMAXSUPPRESS_MxN,  NULL},
            {SINK_NODE,    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,  NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };

    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[GRAD_NODE].kernelArgs= &graphArgs->gradArgs;
    NODELIST[HARRIS_NODE].kernelArgs= &graphArgs->harrisScoreArgs;
    NODELIST[NMS_NODE].kernelArgs= &graphArgs->nmsArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {GRAD_NODE,  BAM_GRADXYMAG_INPUT_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_X_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADX_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_Y_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADY_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_MAG_OUTPUT_PORT},     {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_MAG_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{HARRIS_NODE,   BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT}, {NMS_NODE, BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT}},
            {{NMS_NODE,   BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT}, {SINK_NODE, BAM_SINK_NODE_PORT1}},
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

#else

#ifdef _USE_NATC
    /* Full graph of harris corner detection using natc code for debugging purpose */
    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_NATCGRAD_XYMAG,          NULL},
            {HARRIS_NODE,  BAM_TI_KERNELID_NATCHARRISSCORE_32_7x7,  NULL},
            {NMS_NODE,     BAM_TI_KERNELID_NATCNONMAXSUPPRESS_MxN,  NULL},
            {GENLIST_NODE, BAM_TI_KERNELID_NATCGENERATELIST,        NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };
#else

    BAM_NodeParams (* NODELIST)[];
    BAM_EdgeParams (* EDGELIST)[];

    /* Full graph of harris corner detection. For debugging, user can replace any kernel ID with its natural C counterpart picked from above. */
    BAM_NodeParams NODELIST_listOutput[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_GRAD_XYMAG,          NULL},
            {HARRIS_NODE,  BAM_TI_KERNELID_HARRISSCORE_32_7x7,  NULL},
            {NMS_NODE,     BAM_TI_KERNELID_NONMAXSUPPRESS_MxN,  NULL},
#if VCOP_HOST_EMULATION
            {GENLIST_NODE, BAM_TI_KERNELID_NATCGENERATELIST,        NULL},
#else
            {GENLIST_NODE, BAM_TI_KERNELID_GENERATELIST,        NULL},
#endif
            {SINK_NODE,    BAM_TI_KERNELID_DMAWRITE_ONESHOT,  NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };

    NODELIST_listOutput[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST_listOutput[GRAD_NODE].kernelArgs= &graphArgs->gradArgs;
    NODELIST_listOutput[HARRIS_NODE].kernelArgs= &graphArgs->harrisScoreArgs;
    NODELIST_listOutput[NMS_NODE].kernelArgs= &graphArgs->nmsArgs;
    NODELIST_listOutput[GENLIST_NODE].kernelArgs= &graphArgs->genListArgs;
    NODELIST_listOutput[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    /* This is node list for the graph when user requested bin pack output instead of list output
    Generate list node is removed from this list */
    BAM_NodeParams NODELIST_binPackOutput[]={\
            {SOURCE_NODE,  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,   NULL},
            {GRAD_NODE,    BAM_TI_KERNELID_GRAD_XYMAG,          NULL},
            {HARRIS_NODE,  BAM_TI_KERNELID_HARRISSCORE_32_7x7,  NULL},
            {NMS_NODE,     BAM_TI_KERNELID_NONMAXSUPPRESS_MxN_BINPACK,  NULL},
            {SINK_NODE_BINPACK,    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,  NULL},
            {BAM_END_NODE_MARKER,       0,                          NULL},
    };

    NODELIST_binPackOutput[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST_binPackOutput[GRAD_NODE].kernelArgs= &graphArgs->gradArgs;
    NODELIST_binPackOutput[HARRIS_NODE].kernelArgs= &graphArgs->harrisScoreArgs;
    NODELIST_binPackOutput[NMS_NODE].kernelArgs= &graphArgs->nmsArgs;
    NODELIST_binPackOutput[SINK_NODE_BINPACK].kernelArgs= &graphArgs->dmaWriteBitPackedKernelArgs;

#endif




    BAM_EdgeParams EDGELIST_listOutput[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {GRAD_NODE,  BAM_GRADXYMAG_INPUT_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_X_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADX_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_Y_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADY_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_MAG_OUTPUT_PORT},     {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_MAG_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{HARRIS_NODE,   BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT}, {NMS_NODE, BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT}},
            {{NMS_NODE,   BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT}, {GENLIST_NODE, BAM_GENERATELIST_INPUT_PORT}},
            {{GENLIST_NODE,   BAM_GENERATELIST_OUTPUT_XY_PORT}, {SINK_NODE, BAM_SINK_NODE_PORT1}},
            {{GENLIST_NODE,   BAM_GENERATELIST_OUTPUT_NUM_ELMNTS_PORT}, {SINK_NODE, BAM_SINK_NODE_PORT2}},
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}}
          };

    BAM_EdgeParams EDGELIST_binPackOutput[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {GRAD_NODE,  BAM_GRADXYMAG_INPUT_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_X_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADX_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_Y_OUTPUT_PORT},       {HARRIS_NODE, BAM_HARRISSCORE_32_INPUT_GRADY_PORT}},
            {{GRAD_NODE,    BAM_GRADXYMAG_MAG_OUTPUT_PORT},     {BAM_NULL_NODE, 0}}, /* BAM_GRADXYMAG_MAG_OUTPUT_PORT is unused and so must be connected to BAM_NULL_NODE, otherwise error BAM_E_PORT_NOT_CONNECTED is returned */
            {{HARRIS_NODE,   BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT}, {NMS_NODE, BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT}},
            {{NMS_NODE,   BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT}, {SINK_NODE_BINPACK, BAM_SINK_NODE_PORT1}},
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

    NODELIST = (BAM_NodeParams(*)[])(void*)NODELIST_listOutput;
    EDGELIST = (BAM_EdgeParams (*)[])(void*)EDGELIST_listOutput;
    /* Switch nodelist and edgelist based on the output format selected by user */
    if ( createParams->outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_BINARY_PACK )
    {
      NODELIST = (BAM_NodeParams(*)[])(void*)NODELIST_binPackOutput;
      EDGELIST = (BAM_EdgeParams (*)[])(void*)EDGELIST_binPackOutput;
    }

#endif

    /* If user wanted to use differet score method then just change the corresponding kernel id */
    if ( createParams->harrisScoreMethod == HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_B)
    {
      (*NODELIST)[HARRIS_NODE].kernelId = BAM_TI_KERNELID_HARRISSCORE_32_METHOD_B;
    }
    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gHARRIS_CORNER_DETECTION_32_TI_BAM_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gHARRIS_CORNER_DETECTION_32_TI_BAM_kernelDBdef;
#if !defined(_ONLY_GRAD_OUTPUT) && !defined(_ONLY_HARRIS_OUTPUT) && !defined(_ONLY_NMS_OUTPUT)
    graphCreateParams.nodeList= (BAM_NodeParams*)&((*NODELIST)[0]);
    graphCreateParams.edgeList= (BAM_EdgeParams*)&((*EDGELIST)[0]);
#else
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
#endif
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= HARRIS_CORNER_DETECTION_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= HARRIS_CORNER_DETECTION_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= HARRIS_CORNER_DETECTION_GRAPH_CONTEXT_SIZE;
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
    graphCreateParams.initKernelsArgsFunc= &HARRIS_CORNER_DETECTION_32_TI_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */
    graphCreateParams.blockDimParams.blockWidth= HARRIS_CORNER_DETECTION_BLK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight= HARRIS_CORNER_DETECTION_BLK_HEIGHT;

    graphCreateParams.blockDimParams.blockWidthStep= HARRIS_CORNER_DETECTION_BLK_WIDTH_STEP;
    graphCreateParams.blockDimParams.blockHeightStep= HARRIS_CORNER_DETECTION_BLK_HEIGHT_STEP;
    graphCreateParams.blockDimParams.blockWidthDivisorOf= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= createParams->imgFrameHeight;
    graphCreateParams.blockDimParams.blockWidthMax= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightMax= createParams->imgFrameHeight;

    status = BAM_createGraph(&graphCreateParams, &graphHandle);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    if (graphCreateParams.blockDimParams.blockWidth < graphArgs->createParams->totalBorderRequired) {
        PRINTF("WARNING: Block width of %d returned by BAM_createGraph() is too small. For the block dimensions optimizer to operate better, try to make the frame's width be multiple of HARRIS_CORNER_DETECTION_BLK_WIDTH. \n", graphCreateParams.blockDimParams.blockWidth);
    }

    if (graphCreateParams.blockDimParams.blockHeight <  graphArgs->createParams->totalBorderRequired) {
        PRINTF("WARNING: Block height of %d returned by BAM_createGraph() is too small. For the block dimensions optimizer to operate better, try to make the frame's height be multiple of HARRIS_CORNER_DETECTION_BLK_HEIGHT. \n", graphCreateParams.blockDimParams.blockHeight);
    }

    createParams->outputBlockWidth= graphCreateParams.blockDimParams.blockWidth;
    createParams->outputBlockHeight= graphCreateParams.blockDimParams.blockHeight;

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
    param->blkOffset            = 0;
    param->extMemPtr            = extMemPtr;
    param->extMemPtrStride      = extMemPtrStride ;
    param->interMemPtr          = interMemPtr ;
    param->interMemPtrStride    = interMemPtrStride;
    param->dmaQueNo             = dmaQueNo;
}

static void assignOneShotDmaParams(
        BAM_DMA_OneShot_transferProperties * param,
        uint16_t    blkWidth,
        uint16_t    blkHeight,
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride
)
{
    param->blkWidth             = blkWidth;
    param->blkHeight            = blkHeight;
    param->extMemPtr            = extMemPtr;
    param->extMemPtrStride      = extMemPtrStride ;
    param->interMemPtr          = interMemPtr ;
    param->interMemPtrStride    = interMemPtrStride;
}


/* EVELIB_harrisCornerDetection32_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t HARRIS_CORNER_DETECTION_32_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */

    HARRIS_CORNER_DETECTION_32_TI_graphArgs *graphArgs= (HARRIS_CORNER_DETECTION_32_TI_graphArgs*)initKernelsArgs;

    uint16_t blkWidthFinal= 0;
    uint16_t blkHeightFinal= 0;
    uint16_t blockWidth, blockHeight, inStride, outStride;
    uint16_t numHorzBlocks, numVertBlocks;
    uint8_t totalBorderRequired;
    uint8_t gradientBorder;
    uint8_t harrisBorder;
    uint8_t nmsBorder;

    blkWidthFinal = (uint16_t)blockDimParams->blockWidth;
    blkHeightFinal = (uint16_t)blockDimParams->blockHeight;

    assert((graphArgs->createParams->imgFrameWidth % blkWidthFinal) == 0);
    assert((graphArgs->createParams->imgFrameHeight % blkHeightFinal) == 0);

    gradientBorder = GRAD_FILTER_SZ - 1U;

    harrisBorder   = (uint8_t)(graphArgs->createParams->harrisWindowSize - 1u );

    nmsBorder      = (uint8_t)(graphArgs->createParams->nmsWindowSize - 1u);

    totalBorderRequired = graphArgs->createParams->totalBorderRequired;

    /* The width of the block transferred by the source EDMA includes overlapping region required by the succession of filtering operation taking places in the graph
     * blkWidthFinal and blkHeightFinal just represents the dimension of the final block after all the filtering have been applied
     * */
    blockWidth= blkWidthFinal   + totalBorderRequired;
    blockHeight= blkHeightFinal + totalBorderRequired;

    graphArgs->gradArgs.gradientMethod  = EVE_VLIB_GRADIENT_MAGNITUDE_9BITS;
    graphArgs->gradArgs.pitch           = blockWidth;
    graphArgs->gradArgs.width           = blockWidth  - gradientBorder;
    graphArgs->gradArgs.height          = blockHeight - gradientBorder;

    inStride    = blockWidth  - gradientBorder;
    blockWidth  = blockWidth  - gradientBorder;
    blockHeight = blockHeight - gradientBorder;
    /* Somehow the harris score kernel fails, when compiled on the host, if outStride is not multiple of 8 */
    outStride= (uint16_t)ALIGN_SIMD((uint32_t)((uint32_t)blockWidth - (uint32_t)harrisBorder));

#ifndef _ONLY_GRAD_OUTPUT
    graphArgs->harrisScoreArgs.width= blockWidth;
    graphArgs->harrisScoreArgs.height= blockHeight;
    graphArgs->harrisScoreArgs.inStride= inStride;
    graphArgs->harrisScoreArgs.outStride= outStride;
    graphArgs->harrisScoreArgs.scaling= graphArgs->createParams->harrisScoreScalingFactor;
    graphArgs->harrisScoreArgs.windowSize = graphArgs->createParams->harrisWindowSize;

    inStride= outStride;
    blockWidth= blockWidth   - harrisBorder;
    blockHeight= blockHeight - harrisBorder;
    outStride= (uint16_t)ALIGN_SIMD((uint32_t)((uint32_t)blockWidth - (uint32_t)nmsBorder));

    if ( graphArgs->createParams->outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_BINARY_PACK)
    {
      outStride = outStride / 8u;
    }

#ifndef _ONLY_HARRIS_OUTPUT
    graphArgs->nmsArgs.width= blockWidth;
    graphArgs->nmsArgs.height= blockHeight;
    graphArgs->nmsArgs.inStride= inStride;
    graphArgs->nmsArgs.outStride= outStride;
    graphArgs->nmsArgs.winW = graphArgs->createParams->nmsWindowSize; /* NMS window width */
    graphArgs->nmsArgs.winH = graphArgs->createParams->nmsWindowSize; /* NMS window width */
    graphArgs->nmsArgs.threshold= graphArgs->createParams->nmsThresh;

    if ( graphArgs->createParams->outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST )
    {
      graphArgs->nmsArgs.outputFormat = BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP;
    }
    else
    {
      graphArgs->nmsArgs.outputFormat =BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BINPACK;
    }

    blockWidth= blockWidth    - nmsBorder;
    blockHeight=  blockHeight - nmsBorder;
    inStride= outStride;

    numHorzBlocks= graphArgs->createParams->imgFrameWidth/blockWidth;
    numVertBlocks= graphArgs->createParams->imgFrameHeight/blockHeight;

    graphArgs->createParams->activeImgWidth= ((numHorzBlocks*blockWidth) + totalBorderRequired)*sizeof(uint8_t);
    graphArgs->createParams->activeImgHeight= (numVertBlocks*blockHeight) + totalBorderRequired;

#ifndef _ONLY_NMS_OUTPUT
    graphArgs->genListArgs.width= blockWidth;
    graphArgs->genListArgs.height= blockHeight;
    graphArgs->genListArgs.inStride= inStride;
    graphArgs->genListArgs.numHorzBlock= numHorzBlocks;
    graphArgs->genListArgs.numVertBlock= numVertBlocks;
    graphArgs->genListArgs.maxNumElmts= graphArgs->createParams->maxNumCorners;
    graphArgs->genListArgs.qShift= graphArgs->createParams->qShift;
    graphArgs->genListArgs.offsetX= totalBorderRequired/2u;
    graphArgs->genListArgs.offsetY= totalBorderRequired/2u;
#endif

#endif
#endif
    /* Verify that at the end of the succession of filter, the block dimensions are as expected */
    /*
    assert(blockWidth== blkWidthFinal);
    assert(blockHeight== blkHeightFinal);
     */

    graphArgs->dmaReadKernelArgs.numInTransfers                                           = 1;
    graphArgs->dmaReadKernelArgs.transferType                                             = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(&graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT1],
            (graphArgs->createParams->imgFrameWidth + (uint16_t)totalBorderRequired)*sizeof(uint8_t), /* roiWidth */
            (graphArgs->createParams->imgFrameHeight + (uint16_t)totalBorderRequired),                /* roiHeight */
            (blkWidthFinal  + (uint16_t)totalBorderRequired)*sizeof(uint8_t),                         /* blkWidth */
            blkHeightFinal + (uint16_t)totalBorderRequired,                                           /* blkHeight */
            blkWidthFinal*sizeof(uint8_t),                                              /* extBlkIncrementX */
            blkHeightFinal,                                                             /* extBlkIncrementY */
            0,                                                                          /* intBlkIncrementX */
            0,                                                                          /* intBlkIncrementY */
            0,                                                                          /* roiOffset        */
            NULL,                                                                       /* extMemPtr        */
            0,                                                                          /* extMemPtrStride  */
            NULL,                                                                       /* interMemPtr      */
            (blkWidthFinal  + (uint16_t)totalBorderRequired)*sizeof(uint8_t),                         /* interMemPtrStride */
            0);                                                                         /* dmaQueNo          */

#if defined(_ONLY_GRAD_OUTPUT) || defined(_ONLY_HARRIS_OUTPUT) || defined(_ONLY_NMS_OUTPUT)
    graphArgs->dmaWriteKernelArgs.numOutTransfers                                        = 1;
    graphArgs->dmaWriteKernelArgs.transferType                                           = EDMA_UTILS_TRANSFER_OUT;

#ifdef _ONLY_GRAD_OUTPUT
    assignDMAautoIncrementParams(&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*sizeof(int16_t),                      /* roiWidth */
            graphArgs->createParams->imgFrameHeight,                                     /* roiHeight */
            blkWidthFinal*sizeof(int16_t),                                               /* blkWidth */
            blkHeightFinal,                                                              /* blkHeight */
            blkWidthFinal*sizeof(int16_t),                                               /* extBlkIncrementX */
            blkHeightFinal,                                                              /* extBlkIncrementY */
            0,                                                                           /* intBlkIncrementX */
            0,                                                                           /* intBlkIncrementY */
            0,                                                                           /* roiOffset        */
            NULL,                                                                        /* extMemPtr        */
            0,                                                                           /* extMemPtrStride  */
            NULL,                                                                        /* interMemPtr      */
            (blkWidthFinal+ gradientBorder)*sizeof(int16_t),                            /* interMemPtrStride */
            0);                                                                          /* dmaQueNo          */

#elif defined(_ONLY_HARRIS_OUTPUT)
    assignDMAautoIncrementParams(&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*sizeof(int32_t),                      /* roiWidth */
            graphArgs->createParams->imgFrameHeight,                                     /* roiHeight */
            blkWidthFinal*sizeof(int32_t),                                               /* blkWidth */
            blkHeightFinal,                                                              /* blkHeight */
            blkWidthFinal*sizeof(int32_t),                                               /* extBlkIncrementX */
            blkHeightFinal,                                                              /* extBlkIncrementY */
            0,                                                                           /* intBlkIncrementX */
            0,                                                                           /* intBlkIncrementY */
            0,                                                                           /* roiOffset        */
            NULL,                                                                        /* extMemPtr        */
            0,                                                                           /* extMemPtrStride  */
            NULL,                                                                        /* interMemPtr      */
            blkWidthFinal*sizeof(int32_t),                                               /* interMemPtrStride */
            0);                                                                          /* dmaQueNo          */
#elif defined(_ONLY_NMS_OUTPUT)
    assignDMAautoIncrementParams(&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*sizeof(uint8_t),                      /* roiWidth */
            graphArgs->createParams->imgFrameHeight,                                     /* roiHeight */
            blkWidthFinal*sizeof(uint8_t),                                               /* blkWidth */
            blkHeightFinal,                                                              /* blkHeight */
            blkWidthFinal*sizeof(uint8_t),                                               /* extBlkIncrementX */
            blkHeightFinal,                                                              /* extBlkIncrementY */
            0,                                                                           /* intBlkIncrementX */
            0,                                                                           /* intBlkIncrementY */
            0,                                                                           /* roiOffset        */
            NULL,                                                                        /* extMemPtr        */
            0,                                                                           /* extMemPtrStride  */
            NULL,                                                                        /* interMemPtr      */
            graphArgs->nmsArgs.outStride*sizeof(uint8_t),                                               /* interMemPtrStride */
            0);

#endif

#else

    if ( graphArgs->createParams->outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_BINARY_PACK)
    {
      graphArgs->dmaWriteBitPackedKernelArgs.numOutTransfers                                        = 1U;
      graphArgs->dmaWriteBitPackedKernelArgs.transferType                                           = EDMA_UTILS_TRANSFER_OUT;

      assignDMAautoIncrementParams(&graphArgs->dmaWriteBitPackedKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            (graphArgs->createParams->imgFrameWidth*sizeof(uint8_t)) / 8u,                      /* roiWidth */
            graphArgs->createParams->imgFrameHeight,                                     /* roiHeight */
            (blkWidthFinal*sizeof(uint8_t)) / 8u,                                               /* blkWidth */
            blkHeightFinal,                                                              /* blkHeight */
            (blkWidthFinal*sizeof(uint8_t)) / 8u,                                               /* extBlkIncrementX */
            blkHeightFinal,                                                              /* extBlkIncrementY */
            0,                                                                           /* intBlkIncrementX */
            0,                                                                           /* intBlkIncrementY */
            0,                                                                           /* roiOffset        */
            NULL,                                                                        /* extMemPtr        */
            0,                                                                           /* extMemPtrStride  */
            NULL,                                                                        /* interMemPtr      */
            graphArgs->nmsArgs.outStride * sizeof(uint8_t),                                               /* interMemPtrStride */
            1U);
#if 0
        (&graphArgs->dmaWriteBitPackedKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
        (numHorzBlocks * (graphArgs->nmsArgs.width  - NMS_FILTER_SZ + 1U )) / 8U,                      /* roiWidth */
        numVertBlocks * (graphArgs->nmsArgs.height  - NMS_FILTER_SZ + 1U),                                     /* roiHeight */
        (graphArgs->nmsArgs.width - NMS_FILTER_SZ + 1U) / 8U,                                               /* blkWidth */
        (graphArgs->nmsArgs.height - NMS_FILTER_SZ + 1U),                                                              /* blkHeight */
        (graphArgs->nmsArgs.width - NMS_FILTER_SZ + 1U) / 8U,                                               /* extBlkIncrementX */
        (graphArgs->nmsArgs.height - NMS_FILTER_SZ + 1U),                                                              /* extBlkIncrementY */
        0,                                                                           /* intBlkIncrementX */
        0,                                                                           /* intBlkIncrementY */
        0,                                                                           /* roiOffset        */
        NULL,                                                                        /* extMemPtr        */
        0,                                                                           /* extMemPtrStride  */
        NULL,                                                                        /* interMemPtr      */
        graphArgs->nmsArgs.outStride*sizeof(uint8_t) ,                                               /* interMemPtrStride */
        0);
#endif
    }
    else
    {
      graphArgs->dmaWriteKernelArgs.numOutTransfers                                        = 2U;
      graphArgs->dmaWriteKernelArgs.transferType                                           = EDMA_UTILS_TRANSFER_OUT;
      graphArgs->dmaWriteKernelArgs.numTotalBlocksInFrame                                  = graphArgs->genListArgs.numHorzBlock * graphArgs->genListArgs.numVertBlock;
      graphArgs->dmaWriteKernelArgs.triggerBlockId                                         = graphArgs->dmaWriteKernelArgs.numTotalBlocksInFrame - 1;

      assignOneShotDmaParams( &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
              2u*(graphArgs->genListArgs.maxNumElmts)*sizeof(uint16_t),        /* blkWidth */
              1u,                                                              /* blkHeight */
              NULL,                                                           /* extMemPtr */
              0,                                                              /* extMemPtrStride */
              NULL,                                                           /* interMemPtr */
              graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1].blkWidth    /* interMemPtrStride */
      );

      assignOneShotDmaParams( &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT2],
              sizeof(uint16_t),        /* blkWidth */
              1u,                                                              /* blkHeight */
              NULL,                                                           /* extMemPtr */
              0,                                                              /* extMemPtrStride */
              NULL,                                                           /* interMemPtr */
              sizeof(uint16_t)    /* interMemPtrStride */
      );
    }




#endif

    return 0;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t HARRIS_CORNER_DETECTION_32_TI_execute(
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

int32_t HARRIS_CORNER_DETECTION_32_TI_graphControl(
        const BAM_GraphMem *graphMem,
        IALG_Cmd cmd,
        const HARRIS_CORNER_DETECTION_32_TI_ControlInParams *inParams,
        HARRIS_CORNER_DETECTION_32_TI_ControlOutParams *outParams){

    BAM_NonMaxSuppress_mxn_S32_CtlArgs ctlArgs;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    if (cmd== HARRIS_CORNER_DETECTION_GET_THRESHOLD) {
        ctlArgs.ctlCmdId= BAM_NONMAXSUPPRESS_MxN_S32_CMD_GET_THRESHOLD;
    }
    else {
        ctlArgs.threshold= inParams->nmsThreshold;
        ctlArgs.ctlCmdId= BAM_NONMAXSUPPRESS_MxN_S32_CMD_SET_THRESHOLD;
    }

    status= BAM_controlNode(graphHandle, NMS_NODE, &ctlArgs);

    if (cmd== HARRIS_CORNER_DETECTION_GET_THRESHOLD) {
        outParams->nmsThreshold= ctlArgs.threshold;
        }

    return status;
}

int32_t HARRIS_CORNER_DETECTION_32_TI_dmaControl(const BAM_GraphMem *graphMem,
                                                                  const IVISION_BufDesc *inBufDesc,
                                                                  const IVISION_BufDesc *outBufDesc,
                                                                  const uint16_t *pNumKeyPoints,
                                                                  uint8_t outputFormat,
                                                                  uint8_t totalBorder)
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    BAM_DMA_OneShot_CtlArgs oneShotCtlArgs;
    uint8_t (*buf)[];

    const IVISION_BufPlanes * ivisionBufPlane= &inBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE ;

    buf= (uint8_t (*)[])ivisionBufPlane->buf;
    /* We do some adjustments to the coordinates of the upper left corner such that the DMA reads the ROI and its borders required for filtering */
    autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[
                                              (((ivisionBufPlane->frameROI.topLeft.y - (totalBorder/2u)) * ivisionBufPlane->width)) +
                                              (ivisionBufPlane->frameROI.topLeft.x - (totalBorder/2u))]);

    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);

    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }

    ivisionBufPlane= &outBufDesc->bufPlanes[0];
    buf= (uint8_t (*)[])ivisionBufPlane->buf;

    /* In normal use case, we have all these flags _ONLY_GRAD_OUTPUT, _ONLY_HARRIS_OUTPUT, _ONLY_NMS_OUTPUT turned off so we initialize the control parameters for the SINK DMA node, which is one-shot EDMA */
#if !defined(_ONLY_GRAD_OUTPUT) && !defined(_ONLY_HARRIS_OUTPUT) && !defined(_ONLY_NMS_OUTPUT)
    if ( outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST )
    {
      oneShotCtlArgs.numTransfers= 2U;
      oneShotCtlArgs.extMemPtr[0]= &((*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) +  ivisionBufPlane->frameROI.topLeft.x]);
      oneShotCtlArgs.extMemPtrStride[0] = ivisionBufPlane->width;
      /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
      /* Cast operation removes const or volatile modifier from a pointer or reference */
      /* Deviation is allowed because the elements in the array oneShotCtlArgs.extMemPtr are not pointers to constant */
      oneShotCtlArgs.extMemPtr[1]= (uint8_t*)(void*)pNumKeyPoints;
      /*RESET_MISRA("11.8")  -> Reset rule 11.8  */
      oneShotCtlArgs.extMemPtrStride[1]= 4U;

      status= BAM_controlNode(graphHandle, SINK_NODE, &oneShotCtlArgs);
    }
    else
    {
      autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
              EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE ;

      autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) +  ivisionBufPlane->frameROI.topLeft.x]);
      autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

      status= BAM_controlNode(graphHandle, SINK_NODE_BINPACK, &autoIncCtlArgs);
    }
#else
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE ;

    autoIncCtlArgs.updateParams[0].extMemPtr= &((*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) +  ivisionBufPlane->frameROI.topLeft.x];
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

    status= BAM_controlNode(graphHandle, SINK_NODE, &autoIncCtlArgs);
#endif

 Exit:
    return status;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1  */

