/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 *
 */

/**
 *  \file       pmhal_clocktree.c
 *
 *  \brief      This file contains Acyclic Graph Abstract Data Type,
 *              it has the graph node API for tree traversal
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "pmhal_clocktree.h"
#include "hw_pmhal_clocktree_data.h"
#include "hw_pmhal_data.h"
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**<
 *  \brief   Internal Function to get the Node Pointer.
 *
 *  \param   graph                      Pointer to the clock tree
 *  \param   id                         Clock Tree node ID
 *
 *  \return  pmhalClockTreeNodePtr     Pointer to the node.
 */
static pmhalClockTreeNodePtr PmhalClocktreeGetNodeFast(
    pmhalClockTreePtr    graph,
    pmhalClockTreeNodeId id);

/**<
 *  \brief   Internal Function to get the Edges Pointer.
 *
 *  \param   graph                      Pointer to the clock tree
 *  \param   id                         Clock Tree node ID
 *
 *  \return  pmhalClockTreeOutputEdgePtr     Pointer to the node edges.
 */
static pmhalClockTreeOutputEdgePtr PmhalClocktreeGetEdgeFast(
    pmhalClockTreePtr    graph,
    pmhalClockTreeNodeId id);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALClockTreeValidNode(pmhalClockTreeNodeId id)
{
    pmErrCode_t       result = PM_SUCCESS;
    pmhalClockTreePtr graph  = &prcmGraph;
    /* Check if the clock tree node ID is valid an with in the maximum limits */
    if (id >= graph->nodesMax)
    {
        result = PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID;
    }
    else
    {
        result = PM_SUCCESS;
    }

    return result;
}

pmhalNodeType_t PMHALClockTreeGetNodeType(pmhalClockTreeNodeId id)
{
    pmhalNodeType_t       result = PMHAL_UNDEF;
    pmhalClockTreePtr     graph  = &prcmGraph;
    pmhalClockTreeNodePtr nodePtr;
    pmErrCode_t           retVal = PMHALClockTreeValidNode(id);
    /* Each node has its associated type which defines if the node is a module,
     * mux, dpll etc. This is used to traverse the clock tree and treat
     * different types of nodes appropriately.
     */
    if (PM_SUCCESS == retVal)
    {
        /* Find the pointer to the element in the node ID list */
        nodePtr = PmhalClocktreeGetNodeFast(graph, id);
        /* From the node pointer find the node property and node type */
        result = (pmhalNodeType_t) (nodePtr->prop)->ptype;
    }
    return result;
}

pmErrCode_t PMHALClockTreeGetNode(pmhalClockTreeNodeId   id,
                                  pmhalClockTreeNodePtr *nodePtr)
{
    pmErrCode_t       retStatus = PM_SUCCESS;
    pmhalClockTreePtr graph     = &prcmGraph;
    if (nodePtr == NULL)
    {
        retStatus = PM_BADARGS;
    }
    if (PM_SUCCESS == retStatus)
    {
        retStatus = PMHALClockTreeValidNode(id);
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Get the pointer to the node element based on the ID given by the
         * user. The node element contains essential information to identify
         * the type of the node and its properties.
         */
        *nodePtr = PmhalClocktreeGetNodeFast(graph, id);
    }
    return retStatus;
}

pmErrCode_t PMHALClockTreeGetNodeProp(pmhalClockTreeNodePtr   np,
                                      pmhalClockTreePropCptr *propPtr)
{
    pmErrCode_t retStatus = PM_SUCCESS;
    /* Given a certain pointer to the node element this API returns the
     * pointer to the property of the node.
     */
    if ((NULL != propPtr) && (NULL != np))
    {
        *propPtr = np->prop;
    }
    else
    {
        retStatus = PM_BADARGS;
    }
    return retStatus;
}

pmErrCode_t PMHALClockTreeGetPredecessors(pmhalClockTreeNodeId      id,
                                          pmhalClockTreeNodeIdCvec *pred,
                                          pmhalClockTreeSize_t     *npred)
{
    pmErrCode_t       result = PM_FAIL;
    pmhalClockTreePtr graph  = &prcmGraph;
    if ((pred != NULL) && (npred != NULL))
    {
        result = PMHALClockTreeValidNode(id);
        if (PM_SUCCESS == result)
        {
            /* Each module can have one or more predecessors depending on the
             * number of clocks which the module is receiving. This API returns
             * the information about the predecessors based on the edges which
             * the module is connected to in the clock tree.
             */
            pmhalClockTreeNodePtr node = PmhalClocktreeGetNodeFast(graph, id);
            *pred  = node->edgeIn;
            *npred = node->edgeInMax;
        }
    }
    return result;
}

