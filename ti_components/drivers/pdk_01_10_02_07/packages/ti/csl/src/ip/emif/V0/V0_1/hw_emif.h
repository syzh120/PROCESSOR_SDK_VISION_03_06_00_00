/*
 *  Copyright (c) Texas Instruments Incorporated 2008-2013
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
 *  \file    hw_emif.h
 *
 *  \brief   register-level header file for EMIF
 */
#ifndef HW_EMIF_H_
#define HW_EMIF_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define EMIF_STATUS                                                                                        (0x4U)
#define EMIF_SDRAM_CONFIG                                                                                  (0x8U)
#define EMIF_SDRAM_CONFIG_2                                                                                (0xcU)
#define EMIF_SDRAM_REFRESH_CONTROL                                                                         (0x10U)
#define EMIF_SDRAM_REFRESH_CONTROL_SHADOW                                                                  (0x14U)
#define EMIF_SDRAM_TIMING_1                                                                                (0x18U)
#define EMIF_SDRAM_TIMING_1_SHADOW                                                                         (0x1cU)
#define EMIF_SDRAM_TIMING_2                                                                                (0x20U)
#define EMIF_SDRAM_TIMING_2_SHADOW                                                                         (0x24U)
#define EMIF_SDRAM_TIMING_3                                                                                (0x28U)
#define EMIF_SDRAM_TIMING_3_SHADOW                                                                         (0x2cU)
#define EMIF_LPDDR2_NVM_TIMING                                                                             (0x30U)
#define EMIF_LPDDR2_NVM_TIMING_SHADOW                                                                      (0x34U)
#define EMIF_POWER_MANAGEMENT_CONTROL                                                                      (0x38U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW                                                               (0x3cU)
#define EMIF_LPDDR2_MODE_REG_DATA                                                                          (0x40U)
#define EMIF_LPDDR2_MODE_REG_CONFIG                                                                        (0x50U)
#define EMIF_OCP_CONFIG                                                                                    (0x54U)
#define EMIF_OCP_CONFIG_VALUE_1                                                                            (0x58U)
#define EMIF_OCP_CONFIG_VALUE_2                                                                            (0x5cU)
#define EMIF_IODFT_TLGC                                                                                    (0x60U)
#define EMIF_PERFORMANCE_COUNTER_1                                                                         (0x80U)
#define EMIF_PERFORMANCE_COUNTER_2                                                                         (0x84U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG                                                                    (0x88U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT                                                      (0x8cU)
#define EMIF_PERFORMANCE_COUNTER_TIME                                                                      (0x90U)
#define EMIF_DLL_CALIB_CTRL                                                                                (0x98U)
#define EMIF_DLL_CALIB_CTRL_SHADOW                                                                         (0x9cU)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS                                                               (0xa4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS                                                                   (0xacU)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET                                                               (0xb4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR                                                             (0xbcU)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG                                                     (0xc8U)
#define EMIF_TEMPERATURE_ALERT_CONFIG                                                                      (0xccU)
#define EMIF_OCP_ERROR_LOG                                                                                 (0xd0U)
#define EMIF_READ_WRITE_LEVELING_RAMP_WINDOW                                                               (0xd4U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL                                                              (0xd8U)
#define EMIF_READ_WRITE_LEVELING_CONTROL                                                                   (0xdcU)
#define EMIF_DDR_PHY_CONTROL_1                                                                             (0xe4U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW                                                                      (0xe8U)
#define EMIF_DDR_PHY_CONTROL_2                                                                             (0xecU)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING                                                          (0x100U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING                                                   (0x104U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING                                                   (0x108U)
#define EMIF_ECC_CTRL_REG                                                                                  (0x110U)
#define EMIF_ECC_ADDRESS_RANGE_1                                                                           (0x114U)
#define EMIF_ECC_ADDRESS_RANGE_2                                                                           (0x118U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD                                                                (0x120U)
#define EMIF_COS_CONFIG                                                                                    (0x124U)
#define EMIF_1B_ECC_ERR_CNT                                                                                (0x130U)
#define EMIF_1B_ECC_ERR_THRSH                                                                              (0x134U)
#define EMIF_1B_ECC_ERR_DIST_1                                                                             (0x138U)
#define EMIF_1B_ECC_ERR_ADDR_LOG                                                                           (0x13cU)
#define EMIF_2B_ECC_ERR_ADDR_LOG                                                                           (0x140U)
#define EMIF_PHY_STATUS_1                                                                                  (0x144U)
#define EMIF_PHY_STATUS_20                                                                                 (0x190U)
#define EMIF_PHY_STATUS_21                                                                                 (0x194U)
#define EMIF_EXT_PHY_CONTROL_1                                                                             (0x200U)
#define EMIF_EXT_PHY_CONTROL_1_SHADOW                                                                      (0x204U)
#define EMIF_EXT_PHY_CONTROL_2                                                                             (0x208U)
#define EMIF_EXT_PHY_CONTROL_2_SHADOW                                                                      (0x20cU)
#define EMIF_EXT_PHY_CONTROL_3                                                                             (0x210U)
#define EMIF_EXT_PHY_CONTROL_3_SHADOW                                                                      (0x214U)
#define EMIF_EXT_PHY_CONTROL_4                                                                             (0x218U)
#define EMIF_EXT_PHY_CONTROL_4_SHADOW                                                                      (0x21cU)
#define EMIF_EXT_PHY_CONTROL_5                                                                             (0x220U)
#define EMIF_EXT_PHY_CONTROL_5_SHADOW                                                                      (0x224U)
#define EMIF_EXT_PHY_CONTROL_6                                                                             (0x228U)
#define EMIF_EXT_PHY_CONTROL_6_SHADOW                                                                      (0x22cU)
#define EMIF_EXT_PHY_CONTROL_7                                                                             (0x230U)
#define EMIF_EXT_PHY_CONTROL_7_SHADOW                                                                      (0x234U)
#define EMIF_EXT_PHY_CONTROL_8                                                                             (0x238U)
#define EMIF_EXT_PHY_CONTROL_8_SHADOW                                                                      (0x23cU)
#define EMIF_EXT_PHY_CONTROL_9                                                                             (0x240U)
#define EMIF_EXT_PHY_CONTROL_9_SHADOW                                                                      (0x244U)
#define EMIF_EXT_PHY_CONTROL_10                                                                            (0x248U)
#define EMIF_EXT_PHY_CONTROL_10_SHADOW                                                                     (0x24cU)
#define EMIF_EXT_PHY_CONTROL_11                                                                            (0x250U)
#define EMIF_EXT_PHY_CONTROL_11_SHADOW                                                                     (0x254U)
#define EMIF_EXT_PHY_CONTROL_12                                                                            (0x258U)
#define EMIF_EXT_PHY_CONTROL_12_SHADOW                                                                     (0x25cU)
#define EMIF_EXT_PHY_CONTROL_13                                                                            (0x260U)
#define EMIF_EXT_PHY_CONTROL_13_SHADOW                                                                     (0x264U)
#define EMIF_EXT_PHY_CONTROL_14                                                                            (0x268U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW                                                                     (0x26cU)
#define EMIF_EXT_PHY_CONTROL_15                                                                            (0x270U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW                                                                     (0x274U)
#define EMIF_EXT_PHY_CONTROL_16                                                                            (0x278U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW                                                                     (0x27cU)
#define EMIF_EXT_PHY_CONTROL_17                                                                            (0x280U)
#define EMIF_EXT_PHY_CONTROL_17_SHADOW                                                                     (0x284U)
#define EMIF_EXT_PHY_CONTROL_18                                                                            (0x288U)
#define EMIF_EXT_PHY_CONTROL_18_SHADOW                                                                     (0x28cU)
#define EMIF_EXT_PHY_CONTROL_19                                                                            (0x290U)
#define EMIF_EXT_PHY_CONTROL_19_SHADOW                                                                     (0x294U)
#define EMIF_EXT_PHY_CONTROL_20                                                                            (0x298U)
#define EMIF_EXT_PHY_CONTROL_20_SHADOW                                                                     (0x29cU)
#define EMIF_EXT_PHY_CONTROL_21                                                                            (0x2a0U)
#define EMIF_EXT_PHY_CONTROL_21_SHADOW                                                                     (0x2a4U)
#define EMIF_EXT_PHY_CONTROL_22                                                                            (0x2a8U)
#define EMIF_EXT_PHY_CONTROL_22_SHADOW                                                                     (0x2acU)
#define EMIF_EXT_PHY_CONTROL_23                                                                            (0x2b0U)
#define EMIF_EXT_PHY_CONTROL_23_SHADOW                                                                     (0x2b4U)
#define EMIF_EXT_PHY_CONTROL_24                                                                            (0x2b8U)
#define EMIF_EXT_PHY_CONTROL_24_SHADOW                                                                     (0x2bcU)
#define EMIF_EXT_PHY_CONTROL_25                                                                            (0x2c0U)
#define EMIF_EXT_PHY_CONTROL_25_SHADOW                                                                     (0x2c4U)
#define EMIF_EXT_PHY_CONTROL_26                                                                            (0x2c8U)
#define EMIF_EXT_PHY_CONTROL_26_SHADOW                                                                     (0x2ccU)
#define EMIF_EXT_PHY_CONTROL_27                                                                            (0x2d0U)
#define EMIF_EXT_PHY_CONTROL_27_SHADOW                                                                     (0x2d4U)
#define EMIF_EXT_PHY_CONTROL_28                                                                            (0x2d8U)
#define EMIF_EXT_PHY_CONTROL_28_SHADOW                                                                     (0x2dcU)
#define EMIF_EXT_PHY_CONTROL_29                                                                            (0x2e0U)
#define EMIF_EXT_PHY_CONTROL_29_SHADOW                                                                     (0x2e4U)
#define EMIF_EXT_PHY_CONTROL_30                                                                            (0x2e8U)
#define EMIF_EXT_PHY_CONTROL_30_SHADOW                                                                     (0x2ecU)
#define EMIF_EXT_PHY_CONTROL_31                                                                            (0x2f0U)
#define EMIF_EXT_PHY_CONTROL_31_SHADOW                                                                     (0x2f4U)
#define EMIF_EXT_PHY_CONTROL_32                                                                            (0x2f8U)
#define EMIF_EXT_PHY_CONTROL_32_SHADOW                                                                     (0x2fcU)
#define EMIF_EXT_PHY_CONTROL_33                                                                            (0x300U)
#define EMIF_EXT_PHY_CONTROL_33_SHADOW                                                                     (0x304U)
#define EMIF_EXT_PHY_CONTROL_34                                                                            (0x308U)
#define EMIF_EXT_PHY_CONTROL_34_SHADOW                                                                     (0x30cU)
#define EMIF_EXT_PHY_CONTROL_35                                                                            (0x310U)
#define EMIF_EXT_PHY_CONTROL_35_SHADOW                                                                     (0x314U)
#define EMIF_EXT_PHY_CONTROL_36                                                                            (0x318U)
#define EMIF_EXT_PHY_CONTROL_36_SHADOW                                                                     (0x31cU)
#define EMIF_MISC_REG                                                                                      (0x94U)
#define EMIF_REVISION                                                                                      (0x0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define EMIF_STATUS_BE_SHIFT                                                                              (31U)
#define EMIF_STATUS_BE_MASK                                                                               (0x80000000U)

