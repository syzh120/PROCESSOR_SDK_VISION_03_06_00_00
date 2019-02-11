/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_device_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_DEVICE_PRM_H_
#define HW_DEVICE_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define PRM_RSTCTRL                                             (0x0U)
#define PRM_RSTST                                               (0x4U)
#define PRM_RSTTIME                                             (0x8U)
#define PRM_CLKREQCTRL                                          (0xcU)
#define PRM_VOLTCTRL                                            (0x10U)
#define PRM_PWRREQCTRL                                          (0x14U)
#define PRM_PSCON_COUNT                                         (0x18U)
#define PRM_IO_COUNT                                            (0x1cU)
#define PRM_IO_PMCTRL                                           (0x20U)
#define PRM_VOLTSETUP_WARMRESET                                 (0x24U)
#define PRM_VOLTSETUP_CORE_OFF                                  (0x28U)
#define PRM_VOLTSETUP_MPU_OFF                                   (0x2cU)
#define PRM_VOLTSETUP_MM_OFF                                    (0x30U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP                            (0x34U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP                             (0x38U)
#define PRM_VOLTSETUP_MM_RET_SLEEP                              (0x3cU)
#define PRM_VP_CORE_CONFIG                                      (0x40U)
#define PRM_VP_CORE_STATUS                                      (0x44U)
#define PRM_VP_CORE_VLIMITTO                                    (0x48U)
#define PRM_VP_CORE_VOLTAGE                                     (0x4cU)
#define PRM_VP_CORE_VSTEPMAX                                    (0x50U)
#define PRM_VP_CORE_VSTEPMIN                                    (0x54U)
#define PRM_VP_MPU_CONFIG                                       (0x58U)
#define PRM_VP_MPU_STATUS                                       (0x5cU)
#define PRM_VP_MPU_VLIMITTO                                     (0x60U)
#define PRM_VP_MPU_VOLTAGE                                      (0x64U)
#define PRM_VP_MPU_VSTEPMAX                                     (0x68U)
#define PRM_VP_MPU_VSTEPMIN                                     (0x6cU)
#define PRM_VP_MM_CONFIG                                        (0x70U)
#define PRM_VP_MM_STATUS                                        (0x74U)
#define PRM_VP_MM_VLIMITTO                                      (0x78U)
#define PRM_VP_MM_VOLTAGE                                       (0x7cU)
#define PRM_VP_MM_VSTEPMAX                                      (0x80U)
#define PRM_VP_MM_VSTEPMIN                                      (0x84U)
#define PRM_VC_SMPS_CORE_CONFIG                                 (0x88U)
#define PRM_VC_SMPS_MM_CONFIG                                   (0x8cU)
#define PRM_VC_SMPS_MPU_CONFIG                                  (0x90U)
#define PRM_VC_VAL_CMD_VDD_CORE_L                               (0x94U)
#define PRM_VC_VAL_CMD_VDD_MM_L                                 (0x98U)
#define PRM_VC_VAL_CMD_VDD_MPU_L                                (0x9cU)
#define PRM_VC_VAL_BYPASS                                       (0xa0U)
#define PRM_VC_CORE_ERRST                                       (0xa4U)
#define PRM_VC_MM_ERRST                                         (0xa8U)
#define PRM_VC_MPU_ERRST                                        (0xacU)
#define PRM_VC_BYPASS_ERRST                                     (0xb0U)
#define PRM_VC_CFG_I2C_MODE                                     (0xb4U)
#define PRM_VC_CFG_I2C_CLK                                      (0xb8U)
#define PRM_SRAM_COUNT                                          (0xbcU)
#define PRM_SRAM_WKUP_SETUP                                     (0xc0U)
#define PRM_SLDO_CORE_SETUP                                     (0xc4U)
#define PRM_SLDO_CORE_CTRL                                      (0xc8U)
#define PRM_SLDO_MPU_SETUP                                      (0xccU)
#define PRM_SLDO_MPU_CTRL                                       (0xd0U)
#define PRM_SLDO_GPU_SETUP                                      (0xd4U)
#define PRM_SLDO_GPU_CTRL                                       (0xd8U)
#define PRM_ABBLDO_MPU_SETUP                                    (0xdcU)
#define PRM_ABBLDO_MPU_CTRL                                     (0xe0U)
#define PRM_ABBLDO_GPU_SETUP                                    (0xe4U)
#define PRM_ABBLDO_GPU_CTRL                                     (0xe8U)
#define PRM_BANDGAP_SETUP                                       (0xecU)
#define PRM_DEVICE_OFF_CTRL                                     (0xf0U)
#define PRM_PHASE1_CNDP                                         (0xf4U)
#define PRM_PHASE2A_CNDP                                        (0xf8U)
#define PRM_PHASE2B_CNDP                                        (0xfcU)
#define PRM_MODEM_IF_CTRL                                       (0x100U)
#define PRM_VOLTST_MPU                                          (0x110U)
#define PRM_VOLTST_MM                                           (0x114U)
#define PRM_SLDO_DSPEVE_SETUP                                   (0x118U)
#define PRM_SLDO_IVA_SETUP                                      (0x11cU)
#define PRM_ABBLDO_DSPEVE_CTRL                                  (0x120U)
#define PRM_ABBLDO_IVA_CTRL                                     (0x124U)
#define PRM_SLDO_DSPEVE_CTRL                                    (0x128U)
#define PRM_SLDO_IVA_CTRL                                       (0x12cU)
#define PRM_ABBLDO_DSPEVE_SETUP                                 (0x130U)
#define PRM_ABBLDO_IVA_SETUP                                    (0x134U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PRM_RSTCTRL_RST_GLOBAL_WARM_SW_SHIFT                    (0U)
#define PRM_RSTCTRL_RST_GLOBAL_WARM_SW_MASK                     (0x00000001U)
#define PRM_RSTCTRL_RST_GLOBAL_WARM_SW_0X0                       (0U)
#define PRM_RSTCTRL_RST_GLOBAL_WARM_SW_0X1                       (1U)

#define PRM_RSTCTRL_RST_GLOBAL_COLD_SW_SHIFT                    (1U)
#define PRM_RSTCTRL_RST_GLOBAL_COLD_SW_MASK                     (0x00000002U)
#define PRM_RSTCTRL_RST_GLOBAL_COLD_SW_0X0                       (0U)
#define PRM_RSTCTRL_RST_GLOBAL_COLD_SW_0X1                       (1U)

#define PRM_RSTST_GLOBAL_COLD_RST_SHIFT                         (0U)
#define PRM_RSTST_GLOBAL_COLD_RST_MASK                          (0x00000001U)
#define PRM_RSTST_GLOBAL_COLD_RST_0X0                            (0U)
#define PRM_RSTST_GLOBAL_COLD_RST_0X1                            (1U)

#define PRM_RSTST_GLOBAL_WARM_SW_RST_SHIFT                      (1U)
#define PRM_RSTST_GLOBAL_WARM_SW_RST_MASK                       (0x00000002U)
#define PRM_RSTST_GLOBAL_WARM_SW_RST_0X0                         (0U)
#define PRM_RSTST_GLOBAL_WARM_SW_RST_0X1                         (1U)

#define PRM_RSTST_MPU_SECURITY_VIOL_RST_SHIFT                   (2U)
#define PRM_RSTST_MPU_SECURITY_VIOL_RST_MASK                    (0x00000004U)
#define PRM_RSTST_MPU_SECURITY_VIOL_RST_0X0                      (0U)
#define PRM_RSTST_MPU_SECURITY_VIOL_RST_0X1                      (1U)

#define PRM_RSTST_MPU_WDT_RST_SHIFT                             (3U)
#define PRM_RSTST_MPU_WDT_RST_MASK                              (0x00000008U)
#define PRM_RSTST_MPU_WDT_RST_0X0                                (0U)
#define PRM_RSTST_MPU_WDT_RST_0X1                                (1U)

#define PRM_RSTST_EXTERNAL_WARM_RST_SHIFT                       (5U)
#define PRM_RSTST_EXTERNAL_WARM_RST_MASK                        (0x00000020U)
#define PRM_RSTST_EXTERNAL_WARM_RST_0X0                          (0U)
#define PRM_RSTST_EXTERNAL_WARM_RST_0X1                          (1U)

#define PRM_RSTST_SECURE_WDT_RST_SHIFT                          (4U)
#define PRM_RSTST_SECURE_WDT_RST_MASK                           (0x00000010U)
#define PRM_RSTST_SECURE_WDT_RST_0X0                             (0U)
#define PRM_RSTST_SECURE_WDT_RST_0X1                             (1U)

#define PRM_RSTST_VDD_MPU_VOLT_MGR_RST_SHIFT                    (6U)
#define PRM_RSTST_VDD_MPU_VOLT_MGR_RST_MASK                     (0x00000040U)
#define PRM_RSTST_VDD_MPU_VOLT_MGR_RST_0X0                       (0U)
#define PRM_RSTST_VDD_MPU_VOLT_MGR_RST_0X1                       (1U)

#define PRM_RSTST_VDD_MM_VOLT_MGR_RST_SHIFT                     (7U)
#define PRM_RSTST_VDD_MM_VOLT_MGR_RST_MASK                      (0x00000080U)
#define PRM_RSTST_VDD_MM_VOLT_MGR_RST_0X0                        (0U)
#define PRM_RSTST_VDD_MM_VOLT_MGR_RST_0X1                        (1U)

#define PRM_RSTST_VDD_CORE_VOLT_MGR_RST_SHIFT                   (8U)
#define PRM_RSTST_VDD_CORE_VOLT_MGR_RST_MASK                    (0x00000100U)
#define PRM_RSTST_VDD_CORE_VOLT_MGR_RST_0X0                      (0U)
#define PRM_RSTST_VDD_CORE_VOLT_MGR_RST_0X1                      (1U)

#define PRM_RSTST_ICEPICK_RST_SHIFT                             (9U)
#define PRM_RSTST_ICEPICK_RST_MASK                              (0x00000200U)
#define PRM_RSTST_ICEPICK_RST_0X0                                (0U)
#define PRM_RSTST_ICEPICK_RST_0X1                                (1U)

#define PRM_RSTST_C2C_RST_SHIFT                                 (10U)
#define PRM_RSTST_C2C_RST_MASK                                  (0x00000400U)
#define PRM_RSTST_C2C_RST_0X0                                    (0U)
#define PRM_RSTST_C2C_RST_0X1                                    (1U)

#define PRM_RSTST_TSHUT_MPU_RST_SHIFT                           (11U)
#define PRM_RSTST_TSHUT_MPU_RST_MASK                            (0x00000800U)
#define PRM_RSTST_TSHUT_MPU_RST_0X0                              (0U)
#define PRM_RSTST_TSHUT_MPU_RST_0X1                              (1U)

#define PRM_RSTST_TSHUT_MM_RST_SHIFT                            (12U)
#define PRM_RSTST_TSHUT_MM_RST_MASK                             (0x00001000U)
#define PRM_RSTST_TSHUT_MM_RST_0X0                               (0U)
#define PRM_RSTST_TSHUT_MM_RST_0X1                               (1U)

#define PRM_RSTST_TSHUT_CORE_RST_SHIFT                          (13U)
#define PRM_RSTST_TSHUT_CORE_RST_MASK                           (0x00002000U)
#define PRM_RSTST_TSHUT_CORE_RST_0X0                             (0U)
#define PRM_RSTST_TSHUT_CORE_RST_0X1                             (1U)

#define PRM_RSTST_LLI_RST_SHIFT                                 (14U)
#define PRM_RSTST_LLI_RST_MASK                                  (0x00004000U)
#define PRM_RSTST_LLI_RST_0X0                                    (0U)
#define PRM_RSTST_LLI_RST_0X1                                    (1U)

#define PRM_RSTST_TSHUT_DSPEVE_RST_SHIFT                        (15U)
#define PRM_RSTST_TSHUT_DSPEVE_RST_MASK                         (0x00008000U)
#define PRM_RSTST_TSHUT_DSPEVE_RST_0X0                           (0U)
#define PRM_RSTST_TSHUT_DSPEVE_RST_0X1                           (1U)

#define PRM_RSTST_TSHUT_IVA_RST_SHIFT                           (16U)
#define PRM_RSTST_TSHUT_IVA_RST_MASK                            (0x00010000U)
#define PRM_RSTST_TSHUT_IVA_RST_0X0                              (0U)
#define PRM_RSTST_TSHUT_IVA_RST_0X1                              (1U)

#define PRM_RSTTIME_RSTTIME1_SHIFT                              (0U)
#define PRM_RSTTIME_RSTTIME1_MASK                               (0x000003ffU)
#define PRM_RSTTIME_RSTTIME1_RESERVED                            (0U)

