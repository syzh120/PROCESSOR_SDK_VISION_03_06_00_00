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
 * @{
 */

/**
 *  \file  pmhal_pmicComm.h
 *
 *  \brief This file contains the BUS Read and Write utility functions to
 *         communicate with the PMIC.
 *
 *         This module abstracts the communication mechanism used to
 *         communicate with the PMIC. Normally, I2C or SPI is used to
 *         communicate with the PMIC.
 *
 */

#ifndef PM_PMICOMM_H_
#define PM_PMICOMM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

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

/* None */

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Configure the I2C port used to control the PMIC
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 *
 * \return status - #PM_PMIC_COMM_TIMEOUT_ERROR if the PMIC
 *                       reset times out.
 *                - #PM_SUCCESS if the reset and configuration happens.
 */
pmErrCode_t PMHALPmicCommConfigure(uint8_t i2cNum);

/**
 * \brief  Read the 8-bit register value at the given register address from
 *         the device at the given slave address.
 *         It is the responsibility of the callee of this API to check for the
 *         returned status before using the value read.
 *
 * \param   i2cNum   The I2C number used on the board to connect to the
 *                   desired PMIC.
 * \param  slaveAddr The slave address of the PMIC regulator
 * \param  regAddr   The register address (offset) to read from
 * \param  value     The 8-bit value read
 *
 * \return status - #PM_SUCCESS if the read is successful.
 *                - Any other error return indicates that the read did
 *                  not go through correctly.
 */
pmErrCode_t PMHALPmicCommReadByte(uint8_t i2cNum,
                                  uint8_t slaveAddr, uint8_t regAddr,
                                  uint8_t *value);

/**
 * \brief  Write the given 8-bit value to the register at the given address.
 *
 * \param   i2cNum   The I2C number used on the board to connect to the
 *                   desired PMIC.
 * \param  slaveAddr The slave address of the PMIC regulator.
 * \param  regAddr   The register address (offset) to write to.
 * \param  value     The 8-bit value to write.
 *
 * \return status  - #PM_SUCCESS if the write is successful.
 *                 - Any other value indicates that the write did not
 *                   go through correctly.
 */
pmErrCode_t PMHALPmicCommWriteByte(uint8_t i2cNum,
                                   uint8_t slaveAddr, uint8_t regAddr,
                                   uint8_t value);

#ifdef __cplusplus
}
#endif

#endif

/* @} */



