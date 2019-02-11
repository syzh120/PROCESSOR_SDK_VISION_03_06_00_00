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

#ifndef HW_ISS_H3A_H_
#define HW_ISS_H3A_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define H3A_PID                                                     (0x0U)
#define H3A_PCR                                                     (0x4U)
#define H3A_AFPAX1                                                  (0x8U)
#define H3A_AFPAX2                                                  (0xcU)
#define H3A_AFPAXSTART                                              (0x10U)
#define H3A_AFIIRSH                                                 (0x14U)
#define H3A_AFBUFST                                                 (0x18U)
#define H3A_AFCOEF010                                               (0x1cU)
#define H3A_AFCOEF032                                               (0x20U)
#define H3A_AFCOEF054                                               (0x24U)
#define H3A_AFCOEF076                                               (0x28U)
#define H3A_AFCOEF098                                               (0x2cU)
#define H3A_AFCOEF0010                                              (0x30U)
#define H3A_AFCOEF110                                               (0x34U)
#define H3A_AFCOEF132                                               (0x38U)
#define H3A_AFCOEF154                                               (0x3cU)
#define H3A_AFCOEF176                                               (0x40U)
#define H3A_AFCOEF198                                               (0x44U)
#define H3A_AFCOEF1010                                              (0x48U)
#define H3A_AEWWIN1                                                 (0x4cU)
#define H3A_AEWINSTART                                              (0x50U)
#define H3A_AEWINBLK                                                (0x54U)
#define H3A_AEWSUBWIN                                               (0x58U)
#define H3A_AEWBUFST                                                (0x5cU)
#define H3A_AEWCFG                                                  (0x60U)
#define H3A_LINE_START                                              (0x64U)
#define H3A_VFV_CFG1                                                (0x68U)
#define H3A_VFV_CFG2                                                (0x6cU)
#define H3A_VFV_CFG3                                                (0x70U)
#define H3A_VFV_CFG4                                                (0x74U)
#define H3A_HVF_THR                                                 (0x78U)
#define H3A_ADVANCED                                                (0x7cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define H3A_PID_MINOR_SHIFT                                                             (0U)
#define H3A_PID_MINOR_MASK                                                              (0x0000003fU)

#define H3A_PID_MAJOR_SHIFT                                                             (8U)
#define H3A_PID_MAJOR_MASK                                                              (0x00000700U)

#define H3A_PID_RTL_SHIFT                                                               (11U)
#define H3A_PID_RTL_MASK                                                                (0x0000f800U)

#define H3A_PID_FUNC_SHIFT                                                              (16U)
#define H3A_PID_FUNC_MASK                                                               (0x0fff0000U)

#define H3A_PID_SCHEME_SHIFT                                                            (30U)
#define H3A_PID_SCHEME_MASK                                                             (0xc0000000U)

#define H3A_PID_RESERVED_SHIFT                                                          (6U)
#define H3A_PID_RESERVED_MASK                                                           (0x000000c0U)

#define H3A_PID_RESERVED1_SHIFT                                                         (28U)
#define H3A_PID_RESERVED1_MASK                                                          (0x30000000U)

#define H3A_PCR_AF_EN_SHIFT                                                             (0U)
#define H3A_PCR_AF_EN_MASK                                                              (0x00000001U)
#define H3A_PCR_AF_EN_NEWENUM1                                                           (0U)
#define H3A_PCR_AF_EN_NEWENUM2                                                           (1U)

#define H3A_PCR_AF_ALAW_EN_SHIFT                                                        (1U)
#define H3A_PCR_AF_ALAW_EN_MASK                                                         (0x00000002U)
#define H3A_PCR_AF_ALAW_EN_NEWENUM1                                                      (0U)
#define H3A_PCR_AF_ALAW_EN_NEWENUM2                                                      (1U)

#define H3A_PCR_AF_MED_EN_SHIFT                                                         (2U)
#define H3A_PCR_AF_MED_EN_MASK                                                          (0x00000004U)
#define H3A_PCR_AF_MED_EN_NEWENUM1                                                       (0U)
#define H3A_PCR_AF_MED_EN_NEWENUM2                                                       (1U)

#define H3A_PCR_MED_TH_SHIFT                                                            (3U)
#define H3A_PCR_MED_TH_MASK                                                             (0x000007f8U)

#define H3A_PCR_FVMODE_SHIFT                                                            (14U)
#define H3A_PCR_FVMODE_MASK                                                             (0x00004000U)
#define H3A_PCR_FVMODE_NEWENUM1                                                          (0U)
#define H3A_PCR_FVMODE_NEWENUM2                                                          (1U)

