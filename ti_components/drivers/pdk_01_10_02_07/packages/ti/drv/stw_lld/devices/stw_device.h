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
 * @file stw_device.h
 *
 *  \brief External Video Device API
 *
 */

#ifndef STW_DEVICE_H_
#define STW_DEVICE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name Device IDs for different devices
 *
 *  Used to identify the devices.
 *
 */

/** @{ */
/** \brief Invalid device ID. */
#define DEVICE_ID_INVALID               (0xFFFFFFFFU)

/**
 *  \brief Device ID.
 */
typedef enum
{
    DEVICE_ID_EEPROM = 0x0000U,
    /**< EEPROM device ID */
    DEVICE_ID_TMP102,
    /**< TMP102 Temperature sensor device ID */
    DEVICE_ID_PMIC,
    /**< PMIC device ID */
    DEVICE_ID_QSPI,
    /**< QSPI Flash device ID */
    DEVICE_ID_UART,
    /**< UART  device ID */
    DEVICE_ID_GPIO,
    /**< GPIO device ID */
    DEVICE_ID_LCD,
    /**< LCD device ID */
    DEVICE_ID_SD_CARD,
    /**< SD_CARD device ID */
    DEVICE_ID_NOR,
    /**< NOR flash device ID */
    DEVICE_ID_MCASP,
    /**< McASP device ID */
    DEVICE_ID_MCSPI,
    /**< MCSPI  device ID */
    DEVICE_ID_MAILBOX,
    /**< MAILBOX device ID */
    DEVICE_ID_OV1063X,
    /**< ov1063x OV sensor device ID */
    DEVICE_ID_I2C,
    /**< I2c device ID */
    DEVICE_ID_NORFLASH,
    /**< Nor Flash device ID */
    DEVICE_ID_MMC,
    /**< MMC device ID */
    DEVICE_ID_EMAC0PHY,
    /**< EMAC0PHY device ID */
    DEVICE_ID_MAX
    /**< Max device ID. */
} deviceId_t;

/**
 *  \brief Device Module ID.
 */
typedef enum
{
    DEVICE_MODULE_ID_VIP = 0x0000U,
    /**< VIP Module device ID */
    DEVICE_MODULE_ID_DCTRL,
    /**< VIP Module device ID */
    DEVICE_MODULE_ID_MAX
    /**< Max device ID. */
} deviceModuleId_t;

/**
 *  \name DSS DPI1 Module Instance ID
 *
 */
/** \brief DSS DISPC OVLY DPI1 Instance 0. */
#define DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0   ((uint32_t) 0x0U)
/** \brief DSS DISPC OVLY DPI1 Instance 1. */
#define DEVICE_MODULE_DSS_DISPC_OVLY_DPI3_INST_ID_1   ((uint32_t) 0x1U)

/**
 *  \name VIP Module instance ID
 *
 */
/** \brief VIP instance 0. */
#define DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0   ((uint32_t) 0x0U)
/** \brief VIP instance 1. */
#define DEVICE_MODULE_VIP1_S0_PORTB_INST_ID_0   ((uint32_t) 0x1U)
/** \brief VIP instance 2. */
#define DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0   ((uint32_t) 0x2U)
/** \brief VIP instance 3. */
#define DEVICE_MODULE_VIP1_S1_PORTB_INST_ID_0   ((uint32_t) 0x3U)

/**
 *  \name LCD instance ID
 *
 */
/** \brief LCD instance 0. */
#define DEVICE_LCD_INST_ID_0   ((uint32_t) 0x0U)
/** \brief LCD instance 1. */
#define DEVICE_LCD_INST_ID_1   ((uint32_t) 0x1U)

/**
 *  \name EEPROM instance ID
 *
 */
/** \brief EEPROM instance 0. */
#define DEVICE_EEPROM_INST_ID_0   ((uint32_t) 0x0U)

/**
 *  \name TEMP Sensor instance ID
 *
 */
/** \brief TEMP Sensor instance 0. */
#define DEVICE_TEMP_SENSOR_INST_ID_0   ((uint32_t) 0x0U)

/**
 *  \name I2c instance ID
 *
 */
/** \brief I2c instance 0. */
#define DEVICE_I2C_INST_ID_0   ((uint32_t) 0x0U)
/** \brief I2c instance 1. */
#define DEVICE_I2C_INST_ID_1   ((uint32_t) 0x1U)
/** \brief I2c instance 2. */
#define DEVICE_I2C_INST_ID_2   ((uint32_t) 0x2U)
/** \brief I2c instance 3. */
#define DEVICE_I2C_INST_ID_3   ((uint32_t) 0x3U)
/** \brief I2c instance 4. */
#define DEVICE_I2C_INST_ID_4   ((uint32_t) 0x4U)

/**
 *  \name OV1063X Sensor instance ID
 *
 */
/** \brief OV1063X Sensor instance 0. */
#define DEVICE_OV1063X_INST_ID_0   ((uint32_t) 0x0U)
/** \brief OV1063X Sensor instance 1. */
#define DEVICE_OV1063X_INST_ID_1   ((uint32_t) 0x1U)

/**
 *  \name UART instance ID
 *
 */
/** \brief UART instance 1. */
#define DEVICE_UART_INST_ID_1     ((uint32_t) 0x1U)
/** \brief UART instance 2. */
#define DEVICE_UART_INST_ID_2     ((uint32_t) 0x2U)
/** \brief UART instance 1. */
#define DEVICE_UART_INST_ID_3     ((uint32_t) 0x3U)

/**
 *  \name MCSPI instance ID
 *
 */
