/*
 *  Copyright (C) 2012-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup SOC_DEFINES SOC Defines
 *
 *  @{
 */
/**
 *  \file     tda2ex/cslr_soc_defines.h
 *
 *  \brief    This file contains the enums and macros for the TDA2EX SOC
 *
 */

#ifndef CSLR_SOC_DEFINES_H_
#define CSLR_SOC_DEFINES_H_

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

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_PER_CNT             (1U)

/** @brief Number of VPS VPE instances                                        */
#define CSL_VPS_VPE_PER_CNT             (1U)

/** @brief Number of VPS DSS instances                                        */
#define CSL_VPS_DSS_PER_CNT             (1U)

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_TOP_PER_CNT         (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS VIP-PORT instances                                   */
#define CSL_VPS_VIP_PORT_PER_CNT        (CSL_VPS_VIP_PER_CNT * 4U)

/** @brief Number of VPS VPDMA instances                                      */
#define CSL_VPS_VPDMA_PER_CNT           (CSL_VPS_VIP_PER_CNT + \
                                            CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS CHRUS instances                                      */
#define CSL_VPS_CHRUS_PER_CNT           (CSL_VPS_VPE_PER_CNT * 3U)

/** @brief Number of VPS CSC instances                                        */
#define CSL_VPS_CSC_PER_CNT             ((CSL_VPS_VIP_PER_CNT * 2U) + \
                                            CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS VPE instances                                        */
#define CSL_VPS_VPE_TOP_PER_CNT         (CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS DEI instances                                        */
#define CSL_VPS_DEI_PER_CNT             (CSL_VPS_VPE_PER_CNT * 1U)

/** @brief Number of VPS SC instances                                         */
#define CSL_VPS_SC_PER_CNT              ((CSL_VPS_VIP_PER_CNT * 2U) \
                                            + CSL_VPS_VPE_PER_CNT)

/** @brief Number of VPS DSS-Video + Graphics instances */
#define CSL_VPS_DSS_VID_PIPE_PER_CNT    (4U)

/** @brief Number of VPS WB instances */
#define CSL_VPS_DSS_WB_PIPE_PER_CNT     (1U)

/** @brief Number of VPS CAPT ISS Pipelines  */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT   (3U)

/** @brief Number of VPS DSS-Overlay manager instances                        */
#define CSL_VPS_DSS_OVLY_MGR_PER_CNT    (4U)

/** \brief CAL Instance 0 base address */
#define ISS_CALA_BASE_REGISTER                  (0x4845B000U)
/** \brief CAL RX Core 0/Phy 1 base address */
#define ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER  (0x4845B800U)
/** \brief CAL RX Core 0/Phy 2 base address */
#define ISS_CALA_CAMERARX_CORE_1_BASE_REGISTER  (0x4845B900U)

/** \brief number of instances of CAL available */
#define CSL_CAL_PER_CNT                     (1U)
/** \brief Defines the total number of PPI available per CAL */
#define CSL_CAL_PPI_CNT                     (2U)
/** \brief Defines the total number of complex IO available per CAL */
#define CSL_CAL_CMPLXIO_CNT                 (2U)
/** \brief Defines the total number of pixel processing context
 *          available per CAL */
#define CSL_CAL_PIX_PROC_CTX_CNT            (4U)

/** @brief Number of MMCSD instances                                          */
#define CSL_MMCHS_CNT                   ((uint32_t) 4U)

/** @brief interrupt number for CAL. */
#define CSL_CAL_IRQ_NUM         (71U)
/******************************************************************************\
 * Interrupt Event IDs
\******************************************************************************/

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_VIP1INT0       (27U)
#define CSL_INTC_EVENTID_VPEINT0        (30U)
#define CSL_INTC_EVENTID_DSS_DISPC      (23U)
#define CSL_VPS_INTC_NUM                (0U)

/** @brief Number of MCSPI instances                                          */
#define CSL_MCSPI_PER_CNT               ((uint32_t) 4U)

