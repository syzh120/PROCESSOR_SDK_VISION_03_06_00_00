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
 *  @file      remap_merge_graph.c
 *
 *  @brief      This file defines the functions for Remap Merge graph
 *  @version 0.0 (Dec 2013) : Base version.
 */


/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/* #pragma RESET_MISRA ("required") */

#include "remap_merge_graph_int.h"
#include "edma_utils.h"

/* Helper Fxn Headers */
#include "bam_dma_custom_remap_merge_node.h"  /* SOURCE NODE */
/* Tile Approach */
#include "bam_remap_merge.h"                  /* KERNEL NODE  */
/* Bounding Box Approach */
#include "bam_remap.h"                        /* KERNEL NODE  */
#include "bam_alpha_blend_yuv420nv12.h"       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv422i.h"          /* KERNEL NODE  */
#include "bam_yuv_420nv12_to_422uyvy.h"       /* KERNEL NODE  */
#include "bam_yuv_422uyvy_to_420nv12.h"       /* KERNEL NODE  */

#include "edma_utils_autoincrement.h"         /* SINK NODE      */


static int32_t REMAP_MERGE_TI_initKernelsArgs(void                     *args,
                                                             BAM_BlockDimParams       *blockDimParams);

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

/* No of nodes: 5 (Source, Remap, Format Convert, Merge and Sink nodes) */
#define MAX_NO_OF_NODES     (5U)
#define MAX_NO_OF_EDGES     (7U)

#define MAX_KERNEL_ID       (255U)

#define SOURCE_NODE         (0U)
#define REMAP_MERGE_NODE    (1U)
#define SINK_NODE           (2U)


