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
 *  \ingroup SOC_TDA2PX
 *  \defgroup SOC_DEFINES SOC Defines
 *
 *  @{
 */
/**
 *  \file     tda2px/cslr_soc_defines.h
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
#define CSL_VPS_VIP_PER_CNT             (3U)

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

/** @brief Number of VPS DSS-Overlay manager instances                        */
#define CSL_VPS_DSS_OVLY_MGR_PER_CNT    (4U)


/** @brief Number of MMCSD instances                                          */
#define CSL_MMCHS_CNT                   ((uint32_t) 4U)

/** @brief Number of VPS ISS Capture instances */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT       (3U)

/** \brief CAL Instance 0 base address */
#define ISS_CALA_BASE_REGISTER                  (0x489B0000U)
/** \brief CAL RX Core 0/Phy 1 base address */
#define ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER  (0x489B0800)
/** \brief CAL RX Core 0/Phy 2 base address */
#define ISS_CALA_CAMERARX_CORE_1_BASE_REGISTER  (0x489B0900)

/** @brief ISS Base Registers */
#define ISS_TOP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x0U)
#define ISS_LVDSRX_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x4000U)
#define ISS_CTSET_BASE_REGISTER                 (SOC_ISS_REGS_BASE + 0x10000U)
#define ISS_CALB_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x13000U)
#define ISS_CALC_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x12000U)
#define ISS_SIMCOP_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x20000U)
#define ISS_ISP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x40000U)
#define ISS_ISP_SYS_BASE_REGISTER               (SOC_ISS_SYS_REGS_BASE + 0x40000U)

/* Base Addresses fro ISP Modules */
#define ISS_ISP_SYS1_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x0U)
#define ISS_ISP_SYS2_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0xA0U)
#define ISS_ISP_RSZ_BASE_REGISTER       (ISS_ISP_BASE_REGISTER + 0x400U)
#define ISS_ISP_IPIPE_BASE_REGISTER     (ISS_ISP_BASE_REGISTER + 0x800U)
#define ISS_ISP_ISIF_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x1000U)
#define ISS_ISP_IPIPEIF_BASE_REGISTER   (ISS_ISP_BASE_REGISTER + 0x1200U)
#define ISS_ISP_H3A_BASE_REGISTER       (ISS_ISP_BASE_REGISTER + 0x1400U)
#define ISS_ISP_SYS3_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x10000U)
#define ISS_ISP_NSF3_INST0_BASE_REGISTER (ISS_ISP_BASE_REGISTER + 0x10800u)
#define ISS_ISP_NSF3_INST1_BASE_REGISTER (ISS_ISP_BASE_REGISTER + 0x10C00u)
#define ISS_ISP_CNF1_BASE_REGISTER      (ISS_ISP_BASE_REGISTER + 0x10C00U)
#define ISS_ISP_GLBCE_BASE_REGISTER     (ISS_ISP_BASE_REGISTER + 0x11000U)
#define ISS_ISP_GLBCE_STATS_MEM_ADDR    (ISS_ISP_SYS_BASE_REGISTER + 0x12000U)
#define ISS_ISP_GLBCE_STATS_MEM_SIZE	(16U*1024U)

/* Simcop Modules Base Registers */
#define ISS_SIMCOP_LDC_REGISTERS        (ISS_SIMCOP_BASE_REGISTER + 0x100U)
#define ISS_SIMCOP_DMA_REGISTERS        (ISS_SIMCOP_BASE_REGISTER + 0x200U)
#define ISS_SIMCOP_VTNF_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xA00U)
#define ISS_SIMCOP_LDC_LUT_REGISTERS    (ISS_SIMCOP_BASE_REGISTER + 0x7400U)
#define ISS_SIMCOP_IM_C_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xC000U)
#define ISS_SIMCOP_IM_D_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xD000U)
#define ISS_SIMCOP_IM_E_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xE000U)
#define ISS_SIMCOP_IM_F_REGISTERS       (ISS_SIMCOP_BASE_REGISTER + 0xF000U)

/* Memory Addresses for the different tables */
#define ISS_ISP_IPIPE_HIST_MEM0_ADDR    (ISS_ISP_BASE_REGISTER + 0x2000u)
#define ISS_ISP_IPIPE_HIST_MEM1_ADDR    (ISS_ISP_BASE_REGISTER + 0x2800u)
#define ISS_ISP_IPIPE_HIST_MEM2_ADDR    (ISS_ISP_BASE_REGISTER + 0x3000u)
#define ISS_ISP_IPIPE_HIST_MEM3_ADDR    (ISS_ISP_BASE_REGISTER + 0x3800u)
#define ISS_ISP_IPIPE_HIST_SIZE         (2048u)

#define ISS_ISP_IPIPE_BSC_MEM0_ADDR     (ISS_ISP_BASE_REGISTER + 0x4000u)
#define ISS_ISP_IPIPE_BSC_MEM1_ADDR     (ISS_ISP_BASE_REGISTER + 0x6000u)
#define ISS_ISP_IPIPE_BSC_SIZE          (8192u)

#define ISS_ISP_IPIPE_DPC_MEM0_ADDR     (ISS_ISP_BASE_REGISTER + 0x8000u)
#define ISS_ISP_IPIPE_DPC_MEM1_ADDR     (ISS_ISP_BASE_REGISTER + 0x8400u)
#define ISS_ISP_IPIPE_DPC_SIZE          (1024u)

#define ISS_ISP_IPIPE_YEE_TABLE_ADDR    (ISS_ISP_BASE_REGISTER + 0x00008800u)
#define ISS_ISP_IPIPE_YEE_TABLE_SIZE    (512u)

#define ISS_ISP_IPIPE_GBCE_TABLE_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009000u)
#define ISS_ISP_IPIPE_GBCE_TABLE_SIZE   (2048u)

#define ISS_ISP_IPIPE_3DLUT_MEM0_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009800u)
#define ISS_ISP_IPIPE_3DLUT_MEM1_ADDR   (ISS_ISP_BASE_REGISTER + 0x00009C00u)
#define ISS_ISP_IPIPE_3DLUT_MEM2_ADDR   (ISS_ISP_BASE_REGISTER + 0x0000A000u)
#define ISS_ISP_IPIPE_3DLUT_MEM3_ADDR   (ISS_ISP_BASE_REGISTER + 0x0000A400u)
#define ISS_ISP_IPIPE_3DLUT_SIZE        (1024u)

#define ISS_ISP_IPIPE_GAMMA_R_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000A800u)
#define ISS_ISP_IPIPE_GAMMA_G_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000B000u)
#define ISS_ISP_IPIPE_GAMMA_B_ADDR      (ISS_ISP_BASE_REGISTER + 0x0000B800u)
#define ISS_ISP_IPIPE_GAMMA_SIZE        (2048u)

#define ISS_ISP_ISIF_LIN0_ADDR          (ISS_ISP_BASE_REGISTER + 0xC000u)
#define ISS_ISP_ISIF_LIN1_ADDR          (ISS_ISP_BASE_REGISTER + 0xC200u)
#define ISS_ISP_ISIF_LIN_SIZE           (1024u)

#define ISS_ISP_ISIF_DCCLAMP_MEM_ADDR   (ISS_ISP_BASE_REGISTER + 0xC800u)
#define ISS_ISP_ISIF_DCCLAMP_SIZE       (2048u)

#define ISS_ISP_ISIF_LSC_MEM0_ADDR      (ISS_ISP_BASE_REGISTER + 0xD000u)
#define ISS_ISP_ISIF_LSC_MEM1_ADDR      (ISS_ISP_BASE_REGISTER + 0xE800u)
#define ISS_ISP_ISIF_LSC_MEM_SIZE       (6144u)

#define ISS_ISP_IPIPEIF_LUT0_ADDR       (ISS_ISP_BASE_REGISTER + 0x00016000u)
#define ISS_ISP_IPIPEIF_LUT1_ADDR       (ISS_ISP_BASE_REGISTER + 0x00016C00u)
#define ISS_ISP_IPIPEIF_LUT2_ADDR       (ISS_ISP_BASE_REGISTER + 0x00017800u)

#define ISS_ISP_GLBCE_TABLE_ADDR        (ISS_ISP_BASE_REGISTER + 0x00012000u)

#define ISS_ISP_IPIPEIF_LUT0_SIZE       (513u * 4u)
#define ISS_ISP_IPIPEIF_LUT1_SIZE       (513u * 4u)
#define ISS_ISP_IPIPEIF_LUT2_SIZE       (513u * 4u)

#define CSL_ISS_IPIPE_PER_CNT    (1U)

#define CSL_ISS_ISIF_PER_CNT     (1U)

#define CSL_ISS_RSZ_PER_CNT      (1U)

#define CSL_ISS_NSF3_PER_CNT     (2U)

#define CSL_ISS_H3A_PER_CNT      (1U)

#define CSL_ISS_GLBCE_PER_CNT    (1U)
/** \brief Defines the total number of CAL instances.
 *   TDA2Px has an ISS module which has 2 CAL instances used in m2m mode only.
 *   TDA2Px also has one seperate CAL instance used for capture. */
#define CSL_CAL_PER_CNT          (3U)
/** \brief Defines the total number of PPI available per CAL */
#define CSL_CAL_PPI_CNT          (2U)
/** \brief Defines the total number of complex IO available per CAL */
#define CSL_CAL_CMPLXIO_CNT      (2U)
/** \brief Defines the total number of pixel processing context
 *          available per CAL */
#define CSL_CAL_PIX_PROC_CTX_CNT (4U)

#define CSL_ISS_LVDSRX_PER_CNT   (1U)

#define CSL_ISS_IPIPEIF_PER_CNT  (1U)

#define CSL_ISS_IRQ0_NUM         (32U)
#define CSL_ISS_IRQ1_NUM         (12U + 16U)
#define CSL_ISS_IRQ2_NUM         (13U + 16U)
#define CSL_ISS_IRQ3_NUM         (14U + 16U)
#define CSL_ISS_IRQ4_NUM         (15U + 16U)
#define CSL_ISS_IRQ5_NUM         (16U + 16U)

#define CSL_ISS_SIMCOP_PER_CNT           (1U)
#define CSL_ISS_SIMCOP_NUM_ACT_CTX       (1U)
#define CSL_ISS_SIMCOP_NUM_DMA_CH        (1U)
#define CSL_ISS_SIMCOP_NUM_IRQ           (1U)
#define CSL_ISS_SIMCOP_MAX_HWSEQ_STEPS   (4U)

/** @brief interrupt number for CAL. */
#define CSL_CAL_IRQ_NUM         (71U)
/******************************************************************************\
 * Interrupt Event IDs
\******************************************************************************/

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_VIP1INT0       (27U)
#define CSL_INTC_EVENTID_VIP2INT0       (28U)
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
#define CSL_INTC_EVENTID_I2CINT2        (42U)
#define CSL_INTC_EVENTID_I2CINT4        (48U)
#define CSL_INTC_EVENTID_I2CINT5        (49U)

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
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (CSL_XBAR_INST_IPU1_IRQ_27)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (CSL_XBAR_INST_IPU1_IRQ_28)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (CSL_XBAR_INST_IPU1_IRQ_29)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (CSL_XBAR_INST_IPU1_IRQ_30)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (CSL_XBAR_INST_IPU1_IRQ_31)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (CSL_XBAR_INST_IPU1_IRQ_32)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (CSL_XBAR_INST_IPU1_IRQ_33)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (CSL_XBAR_INST_IPU1_IRQ_59)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (CSL_XBAR_INST_IPU1_IRQ_60)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (CSL_XBAR_INST_IPU1_IRQ_61)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (CSL_XBAR_INST_IPU1_IRQ_62)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (CSL_XBAR_INST_IPU1_IRQ_63)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (CSL_XBAR_INST_IPU1_IRQ_69)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (CSL_XBAR_INST_IPU1_IRQ_70)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (CSL_XBAR_INST_IPU1_IRQ_71)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (CSL_XBAR_INST_IPU1_IRQ_72)
#elif defined (__ARM_ARCH_7A__)
/** @brief Defining McASP interrupt numbers for the A15 core                  */
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (CSL_XBAR_INST_MPU_IRQ_110)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (CSL_XBAR_INST_MPU_IRQ_111)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (CSL_XBAR_INST_MPU_IRQ_112)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (CSL_XBAR_INST_MPU_IRQ_113)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (CSL_XBAR_INST_MPU_IRQ_118)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (CSL_XBAR_INST_MPU_IRQ_119)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (CSL_XBAR_INST_MPU_IRQ_122)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (CSL_XBAR_INST_MPU_IRQ_123)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (CSL_XBAR_INST_MPU_IRQ_124)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (CSL_XBAR_INST_MPU_IRQ_125)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (CSL_XBAR_INST_MPU_IRQ_126)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (CSL_XBAR_INST_MPU_IRQ_127)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (CSL_XBAR_INST_MPU_IRQ_128)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (CSL_XBAR_INST_MPU_IRQ_129)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (CSL_XBAR_INST_MPU_IRQ_130)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (CSL_XBAR_INST_MPU_IRQ_134)
#elif defined (_TMS320C6X)
/** @brief Defining McASP interrupt numbers for the C66 core                  */
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (CSL_XBAR_INST_DSP1_IRQ_58)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (CSL_XBAR_INST_DSP1_IRQ_59)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (CSL_XBAR_INST_DSP1_IRQ_60)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (CSL_XBAR_INST_DSP1_IRQ_61)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (CSL_XBAR_INST_DSP1_IRQ_91)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (CSL_XBAR_INST_DSP1_IRQ_92)
/* McASP4 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_RXINT        (CSL_XBAR_INST_DSP1_IRQ_74)
/* McASP4 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP3_TXINT        (CSL_XBAR_INST_DSP1_IRQ_51)
/* McASP5 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_RXINT        (CSL_XBAR_INST_DSP1_IRQ_79)
/* McASP5 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP4_TXINT        (CSL_XBAR_INST_DSP1_IRQ_81)
/* McASP6 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_RXINT        (CSL_XBAR_INST_DSP1_IRQ_86)
/* McASP6 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP5_TXINT        (CSL_XBAR_INST_DSP1_IRQ_87)
/* McASP7 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_RXINT        (CSL_XBAR_INST_DSP1_IRQ_88)
/* McASP7 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP6_TXINT        (CSL_XBAR_INST_DSP1_IRQ_43)
/* McASP8 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_RXINT        (CSL_XBAR_INST_DSP1_IRQ_48)
/* McASP8 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP7_TXINT        (CSL_XBAR_INST_DSP1_IRQ_49)
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
#define L3FW_INST_NUM                                       (38U)

#define L3FW_EVE1_INST                  (SOC_SECURITYCORE_EVE1_BASE)
#define L3FW_EVE2_INST                  (SOC_SECURITYCORE_EVE2_BASE)
#define L3FW_EVE3_INST                  (SOC_SECURITYCORE_EVE3_BASE)
#define L3FW_EVE4_INST                  (SOC_SECURITYCORE_EVE4_BASE)
#define L3FW_BB2D_INST                  (0x4A21A000U)
#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_GPU_INST                   (SOC_SECURITYCORE_GPU_BASE)
#define L3FW_IPU1_INST                  (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_IVA_CFG_INST               (SOC_SECURITYCORE_IVA1_CONFIG_BASE)
#define L3FW_IVA_SL2IF_INST             (SOC_SECURITYCORE_IVA1_SL2IF_BASE)
#define L3FW_OCMC_RAM1_INST             (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_OCMC_RAM2_INST             (SOC_SECURITYCORE_OCMC_RAM2_BASE)
#define L3FW_OCMC_RAM3_INST             (SOC_SECURITYCORE_OCMC_RAM3_BASE)
#define L3FW_EMIF_INST                  (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_PRUSS1_INST                (SOC_SECURITYCORE_PRUSS1_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_TPCC_INST                  (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_TPTC_INST                  (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_PRUSS2_INST                (SOC_SECURITYCORE_PRUSS2_BASE)
#define L3FW_MCASP1_INST                (SOC_SECURITYCORE_MCASP1_BASE)
#define L3FW_MCASP2_INST                (SOC_SECURITYCORE_MCASP2_BASE)
#define L3FW_MCASP3_INST                (SOC_SECURITYCORE_MCASP3_BASE)
#define L3FW_PCIESS2_INST               (SOC_SECURITYCORE_PCIE2_BASE)
#define L3FW_PCIESS1_INST               (SOC_SECURITYCORE_PCIE1_BASE)
#define L3FW_VCP1_INST                  (SOC_SECURITYCORE_VCP1_BASE)
#define L3FW_VCP2_INST                  (SOC_SECURITYCORE_VCP2_BASE)
#define L3FW_IPU2_INST                  (SOC_SECURITYCORE_IPU2_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_DSP2_SDMA_INST             (SOC_SECURITYCORE_DSP2_SDMA_BASE)
#define L3FW_MA_MPU_NTTP_INST           (SOC_MA_MPU_NTTP_FW_CFG_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)
#define L3FW_OCMC_ROM_INST              (SOC_SECURITYCORE_OCMC_ROM_BASE)
#define L3FW_AES1_INST                  (SOC_SECURITYCORE_AES1_BASE)
#define L3FW_AES2_INST                  (SOC_SECURITYCORE_AES2_BASE)
#define L3FW_SHA2MD5_1_INST             (SOC_SECURITYCORE_SHA2MD5_P1_BASE)
#define L3FW_SHA2MD5_2_INST             (SOC_SECURITYCORE_SHA2MD5_P2_BASE)

#define L3FW_EVE1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EVE2_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EVE3_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EVE4_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_BB2D_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_DEBUGSS_CT_TBR_ERR_REG      (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_DSS_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_GPU_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IVA_SL2IF_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IPU1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IVA_CFG_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EMIF_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_GPMC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_OCMC_RAM1_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_OCMC_RAM2_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_OCMC_RAM3_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_QSPI_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TPCC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TPTC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP3_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP2_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP1_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_VCP1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_VCP2_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PCIESS2_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PCIESS1_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_IPU2_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_DSP1_SDMA_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_DSP2_SDMA_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
/* TBD: Not in TRM */
#define L3FW_OCMC_ROM_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PRUSS1_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_PRUSS2_ERR_REG              (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MA_MPU_NTTP_ERR_REG         (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_L3_INSTR_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_AES1_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_AES2_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_SHA2MD5_1_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_SHA2MD5_2_ERR_REG           (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)

#define L3FW_EVE1_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_MASK)
#define L3FW_EVE2_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE2_FW_ERROR_MASK)
#define L3FW_EVE3_ERR_MASK                ((uint32_t) 1U << 30U)
#define L3FW_EVE4_ERR_MASK                ((uint32_t) 1U << 31U)
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
#define L3FW_OCMC_RAM2_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM2_FW_ERROR_MASK)
#define L3FW_OCMC_RAM3_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM3_FW_ERROR_MASK)
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
#define L3FW_VCP2_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP2_FW_ERROR_MASK)
#define L3FW_PCIESS2_ERR_MASK             ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_MASK)
#define L3FW_PCIESS1_ERR_MASK             ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_MASK)
#define L3FW_IPU2_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_MASK)
#define L3FW_DSP1_SDMA_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_MASK)
#define L3FW_DSP2_SDMA_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_MASK)
/* TBD: Not in TRM */
#define L3FW_OCMC_ROM_ERR_MASK            (0)
#define L3FW_PRUSS2_ERR_MASK              (0)
#define L3FW_PRUSS1_ERR_MASK              (0)
#define L3FW_MA_MPU_NTTP_ERR_MASK         (0)
#define L3FW_L3_INSTR_ERR_MASK            (0)
#define L3FW_AES1_ERR_MASK                (0)
#define L3FW_AES2_ERR_MASK                (0)
#define L3FW_SHA2MD5_1_ERR_MASK           (0)
#define L3FW_SHA2MD5_2_ERR_MASK           (0)

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
        {L3FW_OCMC_RAM1_INST, 16U, 1U,                               \
         L3FW_OCMC_RAM1_ERR_REG, L3FW_OCMC_RAM1_ERR_MASK},           \
        {L3FW_OCMC_RAM2_INST, 16U, 1U,                               \
         L3FW_OCMC_RAM2_ERR_REG, L3FW_OCMC_RAM2_ERR_MASK},           \
        {L3FW_OCMC_RAM3_INST, 16U, 1U,                               \
         L3FW_OCMC_RAM3_ERR_REG, L3FW_OCMC_RAM3_ERR_MASK},           \
        {L3FW_OCMC_ROM_INST, 4U, 1U,                                 \
         L3FW_OCMC_ROM_ERR_REG, L3FW_OCMC_ROM_ERR_MASK},             \
        {L3FW_GPMC_INST, 8U, 1U,                                     \
         L3FW_GPMC_ERR_REG, L3FW_GPMC_ERR_MASK},                     \
        {L3FW_IVA_SL2IF_INST, 4U, 1U,                                \
         L3FW_IVA_SL2IF_ERR_REG, L3FW_IVA_SL2IF_ERR_MASK},           \
        {L3FW_GPU_INST, 1U, 1U,                                      \
         L3FW_GPU_ERR_REG, L3FW_GPU_ERR_MASK},                       \
        {L3FW_PCIESS1_INST, 8U, 1U,                                  \
         L3FW_PCIESS1_ERR_REG, L3FW_PCIESS1_ERR_MASK},               \
        {L3FW_PCIESS2_INST, 8U, 1U,                                  \
         L3FW_PCIESS2_ERR_REG, L3FW_PCIESS2_ERR_MASK},               \
        {L3FW_L3_INSTR_INST, 1U, 1U,                                 \
         L3FW_L3_INSTR_ERR_REG, L3FW_L3_INSTR_ERR_MASK},             \
        {L3FW_AES1_INST, 2U, 1U,                                     \
         L3FW_AES1_ERR_REG, L3FW_AES1_ERR_MASK},                     \
        {L3FW_AES2_INST, 2U, 1U,                                     \
         L3FW_AES2_ERR_REG, L3FW_AES2_ERR_MASK},                     \
        {L3FW_SHA2MD5_1_INST, 2U, 1U,                                \
         L3FW_SHA2MD5_1_ERR_REG, L3FW_SHA2MD5_1_ERR_MASK},           \
        {L3FW_SHA2MD5_2_INST, 2U, 1U,                                \
         L3FW_SHA2MD5_2_ERR_REG, L3FW_SHA2MD5_2_ERR_MASK},           \
        {L3FW_TPTC_INST, 2U, 2U,                                     \
         L3FW_TPTC_ERR_REG, L3FW_TPTC_ERR_MASK},                     \
        {L3FW_TPCC_INST, 1U, 1U,                                     \
         L3FW_TPCC_ERR_REG, L3FW_TPCC_ERR_MASK},                     \
        {L3FW_IPU1_INST, 4U, 1U,                                     \
         L3FW_IPU1_ERR_REG, L3FW_IPU1_ERR_MASK},                     \
        {L3FW_IPU2_INST, 4U, 1U,                                     \
         L3FW_IPU2_ERR_REG, L3FW_IPU2_ERR_MASK},                     \
        {L3FW_DSP1_SDMA_INST, 1U, 1U,                                \
         L3FW_DSP1_SDMA_ERR_REG, L3FW_DSP1_SDMA_ERR_MASK},           \
        {L3FW_DSP2_SDMA_INST, 1U, 1U,                                \
         L3FW_DSP2_SDMA_ERR_REG, L3FW_DSP2_SDMA_ERR_MASK},           \
        {L3FW_DSS_INST, 8U, 1U,                                      \
         L3FW_DSS_ERR_REG, L3FW_DSS_ERR_MASK},                       \
        {L3FW_IVA_CFG_INST, 1U, 1U,                                  \
         L3FW_IVA_CFG_ERR_REG, L3FW_IVA_CFG_ERR_MASK},               \
        {L3FW_DEBUGSS_CT_TBR_INST, 2U, 1U,                           \
         L3FW_DEBUGSS_CT_TBR_ERR_REG, L3FW_DEBUGSS_CT_TBR_ERR_MASK}, \
        {L3FW_EMIF_INST, 8U, 2U,                                     \
         L3FW_EMIF_ERR_REG, L3FW_EMIF_ERR_MASK},                     \
        {L3FW_MA_MPU_NTTP_INST, 8U, 2U,                              \
         L3FW_MA_MPU_NTTP_ERR_REG, L3FW_MA_MPU_NTTP_ERR_MASK},       \
        {L3FW_BB2D_INST, 1U, 1U,                                     \
         L3FW_BB2D_ERR_REG, L3FW_BB2D_ERR_MASK},                     \
        {L3FW_EVE1_INST, 1U, 1U,                                     \
         L3FW_EVE1_ERR_REG, L3FW_EVE1_ERR_MASK},                     \
        {L3FW_EVE2_INST, 1U, 1U,                                     \
         L3FW_EVE2_ERR_REG, L3FW_EVE2_ERR_MASK},                     \
        {L3FW_EVE3_INST, 1U, 1U,                                     \
         L3FW_EVE3_ERR_REG, L3FW_EVE3_ERR_MASK},                     \
        {L3FW_EVE4_INST, 1U, 1U,                                     \
         L3FW_EVE4_ERR_REG, L3FW_EVE4_ERR_MASK},                     \
        {L3FW_MCASP1_INST, 1U, 1U,                                   \
         L3FW_MCASP1_ERR_REG, L3FW_MCASP1_ERR_MASK},                 \
        {L3FW_MCASP2_INST, 1U, 1U,                                   \
         L3FW_MCASP2_ERR_REG, L3FW_MCASP2_ERR_MASK},                 \
        {L3FW_MCASP3_INST, 1U, 1U,                                   \
         L3FW_MCASP3_ERR_REG, L3FW_MCASP3_ERR_MASK},                 \
        {L3FW_QSPI_INST, 1U, 1U,                                     \
         L3FW_QSPI_ERR_REG, L3FW_QSPI_ERR_MASK},                     \
        {L3FW_VCP1_INST, 1U, 1U,                                     \
         L3FW_VCP1_ERR_REG, L3FW_VCP1_ERR_MASK},                     \
        {L3FW_VCP2_INST, 1U, 1U,                                     \
         L3FW_VCP2_ERR_REG, L3FW_VCP2_ERR_MASK},                     \
        {L3FW_PRUSS1_INST, 1U, 1U,                                   \
         L3FW_PRUSS1_ERR_REG, L3FW_PRUSS1_ERR_MASK},                 \
        {L3FW_PRUSS2_INST, 1U, 1U,                                   \
         L3FW_PRUSS2_ERR_REG, L3FW_PRUSS2_ERR_MASK},                 \
    }
