/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup SBL_TDA3XX_I2C_UTILS TDA3xx SBL I2C Utilities
 *
 *  @{
 */
/**
 *  \file     sbl_utils_tda3xx_i2c.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDA3xx
 *            platform needed for I2C communication.
 */

#ifndef SBL_UTILS_TDA3XX_I2C_H_
#define SBL_UTILS_TDA3XX_I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>

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
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function configures parameters needed for Port write.
 *
 * \param   i2cHandle       I2C Handle.
 *                          Refer structure hsI2cObjHandle
 * \param   i2cInstId       I2C Instance ID.
 * \param   i2cDevAddr      I2C Driver Address.
 * \param   regValue        Registers Values.
 * \param   numRegs         Number registers to be configured.
 *
 * \return  status       Configuration status.
 *                       STW_SOK   : Configuration successful
 *                       STW_EFAIL : Configuration failed
 *
 */
int32_t SBLUtilsWritePortConfig(hsI2cObjHandle i2cHandle,
                                uint32_t       i2cInstId,
                                uint32_t       i2cDevAddr,
                                const uint8_t *regValue,
                                uint32_t       numRegs);

/**
 * \brief   This function writes to output port.
 *
 * \param   i2cHandle       I2C Handle.
 *                          Refer structure hsI2cObjHandle
 * \param   i2cInstId       I2C Instance ID.
 * \param   i2cDevAddr      I2C Driver Address.
 * \param   regValue        Registers Values.
 * \param   numRegs         Number registers to be configured.
 *
 * \return  status       Configuration status.
 *                       STW_SOK   : Configuration successful
 *                       STW_EFAIL : Configuration failed
 *
 */
int32_t SBLUtilsWriteOutputPort(hsI2cObjHandle i2cHandle,
                                uint32_t       i2cInstId,
                                uint32_t       i2cDevAddr,
                                const uint8_t *regValue,
                                uint32_t       numRegs);

/**
 * \brief   This function reads value of output port.
 *
 * \param   i2cHandle       I2C Handle.
 *                          Refer structure hsI2cObjHandle
 * \param   i2cInstId       I2C Instance ID.
 * \param   i2cDevAddr      I2C Driver Address.
 * \param   regValue        Registers Values.
 * \param   numRegs         Number registers to be configured.
 *
 * \return  status       Configuration status.
 *                       STW_SOK   : Configuration successful
 *                       STW_EFAIL : Configuration failed
 *
 */
int32_t SBLUtilsReadOutputPort(hsI2cObjHandle i2cHandle,
                               uint32_t       i2cInstId,
                               uint32_t       i2cDevAddr,
                               uint8_t       *regValue,
                               uint32_t       numRegs);

#ifdef __cplusplus
}

#endif

#endif
/* @} */

