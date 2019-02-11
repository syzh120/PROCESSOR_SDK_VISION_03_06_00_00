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
 *  \file vpscore_vip.c
 *
 *  \brief VIP capture core implementation
 *  This file implements the VPS capture core interface for VIP.
 *
 */
/* TODO: PortB should not be allowed if PortA is 24 bit */

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

#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/captcore/src/vpscore_vipPriv.h>
#include <ti/drv/vps/src/vpslib/captcore/src/vpscore_vipVipControl.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/include/vps_cfgMem.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSCORE_VIP_DESC_SIZE  (VPSHAL_VPDMA_DATA_DESC_SIZE)

#define VPSCORE_VIP_MAX_PLANES (2U) /* VIP supports maximum two
                                     * video planes
                                     */

/*
 * Maximum count of descriptors per allocation for data-descriptors
 * per VIP slice
 *
 * For single channels, worst-case allocation is (4 pix-data for 420SP +
 * 1 ancillary). All other scenarios will need lesser memory.
 *
 * Incase of mux-mode, each channel is allocated independently with two
 * descriptors (one pix-data and one ancillary) is allocated together
 *
 */
#define VPSCORE_VIP_MAX_DATA_DESC_COUNT (5U)

/*
 * Total size per allocation for data-descriptors
 */
#define VPSCORE_VIP_DATA_DESC_SIZE      (VPSCORE_VIP_DESC_SIZE * \
                                         VPSCORE_VIP_MAX_DATA_DESC_COUNT)

/*
 * Maximum count of allocations for data-descriptors for all ports
 * Each port can have maximum of 8 data descriptors as the number of lists in
 * VPDMA is 8.
 * Pool-based allocation always allocates the maximum for each port.
 * This is because typically each port will only need 2(luma/chroma)
 * descriptors - and therefore you need memory for 2*4 = 8 descriptors per 
 * VIP instance.
 */
#define VPSCORE_VIP_NUM_DATA_DESC_MAX   ((VPS_CFG_MEM_VIP_MAX_INST_OBJS * \
                                         VPSHAL_VPDMA_MAX_LIST))


/*
 * Maximum count of descriptors for all VIP instances.
 *
 * Summary:
 * List of all Write descriptor, Config descriptors, Control descriptors
 *
 * (NUM_VIP *
 *  ((NUM_SLICES)            + -> CFG desc for two scalars
 *   (NUM_LISTS)             + -> 8U Max lists available for capture per VIP
 *                                Used in VpsCore_vipCreateCCISCtrlDesc
 *   (VPSCORE_VIP_MAX_DATA_DESC_COUNT *
 *    VIP_SW_Q_LEN)          + -> Write descriptors for 2 slices.
 *  )                             Maintain a FIFO of VIP_SW_Q_LEN for each
 * )                              data descriptor.
 *
 */
#define VPSCORE_VIP_NUM_MISC_DESC_MAX \
    (VPS_CFG_MEM_VIP_MAX_INST_OBJS * \
     ((VPS_VIP_SLICE_MAX) + \
      (VPSHAL_VPDMA_MAX_LIST) + \
      (VPSCORE_VIP_MAX_DATA_DESC_COUNT * VPS_VIP_SLICE_MAX * VIP_SW_Q_LEN) \
      )\
     )
/*
 * Total size per allocation for misc-descriptors
 *
 * Allocate 2x32 byte descriptor to support write-descriptors.
 * Same size used for control/config descriptors to avoid additional pool.
 *
 */
#define VPSCORE_VIP_MISC_DESC_SIZE  (VPSCORE_VIP_DESC_SIZE * \
                                     VPSCORE_VIP_MAX_PLANES)



/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static UInt32 gVpsCorePoolObjInitDone = FALSE;

/** \brief Capture Vip Objects */
static VpsCore_VipObj gVcoreVipObjMemPool[VPS_CFG_MEM_VIP_MAX_INST_OBJS];

/** \brief Pool parameters for Capture Vip Objects pool memory */
static BspUtils_PoolParams gVcoreVipObjPoolParams;

/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 gVcoreVipObjMemFlag[VPS_CFG_MEM_VIP_MAX_INST_OBJS];

/** \brief Dss Path Objects */
static VpsCore_VipPathObj  gVcoreVipPathObjMemPool
                           [VPS_CFG_MEM_VIP_MAX_PORT_OBJS];

/** \brief Pool parameters for Dss Path Object pool memory */
static BspUtils_PoolParams gVcoreVipPathObjPoolParams;

/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 gVcoreVipPathObjMemFlag[VPS_CFG_MEM_VIP_MAX_PORT_OBJS];

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVcoreVipMiscDescMemPool, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVcoreVipMiscDescMemPool,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVcoreVipMiscDescMemPool[VPSCORE_VIP_NUM_MISC_DESC_MAX]
                                     [VPSCORE_VIP_MISC_DESC_SIZE];

/*
 * \brief Pool params for descriptor memory.
 */
static BspUtils_PoolParams gVcoreVipMiscDescMemPoolPrm;
/*
 * \brief The flag variable represents whether a handle object is allocated
 *        or not.
 */
static UInt32 gVcoreVipMiscDescMemFlag[VPSCORE_VIP_NUM_MISC_DESC_MAX];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVcoreVipDataDescMemPool, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVcoreVipDataDescMemPool,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8 gVcoreVipDataDescMemPool[VPSCORE_VIP_NUM_DATA_DESC_MAX]
                                     [VPSCORE_VIP_DATA_DESC_SIZE];

/*
 * \brief Pool params for descriptor memory.
 */
static BspUtils_PoolParams gVcoreVipDataDescMemPoolPrm;
/*
 * \brief The flag variable represents whether a handle object is allocated
 *        or not.
 */
static UInt32 gVcoreVipDataDescMemFlag[VPSCORE_VIP_NUM_DATA_DESC_MAX];

/** \brief VIP path core function pointer. */
static const VpsCore_Ops   gVipCoreOps =
{
    &VpsCore_vipGetProperty,          /* Get property */
    &VpsCore_vipOpen,                 /* Open function */
    &VpsCore_vipClose,                /* Close function */
    &VpsCore_vipPathSetConfig,        /* Set config */
    &VpsCore_vipPathGetConfig,        /* Get config */
    &VpsCore_vipControl,              /* Control */
    &VpsCore_vipStart,                /* Start */
    &VpsCore_vipStop,                 /* Stop */
    &VpsCore_vipIsr,                  /* Process */
    NULL,                             /* progBuffer */
    NULL,                             /* putFrames */
    NULL,                             /* getFrames */
    NULL,                             /* Get Error status*/
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void VpsCore_VipGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                          const Vgraph_edgeInfoList *edgeInfoList,
                          VpsCore_VipObj            *pVipInstObj);
Bool VpsCore_VipAncDataExists(const VpsCore_VipPathObj *pathObj);
Bool VpsCore_Vip24BitOut(const VpsCore_VipPathObj *pathObj, UInt32 i);
Bool VpsCore_VipCscReqd(const VpsCore_VipPathObj *pathObj, UInt32 i);
Int32 VpsCore_VipUpdateDefaultCscMode(VpsCore_VipPathObj *pathObj);
Bool VpsCore_VipScReqdAll(const VpsCore_VipPathObj *pathObj);
Bool VpsCore_VipChrdsActive(const VpsCore_VipPathObj *pathObj, UInt32 i);
Bool VpsCore_VipSemiPlanarActive(const VpsCore_VipPathObj *pathObj, UInt32 i);
Bool VpsCore_Vip422SPActive(const VpsCore_VipPathObj *pathObj, UInt32 i);
Int32 VpsCore_VipCreateEdgeList(VpsCore_VipPathObj        *pathObj,
                                const Vgraph_nodeInfoList *nodeList,
                                Vgraph_edgeInfoList       *edgeInfoList);
UInt32 VpsCore_vipGetPort(VpsCore_VipVpdmaDT        outCs,
                          const VpsCore_VipVpdmaDT *portDataType,
                          const VpsHal_VpdmaChanDT *vpdmaDataType,
                          UInt32                    scActive,
                          UInt32                    dstColorSpace);
VpsHal_VpdmaChannel VpsCore_vipGetChan(const VpsCore_VipPathObj *pathObj,
                                       UInt32                    port,
                                       UInt32                    chId);
Int32 VpsCore_VipSetMux(const VpsCore_VipPathObj *pathObj,
                        const Vgraph_nodeInfo    *curNode,
                        VpsHal_VipTopMux          muxName,
                        UInt32                    reset);
Int32 VpsCore_VipCfgMux(const VpsCore_VipPathObj *pathObj,
                        const Vgraph_nodeInfo    *curNode,
                        UInt32                    reset);
Int32 VpsCore_vipPathResAlloc(VpsCore_VipPathObj      *pathObj,
                              const VpsCore_VipParams *pathCfg);
void VpsCore_vipPathResFree(VpsCore_VipPathObj *pathObj);
void VpsCore_vipPathSetControlVars(VpsCore_VipPathObj *pathObj);
void VpsCore_vipPathConfigureNodes(VpsCore_VipPathObj *pathObj);
void VpsCore_vipPathCheck422SPOut(VpsCore_VipPathObj       *pathObj,
                                  void                     *retPrms,
                                  UInt32                    strm,
                                  UInt32                   *numPlanes,
                                  const VpsCore_VipVpdmaDT *portDataType);
void VpsCore_vipPathCheck420SPOut(VpsCore_VipPathObj       *pathObj,
                                  void                     *retPrms,
                                  UInt32                    strm,
                                  UInt32                   *numPlanes,
                                  const VpsCore_VipVpdmaDT *portDataType);
void VpsCore_vipPathCheck422IOut(VpsCore_VipPathObj       *pathObj,
                                 void                     *retPrms,
                                 UInt32                    strm,
                                 UInt32                   *numPlanes,
                                 const VpsCore_VipVpdmaDT *portDataType);
void VpsCore_vipPathCheckRGBOut(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType);
void VpsCore_vipPathCheck444Out(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType);
void VpsCore_vipPathCheckANCOut(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType);
UInt32 VpsCore_vipPathGetDataTypeYUp(const VpsCore_VipPathObj *pathObj,
                                     const Vgraph_nodeInfo    *curNode);
UInt32 VpsCore_vipPathGetDataTypeUVUp(const VpsCore_VipPathObj *pathObj,
                                      const Vgraph_nodeInfo    *curNode);
UInt32 VpsCore_vipPathGetDataTypeYLo(const VpsCore_VipPathObj *pathObj,
                                     const Vgraph_nodeInfo    *curNode);
UInt32 VpsCore_vipPathGetDataTypeUVLo(const VpsCore_VipPathObj *pathObj,
                                      const Vgraph_nodeInfo    *curNode);
void VpsCore_vipPathCreateDesc(VpsCore_VipPathObj *pathObj);
void VpsCore_vipPathCopyConfig(VpsCore_VipPathObj      *pathObj,
                               const VpsCore_VipParams *pathCfg);
Int32 VpsCore_vipValidateVipParams(const VpsCore_VipParams *pathCfg);
Int32 VpsCore_vipPathGetDefConfig(VpsCore_VipPathObj *pathObj,
                                  VpsCore_VipParams  *pathCfg);
Int32 VpsCore_vipPathGetConfig(VpsCore_Handle pathHandle,
                               void          *params);
void VpsCore_vipUpdateVipCoreStats(const VpsCore_VipPathObj *pathObj,
                                   const VpsCore_Frame      *outFrame,
                                   UInt32                    isWrDescValid);
UInt32 VpsCore_vipUpdateDesc(VpsCore_VipPathObj *pathObj, UInt32 chId);
Int32 VpsCore_VipCfgSc(VpsCore_VipPathObj *pathObj, Vgraph_nodeInfo *curNode);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsCore_vipInit
 *  \brief VIP core init function.
 *  Initializes core objects, allocates memory for one instance of VIP.
 *  This function should be called before calling any of VIP core API's.
 *
 *  \param initPrms     [IN] Pointer to the init parameter containing
 *                      instance specific information. #VpsCore_VipInitParams
 *
 *  \return             Returns a handle of type #VpsCore_Inst to the
 *                      VIP instance
 */
VpsCore_Inst VpsCore_vipInit(const VpsCore_VipInitParams *initParams)
{
    Int32           i;
    VpsCore_VipObj *pNewObj = NULL;

    if (FALSE == gVpsCorePoolObjInitDone)
    {
        /* init vip object pool */
        BspUtils_initPool(&gVcoreVipObjPoolParams,
                          (void *) gVcoreVipObjMemPool,
                          VPS_CFG_MEM_VIP_MAX_INST_OBJS,
                          sizeof (VpsCore_VipObj),
                          gVcoreVipObjMemFlag,
                          VpsVipCoreTrace);

        /* init vip object pool */
        BspUtils_initPool(&gVcoreVipPathObjPoolParams,
                          (void *) gVcoreVipPathObjMemPool,
                          VPS_CFG_MEM_VIP_MAX_PORT_OBJS,
                          sizeof (VpsCore_VipPathObj),
                          gVcoreVipPathObjMemFlag,
                          VpsVipCoreTrace);
        BspUtils_initPool(
            &gVcoreVipMiscDescMemPoolPrm,
            (void *) gVcoreVipMiscDescMemPool,
            VPSCORE_VIP_NUM_MISC_DESC_MAX,
            VPSCORE_VIP_MISC_DESC_SIZE,
            gVcoreVipMiscDescMemFlag,
            VpsVipCoreTrace);
        BspUtils_initPool(
            &gVcoreVipDataDescMemPoolPrm,
            (void *) gVcoreVipDataDescMemPool,
            VPSCORE_VIP_NUM_DATA_DESC_MAX,
            VPSCORE_VIP_DATA_DESC_SIZE,
            gVcoreVipDataDescMemFlag,
            VpsVipCoreTrace);
        gVpsCorePoolObjInitDone = (UInt32) TRUE;
    }
    pNewObj = (VpsCore_VipObj *) BspUtils_alloc(&gVcoreVipObjPoolParams,
                                                sizeof (VpsCore_VipObj),
                                                VpsVipCoreTrace);
    if (NULL != pNewObj)
    {
        pNewObj->vipTopHandle  = initParams->vipTopHandle;
        pNewObj->vpdmaHandle   = initParams->vpdmaHandle;
        pNewObj->s0PortAHandle = initParams->s0PortAHandle;
        pNewObj->s0PortBHandle = initParams->s0PortBHandle;
        pNewObj->s1PortAHandle = initParams->s1PortAHandle;
        pNewObj->s1PortBHandle = initParams->s1PortBHandle;
        pNewObj->sc0Handle     = initParams->sc0Handle;
        pNewObj->sc1Handle     = initParams->sc1Handle;
        pNewObj->csc0Handle    = initParams->csc0Handle;
        pNewObj->csc1Handle    = initParams->csc1Handle;
        pNewObj->vemInstId     = initParams->vemInstId;
        pNewObj->vrmInstId     = initParams->vrmInstId;
        pNewObj->numHandles    = 0;

        for (i = 0; i < 4; i++)
        {
            pNewObj->pathObjPool[i] = NULL;
        }

        /* Create default tree with all edges disabled
         * This tree will handle resource management
         */
        BspUtils_memcpy(pNewObj->allVipNodes,
                        vipNodeInfoDefaults,
                        sizeof (vipNodeInfoDefaults));
        pNewObj->vipNodeList.numNodes = GRAPH_VIP_NUM_NODES;
        pNewObj->vipNodeList.list     = pNewObj->allVipNodes;

        BspUtils_memcpy(pNewObj->allEdgeInfo,
                        vipEdgeInfoDefaults,
                        sizeof (vipEdgeInfoDefaults));
        pNewObj->vipEdgeList.numEdges = GRAPH_VIP_NUM_EDGES;
        pNewObj->vipEdgeList.list     = pNewObj->allEdgeInfo;

        VpsCore_VipGraphInit(&pNewObj->vipNodeList,
                             &pNewObj->vipEdgeList,
                             pNewObj);

        /* Enable all VIP sub-modules */
        /* Open all HAL here */
        VpsHal_vipTopResetModule(pNewObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) TRUE, 0);
        /* For Sim only */
        VpsHal_vipTopResetModule(pNewObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) FALSE, 0);
        /* For Sim only */
        VpsHal_vipTopResetModule(pNewObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) TRUE, 0);
        /* For Sim only */
        VpsHal_vipTopResetModule(pNewObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) FALSE, 0);
        /* For Sim only */
        VpsHal_vipTopDisableAllMux(pNewObj->vipTopHandle, VPSHAL_VIP_S0, 0);
        VpsHal_vipTopDisableAllMux(pNewObj->vipTopHandle, VPSHAL_VIP_S1, 0);
    }
    else
    {
        GT_0trace(
            VpsVipCoreTrace, GT_ERR,
            "Allocation of VIP instance Handle failed in VpsCore_vipInit().\r\n");
    }
    /*
     * TODO:
     * malloc of nodeHandlePool
     * Add init calls to all nodes
     * Clk init??
     * VPDMA init
     */
    return (VpsCore_Inst) pNewObj;
}

/**
 *  VpsCore_vipDeInit
 *  \brief VIP core exit function.
 *  Resets all SW state inside the driver for the current VIP instance.
 *
 *  \param pVipHandle   [IN] Handle for the VIP instance to be closed.
 *                      #VpsCore_Inst
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsCore_vipDeInit(VpsCore_Inst pVipHandle)
{
    VpsCore_VipObj *pVipObj = (VpsCore_VipObj *) pVipHandle;

    if (NULL != (void *) pVipObj)
    {
        Vgraph_DeInit((Vgraph_Info *) pVipObj->graph);
        BspUtils_free(&gVcoreVipObjPoolParams, (void *) pVipObj,
                      VpsVipCoreTrace);
    }

    return BSP_SOK;
}

/**
 *  VpsCore_vipGetProperty
 *  \brief Gets the core properties of the VIP core.
 *
 *  \param handle       [IN] VIP instance handle.
 *  \param property     [OUT] Pointer to which the VIP path core properties
 *                      to be copied.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsCore_vipGetProperty(VpsCore_Inst      instObj,
                             VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;

    if (NULL != property)
    {
        property->name = VPSCORE_CAPT_VIP;
        property->isDropDataSupport = TRUE;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsCore_vipOpen
 *  \brief Creates a specified path on the specified VIP instance.
 *
 *  \param pVipHandle     [IN] VIP Instance handle #VpsCore_Inst
 *  \param openPrms       [IN] Callback function information #VpsCore_OpenPrms
 *  \param coreOpenPrms   [IN] Basic source information  #VpsCore_VipOpenParams
 *  \param coreReturnPrms [OUT] Returns interrupt requirement for this path.
 *
 *  \return             If success returns the path handle else returns NULL.
 */
