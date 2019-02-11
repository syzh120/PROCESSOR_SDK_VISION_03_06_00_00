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

#ifndef HW_ISS_IPIPEIF_H_
#define HW_ISS_IPIPEIF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define IPIPEIF_ENABLE                                              (0x0U)
#define IPIPEIF_CFG1                                                (0x4U)
#define IPIPEIF_PPLN                                                (0x8U)
#define IPIPEIF_LPFR                                                (0xcU)
#define IPIPEIF_HNUM                                                (0x10U)
#define IPIPEIF_VNUM                                                (0x14U)
#define IPIPEIF_ADDRU                                               (0x18U)
#define IPIPEIF_ADDRL                                               (0x1cU)
#define IPIPEIF_ADOFS                                               (0x20U)
#define IPIPEIF_RSZ                                                 (0x24U)
#define IPIPEIF_GAIN                                                (0x28U)
#define IPIPEIF_DPCM                                                (0x2cU)
#define IPIPEIF_CFG2                                                (0x30U)
#define IPIPEIF_INIRSZ                                              (0x34U)
#define IPIPEIF_OCLIP                                               (0x38U)
#define IPIPEIF_DTUDF                                               (0x3cU)
#define IPIPEIF_CLKDIV                                              (0x40U)
#define IPIPEIF_DPC1                                                (0x44U)
#define IPIPEIF_DPC2                                                (0x48U)
#define IPIPEIF_DFSGVL                                              (0x4cU)
#define IPIPEIF_DFSGTH                                              (0x50U)
#define IPIPEIF_RSZ3A                                               (0x54U)
#define IPIPEIF_INIRSZ3A                                            (0x58U)
#define IPIPEIF_CFG3                                                (0x5cU)
#define IPIPEIF_CFG4                                                (0x60U)
#define IPIPEIF_WDRAF                                               (0x64U)
#define IPIPEIF_WDRBF                                               (0x68U)
#define IPIPEIF_WDRGAIN                                             (0x6cU)
#define IPIPEIF_WDRTHR                                              (0x70U)
#define IPIPEIF_RSVD1                                               (0x74U)
#define IPIPEIF_RSVD2                                               (0x78U)
#define IPIPEIF_WDRLBK1                                             (0x7cU)
#define IPIPEIF_WDRLBK2                                             (0x80U)
#define IPIPEIF_WDRSBK1                                             (0x84U)
#define IPIPEIF_WDRSBK2                                             (0x88U)
#define IPIPEIF_WDRMA                                               (0x8cU)
#define IPIPEIF_WDRSAT_VP                                           (0x90U)
#define IPIPEIF_WDRSAT_VP2                                          (0x94U)
#define IPIPEIF_WDRSAT_ISIF                                         (0x98U)
#define IPIPEIF_WDRSAT_ISIF2                                        (0x9cU)
#define IPIPEIF_WDRSAT_SD                                           (0xa0U)
#define IPIPEIF_WDRSAT_SD2                                          (0xa4U)
#define IPIPEIF_WDRLWB1                                             (0xa8U)
#define IPIPEIF_WDRLWB2                                             (0xacU)
#define IPIPEIF_WDRSWB1                                             (0xb0U)
#define IPIPEIF_WDRSWB2                                             (0xb4U)
#define IPIPEIF_VPDCMPXTHR1                                         (0xb8U)
#define IPIPEIF_VPDCMPXTHR2                                         (0xbcU)
#define IPIPEIF_VPDCMPXTHR3                                         (0xc0U)
#define IPIPEIF_VPDCMPYTHR1                                         (0xc4U)
#define IPIPEIF_VPDCMPYTHR2                                         (0xc8U)
#define IPIPEIF_VPDCMPYTHR3                                         (0xccU)
#define IPIPEIF_VPDCMPSLOPE1                                        (0xd0U)
#define IPIPEIF_VPDCMPSLOPE2                                        (0xd4U)
#define IPIPEIF_VPDCMPSLOPE3                                        (0xd8U)
#define IPIPEIF_VPDCMPSLOPE4                                        (0xdcU)
#define IPIPEIF_VPDCMPCFG                                           (0xe0U)
#define IPIPEIF_SDDCMPXTHR1                                         (0xe4U)
#define IPIPEIF_SDDCMPXTHR2                                         (0xe8U)
#define IPIPEIF_SDDCMPXTHR3                                         (0xecU)
#define IPIPEIF_SDDCMPYTHR1                                         (0xf0U)
#define IPIPEIF_SDDCMPYTHR2                                         (0xf4U)
#define IPIPEIF_SDDCMPYTHR3                                         (0xf8U)
#define IPIPEIF_SDDCMPSLOPE1                                        (0xfcU)
#define IPIPEIF_SDDCMPSLOPE2                                        (0x100U)
#define IPIPEIF_SDDCMPSLOPE3                                        (0x104U)
#define IPIPEIF_SDDCMPSLOPE4                                        (0x108U)
#define IPIPEIF_SDDCMPCFG                                           (0x10cU)
#define IPIPEIF_WDRCMPXTHR1                                         (0x110U)
#define IPIPEIF_WDRCMPXTHR2                                         (0x114U)
#define IPIPEIF_WDRCMPXTHR3                                         (0x118U)
#define IPIPEIF_WDRCMPYTHR1                                         (0x11cU)
#define IPIPEIF_WDRCMPYTHR2                                         (0x120U)
#define IPIPEIF_WDRCMPYTHR3                                         (0x124U)
#define IPIPEIF_WDRCMPSLOPE1                                        (0x128U)
#define IPIPEIF_WDRCMPSLOPE2                                        (0x12cU)
#define IPIPEIF_WDRCMPSLOPE3                                        (0x130U)
#define IPIPEIF_WDRCMPSLOPE4                                        (0x134U)
#define IPIPEIF_WDRCMPCFG                                           (0x138U)
#define IPIPEIF_WDRMRGCFG                                           (0x13cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define IPIPEIF_ENABLE_SHIFT                                                            (0U)
#define IPIPEIF_ENABLE_MASK                                                             (0x00000001U)
#define IPIPEIF_ENABLE_DISABLE                                                           (0U)
#define IPIPEIF_ENABLE_ENABLE                                                            (1U)

#define IPIPEIF_ENABLE_SYNCOFF_SHIFT                                                    (1U)
#define IPIPEIF_ENABLE_SYNCOFF_MASK                                                     (0x00000002U)
#define IPIPEIF_ENABLE_SYNCOFF_DISABLE                                                   (0U)
#define IPIPEIF_ENABLE_SYNCOFF                                                           (1U)

#define IPIPEIF_ENABLE_RESERVED_SHIFT                                                   (2U)
#define IPIPEIF_ENABLE_RESERVED_MASK                                                    (0xfffffffcU)

