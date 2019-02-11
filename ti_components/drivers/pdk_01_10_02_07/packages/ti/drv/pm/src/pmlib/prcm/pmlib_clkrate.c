/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2017
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
 * \file        pmlib_clkrate.c
 *
 * \brief       PMLIB Clock Rate Manager API implementation.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pmlib_clkrate.h"
#include "pmhal_vm.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_clocktree.h"
#include "pmhal_prcm.h"
#include "pmlib_clk_rate_data_priv.h"
#include "pmlib_boardconfig.h"
#include "pmlib_videopll.h"
#include "pm_utils.h"

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

/**
 * \brief  Get the parent node and its type for a given module
 *
 * \param  nodeId                The Node ID for which the parent needs to be
 *                               found. Refer #pmhalPrcmModuleId_t enum for
 *                               details
 * \param  clkId                 Unique Id given for a clock
 *                               Refer #pmhalPrcmClockId_t enum for details
 *
 * \retval pmhalClockTreeNodeId  The Next Node ID or the parent node
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 */
static pmErrCode_t PmlibClkRateGetParentOfModule(pmhalClockTreeNodeId  nodeId,
                                                 pmhalPrcmClockId_t    clkId,
                                                 pmhalClockTreeNodeId *nxtNode);
/**
 * \brief  Get the parent node and its type for a given Multiplexer
 *
 * \param  nodeId                The Node ID of the Mux.
 *                               Refer #pmhalPrcmNodeId_t enum for details
 * \retval  nxtNode              The Next Node ID or the parent node
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 */
static pmErrCode_t PmlibClkRateGetParentOfMux(pmhalClockTreeNodeId  nodeId,
                                              pmhalClockTreeNodeId *nxtNode);

/**
 * \brief  Get the parent node and its type for a given Divider
 *
 * \param  nodeId                The Node ID of the Divider
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 * \retval  nxtNode              The Next Node ID or the parent node
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 */
static pmErrCode_t PmlibClkRateGetParentOfDiv(pmhalClockTreeNodeId  nodeId,
                                              pmhalClockTreeNodeId *nxtNode);

/**
 * \brief  Get the parent node and its type for a given Dpll
 *
 * \param  nodeId                The Node ID of the DPLL.
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 * \param  clkId                 Unique Id given for a clock
 *                               Refer #pmhalPrcmClockId_t enum for details
 *
 * \retval dpllFlag              Flag to check if DPLL has been found in path
 *
 * \retval  nxtNode              The Next Node ID or the parent node
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 */
static pmErrCode_t PmlibClkRateGetParentOfDpll(
    pmhalClockTreeNodeId  nodeId,
    pmhalPrcmDpllClkInput_t
    bypClkSel,
    pmhalClockTreeNodeId *nxtNode);

/**
 * \brief  Populate the DPLL properties
 *
 * \param  nodeId                The Node Id of the DPLL.
 *                               Refer #pmhalPrcmNodeId_t enum for details
 *
 * \param  edgePtr               Edge Property Structure for the DPLL
 *
 * \retval pmhalPrcmDpllConfig   Holds the Dpll properties
 *                               Refer #pmhalPrcmDpllConfig_t structure
 *
 */
static pmErrCode_t PmlibClkRatePopulateDpll(
    pmhalClockTreeNodeId       nodeId,
    pmhalClockTreeInputEdgePtr edgePtr,
    pmhalPrcmDpllConfig_t     *
    dpllConfig);

/**
 * \brief  Set Clkrate for the given Module which is a CPU
 *
 * \param  clkFreqConfig      Structure having details of node elements that
 *                            need to programmed to get the required clkrate
 *                            Refer #pmlibClockRateFreqConfig_t struct for
 *                            detail.
 *
 * \param  modId              moduleId whose clk Rate needs to be changed
 *
 * \param  clkRate            desired clkRate that is needed
 *
 * \retval pmErrCode_t        return PM_SUCCESS on successful execution.
 *                            refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRateCpuSet(pmlibClockRateFreqConfig_t clkFreqConfig,
                                      pmhalPrcmModuleId_t        modId,
                                      uint32_t                   clkRate);

/**
 * \brief  Set Clkrate for the given Module which is a not a CPU
 *
 * \param  clkFreqConfig      Structure having details of node elements that
 *                            need to programmed to get the required clkrate
 *                            Refer #pmlibClockRateFreqConfig_t struct for
 *                            detail
 *
 * \param  modID              moduleId whose clk Rate needs to be changed
 *
 * \retval pmErrCode_t        return PM_SUCCESS on successful execution.
 *                            refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRatePeripheralSet(
    pmhalPrcmModuleId_t modID,
    pmlibClockRateFreqConfig_t
    clkFreqConfig);

/**
 * \brief  Configure Clock Divider Node
 *
 * \param  muxSelList         Structure having details of all Div elements and
 *                            its value to be programmed.
 *                            Refer #pmlibClockRateDivConfig_t struct for detail
 *
 * \param  numMuxSel          Number of divider elements to be programmed
 *
 * \retval pmErrCode_t        return PM_SUCCESS on successful execution.
 *                            refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRateDividerConfigure(
    const pmlibClockRateDivConfig_t *divSelList,
    uint32_t                         numDivSel);

/**
 * \brief  Configure DPLL Node
 *
 * \param  dpllId             DPLL Id of the DPLL to be programmed.
 *                            refer #pmhalPrcmNodeId_t enum for details
 *
 * \param  dpllConfig         Structure having details of the Dpll values to be
 *                            programmed for the given DpllId
 *                            Refer #pmhalPrcmDpllConfig_t struct for detail
 *
 * \retval pmErrCode_t        return PM_SUCCESS on successful execution.
 *                            refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRateDpllConfigure(pmhalPrcmNodeId_t     dpllId,
                                             pmhalPrcmDpllConfig_t dpllConfig);

/**
 * \brief  Configure Clock Mux Node
 *
 * \param  muxSelList         Structure having details of all mux elements and
 *                            its value to be programmed.
 *                            Refer #pmlibClockRateMuxConfig_t struct for detail
 *
 * \param  numMuxSel          Number of mux elements to be programmed
 *
 * \retval pmErrCode_t        return PM_SUCCESS on successful execution.
 *                            refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRateMuxConfigure(
    const pmlibClockRateMuxConfig_t *muxSelList,
    uint32_t                         numMuxSel);

/**
 * \brief  change OPP for a given voltage Domain by checking if the given
 *         Voltage Domain is ganged with other VD's and change Opp based on
 *         state of other Voltage Domains.
 *
 * \param  newOpp       Opp to which the voltage domain needs to provide.
 *
 * \param  vdId         Voltage domain whose Opp needs to be changed
 *
 * \retval pmErrCode_t  Return PM_SUCCESS on successful execution.
 *                      refer #pmErrCode_t for more information.
 *
 */
