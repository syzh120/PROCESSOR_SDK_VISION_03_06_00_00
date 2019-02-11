/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 * \file main.c
 *
 * \brief     Power management Leakage Test
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/src/pmhal/prcm/common/hw_pmhal_data.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)
#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**<
 *  \brief Function to configure PCIE to be enabled.
 *
 *  \param  None
 *
 *  \return None
 */
void pciess1DependentInit(void);

/**<
 *  \brief Function to configure always enabled for all the modules.
 *
 *  \param  None
 *
 *  \return None
 */
void alwaysEnabledConfig(void);

/**<
 *  \brief Function to set module states.
 *
 *  \param  None
 *
 *  \return None
 */
void setModuleStates(void);

/**<
 *  \brief Function to set power domain for leakage by configuring the clock
 *         domain to sw-wkup.
 *
 *  \param  None
 *
 *  \return None
 */
void setPowerDomainStatesForLeakage(void);

/**<
 *  \brief Function to set PLL state to low power
 *
 *  \param  None
 *
 *  \return None
 */
void setPllStates(void);

/**<
 *  \brief Function to set special power down registers for certain modules
 *
 *  \param  None
 *
 *  \return None
 */
void modulePowerDownProgram(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

pmErrCode_t     finalSuccess = PM_SUCCESS;

pmlibSysConfigPowerStateParams_t gInputTable[] =
{
    {PMHAL_PRCM_MOD_MMC1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,          PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_ATL,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE4,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE1,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE2,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE3,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IO_SRCOMP_CORE,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MLB_SS,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DMA_SYSTEM,              PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_SL2,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IVA,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSP1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSP2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_BB2D,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSS,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SDVENC,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EVE1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EVE2,                    PMLIB_SYS_CONFIG_DISABLED      },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_EVE3,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EVE4,                    PMLIB_SYS_CONFIG_DISABLED      },
#endif
    {PMHAL_PRCM_MOD_CPGMAC,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPU,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C5,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER5,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER6,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER7,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER8,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART6,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IPU1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IPU2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SATA,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP2SCP1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP2SCP3,                PMLIB_SYS_CONFIG_DISABLED      },
    /*{PMHAL_PRCM_MOD_USB_OTG_SS1,             PMLIB_SYS_CONFIG_DISABLED      },
     * {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMLIB_SYS_CONFIG_DISABLED
     *      },
     * {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMLIB_SYS_CONFIG_DISABLED
     *      },
     * {PMHAL_PRCM_MOD_USB_OTG_SS4,             PMLIB_SYS_CONFIG_DISABLED
     *      },*/
    {PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP,     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DLL_AGING,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_INSTR,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP_WP_NOC,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPMC,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM3,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_ROM,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPARE_IVA2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VCP1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VCP2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_CME,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_HDMI,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_ICM,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SATA2,             PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN4,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN5,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN6,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL1,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL2,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL3,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPCC,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC1,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPTC2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_CFG,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCP2SCP2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC,   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM, PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP,  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPINLOCK,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IO_DELAY_BLOCK,          PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX10,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX11,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX12,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX13,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX3,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX4,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX5,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX6,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX7,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX8,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MAILBOX9,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C3,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C4,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER1,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER10,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER11,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER3,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER4,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER9,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ELM,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_HDQ1W,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI3,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI4,                  PMLIB_SYS_CONFIG_DISABLED      },
    /* Switch it off later */
    {PMHAL_PRCM_MOD_UART1,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART3,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART4,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART5,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO3,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO4,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO5,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO6,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO7,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO8,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMC3,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC4,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART7,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART8,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART9,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PRUSS1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PRUSS2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP3,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP4,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP5,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP6,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP7,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP8,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS3,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_QSPI,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER13,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER14,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER15,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER16,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_AES1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_AES2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DES3DES,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_FPKA,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RNG,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SHA2MD51,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SHA2MD52,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MPU,                     PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_MPU_MPU_DBG,             PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_RTCSS,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VIP1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VIP2,                    PMLIB_SYS_CONFIG_DISABLED      },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    {PMHAL_PRCM_MOD_VIP3,                    PMLIB_SYS_CONFIG_DISABLED      },
#endif
    {PMHAL_PRCM_MOD_VPE,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MPU_EMU_DBG,             PMLIB_SYS_CONFIG_AUTO_CG       },
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    /* Find state of ADC */
    {PMHAL_PRCM_MOD_ADC,                     PMLIB_SYS_CONFIG_DISABLED      },
#endif
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCAN1,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO1,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IO_SRCOMP_WKUP,          PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_KBD,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    /* Find the state of spare */
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER12,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART10,                  PMLIB_SYS_CONFIG_DISABLED      },
    /* Find state of WD_TIMER1 */
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMLIB_SYS_CONFIG_DISABLED      },
    /* Keep these modules in the end */
    {PMHAL_PRCM_MOD_L4_PER2,                 PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_L4_PER3,                 PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_DLL,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DMM,                     PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_EMIF1,                   PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_EMIF2,                   PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_EMIF_OCP_FW,             PMLIB_SYS_CONFIG_AUTO_CG       }
};