#define EMIF_STATUS_DUAL_CLK_MODE_SHIFT                                                                   (30U)
#define EMIF_STATUS_DUAL_CLK_MODE_MASK                                                                    (0x40000000U)

#define EMIF_STATUS_FAST_INIT_SHIFT                                                                       (29U)
#define EMIF_STATUS_FAST_INIT_MASK                                                                        (0x20000000U)

#define EMIF_STATUS_RDLVLGATETO_SHIFT                                                                     (6U)
#define EMIF_STATUS_RDLVLGATETO_MASK                                                                      (0x00000040U)

#define EMIF_STATUS_RDLVLTO_SHIFT                                                                         (5U)
#define EMIF_STATUS_RDLVLTO_MASK                                                                          (0x00000020U)

#define EMIF_STATUS_WRLVLTO_SHIFT                                                                         (4U)
#define EMIF_STATUS_WRLVLTO_MASK                                                                          (0x00000010U)

#define EMIF_STATUS_PHY_DLL_READY_SHIFT                                                                   (2U)
#define EMIF_STATUS_PHY_DLL_READY_MASK                                                                    (0x00000004U)

#define EMIF_STATUS_RESERVED_SHIFT                                                                        (0U)
#define EMIF_STATUS_RESERVED_MASK                                                                         (0x00000003U)

#define EMIF_STATUS_RESERVED1_SHIFT                                                                       (3U)
#define EMIF_STATUS_RESERVED1_MASK                                                                        (0x00000008U)

#define EMIF_STATUS_RESERVED2_SHIFT                                                                       (7U)
#define EMIF_STATUS_RESERVED2_MASK                                                                        (0x1fffff80U)

#define EMIF_SDRAM_CONFIG_SDRAM_TYPE_SHIFT                                                                (29U)
#define EMIF_SDRAM_CONFIG_SDRAM_TYPE_MASK                                                                 (0xe0000000U)

#define EMIF_SDRAM_CONFIG_IBANK_POS_SHIFT                                                                 (27U)
#define EMIF_SDRAM_CONFIG_IBANK_POS_MASK                                                                  (0x18000000U)

#define EMIF_SDRAM_CONFIG_DDR_TERM_SHIFT                                                                  (24U)
#define EMIF_SDRAM_CONFIG_DDR_TERM_MASK                                                                   (0x07000000U)

#define EMIF_SDRAM_CONFIG_DDR2_DDQS_SHIFT                                                                 (23U)
#define EMIF_SDRAM_CONFIG_DDR2_DDQS_MASK                                                                  (0x00800000U)

#define EMIF_SDRAM_CONFIG_DYN_ODT_SHIFT                                                                   (21U)
#define EMIF_SDRAM_CONFIG_DYN_ODT_MASK                                                                    (0x00600000U)

#define EMIF_SDRAM_CONFIG_DDR_DISABLE_DLL_SHIFT                                                           (20U)
#define EMIF_SDRAM_CONFIG_DDR_DISABLE_DLL_MASK                                                            (0x00100000U)

#define EMIF_SDRAM_CONFIG_SDRAM_DRIVE_SHIFT                                                               (18U)
#define EMIF_SDRAM_CONFIG_SDRAM_DRIVE_MASK                                                                (0x000c0000U)

#define EMIF_SDRAM_CONFIG_CWL_SHIFT                                                                       (16U)
#define EMIF_SDRAM_CONFIG_CWL_MASK                                                                        (0x00030000U)

#define EMIF_SDRAM_CONFIG_NARROW_MODE_SHIFT                                                               (14U)
#define EMIF_SDRAM_CONFIG_NARROW_MODE_MASK                                                                (0x0000c000U)

#define EMIF_SDRAM_CONFIG_CL_SHIFT                                                                        (10U)
#define EMIF_SDRAM_CONFIG_CL_MASK                                                                         (0x00003c00U)

#define EMIF_SDRAM_CONFIG_ROWSIZE_SHIFT                                                                   (7U)
#define EMIF_SDRAM_CONFIG_ROWSIZE_MASK                                                                    (0x00000380U)

#define EMIF_SDRAM_CONFIG_IBANK_SHIFT                                                                     (4U)
#define EMIF_SDRAM_CONFIG_IBANK_MASK                                                                      (0x00000070U)

#define EMIF_SDRAM_CONFIG_PAGESIZE_SHIFT                                                                  (0U)
#define EMIF_SDRAM_CONFIG_PAGESIZE_MASK                                                                   (0x00000007U)

#define EMIF_SDRAM_CONFIG_RESERVED_SHIFT                                                                  (3U)
#define EMIF_SDRAM_CONFIG_RESERVED_MASK                                                                   (0x00000008U)

#define EMIF_SDRAM_CONFIG_2_EBANK_POS_SHIFT                                                               (27U)
#define EMIF_SDRAM_CONFIG_2_EBANK_POS_MASK                                                                (0x08000000U)

#define EMIF_SDRAM_CONFIG_2_RESERVED2_SHIFT                                                               (0U)
#define EMIF_SDRAM_CONFIG_2_RESERVED2_MASK                                                                (0x07ffffffU)

#define EMIF_SDRAM_CONFIG_2_RESERVED1_SHIFT                                                               (28U)
#define EMIF_SDRAM_CONFIG_2_RESERVED1_MASK                                                                (0xf0000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_SHIFT                                                      (31U)
#define EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_MASK                                                       (0x80000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_SRT_SHIFT                                                              (29U)
#define EMIF_SDRAM_REFRESH_CONTROL_SRT_MASK                                                               (0x20000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_ASR_SHIFT                                                              (28U)
#define EMIF_SDRAM_REFRESH_CONTROL_ASR_MASK                                                               (0x10000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_PASR_SHIFT                                                             (24U)
#define EMIF_SDRAM_REFRESH_CONTROL_PASR_MASK                                                              (0x07000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_REFRESH_RATE_SHIFT                                                     (0U)
#define EMIF_SDRAM_REFRESH_CONTROL_REFRESH_RATE_MASK                                                      (0x0000ffffU)

#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED_SHIFT                                                         (16U)
#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED_MASK                                                          (0x00ff0000U)

#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED1_SHIFT                                                        (27U)
#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED1_MASK                                                         (0x08000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED2_SHIFT                                                        (30U)
#define EMIF_SDRAM_REFRESH_CONTROL_RESERVED2_MASK                                                         (0x40000000U)

#define EMIF_SDRAM_REFRESH_CONTROL_SHADOW_REFRESH_RATE_SHDW_SHIFT                                         (0U)
#define EMIF_SDRAM_REFRESH_CONTROL_SHADOW_REFRESH_RATE_SHDW_MASK                                          (0x0000ffffU)

#define EMIF_SDRAM_REFRESH_CONTROL_SHADOW_RESERVED_SHIFT                                                  (16U)
#define EMIF_SDRAM_REFRESH_CONTROL_SHADOW_RESERVED_MASK                                                   (0xffff0000U)

#define EMIF_SDRAM_TIMING_1_T_RTW_SHIFT                                                                   (29U)
#define EMIF_SDRAM_TIMING_1_T_RTW_MASK                                                                    (0xe0000000U)

#define EMIF_SDRAM_TIMING_1_T_RP_SHIFT                                                                    (25U)
#define EMIF_SDRAM_TIMING_1_T_RP_MASK                                                                     (0x1e000000U)

#define EMIF_SDRAM_TIMING_1_T_RCD_SHIFT                                                                   (21U)
#define EMIF_SDRAM_TIMING_1_T_RCD_MASK                                                                    (0x01e00000U)

#define EMIF_SDRAM_TIMING_1_T_WR_SHIFT                                                                    (17U)
#define EMIF_SDRAM_TIMING_1_T_WR_MASK                                                                     (0x001e0000U)

#define EMIF_SDRAM_TIMING_1_T_RAS_SHIFT                                                                   (12U)
#define EMIF_SDRAM_TIMING_1_T_RAS_MASK                                                                    (0x0001f000U)

#define EMIF_SDRAM_TIMING_1_T_RC_SHIFT                                                                    (6U)
#define EMIF_SDRAM_TIMING_1_T_RC_MASK                                                                     (0x00000fc0U)

#define EMIF_SDRAM_TIMING_1_T_RRD_SHIFT                                                                   (3U)
#define EMIF_SDRAM_TIMING_1_T_RRD_MASK                                                                    (0x00000038U)

#define EMIF_SDRAM_TIMING_1_T_WTR_SHIFT                                                                   (0U)
#define EMIF_SDRAM_TIMING_1_T_WTR_MASK                                                                    (0x00000007U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RTW_SHDW_SHIFT                                                       (29U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RTW_SHDW_MASK                                                        (0xe0000000U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RP_SHDW_SHIFT                                                        (25U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RP_SHDW_MASK                                                         (0x1e000000U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RCD_SHDW_SHIFT                                                       (21U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RCD_SHDW_MASK                                                        (0x01e00000U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_WR_SHDW_SHIFT                                                        (17U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_WR_SHDW_MASK                                                         (0x001e0000U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RAS_SHDW_SHIFT                                                       (12U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RAS_SHDW_MASK                                                        (0x0001f000U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RC_SHDW_SHIFT                                                        (6U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RC_SHDW_MASK                                                         (0x00000fc0U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_RRD_SHDW_SHIFT                                                       (3U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_RRD_SHDW_MASK                                                        (0x00000038U)

#define EMIF_SDRAM_TIMING_1_SHADOW_T_WTR_SHDW_SHIFT                                                       (0U)
#define EMIF_SDRAM_TIMING_1_SHADOW_T_WTR_SHDW_MASK                                                        (0x00000007U)

#define EMIF_SDRAM_TIMING_2_T_XP_SHIFT                                                                    (28U)
#define EMIF_SDRAM_TIMING_2_T_XP_MASK                                                                     (0x70000000U)

#define EMIF_SDRAM_TIMING_2_T_ODT_SHIFT                                                                   (25U)
#define EMIF_SDRAM_TIMING_2_T_ODT_MASK                                                                    (0x0e000000U)