VpsCore_Handle VpsCore_vipOpen(VpsCore_Inst            pVipHandle,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms)
{
    UInt32 i, strm, idx, chId;

    const VpsCore_VipOpenParams   *corePrms =
        (const VpsCore_VipOpenParams *) coreOpenPrms;
    VpsCore_VipOpenRetParams      *retPrms =
        (VpsCore_VipOpenRetParams *) coreReturnPrms;
    VpsCore_VipPathObj            *pathObj     = NULL;
    VpsCore_VipObj                *pVipInstObj = (VpsCore_VipObj *) pVipHandle;
    Int32  retVal = BSP_EFAIL;

    for (i = 0U; i < 4U; i++)
    {
        if (0 == pVipInstObj->pathObjPool[i])
        {
            idx    = i;
            retVal = BSP_SOK;
            break;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* TODO: Add FAIL for PORTA and PORTB re-open */
        pVipInstObj->pathObjPool[idx] = (VpsCore_Handle) BspUtils_alloc(
            &gVcoreVipPathObjPoolParams,
            sizeof (VpsCore_VipPathObj),
            VpsVipCoreTrace);
        pathObj = (VpsCore_VipPathObj *) pVipInstObj->pathObjPool[idx];
        if (NULL == pathObj)
        {
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        GT_assert(VpsVipCoreTrace,
            (corePrms->numChannels < VPSCORE_VIP_CH_ID_MAX));
        for (chId = 0; chId < corePrms->numChannels; chId++)
        {
            retVal =
                Vrm_allocList(pVipInstObj->vrmInstId, &pathObj->listId[chId],
                              VRM_LIST_TYPE_CAPTURE);
            /* TODO: Return error gracefully, not just assert */
            GT_assert(VpsVipCoreTrace, BSP_SOK == retVal);
        }
    }

    if (BSP_SOK == retVal)
    {
        pathObj->drvData   = openPrms->drvData;
        pathObj->handleId  = idx;
        pathObj->parent    = (VpsCore_VipObj *) pVipInstObj;
        pathObj->reqFrmCb  = openPrms->reqFrmCb;
        pathObj->frmDoneCb = openPrms->frmDoneCb;

        for (chId = 0; chId < VPSCORE_VIP_MAX_CH; chId++)
        {
            for (strm = 0; strm < VPSCORE_VIP_STREAM_ID_MAX; strm++)
            {
                for (i = 0; i < VIP_SW_Q_LEN; i++)
                {
                    pathObj->inputFrame[chId][strm][i] = 0;
                }
            }
        }
        pathObj->src              = corePrms->src;
        pathObj->numChannels      = corePrms->numChannels;
        pathObj->muxModeStartChId = corePrms->muxModeStartChId;

        for (chId = 0; chId < VPSCORE_VIP_CH_ID_MAX; chId++)
        {
            pathObj->inpFrmIdx[chId]   = 0;
            pathObj->outFrmIdx[chId]   = 0;
            pathObj->initialWait[chId] = 1U;
            pathObj->descMem[chId]     = NULL;
            for (i = 0; i < VIP_SW_Q_LEN; i++)
            {
                pathObj->wrDescMem[chId][i] = NULL;
            }
        }

        pathObj->descMemSize     = 0;
        pathObj->wrDescMemSize   = 0;
        pathObj->cfgDescMem      = NULL;
        pathObj->cfgDescMemSize  = 0;
        pathObj->ctrlDescMem     = NULL;
        pathObj->ctrlDescMemSize = 0;

        pathObj->edgeList.list     = NULL;
        pathObj->edgeList.numEdges = 0;
        pathObj->nodeList.list     = NULL;
        pathObj->nodeList.numNodes = 0;
        pathObj->multiCaptureValid = (UInt32) FALSE;

        pathObj->isStopped = 1;

        pathObj->forceCscBypass = 0;

        pathObj->setConfigDone = 0;

        pVipInstObj->numHandles += 1;

        GT_assert(VpsVipCoreTrace,
            (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
        for (chId = 0; chId < pathObj->numChannels; chId++)
        {
            retPrms->intrType[chId]      = VPSCORE_VIP_INTRTYPE_VEM;
            retPrms->vemInstId[chId]     = pVipInstObj->vemInstId;
            retPrms->vemEventGroup[chId] = VEM_EG_LISTCOMPLETE;
            retPrms->vemEvent[chId]      = pathObj->listId[chId];
            retPrms->intNum[chId]        = 0U;
        }
    }
    else
    {
        pathObj = NULL;
    }

    return pathObj;
}

/**
 *  VpsCore_vipClose
 *  \brief Closes an already opened handle.
 *
 *  \param handle       [IN] VIP Path handle.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsCore_vipClose(VpsCore_Handle pathHandle)
{
    Int32  retVal = BSP_SOK, chId;
    VpsCore_VipPathObj *pathObj     = (VpsCore_VipPathObj *) pathHandle;
    VpsCore_VipObj     *pVipInstObj = (VpsCore_VipObj *) pathObj->parent;
    UInt32 idx = pathObj->handleId;

    VpsCore_vipPathResFree(pathObj);

    /* Release the VPDMA list allocated for the path. */
    GT_assert(VpsVipCoreTrace,
        (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        retVal = Vrm_releaseList(pVipInstObj->vrmInstId, pathObj->listId[chId]);
    }

    if (NULL != (void *) pVipInstObj->pathObjPool[idx])
    {
        BspUtils_free(&gVcoreVipPathObjPoolParams,
                      (void *) pVipInstObj->pathObjPool[idx],
                      VpsVipCoreTrace);
        pVipInstObj->pathObjPool[idx] = NULL;
    }

    pVipInstObj->numHandles--;
    return (retVal);
}

/**
 *  VpsCore_vipPathGetConfig
 *  \brief Provides the current configuration for the given path handle.
 *         If no configuration has been done, it will provide a fixed default
 *         configuration.
 *
 *  \param pathHandle   [IN] VIP Path handle. #VpsCore_Handle
 *  \param params       [OUT] Pointer where the configuration is to be copied
 *                      #VpsCore_VipParams. This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsCore_vipPathGetConfig(VpsCore_Handle pathHandle,
                               void          *params)
{
    UInt32 strm, pl;
    Int32  retVal = BSP_SOK;
    VpsCore_VipPathObj *pathObj = (VpsCore_VipPathObj *) pathHandle;
    VpsCore_VipParams  *pathCfg = (VpsCore_VipParams *) params;

    if (0 == pathObj->setConfigDone)
    {
        /* retVal = VpsCore_vipPathGetDefConfig(pathObj, pathCfg); */
    }
    else
    {
        pathCfg->srcColorSpace = pathObj->orgSrcColorSpace;
        pathCfg->srcWidth      = pathObj->srcWidth;
        pathCfg->srcHeight     = pathObj->srcHeight;
        pathCfg->numStreams    = pathObj->numStreams;
        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            pathCfg->dstColorSpace[strm] = pathObj->orgDstColorSpace[strm];
            pathCfg->tarWidth[strm]      = pathObj->tarWidth[strm];
            pathCfg->tarHeight[strm]     = pathObj->tarHeight[strm];
            for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
            {
                pathCfg->pitch[strm][pl] = pathObj->pitch[strm][pl];
            }
            pathCfg->scActive[strm] = pathObj->scActive[strm];
        }

        pathCfg->edgeInfoList.numEdges = pathObj->edgeList.numEdges;
        if (NULL != pathCfg->edgeInfoList.list)
        {
            BspUtils_memcpy(
                (void *) pathCfg->edgeInfoList.list,
                (void *) pathObj->edgeList.list,
                sizeof (Vgraph_edgeInfo) *
                pathObj->edgeList.numEdges);
        }

        BspUtils_memcpy((void *) &pathCfg->portCfg,
                        (void *) &pathObj->portCfg,
                        sizeof (Vps_VipPortConfig));

        BspUtils_memcpy((void *) &pathCfg->inCropCfg,
                        (void *) &pathObj->inCropCfg,
                        sizeof (Fvid2_CropConfig));

        BspUtils_memcpy((void *) &pathCfg->inCropCfg,
                        (void *) &pathObj->inCropCfg,
                        sizeof (Fvid2_CropConfig));

        pathCfg->scCfg.bypass           = pathObj->scCfg.bypass;
        pathCfg->scCfg.nonLinear        = pathObj->scCfg.nonLinear;
        pathCfg->scCfg.stripSize        = pathObj->scCfg.stripSize;
        pathCfg->scCfg.enableEdgeDetect = pathObj->scCfg.enableEdgeDetect;
        pathCfg->scCfg.enablePeaking    = pathObj->scCfg.enablePeaking;
        if ((NULL != pathCfg->scCfg.advCfg) &&
            (NULL != pathObj->scCfg.advCfg))
        {
            BspUtils_memcpy((void *) pathCfg->scCfg.advCfg,
                            (void *) pathObj->scCfg.advCfg,
                            sizeof (Vps_ScAdvConfig));
        }

        pathCfg->cscCfg.bypass = pathObj->cscCfg.bypass;
        pathCfg->cscCfg.mode   = pathObj->cscCfg.mode;
        if ((NULL != pathCfg->cscCfg.coeff) &&
            (NULL != pathObj->cscCfg.coeff))
        {
            BspUtils_memcpy((void *) pathCfg->cscCfg.coeff,
                            (void *) pathObj->cscCfg.coeff,
                            sizeof (Vps_CscCoeff));
        }

        BspUtils_memcpy(&pathCfg->subFrmPrms,
                        &pathObj->subFrmPrms,
                        (UInt32) sizeof (VpsCore_SubFrameParams) *
                        VPSCORE_VIP_STREAM_ID_MAX);

        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
            {
                pathCfg->maxOutWidth[strm][pl] =
                    pathObj->maxOutWidth[strm][pl];
                pathCfg->maxOutHeight[strm][pl] =
                    pathObj->maxOutHeight[strm][pl];
            }
            pathCfg->memType[strm] = pathObj->memType[strm];
        }
    }

    return retVal;
}

/**
 *  VpsCore_vipPathSetConfig
 *  \brief Sets the VPE core parameters for a given channel.
 *
 *  \param pathHandle   [IN] VIP Path handle. #VpsCore_Handle
 *  \param params       [IN] Pointer to the input configuration. This should
 *                      point to a valid #VpsCore_VipParams structure.
 *                      This parameter should be non-NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsCore_vipPathSetConfig(VpsCore_Handle pathHandle,
                               const void    *params,
                               void          *setCfgRetPrms)
{
    UInt32 i, prt, strm;
    Int32  retVal = BSP_SOK;
    const VpsCore_VipParams  *pathCfg = (const VpsCore_VipParams *) params;
    VpsCore_VipPathObj       *pathObj = (VpsCore_VipPathObj *) pathHandle;
    Vgraph_nodeInfo          *curNode;
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) setCfgRetPrms;

    VpsCore_VipVpdmaDT       *portDataType  = pathObj->portDataType;
    VpsHal_VpdmaChanDT       *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32                   *strm2PortMap  = pathObj->strm2PortMap;
    UInt32                   *port2StrmMap  = pathObj->port2StrmMap;
    UInt32 numStreams = 0;

    /* Validate the vipParams */
    retVal = VpsCore_vipValidateVipParams(pathCfg);

    if (BSP_SOK == retVal)
    {
        /* Copy the vip parameters into the path handle. */
        VpsCore_vipPathCopyConfig(pathObj, pathCfg);

        pathObj->multiCaptureValid = (UInt32) FALSE;
        if ((pathObj->portCfg.syncType == VPS_VIP_SYNC_TYPE_EMB_2X_422_YUV) ||
            (pathObj->portCfg.syncType == VPS_VIP_SYNC_TYPE_EMB_4X_422_YUV) ||
            (pathObj->portCfg.syncType == VPS_VIP_SYNC_TYPE_EMB_LINE_YUV))
        {
            pathObj->multiCaptureValid = (UInt32) TRUE;
        }

        /* Allocate internal HW resources */
        retVal = VpsCore_vipPathResAlloc(pathObj, pathCfg);
    }

    if (BSP_SOK == retVal)
    {
        setCfgPrms->subFrmVemInstId     = pathObj->parent->vemInstId;
        setCfgPrms->subFrmVemEventGroup = VEM_EG_CLIENT;

        /* Check if CSC is required and set default coeffs */
        retVal = VpsCore_VipUpdateDefaultCscMode(pathObj);
    }

    if (BSP_SOK == retVal)
    {
        VpsCore_vipPathSetControlVars(pathObj);

        /* Identify dataTypes for each VPDMA port in this path */
        i = 0;
        while (i < pathObj->nodeList.numNodes)
        {
            curNode = &pathObj->nodeList.list[i];
            switch (curNode->nodeNum)
            {
                case GRAPH_VIP_S0_Y_UP:
                case GRAPH_VIP_S1_Y_UP:
                {
                    numStreams += VpsCore_vipPathGetDataTypeYUp(pathObj,
                                                                curNode);
                    break;
                }
                case GRAPH_VIP_S0_UV_UP:
                case GRAPH_VIP_S1_UV_UP:
                {
                    numStreams += VpsCore_vipPathGetDataTypeUVUp(pathObj,
                                                                 curNode);
                    break;
                }
                case GRAPH_VIP_S0_Y_LO:
                case GRAPH_VIP_S1_Y_LO:
                {
                    numStreams += VpsCore_vipPathGetDataTypeYLo(pathObj,
                                                                curNode);
                    break;
                }
                case GRAPH_VIP_S0_UV_LO:
                case GRAPH_VIP_S1_UV_LO:
                {
                    numStreams += VpsCore_vipPathGetDataTypeUVLo(pathObj,
                                                                 curNode);
                    break;
                }
                case GRAPH_VIP_S0_PARSER_PORTA_ANC:
                case GRAPH_VIP_S1_PARSER_PORTA_ANC:
                {
                    numStreams++;
                    portDataType[PORTA_ANC] = VCORE_VIPVPDMA_DT_ANC;
                    break;
                }
                case GRAPH_VIP_S0_PARSER_PORTB_ANC:
                case GRAPH_VIP_S1_PARSER_PORTB_ANC:
                {
                    numStreams++;
                    portDataType[PORTB_ANC] = VCORE_VIPVPDMA_DT_ANC;
                    break;
                }
                default:
                    break;
            }
            GT_1trace(VpsVipCoreTrace, GT_DEBUG, "Node ID: %2d\r\n",
                      curNode->nodeNum);
            i++;
        }
        GT_1trace(VpsVipCoreTrace, GT_DEBUG, "Num streams: %2d\r\n", numStreams);

        /* NodeList traversal - input streamId to strmPort mapping */
        for (prt = 0; prt < PORT_MAX; prt++)
        {
            vpdmaDataType[prt] = VPSHAL_VPDMA_CHANDT_INVALID;
            if (prt < (UInt32)(VPSCORE_VIP_STREAM_ID_MAX * FVID2_MAX_PLANES))
            {
                strm2PortMap[(prt * VPSCORE_VIP_STREAM_ID_MAX) + 0U] = PORT_MAX;
                strm2PortMap[(prt * VPSCORE_VIP_STREAM_ID_MAX) + 1U] = PORT_MAX;
                strm2PortMap[(prt * VPSCORE_VIP_STREAM_ID_MAX) + 2U] = PORT_MAX;
                strm2PortMap[(prt * VPSCORE_VIP_STREAM_ID_MAX) + 3U] = PORT_MAX;
            }
            port2StrmMap[prt] = VPSCORE_VIP_STREAM_ID_MAX;
        }

        pathObj->numActivePorts = 0;
        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            UInt32 numPlanes = 0;
            VpsCore_vipPathCheck422SPOut(pathObj, setCfgPrms, strm, &numPlanes,
                                         portDataType);
            VpsCore_vipPathCheck420SPOut(pathObj, setCfgPrms, strm, &numPlanes,
                                         portDataType);
            VpsCore_vipPathCheck422IOut(pathObj, setCfgPrms, strm, &numPlanes,
                                        portDataType);
            VpsCore_vipPathCheckRGBOut(pathObj, setCfgPrms, strm, &numPlanes,
                                       portDataType);
            VpsCore_vipPathCheck444Out(pathObj, setCfgPrms, strm, &numPlanes,
                                       portDataType);
            VpsCore_vipPathCheckANCOut(pathObj, setCfgPrms, strm, &numPlanes,
                                       portDataType);
            if (0U == numPlanes)
            {
                /* Stream was not allocated - free resources and return error */
                retVal = BSP_EFAIL;
                break;
            }
            pathObj->numPlanes[strm] = numPlanes;
            pathObj->numDesc[strm]   = numPlanes * pathObj->numChannels;
        }

        if (BSP_SOK == retVal)
        {
            VpsCore_vipPathCreateDesc(pathObj);
            pathObj->setConfigDone = 1;
        }
    }

    if (BSP_SOK != retVal)
    {
        VpsCore_vipPathResFree(pathObj);
        pathObj->setConfigDone = 0;
    }

    return retVal;
}

/**
 *  VpsCore_vipStart
 *  \brief Start capture.
 *  This will post the initial VPDMA descriptors to enable the VIP port
 *
 *  \param pathHandle       Path handle #VpsCore_Handle returned by
 *                          VpsCore_vipOpen
 *
 *  \return                 success: BSP_SOK
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipStart(VpsCore_Handle pathHandle)
{
    VpsCore_VipPathObj *pathObj = (VpsCore_VipPathObj *) pathHandle;
    UInt32 listSize, chId, cookie;
    Int32  retVal = BSP_SOK;

    if (0 == pathObj->setConfigDone)
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        GT_assert(VpsVipCoreTrace,
            (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
        for (chId = 0; chId < pathObj->numChannels; chId++)
        {
            pathObj->inpFrmIdx[chId]   = 0;
            pathObj->outFrmIdx[chId]   = 0;
            pathObj->initialWait[chId] = 1U;
        }

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        /* Individual module reset not supported */
#else
        VpsCore_vipPortAndModulesReset(pathObj);
#endif
        VpsCore_vipPathConfigureNodes(pathObj);
        VpsCore_vipPathCreateDesc(pathObj);

        /* Disable global interrupts */
        cookie = BspOsal_disableInterrupt();

        GT_assert(VpsVipCoreTrace,
            (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
        for (chId = 0; chId < pathObj->numChannels; chId++)
        {
            listSize = VpsCore_vipUpdateDesc(pathObj, chId);

            pathObj->isStopped = 0;
            /**Post List to VPDMA -- TODO enablecheck */
            VpsHal_vpdmaPostList(pathObj->vpdmaHandle,         /*handle*/
                                 (UInt8) pathObj->listId[chId],/*listNum*/
                                 VPSHAL_VPDMA_LT_NORMAL,       /*listType*/
                                 (Ptr) pathObj->descMem[chId], /* listAddr*/
                                 listSize,                     /*listSize*/
                                 0                             /*enableCheck*/
                                 );
        }

        /* Restore global interrupts */
        BspOsal_restoreInterrupt(cookie);

        VpsHal_vipPortEnable(pathObj->vipPortHandle, (UInt32) TRUE, 0);

        /* Release clear async FIFO reset */
        VpsCore_vipResetFIFO(pathObj, (UInt32) FALSE);
    }
    return retVal; /* TODO: Error checks */
}

/**
 *  VpsCore_vipStop
 *  \brief Stop capture.
 *  This will post the abort descriptors for the capture channel and disable the
 *  VIP port
 *
 *  \param pathHandle       Path handle #VpsCore_Handle returned by
 *                          VpsCore_vipOpen
 *
 *  \return                 success: BSP_SOK
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipStop(VpsCore_Handle pathHandle)
{
    Int32 retVal;
    VpsCore_VipPathObj *pathObj = (VpsCore_VipPathObj *) pathHandle;

    pathObj->isStopped = 1;

    retVal = VpsHal_vipPortEnable(pathObj->vipPortHandle, (UInt32) FALSE, 0);
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* Individual module reset not supported */
#else
    if (BSP_SOK == retVal)
    {
        retVal = VpsCore_vipPortAndModulesReset(pathObj);
    }
#endif
    return retVal;
}

