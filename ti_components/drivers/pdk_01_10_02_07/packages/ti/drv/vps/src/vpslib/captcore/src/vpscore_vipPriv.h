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
 *  \file vpscore_vipPriv.h
 *
 *  \brief Header file for VIP capture core
 *  This file includes data-structures and function declarations for the
 *  the VPS capture core interface for VIP.
 *
 */

#ifndef VPSCORE_VIP_PRIV_H_
#define VPSCORE_VIP_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/vps/src/vpslib/common/vps_graph.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSCORE_VIP_AUTO_EDGELIST_MAX_SIZE  (32U)

#define VPSCORE_VIP_DEF_ALIGN  32U
#ifdef PLATFORM_VIRTIO
#define VIP_HW_Q_LEN         1U
#else
#define VIP_HW_Q_LEN         3U
#endif /* PLATFORM_VIRTIO */
/* For future flexibility. Should be at least VIP_HW_Q_LEN */
#define VIP_SW_Q_LEN         (VIP_HW_Q_LEN)
/* TODO: May need to double for chroma??? */
#define VPSCORE_VIP_MAX_CH   16U

#define PORT_Y_UP            0U
#define PORT_UV_UP           1U
#define PORT_Y_LO            2U
#define PORT_UV_LO           3U
#define PORTA_ANC            4U
#define PORTB_ANC            5U
#define PORT_MAX             6U

#define GRAPH_VIP_NUM_EDGES 164U

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
typedef enum
{
    VCORE_VIPVPDMA_DT_YC444 = 0,
    VCORE_VIPVPDMA_DT_RGB888,
    VCORE_VIPVPDMA_DT_YC422,
    VCORE_VIPVPDMA_DT_C422,
    VCORE_VIPVPDMA_DT_Y420,
    VCORE_VIPVPDMA_DT_C420,
    VCORE_VIPVPDMA_DT_ANC,
    VCORE_VIPVPDMA_DT_INVALID
} VpsCore_VipVpdmaDT;
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_VipObj
 *  \brief VIP Core Handle structure. This will be instantiated for each
 *  instance of VIP sub-system consisting of two slices.
 */
typedef struct
{
    UInt32              numHandles;
    VpsCore_Handle      pathObjPool[4];  /* PORTA/PORTB/S0/S1 */
    VpsHal_Handle       vipTopHandle;
    VpsHal_Handle       vpdmaHandle;
    VpsHal_Handle       s0PortAHandle;
    VpsHal_Handle       s0PortBHandle;
    VpsHal_Handle       s1PortAHandle;
    VpsHal_Handle       s1PortBHandle;
    VpsHal_Handle       sc0Handle;
    VpsHal_Handle       sc1Handle;
    VpsHal_Handle       csc0Handle;
    VpsHal_Handle       csc1Handle;
    Vem_InstId          vemInstId;
    Vrm_InstId          vrmInstId;

    void               *graph;
    Vgraph_Info         graphObj;
    Vgraph_nodeInfoList graphObjNodeList;
    Vgraph_edgeInfoList graphObjEdgeList;

    Vgraph_nodeInfoList vipNodeList;
    Vgraph_edgeInfoList vipEdgeList;
    Vgraph_nodeInfo     allVipNodes[GRAPH_VIP_NUM_NODES];
    Vgraph_edgeInfo     allEdgeInfo[GRAPH_VIP_NUM_EDGES];
} VpsCore_VipObj;

