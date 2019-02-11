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
 *  \file      hw_pmhal_clocktree_data.c
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare PMHAL_PRCM clocktree implementation.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include "stdint.h"
#include "stdlib.h"
#include "hw_pmhal_clocktree_data.h"
#include "hw_pmhal_data.h"

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_EMU_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_EMU_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_REF_CLKIN0
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_REF_CLKIN0_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_REF_CLKIN1
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_REF_CLKIN1_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_REF_CLKIN2
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_REF_CLKIN2_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_REF_CLKIN3
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_REF_CLKIN3_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SATA_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SATA_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_USB_OTG_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_USB_OTG_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
#endif
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_PCIESREF_ACS
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_PCIESREF_ACS_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_ROOT_CLK_RMII
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_RMII_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_ATLCLKIN3
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_ATLCLKIN3_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_MLBP_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_MLBP_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_MLB_CLKIN
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_MLB_CLKIN_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SYS_32K
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SYS_32K_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_ATL_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ATL_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ATL_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_IPU1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_ADC_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ADC_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ADC_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_EVE_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_EVE_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_EVE_GCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_QSPI_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VIP1_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VIP1_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIP1_GCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VIP2_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VIP2_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIP2_GCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VIP3_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VIP3_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIP3_GCLK_MUX - PMHAL_PRCM_MUX_MIN]
};

/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VPE_GCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VPE_GCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VPE_GCLK_MUX - PMHAL_PRCM_MUX_MIN]
};