#define EMIF_SDRAM_TIMING_2_T_XSNR_SHIFT                                                                  (16U)
#define EMIF_SDRAM_TIMING_2_T_XSNR_MASK                                                                   (0x01ff0000U)

#define EMIF_SDRAM_TIMING_2_T_XSRD_SHIFT                                                                  (6U)
#define EMIF_SDRAM_TIMING_2_T_XSRD_MASK                                                                   (0x0000ffc0U)

#define EMIF_SDRAM_TIMING_2_T_RTP_SHIFT                                                                   (3U)
#define EMIF_SDRAM_TIMING_2_T_RTP_MASK                                                                    (0x00000038U)

#define EMIF_SDRAM_TIMING_2_T_CKE_SHIFT                                                                   (0U)
#define EMIF_SDRAM_TIMING_2_T_CKE_MASK                                                                    (0x00000007U)

#define EMIF_SDRAM_TIMING_2_RESERVED_SHIFT                                                                (31U)
#define EMIF_SDRAM_TIMING_2_RESERVED_MASK                                                                 (0x80000000U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_XP_SHDW_SHIFT                                                        (28U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_XP_SHDW_MASK                                                         (0x70000000U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_ODT_SHDW_SHIFT                                                       (25U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_ODT_SHDW_MASK                                                        (0x0e000000U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_XSNR_SHDW_SHIFT                                                      (16U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_XSNR_SHDW_MASK                                                       (0x01ff0000U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_XSRD_SHDW_SHIFT                                                      (6U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_XSRD_SHDW_MASK                                                       (0x0000ffc0U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_RTP_SHDW_SHIFT                                                       (3U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_RTP_SHDW_MASK                                                        (0x00000038U)

#define EMIF_SDRAM_TIMING_2_SHADOW_T_CKE_SHDW_SHIFT                                                       (0U)
#define EMIF_SDRAM_TIMING_2_SHADOW_T_CKE_SHDW_MASK                                                        (0x00000007U)

#define EMIF_SDRAM_TIMING_2_SHADOW_RESERVED_SHIFT                                                         (31U)
#define EMIF_SDRAM_TIMING_2_SHADOW_RESERVED_MASK                                                          (0x80000000U)

#define EMIF_SDRAM_TIMING_3_T_PDLL_UL_SHIFT                                                               (28U)
#define EMIF_SDRAM_TIMING_3_T_PDLL_UL_MASK                                                                (0xf0000000U)

#define EMIF_SDRAM_TIMING_3_T_CKESR_SHIFT                                                                 (21U)
#define EMIF_SDRAM_TIMING_3_T_CKESR_MASK                                                                  (0x00e00000U)

#define EMIF_SDRAM_TIMING_3_ZQ_ZQCS_SHIFT                                                                 (15U)
#define EMIF_SDRAM_TIMING_3_ZQ_ZQCS_MASK                                                                  (0x001f8000U)

#define EMIF_SDRAM_TIMING_3_T_RFC_SHIFT                                                                   (4U)
#define EMIF_SDRAM_TIMING_3_T_RFC_MASK                                                                    (0x00001ff0U)

#define EMIF_SDRAM_TIMING_3_T_RAS_MAX_SHIFT                                                               (0U)
#define EMIF_SDRAM_TIMING_3_T_RAS_MAX_MASK                                                                (0x0000000fU)

#define EMIF_SDRAM_TIMING_3_RESERVED_SHIFT                                                                (24U)
#define EMIF_SDRAM_TIMING_3_RESERVED_MASK                                                                 (0x0f000000U)

#define EMIF_SDRAM_TIMING_3_RESERVED1_SHIFT                                                               (13U)
#define EMIF_SDRAM_TIMING_3_RESERVED1_MASK                                                                (0x00006000U)

#define EMIF_SDRAM_TIMING_3_SHADOW_T_PDLL_UL_SHDW_SHIFT                                                   (28U)
#define EMIF_SDRAM_TIMING_3_SHADOW_T_PDLL_UL_SHDW_MASK                                                    (0xf0000000U)

#define EMIF_SDRAM_TIMING_3_SHADOW_T_CKESR_SHDW_SHIFT                                                     (21U)
#define EMIF_SDRAM_TIMING_3_SHADOW_T_CKESR_SHDW_MASK                                                      (0x00e00000U)

#define EMIF_SDRAM_TIMING_3_SHADOW_ZQ_ZQCS_SHDW_SHIFT                                                     (15U)
#define EMIF_SDRAM_TIMING_3_SHADOW_ZQ_ZQCS_SHDW_MASK                                                      (0x001f8000U)

#define EMIF_SDRAM_TIMING_3_SHADOW_T_RFC_SHDW_SHIFT                                                       (4U)
#define EMIF_SDRAM_TIMING_3_SHADOW_T_RFC_SHDW_MASK                                                        (0x00001ff0U)

#define EMIF_SDRAM_TIMING_3_SHADOW_T_RAS_MAX_SHDW_SHIFT                                                   (0U)
#define EMIF_SDRAM_TIMING_3_SHADOW_T_RAS_MAX_SHDW_MASK                                                    (0x0000000fU)

#define EMIF_SDRAM_TIMING_3_SHADOW_RESERVED_SHIFT                                                         (24U)
#define EMIF_SDRAM_TIMING_3_SHADOW_RESERVED_MASK                                                          (0x0f000000U)

#define EMIF_SDRAM_TIMING_3_SHADOW_RESERVED1_SHIFT                                                        (13U)
#define EMIF_SDRAM_TIMING_3_SHADOW_RESERVED1_MASK                                                         (0x00006000U)

#define EMIF_POWER_MANAGEMENT_CONTROL_PD_TIM_SHIFT                                                        (12U)
#define EMIF_POWER_MANAGEMENT_CONTROL_PD_TIM_MASK                                                         (0x0000f000U)

#define EMIF_POWER_MANAGEMENT_CONTROL_LP_MODE_SHIFT                                                       (8U)
#define EMIF_POWER_MANAGEMENT_CONTROL_LP_MODE_MASK                                                        (0x00000700U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SR_TIM_SHIFT                                                        (4U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SR_TIM_MASK                                                         (0x000000f0U)

#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED_SHIFT                                                      (16U)
#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED_MASK                                                       (0xffff0000U)

#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED1_SHIFT                                                     (0U)
#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED1_MASK                                                      (0x0000000fU)

#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED2_SHIFT                                                     (11U)
#define EMIF_POWER_MANAGEMENT_CONTROL_RESERVED2_MASK                                                      (0x00000800U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_PD_TIM_SHDW_SHIFT                                            (12U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_PD_TIM_SHDW_MASK                                             (0x0000f000U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_SR_TIM_SHDW_SHIFT                                            (4U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_SR_TIM_SHDW_MASK                                             (0x000000f0U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED_SHIFT                                               (8U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED_MASK                                                (0x00000f00U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED1_SHIFT                                              (16U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED1_MASK                                               (0xffff0000U)

#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED2_SHIFT                                              (0U)
#define EMIF_POWER_MANAGEMENT_CONTROL_SHADOW_RESERVED2_MASK                                               (0x0000000fU)

#define EMIF_OCP_CONFIG_SYS_THRESH_MAX_SHIFT                                                              (24U)
#define EMIF_OCP_CONFIG_SYS_THRESH_MAX_MASK                                                               (0x0f000000U)

#define EMIF_OCP_CONFIG_MPU_THRESH_MAX_SHIFT                                                              (20U)
#define EMIF_OCP_CONFIG_MPU_THRESH_MAX_MASK                                                               (0x00f00000U)

#define EMIF_OCP_CONFIG_RESERVED_SHIFT                                                                    (0U)
#define EMIF_OCP_CONFIG_RESERVED_MASK                                                                     (0x000fffffU)

#define EMIF_OCP_CONFIG_RESERVED1_SHIFT                                                                   (28U)
#define EMIF_OCP_CONFIG_RESERVED1_MASK                                                                    (0xf0000000U)

#define EMIF_OCP_CONFIG_VALUE_1_SYS_BUS_WIDTH_SHIFT                                                       (30U)
#define EMIF_OCP_CONFIG_VALUE_1_SYS_BUS_WIDTH_MASK                                                        (0xc0000000U)

#define EMIF_OCP_CONFIG_VALUE_1_WR_FIFO_DEPTH_SHIFT                                                       (8U)
#define EMIF_OCP_CONFIG_VALUE_1_WR_FIFO_DEPTH_MASK                                                        (0x0000ff00U)

#define EMIF_OCP_CONFIG_VALUE_1_CMD_FIFO_DEPTH_SHIFT                                                      (0U)
#define EMIF_OCP_CONFIG_VALUE_1_CMD_FIFO_DEPTH_MASK                                                       (0x000000ffU)

#define EMIF_OCP_CONFIG_VALUE_1_RESERVED_SHIFT                                                            (16U)
#define EMIF_OCP_CONFIG_VALUE_1_RESERVED_MASK                                                             (0x3fff0000U)

#define EMIF_OCP_CONFIG_VALUE_2_RREG_FIFO_DEPTH_SHIFT                                                     (16U)
#define EMIF_OCP_CONFIG_VALUE_2_RREG_FIFO_DEPTH_MASK                                                      (0x00ff0000U)

#define EMIF_OCP_CONFIG_VALUE_2_RSD_FIFO_DEPTH_SHIFT                                                      (8U)
#define EMIF_OCP_CONFIG_VALUE_2_RSD_FIFO_DEPTH_MASK                                                       (0x0000ff00U)

#define EMIF_OCP_CONFIG_VALUE_2_RCMD_FIFO_DEPTH_SHIFT                                                     (0U)
#define EMIF_OCP_CONFIG_VALUE_2_RCMD_FIFO_DEPTH_MASK                                                      (0x000000ffU)

#define EMIF_OCP_CONFIG_VALUE_2_RESERVED_SHIFT                                                            (24U)
#define EMIF_OCP_CONFIG_VALUE_2_RESERVED_MASK                                                             (0xff000000U)

#define EMIF_PERFORMANCE_COUNTER_1_COUNTER1_SHIFT                                                         (0U)
#define EMIF_PERFORMANCE_COUNTER_1_COUNTER1_MASK                                                          (0xffffffffU)