#define PRM_RSTTIME_RSTTIME2_SHIFT                              (10U)
#define PRM_RSTTIME_RSTTIME2_MASK                               (0x00007c00U)
#define PRM_RSTTIME_RSTTIME2_RESERVED                            (0U)

#define PRM_CLKREQCTRL_CLKREQ_COND_SHIFT                        (0U)
#define PRM_CLKREQCTRL_CLKREQ_COND_MASK                         (0x00000007U)
#define PRM_CLKREQCTRL_CLKREQ_COND_NEVER                         (0U)
#define PRM_CLKREQCTRL_CLKREQ_COND_OFF                           (1U)
#define PRM_CLKREQCTRL_CLKREQ_COND_RET                           (2U)
#define PRM_CLKREQCTRL_CLKREQ_COND_SLEEP                         (3U)
#define PRM_CLKREQCTRL_CLKREQ_COND_ON                            (4U)
#define PRM_CLKREQCTRL_CLKREQ_COND_RESERVED_5                    (5U)
#define PRM_CLKREQCTRL_CLKREQ_COND_RESERVED_6                    (6U)
#define PRM_CLKREQCTRL_CLKREQ_COND_RESERVED_7                    (7U)

#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_SHIFT                  (2U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_MASK                   (0x0000000cU)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_DISABLED                (0U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_AUTO_SLEEP              (1U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_AUTO_RET                (2U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MPU_L_RESERVED                (3U)

#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_SHIFT                 (0U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_MASK                  (0x00000003U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_DISABLED               (0U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_AUTO_SLEEP             (1U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_AUTO_RET               (2U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_CORE_L_RESERVED               (3U)

#define PRM_VOLTCTRL_VDD_MPU_PRESENCE_SHIFT                     (8U)
#define PRM_VOLTCTRL_VDD_MPU_PRESENCE_MASK                      (0x00000100U)
#define PRM_VOLTCTRL_VDD_MPU_PRESENCE_VOLTAGE_PRESENT            (1U)
#define PRM_VOLTCTRL_VDD_MPU_PRESENCE_VOLTAGE_ABSENT             (0U)

#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_SHIFT                   (4U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_MASK                    (0x00000030U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_DISABLED                 (0U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_AUTO_SLEEP               (1U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_AUTO_RET                 (2U)
#define PRM_VOLTCTRL_AUTO_CTRL_VDD_MM_L_RESERVED                 (3U)

#define PRM_VOLTCTRL_VDD_MM_PRESENCE_SHIFT                      (9U)
#define PRM_VOLTCTRL_VDD_MM_PRESENCE_MASK                       (0x00000200U)
#define PRM_VOLTCTRL_VDD_MM_PRESENCE_VOLTAGE_PRESENT             (1U)
#define PRM_VOLTCTRL_VDD_MM_PRESENCE_VOLTAGE_ABSENT              (0U)

#define PRM_VOLTCTRL_VDD_CORE_I2C_DISABLE_SHIFT                 (12U)
#define PRM_VOLTCTRL_VDD_CORE_I2C_DISABLE_MASK                  (0x00001000U)
#define PRM_VOLTCTRL_VDD_CORE_I2C_DISABLE_I2C_ENABLED            (0U)
#define PRM_VOLTCTRL_VDD_CORE_I2C_DISABLE_I2C_DISABLED           (1U)

#define PRM_VOLTCTRL_VDD_MPU_I2C_DISABLE_SHIFT                  (13U)
#define PRM_VOLTCTRL_VDD_MPU_I2C_DISABLE_MASK                   (0x00002000U)
#define PRM_VOLTCTRL_VDD_MPU_I2C_DISABLE_I2C_ENABLED             (0U)
#define PRM_VOLTCTRL_VDD_MPU_I2C_DISABLE_I2C_DISABLED            (1U)

#define PRM_VOLTCTRL_VDD_MM_I2C_DISABLE_SHIFT                   (14U)
#define PRM_VOLTCTRL_VDD_MM_I2C_DISABLE_MASK                    (0x00004000U)
#define PRM_VOLTCTRL_VDD_MM_I2C_DISABLE_I2C_ENABLED              (0U)
#define PRM_VOLTCTRL_VDD_MM_I2C_DISABLE_I2C_DISABLED             (1U)

#define PRM_PWRREQCTRL_PWRREQ_COND_SHIFT                        (0U)
#define PRM_PWRREQCTRL_PWRREQ_COND_MASK                         (0x00000003U)
#define PRM_PWRREQCTRL_PWRREQ_COND_NEVER                         (0U)
#define PRM_PWRREQCTRL_PWRREQ_COND_SLEEP                         (1U)
#define PRM_PWRREQCTRL_PWRREQ_COND_RET                           (2U)
#define PRM_PWRREQCTRL_PWRREQ_COND_OFF                           (3U)

#define PRM_PSCON_COUNT_PCHARGE_TIME_SHIFT                      (0U)
#define PRM_PSCON_COUNT_PCHARGE_TIME_MASK                       (0x000000ffU)

#define PRM_PSCON_COUNT_PONOUT_2_PGOODIN_TIME_SHIFT             (8U)
#define PRM_PSCON_COUNT_PONOUT_2_PGOODIN_TIME_MASK              (0x0000ff00U)

#define PRM_PSCON_COUNT_HG_PONOUT_2_PGOODIN_TIME_SHIFT          (16U)
#define PRM_PSCON_COUNT_HG_PONOUT_2_PGOODIN_TIME_MASK           (0x00ff0000U)

#define PRM_IO_COUNT_ISO_2_ON_TIME_SHIFT                        (0U)
#define PRM_IO_COUNT_ISO_2_ON_TIME_MASK                         (0x000000ffU)

#define PRM_IO_PMCTRL_ISOCLK_OVERRIDE_SHIFT                     (0U)
#define PRM_IO_PMCTRL_ISOCLK_OVERRIDE_MASK                      (0x00000001U)
#define PRM_IO_PMCTRL_ISOCLK_OVERRIDE_NOOVERRIDE                 (0U)
#define PRM_IO_PMCTRL_ISOCLK_OVERRIDE_OVERRIDE                   (1U)

#define PRM_IO_PMCTRL_ISOCLK_STATUS_SHIFT                       (1U)
#define PRM_IO_PMCTRL_ISOCLK_STATUS_MASK                        (0x00000002U)

#define PRM_IO_PMCTRL_WUCLK_CTRL_SHIFT                          (8U)
#define PRM_IO_PMCTRL_WUCLK_CTRL_MASK                           (0x00000100U)
#define PRM_IO_PMCTRL_WUCLK_CTRL_LOW                             (0U)
#define PRM_IO_PMCTRL_WUCLK_CTRL_HIGH                            (1U)

#define PRM_IO_PMCTRL_WUCLK_STATUS_SHIFT                        (9U)
#define PRM_IO_PMCTRL_WUCLK_STATUS_MASK                         (0x00000200U)

#define PRM_IO_PMCTRL_GLOBAL_WUEN_SHIFT                         (16U)
#define PRM_IO_PMCTRL_GLOBAL_WUEN_MASK                          (0x00010000U)
#define PRM_IO_PMCTRL_GLOBAL_WUEN_DISABLED                       (0U)
#define PRM_IO_PMCTRL_GLOBAL_WUEN_ENABLED                        (1U)

#define PRM_IO_PMCTRL_ISOOVR_EXTEND_SHIFT                       (4U)
#define PRM_IO_PMCTRL_ISOOVR_EXTEND_MASK                        (0x00000010U)
#define PRM_IO_PMCTRL_ISOOVR_EXTEND_NOOVERRIDE                   (0U)
#define PRM_IO_PMCTRL_ISOOVR_EXTEND_OVERRIDE                     (1U)

#define PRM_IO_PMCTRL_IO_ON_STATUS_SHIFT                        (5U)
#define PRM_IO_PMCTRL_IO_ON_STATUS_MASK                         (0x00000020U)
#define PRM_IO_PMCTRL_IO_ON_STATUS_LOW                           (0U)
#define PRM_IO_PMCTRL_IO_ON_STATUS_HIGH                          (1U)

#define PRM_VOLTSETUP_WARMRESET_STABLE_COUNT_SHIFT              (0U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_COUNT_MASK               (0x0000003fU)

#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_SHIFT            (8U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_MASK             (0x00000300U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_X32               (0U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_X256              (1U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_X2048             (2U)
#define PRM_VOLTSETUP_WARMRESET_STABLE_PRESCAL_X16384            (3U)

#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_COUNT_SHIFT              (0U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_COUNT_MASK               (0x0000003fU)

#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_SHIFT            (8U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_MASK             (0x00000300U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_X64               (0U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_X256              (1U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_X512              (2U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_UP_PRESCAL_X2048             (3U)

#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_COUNT_SHIFT            (16U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_COUNT_MASK             (0x003f0000U)

#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_SHIFT          (24U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_MASK           (0x03000000U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_X64             (0U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_X256            (1U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_X512            (2U)
#define PRM_VOLTSETUP_CORE_OFF_RAMP_DOWN_PRESCAL_X2048           (3U)

#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_COUNT_SHIFT               (0U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_COUNT_MASK                (0x0000003fU)

#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_SHIFT             (8U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_MASK              (0x00000300U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_X64                (0U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_X256               (1U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_X512               (2U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_UP_PRESCAL_X2048              (3U)

#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_COUNT_SHIFT             (16U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_COUNT_MASK              (0x003f0000U)

#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_SHIFT           (24U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_MASK            (0x03000000U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_X64              (0U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_X256             (1U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_X512             (2U)
#define PRM_VOLTSETUP_MPU_OFF_RAMP_DOWN_PRESCAL_X2048            (3U)

#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_COUNT_SHIFT                (0U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_COUNT_MASK                 (0x0000003fU)

#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_SHIFT              (8U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_MASK               (0x00000300U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_X64                 (0U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_X256                (1U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_X512                (2U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_UP_PRESCAL_X2048               (3U)

#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_COUNT_SHIFT              (16U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_COUNT_MASK               (0x003f0000U)

#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_SHIFT            (24U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_MASK             (0x03000000U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_X64               (0U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_X256              (1U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_X512              (2U)
#define PRM_VOLTSETUP_MM_OFF_RAMP_DOWN_PRESCAL_X2048             (3U)

#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_COUNT_SHIFT        (0U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_COUNT_MASK         (0x0000003fU)

#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_SHIFT      (8U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_MASK       (0x00000300U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_X64         (0U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_X256        (1U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_X512        (2U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_UP_PRESCAL_X2048       (3U)

#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_COUNT_SHIFT      (16U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_COUNT_MASK       (0x003f0000U)

#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_SHIFT    (24U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_MASK     (0x03000000U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_X64       (0U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_X256      (1U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_X512      (2U)
#define PRM_VOLTSETUP_CORE_RET_SLEEP_RAMP_DOWN_PRESCAL_X2048     (3U)

#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_COUNT_SHIFT         (0U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_COUNT_MASK          (0x0000003fU)

#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_SHIFT       (8U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_MASK        (0x00000300U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_X64          (0U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_X256         (1U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_X512         (2U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_UP_PRESCAL_X2048        (3U)

#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_COUNT_SHIFT       (16U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_COUNT_MASK        (0x003f0000U)

#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_SHIFT     (24U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_MASK      (0x03000000U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_X64        (0U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_X256       (1U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_X512       (2U)
#define PRM_VOLTSETUP_MPU_RET_SLEEP_RAMP_DOWN_PRESCAL_X2048      (3U)

#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_COUNT_SHIFT          (0U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_COUNT_MASK           (0x0000003fU)

#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_SHIFT        (8U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_MASK         (0x00000300U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_X64           (0U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_X256          (1U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_X512          (2U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_UP_PRESCAL_X2048         (3U)

#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_COUNT_SHIFT        (16U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_COUNT_MASK         (0x003f0000U)

#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_SHIFT      (24U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_MASK       (0x03000000U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_X64         (0U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_X256        (1U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_X512        (2U)
#define PRM_VOLTSETUP_MM_RET_SLEEP_RAMP_DOWN_PRESCAL_X2048       (3U)

#define PRM_VP_CORE_CONFIG_TIMEOUTEN_SHIFT                      (3U)
#define PRM_VP_CORE_CONFIG_TIMEOUTEN_MASK                       (0x00000008U)
#define PRM_VP_CORE_CONFIG_TIMEOUTEN_EN                          (1U)
#define PRM_VP_CORE_CONFIG_TIMEOUTEN_DIS                         (0U)

#define PRM_VP_CORE_CONFIG_FORCEUPDATE_SHIFT                    (1U)
#define PRM_VP_CORE_CONFIG_FORCEUPDATE_MASK                     (0x00000002U)
#define PRM_VP_CORE_CONFIG_FORCEUPDATE_NEGEDGE                   (0U)
#define PRM_VP_CORE_CONFIG_FORCEUPDATE_POSEDGE                   (1U)

