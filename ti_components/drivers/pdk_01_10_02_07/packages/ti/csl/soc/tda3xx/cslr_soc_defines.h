/*
 *  Copyright (C) 2015-2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup SOC_DEFINES SOC Defines
 *
 *  @{
 */
/**
 *  \file     tda3xx/cslr_soc_defines.h
 *
 *  \brief    This file contains the enums and macros for the TDA3XX SOC
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

/** @brief Number of VPS DSS instances                                        */
#define CSL_VPS_DSS_PER_CNT             (1U)

/** @brief Number of VPS VIP instances                                        */
#define CSL_VPS_VIP_TOP_PER_CNT         (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS VIP-PORT instances                                   */
#define CSL_VPS_VIP_PORT_PER_CNT          (CSL_VPS_VIP_PER_CNT * 4U)

/** @brief Number of VPS VPDMA instances                                      */
#define CSL_VPS_VPDMA_PER_CNT      (CSL_VPS_VIP_PER_CNT)

/** @brief Number of VPS CSC instances                                        */
#define CSL_VPS_CSC_PER_CNT        (CSL_VPS_VIP_PER_CNT * 2U)

/** @brief Number of VPS SC instances                                         */
#define CSL_VPS_SC_PER_CNT         (CSL_VPS_VIP_PER_CNT * 2U)

/** @brief Number of VPS DSS-Video + Graphics Pipeline  */
#define CSL_VPS_DSS_VID_PIPE_PER_CNT  (3U)

/** @brief Number of VPS DSS-WB Pipelines  */
#define CSL_VPS_DSS_WB_PIPE_PER_CNT         (1U)

/** @brief Number of VPS DSS-WB Pipelines  */
#define CSL_VPS_ISS_CAPT_PIPE_PER_CNT       (3U)

/** @brief Number of VPS DSS-Overlay manager instances                        */
#define CSL_VPS_DSS_OVLY_MGR_PER_CNT  (2U)

/* VPS interrupt                                                              */
#define CSL_INTC_EVENTID_DSS_DISPC (23U)
/*Todo : Dummy and crossbar Mapped - please cross check before use */
#define CSL_INTC_EVENTID_VIP1INT0  (27U)
#define CSL_VPS_INTC_NUM           (0U)

/** @brief interrupt number for CAL. */
#define CSL_CAL_IRQ_NUM         (71U)

/** @brief ISS Base Registers */
#define ISS_TOP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x0U)
#define ISS_LVDSRX_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x4000U)
#define ISS_CTSET_BASE_REGISTER                 (SOC_ISS_REGS_BASE + 0x10000U)
#define ISS_CALA_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x12000U)
#define ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER  (SOC_ISS_REGS_BASE + 0x12800U)
#define ISS_CALB_BASE_REGISTER                  (SOC_ISS_REGS_BASE + 0x13000U)
#define ISS_SIMCOP_BASE_REGISTER                (SOC_ISS_REGS_BASE + 0x20000U)
#define ISS_ISP_BASE_REGISTER                   (SOC_ISS_REGS_BASE + 0x40000U)

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
#define ISS_ISP_GLBCE_STATS_MEM_ADDR    (ISS_ISP_BASE_REGISTER + 0x12000U)
#define ISS_ISP_GLBCE_STATS_MEM_SIZE    (16U*1024U)

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

#define CSL_CAL_PER_CNT          (2U)
/** \brief Defines the total number of PPI available per CAL */
#define CSL_CAL_PPI_CNT          (1U)
/** \brief Defines the total number of complex IO available per CAL */
#define CSL_CAL_CMPLXIO_CNT      (1U)
/** \brief Defines the total number of pixel processing context
 *          available per CAL */
#define CSL_CAL_PIX_PROC_CTX_CNT (4U)

#define CSL_ISS_LVDSRX_PER_CNT   (1U)

#define CSL_ISS_IPIPEIF_PER_CNT  (1U)

#define CSL_ISS_IRQ0_NUM         (33U)
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

typedef enum {
    UART1_INST = 0,
    UART2_INST,
    UART3_INST
}UART_INST_t;

/** @brief Peripheral Instances of MCSPI instances                            */
#define CSL_MCSPI_0                         (0)
#define CSL_MCSPI_1                         (1)
#define CSL_MCSPI_2                         (2)
#define CSL_MCSPI_3                         (3)

/** @brief Peripheral Instances of MMC/SD instances
 *                           */
