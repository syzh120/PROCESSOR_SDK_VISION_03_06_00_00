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

#ifndef HW_ISS_ISIF_H_
#define HW_ISS_ISIF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ISIF_SYNCEN                                                 (0x0U)
#define ISIF_MODESET                                                (0x4U)
#define ISIF_HDW                                                    (0x8U)
#define ISIF_VDW                                                    (0xcU)
#define ISIF_PPLN                                                   (0x10U)
#define ISIF_LPFR                                                   (0x14U)
#define ISIF_SPH                                                    (0x18U)
#define ISIF_LNH                                                    (0x1cU)
#define ISIF_SLV0                                                   (0x20U)
#define ISIF_SLV1                                                   (0x24U)
#define ISIF_LNV                                                    (0x28U)
#define ISIF_CULH                                                   (0x2cU)
#define ISIF_CULV                                                   (0x30U)
#define ISIF_HSIZE                                                  (0x34U)
#define ISIF_SDOFST                                                 (0x38U)
#define ISIF_CADU                                                   (0x3cU)
#define ISIF_CADL                                                   (0x40U)
#define ISIF_LINCFG0                                                (0x44U)
#define ISIF_LINCFG1                                                (0x48U)
#define ISIF_CCOLP                                                  (0x4cU)
#define ISIF_CRGAIN                                                 (0x50U)
#define ISIF_CGRGAIN                                                (0x54U)
#define ISIF_CGBGAIN                                                (0x58U)
#define ISIF_CBGAIN                                                 (0x5cU)
#define ISIF_COFSTA                                                 (0x60U)
#define ISIF_FLSHCFG0                                               (0x64U)
#define ISIF_FLSHCFG1                                               (0x68U)
#define ISIF_FLSHCFG2                                               (0x6cU)
#define ISIF_VDINT0                                                 (0x70U)
#define ISIF_VDINT1                                                 (0x74U)
#define ISIF_VDINT2                                                 (0x78U)
#define ISIF_MISC                                                   (0x7cU)
#define ISIF_CGAMMAWD                                               (0x80U)
#define ISIF_REC656IF                                               (0x84U)
#define ISIF_CCDCFG                                                 (0x88U)
#define ISIF_DFCCTL                                                 (0x8cU)
#define ISIF_VDFSATLV                                               (0x90U)
#define ISIF_DFCMEMCTL                                              (0x94U)
#define ISIF_DFCMEM0                                                (0x98U)
#define ISIF_DFCMEM1                                                (0x9cU)
#define ISIF_DFCMEM2                                                (0xa0U)
#define ISIF_DFCMEM3                                                (0xa4U)
#define ISIF_DFCMEM4                                                (0xa8U)
#define ISIF_CLAMPCFG                                               (0xacU)
#define ISIF_CLDCOFST                                               (0xb0U)
#define ISIF_CLSV                                                   (0xb4U)
#define ISIF_CLHWIN0                                                (0xb8U)
#define ISIF_CLHWIN1                                                (0xbcU)
#define ISIF_CLHWIN2                                                (0xc0U)
#define ISIF_CLVRV                                                  (0xc4U)
#define ISIF_CLVWIN0                                                (0xc8U)
#define ISIF_CLVWIN1                                                (0xccU)
#define ISIF_CLVWIN2                                                (0xd0U)
#define ISIF_CLVWIN3                                                (0xd4U)
#define ISIF_LSCHOFST                                               (0xd8U)
#define ISIF_LSCVOFST                                               (0xdcU)
#define ISIF_LSCHVAL                                                (0xe0U)
#define ISIF_LSCVVAL                                                (0xe4U)
#define ISIF_2DLSCCFG                                               (0xe8U)
#define ISIF_2DLSCOFST                                              (0xecU)
#define ISIF_2DLSCINI                                               (0xf0U)
#define ISIF_2DLSCGRBU                                              (0xf4U)
#define ISIF_2DLSCGRBL                                              (0xf8U)
#define ISIF_2DLSCGROF                                              (0xfcU)
#define ISIF_2DLSCORBU                                              (0x100U)
#define ISIF_2DLSCORBL                                              (0x104U)
#define ISIF_2DLSCOROF                                              (0x108U)
#define ISIF_2DLSCIRQEN                                             (0x10cU)
#define ISIF_2DLSCIRQST                                             (0x110U)
#define ISIF_FMTCFG                                                 (0x114U)
#define ISIF_FMTPLEN                                                (0x118U)
#define ISIF_FMTSPH                                                 (0x11cU)
#define ISIF_FMTLNH                                                 (0x120U)
#define ISIF_FMTLSV                                                 (0x124U)
#define ISIF_FMTLNV                                                 (0x128U)
#define ISIF_FMTRLEN                                                (0x12cU)
#define ISIF_FMTHCNT                                                (0x130U)
#define ISIF_FMTAPTR0                                               (0x134U)
#define ISIF_FMTAPTR1                                               (0x138U)
#define ISIF_FMTAPTR2                                               (0x13cU)
#define ISIF_FMTAPTR3                                               (0x140U)
#define ISIF_FMTAPTR4                                               (0x144U)
#define ISIF_FMTAPTR5                                               (0x148U)
#define ISIF_FMTAPTR6                                               (0x14cU)
#define ISIF_FMTAPTR7                                               (0x150U)
#define ISIF_FMTAPTR8                                               (0x154U)
#define ISIF_FMTAPTR9                                               (0x158U)
#define ISIF_FMTAPTR10                                              (0x15cU)
#define ISIF_FMTAPTR11                                              (0x160U)
#define ISIF_FMTAPTR12                                              (0x164U)
#define ISIF_FMTAPTR13                                              (0x168U)
#define ISIF_FMTAPTR14                                              (0x16cU)
#define ISIF_FMTAPTR15                                              (0x170U)
#define ISIF_FMTPGMVF0                                              (0x174U)
#define ISIF_FMTPGMVF1                                              (0x178U)
#define ISIF_FMTPGMAPU0                                             (0x17cU)
#define ISIF_FMTPGMAPU1                                             (0x180U)
#define ISIF_FMTPGMAPS0                                             (0x184U)
#define ISIF_FMTPGMAPS1                                             (0x188U)
#define ISIF_FMTPGMAPS2                                             (0x18cU)
#define ISIF_FMTPGMAPS3                                             (0x190U)
#define ISIF_FMTPGMAPS4                                             (0x194U)
#define ISIF_FMTPGMAPS5                                             (0x198U)
#define ISIF_FMTPGMAPS6                                             (0x19cU)
#define ISIF_FMTPGMAPS7                                             (0x1a0U)
#define ISIF_CSCCTL                                                 (0x1a4U)
#define ISIF_CSCM0                                                  (0x1a8U)
#define ISIF_CSCM1                                                  (0x1acU)
#define ISIF_CSCM2                                                  (0x1b0U)
#define ISIF_CSCM3                                                  (0x1b4U)
#define ISIF_CSCM4                                                  (0x1b8U)
#define ISIF_CSCM5                                                  (0x1bcU)
#define ISIF_CSCM6                                                  (0x1c0U)
#define ISIF_CSCM7                                                  (0x1c4U)
#define ISIF_OBWIN0                                                 (0x1c8U)
#define ISIF_OBWIN1                                                 (0x1ccU)
#define ISIF_OBWIN2                                                 (0x1d0U)
#define ISIF_OBWIN3                                                 (0x1d4U)
#define ISIF_OBVAL0                                                 (0x1d8U)
#define ISIF_OBVAL1                                                 (0x1dcU)
#define ISIF_OBVAL2                                                 (0x1e0U)
#define ISIF_OBVAL3                                                 (0x1e4U)
#define ISIF_OBVAL4                                                 (0x1e8U)
#define ISIF_OBVAL5                                                 (0x1ecU)
#define ISIF_OBVAL6                                                 (0x1f0U)
#define ISIF_OBVAL7                                                 (0x1f4U)
#define ISIF_CLKCTL                                                 (0x1f8U)
#define ISIF_CBN                                                    (0x1fcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISIF_SYNCEN_SYEN_SHIFT                                                          (0U)
#define ISIF_SYNCEN_SYEN_MASK                                                           (0x00000001U)
#define ISIF_SYNCEN_SYEN_NEWENUM1                                                        (0U)
#define ISIF_SYNCEN_SYEN_NEWENUM2                                                        (1U)

#define ISIF_SYNCEN_DWEN_SHIFT                                                          (1U)
#define ISIF_SYNCEN_DWEN_MASK                                                           (0x00000002U)
#define ISIF_SYNCEN_DWEN_NEWENUM1                                                        (0U)
#define ISIF_SYNCEN_DWEN_NEWENUM2                                                        (1U)

#define ISIF_SYNCEN_RESERVED_SHIFT                                                      (2U)
#define ISIF_SYNCEN_RESERVED_MASK                                                       (0x0000fffcU)

#define ISIF_SYNCEN_RESERVED1_SHIFT                                                     (16U)
#define ISIF_SYNCEN_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_MODESET_HDVDD_SHIFT                                                        (0U)
#define ISIF_MODESET_HDVDD_MASK                                                         (0x00000001U)
#define ISIF_MODESET_HDVDD_NEWENUM1                                                      (0U)
#define ISIF_MODESET_HDVDD_NEWENUM2                                                      (1U)

#define ISIF_MODESET_FIDD_SHIFT                                                         (1U)
#define ISIF_MODESET_FIDD_MASK                                                          (0x00000002U)
#define ISIF_MODESET_FIDD_NEWENUM1                                                       (0U)
#define ISIF_MODESET_FIDD_NEWENUM2                                                       (1U)

#define ISIF_MODESET_VDPOL_SHIFT                                                        (2U)
#define ISIF_MODESET_VDPOL_MASK                                                         (0x00000004U)
#define ISIF_MODESET_VDPOL_NEWENUM1                                                      (0U)
#define ISIF_MODESET_VDPOL_NEWENUM2                                                      (1U)

#define ISIF_MODESET_HDPOL_SHIFT                                                        (3U)
#define ISIF_MODESET_HDPOL_MASK                                                         (0x00000008U)
#define ISIF_MODESET_HDPOL_NEWENUM1                                                      (0U)
#define ISIF_MODESET_HDPOL_NEWENUM2                                                      (1U)

#define ISIF_MODESET_FIPOL_SHIFT                                                        (4U)
#define ISIF_MODESET_FIPOL_MASK                                                         (0x00000010U)
#define ISIF_MODESET_FIPOL_NEWENUM1                                                      (0U)
#define ISIF_MODESET_FIPOL_NEWENUM2                                                      (1U)

#define ISIF_MODESET_SWEN_SHIFT                                                         (5U)
#define ISIF_MODESET_SWEN_MASK                                                          (0x00000020U)
#define ISIF_MODESET_SWEN_NEWENUM1                                                       (0U)
#define ISIF_MODESET_SWEN_NEWENUM2                                                       (1U)

#define ISIF_MODESET_DPOL_SHIFT                                                         (6U)
#define ISIF_MODESET_DPOL_MASK                                                          (0x00000040U)
#define ISIF_MODESET_DPOL_NEWENUM1                                                       (0U)
#define ISIF_MODESET_DPOL_NEWENUM2                                                       (1U)

#define ISIF_MODESET_CCDMD_SHIFT                                                        (7U)
#define ISIF_MODESET_CCDMD_MASK                                                         (0x00000080U)
#define ISIF_MODESET_CCDMD_NEWENUM1                                                      (0U)
#define ISIF_MODESET_CCDMD_NEWENUM2                                                      (1U)

#define ISIF_MODESET_CCDW_SHIFT                                                         (8U)
#define ISIF_MODESET_CCDW_MASK                                                          (0x00000700U)
#define ISIF_MODESET_CCDW_NEWENUM1                                                       (0U)
#define ISIF_MODESET_CCDW_NEWENUM2                                                       (1U)
#define ISIF_MODESET_CCDW_NEWENUM3                                                       (2U)
#define ISIF_MODESET_CCDW_NEWENUM4                                                       (3U)
#define ISIF_MODESET_CCDW_NEWENUM5                                                       (4U)
#define ISIF_MODESET_CCDW_NEWENUM6                                                       (5U)
#define ISIF_MODESET_CCDW_NEWENUM7                                                       (6U)
#define ISIF_MODESET_CCDW_NEWENUM8                                                       (7U)

#define ISIF_MODESET_INPMOD_SHIFT                                                       (12U)
#define ISIF_MODESET_INPMOD_MASK                                                        (0x00003000U)
#define ISIF_MODESET_INPMOD_NEWENUM1                                                    (0x00000000U)
#define ISIF_MODESET_INPMOD_NEWENUM2                                                    (0x00001000U)
#define ISIF_MODESET_INPMOD_NEWENUM3                                                    (0x00002000U)
#define ISIF_MODESET_INPMOD_NEWENUM4                                                    (0x00003000U)

#define ISIF_MODESET_HLPF_SHIFT                                                         (14U)
#define ISIF_MODESET_HLPF_MASK                                                          (0x00004000U)
#define ISIF_MODESET_HLPF_NEWENUM1                                                       (0U)
#define ISIF_MODESET_HLPF_NEWENUM2                                                       (1U)

#define ISIF_MODESET_MDFS_SHIFT                                                         (15U)
#define ISIF_MODESET_MDFS_MASK                                                          (0x00008000U)
#define ISIF_MODESET_MDFS_NEWENUM1                                                       (0U)
#define ISIF_MODESET_MDFS_NEWENUM2                                                       (1U)

