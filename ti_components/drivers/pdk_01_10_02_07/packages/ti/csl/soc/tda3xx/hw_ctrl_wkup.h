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
 *  \file   hw_ctrl_wkup.h
 *
 *  \brief  Register-level header file for CTRL_WKUP
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

#define CTRL_WKUP_SEC                                               (0x0U)
#define CTRL_WKUP_SEC_EMU                                           (0x4U)
#define CTRL_WKUP_SEC_TAP                                           (0x8U)
#define CTRL_WKUP_OCPREG_SPARE                                      (0xcU)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG                         (0x10U)
#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG                    (0x14U)
#define CTRL_WKUP_STD_FUSE_CONF                                     (0x3cU)
#define CTRL_WKUP_DPLL_CLK_TRIMMING                                 (0x40U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT                            (0x44U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1                          (0x4cU)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE                              (0x64U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_0                                 (0x100U)
#define CTRL_WKUP_ID_CODE                                           (0x104U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_1                                 (0x108U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_2                                 (0x10cU)
#define CTRL_WKUP_STD_FUSE_DIE_ID_3                                 (0x110U)
#define CTRL_WKUP_STD_FUSE_PROD_ID_0                                (0x114U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_WKUP_SEC_SECCTRLWRDISABLE_SHIFT                                            (31U)
#define CTRL_WKUP_SEC_SECCTRLWRDISABLE_MASK                                             (0x80000000U)
#define CTRL_WKUP_SEC_SECCTRLWRDISABLE_WR_FORBIDDEN                                      (1U)
#define CTRL_WKUP_SEC_SECCTRLWRDISABLE_WR_ALLOWED                                        (0U)

#define CTRL_WKUP_SEC_SAVEANDRESTOREINITDONE_SHIFT                                      (30U)
#define CTRL_WKUP_SEC_SAVEANDRESTOREINITDONE_MASK                                       (0x40000000U)

#define CTRL_WKUP_SEC_FASTOCMRAMSECURESAVE_1_SHIFT                                      (29U)
#define CTRL_WKUP_SEC_FASTOCMRAMSECURESAVE_1_MASK                                       (0x20000000U)

#define CTRL_WKUP_SEC_FASTOCMRAMSECURESAVE_0_SHIFT                                      (28U)
#define CTRL_WKUP_SEC_FASTOCMRAMSECURESAVE_0_MASK                                       (0x10000000U)

#define CTRL_WKUP_SEC_L3OCMRAMSECURESAVE_1_SHIFT                                        (27U)
#define CTRL_WKUP_SEC_L3OCMRAMSECURESAVE_1_MASK                                         (0x08000000U)

#define CTRL_WKUP_SEC_L3OCMRAMSECURESAVE_0_SHIFT                                        (26U)
#define CTRL_WKUP_SEC_L3OCMRAMSECURESAVE_0_MASK                                         (0x04000000U)

#define CTRL_WKUP_SEC_LPRMSECUREREGISTERACCESSENABLE_SHIFT                              (19U)
#define CTRL_WKUP_SEC_LPRMSECUREREGISTERACCESSENABLE_MASK                               (0x00080000U)
#define CTRL_WKUP_SEC_LPRMSECUREREGISTERACCESSENABLE_DISABLE                             (1U)
#define CTRL_WKUP_SEC_LPRMSECUREREGISTERACCESSENABLE_ENABLE                              (0U)

#define CTRL_WKUP_SEC_DMLEDMODEMENABLE_SHIFT                                            (16U)
#define CTRL_WKUP_SEC_DMLEDMODEMENABLE_MASK                                             (0x00010000U)
#define CTRL_WKUP_SEC_DMLEDMODEMENABLE_ENA                                               (1U)
#define CTRL_WKUP_SEC_DMLEDMODEMENABLE_DIS                                               (0U)

#define CTRL_WKUP_SEC_HDCP_DUCATI_DISABLE_SHIFT                                         (14U)
#define CTRL_WKUP_SEC_HDCP_DUCATI_DISABLE_MASK                                          (0x00004000U)
#define CTRL_WKUP_SEC_HDCP_DUCATI_DISABLE_MSHIELD                                        (1U)
#define CTRL_WKUP_SEC_HDCP_DUCATI_DISABLE_DES                                            (0U)

