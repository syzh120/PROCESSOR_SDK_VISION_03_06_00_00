/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup SOC_TDA2EX
 *  \defgroup SOC_DEVICE_XBAR Device Xbar Defines
 *
 *  @{
 */
/**
 *  \file   tda2ex/csl_device_xbar.h
 *
 *  \brief  This file contains the XBAR related enums and macros definitions
 *          for the TDA2EX
 */


#ifndef CSL_TDA2EX_DEVICE_INTERRUPT_H
#define CSL_TDA2EX_DEVICE_INTERRUPT_H

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  Enumeration that contains all possible interrupt source IDs as inputs
 *         to each irq crossbar instance
 *
 */
typedef enum {
    CSL_XBAR_IRQ_MIN                            = 0,
    CSL_XBAR_ELM_IRQ                            = 1,
    CSL_XBAR_EXT_SYS_IRQ_1                      = 2,
    CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS      = 3,
    CSL_XBAR_L3_MAIN_IRQ_DBG_ERR                = 4,
    CSL_XBAR_L3_MAIN_IRQ_APP_ERR                = 5,
    CSL_XBAR_PRM_IRQ_MPU                        = 6,
    CSL_XBAR_DMA_SYSTEM_IRQ_0                   = 7,
    CSL_XBAR_DMA_SYSTEM_IRQ_1                   = 8,
    CSL_XBAR_DMA_SYSTEM_IRQ_2                   = 9,
    CSL_XBAR_DMA_SYSTEM_IRQ_3                   = 10,
    CSL_XBAR_L3_MAIN_IRQ_STAT_ALARM             = 11,
    CSL_XBAR_SMARTREFLEX_MPU_IRQ                = 13,
    CSL_XBAR_SMARTREFLEX_CORE_IRQ               = 14,
    CSL_XBAR_GPMC_IRQ                           = 15,
    CSL_XBAR_GPU_IRQ                            = 16,
    CSL_XBAR_DISPC_IRQ                          = 20,
    CSL_XBAR_MAILBOX1_IRQ_USER0                 = 21,
    CSL_XBAR_DSP1_IRQ_MMU0                      = 23,
    CSL_XBAR_GPIO1_IRQ_1                        = 24,
    CSL_XBAR_GPIO2_IRQ_1                        = 25,
    CSL_XBAR_GPIO3_IRQ_1                        = 26,
    CSL_XBAR_GPIO4_IRQ_1                        = 27,
    CSL_XBAR_GPIO5_IRQ_1                        = 28,
    CSL_XBAR_GPIO6_IRQ_1                        = 29,
    CSL_XBAR_GPIO7_IRQ_1                        = 30,
    CSL_XBAR_TIMER1_IRQ                         = 32,
    CSL_XBAR_TIMER2_IRQ                         = 33,
    CSL_XBAR_TIMER3_IRQ                         = 34,
    CSL_XBAR_TIMER4_IRQ                         = 35,
    CSL_XBAR_TIMER5_IRQ                         = 36,
    CSL_XBAR_TIMER6_IRQ                         = 37,
    CSL_XBAR_TIMER7_IRQ                         = 38,
    CSL_XBAR_TIMER8_IRQ                         = 39,
    CSL_XBAR_TIMER9_IRQ                         = 40,
    CSL_XBAR_TIMER10_IRQ                        = 41,
    CSL_XBAR_TIMER11_IRQ                        = 42,
    CSL_XBAR_MCSPI4_IRQ                         = 43,
    CSL_XBAR_SHA2MD5_1_IRQ_S                    = 44,
    CSL_XBAR_FPKA_IRQ                           = 45,
    CSL_XBAR_SHA2MD5_1_IRQ_P                    = 46,
    CSL_XBAR_RNG_IRQ                            = 47,
    CSL_XBAR_SATA_IRQ                           = 49,
    CSL_XBAR_I2C1_IRQ                           = 51,
    CSL_XBAR_I2C2_IRQ                           = 52,
    CSL_XBAR_HDQ1W_IRQ                          = 53,
    CSL_XBAR_I2C5_IRQ                           = 55,
    CSL_XBAR_I2C3_IRQ                           = 56,
    CSL_XBAR_I2C4_IRQ                           = 57,
    CSL_XBAR_AES2_IRQ_S                         = 58,
    CSL_XBAR_AES2_IRQ_P                         = 59,
    CSL_XBAR_MCSPI1_IRQ                         = 60,
    CSL_XBAR_MCSPI2_IRQ                         = 61,
    CSL_XBAR_UART4_IRQ                          = 65,
    CSL_XBAR_UART1_IRQ                          = 67,
    CSL_XBAR_UART2_IRQ                          = 68,
    CSL_XBAR_UART3_IRQ                          = 69,
    CSL_XBAR_PBIAS_IRQ                          = 70,
    CSL_XBAR_USB1_IRQ_INTR0                     = 71,
    CSL_XBAR_USB1_IRQ_INTR1                     = 72,
    CSL_XBAR_USB2_IRQ_INTR0                     = 73,
    CSL_XBAR_AES1_IRQ_S                         = 74,
    CSL_XBAR_WD_TIMER2_IRQ                      = 75,
    CSL_XBAR_DES3DES_IRQ_S                      = 76,
    CSL_XBAR_DES3DES_IRQ_P                      = 77,
    CSL_XBAR_MMC1_IRQ                           = 78,
    CSL_XBAR_AES1_IRQ_P                         = 80,
    CSL_XBAR_MMC2_IRQ                           = 81,
    CSL_XBAR_DEBUGSS_IRQ_CT_UART_TX             = 84,
    CSL_XBAR_DEBUGSS_IRQ_CT_UART_RX             = 85,
    CSL_XBAR_MCSPI3_IRQ                         = 86,
    CSL_XBAR_USB2_IRQ_INTR1                     = 87,
    CSL_XBAR_USB3_IRQ_INTR0                     = 88,
    CSL_XBAR_MMC3_IRQ                           = 89,
    CSL_XBAR_TIMER12_IRQ                        = 90,
    CSL_XBAR_MMC4_IRQ                           = 91,
    CSL_XBAR_HDMI_IRQ                           = 96,
    CSL_XBAR_IVA_IRQ_SYNC_1                     = 98,
    CSL_XBAR_IVA_IRQ_SYNC_0                     = 99,
    CSL_XBAR_UART5_IRQ                          = 100,
    CSL_XBAR_UART6_IRQ                          = 101,
    CSL_XBAR_IVA_IRQ_MAILBOX_0                  = 102,
    CSL_XBAR_McASP1_IRQ_AREVT                   = 103,
    CSL_XBAR_McASP1_IRQ_AXEVT                   = 104,
    CSL_XBAR_EMIF1_IRQ                          = 105,
    CSL_XBAR_DMM_IRQ                            = 108,
    CSL_XBAR_DMA_CRYPTO_IRQ_0                   = 110,
    CSL_XBAR_DMA_CRYPTO_IRQ_1                   = 111,
    CSL_XBAR_DMA_CRYPTO_IRQ_2                   = 112,
    CSL_XBAR_DMA_CRYPTO_IRQ_3                   = 113,
    CSL_XBAR_EXT_SYS_IRQ_2                      = 114,
    CSL_XBAR_KBD_IRQ                            = 115,
    CSL_XBAR_GPIO8_IRQ_1                        = 116,
    CSL_XBAR_CAL_IRQ                            = 119,
    CSL_XBAR_BB2D_IRQ                           = 120,
    CSL_XBAR_CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 121,
    CSL_XBAR_IVA_IRQ_MAILBOX_2                  = 132,
    CSL_XBAR_PRM_IRQ_IPU1                       = 133,
    CSL_XBAR_MAILBOX1_IRQ_USER2                 = 134,
    CSL_XBAR_MAILBOX1_IRQ_USER1                 = 135,
    CSL_XBAR_IVA_IRQ_MAILBOX_1                  = 136,
    CSL_XBAR_PRM_IRQ_DSP1                       = 137,
    CSL_XBAR_GPIO1_IRQ_2                        = 138,
    CSL_XBAR_GPIO2_IRQ_2                        = 139,
    CSL_XBAR_GPIO3_IRQ_2                        = 140,
    CSL_XBAR_GPIO4_IRQ_2                        = 141,
    CSL_XBAR_GPIO5_IRQ_2                        = 142,
    CSL_XBAR_GPIO6_IRQ_2                        = 143,
    CSL_XBAR_DSP1_IRQ_MMU1                      = 145,
    CSL_XBAR_McASP2_IRQ_AREVT                   = 148,
    CSL_XBAR_McASP2_IRQ_AXEVT                   = 149,
    CSL_XBAR_McASP3_IRQ_AREVT                   = 150,
    CSL_XBAR_McASP3_IRQ_AXEVT                   = 151,
    CSL_XBAR_McASP4_IRQ_AREVT                   = 152,
    CSL_XBAR_McASP4_IRQ_AXEVT                   = 153,
    CSL_XBAR_McASP5_IRQ_AREVT                   = 154,
    CSL_XBAR_McASP5_IRQ_AXEVT                   = 155,
    CSL_XBAR_McASP6_IRQ_AREVT                   = 156,
    CSL_XBAR_McASP6_IRQ_AXEVT                   = 157,
    CSL_XBAR_McASP7_IRQ_AREVT                   = 158,
    CSL_XBAR_McASP7_IRQ_AXEVT                   = 159,
    CSL_XBAR_McASP8_IRQ_AREVT                   = 160,
    CSL_XBAR_McASP8_IRQ_AXEVT                   = 161,
    CSL_XBAR_SHA2MD5_2_IRQ_S                    = 162,
    CSL_XBAR_SHA2MD5_2_IRQ_P                    = 163,
    CSL_XBAR_OCMC_RAM1_IRQ                      = 164,
    CSL_XBAR_PRUSS1_IRQ_HOST0                   = 184,
    CSL_XBAR_PRUSS1_IRQ_HOST1                   = 185,
    CSL_XBAR_PRUSS1_IRQ_HOST2                   = 186,
    CSL_XBAR_PRUSS1_IRQ_HOST3                   = 187,
    CSL_XBAR_PRUSS1_IRQ_HOST4                   = 188,
    CSL_XBAR_PRUSS1_IRQ_HOST5                   = 189,
    CSL_XBAR_PRUSS1_IRQ_HOST6                   = 190,
    CSL_XBAR_PRUSS1_IRQ_HOST7                   = 191,
    CSL_XBAR_PRUSS1_IRQ_HOST8                   = 192,
    CSL_XBAR_PRUSS1_IRQ_HOST9                   = 193,
    CSL_XBAR_PRUSS2_IRQ_HOST0                   = 194,
    CSL_XBAR_PRUSS2_IRQ_HOST1                   = 195,
    CSL_XBAR_PRUSS2_IRQ_HOST2                   = 196,
    CSL_XBAR_PRUSS2_IRQ_HOST3                   = 197,
    CSL_XBAR_PRUSS2_IRQ_HOST4                   = 198,
    CSL_XBAR_PRUSS2_IRQ_HOST5                   = 199,
    CSL_XBAR_PRUSS2_IRQ_HOST6                   = 200,
    CSL_XBAR_PRUSS2_IRQ_HOST7                   = 201,
    CSL_XBAR_PRUSS2_IRQ_HOST8                   = 202,
    CSL_XBAR_PRUSS2_IRQ_HOST9                   = 203,
    CSL_XBAR_PWMSS1_IRQ_ePWM0_TZINT             = 204,
    CSL_XBAR_PWMSS2_IRQ_ePWM1_TZINT             = 205,
    CSL_XBAR_PWMSS3_IRQ_ePWM2_TZINT             = 206,
    CSL_XBAR_PWMSS1_IRQ_ePWM0INT                = 207,
    CSL_XBAR_PWMSS2_IRQ_ePWM1INT                = 208,
    CSL_XBAR_PWMSS3_IRQ_ePWM2INT                = 209,
    CSL_XBAR_PWMSS1_IRQ_eQEP0INT                = 210,
    CSL_XBAR_PWMSS2_IRQ_eQEP1INT                = 211,
    CSL_XBAR_PWMSS3_IRQ_eQEP2INT                = 212,
    CSL_XBAR_PWMSS1_IRQ_eCAP0INT                = 213,
    CSL_XBAR_PWMSS2_IRQ_eCAP1INT                = 214,
    CSL_XBAR_PWMSS3_IRQ_eCAP2INT                = 215,
    CSL_XBAR_RTC_SS_IRQ_TIMER                   = 216,
    CSL_XBAR_RTC_SS_IRQ_ALARM                   = 217,
    CSL_XBAR_UART7_IRQ                          = 218,
    CSL_XBAR_UART8_IRQ                          = 219,
    CSL_XBAR_UART9_IRQ                          = 220,
    CSL_XBAR_UART10_IRQ                         = 221,
    CSL_XBAR_DCAN1_IRQ_INT0                     = 222,
    CSL_XBAR_DCAN1_IRQ_INT1                     = 223,
    CSL_XBAR_DCAN1_IRQ_PARITY                   = 224,
    CSL_XBAR_DCAN2_IRQ_INT0                     = 225,
    CSL_XBAR_DCAN2_IRQ_INT1                     = 226,
    CSL_XBAR_DCAN2_IRQ_PARITY                   = 227,
    CSL_XBAR_MLB_IRQ_SYS_INT0                   = 228,
    CSL_XBAR_MLB_IRQ_SYS_INT1                   = 229,
    CSL_XBAR_VCP1_IRQ_INT                       = 230,
    CSL_XBAR_VCP2_IRQ_INT                       = 231,
    CSL_XBAR_PCIe_SS1_IRQ_INT0                  = 232,
    CSL_XBAR_PCIe_SS1_IRQ_INT1                  = 233,
    CSL_XBAR_PCIe_SS1_IRQ_INT2                  = 234,
    CSL_XBAR_PCIe_SS1_IRQ_INT3                  = 235,
    CSL_XBAR_SPARE_TSC_ADC_IRQ_GENINT           = 236,
    CSL_XBAR_MAILBOX2_IRQ_USER0                 = 237,
    CSL_XBAR_MAILBOX2_IRQ_USER1                 = 238,
    CSL_XBAR_MAILBOX2_IRQ_USER2                 = 239,
    CSL_XBAR_MAILBOX2_IRQ_USER3                 = 240,
    CSL_XBAR_MAILBOX3_IRQ_USER0                 = 241,
    CSL_XBAR_MAILBOX3_IRQ_USER1                 = 242,
    CSL_XBAR_MAILBOX3_IRQ_USER2                 = 243,
    CSL_XBAR_MAILBOX3_IRQ_USER3                 = 244,
    CSL_XBAR_MAILBOX4_IRQ_USER0                 = 245,
    CSL_XBAR_MAILBOX4_IRQ_USER1                 = 246,
    CSL_XBAR_MAILBOX4_IRQ_USER2                 = 247,
    CSL_XBAR_MAILBOX4_IRQ_USER3                 = 248,
    CSL_XBAR_MAILBOX5_IRQ_USER0                 = 249,
    CSL_XBAR_MAILBOX5_IRQ_USER1                 = 250,
    CSL_XBAR_MAILBOX5_IRQ_USER2                 = 251,
    CSL_XBAR_MAILBOX5_IRQ_USER3                 = 252,
    CSL_XBAR_MAILBOX6_IRQ_USER0                 = 253,
    CSL_XBAR_MAILBOX6_IRQ_USER1                 = 254,
    CSL_XBAR_MAILBOX6_IRQ_USER2                 = 255,
    CSL_XBAR_MAILBOX6_IRQ_USER3                 = 256,
    CSL_XBAR_MAILBOX7_IRQ_USER0                 = 257,
    CSL_XBAR_MAILBOX7_IRQ_USER1                 = 258,
    CSL_XBAR_MAILBOX7_IRQ_USER2                 = 259,
    CSL_XBAR_MAILBOX7_IRQ_USER3                 = 260,
    CSL_XBAR_MAILBOX8_IRQ_USER0                 = 261,
    CSL_XBAR_MAILBOX8_IRQ_USER1                 = 262,
    CSL_XBAR_MAILBOX8_IRQ_USER2                 = 263,
    CSL_XBAR_MAILBOX8_IRQ_USER3                 = 264,
    CSL_XBAR_MAILBOX9_IRQ_USER0                 = 265,
    CSL_XBAR_MAILBOX9_IRQ_USER1                 = 266,
    CSL_XBAR_MAILBOX9_IRQ_USER2                 = 267,
    CSL_XBAR_MAILBOX9_IRQ_USER3                 = 268,
    CSL_XBAR_MAILBOX10_IRQ_USER0                = 269,
    CSL_XBAR_MAILBOX10_IRQ_USER1                = 270,
    CSL_XBAR_MAILBOX10_IRQ_USER2                = 271,
    CSL_XBAR_MAILBOX10_IRQ_USER3                = 272,
    CSL_XBAR_MAILBOX11_IRQ_USER0                = 273,
    CSL_XBAR_MAILBOX11_IRQ_USER1                = 274,
    CSL_XBAR_MAILBOX11_IRQ_USER2                = 275,
    CSL_XBAR_MAILBOX11_IRQ_USER3                = 276,
    CSL_XBAR_MAILBOX12_IRQ_USER0                = 277,
    CSL_XBAR_MAILBOX12_IRQ_USER1                = 278,
    CSL_XBAR_MAILBOX12_IRQ_USER2                = 279,
    CSL_XBAR_MAILBOX12_IRQ_USER3                = 280,
    CSL_XBAR_DSP1_IRQ_TPCC_ERR                  = 317,
    CSL_XBAR_DSP1_IRQ_TPCC_GLOBAL               = 318,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION0              = 319,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION1              = 320,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION2              = 321,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION3              = 322,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION4              = 323,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION5              = 324,
    CSL_XBAR_MMU1_IRQ                           = 333,
    CSL_XBAR_GMAC_SW_IRQ_RX_THRESH_PULSE        = 334,
    CSL_XBAR_GMAC_SW_IRQ_RX_PULSE               = 335,
    CSL_XBAR_GMAC_SW_IRQ_TX_PULSE               = 336,
    CSL_XBAR_GMAC_SW_IRQ_MISC_PULSE             = 337,
    CSL_XBAR_WD_TIMER1_IRQ                      = 338,
    CSL_XBAR_TIMER13_IRQ                        = 339,
    CSL_XBAR_TIMER14_IRQ                        = 340,
    CSL_XBAR_TIMER15_IRQ                        = 341,
    CSL_XBAR_TIMER16_IRQ                        = 342,
    CSL_XBAR_QSPI_IRQ                           = 343,
    CSL_XBAR_USB3_IRQ_INTR1                     = 344,
    CSL_XBAR_GPIO7_IRQ_2                        = 347,
    CSL_XBAR_GPIO8_IRQ_2                        = 348,
    CSL_XBAR_VIP1_IRQ                           = 351,
    CSL_XBAR_VPE_IRQ                            = 354,
    CSL_XBAR_PCIe_SS2_IRQ_INT0                  = 355,
    CSL_XBAR_PCIe_SS2_IRQ_INT1                  = 356,
    CSL_XBAR_PCIe_SS2_IRQ_INT2                  = 357,
    CSL_XBAR_PCIe_SS2_IRQ_INT3                  = 358,
    CSL_XBAR_EDMA_TPCC_IRQ_ERR                  = 359,
    CSL_XBAR_EDMA_TPCC_IRQ_MP                   = 360,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION0              = 361,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION1              = 362,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION2              = 363,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION3              = 364,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION4              = 365,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION5              = 366,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION6              = 367,
    CSL_XBAR_EDMA_TPCC_IRQ_REGION7              = 368,
    CSL_XBAR_MMU2_IRQ                           = 369,
    CSL_XBAR_EDMA_TC0_IRQ_ERR                   = 370,
    CSL_XBAR_EDMA_TC1_IRQ_ERR                   = 371,
    CSL_XBAR_OCMC_RAM1_IRQ_CBUF                 = 372,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION6              = 375,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION7              = 376,
    CSL_XBAR_MAILBOX13_IRQ_USER0                = 379,
    CSL_XBAR_MAILBOX13_IRQ_USER1                = 380,
    CSL_XBAR_MAILBOX13_IRQ_USER2                = 381,
    CSL_XBAR_MAILBOX13_IRQ_USER3                = 382,
    CSL_XBAR_SMARTREFLEX_DSPEVE_IRQ             = 383,
    CSL_XBAR_SMARTREFLEX_GPU_IRQ                = 384,
    CSL_XBAR_SMARTREFLEX_IVA_IRQ                = 385,
    CSL_XBAR_PRM_IRQ_IPU2                       = 386,
    CSL_XBAR_I2C6_IRQ                           = 402,
    CSL_XBAR_IRQ_MAX                            = 403
} CSL_XbarIrq;

typedef enum
{
    CSL_XBAR_IRQ_CPU_ID_MPU,
    CSL_XBAR_IRQ_CPU_ID_IPU1,
    CSL_XBAR_IRQ_CPU_ID_IPU2,
    CSL_XBAR_IRQ_CPU_ID_DSP1,
    CSL_XBAR_IRQ_CPU_ID_PRUSS1
} CSL_XbarIrqCpuId;

typedef enum
{
    CSL_XBAR_DMA_CPU_ID_SYSTEM_DMA,
    CSL_XBAR_DMA_CPU_ID_EDMA,
    CSL_XBAR_DMA_CPU_ID_DSP1_DMA,
    CSL_XBAR_DMA_CPU_ID_DSP2_DMA
} CSL_XbarDmaCpuId;

typedef enum
{
    CSL_XBAR_DMA_MIN                            = 0,
    CSL_XBAR_DMA_EXT_SYS_DREQ_0                 = 2,
    CSL_XBAR_DMA_EXT_SYS_DREQ_1                 = 3,
    CSL_XBAR_DMA_GPMC_DREQ                      = 4,
    CSL_XBAR_DMA_DISPC_DREQ                     = 6,
    CSL_XBAR_DMA_CT_TBR_DREQ                    = 7,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX0                = 15,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX0                = 16,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX1                = 23,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX1                = 24,
    CSL_XBAR_DMA_I2C3_DREQ_TX                   = 25,
    CSL_XBAR_DMA_I2C3_DREQ_RX                   = 26,
    CSL_XBAR_DMA_I2C1_DREQ_TX                   = 27,
    CSL_XBAR_DMA_I2C1_DREQ_RX                   = 28,
    CSL_XBAR_DMA_I2C2_DREQ_TX                   = 29,
    CSL_XBAR_DMA_I2C2_DREQ_RX                   = 30,
    CSL_XBAR_DMA_MCSPI1_DREQ_TX0                = 35,
    CSL_XBAR_DMA_MCSPI1_DREQ_RX0                = 36,
    CSL_XBAR_DMA_MCSPI1_DREQ_TX1                = 37,
    CSL_XBAR_DMA_MCSPI1_DREQ_RX1                = 38,
    CSL_XBAR_DMA_MCSPI1_DREQ_TX2                = 39,
    CSL_XBAR_DMA_MCSPI1_DREQ_RX2                = 40,
    CSL_XBAR_DMA_MCSPI1_DREQ_TX3                = 41,
    CSL_XBAR_DMA_MCSPI1_DREQ_RX3                = 42,
    CSL_XBAR_DMA_MCSPI2_DREQ_TX0                = 43,
    CSL_XBAR_DMA_MCSPI2_DREQ_RX0                = 44,
    CSL_XBAR_DMA_MCSPI2_DREQ_TX1                = 45,
    CSL_XBAR_DMA_MCSPI2_DREQ_RX1                = 46,
    CSL_XBAR_DMA_MMC2_DREQ_TX                   = 47,
    CSL_XBAR_DMA_MMC2_DREQ_RX                   = 48,
    CSL_XBAR_DMA_UART1_DREQ_TX                  = 49,
    CSL_XBAR_DMA_UART1_DREQ_RX                  = 50,
    CSL_XBAR_DMA_UART2_DREQ_TX                  = 51,
    CSL_XBAR_DMA_UART2_DREQ_RX                  = 52,
    CSL_XBAR_DMA_UART3_DREQ_TX                  = 53,
    CSL_XBAR_DMA_UART3_DREQ_RX                  = 54,
    CSL_XBAR_DMA_UART4_DREQ_TX                  = 55,
    CSL_XBAR_DMA_UART4_DREQ_RX                  = 56,
    CSL_XBAR_DMA_MMC4_DREQ_TX                   = 57,
    CSL_XBAR_DMA_MMC4_DREQ_RX                   = 58,
    CSL_XBAR_DMA_MMC1_DREQ_TX                   = 61,
    CSL_XBAR_DMA_MMC1_DREQ_RX                   = 62,
    CSL_XBAR_DMA_UART5_DREQ_TX                  = 63,
    CSL_XBAR_DMA_UART5_DREQ_RX                  = 64,
    CSL_XBAR_DMA_MCSPI4_DREQ_TX0                = 70,
    CSL_XBAR_DMA_MCSPI4_DREQ_RX0                = 71,
    CSL_XBAR_DMA_DSS_DREQ                       = 76,
    CSL_XBAR_DMA_MMC3_DREQ_TX                   = 77,
    CSL_XBAR_DMA_MMC3_DREQ_RX                   = 78,
    CSL_XBAR_DMA_UART6_DREQ_TX                  = 79,
    CSL_XBAR_DMA_UART6_DREQ_RX                  = 80,
    CSL_XBAR_DMA_AES1_DREQ_P_CTXT_IN            = 109,
    CSL_XBAR_DMA_AES1_DREQ_P_DATA_IN            = 110,
    CSL_XBAR_DMA_AES1_DREQ_P_DATA_OUT           = 111,
    CSL_XBAR_DMA_AES2_DREQ_P_CTXT_IN            = 112,
    CSL_XBAR_DMA_AES2_DREQ_P_DATA_IN            = 113,
    CSL_XBAR_DMA_AES2_DREQ_P_DATA_OUT           = 114,
    CSL_XBAR_DMA_DES3DES_DREQ_P_CTXT_IN         = 115,
    CSL_XBAR_DMA_DES3DES_DREQ_P_DATA_IN         = 116,
    CSL_XBAR_DMA_DES3DES_DREQ_P_DATA_OUT        = 117,
    CSL_XBAR_DMA_SHA2MD5_1_DREQ_P_CTXT_IN       = 118,
    CSL_XBAR_DMA_SHA2MD5_1_DREQ_P_DATA_IN       = 119,
    CSL_XBAR_DMA_SHA2MD5_1_DREQ_P_DATA_CTXT_OUT = 120,
    CSL_XBAR_DMA_AES1_DREQ_P_CTXT_OUT           = 121,
    CSL_XBAR_DMA_AES2_DREQ_P_CTXT_OUT           = 122,
    CSL_XBAR_DMA_I2C4_DREQ_TX                   = 124,
    CSL_XBAR_DMA_I2C4_DREQ_RX                   = 125,
    CSL_XBAR_DMA_McASP1_DREQ_RX                 = 128,
    CSL_XBAR_DMA_McASP1_DREQ_TX                 = 129,
    CSL_XBAR_DMA_McASP2_DREQ_RX                 = 130,
    CSL_XBAR_DMA_McASP2_DREQ_TX                 = 131,
    CSL_XBAR_DMA_McASP3_DREQ_RX                 = 132,
    CSL_XBAR_DMA_McASP3_DREQ_TX                 = 133,
    CSL_XBAR_DMA_McASP4_DREQ_RX                 = 134,
    CSL_XBAR_DMA_McASP4_DREQ_TX                 = 135,
    CSL_XBAR_DMA_McASP5_DREQ_RX                 = 136,
    CSL_XBAR_DMA_McASP5_DREQ_TX                 = 137,
    CSL_XBAR_DMA_McASP6_DREQ_RX                 = 138,
    CSL_XBAR_DMA_McASP6_DREQ_TX                 = 139,
    CSL_XBAR_DMA_McASP7_DREQ_RX                 = 140,
    CSL_XBAR_DMA_McASP7_DREQ_TX                 = 141,
    CSL_XBAR_DMA_McASP8_DREQ_RX                 = 142,
    CSL_XBAR_DMA_McASP8_DREQ_TX                 = 143,
    CSL_XBAR_DMA_UART7_DREQ_TX                  = 144,
    CSL_XBAR_DMA_UART7_DREQ_RX                  = 145,
    CSL_XBAR_DMA_UART8_DREQ_TX                  = 146,
    CSL_XBAR_DMA_UART8_DREQ_RX                  = 147,
    CSL_XBAR_DMA_UART9_DREQ_TX                  = 148,
    CSL_XBAR_DMA_UART9_DREQ_RX                  = 149,
    CSL_XBAR_DMA_UART10_DREQ_TX                 = 150,
    CSL_XBAR_DMA_UART10_DREQ_RX                 = 151,
    CSL_XBAR_DMA_I2C5_DREQ_TX                   = 152,
    CSL_XBAR_DMA_I2C5_DREQ_RX                   = 153,
    CSL_XBAR_DMA_VCP1_DREQ_RX                   = 154,
    CSL_XBAR_DMA_VCP1_DREQ_TX                   = 155,
    CSL_XBAR_DMA_VCP2_DREQ_RX                   = 156,
    CSL_XBAR_DMA_VCP2_DREQ_TX                   = 157,
    CSL_XBAR_DMA_DCAN1_DREQ_IF1                 = 158,
    CSL_XBAR_DMA_DCAN1_DREQ_IF2                 = 159,
    CSL_XBAR_DMA_DCAN1_DREQ_IF3                 = 160,
    CSL_XBAR_DMA_DCAN2_DREQ_IF1                 = 161,
    CSL_XBAR_DMA_DCAN2_DREQ_IF2                 = 162,
    CSL_XBAR_DMA_DCAN2_DREQ_IF3                 = 163,
    CSL_XBAR_DMA_SHA2MD5_2_DREQ_P_CTXT_IN       = 164,
    CSL_XBAR_DMA_SHA2MD5_2_DREQ_P_DATA_IN       = 165,
    CSL_XBAR_DMA_SHA2MD5_2_DREQ_P_DATA_CTXT_OUT = 166,
    CSL_XBAR_DMA_EXT_SYS_DREQ_2                 = 167,
    CSL_XBAR_DMA_EXT_SYS_DREQ_3                 = 168,
    CSL_XBAR_DMA_MCSPI2_DREQ_TX2                = 169,
    CSL_XBAR_DMA_MCSPI2_DREQ_RX2                = 170,
    CSL_XBAR_DMA_MCSPI2_DREQ_TX3                = 171,
    CSL_XBAR_DMA_MCSPI2_DREQ_RX3                = 172,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX2                = 173,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX2                = 174,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX3                = 175,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX3                = 176,
    CSL_XBAR_DMA_MCSPI4_DREQ_TX1                = 177,
    CSL_XBAR_DMA_MCSPI4_DREQ_RX1                = 178,
    CSL_XBAR_DMA_MCSPI4_DREQ_TX2                = 179,
    CSL_XBAR_DMA_MCSPI4_DREQ_RX2                = 180,
    CSL_XBAR_DMA_MCSPI4_DREQ_TX3                = 181,
    CSL_XBAR_DMA_MCSPI4_DREQ_RX3                = 182,
    CSL_XBAR_DMA_PRUSS1_DREQ_HOST_REQ0          = 183,
    CSL_XBAR_DMA_PRUSS1_DREQ_HOST_REQ1          = 184,
    CSL_XBAR_DMA_PRUSS2_DREQ_HOST_REQ0          = 185,
    CSL_XBAR_DMA_PRUSS2_DREQ_HOST_REQ1          = 186,
    CSL_XBAR_DMA_GPIO1_DREQ_EVT                 = 187,
    CSL_XBAR_DMA_GPIO2_DREQ_EVT                 = 188,
    CSL_XBAR_DMA_GPIO3_DREQ_EVT                 = 189,
    CSL_XBAR_DMA_GPIO4_DREQ_EVT                 = 190,
    CSL_XBAR_DMA_GPIO5_DREQ_EVT                 = 191,
    CSL_XBAR_DMA_GPIO6_DREQ_EVT                 = 192,
    CSL_XBAR_DMA_GPIO7_DREQ_EVT                 = 193,
    CSL_XBAR_DMA_GPIO8_DREQ_EVT                 = 194,
    CSL_XBAR_DMA_PWMSS1_DREQ_ePWM0_EVT          = 195,
    CSL_XBAR_DMA_PWMSS2_DREQ_ePWM1_EVT          = 196,
    CSL_XBAR_DMA_PWMSS3_DREQ_ePWM2_EVT          = 197,
    CSL_XBAR_DMA_PWMSS1_DREQ_eQEP0_EVT          = 198,
    CSL_XBAR_DMA_PWMSS2_DREQ_eQEP1_EVT          = 199,
    CSL_XBAR_DMA_PWMSS3_DREQ_eQEP2_EVT          = 200,
    CSL_XBAR_DMA_PWMSS1_DREQ_eCAP0_EVT          = 201,
    CSL_XBAR_DMA_PWMSS2_DREQ_eCAP1_EVT          = 202,
    CSL_XBAR_DMA_PWMSS3_DREQ_eCAP2_EVT          = 203,
    CSL_XBAR_DMA_I2C6_DREQ_TX                   = 204,
    CSL_XBAR_DMA_I2C6_DREQ_RX                   = 205,
    CSL_XBAR_DMA_RSVD1                          = 206

} CSL_XbarDma;

#define CSL_MPU_IRQ_XBAR_COUNT      (0x98U)
#define CSL_IPU1_IRQ_XBAR_COUNT     (0x39U)
#define CSL_IPU2_IRQ_XBAR_COUNT     (0x39U)
#define CSL_IPU_IRQ_XBAR_COUNT      (0x39U)
#define CSL_DSP1_IRQ_XBAR_COUNT     (0x40U)
#define CSL_DSP_IRQ_XBAR_COUNT      (0x40U)
#define CSL_PRUSS1_IRQ_XBAR_COUNT   (0x20U)
#define CSL_IRQ_XBAR_MAX_COUNT      (0x1A4U)

#define CSL_EDMA_XBAR_COUNT         (0x40U)
#define CSL_DSP1_DMA_XBAR_COUNT     (0x14U)
#define CSL_DSP2_DMA_XBAR_COUNT     (0x14U)
#define CSL_DMA_XBAR_MAX_COUNT      (0xDDU)

/******************************************************************************
 * IRQ XBAR instance mapping for each core interrupts.
 * This is the IRQ XBAR instance to which a particular interrupt of the core is
 * mapped. This macro could be used to pass the IRQ XBAR instance to the IRQ
 * XBAR connect API of starterware.
 ******************************************************************************/
/* IRQ XBAR Mapping for MPU */
#define CSL_XBAR_INST_MPU_IRQ_4             (1U)
#define CSL_XBAR_INST_MPU_IRQ_7             (2U)
#define CSL_XBAR_INST_MPU_IRQ_8             (3U)
#define CSL_XBAR_INST_MPU_IRQ_9             (4U)
#define CSL_XBAR_INST_MPU_IRQ_10            (5U)
#define CSL_XBAR_INST_MPU_IRQ_11            (6U)
#define CSL_XBAR_INST_MPU_IRQ_12            (7U)
#define CSL_XBAR_INST_MPU_IRQ_13            (8U)
#define CSL_XBAR_INST_MPU_IRQ_14            (9U)
#define CSL_XBAR_INST_MPU_IRQ_15            (10U)
#define CSL_XBAR_INST_MPU_IRQ_16            (11U)
#define CSL_XBAR_INST_MPU_IRQ_17            (12U)
#define CSL_XBAR_INST_MPU_IRQ_18            (13U)
#define CSL_XBAR_INST_MPU_IRQ_19            (14U)
#define CSL_XBAR_INST_MPU_IRQ_20            (15U)
#define CSL_XBAR_INST_MPU_IRQ_21            (16U)
#define CSL_XBAR_INST_MPU_IRQ_22            (17U)
#define CSL_XBAR_INST_MPU_IRQ_23            (18U)
#define CSL_XBAR_INST_MPU_IRQ_24            (19U)
#define CSL_XBAR_INST_MPU_IRQ_25            (20U)
#define CSL_XBAR_INST_MPU_IRQ_26            (21U)
#define CSL_XBAR_INST_MPU_IRQ_27            (22U)
#define CSL_XBAR_INST_MPU_IRQ_28            (23U)
#define CSL_XBAR_INST_MPU_IRQ_29            (24U)
#define CSL_XBAR_INST_MPU_IRQ_30            (25U)
#define CSL_XBAR_INST_MPU_IRQ_31            (26U)
#define CSL_XBAR_INST_MPU_IRQ_32            (27U)
#define CSL_XBAR_INST_MPU_IRQ_33            (28U)
#define CSL_XBAR_INST_MPU_IRQ_34            (29U)
#define CSL_XBAR_INST_MPU_IRQ_35            (30U)
#define CSL_XBAR_INST_MPU_IRQ_36            (31U)
#define CSL_XBAR_INST_MPU_IRQ_37            (32U)
#define CSL_XBAR_INST_MPU_IRQ_38            (33U)
#define CSL_XBAR_INST_MPU_IRQ_39            (34U)
#define CSL_XBAR_INST_MPU_IRQ_40            (35U)
#define CSL_XBAR_INST_MPU_IRQ_41            (36U)
#define CSL_XBAR_INST_MPU_IRQ_42            (37U)
#define CSL_XBAR_INST_MPU_IRQ_43            (38U)
#define CSL_XBAR_INST_MPU_IRQ_44            (39U)
#define CSL_XBAR_INST_MPU_IRQ_45            (40U)
#define CSL_XBAR_INST_MPU_IRQ_46            (41U)
#define CSL_XBAR_INST_MPU_IRQ_47            (42U)
#define CSL_XBAR_INST_MPU_IRQ_48            (43U)
#define CSL_XBAR_INST_MPU_IRQ_49            (44U)
#define CSL_XBAR_INST_MPU_IRQ_50            (45U)
#define CSL_XBAR_INST_MPU_IRQ_51            (46U)
#define CSL_XBAR_INST_MPU_IRQ_52            (47U)
#define CSL_XBAR_INST_MPU_IRQ_53            (48U)
#define CSL_XBAR_INST_MPU_IRQ_54            (49U)
#define CSL_XBAR_INST_MPU_IRQ_55            (50U)
#define CSL_XBAR_INST_MPU_IRQ_56            (51U)
#define CSL_XBAR_INST_MPU_IRQ_57            (52U)
#define CSL_XBAR_INST_MPU_IRQ_58            (53U)
#define CSL_XBAR_INST_MPU_IRQ_59            (54U)
#define CSL_XBAR_INST_MPU_IRQ_60            (55U)
#define CSL_XBAR_INST_MPU_IRQ_61            (56U)
#define CSL_XBAR_INST_MPU_IRQ_62            (57U)
#define CSL_XBAR_INST_MPU_IRQ_63            (58U)
#define CSL_XBAR_INST_MPU_IRQ_64            (59U)
#define CSL_XBAR_INST_MPU_IRQ_65            (60U)
#define CSL_XBAR_INST_MPU_IRQ_66            (61U)
#define CSL_XBAR_INST_MPU_IRQ_67            (62U)
#define CSL_XBAR_INST_MPU_IRQ_68            (63U)
#define CSL_XBAR_INST_MPU_IRQ_69            (64U)
#define CSL_XBAR_INST_MPU_IRQ_70            (65U)
#define CSL_XBAR_INST_MPU_IRQ_71            (66U)
#define CSL_XBAR_INST_MPU_IRQ_72            (67U)
#define CSL_XBAR_INST_MPU_IRQ_73            (68U)
#define CSL_XBAR_INST_MPU_IRQ_74            (69U)
#define CSL_XBAR_INST_MPU_IRQ_75            (70U)
#define CSL_XBAR_INST_MPU_IRQ_76            (71U)
#define CSL_XBAR_INST_MPU_IRQ_77            (72U)
#define CSL_XBAR_INST_MPU_IRQ_78            (73U)
#define CSL_XBAR_INST_MPU_IRQ_79            (74U)
#define CSL_XBAR_INST_MPU_IRQ_80            (75U)
#define CSL_XBAR_INST_MPU_IRQ_81            (76U)
#define CSL_XBAR_INST_MPU_IRQ_82            (77U)
#define CSL_XBAR_INST_MPU_IRQ_83            (78U)
#define CSL_XBAR_INST_MPU_IRQ_84            (79U)
#define CSL_XBAR_INST_MPU_IRQ_85            (80U)
#define CSL_XBAR_INST_MPU_IRQ_86            (81U)
#define CSL_XBAR_INST_MPU_IRQ_87            (82U)
#define CSL_XBAR_INST_MPU_IRQ_88            (83U)
#define CSL_XBAR_INST_MPU_IRQ_89            (84U)
#define CSL_XBAR_INST_MPU_IRQ_90            (85U)
#define CSL_XBAR_INST_MPU_IRQ_91            (86U)
#define CSL_XBAR_INST_MPU_IRQ_92            (87U)
#define CSL_XBAR_INST_MPU_IRQ_93            (88U)
#define CSL_XBAR_INST_MPU_IRQ_94            (89U)
#define CSL_XBAR_INST_MPU_IRQ_95            (90U)
#define CSL_XBAR_INST_MPU_IRQ_96            (91U)
#define CSL_XBAR_INST_MPU_IRQ_97            (92U)
#define CSL_XBAR_INST_MPU_IRQ_98            (93U)
#define CSL_XBAR_INST_MPU_IRQ_99            (94U)
#define CSL_XBAR_INST_MPU_IRQ_100           (95U)
#define CSL_XBAR_INST_MPU_IRQ_101           (96U)
#define CSL_XBAR_INST_MPU_IRQ_102           (97U)
#define CSL_XBAR_INST_MPU_IRQ_103           (98U)
#define CSL_XBAR_INST_MPU_IRQ_104           (99U)
#define CSL_XBAR_INST_MPU_IRQ_105           (100U)
#define CSL_XBAR_INST_MPU_IRQ_106           (101U)
#define CSL_XBAR_INST_MPU_IRQ_107           (102U)
#define CSL_XBAR_INST_MPU_IRQ_108           (103U)
#define CSL_XBAR_INST_MPU_IRQ_109           (104U)
#define CSL_XBAR_INST_MPU_IRQ_110           (105U)
#define CSL_XBAR_INST_MPU_IRQ_111           (106U)
#define CSL_XBAR_INST_MPU_IRQ_112           (107U)
#define CSL_XBAR_INST_MPU_IRQ_113           (108U)
#define CSL_XBAR_INST_MPU_IRQ_114           (109U)
#define CSL_XBAR_INST_MPU_IRQ_115           (110U)
#define CSL_XBAR_INST_MPU_IRQ_116           (111U)
#define CSL_XBAR_INST_MPU_IRQ_117           (112U)
#define CSL_XBAR_INST_MPU_IRQ_118           (113U)
#define CSL_XBAR_INST_MPU_IRQ_119           (114U)
#define CSL_XBAR_INST_MPU_IRQ_120           (115U)
#define CSL_XBAR_INST_MPU_IRQ_121           (116U)
#define CSL_XBAR_INST_MPU_IRQ_122           (117U)
#define CSL_XBAR_INST_MPU_IRQ_123           (118U)
#define CSL_XBAR_INST_MPU_IRQ_124           (119U)
#define CSL_XBAR_INST_MPU_IRQ_125           (120U)
#define CSL_XBAR_INST_MPU_IRQ_126           (121U)
#define CSL_XBAR_INST_MPU_IRQ_127           (122U)
#define CSL_XBAR_INST_MPU_IRQ_128           (123U)
#define CSL_XBAR_INST_MPU_IRQ_129           (124U)
#define CSL_XBAR_INST_MPU_IRQ_130           (125U)
#define CSL_XBAR_INST_MPU_IRQ_133           (126U)
#define CSL_XBAR_INST_MPU_IRQ_134           (127U)
#define CSL_XBAR_INST_MPU_IRQ_135           (128U)
#define CSL_XBAR_INST_MPU_IRQ_136           (129U)
#define CSL_XBAR_INST_MPU_IRQ_137           (130U)
#define CSL_XBAR_INST_MPU_IRQ_138           (131U)
#define CSL_XBAR_INST_MPU_IRQ_141           (134U)
#define CSL_XBAR_INST_MPU_IRQ_142           (135U)
#define CSL_XBAR_INST_MPU_IRQ_143           (136U)
#define CSL_XBAR_INST_MPU_IRQ_144           (137U)
#define CSL_XBAR_INST_MPU_IRQ_145           (138U)
#define CSL_XBAR_INST_MPU_IRQ_146           (139U)
#define CSL_XBAR_INST_MPU_IRQ_147           (140U)
#define CSL_XBAR_INST_MPU_IRQ_148           (141U)
#define CSL_XBAR_INST_MPU_IRQ_149           (142U)
#define CSL_XBAR_INST_MPU_IRQ_150           (143U)
#define CSL_XBAR_INST_MPU_IRQ_151           (144U)
#define CSL_XBAR_INST_MPU_IRQ_152           (145U)
#define CSL_XBAR_INST_MPU_IRQ_153           (146U)
#define CSL_XBAR_INST_MPU_IRQ_154           (147U)
#define CSL_XBAR_INST_MPU_IRQ_155           (148U)
#define CSL_XBAR_INST_MPU_IRQ_156           (149U)
#define CSL_XBAR_INST_MPU_IRQ_157           (150U)
#define CSL_XBAR_INST_MPU_IRQ_158           (151U)
#define CSL_XBAR_INST_MPU_IRQ_159           (152U)

/* IRQ XBAR Mapping for DSP1 */
#define CSL_XBAR_INST_DSP1_IRQ_32           (1U)
#define CSL_XBAR_INST_DSP1_IRQ_33           (2U)
#define CSL_XBAR_INST_DSP1_IRQ_34           (3U)
#define CSL_XBAR_INST_DSP1_IRQ_35           (4U)
#define CSL_XBAR_INST_DSP1_IRQ_36           (5U)
#define CSL_XBAR_INST_DSP1_IRQ_37           (6U)
#define CSL_XBAR_INST_DSP1_IRQ_38           (7U)
#define CSL_XBAR_INST_DSP1_IRQ_39           (8U)
#define CSL_XBAR_INST_DSP1_IRQ_40           (9U)
#define CSL_XBAR_INST_DSP1_IRQ_41           (10U)
#define CSL_XBAR_INST_DSP1_IRQ_42           (11U)
#define CSL_XBAR_INST_DSP1_IRQ_43           (12U)
#define CSL_XBAR_INST_DSP1_IRQ_44           (13U)
#define CSL_XBAR_INST_DSP1_IRQ_45           (14U)
#define CSL_XBAR_INST_DSP1_IRQ_46           (15U)
#define CSL_XBAR_INST_DSP1_IRQ_47           (16U)
#define CSL_XBAR_INST_DSP1_IRQ_48           (17U)
#define CSL_XBAR_INST_DSP1_IRQ_49           (18U)
#define CSL_XBAR_INST_DSP1_IRQ_50           (19U)
#define CSL_XBAR_INST_DSP1_IRQ_51           (20U)
#define CSL_XBAR_INST_DSP1_IRQ_52           (21U)
#define CSL_XBAR_INST_DSP1_IRQ_53           (22U)
#define CSL_XBAR_INST_DSP1_IRQ_54           (23U)
#define CSL_XBAR_INST_DSP1_IRQ_55           (24U)
#define CSL_XBAR_INST_DSP1_IRQ_56           (25U)
#define CSL_XBAR_INST_DSP1_IRQ_57           (26U)
#define CSL_XBAR_INST_DSP1_IRQ_58           (27U)
#define CSL_XBAR_INST_DSP1_IRQ_59           (28U)
#define CSL_XBAR_INST_DSP1_IRQ_60           (29U)
#define CSL_XBAR_INST_DSP1_IRQ_61           (30U)
#define CSL_XBAR_INST_DSP1_IRQ_62           (31U)
#define CSL_XBAR_INST_DSP1_IRQ_63           (32U)
#define CSL_XBAR_INST_DSP1_IRQ_64           (33U)
#define CSL_XBAR_INST_DSP1_IRQ_65           (34U)
#define CSL_XBAR_INST_DSP1_IRQ_66           (35U)
#define CSL_XBAR_INST_DSP1_IRQ_67           (36U)
#define CSL_XBAR_INST_DSP1_IRQ_68           (37U)
#define CSL_XBAR_INST_DSP1_IRQ_69           (38U)
#define CSL_XBAR_INST_DSP1_IRQ_70           (39U)
#define CSL_XBAR_INST_DSP1_IRQ_71           (40U)
#define CSL_XBAR_INST_DSP1_IRQ_72           (41U)
#define CSL_XBAR_INST_DSP1_IRQ_73           (42U)
#define CSL_XBAR_INST_DSP1_IRQ_74           (43U)
#define CSL_XBAR_INST_DSP1_IRQ_75           (44U)
#define CSL_XBAR_INST_DSP1_IRQ_76           (45U)
#define CSL_XBAR_INST_DSP1_IRQ_77           (46U)
#define CSL_XBAR_INST_DSP1_IRQ_78           (47U)
#define CSL_XBAR_INST_DSP1_IRQ_79           (48U)
#define CSL_XBAR_INST_DSP1_IRQ_80           (49U)
#define CSL_XBAR_INST_DSP1_IRQ_81           (50U)
#define CSL_XBAR_INST_DSP1_IRQ_82           (51U)
#define CSL_XBAR_INST_DSP1_IRQ_83           (52U)
#define CSL_XBAR_INST_DSP1_IRQ_84           (53U)
#define CSL_XBAR_INST_DSP1_IRQ_85           (54U)
#define CSL_XBAR_INST_DSP1_IRQ_86           (55U)
#define CSL_XBAR_INST_DSP1_IRQ_87           (56U)
#define CSL_XBAR_INST_DSP1_IRQ_88           (57U)
#define CSL_XBAR_INST_DSP1_IRQ_89           (58U)
#define CSL_XBAR_INST_DSP1_IRQ_90           (59U)
#define CSL_XBAR_INST_DSP1_IRQ_91           (60U)
#define CSL_XBAR_INST_DSP1_IRQ_92           (61U)
#define CSL_XBAR_INST_DSP1_IRQ_93           (62U)
#define CSL_XBAR_INST_DSP1_IRQ_94           (63U)
#define CSL_XBAR_INST_DSP1_IRQ_95           (64U)

/* IRQ XBAR Mapping for IPU1 */
#define CSL_XBAR_INST_IPU1_IRQ_23           (1U)
#define CSL_XBAR_INST_IPU1_IRQ_24           (2U)
#define CSL_XBAR_INST_IPU1_IRQ_25           (3U)
#define CSL_XBAR_INST_IPU1_IRQ_26           (4U)
#define CSL_XBAR_INST_IPU1_IRQ_27           (5U)
#define CSL_XBAR_INST_IPU1_IRQ_28           (6U)
#define CSL_XBAR_INST_IPU1_IRQ_29           (7U)
#define CSL_XBAR_INST_IPU1_IRQ_30           (8U)
#define CSL_XBAR_INST_IPU1_IRQ_31           (9U)
#define CSL_XBAR_INST_IPU1_IRQ_32           (10U)
#define CSL_XBAR_INST_IPU1_IRQ_33           (11U)
#define CSL_XBAR_INST_IPU1_IRQ_34           (12U)
#define CSL_XBAR_INST_IPU1_IRQ_35           (13U)
#define CSL_XBAR_INST_IPU1_IRQ_36           (14U)
#define CSL_XBAR_INST_IPU1_IRQ_37           (15U)
#define CSL_XBAR_INST_IPU1_IRQ_38           (16U)
#define CSL_XBAR_INST_IPU1_IRQ_39           (17U)
#define CSL_XBAR_INST_IPU1_IRQ_40           (18U)
#define CSL_XBAR_INST_IPU1_IRQ_41           (19U)
#define CSL_XBAR_INST_IPU1_IRQ_42           (20U)
#define CSL_XBAR_INST_IPU1_IRQ_43           (21U)
#define CSL_XBAR_INST_IPU1_IRQ_44           (22U)
#define CSL_XBAR_INST_IPU1_IRQ_45           (23U)
#define CSL_XBAR_INST_IPU1_IRQ_46           (24U)
#define CSL_XBAR_INST_IPU1_IRQ_47           (25U)
#define CSL_XBAR_INST_IPU1_IRQ_48           (26U)
#define CSL_XBAR_INST_IPU1_IRQ_49           (27U)
#define CSL_XBAR_INST_IPU1_IRQ_50           (28U)
#define CSL_XBAR_INST_IPU1_IRQ_51           (29U)
#define CSL_XBAR_INST_IPU1_IRQ_52           (30U)
#define CSL_XBAR_INST_IPU1_IRQ_53           (31U)
#define CSL_XBAR_INST_IPU1_IRQ_54           (32U)
#define CSL_XBAR_INST_IPU1_IRQ_55           (33U)
#define CSL_XBAR_INST_IPU1_IRQ_56           (34U)
#define CSL_XBAR_INST_IPU1_IRQ_57           (35U)
#define CSL_XBAR_INST_IPU1_IRQ_58           (36U)
#define CSL_XBAR_INST_IPU1_IRQ_59           (37U)
#define CSL_XBAR_INST_IPU1_IRQ_60           (38U)
#define CSL_XBAR_INST_IPU1_IRQ_61           (39U)
#define CSL_XBAR_INST_IPU1_IRQ_62           (40U)
#define CSL_XBAR_INST_IPU1_IRQ_63           (41U)
#define CSL_XBAR_INST_IPU1_IRQ_64           (42U)
#define CSL_XBAR_INST_IPU1_IRQ_65           (43U)
#define CSL_XBAR_INST_IPU1_IRQ_66           (44U)
#define CSL_XBAR_INST_IPU1_IRQ_67           (45U)
#define CSL_XBAR_INST_IPU1_IRQ_68           (46U)
#define CSL_XBAR_INST_IPU1_IRQ_69           (47U)
#define CSL_XBAR_INST_IPU1_IRQ_70           (48U)
#define CSL_XBAR_INST_IPU1_IRQ_71           (49U)
#define CSL_XBAR_INST_IPU1_IRQ_72           (50U)
#define CSL_XBAR_INST_IPU1_IRQ_73           (51U)
#define CSL_XBAR_INST_IPU1_IRQ_74           (52U)
#define CSL_XBAR_INST_IPU1_IRQ_75           (53U)
#define CSL_XBAR_INST_IPU1_IRQ_76           (54U)
#define CSL_XBAR_INST_IPU1_IRQ_77           (55U)
#define CSL_XBAR_INST_IPU1_IRQ_78           (56U)
#define CSL_XBAR_INST_IPU1_IRQ_79           (57U)

/* IRQ XBAR Mapping for IPU2 */
#define CSL_XBAR_INST_IPU2_IRQ_23           (1U)
#define CSL_XBAR_INST_IPU2_IRQ_24           (2U)
#define CSL_XBAR_INST_IPU2_IRQ_25           (3U)
#define CSL_XBAR_INST_IPU2_IRQ_26           (4U)
#define CSL_XBAR_INST_IPU2_IRQ_27           (5U)
#define CSL_XBAR_INST_IPU2_IRQ_28           (6U)
#define CSL_XBAR_INST_IPU2_IRQ_29           (7U)
#define CSL_XBAR_INST_IPU2_IRQ_30           (8U)
#define CSL_XBAR_INST_IPU2_IRQ_31           (9U)
#define CSL_XBAR_INST_IPU2_IRQ_32           (10U)
#define CSL_XBAR_INST_IPU2_IRQ_33           (11U)
#define CSL_XBAR_INST_IPU2_IRQ_34           (12U)
#define CSL_XBAR_INST_IPU2_IRQ_35           (13U)
#define CSL_XBAR_INST_IPU2_IRQ_36           (14U)
#define CSL_XBAR_INST_IPU2_IRQ_37           (15U)
#define CSL_XBAR_INST_IPU2_IRQ_38           (16U)
#define CSL_XBAR_INST_IPU2_IRQ_39           (17U)
#define CSL_XBAR_INST_IPU2_IRQ_40           (18U)
#define CSL_XBAR_INST_IPU2_IRQ_41           (19U)
#define CSL_XBAR_INST_IPU2_IRQ_42           (20U)
#define CSL_XBAR_INST_IPU2_IRQ_43           (21U)
#define CSL_XBAR_INST_IPU2_IRQ_44           (22U)
#define CSL_XBAR_INST_IPU2_IRQ_45           (23U)
#define CSL_XBAR_INST_IPU2_IRQ_46           (24U)
#define CSL_XBAR_INST_IPU2_IRQ_47           (25U)
#define CSL_XBAR_INST_IPU2_IRQ_48           (26U)
#define CSL_XBAR_INST_IPU2_IRQ_49           (27U)
#define CSL_XBAR_INST_IPU2_IRQ_50           (28U)
#define CSL_XBAR_INST_IPU2_IRQ_51           (29U)
#define CSL_XBAR_INST_IPU2_IRQ_52           (30U)
#define CSL_XBAR_INST_IPU2_IRQ_53           (31U)
#define CSL_XBAR_INST_IPU2_IRQ_54           (32U)
#define CSL_XBAR_INST_IPU2_IRQ_55           (33U)
#define CSL_XBAR_INST_IPU2_IRQ_56           (34U)
#define CSL_XBAR_INST_IPU2_IRQ_57           (35U)
#define CSL_XBAR_INST_IPU2_IRQ_58           (36U)
#define CSL_XBAR_INST_IPU2_IRQ_59           (37U)
#define CSL_XBAR_INST_IPU2_IRQ_60           (38U)
#define CSL_XBAR_INST_IPU2_IRQ_61           (39U)
#define CSL_XBAR_INST_IPU2_IRQ_62           (40U)
#define CSL_XBAR_INST_IPU2_IRQ_63           (41U)
#define CSL_XBAR_INST_IPU2_IRQ_64           (42U)
#define CSL_XBAR_INST_IPU2_IRQ_65           (43U)
#define CSL_XBAR_INST_IPU2_IRQ_66           (44U)
#define CSL_XBAR_INST_IPU2_IRQ_67           (45U)
#define CSL_XBAR_INST_IPU2_IRQ_68           (46U)
#define CSL_XBAR_INST_IPU2_IRQ_69           (47U)
#define CSL_XBAR_INST_IPU2_IRQ_70           (48U)
#define CSL_XBAR_INST_IPU2_IRQ_71           (49U)
#define CSL_XBAR_INST_IPU2_IRQ_72           (50U)
#define CSL_XBAR_INST_IPU2_IRQ_73           (51U)
#define CSL_XBAR_INST_IPU2_IRQ_74           (52U)
#define CSL_XBAR_INST_IPU2_IRQ_75           (53U)
#define CSL_XBAR_INST_IPU2_IRQ_76           (54U)
#define CSL_XBAR_INST_IPU2_IRQ_77           (55U)
#define CSL_XBAR_INST_IPU2_IRQ_78           (56U)
#define CSL_XBAR_INST_IPU2_IRQ_79           (57U)

/******************************************************************************
 * DMA XBAR instance mapping for each DMA instances.
 * This is the DMA XBAR instance to which a particular DMA event is
 * mapped. This macro could be used to pass the DMA XBAR instance to the DMA
 * XBAR connect API of starterware.
 ******************************************************************************/
/* DMA XBAR Mapping for System DMA */
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_0     (1U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_1     (2U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_2     (3U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_3     (4U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_4     (5U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_5     (6U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_6     (7U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_7     (8U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_8     (9U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_9     (10U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_10    (11U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_11    (12U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_12    (13U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_13    (14U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_14    (15U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_15    (16U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_16    (17U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_17    (18U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_18    (19U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_19    (20U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_20    (21U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_21    (22U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_22    (23U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_23    (24U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_24    (25U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_25    (26U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_26    (27U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_27    (28U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_28    (29U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_29    (30U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_30    (31U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_31    (32U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_32    (33U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_33    (34U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_34    (35U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_35    (36U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_36    (37U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_37    (38U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_38    (39U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_39    (40U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_40    (41U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_41    (42U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_42    (43U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_43    (44U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_44    (45U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_45    (46U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_46    (47U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_47    (48U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_48    (49U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_49    (50U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_50    (51U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_51    (52U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_52    (53U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_53    (54U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_54    (55U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_55    (56U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_56    (57U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_57    (58U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_58    (59U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_59    (60U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_60    (61U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_61    (62U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_62    (63U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_63    (64U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_64    (65U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_65    (66U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_66    (67U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_67    (68U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_68    (69U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_69    (70U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_70    (71U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_71    (72U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_72    (73U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_73    (74U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_74    (75U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_75    (76U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_76    (77U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_77    (78U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_78    (79U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_79    (80U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_80    (81U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_81    (82U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_82    (83U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_83    (84U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_84    (85U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_85    (86U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_86    (87U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_87    (88U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_88    (89U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_89    (90U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_90    (91U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_91    (92U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_92    (93U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_93    (94U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_94    (95U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_95    (96U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_96    (97U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_97    (98U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_98    (99U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_99    (100U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_100   (101U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_101   (102U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_102   (103U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_103   (104U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_104   (105U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_105   (106U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_106   (107U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_107   (108U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_108   (109U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_109   (110U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_110   (111U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_111   (112U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_112   (113U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_113   (114U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_114   (115U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_115   (116U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_116   (117U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_117   (118U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_118   (119U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_119   (120U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_120   (121U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_121   (122U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_122   (123U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_123   (124U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_124   (125U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_125   (126U)
#define CSL_XBAR_INST_DMA_SYSTEM_DREQ_126   (127U)

/* DMA XBAR Mapping for EDMA3 DMA */
#define CSL_XBAR_INST_DMA_EDMA_DREQ_0       (1U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_1       (2U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_2       (3U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_3       (4U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_4       (5U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_5       (6U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_6       (7U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_7       (8U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_8       (9U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_9       (10U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_10      (11U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_11      (12U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_12      (13U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_13      (14U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_14      (15U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_15      (16U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_16      (17U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_17      (18U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_18      (19U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_19      (20U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_20      (21U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_21      (22U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_22      (23U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_23      (24U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_24      (25U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_25      (26U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_26      (27U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_27      (28U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_28      (29U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_29      (30U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_30      (31U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_31      (32U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_32      (33U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_33      (34U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_34      (35U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_35      (36U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_36      (37U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_37      (38U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_38      (39U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_39      (40U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_40      (41U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_41      (42U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_42      (43U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_43      (44U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_44      (45U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_45      (46U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_46      (47U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_47      (48U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_48      (49U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_49      (50U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_50      (51U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_51      (52U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_52      (53U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_53      (54U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_54      (55U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_55      (56U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_56      (57U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_57      (58U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_58      (59U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_59      (60U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_60      (61U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_61      (62U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_62      (63U)
#define CSL_XBAR_INST_DMA_EDMA_DREQ_63      (64U)

/* DMA XBAR Mapping for DSP1 DMA */
#define CSL_XBAR_INST_DMA_DSP1_DREQ_0       (1U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_1       (2U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_2       (3U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_3       (4U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_4       (5U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_5       (6U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_6       (7U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_7       (8U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_8       (9U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_9       (10U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_10      (11U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_11      (12U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_12      (13U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_13      (14U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_14      (15U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_15      (16U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_16      (17U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_17      (18U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_18      (19U)
#define CSL_XBAR_INST_DMA_DSP1_DREQ_19      (20U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief     API to connect/disconnect any connection between an
 *            interrupt source and a processor in the IRQ XBAR.\n
 *
 * \param     cpuId          It can take one of the value from enum CSL_XbarIrqCpuId
 * \param     irqNumIdx      Crossbar index
 * \param     xbarIrq        It can take one of the interrupt id from enum
 *                           CSL_XbarIrq
 * \return  None
 *
 * \note     To connect,pass corresponding interrupt value from xbar_irq_t.
 *           To disconnect,pass IRQ_XBAR_RSVD as xbarIrq.
**/
void CSL_xbarIrqConfigure(CSL_XbarIrqCpuId cpuId, uint32_t irqNumIdx, CSL_XbarIrq xbarIrq);

/**
 * \brief     API to connect any connection between an dma event source to the
 *            dma channel in the DMA instance.\n
 *
 * \param     cpuId          It can take one of the value from enum CSL_XbarDmaCpuId
 * \param     dmaNumIdx      Crossbar index
 * \param     xbarDma        It can take one of the dma event id from enum
 *                           CSL_XbarDma
 * \return  None
 *
 * \note     To connect,pass corresponding interrupt value from xbar_irq_t.
 *           To disconnect,pass IRQ_XBAR_RSVD as xbarIrq.
**/
void CSL_xbarDmaConfigure(CSL_XbarDmaCpuId cpuId, uint32_t dmaNumIdx, CSL_XbarDma xbarDma);


#ifdef __cplusplus
}
#endif

#endif /* CSL_TDA2EX_DEVICE_INTERRUPT_H_ */
 /** @} */