#define ISIF_MODESET_RESERVED1_SHIFT                                                    (16U)
#define ISIF_MODESET_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_MODESET_OVF_SHIFT                                                          (11U)
#define ISIF_MODESET_OVF_MASK                                                           (0x00000800U)
#define ISIF_MODESET_OVF_NEWENUM1                                                        (0U)
#define ISIF_MODESET_OVF_NEWENUM2                                                        (1U)

#define ISIF_HDW_SHIFT                                                                  (0U)
#define ISIF_HDW_MASK                                                                   (0x00000fffU)

#define ISIF_HDW_RESERVED_SHIFT                                                         (12U)
#define ISIF_HDW_RESERVED_MASK                                                          (0x0000f000U)

#define ISIF_HDW_RESERVED1_SHIFT                                                        (16U)
#define ISIF_HDW_RESERVED1_MASK                                                         (0xffff0000U)

#define ISIF_VDW_SHIFT                                                                  (0U)
#define ISIF_VDW_MASK                                                                   (0x00000fffU)

#define ISIF_VDW_RESERVED_SHIFT                                                         (12U)
#define ISIF_VDW_RESERVED_MASK                                                          (0x0000f000U)

#define ISIF_VDW_RESERVED1_SHIFT                                                        (16U)
#define ISIF_VDW_RESERVED1_MASK                                                         (0xffff0000U)

#define ISIF_PPLN_SHIFT                                                                 (0U)
#define ISIF_PPLN_MASK                                                                  (0x0000ffffU)

#define ISIF_PPLN_RESERVED1_SHIFT                                                       (16U)
#define ISIF_PPLN_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_LPFR_SHIFT                                                                 (0U)
#define ISIF_LPFR_MASK                                                                  (0x0000ffffU)

#define ISIF_LPFR_RESERVED1_SHIFT                                                       (16U)
#define ISIF_LPFR_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_SPH_SHIFT                                                                  (0U)
#define ISIF_SPH_MASK                                                                   (0x00007fffU)

#define ISIF_SPH_RESERVED_SHIFT                                                         (15U)
#define ISIF_SPH_RESERVED_MASK                                                          (0x00008000U)

#define ISIF_SPH_RESERVED1_SHIFT                                                        (16U)
#define ISIF_SPH_RESERVED1_MASK                                                         (0xffff0000U)

#define ISIF_LNH_SHIFT                                                                  (0U)
#define ISIF_LNH_MASK                                                                   (0x00007fffU)

#define ISIF_LNH_RESERVED_SHIFT                                                         (15U)
#define ISIF_LNH_RESERVED_MASK                                                          (0x00008000U)

#define ISIF_LNH_RESERVED1_SHIFT                                                        (16U)
#define ISIF_LNH_RESERVED1_MASK                                                         (0xffff0000U)

#define ISIF_SLV0_SHIFT                                                                 (0U)
#define ISIF_SLV0_MASK                                                                  (0x00007fffU)

#define ISIF_SLV0_RESERVED_SHIFT                                                        (15U)
#define ISIF_SLV0_RESERVED_MASK                                                         (0x00008000U)

#define ISIF_SLV0_RESERVED1_SHIFT                                                       (16U)
#define ISIF_SLV0_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_SLV1_SHIFT                                                                 (0U)
#define ISIF_SLV1_MASK                                                                  (0x00007fffU)

#define ISIF_SLV1_RESERVED1_SHIFT                                                       (16U)
#define ISIF_SLV1_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_SLV1_RESERVED_SHIFT                                                        (15U)
#define ISIF_SLV1_RESERVED_MASK                                                         (0x00008000U)

#define ISIF_LNV_SHIFT                                                                  (0U)
#define ISIF_LNV_MASK                                                                   (0x00007fffU)

#define ISIF_LNV_RESERVED_SHIFT                                                         (15U)
#define ISIF_LNV_RESERVED_MASK                                                          (0x00008000U)

#define ISIF_LNV_RESERVED1_SHIFT                                                        (16U)
#define ISIF_LNV_RESERVED1_MASK                                                         (0xffff0000U)

#define ISIF_CULH_CLHO_SHIFT                                                            (0U)
#define ISIF_CULH_CLHO_MASK                                                             (0x000000ffU)
#define ISIF_CULH_CLHO_NEWENUM1                                                          (0U)
#define ISIF_CULH_CLHO_NEWENUM2                                                          (1U)

#define ISIF_CULH_CLHE_SHIFT                                                            (8U)
#define ISIF_CULH_CLHE_MASK                                                             (0x0000ff00U)
#define ISIF_CULH_CLHE_NEWENUM1                                                          (0U)
#define ISIF_CULH_CLHE_NEWENUM2                                                          (1U)

#define ISIF_CULH_RESERVED_SHIFT                                                        (16U)
#define ISIF_CULH_RESERVED_MASK                                                         (0xffff0000U)

#define ISIF_CULV_SHIFT                                                                 (0U)
#define ISIF_CULV_MASK                                                                  (0x000000ffU)
#define ISIF_CULV_NEWENUM1                                                               (0U)
#define ISIF_CULV_NEWENUM2                                                               (1U)

#define ISIF_CULV_RESERVED_SHIFT                                                        (8U)
#define ISIF_CULV_RESERVED_MASK                                                         (0x0000ff00U)

#define ISIF_CULV_RESERVED1_SHIFT                                                       (16U)
#define ISIF_CULV_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_HSIZE_SHIFT                                                                (0U)
#define ISIF_HSIZE_MASK                                                                 (0x00000fffU)

#define ISIF_HSIZE_ADCR_SHIFT                                                           (12U)
#define ISIF_HSIZE_ADCR_MASK                                                            (0x00001000U)
#define ISIF_HSIZE_ADCR_NEWENUM1                                                         (0U)
#define ISIF_HSIZE_ADCR_NEWENUM2                                                         (1U)

#define ISIF_HSIZE_RESERVED_SHIFT                                                       (13U)
#define ISIF_HSIZE_RESERVED_MASK                                                        (0x0000e000U)

#define ISIF_HSIZE_RESERVED1_SHIFT                                                      (16U)
#define ISIF_HSIZE_RESERVED1_MASK                                                       (0xffff0000U)

#define ISIF_SDOFST_LOFSTOO_SHIFT                                                       (0U)
#define ISIF_SDOFST_LOFSTOO_MASK                                                        (0x00000007U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM1                                                     (0U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM2                                                     (1U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM3                                                     (2U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM4                                                     (3U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM5                                                     (4U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM6                                                     (5U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM7                                                     (6U)
#define ISIF_SDOFST_LOFSTOO_NEWENUM8                                                     (7U)

#define ISIF_SDOFST_LOFSTEO_SHIFT                                                       (3U)
#define ISIF_SDOFST_LOFSTEO_MASK                                                        (0x00000038U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM1                                                     (0U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM2                                                     (1U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM3                                                     (2U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM4                                                     (3U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM5                                                     (4U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM6                                                     (5U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM7                                                     (6U)
#define ISIF_SDOFST_LOFSTEO_NEWENUM8                                                     (7U)

#define ISIF_SDOFST_LOFSTOE_SHIFT                                                       (6U)
#define ISIF_SDOFST_LOFSTOE_MASK                                                        (0x000001c0U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM1                                                     (0U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM2                                                     (1U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM3                                                     (2U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM4                                                     (3U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM5                                                     (4U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM6                                                     (5U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM7                                                     (6U)
#define ISIF_SDOFST_LOFSTOE_NEWENUM8                                                     (7U)

#define ISIF_SDOFST_LOFSTEE_SHIFT                                                       (9U)
#define ISIF_SDOFST_LOFSTEE_MASK                                                        (0x00000e00U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM1                                                     (0U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM2                                                     (1U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM3                                                     (2U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM4                                                     (3U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM5                                                     (4U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM6                                                     (5U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM7                                                     (6U)
#define ISIF_SDOFST_LOFSTEE_NEWENUM8                                                     (7U)

#define ISIF_SDOFST_FOFST_SHIFT                                                         (12U)
#define ISIF_SDOFST_FOFST_MASK                                                          (0x00003000U)
#define ISIF_SDOFST_FOFST_NEWENUM1                                                       (0U)
#define ISIF_SDOFST_FOFST_NEWENUM2                                                       (1U)
#define ISIF_SDOFST_FOFST_NEWENUM3                                                       (2U)
#define ISIF_SDOFST_FOFST_NEWENUM4                                                       (3U)

#define ISIF_SDOFST_FIINV_SHIFT                                                         (14U)
#define ISIF_SDOFST_FIINV_MASK                                                          (0x00004000U)
#define ISIF_SDOFST_FIINV_NEWENUM1                                                       (0U)
#define ISIF_SDOFST_FIINV_NEWENUM2                                                       (1U)

#define ISIF_SDOFST_RESERVED_SHIFT                                                      (15U)
#define ISIF_SDOFST_RESERVED_MASK                                                       (0x00008000U)

#define ISIF_SDOFST_RESERVED1_SHIFT                                                     (16U)
#define ISIF_SDOFST_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CADU_SHIFT                                                                 (0U)
#define ISIF_CADU_MASK                                                                  (0x000007ffU)

#define ISIF_CADU_RESERVED_SHIFT                                                        (11U)
#define ISIF_CADU_RESERVED_MASK                                                         (0x0000f800U)

#define ISIF_CADU_RESERVED1_SHIFT                                                       (16U)
#define ISIF_CADU_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_CADL_SHIFT                                                                 (0U)
#define ISIF_CADL_MASK                                                                  (0x0000ffffU)

#define ISIF_CADL_RESERVED_SHIFT                                                        (16U)
#define ISIF_CADL_RESERVED_MASK                                                         (0xffff0000U)

#define ISIF_LINCFG0_LINEN_SHIFT                                                        (0U)
#define ISIF_LINCFG0_LINEN_MASK                                                         (0x00000001U)
#define ISIF_LINCFG0_LINEN_NEWENUM1                                                      (0U)
#define ISIF_LINCFG0_LINEN_NEWENUM2                                                      (1U)

#define ISIF_LINCFG0_LINMD_SHIFT                                                        (1U)
#define ISIF_LINCFG0_LINMD_MASK                                                         (0x00000002U)
#define ISIF_LINCFG0_LINMD_NEWENUM1                                                      (0U)
#define ISIF_LINCFG0_LINMD_NEWENUM2                                                      (1U)

#define ISIF_LINCFG0_CORRSFT_SHIFT                                                      (4U)
#define ISIF_LINCFG0_CORRSFT_MASK                                                       (0x00000070U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM1                                                    (0U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM2                                                    (1U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM3                                                    (2U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM4                                                    (3U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM5                                                    (4U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM6                                                    (5U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM7                                                    (6U)
#define ISIF_LINCFG0_CORRSFT_NEWENUM8                                                    (7U)

#define ISIF_LINCFG0_RESERVED_SHIFT                                                     (2U)
#define ISIF_LINCFG0_RESERVED_MASK                                                      (0x0000000cU)

#define ISIF_LINCFG0_RESERVED1_SHIFT                                                    (7U)
#define ISIF_LINCFG0_RESERVED1_MASK                                                     (0x0000ff80U)

#define ISIF_LINCFG0_RESERVED2_SHIFT                                                    (16U)
#define ISIF_LINCFG0_RESERVED2_MASK                                                     (0xffff0000U)

#define ISIF_LINCFG1_LUTSCL_SHIFT                                                       (0U)
#define ISIF_LINCFG1_LUTSCL_MASK                                                        (0x000007ffU)

#define ISIF_LINCFG1_RESERVED_SHIFT                                                     (11U)
#define ISIF_LINCFG1_RESERVED_MASK                                                      (0x0000f800U)

#define ISIF_LINCFG1_RESERVED1_SHIFT                                                    (16U)
#define ISIF_LINCFG1_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CCOLP_CP3_F0_SHIFT                                                         (0U)
#define ISIF_CCOLP_CP3_F0_MASK                                                          (0x00000003U)
#define ISIF_CCOLP_CP3_F0_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP3_F0_NEWENUM2                                                      (0x00000001U)
#define ISIF_CCOLP_CP3_F0_NEWENUM3                                                      (0x00000002U)
#define ISIF_CCOLP_CP3_F0_NEWENUM4                                                      (0x00000003U)

#define ISIF_CCOLP_CP2_F0_SHIFT                                                         (2U)
#define ISIF_CCOLP_CP2_F0_MASK                                                          (0x0000000cU)
#define ISIF_CCOLP_CP2_F0_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP2_F0_NEWENUM2                                                      (0x00000004U)
#define ISIF_CCOLP_CP2_F0_NEWENUM3                                                      (0x00000008U)
#define ISIF_CCOLP_CP2_F0_NEWENUM4                                                      (0x0000000CU)

#define ISIF_CCOLP_CP1_F0_SHIFT                                                         (4U)
#define ISIF_CCOLP_CP1_F0_MASK                                                          (0x00000030U)
#define ISIF_CCOLP_CP1_F0_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP1_F0_NEWENUM2                                                      (0x00000010U)
#define ISIF_CCOLP_CP1_F0_NEWENUM3                                                      (0x00000020U)
#define ISIF_CCOLP_CP1_F0_NEWENUM4                                                      (0x00000030U)

#define ISIF_CCOLP_CP0_F0_SHIFT                                                         (6U)
#define ISIF_CCOLP_CP0_F0_MASK                                                          (0x000000c0U)
#define ISIF_CCOLP_CP0_F0_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP0_F0_NEWENUM2                                                      (0x00000040U)
#define ISIF_CCOLP_CP0_F0_NEWENUM3                                                      (0x00000080U)
#define ISIF_CCOLP_CP0_F0_NEWENUM4                                                      (0x000000C0U)