#define H3A_PCR_BUSYAF_SHIFT                                                            (15U)
#define H3A_PCR_BUSYAF_MASK                                                             (0x00008000U)

#define H3A_PCR_AEW_EN_SHIFT                                                            (16U)
#define H3A_PCR_AEW_EN_MASK                                                             (0x00010000U)
#define H3A_PCR_AEW_EN_NEWENUM1                                                          (0U)
#define H3A_PCR_AEW_EN_NEWENUM2                                                          (1U)

#define H3A_PCR_AEW_ALAW_EN_SHIFT                                                       (17U)
#define H3A_PCR_AEW_ALAW_EN_MASK                                                        (0x00020000U)
#define H3A_PCR_AEW_ALAW_EN_NEWENUM1                                                     (0U)
#define H3A_PCR_AEW_ALAW_EN_NEWENUM2                                                     (1U)

#define H3A_PCR_BUSYAEAWB_SHIFT                                                         (18U)
#define H3A_PCR_BUSYAEAWB_MASK                                                          (0x00040000U)

#define H3A_PCR_AEW_MED_EN_SHIFT                                                        (19U)
#define H3A_PCR_AEW_MED_EN_MASK                                                         (0x00080000U)
#define H3A_PCR_AEW_MED_EN_NEWENUM1                                                      (0U)
#define H3A_PCR_AEW_MED_EN_NEWENUM2                                                      (1U)

#define H3A_PCR_AF_VF_EN_SHIFT                                                          (20U)
#define H3A_PCR_AF_VF_EN_MASK                                                           (0x00100000U)
#define H3A_PCR_AF_VF_EN_NEWENUM1                                                        (0U)
#define H3A_PCR_AF_VF_EN_NEWENUM2                                                        (1U)

#define H3A_PCR_AVE2LMT_SHIFT                                                           (22U)
#define H3A_PCR_AVE2LMT_MASK                                                            (0xffc00000U)

#define H3A_PCR_RGBPOS_SHIFT                                                            (11U)
#define H3A_PCR_RGBPOS_MASK                                                             (0x00003800U)

#define H3A_PCR_OVF_SHIFT                                                               (21U)
#define H3A_PCR_OVF_MASK                                                                (0x00200000U)
#define H3A_PCR_OVF_NEWENUM1                                                             (0U)
#define H3A_PCR_OVF_NEWENUM2                                                             (1U)

#define H3A_AFPAX1_PAXH_SHIFT                                                           (0U)
#define H3A_AFPAX1_PAXH_MASK                                                            (0x000000ffU)

#define H3A_AFPAX1_PAXW_SHIFT                                                           (16U)
#define H3A_AFPAX1_PAXW_MASK                                                            (0x00ff0000U)

#define H3A_AFPAX1_RESERVED_SHIFT                                                       (8U)
#define H3A_AFPAX1_RESERVED_MASK                                                        (0x0000ff00U)

#define H3A_AFPAX1_RESERVED1_SHIFT                                                      (24U)
#define H3A_AFPAX1_RESERVED1_MASK                                                       (0xff000000U)

#define H3A_AFPAX2_PAXHC_SHIFT                                                          (0U)
#define H3A_AFPAX2_PAXHC_MASK                                                           (0x0000003fU)

#define H3A_AFPAX2_PAXVC_SHIFT                                                          (6U)
#define H3A_AFPAX2_PAXVC_MASK                                                           (0x00001fc0U)

#define H3A_AFPAX2_AFINCV_SHIFT                                                         (13U)
#define H3A_AFPAX2_AFINCV_MASK                                                          (0x0001e000U)

#define H3A_AFPAX2_AFINCH_SHIFT                                                         (17U)
#define H3A_AFPAX2_AFINCH_MASK                                                          (0x001e0000U)

#define H3A_AFPAX2_RESERVED_SHIFT                                                       (21U)
#define H3A_AFPAX2_RESERVED_MASK                                                        (0xffe00000U)

#define H3A_AFPAXSTART_PAXSV_SHIFT                                                      (0U)
#define H3A_AFPAXSTART_PAXSV_MASK                                                       (0x00000fffU)

#define H3A_AFPAXSTART_PAXSH_SHIFT                                                      (16U)
#define H3A_AFPAXSTART_PAXSH_MASK                                                       (0x0fff0000U)

#define H3A_AFPAXSTART_RESERVED_SHIFT                                                   (12U)
#define H3A_AFPAXSTART_RESERVED_MASK                                                    (0x0000f000U)

