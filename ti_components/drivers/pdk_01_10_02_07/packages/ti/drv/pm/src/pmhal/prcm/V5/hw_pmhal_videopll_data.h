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
 *  \file      pmhal/tda2xx/hw_pmhal_videopll_data.h
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare Video PLL (internal) implementation.
 */

#ifndef HW_PMHAL_VIDEO_PLL_DATA_H_
#define HW_PMHAL_VIDEO_PLL_DATA_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <ti/csl/soc.h>
#include <ti/csl/cslr_dss.h>
#include "pmhal_prcm.h"
#include "pmhal_videopll.h"
#include "hw_pmhal_data.h"

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/** \brief Macro defining the value for DSS STATUS */
#define DSS_CTRL_ADDR            (SOC_DSS_FAMILY_BASE + DSS_CTRL)

/** \brief Macro defining the value for DSI CLKCTRL OFFSET */
#define DSI_CLK_CTRL_OFFSET                 (0x00000054U)

/** \brief Macro defining the value for VIDEOPLL SCPCLK SHIFT */
#define PMHAL_VIDEOPLL_SCPCLK_SHIFT         (14U)

/** \brief Macro defining the value for VIDEOPLL SCPCLK MASK */
#define PMHAL_VIDEOPLL_SCPCLK_MASK          (0x00004000U)

/** \brief Macro defining the value for VIDEOPLL PWR CMD SHIFT */
#define PMHAL_VIDEOPLL_PWRCMD_SHIFT         (30U)

/** \brief Macro defining the value for VIDEOPLL PWR CMD MASK */
#define PMHAL_VIDEOPLL_PWRCMD_MASK          (0xC0000000U)

/** \brief Macro defining the value for VIDEOPLL RESET SHIFT */
#define PMHAL_VIDEOPLL_CTRL_RESET_DONE_SHIFT \
    (HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_SHIFT)

/** \brief Macro defining the value for VIDEOPLL RESET MASK */
#define PMHAL_VIDEOPLL_CTRL_RESET_DONE_MASK \
    (HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_MASK)

/** \brief Macro defining the value for VIDEOPLL LOCK SHIFT */
#define PMHAL_VIDEOPLL_LOCK_SHIFT   (HDMI_PLL_STATUS_LOCK_SHIFT)