#define CTRL_WKUP_SEC_CUST_EFUSE_DECODE_N_SHIFT                                         (12U)
#define CTRL_WKUP_SEC_CUST_EFUSE_DECODE_N_MASK                                          (0x00001000U)
#define CTRL_WKUP_SEC_CUST_EFUSE_DECODE_N_NOT_DECODED                                    (1U)
#define CTRL_WKUP_SEC_CUST_EFUSE_DECODE_N_DECODED                                        (0U)

#define CTRL_WKUP_SEC_CUST_EFUSE_WR_DISABLE_SHIFT                                       (11U)
#define CTRL_WKUP_SEC_CUST_EFUSE_WR_DISABLE_MASK                                        (0x00000800U)
#define CTRL_WKUP_SEC_CUST_EFUSE_WR_DISABLE_FORBIDDEN                                    (1U)
#define CTRL_WKUP_SEC_CUST_EFUSE_WR_DISABLE_ALLOWED                                      (0U)

#define CTRL_WKUP_SEC_BSCENABLE_SHIFT                                                   (9U)
#define CTRL_WKUP_SEC_BSCENABLE_MASK                                                    (0x00000200U)
#define CTRL_WKUP_SEC_BSCENABLE_ENA                                                      (1U)
#define CTRL_WKUP_SEC_BSCENABLE_DIS                                                      (0U)

#define CTRL_WKUP_SEC_DMLEDDUCATIENABLE_SHIFT                                           (8U)
#define CTRL_WKUP_SEC_DMLEDDUCATIENABLE_MASK                                            (0x00000100U)
#define CTRL_WKUP_SEC_DMLEDDUCATIENABLE_ENA                                              (1U)
#define CTRL_WKUP_SEC_DMLEDDUCATIENABLE_DIS                                              (0U)

#define CTRL_WKUP_SEC_DMLEDCOREENABLE_SHIFT                                             (7U)
#define CTRL_WKUP_SEC_DMLEDCOREENABLE_MASK                                              (0x00000080U)
#define CTRL_WKUP_SEC_DMLEDCOREENABLE_ENA                                                (1U)
#define CTRL_WKUP_SEC_DMLEDCOREENABLE_DIS                                                (0U)

#define CTRL_WKUP_SEC_VIRTUALISATION_EN_SHIFT                                           (6U)
#define CTRL_WKUP_SEC_VIRTUALISATION_EN_MASK                                            (0x00000040U)
#define CTRL_WKUP_SEC_VIRTUALISATION_EN_ENA                                              (1U)
#define CTRL_WKUP_SEC_VIRTUALISATION_EN_DIS                                              (0U)

#define CTRL_WKUP_SEC_SECURE_EMIF_CONFIG_RO_EN_SHIFT                                    (4U)
#define CTRL_WKUP_SEC_SECURE_EMIF_CONFIG_RO_EN_MASK                                     (0x00000010U)
#define CTRL_WKUP_SEC_SECURE_EMIF_CONFIG_RO_EN                                           (1U)
#define CTRL_WKUP_SEC_SECURE_EMIF_CONFIG_RO_EN_RW                                        (0U)

#define CTRL_WKUP_SEC_WDREGENABLE_SHIFT                                                 (1U)
#define CTRL_WKUP_SEC_WDREGENABLE_MASK                                                  (0x00000002U)
#define CTRL_WKUP_SEC_WDREGENABLE_SECURE_ONLY                                            (1U)
#define CTRL_WKUP_SEC_WDREGENABLE_NEVER_ALLOWED                                          (0U)

#define CTRL_WKUP_SEC_WDOPDISABLE_SHIFT                                                 (0U)
#define CTRL_WKUP_SEC_WDOPDISABLE_MASK                                                  (0x00000001U)
#define CTRL_WKUP_SEC_WDOPDISABLE_WD_FROZEN                                              (1U)
#define CTRL_WKUP_SEC_WDOPDISABLE_WD_RUNNING                                             (0U)