#define EMIF_PERFORMANCE_COUNTER_2_COUNTER2_SHIFT                                                         (0U)
#define EMIF_PERFORMANCE_COUNTER_2_COUNTER2_MASK                                                          (0xffffffffU)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_MCONNID_EN_SHIFT                                            (31U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_MCONNID_EN_MASK                                             (0x80000000U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_REGION_EN_SHIFT                                             (30U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_REGION_EN_MASK                                              (0x40000000U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_CFG_SHIFT                                                   (16U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR2_CFG_MASK                                                    (0x000f0000U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_MCONNID_EN_SHIFT                                            (15U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_MCONNID_EN_MASK                                             (0x00008000U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_REGION_EN_SHIFT                                             (14U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_REGION_EN_MASK                                              (0x00004000U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_CFG_SHIFT                                                   (0U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_CNTR1_CFG_MASK                                                    (0x0000000fU)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_RESERVED_SHIFT                                                    (4U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_RESERVED_MASK                                                     (0x00003ff0U)

#define EMIF_PERFORMANCE_COUNTER_CONFIG_RESERVED1_SHIFT                                                   (20U)
#define EMIF_PERFORMANCE_COUNTER_CONFIG_RESERVED1_MASK                                                    (0x3ff00000U)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_MCONNID2_SHIFT                                      (24U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_MCONNID2_MASK                                       (0xff000000U)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_REGION_SEL2_SHIFT                                   (16U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_REGION_SEL2_MASK                                    (0x00030000U)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_MCONNID1_SHIFT                                      (8U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_MCONNID1_MASK                                       (0x0000ff00U)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_REGION_SEL1_SHIFT                                   (0U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_REGION_SEL1_MASK                                    (0x00000003U)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_RESERVED_SHIFT                                      (2U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_RESERVED_MASK                                       (0x000000fcU)

#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_RESERVED1_SHIFT                                     (18U)
#define EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT_RESERVED1_MASK                                      (0x00fc0000U)

#define EMIF_PERFORMANCE_COUNTER_TIME_TOTAL_TIME_SHIFT                                                    (0U)
#define EMIF_PERFORMANCE_COUNTER_TIME_TOTAL_TIME_MASK                                                     (0xffffffffU)

#define EMIF_DLL_CALIB_CTRL_ACK_WAIT_SHIFT                                                                (16U)
#define EMIF_DLL_CALIB_CTRL_ACK_WAIT_MASK                                                                 (0x000f0000U)

#define EMIF_DLL_CALIB_CTRL_DLL_CALIB_INTERVAL_SHIFT                                                      (0U)
#define EMIF_DLL_CALIB_CTRL_DLL_CALIB_INTERVAL_MASK                                                       (0x000001ffU)

#define EMIF_DLL_CALIB_CTRL_RESERVED_SHIFT                                                                (9U)
#define EMIF_DLL_CALIB_CTRL_RESERVED_MASK                                                                 (0x0000fe00U)

#define EMIF_DLL_CALIB_CTRL_RESERVED1_SHIFT                                                               (20U)
#define EMIF_DLL_CALIB_CTRL_RESERVED1_MASK                                                                (0xfff00000U)

#define EMIF_DLL_CALIB_CTRL_SHADOW_ACK_WAIT_SHDW_SHIFT                                                    (16U)
#define EMIF_DLL_CALIB_CTRL_SHADOW_ACK_WAIT_SHDW_MASK                                                     (0x000f0000U)

#define EMIF_DLL_CALIB_CTRL_SHADOW_DLL_CALIB_INTERVAL_SHDW_SHIFT                                          (0U)
#define EMIF_DLL_CALIB_CTRL_SHADOW_DLL_CALIB_INTERVAL_SHDW_MASK                                           (0x000001ffU)

#define EMIF_DLL_CALIB_CTRL_SHADOW_RESERVED_SHIFT                                                         (9U)
#define EMIF_DLL_CALIB_CTRL_SHADOW_RESERVED_MASK                                                          (0x0000fe00U)

#define EMIF_DLL_CALIB_CTRL_SHADOW_RESERVED1_SHIFT                                                        (20U)
#define EMIF_DLL_CALIB_CTRL_SHADOW_RESERVED1_MASK                                                         (0xfff00000U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_ERR_SYS_SHIFT                                                (0U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_ERR_SYS_MASK                                                 (0x00000001U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_RESERVED_SHIFT                                               (6U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_RESERVED_MASK                                                (0xffffffc0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_RESERVED1_SHIFT                                              (1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_RESERVED1_MASK                                               (0x00000006U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_SHIFT                                         (3U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_MASK                                          (0x00000008U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_ENABLE                                        (0x1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_WR_ECC_ERR_SYS_DISABLE                                       (0x0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_TWOBIT_ECC_ERR_SYS_SHIFT                                     (4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_TWOBIT_ECC_ERR_SYS_MASK                                      (0x00000010U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_TWOBIT_ECC_ERR_SYS_ENABLE                                    (0x1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_TWOBIT_ECC_ERR_SYS_DISABLE                                   (0x0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_ONEBIT_ECC_ERR_SYS_SHIFT                                     (5U)
#define EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS_ONEBIT_ECC_ERR_SYS_MASK                                      (0x00000020U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_RESERVED_SHIFT                                                   (6U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_RESERVED_MASK                                                    (0xffffffc0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_SHIFT                                             (3U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK                                              (0x00000008U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_SHIFT                                         (4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK                                          (0x00000010U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_SHIFT                                         (5U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK                                          (0x00000020U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_RESERVED1_SHIFT                                                  (1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_RESERVED1_MASK                                                   (0x00000006U)

#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ERR_SYS_SHIFT                                                    (0U)
#define EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ERR_SYS_MASK                                                     (0x00000001U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_EN_ERR_SYS_SHIFT                                             (0U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_EN_ERR_SYS_MASK                                              (0x00000001U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_RESERVED_SHIFT                                               (6U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_RESERVED_MASK                                                (0xffffffc0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TA_SYS_SHIFT                                                 (1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TA_SYS_MASK                                                  (0x00000002U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_RESERVED1_SHIFT                                              (2U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_RESERVED1_MASK                                               (0x00000004U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_SHIFT                                         (3U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK                                          (0x00000008U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_SHIFT                                     (4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_MASK                                      (0x00000010U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_SHIFT                                     (5U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK                                      (0x00000020U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_EN_ERR_SYS_SHIFT                                           (0U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_EN_ERR_SYS_MASK                                            (0x00000001U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_RESERVED_SHIFT                                             (6U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_RESERVED_MASK                                              (0xffffffc0U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_RESERVED1_SHIFT                                            (1U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_RESERVED1_MASK                                             (0x00000006U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_WR_ECC_ERR_SYS_SHIFT                                       (3U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_WR_ECC_ERR_SYS_MASK                                        (0x00000008U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_TWOBIT_ECC_ERR_SYS_SHIFT                                   (4U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_TWOBIT_ECC_ERR_SYS_MASK                                    (0x00000010U)

#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_ONEBIT_ECC_ERR_SYS_SHIFT                                   (5U)
#define EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_ONEBIT_ECC_ERR_SYS_MASK                                    (0x00000020U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_CS0EN_SHIFT                                     (30U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_CS0EN_MASK                                      (0x40000000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_SFEXITEN_SHIFT                                  (28U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_SFEXITEN_MASK                                   (0x10000000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_ZQCL_MULT_SHIFT                                 (16U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_ZQCL_MULT_MASK                                  (0x00030000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_REFINTERVAL_SHIFT                               (0U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_REFINTERVAL_MASK                                (0x0000ffffU)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED1_SHIFT                                    (31U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED1_MASK                                     (0x80000000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED2_SHIFT                                    (29U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED2_MASK                                     (0x20000000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED3_SHIFT                                    (18U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_RESERVED3_MASK                                     (0x07fc0000U)

#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_PDEXITEN_SHIFT                                  (27U)
#define EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG_ZQ_PDEXITEN_MASK                                   (0x08000000U)

#define EMIF_OCP_ERROR_LOG_MADDRSPACE_SHIFT                                                               (14U)
#define EMIF_OCP_ERROR_LOG_MADDRSPACE_MASK                                                                (0x0000c000U)

#define EMIF_OCP_ERROR_LOG_MBURSTSEQ_SHIFT                                                                (11U)
#define EMIF_OCP_ERROR_LOG_MBURSTSEQ_MASK                                                                 (0x00003800U)

#define EMIF_OCP_ERROR_LOG_MCMD_SHIFT                                                                     (8U)
#define EMIF_OCP_ERROR_LOG_MCMD_MASK                                                                      (0x00000700U)

#define EMIF_OCP_ERROR_LOG_MCONNID_SHIFT                                                                  (0U)
#define EMIF_OCP_ERROR_LOG_MCONNID_MASK                                                                   (0x000000ffU)

#define EMIF_OCP_ERROR_LOG_RESERVED_SHIFT                                                                 (16U)
#define EMIF_OCP_ERROR_LOG_RESERVED_MASK                                                                  (0xffff0000U)

#define EMIF_READ_WRITE_LEVELING_RAMP_WINDOW_RDWRLVLINC_RMP_WIN_SHIFT                                     (0U)
#define EMIF_READ_WRITE_LEVELING_RAMP_WINDOW_RDWRLVLINC_RMP_WIN_MASK                                      (0x00001fffU)

#define EMIF_READ_WRITE_LEVELING_RAMP_WINDOW_RESERVED_SHIFT                                               (13U)
#define EMIF_READ_WRITE_LEVELING_RAMP_WINDOW_RESERVED_MASK                                                (0xffffe000U)

#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDWRLVL_EN_SHIFT                                            (31U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDWRLVL_EN_MASK                                             (0x80000000U)

#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDWRLVLINC_RMP_PRE_SHIFT                                    (24U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDWRLVLINC_RMP_PRE_MASK                                     (0x7f000000U)

#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDLVLINC_RMP_INT_SHIFT                                      (16U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDLVLINC_RMP_INT_MASK                                       (0x00ff0000U)

#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDLVLGATEINC_RMP_INT_SHIFT                                  (8U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDLVLGATEINC_RMP_INT_MASK                                   (0x0000ff00U)

#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_WRLVLINC_RMP_INT_SHIFT                                      (0U)
#define EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_WRLVLINC_RMP_INT_MASK                                       (0x000000ffU)

#define EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLFULL_START_SHIFT                                          (31U)
#define EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLFULL_START_MASK                                           (0x80000000U)

#define EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLINC_PRE_SHIFT                                             (24U)
#define EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLINC_PRE_MASK                                              (0x7f000000U)

#define EMIF_READ_WRITE_LEVELING_CONTROL_RDLVLINC_INT_SHIFT                                               (16U)
#define EMIF_READ_WRITE_LEVELING_CONTROL_RDLVLINC_INT_MASK                                                (0x00ff0000U)

#define EMIF_READ_WRITE_LEVELING_CONTROL_RDLVLGATEINC_INT_SHIFT                                           (8U)
#define EMIF_READ_WRITE_LEVELING_CONTROL_RDLVLGATEINC_INT_MASK                                            (0x0000ff00U)

