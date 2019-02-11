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
 *  \file   hw_ctrl_core_sec.h
 *
 *  \brief  Register-level header file for CTRL_CORE_SEC
 *
**/

#ifndef HW_CTRL_CORE_SEC_H_
#define HW_CTRL_CORE_SEC_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CTRL_CORE_SEC_SECURITY_MASTER_REG                           (0x0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_0_LOWER                          (0x10U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_0_UPPER                          (0x14U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_0                              (0x18U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_1_LOWER                          (0x20U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_1_UPPER                          (0x24U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_1                              (0x28U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_5_LOWER                          (0x30U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_5_UPPER                          (0x34U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_5                              (0x38U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_LOWER                        (0x40U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_UPPER                        (0x44U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_0                            (0x48U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_LOWER                          (0x50U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_UPPER                          (0x54U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS                              (0x58U)
#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_LOWER                        (0x60U)
#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_UPPER                        (0x64U)
#define CTRL_CORE_SEC_L4_PER_2_MEMBERS_0                            (0x68U)
#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_LOWER                        (0x70U)
#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_UPPER                        (0x74U)
#define CTRL_CORE_SEC_L4_PER_3_MEMBER_0                             (0x78U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_LOWER                         (0x80U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_UPPER                         (0x84U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_0                             (0x88U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_LOWER                         (0x90U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_UPPER                         (0x94U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_1                             (0x98U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_LOWER                         (0xa0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_UPPER                         (0xa4U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_3                             (0xa8U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_LOWER                         (0xb0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_UPPER                         (0xb4U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_4                             (0xb8U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_0                 (0x138U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_1                 (0x13cU)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_2                 (0x140U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_3                 (0x144U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_4                 (0x148U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_0                        (0x160U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_1                        (0x164U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_2                        (0x168U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_3                        (0x16cU)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_4                        (0x170U)
#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM                           (0x188U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS                            (0x1a8U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VIP                                (0x1b8U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VPE                                (0x1bcU)
#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW                            (0x1c4U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC                          (0x1d8U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSS                                (0x1dcU)
#define CTRL_CORE_SEC_MEM_DFT_RW_IPU                                (0x1e4U)
#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D                               (0x1f4U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSP                                (0x1f8U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1                               (0x1fcU)
#define CTRL_CORE_SEC_SMA_SW_2                                      (0x204U)
#define CTRL_CORE_SEC_SMA_SW_3                                      (0x208U)
#define CTRL_CORE_SEC_SMA_SW_4                                      (0x20cU)
#define CTRL_CORE_SEC_SMA_SW_5                                      (0x210U)
#define CTRL_CORE_SEC_SMA_SW_6                                      (0x214U)
#define CTRL_CORE_SEC_SMA_SW_7                                      (0x218U)
#define CTRL_CORE_SEC_SMA_SW_8                                      (0x21cU)
#define CTRL_CORE_SEC_SMA_SW_9                                      (0x220U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0                     (0x248U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1                     (0x24cU)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2                     (0x250U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3                     (0x254U)
#define CTRL_CORE_SEC_EMIF_MPU_ROUTING                              (0x258U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL                           (0x25cU)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1                          (0x260U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2                          (0x264U)
#define CTRL_CORE_SEC_SMA_SW_10                                     (0x268U)
#define CTRL_CORE_SEC_SMA_SW_11                                     (0x26cU)
#define CTRL_CORE_SEC_SMA_SW_12                                     (0x270U)
#define CTRL_CORE_SEC_SMA_SW_13                                     (0x274U)
#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR                    (0x278U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL                                (0x27cU)
#define CTRL_CORE_SEC_SD_DAC_TRIM_VALUE                             (0x280U)
#define CTRL_CORE_SEC_ADC_ERROR_OFFSET                              (0x284U)
#define CTRL_CORE_SEC_IPU_WAKEUP                                    (0x288U)
#define CTRL_CORE_SEC_ISS_EFUSE                                     (0x28cU)
#define CTRL_CORE_SEC_SMA_SW_14                                     (0x290U)
#define CTRL_CORE_SEC_SMA_SW_15                                     (0x294U)
#define CTRL_CORE_SEC_SMA_SW_16                                     (0x298U)
#define CTRL_CORE_SEC_SMA_SW_17                                     (0x29cU)
#define CTRL_CORE_SEC_ROM_CPU0_BRANCH                               (0x2a0U)
#define CTRL_CORE_SEC_ROM_CPU1_BRANCH                               (0x2a4U)
#define CTRL_CORE_SEC_ROM_AUXBOOT0                                  (0x2a8U)
#define CTRL_CORE_SEC_ROM_AUXBOOT1                                  (0x2acU)
#define CTRL_CORE_SEC_SMA_SW_18                                     (0x2b0U)
#define CTRL_CORE_SEC_SMA_SW_19                                     (0x2b4U)
#define CTRL_CORE_SEC_SMA_SW_20                                     (0x2b8U)
#define CTRL_CORE_SEC_SMA_SW_21                                     (0x2bcU)
#define CTRL_CORE_SEC_SMA_SW_22                                     (0x2c0U)
#define CTRL_CORE_SEC_SMA_SW_23                                     (0x2c4U)
#define CTRL_CORE_SEC_SMA_SW_24                                     (0x2c8U)
#define CTRL_CORE_SEC_SMA_SW_25                                     (0x2ccU)
#define CTRL_CORE_SEC_SMA_SW_26                                     (0x2d0U)
#define CTRL_CORE_SEC_SMA_SW_27                                     (0x2d4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_LOCK_SHIFT                                    (31U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_LOCK_MASK                                     (0x80000000U)

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_MPU_EN_SHIFT                                  (12U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_MPU_EN_MASK                                   (0x00001000U)

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_L3_ROM_VISIBLE_SHIFT                          (8U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_L3_ROM_VISIBLE_MASK                           (0x00000100U)

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_IPU_1_SECURE_ENABLE_SHIFT                     (4U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_IPU_1_SECURE_ENABLE_MASK                      (0x00000010U)

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_DSP_1_SECURE_TEST_ENABLE_SHIFT                (1U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_DSP_1_SECURE_TEST_ENABLE_MASK                 (0x00000002U)

#define CTRL_CORE_SEC_SECURITY_MASTER_REG_DSP_1_SECURE_ENABLE_SHIFT                     (0U)
#define CTRL_CORE_SEC_SECURITY_MASTER_REG_DSP_1_SECURE_ENABLE_MASK                      (0x00000001U)

#define CTRL_CORE_SEC_L4_CFG_ROLES_0_LOWER_SHIFT                                        (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_0_LOWER_MASK                                         (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_ROLES_0_UPPER_1_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_0_UPPER_1_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_0_DISABLE_SHIFT                                    (31U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_0_DISABLE_MASK                                     (0x80000000U)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_0_SHIFT                                            (0U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_0_MASK                                             (0x0000ffffU)

#define CTRL_CORE_SEC_L4_CFG_ROLES_1_LOWER_0_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_1_LOWER_0_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_ROLES_1_UPPER_SHIFT                                        (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_1_UPPER_MASK                                         (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_1_DISABLE_SHIFT                                    (31U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_1_DISABLE_MASK                                     (0x80000000U)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_1_SHIFT                                            (0U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_1_MASK                                             (0x0000ffffU)

#define CTRL_CORE_SEC_L4_CFG_ROLES_5_LOWER_0_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_5_LOWER_0_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_ROLES_5_UPPER_1_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_CFG_ROLES_5_UPPER_1_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_5_DISABLE_SHIFT                                    (31U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_5_DISABLE_MASK                                     (0x80000000U)

#define CTRL_CORE_SEC_L4_CFG_MEMBERS_5_SHIFT                                            (0U)
#define CTRL_CORE_SEC_L4_CFG_MEMBERS_5_MASK                                             (0x0000ffffU)

#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_LOWER_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_LOWER_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_UPPER_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_0_UPPER_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_0_DISABLE_SHIFT                                  (31U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_0_DISABLE_MASK                                   (0x80000000U)

#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_0_SHIFT                                          (0U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_0_MASK                                           (0x0000ffffU)

#define CTRL_CORE_SEC_L4_PER_1_ROLES_LOWER_0_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_LOWER_0_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_1_ROLES_UPPER_SHIFT                                        (0U)
#define CTRL_CORE_SEC_L4_PER_1_ROLES_UPPER_MASK                                         (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_DISABLE_SHIFT                                    (31U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_DISABLE_MASK                                     (0x80000000U)

#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_SHIFT                                            (0U)
#define CTRL_CORE_SEC_L4_PER_1_MEMBERS_MASK                                             (0x0000ffffU)

#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_LOWER_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_LOWER_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_UPPER_1_SHIFT                                    (0U)
#define CTRL_CORE_SEC_L4_PER_2_ROLES_0_UPPER_1_MASK                                     (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_2_MEMBERS_0_DISABLE_SHIFT                                  (31U)
#define CTRL_CORE_SEC_L4_PER_2_MEMBERS_0_DISABLE_MASK                                   (0x80000000U)

#define CTRL_CORE_SEC_L4_PER_2_MEMBERS_0_SHIFT                                          (0U)
#define CTRL_CORE_SEC_L4_PER_2_MEMBERS_0_MASK                                           (0x0000ffffU)

#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_LOWER_SHIFT                                      (0U)
#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_LOWER_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_UPPER_1_SHIFT                                    (0U)
#define CTRL_CORE_SEC_L4_PER_3_ROLES_0_UPPER_1_MASK                                     (0xffffffffU)

#define CTRL_CORE_SEC_L4_PER_3_MEMBER_0_DISABLE_SHIFT                                   (31U)
#define CTRL_CORE_SEC_L4_PER_3_MEMBER_0_DISABLE_MASK                                    (0x80000000U)

#define CTRL_CORE_SEC_L4_PER_3_MEMBER_0_MEMBERS_SHIFT                                   (0U)
#define CTRL_CORE_SEC_L4_PER_3_MEMBER_0_MEMBERS_MASK                                    (0x0000ffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_LOWER_SHIFT                                       (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_LOWER_MASK                                        (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_UPPER_1_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_0_UPPER_1_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_0_DISABLE_SHIFT                                   (31U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_0_DISABLE_MASK                                    (0x80000000U)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_0_SHIFT                                           (0U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_0_MASK                                            (0x0000ffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_LOWER_0_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_LOWER_0_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_UPPER_SHIFT                                       (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_1_UPPER_MASK                                        (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_1_DISABLE_SHIFT                                   (31U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_1_DISABLE_MASK                                    (0x80000000U)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_1_SHIFT                                           (0U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_1_MASK                                            (0x0000ffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_LOWER_0_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_LOWER_0_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_UPPER_1_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_3_UPPER_1_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_3_DISABLE_SHIFT                                   (31U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_3_DISABLE_MASK                                    (0x80000000U)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_3_SHIFT                                           (0U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_3_MASK                                            (0x0000ffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_LOWER_0_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_LOWER_0_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_UPPER_1_SHIFT                                     (0U)
#define CTRL_CORE_SEC_L4_WKUP_ROLES_4_UPPER_1_MASK                                      (0xffffffffU)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_4_DISABLE_SHIFT                                   (31U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_4_DISABLE_MASK                                    (0x80000000U)

#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_4_SHIFT                                           (0U)
#define CTRL_CORE_SEC_L4_WKUP_MEMBERS_4_MASK                                            (0x0000ffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_SHIFT                               (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_MASK                                (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_SHIFT                               (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_MASK                                (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_SHIFT                               (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_MASK                                (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_SHIFT                               (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_MASK                                (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_SHIFT                               (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_MASK                                (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_0_SHIFT                                      (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_0_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_1_SHIFT                                      (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_1_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_2_SHIFT                                      (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_2_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_3_SHIFT                                      (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_3_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_4_SHIFT                                      (0U)
#define CTRL_CORE_SEC_STD_FUSE_OPP_VDD_LVT_4_MASK                                       (0xffffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_MUX_SHIFT                                     (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_MUX_MASK                                      (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_MUX_OCP                                        (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_MUX_EFUSE                                      (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_BRGLNT_SHIFT                                  (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_OCMC_RAM_BRGLNT_MASK                                   (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_MUX_SHIFT                                      (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_MUX_MASK                                       (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_MUX_OCP                                         (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_MUX_EFUSE                                       (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_BRGLNT_SHIFT                                   (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DEBUGSS_BRGLNT_MASK                                    (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_MUX_SHIFT                                          (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_MUX_MASK                                           (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_MUX_OCP                                             (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_MUX_EFUSE                                           (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_BRGLNT_SHIFT                                       (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VIP_BRGLNT_MASK                                        (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_MUX_SHIFT                                          (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_MUX_MASK                                           (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_MUX_OCP                                             (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_MUX_EFUSE                                           (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_BRGLNT_SHIFT                                       (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_VPE_BRGLNT_MASK                                        (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_MUX_SHIFT                                      (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_MUX_MASK                                       (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_MUX_OCP                                         (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_MUX_EFUSE                                       (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_BRGLNT_SHIFT                                   (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_GMAC_SW_BRGLNT_MASK                                    (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_MUX_SHIFT                                    (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_MUX_MASK                                     (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_MUX_OCP                                       (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_MUX_EFUSE                                     (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_BRGLNT_SHIFT                                 (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EDMA_TPCC_BRGLNT_MASK                                  (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_MUX_SHIFT                                          (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_MUX_MASK                                           (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_MUX_OCP                                             (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_MUX_EFUSE                                           (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_BRGLNT_SHIFT                                       (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSS_BRGLNT_MASK                                        (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_MUX_SHIFT                                          (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_MUX_MASK                                           (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_MUX_OCP                                             (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_MUX_EFUSE                                           (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_BRGLNT_SHIFT                                       (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_IPU_BRGLNT_MASK                                        (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_MUX_SHIFT                                         (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_MUX_MASK                                          (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_MUX_OCP                                            (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_MUX_EFUSE                                          (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_BRGLNT_SHIFT                                      (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_BB2D_BRGLNT_MASK                                       (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_MUX_SHIFT                                          (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_MUX_MASK                                           (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_MUX_OCP                                             (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_MUX_EFUSE                                           (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_BRGLNT_SHIFT                                       (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_DSP_BRGLNT_MASK                                        (0x7fffffffU)

#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_MUX_EVE_SHIFT                                     (31U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_MUX_EVE_MASK                                      (0x80000000U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_MUX_EVE_OCP                                        (1U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_MUX_EVE_EFUSE                                      (0U)

#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_BRGLNT_SHIFT                                      (0U)
#define CTRL_CORE_SEC_MEM_DFT_RW_EVE1_BRGLNT_MASK                                       (0x0000ffffU)

#define CTRL_CORE_SEC_SMA_SW_2_SHIFT                                                    (0U)
#define CTRL_CORE_SEC_SMA_SW_2_MASK                                                     (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_3_SHIFT                                                    (2U)
#define CTRL_CORE_SEC_SMA_SW_3_MASK                                                     (0xfffffffcU)

#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_EXP7_LOCK_SHIFT                               (31U)
#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_EXP7_LOCK_MASK                                (0x80000000U)

#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_DSP2_EDMA_SHIFT                               (3U)
#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_DSP2_EDMA_MASK                                (0x00000038U)

#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_DSP1_EDMA_SHIFT                               (0U)
#define CTRL_CORE_SEC_SMA_SW_4_MREQDOMAIN_DSP1_EDMA_MASK                                (0x00000007U)

#define CTRL_CORE_SEC_SMA_SW_5_TSHUT_OVERRIDE_SHIFT                                     (0U)
#define CTRL_CORE_SEC_SMA_SW_5_TSHUT_OVERRIDE_MASK                                      (0x00000001U)

#define CTRL_CORE_SEC_SMA_SW_6_PLLEN_CONTROL_SHIFT                                      (24U)
#define CTRL_CORE_SEC_SMA_SW_6_PLLEN_CONTROL_MASK                                       (0x1f000000U)

#define CTRL_CORE_SEC_SMA_SW_6_RMII_CLK_SETTING_SHIFT                                   (8U)
#define CTRL_CORE_SEC_SMA_SW_6_RMII_CLK_SETTING_MASK                                    (0x00000100U)

#define CTRL_CORE_SEC_SMA_SW_6_MUXSEL_32K_CLKIN_SHIFT                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_6_MUXSEL_32K_CLKIN_MASK                                    (0x00000001U)

#define CTRL_CORE_SEC_SMA_SW_7_MMU1_ABORT_ENABLE_SHIFT                                  (16U)
#define CTRL_CORE_SEC_SMA_SW_7_MMU1_ABORT_ENABLE_MASK                                   (0x00010000U)

#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC0_RD_MMU_ROUTE_ENABLE_SHIFT                       (11U)
#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC0_RD_MMU_ROUTE_ENABLE_MASK                        (0x00000800U)

#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC1_RD_MMU_ROUTE_ENABLE_SHIFT                       (10U)
#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC1_RD_MMU_ROUTE_ENABLE_MASK                        (0x00000400U)

#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC0_WR_MMU_ROUTE_ENABLE_SHIFT                       (9U)
#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC0_WR_MMU_ROUTE_ENABLE_MASK                        (0x00000200U)

#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC1_WR_MMU_ROUTE_ENABLE_SHIFT                       (8U)
#define CTRL_CORE_SEC_SMA_SW_7_EDMA_TC1_WR_MMU_ROUTE_ENABLE_MASK                        (0x00000100U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_MMU1_SHIFT                              (28U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_MMU1_MASK                               (0xf0000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC0_RD_SHIFT                       (24U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC0_RD_MASK                        (0x0f000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC0_WR_SHIFT                       (20U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC0_WR_MASK                        (0x00f00000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC1_RD_SHIFT                       (16U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC1_RD_MASK                        (0x000f0000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC1_WR_SHIFT                       (12U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EDMA_TC1_WR_MASK                        (0x0000f000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_VIP1_P0_SHIFT                           (8U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_VIP1_P0_MASK                            (0x00000f00U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_VIP1_P1_SHIFT                           (4U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_VIP1_P1_MASK                            (0x000000f0U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EVE1_TC0_SHIFT                          (0U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_0_EVE1_TC0_MASK                           (0x0000000fU)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_EVE1_TC1_SHIFT                          (28U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_EVE1_TC1_MASK                           (0xf0000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP1_EDMA_SHIFT                         (24U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP1_EDMA_MASK                          (0x0f000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP1_MDMA_SHIFT                         (20U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP1_MDMA_MASK                          (0x00f00000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP2_EDMA_SHIFT                         (16U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP2_EDMA_MASK                          (0x000f0000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP2_MDMA_SHIFT                         (12U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSP2_MDMA_MASK                          (0x0000f000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSS_SHIFT                               (8U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_DSS_MASK                                (0x00000f00U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_IPU1_SHIFT                              (0U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_1_IPU1_MASK                               (0x0000000fU)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DSP1_CFG_SHIFT                          (24U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DSP1_CFG_MASK                           (0x0f000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DSP2_CFG_SHIFT                          (20U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DSP2_CFG_MASK                           (0x00f00000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_GMAC_SW_SHIFT                           (16U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_GMAC_SW_MASK                            (0x000f0000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_IEEE1500_SHIFT                          (4U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_IEEE1500_MASK                           (0x000000f0U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DAP_SHIFT                               (0U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_2_DAP_MASK                                (0x0000000fU)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_RT_SHIFT                            (24U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_RT_MASK                             (0x0f000000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_SPARE_JESD_SHIFT                        (20U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_SPARE_JESD_MASK                         (0x00f00000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_NRT1_SHIFT                          (16U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_NRT1_MASK                           (0x000f0000U)

#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_NRT2_SHIFT                          (12U)
#define CTRL_CORE_SEC_FIREWALL_CONNID_CONTROL_3_ISS_NRT2_MASK                           (0x0000f000U)

#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_EVE1_ENABLE_SHIFT                                (3U)
#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_EVE1_ENABLE_MASK                                 (0x00000008U)

#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_DSP2_ENABLE_SHIFT                                (2U)
#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_DSP2_ENABLE_MASK                                 (0x00000004U)

#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_DSP1_ENABLE_SHIFT                                (1U)
#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_DSP1_ENABLE_MASK                                 (0x00000002U)

#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_IPU1_ENABLE_SHIFT                                (0U)
#define CTRL_CORE_SEC_EMIF_MPU_ROUTING_IPU1_ENABLE_MASK                                 (0x00000001U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_SHIFT                                     (28U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_MASK                                      (0x10000000U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_EVE2_GCLK                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_EVE1_GCLK                                  (0U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_SHIFT                                     (24U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_MASK                                      (0x03000000U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP1_CLK                                   (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_RESERVED                                   (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP0_CLK                                   (2U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP2_CLK                                   (0U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SHIFT                                     (20U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_MASK                                      (0x00300000U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SYS_CLK2                                   (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_RESERVED                                   (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SYS_CLK1                                   (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_XREF_CLK                                   (2U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SHIFT                                    (16U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_MASK                                     (0x00030000U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SYS_CLK2                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_RESERVED                                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SYS_CLK1                                  (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_XREF_CLK                                  (2U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SHIFT                                    (12U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_MASK                                     (0x00003000U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SYS_CLK2                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_RESERVED                                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SYS_CLK1                                  (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_XREF_CLK                                  (2U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SHIFT                                    (8U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_MASK                                     (0x00000300U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SYS_CLK2                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_RESERVED                                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SYS_CLK1                                  (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_XREF_CLK                                  (2U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SHIFT                                    (4U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_MASK                                     (0x00000030U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SYS_CLK2                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_RESERVED                                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SYS_CLK1                                  (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_XREF_CLK                                  (2U)

#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SHIFT                                    (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_MASK                                     (0x00000003U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SYS_CLK2                                  (1U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_RESERVED                                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SYS_CLK1                                  (0U)
#define CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_XREF_CLK                                  (2U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_HSDIV_CHANGE_ACK_SHIFT      (29U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_HSDIV_CHANGE_ACK_MASK       (0x20000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_HSDIV_EN_ACK_SHIFT          (28U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_HSDIV_EN_ACK_MASK           (0x10000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_HSDIV_CHANGE_ACK_SHIFT      (27U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_HSDIV_CHANGE_ACK_MASK       (0x08000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_HSDIV_EN_ACK_SHIFT          (26U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_HSDIV_EN_ACK_MASK           (0x04000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_HSDIV_CHANGE_ACK_SHIFT           (25U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_HSDIV_CHANGE_ACK_MASK            (0x02000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_HSDIV_EN_ACK_SHIFT               (24U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_HSDIV_EN_ACK_MASK                (0x01000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SEL_SHIFT        (23U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SEL_MASK         (0x00800000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SHIFT            (22U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_MASK             (0x00400000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_DIV_SHIFT                   (16U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_DIV_MASK                    (0x003f0000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SEL_SHIFT        (15U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SEL_MASK         (0x00008000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SHIFT            (14U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_MASK             (0x00004000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_DIV_SHIFT                   (8U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_DIV_MASK                    (0x00003f00U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_TENABLEDIV_SEL_SHIFT             (7U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_TENABLEDIV_SEL_MASK              (0x00000080U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_TENABLEDIV_SHIFT                 (6U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_TENABLEDIV_MASK                  (0x00000040U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_DIV_SHIFT                        (0U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_DIV_MASK                         (0x0000003fU)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_TENABLEDIV_SEL_SHIFT             (28U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_TENABLEDIV_SEL_MASK              (0x10000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_CHANGE_ACK_SHIFT           (27U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_CHANGE_ACK_MASK            (0x08000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_SHIFT                    (25U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_MASK                     (0x06000000U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV2                      (1U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_RESERVED                  (3U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV1                      (0U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV4                      (2U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_ACK_SHIFT               (24U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_ACK_MASK                (0x01000000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_SHIFT                   (23U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_MASK                    (0x00800000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_LATCH_EN_SHIFT             (22U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_LATCH_EN_MASK              (0x00400000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_SHIFT                      (16U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_MASK                       (0x003f0000U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_DIV2                        (1U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_RESERVED                    (3U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_DIV1                        (0U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_DIV4                        (2U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_DBG_ATB_CLK_TENABLEDIV_SEL_SHIFT       (12U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_DBG_ATB_CLK_TENABLEDIV_SEL_MASK        (0x00003000U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_CHANGE_ACK_SHIFT                 (11U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_CHANGE_ACK_MASK                  (0x00000800U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_SHIFT                      (9U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_MASK                       (0x00000600U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV2                        (1U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_RESERVED                    (3U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV1                        (0U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV4                        (2U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_ACK_SHIFT                     (8U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_ACK_MASK                      (0x00000100U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_SHIFT                         (7U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_MASK                          (0x00000080U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_LATCH_EN_SHIFT                   (6U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_LATCH_EN_MASK                    (0x00000040U)

#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_SHIFT                            (0U)
#define CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_MASK                             (0x0000003fU)

#define CTRL_CORE_SEC_SMA_SW_10_SHIFT                                                   (30U)
#define CTRL_CORE_SEC_SMA_SW_10_MASK                                                    (0xc0000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y4_SHIFT                                      (29U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y4_MASK                                       (0x20000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X4_SHIFT                                      (28U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X4_MASK                                       (0x10000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y3_SHIFT                                      (27U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y3_MASK                                       (0x08000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X3_SHIFT                                      (25U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X3_MASK                                       (0x06000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y2_SHIFT                                      (24U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y2_MASK                                       (0x01000000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X2_SHIFT                                      (23U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X2_MASK                                       (0x00800000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y1_SHIFT                                      (22U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y1_MASK                                       (0x00400000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X1_SHIFT                                      (21U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X1_MASK                                       (0x00200000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y0_SHIFT                                      (20U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_Y0_MASK                                       (0x00100000U)

#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X0_SHIFT                                      (19U)
#define CTRL_CORE_SEC_SMA_SW_10_IE_CSI2_0_X0_MASK                                       (0x00080000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X4_SHIFT                                    (18U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X4_MASK                                     (0x00040000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y3_SHIFT                                    (17U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y3_MASK                                     (0x00020000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X3_SHIFT                                    (16U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X3_MASK                                     (0x00010000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y2_SHIFT                                    (15U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y2_MASK                                     (0x00008000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X2_SHIFT                                    (14U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X2_MASK                                     (0x00004000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y1_SHIFT                                    (13U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y1_MASK                                     (0x00002000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X1_SHIFT                                    (12U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X1_MASK                                     (0x00001000U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y0_SHIFT                                    (11U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_Y0_MASK                                     (0x00000800U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X0_SHIFT                                    (10U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPD_CSI2_0_X0_MASK                                     (0x00000400U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y4_SHIFT                                    (9U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y4_MASK                                     (0x00000200U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X4_SHIFT                                    (8U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X4_MASK                                     (0x00000100U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y3_SHIFT                                    (7U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y3_MASK                                     (0x00000080U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X3_SHIFT                                    (6U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X3_MASK                                     (0x00000040U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y2_SHIFT                                    (5U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y2_MASK                                     (0x00000020U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X2_SHIFT                                    (4U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X2_MASK                                     (0x00000010U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y1_SHIFT                                    (3U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y1_MASK                                     (0x00000008U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X1_SHIFT                                    (2U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X1_MASK                                     (0x00000004U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y0_SHIFT                                    (1U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_Y0_MASK                                     (0x00000002U)

#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X0_SHIFT                                    (0U)
#define CTRL_CORE_SEC_SMA_SW_10_PIPU_CSI2_0_X0_MASK                                     (0x00000001U)

#define CTRL_CORE_SEC_SMA_SW_11_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_11_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_12_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_12_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_13_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_13_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_IPU_SHIFT                              (24U)
#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_IPU_MASK                               (0x0f000000U)

#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_DSP1_SHIFT                             (16U)
#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_DSP1_MASK                              (0x000f0000U)

#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_DSP2_SHIFT                             (8U)
#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_DSP2_MASK                              (0x00000f00U)

#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_EVE_SHIFT                              (0U)
#define CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_EVE_MASK                               (0x0000000fU)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_CALSET_SHIFT                                       (31U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_CALSET_MASK                                        (0x80000000U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_CAL_SHIFT                                          (21U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_CAL_MASK                                           (0x7fe00000U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_SHIFT                                          (6U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_MASK                                           (0x001fffc0U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_WR_ACK_SHIFT                                   (5U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_WR_ACK_MASK                                    (0x00000020U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_ASYNC_EN_SHIFT                                 (4U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_CTL_ASYNC_EN_MASK                                  (0x00000010U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_TVOUTBYPASS_SHIFT                                  (3U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_TVOUTBYPASS_MASK                                   (0x00000008U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_ACEN_SHIFT                                         (2U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_ACEN_MASK                                          (0x00000004U)

#define CTRL_CORE_SEC_SD_DAC_CONTROL_COMP_EN_SHIFT                                      (0U)
#define CTRL_CORE_SEC_SD_DAC_CONTROL_COMP_EN_MASK                                       (0x00000003U)

#define CTRL_CORE_SEC_SD_DAC_TRIM_VALUE_SHIFT                                           (0U)
#define CTRL_CORE_SEC_SD_DAC_TRIM_VALUE_MASK                                            (0xffffffffU)

#define CTRL_CORE_SEC_ADC_ERROR_OFFSET_SHIFT                                            (0U)
#define CTRL_CORE_SEC_ADC_ERROR_OFFSET_MASK                                             (0x000000ffU)

#define CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN_SHIFT                                          (0U)
#define CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN_MASK                                           (0x00000001U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE1_EN_SHIFT                                (6U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE1_EN_MASK                                 (0x00000040U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE2_EN_SHIFT                                (5U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE2_EN_MASK                                 (0x00000020U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE3_EN_SHIFT                                (4U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE3_EN_MASK                                 (0x00000010U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE4_EN_SHIFT                                (3U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE4_EN_MASK                                 (0x00000008U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE5_EN_SHIFT                                (2U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE5_EN_MASK                                 (0x00000004U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE6_EN_SHIFT                                (1U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE6_EN_MASK                                 (0x00000002U)

#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE7_EN_SHIFT                                (0U)
#define CTRL_CORE_SEC_ISS_EFUSE_STD_FUSE_EFUSE7_EN_MASK                                 (0x00000001U)

#define CTRL_CORE_SEC_SMA_SW_14_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_14_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_15_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_15_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SELECTION_SHIFT                     (0U)
#define CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SELECTION_MASK                      (0x1U)
#define CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SYS_CLK2                            (1U)
#define CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SYS_CLK1                            (0U)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLKHSDIV_SHIFT                                     (0U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLKHSDIV_MASK                                      (0x3fU)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_LATCH_EN_SHIFT                           (6U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_LATCH_EN_MASK                            (0x40U)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_SHIFT                                 (7U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_MASK                                  (0x80U)

#define CTRL_CORE_SEC_SMA_SW_17_RESERVED_SHIFT                                          (8U)
#define CTRL_CORE_SEC_SMA_SW_17_RESERVED_MASK                                           (0x100U)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL_SHIFT                           (9U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL_MASK                            (0x200U)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_ACK_SHIFT                             (10U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_ACK_MASK                              (0x400U)

#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_CHANGE_ACK_SHIFT                         (11U)
#define CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_CHANGE_ACK_MASK                          (0x800U)

#define CTRL_CORE_SEC_ROM_CPU0_BRANCH_SHIFT                                             (0U)
#define CTRL_CORE_SEC_ROM_CPU0_BRANCH_MASK                                              (0xffffffffU)

#define CTRL_CORE_SEC_ROM_CPU1_BRANCH_SHIFT                                             (0U)
#define CTRL_CORE_SEC_ROM_CPU1_BRANCH_MASK                                              (0xffffffffU)

#define CTRL_CORE_SEC_ROM_AUXBOOT0_SHIFT                                                (0U)
#define CTRL_CORE_SEC_ROM_AUXBOOT0_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SEC_ROM_AUXBOOT1_SHIFT                                                (0U)
#define CTRL_CORE_SEC_ROM_AUXBOOT1_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_18_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_18_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_19_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_19_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_20_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_20_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_21_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_21_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_22_CORE_DPLL_REGMF_CONTROL_SHIFT                           (0U)
#define CTRL_CORE_SEC_SMA_SW_22_CORE_DPLL_REGMF_CONTROL_MASK                            (0x3ffffU)

#define CTRL_CORE_SEC_SMA_SW_23_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_23_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_24_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_24_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_25_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_25_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_26_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_26_MASK                                                    (0xffffffffU)

#define CTRL_CORE_SEC_SMA_SW_27_SHIFT                                                   (0U)
#define CTRL_CORE_SEC_SMA_SW_27_MASK                                                    (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_SEC_H_ */