#define CTRL_WKUP_SEC_EMU_SECEMUWRDISABLE_SHIFT                                         (31U)
#define CTRL_WKUP_SEC_EMU_SECEMUWRDISABLE_MASK                                          (0x80000000U)
#define CTRL_WKUP_SEC_EMU_SECEMUWRDISABLE_WR_FORBIDDEN                                   (1U)
#define CTRL_WKUP_SEC_EMU_SECEMUWRDISABLE_WR_ALLOWED                                     (0U)

#define CTRL_WKUP_SEC_EMU_ICE_PRIV_DBG_EN_SHIFT                                         (13U)
#define CTRL_WKUP_SEC_EMU_ICE_PRIV_DBG_EN_MASK                                          (0x00002000U)
#define CTRL_WKUP_SEC_EMU_ICE_PRIV_DBG_EN_ALLOWED                                        (1U)
#define CTRL_WKUP_SEC_EMU_ICE_PRIV_DBG_EN_FORBIDDEN                                      (0U)

#define CTRL_WKUP_SEC_EMU_ETM_PRIV_DBG_EN_SHIFT                                         (12U)
#define CTRL_WKUP_SEC_EMU_ETM_PRIV_DBG_EN_MASK                                          (0x00001000U)
#define CTRL_WKUP_SEC_EMU_ETM_PRIV_DBG_EN_ENA                                            (1U)
#define CTRL_WKUP_SEC_EMU_ETM_PRIV_DBG_EN_DIS                                            (0U)

#define CTRL_WKUP_SEC_EMU_GENDBGENABLE_SHIFT                                            (0U)
#define CTRL_WKUP_SEC_EMU_GENDBGENABLE_MASK                                             (0x00000fffU)

#define CTRL_WKUP_SEC_TAP_SECTAPWR_DISABLE_SHIFT                                        (31U)
#define CTRL_WKUP_SEC_TAP_SECTAPWR_DISABLE_MASK                                         (0x80000000U)
#define CTRL_WKUP_SEC_TAP_SECTAPWR_DISABLE_FORBIDDEN                                     (1U)
#define CTRL_WKUP_SEC_TAP_SECTAPWR_DISABLE_ALLOWED                                       (0U)

#define CTRL_WKUP_SEC_TAP_TEST_TAPENABLE_SHIFT                                          (26U)
#define CTRL_WKUP_SEC_TAP_TEST_TAPENABLE_MASK                                           (0x04000000U)
#define CTRL_WKUP_SEC_TAP_TEST_TAPENABLE_ENABLED                                         (1U)
#define CTRL_WKUP_SEC_TAP_TEST_TAPENABLE_DISABLED                                        (0U)

#define CTRL_WKUP_SEC_TAP_DSP2_TAPENABLE_SHIFT                                          (12U)
#define CTRL_WKUP_SEC_TAP_DSP2_TAPENABLE_MASK                                           (0x00001000U)
#define CTRL_WKUP_SEC_TAP_DSP2_TAPENABLE_ENABLED                                         (1U)
#define CTRL_WKUP_SEC_TAP_DSP2_TAPENABLE_DISABLED                                        (0U)

#define CTRL_WKUP_SEC_TAP_JTAGEXT_TAPENABLE_SHIFT                                       (11U)
#define CTRL_WKUP_SEC_TAP_JTAGEXT_TAPENABLE_MASK                                        (0x00000800U)
#define CTRL_WKUP_SEC_TAP_JTAGEXT_TAPENABLE_ENABLED                                      (1U)
#define CTRL_WKUP_SEC_TAP_JTAGEXT_TAPENABLE_DISABLED                                     (0U)

#define CTRL_WKUP_SEC_TAP_PARTIAL_IEEE1500_DISABLE_SHIFT                                (4U)
#define CTRL_WKUP_SEC_TAP_PARTIAL_IEEE1500_DISABLE_MASK                                 (0x00000010U)
#define CTRL_WKUP_SEC_TAP_PARTIAL_IEEE1500_DISABLE_RESTRICTED                            (1U)
#define CTRL_WKUP_SEC_TAP_PARTIAL_IEEE1500_DISABLE_UNRESTRICTED                          (0U)

