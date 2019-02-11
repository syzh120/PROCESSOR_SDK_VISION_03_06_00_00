/*
 *  Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_ctrl_core_pad.h
 *
 *  \brief  register-level header file for CTRL_CORE_PAD
 *
**/

#ifndef HW_CTRL_CORE_PAD_H_
#define HW_CTRL_CORE_PAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CTRL_CORE_CONTROL_PBIAS                                                                            (0x60U)
#define CTRL_CORE_CONTROL_I2C_0                                                                            (0x64U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY                                                                      (0x6cU)
#define CTRL_CORE_CONTROL_DSIPHY                                                                           (0x74U)
#define CTRL_CORE_CONTROL_USB2PHYCORE                                                                      (0x7cU)
#define CTRL_CORE_CONTROL_HDMI_1                                                                           (0x80U)
#define CTRL_CORE_CONTROL_DDRCACH1_0                                                                       (0x90U)
#define CTRL_CORE_CONTROL_DDRCACH2_0                                                                       (0x94U)
#define CTRL_CORE_CONTROL_DDRCH1_0                                                                         (0x98U)
#define CTRL_CORE_CONTROL_DDRCH1_1                                                                         (0x9cU)
#define CTRL_CORE_CONTROL_DDRCH2_0                                                                         (0xa0U)
#define CTRL_CORE_CONTROL_DDRCH2_1                                                                         (0xa4U)
#define CTRL_CORE_CONTROL_DDRCH1_2                                                                         (0xa8U)
#define CTRL_CORE_CONTROL_DDRCH2_2                                                                         (0xacU)
#define CTRL_CORE_CONTROL_DDRIO_0                                                                          (0xb0U)
#define CTRL_CORE_CONTROL_DDRIO_1                                                                          (0xb4U)
#define CTRL_CORE_CONTROL_HYST_1                                                                           (0xbcU)
#define CTRL_CORE_CONTROL_SPARE_RW                                                                         (0xc8U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE                                                                        (0xd4U)
#define CTRL_CORE_SRCOMP_SOUTH_SIDE                                                                        (0xd8U)
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_TDA2PX)
#define CTRL_CORE_VIP_MUX_SELECT                                                                           (0xECU)
#define CTRL_CORE_ALT_SELECT_MUX                                                                           (0xF0U)
#define CTRL_CORE_CAMERRX_CONTROL                                                                          (0x6DCU)
#endif

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_SHIFT                                                  (27U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK                                                   (0x08000000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_DISABLE                                                (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_ENABLE                                                 (0U)

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_SHIFT                                                    (26U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK                                                     (0x04000000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_DISABLE                                                  (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_ENABLE                                                   (0U)

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_HIZ_MODE_SHIFT                                                (25U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_HIZ_MODE_MASK                                                 (0x02000000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_HIZ_MODE_DISABLE                                              (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_HIZ_MODE_ENABLE                                               (0U)

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_SUPPLY_HI_OUT_SHIFT                                           (24U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_SUPPLY_HI_OUT_MASK                                            (0x01000000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_SUPPLY_HI_OUT_3V                                              (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_SUPPLY_HI_OUT_1V8                                             (0U)

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_ERROR_SHIFT                                             (23U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_ERROR_MASK                                              (0x00800000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_ERROR_VMODE_ERROR1                                      (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_ERROR_VMODE_ERROR0                                      (0U)

#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_SHIFT                                                   (21U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK                                                    (0x00200000U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_3V                                                      (1U)
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_1V8                                                     (0U)

#define CTRL_CORE_CONTROL_PBIAS_RESERVED_0_SHIFT                                                          (0U)
#define CTRL_CORE_CONTROL_PBIAS_RESERVED_0_MASK                                                           (0x001fffffU)

#define CTRL_CORE_CONTROL_PBIAS_RESERVED_1_SHIFT                                                          (22U)
#define CTRL_CORE_CONTROL_PBIAS_RESERVED_1_MASK                                                           (0x00400000U)

#define CTRL_CORE_CONTROL_PBIAS_RESERVED_2_SHIFT                                                          (28U)
#define CTRL_CORE_CONTROL_PBIAS_RESERVED_2_MASK                                                           (0xf0000000U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_SHIFT                                                     (31U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_MASK                                                      (0x80000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_SHIFT                                                 (30U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_MASK                                                  (0x40000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_SHIFT                                                     (29U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_MASK                                                      (0x20000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_SHIFT                                                 (28U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_MASK                                                  (0x10000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_SHIFT                                                     (27U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_MASK                                                      (0x08000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_SHIFT                                                 (26U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_MASK                                                  (0x04000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_SHIFT                                                (25U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_MASK                                                 (0x02000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_SHIFT                                            (24U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_MASK                                             (0x01000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_DISABLE                                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_ENABLE                                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_SHIFT                                                     (23U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_MASK                                                      (0x00800000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_SHIFT                                                 (22U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_MASK                                                  (0x00400000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_SHIFT                                                     (21U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_MASK                                                      (0x00200000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_SHIFT                                                 (20U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_MASK                                                  (0x00100000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_SHIFT                                                     (19U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_MASK                                                      (0x00080000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_MASK                                                  (0x00040000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_SHIFT                                                (17U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_MASK                                                 (0x00020000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_SHIFT                                            (16U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_MASK                                             (0x00010000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_DISABLE                                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_ENABLE                                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_SHIFT                                                     (15U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_MASK                                                      (0x00008000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_SHIFT                                                 (14U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_MASK                                                  (0x00004000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_SHIFT                                                     (13U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_MASK                                                      (0x00002000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_ENABLE                                                    (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_DISABLE                                                   (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_SHIFT                                                 (12U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_MASK                                                  (0x00001000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_DISABLE                                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_ENABLE                                                (0U)

#define CTRL_CORE_CONTROL_I2C_0_RESERVED_0_SHIFT                                                          (0U)
#define CTRL_CORE_CONTROL_I2C_0_RESERVED_0_MASK                                                           (0x00000fffU)

#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_TXVALID_SHIFT                                             (30U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_TXVALID_MASK                                              (0x40000000U)

#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_ENBYPASSCLK_SHIFT                                         (29U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_ENBYPASSCLK_MASK                                          (0x20000000U)

#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_PD_PULLUPDET_SHIFT                                        (28U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY_HDMITXPHY_PD_PULLUPDET_MASK                                         (0x10000000U)

#define CTRL_CORE_CONTROL_HDMI_TX_PHY_RESERVED_0_SHIFT                                                    (0U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY_RESERVED_0_MASK                                                     (0x0fffffffU)

#define CTRL_CORE_CONTROL_HDMI_TX_PHY_RESERVED_1_SHIFT                                                    (31U)
#define CTRL_CORE_CONTROL_HDMI_TX_PHY_RESERVED_1_MASK                                                     (0x80000000U)

#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTA_LANEENABLE_SHIFT                                                (24U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTA_LANEENABLE_MASK                                                 (0x1f000000U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTA_LANEENABLE_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTA_LANEENABLE_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTC_LANEENABLE_SHIFT                                                (19U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTC_LANEENABLE_MASK                                                 (0x00f80000U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTC_LANEENABLE_DISABLE                                              (1U)
#define CTRL_CORE_CONTROL_DSIPHY_DSIPORTC_LANEENABLE_ENABLE                                               (0U)

#define CTRL_CORE_CONTROL_DSIPHY_RESERVED_0_SHIFT                                                         (0U)
#define CTRL_CORE_CONTROL_DSIPHY_RESERVED_0_MASK                                                          (0x0007ffffU)

#define CTRL_CORE_CONTROL_DSIPHY_RESERVED_1_SHIFT                                                         (29U)
#define CTRL_CORE_CONTROL_DSIPHY_RESERVED_1_MASK                                                          (0xe0000000U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_AUTORESUME_EN_SHIFT                                         (31U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_AUTORESUME_EN_MASK                                          (0x80000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_AUTORESUME_EN_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_AUTORESUME_EN_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DISCHGDET_SHIFT                                             (30U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DISCHGDET_MASK                                              (0x40000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DISCHGDET_DISABLE                                           (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DISCHGDET_ENABLE                                            (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_GPIOMODE_SHIFT                                              (29U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_GPIOMODE_MASK                                               (0x20000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_GPIOMODE_ENABLE                                             (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_GPIOMODE_DISABLE                                            (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_EXT_CTL_SHIFT                                       (28U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_EXT_CTL_MASK                                        (0x10000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_EXT_CTL_DISABLE                                     (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_EXT_CTL_ENABLE                                      (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDM_PD_CHGDET_EN_SHIFT                                      (27U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDM_PD_CHGDET_EN_MASK                                       (0x08000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDM_PD_CHGDET_EN_ENABLE                                     (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDM_PD_CHGDET_EN_DISABLE                                    (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDP_PU_CHGDET_EN_SHIFT                                      (26U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDP_PU_CHGDET_EN_MASK                                       (0x04000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDP_PU_CHGDET_EN_ENABLE                                     (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RDP_PU_CHGDET_EN_DISABLE                                    (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_VSRC_EN_SHIFT                                           (25U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_VSRC_EN_MASK                                            (0x02000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_VSRC_EN_ENABLE                                          (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_VSRC_EN_DISABLE                                         (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_ISINK_EN_SHIFT                                          (24U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_ISINK_EN_MASK                                           (0x01000000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_ISINK_EN_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_ISINK_EN_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_SHIFT                                        (21U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_MASK                                         (0x00e00000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_110                                          (6U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_100                                          (4U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_001                                          (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_011                                          (3U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_000                                          (0U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_111                                          (7U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_010                                          (2U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_STATUS_101                                          (5U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DM_COMP_SHIFT                                       (20U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DM_COMP_MASK                                        (0x00100000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DM_COMP_ABOVE                                       (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DM_COMP_BELOW                                       (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DP_COMP_SHIFT                                       (19U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DP_COMP_MASK                                        (0x00080000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DP_COMP_ABOVE                                       (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHG_DET_DP_COMP_BELOW                                       (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATADET_SHIFT                                               (18U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATADET_MASK                                                (0x00040000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATADET_ABOVE                                               (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATADET_BELOW                                               (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SINKONDP_SHIFT                                              (17U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SINKONDP_MASK                                               (0x00020000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SINKONDP_ENABLE                                             (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SINKONDP_DEFAULT                                            (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SRCONDM_SHIFT                                               (16U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SRCONDM_MASK                                                (0x00010000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SRCONDM_ENABLE                                              (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_SRCONDM_DEFAULT                                             (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESTARTCHGDET_SHIFT                                         (15U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESTARTCHGDET_MASK                                          (0x00008000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESTARTCHGDET_RESTART                                       (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESTARTCHGDET_DEFAULT                                       (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETDONE_SHIFT                                            (14U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETDONE_MASK                                             (0x00004000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETDONE_COMPLETED                                        (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETDONE_NOT_COMPLETED                                    (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETECTED_SHIFT                                           (13U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETECTED_MASK                                            (0x00002000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETECTED_DETECTED                                        (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_CHGDETECTED_NOT_DETECTED                                    (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCPUEN_SHIFT                                              (12U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCPUEN_MASK                                               (0x00001000U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCPUEN_ENABLE                                             (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCPUEN_DISABLE                                            (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCMODEEN_SHIFT                                            (11U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCMODEEN_MASK                                             (0x00000800U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCMODEEN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_MCPCMODEEN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONEMCLK_SHIFT                                         (10U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONEMCLK_MASK                                          (0x00000400U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONEMCLK_OUT_OF_RESET                                  (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONEMCLK_IN_RESET                                      (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_UTMIRESETDONE_SHIFT                                         (9U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_UTMIRESETDONE_MASK                                          (0x00000200U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_UTMIRESETDONE_UTMI_FSM_OUT_OF_RESET                         (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_UTMIRESETDONE_UTMI_FSM_INRESET                              (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATAPOLARITYN_SHIFT                                         (7U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATAPOLARITYN_MASK                                          (0x00000080U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATAPOLARITYN_INVERTED                                      (1U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_DATAPOLARITYN_NORMAL                                        (0U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USBDPLL_FREQLOCK_SHIFT                                              (6U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USBDPLL_FREQLOCK_MASK                                               (0x00000040U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONETCLK_SHIFT                                         (5U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_USB2PHY_RESETDONETCLK_MASK                                          (0x00000020U)

#define CTRL_CORE_CONTROL_USB2PHYCORE_RESERVED_0_SHIFT                                                    (0U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_RESERVED_0_MASK                                                     (0x0000001fU)

#define CTRL_CORE_CONTROL_USB2PHYCORE_RESERVED_1_SHIFT                                                    (8U)
#define CTRL_CORE_CONTROL_USB2PHYCORE_RESERVED_1_MASK                                                     (0x00000100U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_GLFENB_SHIFT                                                (31U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_GLFENB_MASK                                                 (0x80000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_GLFENB_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_GLFENB_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_PULLUPRESX_SHIFT                                            (30U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_PULLUPRESX_MASK                                             (0x40000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_PULLUPRESX_DISABLE                                          (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_PULLUPRESX_ENABLE                                           (0U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_GLFENB_SHIFT                                                (29U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_GLFENB_MASK                                                 (0x20000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_GLFENB_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_GLFENB_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_PULLUPRESX_SHIFT                                            (28U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_PULLUPRESX_MASK                                             (0x10000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_PULLUPRESX_DISABLE                                          (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_PULLUPRESX_ENABLE                                           (0U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_HSMODE_SHIFT                                                (27U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_HSMODE_MASK                                                 (0x08000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_HSMODE_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SDA_HSMODE_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_HSMODE_SHIFT                                                (26U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_HSMODE_MASK                                                 (0x04000000U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_HSMODE_ENABLE                                               (1U)
#define CTRL_CORE_CONTROL_HDMI_1_HDMI_DDC_SCL_HSMODE_DISABLE                                              (0U)

#define CTRL_CORE_CONTROL_HDMI_1_RESERVED_0_SHIFT                                                         (0U)
#define CTRL_CORE_CONTROL_HDMI_1_RESERVED_0_MASK                                                          (0x03ffffffU)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_SHIFT                                                 (29U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_MASK                                                  (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P73REXT                                              (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P88REXT                                              (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P33REXT                                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_REXT                                                  (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P6REXT                                               (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P67REXT                                              (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P14REXT                                              (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P8REXT                                               (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SHIFT                                                (26U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_MASK                                                 (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SLOW                                                 (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_FASTEST                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SLOWEST                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_FAST                                                 (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_SHIFT                                                (24U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_MASK                                                 (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_PU                                                   (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_KEEPER                                               (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_NONE                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_PD                                                   (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_SHIFT                                                (21U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_MASK                                                 (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P73REXT                                             (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P88REXT                                             (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P33REXT                                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_REXT                                                 (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P6REXT                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P67REXT                                             (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P14REXT                                             (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P8REXT                                              (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SHIFT                                               (18U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_MASK                                                (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SLOW                                                (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_FASTEST                                             (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SLOWEST                                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_FAST                                                (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_SHIFT                                               (16U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_MASK                                                (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_PU                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_KEEPER                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_NONE                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_PD                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_SHIFT                                                (13U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_MASK                                                 (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P73REXT                                             (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P88REXT                                             (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P33REXT                                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_REXT                                                 (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P6REXT                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P67REXT                                             (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P14REXT                                             (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P8REXT                                              (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SHIFT                                               (10U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_MASK                                                (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SLOW                                                (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_FASTEST                                             (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SLOWEST                                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_FAST                                                (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_SHIFT                                               (8U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_MASK                                                (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_PU                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_KEEPER                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_NONE                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_PD                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_SHIFT                                                 (5U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_MASK                                                  (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P73REXT                                              (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P88REXT                                              (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P33REXT                                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_REXT                                                  (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P6REXT                                               (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P67REXT                                              (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P14REXT                                              (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P8REXT                                               (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SHIFT                                                (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_MASK                                                 (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SLOW                                                 (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_FASTEST                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SLOWEST                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_FAST                                                 (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_SHIFT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_MASK                                                 (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_PU                                                   (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_KEEPER                                               (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_NONE                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_PD                                                   (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_SHIFT                                                 (29U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_MASK                                                  (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_0P73REXT                                              (6U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_0P88REXT                                              (4U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_1P33REXT                                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_REXT                                                  (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_1P6REXT                                               (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_0P67REXT                                              (7U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_1P14REXT                                              (2U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_I_0P8REXT                                               (5U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_SHIFT                                                (26U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_MASK                                                 (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_SLOW                                                 (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_FASTEST                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_SLOWEST                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_SR_FAST                                                 (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_SHIFT                                                (24U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_MASK                                                 (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_PU                                                   (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_KEEPER                                               (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_NONE                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART0_WD_PD                                                   (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_SHIFT                                                (21U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_MASK                                                 (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_0P73REXT                                             (6U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_0P88REXT                                             (4U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_1P33REXT                                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_REXT                                                 (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_1P6REXT                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_0P67REXT                                             (7U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_1P14REXT                                             (2U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_I_0P8REXT                                              (5U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_SHIFT                                               (18U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_MASK                                                (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_SLOW                                                (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_FASTEST                                             (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_SLOWEST                                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_SR_FAST                                                (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_SHIFT                                               (16U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_MASK                                                (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_PU                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_KEEPER                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_NONE                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5A_WD_PD                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_SHIFT                                                (13U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_MASK                                                 (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_0P73REXT                                             (6U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_0P88REXT                                             (4U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_1P33REXT                                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_REXT                                                 (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_1P6REXT                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_0P67REXT                                             (7U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_1P14REXT                                             (2U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_I_0P8REXT                                              (5U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_SHIFT                                               (10U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_MASK                                                (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_SLOW                                                (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_FASTEST                                             (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_SLOWEST                                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_SR_FAST                                                (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_SHIFT                                               (8U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_MASK                                                (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_PU                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_KEEPER                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_NONE                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART5B_WD_PD                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_SHIFT                                                 (5U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_MASK                                                  (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_0P73REXT                                              (6U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_0P88REXT                                              (4U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_1P33REXT                                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_REXT                                                  (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_1P6REXT                                               (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_0P67REXT                                              (7U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_1P14REXT                                              (2U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_I_0P8REXT                                               (5U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_SHIFT                                                (2U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_MASK                                                 (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_SLOW                                                 (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_FASTEST                                              (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_SLOWEST                                              (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_SR_FAST                                                 (2U)

#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_SHIFT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_MASK                                                 (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_PU                                                   (1U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_KEEPER                                               (3U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_NONE                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCACH2_0_DDRCH2_PART6_WD_PD                                                   (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_SHIFT                                                  (29U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_MASK                                                   (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_SHIFT                                                 (26U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_MASK                                                  (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_SHIFT                                                 (24U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_MASK                                                  (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART1B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_SHIFT                                                  (5U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_MASK                                                   (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_SHIFT                                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_MASK                                                  (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_MASK                                                  (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_DDRCH1_PART2B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_SHIFT                                                  (29U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_MASK                                                   (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_SHIFT                                                 (26U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_MASK                                                  (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_SHIFT                                                 (24U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_MASK                                                  (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART3B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_SHIFT                                                  (5U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_MASK                                                   (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_SHIFT                                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_MASK                                                  (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_MASK                                                  (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_DDRCH1_PART4B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_SHIFT                                                  (29U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_MASK                                                   (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_SHIFT                                                 (26U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_MASK                                                  (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_SHIFT                                                 (24U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_MASK                                                  (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART1B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_SHIFT                                                  (5U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_MASK                                                   (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_SHIFT                                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_MASK                                                  (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_MASK                                                  (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_0_DDRCH2_PART2B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_SHIFT                                                  (29U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_MASK                                                   (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_SHIFT                                                 (26U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_MASK                                                  (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_SHIFT                                                 (24U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_MASK                                                  (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART3B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_SHIFT                                                  (5U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_MASK                                                   (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_SHIFT                                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_MASK                                                  (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_MASK                                                  (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_1_DDRCH2_PART4B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_DDRCH1_PART7B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_RESERVED_0_SHIFT                                                       (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_RESERVED_0_MASK                                                        (0x000000ffU)

#define CTRL_CORE_CONTROL_DDRCH1_2_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_CONTROL_DDRCH1_2_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_SHIFT                                                  (21U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_MASK                                                   (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_SHIFT                                                 (18U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_MASK                                                  (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_SHIFT                                                 (16U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_MASK                                                  (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7A_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_SHIFT                                                  (13U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_MASK                                                   (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_0P73REXT                                               (6U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_0P88REXT                                               (4U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_1P33REXT                                               (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_REXT                                                   (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_1P6REXT                                                (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_0P67REXT                                               (7U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_1P14REXT                                               (2U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_I_0P8REXT                                                (5U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_SHIFT                                                 (10U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_MASK                                                  (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_SLOW                                                  (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_FASTEST                                               (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_SLOWEST                                               (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_SR_FAST                                                  (2U)

#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_MASK                                                  (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_PU                                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_KEEPER                                                (3U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_NONE                                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_DDRCH2_PART7B_WD_PD                                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH2_2_RESERVED_0_SHIFT                                                       (0U)
#define CTRL_CORE_CONTROL_DDRCH2_2_RESERVED_0_MASK                                                        (0x000000ffU)

#define CTRL_CORE_CONTROL_DDRCH2_2_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_CONTROL_DDRCH2_2_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_SHIFT                                         (19U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_MASK                                          (0x00080000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_SHIFT                                         (18U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_MASK                                          (0x00040000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_SHIFT                                          (17U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_MASK                                           (0x00020000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_SHIFT                                          (16U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_MASK                                           (0x00010000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_SHIFT                                            (15U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_MASK                                             (0x00008000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_SHIFT                                         (14U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_MASK                                          (0x00004000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_SHIFT                                         (13U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_MASK                                          (0x00002000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_SHIFT                                          (12U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_MASK                                           (0x00001000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_SHIFT                                          (11U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_MASK                                           (0x00000800U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_SHIFT                                            (10U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_MASK                                             (0x00000400U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_SHIFT                                         (9U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_MASK                                          (0x00000200U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_SHIFT                                         (8U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_MASK                                          (0x00000100U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_SHIFT                                          (7U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_MASK                                           (0x00000080U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_SHIFT                                          (6U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_MASK                                           (0x00000040U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_SHIFT                                            (5U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_MASK                                             (0x00000020U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_RESERVED_0_SHIFT                                                        (0U)
#define CTRL_CORE_CONTROL_DDRIO_0_RESERVED_0_MASK                                                         (0x0000001fU)

#define CTRL_CORE_CONTROL_DDRIO_0_RESERVED_1_SHIFT                                                        (20U)
#define CTRL_CORE_CONTROL_DDRIO_0_RESERVED_1_MASK                                                         (0xfff00000U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP0_SHIFT                                         (26U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP0_MASK                                          (0x04000000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP1_SHIFT                                         (25U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP1_MASK                                          (0x02000000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP0_SHIFT                                          (24U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP0_MASK                                           (0x01000000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP1_SHIFT                                          (23U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP1_MASK                                           (0x00800000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_EN_SHIFT                                            (22U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_EN_MASK                                             (0x00400000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ0_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP0_SHIFT                                         (21U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP0_MASK                                          (0x00200000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP1_SHIFT                                         (20U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP1_MASK                                          (0x00100000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP0_SHIFT                                          (19U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP0_MASK                                           (0x00080000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP1_SHIFT                                          (18U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP1_MASK                                           (0x00040000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_EN_SHIFT                                            (17U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_EN_MASK                                             (0x00020000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ1_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP0_SHIFT                                         (16U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP0_MASK                                          (0x00010000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP0_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP0_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP1_SHIFT                                         (15U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP1_MASK                                          (0x00008000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP1_ENABLE                                        (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_CCAP1_DISABLE                                       (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP0_SHIFT                                          (14U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP0_MASK                                           (0x00004000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP0_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP0_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP1_SHIFT                                          (13U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP1_MASK                                           (0x00002000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP1_ENABLE                                         (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_TAP1_DISABLE                                        (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_EN_SHIFT                                            (12U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_EN_MASK                                             (0x00001000U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_EN_ENABLE                                           (1U)
#define CTRL_CORE_CONTROL_DDRIO_1_DDRCH2_VREF_DQ2_INT_EN_DISABLE                                          (0U)

#define CTRL_CORE_CONTROL_DDRIO_1_RESERVED_0_SHIFT                                                        (0U)
#define CTRL_CORE_CONTROL_DDRIO_1_RESERVED_0_MASK                                                         (0x00000fffU)

#define CTRL_CORE_CONTROL_DDRIO_1_RESERVED_1_SHIFT                                                        (27U)
#define CTRL_CORE_CONTROL_DDRIO_1_RESERVED_1_MASK                                                         (0xf8000000U)

#define CTRL_CORE_CONTROL_HYST_1_SDCARD_HYST_SHIFT                                                        (31U)
#define CTRL_CORE_CONTROL_HYST_1_SDCARD_HYST_MASK                                                         (0x80000000U)
#define CTRL_CORE_CONTROL_HYST_1_SDCARD_HYST_ENABLE                                                       (1U)
#define CTRL_CORE_CONTROL_HYST_1_SDCARD_HYST_DISABLE                                                      (0U)

#define CTRL_CORE_CONTROL_HYST_1_SDCARD_IC_SHIFT                                                          (29U)
#define CTRL_CORE_CONTROL_HYST_1_SDCARD_IC_MASK                                                           (0x60000000U)

#define CTRL_CORE_CONTROL_HYST_1_RESERVED_0_SHIFT                                                         (0U)
#define CTRL_CORE_CONTROL_HYST_1_RESERVED_0_MASK                                                          (0x1fffffffU)

#define CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_SHIFT                                                     (13U)
#define CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_MASK                                                      (0x00006000U)
#define CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_DCAN_PADS                                                 (0U)
#define CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_MCAN_DCAN1_PADS                                           (1U)
#define CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_MCAN_GPIO6_PADS                                           (2U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_AUTORESUME_EN_SHIFT                                           (30U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_AUTORESUME_EN_MASK                                            (0x40000000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DISCHGDET_SHIFT                                               (29U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DISCHGDET_MASK                                                (0x20000000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_PD_SHIFT                                                      (28U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_PD_MASK                                                       (0x10000000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_DM_COMP_SHIFT                                         (20U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_DM_COMP_MASK                                          (0x00100000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_DP_COMP_SHIFT                                         (19U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_DP_COMP_MASK                                          (0x00080000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DATADET_SHIFT                                                 (18U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DATADET_MASK                                                  (0x00040000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHGDETDONE_SHIFT                                              (17U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHGDETDONE_MASK                                               (0x00020000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHGDETECTED_SHIFT                                             (16U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHGDETECTED_MASK                                              (0x00010000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESETDONEMCLK_SHIFT                                           (15U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESETDONEMCLK_MASK                                            (0x00008000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_UTMIRESETDONE_SHIFT                                           (14U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_UTMIRESETDONE_MASK                                            (0x00004000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USBDPLL_FREQLOCK_SHIFT                                                (13U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USBDPLL_FREQLOCK_MASK                                                 (0x00002000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESETDONETCLK_SHIFT                                           (12U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESETDONETCLK_MASK                                            (0x00001000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_GPIOMODE_SHIFT                                                (11U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_GPIOMODE_MASK                                                 (0x00000800U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_EXT_CTL_SHIFT                                         (10U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_DET_EXT_CTL_MASK                                          (0x00000400U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RDM_PD_CHGDET_EN_SHIFT                                        (9U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RDM_PD_CHGDET_EN_MASK                                         (0x00000200U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RDP_PU_CHGDET_EN_SHIFT                                        (8U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RDP_PU_CHGDET_EN_MASK                                         (0x00000100U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_VSRC_EN_SHIFT                                             (7U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_VSRC_EN_MASK                                              (0x00000080U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_ISINK_EN_SHIFT                                            (6U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_CHG_ISINK_EN_MASK                                             (0x00000040U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_SINKONDP_SHIFT                                                (5U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_SINKONDP_MASK                                                 (0x00000020U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_SRCONDM_SHIFT                                                 (4U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_SRCONDM_MASK                                                  (0x00000010U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESTARTCHGDET_SHIFT                                           (3U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_RESTARTCHGDET_MASK                                            (0x00000008U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_MCPCPUEN_SHIFT                                                (2U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_MCPCPUEN_MASK                                                 (0x00000004U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_MCPCMODEEN_SHIFT                                              (1U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_MCPCMODEEN_MASK                                               (0x00000002U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DATAPOLARITYN_SHIFT                                           (0U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_USB2PHY_DATAPOLARITYN_MASK                                            (0x00000001U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_RESERVED_0_SHIFT                                                      (21U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_RESERVED_0_MASK                                                       (0x0fe00000U)

#define CTRL_CORE_SRCOMP_NORTH_SIDE_RESERVED_1_SHIFT                                                      (31U)
#define CTRL_CORE_SRCOMP_NORTH_SIDE_RESERVED_1_MASK                                                       (0x80000000U)

#define CTRL_CORE_SRCOMP_SOUTH_SIDE_USB2PHY_CHG_DET_STATUS_SHIFT                                          (12U)
#define CTRL_CORE_SRCOMP_SOUTH_SIDE_USB2PHY_CHG_DET_STATUS_MASK                                           (0x00007000U)

#define CTRL_CORE_SRCOMP_SOUTH_SIDE_RESERVED_0_SHIFT                                                      (0U)
#define CTRL_CORE_SRCOMP_SOUTH_SIDE_RESERVED_0_MASK                                                       (0x00000fffU)

#define CTRL_CORE_SRCOMP_SOUTH_SIDE_RESERVED_1_SHIFT                                                      (15U)
#define CTRL_CORE_SRCOMP_SOUTH_SIDE_RESERVED_1_MASK                                                       (0xffff8000U)

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)

#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_SHIFT                                                         (4U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_MASK                                                          (0x00000070U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP3A                                                       (0x00000000U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP5A                                                       (0x00000001U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP6A                                                       (0x00000002U)

#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_SHIFT                                                         (3U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_MASK                                                          (0x00000008U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_GROUP4B                                                       (0x00000000U)

#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_SHIFT                                                         (1U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_MASK                                                          (0x00000006U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A                                                       (0x00000000U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP4A                                                       (0x00000001U)

#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_SHIFT                                                         (0U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_MASK                                                          (0x00000001U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_GROUP2B                                                       (0x00000000U)
#define CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_GROUP3B                                                       (0x00000001U)

#endif  /* #if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) */

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_CORE_PAD_H_ */