static pmErrCode_t PmlibClkRateOppChangeForGangRails(pmhalVmOppId_t  newOpp,
                                                     pmhalPrcmVdId_t vdId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t *rootClkFreqArray;
static pmlibBoardVdRailShare_t *vdRailShareArray;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBClkRateInit(uint32_t                *rootClkFreqList,
                             pmlibBoardVdRailShare_t *vdRailShareList)
{
    pmErrCode_t retVal = PM_SUCCESS;
    if ((NULL == rootClkFreqList) || (NULL == vdRailShareList))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Store the pointer to the root clock frequency and the voltage rail
         * sharing information.
         */
        rootClkFreqArray = rootClkFreqList;
        vdRailShareArray = vdRailShareList;
    }
    return retVal;
}

pmErrCode_t PMLIBClkRateSet(pmhalPrcmModuleId_t modId,
                            pmhalPrcmClockId_t  clkId,
                            uint32_t            clkRate)
{
    pmErrCode_t                   retVal;
    pmhalPrcmClockActivityState_t clkState;
    pmlibClockRateFreqList_t     *freqList;
    uint32_t                      freqSuppSize;
    uint32_t                      idx = 0U;
    uint32_t                      currRate;
    pmlibClockRateFreqConfig_t    clkFreqConfig = {
        PMHAL_PRCM_NODE_UNDEF,
        NULL,
        NULL,
        0U,
        NULL,
        0U
    };
    pmhalPrcmCpuId_t              cpuId;
    uint32_t                      modIdArrayIndex;
    /* Get the current Rate */
    retVal = PMLIBClkRateGet(modId, clkId, &currRate);
    /* Check if given rate is same as current rate */
    if ((PM_SUCCESS == retVal) && (currRate == clkRate))
    {
        retVal = PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ;
    }
    if (PM_SUCCESS == retVal)
    {
        modIdArrayIndex = (uint32_t) PMUtilsGetModuleId(modId);
        /* Get the clock ID from the Generic clock Id List */
        if (clkId == PMHAL_PRCM_CLK_GENERIC)
        {
            if (modIdArrayIndex <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                clkId = gModuleGenericClkList[modIdArrayIndex];
            }
        }
        /* Check if clock ID is valid for a given module. Clock State is not
         * used further in the code */
        retVal = (pmErrCode_t) PMHALCMGetModuleClockStatus(modId, clkId,
                                                           &clkState);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Index clkId in pmlibClockRateAllClockFreq[] to get the freq list. */
        freqList     = pmlibClockRateAllClockFreq[clkId].clkFreqList;
        freqSuppSize = pmlibClockRateAllClockFreq[clkId].numFreqSupp;
        /* Loop through the list and search for the given clkRate
         * if clkRte is valid, get the pmlibClockRateFreqConfig_t structure
         */
        while (idx < freqSuppSize)
        {
            if (freqList[idx].suppFreq == clkRate)
            {
                clkFreqConfig = *(freqList[idx].freqConfig);
                break;
            }
            idx++;
        }
        /* if idx == freqSuppSize, ClkRate provided is not valid */
        if (idx == freqSuppSize)
        {
            retVal = PM_CLOCKRATE_FREQ_NOT_SUPPORTED;
        }
    }
    if (retVal == PM_SUCCESS)
    {
        cpuId = PMUtilsGetCpuId(modId);
        if (cpuId != PMHAL_PRCM_CPU_ID_UNDEF)
        {
            /* For CPUs the change of frequency can also lead to a change in
             * the value of the voltage rail.
             */
            retVal = PmlibClkRateCpuSet(clkFreqConfig, modId, clkRate);
        }
        else
        {
            /* Change the clock frequency for peripherals. Voltage would
             * not change for peripherals.
             */
            retVal = PmlibClkRatePeripheralSet(modId, clkFreqConfig);
        }
    }

    return retVal;
}

