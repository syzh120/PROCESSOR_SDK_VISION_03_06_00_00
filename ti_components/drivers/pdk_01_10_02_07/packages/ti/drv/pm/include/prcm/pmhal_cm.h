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
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup PM_HAL_CM Clock Configuration
 *
 *   The Clock Domain Manager (CM) is a component of the Power Management (PM)
 *   software which provides access to the PRCM database to enable/disable the
 *   clock domains and provides APIs to program the dividers DPLL and
 *   multiplexers
 *
 *   Clock domain API would not take care of the elements in the path which
 *   source clock from the given DPLL when the DPLL frequency is changed.
 *   USER / APP needs to monitor the same and make changes accordingly.
 * @{
 */

/**
 *  \file     pmhal_cm.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of PRCM Clock mode.
 *            This also contains some related macros.
 */

#ifndef PMHAL_CM_H_
#define PMHAL_CM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

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
 *        with initial values and also to change the frequency during OPP
 *        change (DVFS).
 *
 * Note: The PLL configuration will affect the clock supplied to the down
 *       stream nodes. The caller is expected to handle the down stream of nodes
 *       which will be affected by this change.
 *       Function ultimately locks the DPLL.
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   *pDpllData   PRCM Configuration values.
 *                       Refer enum #pmhalPrcmDpllConfig_t for values.
 * \param   timeOut      Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllConfigure(pmhalPrcmNodeId_t            dpllId,
                             const pmhalPrcmDpllConfig_t *pDpllData,
                             uint32_t                     timeOut);

/**
 * \brief This API sets the divide (DPLL N) value of a divider.
 *        The hardware divides by (N+1) internally. Value of N should be
 *        provided by this API.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to set a different divider this API shall be called.
 *
 * Note:  This change in the clock divider may affect the modules which
 *        derive clock from this dpll. The application is expected to ensure
 *        other modules are handled to accommodate this change.
 *
 * \param dpllId         Unique ID of the node.
 * \param dividerValue   divider value
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid clock domain id
 */
int32_t PMHALCMDpllDividerSet(pmhalPrcmNodeId_t dpllId, uint32_t dividerValue);

/**
 * \brief This API sets the multiplication (DPLL M) value of a multiplier .
 *        At reset the multiplication value will be set to the reset value.
 *        If the application need to set a different multiplication as desired.
 *
 * Note:  This change in the clock multiplication may affect the modules which
 *        derive clock from this dpll. The application is expected to ensure
 *        other modules are handled to accommodate this change.
 *
 * \param dpllId            Unique ID of the node.
 * \param mulValue          Multiplication factor.
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid clock domain id
 */
int32_t PMHALCMDpllMultiplierSet(pmhalPrcmNodeId_t dpllId, uint32_t mulValue);

/**
 * \brief This API is used to multiplier value (M) of the given DPLL.
 *
 * \param dpllId             Unique ID of the dpll.
 *
 * \return mulValue          Multiplier value.
 */
uint32_t PMHALCMDpllGetMultiplier(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API is applicable only for TDA3xx SR2.0.
 *        This API sets the fractional multiplication (DPLL Frac M) value of a
 *        multiplier . At reset the multiplication value will be set to the
 *        reset value. If the application need to set a different
 *        multiplication as desired.
 *
 * \note  This change in the clock multiplication may affect the modules which
 *        derive clock from this dpll. The application is expected to ensure
 *        other modules are handled to accommodate this change.
 *
 * \param dpllId            Unique ID of the node.
 * \param fracValue         Multiplication factor.
 *
 * \return  errorStatus     Status of API call. Can be any of the following,
 *        - #PM_SUCCESS      Indicates the operation is success
 *        - #PM_FAIL         Indicates the API failed to complete the
 *                          desired functionality (timeout)
 *        - #PM_BADARGS      Invalid clock domain id
 */
int32_t PMHALCMDpllSetFracMultiplier(pmhalPrcmNodeId_t dpllId,
                                     uint32_t          fracValue);

/**
 * \brief This API is used to fractional multiplier value (Frac M) of the
 *        given DPLL. This API is applicable only for TDA3xx SR2.0.
 *
 * \param dpllId             Unique ID of the dpll.
 *
 * \return mulValue          Multiplier value.
 */
uint32_t PMHALCMDpllGetFracMultiplier(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API is used to get divider value (N) of the given DPLL.
 *
 * \param dpllId              Unique ID of the dpll.
 *
 * \return dividerValue       Divider value.
 */
uint32_t PMHALCMDpllGetDivider(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API configures the DPLL_EN field with the desired DPLL power mode
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   dpllMode     PRCM Configuration values. User can set the dpll mode.
 *                       Refer enum #pmhalPrcmDpllPowerMode_t for values.
 * \param   timeOut      Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetOperationMode(pmhalPrcmNodeId_t        dpllId,
                                    pmhalPrcmDpllPowerMode_t dpllMode,
                                    uint32_t                 timeOut);

/**
 * \brief This API returns the status of DPLL_EN MODE .
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   dpllMode     Resultant Mode of DPLL
 *                       Refer enum #pmhalPrcmDpllPowerMode_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetOperatingMode(pmhalPrcmNodeId_t         dpllId,
                                    pmhalPrcmDpllPowerMode_t *dpllMode);

/**
 * \brief This API Locks the Pll.
 *
 * \param   dpllId       Unique ID of the DPLL
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllLock(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API Unlock the Pll.
 *
 * \param   dpllId       Unique ID of the DPLL
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllUnLock(pmhalPrcmNodeId_t dpllId);

/**
 * \brief This API gets the dpll lock status .
 *
 * \param dpllId      Unique ID of dpll.
 *
 * \return 0 if Unlocked
 *         1 if Locked
 */
uint32_t PMHALCMDpllLockStatus(pmhalPrcmNodeId_t dpllId);

/**
 * \brief   This API Sets the desired DPLL ramp level .
 *
 *          The DPLL provides an output clock frequency ramping feature when
 *          switching from bypass clock to normal clock during lock and re-lock.
 *          The frequency ramping will happen in a maximum of 4 steps in
 *          frequency before the DPLL's frequency lock indicator is asserted.
 *          This register is used to enable/disable the DPLL ramping feature.
 *
 * \param dpllId       Unique ID of the PLL
 * \param rampLevel    PRCM Configuration values. User can set the Ramp Level
 *                     Refer enum #pmhalPrcmDpllRampLevel_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetRampLevel(pmhalPrcmNodeId_t        dpllId,
                                pmhalPrcmDpllRampLevel_t rampLevel);

/**
 * \brief This API Sets the desired DPLL ramp rate.
 *
 *        Selects the time in terms of DPLL REFCLKs spent at
 *        each stage of the clock ramping process
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   rampRate     PRCM Configuration values. User can set the Ramp Rate
 *                       Refer enum #pmhalPrcmDpllRampRate_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetRampRate(pmhalPrcmNodeId_t       dpllId,
                               pmhalPrcmDpllRampRate_t rampRate);

/**
 * \brief   This API Sets the DPLL Drift guard.
 *
 *          This bit allows to enable or disable the automatic
 *          recalibration feature of the DPLL. The DPLL will
 *          automatically start a recalibration process upon assertion
 *          of the DPLL's RECAL flag if this bit is set
 *
 * \param   dpllId       Unique ID of the PLL
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetDriftGuard(pmhalPrcmNodeId_t dpllId);

/**
 * \brief   This API sets the DutyCycleCorrector bit for dpll.
 *
 * \param   dpllId       Unique ID of the DPLL
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetDutyCycleCorrector(pmhalPrcmNodeId_t dpllId);

/**
 * \brief   This API gets the DutyCycleCorrector bit for the dpll.
 *
 * \param   dpllId       Unique ID of the DPLL
 *
 * \param   status       Populates the value in the DCC_EN bitfiled
 *                       0 if the DCC is disabled
 *                       1 if the DCC is enabled
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetDutyCycleCorrector(pmhalPrcmNodeId_t dpllId,
                                         uint8_t          *status);

/**
 * \brief   This API gets the type of the dpll.
 *
 * \param   dpllId       Unique ID of the DPLL
 *
 * \param   type         Populates the type of the DPLL
 *                       refer #pmhalPrcmDpllType_t for more details
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetDpllType(pmhalPrcmNodeId_t    dpllId,
                               pmhalPrcmDpllType_t *type);

/**
 * \brief This API Sets the desired DPLL in LowPowerMode  .
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   timeOut      Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetLowPowerMode(pmhalPrcmNodeId_t dpllId, uint32_t timeOut);

/**
 * \brief This API configures the DPLL AUTO power MODE.
 *
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   dpllMode     Resultant Mode of DPLL
 *                       Refer enum #pmhalPrcmDpllPowerMode_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetAutoPowerMode(pmhalPrcmNodeId_t        dpllId,
                                    pmhalPrcmDpllPowerMode_t dpllMode);

/**
 * \brief This API reads and returns the DPLL AUTO power MODE.
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   dpllMode     Resultant Mode of DPLL
 *                       Refer enum #pmhalPrcmDpllPowerMode_t for values.
 *
 * \retval  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetAutoPowerMode(pmhalPrcmNodeId_t         dpllId,
                                    pmhalPrcmDpllPowerMode_t *dpllMode);

/**
 * \brief This API configures the DPLL_BYP_CLKSEL field to select bypass clock
 *        input
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   bypassClkSel PRCM Configuration values. User can set the bypass
 *                       selection. Refer enum #pmhalPrcmDpllBypassClkSel_t for
 *                       values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetBypassClkSelect(pmhalPrcmNodeId_t           dpllId,
                                      pmhalPrcmDpllBypassClkSel_t bypassClkSel);

/**
 * \brief This API returns the status of DPLL_BYP_CLKSEL bypass clock selection.
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   bypassClkSel Selected Bypass clock for the given DPLL
 *                       Refer enum #pmhalPrcmDpllClkInput_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetBypassClkSelect(pmhalPrcmNodeId_t        dpllId,
                                      pmhalPrcmDpllClkInput_t *bypassClkSel);

/**
 * \brief This API returns the status of DPLL_BYP_CLKSEL bypass clock selection.
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   bypassClkSel Selected Bypass clock for the given DPLL
 *                       Refer enum #pmhalPrcmDpllClkInput_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetClkOutHIFSelect(pmhalPrcmNodeId_t        dpllId,
                                      pmhalPrcmDpllClkInput_t *bypassClkSel);

/**
 * \brief This API returns the status of DPLL_BYP_CLKSEL bypass clock selection.
 *
 * \param   dpllId       Unique ID of the DPLL
 * \param   bypassClkSel Selected Bypass clock for the given DPLL
 *                       Refer enum #pmhalPrcmDpllClkInput_t for values.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetClkOutHIFSelect(pmhalPrcmNodeId_t       dpllId,
                                      pmhalPrcmDpllClkInput_t bypassClkSel);

/**
 * \brief This API sets the divide value of a HSdivider node in the clock tree.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to set a different divider this API shall be called.
 *
 * Note:  This change in the clock divider may affect the modules which take
 *        clock from this divider. The application is expected to ensure other
 *        modules are handled to accommodate this change.
 *
 * \param   dpllId              Unique ID of the PLL
 * \param   divConfig           Structure with divider parameters
 * \param   maxPostDividerElems Maximum number of post div elements
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetPostDiv(
    pmhalPrcmNodeId_t                 dpllId,
    const pmhalPrcmPllPostDivValue_t *divConfig,
    uint32_t
    maxPostDividerElems);

/**
 * \brief This API returns the divide value of a HSdivider node in the clock
 *        tree.
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   divConfig    Structure with divider name whose value is to get.
 *                       Name of the divider should be mentioned in 'postDivId'
 *                       field of the struct #pmhalPrcmPllPostDivValue_t.
 * \param   maxPostDividerElems Maximum number of post div elements
 *
 * NOTE:    This api returns post divider value in 'configValue' field of the
 *          struct #pmhalPrcmPllPostDivValue_t.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 *          If the divider for a given DPLL is invalid configValue is set with
 *          0xFFFFFFFFU.
 */
int32_t PMHALCMDpllGetPostDiv(pmhalPrcmNodeId_t           dpllId,
                              pmhalPrcmPllPostDivValue_t *divConfig,
                              uint32_t                    maxPostDividerElems);

/**
 * \brief This API gets the clock status of postdivider output clock
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   pPostDivId   Post Divider Id
 *                       Refer enum #pmhalPrcmDpllPostDivId_t for Id's.
 * \param   status       Clock Activity state
 *                       Refer enum #pmhalPrcmClockActivityState_t for vaules.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllGetPostDivClkStatus(
    pmhalPrcmNodeId_t              dpllId,
    pmhalPrcmDpllPostDivId_t       pPostDivId,
    pmhalPrcmClockActivityState_t *status);

/**
 * \brief This API returns all the divide value of a HSdivider node in the clock
 *        tree.
 *
 * \param   dpllId       Unique ID of the PLL
 * \param   divConfig    Structure with divider name whose value is to get.
 *                       Name of the divider should be mentioned in 'postDivId'
 *                       field of the struct #pmhalPrcmPllPostDivValue_t.
 *
 * NOTE:    This api returns post divider value in 'configValue' field of the
 *          struct #pmhalPrcmPllPostDivValue_t.
 *
 * \return  returns the maximum number of post dividers present for the dpll
 */
int32_t PMHALCMDpllGetAllPostDivStatus(
    pmhalPrcmNodeId_t           dpllId,
    pmhalPrcmPllPostDivValue_t *divConfig);

/**
 * \brief   This API checks the clock Activity of a given module.
 *
 * \param   moduleId       Unique ID for module
 * \param   clkId          Unique ID for Clock
 * \param   clkState       Status of the clock.
 *                         Refer enum #pmhalPrcmClockActivityState_t for values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid clock domain id
 */
int32_t PMHALCMGetModuleClockStatus(pmhalPrcmModuleId_t            moduleId,
                                    pmhalPrcmClockId_t             clkId,
                                    pmhalPrcmClockActivityState_t *clkState);

/**
 * \brief This API is used to find if the clocks to a given module are enabled
 *        or disabled. It takes an "or" of all the clock states to the given
 *        module and populates the clockState with 1 if any clock is running
 *        and 0 if all clocks are gated.
 *
 * \param moduleId        Module ID of the interested module.
 * \param clockState      Value updated based on clocks are enabled/disabled.
 *
 * \return status         Return value of the API.
 *                      - #PM_SUCCESS : If the clockState is populated
 **correctly.
 *                      - #PM_BADARGS : If the clockState pointer is NULL or
 *                                     the module is not valid.
 */
int32_t PMHALCMGetModuleAllClockState(pmhalPrcmModuleId_t            moduleId,
                                      pmhalPrcmClockActivityState_t *clockState);

/**
 * \brief This API enables the clock for given modules.
 *
 * \param   moduleId       Unique ID of the module to be enabled
 * \param   clkId          Unique ID of the Clock to get Status
 * \param   timeOut        Wait time duration.
 *
 * NOTE:    This api sets the optional clock and mandatory clock, API assumes
 *          Input clock selection is controlled at mux selection only.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMModuleClockEnable(pmhalPrcmModuleId_t moduleId,
                                 pmhalPrcmClockId_t  clkId,
                                 uint32_t            timeOut);

/**
 * \brief This API disables the clock for given modules.
 *
 * \param   moduleId       Unique ID of the module to be enabled
 * \param   clkId          Unique ID of the Clock to get Status
 * \param   timeOut        Wait time duration.
 *
 * NOTE:    This api sets the optional clock and mandatory clock, API assumes
 *          Input clock selection is controlled at mux selection only.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMModuleClockDisable(pmhalPrcmModuleId_t moduleId,
                                  pmhalPrcmClockId_t  clkId,
                                  uint32_t            timeOut);

/**
 * \brief This API sets all the optional clock for given modules.
 *
 * \param   moduleId       Unique ID of the module to be enabled
 *
 * NOTE:    This api sets the optional clock ,API assumes
 *          Input clock selection is controlled at mux selection only.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMModuleEnableAllOptClock(pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API resets all the optional clock for given modules.
 *
 * \param   moduleId       Unique ID of the module to be enabled
 *
 * NOTE:    This api unsets the optional clock ,API assumes
 *          Input clock selection is controlled at mux selection only.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMModuleDisableAllOptClock(pmhalPrcmModuleId_t moduleId);

/**
 * \brief This API sets the CM clock operating modes.
 *
 * \param   clockdomainId  Unique ID of the Clock Domain
 * \param   mode           Mode at which the CD is desired to operate.
 *                         Refer enum #pmhalPrcmCdClkTrnModes_t for valid modes.
 * \param   timeOut        Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMSetCdClockMode(pmhalPrcmCdId_t          clockdomainId,
                              pmhalPrcmCdClkTrnModes_t mode,
                              uint32_t                 timeOut);

/**
 * \brief   This API gets the Transition Modes of the given clock.
 *
 * \param   cdId           Unique ID of the ClockDomain
 * \param   cdTrnMode      Status of the API call.
 *                         Refer enum #pmhalPrcmCdClkTrnModes_t for values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid clock domain id
 */
int32_t PMHALCMGetCdClockMode(pmhalPrcmCdId_t           cdId,
                              pmhalPrcmCdClkTrnModes_t *cdTrnMode);

/**
 * \brief This API sets the parent clock id of a clock node (multiplexer) in
 *        the clock tree. At reset the parent clock will be set to the reset
 *        selection.
 *
 * \param muxId            Unique ID of the node.
 * \param pParentNodeId    Parent NodeId to be Set.
 *                         Refer enum #pmhalPrcmNodeId_t for values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid clock domain id
 */
int32_t PMHALCMMuxParentSelect(pmhalPrcmNodeId_t muxId,
                               pmhalPrcmNodeId_t pParentNodeId);

/**
 * \brief This API gets the parent clock id of a clock node (multiplexer) in
 *        the clock tree.
 *
 * \param muxId            Unique ID of the node.
 * \param pParentNodeId    Parent NodeId to be Set.
 *                         Refer enum #pmhalPrcmNodeId_t for values.
 *
 * \return  errorStatus    Status of API call. Can be any of the following,
 *        - #PM_SUCCESS     Indicates the operation is success
 *        - #PM_FAIL        Indicates the API failed to complete the
 *                         desired functionality (timeout)
 *        - #PM_BADARGS     Invalid mux id
 */
int32_t PMHALCMMuxParentGet(pmhalPrcmNodeId_t  muxId,
                            pmhalPrcmNodeId_t *pParentNodeId);
/**
 * \brief This API sets the divide value of a divider node in the clock tree.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to set a different divider this API shall be called.
 *
 * Note:  This change in the clock divider may affect the modules which take
 *        clock from this divider. The application is expected to ensure other
 *        modules are handled to accommodate this change.
 *
 * \param   dividerId    Unique ID of the node.
 * \param   dividerValue Value the divider is to divide with.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid clock domain id
 */
int32_t PMHALCMDpllSetClockDivider(pmhalPrcmNodeId_t dividerId,
                                   uint32_t          dividerValue);

/**
 * \brief This API gets the divide value of a divider node in the clock tree.
 *        At reset the divider value will be set to the reset value. If the
 *        application need to get a divider value this API shall be called.
 *
 *
 * \param   dividerId        Unique ID of the node.
 * \param   dividerValue     Value the divider is to divide with.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid divider Id
 */
int32_t PMHALCMDpllGetClockDivider(pmhalPrcmNodeId_t dividerId,
                                   uint32_t         *dividerValue);

/**
 * \brief   This API get the sysclk freq for the board.
 *
 * \return  Frequency of the sysclk in units of KHz .
 */
uint32_t PMHALCMGetSysClockFreq(void);

/**
 * \brief   This API get the sysclk freq Enum for the board.
 *
 * \return  sysClkFreq   Refer enum #pmhalPrcmSysClkVal_t for values.
 */
pmhalPrcmSysClkVal_t PMHALCMGetSysClockFreqEnum(void);

/**
 * \brief This API is applicable only for TDA3xx SR2.0. It allows changing the
 *        DPLL CORE input clock source at run time.
 *
 * \param   sourceId        Unique ID of the DPLL CORE clock source. Valid
 *                          values are PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1 or
 *                          PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2.
 * \param   pDpllData       New PLL configuration based on the chosen input
 *                          clock.
 * \param   timeOut         Wait time duration.
 *
 * \return  errorStatus  Status of API call. Can be any of the following,
 *        - #PM_SUCCESS   Indicates the operation is success
 *        - #PM_FAIL      Indicates the API failed to complete the
 *                       desired functionality (timeout)
 *        - #PM_BADARGS   Invalid source Id
 */
int32_t PMHALCMDpllCoreSwitchSource(pmhalPrcmNodeId_t            sourceId,
                                    const pmhalPrcmDpllConfig_t *pDpllData,
                                    uint32_t                     timeOut);

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_CM_H_ */

/* @} */


