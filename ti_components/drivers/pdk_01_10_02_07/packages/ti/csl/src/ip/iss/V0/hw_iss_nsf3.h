/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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

#ifndef HW_ISS_NSF3_H_
#define HW_ISS_NSF3_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define NSF3V_SYSCONFIG                                             (0x10U)
#define NSF3V_CTRL                                                  (0x18U)
#define NSF3V_CFG                                                   (0x1cU)
#define NSF3V_DIM                                                   (0x20U)
#define NSF3V_VPOUT_CTRL                                            (0x24U)
#define NSF3V_SHD_ST                                                (0x28U)
#define NSF3V_SHD_HA                                                (0x2cU)
#define NSF3V_SHD_VA                                                (0x30U)
#define NSF3V_SHD_HSVS                                              (0x34U)
#define NSF3V_SHD_ADJ                                               (0x38U)
#define NSF3V_SHD_MAXG                                              (0x3cU)
#define NSF3V_TN_C00                                                (0x40U)
#define NSF3V_TN_C01                                                (0x44U)
#define NSF3V_TN_C02                                                (0x48U)
#define NSF3V_TN_C03                                                (0x4cU)
#define NSF3V_TN_C04                                                (0x50U)
#define NSF3V_TN_C05                                                (0x54U)
#define NSF3V_TN_C10                                                (0x58U)
#define NSF3V_TN_C11                                                (0x5cU)
#define NSF3V_TN_C12                                                (0x60U)
#define NSF3V_TN_C13                                                (0x64U)
#define NSF3V_TN_C14                                                (0x68U)
#define NSF3V_TN_C15                                                (0x6cU)
#define NSF3V_TN_C20                                                (0x70U)
#define NSF3V_TN_C21                                                (0x74U)
#define NSF3V_TN_C22                                                (0x78U)
#define NSF3V_TN_C23                                                (0x7cU)
#define NSF3V_TN_C24                                                (0x80U)
#define NSF3V_TN_C25                                                (0x84U)
#define NSF3V_TN_C30                                                (0x88U)
#define NSF3V_TN_C31                                                (0x8cU)
#define NSF3V_TN_C32                                                (0x90U)
#define NSF3V_TN_C33                                                (0x94U)
#define NSF3V_TN_C34                                                (0x98U)
#define NSF3V_TN_C35                                                (0x9cU)
#define NSF3V_TN_SCALE                                              (0xa0U)
#define NSF3V_THR_KNEE                                              (0xa4U)
#define NSF3V_SUP_C00                                               (0xa8U)
#define NSF3V_SUP_C01                                               (0xacU)
#define NSF3V_SUP_C10                                               (0xb0U)
#define NSF3V_SUP_C11                                               (0xb4U)
#define NSF3V_SUP_C20                                               (0xb8U)
#define NSF3V_SUP_C21                                               (0xbcU)
#define NSF3V_SUP_C30                                               (0xc0U)
#define NSF3V_SUP_C31                                               (0xc4U)
#define NSF3V_EE_C00                                                (0xc8U)
#define NSF3V_EE_C01                                                (0xccU)
#define NSF3V_EE_C02                                                (0xd0U)
#define NSF3V_EE_C10                                                (0xd4U)
#define NSF3V_EE_C11                                                (0xd8U)
#define NSF3V_EE_C12                                                (0xdcU)
#define NSF3V_EE_C20                                                (0xe0U)
#define NSF3V_EE_C21                                                (0xe4U)
#define NSF3V_EE_C22                                                (0xe8U)
#define NSF3V_EE_C30                                                (0xecU)
#define NSF3V_EE_C31                                                (0xf0U)
#define NSF3V_EE_C32                                                (0xf4U)
#define NSF3V_DS_THR                                                (0xf8U)
#define NSF3V_DS_SLOPE                                              (0xfcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define NSF3V_SYSCONFIG_SOFTRESET_SHIFT                                                 (0U)
#define NSF3V_SYSCONFIG_SOFTRESET_MASK                                                  (0x00000001U)

#define NSF3V_SYSCONFIG_RESERVED1_SHIFT                                                 (1U)
#define NSF3V_SYSCONFIG_RESERVED1_MASK                                                  (0xfffffffeU)

#define NSF3V_CTRL_EN_SHIFT                                                             (0U)
#define NSF3V_CTRL_EN_MASK                                                              (0x00000001U)

