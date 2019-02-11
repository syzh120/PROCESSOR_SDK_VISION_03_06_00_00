/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_UB960_API APIs to initialize and de-initialize UB960 EVM
 *  @{
 */

/**
 *  \file bsputils_ub960.h
 *
 *  \brief Defines APIs to initialize, de-initialize UB960 EVM, address aliases
 *          & reset sensors.
 *
 *  TODO: Get serializer address function should be common for all modules.
 *          Right now, its seperate for TIDA, SAT0088 & IMI modules
 */

#ifndef BSPUTILS_UB960_H_
#define BSPUTILS_UB960_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_TDA3XX)
    #ifdef BOARD_TYPE_TDA3XX_RVP
        #define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_0)
        /**< Identify the I2C instance through which UB960 is accessible */

        #define UB960_SLAVE_ADDR       (0x32)
        /**< 7 bit UB960 slave address */

        #define KTCA9539_I2CADDR_BASEBOARD          (0x74U)
        /**< RVP Base Board I2C address */
    #else
        #define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_1)
        /**< Identify the I2C instance through which UB960 is accessible */

        #define UB960_SLAVE_ADDR       (0x3D)
        /**< 7 bit UB960 slave address */
    #endif
#elif defined (SOC_TDA2EX) || defined (SOC_AM571x)

    #define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_4)
    /**< Identify the I2C instance through which UB960 is accessible */

    #define UB960_SLAVE_ADDR       (0x3D)
    /**< 7 bit UB960 slave address */

#elif defined (SOC_TDA2PX)

    #define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_4)
    /**< Identify the I2C instance through which UB960 is accessible */

    #define UB960_SLAVE_ADDR       (0x3d)
    /**< 7 bit UB960 slave address */

#else

    #define UB960_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_0)
    /**< Identify the I2C instance through which UB960 is accessible */

    #define UB960_SLAVE_ADDR       (0x00)
    /**< 7 bit UB960 slave address */

#endif

/**
 * Specify the address that should be associated with TIDA00262. TIDA00262
 *  consists of 913 serializer and AR0140 sensor. Specify the address for both
 *  Address is in 7bit format.
 */
#define TIDA00262_PORT_0_SER_ADDR       (0x74U)
/**< Serializer address */
#define TIDA00262_PORT_0_SENSOR_ADDR    (0x40U)
/**< Sensor address */
#define TIDA00262_PORT_1_SER_ADDR       (0x76U)
/**< Serializer address */
#define TIDA00262_PORT_1_SENSOR_ADDR    (0x42U)
/**< Sensor address */
#define TIDA00262_PORT_2_SER_ADDR       (0x78U)
/**< Serializer address */
#define TIDA00262_PORT_2_SENSOR_ADDR    (0x44U)
/**< Sensor address */
#define TIDA00262_PORT_3_SER_ADDR       (0x7AU)
/**< Serializer address */
#define TIDA00262_PORT_3_SENSOR_ADDR    (0x46U)
/**< Sensor address */


#define MARS_PORT_0_SER_ADDR       (0x74U)
/**< Serializer address */
#define MARS_PORT_0_SENSOR_ADDR    (0x40U)
/**< Sensor address */
#define MARS_PORT_1_SER_ADDR       (0x76U)
/**< Serializer address */
#define MARS_PORT_1_SENSOR_ADDR    (0x42U)
/**< Sensor address */
#define MARS_PORT_2_SER_ADDR       (0x78U)
/**< Serializer address */
#define MARS_PORT_2_SENSOR_ADDR    (0x44U)
/**< Sensor address */
#define MARS_PORT_3_SER_ADDR       (0x7AU)
/**< Serializer address */
#define MARS_PORT_3_SENSOR_ADDR    (0x46U)
/**< Sensor address */


#define TIDA1130_OV2775_SER_ADDR                    (0x18U)
/**< Serializer address */
#define TIDA1130_OV2775_SENSOR_ADDR                 (0x36U)
/**< Sensor address */

#define TIDA1130_OV2775_PORT_0_SER_ALIAS_ADDR       (0x74U)
/**< Serializer Alias address */
#define TIDA1130_OV2775_PORT_0_SENSOR_ALIAS_ADDR    (0x40U)
/**< Sensor Alias address */
#define TIDA1130_OV2775_PORT_1_SER_ALIAS_ADDR       (0x76U)
/**< Serializer Alias address */
#define TIDA1130_OV2775_PORT_1_SENSOR_ALIAS_ADDR    (0x42U)
/**< Sensor Alias address */
#define TIDA1130_OV2775_PORT_2_SER_ALIAS_ADDR       (0x78U)
/**< Serializer Alias address */
#define TIDA1130_OV2775_PORT_2_SENSOR_ALIAS_ADDR    (0x44U)
/**< Sensor Alias address */
#define TIDA1130_OV2775_PORT_3_SER_ALIAS_ADDR       (0x7AU)
/**< Serializer Alias address */
#define TIDA1130_OV2775_PORT_3_SENSOR_ALIAS_ADDR    (0x46U)
/**< Sensor Alias address */

/**
 * Specify the address that should be associated with SAT0088 & OV10635.
 * SAT0088 & OV10635 consists of 913 serializer and OV10635 sensor.
 * Specify the address for both addresses is in 7bit format.
 */
#define SAT0088_OV10635_SER_ADDR                    (0x58U) /* 0xB0/2 */
/**< 7 Bit serailizer address */
#define SAT0088_OV10635_SENSOR_ADDR                 (0x30U) /* 0x60/2 */
/**< 7 Bit sensor address */

#define SAT0088_OV10635_PORT_0_SER_ALIAS_ADDR       (0x74U)
/**< Serializer address */
#define SAT0088_OV10635_PORT_0_SENSOR_ALIAS_ADDR    (0x38U) /* 0x70/2 */
/**< Sensor address */
#define SAT0088_OV10635_PORT_1_SER_ALIAS_ADDR       (0x76U)
/**< Serializer address */
#define SAT0088_OV10635_PORT_1_SENSOR_ALIAS_ADDR    (0x39U) /* 0x72/2 */
/**< Sensor address */
#define SAT0088_OV10635_PORT_2_SER_ALIAS_ADDR       (0x78U)
/**< Serializer address */
#define SAT0088_OV10635_PORT_2_SENSOR_ALIAS_ADDR    (0x3AU) /* 0x74/2 */
/**< Sensor address */
#define SAT0088_OV10635_PORT_3_SER_ALIAS_ADDR       (0x7AU)
/**< Serializer address */
#define SAT0088_OV10635_PORT_3_SENSOR_ALIAS_ADDR    (0x3BU) /* 0x76/2 */
/**< Sensor address */

#define IMI_PORT_0_SER_ADDR             (0x74U)
/**< Serializer address */
#define IMI_PORT_1_SER_ADDR             (0x76U)
/**< Serializer address */
#define IMI_PORT_2_SER_ADDR             (0x78U)
/**< Serializer address */
#define IMI_PORT_3_SER_ADDR             (0x7AU)
/**< Serializer address */

#define IMI_PORT_0_SENSOR_ADDR          (0x40U)
/**< Sensor address */
#define IMI_PORT_1_SENSOR_ADDR          (0x42U)
/**< Sensor address */
#define IMI_PORT_2_SENSOR_ADDR          (0x44U)
/**< Sensor address */
#define IMI_PORT_3_SENSOR_ADDR          (0x46U)
/**< Sensor address */

/**
 * Specify the address that should be associated with D3 Satellite Radar module.
 * D3 Satellite Radar module consists of 953 serializer and AR1243 Radar sensor.
 * Specify the address for both addresses is in 7bit format.
 */
#define D3_AR1243_PORT_0_SER_ADDR       (0x74U)
/**< Serializer address */
#define D3_AR1243_PORT_1_SER_ADDR       (0x76U)
/**< Serializer address */
#define D3_AR1243_PORT_2_SER_ADDR       (0x78U)
/**< Serializer address */
#define D3_AR1243_PORT_3_SER_ADDR       (0x7AU)
/**< Serializer address */

#define D3_AR1243_PORT_0_SENSOR_ADDR    (0x40U)
/**< Sensor address */
#define D3_AR1243_PORT_1_SENSOR_ADDR    (0x42U)
/**< Sensor address */
#define D3_AR1243_PORT_2_SENSOR_ADDR    (0x44U)
/**< Sensor address */
#define D3_AR1243_PORT_3_SENSOR_ADDR    (0x46U)
/**< Sensor address */

/** GPIO Addresses on D3 Radar Interface Board */
#define D3RIB_PORT_0_IOEXP_ADDR    (0x48U)
/**< IO EXP address */
#define D3RIB_PORT_1_IOEXP_ADDR    (0x50U)
/**< IO EXP address */
#define D3RIB_PORT_2_IOEXP_ADDR    (0x52U)
/**< IO EXP address */
#define D3RIB_PORT_3_IOEXP_ADDR    (0x54U)
/**< IO EXP address */

#define D3_AR1243_FUSION_PORT_ID        (0x1U)
/**< Deserializer port number connected to Radar for Fusion usage */
#define D3_AR1243_FUSION_SENSOR_ADDR    D3_AR1243_PORT_1_SENSOR_ADDR
/**< Radar sensor address for Fusion usage */

/**
 * @{
 * Generic Alias Addresses for serialisers attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SER_ADDR       (0x74U)
#define D3IMX390_UB960_PORT_1_SER_ADDR       (0x76U)
#define D3IMX390_UB960_PORT_2_SER_ADDR       (0x78U)
#define D3IMX390_UB960_PORT_3_SER_ADDR       (0x7AU)
 /** @} */

/**
 * @{
 * Generic Alias Addresses for sensors attached to the UB960
 */
#define D3IMX390_UB960_PORT_0_SENSOR_ADDR    (0x40U)
#define D3IMX390_UB960_PORT_1_SENSOR_ADDR    (0x42U)
#define D3IMX390_UB960_PORT_2_SENSOR_ADDR    (0x44U)
#define D3IMX390_UB960_PORT_3_SENSOR_ADDR    (0x46U)
 /** @} */

#define BSPUTILS_UB960EVM_MAX_PORTS     (0x4U)
/**< Number of receive ports supported */

#define BSPUTILS_UB960_MAX_INSTANCE     (0x2U)
/**< Number of maximum csi2 instances supported */

#define BSPUTILS_UB960EVM_NO_SOURCE_DETECTED     (0xFFFFFFFFU)
/**< Identifier to indicate no source detected at a given port */

#define BSPUTILS_UB964_VERSION_ID       (0x34U)
/**< UB964 identifier, contents of register 0xF5 */

/**< set of debug registers
* increment the max number of
* reg macro in case of any addition to the list */

#define BSPUTILS_UB960_DEVICE_STS       (0x04)
/**< UB96x debug device status register */
#define BSPUTILS_UB960_GPIO_STS         (0x0E)
/**< UB96x debug GPIO status register */
#define BSPUTILS_UB960_INTERRUPT_STS_ADDR     (0x24)
/**< UB96x debug interrupt status register */
#define BSPUTILS_UB960_TS_STATUS              (0x29)
/**< UB96x debug TS status register */
#define BSPUTILS_UB960_CSI_CTL                (0x33)
/**< UB96x debug CSI CTL status register */
#define BSPUTILS_UB960_CSI_CTL2               (0x34)
/**< UB96x debug CSI CTL2 status register */
#define BSPUTILS_UB960_CSI_STS_ADDR           (0x35)
/**< UB96x debug CSI status register */
#define BSPUTILS_UB960_CSI_TX_ISR             (0x37)
/**< UB96x debug CSI TX status register */
#define BSPUTILS_UB960_RX_PORT_STS1           (0x4D)
/**< UB96x debug RX Port 1 status register */
#define BSPUTILS_UB960_RX_PORT_STS2           (0x4E)
/**< UB96x debug RX Port 2 status register */
#define BSPUTILS_UB960_RX_FREQ_HIGH           (0x4F)
/**< UB96x debug High Freq status register */
#define BSPUTILS_UB960_RX_FREQ_LOW            (0x50)
/**< UB96x debug Low Freq status register */
#define BSPUTILS_UB960_RX_PAR_ERR_HI          (0x55)
/**< UB96x debug RX Par Err Hi status register */
#define BSPUTILS_UB960_RX_PAR_ERR_LO          (0x56)
/**< UB96x debug RX Par Err Lo status register */
#define BSPUTILS_UB960_BIST_ERR_COUNT         (0x57)
/**< UB96x debug Bist Err count register */
#define BSPUTILS_UB960_LINE_COUNT_1           (0x73)
/**< UB96x debug Line count 1 register */
#define BSPUTILS_UB960_LINE_COUNT_0           (0x74)
/**< UB96x debug Line count 0 register */
#define BSPUTILS_UB960_LINE_LEN_1             (0x75)
/**< UB96x debug Line 1 register */
#define BSPUTILS_UB960_LINE_LEN_0             (0x76)
/**< UB96x debug Line 0 register */
#define BSPUTILS_UB960_CSI_RX_STS             (0x7A)
/**< UB96x debug CSI RX status register */
#define BSPUTILS_UB960_CSI_ERR_COUNTER        (0x7B)
/**< UB96x debug CSI ERR counter register */
#define BSPUTILS_UB960_PORT_CONFIG2           (0x7C)
/**< UB96x debug PORT Config2 register */
#define BSPUTILS_UB960_MODE_IDX_STS           (0xB8)
/**< UB96x debug Mode Idx Status register */
#define BSPUTILS_UB960_PORT_ISR_HI            (0xDA)
/**< UB96x debug Port ISR HI register */
#define BSPUTILS_UB960_PORT_ISR_LO            (0xDB)
/**< UB96x debug Port ISR LO register */
#define BSPUTILS_UB960_AEQ_STATUS             (0xD3)
/**< UB96x debug AEQ status register */
#define BSPUTILS_UB960_FPD3_RX_ID5            (0xF5)
/**< UB96x version identifier */

#define BSPUTILS_UB960_MAX_NUM_DEBUG_REG      (27U)
/**< UB96x Maximum debug register */
/* ========================================================================== */
/*                         Enum Declarations                                  */
/* ========================================================================== */

/**
 *  \brief FPD Power level setting.
 */
typedef enum
{
    BSPUTILS_FPDCAMPOWERLEVEL_OFF = 0x0001U,
    BSPUTILS_FPDCAMPOWERLEVEL_5V5 = 0x0002U,
    BSPUTILS_FPDCAMPOWERLEVEL_12V0 = 0x0003U

}BspUtils_FpdCamPowerLevel;

/**
 *  \brief UB960/964/954 Back Channel Frequency Selection
 */
typedef enum
{
    BSPUTILS_BACKCHFREQSELECT_2P5MHZ    = 0x0U,
    BSPUTILS_BACKCHFREQSELECT_10MHZ     = 0x4U,
    BSPUTILS_BACKCHFREQSELECT_25MHZ     = 0x5U,
    BSPUTILS_BACKCHFREQSELECT_50MHZ     = 0x6U,
    BSPUTILS_BACKCHFREQSELECT_100MHZ    = 0x7U
}BspUtils_BackChFreqSelect;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Struct to hold reg addr and value returned.
 *         Initialized the ub96x with default value of reg to be read
 */
typedef struct
{
    UInt8 regAddr;
    /**< Register Addreess which is to be read */
    UInt8 regValue;
    /**< Place holder to store read Reg Val */
}BspUtils_Ub960Debugdata;

/**
 *  \brief Debug Status reg of UB960 initialization.
 *         Initialized the ub96x with default value of reg to be read
 */
typedef struct
{
    UInt32 numofReg;
    /**< Specifies the number of registers to be read */
    BspUtils_Ub960Debugdata ub96xdebugData[BSPUTILS_UB960_MAX_NUM_DEBUG_REG];
    /**< Structure with reg value and reg name */
} BspUtils_Ub960DebugRegData;



/**
 *  \brief Status of UB960 initialization.
 *          When numDetected > 0, indicates UB960 EVM is initialized.
 *          When numDetected == 0, indicates UB960 EVM did not detect any
 *              sources. Please check the I2C addresses in case a source was
 *              connected but not detected.
 */
typedef struct
{
    UInt32 numDetected;
    /**< Specifies the number of sensor/modules connected to UB960 detected */
    UInt32 portNum[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Source detected at ports, range 0 & < BSPUTILS_UB960EVM_MAX_PORTS and
     *      BSPUTILS_UB960EVM_NO_SOURCE_DETECTED in cases no sources detected */
} BspUtils_Ub960Status;

/**
 *  \brief Configure I2C address of the sources
 *          When numDetected > 0, indicates UB960 EVM is initialized.
 *          When numDetected == 0, indicates UB960 EVM did not detect any
 *              sources. Please check the I2C addresses in case a source was
 *              connected but not detected.
 */
typedef struct
{
    UInt32 slaveAddr;
    /**< Specify the 7bit UB960 slave address */
    UInt32 numSource;
    /**< Specify the number of sensor/modules connected to UB960 */
    UInt32 rSlave1Addr[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Designate the 7 bit slave address for first slave.
     *      In cases where TIDA00262 is connected, this holds serializer slave
     *      address */
    UInt32 rSlave2Addr[BSPUTILS_UB960EVM_MAX_PORTS];
    /**< Designate the 7 bit slave address for second slave.
     *      In cases where TIDA00262 is connected, this holds sensor slave
     *      address */
} BspUtils_Ub960SourceI2cAddr;

/**
 *  \brief UB960 Register address and value pair, with delay.
 */
typedef struct
{
    UInt8 nRegAddr;
    /**< Register Address */
    UInt8 nRegValue;
    /**< Slave Address */
    UInt32 nDelay;
    /**< Delay to be applied, after the register is programmed */
} BspUtils_Ub960I2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes the UB960 EVM. Sets up the SLAVE aliases and configures
 *          CSI2 transmit port for transmission. Please note that source
 *          connected to UB960 would require configuration to0.
 *          Supports following source to be connected.
 *          1. TIDA00262
 *
 *  \param instId      [IN]      Instance of UB960 EVM. Ignored for now.
 *  \param sensorDrvId [IN]      Sensor driver ID
 *  \param pSlaveAddr  [IN]      I2C slave address
 *  \param pStatus     [IN/OUT]  Returns the number of sources detected.
 */
Int32 BspUtils_appInitUb960(UInt32 instId,
                            UInt32 sensorDrvId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            BspUtils_Ub960Status *pStatus);

/**
 *  \brief De Initializes the UB960 EVM. Stops transmission on the CSI2
 *          interface.
 *
 *  \param instId       [IN]  Instance of UB960 EVM. Ignored for now.
 *  \param sensorDrvId  [IN]  Sensor driver ID
 */
Int32 BspUtils_appDeInitUb960(UInt32 instId, UInt32 sensorDrvId);

/**
 *  \brief Initializes the serializer of TIDA00262 in RAW12 mode.
 *  \warning Ensure the pixel clock of AR0140 is at 72 MHz. This is requirement
 *              of the serializer.
 *
 *  \param instId   [IN]  Specify the instance id of ub913
 *  \param portId   [IN]  Identify the instance of TIDA that requires to be
 *                        initialized.
 *  \param i2cPrms  [IN]  Specify the register values to program
 *  \param numRegs  [IN]  Specify the number of register to program
 */
Int32 BspUtils_appInitUB913Ser(UInt32 instId, UInt32 portId, BspUtils_Ub960I2cParams* i2cPrms,UInt32 numRegs);

/**
 *  \brief Resets the sensor and stops transmission.
 *
 *  \param instId       [IN]  Specify the instance id of ub913
 *  \param portId       [IN]  Identify the instance of TIDA that requires to be
 *                              de initialized.
 *  \param sensorDrvId  [IN]  Specify the sensor driver id
 */
Int32 BspUtils_appDeInitUB913Ser(UInt32 instId, UInt32 portId, UInt32 sensorDrvId);

/**
 *  \brief Returns the I2C slave address of the TIDA serailizer.
 *
 *  \param instId [IN]  Identify the instance of TIDA that requires to be
 *                          de initialized.
 */
UInt32 BspUtils_getSerAddrTida00262(UInt32 instId);

/**
 *  \brief Returns the I2C slave address of the IMI serailizer.
 *
 *  \param instId [IN]  Identify the instance of IMI that requires to be
 *                          de initialized.
 */
UInt32 BspUtils_getSerAddrIMI(UInt32 instId);

/**
 *  \brief Update the slave addresses for the UB960
 *
 *  \param instId [IN]  Identify the instance of IMI that requires to be
 *                      de initialized.
 *  \param pSlaveAddr  [IN]      I2C slave address
 */
Int32 BspUtils_updateSlaveAddrUb960(UInt32 instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr);

/**
 *  \brief Returns the I2C slave address of the SAT0088 serailizer.
 *
 *  \param instId [IN]  Identify the instance of SAT0088.
 */
UInt32 BspUtils_getSerAddrSat0088(UInt32 instId);

/**
 *  \brief Returns the version number from UB96x (register 0xF5)
 *
 *  \param instId [IN]  Identify the instance of ub96x.
 */
Uint8 BspUtils_appGetUb96xVersion(UInt32 instId);

/**
 *  \brief Returns the Reg Val from UB96x
 *
 *  \param instId       [IN]  Instance of UB960 EVM. Ignored for now.
 *  \param sensorDrvId  [IN]  Sensor driver ID
 *  \param pSlaveAddr   [IN]  I2C slave address (Not used for now)
 *  \param pDebugStatus [IN]  Struct cointaining reg addr to be read and
 *                            place holder for value
 */
Int32 BspUtils_getDebugRegVal(UInt32 instId,
                                UInt32 sensorDrvId,
                                const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                BspUtils_Ub960DebugRegData *pDebugStatus);

/**
 *  \brief Enables FSIN generation on UB960 for 30fps
 *
 *  \param instId      [IN]      Instance of UB960 EVM. Ignored for now.
 *  \param sensorDrvId [IN]      Sensor driver ID
 *  \param pSlaveAddr  [IN]      I2C slave address (Not used for now)
 *  \param pStatus     [IN/OUT]  Unused.
 */
Int32 BspUtils_appUb960EnableFsin(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  const BspUtils_Ub960Status *pStatus);

/**
 *  \brief Initialized the UB960 Deserializer for Satellite radar module
 *
 *  \param sensorDrvId [IN]      Sensor driver ID
 *  \param numSensors [IN]       Number of Sensors connected
 *
 *  \return BSP_SOK upon success or return error
 */
Int32 BspUtils_appUb960InitAR12xx(UInt32 sensorDrvId, UInt32 numSensors);

/**
 *  \brief De-initialize the AR12xx FPD radar module
 *
 *  \return BSP_SOK upon success or return error
 */
Int32 BspUtils_appUb960DeInitAR12xx(void);

/**
 *  \brief Boots up the AR12xx FPD radar module
 *
 *  \param port [IN]      Deserializer port number
 *
 *  \return BSP_SOK upon success or return error
 */
Int32 BspUtils_appUb960BootAR12xx(UInt8 port);

/**
 *  \brief Enables CSI output on the UB960
 *
 *  \return BSP_SOK upon success or return error
 */
Int32 BspUtils_enableUb960CsiOutput(void);

/**
 *  \brief Disables CSI output on the UB960
 *
 *  \return BSP_SOK upon success or return error
 */
Int32 BspUtils_disableUb960CsiOutput(void);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_UB960_H_ */

/* @} */