#define IPIPEIF_CFG1_ONESHOT_SHIFT                                                      (0U)
#define IPIPEIF_CFG1_ONESHOT_MASK                                                       (0x00000001U)
#define IPIPEIF_CFG1_ONESHOT_CONTINUOUS                                                  (0U)
#define IPIPEIF_CFG1_ONESHOT                                                             (1U)

#define IPIPEIF_CFG1_DECIM_SHIFT                                                        (1U)
#define IPIPEIF_CFG1_DECIM_MASK                                                         (0x00000002U)
#define IPIPEIF_CFG1_DECIM_NODECIMATION                                                  (0U)
#define IPIPEIF_CFG1_DECIM_DECIMATE                                                      (1U)

#define IPIPEIF_CFG1_INPSRC2_SHIFT                                                      (2U)
#define IPIPEIF_CFG1_INPSRC2_MASK                                                       (0x0000000cU)
#define IPIPEIF_CFG1_INPSRC2_ISIF                                                        (0U)
#define IPIPEIF_CFG1_INPSRC2_SDRAM_RAW                                                   (1U)
#define IPIPEIF_CFG1_INPSRC2_ISIF_DARKFM                                                 (2U)
#define IPIPEIF_CFG1_INPSRC2_SDRAM_YUV                                                   (3U)

#define IPIPEIF_CFG1_AVGFILT_SHIFT                                                      (7U)
#define IPIPEIF_CFG1_AVGFILT_MASK                                                       (0x00000080U)
#define IPIPEIF_CFG1_AVGFILT_OFF                                                         (0U)
#define IPIPEIF_CFG1_AVGFILT_ON                                                          (1U)

#define IPIPEIF_CFG1_CLKSEL_SHIFT                                                       (10U)
#define IPIPEIF_CFG1_CLKSEL_MASK                                                        (0x00000400U)
#define IPIPEIF_CFG1_CLKSEL_PCLK                                                         (0U)
#define IPIPEIF_CFG1_CLKSEL_SDRAM_DIV_CLK                                                (1U)

#define IPIPEIF_CFG1_DATASFT_SHIFT                                                      (11U)
#define IPIPEIF_CFG1_DATASFT_MASK                                                       (0x00003800U)
#define IPIPEIF_CFG1_DATASFT_0                                                           (0U)
#define IPIPEIF_CFG1_DATASFT_1                                                           (1U)
#define IPIPEIF_CFG1_DATASFT_2                                                           (2U)
#define IPIPEIF_CFG1_DATASFT_3                                                           (3U)
#define IPIPEIF_CFG1_DATASFT_4                                                           (4U)
#define IPIPEIF_CFG1_DATASFT_5                                                           (5U)
#define IPIPEIF_CFG1_DATASFT_6                                                           (6U)
#define IPIPEIF_CFG1_DATASFT_7                                                           (7U)

#define IPIPEIF_CFG1_INPSRC1_SHIFT                                                      (14U)
#define IPIPEIF_CFG1_INPSRC1_MASK                                                       (0x0000c000U)
#define IPIPEIF_CFG1_INPSRC1_RAW                                                         (0U)
#define IPIPEIF_CFG1_INPSRC1_SDRAM_RAW                                                   (1U)
#define IPIPEIF_CFG1_INPSRC1_ISIF_DARKFM                                                 (2U)
#define IPIPEIF_CFG1_INPSRC1_SDRAM_YUV                                                   (3U)

#define IPIPEIF_CFG1_UNPACK_SHIFT                                                       (8U)
#define IPIPEIF_CFG1_UNPACK_MASK                                                        (0x00000300U)
#define IPIPEIF_CFG1_UNPACK_NORMAL_16_BITS_PIXEL                                         (0U)
#define IPIPEIF_CFG1_UNPACK_PACK_8_BITS_PIXEL                                            (1U)
#define IPIPEIF_CFG1_UNPACK_PACK_8_BITS_PIXEL_ALAW                                       (2U)
#define IPIPEIF_CFG1_UNPACK_PACK_12_BITS_PIXEL                                           (3U)

#define IPIPEIF_CFG1_RESERVED1_SHIFT                                                    (16U)
#define IPIPEIF_CFG1_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPEIF_CFG1_RAW16_SDRAM_SHIFT                                                  (4U)
#define IPIPEIF_CFG1_RAW16_SDRAM_MASK                                                   (0x00000010U)

#define IPIPEIF_CFG1_RESERVED_SHIFT                                                     (5U)
#define IPIPEIF_CFG1_RESERVED_MASK                                                      (0x00000060U)

#define IPIPEIF_PPLN_SHIFT                                                              (0U)
#define IPIPEIF_PPLN_MASK                                                               (0x00001fffU)

#define IPIPEIF_PPLN_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_PPLN_RESERVED_MASK                                                      (0x0000e000U)

#define IPIPEIF_PPLN_RESERVED1_SHIFT                                                    (16U)
#define IPIPEIF_PPLN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPEIF_LPFR_SHIFT                                                              (0U)
#define IPIPEIF_LPFR_MASK                                                               (0x00001fffU)

#define IPIPEIF_LPFR_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_LPFR_RESERVED_MASK                                                      (0x0000e000U)

#define IPIPEIF_LPFR_RESERVED1_SHIFT                                                    (16U)
#define IPIPEIF_LPFR_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPEIF_HNUM_SHIFT                                                              (0U)
#define IPIPEIF_HNUM_MASK                                                               (0x00001fffU)

#define IPIPEIF_HNUM_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_HNUM_RESERVED_MASK                                                      (0x0000e000U)

#define IPIPEIF_HNUM_RESERVED1_SHIFT                                                    (16U)
#define IPIPEIF_HNUM_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPEIF_VNUM_SHIFT                                                              (0U)
#define IPIPEIF_VNUM_MASK                                                               (0x00001fffU)

#define IPIPEIF_VNUM_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_VNUM_RESERVED_MASK                                                      (0xffffe000U)

#define IPIPEIF_ADDRU_RESERVED_SHIFT                                                    (11U)
#define IPIPEIF_ADDRU_RESERVED_MASK                                                     (0xfffff800U)

#define IPIPEIF_ADDRU_SHIFT                                                             (0U)
#define IPIPEIF_ADDRU_MASK                                                              (0x000007ffU)

#define IPIPEIF_ADDRL_SHIFT                                                             (0U)
#define IPIPEIF_ADDRL_MASK                                                              (0x0000ffffU)

#define IPIPEIF_ADDRL_RESERVED_SHIFT                                                    (16U)
#define IPIPEIF_ADDRL_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPEIF_ADOFS_SHIFT                                                             (0U)
#define IPIPEIF_ADOFS_MASK                                                              (0x00000fffU)

#define IPIPEIF_ADOFS_RESERVED_SHIFT                                                    (12U)
#define IPIPEIF_ADOFS_RESERVED_MASK                                                     (0xfffff000U)

#define IPIPEIF_RSZ_SHIFT                                                               (0U)
#define IPIPEIF_RSZ_MASK                                                                (0x0000007fU)