#define NSF3V_CTRL_RESERVED_SHIFT                                                       (1U)
#define NSF3V_CTRL_RESERVED_MASK                                                        (0xfffffffeU)

#define NSF3V_CFG_EE_EN_SHIFT                                                           (8U)
#define NSF3V_CFG_EE_EN_MASK                                                            (0x00000100U)

#define NSF3V_CFG_SUPPRS_ALL_SHIFT                                                      (16U)
#define NSF3V_CFG_SUPPRS_ALL_MASK                                                       (0x00010000U)

#define NSF3V_CFG_SHD_EN_SHIFT                                                          (9U)
#define NSF3V_CFG_SHD_EN_MASK                                                           (0x00000200U)

#define NSF3V_CFG_DESAT_EN_SHIFT                                                        (10U)
#define NSF3V_CFG_DESAT_EN_MASK                                                         (0x00000400U)

#define NSF3V_CFG_MODE_SHIFT                                                            (0U)
#define NSF3V_CFG_MODE_MASK                                                             (0x0000000fU)

#define NSF3V_CFG_LBORDER_REP_SHIFT                                                     (11U)
#define NSF3V_CFG_LBORDER_REP_MASK                                                      (0x00000800U)

#define NSF3V_CFG_RBORDER_REP_SHIFT                                                     (12U)
#define NSF3V_CFG_RBORDER_REP_MASK                                                      (0x00001000U)

#define NSF3V_CFG_TBORDER_REP_SHIFT                                                     (13U)
#define NSF3V_CFG_TBORDER_REP_MASK                                                      (0x00002000U)

#define NSF3V_CFG_BBORDER_REP_SHIFT                                                     (14U)
#define NSF3V_CFG_BBORDER_REP_MASK                                                      (0x00004000U)

#define NSF3V_CFG_BYPASS_W_DELAY_SHIFT                                                  (15U)
#define NSF3V_CFG_BYPASS_W_DELAY_MASK                                                   (0x00008000U)

#define NSF3V_CFG_FORCE_CLKON_SHIFT                                                     (17U)
#define NSF3V_CFG_FORCE_CLKON_MASK                                                      (0x00020000U)

#define NSF3V_CFG_RESERVED2_SHIFT                                                       (18U)
#define NSF3V_CFG_RESERVED2_MASK                                                        (0xfffc0000U)

#define NSF3V_CFG_ONESHOT_SHIFT                                                         (7U)
#define NSF3V_CFG_ONESHOT_MASK                                                          (0x00000080U)

#define NSF3V_CFG_RESERVED_SHIFT                                                        (4U)
#define NSF3V_CFG_RESERVED_MASK                                                         (0x00000030U)

#define NSF3V_CFG_HARD_THR_EN_422UV_SHIFT                                               (6U)
#define NSF3V_CFG_HARD_THR_EN_422UV_MASK                                                (0x00000040U)

#define NSF3V_DIM_IW_SHIFT                                                              (0U)
#define NSF3V_DIM_IW_MASK                                                               (0x00003fffU)

#define NSF3V_DIM_IH_SHIFT                                                              (16U)
#define NSF3V_DIM_IH_MASK                                                               (0x3fff0000U)

#define NSF3V_DIM_RESERVED_SHIFT                                                        (14U)
#define NSF3V_DIM_RESERVED_MASK                                                         (0x0000c000U)

#define NSF3V_DIM_RESERVED1_SHIFT                                                       (30U)
#define NSF3V_DIM_RESERVED1_MASK                                                        (0xc0000000U)

#define NSF3V_VPOUT_CTRL_PCLK_SHIFT                                                     (0U)
#define NSF3V_VPOUT_CTRL_PCLK_MASK                                                      (0x0000ffffU)

#define NSF3V_VPOUT_CTRL_RESERVED_SHIFT                                                 (16U)
#define NSF3V_VPOUT_CTRL_RESERVED_MASK                                                  (0xffff0000U)

#define NSF3V_SHD_ST_X_SHIFT                                                            (0U)
#define NSF3V_SHD_ST_X_MASK                                                             (0x00003fffU)

#define NSF3V_SHD_ST_Y_SHIFT                                                            (16U)
#define NSF3V_SHD_ST_Y_MASK                                                             (0x3fff0000U)

#define NSF3V_SHD_ST_RESERVED_SHIFT                                                     (14U)
#define NSF3V_SHD_ST_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_SHD_ST_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_SHD_ST_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_SHD_HA_HA1_SHIFT                                                          (0U)
#define NSF3V_SHD_HA_HA1_MASK                                                           (0x00001fffU)