typedef enum SocConnId
{
    SOC_CONNID_MPU           = 0x01U,
    SOC_CONNID_CS_DAP        = 0x04U,
    SOC_CONNID_DSP1_MDMA     = 0x08U,
    SOC_CONNID_DSP1_CFG      = 0x09U,
    SOC_CONNID_DSP1_DMA      = 0x0AU,
    SOC_CONNID_DSP2_DMA      = 0x0BU,
    SOC_CONNID_DSP2_CFG      = 0x0CU,
    SOC_CONNID_DSP2_MDMA     = 0x0DU,
    SOC_CONNID_IVA           = 0x0EU,
    SOC_CONNID_EVE1_MMU0     = 0x10U,
    SOC_CONNID_EVE2_MMU0     = 0x11U,
    SOC_CONNID_EVE3_MMU0     = 0x12U,
    SOC_CONNID_EVE4_MMU0     = 0x13U,
    SOC_CONNID_IPU1          = 0x18U,
    SOC_CONNID_IPU2          = 0x19U,
    SOC_CONNID_DMA_SYSTEM_RD = 0x1AU,
    SOC_CONNID_DMA_SYSTEM_WR = 0x1AU,
    SOC_CONNID_EDMA_TC1_WR   = 0x1CU,
    SOC_CONNID_EDMA_TC1_RD   = 0x1CU,
    SOC_CONNID_EDMA_TC2_WR   = 0x1DU,
    SOC_CONNID_EDMA_TC2_RD   = 0x1DU,
    SOC_CONNID_DSS           = 0x20U,
    SOC_CONNID_MLB           = 0x21U,
    SOC_CONNID_MMU1          = 0x21U,
    SOC_CONNID_PCIE1         = 0x22U,
    SOC_CONNID_PCIE2         = 0x23U,
    SOC_CONNID_MMU2          = 0x23U,
    SOC_CONNID_VIP1_P1       = 0x24U,
    SOC_CONNID_VIP1_P2       = 0x24U,
    SOC_CONNID_VIP2_P1       = 0x25U,
    SOC_CONNID_VIP2_P2       = 0x25U,
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
    SOC_CONNID_USB4          = 0x2FU,
    SOC_CONNID_SATA          = 0x33U,
    SOC_CONNID_EVE1_MMU1     = 0x34U,
    SOC_CONNID_EVE2_MMU1     = 0x35U,
    SOC_CONNID_EVE3_MMU1     = 0x36U,
    SOC_CONNID_EVE4_MMU1     = 0x37U
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
        {SOC_L4_PER2_AP_BASE, 8U, 52U, 3U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_MASK},         \
        {SOC_L4_PER3_AP_BASE, 8U, 96U, 3U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_MASK},         \
        {SOC_L4_CFG_AP_BASE, 8U, 106U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_MASK},          \
        {SOC_L4_WKUP_AP_BASE, 8U, 31U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_MASK},          \
    }

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the Mreqdomain initiator
 */
