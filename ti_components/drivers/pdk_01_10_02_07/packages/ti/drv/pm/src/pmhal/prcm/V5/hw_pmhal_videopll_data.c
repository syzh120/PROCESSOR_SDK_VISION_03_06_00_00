/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file      hw_pmhal_videopll_data.C
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare Video PLL (internal) implementation.
 */

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <stdint.h>
#include "stdlib.h"
#include <ti/csl/hw_types.h>
#include "pmhal_prcm.h"
#include "hw_pmhal_videopll_data.h"
#include <ti/csl/cslr_dss.h>
#include "pm_utils.h"

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_POST_DIV_M2 divider
 */
registerBitField_t     PMHAL_PRCM_DPLL_POST_DIV_M2_regBitField =
{
    HDMI_PLL_CONFIGURATION4_REGM2_MASK,
    HDMI_PLL_CONFIGURATION4_REGM2_SHIFT
};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_POST_DIV_M4 divider
 */
registerBitField_t     PMHAL_PRCM_DPLL_POST_DIV_M4_regBitField =
{
    HDMI_PLL_CONFIGURATION1_M4_CLOCK_DIV_MASK,
    HDMI_PLL_CONFIGURATION1_M4_CLOCK_DIV_SHIFT
};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_POST_DIV_M6 divider
 */
registerBitField_t     PMHAL_PRCM_DPLL_POST_DIV_M6_regBitField =
{
    HDMI_PLL_CONFIGURATION3_M6_CLOCK_DIV_MASK,
    HDMI_PLL_CONFIGURATION3_M6_CLOCK_DIV_SHIFT
};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_POST_DIV_M6 divider
 */
registerBitField_t     PMHAL_PRCM_DPLL_POST_DIV_M7_regBitField =
{
    HDMI_PLL_CONFIGURATION3_M7_CLOCK_DIV_MASK,
    HDMI_PLL_CONFIGURATION3_M7_CLOCK_DIV_SHIFT
};

/**
 *  \brief Structure defining PMHAL_VIDEOPLL_VIDEO1 divider configuration
 */
pmhalVideopllPostDiv_t PMHAL_VIDEOPLL_VIDEO1_postdividers[] =
{
    {
        PMHAL_PRCM_DPLL_POST_DIV_M4,
        &PMHAL_PRCM_DPLL_POST_DIV_M4_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M6,
        &PMHAL_PRCM_DPLL_POST_DIV_M6_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M7,
        &PMHAL_PRCM_DPLL_POST_DIV_M7_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_POST_DIV_M2_regBitField
    }
};

/**
 *  \brief Structure defining PMHAL_VIDEOPLL_VIDEO2 divider configuration
 */
pmhalVideopllPostDiv_t PMHAL_VIDEOPLL_VIDEO2_postdividers[] =
{
    {
        PMHAL_PRCM_DPLL_POST_DIV_M4,
        &PMHAL_PRCM_DPLL_POST_DIV_M4_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M6,
        &PMHAL_PRCM_DPLL_POST_DIV_M6_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M7,
        &PMHAL_PRCM_DPLL_POST_DIV_M7_regBitField
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_POST_DIV_M2_regBitField
    }
};

/**
 *  \brief Structure defining PMHAL_VIDEOPLL_VIDEO2 divider configuration
 */
pmhalVideopllPostDiv_t PMHAL_VIDEOPLL_HDMI_postdividers[] =
{
    {
        PMHAL_PRCM_DPLL_POST_DIV_M4,
        NULL
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M6,
        NULL
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M7,
        NULL
    },
    {
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_POST_DIV_M2_regBitField
    }
};

/**
 *  \brief structure defining Video pll Elements
 */