#define ISIF_CCOLP_CP3_F1_SHIFT                                                         (8U)
#define ISIF_CCOLP_CP3_F1_MASK                                                          (0x00000300U)
#define ISIF_CCOLP_CP3_F1_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP3_F1_NEWENUM2                                                      (0x00000100U)
#define ISIF_CCOLP_CP3_F1_NEWENUM3                                                      (0x00000200U)
#define ISIF_CCOLP_CP3_F1_NEWENUM4                                                      (0x00000300U)

#define ISIF_CCOLP_CP2_F1_SHIFT                                                         (10U)
#define ISIF_CCOLP_CP2_F1_MASK                                                          (0x00000c00U)
#define ISIF_CCOLP_CP2_F1_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP2_F1_NEWENUM2                                                      (0x00000400U)
#define ISIF_CCOLP_CP2_F1_NEWENUM3                                                      (0x00000800U)
#define ISIF_CCOLP_CP2_F1_NEWENUM4                                                      (0x00000C00U)

#define ISIF_CCOLP_CP1_F1_SHIFT                                                         (12U)
#define ISIF_CCOLP_CP1_F1_MASK                                                          (0x00003000U)
#define ISIF_CCOLP_CP1_F1_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP1_F1_NEWENUM2                                                      (0x00001000U)
#define ISIF_CCOLP_CP1_F1_NEWENUM3                                                      (0x00002000U)
#define ISIF_CCOLP_CP1_F1_NEWENUM4                                                      (0x00003000U)

#define ISIF_CCOLP_CP0_F1_SHIFT                                                         (14U)
#define ISIF_CCOLP_CP0_F1_MASK                                                          (0x0000c000U)
#define ISIF_CCOLP_CP0_F1_NEWENUM1                                                      (0x00000000U)
#define ISIF_CCOLP_CP0_F1_NEWENUM2                                                      (0x00004000U)
#define ISIF_CCOLP_CP0_F1_NEWENUM3                                                      (0x00008000U)
#define ISIF_CCOLP_CP0_F1_NEWENUM4                                                      (0x0000C000U)

#define ISIF_CCOLP_RESERVED_SHIFT                                                       (16U)
#define ISIF_CCOLP_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CRGAIN_CGR_SHIFT                                                           (0U)
#define ISIF_CRGAIN_CGR_MASK                                                            (0x00000fffU)

#define ISIF_CRGAIN_RESERVED_SHIFT                                                      (12U)
#define ISIF_CRGAIN_RESERVED_MASK                                                       (0x0000f000U)

#define ISIF_CRGAIN_RESERVED1_SHIFT                                                     (16U)
#define ISIF_CRGAIN_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CGRGAIN_CGGR_SHIFT                                                         (0U)
#define ISIF_CGRGAIN_CGGR_MASK                                                          (0x00000fffU)

#define ISIF_CGRGAIN_RESERVED_SHIFT                                                     (12U)
#define ISIF_CGRGAIN_RESERVED_MASK                                                      (0x0000f000U)

#define ISIF_CGRGAIN_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CGRGAIN_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CGBGAIN_CGGB_SHIFT                                                         (0U)
#define ISIF_CGBGAIN_CGGB_MASK                                                          (0x00000fffU)

#define ISIF_CGBGAIN_RESERVED_SHIFT                                                     (12U)
#define ISIF_CGBGAIN_RESERVED_MASK                                                      (0x0000f000U)

#define ISIF_CGBGAIN_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CGBGAIN_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CBGAIN_CGB_SHIFT                                                           (0U)
#define ISIF_CBGAIN_CGB_MASK                                                            (0x00000fffU)

#define ISIF_CBGAIN_RESERVED_SHIFT                                                      (12U)
#define ISIF_CBGAIN_RESERVED_MASK                                                       (0x0000f000U)

#define ISIF_CBGAIN_RESERVED1_SHIFT                                                     (16U)
#define ISIF_CBGAIN_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_COFSTA_COFT_SHIFT                                                          (0U)
#define ISIF_COFSTA_COFT_MASK                                                           (0x00000fffU)

#define ISIF_COFSTA_RESERVED_SHIFT                                                      (12U)
#define ISIF_COFSTA_RESERVED_MASK                                                       (0x0000f000U)

#define ISIF_COFSTA_RESERVED1_SHIFT                                                     (16U)
#define ISIF_COFSTA_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_FLSHCFG0_FLSHEN_SHIFT                                                      (0U)
#define ISIF_FLSHCFG0_FLSHEN_MASK                                                       (0x00000001U)
#define ISIF_FLSHCFG0_FLSHEN_NEWENUM1                                                    (0U)
#define ISIF_FLSHCFG0_FLSHEN_NEWENUM2                                                    (1U)

#define ISIF_FLSHCFG0_RESERVED_SHIFT                                                    (1U)
#define ISIF_FLSHCFG0_RESERVED_MASK                                                     (0x0000fffeU)

#define ISIF_FLSHCFG0_RESERVED1_SHIFT                                                   (16U)
#define ISIF_FLSHCFG0_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_FLSHCFG1_SFLSH_SHIFT                                                       (0U)
#define ISIF_FLSHCFG1_SFLSH_MASK                                                        (0x00007fffU)

#define ISIF_FLSHCFG1_RESERVED_SHIFT                                                    (15U)
#define ISIF_FLSHCFG1_RESERVED_MASK                                                     (0x00008000U)

#define ISIF_FLSHCFG1_RESERVED1_SHIFT                                                   (16U)
#define ISIF_FLSHCFG1_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_FLSHCFG2_VFLSH_SHIFT                                                       (0U)
#define ISIF_FLSHCFG2_VFLSH_MASK                                                        (0x0000ffffU)

#define ISIF_FLSHCFG2_RESERVED_SHIFT                                                    (16U)
#define ISIF_FLSHCFG2_RESERVED_MASK                                                     (0xffff0000U)

#define ISIF_VDINT0_CVD0_SHIFT                                                          (0U)
#define ISIF_VDINT0_CVD0_MASK                                                           (0x00007fffU)

#define ISIF_VDINT0_RESERVED_SHIFT                                                      (15U)
#define ISIF_VDINT0_RESERVED_MASK                                                       (0x00008000U)

#define ISIF_VDINT0_RESERVED1_SHIFT                                                     (16U)
#define ISIF_VDINT0_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_VDINT1_CVD1_SHIFT                                                          (0U)
#define ISIF_VDINT1_CVD1_MASK                                                           (0x00007fffU)

#define ISIF_VDINT1_RESERVED_SHIFT                                                      (15U)
#define ISIF_VDINT1_RESERVED_MASK                                                       (0x00008000U)

#define ISIF_VDINT1_RESERVED1_SHIFT                                                     (16U)
#define ISIF_VDINT1_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_VDINT2_CVD2_SHIFT                                                          (0U)
#define ISIF_VDINT2_CVD2_MASK                                                           (0x00007fffU)

#define ISIF_VDINT2_RESERVED_SHIFT                                                      (15U)
#define ISIF_VDINT2_RESERVED_MASK                                                       (0x00008000U)

#define ISIF_VDINT2_RESERVED1_SHIFT                                                     (16U)
#define ISIF_VDINT2_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_MISC_DPCMEN_SHIFT                                                          (12U)
#define ISIF_MISC_DPCMEN_MASK                                                           (0x00001000U)
#define ISIF_MISC_DPCMEN_NEWENUM1                                                        (0U)
#define ISIF_MISC_DPCMEN_NEWENUM2                                                        (1U)

#define ISIF_MISC_DPCMPRE_SHIFT                                                         (13U)
#define ISIF_MISC_DPCMPRE_MASK                                                          (0x00002000U)
#define ISIF_MISC_DPCMPRE_NEWENUM1                                                       (0U)
#define ISIF_MISC_DPCMPRE_NEWENUM2                                                       (1U)

#define ISIF_MISC_RESERVED_SHIFT                                                        (1U)
#define ISIF_MISC_RESERVED_MASK                                                         (0x00000ffeU)

#define ISIF_MISC_RESERVED1_SHIFT                                                       (14U)
#define ISIF_MISC_RESERVED1_MASK                                                        (0x0000c000U)

#define ISIF_MISC_RESERVED2_SHIFT                                                       (16U)
#define ISIF_MISC_RESERVED2_MASK                                                        (0xffff0000U)

#define ISIF_MISC_RESERVED3_SHIFT                                                       (0U)
#define ISIF_MISC_RESERVED3_MASK                                                        (0x00000001U)

#define ISIF_CGAMMAWD_CCDTBL_SHIFT                                                      (0U)
#define ISIF_CGAMMAWD_CCDTBL_MASK                                                       (0x00000001U)
#define ISIF_CGAMMAWD_CCDTBL_NEWENUM1                                                    (0U)
#define ISIF_CGAMMAWD_CCDTBL_NEWENUM2                                                    (1U)

#define ISIF_CGAMMAWD_GWDI_SHIFT                                                        (1U)
#define ISIF_CGAMMAWD_GWDI_MASK                                                         (0x0000001eU)
#define ISIF_CGAMMAWD_GWDI_NEWENUM1                                                      (0U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM2                                                      (1U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM3                                                      (2U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM4                                                      (3U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM5                                                      (4U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM6                                                      (5U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM7                                                      (6U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM8                                                      (7U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM9                                                      (8U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM10                                                     (9U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM11                                                     (10U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM12                                                     (11U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM13                                                     (12U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM14                                                     (13U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM15                                                     (14U)
#define ISIF_CGAMMAWD_GWDI_NEWENUM16                                                     (15U)

#define ISIF_CGAMMAWD_CFAP_SHIFT                                                        (5U)
#define ISIF_CGAMMAWD_CFAP_MASK                                                         (0x00000020U)
#define ISIF_CGAMMAWD_CFAP_NEWENUM1                                                      (0U)
#define ISIF_CGAMMAWD_CFAP_NEWENUM2                                                      (1U)

#define ISIF_CGAMMAWD_OFSTEN0_SHIFT                                                     (8U)
#define ISIF_CGAMMAWD_OFSTEN0_MASK                                                      (0x00000100U)
#define ISIF_CGAMMAWD_OFSTEN0_NEWENUM1                                                   (0U)
#define ISIF_CGAMMAWD_OFSTEN0_NEWENUM2                                                   (1U)

#define ISIF_CGAMMAWD_OFSTEN1_SHIFT                                                     (9U)
#define ISIF_CGAMMAWD_OFSTEN1_MASK                                                      (0x00000200U)
#define ISIF_CGAMMAWD_OFSTEN1_NEWENUM1                                                   (0U)
#define ISIF_CGAMMAWD_OFSTEN1_NEWENUM2                                                   (1U)

#define ISIF_CGAMMAWD_OFSTEN2_SHIFT                                                     (10U)
#define ISIF_CGAMMAWD_OFSTEN2_MASK                                                      (0x00000400U)
#define ISIF_CGAMMAWD_OFSTEN2_NEWENUM1                                                   (0U)
#define ISIF_CGAMMAWD_OFSTEN2_NEWENUM2                                                   (1U)

#define ISIF_CGAMMAWD_WBEN0_SHIFT                                                       (12U)
#define ISIF_CGAMMAWD_WBEN0_MASK                                                        (0x00001000U)
#define ISIF_CGAMMAWD_WBEN0_NEWENUM1                                                     (0U)
#define ISIF_CGAMMAWD_WBEN0_NEWENUM2                                                     (1U)

#define ISIF_CGAMMAWD_WBEN1_SHIFT                                                       (13U)
#define ISIF_CGAMMAWD_WBEN1_MASK                                                        (0x00002000U)
#define ISIF_CGAMMAWD_WBEN1_NEWENUM1                                                     (0U)
#define ISIF_CGAMMAWD_WBEN1_NEWENUM2                                                     (1U)

#define ISIF_CGAMMAWD_WBEN2_SHIFT                                                       (14U)
#define ISIF_CGAMMAWD_WBEN2_MASK                                                        (0x00004000U)
#define ISIF_CGAMMAWD_WBEN2_NEWENUM1                                                     (0U)
#define ISIF_CGAMMAWD_WBEN2_NEWENUM2                                                     (1U)

#define ISIF_CGAMMAWD_RESERVED1_SHIFT                                                   (11U)
#define ISIF_CGAMMAWD_RESERVED1_MASK                                                    (0x00000800U)

#define ISIF_CGAMMAWD_RESERVED2_SHIFT                                                   (15U)
#define ISIF_CGAMMAWD_RESERVED2_MASK                                                    (0x00008000U)

#define ISIF_CGAMMAWD_RESERVED_SHIFT                                                    (6U)
#define ISIF_CGAMMAWD_RESERVED_MASK                                                     (0x000000c0U)

#define ISIF_CGAMMAWD_RESERVED3_SHIFT                                                   (16U)
#define ISIF_CGAMMAWD_RESERVED3_MASK                                                    (0xffff0000U)

#define ISIF_REC656IF_ECCFVH_SHIFT                                                      (0U)
#define ISIF_REC656IF_ECCFVH_MASK                                                       (0x00000001U)
#define ISIF_REC656IF_ECCFVH_NEWENUM1                                                    (0U)
#define ISIF_REC656IF_ECCFVH_NEWENUM2                                                    (1U)

#define ISIF_REC656IF_R656ON_SHIFT                                                      (1U)
#define ISIF_REC656IF_R656ON_MASK                                                       (0x00000002U)
#define ISIF_REC656IF_R656ON_NEWENUM1                                                    (0U)
#define ISIF_REC656IF_R656ON_NEWENUM2                                                    (1U)