#define PRM_VP_CORE_CONFIG_INITVDD_SHIFT                        (2U)
#define PRM_VP_CORE_CONFIG_INITVDD_MASK                         (0x00000004U)
#define PRM_VP_CORE_CONFIG_INITVDD_POSEDGE                       (1U)
#define PRM_VP_CORE_CONFIG_INITVDD_NEGEDGE                       (0U)

#define PRM_VP_CORE_CONFIG_INITVOLTAGE_SHIFT                    (8U)
#define PRM_VP_CORE_CONFIG_INITVOLTAGE_MASK                     (0x0000ff00U)

#define PRM_VP_CORE_CONFIG_VPENABLE_SHIFT                       (0U)
#define PRM_VP_CORE_CONFIG_VPENABLE_MASK                        (0x00000001U)
#define PRM_VP_CORE_CONFIG_VPENABLE_EN                           (1U)
#define PRM_VP_CORE_CONFIG_VPENABLE_DIS                          (0U)

#define PRM_VP_CORE_CONFIG_ERROROFFSET_SHIFT                    (24U)
#define PRM_VP_CORE_CONFIG_ERROROFFSET_MASK                     (0xff000000U)

#define PRM_VP_CORE_CONFIG_ERRORGAIN_SHIFT                      (16U)
#define PRM_VP_CORE_CONFIG_ERRORGAIN_MASK                       (0x00ff0000U)

#define PRM_VP_CORE_STATUS_VPINIDLE_SHIFT                       (0U)
#define PRM_VP_CORE_STATUS_VPINIDLE_MASK                        (0x00000001U)
#define PRM_VP_CORE_STATUS_VPINIDLE_ISIDLE                       (1U)
#define PRM_VP_CORE_STATUS_VPINIDLE_NORMAL                       (0U)

#define PRM_VP_CORE_VLIMITTO_VDDMAX_SHIFT                       (24U)
#define PRM_VP_CORE_VLIMITTO_VDDMAX_MASK                        (0xff000000U)

#define PRM_VP_CORE_VLIMITTO_VDDMIN_SHIFT                       (16U)
#define PRM_VP_CORE_VLIMITTO_VDDMIN_MASK                        (0x00ff0000U)

#define PRM_VP_CORE_VLIMITTO_TIMEOUT_SHIFT                      (0U)
#define PRM_VP_CORE_VLIMITTO_TIMEOUT_MASK                       (0x0000ffffU)

#define PRM_VP_CORE_VOLTAGE_VPVOLTAGE_SHIFT                     (0U)
#define PRM_VP_CORE_VOLTAGE_VPVOLTAGE_MASK                      (0x000000ffU)

#define PRM_VP_CORE_VOLTAGE_FORCEUPDATEWAIT_SHIFT               (8U)
#define PRM_VP_CORE_VOLTAGE_FORCEUPDATEWAIT_MASK                (0xffffff00U)

#define PRM_VP_CORE_VSTEPMAX_VSTEPMAX_SHIFT                     (0U)
#define PRM_VP_CORE_VSTEPMAX_VSTEPMAX_MASK                      (0x000000ffU)

#define PRM_VP_CORE_VSTEPMAX_SMPSWAITTIMEMAX_SHIFT              (8U)
#define PRM_VP_CORE_VSTEPMAX_SMPSWAITTIMEMAX_MASK               (0x00ffff00U)

#define PRM_VP_CORE_VSTEPMIN_SMPSWAITTIMEMIN_SHIFT              (8U)
#define PRM_VP_CORE_VSTEPMIN_SMPSWAITTIMEMIN_MASK               (0x00ffff00U)

#define PRM_VP_CORE_VSTEPMIN_VSTEPMIN_SHIFT                     (0U)
#define PRM_VP_CORE_VSTEPMIN_VSTEPMIN_MASK                      (0x000000ffU)

#define PRM_VP_MPU_CONFIG_TIMEOUTEN_SHIFT                       (3U)
#define PRM_VP_MPU_CONFIG_TIMEOUTEN_MASK                        (0x00000008U)
#define PRM_VP_MPU_CONFIG_TIMEOUTEN_EN                           (1U)
#define PRM_VP_MPU_CONFIG_TIMEOUTEN_DIS                          (0U)

#define PRM_VP_MPU_CONFIG_FORCEUPDATE_SHIFT                     (1U)
#define PRM_VP_MPU_CONFIG_FORCEUPDATE_MASK                      (0x00000002U)
#define PRM_VP_MPU_CONFIG_FORCEUPDATE_NEGEDGE                    (0U)
#define PRM_VP_MPU_CONFIG_FORCEUPDATE_POSEDGE                    (1U)

#define PRM_VP_MPU_CONFIG_INITVDD_SHIFT                         (2U)
#define PRM_VP_MPU_CONFIG_INITVDD_MASK                          (0x00000004U)
#define PRM_VP_MPU_CONFIG_INITVDD_POSEDGE                        (1U)
#define PRM_VP_MPU_CONFIG_INITVDD_NEGEDGE                        (0U)

#define PRM_VP_MPU_CONFIG_INITVOLTAGE_SHIFT                     (8U)
#define PRM_VP_MPU_CONFIG_INITVOLTAGE_MASK                      (0x0000ff00U)

#define PRM_VP_MPU_CONFIG_VPENABLE_SHIFT                        (0U)
#define PRM_VP_MPU_CONFIG_VPENABLE_MASK                         (0x00000001U)
#define PRM_VP_MPU_CONFIG_VPENABLE_EN                            (1U)
#define PRM_VP_MPU_CONFIG_VPENABLE_DIS                           (0U)

#define PRM_VP_MPU_CONFIG_ERROROFFSET_SHIFT                     (24U)
#define PRM_VP_MPU_CONFIG_ERROROFFSET_MASK                      (0xff000000U)

#define PRM_VP_MPU_CONFIG_ERRORGAIN_SHIFT                       (16U)
#define PRM_VP_MPU_CONFIG_ERRORGAIN_MASK                        (0x00ff0000U)

#define PRM_VP_MPU_STATUS_VPINIDLE_SHIFT                        (0U)
#define PRM_VP_MPU_STATUS_VPINIDLE_MASK                         (0x00000001U)
#define PRM_VP_MPU_STATUS_VPINIDLE_ISIDLE                        (1U)
#define PRM_VP_MPU_STATUS_VPINIDLE_NORMAL                        (0U)

#define PRM_VP_MPU_VLIMITTO_VDDMAX_SHIFT                        (24U)
#define PRM_VP_MPU_VLIMITTO_VDDMAX_MASK                         (0xff000000U)

#define PRM_VP_MPU_VLIMITTO_VDDMIN_SHIFT                        (16U)
#define PRM_VP_MPU_VLIMITTO_VDDMIN_MASK                         (0x00ff0000U)

#define PRM_VP_MPU_VLIMITTO_TIMEOUT_SHIFT                       (0U)
#define PRM_VP_MPU_VLIMITTO_TIMEOUT_MASK                        (0x0000ffffU)

#define PRM_VP_MPU_VOLTAGE_VPVOLTAGE_SHIFT                      (0U)
#define PRM_VP_MPU_VOLTAGE_VPVOLTAGE_MASK                       (0x000000ffU)

#define PRM_VP_MPU_VOLTAGE_FORCEUPDATEWAIT_SHIFT                (8U)
#define PRM_VP_MPU_VOLTAGE_FORCEUPDATEWAIT_MASK                 (0xffffff00U)

#define PRM_VP_MPU_VSTEPMAX_VSTEPMAX_SHIFT                      (0U)
#define PRM_VP_MPU_VSTEPMAX_VSTEPMAX_MASK                       (0x000000ffU)

#define PRM_VP_MPU_VSTEPMAX_SMPSWAITTIMEMAX_SHIFT               (8U)
#define PRM_VP_MPU_VSTEPMAX_SMPSWAITTIMEMAX_MASK                (0x00ffff00U)

#define PRM_VP_MPU_VSTEPMIN_SMPSWAITTIMEMIN_SHIFT               (8U)
#define PRM_VP_MPU_VSTEPMIN_SMPSWAITTIMEMIN_MASK                (0x00ffff00U)

#define PRM_VP_MPU_VSTEPMIN_VSTEPMIN_SHIFT                      (0U)
#define PRM_VP_MPU_VSTEPMIN_VSTEPMIN_MASK                       (0x000000ffU)

#define PRM_VP_MM_CONFIG_TIMEOUTEN_SHIFT                        (3U)
#define PRM_VP_MM_CONFIG_TIMEOUTEN_MASK                         (0x00000008U)
#define PRM_VP_MM_CONFIG_TIMEOUTEN_EN                            (1U)
#define PRM_VP_MM_CONFIG_TIMEOUTEN_DIS                           (0U)

#define PRM_VP_MM_CONFIG_FORCEUPDATE_SHIFT                      (1U)
#define PRM_VP_MM_CONFIG_FORCEUPDATE_MASK                       (0x00000002U)
#define PRM_VP_MM_CONFIG_FORCEUPDATE_NEGEDGE                     (0U)
#define PRM_VP_MM_CONFIG_FORCEUPDATE_POSEDGE                     (1U)

#define PRM_VP_MM_CONFIG_INITVDD_SHIFT                          (2U)
#define PRM_VP_MM_CONFIG_INITVDD_MASK                           (0x00000004U)
#define PRM_VP_MM_CONFIG_INITVDD_POSEDGE                         (1U)
#define PRM_VP_MM_CONFIG_INITVDD_NEGEDGE                         (0U)

#define PRM_VP_MM_CONFIG_INITVOLTAGE_SHIFT                      (8U)
#define PRM_VP_MM_CONFIG_INITVOLTAGE_MASK                       (0x0000ff00U)

#define PRM_VP_MM_CONFIG_VPENABLE_SHIFT                         (0U)
#define PRM_VP_MM_CONFIG_VPENABLE_MASK                          (0x00000001U)
#define PRM_VP_MM_CONFIG_VPENABLE_EN                             (1U)
#define PRM_VP_MM_CONFIG_VPENABLE_DIS                            (0U)

#define PRM_VP_MM_CONFIG_ERROROFFSET_SHIFT                      (24U)
#define PRM_VP_MM_CONFIG_ERROROFFSET_MASK                       (0xff000000U)

#define PRM_VP_MM_CONFIG_ERRORGAIN_SHIFT                        (16U)
#define PRM_VP_MM_CONFIG_ERRORGAIN_MASK                         (0x00ff0000U)

#define PRM_VP_MM_STATUS_VPINIDLE_SHIFT                         (0U)
#define PRM_VP_MM_STATUS_VPINIDLE_MASK                          (0x00000001U)
#define PRM_VP_MM_STATUS_VPINIDLE_ISIDLE                         (1U)
#define PRM_VP_MM_STATUS_VPINIDLE_NORMAL                         (0U)

#define PRM_VP_MM_VLIMITTO_VDDMAX_SHIFT                         (24U)
#define PRM_VP_MM_VLIMITTO_VDDMAX_MASK                          (0xff000000U)

#define PRM_VP_MM_VLIMITTO_VDDMIN_SHIFT                         (16U)
#define PRM_VP_MM_VLIMITTO_VDDMIN_MASK                          (0x00ff0000U)

#define PRM_VP_MM_VLIMITTO_TIMEOUT_SHIFT                        (0U)
#define PRM_VP_MM_VLIMITTO_TIMEOUT_MASK                         (0x0000ffffU)

#define PRM_VP_MM_VOLTAGE_VPVOLTAGE_SHIFT                       (0U)
#define PRM_VP_MM_VOLTAGE_VPVOLTAGE_MASK                        (0x000000ffU)

#define PRM_VP_MM_VOLTAGE_FORCEUPDATEWAIT_SHIFT                 (8U)
#define PRM_VP_MM_VOLTAGE_FORCEUPDATEWAIT_MASK                  (0xffffff00U)

#define PRM_VP_MM_VSTEPMAX_VSTEPMAX_SHIFT                       (0U)
#define PRM_VP_MM_VSTEPMAX_VSTEPMAX_MASK                        (0x000000ffU)

#define PRM_VP_MM_VSTEPMAX_SMPSWAITTIMEMAX_SHIFT                (8U)
#define PRM_VP_MM_VSTEPMAX_SMPSWAITTIMEMAX_MASK                 (0x00ffff00U)

#define PRM_VP_MM_VSTEPMIN_SMPSWAITTIMEMIN_SHIFT                (8U)
#define PRM_VP_MM_VSTEPMIN_SMPSWAITTIMEMIN_MASK                 (0x00ffff00U)

#define PRM_VP_MM_VSTEPMIN_VSTEPMIN_SHIFT                       (0U)
#define PRM_VP_MM_VSTEPMIN_VSTEPMIN_MASK                        (0x000000ffU)

