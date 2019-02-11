/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file st_crcCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dcc.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_mdio.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_dcc.h>
#include <ti/drv/pm/pmhal.h>
#include <st_dcc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define SYS_CLK1_FREQ_KHZ                   ((uint32_t) 20000)
#define SYS_CLK2_FREQ_KHz                   ((uint32_t) 22579)
#define XREF_FREQ_KHz                       ((uint32_t) 50000)

/* Macros for mdio configuration */
/* wait until hardware is ready for another user access */
#define USERACCESS_GO    0x80000000
#define USERACCESS_READ  0x00000000
#define USERACCESS_WRITE 0x40000000
#define USERACCESS_ACK   1
#define USERACCESS_DATA  0x0000ffff
#define IPMDIOBASE           0x48485000
/*#define MDIO_VER             0x48485000
 * #define MDIO_CONTROL         0x48485004
 * #define MDIO_ALIVE           0x48485008
 * #define MDIO_LINK            0x4848500c
 * #define MDIO_LINKINTRAW      0x48485010
 * #define MDIO_LINKINTMASKED   0x48485014
 * #define MDIO_USERINTRAW      0x48485020
 * #define MDIO_USERINTMASKED   0x48485024
 * #define MDIO_USERINTMASKSET  0x48485028
 #define MDIO_USERINTMASKCLR  0x4848502c*/
#define MDIO_USERACCESS0     0x48485080
#define MDIO_USERPHYSEL0     0x48485084
#define MDIO_USERACCESS1     0x48485088
#define MDIO_USERPHYSEL1     0x4848508c

/* DPLL m,n and post dividers values */
#define DPLL_CORE_M_VAL                             ((uint32_t)266)
#define DPLL_CORE_N_VAL                             ((uint32_t)4)
#define DPLL_PER_M_VAL                              ((uint32_t)192)
#define DPLL_PER_N_VAL                              ((uint32_t)4)
#define DPLL_DDR_M_VAL                              ((uint32_t)266)
#define DPLL_DDR_N_VAL                              ((uint32_t)4)
#define DPLL_DSP_GMAC_M_VAL                         ((uint32_t)250)
#define DPLL_DSP_GMAC_N_VAL                         ((uint32_t)4)
#define DPLL_EVE_VID_DSP_M_VAL                      ((uint32_t)223)
#define DPLL_EVE_VID_DSP_N_VAL                      ((uint32_t)4)

#define DPLL_CORE_POST_DIV_M2                            ((uint32_t)2)
#define DPLL_CORE_POST_DIV_M3                            ((uint32_t)4)
#define DPLL_CORE_POST_DIV_H11                           ((uint32_t)7)
#define DPLL_CORE_POST_DIV_H12                           ((uint32_t)3)
#define DPLL_CORE_POST_DIV_H13                           ((uint32_t)43)
#define DPLL_CORE_POST_DIV_H14                           ((uint32_t)3)
#define DPLL_CORE_POST_DIV_H21                           ((uint32_t)10)
#define DPLL_CORE_POST_DIV_H22                           ((uint32_t)4)
#define DPLL_CORE_POST_DIV_H23                           ((uint32_t)9)

#define DPLL_PER_POST_DIV_M2                             ((uint32_t)8)
#define DPLL_PER_POST_DIV_H11                            ((uint32_t)5)
#define DPLL_PER_POST_DIV_H12                            ((uint32_t)7)
#define DPLL_PER_POST_DIV_H13                            ((uint32_t)7)
#define DPLL_PER_POST_DIV_H14                            ((uint32_t)3)

#define DPLL_DDR_POST_DIV_M2                             ((uint32_t)2)
#define DPLL_DDR_POST_DIV_H11                            ((uint32_t)7)

/* These are not used in UTs -  Just keeping here for completeness */
#define DPLL_DDR_POST_DIV_M3                             ((uint32_t)2)
#define DPLL_DDR_POST_DIV_H12                            ((uint32_t)7)
/* Above are not used in UTs -  Just keeping here for completeness */

#define DPLL_DSP_GMAC_POST_DIV_M2                        ((uint32_t)4)
#define DPLL_DSP_GMAC_POST_DIV_M3                        ((uint32_t)4)
#define DPLL_DSP_GMAC_POST_DIV_H11                       ((uint32_t)39)
#define DPLL_DSP_GMAC_POST_DIV_H12                       ((uint32_t)7)
#define DPLL_DSP_GMAC_POST_DIV_H13                       ((uint32_t)3)

