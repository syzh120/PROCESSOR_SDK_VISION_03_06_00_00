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
    IRQ_XBAR_RSVD = 0,
    ELM_IRQ       = 1,
    EXT_SYS_IRQ_1 = 2,
    CTRL_MODULE_CORE_IRQ_SEC_EVTS = 3,
    L3_MAIN_IRQ_DBG_ERR           = 4,
    L3_MAIN_IRQ_APP_ERR           = 5,
    PRM_IRQ_MPU                        = 6,
    L3_MAIN_IRQ_STAT_ALARM             = 11,
    SMARTREFLEX_CORE_IRQ               = 14,
    GPMC_IRQ                           = 15,
    DISPC_IRQ                          = 20,
    MAILBOX1_IRQ_USER0                 = 21,
    DSP1_IRQ_MMU0                      = 23,
    GPIO1_IRQ_1                        = 24,
    GPIO2_IRQ_1                        = 25,
    GPIO3_IRQ_1                        = 26,
    GPIO4_IRQ_1                        = 27,
    TIMER1_IRQ                         = 32,
    TIMER2_IRQ                         = 33,
    TIMER3_IRQ                         = 34,
    TIMER4_IRQ                         = 35,
    TIMER5_IRQ                         = 36,
    TIMER6_IRQ                         = 37,
    TIMER7_IRQ                         = 38,
    TIMER8_IRQ                         = 39,
    MCSPI4_IRQ                         = 43,
    I2C1_IRQ                           = 51,
    I2C2_IRQ                           = 52,
    MCSPI1_IRQ                         = 60,
    MCSPI2_IRQ                         = 61,
    UART1_IRQ                          = 67,
    UART2_IRQ                          = 68,
    UART3_IRQ                          = 69,
    RTI2_IRQ_WWD                       = 75,
    DEBUGSS_IRQ_CT_UART_RX             = 85,
    MCSPI3_IRQ                         = 86,
    MMC_IRQ                            = 91,
    McASP1_IRQ_AREVT                   = 103,
    McASP1_IRQ_AXEVT                   = 104,
    EMIF1_IRQ                          = 105,
    EXT_SYS_IRQ_2                      = 114,
    CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 121,
    ISS_IRQ_INT0                       = 126,
    PRM_IRQ_IPU1                       = 133,
    MAILBOX1_IRQ_USER2                 = 134,
    MAILBOX1_IRQ_USER1                 = 135,
    PRM_IRQ_DSP1                       = 137,
    GPIO1_IRQ_2                        = 138,
    GPIO2_IRQ_2                        = 139,
    GPIO3_IRQ_2                        = 140,
    GPIO4_IRQ_2                        = 141,
    DSP1_IRQ_MMU1                      = 145,
    DSP2_IRQ_MMU0                      = 146,
    DSP2_IRQ_MMU1                      = 147,
    OCMC_RAM1_IRQ                      = 164,
    CRC_IRQ_CH1_CPR_COMP               = 167,
    EVE1_IRQ_OUT0                      = 168,
    EVE1_IRQ_OUT1                      = 169,
    EVE1_IRQ_OUT2                      = 170,
    EVE1_IRQ_OUT3                      = 171,
    SD_DAC_IRQ_TVINT                   = 184,
    SD_DAC_IRQ_TVSHORT                 = 185,
    ISS_IRQ_INT1                       = 194,
    ISS_IRQ_INT2                       = 195,
    PWMSS1_IRQ_ePWM0_TZINT             = 204,
    PWMSS1_IRQ_ePWM0INT                = 207,
    PWMSS1_IRQ_eQEP0INT                = 210,
    PWMSS1_IRQ_eCAP0INT                = 213,
    ISS_IRQ_INT3                       = 216,
    DCAN1_IRQ_INT0                     = 222,
    DCAN1_IRQ_INT1                     = 223,
    DCAN1_IRQ_PARITY                   = 224,
    DCAN2_IRQ_INT0                     = 225, /* Only valid for TDA3xx SR1.0 */
    MCAN_IRQ_INT0                      = 225, /* Only valid for TDA3xx SR2.0 and above */
    DCAN2_IRQ_INT1                     = 226, /* Only valid for TDA3xx SR1.0 */
    MCAN_IRQ_INT1                      = 226, /* Only valid for TDA3xx SR2.0 and above */
    DCAN2_IRQ_PARITY                   = 227, /* Only valid for TDA3xx SR1.0 */
    MCAN_IRQ_PARITY                    = 227, /* Only valid for TDA3xx SR2.0 and above */
    DCC1_IRQ_ERROR                     = 234,
    DCC1_IRQ_DONE                      = 235,
    TSC_ADC_IRQ_GENINT                 = 236,
    MAILBOX2_IRQ_USER0                 = 237,
    MAILBOX2_IRQ_USER1                 = 238,
    MAILBOX2_IRQ_USER2                 = 239,
    MAILBOX2_IRQ_USER3                 = 240,
    EVE1_IRQ_TPCC_REGION1              = 281,
    EVE1_IRQ_TPCC_REGION2              = 282,
    EVE1_IRQ_TPCC_REGION3              = 283,
    EVE1_IRQ_MBX0_USER1                = 284,
    EVE1_IRQ_MBX0_USER2                = 285,
    EVE1_IRQ_MBX0_USER3                = 286,
    EVE1_IRQ_MBX1_USER1                = 287,
    EVE1_IRQ_MBX1_USER2                = 288,
    EVE1_IRQ_MBX1_USER3                = 289,
    DSP1_IRQ_TPCC_ERR                  = 317,
    DSP1_IRQ_TPCC_GLOBAL               = 318,
    DSP1_IRQ_TPCC_REGION0              = 319,
    DSP1_IRQ_TPCC_REGION1              = 320,
    DSP1_IRQ_TPCC_REGION2              = 321,
    DSP1_IRQ_TPCC_REGION3              = 322,
    DSP1_IRQ_TPCC_REGION4              = 323,
    DSP1_IRQ_TPCC_REGION5              = 324,
    DSP2_IRQ_TPCC_ERR                  = 325,
    DSP2_IRQ_TPCC_GLOBAL               = 326,
    DSP2_IRQ_TPCC_REGION0              = 327,
    DSP2_IRQ_TPCC_REGION1              = 328,
    DSP2_IRQ_TPCC_REGION2              = 329,
    DSP2_IRQ_TPCC_REGION3              = 330,
    DSP2_IRQ_TPCC_REGION4              = 331,
    DSP2_IRQ_TPCC_REGION5              = 332,
    MMU1_IRQ                           = 333,
    GMAC_SW_IRQ_RX_THRESH_PULSE        = 334,
    GMAC_SW_IRQ_RX_PULSE               = 335,
    GMAC_SW_IRQ_TX_PULSE               = 336,
    GMAC_SW_IRQ_MISC_PULSE             = 337,
    RTI1_IRQ_WWD                       = 338,
    QSPI_IRQ                           = 343,
    ISS_IRQ_INT4                       = 349,
    ISS_IRQ_INT5                       = 350,
    VIP1_IRQ                           = 351,
    ESM_IRQ_HIGH                       = 357,
    ESM_IRQ_LOW                        = 358,
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
    EDMA_TC0_IRQ_ERR                   = 370,
    EDMA_TC1_IRQ_ERR                   = 371,
    OCMC_RAM1_IRQ_CBUF                 = 372,
    DSP1_IRQ_TPCC_REGION6              = 375,
    DSP1_IRQ_TPCC_REGION7              = 376,
    DSP2_IRQ_TPCC_REGION6              = 377,
    DSP2_IRQ_TPCC_REGION7              = 378,
    SMARTREFLEX_DSPEVE_IRQ             = 383,
    PRM_IRQ_IPU2                       = 386,
    PRM_IRQ_DSP2                       = 387,
    PRM_IRQ_EVE1                       = 388,
    PRM_IRQ_EVE2                       = 389,
    PRM_IRQ_EVE3                       = 390,
    PRM_IRQ_EVE4                       = 391,
    VIP1_IRQ_2                         = 392,
    IPU1_IRQ_MMU                       = 395,
    EVE1_IRQ_TPCC_REGION4              = 398,
    RTI1_IRQ_INT0                      = 402,
    RTI1_IRQ_INT1                      = 403,
    TESOC_IRQ_DONE                     = 404,
    RTI3_IRQ_WWD                       = 405,
    RTI4_IRQ_WWD                       = 406,
    RTI5_IRQ_WWD                       = 407,
    RTI1_IRQ_INT2                      = 408,
    RTI1_IRQ_INT3                      = 409,
    RTI1_IRQ_OVL0                      = 410,
    RTI1_IRQ_OVL1                      = 411,
    RTI2_IRQ_INT0                      = 412,
    DCC2_IRQ_ERROR                     = 413,
    DCC2_IRQ_DONE                      = 414,
    DCC3_IRQ_ERROR                     = 415,
    DCC3_IRQ_DONE                      = 416,
    DCC4_IRQ_ERROR                     = 417,
    DCC4_IRQ_DONE                      = 418,
    DCC5_IRQ_ERROR                     = 419,
    DCC5_IRQ_DONE                      = 420,
    DCC6_IRQ_ERROR                     = 421,
    DCC6_IRQ_DONE                      = 422,
    DCC7_IRQ_ERROR                     = 423,
    DCC7_IRQ_DONE                      = 424,
    RTI2_IRQ_INT1                      = 425,
    RTI2_IRQ_INT2                      = 426,
    RTI2_IRQ_INT3                      = 427,
    RTI2_IRQ_OVL0                      = 428,
    RTI2_IRQ_OVL1                      = 429,
    RTI3_IRQ_INT0                      = 430,
    RTI3_IRQ_INT1                      = 431,
    RTI3_IRQ_INT2                      = 432,
    RTI3_IRQ_INT3                      = 433,
    RTI3_IRQ_OVL0                      = 434,
    RTI3_IRQ_OVL1                      = 435,
    RTI4_IRQ_INT0                      = 436,
    RTI4_IRQ_INT1                      = 437,
    RTI4_IRQ_INT2                      = 438,
    RTI4_IRQ_INT3                      = 439,
    RTI4_IRQ_OVL0                      = 440,
    RTI4_IRQ_OVL1                      = 441,
    RTI5_IRQ_INT0                      = 442,
    RTI5_IRQ_INT1                      = 443,
    RTI5_IRQ_INT2                      = 444,
    RTI5_IRQ_INT3                      = 445,
    RTI5_IRQ_OVL                       = 446,
    RTI5_IRQ_OVL1                      = 447,
    RTI1_IRQ_TBINT                     = 448,
    RTI2_IRQ_TBINT                     = 449,
    RTI3_IRQ_TBINT                     = 450,
    RTI4_IRQ_TBINT                     = 451,
    RTI5_IRQ_TBINT                     = 452,
    MCASP2_IRQ_AREVT                   = 453, /* Only valid for TDA3xx SR2.0 and above */
    MCASP2_IRQ_AXEVT                   = 454, /* Only valid for TDA3xx SR2.0 and above */
    MCASP3_IRQ_AREVT                   = 455, /* Only valid for TDA3xx SR2.0 and above */
    MCASP3_IRQ_AXEVT                   = 456, /* Only valid for TDA3xx SR2.0 and above */
    MCAN_IRQ_TS                        = 457  /* Only valid for TDA3xx SR2.0 and above */
} xbar_irq_t;

#define IPU1_IRQ_XBAR_COUNT     0x39U
#define DSP1_IRQ_XBAR_COUNT     0x40U
#define DSP2_IRQ_XBAR_COUNT     0x40U
#define EVE1_IRQ_XBAR_COUNT     0x08U
#define IRQ_XBAR_MAX_COUNT      0x1CDU

#ifdef __cplusplus
}
#endif
#endif