#define IPIPEIF_RSZ_RESERVED_SHIFT                                                      (7U)
#define IPIPEIF_RSZ_RESERVED_MASK                                                       (0xffffff80U)

#define IPIPEIF_GAIN_SHIFT                                                              (0U)
#define IPIPEIF_GAIN_MASK                                                               (0x000003ffU)

#define IPIPEIF_GAIN_RESERVED_SHIFT                                                     (10U)
#define IPIPEIF_GAIN_RESERVED_MASK                                                      (0xfffffc00U)

#define IPIPEIF_DPCM_ENA_SHIFT                                                          (0U)
#define IPIPEIF_DPCM_ENA_MASK                                                           (0x00000001U)
#define IPIPEIF_DPCM_ENA_OFF                                                             (0U)
#define IPIPEIF_DPCM_ENA_ON                                                              (1U)

#define IPIPEIF_DPCM_PRED_SHIFT                                                         (1U)
#define IPIPEIF_DPCM_PRED_MASK                                                          (0x00000002U)
#define IPIPEIF_DPCM_PRED_SIMPLE                                                         (0U)
#define IPIPEIF_DPCM_PRED_ADVANCED                                                       (1U)

#define IPIPEIF_DPCM_BITS_SHIFT                                                         (2U)
#define IPIPEIF_DPCM_BITS_MASK                                                          (0x00000004U)
#define IPIPEIF_DPCM_BITS_8TO10                                                          (0U)
#define IPIPEIF_DPCM_BITS_8TO12                                                          (1U)

#define IPIPEIF_DPCM_RESERVED_SHIFT                                                     (3U)
#define IPIPEIF_DPCM_RESERVED_MASK                                                      (0xfffffff8U)

#define IPIPEIF_CFG2_INTSW_SHIFT                                                        (0U)
#define IPIPEIF_CFG2_INTSW_MASK                                                         (0x00000001U)
#define IPIPEIF_CFG2_INTSW_VPORT                                                         (0U)
#define IPIPEIF_CFG2_INTSW_ISIF                                                          (1U)

#define IPIPEIF_CFG2_HDPOL_SHIFT                                                        (1U)
#define IPIPEIF_CFG2_HDPOL_MASK                                                         (0x00000002U)
#define IPIPEIF_CFG2_HDPOL_POSITIVE                                                      (0U)
#define IPIPEIF_CFG2_HDPOL_NEGATIVE                                                      (1U)

#define IPIPEIF_CFG2_VDPOL_SHIFT                                                        (2U)
#define IPIPEIF_CFG2_VDPOL_MASK                                                         (0x00000004U)
#define IPIPEIF_CFG2_VDPOL_POSITIVE                                                      (0U)
#define IPIPEIF_CFG2_VDPOL_NEGATIVE                                                      (1U)

#define IPIPEIF_CFG2_YUV16_SHIFT                                                        (3U)
#define IPIPEIF_CFG2_YUV16_MASK                                                         (0x00000008U)
#define IPIPEIF_CFG2_YUV16_RAW                                                           (0U)
#define IPIPEIF_CFG2_YUV16_YUV                                                           (1U)

#define IPIPEIF_CFG2_WENE_SHIFT                                                         (4U)
#define IPIPEIF_CFG2_WENE_MASK                                                          (0x00000010U)
#define IPIPEIF_CFG2_WENE_NO_EXTERNAL_WEN                                                (0U)
#define IPIPEIF_CFG2_WENE_EXTERNAL_WEN                                                   (1U)

#define IPIPEIF_CFG2_DFSDIR_SHIFT                                                       (5U)
#define IPIPEIF_CFG2_DFSDIR_MASK                                                        (0x00000020U)
#define IPIPEIF_CFG2_DFSDIR_VPORT                                                        (0U)
#define IPIPEIF_CFG2_DFSDIR_SDRAM                                                        (1U)

#define IPIPEIF_CFG2_YUV8_SHIFT                                                         (6U)
#define IPIPEIF_CFG2_YUV8_MASK                                                          (0x00000040U)
#define IPIPEIF_CFG2_YUV8_YUV16                                                          (0U)
#define IPIPEIF_CFG2_YUV8                                                                (1U)

#define IPIPEIF_CFG2_YUV8P_SHIFT                                                        (7U)
#define IPIPEIF_CFG2_YUV8P_MASK                                                         (0x00000080U)
#define IPIPEIF_CFG2_YUV8P_Y                                                             (0U)
#define IPIPEIF_CFG2_YUV8P_C                                                             (1U)

#define IPIPEIF_CFG2_RESERVED_SHIFT                                                     (8U)
#define IPIPEIF_CFG2_RESERVED_MASK                                                      (0xffffff00U)

#define IPIPEIF_INIRSZ_SHIFT                                                            (0U)
#define IPIPEIF_INIRSZ_MASK                                                             (0x00001fffU)

#define IPIPEIF_INIRSZ_RESERVED_SHIFT                                                   (14U)
#define IPIPEIF_INIRSZ_RESERVED_MASK                                                    (0xffffc000U)

#define IPIPEIF_INIRSZ_ALNSYNC_SHIFT                                                    (13U)
#define IPIPEIF_INIRSZ_ALNSYNC_MASK                                                     (0x00002000U)
#define IPIPEIF_INIRSZ_ALNSYNC_DISABLE                                                   (0U)
#define IPIPEIF_INIRSZ_ALNSYNC_ENABLE                                                    (1U)

#define IPIPEIF_OCLIP_SHIFT                                                             (0U)
#define IPIPEIF_OCLIP_MASK                                                              (0x0000ffffU)

#define IPIPEIF_OCLIP_RESERVED_SHIFT                                                    (16U)
#define IPIPEIF_OCLIP_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPEIF_DTUDF_SHIFT                                                             (0U)
#define IPIPEIF_DTUDF_MASK                                                              (0x00000001U)

#define IPIPEIF_DTUDF_RESERVED1_SHIFT                                                   (16U)
#define IPIPEIF_DTUDF_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPEIF_DTUDF_ENM2MSTALL_SHIFT                                                  (1U)
#define IPIPEIF_DTUDF_ENM2MSTALL_MASK                                                   (0x00000002U)
#define IPIPEIF_DTUDF_ENM2MSTALL_DISABLE                                                 (0U)
#define IPIPEIF_DTUDF_ENM2MSTALL_ENABLE                                                  (1U)

#define IPIPEIF_DTUDF_FIFOWMRKLVL_SHIFT                                                 (2U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_MASK                                                  (0x0000003cU)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_0                                                      (0U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_1                                                      (1U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_2                                                      (2U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_3                                                      (3U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_4                                                      (4U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_5                                                      (5U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_6                                                      (6U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_7                                                      (7U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_8                                                      (8U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_9                                                      (9U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_10                                                     (10U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_11                                                     (11U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_12                                                     (12U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_13                                                     (13U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_14                                                     (14U)
#define IPIPEIF_DTUDF_FIFOWMRKLVL_15                                                     (15U)