typedef enum CSL_mreqDomainInitiator
{
    CSL_MREQDOMAIN_INITIATOR_P1500 = 0x0U,
    CSL_MREQDOMAIN_INITIATOR_RESERVED1_FACEDETECT = 0x1U,
    CSL_MREQDOMAIN_INITIATOR_DSP1_CFG = 0x2U,
    CSL_MREQDOMAIN_INITIATOR_DSS = 0x3U,
    CSL_MREQDOMAIN_INITIATOR_IVAHD = 0x4U,
    CSL_MREQDOMAIN_INITIATOR_RESERVED2_ISS = 0x5U,
    CSL_MREQDOMAIN_INITIATOR_IPU1 = 0x6U,
    CSL_MREQDOMAIN_INITIATOR_GPU_P1 = 0x7U,
    CSL_MREQDOMAIN_INITIATOR_DSP2_CFG = 0x8U,
    CSL_MREQDOMAIN_INITIATOR_IPU2 = 0x9U,
    CSL_MREQDOMAIN_INITIATOR_MMC1 = 0xAU,
    CSL_MREQDOMAIN_INITIATOR_MMC2 = 0xBU,
    CSL_MREQDOMAIN_INITIATOR_EVE1_TC0 = 0xCU,
    CSL_MREQDOMAIN_INITIATOR_EVE2_TC0 = 0xDU,
    CSL_MREQDOMAIN_INITIATOR_USB1 = 0xEU,
    CSL_MREQDOMAIN_INITIATOR_USB2 = 0xFU,
    CSL_MREQDOMAIN_INITIATOR_USB3 = 0x10U,
    CSL_MREQDOMAIN_INITIATOR_SATA = 0x11U,
    CSL_MREQDOMAIN_INITIATOR_EVE3_TC0 = 0x12U,
    CSL_MREQDOMAIN_INITIATOR_EVE4_TC0 = 0x13U,
    CSL_MREQDOMAIN_INITIATOR_BB2D = 0x14U,
    CSL_MREQDOMAIN_INITIATOR_PRUSS1_PRU0 = 0x15U,
    CSL_MREQDOMAIN_INITIATOR_PRUSS2_PRU0 = 0x16U,
    CSL_MREQDOMAIN_INITIATOR_VIP1_P1 = 0x17U,
    CSL_MREQDOMAIN_INITIATOR_VIP2_P1 = 0x18U,
    CSL_MREQDOMAIN_INITIATOR_VIP3_P1 = 0x19U,
    CSL_MREQDOMAIN_INITIATOR_USB4 = 0x1AU,
    CSL_MREQDOMAIN_INITIATOR_MLB = 0x1BU,
    CSL_MREQDOMAIN_INITIATOR_PCIESS1 = 0x1CU,
    CSL_MREQDOMAIN_INITIATOR_PCIESS2 = 0x1DU,
    CSL_MREQDOMAIN_INITIATOR_MMU1 = 0x1EU,
    CSL_MREQDOMAIN_INITIATOR_MMU2 = 0x1FU,
    CSL_MREQDOMAIN_INITIATOR_GMACSW = 0x20U,
    CSL_MREQDOMAIN_INITIATOR_VPE_P1 = 0x21U,
    CSL_MREQDOMAIN_INITIATOR_DSP1_MDMA = 0x22U,
    CSL_MREQDOMAIN_INITIATOR_DSP2_MDMA = 0x23U,
    CSL_MREQDOMAIN_INITIATOR_VIP1_P2 = 0x24U,
    CSL_MREQDOMAIN_INITIATOR_VIP2_P2 = 0x25U,
    CSL_MREQDOMAIN_INITIATOR_VIP3_P2 = 0x26U,
    CSL_MREQDOMAIN_INITIATOR_VPE_P2 = 0x27U,
    CSL_MREQDOMAIN_INITIATOR_GPU_P2 = 0x28U,
    CSL_MREQDOMAIN_INITIATOR_PRUSS1_PRU1 = 0x29U,
    CSL_MREQDOMAIN_INITIATOR_PRUSS2_PRU1 = 0x2AU,
    CSL_MREQDOMAIN_INITIATOR_EVE1_TC1 = 0x2BU,
    CSL_MREQDOMAIN_INITIATOR_EVE2_TC1 = 0x2CU,
    CSL_MREQDOMAIN_INITIATOR_EVE3_TC1 = 0x2DU,
    CSL_MREQDOMAIN_INITIATOR_MAX_INITIATOR =
                                    CSL_MREQDOMAIN_INITIATOR_EVE3_TC1 + 1
} CSL_mreqDomainInitiator_t;

