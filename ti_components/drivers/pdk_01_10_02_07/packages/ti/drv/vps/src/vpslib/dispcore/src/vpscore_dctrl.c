/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vpscore_dss.c
 *
 *  \brief DSS core implementation
 *  This file implements the VPS core interface for DSS.
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
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dctrlPriv.h>
#include <ti/drv/vps/src/vpslib/dispcore/src/vpscore_dssWbPriv.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

VpsCore_DctrlInfo  DctrlCoreInfo;

BspOsal_IntrHandle Dctrlcore_intrHandle = NULL;

/**<Interrupt handle for DCTRL */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static UInt32 VpsCore_convertGraphIdtoOvlyIndex(UInt32 graphId);
static UInt32 VpsCore_convertVencIdtoOvlyIndex(UInt32 vencId);
static UInt32 VpsCore_convertGraphIdtoPipeIndex(UInt32 graphId);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void vpsCoreDctrlDispcIsr(UInt32 arg0);

#ifdef __cplusplus
}
#endif

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
static Int32 vpscore_dctrlHdmiPowerOn(const VpsHal_DssHdmiTimingParam *hdmiCfg);
static Int32 VpsHdmiConfCopy(VpsHal_DssHdmiTimingParam *hdmiConf,
                             const Vps_DctrlConfig     *dctrlCfg,
                             UInt32                     vencId);
static void vpscore_dctrlHdmiPowerOff(void);
#endif

void VpsCore_DctrlSetInfo(const VpsCore_DctrlObj *pDctrlInstObj);
Int32 VpsCore_DctrlSetPathInfo(const Vps_DctrlModeInfo *ModeInfo,
                               UInt32                   VencId,
                               UInt32                   VenNodeNum);
void VpsCore_DctrlResetInfo(VpsCore_DctrlObj *pDctrlInstObj);
VpsCore_DctrlPipe *VpsCore_DctrlOpenPipe(
    VpscoreDctrl_NodeNum nodeNum,
    const Vpscore_dctrlClientInfo *
    clientInfo);
void VpsCore_DctrlSetGO(UInt32 ovlNodeNum);
Int32 VpsLcdConfCopy(VpsHal_DssDispcLcdTimingParam *lcdConf,
                     const Vps_DctrlConfig         *dctrlCfg,
                     UInt32                         vencId);
Int32 VpsConvGraphNodetoOvlMgrHandle(UInt32 nodeInfo);
void Vpscore_DctrlsetParallelSelect(const VpsCore_DctrlObj *pDctrlInstObj);

Int32 Vpscore_dctlrUpdateErrorCount(UInt64 irqStatus);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsCore_DctrlObj  gVcoreDctrlObj;
/** \brief DSS core function pointer. */