/******************************************************************************\
 * Peripheral Instance definitions.
 \******************************************************************************/
/** @brief Peripheral Instances of McASP instances                            */
#define CSL_MCASP_0                         (0)

/** @brief Peripheral Instances of UART instances                             */
#define CSL_UART_0                          (0)
#define CSL_UART_1                          (1)
#define CSL_UART_2                          (2)
#define CSL_UART_3                          (3)
#define CSL_UART_4                          (4)
#define CSL_UART_5                          (5)

typedef enum {
    UART1_INST = 0,
    UART2_INST,
    UART3_INST,
    UART4_INST,
    UART5_INST,
    UART6_INST,
    UART7_INST,
    UART8_INST,
    UART9_INST,
    UART10_INST
}UART_INST_t;

/** @brief Peripheral Instances of MCSPI instances                            */
#define CSL_MCSPI_0                         (0)
#define CSL_MCSPI_1                         (1)
#define CSL_MCSPI_2                         (2)
#define CSL_MCSPI_3                         (3)

/** @brief Peripheral Instances of MMC/SD instances
 *                           */
typedef enum {
    MMC1_INST = 0,
    MMC2_INST,
    MMC3_INST,
    MMC4_INST
}MMC_INST_t;

/******************************************************************************\
 * Interrupt Event IDs
 \*****************************************************************************/

/* I2C interrupt                                                              */
#define CSL_INTC_EVENTID_I2CINT1        (41U)
#define CSL_INTC_EVENTID_I2CINT3        (43U)
/*I2C2 Interrupt is mapped through cross bar and not used */
#define CSL_INTC_EVENTID_I2CINT2        (0U)
#define CSL_INTC_EVENTID_I2CINT4        (48U)
#define CSL_INTC_EVENTID_I2CINT5        (42U)

/* To get the ducati int mux number, the 'CSL_INTMUX_OFFSET' has to be
 * subttracted from the interrupt number (directly mapped)
 */
#define    CSL_INTMUX_OFFSET                (23U)

/* MCSPI interrupt                                                            */
#define    CSL_INTC_EVENTID_MCSPIINT0       (57)
#define    CSL_INTC_EVENTID_MCSPIINT1       (58)
/*Dummy and crossbar Mapped - please cross check before use */
#define    CSL_INTC_EVENTID_MCSPIINT2       (44)
#define    CSL_INTC_EVENTID_MCSPIINT3       (45)

/* UART interrupt                                                             */
/* All are crossbar mapped please cross check before use */
/*UART1 is being used in DMA Mode */
/*Instance Number Macro definitions are started from 0, it needs to be changed
 *to 1 later*/
#if defined (__ARM_ARCH_7A__)
/* For a15, UART1 address is 72. 32 is added to offset reserved interrupts */
#define    CSL_INTC_EVENTID_UARTINT0        (72U + 32U)
/* Below interrupts needs to be changed */
#define    CSL_INTC_EVENTID_UARTINT1        (60U + 32U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U + 32U)
#define    CSL_INTC_EVENTID_UARTINT3        (61U + 32U)
#define    CSL_INTC_EVENTID_UARTINT4        (62U + 32U)
#define    CSL_INTC_EVENTID_UARTINT5        (63U + 32U)
#define    CSL_INTC_EVENTID_UARTINT6        (64U + 32U)
#define    CSL_INTC_EVENTID_UARTINT7        (65U + 32U)
#define    CSL_INTC_EVENTID_UARTINT8        (69U + 32U)
#define    CSL_INTC_EVENTID_UARTINT9        (70U + 32U)
#else
#define    CSL_INTC_EVENTID_UARTINT0        (44U)
#define    CSL_INTC_EVENTID_UARTINT1        (60U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U)
#define    CSL_INTC_EVENTID_UARTINT3        (61U)
#define    CSL_INTC_EVENTID_UARTINT4        (62U)
#define    CSL_INTC_EVENTID_UARTINT5        (63U)
#define    CSL_INTC_EVENTID_UARTINT6        (64U)
#define    CSL_INTC_EVENTID_UARTINT7        (65U)
#define    CSL_INTC_EVENTID_UARTINT8        (69U)
#define    CSL_INTC_EVENTID_UARTINT9        (70U)
#endif