pmErrCode_t PMLIBClkRateGet(pmhalPrcmModuleId_t modId,
                            pmhalPrcmClockId_t  clkId,
                            uint32_t           *clkRate)
{
    pmErrCode_t                retVal       = PM_SUCCESS;
    pmhalClockTreeNodeId       nextNodeId   = modId;
    pmhalClockTreeNodeId       nodeId       = modId;
    pmhalNodeType_t            nodeType     = PMHAL_MOD;
    pmhalNodeType_t            nextNodeType = PMHAL_MOD;
    pmhalClockTreeInputEdgePtr edgePtr;
    uint32_t divVar = 1U;
    pmhalClockTreeNodeId       prevNodeId;
    uint8_t dpllFlag = 0;     /* Variable is 1U if a locked DPLL is found */
    uint32_t rootFreq;
    /* Array to store Divider factors for dividers before the DPLL */
    uint16_t preDpllDivideFactor[PMHAL_PRCM_DIV_COUNT - PMHAL_PRCM_DIV_MIN];
    /* Array to store Divider factors for dividers after the DPLL */
    uint16_t postDpllDivideFactor[PMHAL_PRCM_DIV_COUNT - PMHAL_PRCM_DIV_MIN];
    uint8_t preDivideFactorLength         = 0;
    uint8_t postDivideFactorLength        = 0;
    pmhalPrcmDpllConfig_t      dpllConfig = {0};
    pmhalPrcmPllPostDivValue_t postDivList;
    pmhalPrcmDpllClkInput_t    bypassClkSel;
    pmhalPrcmModuleId_t        moduleArrayIndex;
    pmhalPrcmNodeId_t          lockedDpllId = PMHAL_PRCM_DPLL_UNDEF;
    uint32_t factor = 1U;
    uint32_t lockStatus;
    uint8_t dccStatus;
    pmhalPrcmDpllType_t        dpllType;
    uint64_t dcoLdoClk;
    uint64_t fracDcoLdoClk;
    if (clkRate == NULL)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* If Generic CLock is requested, Get the generic clock as in
         * clock_rate_data.c
         */
        if (PMHAL_PRCM_CLK_GENERIC == clkId)
        {
            moduleArrayIndex = PMUtilsGetModuleId(modId);

            if (moduleArrayIndex <
                (PMHAL_PRCM_MOD_COUNT - PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
            {
                clkId = gModuleGenericClkList[moduleArrayIndex];
            }
        }

        /* Iterate until we hit a ROOT_CLK. This function uses the setting of
         * mux as programmed in the system
         */
        while ((nextNodeType != PMHAL_ROOT_CLK) &&
               (PM_SUCCESS == retVal) &&
               (nextNodeType != PMHAL_UNDEF))
        {
            prevNodeId = nodeId;
            nodeId     = nextNodeId;
            nodeType   = nextNodeType;
            /* 1) If module, get the edge property for the module, which
             * provides the node that is sourcing the provided clock to the
             * module.
             * 2) If no edge is found, then module has only one clock and we
             * get the sourced node by looking at the predecessor list of the
             * module.
             * 3) Get the next node from the above information and its type.
             */
            if (PMHAL_MOD == nodeType)
            {
                retVal = PmlibClkRateGetParentOfModule(nodeId,
                                                       clkId,
                                                       &nextNodeId);
            }
            /* If MUX, read the mux select register to the get the
             * selected node
             */
            if (PMHAL_MUX == nodeType)
            {
                retVal = PmlibClkRateGetParentOfMux(nodeId,
                                                    &nextNodeId);
            }
            /* 1) If divider, store the divide value programmed in the register.
             * 2) Get the next node connected to the divider by looking at the
             * predecessors.
             */
            if (PMHAL_DIV == nodeType)
            {
                retVal = (pmErrCode_t) PMHALCMDpllGetClockDivider(
                    (pmhalPrcmNodeId_t) nodeId,
                    &divVar);
                /* saving the divider factor in appropriate array based on
                 * whether the divider comes before a PLL is encountered
                 * (dpllFlag = 0) or after a locked PLL is encountered
                 * (dpllFlag = 1)
                 */
                if (PM_SUCCESS == retVal)
                {
                    retVal = PmlibClkRateGetParentOfDiv(nodeId, &nextNodeId);
                    if ((uint8_t) 0 == dpllFlag)
                    {
                        /* Fill all the divider values before hitting a DPLL,
                         * while traversing up the tree.
                         */
                        postDpllDivideFactor[postDivideFactorLength] =
                            (uint16_t) divVar;
                        postDivideFactorLength++;
                    }
                    else
                    {
                        /* Fill all the divider values after hitting a DPLL,
                         * while traversing up the tree.
                         */
                        preDpllDivideFactor[preDivideFactorLength] =
                            (uint16_t) divVar;
                        preDivideFactorLength++;
                    }
                }
            }
            /* 1) if DPLL, get the DPLL edge property which says the post
             * divider ID that is connected to the previous node.
             * 2) Get the postdiv value, M value and N value programmed in the
             * DPLL registers.
             * 3) Get the predecessor of the DPLL which is a root_clk. We
             * consider that only ROOT_CLK are connected to DPLL and
             * DPLL_HS_CLK and DPLL_LOW_CLK inputs are not considered.
             */
            if (PMHAL_DPLL == nodeType)
            {
                /* this flag is used to check if DPLL has been hit while
                 * when traversing the clocktree. This helps in saving relevant
                 * information of dividers that's before and after the dpll for
                 * proper calculation of output frequency.
                 */
                retVal = PMHALClockTreeGetDpllEdge(nodeId,
                                                   prevNodeId,
                                                   clkId,
                                                   &edgePtr);
                if (PM_SUCCESS == retVal)
                {
                    dpllConfig.postDivConfList = &postDivList;
                    dpllConfig.maxPostDivElems = 1U;
                    retVal = PmlibClkRatePopulateDpll(nodeId,
                                                      edgePtr,
                                                      &dpllConfig);
                }
                if (PM_SUCCESS == retVal)
                {
                    lockStatus = PMHALCMDpllLockStatus(
                        (pmhalPrcmNodeId_t) nodeId);
                }
                if ((uint8_t) 0 == dpllFlag)
                {
                    /* check whether theDPLL is in locked mode or in bypass
                     * mode. Based on this  information, dpllFlag will be set
                     * to 1 or 0
                     */
                    if (PM_SUCCESS == retVal)
                    {
                        if ((PMHAL_PRCM_DPLL_POST_DIV_M3 ==
                             (dpllConfig.postDivConfList)->postDivId))
                        {
                            /* Check for clock out HIF */
                            retVal =
                                (pmErrCode_t) PMHALCMDpllGetClkOutHIFSelect
                                    ((pmhalPrcmNodeId_t) nodeId,
                                    &bypassClkSel);
                            if (0U == lockStatus)
                            {
                                /* If the DPLL is in bypass and the clock
                                 * selection is the DCOLDO clock this is an
                                 * erroneous situation.
                                 */
                                if (PMHAL_PRCM_DPLL_INP_DCO == bypassClkSel)
                                {
                                    nextNodeId = PMHAL_PRCM_NODE_UNDEF;
                                }
                                else
                                {
                                    /* M3 divider comes after the multiplexer
                                     * for bypass clock selection.
                                     */
                                    postDpllDivideFactor[postDivideFactorLength
                                    ]
                                        = (dpllConfig.postDivConfList)->
                                          configValue;
                                    postDivideFactorLength++;
                                }
                            }
                            else
                            {
                                if (PMHAL_PRCM_DPLL_INP_DCO == bypassClkSel)
                                {
                                    bypassClkSel = PMHAL_PRCM_DPLL_INP_CLKINP;
                                    dpllFlag     = (uint8_t) 1;
                                    lockedDpllId = (pmhalPrcmNodeId_t) nodeId;
                                }
                                else
                                {
                                    postDpllDivideFactor[postDivideFactorLength
                                    ]
                                        = (dpllConfig.postDivConfList)->
                                          configValue;
                                    postDivideFactorLength++;
                                }
                            }
                        }
                        else if (1U == lockStatus)
                        {
                            /* Clock out/ HSDIV locked state */
                            bypassClkSel = PMHAL_PRCM_DPLL_INP_CLKINP;
                            dpllFlag     = (uint8_t) 1;
                            lockedDpllId = (pmhalPrcmNodeId_t) nodeId;
                        }
                        else
                        {
                            /* Clock out/HSDIV bypass state */
                            retVal =
                                (pmErrCode_t) PMHALCMDpllGetBypassClkSelect
                                    ((pmhalPrcmNodeId_t) nodeId,
                                    &bypassClkSel);
                        }
                    }
                    if (nextNodeId != PMHAL_PRCM_NODE_UNDEF)
                    {
                        if (PM_SUCCESS == retVal)
                        {
                            retVal = PmlibClkRateGetParentOfDpll(nodeId,
                                                                 bypassClkSel,
                                                                 &nextNodeId);
                        }
                    }
                } /* if ((uint8_t) 0 == dpllFlag) */
            }     /* if (PMHAL_DPLL == nodeType) */
            if (nextNodeId == PMHAL_PRCM_NODE_UNDEF)
            {
                nextNodeType = PMHAL_UNDEF;
            }
            else
            {
                nextNodeType = PMHALClockTreeGetNodeType(nextNodeId);
            }
        }  /* while ((nextNodeType != PMHAL_ROOT_CLK) &&
            *   (PM_SUCCESS == retVal) &&
            *   (nextNodeType != PMHAL_UNDEF))
            */
           /* Get the root clock frequency. This is got from board config file
            * or
            * by calling get frequency function of videoPLL if its a videoPLL
            * generated clock */
        if (PM_SUCCESS == retVal)
        {
            if (nextNodeType != PMHAL_UNDEF)
            {
                if (PMHAL_PRCM_ROOT_CLK_BOARD_MAX >= nextNodeId)
                {
                    rootFreq = rootClkFreqArray[nextNodeId];
                }
                #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || \
                defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
                else if ((PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN <= nextNodeId) &&
                         (PMHAL_PRCM_ROOT_CLK_MAX >= nextNodeId))
                {
                    /* Video PLL clocks from M7 post dividers are root clocks
                     * for PRCM get clock rate. Using the Video PLL lib to
                     * know what is the frequency for the Video PLL clocks.
                     */
                    PMLIBVideopllPrcmInCLkGetFreq(
                        (pmhalPrcmNodeId_t) nextNodeId,
                        &rootFreq);
                }
                #endif
                else
                {
                    retVal = PM_CLOCKRATE_ROOTCLK_NOT_SUPPORTED;
                }
            }
            else
            {
                /* For the erroneous case the returned clock is 0 */
                rootFreq = 0U;
                *clkRate = 0U;
            }
        }
        /* Calculate the clock rate of the clockID of the module by using the
         * Values got from the above tree traversal
         */
        if ((PM_SUCCESS == retVal) && (PMHAL_UNDEF != nextNodeType))
        {
            /* If a DPLL was hit during traversal */
            if ((uint8_t) 1 == dpllFlag)
            {
                uint64_t tempRate = 0U;
                PMHALCMDpllGetDpllType(lockedDpllId, &dpllType);
                PMHALCMDpllGetDutyCycleCorrector(lockedDpllId, &dccStatus);
                /* DCC is disabled the DCO LDO frequency is
                 * Fdpll = Fref × 2 × M / (N + 1)
                 * When DCC is enabled the clock frequency of DCO LDO is
                 * Fdpll = Fref× (M / (N + 1))
                 * Capturing the multiplication factor.
                 */
                if (((uint8_t) 1 == dccStatus) ||
                    (PMHAL_PRCM_DPLL_TYPE_ADPLLLJM == dpllType))
                {
                    factor = 1U;
                }
                else
                {
                    factor = 2U;
                }
                while (preDivideFactorLength != 0)
                {
                    rootFreq = rootFreq /
                               preDpllDivideFactor[preDivideFactorLength -
                                                   (uint8_t) 1];
                    preDivideFactorLength--;
                }
                /* Convert to uint64_t to make sure no truncation occurs
                 * during calculation.
                 */
                dcoLdoClk = ((uint64_t) factor *
                             (uint64_t) dpllConfig.multiplier *
                             (uint64_t) rootFreq) /
                            (uint64_t) ((uint64_t) dpllConfig.divider +
                                        (uint64_t) 1U);
                fracDcoLdoClk = ((((uint64_t) factor *
                                   (uint64_t) dpllConfig.fracMultiplier *
                                   (uint64_t) rootFreq)) >> (uint64_t) 18) /
                                (uint64_t) ((uint64_t) dpllConfig.divider +
                                            (uint64_t) 1U);
                dcoLdoClk = dcoLdoClk + fracDcoLdoClk;
                if (PMHAL_PRCM_DPLL_POST_DIV_M2 ==
                    (*(dpllConfig.postDivConfList)).postDivId)
                {
                    /* The [1/2] divider located after the M2 post-divider is
                     * not valid when the DCC_EN bit is set.
                     */
                    tempRate = dcoLdoClk /
                               (uint64_t) ((uint64_t) factor *
                                           (uint64_t)
                                           (*(dpllConfig.postDivConfList)).
                                           configValue);
                    *clkRate = (uint32_t) tempRate;
                }
                else
                {
                    /* to stop from 32bit overflow*/
                    tempRate = dcoLdoClk /
                               (uint64_t) (*(dpllConfig.postDivConfList)).
                               configValue;
                    *clkRate = (uint32_t) tempRate;
                }
            }
            else
            {
                *clkRate = rootFreq;
            }
            while (postDivideFactorLength != (uint8_t) 0)
            {
                *clkRate = *clkRate /
                           postDpllDivideFactor[postDivideFactorLength -
                                                (uint8_t) 1];
                postDivideFactorLength--;
            }
        }
    }
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static pmErrCode_t PmlibClkRateGetParentOfModule(pmhalClockTreeNodeId  nodeId,
                                                 pmhalPrcmClockId_t    clkId,
                                                 pmhalClockTreeNodeId *nxtNode)
{
    pmhalClockTreeInputEdgePtr edgePtr;
    pmhalClockTreeNodeIdCvec   pred;
    pmhalClockTreeSize_t       npred;
    pmErrCode_t retVal = PM_SUCCESS;
    retVal = PMHALClockTreeGetModuleEdge(nodeId, clkId, &edgePtr);
    if (PM_SUCCESS == retVal)
    {
        *nxtNode = (edgePtr->prop)->ptype;
    }
    if (PM_CLOCTREE_EDGE_NOT_AVAILABLE == retVal)
    {
        /* npred - number of predecessors is always 1 for a module along a
         * clock.
         */
        retVal = PMHALClockTreeGetPredecessors(nodeId, &pred, &npred);
        if (PM_SUCCESS == retVal)
        {
            *nxtNode = *pred;
        }
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateGetParentOfMux(pmhalClockTreeNodeId  nodeId,
                                              pmhalClockTreeNodeId *nxtNode)
{
    pmErrCode_t       retVal = PM_SUCCESS;
    pmhalPrcmNodeId_t nextNodeVar;
    /* Get the multiplexer selection and find which parent node it is connected
     * to.
     */
    retVal = (pmErrCode_t) PMHALCMMuxParentGet((pmhalPrcmNodeId_t) nodeId,
                                               &nextNodeVar);
    if (PM_SUCCESS == retVal)
    {
        *nxtNode = (pmhalClockTreeNodeId) nextNodeVar;
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateGetParentOfDiv(pmhalClockTreeNodeId  nodeId,
                                              pmhalClockTreeNodeId *nxtNode)
{
    pmErrCode_t              retVal = PM_SUCCESS;
    pmhalClockTreeNodeIdCvec pred;
    pmhalClockTreeSize_t     npred;
    /* A divider always has one parent node */
    retVal = PMHALClockTreeGetPredecessors(nodeId, &pred, &npred);
    if (PM_SUCCESS == retVal)
    {
        *nxtNode = *pred;
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateGetParentOfDpll(
    pmhalClockTreeNodeId  nodeId,
    pmhalPrcmDpllClkInput_t
    bypClkSel,
    pmhalClockTreeNodeId *nxtNode)
{
    pmErrCode_t                retVal = PM_SUCCESS;
    pmhalClockTreeNodeIdCvec   pred;
    pmhalClockTreeSize_t       npred;
    pmhalClockTreeInputEdgePtr edgePtr;
    pmhalClockTreeEdgePropPtr  edgePropPtr;
    retVal = (pmErrCode_t) PMHALClockTreeGetPredecessors(nodeId, &pred, &npred);
    if (PM_SUCCESS == retVal)
    {
        if (1U == npred)
        {
            /* If the DPLL has only one source of clock */
            *nxtNode = *pred;
        }
        else
        {
            /* If there are multiple sources of clocks for the DPLL. Decide
             * which path to follow based on bypass clock selection read off the
             * DPLL register.
             */
            retVal = PMHALClockTreeGetDpllInEdge(nodeId, bypClkSel, &edgePtr);
            if (PM_SUCCESS == retVal)
            {
                retVal = PMHALClockTreeGetEdgeProp(edgePtr, &edgePropPtr);
                if (PM_SUCCESS == retVal)
                {
                    *nxtNode = edgePropPtr->ptype;
                }
            }
            else if (PM_INPUT_PARAM_BAD_CLOCKTREE_EDGE_PROPERTY_ID == retVal)
            {
                *nxtNode = PMHAL_PRCM_NODE_UNDEF;
            }
            else
            {
                *nxtNode = PMHAL_PRCM_NODE_UNDEF;
                retVal   = PM_FAIL;
            }
        }
    }
    return retVal;
}

static pmErrCode_t PmlibClkRatePopulateDpll(
    pmhalClockTreeNodeId       nodeId,
    pmhalClockTreeInputEdgePtr edgePtr,
    pmhalPrcmDpllConfig_t     *
    dpllConfig)
{
    pmErrCode_t     retVal   = PM_SUCCESS;
    pmhalNodeType_t nodeType = PMHALClockTreeGetNodeType(nodeId);
    if (PMHAL_DPLL != nodeType)
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        /* Get the post divider value corresponding to a given HSDIV */
        (*((*dpllConfig).postDivConfList)).postDivId =
            (pmhalPrcmDpllPostDivId_t) edgePtr->prop->ptype;
        retVal = (pmErrCode_t) PMHALCMDpllGetPostDiv(
            (pmhalPrcmNodeId_t) nodeId,
            (*dpllConfig).postDivConfList,
            1U);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Get the M value */
        (*dpllConfig).multiplier =
            PMHALCMDpllGetMultiplier((pmhalPrcmNodeId_t) nodeId);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Get the fractional M value */
        (*dpllConfig).fracMultiplier =
            PMHALCMDpllGetFracMultiplier((pmhalPrcmNodeId_t) nodeId);
    }
    if (PM_SUCCESS == retVal)
    {
        /* Get the N value */
        (*dpllConfig).divider = PMHALCMDpllGetDivider(
            (pmhalPrcmNodeId_t) nodeId);
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateCpuSet(pmlibClockRateFreqConfig_t clkFreqConfig,
                                      pmhalPrcmModuleId_t        modId,
                                      uint32_t                   clkRate)
{
    pmErrCode_t        retVal = PM_SUCCESS;
    pmhalPrcmVdId_t    vdId;
    pmhalVmOppId_t     newOpp, depOpp;
    pmhalPrcmCpuId_t   cpuId;
    pmhalPrcmCpuId_t   depCpuId;
    pmhalPrcmClockId_t depClkId;
    uint32_t           depCurrRate;
    uint32_t           currVoltage, newVoltage;
    uint32_t           modIdArrayIndex;

    /* a) Get OPP for the given clkRate */
    cpuId  = PMUtilsGetCpuId(modId);
    if (cpuId == (pmhalPrcmCpuId_t)PMHAL_PRCM_CPU_ID_UNDEF)
    {
        retVal = PM_FAIL;
    }
    if (PM_SUCCESS == retVal)
    {
        newOpp = PMUtilsGetOppFromClkRate(cpuId, clkRate);
        /* b) Configure all Mux's */
        if (clkFreqConfig.numMuxSel != 0U)
        {
            retVal = PmlibClkRateMuxConfigure(clkFreqConfig.muxSelList,
                                              clkFreqConfig.numMuxSel);
        }
        /* c) Get the currentOPP (derive VDid from given modID) */
        vdId = PMUtilsGetCpuVdId(modId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PMHALVMGetCurrentVoltage(vdId, &currVoltage);
        }
    }

    if ((PM_SUCCESS == retVal) && (newOpp != PMHAL_VM_OPP_UNDEF))
    {
        retVal = PMHALVMGetVoltageForOpp(vdId, newOpp, &newVoltage);
        /* d) If Current voltage and new voltage is same,configure the
         *     DPLL with configuration value
         */
        if (currVoltage == newVoltage)
        {
            if (clkFreqConfig.dpllConfig != NULL)
            {
                retVal = PmlibClkRateDpllConfigure(clkFreqConfig.dpllId,
                                                   *(clkFreqConfig.dpllConfig));
            }
        }
        /* e) if Current voltage is less than new voltage.
         *    Set the OPP to new OPP and then configure the DPLL
         *    with config value */
        else if (newVoltage > currVoltage)
        {
            /* if VD's sharing the same rail has OPP lesser or equal to new OPP,
             * change the OPP
             */
            retVal = PmlibClkRateOppChangeForGangRails(newOpp,
                                                       vdId);
            if (PM_SUCCESS == retVal)
            {
                retVal = PmlibClkRateDpllConfigure(clkFreqConfig.dpllId,
                                                   *(clkFreqConfig.dpllConfig));
            }
        }
        /* if new OPP is less than Current OPP ,configure the DPLL with
         * config value */
        else
        {
            retVal = PmlibClkRateDpllConfigure(clkFreqConfig.dpllId,
                                               *(clkFreqConfig.dpllConfig));
            if (PM_SUCCESS == retVal)
            {
                /* If no dependent CPU's, then lower the OPP to new OPP */
                retVal = PMHALVMGetDepCpuId(cpuId, &depCpuId);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_CPU_ID_UNDEF == depCpuId)
                    {
                        /* if VD's sharing the same rail has OPP lesser or
                         * equal to new OPP, change the OPP
                         */
                        retVal = PmlibClkRateOppChangeForGangRails(newOpp,
                                                                   vdId);
                        if (PM_FAIL == retVal)
                        {
                            /* frequency is set,but OPP not changed */
                            retVal = PM_SUCCESS;
                        }
                    }
                    /* If dependent CPU is present,then get the clockrate of dep
                     * CPU
                     * using clkrateGet() function for its generic clock. */
                    else
                    {
                        pmhalPrcmModuleId_t depModId =
                            PMUtilsGetModIdForCpuId(depCpuId);
                        modIdArrayIndex = PMUtilsGetModuleId(depModId);

                        if (modIdArrayIndex <
                            (PMHAL_PRCM_MOD_COUNT -
                             PMHAL_PRCM_MOD_LOWER_BOUND - 1U))
                        {
                            depClkId = gModuleGenericClkList[modIdArrayIndex];
                        }
                        else
                        {
                            retVal = PM_FAIL;
                        }

                        if (PM_SUCCESS == retVal)
                        {
                            retVal = PMLIBClkRateGet(depModId, depClkId,
                                                     &depCurrRate);
                        }

                        if (PM_SUCCESS == retVal)
                        {
                            /* get the dep OPP corresponding to the clkrate. */
                            depOpp = PMUtilsGetOppFromClkRate(depCpuId,
                                                              depCurrRate);
                            if (PMHAL_VM_OPP_UNDEF == depOpp)
                            {
                                retVal = PM_FAIL;
                            }
                            /* If depCpuOPP is less than or equal to newOpp,
                             * then lower the OPP to newOpp else no OPP change
                             */
                            if ((PM_SUCCESS == retVal) && (depOpp <= newOpp))
                            {
                                /* if VD's sharing the same rail has OPP lesser
                                 * or equal to new OPP, change the OPP
                                 */
                                retVal = PmlibClkRateOppChangeForGangRails(
                                    newOpp,
                                    vdId);
                                if (PM_FAIL == retVal)
                                {
                                    /* frequency is set,but OPP not changed */
                                    retVal = PM_SUCCESS;
                                }
                            }
                        }
                    }
                }
            }
        }
        /* OPP not supported. But Frequency has been changed */
        if (PM_VOLTAGE_INVALID == retVal)
        {
            retVal = PM_SUCCESS;
        }
        /* After setting up the DPLL's, change the divider setting to
         * the required value */
        if (PM_SUCCESS == retVal)
        {
            if (clkFreqConfig.numDivSel != 0)
            {
                retVal = PmlibClkRateDividerConfigure(clkFreqConfig.divSelList,
                                                      clkFreqConfig.numDivSel);
            }
        }
    }
    /* If the frequency provided doesn't have supported OPP Send PM_FAIL */
    else
    {
        retVal = PM_FAIL;
    }
    return retVal;
}

static pmErrCode_t PmlibClkRatePeripheralSet(
    pmhalPrcmModuleId_t modID,
    pmlibClockRateFreqConfig_t
    clkFreqConfig)
{
    pmErrCode_t retVal = PM_SUCCESS;
    /* Configure Dividers */
    if (clkFreqConfig.numDivSel != 0)
    {
        retVal = PmlibClkRateDividerConfigure(clkFreqConfig.divSelList,
                                              clkFreqConfig.numDivSel);
    }
    /* Configure DPLLs */
    if (PM_SUCCESS == retVal)
    {
        if (clkFreqConfig.dpllConfig != NULL)
        {
            retVal = PmlibClkRateDpllConfigure(clkFreqConfig.dpllId,
                                               *(clkFreqConfig.dpllConfig));
        }
    }
    /* Configure Multiplexers */
    if (PM_SUCCESS == retVal)
    {
        if (clkFreqConfig.numMuxSel != 0)
        {
            retVal = PmlibClkRateMuxConfigure(clkFreqConfig.muxSelList,
                                              clkFreqConfig.numMuxSel);
        }
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateDividerConfigure(const pmlibClockRateDivConfig_t
                                                        *divSelList,
                                                uint32_t numDivSel)
{
    uint32_t    idx    = 0U;
    pmErrCode_t retVal = PM_SUCCESS;
    /* Find the number of dividers and program the list of dividers */
    while (idx != numDivSel)
    {
        retVal = (pmErrCode_t) PMHALCMDpllSetClockDivider(
            divSelList[idx].divId,
            divSelList[idx].
            divEnum);
        if (PM_SUCCESS != retVal)
        {
            break;
        }
        idx++;
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateDpllConfigure(pmhalPrcmNodeId_t     dpllId,
                                             pmhalPrcmDpllConfig_t dpllConfig)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalPrcmDpllConfig_t *config = &dpllConfig;
    retVal = (pmErrCode_t) PMHALCMDpllConfigure(dpllId, config,
                                                PM_TIMEOUT_INFINITE);
    return retVal;
}

static pmErrCode_t PmlibClkRateMuxConfigure(
    const pmlibClockRateMuxConfig_t *muxSelList,
    uint32_t
    numMuxSel)
{
    uint32_t    idx    = 0U;
    pmErrCode_t retVal = PM_SUCCESS;
    /* Find the number of multiplexers and program the list of multiplexers */
    while (idx != numMuxSel)
    {
        retVal = (pmErrCode_t) PMHALCMMuxParentSelect(muxSelList[idx].muxId,
                                                      muxSelList[idx].muxSelect);
        if (PM_SUCCESS != retVal)
        {
            break;
        }
        idx++;
    }
    return retVal;
}

static pmErrCode_t PmlibClkRateOppChangeForGangRails(pmhalVmOppId_t  newOpp,
                                                     pmhalPrcmVdId_t vdId)
{
    uint8_t           idx, cantChangeVoltage = 0;
    pmhalVmOppId_t    depOpp;
    pmhalPrcmVdId_t  *vdIdList = vdRailShareArray[vdId].vdRailSharedId;
    pmErrCode_t       retVal;
    uint32_t          depVoltage, newVoltage;
    pmhalPrcmCpuId_t *cpuIdArray;
    uint32_t          numCpus, cpuIdx;
    uint32_t          depCpuRate;

    if (vdRailShareArray[vdId].vdRailShareId != 0U)
    {
        retVal = PMHALVMGetVoltageForOpp(vdId, newOpp, &newVoltage);
        for (idx = 0; idx < vdRailShareArray[vdId].vdRailShareId; idx++)
        {
            /* Get the CPU in the Ganged Voltage rail */
            retVal = PMHALVMGetCpuInVoltageDomain(vdIdList[idx],
                                                  &cpuIdArray, &numCpus);
            for (cpuIdx = 0U; cpuIdx < numCpus; cpuIdx++)
            {
                pmhalPrcmModuleId_t modID = PMUtilsGetModIdForCpuId(
                    cpuIdArray[cpuIdx]);
                /* Get the frequency of the CPU */
                retVal = PMLIBClkRateGet(modID, PMHAL_PRCM_CLK_GENERIC,
                                         &depCpuRate);
                if (PM_SUCCESS == retVal)
                {
                    /* Get the opp from the frequency */
                    depOpp = PMUtilsGetOppFromClkRate(cpuIdArray[cpuIdx],
                                                      depCpuRate);
                    /* Get the voltage from the opp */
                    retVal = PMHALVMGetVoltageForOpp(vdId, depOpp, &depVoltage);
                    if ((PM_SUCCESS == retVal) && (depVoltage > newVoltage))
                    {
                        /* Can't change the voltage in this case */
                        cantChangeVoltage = (uint8_t) 1;
                        break;
                    }
                }
            }
            if ((uint8_t) 1 == cantChangeVoltage)
            {
                break;
            }
        }
        /* If the new voltage is higher than dependent voltages then set new
         * voltage.
         */
        if (0 == cantChangeVoltage)
        {
            retVal = PMHALVMSetOpp(vdId, newOpp, PM_TIMEOUT_INFINITE);
        }
    }
    else
    {
        retVal = PMHALVMSetOpp(vdId, newOpp, PM_TIMEOUT_INFINITE);
    }

    return retVal;
}

