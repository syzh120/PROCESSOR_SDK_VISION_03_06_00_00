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
 *  The Static Dependency (SD) HAL manager helps to enable or disable the
 *  software configurable static dependency between different clock domains.
 *
 * @{
 */

/**
 *  \file     pmhal_sd.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of Static Dependency Mangager.
 */

#ifndef PMHAL_SD_H_
#define PMHAL_SD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

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
 *  \brief  Enable the static dependency from the master clock domain to the
 *          slave clock domain.
 *
 *  \param  srcDom      Unique Clock domain ID of the master clock domain.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *  \param  destDom     Unique clock domain ID of the slave clock domain.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *
 *  \return status      Status of the API. This can be the following values:
 *                    - #PM_SUCCESS  - The API set the static dependency
 *                                    correctly.
 *                    - #PM_BADARGS  - The master clock domain does not have a
 *                                    static dependency register or the slave
 *                                    clock domain does not have a bit in the
 *                                    static dependency register.
 *                    - #PM_FAIL     - The API set the static dependency but
 *                                    dependency is reserved or not software
 *                                    controllable in the design due to which it
 *                                    can not really set it.
 */
int32_t PMHALStaticDepEnable(pmhalPrcmCdId_t srcDom, pmhalPrcmCdId_t destDom);

/**
 *  \brief  Disable the static dependency from the master clock domain to the
 *          slave clock domain.
 *
 *  \param  srcDom      Unique Clock domain ID of the master clock domain.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *  \param  destDom     Unique clock domain ID of the slave clock domain.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *
 *  \return status      Status of the API. This can be the following values:
 *                    - #PM_SUCCESS  - The API cleared the static dependency
 *                                    correctly.
 *                    - #PM_BADARGS  - The master clock domain does not have a
 *                                    static dependency register or the slave
 *                                    clock domain does not have a bit in the
 *                                    static dependency register.
 *                    - #PM_FAIL     - The API cleared the static dependency but
 *                                    dependency is not software
 *                                    controllable in the design due to which it
 *                                    can not really clear it.
 */
int32_t PMHALStaticDepDisable(pmhalPrcmCdId_t srcDom, pmhalPrcmCdId_t destDom);

/**
 *  \brief  Read the static dependency for a given clock domain.
 *
 *  \param  clockDom    Unique Clock domain ID of the master clock domain.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *  \param  regVal      The read register is stored in the memory location
 *                      pointed to by the pointer regVal. For exact bit field
 *                      set use the shift values mentioned in
 *                      #pmhalStaticDepBitShift_t
 *
 *  \return status      Status of the API. This can be the following values:
 *                    - #PM_SUCCESS  - The API read the static dependency
 *                                    correctly.
 *                    - #PM_BADARGS  - The master clock domain does not have a
 *                                    static dependency register or the regVal
 *                                    pointer is NULL.
 */
int32_t PMHALStaticDepRead(pmhalPrcmCdId_t clockDom, uint32_t *regVal);

/**
 *  \brief  Disable the static dependency from the master clock domain to all
 *          slave clock domains.
 *
 *  \param  masterClockDom  Unique Clock domain ID of the master clock domain.
 *                          Refer enum #pmhalPrcmCdId_t for valid values.
 *
 *  \return status          Status of the API. This can be the following values:
 *                        - #PM_SUCCESS  - The API cleared the static dependency
 *                                        correctly.
 *                        - #PM_BADARGS  - The master clock domain does not have
 *                                        a static dependency register.
 */
int32_t PMHALStaticDepDisableAllSlaveDep(pmhalPrcmCdId_t masterClockDom);

/**
 *  \brief  Disable the static dependency from the slave clock domain to all
 *          master clock domains. This API loops through all the clock domains
 *          and clears the bit corresponding slave. If the static dependency
 *          cannot be cleared the API returns with the Clock domain of the ID
 *          for which the API tried to clear the dependency but could not.
 *
 *  \param  slaveClockDom   Unique Clock domain ID of the slave clock domain.
 *                          Refer enum #pmhalPrcmCdId_t for valid values.
 *  \param  failMasterDom   Unique Clock domain ID of the failed master domain.
 *                          Refer enum #pmhalPrcmCdId_t for valid values.
 *
 *  \return status          Status of the API. This can be the following values:
 *                        - #PM_SUCCESS  - The API cleared the static dependency
 *                                        correctly.
 *                        - #PM_BADARGS  - The slave clock domain does not have
 *                                        a static dependency bit.
 *                        - #PM_FAIL     - The clearing of the bit for a given
 *                                        master failed. The failMasterDom is
 *                                        populated with the master domain clock
 *                                        ID if PM_FAIL is returned only if a
 *                                        valid pointer is sent to the API.
 */
int32_t PMHALStaticDepDisableToAllMaster(pmhalPrcmCdId_t  slaveClockDom,
                                         pmhalPrcmCdId_t *failMasterDom);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