#define H3A_AFPAXSTART_RESERVED1_SHIFT                                                  (28U)
#define H3A_AFPAXSTART_RESERVED1_MASK                                                   (0xf0000000U)

#define H3A_AFIIRSH_IIRSH_SHIFT                                                         (0U)
#define H3A_AFIIRSH_IIRSH_MASK                                                          (0x00000fffU)

#define H3A_AFIIRSH_RESERVED_SHIFT                                                      (12U)
#define H3A_AFIIRSH_RESERVED_MASK                                                       (0xfffff000U)

#define H3A_AFBUFST_SHIFT                                                               (5U)
#define H3A_AFBUFST_MASK                                                                (0xffffffe0U)

#define H3A_AFBUFST_RESERVED_SHIFT                                                      (0U)
#define H3A_AFBUFST_RESERVED_MASK                                                       (0x0000001fU)

#define H3A_AFCOEF010_COEFF0_SHIFT                                                      (0U)
#define H3A_AFCOEF010_COEFF0_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF010_COEFF1_SHIFT                                                      (16U)
#define H3A_AFCOEF010_COEFF1_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF010_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF010_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF010_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF010_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF032_COEFF2_SHIFT                                                      (0U)
#define H3A_AFCOEF032_COEFF2_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF032_COEFF3_SHIFT                                                      (16U)
#define H3A_AFCOEF032_COEFF3_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF032_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF032_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF032_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF032_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF054_COEFF4_SHIFT                                                      (0U)
#define H3A_AFCOEF054_COEFF4_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF054_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF054_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF054_COEFF5_SHIFT                                                      (16U)
#define H3A_AFCOEF054_COEFF5_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF054_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF054_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF076_COEFF6_SHIFT                                                      (0U)
#define H3A_AFCOEF076_COEFF6_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF076_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF076_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF076_COEFF7_SHIFT                                                      (16U)
#define H3A_AFCOEF076_COEFF7_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF076_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF076_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF098_COEFF8_SHIFT                                                      (0U)
#define H3A_AFCOEF098_COEFF8_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF098_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF098_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF098_COEFF9_SHIFT                                                      (16U)
#define H3A_AFCOEF098_COEFF9_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF098_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF098_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF0010_COEFF10_SHIFT                                                    (0U)
#define H3A_AFCOEF0010_COEFF10_MASK                                                     (0x00000fffU)

#define H3A_AFCOEF0010_RESERVED_SHIFT                                                   (12U)
#define H3A_AFCOEF0010_RESERVED_MASK                                                    (0xfffff000U)

#define H3A_AFCOEF110_COEFF0_SHIFT                                                      (0U)
#define H3A_AFCOEF110_COEFF0_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF110_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF110_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF110_COEFF1_SHIFT                                                      (16U)
#define H3A_AFCOEF110_COEFF1_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF110_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF110_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF132_COEFF2_SHIFT                                                      (0U)
#define H3A_AFCOEF132_COEFF2_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF132_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF132_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF132_COEFF3_SHIFT                                                      (16U)
#define H3A_AFCOEF132_COEFF3_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF132_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF132_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF154_COEFF4_SHIFT                                                      (0U)
#define H3A_AFCOEF154_COEFF4_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF154_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF154_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF154_COEFF5_SHIFT                                                      (16U)
#define H3A_AFCOEF154_COEFF5_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF154_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF154_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF176_COEFF6_SHIFT                                                      (0U)
#define H3A_AFCOEF176_COEFF6_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF176_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF176_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF176_COEFF7_SHIFT                                                      (16U)
#define H3A_AFCOEF176_COEFF7_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF176_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF176_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF198_COEFF8_SHIFT                                                      (0U)
#define H3A_AFCOEF198_COEFF8_MASK                                                       (0x00000fffU)

#define H3A_AFCOEF198_RESERVED_SHIFT                                                    (12U)
#define H3A_AFCOEF198_RESERVED_MASK                                                     (0x0000f000U)

#define H3A_AFCOEF198_COEFF9_SHIFT                                                      (16U)
#define H3A_AFCOEF198_COEFF9_MASK                                                       (0x0fff0000U)

#define H3A_AFCOEF198_RESERVED1_SHIFT                                                   (28U)
#define H3A_AFCOEF198_RESERVED1_MASK                                                    (0xf0000000U)

#define H3A_AFCOEF1010_COEFF10_SHIFT                                                    (0U)
#define H3A_AFCOEF1010_COEFF10_MASK                                                     (0x00000fffU)