#define CTRL_WKUP_SEC_TAP_IEEE1500_ENABLE_SHIFT                                         (3U)
#define CTRL_WKUP_SEC_TAP_IEEE1500_ENABLE_MASK                                          (0x00000008U)
#define CTRL_WKUP_SEC_TAP_IEEE1500_ENABLE_ENABLED                                        (1U)
#define CTRL_WKUP_SEC_TAP_IEEE1500_ENABLE_DISABLED                                       (0U)

#define CTRL_WKUP_SEC_TAP_DUCATI_TAPENABLE_SHIFT                                        (2U)
#define CTRL_WKUP_SEC_TAP_DUCATI_TAPENABLE_MASK                                         (0x00000004U)
#define CTRL_WKUP_SEC_TAP_DUCATI_TAPENABLE_ENABLED                                       (1U)
#define CTRL_WKUP_SEC_TAP_DUCATI_TAPENABLE_DISABLED                                      (0U)

#define CTRL_WKUP_SEC_TAP_IVA3C64_TAPENABLE_SHIFT                                       (1U)
#define CTRL_WKUP_SEC_TAP_IVA3C64_TAPENABLE_MASK                                        (0x00000002U)
#define CTRL_WKUP_SEC_TAP_IVA3C64_TAPENABLE_ENABLED                                      (1U)
#define CTRL_WKUP_SEC_TAP_IVA3C64_TAPENABLE_DISABLED                                     (0U)

#define CTRL_WKUP_SEC_TAP_DAP_TAPENABLE_SHIFT                                           (0U)
#define CTRL_WKUP_SEC_TAP_DAP_TAPENABLE_MASK                                            (0x00000001U)
#define CTRL_WKUP_SEC_TAP_DAP_TAPENABLE_ENABLED                                          (1U)
#define CTRL_WKUP_SEC_TAP_DAP_TAPENABLE_DISABLED                                         (0U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE31_SHIFT                                            (31U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE31_MASK                                             (0x80000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE30_SHIFT                                            (30U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE30_MASK                                             (0x40000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE29_SHIFT                                            (29U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE29_MASK                                             (0x20000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE28_SHIFT                                            (28U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE28_MASK                                             (0x10000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE27_SHIFT                                            (27U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE27_MASK                                             (0x08000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE26_SHIFT                                            (26U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE26_MASK                                             (0x04000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE25_SHIFT                                            (25U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE25_MASK                                             (0x02000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE24_SHIFT                                            (24U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE24_MASK                                             (0x01000000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE23_SHIFT                                            (23U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE23_MASK                                             (0x00800000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE22_SHIFT                                            (22U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE22_MASK                                             (0x00400000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE21_SHIFT                                            (21U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE21_MASK                                             (0x00200000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE20_SHIFT                                            (20U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE20_MASK                                             (0x00100000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE19_SHIFT                                            (19U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE19_MASK                                             (0x00080000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE18_SHIFT                                            (18U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE18_MASK                                             (0x00040000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE17_SHIFT                                            (17U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE17_MASK                                             (0x00020000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE16_SHIFT                                            (16U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE16_MASK                                             (0x00010000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE15_SHIFT                                            (15U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE15_MASK                                             (0x00008000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE14_SHIFT                                            (14U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE14_MASK                                             (0x00004000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE13_SHIFT                                            (13U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE13_MASK                                             (0x00002000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE12_SHIFT                                            (12U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE12_MASK                                             (0x00001000U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE11_SHIFT                                            (11U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE11_MASK                                             (0x00000800U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE10_SHIFT                                            (10U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE10_MASK                                             (0x00000400U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE9_SHIFT                                             (9U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE9_MASK                                              (0x00000200U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE8_SHIFT                                             (8U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE8_MASK                                              (0x00000100U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE7_SHIFT                                             (7U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE7_MASK                                              (0x00000080U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE6_SHIFT                                             (6U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE6_MASK                                              (0x00000040U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE5_SHIFT                                             (5U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE5_MASK                                              (0x00000020U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE4_SHIFT                                             (4U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE4_MASK                                              (0x00000010U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE3_SHIFT                                             (3U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE3_MASK                                              (0x00000008U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE2_SHIFT                                             (2U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE2_MASK                                              (0x00000004U)

