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

#ifndef HW_ISS_SYS3_H_
#define HW_ISS_SYS3_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ISP_KEY_EN7                                                 (0x0U)
#define ISP_SWT_SEL                                                 (0x4U)
#define ISP_RESERVED0                                               (0x8U)
#define ISP_NSF3V_MODESET                                           (0xcU)
#define ISP_VP1_SPH                                                 (0x10U)
#define ISP_VP1_LNH                                                 (0x14U)
#define ISP_VP1_SLV                                                 (0x18U)
#define ISP_VP1_LNV                                                 (0x1cU)
#define ISP_NSF3V_CGAMMAWD                                          (0x20U)
#define ISP_VP1_CCDCFG                                              (0x24U)
#define ISP_VP1_DLAY                                                (0x28U)
#define ISP_RESERVED1                                               (0x2cU)
#define ISP_VP2_SPH                                                 (0x30U)
#define RSERVED2                                                    (0x34U)
#define ISP_VP2_SLV                                                 (0x38U)
#define ISP_RESERVED3                                               (0x3cU)
#define ISP_GLBCE_CGAMMAWD                                          (0x40U)
#define ISP_VP2_DLAY                                                (0x44U)
#define ISP_CNF_EN                                                  (0x50U)
#define ISP_CNFA_SIZ                                                (0x54U)
#define ISP_CNFB_SIZ                                                (0x58U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISP_KEY_EN7_KEY1_EN_SHIFT                                                       (0U)
#define ISP_KEY_EN7_KEY1_EN_MASK                                                        (0x00000001U)
#define ISP_KEY_EN7_KEY1_EN_DISABLE                                                      (0U)
#define ISP_KEY_EN7_KEY1_EN_ENABLE                                                       (1U)

#define ISP_KEY_EN7_RESERVED_SHIFT                                                      (2U)
#define ISP_KEY_EN7_RESERVED_MASK                                                       (0xfffffffcU)

#define ISP_KEY_EN7_KEY2_EN_SHIFT                                                       (1U)
#define ISP_KEY_EN7_KEY2_EN_MASK                                                        (0x00000002U)
#define ISP_KEY_EN7_KEY2_EN_DISABLE                                                      (0U)
#define ISP_KEY_EN7_KEY2_EN_ENABLE                                                       (1U)

#define ISP_SWT_SEL_NSF3V_SHIFT                                                         (0U)
#define ISP_SWT_SEL_NSF3V_MASK                                                          (0x00000003U)
#define ISP_SWT_SEL_NSF3V_DISABLE                                                        (0U)
#define ISP_SWT_SEL_NSF3V_CAL                                                            (1U)
#define ISP_SWT_SEL_NSF3V                                                                (2U)
#define ISP_SWT_SEL_NSF3V_RESERVED                                                       (3U)

#define ISP_SWT_SEL_GLBCE_SHIFT                                                         (8U)
#define ISP_SWT_SEL_GLBCE_MASK                                                          (0x00000300U)
#define ISP_SWT_SEL_GLBCE_DISABLE                                                        (0U)
#define ISP_SWT_SEL_GLBCE_CAL                                                            (1U)
#define ISP_SWT_SEL_GLBCE                                                                (2U)
#define ISP_SWT_SEL_GLBCE_RESERVED                                                       (3U)

#define ISP_SWT_SEL_RESERVED1_SHIFT                                                     (10U)
#define ISP_SWT_SEL_RESERVED1_MASK                                                      (0xfffffc00U)

#define ISP_SWT_SEL_DPC_SHIFT                                                           (4U)
#define ISP_SWT_SEL_DPC_MASK                                                            (0x00000010U)
#define ISP_SWT_SEL_DPC_ENABLE                                                           (1U)
#define ISP_SWT_SEL_DPC_DISABLE                                                          (0U)

#define ISP_SWT_SEL_RESERVED_SHIFT                                                      (2U)
#define ISP_SWT_SEL_RESERVED_MASK                                                       (0x0000000cU)

#define ISP_SWT_SEL_RESERVED2_SHIFT                                                     (5U)
#define ISP_SWT_SEL_RESERVED2_MASK                                                      (0x000000e0U)

#define ISP_RESERVED0_SHIFT                                                             (0U)
#define ISP_RESERVED0_MASK                                                              (0xffffffffU)

