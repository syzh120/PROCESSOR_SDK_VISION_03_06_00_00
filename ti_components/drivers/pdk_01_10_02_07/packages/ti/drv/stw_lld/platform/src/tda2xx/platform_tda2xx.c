/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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
 */

/*
 * \file platform_tda2xx.c
 *
 * \brief  Contains board specific configurations
 *
 */

#include <stdint.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <platformPriv.h>

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/

#define GPMC_CS0_REG_MUX_VAL (0x00070000)
#define GPMC_OEN_MUX_VAL    (0x00060000)
#define GPMC_WEN_MUX_VAL    (0x00060000)
#define GPMC_D0_MUX_VAL     (0x00040000)
#define GPMC_D1_MUX_VAL     (0x00040000)
#define GPMC_D2_MUX_VAL     (0x00040000)
#define GPMC_D3_MUX_VAL     (0x00040000)
#define GPMC_D4_MUX_VAL     (0x00040000)
#define GPMC_D5_MUX_VAL     (0x00040000)
#define GPMC_D6_MUX_VAL     (0x00040000)
#define GPMC_D7_MUX_VAL     (0x00040000)
#define GPMC_D8_MUX_VAL     (0x00040000)
#define GPMC_D9_MUX_VAL     (0x00040000)
#define GPMC_D10_MUX_VAL    (0x00040000)
#define GPMC_D11_MUX_VAL    (0x00040000)
#define GPMC_D12_MUX_VAL    (0x00040000)
#define GPMC_D13_MUX_VAL    (0x00040000)
#define GPMC_D14_MUX_VAL    (0x00040000)
#define GPMC_D15_MUX_VAL    (0x00040000)
#define GPMC_A1_MUX_VAL     (0x00050000)
#define GPMC_A2_MUX_VAL     (0x00050000)
#define GPMC_A3_MUX_VAL     (0x00050000)
#define GPMC_A4_MUX_VAL     (0x00050000)
#define GPMC_A5_MUX_VAL     (0x00050000)
#define GPMC_A6_MUX_VAL     (0x00050000)
#define GPMC_A7_MUX_VAL     (0x00050000)
#define GPMC_A8_MUX_VAL     (0x00050000)
#define GPMC_A9_MUX_VAL     (0x00050000)
#define GPMC_A10_MUX_VAL    (0x00050000)
#define GPMC_A11_MUX_VAL    (0x00050000)
#define GPMC_A12_MUX_VAL    (0x00050000)
#define GPMC_A13_MUX_VAL    (0x00050000)
#define GPMC_A14_MUX_VAL    (0x00050000)
#define GPMC_A15_MUX_VAL    (0x00050000)
#define GPMC_A16_MUX_VAL    (0x00050000)
#define GPMC_A17_MUX_VAL    (0x00050000)
#define GPMC_A18_MUX_VAL    (0x00050000)
#define GPMC_A19_MUX_VAL    (0x00050000)
#define GPMC_A20_MUX_VAL    (0x00050000)
#define GPMC_A21_MUX_VAL    (0x00050000)
/* GPMC function 1 - NOR get info fails with value 1 */
#define GPMC_A22_MUX_VAL    (0x00050000)
#define GPMC_A23_MUX_VAL    (0x00050000)
#define GPMC_A24_MUX_VAL    (0x00050000)
#define GPMC_A25_MUX_VAL    (0x00050000)
#define GPMC_A26_MUX_VAL    (0x00050000)
#define GPMC_A27_MUX_VAL    (0x00050000)