#define ISIF_REC656IF_RESERVED_SHIFT                                                    (2U)
#define ISIF_REC656IF_RESERVED_MASK                                                     (0x0000fffcU)

#define ISIF_REC656IF_RESERVED1_SHIFT                                                   (16U)
#define ISIF_REC656IF_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_CCDCFG_SDRPACK_SHIFT                                                       (0U)
#define ISIF_CCDCFG_SDRPACK_MASK                                                        (0x00000003U)
#define ISIF_CCDCFG_SDRPACK_NEWENUM1                                                     (0U)
#define ISIF_CCDCFG_SDRPACK_NEWENUM2                                                     (1U)
#define ISIF_CCDCFG_SDRPACK_NEWENUM3                                                     (2U)
#define ISIF_CCDCFG_SDRPACK_NEWENUM4                                                     (3U)

#define ISIF_CCDCFG_YCINSWP_SHIFT                                                       (4U)
#define ISIF_CCDCFG_YCINSWP_MASK                                                        (0x00000010U)
#define ISIF_CCDCFG_YCINSWP_NEWENUM1                                                     (0U)
#define ISIF_CCDCFG_YCINSWP_NEWENUM2                                                     (1U)

#define ISIF_CCDCFG_BT656_SHIFT                                                         (5U)
#define ISIF_CCDCFG_BT656_MASK                                                          (0x00000020U)
#define ISIF_CCDCFG_BT656_NEWENUM1                                                       (0U)
#define ISIF_CCDCFG_BT656_NEWENUM2                                                       (1U)

#define ISIF_CCDCFG_FIDMD_SHIFT                                                         (6U)
#define ISIF_CCDCFG_FIDMD_MASK                                                          (0x000000c0U)
#define ISIF_CCDCFG_FIDMD_NEWENUM1                                                       (0U)
#define ISIF_CCDCFG_FIDMD_NEWENUM2                                                       (1U)
#define ISIF_CCDCFG_FIDMD_NEWENUM3                                                       (2U)
#define ISIF_CCDCFG_FIDMD_NEWENUM4                                                       (3U)

#define ISIF_CCDCFG_WENLOG_SHIFT                                                        (8U)
#define ISIF_CCDCFG_WENLOG_MASK                                                         (0x00000100U)
#define ISIF_CCDCFG_WENLOG_NEWENUM1                                                      (0U)
#define ISIF_CCDCFG_WENLOG_NEWENUM2                                                      (1U)

#define ISIF_CCDCFG_TRGSEL_SHIFT                                                        (9U)
#define ISIF_CCDCFG_TRGSEL_MASK                                                         (0x00000200U)
#define ISIF_CCDCFG_TRGSEL_NEWENUM1                                                      (0U)
#define ISIF_CCDCFG_TRGSEL_NEWENUM2                                                      (1U)

#define ISIF_CCDCFG_EXTRG_SHIFT                                                         (10U)
#define ISIF_CCDCFG_EXTRG_MASK                                                          (0x00000400U)

#define ISIF_CCDCFG_Y8POS_SHIFT                                                         (11U)
#define ISIF_CCDCFG_Y8POS_MASK                                                          (0x00000800U)
#define ISIF_CCDCFG_Y8POS_NEWENUM1                                                       (0U)
#define ISIF_CCDCFG_Y8POS_NEWENUM2                                                       (1U)

#define ISIF_CCDCFG_BSWD_SHIFT                                                          (12U)
#define ISIF_CCDCFG_BSWD_MASK                                                           (0x00001000U)
#define ISIF_CCDCFG_BSWD_NEWENUM1                                                        (0U)
#define ISIF_CCDCFG_BSWD_NEWENUM2                                                        (1U)

#define ISIF_CCDCFG_MSBINVI_SHIFT                                                       (13U)
#define ISIF_CCDCFG_MSBINVI_MASK                                                        (0x00002000U)
#define ISIF_CCDCFG_MSBINVI_NEWENUM1                                                     (0U)
#define ISIF_CCDCFG_MSBINVI_NEWENUM2                                                     (1U)

#define ISIF_CCDCFG_VLDC_SHIFT                                                          (15U)
#define ISIF_CCDCFG_VLDC_MASK                                                           (0x00008000U)
#define ISIF_CCDCFG_VLDC_NEWENUM1                                                        (0U)
#define ISIF_CCDCFG_VLDC_NEWENUM2                                                        (1U)

#define ISIF_CCDCFG_RESERVED1_SHIFT                                                     (16U)
#define ISIF_CCDCFG_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CCDCFG_RESERVED2_SHIFT                                                     (2U)
#define ISIF_CCDCFG_RESERVED2_MASK                                                      (0x00000004U)

#define ISIF_CCDCFG_RESERVED3_SHIFT                                                     (14U)
#define ISIF_CCDCFG_RESERVED3_MASK                                                      (0x00004000U)

#define ISIF_CCDCFG_RESERVED_SHIFT                                                      (3U)
#define ISIF_CCDCFG_RESERVED_MASK                                                       (0x00000008U)

#define ISIF_DFCCTL_VDFCEN_SHIFT                                                        (4U)
#define ISIF_DFCCTL_VDFCEN_MASK                                                         (0x00000010U)
#define ISIF_DFCCTL_VDFCEN_NEWENUM1                                                      (0U)
#define ISIF_DFCCTL_VDFCEN_NEWENUM2                                                      (1U)

#define ISIF_DFCCTL_VDFCSL_SHIFT                                                        (5U)
#define ISIF_DFCCTL_VDFCSL_MASK                                                         (0x00000060U)
#define ISIF_DFCCTL_VDFCSL_NEWENUM1                                                      (0U)
#define ISIF_DFCCTL_VDFCSL_NEWENUM2                                                      (1U)
#define ISIF_DFCCTL_VDFCSL_NEWENUM3                                                      (2U)
#define ISIF_DFCCTL_VDFCSL_NEWENUM4                                                      (3U)

#define ISIF_DFCCTL_VDFCUDA_SHIFT                                                       (7U)
#define ISIF_DFCCTL_VDFCUDA_MASK                                                        (0x00000080U)
#define ISIF_DFCCTL_VDFCUDA_NEWENUM1                                                     (0U)
#define ISIF_DFCCTL_VDFCUDA_NEWENUM2                                                     (1U)

#define ISIF_DFCCTL_VDFLSFT_SHIFT                                                       (8U)
#define ISIF_DFCCTL_VDFLSFT_MASK                                                        (0x00000700U)

#define ISIF_DFCCTL_RESERVED_SHIFT                                                      (0U)
#define ISIF_DFCCTL_RESERVED_MASK                                                       (0x0000000fU)

#define ISIF_DFCCTL_RESERVED1_SHIFT                                                     (11U)
#define ISIF_DFCCTL_RESERVED1_MASK                                                      (0x0000f800U)

#define ISIF_DFCCTL_RESERVED2_SHIFT                                                     (16U)
#define ISIF_DFCCTL_RESERVED2_MASK                                                      (0xffff0000U)

#define ISIF_VDFSATLV_VDFSLV_SHIFT                                                      (0U)
#define ISIF_VDFSATLV_VDFSLV_MASK                                                       (0x00000fffU)

#define ISIF_VDFSATLV_RESERVED1_SHIFT                                                   (16U)
#define ISIF_VDFSATLV_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_VDFSATLV_RESERVED_SHIFT                                                    (12U)
#define ISIF_VDFSATLV_RESERVED_MASK                                                     (0x0000f000U)

#define ISIF_DFCMEMCTL_DFCMWR_SHIFT                                                     (0U)
#define ISIF_DFCMEMCTL_DFCMWR_MASK                                                      (0x00000001U)

#define ISIF_DFCMEMCTL_DFCMRD_SHIFT                                                     (1U)
#define ISIF_DFCMEMCTL_DFCMRD_MASK                                                      (0x00000002U)

#define ISIF_DFCMEMCTL_DFCMARST_SHIFT                                                   (2U)
#define ISIF_DFCMEMCTL_DFCMARST_MASK                                                    (0x00000004U)
#define ISIF_DFCMEMCTL_DFCMARST_NEWENUM1                                                 (0U)
#define ISIF_DFCMEMCTL_DFCMARST_NEWENUM2                                                 (1U)

#define ISIF_DFCMEMCTL_DFCMCLR_SHIFT                                                    (4U)
#define ISIF_DFCMEMCTL_DFCMCLR_MASK                                                     (0x00000010U)

#define ISIF_DFCMEMCTL_RESERVED_SHIFT                                                   (3U)
#define ISIF_DFCMEMCTL_RESERVED_MASK                                                    (0x00000008U)

#define ISIF_DFCMEMCTL_RESERVED1_SHIFT                                                  (5U)
#define ISIF_DFCMEMCTL_RESERVED1_MASK                                                   (0x0000ffe0U)

#define ISIF_DFCMEMCTL_RESERVED2_SHIFT                                                  (16U)
#define ISIF_DFCMEMCTL_RESERVED2_MASK                                                   (0xffff0000U)

#define ISIF_DFCMEM0_SHIFT                                                              (0U)
#define ISIF_DFCMEM0_MASK                                                               (0x00001fffU)

#define ISIF_DFCMEM0_RESERVED_SHIFT                                                     (13U)
#define ISIF_DFCMEM0_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_DFCMEM0_RESERVED1_SHIFT                                                    (16U)
#define ISIF_DFCMEM0_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_DFCMEM1_SHIFT                                                              (0U)
#define ISIF_DFCMEM1_MASK                                                               (0x00001fffU)

#define ISIF_DFCMEM1_RESERVED_SHIFT                                                     (13U)
#define ISIF_DFCMEM1_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_DFCMEM1_RESERVED1_SHIFT                                                    (16U)
#define ISIF_DFCMEM1_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_DFCMEM2_SHIFT                                                              (0U)
#define ISIF_DFCMEM2_MASK                                                               (0x000000ffU)

#define ISIF_DFCMEM2_RESERVED_SHIFT                                                     (8U)
#define ISIF_DFCMEM2_RESERVED_MASK                                                      (0x0000ff00U)

#define ISIF_DFCMEM2_RESERVED1_SHIFT                                                    (16U)
#define ISIF_DFCMEM2_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_DFCMEM3_SHIFT                                                              (0U)
#define ISIF_DFCMEM3_MASK                                                               (0x000000ffU)

#define ISIF_DFCMEM3_RESERVED_SHIFT                                                     (8U)
#define ISIF_DFCMEM3_RESERVED_MASK                                                      (0x0000ff00U)

#define ISIF_DFCMEM3_RESERVED1_SHIFT                                                    (16U)
#define ISIF_DFCMEM3_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_DFCMEM4_SHIFT                                                              (0U)
#define ISIF_DFCMEM4_MASK                                                               (0x000000ffU)

#define ISIF_DFCMEM4_RESERVED1_SHIFT                                                    (16U)
#define ISIF_DFCMEM4_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_DFCMEM4_RESERVED_SHIFT                                                     (8U)
#define ISIF_DFCMEM4_RESERVED_MASK                                                      (0x0000ff00U)

#define ISIF_CLAMPCFG_CLEN_SHIFT                                                        (0U)
#define ISIF_CLAMPCFG_CLEN_MASK                                                         (0x00000001U)
#define ISIF_CLAMPCFG_CLEN_NEWENUM1                                                      (0U)
#define ISIF_CLAMPCFG_CLEN_NEWENUM2                                                      (1U)

#define ISIF_CLAMPCFG_CLHMD_SHIFT                                                       (1U)
#define ISIF_CLAMPCFG_CLHMD_MASK                                                        (0x00000006U)
#define ISIF_CLAMPCFG_CLHMD_NEWENUM1                                                     (0U)
#define ISIF_CLAMPCFG_CLHMD_NEWENUM2                                                     (1U)
#define ISIF_CLAMPCFG_CLHMD_NEWENUM3                                                     (2U)
#define ISIF_CLAMPCFG_CLHMD_NEWENUM4                                                     (3U)

#define ISIF_CLAMPCFG_CLMD_SHIFT                                                        (4U)
#define ISIF_CLAMPCFG_CLMD_MASK                                                         (0x00000010U)
#define ISIF_CLAMPCFG_CLMD_NEWENUM1                                                      (0U)
#define ISIF_CLAMPCFG_CLMD_NEWENUM2                                                      (1U)

#define ISIF_CLAMPCFG_RESERVED_SHIFT                                                    (3U)
#define ISIF_CLAMPCFG_RESERVED_MASK                                                     (0x00000008U)

#define ISIF_CLAMPCFG_RESERVED1_SHIFT                                                   (5U)
#define ISIF_CLAMPCFG_RESERVED1_MASK                                                    (0x0000ffe0U)

#define ISIF_CLAMPCFG_RESERVED2_SHIFT                                                   (16U)
#define ISIF_CLAMPCFG_RESERVED2_MASK                                                    (0xffff0000U)

#define ISIF_CLDCOFST_CLDC_SHIFT                                                        (0U)
#define ISIF_CLDCOFST_CLDC_MASK                                                         (0x00001fffU)

#define ISIF_CLDCOFST_RESERVED_SHIFT                                                    (16U)
#define ISIF_CLDCOFST_RESERVED_MASK                                                     (0xffff0000U)

#define ISIF_CLDCOFST_RESERVED1_SHIFT                                                   (13U)
#define ISIF_CLDCOFST_RESERVED1_MASK                                                    (0x0000e000U)

#define ISIF_CLSV_SHIFT                                                                 (0U)
#define ISIF_CLSV_MASK                                                                  (0x00001fffU)