#define DPLL_EVE_VID_DSP_POST_DIV_M2                     ((uint32_t)3)
#define DPLL_EVE_VID_DSP_POST_DIV_M3                     ((uint32_t)2)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for DCC module.
 *
 * \param   module          DCC module to enable.
 *
 * \retval  status          configuration status.
 */
int32_t DCCClockEnable(uint32_t module);

/**
 * \brief   This function returns reference clock frequency.
 *
 * \param   testClk          Clock whose frequency to be calculated.
 *
 * \param   dpllId          DPLL ID.
 *
 * \param   dpllPostDivider Struct to get post divider.
 *
 * \retval  frequency       Frequency of the given clock in KHz.
 */
uint32_t DCCAppGetTestClkfreqKHz(uint32_t testClk, pmhalPrcmNodeId_t *dpllId,
                                 pmhalPrcmPllPostDivValue_t *dpllPostDivider);

/**
 * \brief   This function returns seed value for COUNT1.
 *
 * \param   testClk          Reference clock frequency in KHz.
 *
 * \param   testClkCnt       Reference clock seed count.
 *
 * \retval  seed value      seed count for COUNT1.
 */
uint32_t DCCAppGetSrc1SeedVal(uint32_t testClk, uint32_t testClkCnt,
                              uint32_t testClkFreq);

/**
 * \brief   This function changes the test clock frequency.
 *
 * \param   dpllId          DPLL ID.
 *
 * \param   dpllPostDivider Struct to get post divider.
 *
 * \param   SYS_CLK1_FREQ_KHZ   Reference clock frequency.
 *
 * \retval  status          Configuration status.
 */
int32_t DCCAppTestClkFreqChange(pmhalPrcmNodeId_t          *dpllId,
                                pmhalPrcmPllPostDivValue_t *dpllPostDivider,
                                uint32_t                    testClk);

/**
 * \brief   This function is used to configure UART.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCAppUARTConfig(void);

/**
 * \brief   This function is used for misc configuration needed by DCC UT.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCAppMiscConfig(uint32_t clksrc);

/**
 * \brief   This function is used for mdio configurations.
 */
void cpsw_mdio_write(unsigned char phy_reg, unsigned short data, int PHY_ADDR);

/**
 * \brief   This function is used to get mdio configurations.
 */
void cpsw_mdio_read(unsigned char phy_reg, int PHY_ADDR);

/**
 * \brief   wait for go bit to 0 and ack bit to become 1.
 */
void wait_for_user_access();

/**
 * \brief   This function is used for DPLL configuration needed by DCC UT.
 *
 * \param   testClk          Clock whose frequency to be calculated.
 *
 * \param   dpllId          DPLL ID.
 *
 * \param   dpllPostDivider Struct to get post divider.
 *
 * \retval  STW_SOK if configuration is successful otherwise STW_EFAIL.
 */
int32_t DCCAppDPLLConfig(uint32_t testClk,
                         pmhalPrcmNodeId_t *dpllId,
                         pmhalPrcmPllPostDivValue_t *dpllPostDivider);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t DCCClockEnable(uint32_t module)
{
    int32_t status = STW_EFAIL, configStatus;

    switch (module)
    {
        case SOC_DCC1_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC1,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC2_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC2,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC3_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC3,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC4_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC4,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC5_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC5,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC6_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC6,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        case SOC_DCC7_BASE:
            /* Enable DCC module */
            configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC7,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS == configStatus)
            {
                status = STW_SOK;
            }
            break;
        default:
            status = STW_EBADARGS;
            break;
    }
    return status;
}