#if 0
#define SPNOR_GPMC_CONFIG1  0x41041000U
#define SPNOR_GPMC_CONFIG2  0x00001C00U
#define SPNOR_GPMC_CONFIG3  0x00000000U
#define SPNOR_GPMC_CONFIG4  0x00001C03U
#define SPNOR_GPMC_CONFIG5  0x041B001FU
#define SPNOR_GPMC_CONFIG6  0x00000000U
#define SPNOR_GPMC_CONFIG7  0x00000C68U
#else
#define SPNOR_GPMC_CONFIG1  0x00001010U
#define SPNOR_GPMC_CONFIG2  0x001E1E01U
#define SPNOR_GPMC_CONFIG3  0x00090907U
#define SPNOR_GPMC_CONFIG4  0x0F071D0BU
#define SPNOR_GPMC_CONFIG5  0x001C1F1FU
#define SPNOR_GPMC_CONFIG6  0x8F070080U
#define SPNOR_GPMC_CONFIG7  0x00000F48U

#endif
#define GPIO_CLKCTRL_VAL \
    0x102

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      EXTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
#ifdef REGRESSION_MODE
sbl_regression_log_bfr_t sbl_regression_log_bfr  __attribute__ ((section(
                                                                     ".sbl_reg_log_bfr")));
#endif

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/**
 * \brief       This API provides the Silicon Rev Value.
 *
 * \param       None.
 *
 * \return      Silicon Revision.
 *
 * \note        For TDA2xx
 *              0: Silicon Rev 1.0
 *              1: Silicon Rev 1.1
 *              2: Silicon Rev 2.0
 *              For TDA2Ex
 *              0: Silicon Rev 1.0
 *              1: Silicon Rev 2.0
 **/
uint32_t PlatformGetSiliconRev(void)
{
    uint32_t siliconRev;

    siliconRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE + CTRL_WKUP_ID_CODE);

    siliconRev = (siliconRev & 0xF0000000U) >> 28U;

    return (siliconRev);
}

void PlatformMCSPI1PrcmEnable(void)
{
    HW_WR_REG32(0x4a0097f0, 0x02);
    while (HW_RD_REG32(0x4a0097f0) != 0x02U)
    {
        ;
    }
}

void PlatformMCSPI2PrcmEnable(void)
{
    HW_WR_REG32(0x4a0097f8, 0x02);
    while (HW_RD_REG32(0x4a0097f8) != 0x02U)
    {
        ;
    }
}

void PlatformDCAN1PrcmEnable(void)
{
    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                          CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
           CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformDCAN2PrcmEnable(void)
{
    /*CM_L4PER2_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                          CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
           CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformI2C5PrcmEnable(void)
{
    /*CM_IPU_I2C5_CLKCTRL*/
    HW_WR_FIELD32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_I2C5_CLKCTRL,
                  CM_IPU_I2C5_CLKCTRL_MODULEMODE,
                  CM_IPU_I2C5_CLKCTRL_MODULEMODE_ENABLE);
    while ((HW_RD_FIELD32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_I2C5_CLKCTRL,
                          CM_IPU_I2C5_CLKCTRL_IDLEST)) ==
           CM_IPU_I2C5_CLKCTRL_IDLEST_DISABLE)
    {
        /* Do nothing - Busy wait */
    }
}