typedef enum remapMerge_bam_ti_kernelid
{
    BAM_TI_KERNELID_BB_APPROACH_DMAREAD_CUSTOM,
    BAM_TI_KERNELID_TILE_APPROACH_DMAREAD_CUSTOM,
    BAM_TI_KERNELID_REMAP,
    BAM_TI_KERNELID_YUV420NV12_TO_422UYVY,
    BAM_TI_KERNELID_422UYVY_TO_YUV420NV12,
    BAM_TI_KERNELID_ALPHABLEND_YUV420NV12,
    BAM_TI_KERNELID_ALPHABLEND_422UYVY,
    BAM_TI_KERNELID_REMAP_MERGE,
    BAM_TI_KERNELID_BB_APPROACH_DMAWRITE_CUSTOM,
    BAM_TI_KERNELID_TILE_APPROACH_DMAWRITE_CUSTOM
} REMAP_MERGE_BAM_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamRemapMergeKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernel,  &gBAM_TI_dmaCustomRemapMergeNodeReadKernelHelperFunc,
                                          "ti_bb_dma_read_custom", BAM_TI_KERNELID_BB_APPROACH_DMAREAD_CUSTOM},
    { &gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernel,  &gBAM_TI_dmaCustomRemapMergeNodeReadKernelHelperFunc,
                                          "ti_tile_dma_read_custom", BAM_TI_KERNELID_TILE_APPROACH_DMAREAD_CUSTOM},
    { &gBAM_TI_remapKernel, &gBAM_TI_remapHelperFunc,
                                           "ti_image_remap", BAM_TI_KERNELID_REMAP},
    { &gBAM_TI_yuv420nv12_to_422uyvyKernel, &gBAM_TI_yuv420nv12_to_422uyvyHelperFunc,
                                           "ti_image_yuv420_to_422ile", BAM_TI_KERNELID_YUV420NV12_TO_422UYVY},
    { &gBAM_TI_yuv422uyvy_to_420nv12Kernel, &gBAM_TI_yuv422uyvy_to_420nv12HelperFunc,
                                           "ti_image_422ile_to_yuv420", BAM_TI_KERNELID_422UYVY_TO_YUV420NV12},
    { &gBAM_TI_alphaBlendYUV420nv12Kernel, &gBAM_TI_alphaBlendYUV420nv12HelperFunc,
                                           "ti_image_alphablend_yuv420", BAM_TI_KERNELID_ALPHABLEND_YUV420NV12},
    { &gBAM_TI_alphaBlendYUV422iKernel, &gBAM_TI_alphaBlendYUV422iHelperFunc,
                                           "ti_image_alphablend_422ile", BAM_TI_KERNELID_ALPHABLEND_422UYVY},
    { &gBAM_TI_remapMergeKernel, &gBAM_TI_remapMergeHelperFunc,
                                           "ti_image_remap_merge", BAM_TI_KERNELID_REMAP_MERGE},
    { &gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernel, &gBAM_TI_dmaCustomRemapMergeNodeWriteKernelHelperFunc,
                                           "ti_bb_dma_write_custom", BAM_TI_KERNELID_BB_APPROACH_DMAWRITE_CUSTOM},
    { &gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernel, &gBAM_TI_dmaCustomRemapMergeNodeWriteKernelHelperFunc,
                                           "ti_tile_dma_write_custom", BAM_TI_KERNELID_TILE_APPROACH_DMAWRITE_CUSTOM},

};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamRemapMergeKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernel,  &gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernelExecFunc,
                                          "ti_bb_dma_read_custom", BAM_TI_KERNELID_BB_APPROACH_DMAREAD_CUSTOM},
    { &gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernel,  &gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernelExecFunc,
                                          "ti_tile_dma_read_custom", BAM_TI_KERNELID_TILE_APPROACH_DMAREAD_CUSTOM},
    { &gBAM_TI_remapKernel, &gBAM_TI_remapExecFunc,
                                          "ti_image_remap", BAM_TI_KERNELID_REMAP},
    { &gBAM_TI_yuv420nv12_to_422uyvyKernel, &gBAM_TI_yuv420nv12_to_422uyvyExecFunc,
                                           "ti_image_yuv420_to_422ile", BAM_TI_KERNELID_YUV420NV12_TO_422UYVY},
    { &gBAM_TI_yuv422uyvy_to_420nv12Kernel, &gBAM_TI_yuv422uyvy_to_420nv12ExecFunc,
                                           "ti_image_422ile_to_yuv420", BAM_TI_KERNELID_422UYVY_TO_YUV420NV12},
    { &gBAM_TI_alphaBlendYUV420nv12Kernel, &gBAM_TI_alphaBlendYUV420nv12ExecFunc,
                                           "ti_image_alphablend_yuv420", BAM_TI_KERNELID_ALPHABLEND_YUV420NV12},
    { &gBAM_TI_alphaBlendYUV422iKernel, &gBAM_TI_alphaBlendYUV422iExecFunc,
                                           "ti_image_alphablend_422ile", BAM_TI_KERNELID_ALPHABLEND_422UYVY},
    { &gBAM_TI_remapMergeKernel, &gBAM_TI_remapMergeExecFunc,
                                          "ti_image_remap_merge", BAM_TI_KERNELID_REMAP_MERGE},
    { &gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernel, &gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernelExecFunc,
                                          "ti_bb_dma_write_custom", BAM_TI_KERNELID_BB_APPROACH_DMAWRITE_CUSTOM},
    { &gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernel, &gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernelExecFunc,
                                          "ti_tile_dma_write_custom", BAM_TI_KERNELID_TILE_APPROACH_DMAWRITE_CUSTOM},
};


BAM_KernelDBdef gRemapMerge_TI_BAM_kernelDBdef =
{
    sizeof(bamRemapMergeKernelExecFuncDB) / sizeof(bamRemapMergeKernelExecFuncDB[0]),
    bamRemapMergeKernelHostDB,
    bamRemapMergeKernelExecFuncDB
};


int32_t REMAP_MERGE_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = REMAP_MERGE_GRAPH_OBJ_SIZE      ;
    memReq->graphScratchSize  = REMAP_MERGE_GRAPH_SCRATCH_SIZE  ;
    memReq->graphcontextSize  = REMAP_MERGE_GRAPH_CONTEXT_SIZE  ;
    memReq->graphArgsSize     = sizeof(REMAP_MERGE_TI_graphArgs);
    return 0;
}


