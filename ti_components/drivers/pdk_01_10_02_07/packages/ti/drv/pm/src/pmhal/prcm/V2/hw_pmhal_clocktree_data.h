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
 *  \file      pmhal/tda3xx/hw_pmhal_clocktree_data.h
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare PRCM (internal) clocktree implementation.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

#ifndef HW_PMHAL_CLOCKTREE_DATA_H_
#define HW_PMHAL_CLOCKTREE_DATA_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include "pmhal_clocktree.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 * \brief Clock-tree Edge Availble Clock Nodes
 */
typedef enum pmhalEdgeNodes
{
    PMHAL_EDGE_LOWER_BOUND = (-(int32_t)1),
    /**< Lower bound Place Holder(inclusive) */
    PMHAL_EDGE_DPLL_CORE,
    /**< PM HAL Dpll Element CORE */
    PMHAL_EDGE_DPLL_DDR,
    /**< PM HAL Dpll Element DDR */
    PMHAL_EDGE_DPLL_DSP_GMAC,
    /**< PM HAL Dpll Element DSP_GMAC */
    PMHAL_EDGE_DPLL_PER,
    /**< PM HAL Dpll Element PER */
    PMHAL_EDGE_DPLL_EVE_VID_DSP,
    /**< PM HAL Dpll Element EVE_VID_DSP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    PMHAL_EDGE_MOD_SMARTREFLEX_CORE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    PMHAL_EDGE_MOD_SMARTREFLEX_DSPEVE,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    PMHAL_EDGE_MOD_EFUSE_CTRL_CUST,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_EDGE_MOD_DSS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    PMHAL_EDGE_MOD_EMIF1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_EDGE_MOD_CPGMAC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_EDGE_MOD_MCASP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    PMHAL_EDGE_MOD_TIMER5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    PMHAL_EDGE_MOD_TIMER6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    PMHAL_EDGE_MOD_TIMER7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    PMHAL_EDGE_MOD_TIMER8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    PMHAL_EDGE_MOD_IEEE1500_2_OCP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    PMHAL_EDGE_MOD_L3_MAIN_2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    PMHAL_EDGE_MOD_OCP_WP_NOC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    PMHAL_EDGE_MOD_L3_MAIN_1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_EDGE_MOD_MMU_EDMA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_EDGE_MOD_OCMC_RAM1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    PMHAL_EDGE_MOD_TESOC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    PMHAL_EDGE_MOD_L4_CFG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_EDGE_MOD_SPINLOCK,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_EDGE_MOD_MAILBOX1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_EDGE_MOD_MAILBOX2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_EDGE_MOD_I2C1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_EDGE_MOD_I2C2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    PMHAL_EDGE_MOD_L4_PER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    PMHAL_EDGE_MOD_DCC6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    PMHAL_EDGE_MOD_DCC7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    PMHAL_EDGE_MOD_TIMER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    PMHAL_EDGE_MOD_TIMER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    PMHAL_EDGE_MOD_TIMER4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    PMHAL_EDGE_MOD_DCC5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_EDGE_MOD_ELM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    PMHAL_EDGE_MOD_ESM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    PMHAL_EDGE_MOD_MCSPI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    PMHAL_EDGE_MOD_MCSPI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    PMHAL_EDGE_MOD_MCSPI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    PMHAL_EDGE_MOD_MCSPI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    PMHAL_EDGE_MOD_UART1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    PMHAL_EDGE_MOD_UART2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    PMHAL_EDGE_MOD_UART3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_EDGE_MOD_GPIO2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_EDGE_MOD_GPIO3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_EDGE_MOD_GPIO4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_EDGE_MOD_MMC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    PMHAL_EDGE_MOD_DCAN2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    PMHAL_EDGE_MOD_L4_PER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    PMHAL_EDGE_MOD_ADC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_EDGE_MOD_PWMSS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_EDGE_MOD_QSPI,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    PMHAL_EDGE_MOD_L4_PER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    PMHAL_EDGE_MOD_DCC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    PMHAL_EDGE_MOD_DCC2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    PMHAL_EDGE_MOD_DCC3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    PMHAL_EDGE_MOD_DCC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    PMHAL_EDGE_MOD_DEBUG_LOGIC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_EDGE_MOD_COUNTER_32K,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    PMHAL_EDGE_MOD_DCAN1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    PMHAL_EDGE_MOD_GPIO1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    PMHAL_EDGE_MOD_RTI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    PMHAL_EDGE_MOD_RTI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    PMHAL_EDGE_MOD_RTI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    PMHAL_EDGE_MOD_RTI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    PMHAL_EDGE_MOD_RTI5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    PMHAL_EDGE_MOD_TIMER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    PMHAL_EDGE_MOD_MCAN,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    PMHAL_EDGE_MOD_ATL,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_EDGE_MOD_MCASP2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_EDGE_MOD_MCASP3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
    PMHAL_EDGE_COUNT,
    /**< Enum Upper bound placeholder */
    PMHAL_EDGE_UNDEF
    /**< Undefined value */
} pmhalEdgeNodes_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< Device PM Clock tree graph  */
extern pmhalClockTree prcmGraph;

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* HW_PMHAL_DATA_H_ */
