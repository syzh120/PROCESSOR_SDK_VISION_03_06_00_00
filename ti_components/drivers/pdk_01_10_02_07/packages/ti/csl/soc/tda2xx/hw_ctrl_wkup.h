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
 *  \file   hw_ctrl_wkup.h
 *
 *  \brief  register-level header file for CTRL_WKUP
 *
**/

#ifndef HW_CTRL_WKUP_H_
#define HW_CTRL_WKUP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CTRL_WKUP_SEC_CTRL                                                                                 (0x0U)
#define CTRL_WKUP_OCPREG_SPARE                                                                             (0xcU)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG                                                                (0x10U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG                                                                (0x18U)
#define CTRL_WKUP_STD_FUSE_USB_CONF                                                                        (0x38U)
#define CTRL_WKUP_STD_FUSE_CONF                                                                            (0x3cU)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT                                                                   (0x44U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT                                                                   (0x48U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1                                                                 (0x4cU)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_2                                                                 (0x50U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL                                                                  (0x54U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL                                                                  (0x58U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL                                                                 (0x5cU)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL                                                                 (0x60U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL                                                                (0x64U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL                                                               (0x68U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_0                                                                        (0x100U)
#define CTRL_WKUP_ID_CODE                                                                                  (0x104U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_1                                                                        (0x108U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_2                                                                        (0x10cU)
#define CTRL_WKUP_STD_FUSE_DIE_ID_3                                                                        (0x110U)
#define CTRL_WKUP_STD_FUSE_PROD_ID_0                                                                       (0x114U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_WKUP_SEC_CTRL_SECCTRLWRDISABLE_SHIFT                                                         (31U)
#define CTRL_WKUP_SEC_CTRL_SECCTRLWRDISABLE_MASK                                                          (0x80000000U)
#define CTRL_WKUP_SEC_CTRL_SECCTRLWRDISABLE_WR_FORBIDDEN                                                  (1U)
#define CTRL_WKUP_SEC_CTRL_SECCTRLWRDISABLE_WR_ALLOWED                                                    (0U)

#define CTRL_WKUP_SEC_CTRL_SECURE_EMIF_CONFIG_RO_EN_SHIFT                                                 (4U)
#define CTRL_WKUP_SEC_CTRL_SECURE_EMIF_CONFIG_RO_EN_MASK                                                  (0x00000010U)
#define CTRL_WKUP_SEC_CTRL_SECURE_EMIF_CONFIG_RO_EN_RO                                                    (1U)
#define CTRL_WKUP_SEC_CTRL_SECURE_EMIF_CONFIG_RO_EN_RW                                                    (0U)

#define CTRL_WKUP_SEC_CTRL_RESERVED_0_SHIFT                                                               (0U)
#define CTRL_WKUP_SEC_CTRL_RESERVED_0_MASK                                                                (0x0000000fU)