#define ISP_NSF3V_MODESET_INPMOD_SHIFT                                                  (12U)
#define ISP_NSF3V_MODESET_INPMOD_MASK                                                   (0x00003000U)
#define ISP_NSF3V_MODESET_INPMOD_NEWENUM1                                                (0U)
#define ISP_NSF3V_MODESET_INPMOD_NEWENUM2                                                (1U)
#define ISP_NSF3V_MODESET_INPMOD_NEWENUM3                                                (2U)
#define ISP_NSF3V_MODESET_INPMOD_NEWENUM4                                                (3U)

#define ISP_NSF3V_MODESET_DPOL_SHIFT                                                    (6U)
#define ISP_NSF3V_MODESET_DPOL_MASK                                                     (0x00000040U)
#define ISP_NSF3V_MODESET_DPOL_NEWENUM1                                                  (0U)
#define ISP_NSF3V_MODESET_DPOL_NEWENUM2                                                  (1U)

#define ISP_NSF3V_MODESET_HDPOL_SHIFT                                                   (3U)
#define ISP_NSF3V_MODESET_HDPOL_MASK                                                    (0x00000008U)
#define ISP_NSF3V_MODESET_HDPOL_NEWENUM1                                                 (0U)
#define ISP_NSF3V_MODESET_HDPOL_NEWENUM2                                                 (1U)

#define ISP_NSF3V_MODESET_VDPOL_SHIFT                                                   (2U)
#define ISP_NSF3V_MODESET_VDPOL_MASK                                                    (0x00000004U)
#define ISP_NSF3V_MODESET_VDPOL_NEWENUM1                                                 (0U)
#define ISP_NSF3V_MODESET_VDPOL_NEWENUM2                                                 (1U)

#define ISP_NSF3V_MODESET_RESERVED_SHIFT                                                (0U)
#define ISP_NSF3V_MODESET_RESERVED_MASK                                                 (0x00000003U)

#define ISP_NSF3V_MODESET_RESERVED2_SHIFT                                               (7U)
#define ISP_NSF3V_MODESET_RESERVED2_MASK                                                (0x00000f80U)

#define ISP_NSF3V_MODESET_RESERVED3_SHIFT                                               (14U)
#define ISP_NSF3V_MODESET_RESERVED3_MASK                                                (0xffffc000U)

#define ISP_NSF3V_MODESET_RESERVED1_SHIFT                                               (4U)
#define ISP_NSF3V_MODESET_RESERVED1_MASK                                                (0x00000030U)

#define ISP_VP1_SPH_SHIFT                                                               (0U)
#define ISP_VP1_SPH_MASK                                                                (0x00007fffU)

#define ISP_VP1_SPH_RESERVED_SHIFT                                                      (15U)
#define ISP_VP1_SPH_RESERVED_MASK                                                       (0xffff8000U)

#define ISP_VP1_LNH_SHIFT                                                               (0U)
#define ISP_VP1_LNH_MASK                                                                (0x00007fffU)

#define ISP_VP1_LNH_RESERVED_SHIFT                                                      (15U)
#define ISP_VP1_LNH_RESERVED_MASK                                                       (0xffff8000U)

#define ISP_VP1_SLV_SHIFT                                                               (0U)
#define ISP_VP1_SLV_MASK                                                                (0x00007fffU)

#define ISP_VP1_SLV_RESERVED_SHIFT                                                      (15U)
#define ISP_VP1_SLV_RESERVED_MASK                                                       (0xffff8000U)

#define ISP_VP1_LNV_SHIFT                                                               (0U)
#define ISP_VP1_LNV_MASK                                                                (0x00007fffU)

#define ISP_VP1_LNV_RESERVED_SHIFT                                                      (15U)
#define ISP_VP1_LNV_RESERVED_MASK                                                       (0xffff8000U)

#define ISP_NSF3V_CGAMMAWD_GWDI_SHIFT                                                   (1U)
#define ISP_NSF3V_CGAMMAWD_GWDI_MASK                                                    (0x0000001eU)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT15                                                    (0U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT14                                                    (1U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT13                                                    (2U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT12                                                    (3U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT11                                                    (4U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT10                                                    (5U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT9                                                     (6U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT8                                                     (7U)
#define ISP_NSF3V_CGAMMAWD_GWDI_BIT7                                                     (8U)
#define ISP_NSF3V_CGAMMAWD_GWDI_NEWENUM10                                                (9U)

