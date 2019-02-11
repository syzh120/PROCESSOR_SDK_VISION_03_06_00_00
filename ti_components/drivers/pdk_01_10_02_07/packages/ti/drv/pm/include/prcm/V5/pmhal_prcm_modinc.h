/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file      V5/pmhal_prcm_modinc.h
 *
 *  \brief     Contains the list of modules to be included for compilation
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

#ifndef PMHAL_PRCM_MODINC_H_
#define PMHAL_PRCM_MODINC_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/**
 * \brief Modules which are included in build
 *        comment out in case the module is to be removed
 */

/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ATL */
#define BUILDCFG_PMHAL_PRCM_MOD_ATL
/** Macro to include DUMMY_MODULE4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
/** Macro to include DUMMY_MODULE1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
/** Macro to include DUMMY_MODULE2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
/** Macro to include DUMMY_MODULE3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
/** Macro to include IO_SRCOMP_CORE in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
/** Macro to include SMARTREFLEX_CORE in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/** Macro to include SMARTREFLEX_DSPEVE in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
/** Macro to include SMARTREFLEX_GPU in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
/** Macro to include SMARTREFLEX_IVAHD in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
/** Macro to include SMARTREFLEX_MPU in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
/** Macro to include USB_PHY1_ALWAYS_ON in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
/** Macro to include USB_PHY2_ALWAYS_ON in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
/** Macro to include USB_PHY3_ALWAYS_ON in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
/** Macro to include EFUSE_CTRL_CUST in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/** Macro to include DMA_SYSTEM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
/** Macro to include DSP1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DSP1

/** Macro to include DSP2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DSP2

/** Macro to include BB2D in build */
#define BUILDCFG_PMHAL_PRCM_MOD_BB2D
/** Macro to include DSS in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DSS
/** Macro to include SDVENC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SDVENC
/** Macro to include DLL in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DLL
/** Macro to include DMM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DMM
/** Macro to include EMIF1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/** Macro to include EMIF2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EMIF2
/** Macro to include EMIF_OCP_FW in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW

/** Macro to include EVE1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EVE1
/** Macro to include EVE2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_EVE2
/** Macro to include EVE3 in build */