#define PRM_VC_SMPS_CORE_CONFIG_SA_VDD_CORE_L_SHIFT             (0U)
#define PRM_VC_SMPS_CORE_CONFIG_SA_VDD_CORE_L_MASK              (0x0000007fU)

#define PRM_VC_SMPS_CORE_CONFIG_VOLRA_VDD_CORE_L_SHIFT          (8U)
#define PRM_VC_SMPS_CORE_CONFIG_VOLRA_VDD_CORE_L_MASK           (0x0000ff00U)

#define PRM_VC_SMPS_CORE_CONFIG_CMDRA_VDD_CORE_L_SHIFT          (16U)
#define PRM_VC_SMPS_CORE_CONFIG_CMDRA_VDD_CORE_L_MASK           (0x00ff0000U)

#define PRM_VC_SMPS_CORE_CONFIG_CMD_VDD_CORE_L_SHIFT            (28U)
#define PRM_VC_SMPS_CORE_CONFIG_CMD_VDD_CORE_L_MASK             (0x10000000U)
#define PRM_VC_SMPS_CORE_CONFIG_CMD_VDD_CORE_L_MPU               (0U)
#define PRM_VC_SMPS_CORE_CONFIG_CMD_VDD_CORE_L_CORE              (1U)

#define PRM_VC_SMPS_CORE_CONFIG_SEL_SA_VDD_CORE_L_SHIFT         (24U)
#define PRM_VC_SMPS_CORE_CONFIG_SEL_SA_VDD_CORE_L_MASK          (0x01000000U)
#define PRM_VC_SMPS_CORE_CONFIG_SEL_SA_VDD_CORE_L_SEL_MPU        (0U)
#define PRM_VC_SMPS_CORE_CONFIG_SEL_SA_VDD_CORE_L_SEL_CORE       (1U)

#define PRM_VC_SMPS_CORE_CONFIG_RAV_VDD_CORE_L_SHIFT            (25U)
#define PRM_VC_SMPS_CORE_CONFIG_RAV_VDD_CORE_L_MASK             (0x02000000U)
#define PRM_VC_SMPS_CORE_CONFIG_RAV_VDD_CORE_L_SEL_MPU           (0U)
#define PRM_VC_SMPS_CORE_CONFIG_RAV_VDD_CORE_L_SEL_CORE          (1U)

#define PRM_VC_SMPS_CORE_CONFIG_RAC_VDD_CORE_L_SHIFT            (26U)
#define PRM_VC_SMPS_CORE_CONFIG_RAC_VDD_CORE_L_MASK             (0x04000000U)
#define PRM_VC_SMPS_CORE_CONFIG_RAC_VDD_CORE_L_SEL_MPU           (0U)
#define PRM_VC_SMPS_CORE_CONFIG_RAC_VDD_CORE_L_SEL_CORE          (1U)

#define PRM_VC_SMPS_CORE_CONFIG_RACEN_VDD_CORE_L_SHIFT          (27U)
#define PRM_VC_SMPS_CORE_CONFIG_RACEN_VDD_CORE_L_MASK           (0x08000000U)
#define PRM_VC_SMPS_CORE_CONFIG_RACEN_VDD_CORE_L_VOLRA           (0U)
#define PRM_VC_SMPS_CORE_CONFIG_RACEN_VDD_CORE_L_CMDRA           (1U)

#define PRM_VC_SMPS_MM_CONFIG_SA_VDD_MM_L_SHIFT                 (0U)
#define PRM_VC_SMPS_MM_CONFIG_SA_VDD_MM_L_MASK                  (0x0000007fU)

#define PRM_VC_SMPS_MM_CONFIG_VOLRA_VDD_MM_L_SHIFT              (8U)
#define PRM_VC_SMPS_MM_CONFIG_VOLRA_VDD_MM_L_MASK               (0x0000ff00U)

#define PRM_VC_SMPS_MM_CONFIG_CMDRA_VDD_MM_L_SHIFT              (16U)
#define PRM_VC_SMPS_MM_CONFIG_CMDRA_VDD_MM_L_MASK               (0x00ff0000U)

#define PRM_VC_SMPS_MM_CONFIG_SEL_SA_VDD_MM_L_SHIFT             (24U)
#define PRM_VC_SMPS_MM_CONFIG_SEL_SA_VDD_MM_L_MASK              (0x01000000U)
#define PRM_VC_SMPS_MM_CONFIG_SEL_SA_VDD_MM_L_SEL_MPU            (0U)
#define PRM_VC_SMPS_MM_CONFIG_SEL_SA_VDD_MM_L_SEL_MM             (1U)

#define PRM_VC_SMPS_MM_CONFIG_RAV_VDD_MM_L_SHIFT                (25U)
#define PRM_VC_SMPS_MM_CONFIG_RAV_VDD_MM_L_MASK                 (0x02000000U)
#define PRM_VC_SMPS_MM_CONFIG_RAV_VDD_MM_L_SEL_MPU               (0U)
#define PRM_VC_SMPS_MM_CONFIG_RAV_VDD_MM_L_SEL_MM                (1U)

#define PRM_VC_SMPS_MM_CONFIG_RAC_VDD_MM_L_SHIFT                (26U)
#define PRM_VC_SMPS_MM_CONFIG_RAC_VDD_MM_L_MASK                 (0x04000000U)
#define PRM_VC_SMPS_MM_CONFIG_RAC_VDD_MM_L_SEL_MPU               (0U)
#define PRM_VC_SMPS_MM_CONFIG_RAC_VDD_MM_L_SEL_MM                (1U)

#define PRM_VC_SMPS_MM_CONFIG_RACEN_VDD_MM_L_SHIFT              (27U)
#define PRM_VC_SMPS_MM_CONFIG_RACEN_VDD_MM_L_MASK               (0x08000000U)
#define PRM_VC_SMPS_MM_CONFIG_RACEN_VDD_MM_L_VOLRA               (0U)
#define PRM_VC_SMPS_MM_CONFIG_RACEN_VDD_MM_L_CMDRA               (1U)

#define PRM_VC_SMPS_MM_CONFIG_CMD_VDD_MM_L_SHIFT                (28U)
#define PRM_VC_SMPS_MM_CONFIG_CMD_VDD_MM_L_MASK                 (0x10000000U)
#define PRM_VC_SMPS_MM_CONFIG_CMD_VDD_MM_L_MPU                   (0U)
#define PRM_VC_SMPS_MM_CONFIG_CMD_VDD_MM_L_MM                    (1U)

#define PRM_VC_SMPS_MPU_CONFIG_SA_VDD_MPU_L_SHIFT               (0U)
#define PRM_VC_SMPS_MPU_CONFIG_SA_VDD_MPU_L_MASK                (0x0000007fU)

#define PRM_VC_SMPS_MPU_CONFIG_VOLRA_VDD_MPU_L_SHIFT            (8U)
#define PRM_VC_SMPS_MPU_CONFIG_VOLRA_VDD_MPU_L_MASK             (0x0000ff00U)

#define PRM_VC_SMPS_MPU_CONFIG_CMDRA_VDD_MPU_L_SHIFT            (16U)
#define PRM_VC_SMPS_MPU_CONFIG_CMDRA_VDD_MPU_L_MASK             (0x00ff0000U)

#define PRM_VC_SMPS_MPU_CONFIG_SEL_SA_VDD_MPU_L_SHIFT           (24U)
#define PRM_VC_SMPS_MPU_CONFIG_SEL_SA_VDD_MPU_L_MASK            (0x01000000U)

#define PRM_VC_SMPS_MPU_CONFIG_RAV_VDD_MPU_L_SHIFT              (25U)
#define PRM_VC_SMPS_MPU_CONFIG_RAV_VDD_MPU_L_MASK               (0x02000000U)

#define PRM_VC_SMPS_MPU_CONFIG_RAC_VDD_MPU_L_SHIFT              (26U)
#define PRM_VC_SMPS_MPU_CONFIG_RAC_VDD_MPU_L_MASK               (0x04000000U)

#define PRM_VC_SMPS_MPU_CONFIG_RACEN_VDD_MPU_L_SHIFT            (27U)
#define PRM_VC_SMPS_MPU_CONFIG_RACEN_VDD_MPU_L_MASK             (0x08000000U)
#define PRM_VC_SMPS_MPU_CONFIG_RACEN_VDD_MPU_L_VOLRA             (0U)
#define PRM_VC_SMPS_MPU_CONFIG_RACEN_VDD_MPU_L_CMDRA             (1U)

#define PRM_VC_SMPS_MPU_CONFIG_CMD_VDD_MPU_L_SHIFT              (28U)
#define PRM_VC_SMPS_MPU_CONFIG_CMD_VDD_MPU_L_MASK               (0x10000000U)

#define PRM_VC_VAL_CMD_VDD_CORE_L_ON_SHIFT                      (24U)
#define PRM_VC_VAL_CMD_VDD_CORE_L_ON_MASK                       (0xff000000U)

#define PRM_VC_VAL_CMD_VDD_CORE_L_ONLP_SHIFT                    (16U)
#define PRM_VC_VAL_CMD_VDD_CORE_L_ONLP_MASK                     (0x00ff0000U)

#define PRM_VC_VAL_CMD_VDD_CORE_L_RET_SHIFT                     (8U)
#define PRM_VC_VAL_CMD_VDD_CORE_L_RET_MASK                      (0x0000ff00U)

#define PRM_VC_VAL_CMD_VDD_CORE_L_OFF_SHIFT                     (0U)
#define PRM_VC_VAL_CMD_VDD_CORE_L_OFF_MASK                      (0x000000ffU)

#define PRM_VC_VAL_CMD_VDD_MM_L_ONLP_SHIFT                      (16U)
#define PRM_VC_VAL_CMD_VDD_MM_L_ONLP_MASK                       (0x00ff0000U)

#define PRM_VC_VAL_CMD_VDD_MM_L_ON_SHIFT                        (24U)
#define PRM_VC_VAL_CMD_VDD_MM_L_ON_MASK                         (0xff000000U)

#define PRM_VC_VAL_CMD_VDD_MM_L_RET_SHIFT                       (8U)
#define PRM_VC_VAL_CMD_VDD_MM_L_RET_MASK                        (0x0000ff00U)

#define PRM_VC_VAL_CMD_VDD_MM_L_OFF_SHIFT                       (0U)
#define PRM_VC_VAL_CMD_VDD_MM_L_OFF_MASK                        (0x000000ffU)

#define PRM_VC_VAL_CMD_VDD_MPU_L_ONLP_SHIFT                     (16U)
#define PRM_VC_VAL_CMD_VDD_MPU_L_ONLP_MASK                      (0x00ff0000U)

#define PRM_VC_VAL_CMD_VDD_MPU_L_ON_SHIFT                       (24U)
#define PRM_VC_VAL_CMD_VDD_MPU_L_ON_MASK                        (0xff000000U)

#define PRM_VC_VAL_CMD_VDD_MPU_L_RET_SHIFT                      (8U)
#define PRM_VC_VAL_CMD_VDD_MPU_L_RET_MASK                       (0x0000ff00U)

#define PRM_VC_VAL_CMD_VDD_MPU_L_OFF_SHIFT                      (0U)
#define PRM_VC_VAL_CMD_VDD_MPU_L_OFF_MASK                       (0x000000ffU)

#define PRM_VC_VAL_BYPASS_REGADDR_SHIFT                         (8U)
#define PRM_VC_VAL_BYPASS_REGADDR_MASK                          (0x0000ff00U)

#define PRM_VC_VAL_BYPASS_DATA_SHIFT                            (16U)
#define PRM_VC_VAL_BYPASS_DATA_MASK                             (0x00ff0000U)

#define PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT                       (0U)
#define PRM_VC_VAL_BYPASS_SLAVEADDR_MASK                        (0x0000007fU)

#define PRM_VC_VAL_BYPASS_VALID_SHIFT                           (24U)
#define PRM_VC_VAL_BYPASS_VALID_MASK                            (0x01000000U)
#define PRM_VC_VAL_BYPASS_VALID_ACK                              (0U)
#define PRM_VC_VAL_BYPASS_VALID_PENDING                          (1U)

#define PRM_VC_VAL_BYPASS_OPP_CHANGE_EMIF_LVL_SHIFT             (25U)
#define PRM_VC_VAL_BYPASS_OPP_CHANGE_EMIF_LVL_MASK              (0x02000000U)
#define PRM_VC_VAL_BYPASS_OPP_CHANGE_EMIF_LVL_EN_LVL             (0U)
#define PRM_VC_VAL_BYPASS_OPP_CHANGE_EMIF_LVL_DIS_LVL            (1U)

#define PRM_VC_CORE_ERRST_SMPS_SA_ERR_CORE_SHIFT                (0U)
#define PRM_VC_CORE_ERRST_SMPS_SA_ERR_CORE_MASK                 (0x00000001U)
#define PRM_VC_CORE_ERRST_SMPS_SA_ERR_CORE_ERROR                 (1U)
#define PRM_VC_CORE_ERRST_SMPS_SA_ERR_CORE_OK                    (0U)