uint32_t DCCAppGetTestClkfreqKHz(uint32_t testClk, pmhalPrcmNodeId_t *dpllId,
                                 pmhalPrcmPllPostDivValue_t *dpllPostDivider)
{
    uint32_t multilpier, divider, postDivider;
    pmhalPrcmDpllPostDivId_t postDiv = PMHAL_PRCM_DPLL_POST_DIV_INVALID;
    uint32_t clkFreqKHz = 0U;

    switch (testClk)
    {
        case DCC_CLK_SRC1_DCC1_DPLLCORE_M2:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_M3:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H11:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H12:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H13:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H14:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H14;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H21:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H21;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H22:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H22;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_M2:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_M3:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_H11:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_H12:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_M2:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_M2x2:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2X2;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H11:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H12:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H13:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H14:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H14;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M2:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M3:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H11:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H13:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M3:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC6_SYS_CLK2:
            clkFreqKHz = SYS_CLK2_FREQ_KHz;
            break;
        case DCC_CLK_SRC1_DCC6_XREF_CLK:
            clkFreqKHz = XREF_FREQ_KHz;
            break;
        case DCC_CLK_SRC1_DCC7_DPLLCORE_H23:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H23;
            break;
        case DCC_CLK_SRC1_DCC6_MCASP_ACLKX:
            clkFreqKHz = 1100;
            break;
        case DCC_CLK_SRC1_DCC6_MCASP_ACLKR:
            clkFreqKHz = 20000;
            break;
        case DCC_CLK_SRC1_DCC7_MDIO_MCLK:
            clkFreqKHz = 868;
            break;
        case DCC_CLK_SRC1_DCC7_RGMII_RXCLK:
            clkFreqKHz = 2500;
            break;
        case DCC_CLK_SRC1_DCC4_VIN1A:
            clkFreqKHz = 97500;
            break;
        case DCC_CLK_SRC1_DCC4_VIN2A:
            clkFreqKHz = 97500;
            break;
        case DCC_CLK_SRC1_DCC6_VIN1B:
            clkFreqKHz = 97500;
            break;
        case DCC_CLK_SRC1_DCC6_VIN2B:
            clkFreqKHz = 97500;
            break;
        case DCC_CLK_SRC1_DCC4_RXBTEHS_CLK:
            clkFreqKHz = 117000;
            break;
    }
    if ((DCC_CLK_SRC1_DCC6_SYS_CLK2 != testClk) &&
        (DCC_CLK_SRC1_DCC6_XREF_CLK != testClk) &&
        (DCC_CLK_SRC1_DCC6_MCASP_ACLKX != testClk) &&
        (DCC_CLK_SRC1_DCC7_MDIO_MCLK != testClk) &&
        (DCC_CLK_SRC1_DCC7_RGMII_RXCLK != testClk) &&
        (DCC_CLK_SRC1_DCC4_VIN1A != testClk) &&
        (DCC_CLK_SRC1_DCC4_VIN2A != testClk) &&
        (DCC_CLK_SRC1_DCC6_VIN1B != testClk) &&
        (DCC_CLK_SRC1_DCC6_VIN2B != testClk) &&
        (DCC_CLK_SRC1_DCC4_RXBTEHS_CLK != testClk) &&
        (DCC_CLK_SRC1_DCC6_MCASP_ACLKR != testClk))
    {
        multilpier = PMHALCMDpllGetMultiplier(*dpllId);
        divider    = PMHALCMDpllGetDivider(*dpllId);
        dpllPostDivider->postDivId   = postDiv;
        dpllPostDivider->configValue = 1000;
        if (PM_SUCCESS == PMHALCMDpllGetPostDiv(*dpllId,
                                                dpllPostDivider, 1))
        {
            if (PMHAL_PRCM_DPLL_POST_DIV_M2 == postDiv)
            {
                postDivider = dpllPostDivider->configValue;
                clkFreqKHz  = (multilpier * SYS_CLK1_FREQ_KHZ /
                               postDivider / (divider + 1));
                /* Fix for absence of PMHAL_PRCM_DPLL_POST_DIV_M2X2 in pmhal */
                if (DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2 == testClk)
                {
                    clkFreqKHz *= 2;
                }
            }
            else if (PMHAL_PRCM_DPLL_POST_DIV_M2X2 == postDiv)
            {
                postDivider = dpllPostDivider->configValue;
                clkFreqKHz  = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
                               postDivider / (divider + 1));
            }
            else if (PMHAL_PRCM_DPLL_POST_DIV_M3 == postDiv)
            {
                postDivider = dpllPostDivider->configValue;
                clkFreqKHz  = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
                               postDivider / (divider + 1));
            }
            /*else if (PMHAL_PRCM_DPLL_POST_DIV_M4 == postDiv)
            {
                postDivider = dpllPostDivider->configValue;
                clkFreqKHz  = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
                               postDivider / (divider + 1));
            }*/
            else if ((PMHAL_PRCM_DPLL_POST_DIV_H11 <= postDiv) &&
                (PMHAL_PRCM_DPLL_POST_DIV_H24 >= postDiv))
            {
                postDivider = dpllPostDivider->configValue;
                // postDivider++;
                clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
                              postDivider / (divider + 1));
            }
            else
            {
            }
            /*if(PMHAL_PRCM_DPLL_POST_DIV_H11 == postDiv)
             * {
             *  if(DCC_CLK_SRC1_DCC1_DPLLCORE_H11 == testClk)
             *  {
             *      dpllPostDivider->configValue++;
             *  }
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H12 == postDiv)
             * {
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H13 == postDiv)
             * {
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H14 == postDiv)
             * {
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H21 == postDiv)
             * {
             *  dpllPostDivider->configValue++;
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H22 == postDiv)
             * {
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }
             * if(PMHAL_PRCM_DPLL_POST_DIV_H23 == postDiv)
             * {
             *  postDivider = dpllPostDivider->configValue;
             *  clkFreqKHz = (2 * multilpier * SYS_CLK1_FREQ_KHZ /
             *               postDivider / (divider + 1));
             * }*/
        }
        else
        {
            clkFreqKHz = 0U;
            UARTprintf("Error in calculating frequency.\n");
        }
    }
    return clkFreqKHz;
}

