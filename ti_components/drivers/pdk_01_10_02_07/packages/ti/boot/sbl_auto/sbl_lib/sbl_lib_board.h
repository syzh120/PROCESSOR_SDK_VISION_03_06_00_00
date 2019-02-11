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
 *  \defgroup SBL_BOARD_LIB SBL Board Lib
 *
 *  @{
 */
/**
 *  \file     sbl_lib_board.h
 *
 *  \brief    This file contains the board related interfaces like pin mux APIs,
 *            etc. present in the Secondary Bootloader(SBL) Library.
 *            This also contains some related macros, structures and enums.
 */

#ifndef SBL_LIB_BOARD_H_
#define SBL_LIB_BOARD_H_

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

/**
 * \brief  Enum to select the Silicon Package Type of SoC.
 */
typedef enum sbllibSiliconPackageType
{
    SBLLIB_SILICON_PACKAGE_TYPE_UNKNOWN = 0,
    /**< Silicon Package type is Unknown */
    SBLLIB_SILICON_PACKAGE_TYPE_12X12 = 1,
    /**< Silicon Package type is 12x12 */
    SBLLIB_SILICON_PACKAGE_TYPE_15X15 = 2,
    /**< Silicon Package type is 15x15 */
    SBLLIB_SILICON_PACKAGE_TYPE_17X17 = 3,
    /**< Silicon Package type is 17x17 */
    SBLLIB_SILICON_PACKAGE_TYPE_23X23 = 4,
    /**< Silicon Package type is 23x23 */
    SBLLIB_SILICON_PACKAGE_TYPE_23X23_HPP = 5
    /**< Silicon Package type is 23x23 (High Performance Package)
     *   Applicable only for the TDA2Px package. */
} sbllibSiliconPackageType_t;

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
 * \brief   This function gets the silicon package type of the SoC.
 *
 * \return  packageType   Refer enum #sbllibSiliconPackageType_t for values.
 */
uint32_t SBLLibGetSiliconPackageType(void);

/**
 * \brief   This function gets the silicon revision of the SoC.
 *
 * \return  siliconRev    For TDA2xx
 *                        0: Silicon Rev 1.0
 *                        1: Silicon Rev 1.1
 *                        2: Silicon Rev 2.0
 *                        For TDA2Ex
 *                        0: Silicon Rev 1.0
 *                        1: Silicon Rev 2.0
 *                        For TDA3xx
 *                        0: Silicon Rev 1.0
 *                        1: Silicon Rev 1.0A
 *                        2: Silicon Rev 2.0
 */
uint32_t SBLLibGetSiliconRev(void);

/**
 * \brief   This function configures UART Pin Mux.
 *
 * \param   uartInstance  UART Instance.
 *                        Refer enum UART_INST_t for values.
 *
 * \return  None
 */
void SBLLibConfigureUARTPinMux(UART_INST_t uartInstance);

/**
 * \brief   This function configures pin mux for QSPI.
 *
 * \return  None
 */
void SBLLibQSPISetPinMux(void);

/**
 * \brief   This function configures pin mux for GPMC.
 *
 * \return  None
 */
void SBLLibGPMCSetPinMux(void);

/**
 * \brief   This function configures pin mux for RGMII.
 *
 * \return  None
 */
void SBLLibRGMIISetPinMux(void);

/**
 * \brief   This function configures MMC Pin Mux.
 *
 * \param   mmcInstance  MMC Instance.
 *                       Refer enum MMC_INST_t for values.
 *
 * \return  None
 */
void SBLLibMMCSDSetPinMux(MMC_INST_t mmcInstance);

/**
 * \brief   This function locks the control module MMRs.
 *
 * \return  None
 */
void SBLLibLockControlModuleMMR(void);

/**
 * \brief   This function unlocks the control module MMRs.
 *
 * \return  None
 */
void SBLLibUnlockControlModuleMMR(void);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/**
 * \brief   This function unlocks the control module registers for DSS.
 *
 * \return  None
 */
void SBLLibUnlockControlIODSS(void);

/**
 * \brief   This function configures pin mux for I2C3.
 *
 * \return  None
 */
void SBLLibI2C3SetPinMux(void);

/**
 * \brief   This function configures pin mux for I2C4.
 *
 * \return  None
 */
void SBLLibI2C4SetPinMux(void);

/**
 * \brief   This function configures pin mux for I2C5.
 *
 * \return  None
 */
void SBLLibI2C5SetPinMux(void);

/**
 * \brief   This function configures pin mux for Monster Cam.
 *
 * \return  None
 */
void SBLLibTDA2xxMCSetPinMux(void);

/**
 * \brief   This function provides the FT revision value.
 *
 * \return  FT Revision.
 */
uint32_t SBLLibGetFtRev(void);
#endif

#ifdef __cplusplus
}

#endif

#endif
/* @} */