/* McASP Interrupts
 *   All are crossbar mapped please cross check before use */
#if defined (__TI_ARM_V7M4__)
/** @brief Defining McASP interrupt numbers for the M4 core                   */
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (27U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (28U)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (29U)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (30U)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (31U)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (32U)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (33U)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (59U)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (60U)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (61U)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (62U)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (63U)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (69U)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (70U)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (71U)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (72U)
#else
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (58U)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (59U)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (60U)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (61U)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (91U)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (92U)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (74U)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (51U)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (79U)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (81U)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (86U)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (87U)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (88U)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (43U)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (48U)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (49U)
#endif

/*************************** EDMA RELATED DEFINES  ****************************/

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/

#define CSL_EDMA3_NUM_DMACH                 64
#define CSL_EDMA3_NUM_QDMACH                8
#define CSL_EDMA3_NUM_PARAMSETS             512
#define CSL_EDMA3_NUM_EVQUE                 4
#define CSL_EDMA3_CHMAPEXIST                0
#define CSL_EDMA3_NUM_REGIONS               4
#define CSL_EDMA3_MEMPROTECT                0

/******************************************************************************\
 * Channel Instance count
 \******************************************************************************/
#define CSL_EDMA3_CHA_CNT                   (CSL_EDMA3_NUM_DMACH + \
                                             CSL_EDMA3_NUM_QDMACH)

/* EDMA channel synchronization events                                        */

/* McASP0 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP0_RX             0
/* McASP0 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP0_TX             1
/* McASP1 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP1_RX             2
/* McASP1 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP1_TX             3
/* McASP2 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP2_RX             4
/* McASP2 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP2_TX             5
/* McASP3 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP3_RX             6
/* McASP3 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP3_TX             7
/* McASP4 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP4_RX             8
/* McASP4 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP4_TX             9
/* McASP5 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP5_RX             10
/* McASP5 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP5_TX             11
/* McASP6 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP6_RX             12
/* McASP6 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP6_TX             13
/* McASP7 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP7_RX             14
/* McASP7 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP7_TX             15
/*
 * Instance Numbers starts from 1 in Vayu but keeping it to 0 to not change the
 * driver
 * Need to modify driver later for Instance Numbers
 */
/* UART0 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART0_RX              49
/* UART0 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART0_TX              48
/* UART1 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART1_RX              51
/* UART1 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART1_TX              50
/* UART2 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART2_RX              53
/* UART2 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART2_TX              52
/* UART3 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART3_RX              55
/* UART3 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART3_TX              54
/* UART4 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART4_RX              63
/* UART4 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART4_TX              62
/*
 * Below are Cross Bar Mapped Please redefine for any
 * simultaneous usecase in DMA Mode
 */
/* UART5 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART5_RX              51
/* UART5 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART5_TX              50
/* UART6 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART6_RX              51
/* UART6 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART6_TX              50
/* UART7 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART7_RX              51
/* UART7 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART7_TX              50
/* UART8 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART8_RX              51
/* UART8 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART8_TX              50
/* UART9 Receive Event                                                        */
#define CSL_EDMA3_CHA_UART9_RX              51
/* UART9 Transmit Event                                                       */
#define CSL_EDMA3_CHA_UART9_TX              50

/*
 * MCSPIx Channelx
 */
