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
 * \file    pmhal_ina226.c
 *
 * \brief   This file contains the API to program and read the INA226 power
 *          measurement ICs.
 *          In order to read the INA's on board from the target please ensure
 *          necessary board modifications have been done to read the INA
 *          registers via I2C.
 *
 *          Example:
 *          For the TDA2xx board, make the following changes to the TI EVM
 *          Change the select for RU113 multiplexer on the board by making
 *          R264 = 10k & R265 = NO-POP. This allows DCAN2 Signalling.
 *          Then perform a blue wiring for the following connections:
 *          1. DCAN2_TX (JP3 pin 1) to PM_I2C_SDA (J8 pin 2)
 *          2. DCAN2_RX (JP3 pin 2) to PM_I2C_SCL (J8 pin 1)
 *          Configure the PAD configuration registers such that the gpio6_14
 *          and gpio6_15 pads operate as I2C3_SDA and I2C3_SCL respectively.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_i2cComm.h"
#include "pmhal_ina226.h"
#include "hw_pmhal_common_ina226data.h"
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None  */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API calls the I2C initialization function. If the
 *          initialization is complete the API exits with a pass with out
 *          calling the initialization multiple times.
 *
 * \param   i2cNum          I2C number to which the INA is connected.
 *
 * \retval  Status          Status of the API call. Can be any of the following,
 *          PM_SUCCESS       Indicates the operation is success
 *          PM_FAIL          Indicates the API failed for desired functionality
 */
static pmErrCode_t PmhalIna226CommConfigure(uint8_t i2cNum);

/**
 * \brief   This API calls the I2C read function to read the value of the 16 bit
 *          register at the given register base address.
 *
 * \param   i2cNum          I2C number to which the INA is connected.
 * \param   slaveAddr       I2C address using which the INA is read.
 * \param   regAddr         Register address to read.
 * \param   value           Stores the 16 bit value read from the INA register.
 *
 * \retval  Status          Status of the API call. Can be any of the following,
 *          PM_SUCCESS       Indicates the operation is success
 *          PM_FAIL          Indicates the API failed to read the register.
 */
static pmErrCode_t PmhalIna226Read16(uint8_t   i2cNum,
                                     uint8_t   slaveAddr,
                                     uint8_t   regAddr,
                                     uint16_t *value);

/**
 * \brief   This API calls the I2C write function to write a 16 bit value to an
 *          INA register at the given register base address.
 *
 * \param   i2cNum          I2C number to which the INA is connected.
 * \param   slaveAddr       I2C address using which the INA is write.
 * \param   regAddr         Register address to write.
 * \param   value           Stores the 16 bit value to be written to the INA.
 *
 * \retval  Status          Status of the API call. Can be any of the following,
 *          PM_SUCCESS       Indicates the operation is success
 *          PM_FAIL          Indicates the API failed to write to the register.
 */
static pmErrCode_t PmhalIna226Write16(uint8_t  i2cNum,
                                      uint8_t  slaveAddr,
                                      uint8_t  regAddr,
                                      uint16_t value);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALINA226SetBusVoltConversionTime(
    pmhalPrcmPmicRegulatorId_t voltDomId,
    pmhalIna226ConvTime_t
    convTime)
{
    pmErrCode_t status = PM_SUCCESS;
    uint16_t    regVal = 0U, checkVal = 0U;
    uint8_t     slaveAddr;
    if ((voltDomId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (convTime >= PMHAL_INA226_CONV_TIME_MAX))
    {
        status = PM_BADARGS;
    }
    if (PM_SUCCESS == status)
    {
        /* Configure the I2C IPs for communication if not already done */
        status = PmhalIna226CommConfigure(PMHAL_INA226_HSI2C_INST_NUMBER);
    }
    if (PM_SUCCESS == status)
    {
        /* Get the SoC specific I2C address for the voltage rail given */
        slaveAddr = PmhalIna226GetI2cAddress(voltDomId);
        /* Read the default configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* If the read is successful, modify the VBUS conversion time of the
         * INA ADC.
         */
        HW_WR_FIELD32(&regVal, PMHAL_INA226_CONFIGURATION_VBUS_CT, convTime);
        /* Write back the modified register to the INA */
        status = PmhalIna226Write16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* Read the configured configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &checkVal);
        if (checkVal != regVal)
        {
            status = PM_FAIL;
        }
    }
    return status;
}

