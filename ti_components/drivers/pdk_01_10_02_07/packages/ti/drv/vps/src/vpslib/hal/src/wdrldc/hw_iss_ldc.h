/*
* hw_iss_ldc.h
*
* Register-level header file for ISS_LDC
*
* Copyright (c) 2013 Texas Instruments Incorporated.
*
* Except for those rights granted to you in your license from TI,
* all rights reserved.
*
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR
* STATUTORY.  EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES
* OF NON-INFRINGEMENT, BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY.
* FURTHERMORE, TI SHALL NOT, UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
* INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
*/

#ifndef HW_ISS_LDC_H_
#define HW_ISS_LDC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define LDC_PID                                                     (0x0U)
#define LDC_PCR                                                     (0x4U)
#define LDC_RD_BASE                                                 (0x8U)
#define LDC_RD_OFST                                                 (0xcU)
#define LDC_FRAME_SIZE                                              (0x10U)
#define LDC_INITXY                                                  (0x14U)
#define LDC_WR_BASE                                                 (0x18U)
#define LDC_WR_OFST                                                 (0x1cU)
#define LDC_420C_RD_BASE                                            (0x20U)
#define LDC_420C_WR_BASE                                            (0x24U)
#define LDC_CONFIG                                                  (0x28U)
#define LDC_BLOCK                                                   (0x34U)
#define LDC_AB                                                      (0x44U)
#define LDC_CD                                                      (0x48U)
#define LDC_EF                                                      (0x4cU)
#define LDC_GH                                                      (0x50U)
#define LDC_SCS_CTL                                                 (0x54U)
#define LDC_INPUT_FRAME_SIZE                                        (0x58U)
#define LDC_MESHTABLE_BASE                                          (0x5cU)
#define LDC_MESHTABLE_OFST                                          (0x60U)
#define LDC_MESHTABLE_CONFIG                                        (0x64U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define LDC_PID_TID_SHIFT                                                               (16U)
#define LDC_PID_TID_MASK                                                                (0x00ff0000U)

#define LDC_PID_CID_SHIFT                                                               (8U)
#define LDC_PID_CID_MASK                                                                (0x0000ff00U)

#define LDC_PID_PREV_SHIFT                                                              (0U)
#define LDC_PID_PREV_MASK                                                               (0x000000ffU)

#define LDC_PID_RSVD_SHIFT                                                              (24U)
#define LDC_PID_RSVD_MASK                                                               (0xff000000U)

#define LDC_PCR_EN_SHIFT                                                                (0U)
#define LDC_PCR_EN_MASK                                                                 (0x00000001U)

#define LDC_PCR_MODE_SHIFT                                                              (3U)
#define LDC_PCR_MODE_MASK                                                               (0x00000018U)

#define LDC_PCR_BUSY_SHIFT                                                              (2U)
#define LDC_PCR_BUSY_MASK                                                               (0x00000004U)

#define LDC_PCR_LDMAPEN_SHIFT                                                           (1U)
#define LDC_PCR_LDMAPEN_MASK                                                            (0x00000002U)

#define LDC_PCR_BMODE_SHIFT                                                             (5U)
#define LDC_PCR_BMODE_MASK                                                              (0x00000060U)

#define LDC_PCR_PWARPEN_SHIFT                                                           (7U)
#define LDC_PCR_PWARPEN_MASK                                                            (0x00000080U)

#define LDC_PCR_CIRCEN_SHIFT                                                            (9U)
#define LDC_PCR_CIRCEN_MASK                                                             (0x00000200U)

#define LDC_PCR_SCSEN_SHIFT                                                             (8U)
#define LDC_PCR_SCSEN_MASK                                                              (0x00000100U)

#define LDC_PCR_RSVD_SHIFT                                                              (12U)
#define LDC_PCR_RSVD_MASK                                                               (0x0000f000U)

#define LDC_PCR_STANDBYMODE_SHIFT                                                       (16U)
#define LDC_PCR_STANDBYMODE_MASK                                                        (0x00030000U)

#define LDC_PCR_RSVD1_SHIFT                                                             (18U)
#define LDC_PCR_RSVD1_MASK                                                              (0xfffc0000U)