/**
 *  VpsCore_vipControl
 *  \brief This is a control call to SET/GET VIP Core related parameters/status
 *  which are not supported by the default API
 *
 *  \param pathHandle       Path handle #VpsCore_Handle returned by
 *                          VpsCore_vipOpen
 *  \param cmd              IOCTL Command to SET/GET parameters/status.
 *
 *  \param appArgs          IOCTL specific arguments provided by the
 *                          application.
 *                          To SET the VIP core parameters this args shall
 *                          point to parameters that shall be provided by
 *                          the Application.
 *                          To GET the VIP core status this args shall
 *                          point to parameters that shall be provided to
 *                          the Application by the VIP Core.
 *  \param drvArgs          IOCTL specific arguments that which are provided by
 *                          the driver to the Core.
 *
 *  \return                 success: BSP_SOK, control call serviced.
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipControl(VpsCore_Handle handle,
                         UInt32         cmd,
                         Ptr            appArgs,
                         Ptr            drvArgs)
{
    Int32 retVal = BSP_SOK;

    GT_assert(VpsVipCoreTrace, NULL != handle);

    if (VPSCORE_COMMON_HANDLE == (UInt32) handle)
    {
        /* IOCTLs supported by the Global handle for VIP Core. */
        switch (cmd)
        {
            case VPSCORE_VIP_IOCTL_SET_MF_CFG:
            {
                VpsCore_VipObj *vipInstObj;
                vipInstObj = (VpsCore_VipObj *) drvArgs;

                /* Validate the appArgs */
                retVal = VpsCore_vipCheckMaxSizeParams(
                    (Vps_VpdmaMaxSizeParams *) appArgs);

                /* HAL api to perform the actual VPDMA register set. */
                if (BSP_SOK == retVal)
                {
                    VpsHal_vpdmaSetFrameSizeReg(vipInstObj->vpdmaHandle,
                                                appArgs);
                }

                break;
            }

            default:
                GT_0trace(VpsVipCoreTrace, GT_ERR, "Unsupported IOCTL\r\n");
                retVal = BSP_EUNSUPPORTED_CMD;
                break;
        }
    }
    else
    {
        /* IOCTLs supported by the VIP Core path handle. */
        VpsCore_VipPathObj *pathObj = (VpsCore_VipPathObj *) handle;
        switch (cmd)
        {
            case VPSCORE_VIP_IOCTL_GET_SUBFRM_INFO:
            {
                VpsHal_VipStatus         vipStatus;
                VpsCore_VipSubFrameInfo *vipSubFrameInfo =
                    (VpsCore_VipSubFrameInfo *) drvArgs;
                VpsHal_VpdmaChannel      vpdmaCh;
                UInt32 streamId;

                streamId = vipSubFrameInfo->streamId;
                vpdmaCh  = (VpsHal_VpdmaChannel) pathObj-> \
                           strm2VpdmaChanMap[0U][streamId * FVID2_MAX_PLANES];

                VpsHal_vipGetSrcStatus(pathObj->vipPortHandle,
                                       vpdmaCh,
                                       &vipStatus,
                                       NULL);
                vipSubFrameInfo->currFid = vipStatus.curFid;
                vipSubFrameInfo->prevFid = vipStatus.prevFid;
                vipSubFrameInfo->height  = vipStatus.height;
                vipSubFrameInfo->width   = vipStatus.width;
                break;
            }

            case VPSCORE_VIP_IOCTL_RESET_PORT:
            {
                VpsCore_vipPortAndModulesReset(pathObj);
                break;
            }

            case VPSCORE_VIP_IOCTL_GET_CURCAPTFRM_INFO:
            {
                VpsCore_Frame *curFrmptr = (VpsCore_Frame *) drvArgs;
                VpsCore_Frame *temp;
                UInt32         i, j;

                temp = VpsCore_vipGetCurrentCaptFrame(pathObj);
                for (i = 0; i < FVID2_MAX_FIELDS; i++)
                {
                    for (j = 0; j < FVID2_MAX_PLANES; j++)
                    {
                        curFrmptr->addr[i][j] = temp->addr[i][j];
                    }
                }
                curFrmptr->fid    = temp->fid;
                curFrmptr->height = temp->height;
                curFrmptr->width  = temp->width;

                break;
            }

            case VPSCORE_VIP_IOCTL_GET_VEM_PARAMS:
            {
                VpsCore_VipObj           *pVipObj =
                    (VpsCore_VipObj *) appArgs;
                VpsCore_VipPathObj       *pCoreHandle =
                    (VpsCore_VipPathObj *) (handle);
                VpsCore_VipOpenRetParams *retparams =
                    (VpsCore_VipOpenRetParams *) drvArgs;
                UInt32 port;
                UInt32 slice;

                /* Loop is not required for overflow interrupt */
                retparams->intrType[0U]      = VPSCORE_VIP_INTRTYPE_VEM;
                retparams->vemEventGroup[0U] = VEM_EG_OVERFLOW;
                /*Get the port patams form HAL*/
                VpsHal_vipPortGetPortParams(pCoreHandle->vipPortHandle, &port,
                                            &slice);
                if (slice == VPSHAL_VIP_S0)
                {
                    if (port == VPSHAL_VIP_PORT_A)
                    {
                        retparams->vemEvent[0U] =
                            VEM_SLICE0_PARSER_INT_RAW_PORTA;
                    }
                    else if (port == VPSHAL_VIP_PORT_B)
                    {
                        retparams->vemEvent[0U] =
                            VEM_SLICE0_PARSER_INT_RAW_PORTB;
                    }
                    else
                    {
                        retVal = BSP_EINVALID_PARAMS;
                    }
                }
                else if (slice == VPSHAL_VIP_S1)
                {
                    if (port == VPSHAL_VIP_PORT_A)
                    {
                        retparams->vemEvent[0U] =
                            VEM_SLICE1_PARSER_INT_RAW_PORTA;
                    }
                    else if (port == VPSHAL_VIP_PORT_B)
                    {
                        retparams->vemEvent[0U] =
                            VEM_SLICE1_PARSER_INT_RAW_PORTB;
                    }
                    else
                    {
                        retVal = BSP_EINVALID_PARAMS;
                    }
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
                retparams->vemInstId[0U] = pVipObj->vemInstId;

                break;
            }

            case VPSCORE_VIP_IOCTL_GET_OVERFLOW_REG_STATUS:
            {
                VpsCore_VipPathObj *pCoreHandle =
                    (VpsCore_VipPathObj *) (handle);
                UInt32 *retParams =
                    (UInt32 *) drvArgs;

                VpsHal_vipPortGetOverflowStatus(pCoreHandle->vipPortHandle,
                                                retParams);
                break;
            }

            case VPSCORE_VIP_IOCTL_RESET_VIP_PORT:
            {
                VpsHal_vipPortReset(pathObj->vipPortHandle, 0);
                break;
            }

            default:
                GT_0trace(VpsVipCoreTrace, GT_ERR,
                          "Unsupported IOCTL for VIP core path handle!!\r\n");
                retVal = BSP_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

/**
 *  VpsCore_vipIsr
 *  \brief ISR callback to be called after recieving the configured interrupt.
 *  Currently, this supports only single channel capture.
 *  ISR registration will be handled by upper layer of SW
 *
 *  \param pathHandle       Path handle #VpsCore_Handle returned by
 *                          VpsCore_vipOpen
 *  \param chId             Channel index. Used in multi-channel capture.
 *
 *  \return                 success: BSP_SOK
 *                          failure: BSP_EFAIL
 */
Int32 VpsCore_vipIsr(VpsCore_Handle pathHandle, UInt32 chId)
{
    VpsCore_VipPathObj *pathObj = (VpsCore_VipPathObj *) pathHandle;
    UInt32 listSize;
    Int32  retVal = BSP_SOK;

    if (1 == pathObj->isStopped)
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        pathObj->inpFrmIdx[chId]++;
        if (0U == pathObj->initialWait[chId])
        {
            pathObj->outFrmIdx[chId]++;
        }
        if (pathObj->inpFrmIdx[chId] >= VIP_HW_Q_LEN)
        {
            pathObj->initialWait[chId] = 0;
        }
        if (pathObj->inpFrmIdx[chId] >= VIP_SW_Q_LEN)
        {
            pathObj->inpFrmIdx[chId] = 0;
        }
        if (pathObj->outFrmIdx[chId] >= VIP_SW_Q_LEN)
        {
            pathObj->outFrmIdx[chId] = 0;
        }
        listSize = VpsCore_vipUpdateDesc(pathObj, chId);

        /**Post List to VPDMA -- TODO enablecheck */
        VpsHal_vpdmaPostList(pathObj->vpdmaHandle,         /* handle      */
                             (UInt8) pathObj->listId[chId],/* listNum     */
                             VPSHAL_VPDMA_LT_NORMAL,       /* listType    */
                             (Ptr) pathObj->descMem[chId], /* listAddr    */
                             listSize,                     /* listSize    */
                             0                             /* enableCheck */
                             );
    }
    return retVal;
}

/**
 *  VpsCore_vipGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_vipGetCoreOps(void)
{
    return &gVipCoreOps;
}

void VpsCore_VipGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                          const Vgraph_edgeInfoList *edgeInfoList,
                          VpsCore_VipObj            *pVipInstObj)
{
    pVipInstObj->graphObj.nodeList = &pVipInstObj->graphObjNodeList;
    pVipInstObj->graphObj.edgeList = &pVipInstObj->graphObjEdgeList;
    pVipInstObj->graph = &pVipInstObj->graphObj;
    Vgraph_Init(pathNodeList, edgeInfoList, (Vgraph_Info *) pVipInstObj->graph);
}

Bool VpsCore_VipAncDataExists(const VpsCore_VipPathObj *pathObj)
{
    UInt32 i;
    Bool   retVal = FALSE;
    for (i = 0; i < pathObj->numStreams; i++)
    {
        if (FVID2_DF_RAW_VBI == pathObj->dstColorSpace[i])
        {
            retVal = TRUE;
        }
    }
    return (retVal);
}

Bool VpsCore_Vip24BitOut(const VpsCore_VipPathObj *pathObj, UInt32 i)
{
    Bool retVal = FALSE;
    if (FVID2_DF_YUV444I == pathObj->dstColorSpace[i])
    {
        retVal = TRUE;
    }
    if ((Int32) TRUE == Fvid2_isDataFmtRgb(pathObj->dstColorSpace[i]))
    {
        retVal = TRUE;
    }

    return (retVal);
}

Bool VpsCore_VipCscReqd(const VpsCore_VipPathObj *pathObj, UInt32 i)
{
    Bool isYuvSrc = FALSE;
    Bool retVal   = FALSE;
    Bool dataFmtYuv, dataFmtYuv444, dataFmtYuv422, dataFmtYuv420;
    if ((Int32) TRUE == Fvid2_isDataFmtYuv(pathObj->srcColorSpace))
    {
        isYuvSrc = TRUE;
    }

    if ((Int32) TRUE == Fvid2_isDataFmtRgb(pathObj->dstColorSpace[i]))
    {
        if (isYuvSrc)
        {
            retVal = TRUE;
        }
    }

    if ((Int32) TRUE == Fvid2_isDataFmtYuv(pathObj->dstColorSpace[i]))
    {
        if (!isYuvSrc)
        {
            retVal = TRUE;
        }
    }

    /* 16b - 24b conversion requires CSC */
    dataFmtYuv    = (Bool) Fvid2_isDataFmtYuv(pathObj->srcColorSpace);
    dataFmtYuv444 = (Bool) Fvid2_isDataFmtYuv444(pathObj->srcColorSpace);
    if ((FVID2_DF_YUV444I == pathObj->dstColorSpace[i]) &&
        (TRUE == dataFmtYuv) &&
        (FALSE == dataFmtYuv444))
    {
        retVal = TRUE;
    }

    /* 24b - 16b conversion requires CSC */
    dataFmtYuv422 = (Bool) Fvid2_isDataFmtYuv422(pathObj->dstColorSpace[i]);
    dataFmtYuv420 = (Bool) Fvid2_isDataFmtYuv420(pathObj->dstColorSpace[i]);
    if ((FVID2_DF_YUV444P == pathObj->srcColorSpace) &&
        ((TRUE == dataFmtYuv422) || (TRUE == dataFmtYuv420)))
    {
        retVal = TRUE;
    }

    return (retVal);
}

Int32 VpsCore_VipUpdateDefaultCscMode(VpsCore_VipPathObj *pathObj)
{
    Int32  retVal = BSP_SOK;
    Bool   isYuvSrc;
    UInt32 strm;

    isYuvSrc = FALSE;

    /* Set default mode as bypass.
     * This is required in 444:420 conversion, 422:444 conversion, RAW outputs
     * with multiple streams, etc.
     */
    pathObj->cscMode   = VPS_CSC_MODE_HDTV_FULL_RANGE_Y2R;
    pathObj->cscBypass = 1;

    for (strm = 0U; strm < pathObj->numStreams; strm++)
    {
        if (TRUE == (Bool) Fvid2_isDataFmtYuv(pathObj->srcColorSpace))
        {
            isYuvSrc = TRUE;
        }
        if (TRUE == (Bool) Fvid2_isDataFmtRgb(pathObj->dstColorSpace[strm]))
        {
            if (isYuvSrc)
            {
                pathObj->cscMode   = VPS_CSC_MODE_HDTV_FULL_RANGE_Y2R;
                pathObj->cscBypass = 0;
            }
        }

        if (TRUE == (Bool) Fvid2_isDataFmtYuv(pathObj->dstColorSpace[strm]))
        {
            if (!isYuvSrc)
            {
                pathObj->cscMode   = VPS_CSC_MODE_HDTV_FULL_RANGE_R2Y;
                pathObj->cscBypass = 0;
            }
        }
    }
    if ((1 == pathObj->forceCscBypass) &&
        (0 == pathObj->cscBypass))
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

Bool VpsCore_VipScReqdAll(const VpsCore_VipPathObj *pathObj)
{
    UInt32 i;
    Bool   retVal = FALSE;
    for (i = 0; i < pathObj->numStreams; i++)
    {
        if (1U == pathObj->scActive[i])
        {
            retVal = TRUE;
        }
    }
    return (retVal);
}

Bool VpsCore_VipChrdsActive(const VpsCore_VipPathObj *pathObj, UInt32 i)
{
    Bool retVal = FALSE;
    if ((FVID2_DF_YUV420SP_UV == pathObj->dstColorSpace[i]) ||
        (FVID2_DF_YUV420SP_VU == pathObj->dstColorSpace[i]))
    {
        retVal = TRUE;
    }
    return (retVal);
}

Bool VpsCore_VipSemiPlanarActive(const VpsCore_VipPathObj *pathObj, UInt32 i)
{
    Bool retVal = FALSE;
    if ((FVID2_DF_YUV422SP_UV == pathObj->dstColorSpace[i]) ||
        (FVID2_DF_YUV422SP_VU == pathObj->dstColorSpace[i]) ||
        (FVID2_DF_YUV420SP_UV == pathObj->dstColorSpace[i]) ||
        (FVID2_DF_YUV420SP_VU == pathObj->dstColorSpace[i]))
    {
        retVal = TRUE;
    }
    return (retVal);
}

Bool VpsCore_Vip422SPActive(const VpsCore_VipPathObj *pathObj, UInt32 i)
{
    Bool retVal = FALSE;
    if ((FVID2_DF_YUV422SP_UV == pathObj->dstColorSpace[i]) ||
        (FVID2_DF_YUV422SP_VU == pathObj->dstColorSpace[i]))
    {
        retVal = TRUE;
    }
    return (retVal);
}

Int32 VpsCore_VipCreateEdgeList(VpsCore_VipPathObj        *pathObj,
                                const Vgraph_nodeInfoList *nodeList,
                                Vgraph_edgeInfoList       *edgeInfoList)
{
    UInt32           idx = 0, i, streamsAdded = 0;
    UInt32           firstNode, dataNode, startNode, endNode;
    UInt32           cscSrcNode = GRAPH_VIP_INVALID, cscNode = GRAPH_VIP_INVALID;
    UInt32           scSrcNode  = GRAPH_VIP_INVALID, scNode  = GRAPH_VIP_INVALID;
    UInt32           chrds0SrcOnNode = GRAPH_VIP_INVALID, chrds0SrcOffNode = GRAPH_VIP_INVALID;
    UInt32           chrds1SrcOnNode = GRAPH_VIP_INVALID, chrds1SrcOffNode = GRAPH_VIP_INVALID;
    UInt32           chrds0Node      = GRAPH_VIP_INVALID, chrds1Node       = GRAPH_VIP_INVALID;
    Bool             chrds0Added  = FALSE, chrds1Added = FALSE;
    Bool             chrds1Bypass = FALSE, rgbHiNodeAdded = FALSE;
    UInt32           rgbHiNode, yUpNode, uvUpNode, yLoNode, uvLoNode;
    UInt32           portARgb, portALuma, portAChroma;
    UInt32           portBRgb, portBLuma, portBChroma;
    Bool             cscAdded        = FALSE;
    Bool             scAdded         = FALSE;
    Bool             dataCscAdded    = FALSE;
    Bool             dataScAdded     = FALSE;
    Bool             cscScAdded      = FALSE;
    Bool             scChrds0Added   = FALSE;
    Bool             scChrds1Added   = FALSE;
    Bool             chrds1OnNeeded  = FALSE;
    Bool             chrds1OffNeeded = FALSE;
    Bool             cscChrds0Added  = FALSE;
    Bool             cscChrds1Added  = FALSE;
    Bool             dataChrds0Added = FALSE;
    Bool             dataChrds1Added = FALSE;
    Bool             dataChrdsForced = FALSE;
    Bool             dataNode24Bit;
    UInt32           numActiveStreams;
    Bool             allowDirect422Path = FALSE;
    UInt32           slice = VPSHAL_NUM_VIP_SLICES;
    Bool             scReqd;
    Bool             cscReqd;
    Bool             cscAvl = FALSE;
    Bool             scAvl;
    Bool             chrds0Avl = FALSE, chrds1Avl = FALSE;
    Bool             chrdsReqd;
    UInt32           chrds0SrcNode, chrds1SrcNode;
    Bool             chrds1outLoAdded = FALSE;
    Bool             chrds1outUpAdded = FALSE;
    Bool             yLoAdded         = FALSE;
    Bool             uvLoAdded        = FALSE;
    Bool             yUpAdded         = FALSE;
    Bool             uvUpAdded        = FALSE;
    Bool             yLoAvl, uvLoAvl, yUpAvl, uvUpAvl;
    Vgraph_edgeInfo *list   = edgeInfoList->list;
    Int32            retVal = BSP_SOK;
    Bool             tmp;
    Bool             spActive, is24BitOut;
    Bool             gotoNextIteration;

    /* Remove gcc compiler warning of maybe-uninitialized */
    yLoAvl    = uvLoAvl  =  yUpAvl      = uvUpAvl  = FALSE;
    yLoAvl    = uvLoAvl   = yUpAvl      = uvUpAvl  = FALSE;
    startNode = endNode   = rgbHiNode   = GRAPH_VIP_INVALID;
    yUpNode   = uvUpNode  = yLoNode     = uvLoNode = GRAPH_VIP_INVALID;
    portARgb  = portALuma = portAChroma = GRAPH_VIP_INVALID;
    portBRgb  = portBLuma = portBChroma = GRAPH_VIP_INVALID;

    /* Identify Slice */
    switch (pathObj->src)
    {
        case S0_PORTA_08:
        case S0_PORTA_16:
        case S0_PORTA_24:
        case S0_PORTB_08:
        case S0_PORTA_MULT:
        case S0_PORTB_MULT:
            slice = VPSHAL_VIP_S0;
            break;
        case S1_PORTA_08:
        case S1_PORTA_16:
        case S1_PORTA_24:
        case S1_PORTB_08:
        case S1_PORTA_MULT:
        case S1_PORTB_MULT:
            slice = VPSHAL_VIP_S1;
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }

    /* Initialize nodes */
    switch (slice)
    {
        case VPSHAL_VIP_S0:
            cscNode          = GRAPH_VIP_S0_CSC;
            cscSrcNode       = GRAPH_VIP_S0_CSC_SRC;
            scNode           = GRAPH_VIP_S0_SC;
            scSrcNode        = GRAPH_VIP_S0_SC_SRC;
            chrds0SrcOnNode  = GRAPH_VIP_S0_CHRDS0_ON;
            chrds0SrcOffNode = GRAPH_VIP_S0_CHRDS0_OFF;
            chrds0Node       = GRAPH_VIP_S0_CHRDS0;
            chrds1SrcOnNode  = GRAPH_VIP_S0_CHRDS1_ON;
            chrds1SrcOffNode = GRAPH_VIP_S0_CHRDS1_OFF;
            chrds1Node       = GRAPH_VIP_S0_CHRDS1;
            rgbHiNode        = GRAPH_VIP_S0_RGB_HI;
            yUpNode          = GRAPH_VIP_S0_Y_UP;
            uvUpNode         = GRAPH_VIP_S0_UV_UP;
            yLoNode          = GRAPH_VIP_S0_Y_LO;
            uvLoNode         = GRAPH_VIP_S0_UV_LO;
            portARgb         = GRAPH_VIP_S0_PORTA_RGB;
            portBRgb         = GRAPH_VIP_S0_PORTB_RGB;
            portALuma        = GRAPH_VIP_S0_PORTA_LUMA;
            portAChroma      = GRAPH_VIP_S0_PORTA_CHROMA;
            portBLuma        = GRAPH_VIP_S0_PORTB_LUMA;
            portBChroma      = GRAPH_VIP_S0_PORTB_CHROMA;
            break;
        case VPSHAL_VIP_S1:
            cscNode          = GRAPH_VIP_S1_CSC;
            cscSrcNode       = GRAPH_VIP_S1_CSC_SRC;
            scNode           = GRAPH_VIP_S1_SC;
            scSrcNode        = GRAPH_VIP_S1_SC_SRC;
            chrds0SrcOnNode  = GRAPH_VIP_S1_CHRDS0_ON;
            chrds0SrcOffNode = GRAPH_VIP_S1_CHRDS0_OFF;
            chrds0Node       = GRAPH_VIP_S1_CHRDS0;
            chrds1SrcOnNode  = GRAPH_VIP_S1_CHRDS1_ON;
            chrds1SrcOffNode = GRAPH_VIP_S1_CHRDS1_OFF;
            chrds1Node       = GRAPH_VIP_S1_CHRDS1;
            rgbHiNode        = GRAPH_VIP_S1_RGB_HI;
            yUpNode          = GRAPH_VIP_S1_Y_UP;
            uvUpNode         = GRAPH_VIP_S1_UV_UP;
            yLoNode          = GRAPH_VIP_S1_Y_LO;
            uvLoNode         = GRAPH_VIP_S1_UV_LO;
            portARgb         = GRAPH_VIP_S1_PORTA_RGB;
            portBRgb         = GRAPH_VIP_S1_PORTB_RGB;
            portALuma        = GRAPH_VIP_S1_PORTA_LUMA;
            portAChroma      = GRAPH_VIP_S1_PORTA_CHROMA;
            portBLuma        = GRAPH_VIP_S1_PORTB_LUMA;
            portBChroma      = GRAPH_VIP_S1_PORTB_CHROMA;
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }

    /* Connect nodes at input port */
    switch (pathObj->src)
    {
        case S0_PORTA_08:
        case S0_PORTA_16:
        case S0_PORTA_24:
        case S0_PORTA_MULT:
        {
            startNode = GRAPH_VIP_S0_PARSER_PORTA;
            endNode   = GRAPH_VIP_S0_PARSER_PORTA_INTF;
            break;
        }
        case S0_PORTB_08:
        case S0_PORTB_MULT:
        {
            startNode = GRAPH_VIP_S0_PARSER_PORTB;
            endNode   = GRAPH_VIP_S0_PARSER_PORTB_INTF;
            break;
        }
        case S1_PORTA_08:
        case S1_PORTA_16:
        case S1_PORTA_24:
        case S1_PORTA_MULT:
        {
            startNode = GRAPH_VIP_S1_PARSER_PORTA;
            endNode   = GRAPH_VIP_S1_PARSER_PORTA_INTF;
            break;
        }
        case S1_PORTB_08:
        case S1_PORTB_MULT:
        {
            startNode = GRAPH_VIP_S1_PARSER_PORTB;
            endNode   = GRAPH_VIP_S1_PARSER_PORTB_INTF;
            break;
        }
        default:
            retVal = BSP_EFAIL;
            break;
    }
    Vgraph_AddEdge(&list[idx], startNode, endNode);
    idx++;
    firstNode = startNode;

    /* Add parser nodes */
    startNode = endNode;
    switch (pathObj->src)
    {
        case S0_PORTA_08:
        case S0_PORTA_MULT:
            endNode = GRAPH_VIP_S0_PARSER_PORTA_08;
            break;
        case S0_PORTA_16:
            endNode = GRAPH_VIP_S0_PARSER_PORTA_16;
            break;
        case S0_PORTA_24:
            endNode = GRAPH_VIP_S0_PARSER_PORTA_24;
            break;
        case S0_PORTB_08:
        case S0_PORTB_MULT:
            endNode = GRAPH_VIP_S0_PARSER_PORTB_08;
            break;
        case S1_PORTA_08:
        case S1_PORTA_MULT:
            endNode = GRAPH_VIP_S1_PARSER_PORTA_08;
            break;
        case S1_PORTA_16:
            endNode = GRAPH_VIP_S1_PARSER_PORTA_16;
            break;
        case S1_PORTA_24:
            endNode = GRAPH_VIP_S1_PARSER_PORTA_24;
            break;
        case S1_PORTB_08:
        case S1_PORTB_MULT:
            endNode = GRAPH_VIP_S1_PARSER_PORTB_08;
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }
    Vgraph_AddEdge(&list[idx], startNode, endNode);
    idx++;

    /* 16b and 8b inputs follow same path inside VIP - so connect them to
     *   a common node - GRAPH_VIP_SX_PARSER_PORTA_08_16 */
    if ((S0_PORTA_08 == pathObj->src) ||
        (S0_PORTA_16 == pathObj->src) ||
        (S1_PORTA_08 == pathObj->src) ||
        (S1_PORTA_16 == pathObj->src) ||
        (S0_PORTA_MULT == pathObj->src) ||
        (S1_PORTA_MULT == pathObj->src))
    {
        startNode = endNode;
        switch (slice)
        {
            case VPSHAL_VIP_S0:
                endNode = GRAPH_VIP_S0_PARSER_PORTA_08_16;
                break;
            case VPSHAL_VIP_S1:
                endNode = GRAPH_VIP_S1_PARSER_PORTA_08_16;
                break;
            default:
                retVal = BSP_EFAIL;
                break;
        }
        Vgraph_AddEdge(&list[idx], startNode, endNode);
        idx++;
    }
    /* dataNode is the node which can be connected to different modules inside
     * VIP. Three values are possible per slice -
     * GRAPH_VIP_SX_PARSER_PORTA_08_16
     * GRAPH_VIP_SX_PARSER_PORTA_24
     * GRAPH_VIP_SX_PARSER_PORTB_08 */
    dataNode = endNode;

    /* Add ancillary data nodes and corresponding VPDMA channel nodes */
    if (BSP_SOK == retVal)
    {
        if (VpsCore_VipAncDataExists(pathObj))
        {
            switch (pathObj->src)
            {
                case S0_PORTA_08:
                case S0_PORTA_16:
                case S0_PORTA_24:
                    endNode = GRAPH_VIP_S0_PARSER_PORTA_ANC;
                    break;
                case S0_PORTB_08:
                    endNode = GRAPH_VIP_S0_PARSER_PORTB_ANC;
                    break;
                case S1_PORTA_08:
                case S1_PORTA_16:
                case S1_PORTA_24:
                    endNode = GRAPH_VIP_S1_PARSER_PORTA_ANC;
                    break;
                case S1_PORTB_08:
                    endNode = GRAPH_VIP_S1_PARSER_PORTB_ANC;
                    break;
                default:
                    retVal = BSP_EFAIL;
                    break;
            }
            Vgraph_AddEdge(&list[idx], firstNode, endNode);
            idx++;

            startNode = endNode;
            switch (pathObj->src)
            {
                case S0_PORTA_08:
                case S0_PORTA_16:
                case S0_PORTA_24:
                    endNode = GRAPH_VIP_S0_MULT_ANCA_SRC0;
                    break;
                case S0_PORTB_08:
                    endNode = GRAPH_VIP_S0_MULT_ANCB_SRC0;
                    break;
                case S1_PORTA_08:
                case S1_PORTA_16:
                case S1_PORTA_24:
                    endNode = GRAPH_VIP_S1_MULT_ANCA_SRC0;
                    break;
                case S1_PORTB_08:
                    endNode = GRAPH_VIP_S1_MULT_ANCB_SRC0;
                    break;
                default:
                    retVal = BSP_EFAIL;
                    break;
            }
            Vgraph_AddEdge(&list[idx], startNode, endNode);
            idx++;
            streamsAdded++;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Get availability of CSC/SC/CHR_DSX from Vgraph module */
        cscAvl    = Vgraph_isNodeInputAvailable(nodeList, cscSrcNode);
        scAvl     = Vgraph_isNodeInputAvailable(nodeList, scSrcNode);
        chrds0Avl = Vgraph_isNodeInputAvailable(nodeList, chrds0Node);
        chrds1Avl = Vgraph_isNodeInputAvailable(nodeList, chrds1Node);
        yLoAvl    = Vgraph_isNodeInputAvailable(nodeList, yLoNode);
        uvLoAvl   = Vgraph_isNodeInputAvailable(nodeList, uvLoNode);
        yUpAvl    = Vgraph_isNodeInputAvailable(nodeList, yUpNode);
        uvUpAvl   = Vgraph_isNodeInputAvailable(nodeList, uvUpNode);
    }

    /* Add CSC to path if required and available */
    for (i = 0; ((i < pathObj->numStreams) && (BSP_SOK == retVal)); i++)
    {
        cscReqd = VpsCore_VipCscReqd(pathObj, i);

        if (FVID2_DF_RAW_VBI == pathObj->dstColorSpace[i])
        {
            cscReqd = FALSE;
        }

        if (cscReqd)
        {
            /* Connect dataNode to CSC */
            if (cscAvl)
            {
                if ((!dataCscAdded) && (BSP_SOK == retVal))
                {
                    Vgraph_AddEdge(&list[idx], dataNode, cscSrcNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], cscSrcNode, cscNode);
                    idx++;
                    cscAdded     = TRUE;
                    dataCscAdded = TRUE;
                    break;
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
        }
    }

    /* Add SC to path if required and available */
    for (i = 0; ((i < pathObj->numStreams) && (BSP_SOK == retVal)); i++)
    {
        scReqd  = (Bool) (1U == pathObj->scActive[i]);
        cscReqd = VpsCore_VipCscReqd(pathObj, i);

        if (FVID2_DF_RAW_VBI == pathObj->dstColorSpace[i])
        {
            cscReqd = FALSE;
            scReqd  = FALSE;
        }

        tmp = VpsCore_Vip24BitOut(pathObj, i);
        if (scReqd && tmp)
        {
            retVal = BSP_EFAIL;
        }

        if ((scReqd == TRUE) && (cscReqd == TRUE) && (BSP_SOK == retVal))
        {
            /* If SC and CSC both are required, connect CSC to SC */
            if (scAvl)
            {
                if ((!cscScAdded) && (scAdded == TRUE))
                {
                    retVal = BSP_EFAIL;
                }
                if ((!cscScAdded) && (BSP_SOK == retVal))
                {
                    Vgraph_AddEdge(&list[idx], cscNode, scSrcNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], scSrcNode, scNode);
                    idx++;
                    cscScAdded = TRUE;
                    scAdded    = TRUE;
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
        }
        if ((scReqd == TRUE) && (cscReqd == FALSE) && (BSP_SOK == retVal))
        {
            /* If SC and CSC both are required, connect dataNode to SC */
            if (scAvl)
            {
                if ((!dataScAdded) && (scAdded == TRUE))
                {
                    retVal = BSP_EFAIL;
                }
                if ((!dataScAdded) && (BSP_SOK == retVal))
                {
                    Vgraph_AddEdge(&list[idx], dataNode, scSrcNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], scSrcNode, scNode);
                    idx++;
                    dataScAdded = TRUE;
                    scAdded     = TRUE;
                }
            }
            else
            {
                retVal = BSP_EFAIL;
            }
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Check if the path has a single stream only - in this case, give
         * preference to connect to the direct path to VIP LO ports */
        numActiveStreams = 0;
        for (i = 0; i < pathObj->numStreams; i++)
        {
            if (FVID2_DF_RAW_VBI != pathObj->dstColorSpace[i])
            {
                numActiveStreams++;
            }
        }
        allowDirect422Path = (Bool) (numActiveStreams == 1U);
    }

    if (TRUE == pathObj->multiCaptureValid)
    {
        UInt32 vpdmaPort, multiNode;
        if ((GRAPH_VIP_S0_PARSER_PORTB_08 == dataNode) ||
            (GRAPH_VIP_S1_PARSER_PORTB_08 == dataNode))
        {
            /* PORT B goes to PORT_B_CHROMA */
            vpdmaPort = uvLoNode;
            if (VPSHAL_VIP_S0 == slice)
            {
                multiNode = GRAPH_VIP_S0_PORTB_CHROMA;
            }
            else /* if(VPSHAL_VIP_S1 == slice) */
            {
                multiNode = GRAPH_VIP_S1_PORTB_CHROMA;
            }
        }
        else
        {
            /* PORT A goes to PORT_B_LUMA */
            vpdmaPort = yLoNode;
            if (VPSHAL_VIP_S0 == slice)
            {
                multiNode = GRAPH_VIP_S0_PORTB_LUMA;
            }
            else /* if(VPSHAL_VIP_S1 == slice) */
            {
                multiNode = GRAPH_VIP_S1_PORTB_LUMA;
            }
        }
        if (Vgraph_isNodeInputAvailable(nodeList, vpdmaPort))
        {
            Vgraph_AddEdge(&list[idx], dataNode, vpdmaPort);
            idx++;
            Vgraph_AddEdge(&list[idx], vpdmaPort, multiNode);
            idx++;
            streamsAdded++;
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }
    else
    {
        /* Allocation of UP/LO port nodes */
        i = 0;
        while ((i < pathObj->numStreams) && (BSP_SOK == retVal))
        {
            gotoNextIteration = FALSE;
            spActive          = VpsCore_VipSemiPlanarActive(pathObj, i);
            is24BitOut        = VpsCore_Vip24BitOut(pathObj, i);
            scReqd        = (Bool) (1U == pathObj->scActive[i]);
            cscReqd       = VpsCore_VipCscReqd(pathObj, i);
            chrdsReqd     = VpsCore_VipChrdsActive(pathObj, i);
            dataNode24Bit =
                (Bool) ((dataNode == GRAPH_VIP_S1_PARSER_PORTA_24) ||
                        (dataNode == GRAPH_VIP_S0_PARSER_PORTA_24));

            if (FVID2_DF_RAW_VBI == pathObj->dstColorSpace[i])
            {
                /* Do Nothing For this iteration */
                gotoNextIteration = TRUE;
            }

            /* Add the direct 422 path from parser to LO ports -
             * This connection is allowed only when -
             *   - Input is 8b/16b data
             *   - No SC or CSC required for the stream
             *   - Output is not semi-planar
             */
            if ((!gotoNextIteration) && (!dataNode24Bit) &&
                (allowDirect422Path == TRUE) && (!scReqd) && (!cscReqd) &&
                (!spActive))
            {
                UInt32 vpdmaPort, vpdmaChan;
                Bool   portAdded;
                if ((GRAPH_VIP_S0_PARSER_PORTB_08 == dataNode) ||
                    (GRAPH_VIP_S1_PARSER_PORTB_08 == dataNode))
                {
                    /* PORT B goes to PORT_B_CHROMA */
                    vpdmaPort = uvLoNode;
                    vpdmaChan = portBChroma;
                    portAdded = uvLoAdded;
                }
                else
                {
                    /* PORT A goes to PORT_B_LUMA */
                    vpdmaPort = yLoNode;
                    vpdmaChan = portBLuma;
                    portAdded = yLoAdded;
                }
                if (((Vgraph_isNodeInputAvailable(nodeList,
                                                  vpdmaPort)) == TRUE) &&
                     (!portAdded))
                {
                    Vgraph_AddEdge(&list[idx], dataNode, vpdmaPort);
                    idx++;
                    Vgraph_AddEdge(&list[idx], vpdmaPort, vpdmaChan);
                    idx++;
                    if (vpdmaPort == yLoNode)
                    {
                        yLoAdded = TRUE;
                    }
                    if (vpdmaPort == uvLoNode)
                    {
                        uvLoAdded = TRUE;
                    }
                    streamsAdded++;
                    allowDirect422Path = FALSE;
                    gotoNextIteration  = TRUE;
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }

            if (((Bool) (!gotoNextIteration)) && ((Bool) (BSP_SOK == retVal)) &&
                ((Bool) (is24BitOut == TRUE)) && ((Bool) (cscReqd == TRUE)))
            {
                /* If output is 24bit data and CSC is required for the stream,
                 * connect CSC node to VIP_UP or VIP_LO ports as per
                 * availability.
                 */
                if ((yLoAvl == TRUE) && (!yLoAdded) &&
                    (uvLoAvl == TRUE) && (!uvLoAdded))
                {
                    Vgraph_AddEdge(&list[idx], cscNode, yLoNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], cscNode, uvLoNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], yLoNode, portBRgb);
                    idx++;
                    Vgraph_AddEdge(&list[idx], uvLoNode, portBRgb);
                    idx++;
                    yLoAdded  = TRUE;
                    uvLoAdded = TRUE;
                    streamsAdded++;
                    gotoNextIteration = TRUE;
                }
                else if ((yUpAvl == TRUE) && (!yUpAdded) &&
                         (uvUpAvl == TRUE) && (!uvUpAdded))
                {
                    Vgraph_AddEdge(&list[idx], cscNode, rgbHiNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], rgbHiNode, yUpNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], rgbHiNode, uvUpNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], yUpNode, portARgb);
                    idx++;
                    Vgraph_AddEdge(&list[idx], uvUpNode, portARgb);
                    idx++;
                    rgbHiNodeAdded = TRUE;
                    yUpAdded       = TRUE;
                    uvUpAdded      = TRUE;
                    streamsAdded++;
                    gotoNextIteration = TRUE;
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }
            else if (((Bool) (!gotoNextIteration)) &&
                     ((Bool) (BSP_SOK == retVal)) &&
                     ((Bool) (is24BitOut == TRUE)) && ((Bool) (!cscReqd)))
            {
                if ((yLoAvl == TRUE) && (!yLoAdded) &&
                    (uvLoAvl == TRUE) && (!uvLoAdded))
                {
                    /* If output is 24bit data and CSC is NOT required for the
                     * stream, connect data node to VIP_LO ports directly if
                     * available */
                    Vgraph_AddEdge(&list[idx], dataNode, yLoNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], dataNode, uvLoNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], yLoNode, portBRgb);
                    idx++;
                    Vgraph_AddEdge(&list[idx], uvLoNode, portBRgb);
                    idx++;
                    yLoAdded  = TRUE;
                    uvLoAdded = TRUE;
                    streamsAdded++;
                    gotoNextIteration = TRUE;
                }
                else if ((cscAvl == TRUE) && (!cscAdded) && (!rgbHiNodeAdded) &&
                         (yUpAvl == TRUE) && (!yUpAdded) &&
                         (uvUpAvl == TRUE) && (!uvUpAdded))
                {
                    /* If output is 24bit data and CSC is NOT required and
                     * VIP_LO ports are not available,
                     * connect dataNode to CSC (if available) and send data to
                     * VIP_UP ports via RGB_HI node */
                    pathObj->forceCscBypass = 1;
                    Vgraph_AddEdge(&list[idx], dataNode, cscNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], cscNode, rgbHiNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], rgbHiNode, yUpNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], rgbHiNode, uvUpNode);
                    idx++;
                    Vgraph_AddEdge(&list[idx], yUpNode, portARgb);
                    idx++;
                    Vgraph_AddEdge(&list[idx], uvUpNode, portARgb);
                    idx++;
                    rgbHiNodeAdded = TRUE;
                    cscAdded       = TRUE;
                    yUpAdded       = TRUE;
                    uvUpAdded      = TRUE;
                    streamsAdded++;
                    gotoNextIteration = TRUE;
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }
            else
            {
                if (FALSE == gotoNextIteration)
                {
                    GT_0trace(VpsVipCoreTrace, GT_DEBUG,
                              "24 bit path not active\r\n");
                }
            }

            /* Allocation of paths via CHR_DS0 and CHR_DS1 - these can be added
             * only if
             *  - Output is not 24bit && (CSC/SC are in path or dataNode to
             *    CHR_DS connection is forced)
             */
            if (((Bool) (!gotoNextIteration)) &&
                ((Bool) (BSP_SOK == retVal)) &&
                ((Bool) (((scReqd == TRUE) || (cscReqd == TRUE) ||
                          (dataChrdsForced == TRUE)) && (!is24BitOut))))
            {
                if (cscReqd && scReqd)
                {
                    startNode = scNode;
                }
                else if (cscReqd)
                {
                    startNode = cscNode;
                }
                else if (scReqd)
                {
                    startNode = scNode;
                }
                else
                {
                    startNode = dataNode;
                }

                if (chrdsReqd)
                {
                    chrds0SrcNode = chrds0SrcOnNode;
                    chrds1SrcNode = chrds1SrcOnNode;
                }
                else
                {
                    chrds0SrcNode = chrds0SrcOffNode;
                    chrds1SrcNode = chrds1SrcOffNode;
                }

                /* Try allocating CHR_DS0 first */
                tmp = Vgraph_isNodeInputAvailable(nodeList, chrds0SrcNode);
                if ((chrds0Avl == TRUE) && (!chrds0Added) && (tmp == TRUE))
                {
                    /* Connect a node to CHR_DS only if it is not connected to
                     * something else already */
                    if (startNode == cscNode)
                    {
                        if (!cscChrds0Added)
                        {
                            cscChrds0Added = TRUE;
                        }
                    }
                    if (startNode == scNode)
                    {
                        if (!scChrds0Added)
                        {
                            scChrds0Added = TRUE;
                        }
                    }
                    if (startNode == dataNode)
                    {
                        if (!dataChrds0Added)
                        {
                            dataChrds0Added = TRUE;
                        }
                    }
                    /* Check availability of VIP_UP ports before adding
                     * CHR_DS0 */
                    chrds0Added = TRUE;
                    tmp         = Vgraph_isNodeInputAvailable(
                        nodeList,
                        chrds1SrcOffNode);
                    if ((!yUpAvl) || (yUpAdded == TRUE) || (rgbHiNodeAdded == TRUE))
                    {
                        chrds0Added = FALSE;
                    }
                    else if ((spActive == TRUE) &&
                             ((!uvUpAvl) || (uvUpAdded == TRUE)))
                    {
                        chrds0Added = FALSE;
                    }
                    else if ((spActive == TRUE) &&
                             ((chrds1Bypass == TRUE) || (!tmp)))
                    {
                        /* An existing path via CHR_DS1 might use UV_UP port
                         * For semi-planar streams, then CHR_DS0 is unusable
                         */
                        chrds0Added = FALSE;
                    }
                    else if (VpsCore_Vip422SPActive(pathObj, i))
                    {
                        /* 422SP is not supported on UP_PORTS */
                        chrds0Added = FALSE;
                    }
                    else
                    {
                        Vgraph_AddEdge(&list[idx], startNode, chrds0SrcNode);
                        idx++;
                        Vgraph_AddEdge(&list[idx], chrds0SrcNode,
                                       chrds0Node);
                        idx++;

                        Vgraph_AddEdge(&list[idx], chrds0Node, yUpNode);
                        idx++;
                        Vgraph_AddEdge(&list[idx], yUpNode, portALuma);
                        idx++;
                        yUpAdded = TRUE;
                        if (spActive)
                        {
                            Vgraph_AddEdge(&list[idx], chrds0Node, uvUpNode);
                            idx++;
                            Vgraph_AddEdge(&list[idx], uvUpNode,
                                           portAChroma);
                            idx++;
                            uvUpAdded      = TRUE;
                            chrds1OnNeeded = TRUE;
                        }
                        streamsAdded++;
                        gotoNextIteration = TRUE;
                    }
                    if ((FALSE == gotoNextIteration) && (!chrds0Added))
                    {
                        if (startNode == cscNode)
                        {
                            cscChrds0Added = FALSE;
                        }
                        if (startNode == scNode)
                        {
                            scChrds0Added = FALSE;
                        }
                        if (startNode == dataNode)
                        {
                            dataChrds0Added = FALSE;
                        }
                    }
                }

                if (FALSE == gotoNextIteration)
                {
                    /* Try allocating CHR_DS1 */
                    tmp = Vgraph_isNodeInputAvailable(nodeList, chrds1SrcNode);
                }

                if ((!gotoNextIteration) && (chrds1Avl == TRUE) && (tmp == TRUE))
                {
                    /* Connect a node to CHR_DS only if it is not connected to
                     * something else already */
                    Bool skipChrds1 = TRUE;
                    if (startNode == cscNode)
                    {
                        if ((!scChrds1Added) &&
                            (!dataChrds1Added))
                        {
                            cscChrds1Added = TRUE;
                            skipChrds1     = FALSE;
                        }
                    }
                    else if (startNode == scNode)
                    {
                        if ((!cscChrds1Added) &&
                            (!dataChrds1Added))
                        {
                            scChrds1Added = TRUE;
                            skipChrds1    = FALSE;
                        }
                    }
                    else if (startNode == dataNode)
                    {
                        if ((!cscChrds1Added) &&
                            (!scChrds1Added))
                        {
                            dataChrds1Added = TRUE;
                            skipChrds1      = FALSE;
                        }
                    }
                    else
                    {
                        skipChrds1 = TRUE;
                    }
                    if ((!skipChrds1) &&
                        ((!chrds1outLoAdded) || (!uvUpAdded)) &&
                        ((!yLoAdded) &&
                         (!(spActive && uvLoAdded))))
                    {
                        /* CHR_DS1 can give outputs to both VIP_LO and VIP_UP
                         * ports check if either is available before
                         * continuing.
                         */
                        Bool chrds1outUpUsable, chrds1SrcOffAvl;
                        chrds1SrcOffAvl = Vgraph_isNodeInputAvailable(
                            nodeList,
                            chrds1SrcOffNode);
                        chrds1outUpUsable =
                            ((Bool) (!uvUpAdded)) &&
                            ((Bool) (uvUpAvl == TRUE)) &&
                            ((Bool) (chrds1SrcOffAvl == TRUE)) &&
                            ((Bool) (chrds1SrcNode == chrds1SrcOffNode)) &&
                            ((Bool) !rgbHiNodeAdded);
                        /* Connect a node to CHR_DS only if it is not connected
                         * to something else already */
                        chrds1Added = TRUE;
                        if (chrds1OffNeeded &&
                            ((Bool) (chrds1SrcNode == chrds1SrcOnNode)))
                        {
                            chrds1Added = FALSE;
                        }
                        else if (chrds1OnNeeded &&
                                 ((Bool) (chrds1SrcNode == chrds1SrcOffNode)))
                        {
                            chrds1Added = FALSE;
                        }
                        else if ((!chrds1outUpUsable) &&
                                 (chrds1outLoAdded == TRUE))
                        {
                            chrds1Added = FALSE;
                        }
                        else if ((!chrds1outUpUsable) &&
                                 ((!yLoAvl) || (yLoAdded == TRUE)))
                        {
                            chrds1Added = FALSE;
                        }
                        else if ((!chrds1outUpUsable) &&
                                 (spActive == TRUE) &&
                                 ((!uvLoAvl) ||
                                  (uvLoAdded == TRUE))
                                 )
                        {
                            chrds1Added = FALSE;
                        }
                        else
                        {
                            /* Connect the source node of CHR_DS1 only once */
                            if ((!chrds1outLoAdded) && (!chrds1outUpAdded))
                            {
                                Vgraph_AddEdge(&list[idx], startNode,
                                               chrds1SrcNode);
                                idx++;
                                Vgraph_AddEdge(&list[idx], chrds1SrcNode,
                                               chrds1Node);
                                idx++;
                            }

                            if ((chrds1outUpUsable == TRUE) &&
                                (!spActive))
                            {
                                /* CHR_DS1 to VIP_UP_UV connection */
                                Vgraph_AddEdge(&list[idx], chrds1Node, uvUpNode);
                                idx++;
                                Vgraph_AddEdge(&list[idx], uvUpNode,
                                               portAChroma);
                                idx++;
                                chrds1Bypass     = TRUE;
                                chrds1OffNeeded  = TRUE;
                                uvUpAdded        = TRUE;
                                chrds1outUpAdded = TRUE;
                            }
                            else
                            {
                                /* CHR_DS1 to VIP_LO connection */
                                Vgraph_AddEdge(&list[idx], chrds1Node, yLoNode);
                                idx++;
                                Vgraph_AddEdge(&list[idx], yLoNode, portBLuma);
                                idx++;
                                yLoAdded = TRUE;
                                if (spActive)
                                {
                                    Vgraph_AddEdge(&list[idx], chrds1Node,
                                                   uvLoNode);
                                    idx++;
                                    Vgraph_AddEdge(&list[idx], uvLoNode,
                                                   portBChroma);
                                    idx++;
                                    uvLoAdded = TRUE;

                                    /* Incase of YUV422SP, block UP port as well
                                    **/
                                    if (VpsCore_Vip422SPActive(pathObj, i))
                                    {
                                        uvUpAdded = TRUE;
                                    }
                                }
                                else
                                {
                                    chrds1Bypass = TRUE;
                                }
                                chrds1outLoAdded = TRUE;
                                chrds1OnNeeded   = TRUE;
                            }
                            streamsAdded++;
                            gotoNextIteration = TRUE;
                        }
                        if ((FALSE == gotoNextIteration) && (!chrds1Added))
                        {
                            if (startNode == cscNode)
                            {
                                cscChrds1Added = FALSE;
                            }
                            if (startNode == scNode)
                            {
                                scChrds1Added = FALSE;
                            }
                            if (startNode == dataNode)
                            {
                                dataChrds1Added = FALSE;
                            }
                            chrds1Added = (chrds1outUpAdded || chrds1outLoAdded);
                        }
                    }
                }
            }

            if ((FALSE == gotoNextIteration) && (BSP_SOK == retVal) &&
                ((!dataNode24Bit) && (!scReqd) && (!cscReqd) && (!spActive)))
            {
                Bool portAdded;

                if ((GRAPH_VIP_S0_PARSER_PORTB_08 == dataNode) ||
                    (GRAPH_VIP_S1_PARSER_PORTB_08 == dataNode))
                {
                    /* PORT B goes to PORT_B_CHROMA */
                    portAdded = uvLoAdded;
                }
                else
                {
                    /* PORT A goes to PORT_B_LUMA */
                    portAdded = yLoAdded;
                }

                /* If we are not able to allocate path for this stream yet, try
                 * direct path to VIP_LO ports */
                allowDirect422Path = TRUE;
                if (TRUE == portAdded)
                {
                    allowDirect422Path = FALSE;
                    dataChrdsForced    = TRUE;
                }
                i--;
                gotoNextIteration = TRUE;
            }
            else if ((FALSE == gotoNextIteration) && (BSP_SOK == retVal) &&
                     ((!dataNode24Bit) && (!dataChrdsForced)))
            {
                /* If we are not able to allocate path for this stream yet, try
                 * dataNode to CHR_DS connection */
                dataChrdsForced = TRUE;
                i--;
                gotoNextIteration = TRUE;
            }
            else
            {
                if (FALSE == gotoNextIteration)
                {
                    /* Unable to allocate path for this stream, return error */
                    retVal = BSP_EFAIL;
                }
            }

            if (FALSE == gotoNextIteration)
            {
                if (BSP_SOK != retVal)
                {
                    break;
                }
            }
            i++;
        }
    }

    GT_1trace(VpsVipCoreTrace, GT_DEBUG, "streamsAdded: %d\r\n", streamsAdded);
    if (BSP_SOK == retVal)
    {
        if (streamsAdded != pathObj->numStreams)
        {
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        edgeInfoList->numEdges = idx;
        edgeInfoList->list     = list;
    }
    return retVal;
}