#define CTRL_WKUP_SEC_CTRL_RESERVED_1_SHIFT                                                               (5U)
#define CTRL_WKUP_SEC_CTRL_RESERVED_1_MASK                                                                (0x7fffffe0U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE31_SHIFT                                                       (31U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE31_MASK                                                        (0x80000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE30_SHIFT                                                       (30U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE30_MASK                                                        (0x40000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE29_SHIFT                                                       (29U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE29_MASK                                                        (0x20000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE28_SHIFT                                                       (28U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE28_MASK                                                        (0x10000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE27_SHIFT                                                       (27U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE27_MASK                                                        (0x08000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE26_SHIFT                                                       (26U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE26_MASK                                                        (0x04000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE25_SHIFT                                                       (25U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE25_MASK                                                        (0x02000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE24_SHIFT                                                       (24U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE24_MASK                                                        (0x01000000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE23_SHIFT                                                       (23U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE23_MASK                                                        (0x00800000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE22_SHIFT                                                       (22U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE22_MASK                                                        (0x00400000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE21_SHIFT                                                       (21U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE21_MASK                                                        (0x00200000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE20_SHIFT                                                       (20U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE20_MASK                                                        (0x00100000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE19_SHIFT                                                       (19U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE19_MASK                                                        (0x00080000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE18_SHIFT                                                       (18U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE18_MASK                                                        (0x00040000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE17_SHIFT                                                       (17U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE17_MASK                                                        (0x00020000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE16_SHIFT                                                       (16U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE16_MASK                                                        (0x00010000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE15_SHIFT                                                       (15U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE15_MASK                                                        (0x00008000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE14_SHIFT                                                       (14U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE14_MASK                                                        (0x00004000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE13_SHIFT                                                       (13U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE13_MASK                                                        (0x00002000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE12_SHIFT                                                       (12U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE12_MASK                                                        (0x00001000U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE11_SHIFT                                                       (11U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE11_MASK                                                        (0x00000800U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE10_SHIFT                                                       (10U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE10_MASK                                                        (0x00000400U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE9_SHIFT                                                        (9U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE9_MASK                                                         (0x00000200U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE8_SHIFT                                                        (8U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE8_MASK                                                         (0x00000100U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE7_SHIFT                                                        (7U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE7_MASK                                                         (0x00000080U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE6_SHIFT                                                        (6U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE6_MASK                                                         (0x00000040U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE5_SHIFT                                                        (5U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE5_MASK                                                         (0x00000020U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE4_SHIFT                                                        (4U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE4_MASK                                                         (0x00000010U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE3_SHIFT                                                        (3U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE3_MASK                                                         (0x00000008U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE2_SHIFT                                                        (2U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE2_MASK                                                         (0x00000004U)

#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE1_SHIFT                                                        (1U)
#define CTRL_WKUP_OCPREG_SPARE_OCPREG_SPARE1_MASK                                                         (0x00000002U)

#define CTRL_WKUP_OCPREG_SPARE_USIM_LOW_IMPEDANCE_SEL_SHIFT                                               (0U)
#define CTRL_WKUP_OCPREG_SPARE_USIM_LOW_IMPEDANCE_SEL_MASK                                                (0x00000001U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_IBANK_POS_SHIFT                                   (27U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_IBANK_POS_MASK                                    (0x18000000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR_TERM_SHIFT                                    (24U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR_TERM_MASK                                     (0x07000000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR2_DDQS_SHIFT                                   (23U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR2_DDQS_MASK                                    (0x00800000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DYN_ODT_SHIFT                                     (21U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DYN_ODT_MASK                                      (0x00600000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR_DISABLE_DLL_SHIFT                             (20U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DDR_DISABLE_DLL_MASK                              (0x00100000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DRIVE_SHIFT                                       (18U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_DRIVE_MASK                                        (0x000c0000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_CWL_SHIFT                                         (16U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_CWL_MASK                                          (0x00030000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_CL_SHIFT                                          (10U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_CL_MASK                                           (0x00003c00U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_ROWSIZE_SHIFT                                     (7U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_ROWSIZE_MASK                                      (0x00000380U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_IBANK_SHIFT                                       (4U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_IBANK_MASK                                        (0x00000070U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_PAGESIZE_SHIFT                                    (0U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EMIF1_SDRAM_PAGESIZE_MASK                                     (0x00000007U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_0_SHIFT                                              (14U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_0_MASK                                               (0x0000c000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_1_SHIFT                                              (29U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_1_MASK                                               (0xe0000000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_2_SHIFT                                              (3U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_RESERVED_2_MASK                                               (0x00000008U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_IBANK_POS_SHIFT                                   (27U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_IBANK_POS_MASK                                    (0x18000000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR_TERM_SHIFT                                    (24U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR_TERM_MASK                                     (0x07000000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR2_DDQS_SHIFT                                   (23U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR2_DDQS_MASK                                    (0x00800000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DYN_ODT_SHIFT                                     (21U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DYN_ODT_MASK                                      (0x00600000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR_DISABLE_DLL_SHIFT                             (20U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DDR_DISABLE_DLL_MASK                              (0x00100000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DRIVE_SHIFT                                       (18U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_DRIVE_MASK                                        (0x000c0000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_CWL_SHIFT                                         (16U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_CWL_MASK                                          (0x00030000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_CL_SHIFT                                          (10U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_CL_MASK                                           (0x00003c00U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_ROWSIZE_SHIFT                                     (7U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_ROWSIZE_MASK                                      (0x00000380U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_IBANK_SHIFT                                       (4U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_IBANK_MASK                                        (0x00000070U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_PAGESIZE_SHIFT                                    (0U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_EMIF2_SDRAM_PAGESIZE_MASK                                     (0x00000007U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_0_SHIFT                                              (14U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_0_MASK                                               (0x0000c000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_1_SHIFT                                              (29U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_1_MASK                                               (0xe0000000U)

