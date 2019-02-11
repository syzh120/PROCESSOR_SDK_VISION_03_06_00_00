/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2018
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
 * \file    pmlib_videopll_data.c
 *
 * \brief   PMLIB Videopll Data Base .
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pmlib_videopll_data.h"
#include "pm_utils.h"
#include "pmhal_cm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID         (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

const uint64_t         gPmlibPllMinmMaxVal[PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS
][
    PMLIB_VIDEOPLL_FEAT_ATTRIBUTES_OF_PARAMS] =
{
    /* PixelClock*/
    {1U,        209250000U                 },
    /* RefClock. Should be in range of 0.5 to 2.5 MHz*/
    {150000U,   52000000U                  },
    /* DcoFrequency. Range of 40 to 280 MHz*/
    {40000000U, 2800000000U                },
    /* Divider value range */
    {1U,        ((uint64_t) 1U << 7U)      },
    /* Multiplier value range */
    {2U,        ((uint64_t) 1U << 11U) - 1U},
    /* hsDivider Range.*/
    {1U,        ((uint64_t) 1U << 6U) - 1U },
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Table containing pre calculated values of the divider and multipliers */
/* The values in the table for divider are N-1 */

const videopllConfig_t gVidPllPreCalcTbl[] =
{
    {81000U,  162U, 7U,  5U,  1U},
    {54000U,  27U,  0U,  10U, 1U},
    {27000U,  27U,  0U,  10U, 2U},
    {195000U, 39U,  1U,  2U,  2U},
    {192000U, 48U,  1U,  5U,  1U},
    {65000U,  65U,  0U,  10U, 2U},
    {29232U,  44U,  14U, 1U,  2U},
    {149000U, 149U, 3U,  5U,  1U},
    {74500U,  149U, 3U,  5U,  2U}
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API verifies gets the Video Params
 *        viz multiplier divider and HS Divider
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param videopllId      Video PLL Id.
 * \param freq            Frequency for which params need to be calculated.
 * \param maxOrMinMN      This parameter allows the API to calculate the
 *                        maximum value of M and N for the given frequency or
 *                        minimum value of M and N for the given frequency.
 *                        0U - Minimum value of M and N.
 *                        1U - Maximum value of M and N.
 * \param pllConf         VideoPll configuration structure.
 * \param isUsed          VideoPll is used for DSP or EVE.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateParams(pmhalPrcmNodeId_t videopllId,
                                            uint32_t          freq,
                                            uint32_t          maxOrMinMN,
                                            videopllConfig_t *pllConf,
                                            uint32_t          isUsed);

/**
 * \brief This API returns the divider round up value
 *
 * \param n         Values to be rounded off
 * \param d         nearest value to be rounded to.
 *
 * \retval uint32_t value of n rounded to nearest d
 *
 */
static uint32_t PmlibVideopllDivRoundUp(uint32_t n, uint32_t d);

/**
 * \brief This API returns the minimum of two value
 *
 * \param a         input parameter A
 * \param b         input parameter B
 *
 * \retval uint32_t value minimum of A and B
 *
 */
static uint32_t PmlibVideopllMinCalc(uint32_t a, uint32_t b);

/**
 * \brief This API returns the maximum of two value
 *
 * \param a         input parameter A
 * \param b         input parameter B
 *
 * \retval uint32_t value Maximum of A and B
 *
 */
static uint32_t PmlibVideopllMaxCalc(uint32_t a, uint32_t b);

/**
 * \brief This API returns the maximum value of Video pll config params
 *
 * \param index     index of the parameter which is to be got.
 *
 * \retval uint32_t value Maximum of parameter
 *
 */
static uint32_t PmlibVideopllGetParamMax(uint32_t index);

/**
 * \brief This API returns the minimum value of Video pll config params
 *
 * \param index     index of the parameter which is to be got.
 *
 * \retval uint32_t value minimum of parameter
 *
 */
static uint32_t PmlibVideopllGetParamMin(uint32_t index);

/**
 * \brief This API verifies gets the Video Params
 *        viz multiplier
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param videopllId      Video Pll Id.
 * \param clkin           Input clock frequency.
 * \param refClock        Reference clock frequency after div by N.
 * \param freq            Frequency for which params need to be calculated.
 * \param pllConf         VideoPll configuration structure which is updated.
 * \param maxOrMinMN      This parameter allows the API to calculate the
 *                        maximum value of M and N for the given frequency or
 *                        minimum value of M and N for the given frequency.
 *                        0U - Minimum value of M and N.
 *                        1U - Maximum value of M and N.
 * \param isUsed          VideoPll is used by another module.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateM(pmhalPrcmNodeId_t videopllId,
                                       uint32_t          clkin,
                                       uint32_t          refClock,
                                       uint32_t          freq,
                                       videopllConfig_t *pllConf,
                                       uint32_t          maxOrMinMN,
                                       uint32_t         *pllDeviation,
                                       uint32_t          isUsed);

/**
 * \brief This API verifies gets the Video Params
 *        viz HS Divider
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param freq            Frequency for which params need to be calculated.
 *
 * \param pllConf         VideoPll configuration structure which is updated.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateHSD(uint32_t          clkin,
                                         uint32_t          outputPll,
                                         uint32_t          freq,
                                         videopllConfig_t *pllConf,
                                         uint32_t         *pllDeviation);
/**
 * \brief This API verifies if the video PLL is being used for other modules.
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param videopllId        Video PLL Id to check.
 *
 * \retval isUsed           1 - If being Used, 0 - Otherwise
 */
static uint32_t PmlibVideopllUsed(pmhalPrcmNodeId_t videopllId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PmlibVideopllGetpllStructure(pmhalPrcmNodeId_t      videopllId,
                                     uint32_t               freq,
                                     uint32_t               maxOrMinMN,
                                     pmhalPrcmDpllConfig_t *pllParams,
                                     uint32_t              *postDivider)
{
    int32_t          retVal    = PM_FAIL;
    uint32_t         configNum = 0U;
    uint32_t         cnt, postdiv;
    videopllConfig_t videoPllConfVal;
    uint32_t         isUsed = 0U;
    uint32_t         breakFromLoop = 0U;

    if (NULL != pllParams)
    {
        isUsed = PmlibVideopllUsed(videopllId);
        /* Try searching for the frequency in the pre calculated table*/
        for (configNum = 0U;
             configNum < PM_UTIL_VSIZE_TYPE(gVidPllPreCalcTbl, videopllConfig_t);
             configNum++)
        {
            if (freq == gVidPllPreCalcTbl[configNum].frequency)
            {
                if (isUsed == 1U)
                {
                    /* Check if the programmed M2, M and N values match with
                     * pre calculated table.
                     */
                    pllParams->postDivConfList[0].postDivId =
                        PMHAL_PRCM_DPLL_POST_DIV_M2;
                    if ((PMHALCMDpllGetMultiplier(videopllId) ==
                        gVidPllPreCalcTbl[configNum].multiplier) &&
                        (PMHALCMDpllGetDivider(videopllId) ==
                        gVidPllPreCalcTbl[configNum].divider))
                    {
                        retVal = PMHALCMDpllGetPostDiv(videopllId,
                            pllParams->postDivConfList, 1U);
                        if (retVal == PM_SUCCESS)
                        {
                            if (pllParams->postDivConfList[0].configValue ==
                                gVidPllPreCalcTbl[configNum].m2Divider)
                            {
                                /* All match. Can go ahead */
                                pllParams->multiplier = gVidPllPreCalcTbl[configNum].
                                            multiplier;
                                pllParams->fracMultiplier = 0U;
                                pllParams->divider        = gVidPllPreCalcTbl[configNum].
                                                            divider;
                                pllParams->dutyCycleCorrector           = 0U;
                                pllParams->postDivConfList[0].postDivId =
                                    PMHAL_PRCM_DPLL_POST_DIV_M2;
                                pllParams->postDivConfList[0].configValue =
                                    gVidPllPreCalcTbl[configNum].
                                    m2Divider;
                                *postDivider = gVidPllPreCalcTbl[configNum].postDivider;
                                pllParams->maxPostDivElems =
                                    PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID;
                                retVal = PM_SUCCESS;
                                breakFromLoop = 1U;
                            }
                            else
                            {
                                /* No Match found */
                                retVal    = PM_FAIL;
                            }
                        }
                    }
                }
                else
                {
                    pllParams->multiplier = gVidPllPreCalcTbl[configNum].
                                            multiplier;
                    pllParams->fracMultiplier = 0U;
                    pllParams->divider        = gVidPllPreCalcTbl[configNum].
                                                divider;
                    pllParams->dutyCycleCorrector           = 0U;
                    pllParams->postDivConfList[0].postDivId =
                        PMHAL_PRCM_DPLL_POST_DIV_M2;
                    pllParams->postDivConfList[0].configValue =
                        gVidPllPreCalcTbl[configNum].
                        m2Divider;
                    *postDivider = gVidPllPreCalcTbl[configNum].postDivider;
                    pllParams->maxPostDivElems =
                        PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID;
                    retVal = PM_SUCCESS;
                    breakFromLoop = 1U;
                }
            }
            if (breakFromLoop == 1U)
            {
                break;
            }
        }

        if (PM_SUCCESS != retVal)
        {
            /*  If value not found in the table, calculate the multipliers and
             *  dividers, Tda3xx has a post divider, valid values are 1,2 and 4
             *  so if multipliers and dividers are not found then will search
             *  for reqFreq * 2 and repeat the same for reqFreq *4 if the
             *  previous one fails to get the dividers.
             */
            for (cnt = 0; cnt < 3U; cnt++)
            {
                postdiv = ((uint32_t) 0x1U << cnt);
                retVal  = PmlibVideopllCalculateParams(videopllId,
                                                       (freq * 1000U * postdiv),
                                                       maxOrMinMN,
                                                       &videoPllConfVal,
                                                       isUsed);
                if (retVal == PM_SUCCESS)
                {
                    break;
                }
            }

            if (PM_SUCCESS == retVal)
            {
                pllParams->multiplier     = videoPllConfVal.multiplier;
                pllParams->fracMultiplier = 0U;
                pllParams->divider        = videoPllConfVal.divider - 1U;

                pllParams->postDivConfList[0].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M2;
                pllParams->postDivConfList[0].configValue =
                    videoPllConfVal.m2Divider;
                if (NULL != postDivider)
                {
                    *postDivider = postdiv;
                }
                pllParams->maxPostDivElems = 1U;
            }
        }
    }
    return retVal;
}

static int32_t PmlibVideopllCalculateParams(pmhalPrcmNodeId_t videopllId,
                                            uint32_t          freq,
                                            uint32_t          maxOrMinMN,
                                            videopllConfig_t *pllConf,
                                            uint32_t          isUsed)
{
    int32_t  retVal       = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t pllDeviation = 999U;
    uint32_t refClockHwMax;
    uint32_t refClockHwMin;
    uint32_t regn, regnStart, regnStop, fractionalFreq;
    uint32_t clkin;
    uint32_t regnMax;
    uint32_t refClock;

    refClockHwMax = PmlibVideopllGetParamMax(PMLIB_VIDEOPLL_FEAT_PARAM_DSS_FINT);
    refClockHwMin = PmlibVideopllGetParamMin(PMLIB_VIDEOPLL_FEAT_PARAM_DSS_FINT);
    regnMax       = PmlibVideopllGetParamMax(PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGN);
    clkin         = PMHALCMGetSysClockFreq() * 1000U;

    if (NULL != pllConf)
    {
        if (isUsed == 1U)
        {
            regnStart = PMHALCMDpllGetDivider(videopllId);
            regnStop = regnStart;
        }
        else
        {
            regnStart = PmlibVideopllMaxCalc(
                (uint32_t) 1U, (uint32_t) PmlibVideopllDivRoundUp(clkin,
                                                                refClockHwMax));
            regnStop = PmlibVideopllMinCalc((clkin / refClockHwMin), regnMax);
        }
        /* Calculate maximum M and N values for the given frequency */
        if ((uint32_t) maxOrMinMN ==
            (uint32_t) PMLIB_VIDEO_PLL_CALC_MAX_MN)
        {
            /* Iterate over all the possible values of n */
            for (regn = regnStop; regn >= regnStart; regn--)
            {
                if (regn != 0U)
                {
                    /* ref clock for a particular value of N*/
                    refClock = clkin / regn;
                    /* Calculate M and m2Divider values for this N*/
                    retVal = PmlibVideopllCalculateM(videopllId, clkin,
                                                     refClock,
                                                     freq,
                                                     pllConf,
                                                     maxOrMinMN,
                                                     &pllDeviation,
                                                     isUsed);
                    /* If we are able to find multiplier and m2Divider
                     * with deviation less then current, update N*/
                    if (PM_SUCCESS == retVal)
                    {
                        pllConf->divider = regn;
                        retVal           = PM_SUCCESS;
                        if (pllDeviation == 0U)
                        {
                            /* m and n value are obtained
                             * verify its not a fractional value.
                             * if found fractional dont break calculate */

                            fractionalFreq =
                                (((clkin / 1000U) * 2U * pllConf->multiplier) %
                                 (pllConf->divider * pllConf->m2Divider));
                            if (fractionalFreq == 0U)
                            {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    retVal = PM_BADARGS;
                }
            }
        }
        else
        {
            /* Calculate minimum M and N values for the given frequency */
            /* Iterate over all the possible values of n */
            for (regn = regnStart; regn <= regnStop; regn++)
            {
                /* ref clock for a particular value of N*/
                refClock = clkin / regn;
                /* Calculate M and m2Divider values for this N*/
                retVal = PmlibVideopllCalculateM(videopllId, clkin,
                                                 refClock,
                                                 freq,
                                                 pllConf,
                                                 maxOrMinMN,
                                                 &pllDeviation,
                                                 isUsed);
                /* If we are able to find multiplier and m2Divider
                 * with deviation less then current, update N*/
                if (PM_SUCCESS == retVal)
                {
                    pllConf->divider = regn;
                    retVal           = PM_SUCCESS;
                    if (pllDeviation == 0U)
                    {
                        /* m and n value are obtained
                         * verify its not a fractional value.
                         * if found fractional dont break calculate */

                        fractionalFreq =
                            (((clkin / 1000U) * 2U * pllConf->multiplier) %
                             (pllConf->divider * pllConf->m2Divider));
                        if (fractionalFreq == 0U)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    if ((isUsed == 1U) && (retVal == PM_SUCCESS))
    {
        pmhalPrcmNodeId_t parentNodeId;
        pmhalPrcmPllPostDivValue_t postDivConfig;
        retVal = (int32_t)PMHALCMMuxParentGet
                             (PMHAL_PRCM_MUX_EVE_CLK_MUX,  &parentNodeId);
        if (retVal == (int32_t)PM_SUCCESS)
        {
            if (parentNodeId == videopllId)
            {
                /* Extra Check required if the clock is used by EVE */
                postDivConfig.postDivId = PMHAL_PRCM_DPLL_POST_DIV_M2;
                retVal = PMHALCMDpllGetPostDiv(videopllId,
                            &postDivConfig, 1U);
                if (postDivConfig.configValue != pllConf->m2Divider)
                {
                    retVal = PM_VIDEOPLL_CALC_PARAMS_FAILED;
                }
            }
        }
    }
    return retVal;
}

static int32_t PmlibVideopllCalculateM(pmhalPrcmNodeId_t videopllId,
                                       uint32_t          clkin,
                                       uint32_t          refClock,
                                       uint32_t          freq,
                                       videopllConfig_t *pllConf,
                                       uint32_t          maxOrMinMN,
                                       uint32_t         *pllDeviation,
                                       uint32_t          isUsed)
{
    int32_t  retVal = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t pllMin = PmlibVideopllGetParamMin(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_DCOFREQ);
    uint32_t pllMax = PmlibVideopllGetParamMax(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_DCOFREQ);
    uint32_t regmMax = PmlibVideopllGetParamMax(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGM);
    uint32_t regmMin = PmlibVideopllGetParamMin(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGM);
    uint32_t regmStart, regmStop, regm;
    uint32_t outputPll;
    pllMin = PmlibVideopllMaxCalc(pllMin, freq);
    /* Output should be in the range of 40 to 2800MHz*/
    if (isUsed == 1U)
    {
        regmStart = PMHALCMDpllGetMultiplier(videopllId);
        regmStop = regmStart;
    }
    else
    {
        regmStart = PmlibVideopllMaxCalc(
                PmlibVideopllDivRoundUp(PmlibVideopllDivRoundUp(
                    pllMin, refClock), (uint32_t) 2U), regmMin);
        regmStop = PmlibVideopllMinCalc(pllMax / (refClock * 2U), regmMax);
    }
    /* Calculate maximum M and N values for the given frequency */
    if ((uint32_t) maxOrMinMN ==
        (uint32_t) PMLIB_VIDEO_PLL_CALC_MAX_MN)
    {
        /* For each possible value of M, calculate HSD*/
        for (regm = regmStop; regm >= regmStart; regm--)
        {
            outputPll = refClock * 2U * regm;
            /* Calculate m2Divider corrosponding to this value of M */
            retVal = PmlibVideopllCalculateHSD(clkin,
                                               outputPll,
                                               freq,
                                               pllConf,
                                               pllDeviation);
            /* If we m2Divider found with deviation less then the existing,
             * update M*/
            if (PM_SUCCESS == retVal)
            {
                pllConf->multiplier = regm;
                retVal = PM_SUCCESS;
                if (*pllDeviation == 0U)
                {
                    break;
                }
            }
        }
    }
    else
    {
        /* Calculate minimum M and N values for the given frequency */
        /* For each possible value of M, calculate HSD*/
        for (regm = regmStart; regm <= regmStop; regm++)
        {
            outputPll = refClock * 2U * regm;
            /* Calculate m2Divider corrosponding to this value of M */
            retVal = PmlibVideopllCalculateHSD(clkin,
                                               outputPll,
                                               freq,
                                               pllConf,
                                               pllDeviation);
            /* If we m2Divider found with deviation less then the existing,
             * update M*/
            if (PM_SUCCESS == retVal)
            {
                pllConf->multiplier = regm;
                retVal = PM_SUCCESS;
                if (*pllDeviation == 0U)
                {
                    break;
                }
            }
        }
    }
    return retVal;
}

static int32_t PmlibVideopllCalculateHSD(uint32_t          clkin,
                                         uint32_t          outputPll,
                                         uint32_t          freq,
                                         videopllConfig_t *pllConf,
                                         uint32_t         *pllDeviation)
{
    int32_t  retVal = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t hsdStart, hsdStop, hsd, deviation;
    uint32_t outMax = PmlibVideopllGetParamMax(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_PCLK);
    uint32_t outMin = PmlibVideopllGetParamMin(
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_PCLK);
    hsdStart = PmlibVideopllMaxCalc(
        (outputPll / outMax),
        PmlibVideopllGetParamMin(PMLIB_VIDEOPLL_FEAT_PARAM_DSS_HSDIV));
    hsdStop = PmlibVideopllMinCalc(
        (outputPll / outMin),
        PmlibVideopllGetParamMax(PMLIB_VIDEOPLL_FEAT_PARAM_DSS_HSDIV));
    /* Calculate the HS Divider required for output PLL*/
    hsd       = outputPll / freq;
    deviation = outputPll - (freq * hsd);
    /* If the deviation is less then the current deviation, update the
     *m2Divider, M and N*/
    if ((deviation < (*pllDeviation)) || (deviation == 0U))
    {
        (*pllDeviation)    = deviation;
        pllConf->m2Divider = hsd;
        /* m2Divider should be in the required range*/

        if ((pllConf->m2Divider < hsdStop) &&
            (pllConf->m2Divider > hsdStart) &&
            ((pllConf->m2Divider % 2) == 0))
        {
            pllConf->m2Divider = pllConf->m2Divider / 2U;
            retVal = PM_SUCCESS;
        }
    }
    return retVal;
}

static uint32_t PmlibVideopllDivRoundUp(uint32_t n, uint32_t d)
{
    return (((n + d) - 1U) / d);
}

static uint32_t PmlibVideopllMinCalc(uint32_t a, uint32_t b)
{
    return ((a) > (b) ? (b) : (a));
}

static uint32_t PmlibVideopllMaxCalc(uint32_t a, uint32_t b)
{
    return ((a) > (b) ? (a) : (b));
}

static uint32_t PmlibVideopllGetParamMin(uint32_t index)
{
    uint32_t retval = 0;
    if (index < PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS)
    {
        retval = (uint32_t) gPmlibPllMinmMaxVal[index][0];
    }
    return retval;
}

static uint32_t PmlibVideopllGetParamMax(uint32_t index)
{
    uint32_t retval = 0;
    if (index < PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS)
    {
        retval = (uint32_t) gPmlibPllMinmMaxVal[index][1];
    }
    return retval;
}

static uint32_t PmlibVideopllUsed(pmhalPrcmNodeId_t videopllId)
{
    uint32_t isUsed = 0U;
    pmhalPrcmNodeId_t parentNodeId;
    int32_t retVal = (int32_t)PMHALCMMuxParentGet
                             (PMHAL_PRCM_MUX_DSP_GFCLK_MUX, &parentNodeId);
    if (retVal == (int32_t)PM_SUCCESS)
    {
        if (parentNodeId == videopllId)
        {
            isUsed = 1U;
        }
    }
    retVal = (int32_t)PMHALCMMuxParentGet
                             (PMHAL_PRCM_MUX_EVE_CLK_MUX,  &parentNodeId);
    if (retVal == (int32_t)PM_SUCCESS)
    {
        if (parentNodeId == videopllId)
        {
            isUsed = 1U;
        }
    }
    return isUsed;
}