/** \brief Macro defining the value for VIDEOPLL LOCK MASK */
#define PMHAL_VIDEOPLL_LOCK_MASK    (HDMI_PLL_STATUS_LOCK_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL AUTOMODE SHIFT */
#define PMHAL_VIDEOPLL_AUTOMODE_SHIFT   (HDMI_PLL_CONTROL_AUTOMODE_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL AUTOMODE MASK */
#define PMHAL_VIDEOPLL_AUTOMODE_MASK    (HDMI_PLL_CONTROL_AUTOMODE_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL MULTIPLIER SHIFT */
#define PMHAL_VIDEOPLL_MULTI_SHIFT   (HDMI_PLL_CONFIGURATION1_REGM_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL MULTIPLIER MASK */
#define PMHAL_VIDEOPLL_MULTI_MASK    (HDMI_PLL_CONFIGURATION1_REGM_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL DIVIDER SHIFT */
#define PMHAL_VIDEOPLL_DIV_SHIFT    (HDMI_PLL_CONFIGURATION1_REGN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL DIVIDER MASK */
#define PMHAL_VIDEOPLL_DIV_MASK     (HDMI_PLL_CONFIGURATION1_REGN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL LPMODE SHIFT */
#define PMHAL_VIDEOPLL_LPMODE_SHIFT \
    (HDMI_PLL_CONFIGURATION2_PLLLPMODE_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL LPMODE MASK */
#define PMHAL_VIDEOPLL_LPMODE_MASK \
    (HDMI_PLL_CONFIGURATION2_PLLLPMODE_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL IDLE SHIFT */
#define PMHAL_VIDEOPLL_IDLE_SHIFT        (HDMI_PLL_CONFIGURATION2_IDLE_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL IDLE MASK */
#define PMHAL_VIDEOPLL_IDLE_MASK         (HDMI_PLL_CONFIGURATION2_IDLE_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL LOWCURRSTBY SHIFT */
#define PMHAL_VIDEOPLL_LOWCURRSTBY_SHIFT \
    (HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL LOWCURRSTBY MASK */
#define PMHAL_VIDEOPLL_LOWCURRSTBY_MASK \
    (HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL DRIFTGUARDEN SHIFT */
#define PMHAL_VIDEOPLL_DRIFTGUARDEN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL DRIFTGUARDEN MASK */
#define PMHAL_VIDEOPLL_DRIFTGUARDEN_MASK \
    (HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL REFEN SHIFT */
#define PMHAL_VIDEOPLL_REFEN_SHIFT     (HDMI_PLL_CONFIGURATION2_REFEN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL REFEN MASK */
#define PMHAL_VIDEOPLL_REFEN_MASK      (HDMI_PLL_CONFIGURATION2_REFEN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M4 CLOCK ENABLE SHIFT */
#define PMHAL_VIDEOPLL_M4_CLOCK_EN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M4 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M4_CLOCK_EN_MASK \
    (HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M4 CLOCK ACK SHIFT*/
#define PMHAL_VIDEOPLL_M4_CLOCK_EN_ACK_SHIFT \
    (HDMI_PLL_STATUS_M4_CLOCK_ACK_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M4 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M4_CLOCK_EN_ACK_MASK \
    (HDMI_PLL_STATUS_M4_CLOCK_ACK_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M6 CLOCK ENABLE SHIFT */
#define PMHAL_VIDEOPLL_M6_CLOCK_EN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M6 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M6_CLOCK_EN_MASK \
    (HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M6 CLOCK ACK SHIFT*/
#define PMHAL_VIDEOPLL_M6_CLOCK_EN_ACK_SHIFT \
    (HDMI_PLL_STATUS_M6_CLOCK_ACK_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M6 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M6_CLOCK_EN_ACK_MASK \
    (HDMI_PLL_STATUS_M6_CLOCK_ACK_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M7 CLOCK ENABLE SHIFT */
#define PMHAL_VIDEOPLL_M7_CLOCK_EN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M7 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M7_CLOCK_EN_MASK \
    (HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL M7 CLOCK ACK SHIFT*/
#define PMHAL_VIDEOPLL_M7_CLOCK_EN_ACK_SHIFT \
    (HDMI_PLL_STATUS_M7_CLOCK_ACK_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL M7 CLOCK ENABLE MASK */
#define PMHAL_VIDEOPLL_M7_CLOCK_EN_ACK_MASK \
    (HDMI_PLL_STATUS_M7_CLOCK_ACK_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL PHY CLKINEN SHIFT */
#define PMHAL_VIDEOPLL_PHY_CLKINEN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL PHY CLKINEN MASK */
#define PMHAL_VIDEOPLL_PHY_CLKINEN_MASK \
    (HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL BYPASSEN SHIFT */
#define PMHAL_VIDEOPLL_BYPASSEN_SHIFT \
    (HDMI_PLL_CONFIGURATION2_BYPASSEN_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL BYPASSEN MASK */
#define PMHAL_VIDEOPLL_BYPASSEN_MASK \
    (HDMI_PLL_CONFIGURATION2_BYPASSEN_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL HSDIVBYPASS SHIFT */
#define PMHAL_VIDEOPLL_HSDIVBYPASS_SHIFT \
    (HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL HSDIVBYPASS MASK */
#define PMHAL_VIDEOPLL_HSDIVBYPASS_MASK \
    (HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL REFSEL SHIFT */
#define PMHAL_VIDEOPLL_REFSEL_SHIFT       (HDMI_PLL_CONFIGURATION2_REFSEL_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL REFSEL MASK */
#define PMHAL_VIDEOPLL_REFSEL_MASK        (HDMI_PLL_CONFIGURATION2_REFSEL_MASK)

/** \brief Macro defining the value for PMHAL VIDEOPLL PLL GO SHIFT */
#define PMHAL_VIDEOPLL_PLL_GO_SHIFT         (HDMI_PLL_GO_SHIFT)

/** \brief Macro defining the value for PMHAL VIDEOPLL PLL GO MASK */
#define PMHAL_VIDEOPLL_PLL_GO_MASK          (HDMI_PLL_GO_MASK)

/** \brief Macro defining the shift for for PMHAL_VIDEOPLL_PLL_SELFREQDCO */
#define PMHAL_VIDEOPLL_PLL_SELFREQDCO_SHIFT       (0x1U)
/** \brief Macro defining the mask for for PMHAL_VIDEOPLL_PLL_SELFREQDCO */
#define PMHAL_VIDEOPLL_PLL_SELFREQDCO_MASK        (0xEU)

/** \brief Macro defining the shift for for PMHAL_VIDEOPLL_PLL_LOCKSEL */
#define PMHAL_VIDEOPLL_PLL_LOCKSEL_SHIFT       (0x9U)
/** \brief Macro defining the mask for for PMHAL_VIDEOPLL_PLL_LOCKSEL */
#define PMHAL_VIDEOPLL_PLL_LOCKSEL_MASK        (0x600U)

/** \brief Macro defining the shift for for PMHAL_VIDEOPLL_PLL_SD */
#define PMHAL_VIDEOPLL_PLL_SD_SHIFT       (10U)
/** \brief Macro defining the mask for for PMHAL_VIDEOPLL_PLL_SD */
#define PMHAL_VIDEOPLL_PLL_SD_MASK        (0x3FC00U)

/** \brief Macro defining address for  DSS PLL CONTROL */
#define DSS_PLL_CONTROL \
    (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL)
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Structure defining register bit-field.
 */
typedef struct registerBitField
{
    uint32_t regMask;
    /**< Mask for bit-field */
    uint8_t  regShift;
    /**< Shift for bit-field from LSB */
} registerBitField_t;

/**
 *  \brief Structure defining the properties of pll post divider.
 */
typedef struct pmhalVideopllPostDiv
{
    pmhalPrcmDpllPostDivId_t postDivId;
    /**< Unique Id of the post divider. */
    registerBitField_t      *postDivBitField;
    /**< Divider configuration bit-field. */
} pmhalVideopllPostDiv_t;

/**
 *  \brief Each PLL in the Soc has to be instantiated with the below data.
 */
typedef struct pmhalVideopll
{
    uint32_t                pllControlRegAddr;
    /**< Video PLL Control Register Address */
    uint32_t                pllConf1RegAddr;
    /**< Video PLL_CONFIGURATION1 Register Address */
    uint32_t                pllConf2RegAddr;
    /**< Video PLL_CONFIGURATION2 Register Address */
    uint32_t                pllConf3RegAddr;
    /**< Video PLL_CONFIGURATION3 Register Address */
    uint32_t                pllConf4RegAddr;
    /**< Video PLL_CONFIGURATION4 Register Address */
    uint32_t                pllGoRegAddr;
    /**< Video PLL_GO Register Address */
    uint32_t                pllStatusRegAddr;
    /**< Video PLL_STATUS Register Address */
    uint32_t                pllDsiRegAddr;
    /**< DSI Register Address */
    uint32_t                dssPllRegShift;
    /**< DSS Register Shift */
    uint32_t                postDividersMax;
    /**< Maximum postdivider elements  */
    pmhalVideopllPostDiv_t *postDividers;
    /**< List of post dividers available in this VideoPLL. */
} pmhalVideopll_t;

/**
 *  \brief  Structure to capture programmed Mux value and
 *          the corresponding bit field value to configure.
 *
 */
typedef struct validEnum
{
    pmhalPrcmVideopllMuxSelectId_t nodeMuxId;
    /**< Mux value configured by User */
    uint8_t                        nodeEnumValue;
    /**< Enum Value corresponding to the supported In nodeName. */
} validEnum_t;

/**
 *  \brief Structure defining the properties of multiplexer.
 *         The link to input clocks are part of the graph's edge property.
 */
typedef struct pmhalVideoMux
{
    regBitField_t *muxSelBitField;
    /**< Multiplexer configuration bit-field. */
    validEnum_t   *pSupportedEnum;
    /**< Array of supported enum values*/
    uint8_t        pSupportedEnumMax;
    /**< Size of pSupportedEnum array */
} pmhalVideoMux_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Array of Videopll Elements  */
extern const pmhalVideopll_t pmhalVideoElems[PMHAL_PRCM_VIDEOPLL_COUNT -
                                             PMHAL_PRCM_VIDEOPLL_MIN];

/** Array of Video Multiplexer Elements  */
extern const pmhalVideoMux_t pmhalVidMuxElems[
    PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX];

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* HW_PMHAL_VIDEO_PLL_DATA_H_ */