const uint32_t  numTableEntries = sizeof (gInputTable) /
                                  sizeof (pmlibSysConfigPowerStateParams_t);

pmhalPrcmCdId_t clockDomainsForLeakage[] =
{
    PMHAL_PRCM_CD_DSP1,
    PMHAL_PRCM_CD_DSP2,
    PMHAL_PRCM_CD_EVE1,
    PMHAL_PRCM_CD_EVE2,
    PMHAL_PRCM_CD_IPU
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    const pmlibSysConfigPowerStateParams_t uart1Disable =
    {PMHAL_PRCM_MOD_UART1, PMLIB_SYS_CONFIG_DISABLED};
    pmhalMpuLprmHgRampParams_t hgRampParam = {1, 0};

    PlatformUART1SetPinMux();
    UARTStdioInit();
    UARTPuts("\nPM Leakage Test App", -1);

    UARTPuts("\n------------------------------------------------------", -1);
    UARTPuts("\n Enabling all modules first", -1);
    UARTPuts("\n------------------------------------------------------\n", -1);
    alwaysEnabledConfig();

    UARTPuts("\n------------------------------------------------------", -1);
    UARTPuts("\n Setting Module states", -1);
    UARTPuts("\n------------------------------------------------------\n", -1);
    modulePowerDownProgram();
    setModuleStates();
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_GPIO8);

    UARTPuts("\n------------------------------------------------------", -1);
    UARTPuts("\n Setting Power Domain states", -1);
    UARTPuts("\n------------------------------------------------------\n", -1);
    setPowerDomainStatesForLeakage();

    UARTPuts("\n------------------------------------------------------", -1);
    UARTPuts("\n Setting DPLL states", -1);
    UARTPuts("\n------------------------------------------------------\n", -1);
    setPllStates();

    UARTPuts("\n------------------------------------------------------", -1);
    UARTPuts("\n Putting MPU to retention and switching off UART 1 ", -1);
    UARTPuts("\n------------------------------------------------------\n", -1);
    PMLIBSysConfigSetPowerState(&uart1Disable, 1U,
                                PM_TIMEOUT_INFINITE, NULL);

    PMHALPdmSetPDState(PMHAL_PRCM_PD_L3INIT,
                       PMHAL_PRCM_PD_STATE_OFF,
                       PM_TIMEOUT_NOWAIT);
    /* Enable Hg/FastRamp-up in Retention */
    PMHALMpuLprmSetHgRampParams(&hgRampParam);
    PMHALMpuLprmSetMercuryRetention();
    /* Switch off the CPU1 for A15 */
    MPU_WUGEN_Init();
    PMLIBCpu1ForcedOff();
    PMLIBCpuModePrepare(PMHAL_PRCM_MOD_MPU, PMLIB_IDLE_CPU_MODE_AUTOCG);
    PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
    return 0;
}

void modulePowerDownProgram(void)
{
    /* Put USB PHY to power down */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DEV_CONF,
                0x1);
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_SRCOMP_NORTH_SIDE, 0xFFFFFFFF);

    PMHALCMDpllSetOperationMode(PMHAL_PRCM_DPLL_USB,
                                PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE,
                                PM_TIMEOUT_NOWAIT);
    HW_WR_REG32(0x4a003c14, 0x0);

    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE4);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE1);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE2);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE3);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON);
    PMHALCMModuleDisableAllOptClock(PMHAL_PRCM_MOD_IO_SRCOMP_CORE);
}