/**
 * \brief  Enum for the Mreqdomain ID
 */
typedef enum CSL_mreqDomainId
{
    CSL_MREQDOMAIN_ID_DOMAIN0 = 0x0U,
    /* MreqDomain[2:0]= 0b000 => DOMAIN0 */
    CSL_MREQDOMAIN_ID_DOMAIN1 = 0x1U,
    /* MreqDomain[2:0]= 0b001 => DOMAIN1 */
    CSL_MREQDOMAIN_ID_DOMAIN2 = 0x2U,
    /* MreqDomain[2:0]= 0b010 => DOMAIN2 */
    CSL_MREQDOMAIN_ID_DOMAIN3 = 0x3U,
    /* MreqDomain[2:0]= 0b011 => DOMAIN3 */
    CSL_MREQDOMAIN_ID_DOMAIN4 = 0x4U,
    /* MreqDomain[2:0]= 0b100 => DOMAIN4 */
    CSL_MREQDOMAIN_ID_DOMAIN5 = 0x5U,
    /* MreqDomain[2:0]= 0b101 => DOMAIN5 */
    CSL_MREQDOMAIN_ID_DOMAIN6 = 0x6U,
    /* MreqDomain[2:0]= 0b110 => DOMAIN6 */
    CSL_MREQDOMAIN_ID_DOMAIN7 = 0x7U,
    /* MreqDomain[2:0]= 0b111 => DOMAIN7 */
	CSL_MREQDOMAIN_ID_MAX = CSL_MREQDOMAIN_ID_DOMAIN7 + 1
} CSL_mreqDomainId_t;

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
 *  \defgroup SOC_TDA2PX TDA2PX
 */