#define ISIF_CLSV_RESERVED_SHIFT                                                        (13U)
#define ISIF_CLSV_RESERVED_MASK                                                         (0x0000e000U)

#define ISIF_CLSV_RESERVED1_SHIFT                                                       (16U)
#define ISIF_CLSV_RESERVED1_MASK                                                        (0xffff0000U)

#define ISIF_CLHWIN0_CLHWC_SHIFT                                                        (0U)
#define ISIF_CLHWIN0_CLHWC_MASK                                                         (0x0000001fU)

#define ISIF_CLHWIN0_CLHWBS_SHIFT                                                       (5U)
#define ISIF_CLHWIN0_CLHWBS_MASK                                                        (0x00000020U)
#define ISIF_CLHWIN0_CLHWBS_NEWENUM1                                                     (0U)
#define ISIF_CLHWIN0_CLHWBS_NEWENUM2                                                     (1U)

#define ISIF_CLHWIN0_CLHWM_SHIFT                                                        (8U)
#define ISIF_CLHWIN0_CLHWM_MASK                                                         (0x00000300U)
#define ISIF_CLHWIN0_CLHWM_NEWENUM1                                                      (0U)
#define ISIF_CLHWIN0_CLHWM_NEWENUM2                                                      (1U)
#define ISIF_CLHWIN0_CLHWM_NEWENUM3                                                      (2U)
#define ISIF_CLHWIN0_CLHWM_NEWENUM4                                                      (3U)

#define ISIF_CLHWIN0_CLHWN_SHIFT                                                        (12U)
#define ISIF_CLHWIN0_CLHWN_MASK                                                         (0x00003000U)
#define ISIF_CLHWIN0_CLHWN_NEWENUM1                                                      (0U)
#define ISIF_CLHWIN0_CLHWN_NEWENUM2                                                      (1U)
#define ISIF_CLHWIN0_CLHWN_NEWENUM3                                                      (2U)
#define ISIF_CLHWIN0_CLHWN_NEWENUM4                                                      (3U)

#define ISIF_CLHWIN0_RESERVED1_SHIFT                                                    (10U)
#define ISIF_CLHWIN0_RESERVED1_MASK                                                     (0x00000c00U)

#define ISIF_CLHWIN0_RESERVED2_SHIFT                                                    (14U)
#define ISIF_CLHWIN0_RESERVED2_MASK                                                     (0x0000c000U)

#define ISIF_CLHWIN0_RESERVED3_SHIFT                                                    (16U)
#define ISIF_CLHWIN0_RESERVED3_MASK                                                     (0xffff0000U)

#define ISIF_CLHWIN0_CLHLMT_SHIFT                                                       (6U)
#define ISIF_CLHWIN0_CLHLMT_MASK                                                        (0x00000040U)
#define ISIF_CLHWIN0_CLHLMT_NEWENUM1                                                     (0U)
#define ISIF_CLHWIN0_CLHLMT_NEWENUM2                                                     (1U)

#define ISIF_CLHWIN0_RESERVED_SHIFT                                                     (7U)
#define ISIF_CLHWIN0_RESERVED_MASK                                                      (0x00000080U)

#define ISIF_CLHWIN1_CLHSH_SHIFT                                                        (0U)
#define ISIF_CLHWIN1_CLHSH_MASK                                                         (0x00001fffU)

#define ISIF_CLHWIN1_RESERVED_SHIFT                                                     (13U)
#define ISIF_CLHWIN1_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_CLHWIN1_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CLHWIN1_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CLHWIN2_CLHSV_SHIFT                                                        (0U)
#define ISIF_CLHWIN2_CLHSV_MASK                                                         (0x00001fffU)

#define ISIF_CLHWIN2_RESERVED_SHIFT                                                     (13U)
#define ISIF_CLHWIN2_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_CLHWIN2_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CLHWIN2_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CLVRV_SHIFT                                                                (0U)
#define ISIF_CLVRV_MASK                                                                 (0x00000fffU)

#define ISIF_CLVRV_RESERVED_SHIFT                                                       (12U)
#define ISIF_CLVRV_RESERVED_MASK                                                        (0x0000f000U)

#define ISIF_CLVRV_RESERVED1_SHIFT                                                      (16U)
#define ISIF_CLVRV_RESERVED1_MASK                                                       (0xffff0000U)

#define ISIF_CLVWIN0_CLVOBH_SHIFT                                                       (0U)
#define ISIF_CLVWIN0_CLVOBH_MASK                                                        (0x00000007U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM1                                                     (0U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM2                                                     (1U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM3                                                     (2U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM4                                                     (3U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM5                                                     (4U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM6                                                     (5U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM7                                                     (6U)
#define ISIF_CLVWIN0_CLVOBH_NEWENUM8                                                     (7U)

#define ISIF_CLVWIN0_CLVRVSL_SHIFT                                                      (4U)
#define ISIF_CLVWIN0_CLVRVSL_MASK                                                       (0x00000030U)
#define ISIF_CLVWIN0_CLVRVSL_NEWENUM1                                                    (0U)
#define ISIF_CLVWIN0_CLVRVSL_NEWENUM2                                                    (1U)
#define ISIF_CLVWIN0_CLVRVSL_NEWENUM3                                                    (2U)
#define ISIF_CLVWIN0_CLVRVSL_NEWENUM4                                                    (3U)

#define ISIF_CLVWIN0_CLVCOEF_SHIFT                                                      (8U)
#define ISIF_CLVWIN0_CLVCOEF_MASK                                                       (0x0000ff00U)

#define ISIF_CLVWIN0_RESERVED_SHIFT                                                     (3U)
#define ISIF_CLVWIN0_RESERVED_MASK                                                      (0x00000008U)

#define ISIF_CLVWIN0_RESERVED1_SHIFT                                                    (6U)
#define ISIF_CLVWIN0_RESERVED1_MASK                                                     (0x000000c0U)

#define ISIF_CLVWIN0_RESERVED2_SHIFT                                                    (16U)
#define ISIF_CLVWIN0_RESERVED2_MASK                                                     (0xffff0000U)

#define ISIF_CLVWIN1_CLVSH_SHIFT                                                        (0U)
#define ISIF_CLVWIN1_CLVSH_MASK                                                         (0x00001fffU)

#define ISIF_CLVWIN1_RESERVED_SHIFT                                                     (13U)
#define ISIF_CLVWIN1_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_CLVWIN1_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CLVWIN1_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CLVWIN2_CLVSV_SHIFT                                                        (0U)
#define ISIF_CLVWIN2_CLVSV_MASK                                                         (0x00001fffU)

#define ISIF_CLVWIN2_RESERVED_SHIFT                                                     (13U)
#define ISIF_CLVWIN2_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_CLVWIN2_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CLVWIN2_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_CLVWIN3_CLVOBV_SHIFT                                                       (0U)
#define ISIF_CLVWIN3_CLVOBV_MASK                                                        (0x00001fffU)

#define ISIF_CLVWIN3_RESERVED_SHIFT                                                     (13U)
#define ISIF_CLVWIN3_RESERVED_MASK                                                      (0x0000e000U)

#define ISIF_CLVWIN3_RESERVED1_SHIFT                                                    (16U)
#define ISIF_CLVWIN3_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_LSCHOFST_HOFST_SHIFT                                                       (0U)
#define ISIF_LSCHOFST_HOFST_MASK                                                        (0x00003fffU)

#define ISIF_LSCHOFST_RESERVED_SHIFT                                                    (14U)
#define ISIF_LSCHOFST_RESERVED_MASK                                                     (0x0000c000U)

#define ISIF_LSCHOFST_RESERVED1_SHIFT                                                   (16U)
#define ISIF_LSCHOFST_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_LSCVOFST_VOFST_SHIFT                                                       (0U)
#define ISIF_LSCVOFST_VOFST_MASK                                                        (0x00003fffU)

#define ISIF_LSCVOFST_RESERVED_SHIFT                                                    (14U)
#define ISIF_LSCVOFST_RESERVED_MASK                                                     (0x0000c000U)

#define ISIF_LSCVOFST_RESERVED1_SHIFT                                                   (16U)
#define ISIF_LSCVOFST_RESERVED1_MASK                                                    (0xffff0000U)

#define ISIF_LSCHVAL_HVAL_SHIFT                                                         (0U)
#define ISIF_LSCHVAL_HVAL_MASK                                                          (0x00003fffU)

#define ISIF_LSCHVAL_RESERVED_SHIFT                                                     (14U)
#define ISIF_LSCHVAL_RESERVED_MASK                                                      (0x0000c000U)

#define ISIF_LSCHVAL_RESERVED1_SHIFT                                                    (16U)
#define ISIF_LSCHVAL_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_LSCVVAL_VVAL_SHIFT                                                         (0U)
#define ISIF_LSCVVAL_VVAL_MASK                                                          (0x00003fffU)

#define ISIF_LSCVVAL_RESERVED_SHIFT                                                     (14U)
#define ISIF_LSCVVAL_RESERVED_MASK                                                      (0x0000c000U)

#define ISIF_LSCVVAL_RESERVED1_SHIFT                                                    (16U)
#define ISIF_LSCVVAL_RESERVED1_MASK                                                     (0xffff0000U)

#define ISIF_2DLSCCFG_ENABLE_SHIFT                                                      (0U)
#define ISIF_2DLSCCFG_ENABLE_MASK                                                       (0x00000001U)
#define ISIF_2DLSCCFG_ENABLE_NEWENUM1                                                    (0U)
#define ISIF_2DLSCCFG_ENABLE_NEWENUM2                                                    (1U)

#define ISIF_2DLSCCFG_GAIN_FORMAT_SHIFT                                                 (1U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_MASK                                                  (0x0000001eU)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM1                                               (0U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM2                                               (1U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM3                                               (2U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM4                                               (3U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM5                                               (4U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM6                                               (5U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM7                                               (6U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM8                                               (7U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM9                                               (8U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM10                                              (9U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM11                                              (10U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM12                                              (11U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM13                                              (12U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM14                                              (13U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM15                                              (14U)
#define ISIF_2DLSCCFG_GAIN_FORMAT_NEWENUM16                                              (15U)

#define ISIF_2DLSCCFG_BUSY_SHIFT                                                        (7U)
#define ISIF_2DLSCCFG_BUSY_MASK                                                         (0x00000080U)
#define ISIF_2DLSCCFG_BUSY_NEWENUM1                                                      (0U)
#define ISIF_2DLSCCFG_BUSY_NEWENUM2                                                      (1U)

#define ISIF_2DLSCCFG_GAIN_MODE_N_SHIFT                                                 (8U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_MASK                                                  (0x00000700U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM1                                               (0U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM2                                               (1U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM3                                               (2U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM4                                               (3U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM5                                               (4U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM6                                               (5U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM7                                               (6U)
#define ISIF_2DLSCCFG_GAIN_MODE_N_NEWENUM8                                               (7U)

#define ISIF_2DLSCCFG_GAIN_MODE_M_SHIFT                                                 (12U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_MASK                                                  (0x00007000U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM1                                               (0U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM2                                               (1U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM3                                               (2U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM4                                               (3U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM5                                               (4U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM6                                               (5U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM7                                               (6U)
#define ISIF_2DLSCCFG_GAIN_MODE_M_NEWENUM8                                               (7U)

#define ISIF_2DLSCCFG_RESERVED_SHIFT                                                    (5U)
#define ISIF_2DLSCCFG_RESERVED_MASK                                                     (0x00000020U)

#define ISIF_2DLSCCFG_RESERVED1_SHIFT                                                   (11U)
#define ISIF_2DLSCCFG_RESERVED1_MASK                                                    (0x00000800U)

#define ISIF_2DLSCCFG_RESERVED2_SHIFT                                                   (15U)
#define ISIF_2DLSCCFG_RESERVED2_MASK                                                    (0x00008000U)

#define ISIF_2DLSCCFG_RESERVED3_SHIFT                                                   (16U)
#define ISIF_2DLSCCFG_RESERVED3_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCCFG_GAIN_RANGE_SHIFT                                                  (6U)
#define ISIF_2DLSCCFG_GAIN_RANGE_MASK                                                   (0x00000040U)

#define ISIF_2DLSCOFST_OFSTEN_SHIFT                                                     (0U)
#define ISIF_2DLSCOFST_OFSTEN_MASK                                                      (0x00000001U)
#define ISIF_2DLSCOFST_OFSTEN_NEWENUM1                                                   (0U)
#define ISIF_2DLSCOFST_OFSTEN_NEWENUM2                                                   (1U)

#define ISIF_2DLSCOFST_OFSTSFT_SHIFT                                                    (4U)
#define ISIF_2DLSCOFST_OFSTSFT_MASK                                                     (0x00000070U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM1                                                  (0U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM2                                                  (1U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM3                                                  (2U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM4                                                  (3U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM5                                                  (4U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM6                                                  (5U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM7                                                  (6U)
#define ISIF_2DLSCOFST_OFSTSFT_NEWENUM8                                                  (7U)

#define ISIF_2DLSCOFST_OFSTSF_SHIFT                                                     (8U)
#define ISIF_2DLSCOFST_OFSTSF_MASK                                                      (0x0000ff00U)

#define ISIF_2DLSCOFST_RESERVED_SHIFT                                                   (1U)
#define ISIF_2DLSCOFST_RESERVED_MASK                                                    (0x0000000eU)

#define ISIF_2DLSCOFST_RESERVED1_SHIFT                                                  (7U)
#define ISIF_2DLSCOFST_RESERVED1_MASK                                                   (0x00000080U)

