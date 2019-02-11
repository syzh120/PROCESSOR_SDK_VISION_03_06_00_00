/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 * \file main.c
 *
 * \brief   Video Pll calculator example
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <stdio.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/src/pmhal/prcm/common/hw_pmhal_data.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define STEPSIZE 250

/**
 * \brief Holds the root clock frequencies specific for a given platform
 */
static uint32_t *gRootClkFreqList;

/**
 * \brief Holds the voltage domains information whose rails are shared
 */
static pmlibBoardVdRailShare_t *gVdRailShareList;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API validate the videopll PMLIBVideopllSetFreq api.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the module is not enabled (timeout)
 *         PM_BADARGS       Invalid module id
 */
static pmErrCode_t PmlibVaildateVideoPll();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    printf("\n Video PLL Test Application Running on m4 \n");

    gRootClkFreqList = PMLIBBoardConfigGetRootClks();
    gVdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    PMLIBClkRateInit(gRootClkFreqList, gVdRailShareList);

    /* validate videopll */
    PmlibVaildateVideoPll();

    return 0;
}

static pmErrCode_t PmlibVaildateVideoPll()
{
    int32_t                    retVal = PM_FAIL;
    uint32_t                   i, maxOrMin;
    uint32_t                   setFreq   = 0U;
    uint32_t                   timeDelay = 0x00001000U;
    int32_t                    multi, divider;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    pmhalPrcmNodeId_t          videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
    pmhalPrcmClockId_t         vidpllClkId;
    pmhalVideopllHSD_t         hsDivId;
    uint32_t                   hsDiv;
#else
    pmhalPrcmNodeId_t          videopllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
    pmhalPrcmPllPostDivValue_t postDiv    = {PMHAL_PRCM_DPLL_POST_DIV_M2, 0U};

#endif

    for (maxOrMin = PMLIB_VIDEO_PLL_CALC_MIN_MN;
         maxOrMin <= PMLIB_VIDEO_PLL_CALC_MAX_MN; maxOrMin++)
    {
        printf("\n--------------------------------------------------\n");
        if (maxOrMin == 0U)
        {
            printf(" Calculating for minimum M and N ");
        }
        else
        {
            printf(" Calculating for maximum M and N ");
        }
        printf("\n--------------------------------------------------\n");
        printf("Enter the Desired Value: ");
        scanf("%d", &i);
        retVal = PMLIBVideopllSetFreq(videopllId,
                                      i,
                                      maxOrMin,
                                      timeDelay);
        if (PM_SUCCESS == retVal)
        {
            printf("Set Freq success, ");
        }
        else if (PM_VIDEOPLL_CALC_PARAMS_FAILED == retVal)
        {
            printf("Params Get Failed, ");
        }
        else
        {
            printf("Setting Failed, ");
        }
        if (PM_SUCCESS == retVal)
        {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            retVal = PMLIBVideopllSetVencClkSrc(
                PMLIB_VIDEOPLL_VENC_LCD1,
                PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1);
            if (retVal == PM_SUCCESS)
            {
                retVal = PMLIBVideopllVencGetFreq(PMLIB_VIDEOPLL_VENC_LCD1,
                                                  &setFreq);
            }
            else
            {
                printf("Set Venc Source Failed\n");
            }
            if (setFreq == i)
            {
                printf("Get Freq Success\n");
            }
            else
            {
                printf(
                    " Frequency did not match %d\n",
                    setFreq);
            }
            retVal = PMHALVideopllGetVencSource((pmhalVideoPllVenc_t)
                                                PMLIB_VIDEOPLL_VENC_LCD1,
                                                &vidpllClkId, &hsDivId);
            /* Read the multiplier */
            multi = PMHALVideopllGetMultiplier(videopllId);
            /* Read the Divider */
            divider = PMHALVideopllGetDivider(videopllId);
            /* Read possible HSdividers */
            if (PMHAL_PRCM_VIDEOPLL_HDMI != videopllId)
            {
                if ((hsDivId != PMHAL_VIDEOPLL_HSD_M2) &&
                    (hsDivId != PMHAL_VIDEOPLL_HSD_INVALID))
                {
                    retVal = PMHALVideopllGetHSDivider(videopllId,
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
                hsDiv = 1U;
            }
            printf("Multiplier   = %d\n", multi);
            printf("Divider      = %d\n", divider);
            printf("Post Divider = %d\n", hsDiv);
#else
            retVal = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSS,
                                     PMHAL_PRCM_CLK_VID_PIX_CLK, &setFreq);
            setFreq = setFreq / 1000U;
            if ((setFreq >= (i - 5 * i / 100U)) ||
                (setFreq <= (i + 5 * i / 100U)))
            {
                printf("Get Freq Success\n");
            }
            else
            {
                printf(
                    " Frequency did not match %d\n",
                    setFreq);
            }
            multi   = PMHALCMDpllGetMultiplier(PMHAL_PRCM_DPLL_EVE_VID_DSP);
            divider = PMHALCMDpllGetDivider(PMHAL_PRCM_DPLL_EVE_VID_DSP);
            retVal  = PMHALCMDpllGetPostDiv(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                            &postDiv, 1U);
            printf("Multiplier   = %d\n", multi);
            printf("Divider      = %d\n", divider);
            printf("Post Divider = %d\n", postDiv.configValue);
#endif
        }
        else
        {
            printf("\n");
        }
    }

    return (pmErrCode_t) (retVal);
}

