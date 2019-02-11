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
 *  \file      hw_pmhal_data.h
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare PRCM (internal) implementation.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

#ifndef HW_PMHAL_DATA_H_
#define HW_PMHAL_DATA_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm_includes.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/** \brief Macro to find the size of the vector */
#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))

/** \brief PMHAL Optional clock enable */
#define PMHAL_OPT_CLOCK_ENABLE           (1U)

/** \brief PMHAL MAX SysConfigElems */
#define PMHAL_MAX_SYS_CONFIG_ELEMS       (56U)
/** \brief PMHAL Bypass modes shift */
#define PMHAL_CLKMODE_DPLL_EN_SHIFT      (CM_CLKMODE_DPLL_CORE_DPLL_EN_SHIFT)
/** \brief PMHAL Bypass modes mask */
#define PMHAL_CLKMODE_DPLL_EN_MASK       (CM_CLKMODE_DPLL_CORE_DPLL_EN_MASK)

/** \brief PMHAL Duty-cycle corrector shift */
#define PMHAL_CLKSEL_DPLL_DCC_EN_SHIFT  (CM_CLKSEL_DPLL_CORE_DCC_EN_SHIFT)
/** \brief PMHAL Duty-cycle corrector mask */
#define PMHAL_CLKSEL_DPLL_DCC_EN_MASK  (CM_CLKSEL_DPLL_CORE_DCC_EN_MASK)

/** \brief PMHAL dpll bypass clock shift */
#define PMHAL_CLKSEL_DPLL_BYP_CLKSEL_SHIFT  ( \
        CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_SHIFT)
/** \brief PMHAL dpll bypass clock mask */
#define PMHAL_CLKSEL_DPLL_BYP_CLKSEL_MASK  ( \
        CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_MASK)

/** \brief PMHAL dpll bypass clock shift */
#define PMHAL_CLKSEL_DPLL_HIF_CLKSEL_SHIFT  ( \
        CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_SHIFT)
/** \brief PMHAL dpll bypass clock mask */
#define PMHAL_CLKSEL_DPLL_HIF_CLKSEL_MASK  ( \
        CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_MASK)

/** \brief PMHAL Idle state shift */
#define PMHAL_IDLEST_DPLL_ST_CLK_SHIFT   (CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_SHIFT)
/** \brief PMHAL Idle state shift */
#define PMHAL_IDLEST_DPLL_ST_CLK_MASK    (CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_MASK)

/** \brief PMHAL Idle state shift */
#define CM_IDLEST_DPLL_ST_DPLL_MODE_SHIFT \
    (CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_SHIFT)
/** \brief PMHAL Idle state shift */
#define CM_IDLEST_DPLL_ST_DPLL_MODE_MASK \
    (CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_MASK)

/** \brief PMHAL ADPLLS Multiplier shift */
#define PMHAL_CLKSEL_MULT_SHIFT   (CM_CLKSEL_DPLL_CORE_DPLL_MULT_SHIFT)
/** \brief PMHAL ADPLLS Multiplier mask */
#define PMHAL_CLKSEL_MULT_MASK    (CM_CLKSEL_DPLL_CORE_DPLL_MULT_MASK)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/** \brief PMHAL ADPLLS Fractional Multiplier shift */
#define PMHAL_FRACM_SHIFT \
    (CTRL_CORE_SEC_SMA_SW_22_CORE_DPLL_REGMF_CONTROL_SHIFT)
/** \brief PMHAL ADPLLS Fractional Multiplier mask */
#define PMHAL_FRACM_MASK \
    (CTRL_CORE_SEC_SMA_SW_22_CORE_DPLL_REGMF_CONTROL_MASK)
#elif defined (SOC_TDA2PX)
/** \brief PMHAL ADPLLS Fractional Multiplier shift */
#define PMHAL_FRACM_SHIFT \
    (CTRL_CORE_SMA_SW_2_SMA_SW_2_ABE_DPLL_REGMF_CONTROL_SHIFT)
/** \brief PMHAL ADPLLS Fractional Multiplier mask */
#define PMHAL_FRACM_MASK \
    (CTRL_CORE_SMA_SW_2_SMA_SW_2_ABE_DPLL_REGMF_CONTROL_MASK)
#else
/* Not to be used in any other platform */
/** \brief PMHAL ADPLLS Fractional Multiplier shift */
#define PMHAL_FRACM_SHIFT
/** \brief PMHAL ADPLLS Fractional Multiplier mask */
#define PMHAL_FRACM_MASK
#endif

/** \brief DPLL Drift guard shift */
#define PMHAL_DPLL_DRIFTGUARD_EN_SHIFT \
    (CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_SHIFT)
/** \brief DPLL Drift guard mask */
#define PMHAL_DPLL_DRIFTGUARD_EN_MASK \
    (CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_MASK)

/** \brief DPLL Ramp level shift */
#define PMHAL_DPLL_RAMP_LEVEL_SHIFT \
    (CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_SHIFT)
/** \brief DPLL Ramp level mask */
#define PMHAL_DPLL_RAMP_LEVEL_MASK \
    (CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_MASK)

/** \brief DPLL Ramp Rate shift */
#define PMHAL_DPLL_RAMP_RATE_SHIFT \
    (CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_SHIFT)
/** \brief DPLL Ramp Rate mask */
#define PMHAL_DPLL_RAMP_RATE_MASK \
    (CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_MASK)

/** \brief DPLL Divider Shift */
#define PMHAL_DPLL_DIV_SHIFT             (CM_CLKSEL_DPLL_CORE_DPLL_DIV_SHIFT)
/** \brief DPLL Divider Mask */
#define PMHAL_DPLL_DIV_MASK              (CM_CLKSEL_DPLL_CORE_DPLL_DIV_MASK)
/** \brief DPLL Divider Mask */
#define PMHAL_DPLL_USB_DPLL_DIV_MASK \
    (CM_CLKSEL_DPLL_USB_DPLL_DIV_MASK)

/** \brief DPLL bypass clock selection shift */
#define PMHAL_DPLL_BYP_SHIFT \
    (CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_SHIFT)
/** \brief DPLL bypass clock selection mask */
#define PMHAL_DPLL_BYP_MASK \
    (CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_MASK)

/** \brief PMHAL module mode shift */
#define PMHAL_MODULE_MODE_SHIFT \
    (CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_SHIFT)
/** \brief PMHAL module mode mask */
#define PMHAL_MODULE_MODE_MASK \
    (CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_MASK)

/** \brief PMHAL Clock control - idle state shift */
#define PMHAL_CLKCTRL_IDLEST_SHIFT \
    (CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_SHIFT)
/** \brief PMHAL Clock control - idle state mask */
#define PMHAL_CLKCTRL_IDLEST_MASK \
    (CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_MASK)

/** \brief PMHAL Clock control - standby state shift */
#define PMHAL_CLKCTRL_STBYST_SHIFT       (CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_SHIFT)
/** \brief PMHAL Clock control - standby state mask */
#define PMHAL_CLKCTRL_STBYST_MASK        (CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_MASK)

/** \brief PMHAL Clock domain transition shift */
#define PMHAL_CLKSTCTRL_CLKTRCTRL_SHIFT  (CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_SHIFT)
/** \brief PMHAL Clock domain transition mask */
#define PMHAL_CLKSTCTRL_CLKTRCTRL_MASK   (CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_MASK)

/** \brief PMHAL Power domain status shift */
#define PMHAL_PWRSTST_POWERSTATEST_SHIFT (PM_CORE_PWRSTST_POWERSTATEST_SHIFT)
/** \brief PMHAL Power domain status mask */
#define PMHAL_PWRSTST_POWERSTATEST_MASK  (PM_CORE_PWRSTST_POWERSTATEST_MASK)

/** \brief PMHAL Power domain logic status shift */
#define PMHAL_PWRSTST_LOGICSTATEST_SHIFT (PM_CORE_PWRSTST_LOGICSTATEST_SHIFT)
/** \brief PMHAL Power domain logic status mask */
#define PMHAL_PWRSTST_LOGICSTATEST_MASK  (PM_CORE_PWRSTST_LOGICSTATEST_MASK)

/** \brief PMHAL Power domain in transition shift */
#define PMHAL_PWRSTST_INTRANSITION_SHIFT (PM_CORE_PWRSTST_INTRANSITION_SHIFT)
/** \brief PMHAL Power domain in transition mask */
#define PMHAL_PWRSTST_INTRANSITION_MASK  (PM_CORE_PWRSTST_INTRANSITION_MASK)

/** \brief PMHAL Power domain last power status shift */
#define PMHAL_PWRSTST_LASTPOWERSTATEENTERED_SHIFT \
    (PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_SHIFT)
/** \brief PMHAL Power domain last power status mask */
#define PMHAL_PWRSTST_LASTPOWERSTATEENTERED_MASK \
    (PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_MASK)

/** \brief PMHAL Power domain status shift */
#define PMHAL_PWRSTCTRL_POWERSTATE_SHIFT (PM_CORE_PWRSTCTRL_POWERSTATE_SHIFT)
/** \brief PMHAL Power domain status mask */
#define PMHAL_PWRSTCTRL_POWERSTATE_MASK  (PM_CORE_PWRSTCTRL_POWERSTATE_MASK)

/** \brief PMHAL Power domain logic retention state shift */
#define PMHAL_PWRSTCTRL_LOGICRETSTATE_SHIFT \
    (PM_CORE_PWRSTCTRL_LOGICRETSTATE_SHIFT)
/** \brief PMHAL Power domain logic retention state mask */
#define PMHAL_PWRSTCTRL_LOGICRETSTATE_MASK \
    (PM_CORE_PWRSTCTRL_LOGICRETSTATE_MASK)

/** \brief PMHAL Power domain logic power state change shift */
#define PMHAL_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT \
    (PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT)
/** \brief PMHAL Power domain logic power state change mask */
#define PMHAL_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK \
    (PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK)

/** \brief DPLL Low power mode enable shift */
#define PMHAL_CLKMODE_DPLL_LPMODE_EN_SHIFT \
    (CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_SHIFT)
/** \brief DPLL Low power mode enable mask */
#define PMHAL_CLKMODE_DPLL_LPMODE_EN_MASK \
    (CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_MASK)

/** \brief DPLL Auto mode enable shift */
#define PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_SHIFT \
    (CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_SHIFT)
/** \brief DPLL Auto mode enable mask */
#define PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_MASK \
    (CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_MASK)
/** \brief Module SysConfig Standby Mode shift */
#define SYSCONFIG_STANDBYMODE_SHIFT (DSP_SYSCONFIG_STANDBYMODE_SHIFT)
/** \brief Module SysConfig Standby Mode mask */
#define SYSCONFIG_STANDBYMODE_MASK (DSP_SYSCONFIG_STANDBYMODE_MASK)

/** \brief Module SysConfig Idlemode Mode shift */
#define SYSCONFIG_IDLEMODE_SHIFT (DSP_SYSCONFIG_IDLEMODE_SHIFT)
/** \brief Module SysConfig Idlemode Mode mask */
#define SYSCONFIG_IDLEMODE_MASK (DSP_SYSCONFIG_IDLEMODE_MASK)

/** \brief Module SysConfig ClockActivity Mode shift */
#define SYSCONFIG_CLOCKACTIVITY_SHIFT (DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_SHIFT)
/** \brief Module SysConfig ClockActivity Mode mask */
#define SYSCONFIG_CLOCKACTIVITY_MASK (DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_MASK)

/** \brief Powerdomain Powerstate shift */
#define POWERSTATE_SHIFT (PM_CORE_PWRSTCTRL_POWERSTATE_SHIFT)
/** \brief Powerdomain Powerstate mask */
#define POWERSTATE_MASK (PM_CORE_PWRSTCTRL_POWERSTATE_MASK)

/** \brief Powerdomain LogicRetention State shift */
#define LOGICRETSTATE_SHIFT (PM_CORE_PWRSTCTRL_LOGICRETSTATE_SHIFT)
/** \brief Powerdomain LogicRetention State mask */
#define LOGICRETSTATE_MASK (PM_CORE_PWRSTCTRL_LOGICRETSTATE_MASK)

/** \brief Powerdomain LOWPOWERSTATECHANGE shift */
#define LOWPOWERSTATECHANGE_SHIFT (PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT)
/** \brief Powerdomain LOWPOWERSTATECHANGE mask */
#define LOWPOWERSTATECHANGE_MASK (PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK)

/** \brief Powerdomain POWERSTATEST shift */
#define POWERSTATEST_SHIFT (PM_CAM_PWRSTST_POWERSTATEST_SHIFT)
/** \brief Powerdomain POWERSTATEST mask */
#define POWERSTATEST_MASK (PM_CAM_PWRSTST_POWERSTATEST_MASK)

/** \brief Powerdomain LastPowerstateEntered shift */
#define LASTPOWERSTATEENTERED_SHIFT (PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_SHIFT)
/** \brief Powerdomain LastPowerstateEntered mask */
#define LASTPOWERSTATEENTERED_MASK (PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_MASK)

/** \brief Powerdomain LastPowerstateEntered shift */
#define INTRANSITION_SHIFT (PM_CAM_PWRSTST_INTRANSITION_SHIFT)
/** \brief Powerdomain LastPowerstateEntered mask */
#define INTRANSITION_MASK (PM_CAM_PWRSTST_INTRANSITION_MASK)

/** \brief Powerdomain LastPowerstateEntered shift */
#define LOGICSTATEST_SHIFT (PM_CAM_PWRSTST_LOGICSTATEST_SHIFT)
/** \brief Powerdomain LastPowerstateEntered mask */
#define LOGICSTATEST_MASK (PM_CAM_PWRSTST_LOGICSTATEST_MASK)

/** \brief Clock Module DPLL LPMODE shift */
#define PMHAL_DPLL_LPMODE_EN_SHIFT (CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_SHIFT)
/** \brief Clock Module DPLL LPMODE mask */
#define PMHAL_DPLL_LPMODE_EN_MASK (CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_MASK)

/** \brief Clock Module DPLL SELFREQDCO shift */
#define PMHAL_DPLL_SELFREQDCO_SHIFT (CM_CLKSEL_DPLL_USB_DPLL_SELFREQDCO_SHIFT)
/** \brief Clock Module DPLL SELFREQDCO mask */
#define PMHAL_DPLL_SELFREQDCO_MASK (CM_CLKSEL_DPLL_USB_DPLL_SELFREQDCO_MASK)

/** \brief Control Module muxselect0 value for control module postdivider */
#define PMHAL_CTRLMDL_POSTDIV_MUXSEL0_VAL (1U)
/** \brief Control Module muxselect1 value for control module postdivider */
#define PMHAL_CTRLMDL_POSTDIV_MUXSEL1_VAL (1U)
/** \brief Control Module muxselect2 value for control module postdivider */
#define PMHAL_CTRLMDL_POSTDIV_MUXSEL2_VAL (1U)
/** \brief Control Module muxselect3 value for control module postdivider */
#define PMHAL_CTRLMDL_POSTDIV_MUXSEL3_VAL (2U)
/** \brief Control Module muxselect4 value for control module postdivider */
#define PMHAL_CTRLMDL_POSTDIV_MUXSEL4_VAL (1U)

/** \brief Macros for invalid value */
#define PMHAL_INVALID_REGADDR    (0xFFFFFFFFU)
/** \brief PMHAL Invalid address */
#define PMHAL_INVALID_BITFIELD   (0xFFFFFFFFU)
/** \brief PMHAL Invalid bit-field */
#define PMHAL_INVALID_SHIFT      (0xFFU)
/** \brief PMHAL Invalid shift */
#define PMHAL_INVALID_MASK       (0U)
/** \brief PMHAL Invalid mask */
#define PMHAL_CLKSELCTRL_NOTAPPLICABLE (0xFFU)
/** \brief PMHAL CLKCTRL not applicable */
#define PMHAL_REG_NOTAPPLICABLE   (0xFFFFFFFFU)
/** \brief PMHAL register not applicable */
#define PMHAL_BITFIELD_NOTAPPLICABLE   (0xFFFFFFFFU)
/** \brief PMHAL bit-field not applicable*/
#define PMHAL_SHIFT_NOTAPPLICABLE      (0xFFU)
/** \brief PMHAL shift not applicable*/
#define PMHAL_MASK_NOTAPPLICABLE       (0U)
/** \brief PMHAL mask not applicable*/
#define PMHAL_VALUE_NOTAPPLICABLE       (0U)
/** \brief PMHAL value not applicable*/
#define PMHAL_DIV_ENUM_NOTAPPLICABLE   (0xFFU)
/** \brief PMHAL Divider Enum not applicable*/
#define PMHAL_MUX_ENUM_NOTAPPLICABLE   (0xFFU)
/** \brief PMHAL Multiplexer Enum not applicable*/
#define PMHAL_SIDLEMODE_NOTAPPLICABLE  (0xFFU)
/** \brief PMHAL SIDLEMODE Enum not applicable*/
#define PMHAL_DIV_DPLL_CLKST_SHIFT  (CM_DIV_M2_DPLL_CORE_CLKST_SHIFT)
/** \brief PMHAL divider clock status register shift */
#define PMHAL_DIV_DPLL_CLKST_MASK  (CM_DIV_M2_DPLL_CORE_CLKST_MASK)
/** \brief PMHAL divider clock status register Mask */
#define PMHAL_DIV_DPLL_CLKX2ST_SHIFT (CM_DIV_M2_DPLL_PER_CLKX2ST_SHIFT)
/** \brief PMHAL divider clock status X2 register Shift */
#define PMHAL_DIV_DPLL_CLKX2ST_MASK  (CM_DIV_M2_DPLL_PER_CLKX2ST_MASK)
/** \brief PMHAL divider clock status register Mask */
#define PMHAL_MODULEMODE_NOTAPPLICABLE       (0U)
/** \brief PMHAL MODULE MODE not applicable */
#define PMHAL_PRCM_PD_RM_OCCUR_COUNT          (2U)
/** \brief The number of global resets that is software controllable. In TDA2xx
 *         and TDA3xx this value is 2 for Cold and Warm Reset.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Structure defining register bit-field.
 */
typedef struct regBitField
{
    uint32_t regAddr;
    /**< Register address */
    uint32_t regMask;
    /**< Mask for bit-field */
    uint8_t  regShift;
    /**< Shift for bit-field from LSB */
} regBitField_t;

/**
 *  \brief Structure defining register bit-field of width one (no mask).
 */
typedef struct regBitFieldShift
{
    uint32_t regAddr;
    /**< Register address */
    uint8_t  regShift;
    /**< Shift for bit-field from LSB */
} regBitFieldShift_t;

/**
 *  \brief Structure defining the properties of clock.
 */
typedef struct pmhalClock
{
    regBitField_t pClkCtrlBitField;
    /**< Clock Control bitfiled description */
    regBitField_t clkActivityBitField;
    /**< clockactivity bitfiled description */
} pmhalClock_t;

/**
 *  \brief  Structure to capture programmed divider value and
 *          the corresponding bitfield value to configure.
 */
typedef struct validDivValue
{
    uint16_t divValue;
    /**< Divider value configured by User */
    uint8_t  divEnum;
    /**< Bit field configuration value to achieve the above division. */
} validDivValue_t;

/**
 *  \brief  Structure defining the properties of divider.
 *          Divider is defined as one input and one output.
 */
typedef struct pmhalClockDivider
{
    regBitField_t   *pDivCtrlBitField;
    /**< Register bit-field info. If this filed is invalid, then this is a
     *   fixed divider and can be programmed. In this case the value
     *   pSupportedDivision[0] gives the fixed division value. */
    validDivValue_t *pSupportedDivision;
    /**< Array of allowed divValues */
    uint8_t          pSupportedDivisionMax;
    /**< Size of pSupportedDivision array */
} pmhalClockDivider_t;

/**
 *  \brief  Structure to capture programmed Mux value and
 *          the corresponding bitfield value to configure.
 *
 */
typedef struct validEnumValue
{
    pmhalPrcmNodeId_t nodeName;
    /**< Mux value configured by User */
    uint8_t           nodeEnumVaule;
    /**< Enum Vaule corresponding to the supported In nodeName. */
} validEnumValue_t;

/**
 *  \brief Structure defining the properties of multiplexer.
 *         The link to input clocks are part of the graph's edge property.
 */
typedef struct pmhalMultiplexer
{
    regBitField_t    *muxSelBitField;
    /**< Multiplexer configuration bit-field. */
    validEnumValue_t *pSupportedEnum;
    /**< Array of supported enum values*/
    uint8_t           pSupportedEnumMax;
    /**< Size of pSupportedEnum array */
} pmhalMultiplexer_t;

/**
 *  \brief Structure defining the properties of pll post divider.
 */
typedef struct pmhalDpllPostDiv
{
    pmhalPrcmDpllPostDivId_t postDivId;
    /**< Unique Id of the post divider. */
    regBitField_t           *postDivBitField;
    /**< Divider configuration bit-field. */
    pmhalCtrlMdlPostDivIdx_t ctrlModDivIdx;
    /**< whether controlled by control module */
} pmhalDpllPostDiv_t;

/**
 *  \brief Structure defining the properties of pll post divider configured by
 *         control module.
 */
typedef struct pmhalDpllCtrlMdlHsDiv
{
    pmhalPrcmDpllPostDivId_t postDivId;
    /**< Unique Id of the post divider. */
    regBitFieldShift_t      *hsDivTEnableBitField;
    /**< Divider value latching bit field*/
    regBitField_t           *hsDivValBitField;
    /**< Divider configuration bit-field. */
    regBitField_t           *hsDivValEnableBitField;
    /**< Divider Enable bit-field. */
    regBitField_t           *hsDivMuxSelBitField;
    /**< HS divider Mux select configuration bit-field. */
    uint8_t                  muxSelectValue;
    /**< mux select value for this HS divider */
    uint8_t                  valueAdjust;
    /**< Adjustment value which helps the PMHAL CM API to be able to correctly
     *   program the control module post dividers based on the value given by
     *   the user */
} pmhalDpllCtrlMdlHsDiv_t;

/**
 *  \brief Each PLL in the Soc has to be instantiated with the below data.
 */
typedef struct pmhalDpll
{
    uint32_t            pllClkModeRegAddr;
    /**< Clock mode register address. It has configurations for bypass mode,
     *   clock ramp, auto-recalibration, low power mode, spread spectrum
     *   configuration etc... */
    uint32_t            pllIdleStatusRegAddr;
    /**< Idle state register address. It indicates the DPLL lock/unlock(bypass)
     *   status. */
    uint32_t            pllAutoIdleRegAddr;
    /**< Pll AutoIdle register address.*/
    uint32_t            pllClkSelRegAddr;
    /**< Clock select register. It has configurations for DPLL multiplier,
     *   divider, duty cycle correction  and bypass clock selection
     *   configurations. */
    uint32_t            pllClkSel2RegAddr;
    /**< Clock select2 register. This register provides DPLL fractional
     *   multiplier factor control and BandWidth Control for PER DPLL. */
    uint32_t            pllSscDeltaMstepRegAddr;
    /**< Delta MStep register. It controls the DeltaMStep parameter which is
     *   used for Spread Spectrum Clocking technique. */
    uint32_t            pllSscModfreqDivRegAddr;
    /**< Modulation frequency divide register. It controls the Modulation
     *   Frequency (FM) for Spread Spectrum Clocking technique . */
    uint32_t            pllClkDcoLdoRegAddr;
    /**< CLKDCOLOD register address. It includes control and status for
     *   CLKDCOLDO configuration. */
    uint32_t            pllDivElemMask;
    /**< Pll Div Elem register Mask address.*/
    uint32_t            pllMulElemMask;
    /**< Pll Div Elem register Mask address.*/
    uint32_t            pllAutoIdleMask;
    /**< Pll AutoIdle register Mask address.*/
    uint8_t             pllModesSupportedMask;
    /**< Pll Supported modes register Mask address.*/
    uint8_t             pllModesSupportedModes;
    /**< Power Modes - bypass (including type) and lock mode. */
    uint8_t             dpllType;
    /**< Indicates DPLL type - ADPLLS or ADPLLLJ. */
    uint8_t             postDividersMax;
    /**< Number of post dividers in this DPLL. */
    pmhalDpllPostDiv_t *postDividers;
    /**< List of post dividers available in this DPLL. */
    uint8_t             edgePropertyEnum;
    /**< points to the edge Property of this DPLL */
    uint32_t            fracMDivRegAddr;
    /**< Register address for the fractional M divider */
} pmhalDpll_t;

/**
 *  \brief Root clock configuration value.
 */
typedef struct pmhalRootClockValues
{
    uint32_t supportedClockRate;
    /**< Clock rate in Hz */
    uint8_t  configValue;
    /**< Bit-field configuration value corresponding to above clock rate. */
} pmhalRootClockValues_t;

/**
 *  \brief Root clock fields to get the clock rate.
 */
typedef struct regBitFieldRootClk
{
    uint32_t regAddr;
    /**< Root clock rate read register address */
    uint32_t maskFreqSrc;
    /**< Root clock frequency source select mask */
    uint32_t shiftFreqSrc;
    /**< Root clock frequency source select shift */
    uint32_t maskFreqSel1;
    /**< Root clock frequency source1 mask */
    uint32_t shiftFreqSel1;
    /**< Root clock frequency source1 shift */
    uint32_t maskFreqSel2;
    /**< Root clock frequency source2 mask */
    uint32_t shiftFreqSel2;
    /**< Root clock frequency source2 shift */
} regBitFieldRootClk_t;

/**
 *  \brief Structure defining the properties of the root clock.
 */
typedef struct pmhalRootClk
{
    pmhalPrcmRootClkType_t  rootClkType;
    /**< Root clock type indicating fixed/configurable root clock. */
    pmhalRootClockValues_t *pClockRateConfig;
    /**< Supported clock rates and corresponding configuration value. */
    regBitFieldRootClk_t   *pClkCtrlBitField;
    /**< Register bit field to read the root clock. */
    /* uint8_t maxPossibleRates; TODO : Add in auto-generation */
    /**< Number of clock frequency values supported. */
} pmhalRootClk_t;

/**
 *  \brief Structure defining the reset properties of a voltage domain. This
 *         is added for place holder to which Power domains can link to.
 */
typedef struct pmhalVoltageDomain
{
    pmhalPrcmVdId_t vdId;
    /**< Voltage domain ID. */
} pmhalVoltageDomain_t;

/**
 *  \brief Structure defining the Global reset control properties.
 *         These parameters define the properties to configure global reset of
 *         all device modules.
 */
typedef struct pmhalGlobalResetCtrl
{
    regBitFieldShift_t *rstctrlBitField;
    /**< Global Reset control bit field with shift. */
} pmhalGlobalResetControl_t;

/**
 *  \brief Structure defining the Global reset status properties.
 *         These parameters define the properties to get the reset status of a
 *         global reset source.
 */
typedef struct pmhalGlobalResetStatus
{
    regBitFieldShift_t *rstStBitField;
    /**< Global Reset status bit field with shift. */
} pmhalGlobalResetStatus_t;

/**
 *  \brief Structure defining the reset properties of a power domain.
 *         These parameters define the properties to configure the reset of a
 *         power domain.
 */
typedef struct pmhalReset
{
    regBitFieldShift_t *rstCtrlBitField;
    /**< Reset control bit field with shift. */
    regBitFieldShift_t *rstStBitField;
    /**< Reset status bit field with shift. */
    pmhalPrcmModuleId_t toSubsystem;
    /**< Module to which the subsystem reset belongs to. In cases where there
     *   are 2 reset signals to the subsystem only the subsystem reset is
     *   considered not the CPU reset.
     */
    pmhalPrcmModuleId_t toCpu;
    /**< Module to which the CPU reset belongs to. In cases where there
     *   are 2 reset signals to the subsystem only the CPU reset is
     *   considered not the subsystem reset.
     */
} pmhalReset_t;

/**
 *  \brief Structure defining the power domain properties.
 *         These parameters define the properties of power domain and allow
 *         to configure PD to different states.
 */
typedef struct pmhalPowerDomain
{
    uint8_t                  vdId;
    /**< Voltage domain ID to which this power domain belongs to.
     *   Refer #pmhalPrcmVdId_t for details. */
    uint8_t                  validPwrStates;
    /**< Supported power states for the given power domain */
    uint8_t                  validLogicRetState;
    /**< Supported logic retention state for a given power domain */
    uint8_t                  validLowPwrRequest;
    /**< Supported low power request for a given power domain */
    uint8_t                  numMemoryModules;
    /**< Number of memory elements present in the power domain. */
    uint8_t                  numResetDomain;
    /**< Number of reset domain elements present in the power domain. */
    uint8_t                  numClockDomain;
    /**< Number of Clock domain elements present in the power domain. */
    pmhalPrcmPhyMemBankId_t *phyMemoryBankId;
    /**< Memory present in the PD */
    pmhalPrcmResetGroupId_t *resetId;
    /**< Reset domain ID to which the power domain belongs to. */
    pmhalPrcmCdId_t         *clockDomainId;
    /**< Clock Domains present in the PD */
    uint32_t                 pwrStateCtrlRegAddr;
    /**< Power domain state control register address - ON/OFF/Retention */
    uint32_t                 pwrStateStatusRegAddr;
    /**< Power domain state status register address - ON/OFF/Retention */
} pmhalPowerDomain_t;

/**
 *  \brief Structure defining the physical memory.
 *         These parameters define the properties of the physical memory
 *         and allow to configure the memory state.
 */
typedef struct pmhalPhysicalMemory
{
    uint8_t pwrOnStateCtrlShift;
    /**< Bit position for 'ON' state control in the Power state control
     *   register. The register offset is taken from the power domain info. */
    uint8_t pwrRetStateCtrlShift;
    /**< Bit position for 'RET' state control in the Power state control
     *   register. The register offset is taken from the power domain info. */
    uint8_t pwrStateStatusShift;
    /**< Bit position for 'STATEST' state status in the Power state status
     *   register. The register offset is taken from the power domain info. */
    uint8_t pwrRetStateModes;
    /**< Bit map indicating the data retention states of a memory bank WRT a PD.
     *   It can take any of the values from #pmhalPhyBankRetStates_t */
} pmhalPhysicalMemory_t;

/**
 *  \brief Structure defining the clock domain.
 *         These parameters define the properties of the clock domain and
 *         enable clock domain control.
 */
typedef struct pmhalClkDomain
{
    pmhalPrcmPdId_t      powerDomainId;
    /**< Power domain ID to which clock domain belongs to. */
    uint32_t             clkStCtrlAddr;
    /**< Clock state(gated/ungated) status control register address. */
    pmhalPrcmModuleId_t *pFirstModPtr;
    /**< Pointer to module array which has list of modules belonging to this
     *   clock domain. */
    uint32_t             staticDepAddr;
    /**< Static Dependency register base address */
    uint8_t              staticDepCdShift;
    /**< Shift value of the clock domain in the other clock domain static
     *   dependency registers */
    uint8_t              numModulesInCd;
    /**< Number of modules in the clock domain. */
    uint8_t              clkDomainCapability;
    /**< Bit map indicating the capability of the clock domain.
     *   It can take any of the values from #pmhalPrcmCdClkTrnModes_t */
    /*uint32_t              enabledModCount;  TODO:include after fixing in
     * auto-generation. */
} pmhalClkDomain_t;

/**
 *  \brief Structure defining the SIDLEMODE definition.
 *         These parameters define the properties to configure SIDLEMODE
 */
typedef struct pmhalSysConfig
{
    uint32_t sysConfigRegAddr;
    /**< Sysconfig register address. */
    uint8_t  idleModeShift;
    /**< idleMode Shift. */
    uint8_t  isSClockActivityPresent;
    /**< presence of SClkActivity. */
    uint8_t  standbymodeShift;
    /**< standby Shift. */
    uint8_t  standbyMode;
    /**< Bit map indicating the standbyMode supported. It can take any of the
     *   values from #pmhalPrcmModuleMStbyMode_t. */
    uint8_t  sidleMode;
    /**< Bit map indicating the idleModes supported. It can take any of the
     *   values from #pmhalPrcmModuleSIdleMode_t. */
} pmhalSysConfig_t;

/**
 *  \brief Structure defining the Clock Select definition for modules.
 *         These parameters define the properties for selecting input clocks for
 *         a given module
 */
typedef struct pmhalClockSelConfig
{
    pmhalPrcmClockId_t clockId;
    /**< Clock ID. */
    uint8_t            clockSelControlShift;
    /**< clockSelControl Shift address. */
    uint8_t            clockStatusShift;
    /**< clockStatus Shift address. */
} pmhalClockSelConfig_t;

/**
 *  \brief Structure defining the MODULE definition.
 *         These parameters define the properties of a module and allow to
 *         configure, read status and traverse the tree.
 */
typedef struct pmhalModule
{
    uint8_t                clockDomainId;
    /**< Clock domain ID to which this module belongs to.
     *   Refer #pmhalPrcmCdId_t for more details. */
    uint8_t                retentionType;
    /**< Module retention type. */
    uint8_t                pmhalPrcmSysConfigModId;
    /**< SysConfig module ID for the given module. */
    uint8_t                maxClock;
    /**< Number of clocks. */
    uint32_t               clkCtrlRegAddr;
    /**< Clock mode register address. */
    pmhalClockSelConfig_t *clkSelCfg;
    /**< List of all clock select configuration belonging to this module. */
    uint8_t                isStandbySuported;
    /**< Flag indicating whether standby protocol is supported for this
     *   module. */
    uint8_t                moduleMode;
    /**< Bit map indicating the capability of module - Enable, disable,
     *   automatic. It can take any of the values from
     *   #pmhalPrcmModuleSModuleMode_t. */
    uint8_t                edgePropertyEnum;
    /**< points to the edge Property of this Module */
    pmhalPrcmCpuId_t       cpuId;
    /**< CPU ID. It can take any of the values from #pmhalPrcmCpuId_t*/
    /* TODO: The following fields are NA in some devices. Need to check if we
     * can group such fields under conditional compilation to save memory of
     * devices which don't need them.
     * - Static and dynamic dependency
     * - Wakeup dependencies (reg, mask, shift ?)
     * - Context register
     */
} pmhalModule_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Array of Power Domain Elements  */
extern const pmhalPowerDomain_t  pmhalPowerDomainElems[PMHAL_PRCM_PD_COUNT];

/** Array of Module Elements  */
extern const pmhalModule_t       pmhalModuleElems[PMHAL_PRCM_MOD_COUNT -
                                                  PMHAL_PRCM_MOD_LOWER_BOUND];
/** Array of SysConfig Elements  */
extern const pmhalSysConfig_t    pmhalSysConfigElems[PMHAL_PRCM_SYSCFG_COUNT];

/** Array of Reset Domain Elements  */
extern const pmhalReset_t        pmhalResetDomainElems[
    PMHAL_PRCM_RG_PROGRAMMABLE_RST_COUNT];

/** Array of Clock Domain Elements  */
extern const pmhalClkDomain_t    pmhalClockDomainElems[PMHAL_PRCM_CD_COUNT];

/** Array of Physical Memory Elements  */
extern const pmhalPhysicalMemory_t
    pmhalPhysicalMemoryElems[PMHAL_PRCM_PHY_BANK_COUNT];

/** Array of SysClk Freq Elements  */
extern const uint32_t            gPmhalSysClkFreqkHz[PMHAL_PRCM_SYSCLK_COUNT];

/** Array of GlobalReset Status Elements  */
extern const pmhalGlobalResetStatus_t
    pmhalGlobalResetStatusElems[PMHAL_PRCM_GLB_RG_COUNT];

/** Array of GlobalReset Elements  */
extern const pmhalGlobalResetControl_t
    pmhalGlobalResetControlElems[PMHAL_PRCM_PD_RM_OCCUR_COUNT];

/** Array of Multiplexer Elements  */
extern const pmhalMultiplexer_t  pmhalMultiplexerElems[PMHAL_PRCM_MUX_COUNT -
                                                       PMHAL_PRCM_MUX_MIN];

/** Array of Dpll Elements  */
extern const pmhalDpll_t         pmhalDpllElems[PMHAL_PRCM_DPLL_COUNT -
                                                PMHAL_PRCM_DPLL_MIN];

/** Array of Divider Elements  */
extern const pmhalClockDivider_t pmhalDividerElems[PMHAL_PRCM_DIV_COUNT -
                                                   PMHAL_PRCM_DIV_MIN];
/** Array of CtrlModule Dpll Divider Elements  */
extern const pmhalDpllCtrlMdlHsDiv_t
    pmhalCtrlModuleDpllDividerElems[PMHAL_CTRL_POSTDIV_COUNT];

/** Array of Opp Module Max Rate  Elements  */
extern uint32_t pmhalOppModuleMaxRate[PMHAL_PRCM_CPU_ID_COUNT][PMHAL_VM_OPP_MAX
];

/** Array of Dep Cpu List Elements  */
extern pmhalPrcmCpuId_t          pmhalDepCpuList[PMHAL_PRCM_CPU_ID_COUNT];

/** Array of Cpu Module Id Elements  */
extern pmhalPrcmModuleId_t       pmhalCpuModuleId[PMHAL_PRCM_CPU_ID_COUNT];

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* HW_PMHAL_DATA_H_ */