#define ISIF_2DLSCOFST_RESERVED2_SHIFT                                                  (16U)
#define ISIF_2DLSCOFST_RESERVED2_MASK                                                   (0xffff0000U)

#define ISIF_2DLSCINI_X_SHIFT                                                           (0U)
#define ISIF_2DLSCINI_X_MASK                                                            (0x0000007fU)

#define ISIF_2DLSCINI_Y_SHIFT                                                           (8U)
#define ISIF_2DLSCINI_Y_MASK                                                            (0x00007f00U)

#define ISIF_2DLSCINI_RESERVED_SHIFT                                                    (7U)
#define ISIF_2DLSCINI_RESERVED_MASK                                                     (0x00000080U)

#define ISIF_2DLSCINI_RESERVED1_SHIFT                                                   (15U)
#define ISIF_2DLSCINI_RESERVED1_MASK                                                    (0x00008000U)

#define ISIF_2DLSCINI_RESERVED2_SHIFT                                                   (16U)
#define ISIF_2DLSCINI_RESERVED2_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCGRBU_BASE31_16_SHIFT                                                  (0U)
#define ISIF_2DLSCGRBU_BASE31_16_MASK                                                   (0x0000ffffU)

#define ISIF_2DLSCGRBU_RESERVED1_SHIFT                                                  (16U)
#define ISIF_2DLSCGRBU_RESERVED1_MASK                                                   (0xffff0000U)

#define ISIF_2DLSCGRBL_BASE15_0_SHIFT                                                   (0U)
#define ISIF_2DLSCGRBL_BASE15_0_MASK                                                    (0x0000ffffU)

#define ISIF_2DLSCGRBL_RESERVED1_SHIFT                                                  (16U)
#define ISIF_2DLSCGRBL_RESERVED1_MASK                                                   (0xffff0000U)

#define ISIF_2DLSCGROF_OFFSET_SHIFT                                                     (0U)
#define ISIF_2DLSCGROF_OFFSET_MASK                                                      (0x0000ffffU)

#define ISIF_2DLSCGROF_RESERVED_SHIFT                                                   (16U)
#define ISIF_2DLSCGROF_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCORBU_BASE_SHIFT                                                       (0U)
#define ISIF_2DLSCORBU_BASE_MASK                                                        (0x0000ffffU)

#define ISIF_2DLSCORBU_RESERVED_SHIFT                                                   (16U)
#define ISIF_2DLSCORBU_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCORBL_BASE_SHIFT                                                       (0U)
#define ISIF_2DLSCORBL_BASE_MASK                                                        (0x0000ffffU)

#define ISIF_2DLSCORBL_RESERVED_SHIFT                                                   (16U)
#define ISIF_2DLSCORBL_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCOROF_OFFSET_SHIFT                                                     (0U)
#define ISIF_2DLSCOROF_OFFSET_MASK                                                      (0x0000ffffU)

#define ISIF_2DLSCOROF_RESERVED_SHIFT                                                   (16U)
#define ISIF_2DLSCOROF_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_2DLSCIRQEN_DONE_SHIFT                                                      (0U)
#define ISIF_2DLSCIRQEN_DONE_MASK                                                       (0x00000001U)
#define ISIF_2DLSCIRQEN_DONE_NEWENUM1                                                    (0U)
#define ISIF_2DLSCIRQEN_DONE_NEWENUM2                                                    (1U)

#define ISIF_2DLSCIRQEN_PREFETCH_ERROR_SHIFT                                            (1U)
#define ISIF_2DLSCIRQEN_PREFETCH_ERROR_MASK                                             (0x00000002U)
#define ISIF_2DLSCIRQEN_PREFETCH_ERROR_NEWENUM1                                          (0U)
#define ISIF_2DLSCIRQEN_PREFETCH_ERROR_NEWENUM2                                          (1U)

#define ISIF_2DLSCIRQEN_PREFETCH_COMPLETED_SHIFT                                        (2U)
#define ISIF_2DLSCIRQEN_PREFETCH_COMPLETED_MASK                                         (0x00000004U)
#define ISIF_2DLSCIRQEN_PREFETCH_COMPLETED_NEWENUM1                                      (0U)
#define ISIF_2DLSCIRQEN_PREFETCH_COMPLETED_NEWENUM2                                      (1U)

#define ISIF_2DLSCIRQEN_SOF_SHIFT                                                       (3U)
#define ISIF_2DLSCIRQEN_SOF_MASK                                                        (0x00000008U)
#define ISIF_2DLSCIRQEN_SOF_NEWENUM1                                                     (0U)
#define ISIF_2DLSCIRQEN_SOF_NEWENUM2                                                     (1U)

#define ISIF_2DLSCIRQEN_RESERVED_SHIFT                                                  (4U)
#define ISIF_2DLSCIRQEN_RESERVED_MASK                                                   (0x0000fff0U)

#define ISIF_2DLSCIRQEN_RESERVED1_SHIFT                                                 (16U)
#define ISIF_2DLSCIRQEN_RESERVED1_MASK                                                  (0xffff0000U)

#define ISIF_2DLSCIRQST_DONE_SHIFT                                                      (0U)
#define ISIF_2DLSCIRQST_DONE_MASK                                                       (0x00000001U)
#define ISIF_2DLSCIRQST_DONE_NEWENUM1                                                    (0U)
#define ISIF_2DLSCIRQST_DONE_NEWENUM2                                                    (1U)

#define ISIF_2DLSCIRQST_PREFETCH_ERROR_SHIFT                                            (1U)
#define ISIF_2DLSCIRQST_PREFETCH_ERROR_MASK                                             (0x00000002U)
#define ISIF_2DLSCIRQST_PREFETCH_ERROR_NEWENUM1                                          (0U)
#define ISIF_2DLSCIRQST_PREFETCH_ERROR_NEWENUM2                                          (1U)

#define ISIF_2DLSCIRQST_PREFETCH_COMPLETED_SHIFT                                        (2U)
#define ISIF_2DLSCIRQST_PREFETCH_COMPLETED_MASK                                         (0x00000004U)
#define ISIF_2DLSCIRQST_PREFETCH_COMPLETED_NEWENUM1                                      (0U)
#define ISIF_2DLSCIRQST_PREFETCH_COMPLETED_NEWENUM2                                      (1U)

#define ISIF_2DLSCIRQST_SOF_SHIFT                                                       (3U)
#define ISIF_2DLSCIRQST_SOF_MASK                                                        (0x00000008U)
#define ISIF_2DLSCIRQST_SOF_NEWENUM1                                                     (0U)
#define ISIF_2DLSCIRQST_SOF_NEWENUM2                                                     (1U)

#define ISIF_2DLSCIRQST_RESERVED_SHIFT                                                  (4U)
#define ISIF_2DLSCIRQST_RESERVED_MASK                                                   (0x0000fff0U)

#define ISIF_2DLSCIRQST_RESERVED1_SHIFT                                                 (16U)
#define ISIF_2DLSCIRQST_RESERVED1_MASK                                                  (0xffff0000U)

#define ISIF_FMTCFG_FMTEN_SHIFT                                                         (0U)
#define ISIF_FMTCFG_FMTEN_MASK                                                          (0x00000001U)
#define ISIF_FMTCFG_FMTEN_NEWENUM1                                                       (0U)
#define ISIF_FMTCFG_FMTEN_NEWENUM2                                                       (1U)

#define ISIF_FMTCFG_FMTCBL_SHIFT                                                        (1U)
#define ISIF_FMTCFG_FMTCBL_MASK                                                         (0x00000002U)
#define ISIF_FMTCFG_FMTCBL_NEWENUM1                                                      (0U)
#define ISIF_FMTCFG_FMTCBL_NEWENUM2                                                      (1U)

#define ISIF_FMTCFG_LNALT_SHIFT                                                         (2U)
#define ISIF_FMTCFG_LNALT_MASK                                                          (0x00000004U)
#define ISIF_FMTCFG_LNALT_NEWENUM1                                                       (0U)
#define ISIF_FMTCFG_LNALT_NEWENUM2                                                       (1U)

#define ISIF_FMTCFG_LNUM_SHIFT                                                          (4U)
#define ISIF_FMTCFG_LNUM_MASK                                                           (0x00000030U)
#define ISIF_FMTCFG_LNUM_NEWENUM1                                                        (0U)
#define ISIF_FMTCFG_LNUM_NEWENUM2                                                        (1U)
#define ISIF_FMTCFG_LNUM_NEWENUM3                                                        (2U)
#define ISIF_FMTCFG_LNUM_NEWENUM4                                                        (3U)

#define ISIF_FMTCFG_FMTAINC_SHIFT                                                       (8U)
#define ISIF_FMTCFG_FMTAINC_MASK                                                        (0x00000f00U)

#define ISIF_FMTCFG_RESERVED_SHIFT                                                      (3U)
#define ISIF_FMTCFG_RESERVED_MASK                                                       (0x00000008U)

#define ISIF_FMTCFG_RESERVED1_SHIFT                                                     (6U)
#define ISIF_FMTCFG_RESERVED1_MASK                                                      (0x000000c0U)

#define ISIF_FMTCFG_RESERVED2_SHIFT                                                     (12U)
#define ISIF_FMTCFG_RESERVED2_MASK                                                      (0xfffff000U)

#define ISIF_FMTPLEN_FMTPLEN0_SHIFT                                                     (0U)
#define ISIF_FMTPLEN_FMTPLEN0_MASK                                                      (0x0000000fU)

#define ISIF_FMTPLEN_FMTPLEN1_SHIFT                                                     (4U)
#define ISIF_FMTPLEN_FMTPLEN1_MASK                                                      (0x000000f0U)

#define ISIF_FMTPLEN_FMTPLEN2_SHIFT                                                     (8U)
#define ISIF_FMTPLEN_FMTPLEN2_MASK                                                      (0x00000700U)

#define ISIF_FMTPLEN_FMTPLEN3_SHIFT                                                     (12U)
#define ISIF_FMTPLEN_FMTPLEN3_MASK                                                      (0x00007000U)

#define ISIF_FMTPLEN_RESERVED_SHIFT                                                     (11U)
#define ISIF_FMTPLEN_RESERVED_MASK                                                      (0x00000800U)

#define ISIF_FMTPLEN_RESERVED1_SHIFT                                                    (15U)
#define ISIF_FMTPLEN_RESERVED1_MASK                                                     (0xffff8000U)

#define ISIF_FMTSPH_SHIFT                                                               (0U)
#define ISIF_FMTSPH_MASK                                                                (0x00001fffU)

#define ISIF_FMTSPH_RESERVED_SHIFT                                                      (13U)
#define ISIF_FMTSPH_RESERVED_MASK                                                       (0xffffe000U)

#define ISIF_FMTLNH_SHIFT                                                               (0U)
#define ISIF_FMTLNH_MASK                                                                (0x00001fffU)

#define ISIF_FMTLNH_RESERVED_SHIFT                                                      (13U)
#define ISIF_FMTLNH_RESERVED_MASK                                                       (0xffffe000U)

#define ISIF_FMTLSV_FMTSLV_SHIFT                                                        (0U)
#define ISIF_FMTLSV_FMTSLV_MASK                                                         (0x00001fffU)

#define ISIF_FMTLSV_RESERVED_SHIFT                                                      (13U)
#define ISIF_FMTLSV_RESERVED_MASK                                                       (0xffffe000U)

#define ISIF_FMTLNV_SHIFT                                                               (0U)
#define ISIF_FMTLNV_MASK                                                                (0x00007fffU)

#define ISIF_FMTLNV_RESERVED_SHIFT                                                      (15U)
#define ISIF_FMTLNV_RESERVED_MASK                                                       (0xffff8000U)

#define ISIF_FMTRLEN_SHIFT                                                              (0U)
#define ISIF_FMTRLEN_MASK                                                               (0x00001fffU)

#define ISIF_FMTRLEN_RESERVED_SHIFT                                                     (13U)
#define ISIF_FMTRLEN_RESERVED_MASK                                                      (0xffffe000U)

#define ISIF_FMTHCNT_SHIFT                                                              (0U)
#define ISIF_FMTHCNT_MASK                                                               (0x00001fffU)

#define ISIF_FMTHCNT_RESERVED_SHIFT                                                     (13U)
#define ISIF_FMTHCNT_RESERVED_MASK                                                      (0xffffe000U)

#define ISIF_FMTAPTR0_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR0_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR0_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR0_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR0_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR0_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR0_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR0_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR0_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR0_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR1_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR1_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR1_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR1_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR1_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR1_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR1_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR1_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR1_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR1_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR2_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR2_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR2_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR2_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR2_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR2_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR2_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR2_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR2_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR2_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR3_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR3_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR3_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR3_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR3_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR3_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR3_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR3_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR3_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR3_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR4_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR4_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR4_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR4_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR4_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR4_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR4_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR4_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR4_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR4_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR5_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR5_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR5_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR5_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR5_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR5_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR5_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR5_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR5_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR5_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR6_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR6_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR6_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR6_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR6_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR6_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR6_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR6_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR6_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR6_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR7_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR7_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR7_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR7_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR7_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR7_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR7_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR7_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR7_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR7_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR8_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR8_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR8_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR8_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR8_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR8_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR8_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR8_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR8_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR8_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR9_INIT_SHIFT                                                        (0U)
#define ISIF_FMTAPTR9_INIT_MASK                                                         (0x00001fffU)