void setPllStates(void)
{
    pmhalPrcmNodeId_t        dpllId;
    pmhalPrcmDpllPowerMode_t dpllMode;
    int32_t status = (int32_t) PM_SUCCESS;
    /* Ensure the DPLLs are switched off when the modules go to low power */
    for (dpllId = PMHAL_PRCM_DPLL_ABE; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        UARTPuts((char *) pmhalNodeList_names[dpllId], -1);
        if ((dpllId != PMHAL_PRCM_DPLL_PER) && (dpllId != PMHAL_PRCM_DPLL_DDR))
        {
            PMHALCMDpllGetOperatingMode(dpllId, &dpllMode);
            if ((dpllMode != PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE) ||
                (dpllMode != PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE))
            {
                status = PMHALCMDpllSetOperationMode(
                    dpllId,
                    PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE,
                    PM_TIMEOUT_NOWAIT);
                if (PM_CM_DPLL_POWER_MODE_NOT_SUPPORTED == status)
                {
                    status = PMHALCMDpllSetOperationMode(
                        dpllId,
                        PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE,
                        PM_TIMEOUT_NOWAIT);
                }
            }
        }
    }
    for (dpllId = PMHAL_PRCM_DPLL_ABE; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        if ((dpllId != PMHAL_PRCM_DPLL_PER) && (dpllId != PMHAL_PRCM_DPLL_DDR))
        {
            PMHALCMDpllGetOperatingMode(dpllId, &dpllMode);
            if ((dpllMode == PMHAL_PRCM_DPLL_POWER_MODE_LP_STP_MODE) ||
                (dpllMode == PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE))
            {
                UARTPuts(": Set Operation Mode PASS\n", -1);
            }
            else
            {
                UARTPuts(": Set Operation Mode FAIL\n", -1);
            }
        }
    }
    for (dpllId = PMHAL_PRCM_DPLL_ABE; dpllId <= PMHAL_PRCM_DPLL_MAX;
         dpllId++)
    {
        uint32_t id;
        id = PMUtilsGetDpllId(dpllId);
        /* Hard coding here as the API does not support any other mode than
         * auto idle disable to support Errata i810 */
        HW_WR_FIELD32(pmhalDpllElems[id].pllAutoIdleRegAddr,
                      PMHAL_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE, 0x1);
    }
}

void setPowerDomainStatesForLeakage(void)
{
    uint32_t    size = sizeof (clockDomainsForLeakage) /
                       sizeof (pmhalPrcmCdId_t);
    uint32_t    count  = 0U;
    pmErrCode_t status = PM_SUCCESS;

    for (count = 0U; count < size; count++)
    {
        status = PMHALCMSetCdClockMode(clockDomainsForLeakage[count],
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_NOWAIT);
        UARTPuts((char *)
                 pmhalClkDomain_t_names[clockDomainsForLeakage[count]], -1);
        if (status != PM_SUCCESS)
        {
            UARTPuts(": FAIL\n", -1);
        }
        else
        {
            UARTPuts(": PASS\n", -1);
        }
    }
}