static const VpsCore_Ops gDctrlCoreOps =
{
    &VpsCore_dctrlGetProperty, /* Get property */
    NULL,                      /* Open function */
    NULL,                      /* Close function */
    NULL,                      /* Set config */
    NULL,                      /* Get config */
    &VpsCore_dctrlControl,     /* Control */
    NULL,                      /* Start */
    NULL,                      /* Stop */
    NULL,                      /* Process */
    NULL,                      /* progBuffer */
    NULL,                      /* putFrames */
    NULL,                      /* getFrames */
    NULL,                      /* Get error stats */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

VpsCore_Inst VpsCore_dctrlInit(const VpsCore_DctrlInitParams *initParams)
{
    VpsCore_DctrlObj *pNewObj = &gVcoreDctrlObj;
    UInt32 cnt = 0;

    BspUtils_memset(&DctrlCoreInfo, 0, sizeof (DctrlCoreInfo));

    for (cnt = 0; cnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; cnt++)
    {
        DctrlCoreInfo.dvoFmt[cnt] = VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    }

    pNewObj->dispcIrqNumber = initParams->dispcIrqNumber;

    pNewObj->ovlHandle[0] = initParams->ovlHandle[0];
    pNewObj->ovlHandle[1] = initParams->ovlHandle[1];
    pNewObj->ovlHandle[2] = initParams->ovlHandle[2];
    pNewObj->ovlHandle[3] = initParams->ovlHandle[3];

    VpsCore_DctrlInit(pNewObj);

    if (NULL == Dctrlcore_intrHandle)
    {
        BspOsal_clearIntr(pNewObj->dispcIrqNumber);
        /* ----------------- Register ISR --------------- */
        Dctrlcore_intrHandle = BspOsal_registerIntr(
            pNewObj->dispcIrqNumber,
            &vpsCoreDctrlDispcIsr,
            NULL);
        if (NULL == Dctrlcore_intrHandle)
        {
            GT_0trace(VpsDctrlCoreTrace, GT_ERR,
                      "DISPC ISR create failed!!\r\n");
        }
    }

    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_dctrlDeInit(VpsCore_Inst pDctrlHandle)
{
    if (NULL != Dctrlcore_intrHandle)
    {
        BspOsal_unRegisterIntr(&Dctrlcore_intrHandle);
        Dctrlcore_intrHandle = NULL;
    }

    VpsCore_DctrlDeInit(pDctrlHandle);

    return BSP_SOK;
}

/**
 *  VpsCore_dctrlGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dctrlGetCoreOps(void)
{
    return (&gDctrlCoreOps);
}

Int32 VpsCore_dctrlGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;

    if (NULL != property)
    {
        property->name = VPSCORE_DISP_DCTRL;
        retVal         = BSP_SOK;
    }

    return (retVal);
}

void VpsCore_DctrlSetInfo(const VpsCore_DctrlObj *pDctrlInstObj)
{
    Vgraph_edgeInfo *curEdge, *vencEdge;
    UInt32           i, j;

    for (i = 0; i < pDctrlInstObj->dctrlEdgeList.numEdges; i++)
    {
        curEdge = &pDctrlInstObj->dctrlEdgeList.list[i];
        switch (curEdge->startNode)
        {
            case GRAPH_DCTRL_DSS_VID1:
            case GRAPH_DCTRL_DSS_VID2:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
            case GRAPH_DCTRL_DSS_VID3:
#endif
            case GRAPH_DCTRL_DSS_GFX:
                GT_assert(VpsDctrlCoreTrace,
                    (DctrlCoreInfo.numPipes < VPSHAL_DSS_DISPC_PIPE_MAX_INST));
                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].ovlNodeNum =
                    curEdge->endNode;
                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].pipeNodeNum =
                    curEdge->startNode;
                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].state =
                    VPS_DCTRL_PIPE_IDLE;
                for (j = 0; j < pDctrlInstObj->dctrlEdgeList.numEdges; j++)
                {
                    vencEdge = &pDctrlInstObj->dctrlEdgeList.list[j];
                    if (vencEdge->startNode == curEdge->endNode)
                    {
                        DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].
                        VencNodeNum = vencEdge->endNode;
                        switch (vencEdge->startNode)
                        {
                            case GRAPH_DCTRL_DSS_LCD1_BLENDER:
                                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].
                                vencId = VPS_DCTRL_DSS_VENC_LCD1;
                                break;
                            case GRAPH_DCTRL_DSS_LCD2_BLENDER:
                                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].
                                vencId = VPS_DCTRL_DSS_VENC_LCD2;
                                break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                            case GRAPH_DCTRL_DSS_LCD3_BLENDER:
                                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].
                                vencId = VPS_DCTRL_DSS_VENC_LCD3;
                                break;
                            case GRAPH_DCTRL_DSS_HDMI_BLENDER:
                                DctrlCoreInfo.VidInfo[DctrlCoreInfo.numPipes].
                                vencId = VPS_DCTRL_DSS_VENC_HDMI;
                                break;
#endif
                            default:
                                break;
                        }
                    }
                }
                DctrlCoreInfo.numPipes++;
                break;
            default:
                break;
        }
    }
}

Int32 VpsCore_DctrlSetPathInfo(const Vps_DctrlModeInfo *ModeInfo,
                               UInt32                   VencId,
                               UInt32                   VenNodeNum)
{
    UInt32 i;
    Int32  retVal = BSP_EFAIL;

    for (i = 0; i < DctrlCoreInfo.numVencs; i++)
    {
        if (DctrlCoreInfo.pathInfo[i].vencId == VencId)
        {
            DctrlCoreInfo.pathInfo[i].isVencRunning = ModeInfo->isVencRunning;
            DctrlCoreInfo.pathInfo[i].scanFormat    =
                ModeInfo->mInfo.scanFormat;
            DctrlCoreInfo.pathInfo[i].standard = ModeInfo->mInfo.standard;
            DctrlCoreInfo.pathInfo[i].width    = ModeInfo->mInfo.width;
            DctrlCoreInfo.pathInfo[i].height   = ModeInfo->mInfo.height;
            retVal = BSP_SOK;
            break;
        }
    }
    if (retVal != BSP_SOK)
    {
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].isVencRunning =
            ModeInfo->isVencRunning;
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].scanFormat =
            ModeInfo->mInfo.scanFormat;
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].standard =
            ModeInfo->mInfo.standard;
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].width =
            ModeInfo->mInfo.width;
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].height =
            ModeInfo->mInfo.height;
        DctrlCoreInfo.pathInfo[DctrlCoreInfo.numVencs].vencId = VencId;
        DctrlCoreInfo.numVencs++;
        retVal = BSP_SOK;
    }
    return retVal;
}

void VpsCore_DctrlResetInfo(VpsCore_DctrlObj *pDctrlInstObj)
{
    /* TODO currently clear config clears all the nodes, We should make it more
     * intuitive to delete
     * only nodes that are not needed and check for the state, whether it is
     * running or not and then disable
     */
    BspUtils_memset(&DctrlCoreInfo, 0, sizeof (DctrlCoreInfo));
}

/* Index of DctrlCoreInfo of ovly pipe is returned */
VpsCore_DctrlPipe *VpsCore_DctrlOpenPipe(
    VpscoreDctrl_NodeNum nodeNum,
    const Vpscore_dctrlClientInfo *
    clientInfo)
{
    UInt32 i;
    VpsCore_DctrlPipe *retDctrlPipe = NULL;

    GT_assert(VpsDctrlCoreTrace,
                (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
    for (i = 0; i < DctrlCoreInfo.numPipes; i++)
    {
        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum == nodeNum)
        {
            DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn = clientInfo->cbFxn;
            DctrlCoreInfo.VidInfo[i].gClientInfo.arg   = clientInfo->arg;
            DctrlCoreInfo.VidInfo[i].gClientInfo.clientMode
                = clientInfo->clientMode;
            DctrlCoreInfo.VidInfo[i].state = VPS_DCTRL_PIPE_OPENED;
            retDctrlPipe = &DctrlCoreInfo.VidInfo[i];
            break;
        }
    }

    /* For WB instance allocate DctrlPipePipe object.
     * Update will be done in set cfg of Wb Pipe. */
    if ((DctrlCoreInfo.numPipes < VPSHAL_DSS_DISPC_PIPE_MAX_INST) &&
        (i == DctrlCoreInfo.numPipes))
    {
        if (nodeNum == VPSCORE_DCTRL_NODE_WB)
        {
            DctrlCoreInfo.VidInfo[i].pipeNodeNum       = nodeNum;
            DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn = clientInfo->cbFxn;
            DctrlCoreInfo.VidInfo[i].gClientInfo.arg   = clientInfo->arg;
            DctrlCoreInfo.VidInfo[i].gClientInfo.clientMode
                = clientInfo->clientMode;
            DctrlCoreInfo.VidInfo[i].state = VPS_DCTRL_PIPE_OPENED;
            retDctrlPipe = &DctrlCoreInfo.VidInfo[i];
            DctrlCoreInfo.numPipes++;
        }
    }

    return (retDctrlPipe);
}

void VpsCore_DctrlSetGO(UInt32 ovlNodeNum)
{
    UInt32 ovlyId;
    Int32  retVal;

    ovlyId = VpsCore_convertGraphIdtoOvlyIndex(ovlNodeNum);
    retVal = VpsHal_dssOvlySetGoBit(ovlyId);

    if (BSP_SOK != retVal)
    {
        GT_1trace(VpsDctrlCoreTrace, GT_ERR,
                  "Failed to set Go Bit for OVL ID %d\r\n",
                  ovlyId);
    }
}

Int32  Vpscore_dctrlClrErrorCount(VpscoreDctrlClientHandle handle)
{
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;
    Int32 retVal = BSP_SOK;

    GT_assert(VpsDctrlCoreTrace, (NULL != handle));

    switch (VidInfo->pipeNodeNum)
    {
        case GRAPH_DCTRL_DSS_VID1:
        {
            DctrlCoreInfo.errorCnt.vid1BufferUnderflow = 0;
        }
        break;
        case GRAPH_DCTRL_DSS_VID2:
        {
            DctrlCoreInfo.errorCnt.vid2BufferUnderflow = 0;
        }
        break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        case GRAPH_DCTRL_DSS_VID3:
        {
            DctrlCoreInfo.errorCnt.vid3BufferUnderflow = 0;
        }
        break;
#endif
        case GRAPH_DCTRL_DSS_GFX:
        {
            DctrlCoreInfo.errorCnt.gfxBufferUnderflow = 0;
        }
        break;

        case GRAPH_DCTRL_DSS_WB:
        {
            DctrlCoreInfo.errorCnt.wbBufferOverflow  = 0;
            DctrlCoreInfo.errorCnt.wbIncompleteError = 0;
        }
        break;

        default:
            GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Pipeline\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return retVal;
}

Int32 Vpscore_dctrlGetDssVidErrorCount(VpscoreDctrlClientHandle   handle,
                                       VpsCore_DssVidErrorStatus *retParams)
{
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;
    Int32 retVal = BSP_SOK;

    GT_assert(VpsDctrlCoreTrace, (NULL != handle));

    switch (VidInfo->pipeNodeNum)
    {
        case GRAPH_DCTRL_DSS_VID1:
        {
            retParams->vidBufferUnderflow =
                DctrlCoreInfo.errorCnt.vid1BufferUnderflow;
        }
        break;
        case GRAPH_DCTRL_DSS_VID2:
        {
            retParams->vidBufferUnderflow =
                DctrlCoreInfo.errorCnt.vid2BufferUnderflow;
        }
        break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        case GRAPH_DCTRL_DSS_VID3:
        {
            retParams->vidBufferUnderflow =
                DctrlCoreInfo.errorCnt.vid3BufferUnderflow;
        }
        break;
#endif
        case GRAPH_DCTRL_DSS_GFX:
        {
            retParams->vidBufferUnderflow =
                DctrlCoreInfo.errorCnt.gfxBufferUnderflow;
        }
        break;

        default:
            GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Pipeline\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return retVal;
}

Int32 Vpscore_dctrlGetDssWbErrorCount(VpscoreDctrlClientHandle  handle,
                                      VpsCore_DssWbErrorStatus *retParams)
{
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;
    Int32 retVal = BSP_SOK;

    GT_assert(VpsDctrlCoreTrace, (NULL != handle));

    switch (VidInfo->pipeNodeNum)
    {
        case GRAPH_DCTRL_DSS_WB:
        {
            retParams->wbBufferOverflow =
                DctrlCoreInfo.errorCnt.wbBufferOverflow;
            retParams->wbIncompleteError =
                DctrlCoreInfo.errorCnt.wbIncompleteError;
        }
        break;

        default:
            GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Pipeline\r\n");
            retVal = BSP_EFAIL;
            break;
    }

    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_018)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-997)
 */
static void vpsCoreDctrlDispcIsr(UInt32 arg0)
{
    UInt64 irqStatus = 0;
    UInt32 i         = 0;

    GT_assert(VpsDctrlCoreTrace,
                (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));

    irqStatus = VpsHal_dssOvlyGetIrqStat();
    VpsHal_dssOvlyClearIrq(irqStatus);

    for (i = 0; i < DctrlCoreInfo.numPipes; i++)
    {
        if ((DctrlCoreInfo.VidInfo[i].state == VPS_DCTRL_PIPE_RUNNING) ||
            (DctrlCoreInfo.VidInfo[i].state == VPS_DCTRL_PIPE_STARTED))
        {
            switch (DctrlCoreInfo.VidInfo[i].ovlNodeNum)
            {
                case GRAPH_DCTRL_DSS_LCD1_BLENDER:

                    /* This is line number interrupt, once this occurs we mark
                     * push as not safe, this variable will be reset in vsync
                     * ISR, Note LIne number interrupt is configured at
                     * height-5 lines. Only Applicable for LCD1 Blender, other
                     * pipelines wont support low latency display. */
                    if ((irqStatus & 0x20U) == 0x20U)
                    {
                        DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD1] =
                            (UInt32) FALSE;
                    }

                    /*  For all Pipelines VID,GFX and WB callback will be called
                     *  in VSYNC ISR only, WBDELAY Count should be equal to
                     *  VFP. */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                    if ((irqStatus & 0x2U) == 0x2U)
                    {
                        if (DctrlCoreInfo.VidInfo[i].state ==
                                VPS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first VSync after DSS Core has
                             * started the pipe. Update pipe status.
                             */
                            DctrlCoreInfo.VidInfo[i].state =
                                VPS_DCTRL_PIPE_RUNNING;
                        }

                        DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD1] =
                            (UInt32) TRUE;
                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum ==
                                GRAPH_DCTRL_DSS_WB)
                        {
                            VpsCore_DssWbPathObj *pathObj = NULL;
                            pathObj =
                                (VpsCore_DssWbPathObj *) (DctrlCoreInfo.VidInfo
                                                        [i].
                                                        gClientInfo.arg);
                            if (pathObj->pipeDisableStatus ==
                                 VPSCORE_DSSWB_PIPE_DISABLE_INITIATED)
                            {
                                /* Pipe disable is done.
                                * Unblock the stop call */
                                pathObj->pipeDisableStatus =
                                    VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE;
                                BspOsal_semPost(pathObj->pipeDisableSem);
                            }
                        }
                    }
#endif

#if defined (SOC_TDA3XX)
                    /* For VID and GFX the callback will be given at VSync
                     * and for WB it will be given at WB Sync Interrupt, this
                     * is the point where shadow to work copy happens for WB.*/
                    if (((irqStatus & 0x2U) == 0x2U) &&
                        (DctrlCoreInfo.VidInfo[i].pipeNodeNum !=
                         GRAPH_DCTRL_DSS_WB))
                    {
                        if (DctrlCoreInfo.VidInfo[i].state ==
                                VPS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first VSync after DSS Core has
                             * started the pipe. Update pipe status.
                             */
                            DctrlCoreInfo.VidInfo[i].state =
                                VPS_DCTRL_PIPE_RUNNING;
                        }

                        DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD1] =
                            (UInt32) TRUE;
                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                    }
                    if (DctrlCoreInfo.VidInfo[i].pipeNodeNum ==
                        GRAPH_DCTRL_DSS_WB)
                    {
                        VpsCore_DssWbPathObj *pathObj = NULL;
                        pathObj =
                            (VpsCore_DssWbPathObj *) (DctrlCoreInfo.VidInfo
                                                      [i].
                                                      gClientInfo.arg);
                        if ((irqStatus & 0x400000000U) == 0x400000000U)
                        {
                            /* VSyncOdd Event happened. It is set only in case
                             * of interlaced display, at the end of odd field.
                             * update this status in wb path object. It is used
                             * to decide whether to give callback to app in
                             * WB Sync interrupt. */
                            pathObj->currentFieldVal = FVID2_FID_TOP;
                            if (pathObj->fieldsCaptured ==
                                    VPSCORE_DSSWB_CAPTURE_NOT_STARTED)
                            {
                                /* WB pipe is started after last Vsync and
                                 * before this VSync Odd. Odd Field was not
                                 * written in buffer. Skip updating variable
                                 * fieldsCaptured.
                                 */
                            }
                            else
                            {
                                /* Update fieldsCaptured indicating ODD
                                 *  field is captured.
                                 */
                                pathObj->fieldsCaptured |=
                                    VPSCORE_DSSWB_ODD_FIELD_CAPTURED;
                            }
                        }
                        if ((irqStatus & 0x2U) == 0x2U)
                        {
                            /* VSync Event happened. In case of interlaced
                             * display, this event happens at the end of even
                             * field. Update the status in wb path object. It is
                             * used to give the callback to app in WB sync
                             * interrupt. */
                            if (DctrlCoreInfo.VidInfo[i].state ==
                                    VPS_DCTRL_PIPE_STARTED)
                            {
                                /* This is the first VSync after DSS Core has
                                * started the pipe. Update pipe status.
                                */
                                DctrlCoreInfo.VidInfo[i].state =
                                    VPS_DCTRL_PIPE_RUNNING;
                            }

                            pathObj->currentFieldVal = FVID2_FID_BOTTOM;
                            if (pathObj->pipeDisableStatus !=
                                VPSCORE_DSSWB_PIPE_RUNNING)
                            {
                                if (pathObj->pipeDisableStatus ==
                                    VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_3)
                                {
                                    /* This frame should be non RB writeback.
                                     * If this vsync is delayed and WB Sync
                                     * Event has happened, current frame would
                                     * be RB writeback. */
                                     VpsHal_dssWbPipeSetRegionBased(
                                        pathObj->pipeHandle, (UInt32) 0);
                                     VpsCore_DctrlSetGO(
                                        GRAPH_DCTRL_DSS_LCD1_BLENDER);
                                     pathObj->pipeDisableStatus =
                                        VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_2;
                                }
                                else if (pathObj->pipeDisableStatus ==
                                         VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_2)
                                {
                                    /* This frame will definately be non RB
                                     * writeback. Initiate stop in the next
                                     * vsync. */
                                     VpsHal_dssWbPipeSetRegionBased(
                                        pathObj->pipeHandle, (UInt32) 0);
                                     VpsCore_DctrlSetGO(
                                        GRAPH_DCTRL_DSS_LCD1_BLENDER);
                                     pathObj->pipeDisableStatus =
                                        VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_1;
                                }
                                else if (pathObj->pipeDisableStatus ==
                                         VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_1)
                                {
                                    /* Initiate the stop in this vsync. */
                                    VpsHal_dssVidPipeEnable(pathObj->pipeHandle,
                                        (UInt32) FALSE);
                                    pathObj->pipeDisableStatus =
                                        VPSCORE_DSSWB_PIPE_DISABLE_INITIATED;
                                }
                                else if (pathObj->pipeDisableStatus ==
                                         VPSCORE_DSSWB_PIPE_DISABLE_INITIATED)
                                {
                                    /* Pipe disable is done.
                                     * Unblock the stop call */
                                    pathObj->pipeDisableStatus =
                                        VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE;
                                    pathObj->fieldsCaptured =
                                        VPSCORE_DSSWB_CAPTURE_NOT_STARTED;
                                    BspOsal_semPost(pathObj->pipeDisableSem);
                                }
                            }
                        }
                        if (((irqStatus & 0x100000000U) == 0x100000000U) &&
                            (pathObj->pipeDisableStatus ==
                                VPSCORE_DSSWB_PIPE_RUNNING))
                        {
                            /* WB SYNC IRQ */
                            DctrlCoreInfo.wbDebugInfo.wbSyncIrq++;
                            if (pathObj->wbPipeCfg.cropEnable == TRUE)
                            {
                                if ((irqStatus & 0x200000000U) == 0x200000000U)
                                {
                                    /* If WB END WINDOW INTERRUPT is also set
                                     *corner case ISR delayed */
                                    /* Reset WB_REGION BASED BIT */
                                    DctrlCoreInfo.wbDebugInfo.wbSyncRbEndWinTog
                                    ++;
                                }
                                else if (pathObj->regionBasedBit == 1)
                                {
                                    /* Normal operation */
                                    /* Reset WB_REGION BASED BIT */
                                    DctrlCoreInfo.wbDebugInfo.wbSyncOnlyNormal
                                    ++;
                                }
                                else
                                {
                                    /* Enable region based bit for next frame */
                                    /* Set WB_REGION BASED BIT */
                                    DctrlCoreInfo.wbDebugInfo.
                                    wbSyncOnlyFrameSkip++;
                                }
                                /* Toggle RB bit */
                                if (pathObj->regionBasedBit == 1)
                                {
                                    pathObj->regionBasedBit = 0;
                                    VpsHal_dssWbPipeSetRegionBased(
                                        pathObj->pipeHandle, (UInt32) 0);
                                }
                                else
                                {
                                    pathObj->regionBasedBit = 1;
                                    VpsHal_dssWbPipeSetRegionBased(
                                        pathObj->pipeHandle, (UInt32) 1);
                                }
                                VpsCore_DctrlSetGO(GRAPH_DCTRL_DSS_LCD1_BLENDER);
                            }
                            else
                            {
                                /* For Interlaced display WB Sync event happens
                                 * for both fields. Check the currentField value
                                 * stored in pathObj.
                                 * If its FVID2_FID_TOP donot give callback,
                                 * else give the callback.
                                 *
                                 * For progressive display Wb Sync happens at
                                 * the end of frame. call back should be given
                                 * in every wb sync interrupt
                                 */
                            if (pathObj->fieldsCaptured ==
                                    VPSCORE_DSSWB_CAPTURE_NOT_STARTED)
                            {
                                /* This is the first Wb Sync after WB started.
                                 * Start the writeback from the next frame.
                                 */
                                pathObj->fieldsCaptured =
                                    VPSCORE_DSSWB_CAPTURE_STARTED;
                            }
                            else
                            {
                                /* Update fieldsCaptured indicating EVEN
                                 *  field is captured.
                                 */
                                pathObj->fieldsCaptured |=
                                    VPSCORE_DSSWB_EVEN_FIELD_CAPTURED;
                            }

                                if ((pathObj->outScanFormat ==
                                      FVID2_SF_INTERLACED) &&
                                    ((pathObj->currentFieldVal ==
                                        FVID2_FID_TOP) ||
                                     (pathObj->fieldsCaptured !=
                                        VPSCORE_DSSWB_BOTH_FIELDS_CAPTURED)))
                                {
                                    /* Donot give the app callback. Skip this
                                     *interrupt */
                                }
                                else
                                {
                                    /* If region based is not set call back
                                     *  to be called in Wb Sync Irq */
                                    GT_assert(VpsDctrlCoreTrace,
                                              (NULL !=
                                               DctrlCoreInfo.VidInfo[i].
                                               gClientInfo.cbFxn));
                                    DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                                        DctrlCoreInfo.VidInfo[i].gClientInfo.
                                        arg);
                                    pathObj->fieldsCaptured =
                                        VPSCORE_DSSWB_CAPTURE_STARTED;
                                }
                            }
                        }
                        else if (((irqStatus & 0x200000000U) == 0x200000000U) &&
                            (pathObj->pipeDisableStatus ==
                                VPSCORE_DSSWB_PIPE_RUNNING))
                        {
                            DctrlCoreInfo.wbDebugInfo.rbEndWinOnly++;
                            /* WB REGION BASED END WINDOW INTERRUPT */
                            if (pathObj->wbPipeCfg.cropEnable == TRUE)
                            {
                                /* Set WB_REGION BASED BIT */
                                pathObj->regionBasedBit = 1;
                                VpsHal_dssWbPipeSetRegionBased(
                                    pathObj->pipeHandle, (UInt32) 1);
                                if (pathObj->fieldsCaptured ==
                                        VPSCORE_DSSWB_CAPTURE_NOT_STARTED)
                                {
                                    /* This is the first WB RB Event after
                                     * WB pipe started. Start the writeback
                                     * from the next frame.
                                     */
                                    pathObj->fieldsCaptured =
                                        VPSCORE_DSSWB_CAPTURE_STARTED;
                                }
                                else
                                {
                                    /* Update fieldsCaptured indicating EVEN
                                     *  field is captured.
                                     */
                                    pathObj->fieldsCaptured |=
                                        VPSCORE_DSSWB_EVEN_FIELD_CAPTURED;
                                }
                                if ((pathObj->outScanFormat ==
                                      FVID2_SF_INTERLACED) &&
                                    ((pathObj->currentFieldVal ==
                                        FVID2_FID_TOP) ||
                                     (pathObj->fieldsCaptured !=
                                        VPSCORE_DSSWB_BOTH_FIELDS_CAPTURED)))
                                {
                                    /* Donot give the app callback. Skip this
                                     *interrupt */
                                }
                                else if((irqStatus & 0x2U) != 0x2U)
                                {
                                    /* If region based is set call back to be
                                     * called in RB End Wondow Irq. Also the
                                     * execution is between RB Event and VSync,
                                     * It is safe to program next buffer. */
                                    GT_assert(VpsDctrlCoreTrace,
                                              (NULL !=
                                               DctrlCoreInfo.VidInfo[i].
                                               gClientInfo.cbFxn));
                                    DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                                        DctrlCoreInfo.VidInfo[i].gClientInfo.
                                        arg);
                                    pathObj->fieldsCaptured =
                                        VPSCORE_DSSWB_CAPTURE_STARTED;
                                }
                                else
                                {
                                    /* Nothing to be done here */
                                }
                            }
                        }
                        else
                        {
                            /* Nothing to be done here */
                        }
                    }
#endif
                    break;

                case GRAPH_DCTRL_DSS_LCD2_BLENDER:
                    if ((irqStatus & 0x00040000U) == 0x00040000U)
                    {
                        if (DctrlCoreInfo.VidInfo[i].state ==
                                VPS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first VSync after DSS Core has
                             * started the pipe. Update pipe status.
                             */
                            DctrlCoreInfo.VidInfo[i].state =
                                VPS_DCTRL_PIPE_RUNNING;
                        }

                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum ==
                                GRAPH_DCTRL_DSS_WB)
                        {
                            VpsCore_DssWbPathObj *pathObj = NULL;
                            pathObj =
                                (VpsCore_DssWbPathObj *) (DctrlCoreInfo.VidInfo
                                                        [i].
                                                        gClientInfo.arg);
                            if (pathObj->pipeDisableStatus ==
                                 VPSCORE_DSSWB_PIPE_DISABLE_INITIATED)
                            {
                                /* Pipe disable is done.
                                * Unblock the stop call */
                                pathObj->pipeDisableStatus =
                                    VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE;
                                BspOsal_semPost(pathObj->pipeDisableSem);
                            }
                        }
                    }
                    break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case GRAPH_DCTRL_DSS_LCD3_BLENDER:
                    if ((irqStatus & 0x10000000U) == 0x10000000U)
                    {
                        if (DctrlCoreInfo.VidInfo[i].state ==
                                VPS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first VSync after DSS Core has
                             * started the pipe. Update pipe status.
                             */
                            DctrlCoreInfo.VidInfo[i].state =
                                VPS_DCTRL_PIPE_RUNNING;
                        }

                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum ==
                                GRAPH_DCTRL_DSS_WB)
                        {
                            VpsCore_DssWbPathObj *pathObj = NULL;
                            pathObj =
                                (VpsCore_DssWbPathObj *) (DctrlCoreInfo.VidInfo
                                                        [i].
                                                        gClientInfo.arg);
                            if (pathObj->pipeDisableStatus ==
                                 VPSCORE_DSSWB_PIPE_DISABLE_INITIATED)
                            {
                                /* Pipe disable is done.
                                * Unblock the stop call */
                                pathObj->pipeDisableStatus =
                                    VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE;
                                BspOsal_semPost(pathObj->pipeDisableSem);
                            }
                        }
                    }
                    break;

                case GRAPH_DCTRL_DSS_HDMI_BLENDER:
                    if ((irqStatus & 0x4U) == 0x4U)
                    {
                        if (DctrlCoreInfo.VidInfo[i].state ==
                                VPS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first VSync after DSS Core has
                             * started the pipe. Update pipe status.
                             */
                            DctrlCoreInfo.VidInfo[i].state =
                                VPS_DCTRL_PIPE_RUNNING;
                        }

                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum ==
                                GRAPH_DCTRL_DSS_WB)
                        {
                            VpsCore_DssWbPathObj *pathObj = NULL;
                            pathObj =
                                (VpsCore_DssWbPathObj *) (DctrlCoreInfo.VidInfo
                                                        [i].
                                                        gClientInfo.arg);
                            if (pathObj->pipeDisableStatus ==
                                 VPSCORE_DSSWB_PIPE_DISABLE_INITIATED)
                            {
                                /* Pipe disable is done.
                                * Unblock the stop call */
                                pathObj->pipeDisableStatus =
                                    VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE;
                                BspOsal_semPost(pathObj->pipeDisableSem);
                            }
                        }
                    }
                    break;
