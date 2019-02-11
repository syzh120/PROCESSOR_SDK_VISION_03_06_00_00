/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     pcie_app.c
 *
 *  \brief    Source file containing the PCIe IP related configuration
 *            functions. These functions will be called by example
 *            applications.
 *
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include<ti/csl/csl_pcie.h>

/* Application header files */
#include "pcie_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* None */

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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#if    defined (__TI_ARM_V7M4__)
#if    defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
void AppUtilsConfigIPU1DefaultAMMU(void)
{
    ammuPageConfig_t      pageConfig       = {0U};
    ammuPolicyRegParams_t pagePolicyParams = {0U};
    uint32_t policyReg;

    /*******************************************
     * LARGE PAGE MAPPINGS                     *
     *******************************************/
    /* 0th large page mapping: P.A. 0x40000000U V.A 0x40000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize   = AMMU_PAGE_SIZE_512MB;
    policyReg                   = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 0U;
    pageConfig.policyRegVal    = policyReg; /* 0x00000007 */
    pageConfig.physicalAddress = 0x40000000U;
    pageConfig.logicalAddress  = 0x40000000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st large page mapping: P.A. 0x80000000U V.A 0x80000000U */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_512MB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    pagePolicyParams.l1WritePolicy   = AMMU_L1_WRITE_POLICY_WRITEBACK;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum           = 1U;
    pageConfig.policyRegVal          = policyReg; /* 0x000B0007; */
    pageConfig.physicalAddress       = 0x80000000U;
    pageConfig.logicalAddress        = 0x80000000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd large page mapping: P.A. 0xA0000000U V.A 0xA0000000U */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_512MB;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum           = 2U;
    pageConfig.policyRegVal          = policyReg;
    pageConfig.physicalAddress       = 0xA0000000U;
    pageConfig.logicalAddress        = 0xA0000000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd large page mapping: P.A. 0x40000000U V.A 0x60000000U */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_512MB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum           = 3U;
    pageConfig.policyRegVal          = policyReg; /* 0x00000007; */
    pageConfig.physicalAddress       = 0x40000000U;
    pageConfig.logicalAddress        = 0x60000000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /*******************************************
     * MEDIUM PAGE MAPPINGS                     *
     *******************************************/
    /* 0th medium page mapping: P.A. 0x40300000 V.A. 0x00300000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_256KB;
    pagePolicyParams.l1PostedWrite   = AMMU_L1_POSTED_WRITE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.policyRegVal          = policyReg; /* 0x0001000B; */
    pageConfig.ammuPageNum           = 0;
    pageConfig.logicalAddress        = 0x00300000;
    pageConfig.physicalAddress       = 0x40300000;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st medium page mapping: P.A. 0x40400000 V.A. 0x00400000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_256KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.policyRegVal          = policyReg; /* 0x0001000B; */
    pageConfig.ammuPageNum           = 1;
    pageConfig.logicalAddress        = 0x00400000;
    pageConfig.physicalAddress       = 0x40400000;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);


    /*******************************************
     * SMALL PAGE MAPPINGS                     *
     *******************************************/
    /* 0th small page mapping: P.A. 0x55020000U V.A. 0x00000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.volatileEnable  = AMMU_VOLATILE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x0001000B; */
    pageConfig.ammuPageNum           = 0;
    pageConfig.logicalAddress        = 0x00000000U;
    pageConfig.physicalAddress       = 0x55020000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st small page mapping: P.A. 0x55080000U V.A. 0x40000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.volatileEnable  = AMMU_VOLATILE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x0000000B; */
    pageConfig.ammuPageNum           = 1;
    pageConfig.logicalAddress        = 0x40000000U;
    pageConfig.physicalAddress       = 0x55080000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd small page mapping: P.A. 0x55024000 V.A. 0x00004000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.l1CacheEnable   = AMMU_L1_CACHE_ENABLED;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x0001000B; */
    pageConfig.ammuPageNum           = 2;
    pageConfig.logicalAddress        = 0x00004000U;
    pageConfig.physicalAddress       = 0x55024000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd small page mapping: P.A. 0x55028000 V.A. 0x00008000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 3;
    pageConfig.logicalAddress        = 0x00008000U;
    pageConfig.physicalAddress       = 0x55028000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);


    /* 4th small page mapping: P.A. 0x55020000 V.A. 0x20000000 */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 4;
    pageConfig.logicalAddress        = 0x20000000U;
    pageConfig.physicalAddress       = 0x55020000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 5th small page mapping: P.A. 0x24000000U V.A. 0x24000000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 5;
    pageConfig.logicalAddress        = 0x24000000U;
    pageConfig.physicalAddress       = 0x24000000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

    /* 6th small page mapping: P.A. 0x29FFC000U V.A. 0x29FFC000U */
    /* Set Policy Params for the page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable      = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize        = AMMU_PAGE_SIZE_16KB;
    policyReg                        = AMMUMakePolicyReg(&pagePolicyParams);

    pageConfig.ammuPageType          = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal          = policyReg; /* 0x00000003; */
    pageConfig.ammuPageNum           = 6;
    pageConfig.logicalAddress        = 0x25FFC000U;
    pageConfig.physicalAddress       = 0x25FFC000U;
    AMMUConfigPage(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, &pageConfig);

}
#else
void AppUtilsConfigIPU1DefaultAMMU(void)
{
   /* Implement AMMU for tda devices here */
   return;
}
#endif
#endif /* __TI_ARM_V7M4__ */