uint32_t DCCAppGetSrc1SeedVal(uint32_t testClk,
                              uint32_t refClkCnt,
                              uint32_t testClkFreq)
{
    uint32_t testClkCnt;

    testClkCnt = refClkCnt * testClkFreq / testClk;
    return testClkCnt;
}

int32_t DCCAppTestClkFreqChange(pmhalPrcmNodeId_t          *dpllId,
                                pmhalPrcmPllPostDivValue_t *dpllPostDivider,
                                uint32_t                    testClk)
{
    uint32_t status = FAIL;

    /*      Unlock MMR Lock1        */
    PlatformUnlockMMR();
    if (DCC_CLK_SRC1_DCC7_RGMII_RXCLK == testClk)
    {
        cpsw_mdio_write(0, 0x6100U, 0);
        cpsw_mdio_read(1, 0);
    }
    else if (DCC_CLK_SRC1_DCC7_MDIO_MCLK == testClk)
    {
        HW_WR_REG32(SOC_GMAC_MDIO_BASE + CSL_MDIO_CONTROL_REG, 0x40000001U);
    }
    else if (DCC_CLK_SRC1_DCC4_VIN1A == testClk)
    {
        /* Change PAD config setting to reserved - to cut the external clock */
        HW_WR_REG32(
            SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_IO_VIN1A_CLK0,
            0x00000001U);
    }
    else if (DCC_CLK_SRC1_DCC4_VIN2A == testClk)
    {
        /* Change PAD config setting to reserved - to cut the external clock */
        HW_WR_REG32(
            SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_IO_VIN2A_CLK0,
            0x0000000EU);
    }
    else if (DCC_CLK_SRC1_DCC6_VIN1B == testClk)
    {
        /* Change PAD config setting to reserved - to cut the external clock */
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_IO_VIN1A_DE0,
                    0x00000000U);
    }
    else if (DCC_CLK_SRC1_DCC6_VIN2B == testClk)
    {
        /* Change PAD config setting to reserved - to cut the external clock */
        HW_WR_REG32(
            SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_IO_VIN1A_FLD0,
            0x00000000U);
    }
    else if (DCC_CLK_SRC1_DCC4_RXBTEHS_CLK == testClk)
    {}
    else if (DCC_CLK_SRC1_DCC6_MCASP_ACLKR == testClk)
    {
        /* Change mcasp1_aclkr freq. */
        HW_WR_REG32(0x45800070, 0x00000023U);
    }
    else
    {
        dpllPostDivider->configValue++;
        if ((PMHAL_PRCM_DPLL_PER == *dpllId) &&
            (PMHAL_PRCM_DPLL_POST_DIV_H11 == dpllPostDivider->postDivId))
        {
            dpllPostDivider->configValue += 5U;
        }
        if ((PMHAL_PRCM_DPLL_PER == *dpllId) &&
            (PMHAL_PRCM_DPLL_POST_DIV_M2X2 == dpllPostDivider->postDivId))
        {
            dpllPostDivider->configValue -= 5U;
        }
        if ((PMHAL_PRCM_DPLL_CORE == *dpllId) &&
            (PMHAL_PRCM_DPLL_POST_DIV_H23 == dpllPostDivider->postDivId))
        {
            dpllPostDivider->configValue -= 5U;
        }
        dpllPostDivider->configValue %= 16;
        if (PM_SUCCESS == PMHALCMDpllSetPostDiv(*dpllId,
                                                dpllPostDivider, 1))
        {
            status = SUCCESS;
            UARTprintf("Frequency configuration successful.\n");
        }
        else
        {
            status = FAIL;
            UARTprintf("Error in configuring frequency.\n");
        }
    }
    /*      Lock MMR Lock1      */
    PlatformLockMMR();
    return status;
}