#define NSF3V_SHD_HA_HA2_SHIFT                                                          (16U)
#define NSF3V_SHD_HA_HA2_MASK                                                           (0x1fff0000U)

#define NSF3V_SHD_HA_RESERVED_SHIFT                                                     (13U)
#define NSF3V_SHD_HA_RESERVED_MASK                                                      (0x0000e000U)

#define NSF3V_SHD_HA_RESERVED1_SHIFT                                                    (29U)
#define NSF3V_SHD_HA_RESERVED1_MASK                                                     (0xe0000000U)

#define NSF3V_SHD_VA_VA1_SHIFT                                                          (0U)
#define NSF3V_SHD_VA_VA1_MASK                                                           (0x00001fffU)

#define NSF3V_SHD_VA_VA2_SHIFT                                                          (16U)
#define NSF3V_SHD_VA_VA2_MASK                                                           (0x1fff0000U)

#define NSF3V_SHD_VA_RESERVED_SHIFT                                                     (13U)
#define NSF3V_SHD_VA_RESERVED_MASK                                                      (0x0000e000U)

#define NSF3V_SHD_VA_RESERVED1_SHIFT                                                    (29U)
#define NSF3V_SHD_VA_RESERVED1_MASK                                                     (0xe0000000U)

#define NSF3V_SHD_HSVS_S0_SHIFT                                                         (0U)
#define NSF3V_SHD_HSVS_S0_MASK                                                          (0x0000000fU)

#define NSF3V_SHD_HSVS_HS1_SHIFT                                                        (4U)
#define NSF3V_SHD_HSVS_HS1_MASK                                                         (0x000000f0U)

#define NSF3V_SHD_HSVS_HS2_SHIFT                                                        (8U)
#define NSF3V_SHD_HSVS_HS2_MASK                                                         (0x00000f00U)

#define NSF3V_SHD_HSVS_HCS_SHIFT                                                        (12U)
#define NSF3V_SHD_HSVS_HCS_MASK                                                         (0x00003000U)

#define NSF3V_SHD_HSVS_VS2_SHIFT                                                        (24U)
#define NSF3V_SHD_HSVS_VS2_MASK                                                         (0x0f000000U)

#define NSF3V_SHD_HSVS_VS1_SHIFT                                                        (20U)
#define NSF3V_SHD_HSVS_VS1_MASK                                                         (0x00f00000U)

#define NSF3V_SHD_HSVS_VCS_SHIFT                                                        (28U)
#define NSF3V_SHD_HSVS_VCS_MASK                                                         (0x30000000U)

#define NSF3V_SHD_HSVS_RESERVED_SHIFT                                                   (14U)
#define NSF3V_SHD_HSVS_RESERVED_MASK                                                    (0x000fc000U)

#define NSF3V_SHD_HSVS_RESERVED1_SHIFT                                                  (30U)
#define NSF3V_SHD_HSVS_RESERVED1_MASK                                                   (0xc0000000U)

#define NSF3V_SHD_ADJ_GADJ_SHIFT                                                        (0U)
#define NSF3V_SHD_ADJ_GADJ_MASK                                                         (0x000000ffU)

#define NSF3V_SHD_ADJ_OADJ_SHIFT                                                        (16U)
#define NSF3V_SHD_ADJ_OADJ_MASK                                                         (0x1fff0000U)

#define NSF3V_SHD_ADJ_RESERVED_SHIFT                                                    (8U)
#define NSF3V_SHD_ADJ_RESERVED_MASK                                                     (0x0000ff00U)

#define NSF3V_SHD_ADJ_RESERVED1_SHIFT                                                   (29U)
#define NSF3V_SHD_ADJ_RESERVED1_MASK                                                    (0xe0000000U)

#define NSF3V_SHD_MAXG_SHIFT                                                            (0U)
#define NSF3V_SHD_MAXG_MASK                                                             (0x000001ffU)

#define NSF3V_SHD_MAXG_RESERVED_SHIFT                                                   (9U)
#define NSF3V_SHD_MAXG_RESERVED_MASK                                                    (0xfffffe00U)