#endif
                /* Give callback only in case of m2m WB mode */
                case GRAPH_DCTRL_DSS_WB:
                    if (((irqStatus & 0x800000U) == 0x800000U) &&
                        (DctrlCoreInfo.VidInfo[i].gClientInfo.clientMode ==
                         VPS_DSS_DISPC_WB_M2M))
                    {
                        GT_assert(VpsDctrlCoreTrace,
                                  (NULL !=
                                   DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn));
                        DctrlCoreInfo.VidInfo[i].gClientInfo.cbFxn(
                            DctrlCoreInfo.VidInfo[i].gClientInfo.arg);
                    }
                    break;
                default:
                    break;
            }
            if (DctrlCoreInfo.VidInfo[i].state == VPS_DCTRL_PIPE_RUNNING)
            {
                /* Count the errors after first VSync after the DSS Core starts
                 * the pipe. In Case of SD Venc few initial sync lost errors are
                 * expected after the pipe enable and before the first VSync.
                 * So skip counting error interrupts when pipe state is started
                 * and before running.
                 */
                Vpscore_dctlrUpdateErrorCount(irqStatus);
            }
        }
    }

    return;
}

Int32 Vpscore_dctlrUpdateErrorCount(UInt64 irqStatus)
{
    DctrlCoreInfo.errorCnt.gfxBufferUnderflow +=
        ((irqStatus & 0x00000040U) >> 6U);
    DctrlCoreInfo.errorCnt.wbBufferOverflow +=
        ((irqStatus & 0x02000000U) >> 25U);
    DctrlCoreInfo.errorCnt.wbIncompleteError +=
        ((irqStatus & 0x04000000U) >> 26U);
    DctrlCoreInfo.errorCnt.vid1BufferUnderflow +=
        ((irqStatus & 0x00000400U) >> 10U);
    DctrlCoreInfo.errorCnt.vid2BufferUnderflow +=
        ((irqStatus & 0x00001000U) >> 12U);
    DctrlCoreInfo.errorCnt.vid3BufferUnderflow +=
        ((irqStatus & 0x00100000U) >> 20U);
    DctrlCoreInfo.errorCnt.syncLost1 +=
        ((irqStatus & 0x00004000U) >> 14U);
    DctrlCoreInfo.errorCnt.syncLost2 +=
        ((irqStatus & 0x00020000U) >> 17U);
    DctrlCoreInfo.errorCnt.syncLost3 +=
        ((irqStatus & 0x08000000U) >> 27U);
    DctrlCoreInfo.errorCnt.syncLostTV +=
        ((irqStatus & 0x00008000U) >> 15U);
    DctrlCoreInfo.errorCnt.ocpError += ((irqStatus & 0x00000200U) >> 9U);

    return BSP_SOK;
}