void DCCAppUARTConfig(void)
{
    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
}

void DCCAppMiscConfig(uint32_t clksrc)
{
    uint32_t temp;
    int32_t  configStatus;

    /*      Unlock MMR Lock1        */
    PlatformUnlockMMR();

    if (DCC_CLK_SRC1_DCC1_DPLLCORE_M3 == clksrc)
    {
        /* Select EVE clk to DPLL_CORE_M3 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xEFFFFFFF;
        temp |= 0x10000000;
        HW_WR_REG32(0x4a003c5c, temp);
        HW_WR_REG32(0x4ae06180, 0x1);
    }
    if (DCC_CLK_SRC1_DCC1_DPLLCORE_M2 == clksrc)
    {
        /* Enable Timer 5 for DPLLCORE_M2 */
        HW_WR_REG32(0x4a005558, 0x0b000002);
        HW_WR_REG32(0x4ae06158, 0x07);
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER5,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC1_DPLLCORE_H14 == clksrc)
    {
        /* Select DSP clk to DPLL_CORE_H14 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xF0FFFFFF;
        HW_WR_REG32(0x4a003c5c, temp);
        UARTprintf("Misc Config done.\n");
    }
    if (DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M3 == clksrc)
    {
        /* Select DSP clk to DPLLEVE_VID_M3 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xF0FFFFFF;
        temp |= 0x01000000;
        HW_WR_REG32(0x4a003c5c, temp);
        UARTprintf("Misc Config done.\n");
    }
    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M3 == clksrc)
    {
        /* Select DSP clk to DPLLDSP_GMAC_M3 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xF0FFFFFF;
        temp |= 0x02000000;
        HW_WR_REG32(0x4a003c5c, temp);
        UARTprintf("Misc Config done.\n");
    }
    if (DCC_CLK_SRC1_DCC3_DPLLPER_H12 == clksrc)
    {
        /* Enable DSS 5 for DPLLPER_H12 */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DSS,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            /* Select clk to DPLLPER_H12 */
            temp  = HW_RD_REG32(0x4a009120);
            temp |= 0x00000100;
            HW_WR_REG32(0x4a009120, temp);
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC3_DPLLPER_H13 == clksrc)
    {
        /* Select QSPI clk to DPLLPER_H13 */
        temp  = HW_RD_REG32(0x4a009838);
        temp &= 0xF0FFFFFF;
        temp |= 0x01000000;
        HW_WR_REG32(0x4a009838, temp);
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_QSPI,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC3_DPLLPER_M2 == clksrc)
    {
        /* Select DPLLPER_M3 for MCASP */
        temp  = HW_RD_REG32(0x4a005550);
        temp &= 0x00FFFFFF;
        temp |= 0x22000000;
        HW_WR_REG32(0x4a005550, temp);
        /* Enable MCASP1 for DPLLCORE_M2 */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCASP1,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H11 == clksrc)
    {
        /* Select DPLLDSP_GMAC_H11 for CPGMAC */
        temp  = HW_RD_REG32(0x4a0093d0);
        temp &= 0xFEFFFFFF;
        temp |= 0x01000000;
        HW_WR_REG32(0x4a0093d0, temp);
        /* Enable CPGMAC for DPLLCORE_M2 */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_CPGMAC,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12 == clksrc)
    {
        /* Enable CPGMAC for DPLLCORE_M2 */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_CPGMAC,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTprintf("Error in Misc Config.\n");
        }
        else
        {
            UARTprintf("Misc Config done.\n");
        }
    }
    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H13 == clksrc)
    {
        /* Select EVE clk to DPLLDSP_GMAC_H13 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xEFFFFFFF;
        temp |= 0x000000000;
        HW_WR_REG32(0x4a003c5c, temp);
        HW_WR_REG32(0x4ae06180, 0x1);
        UARTprintf("Misc Config done.\n");
    }
    if (DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2 == clksrc)
    {
        /* Select EVE clk to DPLLEVE_VID_M2x2 */
        temp  = HW_RD_REG32(0x4a003c5c);
        temp &= 0xEFFFFFFF;
        temp |= 0x000000000;
        HW_WR_REG32(0x4a003c5c, temp);
        HW_WR_REG32(0x4ae06180, 0x0);
        UARTprintf("Misc Config done.\n");
    }
    if (DCC_CLK_SRC1_DCC6_MCASP_ACLKR == clksrc)
    {
        /* Select and PAD for mcasp1_aclkr */
        HW_WR_REG32(0x4a0034e4, 0x00040001U);
        HW_WR_REG32(0x45800070, 0x00000020U);
        UARTprintf("Misc Config done.\n");
    }
    if ((DCC_CLK_SRC1_DCC7_MDIO_MCLK == clksrc) ||
        (DCC_CLK_SRC1_DCC7_RGMII_RXCLK == clksrc))
    {
        /* Configure MDIO control register */
        HW_WR_REG32(SOC_GMAC_MDIO_BASE + CSL_MDIO_CONTROL_REG, 0x40000089U);
        /* configure MDIO */
        cpsw_mdio_write(0, 0x4100U, 0);
        cpsw_mdio_read(1, 0);
        UARTprintf("Misc Config done.\n");
    }
    /*      Lock MMR Lock1      */
    PlatformLockMMR();
}