#define H3A_AFCOEF1010_RESERVED_SHIFT                                                   (12U)
#define H3A_AFCOEF1010_RESERVED_MASK                                                    (0xfffff000U)

#define H3A_AEWWIN1_WINHC_SHIFT                                                         (0U)
#define H3A_AEWWIN1_WINHC_MASK                                                          (0x0000003fU)

#define H3A_AEWWIN1_WINVC_SHIFT                                                         (6U)
#define H3A_AEWWIN1_WINVC_MASK                                                          (0x00001fc0U)

#define H3A_AEWWIN1_WINW_SHIFT                                                          (13U)
#define H3A_AEWWIN1_WINW_MASK                                                           (0x001fe000U)

#define H3A_AEWWIN1_WINH_SHIFT                                                          (24U)
#define H3A_AEWWIN1_WINH_MASK                                                           (0xff000000U)

#define H3A_AEWWIN1_RESERVED_SHIFT                                                      (21U)
#define H3A_AEWWIN1_RESERVED_MASK                                                       (0x00e00000U)

#define H3A_AEWINSTART_WINSH_SHIFT                                                      (0U)
#define H3A_AEWINSTART_WINSH_MASK                                                       (0x00000fffU)

#define H3A_AEWINSTART_WINSV_SHIFT                                                      (16U)
#define H3A_AEWINSTART_WINSV_MASK                                                       (0x0fff0000U)

#define H3A_AEWINSTART_RESERVED_SHIFT                                                   (12U)
#define H3A_AEWINSTART_RESERVED_MASK                                                    (0x0000f000U)

#define H3A_AEWINSTART_RESERVED1_SHIFT                                                  (28U)
#define H3A_AEWINSTART_RESERVED1_MASK                                                   (0xf0000000U)

#define H3A_AEWINBLK_WINH_SHIFT                                                         (0U)
#define H3A_AEWINBLK_WINH_MASK                                                          (0x0000007fU)

#define H3A_AEWINBLK_WINSV_SHIFT                                                        (16U)
#define H3A_AEWINBLK_WINSV_MASK                                                         (0x0fff0000U)

#define H3A_AEWINBLK_RESERVED1_SHIFT                                                    (28U)
#define H3A_AEWINBLK_RESERVED1_MASK                                                     (0xf0000000U)

#define H3A_AEWINBLK_RESERVED_SHIFT                                                     (7U)
#define H3A_AEWINBLK_RESERVED_MASK                                                      (0x0000ff80U)

#define H3A_AEWSUBWIN_AEWINCH_SHIFT                                                     (0U)
#define H3A_AEWSUBWIN_AEWINCH_MASK                                                      (0x0000000fU)

#define H3A_AEWSUBWIN_AEWINCV_SHIFT                                                     (8U)
#define H3A_AEWSUBWIN_AEWINCV_MASK                                                      (0x00000f00U)

#define H3A_AEWSUBWIN_RESERVED_SHIFT                                                    (4U)
#define H3A_AEWSUBWIN_RESERVED_MASK                                                     (0x000000f0U)

#define H3A_AEWSUBWIN_RESERVED1_SHIFT                                                   (12U)
#define H3A_AEWSUBWIN_RESERVED1_MASK                                                    (0xfffff000U)

#define H3A_AEWBUFST_SHIFT                                                              (5U)
#define H3A_AEWBUFST_MASK                                                               (0xffffffe0U)

#define H3A_AEWBUFST_RESERVED_SHIFT                                                     (0U)
#define H3A_AEWBUFST_RESERVED_MASK                                                      (0x0000001fU)

#define H3A_AEWCFG_SUMSHFT_SHIFT                                                        (0U)
#define H3A_AEWCFG_SUMSHFT_MASK                                                         (0x0000000fU)

#define H3A_AEWCFG_AEFMT_SHIFT                                                          (8U)
#define H3A_AEWCFG_AEFMT_MASK                                                           (0x00000300U)

#define H3A_AEWCFG_RESERVED_SHIFT                                                       (4U)
#define H3A_AEWCFG_RESERVED_MASK                                                        (0x000000f0U)

#define H3A_AEWCFG_RESERVED1_SHIFT                                                      (10U)
#define H3A_AEWCFG_RESERVED1_MASK                                                       (0xfffffc00U)

#define H3A_LINE_START_SHIFT                                                            (0U)
#define H3A_LINE_START_MASK                                                             (0x0000ffffU)

