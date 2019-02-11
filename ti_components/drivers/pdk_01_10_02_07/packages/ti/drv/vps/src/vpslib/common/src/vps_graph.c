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

/**
 *  \file vps_graph.c
 *
 *  \brief VPS Graph Core
 *  Supports graph functions for resource management in VPS core
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/src/vpslib/common/vps_graph.h>

/* ========================================================================== */
/*                         Internal Function Declarations                     */
/* ========================================================================== */

static Int32 Vgraph_Connect(const Vgraph_nodeInfoList *inNodeList,
                            const Vgraph_edgeInfoList *inEdgeList);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/* Helper function */
static Int32 Vgraph_Connect(const Vgraph_nodeInfoList *inNodeList,
                            const Vgraph_edgeInfoList *inEdgeList)
{
    Vgraph_nodeInfo *nodes = inNodeList->list;
    Vgraph_edgeInfo *edges = inEdgeList->list;
    UInt32           cnt, startNode, endNode, index1, index2;
    for (cnt = 0; cnt < inNodeList->numNodes; cnt++)
    {
        BspUtils_memset(&nodes[cnt].input, 0, sizeof (Vgraph_nodeSet));
        BspUtils_memset(&nodes[cnt].output, 0, sizeof (Vgraph_nodeSet));
    }

    for (cnt = 0U; cnt < inEdgeList->numEdges; cnt++)
    {
        startNode = edges[cnt].startNode;
        endNode   = edges[cnt].endNode;
        /* End Node is output node for the start Node so update
         * information in start node*/
        index1 = nodes[startNode].output.numNodes;
        nodes[startNode].output.node[index1] = &nodes[endNode];
        nodes[startNode].output.numNodes++;
        GT_assert(VpsTrace, (index1 < GRAPH_MAX_NUM_PATHS));

        /* Start Node is input node for the end Node so update
         * information in end node*/
        index2 = nodes[endNode].input.numNodes;
        nodes[endNode].input.node[index2] = &nodes[startNode];
        nodes[endNode].input.numNodes++;
        GT_assert(VpsTrace, (index2 < GRAPH_MAX_NUM_PATHS));

        /* Dummy node's input is always enabled */
        if ((TRUE == nodes[endNode].isDummy) &&
            (TRUE == nodes[startNode].isDummy))
        {
            nodes[startNode].output.isEnabled[index1] = (UInt32) TRUE;
            nodes[endNode].input.isEnabled[index2]    = (UInt32) TRUE;
        }
    }

    return BSP_SOK;
}

/** \brief Creates static DSS topology for the fixed edges/nodes. There
 *  are some dummy nodes in the DSS topology. Input and output of these
 *  nodes are always enabled and cannot be changed. This function creates
 *  this static table.
 *  Called at the init time only
 */
Vgraph_Info *Vgraph_Init(const Vgraph_nodeInfoList *inNodeList,
                         const Vgraph_edgeInfoList *inEdgeList,
                         Vgraph_Info               *graphHandle)
{
    GT_assert(VpsTrace, (graphHandle != NULL));
    GT_assert(VpsTrace, (graphHandle->nodeList != NULL));
    GT_assert(VpsTrace, (graphHandle->edgeList != NULL));

    GT_assert(VpsTrace, (inNodeList != NULL));
    GT_assert(VpsTrace, (inEdgeList != NULL));

    graphHandle->nodeList->numNodes = inNodeList->numNodes;
    graphHandle->edgeList->numEdges = inEdgeList->numEdges;
    graphHandle->nodeList->list     = inNodeList->list;
    graphHandle->edgeList->list     = inEdgeList->list;

    Vgraph_Connect(inNodeList, inEdgeList);
    return graphHandle;
}

Int32 Vgraph_DeInit(Vgraph_Info *graphHandle)
{
    return BSP_SOK;
}

/** \brief Function to get the pointer to node for the given index
 */
Vgraph_nodeInfo *Vgraph_getNodeInfo(const Vgraph_nodeInfoList *nodeList,
                                    UInt32                     cnt)
{
    Vgraph_nodeInfo *node = NULL;
    if (cnt < nodeList->numNodes)
    {
        node = &nodeList->list[cnt];
    }
    return (node);
}

