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
 *  \defgroup SBL_DDR_UTILS SBL DDR Configuration Utilities
 *
 *  @{
 */
/**
 *  \file     sbl_utils_ddr_config.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDAxx DDR
 *            configuration. This is taken from gel and follows the Gel coding
 *            guidelines which are different from starterware coding guidelines.
 */

#ifndef SBL_UTILS_DDR_CONFIG_H_
#define SBL_UTILS_DDR_CONFIG_H_

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

/* Macros for DDR type */
#define CFG_MODE_DDR3                                           (0x1000U) /**< DDR type is DDR3 */ 
#define CFG_MODE_DDR2                                           (0x1001U) /**< DDR type is DDR2 */
#define CFG_MODE_LPDDR2                                         (0x1002U) /**< DDR type is LPDDR2 */

/* DMM Registers */
#define SOC_MA_MPU_CONF_REGS_BASE                               (0x482af000U) /**< Base address */
#define LISA_MAP_0                                              (0x40U) /**< LISA MAP 0 */
#define LISA_MAP_1                                              (0x44U) /**< LISA MAP 1 */
#define LISA_MAP_2                                              (0x48U) /**< LISA MAP 2 */
#define LISA_MAP_3                                              (0x4CU) /**< LISA MAP 3 */

/* EMIF Registers */
#define EMIF_PHY_STATUS_7                                       (0x15CU) /**< EMIF register is PHY_STATUS_7 */
#define EMIF_PHY_STATUS_8                                       (0x160U) /**< EMIF register is PHY_STATUS_8 */
#define EMIF_PHY_STATUS_9                                       (0x164U) /**< EMIF register is PHY_STATUS_9 */
#define EMIF_PHY_STATUS_10                                      (0x168U) /**< EMIF register is PHY_STATUS_10 */
#define EMIF_PHY_STATUS_11                                      (0x16CU) /**< EMIF register is PHY_STATUS_11 */
#define EMIF_PHY_STATUS_12                                      (0x170U) /**< EMIF register is PHY_STATUS_12 */
#define EMIF_PHY_STATUS_13                                      (0x174U) /**< EMIF register is PHY_STATUS_13 */
#define EMIF_PHY_STATUS_14                                      (0x178U) /**< EMIF register is PHY_STATUS_14 */
#define EMIF_PHY_STATUS_15                                      (0x17CU) /**< EMIF register is PHY_STATUS_15 */
#define EMIF_PHY_STATUS_16                                      (0x180U) /**< EMIF register is PHY_STATUS_16 */
#define EMIF_PHY_STATUS_17                                      (0x184U) /**< EMIF register is PHY_STATUS_17 */
#define EMIF_PHY_STATUS_18                                      (0x188U) /**< EMIF register is PHY_STATUS_18 */
#define EMIF_PHY_STATUS_19                                      (0x18CU) /**< EMIF register is PHY_STATUS_19 */
#define EMIF_PHY_STATUS_20                                      (0x190U) /**< EMIF register is PHY_STATUS_20 */
#define EMIF_PHY_STATUS_21                                      (0x194U) /**< EMIF register is PHY_STATUS_21 */
#define EMIF_PHY_STATUS_22                                      (0x198U) /**< EMIF register is PHY_STATUS_22 */
#define EMIF_PHY_STATUS_23                                      (0x19CU) /**< EMIF register is PHY_STATUS_23 */
#define EMIF_PHY_STATUS_24                                      (0x1A0U) /**< EMIF register is PHY_STATUS_24 */
#define EMIF_PHY_STATUS_25                                      (0x1A4U) /**< EMIF register is PHY_STATUS_25 */
#define EMIF_PHY_STATUS_26                                      (0x1A8U) /**< EMIF register is PHY_STATUS_26 */
#define EMIF_LPDDR2_MODE_REG_DATA                               (0x40U) /**< EMIF register is LPDDR2_MODE_REG_DATA */
#define EMIF_LPDDR2_MODE_REG_CONFIG                             (0x50U) /**< EMIF register is LPDDR2_MODE_REG_CONFIG */

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
 * \brief   This function does the DDR3 Configuration.
 *
 * \param   ddrSpeed         DDR Speed
 *                           SBLLIB_DDR_SPEED_532MHZ : For 532 MHz
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsDDR3Config(uint32_t ddrSpeed);

/**
 * \brief   This function does the DDR2 Configuration.
 *
 * \param   ddrSpeed         DDR Speed
 *                           SBLLIB_DDR_SPEED_532MHZ : For 532 MHz
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsDDR2Config(uint32_t ddrSpeed);

/**
 * \brief   This function does the LPDDR2 Configuration.
 *
 * \param   lpddr2Speed      LPDDR2 Speed
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsLPDDR2Config(uint32_t lpddr2Speed);

#ifdef __cplusplus
}

#endif

#endif
/* @} */