#define IPIPEIF_DTUDF_RESERVED_SHIFT                                                    (6U)
#define IPIPEIF_DTUDF_RESERVED_MASK                                                     (0x0000ffc0U)

#define IPIPEIF_CLKDIV_SHIFT                                                            (0U)
#define IPIPEIF_CLKDIV_MASK                                                             (0x0000ffffU)

#define IPIPEIF_CLKDIV_RESERVED_SHIFT                                                   (16U)
#define IPIPEIF_CLKDIV_RESERVED_MASK                                                    (0xffff0000U)

#define IPIPEIF_DPC1_TH_SHIFT                                                           (0U)
#define IPIPEIF_DPC1_TH_MASK                                                            (0x00000fffU)

#define IPIPEIF_DPC1_ENA_SHIFT                                                          (12U)
#define IPIPEIF_DPC1_ENA_MASK                                                           (0x00001000U)
#define IPIPEIF_DPC1_ENA_DISABLE                                                         (0U)
#define IPIPEIF_DPC1_ENA_ENABLE                                                          (1U)

#define IPIPEIF_DPC1_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_DPC1_RESERVED_MASK                                                      (0x0000e000U)

#define IPIPEIF_DPC1_RESERVED1_SHIFT                                                    (16U)
#define IPIPEIF_DPC1_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPEIF_DPC2_TH_SHIFT                                                           (0U)
#define IPIPEIF_DPC2_TH_MASK                                                            (0x00000fffU)

#define IPIPEIF_DPC2_ENA_SHIFT                                                          (12U)
#define IPIPEIF_DPC2_ENA_MASK                                                           (0x00001000U)
#define IPIPEIF_DPC2_ENA_DISABLE                                                         (0U)
#define IPIPEIF_DPC2_ENA_ENABLE                                                          (1U)

#define IPIPEIF_DPC2_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_DPC2_RESERVED_MASK                                                      (0xffffe000U)

#define IPIPEIF_DFSGVL_SHIFT                                                            (0U)
#define IPIPEIF_DFSGVL_MASK                                                             (0x000003ffU)

#define IPIPEIF_DFSGVL_DFSGEN_SHIFT                                                     (10U)
#define IPIPEIF_DFSGVL_DFSGEN_MASK                                                      (0x00000400U)

#define IPIPEIF_DFSGVL_RESERVED_SHIFT                                                   (11U)
#define IPIPEIF_DFSGVL_RESERVED_MASK                                                    (0xfffff800U)

#define IPIPEIF_DFSGTH_SHIFT                                                            (0U)
#define IPIPEIF_DFSGTH_MASK                                                             (0x00000fffU)

#define IPIPEIF_DFSGTH_RESERVED_SHIFT                                                   (12U)
#define IPIPEIF_DFSGTH_RESERVED_MASK                                                    (0xfffff000U)

#define IPIPEIF_RSZ3A_RSZ_SHIFT                                                         (0U)
#define IPIPEIF_RSZ3A_RSZ_MASK                                                          (0x0000007fU)

#define IPIPEIF_RSZ3A_AVGFILT_SHIFT                                                     (8U)
#define IPIPEIF_RSZ3A_AVGFILT_MASK                                                      (0x00000100U)
#define IPIPEIF_RSZ3A_AVGFILT_DISABLE                                                    (0U)
#define IPIPEIF_RSZ3A_AVGFILT_ENABLE                                                     (1U)

#define IPIPEIF_RSZ3A_DECIM_SHIFT                                                       (9U)
#define IPIPEIF_RSZ3A_DECIM_MASK                                                        (0x00000200U)
#define IPIPEIF_RSZ3A_DECIM_DISABLE                                                      (0U)
#define IPIPEIF_RSZ3A_DECIM_ENABLE                                                       (1U)

#define IPIPEIF_RSZ3A_RESERVED_SHIFT                                                    (7U)
#define IPIPEIF_RSZ3A_RESERVED_MASK                                                     (0x00000080U)

#define IPIPEIF_RSZ3A_RESERVED1_SHIFT                                                   (10U)
#define IPIPEIF_RSZ3A_RESERVED1_MASK                                                    (0x0000fc00U)

#define IPIPEIF_RSZ3A_RESERVED2_SHIFT                                                   (16U)
#define IPIPEIF_RSZ3A_RESERVED2_MASK                                                    (0xffff0000U)

#define IPIPEIF_INIRSZ3A_INIRSZ_SHIFT                                                   (0U)
#define IPIPEIF_INIRSZ3A_INIRSZ_MASK                                                    (0x00001fffU)

#define IPIPEIF_INIRSZ3A_RESERVED_SHIFT                                                 (14U)
#define IPIPEIF_INIRSZ3A_RESERVED_MASK                                                  (0xffffc000U)

#define IPIPEIF_INIRSZ3A_ALNSYNC_SHIFT                                                  (13U)
#define IPIPEIF_INIRSZ3A_ALNSYNC_MASK                                                   (0x00002000U)
#define IPIPEIF_INIRSZ3A_ALNSYNC_DISABLE                                                 (0U)
#define IPIPEIF_INIRSZ3A_ALNSYNC_ENABLE                                                  (1U)

#define IPIPEIF_CFG3_CIR_EN_SHIFT                                                       (12U)
#define IPIPEIF_CFG3_CIR_EN_MASK                                                        (0x00001000U)
#define IPIPEIF_CFG3_CIR_EN_DISABLE                                                      (0U)
#define IPIPEIF_CFG3_CIR_EN_ENABLE                                                       (1U)

#define IPIPEIF_CFG3_CBN_SHIFT                                                          (0U)
#define IPIPEIF_CFG3_CBN_MASK                                                           (0x00000fffU)

#define IPIPEIF_CFG3_HSK_EN_SHIFT                                                       (28U)
#define IPIPEIF_CFG3_HSK_EN_MASK                                                        (0x10000000U)
#define IPIPEIF_CFG3_HSK_EN_DISABLE                                                      (0U)
#define IPIPEIF_CFG3_HSK_EN_ENABLE                                                       (1U)

#define IPIPEIF_CFG3_CYN_SHIFT                                                          (16U)
#define IPIPEIF_CFG3_CYN_MASK                                                           (0x0fff0000U)

#define IPIPEIF_CFG3_RESERVED_SHIFT                                                     (13U)
#define IPIPEIF_CFG3_RESERVED_MASK                                                      (0x0000e000U)

#define IPIPEIF_CFG3_HSK_EOF_SHIFT                                                      (29U)
#define IPIPEIF_CFG3_HSK_EOF_MASK                                                       (0x20000000U)
#define IPIPEIF_CFG3_HSK_EOF_ENABLE                                                      (1U)
#define IPIPEIF_CFG3_HSK_EOF_DISABLE                                                     (0U)

