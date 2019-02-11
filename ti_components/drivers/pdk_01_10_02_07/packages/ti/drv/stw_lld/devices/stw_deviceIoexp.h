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
 * @file stw_device_ioexp.h
 *
 *  \brief I2C IO expander interface file supporting TCA64xx (16/24).
 *  This modules define API to configure and use the external IO expanders
 *  like TCA6424, TCA6416. I2C is used to control IO expanders.
 *
 */

#ifndef STW_DEVICE_IOEXP_H_
#define STW_DEVICE_IOEXP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of ports in TCA6424 IO expander. */
#define DEVICE_IOEXP_TCA6424_NUM_PORTS               (3U)

/** \brief Number of ports in TCA6416 IO expander. */
#define DEVICE_IOEXP_TCA6416_NUM_PORTS               (2U)

/** \brief Index for PORT0 register. */
#define DEVICE_IOEXP_TCA64XX_PORT0_OFFSET            (0U)
/** \brief Index for PORT1 register. */
#define DEVICE_IOEXP_TCA64XX_PORT1_OFFSET            (1U)
/** \brief Index for PORT2 register - not applicable for TCA6416. */
#define DEVICE_IOEXP_TCA64XX_PORT2_OFFSET            (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Write the configuration of the TCA6424 IO expander.
 *
 *  The Configuration registers configure the direction of the I/O pins.
 *  If a bit in these registers is set to 1, the corresponding port pin is
 *  enabled as an input with a high-impedance output driver. If a bit in
 *  these registers is cleared to 0, the corresponding port pin is enabled as
 *  an output.
 *
 *  By default all the ports are configured as input. This API should be called
 *  to set the ports as output as per need before calling any other API.
 *
 *  At max TCA6424_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6424WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs);

/**
 *  \brief Write the output port value of the TCA6424 IO expander.
 *
 *  The Output Port registers shows the outgoing logic levels of the pins
 *  defined as outputs by the Configuration registers. Bit values in these
 *  registers have no effect on pins defined as inputs. In turn, reads
 *  from these registers reflect the value that is in the flip-flop controlling
 *  the output selection, NOT the actual pin value.
 *
 *  Each bit of a byte represents the output pins of a port. At max
 *  TCA6424_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6424WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs);

/**
 *  \brief Read the output port value of the TCA6424 IO expander.
 *
 *  The Output Port registers shows the outgoing logic levels of the pins
 *  defined as outputs by the Configuration registers. Bit values in these
 *  registers have no effect on pins defined as inputs. In turn, reads
 *  from these registers reflect the value that is in the flip-flop controlling
 *  the output selection, NOT the actual pin value.
 *
 *  Each bit of a byte represents the output pins of a port. At max
 *  TCA6424_NUM_PORTS registers can be read.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue    [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6424ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs);

/**
 *  \brief Read the input port value of the TCA6424 IO expander.
 *
 *  The Input Port registers reflect the incoming logic levels of the pins,
 *  regardless of whether the pin is defined as an input or an output by the
 *  Configuration register. They act only on read operation. Writes
 *  to these registers have no effect. The default value (X) is determined by
 *  the externally applied logic level.
 *
 *  Each bit of a byte represents the input pins of the port. At max
 *  TCA6424_NUM_PORTS registers can be read.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue    [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6424ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs);

/**
 *  \brief Write the polarity configuration of the TCA6424 IO expander.
 *
 *  The Polarity Inversion registers allow polarity inversion of pins defined
 *  as inputs by the Configuration register. If a bit in these registers is set
 *  (written with 1), the corresponding port pin's polarity is inverted.
 *  If a bit in these registers is cleared (written with a 0), the
 *  corresponding port pin's original polarity is retained
 *
 *  At max TCA6424_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6424WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs);

/**
 *  \brief Write the configuration of the TCA6416 IO expander.
 *
 *  The Configuration registers configure the direction of the I/O pins.
 *  If a bit in these registers is set to 1, the corresponding port pin is
 *  enabled as an input with a high-impedance output driver. If a bit in
 *  these registers is cleared to 0, the corresponding port pin is enabled as
 *  an output.
 *
 *  By default all the ports are configured as input. This API should be called
 *  to set the ports as output as per need before calling any other API.
 *
 *  At max TCA6416_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6416WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs);

/**
 *  \brief Write the output port value of the TCA6416 IO expander.
 *
 *  The Output Port registers shows the outgoing logic levels of the pins
 *  defined as outputs by the Configuration registers. Bit values in these
 *  registers have no effect on pins defined as inputs. In turn, reads
 *  from these registers reflect the value that is in the flip-flop controlling
 *  the output selection, NOT the actual pin value.
 *
 *  Each bit of a byte represents the output pins of a port. At max
 *  TCA6416_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6416WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs);

/**
 *  \brief Read the output port value of the TCA6416 IO expander.
 *
 *  The Output Port registers shows the outgoing logic levels of the pins
 *  defined as outputs by the Configuration registers. Bit values in these
 *  registers have no effect on pins defined as inputs. In turn, reads
 *  from these registers reflect the value that is in the flip-flop controlling
 *  the output selection, NOT the actual pin value.
 *
 *  Each bit of a byte represents the output pins of a port. At max
 *  TCA6416_NUM_PORTS registers can be read.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue    [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6416ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs);

/**
 *  \brief Read the input port value of the TCA6416 IO expander.
 *
 *  The Input Port registers reflect the incoming logic levels of the pins,
 *  regardless of whether the pin is defined as an input or an output by the
 *  Configuration register. They act only on read operation. Writes
 *  to these registers have no effect. The default value (X) is determined by
 *  the externally applied logic level.
 *
 *  Each bit of a byte represents the input pins of the port. At max
 *  TCA6416_NUM_PORTS registers can be read.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue    [OUT] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6416ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs);

/**
 *  \brief Write the polarity configuration of the TCA6416 IO expander.
 *
 *  The Polarity Inversion registers allow polarity inversion of pins defined
 *  as inputs by the Configuration register. If a bit in these registers is set
 *  (written with 1), the corresponding port pin's polarity is inverted.
 *  If a bit in these registers is cleared (written with a 0), the
 *  corresponding port pin's original polarity is retained
 *
 *  At max TCA6416_NUM_PORTS registers can be written.
 *  Make sure size of regValue array is greater or equal to numRegs.
 *
 *  \param i2cInstId    [IN] \ref HSI2C_INST_0 or
 *                           \ref HSI2C_INST_1
 *  \param i2cDevAddr   [IN] Slave device address - 0x22U or 0x23U
 *  \param regValue     [IN] Device Register Value Array
 *  \param numRegs      [IN] Number of registers to write
 *
 *  \return STW_SOK on success else failure.
 */
int32_t DEVICEIoexpTca6416WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_DEVICE_IOEXP_H_ */

/* @} */