pmErrCode_t PMHALClockTreeGetEdgeProp(pmhalClockTreeInputEdgePtr ep,
                                      pmhalClockTreeEdgePropPtr *edgePropPtr)
{
    pmErrCode_t retStatus = PM_SUCCESS;
    if (NULL != edgePropPtr)
    {
        if (NULL == ep)
        {
            retStatus    = PM_BADARGS;
            *edgePropPtr = NULL;
        }
        else
        {
            /* Each edge to a module contains a property defining the clock
             * name and the divider/multiplexer/DPLL from which the clock is
             * derived.
             */
            *edgePropPtr = ep->prop;
        }
    }
    else
    {
        retStatus = PM_BADARGS;
    }
    return retStatus;
}

pmErrCode_t PMHALClockTreeGetModuleEdge(pmhalClockTreeNodeId        sourceNode,
                                        pmhalClockTreeProperty      property,
                                        pmhalClockTreeInputEdgePtr *edgePtr)
{
    pmErrCode_t                 retStatus = PM_SUCCESS;
    pmhalClockTreeNodePtr       nodePtr;
    pmhalClockTreePropCptr      nodePropPtr;
    pmhalClockTreeOutputEdgePtr edges;
    pmhalClockTreeNodeId        edgePropEnum;
    pmhalNodeType_t             nodeType = PMHAL_UNDEF;
    uint32_t loopVariable = 0U;
    pmhalClockTreePtr           graph = &prcmGraph;

    if (edgePtr == NULL)
    {
        retStatus = PM_BADARGS;
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Check if the source node provided is a module or not */
        nodeType = PMHALClockTreeGetNodeType(sourceNode);
        if (nodeType != PMHAL_MOD)
        {
            retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID;
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Get the node pointer and the node property for the given module */
        retStatus = PMHALClockTreeGetNode(sourceNode, &nodePtr);
        if (PM_SUCCESS == retStatus)
        {
            retStatus = PMHALClockTreeGetNodeProp(nodePtr, &nodePropPtr);
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Once the node property is found, type cast this to a module property
         * Each module has an index to the edge property array.
         */
        const pmhalModule_t *ptr = (const pmhalModule_t *) (nodePropPtr->pvalue);
        edgePropEnum = (*(ptr)).edgePropertyEnum;

        if (edgePropEnum != PMHAL_EDGE_UNDEF)
        {
            edges = PmhalClocktreeGetEdgeFast(graph, edgePropEnum);
            /* A given module can contain multiple edges. To find which edge
             * is being searched for loop through all the edges and find the
             * edge for which the clock ID matches. For the matched clock ID
             * the API returns the corresponding edge property.
             */
            while (loopVariable < (edges->toNodesMax))
            {
                if (property == ((edges)->toNodes[loopVariable]).toProp)
                {
                    *edgePtr = &((edges)->toNodes[loopVariable]);
                    break;
                }
                loopVariable = loopVariable + 1U;
            }
            if (loopVariable == (edges->toNodesMax))
            {
                retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID;
                /* property given is invalid for module */
            }
        }
        else
        {
            retStatus = PM_CLOCTREE_EDGE_NOT_AVAILABLE;
            /* module doesn't have edge property */
        }
    }
    return retStatus;
}

pmErrCode_t PMHALClockTreeGetDpllEdge(pmhalClockTreeNodeId        sourceNode,
                                      pmhalClockTreeNodeId        toNode,
                                      pmhalClockTreeProperty      property,
                                      pmhalClockTreeInputEdgePtr *edgePtr)
{
    pmErrCode_t                 retStatus = PM_SUCCESS;
    pmhalClockTreeNodePtr       nodePtr;
    pmhalClockTreePropCptr      nodePropPtr;
    pmhalClockTreeOutputEdgePtr edges;
    pmhalClockTreeNodeId        edgePropEnum;
    pmhalClockTreePtr           graph = &prcmGraph;
    uint32_t loopVariable = 0U;
    pmhalNodeType_t             nodeType = PMHAL_UNDEF;
    if (edgePtr == NULL)
    {
        retStatus = PM_BADARGS;
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Check if the source node provided is a DPLL or not */
        nodeType = PMHALClockTreeGetNodeType(sourceNode);
        if (nodeType != PMHAL_DPLL)
        {
            retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID;
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Check if the node to which the DPLL clock goes to is valid or not */
        retStatus = PMHALClockTreeValidNode(toNode);
    }
    if (PM_SUCCESS == retStatus)
    {
        /* For the given DPLL find the node pointer and the DPLL property */
        retStatus = PMHALClockTreeGetNode(sourceNode, &nodePtr);
        if (PM_SUCCESS == retStatus)
        {
            retStatus = PMHALClockTreeGetNodeProp(nodePtr, &nodePropPtr);
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        edgePropEnum =
            (*((const pmhalDpll_t *) (nodePropPtr->pvalue))).edgePropertyEnum;
        if (edgePropEnum != PMHAL_EDGE_UNDEF)
        {
            edges = PmhalClocktreeGetEdgeFast(graph, edgePropEnum);
            /* A DPLL can source clocks to multiple modules depending on which
             * HSdivider is sourcing the clock. To find which edge
             * is being searched for loop through all the edges and find the
             * edge for which the clock ID matches. For the matched clock ID
             * the API returns the corresponding edge property.
             */
            while (loopVariable < (edges->toNodesMax))
            {
                if (toNode == (((edges)->toNodes[loopVariable]).toProp))
                {
                    if ((property ==
                         (((edges)->toNodes[loopVariable]).prop->vType)) ||
                        ((((edges)->toNodes[loopVariable]).prop->vType) == 0U))
                    {
                        *edgePtr = &((edges)->toNodes[loopVariable]);
                        break;
                    }
                }
                loopVariable = loopVariable + 1U;
            }
            if (loopVariable == (edges->toNodesMax))
            {
                retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID;
                /* property given is invalid for module */
            }
        }
        else
        {
            retStatus = PM_CLOCTREE_EDGE_NOT_AVAILABLE;
            /* module doesn't have edge property */
        }
    }
    return retStatus;
}

pmErrCode_t PMHALClockTreeGetDpllInEdge(pmhalClockTreeNodeId        sourceNode,
                                        pmhalClockTreeProperty      property,
                                        pmhalClockTreeInputEdgePtr *edgePtr)
{
    pmErrCode_t                 retStatus = PM_SUCCESS;
    pmhalClockTreeNodePtr       nodePtr;
    pmhalClockTreePropCptr      nodePropPtr;
    pmhalClockTreeOutputEdgePtr edges;
    pmhalClockTreeNodeId        edgePropEnum;
    pmhalNodeType_t             nodeType = PMHAL_UNDEF;
    uint32_t loopVariable = 0U;
    pmhalClockTreePtr           graph = &prcmGraph;

    if (edgePtr == NULL)
    {
        retStatus = PM_BADARGS;
    }
    if (PM_SUCCESS == retStatus)
    {
        /* Check if the source node provided is a DPLL or not */
        nodeType = PMHALClockTreeGetNodeType(sourceNode);
        if (nodeType != PMHAL_DPLL)
        {
            retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_NODE_ID;
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        /* For the given DPLL find the node pointer and the DPLL property */
        retStatus = PMHALClockTreeGetNode(sourceNode, &nodePtr);
        if (PM_SUCCESS == retStatus)
        {
            retStatus = PMHALClockTreeGetNodeProp(nodePtr, &nodePropPtr);
        }
    }
    if (PM_SUCCESS == retStatus)
    {
        edgePropEnum =
            (*((const pmhalDpll_t *) (nodePropPtr->pvalue))).edgePropertyEnum;

        if (edgePropEnum != PMHAL_EDGE_UNDEF)
        {
            edges = PmhalClocktreeGetEdgeFast(graph, edgePropEnum);
            /* A given DPLL can contain multiple edges going in. To find which
             * edge is being searched for loop through all the edges and find
             * the edge for which the clock ID matches. For the matched clock ID
             * the API returns the corresponding edge property.
             */
            while (loopVariable < (edges->toNodesMax))
            {
                if (property == ((edges)->toNodes[loopVariable]).toProp)
                {
                    *edgePtr = &((edges)->toNodes[loopVariable]);
                    break;
                }
                loopVariable = loopVariable + 1U;
            }
            if (loopVariable == (edges->toNodesMax))
            {
                retStatus = PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID;
                /* property given is invalid for module */
            }
        }
        else
        {
            retStatus = PM_CLOCTREE_EDGE_NOT_AVAILABLE;
            /* module doesn't have edge property */
        }
    }
    return retStatus;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmhalClockTreeNodePtr PmhalClocktreeGetNodeFast(
    pmhalClockTreePtr    graph,
    pmhalClockTreeNodeId id)
{
    return (pmhalClockTreeNodePtr) & ((graph)->nodes[id]);
}

static pmhalClockTreeOutputEdgePtr PmhalClocktreeGetEdgeFast(
    pmhalClockTreePtr    graph,
    pmhalClockTreeNodeId id)
{
    return (pmhalClockTreeOutputEdgePtr) & ((graph)->edges[id]);
}