#define ISIF_FMTAPTR9_LINE_SHIFT                                                        (13U)
#define ISIF_FMTAPTR9_LINE_MASK                                                         (0x00006000U)
#define ISIF_FMTAPTR9_LINE_NEWENUM1                                                      (0U)
#define ISIF_FMTAPTR9_LINE_NEWENUM2                                                      (1U)
#define ISIF_FMTAPTR9_LINE_NEWENUM3                                                      (2U)
#define ISIF_FMTAPTR9_LINE_NEWENUM4                                                      (3U)

#define ISIF_FMTAPTR9_RESERVED_SHIFT                                                    (15U)
#define ISIF_FMTAPTR9_RESERVED_MASK                                                     (0xffff8000U)

#define ISIF_FMTAPTR10_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR10_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR10_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR10_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR10_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR10_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR10_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR10_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR10_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR10_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTAPTR11_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR11_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR11_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR11_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR11_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR11_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR11_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR11_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR11_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR11_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTAPTR12_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR12_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR12_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR12_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR12_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR12_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR12_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR12_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR12_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR12_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTAPTR13_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR13_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR13_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR13_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR13_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR13_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR13_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR13_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR13_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR13_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTAPTR14_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR14_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR14_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR14_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR14_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR14_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR14_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR14_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR14_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR14_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTAPTR15_INIT_SHIFT                                                       (0U)
#define ISIF_FMTAPTR15_INIT_MASK                                                        (0x00001fffU)

#define ISIF_FMTAPTR15_LINE_SHIFT                                                       (13U)
#define ISIF_FMTAPTR15_LINE_MASK                                                        (0x00006000U)
#define ISIF_FMTAPTR15_LINE_NEWENUM1                                                     (0U)
#define ISIF_FMTAPTR15_LINE_NEWENUM2                                                     (1U)
#define ISIF_FMTAPTR15_LINE_NEWENUM3                                                     (2U)
#define ISIF_FMTAPTR15_LINE_NEWENUM4                                                     (3U)

#define ISIF_FMTAPTR15_RESERVED_SHIFT                                                   (15U)
#define ISIF_FMTAPTR15_RESERVED_MASK                                                    (0xffff8000U)

#define ISIF_FMTPGMVF0_PGM00EN_SHIFT                                                    (0U)
#define ISIF_FMTPGMVF0_PGM00EN_MASK                                                     (0x00000001U)
#define ISIF_FMTPGMVF0_PGM00EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM00EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM01EN_SHIFT                                                    (1U)
#define ISIF_FMTPGMVF0_PGM01EN_MASK                                                     (0x00000002U)
#define ISIF_FMTPGMVF0_PGM01EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM01EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM02EN_SHIFT                                                    (2U)
#define ISIF_FMTPGMVF0_PGM02EN_MASK                                                     (0x00000004U)
#define ISIF_FMTPGMVF0_PGM02EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM02EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM03EN_SHIFT                                                    (3U)
#define ISIF_FMTPGMVF0_PGM03EN_MASK                                                     (0x00000008U)
#define ISIF_FMTPGMVF0_PGM03EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM03EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM04EN_SHIFT                                                    (4U)
#define ISIF_FMTPGMVF0_PGM04EN_MASK                                                     (0x00000010U)
#define ISIF_FMTPGMVF0_PGM04EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM04EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM05EN_SHIFT                                                    (5U)
#define ISIF_FMTPGMVF0_PGM05EN_MASK                                                     (0x00000020U)
#define ISIF_FMTPGMVF0_PGM05EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM05EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM06EN_SHIFT                                                    (6U)
#define ISIF_FMTPGMVF0_PGM06EN_MASK                                                     (0x00000040U)
#define ISIF_FMTPGMVF0_PGM06EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM06EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM07EN_SHIFT                                                    (7U)
#define ISIF_FMTPGMVF0_PGM07EN_MASK                                                     (0x00000080U)
#define ISIF_FMTPGMVF0_PGM07EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM07EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM08EN_SHIFT                                                    (8U)
#define ISIF_FMTPGMVF0_PGM08EN_MASK                                                     (0x00000100U)
#define ISIF_FMTPGMVF0_PGM08EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM08EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM09EN_SHIFT                                                    (9U)
#define ISIF_FMTPGMVF0_PGM09EN_MASK                                                     (0x00000200U)
#define ISIF_FMTPGMVF0_PGM09EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM09EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM10EN_SHIFT                                                    (10U)
#define ISIF_FMTPGMVF0_PGM10EN_MASK                                                     (0x00000400U)
#define ISIF_FMTPGMVF0_PGM10EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM10EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM11EN_SHIFT                                                    (11U)
#define ISIF_FMTPGMVF0_PGM11EN_MASK                                                     (0x00000800U)
#define ISIF_FMTPGMVF0_PGM11EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM11EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM12EN_SHIFT                                                    (12U)
#define ISIF_FMTPGMVF0_PGM12EN_MASK                                                     (0x00001000U)
#define ISIF_FMTPGMVF0_PGM12EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM12EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM13EN_SHIFT                                                    (13U)
#define ISIF_FMTPGMVF0_PGM13EN_MASK                                                     (0x00002000U)
#define ISIF_FMTPGMVF0_PGM13EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM13EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM14EN_SHIFT                                                    (14U)
#define ISIF_FMTPGMVF0_PGM14EN_MASK                                                     (0x00004000U)
#define ISIF_FMTPGMVF0_PGM14EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM14EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_PGM15EN_SHIFT                                                    (15U)
#define ISIF_FMTPGMVF0_PGM15EN_MASK                                                     (0x00008000U)
#define ISIF_FMTPGMVF0_PGM15EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF0_PGM15EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF0_RESERVED_SHIFT                                                   (16U)
#define ISIF_FMTPGMVF0_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_FMTPGMVF1_PGM16EN_SHIFT                                                    (0U)
#define ISIF_FMTPGMVF1_PGM16EN_MASK                                                     (0x00000001U)
#define ISIF_FMTPGMVF1_PGM16EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM16EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM17EN_SHIFT                                                    (1U)
#define ISIF_FMTPGMVF1_PGM17EN_MASK                                                     (0x00000002U)
#define ISIF_FMTPGMVF1_PGM17EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM17EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM18EN_SHIFT                                                    (2U)
#define ISIF_FMTPGMVF1_PGM18EN_MASK                                                     (0x00000004U)
#define ISIF_FMTPGMVF1_PGM18EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM18EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM19EN_SHIFT                                                    (3U)
#define ISIF_FMTPGMVF1_PGM19EN_MASK                                                     (0x00000008U)
#define ISIF_FMTPGMVF1_PGM19EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM19EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM20EN_SHIFT                                                    (4U)
#define ISIF_FMTPGMVF1_PGM20EN_MASK                                                     (0x00000010U)
#define ISIF_FMTPGMVF1_PGM20EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM20EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM21EN_SHIFT                                                    (5U)
#define ISIF_FMTPGMVF1_PGM21EN_MASK                                                     (0x00000020U)
#define ISIF_FMTPGMVF1_PGM21EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM21EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM22EN_SHIFT                                                    (6U)
#define ISIF_FMTPGMVF1_PGM22EN_MASK                                                     (0x00000040U)
#define ISIF_FMTPGMVF1_PGM22EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM22EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM23EN_SHIFT                                                    (7U)
#define ISIF_FMTPGMVF1_PGM23EN_MASK                                                     (0x00000080U)
#define ISIF_FMTPGMVF1_PGM23EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM23EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM24EN_SHIFT                                                    (8U)
#define ISIF_FMTPGMVF1_PGM24EN_MASK                                                     (0x00000100U)
#define ISIF_FMTPGMVF1_PGM24EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM24EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM25EN_SHIFT                                                    (9U)
#define ISIF_FMTPGMVF1_PGM25EN_MASK                                                     (0x00000200U)
#define ISIF_FMTPGMVF1_PGM25EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM25EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM26EN_SHIFT                                                    (10U)
#define ISIF_FMTPGMVF1_PGM26EN_MASK                                                     (0x00000400U)
#define ISIF_FMTPGMVF1_PGM26EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM26EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM27EN_SHIFT                                                    (11U)
#define ISIF_FMTPGMVF1_PGM27EN_MASK                                                     (0x00000800U)
#define ISIF_FMTPGMVF1_PGM27EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM27EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM28EN_SHIFT                                                    (12U)
#define ISIF_FMTPGMVF1_PGM28EN_MASK                                                     (0x00001000U)
#define ISIF_FMTPGMVF1_PGM28EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM28EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM29EN_SHIFT                                                    (13U)
#define ISIF_FMTPGMVF1_PGM29EN_MASK                                                     (0x00002000U)
#define ISIF_FMTPGMVF1_PGM29EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM29EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM30EN_SHIFT                                                    (14U)
#define ISIF_FMTPGMVF1_PGM30EN_MASK                                                     (0x00004000U)
#define ISIF_FMTPGMVF1_PGM30EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM30EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_PGM31EN_SHIFT                                                    (15U)
#define ISIF_FMTPGMVF1_PGM31EN_MASK                                                     (0x00008000U)
#define ISIF_FMTPGMVF1_PGM31EN_NEWENUM1                                                  (0U)
#define ISIF_FMTPGMVF1_PGM31EN_NEWENUM2                                                  (1U)

#define ISIF_FMTPGMVF1_RESERVED_SHIFT                                                   (16U)
#define ISIF_FMTPGMVF1_RESERVED_MASK                                                    (0xffff0000U)

#define ISIF_FMTPGMAPU0_PGM0UPDT_SHIFT                                                  (0U)
#define ISIF_FMTPGMAPU0_PGM0UPDT_MASK                                                   (0x00000001U)
#define ISIF_FMTPGMAPU0_PGM0UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM0UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM1UPDT_SHIFT                                                  (1U)
#define ISIF_FMTPGMAPU0_PGM1UPDT_MASK                                                   (0x00000002U)
#define ISIF_FMTPGMAPU0_PGM1UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM1UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM2UPDT_SHIFT                                                  (2U)
#define ISIF_FMTPGMAPU0_PGM2UPDT_MASK                                                   (0x00000004U)
#define ISIF_FMTPGMAPU0_PGM2UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM2UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM3UPDT_SHIFT                                                  (3U)
#define ISIF_FMTPGMAPU0_PGM3UPDT_MASK                                                   (0x00000008U)
#define ISIF_FMTPGMAPU0_PGM3UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM3UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM4UPDT_SHIFT                                                  (4U)
#define ISIF_FMTPGMAPU0_PGM4UPDT_MASK                                                   (0x00000010U)
#define ISIF_FMTPGMAPU0_PGM4UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM4UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM5UPDT_SHIFT                                                  (5U)
#define ISIF_FMTPGMAPU0_PGM5UPDT_MASK                                                   (0x00000020U)
#define ISIF_FMTPGMAPU0_PGM5UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM5UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM6UPDT_SHIFT                                                  (6U)
#define ISIF_FMTPGMAPU0_PGM6UPDT_MASK                                                   (0x00000040U)
#define ISIF_FMTPGMAPU0_PGM6UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM6UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM7UPDT_SHIFT                                                  (7U)
#define ISIF_FMTPGMAPU0_PGM7UPDT_MASK                                                   (0x00000080U)
#define ISIF_FMTPGMAPU0_PGM7UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM7UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM8UPDT_SHIFT                                                  (8U)
#define ISIF_FMTPGMAPU0_PGM8UPDT_MASK                                                   (0x00000100U)
#define ISIF_FMTPGMAPU0_PGM8UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM8UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM9UPDT_SHIFT                                                  (9U)
#define ISIF_FMTPGMAPU0_PGM9UPDT_MASK                                                   (0x00000200U)
#define ISIF_FMTPGMAPU0_PGM9UPDT_NEWENUM1                                                (0U)
#define ISIF_FMTPGMAPU0_PGM9UPDT_NEWENUM2                                                (1U)