typedef enum {
    MMC4_INST = 0
}MMC_INST_t;

/******************************************************************************\
 * Interrupt Event IDs
 \*****************************************************************************/

/* I2C interrupt                                                              */
#define CSL_INTC_EVENTID_I2CINT1        (41U)
#define CSL_INTC_EVENTID_I2CINT2        (42U)

/* To get the ducati int mux number, the 'CSL_INTMUX_OFFSET' has to be
 * subttracted from the interrupt number (directly mapped)
 */
#define    CSL_INTMUX_OFFSET                (23U)

/* MCSPI interrupt                                                            */
#define    CSL_INTC_EVENTID_MCSPIINT0       (64)
#define    CSL_INTC_EVENTID_MCSPIINT1       (65)
/*Todo : Dummy and crossbar Mapped - please cross check before use */
#define    CSL_INTC_EVENTID_MCSPIINT2       (48)
#define    CSL_INTC_EVENTID_MCSPIINT3       (49)

/* McASP Interrupts
 * All are crossbar mapped please cross check before use */
#if defined(__TI_ARM_V7M4__)
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (CSL_XBAR_INST_IPU1_IRQ_60)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (CSL_XBAR_INST_IPU1_IRQ_61)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (CSL_XBAR_INST_IPU1_IRQ_62)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (CSL_XBAR_INST_IPU1_IRQ_63)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (CSL_XBAR_INST_IPU1_IRQ_64)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (CSL_XBAR_INST_IPU1_IRQ_65)
#elif defined(_TMS320C6X)
/* McASP1 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_RXINT        (CSL_XBAR_INST_DSP1_IRQ_59)
/* McASP1 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP0_TXINT        (CSL_XBAR_INST_DSP1_IRQ_60)
/* McASP2 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_RXINT        (CSL_XBAR_INST_DSP1_IRQ_61)
/* McASP2 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP1_TXINT        (CSL_XBAR_INST_DSP1_IRQ_62)
/* McASP3 RX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_RXINT        (CSL_XBAR_INST_DSP1_IRQ_71)
/* McASP3 TX interrupt                                                        */
#define    CSL_INTC_EVENTID_MCASP2_TXINT        (CSL_XBAR_INST_DSP1_IRQ_72)
#endif

/* UART interrupt                                                             */
/*UART1 is being used in DMA Mode */
/*Instance Number Macro definitions are started from 0, it needs to be changed
 *to 1 later*/
#define    CSL_INTC_EVENTID_UARTINT0        (44U)
#define    CSL_INTC_EVENTID_UARTINT1        (43U)
#define    CSL_INTC_EVENTID_UARTINT2        (45U)
/*************************** EDMA RELATED DEFINES  ****************************/

/******************************************************************************\
 *  Parameterizable Configuration:- These are fed directly from the RTL
 *  parameters for the given SOC
 \******************************************************************************/

#define CSL_EDMA3_NUM_DMACH                 64
#define CSL_EDMA3_NUM_QDMACH                8
#define CSL_EDMA3_NUM_PARAMSETS             512
/* Todo : please cross check before use */
#define CSL_EDMA3_NUM_EVQUE                 2
#define CSL_EDMA3_CHMAPEXIST                1
#define CSL_EDMA3_NUM_REGIONS               8
#define CSL_EDMA3_MEMPROTECT                1

/******************************************************************************\
 * Channel Instance count
 \******************************************************************************/
#define CSL_EDMA3_CHA_CNT                   (CSL_EDMA3_NUM_DMACH + \
                                             CSL_EDMA3_NUM_QDMACH)

/* EDMA channel synchronization events                                        */
/* Todo : please cross check before use */
/* McASP0 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP0_RX             0
/* McASP0 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP0_TX             1
/* McASP1 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP1_RX             54
/* McASP1 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP1_TX             55
/* McASP2 Receive Event                                                       */
#define CSL_EDMA3_CHA_MCASP2_RX             56
/* McASP2 Transmit Event                                                      */
#define CSL_EDMA3_CHA_MCASP2_TX             57

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
#define CSL_MCSPI_1_NumOfPhyChannels       (2U)
#define CSL_MCSPI_2_NumOfPhyChannels       (2U)
#define CSL_MCSPI_3_NumOfPhyChannels       (1U)

#define CSL_NUM_MCSPI_INST                 (4U)

#define CSL_MCASP_0_NumSerializers         (16)

/******************************************************************************\
 * TESOC related info for this SoC.
 \******************************************************************************/
