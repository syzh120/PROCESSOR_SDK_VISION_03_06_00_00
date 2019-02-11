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
 * \file    pmlib_videopll.c
 *
 * \brief   This file contains Videopll LIB API Implementation.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include "pmhal_prcm.h"
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
#include "pmhal_videopll.h"
#endif
#include "pmhal_cm.h"
#include "pm_utils.h"
#include "pmlib_videopll_data.h"
#include "pmlib_videopll.h"
#include "pmlib_clkrate.h"

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
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
/**
 * \brief This API returns the frequency calculated using inputs.
 *
 * \param multi     multiplier input parameter to calculate output frequency .
 * \param fracM     Fractional multiplier input parameter to calculate
 *                  output frequency .
 * \param divider   divider input parameter to calculate output frequency .
 * \param hsDiv     HS divider input parameter to calculate output frequency .
 * \param srcClk    Source clk input parameter to calculate output frequency .
 *
 * \retval frequency resulting for given input params
 */
static uint32_t PmlibCalculateFreq(int32_t  multi,
                                   int32_t  fracM,
                                   int32_t  divider,
                                   uint32_t hsDiv,
                                   uint32_t srcClk);
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*  None    */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMLIBVideopllSetFreq(pmhalPrcmNodeId_t videopllId,
                             uint32_t          freq,
                             uint32_t          maxOrMinMN,
                             uint32_t          timeOut)
{
    int32_t retVal = PM_FAIL;

    if ((PMHAL_PRCM_VIDEOPLL_MIN <= videopllId) &&
        (PMHAL_PRCM_VIDEOPLL_COUNT > videopllId))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
        /* For the SOC_TDA2XX, SOC_DRA75x and SOC_TDA2EX DSS video PLLs
         * are present in the design. Hence use PMHAL Video PLL to program
         * the video clock frequency
         */
        pmhalVideopllConfig_t       videoPllConfigure;
        pmhalPrcmPllPostDivValue_t  postDivConfig[
            PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID];
        pmhalVideopllSelectConfig_t pllSelectConfig;
        pmhalVideopllModeConfig_t   pllModeConfig;

        videoPllConfigure.postDivConfList = postDivConfig;
        /* For the given frequency find the configuration to program the
         * Video PLL.
         */
        retVal = PmlibVideopllGetpllStructure(videopllId, freq, maxOrMinMN,
                                              &videoPllConfigure);

        if (PM_SUCCESS == retVal)
        {
            /* Configure the PLL Select and mode config structures which would
             * be used by the PMHAL API to program the Video PLL.
             */
            pllSelectConfig.pllRefEn    = 1U;
            pllSelectConfig.phyClkinEn  = 0U;
            pllSelectConfig.hsdivBypass = 1U;
            pllSelectConfig.refSysclk   = PMHAL_VIDEOPLL_REFSEL_REF_SYSCLK;
            pllSelectConfig.clockEnM4   = 1U;
            pllSelectConfig.clockEnM6   = 1U;

            videoPllConfigure.videopllSelectConfig = &pllSelectConfig;

            pllModeConfig.pllIdle      = 0U;
            pllModeConfig.pllLpMode    = 0U;
            pllModeConfig.lowCurrStBy  = 0U;
            pllModeConfig.driftGuardEn = 0U;
            pllModeConfig.lockSel      = 0U;
            pllModeConfig.refEn        = 1U;
            pllModeConfig.phyClkinEn   = 1U;
            pllModeConfig.byPassEn     = 0U;
            pllModeConfig.hsDivbyPass  = 0U;

            videoPllConfigure.videopllModeConfig = &pllModeConfig;

            if (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI)
            {
                /* HDMI supports only one post divider */
                videoPllConfigure.maxPostDivElems = 1U;
                videoPllConfigure.postDivConfList[0].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M2;
            }
            if (videoPllConfigure.divider != (uint16_t)0)
            {
                retVal = PMHALVideopllConfigure(videopllId,
                                            &videoPllConfigure,
                                            timeOut);
            }
            else
            {
                retVal = PM_FAIL;
            }
        }
#else
        /* For TDA3xx the DSS video clock is sourced from the device DPLLs
         * Hence use the PMHAL CM APIs to be able to program the video clock
         * frequency.
         */
        pmhalPrcmDpllConfig_t      pllParams;
        pmhalPrcmPllPostDivValue_t postDivConfig[
            PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID];
        uint32_t postdiv = PMHAL_PRCM_DPLL_POST_DIV_INVALID;

        pllParams.postDivConfList = postDivConfig;
        /* For the given frequency find the configuration to program the
         * DPLL.
         */
        retVal = PmlibVideopllGetpllStructure(videopllId,
                                              freq, maxOrMinMN,
                                              &pllParams, &postdiv);

        if (PM_SUCCESS == retVal)
        {
            retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                           &pllParams,
                                           timeOut);

            retVal += PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_VID_PIX_CLK,
                                                 postdiv);
        }