#define CTRL_WKUP_OCPREG_SPARE_SPARE1_SHIFT                                             (1U)
#define CTRL_WKUP_OCPREG_SPARE_SPARE1_MASK                                              (0x00000002U)

#define CTRL_WKUP_OCPREG_SPARE_USIM_LOW_IMPEDANCE_SEL_SHIFT                             (0U)
#define CTRL_WKUP_OCPREG_SPARE_USIM_LOW_IMPEDANCE_SEL_MASK                              (0x00000001U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_IBANK_POS_SHIFT                             (27U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_IBANK_POS_MASK                              (0x18000000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR_TERM_SHIFT                              (24U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR_TERM_MASK                               (0x07000000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR2_DDQS_SHIFT                             (23U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR2_DDQS_MASK                              (0x00800000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DYN_ODT_SHIFT                               (21U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DYN_ODT_MASK                                (0x00600000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR_DISABLE_DLL_SHIFT                       (20U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DDR_DISABLE_DLL_MASK                        (0x00100000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DRIVE_SHIFT                                 (18U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_DRIVE_MASK                                  (0x000c0000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_CWL_SHIFT                                   (16U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_CWL_MASK                                    (0x00030000U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_CL_SHIFT                                    (10U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_CL_MASK                                     (0x00003c00U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_ROWSIZE_SHIFT                               (7U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_ROWSIZE_MASK                                (0x00000380U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_IBANK_SHIFT                                 (4U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_IBANK_MASK                                  (0x00000070U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EBANK_SHIFT                                 (3U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_EBANK_MASK                                  (0x00000008U)

#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_PAGESIZE_SHIFT                              (0U)
#define CTRL_WKUP_SECURE_EMIF1_SDRAM_CONFIG_PAGESIZE_MASK                               (0x00000007U)

#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_CS1NVMEN_SHIFT                   (30U)
#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_CS1NVMEN_MASK                    (0x40000000U)

#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_EBANK_POS_SHIFT                  (27U)
#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_EBANK_POS_MASK                   (0x08000000U)

#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_RDBNUM_SHIFT                     (4U)
#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_RDBNUM_MASK                      (0x00000030U)

#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_RDBSIZE_SHIFT                    (0U)
#define CTRL_WKUP_SECURE_EMIF1_LPDDR2_NVM_CONFIG_SDRAM_RDBSIZE_MASK                     (0x00000007U)

#define CTRL_WKUP_STD_FUSE_CONF_SPARE_SHIFT                                             (25U)
#define CTRL_WKUP_STD_FUSE_CONF_SPARE_MASK                                              (0x3e000000U)

#define CTRL_WKUP_STD_FUSE_CONF_HIGHLY_SECURE1_SHIFT                                    (24U)
#define CTRL_WKUP_STD_FUSE_CONF_HIGHLY_SECURE1_MASK                                     (0x01000000U)

#define CTRL_WKUP_STD_FUSE_CONF_HIGHLY_SECURE0_SHIFT                                    (23U)
#define CTRL_WKUP_STD_FUSE_CONF_HIGHLY_SECURE0_MASK                                     (0x00800000U)

#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_INITREF_DEF_DIS_SHIFT                             (19U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_INITREF_DEF_DIS_MASK                              (0x00080000U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_INITREF_DEF_DIS_DISABLED                           (1U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_INITREF_DEF_DIS_ENABLED                            (0U)

#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_DDR3_LPDDR2N_SHIFT                                (18U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_DDR3_LPDDR2N_MASK                                 (0x00040000U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_DDR3_LPDDR2N                                       (1U)
#define CTRL_WKUP_STD_FUSE_CONF_EMIF1_DDR3_LPDDR2N_LPDDR2                                (0U)

