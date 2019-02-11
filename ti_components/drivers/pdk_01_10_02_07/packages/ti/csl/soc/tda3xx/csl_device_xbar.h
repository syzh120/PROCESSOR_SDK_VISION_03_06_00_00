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
 *  \ingroup SOC_TDA3XX
 *  \defgroup SOC_DEVICE_XBAR Device Xbar Defines
 *
 *  @{
 */
/**
 *  \file   tda3xx/csl_device_xbar.h
 *
 *  \brief  This file contains the XBAR related enums and macros definitions
 *          for the TDA3XX
 */

#ifndef CSL_TDA3XX_DEVICE_INTERRUPT_H
#define CSL_TDA3XX_DEVICE_INTERRUPT_H

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
    CSL_XBAR_L3_MAIN_IRQ_STAT_ALARM             = 11,
    CSL_XBAR_SMARTREFLEX_CORE_IRQ               = 14,
    CSL_XBAR_GPMC_IRQ                           = 15,
    CSL_XBAR_DISPC_IRQ                          = 20,
    CSL_XBAR_MAILBOX1_IRQ_USER0                 = 21,
    CSL_XBAR_DSP1_IRQ_MMU0                      = 23,
    CSL_XBAR_GPIO1_IRQ_1                        = 24,
    CSL_XBAR_GPIO2_IRQ_1                        = 25,
    CSL_XBAR_GPIO3_IRQ_1                        = 26,
    CSL_XBAR_GPIO4_IRQ_1                        = 27,
    CSL_XBAR_TIMER1_IRQ                         = 32,
    CSL_XBAR_TIMER2_IRQ                         = 33,
    CSL_XBAR_TIMER3_IRQ                         = 34,
    CSL_XBAR_TIMER4_IRQ                         = 35,
    CSL_XBAR_TIMER5_IRQ                         = 36,
    CSL_XBAR_TIMER6_IRQ                         = 37,
    CSL_XBAR_TIMER7_IRQ                         = 38,
    CSL_XBAR_TIMER8_IRQ                         = 39,
    CSL_XBAR_MCSPI4_IRQ                         = 43,
    CSL_XBAR_I2C1_IRQ                           = 51,
    CSL_XBAR_I2C2_IRQ                           = 52,
    CSL_XBAR_MCSPI1_IRQ                         = 60,
    CSL_XBAR_MCSPI2_IRQ                         = 61,
    CSL_XBAR_UART1_IRQ                          = 67,
    CSL_XBAR_UART2_IRQ                          = 68,
    CSL_XBAR_UART3_IRQ                          = 69,
    CSL_XBAR_RTI2_IRQ_WWD                       = 75,
    CSL_XBAR_DEBUGSS_IRQ_CT_UART_RX             = 85,
    CSL_XBAR_MCSPI3_IRQ                         = 86,
    CSL_XBAR_MMC_IRQ                            = 91,
    CSL_XBAR_McASP1_IRQ_AREVT                   = 103,
    CSL_XBAR_McASP1_IRQ_AXEVT                   = 104,
    CSL_XBAR_EMIF1_IRQ                          = 105,
    CSL_XBAR_EXT_SYS_IRQ_2                      = 114,
    CSL_XBAR_CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 121,
    CSL_XBAR_ISS_IRQ_INT0                       = 126,
    CSL_XBAR_PRM_IRQ_IPU1                       = 133,
    CSL_XBAR_MAILBOX1_IRQ_USER2                 = 134,
    CSL_XBAR_MAILBOX1_IRQ_USER1                 = 135,
    CSL_XBAR_PRM_IRQ_DSP1                       = 137,
    CSL_XBAR_GPIO1_IRQ_2                        = 138,
    CSL_XBAR_GPIO2_IRQ_2                        = 139,
    CSL_XBAR_GPIO3_IRQ_2                        = 140,
    CSL_XBAR_GPIO4_IRQ_2                        = 141,
    CSL_XBAR_DSP1_IRQ_MMU1                      = 145,
    CSL_XBAR_DSP2_IRQ_MMU0                      = 146,
    CSL_XBAR_DSP2_IRQ_MMU1                      = 147,
    CSL_XBAR_OCMC_RAM1_IRQ                      = 164,
    CSL_XBAR_CRC_IRQ_CH1_CPR_COMP               = 167,
    CSL_XBAR_EVE1_IRQ_OUT0                      = 168,
    CSL_XBAR_EVE1_IRQ_OUT1                      = 169,
    CSL_XBAR_EVE1_IRQ_OUT2                      = 170,
    CSL_XBAR_EVE1_IRQ_OUT3                      = 171,
    CSL_XBAR_SD_DAC_IRQ_TVINT                   = 184,
    CSL_XBAR_SD_DAC_IRQ_TVSHORT                 = 185,
    CSL_XBAR_ISS_IRQ_INT1                       = 194,
    CSL_XBAR_ISS_IRQ_INT2                       = 195,
    CSL_XBAR_PWMSS1_IRQ_ePWM0_TZINT             = 204,
    CSL_XBAR_PWMSS1_IRQ_ePWM0INT                = 207,
    CSL_XBAR_PWMSS1_IRQ_eQEP0INT                = 210,
    CSL_XBAR_PWMSS1_IRQ_eCAP0INT                = 213,
    CSL_XBAR_ISS_IRQ_INT3                       = 216,
    CSL_XBAR_DCAN1_IRQ_INT0                     = 222,
    CSL_XBAR_DCAN1_IRQ_INT1                     = 223,
    CSL_XBAR_DCAN1_IRQ_PARITY                   = 224,
    CSL_XBAR_DCAN2_IRQ_INT0                     = 225,  /* Only for PG1.0 */
    CSL_XBAR_MCAN_IRQ_INT0                      = 225,  /* PG2.0 and above */
    CSL_XBAR_DCAN2_IRQ_INT1                     = 226,  /* Only for PG1.0 */
    CSL_XBAR_MCAN_IRQ_INT1                      = 226,  /* PG2.0 and above */
    CSL_XBAR_DCAN2_IRQ_PARITY                   = 227,  /* Only for PG1.0 */
    CSL_XBAR_MCAN_IRQ_PARITY                    = 227,  /* PG2.0 and above */
    CSL_XBAR_DCC1_IRQ_ERROR                     = 234,
    CSL_XBAR_DCC1_IRQ_DONE                      = 235,
    CSL_XBAR_TSC_ADC_IRQ_GENINT                 = 236,
    CSL_XBAR_MAILBOX2_IRQ_USER0                 = 237,
    CSL_XBAR_MAILBOX2_IRQ_USER1                 = 238,
    CSL_XBAR_MAILBOX2_IRQ_USER2                 = 239,
    CSL_XBAR_MAILBOX2_IRQ_USER3                 = 240,
    CSL_XBAR_EVE1_IRQ_TPCC_REGION1              = 281,
    CSL_XBAR_EVE1_IRQ_TPCC_REGION2              = 282,
    CSL_XBAR_EVE1_IRQ_TPCC_REGION3              = 283,
    CSL_XBAR_EVE1_IRQ_MBX0_USER1                = 284,
    CSL_XBAR_EVE1_IRQ_MBX0_USER2                = 285,
    CSL_XBAR_EVE1_IRQ_MBX0_USER3                = 286,
    CSL_XBAR_EVE1_IRQ_MBX1_USER1                = 287,
    CSL_XBAR_EVE1_IRQ_MBX1_USER2                = 288,
    CSL_XBAR_EVE1_IRQ_MBX1_USER3                = 289,
    CSL_XBAR_DSP1_IRQ_TPCC_ERR                  = 317,
    CSL_XBAR_DSP1_IRQ_TPCC_GLOBAL               = 318,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION0              = 319,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION1              = 320,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION2              = 321,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION3              = 322,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION4              = 323,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION5              = 324,
    CSL_XBAR_DSP2_IRQ_TPCC_ERR                  = 325,
    CSL_XBAR_DSP2_IRQ_TPCC_GLOBAL               = 326,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION0              = 327,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION1              = 328,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION2              = 329,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION3              = 330,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION4              = 331,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION5              = 332,
    CSL_XBAR_MMU1_IRQ                           = 333,
    CSL_XBAR_GMAC_SW_IRQ_RX_THRESH_PULSE        = 334,
    CSL_XBAR_GMAC_SW_IRQ_RX_PULSE               = 335,
    CSL_XBAR_GMAC_SW_IRQ_TX_PULSE               = 336,
    CSL_XBAR_GMAC_SW_IRQ_MISC_PULSE             = 337,
    CSL_XBAR_RTI1_IRQ_WWD                       = 338,
    CSL_XBAR_QSPI_IRQ                           = 343,
    CSL_XBAR_ISS_IRQ_INT4                       = 349,
    CSL_XBAR_ISS_IRQ_INT5                       = 350,
    CSL_XBAR_VIP1_IRQ                           = 351,
    CSL_XBAR_ESM_IRQ_HIGH                       = 357,
    CSL_XBAR_ESM_IRQ_LOW                        = 358,
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
    CSL_XBAR_EDMA_TC0_IRQ_ERR                   = 370,
    CSL_XBAR_EDMA_TC1_IRQ_ERR                   = 371,
    CSL_XBAR_OCMC_RAM1_IRQ_CBUF                 = 372,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION6              = 375,
    CSL_XBAR_DSP1_IRQ_TPCC_REGION7              = 376,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION6              = 377,
    CSL_XBAR_DSP2_IRQ_TPCC_REGION7              = 378,
    CSL_XBAR_SMARTREFLEX_DSPEVE_IRQ             = 383,
    CSL_XBAR_PRM_IRQ_IPU2                       = 386,
    CSL_XBAR_PRM_IRQ_DSP2                       = 387,
    CSL_XBAR_PRM_IRQ_EVE1                       = 388,
    CSL_XBAR_PRM_IRQ_EVE2                       = 389,
    CSL_XBAR_PRM_IRQ_EVE3                       = 390,
    CSL_XBAR_PRM_IRQ_EVE4                       = 391,
    CSL_XBAR_VIP1_IRQ_2                         = 392,
    CSL_XBAR_IPU1_IRQ_MMU                       = 395,
    CSL_XBAR_EVE1_IRQ_TPCC_REGION4              = 398,
    CSL_XBAR_RTI1_IRQ_INT0                      = 402,
    CSL_XBAR_RTI1_IRQ_INT1                      = 403,
    CSL_XBAR_TESOC_IRQ_DONE                     = 404,
    CSL_XBAR_RTI3_IRQ_WWD                       = 405,
    CSL_XBAR_RTI4_IRQ_WWD                       = 406,
    CSL_XBAR_RTI5_IRQ_WWD                       = 407,
    CSL_XBAR_RTI1_IRQ_INT2                      = 408,
    CSL_XBAR_RTI1_IRQ_INT3                      = 409,
    CSL_XBAR_RTI1_IRQ_OVL0                      = 410,
    CSL_XBAR_RTI1_IRQ_OVL1                      = 411,
    CSL_XBAR_RTI2_IRQ_INT0                      = 412,
    CSL_XBAR_DCC2_IRQ_ERROR                     = 413,
    CSL_XBAR_DCC2_IRQ_DONE                      = 414,
    CSL_XBAR_DCC3_IRQ_ERROR                     = 415,
    CSL_XBAR_DCC3_IRQ_DONE                      = 416,
    CSL_XBAR_DCC4_IRQ_ERROR                     = 417,
    CSL_XBAR_DCC4_IRQ_DONE                      = 418,
    CSL_XBAR_DCC5_IRQ_ERROR                     = 419,
    CSL_XBAR_DCC5_IRQ_DONE                      = 420,
    CSL_XBAR_DCC6_IRQ_ERROR                     = 421,
    CSL_XBAR_DCC6_IRQ_DONE                      = 422,
    CSL_XBAR_DCC7_IRQ_ERROR                     = 423,
    CSL_XBAR_DCC7_IRQ_DONE                      = 424,
    CSL_XBAR_RTI2_IRQ_INT1                      = 425,
    CSL_XBAR_RTI2_IRQ_INT2                      = 426,
    CSL_XBAR_RTI2_IRQ_INT3                      = 427,
    CSL_XBAR_RTI2_IRQ_OVL0                      = 428,
    CSL_XBAR_RTI2_IRQ_OVL1                      = 429,
    CSL_XBAR_RTI3_IRQ_INT0                      = 430,
    CSL_XBAR_RTI3_IRQ_INT1                      = 431,
    CSL_XBAR_RTI3_IRQ_INT2                      = 432,
    CSL_XBAR_RTI3_IRQ_INT3                      = 433,
    CSL_XBAR_RTI3_IRQ_OVL0                      = 434,
    CSL_XBAR_RTI3_IRQ_OVL1                      = 435,
    CSL_XBAR_RTI4_IRQ_INT0                      = 436,
    CSL_XBAR_RTI4_IRQ_INT1                      = 437,
    CSL_XBAR_RTI4_IRQ_INT2                      = 438,
    CSL_XBAR_RTI4_IRQ_INT3                      = 439,
    CSL_XBAR_RTI4_IRQ_OVL0                      = 440,
    CSL_XBAR_RTI4_IRQ_OVL1                      = 441,
    CSL_XBAR_RTI5_IRQ_INT0                      = 442,
    CSL_XBAR_RTI5_IRQ_INT1                      = 443,
    CSL_XBAR_RTI5_IRQ_INT2                      = 444,
    CSL_XBAR_RTI5_IRQ_INT3                      = 445,
    CSL_XBAR_RTI5_IRQ_OVL                       = 446,
    CSL_XBAR_RTI5_IRQ_OVL1                      = 447,
    CSL_XBAR_RTI1_IRQ_TBINT                     = 448,
    CSL_XBAR_RTI2_IRQ_TBINT                     = 449,
    CSL_XBAR_RTI3_IRQ_TBINT                     = 450,
    CSL_XBAR_RTI4_IRQ_TBINT                     = 451,
    CSL_XBAR_RTI5_IRQ_TBINT                     = 452,
    CSL_XBAR_McASP2_IRQ_AREVT                   = 453,  /* PG2.0 and above */
    CSL_XBAR_McASP2_IRQ_AXEVT                   = 454,  /* PG2.0 and above */
    CSL_XBAR_McASP3_IRQ_AREVT                   = 455,  /* PG2.0 and above */
    CSL_XBAR_McASP3_IRQ_AXEVT                   = 456,  /* PG2.0 and above */
    CSL_XBAR_MCAN_IRQ_TS                        = 457,  /* PG2.0 and above */
    CSL_XBAR_IRQ_MAX                            = 458
} CSL_XbarIrq;