#endif
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
int32_t PMLIBVideopllVencGetFreq(pmlibVideoPllVenc_t vencId, uint32_t *freq)
{
    int32_t retVal = PM_FAIL;
    pmhalPrcmClockId_t vidpllClkId;
    pmhalVideopllHSD_t hsDivId;

    if (vencId < PMLIB_VIDEOPLL_VENC_MAX)
    {
        /* Find the source of the Venc clock */
        retVal = PMHALVideopllGetVencSource((pmhalVideoPllVenc_t) vencId,
                                            &vidpllClkId, &hsDivId);

        if (PM_SUCCESS == retVal)
        {
            /* Find the clock frequency sourced by the video PLL and HS Divider
             * combination.
             */
            PMLIBVideopllGetFreq(vidpllClkId, hsDivId, freq);
        }
    }
    return retVal;
}

int32_t PMLIBVideopllPrcmInCLkGetFreq(pmhalPrcmNodeId_t vidpllId,
                                      uint32_t         *freq)
{
    int32_t retVal = PM_SUCCESS;
    pmhalPrcmClockId_t vidpllClkId;
    pmhalVideopllHSD_t hsDivId;

    /* For the given Video PLL Node find the source of the clock from the
     * HSDivider and PLL Clock source.
     */
    if (vidpllId == PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN)
    {
        vidpllClkId = PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK;
        hsDivId     = PMHAL_VIDEOPLL_HSD_M7;
    }
    else if (vidpllId == PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN)
    {
        vidpllClkId = PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK;
        hsDivId     = PMHAL_VIDEOPLL_HSD_M2;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (vidpllId == PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN)
    {
        vidpllClkId = PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK;
        hsDivId     = PMHAL_VIDEOPLL_HSD_M7;
    }
    else if (vidpllId == PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN)
    {
        vidpllClkId = PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK;
        hsDivId     = PMHAL_VIDEOPLL_HSD_M2;
    }
#endif
    else if (vidpllId == PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN)
    {
        vidpllClkId = PMHAL_PRCM_CLK_HDMI_DPLL_CLK;
        hsDivId     = PMHAL_VIDEOPLL_HSD_INVALID;
    }
    else
    {
        retVal = PM_BADARGS;
    }
    if (PM_SUCCESS == retVal)
    {
        /* Once the clock source is known find the frequency of the clock
         * sourced.
         */
        retVal = PMLIBVideopllGetFreq(vidpllClkId, hsDivId, freq);
    }
    return retVal;
}

int32_t PMLIBVideopllGetFreq(pmhalPrcmClockId_t vidpllClkId,
                             pmhalVideopllHSD_t hsDivId,
                             uint32_t          *freq)
{
    int32_t           retVal = (int32_t) PM_SUCCESS;
    int32_t           multi = (int32_t) 1, divider = (int32_t) 1;
    uint32_t          hsDiv, srcClk;
    int32_t           fracM = (int32_t)0;
    pmhalPrcmNodeId_t vidPllId;

    /* Find the PLL Id from the Video PLL Clock ID */
    if (vidpllClkId == PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK)
    {
        vidPllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (vidpllClkId == PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK)
    {
        vidPllId = PMHAL_PRCM_VIDEOPLL_VIDEO2;
    }
#endif
    else if (vidpllClkId == PMHAL_PRCM_CLK_HDMI_DPLL_CLK)
    {
        vidPllId = PMHAL_PRCM_VIDEOPLL_HDMI;
    }
#if defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (vidpllClkId == PMHAL_PRCM_CLK_SATA_DPLL_CLK)
    {
        vidPllId = PMHAL_PRCM_DPLL_SATA;
    }
#endif
    else
    {
        vidPllId = PMHAL_PRCM_VIDEOPLL_UNDEF;
    }
    if (PMHAL_PRCM_VIDEOPLL_UNDEF != vidPllId)
    {
        /* Read the multiplier */
        multi = PMHALVideopllGetMultiplier(vidPllId);
        fracM = PMHALVideopllGetFracMultiplier(vidPllId);
        /* Read the Divider */
        divider = PMHALVideopllGetDivider(vidPllId);
        /* Read possible HSdividers */
        if (PMHAL_PRCM_VIDEOPLL_HDMI != vidPllId)
        {
            if ((hsDivId != PMHAL_VIDEOPLL_HSD_M2) &&
                (hsDivId != PMHAL_VIDEOPLL_HSD_INVALID))
            {
                retVal = PMHALVideopllGetHSDivider(vidPllId,
                                                   hsDivId,
                                                   &hsDiv);
            }
            else if (PMHAL_VIDEOPLL_HSD_M2 == hsDivId)
            {
                /* Fixed value of 2 as the M2 clock is
                 * M * ref_clk /((N+1) * M2).
                 * M2 is always 1 and the PmlibCalculateFreq
                 * function calculates the frequency as
                 * 2*M*ref_clk/((N+1) * HSD).
                 */
                hsDiv = 2U;
            }
            else
            {
                hsDiv = 1U;
            }
        }
        else
        {
            retVal = PMHALVideopllGetHSDivider(vidPllId, hsDivId, &hsDiv);
        }
    }
    #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
    if (vidpllClkId == PMHAL_PRCM_CLK_SATA_DPLL_CLK)
    {
        srcClk = PMHALCMGetSysClockFreq() * 1000U;
    }
    else
    {
        /* Find the frequency of the clock source */
        retVal = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSS, vidpllClkId, &srcClk);
    }
    #else
    retVal = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSS, vidpllClkId, &srcClk);
    #endif
    if (PM_SUCCESS == retVal)
    {
        if (PMHAL_PRCM_VIDEOPLL_UNDEF != vidPllId)
        {
            /* From the clock source frequency find the actual video clock
             * frequency.
             */
            #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
            if (vidPllId != PMHAL_PRCM_VIDEOPLL_HDMI)
            {
                hsDiv = hsDiv + 1U;
            }
            else
            {
                hsDiv = 2U * hsDiv;
            }
            #else
            hsDiv = hsDiv + 1U;
            #endif
            *freq = PmlibCalculateFreq(multi, fracM, divider, hsDiv, srcClk);
        }
        else
        {
            *freq = srcClk;
        }
    }
    return retVal;
}