int32_t REMAP_MERGE_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                 REMAP_MERGE_TI_graphCreateParams * createParams)
{
    /* Initilize the sub-handles inside the main handle */
    REMAP_MERGE_TI_graphArgs * graphArgs = (REMAP_MERGE_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle          = (BAM_GraphHandle)graphMem->graphObj;
    BAM_CreateGraphParams graphCreateParams;
    BAM_Remap_Args *remapParams = &(createParams->remapParams);
    int32_t         status = BAM_S_SUCCESS;

    BAM_NodeParams  NODELIST[MAX_NO_OF_NODES + 1U];
    BAM_EdgeParams  EDGELIST[MAX_NO_OF_EDGES + 1U];
    BAM_KernelId    kernelId;
    Format          srcFormat, dstFormat;
    uint8_t         sourceDMANode, remapNode, formatConvertNode = 0, mergeNode, sinkNode, enableTileApproach;
    uint8_t         upStreamNodeId = 0, upStreamNodePort = 0, downStreamNodePort;
    uint8_t         sourceToMergeEdgeListIdx1, sourceToMergeEdgeListIdx2, mergeNodeOutputPort2, mergeNodeOutputPort3;
    int8_t          nodelistParamIdxCurr, nodelistParamIdxPrev, edgelistParamIdx;


    if((sizeof(BAM_Yuv_420nv12_to_422uyvy_Args) != sizeof(BAM_Yuv_422uyvy_to_420nv12_Args)) ||
       (sizeof(BAM_Alpha_Blend_YUV420nv12_Args) != sizeof(BAM_Alpha_Blend_YUV422i_Args)))
    {
        /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
        /* The if() condition will currently never fail hence code is unreachable but  */
        /* as the implementation of the function changes, it will not be unreachable.   */
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
#ifdef DEBUG
        PRINTF("The primary assumption that the Format Convert Kernel Arguments of 420 and 422" \
                "or the Alpha Blend Kernel Arguments of 420 and 422 are same as eachother is wrong.\n");
#endif
        status = BAM_E_FAIL;
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        /* RESET_MISRA("14.1")  -> Reset rule 14.1     */
    }


    if(remapParams->maps.maxInputBlockSize != 0)
    {
        enableTileApproach = 0;
    }
    else
    {
        enableTileApproach = 1U;
    }

    /*------------------------------------------------------------------------------*/
    /* Tile Approach                                                                                                                                       */
    /*------------------------------------------------------------------------------*/
    if(enableTileApproach)
    {
        /*------------------------------------------------------------------------------*/
        /* Create NODELIST and EDGE LIST for Tile Approach. It should be derived from the algorithm graph */
        /*------------------------------------------------------------------------------*/
        fillNodeParams(NODELIST + SOURCE_NODE, SOURCE_NODE, BAM_TI_KERNELID_TILE_APPROACH_DMAREAD_CUSTOM,
                   (void *)&(graphArgs->dmaReadWriteKernelArgs));
        fillNodeParams(NODELIST + REMAP_MERGE_NODE, REMAP_MERGE_NODE, BAM_TI_KERNELID_REMAP_MERGE,
                   (void *)&(graphArgs->remapKernelArgs));
        fillNodeParams(NODELIST + SINK_NODE, SINK_NODE, BAM_TI_KERNELID_TILE_APPROACH_DMAWRITE_CUSTOM,
                   (void *)&(graphArgs->dmaReadWriteKernelArgs));
        fillNodeParams(NODELIST + SINK_NODE + 1U, (uint8_t)BAM_END_NODE_MARKER, (BAM_KernelId)0, (void *)NULL);

        edgelistParamIdx = 0;
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        SOURCE_NODE, BAM_SOURCE_NODE_PORT1, REMAP_MERGE_NODE, BAM_REMAP_MERGE_INPUT_PORT_IMAGE_BLOCK);
        edgelistParamIdx++;
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        SOURCE_NODE, BAM_SOURCE_NODE_PORT2, REMAP_MERGE_NODE, BAM_REMAP_MERGE_INPUT_PORT_LUT);
        edgelistParamIdx++;
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        SOURCE_NODE, BAM_SOURCE_NODE_PORT3, REMAP_MERGE_NODE, BAM_REMAP_MERGE_INPUT_PORT_MERGE_BLOCK);
        edgelistParamIdx++;
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        SOURCE_NODE, BAM_SOURCE_NODE_PORT4, REMAP_MERGE_NODE, BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK);
        edgelistParamIdx++;
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        REMAP_MERGE_NODE, BAM_REMAP_MERGE_OUTPUT_PORT, SINK_NODE, BAM_SINK_NODE_PORT1);
        edgelistParamIdx++;
        fillEdgeParams(EDGELIST + edgelistParamIdx  , (uint8_t)BAM_END_NODE_MARKER, 0U, (uint8_t)BAM_END_NODE_MARKER, 0U);

    }
    /*------------------------------------------------------------------------------*/
    /* Bounding Box Approach                                                                                                                        */
    /*------------------------------------------------------------------------------*/
    else
    {
        /*------------------------------------------------------------------------------*/
        /* Create NODELIST and EDGE LIST for Bounding Box Approach. It should be derived from the algorithm graph */
        /*------------------------------------------------------------------------------*/
        srcFormat = remapParams->maps.srcFormat;
        dstFormat = createParams->dstFormat;

        nodelistParamIdxCurr =  0;
        nodelistParamIdxPrev = (int8_t)-1;
        edgelistParamIdx     =  0;

        sourceDMANode = (uint8_t)nodelistParamIdxCurr;
        fillNodeParams(NODELIST + sourceDMANode, sourceDMANode, BAM_TI_KERNELID_BB_APPROACH_DMAREAD_CUSTOM,
                       (void *)&(graphArgs->dmaReadWriteKernelArgs));

        nodelistParamIdxCurr++;
        nodelistParamIdxPrev++;

        remapNode = (uint8_t)nodelistParamIdxCurr;
        fillNodeParams(NODELIST + remapNode, remapNode, BAM_TI_KERNELID_REMAP,
                       (void *)&(graphArgs->remapKernelArgs));

        nodelistParamIdxCurr++;
        nodelistParamIdxPrev++;

        /* Edge between DMA Source Node and Remap Node to transfer Input Image and LUT blocks. */
        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        sourceDMANode, BAM_SOURCE_NODE_PORT1,
                        remapNode,     BAM_REMAP_INPUT_PORT_IMAGE_BLOCK);
        edgelistParamIdx++;

        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        sourceDMANode, BAM_SOURCE_NODE_PORT2,
                        remapNode,     BAM_REMAP_INPUT_PORT_LUT);
        edgelistParamIdx++;

        /* In case of Merge Node, leave space for 2 Edges from Source to Merge Node in Edgelist */
        if(createParams->enableMerge == 1)
        {
            sourceToMergeEdgeListIdx1 = (uint8_t)edgelistParamIdx;
            edgelistParamIdx++;
            sourceToMergeEdgeListIdx2 = (uint8_t)edgelistParamIdx;
            edgelistParamIdx++;
        }


        /* If the src and dst formats are different, Format Convert Node is to be appended */
        if(srcFormat != dstFormat)
        {
            if(srcFormat == YUV_420SP)
            {
                kernelId           = BAM_TI_KERNELID_YUV420NV12_TO_422UYVY;
                downStreamNodePort = BAM_YUV_420NV12_TO_422UYVY_INPUT_PORT_IMG;

            }
            else if(srcFormat == YUV_422ILE)
            {
                kernelId           = BAM_TI_KERNELID_422UYVY_TO_YUV420NV12;
                downStreamNodePort = BAM_YUV_422UYVY_TO_420NV12_INPUT_PORT_IMG;

            }
            else
            {
#ifdef DEBUG
                PRINTF("Unsupported Source Format");
#endif
                status = BAM_E_UNSUPPORTED;
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto Exit;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
            }

            formatConvertNode = (uint8_t)nodelistParamIdxCurr;
            fillNodeParams(NODELIST + formatConvertNode, formatConvertNode, kernelId,
                           (void *)&(graphArgs->formatConvertKernelArgs));

            fillEdgeParams(EDGELIST + edgelistParamIdx,
                            remapNode,         BAM_REMAP_OUTPUT_PORT,
                            formatConvertNode, downStreamNodePort);

            nodelistParamIdxCurr++;
            nodelistParamIdxPrev++;
            edgelistParamIdx++;

        }

        /* If Merge is enabled, Alpha Blend Node is to be appended */
        if(createParams->enableMerge == 1)
        {
            if(dstFormat == YUV_420SP)
            {
                kernelId = BAM_TI_KERNELID_ALPHABLEND_YUV420NV12;

                if( nodelistParamIdxPrev == (int8_t)remapNode )
                {
                    upStreamNodeId   = remapNode;
                    upStreamNodePort = BAM_REMAP_OUTPUT_PORT;

                }
                else if( nodelistParamIdxPrev == (int8_t)formatConvertNode )
                {
                    upStreamNodeId   = formatConvertNode;
                    upStreamNodePort = BAM_YUV_422UYVY_TO_420NV12_OUTPUT_PORT;
                }
                else
                {
#ifdef DEBUG
                    PRINTF("Error in graph creation");
#endif
                    status = BAM_E_CUSTOMFAILEND;
                    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                    /* GOTO is used at error check to jump to end of function, to exit.   */
                    goto Exit;
                    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
                }

                downStreamNodePort   = BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG1;
                mergeNodeOutputPort2 = BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG2;
                mergeNodeOutputPort3 = BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_ALPHA;

            }
            else if(dstFormat == YUV_422ILE)
            {
                kernelId = BAM_TI_KERNELID_ALPHABLEND_422UYVY;

                if( nodelistParamIdxPrev == (int8_t)remapNode )
                {
                    upStreamNodeId   = remapNode;
                    upStreamNodePort = BAM_REMAP_OUTPUT_PORT;

                }
                else if( nodelistParamIdxPrev == (int8_t)formatConvertNode )
                {
                    upStreamNodeId   = formatConvertNode;
                    upStreamNodePort = BAM_YUV_422UYVY_TO_420NV12_OUTPUT_PORT;

                }
                else
                {
#ifdef DEBUG
                    PRINTF("Error in graph creation");
#endif
                    status = BAM_E_CUSTOMFAILEND;
                    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                    /* GOTO is used at error check to jump to end of function, to exit.   */
                    goto Exit;
                    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
                }

                downStreamNodePort   = BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG1;
                mergeNodeOutputPort2 = BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG2;
                mergeNodeOutputPort3 = BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_ALPHA;

            }
            else
            {
#ifdef DEBUG
                PRINTF("Unsupported Destination Format");
#endif
                status = BAM_E_UNSUPPORTED;
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto Exit;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
            }
            mergeNode = (uint8_t)nodelistParamIdxCurr;
            fillNodeParams(NODELIST + mergeNode, mergeNode, kernelId,
                           (void *)&(graphArgs->alphaBlendKernelArgs));

            fillEdgeParams(EDGELIST + edgelistParamIdx,
                            upStreamNodeId, upStreamNodePort,
                            mergeNode, downStreamNodePort);

            fillEdgeParams(EDGELIST + sourceToMergeEdgeListIdx1,
                            sourceDMANode, BAM_SOURCE_NODE_PORT3,
                            mergeNode,     mergeNodeOutputPort2);

            fillEdgeParams(EDGELIST + sourceToMergeEdgeListIdx2,
                            sourceDMANode, BAM_SOURCE_NODE_PORT4,
                            mergeNode,     mergeNodeOutputPort3);

            nodelistParamIdxCurr++;
            nodelistParamIdxPrev++;
            edgelistParamIdx++;

        }


        if( nodelistParamIdxPrev == (int8_t)remapNode )
        {
            upStreamNodeId   = remapNode;
            upStreamNodePort = BAM_REMAP_OUTPUT_PORT;

        }
        else if( nodelistParamIdxPrev == (int8_t)formatConvertNode )
        {
            if(srcFormat == YUV_420SP)
            {
                upStreamNodeId   = formatConvertNode;
                upStreamNodePort = BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT;

            }
            else if(srcFormat == YUV_422ILE)
            {
                upStreamNodeId   = formatConvertNode;
                upStreamNodePort = BAM_YUV_422UYVY_TO_420NV12_OUTPUT_PORT;

            }
            else
            {
                status = BAM_E_CUSTOMFAILEND;
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto Exit;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
            }

        }
        else if( nodelistParamIdxPrev == (int8_t)mergeNode )
        {
            if(dstFormat == YUV_420SP)
            {
                upStreamNodeId   = mergeNode;
                upStreamNodePort = BAM_ALPHA_BLEND_YUV420NV12_OUTPUT_PORT;

            }
            else if(dstFormat == YUV_422ILE)
            {
                upStreamNodeId   = mergeNode;
                upStreamNodePort = BAM_ALPHA_BLEND_YUV422I_OUTPUT_PORT;

            }
            else
            {
                status = BAM_E_CUSTOMFAILEND;
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto Exit;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
            }
        }
        else
        {
            status = BAM_E_CUSTOMFAILEND;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }

        sinkNode = (uint8_t)nodelistParamIdxCurr;
        fillNodeParams(NODELIST + sinkNode, sinkNode, BAM_TI_KERNELID_BB_APPROACH_DMAWRITE_CUSTOM,
                       (void *)&(graphArgs->dmaReadWriteKernelArgs));

        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        upStreamNodeId, upStreamNodePort,
                        sinkNode,       BAM_SINK_NODE_PORT1);

        nodelistParamIdxCurr++;
        edgelistParamIdx++;

        fillNodeParams(NODELIST + nodelistParamIdxCurr, (uint8_t)BAM_END_NODE_MARKER, (BAM_KernelId)0, (void *)NULL);

        fillEdgeParams(EDGELIST + edgelistParamIdx,
                        (uint8_t)BAM_END_NODE_MARKER, 0U,
                        (uint8_t)BAM_END_NODE_MARKER, 0U);
    }



    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    BAM_initKernelDB(&gRemapMerge_TI_BAM_kernelDBdef);

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gRemapMerge_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = REMAP_MERGE_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = REMAP_MERGE_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = REMAP_MERGE_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &REMAP_MERGE_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /* Initialize the structure blockDimParams that lists the processing block
    * dimensions as well as the step increment sizes used during the block
    * dimension optimization if enabled
    */
    graphCreateParams.blockDimParams.blockWidth           = remapParams->maps.outputBlockDim.width;
    graphCreateParams.blockDimParams.blockHeight          = remapParams->maps.outputBlockDim.height;

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

