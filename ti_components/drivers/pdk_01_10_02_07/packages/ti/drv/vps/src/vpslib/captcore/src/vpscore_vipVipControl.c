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
 *  \file vpscore_vipVipControl.c
 *
 *  \brief Core functions for controlling VIP HW
 *  This file calls the HAL APIs of the VPDMA, VIP Port and VIP Top.
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

#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#include <ti/drv/vps/src/vpslib/captcore/src/vpscore_vipPriv.h>
#include <ti/drv/vps/src/vpslib/common/vps_graph.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/captcore/src/vpscore_vipVipControl.h>

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

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 VpsCore_vipPostAbortList(VpsCore_VipPathObj *pathObj)
{
    Int32  retVal = BSP_SOK;
    UInt32 descAddr;
    UInt32 listSize = 0;
    UInt32 chId, strm, pl;

    GT_assert(VpsVipCoreTrace, (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        UInt32 numPlanes;
        descAddr = (UInt32) pathObj->descMem[chId];
        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            numPlanes = pathObj->numPlanes[strm];
            for (pl = 0; pl < numPlanes; pl++)
            {
                VpsHal_vpdmaCreateAbortCtrlDesc(
                    (UInt8 *) (descAddr),
                    pathObj->strm2VpdmaChanMap[chId][(strm *
                                                      FVID2_MAX_PLANES) + pl]);
                descAddr += VPSHAL_VPDMA_CTRL_DESC_SIZE;
            }
        }
        listSize = (descAddr - (UInt32) pathObj->descMem[chId]);
        /* TODO: Alloc separate memory for abort descriptors */
        /* VPS_CAPT_ABORT_DESC_MEM_SIZE */
        /* GT_assert(VpsVipCoreTrace, listSize < VPS_CAPT_ABORT_DESC_MEM_SIZE);
        **/

        VpsHal_vpdmaPostList(pathObj->vpdmaHandle,          /* handle      */
                             (UInt8) pathObj->listId[chId], /* listNum     */
                             VPSHAL_VPDMA_LT_NORMAL,        /* listType    */
                             &pathObj->descMem[chId][0U],   /* memPtr      */
                             listSize,                      /* listSize    */
                             0);                            /* enableCheck */

        /* TODO: Fix 3000 */
        retVal = VpsHal_vpdmaListWaitComplete(pathObj->vpdmaHandle,
                                              (UInt8) pathObj->listId[chId],
                                              (UInt32) 3000U);
    }

    return retVal;
}

Int32 VpsCore_vipResetFIFO(VpsCore_VipPathObj *pathObj, UInt32 enable)
{
    Int32           retVal = BSP_SOK;
    /* TODO: Only one port for now. Might need to stop other PORT as well. */
    VpsHal_vipPortResetFIFO(pathObj->vipPortHandle, enable);

    VpsCore_VipObj *pVipInstObj = (VpsCore_VipObj *) (pathObj->parent);
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipPortResetFIFO(pVipInstObj->s0PortAHandle, enable);
        VpsHal_vipPortResetFIFO(pVipInstObj->s0PortBHandle, enable);
    }
    else if (VPSHAL_VIP_S1 == pathObj->sliceId)
    {
        VpsHal_vipPortResetFIFO(pVipInstObj->s1PortAHandle, enable);
        VpsHal_vipPortResetFIFO(pVipInstObj->s1PortBHandle, enable);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

Int32 VpsCore_vipBlockReset(VpsCore_VipPathObj *pathObj)
{
    UInt32 delayMsec = 1U;
    Int32  retVal, chId;

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] VIP Reset Starting !!!\r\n",
              vipInstId);
    #endif

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Disabling Parser !!!\r\n",
              vipInstId);
    #endif

    /* disable VIP Parser - TODO: Need to add disable for all PORTS */
    VpsHal_vipPortEnable(pathObj->vipPortHandle, (UInt32) FALSE, 0);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Asserting Reset !!!\r\n",
              vipInstId);
    #endif

    /* Reset the whole VIP block */
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) TRUE, 0);
    }
    else
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) TRUE, 0);
    }

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Asserting Clear FIFO !!!\r\n",
              vipInstId);
    #endif

    /* Assert clear async FIFO reset */
    VpsCore_vipResetFIFO(pathObj, (UInt32) TRUE);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Posting Abort List !!!\r\n",
              vipInstId);
    #endif

    /* clear VIP overflow FIQ : TODO: Implement in HAL*/
    /* VpsHal_vipInstPortClearFIQ((VpsHal_VipInst)vipInstId); */

    /* post abort desc on all VIP VPDMA CHs */
    /* Stop the capture list before posting abort descriptors */
    GT_assert(VpsVipCoreTrace, (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        VpsHal_vpdmaStopList(pathObj->vpdmaHandle,
                             (UInt8) pathObj->listId[chId],
                             VPSHAL_VPDMA_LT_NORMAL);
    }

    /* Program Abort descriptors and wait for list to get completed */
    retVal = VpsCore_vipPostAbortList(pathObj);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] De-asserting Reset !!!\r\n",
              vipInstId);
    #endif

    /* Release the VIP block reset TODO: Add conditional reset to other slice */
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) FALSE, 0);
    }
    else
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) FALSE, 0);
    }

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG,
              " [VIP%d] De-asserting Clear FIFO !!!\r\n",
              vipInstId);
    #endif

    /* TODO: Release clear async FIFO reset To remove this and put after start
    **/
    VpsCore_vipResetFIFO(pathObj, (UInt32) FALSE);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] VIP Reset Done !!!\r\n",
              vipInstId);
    #endif

    return retVal;
}