/** \brief This function allocates nodes within the CORE by enabling
 *  specified edges.
 *
 *  To enable an edge, it enables output of source node and
 *  enables input of the target node.
 *
 *  Returns error if a node is already active.
 *
 *  TODO: First edge is assumed as input, Why/How to disable edges?,
 *  Multiple handle support.
 *  TODO: If FAIL, run through again and disable if anything was enabled.
 */

Bool Vgraph_isNodeInputAvailable(const Vgraph_nodeInfoList *nodeList,
                                 UInt32                     nodeNum)
{
    UInt32           j;
    Bool             retVal  = TRUE;
    Vgraph_nodeInfo *curNode = Vgraph_getNodeInfo(nodeList, nodeNum);
    if (NULL == curNode)
    {
        retVal = FALSE;
    }
    else
    {
        for (j = 0; j < curNode->input.numNodes; j++)
        {
            if (VGRAPH_NODE_ENABLE == curNode->input.isEnabled[j])
            {
                retVal = FALSE;
                break;
            }
        }
    }
    return retVal;
}

Bool Vgraph_isNodeOutputAvailable(const Vgraph_nodeInfoList *nodeList,
                                  UInt32                     nodeNum)
{
    UInt32           j;
    Bool             retVal  = TRUE;
    Vgraph_nodeInfo *curNode = Vgraph_getNodeInfo(nodeList, nodeNum);
    if (NULL == curNode)
    {
        retVal = FALSE;
    }
    else
    {
        for (j = 0; j < curNode->output.numNodes; j++)
        {
            if (VGRAPH_NODE_ENABLE == curNode->output.isEnabled[j])
            {
                retVal = FALSE;
                break;
            }
        }
    }
    return retVal;
}

Int32 Vgraph_allocNodes(const Vgraph_nodeInfoList *nodeList,
                        const Vgraph_edgeInfoList *edgeList,
                        Vgraph_mode                mode)
{
    UInt32           i, j;
    Int32            retVal        = BSP_SOK;
    Vgraph_edgeInfo *inputEdgeList = edgeList->list;
    for (i = 0; i < edgeList->numEdges; i++)
    {
        Vgraph_nodeInfo *startNode = Vgraph_getNodeInfo(
            nodeList, inputEdgeList[i].startNode);
        GT_assert(VpsTrace, (startNode != NULL));
        Vgraph_nodeInfo *endNode = Vgraph_getNodeInfo(
            nodeList, inputEdgeList[i].endNode);
        GT_assert(VpsTrace, (endNode != NULL));
        if ((startNode->nodeNum == GRAPH_INVALID_NODE_ID) &&
            (endNode->nodeNum == GRAPH_INVALID_NODE_ID))
        {
            break;
        }

        /* TODO: Multiple connections from different path probably does not work
        **/
        /*      here. Will it be ever required? */
        /* Example: One handle connects one source for blender, Second handle */
        /*         connects second source for blender - Is such a case required?
        **/
        if (SINGLE_OUT == startNode->outType)
        {
            UInt32 inUse = FALSE;
            for (j = 0; j < startNode->output.numNodes; j++)
            {
                if (VGRAPH_NODE_ENABLE == startNode->output.isEnabled[j])
                {
                    inUse = (UInt32) TRUE;
                    break;
                }
            }
            if ((FALSE == inUse) || (VGRAPH_NODE_DISABLE == mode))
            {
                for (j = 0; j < startNode->output.numNodes; j++)
                {
                    if (startNode->output.node[j] == endNode)
                    {
                        startNode->output.isEnabled[j] = mode;
                        break;
                    }
                }
                if (j == startNode->output.numNodes)
                {
                    retVal = BSP_EFAIL;
                }
            }
        }
        else if (MULTI_OUT == startNode->outType)
        {
            for (j = 0; j < startNode->output.numNodes; j++)
            {
                if (startNode->output.node[j] == endNode)
                {
                    startNode->output.isEnabled[j] = mode;
                    break;
                }
            }
            if (j == startNode->output.numNodes)
            {
                retVal = BSP_EFAIL;
            }
        }
        else
        {
            /*Do nothing */
        }

        if (SINGLE_IN == endNode->inType)
        {
            UInt32 inUse = FALSE;
            for (j = 0; j < endNode->input.numNodes; j++)
            {
                if (VGRAPH_NODE_ENABLE == endNode->input.isEnabled[j])
                {
                    inUse = (UInt32) TRUE;
                    break;
                }
            }
            if ((FALSE == inUse) || (VGRAPH_NODE_DISABLE == mode))
            {
                for (j = 0; j < endNode->input.numNodes; j++)
                {
                    if (endNode->input.node[j] == startNode)
                    {
                        endNode->input.isEnabled[j] = mode;
                        break;
                    }
                }
                if (j == endNode->input.numNodes)
                {
                    retVal = BSP_EFAIL;
                }
            }
        }
        else if (MULTI_IN == endNode->inType)
        {
            for (j = 0; j < endNode->input.numNodes; j++)
            {
                if (endNode->input.node[j] == startNode)
                {
                    endNode->input.isEnabled[j] = mode;
                    break;
                }
            }
            if (j == endNode->input.numNodes)
            {
                retVal = BSP_EFAIL;
            }
        }
        else
        {
            /*Do nothing */
        }
    }

    /* Special case: VPDMA_MI */
    if ((VGRAPH_NODE_DISABLE != mode) && (retVal == BSP_SOK))
    {
        for (i = 0; i < edgeList->numEdges; i++)
        {
            Vgraph_nodeInfo *startNode = Vgraph_getNodeInfo(
                nodeList, inputEdgeList[i].startNode);
            GT_assert(VpsTrace, (startNode != NULL));
            Vgraph_nodeInfo *endNode = Vgraph_getNodeInfo(
                nodeList, inputEdgeList[i].endNode);
            GT_assert(VpsTrace, (endNode != NULL));
            if ((startNode->nodeNum == 0) && (endNode->nodeNum == 0))
            {
                break;
            }
            if ((VGRAPH_NODETYPE_VPDMA == endNode->nodeType) &&
                (MULTI_IN == endNode->inType))
            {
                UInt32 isFullyConnected = TRUE;
                for (j = 0; j < endNode->input.numNodes; j++)
                {
                    if (mode != endNode->input.isEnabled[j])
                    {
                        isFullyConnected = (UInt32) FALSE;
                    }
                }
                if (FALSE == isFullyConnected)
                {
                    retVal = BSP_EFAIL;
                }
            }
        }
    }
    return retVal;
}

