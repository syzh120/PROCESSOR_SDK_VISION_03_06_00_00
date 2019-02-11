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
 *  \addtogroup CLK_RATE Clock Rate Configuration
 *
 * VideoPll Configuration - Video-PLL library provides APIs configure the
 *  Video PLL to the required frequency for display application.
 *
 *  - Video-pll library calculates the values of multiplier, divider and
 *  post divider, these values selected may not be with least jitter.
 *  - In case the frequency cannot be obtained from any combination the
 *  lib doesnt approximate to nearest but returns an error status as
 *  values cannot be calculated.
 *
 * @{
 */

/**
 *  \file  pmlib_videopll.h
 *
 *  \brief  This file declares the interface for video pll programming.
 */

#ifndef PMLIB_VIDEOPLL_H_
#define PMLIB_VIDEOPLL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
#include <ti/drv/pm/include/prcm/pmhal_videopll.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Flag to indicate to the API to calculate the min M and min N
 *          values that can meet the desired frequency. */
#define PMLIB_VIDEO_PLL_CALC_MIN_MN         (0U)
/** \brief Flag to indicate to the API to calculate the max M and max N
 *          values that can meet the desired frequency. Useful for errata i886.
 */
#define PMLIB_VIDEO_PLL_CALC_MAX_MN         (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum for the Venc's
 *  Caution: Do not change the enum values.
 *           these are exact match of Bsp_PlatformVenc
 */
typedef enum pmlibVideoPllVenc
{
    PMLIB_VIDEOPLL_VENC_LCD1 = 0U,
    /**< LCD1 Venc. */
    PMLIB_VIDEOPLL_VENC_LCD2,
    /**< LCD2 Venc. */
    PMLIB_VIDEOPLL_VENC_LCD3,
    /**< LCD3 Venc */
    PMLIB_VIDEOPLL_VENC_HDMI,
    /**< HDMI PLL. */
    PMLIB_VIDEOPLL_VENC_MAX
    /**< This should be last Enum. */
} pmlibVideoPllVenc_t;

/**
 *  \brief Enum for the Venc's Clock Source
 *  Caution: Do not change the enum values.
 *           these are exact match of Bsp_PlatformClkSrc
 */
typedef enum pmlibVideoPllClkSrc
{
    PMLIB_VIDEOPLL_CLKSRC_PRCM_PER_PLL = 0,
    /**<  PER PLL*/
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1,
    /**< Video1 PLL clkout1. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT2,
    /**< Video1 PLL clkout2. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3,
    /**< Video1 PLL clkout3. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT4,
    /**< Video1 PLL clkout4. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT1,
    /**< Video2 PLL clkout1. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT2,
    /**< Video2 PLL clkout2. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT3,
    /**< Video2 PLL clkout3. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO2_CLKOUT4,
    /**< Video2 PLL clkout4. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_HDMI,
    /**< HDMI PLL. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_ABE_GICLK,
    /**< ABE PLL. */
    PMLIB_VIDEOPLL_CLKSRC_DSS_GFCLK,
    /**< Functional Clock of DISPC. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_EVE_VID_DSP,
    /**< Common PLL for VID,EVE,DSP. Available only on Tda3xx platform. */
    PMLIB_VIDEOPLL_CLKSRC_DPLL_SATA,
    /**< Sata PLL clock source available only for TDA2px */
    PMLIB_VIDEOPLL_CLKSRC_MAX
    /**< This should be last Enum. */
} pmlibVideoPllClkSrc_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Api to set the VideoPll to given frequency .
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   freq            Frequency at which video pll needs to be configured.
 *                          This number should be represented in kHz.
 * \param   maxOrMinMN      This parameter allows the API to calculate the
 *                          maximum value of M and N for the given frequency or
 *                          minimum value of M and N for the given frequency.
 *                          PMLIB_VIDEO_PLL_CALC_MIN_MN - Minimum value of M, N.
 *                          PMLIB_VIDEO_PLL_CALC_MAX_MN - Maximum value of M, N.
 * \param   timeOut         Wait time duration.
 *                          #PM_TIMEOUT_NOWAIT - If one does not want to wait
 *                          #PM_TIMEOUT_INFINITE - If one wants to wait
 *                          infinitely till the Frequency is set.
 *                          Any other Number - To specify the number of cycles.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 #PM_SUCCESS  If the desired frequency was set.
 *                 #PM_FAIL     If the desired frequency was not set.
 */
int32_t PMLIBVideopllSetFreq(pmhalPrcmNodeId_t videopllId,
                             uint32_t          freq,
                             uint32_t          maxOrMinMN,
                             uint32_t          timeOut);

/**
 * \note For the TDA3x device Use the PMLIBClkRateGet Function to read video PLL
 * clocks.
 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
/**
 * \brief   Api to get the VideoPll to given frequency .
 *
 * \param   vidpllClkId     Unique Clock ID of the PLL
 * \param   hsDivId         Enum corresponding to HS divider
 * \param   freq            Returns frequency at which video pll is configured.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 #PM_SUCCESS  If the desired frequency was set.
 *                 #PM_FAIL     If the desired frequency was not set.
 */
int32_t PMLIBVideopllGetFreq(pmhalPrcmClockId_t vidpllClkId,
                             pmhalVideopllHSD_t hsDivId,
                             uint32_t          *freq);

/**
 * \brief   Api to get the VEnc Input frequency .
 *
 * \param   vencId          Enum corresponding to venc ID
 * \param   freq            Returns frequency at which video pll is configured.
 *                          The value returned is in kHz.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 #PM_SUCCESS  If the desired frequency was set.
 *                 #PM_FAIL     If the desired frequency was not set.
 */
int32_t PMLIBVideopllVencGetFreq(pmlibVideoPllVenc_t vencId, uint32_t *freq);

/**
 * \brief   API to get the PRCM Input Clock frequency. Video PLL outputs are
 *          input to the PRCM. PRCM treats them as root clocks. This API helps
 *          determine their frequency.
 *
 * \param   vidpllId        Unique Videopll ID of the PLL
 * \param   freq            Returns frequency at which video pll is configured.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 #PM_SUCCESS  If the desired frequency was set.
 *                 #PM_FAIL     If the desired frequency was not set.
 */
int32_t PMLIBVideopllPrcmInCLkGetFreq(pmhalPrcmNodeId_t vidpllId,
                                      uint32_t         *freq);

/**
 * \brief   API to program the right multiplexer combinations to choose the
 *          clock source for a given Video Encoder.
 *
 * \param   outputVenc      Unique ID of the desired output VENC. Refer
 *                          #pmlibVideoPllVenc_t for details.
 * \param   vencClkSrc      Unique ID of the desired clock input source.
 *                          Refer #pmlibVideoPllClkSrc_t for more details.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                  #PM_SUCCESS  If the desired output Venc is sourced by the
 *                              desired clock source.
 *                  #PM_BADARGS  If the combination of output venc and clock
 *                              source is not supported.
 */
int32_t PMLIBVideopllSetVencClkSrc(pmlibVideoPllVenc_t   outputVenc,
                                   pmlibVideoPllClkSrc_t vencClkSrc);

/**
 * \brief   API to program the right multiplexer combinations to choose the
 *          clock source for the display controller.
 *
 * \param   fClkSrc         Unique ID of the desired clock input source.
 *                          Refer #pmlibVideoPllClkSrc_t for more details.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                  #PM_SUCCESS  If DISPC is sourced by the
 *                               desired clock source.
 *                  #PM_BADARGS  If clock source is not supported in the device.
 */
int32_t PMLIBVideopllSetDispcFuncClkSrc(pmlibVideoPllClkSrc_t fClkSrc);

/**
 * \brief   API to enable or disable the HDMI PLL.
 *
 * \param   enable         1 - To enable the HDMI PLL.
 *                         0 - To disable the HDMI PLL.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                 #PM_SUCCESS  If HDMI PLL is enabled or disabled as desired.
 */
int32_t PMLIBVideopllEnableHdmiPll(uint32_t enable);

#endif

#ifdef __cplusplus
}
#endif

#endif

/* @} */