/**
 * \brief   No. of TESOC domains in SoC.
 */
#define TESOC_NUM_DOMAINS                                   (5U)

/**
 * \brief   No. of modules in SoC for which TESOC test can be run.
 *          Each TESOC domain can have multiple modules ex. ISSDSSVIP has
 *          ISS, DSS and VIP.
 */
#define TESOC_NUM_MODULES                                   (8U)

/**
 * \brief   No. of TESOC Tests currently supported by SoC.
 *          Each TESOC domain can have multiple tests ex. ISSDSSVIP has
 *          ISS, DSS and VIP and IPU has IPU LBIST & IPU MBIST.
 */
#define TESOC_NUM_TESTS                                   (9U)

/**
 * \brief   No. of slice blocks for each TESOC domain in SoC.
 */
#define TESOC_NUM_SLICE_BLOCKS                              (8U)

/**
 * \brief   No. of slices for each domain of TESOC in SoC.
 */
#define TESOC_NUM_SLICES                                    (256U)

/**
 * \brief  Macro to store no. of cycles of error log TESOC dumps after failure.
 */
#define  TESOC_DIAG_LOG_CYCLES                              (16U)

/**
 * \brief  Macro to store no. of 32 bit words of error diag data TESOC dumps.
 *         for each failure cycle.
 */
#define  TESOC_DIAG_LOG_DATA_SIZE                           (128U / 32U)

/**
 * \brief  TESOC RAM size in SoC.
 */
#define TESOC_RAM_SIZE                                      (0x10000U)

/**
 * \brief  TESOC ROM size in SoC.
 */
#define TESOC_ROM_SIZE                                      (0x280000U)

/**
 * \brief  TESOC IPU ROM size in SoC.
 *         This is part of TESOC ROM which contains IPU slices.
 *         Only IPU slices are in contiguous in TESOC ROM, for rest of domains
 *         slices are scattered throughout ROM.
 */
#define TESOC_ROM_IPU_SIZE                             ((uint32_t) 0x4B000U)

/**
 * \brief  TESOC IPU ROM CRC golden value.
 *         As CRC signature is 64 bit, it is split into
 *         two parts REGL and REGH.
 */
#define TESOC_ROM_IPU_CRC_SIGNATURE_REGL               ((uint32_t) 0x6F10A976U)
#define TESOC_ROM_IPU_CRC_SIGNATURE_REGH               ((uint32_t) 0x731BA4C1U)

/**
 * \brief   TESOC domain labels in the SoC.
 */
typedef enum tesocDomainLabel
{
    TESOC_DOMAIN_LABEL_IPU = 0x0,
    /**< IPU domain */
    TESOC_DOMAIN_LABEL_EVE = 0x1,
    /**< EVE domain */
    TESOC_DOMAIN_LABEL_DSP1 = 0x2,
    /**< TURING1 domain */
    TESOC_DOMAIN_LABEL_DSP2 = 0x3,
    /**< TURING2 domain */
    TESOC_DOMAIN_LABEL_ISSDSSVIP = 0x4,
    /**< ISS/DSS/VIP domain domain */
    TESOC_DOMAIN_LABEL_ISS = 0x4,
    /**< ISS domain is part of ISSDSSVIP and all 3 should be
     *   powered off for running this domain
     */
    TESOC_DOMAIN_LABEL_DSS = 0x4,
    /**< DSS domain is part of ISSDSSVIP and all 3 should be
     *   powered off for running this domain
     */
    TESOC_DOMAIN_LABEL_VIP = 0x4
                             /**< VIP domain is part of ISSDSSVIP and all 3
                              * should be powered off for running this domain.
                              */
} tesocDomainLabel_t;

/**
 * \brief   This macro defines the default slice configuration for each
 *          domain.
 *
 *          Though TesOC allows each domain to have maximum of TESOC_NUM_SLICES
 *          slices not all are used by domains in SoC. Only few are used for
 *          storing TDLs(patterns), remaining slices are dummy slices. This
 *          structure stores enabled slices for each domains in SoC.
 *          If value at slice location is 0, slice is not used for storing
 *          valid pattern.
 */