#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_2_SHIFT                                              (3U)
#define CTRL_WKUP_SECURE_EMIF2_SDRAM_CONFIG_RESERVED_2_MASK                                               (0x00000008U)

#define CTRL_WKUP_STD_FUSE_USB_CONF_USB_PROD_ID_SHIFT                                                     (16U)
#define CTRL_WKUP_STD_FUSE_USB_CONF_USB_PROD_ID_MASK                                                      (0xffff0000U)

#define CTRL_WKUP_STD_FUSE_USB_CONF_USB_VENDOR_ID_SHIFT                                                   (0U)
#define CTRL_WKUP_STD_FUSE_USB_CONF_USB_VENDOR_ID_MASK                                                    (0x0000ffffU)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_INITREF_DEF_DIS_SHIFT                                      (21U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_INITREF_DEF_DIS_MASK                                       (0x00200000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_INITREF_DEF_DIS_DISABLED                                   (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_INITREF_DEF_DIS_ENABLED                                    (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_DDR3_LPDDR2N_SHIFT                                         (20U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_DDR3_LPDDR2N_MASK                                          (0x00100000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_DDR3_LPDDR2N_DDR3                                          (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF2_DDR3_LPDDR2N_LPDDR2                                        (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_INITREF_DEF_DIS_SHIFT                                      (19U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_INITREF_DEF_DIS_MASK                                       (0x00080000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_INITREF_DEF_DIS_DISABLED                                   (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_INITREF_DEF_DIS_ENABLED                                    (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_DDR3_LPDDR2N_SHIFT                                         (18U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_DDR3_LPDDR2N_MASK                                          (0x00040000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_DDR3_LPDDR2N_DDR3                                          (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_EMIF1_DDR3_LPDDR2N_LPDDR2                                        (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_HDCP_ENABLE_SHIFT                                                (16U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_HDCP_ENABLE_MASK                                                 (0x00010000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_HDCP_ENABLE_DISABLED                                             (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_HDCP_ENABLE_ENABLED                                              (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_CH_SPEEDUP_DISABLE_SHIFT                                         (12U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_CH_SPEEDUP_DISABLE_MASK                                          (0x00001000U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_CH_SPEEDUP_DISABLE_DISABLED                                      (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_CH_SPEEDUP_DISABLE_ENABLED                                       (0U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_CLOCK_SOURCE_SHIFT                                     (4U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_CLOCK_SOURCE_MASK                                      (0x00000010U)

#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_DISABLE_SHIFT                                          (3U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_DISABLE_MASK                                           (0x00000008U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_DISABLE_DISABLED                                       (1U)
#define CTRL_WKUP_STD_FUSE_CONF_STD_FUSE_SGX540_3D_DISABLE_ENABLED                                        (0U)

#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_0_SHIFT                                                          (0U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_0_MASK                                                           (0x00000007U)

#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_1_SHIFT                                                          (5U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_1_MASK                                                           (0x00000fe0U)

#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_2_SHIFT                                                          (17U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_2_MASK                                                           (0x00020000U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_2_DISABLED                                                       (1U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_2_ENABLED                                                        (0U)

#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_3_SHIFT                                                          (22U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_3_MASK                                                           (0xffc00000U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_3_ENABLED                                                        (1U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_3_DISABLED                                                       (0U)

