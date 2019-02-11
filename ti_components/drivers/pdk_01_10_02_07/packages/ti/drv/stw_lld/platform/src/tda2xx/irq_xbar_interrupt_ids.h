/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file   irq_xbar_interrupt_ids.h
 *
 *  \brief  Definitions used for XBAR interrupt source IDs
 *
 *   This file contains all of the XBAR interrupt source IDs needed to program
 *   an IRQ XBAR instance.
 */

#ifndef IRQ_XBAR_INTR_IDS_H
#define IRQ_XBAR_INTR_IDS_H

#ifdef __cplusplus
extern "C"
{
#endif
/* Enumerated list of interrupt sources into the IRQ_XBAR */
/**
 * \enum xbar_irq_t
 * \brief  Enumeration that contains all possible interrupt source IDs as inputs
 *         to each irq crossbar instance on Vayu
 *
 */
typedef enum {
    IRQ_XBAR_RSVD                      = 0,
    ELM_IRQ                            = 1,
    EXT_SYS_IRQ_1                      = 2,
    CTRL_MODULE_CORE_IRQ_SEC_EVTS      = 3,
    L3_MAIN_IRQ_DBG_ERR                = 4,
    L3_MAIN_IRQ_APP_ERR                = 5,
    PRM_IRQ_MPU                        = 6,
    DMA_SYSTEM_IRQ_0                   = 7,
    DMA_SYSTEM_IRQ_1                   = 8,
    DMA_SYSTEM_IRQ_2                   = 9,
    DMA_SYSTEM_IRQ_3                   = 10,
    L3_MAIN_IRQ_STAT_ALARM             = 11,
    SMARTREFLEX_MPU_IRQ                = 13,
    SMARTREFLEX_CORE_IRQ               = 14,
    GPMC_IRQ                           = 15,
    GPU_IRQ                            = 16,
    DISPC_IRQ                          = 20,
    MAILBOX1_IRQ_USER0                 = 21,
    DSP1_IRQ_MMU0                      = 23,
    GPIO1_IRQ_1                        = 24,
    GPIO2_IRQ_1                        = 25,
    GPIO3_IRQ_1                        = 26,
    GPIO4_IRQ_1                        = 27,
    GPIO5_IRQ_1                        = 28,
    GPIO6_IRQ_1                        = 29,
    GPIO7_IRQ_1                        = 30,
    TIMER1_IRQ                         = 32,
    TIMER2_IRQ                         = 33,
    TIMER3_IRQ                         = 34,
    TIMER4_IRQ                         = 35,
    TIMER5_IRQ                         = 36,
    TIMER6_IRQ                         = 37,
    TIMER7_IRQ                         = 38,
    TIMER8_IRQ                         = 39,
    TIMER9_IRQ                         = 40,
    TIMER10_IRQ                        = 41,
    TIMER11_IRQ                        = 42,
    MCSPI4_IRQ                         = 43,
    SHA2MD5_1_IRQ_S                    = 44,
    FPKA_IRQ                           = 45,
    SHA2MD5_1_IRQ_P                    = 46,
    RNG_IRQ                            = 47,
    SATA_IRQ                           = 49,
    I2C1_IRQ                           = 51,
    I2C2_IRQ                           = 52,
    HDQ1W_IRQ                          = 53,
    I2C5_IRQ                           = 55,
    I2C3_IRQ                           = 56,
    I2C4_IRQ                           = 57,
    AES2_IRQ_S                         = 58,
    AES2_IRQ_P                         = 59,
    MCSPI1_IRQ                         = 60,
    MCSPI2_IRQ                         = 61,
    UART4_IRQ                          = 65,
    UART1_IRQ                          = 67,
    UART2_IRQ                          = 68,
    UART3_IRQ                          = 69,
    PBIAS_IRQ                          = 70,
    USB1_IRQ_INTR0                     = 71,
    USB1_IRQ_INTR1                     = 72,
    USB2_IRQ_INTR0                     = 73,
    AES1_IRQ_S                         = 74,
    WD_TIMER2_IRQ                      = 75,
    DES3DES_IRQ_S                      = 76,
    DES3DES_IRQ_P                      = 77,
    MMC1_IRQ                           = 78,
    AES1_IRQ_P                         = 80,
    MMC2_IRQ                           = 81,
    DEBUGSS_IRQ_CT_UART_TX             = 84,
    DEBUGSS_IRQ_CT_UART_RX             = 85,
    MCSPI3_IRQ                         = 86,
    USB2_IRQ_INTR1                     = 87,
    USB3_IRQ_INTR0                     = 88,
    MMC3_IRQ                           = 89,
    TIMER12_IRQ                        = 90,
    MMC4_IRQ                           = 91,
    HDMI_IRQ                           = 96,
    IVA_IRQ_SYNC_1                     = 98,
    IVA_IRQ_SYNC_0                     = 99,
    UART5_IRQ                          = 100,
    UART6_IRQ                          = 101,
    IVA_IRQ_MAILBOX_0                  = 102,
    McASP1_IRQ_AREVT                   = 103,
    McASP1_IRQ_AXEVT                   = 104,
    EMIF1_IRQ                          = 105,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    EMIF2_IRQ                          = 106,
#endif
    DMM_IRQ                            = 108,
    DMA_CRYPTO_IRQ_0                   = 110,
    DMA_CRYPTO_IRQ_1                   = 111,
    DMA_CRYPTO_IRQ_2                   = 112,
    DMA_CRYPTO_IRQ_3                   = 113,
    EXT_SYS_IRQ_2                      = 114,
    KBD_IRQ                            = 115,
    GPIO8_IRQ_1                        = 116,
#if defined (SOC_TDA2EX)
    CAL_IRQ                            = 119,
#endif
    BB2D_IRQ                           = 120,
    CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 121,
    IVA_IRQ_MAILBOX_2                  = 132,
    PRM_IRQ_IPU1                       = 133,
    MAILBOX1_IRQ_USER2                 = 134,
    MAILBOX1_IRQ_USER1                 = 135,
    IVA_IRQ_MAILBOX_1                  = 136,
    PRM_IRQ_DSP1                       = 137,
    GPIO1_IRQ_2                        = 138,
    GPIO2_IRQ_2                        = 139,
    GPIO3_IRQ_2                        = 140,
    GPIO4_IRQ_2                        = 141,
    GPIO5_IRQ_2                        = 142,
    GPIO6_IRQ_2                        = 143,
    DSP1_IRQ_MMU1                      = 145,
#if defined (SOC_TDA2EX)
    /* No DSP2 in TDA2EX */
#else
    DSP2_IRQ_MMU0                      = 146,
    DSP2_IRQ_MMU1                      = 147,
#endif
    McASP2_IRQ_AREVT                   = 148,
    McASP2_IRQ_AXEVT                   = 149,
    McASP3_IRQ_AREVT                   = 150,
    McASP3_IRQ_AXEVT                   = 151,
    McASP4_IRQ_AREVT                   = 152,
    McASP4_IRQ_AXEVT                   = 153,
    McASP5_IRQ_AREVT                   = 154,
    McASP5_IRQ_AXEVT                   = 155,
    McASP6_IRQ_AREVT                   = 156,
    McASP6_IRQ_AXEVT                   = 157,
    McASP7_IRQ_AREVT                   = 158,
    McASP7_IRQ_AXEVT                   = 159,
    McASP8_IRQ_AREVT                   = 160,
    McASP8_IRQ_AXEVT                   = 161,
    SHA2MD5_2_IRQ_S                    = 162,
    SHA2MD5_2_IRQ_P                    = 163,
    OCMC_RAM1_IRQ                      = 164,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    OCMC_RAM2_IRQ                      = 165,
    OCMC_RAM3_IRQ                      = 166,
    EVE1_IRQ_OUT0                      = 168,
    EVE1_IRQ_OUT1                      = 169,
    EVE1_IRQ_OUT2                      = 170,
    EVE1_IRQ_OUT3                      = 171,
    EVE2_IRQ_OUT0                      = 172,
    EVE2_IRQ_OUT1                      = 173,
    EVE2_IRQ_OUT2                      = 174,
    EVE2_IRQ_OUT3                      = 175,
    EVE3_IRQ_OUT0                      = 176,
    EVE3_IRQ_OUT1                      = 177,
    EVE3_IRQ_OUT2                      = 178,
    EVE3_IRQ_OUT3                      = 179,
    EVE4_IRQ_OUT0                      = 180,
    EVE4_IRQ_OUT1                      = 181,
    EVE4_IRQ_OUT2                      = 182,
    EVE4_IRQ_OUT3                      = 183,
#endif
    PRUSS1_IRQ_HOST0                   = 184,
    PRUSS1_IRQ_HOST1                   = 185,
    PRUSS1_IRQ_HOST2                   = 186,
    PRUSS1_IRQ_HOST3                   = 187,
    PRUSS1_IRQ_HOST4                   = 188,
    PRUSS1_IRQ_HOST5                   = 189,
    PRUSS1_IRQ_HOST6                   = 190,
    PRUSS1_IRQ_HOST7                   = 191,
    PRUSS1_IRQ_HOST8                   = 192,
    PRUSS1_IRQ_HOST9                   = 193,
    PRUSS2_IRQ_HOST0                   = 194,
    PRUSS2_IRQ_HOST1                   = 195,
    PRUSS2_IRQ_HOST2                   = 196,
    PRUSS2_IRQ_HOST3                   = 197,
    PRUSS2_IRQ_HOST4                   = 198,
    PRUSS2_IRQ_HOST5                   = 199,
    PRUSS2_IRQ_HOST6                   = 200,
    PRUSS2_IRQ_HOST7                   = 201,
    PRUSS2_IRQ_HOST8                   = 202,
    PRUSS2_IRQ_HOST9                   = 203,
    PWMSS1_IRQ_ePWM0_TZINT             = 204,
    PWMSS2_IRQ_ePWM1_TZINT             = 205,
    PWMSS3_IRQ_ePWM2_TZINT             = 206,
    PWMSS1_IRQ_ePWM0INT                = 207,
    PWMSS2_IRQ_ePWM1INT                = 208,
    PWMSS3_IRQ_ePWM2INT                = 209,
    PWMSS1_IRQ_eQEP0INT                = 210,
    PWMSS2_IRQ_eQEP1INT                = 211,
    PWMSS3_IRQ_eQEP2INT                = 212,
    PWMSS1_IRQ_eCAP0INT                = 213,
    PWMSS2_IRQ_eCAP1INT                = 214,
    PWMSS3_IRQ_eCAP2INT                = 215,
    RTC_SS_IRQ_TIMER                   = 216,
    RTC_SS_IRQ_ALARM                   = 217,
    UART7_IRQ                          = 218,
    UART8_IRQ                          = 219,
    UART9_IRQ                          = 220,
    UART10_IRQ                         = 221,
    DCAN1_IRQ_INT0                     = 222,
    DCAN1_IRQ_INT1                     = 223,
    DCAN1_IRQ_PARITY                   = 224,
    DCAN2_IRQ_INT0                     = 225,
    DCAN2_IRQ_INT1                     = 226,
    DCAN2_IRQ_PARITY                   = 227,
    MLB_IRQ_SYS_INT0                   = 228,
    MLB_IRQ_SYS_INT1                   = 229,
    VCP1_IRQ_INT                       = 230,
    VCP2_IRQ_INT                       = 231,
    PCIe_SS1_IRQ_INT0                  = 232,
    PCIe_SS1_IRQ_INT1                  = 233,
    PCIe_SS1_IRQ_INT2                  = 234,
    PCIe_SS1_IRQ_INT3                  = 235,
    SPARE_TSC_ADC_IRQ_GENINT           = 236,
    MAILBOX2_IRQ_USER0                 = 237,
    MAILBOX2_IRQ_USER1                 = 238,
    MAILBOX2_IRQ_USER2                 = 239,
    MAILBOX2_IRQ_USER3                 = 240,
    MAILBOX3_IRQ_USER0                 = 241,
    MAILBOX3_IRQ_USER1                 = 242,
    MAILBOX3_IRQ_USER2                 = 243,
    MAILBOX3_IRQ_USER3                 = 244,
    MAILBOX4_IRQ_USER0                 = 245,
    MAILBOX4_IRQ_USER1                 = 246,
    MAILBOX4_IRQ_USER2                 = 247,
    MAILBOX4_IRQ_USER3                 = 248,
    MAILBOX5_IRQ_USER0                 = 249,
    MAILBOX5_IRQ_USER1                 = 250,
    MAILBOX5_IRQ_USER2                 = 251,
    MAILBOX5_IRQ_USER3                 = 252,
    MAILBOX6_IRQ_USER0                 = 253,
    MAILBOX6_IRQ_USER1                 = 254,
    MAILBOX6_IRQ_USER2                 = 255,
    MAILBOX6_IRQ_USER3                 = 256,
    MAILBOX7_IRQ_USER0                 = 257,
    MAILBOX7_IRQ_USER1                 = 258,
    MAILBOX7_IRQ_USER2                 = 259,
    MAILBOX7_IRQ_USER3                 = 260,
    MAILBOX8_IRQ_USER0                 = 261,
    MAILBOX8_IRQ_USER1                 = 262,
    MAILBOX8_IRQ_USER2                 = 263,
    MAILBOX8_IRQ_USER3                 = 264,
    MAILBOX9_IRQ_USER0                 = 265,
    MAILBOX9_IRQ_USER1                 = 266,
    MAILBOX9_IRQ_USER2                 = 267,
    MAILBOX9_IRQ_USER3                 = 268,
    MAILBOX10_IRQ_USER0                = 269,
    MAILBOX10_IRQ_USER1                = 270,
    MAILBOX10_IRQ_USER2                = 271,
    MAILBOX10_IRQ_USER3                = 272,
    MAILBOX11_IRQ_USER0                = 273,
    MAILBOX11_IRQ_USER1                = 274,
    MAILBOX11_IRQ_USER2                = 275,
    MAILBOX11_IRQ_USER3                = 276,
    MAILBOX12_IRQ_USER0                = 277,
    MAILBOX12_IRQ_USER1                = 278,
    MAILBOX12_IRQ_USER2                = 279,
    MAILBOX12_IRQ_USER3                = 280,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    EVE1_IRQ_TPCC_REGION1              = 281,
    EVE1_IRQ_TPCC_REGION2              = 282,
    EVE1_IRQ_TPCC_REGION3              = 283,
    EVE1_IRQ_MBX0_USER1                = 284,
    EVE1_IRQ_MBX0_USER2                = 285,
    EVE1_IRQ_MBX0_USER3                = 286,
    EVE1_IRQ_MBX1_USER1                = 287,
    EVE1_IRQ_MBX1_USER2                = 288,
    EVE1_IRQ_MBX1_USER3                = 289,
    EVE2_IRQ_TPCC_REGION1              = 290,
    EVE2_IRQ_TPCC_REGION2              = 291,
    EVE2_IRQ_TPCC_REGION3              = 292,
    EVE2_IRQ_MBX0_USER1                = 293,
    EVE2_IRQ_MBX0_USER2                = 294,
    EVE2_IRQ_MBX0_USER3                = 295,
    EVE2_IRQ_MBX1_USER1                = 296,
    EVE2_IRQ_MBX1_USER2                = 297,
    EVE2_IRQ_MBX1_USER3                = 298,
    EVE3_IRQ_TPCC_REGION1              = 299,
    EVE3_IRQ_TPCC_REGION2              = 300,
    EVE3_IRQ_TPCC_REGION3              = 301,
    EVE3_IRQ_MBX0_USER1                = 302,
    EVE3_IRQ_MBX0_USER2                = 303,
    EVE3_IRQ_MBX0_USER3                = 304,
    EVE3_IRQ_MBX1_USER1                = 305,
    EVE3_IRQ_MBX1_USER2                = 306,
    EVE3_IRQ_MBX1_USER3                = 307,
    EVE4_IRQ_TPCC_REGION1              = 308,
    EVE4_IRQ_TPCC_REGION2              = 309,
    EVE4_IRQ_TPCC_REGION3              = 310,
    EVE4_IRQ_MBX0_USER1                = 311,
    EVE4_IRQ_MBX0_USER2                = 312,
    EVE4_IRQ_MBX0_USER3                = 313,
    EVE4_IRQ_MBX1_USER1                = 314,
    EVE4_IRQ_MBX1_USER2                = 315,
    EVE4_IRQ_MBX1_USER3                = 316,
#endif
    DSP1_IRQ_TPCC_ERR                  = 317,
    DSP1_IRQ_TPCC_GLOBAL               = 318,
    DSP1_IRQ_TPCC_REGION0              = 319,
    DSP1_IRQ_TPCC_REGION1              = 320,
    DSP1_IRQ_TPCC_REGION2              = 321,
    DSP1_IRQ_TPCC_REGION3              = 322,
    DSP1_IRQ_TPCC_REGION4              = 323,
    DSP1_IRQ_TPCC_REGION5              = 324,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    DSP2_IRQ_TPCC_ERR                  = 325,
    DSP2_IRQ_TPCC_GLOBAL               = 326,
    DSP2_IRQ_TPCC_REGION0              = 327,
    DSP2_IRQ_TPCC_REGION1              = 328,
    DSP2_IRQ_TPCC_REGION2              = 329,
    DSP2_IRQ_TPCC_REGION3              = 330,
    DSP2_IRQ_TPCC_REGION4              = 331,
    DSP2_IRQ_TPCC_REGION5              = 332,
#endif
    MMU1_IRQ                           = 333,
    GMAC_SW_IRQ_RX_THRESH_PULSE        = 334,
    GMAC_SW_IRQ_RX_PULSE               = 335,
    GMAC_SW_IRQ_TX_PULSE               = 336,
    GMAC_SW_IRQ_MISC_PULSE             = 337,
    WD_TIMER1_IRQ                      = 338,
    TIMER13_IRQ                        = 339,
    TIMER14_IRQ                        = 340,
    TIMER15_IRQ                        = 341,
    TIMER16_IRQ                        = 342,
    QSPI_IRQ                           = 343,
    USB3_IRQ_INTR1                     = 344,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    USB4_IRQ_INTR0                     = 345,
    USB4_IRQ_INTR1                     = 346,
#endif
    GPIO7_IRQ_2                        = 347,
    GPIO8_IRQ_2                        = 348,
    VIP1_IRQ                           = 351,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    VIP2_IRQ                           = 352,
    VIP3_IRQ                           = 353,
#endif
    VPE_IRQ                            = 354,
    PCIe_SS2_IRQ_INT0                  = 355,
    PCIe_SS2_IRQ_INT1                  = 356,
    PCIe_SS2_IRQ_INT2                  = 357,
    PCIe_SS2_IRQ_INT3                  = 358,
    EDMA_TPCC_IRQ_ERR                  = 359,
    EDMA_TPCC_IRQ_MP                   = 360,
    EDMA_TPCC_IRQ_REGION0              = 361,
    EDMA_TPCC_IRQ_REGION1              = 362,
    EDMA_TPCC_IRQ_REGION2              = 363,
    EDMA_TPCC_IRQ_REGION3              = 364,
    EDMA_TPCC_IRQ_REGION4              = 365,
    EDMA_TPCC_IRQ_REGION5              = 366,
    EDMA_TPCC_IRQ_REGION6              = 367,
    EDMA_TPCC_IRQ_REGION7              = 368,
    MMU2_IRQ                           = 369,
    EDMA_TC0_IRQ_ERR                   = 370,
    EDMA_TC1_IRQ_ERR                   = 371,
    OCMC_RAM1_IRQ_CBUF                 = 372,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    OCMC_RAM2_IRQ_CBUF                 = 373,
    OCMC_RAM3_IRQ_CBUF                 = 374,
#endif
    DSP1_IRQ_TPCC_REGION6              = 375,
    DSP1_IRQ_TPCC_REGION7              = 376,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    DSP2_IRQ_TPCC_REGION6              = 377,
    DSP2_IRQ_TPCC_REGION7              = 378,
#endif
    MAILBOX13_IRQ_USER0                = 379,
    MAILBOX13_IRQ_USER1                = 380,
    MAILBOX13_IRQ_USER2                = 381,
    MAILBOX13_IRQ_USER3                = 382,
    SMARTREFLEX_DSPEVE_IRQ             = 383,
    SMARTREFLEX_GPU_IRQ                = 384,
    SMARTREFLEX_IVA_IRQ                = 385,
    PRM_IRQ_IPU2                       = 386,
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
    PRM_IRQ_DSP2                       = 387,
    PRM_IRQ_EVE1                       = 388,
    PRM_IRQ_EVE2                       = 389,
    PRM_IRQ_EVE3                       = 390,
    PRM_IRQ_EVE4                       = 391,
#endif
#if defined (SOC_TDA2EX)
    I2C6_IRQ                           = 402,
#endif
    IRQ_XBAR_RSVD1                     = 403
} xbar_irq_t;

#define MPU_IRQ_XBAR_COUNT      0x98U
#define IPU1_IRQ_XBAR_COUNT     0x39U
#define DSP1_IRQ_XBAR_COUNT     0x40U
#if defined (SOC_TDA2EX)
    /* Not applicable */
#else
#define DSP2_IRQ_XBAR_COUNT     0x40U
#define EVE1_IRQ_XBAR_COUNT     0x08U
#define EVE2_IRQ_XBAR_COUNT     0x08U
#define EVE3_IRQ_XBAR_COUNT     0x08U
#define EVE4_IRQ_XBAR_COUNT     0x08U
#endif
#define PRUSS1_IRQ_XBAR_COUNT   0x20U
#define IRQ_XBAR_MAX_COUNT      0x1A4U

#ifdef __cplusplus
}
#endif
#endif