typedef struct
{
    UInt32                 handleId;
    Ptr                    drvData;
    VpsCore_VipObj        *parent;
    VpsHal_Handle          vipTopHandle;
    VpsHal_Handle          vpdmaHandle;
    VpsHal_Handle          vipPortHandle;
    VpsHal_Handle          scHandle;
    VpsHal_Handle          cscHandle;
    UInt32                 sliceId;
    UInt32                 portId;
    Vgraph_nodeInfoList    nodeList;
    Vgraph_edgeInfoList    edgeList;
    Vgraph_nodeInfo        nodeObj[GRAPH_VIP_NUM_NODES];
    Vgraph_edgeInfo        edgeObj[GRAPH_VIP_NUM_EDGES];

    UInt32                 descMemSize;
    UInt8                 *descMem[VPSCORE_VIP_CH_ID_MAX];
    UInt32                 wrDescMemSize;
    UInt8                 *wrDescMem[VPSCORE_VIP_CH_ID_MAX][VIP_SW_Q_LEN];
    UInt32                 cfgDescMemSize;
    UInt8                 *cfgDescMem;
    UInt32                 ctrlDescMemSize;
    UInt8                 *ctrlDescMem;
    UInt32                 curIdx;

    UInt32                 listSize;
    UInt32                 interruptId;                    /* TODO */
    UInt32                 numFrames;                      /* TODO */
    UInt32                 chFreed[VPSCORE_VIP_MAX_CH];    /* TODO */

    /* VpsCore_VipParams     pathHandleParams; */
    UInt32                 src;
    UInt32                 numChannels;
    UInt32                 muxModeStartChId;
    UInt32                 srcColorSpace;
    UInt32                 orgSrcColorSpace;
    UInt32                 srcWidth;
    UInt32                 srcHeight;
    UInt32                 numStreams;
    UInt32                 dstColorSpace[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 orgDstColorSpace[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 tarWidth[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 tarHeight[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 pitch[VPSCORE_VIP_STREAM_ID_MAX][FVID2_MAX_PLANES
    ];
    UInt32                 scActive[VPSCORE_VIP_STREAM_ID_MAX];

    UInt32                 maxOutWidth[VPSCORE_VIP_STREAM_ID_MAX]
    [FVID2_MAX_PLANES];
    /**< Set limit on the max possible width of the output frame
     *   For valid values see #Vps_VpdmaMaxOutWidth. */
    UInt32                 maxOutHeight[VPSCORE_VIP_STREAM_ID_MAX]
    [FVID2_MAX_PLANES];
    /**< Set limit on the max possible height of the output frame
     *   For valid values see #Vps_VpdmaMaxOutHeight. */
    UInt32                 memType[VPS_CAPT_VIP_STREAM_ID_MAX];
    /**< Tiled or non-tiled memory selection for output.
     *   For valid values see #Vps_VpdmaMemoryType.*/

    Vps_VipPortConfig      portCfg;
    Fvid2_CropConfig       inCropCfg;
    Vps_ScConfig           scCfg;
    Vps_ScAdvConfig        scAdvCfg;
    Vps_ScAdvConfig        defScAdvCfg;
    Vps_CscConfig          cscCfg;
    Vps_CscCoeff           cscCoeff;

    UInt32                 strm2PortMap[VPSCORE_VIP_STREAM_ID_MAX *
                                        FVID2_MAX_PLANES];
    VpsHal_VpdmaChannel    strm2VpdmaChanMap[VPSCORE_VIP_CH_ID_MAX]
    [VPSCORE_VIP_STREAM_ID_MAX * FVID2_MAX_PLANES];
    UInt32                 port2StrmMap[PORT_MAX];
    VpsHal_VpdmaChanDT     vpdmaDataType[PORT_MAX];

    UInt32                 numPlanes[FVID2_MAX_PLANES];
    UInt32                 numDesc[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 descAddr[VPSCORE_VIP_STREAM_ID_MAX];
    UInt32                 numActivePorts;

    VpsCore_ReqFrameCb     reqFrmCb;
    /**< Request frame callback function. This cannot be NULL. */
    VpsCore_FrameDoneCb    frmDoneCb;
    /**< Frame complete callback function. This cannot be NULL. */

    VpsCore_Frame         *inputFrame[VPSCORE_VIP_MAX_CH]
    [VPSCORE_VIP_STREAM_ID_MAX]
    [VIP_SW_Q_LEN];
    UInt32                 inpFrmIdx[VPSCORE_VIP_CH_ID_MAX];
    UInt32                 outFrmIdx[VPSCORE_VIP_CH_ID_MAX];
    UInt32                 initialWait[VPSCORE_VIP_CH_ID_MAX];

    UInt32                 cscActive;
    UInt32                 chrDs0Bypass;
    UInt32                 chrDs1Bypass;
    VpsCore_VipVpdmaDT     portDataType[PORT_MAX];

    VpsCore_SubFrameParams subFrmPrms[VPSCORE_VIP_STREAM_ID_MAX];
    /**< SubFrame mode parameters. */

    UInt32                 isStopped;
    UInt32                 listId[VPSCORE_VIP_CH_ID_MAX];

    UInt32                 forceCscBypass;
    UInt32                 cscMode;
    UInt32                 cscBypass;

    UInt32                 setConfigDone;
    UInt32                 multiCaptureValid;
} VpsCore_VipPathObj;

extern const Vgraph_nodeInfo vipNodeInfoDefaults[GRAPH_VIP_NUM_NODES];
extern const Vgraph_edgeInfo vipEdgeInfoDefaults[GRAPH_VIP_NUM_EDGES];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsCore_vipPathResetMuxes
 *  \brief This function will reset the muxes presetn in the path.
 *
 *  \param VpsCore_VipPathObj Pointer to capture handle as created by
 *                          VpsCore_vipOpen() of type #VpsCore_VipPathObj.
 *
 *  \return               None
 */
void VpsCore_vipPathResetMuxes(const VpsCore_VipPathObj *pathObj);

/**
 *  VpsCore_vipCheckMaxSizeParams
 *  \brief This function validates the max size parameters received
 *         during the control API.
 *
 *  \param vipMaxFrmPrms    Pointer to the instance of max size parameters
 *                          #Vps_VpdmaMaxSizeParams.
 *
 *  \return                 success: BSP_SOK, max size parameters are
 *                          in valid range.
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipCheckMaxSizeParams(const Vps_VpdmaMaxSizeParams *vipMaxFrmPrms);

/**
 *  VpsCore_vipPathResAlloc
 *  \brief This function allocates resources for a given VpsCore_VipParams
 *         as per availaibility
 *
 *  \param VpsCore_VipPathObj Pointer to capture handle as created by
 *                          VpsCore_vipOpen() of type #VpsCore_VipPathObj.
 *  \param VpsCore_VipParams  Input parameters for the handle
 *                          #VpsCore_VipParams.
 *
 *  \return                 success: BSP_SOK
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipPathResAlloc(VpsCore_VipPathObj      *pathObj,
                              const VpsCore_VipParams *pathCfg);

/**
 *  VpsCore_vipPathResFree
 *  \brief This function frees up all resources allocated for the specified
 *         capture handle
 *
 *  \param VpsCore_VipPathObj Pointer to capture handle as created by
 *                          VpsCore_vipOpen() of type #VpsCore_VipPathObj.
 *
 *  \return                 None
 */
void  VpsCore_vipPathResFree(VpsCore_VipPathObj *pathObj);

/**
 *  VpsCore_vipCreateCCISCtrlDesc
 *  \brief This function creates and posts the control descriptor for
 *         change of client interrupt.
 *         Typically, for sub Frame mode, it enables Client interrupt for
 *         every N-Lines/only Nth Line.
 *         N is the value provided by the application.
 *         For sub frame mode disabled, it shall enable interrupt for
 *         end of frame.
 *
 *  \param VpsCore_VipPathObj Pointer to capture handle as created by
 *                          VpsCore_vipOpen() of type #VpsCore_VipPathObj.
 *
 *  \return                 None.
 */
void VpsCore_vipCreateCCISCtrlDesc(VpsCore_VipPathObj *pathObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSCORE_VIP_PRIV_H_ */