#define EMIF_READ_WRITE_LEVELING_CONTROL_WRLVLINC_INT_SHIFT                                               (0U)
#define EMIF_READ_WRITE_LEVELING_CONTROL_WRLVLINC_INT_MASK                                                (0x000000ffU)

#define EMIF_DDR_PHY_CONTROL_1_READ_LATENCY_SHIFT                                                         (0U)
#define EMIF_DDR_PHY_CONTROL_1_READ_LATENCY_MASK                                                          (0x0000001fU)

#define EMIF_DDR_PHY_CONTROL_1_RESERVED_SHIFT                                                             (5U)
#define EMIF_DDR_PHY_CONTROL_1_RESERVED_MASK                                                              (0x000001e0U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_FAST_DLL_LOCK_SHIFT                                                    (9U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_FAST_DLL_LOCK_MASK                                                     (0x00000200U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_DLL_LOCK_DIFF_SHIFT                                                    (10U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_DLL_LOCK_DIFF_MASK                                                     (0x0003fc00U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_INVERT_CLKOUT_SHIFT                                                    (18U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_INVERT_CLKOUT_MASK                                                     (0x00040000U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_DIS_CALIB_RST_SHIFT                                                    (19U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_DIS_CALIB_RST_MASK                                                     (0x00080000U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_CLK_STALL_LEVEL_SHIFT                                                  (20U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_CLK_STALL_LEVEL_MASK                                                   (0x00100000U)

#define EMIF_DDR_PHY_CONTROL_1_PHY_HALF_DELAYS_SHIFT                                                      (21U)
#define EMIF_DDR_PHY_CONTROL_1_PHY_HALF_DELAYS_MASK                                                       (0x00200000U)

#define EMIF_DDR_PHY_CONTROL_1_RESERVED1_SHIFT                                                            (22U)
#define EMIF_DDR_PHY_CONTROL_1_RESERVED1_MASK                                                             (0x01c00000U)

#define EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_SHIFT                                                           (25U)
#define EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_MASK                                                            (0x02000000U)

#define EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_SHIFT                                                       (26U)
#define EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_MASK                                                        (0x04000000U)

#define EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_SHIFT                                                           (27U)
#define EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_MASK                                                            (0x08000000U)

#define EMIF_DDR_PHY_CONTROL_1_RESERVED2_SHIFT                                                            (28U)
#define EMIF_DDR_PHY_CONTROL_1_RESERVED2_MASK                                                             (0x70000000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_READ_LATENCY_SHDW_SHIFT                                             (0U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_READ_LATENCY_SHDW_MASK                                              (0x0000001fU)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED1_SHIFT                                                     (5U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED1_MASK                                                      (0x000001e0U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_FAST_DLL_SHDW_SHIFT                                             (9U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_FAST_DLL_SHDW_MASK                                              (0x00000200U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_DLL_LOCK_DIFF_SHDW_SHIFT                                        (10U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_DLL_LOCK_DIFF_SHDW_MASK                                         (0x0003fc00U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_INVERT_CLKOUT_SHDW_SHIFT                                        (18U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_INVERT_CLKOUT_SHDW_MASK                                         (0x00040000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_DIS_CALIB_RST_SHDW_SHIFT                                        (19U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_DIS_CALIB_RST_SHDW_MASK                                         (0x00080000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_CLK_STALL_LEVEL_SHDW_SHIFT                                      (20U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_CLK_STALL_LEVEL_SHDW_MASK                                       (0x00100000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_HALF_DELAYS_SHDW_SHIFT                                          (21U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_PHY_HALF_DELAYS_SHDW_MASK                                           (0x00200000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED2_SHIFT                                                     (22U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED2_MASK                                                      (0x01c00000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_WRLVL_MASK_SHDW_SHIFT                                               (25U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_WRLVL_MASK_SHDW_MASK                                                (0x02000000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RDLVLGATE_MASK_SHDW_SHIFT                                           (25U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RDLVLGATE_MASK_SHDW_MASK                                            (0x02000000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RDLVL_MASK_SHDW_SHIFT                                               (27U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RDLVL_MASK_SHDW_MASK                                                (0x08000000U)

#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED3_SHIFT                                                     (28U)
#define EMIF_DDR_PHY_CONTROL_1_SHADOW_RESERVED3_MASK                                                      (0x70000000U)

#define EMIF_DDR_PHY_CONTROL_2_DDR_PHY_CTRL_2_SHIFT                                                       (0U)
#define EMIF_DDR_PHY_CONTROL_2_DDR_PHY_CTRL_2_MASK                                                        (0xffffffffU)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_COS_MAP_EN_SHIFT                                    (31U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_COS_MAP_EN_MASK                                     (0x80000000U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_7_COS_SHIFT                                         (14U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_7_COS_MASK                                          (0x0000c000U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_6_COS_SHIFT                                         (12U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_6_COS_MASK                                          (0x00003000U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_5_COS_SHIFT                                         (10U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_5_COS_MASK                                          (0x00000c00U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_4_COS_SHIFT                                         (8U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_4_COS_MASK                                          (0x00000300U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_3_COS_SHIFT                                         (6U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_3_COS_MASK                                          (0x000000c0U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_2_COS_SHIFT                                         (4U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_2_COS_MASK                                          (0x00000030U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_1_COS_SHIFT                                         (2U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_1_COS_MASK                                          (0x0000000cU)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_0_COS_SHIFT                                         (0U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_PRI_0_COS_MASK                                          (0x00000003U)

#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_RESERVED_SHIFT                                          (16U)
#define EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING_RESERVED_MASK                                           (0x7fff0000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_COS_1_MAP_EN_SHIFT                        (31U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_COS_1_MAP_EN_MASK                         (0x80000000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_1_COS_1_SHIFT                             (23U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_1_COS_1_MASK                              (0x7f800000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_1_COS_1_SHIFT                                (20U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_1_COS_1_MASK                                 (0x00700000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_2_COS_1_SHIFT                             (12U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_2_COS_1_MASK                              (0x000ff000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_2_COS_1_SHIFT                                (10U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_2_COS_1_MASK                                 (0x00000c00U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_3_COS_1_SHIFT                             (2U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_CONNID_3_COS_1_MASK                              (0x000003fcU)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_3_COS_1_SHIFT                                (0U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING_MSK_3_COS_1_MASK                                 (0x00000003U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_COS_2_MAP_EN_SHIFT                        (31U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_COS_2_MAP_EN_MASK                         (0x80000000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_1_COS_2_SHIFT                             (23U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_1_COS_2_MASK                              (0x7f800000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_1_COS_2_SHIFT                                (20U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_1_COS_2_MASK                                 (0x00700000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_2_COS_2_SHIFT                             (12U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_2_COS_2_MASK                              (0x000ff000U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_2_COS_2_SHIFT                                (10U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_2_COS_2_MASK                                 (0x00000c00U)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_3_COS_2_SHIFT                             (2U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_CONNID_3_COS_2_MASK                              (0x000003fcU)

#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_3_COS_2_SHIFT                                (0U)
#define EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING_MSK_3_COS_2_MASK                                 (0x00000003U)

#define EMIF_ECC_CTRL_REG_REG_ECC_EN_SHIFT                                                                (31U)
#define EMIF_ECC_CTRL_REG_REG_ECC_EN_MASK                                                                 (0x80000000U)

#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_PROT_SHIFT                                                     (30U)
#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_PROT_MASK                                                      (0x40000000U)

#define EMIF_ECC_CTRL_REG_RESERVED_SHIFT                                                                  (2U)
#define EMIF_ECC_CTRL_REG_RESERVED_MASK                                                                   (0x3ffffffcU)

#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_2_EN_SHIFT                                                     (1U)
#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_2_EN_MASK                                                      (0x00000002U)

#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_1_EN_SHIFT                                                     (0U)
#define EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_1_EN_MASK                                                      (0x00000001U)

#define EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_END_ADDR_1_SHIFT                                                 (16U)
#define EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_END_ADDR_1_MASK                                                  (0xffff0000U)

#define EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_STRT_ADDR_1_SHIFT                                                (0U)
#define EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_STRT_ADDR_1_MASK                                                 (0x0000ffffU)

#define EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_END_ADDR_2_SHIFT                                                 (16U)
#define EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_END_ADDR_2_MASK                                                  (0xffff0000U)

#define EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_STRT_ADDR_2_SHIFT                                                (0U)
#define EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_STRT_ADDR_2_MASK                                                 (0x0000ffffU)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_MFLAG_OVERRIDE_SHIFT                                          (31U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_MFLAG_OVERRIDE_MASK                                           (0x80000000U)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_WR_THRSH_SHIFT                                                (8U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_WR_THRSH_MASK                                                 (0x00001f00U)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RD_THRSH_SHIFT                                                (0U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RD_THRSH_MASK                                                 (0x0000001fU)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RESERVED_SHIFT                                                (5U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RESERVED_MASK                                                 (0x000000e0U)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RESERVED1_SHIFT                                               (13U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_RESERVED1_MASK                                                (0x3fffe000U)

#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_LLBUBBLE_ENABLE_SHIFT                                         (30U)
#define EMIF_READ_WRITE_EXECUTION_THRESHOLD_LLBUBBLE_ENABLE_MASK                                          (0x40000000U)

#define EMIF_COS_CONFIG_COS_COUNT_1_SHIFT                                                                 (16U)
#define EMIF_COS_CONFIG_COS_COUNT_1_MASK                                                                  (0x00ff0000U)

#define EMIF_COS_CONFIG_COS_COUNT_2_SHIFT                                                                 (8U)
#define EMIF_COS_CONFIG_COS_COUNT_2_MASK                                                                  (0x0000ff00U)

#define EMIF_COS_CONFIG_PR_OLD_COUNT_SHIFT                                                                (0U)
#define EMIF_COS_CONFIG_PR_OLD_COUNT_MASK                                                                 (0x000000ffU)

#define EMIF_COS_CONFIG_RESERVED_SHIFT                                                                    (24U)
#define EMIF_COS_CONFIG_RESERVED_MASK                                                                     (0xff000000U)

#define EMIF_1B_ECC_ERR_CNT_REG_1B_ECC_ERR_CNT_SHIFT                                                      (0U)
#define EMIF_1B_ECC_ERR_CNT_REG_1B_ECC_ERR_CNT_MASK                                                       (0xffffffffU)

#define EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_THRSH_SHIFT                                                  (24U)
#define EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_THRSH_MASK                                                   (0xff000000U)

#define EMIF_1B_ECC_ERR_THRSH_RESERVED_SHIFT                                                              (16U)
#define EMIF_1B_ECC_ERR_THRSH_RESERVED_MASK                                                               (0x00ff0000U)