#define IPIPEIF_CFG3_RESERVED1_SHIFT                                                    (30U)
#define IPIPEIF_CFG3_RESERVED1_MASK                                                     (0xc0000000U)

#define IPIPEIF_CFG4_WDR_EN_SHIFT                                                       (0U)
#define IPIPEIF_CFG4_WDR_EN_MASK                                                        (0x00000001U)
#define IPIPEIF_CFG4_WDR_EN_DISABLE                                                      (0U)
#define IPIPEIF_CFG4_WDR_EN_ENABLE                                                       (1U)

#define IPIPEIF_CFG4_LBIT_SHIFT                                                         (4U)
#define IPIPEIF_CFG4_LBIT_MASK                                                          (0x000000f0U)

#define IPIPEIF_CFG4_SBIT_SHIFT                                                         (8U)
#define IPIPEIF_CFG4_SBIT_MASK                                                          (0x00000f00U)

#define IPIPEIF_CFG4_WGT_SEL_SHIFT                                                      (1U)
#define IPIPEIF_CFG4_WGT_SEL_MASK                                                       (0x00000002U)
#define IPIPEIF_CFG4_WGT_SEL_LONG                                                        (0U)
#define IPIPEIF_CFG4_WGT_SEL_SHORT                                                       (1U)

#define IPIPEIF_CFG4_RESERVED_SHIFT                                                     (2U)
#define IPIPEIF_CFG4_RESERVED_MASK                                                      (0x0000000cU)

#define IPIPEIF_CFG4_DST_SHIFT                                                          (16U)
#define IPIPEIF_CFG4_DST_MASK                                                           (0x001f0000U)

#define IPIPEIF_CFG4_RESERVED1_SHIFT                                                    (12U)
#define IPIPEIF_CFG4_RESERVED1_MASK                                                     (0x0000f000U)

#define IPIPEIF_CFG4_RESERVED2_SHIFT                                                    (21U)
#define IPIPEIF_CFG4_RESERVED2_MASK                                                     (0xffe00000U)

#define IPIPEIF_WDRAF_AFM_SHIFT                                                         (0U)
#define IPIPEIF_WDRAF_AFM_MASK                                                          (0x0000ffffU)

#define IPIPEIF_WDRAF_AFE_SHIFT                                                         (20U)
#define IPIPEIF_WDRAF_AFE_MASK                                                          (0x01f00000U)

#define IPIPEIF_WDRAF_RESERVED_SHIFT                                                    (16U)
#define IPIPEIF_WDRAF_RESERVED_MASK                                                     (0x000f0000U)

#define IPIPEIF_WDRAF_RESERVED1_SHIFT                                                   (25U)
#define IPIPEIF_WDRAF_RESERVED1_MASK                                                    (0xfe000000U)

#define IPIPEIF_WDRBF_BF_SHIFT                                                          (0U)
#define IPIPEIF_WDRBF_BF_MASK                                                           (0x0000ffffU)

#define IPIPEIF_WDRBF_RESERVED_SHIFT                                                    (16U)
#define IPIPEIF_WDRBF_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPEIF_WDRGAIN_GLONG_SHIFT                                                     (0U)
#define IPIPEIF_WDRGAIN_GLONG_MASK                                                      (0x0000ffffU)

#define IPIPEIF_WDRGAIN_GSHORT_SHIFT                                                    (16U)
#define IPIPEIF_WDRGAIN_GSHORT_MASK                                                     (0xffff0000U)

#define IPIPEIF_WDRTHR_THR_SHIFT                                                        (0U)
#define IPIPEIF_WDRTHR_THR_MASK                                                         (0x0000ffffU)

#define IPIPEIF_WDRTHR_RESERVED_SHIFT                                                   (16U)
#define IPIPEIF_WDRTHR_RESERVED_MASK                                                    (0xffff0000U)

#define IPIPEIF_RSVD1_RESERVED_SHIFT                                                    (0U)
#define IPIPEIF_RSVD1_RESERVED_MASK                                                     (0xffffffffU)

#define IPIPEIF_RSVD2_RESERVED1_SHIFT                                                   (0U)
#define IPIPEIF_RSVD2_RESERVED1_MASK                                                    (0xffffffffU)

#define IPIPEIF_WDRLBK1_LBK00_SHIFT                                                     (0U)
#define IPIPEIF_WDRLBK1_LBK00_MASK                                                      (0x00000fffU)

#define IPIPEIF_WDRLBK1_LBK01_SHIFT                                                     (16U)
#define IPIPEIF_WDRLBK1_LBK01_MASK                                                      (0x0fff0000U)

#define IPIPEIF_WDRLBK1_RESERVED_SHIFT                                                  (12U)
#define IPIPEIF_WDRLBK1_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPEIF_WDRLBK1_RESERVED1_SHIFT                                                 (28U)
#define IPIPEIF_WDRLBK1_RESERVED1_MASK                                                  (0xf0000000U)

#define IPIPEIF_WDRLBK2_LBK10_SHIFT                                                     (0U)
#define IPIPEIF_WDRLBK2_LBK10_MASK                                                      (0x00000fffU)

#define IPIPEIF_WDRLBK2_LBK11_SHIFT                                                     (16U)
#define IPIPEIF_WDRLBK2_LBK11_MASK                                                      (0x0fff0000U)

#define IPIPEIF_WDRLBK2_RESERVED_SHIFT                                                  (12U)
#define IPIPEIF_WDRLBK2_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPEIF_WDRLBK2_RESERVED1_SHIFT                                                 (28U)
#define IPIPEIF_WDRLBK2_RESERVED1_MASK                                                  (0xf0000000U)

#define IPIPEIF_WDRSBK1_SBK00_SHIFT                                                     (0U)
#define IPIPEIF_WDRSBK1_SBK00_MASK                                                      (0x00000fffU)

#define IPIPEIF_WDRSBK1_SBK01_SHIFT                                                     (16U)
#define IPIPEIF_WDRSBK1_SBK01_MASK                                                      (0x0fff0000U)

#define IPIPEIF_WDRSBK1_RESERVED_SHIFT                                                  (12U)
#define IPIPEIF_WDRSBK1_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPEIF_WDRSBK1_RESERVED1_SHIFT                                                 (28U)
#define IPIPEIF_WDRSBK1_RESERVED1_MASK                                                  (0xf0000000U)

#define IPIPEIF_WDRSBK2_SBK10_SHIFT                                                     (0U)
#define IPIPEIF_WDRSBK2_SBK10_MASK                                                      (0x00000fffU)

#define IPIPEIF_WDRSBK2_SBK11_SHIFT                                                     (16U)
#define IPIPEIF_WDRSBK2_SBK11_MASK                                                      (0x0fff0000U)

#define IPIPEIF_WDRSBK2_RESERVED_SHIFT                                                  (12U)
#define IPIPEIF_WDRSBK2_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPEIF_WDRSBK2_RESERVED1_SHIFT                                                 (28U)
#define IPIPEIF_WDRSBK2_RESERVED1_MASK                                                  (0xf0000000U)

