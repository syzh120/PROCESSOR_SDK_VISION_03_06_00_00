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
 *  \file     sbl_lib_config_tda3xx.h
 *
 *  \brief    This file contains compile time configurable parameters of
 *            TDA3xx SBL. This can be used to port SBL to custom use case.
 */

#ifndef SBL_LIB_CONFIG_TDA3XX_H_
#define SBL_LIB_CONFIG_TDA3XX_H_

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

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                 (SBLLIB_DDR_TYPE_DDR3)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12           (SBLLIB_DDR_TYPE_LPDDR2)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12          (SBLLIB_DDR_SPEED_400MHZ)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST                (UART3_INST)
/* QSPI Flash Type from which App Image is Read */
#define SBL_LIB_CONFIG_QSPI_FLASH_TYPE          (DEVICE_TYPE_QSPI4)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests
 * NOTE: Enable is not supported for Silicon Rev 1.0/1.0A
 **/
#define SBL_LIB_CONFIG_ENABLE_TESOC             (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests
 * NOTE: Enable is not supported for Silicon Rev 1.0/1.0A
 **/
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (0)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x84000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF - region is disabled if corresponding start
 * address entry is set to 0U
 */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x0U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x0U)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x0U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x0U)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* Whether to enable ECC for IPU RAM*/
#define SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC       (0U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (1U)
/* Flag to enable DSP to clock at 1 GHz and EVE to run at 900 MHz. When EVE
 * is set to 900 MHz the video PLL clock **cannot** be used */
#define SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ   (0U)
/* Whether to enable parity check for DSP1 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP1_PARITY_CHECK        (0U)
/* Whether to enable parity check for DSP2 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP2_PARITY_CHECK        (0U)

#elif defined (SBL_CONFIG_CUSTOM1)

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                (SBLLIB_DDR_TYPE_DDR2)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED               (SBLLIB_DDR_SPEED_333MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12          (SBLLIB_DDR_TYPE_INVALID)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12         (SBLLIB_DDR_SPEED_INVALID)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST               (UART1_INST)
/* QSPI Flash Type from which App Image is Read */
#define SBL_LIB_CONFIG_QSPI_FLASH_TYPE          (DEVICE_TYPE_QSPI4)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests
 * NOTE: Enable is not supported for Silicon Rev 1.0/1.0A
 **/
#define SBL_LIB_CONFIG_ENABLE_TESOC             (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests
 * NOTE: Enable is not supported for Silicon Rev 1.0/1.0A
 **/
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (0)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x84000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF - region is disabled if corresponding start
 * address entry is set to 0U
 */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x0U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x0U)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x0U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x0U)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* Whether to enable ECC for IPU RAM*/
#define SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC       (0U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (1U)
/* Flag to enable DSP to clock at 1 GHz and EVE to run at 900 MHz. When EVE
 * is set to 900 MHz the video PLL clock **cannot** be used */
#define SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ   (0U)
/* Whether to enable parity check for DSP1 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP1_PARITY_CHECK        (0U)
/* Whether to enable parity check for DSP2 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP2_PARITY_CHECK        (0U)

#else   /* Default configuration */

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                 (SBLLIB_DDR_TYPE_DDR3)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12           (SBLLIB_DDR_TYPE_LPDDR2)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12          (SBLLIB_DDR_SPEED_400MHZ)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST                (UART3_INST)
/* QSPI Flash Type from which App Image is Read */
#define SBL_LIB_CONFIG_QSPI_FLASH_TYPE          (DEVICE_TYPE_QSPI4)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests
 * NOTE: Enable is not supported for now
 **/
#define SBL_LIB_CONFIG_ENABLE_TESOC             (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests
 * NOTE: Enable is not supported for now
 **/
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (1)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x84000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF - region is disabled if corresponding start
 * address entry is set to 0U
 */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x82080000U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x87d80000U - 1U)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x0U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x0U)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* Whether to enable ECC for IPU RAM*/
#define SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC       (1U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (1U)
/* Flag to enable DSP to clock at 1 GHz and EVE to run at 900 MHz. When EVE
 * is set to 900 MHz the video PLL clock **cannot** be used */
#define SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ   (0U)
/* Whether to enable parity check for DSP1 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP1_PARITY_CHECK        (1U)
/* Whether to enable parity check for DSP2 L2 RAM/L1P memory */
#define SBL_LIB_CONFIG_DSP2_PARITY_CHECK        (1U)

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