#define EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_WIN_SHIFT                                                    (0U)
#define EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_WIN_MASK                                                     (0x0000ffffU)

#define EMIF_1B_ECC_ERR_DIST_1_REG_1B_ECC_ERR_DIST_1_SHIFT                                                (0U)
#define EMIF_1B_ECC_ERR_DIST_1_REG_1B_ECC_ERR_DIST_1_MASK                                                 (0xffffffffU)

#define EMIF_1B_ECC_ERR_ADDR_LOG_REG_1B_ECC_ERR_ADDR_SHIFT                                                (0U)
#define EMIF_1B_ECC_ERR_ADDR_LOG_REG_1B_ECC_ERR_ADDR_MASK                                                 (0xffffffffU)

#define EMIF_2B_ECC_ERR_ADDR_LOG_REG_2B_ECC_ERR_ADDR_SHIFT                                                (0U)
#define EMIF_2B_ECC_ERR_ADDR_LOG_REG_2B_ECC_ERR_ADDR_MASK                                                 (0xffffffffU)

#define EMIF_PHY_STATUS_1_RESERVED_SHIFT                                                                  (6U)
#define EMIF_PHY_STATUS_1_RESERVED_MASK                                                                   (0xffffffc0U)

#define EMIF_PHY_STATUS_1_PHY_REG_PHY_CTRL_DLL_SLAVE_VALUE_SHIFT                                          (12U)
#define EMIF_PHY_STATUS_1_PHY_REG_PHY_CTRL_DLL_SLAVE_VALUE_MASK                                           (0x3ffff000U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_PHY_CTRL_DLL_LOCK_0_SHIFT                                        (0U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_PHY_CTRL_DLL_LOCK_0_MASK                                         (0x00000001U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_PHY_CTRL_DLL_LOCK_1_SHIFT                                        (1U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_PHY_CTRL_DLL_LOCK_1_MASK                                         (0x00000002U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_0_SHIFT                                                 (2U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_0_MASK                                                  (0x00000004U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_1_SHIFT                                                 (3U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_1_MASK                                                  (0x00000008U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_2_SHIFT                                                 (4U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_2_MASK                                                  (0x00000010U)

#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_3_SHIFT                                                 (5U)
#define EMIF_PHY_STATUS_1_PHY_REG_STATUS_DLL_LOCK_3_MASK                                                  (0x00000020U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_0_SHIFT                                           (0U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_0_MASK                                            (0x0000000fU)

#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_1_SHIFT                                           (4U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_1_MASK                                            (0x000000f0U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_2_SHIFT                                           (8U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_2_MASK                                            (0x00000f00U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_3_SHIFT                                           (12U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDC_FIFO_RST_ERR_CNT_3_MASK                                            (0x0000f000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_0_SHIFT                                      (16U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_0_MASK                                       (0x00010000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_1_SHIFT                                      (17U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_1_MASK                                       (0x00020000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_2_SHIFT                                      (18U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_2_MASK                                       (0x00040000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_3_SHIFT                                      (19U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_MDLL_UNLOCK_STICKY_3_MASK                                       (0x00080000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_PHY_CTRL_MDLL_UNLOCK_STICKY_0_SHIFT                             (20U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_PHY_CTRL_MDLL_UNLOCK_STICKY_0_MASK                              (0x00100000U)

#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_PHY_CTRL_MDLL_UNLOCK_STICKY_1_SHIFT                             (21U)
#define EMIF_PHY_STATUS_20_PHY_REG_STATUS_PHY_CTRL_MDLL_UNLOCK_STICKY_1_MASK                              (0x00200000U)

#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_0_SHIFT                                   (22U)
#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_0_MASK                                    (0x00400000U)

#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_1_SHIFT                                   (23U)
#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_1_MASK                                    (0x00800000U)

#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_2_SHIFT                                   (24U)
#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_2_MASK                                    (0x01000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_3_SHIFT                                   (25U)
#define EMIF_PHY_STATUS_20_PHY_REG_FIFO_WE_IN_MISALIGNED_STICKY_3_MASK                                    (0x02000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_0_SHIFT                                                 (26U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_0_MASK                                                  (0x04000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_1_SHIFT                                                 (27U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_1_MASK                                                  (0x08000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_2_SHIFT                                                 (28U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_2_MASK                                                  (0x10000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_3_SHIFT                                                 (29U)
#define EMIF_PHY_STATUS_20_PHY_REG_RDLVL_INC_FAIL_3_MASK                                                  (0x20000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_WRLVL_INC_FAIL_0_SHIFT                                                 (30U)
#define EMIF_PHY_STATUS_20_PHY_REG_WRLVL_INC_FAIL_0_MASK                                                  (0x40000000U)

#define EMIF_PHY_STATUS_20_PHY_REG_WRLVL_INC_FAIL_1_SHIFT                                                 (31U)
#define EMIF_PHY_STATUS_20_PHY_REG_WRLVL_INC_FAIL_1_MASK                                                  (0x80000000U)

#define EMIF_PHY_STATUS_21_RESERVED_SHIFT                                                                 (6U)
#define EMIF_PHY_STATUS_21_RESERVED_MASK                                                                  (0xffffffc0U)

#define EMIF_PHY_STATUS_21_PHY_REG_WRLVL_INC_FAIL_2_SHIFT                                                 (0U)
#define EMIF_PHY_STATUS_21_PHY_REG_WRLVL_INC_FAIL_2_MASK                                                  (0x00000001U)

#define EMIF_PHY_STATUS_21_PHY_REG_WRLVL_INC_FAIL_3_SHIFT                                                 (1U)
#define EMIF_PHY_STATUS_21_PHY_REG_WRLVL_INC_FAIL_3_MASK                                                  (0x00000002U)

#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_0_SHIFT                                               (2U)
#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_0_MASK                                                (0x00000004U)

#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_1_SHIFT                                               (3U)
#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_1_MASK                                                (0x00000008U)

#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_2_SHIFT                                               (4U)
#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_2_MASK                                                (0x00000010U)

#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_3_SHIFT                                               (5U)
#define EMIF_PHY_STATUS_21_PHY_REG_GATELVL_INC_FAIL_3_MASK                                                (0x00000020U)

#define EMIF_EXT_PHY_CONTROL_1_RESERVED_SHIFT                                                             (30U)
#define EMIF_EXT_PHY_CONTROL_1_RESERVED_MASK                                                              (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_0_SHIFT                                               (0U)
#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_0_MASK                                                (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_1_SHIFT                                               (10U)
#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_1_MASK                                                (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_2_SHIFT                                               (20U)
#define EMIF_EXT_PHY_CONTROL_1_PHY_CTRL_SLAVE_RATIO_2_MASK                                                (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_1_SHADOW_RESERVED_SHIFT                                                      (30U)
#define EMIF_EXT_PHY_CONTROL_1_SHADOW_RESERVED_MASK                                                       (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_2_SHDW_SHIFT                                   (20U)
#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_2_SHDW_MASK                                    (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_1_SHDW_SHIFT                                   (10U)
#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_1_SHDW_MASK                                    (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_0_SHDW_SHIFT                                   (0U)
#define EMIF_EXT_PHY_CONTROL_1_SHADOW_PHY_CTRL_SLAVE_RATIO_0_SHDW_MASK                                    (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_0_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_0_0_MASK                                           (0x000007ffU)

#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_0_1_SHIFT                                          (11U)
#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_0_1_MASK                                           (0x003ff800U)

#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHIFT                                          (22U)
#define EMIF_EXT_PHY_CONTROL_2_PHY_FIFO_WE_SLAVE_RATIO_1_0_MASK                                           (0xffc00000U)

#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHDW_SHIFT                              (22U)
#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHDW_MASK                               (0xffc00000U)

#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_0_1_SHDW_SHIFT                              (11U)
#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_0_1_SHDW_MASK                               (0x003ff800U)

#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_0_0_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_2_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_0_0_SHDW_MASK                               (0x000007ffU)

#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_1_0_MASK                                           (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_1_1_SHIFT                                          (1U)
#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_1_1_MASK                                           (0x00000ffeU)

#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_2_0_SHIFT                                          (12U)
#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_2_0_MASK                                           (0x007ff000U)

#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHIFT                                          (23U)
#define EMIF_EXT_PHY_CONTROL_3_PHY_FIFO_WE_SLAVE_RATIO_2_1_MASK                                           (0xff800000U)

#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHDW_SHIFT                              (23U)
#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHDW_MASK                               (0xff800000U)

#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_0_SHDW_SHIFT                              (12U)
#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_0_SHDW_MASK                               (0x007ff000U)

#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_1_SHDW_SHIFT                              (1U)
#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_1_SHDW_MASK                               (0x00000ffeU)

#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_3_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_1_0_SHDW_MASK                               (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_4_RESERVED_SHIFT                                                             (24U)
#define EMIF_EXT_PHY_CONTROL_4_RESERVED_MASK                                                              (0xff000000U)

#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_2_1_MASK                                           (0x00000003U)

#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_3_0_SHIFT                                          (2U)
#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_3_0_MASK                                           (0x00001ffcU)

#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_3_1_SHIFT                                          (13U)
#define EMIF_EXT_PHY_CONTROL_4_PHY_FIFO_WE_SLAVE_RATIO_3_1_MASK                                           (0x00ffe000U)

#define EMIF_EXT_PHY_CONTROL_4_SHADOW_RESERVED_SHIFT                                                      (24U)
#define EMIF_EXT_PHY_CONTROL_4_SHADOW_RESERVED_MASK                                                       (0xff000000U)

#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_3_1_SHDW_SHIFT                              (13U)
#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_3_1_SHDW_MASK                               (0x00ffe000U)

#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_3_0_SHDW_SHIFT                              (2U)
#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_3_0_SHDW_MASK                               (0x00001ffcU)

#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_4_SHADOW_PHY_FIFO_WE_SLAVE_RATIO_2_1_SHDW_MASK                               (0x00000003U)