/* MCSPI0 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI0_RX            35
/* MCSPI0 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI0_TX            34
/* MCSPI0 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI0_RX            37
/* MCSPI0 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI0_TX            36
/* MCSPI0 CHA2 Receive Event                                                  */
#define CSL_EDMA3_CHA2_MCSPI0_RX            39
/* MCSPI0 CHA2 Transmit Event                                                 */
#define CSL_EDMA3_CHA2_MCSPI0_TX            38
/* MCSPI0 CHA3 Receive Event                                                  */
#define CSL_EDMA3_CHA3_MCSPI0_RX            41
/* MCSPI0 CHA3 Transmit Event                                                 */
#define CSL_EDMA3_CHA3_MCSPI0_TX            40
/* MCSPI1 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI1_RX            43
/* MCSPI1 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI1_TX            42
/* MCSPI1 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI1_RX            45
/* MCSPI1 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI1_TX            44
/* MCSPI2 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI2_RX            15
/* MCSPI2 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI2_TX            14
/* MCSPI2 CHA1 Receive Event                                                  */
#define CSL_EDMA3_CHA1_MCSPI2_RX            23
/* MCSPI2 CHA1 Transmit Event                                                 */
#define CSL_EDMA3_CHA1_MCSPI2_TX            22
/*
 * Cross Bar Mapped Please check before use
 */
/* MCSPI3 CHA0 Receive Event                                                  */
#define CSL_EDMA3_CHA0_MCSPI3_RX            23
/* MCSPI3 CHA0 Transmit Event                                                 */
#define CSL_EDMA3_CHA0_MCSPI3_TX            22

/*
 * Peripheral related Info
 */
/*  MCSPI   */
#define CSL_MCSPI_0_NumOfPhyChannels       (4U)
#define CSL_MCSPI_1_NumOfPhyChannels       (4U)
#define CSL_MCSPI_2_NumOfPhyChannels       (4U)
#define CSL_MCSPI_3_NumOfPhyChannels       (4U)

#define CSL_NUM_MCSPI_INST                 (4U)

#define CSL_MCASP_0_NumSerializers         (16)
#define CSL_MCASP_1_NumSerializers         (16)
#define CSL_MCASP_2_NumSerializers         (4)
#define CSL_MCASP_3_NumSerializers         (4)
#define CSL_MCASP_4_NumSerializers         (4)
#define CSL_MCASP_5_NumSerializers         (4)
#define CSL_MCASP_6_NumSerializers         (4)
#define CSL_MCASP_7_NumSerializers         (4)

/*
 * L3 FIREWALL
 */
/* L3 Firewall Instance Summary */
#define L3FW_INST_NUM                                       (25U)

#define L3FW_BB2D_INST                  (0x4A21A000U)
#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_GPU_INST                   (SOC_SECURITYCORE_GPU_BASE)
#define L3FW_IPU1_INST                  (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_IVA_CFG_INST               (SOC_SECURITYCORE_IVA1_CONFIG_BASE)
#define L3FW_IVA_SL2IF_INST             (SOC_SECURITYCORE_IVA1_SL2IF_BASE)
#define L3FW_OCMC_RAM1_INST             (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_EMIF_INST                  (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_TPCC_INST                  (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_TPTC_INST                  (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_MCASP1_INST                (SOC_SECURITYCORE_MCASP1_BASE)
#define L3FW_MCASP2_INST                (SOC_SECURITYCORE_MCASP2_BASE)
#define L3FW_MCASP3_INST                (SOC_SECURITYCORE_MCASP3_BASE)
#define L3FW_PCIESS2_INST               (SOC_SECURITYCORE_PCIE2_BASE)
#define L3FW_PCIESS1_INST               (SOC_SECURITYCORE_PCIE1_BASE)
#define L3FW_VCP1_INST                  (SOC_SECURITYCORE_VCP1_BASE)
#define L3FW_IPU2_INST                  (SOC_SECURITYCORE_IPU2_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_PRUSS1_INST                (SOC_SECURITYCORE_PRUSS1_BASE)
#define L3FW_PRUSS2_INST                (SOC_SECURITYCORE_PRUSS2_BASE)
#define L3FW_MA_MPU_NTTP_INST           (SOC_MA_MPU_NTTP_FW_CFG_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)