typedef enum
{
    CSL_XBAR_IRQ_CPU_ID_IPU1,
    CSL_XBAR_IRQ_CPU_ID_DSP1,
    CSL_XBAR_IRQ_CPU_ID_DSP2,
    CSL_XBAR_IRQ_CPU_ID_EVE1
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
    CSL_XBAR_DMA_RSVD                           = 0,
    CSL_XBAR_DMA_EXT_SYS_DREQ_0                 = 2,
    CSL_XBAR_DMA_EXT_SYS_DREQ_1                 = 3,
    CSL_XBAR_DMA_GPMC_DREQ                      = 4,
    CSL_XBAR_DMA_DISPC_DREQ                     = 6,
    CSL_XBAR_DMA_CT_TBR_DREQ                    = 7,
    CSL_XBAR_DMA_ISS_DREQ_1                     = 9,
    CSL_XBAR_DMA_ISS_DREQ_2                     = 10,
    CSL_XBAR_DMA_ISS_DREQ_3                     = 12,
    CSL_XBAR_DMA_ISS_DREQ_4                     = 13,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX0                = 15,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX0                = 16,
    CSL_XBAR_DMA_MCSPI3_DREQ_TX1                = 23,
    CSL_XBAR_DMA_MCSPI3_DREQ_RX1                = 24,
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
    CSL_XBAR_DMA_UART1_DREQ_TX                  = 49,
    CSL_XBAR_DMA_UART1_DREQ_RX                  = 50,
    CSL_XBAR_DMA_UART2_DREQ_TX                  = 51,
    CSL_XBAR_DMA_UART2_DREQ_RX                  = 52,
    CSL_XBAR_DMA_UART3_DREQ_TX                  = 53,
    CSL_XBAR_DMA_UART3_DREQ_RX                  = 54,
    CSL_XBAR_DMA_MMC1_DREQ_TX                   = 61,
    CSL_XBAR_DMA_MMC1_DREQ_RX                   = 62,
    CSL_XBAR_DMA_MCSPI4_DREQ_TX0                = 70,
    CSL_XBAR_DMA_MCSPI4_DREQ_RX0                = 71,
    CSL_XBAR_DMA_McASP1_DREQ_RX                 = 128,
    CSL_XBAR_DMA_McASP1_DREQ_TX                 = 129,
    CSL_XBAR_DMA_DCAN1_DREQ_IF1                 = 158,
    CSL_XBAR_DMA_DCAN1_DREQ_IF2                 = 159,
    CSL_XBAR_DMA_DCAN1_DREQ_IF3                 = 160,
    CSL_XBAR_DMA_DCAN2_DREQ_IF1                 = 161,
    CSL_XBAR_DMA_DCAN2_DREQ_IF2                 = 162,
    CSL_XBAR_DMA_DCAN2_DREQ_IF3                 = 163,
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
    CSL_XBAR_DMA_GPIO1_DREQ_EVT                 = 187,
    CSL_XBAR_DMA_GPIO2_DREQ_EVT                 = 188,
    CSL_XBAR_DMA_GPIO3_DREQ_EVT                 = 189,
    CSL_XBAR_DMA_GPIO4_DREQ_EVT                 = 190,
    CSL_XBAR_DMA_PWMSS1_DREQ_ePWM0_EVT          = 195,
    CSL_XBAR_DMA_PWMSS1_DREQ_eQEP0_EVT          = 198,
    CSL_XBAR_DMA_PWMSS1_DREQ_eCAP0_EVT          = 201,
    CSL_XBAR_DMA_CRC_DREQ_EVT0                  = 204,
    CSL_XBAR_DMA_TSC_ADC_DREQ_FIFO0             = 205,
    CSL_XBAR_DMA_TSC_ADC_DREQ_FIFO1             = 206,
    CSL_XBAR_DMA_CRC_DREQ_EVT1                  = 207,
    CSL_XBAR_DMA_CRC_DREQ_EVT2                  = 208,
    CSL_XBAR_DMA_CRC_DREQ_EVT3                  = 209,
    CSL_XBAR_DMA_RTI1_DREQ_EVT0                 = 210,
    CSL_XBAR_DMA_RTI1_DREQ_EVT1                 = 211,
    CSL_XBAR_DMA_RTI1_DREQ_EVT2                 = 212,
    CSL_XBAR_DMA_RTI1_DREQ_EVT3                 = 213,
    CSL_XBAR_DMA_RTI2_DREQ_EVT0                 = 214,
    CSL_XBAR_DMA_RTI2_DREQ_EVT1                 = 215,
    CSL_XBAR_DMA_RTI2_DREQ_EVT2                 = 216,
    CSL_XBAR_DMA_RTI2_DREQ_EVT3                 = 217,
    CSL_XBAR_DMA_RTI3_DREQ_EVT0                 = 218,
    CSL_XBAR_DMA_RTI3_DREQ_EVT1                 = 219,
    CSL_XBAR_DMA_RTI3_DREQ_EVT2                 = 220,
    CSL_XBAR_DMA_RTI3_DREQ_EVT3                 = 221,
    CSL_XBAR_DMA_RTI4_DREQ_EVT0                 = 222,
    CSL_XBAR_DMA_RTI4_DREQ_EVT1                 = 223,
    CSL_XBAR_DMA_RTI4_DREQ_EVT2                 = 224,
    CSL_XBAR_DMA_RTI4_DREQ_EVT3                 = 225,
    CSL_XBAR_DMA_RTI5_DREQ_EVT0                 = 226,
    CSL_XBAR_DMA_RTI5_DREQ_EVT1                 = 227,
    CSL_XBAR_DMA_RTI5_DREQ_EVT2                 = 228,
    CSL_XBAR_DMA_RTI5_DREQ_EVT3                 = 229,
    CSL_XBAR_DMA_RSVD1                          = 230

} CSL_XbarDma;