#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_0_0_SHIFT                                           (0U)
#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_0_0_MASK                                            (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_0_1_SHIFT                                           (10U)
#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_0_1_MASK                                            (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_1_0_SHIFT                                           (20U)
#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_1_0_MASK                                            (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_1_1_SHIFT                                           (30U)
#define EMIF_EXT_PHY_CONTROL_5_PHY_RD_DQS_SLAVE_RATIO_1_1_MASK                                            (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_1_SHDW_SHIFT                               (30U)
#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_1_SHDW_MASK                                (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_0_SHDW_SHIFT                               (20U)
#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_0_SHDW_MASK                                (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_0_1_SHDW_SHIFT                               (10U)
#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_0_1_SHDW_MASK                                (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_0_0_SHDW_SHIFT                               (0U)
#define EMIF_EXT_PHY_CONTROL_5_SHADOW_PHY_RD_DQS_SLAVE_RATIO_0_0_SHDW_MASK                                (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_1_1_SHIFT                                           (0U)
#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_1_1_MASK                                            (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_2_0_SHIFT                                           (8U)
#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_2_0_MASK                                            (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_2_1_SHIFT                                           (18U)
#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_2_1_MASK                                            (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_3_0_SHIFT                                           (28U)
#define EMIF_EXT_PHY_CONTROL_6_PHY_RD_DQS_SLAVE_RATIO_3_0_MASK                                            (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_0_SHDW_SHIFT                               (28U)
#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_0_SHDW_MASK                                (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_2_1_SHDW_SHIFT                               (18U)
#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_2_1_SHDW_MASK                                (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_2_0_SHDW_SHIFT                               (8U)
#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_2_0_SHDW_MASK                                (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_1_SHDW_SHIFT                               (0U)
#define EMIF_EXT_PHY_CONTROL_6_SHADOW_PHY_RD_DQS_SLAVE_RATIO_1_1_SHDW_MASK                                (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_7_RESERVED_SHIFT                                                             (16U)
#define EMIF_EXT_PHY_CONTROL_7_RESERVED_MASK                                                              (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_7_PHY_RD_DQS_SLAVE_RATIO_3_0_SHIFT                                           (0U)
#define EMIF_EXT_PHY_CONTROL_7_PHY_RD_DQS_SLAVE_RATIO_3_0_MASK                                            (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_7_PHY_RD_DQS_SLAVE_RATIO_3_1_SHIFT                                           (6U)
#define EMIF_EXT_PHY_CONTROL_7_PHY_RD_DQS_SLAVE_RATIO_3_1_MASK                                            (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_7_SHADOW_RESERVED_SHIFT                                                      (16U)
#define EMIF_EXT_PHY_CONTROL_7_SHADOW_RESERVED_MASK                                                       (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_7_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_1_SHDW_SHIFT                               (6U)
#define EMIF_EXT_PHY_CONTROL_7_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_1_SHDW_MASK                                (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_7_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_0_SHDW_SHIFT                               (0U)
#define EMIF_EXT_PHY_CONTROL_7_SHADOW_PHY_RD_DQS_SLAVE_RATIO_3_0_SHDW_MASK                                (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_0_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_0_0_MASK                                           (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_0_1_SHIFT                                          (10U)
#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_0_1_MASK                                           (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_1_0_SHIFT                                          (20U)
#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_1_0_MASK                                           (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_1_1_SHIFT                                          (30U)
#define EMIF_EXT_PHY_CONTROL_8_PHY_WR_DATA_SLAVE_RATIO_1_1_MASK                                           (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_1_SHDW_SHIFT                              (30U)
#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_1_SHDW_MASK                               (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_0_SHDW_SHIFT                              (20U)
#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_0_SHDW_MASK                               (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_0_1_SHDW_SHIFT                              (10U)
#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_0_1_SHDW_MASK                               (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_0_0_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_8_SHADOW_PHY_WR_DATA_SLAVE_RATIO_0_0_SHDW_MASK                               (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_1_1_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_1_1_MASK                                           (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_2_0_SHIFT                                          (8U)
#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_2_0_MASK                                           (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_2_1_SHIFT                                          (18U)
#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_2_1_MASK                                           (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_3_0_SHIFT                                          (28U)
#define EMIF_EXT_PHY_CONTROL_9_PHY_WR_DATA_SLAVE_RATIO_3_0_MASK                                           (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_1_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_1_1_SHDW_MASK                               (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_2_0_SHDW_SHIFT                              (8U)
#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_2_0_SHDW_MASK                               (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_2_1_SHDW_SHIFT                              (18U)
#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_2_1_SHDW_MASK                               (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_0_SHDW_SHIFT                              (28U)
#define EMIF_EXT_PHY_CONTROL_9_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_0_SHDW_MASK                               (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_10_RESERVED_SHIFT                                                            (16U)
#define EMIF_EXT_PHY_CONTROL_10_RESERVED_MASK                                                             (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_10_PHY_WR_DATA_SLAVE_RATIO_3_0_SHIFT                                         (0U)
#define EMIF_EXT_PHY_CONTROL_10_PHY_WR_DATA_SLAVE_RATIO_3_0_MASK                                          (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_10_PHY_WR_DATA_SLAVE_RATIO_3_1_SHIFT                                         (6U)
#define EMIF_EXT_PHY_CONTROL_10_PHY_WR_DATA_SLAVE_RATIO_3_1_MASK                                          (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_0_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_0_0_MASK                                           (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_0_1_SHIFT                                          (10U)
#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_0_1_MASK                                           (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_1_0_SHIFT                                          (20U)
#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_1_0_MASK                                           (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_1_1_SHIFT                                          (30U)
#define EMIF_EXT_PHY_CONTROL_11_PHY_WR_DQS_SLAVE_RATIO_1_1_MASK                                           (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_1_SHDW_SHIFT                              (30U)
#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_1_SHDW_MASK                               (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_0_SHDW_SHIFT                              (20U)
#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_0_SHDW_MASK                               (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_0_1_SHDW_SHIFT                              (10U)
#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_0_1_SHDW_MASK                               (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_0_0_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_11_SHADOW_PHY_WR_DQS_SLAVE_RATIO_0_0_SHDW_MASK                               (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_1_1_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_1_1_MASK                                           (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_2_0_SHIFT                                          (8U)
#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_2_0_MASK                                           (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_2_1_SHIFT                                          (18U)
#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_2_1_MASK                                           (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_3_0_SHIFT                                          (28U)
#define EMIF_EXT_PHY_CONTROL_12_PHY_WR_DQS_SLAVE_RATIO_3_0_MASK                                           (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_0_SHDW_SHIFT                              (28U)
#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_0_SHDW_MASK                               (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_2_1_SHDW_SHIFT                              (18U)
#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_2_1_SHDW_MASK                               (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_2_0_SHDW_SHIFT                              (8U)
#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_2_0_SHDW_MASK                               (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_1_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_12_SHADOW_PHY_WR_DQS_SLAVE_RATIO_1_1_SHDW_MASK                               (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_13_RESERVED_SHIFT                                                            (16U)
#define EMIF_EXT_PHY_CONTROL_13_RESERVED_MASK                                                             (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_13_PHY_WR_DQS_SLAVE_RATIO_3_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_13_PHY_WR_DQS_SLAVE_RATIO_3_0_MASK                                           (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_13_PHY_WR_DQS_SLAVE_RATIO_3_1_SHIFT                                          (6U)
#define EMIF_EXT_PHY_CONTROL_13_PHY_WR_DQS_SLAVE_RATIO_3_1_MASK                                           (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_13_SHADOW_RESERVED_SHIFT                                                     (16U)
#define EMIF_EXT_PHY_CONTROL_13_SHADOW_RESERVED_MASK                                                      (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_13_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_0_SHDW_SHIFT                              (0U)
#define EMIF_EXT_PHY_CONTROL_13_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_0_SHDW_MASK                               (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_13_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_1_SHDW_SHIFT                              (6U)
#define EMIF_EXT_PHY_CONTROL_13_SHADOW_PHY_WR_DQS_SLAVE_RATIO_3_1_SHDW_MASK                               (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_14_RESERVED_SHIFT                                                            (21U)
#define EMIF_EXT_PHY_CONTROL_14_RESERVED_MASK                                                             (0x00e00000U)

#define EMIF_EXT_PHY_CONTROL_14_RESERVED1_SHIFT                                                           (9U)
#define EMIF_EXT_PHY_CONTROL_14_RESERVED1_MASK                                                            (0x00000e00U)

#define EMIF_EXT_PHY_CONTROL_14_PHY_CTRL_SLAVE_DELAY_SHIFT                                                (0U)
#define EMIF_EXT_PHY_CONTROL_14_PHY_CTRL_SLAVE_DELAY_MASK                                                 (0x000001ffU)

#define EMIF_EXT_PHY_CONTROL_14_PHY_FIFO_WE_IN_DELAY_SHIFT                                                (12U)
#define EMIF_EXT_PHY_CONTROL_14_PHY_FIFO_WE_IN_DELAY_MASK                                                 (0x001ff000U)

#define EMIF_EXT_PHY_CONTROL_14_PHY_RD_DQS_SLAVE_DELAY_SHIFT                                              (24U)
#define EMIF_EXT_PHY_CONTROL_14_PHY_RD_DQS_SLAVE_DELAY_MASK                                               (0xff000000U)

#define EMIF_EXT_PHY_CONTROL_14_SHADOW_RESERVED_SHIFT                                                     (21U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW_RESERVED_MASK                                                      (0x00e00000U)

#define EMIF_EXT_PHY_CONTROL_14_SHADOW_RESERVED1_SHIFT                                                    (9U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW_RESERVED1_MASK                                                     (0x00000e00U)

#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_FIFO_WE_IN_DELAY_SHDW_SHIFT                                    (12U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_FIFO_WE_IN_DELAY_SHDW_MASK                                     (0x001ff000U)

#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_CTRL_SLAVE_DELAY_SHDW_SHIFT                                    (0U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_CTRL_SLAVE_DELAY_SHDW_MASK                                     (0x000001ffU)

#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_RD_DQS_SLAVE_DELAY_SHDW_SHIFT                                  (24U)
#define EMIF_EXT_PHY_CONTROL_14_SHADOW_PHY_RD_DQS_SLAVE_DELAY_SHDW_MASK                                   (0xff000000U)

#define EMIF_EXT_PHY_CONTROL_15_RESERVED_SHIFT                                                            (1U)
#define EMIF_EXT_PHY_CONTROL_15_RESERVED_MASK                                                             (0x0000000eU)

#define EMIF_EXT_PHY_CONTROL_15_RESERVED1_SHIFT                                                           (13U)
#define EMIF_EXT_PHY_CONTROL_15_RESERVED1_MASK                                                            (0x0000e000U)

#define EMIF_EXT_PHY_CONTROL_15_PHY_RD_DQS_SLAVE_DELAY_SHIFT                                              (0U)
#define EMIF_EXT_PHY_CONTROL_15_PHY_RD_DQS_SLAVE_DELAY_MASK                                               (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_15_PHY_WR_DQS_SLAVE_DELAY_SHIFT                                              (4U)
#define EMIF_EXT_PHY_CONTROL_15_PHY_WR_DQS_SLAVE_DELAY_MASK                                               (0x00001ff0U)

#define EMIF_EXT_PHY_CONTROL_15_PHY_WR_DATA_SLAVE_DELAY_SHIFT                                             (16U)
#define EMIF_EXT_PHY_CONTROL_15_PHY_WR_DATA_SLAVE_DELAY_MASK                                              (0x01ff0000U)