#define IPIPEIF_WDRMA_MAD_SHIFT                                                         (0U)
#define IPIPEIF_WDRMA_MAD_MASK                                                          (0x0000ffffU)

#define IPIPEIF_WDRMA_MAS_SHIFT                                                         (16U)
#define IPIPEIF_WDRMA_MAS_MASK                                                          (0xffff0000U)

#define IPIPEIF_WDRSAT_VP_SAT_SHIFT                                                     (0U)
#define IPIPEIF_WDRSAT_VP_SAT_MASK                                                      (0x000fffffU)

#define IPIPEIF_WDRSAT_VP_RESERVED1_SHIFT                                               (20U)
#define IPIPEIF_WDRSAT_VP_RESERVED1_MASK                                                (0xfff00000U)

#define IPIPEIF_WDRSAT_VP2_RESERVED1_SHIFT                                              (16U)
#define IPIPEIF_WDRSAT_VP2_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPEIF_WDRSAT_VP2_VP_SATEN_SHIFT                                               (0U)
#define IPIPEIF_WDRSAT_VP2_VP_SATEN_MASK                                                (0x00000001U)
#define IPIPEIF_WDRSAT_VP2_VP_SATEN_DISABLE                                              (0U)
#define IPIPEIF_WDRSAT_VP2_VP_SATEN_ENABLE                                               (1U)

#define IPIPEIF_WDRSAT_VP2_VP_DSF_SHIFT                                                 (3U)
#define IPIPEIF_WDRSAT_VP2_VP_DSF_MASK                                                  (0x000000f8U)

#define IPIPEIF_WDRSAT_VP2_RESERVED_SHIFT                                               (1U)
#define IPIPEIF_WDRSAT_VP2_RESERVED_MASK                                                (0x00000006U)

#define IPIPEIF_WDRSAT_VP2_VP_DCCLMP_SHIFT                                              (8U)
#define IPIPEIF_WDRSAT_VP2_VP_DCCLMP_MASK                                               (0x0000ff00U)

#define IPIPEIF_WDRSAT_ISIF_SAT_SHIFT                                                   (0U)
#define IPIPEIF_WDRSAT_ISIF_SAT_MASK                                                    (0x000fffffU)

#define IPIPEIF_WDRSAT_ISIF_RESERVED1_SHIFT                                             (20U)
#define IPIPEIF_WDRSAT_ISIF_RESERVED1_MASK                                              (0xfff00000U)

#define IPIPEIF_WDRSAT_ISIF2_RESERVED1_SHIFT                                            (16U)
#define IPIPEIF_WDRSAT_ISIF2_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_SHIFT                                           (0U)
#define IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_MASK                                            (0x00000001U)
#define IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_DISABLE                                          (0U)
#define IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_ENABLE                                           (1U)

#define IPIPEIF_WDRSAT_ISIF2_ISIF_DSF_SHIFT                                             (3U)
#define IPIPEIF_WDRSAT_ISIF2_ISIF_DSF_MASK                                              (0x000000f8U)

#define IPIPEIF_WDRSAT_ISIF2_RESERVED_SHIFT                                             (1U)
#define IPIPEIF_WDRSAT_ISIF2_RESERVED_MASK                                              (0x00000006U)

#define IPIPEIF_WDRSAT_ISIF2_ISIF_DCCLMP_SHIFT                                          (8U)
#define IPIPEIF_WDRSAT_ISIF2_ISIF_DCCLMP_MASK                                           (0x0000ff00U)

#define IPIPEIF_WDRSAT_SD_SAT_SHIFT                                                     (0U)
#define IPIPEIF_WDRSAT_SD_SAT_MASK                                                      (0x000fffffU)

#define IPIPEIF_WDRSAT_SD_RESERVED1_SHIFT                                               (20U)
#define IPIPEIF_WDRSAT_SD_RESERVED1_MASK                                                (0xfff00000U)

#define IPIPEIF_WDRSAT_SD2_RESERVED1_SHIFT                                              (16U)
#define IPIPEIF_WDRSAT_SD2_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPEIF_WDRSAT_SD2_SD_SATEN_SHIFT                                               (0U)
#define IPIPEIF_WDRSAT_SD2_SD_SATEN_MASK                                                (0x00000001U)
#define IPIPEIF_WDRSAT_SD2_SD_SATEN_DISABLE                                              (0U)
#define IPIPEIF_WDRSAT_SD2_SD_SATEN_ENABLE                                               (1U)

#define IPIPEIF_WDRSAT_SD2_SD_DSF_SHIFT                                                 (3U)
#define IPIPEIF_WDRSAT_SD2_SD_DSF_MASK                                                  (0x000000f8U)

#define IPIPEIF_WDRSAT_SD2_SD_DCCLMP_SHIFT                                              (8U)
#define IPIPEIF_WDRSAT_SD2_SD_DCCLMP_MASK                                               (0x0000ff00U)

#define IPIPEIF_WDRSAT_SD2_RESERVED_SHIFT                                               (1U)
#define IPIPEIF_WDRSAT_SD2_RESERVED_MASK                                                (0x00000006U)

#define IPIPEIF_WDRLWB1_LWB00_SHIFT                                                     (0U)
#define IPIPEIF_WDRLWB1_LWB00_MASK                                                      (0x00001fffU)

#define IPIPEIF_WDRLWB1_LWB01_SHIFT                                                     (16U)
#define IPIPEIF_WDRLWB1_LWB01_MASK                                                      (0x1fff0000U)

#define IPIPEIF_WDRLWB1_RESERVED_SHIFT                                                  (13U)
#define IPIPEIF_WDRLWB1_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPEIF_WDRLWB1_RESERVED1_SHIFT                                                 (29U)
#define IPIPEIF_WDRLWB1_RESERVED1_MASK                                                  (0xe0000000U)

#define IPIPEIF_WDRLWB2_LWB10_SHIFT                                                     (0U)
#define IPIPEIF_WDRLWB2_LWB10_MASK                                                      (0x00001fffU)

#define IPIPEIF_WDRLWB2_LWB11_SHIFT                                                     (16U)
#define IPIPEIF_WDRLWB2_LWB11_MASK                                                      (0x1fff0000U)

#define IPIPEIF_WDRLWB2_RESERVED_SHIFT                                                  (13U)
#define IPIPEIF_WDRLWB2_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPEIF_WDRLWB2_RESERVED1_SHIFT                                                 (29U)
#define IPIPEIF_WDRLWB2_RESERVED1_MASK                                                  (0xe0000000U)

#define IPIPEIF_WDRSWB1_SWB00_SHIFT                                                     (0U)
#define IPIPEIF_WDRSWB1_SWB00_MASK                                                      (0x00001fffU)