/* \brief Number of XBAR instances for each core */
#define CSL_IPU1_IRQ_XBAR_COUNT     (0x39U)
#define CSL_DSP1_IRQ_XBAR_COUNT     (0x40U)
#define CSL_DSP2_IRQ_XBAR_COUNT     (0x40U)
#define CSL_EVE1_IRQ_XBAR_COUNT     (0x08U)
#define CSL_IRQ_XBAR_MAX_COUNT      (0x1CDU)

#define CSL_EDMA_XBAR_COUNT         (0x40U)
#define CSL_DSP1_DMA_XBAR_COUNT     (0x40U)
#define CSL_DSP2_DMA_XBAR_COUNT     (0x40U)
#define CSL_DMA_XBAR_MAX_COUNT      (0xE6U)

/******************************************************************************
 * IRQ XBAR instance mapping for each core interrupts.
 * This is the IRQ XBAR instance to which a particular interrupt of the core is
 * mapped. This macro could be used to pass the IRQ XBAR instance to the IRQ
 * XBAR connect API of starterware.
 ******************************************************************************/
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

/* IRQ XBAR Mapping for DSP2 */
#define CSL_XBAR_INST_DSP2_IRQ_32           (1U)
#define CSL_XBAR_INST_DSP2_IRQ_33           (2U)
#define CSL_XBAR_INST_DSP2_IRQ_34           (3U)
#define CSL_XBAR_INST_DSP2_IRQ_35           (4U)
#define CSL_XBAR_INST_DSP2_IRQ_36           (5U)
#define CSL_XBAR_INST_DSP2_IRQ_37           (6U)
#define CSL_XBAR_INST_DSP2_IRQ_38           (7U)
#define CSL_XBAR_INST_DSP2_IRQ_39           (8U)
#define CSL_XBAR_INST_DSP2_IRQ_40           (9U)
#define CSL_XBAR_INST_DSP2_IRQ_41           (10U)
#define CSL_XBAR_INST_DSP2_IRQ_42           (11U)
#define CSL_XBAR_INST_DSP2_IRQ_43           (12U)
#define CSL_XBAR_INST_DSP2_IRQ_44           (13U)
#define CSL_XBAR_INST_DSP2_IRQ_45           (14U)
#define CSL_XBAR_INST_DSP2_IRQ_46           (15U)
#define CSL_XBAR_INST_DSP2_IRQ_47           (16U)
#define CSL_XBAR_INST_DSP2_IRQ_48           (17U)
#define CSL_XBAR_INST_DSP2_IRQ_49           (18U)
#define CSL_XBAR_INST_DSP2_IRQ_50           (19U)
#define CSL_XBAR_INST_DSP2_IRQ_51           (20U)
#define CSL_XBAR_INST_DSP2_IRQ_52           (21U)
#define CSL_XBAR_INST_DSP2_IRQ_53           (22U)
#define CSL_XBAR_INST_DSP2_IRQ_54           (23U)
#define CSL_XBAR_INST_DSP2_IRQ_55           (24U)
#define CSL_XBAR_INST_DSP2_IRQ_56           (25U)
#define CSL_XBAR_INST_DSP2_IRQ_57           (26U)
#define CSL_XBAR_INST_DSP2_IRQ_58           (27U)
#define CSL_XBAR_INST_DSP2_IRQ_59           (28U)
#define CSL_XBAR_INST_DSP2_IRQ_60           (29U)
#define CSL_XBAR_INST_DSP2_IRQ_61           (30U)
#define CSL_XBAR_INST_DSP2_IRQ_62           (31U)
#define CSL_XBAR_INST_DSP2_IRQ_63           (32U)
#define CSL_XBAR_INST_DSP2_IRQ_64           (33U)
#define CSL_XBAR_INST_DSP2_IRQ_65           (34U)
#define CSL_XBAR_INST_DSP2_IRQ_66           (35U)
#define CSL_XBAR_INST_DSP2_IRQ_67           (36U)
#define CSL_XBAR_INST_DSP2_IRQ_68           (37U)
#define CSL_XBAR_INST_DSP2_IRQ_69           (38U)
#define CSL_XBAR_INST_DSP2_IRQ_70           (39U)
#define CSL_XBAR_INST_DSP2_IRQ_71           (40U)
#define CSL_XBAR_INST_DSP2_IRQ_72           (41U)
#define CSL_XBAR_INST_DSP2_IRQ_73           (42U)
#define CSL_XBAR_INST_DSP2_IRQ_74           (43U)
#define CSL_XBAR_INST_DSP2_IRQ_75           (44U)
#define CSL_XBAR_INST_DSP2_IRQ_76           (45U)
#define CSL_XBAR_INST_DSP2_IRQ_77           (46U)
#define CSL_XBAR_INST_DSP2_IRQ_78           (47U)
#define CSL_XBAR_INST_DSP2_IRQ_79           (48U)
#define CSL_XBAR_INST_DSP2_IRQ_80           (49U)
#define CSL_XBAR_INST_DSP2_IRQ_81           (50U)
#define CSL_XBAR_INST_DSP2_IRQ_82           (51U)
#define CSL_XBAR_INST_DSP2_IRQ_83           (52U)
#define CSL_XBAR_INST_DSP2_IRQ_84           (53U)
#define CSL_XBAR_INST_DSP2_IRQ_85           (54U)
#define CSL_XBAR_INST_DSP2_IRQ_86           (55U)
#define CSL_XBAR_INST_DSP2_IRQ_87           (56U)
#define CSL_XBAR_INST_DSP2_IRQ_88           (57U)
#define CSL_XBAR_INST_DSP2_IRQ_89           (58U)
#define CSL_XBAR_INST_DSP2_IRQ_90           (59U)
#define CSL_XBAR_INST_DSP2_IRQ_91           (60U)
#define CSL_XBAR_INST_DSP2_IRQ_92           (61U)
#define CSL_XBAR_INST_DSP2_IRQ_93           (62U)
#define CSL_XBAR_INST_DSP2_IRQ_94           (63U)
#define CSL_XBAR_INST_DSP2_IRQ_95           (64U)

