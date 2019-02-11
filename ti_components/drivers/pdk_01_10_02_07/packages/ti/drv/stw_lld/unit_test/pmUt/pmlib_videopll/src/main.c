/*
 *  Copyright (C) 2014-2018 Texas Instruments Incorporated
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
 * \brief   Video Pll Lib API implementation test.
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define STEPSIZE (250U)

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

typedef struct
{
    pmlibVideoPllVenc_t   outputVenc;
    pmlibVideoPllClkSrc_t vencClkSrc;
} PmlibUtCombination;

typedef struct
{
    uint32_t   startFreq;
    uint32_t   stopFreq;
    uint32_t   stepFreq;
} PmlibUtFreqLimits;

static pmErrCode_t PmlibVaildateVideoPll()
{
    int32_t           retVal = PM_FAIL;
    uint32_t          i, maxOrMin;
    uint32_t          setFreq   = 0U;
    uint32_t          timeDelay = 0x00001000U;
    pmhalPrcmNodeId_t videopllId;
#if defined (SOC_TDA2XX)
PmlibUtCombination arrayInp[] =
{
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1}, /* VIDEOPLL1 */
    {PMLIB_VIDEOPLL_VENC_LCD2, PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3}, /* VIDEOPLL2 */
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI          }, /* HDMI      */
};
PmlibUtFreqLimits arrayLims[] =
{
    {1000U,  191750U , STEPSIZE    },
    {1000U,  191750U , STEPSIZE    },
    {20000U, 192000U , STEPSIZE    }
};
#elif defined (SOC_TDA2EX)
PmlibUtCombination arrayInp[] =
{
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1}, /* VIDEOPLL1 */
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI          }, /* HDMI      */
};
PmlibUtFreqLimits arrayLims[] =
{
    {1000U,  191750U , STEPSIZE  },
    {20000U, 192000U , STEPSIZE  }
};
#elif defined (SOC_TDA2PX)
PmlibUtCombination arrayInp[] =
{
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1}, /* VIDEOPLL1 */
    {PMLIB_VIDEOPLL_VENC_LCD2, PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3}, /* VIDEOPLL2 */
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI          }, /* HDMI      */
    {PMLIB_VIDEOPLL_VENC_LCD1, PMLIB_VIDEOPLL_CLKSRC_DPLL_SATA          }  /* SATA */
};
PmlibUtFreqLimits arrayLims[] =
{
   {1000U,  191750U , STEPSIZE },
   {1000U,  191750U , STEPSIZE },
   {20000U, 192000U  , STEPSIZE },
   {750000U,1995000U , 5000 }
};
#else
PmlibUtFreqLimits arrayLims[] =
{
    {1000U,  191750U , STEPSIZE }
};
#endif
    /* Register read and write for Loop Bandwidth */
#if defined (SOC_TDA2PX)
    for (videopllId = PMHAL_PRCM_VIDEOPLL_MIN;
         videopllId < PMHAL_PRCM_VIDEOPLL_COUNT;
         videopllId++)
    {
        pmhalPrcmLoopBwMode_t        mode;
        retVal = PMHALVideopllSetLoopBw(videopllId, PMHAL_PRCM_LOOP_BW_0p25x);
        if (retVal != PM_SUCCESS)
        {
            printf("Loop bandwidth Set Failed for PLL %d\n", videopllId);
        }
        else
        {
            retVal = PMHALVideopllGetLoopBw(videopllId, &mode);
            if ((retVal != PM_SUCCESS) || (mode != PMHAL_PRCM_LOOP_BW_0p25x))
            {
                printf("Loop bandwidth Set Failed for PLL %d\n", videopllId);
            }
            else
            {
                printf("Loop bandwidth Set Passed for PLL %d\n", videopllId);
            }
        }
    }
#endif

    for (videopllId = PMHAL_PRCM_VIDEOPLL_MIN;
         videopllId < PMHAL_PRCM_VIDEOPLL_COUNT;
         videopllId = (pmhalPrcmNodeId_t) ((uint32_t)videopllId + 1U))
    {
        for (maxOrMin = PMLIB_VIDEO_PLL_CALC_MIN_MN;
             maxOrMin <= PMLIB_VIDEO_PLL_CALC_MAX_MN; maxOrMin++)
        {
            printf("\n--------------------------------------------------\n");
            if (maxOrMin == 0U)
            {
                printf(" %s : Calculating for minimum M and N ", pmhalNodeList_names[videopllId]);
            }
            else
            {
                printf(" %s : Calculating for maximum M and N ", pmhalNodeList_names[videopllId]);
            }
            printf("\n--------------------------------------------------\n");
            for (i = arrayLims[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].startFreq;
                 i < arrayLims[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].stopFreq; )
            {
                printf("%d, ", i);
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
                        arrayInp[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].outputVenc,
                        arrayInp[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].vencClkSrc);
                    if (retVal == PM_SUCCESS)
                    {
                        retVal = PMLIBVideopllVencGetFreq(arrayInp[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].outputVenc,
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
#else
                    retVal = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSS,
                                             PMHAL_PRCM_CLK_VID_PIX_CLK, &setFreq);
                    setFreq = setFreq / 1000U;
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
#endif
                }
                else
                {
                    printf("\n");
                }
                i = i + arrayLims[videopllId - PMHAL_PRCM_VIDEOPLL_MIN].stepFreq;
            }
        }
    }
    return (pmErrCode_t) (retVal);
}