#define IPIPEIF_WDRSWB1_SWB01_SHIFT                                                     (16U)
#define IPIPEIF_WDRSWB1_SWB01_MASK                                                      (0x1fff0000U)

#define IPIPEIF_WDRSWB1_RESERVED_SHIFT                                                  (13U)
#define IPIPEIF_WDRSWB1_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPEIF_WDRSWB1_RESERVED1_SHIFT                                                 (29U)
#define IPIPEIF_WDRSWB1_RESERVED1_MASK                                                  (0xe0000000U)

#define IPIPEIF_WDRSWB2_SWB10_SHIFT                                                     (0U)
#define IPIPEIF_WDRSWB2_SWB10_MASK                                                      (0x00001fffU)

#define IPIPEIF_WDRSWB2_SWB11_SHIFT                                                     (16U)
#define IPIPEIF_WDRSWB2_SWB11_MASK                                                      (0x1fff0000U)

#define IPIPEIF_WDRSWB2_RESERVED_SHIFT                                                  (13U)
#define IPIPEIF_WDRSWB2_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPEIF_WDRSWB2_RESERVED1_SHIFT                                                 (29U)
#define IPIPEIF_WDRSWB2_RESERVED1_MASK                                                  (0xe0000000U)

#define IPIPEIF_VPDCMPXTHR1_XTHR1_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPXTHR1_XTHR1_MASK                                                  (0x0000ffffU)

#define IPIPEIF_VPDCMPXTHR1_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_VPDCMPXTHR1_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_VPDCMPXTHR2_XTHR2_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPXTHR2_XTHR2_MASK                                                  (0x0000ffffU)

#define IPIPEIF_VPDCMPXTHR2_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_VPDCMPXTHR2_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_VPDCMPXTHR3_XTHR3_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPXTHR3_XTHR3_MASK                                                  (0x0000ffffU)

#define IPIPEIF_VPDCMPXTHR3_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_VPDCMPXTHR3_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_VPDCMPYTHR1_YTHR1_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPYTHR1_YTHR1_MASK                                                  (0x000fffffU)

#define IPIPEIF_VPDCMPYTHR1_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_VPDCMPYTHR1_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_VPDCMPYTHR2_YTHR2_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPYTHR2_YTHR2_MASK                                                  (0x000fffffU)

#define IPIPEIF_VPDCMPYTHR2_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_VPDCMPYTHR2_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_VPDCMPYTHR3_YTHR3_SHIFT                                                 (0U)
#define IPIPEIF_VPDCMPYTHR3_YTHR3_MASK                                                  (0x000fffffU)

#define IPIPEIF_VPDCMPYTHR3_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_VPDCMPYTHR3_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_VPDCMPSLOPE1_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_VPDCMPSLOPE1_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_VPDCMPSLOPE1_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_VPDCMPSLOPE1_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_VPDCMPSLOPE2_SLOPE2_SHIFT                                               (0U)
#define IPIPEIF_VPDCMPSLOPE2_SLOPE2_MASK                                                (0x0000ffffU)

#define IPIPEIF_VPDCMPSLOPE2_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_VPDCMPSLOPE2_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_VPDCMPSLOPE3_SLOPE3_SHIFT                                               (0U)
#define IPIPEIF_VPDCMPSLOPE3_SLOPE3_MASK                                                (0x0000ffffU)

#define IPIPEIF_VPDCMPSLOPE3_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_VPDCMPSLOPE3_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_VPDCMPSLOPE4_SLOPE4_SHIFT                                               (0U)
#define IPIPEIF_VPDCMPSLOPE4_SLOPE4_MASK                                                (0x0000ffffU)

#define IPIPEIF_VPDCMPSLOPE4_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_VPDCMPSLOPE4_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_VPDCMPCFG_SHIFT_SHIFT                                                   (24U)
#define IPIPEIF_VPDCMPCFG_SHIFT_MASK                                                    (0x1f000000U)

#define IPIPEIF_VPDCMPCFG_RESERVED1_SHIFT                                               (29U)
#define IPIPEIF_VPDCMPCFG_RESERVED1_MASK                                                (0xe0000000U)

#define IPIPEIF_VPDCMPCFG_LUTBITSEL_SHIFT                                               (16U)
#define IPIPEIF_VPDCMPCFG_LUTBITSEL_MASK                                                (0x000f0000U)

#define IPIPEIF_VPDCMPCFG_RESERVED2_SHIFT                                               (20U)
#define IPIPEIF_VPDCMPCFG_RESERVED2_MASK                                                (0x00f00000U)

#define IPIPEIF_VPDCMPCFG_ENABLE_SHIFT                                                  (0U)
#define IPIPEIF_VPDCMPCFG_ENABLE_MASK                                                   (0x00000001U)

#define IPIPEIF_VPDCMPCFG_LUTSET_SHIFT                                                  (1U)
#define IPIPEIF_VPDCMPCFG_LUTSET_MASK                                                   (0x00000002U)

#define IPIPEIF_VPDCMPCFG_RESERVED0_SHIFT                                               (2U)
#define IPIPEIF_VPDCMPCFG_RESERVED0_MASK                                                (0x0000fffcU)

#define IPIPEIF_SDDCMPXTHR1_XTHR1_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPXTHR1_XTHR1_MASK                                                  (0x0000ffffU)

#define IPIPEIF_SDDCMPXTHR1_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_SDDCMPXTHR1_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_SDDCMPXTHR2_XTHR2_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPXTHR2_XTHR2_MASK                                                  (0x0000ffffU)

#define IPIPEIF_SDDCMPXTHR2_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_SDDCMPXTHR2_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_SDDCMPXTHR3_XTHR3_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPXTHR3_XTHR3_MASK                                                  (0x0000ffffU)

#define IPIPEIF_SDDCMPXTHR3_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_SDDCMPXTHR3_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_SDDCMPYTHR1_YTHR1_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPYTHR1_YTHR1_MASK                                                  (0x000fffffU)

#define IPIPEIF_SDDCMPYTHR1_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_SDDCMPYTHR1_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_SDDCMPYTHR2_YTHR2_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPYTHR2_YTHR2_MASK                                                  (0x000fffffU)

#define IPIPEIF_SDDCMPYTHR2_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_SDDCMPYTHR2_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_SDDCMPYTHR3_YTHR3_SHIFT                                                 (0U)
#define IPIPEIF_SDDCMPYTHR3_YTHR3_MASK                                                  (0x000fffffU)

#define IPIPEIF_SDDCMPYTHR3_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_SDDCMPYTHR3_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_SDDCMPSLOPE1_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_SDDCMPSLOPE1_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_SDDCMPSLOPE1_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_SDDCMPSLOPE1_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_SDDCMPSLOPE2_SLOPE2_SHIFT                                               (0U)
#define IPIPEIF_SDDCMPSLOPE2_SLOPE2_MASK                                                (0x0000ffffU)

