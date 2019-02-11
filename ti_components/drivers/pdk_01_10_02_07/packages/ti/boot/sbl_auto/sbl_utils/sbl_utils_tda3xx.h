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
 *  \defgroup SBL_TDA3XX_UTILS TDA3xx SBL Utilities
 *
 *  @{
 */
/**
 *  \file     sbl_utils_tda3xx.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDA3xx
 *            platform. This also contains some related macros, structures and
 *            enums.
 */

#ifndef SBL_UTILS_TDA3XX_H_
#define SBL_UTILS_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/csl_crc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Below macros contain device IDs that can be selected for TDA3xx */
#define SBL_UTILS_DEVICE_ID_MMC4               ((uint32_t) 0x00000000U) /**< SBL_UTILS_DEVICE_ID_MMC4 */
#define SBL_UTILS_DEVICE_ID_EMAC0PHY           ((uint32_t) 0x00000001U) /**< SBL_UTILS_DEVICE_ID_EMAC0PHY */
#define SBL_UTILS_DEVICE_ID_UART1              ((uint32_t) 0x00000002U) /**< SBL_UTILS_DEVICE_ID_UART1 */
#define SBL_UTILS_DEVICE_ID_UART2              ((uint32_t) 0x00000003U) /**< SBL_UTILS_DEVICE_ID_UART2 */

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
 * \brief   This function wakes up IPU1 Core1. Core1 is held in WFE by RBL.
 *          To wakeup core1 SEV instruction is sent from master core.
 *
 * \param   startAddr       Address at which Core1 starts executing.
 *
 * \return  None.
 */
void SBLUtilsWakeUpIPU1Core1(uint32_t startAddr);

/**
 * \brief   This function enables the IPU1's Uni-cache.
 *
 * \return  None.
 */
void SBLUtilsEnableIPU1Unicache(void);

/**
 * \brief   This function computes the CRC of TESOC ROM used for IPU TESOC
 *          tests.
 *
 * \param   crcSignVal      CRC Signature value.
 *
 * \return  status          CRC signature calculation status.
 *                          STW_SOK   : Signature is calculated successfully
 *                          STW_EFAIL : Failed to calculate signature
 */
int32_t SBLUtilsComputeIPUTesocROMCRC(crcSignature_t *crcSignVal);

/**
 * \brief   This function computes the CRC of the given data.
 *
 * \param   crcSrcAddr   Source Address of data for which CRC is calculated.
 * \param   crcDataSize  CRC Data Size.
 * \param   crcSignVal   CRC Signature value.
 *
 * \return  status       CRC signature calculation status.
 *                       STW_SOK   : Signature is calculated successfully
 *                       STW_EFAIL : Failed to calculate signature
 *
 * \note    This API does not initialize and de-initialize the EDMA. This
 *          should be taken care by caller.
 */
int32_t SBLUtilsComputeCRC(const void     *crcSrcAddr,
                           uint32_t        crcDataSize,
                           crcSignature_t *crcSignVal);

/**
 * \brief   This function does the IPU1's default AMMU Configuration.
 *
 * \return  None.
 */
void SBLUtilsConfigIPU1DefaultAMMU(void);

/**
 * \brief   This function evicts the IPU1's Uni-cache.
 *
 * \return  None.
 */
void SBLUtilsEvictIPU1Unicache(void);

/**
 * \brief   This function disables the IPU1's Uni-cache.
 *
 * \return  None.
 */
void SBLUtilsDisableIPU1Unicache(void);

/**
 * \brief   This function invalidates the IPU1's Uni-cache.
 *
 * \return  None.
 */
void SBLUtilsInvalidateIPU1Unicache(void);

/**
 * \brief   This function disable the AMMU configuration for large pages that
 *          was done by SBL.
 *
 * \return  None.
 */
void SBLUtilsDisableIPU1AMMU(void);

/**
 * \brief   This function configures the source for DSP and EVE clocks
 *          based on the package type and opp.
 *
 * \param   oppId       Index giving the choice of Operating point.
 * \param   siliconPackageType
                        Parameter indicates if this is a 15x15 or a 12x12
 *                      package.
 *
 * \return  status       Multiplexer configuration status.
 *                       STW_SOK   : Multiplexer configured successfully
 *                       STW_EFAIL : Failed to configure multiplexer
 *
 */
int32_t SBLUtilsConfigureDspEveMux(uint32_t oppId,
                                   uint32_t siliconPackageType);

/**
 * \brief   This function configures the mux for given device.
 *
 * \param   deviceId     Device to be configured
 *                       Supported devices for TDA3xx:
 *                       SBL_UTILS_DEVICE_ID_MMC4
 *                       SBL_UTILS_DEVICE_ID_EMAC0PHY
 *                       SBL_UTILS_DEVICE_ID_UART1
 *                       SBL_UTILS_DEVICE_ID_UART2
 *
 * \return  status       Device Config status.
 *                       STW_SOK   : Device configured successfully
 *                       STW_EFAIL : Failed to configure device
 */
int32_t SBLUtilsConfigDevice(uint32_t deviceId);

#ifdef __cplusplus
}

#endif

#endif
/* @} */