UInt32 VpsCore_vipGetPort(VpsCore_VipVpdmaDT        outCs,
                          const VpsCore_VipVpdmaDT *portDataType,
                          const VpsHal_VpdmaChanDT *vpdmaDataType,
                          UInt32                    scActive,
                          UInt32                    dstColorSpace)
{
    UInt32 j, retVal = PORT_MAX;
    for (j = 0; j < PORT_MAX; j++)
    {
        if ((VPSHAL_VPDMA_CHANDT_INVALID == vpdmaDataType[j]) &&
            (outCs == portDataType[j]))
        {
            Int32 dataFmtYuv422Sp, dataFmtYuv420Sp;
            retVal = j;
            /* When allocating port in case of scalar with non-422SP format or
             *  just 420SP, we start allocating from UP and then to Lo port.
             * Hence the moment the ports match the data type, break the
             * loop so that the right ports are used for the right stream.
             * For other cases, we try to allocate LO ports first and hence
             * continue the loop so that LO port gets allocated to the first
             * stream */
            dataFmtYuv422Sp = Fvid2_isDataFmtYuv422Sp(dstColorSpace);
            dataFmtYuv420Sp = Fvid2_isDataFmtYuv420Sp(dstColorSpace);
            if (((TRUE == scActive) &&
                 ((Int32) TRUE != dataFmtYuv422Sp)) ||
                ((Int32) TRUE == dataFmtYuv420Sp))
            {
                break;
            }
        }
    }
    return (retVal);
}

