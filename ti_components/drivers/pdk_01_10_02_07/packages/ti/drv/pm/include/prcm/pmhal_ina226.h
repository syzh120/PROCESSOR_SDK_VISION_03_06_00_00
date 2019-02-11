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
 *  \addtogroup PRCM_STAT PRCM Statistics
 *   APIs to program and read the INA226 power
 *          measurement ICs
 * @{
 */

/**
 *  \file   pmhal_ina226.h
 *
 *  \brief  This file contains the APIs to program and read the INA226 power
 *          measurement ICs.
 */

#ifndef PMHAL_INA226_H_
#define PMHAL_INA226_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/prcm/pmhal_i2cComm.h>

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
 * \brief INA226 ADC conversion time configuration values.
 */
typedef enum pmhalIna226ConvTime
{
    PMHAL_INA226_CONV_TIME_140_MICROS = 0x0U,
    /**< 140 us conversion time */
    PMHAL_INA226_CONV_TIME_MIN = PMHAL_INA226_CONV_TIME_140_MICROS,
    /**< Minimum conversion time */
    PMHAL_INA226_CONV_TIME_204_MICROS = 0x1U,
    /**< 204 us conversion time */
    PMHAL_INA226_CONV_TIME_332_MICROS = 0x2U,
    /**< 332 us conversion time */
    PMHAL_INA226_CONV_TIME_588_MICROS = 0x3U,
    /**< 588 us conversion time */
    PMHAL_INA226_CONV_TIME_1P1_MILLIS = 0x4U,
    /**< 1.1 ms conversion time */
    PMHAL_INA226_CONV_TIME_2P116_MILLIS = 0x5U,
    /**< 2.116 ms conversion time */
    PMHAL_INA226_CONV_TIME_4P156_MILLIS = 0x6U,
    /**< 4.156 ms conversion time */
    PMHAL_INA226_CONV_TIME_8P244_MILLIS = 0x7U,
    /**< 8.244 ms conversion time */
    PMHAL_INA226_CONV_TIME_MAX = PMHAL_INA226_CONV_TIME_8P244_MILLIS + 1U
                                 /**< Maximum conversion time */
} pmhalIna226ConvTime_t;

/**
 * \brief INA226 ADC average configuration values.
 */
typedef enum pmhalIna226NumAverages
{
    PMHAL_INA226_NUM_AVERAGE_1 = 0x0U,
    /**< Every sample is used. No averaging */
    PMHAL_INA226_NUM_AVERAGE_MIN = PMHAL_INA226_NUM_AVERAGE_1,
    /**< Minimum number of averages */
    PMHAL_INA226_NUM_AVERAGE_4 = 0x1U,
    /**< 4 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_16 = 0x2U,
    /**< 16 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_64 = 0x3U,
    /**< 64 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_128 = 0x4U,
    /**< 128 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_256 = 0x5U,
    /**< 256 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_512 = 0x6U,
    /**< 512 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_1024 = 0x7U,
    /**< 1024 samples are averaged */
    PMHAL_INA226_NUM_AVERAGE_MAX = PMHAL_INA226_NUM_AVERAGE_1024 + 1U
                                   /**< Maximum number of averages */
} pmhalIna226NumAverages_t;

/**
 * \brief   Container for the outputs read from the INA for a given voltage
 *          rail.
 */
typedef struct pmhalIna226OutputData
{
    pmhalPrcmPmicRegulatorId_t voltDomId;
    /**< Voltage Domain for the data. Refer to #pmhalPrcmPmicRegulatorId_t for
     *  valid values.
     */
    uint32_t                   busVoltage;
    /**< Voltage at which the voltage domain is operating. The voltage value
     *  is represented in micro Volts
     */
    uint32_t                   shuntRes;
    /**< Shunt resistance along the given voltage rail */
    int32_t                    shuntVoltage;
    /**< Voltage accross the shunt resistor. The voltage value is in nano Volts
     */
    int32_t                    current;
    /**< Current drawn in micro amperes */
    int32_t                    power;
    /**< Power drawn in micro watts */
} pmhalIna226OutputData_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Program the INA226 Bus Voltage measurement conversion time.
 *
 * \param  voltDomId   Voltage Domain ID for which the value needs
 *                     to be set. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 * \param  convTime    Conversion Time for the given INA on the provided voltage
 *                     rail. Refer #pmhalIna226ConvTime_t for valid values.
 *
 * \return status      PM_SUCCESS When the conversion time is programmed.
 *                     PM_BADARGS When the voltage ID is not valid.
 *                     PM_FAIL    When the conversion time is not programmed.
 */
pmErrCode_t PMHALINA226SetBusVoltConversionTime(
    pmhalPrcmPmicRegulatorId_t voltDomId,
    pmhalIna226ConvTime_t
    convTime);

/**
 * \brief  Program the INA226 Shunt Voltage measurement conversion time.
 *
 * \param  voltDomId   Voltage Domain ID for which the value needs
 *                     to be set. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 * \param  convTime    Conversion Time for the given INA on the provided voltage
 *                     rail. Refer #pmhalIna226ConvTime_t for valid values.
 *
 * \return status      PM_SUCCESS When the conversion time is programmed.
 *                     PM_BADARGS When the voltage ID is not valid.
 *                     PM_FAIL    When the conversion time is not programmed.
 */
pmErrCode_t PMHALINA226SetShuntVoltConversionTime(
    pmhalPrcmPmicRegulatorId_t voltDomId,
    pmhalIna226ConvTime_t
    convTime);

/**
 * \brief  Program the INA226 ADC average number of samples.
 *
 * \param  voltDomId   Voltage Domain ID for which the value needs
 *                     to be set. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 * \param  average     Average number of samples for the given INA on the
 *                     provided voltage rail. Refer #pmhalIna226NumAverages_t
 *                     for valid values.
 *
 * \return status      PM_SUCCESS When the average is programmed.
 *                     PM_BADARGS When the voltage ID is not valid.
 *                     PM_FAIL    When the average is not programmed.
 */
pmErrCode_t PMHALINA226SetAverage(pmhalPrcmPmicRegulatorId_t voltDomId,
                                  pmhalIna226NumAverages_t   average);

/**
 * \brief  Read the INA226 registers to find the voltage and power drawn
 *         for a given voltage domain.
 *
 * \param  voltDomId   Voltage Domain ID for which the data needs
 *                     to be found. Refer #pmhalPrcmPmicRegulatorId_t enum for
 *                     valid values.
 * \param  data        Container for the output data. Refer
 *                     #pmhalIna226OutputData_t for details about each output
 *                     field.
 *
 * \return status      PM_SUCCESS When the output data is read correctly.
 *                     PM_BADARGS When the voltage ID is not valid.
 *                     PM_FAIL    When the output data is not read correctly.
 */
pmErrCode_t PMHALINA226GetData(pmhalPrcmPmicRegulatorId_t voltDomId,
                               pmhalIna226OutputData_t   *data);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