#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_4_SHIFT                                                          (13U)
#define CTRL_WKUP_STD_FUSE_CONF_RESERVED_4_MASK                                                           (0x0000e000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_NARROW_ONLY_SHIFT                                          (17U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_NARROW_ONLY_MASK                                           (0x00020000U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_NARROW_ONLY_16_BITMODEONLY                                 (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_NARROW_ONLY_32_BIT_16_BITMODE                              (0U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_ECC_SHIFT                                               (16U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_ECC_MASK                                                (0x00010000U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_ECC_ECCCANBEENABLED                                     (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_ECC_ECCCANNOTBEENABLED                                  (0U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_NUM_OF_SAMPLES_SHIFT                               (14U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_NUM_OF_SAMPLES_MASK                                (0x0000c000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_SEL_LOGIC_SHIFT                                    (13U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_SEL_LOGIC_MASK                                     (0x00002000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_ALL_DQ_MPR_RD_RESP_SHIFT                           (12U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_ALL_DQ_MPR_RD_RESP_MASK                            (0x00001000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_OUTPUT_STATUS_SELECT_SHIFT                         (9U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_REG_PHY_OUTPUT_STATUS_SELECT_MASK                          (0x00000e00U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_SDRAM_DISABLE_RESET_SHIFT                                  (7U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_SDRAM_DISABLE_RESET_MASK                                   (0x00000080U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_PHY_RD_LOCAL_ODT_SHIFT                                     (5U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_PHY_RD_LOCAL_ODT_MASK                                      (0x00000060U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_DFI_CLOCK_PHASE_CTRL_SHIFT                                 (3U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_DFI_CLOCK_PHASE_CTRL_MASK                                  (0x00000008U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_2_SHIFT                                           (2U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_2_MASK                                            (0x00000004U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_1_SHIFT                                           (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_1_MASK                                            (0x00000002U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_0_SHIFT                                           (0U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EMIF1_EN_SLICE_0_MASK                                            (0x00000001U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_0_SHIFT                                                 (18U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_0_MASK                                                  (0xfffc0000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_1_SHIFT                                                 (8U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_1_MASK                                                  (0x00000100U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_2_SHIFT                                                 (4U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_RESERVED_2_MASK                                                  (0x00000010U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_NARROW_ONLY_SHIFT                                          (17U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_NARROW_ONLY_MASK                                           (0x00020000U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_NARROW_ONLY_16_BITMODEONLY                                 (1U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_NARROW_ONLY_32_BIT_16_BITMODE                              (0U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_NUM_OF_SAMPLES_SHIFT                               (14U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_NUM_OF_SAMPLES_MASK                                (0x0000c000U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_SEL_LOGIC_SHIFT                                    (13U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_SEL_LOGIC_MASK                                     (0x00002000U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_ALL_DQ_MPR_RD_RESP_SHIFT                           (12U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_ALL_DQ_MPR_RD_RESP_MASK                            (0x00001000U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_OUTPUT_STATUS_SELECT_SHIFT                         (9U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_REG_PHY_OUTPUT_STATUS_SELECT_MASK                          (0x00000e00U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_SDRAM_DISABLE_RESET_SHIFT                                  (7U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_SDRAM_DISABLE_RESET_MASK                                   (0x00000080U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_PHY_RD_LOCAL_ODT_SHIFT                                     (5U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_PHY_RD_LOCAL_ODT_MASK                                      (0x00000060U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_DFI_CLOCK_PHASE_CTRL_SHIFT                                 (3U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_DFI_CLOCK_PHASE_CTRL_MASK                                  (0x00000008U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_2_SHIFT                                           (2U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_2_MASK                                            (0x00000004U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_1_SHIFT                                           (1U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_1_MASK                                            (0x00000002U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_0_SHIFT                                           (0U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_EMIF2_EN_SLICE_0_MASK                                            (0x00000001U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_0_SHIFT                                                 (18U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_0_MASK                                                  (0xfffc0000U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_1_SHIFT                                                 (16U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_1_MASK                                                  (0x00010000U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_1_ECCCANBEENABLED                                       (1U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_1_ECCCANNOTBEENABLED                                    (0U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_2_SHIFT                                                 (8U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_2_MASK                                                  (0x00000100U)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_3_SHIFT                                                 (4U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_RESERVED_3_MASK                                                  (0x00000010U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1_EMIF1_PHY_REG_READ_DATA_EYE_LVL_SHIFT                          (0U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1_EMIF1_PHY_REG_READ_DATA_EYE_LVL_MASK                           (0xffffffffU)