void PlatformPCIESS1ClockEnable(void)
{
    uint32_t regVal;

    /*OCP2SCP1 enables accessing the PCIe PHY serial configuration*/
    HW_WR_FIELD32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_OCP2SCP1_CLKCTRL,
                    CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE,
                    CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_AUTO);

    /*OCP2SCP3 enables accessing the PCIe PHY serial configuration*/
    HW_WR_FIELD32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_OCP2SCP3_CLKCTRL,
                    CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE,
                    CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_AUTO);

    /*PCIeSS CLKSTCTRL SW WakeUp*/
    HW_WR_FIELD32(SOC_L3INIT_CM_CORE_BASE + CM_PCIE_CLKSTCTRL,
                    CM_PCIE_CLKSTCTRL_CLKTRCTRL,
                    CM_PCIE_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    /*L3 Init PCIeSS1 CLKCTRL SW Enable*/
    HW_WR_FIELD32(SOC_L3INIT_CM_CORE_BASE + CM_PCIE_PCIESS1_CLKCTRL,
                    CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE,
                    CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_ENABLED);

    while ((HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_PCIE_PCIESS1_CLKCTRL) &
            CM_PCIE_PCIESS1_CLKCTRL_IDLEST_MASK) !=
            CM_PCIE_PCIESS1_CLKCTRL_IDLEST_FUNC)
    {
        ;
    }

    /*Enable PCIe PHY optional clk*/
    regVal = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_PCIE_PCIESS1_CLKCTRL);

    HW_SET_FIELD32(regVal, CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV,
                    CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_FCLK_EN);

    HW_SET_FIELD32(regVal, CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK,
                    CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_FCLK_EN);

    HW_SET_FIELD32(regVal, CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ,
                    CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ_FCLK_EN);

    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_PCIE_PCIESS1_CLKCTRL, regVal);
}