void cpsw_mdio_read(unsigned char phy_reg, int PHY_ADDR)
{
    int reg = 0;
    reg =
        (USERACCESS_GO | USERACCESS_READ | (phy_reg << 21) | (PHY_ADDR << 16));
    HW_WR_REG32(MDIO_USERACCESS0, reg);
    wait_for_user_access();
    reg = HW_RD_REG32(MDIO_USERACCESS0);
    reg = reg & 0x0000ffff;
    UARTprintf("PHYREG READ VALUE =  %x \n", reg);
}

void cpsw_mdio_write(unsigned char phy_reg, unsigned short data, int PHY_ADDR)
{
    int reg = 0;
    reg =
        (USERACCESS_GO | USERACCESS_WRITE |
         (phy_reg << 21) | (PHY_ADDR << 16) |
         (data & USERACCESS_DATA));
    HW_WR_REG32(MDIO_USERACCESS0, reg);
    wait_for_user_access();
    reg = HW_RD_REG32(MDIO_USERACCESS0);
    reg = reg & 0x0000ffff;
    UARTprintf("PHYREG WRITE VALUE  is  = %x \n", reg);
}

void wait_for_user_access()
{
    int reg, cnt = 0;
    reg = HW_RD_REG32(MDIO_USERACCESS0) & 0x80000000;
    while (reg != 0x0)
    {
        for (cnt = 0; cnt < 10000U; cnt++) ;
        for (cnt = 0; cnt < 10000U; cnt++) ;
        reg = HW_RD_REG32(MDIO_USERACCESS0) & 0x80000000;
    }
    reg = HW_RD_REG32(MDIO_USERACCESS0) & 0x20000000;
    while (reg != 0x20000000)
    {
        for (cnt = 0; cnt < 10000U; cnt++) ;
        reg = HW_RD_REG32(MDIO_USERACCESS0) & 0x80000000;
    }
}

