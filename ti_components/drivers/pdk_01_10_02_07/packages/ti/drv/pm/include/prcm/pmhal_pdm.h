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
 *   \ingroup PM_HAL PM HAL API
 *   \defgroup POWER_DOMAIN Power Domain Configuration
 *      The Power Domain Manager (PDM) is a component of Power Management (PM)
 *      software which helps in putting a particular power domain to the
 *      different power states, reading the current and the last power states
 *      in which the power domain is present.
 *      \n The PDM also allows the user to set the supported Logic and
 *      memory retention states in which the  power domain logic and
 *      memory should be put in.
 *      \n The PDM HAL API would not retain any state which would record which
 *      power domain is being configured for what state.
 *      \n The HAL does not provide any sequencing with respect to powering down
 *      a given module. It only provides the abstraction for register access.
 *
 * @{
 */

/**
 *  \file     pmhal_pdm.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of Power Domain Manager (PDM).
 */

#ifndef PMHAL_PDM_H_
#define PMHAL_PDM_H_

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
 * \brief   This API write to the power state for the power domain (PD)
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdState         The power domain state is populated in this
 *                          argument. Refer enum #pmhalPrcmPdState_t for details
 * \param   timeout         Required timeout for which the API should wait for
 *                          the power domain to go to the desired state.
 *                         - #PM_TIMEOUT_NOWAIT    - The API does not wait.
 *                         - #PM_TIMEOUT_INFINITE  - The API waits
 *                          till the power domain transition happens. If it
 *                          does not happen the API waits infinitely for the
 *                          power domain to reach the desired state.
 *                          Any other value - The API waits to any one of the
 *                          events to happen first :
 *                \n (1)(Success)Power domain reaches the desired state.
 *                \n (2)(Failure)The timeout is reached but no power domain
 *                      state change.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdState write is successful.
 *         - #PM_BADARGS    Indicates the pdState write is not successful and
 *                          the pdId is incorrect or register is not supported
 *                          or the pdState value is invalid.
 *         - #PM_FAIL       Indicates the time out is reached and the power
 *                          domain did not change to the desired value.
 */
int32_t PMHALPdmSetPDState(pmhalPrcmPdId_t pdId, pmhalPrcmPdState_t pdState,
                           uint32_t timeout);

/**
 * \brief   This API reads the power state configured for the power domain (PD)
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdState         The power domain state is populated in this
 *                          argument. Refer enum #pmhalPrcmPdState_t for details
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdState read is successful.
 *         - #PM_BADARGS    Indicates the pdState read is not successful and
 *                          the pdId is incorrect or register is not supported.
 */
int32_t PMHALPdmGetConfiguredPDState(pmhalPrcmPdId_t     pdId,
                                     pmhalPrcmPdState_t *pdState);

/**
 * \brief   This API sets the Logic retention state when the PD is
 *          retention.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   logicState      Logic retention state is populated in this field.
 *                          Refer enum #pmhalPrcmPdLogicRetState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the logicState write is successful.
 *         - #PM_BADARGS    Indicates the logicState write is not successful and
 *                          the pdId is incorrect or register is not supported.
 */
int32_t PMHALPdmSetLogicRetState(pmhalPrcmPdId_t            pdId,
                                 pmhalPrcmPdLogicRetState_t logicState);

/**
 * \brief   This API reads the Logic retention state configured when the PD is
 *          retention.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   logicState      Logic retention state is populated in this field.
 *                          Refer enum #pmhalPrcmPdLogicRetState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the logicState read is successful.
 *         - #PM_BADARGS    Indicates the logicState read is not successful and
 *                          the pdId is incorrect or register is not supported
 *                          or logicState is NULL.
 */
int32_t PMHALPdmGetConfiguredLogicRetState(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLogicRetState_t *
    logicState);

/**
 * \brief   This API writes to the low power change request field.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   lowPwrReq       Low Power Request is populated in this field.
 *                          Refer enum #pmhalPrcmPdLowPwrStateChangeType_t
 *                          for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the lowPwrReq write is successful.
 *         - #PM_BADARGS    Indicates the lowPwrReq write is not successful and
 *                          the pdId is incorrect or register is not supported.
 */
int32_t PMHALPdmSetLowPwrStateChange(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
    lowPwrReq);

/**
 * \brief   This API reads the low power change request field.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   lowPwrReq       Low Power Request is populated in this field.
 *                          Refer enum #pmhalPrcmPdLowPwrStateChangeType_t
 *                          for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the lowPwrReq read is successful.
 *         - #PM_BADARGS    Indicates the lowPwrReq read is not successful and
 *                          the pdId is incorrect or lowPwrReq is NULL.
 */
int32_t PMHALPdmGetConfiguredLowPwrStateChange(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
                   *lowPwrReq);

/**
 * \brief   This API configures the memory bank status when the
 *          power domain is in retention.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   memBankId       Unique ID of the memory bank.
 * \param   memoryRetState  The memory bank power state when the PD is in RET
 *                          is populated here.
 *                          Refer enum #pmhalPhyBankRetStates_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the memoryRetState write is successful.
 *         - #PM_BADARGS    Indicates the memoryRetState write is not valid and
 *                          the pdId is incorrect or the memory bank does not
 *                          belong to the power domain.
 */
int32_t PMHALPdmSetMemRetState(pmhalPrcmPdId_t         pdId,
                               pmhalPrcmPhyMemBankId_t memBankId,
                               pmhalPhyBankRetStates_t memoryRetState);

/**
 * \brief   This API reads the configured memory bank status when the
 *          power domain is in retention.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   memBankId       Unique ID of the memory bank.
 * \param   memoryRetState  The memory bank power state when the PD is in RET
 *                          is populated here.
 *                          Refer enum #pmhalPhyBankRetStates_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the memoryRetState read is valid.
 *         - #PM_BADARGS    Indicates the memoryRetState read is not valid and
 *                          the pdId is incorrect or the pointer to
 *                          memoryRetState is NULL or the memory bank does not
 *                          belong to the power domain.
 */
int32_t PMHALPdmGetConfiguredMemRetState(
    pmhalPrcmPdId_t         pdId,
    pmhalPrcmPhyMemBankId_t memBankId,
    pmhalPhyBankRetStates_t *
    memoryRetState);

/**
 * \brief   This API reads the current memory bank status when the power domain
 *          is ON.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   memBankId       Unique ID of the memory bank.
 * \param   memOnState      The memory bank power state when the PD is ON
 *                          is populated here.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the memOnState read is valid.
 *         - #PM_BADARGS    Indicates the memOnState read is not valid and
 *                          the pdId is incorrect or the pointer to
 *                          memOnState is NULL or the memory bank does not
 *                          belong to the power domain.
 */
int32_t PMHALPdmGetMemOnState(pmhalPrcmPdId_t         pdId,
                              pmhalPrcmPhyMemBankId_t memBankId,
                              uint32_t               *memOnState);

/**
 * \brief   This API reads the current power domain power status.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdState         The current power domain state is populated in this
 *                          argument.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdState read is valid.
 *         - #PM_BADARGS    Indicates the pdState read is not valid and the pdId
 *                          is incorrect or the pointer to pdState is incorrect.
 */
int32_t PMHALPdmGetCurrPDStatus(pmhalPrcmPdId_t     pdId,
                                pmhalPrcmPdState_t *pdState);

/**
 * \brief   This API reads the current power domain logic power status.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   logicOn         The PD logic power status is populated here.
 *                          1 - If logic is ON, 0 - If logic is OFF.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the logicOn read is valid.
 *         - #PM_BADARGS    Indicates the logicOn read is not valid and
 *                          the pdId is incorrect or the pointer to
 *                          logicOn is NULL.
 */
int32_t PMHALPdmGetCurrLogicStatus(pmhalPrcmPdId_t pdId, uint32_t *logicOn);

/**
 * \brief   This API reads the current memory bank power status in the given
 *          power domain.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   memBankId       Unique ID of the memory bank.
 * \param   memBankState    The memory bank power status is populated here.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the memBankState read is valid.
 *         - #PM_BADARGS    Indicates the memBankState read is not valid and
 *                          the pdId is incorrect or the pointer to
 *                          memBankState is NULL or the memory bank does not
 *                          belong to the power domain.
 */
int32_t PMHALPdmGetCurrMemBankStatus(pmhalPrcmPdId_t         pdId,
                                     pmhalPrcmPhyMemBankId_t memBankId,
                                     pmhalPrcmPdState_t     *memBankState);

/**
 * \brief   This API reads the power domain transition status.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdInTransition  The flag of whether the PD is in transition is
 *                          populated in this field.
 *                          1 - If PD in transition, 0 - If not.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdInTransition read is valid.
 *         - #PM_BADARGS    Indicates the pdInTransition read is not valid and
 *                          the pdId is incorrect or the pointer to
 *                          pdInTransition is NULL.
 */
int32_t PMHALPdmGetPDTransState(pmhalPrcmPdId_t pdId,
                                uint32_t       *pdInTransition);

/**
 * \brief   This API writes to the last power status of the power domain.
 *          This API is mainly used to clear the last entered power status.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdState         The last power domain state is populated in this
 *                          argument.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdState write is valid.
 *         - #PM_BADARGS    Indicates the pdState write is not valid and the
 *                          pdId is incorrect or the value of pdState is wrong.
 */
int32_t PMHALPdmSetLastPDStatus(pmhalPrcmPdId_t    pdId,
                                pmhalPrcmPdState_t pdState);

/**
 * \brief   This API reads the last power status of the power domain.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   pdState         The last power domain state is populated in this
 *                          argument.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return                  Status of the API call. Can be any of the following
 *         - #PM_SUCCESS    Indicates the pdState read is valid.
 *         - #PM_BADARGS    Indicates the pdState read is not valid and the pdId
 *                          is incorrect or the pointer to pdState is incorrect.
 */
int32_t PMHALPdmGetLastPDStatus(pmhalPrcmPdId_t     pdId,
                                pmhalPrcmPdState_t *pdState);

/**
 * \brief   This API finds the corresponding subsystem reset for a given module.
 *
 * \param   pdId            Unique ID of the power domain.
 * \param   modIdx          Module Id of the desired module.
 *
 * \return  resetId         Reset group Id of the corresponding module.
 */
pmhalPrcmResetGroupId_t PMHALPdmGetModuleResetId(pmhalPrcmPdId_t     pdId,
                                                 pmhalPrcmModuleId_t modIdx);

/**
 * \brief   This API finds the corresponding CPU reset for a given CPU
 *          Subsystem.
 *
 * \param   pdId               Unique ID of the power domain.
 * \param   modIdx             Module Id of the desired module.
 * \param   cpuResetId         Array which would hold the reset IDs of the CPU
 *                             resets for a given CPU subsystem.
 * \param   numResetsReturned  Gives the number of CPU resets returned.
 *
 * \return  status             Status of the operation.
 *                            - #PM_SUCCESS - Indicates if the CPU reset IDs are
 *                                          returned correctly.
 *                            - #PM_BADARGS - If the Array and the
 *                                          numResetsReturned is NULL.
 */
pmErrCode_t PMHALPdmGetCpuResetId(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmModuleId_t modIdx,
    pmhalPrcmResetGroupId_t cpuResetId[PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM],
    uint32_t * numResetsReturned);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