/**
 *  Vpscore_dctrlReadytoSetGoBit
 *  \brief All update of registers is done and its ready to set the go bit
 *
 *
 *  The Dss core has updated all the vid/gfx pipeline registers and its ready
 *  to set the go bit. Once all the pipelines connected to a particular Overlay
 *  manager are done with updating pipeline registes, display controller will
 *  will set the go bit of overlay manager
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return                Returns 0 on success else returns error value
 */

Int32 Vpscore_dctrlReadyToSetGoBit(VpscoreDctrlClientHandle handle)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;

    VpsCore_DctrlSetGO(VidInfo->ovlNodeNum);

    return retVal;
}

/**
 *  Vpscore_dctrlRegisterClient
 *  \brief Function to register a client to display controller
 *
 *  This function registers the client callbacks with the display controller.
 *
 *  The client can be either present in the same core where master DC resides
 *  or it can reside in some other core. This is differentiated by the
 *  callback parameter value.
 *
 *  \param nodeNum      Input Node Number for which this client is to be
 *                      registered
 *  \param clientInfo   Pointer to client info structure containing client
 *                      information
 *  \param arg          Not used currently. For the future use
 *
 *  \return             Handle to the client if registered successfully
 *                      NULL if not able to register
 */
VpscoreDctrlClientHandle Vpscore_dctrlRegisterClient(
    VpscoreDctrl_NodeNum nodeNum,
    const Vpscore_dctrlClientInfo *
    clientInfo,
    Ptr                  arg)
{
    VpscoreDctrlClientHandle dcHandle;

    dcHandle = VpsCore_DctrlOpenPipe(nodeNum, clientInfo);

    return dcHandle;
}