#define NSF3V_TN_C00_S0_X_SHIFT                                                         (0U)
#define NSF3V_TN_C00_S0_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C00_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C00_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C00_S0_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C00_S0_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C00_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C00_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C01_S0_S_SHIFT                                                         (0U)
#define NSF3V_TN_C01_S0_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C01_S1_X_SHIFT                                                         (16U)
#define NSF3V_TN_C01_S1_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C01_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C01_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C01_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C01_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C02_S1_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C02_S1_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C02_S1_S_SHIFT                                                         (16U)
#define NSF3V_TN_C02_S1_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C02_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C02_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C02_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C02_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C03_S2_X_SHIFT                                                         (0U)
#define NSF3V_TN_C03_S2_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C03_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C03_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C03_S2_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C03_S2_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C03_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C03_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C04_S2_S_SHIFT                                                         (0U)
#define NSF3V_TN_C04_S2_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C04_S3_X_SHIFT                                                         (16U)
#define NSF3V_TN_C04_S3_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C04_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C04_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C04_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C04_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C05_S3_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C05_S3_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C05_S3_S_SHIFT                                                         (16U)
#define NSF3V_TN_C05_S3_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C05_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C05_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C05_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C05_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C10_S0_X_SHIFT                                                         (0U)
#define NSF3V_TN_C10_S0_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C10_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C10_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C10_S0_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C10_S0_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C10_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C10_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C11_S0_S_SHIFT                                                         (0U)
#define NSF3V_TN_C11_S0_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C11_S1_X_SHIFT                                                         (16U)
#define NSF3V_TN_C11_S1_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C11_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C11_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C11_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C11_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C12_S1_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C12_S1_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C12_S1_S_SHIFT                                                         (16U)
#define NSF3V_TN_C12_S1_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C12_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C12_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C12_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C12_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C13_S2_X_SHIFT                                                         (0U)
#define NSF3V_TN_C13_S2_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C13_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C13_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C13_S2_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C13_S2_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C13_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C13_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C14_S2_S_SHIFT                                                         (0U)
#define NSF3V_TN_C14_S2_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C14_S3_X_SHIFT                                                         (16U)
#define NSF3V_TN_C14_S3_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C14_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C14_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C14_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C14_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C15_S3_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C15_S3_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C15_S3_S_SHIFT                                                         (16U)
#define NSF3V_TN_C15_S3_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C15_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C15_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C15_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C15_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C20_S0_X_SHIFT                                                         (0U)
#define NSF3V_TN_C20_S0_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C20_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C20_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C20_S0_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C20_S0_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C20_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C20_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C21_S0_S_SHIFT                                                         (0U)
#define NSF3V_TN_C21_S0_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C21_S1_X_SHIFT                                                         (16U)
#define NSF3V_TN_C21_S1_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C21_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C21_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C21_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C21_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C22_S1_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C22_S1_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C22_S1_S_SHIFT                                                         (16U)
#define NSF3V_TN_C22_S1_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C22_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C22_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C22_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C22_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C23_S2_X_SHIFT                                                         (0U)
#define NSF3V_TN_C23_S2_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C23_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C23_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C23_S2_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C23_S2_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C23_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C23_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C24_S2_S_SHIFT                                                         (0U)
#define NSF3V_TN_C24_S2_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C24_S3_X_SHIFT                                                         (16U)
#define NSF3V_TN_C24_S3_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C24_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C24_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C24_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C24_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C25_S3_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C25_S3_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C25_S3_S_SHIFT                                                         (16U)
#define NSF3V_TN_C25_S3_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C25_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C25_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C25_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C25_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C30_S0_X_SHIFT                                                         (0U)
#define NSF3V_TN_C30_S0_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C30_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C30_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C30_S0_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C30_S0_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C30_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C30_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C31_S0_S_SHIFT                                                         (0U)
#define NSF3V_TN_C31_S0_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C31_S1_X_SHIFT                                                         (16U)
#define NSF3V_TN_C31_S1_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C31_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C31_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C31_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C31_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C32_S1_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C32_S1_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C32_S1_S_SHIFT                                                         (16U)
#define NSF3V_TN_C32_S1_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C32_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C32_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C32_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C32_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_C33_S2_X_SHIFT                                                         (0U)
#define NSF3V_TN_C33_S2_X_MASK                                                          (0x00000fffU)

#define NSF3V_TN_C33_RESERVED_SHIFT                                                     (12U)
#define NSF3V_TN_C33_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_TN_C33_S2_Y_SHIFT                                                         (16U)
#define NSF3V_TN_C33_S2_Y_MASK                                                          (0x07ff0000U)

#define NSF3V_TN_C33_RESERVED1_SHIFT                                                    (27U)
#define NSF3V_TN_C33_RESERVED1_MASK                                                     (0xf8000000U)