void PlatformGPMCPinCtrl(void)
{
    /* Unlock All MMR registers */
    PlatformUnlockMMR();

    /* Do the pin muxing */
    HW_WR_REG32(GPMC_D0, GPMC_D0_MUX_VAL);
    HW_WR_REG32(GPMC_D1, GPMC_D1_MUX_VAL);
    HW_WR_REG32(GPMC_D2, GPMC_D2_MUX_VAL);
    HW_WR_REG32(GPMC_D3, GPMC_D3_MUX_VAL);
    HW_WR_REG32(GPMC_D4, GPMC_D4_MUX_VAL);
    HW_WR_REG32(GPMC_D5, GPMC_D5_MUX_VAL);
    HW_WR_REG32(GPMC_D6, GPMC_D6_MUX_VAL);
    HW_WR_REG32(GPMC_D7, GPMC_D7_MUX_VAL);
    HW_WR_REG32(GPMC_D8, GPMC_D8_MUX_VAL);
    HW_WR_REG32(GPMC_D9, GPMC_D9_MUX_VAL);
    HW_WR_REG32(GPMC_D10, GPMC_D10_MUX_VAL);
    HW_WR_REG32(GPMC_D11, GPMC_D11_MUX_VAL);
    HW_WR_REG32(GPMC_D12, GPMC_D12_MUX_VAL);
    HW_WR_REG32(GPMC_D13, GPMC_D13_MUX_VAL);
    HW_WR_REG32(GPMC_D14, GPMC_D14_MUX_VAL);
    HW_WR_REG32(GPMC_D15, GPMC_D15_MUX_VAL);
    HW_WR_REG32(GPMC_CS0_REG, GPMC_CS0_REG_MUX_VAL);
    HW_WR_REG32(GPMC_OEN, GPMC_OEN_MUX_VAL);
    HW_WR_REG32(GPMC_WEN, GPMC_WEN_MUX_VAL);
    HW_WR_REG32(GPMC_A1, GPMC_A1_MUX_VAL);
    HW_WR_REG32(GPMC_A2, GPMC_A2_MUX_VAL);
    HW_WR_REG32(GPMC_A3, GPMC_A3_MUX_VAL);
    HW_WR_REG32(GPMC_A4, GPMC_A4_MUX_VAL);
    HW_WR_REG32(GPMC_A5, GPMC_A5_MUX_VAL);
    HW_WR_REG32(GPMC_A6, GPMC_A6_MUX_VAL);
    HW_WR_REG32(GPMC_A7, GPMC_A7_MUX_VAL);
    HW_WR_REG32(GPMC_A8, GPMC_A8_MUX_VAL);
    HW_WR_REG32(GPMC_A9, GPMC_A9_MUX_VAL);
    HW_WR_REG32(GPMC_A10, GPMC_A10_MUX_VAL);
    HW_WR_REG32(GPMC_A11, GPMC_A11_MUX_VAL);
    HW_WR_REG32(GPMC_A12, GPMC_A12_MUX_VAL);
    HW_WR_REG32(GPMC_A13, GPMC_A13_MUX_VAL);
    HW_WR_REG32(GPMC_A14, GPMC_A14_MUX_VAL);
    HW_WR_REG32(GPMC_A15, GPMC_A15_MUX_VAL);
    HW_WR_REG32(GPMC_A16, GPMC_A16_MUX_VAL);
    HW_WR_REG32(GPMC_A17, GPMC_A17_MUX_VAL);
    HW_WR_REG32(GPMC_A18, GPMC_A18_MUX_VAL);
    HW_WR_REG32(GPMC_A19, GPMC_A19_MUX_VAL);
    HW_WR_REG32(GPMC_A20, GPMC_A20_MUX_VAL);
    HW_WR_REG32(GPMC_A21, GPMC_A21_MUX_VAL);
    HW_WR_REG32(GPMC_A22, GPMC_A22_MUX_VAL);
    HW_WR_REG32(GPMC_A23, GPMC_A23_MUX_VAL);
    HW_WR_REG32(GPMC_A24, GPMC_A24_MUX_VAL);
    HW_WR_REG32(GPMC_A25, GPMC_A25_MUX_VAL);
    HW_WR_REG32(GPMC_A26, GPMC_A25_MUX_VAL);
    HW_WR_REG32(GPMC_A27, GPMC_A25_MUX_VAL);

    /* Enable FPMC CS0 */
    HW_WR_REG32(gpmc_cfg7_addr, (SPNOR_GPMC_CONFIG7 | 0x40U));
    wait((int32_t) 900);
}

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
             CM_IDLEST_DPLL_PCIE_REF_ST_DPLL_CLK_MASK) <<
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
             CM_IDLEST_APLL_PCIE_ST_APLL_CLK_MASK) <<
            CM_IDLEST_APLL_PCIE_ST_APLL_CLK_SHIFT) !=
           CM_IDLEST_APLL_PCIE_ST_APLL_CLK_APLL_LOCKED)
    {
        ;
    }
}

