/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file   main_tda2xx.c
 *
 *  \brief  INA226 power measurement example.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/prcm/pmhal_i2cComm.h>
#include <ti/drv/pm/include/prcm/pmhal_ina226.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include "app_utils.h"


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*Pad config constant values */
#define PULLUDENABLE_ENABLE         (0U)
#define PULLUDENABLE_DISABLE        (1U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (0U)
#define SLEWCONTROL_SLOW_SLEW       (1U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

int32_t INA226_I2CInitialize(void);
int32_t INA226_I2CRead16(uint32_t i2cInstId, uint32_t i2cDevAddr,
                         const uint8_t *regAddr,
                         uint16_t *regValue,
                         uint32_t numRegs);
int32_t INA226_I2CWrite16(uint32_t i2cInstId, uint32_t i2cDevAddr,
                          const uint8_t *regAddr,
                          const uint16_t *regValue,
                          uint32_t numRegs);

static void I2C3SetPinMux();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

hsI2cHandle i2cHandle = NULL;
static const pmhalI2cCommOperations_t gIna226I2cFunc =
{
    &INA226_I2CInitialize,
    NULL,
    NULL,
    &INA226_I2CRead16,
    &INA226_I2CWrite16
};

/**
 * Voltage rail names
 */
const char *pmhalRegulator_names[] =
{
    "VD_MPU    ",
    "VD_CORE   ",
    "VD_IVA    ",
    "VD_DSPEVE ",
    "VD_GPU    ",
    "VD_MMC13V3",
    "VD_SHV5   ",
    "VD_1V8PHY ",
    "VD_1V8PLL "
};
int32_t     gTestStatus = PM_SUCCESS;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    pmhalPrcmPmicRegulatorId_t regId;
    pmErrCode_t status = PM_SUCCESS;
    pmhalIna226OutputData_t    opData;
    int64_t totalcurrent, totolpower;

    AppUtils_defaultInit();
    AppUtils_printf("\r\nPM INA226 Power Measurement Test Application\r\n");

    /* Register the I2C functions with the PMHAL I2C Communication to ensure the
     * INA226 can be accessed by I2C drivers.
     */
    PMHALI2CCommRegister(&gIna226I2cFunc);

    /* Use the I2C3 for accessing INA registers */
    I2C3SetPinMux();
    for (regId = PMHAL_PRCM_PMIC_REGULATOR_MIN;
         regId < PMHAL_PRCM_PMIC_REGULATOR_COUNT;
         regId = (pmhalPrcmPmicRegulatorId_t) ((int32_t) regId + 1))
    {
        /* 8.244 ms and 1024 averages is the best combination for lowest
         * noise.
         */
        status += (int32_t) PMHALINA226SetBusVoltConversionTime(
            regId, PMHAL_INA226_CONV_TIME_8P244_MILLIS);
        status += (int32_t) PMHALINA226SetShuntVoltConversionTime(
            regId, PMHAL_INA226_CONV_TIME_8P244_MILLIS);
        status += (int32_t) PMHALINA226SetAverage(regId,
                                                  PMHAL_INA226_NUM_AVERAGE_1024);
    }
    if (PM_SUCCESS == status)
    {
        AppUtils_printf(
            "============================================================================\r\n");
        AppUtils_printf(
            "Name      | Bus (mV) | Res (mOhm) | Shunt (uV)  | Current (mA)\t| Power (mW)\r\n");
        AppUtils_printf(
            "----------------------------------------------------------------------------\r\n");
        totolpower   = (int64_t) 0;
        totalcurrent = (int64_t) 0;
        for (regId = PMHAL_PRCM_PMIC_REGULATOR_MIN;
             regId < PMHAL_PRCM_PMIC_REGULATOR_COUNT;
             regId = (pmhalPrcmPmicRegulatorId_t) ((int32_t) regId + 1))
        {
            status = PMHALINA226GetData(regId, &opData);
            if (PM_SUCCESS == status)
            {
                char busVolt[256], shuntVolt[256], current[256], power[256],
                     resistance[256];
                int  integerValue, decimal;
                integerValue = (int32_t) opData.busVoltage / 1000;
                decimal      = ((int32_t) opData.busVoltage % 1000);
                sprintf(busVolt, "%d.%03d", integerValue, decimal);

                integerValue = (int32_t) opData.shuntVoltage / 1000;
                decimal      = ((int32_t) opData.shuntVoltage % 1000);
                if (decimal < 0)
                {
                    decimal = -1 * decimal;
                }
                sprintf(shuntVolt, "%d.%03d", integerValue, decimal);

                integerValue = (int32_t) opData.current / 1000;
                decimal      = ((int32_t) opData.current % 1000);
                if (decimal < 0)
                {
                    decimal = -1 * decimal;
                }
                sprintf(current, "%02d.%03d", integerValue, decimal);

                integerValue = (int32_t) opData.power / 1000;
                decimal      = (int32_t) (opData.power % 1000);
                if (decimal < 0)
                {
                    decimal = -1 * decimal;
                }
                sprintf(power, "%d.%03d", integerValue, decimal);

                integerValue = (int32_t) opData.shuntRes;
                sprintf(resistance, "%02d", integerValue);

                AppUtils_printf(
                    "%s| %s | %s         | %s\t| %s\t| %s\r\n",
                    pmhalRegulator_names[regId],
                    busVolt, resistance, shuntVolt, current, power);
                AppUtils_printf(
                    "----------------------------------------------------------------------------\r\n");
                totalcurrent += (int64_t) opData.current;
                totolpower   += (int64_t) opData.power;
            }
            else
            {
                AppUtils_printf("\r\nReading the regulator data failed\r\n");
                gTestStatus = PM_FAIL;
            }
        }
        if (PM_SUCCESS == status)
        {
            char current[256], power[256];
            int  integerValue, decimal;
            integerValue = (int32_t) totalcurrent / 1000;
            decimal      = ((int32_t) totalcurrent % 1000);
            sprintf(current, "%d.%03d", integerValue, decimal);

            integerValue = (int32_t) totolpower / 1000U;
            decimal      = (int32_t) (totolpower % 1000U);
            sprintf(power, "%d.%03d", integerValue, decimal);

            AppUtils_printf(
                "Total     |                                     | %s\t| %s\r\n",
                current, power);
            AppUtils_printf(
                "============================================================================\r\n");
            AppUtils_printf("\r\nPM INA226 Power Read Successfully !!\r\n");
        }
        else
        {
            AppUtils_printf("\r\nPM INA226 Power Read Failed !!\r\n");
            gTestStatus = PM_FAIL;
        }
    }

    if (gTestStatus == PM_SUCCESS)
    {
        AppUtils_printf("\r\nPM INA226 Power Measurement Test Pass");
    }
    else
    {
        AppUtils_printf("\r\nPM INA226 Power Measurement Test Fail");
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
/* This function set the pin mux for I2C3 for tda2xx evm */
static void I2C3SetPinMux()
{
    uint32_t reg_val;

    /* unlock MMR5 space for region 0x1400 to 0x1FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK);

    /* I2C3_SDA */
    reg_val = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPIO6_14);

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_MASK;
    reg_val |= (uint32_t) PULLUDENABLE_ENABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_MASK;
    reg_val |= (uint32_t) PULLTYPESELECT_PULL_UP <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_MASK;
    reg_val |= (uint32_t) INPUTENABLE_ENABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_MASK;
    reg_val |= (uint32_t) SLEWCONTROL_FAST_SLEW <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_MASK;
    reg_val |= (uint32_t) WAKEUPENABLE_DISABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_SHIFT;

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + (CTRL_CORE_PAD_GPIO6_14), reg_val);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */
    reg_val &= ~((uint32_t) CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_MASK);
    reg_val |= (uint32_t) 9 <<
               CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_SHIFT;

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPIO6_14, reg_val);


    /* I2C3_SCL */
    reg_val = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPIO6_15);

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_MASK;
    reg_val |= (uint32_t) PULLUDENABLE_ENABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_MASK;
    reg_val |= (uint32_t) PULLTYPESELECT_PULL_UP <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_MASK;
    reg_val |= (uint32_t) INPUTENABLE_ENABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_MASK;
    reg_val |= (uint32_t) SLEWCONTROL_FAST_SLEW <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_SHIFT;

    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_MASK;
    reg_val |= (uint32_t) WAKEUPENABLE_DISABLE <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_SHIFT;

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + (CTRL_CORE_PAD_GPIO6_15), reg_val);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */
    reg_val &= ~((uint32_t) CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_MASK);
    reg_val |= (uint32_t) 9 <<
               CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_SHIFT;

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPIO6_15, reg_val);

    /* Lock MMR5 space for region 0x1400 to 0x1FFF */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_MMR_LOCK_5,
        CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOLOCK);
}