#define NSF3V_TN_C34_S2_S_SHIFT                                                         (0U)
#define NSF3V_TN_C34_S2_S_MASK                                                          (0x00003fffU)

#define NSF3V_TN_C34_S3_X_SHIFT                                                         (16U)
#define NSF3V_TN_C34_S3_X_MASK                                                          (0x0fff0000U)

#define NSF3V_TN_C34_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_TN_C34_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_TN_C34_RESERVED_SHIFT                                                     (14U)
#define NSF3V_TN_C34_RESERVED_MASK                                                      (0x0000c000U)

#define NSF3V_TN_C35_S3_Y_SHIFT                                                         (0U)
#define NSF3V_TN_C35_S3_Y_MASK                                                          (0x000007ffU)

#define NSF3V_TN_C35_S3_S_SHIFT                                                         (16U)
#define NSF3V_TN_C35_S3_S_MASK                                                          (0x3fff0000U)

#define NSF3V_TN_C35_RESERVED_SHIFT                                                     (11U)
#define NSF3V_TN_C35_RESERVED_MASK                                                      (0x0000f800U)

#define NSF3V_TN_C35_RESERVED1_SHIFT                                                    (30U)
#define NSF3V_TN_C35_RESERVED1_MASK                                                     (0xc0000000U)

#define NSF3V_TN_SCALE_TN1_TO_TN2_SHIFT                                                 (0U)
#define NSF3V_TN_SCALE_TN1_TO_TN2_MASK                                                  (0x000000ffU)

#define NSF3V_TN_SCALE_TN3_TO_TN2_SHIFT                                                 (16U)
#define NSF3V_TN_SCALE_TN3_TO_TN2_MASK                                                  (0x00ff0000U)

#define NSF3V_TN_SCALE_RESERVED_SHIFT                                                   (8U)
#define NSF3V_TN_SCALE_RESERVED_MASK                                                    (0x0000ff00U)

#define NSF3V_TN_SCALE_RESERVED1_SHIFT                                                  (24U)
#define NSF3V_TN_SCALE_RESERVED1_MASK                                                   (0xff000000U)

#define NSF3V_THR_KNEE_U_SHIFT(n)                                                       ((n) * 8U)
#define NSF3V_THR_KNEE_U_MASK(n)                                                        ((uint32_t)255U << ((n) * 8U))

#define NSF3V_SUP_C00_L1_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C00_L1_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C00_L1_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C00_L1_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C00_L2_LH_SHIFT                                                       (16U)
#define NSF3V_SUP_C00_L2_LH_MASK                                                        (0x00ff0000U)

#define NSF3V_SUP_C00_L2_HH_SHIFT                                                       (24U)
#define NSF3V_SUP_C00_L2_HH_MASK                                                        (0xff000000U)

#define NSF3V_SUP_C01_L3_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C01_L3_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C01_L3_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C01_L3_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C01_RESERVED_SHIFT                                                    (16U)
#define NSF3V_SUP_C01_RESERVED_MASK                                                     (0xffff0000U)

#define NSF3V_SUP_C10_L1_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C10_L1_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C10_L1_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C10_L1_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C10_L2_LH_SHIFT                                                       (16U)
#define NSF3V_SUP_C10_L2_LH_MASK                                                        (0x00ff0000U)

#define NSF3V_SUP_C10_L2_HH_SHIFT                                                       (24U)
#define NSF3V_SUP_C10_L2_HH_MASK                                                        (0xff000000U)

#define NSF3V_SUP_C11_L3_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C11_L3_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C11_L3_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C11_L3_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C11_RESERVED_SHIFT                                                    (16U)
#define NSF3V_SUP_C11_RESERVED_MASK                                                     (0xffff0000U)

#define NSF3V_SUP_C20_L1_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C20_L1_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C20_L1_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C20_L1_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C20_L2_LH_SHIFT                                                       (16U)
#define NSF3V_SUP_C20_L2_LH_MASK                                                        (0x00ff0000U)

#define NSF3V_SUP_C20_L2_HH_SHIFT                                                       (24U)
#define NSF3V_SUP_C20_L2_HH_MASK                                                        (0xff000000U)

#define NSF3V_SUP_C21_L3_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C21_L3_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C21_L3_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C21_L3_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C21_RESERVED_SHIFT                                                    (16U)
#define NSF3V_SUP_C21_RESERVED_MASK                                                     (0xffff0000U)