#define L3FW_BB2D_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_DEBUGSS_CT_TBR_ERR_REG      (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_DSS_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_GPU_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IPU1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_GPMC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IVA_CFG_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IVA_SL2IF_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_OCMC_RAM1_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EMIF_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_QSPI_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_VCP1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TPCC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TPTC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP1_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP2_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP3_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PCIESS2_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PCIESS1_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_IPU2_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_DSP1_SDMA_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
/* TBD: Not in TRM */
#define L3FW_PRUSS1_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PRUSS2_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MA_MPU_NTTP_ERR_REG         (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_L3_INSTR_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)

#define L3FW_BB2D_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_BB2D_FW_ERROR_MASK)
#define L3FW_DEBUGSS_CT_TBR_ERR_MASK      (                     \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_MASK | \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED6_MASK)
#define L3FW_DSS_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_MASK)
#define L3FW_GPU_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPU_FW_ERROR_MASK)
#define L3FW_IVA_SL2IF_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_SL2_FW_ERROR_MASK)
#define L3FW_IPU1_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_MASK)
#define L3FW_IVA_CFG_ERR_MASK             ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_FW_ERROR_MASK)
#define L3FW_EMIF_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_MASK)
#define L3FW_GPMC_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_MASK)
#define L3FW_OCMC_RAM1_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK)
#define L3FW_QSPI_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_MASK)
#define L3FW_TPCC_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_MASK)
#define L3FW_TPTC_ERR_MASK                (                      \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_MASK | \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_MASK)
#define L3FW_MCASP3_ERR_MASK              ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP3_FW_ERROR_MASK)
#define L3FW_MCASP2_ERR_MASK              ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP2_FW_ERROR_MASK)
#define L3FW_MCASP1_ERR_MASK              ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_MASK)
#define L3FW_VCP1_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP1_FW_ERROR_MASK)
#define L3FW_PCIESS2_ERR_MASK             ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_MASK)
#define L3FW_PCIESS1_ERR_MASK             ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_MASK)
#define L3FW_IPU2_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_MASK)
#define L3FW_DSP1_SDMA_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_MASK)
/* TBD: Not in TRM */
#define L3FW_PRUSS2_ERR_MASK              (0)
#define L3FW_PRUSS1_ERR_MASK              (0)
#define L3FW_MA_MPU_NTTP_ERR_MASK         (0)
#define L3FW_L3_INSTR_ERR_MASK            (0)

/**
 * \brief  Macro containing instance summary of L3 Firewalls.
 *         Details:
 *         Element No.  Details
 *         1            Firewall Instance
 *         2            Number of region in Firewall
 *         3            Number of ports in Firewall
 *         This macro is used to initialize struct l3fwInstSummary_t in
 *         fwlibl3.h
 */