/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MMC1_FCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MMC1_FCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MMC1_FCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MMC2_FCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MMC2_FCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MMC2_FCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MMC3_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MMC3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MMC4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RMII_REF_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RMII_REF_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART10_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART10_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART10_GFCLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART1_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART2_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART2_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART3_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART4_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART4_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART5_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART5_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART5_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART6_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART6_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART6_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART7_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART7_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART7_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART8_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART8_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART8_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_UART9_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_UART9_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART9_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures
 *          for PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_ABE_24M_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_ABE_24M_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_ABE_24M_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_ABE_LP_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_ABE_LP_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_ABE_LP_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_24M_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_24M_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_L3_ICLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_L3_ICLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_L3_ICLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_L4_ROOT_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_L4_ROOT_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PER_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_USB_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_USB_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_ABE_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_ABE_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_ABE_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_ABE_GICLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_ABE_GICLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_ABE_GICLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_AESS_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_AESS_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_AESS_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_QSPI_GFCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_QSPI_GFCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_QSPI_GFCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_DSP_GCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_DSP_GCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_DSP_GCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_EMIF_PHY_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_EMIF_PHY_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_EMIF_PHY_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_EMU_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_EMU_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_EMU_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_EVE_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_EVE_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_EVE_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_GMAC_250M_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_GMAC_250M_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_GMAC_250M_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_GPU_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_GPU_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_GPU_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_HDMI_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_HDMI_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_HDMI_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_IVA_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_IVA_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_IVA_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_L3INIT_480M_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_L3INIT_480M_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_L3INIT_480M_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MPU_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MPU_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MPU_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_PCIE2_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PCIE2_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PCIE2_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_PCIE_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PCIE_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PCIE_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PER_ABE_X1_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SATA_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SATA_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SATA_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SECURE_32K_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SECURE_32K_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SECURE_32K_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SYS_CLK1_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SYS_CLK1_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SYS_CLK1_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SYS_CLK2_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SYS_CLK2_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SYS_CLK2_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_USB_OTG_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_USB_OTG_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_USB_OTG_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO1_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO1_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO1_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO2_DCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO2_DCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO2_DCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_12M_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_12M_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_12M_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_48M_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_48M_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_96M_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_96M_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MMC1_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MMC1_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MMC1_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MMC2_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MMC2_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MMC2_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_L3INIT_60M_FCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_L3INIT_60M_FCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_L3INIT_60M_FCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_GMII_M_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_GMII_M_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_GMII_M_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MMC3_GFCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MMC3_GFCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MMC3_GFCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MMC4_GFCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MMC4_GFCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MMC4_GFCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_RGMII_5M_REF_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_RGMII_5M_REF_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_HDMI_CLK2
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_HDMI_CLK2_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_HDMI_CLK2 - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO1_CLK2
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO1_CLK2_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO1_CLK2 - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO2_CLK2
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO2_CLK2_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO2_CLK2 - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MLBP_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MLBP_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MLBP_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_MLB_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_MLB_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_MLB_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_HDMI_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_HDMI_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_HDMI_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO1_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO1_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO1_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VIDEO2_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VIDEO2_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VIDEO2_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_ABE_SYS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_ABE_SYS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_ABE_SYS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_L3INSTR_TS_GCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_TIMER_SYS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_TIMER_SYS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_TIMER_SYS_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_IPU1_GCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_IPU1_GCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_IPU1_GCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_IPU2_GCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_IPU2_GCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_IPU2_GCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_32K_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_32K_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VPE_GCLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VPE_GCLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VPE_GCLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_APLL_PCIE_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_ABE_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_CORE_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_DDR_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_GMAC_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_GPU_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_IVA_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_PCIE_REF
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_PCIE_REF_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_PCIE_REF - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_PER_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_USB_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_DSP_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_EVE_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_MPU_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN]
};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ATL
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ATL_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ATL - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_DUMMY_MODULE4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DUMMY_MODULE4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DUMMY_MODULE4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_DUMMY_MODULE1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DUMMY_MODULE1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DUMMY_MODULE1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_DUMMY_MODULE2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DUMMY_MODULE2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DUMMY_MODULE2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_DUMMY_MODULE3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DUMMY_MODULE3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DUMMY_MODULE3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_IO_SRCOMP_CORE
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IO_SRCOMP_CORE_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IO_SRCOMP_CORE -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SMARTREFLEX_CORE
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SMARTREFLEX_CORE_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SMARTREFLEX_CORE -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SMARTREFLEX_GPU
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SMARTREFLEX_GPU_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SMARTREFLEX_GPU -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SMARTREFLEX_MPU
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SMARTREFLEX_MPU_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SMARTREFLEX_MPU -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EFUSE_CTRL_CUST -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DMA_SYSTEM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DMA_SYSTEM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DMA_SYSTEM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DSP1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DSP1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DSP1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DSP2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DSP2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DSP2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_BB2D
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_BB2D_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_BB2D - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DSS
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DSS_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DSS - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SDVENC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SDVENC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SDVENC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DLL
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DLL_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DLL - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DMM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DMM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DMM - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EMIF1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EMIF1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EMIF1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EMIF2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EMIF2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EMIF2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EMIF_OCP_FW
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EMIF_OCP_FW_prop =
{
    PMHAL_MOD, &pmhalModuleElems[PMHAL_PRCM_MOD_EMIF_OCP_FW -
                                 (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EVE1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EVE1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EVE1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EVE2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EVE2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EVE2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EVE3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EVE3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EVE3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_EVE4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_EVE4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_EVE4 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CPGMAC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CPGMAC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPU
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPU_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPU - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C5 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER5 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER6 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER7 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER8
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER8 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART6 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_IPU1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IPU1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IPU1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_IPU2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IPU2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IPU2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_IVA
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IVA_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IVA - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SL2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SL2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SL2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_IEEE1500_2_OCP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IEEE1500_2_OCP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IEEE1500_2_OCP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMC1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMC1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMC1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMC2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMC2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMC2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MLB_SS
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MLB_SS_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MLB_SS -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SATA
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SATA_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SATA - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCP2SCP1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCP2SCP1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCP2SCP1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCP2SCP3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCP2SCP3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCP2SCP3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_USB_OTG_SS1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_OTG_SS1_prop =
{
    PMHAL_MOD, &pmhalModuleElems[PMHAL_PRCM_MOD_USB_OTG_SS1 -
                                 (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_USB_OTG_SS2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_OTG_SS2_prop =
{
    PMHAL_MOD, &pmhalModuleElems[PMHAL_PRCM_MOD_USB_OTG_SS2 -
                                 (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_USB_OTG_SS3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_OTG_SS3_prop =
{
    PMHAL_MOD, &pmhalModuleElems[PMHAL_PRCM_MOD_USB_OTG_SS3 -
                                 (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_USB_OTG_SS4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_USB_OTG_SS4_prop =
{
    PMHAL_MOD, &pmhalModuleElems[PMHAL_PRCM_MOD_USB_OTG_SS4 -
                                 (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DLL_AGING
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DLL_AGING_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DLL_AGING -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L3_INSTR
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L3_INSTR_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L3_INSTR -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L3_MAIN_2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L3_MAIN_2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L3_MAIN_2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCP_WP_NOC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCP_WP_NOC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCP_WP_NOC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPMC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPMC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPMC - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L3_MAIN_1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L3_MAIN_1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L3_MAIN_1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMU_EDMA
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMU_EDMA_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMU_EDMA -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMU_PCIESS
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMU_PCIESS_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMU_PCIESS -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCMC_RAM1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCMC_RAM1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCMC_RAM1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCMC_RAM2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCMC_RAM2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCMC_RAM2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCMC_RAM3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCMC_RAM3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCMC_RAM3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCMC_ROM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCMC_ROM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCMC_ROM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPARE_IVA2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_IVA2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_IVA2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VCP1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VCP1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VCP1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VCP2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VCP2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VCP2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPARE_CME
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_CME_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_CME -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPARE_HDMI
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_HDMI_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_HDMI -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPARE_ICM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_ICM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_ICM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPARE_SATA2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SATA2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SATA2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_UNKNOWN4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_UNKNOWN4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_UNKNOWN4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_UNKNOWN5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_UNKNOWN5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_UNKNOWN5 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_UNKNOWN6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_UNKNOWN6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_UNKNOWN6 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_VIDEOPLL1.
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_VIDEOPLL1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_VIDEOPLL2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_VIDEOPLL3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TPCC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TPCC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TPCC - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TPTC1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TPTC1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TPTC1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TPTC2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TPTC2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TPTC2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L4_CFG
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L4_CFG_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L4_CFG -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_OCP2SCP2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_OCP2SCP2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_OCP2SCP2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SAR_ROM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SAR_ROM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SAR_ROM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SPINLOCK
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPINLOCK_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPINLOCK -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_IO_DELAY_BLOCK
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IO_DELAY_BLOCK_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IO_DELAY_BLOCK -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX10
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX10_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX10 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX11
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX11_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX11 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX12
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX12_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX12 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX13
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX13_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX13 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX5 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX6 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX7 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX8
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX8 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MAILBOX9
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MAILBOX9_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MAILBOX9 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C4 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L4_PER1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L4_PER1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L4_PER1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER10
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER10_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER10 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER11
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER11_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER11 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER9
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER9_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER9 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ELM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ELM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ELM - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_HDQ1W
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_HDQ1W_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_HDQ1W - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCSPI1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCSPI1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCSPI1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCSPI2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCSPI2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCSPI2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCSPI3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCSPI3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCSPI3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCSPI4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCSPI4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCSPI4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART4 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART5 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO4 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO5 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO6 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO7 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO8
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO8 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMC3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMC3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMC3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MMC4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MMC4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MMC4 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCAN2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCAN2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCAN2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L4_PER2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L4_PER2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L4_PER2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART7 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART8
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART8 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART9
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART9_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART9 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PRUSS1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PRUSS1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PRUSS1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PRUSS2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PRUSS2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PRUSS2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP5 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP6 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP7 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCASP8
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCASP8 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PWMSS1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PWMSS1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PWMSS1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PWMSS2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PWMSS2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PWMSS2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PWMSS3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PWMSS3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PWMSS3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_QSPI
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_QSPI_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_QSPI - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L4_PER3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L4_PER3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L4_PER3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER13
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER13_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER13 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER14
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER14_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER14 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER15
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER15_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER15 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER16
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER16_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER16 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_AES1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_AES1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_AES1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_AES2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_AES2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_AES2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DES3DES
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DES3DES_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DES3DES -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DMA_CRYPTO
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DMA_CRYPTO_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DMA_CRYPTO -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_FPKA
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_FPKA_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_FPKA - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_RNG
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RNG_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RNG - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SHA2MD51
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SHA2MD51_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SHA2MD51 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SHA2MD52
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SHA2MD52_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SHA2MD52 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MPU
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MPU_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MPU - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MPU_MPU_DBG
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MPU_MPU_DBG_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MPU_MPU_DBG -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PCIESS1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PCIESS1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PCIESS1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_PCIESS2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_PCIESS2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_PCIESS2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_RTCSS
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTCSS_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTCSS - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CSI1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CSI1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CSI1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CSI2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CSI2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CSI2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI2 */

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_LVDSRX
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_LVDSRX_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_LVDSRX -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VIP1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VIP1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VIP1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAL
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CAL
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CAL_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CAL - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAL */
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_I2C6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_I2C6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_I2C6 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C6 */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VIP2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VIP2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VIP2 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VIP3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VIP3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VIP3 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_VPE
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_VPE_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_VPE - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DEBUG_LOGIC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DEBUG_LOGIC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DEBUG_LOGIC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MPU_EMU_DBG
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MPU_EMU_DBG_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MPU_EMU_DBG -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ADC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ADC - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_COUNTER_32K
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_COUNTER_32K_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_COUNTER_32K -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CTRL_MODULE_WKUP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCAN1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCAN1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCAN1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_GPIO1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_GPIO1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_GPIO1 - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_IO_SRCOMP_WKUP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_IO_SRCOMP_WKUP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_KBD
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_KBD_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_KBD - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_L4_WKUP
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_L4_WKUP_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_L4_WKUP -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_SAR_RAM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SAR_RAM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SAR_RAM -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SAFETY1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SAFETY1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SAFETY2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SAFETY2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SAFETY3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SAFETY3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_SAFETY4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_SAFETY4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_UNKNOWN2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_UNKNOWN2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_UNKNOWN2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_UNKNOWN3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_SPARE_UNKNOWN3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_SPARE_UNKNOWN3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TIMER12
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TIMER12_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TIMER12 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_UART10
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_UART10_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_UART10 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_WD_TIMER1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_WD_TIMER1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_WD_TIMER1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_WD_TIMER2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_WD_TIMER2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_WD_TIMER2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */

/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX_inNodes[] = {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN,
#endif
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN,
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ATL_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ATL_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DPLL_ABE,
    PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ADC_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ADC_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_EVE_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP,
    PMHAL_PRCM_DPLL_EVE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_GPU
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_GPU
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIP1_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIP2_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIP2_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIP3_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIP3_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK
};

/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VPE_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VPE_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN
};

/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
    PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
    PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
    PMHAL_PRCM_DIV_DSP_GCLK,
    PMHAL_PRCM_DIV_EVE_DCLK,
    PMHAL_PRCM_DIV_IVA_DCLK,
    PMHAL_PRCM_DIV_MPU_DCLK,
    PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
    PMHAL_PRCM_DIV_GMAC_250M_DCLK,
    PMHAL_PRCM_DIV_GPU_DCLK,
    PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
    PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
    PMHAL_PRCM_DIV_PCIE2_DCLK,
    PMHAL_PRCM_DIV_PCIE_DCLK,
    PMHAL_PRCM_DIV_HDMI_DCLK,
    PMHAL_PRCM_DIV_VIDEO1_DCLK,
    PMHAL_PRCM_DIV_USB_OTG_DCLK,
    PMHAL_PRCM_DIV_VIDEO2_DCLK,
    PMHAL_PRCM_DIV_EMU_DCLK,
    PMHAL_PRCM_DIV_SECURE_32K_DCLK,
    PMHAL_PRCM_DIV_SATA_DCLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
    PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
    PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
    PMHAL_PRCM_DIV_DSP_GCLK,
    PMHAL_PRCM_DIV_EVE_DCLK,
    PMHAL_PRCM_DIV_IVA_DCLK,
    PMHAL_PRCM_DIV_MPU_DCLK,
    PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
    PMHAL_PRCM_DIV_GMAC_250M_DCLK,
    PMHAL_PRCM_DIV_GPU_DCLK,
    PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
    PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
    PMHAL_PRCM_DIV_PCIE2_DCLK,
    PMHAL_PRCM_DIV_PCIE_DCLK,
    PMHAL_PRCM_DIV_HDMI_DCLK,
    PMHAL_PRCM_DIV_VIDEO1_DCLK,
    PMHAL_PRCM_DIV_USB_OTG_DCLK,
    PMHAL_PRCM_DIV_VIDEO2_DCLK,
    PMHAL_PRCM_DIV_EMU_DCLK,
    PMHAL_PRCM_DIV_SECURE_32K_DCLK,
    PMHAL_PRCM_DIV_SATA_DCLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
    PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
    PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
    PMHAL_PRCM_DIV_DSP_GCLK,
    PMHAL_PRCM_DIV_EVE_DCLK,
    PMHAL_PRCM_DIV_IVA_DCLK,
    PMHAL_PRCM_DIV_MPU_DCLK,
    PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
    PMHAL_PRCM_DIV_GMAC_250M_DCLK,
    PMHAL_PRCM_DIV_GPU_DCLK,
    PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
    PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
    PMHAL_PRCM_DIV_PCIE2_DCLK,
    PMHAL_PRCM_DIV_PCIE_DCLK,
    PMHAL_PRCM_DIV_HDMI_DCLK,
    PMHAL_PRCM_DIV_VIDEO1_DCLK,
    PMHAL_PRCM_DIV_USB_OTG_DCLK,
    PMHAL_PRCM_DIV_VIDEO2_DCLK,
    PMHAL_PRCM_DIV_EMU_DCLK,
    PMHAL_PRCM_DIV_SECURE_32K_DCLK,
    PMHAL_PRCM_DIV_SATA_DCLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MMC1_FCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MMC1_FCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MMC2_FCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MMC2_FCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DPLL_ABE,
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN,
#endif
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN,
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MMC3_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RMII_REF_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_GMAC,
    PMHAL_PRCM_ROOT_CLK_RMII
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATLCLKIN3,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_ABE_GICLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_TIMER_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN3,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART10_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART10_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART1_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART2_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART3_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART4_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART4_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART5_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART5_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART6_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART6_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART7_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART7_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART8_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART8_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_UART9_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_UART9_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX_inNodes[]
    = {
    PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
    };
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_ABE_LP_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_FUNC_32K_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_32K
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_24M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_24M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_LP_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_LP_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L3_ICLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L3_ICLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L4_ROOT_CLK_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_USB_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_GICLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_GICLK_inNodes[] = {
    PMHAL_PRCM_DIV_AESS_FCLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_AESS_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_AESS_FCLK_inNodes[] = {
    PMHAL_PRCM_DIV_ABE_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_QSPI_GFCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_QSPI_GFCLK_inNodes[] = {
    PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_DSP_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_DSP_GCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_EMIF_PHY_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_EMIF_PHY_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_EMU_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_EMU_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_EMU_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_EVE_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_EVE_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_EVE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GMAC_250M_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GMAC_250M_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GPU_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GPU_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_GPU
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IVA_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IVA_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_IVA
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L3INIT_480M_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L3INIT_480M_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_USB
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MPU_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MPU_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_MPU
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PCIE2_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PCIE2_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PCIE_REF
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PCIE_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PCIE_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_APLL_PCIE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_ABE_X1_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SATA_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SATA_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SATA_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SECURE_32K_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SECURE_32K_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SYS_CLK1_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SYS_CLK1_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SYS_CLK2_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SYS_CLK2_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_USB_OTG_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_USB_OTG_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_USB_OTG_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_DCLK_inNodes[] = {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN
#else
    PMHAL_PRCM_NODE_UNDEF
#endif
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_12M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_12M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_48M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_96M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MMC1_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MMC1_FCLK_inNodes[] = {
    PMHAL_PRCM_MUX_MMC1_FCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MMC2_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MMC2_FCLK_inNodes[] = {
    PMHAL_PRCM_MUX_MMC2_FCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L3INIT_60M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L3INIT_60M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_USB
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GMII_M_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GMII_M_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MMC3_GFCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MMC3_GFCLK_inNodes[] = {
    PMHAL_PRCM_MUX_MMC3_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MMC4_GFCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes[] = {
    PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_RGMII_5M_REF_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_inNodes[] = {
    PMHAL_PRCM_MUX_RMII_REF_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_CLK2_inNodes[] = {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN
#else
    PMHAL_PRCM_NODE_UNDEF
#endif
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MLBP_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MLBP_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_MLBP_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MLB_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MLB_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_MLB_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_CLK_inNodes[] = {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN,
#else
    PMHAL_PRCM_NODE_UNDEF
#endif
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_inNodes[] =
{
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_SYS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_SYS_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_TIMER_SYS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_TIMER_SYS_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IPU1_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IPU1_GCLK_inNodes[] = {
    PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IPU2_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IPU2_GCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VPE_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VPE_GCLK_inNodes[] = {
    PMHAL_PRCM_MUX_VPE_GCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_APLL_PCIE_inNodes[] = {
    PMHAL_PRCM_DPLL_PCIE_REF,
    PMHAL_PRCM_ROOT_CLK_PCIESREF_ACS
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_ABE_inNodes[] = {
    PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX,
    PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_CORE_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_DDR_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_GMAC_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_GPU_inNodes[] = {
    PMHAL_PRCM_DPLL_ABE,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_IVA_inNodes[] = {
    PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_PCIE_REF
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_PCIE_REF_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_PER_inNodes[] = {
    PMHAL_PRCM_DIV_PER_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_USB_inNodes[] = {
    PMHAL_PRCM_DIV_USB_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_DSP_inNodes[] = {
    PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_EVE_inNodes[] = {
    PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_MPU_inNodes[] = {
    PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ATL
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ATL_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DUMMY_MODULE4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DUMMY_MODULE4_inNodes[] = {
    PMHAL_PRCM_DIV_ABE_GICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DUMMY_MODULE1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DUMMY_MODULE1_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DUMMY_MODULE2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DUMMY_MODULE2_inNodes[] = {
    PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DUMMY_MODULE3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DUMMY_MODULE3_inNodes[] = {
    PMHAL_PRCM_DIV_L3INIT_60M_FCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IO_SRCOMP_CORE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IO_SRCOMP_CORE_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SMARTREFLEX_CORE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SMARTREFLEX_CORE_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SMARTREFLEX_GPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SMARTREFLEX_GPU_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SMARTREFLEX_MPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SMARTREFLEX_MPU_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON_inNodes[] = {
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON_inNodes[] = {
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON_inNodes[] = {
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DMA_SYSTEM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DMA_SYSTEM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSP1_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSP2_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP
};
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_BB2D
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_BB2D_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSS_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX,
    PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX,
    PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SDVENC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SDVENC_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DLL
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DLL_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DMM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DMM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EMIF1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EMIF1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DPLL_DDR
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EMIF2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EMIF2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DPLL_DDR
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EMIF_OCP_FW
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EMIF_OCP_FW_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EVE1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EVE1_inNodes[] = {
    PMHAL_PRCM_MUX_EVE_GCLK_MUX
};
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EVE2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EVE2_inNodes[] = {
    PMHAL_PRCM_MUX_EVE_GCLK_MUX
};
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE3
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EVE3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EVE3_inNodes[] = {
    PMHAL_PRCM_MUX_EVE_GCLK_MUX
};
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE4
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EVE4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EVE4_inNodes[] = {
    PMHAL_PRCM_MUX_EVE_GCLK_MUX
};
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CPGMAC_inNodes[] = {
    PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
    PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK,
    PMHAL_PRCM_DIV_RGMII_5M_REF_CLK,
    PMHAL_PRCM_MUX_RMII_REF_CLK_MUX,
    PMHAL_PRCM_DPLL_GMAC
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPU_inNodes[] = {
    PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
    PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C5_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP1_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
    PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER5_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER6_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER7_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER8
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER8_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART6_inNodes[] = {
    PMHAL_PRCM_MUX_UART6_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IPU1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IPU1_inNodes[] = {
    PMHAL_PRCM_DIV_IPU1_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IPU2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IPU2_inNodes[] = {
    PMHAL_PRCM_DIV_IPU2_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IVA
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IVA_inNodes[] = {
    PMHAL_PRCM_DPLL_IVA
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SL2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SL2_inNodes[] = {
    PMHAL_PRCM_DPLL_IVA
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IEEE1500_2_OCP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMC1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMC1_inNodes[] = {
    PMHAL_PRCM_DIV_MMC1_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMC2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMC2_inNodes[] = {
    PMHAL_PRCM_DIV_MMC2_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MLB_SS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MLB_SS_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SATA
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SATA_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCP2SCP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCP2SCP1_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCP2SCP3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCP2SCP3_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_OTG_SS1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_OTG_SS1_inNodes[] = {
    PMHAL_PRCM_DPLL_USB,
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_OTG_SS2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_OTG_SS2_inNodes[] = {
    PMHAL_PRCM_DPLL_USB,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_OTG_SS3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_OTG_SS3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_USB_OTG_SS4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_USB_OTG_SS4_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_inNodes[] =
{
    PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DLL_AGING
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DLL_AGING_inNodes[] = {
    PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L3_INSTR
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L3_INSTR_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L3_MAIN_2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L3_MAIN_2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCP_WP_NOC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCP_WP_NOC_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPMC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPMC_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L3_MAIN_1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L3_MAIN_1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMU_EDMA
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMU_EDMA_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMU_PCIESS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMU_PCIESS_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCMC_RAM1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCMC_RAM1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCMC_RAM2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCMC_RAM2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCMC_RAM3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCMC_RAM3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCMC_ROM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCMC_ROM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_IVA2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_IVA2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VCP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VCP1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VCP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VCP2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_CME
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_CME_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_HDMI
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_HDMI_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_ICM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_ICM_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SATA2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SATA2_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_UNKNOWN4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_UNKNOWN4_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_UNKNOWN5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_UNKNOWN5_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_UNKNOWN6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_UNKNOWN6_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_VIDEOPLL1_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_VIDEOPLL2_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_VIDEOPLL3_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TPCC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TPCC_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TPTC1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TPTC1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TPTC2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TPTC2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_CFG
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_CFG_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCP2SCP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCP2SCP2_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SAR_ROM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SAR_ROM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC_inNodes[]
    = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
    };
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM_inNodes
[] =
{
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP_inNodes[]
    = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK
    };
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPINLOCK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPINLOCK_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IO_DELAY_BLOCK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IO_DELAY_BLOCK_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX10
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX10_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX11
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX11_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX12
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX12_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX13
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX13_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX4_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX5_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX6_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX7_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX8
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX8_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX9
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX9_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C1_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C2_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C3_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C4_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_I2C6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_I2C6_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C6 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_PER1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_PER1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER10
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER10_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER11
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER11_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER2_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER3_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER4_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER9
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER9_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ELM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ELM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_HDQ1W
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_HDQ1W_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_12M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCSPI1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCSPI1_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCSPI2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCSPI2_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCSPI3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCSPI3_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCSPI4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCSPI4_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART1_inNodes[] = {
    PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART2_inNodes[] = {
    PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART3_inNodes[] = {
    PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART4_inNodes[] = {
    PMHAL_PRCM_MUX_UART4_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART5_inNodes[] = {
    PMHAL_PRCM_MUX_UART5_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO4_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO5_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO6_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO7_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO8
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO8_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMC3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMC3_inNodes[] = {
    PMHAL_PRCM_DIV_MMC3_GFCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MMC4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MMC4_inNodes[] = {
    PMHAL_PRCM_DIV_MMC4_GFCLK,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCAN2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCAN2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_PER2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_PER2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART7_inNodes[] = {
    PMHAL_PRCM_MUX_UART7_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART8
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART8_inNodes[] = {
    PMHAL_PRCM_MUX_UART8_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART9
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART9_inNodes[] = {
    PMHAL_PRCM_MUX_UART9_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PRUSS1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PRUSS1_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DPLL_GMAC
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PRUSS2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PRUSS2_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DPLL_GMAC
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP2_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
    PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP3_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP4_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP5_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP6_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP7_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP8
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP8_inNodes[] = {
    PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PWMSS1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PWMSS1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PWMSS2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PWMSS2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PWMSS3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PWMSS3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_QSPI
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_QSPI_inNodes[] = {
    PMHAL_PRCM_DIV_QSPI_GFCLK,
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_PER3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_PER3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER13
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER13_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER14
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER14_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER15
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER15_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER16
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER16_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_AES1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_AES1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_AES2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_AES2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DES3DES
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DES3DES_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DMA_CRYPTO
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DMA_CRYPTO_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_FPKA
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_FPKA_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RNG
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RNG_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SHA2MD51
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SHA2MD51_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SHA2MD52
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SHA2MD52_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MPU
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MPU_inNodes[] = {
    PMHAL_PRCM_DPLL_MPU
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MPU_MPU_DBG
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MPU_MPU_DBG_inNodes[] = {
    PMHAL_PRCM_DPLL_MPU
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PCIESS1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PCIESS1_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_DPLL_APLL_PCIE,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PCIESS2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PCIESS2_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_DPLL_APLL_PCIE,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTCSS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTCSS_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_ROOT_CLK_SYS_32K,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CSI1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CSI1_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CSI2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CSI2_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI2 */

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_LVDSRX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_LVDSRX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VIP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VIP1_inNodes[] = {
    PMHAL_PRCM_MUX_VIP1_GCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAL
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CAL
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CAL_inNodes[] = {
    PMHAL_PRCM_MUX_VIP2_GCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAL */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VIP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VIP2_inNodes[] = {
    PMHAL_PRCM_MUX_VIP2_GCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VIP3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VIP3_inNodes[] = {
    PMHAL_PRCM_MUX_VIP3_GCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VPE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VPE_inNodes[] = {
    PMHAL_PRCM_DIV_VPE_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DEBUG_LOGIC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MPU_EMU_DBG
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MPU_EMU_DBG_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ADC_inNodes[] = {
    PMHAL_PRCM_MUX_ADC_GFCLK_MUX,
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_COUNTER_32K
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_COUNTER_32K_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCAN1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCAN1_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_GPIO1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_GPIO1_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IO_SRCOMP_WKUP_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_KBD
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_KBD_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_WKUP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_WKUP_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SAR_RAM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SAR_RAM_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SAFETY1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SAFETY1_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SAFETY2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SAFETY2_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SAFETY3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SAFETY3_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_SAFETY4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_SAFETY4_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_UNKNOWN2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_UNKNOWN2_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPARE_UNKNOWN3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPARE_UNKNOWN3_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER1_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER12
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER12_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_UART10
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_UART10_inNodes[] = {
    PMHAL_PRCM_MUX_UART10_GFCLK_MUX,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_WD_TIMER1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_WD_TIMER1_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_WD_TIMER2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_WD_TIMER2_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */

/**
 *  \brief Structure defining Node List Elements
 */
const pmhalClockTreeNode prcmNodes[] =
{
    {&PMHAL_PRCM_ROOT_CLK_PCIESREF_ACS_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_RMII_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SYS_32K_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_EMU_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_REF_CLKIN0_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_REF_CLKIN1_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_REF_CLKIN2_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_REF_CLKIN3_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SATA_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_USB_OTG_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATLCLKIN3_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_MLBP_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_MLB_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_VIDEO1_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_VIDEO1_M2_CLKIN_prop,
     NULL,
     0},
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_ROOT_CLK_VIDEO2_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_VIDEO2_M2_CLKIN_prop,
     NULL,
     0},
    #endif
    {&PMHAL_PRCM_ROOT_CLK_HDMI_CLKIN_prop,
     NULL,
     0},
    {&PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX_prop,
     PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ATL_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_ATL_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ATL_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ADC_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_ADC_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ADC_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_EVE_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIP1_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIP2_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_VIP2_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIP2_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIP3_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_VIP3_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIP3_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_prop,
     PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_prop,
     PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_prop,
     PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MMC1_FCLK_MUX_prop,
     PMHAL_PRCM_MUX_MMC1_FCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MMC1_FCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MMC2_FCLK_MUX_prop,
     PMHAL_PRCM_MUX_MMC2_FCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MMC2_FCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_prop,
     PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART10_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART10_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART10_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART1_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART1_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART1_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART2_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART2_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART2_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART3_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART3_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART3_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART4_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART4_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART4_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART5_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART5_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART5_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART6_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART6_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART6_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART7_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART7_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART7_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART8_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART8_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART8_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_UART9_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_UART9_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_UART9_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX_prop,
     PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX_prop,
     PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX_prop,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_prop,
     PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_prop,
     PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_prop,
     PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_prop,
     PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_prop,
     PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_prop,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VPE_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_VPE_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VPE_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_ABE_24M_FCLK_prop,
     PMHAL_PRCM_DIV_ABE_24M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_24M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_ABE_LP_CLK_prop,
     PMHAL_PRCM_DIV_ABE_LP_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_LP_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_24M_CLK_prop,
     PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L3_ICLK_prop,
     PMHAL_PRCM_DIV_L3_ICLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L3_ICLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L4_ROOT_CLK_prop,
     PMHAL_PRCM_DIV_L4_ROOT_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L4_ROOT_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_ABE_CLK_prop,
     PMHAL_PRCM_DIV_ABE_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_ABE_GICLK_prop,
     PMHAL_PRCM_DIV_ABE_GICLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_GICLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_AESS_FCLK_prop,
     PMHAL_PRCM_DIV_AESS_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_AESS_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_prop,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_QSPI_GFCLK_prop,
     PMHAL_PRCM_DIV_QSPI_GFCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_QSPI_GFCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_prop,
     PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_DSP_GCLK_prop,
     PMHAL_PRCM_DIV_DSP_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_DSP_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_EMIF_PHY_DCLK_prop,
     PMHAL_PRCM_DIV_EMIF_PHY_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_EMIF_PHY_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_EMU_DCLK_prop,
     PMHAL_PRCM_DIV_EMU_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_EMU_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_EVE_DCLK_prop,
     PMHAL_PRCM_DIV_EVE_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_EVE_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_prop,
     PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_GMAC_250M_DCLK_prop,
     PMHAL_PRCM_DIV_GMAC_250M_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_GMAC_250M_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_GPU_DCLK_prop,
     PMHAL_PRCM_DIV_GPU_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_GPU_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_HDMI_DCLK_prop,
     PMHAL_PRCM_DIV_HDMI_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_IVA_DCLK_prop,
     PMHAL_PRCM_DIV_IVA_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_IVA_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L3INIT_480M_DCLK_prop,
     PMHAL_PRCM_DIV_L3INIT_480M_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L3INIT_480M_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MPU_DCLK_prop,
     PMHAL_PRCM_DIV_MPU_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MPU_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PCIE2_DCLK_prop,
     PMHAL_PRCM_DIV_PCIE2_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PCIE2_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PCIE_DCLK_prop,
     PMHAL_PRCM_DIV_PCIE_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PCIE_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_prop,
     PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SATA_DCLK_prop,
     PMHAL_PRCM_DIV_SATA_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SATA_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SECURE_32K_DCLK_prop,
     PMHAL_PRCM_DIV_SECURE_32K_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SECURE_32K_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SYS_CLK1_DCLK_prop,
     PMHAL_PRCM_DIV_SYS_CLK1_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK1_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SYS_CLK2_DCLK_prop,
     PMHAL_PRCM_DIV_SYS_CLK2_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK2_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_USB_OTG_DCLK_prop,
     PMHAL_PRCM_DIV_USB_OTG_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_USB_OTG_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO1_DCLK_prop,
     PMHAL_PRCM_DIV_VIDEO1_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO2_DCLK_prop,
     PMHAL_PRCM_DIV_VIDEO2_DCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_DCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_12M_FCLK_prop,
     PMHAL_PRCM_DIV_FUNC_12M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_12M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_48M_FCLK_prop,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_48M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_96M_FCLK_prop,
     PMHAL_PRCM_DIV_FUNC_96M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_96M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MMC1_FCLK_prop,
     PMHAL_PRCM_DIV_MMC1_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MMC1_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MMC2_FCLK_prop,
     PMHAL_PRCM_DIV_MMC2_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MMC2_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L3INIT_60M_FCLK_prop,
     PMHAL_PRCM_DIV_L3INIT_60M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L3INIT_60M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_prop,
     PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_GMII_M_CLK_prop,
     PMHAL_PRCM_DIV_GMII_M_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_GMII_M_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MMC3_GFCLK_prop,
     PMHAL_PRCM_DIV_MMC3_GFCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MMC3_GFCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MMC4_GFCLK_prop,
     PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_prop,
     PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_HDMI_CLK2_prop,
     PMHAL_PRCM_DIV_HDMI_CLK2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_CLK2_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_prop,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO1_CLK2_prop,
     PMHAL_PRCM_DIV_VIDEO1_CLK2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_CLK2_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO2_CLK2_prop,
     PMHAL_PRCM_DIV_VIDEO2_CLK2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_CLK2_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MLBP_CLK_prop,
     PMHAL_PRCM_DIV_MLBP_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MLBP_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MLB_CLK_prop,
     PMHAL_PRCM_DIV_MLB_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MLB_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_HDMI_CLK_prop,
     PMHAL_PRCM_DIV_HDMI_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO1_CLK_prop,
     PMHAL_PRCM_DIV_VIDEO1_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_CLK_inNodes, pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VIDEO2_CLK_prop,
     PMHAL_PRCM_DIV_VIDEO2_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_prop,
     PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_ABE_SYS_CLK_prop,
     PMHAL_PRCM_DIV_ABE_SYS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_SYS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_prop,
     PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_TIMER_SYS_CLK_prop,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_TIMER_SYS_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_IPU1_GCLK_prop,
     PMHAL_PRCM_DIV_IPU1_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_IPU1_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_IPU2_GCLK_prop,
     PMHAL_PRCM_DIV_IPU2_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_IPU2_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_32K_CLK_prop,
     PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VPE_GCLK_prop,
     PMHAL_PRCM_DIV_VPE_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VPE_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_APLL_PCIE_prop,
     PMHAL_PRCM_DPLL_APLL_PCIE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_APLL_PCIE_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_ABE_prop,
     PMHAL_PRCM_DPLL_ABE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_ABE_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_CORE_prop,
     PMHAL_PRCM_DPLL_CORE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_CORE_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_DDR_prop,
     PMHAL_PRCM_DPLL_DDR_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DDR_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_GMAC_prop,
     PMHAL_PRCM_DPLL_GMAC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_GMAC_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_GPU_prop,
     PMHAL_PRCM_DPLL_GPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_GPU_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_IVA_prop,
     PMHAL_PRCM_DPLL_IVA_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_IVA_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_PCIE_REF_prop,
     PMHAL_PRCM_DPLL_PCIE_REF_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PCIE_REF_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_PER_prop,
     PMHAL_PRCM_DPLL_PER_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PER_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_USB_prop,
     PMHAL_PRCM_DPLL_USB_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_USB_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_DSP_prop,
     PMHAL_PRCM_DPLL_DSP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DSP_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_EVE_prop,
     PMHAL_PRCM_DPLL_EVE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_EVE_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_MPU_prop,
     PMHAL_PRCM_DPLL_MPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_MPU_inNodes,
                pmhalClockTreeNodeId)},
    {NULL,
     NULL,
     0U},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {NULL,
     NULL,
     0U},
#endif
    {NULL,
     NULL,
     0U},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    {&PMHAL_PRCM_MOD_ATL_prop,
     PMHAL_PRCM_MOD_ATL_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ATL_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
    {&PMHAL_PRCM_MOD_DUMMY_MODULE4_prop,
     PMHAL_PRCM_MOD_DUMMY_MODULE4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DUMMY_MODULE4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
    {&PMHAL_PRCM_MOD_DUMMY_MODULE1_prop,
     PMHAL_PRCM_MOD_DUMMY_MODULE1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DUMMY_MODULE1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
    {&PMHAL_PRCM_MOD_DUMMY_MODULE2_prop,
     PMHAL_PRCM_MOD_DUMMY_MODULE2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DUMMY_MODULE2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
    {&PMHAL_PRCM_MOD_DUMMY_MODULE3_prop,
     PMHAL_PRCM_MOD_DUMMY_MODULE3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DUMMY_MODULE3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
    {&PMHAL_PRCM_MOD_IO_SRCOMP_CORE_prop,
     PMHAL_PRCM_MOD_IO_SRCOMP_CORE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IO_SRCOMP_CORE_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    {&PMHAL_PRCM_MOD_SMARTREFLEX_CORE_prop,
     PMHAL_PRCM_MOD_SMARTREFLEX_CORE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_CORE_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    {&PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_prop,
     PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
    {&PMHAL_PRCM_MOD_SMARTREFLEX_GPU_prop,
     PMHAL_PRCM_MOD_SMARTREFLEX_GPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_GPU_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
    {&PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_prop,
     PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
    {&PMHAL_PRCM_MOD_SMARTREFLEX_MPU_prop,
     PMHAL_PRCM_MOD_SMARTREFLEX_MPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_MPU_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
    {&PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON_prop,
     PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
    {&PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON_prop,
     PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
    {&PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON_prop,
     PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    {&PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_prop,
     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
    {&PMHAL_PRCM_MOD_DMA_SYSTEM_prop,
     PMHAL_PRCM_MOD_DMA_SYSTEM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DMA_SYSTEM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    {&PMHAL_PRCM_MOD_DSP1_prop,
     PMHAL_PRCM_MOD_DSP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_MOD_DSP2_prop,
     PMHAL_PRCM_MOD_DSP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSP2_inNodes,
                pmhalClockTreeNodeId)},
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
    {&PMHAL_PRCM_MOD_BB2D_prop,
     PMHAL_PRCM_MOD_BB2D_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_BB2D_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {&PMHAL_PRCM_MOD_DSS_prop,
     PMHAL_PRCM_MOD_DSS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
    {&PMHAL_PRCM_MOD_SDVENC_prop,
     PMHAL_PRCM_MOD_SDVENC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SDVENC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    {&PMHAL_PRCM_MOD_DLL_prop,
     PMHAL_PRCM_MOD_DLL_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DLL_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
    {&PMHAL_PRCM_MOD_DMM_prop,
     PMHAL_PRCM_MOD_DMM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DMM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {&PMHAL_PRCM_MOD_EMIF1_prop,
     PMHAL_PRCM_MOD_EMIF1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    {&PMHAL_PRCM_MOD_EMIF2_prop,
     PMHAL_PRCM_MOD_EMIF2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
    {&PMHAL_PRCM_MOD_EMIF_OCP_FW_prop,
     PMHAL_PRCM_MOD_EMIF_OCP_FW_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF_OCP_FW_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_MOD_EVE1_prop,
     PMHAL_PRCM_MOD_EVE1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EVE1_inNodes,
                pmhalClockTreeNodeId)},
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_MOD_EVE2_prop,
     PMHAL_PRCM_MOD_EVE2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EVE2_inNodes,
                pmhalClockTreeNodeId)},
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE3
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_MOD_EVE3_prop,
     PMHAL_PRCM_MOD_EVE3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EVE3_inNodes,
                pmhalClockTreeNodeId)},
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE4
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {&PMHAL_PRCM_MOD_EVE4_prop,
     PMHAL_PRCM_MOD_EVE4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EVE4_inNodes,
                pmhalClockTreeNodeId)},
#endif
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {&PMHAL_PRCM_MOD_CPGMAC_prop,
     PMHAL_PRCM_MOD_CPGMAC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CPGMAC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
    {&PMHAL_PRCM_MOD_GPU_prop,
     PMHAL_PRCM_MOD_GPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPU_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
    {&PMHAL_PRCM_MOD_I2C5_prop,
     PMHAL_PRCM_MOD_I2C5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    {&PMHAL_PRCM_MOD_MCASP1_prop,
     PMHAL_PRCM_MOD_MCASP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    {&PMHAL_PRCM_MOD_TIMER5_prop,
     PMHAL_PRCM_MOD_TIMER5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    {&PMHAL_PRCM_MOD_TIMER6_prop,
     PMHAL_PRCM_MOD_TIMER6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    {&PMHAL_PRCM_MOD_TIMER7_prop,
     PMHAL_PRCM_MOD_TIMER7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    {&PMHAL_PRCM_MOD_TIMER8_prop,
     PMHAL_PRCM_MOD_TIMER8_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER8_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
    {&PMHAL_PRCM_MOD_UART6_prop,
     PMHAL_PRCM_MOD_UART6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    {&PMHAL_PRCM_MOD_IPU1_prop,
     PMHAL_PRCM_MOD_IPU1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IPU1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
    {&PMHAL_PRCM_MOD_IPU2_prop,
     PMHAL_PRCM_MOD_IPU2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IPU2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
    {&PMHAL_PRCM_MOD_IVA_prop,
     PMHAL_PRCM_MOD_IVA_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IVA_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
    {&PMHAL_PRCM_MOD_SL2_prop,
     PMHAL_PRCM_MOD_SL2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SL2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    {&PMHAL_PRCM_MOD_IEEE1500_2_OCP_prop,
     PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
    {&PMHAL_PRCM_MOD_MMC1_prop,
     PMHAL_PRCM_MOD_MMC1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
    {&PMHAL_PRCM_MOD_MMC2_prop,
     PMHAL_PRCM_MOD_MMC2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
    {&PMHAL_PRCM_MOD_MLB_SS_prop,
     PMHAL_PRCM_MOD_MLB_SS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MLB_SS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
    {&PMHAL_PRCM_MOD_SATA_prop,
     PMHAL_PRCM_MOD_SATA_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SATA_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
    {&PMHAL_PRCM_MOD_OCP2SCP1_prop,
     PMHAL_PRCM_MOD_OCP2SCP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCP2SCP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
    {&PMHAL_PRCM_MOD_OCP2SCP3_prop,
     PMHAL_PRCM_MOD_OCP2SCP3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCP2SCP3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    {&PMHAL_PRCM_MOD_USB_OTG_SS1_prop,
     PMHAL_PRCM_MOD_USB_OTG_SS1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    {&PMHAL_PRCM_MOD_USB_OTG_SS2_prop,
     PMHAL_PRCM_MOD_USB_OTG_SS2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
    {&PMHAL_PRCM_MOD_USB_OTG_SS3_prop,
     PMHAL_PRCM_MOD_USB_OTG_SS3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
    {&PMHAL_PRCM_MOD_USB_OTG_SS4_prop,
     PMHAL_PRCM_MOD_USB_OTG_SS4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
    {&PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_prop,
     PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
    {&PMHAL_PRCM_MOD_DLL_AGING_prop,
     PMHAL_PRCM_MOD_DLL_AGING_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DLL_AGING_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
    {&PMHAL_PRCM_MOD_L3_INSTR_prop,
     PMHAL_PRCM_MOD_L3_INSTR_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L3_INSTR_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    {&PMHAL_PRCM_MOD_L3_MAIN_2_prop,
     PMHAL_PRCM_MOD_L3_MAIN_2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    {&PMHAL_PRCM_MOD_OCP_WP_NOC_prop,
     PMHAL_PRCM_MOD_OCP_WP_NOC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCP_WP_NOC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    {&PMHAL_PRCM_MOD_GPMC_prop,
     PMHAL_PRCM_MOD_GPMC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPMC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    {&PMHAL_PRCM_MOD_L3_MAIN_1_prop,
     PMHAL_PRCM_MOD_L3_MAIN_1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    {&PMHAL_PRCM_MOD_MMU_EDMA_prop,
     PMHAL_PRCM_MOD_MMU_EDMA_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMU_EDMA_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
    {&PMHAL_PRCM_MOD_MMU_PCIESS_prop,
     PMHAL_PRCM_MOD_MMU_PCIESS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMU_PCIESS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    {&PMHAL_PRCM_MOD_OCMC_RAM1_prop,
     PMHAL_PRCM_MOD_OCMC_RAM1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
    {&PMHAL_PRCM_MOD_OCMC_RAM2_prop,
     PMHAL_PRCM_MOD_OCMC_RAM2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
    {&PMHAL_PRCM_MOD_OCMC_RAM3_prop,
     PMHAL_PRCM_MOD_OCMC_RAM3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
    {&PMHAL_PRCM_MOD_OCMC_ROM_prop,
     PMHAL_PRCM_MOD_OCMC_ROM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_ROM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
    {&PMHAL_PRCM_MOD_SPARE_IVA2_prop,
     PMHAL_PRCM_MOD_SPARE_IVA2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_IVA2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
    {&PMHAL_PRCM_MOD_VCP1_prop,
     PMHAL_PRCM_MOD_VCP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VCP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
    {&PMHAL_PRCM_MOD_VCP2_prop,
     PMHAL_PRCM_MOD_VCP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VCP2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
    {&PMHAL_PRCM_MOD_SPARE_CME_prop,
     PMHAL_PRCM_MOD_SPARE_CME_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_CME_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
    {&PMHAL_PRCM_MOD_SPARE_HDMI_prop,
     PMHAL_PRCM_MOD_SPARE_HDMI_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_HDMI_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
    {&PMHAL_PRCM_MOD_SPARE_ICM_prop,
     PMHAL_PRCM_MOD_SPARE_ICM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_ICM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
    {&PMHAL_PRCM_MOD_SPARE_SATA2_prop,
     PMHAL_PRCM_MOD_SPARE_SATA2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SATA2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
    {&PMHAL_PRCM_MOD_SPARE_UNKNOWN4_prop,
     PMHAL_PRCM_MOD_SPARE_UNKNOWN4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_UNKNOWN4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
    {&PMHAL_PRCM_MOD_SPARE_UNKNOWN5_prop,
     PMHAL_PRCM_MOD_SPARE_UNKNOWN5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_UNKNOWN5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
    {&PMHAL_PRCM_MOD_SPARE_UNKNOWN6_prop,
     PMHAL_PRCM_MOD_SPARE_UNKNOWN6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_UNKNOWN6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
    {&PMHAL_PRCM_MOD_SPARE_VIDEOPLL1_prop,
     PMHAL_PRCM_MOD_SPARE_VIDEOPLL1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_VIDEOPLL1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
    {&PMHAL_PRCM_MOD_SPARE_VIDEOPLL2_prop,
     PMHAL_PRCM_MOD_SPARE_VIDEOPLL2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_VIDEOPLL2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
    {&PMHAL_PRCM_MOD_SPARE_VIDEOPLL3_prop,
     PMHAL_PRCM_MOD_SPARE_VIDEOPLL3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_VIDEOPLL3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
    {&PMHAL_PRCM_MOD_TPCC_prop,
     PMHAL_PRCM_MOD_TPCC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TPCC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    {&PMHAL_PRCM_MOD_TPTC1_prop,
     PMHAL_PRCM_MOD_TPTC1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TPTC1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    {&PMHAL_PRCM_MOD_TPTC2_prop,
     PMHAL_PRCM_MOD_TPTC2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TPTC2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    {&PMHAL_PRCM_MOD_L4_CFG_prop,
     PMHAL_PRCM_MOD_L4_CFG_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_CFG_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
    {&PMHAL_PRCM_MOD_OCP2SCP2_prop,
     PMHAL_PRCM_MOD_OCP2SCP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCP2SCP2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
    {&PMHAL_PRCM_MOD_SAR_ROM_prop,
     PMHAL_PRCM_MOD_SAR_ROM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SAR_ROM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
    {&PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC_prop,
     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
    {&PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM_prop,
     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
    {&PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP_prop,
     PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    {&PMHAL_PRCM_MOD_SPINLOCK_prop,
     PMHAL_PRCM_MOD_SPINLOCK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPINLOCK_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
    {&PMHAL_PRCM_MOD_IO_DELAY_BLOCK_prop,
     PMHAL_PRCM_MOD_IO_DELAY_BLOCK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IO_DELAY_BLOCK_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    {&PMHAL_PRCM_MOD_MAILBOX1_prop,
     PMHAL_PRCM_MOD_MAILBOX1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
    {&PMHAL_PRCM_MOD_MAILBOX10_prop,
     PMHAL_PRCM_MOD_MAILBOX10_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX10_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
    {&PMHAL_PRCM_MOD_MAILBOX11_prop,
     PMHAL_PRCM_MOD_MAILBOX11_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX11_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
    {&PMHAL_PRCM_MOD_MAILBOX12_prop,
     PMHAL_PRCM_MOD_MAILBOX12_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX12_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
    {&PMHAL_PRCM_MOD_MAILBOX13_prop,
     PMHAL_PRCM_MOD_MAILBOX13_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX13_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    {&PMHAL_PRCM_MOD_MAILBOX2_prop,
     PMHAL_PRCM_MOD_MAILBOX2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
    {&PMHAL_PRCM_MOD_MAILBOX3_prop,
     PMHAL_PRCM_MOD_MAILBOX3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
    {&PMHAL_PRCM_MOD_MAILBOX4_prop,
     PMHAL_PRCM_MOD_MAILBOX4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
    {&PMHAL_PRCM_MOD_MAILBOX5_prop,
     PMHAL_PRCM_MOD_MAILBOX5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
    {&PMHAL_PRCM_MOD_MAILBOX6_prop,
     PMHAL_PRCM_MOD_MAILBOX6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
    {&PMHAL_PRCM_MOD_MAILBOX7_prop,
     PMHAL_PRCM_MOD_MAILBOX7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
    {&PMHAL_PRCM_MOD_MAILBOX8_prop,
     PMHAL_PRCM_MOD_MAILBOX8_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX8_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
    {&PMHAL_PRCM_MOD_MAILBOX9_prop,
     PMHAL_PRCM_MOD_MAILBOX9_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX9_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    {&PMHAL_PRCM_MOD_I2C1_prop,
     PMHAL_PRCM_MOD_I2C1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    {&PMHAL_PRCM_MOD_I2C2_prop,
     PMHAL_PRCM_MOD_I2C2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
    {&PMHAL_PRCM_MOD_I2C3_prop,
     PMHAL_PRCM_MOD_I2C3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
    {&PMHAL_PRCM_MOD_I2C4_prop,
     PMHAL_PRCM_MOD_I2C4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    {&PMHAL_PRCM_MOD_L4_PER1_prop,
     PMHAL_PRCM_MOD_L4_PER1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
    {&PMHAL_PRCM_MOD_TIMER10_prop,
     PMHAL_PRCM_MOD_TIMER10_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER10_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
    {&PMHAL_PRCM_MOD_TIMER11_prop,
     PMHAL_PRCM_MOD_TIMER11_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER11_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    {&PMHAL_PRCM_MOD_TIMER2_prop,
     PMHAL_PRCM_MOD_TIMER2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    {&PMHAL_PRCM_MOD_TIMER3_prop,
     PMHAL_PRCM_MOD_TIMER3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    {&PMHAL_PRCM_MOD_TIMER4_prop,
     PMHAL_PRCM_MOD_TIMER4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
    {&PMHAL_PRCM_MOD_TIMER9_prop,
     PMHAL_PRCM_MOD_TIMER9_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER9_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    {&PMHAL_PRCM_MOD_ELM_prop,
     PMHAL_PRCM_MOD_ELM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ELM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
    {&PMHAL_PRCM_MOD_HDQ1W_prop,
     PMHAL_PRCM_MOD_HDQ1W_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_HDQ1W_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    {&PMHAL_PRCM_MOD_MCSPI1_prop,
     PMHAL_PRCM_MOD_MCSPI1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    {&PMHAL_PRCM_MOD_MCSPI2_prop,
     PMHAL_PRCM_MOD_MCSPI2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    {&PMHAL_PRCM_MOD_MCSPI3_prop,
     PMHAL_PRCM_MOD_MCSPI3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    {&PMHAL_PRCM_MOD_MCSPI4_prop,
     PMHAL_PRCM_MOD_MCSPI4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    {&PMHAL_PRCM_MOD_UART1_prop,
     PMHAL_PRCM_MOD_UART1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    {&PMHAL_PRCM_MOD_UART2_prop,
     PMHAL_PRCM_MOD_UART2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    {&PMHAL_PRCM_MOD_UART3_prop,
     PMHAL_PRCM_MOD_UART3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
    {&PMHAL_PRCM_MOD_UART4_prop,
     PMHAL_PRCM_MOD_UART4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
    {&PMHAL_PRCM_MOD_UART5_prop,
     PMHAL_PRCM_MOD_UART5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    {&PMHAL_PRCM_MOD_GPIO2_prop,
     PMHAL_PRCM_MOD_GPIO2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    {&PMHAL_PRCM_MOD_GPIO3_prop,
     PMHAL_PRCM_MOD_GPIO3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    {&PMHAL_PRCM_MOD_GPIO4_prop,
     PMHAL_PRCM_MOD_GPIO4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
    {&PMHAL_PRCM_MOD_GPIO5_prop,
     PMHAL_PRCM_MOD_GPIO5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
    {&PMHAL_PRCM_MOD_GPIO6_prop,
     PMHAL_PRCM_MOD_GPIO6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
    {&PMHAL_PRCM_MOD_GPIO7_prop,
     PMHAL_PRCM_MOD_GPIO7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
    {&PMHAL_PRCM_MOD_GPIO8_prop,
     PMHAL_PRCM_MOD_GPIO8_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO8_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
    {&PMHAL_PRCM_MOD_MMC3_prop,
     PMHAL_PRCM_MOD_MMC3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    {&PMHAL_PRCM_MOD_MMC4_prop,
     PMHAL_PRCM_MOD_MMC4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    {&PMHAL_PRCM_MOD_DCAN2_prop,
     PMHAL_PRCM_MOD_DCAN2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    {&PMHAL_PRCM_MOD_L4_PER2_prop,
     PMHAL_PRCM_MOD_L4_PER2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
    {&PMHAL_PRCM_MOD_UART7_prop,
     PMHAL_PRCM_MOD_UART7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
    {&PMHAL_PRCM_MOD_UART8_prop,
     PMHAL_PRCM_MOD_UART8_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART8_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
    {&PMHAL_PRCM_MOD_UART9_prop,
     PMHAL_PRCM_MOD_UART9_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART9_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    {&PMHAL_PRCM_MOD_PRUSS1_prop,
     PMHAL_PRCM_MOD_PRUSS1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PRUSS1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    {&PMHAL_PRCM_MOD_PRUSS2_prop,
     PMHAL_PRCM_MOD_PRUSS2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PRUSS2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    {&PMHAL_PRCM_MOD_MCASP2_prop,
     PMHAL_PRCM_MOD_MCASP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    {&PMHAL_PRCM_MOD_MCASP3_prop,
     PMHAL_PRCM_MOD_MCASP3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
    {&PMHAL_PRCM_MOD_MCASP4_prop,
     PMHAL_PRCM_MOD_MCASP4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
    {&PMHAL_PRCM_MOD_MCASP5_prop,
     PMHAL_PRCM_MOD_MCASP5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
    {&PMHAL_PRCM_MOD_MCASP6_prop,
     PMHAL_PRCM_MOD_MCASP6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
    {&PMHAL_PRCM_MOD_MCASP7_prop,
     PMHAL_PRCM_MOD_MCASP7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
    {&PMHAL_PRCM_MOD_MCASP8_prop,
     PMHAL_PRCM_MOD_MCASP8_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP8_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    {&PMHAL_PRCM_MOD_PWMSS1_prop,
     PMHAL_PRCM_MOD_PWMSS1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
    {&PMHAL_PRCM_MOD_PWMSS2_prop,
     PMHAL_PRCM_MOD_PWMSS2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
    {&PMHAL_PRCM_MOD_PWMSS3_prop,
     PMHAL_PRCM_MOD_PWMSS3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    {&PMHAL_PRCM_MOD_QSPI_prop,
     PMHAL_PRCM_MOD_QSPI_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_QSPI_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    {&PMHAL_PRCM_MOD_L4_PER3_prop,
     PMHAL_PRCM_MOD_L4_PER3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
    {&PMHAL_PRCM_MOD_TIMER13_prop,
     PMHAL_PRCM_MOD_TIMER13_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER13_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
    {&PMHAL_PRCM_MOD_TIMER14_prop,
     PMHAL_PRCM_MOD_TIMER14_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER14_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
    {&PMHAL_PRCM_MOD_TIMER15_prop,
     PMHAL_PRCM_MOD_TIMER15_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER15_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
    {&PMHAL_PRCM_MOD_TIMER16_prop,
     PMHAL_PRCM_MOD_TIMER16_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER16_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES1
    {&PMHAL_PRCM_MOD_AES1_prop,
     PMHAL_PRCM_MOD_AES1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_AES1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES2
    {&PMHAL_PRCM_MOD_AES2_prop,
     PMHAL_PRCM_MOD_AES2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_AES2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
    {&PMHAL_PRCM_MOD_DES3DES_prop,
     PMHAL_PRCM_MOD_DES3DES_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DES3DES_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
    {&PMHAL_PRCM_MOD_DMA_CRYPTO_prop,
     PMHAL_PRCM_MOD_DMA_CRYPTO_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DMA_CRYPTO_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
    {&PMHAL_PRCM_MOD_FPKA_prop,
     PMHAL_PRCM_MOD_FPKA_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_FPKA_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
    {&PMHAL_PRCM_MOD_RNG_prop,
     PMHAL_PRCM_MOD_RNG_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RNG_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
    {&PMHAL_PRCM_MOD_SHA2MD51_prop,
     PMHAL_PRCM_MOD_SHA2MD51_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SHA2MD51_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
    {&PMHAL_PRCM_MOD_SHA2MD52_prop,
     PMHAL_PRCM_MOD_SHA2MD52_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SHA2MD52_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
    {&PMHAL_PRCM_MOD_MPU_prop,
     PMHAL_PRCM_MOD_MPU_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MPU_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
    {&PMHAL_PRCM_MOD_MPU_MPU_DBG_prop,
     PMHAL_PRCM_MOD_MPU_MPU_DBG_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MPU_MPU_DBG_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    {&PMHAL_PRCM_MOD_PCIESS1_prop,
     PMHAL_PRCM_MOD_PCIESS1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PCIESS1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    {&PMHAL_PRCM_MOD_PCIESS2_prop,
     PMHAL_PRCM_MOD_PCIESS2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PCIESS2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
    {&PMHAL_PRCM_MOD_RTCSS_prop,
     PMHAL_PRCM_MOD_RTCSS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTCSS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI1
    {&PMHAL_PRCM_MOD_CSI1_prop,
     PMHAL_PRCM_MOD_CSI1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CSI1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CSI2
    {&PMHAL_PRCM_MOD_CSI2_prop,
     PMHAL_PRCM_MOD_CSI2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CSI2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CSI2 */
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
    {&PMHAL_PRCM_MOD_LVDSRX_prop,
     PMHAL_PRCM_MOD_LVDSRX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_LVDSRX_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    {&PMHAL_PRCM_MOD_VIP1_prop,
     PMHAL_PRCM_MOD_VIP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VIP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
    {&PMHAL_PRCM_MOD_VIP2_prop,
     PMHAL_PRCM_MOD_VIP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VIP2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP3
    {&PMHAL_PRCM_MOD_VIP3_prop,
     PMHAL_PRCM_MOD_VIP3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VIP3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
    {&PMHAL_PRCM_MOD_VPE_prop,
     PMHAL_PRCM_MOD_VPE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VPE_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {&PMHAL_PRCM_MOD_DEBUG_LOGIC_prop,
     PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
    {&PMHAL_PRCM_MOD_MPU_EMU_DBG_prop,
     PMHAL_PRCM_MOD_MPU_EMU_DBG_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MPU_EMU_DBG_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    {&PMHAL_PRCM_MOD_ADC_prop,
     PMHAL_PRCM_MOD_ADC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ADC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    {&PMHAL_PRCM_MOD_COUNTER_32K_prop,
     PMHAL_PRCM_MOD_COUNTER_32K_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_COUNTER_32K_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
    {&PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_prop,
     PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    {&PMHAL_PRCM_MOD_DCAN1_prop,
     PMHAL_PRCM_MOD_DCAN1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    {&PMHAL_PRCM_MOD_GPIO1_prop,
     PMHAL_PRCM_MOD_GPIO1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
    {&PMHAL_PRCM_MOD_IO_SRCOMP_WKUP_prop,
     PMHAL_PRCM_MOD_IO_SRCOMP_WKUP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IO_SRCOMP_WKUP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
    {&PMHAL_PRCM_MOD_KBD_prop,
     PMHAL_PRCM_MOD_KBD_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_KBD_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    {&PMHAL_PRCM_MOD_L4_WKUP_prop,
     PMHAL_PRCM_MOD_L4_WKUP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_WKUP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
    {&PMHAL_PRCM_MOD_SAR_RAM_prop,
     PMHAL_PRCM_MOD_SAR_RAM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SAR_RAM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
    {&PMHAL_PRCM_MOD_SPARE_SAFETY1_prop,
     PMHAL_PRCM_MOD_SPARE_SAFETY1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SAFETY1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
    {&PMHAL_PRCM_MOD_SPARE_SAFETY2_prop,
     PMHAL_PRCM_MOD_SPARE_SAFETY2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SAFETY2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
    {&PMHAL_PRCM_MOD_SPARE_SAFETY3_prop,
     PMHAL_PRCM_MOD_SPARE_SAFETY3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SAFETY3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
    {&PMHAL_PRCM_MOD_SPARE_SAFETY4_prop,
     PMHAL_PRCM_MOD_SPARE_SAFETY4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_SAFETY4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
    {&PMHAL_PRCM_MOD_SPARE_UNKNOWN2_prop,
     PMHAL_PRCM_MOD_SPARE_UNKNOWN2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_UNKNOWN2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
    {&PMHAL_PRCM_MOD_SPARE_UNKNOWN3_prop,
     PMHAL_PRCM_MOD_SPARE_UNKNOWN3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPARE_UNKNOWN3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    {&PMHAL_PRCM_MOD_TIMER1_prop,
     PMHAL_PRCM_MOD_TIMER1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
    {&PMHAL_PRCM_MOD_TIMER12_prop,
     PMHAL_PRCM_MOD_TIMER12_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER12_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
    {&PMHAL_PRCM_MOD_UART10_prop,
     PMHAL_PRCM_MOD_UART10_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART10_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
    {&PMHAL_PRCM_MOD_WD_TIMER1_prop,
     PMHAL_PRCM_MOD_WD_TIMER1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_WD_TIMER1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
    {&PMHAL_PRCM_MOD_WD_TIMER2_prop,
     PMHAL_PRCM_MOD_WD_TIMER2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_WD_TIMER2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAL
    {&PMHAL_PRCM_MOD_CAL_prop,
     PMHAL_PRCM_MOD_CAL_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CAL_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAL */
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C6
    {&PMHAL_PRCM_MOD_I2C6_prop,
     PMHAL_PRCM_MOD_I2C6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C6 */
#endif
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_PCIE_DCLK connected to PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_DIV_PCIE_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS1 connected to PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_PCIE_PHY_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS1 connected to PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS1_DIV_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO_DIV,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS2 connected to PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_PCIE_PHY_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS2 connected to PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS2_DIV_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_VCO_LDO_DIV,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_APLL_PCIE_toNodes[] =
{
    {PMHAL_PRCM_DIV_PCIE_DCLK,
     &PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_DIV_PCIE_DCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    {PMHAL_PRCM_MOD_PCIESS1,
     &PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    {PMHAL_PRCM_MOD_PCIESS1,
     &PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS1_DIV_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    {PMHAL_PRCM_MOD_PCIESS2,
     &PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS2_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    {PMHAL_PRCM_MOD_PCIESS2,
     &PMHAL_PRCM_DPLL_APLL_PCIE_PMHAL_PRCM_MOD_PCIESS2_DIV_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_GPU connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_GPU_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M3,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_GMAC connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_GMAC_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M3,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_DDR connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_DDR_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M3,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_CORE connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_CORE_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M3,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_CLK connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_USB_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_PER_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_LP_CLK connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_LP_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_24M_FCLK connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_24M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_ATL_GFCLK_MUX connected to PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_ATL_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_ABE connected to PMHAL_PRCM_DPLL_INP_CLKINPULOW
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp =
{PMHAL_PRCM_MUX_ABE_DPLL_BYPAS_CLK_MUX,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_ABE connected to PMHAL_PRCM_DPLL_INP_CLKINPHIF
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp =
{PMHAL_PRCM_NODE_UNDEF,
 NULL,
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_ABE connected to PMHAL_PRCM_DPLL_INP_CLKINP
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_ABE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_ABE
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_ABE_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_DPLL_GPU,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_GPU_edgeProp},
    {PMHAL_PRCM_DPLL_GMAC,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_GMAC_edgeProp},
    {PMHAL_PRCM_DPLL_DDR,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_DDR_edgeProp},
    {PMHAL_PRCM_DPLL_CORE,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_edgeProp},
    {PMHAL_PRCM_DIV_ABE_CLK,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_CLK_edgeProp},
    {PMHAL_PRCM_DIV_USB_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_USB_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_PER_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_LP_CLK_edgeProp},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_DIV_ABE_24M_FCLK_edgeProp},
    {PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_ABE_PMHAL_PRCM_MUX_ATL_GFCLK_MUX_edgeProp}
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H22,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_VIP1_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP1_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H23,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_VIP2_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP2_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H23,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_VIP3_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP3_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H23,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_L3_ICLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_L3_ICLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_VPE_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VPE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H23,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_BB2D connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_BB2D_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H24,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_IPU2_GCLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_IPU2_GCLK_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H22,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_USB_OTG_SS1 connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_USB_OTG_SS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS1 connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_PCIESS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PCIESS2 connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_PCIESS2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_VPE connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_VPE_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H23,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_VPE connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DPLL_ABE,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_CORE_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_VIP1_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP1_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_VIP2_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP2_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_VIP3_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP3_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_L3_ICLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_IPU2_GCLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_IPU2_GCLK_edgeProp},
    {PMHAL_PRCM_MUX_VPE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VPE_GCLK_MUX_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
    {PMHAL_PRCM_MOD_BB2D,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_BB2D_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    {PMHAL_PRCM_MOD_USB_OTG_SS1,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_USB_OTG_SS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    {PMHAL_PRCM_MOD_PCIESS1,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_PCIESS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    {PMHAL_PRCM_MOD_PCIESS2,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_PCIESS2_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
    {PMHAL_PRCM_MOD_VPE,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_VPE_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_EMIF_PHY_DCLK connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_EMIF_PHY_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_DLL connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_DLL_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H11,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_EMIF1 connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF1_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H11,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
 PMHAL_PRCM_CLK_EMIF_DLL_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_EMIF1 connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF1_PHY_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_EMIF_PHY_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_EMIF2 connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF2_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H11,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
 PMHAL_PRCM_CLK_EMIF_DLL_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_EMIF2 connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF2_PHY_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_EMIF_PHY_GCLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DPLL_ABE,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_DDR_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_EMIF_PHY_DCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    {PMHAL_PRCM_MOD_DLL,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_DLL_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {PMHAL_PRCM_MOD_EMIF1,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {PMHAL_PRCM_MOD_EMIF1,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF1_PHY_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    {PMHAL_PRCM_MOD_EMIF2,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF2_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    {PMHAL_PRCM_MOD_EMIF2,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MOD_EMIF2_PHY_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_RMII_REF_CLK_MUX connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H11,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GMII_M_CLK connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMII_M_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H11,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GMAC_250M_DCLK connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMAC_250M_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_CPGMAC connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_CPGMAC_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS1 connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_ICSS_CLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS1 connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS1_IEP_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_ICSS_IEP_CLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS2 connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_ICSS_CLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS2 connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS2_IEP_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_ICSS_IEP_CLK};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DPLL_ABE,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPHIF connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp
    =
    {PMHAL_PRCM_DPLL_ABE,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_GMAC_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_MUX_RMII_REF_CLK_MUX,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_GMAC_250M_DCLK,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMAC_250M_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_edgeProp},
    {PMHAL_PRCM_DIV_GMII_M_CLK,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_DIV_GMII_M_CLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {PMHAL_PRCM_MOD_CPGMAC,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_CPGMAC_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    {PMHAL_PRCM_MOD_PRUSS1,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    {PMHAL_PRCM_MOD_PRUSS1,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS1_IEP_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    {PMHAL_PRCM_MOD_PRUSS2,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS2_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    {PMHAL_PRCM_MOD_PRUSS2,
     &PMHAL_PRCM_DPLL_GMAC_PMHAL_PRCM_MOD_PRUSS2_IEP_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX connected to PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX connected to PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GPU_DCLK connected to PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DIV_GPU_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DPLL_ABE,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_GPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_GPU
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_GPU_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     &PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_GPU_DCLK,
     &PMHAL_PRCM_DPLL_GPU_PMHAL_PRCM_DIV_GPU_DCLK_edgeProp}
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_IVA_DCLK connected to PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DIV_IVA_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_IVA connected to PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_MOD_IVA_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M2,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_SL2 connected to PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_MOD_SL2_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M2,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp =
{PMHAL_PRCM_DIV_IVA_DPLL_HS_CLK,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_IVA - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_IVA
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_IVA_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DIV_IVA_DCLK,
     &PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_DIV_IVA_DCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
    {PMHAL_PRCM_MOD_IVA,
     &PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_MOD_IVA_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
    {PMHAL_PRCM_MOD_SL2,
     &PMHAL_PRCM_DPLL_IVA_PMHAL_PRCM_MOD_SL2_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_PCIE2_DCLK connected to PMHAL_PRCM_DPLL_PCIE_REF
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PCIE_REF_PMHAL_PRCM_DIV_PCIE2_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PCIE_REF - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_APLL_PCIE connected to PMHAL_PRCM_DPLL_PCIE_REF
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PCIE_REF_PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PCIE_REF - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_PCIE_REF
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_PCIE_REF_toNodes[] =
{
    {PMHAL_PRCM_DIV_PCIE2_DCLK,
     &PMHAL_PRCM_DPLL_PCIE_REF_PMHAL_PRCM_DIV_PCIE2_DCLK_edgeProp},
    {PMHAL_PRCM_DPLL_APLL_PCIE,
     &PMHAL_PRCM_DPLL_PCIE_REF_PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp}
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_QSPI_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_MMC1_FCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC1_FCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_MMC2_FCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC2_FCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_MMC3_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_MMC4_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART10_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART10_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART4_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART4_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART5_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART5_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART6_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART6_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART7_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART7_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART8_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART8_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_UART9_GFCLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART9_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_24M_CLK connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_24M_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H11,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_12M_FCLK connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_12M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_48M_FCLK connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_FUNC_96M_FCLK connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_DSS connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DSS_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H12,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS1 connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_PRUSS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_PRUSS2 connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_PRUSS2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DIV_PER_DPLL_HS_CLK,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_PER_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC1_FCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC2_FCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC3_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART10_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART10_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART4_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART4_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART5_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART5_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART6_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART6_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART7_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART7_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART8_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART8_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART9_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART9_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_24M_CLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_12M_FCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_12M_FCLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_96M_FCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {PMHAL_PRCM_MOD_DSS,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DSS_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    {PMHAL_PRCM_MOD_PRUSS1,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_PRUSS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    {PMHAL_PRCM_MOD_PRUSS2,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_PRUSS2_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_L3INIT_480M_DCLK connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DIV_L3INIT_480M_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_L3INIT_60M_FCLK connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DIV_L3INIT_60M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_USB_OTG_SS1 connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_MOD_USB_OTG_SS1_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_USB_OTG_SS2 connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_MOD_USB_OTG_SS2_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW connected to PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DIV_USB_DPLL_HS_CLK,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_USB_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DIV_L3INIT_480M_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_L3INIT_60M_FCLK,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_DIV_L3INIT_60M_FCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    {PMHAL_PRCM_MOD_USB_OTG_SS1,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_MOD_USB_OTG_SS1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    {PMHAL_PRCM_MOD_USB_OTG_SS2,
     &PMHAL_PRCM_DPLL_USB_PMHAL_PRCM_MOD_USB_OTG_SS2_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
};

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_MUX_EVE_GCLK_MUX
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DIV_DSP_GCLK
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DIV_DSP_GCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
/**
 *  \brief Structure defining property structure for PMHAL_PRCM_MOD_DSP1
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MOD_DSP1_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M2,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
/**
 *  \brief Structure defining property structure for PMHAL_PRCM_MOD_DSP2
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MOD_DSP2_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M2,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp  PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp =
{PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPHIF
 *         connected to PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp =
{PMHAL_PRCM_NODE_UNDEF,
 NULL,
 0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_DSP
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_DSP_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_DSP_GCLK,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_DIV_DSP_GCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    {PMHAL_PRCM_MOD_DSP1,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MOD_DSP1_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    {PMHAL_PRCM_MOD_DSP2,
     &PMHAL_PRCM_DPLL_DSP_PMHAL_PRCM_MOD_DSP2_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#endif
};

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_MUX_EVE_GCLK_MUX
 *         connected to PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DIV_EVE_DCLK
 *         connected to PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DIV_EVE_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DIV_EVE_DPLL_HS_CLK,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_EVE
 */
pmhalClockTreeInputEdge PMHAL_PRCM_DPLL_EVE_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_EVE_DCLK,
     &PMHAL_PRCM_DPLL_EVE_PMHAL_PRCM_DIV_EVE_DCLK_edgeProp}
};

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DIV_MPU_DCLK
 *         connected to PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DIV_MPU_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MPU
 *         connected to PMHAL_PRCM_DPLL_MPU
 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_MOD_MPU_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_M2,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MPU_MPU_DBG
 *         connected to PMHAL_PRCM_DPLL_MPU
 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_MOD_MPU_MPU_DBG_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */

/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DIV_MPU_DPLL_HS_CLK,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_MPU - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_MPU
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_MPU_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DIV_MPU_DCLK,
     &PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_DIV_MPU_DCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
    {PMHAL_PRCM_MOD_MPU,
     &PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_MOD_MPU_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
    {PMHAL_PRCM_MOD_MPU_MPU_DBG,
     &PMHAL_PRCM_DPLL_MPU_PMHAL_PRCM_MOD_MPU_MPU_DBG_edgeProp}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_L3_ICLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_L3_ICLK_edgeProp =
{PMHAL_PRCM_DIV_L3_ICLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_L3_ICLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_ATL_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_ATL_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ATL_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp =
{PMHAL_PRCM_DIV_L4_ROOT_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_L4_ROOT_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_PER_edgeProp =
{PMHAL_PRCM_DPLL_PER,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp =
{PMHAL_PRCM_DIV_FUNC_48M_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_48M_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_ROOT_CLK_SYS_32K
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_ROOT_CLK_SYS_32K_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_32K,
 NULL,
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN,
 NULL,
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_DDR_edgeProp =
{PMHAL_PRCM_DPLL_DDR,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RMII_REF_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RMII_REF_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RMII_REF_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_GMAC_edgeProp =
{PMHAL_PRCM_DPLL_GMAC,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_GMAC - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_edgeProp =
{PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_RGMII_5M_REF_CLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_edgeProp =
{PMHAL_PRCM_DIV_RGMII_5M_REF_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_RGMII_5M_REF_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp =
{PMHAL_PRCM_DIV_FUNC_96M_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_96M_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART6_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART6_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART6_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART6_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_MMC1_FCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_MMC1_FCLK_edgeProp =
{PMHAL_PRCM_DIV_MMC1_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_MMC1_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 NULL,
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_MMC2_FCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_MMC2_FCLK_edgeProp =
{PMHAL_PRCM_DIV_MMC2_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_MMC2_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_USB
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_USB_edgeProp =
{PMHAL_PRCM_DPLL_USB,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_USB - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_CORE_edgeProp =
{PMHAL_PRCM_DPLL_CORE,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_FUNC_12M_FCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_FUNC_12M_FCLK_edgeProp =
{PMHAL_PRCM_DIV_FUNC_12M_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_12M_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART2_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART4_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART4_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART4_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART5_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART5_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART5_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART5_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_MMC3_GFCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_MMC3_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_MMC3_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_MMC3_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_MMC4_GFCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_MMC4_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_MMC4_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_MMC4_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART7_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART7_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART7_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART7_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART8_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART8_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART8_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART8_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART9_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART9_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART9_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART9_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_QSPI_GFCLK
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DIV_QSPI_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_QSPI_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_QSPI_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_APLL_PCIE
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp =
{PMHAL_PRCM_DPLL_APLL_PCIE,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_APLL_PCIE - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_ADC_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_ADC_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_ADC_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ADC_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC,
     NULL,
     0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART10_GFCLK_MUX
 */
pmhalClockTreeEdgeProp         PMHAL_PRCM_MUX_UART10_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART10_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART10_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ATL
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ATL_fromNodes[] = {
    {PMHAL_PRCM_CLK_ATL_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_ATL_GFCLK,
     &PMHAL_PRCM_MUX_ATL_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_ATL_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SMARTREFLEX_CORE
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SMARTREFLEX_CORE_fromNodes[] = {
    {PMHAL_PRCM_CLK_COREAON_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_fromNodes[] =
{
    {PMHAL_PRCM_CLK_COREAON_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SMARTREFLEX_GPU
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SMARTREFLEX_GPU_fromNodes[] = {
    {PMHAL_PRCM_CLK_COREAON_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_fromNodes[] = {
    {PMHAL_PRCM_CLK_COREAON_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SMARTREFLEX_MPU
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SMARTREFLEX_MPU_fromNodes[] = {
    {PMHAL_PRCM_CLK_COREAON_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_fromNodes[] = {
    {PMHAL_PRCM_CLK_CUSTEFUSE_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK,
     &PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DMA_SYSTEM
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DMA_SYSTEM_fromNodes[] = {
    {PMHAL_PRCM_CLK_DMA_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_DMA_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_BB2D
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_BB2D_fromNodes[] = {
    {PMHAL_PRCM_CLK_BB2D_GFCLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_CLK_DSS_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DSS
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DSS_fromNodes[] = {
    {PMHAL_PRCM_CLK_DSS_GFCLK,
     &PMHAL_PRCM_DPLL_PER_edgeProp},
    {PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_DSS_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_DSS_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     &PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     &PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     &PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SDVENC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SDVENC_fromNodes[] = {
    {PMHAL_PRCM_CLK_DSS_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_SDVENC_GFCLK,
     &PMHAL_PRCM_ROOT_CLK_SDVENC_CLKIN_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_EMIF1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_EMIF1_fromNodes[] = {
    {PMHAL_PRCM_CLK_EMIF_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_EMIF_DLL_GCLK,
     &PMHAL_PRCM_DPLL_DDR_edgeProp},
    {PMHAL_PRCM_CLK_EMIF_PHY_GCLK,
     &PMHAL_PRCM_DPLL_DDR_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_EMIF2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_EMIF2_fromNodes[] = {
    {PMHAL_PRCM_CLK_EMIF_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_EMIF_DLL_GCLK,
     &PMHAL_PRCM_DPLL_DDR_edgeProp},
    {PMHAL_PRCM_CLK_EMIF_PHY_GCLK,
     &PMHAL_PRCM_DPLL_DDR_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_EMIF_OCP_FW
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_EMIF_OCP_FW_fromNodes[] = {
    {PMHAL_PRCM_CLK_EMIF_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_EMIF_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_CPGMAC_fromNodes[] = {
    {PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     &PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
     &PMHAL_PRCM_DIV_GMAC_GMII_REF_CLK_edgeProp},
    {PMHAL_PRCM_CLK_RGMII_5MHZ_CLK,
     &PMHAL_PRCM_DIV_RGMII_5M_REF_CLK_edgeProp},
    {PMHAL_PRCM_CLK_RMII_50MHZ_CLK,
     &PMHAL_PRCM_MUX_RMII_REF_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GMII_250MHZ_CLK,
     &PMHAL_PRCM_DPLL_GMAC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPU
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPU_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPU_CORE_GCLK,
     &PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GPU_HYD_GCLK,
     &PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C5_fromNodes[] = {
    {PMHAL_PRCM_CLK_IPU_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP1_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     &PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_edgeProp},
    {PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER5_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER5_GFCLK,
     &PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER6_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER6_GFCLK,
     &PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER7_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER7_GFCLK,
     &PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER8
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER8_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER8_GFCLK,
     &PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART6_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART6_GFCLK,
     &PMHAL_PRCM_MUX_UART6_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_IPU_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_IEEE1500_2_OCP
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_IEEE1500_2_OCP_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMC1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMC1_fromNodes[] = {
    {PMHAL_PRCM_CLK_MMC1_GFCLK,
     &PMHAL_PRCM_DIV_MMC1_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMC2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMC2_fromNodes[] = {
    {PMHAL_PRCM_CLK_MMC2_GFCLK,
     &PMHAL_PRCM_DIV_MMC2_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MLB_SS
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MLB_SS_fromNodes[] = {
    {PMHAL_PRCM_CLK_MLB_SHB_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_MLB_SPB_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SATA
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SATA_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_48M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_SATA_REF_GFCLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_USB_OTG_SS1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_USB_OTG_SS1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     &PMHAL_PRCM_DPLL_USB_edgeProp},
    {PMHAL_PRCM_CLK_USB_LFPS_TX_GFCLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_USB_OTG_SS2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_USB_OTG_SS2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
     &PMHAL_PRCM_DPLL_USB_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_USB_OTG_SS3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_USB_OTG_SS3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_USB_OTG_SS4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_USB_OTG_SS4_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L3_MAIN_2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L3_MAIN_2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INSTR_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_OCP_WP_NOC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_OCP_WP_NOC_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3INSTR_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L3_MAIN_1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L3_MAIN_1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMU_EDMA
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMU_EDMA_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMU_PCIESS
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMU_PCIESS_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_OCMC_RAM1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_OCMC_RAM1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_OCMC_RAM2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_OCMC_RAM2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_OCMC_RAM3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_OCMC_RAM3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L4_CFG
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L4_CFG_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SAR_ROM
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SAR_ROM_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_SPINLOCK
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_SPINLOCK_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_IO_DELAY_BLOCK
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_IO_DELAY_BLOCK_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX10
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX10_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX11
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX11_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX12
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX12_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX13
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX13_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX4_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX5_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX6_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX7_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX8
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX8_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MAILBOX9
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MAILBOX9_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C1_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C2_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C3_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C4_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_I2C6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_I2C6_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C6 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L4_PER1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L4_PER1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER10
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER10_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER10_GFCLK,
     &PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER11
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER11_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER11_GFCLK,
     &PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER2_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER2_GFCLK,
     &PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER3_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER3_GFCLK,
     &PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER4_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER4_GFCLK,
     &PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER9
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER9_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER9_GFCLK,
     &PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ELM
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ELM_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_HDQ1W
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_HDQ1W_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_12M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_12M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCSPI1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCSPI1_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCSPI2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCSPI2_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCSPI3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCSPI3_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCSPI4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCSPI4_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART1_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART1_GFCLK,
     &PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART2_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART2_GFCLK,
     &PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART3_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART3_GFCLK,
     &PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART4_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART4_GFCLK,
     &PMHAL_PRCM_MUX_UART4_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART5_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART5_GFCLK,
     &PMHAL_PRCM_MUX_UART5_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO2_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO3_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO4_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO5_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO6_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO7_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO8
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO8_fromNodes[] = {
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMC3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMC3_fromNodes[] = {
    {PMHAL_PRCM_CLK_MMC3_GFCLK,
     &PMHAL_PRCM_DIV_MMC3_GFCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MMC4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MMC4_fromNodes[] = {
    {PMHAL_PRCM_CLK_MMC4_GFCLK,
     &PMHAL_PRCM_DIV_MMC4_GFCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCAN2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCAN2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L4_PER2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L4_PER2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART7_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART7_GFCLK,
     &PMHAL_PRCM_MUX_UART7_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART8
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART8_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART8_GFCLK,
     &PMHAL_PRCM_MUX_UART8_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART9
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART9_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART9_GFCLK,
     &PMHAL_PRCM_MUX_UART9_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PRUSS1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PRUSS1_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_192M_GFCLK,
     &PMHAL_PRCM_DPLL_PER_edgeProp},
    {PMHAL_PRCM_CLK_ICSS_IEP_CLK,
     &PMHAL_PRCM_DPLL_GMAC_edgeProp},
    {PMHAL_PRCM_CLK_ICSS_CLK,
     &PMHAL_PRCM_DPLL_GMAC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PRUSS2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PRUSS2_fromNodes[] = {
    {PMHAL_PRCM_CLK_PER_192M_GFCLK,
     &PMHAL_PRCM_DPLL_PER_edgeProp},
    {PMHAL_PRCM_CLK_ICSS_IEP_CLK,
     &PMHAL_PRCM_DPLL_GMAC_edgeProp},
    {PMHAL_PRCM_CLK_ICSS_CLK,
     &PMHAL_PRCM_DPLL_GMAC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP2_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     &PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_edgeProp},
    {PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP3_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP4_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP4_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP5_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP5_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP6_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP6_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP7_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP7_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP8
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP8_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP8_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PWMSS1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PWMSS1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PWMSS2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PWMSS2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PWMSS3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PWMSS3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_QSPI
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_QSPI_fromNodes[] = {
    {PMHAL_PRCM_CLK_QSPI_GFCLK,
     &PMHAL_PRCM_DIV_QSPI_GFCLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_L4_PER3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_L4_PER3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER13
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER13_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER13_GFCLK,
     &PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER14
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER14_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER14_GFCLK,
     &PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER15
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER15_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER15_GFCLK,
     &PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER16
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER16_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER16_GFCLK,
     &PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DES3DES
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DES3DES_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DMA_CRYPTO
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DMA_CRYPTO_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_FPKA
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_FPKA_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RNG
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RNG_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4SEC_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PCIESS1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PCIESS1_fromNodes[] = {
    {PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_PHY_GCLK,
     &PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK,
     &PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_PCIESS2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_PCIESS2_fromNodes[] = {
    {PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_SYS_GFCLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_PHY_GCLK,
     &PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK,
     &PMHAL_PRCM_DPLL_APLL_PCIE_edgeProp},
    {PMHAL_PRCM_CLK_PCIE_32K_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTCSS
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTCSS_fromNodes[] = {
    {PMHAL_PRCM_CLK_RTC_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_RTC_AUX_CLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTC_32K_GFCLK,
     &PMHAL_PRCM_ROOT_CLK_SYS_32K_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_LVDSRX
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_LVDSRX_fromNodes[] = {
    {PMHAL_PRCM_CLK_LVDSRX_96M_GFCLK,
     &PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
    {PMHAL_PRCM_CLK_LVDSRX_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ADC_fromNodes[] = {
    {PMHAL_PRCM_CLK_ADC_GFCLK,
     &PMHAL_PRCM_MUX_ADC_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_ADC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_COUNTER_32K
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_COUNTER_32K_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_FUNC_32K_CLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCAN1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCAN1_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     &PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_GPIO1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_GPIO1_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_KBD
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_KBD_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER1_fromNodes[] = {
    {PMHAL_PRCM_CLK_TIMER1_GFCLK,
     &PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TIMER12
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TIMER12_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_SECURE_32K_CLK,
     &PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_UART10
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_UART10_fromNodes[] = {
    {PMHAL_PRCM_CLK_UART10_GFCLK,
     &PMHAL_PRCM_MUX_UART10_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_WD_TIMER1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_WD_TIMER1_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_SECURE_32K_CLK,
     &PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_WD_TIMER2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_WD_TIMER2_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */

const pmhalClockTreeOutputEdge prcmEdges[] =
{
    {PMHAL_PRCM_DPLL_APLL_PCIE,
     PMHAL_PRCM_DPLL_APLL_PCIE_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_APLL_PCIE_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_ABE,
     PMHAL_PRCM_DPLL_ABE_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_ABE_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_CORE,
     PMHAL_PRCM_DPLL_CORE_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_CORE_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_DDR,
     PMHAL_PRCM_DPLL_DDR_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DDR_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_GMAC,
     PMHAL_PRCM_DPLL_GMAC_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_GMAC_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_GPU,
     PMHAL_PRCM_DPLL_GPU_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_GPU_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_IVA,
     PMHAL_PRCM_DPLL_IVA_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_IVA_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_PCIE_REF,
     PMHAL_PRCM_DPLL_PCIE_REF_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PCIE_REF_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_PER,
     PMHAL_PRCM_DPLL_PER_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PER_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_USB,
     PMHAL_PRCM_DPLL_USB_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_USB_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_DSP,
     PMHAL_PRCM_DPLL_DSP_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DSP_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_EVE,
     PMHAL_PRCM_DPLL_EVE_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_EVE_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_MPU,
     PMHAL_PRCM_DPLL_MPU_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_MPU_toNodes, pmhalClockTreeInputEdge)},
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    {PMHAL_PRCM_MOD_ATL,
     PMHAL_PRCM_MOD_ATL_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ATL_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,
     PMHAL_PRCM_MOD_SMARTREFLEX_CORE_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_CORE_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,
     PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,
     PMHAL_PRCM_MOD_SMARTREFLEX_GPU_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_GPU_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,
     PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,
     PMHAL_PRCM_MOD_SMARTREFLEX_MPU_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_MPU_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,
     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
    {PMHAL_PRCM_MOD_DMA_SYSTEM,
     PMHAL_PRCM_MOD_DMA_SYSTEM_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DMA_SYSTEM_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
    {PMHAL_PRCM_MOD_BB2D,
     PMHAL_PRCM_MOD_BB2D_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_BB2D_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {PMHAL_PRCM_MOD_DSS,
     PMHAL_PRCM_MOD_DSS_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSS_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
    {PMHAL_PRCM_MOD_SDVENC,
     PMHAL_PRCM_MOD_SDVENC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SDVENC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {PMHAL_PRCM_MOD_EMIF1,
     PMHAL_PRCM_MOD_EMIF1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    {PMHAL_PRCM_MOD_EMIF2,
     PMHAL_PRCM_MOD_EMIF2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
    #endif
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
    {PMHAL_PRCM_MOD_EMIF_OCP_FW,
     PMHAL_PRCM_MOD_EMIF_OCP_FW_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF_OCP_FW_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {PMHAL_PRCM_MOD_CPGMAC,
     PMHAL_PRCM_MOD_CPGMAC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CPGMAC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
    {PMHAL_PRCM_MOD_GPU,
     PMHAL_PRCM_MOD_GPU_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPU_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
    {PMHAL_PRCM_MOD_I2C5,
     PMHAL_PRCM_MOD_I2C5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    {PMHAL_PRCM_MOD_MCASP1,
     PMHAL_PRCM_MOD_MCASP1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    {PMHAL_PRCM_MOD_TIMER5,
     PMHAL_PRCM_MOD_TIMER5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    {PMHAL_PRCM_MOD_TIMER6,
     PMHAL_PRCM_MOD_TIMER6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    {PMHAL_PRCM_MOD_TIMER7,
     PMHAL_PRCM_MOD_TIMER7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    {PMHAL_PRCM_MOD_TIMER8,
     PMHAL_PRCM_MOD_TIMER8_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER8_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
    {PMHAL_PRCM_MOD_UART6,
     PMHAL_PRCM_MOD_UART6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,
     PMHAL_PRCM_MOD_IEEE1500_2_OCP_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IEEE1500_2_OCP_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
    {PMHAL_PRCM_MOD_MMC1,
     PMHAL_PRCM_MOD_MMC1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
    {PMHAL_PRCM_MOD_MMC2,
     PMHAL_PRCM_MOD_MMC2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
    {PMHAL_PRCM_MOD_MLB_SS,
     PMHAL_PRCM_MOD_MLB_SS_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MLB_SS_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
    {PMHAL_PRCM_MOD_SATA,
     PMHAL_PRCM_MOD_SATA_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SATA_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    {PMHAL_PRCM_MOD_USB_OTG_SS1,
     PMHAL_PRCM_MOD_USB_OTG_SS1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    {PMHAL_PRCM_MOD_USB_OTG_SS2,
     PMHAL_PRCM_MOD_USB_OTG_SS2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
    {PMHAL_PRCM_MOD_USB_OTG_SS3,
     PMHAL_PRCM_MOD_USB_OTG_SS3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
    {PMHAL_PRCM_MOD_USB_OTG_SS4,
     PMHAL_PRCM_MOD_USB_OTG_SS4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_USB_OTG_SS4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
    #endif
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    {PMHAL_PRCM_MOD_L3_MAIN_2,
     PMHAL_PRCM_MOD_L3_MAIN_2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    {PMHAL_PRCM_MOD_OCP_WP_NOC,
     PMHAL_PRCM_MOD_OCP_WP_NOC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCP_WP_NOC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    {PMHAL_PRCM_MOD_L3_MAIN_1,
     PMHAL_PRCM_MOD_L3_MAIN_1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    {PMHAL_PRCM_MOD_MMU_EDMA,
     PMHAL_PRCM_MOD_MMU_EDMA_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMU_EDMA_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
    {PMHAL_PRCM_MOD_MMU_PCIESS,
     PMHAL_PRCM_MOD_MMU_PCIESS_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMU_PCIESS_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    {PMHAL_PRCM_MOD_OCMC_RAM1,
     PMHAL_PRCM_MOD_OCMC_RAM1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
    {PMHAL_PRCM_MOD_OCMC_RAM2,
     PMHAL_PRCM_MOD_OCMC_RAM2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
    {PMHAL_PRCM_MOD_OCMC_RAM3,
     PMHAL_PRCM_MOD_OCMC_RAM3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
    #endif
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    {PMHAL_PRCM_MOD_L4_CFG,
     PMHAL_PRCM_MOD_L4_CFG_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_CFG_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
    {PMHAL_PRCM_MOD_SAR_ROM,
     PMHAL_PRCM_MOD_SAR_ROM_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SAR_ROM_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    {PMHAL_PRCM_MOD_SPINLOCK,
     PMHAL_PRCM_MOD_SPINLOCK_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPINLOCK_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,
     PMHAL_PRCM_MOD_IO_DELAY_BLOCK_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IO_DELAY_BLOCK_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    {PMHAL_PRCM_MOD_MAILBOX1,
     PMHAL_PRCM_MOD_MAILBOX1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
    {PMHAL_PRCM_MOD_MAILBOX10,
     PMHAL_PRCM_MOD_MAILBOX10_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX10_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
    {PMHAL_PRCM_MOD_MAILBOX11,
     PMHAL_PRCM_MOD_MAILBOX11_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX11_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
    {PMHAL_PRCM_MOD_MAILBOX12,
     PMHAL_PRCM_MOD_MAILBOX12_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX12_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
    {PMHAL_PRCM_MOD_MAILBOX13,
     PMHAL_PRCM_MOD_MAILBOX13_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX13_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    {PMHAL_PRCM_MOD_MAILBOX2,
     PMHAL_PRCM_MOD_MAILBOX2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
    {PMHAL_PRCM_MOD_MAILBOX3,
     PMHAL_PRCM_MOD_MAILBOX3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
    {PMHAL_PRCM_MOD_MAILBOX4,
     PMHAL_PRCM_MOD_MAILBOX4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
    {PMHAL_PRCM_MOD_MAILBOX5,
     PMHAL_PRCM_MOD_MAILBOX5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
    {PMHAL_PRCM_MOD_MAILBOX6,
     PMHAL_PRCM_MOD_MAILBOX6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
    {PMHAL_PRCM_MOD_MAILBOX7,
     PMHAL_PRCM_MOD_MAILBOX7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
    {PMHAL_PRCM_MOD_MAILBOX8,
     PMHAL_PRCM_MOD_MAILBOX8_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX8_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
    {PMHAL_PRCM_MOD_MAILBOX9,
     PMHAL_PRCM_MOD_MAILBOX9_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX9_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    {PMHAL_PRCM_MOD_I2C1,
     PMHAL_PRCM_MOD_I2C1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    {PMHAL_PRCM_MOD_I2C2,
     PMHAL_PRCM_MOD_I2C2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
    {PMHAL_PRCM_MOD_I2C3,
     PMHAL_PRCM_MOD_I2C3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
    {PMHAL_PRCM_MOD_I2C4,
     PMHAL_PRCM_MOD_I2C4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    {PMHAL_PRCM_MOD_L4_PER1,
     PMHAL_PRCM_MOD_L4_PER1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
    {PMHAL_PRCM_MOD_TIMER10,
     PMHAL_PRCM_MOD_TIMER10_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER10_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
    {PMHAL_PRCM_MOD_TIMER11,
     PMHAL_PRCM_MOD_TIMER11_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER11_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    {PMHAL_PRCM_MOD_TIMER2,
     PMHAL_PRCM_MOD_TIMER2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    {PMHAL_PRCM_MOD_TIMER3,
     PMHAL_PRCM_MOD_TIMER3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    {PMHAL_PRCM_MOD_TIMER4,
     PMHAL_PRCM_MOD_TIMER4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
    {PMHAL_PRCM_MOD_TIMER9,
     PMHAL_PRCM_MOD_TIMER9_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER9_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    {PMHAL_PRCM_MOD_ELM,
     PMHAL_PRCM_MOD_ELM_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ELM_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
    {PMHAL_PRCM_MOD_HDQ1W,
     PMHAL_PRCM_MOD_HDQ1W_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_HDQ1W_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    {PMHAL_PRCM_MOD_MCSPI1,
     PMHAL_PRCM_MOD_MCSPI1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    {PMHAL_PRCM_MOD_MCSPI2,
     PMHAL_PRCM_MOD_MCSPI2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    {PMHAL_PRCM_MOD_MCSPI3,
     PMHAL_PRCM_MOD_MCSPI3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    {PMHAL_PRCM_MOD_MCSPI4,
     PMHAL_PRCM_MOD_MCSPI4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    {PMHAL_PRCM_MOD_UART1,
     PMHAL_PRCM_MOD_UART1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    {PMHAL_PRCM_MOD_UART2,
     PMHAL_PRCM_MOD_UART2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    {PMHAL_PRCM_MOD_UART3,
     PMHAL_PRCM_MOD_UART3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
    {PMHAL_PRCM_MOD_UART4,
     PMHAL_PRCM_MOD_UART4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
    {PMHAL_PRCM_MOD_UART5,
     PMHAL_PRCM_MOD_UART5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    {PMHAL_PRCM_MOD_GPIO2,
     PMHAL_PRCM_MOD_GPIO2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    {PMHAL_PRCM_MOD_GPIO3,
     PMHAL_PRCM_MOD_GPIO3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    {PMHAL_PRCM_MOD_GPIO4,
     PMHAL_PRCM_MOD_GPIO4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
    {PMHAL_PRCM_MOD_GPIO5,
     PMHAL_PRCM_MOD_GPIO5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
    {PMHAL_PRCM_MOD_GPIO6,
     PMHAL_PRCM_MOD_GPIO6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
    {PMHAL_PRCM_MOD_GPIO7,
     PMHAL_PRCM_MOD_GPIO7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
    {PMHAL_PRCM_MOD_GPIO8,
     PMHAL_PRCM_MOD_GPIO8_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO8_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
    {PMHAL_PRCM_MOD_MMC3,
     PMHAL_PRCM_MOD_MMC3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    {PMHAL_PRCM_MOD_MMC4,
     PMHAL_PRCM_MOD_MMC4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MMC4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    {PMHAL_PRCM_MOD_DCAN2,
     PMHAL_PRCM_MOD_DCAN2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    {PMHAL_PRCM_MOD_L4_PER2,
     PMHAL_PRCM_MOD_L4_PER2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
    {PMHAL_PRCM_MOD_UART7,
     PMHAL_PRCM_MOD_UART7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
    {PMHAL_PRCM_MOD_UART8,
     PMHAL_PRCM_MOD_UART8_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART8_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
    {PMHAL_PRCM_MOD_UART9,
     PMHAL_PRCM_MOD_UART9_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART9_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    {PMHAL_PRCM_MOD_PRUSS1,
     PMHAL_PRCM_MOD_PRUSS1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PRUSS1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    {PMHAL_PRCM_MOD_PRUSS2,
     PMHAL_PRCM_MOD_PRUSS2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PRUSS2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
    #endif
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    {PMHAL_PRCM_MOD_MCASP2,
     PMHAL_PRCM_MOD_MCASP2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    {PMHAL_PRCM_MOD_MCASP3,
     PMHAL_PRCM_MOD_MCASP3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
    {PMHAL_PRCM_MOD_MCASP4,
     PMHAL_PRCM_MOD_MCASP4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
    {PMHAL_PRCM_MOD_MCASP5,
     PMHAL_PRCM_MOD_MCASP5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
    {PMHAL_PRCM_MOD_MCASP6,
     PMHAL_PRCM_MOD_MCASP6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
    {PMHAL_PRCM_MOD_MCASP7,
     PMHAL_PRCM_MOD_MCASP7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
    {PMHAL_PRCM_MOD_MCASP8,
     PMHAL_PRCM_MOD_MCASP8_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP8_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    {PMHAL_PRCM_MOD_PWMSS1,
     PMHAL_PRCM_MOD_PWMSS1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
    {PMHAL_PRCM_MOD_PWMSS2,
     PMHAL_PRCM_MOD_PWMSS2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
    {PMHAL_PRCM_MOD_PWMSS3,
     PMHAL_PRCM_MOD_PWMSS3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    {PMHAL_PRCM_MOD_QSPI,
     PMHAL_PRCM_MOD_QSPI_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_QSPI_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    {PMHAL_PRCM_MOD_L4_PER3,
     PMHAL_PRCM_MOD_L4_PER3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
    {PMHAL_PRCM_MOD_TIMER13,
     PMHAL_PRCM_MOD_TIMER13_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER13_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
    {PMHAL_PRCM_MOD_TIMER14,
     PMHAL_PRCM_MOD_TIMER14_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER14_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
    {PMHAL_PRCM_MOD_TIMER15,
     PMHAL_PRCM_MOD_TIMER15_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER15_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
    {PMHAL_PRCM_MOD_TIMER16,
     PMHAL_PRCM_MOD_TIMER16_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER16_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
    {PMHAL_PRCM_MOD_DES3DES,
     PMHAL_PRCM_MOD_DES3DES_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DES3DES_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
    {PMHAL_PRCM_MOD_DMA_CRYPTO,
     PMHAL_PRCM_MOD_DMA_CRYPTO_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DMA_CRYPTO_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
    {PMHAL_PRCM_MOD_FPKA,
     PMHAL_PRCM_MOD_FPKA_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_FPKA_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
    {PMHAL_PRCM_MOD_RNG,
     PMHAL_PRCM_MOD_RNG_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RNG_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    {PMHAL_PRCM_MOD_PCIESS1,
     PMHAL_PRCM_MOD_PCIESS1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PCIESS1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    {PMHAL_PRCM_MOD_PCIESS2,
     PMHAL_PRCM_MOD_PCIESS2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PCIESS2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
    {PMHAL_PRCM_MOD_RTCSS,
     PMHAL_PRCM_MOD_RTCSS_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTCSS_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
    #if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
    {PMHAL_PRCM_MOD_LVDSRX,
     PMHAL_PRCM_MOD_LVDSRX_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_LVDSRX_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
    #endif
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    {PMHAL_PRCM_MOD_ADC,
     PMHAL_PRCM_MOD_ADC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ADC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    {PMHAL_PRCM_MOD_COUNTER_32K,
     PMHAL_PRCM_MOD_COUNTER_32K_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_COUNTER_32K_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    {PMHAL_PRCM_MOD_DCAN1,
     PMHAL_PRCM_MOD_DCAN1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    {PMHAL_PRCM_MOD_GPIO1,
     PMHAL_PRCM_MOD_GPIO1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
    {PMHAL_PRCM_MOD_KBD,
     PMHAL_PRCM_MOD_KBD_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_KBD_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    {PMHAL_PRCM_MOD_TIMER1,
     PMHAL_PRCM_MOD_TIMER1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
    {PMHAL_PRCM_MOD_TIMER12,
     PMHAL_PRCM_MOD_TIMER12_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER12_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
    {PMHAL_PRCM_MOD_UART10,
     PMHAL_PRCM_MOD_UART10_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_UART10_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
    {PMHAL_PRCM_MOD_WD_TIMER1,
     PMHAL_PRCM_MOD_WD_TIMER1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_WD_TIMER1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
    {PMHAL_PRCM_MOD_WD_TIMER2,
     PMHAL_PRCM_MOD_WD_TIMER2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_WD_TIMER2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */
    #if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C6
    {PMHAL_PRCM_MOD_I2C6,
     PMHAL_PRCM_MOD_I2C6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_I2C6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C6 */
    #endif
};

pmhalClockTree prcmGraph = {
    VSIZE_TYPE(prcmNodes, pmhalClockTreeNode),
    prcmNodes,
    VSIZE_TYPE(prcmEdges, pmhalClockTreeOutputEdge), /* edges max */
    prcmEdges                                        /* edges[] */
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif
