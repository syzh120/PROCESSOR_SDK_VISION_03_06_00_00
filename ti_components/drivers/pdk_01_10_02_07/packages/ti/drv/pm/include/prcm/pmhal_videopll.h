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
 *  \addtogroup PM_HAL_CM
 *
 *  Video-PLL library provides APIs configure the Video PLL to the required
 *  frequency for display application.
 *  Video-pll library calculates the values of multiplier, divider and
 *  post divider, these values selected may not be with least jitter.
 *  In case the frequency cannot be obtained from any combination the lib
 *  doesn’t approximate to nearest but returns an error status as values cannot
 *  be calculated.
 *
 * @{
 */

/**
 *  \file      pmhal_videopll.h
 *
 *  \brief     This file contains enumeration declarations for different
 *             elements of videopll. This is only for tda2xx.
 */

#ifndef PMHAL_VIDEOPLL_H_
#define PMHAL_VIDEOPLL_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/pm_types.h>
#include <ti/csl/cslr_dss.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/** \brief  Video pll Go Completed */
#define PMHAL_VIDEOPLL_PLL_GO_DONE          (HDMI_PLL_GO_DONE)

/** \brief  Video pll Go Initiated */
#define PMHAL_VIDEOPLL_PLL_GO_GO            (HDMI_PLL_GO_GO)

/** \brief  Video Dss Control Disable */
#define PMHAL_VIDEOPLL_DSS_CONTROL_DISABLE \
    (CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_PLLDISABLED)

/** \brief  Video Dss Control Enable */
#define PMHAL_VIDEOPLL_DSS_CONTROL_ENABLE \
    (CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_PLLENABLED)

/** \brief  PCLK REF Clock Select */
#define PMHAL_VIDEOPLL_REFSEL_REF_PCLK \
    (HDMI_PLL_CONFIGURATION2_REFSEL_REF_PCLK)
/** \brief  REF1 Clock Select */
#define PMHAL_VIDEOPLL_REFSEL_REF_1       (HDMI_PLL_CONFIGURATION2_REFSEL_REF_1)
/** \brief  REF2 Clock Select */
#define PMHAL_VIDEOPLL_REFSEL_REF_2       (HDMI_PLL_CONFIGURATION2_REFSEL_REF_2)
/** \brief  SYSCLK Clock Select */
#define PMHAL_VIDEOPLL_REFSEL_REF_SYSCLK \
    (HDMI_PLL_CONFIGURATION2_REFSEL_REF_SYSCLK)

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Enum for the Venc's
 *  Caution: Do not change the enum values
 *           these are exact match of Bsp_PlatformVenc .
 */
typedef enum videopllVenc
{
    PMHAL_VIDEOPLL_VENC_LCD1 = 0,
    /**< LCD1 Venc. */
    PMHAL_VIDEOPLL_VENC_LCD2,
    /**< LCD2 Venc. */
    PMHAL_VIDEOPLL_VENC_LCD3,
    /**< LCD3 Venc */
    PMHAL_VIDEOPLL_VENC_HDMI,
    /**< HDMI PLL. */
    PMHAL_VIDEOPLL_VENC_MAX
    /**< This should be last Enum. */
} pmhalVideoPllVenc_t;

/**
 *  \brief Enum defining HS divider for video pll
 *
 */
typedef enum pmhalVideopllHSD
{
    PMHAL_VIDEOPLL_HSD_INVALID = 0x7FFFFFFFU,
    /**< HSD INVALID enum. */
    PMHAL_VIDEOPLL_HSD_MIN = 0U,
    /**< Min value of the enum. Can be used for validation. */
    PMHAL_VIDEOPLL_HSD_M4 = PMHAL_VIDEOPLL_HSD_MIN,
    /**< Value of the enum for HSDivider M4 */
    PMHAL_VIDEOPLL_HSD_M6 = 1U,
    /**< Value of the enum for HSDivider M6 */
    PMHAL_VIDEOPLL_HSD_M7 = 2U,
    /**< Value of the enum for HSDivider M7 */
    PMHAL_VIDEOPLL_HSD_M2 = 3U,
    /**< Value of the enum for HSDivider M2 */
    PMHAL_VIDEOPLL_HSD_MAX = PMHAL_VIDEOPLL_HSD_M2
    /**< Max value of the enum. Can be used for
     *                       validation. */
} pmhalVideopllHSD_t;

/**
 *  \brief Enum defining loop bandwidth mode. Valid only for TDA2px.
 *         The DPLL design targets a loop bandwidth of REFCLK/50 (1x mode).
 *         However, due to minor estimation inaccuracies, the estimated loop
 *         bandwidth will be in the range of REFCLK/70 to REFCLK/30. The BW
 *         can be increased or decreased by programming the following controls.
 *         The damping factor (zeta) remains constant for any Bandwidth
 *         programmed.
 */
typedef enum pmhalPrcmLoopBwMode
{
    PMHAL_PRCM_LOOP_BW_MIN = 0U,
    /**< Minimum Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_1x = PMHAL_PRCM_LOOP_BW_MIN,
    /**< 1x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_0p5x = 1U,
    /**< 0.5x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_0p25x = 2U,
    /**< 0.25x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_0p125x = 3U,
    /**< 0.125x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_1x_1 = 4U,
    /**< 1x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_2x = 5U,
    /**< 2x Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_MAX = PMHAL_PRCM_LOOP_BW_2x,
    /**< Max Loop Bandwidth */
    PMHAL_PRCM_LOOP_BW_COUNT = PMHAL_PRCM_LOOP_BW_MAX + 1U
    /**< Loop Bandwidth Count */
} pmhalPrcmLoopBwMode_t;

/**
 * \brief This shall be used by the APIs to take configuration input from the
 *        user. This struct will not be modelled to represent a PLL.
 *        This is only for tda2xx.
 */
typedef struct pmhalVideopllSelectConfig
{
    uint8_t pllRefEn;
    /**< PLL_REFEN  */
    uint8_t phyClkinEn;
    /**< DSIPHY_CLKINEN  */
    uint8_t hsdivBypass;
    /**< HSDIVBYPASS  */
    uint8_t refSysclk;
    /**< REF_SYSCLK  */
    uint8_t clockEnM4;
    /**< CLOCK_EN_M4  */
    uint8_t clockEnM6;
    /**< CLOCK_EN_M6  */
    uint8_t clockEnM7;
    /**< CLOCK_EN_M7  */
    uint8_t pllLockSel;
    /**< Selects the lock criteria for the PLL. Used only in TDA2px for
     *   Sata PLL.
     */
    uint8_t pllSelFreqDco;
    /**< DCO frequency range selector Used only in TDA2px for
     *   Sata PLL.
     */
} pmhalVideopllSelectConfig_t;

/**
 * \brief This shall be used by the APIs to take configuration input from the
 *        user. This struct will not be modelled to represent a PLL.
 *        This is only for tda2xx.
 */
typedef struct pmhalVideopllModeConfig
{
    uint8_t pllIdle;
    /**< PLL_IDLE  */
    uint8_t pllLpMode;
    /**< PLL_PLLLPMODE  */
    uint8_t lowCurrStBy;
    /**< PLL_LOWCURRSTBY  */
    uint8_t driftGuardEn;
    /**< PLL_DRIFTGUARDEN  */
    uint8_t lockSel;
    /**< PLL_LOCKSEL  */
    uint8_t refEn;
    /**< PLL_REFEN  */
    uint8_t phyClkinEn;
    /**< PHY_CLKINEN  */
    uint8_t byPassEn;
    /**< BYPASSEN  */
    uint8_t hsDivbyPass;
    /**< HSDIVBYPASS  */
} pmhalVideopllModeConfig_t;

/**
 * \brief This shall be used by the APIs to take configuration input from the
 *        user. This structure will not be modelled to represent a PLL.
 *        This is only for tda2xx.
 */
typedef struct pmhalVideopllConfig
{
    uint16_t                     multiplier;
    /**< Multiplier value for DPLL configuration. */
    uint16_t                     divider;
    /**< Divider value for DPLL configuration. */
    uint32_t                     fracM;
    /**< Fractional Multiplier Value */
    pmhalPrcmPllPostDivValue_t  *postDivConfList;
    /**< List of post divider configuration values. */
    uint32_t                     maxPostDivElems;
    /**< Maximum post divider elements. */
    pmhalVideopllSelectConfig_t *videopllSelectConfig;
    /**< Structure contains Configuration1 and 3 pll elements */
    pmhalVideopllModeConfig_t   *videopllModeConfig;
    /**< Structure contains video pll mode elements */
} pmhalVideopllConfig_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API configures different parameters of PLL as indicated by the
 *        input. If the multiplier and divider are updated it also
 *        makes sure the PLL is locked with new values.The post divider is also
 *        considered as part of PLL. This API can be used to configure the PLL
 *        with initial values only.
 *
 * Note: The PLL configuration will affect the clock supplied to the down
 *       stream nodes. The caller is expected to handle the down stream of nodes
 *       which will be affected by this change.
 *       Function ultimately locks the DPLL.
 *       This is only for tda2xx.
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   *pVideopllData  Video Configuration values.
 *                          Refer enum #pmhalVideopllConfig_t for values.
 * \param   timeOut         Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllConfigure(pmhalPrcmNodeId_t            videopllId,
                               const pmhalVideopllConfig_t *pVideopllData,
                               uint32_t                     timeOut);

/**
 * \brief This API sets the multiplexer with the given mux select value.
 *        This is only for tda2xx.
 *
 * \param   muxId           Unique ID of the mux.
 * \param   pParentNodeId   Mux parent node id.
 *                          Refer enum #pmhalPrcmVideopllMuxSelectId_t for
 *                          values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid Video Pll id
 */
int32_t PMHALVideopllConfigureMux(
    pmhalPrcmVideopllDssClkSrcMuxId_t muxId,
    pmhalPrcmVideopllMuxSelectId_t
    pParentNodeId);

/**
 * \brief This API sets the SCP CLock.
 *        This is only for tda2xx.
 *
 * \param videopllId       Unique ID of the VideoPll.
 * \param value            Value to be set.
 *                          (Only Enabled/Disabled are valid values)
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid Video Pll id
 */
int32_t PMHALVideopllSetSCPClk(pmhalPrcmNodeId_t videopllId, uint32_t value);

/**
 * \brief This API Sets PLL Programming (Enabled/Disabled).
 *        This is only for tda2xx.
 *
 * \param videopllId        Unique ID of the VideoPll.
 * \param value             Value to be set.
 *                          (Only Enabled/Disabled are valid values).
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid Video Pll id
 */
int32_t PMHALVideopllSetPllProgramming(pmhalPrcmNodeId_t videopllId,
                                       uint32_t          value);

/**
 * \brief This API Sets DSI Power (Enabled/Disabled).
 *        This is only for tda2xx.
 *
 * \param videopllId       Unique ID of the VideoPll.
 * \param value            Value to be set.
 *                          (Only Enabled/Disabled are valid values).
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid Video Pll id
 */
int32_t PMHALVideopllSetDSIPower(pmhalPrcmNodeId_t videopllId, uint32_t value);

/**
 * \brief This API gets videopll reset status .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return  reset status returned by Control Register
 *
 */
int32_t PMHALVideopllGetResetStatus(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API sets Auto Power mode (Enabled/Disabled).
 *        This is only for tda2xx.
 *
 * \param videopllId       Unique ID of the VideoPll.
 * \param value            Value to be set.
 *                          (Only Enabled/Disabled are valid values).
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid Video Pll id
 */
int32_t PMHALVideopllSetAutoPowerMode(pmhalPrcmNodeId_t videopllId,
                                      uint32_t          value);

/**
 * \brief This API gets the power mode .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return Current power mode of the VideoPLL
 *
 */
int32_t PMHALVideopllGetPowerMode(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API gets the Lock status .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return Current lock states of the VideoPLL weither locked or no
 *
 */
int32_t PMHALVideopllGetLockStatus(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API gets the Divider Value .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return Divider value set in VideoPLL
 *
 */
int32_t PMHALVideopllGetDivider(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API gets the Multiplier Value .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return Multiplier value set in VideoPLL
 *
 */
int32_t PMHALVideopllGetMultiplier(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API gets the Fractional Multiplier Value .
 *        This is only for tda2xx.
 *
 * \param videopllId            Unique ID of the VideoPll.
 *
 * \return Fractional Multiplier value set in VideoPLL
 *
 */
int32_t PMHALVideopllGetFracMultiplier(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API gets the HS Divider Value .
 *        This is only for tda2xx.
 *
 * \param videopllId         Unique ID of the Videopll.
 * \param videopllHSD        Enum for HS divider for videopll.
 * \param hsdivValue         HS Divider value set in VideoPLL.
 *
 * \return  errorStatus         Status of API call. Can be any of the following,
 *        - #PM_SUCCESS          Indicates the operation is success
 *        - #PM_VIDEOPLL_HSDIV_NOT_SUPPORTED  Indicates HSDivider id passed
 *                               is invalid
 *        - #PM_BADARGS          Invalid Video Pll id
 *
 */
int32_t PMHALVideopllGetHSDivider(pmhalPrcmNodeId_t  videopllId,
                                  pmhalVideopllHSD_t videopllHSD,
                                  uint32_t          *hsdivValue);

/**
 * \brief This API returns the configured Videopll for given Venc Id
 *
 * \param VencId       Input Venc who's source to be returned.
 * \param videopllId    Unique ID of the video pll which is configured.
 * \param postDivId     Unique ID of the post divider which is configured.
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid Video Pll id
 *
 */
int32_t PMHALVideopllGetVencSource(pmhalVideoPllVenc_t VencId,
                                   pmhalPrcmClockId_t *videopllId,
                                   pmhalVideopllHSD_t *postDivId);

/**
 * \brief This API sets the divide (DPLL N) value of a divider.
 *        Value of N should be provided by this API.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to set a different divider this API shall be called.
 *
 * Note:  This change in the clock divider may affect the modules which
 *        derive clock from this dpll. The application is expected to ensure
 *        other modules are handled to accommodate this change.
 *        This is only for tda2xx.
 *
 * \param videopllId        Unique ID of the node.
 * \param divValue          Divider value
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid Video Pll id
 */
int32_t PMHALVideopllSetDivider(pmhalPrcmNodeId_t videopllId,
                                uint32_t          divValue);

/**
 * \brief This API sets the multiplication (DPLL M) value of a multiplier .
 *        At reset the multiplication value will be set to the reset value.
 *        If the application need to set a different multiplication as desired.
 *
 * Note:  This change in the clock multiplication may affect the modules which
 *        derive clock from this dpll. The application is expected to ensure
 *        other modules are handled to accommodate this change.
 *        This is only for tda2xx.
 *
 * \param videopllId        Unique ID of the node.
 * \param mulValue          Multiplication factor.
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid Video Pll id
 */
int32_t PMHALVideopllSetMultiplier(pmhalPrcmNodeId_t videopllId,
                                   uint32_t          mulValue);
/**
 * \brief This API sets the divide value of a HSdivider.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to set a different divider this API shall be called.
 *
 * Note:  This change in the clock divider may affect the modules which take
 *        clock from this divider. The application is expected to ensure other
 *        modules are handled to accommodate this change.
 *        This is only for tda2xx.
 *
 * \param   videopllId          Unique ID of the PLL
 * \param   divConfig           Structure with divider parameters
 * \param   maxPostDivElems     Maximum number of post div elements
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllSetPostDiv(
    pmhalPrcmNodeId_t                 videopllId,
    const pmhalPrcmPllPostDivValue_t *divConfig,
    uint32_t                          maxPostDivElems);

/**
 * \brief This API sets the select Fields of configuration2 .
 *        Configuration2 Registor contains the select bit fields for
 *        Video pll operating modes.
 *        This is only for tda2xx.
 *
 * \param   videopllId          Unique ID of the PLL
 * \param   pSelectConfig       Structure with select Field parameters
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllSetSelectFields(
    pmhalPrcmNodeId_t videopllId,
    const pmhalVideopllSelectConfig_t *
    pSelectConfig);

/**
 * \brief This API sets the select Fields of configuration2 .
 *        Configuration2 Registor contains the select bit fields for
 *        Video pll operating modes.
 *        This is only for tda2xx.
 *
 * \param   videopllId          Unique ID of the PLL
 * \param   pSelectConfig       Structure with select Field parameters which
 *                              are to be filled
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllGetSelectFields(
    pmhalPrcmNodeId_t videopllId,
    pmhalVideopllSelectConfig_t *
    pSelectConfig);

/**
 * \brief This API sets the pll Go register .
 *        This is only for tda2xx.
 *
 * \param   videopllId     Unique ID of the PLL
 * \param   value          Value to be set.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllSetpllGo(pmhalPrcmNodeId_t videopllId, uint32_t value);

/**
 * \brief This API gets the pll Go register .
 *        This is only for tda2xx.
 *
 * \param   videopllId     Unique ID of the PLL
 *
 * \return  value          Value been set (negative if fails)
 *
 */
int32_t PMHALVideopllGetpllGo(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API sets the Mode Fields of configuration2 .
 *        Configuration2 Registor contains the bit fields for
 *        Video pll operating modes.
 *        This is only for tda2xx.
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   pModeConfig     Structure with select Field parameters
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllSetModeFields(pmhalPrcmNodeId_t                videopllId,
                                   const pmhalVideopllModeConfig_t *pModeConfig);

/**
 * \brief This API sets the Mode Fields of configuration2 .
 *        Configuration2 Registor contains the bit fields for
 *        Video pll operating modes.
 *        This is only for tda2xx.
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   pModeConfig     Structure with select Field parameters which is
 *                          to be updated.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllGetModeFields(pmhalPrcmNodeId_t          videopllId,
                                   pmhalVideopllModeConfig_t *pModeConfig);
/**
 * \brief This API sets the loop bandwidth fields in control module. Applicable
 *        only to TDA2px.
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   mode            Field selecting the loop BW mode configuration.
 *                          Refer #pmhalPrcmLoopBwMode_t.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllSetLoopBw (pmhalPrcmNodeId_t            videopllId,
                                pmhalPrcmLoopBwMode_t        mode);
/**
 * \brief This API gets the loop bandwidth fields in control module. Applicable
 *        only to TDA2px.
 *
 * \param   videopllId      Unique ID of the PLL
 * \param   mode            Field selecting the loop BW mode configuration.
 *                          Refer #pmhalPrcmLoopBwMode_t.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid Video Pll id
 */
int32_t PMHALVideopllGetLoopBw (pmhalPrcmNodeId_t            videopllId,
                                pmhalPrcmLoopBwMode_t        *mode);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_PRCM_H_ */

/* @} */


