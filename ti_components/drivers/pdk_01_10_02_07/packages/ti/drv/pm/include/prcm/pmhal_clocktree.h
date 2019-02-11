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
 *  \addtogroup PM_HAL_CM
 *
 *   The Clock Rate Configuration APIs are used to configure the module clocks
 *   to run at desired clock frequency as specified by the user. \n The generic
 *   clocking scheme in the device can be visualized as a tree where a certain
 *   input clock to the device is the root node (or Root Clock) of the clock
 *   tree and the modules are leaf nodes. Between these two levels are
 *   multiple levels consisting of DPLLs, multiplexers, dividers etc.
 *   \n Configuring a clock frequency for the module requires programming these
 *   DPLLs, multiplexers and dividers.
 *   -  The Clock Rate Configuration APIs abstracts the programming of various
 *   PRCM clocking elements, such as DPLL, dividers and multiplexers,
 *   to provide the desired frequency for the given module clock.
 *   It uses the PRCM Database and the clock frequency database to configure
 *   module clocks.
 *
 * @{
 */

/**
 *  \file       pmhal_clocktree.h
 *
 *  \brief      This file contains Acyclic Graph Abstract Data Type,
 *              it has the graph node API for tree traversal
 */

#ifndef PMHAL_CLOCKTREE_H_
#define PMHAL_CLOCKTREE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <limits.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/pm_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Clock-tree node types
 */
typedef enum pmhalNodeType
{
    PMHAL_MOD = 0U,
    PMHAL_MIN = PMHAL_MOD,
    /**< Lower bound (inclusive) */
    PMHAL_DPLL = 1U,
    /**< Node Type for DPLL */
    PMHAL_MUX = 2U,
    /**< Node Type for Multiplexer */
    PMHAL_DIV = 3U,
    /**< Node Type for Divider */
    PMHAL_ROOT_CLK = 4U,
    /**< Node Type for Root Clocks */
    PMHAL_MAX = PMHAL_ROOT_CLK,
    /**< Enum Upper bound */
    PMHAL_COUNT = PMHAL_MAX + 1U,
    /**< Enum Count */
    PMHAL_UNDEF = -((int32_t) 1)
                  /**< Undefined value */
} pmhalNodeType_t;

/**
 * \brief  Graph Node-ID type
 */
typedef uint32_t pmhalClockTreeNodeId;

/**
 * \brief  Graph Node-ID type
 */
typedef pmhalClockTreeNodeId *pmhalClockTreeNodeIdVec;

/**
 * \brief  Graph Node-ID const vector type
 */
typedef const pmhalClockTreeNodeId *pmhalClockTreeNodeIdCvec;

/**
 * \brief  Graph Node Vertex type
 */
typedef uint32_t pmhalClockTreePropType;

/**
 * \brief  Graph Node Vertex type
 */
typedef uint32_t pmhalClockTreeProperty;

/**
 * \brief  Graph Node Property type
 */
typedef uint8_t clockTreeVertex;

/**
 * \brief  Graph size type
 */
typedef uint16_t pmhalClockTreeSize_t;

/**
 * \brief   Graph container to hold clock tree property
 */
typedef struct
{
    pmhalClockTreePropType ptype;
    /**< Property type used to interpret pvalue*/
    const void            *pvalue;
    /**< Property value*/
} pmhalClockTreeProp;

/** \brief Pointer to the clock tree property structure */
typedef const pmhalClockTreeProp *pmhalClockTreePropCptr;

/**
 * \brief   Graph container to hold clock tree edge property
 */
typedef struct
{
    pmhalClockTreePropType ptype;
    /**< Property type used to interpret pvalue*/
    const void            *pvalue;
    /**< Property value*/
    clockTreeVertex        vType;
    /**< Vertex of value*/
} pmhalClockTreeEdgeProp;

/** \brief Pointer to the clock tree edge property structure */
typedef const pmhalClockTreeEdgeProp *pmhalClockTreeEdgePropPtr;

/**
 * \brief   Edge stuct that encapsulates a property
 */
typedef struct
{
    pmhalClockTreeProperty    toProp;
    /**< Property of the connected node*/
    pmhalClockTreeEdgePropPtr prop;
    /**< Edge property specific to this edge*/
} pmhalClockTreeInputEdge;

/** \brief Pointer to the clock tree input edge structure */
typedef const pmhalClockTreeInputEdge *pmhalClockTreeInputEdgePtr;

/**
 *  \brief   List of edges originating from a node
 */
typedef struct
{
    pmhalClockTreeNodeId       from;
    /**< Source of edge*/
    pmhalClockTreeInputEdgePtr toNodes;
    /**< Target(s) of edge*/
    pmhalClockTreeSize_t       toNodesMax;
    /**< Number of elements in toNodes vector*/
} pmhalClockTreeOutputEdge;

/** \brief Pointer to the clock tree output edge structure */
typedef const pmhalClockTreeOutputEdge *pmhalClockTreeOutputEdgePtr;

/**
 *  \brief  Graph node optimized for PM
 */
typedef struct
{
    pmhalClockTreePropCptr   prop;
    /**< Node Property*/
    pmhalClockTreeNodeIdCvec edgeIn;
    /**< List of edges incident on this node (Parent node-ids)*/
    pmhalClockTreeSize_t     edgeInMax;
    /**< Number of edges incident on this node*/
} pmhalClockTreeNode;

/** \brief Pointer to the clock tree Node */
typedef const pmhalClockTreeNode *pmhalClockTreeNodePtr;

/**
 *  \brief  Graph for clocktree structure
 */
typedef struct
{
    pmhalClockTreeSize_t        nodesMax;
    /**< Max number of nodes incident.*/
    pmhalClockTreeNodePtr       nodes;
    /**< Number of node incident */
    pmhalClockTreeSize_t        edgesMax;
    /**< Max number of edges incident on this node*/
    pmhalClockTreeOutputEdgePtr edges;
    /**< Number of edges incident on this node*/
} pmhalClockTree;

/** \brief Pointer to the clock tree Node */
typedef const pmhalClockTree *pmhalClockTreePtr;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Is the given node-id valid?
 *
 * \param   id              graph node Id
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the nodeId is not valid
 */
pmErrCode_t PMHALClockTreeValidNode(pmhalClockTreeNodeId id);

/**
 * \brief   gives the type of the given node
 *
 * \param   id           Graph node Id
 *
 * \return  nodeType     Refer #pmhalNodeType_t name for details
 *
 */
pmhalNodeType_t PMHALClockTreeGetNodeType(pmhalClockTreeNodeId id);

/**
 * \brief  Get the node_ptr corresponding to the node_id
 *
 * \param  id         Graph node Id Refer #pmhalClockTreeNodeId
 * \param  nodePtr       NodePointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates node is not found
 */
pmErrCode_t PMHALClockTreeGetNode(pmhalClockTreeNodeId   id,
                                  pmhalClockTreeNodePtr *nodePtr);

/**
 * \brief  Get the property corresponding to the node_id
 *
 * \param  np         Node_ptr corresponding to the node_id
 * \param  propPtr    PropPtr corresponding to nodePointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates node is not found or property is
 **undefined
 */
pmErrCode_t PMHALClockTreeGetNodeProp(pmhalClockTreeNodePtr   np,
                                      pmhalClockTreePropCptr *propPtr);

/**
 * \brief     Get the the list of predecessor nodes
 *
 * \param  id        Graph node Id
 * \param  pred      Graph Node-ID const vector type
 * \param  npred     No of innodes to the given node
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the nodeId is not valid
 */
pmErrCode_t PMHALClockTreeGetPredecessors(pmhalClockTreeNodeId      id,
                                          pmhalClockTreeNodeIdCvec *pred,
                                          pmhalClockTreeSize_t     *npred);

/**
 * \brief   Get the edge_ptr associated with a clock for a Module.
 *
 * \param   sourceNode      Module for which edge property is valid.
 * \param   property        Edge property that we are interested
 * \param   edgePtr         Pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates edge is undefined for the source Node
 *                          or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetModuleEdge(pmhalClockTreeNodeId        sourceNode,
                                        pmhalClockTreeProperty      property,
                                        pmhalClockTreeInputEdgePtr *edgePtr);

/**
 * \brief   Get the edge_ptr connecting Dpll and a Node.
 *
 * \param   sourceNode      Module for which edge property is valid.
 * \param   toNode          Node that is connected to source node
 * \param   property        Edge property that we are interested
 * \param   edgePtr         Pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates edge is undefined for the source
 *                          Node or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetDpllEdge(pmhalClockTreeNodeId        sourceNode,
                                      pmhalClockTreeNodeId        toNode,
                                      pmhalClockTreeProperty      property,
                                      pmhalClockTreeInputEdgePtr *edgePtr);

/**
 * \brief  Get the property corresponding to the edge
 *
 * \param  ep             Graph edge const pointer
 * \param  edgePropPtr    Edge property pointer
 *
 * \return errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates edge is not found or property is
 **undefined
 */
pmErrCode_t PMHALClockTreeGetEdgeProp(pmhalClockTreeInputEdgePtr ep,
                                      pmhalClockTreeEdgePropPtr *edgePropPtr);

/**
 * \brief   Get the edge_ptr associated with a clock for a dpll.
 *
 * \param   sourceNode      Dpll for which edge property is valid.
 * \param   property        Edge property that we are interested
 * \param   edgePtr         Pointer that defines the edge attributes
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates edge is undefined for the source Node
 *                          or the related Node is not connected
 */
pmErrCode_t PMHALClockTreeGetDpllInEdge(pmhalClockTreeNodeId        sourceNode,
                                        pmhalClockTreeProperty      property,
                                        pmhalClockTreeInputEdgePtr *edgePtr);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_CLOCKTREE_H_ */

/* @} */


