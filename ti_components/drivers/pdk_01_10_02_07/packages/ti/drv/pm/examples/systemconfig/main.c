/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2017
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
 *  \file   main_tda2xx.c
 *
 *  \brief  System Config implementation example.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/pm/include/pmlib_sysconfig.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/prcm/hw_pmhal_data_names.h>
#include "app_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)
#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

pmErrCode_t    finalSuccess = PM_SUCCESS;

#if defined(SOC_AM574x) || defined(SOC_AM572x)|| defined(SOC_AM571x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined(SOC_DRA75x) || defined(SOC_TDA2EX) || defined(SOC_DRA72x)
pmlibSysConfigPowerStateParams_t gInputTable[] =
{
    {PMHAL_PRCM_MOD_ATL,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE4,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE1,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE2,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DUMMY_MODULE3,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IO_SRCOMP_CORE,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,        PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE,      PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SMARTREFLEX_GPU,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD,       PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if (defined (__ARM_ARCH_7A__) || defined (_TMS320C6X))
    {PMHAL_PRCM_MOD_SMARTREFLEX_MPU,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#endif
    {PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON,      PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DMA_SYSTEM,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DSP1,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_DSP2,                    PMLIB_SYS_CONFIG_AUTO_CG       },
#endif
    {PMHAL_PRCM_MOD_BB2D,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DSS,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SDVENC,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DLL,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DMM,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EMIF1,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_EMIF2,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#endif
    {PMHAL_PRCM_MOD_EMIF_OCP_FW,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
#if (defined (__ARM_ARCH_7A__) || defined (_TMS320C6X))
    {PMHAL_PRCM_MOD_EVE1,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EVE2,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_EVE3,                    PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_EVE4,                    PMLIB_SYS_CONFIG_AUTO_CG       },
#endif
#endif
#endif
    {PMHAL_PRCM_MOD_CPGMAC,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPU,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C5,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MCASP1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER5,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER6,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER7,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER8,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART6,                   PMLIB_SYS_CONFIG_DISABLED      },
#if !defined (__TI_ARM_V7M4__)
    {PMHAL_PRCM_MOD_IPU1,                    PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_IPU2,                    PMLIB_SYS_CONFIG_AUTO_CG       },
#endif
    {PMHAL_PRCM_MOD_IVA,                     PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_SL2,                     PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MLB_SS,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SATA,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP2SCP1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_OCP2SCP3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_OTG_SS1,             PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_OTG_SS2,             PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_USB_OTG_SS3,             PMLIB_SYS_CONFIG_DISABLED      },
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_USB_OTG_SS4,             PMLIB_SYS_CONFIG_DISABLED      },
#endif
    {PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP,     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DLL_AGING,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCP_WP_NOC,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPMC,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_EDMA,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_PCIESS,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_OCMC_RAM2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM3,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_ROM,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#endif
    {PMHAL_PRCM_MOD_SPARE_IVA2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VCP1,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VCP2,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_CME,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_HDMI,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_ICM,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SATA2,             PMLIB_SYS_CONFIG_DISABLED      },
    #if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN4,          PMLIB_SYS_CONFIG_DISABLED      },
    #endif
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN5,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN6,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL1,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL2,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_VIDEOPLL3,         PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPCC,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC1,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC2,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_CFG,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCP2SCP2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SAR_ROM,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC,   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM, PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP,  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
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
    {PMHAL_PRCM_MOD_I2C1,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C2,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C3,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C4,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_PER1,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER10,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER11,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER2,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER3,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER4,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER9,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ELM,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_HDQ1W,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI2,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI3,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI4,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART1,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART3,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART4,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART5,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO2,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO3,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO4,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO5,                   PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO6,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO7,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO8,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC3,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC4,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN2,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER2,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART7,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART8,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART9,                   PMLIB_SYS_CONFIG_DISABLED      },
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_PRUSS1,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PRUSS2,                  PMLIB_SYS_CONFIG_DISABLED      },
#endif
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
    {PMHAL_PRCM_MOD_L4_PER3,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER13,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER14,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER15,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER16,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_AES1,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_AES2,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DES3DES,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DMA_CRYPTO,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_FPKA,                    PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RNG,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SHA2MD51,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SHA2MD52,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MPU,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MPU_MPU_DBG,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    #if defined (SOC_TDA2EX) || defined (SOC_DRA72x)
    /* This module is present only in TDA2ex */
    {PMHAL_PRCM_MOD_LVDSRX,                  PMLIB_SYS_CONFIG_DISABLED      },
    #endif
    {PMHAL_PRCM_MOD_VIP1,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    #if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_VIP2,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    #endif
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_VIP3,                    PMLIB_SYS_CONFIG_DISABLED      },
    #endif
    {PMHAL_PRCM_MOD_VPE,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MPU_EMU_DBG,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    #if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM574x)
    {PMHAL_PRCM_MOD_ADC,                     PMLIB_SYS_CONFIG_DISABLED      },
    #endif
    {PMHAL_PRCM_MOD_COUNTER_32K,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,        PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN1,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO1,                   PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_IO_SRCOMP_WKUP,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_KBD,                     PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_WKUP,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SAR_RAM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY1,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY2,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY3,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_SAFETY4,           PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN2,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SPARE_UNKNOWN3,          PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER1,                  PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER12,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART10,                  PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_WD_TIMER1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_WD_TIMER2,               PMLIB_SYS_CONFIG_DISABLED      },
    #if defined (SOC_TDA2PX)
    {PMHAL_PRCM_MOD_CAL,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ISS,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MCAN,                    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    #endif
};
#endif

#if defined(SOC_TDA3XX) || defined(SOC_DRA78x)
pmlibSysConfigPowerStateParams_t gInputTable[] =
{
    {PMHAL_PRCM_MOD_CRC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DSP1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DSP2,                PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_DSS,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DLL,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EMIF1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#ifndef __TI_ARM_V7M4__
    {PMHAL_PRCM_MOD_EVE1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#endif
    {PMHAL_PRCM_MOD_CPGMAC,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER5,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER6,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER7,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER8,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#ifndef __TI_ARM_V7M4__
    {PMHAL_PRCM_MOD_IPU1,                PMLIB_SYS_CONFIG_AUTO_CG       },
#endif
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,      PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP, PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DLL_AGING,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_INSTR,            PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_MAIN_2,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCP_WP_NOC,          PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPMC,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_EDMA,            PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TESOC,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPCC,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_CFG,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPINLOCK,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX1,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX2,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_PER1,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC6,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC7,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC5,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ELM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ESM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI1,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MCSPI2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART3,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO3,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO4,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER2,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ADC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_QSPI,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER3,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VIP1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ISS,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_COUNTER_32K,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCAN1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_WKUP,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI5,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_CAMERARX,            PMLIB_SYS_CONFIG_DISABLED      }
};
#endif

const uint32_t numTableEntries = sizeof (gInputTable) /
                                 sizeof (pmlibSysConfigPowerStateParams_t);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32_t                  i = 0U;
    pmhalPrcmModuleId_t       idx;
    pmErrCode_t               status = PM_SUCCESS;
    pmlibSysConfigErrReturn_t resultReturn[sizeof (gInputTable) /
                                           sizeof (
                                               pmlibSysConfigPowerStateParams_t)
    ];
#if defined (SOC_AM574x) || defined(SOC_AM572x)|| defined(SOC_AM571x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined(SOC_DRA75x) || defined(SOC_TDA2EX) || defined(SOC_DRA72x)
    const pmlibSysConfigPowerStateParams_t des3desDependency =
    {PMHAL_PRCM_MOD_L3_INSTR, PMLIB_SYS_CONFIG_ALWAYS_ENABLED};
#endif

    AppUtils_defaultInit();
    AppUtils_printf("\nPM System Config Test App\n");

#if defined (SOC_AM574x)|| defined(SOC_AM572x)|| defined(SOC_AM571x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined(SOC_DRA75x) || defined(SOC_TDA2EX) || defined(SOC_DRA72x)
    status = PMLIBSysConfigSetPowerState(&des3desDependency, 1U,
                                         PM_TIMEOUT_INFINITE, NULL);
#ifdef __TI_ARM_V7M4__
    /* DES3DES does not complete its power sequence if the A15 is debug halted
     * Write to the DRM suspend control to ensure even if A15 is debug halted
     * the test case passes.
     */
    HW_WR_REG32(SOC_I_DRM_BASE + 0x23c, 0x50);

#endif
#endif

    status = PMLIBSysConfigSetPowerState(gInputTable, (uint32_t) numTableEntries,
                                         PM_TIMEOUT_INFINITE,
                                         resultReturn);

    if (PM_SUCCESS == status)
    {
        AppUtils_printf("All Module Power Status Success... Printing Pass status\n");
    }

    for (i = 0U; i < numTableEntries; i++)
    {
        idx = gInputTable[i].modId;
        AppUtils_printf((char *) pmhalNodeList_names[idx]);
        AppUtils_printf(": ");
        if (PMLIB_SYS_CONFIG_ALWAYS_ENABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                AppUtils_printf("PMLIB_SYS_CONFIG_ALWAYS_ENABLED PASS\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                AppUtils_printf(
                    "No Valid Module Mode, Cannot be enabled from software\n");
                AppUtils_printf("Optional Clocks if any have been enabled\n");
            }
            else
            {
                AppUtils_printf(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ");
                AppUtils_printf("%d", resultReturn[i].failCause);
                AppUtils_printf("\n");
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_DISABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                AppUtils_printf("PMLIB_SYS_CONFIG_DISABLED PASS\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED ==
                     resultReturn[i].failCause)
            {
                AppUtils_printf(
                    "No Valid Module Mode, Cannot be disabled from software\n");
                AppUtils_printf("Optional Clocks if any have been disabled\n");
            }
            else if (PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES ==
                     resultReturn[i].failCause)
            {
                AppUtils_printf("Module has dependencies\n");
            }
            else
            {
                AppUtils_printf(
                    "PMLIB_SYS_CONFIG_DISABLED FAIL :Error Code Returned : ");
                AppUtils_printf("%d", resultReturn[i].failCause);
                AppUtils_printf("\n");
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_AUTO_CG == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                AppUtils_printf("PMLIB_SYS_CONFIG_AUTO_CG PASS\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                AppUtils_printf(
                    "No Valid Module Mode, Cannot be enabled from software\n");
                AppUtils_printf("Optional Clocks if any have been enabled\n");
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG ==
                     resultReturn[i].failCause)
            {
                AppUtils_printf(
                    "No Valid CLKCTLR Register. Cannot be auto clock gated\n");
            }
            else
            {
                AppUtils_printf(
                    "PMLIB_SYS_CONFIG_AUTO_CG FAIL :Error Code Returned : ");
                AppUtils_printf("%d", resultReturn[i].failCause);
                AppUtils_printf("\n");
                finalSuccess = PM_FAIL;
            }
        }
    }
    if (PM_SUCCESS == finalSuccess)
    {
        AppUtils_printf("\n--------------------------------------------------\n");
        AppUtils_printf("Sysconfig Test case has passed\n");
    }
    else
    {
        AppUtils_printf("\n----------------------------------------------------");
        AppUtils_printf("Sysconfig Test case has failed\n");
    }
    return 0;
}