#define PRM_VC_CORE_ERRST_SMPS_RA_ERR_CORE_SHIFT                (1U)
#define PRM_VC_CORE_ERRST_SMPS_RA_ERR_CORE_MASK                 (0x00000002U)
#define PRM_VC_CORE_ERRST_SMPS_RA_ERR_CORE_ERROR                 (1U)
#define PRM_VC_CORE_ERRST_SMPS_RA_ERR_CORE_OK                    (0U)

#define PRM_VC_CORE_ERRST_SMPS_TIMEOUT_ERR_CORE_SHIFT           (2U)
#define PRM_VC_CORE_ERRST_SMPS_TIMEOUT_ERR_CORE_MASK            (0x00000004U)
#define PRM_VC_CORE_ERRST_SMPS_TIMEOUT_ERR_CORE_ERROR            (1U)
#define PRM_VC_CORE_ERRST_SMPS_TIMEOUT_ERR_CORE_OK               (0U)

#define PRM_VC_CORE_ERRST_VFSM_SA_ERR_CORE_SHIFT                (3U)
#define PRM_VC_CORE_ERRST_VFSM_SA_ERR_CORE_MASK                 (0x00000008U)
#define PRM_VC_CORE_ERRST_VFSM_SA_ERR_CORE_ERROR                 (1U)
#define PRM_VC_CORE_ERRST_VFSM_SA_ERR_CORE_OK                    (0U)

#define PRM_VC_CORE_ERRST_VFSM_RA_ERR_CORE_SHIFT                (4U)
#define PRM_VC_CORE_ERRST_VFSM_RA_ERR_CORE_MASK                 (0x00000010U)
#define PRM_VC_CORE_ERRST_VFSM_RA_ERR_CORE_ERROR                 (1U)
#define PRM_VC_CORE_ERRST_VFSM_RA_ERR_CORE_OK                    (0U)

#define PRM_VC_CORE_ERRST_VFSM_TIMEOUT_ERR_CORE_SHIFT           (5U)
#define PRM_VC_CORE_ERRST_VFSM_TIMEOUT_ERR_CORE_MASK            (0x00000020U)
#define PRM_VC_CORE_ERRST_VFSM_TIMEOUT_ERR_CORE_ERROR            (1U)
#define PRM_VC_CORE_ERRST_VFSM_TIMEOUT_ERR_CORE_OK               (0U)

#define PRM_VC_MM_ERRST_SMPS_SA_ERR_MM_SHIFT                    (0U)
#define PRM_VC_MM_ERRST_SMPS_SA_ERR_MM_MASK                     (0x00000001U)
#define PRM_VC_MM_ERRST_SMPS_SA_ERR_MM_ERROR                     (1U)
#define PRM_VC_MM_ERRST_SMPS_SA_ERR_MM_OK                        (0U)

#define PRM_VC_MM_ERRST_SMPS_RA_ERR_MM_SHIFT                    (1U)
#define PRM_VC_MM_ERRST_SMPS_RA_ERR_MM_MASK                     (0x00000002U)
#define PRM_VC_MM_ERRST_SMPS_RA_ERR_MM_ERROR                     (1U)
#define PRM_VC_MM_ERRST_SMPS_RA_ERR_MM_OK                        (0U)

#define PRM_VC_MM_ERRST_SMPS_TIMEOUT_ERR_MM_SHIFT               (2U)
#define PRM_VC_MM_ERRST_SMPS_TIMEOUT_ERR_MM_MASK                (0x00000004U)
#define PRM_VC_MM_ERRST_SMPS_TIMEOUT_ERR_MM_ERROR                (1U)
#define PRM_VC_MM_ERRST_SMPS_TIMEOUT_ERR_MM_OK                   (0U)

#define PRM_VC_MM_ERRST_VFSM_SA_ERR_MM_SHIFT                    (3U)
#define PRM_VC_MM_ERRST_VFSM_SA_ERR_MM_MASK                     (0x00000008U)
#define PRM_VC_MM_ERRST_VFSM_SA_ERR_MM_ERROR                     (1U)
#define PRM_VC_MM_ERRST_VFSM_SA_ERR_MM_OK                        (0U)

#define PRM_VC_MM_ERRST_VFSM_RA_ERR_MM_SHIFT                    (4U)
#define PRM_VC_MM_ERRST_VFSM_RA_ERR_MM_MASK                     (0x00000010U)
#define PRM_VC_MM_ERRST_VFSM_RA_ERR_MM_ERROR                     (1U)
#define PRM_VC_MM_ERRST_VFSM_RA_ERR_MM_OK                        (0U)

#define PRM_VC_MM_ERRST_VFSM_TIMEOUT_ERR_MM_SHIFT               (5U)
#define PRM_VC_MM_ERRST_VFSM_TIMEOUT_ERR_MM_MASK                (0x00000020U)
#define PRM_VC_MM_ERRST_VFSM_TIMEOUT_ERR_MM_ERROR                (1U)
#define PRM_VC_MM_ERRST_VFSM_TIMEOUT_ERR_MM_OK                   (0U)

#define PRM_VC_MPU_ERRST_SMPS_SA_ERR_MPU_SHIFT                  (0U)
#define PRM_VC_MPU_ERRST_SMPS_SA_ERR_MPU_MASK                   (0x00000001U)
#define PRM_VC_MPU_ERRST_SMPS_SA_ERR_MPU_ERROR                   (1U)
#define PRM_VC_MPU_ERRST_SMPS_SA_ERR_MPU_OK                      (0U)

#define PRM_VC_MPU_ERRST_SMPS_RA_ERR_MPU_SHIFT                  (1U)
#define PRM_VC_MPU_ERRST_SMPS_RA_ERR_MPU_MASK                   (0x00000002U)
#define PRM_VC_MPU_ERRST_SMPS_RA_ERR_MPU_ERROR                   (1U)
#define PRM_VC_MPU_ERRST_SMPS_RA_ERR_MPU_OK                      (0U)

#define PRM_VC_MPU_ERRST_SMPS_TIMEOUT_ERR_MPU_SHIFT             (2U)
#define PRM_VC_MPU_ERRST_SMPS_TIMEOUT_ERR_MPU_MASK              (0x00000004U)
#define PRM_VC_MPU_ERRST_SMPS_TIMEOUT_ERR_MPU_ERROR              (1U)
#define PRM_VC_MPU_ERRST_SMPS_TIMEOUT_ERR_MPU_OK                 (0U)

#define PRM_VC_MPU_ERRST_VFSM_SA_ERR_MPU_SHIFT                  (3U)
#define PRM_VC_MPU_ERRST_VFSM_SA_ERR_MPU_MASK                   (0x00000008U)
#define PRM_VC_MPU_ERRST_VFSM_SA_ERR_MPU_ERROR                   (1U)
#define PRM_VC_MPU_ERRST_VFSM_SA_ERR_MPU_OK                      (0U)

#define PRM_VC_MPU_ERRST_VFSM_RA_ERR_MPU_SHIFT                  (4U)
#define PRM_VC_MPU_ERRST_VFSM_RA_ERR_MPU_MASK                   (0x00000010U)
#define PRM_VC_MPU_ERRST_VFSM_RA_ERR_MPU_ERROR                   (1U)
#define PRM_VC_MPU_ERRST_VFSM_RA_ERR_MPU_OK                      (0U)

#define PRM_VC_MPU_ERRST_VFSM_TIMEOUT_ERR_MPU_SHIFT             (5U)
#define PRM_VC_MPU_ERRST_VFSM_TIMEOUT_ERR_MPU_MASK              (0x00000020U)
#define PRM_VC_MPU_ERRST_VFSM_TIMEOUT_ERR_MPU_ERROR              (1U)
#define PRM_VC_MPU_ERRST_VFSM_TIMEOUT_ERR_MPU_OK                 (0U)

#define PRM_VC_BYPASS_ERRST_BYPS_SA_ERR_SHIFT                   (0U)
#define PRM_VC_BYPASS_ERRST_BYPS_SA_ERR_MASK                    (0x00000001U)
#define PRM_VC_BYPASS_ERRST_BYPS_SA_ERR_ERROR                    (1U)
#define PRM_VC_BYPASS_ERRST_BYPS_SA_ERR_OK                       (0U)

#define PRM_VC_BYPASS_ERRST_BYPS_RA_ERR_SHIFT                   (1U)
#define PRM_VC_BYPASS_ERRST_BYPS_RA_ERR_MASK                    (0x00000002U)
#define PRM_VC_BYPASS_ERRST_BYPS_RA_ERR_ERROR                    (1U)
#define PRM_VC_BYPASS_ERRST_BYPS_RA_ERR_OK                       (0U)

#define PRM_VC_BYPASS_ERRST_BYPS_TIMEOUT_ERR_SHIFT              (2U)
#define PRM_VC_BYPASS_ERRST_BYPS_TIMEOUT_ERR_MASK               (0x00000004U)
#define PRM_VC_BYPASS_ERRST_BYPS_TIMEOUT_ERR_ERROR               (1U)
#define PRM_VC_BYPASS_ERRST_BYPS_TIMEOUT_ERR_OK                  (0U)

#define PRM_VC_CFG_I2C_MODE_SRMODEEN_SHIFT                      (4U)
#define PRM_VC_CFG_I2C_MODE_SRMODEEN_MASK                       (0x00000010U)
#define PRM_VC_CFG_I2C_MODE_SRMODEEN_EN_SR                       (1U)
#define PRM_VC_CFG_I2C_MODE_SRMODEEN_DIS_SR                      (0U)

#define PRM_VC_CFG_I2C_MODE_HSMCODE_SHIFT                       (0U)
#define PRM_VC_CFG_I2C_MODE_HSMCODE_MASK                        (0x00000007U)

#define PRM_VC_CFG_I2C_MODE_HSMODEEN_SHIFT                      (3U)
#define PRM_VC_CFG_I2C_MODE_HSMODEEN_MASK                       (0x00000008U)
#define PRM_VC_CFG_I2C_MODE_HSMODEEN_EN_HS                       (1U)
#define PRM_VC_CFG_I2C_MODE_HSMODEEN_DIS_HS                      (0U)

#define PRM_VC_CFG_I2C_MODE_DFILTEREN_SHIFT                     (6U)
#define PRM_VC_CFG_I2C_MODE_DFILTEREN_MASK                      (0x00000040U)
#define PRM_VC_CFG_I2C_MODE_DFILTEREN_DFILTER_EN1                (0U)
#define PRM_VC_CFG_I2C_MODE_DFILTEREN_DFILTER_EN2                (1U)

#define PRM_VC_CFG_I2C_CLK_SCLH_SHIFT                           (0U)
#define PRM_VC_CFG_I2C_CLK_SCLH_MASK                            (0x000000ffU)

#define PRM_VC_CFG_I2C_CLK_SCLL_SHIFT                           (8U)
#define PRM_VC_CFG_I2C_CLK_SCLL_MASK                            (0x0000ff00U)

#define PRM_VC_CFG_I2C_CLK_HSSCLH_SHIFT                         (16U)
#define PRM_VC_CFG_I2C_CLK_HSSCLH_MASK                          (0x00ff0000U)

#define PRM_VC_CFG_I2C_CLK_HSSCLL_SHIFT                         (24U)
#define PRM_VC_CFG_I2C_CLK_HSSCLL_MASK                          (0xff000000U)

#define PRM_SRAM_COUNT_PCHARGECNT_VALUE_SHIFT                   (0U)
#define PRM_SRAM_COUNT_PCHARGECNT_VALUE_MASK                    (0x0000003fU)

#define PRM_SRAM_COUNT_VSETUPCNT_VALUE_SHIFT                    (8U)
#define PRM_SRAM_COUNT_VSETUPCNT_VALUE_MASK                     (0x0000ff00U)

#define PRM_SRAM_COUNT_SLPCNT_VALUE_SHIFT                       (16U)
#define PRM_SRAM_COUNT_SLPCNT_VALUE_MASK                        (0x00ff0000U)

#define PRM_SRAM_COUNT_STARTUP_COUNT_SHIFT                      (24U)
#define PRM_SRAM_COUNT_STARTUP_COUNT_MASK                       (0xff000000U)

#define PRM_SRAM_WKUP_SETUP_ENABLE_RTA_SHIFT                    (0U)
#define PRM_SRAM_WKUP_SETUP_ENABLE_RTA_MASK                     (0x00000001U)
#define PRM_SRAM_WKUP_SETUP_ENABLE_RTA_RTA_ENABLED               (1U)
#define PRM_SRAM_WKUP_SETUP_ENABLE_RTA_RTA_DISABLED              (0U)

#define PRM_SLDO_CORE_SETUP_ABBOFF_ACT_SHIFT                    (1U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_ACT_MASK                     (0x00000002U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDS           (0U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDAR          (1U)