int32_t INA226_I2CInitialize(void)
{
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
    int32_t status = (int32_t) PM_SUCCESS;

    initPar.i2cBusFreq   = I2C_NORMAL;
    initPar.opMode       = HSI2C_OPMODE_POLLED;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;
    lld_i2c_init(&i2cObjHandle, HSI2C_INST_2, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST_2, NULL, NULL);

    if (NULL == i2cHandle)
    {
        status      = (int32_t) PM_FAIL;
        gTestStatus = PM_FAIL;
    }
    return status;
}

int32_t INA226_I2CRead16(uint32_t i2cInstId, uint32_t i2cDevAddr,
                         const uint8_t *regAddr,
                         uint16_t *regValue,
                         uint32_t numRegs)
{
    int32_t  retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint8_t  buffer[2];

    retVal = lld_i2c_probe(i2cHandle, i2cDevAddr);

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.timeout   = 0x1000;
        for (regId = 0; regId < numRegs; regId++)
        {
            i2cParams.bufLen = 1;
            i2cParams.buffer = (uint8_t *) buffer;
            buffer[0]        = regAddr[regId] & 0xFFU;
            /* While reading the INA registers one must first perform a full
             * I2C write to the INA register to change the register pointer
             * address */
            i2cParams.flags
                = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_STOP |
                   LLD_HSI2C_START);
            retVal = lld_i2c_transfer(i2cHandle, &i2cParams);
            /* Once the write is successful read the 2 8 bit values.
             * The first value is MSB and the second is LSB.
             */
            if (retVal == LLD_HSI2C_SUCCESS)
            {
                i2cParams.buffer = (uint8_t *) &buffer[0];
                i2cParams.bufLen = 2;
                i2cParams.flags
                    = (LLD_HSI2C_READ | LLD_HSI2C_MASTER | LLD_HSI2C_START |
                       LLD_HSI2C_STOP |
                       LLD_HSI2C_IGNORE_BUS_BUSY);
                retVal = lld_i2c_transfer(i2cHandle, &i2cParams);

                if (retVal != LLD_HSI2C_SUCCESS)
                {
                    AppUtils_printf("\r\nPM INA226 read register failed\r\n");
                    gTestStatus = PM_FAIL;
                    break;
                }
                else
                {
                    /* Join the two values to make a single 16 bit value */
                    regValue[regId] = (((uint16_t) buffer[1]) & 0x00FFU) |
                                      ((uint16_t) (((uint16_t) buffer[0]) <<
                                                   8) & 0xFF00U);
                }
            }
            else
            {
                AppUtils_printf("\r\nPM INA226 read register failed\r\n");
                gTestStatus = PM_FAIL;
            }
        }
    }
    else
    {
        AppUtils_printf("\r\nPM INA226 probe failed\r\n");
        gTestStatus = PM_FAIL;
    }
    return retVal;
}