VpsHal_VpdmaChannel VpsCore_vipGetChan(const VpsCore_VipPathObj *pathObj,
                                       UInt32                    port,
                                       UInt32                    chId)
{
    UInt32 i;
    Vgraph_nodeInfoList *vipNodeList = &(pathObj->parent->vipNodeList);
    Vgraph_nodeInfo     *curNode;
    UInt32 chan    = GRAPH_VIP_NUM_NODES;
    UInt32 sliceId = pathObj->sliceId;
    VpsHal_VpdmaChannel retVal = VPSHAL_VPDMA_CHANNEL_INVALID;

    if (VPSHAL_VIP_S0 == sliceId)
    {
        curNode = Vgraph_getNodeInfo(vipNodeList, GRAPH_VIP_S0_Y_UP + port);
    }
    else
    {
        curNode = Vgraph_getNodeInfo(vipNodeList, GRAPH_VIP_S1_Y_UP + port);
    }

    if (NULL != curNode)
    {
        for (i = 0U; i < GRAPH_MAX_NUM_PATHS; i++)
        {
            if (0U != curNode->output.isEnabled[i])
            {
                chan = curNode->output.node[i]->nodeNum;
            }
        }

        switch (chan)
        {
            /* Slice 0 */
            case GRAPH_VIP_S0_PORTA_RGB:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTA_RGB;
                break;
            case GRAPH_VIP_S0_PORTB_RGB:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB;
                break;
            case GRAPH_VIP_S0_PORTA_LUMA:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTA_LUMA;
                break;
            case GRAPH_VIP_S0_PORTB_LUMA:
                if (TRUE == pathObj->multiCaptureValid)
                {
                    retVal = (VpsHal_VpdmaChannel)
                             (VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0 + chId);
                    if (VPS_VIP_SYNC_TYPE_EMB_LINE_YUV ==
                        pathObj->portCfg.syncType)
                    {
                        /* For line muxed channel increments by two */
                        retVal = (VpsHal_VpdmaChannel)
                                 (VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0 +
                                  (2U * chId));
                    }
                    retVal =
                        (VpsHal_VpdmaChannel) (retVal +
                                               pathObj->muxModeStartChId);
                }
                else
                {
                    retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTB_LUMA;
                }
                break;
            case GRAPH_VIP_S0_PORTA_CHROMA:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTA_CHROMA;
                break;
            case GRAPH_VIP_S0_PORTB_CHROMA:
                if (TRUE == pathObj->multiCaptureValid)
                {
                    retVal = (VpsHal_VpdmaChannel)
                             (VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0 + chId);
                    if (VPS_VIP_SYNC_TYPE_EMB_LINE_YUV ==
                        pathObj->portCfg.syncType)
                    {
                        /* For line muxed channel increments by two */
                        retVal = (VpsHal_VpdmaChannel)
                                 (VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0 +
                                  (2U * chId));
                    }
                    retVal =
                        (VpsHal_VpdmaChannel) (retVal +
                                               pathObj->muxModeStartChId);
                }
                else
                {
                    retVal = VPSHAL_VPDMA_CHANNEL_S0_PORTB_CHROMA;
                }
                break;
            case GRAPH_VIP_S0_MULT_ANCA_SRC0:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC0;
                break;
            case GRAPH_VIP_S0_MULT_ANCB_SRC0:
                retVal = VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC0;
                break;
            /* Slice 1 */
            case GRAPH_VIP_S1_PORTA_RGB:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTA_RGB;
                break;
            case GRAPH_VIP_S1_PORTB_RGB:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTB_RGB;
                break;
            case GRAPH_VIP_S1_PORTA_LUMA:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTA_LUMA;
                break;
            case GRAPH_VIP_S1_PORTB_LUMA:
                if (TRUE == pathObj->multiCaptureValid)
                {
                    retVal = (VpsHal_VpdmaChannel)
                             (VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0 + chId);
                    if (VPS_VIP_SYNC_TYPE_EMB_LINE_YUV ==
                        pathObj->portCfg.syncType)
                    {
                        /* For line muxed channel increments by two */
                        retVal = (VpsHal_VpdmaChannel)
                                 (VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0 +
                                  (2U * chId));
                    }
                    retVal =
                        (VpsHal_VpdmaChannel) (retVal +
                                               pathObj->muxModeStartChId);
                }
                else
                {
                    retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTB_LUMA;
                }
                break;
            case GRAPH_VIP_S1_PORTA_CHROMA:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTA_CHROMA;
                break;
            case GRAPH_VIP_S1_PORTB_CHROMA:
                if (TRUE == pathObj->multiCaptureValid)
                {
                    retVal = (VpsHal_VpdmaChannel)
                             (VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0 + chId);
                    if (VPS_VIP_SYNC_TYPE_EMB_LINE_YUV ==
                        pathObj->portCfg.syncType)
                    {
                        /* For line muxed channel increments by two */
                        retVal = (VpsHal_VpdmaChannel)
                                 (VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0 +
                                  (2U * chId));
                    }
                    retVal =
                        (VpsHal_VpdmaChannel) (retVal +
                                               pathObj->muxModeStartChId);
                }
                else
                {
                    retVal = VPSHAL_VPDMA_CHANNEL_S1_PORTB_CHROMA;
                }
                break;
            case GRAPH_VIP_S1_MULT_ANCA_SRC0:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC0;
                break;
            case GRAPH_VIP_S1_MULT_ANCB_SRC0:
                retVal = VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC0;
                break;
            default:
                retVal = VPSHAL_VPDMA_CHANNEL_INVALID;
                break;
        }
    }

    return (retVal);
}

Int32 VpsCore_VipSetMux(const VpsCore_VipPathObj *pathObj,
                        const Vgraph_nodeInfo    *curNode,
                        VpsHal_VipTopMux          muxName,
                        UInt32                    reset)
{
    VpsCore_VipObj *vipObj = (VpsCore_VipObj *) pathObj->parent;
    Int32           muxVal = 0;
    Int32           retVal = BSP_SOK;

    if (reset != TRUE)
    {
        muxVal = Vgraph_getEnabledIndex(curNode->input.isEnabled,
                                        curNode->input.numNodes);
    }

    if (BSP_EFAIL == muxVal)
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vipTopSetMux(vipObj->vipTopHandle,
                                     pathObj->sliceId,
                                     muxName,
                                     (UInt32) muxVal,
                                     NULL);
    }

    return (retVal);
}

Int32 VpsCore_VipCfgMux(const VpsCore_VipPathObj *pathObj,
                        const Vgraph_nodeInfo    *curNode,
                        UInt32                    reset)
{
    Int32 retVal = BSP_SOK;

    switch (curNode->nodeNum)
    {
        case GRAPH_VIP_S0_CSC_SRC:
        case GRAPH_VIP_S1_CSC_SRC:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_CSC_SRC, reset);
            break;
        case GRAPH_VIP_S0_SC_SRC:
        case GRAPH_VIP_S1_SC_SRC:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_SC_SRC, reset);
            break;
        case GRAPH_VIP_S0_CHRDS0_ON:
        case GRAPH_VIP_S0_CHRDS0_OFF:
        case GRAPH_VIP_S1_CHRDS0_ON:
        case GRAPH_VIP_S1_CHRDS0_OFF:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_CHRDS0_SRC,
                              reset);
            break;
        case GRAPH_VIP_S0_CHRDS1_ON:
        case GRAPH_VIP_S0_CHRDS1_OFF:
        case GRAPH_VIP_S1_CHRDS1_ON:
        case GRAPH_VIP_S1_CHRDS1_OFF:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_CHRDS1_SRC,
                              reset);
            break;
        case GRAPH_VIP_S0_CHRDS0:
        case GRAPH_VIP_S1_CHRDS0:
            VpsCore_VipSetMux(pathObj, curNode,
                              VPSHAL_VIP_TOP_CHRDS0_BYPASS, reset);
            break;
        case GRAPH_VIP_S0_CHRDS1:
        case GRAPH_VIP_S1_CHRDS1:
            VpsCore_VipSetMux(pathObj, curNode,
                              VPSHAL_VIP_TOP_CHRDS1_BYPASS, reset);
            break;
        case GRAPH_VIP_S0_RGB_HI:
        case GRAPH_VIP_S1_RGB_HI:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_RGB_OUT, reset);
            break;
        case GRAPH_VIP_S0_Y_UP:
        case GRAPH_VIP_S1_Y_UP:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_RGB_OUT_HI,
                              reset);
            break;
        case GRAPH_VIP_S0_UV_UP:
        case GRAPH_VIP_S1_UV_UP:
            /* TODO: Check this may fail due to identical inputs */
            /* VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_UV_UP); */
            break;
        case GRAPH_VIP_S0_Y_LO:
        case GRAPH_VIP_S0_UV_LO:
        case GRAPH_VIP_S1_Y_LO:
        case GRAPH_VIP_S1_UV_LO:
            VpsCore_VipSetMux(pathObj, curNode, VPSHAL_VIP_TOP_UV_LO, reset);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }
    return (retVal);
}