#define TESOC_DEFAULT_SLICE_CFG                                       \
    {                                                                 \
        {                                                             \
            TESOC_TEST_ID_IPU,                                        \
            TESOC_DOMAIN_LABEL_IPU,                                   \
            TRUE,                                                     \
            {0x003FFFFB, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}           \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_EVE,                                        \
            TESOC_DOMAIN_LABEL_EVE,                                   \
            FALSE,                                                    \
            {0x000FFBFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}           \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSP1,                                       \
            TESOC_DOMAIN_LABEL_DSP1,                                  \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0xFDFFFFFFU, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0} \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSP2,                                       \
            TESOC_DOMAIN_LABEL_DSP2,                                  \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0xFDFFFFFFU, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0} \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_ISSDSSVIP,                                  \
            TESOC_DOMAIN_LABEL_ISSDSSVIP,                             \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0x001DBFFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}   \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_ISS,                                        \
            TESOC_DOMAIN_LABEL_ISS,                                   \
            FALSE,                                                    \
            {0xFFFFFFFFU, 0x3FFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}       \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_DSS,                                        \
            TESOC_DOMAIN_LABEL_DSS,                                   \
            FALSE,                                                    \
            {0x0, 0x018000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}             \
        },                                                            \
        {                                                             \
            TESOC_TEST_ID_VIP,                                        \
            TESOC_DOMAIN_LABEL_VIP,                                   \
            FALSE,                                                    \
            {0x0, 0x1C0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}             \
        },                                                            \
        {                                                             \
            0,                                                        \
            0,                                                        \
            0,                                                        \
            {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}                  \
        }                                                             \
    }

/**
 *  \brief  This macro defines the diagnostic slice info for each domain.
 *          Refer #tesocAdvanceResult_t for details.
 *
 *          The diagnostic slice will check if TesOC is able to detect errors
 *          during LBIST. A false compare is made and if f TesOC detects the
 *          miscompare, then the slice fails. The failure in slice result for
 *          the diagnostic slice test means actual pass for diag test.
 */
#define TESOC_DIAGNOSTIC_SLICE_CFG                                \
    {                                                             \
        {TESOC_TEST_ID_IPU,                                       \
         TESOC_DOMAIN_LABEL_IPU,                                  \
         {0x00700000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (22U)}, \
        {TESOC_TEST_ID_EVE,                                       \
         TESOC_DOMAIN_LABEL_EVE,                                  \
         {0x00100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (20U)}, \
        {TESOC_TEST_ID_DSP1,                                      \
         TESOC_DOMAIN_LABEL_DSP1,                                 \
         {0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0}, (70U)},       \
        {TESOC_TEST_ID_DSP2,                                      \
         TESOC_DOMAIN_LABEL_DSP2,                                 \
         {0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0}, (70U)},       \
        {TESOC_TEST_ID_ISSDSSVIP,                                 \
         TESOC_DOMAIN_LABEL_ISSDSSVIP,                            \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-(int32_t)1)},\
        {TESOC_TEST_ID_ISS,                                       \
         TESOC_DOMAIN_LABEL_ISS,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-(int32_t)1)},\
        {TESOC_TEST_ID_DSS,                                       \
         TESOC_DOMAIN_LABEL_DSS,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-(int32_t)1)},\
        {TESOC_TEST_ID_VIP,                                       \
         TESOC_DOMAIN_LABEL_VIP,                                  \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-(int32_t)1)},\
        {0,                                                       \
         0,                                                       \
         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, (-(int32_t)1)} \
    }

/**
 * \brief   TESOC test ids for identifying tests.
 */
typedef enum tesocTestId
{
    TESOC_TEST_ID_IPU,
    /**< Test ID for IPU test*/
    TESOC_TEST_ID_EVE,
    /**< Test ID for EVE test*/
    TESOC_TEST_ID_DSP1,
    /**< Test ID for DSP1 test */
    TESOC_TEST_ID_DSP2,
    /**< Test ID for DSP1 test */
    TESOC_TEST_ID_ISSDSSVIP,
    /**< Test ID for ISS/DSS/VIP test */
    TESOC_TEST_ID_ISS,
    /**< Test ID for ISS test */
    TESOC_TEST_ID_DSS,
    /**< Test ID for DSS test */
    TESOC_TEST_ID_VIP
    /**< Test ID for VIP test */
} tesocTestId_t;

/**
 * \brief  Enum to select the COUNT1 clock source for DCC modules.
 */