#define CTRL_WKUP_STD_FUSE_CONF_BGAP_REGISTER_ACCESS_SHIFT                              (17U)
#define CTRL_WKUP_STD_FUSE_CONF_BGAP_REGISTER_ACCESS_MASK                               (0x00020000U)
#define CTRL_WKUP_STD_FUSE_CONF_BGAP_REGISTER_ACCESS_DISABLED                            (1U)
#define CTRL_WKUP_STD_FUSE_CONF_BGAP_REGISTER_ACCESS_ENABLED                             (0U)

#define CTRL_WKUP_STD_FUSE_CONF_TEXTURE_COMPRESSION_ENABLE_SHIFT                        (15U)
#define CTRL_WKUP_STD_FUSE_CONF_TEXTURE_COMPRESSION_ENABLE_MASK                         (0x00008000U)
#define CTRL_WKUP_STD_FUSE_CONF_TEXTURE_COMPRESSION_ENABLE_ENABLED                       (1U)
#define CTRL_WKUP_STD_FUSE_CONF_TEXTURE_COMPRESSION_ENABLE_DISABLED                      (0U)

#define CTRL_WKUP_STD_FUSE_CONF_CRYPTO_DISABLE_SHIFT                                    (13U)
#define CTRL_WKUP_STD_FUSE_CONF_CRYPTO_DISABLE_MASK                                     (0x00002000U)
#define CTRL_WKUP_STD_FUSE_CONF_CRYPTO_DISABLE_DISABLED                                  (1U)
#define CTRL_WKUP_STD_FUSE_CONF_CRYPTO_DISABLE_ENABLED                                   (0U)

#define CTRL_WKUP_STD_FUSE_CONF_CH_SPEEDUP_DISABLE_SHIFT                                (12U)
#define CTRL_WKUP_STD_FUSE_CONF_CH_SPEEDUP_DISABLE_MASK                                 (0x00001000U)
#define CTRL_WKUP_STD_FUSE_CONF_CH_SPEEDUP_DISABLE_DISABLED                              (1U)
#define CTRL_WKUP_STD_FUSE_CONF_CH_SPEEDUP_DISABLE_ENABLED                               (0U)

#define CTRL_WKUP_STD_FUSE_CONF_ROM_HIDE_SHIFT                                          (11U)
#define CTRL_WKUP_STD_FUSE_CONF_ROM_HIDE_MASK                                           (0x00000800U)
#define CTRL_WKUP_STD_FUSE_CONF_ROM_HIDE_RESERVED                                        (1U)
#define CTRL_WKUP_STD_FUSE_CONF_ROM_HIDE_UNRESERVED                                      (0U)

#define CTRL_WKUP_STD_FUSE_CONF_DPLL_CLK_TRIMMING_DISABLE_SHIFT                         (10U)
#define CTRL_WKUP_STD_FUSE_CONF_DPLL_CLK_TRIMMING_DISABLE_MASK                          (0x00000400U)
#define CTRL_WKUP_STD_FUSE_CONF_DPLL_CLK_TRIMMING_DISABLE_DISABLED                       (1U)
#define CTRL_WKUP_STD_FUSE_CONF_DPLL_CLK_TRIMMING_DISABLE_ENABLED                        (0U)

#define CTRL_WKUP_STD_FUSE_CONF_DSS_VENC_MVENAB_SHIFT                                   (9U)
#define CTRL_WKUP_STD_FUSE_CONF_DSS_VENC_MVENAB_MASK                                    (0x00000200U)
#define CTRL_WKUP_STD_FUSE_CONF_DSS_VENC_MVENAB_ENABLED                                  (1U)
#define CTRL_WKUP_STD_FUSE_CONF_DSS_VENC_MVENAB_DISABLED                                 (0U)

#define CTRL_WKUP_STD_FUSE_CONF_BSC_ACCESS_PROTECT_SHIFT                                (1U)
#define CTRL_WKUP_STD_FUSE_CONF_BSC_ACCESS_PROTECT_MASK                                 (0x00000002U)

