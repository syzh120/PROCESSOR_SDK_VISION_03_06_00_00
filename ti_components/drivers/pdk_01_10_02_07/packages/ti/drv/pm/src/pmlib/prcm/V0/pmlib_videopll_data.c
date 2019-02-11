/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

/*  none */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**< Minimum and Maximun range of Videopll feat param Elements  */
const uint64_t         gPmlibPllMinmMaxVal
    [PMHAL_PRCM_VIDEOPLL_COUNT - PMHAL_PRCM_VIDEOPLL_MIN]
    [PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS]
    [PMLIB_VIDEOPLL_FEAT_ATTRIBUTES_OF_PARAMS] =
{
    {/* PixelClock*/
        {1300U,      2800000000U               },
        /* RefClock. Should be in range of 0.15 to 52 MHz*/
        {150000U,   52000000U                  },
        /* DcoFrequency. Range of 40 to 280 MHz*/
        {40000000U, 2800000000U                },
        /* Divider value range */
        {1U,        ((uint64_t) 1U << 8U)      },
        /* Multiplier value range */
        {2U,        ((uint64_t) 1U << 11U) - 1U},
        /* hdDivider Range.*/
        {1U,        ((uint64_t) 1U << 5U)      }
    },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {/* PixelClock*/
        {1300U,      2800000000U               },
        /* RefClock. Should be in range of 0.15 to 52 MHz*/
        {150000U,   52000000U                  },
        /* DcoFrequency. Range of 40 to 280 MHz*/
        {40000000U, 2800000000U                },
        /* Divider value range */
        {1U,        ((uint64_t) 1U << 8U)      },
        /* Multiplier value range */
        {2U,        ((uint64_t) 1U << 11U) - 1U},
        /* hdDivider Range.*/
        {1U,        ((uint64_t) 1U << 5U)      }
    },
#endif
    {   /* PixelClock*/
        {20000000U, 2500000000U               },
        /* RefClock. Should be in range of 0.62 to 2.5 MHz*/
        {620000U,   2500000U                  },
        /* DcoFrequency. Range of 750 MHz  to 2500 MHz*/
        {750000000U, 2500000000U              },
        /* Divider value range */
        {1U,        ((uint64_t) 1U << 8U)     },
        /* Multiplier value range */
        {2U,        ((uint64_t) 1U << 12U) - 1U},
        /* hdDivider Range.*/
        {1U,        ((uint64_t) 1U << 7U) - 1U }
    }
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Table containing pre calculated values of the divider and multipliers */
const videopllConfig_t gVidPllPreCalcTbl[] =
{
    {116928U, 1637U, 40U, 14U, 0U},
    {207900U, 421U,  8U,  8U , 0U}
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API gets the Video Params
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
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateParams(pmhalPrcmNodeId_t videopllId,
                                            uint32_t          freq,
                                            uint32_t          maxOrMinMN,
                                            videopllConfig_t *pllConf);

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
 * \param pllId     PLL index to get the right parameters.
 * \param index     index of the parameter which is to be got.
 *
 * \retval uint32_t value Maximum of parameter
 *
 */
static uint32_t PmlibVideopllGetParamMax(uint32_t pllId, uint32_t index);

/**
 * \brief This API returns the minimum value of Video pll config params
 *
 * \param pllId     PLL index to get the right parameters.
 * \param index     index of the parameter which is to be got.
 *
 * \retval uint32_t value minimum of parameter
 *
 */
static uint32_t PmlibVideopllGetParamMin(uint32_t pllId, uint32_t index);

/**
 * \brief This API verifies gets the Video Params
 *        viz multiplier
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param videopllId      Video PLL ID
 * \param clkin           Input clock frequency.
 * \param regn            Value of N+1.
 * \param freq            Frequency for which params need to be calculated.
 * \param pllConf         VideoPll configuration structure which is updated.
 * \param maxOrMinMN      This parameter allows the API to calculate the
 *                        maximum value of M and N for the given frequency or
 *                        minimum value of M and N for the given frequency.
 *                        0U - Minimum value of M and N.
 *                        1U - Maximum value of M and N.
 * \param pllDeviation    Deviation from requested frequency and current
 *                        calculated frequency.
 *
 * \retval errorStatus    Status of the API call. Can be any of the following,
 *         PM_SUCCESS     Indicates the operation is success
 *         PM_FAIL        Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateM(pmhalPrcmNodeId_t      videopllId,
                                       uint32_t          clkin,
                                       uint32_t          regn,
                                       uint32_t          freq,
                                       videopllConfig_t *pllConf,
                                       uint32_t          maxOrMinMN,
                                       uint32_t         *pllDeviation);

/**
 * \brief This API verifies gets the Video Params
 *        viz HS Divider
 *
 *  NOTE : The m,n and HS Divider returned from the api may not
 *         be optimal and may have jitter.
 *
 * \param videopllId      Video PLL ID
 * \param clkin           Clock input frequency.
 * \param regn            Value of divider
 * \param regm            Value of multiplier
 * \param outputPll       Value of clock output of DCOLDO.
 * \param freq            Frequency for which params need to be calculated.
 * \param pllConf         VideoPll configuration structure which is updated.
 * \param pllDeviation    Deviation from desired frequency.
 *
 * \retval errorStatus    Status of the API call. Can be any of the following,
 *         PM_SUCCESS     Indicates the operation is success
 *         PM_FAIL        Indicates the API failed for desired functionality
 */
static int32_t PmlibVideopllCalculateHSD(pmhalPrcmNodeId_t videopllId,
                                         uint32_t          clkin,
                                         uint32_t          regn,
                                         uint32_t          regm,
                                         uint64_t          outputPll,
                                         uint32_t          freq,
                                         videopllConfig_t *pllConf,
                                         uint32_t         *pllDeviation);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PmlibVideopllGetpllStructure(pmhalPrcmNodeId_t      videopllId,
                                     uint32_t               freq,
                                     uint32_t               maxOrMinMN,
                                     pmhalVideopllConfig_t *pVideoPllConfigure)
{
    int32_t          retVal          = PM_FAIL;
    uint32_t         configNum       = 0U;
    videopllConfig_t videoPllConfVal = {0};

    if (NULL != pVideoPllConfigure)
    {
        /* Try searching for the frequency in the pre calculated table*/
        for (configNum = 0U;
             configNum < PM_UTIL_VSIZE_TYPE(gVidPllPreCalcTbl, videopllConfig_t);
             configNum++)
        {
            if (freq == gVidPllPreCalcTbl[configNum].frequency)
            {
                pVideoPllConfigure->multiplier = gVidPllPreCalcTbl[configNum].
                                                 multiplier;
                pVideoPllConfigure->divider =
                    gVidPllPreCalcTbl[configNum].
                    divider;
                pVideoPllConfigure->fracM = gVidPllPreCalcTbl[configNum].fracM;
                pVideoPllConfigure->postDivConfList[0].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M4;
                pVideoPllConfigure->postDivConfList[0].configValue =
                    gVidPllPreCalcTbl[configNum].
                    m2Divider;
                pVideoPllConfigure->postDivConfList[1].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M6;
                pVideoPllConfigure->postDivConfList[1].configValue =
                    gVidPllPreCalcTbl[configNum].m2Divider;
                pVideoPllConfigure->maxPostDivElems =
                    PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID;

                retVal = PM_SUCCESS;
                break;
            }
        }

        if (PM_SUCCESS != retVal)
        {
            retVal = PmlibVideopllCalculateParams(videopllId,
                                                  freq * 1000U, maxOrMinMN,
                                                  &videoPllConfVal);

            if (PM_SUCCESS == retVal)
            {
                pVideoPllConfigure->multiplier = videoPllConfVal.multiplier;
                pVideoPllConfigure->fracM = videoPllConfVal.fracM;
                pVideoPllConfigure->divider    = videoPllConfVal.divider;

                pVideoPllConfigure->postDivConfList[0].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M4;
                pVideoPllConfigure->postDivConfList[0].configValue =
                    videoPllConfVal.m2Divider;
                pVideoPllConfigure->postDivConfList[1].postDivId =
                    PMHAL_PRCM_DPLL_POST_DIV_M6;
                pVideoPllConfigure->postDivConfList[1].configValue =
                    videoPllConfVal.m2Divider;
                pVideoPllConfigure->maxPostDivElems =
                    PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID;
            }
        }
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

static int32_t PmlibVideopllCalculateParams(pmhalPrcmNodeId_t videopllId,
                                            uint32_t          freq,
                                            uint32_t          maxOrMinMN,
                                            videopllConfig_t *pllConf)
{
    int32_t  retVal       = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t pllDeviation = 999U;
    uint32_t refClockHwMax;
    uint32_t refClockHwMin;
    uint32_t regn, regnStart, regnStop, fractionalFreq;
    uint32_t clkin;
    uint32_t regnMax;
    refClockHwMax = PmlibVideopllGetParamMax(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_FINT);
    refClockHwMin = PmlibVideopllGetParamMin(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_FINT);

    regnMax       = PmlibVideopllGetParamMax(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGN);
    clkin         = PMHALCMGetSysClockFreq() * 1000U;

    if ((refClockHwMax != 0U) && (refClockHwMin != 0U))
    {
        regnStart = PmlibVideopllMaxCalc(
            ((uint32_t) PmlibVideopllGetParamMin(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGN) + 1U),
        (uint32_t) PmlibVideopllDivRoundUp(clkin, refClockHwMax));
        regnStop = PmlibVideopllMinCalc(clkin / refClockHwMin, regnMax);
        if (NULL != pllConf)
        {
            /* Calculate maximum M and N values for the given frequency */
            if ((uint32_t) maxOrMinMN ==
                (uint32_t) PMLIB_VIDEO_PLL_CALC_MAX_MN)
            {
                /* Iterate over all the possible values of n */
                for (regn = regnStop; regn >= regnStart; regn--)
                {
                    if(regn != 0U)
                    {
                        /* Calculate M and m2Divider values for this N*/
                        retVal = PmlibVideopllCalculateM(videopllId, clkin,
                                                        regn,
                                                        freq, pllConf, maxOrMinMN,
                                                        &pllDeviation);
                        /* If we are able to find multiplier and m2Divider
                        * with deviation less then current, update N*/
                        if (PM_SUCCESS == retVal)
                        {
                            pllConf->divider = regn;
                            retVal           = PM_SUCCESS;
                            if (pllDeviation == 0U)
                            {
                                if (videopllId != PMHAL_PRCM_VIDEOPLL_HDMI)
                                {
                                    /* m and n value are obtained
                                    * verify its not a fractional value.
                                    * if found fractional dont break calculate */
                                    fractionalFreq =
                                        (((clkin / 1000U) * 2U * pllConf->multiplier) %
                                        (pllConf->divider * pllConf->m2Divider));
                                }
                                else
                                {
                                    Double mul = (Double)pllConf->multiplier +
                                                (((Double)pllConf->fracM)/262144.0);
                                    Double numerator = ((Double)clkin / 1000.0) * mul;
                                    fractionalFreq =
                                    (uint32_t)(numerator) %
                                    (pllConf->divider * pllConf->m2Divider);
                                }
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
                    /* Calculate M and m2Divider values for this N*/
                    retVal = PmlibVideopllCalculateM(videopllId, clkin,
                                                    regn,
                                                    freq,
                                                    pllConf,
                                                    maxOrMinMN,
                                                    &pllDeviation);
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
    }
    else
    {
        retVal = PM_BADARGS;
    }

    return retVal;
}

static int32_t PmlibVideopllCalculateM(pmhalPrcmNodeId_t videopllId,
                                       uint32_t          clkin,
                                       uint32_t          regn,
                                       uint32_t          freq,
                                       videopllConfig_t *pllConf,
                                       uint32_t          maxOrMinMN,
                                       uint32_t         *pllDeviation)
{
    int32_t  retVal = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t pllMin = PmlibVideopllGetParamMin(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_DCOFREQ);
    uint32_t pllMax = PmlibVideopllGetParamMax(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_DCOFREQ);
    uint32_t regmMax = PmlibVideopllGetParamMax(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGM);
    uint32_t regmMin = PmlibVideopllGetParamMin(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGM);
    uint32_t regmStart, regmStop, regm;
    uint64_t outputPll;
    uint32_t refClock;

    /* ref clock for a particular value of N*/
    refClock = clkin / regn;

    pllMin = PmlibVideopllMaxCalc(pllMin, freq);
    if (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI)
    {
        regmStart =
        PmlibVideopllMaxCalc(PmlibVideopllDivRoundUp(pllMin, refClock),
                             regmMin);
        regmStop = PmlibVideopllMinCalc(pllMax / refClock, regmMax);
    }
    else
    {
        /* Output should be in the range of 40 to 2800MHz */
        regmStart =
            PmlibVideopllMaxCalc(PmlibVideopllDivRoundUp(PmlibVideopllDivRoundUp(
                                                             pllMin,
                                                             refClock),
                                                         (uint32_t) 2U),
                                 regmMin);
        regmStop = PmlibVideopllMinCalc(pllMax / (refClock * 2U), regmMax);
    }
    /* Calculate maximum M and N values for the given frequency */
    if ((uint32_t) maxOrMinMN ==
        (uint32_t) PMLIB_VIDEO_PLL_CALC_MAX_MN)
    {
        /* For each possible value of M, calculate HSD*/
        for (regm = regmStop; regm >= regmStart; regm--)
        {
            outputPll = (uint64_t) refClock * (uint64_t) 2U * (uint64_t) regm;
            if (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI)
            {
                outputPll = (uint64_t) outputPll/ (uint64_t) 2U;
            }
            /* Calculate m2Divider corrosponding to this value of M */
            retVal = PmlibVideopllCalculateHSD(videopllId, clkin,
                                               regn, regm,
                                               outputPll, freq,
                                               pllConf, pllDeviation);
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
            outputPll = (uint64_t) refClock * (uint64_t) 2U * (uint64_t) regm;
            if (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI)
            {
                outputPll = (uint64_t) outputPll/ (uint64_t) 2U;
            }
            /* Calculate m2Divider corrosponding to this value of M */
            retVal = PmlibVideopllCalculateHSD(videopllId, clkin,
                                           regn, regm,
                                           outputPll, freq,
                                           pllConf, pllDeviation);
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

static int32_t PmlibVideopllCalculateHSD(pmhalPrcmNodeId_t videopllId,
                                         uint32_t          clkin,
                                         uint32_t          regn,
                                         uint32_t          regm,
                                         uint64_t          outputPll,
                                         uint32_t          freq,
                                         videopllConfig_t *pllConf,
                                         uint32_t         *pllDeviation)
{
    int32_t  retVal = PM_VIDEOPLL_CALC_PARAMS_FAILED;
    uint32_t hsdStart, hsdStop, hsd, deviation;
    uint32_t outMax = PmlibVideopllGetParamMax(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_PCLK);
    uint32_t outMin = PmlibVideopllGetParamMin(
                        videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
        PMLIB_VIDEOPLL_FEAT_PARAM_DSS_PCLK);
    if ((outMax != 0U) && (outMin != 0U))
    {
        hsdStart = PmlibVideopllMaxCalc(
            (uint32_t)(outputPll / (uint64_t)outMax),
            PmlibVideopllGetParamMin(
                            videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                            PMLIB_VIDEOPLL_FEAT_PARAM_DSS_HSDIV));
        hsdStop = PmlibVideopllMinCalc(
            (uint32_t)(outputPll / (uint64_t)outMin),
            PmlibVideopllGetParamMax(
                            videopllId - PMHAL_PRCM_VIDEOPLL_MIN,
                            PMLIB_VIDEOPLL_FEAT_PARAM_DSS_HSDIV));
        /* Calculate the HS Divider required for output PLL*/
        hsd       = (uint32_t)(outputPll / (uint64_t) freq);
        deviation = (uint32_t)(outputPll - (uint64_t)((uint64_t)freq * (uint64_t)hsd));
        /* If the deviation is less then the current deviation, update the
        *m2Divider, M and N*/
        if ((deviation < *pllDeviation) || (deviation == 0U))
        {
            *pllDeviation      = deviation;
            pllConf->m2Divider = hsd;
            pllConf->fracM     = 0U;
            /* m2Divider should be in the required range*/
            if ((pllConf->m2Divider <= hsdStop) && (pllConf->m2Divider >= hsdStart))
            {
                retVal = PM_SUCCESS;
            }
        }
        else
        {
            /* Calculate if a fractional M will satisfy this */
            if (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI)
            {
                uint32_t hsdLocal;
                /* Loop through +1 and -1 of the HSD to make sure that fractional calculation effect on
                * the output PLL does not impact the final result.
                */
                for (hsdLocal = hsd - 1U; hsdLocal < (hsd + 2U); hsdLocal++)
                {
                    Double fregm = ((Double)(freq)/(Double)clkin) * (Double)hsdLocal * (Double)regn;
                    uint32_t iregm = (uint32_t) fregm;
                    if (iregm == regm)
                    {
                        /* Multiply the difference by 2 ^ 18 */
                        uint32_t intRegm = (uint32_t)fregm;
                        Double fracMTemp = (fregm - (Double)intRegm);
                        Double fracMfloat = fracMTemp * (Double) 262144.0;
                        uint32_t  fracMint = (uint32_t) fracMfloat;
                        Double diff = fracMfloat - (Double)fracMint;
                        diff = diff * (Double)100000.0;
                        uint32_t diffIntFiveDecimal = (uint32_t)diff;
                        if (diffIntFiveDecimal == 0U)
                        {
                            *pllDeviation      = 0U;
                            pllConf->m2Divider = hsdLocal;
                            pllConf->fracM     = fracMint;
                            if ((pllConf->m2Divider <= hsdStop) && (pllConf->m2Divider >= hsdStart) &&
                                (pllConf->fracM <= HDMI_PLL_CONFIGURATION4_REGM_F_MASK))
                            {
                                retVal = PM_SUCCESS;
                                break;
                            }
                        }
                    }
                }
            }
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

static uint32_t PmlibVideopllGetParamMin(uint32_t pllId, uint32_t index)
{
    uint32_t retval = 0;
    if ((index < PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS) &&
    (pllId < (PMHAL_PRCM_VIDEOPLL_COUNT - PMHAL_PRCM_VIDEOPLL_MIN)))
    {
        retval = (uint32_t) gPmlibPllMinmMaxVal[pllId][index][0];
    }
    return retval;
}

static uint32_t PmlibVideopllGetParamMax(uint32_t pllId, uint32_t index)
{
    uint32_t retval = 0;
    if ((index < PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS) &&
    (pllId < (PMHAL_PRCM_VIDEOPLL_COUNT - PMHAL_PRCM_VIDEOPLL_MIN)))
    {
        retval = (uint32_t) gPmlibPllMinmMaxVal[pllId][index][1];
    }
    return retval;
}

