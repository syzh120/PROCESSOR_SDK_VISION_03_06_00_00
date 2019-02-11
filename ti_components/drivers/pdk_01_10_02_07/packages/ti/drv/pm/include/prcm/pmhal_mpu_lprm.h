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
 *  \addtogroup MISC Infrastructure and Domain List
 *
 *  -   The MPU LPRM Manager is the software HAL which provides register
 *      abstraction for accessing the local PRCM of the MPU subsystem.
 *
 * @{
 */

/**
 *  \file  pmhal_mpu_lprm.h
 *
 *  \brief This file contains the MPU LPRM interface declarations.
 *         The MPU LPRM API supports the following features:
 *         - Mercury Retention Enable.
 *         - Mercury Retention Ramp Up enable + Corresponding ramp time.
 *         - Set the power state of the CPU.
 *         - Read the power status of the CPU.
 *         - Set the clock state of the CPU.
 *         - Read the standby status of the CPU.
 *
 *  \note   The reset capability of MPU LPRM is handled in the Reset
 *          Manager HAL.
 */

#ifndef PMHAL_MPU_LPRM_H_
#define PMHAL_MPU_LPRM_H_

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

/**
 * \brief Structure to capture the MPU LPRM Mercury Retention parameters
 */
typedef struct pmhalMpuLprmHgRampParams
{
    uint8_t hgRampType;
    /**< Indicates the type of the ramp, 0 - Slow Ramp up, 1 - Fast Ramp up */
    uint8_t hgSlowRampTime;
    /**<
     * The value set in this field determines the slow ramp-up time and the
     * duration (number of cycles) of the PONOUTHG to PGOODINHG (transition
     * for power domain without DPS).
     * The duration is computed as 8 x hgSlowRampTime of system clock cycles.
     */
} pmhalMpuLprmHgRampParams_t;

/**
 * \brief Structure to capture the MPU LPRM Power status
 */
typedef struct pmhalMpuPowerStatusParams
{
    pmhalPrcmPdState_t currPowerStatus;
    /**<
     * Indicates the  current power status of the MPU Core.
     * Refer #pmhalPrcmPdState_t
     */
    uint8_t            mpuLogicState;
    /**<
     * Indicates the power state of the logic
     * 0 - Logic Domain is OFF, 1 - Logic Domain is ON
     */
    uint8_t            mpuL1MemoryState;
    /**<
     * CPU_L1 Memory State
     * 0 - Memory is OFF, 1 - Memory is in RET, 2 - Reserved, 3 - Memory is ON
     */
} pmhalMpuPowerStatusParams_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Function to set the HG_EN bit for MPU Mercury retention.
 *
 * \return  None.
 */
void PMHALMpuLprmSetMercuryRetention(void);

/**
 * \brief   Function to clear the HG_EN bit for disallowing MPU Mercury
 *          retention.
 *
 * \return  None.
 */
void PMHALMpuLprmClearMercuryRetention(void);

/**
 * \brief   Function to set the Mercury Retention ramp parameters. This is to be
 *          used only If the HG_EN bit is set.
 *
 * \param   hgRampParam     Structure which holds the parameters to be set for
 *                          correct mercury retention ramp.
 *                          If fast ramp is used then no need to fill the
 *                          hgSlowRampTime field.
 *
 * \return  status          PM_SUCCESS If the ramp parameters are set correctly.
 *                          PM_BADARGS If the slow ramp is enabled and the
 *                                     ramp time provided is 0.
 */
int32_t PMHALMpuLprmSetHgRampParams(
    const pmhalMpuLprmHgRampParams_t *hgRampParam);

/**
 * \brief   Function to set the desired power mode of the MPU core.
 *
 * \param   cpuId   ID of the CPU whose power mode one wants to set.
 *                  0 - for CPU0 and 1 - for CPU1
 * \param   mode    Power mode to be set. Refer enum #pmhalPrcmPdState_t
 *                  for details.
 *
 * \return  status  PM_SUCCESS If the power mode is set correctly.
 *                  PM_BADARGS If the cpuId provided is neither 0 nor 1.
 */
int32_t PMHALMpuLprmSetPowerMode(uint32_t cpuId, pmhalPrcmPdState_t mode);

/**
 * \brief   Function to set the force off bit for CPU1 to go to force off.
 *
 * \param   cpuId   ID of the CPU for whom force off should be set.
 *                  1 - for CPU1
 *
 * \return  status  PM_SUCCESS If the CPU is forced off.
 *                  PM_BADARGS If the cpuId provided is not 1.
 */
int32_t PMHALMpuLprmSetForceOff(uint32_t cpuId);

/**
 * \brief   Function to Clear the force off bit for CPU1 to not go to force off.
 *
 * \param   cpuId   ID of the CPU for whom force off should be set.
 *                  1 - for CPU1
 *
 * \return  status  PM_SUCCESS If the CPU is forced off.
 *                  PM_BADARGS If the cpuId provided is not 1.
 */
int32_t PMHALMpuLprmClearForceOff(uint32_t cpuId);

/**
 * \brief   Function to find If the given CPU power domain is in transition.
 *
 * \param   cpuId           ID of the CPU whose power mode one wants to set.
 *                          0 - for CPU0 and 1 - for CPU1
 * \param   inTransition    This field is populated with the transition state.
 *                          Refer enum #pmhalPrcmPdTransitionState_t for details
 *
 * \return  status          PM_SUCCESS If the transition state is read correctly
 *                          PM_BADARGS If the cpuId provided is neither 0 nor 1
 *                                     or the pointer inTransition is NULL.
 */
int32_t PMHALMpuLprmGetPowerTransitionState(
    uint32_t cpuId,
    pmhalPrcmPdTransitionState_t *
    inTransition);

/**
 * \brief   Function to read the last power state in which the MPU core was in.
 *
 * \param   cpuId           ID of the CPU whose power mode one wants to set.
 *                          0 - for CPU0 and 1 - for CPU1
 * \param   lastPowerState  This field is populated with the last power state.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return  status          PM_SUCCESS If the last power state is read correctly
 *                          PM_BADARGS If the cpuId provided is neither 0 nor 1
 *                                     or the pointer lastPowerState is NULL.
 */
int32_t PMHALMpuLprmGetLastPowerState(uint32_t            cpuId,
                                      pmhalPrcmPdState_t *lastPowerState);

/**
 * \brief   Function to set the last power state in which the MPU core was in.
 *          This API is mainly used to clear the last power status.
 *
 * \param   cpuId           ID of the CPU whose power mode one wants to set.
 *                          0 - for CPU0 and 1 - for CPU1
 * \param   lastPowerState  This field is populated with the last power state.
 *                          Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return  status          PM_SUCCESS If the last power state is set correctly
 *                          PM_BADARGS If the cpuId provided is neither 0 nor 1
 *                                     or the pointer lastPowerState is NULL.
 */
int32_t PMHALMpuLprmSetLastPowerState(uint32_t           cpuId,
                                      pmhalPrcmPdState_t lastPowerState);

/**
 * \brief   Function to read the current power state in which the MPU core is in
 *
 * \param   cpuId           ID of the CPU whose power mode one wants to set.
 *                          0 - for CPU0 and 1 - for CPU1
 * \param   mpuPowerState   This field is populated with the current power
 *                          state. Refer enum #pmhalPrcmPdState_t for details.
 *
 * \return  status          PM_SUCCESS If the last power state is read correctly
 *                          PM_BADARGS If the cpuId provided is neither 0 nor 1
 *                                     or the pointer mpuPowerState is NULL.
 */
int32_t PMHALMpuLprmGetPowerStatus(uint32_t                     cpuId,
                                   pmhalMpuPowerStatusParams_t *mpuPowerState);

/**
 * \brief   Function to set the desired clock mode of the MPU core.
 *
 * \param   cpuId       ID of the CPU whose power mode one wants to set.
 *                      0 - for CPU0 and 1 - for CPU1
 * \param   clockMode   This field holds the desired clock mode state to be set
 *                      Refer #pmhalPrcmCdClkTrnModes_t for details.
 *
 * \return  status      PM_SUCCESS If the clock mode is set correctly.
 *                      PM_BADARGS If the cpuId provided is neither 0 nor 1 or
 *                                 the clock mode is set to SW_SLEEP which is an
 *                                 invalid clock state for MPU.
 */
int32_t PMHALMpuLprmSetClockMode(uint32_t                 cpuId,
                                 pmhalPrcmCdClkTrnModes_t clockMode);

/**
 * \brief   Function to read the standby status of the MPU core.
 *
 * \param   cpuId       ID of the CPU whose power mode one wants to set.
 *                      0 - for CPU0 and 1 - for CPU1
 * \param   standbyEn   This field is populated with the current standby
 *                      state. 0 - If not in standby, 1 - If in standby
 *
 * \return  status      PM_SUCCESS If the standby state is read correctly.
 *                      PM_BADARGS If the cpuId provided is neither 0 nor 1 or
 *                                 the pointer standbyEn is NULL.
 */
int32_t PMHALMpuLprmGetStandbyStatus(uint32_t cpuId, uint8_t *standbyEn);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