void pciess1DependentInit(void)
{
    pmlibSysConfigPowerStateParams_t dependentTable[2];
    pmlibSysConfigErrReturn_t        depResultReturn[2];

    PMLIBSysConfigPowerStateParams_init(dependentTable, (uint32_t) 2U);
    dependentTable[0].modId    = PMHAL_PRCM_MOD_OCP2SCP1;
    dependentTable[0].pwrState = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
    dependentTable[1].modId    = PMHAL_PRCM_MOD_OCP2SCP3;
    dependentTable[1].pwrState = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;

    PMLIBSysConfigSetPowerState(dependentTable, (uint32_t) 2U,
                                PM_TIMEOUT_INFINITE,
                                depResultReturn);

    UARTPuts((char *) pmhalNodeList_names[PMHAL_PRCM_MOD_OCP2SCP1], -1);
    UARTPuts(": ", -1);
    if (PM_SUCCESS == depResultReturn[0].failCause)
    {
        UARTPuts("PASS\n", -1);
    }
    else
    {
        UARTPuts("PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                 -1);
        UARTPutNum(depResultReturn[0].failCause);
        UARTPuts("\n", -1);
    }

    UARTPuts((char *) pmhalNodeList_names[PMHAL_PRCM_MOD_OCP2SCP3], -1);
    UARTPuts(": ", -1);
    if (PM_SUCCESS == depResultReturn[1].failCause)
    {
        UARTPuts("PASS\n", -1);
    }
    else
    {
        UARTPuts("PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                 -1);
        UARTPutNum(depResultReturn[1].failCause);
        UARTPuts("\n", -1);
    }

    PlatformPCIESS1PllConfig();
    PlatformPCIESS1CtrlConfig();
    PCIESS1PhyConfig();
}

void alwaysEnabledConfig(void)
{
    pmlibSysConfigPowerStateParams_t inputTable;
    pmlibSysConfigErrReturn_t        resultReturn;
    pmhalPrcmModuleId_t idx;
    pmlibSysConfigPowerState_t       pwrSt;
    pmErrCode_t status = PM_SUCCESS;
    pwrSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        PMLIBSysConfigPowerStateParams_init(&inputTable, (uint32_t) 1U);
        inputTable.modId    = idx;
        inputTable.pwrState = pwrSt;
        if ((PMHAL_PRCM_MOD_PCIESS1 == idx) || (PMHAL_PRCM_MOD_PCIESS2 == idx)
            || (PMHAL_PRCM_MOD_USB_OTG_SS1 == idx)
            || (PMHAL_PRCM_MOD_USB_OTG_SS2 == idx)
            || (PMHAL_PRCM_MOD_USB_OTG_SS3 == idx)
            || (PMHAL_PRCM_MOD_USB_OTG_SS4 == idx))
        {
            continue;
        }
        else if ((PMHAL_PRCM_MOD_SDVENC == idx) ||
                 (PMHAL_PRCM_MOD_TIMER4 == idx) ||
                 (PMHAL_PRCM_MOD_MPU_EMU_DBG == idx) ||
                 (PMHAL_PRCM_MOD_MPU_MPU_DBG == idx) ||
                 (PMHAL_PRCM_MOD_SMARTREFLEX_MPU == idx))
        {
            continue;
        }
        else
        {}
        UARTPuts((char *) pmhalNodeList_names[idx], -1);
        UARTPuts(": ", -1);
        status = PMLIBSysConfigSetPowerState(&inputTable, (uint32_t) 1U,
                                             PM_TIMEOUT_INFINITE,
                                             &resultReturn);
        if (PM_SUCCESS == status)
        {
            UARTPuts("PASS\n", -1);
        }
        else
        {
            if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                resultReturn.failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn.failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
}

void setModuleStates(void)
{
    uint32_t                  i = 0U;
    pmhalPrcmModuleId_t       idx;
    pmErrCode_t               status = PM_SUCCESS;
    pmlibSysConfigErrReturn_t resultReturn[sizeof (gInputTable) /
                                           sizeof (
                                               pmlibSysConfigPowerStateParams_t)
    ];

    /* Some pre-processing steps */
    status = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_PCIE,
                                   PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                   PM_TIMEOUT_INFINITE);

    status =
        PMLIBSysConfigSetPowerState(gInputTable, (uint32_t) numTableEntries,
                                    PM_TIMEOUT_INFINITE,
                                    resultReturn);
    if (PM_SUCCESS == status)
    {
        UARTPuts("All Module Power Status Success... Printing Pass status\r\n",
                 -1);
    }

    /* Need an extra step for CD_L4SEC and CD_L3INIT to disable */
    status = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4SEC,
                                   PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                   PM_TIMEOUT_INFINITE);
    status = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L3INIT,
                                   PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                   PM_TIMEOUT_INFINITE);

    for (i = 0U; i < numTableEntries; i++)
    {
        idx = gInputTable[i].modId;
        if (idx < PMHAL_PRCM_MOD_COUNT)
        {
            UARTPuts((char *) pmhalNodeList_names[idx], -1);
        }
        UARTPuts(": ", -1);
        if (PMLIB_SYS_CONFIG_ALWAYS_ENABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_ALWAYS_ENABLED PASS\r\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\r\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\r\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\r\n", -1);
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_DISABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_DISABLED PASS\r\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be disabled from software\r\n",
                    -1);
                UARTPuts("Optional Clocks if any have been disabled\r\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES ==
                     resultReturn[i].failCause)
            {
                UARTPuts("Module has dependencies\r\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_DISABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\r\n", -1);
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_AUTO_CG == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_AUTO_CG PASS\r\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\r\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\r\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid CLKCTLR Register. Cannot be auto clock gated\r\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_AUTO_CG FAIL :Error Code Returned : ", -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\r\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
}