typedef enum dccClkSrc1
{
    DCC_CLK_SRC1_DCC1_DPLLCORE_M2 = 0U,
    /**< DPLLCORE_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_M3 = 1U,
    /**< DPLLCORE_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H11 = 2U,
    /**< DPLLCORE_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H12 = 3U,
    /**< DPLLCORE_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H13 = 4U,
    /**< DPLLCORE_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H14 = 5U,
    /**< DPLLCORE_H14 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H21 = 6U,
    /**< DPLLCORE_H21 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC1_DPLLCORE_H22 = 7U,
    /**< DPLLCORE_H22 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_M2 = 16U,
    /**< DPLLDDR_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_M3 = 17U,
    /**< DPLLDDR_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_H11 = 18U,
    /**< DPLLDDR_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC2_DPLLDDR_H12 = 19U,
    /**< DPLLDDR_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_M2 = 32U,
    /**< DPLLPER_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_M2x2 = 33U,
    /**< DPLLPER_M2x2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H11 = 34U,
    /**< DPLLPER_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H12 = 35U,
    /**< DPLLPER_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H13 = 36U,
    /**< DPLLPER_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC3_DPLLPER_H14 = 37U,
    /**< DPLLPER_H14 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M2 = 48U,
    /**< DPLLDSP_GMAC_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M3 = 49U,
    /**< DPLLDSP_GMAC_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H11 = 50U,
    /**< DPLLDSP_GMAC_H11 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12 = 51U,
    /**< DPLLDSP_GMAC_H12 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H13 = 52U,
    /**< DPLLDSP_GMAC_H13 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_VIN1A = 53U,
    /**< VIN1A is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_VIN2A = 54U,
    /**< VIN2A is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC4_RXBTEHS_CLK = 55U,
    /**< RXBTEHS_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2 = 64U,
    /**< DPLLEVE_VID_M2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2 = 65U,
    /**< DPLLEVE_VID_M2x2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M3 = 66U,
    /**< DPLLEVE_VID_M3 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_SYS_CLK2 = 80U,
    /**< SYS_CLK2 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_XREF_CLK = 81U,
    /**< XREF_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_VIN1B = 82U,
    /**< VIN1B is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_VIN2B = 83U,
    /**< VIN2B is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_RXBTEHS_CLK = 84U,
    /**< RXBTEHS_CLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_MCASP_ACLKX = 85U,
    /**< MCASP_ACLKX is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC6_MCASP_ACLKR = 86U,
    /**< MCASP_ACLKR is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_DPLLCORE_H23 = 96U,
    /**< DPLLCORE_H23 is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MCASP_ACLKX = 97U,
    /**< MCASP_ACLKX is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MCASP_ACLKR = 98U,
    /**< MCASP_ACLKR is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_MDIO_MCLK = 99U,
    /**< MDIO_MCLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_DCC7_RGMII_RXCLK = 100U,
    /**< RGMII_RXCLK is selected as source for COUNT1 */
    DCC_CLK_SRC1_ALTERNATE_CLK = 10000U
    /**< Alternate clock is selected as source for COUNT1
     *   Value of 10000U is given because it will not used as source for DCC
     *   These values are directly use to program in DCC registers.
     */
}dccClkSrc1_t;

/* ESM number of groups */
#define ESM_NUM_GROUP_MAX                    (1U)
#define ESM_NUM_INTR_PER_GROUP               (128U)
/**
 * \brief  Enum to select the interrupt source for ESM group 1.
 */