#define ISP_NSF3V_CGAMMAWD_RESERVED_SHIFT                                               (0U)
#define ISP_NSF3V_CGAMMAWD_RESERVED_MASK                                                (0x00000001U)

#define ISP_NSF3V_CGAMMAWD_RESERVED1_SHIFT                                              (5U)
#define ISP_NSF3V_CGAMMAWD_RESERVED1_MASK                                               (0xffffffe0U)

#define ISP_VP1_CCDCFG_Y8POS_SHIFT                                                      (11U)
#define ISP_VP1_CCDCFG_Y8POS_MASK                                                       (0x00000800U)
#define ISP_VP1_CCDCFG_Y8POS_EVEN                                                        (0U)
#define ISP_VP1_CCDCFG_Y8POS_ODD                                                         (1U)

#define ISP_VP1_CCDCFG_YCINSWP_SHIFT                                                    (4U)
#define ISP_VP1_CCDCFG_YCINSWP_MASK                                                     (0x00000010U)
#define ISP_VP1_CCDCFG_YCINSWP_NEWENUM1                                                  (0U)
#define ISP_VP1_CCDCFG_YCINSWP_NEWENUM2                                                  (1U)

#define ISP_VP1_CCDCFG_RESERVED_SHIFT                                                   (0U)
#define ISP_VP1_CCDCFG_RESERVED_MASK                                                    (0x0000000fU)

#define ISP_VP1_CCDCFG_RESERVED1_SHIFT                                                  (5U)
#define ISP_VP1_CCDCFG_RESERVED1_MASK                                                   (0x000007e0U)

#define ISP_VP1_CCDCFG_EE_SHIFT                                                         (16U)
#define ISP_VP1_CCDCFG_EE_MASK                                                          (0x00030000U)
#define ISP_VP1_CCDCFG_EE_R                                                             (0x00000000U)
#define ISP_VP1_CCDCFG_EE_GR                                                            (0x00010000U)
#define ISP_VP1_CCDCFG_EE_GB                                                            (0x00020000U)
#define ISP_VP1_CCDCFG_EE_B                                                             (0x00030000U)

#define ISP_VP1_CCDCFG_EO_SHIFT                                                         (18U)
#define ISP_VP1_CCDCFG_EO_MASK                                                          (0x000c0000U)
#define ISP_VP1_CCDCFG_EO_R                                                             (0x00000000U)
#define ISP_VP1_CCDCFG_EO_GR                                                            (0x00040000U)
#define ISP_VP1_CCDCFG_EO_GB                                                            (0x00080000U)
#define ISP_VP1_CCDCFG_EO_B                                                             (0x000C0000U)

#define ISP_VP1_CCDCFG_OE_SHIFT                                                         (20U)
#define ISP_VP1_CCDCFG_OE_MASK                                                          (0x00300000U)
#define ISP_VP1_CCDCFG_OE_R                                                             (0x00000000U)
#define ISP_VP1_CCDCFG_OE_GR                                                            (0x00100000U)
#define ISP_VP1_CCDCFG_OE_GB                                                            (0x00200000U)
#define ISP_VP1_CCDCFG_OE_B                                                             (0x00300000U)

#define ISP_VP1_CCDCFG_OO_SHIFT                                                         (22U)
#define ISP_VP1_CCDCFG_OO_MASK                                                          (0x00c00000U)
#define ISP_VP1_CCDCFG_OO_R                                                             (0x00000000U)
#define ISP_VP1_CCDCFG_OO_GR                                                            (0x00400000U)
#define ISP_VP1_CCDCFG_OO_GB                                                            (0x00800000U)
#define ISP_VP1_CCDCFG_OO_B                                                             (0x00C00000U)

#define ISP_VP1_CCDCFG_RESERVED2_SHIFT                                                  (12U)
#define ISP_VP1_CCDCFG_RESERVED2_MASK                                                   (0x0000f000U)

#define ISP_VP1_CCDCFG_RESERVED3_SHIFT                                                  (24U)
#define ISP_VP1_CCDCFG_RESERVED3_MASK                                                   (0xff000000U)

#define ISP_VP1_DLAY_DLH_SHIFT                                                          (0U)
#define ISP_VP1_DLAY_DLH_MASK                                                           (0x000000ffU)

