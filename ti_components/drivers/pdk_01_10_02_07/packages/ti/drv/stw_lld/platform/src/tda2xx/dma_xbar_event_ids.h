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
 *  \file   dma_xbar_event_ids.h
 *
 *  \brief  Definitions used for DMA XBAR Event IDs
 *
 *   This file contains all of the DMA XBAR Event IDs needed to program an DMA
 *   XBAR instance.
 */

#ifndef DMA_XBAR_EVENT_IDS_H
#define DMA_XBAR_EVENT_IDS_H

#ifdef __cplusplus
extern "C"
{
#endif
/* Enumerated list of DMA event sources into the DMA_XBAR */
/**
 * \enum xbar_evt_t
 * \brief  Enumeration that contains all possible DMA event source IDs as inputs
 *         to each DMA crossbar instance on Vayu
 *
 */
typedef enum {
    DMA_XBAR_RSVD                  = 0,
    EXT_SYS_DREQ_0                 = 2,
    EXT_SYS_DREQ_1                 = 3,
    GPMC_DREQ                      = 4,
    DISPC_DREQ                     = 6,
    CT_TBR_DREQ                    = 7,
    MCSPI3_DREQ_TX0                = 15,
    MCSPI3_DREQ_RX0                = 16,
#if defined (SOC_TDA2PX)
    MCAN_DREQ_TX                   = 17,
    MCAN_DREQ_RX_FE1               = 18,
    MCAN_DREQ_RX_FE2               = 19,
#endif
    MCSPI3_DREQ_TX1                = 23,
    MCSPI3_DREQ_RX1                = 24,
    I2C3_DREQ_TX                   = 25,
    I2C3_DREQ_RX                   = 26,
    I2C1_DREQ_TX                   = 27,
    I2C1_DREQ_RX                   = 28,
    I2C2_DREQ_TX                   = 29,
    I2C2_DREQ_RX                   = 30,
    MCSPI1_DREQ_TX0                = 35,
    MCSPI1_DREQ_RX0                = 36,
    MCSPI1_DREQ_TX1                = 37,
    MCSPI1_DREQ_RX1                = 38,
    MCSPI1_DREQ_TX2                = 39,
    MCSPI1_DREQ_RX2                = 40,
    MCSPI1_DREQ_TX3                = 41,
    MCSPI1_DREQ_RX3                = 42,
    MCSPI2_DREQ_TX0                = 43,
    MCSPI2_DREQ_RX0                = 44,
    MCSPI2_DREQ_TX1                = 45,
    MCSPI2_DREQ_RX1                = 46,
    MMC2_DREQ_TX                   = 47,
    MMC2_DREQ_RX                   = 48,
    UART1_DREQ_TX                  = 49,
    UART1_DREQ_RX                  = 50,
    UART2_DREQ_TX                  = 51,
    UART2_DREQ_RX                  = 52,
    UART3_DREQ_TX                  = 53,
    UART3_DREQ_RX                  = 54,
    UART4_DREQ_TX                  = 55,
    UART4_DREQ_RX                  = 56,
    MMC4_DREQ_TX                   = 57,
    MMC4_DREQ_RX                   = 58,
    MMC1_DREQ_TX                   = 61,
    MMC1_DREQ_RX                   = 62,
    UART5_DREQ_TX                  = 63,
    UART5_DREQ_RX                  = 64,
    MCSPI4_DREQ_TX0                = 70,
    MCSPI4_DREQ_RX0                = 71,
    DSS_DREQ                       = 76,
    MMC3_DREQ_TX                   = 77,
    MMC3_DREQ_RX                   = 78,
    UART6_DREQ_TX                  = 79,
    UART6_DREQ_RX                  = 80,
    AES1_DREQ_P_CTXT_IN            = 109,
    AES1_DREQ_P_DATA_IN            = 110,
    AES1_DREQ_P_DATA_OUT           = 111,
    AES2_DREQ_P_CTXT_IN            = 112,
    AES2_DREQ_P_DATA_IN            = 113,
    AES2_DREQ_P_DATA_OUT           = 114,
    DES3DES_DREQ_P_CTXT_IN         = 115,
    DES3DES_DREQ_P_DATA_IN         = 116,
    DES3DES_DREQ_P_DATA_OUT        = 117,
    SHA2MD5_1_DREQ_P_CTXT_IN       = 118,
    SHA2MD5_1_DREQ_P_DATA_IN       = 119,
    SHA2MD5_1_DREQ_P_DATA_CTXT_OUT = 120,
    AES1_DREQ_P_CTXT_OUT           = 121,
    AES2_DREQ_P_CTXT_OUT           = 122,
    I2C4_DREQ_TX                   = 124,
    I2C4_DREQ_RX                   = 125,
    McASP1_DREQ_RX                 = 128,
    McASP1_DREQ_TX                 = 129,
    McASP2_DREQ_RX                 = 130,
    McASP2_DREQ_TX                 = 131,
    McASP3_DREQ_RX                 = 132,
    McASP3_DREQ_TX                 = 133,
    McASP4_DREQ_RX                 = 134,
    McASP4_DREQ_TX                 = 135,
    McASP5_DREQ_RX                 = 136,
    McASP5_DREQ_TX                 = 137,
    McASP6_DREQ_RX                 = 138,
    McASP6_DREQ_TX                 = 139,
    McASP7_DREQ_RX                 = 140,
    McASP7_DREQ_TX                 = 141,
    McASP8_DREQ_RX                 = 142,
    McASP8_DREQ_TX                 = 143,
    UART7_DREQ_TX                  = 144,
    UART7_DREQ_RX                  = 145,
    UART8_DREQ_TX                  = 146,
    UART8_DREQ_RX                  = 147,
    UART9_DREQ_TX                  = 148,
    UART9_DREQ_RX                  = 149,
    UART10_DREQ_TX                 = 150,
    UART10_DREQ_RX                 = 151,
    I2C5_DREQ_TX                   = 152,
    I2C5_DREQ_RX                   = 153,
    VCP1_DREQ_RX                   = 154,
    VCP1_DREQ_TX                   = 155,
    VCP2_DREQ_RX                   = 156,
    VCP2_DREQ_TX                   = 157,
    DCAN1_DREQ_IF1                 = 158,
    DCAN1_DREQ_IF2                 = 159,
    DCAN1_DREQ_IF3                 = 160,
    DCAN2_DREQ_IF1                 = 161,
    DCAN2_DREQ_IF2                 = 162,
    DCAN2_DREQ_IF3                 = 163,
    SHA2MD5_2_DREQ_P_CTXT_IN       = 164,
    SHA2MD5_2_DREQ_P_DATA_IN       = 165,
    SHA2MD5_2_DREQ_P_DATA_CTXT_OUT = 166,
    EXT_SYS_DREQ_2                 = 167,
    EXT_SYS_DREQ_3                 = 168,
    MCSPI2_DREQ_TX2                = 169,
    MCSPI2_DREQ_RX2                = 170,
    MCSPI2_DREQ_TX3                = 171,
    MCSPI2_DREQ_RX3                = 172,
    MCSPI3_DREQ_TX2                = 173,
    MCSPI3_DREQ_RX2                = 174,
    MCSPI3_DREQ_TX3                = 175,
    MCSPI3_DREQ_RX3                = 176,
    MCSPI4_DREQ_TX1                = 177,
    MCSPI4_DREQ_RX1                = 178,
    MCSPI4_DREQ_TX2                = 179,
    MCSPI4_DREQ_RX2                = 180,
    MCSPI4_DREQ_TX3                = 181,
    MCSPI4_DREQ_RX3                = 182,
    PRUSS1_DREQ_HOST_REQ0          = 183,
    PRUSS1_DREQ_HOST_REQ1          = 184,
    PRUSS2_DREQ_HOST_REQ0          = 185,
    PRUSS2_DREQ_HOST_REQ1          = 186,
    GPIO1_DREQ_EVT                 = 187,
    GPIO2_DREQ_EVT                 = 188,
    GPIO3_DREQ_EVT                 = 189,
    GPIO4_DREQ_EVT                 = 190,
    GPIO5_DREQ_EVT                 = 191,
    GPIO6_DREQ_EVT                 = 192,
    GPIO7_DREQ_EVT                 = 193,
    GPIO8_DREQ_EVT                 = 194,
    PWMSS1_DREQ_ePWM0_EVT          = 195,
    PWMSS2_DREQ_ePWM1_EVT          = 196,
    PWMSS3_DREQ_ePWM2_EVT          = 197,
    PWMSS1_DREQ_eQEP0_EVT          = 198,
    PWMSS2_DREQ_eQEP1_EVT          = 199,
    PWMSS3_DREQ_eQEP2_EVT          = 200,
    PWMSS1_DREQ_eCAP0_EVT          = 201,
    PWMSS2_DREQ_eCAP1_EVT          = 202,
    PWMSS3_DREQ_eCAP2_EVT          = 203,
#if defined (SOC_TDA2EX)
    I2C6_DREQ_TX = 204,
    I2C6_DREQ_RX = 205,
#endif
    DMA_XBAR_RSVD1 = 206
} xbar_evt_t;

#define EDMA_EVT_XBAR_COUNT             0x40
#define DSP1_EDMA_EVT_XBAR_COUNT        0x14
#if defined (SOC_TDA2EX)
 /* Not applicable */
#else
#define DSP2_EDMA_EVT_XBAR_COUNT        0x14
#endif
#define DMA_XBAR_MAX_EVT_COUNT          0xDD

#ifdef __cplusplus
}
#endif
#endif

