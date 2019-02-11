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
 *  \file vpscore_dctrl.c
 *
 *  \brief DSS display controller core implementation
 *  This file implements the Display controller core interface for DSS.
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

#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dctrlPriv.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void VpsCore_DctrlGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                            const Vgraph_edgeInfoList *edgeInfoList,
                            VpsCore_DctrlObj          *pDctrlInstObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void VpsCore_DctrlGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                            const Vgraph_edgeInfoList *edgeInfoList,
                            VpsCore_DctrlObj          *pDctrlInstObj)
{
    pDctrlInstObj->graphObj.nodeList = &pDctrlInstObj->graphObjNodeList;
    pDctrlInstObj->graphObj.edgeList = &pDctrlInstObj->graphObjEdgeList;
    pDctrlInstObj->graph = &pDctrlInstObj->graphObj;
    Vgraph_Init(pathNodeList, edgeInfoList,
                (Vgraph_Info *) pDctrlInstObj->graph);
}

VpsCore_Inst VpsCore_DctrlInit(VpsCore_DctrlObj *pNewObj)
{
    if (NULL != pNewObj)
    {
        /* Create default tree with all edges disabled
         * This tree will handle resource management
         */
        BspUtils_memcpy(pNewObj->allDctrlNodes,
                        dctrlNodeInfoDefaults,
                        sizeof (dctrlNodeInfoDefaults));
        pNewObj->dctrlNodeList.numNodes = GRAPH_DCTRL_DSS_NUM_NODES;
        pNewObj->dctrlNodeList.list     = pNewObj->allDctrlNodes;

        BspUtils_memcpy(pNewObj->allEdgeInfo,
                        dctrlEdgeInfoDefaults,
                        sizeof (dctrlEdgeInfoDefaults));
        pNewObj->dctrlEdgeList.numEdges = GRAPH_DCTRL_DSS_NUM_EDGES;
        pNewObj->dctrlEdgeList.list     = pNewObj->allEdgeInfo;

        VpsCore_DctrlGraphInit(&pNewObj->dctrlNodeList,
                               &pNewObj->dctrlEdgeList,
                               pNewObj);
    }
    else
    {
        GT_0trace(
            VpsDctrlCoreTrace, GT_ERR,
            "Allocation of DSS instance Handle failed in VpsCore_DctrlInit().\r\n");
    }

    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_DctrlDeInit(VpsCore_Inst pDssHandle)
{
    VpsCore_DctrlObj *pDctrlObj = (VpsCore_DctrlObj *) pDssHandle;

    if (NULL != (void *) pDctrlObj)
    {
        Vgraph_DeInit((Vgraph_Info *) pDctrlObj->graph);
    }

    return BSP_SOK;
}

Int32 VpsCore_dctrlCreateEdgeList(VpsCore_DctrlObj *pathObj,
                                  Vps_DctrlConfig  *pathCfg)
{
    Vgraph_edgeInfoList tmpEdgeInfoList;
    VpsCore_DctrlObj   *pDctrlInstObj = (VpsCore_DctrlObj *) pathObj;
    Vgraph_Info        *DctrlGraph    = (Vgraph_Info *) (pDctrlInstObj->graph);
    Int32 retVal = BSP_SOK;

    tmpEdgeInfoList.numEdges = pathCfg->numEdges;
    tmpEdgeInfoList.list     = (Vgraph_edgeInfo *) &pathCfg->edgeInfo[0U];

    if (BSP_SOK == retVal)
    {
        /* Try to allocate nodes in the complete graph */
        if (BSP_SOK == Vgraph_allocNodes(DctrlGraph->nodeList,
                                         &tmpEdgeInfoList,
                                         VGRAPH_NODE_CHECK))
        {
            Vgraph_allocNodes(DctrlGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_ENABLE);

            pathObj->dctrlNodeList.list = pathObj->dctrlNodeObj;
            pathObj->dctrlEdgeList.list = pathObj->dctrlEdgeObj;
            Vgraph_getPath(DctrlGraph->nodeList,
                           &tmpEdgeInfoList,
                           &pathObj->dctrlNodeList,
                           &pathObj->dctrlEdgeList,
                           sizeof (pathObj->dctrlNodeObj) /
                           sizeof (Vgraph_nodeInfo),
                           sizeof (pathObj->dctrlEdgeObj) /
                           sizeof (Vgraph_edgeInfo));

            if (BSP_SOK != retVal)
            {
                /* TODO Free the resources */
            }
        }
        else
        {
            Vgraph_allocNodes(DctrlGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_DISABLE);
            retVal = BSP_EFAIL;
        }
    }

    return retVal;
}

void VpsCore_dctrlFreeEdgeList(VpsCore_DctrlObj *pathObj)
{
    VpsCore_DctrlObj *pDctrlInstObj = (VpsCore_DctrlObj *) pathObj;
    Vgraph_Info      *DctrlGraph    = (Vgraph_Info *) (pDctrlInstObj->graph);

    Vgraph_allocNodes(DctrlGraph->nodeList,
                      &(pathObj->dctrlEdgeList),
                      VGRAPH_NODE_DISABLE);

    Vgraph_freePath(&pathObj->dctrlNodeList, &pathObj->dctrlEdgeList);
}