#define PRM_SLDO_CORE_SETUP_ABBOFF_SLEEP_SHIFT                  (2U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_SLEEP_MASK                   (0x00000004U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDS         (0U)
#define PRM_SLDO_CORE_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDAR        (1U)

#define PRM_SLDO_CORE_SETUP_ENABLE_RTA_SHIFT                    (0U)
#define PRM_SLDO_CORE_SETUP_ENABLE_RTA_MASK                     (0x00000001U)
#define PRM_SLDO_CORE_SETUP_ENABLE_RTA_RTA_ENABLED               (1U)
#define PRM_SLDO_CORE_SETUP_ENABLE_RTA_RTA_DISABLED              (0U)

#define PRM_SLDO_CORE_SETUP_ENFUNC1_SHIFT                       (3U)
#define PRM_SLDO_CORE_SETUP_ENFUNC1_MASK                        (0x00000008U)
#define PRM_SLDO_CORE_SETUP_ENFUNC1_SHORT_PROT_DISABLED          (0U)
#define PRM_SLDO_CORE_SETUP_ENFUNC1_SHORT_PROT_ENABLED           (1U)

#define PRM_SLDO_CORE_SETUP_ENFUNC2_SHIFT                       (4U)
#define PRM_SLDO_CORE_SETUP_ENFUNC2_MASK                        (0x00000010U)
#define PRM_SLDO_CORE_SETUP_ENFUNC2_EXT_CAP                      (0U)
#define PRM_SLDO_CORE_SETUP_ENFUNC2_NO_EXT_CAP                   (1U)

#define PRM_SLDO_CORE_SETUP_ENFUNC3_SHIFT                       (5U)
#define PRM_SLDO_CORE_SETUP_ENFUNC3_MASK                        (0x00000020U)
#define PRM_SLDO_CORE_SETUP_ENFUNC3_SUB_REGUL_DISABLED           (0U)
#define PRM_SLDO_CORE_SETUP_ENFUNC3_SUB_REGUL_ENABLED            (1U)

#define PRM_SLDO_CORE_SETUP_ENFUNC4_SHIFT                       (6U)
#define PRM_SLDO_CORE_SETUP_ENFUNC4_MASK                        (0x00000040U)
#define PRM_SLDO_CORE_SETUP_ENFUNC4_EXT_CLOCK                    (0U)
#define PRM_SLDO_CORE_SETUP_ENFUNC4_NO_EXT_CLOCK                 (1U)

#define PRM_SLDO_CORE_SETUP_ENFUNC5_SHIFT                       (7U)
#define PRM_SLDO_CORE_SETUP_ENFUNC5_MASK                        (0x00000080U)
#define PRM_SLDO_CORE_SETUP_ENFUNC5_ONE_STEP                     (0U)
#define PRM_SLDO_CORE_SETUP_ENFUNC5_TWO_STEP                     (1U)

#define PRM_SLDO_CORE_SETUP_AIPOFF_SHIFT                        (8U)
#define PRM_SLDO_CORE_SETUP_AIPOFF_MASK                         (0x00000100U)
#define PRM_SLDO_CORE_SETUP_AIPOFF_NO_OVERRIDE                   (0U)
#define PRM_SLDO_CORE_SETUP_AIPOFF_OVERRIDE                      (1U)

#define PRM_SLDO_CORE_CTRL_SRAMLDO_STATUS_SHIFT                 (8U)
#define PRM_SLDO_CORE_CTRL_SRAMLDO_STATUS_MASK                  (0x00000100U)
#define PRM_SLDO_CORE_CTRL_SRAMLDO_STATUS_ACTIVE                 (0U)
#define PRM_SLDO_CORE_CTRL_SRAMLDO_STATUS_RETENTION              (1U)

#define PRM_SLDO_CORE_CTRL_SRAM_IN_TRANSITION_SHIFT             (9U)
#define PRM_SLDO_CORE_CTRL_SRAM_IN_TRANSITION_MASK              (0x00000200U)
#define PRM_SLDO_CORE_CTRL_SRAM_IN_TRANSITION_IDLE               (0U)
#define PRM_SLDO_CORE_CTRL_SRAM_IN_TRANSITION_IN_TRANSITION      (1U)

#define PRM_SLDO_CORE_CTRL_RETMODE_ENABLE_SHIFT                 (0U)
#define PRM_SLDO_CORE_CTRL_RETMODE_ENABLE_MASK                  (0x00000001U)
#define PRM_SLDO_CORE_CTRL_RETMODE_ENABLE_DISABLED               (0U)

#define PRM_SLDO_MPU_SETUP_ABBOFF_ACT_SHIFT                     (1U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_ACT_MASK                      (0x00000002U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDS            (0U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDAR           (1U)

#define PRM_SLDO_MPU_SETUP_ABBOFF_SLEEP_SHIFT                   (2U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_SLEEP_MASK                    (0x00000004U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDS          (0U)
#define PRM_SLDO_MPU_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDAR         (1U)

#define PRM_SLDO_MPU_SETUP_ENFUNC4_SHIFT                        (6U)
#define PRM_SLDO_MPU_SETUP_ENFUNC4_MASK                         (0x00000040U)
#define PRM_SLDO_MPU_SETUP_ENFUNC4_EXT_CLOCK                     (0U)
#define PRM_SLDO_MPU_SETUP_ENFUNC4_NO_EXT_CLOCK                  (1U)

#define PRM_SLDO_MPU_SETUP_ENFUNC5_SHIFT                        (7U)
#define PRM_SLDO_MPU_SETUP_ENFUNC5_MASK                         (0x00000080U)
#define PRM_SLDO_MPU_SETUP_ENFUNC5_ONE_STEP                      (0U)
#define PRM_SLDO_MPU_SETUP_ENFUNC5_TWO_STEP                      (1U)

#define PRM_SLDO_MPU_SETUP_AIPOFF_SHIFT                         (8U)
#define PRM_SLDO_MPU_SETUP_AIPOFF_MASK                          (0x00000100U)
#define PRM_SLDO_MPU_SETUP_AIPOFF_NO_OVERRIDE                    (0U)
#define PRM_SLDO_MPU_SETUP_AIPOFF_OVERRIDE                       (1U)

#define PRM_SLDO_MPU_SETUP_ENABLE_RTA_SHIFT                     (0U)
#define PRM_SLDO_MPU_SETUP_ENABLE_RTA_MASK                      (0x00000001U)
#define PRM_SLDO_MPU_SETUP_ENABLE_RTA_RTA_ENABLED                (1U)
#define PRM_SLDO_MPU_SETUP_ENABLE_RTA_RTA_DISABLED               (0U)

#define PRM_SLDO_MPU_SETUP_ENFUNC1_SHIFT                        (3U)
#define PRM_SLDO_MPU_SETUP_ENFUNC1_MASK                         (0x00000008U)
#define PRM_SLDO_MPU_SETUP_ENFUNC1_SHORT_PROT_DISABLED           (0U)
#define PRM_SLDO_MPU_SETUP_ENFUNC1_SHORT_PROT_ENABLED            (1U)

#define PRM_SLDO_MPU_SETUP_ENFUNC2_SHIFT                        (4U)
#define PRM_SLDO_MPU_SETUP_ENFUNC2_MASK                         (0x00000010U)
#define PRM_SLDO_MPU_SETUP_ENFUNC2_EXT_CAP                       (0U)
#define PRM_SLDO_MPU_SETUP_ENFUNC2_NO_EXT_CAP                    (1U)

#define PRM_SLDO_MPU_SETUP_ENFUNC3_SHIFT                        (5U)
#define PRM_SLDO_MPU_SETUP_ENFUNC3_MASK                         (0x00000020U)
#define PRM_SLDO_MPU_SETUP_ENFUNC3_SUB_REGUL_DISABLED            (0U)
#define PRM_SLDO_MPU_SETUP_ENFUNC3_SUB_REGUL_ENABLED             (1U)

#define PRM_SLDO_MPU_CTRL_SRAMLDO_STATUS_SHIFT                  (8U)
#define PRM_SLDO_MPU_CTRL_SRAMLDO_STATUS_MASK                   (0x00000100U)
#define PRM_SLDO_MPU_CTRL_SRAMLDO_STATUS_ACTIVE                  (0U)
#define PRM_SLDO_MPU_CTRL_SRAMLDO_STATUS_RETENTION               (1U)

#define PRM_SLDO_MPU_CTRL_SRAM_IN_TRANSITION_SHIFT              (9U)
#define PRM_SLDO_MPU_CTRL_SRAM_IN_TRANSITION_MASK               (0x00000200U)
#define PRM_SLDO_MPU_CTRL_SRAM_IN_TRANSITION_IDLE                (0U)
#define PRM_SLDO_MPU_CTRL_SRAM_IN_TRANSITION_IN_TRANSITION       (1U)

#define PRM_SLDO_MPU_CTRL_RETMODE_ENABLE_SHIFT                  (0U)
#define PRM_SLDO_MPU_CTRL_RETMODE_ENABLE_MASK                   (0x00000001U)
#define PRM_SLDO_MPU_CTRL_RETMODE_ENABLE_DISABLED                (0U)
#define PRM_SLDO_MPU_CTRL_RETMODE_ENABLE_ENABLED                 (1U)

#define PRM_SLDO_GPU_SETUP_ABBOFF_ACT_SHIFT                     (1U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_ACT_MASK                      (0x00000002U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDS            (0U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDAR           (1U)

#define PRM_SLDO_GPU_SETUP_ABBOFF_SLEEP_SHIFT                   (2U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_SLEEP_MASK                    (0x00000004U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDS          (0U)
#define PRM_SLDO_GPU_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDAR         (1U)

#define PRM_SLDO_GPU_SETUP_ENFUNC4_SHIFT                        (6U)
#define PRM_SLDO_GPU_SETUP_ENFUNC4_MASK                         (0x00000040U)
#define PRM_SLDO_GPU_SETUP_ENFUNC4_EXT_CLOCK                     (0U)
#define PRM_SLDO_GPU_SETUP_ENFUNC4_NO_EXT_CLOCK                  (1U)

#define PRM_SLDO_GPU_SETUP_ENFUNC5_SHIFT                        (7U)
#define PRM_SLDO_GPU_SETUP_ENFUNC5_MASK                         (0x00000080U)
#define PRM_SLDO_GPU_SETUP_ENFUNC5_ONE_STEP                      (0U)
#define PRM_SLDO_GPU_SETUP_ENFUNC5_TWO_STEP                      (1U)

#define PRM_SLDO_GPU_SETUP_AIPOFF_SHIFT                         (8U)
#define PRM_SLDO_GPU_SETUP_AIPOFF_MASK                          (0x00000100U)
#define PRM_SLDO_GPU_SETUP_AIPOFF_NO_OVERRIDE                    (0U)
#define PRM_SLDO_GPU_SETUP_AIPOFF_OVERRIDE                       (1U)

#define PRM_SLDO_GPU_SETUP_ENABLE_RTA_SHIFT                     (0U)
#define PRM_SLDO_GPU_SETUP_ENABLE_RTA_MASK                      (0x00000001U)
#define PRM_SLDO_GPU_SETUP_ENABLE_RTA_RTA_ENABLED                (1U)
#define PRM_SLDO_GPU_SETUP_ENABLE_RTA_RTA_DISABLED               (0U)

#define PRM_SLDO_GPU_SETUP_ENFUNC1_SHIFT                        (3U)
#define PRM_SLDO_GPU_SETUP_ENFUNC1_MASK                         (0x00000008U)
#define PRM_SLDO_GPU_SETUP_ENFUNC1_SHORT_PROT_DISABLED           (0U)
#define PRM_SLDO_GPU_SETUP_ENFUNC1_SHORT_PROT_ENABLED            (1U)

#define PRM_SLDO_GPU_SETUP_ENFUNC2_SHIFT                        (4U)
#define PRM_SLDO_GPU_SETUP_ENFUNC2_MASK                         (0x00000010U)
#define PRM_SLDO_GPU_SETUP_ENFUNC2_EXT_CAP                       (0U)
#define PRM_SLDO_GPU_SETUP_ENFUNC2_NO_EXT_CAP                    (1U)

#define PRM_SLDO_GPU_SETUP_ENFUNC3_SHIFT                        (5U)
#define PRM_SLDO_GPU_SETUP_ENFUNC3_MASK                         (0x00000020U)
#define PRM_SLDO_GPU_SETUP_ENFUNC3_SUB_REGUL_DISABLED            (0U)
#define PRM_SLDO_GPU_SETUP_ENFUNC3_SUB_REGUL_ENABLED             (1U)