#define NSF3V_SUP_C30_L1_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C30_L1_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C30_L1_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C30_L1_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C30_L2_LH_SHIFT                                                       (16U)
#define NSF3V_SUP_C30_L2_LH_MASK                                                        (0x00ff0000U)

#define NSF3V_SUP_C30_L2_HH_SHIFT                                                       (24U)
#define NSF3V_SUP_C30_L2_HH_MASK                                                        (0xff000000U)

#define NSF3V_SUP_C31_L3_LH_SHIFT                                                       (0U)
#define NSF3V_SUP_C31_L3_LH_MASK                                                        (0x000000ffU)

#define NSF3V_SUP_C31_L3_HH_SHIFT                                                       (8U)
#define NSF3V_SUP_C31_L3_HH_MASK                                                        (0x0000ff00U)

#define NSF3V_SUP_C31_RESERVED_SHIFT                                                    (16U)
#define NSF3V_SUP_C31_RESERVED_MASK                                                     (0xffff0000U)

#define NSF3V_EE_C00_L1_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C00_L1_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C00_L1_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C00_L1_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C00_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C00_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C00_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C00_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C01_L2_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C01_L2_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C01_L2_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C01_L2_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C01_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C01_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C01_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C01_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C02_L3_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C02_L3_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C02_L3_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C02_L3_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C02_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C02_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C02_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C02_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C10_L1_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C10_L1_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C10_L1_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C10_L1_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C10_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C10_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C10_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C10_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C11_L2_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C11_L2_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C11_L2_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C11_L2_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C11_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C11_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C11_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C11_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C12_L3_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C12_L3_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C12_L3_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C12_L3_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C12_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C12_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C12_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C12_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C20_L1_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C20_L1_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C20_L1_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C20_L1_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C20_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C20_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C20_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C20_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C21_L2_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C21_L2_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C21_L2_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C21_L2_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C21_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C21_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C21_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C21_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C22_L3_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C22_L3_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C22_L3_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C22_L3_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C22_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C22_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C22_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C22_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C30_L1_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C30_L1_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C30_L1_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C30_L1_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C30_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C30_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C30_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C30_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C31_L2_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C31_L2_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C31_L2_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C31_L2_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C31_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C31_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C31_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C31_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_EE_C32_L3_LH_SHIFT                                                        (0U)
#define NSF3V_EE_C32_L3_LH_MASK                                                         (0x00000fffU)

#define NSF3V_EE_C32_L3_HH_SHIFT                                                        (16U)
#define NSF3V_EE_C32_L3_HH_MASK                                                         (0x0fff0000U)

#define NSF3V_EE_C32_RESERVED_SHIFT                                                     (12U)
#define NSF3V_EE_C32_RESERVED_MASK                                                      (0x0000f000U)

#define NSF3V_EE_C32_RESERVED1_SHIFT                                                    (28U)
#define NSF3V_EE_C32_RESERVED1_MASK                                                     (0xf0000000U)

#define NSF3V_DS_THR_THR1_SHIFT                                                         (0U)
#define NSF3V_DS_THR_THR1_MASK                                                          (0x0000003fU)

#define NSF3V_DS_THR_THR2_SHIFT                                                         (16U)
#define NSF3V_DS_THR_THR2_MASK                                                          (0x003f0000U)

#define NSF3V_DS_THR_RESERVED_SHIFT                                                     (6U)
#define NSF3V_DS_THR_RESERVED_MASK                                                      (0x0000ffc0U)

#define NSF3V_DS_THR_RESERVED1_SHIFT                                                    (22U)
#define NSF3V_DS_THR_RESERVED1_MASK                                                     (0xffc00000U)

#define NSF3V_DS_SLOPE_SLOPE1_SHIFT                                                     (0U)
#define NSF3V_DS_SLOPE_SLOPE1_MASK                                                      (0x000003ffU)

#define NSF3V_DS_SLOPE_SLOPE2_SHIFT                                                     (16U)
#define NSF3V_DS_SLOPE_SLOPE2_MASK                                                      (0x03ff0000U)

#define NSF3V_DS_SLOPE_RESERVED_SHIFT                                                   (10U)
#define NSF3V_DS_SLOPE_RESERVED_MASK                                                    (0x0000fc00U)

#define NSF3V_DS_SLOPE_RESERVED1_SHIFT                                                  (26U)
#define NSF3V_DS_SLOPE_RESERVED1_MASK                                                   (0xfc000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_NSF3_H_ */

