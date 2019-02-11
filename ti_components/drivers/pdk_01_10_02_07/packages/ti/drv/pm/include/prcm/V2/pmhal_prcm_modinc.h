/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 *  \file      V2/pmhal_prcm_modinc.h
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

/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#define BUILDCFG_PMHAL_PRCM_MOD_VIP1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#define BUILDCFG_PMHAL_PRCM_MOD_DSP1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#define BUILDCFG_PMHAL_PRCM_MOD_DSP2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#define BUILDCFG_PMHAL_PRCM_MOD_EVE1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DSS */
#define BUILDCFG_PMHAL_PRCM_MOD_DSS
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ISS */
#define BUILDCFG_PMHAL_PRCM_MOD_ISS
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CRC */
#define BUILDCFG_PMHAL_PRCM_MOD_CRC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#define BUILDCFG_PMHAL_PRCM_MOD_TESOC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#define BUILDCFG_PMHAL_PRCM_MOD_I2C2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#define BUILDCFG_PMHAL_PRCM_MOD_UART1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#define BUILDCFG_PMHAL_PRCM_MOD_UART2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ELM */
#define BUILDCFG_PMHAL_PRCM_MOD_ELM
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#define BUILDCFG_PMHAL_PRCM_MOD_UART3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#define BUILDCFG_PMHAL_PRCM_MOD_QSPI
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#define BUILDCFG_PMHAL_PRCM_MOD_GPMC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#define BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#define BUILDCFG_PMHAL_PRCM_MOD_TPCC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#define BUILDCFG_PMHAL_PRCM_MOD_TPTC1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#define BUILDCFG_PMHAL_PRCM_MOD_TPTC2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#define BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#define BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#define BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#define BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#define BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#define BUILDCFG_PMHAL_PRCM_MOD_MMC4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#define BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ESM */
#define BUILDCFG_PMHAL_PRCM_MOD_ESM
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC5
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC6
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
#define BUILDCFG_PMHAL_PRCM_MOD_DCC7
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#define BUILDCFG_PMHAL_PRCM_MOD_IPU1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#define BUILDCFG_PMHAL_PRCM_MOD_RTI1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#define BUILDCFG_PMHAL_PRCM_MOD_MCAN
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ATL */
#define BUILDCFG_PMHAL_PRCM_MOD_ATL
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#define BUILDCFG_PMHAL_PRCM_MOD_MCASP3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_ADC */
#define BUILDCFG_PMHAL_PRCM_MOD_ADC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#define BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#define BUILDCFG_PMHAL_PRCM_MOD_RTI2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#define BUILDCFG_PMHAL_PRCM_MOD_RTI3
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#define BUILDCFG_PMHAL_PRCM_MOD_RTI4
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#define BUILDCFG_PMHAL_PRCM_MOD_RTI5
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#define BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CSI1 */
#define BUILDCFG_PMHAL_PRCM_MOD_CSI1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CSI2 */
#define BUILDCFG_PMHAL_PRCM_MOD_CSI2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_LVDSRX */
#define BUILDCFG_PMHAL_PRCM_MOD_LVDSRX
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DLL */
#define BUILDCFG_PMHAL_PRCM_MOD_DLL
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#define BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#define BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#define BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#define BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#define BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#define BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#define BUILDCFG_PMHAL_PRCM_MOD_SDVENC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#define BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#define BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#define BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#define BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#define BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#define BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */
#define BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#define BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#define BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
/** Macro to include BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#define BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE

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