#define PRM_SLDO_GPU_CTRL_SRAMLDO_STATUS_SHIFT                  (8U)
#define PRM_SLDO_GPU_CTRL_SRAMLDO_STATUS_MASK                   (0x00000100U)
#define PRM_SLDO_GPU_CTRL_SRAMLDO_STATUS_ACTIVE                  (0U)
#define PRM_SLDO_GPU_CTRL_SRAMLDO_STATUS_RETENTION               (1U)

#define PRM_SLDO_GPU_CTRL_SRAM_IN_TRANSITION_SHIFT              (9U)
#define PRM_SLDO_GPU_CTRL_SRAM_IN_TRANSITION_MASK               (0x00000200U)
#define PRM_SLDO_GPU_CTRL_SRAM_IN_TRANSITION_IDLE                (0U)
#define PRM_SLDO_GPU_CTRL_SRAM_IN_TRANSITION_IN_TRANSITION       (1U)

#define PRM_SLDO_GPU_CTRL_RETMODE_ENABLE_SHIFT                  (0U)
#define PRM_SLDO_GPU_CTRL_RETMODE_ENABLE_MASK                   (0x00000001U)
#define PRM_SLDO_GPU_CTRL_RETMODE_ENABLE_DISABLED                (0U)
#define PRM_SLDO_GPU_CTRL_RETMODE_ENABLE_ENABLED                 (1U)

#define PRM_ABBLDO_MPU_SETUP_ACTIVE_FBB_SEL_SHIFT               (2U)
#define PRM_ABBLDO_MPU_SETUP_ACTIVE_FBB_SEL_MASK                (0x00000004U)
#define PRM_ABBLDO_MPU_SETUP_ACTIVE_FBB_SEL_BYPASS               (0U)
#define PRM_ABBLDO_MPU_SETUP_ACTIVE_FBB_SEL_FBB                  (1U)

#define PRM_ABBLDO_MPU_SETUP_SR2EN_SHIFT                        (0U)
#define PRM_ABBLDO_MPU_SETUP_SR2EN_MASK                         (0x00000001U)
#define PRM_ABBLDO_MPU_SETUP_SR2EN_BYPASS                        (0U)
#define PRM_ABBLDO_MPU_SETUP_SR2EN_FUNCTIONAL                    (1U)

#define PRM_ABBLDO_MPU_SETUP_SR2_WTCNT_VALUE_SHIFT              (8U)
#define PRM_ABBLDO_MPU_SETUP_SR2_WTCNT_VALUE_MASK               (0x0000ff00U)

#define PRM_ABBLDO_MPU_SETUP_NOCAP_SHIFT                        (4U)
#define PRM_ABBLDO_MPU_SETUP_NOCAP_MASK                         (0x00000010U)
#define PRM_ABBLDO_MPU_SETUP_NOCAP_CAP                           (0U)
#define PRM_ABBLDO_MPU_SETUP_NOCAP_NOCAP                         (1U)

#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_SHIFT                       (0U)
#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_MASK                        (0x00000003U)
#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_DEFAULT_NOMINAL              (0U)
#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_FASTOPP                      (1U)
#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_NOMINALOPP                   (2U)
#define PRM_ABBLDO_MPU_CTRL_OPP_SEL_SLOWOPP                      (3U)

#define PRM_ABBLDO_MPU_CTRL_OPP_CHANGE_SHIFT                    (2U)
#define PRM_ABBLDO_MPU_CTRL_OPP_CHANGE_MASK                     (0x00000004U)

#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_SHIFT                    (3U)
#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_MASK                     (0x00000018U)
#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_BYPASS                    (0U)
#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_FBB                       (2U)
#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_RESERVED                  (3U)
#define PRM_ABBLDO_MPU_CTRL_SR2_STATUS_RESERVED1                 (1U)

#define PRM_ABBLDO_MPU_CTRL_SR2_IN_TRANSITION_SHIFT             (6U)
#define PRM_ABBLDO_MPU_CTRL_SR2_IN_TRANSITION_MASK              (0x00000040U)
#define PRM_ABBLDO_MPU_CTRL_SR2_IN_TRANSITION_IDLE               (0U)
#define PRM_ABBLDO_MPU_CTRL_SR2_IN_TRANSITION_INTRANSITION       (1U)

#define PRM_ABBLDO_GPU_SETUP_SR2EN_SHIFT                        (0U)
#define PRM_ABBLDO_GPU_SETUP_SR2EN_MASK                         (0x00000001U)
#define PRM_ABBLDO_GPU_SETUP_SR2EN_BYPASS                        (0U)
#define PRM_ABBLDO_GPU_SETUP_SR2EN_FUNCTIONAL                    (1U)

#define PRM_ABBLDO_GPU_SETUP_ACTIVE_FBB_SEL_SHIFT               (2U)
#define PRM_ABBLDO_GPU_SETUP_ACTIVE_FBB_SEL_MASK                (0x00000004U)
#define PRM_ABBLDO_GPU_SETUP_ACTIVE_FBB_SEL_BYPASS               (0U)
#define PRM_ABBLDO_GPU_SETUP_ACTIVE_FBB_SEL_FBB                  (1U)

#define PRM_ABBLDO_GPU_SETUP_NOCAP_SHIFT                        (4U)
#define PRM_ABBLDO_GPU_SETUP_NOCAP_MASK                         (0x00000010U)
#define PRM_ABBLDO_GPU_SETUP_NOCAP_CAP                           (0U)
#define PRM_ABBLDO_GPU_SETUP_NOCAP_NOCAP                         (1U)

#define PRM_ABBLDO_GPU_SETUP_SR2_WTCNT_VALUE_SHIFT              (8U)
#define PRM_ABBLDO_GPU_SETUP_SR2_WTCNT_VALUE_MASK               (0x0000ff00U)

#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_SHIFT                       (0U)
#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_MASK                        (0x00000003U)
#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_DEFAULT_NOMINAL              (0U)
#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_FASTOPP                      (1U)
#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_NOMINALOPP                   (2U)
#define PRM_ABBLDO_GPU_CTRL_OPP_SEL_SLOWOPP                      (3U)

#define PRM_ABBLDO_GPU_CTRL_OPP_CHANGE_SHIFT                    (2U)
#define PRM_ABBLDO_GPU_CTRL_OPP_CHANGE_MASK                     (0x00000004U)

#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_SHIFT                    (3U)
#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_MASK                     (0x00000018U)
#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_BYPASS                    (0U)
#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_RESERVED1                 (1U)
#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_RESERVED                  (3U)
#define PRM_ABBLDO_GPU_CTRL_SR2_STATUS_FBB                       (2U)

#define PRM_ABBLDO_GPU_CTRL_SR2_IN_TRANSITION_SHIFT             (6U)
#define PRM_ABBLDO_GPU_CTRL_SR2_IN_TRANSITION_MASK              (0x00000040U)
#define PRM_ABBLDO_GPU_CTRL_SR2_IN_TRANSITION_IDLE               (0U)
#define PRM_ABBLDO_GPU_CTRL_SR2_IN_TRANSITION_INTRANSITION       (1U)

#define PRM_BANDGAP_SETUP_STARTUP_COUNT_SHIFT                   (0U)
#define PRM_BANDGAP_SETUP_STARTUP_COUNT_MASK                    (0x000000ffU)

#define PRM_DEVICE_OFF_CTRL_DEVICE_OFF_ENABLE_SHIFT             (0U)
#define PRM_DEVICE_OFF_CTRL_DEVICE_OFF_ENABLE_MASK              (0x00000001U)
#define PRM_DEVICE_OFF_CTRL_DEVICE_OFF_ENABLE_DISABLED           (0U)
#define PRM_DEVICE_OFF_CTRL_DEVICE_OFF_ENABLE_ENABLED            (1U)

#define PRM_DEVICE_OFF_CTRL_EMIF1_OFFWKUP_DISABLE_SHIFT         (8U)
#define PRM_DEVICE_OFF_CTRL_EMIF1_OFFWKUP_DISABLE_MASK          (0x00000100U)
#define PRM_DEVICE_OFF_CTRL_EMIF1_OFFWKUP_DISABLE_DISABLED       (1U)
#define PRM_DEVICE_OFF_CTRL_EMIF1_OFFWKUP_DISABLE_ENABLED        (0U)

#define PRM_DEVICE_OFF_CTRL_EMIF2_OFFWKUP_DISABLE_SHIFT         (9U)
#define PRM_DEVICE_OFF_CTRL_EMIF2_OFFWKUP_DISABLE_MASK          (0x00000200U)
#define PRM_DEVICE_OFF_CTRL_EMIF2_OFFWKUP_DISABLE_DISABLED       (1U)
#define PRM_DEVICE_OFF_CTRL_EMIF2_OFFWKUP_DISABLE_ENABLED        (0U)

#define PRM_PHASE1_CNDP_PHASE1_CNDP_SHIFT                       (0U)
#define PRM_PHASE1_CNDP_PHASE1_CNDP_MASK                        (0xffffffffU)

#define PRM_PHASE2A_CNDP_PHASE2A_CNDP_SHIFT                     (0U)
#define PRM_PHASE2A_CNDP_PHASE2A_CNDP_MASK                      (0xffffffffU)

#define PRM_PHASE2B_CNDP_PHASE2B_CNDP_SHIFT                     (0U)
#define PRM_PHASE2B_CNDP_PHASE2B_CNDP_MASK                      (0xffffffffU)

#define PRM_MODEM_IF_CTRL_MODEM_WAKE_IRQ_SHIFT                  (8U)
#define PRM_MODEM_IF_CTRL_MODEM_WAKE_IRQ_MASK                   (0x00000100U)
#define PRM_MODEM_IF_CTRL_MODEM_WAKE_IRQ_ACTIVE                  (1U)
#define PRM_MODEM_IF_CTRL_MODEM_WAKE_IRQ_INACTIVE                (0U)

#define PRM_MODEM_IF_CTRL_MODEM_SHUTDOWN_IRQ_SHIFT              (9U)
#define PRM_MODEM_IF_CTRL_MODEM_SHUTDOWN_IRQ_MASK               (0x00000200U)
#define PRM_MODEM_IF_CTRL_MODEM_SHUTDOWN_IRQ_ACTIVE              (1U)
#define PRM_MODEM_IF_CTRL_MODEM_SHUTDOWN_IRQ_INACTIVE            (0U)

#define PRM_VOLTST_MPU_VOLTSTATEST_SHIFT                        (0U)
#define PRM_VOLTST_MPU_VOLTSTATEST_MASK                         (0x00000003U)
#define PRM_VOLTST_MPU_VOLTSTATEST_OFF                           (0U)
#define PRM_VOLTST_MPU_VOLTSTATEST_RET                           (1U)
#define PRM_VOLTST_MPU_VOLTSTATEST_SLEEP                         (2U)
#define PRM_VOLTST_MPU_VOLTSTATEST_ON                            (3U)

#define PRM_VOLTST_MPU_INTRANSITION_SHIFT                       (20U)
#define PRM_VOLTST_MPU_INTRANSITION_MASK                        (0x00100000U)
#define PRM_VOLTST_MPU_INTRANSITION_NO                           (0U)
#define PRM_VOLTST_MPU_INTRANSITION_ONGOING                      (1U)

#define PRM_VOLTST_MM_VOLTSTATEST_SHIFT                         (0U)
#define PRM_VOLTST_MM_VOLTSTATEST_MASK                          (0x00000003U)
#define PRM_VOLTST_MM_VOLTSTATEST_OFF                            (0U)
#define PRM_VOLTST_MM_VOLTSTATEST_RET                            (1U)
#define PRM_VOLTST_MM_VOLTSTATEST_SLEEP                          (2U)
#define PRM_VOLTST_MM_VOLTSTATEST_ON                             (3U)

#define PRM_VOLTST_MM_INTRANSITION_SHIFT                        (20U)
#define PRM_VOLTST_MM_INTRANSITION_MASK                         (0x00100000U)
#define PRM_VOLTST_MM_INTRANSITION_NO                            (0U)
#define PRM_VOLTST_MM_INTRANSITION_ONGOING                       (1U)

#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_ACT_SHIFT                  (1U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_ACT_MASK                   (0x00000002U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDS         (0U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDAR        (1U)

#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_SLEEP_SHIFT                (2U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_SLEEP_MASK                 (0x00000004U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDS       (0U)
#define PRM_SLDO_DSPEVE_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDAR      (1U)

#define PRM_SLDO_DSPEVE_SETUP_ENFUNC4_SHIFT                     (6U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC4_MASK                      (0x00000040U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC4_EXT_CLOCK                  (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC4_NO_EXT_CLOCK               (1U)

#define PRM_SLDO_DSPEVE_SETUP_ENFUNC5_SHIFT                     (7U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC5_MASK                      (0x00000080U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC5_ONE_STEP                   (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC5_TWO_STEP                   (1U)

