/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VPS_GRAPH_H_
#define VPS_GRAPH_H_

#include <ti/drv/vps/include/common/bsp_types.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define VGRAPH_DEF_ALIGN       ((UInt32) 16U)
#define GRAPH_INVALID_NODE_ID  ((UInt32) 0U)
#define GRAPH_MAX_NODES        ((UInt32) 80U)
#define GRAPH_MAX_NUM_PATHS    ((UInt32) 20U)

typedef enum
{
    VGRAPH_NODE_DISABLE = 0,
    VGRAPH_NODE_ENABLE  = 1,
    VGRAPH_NODE_CHECK   = 2
} Vgraph_mode;

typedef enum
{
    VGRAPH_NODETYPE_DUMMY,
    VGRAPH_NODETYPE_VPDMA,   /* VPDMA channels */
    VGRAPH_NODETYPE_VIPPORT, /* VIP Inputs */
    VGRAPH_NODETYPE_VIPMUX,  /* VIP Muxes */
    VGRAPH_NODETYPE_SC,      /* VIP Muxes */
    VGRAPH_NODETYPE_CSC,     /* VIP Muxes */
    VGRAPH_NODETYPE_DSSVID,  /* DSS Pipelines */
    VGRAPH_NODETYPE_DSSMGR,  /* DSS overlay manager */
    VGRAPH_NODETYPE_DSSOUT,  /* DSS output */
    VGRAPH_NODETYPE_MAX_NODETYPE
} Vgraph_NodeTypes;

typedef struct Vgraph_nodeInfo_t Vgraph_nodeInfo;
typedef struct Vgraph_nodeSet_t
{
    UInt32           numNodes;
    /**< Number of input/output nodes */
    Vgraph_nodeInfo *node[GRAPH_MAX_NUM_PATHS];
    /**< Pointer to the input/output node */
    UInt32           isEnabled[GRAPH_MAX_NUM_PATHS];
    /**< Flag to indicate whether input/output is enabled or not. */
} Vgraph_nodeSet;

typedef enum
{
    SINGLE_IN,
    MULTI_IN,
    EMPTY_IN
} Vgraph_NodeInputType;

typedef enum
{
    SINGLE_OUT,
    MULTI_OUT,
    EMPTY_OUT
} Vgraph_NodeOutputType;

struct Vgraph_nodeInfo_t
{
    /* Will be used to select config structure from the handleCreateParams */
    UInt32                nodeNum;

    /* Tree-connections */
    Vgraph_NodeInputType  inType;
    Vgraph_NodeOutputType outType;

    /* SI/SO/MI/MO */
    UInt32                nodeType;

    /* For multiple handles */
    /* UInt32          isMH; */
    /* UInt32          openCount; */

    /* List of HAL functions required while configuring */
    /* FuncPtrList*    halPtr; */
    void                 *corePtr;

    UInt32                isDummy;
    UInt32                inUse;

    /* Need to check how to track state when in multi-handle mode */
    /* void*           fnPtr_isAvailable;  */
    /* required when sharing an IP across two handles */
    /* void*           fnPtr_isRunning;    */
    /* required when sharing an IP across two handles */
    /* and using different list for different handles */
    Vgraph_nodeSet        input;
    Vgraph_nodeSet        output;

    /* TODO: Need to check how to track state when in multi-handle mode */
};

typedef struct
{
    UInt32           numNodes;
    Vgraph_nodeInfo *list;
} Vgraph_nodeInfoList;

/**
 * \brief Structure containing edge information. Edge is a connection
 *  between two nodes i.e. two modules (like CIG and Blend) in VPS.
 *  VPS can be represented by a graph, where each
 *  module is node and edge is present between two nodes if they are connected.
 *  All VPS paths can be configured in one shot by IOCTL
 *  IOCTL_VPSCORE_DCTRL_SET_CONFIG.
 *  This IOCTL takes the array of edges connected between nodes. This structure
 *  is used to specify individual edge information.
 */
typedef struct
{
    UInt32 startNode;
    /**< Starting node (VPS Module) of the edge */
    UInt32 endNode;
    /**< End node (VPS Module) of the edge */
} Vgraph_edgeInfo;

typedef struct
{
    UInt32           numEdges;
    /**< End node (VPS Module) of the edge */

    Vgraph_edgeInfo *list;
    /**< Starting node (VPS Module) of the edge */
} Vgraph_edgeInfoList;

typedef struct
{
    Vgraph_nodeInfoList *nodeList;
    Vgraph_edgeInfoList *edgeList;
} Vgraph_Info;

Vgraph_Info *Vgraph_Init(const Vgraph_nodeInfoList *inNodeList,
                         const Vgraph_edgeInfoList *inEdgeList,
                         Vgraph_Info               *graphHandle);

Int32 Vgraph_DeInit(Vgraph_Info *graphHandle);

Vgraph_nodeInfo *Vgraph_getNodeInfo(const Vgraph_nodeInfoList *nodeList,
                                    UInt32                     cnt);

Int32 Vgraph_allocNodes(const Vgraph_nodeInfoList *nodeList,
                        const Vgraph_edgeInfoList *edgeList,
                        Vgraph_mode                mode);

Int32 Vgraph_getPath(const Vgraph_nodeInfoList *inNodeList,
                     const Vgraph_edgeInfoList *inEdgeList,
                     Vgraph_nodeInfoList       *outNodeList,
                     Vgraph_edgeInfoList       *outEdgeList,
                     UInt32                     maxOutNodeCnt,
                     UInt32                     maxOutEdgeCnt);

Int32 Vgraph_freePath(Vgraph_nodeInfoList *nodeList,
                      Vgraph_edgeInfoList *edgeList);

#if defined(__GNUC__) && !defined(__ti__)
/* define local functions */
#else
static void Vgraph_stackReset(void);

static void Vgraph_stackPush(Vgraph_nodeInfo *node);

static void Vgraph_stackPop(void);

static UInt32 Vgraph_stackIsVisited(const Vgraph_nodeInfo *node);
#endif

Int32 Vgraph_stackIsLastNode(const Vgraph_nodeInfo *currNode, UInt32 isForward);

void Vgraph_stackInitTraverser(Vgraph_nodeInfo *node);

Vgraph_nodeInfo *Vgraph_getNextNodeToTraverse(UInt32 isForward);

Bool Vgraph_isNodeInputAvailable(const Vgraph_nodeInfoList *nodeList,
                                 UInt32                     nodeNum);

Bool Vgraph_isNodeOutputAvailable(const Vgraph_nodeInfoList *nodeList,
                                  UInt32                     nodeNum);

void Vgraph_initTraverser(Vgraph_nodeInfo *node);

Vgraph_nodeInfo *Vgraph_getNextChildNode(const Vgraph_nodeInfo *currNode,
                                         UInt32                 isForward);

Vgraph_nodeInfo *Vgraph_stackPeak(UInt32 *stNum);

Int32 Vgraph_getEnabledIndex(const UInt32 *array, UInt32 size);

void Vgraph_AddEdge(Vgraph_edgeInfo *edge, UInt32 startNode, UInt32 endNode);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_GRAPH_H_ */