/**
 *  Vpscore_dctrlUnRegisterClient
 *  \brief Unregisters the clients from display controller.
 *
 *  This function inregisters the display controller client and
 *  de-allocates client objects.
 *  If client is started, it cannot be unregistered. It returns error in
 *  this case
 *  Vpscore_dctrlRegisterClient should be called prior to this call.
 *  Client is freed.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlUnRegisterClient(VpscoreDctrlClientHandle handle)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;

    VidInfo->gClientInfo.cbFxn = NULL;
    VidInfo->gClientInfo.arg   = NULL;
    VidInfo->state = VPS_DCTRL_PIPE_IDLE;
    return retVal;
}

/**
 *  Vpscore_dctrlStartClient
 *  \brief
 *
 *
 *  The state for the client changes to started.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlStartClient(VpscoreDctrlClientHandle handle)
{
    Int32  retVal = BSP_SOK;
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;
    UInt32 ovlyId, pipeId;

    ovlyId = VpsCore_convertGraphIdtoOvlyIndex(VidInfo->ovlNodeNum);

    retVal = VpsHal_dssOvlyEnableIntr(ovlyId, (UInt32) 0x1U);

    pipeId = VpsCore_convertGraphIdtoPipeIndex(VidInfo->pipeNodeNum);

    retVal = VpsHal_dssEnablePipeIntr(pipeId, (UInt32) 0x1U);

    VpsCore_DctrlSetGO(VidInfo->ovlNodeNum);

    if (retVal == BSP_SOK)
    {
        VidInfo->state = VPS_DCTRL_PIPE_STARTED;
    }

    return retVal;
}

/**
 *  Vpscore_dctrlStopClient
 *  \brief
 *
 *
 *  The state for the client changes to started.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlStopClient(VpscoreDctrlClientHandle handle)

{
    Int32  retVal = BSP_SOK;
    UInt32 ovlyId, pipeId;
    UInt32 interruptDisable = TRUE;
    UInt32 pipeNum          = 0;

    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;

    ovlyId = VpsCore_convertGraphIdtoOvlyIndex(VidInfo->ovlNodeNum);
    pipeId = VpsCore_convertGraphIdtoPipeIndex(VidInfo->pipeNodeNum);

    /* Disable interrupts for current pipe and change state to opened. */
    VpsHal_dssEnablePipeIntr(pipeId, (UInt32) 0x0U);
    VidInfo->state = VPS_DCTRL_PIPE_OPENED;

    GT_assert(VpsDctrlCoreTrace,
                (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
    for (pipeNum = 0; pipeNum < DctrlCoreInfo.numPipes; pipeNum++)
    {
        if (((DctrlCoreInfo.VidInfo[pipeNum].state == VPS_DCTRL_PIPE_RUNNING) ||
             (DctrlCoreInfo.VidInfo[pipeNum].state == VPS_DCTRL_PIPE_STARTED)) &&
            (DctrlCoreInfo.VidInfo[pipeNum].ovlNodeNum == VidInfo->ovlNodeNum))
        {
            interruptDisable = (UInt32) FALSE;
            break;
        }
    }

    if (TRUE == interruptDisable)
    {
        /* If No pipes connected to current overlay are running,
         * disable overlay interrupts. */
        retVal = VpsHal_dssOvlyEnableIntr(ovlyId, 0x0);
    }

    return retVal;
}

/**
 *  Vpscore_dctrlGetPathInfo
 *  \brief Function to get the path information.
 *
 *  Input client driver needs to know the size of the frame and frame mode
 *  by which it should pump input frame data. This function returns the
 *  size of the frame and frame mode to the client at the input node.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *  \param pathInfo   Pointer to path information structure returned by
 *                             display controller
 *
 *  \return           Returns 0 on success else returns error value
 */
/* Change this Client Handle to node information */
Int32 Vpscore_dctrlGetPathInfo(VpscoreDctrlClientHandle handle,
                               Vpscore_dctrlPathInfo   *pathInfo)
{
    Int32  retVal = BSP_SOK;
    UInt32 i      = 0;
    UInt32 j      = 0;
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;

    for (i = 0; i < DctrlCoreInfo.numVencs; i++)
    {
        if (VidInfo->vencId == DctrlCoreInfo.pathInfo[i].vencId)
        {
            pathInfo->isVencRunning = DctrlCoreInfo.pathInfo[i].isVencRunning;
            pathInfo->scanFormat    = DctrlCoreInfo.pathInfo[i].scanFormat;
            pathInfo->standard      = DctrlCoreInfo.pathInfo[i].standard;
            pathInfo->width         = DctrlCoreInfo.pathInfo[i].width;
            pathInfo->height        = DctrlCoreInfo.pathInfo[i].height;
            pathInfo->vencId        = DctrlCoreInfo.pathInfo[i].vencId;

            break;
        }
    }

    GT_assert(VpsDctrlCoreTrace,
                (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
    for (j = 0; j < DctrlCoreInfo.numPipes; j++)
    {
        if (VidInfo->pipeNodeNum == DctrlCoreInfo.VidInfo[j].pipeNodeNum)
        {
            pathInfo->shiftVidPosX = DctrlCoreInfo.VidInfo[j].shiftVidPosX;
        }
    }

    if (i == DctrlCoreInfo.numVencs)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

/**
 *  Vpscore_dctrlIsSafeToPush
 *  \brief check if it is safe to program the Buffer.Its safe
 *         to program before the line number interrupt and after the vsync
 *         interrupt. This is required for low latency display.
 *         This call should be gaurded by the disabling the interrupt.The same
 *         variable is modified in the interrupt.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *
 *  \return                Returns TRUE if its safe else FALSE
 */
UInt32 Vpscore_dctrlIsSafeToPush(VpscoreDctrlClientHandle handle)
{
    UInt32 retVal = FALSE;
    void  *VidInfoTmp;
    VpsCore_DctrlPipe *VidInfo;
    UInt32 ovlyId;

    VidInfoTmp = (void *) handle;
    VidInfo    = (VpsCore_DctrlPipe *) VidInfoTmp;
    GT_assert(VpsDctrlCoreTrace, (NULL != handle));

    ovlyId = VpsCore_convertGraphIdtoOvlyIndex(VidInfo->ovlNodeNum);

    if (ovlyId == VPSHAL_DSS_DISPC_LCD1)
    {
        retVal = DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD1];
    }
    else
    {
        retVal = (UInt32) FALSE;
    }

    return retVal;
}

/**
 *  Vpscore_dctrlGetCurLineNumber
 *  \brief Get the current Line Number of the corresponding LCD
 *
 *
 *  This is to Check if its safe to program the buffer in DSS registers.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *  \param lineNumber  Pointer to lineNumber Variable.
 *
 *  \return                Returns 0 on success else returns error value
 */

Int32 Vpscore_dctrlGetCurLineNumber(VpscoreDctrlClientHandle handle,
                                    UInt32                  *lineNumber)
{
    Int32  retVal = BSP_SOK;
    VpsCore_DctrlPipe *VidInfo = (VpsCore_DctrlPipe *) handle;
    UInt32 ovlyId;

    GT_assert(VpsDctrlCoreTrace, (NULL != handle));

    ovlyId = VpsCore_convertGraphIdtoOvlyIndex(VidInfo->ovlNodeNum);
    retVal = VpsHal_dssOvlyGetLineNum(ovlyId, lineNumber);

    return retVal;
}

Int32 VpsLcdConfCopy(VpsHal_DssDispcLcdTimingParam *lcdConf,
                     const Vps_DctrlConfig         *dctrlCfg,
                     UInt32                         vencId)
{
    UInt32 i      = 0;
    Int32  retVal = BSP_EFAIL;
    UInt32 ovlyId;

    for (i = 0; i < dctrlCfg->vencInfo.numVencs; i++)
    {
        if (dctrlCfg->vencInfo.modeInfo[i].vencId == vencId)
        {
            lcdConf->standard = dctrlCfg->vencInfo.modeInfo[i].mInfo.standard;
            if (lcdConf->standard == FVID2_STD_CUSTOM)
            {
                lcdConf->width =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.width;
                lcdConf->height =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.height;
                if (dctrlCfg->vencInfo.modeInfo[i].mInfo.scanFormat ==
                    FVID2_SF_INTERLACED)
                {
                    lcdConf->height = lcdConf->height / 2U;
                }
                lcdConf->scanFormat =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.scanFormat;
                lcdConf->hFrontPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hFrontPorch;
                lcdConf->hBackPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hBackPorch;
                lcdConf->hSyncLen =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hSyncLen;
                lcdConf->vFrontPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vFrontPorch;
                lcdConf->vBackPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vBackPorch;
                lcdConf->vSyncLen =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vSyncLen;
            }

            ovlyId = VpsCore_convertVencIdtoOvlyIndex(vencId);

            if (ovlyId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
            {
                if ((DctrlCoreInfo.dvoFmt[ovlyId] ==
                     VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
                    && (lcdConf->standard == FVID2_STD_NTSC))
                {
                    lcdConf->width       = 720U;
                    lcdConf->height      = 240U;
                    lcdConf->scanFormat  = FVID2_SF_INTERLACED;
                    lcdConf->hFrontPorch = 2U;
                    lcdConf->hBackPorch  = 16U;
                    lcdConf->hSyncLen    = 15U;
                    lcdConf->vFrontPorch = 2U;
                    lcdConf->vBackPorch  = 17U;
                    lcdConf->vSyncLen    = 2U;
                    /* Moving it back to CUSTOM so that HAL will program
                     * it directly.*/
                    lcdConf->standard = FVID2_STD_CUSTOM;
                }

                if ((DctrlCoreInfo.dvoFmt[ovlyId] ==
                     VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
                    && (lcdConf->standard == FVID2_STD_PAL))
                {
                    lcdConf->width       = 720U;
                    lcdConf->height      = 288U;
                    lcdConf->scanFormat  = FVID2_SF_INTERLACED;
                    lcdConf->hFrontPorch = 2U;
                    lcdConf->hBackPorch  = 22U;
                    lcdConf->hSyncLen    = 24U;
                    lcdConf->vFrontPorch = 2U;
                    lcdConf->vBackPorch  = 23U;
                    lcdConf->vSyncLen    = 2U;
                    lcdConf->standard    = FVID2_STD_CUSTOM;
                }

                if ((DctrlCoreInfo.dvoFmt[ovlyId] ==
                     VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
                    && (lcdConf->standard == FVID2_STD_1080I_60))
                {
                    lcdConf->width       = 1920U;
                    lcdConf->height      = 540U;
                    lcdConf->scanFormat  = FVID2_SF_INTERLACED;
                    lcdConf->hFrontPorch = 3U;
                    lcdConf->hBackPorch  = 20U;
                    lcdConf->hSyncLen    = 16U;
                    lcdConf->vFrontPorch = 2U;
                    lcdConf->vBackPorch  = 20U;
                    lcdConf->vSyncLen    = 2U;
                    lcdConf->standard    = FVID2_STD_CUSTOM;
                }
            }

            retVal = BSP_SOK;
            break;
        }
    }
    return retVal;
}

Int32 VpsConvGraphNodetoOvlMgrHandle(UInt32 nodeInfo)
{
    Int32 retval;

    switch (nodeInfo)
    {
        case GRAPH_DCTRL_DSS_LCD1_BLENDER:
            retval = 0;
            break;
        case GRAPH_DCTRL_DSS_LCD2_BLENDER:
            retval = 1;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        case GRAPH_DCTRL_DSS_LCD3_BLENDER:
            retval = 2;
            break;
        case GRAPH_DCTRL_DSS_HDMI_BLENDER:
            retval = 3;
            break;
#endif
        default:
            retval = BSP_EBADARGS;
            break;
    }
    return retval;
}

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
static Int32 VpsHdmiConfCopy(VpsHal_DssHdmiTimingParam *hdmiConf,
                             const Vps_DctrlConfig     *dctrlCfg,
                             UInt32                     vencId)
{
    UInt32 i      = 0;
    Int32  retVal = BSP_SOK;

    for (i = 0; i < dctrlCfg->vencInfo.numVencs; i++)
    {
        if (dctrlCfg->vencInfo.modeInfo[i].vencId == vencId)
        {
            if (dctrlCfg->vencInfo.modeInfo[i].mInfo.standard ==
                FVID2_STD_CUSTOM)
            {
                hdmiConf->width  = dctrlCfg->vencInfo.modeInfo[i].mInfo.width;
                hdmiConf->height = dctrlCfg->vencInfo.modeInfo[i].mInfo.height;
                if (dctrlCfg->vencInfo.modeInfo[i].mInfo.scanFormat ==
                    FVID2_SF_INTERLACED)
                {
                    hdmiConf->height = hdmiConf->height / 2U;
                }
                if (dctrlCfg->vencInfo.modeInfo[i].mInfo.scanFormat ==
                    FVID2_SF_PROGRESSIVE)
                {
                    hdmiConf->scanFormat = 0;
                }
                else
                {
                    hdmiConf->scanFormat = 1;
                }
                hdmiConf->hFrontPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hFrontPorch;
                hdmiConf->hBackPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hBackPorch;
                hdmiConf->hSyncLen =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.hSyncLen;
                hdmiConf->vFrontPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vFrontPorch;
                hdmiConf->vBackPorch =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vBackPorch;
                hdmiConf->vSyncLen =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.vSyncLen;
                hdmiConf->pixel_clock =
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.pixelClock;
                hdmiConf->mode =
                    dctrlCfg->vencInfo.modeInfo[i].mode;
            }
            else
            {
                retVal = VpsHal_hdmiGetTiming(
                    dctrlCfg->vencInfo.modeInfo[i].mInfo.standard,
                    hdmiConf);
            }
            hdmiConf->outputRange = dctrlCfg->vencInfo.modeInfo[i].outputRange;

            break;
        }
    }

    if (i >= dctrlCfg->vencInfo.numVencs)
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

static Int32 vpscore_dctrlHdmiPowerOn(const VpsHal_DssHdmiTimingParam *hdmiCfg)
{
    Int32 retVal = BSP_SOK, tempRetVal = BSP_SOK;

    VpsHal_DssHdmiPllInfo pllInfo;

    vpshal_HdmiComputePll(hdmiCfg->pixel_clock, &pllInfo);

    vpshal_HdmiWpVideoStart(0);

    /* config the PLL and PHY hdmi_set_pll_pwrfirst */
    retVal = vpshal_HdmiPllEnable(&pllInfo);
    if (retVal != BSP_SOK)
    {
        GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Failed to lock PLL\r\n");
    }

    tempRetVal = vpshal_HdmiPhyPowerOn(hdmiCfg);

    if (tempRetVal != BSP_SOK)
    {
        GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Failed to start PHY\r\n");
        /* retVal += tempRetVal; */
        /* Masking the powerOn ret val status for SDK */
    }

    VpsHal_hdmiBasicConfigure(hdmiCfg);

    /* bypass TV gamma table */
    VpsHal_dssOvlyEnableTvGamma(
        0);

    /*set  tv size */
    retVal += Vpshal_dssOvlySetTvRes(hdmiCfg->height, hdmiCfg->width);

    vpshal_HdmiWpVideoStart((UInt32) 1U);

    return retVal;
}

static void vpscore_dctrlHdmiPowerOff(void)
{
    vpshal_HdmiWpVideoStart(0);

    vpshal_HdmiPhyEnable(0);

    vpshal_HdmiPllDisable();
}

#endif

void Vpscore_DctrlsetParallelSelect(const VpsCore_DctrlObj *pDctrlInstObj)
{
    Vgraph_edgeInfo *curEdge;
    UInt32           i, ovlyId;

    for (i = 0; i < pDctrlInstObj->dctrlEdgeList.numEdges; i++)
    {
        curEdge = &pDctrlInstObj->dctrlEdgeList.list[i];
        ovlyId  = VpsCore_convertGraphIdtoOvlyIndex(curEdge->startNode);
        switch (curEdge->startNode)
        {
            case GRAPH_DCTRL_DSS_LCD1_BLENDER:
            case GRAPH_DCTRL_DSS_LCD2_BLENDER:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
            case GRAPH_DCTRL_DSS_LCD3_BLENDER:
            case GRAPH_DCTRL_DSS_HDMI_BLENDER:
#endif
                if (curEdge->endNode == GRAPH_DCTRL_DSS_DPI1_OUTPUT)
                {
                    /* Mux Select - To select appropriate source */
                    VpsHal_dssOvlySetParallelMux(ovlyId);
                }
                break;

            default:
                break;
        }
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_010)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-809) DOX_REQ_TAG(PDK-810)
 */
Int32 VpsCore_dctrlControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           Ptr            appArgs,
                           Ptr            drvArgs)
{
    Int32  retVal = BSP_SOK, handleId =
        BSP_EBADARGS;
    UInt32 i = 0;
    UInt32 ovlyIdx, dispcMode;
    UInt32 confOvly, confPipe;
    VpsCore_DctrlObj *pDctrlInstObj =
        (VpsCore_DctrlObj *) drvArgs;
    Vps_DctrlConfig  *dctrlCfg;
    Vps_DssDispcOvlyPanelConfig          *panelCfg;
    Vgraph_nodeInfo                      *curNode;
    Vgraph_edgeInfo                      *curEdge;
    VpsHal_DssDispcLcdTimingParam lcdConf;
    Vps_DssDispcOvlyPipeConfig           *pipeconfig;
    Vps_DctrlOutputInfo                  *vencInfo;
    Vps_DssDispcLcdAdvDisplayConfig AdvLcdConfig;
    Vps_DctrlVencDivisorInfo             *vencDivisors;
    VpsHal_DssDispcLcdDivisorParam lcdDivisors;
    VpsHal_DssDispcLcdSignalPolarityParam lcdSigPolarity;
    VpsHal_DssDispcLcdOutputParam lcdOutParms;
    Vps_DssDispcLcdAdvDisplayConfig      *advLcdDispConfig;
    Vps_DssDispcLcdAdvSignalConfig       *advLcdSignalConfig;
    Vps_DssDispcAdvLcdTdmConfig          *lcdTdmconfig;
    Vps_DctrlErrorSyncLostStats               *errStats;
    Vps_DctrlVencBlankTiming             *vencBlankTiming;
    VpsHal_DssDispcLcdBlankTimingParam   halLcdBlankTiming;
    Vps_DssVencCprCoeff                  *vencCprCoeff;
    VpsHal_DssDispcCprCoeff              cprCoeff;
    Vps_DssDispcMflagConfigParam         *mflagParam;
    UInt32                               cookie;
#if defined (SOC_TDA3XX)
    Vps_DctrlSDVencVideoStandard               *standard;
    Vps_DssDispcSdVencAdvConfig    *dispcSdVencConfig;
    UInt32 sdEnable;
#endif

    GT_assert(VpsDssCoreTrace, (NULL != appArgs));

    /* IOCTLs supported by the Global handle for DCTRL core */
    switch (cmd)
    {
        case IOCTL_VPSCORE_DCTRL_SET_CONFIG:
        {
            /* For Non SD-VENC Displays, Need to enable DPI output and
             * DISPC should be in Master mode. Applicable only for Tda3xx */
            retVal   += VpsHal_dssOvlyDpiEnable((UInt32) TRUE);
            dispcMode = VPS_DCTRL_DISPC_MODE_MASTER;
            retVal   += VpsHal_dssOvlySetDispcMode(dispcMode);

            dctrlCfg = (Vps_DctrlConfig *) appArgs;
            if (dctrlCfg->numEdges != 0)
            {
                retVal = VpsCore_dctrlCreateEdgeList(
                    pDctrlInstObj,
                    (Vps_DctrlConfig *)
                    appArgs);
                VpsCore_DctrlSetInfo(pDctrlInstObj);
                Vpscore_DctrlsetParallelSelect(pDctrlInstObj);
            }

            if ((BSP_SOK == retVal) && (dctrlCfg->vencInfo.numVencs != 0))
            {
                /* To select frame data or palette */
                retVal += VpsHal_dssOvlySetLoadMode((UInt32) 0x2);
                for (i = 0; i < dctrlCfg->vencInfo.numVencs; i++)
                {
                    switch (dctrlCfg->vencInfo.modeInfo[i].vencId)
                    {
                        case VPS_DCTRL_DSS_VENC_LCD1:
                            DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD1] =
                                (UInt32) FALSE;
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD1);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[0],
                                    &lcdConf);
                                if (lcdConf.height > 5)
                                {
                                    retVal += VpsHal_dssOvlyLcdConfLineNum(
                                        pDctrlInstObj->ovlHandle[0],
                                        (lcdConf.height - (UInt32) 5));
                                }
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));
                                AdvLcdConfig.stnTft = 1;
                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[0], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[0], (UInt32) 1U);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) TRUE;
                            VpsCore_DctrlSetPathInfo(
                                &dctrlCfg->vencInfo.modeInfo[i],
                                VPS_DCTRL_DSS_VENC_LCD1,
                                GRAPH_DCTRL_DSS_DPI1_OUTPUT);
                            break;

                        case VPS_DCTRL_DSS_VENC_LCD2:
                            DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD2] =
                                (UInt32) FALSE;
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD2);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[1],
                                    &lcdConf);
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));
                                AdvLcdConfig.stnTft = 1;
                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[1], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[1], (UInt32) 1U);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) TRUE;
                            VpsCore_DctrlSetPathInfo(
                                &dctrlCfg->vencInfo.modeInfo[i],
                                VPS_DCTRL_DSS_VENC_LCD2,
                                GRAPH_DCTRL_DSS_DPI1_OUTPUT);
                            break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                        case VPS_DCTRL_DSS_VENC_LCD3:
                            DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_LCD3] =
                                (UInt32) FALSE;
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD3);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[2],
                                    &lcdConf);
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));
                                AdvLcdConfig.stnTft = 1;
                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[2], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[2], (UInt32) 1U);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) TRUE;
                            VpsCore_DctrlSetPathInfo(
                                &dctrlCfg->vencInfo.modeInfo[i],
                                VPS_DCTRL_DSS_VENC_LCD3,
                                GRAPH_DCTRL_DSS_DPI1_OUTPUT);
                            break;

                        case VPS_DCTRL_DSS_VENC_HDMI:
                        {
                            DctrlCoreInfo.isPushSafe[VPSHAL_DSS_DISPC_HDMI] =
                                (UInt32) FALSE;
                            VpsHal_DssHdmiTimingParam hdmiConf;
                            retVal = VpsHdmiConfCopy(&hdmiConf, dctrlCfg,
                                                     VPS_DCTRL_DSS_VENC_HDMI);
                            hdmiConf.mode = 1;
                            if (retVal == BSP_SOK)
                            {
                                retVal += vpscore_dctrlHdmiPowerOn(&hdmiConf);
                            }
                            retVal += VpsHal_dssOvlyEnable(
                                pDctrlInstObj->ovlHandle[3], (UInt32) 1U);
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) TRUE;
                            VpsCore_DctrlSetPathInfo(
                                &dctrlCfg->vencInfo.modeInfo[i],
                                VPS_DCTRL_DSS_VENC_HDMI,
                                GRAPH_DCTRL_DSS_HDMI_OUTPUT);
                        }
                        break;