#define LDC_PCR_SCS_SUPPORT_SHIFT                                                       (11U)
#define LDC_PCR_SCS_SUPPORT_MASK                                                        (0x00000800U)

#define LDC_PCR_AFF_EXPANDEN_SHIFT                                                      (10U)
#define LDC_PCR_AFF_EXPANDEN_MASK                                                       (0x00000400U)

#define LDC_RD_BASE_RBASE_SHIFT                                                         (0U)
#define LDC_RD_BASE_RBASE_MASK                                                          (0xffffffffU)

#define LDC_RD_OFST_ROFST_SHIFT                                                         (0U)
#define LDC_RD_OFST_ROFST_MASK                                                          (0x0000ffffU)

#define LDC_RD_OFST_RSVD_SHIFT                                                          (30U)
#define LDC_RD_OFST_RSVD_MASK                                                           (0xc0000000U)

#define LDC_RD_OFST_MOD_SHIFT                                                           (16U)
#define LDC_RD_OFST_MOD_MASK                                                            (0x3fff0000U)

#define LDC_FRAME_SIZE_W_SHIFT                                                          (0U)
#define LDC_FRAME_SIZE_W_MASK                                                           (0x00003fffU)

#define LDC_FRAME_SIZE_H_SHIFT                                                          (16U)
#define LDC_FRAME_SIZE_H_MASK                                                           (0x3fff0000U)

#define LDC_FRAME_SIZE_RSVD1_SHIFT                                                      (30U)
#define LDC_FRAME_SIZE_RSVD1_MASK                                                       (0xc0000000U)

#define LDC_FRAME_SIZE_RSVD0_SHIFT                                                      (14U)
#define LDC_FRAME_SIZE_RSVD0_MASK                                                       (0x0000c000U)

#define LDC_INITXY_INITX_SHIFT                                                          (0U)
#define LDC_INITXY_INITX_MASK                                                           (0x00003fffU)

#define LDC_INITXY_INITY_SHIFT                                                          (16U)
#define LDC_INITXY_INITY_MASK                                                           (0x3fff0000U)

#define LDC_INITXY_RSVD1_SHIFT                                                          (30U)
#define LDC_INITXY_RSVD1_MASK                                                           (0xc0000000U)

#define LDC_INITXY_RSVD0_SHIFT                                                          (14U)
#define LDC_INITXY_RSVD0_MASK                                                           (0x0000c000U)

#define LDC_WR_BASE_WBASE_SHIFT                                                         (0U)
#define LDC_WR_BASE_WBASE_MASK                                                          (0xffffffffU)

#define LDC_WR_OFST_WOFST_SHIFT                                                         (0U)
#define LDC_WR_OFST_WOFST_MASK                                                          (0x0000ffffU)

#define LDC_WR_OFST_RSVD_SHIFT                                                          (16U)
#define LDC_WR_OFST_RSVD_MASK                                                           (0xffff0000U)

#define LDC_420C_RD_BASE_RBASE_SHIFT                                                    (0U)
#define LDC_420C_RD_BASE_RBASE_MASK                                                     (0xffffffffU)

#define LDC_420C_WR_BASE_WBASE_SHIFT                                                    (0U)
#define LDC_420C_WR_BASE_WBASE_MASK                                                     (0xffffffffU)

#define LDC_CONFIG_INITC_SHIFT                                                          (4U)
#define LDC_CONFIG_INITC_MASK                                                           (0x00000030U)

#define LDC_CONFIG_RSVD0_SHIFT                                                          (0U)
#define LDC_CONFIG_RSVD0_MASK                                                           (0x0000000fU)

#define LDC_CONFIG_YINT_TYP_SHIFT                                                       (6U)
#define LDC_CONFIG_YINT_TYP_MASK                                                        (0x00000040U)

#define LDC_CONFIG_RSVD1_SHIFT                                                          (8U)
#define LDC_CONFIG_RSVD1_MASK                                                           (0xffffff00U)

#define LDC_CONFIG_CNST_MD_SHIFT                                                        (7U)
#define LDC_CONFIG_CNST_MD_MASK                                                         (0x00000080U)

#define LDC_BLOCK_OBW_SHIFT                                                             (0U)
#define LDC_BLOCK_OBW_MASK                                                              (0x000000ffU)