/** \brief MCSPI instance 1. */
#define DEVICE_MCSPI_INST_ID_1     ((uint32_t) 0x1U)
/** \brief MCSPI instance 2. */
#define DEVICE_MCSPI_INST_ID_2     ((uint32_t) 0x2U)
/** \brief MCSPI instance 3. */
#define DEVICE_MCSPI_INST_ID_3     ((uint32_t) 0x3U)
/** \brief MCSPI instance 4. */
#define DEVICE_MCSPI_INST_ID_4     ((uint32_t) 0x4U)

/**
 *  \name NOR FLASH instance ID
 *
 */
/** \brief NOR FLASH instance 0. */
#define DEVICE_NORFLASH_INST_ID_0 ((uint32_t) 0x0U)

/**
 *  \name MMC instance ID
 *
 */
/** \brief MMC instance 4. */
#define DEVICE_MMC_INST_ID_2     ((uint32_t) 0x2U)
#define DEVICE_MMC_INST_ID_4     ((uint32_t) 0x4U)

/**
 *  \name EMAC0PHY instance ID
 *
 */
/** \brief EMAC0PHY instance 0. */
#define DEVICE_EMAC0PHY_INST_ID_0     ((uint32_t) 0x0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief External video device sub-system init parameters
 */
typedef struct deviceInitParams
{
    uint32_t         isI2cInitReq;
    /**< Indicates whether I2C initialization is required. */
    uint32_t         isI2cProbingReq;
    /**< If this is TRUE, THE INIT will try to probe all the I2C
     *   devices connected on a specific I2C bus. This should be FALSE for
     *   all production system/build since this is a time consuming function.
     *   For debugging this should be kept TRUE to probe all on-board I2C
     *   devices.
     *   This field is dont care if #isI2cInitReq is FALSE. */
    lld_hsi2c_opMode i2cOpMode;
    /**< I2C Driver operating mode - polled ,interrupt or DMA.
     * For valid values see lld_hsi2c_opMode */
} deviceInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Probes an I2C bus for all video devices.
 *
 *  Probes an I2C bus for all possibly connected slaves to it.
 *  Prints the detected slave address on the console.
 *
 *  \param i2cInstId    I2C instance number
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
LLD_hsi2cErrorCode_t DEVICEI2cProbeAll(uint32_t i2cInstId);

/**
 *  \brief Probes an I2C bus for a specific device slave address.
 *
 *  \param i2cInstId    I2C instance number
 *  \param slaveAddr    Slave I2C address
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
LLD_hsi2cErrorCode_t DEVICEI2cProbeDevice(uint32_t i2cInstId,
                                          uint8_t  slaveAddr);

/**
 *  \brief Initialize external video device subsystem.
 *
 *  - This API initializes data structures, resources and I2C subsystem needed
 *    to use the external video devices.
 *
 *  \param pPrm         [IN] Pointer to init parameters.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t DEVICEInit(const deviceInitParams_t *pPrm);

/**
 *  \brief De-Initialize external video device subsystem.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t DEVICEDeInit(void *args);

/**
 *  \brief Read registers from device via I2C.
 *
 *  Make sure size of regAddr[] array and regValue[] array is
 *  greater than euqal to numRegs.
 *
 *  The value that gets read from the device is, <br>
 *  For regAddr[x], value read would be regValue[x]
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *                           (regAddr[x] = 0 .. 0xFF)
 *  \param regValue     [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to read (<= sizeof regAddr[])
 *
 *  \return STW_SOK on success else failure.
 */
LLD_hsi2cErrorCode_t DEVICEI2cRead8(uint32_t       i2cInstId,
                                    uint32_t       i2cDevAddr,
                                    const uint8_t *regAddr,
                                    uint8_t       *regValue,
                                    uint32_t       numRegs);

/**
 *  \brief Raw Read from device via I2C.
 *
 *  Make sure regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regValue     [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of Registers to read
 *
 *  \return STW_SOK on success else failure.
 */
LLD_hsi2cErrorCode_t DEVICEI2cRawRead8(uint32_t i2cInstId,
                                       uint32_t i2cDevAddr,
                                       uint8_t *regValue,
                                       uint32_t numRegs);

/**
 *  \brief Write registers to device via I2C.
 *
 *  Make sure size of regAddr array and regValue array is
 *  greater or equal to numRegs.
 *
 *  The value that gets written to the device is
 *
 *  For regAddr[x], value would be regValue[x]
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regAddr      [IN] Device Register Address Array
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
LLD_hsi2cErrorCode_t DEVICEI2cWrite8(uint32_t       i2cInstId,
                                     uint32_t       i2cDevAddr,
                                     const uint8_t *regAddr,
                                     const uint8_t *regValue,
                                     uint32_t       numRegs);

/**
 *  \brief Raw Write to device via I2C.
 *
 *  Make sure size of regValue array is
 *  greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address (0 .. 0xFF)
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
LLD_hsi2cErrorCode_t DEVICEI2cRawWrite8(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs);

/**
 *  \brief Enable I2C debug prints.
 *
 *  \param enable       [IN] Enable/disable I2C debug prints
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEI2cDebugEnable(uint32_t enable);

/**
 *  \brief deviceInitParams_t structure init function.
 *
 *  \param initPrms     [IN] Pointer to #deviceInitParams_t structure.
 *
 */
static inline void DEVICEInitParams_init(deviceInitParams_t *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void DEVICEInitParams_init(deviceInitParams_t *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isI2cInitReq    = (uint32_t) TRUE;
        initPrms->isI2cProbingReq = (uint32_t) FALSE;
        initPrms->i2cOpMode       = HSI2C_OPMODE_POLLED;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_DEVICE_H_ */

/* @} */