#define CTRL_WKUP_STD_FUSE_CONF_CUST_IEEE1500_DISABLE_SHIFT                             (0U)
#define CTRL_WKUP_STD_FUSE_CONF_CUST_IEEE1500_DISABLE_MASK                              (0x00000001U)

#define CTRL_WKUP_DPLL_CLK_TRIMMING_SHIFT                                               (0U)
#define CTRL_WKUP_DPLL_CLK_TRIMMING_MASK                                                (0xffffffffU)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_NARROW_ONLY_SHIFT                              (17U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_NARROW_ONLY_MASK                               (0x00020000U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_NARROW_ONLY_16_BITMODEONLY                      (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_NARROW_ONLY_32_BIT_16_BITMODE                   (0U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_ECC_SHIFT                                   (16U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_ECC_MASK                                    (0x00010000U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_ECC_ECCCANBEENABLED                          (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_ECC_ECCCANNOTBEENABLED                       (0U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_NUM_OF_SAMPLES_SHIFT                   (14U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_NUM_OF_SAMPLES_MASK                    (0x0000c000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_SEL_LOGIC_SHIFT                        (13U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_SEL_LOGIC_MASK                         (0x00002000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_ALL_DQ_MPR_RD_RESP_SHIFT               (12U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_ALL_DQ_MPR_RD_RESP_MASK                (0x00001000U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_OUTPUT_STATUS_SELECT_SHIFT             (9U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_REG_PHY_OUTPUT_STATUS_SELECT_MASK              (0x00000e00U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DYNAMIC_PWRDN_ENABLE_SHIFT                     (8U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DYNAMIC_PWRDN_ENABLE_MASK                      (0x00000100U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DISABLE_RESET_SHIFT                            (7U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DISABLE_RESET_MASK                             (0x00000080U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_PHY_RD_LOCAL_ODT_SHIFT                         (5U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_PHY_RD_LOCAL_ODT_MASK                          (0x00000060U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_STATIC_CMOSEN_ENABLE_SHIFT                     (4U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_STATIC_CMOSEN_ENABLE_MASK                      (0x00000010U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DFI_CLOCK_PHASE_SHIFT                          (3U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_DFI_CLOCK_PHASE_MASK                           (0x00000008U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_2_SHIFT                               (2U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_2_MASK                                (0x00000004U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_1_SHIFT                               (1U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_1_MASK                                (0x00000002U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_0_SHIFT                               (0U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_EN_SLICE_0_MASK                                (0x00000001U)

#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1_PHY_REG_READ_DATA_EYE_LVL_SHIFT              (0U)
#define CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT_1_PHY_REG_READ_DATA_EYE_LVL_MASK               (0xffffffffU)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_SHIFT                    (26U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_MASK                     (0x04000000U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_OCP                       (1U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_EFUSE                     (0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_IN_SHIFT                (21U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_IN_MASK                 (0x03e00000U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_OUT_SHIFT               (16U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_OUT_MASK                (0x001f0000U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_SHIFT                    (10U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_MASK                     (0x00000400U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_OCP                       (1U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_EFUSE                     (0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_IN_SHIFT                (5U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_IN_MASK                 (0x000003e0U)

#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_OUT_SHIFT               (0U)
#define CTRL_WKUP_LDOSRAM_CORE_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_OUT_MASK                (0x0000001fU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_0_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_0_MASK                                                (0xffffffffU)

#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_SHIFT                                         (6U)
#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_MASK                                          (0xffffffc0U)

#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_FIXED_SHIFT                                   (0U)
#define CTRL_WKUP_ID_CODE_STD_FUSE_IDCODE_FIXED_MASK                                    (0x0000003fU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_1_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_1_MASK                                                (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_2_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_2_MASK                                                (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_DIE_ID_3_SHIFT                                               (0U)
#define CTRL_WKUP_STD_FUSE_DIE_ID_3_MASK                                                (0xffffffffU)

#define CTRL_WKUP_STD_FUSE_PROD_ID_0_SHIFT                                              (0U)
#define CTRL_WKUP_STD_FUSE_PROD_ID_0_MASK                                               (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_WKUP_H_ */