typedef enum esmGroup1IntrSrc
{
    ESM_GROUP1_INTR_SRC_DCC1_IRQ_ERROR = 0,
    /**< DCC1_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC2_IRQ_ERROR = 1,
    /**< DCC2_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC3_IRQ_ERROR = 2,
    /**< DCC3_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_GPMC_DREQ = 3,
    /**< GPMC_DREQ interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CTRL_MODULE_CORE_IRQ_SEC_EVTS = 4,
    /**< CTRL_MODULE_CORE_IRQ_SEC_EVTS interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_DBG_ERR = 5,
    /**< L3_MAIN_IRQ_DBG_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_APP_ERR = 6,
    /**< L3_MAIN_IRQ_APP_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3_MAIN_IRQ_STAT_ALARM = 7,
    /**< L3_MAIN_IRQ_STAT_ALARM interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CTRL_MODULE_CORE_IRQ_THERMAL_ALERT = 8,
    /**< CTRL_MODULE_CORE_IRQ_THERMAL_ALERT interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_IRQ_TPCC_ERR = 10,
    /**< DSP1_IRQ_TPCC_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_IRQ_TPCC_ERR = 11,
    /**< DSP2_IRQ_TPCC_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TPCC_IRQ_ERR = 14,
    /**< EDMA_TPCC_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TC0_IRQ_ERR = 15,
    /**< EDMA_TC0_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EDMA_TC1_IRQ_ERR = 16,
    /**< EDMA_TC1_IRQ_ERR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC4_IRQ_ERROR = 19,
    /**< DCC4_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC5_IRQ_ERROR = 20,
    /**< DCC5_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC6_IRQ_ERROR = 21,
    /**< DCC6_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DCC7_IRQ_ERROR = 22,
    /**< DCC7_IRQ_ERROR interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CAM_RST = 23,
    /**< CAM_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_PWRON_RET_RST = 24,
    /**< CM_CORE_PWRON_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_RET_RST = 25,
    /**< CM_CORE_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CUSTEFUSE_RST = 26,
    /**< CUSTEFUSE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_PWRON_RST = 27,
    /**< DSP1_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_RET_RST = 28,
    /**< DSP1_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_RST = 29,
    /**< DSP1_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP1_SYS_RST = 30,
    /**< DSP1_SYS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_PWRON_RST = 31,
    /**< DSP2_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_RET_RST = 32,
    /**< DSP2_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_RST = 33,
    /**< DSP2_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSP2_SYS_RST = 34,
    /**< DSP2_SYS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSS_RET_RST = 35,
    /**< DSS_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DSS_RST = 36,
    /**< DSS_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_EARLY_PWRON_RST = 37,
    /**< EMU_EARLY_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_PWRON_RST = 38,
    /**< EMU_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EMU_RST = 39,
    /**< EMU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_CPU_RST = 40,
    /**< EVE_CPU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_PWRON_RST = 41,
    /**< EVE_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_EVE_RST = 42,
    /**< EVE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_CPU0_RST = 43,
    /**< IPU_CPU0_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_CPU1_RST = 44,
    /**< IPU_CPU1_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_PWRON_RST = 45,
    /**< IPU_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_RET_RST = 46,
    /**< IPU_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_IPU_RST = 47,
    /**< IPU_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3INIT_PWRON_RST = 48,
    /**< L3INIT_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L3INIT_RST = 49,
    /**< L3INIT_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_PWRON_RET_RST = 50,
    /**< L4PER_PWRON_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_RET_RST = 51,
    /**< L4PER_RET_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_L4PER_RST = 52,
    /**< L4PER_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_DEBUGSS_STANDBY = 53,
    /**< DEBUGSS_STANDBY interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_PWRON_RST = 56,
    /**< LPRM_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_RST = 57,
    /**< LPRM_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_LPRM_SECURE_RST = 58,
    /**< LPRM_SECURE_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_PWRON_RST = 59,
    /**< WKUPAON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_RST = 60,
    /**< WKUPAON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_WKUPAON_SYS_PWRON_RST = 61,
    /**< WKUPAON_SYS_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_AON_PWRON_RST = 62,
    /**< CM_CORE_AON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_CM_CORE_AON_RST = 63,
    /**< CM_CORE_AON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_COREAON_PWRON_RST = 64,
    /**< COREAON_PWRON_RST interrupt source for ESM group 1 */
    ESM_GROUP1_INTR_SRC_COREAON_RST = 65
                                      /**< COREAON_RST interrupt source for ESM
                                       *   group 1 */
}esmGroup1IntrSrc_t;

/* L3 FIREWALL */
/* L3 Firewall Instance Summary */
#define L3FW_INST_NUM                                       (17U)

#define L3FW_DEBUGSS_CT_TBR_INST        (SOC_SECURITYCORE_DEBUGSS_CT_TBR_BASE)
#define L3FW_DSP1_SDMA_INST             (SOC_SECURITYCORE_DSP1_SDMA_BASE)
#define L3FW_DSP2_SDMA_INST             (SOC_SECURITYCORE_DSP2_SDMA_BASE)
#define L3FW_DSS_INST                   (SOC_SECURITYCORE_DSS_BASE)
#define L3FW_EVE_INST                   (SOC_SECURITYCORE_EVE1_BASE)
#define L3FW_GPMC_INST                  (SOC_SECURITYCORE_GPMC_BASE)
#define L3FW_IPU_INST                   (SOC_SECURITYCORE_IPU1_BASE)
#define L3FW_L3_INSTR_INST              (SOC_SECURITYCORE_L3_INSTR_BASE)
#define L3FW_OCMC_RAM1_INST             (SOC_SECURITYCORE_OCMC_RAM1_BASE)
#define L3FW_EMIF_INST                  (SOC_SECURITYCORE_OCP_FW_EMIF_5430_BASE)
#define L3FW_QSPI_INST                  (SOC_SECURITYCORE_QSPI_BASE)
#define L3FW_EDMA_TPCC_INST             (SOC_SECURITYCORE_TPCC_BASE)
#define L3FW_TPTC_INST                  (SOC_SECURITYCORE_TPTC_BASE)
#define L3FW_CRC_INST                   (SOC_SECURITYCORE_CRC_BASE)
#define L3FW_TESOC_INST                 (SOC_SECURITYCORE_TESOC_BASE)
#define L3FW_ISS_INST                   (SOC_SECURITYCORE_ISS_BASE)
#define L3FW_MCASP_INST                 (SOC_SECURITYCORE_MCASP1_BASE)