int32_t PMLIBVideopllSetVencClkSrc(pmlibVideoPllVenc_t   outputVenc,
                                   pmlibVideoPllClkSrc_t vencClkSrc)
{
    pmhalVideopllSelectConfig_t videopllSelectConfig;
    int32_t retVal = (int32_t) PM_SUCCESS;
    if ((outputVenc < PMLIB_VIDEOPLL_VENC_MAX) &&
        (vencClkSrc < PMLIB_VIDEOPLL_CLKSRC_MAX))
    {
        /* Based on the output VENC clock source find the proper mux selection
         * to source the clock source */
        switch (outputVenc)
        {
            case PMLIB_VIDEOPLL_VENC_LCD1:
            /* Perform a default configuration for TDA2px */
            #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                retVal = PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1);
            #endif
                /* Find the clock source configuration */
                switch (vencClkSrc)
                {
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1:
                        PMHALVideopllGetSelectFields(PMHAL_PRCM_VIDEOPLL_VIDEO1,
                                                     &videopllSelectConfig);

                        videopllSelectConfig.clockEnM4 = 1U;

                        retVal += PMHALVideopllSetSelectFields(
                            PMHAL_PRCM_VIDEOPLL_VIDEO1,
                            &videopllSelectConfig);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A,
                            PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1);
                        #endif
                        break;

                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A,
                            PMHAL_PRCM_VIDEOPLL_MUX_HDMI);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1);
                        #endif
                        break;

                    case PMLIB_VIDEOPLL_CLKSRC_DSS_GFCLK:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM);
                        break;
                    #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_SATA:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1,
                            PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA);
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1,
                            PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL1);
                        retVal += PMHALVideopllConfigureMux(
                                    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH,
                                    PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1);
                        break;
                    #endif
                    default:
                        retVal = PM_BADARGS;
                        break;
                }
                break;

            case PMLIB_VIDEOPLL_VENC_LCD2:
            /* Perform a default configuration for TDA2px */
            #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                retVal = PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
            #endif
                /* Find the clock source configuration */
                switch (vencClkSrc)
                {
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3:
                        PMHALVideopllGetSelectFields(PMHAL_PRCM_VIDEOPLL_VIDEO1,
                                                     &videopllSelectConfig);

                        videopllSelectConfig.clockEnM6 = 1U;

                        retVal += PMHALVideopllSetSelectFields(
                            PMHAL_PRCM_VIDEOPLL_VIDEO1,
                            &videopllSelectConfig);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B,
                            PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
                        #endif
                        break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3:
                        PMHALVideopllGetSelectFields(PMHAL_PRCM_VIDEOPLL_VIDEO2,
                                                     &videopllSelectConfig);
                        videopllSelectConfig.clockEnM6 = 1U;

                        retVal += PMHALVideopllSetSelectFields(
                            PMHAL_PRCM_VIDEOPLL_VIDEO2,
                            &videopllSelectConfig);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B,
                            PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
                        #endif
                        break;
#endif
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI:

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B,
                            PMHAL_PRCM_VIDEOPLL_MUX_HDMI);

                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
                        #endif
                        break;

                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_ABE_GICLK:

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B,
                            PMHAL_PRCM_VIDEOPLL_MUX_ABE);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
                        break;

                    case PMLIB_VIDEOPLL_CLKSRC_DSS_GFCLK:

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM);
                        break;
                    #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_SATA:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2,
                            PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA);
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2,
                            PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL2);
                        retVal += PMHALVideopllConfigureMux(
                                    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH,
                                    PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2);
                        break;
                    #endif
                    default:
                        retVal = PM_BADARGS;
                        break;
                }
                break;
            case PMLIB_VIDEOPLL_VENC_LCD3:
                /* Perform a default configuration for TDA2px */
            #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                retVal = PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1);
            #endif
                /* Find the clock source configuration */
                switch (vencClkSrc)
                {
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3:
                        PMHALVideopllGetSelectFields(PMHAL_PRCM_VIDEOPLL_VIDEO1,
                                                     &videopllSelectConfig);

                        videopllSelectConfig.clockEnM6 = 1U;

                        retVal += PMHALVideopllSetSelectFields(
                            PMHAL_PRCM_VIDEOPLL_VIDEO1,
                            &videopllSelectConfig);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C,
                            PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1);
                        #endif
                        break;

                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C,
                            PMHAL_PRCM_VIDEOPLL_MUX_HDMI);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1);
                        #endif
                        break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT1:
                        PMHALVideopllGetSelectFields(PMHAL_PRCM_VIDEOPLL_VIDEO2,
                                                     &videopllSelectConfig);
                        videopllSelectConfig.clockEnM4 = 1U;

                        retVal += PMHALVideopllSetSelectFields(
                            PMHAL_PRCM_VIDEOPLL_VIDEO2,
                            &videopllSelectConfig);

                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C,
                            PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2);
                        #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12);
                        #else
                        retVal += PMHALVideopllConfigureMux(
                                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1);
                        #endif
                        break;