/**
 * findPath()
 */
/**
 * Inputs
 * PORTA/B_08/16/24
 * isCSCEnabled
 * isSCEnabled
 */
/**
 * Algo:
 * Decide FirstNode
 * Decide LastNodes
 * curNode = FirstNode
 * if(isCSCEnabled) {join curNode to CSC; curNode = CSC}
 * if(isSCEnabled)  {join curNode to SC; curNode = SC}
 * foreach(LastNode_option1, LastNode_option2)
 * {
 * join curNode to LastNode
 * if (successful) break
 * else next
 * }
 */

/** \brief This function gets a list of valid nodes in an edge list and
 *  also enable the input in each entry. Fill in VpsCore_VipPathObj
 *
 *  Should be called only after Vgraph_allocNodes() is successful
 *
 *  TODO: Connections should be made in this function and not copied from
 *  main graph (as is done currently) since this will fail for multiple handle
 *  scenarios.
 */
Int32 Vgraph_getPath(const Vgraph_nodeInfoList *inNodeList,
                     const Vgraph_edgeInfoList *inEdgeList,
                     Vgraph_nodeInfoList       *outNodeList,
                     Vgraph_edgeInfoList       *outEdgeList,
                     UInt32                     maxOutNodeCnt,
                     UInt32                     maxOutEdgeCnt)
{
    UInt32 i, j;
    UInt32 pathEdgeCount          = inEdgeList->numEdges;
    UInt32 pathNodeCount          = 0;
    UInt32 numInNodes             = inNodeList->numNodes;
    UInt32 nodes[GRAPH_MAX_NODES] = {0};

    for (i = 0; i < inEdgeList->numEdges; i++)
    {
        j        = inEdgeList->list[i].startNode;
        nodes[j] = 1U;
        j        = inEdgeList->list[i].endNode;
        nodes[j] = 1U;
    }

    for (i = 0; i < numInNodes; i++)
    {
        if (nodes[i] == 1U)
        {
            pathNodeCount++;
        }
    }

    GT_assert(VpsTrace, (pathNodeCount < maxOutNodeCnt));
    outNodeList->numNodes = pathNodeCount;

    GT_assert(VpsTrace, (outNodeList->list != NULL));

    GT_assert(VpsTrace, (pathEdgeCount < maxOutEdgeCnt));
    outEdgeList->numEdges = pathEdgeCount;
    GT_assert(VpsTrace, (outEdgeList->list != NULL));

    for (i = 0; i < pathEdgeCount; i++)
    {
        outEdgeList->list[i].startNode =
            inEdgeList->list[i].startNode;
        outEdgeList->list[i].endNode =
            inEdgeList->list[i].endNode;
    }

    j = 0;
    for (i = 0; i < numInNodes; i++)
    {
        if (nodes[i] == 1U)
        {
            BspUtils_memcpy((void *) &outNodeList->list[j],
                            (void *) &inNodeList->list[i],
                            sizeof (Vgraph_nodeInfo));

            /* Reset connection info from the original graph */
            BspUtils_memset((void *) (outNodeList->list[j].input.node), 0,
                            sizeof (Vgraph_nodeInfo *) * GRAPH_MAX_NUM_PATHS);
            BspUtils_memset((void *) (outNodeList->list[j].output.node), 0,
                            sizeof (Vgraph_nodeInfo *) * GRAPH_MAX_NUM_PATHS);
            /* BspUtils_memset( (void *)(outNodeList->list[j].input.isEnabled),
            **/
            /* 0, sizeof(UInt32)*GRAPH_MAX_NUM_PATHS); */
            /* BspUtils_memset( (void *)(outNodeList->list[j].output.isEnabled),
            **/
            /* 0, sizeof(UInt32)*GRAPH_MAX_NUM_PATHS); */
            j++;
        }
    }

    return BSP_SOK;
}