/** Macro to include CPGMAC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/** Macro to include GPU in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPU
/** Macro to include I2C5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C5
/** Macro to include MCASP1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/** Macro to include TIMER5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/** Macro to include TIMER6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/** Macro to include TIMER7 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/** Macro to include TIMER8 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/** Macro to include UART6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART6
/** Macro to include IPU1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IPU1
/** Macro to include IPU2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IPU2
/** Macro to include IVA in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IVA
/** Macro to include SL2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SL2
/** Macro to include IEEE1500_2_OCP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/** Macro to include MMC1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMC1
/** Macro to include MMC2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMC2
/** Macro to include MLB_SS in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
/** Macro to include SATA in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SATA
/** Macro to include OCP2SCP1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
/** Macro to include OCP2SCP3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
/** Macro to include USB_OTG_SS1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
/** Macro to include USB_OTG_SS2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
/** Macro to include USB_OTG_SS3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
/** Macro to include USB_OTG_SS4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
/** Macro to include CTRL_MODULE_BANDGAP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
/** Macro to include DLL_AGING in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
/** Macro to include L3_INSTR in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
/** Macro to include L3_MAIN_2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/** Macro to include OCP_WP_NOC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/** Macro to include GPMC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPMC
/** Macro to include L3_MAIN_1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/** Macro to include MMU_EDMA in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/** Macro to include MMU_PCIESS in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
/** Macro to include OCMC_RAM1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/** Macro to include OCMC_RAM2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
/** Macro to include OCMC_RAM3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3

/** Macro to include SPARE_IVA2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
/** Macro to include VCP1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_VCP1
/** Macro to include VCP2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_VCP2
/** Macro to include SPARE_CME in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
/** Macro to include SPARE_HDMI in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
/** Macro to include SPARE_ICM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
/** Macro to include SPARE_SATA2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
/** Macro to include SPARE_UNKNOWN4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
/** Macro to include SPARE_UNKNOWN5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
/** Macro to include SPARE_UNKNOWN6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
/** Macro to include SPARE_VIDEOPLL1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
/** Macro to include SPARE_VIDEOPLL2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
/** Macro to include SPARE_VIDEOPLL3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
/** Macro to include TPCC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TPCC
/** Macro to include TPTC1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TPTC1
/** Macro to include TPTC2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TPTC2
/** Macro to include L4_CFG in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/** Macro to include OCP2SCP2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
/** Macro to include SAR_ROM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
/** Macro to include SPARE_SMARTREFLEX_RTC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
/** Macro to include SPARE_SMARTREFLEX_SDRAM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
/** Macro to include SPARE_SMARTREFLEX_WKUP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
/** Macro to include SPINLOCK in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/** Macro to include IO_DELAY_BLOCK in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
/** Macro to include MAILBOX1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/** Macro to include MAILBOX10 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
/** Macro to include MAILBOX11 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
/** Macro to include MAILBOX12 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
/** Macro to include MAILBOX13 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
/** Macro to include MAILBOX2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/** Macro to include MAILBOX3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
/** Macro to include MAILBOX4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
/** Macro to include MAILBOX5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
/** Macro to include MAILBOX6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
/** Macro to include MAILBOX7 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
/** Macro to include MAILBOX8 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
/** Macro to include MAILBOX9 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
/** Macro to include I2C1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C1
/** Macro to include I2C2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C2
/** Macro to include I2C3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C3
/** Macro to include I2C4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C4
/** Macro to include L4_PER1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/** Macro to include TIMER10 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER10
/** Macro to include TIMER11 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER11
/** Macro to include TIMER2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/** Macro to include TIMER3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/** Macro to include TIMER4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/** Macro to include TIMER9 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER9
/** Macro to include ELM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_ELM
/** Macro to include HDQ1W in build */
#define BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
/** Macro to include MCSPI1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/** Macro to include MCSPI2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/** Macro to include MCSPI3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/** Macro to include MCSPI4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/** Macro to include UART1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART1
/** Macro to include UART2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART2
/** Macro to include UART3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART3
/** Macro to include UART4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART4
/** Macro to include UART5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART5
/** Macro to include GPIO2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/** Macro to include GPIO3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/** Macro to include GPIO4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/** Macro to include GPIO5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO5
/** Macro to include GPIO6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO6
/** Macro to include GPIO7 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO7
/** Macro to include GPIO8 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO8
/** Macro to include MMC3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMC3
/** Macro to include MMC4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MMC4
/** Macro to include DCAN2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/** Macro to include L4_PER2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/** Macro to include UART7 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART7
/** Macro to include UART8 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART8
/** Macro to include UART9 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART9
/** Macro to include PRUSS1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
/** Macro to include PRUSS2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
/** Macro to include MCASP2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/** Macro to include MCASP3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/** Macro to include MCASP4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP4
/** Macro to include MCASP5 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP5
/** Macro to include MCASP6 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP6
/** Macro to include MCASP7 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP7
/** Macro to include MCASP8 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP8
/** Macro to include PWMSS1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/** Macro to include PWMSS2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
/** Macro to include PWMSS3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
/** Macro to include QSPI in build */
#define BUILDCFG_PMHAL_PRCM_MOD_QSPI
/** Macro to include L4_PER3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/** Macro to include TIMER13 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER13
/** Macro to include TIMER14 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER14
/** Macro to include TIMER15 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER15
/** Macro to include TIMER16 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER16
/** Macro to include AES1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_AES1
/** Macro to include AES2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_AES2
/** Macro to include DES3DES in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DES3DES
/** Macro to include DMA_CRYPTO in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
/** Macro to include FPKA in build */
#define BUILDCFG_PMHAL_PRCM_MOD_FPKA
/** Macro to include RNG in build */
#define BUILDCFG_PMHAL_PRCM_MOD_RNG
/** Macro to include SHA2MD51 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
/** Macro to include SHA2MD52 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
/** Macro to include MPU in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MPU
/** Macro to include MPU_MPU_DBG in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
/** Macro to include PCIESS1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
/** Macro to include PCIESS2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
/** Macro to include RTCSS in build */
#define BUILDCFG_PMHAL_PRCM_MOD_RTCSS

/** Macro to include LVDSRX in build */
#define BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
/** Macro to include VIP1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_VIP1
/** Macro to include VIP2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_VIP2
/** Macro to include VPE in build */
#define BUILDCFG_PMHAL_PRCM_MOD_VPE
/** Macro to include DEBUG_LOGIC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/** Macro to include MPU_EMU_DBG in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
/** Macro to include ADC in build */
#define BUILDCFG_PMHAL_PRCM_MOD_ADC
/** Macro to include COUNTER_32K in build */
#define BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/** Macro to include CTRL_MODULE_WKUP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
/** Macro to include DCAN1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/** Macro to include GPIO1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/** Macro to include IO_SRCOMP_WKUP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
/** Macro to include KBD in build */
#define BUILDCFG_PMHAL_PRCM_MOD_KBD
/** Macro to include L4_WKUP in build */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/** Macro to include SAR_RAM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
/** Macro to include SPARE_SAFETY1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
/** Macro to include SPARE_SAFETY2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
/** Macro to include SPARE_SAFETY3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
/** Macro to include SPARE_SAFETY4 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
/** Macro to include SPARE_UNKNOWN2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
/** Macro to include SPARE_UNKNOWN3 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
/** Macro to include TIMER1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/** Macro to include TIMER12 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER12
/** Macro to include UART10 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_UART10
/** Macro to include WD_TIMER1 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
/** Macro to include WD_TIMER2 in build */
#define BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
/** Macro to include CAL in build */
#define BUILDCFG_PMHAL_PRCM_MOD_CAL
/** Macro to include ISS in build */
#define BUILDCFG_PMHAL_PRCM_MOD_ISS
/** Macro to include MCAN in build */
#define BUILDCFG_PMHAL_PRCM_MOD_MCAN
/** Macro to include OCMC_ROM in build */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_PRCM_MODINC_H_ */