void VpsCore_vipTopResetAllModules(VpsCore_VipPathObj *pathObj, UInt32 enable)
{
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* Individual module reset not supported */
    VpsCore_vipBlockReset(pathObj); /* Do full reset */
#else
    UInt32           i = 0;
    Vgraph_nodeInfo *curNode;
    while (i < pathObj->nodeList.numNodes)
    {
        curNode = &pathObj->nodeList.list[i];
        if (GRAPH_VIP_S0_CSC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CSC, enable, 0);
        }
        if (GRAPH_VIP_S1_CSC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CSC, enable, 0);
        }

        if (GRAPH_VIP_S0_SC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_SC, enable, 0);
        }
        if (GRAPH_VIP_S1_SC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_SC, enable, 0);
        }

        if (GRAPH_VIP_S0_CHRDS0 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CHRDS0, enable, 0);
        }
        if (GRAPH_VIP_S0_CHRDS1 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CHRDS1, enable, 0);
        }
        if (GRAPH_VIP_S1_CHRDS0 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CHRDS0, enable, 0);
        }
        if (GRAPH_VIP_S1_CHRDS1 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CHRDS1, enable, 0);
        }
        i++;
    }
#endif
}

VpsCore_Frame *VpsCore_vipGetCurrentCaptFrame(const VpsCore_VipPathObj *pathObj)
{
    VpsCore_Frame *curFrmptr;
    /* TODO: Add support for multi channel */
    if (pathObj->initialWait[0] != 0)
    {
        curFrmptr =
            pathObj->inputFrame[0][0][(pathObj->outFrmIdx[0]) % VIP_SW_Q_LEN];
    }
    else
    {
        curFrmptr =
            pathObj->inputFrame[0][0]
            [(pathObj->outFrmIdx[0] + 1U) % VIP_SW_Q_LEN];
    }
    return curFrmptr;
}

Int32 VpsCore_vipPortAndModulesReset(VpsCore_VipPathObj *pathObj)
{
    Int32  retVal    = 0;
    UInt32 delayMsec = 1U;
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* Stop not supported */
#else
    Int32  chId;
#endif

    /* Reset VIP Port */
    retVal = VpsHal_vipPortReset(pathObj->vipPortHandle, (UInt32) TRUE);

    /* Reset CSC, SC, core will ensure if CSC, SC is being used in the path,
     * it would reset otherwise skip resetting it */
    VpsCore_vipTopResetAllModules(pathObj, (UInt32) TRUE);

    BspOsal_sleep(delayMsec);

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* Stop not supported */
#else
    /* Stop the capture list before posting abort descriptors */
    GT_assert(VpsVipCoreTrace, (pathObj->numChannels < VPSCORE_VIP_CH_ID_MAX));
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        VpsHal_vpdmaStopList(pathObj->vpdmaHandle,
                             (UInt8) pathObj->listId[chId],
                             VPSHAL_VPDMA_LT_NORMAL);
    }

    /* Program Abort descriptors and wait for list to get completed */
    retVal += VpsCore_vipPostAbortList(pathObj);

    /* TODO: clear VIP async FIFO -
     * need to take from latest release after Brijesh update - 06 AUG 2012
     */
    /* TODO: / * clear VIP overflow FIQ * / */
    /* TODO: VpsHal_vipInstPortClearFIQ((VpsHal_VipInst)vipInstId); */

    BspOsal_sleep(delayMsec);

    /* Un-reset all modules */
    VpsCore_vipTopResetAllModules(pathObj, (UInt32) FALSE);

    /* Resetting the Muxes involved in the path */
    VpsCore_vipPathResetMuxes(pathObj);

#endif
    /* Clear VIP port: TODO - check if this is applicable to 814x */
    retVal += VpsHal_vipPortReset(pathObj->vipPortHandle, (UInt32) FALSE);

    return retVal;
}