void PlatformPCIESS1PllConfig(void)
{
    uint32_t regVal;

    /*OCP2SCP_SYSCONFIG[1] Soft Reset*/
    regVal = HW_RD_REG32(SOC_OCP2SCP3_BASE + 0x10U) & 0xFFFFFFFDU;

    regVal |= 0x02U;

    HW_WR_REG32(SOC_OCP2SCP3_BASE + 0x10U, regVal);

    /*OCP2SCP_SYSSTATUS[0] Reset Done*/
    while ((HW_RD_REG32(SOC_OCP2SCP3_BASE + 0x14U) & 0x01U) != 0x01U)
    {
        ;
    }

    /*OCP2SCP_TIMING[9:7] Division Ratio = 1*/
    regVal = HW_RD_REG32(SOC_OCP2SCP3_BASE + 0x18U) & 0xFFFFFC7FU;

    regVal |= (uint32_t) 0x8U << 4U;

    HW_WR_REG32(SOC_OCP2SCP3_BASE + 0x18U, regVal);

    /*OCP2SCP_TIMING[3:0] (SYNC2) = 0xF*/
    regVal = HW_RD_REG32(SOC_OCP2SCP3_BASE + 0x18U) & 0xFFFFFFF0U;

    regVal |= 0xFU;

    HW_WR_REG32(SOC_OCP2SCP3_BASE + 0x18U, regVal);

    /*PCIe DPLL - M&N programming; CLKSEL*/
    regVal = HW_RD_REG32(SOC_CKGEN_CM_CORE_BASE + CM_CLKSEL_DPLL_PCIE_REF);

    HW_SET_FIELD32(regVal, CM_CLKSEL_DPLL_PCIE_REF_DPLL_DIV, 0x09U);

    HW_SET_FIELD32(regVal, CM_CLKSEL_DPLL_PCIE_REF_DPLL_MULT, 0x2EEU);

    HW_WR_REG32(SOC_CKGEN_CM_CORE_BASE + CM_CLKSEL_DPLL_PCIE_REF, regVal);

    /*SigmaDelta SD DIV programming */
    HW_WR_FIELD32(SOC_CKGEN_CM_CORE_BASE + CM_CLKSEL_DPLL_PCIE_REF,
                    CM_CLKSEL_DPLL_PCIE_REF_DPLL_SD_DIV, 0x06U);

    /*PCIe DPLL - M2 programming*/
    HW_WR_FIELD32(SOC_CKGEN_CM_CORE_BASE + CM_DIV_M2_DPLL_PCIE_REF,
                    CM_DIV_M2_DPLL_PCIE_REF_DIVHS, 0x0FU);

    /*DPLL Enable*/
    HW_WR_FIELD32(SOC_CKGEN_CM_CORE_BASE + CM_CLKMODE_DPLL_PCIE_REF,
                    CM_CLKMODE_DPLL_PCIE_REF_DPLL_EN,
                    CM_CLKMODE_DPLL_PCIE_REF_DPLL_EN_DPLL_LOCK_MODE);

    /* Check for DPLL lock status */
    while (((HW_RD_REG32(SOC_CKGEN_CM_CORE_BASE + CM_IDLEST_DPLL_PCIE_REF) &
            CM_IDLEST_DPLL_PCIE_REF_ST_DPLL_CLK_MASK) >>
            CM_IDLEST_DPLL_PCIE_REF_ST_DPLL_CLK_SHIFT) !=
            CM_IDLEST_DPLL_PCIE_REF_ST_DPLL_CLK_DPLL_LOCKED)
    {
        ;
    }

    /*PCIe Tx and Rx Control of ACSPCIe*/
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SMA_SW_6,
                    CTRL_CORE_SMA_SW_6_PCIE_TX_RX_CONTROL, 0x02U);

    /*Locking APLL to 2.5GHz with 100MHz input*/
    regVal = HW_RD_REG32(SOC_CKGEN_CM_CORE_BASE + CM_CLKMODE_APLL_PCIE);

    HW_SET_FIELD32(regVal, CM_CLKMODE_APLL_PCIE_CLKDIV_BYPASS,
                    CM_CLKMODE_APLL_PCIE_CLKDIV_BYPASS_PCIEDIVBY2_BYPASS_1);

    HW_SET_FIELD32(regVal, CM_CLKMODE_APLL_PCIE_REFSEL,
                    CM_CLKMODE_APLL_PCIE_REFSEL_CLKREF_ADPLL);

    HW_WR_REG32(SOC_CKGEN_CM_CORE_BASE + CM_CLKMODE_APLL_PCIE, regVal);

    HW_WR_FIELD32(SOC_CKGEN_CM_CORE_BASE + CM_CLKMODE_APLL_PCIE,
                    CM_CLKMODE_APLL_PCIE_MODE_SELECT,
                    CM_CLKMODE_APLL_PCIE_MODE_SELECT_APLL_FORCE_LOCK_MODE);

    /*Wait for APLL lock*/
    while (((HW_RD_REG32(SOC_CKGEN_CM_CORE_BASE + CM_IDLEST_APLL_PCIE) &
            CM_IDLEST_APLL_PCIE_ST_APLL_CLK_MASK) >>
            CM_IDLEST_APLL_PCIE_ST_APLL_CLK_SHIFT) !=
            CM_IDLEST_APLL_PCIE_ST_APLL_CLK_APLL_LOCKED)
    {
        ;
    }
}