#endif
                    case PMLIB_VIDEOPLL_CLKSRC_DSS_GFCLK:
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                            PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM);
                        break;
                    #if defined (SOC_TDA2PX) || defined (SOC_AM574x)
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_SATA:
                        /* Defaulting to AL2. Need to revisit if AL1 should
                         * source this clock.
                         */
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2,
                            PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA);
                        retVal += PMHALVideopllConfigureMux(
                            PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12,
                            PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL2);
                        retVal += PMHALVideopllConfigureMux(
                                    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH,
                                    PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12);
                        break;
                    #endif
                    default:
                        retVal = PM_BADARGS;
                        break;
                }
                break;

            case PMLIB_VIDEOPLL_VENC_HDMI:
                /* Find the clock source configuration */
                switch (vencClkSrc)
                {
                    case PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI:
                        /*TODO - Find if there is any other options for HDMI*/
                        break;

                    default:
                        retVal = PM_BADARGS;
                        break;
                }
                break;
            default:
                retVal = PM_BADARGS;
                break;
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

int32_t PMLIBVideopllSetDispcFuncClkSrc(pmlibVideoPllClkSrc_t fClkSrc)
{
    int32_t retVal = PM_SUCCESS;
    switch (fClkSrc)
    {
        /* Find the clock source multiplexer configuration */
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_HDMI_CLK1);
            break;

        case PMLIB_VIDEOPLL_CLKSRC_DSS_GFCLK:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM);
            break;