Int32 VpsCore_VipCfgSc(VpsCore_VipPathObj *pathObj, Vgraph_nodeInfo *curNode)
{
    UInt32 descOffset;
    UInt32 strm, foundStrm = VPSCORE_VIP_STREAM_ID_MAX;
    VpsHal_ScFactorConfig scFactorConfig;
    UInt32 scVpdmaDest, hCoeffSize, vCoeffSize, biLinCoeffSize;
    Ptr    horzCoeffMemPtr         = NULL;
    Ptr    vertCoeffMemPtr         = NULL;
    Ptr    vertBilinearCoeffMemPtr = NULL;
    Vps_ScConfig    *scCfg;
    Vps_ScAdvConfig *scAdvCfg;
    UInt8           *scCoeffDestAddr;

    scCfg    = &pathObj->scCfg;
    scAdvCfg = &pathObj->scAdvCfg;
    if (NULL == scCfg->advCfg)
    {
        scCfg->advCfg = scAdvCfg;

        /* Find the stream in which SC is active */
        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            if (pathObj->scActive[strm] == TRUE)
            {
                foundStrm = strm;
                break;
            }
        }
        GT_assert(VpsVipCoreTrace, foundStrm != VPSCORE_VIP_STREAM_ID_MAX);

        scAdvCfg->tarWidth      = pathObj->tarWidth[foundStrm];
        scAdvCfg->tarHeight     = pathObj->tarHeight[foundStrm];
        scAdvCfg->srcWidth      = pathObj->srcWidth;
        scAdvCfg->srcHeight     = pathObj->srcHeight;
        scAdvCfg->inFrameMode   = FVID2_SF_PROGRESSIVE;
        scAdvCfg->outFrameMode  = FVID2_SF_PROGRESSIVE;
        scAdvCfg->cropStartX    = pathObj->inCropCfg.cropStartX;
        scAdvCfg->cropStartY    = pathObj->inCropCfg.cropStartY;
        scAdvCfg->cropWidth     = pathObj->inCropCfg.cropWidth;
        scAdvCfg->cropHeight    = pathObj->inCropCfg.cropHeight;
        scAdvCfg->fidPol        = FVID2_FIDPOL_NORMAL;
        scAdvCfg->selfGenFid    = VPS_SC_SELF_GEN_FID_DISABLE;
        scAdvCfg->biLinIntpType = VPS_SC_BINTP_MODIFIED;
        scAdvCfg->hPolyBypass   = (UInt32) FALSE;
        scAdvCfg->defConfFactor = 0U;
        scAdvCfg->edgeDetectCfg = NULL;
        scAdvCfg->peakingCfg    = NULL;
        scAdvCfg->phInfoMode    = VPS_SC_SET_PHASE_INFO_DEFAULT;
        scAdvCfg->hsDcmType     = VPS_SC_HST_DCM_AUTO;
        scAdvCfg->vsType        = VPS_SC_VST_AUTO;
    }

    /* Update hsType and vsType and get scaling sets */
    VpsHal_scGetScFactorConfig(pathObj->scHandle,
                               &pathObj->scCfg,
                               &scFactorConfig);
    scAdvCfg->hsDcmType   = scFactorConfig.hsDcmType;
    scAdvCfg->hPolyBypass = scFactorConfig.hPolyBypass;
    scAdvCfg->vsType      = scFactorConfig.vsType;

    /* Set all registers */
    VpsHal_scSetConfig(pathObj->scHandle, &pathObj->scCfg, 0);

    /* SC coeffs configuration */
    scVpdmaDest = VpsHal_scGetVpdmaConfigDest(pathObj->scHandle);

    VpsHal_scGetCoeffOvlySize(pathObj->scHandle,
                              &hCoeffSize,
                              &vCoeffSize,
                              &biLinCoeffSize);

    VpsHal_scGetCoeffOvlyMemPtr(pathObj->scHandle,
                                &scFactorConfig,
                                &horzCoeffMemPtr,
                                &vertCoeffMemPtr,
                                &vertBilinearCoeffMemPtr);

    /* Creating 2 coeff descriptors - one for horizontal and one for
     * vertical scaling coeffs */
    descOffset      = 0;
    scCoeffDestAddr = NULL;

    VpsHal_vpdmaCreateConfigDesc(
        &pathObj->cfgDescMem[descOffset],            /* memPtr      */
        (VpsHal_VpdmaConfigDest) scVpdmaDest,        /* dest        */
        VPSHAL_VPDMA_CPT_BLOCK_SET,                  /* classVal    */
        VPSHAL_VPDMA_CCT_INDIRECT,                   /* direct      */
        hCoeffSize,                                  /* payloadSize */
        horzCoeffMemPtr,                             /* payloadAddr */
        scCoeffDestAddr,                             /* destAddr    */
        (UInt16) hCoeffSize);                        /* dataSize    */
    descOffset += VPSHAL_VPDMA_CONFIG_DESC_SIZE;

    scCoeffDestAddr += hCoeffSize;
    VpsHal_vpdmaCreateConfigDesc(
        &pathObj->cfgDescMem[descOffset],            /* memPtr      */
        (VpsHal_VpdmaConfigDest) scVpdmaDest,        /* dest        */
        VPSHAL_VPDMA_CPT_BLOCK_SET,                  /* classVal    */
        VPSHAL_VPDMA_CCT_INDIRECT,                   /* direct      */
        vCoeffSize,                                  /* payloadSize */
        vertCoeffMemPtr,                             /* payloadAddr */
        scCoeffDestAddr,                             /* destAddr    */
        (UInt16) vCoeffSize);                        /* dataSize    */
    descOffset += VPSHAL_VPDMA_CONFIG_DESC_SIZE;

    VpsHal_vpdmaPostList(pathObj->vpdmaHandle,       /* handle      */
                         (UInt8) pathObj->listId[0U],/* listNum     */
                         VPSHAL_VPDMA_LT_NORMAL,     /* listType    */
                         &pathObj->cfgDescMem[0],    /* memPtr      */
                         descOffset,                 /* listSize    */
                         0);                         /* enableCheck */

    /* TODO: Fix 3000 */
    VpsHal_vpdmaListWaitComplete(pathObj->vpdmaHandle,
                                 (UInt8) pathObj->listId[0U],
                                 (UInt32) 3000U);

    return BSP_SOK;
}

Int32 VpsCore_vipPathResAlloc(VpsCore_VipPathObj      *pathObj,
                              const VpsCore_VipParams *pathCfg)
{
    UInt32              i, chId;
    Vgraph_edgeInfoList tmpEdgeInfoList;
    Vgraph_edgeInfo     tmpVgraphEdgeInfo[VPSCORE_VIP_AUTO_EDGELIST_MAX_SIZE];
    Bool autoMode = FALSE;
    VpsCore_VipObj     *pVipInstObj = (VpsCore_VipObj *) (pathObj->parent);
    Vgraph_Info        *vipGraph    = (Vgraph_Info *) (pVipInstObj->graph);
    Int32 retVal = BSP_SOK;

    if (1 == pathObj->setConfigDone)
    {
        VpsCore_vipPathResFree(pathObj);
        pathObj->setConfigDone = 0;
    }

    /* if no edges - create edge List */
    if (0 == pathCfg->edgeInfoList.numEdges)
    {
        autoMode = TRUE;
        /* TODO: Decide size */
        tmpEdgeInfoList.list = tmpVgraphEdgeInfo;
        retVal = VpsCore_VipCreateEdgeList(pathObj,
                                           vipGraph->nodeList,
                                           &tmpEdgeInfoList);
    }
    else
    {
        tmpEdgeInfoList.numEdges = pathCfg->edgeInfoList.numEdges;
        tmpEdgeInfoList.list     = pathCfg->edgeInfoList.list;
    }

    if (BSP_SOK == retVal)
    {
        /* Try to allocate nodes in the complete VIP graph */
        if (BSP_SOK == Vgraph_allocNodes(vipGraph->nodeList,
                                         &tmpEdgeInfoList,
                                         VGRAPH_NODE_CHECK))
        {
            Vgraph_allocNodes(vipGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_ENABLE);

            pathObj->nodeList.list = pathObj->nodeObj;
            pathObj->edgeList.list = pathObj->edgeObj;
            Vgraph_getPath(vipGraph->nodeList,
                           &tmpEdgeInfoList,
                           &pathObj->nodeList,
                           &pathObj->edgeList,
                           sizeof (pathObj->nodeObj) / sizeof (Vgraph_nodeInfo),
                           sizeof (pathObj->edgeObj) / sizeof (Vgraph_edgeInfo));

            pathObj->descMemSize   = VPSCORE_VIP_DATA_DESC_SIZE;
            pathObj->wrDescMemSize = VPSCORE_VIP_MISC_DESC_SIZE;

            GT_assert(VpsVipCoreTrace,
                (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
            for (chId = 0; chId < pathObj->numChannels; chId++)
            {
                pathObj->descMem[chId] = (UInt8 *) BspUtils_alloc(
                    &gVcoreVipDataDescMemPoolPrm,
                    pathObj->descMemSize,
                    VpsVipCoreTrace);
                for (i = 0; i < VIP_SW_Q_LEN; i++)
                {
                    pathObj->wrDescMem[chId][i] =
                        (UInt8 *) BspUtils_alloc(
                            &gVcoreVipMiscDescMemPoolPrm,
                            pathObj->wrDescMemSize,
                            VpsVipCoreTrace);
                }
            }

            pathObj->cfgDescMemSize = VPSCORE_VIP_MISC_DESC_SIZE;
            pathObj->cfgDescMem     = (UInt8 *) BspUtils_alloc(
                &gVcoreVipMiscDescMemPoolPrm,
                pathObj->cfgDescMemSize,
                VpsVipCoreTrace);

            /*
             * Allocate memory for Control Descriptor.
             * Currently only Change Client Interrupt control descriptor
             */
            pathObj->ctrlDescMemSize = VPSCORE_VIP_MISC_DESC_SIZE;
            pathObj->ctrlDescMem     = (UInt8 *) BspUtils_alloc(
                &gVcoreVipMiscDescMemPoolPrm,
                pathObj->ctrlDescMemSize,
                VpsVipCoreTrace);

            switch (pathObj->nodeList.list[0].nodeNum)
            {
                case GRAPH_VIP_S0_PARSER_PORTA:
                    pathObj->vipPortHandle = pVipInstObj->s0PortAHandle;
                    pathObj->sliceId       = VPSHAL_VIP_S0;
                    pathObj->portId        = VPSHAL_VIP_PORT_A;
                    pathObj->scHandle      = pVipInstObj->sc0Handle;
                    pathObj->cscHandle     = pVipInstObj->csc0Handle;
                    break;
                case GRAPH_VIP_S0_PARSER_PORTB:
                    pathObj->vipPortHandle = pVipInstObj->s0PortBHandle;
                    pathObj->sliceId       = VPSHAL_VIP_S0;
                    pathObj->portId        = VPSHAL_VIP_PORT_B;
                    pathObj->scHandle      = pVipInstObj->sc0Handle;
                    pathObj->cscHandle     = pVipInstObj->csc0Handle;
                    break;
                case GRAPH_VIP_S1_PARSER_PORTA:
                    pathObj->vipPortHandle = pVipInstObj->s1PortAHandle;
                    pathObj->sliceId       = VPSHAL_VIP_S1;
                    pathObj->portId        = VPSHAL_VIP_PORT_A;
                    pathObj->scHandle      = pVipInstObj->sc1Handle;
                    pathObj->cscHandle     = pVipInstObj->csc1Handle;
                    break;
                case GRAPH_VIP_S1_PARSER_PORTB:
                    pathObj->vipPortHandle = pVipInstObj->s1PortBHandle;
                    pathObj->sliceId       = VPSHAL_VIP_S1;
                    pathObj->portId        = VPSHAL_VIP_PORT_B;
                    pathObj->scHandle      = pVipInstObj->sc1Handle;
                    pathObj->cscHandle     = pVipInstObj->csc1Handle;
                    break;
                default:
                    retVal = BSP_EFAIL; /* TODO: Do something more....free etc
                                        **/
                    break;
            }

            if (BSP_SOK == retVal)
            {
                pathObj->vpdmaHandle  = pVipInstObj->vpdmaHandle;
                pathObj->vipTopHandle = pVipInstObj->vipTopHandle;

                pathObj->isStopped       = 1;
                pVipInstObj->numHandles += 1;
            }
            else
            {
                VpsCore_vipPathResFree(pathObj);
                pathObj->setConfigDone = 0;
            }
        }
        else
        {
            Vgraph_allocNodes(vipGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_DISABLE);
            retVal = BSP_EFAIL;
        }
    }

    if ((TRUE == autoMode) && (NULL != tmpEdgeInfoList.list))
    {
        tmpEdgeInfoList.list = NULL;
    }

    return retVal;
}

void VpsCore_vipPathResFree(VpsCore_VipPathObj *pathObj)
{
    UInt32          i, chId;
    VpsCore_VipObj *pVipInstObj = (VpsCore_VipObj *) (pathObj->parent);
    Vgraph_Info    *vipGraph    = (Vgraph_Info *) (pVipInstObj->graph);

    Vgraph_allocNodes(vipGraph->nodeList,
                      &(pathObj->edgeList),
                      VGRAPH_NODE_DISABLE);
    Vgraph_freePath(&pathObj->nodeList, &pathObj->edgeList);

    GT_assert(VpsVipCoreTrace,
        (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        if (NULL != pathObj->descMem[chId])
        {
            BspUtils_free(&gVcoreVipDataDescMemPoolPrm,
                          (void *) pathObj->descMem[chId],
                          VpsVipCoreTrace);
            pathObj->descMem[chId] = NULL;
        }
        for (i = 0; i < VIP_SW_Q_LEN; i++)
        {
            if (NULL != pathObj->wrDescMem[chId][i])
            {
                BspUtils_free(&gVcoreVipMiscDescMemPoolPrm,
                              (void *) pathObj->wrDescMem[chId][i],
                              VpsVipCoreTrace);
                pathObj->wrDescMem[chId][i] = NULL;
            }
        }
    }

    if (NULL != pathObj->cfgDescMem)
    {
        BspUtils_free(&gVcoreVipMiscDescMemPoolPrm, (void *) pathObj->cfgDescMem,
                      VpsVipCoreTrace);
        pathObj->cfgDescMem = NULL;
    }

    if (NULL != pathObj->ctrlDescMem)
    {
        BspUtils_free(&gVcoreVipMiscDescMemPoolPrm, (void *) pathObj->ctrlDescMem,
                      VpsVipCoreTrace);
        pathObj->ctrlDescMem = NULL;
    }
}

/* NodeList traversal - config all nodes */
void VpsCore_vipPathSetControlVars(VpsCore_VipPathObj *pathObj)
{
    Vgraph_nodeInfo *curNode;
    UInt32           i = 0;
    while (i < pathObj->nodeList.numNodes)
    {
        curNode = &pathObj->nodeList.list[i];
        if (curNode->nodeType == VGRAPH_NODETYPE_CSC)
        {
            /* TODO: Check usage - cscActive should not get used in pathCreation
            **/
            if ((VPS_CSC_MODE_AUTO == pathObj->cscCfg.mode) &&
                (0 == pathObj->cscBypass))
            {
                pathObj->cscActive = 1;
                GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CSC Active\r\n");
            }
            else if (0 == pathObj->cscCfg.bypass)
            {
                pathObj->cscActive = 1;
                GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CSC Active\r\n");
            }
            else
            {
                GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CSC Inactive\r\n");
            }
        }
        if ((curNode->nodeNum == GRAPH_VIP_S0_CHRDS0_OFF) ||
            (curNode->nodeNum == GRAPH_VIP_S1_CHRDS0_OFF))
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CHRDS0 bypass\r\n");
            pathObj->chrDs0Bypass = 1;
        }
        if ((curNode->nodeNum == GRAPH_VIP_S0_CHRDS1_OFF) ||
            (curNode->nodeNum == GRAPH_VIP_S1_CHRDS1_OFF))
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CHRDS1 bypass\r\n");
            pathObj->chrDs1Bypass = 1;
        }
        i++;
    }
}

/* NodeList traversal - config all nodes */
void VpsCore_vipPathResetMuxes(const VpsCore_VipPathObj *pathObj)
{
    Vgraph_nodeInfo *curNode;
    UInt32           i = 0;
    while (i < pathObj->nodeList.numNodes)
    {
        curNode = &pathObj->nodeList.list[i];
        if (curNode->nodeType == VGRAPH_NODETYPE_VIPMUX)
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "VipMux\r\n");
            VpsCore_VipCfgMux(pathObj, curNode, (UInt32) TRUE);
        }
        i++;
    }
}

void VpsCore_vipPathConfigureNodes(VpsCore_VipPathObj *pathObj)
{
    Vgraph_nodeInfo *curNode;
    UInt32           i = 0;
    while (i < pathObj->nodeList.numNodes)
    {
        curNode = &pathObj->nodeList.list[i];
        if (curNode->nodeType == VGRAPH_NODETYPE_DUMMY)
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "Dummy\r\n");
        }
        else if (curNode->nodeType == VGRAPH_NODETYPE_VIPPORT)
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "VipPort\r\n");
            VpsHal_vipPortSetCfg(pathObj->vipPortHandle,
                                 &pathObj->portCfg, NULL);
        }
        else if (curNode->nodeType == VGRAPH_NODETYPE_VIPMUX)
        {
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "VipMux\r\n");
            VpsCore_VipCfgMux(pathObj, curNode, (UInt32) FALSE);
        }
        else if (curNode->nodeType == VGRAPH_NODETYPE_CSC)
        {
            if (VPS_CSC_MODE_AUTO == pathObj->cscCfg.mode)
            {
                pathObj->cscCfg.mode   = pathObj->cscMode;
                pathObj->cscCfg.bypass = pathObj->cscBypass;
            }
            VpsHal_cscSetConfig(pathObj->cscHandle, &pathObj->cscCfg, 0);
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "CSC\r\n");
        }
        else if (curNode->nodeType == VGRAPH_NODETYPE_SC)
        {
            VpsCore_VipCfgSc(pathObj, curNode);
            GT_0trace(VpsVipCoreTrace, GT_DEBUG, "SC\r\n");
        }
        else
        {
            GT_1trace(VpsVipCoreTrace, GT_DEBUG, "NodeType: %2d\r\n",
                      curNode->nodeType);
        }
        i++;
    }
}

void VpsCore_vipPathCheck422SPOut(VpsCore_VipPathObj       *pathObj,
                                  void                     *retPrms,
                                  UInt32                    strm,
                                  UInt32                   *numPlanes,
                                  const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32 port, portY, portUV;
    VpsHal_VpdmaChanDT       *vpdmaDataType     = pathObj->vpdmaDataType;
    UInt32                   *strm2PortMap      = pathObj->strm2PortMap;
    VpsHal_VpdmaChannel      *strm2VpdmaChanMap =
        &pathObj->strm2VpdmaChanMap[0U][0U];
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32                   *port2StrmMap  = pathObj->port2StrmMap;
    UInt32                   *dstColorSpace = pathObj->dstColorSpace;
    UInt32 tmp;
    VpsHal_VpdmaChanDT  tmpDT;
    VpsHal_VpdmaChannel chan;
    VpsHal_VpdmaChannel tmpChan;

    if ((FVID2_DF_YUV422SP_UV == dstColorSpace[strm]) ||
        (FVID2_DF_YUV422SP_VU == dstColorSpace[strm]))
    {
        *numPlanes = 2U;
        /* Search for Y422 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_YC422,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);

        portY = port;
        if (PORT_MAX == port)
        {
            /* It is error condition, should not come here. */
            GT_assert(VpsVipCoreTrace, ((Bool)(FALSE)));
        }
        else
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_Y_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_Y_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_Y_ADDR_IDX;
            vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_Y422;
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }

        /* Search for C422 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_C422,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX == port)
        {
            port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_YC422,
                                      portDataType,
                                      vpdmaDataType,
                                      pathObj->scActive[strm],
                                      dstColorSpace[strm]);
        }

        portUV = port;
        if (PORT_MAX == port)
        {
            /* It is error condition, should not come here. */
            GT_assert(VpsVipCoreTrace, ((Bool)(FALSE)));
        }
        else
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_CBCR_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_CBCR_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_CBCR_ADDR_IDX;
            if (FVID2_DF_YUV422SP_UV == dstColorSpace[strm])
            {
                vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_C422;
            }
            else if (FVID2_DF_YUV422SP_VU == dstColorSpace[strm])
            {
                vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_Cb422;
            }
            else
            {
                GT_0trace(VpsVipCoreTrace, GT_ERR,
                          "Unsupported 422 dstColorSpace\r\n");
            }
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_CBCR_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }

        if ((FVID2_DF_YUV422I_YUYV == pathObj->srcColorSpace) ||
            (FVID2_DF_YUV422I_YVYU == pathObj->srcColorSpace))
        {
            /* Swap Y and U entries for everything */
            /* strm2VpdmaChanMap */
            tmpChan = strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                                        FVID2_YUV_SP_Y_ADDR_IDX];
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_Y_ADDR_IDX] =
                strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                                  FVID2_YUV_SP_CBCR_ADDR_IDX];
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_CBCR_ADDR_IDX] = tmpChan;

            /* strm2PortMap */
            tmp = strm2PortMap[(strm * FVID2_MAX_PLANES) +
                               FVID2_YUV_SP_Y_ADDR_IDX];
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_Y_ADDR_IDX] =
                strm2PortMap[(strm * FVID2_MAX_PLANES) +
                             FVID2_YUV_SP_CBCR_ADDR_IDX];
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_CBCR_ADDR_IDX] = tmp;

            /* port2StrmMap */
            tmp = port2StrmMap[portY];
            port2StrmMap[portY]  = port2StrmMap[portUV];
            port2StrmMap[portUV] = tmp;

            /* vpdmaDataType */
            tmpDT = vpdmaDataType[portY];
            vpdmaDataType[portY]  = vpdmaDataType[portUV];
            vpdmaDataType[portUV] = tmpDT;

            /* setCfgPrms->subFrmVemEvent */
            tmp = setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX];
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX] =
                setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_CBCR_ADDR_IDX];
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_CBCR_ADDR_IDX] = tmp;
        }
    }
}