#define L3FW_DEBUGSS_CT_TBR_ERR_REG       (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EVE_ERR_REG                  (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_DSS_ERR_REG                  (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_IPU_ERR_REG                  (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_EMIF_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_GPMC_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_OCMC_RAM1_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
#define L3FW_ISS_ERR_REG                  (CTRL_CORE_SEC_ERR_STATUS_FUNC_1)
/* TBD: Not in TRM */
#define L3FW_L3_INSTR_ERR_REG             (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_QSPI_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TPTC_ERR_REG                 (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_EDMA_TPCC_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_MCASP_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_DSP1_SDMA_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_DSP2_SDMA_ERR_REG            (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_TESOC_ERR_REG                (CTRL_CORE_SEC_ERR_STATUS_FUNC_2)
#define L3FW_CRC_ERR_REG                  (CTRL_CORE_SEC_ERR_STATUS_FUNC_3)

#define L3FW_DEBUGSS_CT_TBR_ERR_MASK      (                     \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_MASK | \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_MASK)
#define L3FW_EVE_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_MASK)
#define L3FW_DSS_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_MASK)
#define L3FW_IPU_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_MASK)
#define L3FW_EMIF_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_MASK)
#define L3FW_GPMC_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_MASK)
#define L3FW_OCMC_RAM1_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK)
#define L3FW_ISS_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_1_ISS_FW_ERROR_MASK)
/* TBD: Not in HW/TRM ??? */
#define L3FW_L3_INSTR_ERR_MASK            (0U)
#define L3FW_QSPI_ERR_MASK                ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_MASK)
#define L3FW_TPTC_ERR_MASK                (                      \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_MASK | \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_MASK)
#define L3FW_EDMA_TPCC_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_MASK)
#define L3FW_MCASP_ERR_MASK               ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_MASK)
#define L3FW_DSP1_SDMA_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_MASK)
#define L3FW_DSP2_SDMA_ERR_MASK           ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_MASK)
#define L3FW_TESOC_ERR_MASK               ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TESOC_FW_ERROR_MASK)
#define L3FW_CRC_ERR_MASK                 ( \
        CTRL_CORE_SEC_ERR_STATUS_FUNC_3_CRC_FW_ERROR_MASK)

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
        {L3FW_DEBUGSS_CT_TBR_INST, 2U, 1U,                           \
         L3FW_DEBUGSS_CT_TBR_ERR_REG, L3FW_DEBUGSS_CT_TBR_ERR_MASK}, \
        {L3FW_DSP1_SDMA_INST, 1U, 1U,                                \
         L3FW_DSP1_SDMA_ERR_REG, L3FW_DSP1_SDMA_ERR_MASK},           \
        {L3FW_DSP2_SDMA_INST, 1U, 1U,                                \
         L3FW_DSP2_SDMA_ERR_REG, L3FW_DSP2_SDMA_ERR_MASK},           \
        {L3FW_DSS_INST, 8U, 1U,                                      \
         L3FW_DSS_ERR_REG, L3FW_DSS_ERR_MASK},                       \
        {L3FW_EVE_INST, 1U, 1U,                                      \
         L3FW_EVE_ERR_REG, L3FW_EVE_ERR_MASK},                       \
        {L3FW_GPMC_INST, 8U, 1U,                                     \
         L3FW_GPMC_ERR_REG, L3FW_GPMC_ERR_MASK},                     \
        {L3FW_IPU_INST, 4U, 1U,                                      \
         L3FW_IPU_ERR_REG, L3FW_IPU_ERR_MASK},                       \
        {L3FW_L3_INSTR_INST, 1U, 1U,                                 \
         L3FW_L3_INSTR_ERR_REG, L3FW_L3_INSTR_ERR_MASK},             \
        {L3FW_OCMC_RAM1_INST, 24U, 1U,                               \
         L3FW_OCMC_RAM1_ERR_REG, L3FW_OCMC_RAM1_ERR_MASK},           \
        {L3FW_EMIF_INST, 24U, 1U,                                    \
         L3FW_EMIF_ERR_REG, L3FW_EMIF_ERR_MASK},                     \
        {L3FW_QSPI_INST, 4U, 1U,                                     \
         L3FW_QSPI_ERR_REG, L3FW_QSPI_ERR_MASK},                     \
        {L3FW_EDMA_TPCC_INST, 1U, 1U,                                \
         L3FW_EDMA_TPCC_ERR_REG, L3FW_EDMA_TPCC_ERR_MASK},           \
        {L3FW_TPTC_INST, 2U, 1U,                                     \
         L3FW_TPTC_ERR_REG, L3FW_TPTC_ERR_MASK},                     \
        {L3FW_CRC_INST, 4U, 1U,                                      \
         L3FW_CRC_ERR_REG, L3FW_CRC_ERR_MASK},                       \
        {L3FW_TESOC_INST, 4U, 1U,                                    \
         L3FW_TESOC_ERR_REG, L3FW_TESOC_ERR_MASK},                   \
        {L3FW_ISS_INST, 2U, 1U,                                      \
         L3FW_ISS_ERR_REG, L3FW_ISS_ERR_MASK},                       \
        {L3FW_MCASP_INST, 1U, 1U,                                    \
         L3FW_MCASP_ERR_REG, L3FW_MCASP_ERR_MASK},                   \
    }