int32_t INA226_I2CWrite16(uint32_t i2cInstId, uint32_t i2cDevAddr,
                          const uint8_t *regAddr,
                          const uint16_t *regValue,
                          uint32_t numRegs)
{
    int32_t  retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint8_t  buffer[4];
    uint32_t bufVal;

    retVal = lld_i2c_probe(i2cHandle, i2cDevAddr);

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0x1000;

        for (regId = 0; regId < numRegs; regId++)
        {
            /* For the write make the register address as the first byte and
             * the next two bytes would be the data to be written.
             */
            i2cParams.buffer = buffer;
            bufVal           = ((uint32_t) regAddr[regId] & 0xFFU);
            buffer[0]        = (uint8_t) (bufVal);
            buffer[1]        = regValue[regId] >> 8;
            bufVal           = ((uint32_t) regValue[regId] & 0xFFU);
            buffer[2]        = (uint8_t) (bufVal);
            i2cParams.bufLen = 3;
            retVal           = lld_i2c_transfer(i2cHandle, &i2cParams);
            if (retVal != LLD_HSI2C_SUCCESS)
            {
                AppUtils_printf("\r\nPM INA226 write register failed\r\n");
                gTestStatus = PM_FAIL;
                break;
            }
        }
    }
    else
    {
        AppUtils_printf("PM INA226 probe failed\r\n");
        gTestStatus = PM_FAIL;
    }
    return retVal;
}