#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_2_EMIF2_PHY_REG_READ_DATA_EYE_LVL_SHIFT                          (0U)
#define CTRL_WKUP_EMIF2_SDRAM_CONFIG_EXT_2_EMIF2_PHY_REG_READ_DATA_EYE_LVL_MASK                           (0xffffffffU)

#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_MUX_CTRL_SHIFT                                    (10U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_MUX_CTRL_MASK                                     (0x00000400U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_MUX_CTRL_OCP                                      (1U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_MUX_CTRL_EFUSE                                    (0U)

#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_VSET_IN_SHIFT                                     (5U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_VSET_IN_MASK                                      (0x000003e0U)

#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_VSET_OUT_SHIFT                                    (0U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_LDOVBBGPU_FBB_VSET_OUT_MASK                                     (0x0000001fU)

#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_RESERVED_0_SHIFT                                                (11U)
#define CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL_RESERVED_0_MASK                                                 (0xfffff800U)

#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_MUX_CTRL_SHIFT                                    (10U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_MUX_CTRL_MASK                                     (0x00000400U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_MUX_CTRL_OCP                                      (1U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_MUX_CTRL_EFUSE                                    (0U)

#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_VSET_IN_SHIFT                                     (5U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_VSET_IN_MASK                                      (0x000003e0U)

#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_VSET_OUT_SHIFT                                    (0U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_LDOVBBMPU_FBB_VSET_OUT_MASK                                     (0x0000001fU)

#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_RESERVED_0_SHIFT                                                (11U)
#define CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL_RESERVED_0_MASK                                                 (0xfffff800U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_MUX_CTRL_SHIFT                              (26U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_MUX_CTRL_MASK                               (0x04000000U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_MUX_CTRL_OCP                                (1U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_MUX_CTRL_EFUSE                              (0U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_VSET_IN_SHIFT                               (21U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_VSET_IN_MASK                                (0x03e00000U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_VSET_OUT_SHIFT                              (16U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_RETMODE_VSET_OUT_MASK                               (0x001f0000U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_MUX_CTRL_SHIFT                              (10U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_MUX_CTRL_MASK                               (0x00000400U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_MUX_CTRL_OCP                                (1U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_MUX_CTRL_EFUSE                              (0U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_VSET_IN_SHIFT                               (5U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_VSET_IN_MASK                                (0x000003e0U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_VSET_OUT_SHIFT                              (0U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_LDOSRAMGPU_ACTMODE_VSET_OUT_MASK                               (0x0000001fU)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_RESERVED_0_SHIFT                                               (11U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_RESERVED_0_MASK                                                (0x0000f800U)

#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_RESERVED_1_SHIFT                                               (27U)
#define CTRL_WKUP_LDOSRAM_GPU_VOLTAGE_CTRL_RESERVED_1_MASK                                                (0xf8000000U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_MUX_CTRL_SHIFT                              (26U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_MUX_CTRL_MASK                               (0x04000000U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_MUX_CTRL_OCP                                (1U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_MUX_CTRL_EFUSE                              (0U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_VSET_IN_SHIFT                               (21U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_VSET_IN_MASK                                (0x03e00000U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_VSET_OUT_SHIFT                              (16U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_RETMODE_VSET_OUT_MASK                               (0x001f0000U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_MUX_CTRL_SHIFT                              (10U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_MUX_CTRL_MASK                               (0x00000400U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_MUX_CTRL_OCP                                (1U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_MUX_CTRL_EFUSE                              (0U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_VSET_IN_SHIFT                               (5U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_VSET_IN_MASK                                (0x000003e0U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_VSET_OUT_SHIFT                              (0U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_LDOSRAMMPU_ACTMODE_VSET_OUT_MASK                               (0x0000001fU)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_RESERVED_0_SHIFT                                               (11U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_RESERVED_0_MASK                                                (0x0000f800U)

