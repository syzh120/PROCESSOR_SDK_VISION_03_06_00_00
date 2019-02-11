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
 *  \file vpscore_DctrlDefaults.c
 *
 *  \brief Default NodeInfo and EdgeInfo structure for DCTRL
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dctrlPriv.h>
#include <ti/drv/vps/src/vpslib/common/vps_graph.h>

/* {nodeNum,                        inType,     outType,    nodeType,
 *            corePtr, 0, 0, {     input   },  {     input   }},  */
const Vgraph_nodeInfo dctrlNodeInfoDefaults[GRAPH_DCTRL_DSS_NUM_NODES] =
{ \
    {GRAPH_DCTRL_DSS_INVALID,      EMPTY_IN,  EMPTY_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID1,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID2,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_VID3,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_GFX,          SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_WB,           SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSVID, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, MULTI_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DSSMGR, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI1_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI2_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_DPI3_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}}, \
    {GRAPH_DCTRL_DSS_HDMI_OUTPUT,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DSSOUT, NULL, 0, 0,
                                        {0,                            {NULL},
                                        {0}},
                                        {0,                            {NULL},
                                        {0}}},
};

/***
 * Defining EdgeList:
 * Muxes: Arrange in terms of mux values, if any entry is invalid, mark as
 * GRAPH_DSS_INVALID
 ***/
const Vgraph_edgeInfo dctrlEdgeInfoDefaults[GRAPH_DCTRL_DSS_NUM_EDGES] =
{                                                                 \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID2,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID1,         GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_VID3,         GRAPH_DCTRL_DSS_WB          }, \

    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD1_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD2_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_LCD3_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_HDMI_BLENDER}, \
    {GRAPH_DCTRL_DSS_GFX,          GRAPH_DCTRL_DSS_WB          }, \
                                                                  \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD1_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \


    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_LCD2_BLENDER, GRAPH_DCTRL_DSS_DPI2_OUTPUT }, \


    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_LCD3_BLENDER, GRAPH_DCTRL_DSS_DPI3_OUTPUT }, \

    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_WB          }, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_DPI1_OUTPUT }, \
    {GRAPH_DCTRL_DSS_HDMI_BLENDER, GRAPH_DCTRL_DSS_HDMI_OUTPUT }, \

};