const pmhalVideopll_t  pmhalVideoElems[] =
{
    {
        (SOC_PLLCTRL1_BASE + HDMI_PLL_CONTROL),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_CONFIGURATION1),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_CONFIGURATION2),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_CONFIGURATION3),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_CONFIGURATION4),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_GO),
        (SOC_PLLCTRL1_BASE + HDMI_PLL_STATUS),
        (SOC_DSI_PROTOCOL_ENGINE1_BASE + DSI_CLK_CTRL_OFFSET),
        (CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_SHIFT),
        VSIZE_TYPE(PMHAL_VIDEOPLL_VIDEO1_postdividers, pmhalVideopllPostDiv_t),
        PMHAL_VIDEOPLL_VIDEO1_postdividers
    },
    {
        (SOC_PLLCTRL3_BASE + HDMI_PLL_CONTROL),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_CONFIGURATION1),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_CONFIGURATION2),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_CONFIGURATION3),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_CONFIGURATION4),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_GO),
        (SOC_PLLCTRL3_BASE + HDMI_PLL_STATUS),
        (SOC_DSI_PROTOCOL_ENGINE3_BASE + DSI_CLK_CTRL_OFFSET),
        (CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_DSS_CONTROL_DISABLE_SHIFT),
        VSIZE_TYPE(PMHAL_VIDEOPLL_VIDEO2_postdividers, pmhalVideopllPostDiv_t),
        PMHAL_VIDEOPLL_VIDEO2_postdividers
    },
    {
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONTROL),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION1),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION2),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION3),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION4),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_GO),
        (SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_STATUS),
        (SOC_DSI_PROTOCOL_ENGINE1_BASE + DSI_CLK_CTRL_OFFSET),
        (CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_SHIFT),
        VSIZE_TYPE(PMHAL_VIDEOPLL_HDMI_postdividers, pmhalVideopllPostDiv_t),
        PMHAL_VIDEOPLL_HDMI_postdividers
    },
    {
        (PMHAL_INVALID_REGADDR),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_CONFIGURATION1),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_CONFIGURATION2),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_CONFIGURATION3),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_CONFIGURATION4),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_GO),
        (SOC_OCP2SCP3_DPLLCTRL_SATA_BASE + HDMI_PLL_STATUS),
        (PMHAL_INVALID_REGADDR),
        (CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_SHIFT),
        0,
        NULL
    }
};

/**
 *  \brief structure defining MUX A validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_DPLL_VIDEO1},
    {PMHAL_PRCM_VIDEOPLL_MUX_HDMI,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_DPLL_HDMI}
};

/**
 *  \brief structure defining MUX B validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_HDMI,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_HDMI},
    {PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_VIDEO1},
    {PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_VIDEO2},
    {PMHAL_PRCM_VIDEOPLL_MUX_ABE,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_ABE}
};

/**
 *  \brief structure defining MUX C validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_HDMI,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_HDMI},
    {PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_VIDEO1},
    {PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_VIDEO2}
};

/**
 *  \brief structure defining LCD3 Switch validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM,
     DSS_CTRL_LCD3_CLK_SWITCH_DSS_CLK_SEL},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12,
     DSS_CTRL_LCD3_CLK_SWITCH_DPLL_DSI1_C_CLK1_SEL}
};

/**
 *  \brief structure defining LCD2 Switch validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM,
     DSS_CTRL_LCD2_CLK_SWITCH_DSS_CLK_SEL},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2,
     DSS_CTRL_LCD2_CLK_SWITCH_DPLL_DSI1_B_CLK1_SEL}
};

/**
 *  \brief structure defining LCD1 Switch validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM,
     DSS_CTRL_LCD1_CLK_SWITCH_DSS_CLK_SEL},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1,
     DSS_CTRL_LCD1_CLK_SWITCH_DPLL_DSI1_A_CLK1_SEL}
};

/**
 *  \brief structure defining F_CLK Switch validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_PRCM,
     DSS_CTRL_FCK_CLK_SWITCH_DSS_CLK},
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_HDMI_CLK1,
     DSS_CTRL_FCK_CLK_SWITCH_DPLL_HDMI_CLK1},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2,
     DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_B_CLK1},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1,
     DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_A_CLK1},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12,
     DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_C_CLK1}
};

/**
 *  \brief structure defining Mux A1 validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_ALTCLK1_SEL_ALTCLK1_SEL},
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_ALTCLK1_SEL_DSI1_A_CLK1_SELECTION}
};

/**
 *  \brief structure defining Mux B2 validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL2,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_ALTCLK2_SEL_ALTCLK2_SEL},
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_ALTCLK2_SEL_DSI1_B_CLK1_SELECTION}
};

/**
 *  \brief structure defining Mux C12 validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_ALTCLK12_SEL_ALTCLK1_SEL},
    {PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL2,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_ALTCLK12_SEL_ALTCLK2_SEL},
    {PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1,
     CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_ALTCLK12_SEL_DSI1_C_CLK1_SELECTION}
};

/**
 *  \brief structure defining ALTCLK1 validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_DPLL_SATA},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_PCIEREF,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_DPLL_PCIEREF},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_VIN1B_CLK,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_VIN1B_CLK},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_VIN1A_CLK,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_VIN1A_CLK},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_WAKEUP1_PIN,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_WAKEUP1_PIN},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_WAKEUP0_PIN,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_WAKEUP0_PIN}
};

/**
 *  \brief structure defining ALTCLK2 validEnum Elements
 */