#endif
                        default:
                            break;
                    }
                }
            }
        }
        break;
        case IOCTL_VPSCORE_DCTRL_CLEAR_CONFIG:
        {
            dctrlCfg = (Vps_DctrlConfig *) appArgs;

            for (i = 0; i < dctrlCfg->vencInfo.numVencs; i++)
            {
                if (dctrlCfg->vencInfo.modeInfo[i].isVencRunning == TRUE)
                {
                    switch (dctrlCfg->vencInfo.modeInfo[i].vencId)
                    {
                        case VPS_DCTRL_DSS_VENC_LCD1:
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD1);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[0],
                                    &lcdConf);
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));
                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[0], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[0], 0);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) FALSE;
                            break;

                        case VPS_DCTRL_DSS_VENC_LCD2:
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD2);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[1],
                                    &lcdConf);
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));

                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[1], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[1], 0);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) FALSE;
                            break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                        case VPS_DCTRL_DSS_VENC_LCD3:
                            retVal = VpsLcdConfCopy(
                                &lcdConf, dctrlCfg,
                                VPS_DCTRL_DSS_VENC_LCD3);
                            if (retVal == BSP_SOK)
                            {
                                retVal += VpsHal_dssOvlyLcdSetTiming(
                                    pDctrlInstObj->ovlHandle[2],
                                    &lcdConf);
                                BspUtils_memset(&AdvLcdConfig, 0,
                                                sizeof (AdvLcdConfig));
                                retVal += VpsHal_dssOvlyLcdAdvDispConfig(
                                    pDctrlInstObj->ovlHandle[2], &AdvLcdConfig);
                                retVal += VpsHal_dssOvlyEnable(
                                    pDctrlInstObj->ovlHandle[2], 0);
                            }
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) FALSE;
                            break;

                        case VPS_DCTRL_DSS_VENC_HDMI:
                            vpscore_dctrlHdmiPowerOff();
                            dctrlCfg->vencInfo.modeInfo[i].isVencRunning =
                                (UInt32) FALSE;
                            retVal += VpsHal_dssOvlyEnable(
                                pDctrlInstObj->ovlHandle[3], 0);
                            break;