void PlatformPCIESS1CtrlConfig(void)
{
    uint32_t regVal;

    /*CONTROL MODULE PWR CTL REG status of PCIeSS1*/
    regVal = HW_RD_REG32(
        SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_PHY_POWER_PCIESS1);

    HW_SET_FIELD32(regVal, CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CMD,
                    0x03U);

    HW_SET_FIELD32(regVal, CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CLKFREQ,
                    0x1AU);

    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_PHY_POWER_PCIESS1,
                regVal);

    /*Set PCIeSS1 delay count*/
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_PCIE_PCS,
                    CTRL_CORE_PCIE_PCS_PCIESS1_PCS_RC_DELAY_COUNT, 0xF1U);
    /*Set PCIeSS2 delay count*/
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_PCIE_PCS,
                    CTRL_CORE_PCIE_PCS_PCIESS2_PCS_RC_DELAY_COUNT, 0xF1U);
}

void PlatformPCIESS1Reset(void)
{
    /*Reset PCIeSS1*/
    HW_WR_FIELD32(SOC_L3INIT_PRM_BASE + RM_PCIESS_RSTCTRL,
                    RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1,
                  RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_CLEAR);

    /* Wait till PCIeSS1 is out of reset */
    while (((HW_RD_REG32(SOC_L3INIT_PRM_BASE + RM_PCIESS_RSTST) &
            RM_PCIESS_RSTST_RST_LOCAL_PCIE1_MASK) >>
            RM_PCIESS_RSTST_RST_LOCAL_PCIE1_SHIFT) !=
            RM_PCIESS_RSTST_RST_LOCAL_PCIE1_RESET_YES)
    {
        ;
    }
}

void PlatformPCIESS1PhyConfig(void)
{
    uint32_t regVal;

    /*Program for Analog circuits in the IP.*/
    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU);
    regVal &= 0x07FFFFFFU;
    regVal |= ((uint32_t) 0x10U << 24U);
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU, regVal);

    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU);
    regVal &= 0xFFFC3FFFU;
    regVal |= ((uint32_t) 0x10U << 12U);
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU, regVal);

    /*Program for digital section of the IP.*/
    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x28U);
    regVal &= 0xE30007FFU;
    regVal |= 0x001B3000U;
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x28U, regVal);

    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU);
    regVal &= 0xFFFFFF9FU;
    regVal |= ((uint32_t) 0x0U << 4U);
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x0CU, regVal);

    /*Determines which of the 4 EFUSE registers. Selects dll_rate2_coarsetrim*/
    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x1CU);
    regVal &= 0x3FFFFFFFU;
    regVal |= ((uint32_t) 0x8U << 28U);
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x1CU, regVal);

    /*
    * Programs the DLL and the Phase Interpolator analog RW 0x3
    * circuits to work with different clock frequencies
    */
    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x24U);
    regVal &= 0x3FFFFFFFU;
    regVal |= ((uint32_t) 0xCU << 28U);
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x24U, regVal);

    /*Program IP Equalizer*/
    regVal  = HW_RD_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x38U);
    regVal &= 0x0U;
    regVal |= 0x0000F80FU;
    HW_WR_REG32(SOC_OCP2SCP3_USB3RX_PHY_PCIE1_BASE + 0x38U, regVal);
}

void PCIEAppPrcmConfig(void)
{
    PlatformPCIESS1ClockEnable();

    PlatformPCIESS1PllConfig();

    PlatformPCIESS1CtrlConfig();

    PlatformPCIESS1Reset();

    PlatformPCIESS1PhyConfig();
}
