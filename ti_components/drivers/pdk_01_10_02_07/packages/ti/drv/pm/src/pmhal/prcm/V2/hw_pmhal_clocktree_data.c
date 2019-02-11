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
#include "stdio.h"
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
 *         PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
 */
pmhalClockTreeProp       PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3_prop =
{
    PMHAL_ROOT_CLK,
    NULL
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_32K_CLK_prop =
{
    PMHAL_DIV,
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
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_IPU1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
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
 *         PMHAL_PRCM_MUX_EVE_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_EVE_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_EVE_CLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_DSP_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_DSP_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_DSP_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
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
 *         PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_PER_DPLL_HS_CLK - PMHAL_PRCM_DIV_MIN]
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
 *         PMHAL_PRCM_MUX_ADC_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_ADC_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ADC_MUX - PMHAL_PRCM_MUX_MIN]
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
 *         PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MMC4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RMII_50M_CLK_MUX -
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
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX -
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
 *         PMHAL_PRCM_MUX_RTI1_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RTI1_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI1_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RTI2_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RTI2_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI2_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RTI3_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RTI3_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI3_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RTI4_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RTI4_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI4_CLK_MUX -
                           PMHAL_PRCM_MUX_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MUX_RTI5_CLK_MUX
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_RTI5_CLK_MUX_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI5_CLK_MUX -
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
 *         PMHAL_PRCM_MUX_DPLL_CORE_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_MUX_DPLL_CORE_CLK_prop =
{
    PMHAL_MUX,
    &pmhalMultiplexerElems[PMHAL_PRCM_MUX_DPLL_CORE_CLK -
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
 *         PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_FUNC_24M_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_24M_CLK - PMHAL_PRCM_DIV_MIN]
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
 *         PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK - PMHAL_PRCM_DIV_MIN]
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
 *         PMHAL_PRCM_DIV_RGMII_5M_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_RGMII_5M_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_RGMII_5M_CLK - PMHAL_PRCM_DIV_MIN]
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
 *         PMHAL_PRCM_DIV_TESOC_EXT_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_TESOC_EXT_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_TESOC_EXT_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_VID_PIX_CLK
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_VID_PIX_CLK_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_VID_PIX_CLK - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SYS_CLK1
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SYS_CLK1_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SYS_CLK1 - PMHAL_PRCM_DIV_MIN]
};
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DIV_SYS_CLK2
 */