#endif
                        default:
                            break;
                    }
                }
            }
            if (dctrlCfg->numEdges != 0)
            {
                VpsCore_dctrlFreeEdgeList(pDctrlInstObj);
            }
            VpsCore_DctrlResetInfo(pDctrlInstObj);
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_OVLY_PARAMS:
        {
            panelCfg = (Vps_DssDispcOvlyPanelConfig *) appArgs;

            confOvly = (UInt32) FALSE;

            while ((i < pDctrlInstObj->dctrlNodeList.numNodes) &&
                   (confOvly == (UInt32) FALSE))
            {
                curNode = &pDctrlInstObj->dctrlNodeList.list[i];

                switch (curNode->nodeType)
                {
                    case VGRAPH_NODETYPE_DSSMGR:
                    {
                        switch (curNode->nodeNum)
                        {
                            case GRAPH_DCTRL_DSS_LCD1_BLENDER:
                                if (panelCfg->vencId == VPS_DCTRL_DSS_VENC_LCD1)
                                {
                                    confOvly = (UInt32) TRUE;
                                }
                                break;

                            case GRAPH_DCTRL_DSS_LCD2_BLENDER:
                                if (panelCfg->vencId == VPS_DCTRL_DSS_VENC_LCD2)
                                {
                                    confOvly = (UInt32) TRUE;
                                }

                                break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                            case GRAPH_DCTRL_DSS_LCD3_BLENDER:
                                if (panelCfg->vencId == VPS_DCTRL_DSS_VENC_LCD3)
                                {
                                    confOvly = (UInt32) TRUE;
                                }

                                break;

                            case GRAPH_DCTRL_DSS_HDMI_BLENDER:
                                if (panelCfg->vencId == VPS_DCTRL_DSS_VENC_HDMI)
                                {
                                    confOvly = (UInt32) TRUE;
                                }
                                break;
#endif

                            default:
                                break;
                        }
                    }
                    break;
                    default:
                        break;
                }
                i++;
            }
            if (TRUE == confOvly)
            {
                ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(panelCfg->vencId);
                if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
                {
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                    retVal += BSP_EBADARGS;
                }
                if (BSP_SOK == retVal)
                {
                    retVal += VpsHal_dssOvlyPanelConf(
                        pDctrlInstObj->ovlHandle[ovlyIdx],
                        panelCfg);
                }
            }
            else
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal += BSP_EBADARGS;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_PIPELINE_PARAMS:
        {
            pipeconfig = (Vps_DssDispcOvlyPipeConfig *) appArgs;
            confPipe   = (UInt32) FALSE;

            for (i = 0;
                 ((i < pDctrlInstObj->dctrlEdgeList.numEdges) &&
                  (confPipe == FALSE));
                 i++)
            {
                curEdge = &pDctrlInstObj->dctrlEdgeList.list[i];

                switch (curEdge->startNode)
                {
                    case GRAPH_DCTRL_DSS_VID1:
                        if (pipeconfig->pipeLine == VPS_DSS_DISPC_PIPE_VID1)
                        {
                            confPipe = (UInt32) TRUE;
                        }
                        break;
                    case GRAPH_DCTRL_DSS_VID2:
                        if (pipeconfig->pipeLine == VPS_DSS_DISPC_PIPE_VID2)
                        {
                            confPipe = (UInt32) TRUE;
                        }
                        break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                    case GRAPH_DCTRL_DSS_VID3:
                        if (pipeconfig->pipeLine == VPS_DSS_DISPC_PIPE_VID3)
                        {
                            confPipe = (UInt32) TRUE;
                        }
                        break;
#endif
                    case GRAPH_DCTRL_DSS_GFX:
                        if (pipeconfig->pipeLine == VPS_DSS_DISPC_PIPE_GFX1)
                        {
                            confPipe = (UInt32) TRUE;
                        }
                        break;
                    default:
                        break;
                }
            }
            if (TRUE == confPipe)
            {
                handleId = VpsConvGraphNodetoOvlMgrHandle(
                    curEdge->endNode);

                if (BSP_EBADARGS != handleId)
                {
                    retVal += VpsHal_dssOvlyPipeConfig(
                        pDctrlInstObj->ovlHandle[handleId],
                        pipeconfig);
                }
                else
                {
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc \r\n");
                    retVal += BSP_EBADARGS;
                }
            }
            else
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Pipe/Venc \r\n");
                retVal += BSP_EBADARGS;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT:
        {
            vencInfo = (Vps_DctrlOutputInfo *) appArgs;
            switch (vencInfo->vencId)
            {
                case VPS_DCTRL_DSS_VENC_LCD1:
                case VPS_DCTRL_DSS_VENC_LCD2:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case VPS_DCTRL_DSS_VENC_LCD3:
#endif
                    lcdSigPolarity.hsPolarity       = vencInfo->hsPolarity;
                    lcdSigPolarity.vsPolarity       = vencInfo->vsPolarity;
                    lcdSigPolarity.pixelClkPolarity =
                        vencInfo->pixelClkPolarity;
                    lcdSigPolarity.dvoActVidPolarity =
                        vencInfo->actVidPolarity;
                    lcdOutParms.dvoFormat = vencInfo->dvoFormat;

                    if (vencInfo->videoIfWidth == FVID2_VIFW_12BIT)
                    {
                        lcdOutParms.videoIfWidth = 0;
                    }
                    else if (vencInfo->videoIfWidth == FVID2_VIFW_16BIT)
                    {
                        lcdOutParms.videoIfWidth = 1;
                    }
                    else if (vencInfo->videoIfWidth == FVID2_VIFW_18BIT)
                    {
                        lcdOutParms.videoIfWidth = 2;
                    }
                    else if (vencInfo->videoIfWidth == FVID2_VIFW_24BIT)
                    {
                        lcdOutParms.videoIfWidth = 3;
                    }
                    else
                    {
                        retVal = BSP_EINVALID_PARAMS;
                    }

                    if (retVal == BSP_SOK)
                    {
                        ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                            vencInfo->vencId);
                        if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
                        {
                            GT_0trace(VpsDctrlCoreTrace, GT_ERR,
                                      "Unsupported Venc\r\n");
                            retVal = BSP_EBADARGS;
                        }
                        if (retVal == BSP_SOK)
                        {
                            retVal += VpsHal_dssOvlyLcdSignalPolarityConf(
                                pDctrlInstObj->ovlHandle[
                                    ovlyIdx],
                                &lcdSigPolarity);

                            retVal += VpsHal_dssOvlyLcdOutputConf(
                                pDctrlInstObj->ovlHandle[
                                    ovlyIdx],
                                &lcdOutParms);
                        }
                        if (retVal == BSP_SOK)
                        {
                            DctrlCoreInfo.dvoFmt[ovlyIdx] = vencInfo->dvoFormat;
                        }
                    }
                    break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case VPS_DCTRL_DSS_VENC_HDMI:
                {
                    VpsHal_DssHdmiOutputInfo hdmiInfo;

                    hdmiInfo.dataFormat = vencInfo->dataFormat;
                    hdmiInfo.hsPolarity = vencInfo->hsPolarity;
                    hdmiInfo.vsPolarity = vencInfo->vsPolarity;
                    VpsHal_hdmiVencOuptputConfig(&hdmiInfo);
                }
                break;
#endif
                default:
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported VENC\r\n");
                    retVal = BSP_EBADARGS;
                    break;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_VENC_PCLK_DIVISORS:
        {
            vencDivisors = (Vps_DctrlVencDivisorInfo *) appArgs;

            lcdDivisors.divisorLCD = vencDivisors->divisorLCD;
            lcdDivisors.divisorPCD = vencDivisors->divisorPCD;

            switch (vencDivisors->vencId)
            {
                case VPS_DCTRL_DSS_VENC_LCD1:
                case VPS_DCTRL_DSS_VENC_LCD2:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case VPS_DCTRL_DSS_VENC_LCD3:
#endif
                    ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                        vencDivisors->vencId);
                    if (retVal == BSP_SOK)
                    {
                        retVal = VpsHal_dssOvlyLcdSetClkDivisors(
                            pDctrlInstObj->ovlHandle[ovlyIdx],
                            &lcdDivisors);
                    }
                    break;
                default:
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                    retVal = BSP_EBADARGS;
                    break;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_TDM_PARAMS:
        {
            lcdTdmconfig = (Vps_DssDispcAdvLcdTdmConfig *) appArgs;
            ovlyIdx      = VpsCore_convertVencIdtoOvlyIndex(
                lcdTdmconfig->vencId);

            if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal = BSP_EBADARGS;
            }
            if (retVal == BSP_SOK)
            {
                retVal = VpsHal_dssOvlyLcdTdmConfig(
                    pDctrlInstObj->ovlHandle[ovlyIdx],
                    lcdTdmconfig);
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_DISP_PARAMS:
        {
            advLcdDispConfig = (Vps_DssDispcLcdAdvDisplayConfig *) appArgs;

            ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(advLcdDispConfig->vencId);
            if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal = BSP_EBADARGS;
            }
            if (retVal == BSP_SOK)
            {
                retVal = VpsHal_dssOvlyLcdAdvDispConfig(
                    pDctrlInstObj->ovlHandle[ovlyIdx],
                    advLcdDispConfig);
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_ADV_VENC_SIGNAL_PARAMS:
        {
            advLcdSignalConfig = (Vps_DssDispcLcdAdvSignalConfig *) appArgs;

            ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                advLcdSignalConfig->vencId);
            if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal = BSP_EBADARGS;
            }
            if (retVal == BSP_SOK)
            {
                retVal = VpsHal_dssOvlyLcdAdvSignalConf(
                    pDctrlInstObj->ovlHandle[ovlyIdx],
                    advLcdSignalConfig);
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_GET_ERROR_STATS:
        {
            errStats = (Vps_DctrlErrorSyncLostStats *) appArgs;

            errStats->syncLost1  = DctrlCoreInfo.errorCnt.syncLost1;
            errStats->syncLost2  = DctrlCoreInfo.errorCnt.syncLost2;
            errStats->syncLost3  = DctrlCoreInfo.errorCnt.syncLost3;
            errStats->syncLostTV = DctrlCoreInfo.errorCnt.syncLostTV;
            errStats->ocpError   = DctrlCoreInfo.errorCnt.ocpError;
        }
        break;
#if defined (SOC_TDA3XX)
        case IOCTL_VPSCORE_DCTRL_SET_SDVENC_MODE:
        {
            standard = (Vps_DctrlSDVencVideoStandard *) appArgs;
            retVal   = VpsHal_dssSdVencConfigure(standard->videoStandard);
        }
        break;

        case IOCTL_VPSCORE_DCTRL_GET_DEF_SDVENC_ADV_CONFIG:
        {
            dispcSdVencConfig = (Vps_DssDispcSdVencAdvConfig *) appArgs;
            retVal = VpsHal_dssGetDefAdvSdVencParams(dispcSdVencConfig);
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_SDVENC_ADV_CONFIG:
        {
            dispcSdVencConfig = (Vps_DssDispcSdVencAdvConfig *) appArgs;
            retVal = VpsHal_dssSetAdvSdVencParams(dispcSdVencConfig);
        }
        break;

        case IOCTL_VPSCORE_DCTRL_ENABLE_SDVENC:
        {
            sdEnable = *(UInt32 *) appArgs;
            if (TRUE == sdEnable)
            {
                retVal = VpsHal_dssSdVencInit();
                /* For SDVENC display DPI output should be disabled*/
                retVal   += VpsHal_dssOvlyDpiEnable((UInt32) FALSE);
                dispcMode = VPS_DCTRL_DISPC_MODE_SLAVE;
                retVal   += VpsHal_dssOvlySetDispcMode(dispcMode);
                /* fwd pipe position in overlay should be shifted by 2 pixels
                 * for sd venc display in tda3xx (errata: i873) */
                GT_assert(VpsDctrlCoreTrace,
                    (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
                for (i = 0; i < DctrlCoreInfo.numPipes; i++)
                {
                    if (DctrlCoreInfo.VidInfo[i].pipeNodeNum !=
                        VPSCORE_DCTRL_NODE_WB)
                    {
                        if (DctrlCoreInfo.VidInfo[i].vencId ==
                            VPS_DCTRL_DSS_VENC_LCD1)
                        {
                            /* Only lcd1 o/p can be connected to sd venc */
                            DctrlCoreInfo.VidInfo[i].shiftVidPosX = 2;
                        }
                    }
                }
                /* Update panel size. Increase PPL by 2 for LCD1 overlay.
                 * Only this can be connected to sd venc. */
                VpsHal_dssOvlyUpdatePanelSizeSdVenc(pDctrlInstObj->ovlHandle[0]);
            }
            else if (FALSE == sdEnable)
            {
                retVal    = VpsHal_dssSdVencDeInit();
                retVal   += VpsHal_dssOvlyDpiEnable((UInt32) TRUE);
                dispcMode = VPS_DCTRL_DISPC_MODE_MASTER;
                retVal   += VpsHal_dssOvlySetDispcMode(dispcMode);
                GT_assert(VpsDctrlCoreTrace,
                    (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
                for (i = 0; i < DctrlCoreInfo.numPipes; i++)
                {
                    if (DctrlCoreInfo.VidInfo[i].pipeNodeNum !=
                        VPSCORE_DCTRL_NODE_WB)
                    {
                        if (DctrlCoreInfo.VidInfo[i].vencId ==
                            VPS_DCTRL_DSS_VENC_LCD1)
                        {
                            /* Only lcd1 o/p can be connected to sd venc */
                            DctrlCoreInfo.VidInfo[i].shiftVidPosX = 0;
                        }
                    }
                }
            }
            else
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Bad Arguments \r\n");
                retVal = BSP_EBADARGS;
            }
        }
        break;
#endif
        case IOCTL_VPSCORE_DCTRL_GET_VENC_BLANK_TIMING:
        {
            vencBlankTiming = (Vps_DctrlVencBlankTiming *) appArgs;
            ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                vencBlankTiming->vencId);
            if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal = BSP_EBADARGS;
            }
            if (retVal == BSP_SOK)
            {
                retVal += VpsHal_dssOvlyLcdGetBlankTiming(
                    pDctrlInstObj->ovlHandle[ovlyIdx],
                    &halLcdBlankTiming);
            }
            if (retVal == BSP_SOK)
            {
                vencBlankTiming->hFrontPorch = halLcdBlankTiming.hFrontPorch;
                vencBlankTiming->hBackPorch  = halLcdBlankTiming.hBackPorch;
                vencBlankTiming->hSyncLen    = halLcdBlankTiming.hSyncLen;
                vencBlankTiming->vFrontPorch = halLcdBlankTiming.vFrontPorch;
                vencBlankTiming->vBackPorch  = halLcdBlankTiming.vBackPorch;
                vencBlankTiming->vSyncLen    = halLcdBlankTiming.vSyncLen;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_VENC_BLANK_TIMING:
        {
            vencBlankTiming = (Vps_DctrlVencBlankTiming *) appArgs;

            halLcdBlankTiming.hFrontPorch = vencBlankTiming->hFrontPorch;
            halLcdBlankTiming.hBackPorch  = vencBlankTiming->hBackPorch;
            halLcdBlankTiming.hSyncLen    = vencBlankTiming->hSyncLen;
            halLcdBlankTiming.vFrontPorch = vencBlankTiming->vFrontPorch;
            halLcdBlankTiming.vBackPorch  = vencBlankTiming->vBackPorch;
            halLcdBlankTiming.vSyncLen    = vencBlankTiming->vSyncLen;

            ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                vencBlankTiming->vencId);
            if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
            {
                GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                retVal = BSP_EBADARGS;
            }
            if (retVal == BSP_SOK)
            {
                cookie = BspOsal_disableInterrupt();
                retVal += VpsHal_dssOvlyLcdSetBlankTiming(
                    pDctrlInstObj->ovlHandle[ovlyIdx],
                    &halLcdBlankTiming);
                VpsHal_dssOvlySetGoBit(ovlyIdx);
                BspOsal_restoreInterrupt(cookie);
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_SET_CPR_COEFF:
        {
            vencCprCoeff = (Vps_DssVencCprCoeff *) appArgs;

            switch (vencCprCoeff->vencId)
            {
                case VPS_DCTRL_DSS_VENC_LCD1:
                case VPS_DCTRL_DSS_VENC_LCD2:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case VPS_DCTRL_DSS_VENC_LCD3:
#endif
                    ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                        vencCprCoeff->vencId);
                    if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
                    {
                        GT_0trace(VpsDctrlCoreTrace, GT_ERR,
                                  "Unsupported Venc\r\n");
                        retVal = BSP_EBADARGS;
                    }

                    if (retVal == BSP_SOK)
                    {
                        cprCoeff.enableCpr  = vencCprCoeff->enableCpr;
                        cprCoeff.enableCsc  = vencCprCoeff->enableCsc;
                        cprCoeff.rr  = vencCprCoeff->rr;
                        cprCoeff.rg  = vencCprCoeff->rg;
                        cprCoeff.rb  = vencCprCoeff->rb;
                        cprCoeff.gr  = vencCprCoeff->gr;
                        cprCoeff.gg  = vencCprCoeff->gg;
                        cprCoeff.gb  = vencCprCoeff->gb;
                        cprCoeff.br  = vencCprCoeff->br;
                        cprCoeff.bg  = vencCprCoeff->bg;
                        cprCoeff.bb  = vencCprCoeff->bb;
                        retVal = VpsHal_dssOvlySetCprCoeff(
                            pDctrlInstObj->ovlHandle[ovlyIdx],
                            &cprCoeff);
                    }
                    break;
                default:
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                    retVal = BSP_EBADARGS;
                    break;
            }
        }
        break;

        case IOCTL_VPSCORE_DCTRL_GET_CPR_COEFF:
        {
            vencCprCoeff = (Vps_DssVencCprCoeff *) appArgs;

            switch (vencCprCoeff->vencId)
            {
                case VPS_DCTRL_DSS_VENC_LCD1:
                case VPS_DCTRL_DSS_VENC_LCD2:
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
                case VPS_DCTRL_DSS_VENC_LCD3:
#endif
                    ovlyIdx = VpsCore_convertVencIdtoOvlyIndex(
                        vencCprCoeff->vencId);
                    if (ovlyIdx >= VPSHAL_DSS_DISPC_OVLY_MAX_INST)
                    {
                        GT_0trace(VpsDctrlCoreTrace, GT_ERR,
                                  "Unsupported Venc\r\n");
                        retVal = BSP_EBADARGS;
                    }

                    if (retVal == BSP_SOK)
                    {
                        retVal = VpsHal_dssOvlyGetCprCoeff(
                            pDctrlInstObj->ovlHandle[ovlyIdx],
                            &cprCoeff);
                    }
                    if (retVal == BSP_SOK)
                    {
                        vencCprCoeff->enableCpr = cprCoeff.enableCpr;
                        vencCprCoeff->enableCsc = cprCoeff.enableCsc;
                        vencCprCoeff->rr  = cprCoeff.rr;
                        vencCprCoeff->rg  = cprCoeff.rg;
                        vencCprCoeff->rb  = cprCoeff.rb;
                        vencCprCoeff->gr  = cprCoeff.gr;
                        vencCprCoeff->gg  = cprCoeff.gg;
                        vencCprCoeff->gb  = cprCoeff.gb;
                        vencCprCoeff->br  = cprCoeff.br;
                        vencCprCoeff->bg  = cprCoeff.bg;
                        vencCprCoeff->bb  = cprCoeff.bb;
                    }
                    break;
                default:
                    GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported Venc\r\n");
                    retVal = BSP_EBADARGS;
                    break;
            }
        }
        break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        case IOCTL_VPSCORE_DCTRL_HDMI_FLIP_DATA_P_N_ORDER:
        {
            vpshal_HdmiFlipDataPnOrder();
        }
        break;
#endif

        case IOCTL_VPSCORE_DCTRL_SET_MFLAG_PARAM:
        {
            VpsHal_DssDispcMflagConfigParam halMflagParam;
            mflagParam = (Vps_DssDispcMflagConfigParam *) appArgs;

            halMflagParam.globalMflagStart = mflagParam->globalMflagStart;
            halMflagParam.globalMflagCtrl = mflagParam->globalMflagCtrl;
            halMflagParam.gfxMflagHighThreshold = mflagParam->gfxMflagHighThreshold;
            halMflagParam.gfxMflagLowThreshold = mflagParam->gfxMflagLowThreshold;
            halMflagParam.vid1MflagHighThreshold = mflagParam->vid1MflagHighThreshold;
            halMflagParam.vid1MflagLowThreshold = mflagParam->vid1MflagLowThreshold;
            halMflagParam.vid2MflagHighThreshold = mflagParam->vid2MflagHighThreshold;
            halMflagParam.vid2MflagLowThreshold = mflagParam->vid2MflagLowThreshold;
            halMflagParam.vid3MflagHighThreshold = mflagParam->vid3MflagHighThreshold;
            halMflagParam.vid3MflagLowThreshold = mflagParam->vid3MflagLowThreshold;
            halMflagParam.wbMflagHighThreshold = mflagParam->wbMflagHighThreshold;
            halMflagParam.wbMflagLowThreshold = mflagParam->wbMflagLowThreshold;

            VpsHal_dssOvlySetMflagConfig(&halMflagParam);
        }
        break;
        case IOCTL_VPSCORE_DCTRL_GET_MFLAG_PARAM:
        {
            VpsHal_DssDispcMflagConfigParam halMflagParam;
            mflagParam = (Vps_DssDispcMflagConfigParam *) appArgs;

            VpsHal_dssOvlyGetMflagConfig(&halMflagParam);

            mflagParam->globalMflagStart = halMflagParam.globalMflagStart;
            mflagParam->globalMflagCtrl = halMflagParam.globalMflagCtrl;
            mflagParam->gfxMflagHighThreshold = halMflagParam.gfxMflagHighThreshold;
            mflagParam->gfxMflagLowThreshold = halMflagParam.gfxMflagLowThreshold;
            mflagParam->vid1MflagHighThreshold = halMflagParam.vid1MflagHighThreshold;
            mflagParam->vid1MflagLowThreshold = halMflagParam.vid1MflagLowThreshold;
            mflagParam->vid2MflagHighThreshold = halMflagParam.vid2MflagHighThreshold;
            mflagParam->vid2MflagLowThreshold = halMflagParam.vid2MflagLowThreshold;
            mflagParam->vid3MflagHighThreshold = halMflagParam.vid3MflagHighThreshold;
            mflagParam->vid3MflagLowThreshold = halMflagParam.vid3MflagLowThreshold;
            mflagParam->wbMflagHighThreshold = halMflagParam.wbMflagHighThreshold;
            mflagParam->wbMflagLowThreshold = halMflagParam.wbMflagLowThreshold;
        }
        break;
        default:
            GT_0trace(VpsDctrlCoreTrace, GT_ERR, "Unsupported IOCTL\r\n");
            retVal = BSP_EUNSUPPORTED_CMD;
            break;
    }

    return retVal;
}

static UInt32 VpsCore_convertVencIdtoOvlyIndex(UInt32 vencId)
{
    UInt32 ovlyIdx;

    if (vencId == VPS_DCTRL_DSS_VENC_LCD1)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD1;
    }
    else if (vencId == VPS_DCTRL_DSS_VENC_LCD2)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD2;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
    else if (vencId == VPS_DCTRL_DSS_VENC_LCD3)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD3;
    }
    else if (vencId == VPS_DCTRL_DSS_VENC_HDMI)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_HDMI;
    }
#endif
    else
    {
        ovlyIdx = VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX;
    }

    return ovlyIdx;
}

static UInt32 VpsCore_convertGraphIdtoOvlyIndex(UInt32 graphId)
{
    UInt32 ovlyIdx;

    if (graphId == GRAPH_DCTRL_DSS_LCD1_BLENDER)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD1;
    }
    else if (graphId == GRAPH_DCTRL_DSS_LCD2_BLENDER)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD2;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
    else if (graphId == GRAPH_DCTRL_DSS_LCD3_BLENDER)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_LCD3;
    }
    else if (graphId == GRAPH_DCTRL_DSS_HDMI_BLENDER)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_HDMI;
    }
#endif
    else if (graphId == GRAPH_DCTRL_DSS_WB)
    {
        ovlyIdx = VPSHAL_DSS_DISPC_WBOVR;
    }
    else
    {
        ovlyIdx = VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX;
    }

    return ovlyIdx;
}

static UInt32 VpsCore_convertGraphIdtoPipeIndex(UInt32 graphId)
{
    UInt32 pipeIdx;

    if (graphId == GRAPH_DCTRL_DSS_VID1)
    {
        pipeIdx = VPSHAL_DSS_DISPC_VID1;
    }
    else if (graphId == GRAPH_DCTRL_DSS_VID2)
    {
        pipeIdx = VPSHAL_DSS_DISPC_VID2;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
    else if (graphId == GRAPH_DCTRL_DSS_VID3)
    {
        pipeIdx = VPSHAL_DSS_DISPC_VID3;
    }
#endif
    else if (graphId == GRAPH_DCTRL_DSS_GFX)
    {
        pipeIdx = VPSHAL_DSS_DISPC_GFX;
    }
    else if (graphId == GRAPH_DCTRL_DSS_WB)
    {
        pipeIdx = VPSHAL_DSS_DISPC_WB1;
    }
    else
    {
        pipeIdx = VPSHAL_DSS_DISPC_VID_INST_ID_MAX;
    }

    return pipeIdx;
}

Int32 VpsCore_dctrlPipeUpdateOverlayNode(VpscoreDctrlClientHandle handle,
                                         UInt32                   ovlyNode)
{
    UInt32 i;

    GT_assert(VpsDctrlCoreTrace,
                (DctrlCoreInfo.numPipes <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
    for (i = 0; i < DctrlCoreInfo.numPipes; i++)
    {
        if (DctrlCoreInfo.VidInfo[i].pipeNodeNum == VPSCORE_DCTRL_NODE_WB)
        {
            /* Update Overlay Node only for WB pipe */
            DctrlCoreInfo.VidInfo[i].ovlNodeNum = ovlyNode;
        }
    }
    return BSP_SOK;
}