#define EMIF_EXT_PHY_CONTROL_15_RESERVED2_SHIFT                                                           (25U)
#define EMIF_EXT_PHY_CONTROL_15_RESERVED2_MASK                                                            (0xfe000000U)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED_SHIFT                                                     (1U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED_MASK                                                      (0x0000000eU)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED1_SHIFT                                                    (13U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED1_MASK                                                     (0x0000e000U)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED2_SHIFT                                                    (25U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_RESERVED2_MASK                                                     (0xfe000000U)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_RD_DQS_SLAVE_DELAY_SHDW_SHIFT                                  (0U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_RD_DQS_SLAVE_DELAY_SHDW_MASK                                   (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_WR_DQS_SLAVE_DELAY_SHDW_SHIFT                                  (4U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_WR_DQS_SLAVE_DELAY_SHDW_MASK                                   (0x00001ff0U)

#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_WR_DATA_SLAVE_DELAY_SHDW_SHIFT                                 (16U)
#define EMIF_EXT_PHY_CONTROL_15_SHADOW_PHY_WR_DATA_SLAVE_DELAY_SHDW_MASK                                  (0x01ff0000U)

#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_0_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_0_MASK                                                      (0x0000007fU)

#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_1_SHIFT                                                     (7U)
#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_1_MASK                                                      (0x00003f80U)

#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_2_SHIFT                                                     (14U)
#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_2_MASK                                                      (0x001fc000U)

#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_3_SHIFT                                                     (21U)
#define EMIF_EXT_PHY_CONTROL_16_PHY_DQ_OFFSET_3_MASK                                                      (0x0fe00000U)

#define EMIF_EXT_PHY_CONTROL_16_RESERVED_SHIFT                                                            (28U)
#define EMIF_EXT_PHY_CONTROL_16_RESERVED_MASK                                                             (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_16_SHADOW_RESERVED_SHIFT                                                     (28U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW_RESERVED_MASK                                                      (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_0_SHDW_SHIFT                                         (0U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_0_SHDW_MASK                                          (0x0000007fU)

#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_1_SHDW_SHIFT                                         (7U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_1_SHDW_MASK                                          (0x00003f80U)

#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_2_SHDW_SHIFT                                         (14U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_2_SHDW_MASK                                          (0x001fc000U)

#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_3_SHDW_SHIFT                                         (21U)
#define EMIF_EXT_PHY_CONTROL_16_SHADOW_PHY_DQ_OFFSET_3_SHDW_MASK                                          (0x0fe00000U)

#define EMIF_EXT_PHY_CONTROL_17_PHY_USE_RANK0_DELAYS_SHIFT                                                (0U)
#define EMIF_EXT_PHY_CONTROL_17_PHY_USE_RANK0_DELAYS_MASK                                                 (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_17_PHY_GATELVL_INIT_MODE_SHIFT                                               (1U)
#define EMIF_EXT_PHY_CONTROL_17_PHY_GATELVL_INIT_MODE_MASK                                                (0x00000002U)

#define EMIF_EXT_PHY_CONTROL_17_RESERVED_SHIFT                                                            (2U)
#define EMIF_EXT_PHY_CONTROL_17_RESERVED_MASK                                                             (0xfffffffcU)

#define EMIF_EXT_PHY_CONTROL_17_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_17_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_0_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_0_0_MASK                                           (0x000007ffU)

#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_0_1_SHIFT                                          (11U)
#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_0_1_MASK                                           (0x003ff800U)

#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_1_0_SHIFT                                          (22U)
#define EMIF_EXT_PHY_CONTROL_18_PHY_GATELVL_INIT_RATIO_1_0_MASK                                           (0xffc00000U)

#define EMIF_EXT_PHY_CONTROL_18_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_18_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_1_0_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_1_0_MASK                                           (0x00000001U)

#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_1_1_SHIFT                                          (1U)
#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_1_1_MASK                                           (0x00001ffeU)

#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_2_0_SHIFT                                          (12U)
#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_2_0_MASK                                           (0x007ff000U)

#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_2_1_SHIFT                                          (23U)
#define EMIF_EXT_PHY_CONTROL_19_PHY_GATELVL_INIT_RATIO_2_1_MASK                                           (0xff800000U)

#define EMIF_EXT_PHY_CONTROL_19_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_19_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_20_RESERVED_SHIFT                                                            (24U)
#define EMIF_EXT_PHY_CONTROL_20_RESERVED_MASK                                                             (0xff000000U)

#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_2_1_SHIFT                                          (0U)
#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_2_1_MASK                                           (0x00000003U)

#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_3_0_SHIFT                                          (2U)
#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_3_0_MASK                                           (0x00001ffcU)

#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_3_1_SHIFT                                          (13U)
#define EMIF_EXT_PHY_CONTROL_20_PHY_GATELVL_INIT_RATIO_3_1_MASK                                           (0x00ffe000U)

#define EMIF_EXT_PHY_CONTROL_20_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_20_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_0_0_SHIFT                                            (0U)
#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_0_0_MASK                                             (0x000003ffU)

#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_0_1_SHIFT                                            (10U)
#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_0_1_MASK                                             (0x000ffc00U)

#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_1_0_SHIFT                                            (20U)
#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_1_0_MASK                                             (0x3ff00000U)

#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_1_1_SHIFT                                            (30U)
#define EMIF_EXT_PHY_CONTROL_21_PHY_WRLVL_INIT_RATIO_1_1_MASK                                             (0xc0000000U)

#define EMIF_EXT_PHY_CONTROL_21_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_21_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_22_RESERVED_SHIFT                                                            (28U)
#define EMIF_EXT_PHY_CONTROL_22_RESERVED_MASK                                                             (0xf0000000U)

#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_1_1_SHIFT                                            (0U)
#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_1_1_MASK                                             (0x000000ffU)

#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_2_0_SHIFT                                            (8U)
#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_2_0_MASK                                             (0x0003ff00U)

#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_2_1_SHIFT                                            (18U)
#define EMIF_EXT_PHY_CONTROL_22_PHY_WRLVL_INIT_RATIO_2_1_MASK                                             (0x0ffc0000U)

#define EMIF_EXT_PHY_CONTROL_22_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_22_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_23_PHY_WRLVL_INT_RATIO_3_0_SHIFT                                             (0U)
#define EMIF_EXT_PHY_CONTROL_23_PHY_WRLVL_INT_RATIO_3_0_MASK                                              (0x0000003fU)

#define EMIF_EXT_PHY_CONTROL_23_PHY_WRLVL_INIT_RATIO_3_1_SHIFT                                            (6U)
#define EMIF_EXT_PHY_CONTROL_23_PHY_WRLVL_INIT_RATIO_3_1_MASK                                             (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_23_RESERVED_SHIFT                                                            (16U)
#define EMIF_EXT_PHY_CONTROL_23_RESERVED_MASK                                                             (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_23_SHADOW_RESERVED_SHIFT                                                     (0U)
#define EMIF_EXT_PHY_CONTROL_23_SHADOW_RESERVED_MASK                                                      (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_24_PHY_GATELVL_NUM_OF_DQ0_SHIFT                                              (0U)
#define EMIF_EXT_PHY_CONTROL_24_PHY_GATELVL_NUM_OF_DQ0_MASK                                               (0x0000000fU)

#define EMIF_EXT_PHY_CONTROL_24_PHY_WRLVL_NUM_OF_DQ0_SHIFT                                                (4U)
#define EMIF_EXT_PHY_CONTROL_24_PHY_WRLVL_NUM_OF_DQ0_MASK                                                 (0x000000f0U)

#define EMIF_EXT_PHY_CONTROL_24_PHY_FIFO_WE_IN_MISALIGNED_CLR_SHIFT                                       (8U)
#define EMIF_EXT_PHY_CONTROL_24_PHY_FIFO_WE_IN_MISALIGNED_CLR_MASK                                        (0x00000100U)

#define EMIF_EXT_PHY_CONTROL_24_PHY_RDC_FIFO_RST_ERR_CNT_CLR_SHIFT                                        (10U)
#define EMIF_EXT_PHY_CONTROL_24_PHY_RDC_FIFO_RST_ERR_CNT_CLR_MASK                                         (0x00000400U)

#define EMIF_EXT_PHY_CONTROL_24_PHY_MDLL_UNLOCK_CLEAR_SHIFT                                               (9U)
#define EMIF_EXT_PHY_CONTROL_24_PHY_MDLL_UNLOCK_CLEAR_MASK                                                (0x00000200U)

#define EMIF_EXT_PHY_CONTROL_24_RESERVED_SHIFT                                                            (11U)
#define EMIF_EXT_PHY_CONTROL_24_RESERVED_MASK                                                             (0xfffff800U)

#define EMIF_EXT_PHY_CONTROL_24_SHADOW_RESERVED_SHIFT                                                     (4U)
#define EMIF_EXT_PHY_CONTROL_24_SHADOW_RESERVED_MASK                                                      (0xfffffff0U)

#define EMIF_EXT_PHY_CONTROL_24_SHADOW_PHY_GATELVL_NUM_OF_DQ0_SHDW_SHIFT                                  (0U)
#define EMIF_EXT_PHY_CONTROL_24_SHADOW_PHY_GATELVL_NUM_OF_DQ0_SHDW_MASK                                   (0x0000000fU)

#define EMIF_MISC_REG_DLL_CALIB_OS_SHIFT                                                                  (0U)
#define EMIF_MISC_REG_DLL_CALIB_OS_MASK                                                                   (0x00000001U)

#define EMIF_MISC_REG_RESERVED_SHIFT                                                                      (1U)
#define EMIF_MISC_REG_RESERVED_MASK                                                                       (0xfffffffeU)

#define EMIF_REVISION_REVISION_SHIFT                                                                      (0U)
#define EMIF_REVISION_REVISION_MASK                                                                       (0xffffffffU)

#define EMIF_EXT_PHY_CONTROL_10_SHADOW_RESERVED_SHIFT                                                     (16U)
#define EMIF_EXT_PHY_CONTROL_10_SHADOW_RESERVED_MASK                                                      (0xffff0000U)

#define EMIF_EXT_PHY_CONTROL_10_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_1_SHDW_SHIFT                             (6U)
#define EMIF_EXT_PHY_CONTROL_10_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_1_SHDW_MASK                              (0x0000ffc0U)

#define EMIF_EXT_PHY_CONTROL_10_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_0_SHDW_SHIFT                             (0U)
#define EMIF_EXT_PHY_CONTROL_10_SHADOW_PHY_WR_DATA_SLAVE_RATIO_3_0_SHDW_MASK                              (0x0000003fU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_EMIF_H_ */