#define ISP_VP1_DLAY_DLV_SHIFT                                                          (16U)
#define ISP_VP1_DLAY_DLV_MASK                                                           (0x00ff0000U)

#define ISP_VP1_DLAY_RESERVED_SHIFT                                                     (8U)
#define ISP_VP1_DLAY_RESERVED_MASK                                                      (0x0000ff00U)

#define ISP_VP1_DLAY_RESERVED1_SHIFT                                                    (24U)
#define ISP_VP1_DLAY_RESERVED1_MASK                                                     (0x3f000000U)

#define ISP_VP1_DLAY_DELAY_SWT_SHIFT                                                    (30U)
#define ISP_VP1_DLAY_DELAY_SWT_MASK                                                     (0x40000000U)
#define ISP_VP1_DLAY_DELAY_SWT_DISABLE                                                   (0U)
#define ISP_VP1_DLAY_DELAY_SWT_ENABLE                                                    (1U)

#define ISP_VP1_DLAY_RESERVED2_SHIFT                                                    (31U)
#define ISP_VP1_DLAY_RESERVED2_MASK                                                     (0x80000000U)

#define ISP_RESERVED1_RESERVED3_SHIFT                                                   (0U)
#define ISP_RESERVED1_RESERVED3_MASK                                                    (0xffffffffU)

#define ISP_VP2_SPH_SHIFT                                                               (0U)
#define ISP_VP2_SPH_MASK                                                                (0x00007fffU)

#define ISP_VP2_SPH_RESERVED_SHIFT                                                      (15U)
#define ISP_VP2_SPH_RESERVED_MASK                                                       (0xffff8000U)

#define RSERVED2_RESERVED_SHIFT                                                         (0U)
#define RSERVED2_RESERVED_MASK                                                          (0xffffffffU)

#define ISP_VP2_SLV_SHIFT                                                               (0U)
#define ISP_VP2_SLV_MASK                                                                (0x00007fffU)

#define ISP_VP2_SLV_RESERVED_SHIFT                                                      (15U)
#define ISP_VP2_SLV_RESERVED_MASK                                                       (0xffff8000U)

#define ISP_RESERVED3_RESERVED_SHIFT                                                    (0U)
#define ISP_RESERVED3_RESERVED_MASK                                                     (0xffffffffU)

#define ISP_GLBCE_CGAMMAWD_GWDI_SHIFT                                                   (1U)
#define ISP_GLBCE_CGAMMAWD_GWDI_MASK                                                    (0x0000001eU)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT15                                                    (0U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT14                                                    (1U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT13                                                    (2U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT12                                                    (3U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT11                                                    (4U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT10                                                    (5U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT9                                                     (6U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT8                                                     (7U)
#define ISP_GLBCE_CGAMMAWD_GWDI_BIT7                                                     (8U)
#define ISP_GLBCE_CGAMMAWD_GWDI_OTHERS                                                   (9U)

#define ISP_GLBCE_CGAMMAWD_RESERVED_SHIFT                                               (0U)
#define ISP_GLBCE_CGAMMAWD_RESERVED_MASK                                                (0x00000001U)

#define ISP_GLBCE_CGAMMAWD_GWDO_SHIFT                                                   (8U)
#define ISP_GLBCE_CGAMMAWD_GWDO_MASK                                                    (0x00000f00U)
#define ISP_GLBCE_CGAMMAWD_GWDO_16BIT                                                    (0U)
#define ISP_GLBCE_CGAMMAWD_GWDO_15BIT                                                    (1U)
#define ISP_GLBCE_CGAMMAWD_GWDO_14BIT                                                    (2U)
#define ISP_GLBCE_CGAMMAWD_GWDO_13BIT                                                    (3U)
#define ISP_GLBCE_CGAMMAWD_GWDO_12BIT                                                    (4U)
#define ISP_GLBCE_CGAMMAWD_GWDO_11BIT                                                    (5U)
#define ISP_GLBCE_CGAMMAWD_GWDO_10BIT                                                    (6U)
#define ISP_GLBCE_CGAMMAWD_GWDO_9BIT                                                     (7U)
#define ISP_GLBCE_CGAMMAWD_GWDO_8BIT                                                     (8U)
#define ISP_GLBCE_CGAMMAWD_GWDO_OTHERS                                                   (9U)

#define ISP_GLBCE_CGAMMAWD_RESERVED1_SHIFT                                              (5U)
#define ISP_GLBCE_CGAMMAWD_RESERVED1_MASK                                               (0x000000e0U)

