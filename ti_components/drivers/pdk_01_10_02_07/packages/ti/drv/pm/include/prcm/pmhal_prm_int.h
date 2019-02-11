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
 *  -   The PRM INT provides PRM Interrupt interface declarations.
 *
 * @{
 */

/**
 *  \file  pmhal_prm_int.h
 *
 *  \brief This file contains the PRM Interrupt interface declarations.
 *          This file contains declarations of APIs which provide:
 *          - Enabling the particular interrupt line for a particular CPU.
 *          - Disabling the particular interrupt line for a particular CPU.
 *          - Reading the status of a particular interrupt for a particular CPU
 *          - Clearing the status of a particular interrupt for a particular
 *            CPU.
 *          - Waiting for the reception of a given interrupt for a given core.
 */

#ifndef PMHAL_PRM_INT_H_
#define PMHAL_PRM_INT_H_

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
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function allows enabling a single interrupt line from the PRM
 *          for a given CPU. Register abstraction is provided by this API.
 *
 * \param   cpuId   Unique ID of the CPU for which the interrupt should be
 *                  enabled. Refer #pmhalPrcmSocCpuId_t for details.
 * \param   intId   Unique ID of the interrupt line one wants to enable.
 *                  Refer #pmhalPrcmPrmIntId_t for details.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If the interrupt is enabled correctly.
 *                  PM_BADARGS  If the CPU ID, INT ID is incorrect.
 */
int32_t PMHALPrmIntEnableInterrupt(pmhalPrcmSocCpuId_t cpuId,
                                   pmhalPrcmPrmIntId_t intId);

/**
 * \brief   This function allows disabling a single interrupt line from the PRM
 *          for a given CPU. Register abstraction is provided by this API.
 *
 * \param   cpuId   Unique ID of the CPU for which the interrupt should be
 *                  disabled. Refer #pmhalPrcmSocCpuId_t for details.
 * \param   intId   Unique ID of the interrupt line one wants to disable.
 *                  Refer #pmhalPrcmPrmIntId_t for details.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If the interrupt is disabled correctly.
 *                  PM_BADARGS  If the CPU ID, INT ID is incorrect.
 */
int32_t PMHALPrmIntDisableInterrupt(pmhalPrcmSocCpuId_t cpuId,
                                    pmhalPrcmPrmIntId_t intId);

/**
 * \brief   This function allows reading all the SW enabled interrupts
 *          for a given CPU from the Interrupt Enable register.
 *
 * \param   cpuId       Unique ID of the CPU for which the interrupt should be
 *                      read. Refer #pmhalPrcmSocCpuId_t for details.
 * \param   interrupts  The interrupts which are enabled are returned in this
 *                      variable. This parameter is 64 bits as the MPU has 2
 *                      registers in which it stores the interrupts that are
 *                      enabled.
 *
 * \return  status      Status of the API is returned.
 *                      PM_SUCCESS  If the interrupts are read correctly.
 *                      PM_BADARGS  If the CPU ID is incorrect or interrupts is
 *                                  NULL.
 */
int32_t PMHALPrmIntGetEnabledInts(pmhalPrcmSocCpuId_t cpuId,
                                  uint64_t           *interrupts);

/**
 * \brief   This function allows enabling all the interrupts of the PRM
 *          for a given CPU using the Interrupt Enable register.
 *
 * \param   cpuId       Unique ID of the CPU for which all interrupts should be
 *                      enabled. Refer #pmhalPrcmSocCpuId_t for details.
 *
 * \return  status      Status of the API is returned.
 *                      PM_SUCCESS  If the interrupts are enabled correctly.
 *                      PM_BADARGS  If the CPU ID is incorrect.
 */
int32_t PMHALPrmIntEnableAllInts(pmhalPrcmSocCpuId_t cpuId);

/**
 * \brief   This function allows disabling all the interrupts from the PRM
 *          for a given CPU by clearing the Interrupt Enable register.
 *
 * \param   cpuId       Unique ID of the CPU for which all interrupts should be
 *                      disabled. Refer #pmhalPrcmSocCpuId_t for details.
 *
 * \return  status      Status of the API is returned.
 *                      PM_SUCCESS  If the interrupts are disabled correctly.
 *                      PM_BADARGS  If the CPU ID is incorrect.
 */
int32_t PMHALPrmIntDisableAllInts(pmhalPrcmSocCpuId_t cpuId);

/**
 * \brief   This function allows getting the status of an interrupt of the PRM
 *          for a given CPU using the Interrupt Status register.
 *
 * \param   cpuId   Unique ID of the CPU for which all interrupts should be
 *                  enabled. Refer #pmhalPrcmSocCpuId_t for details.
 * \param   intId   Unique ID of the interrupt line one wants to get the status
 *                  of. Refer #pmhalPrcmPrmIntId_t for details.
 * \param   isSet   This variable returns the status of the interrupt
 *                  1 - Interrupt is pending. 0 - Interrupt is not pending.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If the interrupt status is got correctly.
 *                  PM_BADARGS  If the CPU ID, INT ID is incorrect or isSet is
 *                              NULL.
 */
int32_t PMHALPrmIntGetStatus(pmhalPrcmSocCpuId_t cpuId,
                             pmhalPrcmPrmIntId_t intId, uint32_t *isSet);

/**
 * \brief   This function allows waiting for a given interrupt to occur. This is
 *          used for polling for an interrupt.
 *
 * \param   cpuId   Unique ID of the CPU for which to wait.
 *                  Refer #pmhalPrcmSocCpuId_t for details.
 * \param   intId   Unique ID of the interrupt line one wants to wait for.
 *                  Refer #pmhalPrcmPrmIntId_t for details.
 * \param   timeout Indicates the number of iterations to wait for the interrupt
 *                  to get set in the status. Valid values for time out can be:
 *                  (1) Non Zero value for which the code would wait.
 *                  (2) PM_TIMEOUT_INFINITE for which the code would wait till
 *                      the interrupt is received.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If the interrupt is received correctly.
 *                  PM_BADARGS  If the CPU ID, INT ID is incorrect.
 *                  PM_FAIL     If the interrupt is not received in the given
 *                              time out or if time out provided is
 *                              0 or PM_TIMEOUT_NOWAIT
 */
int32_t PMHALPrmIntWaitforInt(pmhalPrcmSocCpuId_t cpuId,
                              pmhalPrcmPrmIntId_t intId, uint32_t timeout);

/**
 * \brief   This function allows clearing the status of an interrupt which is
 *          pending.
 *
 * \param   cpuId   Unique ID of the CPU for the interrupt status clear.
 *                  Refer #pmhalPrcmSocCpuId_t for details.
 * \param   intId   Unique ID of the interrupt line one wants to clear the
 *                  status of. Refer #pmhalPrcmPrmIntId_t for details.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If the interrupt is disabled correctly.
 *                  PM_BADARGS  If the CPU ID, INT ID is incorrect.
 */
int32_t PMHALPrmIntClearStatus(pmhalPrcmSocCpuId_t cpuId,
                               pmhalPrcmPrmIntId_t intId);

/**
 * \brief   This function allows clearing the status of all interrupts which are
 *          pending.
 *
 * \param   cpuId   Unique ID of the CPU for the interrupt status clear.
 *                  Refer #pmhalPrcmSocCpuId_t for details.
 *
 * \return  status  Status of the API is returned.
 *                  PM_SUCCESS  If all interrupt status are cleared correctly.
 *                  PM_BADARGS  If the CPU ID is incorrect.
 */
int32_t PMHALPrmIntClearAllStatus(pmhalPrcmSocCpuId_t cpuId);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