#define PRM_SLDO_DSPEVE_SETUP_AIPOFF_SHIFT                      (8U)
#define PRM_SLDO_DSPEVE_SETUP_AIPOFF_MASK                       (0x00000100U)
#define PRM_SLDO_DSPEVE_SETUP_AIPOFF_NO_OVERRIDE                 (0U)
#define PRM_SLDO_DSPEVE_SETUP_AIPOFF_OVERRIDE                    (1U)

#define PRM_SLDO_DSPEVE_SETUP_ENABLE_RTA_SHIFT                  (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENABLE_RTA_MASK                   (0x00000001U)
#define PRM_SLDO_DSPEVE_SETUP_ENABLE_RTA_RTA_ENABLED             (1U)
#define PRM_SLDO_DSPEVE_SETUP_ENABLE_RTA_RTA_DISABLED            (0U)

#define PRM_SLDO_DSPEVE_SETUP_ENFUNC1_SHIFT                     (3U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC1_MASK                      (0x00000008U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC1_SHORT_PROT_DISABLED        (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC1_SHORT_PROT_ENABLED         (1U)

#define PRM_SLDO_DSPEVE_SETUP_ENFUNC2_SHIFT                     (4U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC2_MASK                      (0x00000010U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC2_EXT_CAP                    (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC2_NO_EXT_CAP                 (1U)

#define PRM_SLDO_DSPEVE_SETUP_ENFUNC3_SHIFT                     (5U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC3_MASK                      (0x00000020U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC3_SUB_REGUL_DISABLED         (0U)
#define PRM_SLDO_DSPEVE_SETUP_ENFUNC3_SUB_REGUL_ENABLED          (1U)

#define PRM_SLDO_IVA_SETUP_ABBOFF_ACT_SHIFT                     (1U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_ACT_MASK                      (0x00000002U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDS            (0U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_ACT_SRAMNW_ACT_VDDAR           (1U)

#define PRM_SLDO_IVA_SETUP_ABBOFF_SLEEP_SHIFT                   (2U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_SLEEP_MASK                    (0x00000004U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDS          (0U)
#define PRM_SLDO_IVA_SETUP_ABBOFF_SLEEP_SRAMNW_SLP_VDDAR         (1U)

#define PRM_SLDO_IVA_SETUP_ENFUNC4_SHIFT                        (6U)
#define PRM_SLDO_IVA_SETUP_ENFUNC4_MASK                         (0x00000040U)
#define PRM_SLDO_IVA_SETUP_ENFUNC4_EXT_CLOCK                     (0U)
#define PRM_SLDO_IVA_SETUP_ENFUNC4_NO_EXT_CLOCK                  (1U)

#define PRM_SLDO_IVA_SETUP_ENFUNC5_SHIFT                        (7U)
#define PRM_SLDO_IVA_SETUP_ENFUNC5_MASK                         (0x00000080U)
#define PRM_SLDO_IVA_SETUP_ENFUNC5_ONE_STEP                      (0U)
#define PRM_SLDO_IVA_SETUP_ENFUNC5_TWO_STEP                      (1U)

#define PRM_SLDO_IVA_SETUP_AIPOFF_SHIFT                         (8U)
#define PRM_SLDO_IVA_SETUP_AIPOFF_MASK                          (0x00000100U)
#define PRM_SLDO_IVA_SETUP_AIPOFF_NO_OVERRIDE                    (0U)
#define PRM_SLDO_IVA_SETUP_AIPOFF_OVERRIDE                       (1U)

#define PRM_SLDO_IVA_SETUP_ENABLE_RTA_SHIFT                     (0U)
#define PRM_SLDO_IVA_SETUP_ENABLE_RTA_MASK                      (0x00000001U)
#define PRM_SLDO_IVA_SETUP_ENABLE_RTA_RTA_ENABLED                (1U)
#define PRM_SLDO_IVA_SETUP_ENABLE_RTA_RTA_DISABLED               (0U)

#define PRM_SLDO_IVA_SETUP_ENFUNC1_SHIFT                        (3U)
#define PRM_SLDO_IVA_SETUP_ENFUNC1_MASK                         (0x00000008U)
#define PRM_SLDO_IVA_SETUP_ENFUNC1_SHORT_PROT_DISABLED           (0U)
#define PRM_SLDO_IVA_SETUP_ENFUNC1_SHORT_PROT_ENABLED            (1U)

#define PRM_SLDO_IVA_SETUP_ENFUNC2_SHIFT                        (4U)
#define PRM_SLDO_IVA_SETUP_ENFUNC2_MASK                         (0x00000010U)
#define PRM_SLDO_IVA_SETUP_ENFUNC2_EXT_CAP                       (0U)
#define PRM_SLDO_IVA_SETUP_ENFUNC2_NO_EXT_CAP                    (1U)

#define PRM_SLDO_IVA_SETUP_ENFUNC3_SHIFT                        (5U)
#define PRM_SLDO_IVA_SETUP_ENFUNC3_MASK                         (0x00000020U)
#define PRM_SLDO_IVA_SETUP_ENFUNC3_SUB_REGUL_DISABLED            (0U)
#define PRM_SLDO_IVA_SETUP_ENFUNC3_SUB_REGUL_ENABLED             (1U)

#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_SHIFT                    (0U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_MASK                     (0x00000003U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_DEFAULT_NOMINAL           (0U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_FASTOPP                   (1U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_NOMINALOPP                (2U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_SLOWOPP                   (3U)

#define PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE_SHIFT                 (2U)
#define PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE_MASK                  (0x00000004U)

#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_SHIFT                 (3U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_MASK                  (0x00000018U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_BYPASS                 (0U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_RESERVED1              (1U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_RESERVED               (3U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_STATUS_FBB                    (2U)

#define PRM_ABBLDO_DSPEVE_CTRL_SR2_IN_TRANSITION_SHIFT          (6U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_IN_TRANSITION_MASK           (0x00000040U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_IN_TRANSITION_IDLE            (0U)
#define PRM_ABBLDO_DSPEVE_CTRL_SR2_IN_TRANSITION_INTRANSITION    (1U)

#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_SHIFT                       (0U)
#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_MASK                        (0x00000003U)
#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_DEFAULT_NOMINAL              (0U)
#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_FASTOPP                      (1U)
#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_NOMINALOPP                   (2U)
#define PRM_ABBLDO_IVA_CTRL_OPP_SEL_SLOWOPP                      (3U)

#define PRM_ABBLDO_IVA_CTRL_OPP_CHANGE_SHIFT                    (2U)
#define PRM_ABBLDO_IVA_CTRL_OPP_CHANGE_MASK                     (0x00000004U)

#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_SHIFT                    (3U)
#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_MASK                     (0x00000018U)
#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_BYPASS                    (0U)
#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_RESERVED1                 (1U)
#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_RESERVED                  (3U)
#define PRM_ABBLDO_IVA_CTRL_SR2_STATUS_FBB                       (2U)

#define PRM_ABBLDO_IVA_CTRL_SR2_IN_TRANSITION_SHIFT             (6U)
#define PRM_ABBLDO_IVA_CTRL_SR2_IN_TRANSITION_MASK              (0x00000040U)
#define PRM_ABBLDO_IVA_CTRL_SR2_IN_TRANSITION_IDLE               (0U)
#define PRM_ABBLDO_IVA_CTRL_SR2_IN_TRANSITION_INTRANSITION       (1U)

#define PRM_SLDO_DSPEVE_CTRL_SRAMLDO_STATUS_SHIFT               (8U)
#define PRM_SLDO_DSPEVE_CTRL_SRAMLDO_STATUS_MASK                (0x00000100U)
#define PRM_SLDO_DSPEVE_CTRL_SRAMLDO_STATUS_ACTIVE               (0U)
#define PRM_SLDO_DSPEVE_CTRL_SRAMLDO_STATUS_RETENTION            (1U)

#define PRM_SLDO_DSPEVE_CTRL_SRAM_IN_TRANSITION_SHIFT           (9U)
#define PRM_SLDO_DSPEVE_CTRL_SRAM_IN_TRANSITION_MASK            (0x00000200U)
#define PRM_SLDO_DSPEVE_CTRL_SRAM_IN_TRANSITION_IDLE             (0U)
#define PRM_SLDO_DSPEVE_CTRL_SRAM_IN_TRANSITION_IN_TRANSITION    (1U)

#define PRM_SLDO_DSPEVE_CTRL_RETMODE_ENABLE_SHIFT               (0U)
#define PRM_SLDO_DSPEVE_CTRL_RETMODE_ENABLE_MASK                (0x00000001U)
#define PRM_SLDO_DSPEVE_CTRL_RETMODE_ENABLE_DISABLED             (0U)
#define PRM_SLDO_DSPEVE_CTRL_RETMODE_ENABLE_ENABLED              (1U)

#define PRM_SLDO_IVA_CTRL_SRAMLDO_STATUS_SHIFT                  (8U)
#define PRM_SLDO_IVA_CTRL_SRAMLDO_STATUS_MASK                   (0x00000100U)
#define PRM_SLDO_IVA_CTRL_SRAMLDO_STATUS_ACTIVE                  (0U)
#define PRM_SLDO_IVA_CTRL_SRAMLDO_STATUS_RETENTION               (1U)

#define PRM_SLDO_IVA_CTRL_SRAM_IN_TRANSITION_SHIFT              (9U)
#define PRM_SLDO_IVA_CTRL_SRAM_IN_TRANSITION_MASK               (0x00000200U)
#define PRM_SLDO_IVA_CTRL_SRAM_IN_TRANSITION_IDLE                (0U)
#define PRM_SLDO_IVA_CTRL_SRAM_IN_TRANSITION_IN_TRANSITION       (1U)

#define PRM_SLDO_IVA_CTRL_RETMODE_ENABLE_SHIFT                  (0U)
#define PRM_SLDO_IVA_CTRL_RETMODE_ENABLE_MASK                   (0x00000001U)
#define PRM_SLDO_IVA_CTRL_RETMODE_ENABLE_DISABLED                (0U)
#define PRM_SLDO_IVA_CTRL_RETMODE_ENABLE_ENABLED                 (1U)

#define PRM_ABBLDO_DSPEVE_SETUP_SR2EN_SHIFT                     (0U)
#define PRM_ABBLDO_DSPEVE_SETUP_SR2EN_MASK                      (0x00000001U)
#define PRM_ABBLDO_DSPEVE_SETUP_SR2EN_BYPASS                     (0U)
#define PRM_ABBLDO_DSPEVE_SETUP_SR2EN_FUNCTIONAL                 (1U)

#define PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_SHIFT            (2U)
#define PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_MASK             (0x00000004U)
#define PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_BYPASS            (0U)
#define PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_FBB               (1U)

#define PRM_ABBLDO_DSPEVE_SETUP_NOCAP_SHIFT                     (4U)
#define PRM_ABBLDO_DSPEVE_SETUP_NOCAP_MASK                      (0x00000010U)
#define PRM_ABBLDO_DSPEVE_SETUP_NOCAP_CAP                        (0U)
#define PRM_ABBLDO_DSPEVE_SETUP_NOCAP_NOCAP                      (1U)

#define PRM_ABBLDO_DSPEVE_SETUP_SR2_WTCNT_VALUE_SHIFT           (8U)
#define PRM_ABBLDO_DSPEVE_SETUP_SR2_WTCNT_VALUE_MASK            (0x0000ff00U)

#define PRM_ABBLDO_IVA_SETUP_SR2EN_SHIFT                        (0U)
#define PRM_ABBLDO_IVA_SETUP_SR2EN_MASK                         (0x00000001U)
#define PRM_ABBLDO_IVA_SETUP_SR2EN_BYPASS                        (0U)
#define PRM_ABBLDO_IVA_SETUP_SR2EN_FUNCTIONAL                    (1U)

#define PRM_ABBLDO_IVA_SETUP_ACTIVE_FBB_SEL_SHIFT               (2U)
#define PRM_ABBLDO_IVA_SETUP_ACTIVE_FBB_SEL_MASK                (0x00000004U)
#define PRM_ABBLDO_IVA_SETUP_ACTIVE_FBB_SEL_BYPASS               (0U)
#define PRM_ABBLDO_IVA_SETUP_ACTIVE_FBB_SEL_FBB                  (1U)

#define PRM_ABBLDO_IVA_SETUP_NOCAP_SHIFT                        (4U)
#define PRM_ABBLDO_IVA_SETUP_NOCAP_MASK                         (0x00000010U)
#define PRM_ABBLDO_IVA_SETUP_NOCAP_CAP                           (0U)
#define PRM_ABBLDO_IVA_SETUP_NOCAP_NOCAP                         (1U)

#define PRM_ABBLDO_IVA_SETUP_SR2_WTCNT_VALUE_SHIFT              (8U)
#define PRM_ABBLDO_IVA_SETUP_SR2_WTCNT_VALUE_MASK               (0x0000ff00U)

#ifdef __cplusplus
}
#endif

#endif /* HW_DEVICE_PRM_H_ */

