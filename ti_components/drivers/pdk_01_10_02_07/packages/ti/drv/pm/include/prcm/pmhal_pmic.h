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
 *  \addtogroup PM_HAL_VM
 *
 *  The Power Management IC (PMIC) Manager is used to set and read back the
 *  voltage on the voltage rails of the System on Chip (SoC) through its
 *  interaction with the external PMIC on the board via I2C.
 *  The VM uses the HAL abstraction provided by the PMIC Manager to set a
 *  given voltage domain to a desired voltage.
 *  The PMIC API would not retain any state which would record the voltage/OPP
 *  setting for a given regulator that it is programming. The only state
 *  maintained at the PMIC HAL would be the function pointers populated on the
 *  PMIC registration.
 *
 *  The PMIC APIs do not work independently. They need to be populated with
 *  the right PMIC operation functions (using function pointers) by the
 *  application to achieve the desired operation.
 * @{
 */

/**
 *  \file  pmhal_pmic.h
 *
 *  \brief This file contains the PMIC API.
 *         The PMIC API provides a generic PMIC interface to the users while
 *         abstracting the different PMIC HW. A user can bind a specific
 *         PMIC HW to this PMIC interface by registering the
 *         pmhalPmicOperations_t type with the PMIC module.
 */

#ifndef PMHAL_PMHAL_PMIC_H_
#define PMHAL_PMHAL_PMIC_H_

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

/**
 * \brief  Power Management IC device callbacks.
 */
typedef struct pmhalPmicOperations
{
    pmErrCode_t (*isPresent)(void);
    /**< Return true if the PMIC device is present in the system */
    const char * (*getRevision)(void);
    /**< Return the device revision of the PMIC device */
    pmErrCode_t (*getVendorId)(uint32_t *vendorId);
    /**< Return the PMIC vendor ID */
    pmErrCode_t (*getProductId)(uint32_t *productId);
    /**< Return the PMIC product ID */
    uint32_t (*isRegulatorEnabled)(pmhalPrcmPmicRegulatorId_t regId);
    /**< Is the given regulator of the PMIC enabled? */
    pmErrCode_t (*regulatorEnable)(pmhalPrcmPmicRegulatorId_t regId);
    /**< Enable the given regulator if it isn't already */
    pmErrCode_t (*regulatorDisable)(pmhalPrcmPmicRegulatorId_t regId);
    /**< Disable the given regulator if it isn't already */
    pmErrCode_t (*regulatorGetVoltage)(pmhalPrcmPmicRegulatorId_t regId,
                                       uint32_t                  *voltage);
    /**< Get the current voltage setting of the given regulator */
    pmErrCode_t (*regulatorSetVoltage)(pmhalPrcmPmicRegulatorId_t regId,
                                       uint32_t                   voltage,
                                       uint32_t                   timeout);
    /**< Set the voltage of the given regulator to the given value */
    uint32_t (*regulatorGetConvVoltage)(pmhalPrcmPmicRegulatorId_t regId,
                                        uint32_t                   avsVolt);
    /**< Get the regulator voltage step voltage */
} pmhalPmicOperations_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Register the given PMIC HW.
 *
 *          Note: At present only one PMIC HW registration is supported for
 *          all the regulators. If in future there is a need to support
 *          more than one PMIC HW, then a new API function can be added
 *          to register a PMIC HW to specific regulator.
 *
 * \param   pmicOps     PMIC callback functions
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_FAIL - if the API fails.
 *                    - #PM_SUCCESS - If the PMIC API is able register the
 *                      function pointers.
 */
pmErrCode_t PMHALPmicRegister(const pmhalPmicOperations_t *pmicOps);

/**
 * \brief   Get the PMIC device revision.
 *
 * \return  revision    The revision string.
 */
const char *PMHALPmicGetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID.
 *
 * \param   vendorId    PMIC Vendor ID is populated in this parameter.
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_FAIL - if the API fails.
 *                    - #PM_SUCCESS - If the PMIC API is able to get the vendor
 *                      Identification Number.
 */
pmErrCode_t PMHALPmicGetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID.
 *
 * \param   productId    PMIC Product ID is populated in this parameter.
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_FAIL - if the API fails.
 *                    - #PM_SUCCESS - If the PMIC API is able to get the product
 *                      Identification Number.
 */
pmErrCode_t PMHALPmicGetProductId(uint32_t *productId);

/**
 * \brief   Get the voltage setting of the given regulator.
 *
 * \param   regId       Id of the desired regulator.
 *                      Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   voltage     Voltage in mV returned via this argument.
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_FAIL - if the API fails.
 *                    - #PM_SUCCESS - If the PMIC API is able to get the voltage
 *                      from the regulator ID.
 */
pmErrCode_t PMHALPmicGetRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                         uint32_t                  *voltage);

