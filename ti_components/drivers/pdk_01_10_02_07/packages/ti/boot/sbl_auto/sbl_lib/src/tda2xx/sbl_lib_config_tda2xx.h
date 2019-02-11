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
 *  \file     sbl_lib_config_tda2xx.h
 *
 *  \brief    This file contains compile time configurable parameters of
 *            TDA2xx SBL. This is not applicable for TDA2Ex devices.
 *            This can be used to port SBL to custom use case.
 */

#ifndef SBL_LIB_CONFIG_TDA2XX_H_
#define SBL_LIB_CONFIG_TDA2XX_H_

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

#if defined (SBL_CONFIG_DISABLE_SAFETY_FEATURES)

/* Active EMIF configuration - can be also set via make argument EMIFMODE */
#ifndef TDA2XX_EMIF_MODE
#define TDA2XX_EMIF_MODE                        (SBLLIB_SINGLE_EMIF_512MB)
#endif

/* DDR Speed - only 532MHz is supported */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)

/* Enable ECC on EMIF */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0U)

/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)

/* EMIF ECC start address for region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1     (0x0U)

/* EMIF ECC end address for region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1       (0x0U)

/* Define the range type of region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE (EMIF_ECC_ADDR_RANGE_WITHIN)

/* EMIF ECC start address for region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2     (0x0U)

/* EMIF ECC end address for region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2       (0x0U)

/* Define the range type of region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE (EMIF_ECC_ADDR_RANGE_WITHIN)

/* EMIF Size for TDA2x EVM silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE                (0x20000000U)

/* QSPI Flash Type from which App Image is Read */
#define SBL_LIB_CONFIG_QSPI_FLASH_TYPE          (DEVICE_TYPE_QSPI4)

/* DDR location where app image is copied temporarily */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS           (0x98000000U)

#else /* Default configuration */

/* Active EMIF configuration - can be also set via make argument EMIFMODE */
#ifndef TDA2XX_EMIF_MODE
#define TDA2XX_EMIF_MODE                        (SBLLIB_SINGLE_EMIF_512MB)
#endif

/* DDR Speed - only 532MHz is supported */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)

/* Enable ECC on EMIF */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0U)

/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)

/* EMIF ECC start address for region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1     (0x84400000U)

/* EMIF ECC end address for region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1       (0x8C400000U - 1U)

/* Define the range type of region 1 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE (EMIF_ECC_ADDR_RANGE_WITHIN)

/* EMIF ECC start address for region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2     (0x0U)

/* EMIF ECC end address for region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2       (0x0U)

/* Define the range type of region 2 for TDA2x EVM */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE (EMIF_ECC_ADDR_RANGE_WITHIN)

/* EMIF Size for TDA2x EVM silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE                (0x20000000U)

/* QSPI Flash Type from which App Image is Read */
#define SBL_LIB_CONFIG_QSPI_FLASH_TYPE          (DEVICE_TYPE_QSPI4)

/* Whether to enable parity check for DSP1 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP1_PARITY_CHECK        (1U)

/* Whether to enable parity check for DSP2 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP2_PARITY_CHECK        (1U)

/* DDR location where app image is copied temporarily */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS           (0x98000000U)

#endif

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

/* None */

#ifdef __cplusplus
}

#endif

#endif