typedef enum SocConnId
{
    SOC_CONNID_CS_DAP         = 0x4U,
    SOC_CONNID_IEEE1500_2_OCP = 0x5U,
    SOC_CONNID_DSP1_MDMA      = 0x8U,
    SOC_CONNID_DSP1_CFG       = 0x9U,
    SOC_CONNID_DSP1_DMA       = 0xAU,
    SOC_CONNID_DSP2_DMA       = 0xBU,
    SOC_CONNID_DSP2_CFG       = 0xCU,
    SOC_CONNID_DSP2_MDMA      = 0xDU,
    SOC_CONNID_EVE1_MMU0      = 0x10U,
    SOC_CONNID_IPU1           = 0x18U,
    SOC_CONNID_EDMA_TC1_WR    = 0x1CU,
    SOC_CONNID_EDMA_TC1_RD    = 0x1CU,
    SOC_CONNID_EDMA_TC2_WR    = 0x1DU,
    SOC_CONNID_EDMA_TC2_RD    = 0x1DU,
    SOC_CONNID_DSS            = 0x20U,
    SOC_CONNID_MMU1           = 0x21U,
    SOC_CONNID_VIP1_P1        = 0x24U,
    SOC_CONNID_VIP1_P2        = 0x24U,
    SOC_CONNID_GMAC_SW        = 0x2BU,
    SOC_CONNID_ISS_RT         = 0x30U,
    SOC_CONNID_ISS_NRT1       = 0x31U,
    SOC_CONNID_ISS_NRT2       = 0x32U,
    SOC_CONNID_EVE1_MMU1      = 0x34U,
    SOC_CONNID_STATCOLL1      = 0x38U,
    SOC_CONNID_STATCOLL2      = 0x38U,
    SOC_CONNID_STATCOLL3      = 0x38U,
    SOC_CONNID_STATCOLL4      = 0x38U
}SocConnId_t;

/* L4 FIREWALL */
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
        {SOC_L4_PER_AP_BASE, 8U, 77U, 2U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1,  \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_MASK},         \
        {SOC_L4_PER2_AP_BASE, 8U, 32U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_MASK},         \
        {SOC_L4_PER3_AP_BASE, 8U, 92U, 2U, CTRL_CORE_SEC_ERR_STATUS_FUNC_2, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_MASK},         \
        {SOC_L4_CFG_AP_BASE, 8U, 110U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
         CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_MASK},          \
        {SOC_L4_WKUP_AP_BASE, 8U, 43U, 1U, CTRL_CORE_SEC_ERR_STATUS_FUNC_1, \
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
 *  \defgroup SOC_TDA3XX TDA3XX
 */