pmErrCode_t PMHALINA226SetShuntVoltConversionTime(
    pmhalPrcmPmicRegulatorId_t voltDomId,
    pmhalIna226ConvTime_t
    convTime)
{
    pmErrCode_t status = PM_SUCCESS;
    uint16_t    regVal = 0U, checkVal = 0U;
    uint8_t     slaveAddr;
    if ((voltDomId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (convTime >= PMHAL_INA226_CONV_TIME_MAX))
    {
        status = PM_BADARGS;
    }
    if (PM_SUCCESS == status)
    {
        /* Configure the I2C IPs for communication if not already done */
        status = PmhalIna226CommConfigure(PMHAL_INA226_HSI2C_INST_NUMBER);
    }
    if (PM_SUCCESS == status)
    {
        /* Get the SoC specific I2C address for the voltage rail given */
        slaveAddr = PmhalIna226GetI2cAddress(voltDomId);
        /* Read the default configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* If the read is successful, modify the VSHUNT conversion time of the
         * INA ADC.
         */
        HW_WR_FIELD32(&regVal, PMHAL_INA226_CONFIGURATION_VSHUNT_CT, convTime);
        status = PmhalIna226Write16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* Read the configured configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &checkVal);
        if (checkVal != regVal)
        {
            status = PM_FAIL;
        }
    }
    return status;
}

pmErrCode_t PMHALINA226SetAverage(pmhalPrcmPmicRegulatorId_t voltDomId,
                                  pmhalIna226NumAverages_t   average)
{
    pmErrCode_t status = PM_SUCCESS;
    uint16_t    regVal = 0U, checkVal = 0U;
    uint8_t     slaveAddr;
    if ((voltDomId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (average >= PMHAL_INA226_NUM_AVERAGE_MAX))
    {
        status = PM_BADARGS;
    }
    if (PM_SUCCESS == status)
    {
        /* Configure the I2C IPs for communication if not already done */
        status = PmhalIna226CommConfigure(PMHAL_INA226_HSI2C_INST_NUMBER);
    }
    if (PM_SUCCESS == status)
    {
        /* Get the SoC specific I2C address for the voltage rail given */
        slaveAddr = PmhalIna226GetI2cAddress(voltDomId);
        /* Read the default configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* If the read is successful, modify the number of averages of the
         * INA ADC.
         */
        HW_WR_FIELD32(&regVal, PMHAL_INA226_CONFIGURATION_AVG, average);
        status = PmhalIna226Write16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            regVal);
    }
    if (PM_SUCCESS == status)
    {
        /* Read the configured configuration register value */
        status = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t)
            PMHAL_INA226_CONFIGURATION_REGISTER,
            &checkVal);
        if (checkVal != regVal)
        {
            status = PM_FAIL;
        }
    }
    return status;
}