/**
 * \brief   Set the voltage of the regulator to the mV given.
 *
 * \param   regId       Id of the desired regulator.
 *                      Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   voltage     Voltage in mV to be set.
 * \param   timeout     Timeout iterations to wait for setting the right
 *                      regulator voltage value. Possible values can be:
 *                    - #PM_TIMEOUT_NOWAIT   Do not wait for voltage setting.
 *                    - #PM_TIMEOUT_INFINITE Wait infinitely till the voltage
 *                                          is set.
 *                      Non Zero Value      Wait for the time provided by the
 *                                          user.
 * \param   checkRange  Enables and disables checking of the input voltage
 *                      against allowable voltage range for the device.
 *                      Possible values can be:
 *                    - #TRUE  voltage is checked against allowable range for
 *                             the device
 *                    - #FALSE voltage is not checked against allowable range
 *                             for the device
 *                      WARNING: Disabling the allowable range check and
 *                               inputting a voltage outside the allowable
 *                               range may damage the device.  Please refer to
 *                               the PMIC device specification for allowed
 *                               voltage ranges for each voltage domain prior
 *                               to setting a voltage with allowable range
 *                               checking disabled.
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_FAIL - if the API fails.
 *                    - #PM_SUCCESS - If the PMIC API is able to set the voltage
 *                      from the regulator ID.
 */
pmErrCode_t PMHALPmicSetRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                         uint32_t                   voltage,
                                         uint32_t                   timeout,
                                         uint32_t                   checkRange);

/**
 * \brief   API to find if the given regulator enabled.
 *
 * \param   regId       Regulator Id whose status is to be known.
 *                      Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return  present   - 1 - If the Regulator is enabled.
 *                    - 0 - If the Regulator is disabled.
 */
uint32_t PMHALPmicIsRegulatorEnabled(pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  API to enable the given regulator
 *
 * \param   regId       Regulator Id whose status is to be known.
 *                      Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_SUCCESS if API is a success.
 *                    - #PM_BADARGS
 *                    - #PM_FAIL otherwise.
 */
pmErrCode_t PMHALPmicEnableRegulator(pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  API to disable the given regulator
 *
 * \param   regId       Regulator Id whose status is to be known.
 *                      Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return  retVal      This returns the success or failure of the API.
 *                    - #PM_SUCCESS if API is a success.
 *                    - #PM_BADARGS
 *                    - #PM_FAIL
 */
pmErrCode_t PMHALPmicDisableRegulator(pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief   API to read the AVS voltage and convert it to the regulator voltage
 *          and return the voltage that would have been supplied by the
 *          PMIC given it supports a given step voltage resolution.
 *
 * \param   regId       Regulator ID provided. Refer #pmhalPrcmPmicRegulatorId_t
 *                      for details.
 * \param   avsVolt     AVS voltage which is to be converted to regulator
 *                      voltage
 *
 * \return  convVolt    The voltage that would be supplied by the regulator if
 *                      the AVS voltage is given to the API.
 *                      NOTE: This API does not program the PMIC. It just
 *                      returns the calculated value of AVS voltage converted to
 *                      PMIC voltage based on the PMIC voltage resolution.
 */
uint32_t PMHALPmicGetConvRegulatorVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                          uint32_t                   avsVolt);

#ifdef __cplusplus
}
#endif

#endif

/* @} */