#define LDC_BLOCK_OBH_SHIFT                                                             (8U)
#define LDC_BLOCK_OBH_MASK                                                              (0x0000ff00U)

#define LDC_BLOCK_PIXPAD_SHIFT                                                          (16U)
#define LDC_BLOCK_PIXPAD_MASK                                                           (0x000f0000U)

#define LDC_BLOCK_RSVD_SHIFT                                                            (20U)
#define LDC_BLOCK_RSVD_MASK                                                             (0xfff00000U)

#define LDC_AB_A_SHIFT                                                                  (0U)
#define LDC_AB_A_MASK                                                                   (0x0000ffffU)

#define LDC_AB_B_SHIFT                                                                  (16U)
#define LDC_AB_B_MASK                                                                   (0xffff0000U)

#define LDC_CD_C_SHIFT                                                                  (0U)
#define LDC_CD_C_MASK                                                                   (0x0000ffffU)

#define LDC_CD_D_SHIFT                                                                  (16U)
#define LDC_CD_D_MASK                                                                   (0xffff0000U)

#define LDC_EF_E_SHIFT                                                                  (0U)
#define LDC_EF_E_MASK                                                                   (0x0000ffffU)

#define LDC_EF_F_SHIFT                                                                  (16U)
#define LDC_EF_F_MASK                                                                   (0xffff0000U)

#define LDC_GH_G_SHIFT                                                                  (0U)
#define LDC_GH_G_MASK                                                                   (0x0000ffffU)

#define LDC_GH_H_SHIFT                                                                  (16U)
#define LDC_GH_H_MASK                                                                   (0xffff0000U)

#define LDC_SCS_CTL_ACCSHIFT_SHIFT                                                      (0U)
#define LDC_SCS_CTL_ACCSHIFT_MASK                                                       (0x0000001fU)

#define LDC_SCS_CTL_REGION_SHIFT                                                        (5U)
#define LDC_SCS_CTL_REGION_MASK                                                         (0x00000060U)

#define LDC_SCS_CTL_RSVD_SHIFT                                                          (7U)
#define LDC_SCS_CTL_RSVD_MASK                                                           (0x0000ff80U)

#define LDC_SCS_CTL_SLICE_SIZE_SHIFT                                                    (16U)
#define LDC_SCS_CTL_SLICE_SIZE_MASK                                                     (0x3fff0000U)

#define LDC_SCS_CTL_RSVD1_SHIFT                                                         (30U)
#define LDC_SCS_CTL_RSVD1_MASK                                                          (0xc0000000U)

#define LDC_INPUT_FRAME_SIZE_W_SHIFT                                                    (0U)
#define LDC_INPUT_FRAME_SIZE_W_MASK                                                     (0x00003fffU)

#define LDC_INPUT_FRAME_SIZE_RSVD0_SHIFT                                                (14U)
#define LDC_INPUT_FRAME_SIZE_RSVD0_MASK                                                 (0x0000c000U)

#define LDC_INPUT_FRAME_SIZE_H_SHIFT                                                    (16U)
#define LDC_INPUT_FRAME_SIZE_H_MASK                                                     (0x3fff0000U)

#define LDC_INPUT_FRAME_SIZE_RSVD1_SHIFT                                                (30U)
#define LDC_INPUT_FRAME_SIZE_RSVD1_MASK                                                 (0xc0000000U)

#define LDC_MESHTABLE_BASE_SHIFT                                                        (0U)
#define LDC_MESHTABLE_BASE_MASK                                                         (0xffffffffU)

#define LDC_MESHTABLE_OFST_SHIFT                                                        (0U)
#define LDC_MESHTABLE_OFST_MASK                                                         (0x0000ffffU)

#define LDC_MESHTABLE_OFST_RSVD_SHIFT                                                   (16U)
#define LDC_MESHTABLE_OFST_RSVD_MASK                                                    (0xffff0000U)

#define LDC_MESHTABLE_CONFIG_M_SHIFT                                                    (0U)
#define LDC_MESHTABLE_CONFIG_M_MASK                                                     (0x00000007U)

#define LDC_MESHTABLE_CONFIG_RSVD_SHIFT                                                 (3U)
#define LDC_MESHTABLE_CONFIG_RSVD_MASK                                                  (0xfffffff8U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_LDC_H_ */

