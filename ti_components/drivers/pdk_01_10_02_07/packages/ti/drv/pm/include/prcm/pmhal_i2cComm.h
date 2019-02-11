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
 *  \addtogroup MISC Infrastructure and Domain List
 *
 *  -   I2C Comm Provides APIs to register I2C handlers with PMHAL.
 * @{
 */

/**
 *  \file  pmhal_i2cComm.h
 *
 *  \brief This file contains the structure and APIs to register I2C handlers
 *         with PMHAL.
 *
 *         This module abstracts the I2C communication mechanism used to
 *         communicate with the PMIC and INA226.
 *
 */

#ifndef PM_I2CCOMM_H_
#define PM_I2CCOMM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

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

/** \brief Structure to hold the I2C functions for read and write and initialize
 */
typedef struct pmhalI2cCommOperations
{
    int32_t (*pmhalI2cCommInit)(void);
    /**< I2C initialization function */
    int32_t (*pmhalI2cCommRead8)(uint32_t i2cInstId, uint32_t i2cDevAddr,
                                 const uint8_t *regAddr,
                                 uint8_t *regValue,
                                 uint32_t numRegs);
    /**< I2C Read function to read the value of a device register of 8 bits */
    int32_t (*pmhalI2cCommWrite8)(uint32_t i2cInstId, uint32_t i2cDevAddr,
                                  const uint8_t *regAddr,
                                  const uint8_t *regValue,
                                  uint32_t numRegs);
    /**< I2C Write function to write a value to a device register of 8 bits */
    int32_t (*pmhalI2cCommRead16)(uint32_t i2cInstId, uint32_t i2cDevAddr,
                                  const uint8_t *regAddr,
                                  uint16_t *regValue,
                                  uint32_t numRegs);
    /**< I2C Read function to read a value from a device register of 8 bits
     *   and data 16 bits */
    int32_t (*pmhalI2cCommWrite16)(uint32_t i2cInstId, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   const uint16_t *regValue,
                                   uint32_t numRegs);
    /**< I2C Write function to write a value of to device register of 8 bits
     *   and data of 16 bits */
} pmhalI2cCommOperations_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/**
 * Pointer to the PMIC I2C functions. This should be populated with pointers to
 * the I2C driver being used.
 */
extern const pmhalI2cCommOperations_t *gPmhalI2cFunc;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   API to register the I2C initialization, read and write functions
 *          with the PMIC and INA226 communication HAL.
 *
 * \param   i2cfunc      The structure containing function pointers to the I2C
 *                       initialization, read and write functions. Refer
 *                       #pmhalI2cCommOperations_t for structure details
 *
 * \return  status       PM_SUCCESS - If the I2C functions are registered
 *                                    correctly.
 *                       PM_FAIL    - If the I2C functions are not
 *                                    registered correctly.
 */
pmErrCode_t PMHALI2CCommRegister(const pmhalI2cCommOperations_t *i2cfunc);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