#define ISP_GLBCE_CGAMMAWD_RESERVED2_SHIFT                                              (12U)
#define ISP_GLBCE_CGAMMAWD_RESERVED2_MASK                                               (0xfffff000U)

#define ISP_VP2_DLAY_DLH_SHIFT                                                          (0U)
#define ISP_VP2_DLAY_DLH_MASK                                                           (0x000000ffU)

#define ISP_VP2_DLAY_DLV_SHIFT                                                          (16U)
#define ISP_VP2_DLAY_DLV_MASK                                                           (0x00ff0000U)

#define ISP_VP2_DLAY_RESERVED_SHIFT                                                     (8U)
#define ISP_VP2_DLAY_RESERVED_MASK                                                      (0x0000ff00U)

#define ISP_VP2_DLAY_RESERVED1_SHIFT                                                    (24U)
#define ISP_VP2_DLAY_RESERVED1_MASK                                                     (0xff000000U)

#define ISP_CNF_EN_CNFA_SHIFT                                                           (0U)
#define ISP_CNF_EN_CNFA_MASK                                                            (0x00000001U)
#define ISP_CNF_EN_CNFA_ENABLED                                                          (1U)
#define ISP_CNF_EN_CNFA_DISABLED                                                         (0U)

#define ISP_CNF_EN_CNFA_CDSEN_SHIFT                                                     (1U)
#define ISP_CNF_EN_CNFA_CDSEN_MASK                                                      (0x00000002U)
#define ISP_CNF_EN_CNFA_CDSEN_ENABLED                                                    (1U)
#define ISP_CNF_EN_CNFA_CDSEN_DISABLED                                                   (0U)

#define ISP_CNF_EN_CNFB_SHIFT                                                           (4U)
#define ISP_CNF_EN_CNFB_MASK                                                            (0x00000010U)
#define ISP_CNF_EN_CNFB_ENABLED                                                          (1U)
#define ISP_CNF_EN_CNFB_DISABLED                                                         (0U)

#define ISP_CNF_EN_CNFB_CDSEN_SHIFT                                                     (5U)
#define ISP_CNF_EN_CNFB_CDSEN_MASK                                                      (0x00000020U)
#define ISP_CNF_EN_CNFB_CDSEN_ENABLED                                                    (1U)
#define ISP_CNF_EN_CNFB_CDSEN_DISABLED                                                   (0U)

#define ISP_CNF_EN_RESERVED_SHIFT                                                       (2U)
#define ISP_CNF_EN_RESERVED_MASK                                                        (0x0000000cU)

#define ISP_CNF_EN_RESERVED1_SHIFT                                                      (6U)
#define ISP_CNF_EN_RESERVED1_MASK                                                       (0xffffffc0U)

#define ISP_CNFA_SIZ_WIDTH_SHIFT                                                        (0U)
#define ISP_CNFA_SIZ_WIDTH_MASK                                                         (0x00003fffU)

#define ISP_CNFA_SIZ_HEIGHT_SHIFT                                                       (16U)
#define ISP_CNFA_SIZ_HEIGHT_MASK                                                        (0x3fff0000U)

#define ISP_CNFA_SIZ_RESERVED_SHIFT                                                     (14U)
#define ISP_CNFA_SIZ_RESERVED_MASK                                                      (0x0000c000U)

#define ISP_CNFA_SIZ_RESERVED1_SHIFT                                                    (30U)
#define ISP_CNFA_SIZ_RESERVED1_MASK                                                     (0xc0000000U)

#define ISP_CNFB_SIZ_WIDTH_SHIFT                                                        (0U)
#define ISP_CNFB_SIZ_WIDTH_MASK                                                         (0x00003fffU)

#define ISP_CNFB_SIZ_HEIGHT_SHIFT                                                       (16U)
#define ISP_CNFB_SIZ_HEIGHT_MASK                                                        (0x3fff0000U)

#define ISP_CNFB_SIZ_RESERVED_SHIFT                                                     (14U)
#define ISP_CNFB_SIZ_RESERVED_MASK                                                      (0x0000c000U)

#define ISP_CNFB_SIZ_RESERVED1_SHIFT                                                    (30U)
#define ISP_CNFB_SIZ_RESERVED1_MASK                                                     (0xc0000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_SYS3_H_ */