#define L3FW_INST_SUMMARY                                            \
    {                                                                \
        {L3FW_DSP1_SDMA_INST, 1U, 1U,                                \
         L3FW_DSP1_SDMA_ERR_REG, L3FW_DSP1_SDMA_ERR_MASK},           \
        {L3FW_DSS_INST, 8U, 1U,                                      \
         L3FW_DSS_ERR_REG, L3FW_DSS_ERR_MASK},                       \
        {L3FW_GPMC_INST, 8U, 1U,                                     \
         L3FW_GPMC_ERR_REG, L3FW_GPMC_ERR_MASK},                     \
        {L3FW_GPU_INST, 1U, 1U,                                      \
         L3FW_GPU_ERR_REG, L3FW_GPU_ERR_MASK},                       \
        {L3FW_IPU1_INST, 4U, 2U,                                     \
         L3FW_IPU1_ERR_REG, L3FW_IPU1_ERR_MASK},                     \
        {L3FW_IPU2_INST, 4U, 2U,                                     \
         L3FW_IPU2_ERR_REG, L3FW_IPU2_ERR_MASK},                     \
        {L3FW_PRUSS1_INST, 1U, 1U,                                   \
         L3FW_PRUSS1_ERR_REG, L3FW_PRUSS1_ERR_MASK},                 \
        {L3FW_PRUSS2_INST, 1U, 1U,                                   \
         L3FW_PRUSS2_ERR_REG, L3FW_PRUSS2_ERR_MASK},                 \
        {L3FW_IVA_CFG_INST, 1U, 1U,                                  \
         L3FW_IVA_CFG_ERR_REG, L3FW_IVA_CFG_ERR_MASK},               \
        {L3FW_IVA_SL2IF_INST, 4U, 1U,                                \
         L3FW_IVA_SL2IF_ERR_REG, L3FW_IVA_SL2IF_ERR_MASK},           \
        {L3FW_OCMC_RAM1_INST, 16U, 1U,                               \
         L3FW_OCMC_RAM1_ERR_REG, L3FW_OCMC_RAM1_ERR_MASK},           \
        {L3FW_EMIF_INST, 8U, 1U,                                     \
         L3FW_EMIF_ERR_REG, L3FW_EMIF_ERR_MASK},                     \
        {L3FW_MA_MPU_NTTP_INST, 8U, 1U,                              \
         L3FW_MA_MPU_NTTP_ERR_REG, L3FW_MA_MPU_NTTP_ERR_MASK},       \
        {L3FW_PCIESS1_INST, 8U, 1U,                                  \
         L3FW_PCIESS1_ERR_REG, L3FW_PCIESS1_ERR_MASK},               \
        {L3FW_PCIESS2_INST, 8U, 1U,                                  \
         L3FW_PCIESS2_ERR_REG, L3FW_PCIESS2_ERR_MASK},               \
        {L3FW_BB2D_INST, 1U, 1U,                                     \
         L3FW_BB2D_ERR_REG, L3FW_BB2D_ERR_MASK},                     \
        {L3FW_QSPI_INST, 1U, 1U,                                     \
         L3FW_QSPI_ERR_REG, L3FW_QSPI_ERR_MASK},                     \
        {L3FW_TPCC_INST, 1U, 1U,                                     \
         L3FW_TPCC_ERR_REG, L3FW_TPCC_ERR_MASK},                     \
        {L3FW_TPTC_INST, 2U, 2U,                                     \
         L3FW_TPTC_ERR_REG, L3FW_TPTC_ERR_MASK},                     \
        {L3FW_VCP1_INST, 1U, 1U,                                     \
         L3FW_VCP1_ERR_REG, L3FW_VCP1_ERR_MASK},                     \
        {L3FW_MCASP1_INST, 1U, 1U,                                   \
         L3FW_MCASP1_ERR_REG, L3FW_MCASP1_ERR_MASK},                 \
        {L3FW_MCASP2_INST, 1U, 1U,                                   \
         L3FW_MCASP2_ERR_REG, L3FW_MCASP2_ERR_MASK},                 \
        {L3FW_MCASP3_INST, 1U, 1U,                                   \
         L3FW_MCASP3_ERR_REG, L3FW_MCASP3_ERR_MASK},                 \
        {L3FW_L3_INSTR_INST, 2U, 1U,                                 \
         L3FW_L3_INSTR_ERR_REG, L3FW_L3_INSTR_ERR_MASK},             \
        {L3FW_DEBUGSS_CT_TBR_INST, 1U, 1U,                           \
         L3FW_DEBUGSS_CT_TBR_ERR_REG, L3FW_DEBUGSS_CT_TBR_ERR_MASK}, \
    }