Int32 Vgraph_freePath(Vgraph_nodeInfoList *nodeList,
                      Vgraph_edgeInfoList *edgeList)
{
    if (NULL != nodeList->list)
    {
        nodeList->numNodes = 0;
        nodeList->list     = NULL;
    }
    if (NULL != edgeList->list)
    {
        edgeList->numEdges = 0;
        edgeList->list     = NULL;
    }
    return BSP_SOK;
}

typedef struct Vgraph_stack_t
{
    Vgraph_nodeInfo *node[GRAPH_MAX_NODES];
    /**< Array of node pointers */
    Int32            stNum[GRAPH_MAX_NODES];
    /**< Keeps track of which child of this node is next to be visited, on
     *   the stack for a node. */
    UInt8            isVisited[GRAPH_MAX_NODES];
    /**< Flag keeps track of whether given node is visited or not */
    Int32            top;
    /**< Top marker of the stack */
} Vgraph_stack;
Vgraph_stack nodeStack;

static void Vgraph_stackReset(void);
static void Vgraph_stackPush(Vgraph_nodeInfo *node);
static void Vgraph_stackPop(void);
static UInt32 Vgraph_stackIsVisited(const Vgraph_nodeInfo *node);
Int32 Vgraph_stackIsLastNode(const Vgraph_nodeInfo *currNode, UInt32 isForward);

void Vgraph_initTraverser(Vgraph_nodeInfo *node)
{
    /* Initialize Stack */
    Vgraph_stackReset();

    /* Push root node onto stack */
    Vgraph_stackPush(node);
}

static void Vgraph_stackReset(void)
{
    BspUtils_memset(&nodeStack, 0, sizeof (nodeStack));
    nodeStack.top = (-(int32_t)1);

    /* Initialize All stack numbers with -1 */
    BspUtils_memset(nodeStack.stNum, 0, sizeof (UInt32) * GRAPH_MAX_NODES);
    BspUtils_memset(nodeStack.isVisited, 0, sizeof (GRAPH_MAX_NODES));
}

/* Push a node on the stack */
static void Vgraph_stackPush(Vgraph_nodeInfo *node)
{
    nodeStack.top++;
    nodeStack.node[nodeStack.top] = node;
}

/* Remove top node from the stack */
static void Vgraph_stackPop(void)
{
    /* Remove the node from the stack */
    nodeStack.stNum[nodeStack.top] = 0;
    nodeStack.node[nodeStack.top]  = NULL;
    nodeStack.top--;
}