#if 0
    BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);
#endif

    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/
Exit:
    if (status== BAM_E_INVALID_MEM_SIZE)
    {
#ifdef DEBUG
      PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
#endif
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
#ifdef DEBUG
      PRINTF("Graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
        graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
#endif
    }
    else if (status != BAM_S_SUCCESS)
    {
#ifdef DEBUG
      PRINTF("Graph construction failed!!!");
#endif
    }
    else
    {
#ifdef DEBUG
      PRINTF("BAM_createGraph passed!!!");
#endif
      /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}

int32_t REMAP_MERGE_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const IVISION_InBufs *inBuf, const IVISION_OutBufs *outBuf , uint8_t sinkNodeId)
{
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    int32_t status = BAM_S_SUCCESS;
    IVISION_InBufs tempInBuf = *inBuf;
    IVISION_OutBufs tempOutBuf = *outBuf;

    /* Source Node Id is always zero */
    status = BAM_controlNode(graphHandle, 0, (void *)&tempInBuf);

    if (status != BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    status= BAM_controlNode(graphHandle, sinkNodeId, (void *)&tempOutBuf);

 Exit:
    return status;
}


/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t REMAP_MERGE_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
    uint16_t blockWidth, blockHeight;
    Format srcFormat, dstFormat;
    int32_t status = BAM_S_SUCCESS;

    REMAP_MERGE_TI_graphArgs             *graphArgs               =  (REMAP_MERGE_TI_graphArgs*)args;
    REMAP_MERGE_TI_graphCreateParams     *createParams            =  (graphArgs->createParams);
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *dmaReadWriteKernelArgs  = &(graphArgs->dmaReadWriteKernelArgs);
    BAM_Remap_Args                       *remapKernelArgs         = &(graphArgs->remapKernelArgs);
    BAM_Memcpy_Args                      *memcpyKernelArgs        = &(graphArgs->memcpyKernelArgs);
    BAM_Yuv_420nv12_to_422uyvy_Args      *formatConvertKernelArgs = &(graphArgs->formatConvertKernelArgs);
    BAM_Alpha_Blend_YUV420nv12_Args      *alphaBlendKernelArgs    = &(graphArgs->alphaBlendKernelArgs);
    BAM_Remap_Args                       *remapParams             = &(createParams->remapParams);

    blockWidth  = blockDimParams->blockWidth;
    blockHeight = blockDimParams->blockHeight;

    srcFormat = remapParams->maps.srcFormat;
    dstFormat = createParams->dstFormat;

    graphArgs->dstFormat   = dstFormat;
    graphArgs->enableMerge = createParams->enableMerge;

    *dmaReadWriteKernelArgs  = *createParams;
    *remapKernelArgs         = *remapParams;

    memcpyKernelArgs->width       = blockWidth;
    memcpyKernelArgs->height      = blockHeight;
    memcpyKernelArgs->format      = srcFormat;

    formatConvertKernelArgs->width       = blockWidth;
    formatConvertKernelArgs->height      = blockHeight;

    if(srcFormat == YUV_420SP) {
        formatConvertKernelArgs->in_stride   = blockWidth;
        formatConvertKernelArgs->out_stride  = (uint16_t)((uint16_t)blockWidth << (uint16_t)1U);
    }
    else if(srcFormat == YUV_422ILE) {
        formatConvertKernelArgs->in_stride   = (uint16_t)((uint16_t)blockWidth << (uint16_t)1U);
        formatConvertKernelArgs->out_stride  = blockWidth;
    }
    else {
        formatConvertKernelArgs->in_stride   = 0U;
        formatConvertKernelArgs->out_stride  = 0U;
    }

    alphaBlendKernelArgs->width          = blockWidth;
    alphaBlendKernelArgs->height         = blockHeight;

    if (dstFormat == YUV_420SP) {
        alphaBlendKernelArgs->in_img1_stride = blockWidth;
        alphaBlendKernelArgs->in_img2_stride = blockWidth;
        alphaBlendKernelArgs->out_stride     = blockWidth;
    } else if(dstFormat == YUV_422ILE) {
        alphaBlendKernelArgs->in_img1_stride = (uint16_t)((uint16_t)blockWidth << (uint16_t)1U);
        alphaBlendKernelArgs->in_img2_stride = (uint16_t)((uint16_t)blockWidth << (uint16_t)1U);
        alphaBlendKernelArgs->out_stride     = (uint16_t)((uint16_t)blockWidth << (uint16_t)1U);
    }
    else
    {
        alphaBlendKernelArgs->in_img1_stride = 0U;
        alphaBlendKernelArgs->in_img2_stride = 0U;
        alphaBlendKernelArgs->out_stride     = 0U;
    }

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t REMAP_MERGE_TI_execute(
                                    BAM_GraphMem     *graphMem,
                                    const BAM_InArgs *inArgs,
                                    BAM_OutArgs      *outArgs)
  {
    BAM_ProcessHints hints;
    int32_t status = BAM_S_SUCCESS;

    /* Specify which processing schedule is the best, unsupported for now */
    hints.priority= BAM_DATA_FIRST;

    BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

    return status;
}