#define H3A_LINE_START_SLV_SHIFT                                                        (16U)
#define H3A_LINE_START_SLV_MASK                                                         (0xffff0000U)

#define H3A_VFV_CFG1_VCOEF1_3_SHIFT                                                     (24U)
#define H3A_VFV_CFG1_VCOEF1_3_MASK                                                      (0xff000000U)

#define H3A_VFV_CFG1_VCOEF1_2_SHIFT                                                     (16U)
#define H3A_VFV_CFG1_VCOEF1_2_MASK                                                      (0x00ff0000U)

#define H3A_VFV_CFG1_VCOEF1_1_SHIFT                                                     (8U)
#define H3A_VFV_CFG1_VCOEF1_1_MASK                                                      (0x0000ff00U)

#define H3A_VFV_CFG1_VCOEF1_0_SHIFT                                                     (0U)
#define H3A_VFV_CFG1_VCOEF1_0_MASK                                                      (0x000000ffU)

#define H3A_VFV_CFG2_VCOEF1_4_SHIFT                                                     (0U)
#define H3A_VFV_CFG2_VCOEF1_4_MASK                                                      (0x000000ffU)

#define H3A_VFV_CFG2_VTHR1_SHIFT                                                        (16U)
#define H3A_VFV_CFG2_VTHR1_MASK                                                         (0xffff0000U)

#define H3A_VFV_CFG2_RESERVED_SHIFT                                                     (8U)
#define H3A_VFV_CFG2_RESERVED_MASK                                                      (0x0000ff00U)

#define H3A_VFV_CFG3_VCOEF2_3_SHIFT                                                     (24U)
#define H3A_VFV_CFG3_VCOEF2_3_MASK                                                      (0xff000000U)

#define H3A_VFV_CFG3_VCOEF2_2_SHIFT                                                     (16U)
#define H3A_VFV_CFG3_VCOEF2_2_MASK                                                      (0x00ff0000U)

#define H3A_VFV_CFG3_VCOEF2_1_SHIFT                                                     (8U)
#define H3A_VFV_CFG3_VCOEF2_1_MASK                                                      (0x0000ff00U)

#define H3A_VFV_CFG3_VCOEF2_0_SHIFT                                                     (0U)
#define H3A_VFV_CFG3_VCOEF2_0_MASK                                                      (0x000000ffU)

#define H3A_VFV_CFG4_VCOEF2_4_SHIFT                                                     (0U)
#define H3A_VFV_CFG4_VCOEF2_4_MASK                                                      (0x000000ffU)

#define H3A_VFV_CFG4_RESERVED_SHIFT                                                     (8U)
#define H3A_VFV_CFG4_RESERVED_MASK                                                      (0x0000ff00U)

#define H3A_VFV_CFG4_VTHR2_SHIFT                                                        (16U)
#define H3A_VFV_CFG4_VTHR2_MASK                                                         (0xffff0000U)

#define H3A_HVF_THR_HTHR1_SHIFT                                                         (0U)
#define H3A_HVF_THR_HTHR1_MASK                                                          (0x0000ffffU)

#define H3A_HVF_THR_HTHR2_SHIFT                                                         (16U)
#define H3A_HVF_THR_HTHR2_MASK                                                          (0xffff0000U)

#define H3A_ADVANCED_AF_MODE_SHIFT                                                      (0U)
#define H3A_ADVANCED_AF_MODE_MASK                                                       (0x00000001U)
#define H3A_ADVANCED_AF_MODE_NEWENUM1                                                    (0U)
#define H3A_ADVANCED_AF_MODE_NEWENUM2                                                    (1U)

#define H3A_ADVANCED_ID_SHIFT                                                           (16U)
#define H3A_ADVANCED_ID_MASK                                                            (0xffff0000U)
#define H3A_ADVANCED_ID_NEWENUM1                                                         (0U)

#define H3A_ADVANCED_RESERVED_SHIFT                                                     (1U)
#define H3A_ADVANCED_RESERVED_MASK                                                      (0x0000000eU)

#define H3A_ADVANCED_AEW_MODE_SHIFT                                                     (4U)
#define H3A_ADVANCED_AEW_MODE_MASK                                                      (0x00000010U)
#define H3A_ADVANCED_AEW_MODE_NEWENUM1                                                   (0U)
#define H3A_ADVANCED_AEW_MODE_NEWENUM2                                                   (1U)

#define H3A_ADVANCED_RESERVED1_SHIFT                                                    (5U)
#define H3A_ADVANCED_RESERVED1_MASK                                                     (0x0000ffe0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_H3A_H_ */