void VpsCore_vipPathCheck420SPOut(VpsCore_VipPathObj       *pathObj,
                                  void                     *retPrms,
                                  UInt32                    strm,
                                  UInt32                   *numPlanes,
                                  const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32 port;
    VpsHal_VpdmaChanDT       *vpdmaDataType     = pathObj->vpdmaDataType;
    UInt32                   *strm2PortMap      = pathObj->strm2PortMap;
    VpsHal_VpdmaChannel      *strm2VpdmaChanMap =
        &pathObj->strm2VpdmaChanMap[0U][0U];
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32                   *port2StrmMap  = pathObj->port2StrmMap;
    UInt32                   *dstColorSpace = pathObj->dstColorSpace;
    VpsHal_VpdmaChannel       chan;

    if ((FVID2_DF_YUV420SP_UV == dstColorSpace[strm]) ||
        (FVID2_DF_YUV420SP_VU == dstColorSpace[strm]))
    {
        *numPlanes = 2U;
        /* Search for Y420 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_Y420,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX == port)
        {
            /* TODO what???? check for YC422 ??? */
        }
        else
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_Y_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_Y_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_Y_ADDR_IDX;
            vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_Y420;
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }
        /* Search for C420 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_C420,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX == port)
        {
            /* TODO what???? */
        }
        else
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_CBCR_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_CBCR_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_CBCR_ADDR_IDX;
            if (FVID2_DF_YUV420SP_UV == dstColorSpace[strm])
            {
                vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_C420;
            }
            else if (FVID2_DF_YUV420SP_VU == dstColorSpace[strm])
            {
                vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_Cb420;
            }
            else
            {
                GT_0trace(VpsVipCoreTrace, GT_ERR,
                          "Unsupported 420 dstColorSpace\r\n");
            }
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_CBCR_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }
    }
}

void VpsCore_vipPathCheck422IOut(VpsCore_VipPathObj       *pathObj,
                                 void                     *retPrms,
                                 UInt32                    strm,
                                 UInt32                   *numPlanes,
                                 const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32 port, chId;
    VpsHal_VpdmaChanDT       *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32                   *strm2PortMap  = pathObj->strm2PortMap;
    VpsCore_VipSetCfgRetPrms *setCfgPrms    =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32                   *port2StrmMap  = pathObj->port2StrmMap;
    UInt32                   *dstColorSpace = pathObj->dstColorSpace;
    VpsHal_VpdmaChannel       chan, subFrmChan = VPSHAL_VPDMA_CHANNEL_INVALID;

    if ((FVID2_DF_YUV422I_UYVY == dstColorSpace[strm]) ||
        (FVID2_DF_YUV422I_VYUY == dstColorSpace[strm]) ||
        (FVID2_DF_YUV422I_YUYV == dstColorSpace[strm]) ||
        (FVID2_DF_YUV422I_YVYU == dstColorSpace[strm]))
    {
        *numPlanes = 1U;
        /* Search for YC422 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_YC422,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX == port)
        {
            /* TODO what??? */
        }
        else
        {
            GT_assert(VpsVipCoreTrace,
                (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
            for (chId = 0; chId < pathObj->numChannels; chId++)
            {
                chan = VpsCore_vipGetChan(pathObj, port, chId);
                pathObj->strm2VpdmaChanMap[chId][(strm * FVID2_MAX_PLANES) +
                                                 FVID2_YUV_SP_Y_ADDR_IDX] =
                    chan;
                if (chId == 0U)
                {
                    subFrmChan = chan;  /* Use first ch for subframe client */
                }
            }
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_Y_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_Y_ADDR_IDX;
            vpdmaDataType[port] = VpsHal_vpdmaFvid2ToVpdma(
                (Fvid2_DataFormat) dstColorSpace[strm]);

            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsHal_vpdmaGetClient(subFrmChan);
            pathObj->numActivePorts++;
        }
    }
}

void VpsCore_vipPathCheckRGBOut(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32  port;
    VpsHal_VpdmaChanDT *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32 *strm2PortMap = pathObj->strm2PortMap;
    VpsHal_VpdmaChannel *strm2VpdmaChanMap =
        &pathObj->strm2VpdmaChanMap[0U][0U];
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32 *port2StrmMap  = pathObj->port2StrmMap;
    UInt32 *dstColorSpace = pathObj->dstColorSpace;
    VpsHal_VpdmaChannel chan;

    if ((Int32) TRUE == Fvid2_isDataFmtRgb(pathObj->dstColorSpace[strm]))
    {
        *numPlanes = 1U;
        /* Search for RGB888 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_RGB888,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX != port)
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_RGB_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_RGB_ADDR_IDX] = port;
            port2StrmMap[port] =
                (strm * FVID2_MAX_PLANES) + FVID2_RGB_ADDR_IDX;
            vpdmaDataType[port] = VpsHal_vpdmaFvid2ToVpdma(
                (Fvid2_DataFormat) dstColorSpace[strm]);

            setCfgPrms->subFrmVemEvent[strm][FVID2_RGB_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }
    }
}

void VpsCore_vipPathCheck444Out(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32  port;
    VpsHal_VpdmaChanDT *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32 *strm2PortMap = pathObj->strm2PortMap;
    VpsHal_VpdmaChannel *strm2VpdmaChanMap =
        &pathObj->strm2VpdmaChanMap[0U][0U];
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32 *port2StrmMap  = pathObj->port2StrmMap;
    UInt32 *dstColorSpace = pathObj->dstColorSpace;
    VpsHal_VpdmaChannel chan;

    if (FVID2_DF_YUV444I == dstColorSpace[strm])
    {
        *numPlanes = 1U;
        /* Search for YUV444 */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_YC444,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX != port)
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_YUV_SP_Y_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_YUV_SP_Y_ADDR_IDX] = port;
            port2StrmMap[port] = (strm * FVID2_MAX_PLANES) +
                                 FVID2_YUV_SP_Y_ADDR_IDX;
            /* TODO: VPSHAL_VPDMA_CHANDT_YC444 not working on Ce2.1
             * Need to check on Vayu Zebu */
            vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_BGR888;
            setCfgPrms->subFrmVemEvent[strm][FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }
    }
}

void VpsCore_vipPathCheckANCOut(VpsCore_VipPathObj       *pathObj,
                                void                     *retPrms,
                                UInt32                    strm,
                                UInt32                   *numPlanes,
                                const VpsCore_VipVpdmaDT *portDataType)
{
    UInt32  port;
    VpsHal_VpdmaChanDT *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32 *strm2PortMap = pathObj->strm2PortMap;
    VpsHal_VpdmaChannel *strm2VpdmaChanMap =
        &pathObj->strm2VpdmaChanMap[0U][0U];
    VpsCore_VipSetCfgRetPrms *setCfgPrms =
        (VpsCore_VipSetCfgRetPrms *) retPrms;
    UInt32 *port2StrmMap  = pathObj->port2StrmMap;
    UInt32 *dstColorSpace = pathObj->dstColorSpace;
    VpsHal_VpdmaChannel chan;

    if (FVID2_DF_RAW_VBI == dstColorSpace[strm])
    {
        *numPlanes = 1U;
        /* TODO: Do something */
        port = VpsCore_vipGetPort(VCORE_VIPVPDMA_DT_ANC,
                                  portDataType,
                                  vpdmaDataType,
                                  pathObj->scActive[strm],
                                  dstColorSpace[strm]);
        if (PORT_MAX != port)
        {
            chan = VpsCore_vipGetChan(pathObj, port, (UInt32) 0);
            strm2VpdmaChanMap[(strm * FVID2_MAX_PLANES) +
                              FVID2_RAW_ADDR_IDX] = chan;
            strm2PortMap[(strm * FVID2_MAX_PLANES) +
                         FVID2_RAW_ADDR_IDX] = port;
            port2StrmMap[port] =
                (strm * FVID2_MAX_PLANES) + FVID2_RAW_ADDR_IDX;
            vpdmaDataType[port] = VPSHAL_VPDMA_CHANDT_ANC;
            setCfgPrms->subFrmVemEvent[strm][FVID2_RAW_ADDR_IDX] =
                VpsHal_vpdmaGetClient(chan);
            pathObj->numActivePorts++;
        }
    }
}

UInt32 VpsCore_vipPathGetDataTypeYUp(const VpsCore_VipPathObj *pathObj,
                                     const Vgraph_nodeInfo    *curNode)
{
    UInt32 srcColorSpace = pathObj->srcColorSpace;
    UInt32 numStreams    = 1U;
    Bool   cscActive     = pathObj->cscActive;
    Bool   chrDs0Bypass  = pathObj->chrDs0Bypass;
    VpsCore_VipVpdmaDT *portDataType =
        (VpsCore_VipVpdmaDT *) pathObj->portDataType;

    if (0U != curNode->input.isEnabled[1])
    {
        Bool rgbSrc = (Bool) Fvid2_isDataFmtRgb(srcColorSpace);
        if (cscActive && rgbSrc)
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_YC444;
        }
        else if ((cscActive == TRUE) && (!rgbSrc))
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_RGB888;
        }
        else if (!rgbSrc)
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_YC444;
        }
        else
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_RGB888;
        }
    }
    else if (0U != curNode->input.isEnabled[0])
    {
        if (!chrDs0Bypass)
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_Y420;
        }
        else
        {
            portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_YC422;
        }
    }
    else
    {
        portDataType[PORT_Y_UP] = VCORE_VIPVPDMA_DT_INVALID;
        numStreams--;
    }

    return numStreams;
}

UInt32 VpsCore_vipPathGetDataTypeUVUp(const VpsCore_VipPathObj *pathObj,
                                      const Vgraph_nodeInfo    *curNode)
{
    UInt32 numStreams = 1U;
    VpsCore_VipVpdmaDT *portDataType =
        (VpsCore_VipVpdmaDT *) pathObj->portDataType;

    portDataType[PORT_UV_UP] = VCORE_VIPVPDMA_DT_C420;
    if (0U != curNode->input.isEnabled[0])
    {
        /* Note: isEnabled[1] never gets set! Therefore, refer to chrDs0Bypass
        **/
        if (1 == pathObj->chrDs0Bypass)
        {
            portDataType[PORT_UV_UP] = VCORE_VIPVPDMA_DT_C422;
        }
        else
        {
            portDataType[PORT_UV_UP] = VCORE_VIPVPDMA_DT_C420;
        }
    }
    else if (0U != curNode->input.isEnabled[3])
    {
        portDataType[PORT_UV_UP] = VCORE_VIPVPDMA_DT_YC422;
    }
    else /* 2 or 4 or else */
    {
        numStreams--;
        portDataType[PORT_UV_UP] = VCORE_VIPVPDMA_DT_INVALID;
    }

    return numStreams;
}

UInt32 VpsCore_vipPathGetDataTypeYLo(const VpsCore_VipPathObj *pathObj,
                                     const Vgraph_nodeInfo    *curNode)
{
    UInt32 srcColorSpace = pathObj->srcColorSpace;
    UInt32 numStreams    = 1U;
    VpsCore_VipVpdmaDT *portDataType =
        (VpsCore_VipVpdmaDT *) pathObj->portDataType;

    portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_INVALID;
    if (0U != curNode->input.isEnabled[0])
    {
        if (0 == pathObj->chrDs1Bypass)
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_Y420;
        }
        else
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_YC422;
        }
    }
    else if (0U != curNode->input.isEnabled[1])
    {
        portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_YC422;
    }
    else if (0U != curNode->input.isEnabled[2])
    {
        Bool rgbSrc = (Bool) Fvid2_isDataFmtRgb(srcColorSpace);

        if (((Bool) (1U == pathObj->cscActive)) && rgbSrc)
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_YC444;
        }
        else if (((Bool) (1U == pathObj->cscActive)) && ((Bool) (!rgbSrc)))
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_RGB888;
        }
        else if (!rgbSrc)
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_YC444;
        }
        else
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_RGB888;
        }
    }
    else if (0U != curNode->input.isEnabled[3])
    {
        Bool rgbSrc = (Bool) Fvid2_isDataFmtRgb(srcColorSpace);

        if (!rgbSrc)
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_YC444;
        }
        else
        {
            portDataType[PORT_Y_LO] = VCORE_VIPVPDMA_DT_RGB888;
        }
    }
    else
    {
        numStreams--;
    }

    return numStreams;
}

UInt32 VpsCore_vipPathGetDataTypeUVLo(const VpsCore_VipPathObj *pathObj,
                                      const Vgraph_nodeInfo    *curNode)
{
    UInt32 numStreams = 1U;
    VpsCore_VipVpdmaDT *portDataType =
        (VpsCore_VipVpdmaDT *) pathObj->portDataType;

    portDataType[PORT_UV_LO] = VCORE_VIPVPDMA_DT_INVALID;
    if (0U != curNode->input.isEnabled[0])
    {
        if (0 == pathObj->chrDs1Bypass)
        {
            portDataType[PORT_UV_LO] = VCORE_VIPVPDMA_DT_C420;
        }
        else
        {
            portDataType[PORT_UV_LO] = VCORE_VIPVPDMA_DT_C422;
        }
    }
    else if (0U != curNode->input.isEnabled[1])
    {
        portDataType[PORT_UV_LO] = VCORE_VIPVPDMA_DT_YC422;
    }
    else
    {
        numStreams--;
    }

    return numStreams;
}