pmhalClockTreeProp       PMHAL_PRCM_DIV_SYS_CLK2_prop =
{
    PMHAL_DIV,
    &pmhalDividerElems[PMHAL_PRCM_DIV_SYS_CLK2 - PMHAL_PRCM_DIV_MIN]
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
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_EVE_VID_DSP_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN]
};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_DSP_GMAC_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN]
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
 *  \brief Structure defining property structures for PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeProp       PMHAL_PRCM_DPLL_PER_prop =
{
    PMHAL_DPLL,
    &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN]
};
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CRC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CRC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CRC - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_TESOC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_TESOC_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_TESOC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC6
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC6_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC6 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC7
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC7_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC7 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC5 -
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ESM
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ESM_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ESM - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCASP8_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ADC -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_DCC4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_DCC4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_DCC4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ISS
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ISS_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ISS - (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_RTI1
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTI1_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTI1 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY2
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTI2_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTI2 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_SPARE_SAFETY3
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTI3_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTI3 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_RTI4
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTI4_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTI4 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
/**
 *  \brief Structure defining property structures for
 *         PMHAL_PRCM_MOD_RTI5
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_RTI5_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_RTI5 -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_CAMERARX
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_CAMERARX_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_CAMERARX -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_MCAN
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_MCAN_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_MCAN -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_MOD_ATL
 */
pmhalClockTreeProp       PMHAL_PRCM_MOD_ATL_prop =
{
    PMHAL_MOD,
    &pmhalModuleElems[PMHAL_PRCM_MOD_ATL -
                      (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)]
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
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

/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_DDR
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_ADC_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_ADC_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_EVE_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC,
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_VIP1_GCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DIV_L3_ICLK
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
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_48M_FCLK,
    PMHAL_PRCM_DPLL_PER
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_DIV_VIDEO2_CLK2,
    PMHAL_PRCM_DIV_VIDEO1_CLK2,
    PMHAL_PRCM_DIV_HDMI_CLK2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
    PMHAL_PRCM_DIV_FUNC_24M_CLK,
    PMHAL_PRCM_DIV_ABE_24M_FCLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_ABE_SYS_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_DIV_MLB_CLK,
    PMHAL_PRCM_DIV_MLBP_CLK,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
    PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
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
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
    PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
    PMHAL_PRCM_DIV_VIDEO2_CLK,
    PMHAL_PRCM_DIV_VIDEO1_CLK,
    PMHAL_PRCM_DIV_HDMI_CLK,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
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
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_EVE_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_EVE_CLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_EVE_VID_DSP,
    PMHAL_PRCM_MUX_EVE_GCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_DSP_GFCLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_DSP_GFCLK_MUX_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_EVE_VID_DSP,
    PMHAL_PRCM_DPLL_DSP_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RTI1_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RTI1_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_SYS_CLK1,
    PMHAL_PRCM_DIV_SYS_CLK2,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RTI2_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RTI2_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_SYS_CLK1,
    PMHAL_PRCM_DIV_SYS_CLK2,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RTI3_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RTI3_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_SYS_CLK1,
    PMHAL_PRCM_DIV_SYS_CLK2,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RTI4_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RTI4_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_SYS_CLK1,
    PMHAL_PRCM_DIV_SYS_CLK2,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_RTI5_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_RTI5_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_SYS_CLK1,
    PMHAL_PRCM_DIV_SYS_CLK2,
    PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes[] =
{
    PMHAL_PRCM_DIV_FUNC_32K_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MUX_DPLL_CORE_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MUX_DPLL_CORE_CLK_inNodes[] =
{
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2
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
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_24M_FCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_24M_FCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_ABE_LP_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_ABE_LP_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_PER
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
    PMHAL_PRCM_MUX_DSP_GFCLK_MUX
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
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_EVE_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_EVE_DCLK_inNodes[] = {
    PMHAL_PRCM_DPLL_EVE_VID_DSP
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
    PMHAL_PRCM_DPLL_DSP_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GPU_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GPU_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IVA_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IVA_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_L3INIT_480M_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_L3INIT_480M_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MPU_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MPU_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PCIE2_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PCIE2_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PCIE_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PCIE_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_ABE_X1_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SATA_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SATA_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
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
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_USB_OTG_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_USB_OTG_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_DCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_DCLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
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
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
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
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MMC4_GFCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes[] = {
    PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_RGMII_5M_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_RGMII_5M_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MLBP_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MLBP_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_MLB_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_MLB_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_HDMI_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_HDMI_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO1_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO1_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VIDEO2_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VIDEO2_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
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
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_TESOC_EXT_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_TESOC_EXT_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_VID_PIX_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_VID_PIX_CLK_inNodes[] = {
    PMHAL_PRCM_DPLL_EVE_VID_DSP
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SYS_CLK1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SYS_CLK1_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_SYS_CLK2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_SYS_CLK2_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_IPU1_GCLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_IPU1_GCLK_inNodes[] = {
    PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_CORE_inNodes[] = {
    PMHAL_PRCM_MUX_DPLL_CORE_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_DDR_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_EVE_VID_DSP_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_DSP_GMAC_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
};
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeNodeId     PMHAL_PRCM_DPLL_PER_inNodes[] = {
    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
    PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
};
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CRC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CRC_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes[] = {
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSP1_inNodes[] = {
    PMHAL_PRCM_MUX_DSP_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSP2_inNodes[] = {
    PMHAL_PRCM_MUX_DSP_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DSS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DSS_inNodes[] = {
    PMHAL_PRCM_DPLL_PER,
    PMHAL_PRCM_DIV_VID_PIX_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DLL
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DLL_inNodes[] = {
    PMHAL_PRCM_DPLL_DDR
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EMIF1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EMIF1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DPLL_DDR
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_EVE1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_EVE1_inNodes[] = {
    PMHAL_PRCM_MUX_EVE_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CPGMAC_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC,
    PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
    PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK,
    PMHAL_PRCM_DIV_RGMII_5M_CLK,
    PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
    PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IPU1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IPU1_inNodes[] = {
    PMHAL_PRCM_DIV_IPU1_GCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_IEEE1500_2_OCP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_OCMC_RAM1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_OCMC_RAM1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TESOC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TESOC_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_TESOC_EXT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_SPINLOCK
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_SPINLOCK_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MAILBOX2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MAILBOX2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_PER1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_PER1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC6
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC6_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC7
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC7_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC5_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ELM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ELM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ESM
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ESM_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ADC_inNodes[] = {
    PMHAL_PRCM_MUX_ADC_MUX,
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_PWMSS1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_PWMSS1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC1_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DCC4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DCC4_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_VIP1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_VIP1_inNodes[] = {
    PMHAL_PRCM_MUX_VIP1_GCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ISS
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ISS_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_DEBUG_LOGIC
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes[] = {
    PMHAL_PRCM_DPLL_CORE,
    PMHAL_PRCM_DPLL_PER
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_L4_WKUP
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_L4_WKUP_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTI1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTI1_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_RTI1_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTI2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTI2_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_RTI2_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTI3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTI3_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_RTI3_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTI4
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTI4_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_RTI4_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_RTI5
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_RTI5_inNodes[] = {
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
    PMHAL_PRCM_MUX_RTI5_CLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_TIMER1
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_TIMER1_inNodes[] = {
    PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
    PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_CAMERARX
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_CAMERARX_inNodes[] = {
    PMHAL_PRCM_DIV_FUNC_96M_FCLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCAN
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCAN_inNodes[] = {
    PMHAL_PRCM_DPLL_DSP_GMAC,
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_ATL
 *         TODO: ATL can take in 3 clocks. Need to find
 *               what else is connected in SR2.0.
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_ATL_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP2
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP2_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
    PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
    PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/**
 *  \brief Structure defining InNodes of PMHAL_PRCM_MOD_MCASP3
 */
pmhalClockTreeNodeId     PMHAL_PRCM_MOD_MCASP3_inNodes[] = {
    PMHAL_PRCM_DIV_L3_ICLK,
    PMHAL_PRCM_DIV_L4_ROOT_CLK,
    PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX,
    PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
    PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */

const pmhalClockTreeNode prcmNodes[] =
{
    {&PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2_prop,
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
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3_prop,
     NULL,
     0},
    {&PMHAL_PRCM_ROOT_CLK_SECURE_32K_CLK_SRC_prop,
     NULL,
     0},
    {&PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_ADC_MUX_prop,
     PMHAL_PRCM_MUX_ADC_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_ADC_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_EVE_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_EVE_GCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_VIP1_GCLK_MUX_prop,
     PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_VIP1_GCLK_MUX_inNodes,
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
    {&PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_prop,
     PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_prop,
     PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_prop,
     PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_inNodes,
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
    {&PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_prop,
     PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_prop,
     PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_EVE_CLK_MUX_prop,
     PMHAL_PRCM_MUX_EVE_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_EVE_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_DSP_GFCLK_MUX_prop,
     PMHAL_PRCM_MUX_DSP_GFCLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_DSP_GFCLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RTI1_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RTI1_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RTI1_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RTI2_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RTI2_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RTI2_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RTI3_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RTI3_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RTI3_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RTI4_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RTI4_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RTI4_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_RTI5_CLK_MUX_prop,
     PMHAL_PRCM_MUX_RTI5_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_RTI5_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_prop,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_MUX_DPLL_CORE_CLK_prop,
     PMHAL_PRCM_MUX_DPLL_CORE_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MUX_DPLL_CORE_CLK_inNodes,
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
    {&PMHAL_PRCM_DIV_FUNC_24M_CLK_prop,
     PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_24M_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L3_ICLK_prop,
     PMHAL_PRCM_DIV_L3_ICLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L3_ICLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_L4_ROOT_CLK_prop,
     PMHAL_PRCM_DIV_L4_ROOT_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_L4_ROOT_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_prop,
     PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_inNodes,
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
    {&PMHAL_PRCM_DIV_FUNC_48M_FCLK_prop,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_48M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_96M_FCLK_prop,
     PMHAL_PRCM_DIV_FUNC_96M_FCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_96M_FCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_prop,
     PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_MMC4_GFCLK_prop,
     PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_MMC4_GFCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_RGMII_5M_CLK_prop,
     PMHAL_PRCM_DIV_RGMII_5M_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_RGMII_5M_CLK_inNodes,
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
     VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_CLK_inNodes,
                pmhalClockTreeNodeId)},
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
    {&PMHAL_PRCM_DIV_TESOC_EXT_CLK_prop,
     PMHAL_PRCM_DIV_TESOC_EXT_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_TESOC_EXT_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_VID_PIX_CLK_prop,
     PMHAL_PRCM_DIV_VID_PIX_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_VID_PIX_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SYS_CLK1_prop,
     PMHAL_PRCM_DIV_SYS_CLK1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK1_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_SYS_CLK2_prop,
     PMHAL_PRCM_DIV_SYS_CLK2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK2_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_IPU1_GCLK_prop,
     PMHAL_PRCM_DIV_IPU1_GCLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_IPU1_GCLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DIV_FUNC_32K_CLK_prop,
     PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_32K_CLK_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_CORE_prop,
     PMHAL_PRCM_DPLL_CORE_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_CORE_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_DDR_prop,
     PMHAL_PRCM_DPLL_DDR_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DDR_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_DSP_GMAC_prop,
     PMHAL_PRCM_DPLL_DSP_GMAC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DSP_GMAC_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_PER_prop,
     PMHAL_PRCM_DPLL_PER_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PER_inNodes,
                pmhalClockTreeNodeId)},
    {&PMHAL_PRCM_DPLL_EVE_VID_DSP_prop,
     PMHAL_PRCM_DPLL_EVE_VID_DSP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_EVE_VID_DSP_inNodes,
                pmhalClockTreeNodeId)},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
    {&PMHAL_PRCM_MOD_CRC_prop,
     PMHAL_PRCM_MOD_CRC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CRC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    {&PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_prop,
     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    {&PMHAL_PRCM_MOD_DSP1_prop,
     PMHAL_PRCM_MOD_DSP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    {&PMHAL_PRCM_MOD_DSP2_prop,
     PMHAL_PRCM_MOD_DSP2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSP2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {&PMHAL_PRCM_MOD_DSS_prop,
     PMHAL_PRCM_MOD_DSS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    {&PMHAL_PRCM_MOD_DLL_prop,
     PMHAL_PRCM_MOD_DLL_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DLL_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {&PMHAL_PRCM_MOD_EMIF1_prop,
     PMHAL_PRCM_MOD_EMIF1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    {&PMHAL_PRCM_MOD_EVE1_prop,
     PMHAL_PRCM_MOD_EVE1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EVE1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {&PMHAL_PRCM_MOD_CPGMAC_prop,
     PMHAL_PRCM_MOD_CPGMAC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CPGMAC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    {&PMHAL_PRCM_MOD_IPU1_prop,
     PMHAL_PRCM_MOD_IPU1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IPU1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    {&PMHAL_PRCM_MOD_IEEE1500_2_OCP_prop,
     PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IEEE1500_2_OCP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    {&PMHAL_PRCM_MOD_OCMC_RAM1_prop,
     PMHAL_PRCM_MOD_OCMC_RAM1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    {&PMHAL_PRCM_MOD_TESOC_prop,
     PMHAL_PRCM_MOD_TESOC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TESOC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    {&PMHAL_PRCM_MOD_SPINLOCK_prop,
     PMHAL_PRCM_MOD_SPINLOCK_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPINLOCK_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    {&PMHAL_PRCM_MOD_MAILBOX1_prop,
     PMHAL_PRCM_MOD_MAILBOX1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    {&PMHAL_PRCM_MOD_MAILBOX2_prop,
     PMHAL_PRCM_MOD_MAILBOX2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    {&PMHAL_PRCM_MOD_L4_PER1_prop,
     PMHAL_PRCM_MOD_L4_PER1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    {&PMHAL_PRCM_MOD_DCC6_prop,
     PMHAL_PRCM_MOD_DCC6_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC6_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    {&PMHAL_PRCM_MOD_DCC7_prop,
     PMHAL_PRCM_MOD_DCC7_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC7_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    {&PMHAL_PRCM_MOD_DCC5_prop,
     PMHAL_PRCM_MOD_DCC5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    {&PMHAL_PRCM_MOD_ELM_prop,
     PMHAL_PRCM_MOD_ELM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ELM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    {&PMHAL_PRCM_MOD_ESM_prop,
     PMHAL_PRCM_MOD_ESM_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ESM_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    {&PMHAL_PRCM_MOD_ADC_prop,
     PMHAL_PRCM_MOD_ADC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ADC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    {&PMHAL_PRCM_MOD_PWMSS1_prop,
     PMHAL_PRCM_MOD_PWMSS1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    {&PMHAL_PRCM_MOD_DCC1_prop,
     PMHAL_PRCM_MOD_DCC1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    {&PMHAL_PRCM_MOD_DCC2_prop,
     PMHAL_PRCM_MOD_DCC2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    {&PMHAL_PRCM_MOD_DCC3_prop,
     PMHAL_PRCM_MOD_DCC3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    {&PMHAL_PRCM_MOD_DCC4_prop,
     PMHAL_PRCM_MOD_DCC4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    {&PMHAL_PRCM_MOD_VIP1_prop,
     PMHAL_PRCM_MOD_VIP1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_VIP1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    {&PMHAL_PRCM_MOD_ISS_prop,
     PMHAL_PRCM_MOD_ISS_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ISS_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {&PMHAL_PRCM_MOD_DEBUG_LOGIC_prop,
     PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DEBUG_LOGIC_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    {&PMHAL_PRCM_MOD_L4_WKUP_prop,
     PMHAL_PRCM_MOD_L4_WKUP_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_WKUP_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    {&PMHAL_PRCM_MOD_RTI1_prop,
     PMHAL_PRCM_MOD_RTI1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    {&PMHAL_PRCM_MOD_RTI2_prop,
     PMHAL_PRCM_MOD_RTI2_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI2_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    {&PMHAL_PRCM_MOD_RTI3_prop,
     PMHAL_PRCM_MOD_RTI3_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI3_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    {&PMHAL_PRCM_MOD_RTI4_prop,
     PMHAL_PRCM_MOD_RTI4_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI4_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    {&PMHAL_PRCM_MOD_RTI5_prop,
     PMHAL_PRCM_MOD_RTI5_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI5_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    {&PMHAL_PRCM_MOD_TIMER1_prop,
     PMHAL_PRCM_MOD_TIMER1_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER1_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
    {&PMHAL_PRCM_MOD_CAMERARX_prop,
     PMHAL_PRCM_MOD_CAMERARX_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CAMERARX_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    {&PMHAL_PRCM_MOD_MCAN_prop,
     PMHAL_PRCM_MOD_MCAN_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCAN_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    {&PMHAL_PRCM_MOD_ATL_prop,
     PMHAL_PRCM_MOD_ATL_inNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ATL_inNodes,
                pmhalClockTreeNodeId)},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
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
                pmhalClockTreeNodeId)}
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp =
{PMHAL_PRCM_DIV_L4_ROOT_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_L4_ROOT_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DPLL_PER_edgeProp =
{PMHAL_PRCM_DPLL_PER,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_L3_ICLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_L3_ICLK_edgeProp =
{PMHAL_PRCM_DIV_L3_ICLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_L3_ICLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_VID_PIX_CLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_VID_PIX_CLK_edgeProp =
{PMHAL_PRCM_DIV_VID_PIX_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_VID_PIX_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DPLL_DDR_edgeProp =
{PMHAL_PRCM_DPLL_DDR,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_edgeProp =
{PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DPLL_DSP_GMAC_edgeProp =
{PMHAL_PRCM_DPLL_DSP_GMAC,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RMII_50M_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RMII_50M_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_RGMII_5M_CLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_RGMII_5M_CLK_edgeProp =
{PMHAL_PRCM_DIV_RGMII_5M_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_RGMII_5M_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX -
                        PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_TESOC_EXT_CLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_TESOC_EXT_CLK_edgeProp =
{PMHAL_PRCM_DIV_TESOC_EXT_CLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_TESOC_EXT_CLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp =
{PMHAL_PRCM_DIV_FUNC_96M_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_96M_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp =
{PMHAL_PRCM_DIV_FUNC_48M_FCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_FUNC_48M_FCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART2_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_UART3_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_MMC4_GFCLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_MMC4_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_MMC4_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_MMC4_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 NULL,
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_ADC_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_ADC_MUX_edgeProp =
{PMHAL_PRCM_MUX_ADC_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_ADC_MUX - PMHAL_PRCM_ROOT_CLK_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DIV_QSPI_GFCLK
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DIV_QSPI_GFCLK_edgeProp =
{PMHAL_PRCM_DIV_QSPI_GFCLK,
 &pmhalDividerElems[PMHAL_PRCM_DIV_QSPI_GFCLK - PMHAL_PRCM_DIV_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_DPLL_CORE_edgeProp =
{PMHAL_PRCM_DPLL_CORE,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RTI1_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RTI1_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RTI1_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI1_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RTI2_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RTI2_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RTI2_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI2_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RTI3_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RTI3_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RTI3_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI3_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RTI4_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RTI4_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RTI4_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI4_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_RTI5_CLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_RTI5_CLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_RTI5_CLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_RTI5_CLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining edge property structure for
 *         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
pmhalClockTreeEdgeProp   PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_edgeProp =
{PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
 &pmhalMultiplexerElems[PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX - PMHAL_PRCM_MUX_MIN],
 0U};

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPHIF
 *         connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};

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
 *         PMHAL_PRCM_MUX_DSP_GFCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_EVE_GCLK_MUX connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
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
 *         PMHAL_PRCM_DIV_TESOC_EXT_CLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_TESOC_EXT_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_ISS connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_ISS_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H23,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_DEBUG_LOGIC connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_DEBUG_LOGIC_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H21,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_DEBUG_STMEXPT_CLK};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_DEBUG_LOGIC connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_DEBUG_LOGIC_ATB_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H11,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     PMHAL_PRCM_CLK_DEBUG_ATB_CLK};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_EMU_DCLK connected to PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_EMU_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H21,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp =
{PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_CORE - PMHAL_PRCM_DPLL_MIN],
 0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};
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
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_CLK connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_24M_FCLK connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_24M_FCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_ABE_LP_CLK connected to PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_LP_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DDR - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_EVE_GCLK_MUX connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H13,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GMAC_250M_DCLK connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_GMAC_250M_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_RMII_50M_CLK_MUX connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK connected to
 *         PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DIV_RGMII_5M_CLK connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_RGMII_5M_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H11,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_DSP_GMAC connected to PMHAL_PRCM_DPLL_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MOD_CPGMAC_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H12,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_DSP_GMAC connected to PMHAL_PRCM_DPLL_MCAN
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MOD_MCAN_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_DSP_GMAC - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPHIF
 *         connected to PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp
    =
    {PMHAL_PRCM_NODE_UNDEF,
     NULL,
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_DSP_GFCLK_MUX connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M3,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MUX_EVE_CLK_MUX connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_MUX_EVE_CLK_MUX_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DIV_EVE_DCLK
 *         connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DIV_EVE_DCLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2X2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};
/**
 *  \brief Structure defining property structures for PMHAL_PRCM_DIV_VID_PIX_CLK
 *         connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DIV_VID_PIX_CLK_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_M2,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for PMHAL_PRCM_DPLL_INP_CLKINP
 *         connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
    =
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPULOW
 *         connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp
    =
    {PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_EVE_VID_DSP - PMHAL_PRCM_DPLL_MIN],
     0};

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINPHIF
 *         connected to PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp
    =
    {PMHAL_PRCM_NODE_UNDEF,
     NULL,
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
pmhalClockTreeEdgeProp PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DSS_edgeProp =
{PMHAL_PRCM_DPLL_POST_DIV_H12,
 &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
 0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_MOD_DEBUG_LOGIC connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DEBUG_LOGIC_edgeProp
    =
    {PMHAL_PRCM_DPLL_POST_DIV_H14,
     &pmhalDpllElems[PMHAL_PRCM_DPLL_PER - PMHAL_PRCM_DPLL_MIN],
     0};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */

/**
 *  \brief Structure defining property structure for
 *         PMHAL_PRCM_DPLL_INP_CLKINP connected to PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeEdgeProp
    PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp
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
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_CORE
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_CORE_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_L3_ICLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_MUX_VIP1_GCLK_MUX,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MUX_VIP1_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_edgeProp},
    {PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_TESOC_EXT_CLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_TESOC_EXT_CLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    {PMHAL_PRCM_MOD_ISS,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_ISS_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_DEBUG_LOGIC_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_MOD_DEBUG_LOGIC_ATB_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
    {PMHAL_PRCM_DIV_EMU_DCLK,
     &PMHAL_PRCM_DPLL_CORE_PMHAL_PRCM_DIV_EMU_DCLK_edgeProp}
};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_DDR
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_DDR_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_edgeProp},
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
    {PMHAL_PRCM_DIV_ABE_CLK,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_CLK_edgeProp},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_24M_FCLK_edgeProp},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     &PMHAL_PRCM_DPLL_DDR_PMHAL_PRCM_DIV_ABE_LP_CLK_edgeProp},
};

/**
 *  \brief Structure defining to-nodes structures for PMHAL_PRCM_DPLL_DSP_GMAC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_DSP_GMAC_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_EVE_GCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_RMII_50M_CLK_MUX,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_GMAC_250M_DCLK,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_GMAC_250M_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_edgeProp},
    {PMHAL_PRCM_DIV_RGMII_5M_CLK,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_DIV_RGMII_5M_CLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {PMHAL_PRCM_MOD_CPGMAC,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MOD_CPGMAC_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    {PMHAL_PRCM_MOD_MCAN,
     &PMHAL_PRCM_DPLL_DSP_GMAC_PMHAL_PRCM_MOD_MCAN_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
};

/**
 *  \brief Structure defining to-nodes structures for
 *         PMHAL_PRCM_DPLL_EVE_VID_DSP
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_EVE_VID_DSP_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPHIF,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DPLL_INP_CLKINPHIF_edgeProp},
    {PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_MUX_DSP_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_EVE_CLK_MUX,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_MUX_EVE_CLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_EVE_DCLK,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DIV_EVE_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_VID_PIX_CLK,
     &PMHAL_PRCM_DPLL_EVE_VID_DSP_PMHAL_PRCM_DIV_VID_PIX_CLK_edgeProp},
};

/**
 *  \brief Structure defining to-nodes structures for
 *         PMHAL_PRCM_DPLL_PER
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_DPLL_PER_toNodes[] =
{
    {PMHAL_PRCM_DPLL_INP_CLKINP,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINP_edgeProp},
    {PMHAL_PRCM_DPLL_INP_CLKINPULOW,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DPLL_INP_CLKINPULOW_edgeProp},
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART1_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART2_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MUX_UART3_GFCLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_24M_CLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_48M_FCLK_edgeProp},
    {PMHAL_PRCM_DIV_FUNC_96M_FCLK,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_DIV_FUNC_96M_FCLK_edgeProp},
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {PMHAL_PRCM_MOD_DSS,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DSS_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,
     &PMHAL_PRCM_DPLL_PER_PMHAL_PRCM_MOD_DEBUG_LOGIC_edgeProp},
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
};

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

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DSS
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DSS_fromNodes[] = {
    {PMHAL_PRCM_CLK_DSS_GFCLK,
     &PMHAL_PRCM_DPLL_PER_edgeProp},
    {PMHAL_PRCM_CLK_VID_PIX_CLK,
     &PMHAL_PRCM_DIV_VID_PIX_CLK_edgeProp},
    {PMHAL_PRCM_CLK_DSS_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_DSS_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_CPGMAC_fromNodes[] = {
    {PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     &PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
     &PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_edgeProp},
    {PMHAL_PRCM_CLK_RGMII_5MHZ_CLK,
     &PMHAL_PRCM_DIV_RGMII_5M_CLK_edgeProp},
    {PMHAL_PRCM_CLK_RMII_50MHZ_CLK,
     &PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_GMII_250MHZ_CLK,
     &PMHAL_PRCM_DPLL_DSP_GMAC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_TESOC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_TESOC_fromNodes[] = {
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_TESOC_EXT_CLK,
     &PMHAL_PRCM_DIV_TESOC_EXT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC6
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC6_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC7
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC7_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC5_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ESM
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ESM_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ADC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ADC_fromNodes[] = {
    {PMHAL_PRCM_CLK_ADC_GFCLK,
     &PMHAL_PRCM_MUX_ADC_MUX_edgeProp},
    {PMHAL_PRCM_CLK_ADC_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC1_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC2_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC3_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DCC4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DCC4_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_DEBUG_LOGIC
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_DEBUG_LOGIC_fromNodes[] = {
    {PMHAL_PRCM_CLK_DEBUG_ATB_CLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp},
    {PMHAL_PRCM_CLK_DEBUG_TREXCPT_CLK,
     &PMHAL_PRCM_DPLL_PER_edgeProp},
    {PMHAL_PRCM_CLK_DEBUG_STMEXPT_CLK,
     &PMHAL_PRCM_DPLL_CORE_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTI1
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTI1_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTI1_CLK,
     &PMHAL_PRCM_MUX_RTI1_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTI2
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTI2_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTI2_CLK,
     &PMHAL_PRCM_MUX_RTI2_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTI3
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTI3_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTI3_CLK,
     &PMHAL_PRCM_MUX_RTI3_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTI4
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTI4_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTI4_CLK,
     &PMHAL_PRCM_MUX_RTI4_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_RTI5
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_RTI5_fromNodes[] = {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_edgeProp},
    {PMHAL_PRCM_CLK_RTI5_CLK,
     &PMHAL_PRCM_MUX_RTI5_CLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
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
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCAN
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCAN_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     &PMHAL_PRCM_DIV_L4_ROOT_CLK_edgeProp},
    {PMHAL_PRCM_CLK_MCAN_CLK,
     &PMHAL_PRCM_DPLL_DSP_GMAC_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_ATL.
 *         [TODO]: ATL can take in 3 clocks. Need to find
 *                 what else is connected in SR2.0.
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_ATL_fromNodes[] = {
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP2.
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP2_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     &PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_edgeProp},
    {PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/**
 *  \brief Structure defining FromNodes of PMHAL_PRCM_MOD_MCASP3.
 */
pmhalClockTreeInputEdge        PMHAL_PRCM_MOD_MCASP3_fromNodes[] = {
    {PMHAL_PRCM_CLK_MCASP3_AHCLKR,
     &PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_edgeProp},
    {PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     &PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_edgeProp},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     &PMHAL_PRCM_DIV_L3_ICLK_edgeProp},
    {PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     &PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_edgeProp}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */

const pmhalClockTreeOutputEdge prcmEdges[] =
{
    {PMHAL_PRCM_DPLL_CORE,
     PMHAL_PRCM_DPLL_CORE_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_CORE_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_DDR,
     PMHAL_PRCM_DPLL_DDR_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DDR_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_DSP_GMAC,
     PMHAL_PRCM_DPLL_DSP_GMAC_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_DSP_GMAC_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_PER,
     PMHAL_PRCM_DPLL_PER_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_PER_toNodes, pmhalClockTreeInputEdge)},
    {PMHAL_PRCM_DPLL_EVE_VID_DSP,
     PMHAL_PRCM_DPLL_EVE_VID_DSP_toNodes,
     VSIZE_TYPE(PMHAL_PRCM_DPLL_EVE_VID_DSP_toNodes, pmhalClockTreeInputEdge)},
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,
     PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {PMHAL_PRCM_MOD_DSS,
     PMHAL_PRCM_MOD_DSS_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DSS_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    {PMHAL_PRCM_MOD_EMIF1,
     PMHAL_PRCM_MOD_EMIF1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {PMHAL_PRCM_MOD_CPGMAC,
     PMHAL_PRCM_MOD_CPGMAC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_CPGMAC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,
     PMHAL_PRCM_MOD_IEEE1500_2_OCP_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_IEEE1500_2_OCP_fromNodes,
                pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    {PMHAL_PRCM_MOD_OCMC_RAM1,
     PMHAL_PRCM_MOD_OCMC_RAM1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    {PMHAL_PRCM_MOD_TESOC,
     PMHAL_PRCM_MOD_TESOC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TESOC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    {PMHAL_PRCM_MOD_L4_CFG,
     PMHAL_PRCM_MOD_L4_CFG_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_CFG_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    {PMHAL_PRCM_MOD_SPINLOCK,
     PMHAL_PRCM_MOD_SPINLOCK_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_SPINLOCK_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    {PMHAL_PRCM_MOD_MAILBOX1,
     PMHAL_PRCM_MOD_MAILBOX1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    {PMHAL_PRCM_MOD_MAILBOX2,
     PMHAL_PRCM_MOD_MAILBOX2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    {PMHAL_PRCM_MOD_L4_PER1,
     PMHAL_PRCM_MOD_L4_PER1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    {PMHAL_PRCM_MOD_DCC6,
     PMHAL_PRCM_MOD_DCC6_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC6_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    {PMHAL_PRCM_MOD_DCC7,
     PMHAL_PRCM_MOD_DCC7_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC7_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    {PMHAL_PRCM_MOD_DCC5,
     PMHAL_PRCM_MOD_DCC5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    {PMHAL_PRCM_MOD_ELM,
     PMHAL_PRCM_MOD_ELM_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ELM_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    {PMHAL_PRCM_MOD_ESM,
     PMHAL_PRCM_MOD_ESM_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ESM_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    {PMHAL_PRCM_MOD_ADC,
     PMHAL_PRCM_MOD_ADC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ADC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    {PMHAL_PRCM_MOD_PWMSS1,
     PMHAL_PRCM_MOD_PWMSS1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    {PMHAL_PRCM_MOD_DCC1,
     PMHAL_PRCM_MOD_DCC1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    {PMHAL_PRCM_MOD_DCC2,
     PMHAL_PRCM_MOD_DCC2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    {PMHAL_PRCM_MOD_DCC3,
     PMHAL_PRCM_MOD_DCC3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    {PMHAL_PRCM_MOD_DCC4,
     PMHAL_PRCM_MOD_DCC4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DCC4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,
     PMHAL_PRCM_MOD_DEBUG_LOGIC_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_DEBUG_LOGIC_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
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
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    {PMHAL_PRCM_MOD_RTI1,
     PMHAL_PRCM_MOD_RTI1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    {PMHAL_PRCM_MOD_RTI2,
     PMHAL_PRCM_MOD_RTI2_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI2_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    {PMHAL_PRCM_MOD_RTI3,
     PMHAL_PRCM_MOD_RTI3_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI3_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    {PMHAL_PRCM_MOD_RTI4,
     PMHAL_PRCM_MOD_RTI4_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI4_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    {PMHAL_PRCM_MOD_RTI5,
     PMHAL_PRCM_MOD_RTI5_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_RTI5_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    {PMHAL_PRCM_MOD_TIMER1,
     PMHAL_PRCM_MOD_TIMER1_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER1_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    {PMHAL_PRCM_MOD_MCAN,
     PMHAL_PRCM_MOD_MCAN_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_MCAN_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
    #ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    {PMHAL_PRCM_MOD_ATL,
     PMHAL_PRCM_MOD_ATL_fromNodes,
     VSIZE_TYPE(PMHAL_PRCM_MOD_ATL_fromNodes, pmhalClockTreeInputEdge)},
    #endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
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
};

pmhalClockTree prcmGraph = {
    VSIZE_TYPE(prcmNodes, pmhalClockTreeNode),
    prcmNodes,
    VSIZE_TYPE(prcmEdges, pmhalClockTreeOutputEdge), /* edges max */
    prcmEdges,                                       /* edges[] */
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