static UInt32 Vgraph_stackIsVisited(const Vgraph_nodeInfo *node)
{
    UInt32 visited = TRUE;

    if (0 == nodeStack.isVisited[node->nodeNum])
    {
        visited = (UInt32) FALSE;
    }

    return (visited);
}

Int32 Vgraph_stackIsLastNode(const Vgraph_nodeInfo *currNode, UInt32 isForward)
{
    Int32 ret = (Int32) TRUE;

    if (((TRUE == isForward) && (0 != currNode->output.numNodes)) ||
        ((FALSE == isForward) && (0 != currNode->input.numNodes)))
    {
        ret = (Int32) FALSE;
    }

    return (ret);
}

/* Function to get the next enabled node for the currNode */
Vgraph_nodeInfo *Vgraph_getNextChildNode(const Vgraph_nodeInfo *currNode,
                                         UInt32                 isForward)
{
    Vgraph_nodeInfo *node      = NULL;
    UInt32           isEnabled = TRUE;
    UInt32           nodeNum, nextNodeNum;
    UInt32           loopEnd = 1U;

    nodeNum     = nodeStack.top;
    nextNodeNum = (UInt32) nodeStack.stNum[nodeNum];
    do
    {
        /* Traversing from input Node to Venc Nodes */
        if (TRUE == isForward)
        {
            /* Get the next node from the output nodes */
            if (nextNodeNum < currNode->output.numNodes)
            {
                node      = currNode->output.node[nextNodeNum];
                isEnabled = currNode->output.isEnabled[nextNodeNum];
            }
            else
            {
                loopEnd = 0;
            }
        }
        else  /* Traversing from Venc Nodes to input node */
        {
            /* Get the next node from the input nodes */
            if (nextNodeNum < currNode->input.numNodes)
            {
                node      = currNode->input.node[(nextNodeNum)];
                isEnabled = currNode->input.isEnabled[nextNodeNum];
            }
            else
            {
                loopEnd = 0;
            }
        }
        if (0U == loopEnd)
        {
            break;
        }
        nextNodeNum += 1U;
    } while (FALSE == isEnabled);

    if (FALSE == isEnabled)
    {
        node = NULL;
    }
    else
    {
        nodeStack.stNum[nodeNum] = (Int32) nextNodeNum;
    }
    return (node);
}

/* Get the top node on the stack */
Vgraph_nodeInfo *Vgraph_stackPeak(UInt32 *stNum)
{
    *stNum = (UInt32) nodeStack.stNum[nodeStack.top];
    return (nodeStack.node[nodeStack.top]);
}

Vgraph_nodeInfo *Vgraph_getNextNodeToTraverse(UInt32 isForward)
{
    UInt32           nodeNum;
    Vgraph_nodeInfo *currNode = NULL, *nextNode = NULL;

    while (nodeStack.top > (-(int32_t)1))
    {
        /* Get the stack top node */
        currNode = Vgraph_stackPeak(&nodeNum);

        if (FALSE == Vgraph_stackIsVisited(currNode))
        {
            /* If current node is ot visited, return it to the caller. */
            break;
        }
        else
        {
            /* Get the Next Node */
            nextNode = Vgraph_getNextChildNode(currNode, isForward);

            /* If next node is not null, push it onto stack so that it can
             * be traversed */
            if (NULL != nextNode)
            {
                /* Push the start node onto stack */
                Vgraph_stackPush(nextNode);
            }
            else
            {
                /* Remove the node from the stack */
                Vgraph_stackPop();
            }
        }
    }
    if ((-(int32_t)1) == nodeStack.top)
    {
        currNode = NULL;
    }

    if (NULL != currNode)
    {
        nodeNum = currNode->nodeNum;
        nodeStack.isVisited[nodeNum] = (UInt8) 1;
    }

    return (currNode);
}

Int32 Vgraph_getEnabledIndex(const UInt32 *array, UInt32 size)
{
    UInt32 i;
    Int32  retVal = BSP_EFAIL;

    for (i = 0; i < size; i++)
    {
        if ((UInt32) 0 != array[i])
        {
            retVal = (Int32) i;
            break;
        }
    }
    return retVal;
}

void Vgraph_AddEdge(Vgraph_edgeInfo *edge, UInt32 startNode, UInt32 endNode)
{
    if (startNode != endNode)
    {
        edge->startNode = startNode;
        edge->endNode   = endNode;
    }
}