void VpsCore_vipCreateCCISCtrlDesc(VpsCore_VipPathObj *pathObj)
{
    VpsHal_VpdmaChannel  channelId;
    UInt8 *descMem;
    UInt32 chId, strm, lineCount;
    VpsHal_VpdmaSocEvent event;
    UInt32 listSize = 0;

    descMem   = pathObj->ctrlDescMem;
    lineCount = 0;

    GT_assert(VpsVipCoreTrace,
        (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        UInt32 numStreams = pathObj->numStreams;

        for (strm = 0; strm < numStreams; strm++)
        {
            channelId =
                pathObj->strm2VpdmaChanMap[chId][strm * FVID2_MAX_PLANES];
            channelId = (VpsHal_VpdmaChannel) ((UInt32) channelId + chId);

            lineCount = 0;
            event     = VPSHAL_VPDMA_SOC_EOF;
            if (0 != pathObj->subFrmPrms[strm].subFrameEnable)
            {
                lineCount = pathObj->subFrmPrms[strm].numLinesPerSubFrame;
                event     = VPSHAL_VPDMA_SOC_EOL;

                if (VPS_INTR_END_OF_NTH_LINE ==
                    pathObj->subFrmPrms[strm].interruptMode)
                {
                    event = VPSHAL_VPDMA_SOC_EOL;
                }

                if (VPS_INTR_END_OF_EVERY_NTH_LINE ==
                    pathObj->subFrmPrms[strm].interruptMode)
                {
                    event = VPSHAL_VPDMA_SOC_EOEL;
                }
            }

            if (lineCount > 0xFFFFU)
            {
                lineCount = 0xFFFFU;
            }

            VpsHal_vpdmaCreateCCISCtrlDesc(
                (Ptr) descMem,                   /* Descriptor Memory Address */
                (VpsHal_VpdmaChannel) channelId, /* VpsHal_VpdmaChannel       */
                event,                           /* VpsHal_VpdmaSocEvent      */
                (UInt16) lineCount,              /* Line Count                */
                0                                /* Pixel Count               */
                );

            listSize = VPSHAL_VPDMA_CTRL_DESC_SIZE;
            /* TODO :: Handle return value */
            VpsHal_vpdmaPostList(pathObj->vpdmaHandle,         /* handle      */
                                 (UInt8) pathObj->listId[chId],/* listNum     */
                                 VPSHAL_VPDMA_LT_NORMAL,       /* listType    */
                                 (Ptr) (pathObj->ctrlDescMem), /* listAddr    */
                                 listSize,                     /* listSize    */
                                 0                             /* enableCheck */
                                 );

            /* TODO :: Wait for List Post to complete. */
            /* TODO :: Fix 3000 */
            VpsHal_vpdmaListWaitComplete(pathObj->vpdmaHandle,
                                         (UInt8) pathObj->listId[chId],
                                         (UInt32) 3000U);
        }
    }

}

void VpsCore_vipPathCreateDesc(VpsCore_VipPathObj *pathObj)
{
    UInt8 *descAddr;
    UInt32 chId, strm, pl;
    VpsHal_VpdmaChanDT *vpdmaDataType = pathObj->vpdmaDataType;
    UInt32             *strm2PortMap  = pathObj->strm2PortMap;

    /*
     * Create Change Client Intr Control Descriptor for Slices.
     */
    VpsCore_vipCreateCCISCtrlDesc(pathObj);

    GT_assert(VpsVipCoreTrace,
        (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        UInt32 numStreams = pathObj->numStreams;

        descAddr = pathObj->descMem[chId];
        for (strm = 0; strm < numStreams; strm++)
        {
            UInt32 numPlanes = pathObj->numPlanes[strm];
            for (pl = 0; pl < numPlanes; pl++)
            {
                VpsHal_VpdmaOutDescParams outDescInfo =
                {
                    VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB,        /* channel     */
                    VPSHAL_VPDMA_CHANDT_RGB888,               /* dataType    */
                    0U,                                       /* lineStride  */
                    VPSHAL_VPDMA_LS_1,                        /* lineSkip    */
                    TRUE,                                     /* notify      */
                    VPSHAL_VPDMA_DATADESCPRIO_0,              /* priority    */
                    VPSHAL_VPDMA_MT_NONTILEDMEM,              /* memType     */
                    VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB,        /* nextChannel */
                    VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED,        /* maxWidth */
                    VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED,       /* maxHeight*/
                    FALSE                                     /* is1DMem  */
                };
                outDescInfo.channel =
                    pathObj->strm2VpdmaChanMap[chId][(strm *
                                                      FVID2_MAX_PLANES) + pl];
                outDescInfo.nextChannel = outDescInfo.channel;
                outDescInfo.dataType    =
                    vpdmaDataType[strm2PortMap[(strm * FVID2_MAX_PLANES) + pl]];
                outDescInfo.lineStride = pathObj->pitch[strm][pl];

                outDescInfo.maxWidth = (Vps_VpdmaMaxOutWidth) \
                                       pathObj->maxOutWidth[strm][pl];
                outDescInfo.maxHeight = (Vps_VpdmaMaxOutHeight) \
                                        pathObj->maxOutHeight[strm][pl];
                outDescInfo.memType =
                    (VpsHal_VpdmaMemoryType) pathObj->memType[strm];

                VpsHal_vpdmaCreateOutBoundDataDesc(
                    (descAddr),
                    &outDescInfo);

                /* TODO: Add TILED memory condition */
                VpsHal_vpdmaSetWriteDesc(descAddr, (UInt8) TRUE);

                descAddr += VPSHAL_VPDMA_DATA_DESC_SIZE;
            }
        }
    }
}

void VpsCore_vipPathCopyConfig(VpsCore_VipPathObj      *pathObj,
                               const VpsCore_VipParams *pathCfg)
{
    UInt32 strm, pl, i;
    VpsCore_VipVpdmaDT *portDataType = pathObj->portDataType;

    BspUtils_memcpy(&pathObj->portCfg,
                    &pathCfg->portCfg,
                    sizeof (Vps_VipPortConfig));

    BspUtils_memcpy(&pathObj->inCropCfg,
                    &pathCfg->inCropCfg,
                    sizeof (Fvid2_CropConfig));

    BspUtils_memcpy(&pathObj->scCfg,
                    &pathCfg->scCfg,
                    sizeof (Vps_ScConfig));
    pathObj->scCfg.advCfg = NULL;
    if (NULL != pathCfg->scCfg.advCfg)
    {
        pathObj->scCfg.advCfg = &(pathObj->scAdvCfg);
        BspUtils_memcpy((void *) (&(pathObj->scAdvCfg)),
                        (void *) (pathCfg->scCfg.advCfg),
                        sizeof (Vps_ScAdvConfig));
    }

    BspUtils_memcpy(&pathObj->cscCfg,
                    &pathCfg->cscCfg,
                    sizeof (Vps_CscConfig));
    pathObj->cscCfg.coeff = NULL;
    if (NULL != pathCfg->cscCfg.coeff)
    {
        pathObj->cscCfg.coeff = &(pathObj->cscCoeff);
        BspUtils_memcpy((void *) (&(pathObj->cscCoeff)),
                        (void *) (pathCfg->cscCfg.coeff),
                        sizeof (Vps_CscCoeff));
    }

    BspUtils_memcpy(&pathObj->subFrmPrms,
                    &pathCfg->subFrmPrms,
                    (UInt32) (sizeof (VpsCore_SubFrameParams) *
                              VPSCORE_VIP_STREAM_ID_MAX));

    pathObj->srcWidth   = pathCfg->srcWidth;
    pathObj->srcHeight  = pathCfg->srcHeight;
    pathObj->numStreams = pathCfg->numStreams;

    /* In case input color-source is RAW8/16/24, process internally as if them
     * input is YC422/YC422/RGB888 respectively.
     * Original values are not currently required - just maintaining for
     * any future use.
     */
    pathObj->srcColorSpace    = pathCfg->srcColorSpace;
    pathObj->orgSrcColorSpace = pathCfg->srcColorSpace;
    if (FVID2_DF_RAW24 == pathCfg->srcColorSpace)
    {
        pathObj->srcColorSpace = FVID2_DF_RGB24_888;
    }
    if ((FVID2_DF_RAW08 == pathCfg->srcColorSpace) ||
        (FVID2_DF_RAW16 == pathCfg->srcColorSpace))
    {
        pathObj->srcColorSpace = FVID2_DF_YUV422I_UYVY;
    }

    for (strm = 0; strm < pathObj->numStreams; strm++)
    {
        pathObj->orgDstColorSpace[strm] = pathCfg->dstColorSpace[strm];
        pathObj->dstColorSpace[strm]    = pathCfg->dstColorSpace[strm];
        if (FVID2_DF_RAW24 == pathCfg->dstColorSpace[strm])
        {
            pathObj->dstColorSpace[strm] = FVID2_DF_RGB24_888;
        }
        if (FVID2_DF_RAW16 == pathCfg->dstColorSpace[strm])
        {
            /* VIP parser expects U/V in D[7:0] and Y in D[15:8]. And in RAW
             * 16-bit we want D[7:0] to go in LSB (0th byte) and D[15:8] to go
             * to MSB (1st byte). Hence use UYVY VPDMA output. */
            pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_UYVY;
        }
        /* VIP parser does swapping of bytes for raw 8 bit input, so
         * swapping it again in VPDMA to nullify the effect. */
        if (FVID2_DF_RAW08 == pathCfg->dstColorSpace[strm])
        {
            pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_UYVY;
        }

        /* If Y and UV are swapped at source, fix it - default
         * expectation is UYVY order in time for 8b/16 mode and
         * U/V in LSBs for 16b mode.
         */
        if (FVID2_DF_YUV422I_YUYV == pathObj->srcColorSpace)
        {
            /* 420SP cannot be supported in this case - so no modifications
             * for 420SP output */
            /* No special handling for 422SP since Y and UV channel swap
             * will be done in VpsCore_vipPathCheck422SPOut() */
            if (FVID2_DF_YUV422I_YUYV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_UYVY;
            }
            else if (FVID2_DF_YUV422I_UYVY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YUYV;
            }
            else if (FVID2_DF_YUV422I_YVYU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_VYUY;
            }
            else if (FVID2_DF_YUV422I_VYUY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YVYU;
            }
            else
            {
                /* Nothing to be done here */
            }
        }
        if (FVID2_DF_YUV422I_YVYU == pathObj->srcColorSpace)
        {
            /* 420SP cannot be supported in this case - so no modifications
             * for 420SP output */
            /* Special handling for 422SP only for UV order.
             * Y and UV channel swap will be done in
             * VpsCore_vipPathCheck422SPOut() */
            if (FVID2_DF_YUV422I_YUYV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_VYUY;
            }
            else if (FVID2_DF_YUV422I_UYVY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YVYU;
            }
            else if (FVID2_DF_YUV422I_YVYU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_UYVY;
            }
            else if (FVID2_DF_YUV422I_VYUY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YUYV;
            }
            else if (FVID2_DF_YUV422SP_UV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422SP_VU;
            }
            else if (FVID2_DF_YUV422SP_VU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422SP_UV;
            }
            else
            {
                /* Nothing to be done here */
            }
        }
        if (FVID2_DF_YUV422I_VYUY == pathObj->srcColorSpace)
        {
            /* Special handling for 420SP and 422SP only for UV order.
             * Y and UV channel swap will be done in
             * VpsCore_vipPathCheck422SPOut() */
            if (FVID2_DF_YUV422I_YUYV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YVYU;
            }
            else if (FVID2_DF_YUV422I_UYVY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_VYUY;
            }
            else if (FVID2_DF_YUV422I_YVYU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_YUYV;
            }
            else if (FVID2_DF_YUV422I_VYUY == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422I_UYVY;
            }
            else if (FVID2_DF_YUV420SP_UV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV420SP_VU;
            }
            else if (FVID2_DF_YUV420SP_VU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV420SP_UV;
            }
            else if (FVID2_DF_YUV422SP_UV == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422SP_VU;
            }
            else if (FVID2_DF_YUV422SP_VU == pathObj->dstColorSpace[strm])
            {
                pathObj->dstColorSpace[strm] = FVID2_DF_YUV422SP_UV;
            }
            else
            {
                /* Nothing to be done here */
            }
        }
    }

    for (strm = 0; strm < pathObj->numStreams; strm++)
    {
        pathObj->tarWidth[strm]  = pathCfg->tarWidth[strm];
        pathObj->tarHeight[strm] = pathCfg->tarHeight[strm];
        pathObj->memType[strm]   = pathCfg->memType[strm];

        for (pl = 0U; pl < FVID2_MAX_PLANES; pl++)
        {
            pathObj->pitch[strm][pl]        = pathCfg->pitch[strm][pl];
            pathObj->maxOutWidth[strm][pl]  = pathCfg->maxOutWidth[strm][pl];
            pathObj->maxOutHeight[strm][pl] = pathCfg->maxOutHeight[strm][pl];
        }

        pathObj->scActive[strm] = pathCfg->scActive[strm];
    }

    for (i = 0; i < PORT_MAX; i++)
    {
        portDataType[i] = VCORE_VIPVPDMA_DT_INVALID;
    }
    pathObj->cscActive = pathObj->chrDs0Bypass = pathObj->chrDs1Bypass = 0;
}

Int32 VpsCore_vipValidateVipParams(const VpsCore_VipParams *pathCfg)
{
    Int32  retVal    = BSP_SOK;
    UInt32 numStream = pathCfg->numStreams;
    UInt32 memType;
    UInt32 strm, pl;

    /*
     * Validate the MAX OUT WIDTH/HEIGHT parameters.
     */
    for (strm = 0; strm < numStream; strm++)
    {
        memType = pathCfg->memType[strm];
        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            if (pathCfg->maxOutWidth[strm][pl] >
                VPS_VPDMA_MAX_OUT_WIDTH_1920_PIXELS)
            {
                retVal = BSP_EINVALID_PARAMS;
            }

            if (pathCfg->maxOutHeight[strm][pl] >
                VPS_VPDMA_MAX_OUT_HEIGHT_1080_LINES)
            {
                retVal = BSP_EINVALID_PARAMS;
            }

            /*
             * For TILED memory type, the maxOutWidth and maxOutHeight
             * should be set to UNLIMITED.
             */
            if ((memType == VPS_VPDMA_MT_TILEDMEM) &&
                ((pathCfg->maxOutWidth[strm][pl] != \
                  VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED) ||
                 (pathCfg->maxOutHeight[strm][pl] != \
                  VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED)))
            {
                retVal = BSP_EINVALID_PARAMS;
            }
        }
    }

    /* Validate constraints for RAW8/16/24 inputs
     * In this case, output streams should be of same type.
     * Allow ancillary data, but do not allow RGB/YUV/etc formats.
     */
    if ((FVID2_DF_RAW24 == pathCfg->srcColorSpace) ||
        (FVID2_DF_RAW16 == pathCfg->srcColorSpace) ||
        (FVID2_DF_RAW08 == pathCfg->srcColorSpace))
    {
        for (strm = 0; strm < numStream; strm++)
        {
            if ((pathCfg->dstColorSpace[strm] != FVID2_DF_RAW_VBI) &&
                (pathCfg->dstColorSpace[strm] != pathCfg->srcColorSpace))
            {
                retVal = BSP_EINVALID_PARAMS;
            }
        }
    }
    return (retVal);
}

#if 0
Int32 VpsCore_vipPathGetDefConfig_Old(VpsCore_VipPathObj *pathObj,
                                      Vcore_GetVipParams *pathCfg)
{
    UInt32 strm;
    Vps_CaptVipParams   *captVipParams;
    Vps_CaptVipScParams *captVipScParams;
    Vps_VipPortConfig   *captVipPortCfg;
    Vps_CscConfig       *captVipCscCfg;

    captVipParams   = pathCfg->vipPrms;
    captVipScParams = captVipParams->scPrms;
    captVipPortCfg  = captVipParams->vipPortCfg;
    captVipCscCfg   = captVipParams->cscCfg;

    Fvid2Format_init(&captVipParams->inFmt);
    for (strm = 0U; strm < VPS_CAPT_VIP_STREAM_ID_MAX; strm++)
    {
        VpsCaptVipOutInfo_init(&captVipParams->outStreamInfo[strm]);
    }

    if (NULL != captVipScParams)
    {
        captVipScParams->scCfg.bypass           = 1;
        captVipScParams->scCfg.nonLinear        = 0;
        captVipScParams->scCfg.stripSize        = 0;
        captVipScParams->scCfg.enableEdgeDetect = 0;
        captVipScParams->scCfg.enablePeaking    = 1;
        VpsScAdvConfig_init(&(pathObj->defScAdvCfg));
        if (NULL != captVipScParams->scCfg.advCfg)
        {
            BspUtils_memcpy((void *) (captVipScParams->scCfg.advCfg),
                            (void *) (&(pathObj->defScAdvCfg)),
                            sizeof (Vps_ScAdvConfig));
        }
        captVipScParams->inCropCfg.cropStartX = pathObj->defScAdvCfg.cropStartX;
        captVipScParams->inCropCfg.cropStartY = pathObj->defScAdvCfg.cropStartY;
        captVipScParams->inCropCfg.cropWidth  = pathObj->defScAdvCfg.cropWidth;
        captVipScParams->inCropCfg.cropHeight = pathObj->defScAdvCfg.cropHeight;
        /* TODO: Need to fix this when user-coeffs are supported */
        /* captVipScParams->scCoeffCfg = NULL; */
        captVipScParams->enableCoeffLoad = 0;
    }

    VpsVipPortConfig_init(captVipPortCfg);

    captVipCscCfg->bypass = 1;
    captVipCscCfg->mode   = VPS_CSC_MODE_AUTO;

    return BSP_SOK;
}

#endif

Int32 VpsCore_vipPathGetDefConfig(VpsCore_VipPathObj *pathObj,
                                  VpsCore_VipParams  *pathCfg)
{
    UInt32 strm, pl;

    pathCfg->srcColorSpace = FVID2_DF_YUV422I_YUYV;
    pathCfg->srcWidth      = 0;
    pathCfg->srcHeight     = 0;
    pathCfg->numStreams    = 1;
    for (strm = 0U; strm < VPS_CAPT_VIP_STREAM_ID_MAX; strm++)
    {
        pathCfg->dstColorSpace[strm] = FVID2_DF_YUV422I_YUYV;
        pathCfg->tarWidth[strm]      = 0;
        pathCfg->tarHeight[strm]     = 0;
        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            pathCfg->pitch[strm][pl] = 0;
        }
        pathCfg->scActive[strm] = 0;
    }
    pathCfg->edgeInfoList.numEdges = 0;

    VpsVipPortConfig_init(&pathCfg->portCfg);

    pathCfg->inCropCfg.cropStartX = pathObj->defScAdvCfg.cropStartX;
    pathCfg->inCropCfg.cropStartY = pathObj->defScAdvCfg.cropStartY;
    pathCfg->inCropCfg.cropWidth  = pathObj->defScAdvCfg.cropWidth;
    pathCfg->inCropCfg.cropHeight = pathObj->defScAdvCfg.cropHeight;

    pathCfg->scCfg.bypass           = 1;
    pathCfg->scCfg.nonLinear        = 0;
    pathCfg->scCfg.stripSize        = 0;
    pathCfg->scCfg.enableEdgeDetect = 0;
    pathCfg->scCfg.enablePeaking    = 1;
    VpsScAdvConfig_init(&(pathObj->defScAdvCfg));
    if (NULL != pathCfg->scCfg.advCfg)
    {
        BspUtils_memcpy((void *) (pathCfg->scCfg.advCfg),
                        (void *) (&(pathObj->defScAdvCfg)),
                        sizeof (Vps_ScAdvConfig));
    }

    pathCfg->cscCfg.bypass = 1;
    pathCfg->cscCfg.mode   = VPS_CSC_MODE_AUTO;

    for (strm = 0U; strm < VPS_CAPT_VIP_STREAM_ID_MAX; strm++)
    {
        pathCfg->subFrmPrms[strm].subFrameEnable      = (UInt32) FALSE;
        pathCfg->subFrmPrms[strm].numLinesPerSubFrame = 0;

        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            pathCfg->maxOutWidth[strm][pl] =
                VPS_VPDMA_MAX_OUT_WIDTH_768_PIXELS;
            pathCfg->maxOutHeight[strm][pl] =
                VPS_VPDMA_MAX_OUT_HEIGHT_288_LINES;
        }
        pathCfg->memType[strm] = VPS_VPDMA_MT_NONTILEDMEM;
    }

    return BSP_SOK;
}

void VpsCore_vipUpdateVipCoreStats(const VpsCore_VipPathObj *pathObj,
                                   const VpsCore_Frame      *outFrame,
                                   UInt32                    isWrDescValid)
{
    Int32 retVal = BSP_SOK;
    VpsHal_VipPortErrStatus vipErrStatus;
    retVal = VpsHal_vipPortGetErrorStatus(pathObj->vipPortHandle,
                                          &vipErrStatus);

    if ((NULL != outFrame->coreStats) && (BSP_SOK == retVal))
    {
        VpsCore_VipCoreStats *vipCoreStats =
            (VpsCore_VipCoreStats *) (outFrame->coreStats);
        vipCoreStats->isWrDescValid      = isWrDescValid;
        vipCoreStats->isOutputOverflow   = vipErrStatus.isOutputOverflow;
        vipCoreStats->isAsyncOverflow    = vipErrStatus.isAsyncOverflow;
        vipCoreStats->isActProtViolation = vipErrStatus.isActProtViolation;
        vipCoreStats->isAncProtViolation = vipErrStatus.isAncProtViolation;
    }
}

UInt32 VpsCore_vipUpdateDesc(VpsCore_VipPathObj *pathObj, UInt32 chId)
{
    VpsCore_Frame **inpFrame;
    VpsCore_Frame **outFrame;
    UInt32          strm, pl;
    UInt32          listSize = 0;
    UInt32          numPlanes;
    UInt32          outFrmIdx = pathObj->outFrmIdx[chId];
    UInt32          inpFrmIdx = pathObj->inpFrmIdx[chId];
    UInt8          *descAddr, *wrDescAddr, *outWrDescAddr;
    VpsHal_VpdmaWriteDescParams wrDescPrms;

    descAddr      = pathObj->descMem[chId];
    wrDescAddr    = pathObj->wrDescMem[chId][inpFrmIdx];
    outWrDescAddr = pathObj->wrDescMem[chId][outFrmIdx];
    for (strm = 0; strm < pathObj->numStreams; strm++)
    {
        outFrame  = &(pathObj->inputFrame[chId][strm][outFrmIdx]);
        numPlanes = pathObj->numPlanes[strm];

        GT_assert(VpsVipCoreTrace, (numPlanes <= FVID2_MAX_PLANES));

        if (0U == pathObj->initialWait[chId])
        {
            VpsHal_vpdmaParseWriteDesc(
                (const void *) outWrDescAddr,
                &wrDescPrms);

            (*outFrame)->width  = wrDescPrms.frameWidth;
            (*outFrame)->height = wrDescPrms.frameHeight;
            if (TRUE == wrDescPrms.isValid)
            {
                (*outFrame)->fid = wrDescPrms.fid;
            }
            else
            {
                (*outFrame)->fid = FVID2_FID_TOP;
            }

            VpsCore_vipUpdateVipCoreStats(pathObj,
                                          *outFrame,
                                          wrDescPrms.isValid);

            (*outFrame)->status = FVID2_FRAME_STATUS_COMPLETED;

            pathObj->frmDoneCb(pathObj->drvData, *outFrame);
            outWrDescAddr += (VPSHAL_VPDMA_DATA_DESC_SIZE * numPlanes);
        }

        inpFrame  = &(pathObj->inputFrame[chId][strm][inpFrmIdx]);
        *inpFrame = pathObj->reqFrmCb(pathObj->drvData, strm, chId);

        for (pl = 0; pl < numPlanes; pl++)
        {
            VpsHal_vpdmaSetDropData((Ptr) descAddr, (UInt8) FALSE);
            VpsHal_vpdmaSetAddress((Ptr) descAddr, 0,
                                   (*inpFrame)->addr[0][pl]);
            if ((TRUE == (*inpFrame)->dropFrm) ||
                (NULL == (*inpFrame)->addr[0][pl]))
            {
                VpsHal_vpdmaSetDropData((Ptr) descAddr, (UInt8) TRUE);
            }

            /* TODO: Added TILED memory condition */
            VpsHal_vpdmaSetDescWriteAddr((Ptr) (descAddr), (Ptr) wrDescAddr);

            wrDescAddr += VPSHAL_VPDMA_DATA_DESC_SIZE;
            descAddr   += VPSHAL_VPDMA_DATA_DESC_SIZE;
            listSize   += VPSHAL_VPDMA_DATA_DESC_SIZE;
        }
    }

    return listSize;
}

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
Int32 VpsCore_vipCheckMaxSizeParams(const Vps_VpdmaMaxSizeParams *vipMaxFrmPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 regCnt;

    /*
     * vipInstId:
     * can take 3 values for VPS_VIP1, VPS_VIP2 and VPS_VIP3.
     */
    if (vipMaxFrmPrms->instId >= VPS_VIP_MAX)
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    for (regCnt = 0; regCnt < VPS_VPDMA_NUM_MAXSIZE_REG; regCnt++)
    {
        /*
         * maxOutWidth:
         * should be in the range of [1, 4096].
         */
        if ((vipMaxFrmPrms->maxOutWidth[regCnt] < VPS_VIP_MAXSIZE_MIN_WIDTH) ||
            (vipMaxFrmPrms->maxOutWidth[regCnt] > VPS_VIP_MAXSIZE_MAX_WIDTH))
        {
            retVal = BSP_EINVALID_PARAMS;
        }

        /*
         * maxOutHeight:
         * should be in the range of [1, 2048].
         */
        if ((vipMaxFrmPrms->maxOutHeight[regCnt] <
             VPS_VIP_MAXSIZE_MIN_HEIGHT) ||
            (vipMaxFrmPrms->maxOutHeight[regCnt] > VPS_VIP_MAXSIZE_MAX_HEIGHT))
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    return (retVal);
}