pmErrCode_t PMHALINA226GetData(pmhalPrcmPmicRegulatorId_t voltDomId,
                               pmhalIna226OutputData_t   *data)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     slaveAddr;
    uint32_t    shuntRes;
    uint16_t    shuntRegVal, busRegVal;
    int32_t     shuntVoltage, current, busVolt;
    int32_t     power;
    uint16_t    tempU16;
    if ((voltDomId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (NULL == data))
    {
        status = PM_BADARGS;
    }
    if (PM_SUCCESS == status)
    {
        /* Configure the I2C IPs for communication if not already done */
        status = PmhalIna226CommConfigure(PMHAL_INA226_HSI2C_INST_NUMBER);
    }
    if (PM_SUCCESS == status)
    {
        /* Get the SoC specific I2C address for the voltage rail given */
        slaveAddr = PmhalIna226GetI2cAddress(voltDomId);
        status    = PmhalIna226Read16((uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
                                      slaveAddr,
                                      (uint8_t) PMHAL_INA226_SHUNT_VOLTAGE,
                                      &shuntRegVal);
    }
    if (PM_SUCCESS == status)
    {
        /* Test if the shunt voltage is negative */
        if ((shuntRegVal & (uint16_t) 0x8000) == (uint16_t) 0x8000)
        {
            /* Find the two's complement of the number and save this to
             * shunt voltage.
             */
            shuntRegVal  = shuntRegVal - (uint16_t) 1;
            tempU16      = ((uint16_t) (~shuntRegVal) & (uint16_t) 0xFFFF);
            shuntVoltage = ((-((int32_t) 1)) * (int32_t) tempU16);
        }
        else
        {
            shuntVoltage = (int32_t) shuntRegVal;
        }
        /* Convert to actual voltage value */
        shuntVoltage = PMHAL_INA226_SHUNT_NANOV_PER_LSB * shuntVoltage;
        status       = PmhalIna226Read16(
            (uint8_t) PMHAL_INA226_HSI2C_INST_NUMBER,
            slaveAddr,
            (uint8_t) PMHAL_INA226_BUS_VOLTAGE,
            &busRegVal);
    }
    if (PM_SUCCESS == status)
    {
        tempU16 = (busRegVal & (uint16_t) 0xFFFF);
        /* Convert to actual voltage value */
        busVolt = PMHAL_INA226_BUS_MICROV_PER_LSB * (int32_t) tempU16;
        /* Using Ohm's law calculate the power and current */
        shuntRes = PmhalIna226GetShuntRes(voltDomId);
        current  = shuntVoltage / (int32_t) shuntRes;
        /* Find power from bus voltage x current */
        power = (int32_t) (((int64_t) current * (int64_t) busVolt) /
                           (int64_t) 1000000);

        data->voltDomId    = voltDomId;
        data->busVoltage   = busVolt;
        data->shuntVoltage = shuntVoltage;
        data->current      = current;
        data->power        = power;
        data->shuntRes     = shuntRes;
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PmhalIna226CommConfigure(uint8_t i2cNum)
{
    pmErrCode_t     status        = PM_SUCCESS;
    static uint32_t configureDone = 0U;
    int32_t         retval        = 0;
    /* Only one time configuration */
    if (0U == configureDone)
    {
        if (gPmhalI2cFunc->pmhalI2cCommInit != NULL)
        {
            /* This is the driver specific I2C initialization */
            retval = gPmhalI2cFunc->pmhalI2cCommInit();
            if (0 == retval)
            {
                status        = PM_SUCCESS;
                configureDone = 1U;
            }
            else
            {
                status = PM_FAIL;
            }
        }
    }
    return status;
}

static pmErrCode_t PmhalIna226Read16(uint8_t   i2cNum,
                                     uint8_t   slaveAddr,
                                     uint8_t   regAddr,
                                     uint16_t *value)
{
    pmErrCode_t status = PM_SUCCESS;
    int32_t     retval = 0;
    uint8_t     dataArr[1U];

    /* Populate the data to an array */
    dataArr[0U] = regAddr;
    /* This is the driver specific read implementation */
    if (gPmhalI2cFunc->pmhalI2cCommRead16 != NULL)
    {
        retval = gPmhalI2cFunc->pmhalI2cCommRead16((uint32_t) i2cNum,
                                                   (uint32_t) slaveAddr,
                                                   (const uint8_t *) dataArr,
                                                   value, 1U);
        if (0 == retval)
        {
            status = PM_SUCCESS;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_FAIL;
    }
    return status;
}

static pmErrCode_t PmhalIna226Write16(uint8_t  i2cNum,
                                      uint8_t  slaveAddr,
                                      uint8_t  regAddr,
                                      uint16_t value)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     dataAddr[1];
    uint16_t    dataValue[1];
    int32_t     retval = 0;

    /* Populate the data to an array */
    dataAddr[0]  = regAddr;
    dataValue[0] = value;
    if (gPmhalI2cFunc->pmhalI2cCommWrite16 != NULL)
    {
        retval = gPmhalI2cFunc->pmhalI2cCommWrite16(
            i2cNum, slaveAddr,
            (const uint8_t *) dataAddr,
            dataValue, 1U);
        if (0 == retval)
        {
            status = PM_SUCCESS;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_FAIL;
    }
    return status;
}