#define ISIF_FMTPGMAPU0_PGM10UPDT_SHIFT                                                 (10U)
#define ISIF_FMTPGMAPU0_PGM10UPDT_MASK                                                  (0x00000400U)
#define ISIF_FMTPGMAPU0_PGM10UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM10UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_PGM11UPDT_SHIFT                                                 (11U)
#define ISIF_FMTPGMAPU0_PGM11UPDT_MASK                                                  (0x00000800U)
#define ISIF_FMTPGMAPU0_PGM11UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM11UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_PGM12UPDT_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPU0_PGM12UPDT_MASK                                                  (0x00001000U)
#define ISIF_FMTPGMAPU0_PGM12UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM12UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_PGM13UPDT_SHIFT                                                 (13U)
#define ISIF_FMTPGMAPU0_PGM13UPDT_MASK                                                  (0x00002000U)
#define ISIF_FMTPGMAPU0_PGM13UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM13UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_PGM14UPDT_SHIFT                                                 (14U)
#define ISIF_FMTPGMAPU0_PGM14UPDT_MASK                                                  (0x00004000U)
#define ISIF_FMTPGMAPU0_PGM14UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM14UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_PGM15UPDT_SHIFT                                                 (15U)
#define ISIF_FMTPGMAPU0_PGM15UPDT_MASK                                                  (0x00008000U)
#define ISIF_FMTPGMAPU0_PGM15UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU0_PGM15UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU0_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPU0_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPU1_PGM16UPDT_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPU1_PGM16UPDT_MASK                                                  (0x00000001U)
#define ISIF_FMTPGMAPU1_PGM16UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM16UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM17UPDT_SHIFT                                                 (1U)
#define ISIF_FMTPGMAPU1_PGM17UPDT_MASK                                                  (0x00000002U)
#define ISIF_FMTPGMAPU1_PGM17UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM17UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM18UPDT_SHIFT                                                 (2U)
#define ISIF_FMTPGMAPU1_PGM18UPDT_MASK                                                  (0x00000004U)
#define ISIF_FMTPGMAPU1_PGM18UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM18UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM19UPDT_SHIFT                                                 (3U)
#define ISIF_FMTPGMAPU1_PGM19UPDT_MASK                                                  (0x00000008U)
#define ISIF_FMTPGMAPU1_PGM19UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM19UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM20UPDT_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPU1_PGM20UPDT_MASK                                                  (0x00000010U)
#define ISIF_FMTPGMAPU1_PGM20UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM20UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM21UPDT_SHIFT                                                 (5U)
#define ISIF_FMTPGMAPU1_PGM21UPDT_MASK                                                  (0x00000020U)
#define ISIF_FMTPGMAPU1_PGM21UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM21UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM22UPDT_SHIFT                                                 (6U)
#define ISIF_FMTPGMAPU1_PGM22UPDT_MASK                                                  (0x00000040U)
#define ISIF_FMTPGMAPU1_PGM22UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM22UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM23UPDT_SHIFT                                                 (7U)
#define ISIF_FMTPGMAPU1_PGM23UPDT_MASK                                                  (0x00000080U)
#define ISIF_FMTPGMAPU1_PGM23UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM23UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM24UPDT_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPU1_PGM24UPDT_MASK                                                  (0x00000100U)
#define ISIF_FMTPGMAPU1_PGM24UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM24UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM25UPDT_SHIFT                                                 (9U)
#define ISIF_FMTPGMAPU1_PGM25UPDT_MASK                                                  (0x00000200U)
#define ISIF_FMTPGMAPU1_PGM25UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM25UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM26UPDT_SHIFT                                                 (10U)
#define ISIF_FMTPGMAPU1_PGM26UPDT_MASK                                                  (0x00000400U)
#define ISIF_FMTPGMAPU1_PGM26UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM26UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM27UPDT_SHIFT                                                 (11U)
#define ISIF_FMTPGMAPU1_PGM27UPDT_MASK                                                  (0x00000800U)
#define ISIF_FMTPGMAPU1_PGM27UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM27UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM28UPDT_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPU1_PGM28UPDT_MASK                                                  (0x00001000U)
#define ISIF_FMTPGMAPU1_PGM28UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM28UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM29UPDT_SHIFT                                                 (13U)
#define ISIF_FMTPGMAPU1_PGM29UPDT_MASK                                                  (0x00002000U)
#define ISIF_FMTPGMAPU1_PGM29UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM29UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM30UPDT_SHIFT                                                 (14U)
#define ISIF_FMTPGMAPU1_PGM30UPDT_MASK                                                  (0x00004000U)
#define ISIF_FMTPGMAPU1_PGM30UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM30UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_PGM31UPDT_SHIFT                                                 (15U)
#define ISIF_FMTPGMAPU1_PGM31UPDT_MASK                                                  (0x00008000U)
#define ISIF_FMTPGMAPU1_PGM31UPDT_NEWENUM1                                               (0U)
#define ISIF_FMTPGMAPU1_PGM31UPDT_NEWENUM2                                               (1U)

#define ISIF_FMTPGMAPU1_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPU1_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS0_PGM0APTR_SHIFT                                                  (0U)
#define ISIF_FMTPGMAPS0_PGM0APTR_MASK                                                   (0x0000000fU)

#define ISIF_FMTPGMAPS0_PGM1APTR_SHIFT                                                  (4U)
#define ISIF_FMTPGMAPS0_PGM1APTR_MASK                                                   (0x000000f0U)

#define ISIF_FMTPGMAPS0_PGM2APTR_SHIFT                                                  (8U)
#define ISIF_FMTPGMAPS0_PGM2APTR_MASK                                                   (0x00000f00U)

#define ISIF_FMTPGMAPS0_PGM3APTR_SHIFT                                                  (12U)
#define ISIF_FMTPGMAPS0_PGM3APTR_MASK                                                   (0x0000f000U)

#define ISIF_FMTPGMAPS0_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS0_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS1_PGM4APTR_SHIFT                                                  (0U)
#define ISIF_FMTPGMAPS1_PGM4APTR_MASK                                                   (0x0000000fU)

#define ISIF_FMTPGMAPS1_PGM5APTR_SHIFT                                                  (4U)
#define ISIF_FMTPGMAPS1_PGM5APTR_MASK                                                   (0x000000f0U)

#define ISIF_FMTPGMAPS1_PGM6APTR_SHIFT                                                  (8U)
#define ISIF_FMTPGMAPS1_PGM6APTR_MASK                                                   (0x00000f00U)

#define ISIF_FMTPGMAPS1_PGM7APTR_SHIFT                                                  (12U)
#define ISIF_FMTPGMAPS1_PGM7APTR_MASK                                                   (0x0000f000U)

#define ISIF_FMTPGMAPS1_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS1_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS2_PGM8APTR_SHIFT                                                  (0U)
#define ISIF_FMTPGMAPS2_PGM8APTR_MASK                                                   (0x0000000fU)

#define ISIF_FMTPGMAPS2_PGM9APTR_SHIFT                                                  (4U)
#define ISIF_FMTPGMAPS2_PGM9APTR_MASK                                                   (0x000000f0U)

#define ISIF_FMTPGMAPS2_PGM10APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS2_PGM10APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS2_PGM11APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS2_PGM11APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS2_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS2_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS3_PGM12APTR_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPS3_PGM12APTR_MASK                                                  (0x0000000fU)

#define ISIF_FMTPGMAPS3_PGM13APTR_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPS3_PGM13APTR_MASK                                                  (0x000000f0U)

#define ISIF_FMTPGMAPS3_PGM14APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS3_PGM14APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS3_PGM15APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS3_PGM15APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS3_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS3_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS4_PGM16APTR_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPS4_PGM16APTR_MASK                                                  (0x0000000fU)

#define ISIF_FMTPGMAPS4_PGM17APTR_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPS4_PGM17APTR_MASK                                                  (0x000000f0U)

#define ISIF_FMTPGMAPS4_PGM18APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS4_PGM18APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS4_PGM19APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS4_PGM19APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS4_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS4_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS5_PGM20APTR_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPS5_PGM20APTR_MASK                                                  (0x0000000fU)

#define ISIF_FMTPGMAPS5_PGM21APTR_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPS5_PGM21APTR_MASK                                                  (0x000000f0U)

#define ISIF_FMTPGMAPS5_PGM22APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS5_PGM22APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS5_PGM23APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS5_PGM23APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS5_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS5_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS6_PGM24APTR_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPS6_PGM24APTR_MASK                                                  (0x0000000fU)

#define ISIF_FMTPGMAPS6_PGM25APTR_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPS6_PGM25APTR_MASK                                                  (0x000000f0U)

#define ISIF_FMTPGMAPS6_PGM26APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS6_PGM26APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS6_PGM27APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS6_PGM27APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS6_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS6_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_FMTPGMAPS7_PGM28APTR_SHIFT                                                 (0U)
#define ISIF_FMTPGMAPS7_PGM28APTR_MASK                                                  (0x0000000fU)

#define ISIF_FMTPGMAPS7_PGM29APTR_SHIFT                                                 (4U)
#define ISIF_FMTPGMAPS7_PGM29APTR_MASK                                                  (0x000000f0U)

#define ISIF_FMTPGMAPS7_PGM30APTR_SHIFT                                                 (8U)
#define ISIF_FMTPGMAPS7_PGM30APTR_MASK                                                  (0x00000f00U)

#define ISIF_FMTPGMAPS7_PGM31APTR_SHIFT                                                 (12U)
#define ISIF_FMTPGMAPS7_PGM31APTR_MASK                                                  (0x0000f000U)

#define ISIF_FMTPGMAPS7_RESERVED_SHIFT                                                  (16U)
#define ISIF_FMTPGMAPS7_RESERVED_MASK                                                   (0xffff0000U)

#define ISIF_CSCCTL_CSCEN_SHIFT                                                         (0U)
#define ISIF_CSCCTL_CSCEN_MASK                                                          (0x00000001U)
#define ISIF_CSCCTL_CSCEN_NEWENUM1                                                       (0U)
#define ISIF_CSCCTL_CSCEN_NEWENUM2                                                       (1U)

#define ISIF_CSCCTL_RESERVED_SHIFT                                                      (1U)
#define ISIF_CSCCTL_RESERVED_MASK                                                       (0x0000fffeU)

#define ISIF_CSCCTL_RESERVED1_SHIFT                                                     (16U)
#define ISIF_CSCCTL_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CSCM0_CSCM00_SHIFT                                                         (0U)
#define ISIF_CSCM0_CSCM00_MASK                                                          (0x000000ffU)

#define ISIF_CSCM0_CSCM01_SHIFT                                                         (8U)
#define ISIF_CSCM0_CSCM01_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM0_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM0_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM1_CSCM02_SHIFT                                                         (0U)
#define ISIF_CSCM1_CSCM02_MASK                                                          (0x000000ffU)

#define ISIF_CSCM1_CSCM03_SHIFT                                                         (8U)
#define ISIF_CSCM1_CSCM03_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM1_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM1_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM2_CSCM10_SHIFT                                                         (0U)
#define ISIF_CSCM2_CSCM10_MASK                                                          (0x000000ffU)

#define ISIF_CSCM2_CSCM11_SHIFT                                                         (8U)
#define ISIF_CSCM2_CSCM11_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM2_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM2_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM3_CSCM12_SHIFT                                                         (0U)
#define ISIF_CSCM3_CSCM12_MASK                                                          (0x000000ffU)

#define ISIF_CSCM3_CSCM13_SHIFT                                                         (8U)
#define ISIF_CSCM3_CSCM13_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM3_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM3_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM4_CSCM20_SHIFT                                                         (0U)
#define ISIF_CSCM4_CSCM20_MASK                                                          (0x000000ffU)

#define ISIF_CSCM4_CSCM21_SHIFT                                                         (8U)
#define ISIF_CSCM4_CSCM21_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM4_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM4_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM5_CSCM22_SHIFT                                                         (0U)
#define ISIF_CSCM5_CSCM22_MASK                                                          (0x000000ffU)

#define ISIF_CSCM5_CSCM23_SHIFT                                                         (8U)
#define ISIF_CSCM5_CSCM23_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM5_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM5_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM6_CSCM30_SHIFT                                                         (0U)
#define ISIF_CSCM6_CSCM30_MASK                                                          (0x000000ffU)

#define ISIF_CSCM6_CSCM31_SHIFT                                                         (8U)
#define ISIF_CSCM6_CSCM31_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM6_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM6_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_CSCM7_CSCM32_SHIFT                                                         (0U)
#define ISIF_CSCM7_CSCM32_MASK                                                          (0x000000ffU)

#define ISIF_CSCM7_CSCM33_SHIFT                                                         (8U)
#define ISIF_CSCM7_CSCM33_MASK                                                          (0x0000ff00U)

#define ISIF_CSCM7_RESERVED_SHIFT                                                       (16U)
#define ISIF_CSCM7_RESERVED_MASK                                                        (0xffff0000U)

#define ISIF_OBWIN0_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBWIN0_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBWIN0_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBWIN0_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBWIN1_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBWIN1_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBWIN1_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBWIN1_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBWIN2_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBWIN2_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBWIN2_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBWIN2_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBWIN3_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBWIN3_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBWIN3_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBWIN3_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL0_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL0_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL0_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL0_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL1_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL1_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL1_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL1_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL2_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL2_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL2_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL2_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL3_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL3_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL3_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL3_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL4_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL4_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL4_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL4_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL5_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL5_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL5_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL5_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL6_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL6_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL6_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL6_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_OBVAL7_RESERVED_SHIFT                                                      (0U)
#define ISIF_OBVAL7_RESERVED_MASK                                                       (0x0000ffffU)

#define ISIF_OBVAL7_RESERVED1_SHIFT                                                     (16U)
#define ISIF_OBVAL7_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CLKCTL_CLKEN2_SHIFT                                                        (0U)
#define ISIF_CLKCTL_CLKEN2_MASK                                                         (0x00000001U)
#define ISIF_CLKCTL_CLKEN2_NEWENUM1                                                      (0U)
#define ISIF_CLKCTL_CLKEN2_NEWENUM2                                                      (1U)

#define ISIF_CLKCTL_CLKEN1_SHIFT                                                        (1U)
#define ISIF_CLKCTL_CLKEN1_MASK                                                         (0x00000002U)
#define ISIF_CLKCTL_CLKEN1_NEWENUM1                                                      (0U)
#define ISIF_CLKCTL_CLKEN1_NEWENUM2                                                      (1U)

#define ISIF_CLKCTL_RESERVED_SHIFT                                                      (2U)
#define ISIF_CLKCTL_RESERVED_MASK                                                       (0x0000fffcU)

#define ISIF_CLKCTL_RESERVED1_SHIFT                                                     (16U)
#define ISIF_CLKCTL_RESERVED1_MASK                                                      (0xffff0000U)

#define ISIF_CBN_SHIFT                                                                  (0U)
#define ISIF_CBN_MASK                                                                   (0x00007fffU)

#define ISIF_CBN_CYN_SHIFT                                                              (16U)
#define ISIF_CBN_CYN_MASK                                                               (0x7fff0000U)

#define ISIF_CBN_RESERVED_SHIFT                                                         (15U)
#define ISIF_CBN_RESERVED_MASK                                                          (0x00008000U)

#define ISIF_CBN_RESERVED1_SHIFT                                                        (31U)
#define ISIF_CBN_RESERVED1_MASK                                                         (0x80000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_ISIF_H_ */