/* IRQ XBAR Mapping for IPU1 */
#define CSL_XBAR_INST_IPU1_IRQ_23           (uint32_t) (1U)
#define CSL_XBAR_INST_IPU1_IRQ_24           (2U)
#define CSL_XBAR_INST_IPU1_IRQ_25           (3U)
#define CSL_XBAR_INST_IPU1_IRQ_26           (4U)
#define CSL_XBAR_INST_IPU1_IRQ_27           (uint32_t) (5U)
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

/******************************************************************************
 * DMA XBAR instance mapping for each DMA instances.
 * This is the DMA XBAR instance to which a particular DMA event is
 * mapped. This macro could be used to pass the DMA XBAR instance to the DMA
 * XBAR connect API of starterware.
 ******************************************************************************/
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

/* DMA XBAR Mapping for DSP2 DMA */
#define CSL_XBAR_INST_DMA_DSP2_DREQ_0       (1U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_1       (2U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_2       (3U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_3       (4U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_4       (5U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_5       (6U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_6       (7U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_7       (8U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_8       (9U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_9       (10U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_10      (11U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_11      (12U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_12      (13U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_13      (14U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_14      (15U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_15      (16U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_16      (17U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_17      (18U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_18      (19U)
#define CSL_XBAR_INST_DMA_DSP2_DREQ_19      (20U)

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

#endif /* CSL_TDA3XX_DEVICE_INTERRUPT_H_ */
 /** @} */