validEnum_t           PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2_validEnum[] =
{
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_DPLL_SATA},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_PCIEREF,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_DPLL_PCIEREF},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_VIN1B_CLK,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_VIN1B_CLK},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_VIN1A_CLK,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_VIN1A_CLK},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_WAKEUP1_PIN,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_WAKEUP1_PIN},
    {PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_WAKEUP0_PIN,
     CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_WAKEUP0_PIN}
};

/**
 *  \brief structure defining Video pll Mux A Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_SHIFT};

/**
 *  \brief structure defining Video pll Mux B Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_SHIFT};

/**
 *  \brief structure defining Video pll Mux C Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_SHIFT};

/**
 *  \brief structure defining Video pll LCD3 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH_regBitField =
{(SOC_DSS_FAMILY_BASE + DSS_CTRL),
 DSS_CTRL_LCD3_CLK_SWITCH_MASK,
 DSS_CTRL_LCD3_CLK_SWITCH_SHIFT};

/**
 *  \brief structure defining Video pll LCD2 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH_regBitField =
{(SOC_DSS_FAMILY_BASE + DSS_CTRL),
 DSS_CTRL_LCD2_CLK_SWITCH_MASK,
 DSS_CTRL_LCD2_CLK_SWITCH_SHIFT};

/**
 *  \brief structure defining Video pll LCD1 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH_regBitField =
{(SOC_DSS_FAMILY_BASE + DSS_CTRL),
 DSS_CTRL_LCD1_CLK_SWITCH_MASK,
 DSS_CTRL_LCD1_CLK_SWITCH_SHIFT};

/**
 *  \brief structure defining Video pll F CLK Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH_regBitField =
{(SOC_DSS_FAMILY_BASE + DSS_CTRL),
 DSS_CTRL_FCK_CLK_SWITCH_MASK,
 DSS_CTRL_FCK_CLK_SWITCH_SHIFT};

/**
 *  \brief structure defining MUX A1 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_ALTCLK1_SEL_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_ALTCLK1_SEL_SHIFT};

/**
 *  \brief structure defining MUX B2 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_ALTCLK2_SEL_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_ALTCLK2_SEL_SHIFT};

/**
 *  \brief structure defining MUX C12 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_ALTCLK12_SEL_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_ALTCLK12_SEL_SHIFT};

/**
 *  \brief structure defining ALKTCLK1 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_ALTCLK1_SEL_SHIFT};

/**
 *  \brief structure defining ALKTCLK2 Elements
 */
regBitField_t         PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2_regBitField =
{(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL),
 CTRL_CORE_DSS_PLL_CONTROL_ALTCLK2_SEL_MASK,
 CTRL_CORE_DSS_PLL_CONTROL_ALTCLK2_SEL_SHIFT};

/**
 *  \brief structure defining Video pll Mux Elements
 */
const pmhalVideoMux_t pmhalVidMuxElems[] =
{
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A_validEnum, validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B_validEnum, validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C_validEnum, validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD1_CLK_SWITCH_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD2_CLK_SWITCH_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_LCD3_CLK_SWITCH_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_F_CLK_SWITCH_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1_validEnum,
                        validEnum_t)},
    {&PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2_regBitField,
     PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2_validEnum,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2_validEnum,
                        validEnum_t)}
};

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

