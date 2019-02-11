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
 *  \file vpscore_dssPriv.h
 *
 *  \brief Header file for DSS display core
 *  This file includes data-structures and function declarations for the
 *  the VPS display core interface for DSS.
 *
 */

#ifndef DCTRLLIB_PRIV_H_
#define DCTRLLIB_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/src/vpslib/common/vps_graph.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dctrlIntr.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define VPSCORE_DSS_DEF_ALIGN      ((uint32_t) 32U)
#define GRAPH_DCTRL_DSS_NUM_EDGES  ((uint32_t) 31U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef enum
{
    VPS_DCTRL_PIPE_IDLE,
    /**< When Graph is created*/
    VPS_DCTRL_PIPE_OPENED,
    /**< When DSS core opens the pipe */
    VPS_DCTRL_PIPE_STARTED,
    /**< When DSS core starts pipe, DCTRL  need to send interrupts then */
    VPS_DCTRL_PIPE_RUNNING
    /**< When first VSync happens after DSS Core starts pipe */
} VpsCore_DctrlPipeState;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_DssObj
 *  \brief DSS Core Handle structure. This will be instantiated for each
 *  instance of DSS. (Currently there is only one instance of DSS)
 */

typedef struct
{
    UInt32              dispcIrqNumber;

    VpsHal_Handle       ovlHandle[VPSHAL_DSS_DISPC_OVLY_MAX_INST];

    void               *graph;
    Vgraph_Info         graphObj;
    Vgraph_nodeInfoList graphObjNodeList;
    Vgraph_edgeInfoList graphObjEdgeList;

    Vgraph_nodeInfoList dctrlNodeList;
    Vgraph_edgeInfoList dctrlEdgeList;
    Vgraph_nodeInfo     dctrlNodeObj[GRAPH_DCTRL_DSS_NUM_NODES];
    Vgraph_edgeInfo     dctrlEdgeObj[GRAPH_DCTRL_DSS_NUM_EDGES];

    Vgraph_nodeInfo     allDctrlNodes[GRAPH_DCTRL_DSS_NUM_NODES];
    Vgraph_edgeInfo     allEdgeInfo[GRAPH_DCTRL_DSS_NUM_EDGES];
} VpsCore_DctrlObj;

typedef struct
{
    UInt32                  pipeNodeNum;
    /**<Information of the pipe connected. */
    VpsCore_DctrlPipeState  state;
    /** <Dss core has opened the node. handle given. */
    UInt32                  ovlNodeNum;
    /**<Information of the Overlay connected. */
    UInt32                  VencNodeNum;
    /**<Information of the Display connected. */
    UInt32                  vencId;
    /**<ID of the display. */
    Int32                   shiftVidPosX;
    /**<Vid position in overlay to be shifted in Number of pixels. */
    Vpscore_dctrlClientInfo gClientInfo;
    /**< DSS core call back function */
} VpsCore_DctrlPipe;

typedef struct
{
    UInt32 gfxBufferUnderflow;
    /**<Graphics pipeline Buffer underflow count. */
    UInt32 wbBufferOverflow;
    /**<Wb pipeline Buffer overflow count. */
    UInt32 wbIncompleteError;
    /**<WB pipeline Incomplete Error count. */
    UInt32 vid1BufferUnderflow;
    /**<VID1 pipeline Buffer underflow count. */
    UInt32 vid2BufferUnderflow;
    /**<VID2 pipeline Buffer underflow count. */
    UInt32 vid3BufferUnderflow;
    /**<VID3 pipeline Buffer underflow count. */
    UInt32 syncLost1;
    /**<SyncLost Error Count for LCD1 Overlay. */
    UInt32 syncLost2;
    /**<SyncLost Error Count for LCD2 Overlay. */
    UInt32 syncLost3;
    /**<SyncLost Error Count for LCD3 Overlay. */
    UInt32 syncLostTV;
    /**<SyncLost Error Count for TV Overlay. */
    UInt32 ocpError;
    /**< Ocp Error Count. */
}VpsCore_DctrlErrorCount;

typedef struct
{
    UInt32 wbSyncRbEndWinTog;
    /**<Number of times wbSync and rbEndWindow interrupts occured together. */
    UInt32 wbSyncIrq;
    /**<Number of times wbSync interrupt occured. */
    UInt32 wbSyncOnlyNormal;
    /**<Number of times wbSync interrupt occured
     *  when regionbased bit is set previously. */
    UInt32 wbSyncOnlyFrameSkip;
    /**<Number of times wbSync interrupt occured
     *  when regionbased bit is not set previously.*/
    UInt32 rbEndWinOnly;
    /**<Number of times rb end window interrupt occured. */
} VpsCore_DctrlWbDebugInfo;

typedef struct
{
    UInt32                   numPipes;
    /**<Number of valid pipes in this struct. */
    VpsCore_DctrlPipe        VidInfo[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    /**<Information about the connected pipe. */
    UInt32                   numVencs;
    /**<Number of valid Vencs in this struct. */
    Vpscore_dctrlPathInfo    pathInfo[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Information about the LCD timing */
    UInt32                   isPushSafe[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Flag to indicate if buf push is safe - low latency display */
    UInt32                   dvoFmt[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**<Variable to Store the output format, vaild values #Vps_DctrlDigitalFmt.
    **/
    VpsCore_DctrlErrorCount  errorCnt;
    /**< all error stats are stored here. */
    VpsCore_DctrlWbDebugInfo wbDebugInfo;
    /**< Debug info for write back irq count. */
} VpsCore_DctrlInfo;

typedef struct
{
    UInt32 isStarted;
} VpsCore_DctrlPathObj;

extern const Vgraph_nodeInfo dctrlNodeInfoDefaults[GRAPH_DCTRL_DSS_NUM_NODES];
extern const Vgraph_edgeInfo dctrlEdgeInfoDefaults[GRAPH_DCTRL_DSS_NUM_EDGES];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TODO - Add description*/
Int32 VpsCore_dctrlGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property);
Int32 VpsCore_dctrlControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           Ptr            appArgs,
                           Ptr            drvArgs);
VpsCore_Inst VpsCore_DctrlInit(VpsCore_DctrlObj *pNewObj);

Int32 VpsCore_DctrlDeInit(VpsCore_Inst pDssHandle);

Int32 VpsCore_dctrlCreateEdgeList(VpsCore_DctrlObj *pathObj,
                                  Vps_DctrlConfig  *pathCfg);

void VpsCore_dctrlFreeEdgeList(VpsCore_DctrlObj *pathObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif
#endif /*DCTRLLIB_PRIV_H_*/
