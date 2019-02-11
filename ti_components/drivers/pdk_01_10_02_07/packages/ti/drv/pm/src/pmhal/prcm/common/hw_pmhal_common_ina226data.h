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
 * \file    hw_pmhal_common_ina226data.h
 *
 * \brief   This file contains the APIs to access the INA226 power measurement
 *          data structure.
 */

#ifndef HW_PMHAL_INA226_COMMON_DATA_
#define HW_PMHAL_INA226_COMMON_DATA_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**  Macro for the INA226 register address for CONFIGURATION_REGISTER */
#define PMHAL_INA226_CONFIGURATION_REGISTER             (0x0U)
/**  Macro for the INA226 register address for SHUNT_VOLTAGE */
#define PMHAL_INA226_SHUNT_VOLTAGE                      (0x1U)
/**  Macro for the INA226 register address for BUS_VOLTAGE */
#define PMHAL_INA226_BUS_VOLTAGE                        (0x2U)

/**  Macro for mask of the INA226 CONFIGURATION_REGISTER Average field*/
#define PMHAL_INA226_CONFIGURATION_AVG_MASK             (0xE00U)
/**  Macro for shift of the INA226 CONFIGURATION_REGISTER Average field*/
#define PMHAL_INA226_CONFIGURATION_AVG_SHIFT            (9U)

/**  Macro for mask of the INA226 CONFIGURATION_REGISTER
 *   Bus Voltage Conversion Time field */
#define PMHAL_INA226_CONFIGURATION_VBUS_CT_MASK         (0x1C0U)

/**  Macro for shift of the INA226 CONFIGURATION_REGISTER
 *   Bus Voltage Conversion Time field */
#define PMHAL_INA226_CONFIGURATION_VBUS_CT_SHIFT        (6U)

/**  Macro for mask of the INA226 CONFIGURATION_REGISTER
 *   Shunt Voltage Conversion Time field */
#define PMHAL_INA226_CONFIGURATION_VSHUNT_CT_MASK       (0x038U)

/**  Macro for shift of the INA226 CONFIGURATION_REGISTER
 *   Shunt Voltage Conversion Time field */
#define PMHAL_INA226_CONFIGURATION_VSHUNT_CT_SHIFT      (3U)

/**  Macro which defines which instance of I2C is to be used to read INA226 */
#define PMHAL_INA226_HSI2C_INST_NUMBER                  (2U)

/**  Number of nano volts per lsb of the Shunt voltage register */
#define PMHAL_INA226_SHUNT_NANOV_PER_LSB                (2500)

/**  Number of micro volts per lsb of the bus voltage register */
#define PMHAL_INA226_BUS_MICROV_PER_LSB                 (1250)

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief   Container for the outputs read from the INA for a given voltage
 *          rail.
 */
typedef struct pmhalIna226RegulatorData
{
    uint8_t  i2cAddress;
    /**< I2C address of the INA to which the regulator is connected */
    uint32_t shuntResistance;
    /**< Shunt resistance value in milli ohms */
} pmhalIna226RegulatorData_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Find the I2C address which corresponds to the voltage domain ID.
 *
 * \param  voltDomId   Voltage Domain ID for which the value needs
 *                     to be found. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 *
 * \return i2cAddr     I2C address corresponding to the INA226 for the given
 *                     voltage domain.
 */
uint8_t PmhalIna226GetI2cAddress(pmhalPrcmPmicRegulatorId_t voltDomId);

/**
 * \brief  Find the shunt resistance which corresponds to the voltage domain ID.
 *
 * \param  voltDomId   Voltage Domain ID for which the value needs
 *                     to be found. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 *
 * \return shuntRes    Shunt resistance corresponding to the INA226 for the
 *                     given voltage domain.
 */
uint32_t PmhalIna226GetShuntRes(pmhalPrcmPmicRegulatorId_t voltDomId);

#ifdef __cplusplus
}
#endif

#endif