void PlatformPCIESS1Reset(void)
{
    /*Reset PCIeSS1*/
    HW_WR_FIELD32(SOC_L3INIT_PRM_BASE + RM_PCIESS_RSTCTRL,
                  RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1,
                  RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_CLEAR);

    /* Wait till PCIeSS1 is out of reset */
    while (((HW_RD_REG32(SOC_L3INIT_PRM_BASE + RM_PCIESS_RSTST) &
             RM_PCIESS_RSTST_RST_LOCAL_PCIE1_MASK) <<
            RM_PCIESS_RSTST_RST_LOCAL_PCIE1_SHIFT) !=
           RM_PCIESS_RSTST_RST_LOCAL_PCIE1_RESET_YES)
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

void PlatformMCASP3PrcmEnable(void)
{
    HW_WR_REG32(0x4a009868, 0x02);
    while ((HW_RD_REG32(0x4a009868)) != 0x02U)
    {
        ;
    }
}

uint32_t PlatformGetQspiMode(void)
{
    uint32_t mode;

#if defined (SOC_TDA2EX)
    mode = 0U;
#else
    uint32_t siliconRev = PlatformGetSiliconRev();
    if (0U == siliconRev)
    {
        /* On ES 1.0 TDA2xx silicon only mode 3 works */
        mode = 3U;
    }
    else
    {
        /* On ES 1.1 TDA2xx silicon both mode 0 & 3 work */
        /* Reutrning 0 as it can work at higher frequency */
        mode = 0U;
    }
#endif
    return mode;
}

void PlatformDcanMessageRamInit(uint32_t instance)
{
    uint32_t status = 0U;

    switch (instance)
    {
        case 0U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_CLEAR);
            break;

        case 1U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_CLEAR);
            break;

        default:
            break;
    }
}

uint32_t PlatformGetSiliconPackageType(void)
{
    uint32_t packageType, regVal;

    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                           CTRL_WKUP_STD_FUSE_DIE_ID_2,
                           CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE);

    if (0x1U == regVal)
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_17X17;
    }
    else if (0x2U == regVal)
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_23X23;
    }
    else
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_UNKNOWN;
    }
    return packageType;
}

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */

void MCSPI1_prcm_enable(void)
{
    PlatformMCSPI1PrcmEnable();
}

void MCSPI2_prcm_enable(void)
{
    PlatformMCSPI2PrcmEnable();
}

void GPMC_pin_Ctrl(void)
{
    PlatformGPMCPinCtrl();
}

void PlatformGPMCConfig(void)
{
    /* Disable GPMC CS0 */
    HW_WR_REG32(gpmc_cfg7_addr, 0);
    wait((int32_t) 900);

    /* Load GPMC Config Values */
    HW_WR_REG32(gpmc_cfg1_addr, SPNOR_GPMC_CONFIG1);
    HW_WR_REG32(gpmc_cfg2_addr, SPNOR_GPMC_CONFIG2);
    HW_WR_REG32(gpmc_cfg3_addr, SPNOR_GPMC_CONFIG3);
    HW_WR_REG32(gpmc_cfg4_addr, SPNOR_GPMC_CONFIG4);
    HW_WR_REG32(gpmc_cfg5_addr, SPNOR_GPMC_CONFIG5);
    HW_WR_REG32(gpmc_cfg6_addr, SPNOR_GPMC_CONFIG6);
    HW_WR_REG32(gpmc_cfg7_addr, SPNOR_GPMC_CONFIG7);
}

void GPMC_config(void)
{
    PlatformGPMCConfig();
}

void PCIESS1ClockEnable(void)
{
    PlatformPCIESS1ClockEnable();
}

void PCIESS1PllConfig(void)
{
    PlatformPCIESS1PllConfig();
}

void PCIESS1Reset(void)
{
    PlatformPCIESS1Reset();
}

void PCIESS1CtrlConfig(void)
{
    PlatformPCIESS1CtrlConfig();
}

void PCIESS1PhyConfig(void)
{
    PlatformPCIESS1PhyConfig();
}

void MCASP3_prcm_enable(void)
{
    PlatformMCASP3PrcmEnable();
}