int32_t DCCAppDPLLConfig(uint32_t testClk,
                         pmhalPrcmNodeId_t *dpllId,
                         pmhalPrcmPllPostDivValue_t *dpllPostDivider)
{
    uint32_t multilpier, divider, postDivider;
    uint32_t flag = 1U;
    pmhalPrcmDpllPostDivId_t postDiv;
    int32_t status = STW_SOK;

    switch (testClk)
    {
        case DCC_CLK_SRC1_DCC1_DPLLCORE_M2:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_M3:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H11:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H12:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H13:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H14:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H14;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H14;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H21:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H21;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H21;
            break;
        case DCC_CLK_SRC1_DCC1_DPLLCORE_H22:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H22;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H22;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_M2:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_DDR_M_VAL;
            divider = DPLL_DDR_N_VAL;
            postDivider = DPLL_DDR_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_M3:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            multilpier =DPLL_DDR_M_VAL;
            divider = DPLL_DDR_N_VAL;
            postDivider = DPLL_DDR_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_H11:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            multilpier =DPLL_DDR_M_VAL;
            divider = DPLL_DDR_N_VAL;
            postDivider = DPLL_DDR_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC2_DPLLDDR_H12:
            *dpllId = PMHAL_PRCM_DPLL_DDR;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            multilpier =DPLL_DDR_M_VAL;
            divider = DPLL_DDR_N_VAL;
            postDivider = DPLL_DDR_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_M2:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_M2x2:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2X2;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H11:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H12:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H13:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC3_DPLLPER_H14:
            *dpllId = PMHAL_PRCM_DPLL_PER;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H14;
            multilpier =DPLL_PER_M_VAL;
            divider = DPLL_PER_N_VAL;
            postDivider = DPLL_PER_POST_DIV_H14;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M2:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_DSP_GMAC_M_VAL;
            divider = DPLL_DSP_GMAC_N_VAL;
            postDivider = DPLL_DSP_GMAC_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_M3:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            multilpier =DPLL_DSP_GMAC_M_VAL;
            divider = DPLL_DSP_GMAC_N_VAL;
            postDivider = DPLL_DSP_GMAC_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H11:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H11;
            multilpier =DPLL_DSP_GMAC_M_VAL;
            divider = DPLL_DSP_GMAC_N_VAL;
            postDivider = DPLL_DSP_GMAC_POST_DIV_H11;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H12;
            multilpier =DPLL_DSP_GMAC_M_VAL;
            divider = DPLL_DSP_GMAC_N_VAL;
            postDivider = DPLL_DSP_GMAC_POST_DIV_H12;
            break;
        case DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H13:
            *dpllId = PMHAL_PRCM_DPLL_DSP_GMAC;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H13;
            multilpier =DPLL_DSP_GMAC_M_VAL;
            divider = DPLL_DSP_GMAC_N_VAL;
            postDivider = DPLL_DSP_GMAC_POST_DIV_H13;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_EVE_VID_DSP_M_VAL;
            divider = DPLL_EVE_VID_DSP_N_VAL;
            postDivider = DPLL_EVE_VID_DSP_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M2x2:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M2;
            multilpier =DPLL_EVE_VID_DSP_M_VAL;
            divider = DPLL_EVE_VID_DSP_N_VAL;
            postDivider = DPLL_EVE_VID_DSP_POST_DIV_M2;
            break;
        case DCC_CLK_SRC1_DCC5_DPLLEVE_VID_M3:
            *dpllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_M3;
            multilpier =DPLL_EVE_VID_DSP_M_VAL;
            divider = DPLL_EVE_VID_DSP_N_VAL;
            postDivider = DPLL_EVE_VID_DSP_POST_DIV_M3;
            break;
        case DCC_CLK_SRC1_DCC7_DPLLCORE_H23:
            *dpllId = PMHAL_PRCM_DPLL_CORE;
            postDiv = PMHAL_PRCM_DPLL_POST_DIV_H23;
            multilpier =DPLL_CORE_M_VAL;
            divider = DPLL_CORE_N_VAL;
            postDivider = DPLL_CORE_POST_DIV_H23;
            break;
        default:
            flag = 0U;
        break;
    }
    if(1U == flag)
    {
        PMHALCMDpllMultiplierSet(*dpllId,
                                 multilpier);
        PMHALCMDpllDividerSet(*dpllId,
                              divider);
        dpllPostDivider->postDivId   = postDiv;
        dpllPostDivider->configValue = postDivider;
        if (PM_SUCCESS == PMHALCMDpllSetPostDiv(*dpllId,
                                            dpllPostDivider, 1))
        {
            status = STW_SOK;
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}