#if defined (SOC_TDA2PX) || defined (SOC_AM574x)
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1);
            break;
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3:
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3:
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_ABE_GICLK:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2);
            break;
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT1:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12);
            break;
#else
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1);
            break;
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3:
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3:
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_ABE_GICLK:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1);
            break;
        case PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT1:
            retVal = PMHALVideopllConfigureMux(
                PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH,
                PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1);
            break;
#endif
        default:
            retVal = PM_BADARGS;
            break;
    }
    return retVal;
}

int32_t PMLIBVideopllEnableHdmiPll(uint32_t enable)
{
    int32_t retVal = PM_SUCCESS;
    /* Call the PMHAL APIs to enable or disable the HDMI PLL */
    if (1U == enable)
    {
        retVal = PMHALVideopllSetPllProgramming(
            PMHAL_PRCM_VIDEOPLL_HDMI,
            PMHAL_VIDEOPLL_DSS_CONTROL_ENABLE);
    }
    else
    {
        retVal = PMHALVideopllSetPllProgramming(
            PMHAL_PRCM_VIDEOPLL_HDMI,
            PMHAL_VIDEOPLL_DSS_CONTROL_DISABLE);
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmlibCalculateFreq(int32_t  multi,
                                   int32_t  fracM,
                                   int32_t  divider,
                                   uint32_t hsDiv,
                                   uint32_t srcClk)
{
    uint32_t freq;
    Double dFreq;
    uint32_t rootClk = srcClk / 1000U;
    Double mul = (Double)multi + ((Double)fracM/(Double)262144);
    /* Find the frequency as 2*M* sourceClock / (HSDIV * (N+1)) */
    dFreq = (((Double) 2U * (Double) mul * (Double) rootClk) /
           ((Double) hsDiv *
            ((Double) divider + (Double) 1)));
    freq = (uint32_t) dFreq;
    return freq;
}

#endif
/* None */