#define IPIPEIF_SDDCMPSLOPE2_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_SDDCMPSLOPE2_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_SDDCMPSLOPE3_SLOPE3_SHIFT                                               (0U)
#define IPIPEIF_SDDCMPSLOPE3_SLOPE3_MASK                                                (0x0000ffffU)

#define IPIPEIF_SDDCMPSLOPE3_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_SDDCMPSLOPE3_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_SDDCMPSLOPE4_SLOPE4_SHIFT                                               (0U)
#define IPIPEIF_SDDCMPSLOPE4_SLOPE4_MASK                                                (0x0000ffffU)

#define IPIPEIF_SDDCMPSLOPE4_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_SDDCMPSLOPE4_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_SDDCMPCFG_SHIFT_SHIFT                                                   (24U)
#define IPIPEIF_SDDCMPCFG_SHIFT_MASK                                                    (0x1f000000U)

#define IPIPEIF_SDDCMPCFG_RESERVED1_SHIFT                                               (29U)
#define IPIPEIF_SDDCMPCFG_RESERVED1_MASK                                                (0xe0000000U)

#define IPIPEIF_SDDCMPCFG_LUTBITSEL_SHIFT                                               (16U)
#define IPIPEIF_SDDCMPCFG_LUTBITSEL_MASK                                                (0x000f0000U)

#define IPIPEIF_SDDCMPCFG_RESERVED2_SHIFT                                               (20U)
#define IPIPEIF_SDDCMPCFG_RESERVED2_MASK                                                (0x00f00000U)

#define IPIPEIF_SDDCMPCFG_ENABLE_SHIFT                                                  (0U)
#define IPIPEIF_SDDCMPCFG_ENABLE_MASK                                                   (0x00000001U)

#define IPIPEIF_SDDCMPCFG_LUTSET_SHIFT                                                  (1U)
#define IPIPEIF_SDDCMPCFG_LUTSET_MASK                                                   (0x00000002U)

#define IPIPEIF_SDDCMPCFG_RESERVED0_SHIFT                                               (2U)
#define IPIPEIF_SDDCMPCFG_RESERVED0_MASK                                                (0x0000fffcU)

#define IPIPEIF_WDRCMPXTHR1_XTHR1_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPXTHR1_XTHR1_MASK                                                  (0x000fffffU)

#define IPIPEIF_WDRCMPXTHR1_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_WDRCMPXTHR1_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_WDRCMPXTHR2_XTHR2_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPXTHR2_XTHR2_MASK                                                  (0x000fffffU)

#define IPIPEIF_WDRCMPXTHR2_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_WDRCMPXTHR2_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_WDRCMPXTHR3_XTHR3_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPXTHR3_XTHR3_MASK                                                  (0x000fffffU)

#define IPIPEIF_WDRCMPXTHR3_RESERVED_SHIFT                                              (20U)
#define IPIPEIF_WDRCMPXTHR3_RESERVED_MASK                                               (0xfff00000U)

#define IPIPEIF_WDRCMPYTHR1_YTHR1_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPYTHR1_YTHR1_MASK                                                  (0x0000ffffU)

#define IPIPEIF_WDRCMPYTHR1_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_WDRCMPYTHR1_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_WDRCMPYTHR2_YTHR2_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPYTHR2_YTHR2_MASK                                                  (0x0000ffffU)

#define IPIPEIF_WDRCMPYTHR2_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_WDRCMPYTHR2_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_WDRCMPYTHR3_YTHR3_SHIFT                                                 (0U)
#define IPIPEIF_WDRCMPYTHR3_YTHR3_MASK                                                  (0x0000ffffU)

#define IPIPEIF_WDRCMPYTHR3_RESERVED_SHIFT                                              (16U)
#define IPIPEIF_WDRCMPYTHR3_RESERVED_MASK                                               (0xffff0000U)

#define IPIPEIF_WDRCMPSLOPE1_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_WDRCMPSLOPE1_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_WDRCMPSLOPE1_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_WDRCMPSLOPE1_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_WDRCMPSLOPE2_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_WDRCMPSLOPE2_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_WDRCMPSLOPE2_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_WDRCMPSLOPE2_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_WDRCMPSLOPE3_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_WDRCMPSLOPE3_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_WDRCMPSLOPE3_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_WDRCMPSLOPE3_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_WDRCMPSLOPE4_SLOPE1_SHIFT                                               (0U)
#define IPIPEIF_WDRCMPSLOPE4_SLOPE1_MASK                                                (0x0000ffffU)

#define IPIPEIF_WDRCMPSLOPE4_RESERVED_SHIFT                                             (16U)
#define IPIPEIF_WDRCMPSLOPE4_RESERVED_MASK                                              (0xffff0000U)

#define IPIPEIF_WDRCMPCFG_SHIFT_SHIFT                                                   (24U)
#define IPIPEIF_WDRCMPCFG_SHIFT_MASK                                                    (0x1f000000U)

#define IPIPEIF_WDRCMPCFG_RESERVED1_SHIFT                                               (29U)
#define IPIPEIF_WDRCMPCFG_RESERVED1_MASK                                                (0xe0000000U)

#define IPIPEIF_WDRCMPCFG_LUTBITSEL_SHIFT                                               (16U)
#define IPIPEIF_WDRCMPCFG_LUTBITSEL_MASK                                                (0x000f0000U)

#define IPIPEIF_WDRCMPCFG_RESERVED2_SHIFT                                               (20U)
#define IPIPEIF_WDRCMPCFG_RESERVED2_MASK                                                (0x00f00000U)

#define IPIPEIF_WDRCMPCFG_ENABLE_SHIFT                                                  (0U)
#define IPIPEIF_WDRCMPCFG_ENABLE_MASK                                                   (0x00000001U)

#define IPIPEIF_WDRCMPCFG_LUTSET_SHIFT                                                  (1U)
#define IPIPEIF_WDRCMPCFG_LUTSET_MASK                                                   (0x00000002U)

#define IPIPEIF_WDRCMPCFG_RESERVED0_SHIFT                                               (2U)
#define IPIPEIF_WDRCMPCFG_RESERVED0_MASK                                                (0x0000fffcU)

#define IPIPEIF_WDRMRGCFG_MRGWTSFT_SHIFT                                                (24U)
#define IPIPEIF_WDRMRGCFG_MRGWTSFT_MASK                                                 (0x07000000U)

#define IPIPEIF_WDRMRGCFG_RESERVED1_SHIFT                                               (27U)
#define IPIPEIF_WDRMRGCFG_RESERVED1_MASK                                                (0xf8000000U)

#define IPIPEIF_WDRMRGCFG_RESERVED2_SHIFT                                               (20U)
#define IPIPEIF_WDRMRGCFG_RESERVED2_MASK                                                (0x00f00000U)

#define IPIPEIF_WDRMRGCFG_WDRCLIP_SHIFT                                                 (0U)
#define IPIPEIF_WDRMRGCFG_WDRCLIP_MASK                                                  (0x000fffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_IPIPEIF_H_ */