#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_RESERVED_1_SHIFT                                               (27U)
#define CTRL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL_RESERVED_1_MASK                                                (0xf8000000U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_MUX_CTRL_SHIFT                            (26U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_MUX_CTRL_MASK                             (0x04000000U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_MUX_CTRL_OCP                              (1U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_MUX_CTRL_EFUSE                            (0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_VSET_IN_SHIFT                             (21U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_VSET_IN_MASK                              (0x03e00000U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_VSET_OUT_SHIFT                            (16U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_RETMODE_VSET_OUT_MASK                             (0x001f0000U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_MUX_CTRL_SHIFT                            (10U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_MUX_CTRL_MASK                             (0x00000400U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_MUX_CTRL_OCP                              (1U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_MUX_CTRL_EFUSE                            (0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_VSET_IN_SHIFT                             (5U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_VSET_IN_MASK                              (0x000003e0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_VSET_OUT_SHIFT                            (0U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_LDOSRAMCORE_ACTMODE_VSET_OUT_MASK                             (0x0000001fU)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_RESERVED_0_SHIFT                                              (11U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_RESERVED_0_MASK                                               (0x0000f800U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_RESERVED_1_SHIFT                                              (27U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL_RESERVED_1_MASK                                               (0xf8000000U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_MUX_CTRL_SHIFT                          (26U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_MUX_CTRL_MASK                           (0x04000000U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_MUX_CTRL_OCP                            (1U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_MUX_CTRL_EFUSE                          (0U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_VSET_IN_SHIFT                           (21U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_VSET_IN_MASK                            (0x03e00000U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_VSET_OUT_SHIFT                          (16U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_RETMODE_VSET_OUT_MASK                           (0x001f0000U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_MUX_CTRL_SHIFT                          (10U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_MUX_CTRL_MASK                           (0x00000400U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_MUX_CTRL_OCP                            (1U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_MUX_CTRL_EFUSE                          (0U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_VSET_IN_SHIFT                           (5U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_VSET_IN_MASK                            (0x000003e0U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_VSET_OUT_SHIFT                          (0U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_LDOSRAMMPU_2_ACTMODE_VSET_OUT_MASK                           (0x0000001fU)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_RESERVED_0_SHIFT                                             (11U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_RESERVED_0_MASK                                              (0x0000f800U)

#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_RESERVED_1_SHIFT                                             (27U)
#define CTRL_WKUP_LDOSRAM_MPU_2_VOLTAGE_CTRL_RESERVED_1_MASK                                              (0xf8000000U)

#define CTRL_WKUP_STD_FUSE_DIE_ID_0_STD_FUSE_DIE_ID_0_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_0_STD_FUSE_DIE_ID_0_MASK                                                (0xffffffffU)

#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_SHIFT                                                           (0U)
#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_MASK                                                            (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_1_STD_FUSE_DIE_ID_1_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_1_STD_FUSE_DIE_ID_1_MASK                                                (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_2_STD_FUSE_DIE_ID_2_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_2_STD_FUSE_DIE_ID_2_MASK                                                (0x0000ffffU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE_SHIFT                                                    (16U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE_MASK                                                    (0x00030000U)

#define CTRL_WKUP_STD_FUSE_DIE_ID_3_STD_FUSE_DIE_ID_3_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_3_STD_FUSE_DIE_ID_3_MASK                                                (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_PROD_ID_0_STD_FUSE_PROD_ID_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_PROD_ID_0_STD_FUSE_PROD_ID_MASK                                                (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_WKUP_H_ */