typedef enum SocConnId
{
    SOC_CONNID_MPU           = 0x1U,
    SOC_CONNID_CS_DAP        = 0x4U,
    SOC_CONNID_DSP1_MDMA     = 0x8U,
    SOC_CONNID_DSP1_CFG      = 0x9U,
    SOC_CONNID_DSP1_DMA      = 0xAU,
    SOC_CONNID_IVA           = 0xEU,
    SOC_CONNID_PRUSS1_PRU1   = 0x14U,
    SOC_CONNID_PRUSS1_PRU2   = 0x15U,
    SOC_CONNID_PRUSS2_PRU1   = 0x16U,
    SOC_CONNID_PRUSS2_PRU2   = 0x17U,
    SOC_CONNID_IPU1          = 0x18U,
    SOC_CONNID_IPU2          = 0x19U,
    SOC_CONNID_DMA_SYSTEM_RD = 0x1AU,
    SOC_CONNID_DMA_SYSTEM_WR = 0x1AU,
    SOC_CONNID_TC1_EDMA_WR   = 0x1CU,
    SOC_CONNID_TC1_EDMA_RD   = 0x1CU,
    SOC_CONNID_TC2_EDMA_WR   = 0x1DU,
    SOC_CONNID_TC2_EDMA_RD   = 0x1DU,
    SOC_CONNID_DSS           = 0x20U,
    SOC_CONNID_MLB           = 0x21U,
    SOC_CONNID_MMU1          = 0x21U,
    SOC_CONNID_PCIE1         = 0x22U,
    SOC_CONNID_PCIE2         = 0x23U,
    SOC_CONNID_MMU2          = 0x23U,
    SOC_CONNID_VIP1_P1       = 0x24U,
    SOC_CONNID_VIP1_P2       = 0x24U,
    SOC_CONNID_CAL           = 0x25U,
    SOC_CONNID_VPE_P1        = 0x27U,
    SOC_CONNID_VPE_P2        = 0x27U,
    SOC_CONNID_MMC1          = 0x28U,
    SOC_CONNID_GPU_P1        = 0x28U,
    SOC_CONNID_MMC2          = 0x29U,
    SOC_CONNID_GPU_P2        = 0x29U,
    SOC_CONNID_BB2D_P1       = 0x2AU,
    SOC_CONNID_BB2D_P2       = 0x2AU,
    SOC_CONNID_GMAC_SW       = 0x2BU,
    SOC_CONNID_USB1          = 0x2CU,
    SOC_CONNID_USB2          = 0x2DU,
    SOC_CONNID_USB3          = 0x2EU,
    SOC_CONNID_SATA          = 0x33U
}SocConnId_t;

/*
 * L4 FIREWALL
 */
/* L4 Firewall Instance Summary */
#define L4FW_NUM_INST                                       (5U)
/**
 * \brief  Macro containing instance summary of L4 Firewalls.
 *         Details:
 *         Element No.  Details
 *         1            Firewall Instance Base Address
 *         2            Number of protection groups in Firewall
 *         3            Number of region in Firewall
 *         4            Number of ports in Firewall
 *         5            Address of control module error register
 *         6            Bit field corrosponding to error in register in 5
 *         This macro is used to initialize struct l4fwInstSummary_t in
 *         fwlibl4.h
 */
#define L4FW_INST_SUMMARY                                                   \
    {                                                                       \
        {SOC_L4_PER_AP_BASE, 8U, 84U, 3U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1,  \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_MASK},         \
        {SOC_L4_PER2_AP_BASE, 8U, 60U, 3U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_MASK},         \
        {SOC_L4_PER3_AP_BASE, 8U, 96U, 3U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_MASK},         \
        {SOC_L4_CFG_AP_BASE, 8U, 126U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_MASK},          \
        {SOC_L4_WKUP_AP_BASE, 8U, 31U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_MASK},          \
    }

/* ========================================================================== */
/*                         Structures and Enums                               */
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

#endif  /* CSLR_SOC_DEFINES_H_ */
/** @} */

/**
 *  \ingroup CSL_SOC
 *  \defgroup SOC_TDA2EX TDA2EX
 */
