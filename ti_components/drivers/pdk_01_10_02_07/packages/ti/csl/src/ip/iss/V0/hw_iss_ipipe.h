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

#ifndef HW_ISS_IPIPE_H_
#define HW_ISS_IPIPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define IPIPE_SRC_EN                                                (0x0U)
#define IPIPE_SRC_MODE                                              (0x4U)
#define IPIPE_SRC_FMT                                               (0x8U)
#define IPIPE_SRC_COL                                               (0xcU)
#define IPIPE_SRC_VPS                                               (0x10U)
#define IPIPE_SRC_VSZ                                               (0x14U)
#define IPIPE_SRC_HPS                                               (0x18U)
#define IPIPE_SRC_HSZ                                               (0x1cU)
#define IPIPE_SEL_SBU                                               (0x20U)
#define IPIPE_SRC_STA                                               (0x24U)
#define IPIPE_GCK_MMR                                               (0x28U)
#define IPIPE_GCK_PIX                                               (0x2cU)
#define IPIPE_RESERVED1                                             (0x30U)
#define IPIPE_DPC_LUT_EN                                            (0x34U)
#define IPIPE_DPC_LUT_SEL                                           (0x38U)
#define IPIPE_DPC_LUT_ADR                                           (0x3cU)
#define IPIPE_DPC_LUT_SIZ                                           (0x40U)
#define IPIPE_DPC_OTF_EN                                            (0x44U)
#define IPIPE_DPC_OTF_TYP                                           (0x48U)
#define IPIPE_DPC_OTF_2_D_THR_R                                     (0x4cU)
#define IPIPE_DPC_OTF_2_D_THR_GR                                    (0x50U)
#define IPIPE_DPC_OTF_2_D_THR_GB                                    (0x54U)
#define IPIPE_DPC_OTF_2_D_THR_B                                     (0x58U)
#define IPIPE_DPC_OTF_2_C_THR_R                                     (0x5cU)
#define IPIPE_DPC_OTF_2_C_THR_GR                                    (0x60U)
#define IPIPE_DPC_OTF_2_C_THR_GB                                    (0x64U)
#define IPIPE_DPC_OTF_2_C_THR_B                                     (0x68U)
#define IPIPE_DPC_OTF_3_SHF                                         (0x6cU)
#define IPIPE_DPC_OTF_3_D_THR                                       (0x70U)
#define IPIPE_DPC_OTF_3_D_SPL                                       (0x74U)
#define IPIPE_DPC_OTF_3_D_MIN                                       (0x78U)
#define IPIPE_DPC_OTF_3_D_MAX                                       (0x7cU)
#define IPIPE_DPC_OTF_3_C_THR                                       (0x80U)
#define IPIPE_DPC_OTF_3_C_SLP                                       (0x84U)
#define IPIPE_DPC_OTF_3_C_MIN                                       (0x88U)
#define IPIPE_DPC_OTF_3_C_MAX                                       (0x8cU)
#define IPIPE_LSC_VOFT                                              (0x90U)
#define IPIPE_LSC_VA2                                               (0x94U)
#define IPIPE_LSC_VA1                                               (0x98U)
#define IPIPE_LSC_VS                                                (0x9cU)
#define IPIPE_LSC_HOFT                                              (0xa0U)
#define IPIPE_LSC_HA2                                               (0xa4U)
#define IPIPE_LSC_HA1                                               (0xa8U)
#define IPIPE_LSC_HS                                                (0xacU)
#define IPIPE_LSC_GAN_R                                             (0xb0U)
#define IPIPE_LSC_GAN_GR                                            (0xb4U)
#define IPIPE_LSC_GAN_GB                                            (0xb8U)
#define IPIPE_LSC_GAN_B                                             (0xbcU)
#define IPIPE_LSC_OFT_R                                             (0xc0U)
#define IPIPE_LSC_OFT_GR                                            (0xc4U)
#define IPIPE_LSC_OFT_GB                                            (0xc8U)
#define IPIPE_LSC_OFT_B                                             (0xccU)
#define IPIPE_LSC_SHF                                               (0xd0U)
#define IPIPE_LSC_MAX                                               (0xd4U)
#define IPIPE_D2F_1ST_EN                                            (0xd8U)
#define IPIPE_D2F_1ST_TYP                                           (0xdcU)
#define IPIPE_D2F_1ST_THR_00                                        (0xe0U)
#define IPIPE_D2F_1ST_THR_01                                        (0xe4U)
#define IPIPE_D2F_1ST_THR_02                                        (0xe8U)
#define IPIPE_D2F_1ST_THR_03                                        (0xecU)
#define IPIPE_D2F_1ST_THR_04                                        (0xf0U)
#define IPIPE_D2F_1ST_THR_05                                        (0xf4U)
#define IPIPE_D2F_1ST_THR_06                                        (0xf8U)
#define IPIPE_D2F_1ST_THR_07                                        (0xfcU)
#define IPIPE_D2F_1ST_STR_00                                        (0x100U)
#define IPIPE_D2F_1ST_STR_01                                        (0x104U)
#define IPIPE_D2F_1ST_STR_02                                        (0x108U)
#define IPIPE_D2F_1ST_STR_03                                        (0x10cU)
#define IPIPE_D2F_1ST_STR_04                                        (0x110U)
#define IPIPE_D2F_1ST_STR_05                                        (0x114U)
#define IPIPE_D2F_1ST_STR_06                                        (0x118U)
#define IPIPE_D2F_1ST_STR_07                                        (0x11cU)
#define IPIPE_D2F_1ST_SPR_00                                        (0x120U)
#define IPIPE_D2F_1ST_SPR_01                                        (0x124U)
#define IPIPE_D2F_1ST_SPR_02                                        (0x128U)
#define IPIPE_D2F_1ST_SPR_03                                        (0x12cU)
#define IPIPE_D2F_1ST_SPR_04                                        (0x130U)
#define IPIPE_D2F_1ST_SPR_05                                        (0x134U)
#define IPIPE_D2F_1ST_SPR_06                                        (0x138U)
#define IPIPE_D2F_1ST_SPR_07                                        (0x13cU)
#define IPIPE_D2F_1ST_EDG_MIN                                       (0x140U)
#define IPIPE_D2F_1ST_EDG_MAX                                       (0x144U)
#define IPIPE_D2F_2ND_EN                                            (0x148U)
#define IPIPE_D2F_2ND_TYP                                           (0x14cU)
#define IPIPE_D2F_2ND_THR00                                         (0x150U)
#define IPIPE_D2F_2ND_THR01                                         (0x154U)
#define IPIPE_D2F_2ND_THR02                                         (0x158U)
#define IPIPE_D2F_2ND_THR03                                         (0x15cU)
#define IPIPE_D2F_2ND_THR04                                         (0x160U)
#define IPIPE_D2F_2ND_THR05                                         (0x164U)
#define IPIPE_D2F_2ND_THR06                                         (0x168U)
#define IPIPE_D2F_2ND_THR07                                         (0x16cU)
#define IPIPE_D2F_2ND_STR_00                                        (0x170U)
#define IPIPE_D2F_2ND_STR_01                                        (0x174U)
#define IPIPE_D2F_2ND_STR_02                                        (0x178U)
#define IPIPE_D2F_2ND_STR_03                                        (0x17cU)
#define IPIPE_D2F_2ND_STR_04                                        (0x180U)
#define IPIPE_D2F_2ND_STR_05                                        (0x184U)
#define IPIPE_D2F_2ND_STR_06                                        (0x188U)
#define IPIPE_D2F_2ND_STR_07                                        (0x18cU)
#define IPIPE_D2F_2ND_SPR_00                                        (0x190U)
#define IPIPE_D2F_2ND_SPR_01                                        (0x194U)
#define IPIPE_D2F_2ND_SPR_02                                        (0x198U)
#define IPIPE_D2F_2ND_SPR_03                                        (0x19cU)
#define IPIPE_D2F_2ND_SPR_04                                        (0x1a0U)
#define IPIPE_D2F_2ND_SPR_05                                        (0x1a4U)
#define IPIPE_D2F_2ND_SPR_06                                        (0x1a8U)
#define IPIPE_D2F_2ND_SPR_07                                        (0x1acU)
#define IPIPE_D2F_2ND_EDG_MIN                                       (0x1b0U)
#define IPIPE_D2F_2ND_EDG_MAX                                       (0x1b4U)
#define IPIPE_GIC_EN                                                (0x1b8U)
#define IPIPE_GIC_TYP                                               (0x1bcU)
#define IPIPE_GIC_GAN                                               (0x1c0U)
#define IPIPE_GIC_NFGAIN                                            (0x1c4U)
#define IPIPE_GIC_THR                                               (0x1c8U)
#define IPIPE_GIC_SLP                                               (0x1ccU)
#define IPIPE_WB2_OFT_R                                             (0x1d0U)
#define IPIPE_WB2_OFT_GR                                            (0x1d4U)
#define IPIPE_WB2_OFT_GB                                            (0x1d8U)
#define IPIPE_WB2_OFT_B                                             (0x1dcU)
#define IPIPE_WB2_WGN_R                                             (0x1e0U)
#define IPIPE_WB2_WGN_GR                                            (0x1e4U)
#define IPIPE_WB2_WGN_GB                                            (0x1e8U)
#define IPIPE_WB2_WGN_B                                             (0x1ecU)
#define IPIPE_CFA_MODE                                              (0x1f0U)
#define IPIPE_CFA_2DIR_HPF_THR                                      (0x1f4U)
#define IPIPE_CFA_2DIR_HPF_SLP                                      (0x1f8U)
#define IPIPE_CFA_2DIR_MIX_THR                                      (0x1fcU)
#define IPIPE_CFA_2DIR_MIX_SLP                                      (0x200U)
#define IPIPE_CFA_2DIR_DIR_TRH                                      (0x204U)
#define IPIPE_CFA_2DIR_DIR_SLP                                      (0x208U)
#define IPIPE_CFA_2DIR_NDWT                                         (0x20cU)
#define IPIPE_CFA_MONO_HUE_FRA                                      (0x210U)
#define IPIPE_CFA_MONO_EDG_THR                                      (0x214U)
#define IPIPE_CFA_MONO_THR_MIN                                      (0x218U)
#define IPIPE_CFA_MONO_THR_SLP                                      (0x21cU)
#define IPIPE_CFA_MONO_SLP_MIN                                      (0x220U)
#define IPIPE_CFA_MONO_SLP                                          (0x224U)
#define IPIPE_CFA_MONO_LPWT                                         (0x228U)
#define IPIPE_RGB1_MUL_RR                                           (0x22cU)
#define IPIPE_RGB1_MUL_GR                                           (0x230U)
#define IPIPE_RGB1_MUL_BR                                           (0x234U)
#define IPIPE_RGB1_MUL_RG                                           (0x238U)
#define IPIPE_RGB1_MUL_GG                                           (0x23cU)
#define IPIPE_RGB1_MUL_BG                                           (0x240U)
#define IPIPE_RGB1_MUL_RB                                           (0x244U)
#define IPIPE_RGB1_MUL_GB                                           (0x248U)
#define IPIPE_RGB1_MUL_BB                                           (0x24cU)
#define IPIPE_RGB1_OFT_OR                                           (0x250U)
#define IPIPE_RGB1_OFT_OG                                           (0x254U)
#define IPIPE_RGB1_OFT_OB                                           (0x258U)
#define IPIPE_GMM_CFG                                               (0x25cU)
#define IPIPE_RGB2_MUL_RR                                           (0x260U)
#define IPIPE_RGB2_MUL_GR                                           (0x264U)
#define IPIPE_RGB2_MUL_BR                                           (0x268U)
#define IPIPE_RGB2_MUL_RG                                           (0x26cU)
#define IPIPE_RGB2_MUL_GG                                           (0x270U)
#define IPIPE_RGB2_MUL_BG                                           (0x274U)
#define IPIPE_RGB2_MUL_RB                                           (0x278U)
#define IPIPE_RGB2_MUL_GB                                           (0x27cU)
#define IPIPE_RGB2_MUL_BB                                           (0x280U)
#define IPIPE_RGB2_OFT_OR                                           (0x284U)
#define IPIPE_RGB2_OFT_OG                                           (0x288U)
#define IPIPE_RGB2_OFT_OB                                           (0x28cU)
#define IPIPE_3DLUT_EN                                              (0x290U)
#define IPIPE_YUV_ADJ                                               (0x294U)
#define IPIPE_YUV_MUL_RY                                            (0x298U)
#define IPIPE_YUV_MUL_GY                                            (0x29cU)
#define IPIPE_YUV_MUL_BY                                            (0x2a0U)
#define IPIPE_YUV_MUL_RCB                                           (0x2a4U)
#define IPIPE_YUV_MUL_GCB                                           (0x2a8U)
#define IPIPE_YUV_MUL_BCB                                           (0x2acU)
#define IPIPE_YUV_MUL_RCR                                           (0x2b0U)
#define IPIPE_YUV_MUL_GCR                                           (0x2b4U)
#define IPIPE_YUV_MUL_BCR                                           (0x2b8U)
#define IPIPE_YUV_OFT_Y                                             (0x2bcU)
#define IPIPE_YUV_OFT_CB                                            (0x2c0U)
#define IPIPE_YUV_OFT_CR                                            (0x2c4U)
#define IPIPE_YUV_PHS                                               (0x2c8U)
#define IPIPE_GBCE_EN                                               (0x2ccU)
#define IPIPE_GBCE_TYP                                              (0x2d0U)
#define IPIPE_YEE_EN                                                (0x2d4U)
#define IPIPE_YEE_TYP                                               (0x2d8U)
#define IPIPE_YEE_SHF                                               (0x2dcU)
#define IPIPE_YEE_MUL_00                                            (0x2e0U)
#define IPIPE_YEE_MUL_01                                            (0x2e4U)
#define IPIPE_YEE_MUL_02                                            (0x2e8U)
#define IPIPE_YEE_MUL_10                                            (0x2ecU)
#define IPIPE_YEE_MUL_11                                            (0x2f0U)
#define IPIPE_YEE_MUL_12                                            (0x2f4U)
#define IPIPE_YEE_MUL_20                                            (0x2f8U)
#define IPIPE_YEE_MUL_21                                            (0x2fcU)
#define IPIPE_YEE_MUL_22                                            (0x300U)
#define IPIPE_YEE_THR                                               (0x304U)
#define IPIPE_YEE_E_GAN                                             (0x308U)
#define IPIPE_YEE_E_THR_1                                           (0x30cU)
#define IPIPE_YEE_E_THR_2                                           (0x310U)
#define IPIPE_YEE_G_GAN                                             (0x314U)
#define IPIPE_YEE_G_OFT                                             (0x318U)
#define IPIPE_CAR_EN                                                (0x31cU)
#define IPIPE_CAR_TYP                                               (0x320U)
#define IPIPE_CAR_SW                                                (0x324U)
#define IPIPE_CAR_HPF_TYP                                           (0x328U)
#define IPIPE_CAR_HPF_SHF                                           (0x32cU)
#define IPIPE_CAR_HPF_THR                                           (0x330U)
#define IPIPE_CAR_GN1_GAN                                           (0x334U)
#define IPIPE_CAR_GN1_SHF                                           (0x338U)
#define IPIPE_CAR_GN1_MIN                                           (0x33cU)
#define IPIPE_CAR_GN2_GAN                                           (0x340U)
#define IPIPE_CAR_GN2_SHF                                           (0x344U)
#define IPIPE_CAR_GN2_MIN                                           (0x348U)
#define IPIPE_CGS_EN                                                (0x34cU)
#define IPIPE_CGS_GN1_L_THR                                         (0x350U)
#define IPIPE_CGS_GN1_L_GAIN                                        (0x354U)
#define IPIPE_CGS_GN1_L_SHF                                         (0x358U)
#define IPIPE_CGS_GN1_L_MIN                                         (0x35cU)
#define IPIPE_CGS_GN1_H_THR                                         (0x360U)
#define IPIPE_CGS_GN1_H_GAIN                                        (0x364U)
#define IPIPE_CGS_GN1_H_SHF                                         (0x368U)
#define IPIPE_CGS_GN1_H_MIN                                         (0x36cU)
#define IPIPE_CGS_GN2_L_THR                                         (0x370U)
#define IPIPE_CGS_GN2_L_GAIN                                        (0x374U)
#define IPIPE_CGS_GN2_L_SHF                                         (0x378U)
#define IPIPE_CGS_GN2_L_MIN                                         (0x37cU)
#define IPIPE_BOX_EN                                                (0x380U)
#define IPIPE_BOX_MODE                                              (0x384U)
#define IPIPE_BOX_TYP                                               (0x388U)
#define IPIPE_BOX_SHF                                               (0x38cU)
#define IPIPE_BOX_SDR_SAD_H                                         (0x390U)
#define IPIPE_BOX_SDR_SAD_L                                         (0x394U)
#define IPIPE_RESERVED2                                             (0x398U)
#define IPIPE_HST_EN                                                (0x39cU)
#define IPIPE_HST_MODE                                              (0x3a0U)
#define IPIPE_HST_SEL                                               (0x3a4U)
#define IPIPE_HST_PARA                                              (0x3a8U)
#define IPIPE_HST_0_VPS                                             (0x3acU)
#define IPIPE_HST_0_VSZ                                             (0x3b0U)
#define IPIPE_HST_0_HPS                                             (0x3b4U)
#define IPIPE_HST_0_HSZ                                             (0x3b8U)
#define IPIPE_HST_1_VPS                                             (0x3bcU)
#define IPIPE_HST_1_VSZ                                             (0x3c0U)
#define IPIPE_HST_1_HPS                                             (0x3c4U)
#define IPIPE_HST_1_HSZ                                             (0x3c8U)
#define IPIPE_HST_2_VPS                                             (0x3ccU)
#define IPIPE_HST_2_VSZ                                             (0x3d0U)
#define IPIPE_HST_2_HPS                                             (0x3d4U)
#define IPIPE_HST_2_HSZ                                             (0x3d8U)
#define IPIPE_HST_3_VPS                                             (0x3dcU)
#define IPIPE_HST_3_VSZ                                             (0x3e0U)
#define IPIPE_HST_3_HPS                                             (0x3e4U)
#define IPIPE_HST_3_HSZ                                             (0x3e8U)
#define IPIPE_HST_TBL                                               (0x3ecU)
#define IPIPE_HST_MUL_R                                             (0x3f0U)
#define IPIPE_HST_MUL_GR                                            (0x3f4U)
#define IPIPE_HST_MUL_GB                                            (0x3f8U)
#define IPIPE_HST_MUL_B                                             (0x3fcU)
#define IPIPE_BSC_EN                                                (0x400U)
#define IPIPE_BSC_MODE                                              (0x404U)
#define IPIPE_BSC_TYP                                               (0x408U)
#define IPIPE_BSC_ROW_VCT                                           (0x40cU)
#define IPIPE_BSC_ROW_SHF                                           (0x410U)
#define IPIPE_BSC_ROW_VPOS                                          (0x414U)
#define IPIPE_BSC_ROW_VNUM                                          (0x418U)
#define IPIPE_BSC_ROW_VSKIP                                         (0x41cU)
#define IPIPE_BSC_ROW_HPOS                                          (0x420U)
#define IPIPE_BSC_ROW_HNUM                                          (0x424U)
#define IPIPE_BSC_ROW_HSKIP                                         (0x428U)
#define IPIPE_BSC_COL_VCT                                           (0x42cU)
#define IPIPE_BSC_COL_SHF                                           (0x430U)
#define IPIPE_BSC_COL_VPOS                                          (0x434U)
#define IPIPE_BSC_COL_VNUM                                          (0x438U)
#define IPIPE_BSC_COL_VSKIP                                         (0x43cU)
#define IPIPE_BSC_COL_HPOS                                          (0x440U)
#define IPIPE_BSC_COL_HNUM                                          (0x444U)
#define IPIPE_BSC_COL_HSKIP                                         (0x448U)
#define IPIPE_YUV_INP_OFST_Y                                        (0x44cU)
#define IPIPE_YUV_INP_OFST_CB                                       (0x450U)
#define IPIPE_YUV_INP_OFST_CR                                       (0x454U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define IPIPE_SRC_EN_SHIFT                                                              (0U)
#define IPIPE_SRC_EN_MASK                                                               (0x00000001U)
#define IPIPE_SRC_EN_NEWENUM1                                                            (0U)
#define IPIPE_SRC_EN_NEWENUM2                                                            (1U)

#define IPIPE_SRC_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_SRC_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_SRC_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_SRC_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_SRC_MODE_OST_SHIFT                                                        (0U)
#define IPIPE_SRC_MODE_OST_MASK                                                         (0x00000001U)
#define IPIPE_SRC_MODE_OST_NEWENUM1                                                      (0U)
#define IPIPE_SRC_MODE_OST_NEWENUM2                                                      (1U)

#define IPIPE_SRC_MODE_WRT_SHIFT                                                        (1U)
#define IPIPE_SRC_MODE_WRT_MASK                                                         (0x00000002U)
#define IPIPE_SRC_MODE_WRT_NEWENUM1                                                      (0U)
#define IPIPE_SRC_MODE_WRT_NEWENUM2                                                      (1U)

#define IPIPE_SRC_MODE_RESERVED_SHIFT                                                   (2U)
#define IPIPE_SRC_MODE_RESERVED_MASK                                                    (0x0000fffcU)

#define IPIPE_SRC_MODE_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_SRC_MODE_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_SRC_FMT_SHIFT                                                             (0U)
#define IPIPE_SRC_FMT_MASK                                                              (0x00000003U)
#define IPIPE_SRC_FMT_NEWENUM1                                                           (0U)
#define IPIPE_SRC_FMT_NEWENUM2                                                           (1U)
#define IPIPE_SRC_FMT_NEWENUM3                                                           (2U)
#define IPIPE_SRC_FMT_NEWENUM4                                                           (3U)

#define IPIPE_SRC_FMT_FMT2_SHIFT                                                        (2U)
#define IPIPE_SRC_FMT_FMT2_MASK                                                         (0x0000000cU)
#define IPIPE_SRC_FMT_FMT2_YUV_PROCESS                                                   (0U)
#define IPIPE_SRC_FMT_FMT2_YUV444_MODE                                                   (1U)
#define IPIPE_SRC_FMT_FMT2_RGB_MODE                                                      (2U)
#define IPIPE_SRC_FMT_FMT2_RESERVED                                                      (3U)

#define IPIPE_SRC_FMT_FMT3_SHIFT                                                        (4U)
#define IPIPE_SRC_FMT_FMT3_MASK                                                         (0x00000010U)
#define IPIPE_SRC_FMT_FMT3_COSITED                                                       (0U)
#define IPIPE_SRC_FMT_FMT3_CENTERED                                                      (1U)

#define IPIPE_SRC_FMT_RESERVED_SHIFT                                                    (5U)
#define IPIPE_SRC_FMT_RESERVED_MASK                                                     (0xffffffe0U)

#define IPIPE_SRC_COL_EE_SHIFT                                                          (0U)
#define IPIPE_SRC_COL_EE_MASK                                                           (0x00000003U)
#define IPIPE_SRC_COL_EE_NEWENUM1                                                       (0x00000000U)
#define IPIPE_SRC_COL_EE_NEWENUM2                                                       (0x00000001U)
#define IPIPE_SRC_COL_EE_NEWENUM3                                                       (0x00000002U)
#define IPIPE_SRC_COL_EE_NEWENUM4                                                       (0x00000003U)

#define IPIPE_SRC_COL_EO_SHIFT                                                          (2U)
#define IPIPE_SRC_COL_EO_MASK                                                           (0x0000000cU)
#define IPIPE_SRC_COL_EO_NEWENUM1                                                       (0x00000000U)
#define IPIPE_SRC_COL_EO_NEWENUM2                                                       (0x00000004U)
#define IPIPE_SRC_COL_EO_NEWENUM3                                                       (0x00000008U)
#define IPIPE_SRC_COL_EO_NEWENUM4                                                       (0x0000000CU)

#define IPIPE_SRC_COL_OE_SHIFT                                                          (4U)
#define IPIPE_SRC_COL_OE_MASK                                                           (0x00000030U)
#define IPIPE_SRC_COL_OE_NEWENUM1                                                       (0x00000000U)
#define IPIPE_SRC_COL_OE_NEWENUM2                                                       (0x00000010U)
#define IPIPE_SRC_COL_OE_NEWENUM3                                                       (0x00000020U)
#define IPIPE_SRC_COL_OE_NEWENUM4                                                       (0x00000030U)

#define IPIPE_SRC_COL_OO_SHIFT                                                          (6U)
#define IPIPE_SRC_COL_OO_MASK                                                           (0x000000c0U)
#define IPIPE_SRC_COL_OO_NEWENUM1                                                       (0x00000000U)
#define IPIPE_SRC_COL_OO_NEWENUM2                                                       (0x00000040U)
#define IPIPE_SRC_COL_OO_NEWENUM3                                                       (0x00000080U)
#define IPIPE_SRC_COL_OO_NEWENUM4                                                       (0x000000C0U)

#define IPIPE_SRC_COL_RESERVED_SHIFT                                                    (8U)
#define IPIPE_SRC_COL_RESERVED_MASK                                                     (0x0000ff00U)

#define IPIPE_SRC_COL_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_SRC_COL_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_SRC_VPS_VAL_SHIFT                                                         (0U)
#define IPIPE_SRC_VPS_VAL_MASK                                                          (0x0000ffffU)

#define IPIPE_SRC_VPS_RESERVED_SHIFT                                                    (16U)
#define IPIPE_SRC_VPS_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPE_SRC_VSZ_VAL_SHIFT                                                         (0U)
#define IPIPE_SRC_VSZ_VAL_MASK                                                          (0x00001fffU)

#define IPIPE_SRC_VSZ_RESERVED_SHIFT                                                    (13U)
#define IPIPE_SRC_VSZ_RESERVED_MASK                                                     (0x0000e000U)

#define IPIPE_SRC_VSZ_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_SRC_VSZ_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_SRC_HPS_VAL_SHIFT                                                         (0U)
#define IPIPE_SRC_HPS_VAL_MASK                                                          (0x0000ffffU)

#define IPIPE_SRC_HPS_RESERVED_SHIFT                                                    (16U)
#define IPIPE_SRC_HPS_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPE_SRC_HSZ_VAL_SHIFT                                                         (1U)
#define IPIPE_SRC_HSZ_VAL_MASK                                                          (0x00001ffeU)

#define IPIPE_SRC_HSZ_VAL_0_SHIFT                                                       (0U)
#define IPIPE_SRC_HSZ_VAL_0_MASK                                                        (0x00000001U)

#define IPIPE_SRC_HSZ_RESERVED_SHIFT                                                    (13U)
#define IPIPE_SRC_HSZ_RESERVED_MASK                                                     (0xffffe000U)

#define IPIPE_SEL_SBU_EDOF_SHIFT                                                        (0U)
#define IPIPE_SEL_SBU_EDOF_MASK                                                         (0x00000001U)
#define IPIPE_SEL_SBU_EDOF_INT                                                           (0U)
#define IPIPE_SEL_SBU_EDOF_EXT                                                           (1U)

#define IPIPE_SEL_SBU_RESERVED_SHIFT                                                    (1U)
#define IPIPE_SEL_SBU_RESERVED_MASK                                                     (0x0000fffeU)

#define IPIPE_SEL_SBU_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_SEL_SBU_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_SRC_STA_VAL0_SHIFT                                                        (0U)
#define IPIPE_SRC_STA_VAL0_MASK                                                         (0x00000001U)

#define IPIPE_SRC_STA_VAL1_SHIFT                                                        (1U)
#define IPIPE_SRC_STA_VAL1_MASK                                                         (0x00000002U)

#define IPIPE_SRC_STA_VAL2_SHIFT                                                        (2U)
#define IPIPE_SRC_STA_VAL2_MASK                                                         (0x00000004U)

#define IPIPE_SRC_STA_VAL3_SHIFT                                                        (3U)
#define IPIPE_SRC_STA_VAL3_MASK                                                         (0x00000008U)

#define IPIPE_SRC_STA_VAL4_SHIFT                                                        (4U)
#define IPIPE_SRC_STA_VAL4_MASK                                                         (0x00000010U)

#define IPIPE_SRC_STA_RESERVED_SHIFT                                                    (5U)
#define IPIPE_SRC_STA_RESERVED_MASK                                                     (0x0000ffe0U)

#define IPIPE_SRC_STA_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_SRC_STA_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GCK_MMR_REG_SHIFT                                                         (0U)
#define IPIPE_GCK_MMR_REG_MASK                                                          (0x00000001U)
#define IPIPE_GCK_MMR_REG_NEWENUM1                                                       (0U)
#define IPIPE_GCK_MMR_REG_NEWENUM2                                                       (1U)

#define IPIPE_GCK_MMR_RESERVED_SHIFT                                                    (1U)
#define IPIPE_GCK_MMR_RESERVED_MASK                                                     (0x0000fffeU)

#define IPIPE_GCK_MMR_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GCK_MMR_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GCK_PIX_G0_SHIFT                                                          (0U)
#define IPIPE_GCK_PIX_G0_MASK                                                           (0x00000001U)
#define IPIPE_GCK_PIX_G0_NEWENUM1                                                        (0U)
#define IPIPE_GCK_PIX_G0_NEWENUM2                                                        (1U)

#define IPIPE_GCK_PIX_G1_SHIFT                                                          (1U)
#define IPIPE_GCK_PIX_G1_MASK                                                           (0x00000002U)
#define IPIPE_GCK_PIX_G1_NEWENUM1                                                        (0U)
#define IPIPE_GCK_PIX_G1_NEWENUM2                                                        (1U)

#define IPIPE_GCK_PIX_G2_SHIFT                                                          (2U)
#define IPIPE_GCK_PIX_G2_MASK                                                           (0x00000004U)
#define IPIPE_GCK_PIX_G2_NEWENUM1                                                        (0U)
#define IPIPE_GCK_PIX_G2_NEWENUM2                                                        (1U)

#define IPIPE_GCK_PIX_G3_SHIFT                                                          (3U)
#define IPIPE_GCK_PIX_G3_MASK                                                           (0x00000008U)
#define IPIPE_GCK_PIX_G3_NEWENUM1                                                        (0U)
#define IPIPE_GCK_PIX_G3_NEWENUM2                                                        (1U)

#define IPIPE_GCK_PIX_RESERVED_SHIFT                                                    (4U)
#define IPIPE_GCK_PIX_RESERVED_MASK                                                     (0x0000fff0U)

#define IPIPE_GCK_PIX_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GCK_PIX_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_RESERVED1_RESERVED_SHIFT                                                  (0U)
#define IPIPE_RESERVED1_RESERVED_MASK                                                   (0x0000ffffU)

#define IPIPE_RESERVED1_SHIFT                                                           (16U)
#define IPIPE_RESERVED1_MASK                                                            (0xffff0000U)

#define IPIPE_DPC_LUT_EN_SHIFT                                                          (0U)
#define IPIPE_DPC_LUT_EN_MASK                                                           (0x00000001U)
#define IPIPE_DPC_LUT_EN_NEWENUM1                                                        (0U)
#define IPIPE_DPC_LUT_EN_NEWENUM2                                                        (1U)

#define IPIPE_DPC_LUT_EN_RESERVED_SHIFT                                                 (1U)
#define IPIPE_DPC_LUT_EN_RESERVED_MASK                                                  (0x0000fffeU)

#define IPIPE_DPC_LUT_EN_RESERVED1_SHIFT                                                (16U)
#define IPIPE_DPC_LUT_EN_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_DPC_LUT_SEL_DOT_SHIFT                                                     (0U)
#define IPIPE_DPC_LUT_SEL_DOT_MASK                                                      (0x00000001U)
#define IPIPE_DPC_LUT_SEL_DOT_NEWENUM1                                                   (0U)
#define IPIPE_DPC_LUT_SEL_DOT_NEWENUM2                                                   (1U)

#define IPIPE_DPC_LUT_SEL_TBL_SHIFT                                                     (1U)
#define IPIPE_DPC_LUT_SEL_TBL_MASK                                                      (0x00000002U)
#define IPIPE_DPC_LUT_SEL_TBL_NEWENUM1                                                   (0U)
#define IPIPE_DPC_LUT_SEL_TBL_NEWENUM2                                                   (1U)

#define IPIPE_DPC_LUT_SEL_RESERVED_SHIFT                                                (2U)
#define IPIPE_DPC_LUT_SEL_RESERVED_MASK                                                 (0x0000fffcU)

#define IPIPE_DPC_LUT_SEL_RESERVED1_SHIFT                                               (16U)
#define IPIPE_DPC_LUT_SEL_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_DPC_LUT_ADR_SHIFT                                                         (0U)
#define IPIPE_DPC_LUT_ADR_MASK                                                          (0x000003ffU)

#define IPIPE_DPC_LUT_ADR_RESERVED_SHIFT                                                (10U)
#define IPIPE_DPC_LUT_ADR_RESERVED_MASK                                                 (0x0000fc00U)

#define IPIPE_DPC_LUT_ADR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_DPC_LUT_ADR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_DPC_LUT_SIZ_SHIFT                                                         (0U)
#define IPIPE_DPC_LUT_SIZ_MASK                                                          (0x000003ffU)

#define IPIPE_DPC_LUT_SIZ_RESERVED_SHIFT                                                (10U)
#define IPIPE_DPC_LUT_SIZ_RESERVED_MASK                                                 (0x0000fc00U)

#define IPIPE_DPC_LUT_SIZ_RESERVED1_SHIFT                                               (16U)
#define IPIPE_DPC_LUT_SIZ_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_DPC_OTF_EN_SHIFT                                                          (0U)
#define IPIPE_DPC_OTF_EN_MASK                                                           (0x00000001U)
#define IPIPE_DPC_OTF_EN_NEWENUM1                                                        (0U)
#define IPIPE_DPC_OTF_EN_NEWENUM2                                                        (1U)

#define IPIPE_DPC_OTF_EN_RESERVED_SHIFT                                                 (1U)
#define IPIPE_DPC_OTF_EN_RESERVED_MASK                                                  (0x0000fffeU)

#define IPIPE_DPC_OTF_EN_RESERVED1_SHIFT                                                (16U)
#define IPIPE_DPC_OTF_EN_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_DPC_OTF_TYP_ALG_SHIFT                                                     (0U)
#define IPIPE_DPC_OTF_TYP_ALG_MASK                                                      (0x00000001U)
#define IPIPE_DPC_OTF_TYP_ALG_NEWENUM1                                                   (0U)
#define IPIPE_DPC_OTF_TYP_ALG_NEWENUM2                                                   (1U)

#define IPIPE_DPC_OTF_TYP_SHIFT                                                         (1U)
#define IPIPE_DPC_OTF_TYP_MASK                                                          (0x00000002U)
#define IPIPE_DPC_OTF_TYP_NEWENUM1                                                       (0U)
#define IPIPE_DPC_OTF_TYP_NEWENUM2                                                       (1U)

#define IPIPE_DPC_OTF_TYP_RESERVED_SHIFT                                                (2U)
#define IPIPE_DPC_OTF_TYP_RESERVED_MASK                                                 (0x0000fffcU)

#define IPIPE_DPC_OTF_TYP_RESERVED1_SHIFT                                               (16U)
#define IPIPE_DPC_OTF_TYP_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_DPC_OTF_2_D_THR_R_VAL_SHIFT                                               (0U)
#define IPIPE_DPC_OTF_2_D_THR_R_VAL_MASK                                                (0x00000fffU)

#define IPIPE_DPC_OTF_2_D_THR_R_RESERVED_SHIFT                                          (12U)
#define IPIPE_DPC_OTF_2_D_THR_R_RESERVED_MASK                                           (0x0000f000U)

#define IPIPE_DPC_OTF_2_D_THR_R_RESERVED1_SHIFT                                         (16U)
#define IPIPE_DPC_OTF_2_D_THR_R_RESERVED1_MASK                                          (0xffff0000U)

#define IPIPE_DPC_OTF_2_D_THR_GR_VAL_SHIFT                                              (0U)
#define IPIPE_DPC_OTF_2_D_THR_GR_VAL_MASK                                               (0x00000fffU)

#define IPIPE_DPC_OTF_2_D_THR_GR_RESERVED_SHIFT                                         (12U)
#define IPIPE_DPC_OTF_2_D_THR_GR_RESERVED_MASK                                          (0x0000f000U)

#define IPIPE_DPC_OTF_2_D_THR_GR_RESERVED1_SHIFT                                        (16U)
#define IPIPE_DPC_OTF_2_D_THR_GR_RESERVED1_MASK                                         (0xffff0000U)

#define IPIPE_DPC_OTF_2_D_THR_GB_VAL_SHIFT                                              (0U)
#define IPIPE_DPC_OTF_2_D_THR_GB_VAL_MASK                                               (0x00000fffU)

#define IPIPE_DPC_OTF_2_D_THR_GB_RESERVED_SHIFT                                         (12U)
#define IPIPE_DPC_OTF_2_D_THR_GB_RESERVED_MASK                                          (0x0000f000U)

#define IPIPE_DPC_OTF_2_D_THR_GB_RESERVED1_SHIFT                                        (16U)
#define IPIPE_DPC_OTF_2_D_THR_GB_RESERVED1_MASK                                         (0xffff0000U)

#define IPIPE_DPC_OTF_2_D_THR_B_VAL_SHIFT                                               (0U)
#define IPIPE_DPC_OTF_2_D_THR_B_VAL_MASK                                                (0x00000fffU)

#define IPIPE_DPC_OTF_2_D_THR_B_RESERVED_SHIFT                                          (12U)
#define IPIPE_DPC_OTF_2_D_THR_B_RESERVED_MASK                                           (0x0000f000U)

#define IPIPE_DPC_OTF_2_D_THR_B_RESERVED1_SHIFT                                         (16U)
#define IPIPE_DPC_OTF_2_D_THR_B_RESERVED1_MASK                                          (0xffff0000U)

#define IPIPE_DPC_OTF_2_C_THR_R_VAL_SHIFT                                               (0U)
#define IPIPE_DPC_OTF_2_C_THR_R_VAL_MASK                                                (0x00000fffU)

#define IPIPE_DPC_OTF_2_C_THR_R_RESERVED_SHIFT                                          (12U)
#define IPIPE_DPC_OTF_2_C_THR_R_RESERVED_MASK                                           (0x0000f000U)

#define IPIPE_DPC_OTF_2_C_THR_R_RESERVED1_SHIFT                                         (16U)
#define IPIPE_DPC_OTF_2_C_THR_R_RESERVED1_MASK                                          (0xffff0000U)

#define IPIPE_DPC_OTF_2_C_THR_GR_VAL_SHIFT                                              (0U)
#define IPIPE_DPC_OTF_2_C_THR_GR_VAL_MASK                                               (0x00000fffU)

#define IPIPE_DPC_OTF_2_C_THR_GR_RESERVED_SHIFT                                         (12U)
#define IPIPE_DPC_OTF_2_C_THR_GR_RESERVED_MASK                                          (0x0000f000U)

#define IPIPE_DPC_OTF_2_C_THR_GR_RESERVED1_SHIFT                                        (16U)
#define IPIPE_DPC_OTF_2_C_THR_GR_RESERVED1_MASK                                         (0xffff0000U)

#define IPIPE_DPC_OTF_2_C_THR_GB_VAL_SHIFT                                              (0U)
#define IPIPE_DPC_OTF_2_C_THR_GB_VAL_MASK                                               (0x00000fffU)

#define IPIPE_DPC_OTF_2_C_THR_GB_RESERVED_SHIFT                                         (12U)
#define IPIPE_DPC_OTF_2_C_THR_GB_RESERVED_MASK                                          (0x0000f000U)

#define IPIPE_DPC_OTF_2_C_THR_GB_RESERVED1_SHIFT                                        (16U)
#define IPIPE_DPC_OTF_2_C_THR_GB_RESERVED1_MASK                                         (0xffff0000U)

#define IPIPE_DPC_OTF_2_C_THR_B_VAL_SHIFT                                               (0U)
#define IPIPE_DPC_OTF_2_C_THR_B_VAL_MASK                                                (0x00000fffU)

#define IPIPE_DPC_OTF_2_C_THR_B_RESERVED_SHIFT                                          (12U)
#define IPIPE_DPC_OTF_2_C_THR_B_RESERVED_MASK                                           (0x0000f000U)

#define IPIPE_DPC_OTF_2_C_THR_B_RESERVED1_SHIFT                                         (16U)
#define IPIPE_DPC_OTF_2_C_THR_B_RESERVED1_MASK                                          (0xffff0000U)

#define IPIPE_DPC_OTF_3_SHF_SHIFT                                                       (0U)
#define IPIPE_DPC_OTF_3_SHF_MASK                                                        (0x00000003U)

#define IPIPE_DPC_OTF_3_SHF_RESERVED_SHIFT                                              (2U)
#define IPIPE_DPC_OTF_3_SHF_RESERVED_MASK                                               (0x0000fffcU)

#define IPIPE_DPC_OTF_3_SHF_RESERVED1_SHIFT                                             (16U)
#define IPIPE_DPC_OTF_3_SHF_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_DPC_OTF_3_D_THR_VAL_SHIFT                                                 (6U)
#define IPIPE_DPC_OTF_3_D_THR_VAL_MASK                                                  (0x00000fc0U)

#define IPIPE_DPC_OTF_3_D_THR_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_D_THR_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_D_THR_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_D_THR_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_D_THR_VAL_RESERVED_SHIFT                                        (0U)
#define IPIPE_DPC_OTF_3_D_THR_VAL_RESERVED_MASK                                         (0x0000003fU)

#define IPIPE_DPC_OTF_3_D_SPL_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_D_SPL_VAL_MASK                                                  (0x0000003fU)

#define IPIPE_DPC_OTF_3_D_SPL_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_D_SPL_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_D_SPL_RESERVED_SHIFT                                            (6U)
#define IPIPE_DPC_OTF_3_D_SPL_RESERVED_MASK                                             (0x0000ffc0U)

#define IPIPE_DPC_OTF_3_D_MIN_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_D_MIN_VAL_MASK                                                  (0x00000fffU)

#define IPIPE_DPC_OTF_3_D_MIN_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_D_MIN_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_D_MIN_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_D_MIN_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_D_MAX_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_D_MAX_VAL_MASK                                                  (0x00000fffU)

#define IPIPE_DPC_OTF_3_D_MAX_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_D_MAX_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_D_MAX_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_D_MAX_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_C_THR_VAL_RESERVED_SHIFT                                        (0U)
#define IPIPE_DPC_OTF_3_C_THR_VAL_RESERVED_MASK                                         (0x0000003fU)

#define IPIPE_DPC_OTF_3_C_THR_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_C_THR_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_C_THR_VAL_SHIFT                                                 (6U)
#define IPIPE_DPC_OTF_3_C_THR_VAL_MASK                                                  (0x00000fc0U)

#define IPIPE_DPC_OTF_3_C_THR_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_C_THR_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_C_SLP_VAL_RESERVED_SHIFT                                        (6U)
#define IPIPE_DPC_OTF_3_C_SLP_VAL_RESERVED_MASK                                         (0x00000fc0U)

#define IPIPE_DPC_OTF_3_C_SLP_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_C_SLP_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_C_SLP_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_C_SLP_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_C_SLP_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_C_SLP_VAL_MASK                                                  (0x0000003fU)

#define IPIPE_DPC_OTF_3_C_MIN_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_C_MIN_VAL_MASK                                                  (0x00000fffU)

#define IPIPE_DPC_OTF_3_C_MIN_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_C_MIN_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_C_MIN_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_C_MIN_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_DPC_OTF_3_C_MAX_VAL_SHIFT                                                 (0U)
#define IPIPE_DPC_OTF_3_C_MAX_VAL_MASK                                                  (0x00000fffU)

#define IPIPE_DPC_OTF_3_C_MAX_RESERVED_SHIFT                                            (12U)
#define IPIPE_DPC_OTF_3_C_MAX_RESERVED_MASK                                             (0x0000f000U)

#define IPIPE_DPC_OTF_3_C_MAX_RESERVED1_SHIFT                                           (16U)
#define IPIPE_DPC_OTF_3_C_MAX_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_LSC_VOFT_SHIFT                                                            (0U)
#define IPIPE_LSC_VOFT_MASK                                                             (0x00001fffU)

#define IPIPE_LSC_VOFT_RESERVED_SHIFT                                                   (13U)
#define IPIPE_LSC_VOFT_RESERVED_MASK                                                    (0x0000e000U)

#define IPIPE_LSC_VOFT_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_LSC_VOFT_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_LSC_VA2_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_VA2_VAL_MASK                                                          (0x00001fffU)

#define IPIPE_LSC_VA2_RESERVED_SHIFT                                                    (13U)
#define IPIPE_LSC_VA2_RESERVED_MASK                                                     (0x0000e000U)

#define IPIPE_LSC_VA2_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_VA2_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_LSC_VA1_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_VA1_VAL_MASK                                                          (0x00001fffU)

#define IPIPE_LSC_VA1_RESERVED_SHIFT                                                    (13U)
#define IPIPE_LSC_VA1_RESERVED_MASK                                                     (0x0000e000U)

#define IPIPE_LSC_VA1_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_VA1_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_LSC_VS_VS1_SHIFT                                                          (0U)
#define IPIPE_LSC_VS_VS1_MASK                                                           (0x0000000fU)

#define IPIPE_LSC_VS_VS2_SHIFT                                                          (4U)
#define IPIPE_LSC_VS_VS2_MASK                                                           (0x000000f0U)

#define IPIPE_LSC_VS_RESERVED_SHIFT                                                     (8U)
#define IPIPE_LSC_VS_RESERVED_MASK                                                      (0x0000ff00U)

#define IPIPE_LSC_VS_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_LSC_VS_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_LSC_HOFT_VAL_SHIFT                                                        (0U)
#define IPIPE_LSC_HOFT_VAL_MASK                                                         (0x00001fffU)

#define IPIPE_LSC_HOFT_RESERVED_SHIFT                                                   (13U)
#define IPIPE_LSC_HOFT_RESERVED_MASK                                                    (0x0000e000U)

#define IPIPE_LSC_HOFT_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_LSC_HOFT_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_LSC_HA2_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_HA2_VAL_MASK                                                          (0x00001fffU)

#define IPIPE_LSC_HA2_RESERVED_SHIFT                                                    (13U)
#define IPIPE_LSC_HA2_RESERVED_MASK                                                     (0x0000e000U)

#define IPIPE_LSC_HA2_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_HA2_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_LSC_HA1_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_HA1_VAL_MASK                                                          (0x00001fffU)

#define IPIPE_LSC_HA1_RESERVED_SHIFT                                                    (13U)
#define IPIPE_LSC_HA1_RESERVED_MASK                                                     (0x0000e000U)

#define IPIPE_LSC_HA1_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_HA1_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_LSC_HS_HS1_SHIFT                                                          (0U)
#define IPIPE_LSC_HS_HS1_MASK                                                           (0x0000000fU)

#define IPIPE_LSC_HS_HS2_SHIFT                                                          (4U)
#define IPIPE_LSC_HS_HS2_MASK                                                           (0x000000f0U)

#define IPIPE_LSC_HS_RESERVED_SHIFT                                                     (8U)
#define IPIPE_LSC_HS_RESERVED_MASK                                                      (0x0000ff00U)

#define IPIPE_LSC_HS_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_LSC_HS_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_LSC_GAN_R_VAL_SHIFT                                                       (0U)
#define IPIPE_LSC_GAN_R_VAL_MASK                                                        (0x000000ffU)

#define IPIPE_LSC_GAN_R_RESERVED_SHIFT                                                  (8U)
#define IPIPE_LSC_GAN_R_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_LSC_GAN_R_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_LSC_GAN_R_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_LSC_GAN_GR_VAL_SHIFT                                                      (0U)
#define IPIPE_LSC_GAN_GR_VAL_MASK                                                       (0x000000ffU)

#define IPIPE_LSC_GAN_GR_RESERVED_SHIFT                                                 (8U)
#define IPIPE_LSC_GAN_GR_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_LSC_GAN_GR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_LSC_GAN_GR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_LSC_GAN_GB_VAL_SHIFT                                                      (0U)
#define IPIPE_LSC_GAN_GB_VAL_MASK                                                       (0x000000ffU)

#define IPIPE_LSC_GAN_GB_RESERVED_SHIFT                                                 (8U)
#define IPIPE_LSC_GAN_GB_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_LSC_GAN_GB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_LSC_GAN_GB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_LSC_GAN_B_VAL_SHIFT                                                       (0U)
#define IPIPE_LSC_GAN_B_VAL_MASK                                                        (0x000000ffU)

#define IPIPE_LSC_GAN_B_RESERVED_SHIFT                                                  (8U)
#define IPIPE_LSC_GAN_B_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_LSC_GAN_B_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_LSC_GAN_B_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_LSC_OFT_R_VAL_SHIFT                                                       (0U)
#define IPIPE_LSC_OFT_R_VAL_MASK                                                        (0x000000ffU)

#define IPIPE_LSC_OFT_R_RESERVED_SHIFT                                                  (8U)
#define IPIPE_LSC_OFT_R_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_LSC_OFT_R_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_LSC_OFT_R_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_LSC_OFT_GR_VAL_SHIFT                                                      (0U)
#define IPIPE_LSC_OFT_GR_VAL_MASK                                                       (0x000000ffU)

#define IPIPE_LSC_OFT_GR_RESERVED_SHIFT                                                 (8U)
#define IPIPE_LSC_OFT_GR_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_LSC_OFT_GR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_LSC_OFT_GR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_LSC_OFT_GB_VAL_SHIFT                                                      (0U)
#define IPIPE_LSC_OFT_GB_VAL_MASK                                                       (0x000000ffU)

#define IPIPE_LSC_OFT_GB_RESERVED_SHIFT                                                 (8U)
#define IPIPE_LSC_OFT_GB_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_LSC_OFT_GB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_LSC_OFT_GB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_LSC_OFT_B_VAL_SHIFT                                                       (0U)
#define IPIPE_LSC_OFT_B_VAL_MASK                                                        (0x000000ffU)

#define IPIPE_LSC_OFT_B_RESERVED_SHIFT                                                  (8U)
#define IPIPE_LSC_OFT_B_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_LSC_OFT_B_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_LSC_OFT_B_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_LSC_SHF_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_SHF_VAL_MASK                                                          (0x0000000fU)

#define IPIPE_LSC_SHF_RESERVED_SHIFT                                                    (4U)
#define IPIPE_LSC_SHF_RESERVED_MASK                                                     (0x0000fff0U)

#define IPIPE_LSC_SHF_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_SHF_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_LSC_MAX_VAL_SHIFT                                                         (0U)
#define IPIPE_LSC_MAX_VAL_MASK                                                          (0x000001ffU)

#define IPIPE_LSC_MAX_RESERVED_SHIFT                                                    (9U)
#define IPIPE_LSC_MAX_RESERVED_MASK                                                     (0x0000fe00U)

#define IPIPE_LSC_MAX_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_LSC_MAX_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_D2F_1ST_EN_SHIFT                                                          (0U)
#define IPIPE_D2F_1ST_EN_MASK                                                           (0x00000001U)
#define IPIPE_D2F_1ST_EN_NEWENUM1                                                        (0U)
#define IPIPE_D2F_1ST_EN_NEWENUM2                                                        (1U)

#define IPIPE_D2F_1ST_EN_RESERVED_SHIFT                                                 (1U)
#define IPIPE_D2F_1ST_EN_RESERVED_MASK                                                  (0x0000fffeU)

#define IPIPE_D2F_1ST_EN_RESERVED1_SHIFT                                                (16U)
#define IPIPE_D2F_1ST_EN_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_D2F_1ST_TYP_SPR_SHIFT                                                     (0U)
#define IPIPE_D2F_1ST_TYP_SPR_MASK                                                      (0x0000001fU)

#define IPIPE_D2F_1ST_TYP_SHF_SHIFT                                                     (5U)
#define IPIPE_D2F_1ST_TYP_SHF_MASK                                                      (0x00000060U)

#define IPIPE_D2F_1ST_TYP_SHIFT                                                         (7U)
#define IPIPE_D2F_1ST_TYP_MASK                                                          (0x00000080U)
#define IPIPE_D2F_1ST_TYP_NEWENUM1                                                       (0U)
#define IPIPE_D2F_1ST_TYP_NEWENUM2                                                       (1U)

#define IPIPE_D2F_1ST_TYP_LSC_SHIFT                                                     (8U)
#define IPIPE_D2F_1ST_TYP_LSC_MASK                                                      (0x00000100U)
#define IPIPE_D2F_1ST_TYP_LSC_NEWENUM1                                                   (0U)
#define IPIPE_D2F_1ST_TYP_LSC_NEWENUM2                                                   (1U)

#define IPIPE_D2F_1ST_TYP_SEL_SHIFT                                                     (9U)
#define IPIPE_D2F_1ST_TYP_SEL_MASK                                                      (0x00000200U)
#define IPIPE_D2F_1ST_TYP_SEL_NEWENUM1                                                   (0U)
#define IPIPE_D2F_1ST_TYP_SEL_NEWENUM2                                                   (1U)

#define IPIPE_D2F_1ST_TYP_RESERVED1_SHIFT                                               (16U)
#define IPIPE_D2F_1ST_TYP_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_D2F_1ST_TYP_RESERVED_SHIFT                                                (10U)
#define IPIPE_D2F_1ST_TYP_RESERVED_MASK                                                 (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_00_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_00_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_00_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_00_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_00_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_00_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_01_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_01_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_01_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_01_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_01_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_01_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_02_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_02_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_02_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_02_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_02_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_02_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_03_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_03_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_03_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_03_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_03_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_03_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_04_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_04_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_04_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_04_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_04_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_04_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_05_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_05_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_05_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_05_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_05_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_05_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_06_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_06_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_06_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_06_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_06_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_06_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_THR_07_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_THR_07_VAL_MASK                                                   (0x000003ffU)

#define IPIPE_D2F_1ST_THR_07_RESERVED_SHIFT                                             (10U)
#define IPIPE_D2F_1ST_THR_07_RESERVED_MASK                                              (0x0000fc00U)

#define IPIPE_D2F_1ST_THR_07_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_THR_07_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_00_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_00_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_00_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_00_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_00_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_00_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_01_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_01_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_01_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_01_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_01_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_01_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_02_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_02_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_02_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_02_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_02_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_02_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_03_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_03_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_03_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_03_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_03_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_03_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_04_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_04_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_04_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_04_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_04_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_04_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_05_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_05_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_05_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_05_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_05_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_05_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_06_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_06_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_06_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_06_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_06_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_06_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_STR_07_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_STR_07_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_STR_07_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_STR_07_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_STR_07_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_STR_07_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_00_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_00_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_00_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_00_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_00_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_00_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_01_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_01_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_01_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_01_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_01_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_01_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_02_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_02_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_02_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_02_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_02_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_02_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_03_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_03_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_03_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_03_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_03_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_03_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_04_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_04_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_04_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_04_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_04_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_04_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_05_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_05_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_05_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_05_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_05_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_05_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_06_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_06_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_06_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_06_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_06_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_06_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_SPR_07_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_1ST_SPR_07_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_1ST_SPR_07_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_1ST_SPR_07_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_1ST_SPR_07_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_1ST_SPR_07_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_1ST_EDG_MIN_VAL_SHIFT                                                 (0U)
#define IPIPE_D2F_1ST_EDG_MIN_VAL_MASK                                                  (0x000007ffU)

#define IPIPE_D2F_1ST_EDG_MIN_RESERVED_SHIFT                                            (11U)
#define IPIPE_D2F_1ST_EDG_MIN_RESERVED_MASK                                             (0x0000f800U)

#define IPIPE_D2F_1ST_EDG_MIN_RESERVED1_SHIFT                                           (16U)
#define IPIPE_D2F_1ST_EDG_MIN_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_D2F_1ST_EDG_MAX_VAL_SHIFT                                                 (0U)
#define IPIPE_D2F_1ST_EDG_MAX_VAL_MASK                                                  (0x000007ffU)

#define IPIPE_D2F_1ST_EDG_MAX_RESERVED_SHIFT                                            (11U)
#define IPIPE_D2F_1ST_EDG_MAX_RESERVED_MASK                                             (0x0000f800U)

#define IPIPE_D2F_1ST_EDG_MAX_RESERVED1_SHIFT                                           (16U)
#define IPIPE_D2F_1ST_EDG_MAX_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_D2F_2ND_EN_SHIFT                                                          (0U)
#define IPIPE_D2F_2ND_EN_MASK                                                           (0x00000001U)
#define IPIPE_D2F_2ND_EN_NEWENUM1                                                        (0U)
#define IPIPE_D2F_2ND_EN_NEWENUM2                                                        (1U)

#define IPIPE_D2F_2ND_EN_RESERVED_SHIFT                                                 (1U)
#define IPIPE_D2F_2ND_EN_RESERVED_MASK                                                  (0x0000fffeU)

#define IPIPE_D2F_2ND_EN_RESERVED1_SHIFT                                                (16U)
#define IPIPE_D2F_2ND_EN_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_D2F_2ND_TYP_SPR_SHIFT                                                     (0U)
#define IPIPE_D2F_2ND_TYP_SPR_MASK                                                      (0x0000001fU)

#define IPIPE_D2F_2ND_TYP_SHF_SHIFT                                                     (5U)
#define IPIPE_D2F_2ND_TYP_SHF_MASK                                                      (0x00000060U)

#define IPIPE_D2F_2ND_TYP_SHIFT                                                         (7U)
#define IPIPE_D2F_2ND_TYP_MASK                                                          (0x00000080U)
#define IPIPE_D2F_2ND_TYP_NEWENUM1                                                       (0U)
#define IPIPE_D2F_2ND_TYP_NEWENUM2                                                       (1U)

#define IPIPE_D2F_2ND_TYP_LSC_SHIFT                                                     (8U)
#define IPIPE_D2F_2ND_TYP_LSC_MASK                                                      (0x00000100U)
#define IPIPE_D2F_2ND_TYP_LSC_NEWENUM1                                                   (0U)
#define IPIPE_D2F_2ND_TYP_LSC_NEWENUM2                                                   (1U)

#define IPIPE_D2F_2ND_TYP_SEL_SHIFT                                                     (9U)
#define IPIPE_D2F_2ND_TYP_SEL_MASK                                                      (0x00000200U)
#define IPIPE_D2F_2ND_TYP_SEL_NEWENUM1                                                   (0U)
#define IPIPE_D2F_2ND_TYP_SEL_NEWENUM2                                                   (1U)

#define IPIPE_D2F_2ND_TYP_RESERVED1_SHIFT                                               (16U)
#define IPIPE_D2F_2ND_TYP_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_D2F_2ND_TYP_RESERVED_SHIFT                                                (10U)
#define IPIPE_D2F_2ND_TYP_RESERVED_MASK                                                 (0x0000fc00U)

#define IPIPE_D2F_2ND_THR00_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR00_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR00_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR00_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR00_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR00_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR01_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR01_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR01_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR01_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR01_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR01_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR02_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR02_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR02_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR02_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR02_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR02_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR03_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR03_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR03_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR03_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR03_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR03_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR04_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR04_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR04_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR04_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR04_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR04_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR05_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR05_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR05_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR05_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR05_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR05_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR06_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR06_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR06_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR06_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR06_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR06_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_THR07_VAL_SHIFT                                                   (0U)
#define IPIPE_D2F_2ND_THR07_VAL_MASK                                                    (0x000003ffU)

#define IPIPE_D2F_2ND_THR07_RESERVED_SHIFT                                              (10U)
#define IPIPE_D2F_2ND_THR07_RESERVED_MASK                                               (0x0000fc00U)

#define IPIPE_D2F_2ND_THR07_RESERVED1_SHIFT                                             (16U)
#define IPIPE_D2F_2ND_THR07_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_D2F_2ND_STR_00_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_00_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_00_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_00_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_00_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_00_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_01_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_01_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_01_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_01_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_01_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_01_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_02_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_02_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_02_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_02_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_02_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_02_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_03_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_03_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_03_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_03_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_03_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_03_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_04_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_04_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_04_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_04_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_04_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_04_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_05_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_05_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_05_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_05_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_05_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_05_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_06_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_06_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_06_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_06_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_06_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_06_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_STR_07_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_STR_07_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_STR_07_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_STR_07_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_STR_07_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_STR_07_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_00_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_00_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_00_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_00_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_00_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_00_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_01_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_01_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_01_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_01_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_01_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_01_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_02_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_02_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_02_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_02_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_02_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_02_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_03_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_03_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_03_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_03_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_03_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_03_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_04_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_04_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_04_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_04_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_04_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_04_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_05_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_05_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_05_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_05_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_05_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_05_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_06_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_06_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_06_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_06_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_06_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_06_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_SPR_07_VAL_SHIFT                                                  (0U)
#define IPIPE_D2F_2ND_SPR_07_VAL_MASK                                                   (0x0000001fU)

#define IPIPE_D2F_2ND_SPR_07_RESERVED1_SHIFT                                            (16U)
#define IPIPE_D2F_2ND_SPR_07_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_D2F_2ND_SPR_07_RESERVED_SHIFT                                             (5U)
#define IPIPE_D2F_2ND_SPR_07_RESERVED_MASK                                              (0x0000ffe0U)

#define IPIPE_D2F_2ND_EDG_MIN_VAL_SHIFT                                                 (0U)
#define IPIPE_D2F_2ND_EDG_MIN_VAL_MASK                                                  (0x000007ffU)

#define IPIPE_D2F_2ND_EDG_MIN_RESERVED_SHIFT                                            (11U)
#define IPIPE_D2F_2ND_EDG_MIN_RESERVED_MASK                                             (0x0000f800U)

#define IPIPE_D2F_2ND_EDG_MIN_RESERVED1_SHIFT                                           (16U)
#define IPIPE_D2F_2ND_EDG_MIN_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_D2F_2ND_EDG_MAX_VAL_SHIFT                                                 (0U)
#define IPIPE_D2F_2ND_EDG_MAX_VAL_MASK                                                  (0x000007ffU)

#define IPIPE_D2F_2ND_EDG_MAX_RESERVED_SHIFT                                            (11U)
#define IPIPE_D2F_2ND_EDG_MAX_RESERVED_MASK                                             (0x0000f800U)

#define IPIPE_D2F_2ND_EDG_MAX_RESERVED1_SHIFT                                           (16U)
#define IPIPE_D2F_2ND_EDG_MAX_RESERVED1_MASK                                            (0xffff0000U)

#define IPIPE_GIC_EN_SHIFT                                                              (0U)
#define IPIPE_GIC_EN_MASK                                                               (0x00000001U)
#define IPIPE_GIC_EN_NEWENUM1                                                            (0U)
#define IPIPE_GIC_EN_NEWENUM2                                                            (1U)

#define IPIPE_GIC_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_GIC_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_GIC_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_GIC_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_GIC_TYP_SHIFT                                                             (0U)
#define IPIPE_GIC_TYP_MASK                                                              (0x00000001U)
#define IPIPE_GIC_TYP_NEWENUM1                                                           (0U)
#define IPIPE_GIC_TYP_NEWENUM2                                                           (1U)

#define IPIPE_GIC_TYP_SEL_SHIFT                                                         (1U)
#define IPIPE_GIC_TYP_SEL_MASK                                                          (0x00000002U)
#define IPIPE_GIC_TYP_SEL_NEWENUM1                                                       (0U)
#define IPIPE_GIC_TYP_SEL_NEWENUM2                                                       (1U)

#define IPIPE_GIC_TYP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GIC_TYP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GIC_TYP_LSC_SHIFT                                                         (2U)
#define IPIPE_GIC_TYP_LSC_MASK                                                          (0x00000004U)
#define IPIPE_GIC_TYP_LSC_NEWENUM1                                                       (0U)
#define IPIPE_GIC_TYP_LSC_NEWENUM2                                                       (1U)

#define IPIPE_GIC_TYP_RESERVED_SHIFT                                                    (3U)
#define IPIPE_GIC_TYP_RESERVED_MASK                                                     (0x0000fff8U)

#define IPIPE_GIC_GAN_VAL_SHIFT                                                         (0U)
#define IPIPE_GIC_GAN_VAL_MASK                                                          (0x000000ffU)

#define IPIPE_GIC_GAN_RESERVED_SHIFT                                                    (8U)
#define IPIPE_GIC_GAN_RESERVED_MASK                                                     (0x0000ff00U)

#define IPIPE_GIC_GAN_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GIC_GAN_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GIC_NFGAIN_VAL_SHIFT                                                      (0U)
#define IPIPE_GIC_NFGAIN_VAL_MASK                                                       (0x000000ffU)

#define IPIPE_GIC_NFGAIN_RESERVED_SHIFT                                                 (8U)
#define IPIPE_GIC_NFGAIN_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_GIC_NFGAIN_RESERVED1_SHIFT                                                (16U)
#define IPIPE_GIC_NFGAIN_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_GIC_THR_VAL_SHIFT                                                         (0U)
#define IPIPE_GIC_THR_VAL_MASK                                                          (0x00000fffU)

#define IPIPE_GIC_THR_RESERVED_SHIFT                                                    (12U)
#define IPIPE_GIC_THR_RESERVED_MASK                                                     (0x0000f000U)

#define IPIPE_GIC_THR_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GIC_THR_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GIC_SLP_VAL_SHIFT                                                         (0U)
#define IPIPE_GIC_SLP_VAL_MASK                                                          (0x00000fffU)

#define IPIPE_GIC_SLP_RESERVED_SHIFT                                                    (12U)
#define IPIPE_GIC_SLP_RESERVED_MASK                                                     (0x0000f000U)

#define IPIPE_GIC_SLP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GIC_SLP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_WB2_OFT_R_VAL_SHIFT                                                       (0U)
#define IPIPE_WB2_OFT_R_VAL_MASK                                                        (0x00000fffU)

#define IPIPE_WB2_OFT_R_RESERVED_SHIFT                                                  (12U)
#define IPIPE_WB2_OFT_R_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPE_WB2_OFT_R_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_WB2_OFT_R_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_WB2_OFT_GR_VAL_SHIFT                                                      (0U)
#define IPIPE_WB2_OFT_GR_VAL_MASK                                                       (0x00000fffU)

#define IPIPE_WB2_OFT_GR_RESERVED_SHIFT                                                 (12U)
#define IPIPE_WB2_OFT_GR_RESERVED_MASK                                                  (0x0000f000U)

#define IPIPE_WB2_OFT_GR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_WB2_OFT_GR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_WB2_OFT_GB_VAL_SHIFT                                                      (0U)
#define IPIPE_WB2_OFT_GB_VAL_MASK                                                       (0x00000fffU)

#define IPIPE_WB2_OFT_GB_RESERVED_SHIFT                                                 (12U)
#define IPIPE_WB2_OFT_GB_RESERVED_MASK                                                  (0x0000f000U)

#define IPIPE_WB2_OFT_GB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_WB2_OFT_GB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_WB2_OFT_B_VAL_SHIFT                                                       (0U)
#define IPIPE_WB2_OFT_B_VAL_MASK                                                        (0x00000fffU)

#define IPIPE_WB2_OFT_B_RESERVED_SHIFT                                                  (12U)
#define IPIPE_WB2_OFT_B_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPE_WB2_OFT_B_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_WB2_OFT_B_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_WB2_WGN_R_VAL_SHIFT                                                       (0U)
#define IPIPE_WB2_WGN_R_VAL_MASK                                                        (0x00001fffU)

#define IPIPE_WB2_WGN_R_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_WB2_WGN_R_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_WB2_WGN_R_RESERVED_SHIFT                                                  (13U)
#define IPIPE_WB2_WGN_R_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_WB2_WGN_GR_VAL_SHIFT                                                      (0U)
#define IPIPE_WB2_WGN_GR_VAL_MASK                                                       (0x00001fffU)

#define IPIPE_WB2_WGN_GR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_WB2_WGN_GR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_WB2_WGN_GR_RESERVED_SHIFT                                                 (13U)
#define IPIPE_WB2_WGN_GR_RESERVED_MASK                                                  (0x0000e000U)

#define IPIPE_WB2_WGN_GB_VAL_SHIFT                                                      (0U)
#define IPIPE_WB2_WGN_GB_VAL_MASK                                                       (0x00001fffU)

#define IPIPE_WB2_WGN_GB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_WB2_WGN_GB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_WB2_WGN_GB_RESERVED_SHIFT                                                 (13U)
#define IPIPE_WB2_WGN_GB_RESERVED_MASK                                                  (0x0000e000U)

#define IPIPE_WB2_WGN_B_VAL_SHIFT                                                       (0U)
#define IPIPE_WB2_WGN_B_VAL_MASK                                                        (0x00001fffU)

#define IPIPE_WB2_WGN_B_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_WB2_WGN_B_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_WB2_WGN_B_RESERVED_SHIFT                                                  (13U)
#define IPIPE_WB2_WGN_B_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_CFA_MODE_SHIFT                                                            (0U)
#define IPIPE_CFA_MODE_MASK                                                             (0x00000003U)
#define IPIPE_CFA_MODE_NEWENUM1                                                          (0U)
#define IPIPE_CFA_MODE_NEWENUM2                                                          (1U)
#define IPIPE_CFA_MODE_NEWENUM3                                                          (2U)
#define IPIPE_CFA_MODE_NEWENUM4                                                          (3U)

#define IPIPE_CFA_MODE_RESERVED_SHIFT                                                   (2U)
#define IPIPE_CFA_MODE_RESERVED_MASK                                                    (0x0000fffcU)

#define IPIPE_CFA_MODE_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_CFA_MODE_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_CFA_2DIR_HPF_THR_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_HPF_THR_VAL_MASK                                                 (0x00001fffU)

#define IPIPE_CFA_2DIR_HPF_THR_RESERVED_SHIFT                                           (13U)
#define IPIPE_CFA_2DIR_HPF_THR_RESERVED_MASK                                            (0x0000e000U)

#define IPIPE_CFA_2DIR_HPF_THR_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_HPF_THR_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_HPF_SLP_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_HPF_SLP_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_2DIR_HPF_SLP_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_2DIR_HPF_SLP_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_2DIR_HPF_SLP_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_HPF_SLP_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_MIX_THR_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_MIX_THR_VAL_MASK                                                 (0x00001fffU)

#define IPIPE_CFA_2DIR_MIX_THR_RESERVED_SHIFT                                           (13U)
#define IPIPE_CFA_2DIR_MIX_THR_RESERVED_MASK                                            (0x0000e000U)

#define IPIPE_CFA_2DIR_MIX_THR_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_MIX_THR_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_MIX_SLP_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_MIX_SLP_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_2DIR_MIX_SLP_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_2DIR_MIX_SLP_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_2DIR_MIX_SLP_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_MIX_SLP_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_DIR_TRH_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_DIR_TRH_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_2DIR_DIR_TRH_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_2DIR_DIR_TRH_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_2DIR_DIR_TRH_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_DIR_TRH_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_DIR_SLP_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_2DIR_DIR_SLP_VAL_MASK                                                 (0x0000007fU)

#define IPIPE_CFA_2DIR_DIR_SLP_RESERVED_SHIFT                                           (7U)
#define IPIPE_CFA_2DIR_DIR_SLP_RESERVED_MASK                                            (0x0000ff80U)

#define IPIPE_CFA_2DIR_DIR_SLP_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_2DIR_DIR_SLP_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_2DIR_NDWT_VAL_SHIFT                                                   (0U)
#define IPIPE_CFA_2DIR_NDWT_VAL_MASK                                                    (0x0000003fU)

#define IPIPE_CFA_2DIR_NDWT_RESERVED_SHIFT                                              (6U)
#define IPIPE_CFA_2DIR_NDWT_RESERVED_MASK                                               (0x0000ffc0U)

#define IPIPE_CFA_2DIR_NDWT_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CFA_2DIR_NDWT_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CFA_MONO_HUE_FRA_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_MONO_HUE_FRA_VAL_MASK                                                 (0x0000003fU)

#define IPIPE_CFA_MONO_HUE_FRA_RESERVED_SHIFT                                           (6U)
#define IPIPE_CFA_MONO_HUE_FRA_RESERVED_MASK                                            (0x0000ffc0U)

#define IPIPE_CFA_MONO_HUE_FRA_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_MONO_HUE_FRA_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_MONO_EDG_THR_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_MONO_EDG_THR_VAL_MASK                                                 (0x000000ffU)

#define IPIPE_CFA_MONO_EDG_THR_RESERVED_SHIFT                                           (8U)
#define IPIPE_CFA_MONO_EDG_THR_RESERVED_MASK                                            (0x0000ff00U)

#define IPIPE_CFA_MONO_EDG_THR_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_MONO_EDG_THR_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_MONO_THR_MIN_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_MONO_THR_MIN_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_MONO_THR_MIN_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_MONO_THR_MIN_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_MONO_THR_MIN_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_MONO_THR_MIN_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_MONO_THR_SLP_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_MONO_THR_SLP_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_MONO_THR_SLP_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_MONO_THR_SLP_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_MONO_THR_SLP_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_MONO_THR_SLP_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_MONO_SLP_MIN_VAL_SHIFT                                                (0U)
#define IPIPE_CFA_MONO_SLP_MIN_VAL_MASK                                                 (0x000003ffU)

#define IPIPE_CFA_MONO_SLP_MIN_RESERVED_SHIFT                                           (10U)
#define IPIPE_CFA_MONO_SLP_MIN_RESERVED_MASK                                            (0x0000fc00U)

#define IPIPE_CFA_MONO_SLP_MIN_RESERVED1_SHIFT                                          (16U)
#define IPIPE_CFA_MONO_SLP_MIN_RESERVED1_MASK                                           (0xffff0000U)

#define IPIPE_CFA_MONO_SLP_VAL_SHIFT                                                    (0U)
#define IPIPE_CFA_MONO_SLP_VAL_MASK                                                     (0x000003ffU)

#define IPIPE_CFA_MONO_SLP_RESERVED_SHIFT                                               (10U)
#define IPIPE_CFA_MONO_SLP_RESERVED_MASK                                                (0x0000fc00U)

#define IPIPE_CFA_MONO_SLP_RESERVED1_SHIFT                                              (16U)
#define IPIPE_CFA_MONO_SLP_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_CFA_MONO_LPWT_VAL_SHIFT                                                   (0U)
#define IPIPE_CFA_MONO_LPWT_VAL_MASK                                                    (0x0000003fU)

#define IPIPE_CFA_MONO_LPWT_RESERVED_SHIFT                                              (6U)
#define IPIPE_CFA_MONO_LPWT_RESERVED_MASK                                               (0x0000ffc0U)

#define IPIPE_CFA_MONO_LPWT_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CFA_MONO_LPWT_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_RGB1_MUL_RR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_RR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_RR_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_RR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_RR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_RR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_GR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_GR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_GR_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_GR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_GR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_GR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_BR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_BR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_BR_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_BR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_BR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_BR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_RG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_RG_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_RG_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_RG_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_RG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_RG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_GG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_GG_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_GG_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_GG_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_GG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_GG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_BG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_BG_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_BG_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_BG_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_BG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_BG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_RB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_RB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_RB_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_RB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_RB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_RB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_GB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_GB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_GB_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_GB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_GB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_GB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_MUL_BB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_MUL_BB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_RGB1_MUL_BB_RESERVED_SHIFT                                                (12U)
#define IPIPE_RGB1_MUL_BB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_RGB1_MUL_BB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_MUL_BB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_OFT_OR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_OFT_OR_VAL_MASK                                                      (0x00001fffU)

#define IPIPE_RGB1_OFT_OR_RESERVED_SHIFT                                                (13U)
#define IPIPE_RGB1_OFT_OR_RESERVED_MASK                                                 (0x0000e000U)

#define IPIPE_RGB1_OFT_OR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_OFT_OR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_OFT_OG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_OFT_OG_VAL_MASK                                                      (0x00001fffU)

#define IPIPE_RGB1_OFT_OG_RESERVED_SHIFT                                                (13U)
#define IPIPE_RGB1_OFT_OG_RESERVED_MASK                                                 (0x0000e000U)

#define IPIPE_RGB1_OFT_OG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_OFT_OG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB1_OFT_OB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB1_OFT_OB_VAL_MASK                                                      (0x00001fffU)

#define IPIPE_RGB1_OFT_OB_RESERVED_SHIFT                                                (13U)
#define IPIPE_RGB1_OFT_OB_RESERVED_MASK                                                 (0x0000e000U)

#define IPIPE_RGB1_OFT_OB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB1_OFT_OB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_GMM_CFG_BYPR_SHIFT                                                        (0U)
#define IPIPE_GMM_CFG_BYPR_MASK                                                         (0x00000001U)
#define IPIPE_GMM_CFG_BYPR_NEWENUM1                                                      (0U)
#define IPIPE_GMM_CFG_BYPR_NEWENUM2                                                      (1U)

#define IPIPE_GMM_CFG_BYPG_SHIFT                                                        (1U)
#define IPIPE_GMM_CFG_BYPG_MASK                                                         (0x00000002U)
#define IPIPE_GMM_CFG_BYPG_NEWENUM1                                                      (0U)
#define IPIPE_GMM_CFG_BYPG_NEWENUM2                                                      (1U)

#define IPIPE_GMM_CFG_BYPB_SHIFT                                                        (2U)
#define IPIPE_GMM_CFG_BYPB_MASK                                                         (0x00000004U)
#define IPIPE_GMM_CFG_BYPB_NEWENUM1                                                      (0U)
#define IPIPE_GMM_CFG_BYPB_NEWENUM2                                                      (1U)

#define IPIPE_GMM_CFG_SIZ_SHIFT                                                         (5U)
#define IPIPE_GMM_CFG_SIZ_MASK                                                          (0x00000060U)
#define IPIPE_GMM_CFG_SIZ_NEWENUM1                                                       (0U)
#define IPIPE_GMM_CFG_SIZ_NEWENUM2                                                       (1U)
#define IPIPE_GMM_CFG_SIZ_NEWENUM3                                                       (2U)
#define IPIPE_GMM_CFG_SIZ_NEWENUM4                                                       (3U)

#define IPIPE_GMM_CFG_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GMM_CFG_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GMM_CFG_TBL_SHIFT                                                         (4U)
#define IPIPE_GMM_CFG_TBL_MASK                                                          (0x00000010U)
#define IPIPE_GMM_CFG_TBL_NEWENUM1                                                       (0U)
#define IPIPE_GMM_CFG_TBL_NEWENUM2                                                       (1U)

#define IPIPE_GMM_CFG_RESERVED_SHIFT                                                    (3U)
#define IPIPE_GMM_CFG_RESERVED_MASK                                                     (0x00000008U)

#define IPIPE_GMM_CFG_RESERVED2_SHIFT                                                   (7U)
#define IPIPE_GMM_CFG_RESERVED2_MASK                                                    (0x0000ff80U)

#define IPIPE_RGB2_MUL_RR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_RR_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_RR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_RR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_RR_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_RR_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_GR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_GR_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_GR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_GR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_GR_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_GR_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_BR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_BR_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_BR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_BR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_BR_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_BR_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_RG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_RG_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_RG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_RG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_RG_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_RG_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_GG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_GG_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_GG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_GG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_GG_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_GG_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_BG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_BG_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_BG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_BG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_BG_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_BG_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_RB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_RB_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_RB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_RB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_RB_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_RB_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_GB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_GB_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_GB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_GB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_GB_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_GB_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_MUL_BB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_MUL_BB_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_MUL_BB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_MUL_BB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_MUL_BB_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_MUL_BB_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_OFT_OR_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_OFT_OR_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_OFT_OR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_OFT_OR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_OFT_OR_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_OFT_OR_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_OFT_OG_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_OFT_OG_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_OFT_OG_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_OFT_OG_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_OFT_OG_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_OFT_OG_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_RGB2_OFT_OB_VAL_SHIFT                                                     (0U)
#define IPIPE_RGB2_OFT_OB_VAL_MASK                                                      (0x000007ffU)

#define IPIPE_RGB2_OFT_OB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_RGB2_OFT_OB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_RGB2_OFT_OB_RESERVED_SHIFT                                                (11U)
#define IPIPE_RGB2_OFT_OB_RESERVED_MASK                                                 (0x0000f800U)

#define IPIPE_3DLUT_EN_SHIFT                                                            (0U)
#define IPIPE_3DLUT_EN_MASK                                                             (0x00000001U)
#define IPIPE_3DLUT_EN_NEWENUM1                                                          (0U)
#define IPIPE_3DLUT_EN_NEWENUM2                                                          (1U)

#define IPIPE_3DLUT_EN_RESERVED_SHIFT                                                   (1U)
#define IPIPE_3DLUT_EN_RESERVED_MASK                                                    (0x0000fffeU)

#define IPIPE_3DLUT_EN_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_3DLUT_EN_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_YUV_ADJ_CRT_SHIFT                                                         (0U)
#define IPIPE_YUV_ADJ_CRT_MASK                                                          (0x000000ffU)

#define IPIPE_YUV_ADJ_BRT_SHIFT                                                         (8U)
#define IPIPE_YUV_ADJ_BRT_MASK                                                          (0x0000ff00U)

#define IPIPE_YUV_ADJ_RESERVED_SHIFT                                                    (16U)
#define IPIPE_YUV_ADJ_RESERVED_MASK                                                     (0xffff0000U)

#define IPIPE_YUV_MUL_RY_VAL_SHIFT                                                      (0U)
#define IPIPE_YUV_MUL_RY_VAL_MASK                                                       (0x00000fffU)

#define IPIPE_YUV_MUL_RY_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YUV_MUL_RY_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YUV_MUL_RY_RESERVED_SHIFT                                                 (12U)
#define IPIPE_YUV_MUL_RY_RESERVED_MASK                                                  (0x0000f000U)

#define IPIPE_YUV_MUL_GY_VAL_SHIFT                                                      (0U)
#define IPIPE_YUV_MUL_GY_VAL_MASK                                                       (0x00000fffU)

#define IPIPE_YUV_MUL_GY_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YUV_MUL_GY_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YUV_MUL_GY_RESERVED_SHIFT                                                 (12U)
#define IPIPE_YUV_MUL_GY_RESERVED_MASK                                                  (0x0000f000U)

#define IPIPE_YUV_MUL_BY_VAL_SHIFT                                                      (0U)
#define IPIPE_YUV_MUL_BY_VAL_MASK                                                       (0x00000fffU)

#define IPIPE_YUV_MUL_BY_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YUV_MUL_BY_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YUV_MUL_BY_RESERVED_SHIFT                                                 (12U)
#define IPIPE_YUV_MUL_BY_RESERVED_MASK                                                  (0x0000f000U)

#define IPIPE_YUV_MUL_RCB_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_RCB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_RCB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_RCB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_MUL_RCB_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_RCB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_GCB_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_GCB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_GCB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_GCB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_MUL_GCB_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_GCB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_BCB_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_BCB_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_BCB_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_BCB_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_MUL_BCB_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_BCB_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_RCR_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_RCR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_RCR_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_RCR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_RCR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_RCR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_MUL_GCR_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_GCR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_GCR_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_GCR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_GCR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_GCR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_MUL_BCR_VAL_SHIFT                                                     (0U)
#define IPIPE_YUV_MUL_BCR_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YUV_MUL_BCR_RESERVED_SHIFT                                                (12U)
#define IPIPE_YUV_MUL_BCR_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YUV_MUL_BCR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YUV_MUL_BCR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YUV_OFT_Y_VAL_SHIFT                                                       (0U)
#define IPIPE_YUV_OFT_Y_VAL_MASK                                                        (0x000007ffU)

#define IPIPE_YUV_OFT_Y_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_YUV_OFT_Y_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_YUV_OFT_Y_RESERVED_SHIFT                                                  (11U)
#define IPIPE_YUV_OFT_Y_RESERVED_MASK                                                   (0x0000f800U)

#define IPIPE_YUV_OFT_CB_VAL_SHIFT                                                      (0U)
#define IPIPE_YUV_OFT_CB_VAL_MASK                                                       (0x000007ffU)

#define IPIPE_YUV_OFT_CB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YUV_OFT_CB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YUV_OFT_CB_RESERVED_SHIFT                                                 (11U)
#define IPIPE_YUV_OFT_CB_RESERVED_MASK                                                  (0x0000f800U)

#define IPIPE_YUV_OFT_CR_VAL_SHIFT                                                      (0U)
#define IPIPE_YUV_OFT_CR_VAL_MASK                                                       (0x000007ffU)

#define IPIPE_YUV_OFT_CR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YUV_OFT_CR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YUV_OFT_CR_RESERVED_SHIFT                                                 (11U)
#define IPIPE_YUV_OFT_CR_RESERVED_MASK                                                  (0x0000f800U)

#define IPIPE_YUV_PHS_POS_SHIFT                                                         (0U)
#define IPIPE_YUV_PHS_POS_MASK                                                          (0x00000001U)
#define IPIPE_YUV_PHS_POS_NEWENUM1                                                       (0U)
#define IPIPE_YUV_PHS_POS_NEWENUM2                                                       (1U)

#define IPIPE_YUV_PHS_LPF_SHIFT                                                         (1U)
#define IPIPE_YUV_PHS_LPF_MASK                                                          (0x00000002U)
#define IPIPE_YUV_PHS_LPF_NEWENUM1                                                       (0U)
#define IPIPE_YUV_PHS_LPF_NEWENUM2                                                       (1U)

#define IPIPE_YUV_PHS_RESERVED_SHIFT                                                    (2U)
#define IPIPE_YUV_PHS_RESERVED_MASK                                                     (0x0000fffcU)

#define IPIPE_YUV_PHS_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_YUV_PHS_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GBCE_EN_SHIFT                                                             (0U)
#define IPIPE_GBCE_EN_MASK                                                              (0x00000001U)
#define IPIPE_GBCE_EN_NEWENUM1                                                           (0U)
#define IPIPE_GBCE_EN_NEWENUM2                                                           (1U)

#define IPIPE_GBCE_EN_RESERVED_SHIFT                                                    (1U)
#define IPIPE_GBCE_EN_RESERVED_MASK                                                     (0x0000fffeU)

#define IPIPE_GBCE_EN_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_GBCE_EN_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_GBCE_TYP_SHIFT                                                            (0U)
#define IPIPE_GBCE_TYP_MASK                                                             (0x00000001U)
#define IPIPE_GBCE_TYP_NEWENUM1                                                          (0U)
#define IPIPE_GBCE_TYP_NEWENUM2                                                          (1U)

#define IPIPE_GBCE_TYP_RESERVED_SHIFT                                                   (1U)
#define IPIPE_GBCE_TYP_RESERVED_MASK                                                    (0x0000fffeU)

#define IPIPE_GBCE_TYP_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_GBCE_TYP_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_YEE_EN_SHIFT                                                              (0U)
#define IPIPE_YEE_EN_MASK                                                               (0x00000001U)
#define IPIPE_YEE_EN_NEWENUM1                                                            (0U)
#define IPIPE_YEE_EN_NEWENUM2                                                            (1U)

#define IPIPE_YEE_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_YEE_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_YEE_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_YEE_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_YEE_TYP_SEL_SHIFT                                                         (0U)
#define IPIPE_YEE_TYP_SEL_MASK                                                          (0x00000001U)
#define IPIPE_YEE_TYP_SEL_NEWENUM1                                                       (1U)
#define IPIPE_YEE_TYP_SEL_NEWENUM2                                                       (0U)

#define IPIPE_YEE_TYP_HAL_SHIFT                                                         (1U)
#define IPIPE_YEE_TYP_HAL_MASK                                                          (0x00000002U)

#define IPIPE_YEE_TYP_RESERVED_SHIFT                                                    (2U)
#define IPIPE_YEE_TYP_RESERVED_MASK                                                     (0x0000fffcU)

#define IPIPE_YEE_TYP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_YEE_TYP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_YEE_SHF_SHIFT                                                             (0U)
#define IPIPE_YEE_SHF_MASK                                                              (0x0000000fU)

#define IPIPE_YEE_SHF_RESERVED_SHIFT                                                    (4U)
#define IPIPE_YEE_SHF_RESERVED_MASK                                                     (0x0000fff0U)

#define IPIPE_YEE_SHF_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_YEE_SHF_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_YEE_MUL_00_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_00_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_00_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_00_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_00_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_00_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_01_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_01_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_01_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_01_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_01_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_01_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_02_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_02_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_02_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_02_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_02_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_02_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_10_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_10_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_10_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_10_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_10_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_10_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_11_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_11_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_11_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_11_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_11_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_11_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_12_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_12_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_12_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_12_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_12_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_12_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_20_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_20_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_20_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_20_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_20_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_20_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_21_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_21_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_21_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_21_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_21_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_21_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_MUL_22_VAL_SHIFT                                                      (0U)
#define IPIPE_YEE_MUL_22_VAL_MASK                                                       (0x000003ffU)

#define IPIPE_YEE_MUL_22_RESERVED_SHIFT                                                 (10U)
#define IPIPE_YEE_MUL_22_RESERVED_MASK                                                  (0x0000fc00U)

#define IPIPE_YEE_MUL_22_RESERVED1_SHIFT                                                (16U)
#define IPIPE_YEE_MUL_22_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_YEE_THR_VAL_SHIFT                                                         (0U)
#define IPIPE_YEE_THR_VAL_MASK                                                          (0x0000003fU)

#define IPIPE_YEE_THR_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_YEE_THR_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_YEE_THR_RESERVED_SHIFT                                                    (6U)
#define IPIPE_YEE_THR_RESERVED_MASK                                                     (0x0000ffc0U)

#define IPIPE_YEE_E_GAN_VAL_SHIFT                                                       (0U)
#define IPIPE_YEE_E_GAN_VAL_MASK                                                        (0x00000fffU)

#define IPIPE_YEE_E_GAN_RESERVED_SHIFT                                                  (12U)
#define IPIPE_YEE_E_GAN_RESERVED_MASK                                                   (0x0000f000U)

#define IPIPE_YEE_E_GAN_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_YEE_E_GAN_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_YEE_E_THR_1_VAL_SHIFT                                                     (0U)
#define IPIPE_YEE_E_THR_1_VAL_MASK                                                      (0x00000fffU)

#define IPIPE_YEE_E_THR_1_RESERVED_SHIFT                                                (12U)
#define IPIPE_YEE_E_THR_1_RESERVED_MASK                                                 (0x0000f000U)

#define IPIPE_YEE_E_THR_1_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YEE_E_THR_1_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YEE_E_THR_2_VAL_SHIFT                                                     (0U)
#define IPIPE_YEE_E_THR_2_VAL_MASK                                                      (0x0000003fU)

#define IPIPE_YEE_E_THR_2_RESERVED_SHIFT                                                (6U)
#define IPIPE_YEE_E_THR_2_RESERVED_MASK                                                 (0x0000ffc0U)

#define IPIPE_YEE_E_THR_2_RESERVED1_SHIFT                                               (16U)
#define IPIPE_YEE_E_THR_2_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_YEE_G_GAN_VAL_SHIFT                                                       (0U)
#define IPIPE_YEE_G_GAN_VAL_MASK                                                        (0x000000ffU)

#define IPIPE_YEE_G_GAN_RESERVED_SHIFT                                                  (8U)
#define IPIPE_YEE_G_GAN_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_YEE_G_GAN_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_YEE_G_GAN_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_YEE_G_OFT_VAL_SHIFT                                                       (0U)
#define IPIPE_YEE_G_OFT_VAL_MASK                                                        (0x0000003fU)

#define IPIPE_YEE_G_OFT_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_YEE_G_OFT_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_YEE_G_OFT_RESERVED_SHIFT                                                  (6U)
#define IPIPE_YEE_G_OFT_RESERVED_MASK                                                   (0x0000ffc0U)

#define IPIPE_CAR_EN_SHIFT                                                              (0U)
#define IPIPE_CAR_EN_MASK                                                               (0x00000001U)
#define IPIPE_CAR_EN_NEWENUM1                                                            (0U)
#define IPIPE_CAR_EN_NEWENUM2                                                            (1U)

#define IPIPE_CAR_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_CAR_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_CAR_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_CAR_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_CAR_TYP_SHIFT                                                             (0U)
#define IPIPE_CAR_TYP_MASK                                                              (0x00000001U)
#define IPIPE_CAR_TYP_NEWENUM1                                                           (0U)
#define IPIPE_CAR_TYP_NEWENUM2                                                           (1U)

#define IPIPE_CAR_TYP_RESERVED_SHIFT                                                    (2U)
#define IPIPE_CAR_TYP_RESERVED_MASK                                                     (0x0000fffcU)

#define IPIPE_CAR_TYP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_CAR_TYP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_CAR_TYP_CHR_SHIFT                                                         (1U)
#define IPIPE_CAR_TYP_CHR_MASK                                                          (0x00000002U)
#define IPIPE_CAR_TYP_CHR_NEWENUM1                                                       (0U)
#define IPIPE_CAR_TYP_CHR_NEWENUM2                                                       (1U)

#define IPIPE_CAR_SW_SW0_SHIFT                                                          (0U)
#define IPIPE_CAR_SW_SW0_MASK                                                           (0x000000ffU)

#define IPIPE_CAR_SW_SW1_SHIFT                                                          (8U)
#define IPIPE_CAR_SW_SW1_MASK                                                           (0x0000ff00U)

#define IPIPE_CAR_SW_RESERVED_SHIFT                                                     (16U)
#define IPIPE_CAR_SW_RESERVED_MASK                                                      (0xffff0000U)

#define IPIPE_CAR_HPF_TYP_SHIFT                                                         (0U)
#define IPIPE_CAR_HPF_TYP_MASK                                                          (0x00000007U)
#define IPIPE_CAR_HPF_TYP_NEWENUM1                                                       (0U)
#define IPIPE_CAR_HPF_TYP_NEWENUM2                                                       (1U)
#define IPIPE_CAR_HPF_TYP_NEWENUM3                                                       (2U)
#define IPIPE_CAR_HPF_TYP_NEWENUM4                                                       (3U)
#define IPIPE_CAR_HPF_TYP_NEWENUM5                                                       (4U)
#define IPIPE_CAR_HPF_TYP_NEWENUM6                                                       (5U)
#define IPIPE_CAR_HPF_TYP_NEWENUM7                                                       (6U)
#define IPIPE_CAR_HPF_TYP_NEWENUM8                                                       (7U)

#define IPIPE_CAR_HPF_TYP_RESERVED_SHIFT                                                (3U)
#define IPIPE_CAR_HPF_TYP_RESERVED_MASK                                                 (0x0000fff8U)

#define IPIPE_CAR_HPF_TYP_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_HPF_TYP_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_HPF_SHF_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_HPF_SHF_VAL_MASK                                                      (0x00000003U)

#define IPIPE_CAR_HPF_SHF_RESERVED_SHIFT                                                (2U)
#define IPIPE_CAR_HPF_SHF_RESERVED_MASK                                                 (0x0000fffcU)

#define IPIPE_CAR_HPF_SHF_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_HPF_SHF_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_HPF_THR_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_HPF_THR_VAL_MASK                                                      (0x000000ffU)

#define IPIPE_CAR_HPF_THR_RESERVED_SHIFT                                                (8U)
#define IPIPE_CAR_HPF_THR_RESERVED_MASK                                                 (0x0000ff00U)

#define IPIPE_CAR_HPF_THR_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_HPF_THR_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_GN1_GAN_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN1_GAN_VAL_MASK                                                      (0x000000ffU)

#define IPIPE_CAR_GN1_GAN_RESERVED_SHIFT                                                (8U)
#define IPIPE_CAR_GN1_GAN_RESERVED_MASK                                                 (0x0000ff00U)

#define IPIPE_CAR_GN1_GAN_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_GN1_GAN_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_GN1_SHF_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN1_SHF_VAL_MASK                                                      (0x00000007U)

#define IPIPE_CAR_GN1_SHF_RESERVED_SHIFT                                                (3U)
#define IPIPE_CAR_GN1_SHF_RESERVED_MASK                                                 (0x0000fff8U)

#define IPIPE_CAR_GN1_SHF_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_GN1_SHF_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_GN1_MIN_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN1_MIN_VAL_MASK                                                      (0x000001ffU)

#define IPIPE_CAR_GN1_MIN_RESERVED_SHIFT                                                (9U)
#define IPIPE_CAR_GN1_MIN_RESERVED_MASK                                                 (0x0000fe00U)

#define IPIPE_CAR_GN1_MIN_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_GN1_MIN_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_GN2_GAN_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN2_GAN_VAL_MASK                                                      (0x000000ffU)

#define IPIPE_CAR_GN2_GAN_RESERVED_SHIFT                                                (8U)
#define IPIPE_CAR_GN2_GAN_RESERVED_MASK                                                 (0x0000ff00U)

#define IPIPE_CAR_GN2_GAN_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_GN2_GAN_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CAR_GN2_SHF_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN2_SHF_VAL_MASK                                                      (0x0000000fU)

#define IPIPE_CAR_GN2_SHF_RESERVED_SHIFT                                                (4U)
#define IPIPE_CAR_GN2_SHF_RESERVED_MASK                                                 (0xfffffff0U)

#define IPIPE_CAR_GN2_MIN_VAL_SHIFT                                                     (0U)
#define IPIPE_CAR_GN2_MIN_VAL_MASK                                                      (0x000001ffU)

#define IPIPE_CAR_GN2_MIN_RESERVED_SHIFT                                                (9U)
#define IPIPE_CAR_GN2_MIN_RESERVED_MASK                                                 (0x0000fe00U)

#define IPIPE_CAR_GN2_MIN_RESERVED1_SHIFT                                               (16U)
#define IPIPE_CAR_GN2_MIN_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_CGS_EN_SHIFT                                                              (0U)
#define IPIPE_CGS_EN_MASK                                                               (0x00000001U)
#define IPIPE_CGS_EN_NEWENUM1                                                            (0U)
#define IPIPE_CGS_EN_NEWENUM2                                                            (1U)

#define IPIPE_CGS_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_CGS_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_CGS_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_CGS_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_CGS_GN1_L_THR_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_L_THR_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN1_L_THR_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN1_L_THR_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_CGS_GN1_L_THR_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_L_THR_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_L_GAIN_VAL_SHIFT                                                  (0U)
#define IPIPE_CGS_GN1_L_GAIN_VAL_MASK                                                   (0x000000ffU)

#define IPIPE_CGS_GN1_L_GAIN_RESERVED_SHIFT                                             (8U)
#define IPIPE_CGS_GN1_L_GAIN_RESERVED_MASK                                              (0x0000ff00U)

#define IPIPE_CGS_GN1_L_GAIN_RESERVED1_SHIFT                                            (16U)
#define IPIPE_CGS_GN1_L_GAIN_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_CGS_GN1_L_SHF_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_L_SHF_VAL_MASK                                                    (0x00000007U)

#define IPIPE_CGS_GN1_L_SHF_RESERVED_SHIFT                                              (3U)
#define IPIPE_CGS_GN1_L_SHF_RESERVED_MASK                                               (0x0000fff8U)

#define IPIPE_CGS_GN1_L_SHF_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_L_SHF_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_L_MIN_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_L_MIN_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN1_L_MIN_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_L_MIN_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_L_MIN_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN1_L_MIN_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_CGS_GN1_H_THR_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_H_THR_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN1_H_THR_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN1_H_THR_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_CGS_GN1_H_THR_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_H_THR_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_H_GAIN_VAL_SHIFT                                                  (0U)
#define IPIPE_CGS_GN1_H_GAIN_VAL_MASK                                                   (0x000000ffU)

#define IPIPE_CGS_GN1_H_GAIN_RESERVED_SHIFT                                             (8U)
#define IPIPE_CGS_GN1_H_GAIN_RESERVED_MASK                                              (0x0000ff00U)

#define IPIPE_CGS_GN1_H_GAIN_RESERVED1_SHIFT                                            (16U)
#define IPIPE_CGS_GN1_H_GAIN_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_CGS_GN1_H_SHF_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_H_SHF_VAL_MASK                                                    (0x00000007U)

#define IPIPE_CGS_GN1_H_SHF_RESERVED_SHIFT                                              (3U)
#define IPIPE_CGS_GN1_H_SHF_RESERVED_MASK                                               (0x0000fff8U)

#define IPIPE_CGS_GN1_H_SHF_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_H_SHF_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_H_MIN_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN1_H_MIN_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN1_H_MIN_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN1_H_MIN_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN1_H_MIN_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN1_H_MIN_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_CGS_GN2_L_THR_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN2_L_THR_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN2_L_THR_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN2_L_THR_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_CGS_GN2_L_THR_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN2_L_THR_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN2_L_GAIN_VAL_SHIFT                                                  (0U)
#define IPIPE_CGS_GN2_L_GAIN_VAL_MASK                                                   (0x000000ffU)

#define IPIPE_CGS_GN2_L_GAIN_RESERVED1_SHIFT                                            (16U)
#define IPIPE_CGS_GN2_L_GAIN_RESERVED1_MASK                                             (0xffff0000U)

#define IPIPE_CGS_GN2_L_GAIN_RESERVED_SHIFT                                             (8U)
#define IPIPE_CGS_GN2_L_GAIN_RESERVED_MASK                                              (0x0000ff00U)

#define IPIPE_CGS_GN2_L_SHF_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN2_L_SHF_VAL_MASK                                                    (0x00000007U)

#define IPIPE_CGS_GN2_L_SHF_RESERVED_SHIFT                                              (3U)
#define IPIPE_CGS_GN2_L_SHF_RESERVED_MASK                                               (0x0000fff8U)

#define IPIPE_CGS_GN2_L_SHF_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN2_L_SHF_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN2_L_MIN_VAL_SHIFT                                                   (0U)
#define IPIPE_CGS_GN2_L_MIN_VAL_MASK                                                    (0x000000ffU)

#define IPIPE_CGS_GN2_L_MIN_RESERVED1_SHIFT                                             (16U)
#define IPIPE_CGS_GN2_L_MIN_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_CGS_GN2_L_MIN_RESERVED_SHIFT                                              (8U)
#define IPIPE_CGS_GN2_L_MIN_RESERVED_MASK                                               (0x0000ff00U)

#define IPIPE_BOX_EN_SHIFT                                                              (0U)
#define IPIPE_BOX_EN_MASK                                                               (0x00000001U)
#define IPIPE_BOX_EN_NEWENUM1                                                            (0U)
#define IPIPE_BOX_EN_NEWENUM2                                                            (1U)

#define IPIPE_BOX_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_BOX_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_BOX_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_BOX_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_BOX_MODE_OST_SHIFT                                                        (0U)
#define IPIPE_BOX_MODE_OST_MASK                                                         (0x00000001U)
#define IPIPE_BOX_MODE_OST_NEWENUM1                                                      (0U)
#define IPIPE_BOX_MODE_OST_NEWENUM2                                                      (1U)

#define IPIPE_BOX_MODE_RESERVED_SHIFT                                                   (1U)
#define IPIPE_BOX_MODE_RESERVED_MASK                                                    (0x0000fffeU)

#define IPIPE_BOX_MODE_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_BOX_MODE_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_BOX_TYP_SEL_SHIFT                                                         (0U)
#define IPIPE_BOX_TYP_SEL_MASK                                                          (0x00000001U)
#define IPIPE_BOX_TYP_SEL_NEWENUM1                                                       (0U)
#define IPIPE_BOX_TYP_SEL_NEWENUM2                                                       (1U)

#define IPIPE_BOX_TYP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_BOX_TYP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_BOX_TYP_RESERVED_SHIFT                                                    (1U)
#define IPIPE_BOX_TYP_RESERVED_MASK                                                     (0x0000fffeU)

#define IPIPE_BOX_SHF_VAL_SHIFT                                                         (0U)
#define IPIPE_BOX_SHF_VAL_MASK                                                          (0x00000007U)

#define IPIPE_BOX_SHF_RESERVED_SHIFT                                                    (3U)
#define IPIPE_BOX_SHF_RESERVED_MASK                                                     (0x0000fff8U)

#define IPIPE_BOX_SHF_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_BOX_SHF_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_BOX_SDR_SAD_H_VAL_SHIFT                                                   (0U)
#define IPIPE_BOX_SDR_SAD_H_VAL_MASK                                                    (0x0000ffffU)

#define IPIPE_BOX_SDR_SAD_H_RESERVED_SHIFT                                              (16U)
#define IPIPE_BOX_SDR_SAD_H_RESERVED_MASK                                               (0xffff0000U)

#define IPIPE_BOX_SDR_SAD_L_VAL_SHIFT                                                   (5U)
#define IPIPE_BOX_SDR_SAD_L_VAL_MASK                                                    (0x0000ffe0U)

#define IPIPE_BOX_SDR_SAD_L_RESERVED_SHIFT                                              (16U)
#define IPIPE_BOX_SDR_SAD_L_RESERVED_MASK                                               (0xffff0000U)

#define IPIPE_BOX_SDR_SAD_L_VAL_RESERVED_SHIFT                                          (0U)
#define IPIPE_BOX_SDR_SAD_L_VAL_RESERVED_MASK                                           (0x0000001fU)

#define IPIPE_RESERVED2_RESERVED_SHIFT                                                  (0U)
#define IPIPE_RESERVED2_RESERVED_MASK                                                   (0x0000ffffU)

#define IPIPE_RESERVED2_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_RESERVED2_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_EN_SHIFT                                                              (0U)
#define IPIPE_HST_EN_MASK                                                               (0x00000001U)
#define IPIPE_HST_EN_NEWENUM1                                                            (0U)
#define IPIPE_HST_EN_NEWENUM2                                                            (1U)

#define IPIPE_HST_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_HST_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_HST_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_HST_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_HST_MODE_OST_SHIFT                                                        (0U)
#define IPIPE_HST_MODE_OST_MASK                                                         (0x00000001U)
#define IPIPE_HST_MODE_OST_NEWENUM1                                                      (0U)
#define IPIPE_HST_MODE_OST_NEWENUM2                                                      (1U)

#define IPIPE_HST_MODE_RESERVED_SHIFT                                                   (1U)
#define IPIPE_HST_MODE_RESERVED_MASK                                                    (0x0000fffeU)

#define IPIPE_HST_MODE_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_HST_MODE_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_HST_SEL_TYP_SHIFT                                                         (0U)
#define IPIPE_HST_SEL_TYP_MASK                                                          (0x00000003U)
#define IPIPE_HST_SEL_TYP_NEWENUM1                                                       (0U)
#define IPIPE_HST_SEL_TYP_NEWENUM2                                                       (1U)
#define IPIPE_HST_SEL_TYP_NEWENUM3                                                       (2U)
#define IPIPE_HST_SEL_TYP_NEWENUM4                                                       (3U)

#define IPIPE_HST_SEL_SHIFT                                                             (2U)
#define IPIPE_HST_SEL_MASK                                                              (0x00000004U)
#define IPIPE_HST_SEL_NEWENUM1                                                           (0U)
#define IPIPE_HST_SEL_NEWENUM2                                                           (1U)

#define IPIPE_HST_SEL_RESERVED_SHIFT                                                    (3U)
#define IPIPE_HST_SEL_RESERVED_MASK                                                     (0x0000fff8U)

#define IPIPE_HST_SEL_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_HST_SEL_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_HST_PARA_RGN0_SHIFT                                                       (0U)
#define IPIPE_HST_PARA_RGN0_MASK                                                        (0x00000001U)
#define IPIPE_HST_PARA_RGN0_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_RGN0_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_RGN1_SHIFT                                                       (1U)
#define IPIPE_HST_PARA_RGN1_MASK                                                        (0x00000002U)
#define IPIPE_HST_PARA_RGN1_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_RGN1_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_RGN2_SHIFT                                                       (2U)
#define IPIPE_HST_PARA_RGN2_MASK                                                        (0x00000004U)
#define IPIPE_HST_PARA_RGN2_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_RGN2_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_RGN3_SHIFT                                                       (3U)
#define IPIPE_HST_PARA_RGN3_MASK                                                        (0x00000008U)
#define IPIPE_HST_PARA_RGN3_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_RGN3_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_COL0_SHIFT                                                       (4U)
#define IPIPE_HST_PARA_COL0_MASK                                                        (0x00000010U)
#define IPIPE_HST_PARA_COL0_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_COL0_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_COL1_SHIFT                                                       (5U)
#define IPIPE_HST_PARA_COL1_MASK                                                        (0x00000020U)
#define IPIPE_HST_PARA_COL1_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_COL1_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_COL2_SHIFT                                                       (6U)
#define IPIPE_HST_PARA_COL2_MASK                                                        (0x00000040U)
#define IPIPE_HST_PARA_COL2_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_COL2_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_COL3_SHIFT                                                       (7U)
#define IPIPE_HST_PARA_COL3_MASK                                                        (0x00000080U)
#define IPIPE_HST_PARA_COL3_NEWENUM1                                                     (0U)
#define IPIPE_HST_PARA_COL3_NEWENUM2                                                     (1U)

#define IPIPE_HST_PARA_SHF_SHIFT                                                        (8U)
#define IPIPE_HST_PARA_SHF_MASK                                                         (0x00000f00U)

#define IPIPE_HST_PARA_BIN_SHIFT                                                        (12U)
#define IPIPE_HST_PARA_BIN_MASK                                                         (0x00003000U)
#define IPIPE_HST_PARA_BIN_NEWENUM1                                                      (0U)
#define IPIPE_HST_PARA_BIN_NEWENUM2                                                      (1U)
#define IPIPE_HST_PARA_BIN_NEWENUM3                                                      (2U)
#define IPIPE_HST_PARA_BIN_NEWENUM4                                                      (3U)

#define IPIPE_HST_PARA_RESERVED_SHIFT                                                   (14U)
#define IPIPE_HST_PARA_RESERVED_MASK                                                    (0x0000c000U)

#define IPIPE_HST_PARA_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_HST_PARA_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_HST_0_VPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_0_VPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_0_VPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_0_VPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_0_VPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_0_VPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_0_VPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_0_VPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_0_VSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_0_VSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_0_VSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_0_VSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_0_VSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_0_VSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_0_VSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_0_VSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_0_HPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_0_HPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_0_HPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_0_HPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_0_HPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_0_HPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_0_HPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_0_HPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_0_HSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_0_HSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_0_HSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_0_HSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_0_HSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_0_HSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_0_HSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_0_HSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_1_VPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_1_VPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_1_VPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_1_VPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_1_VPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_1_VPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_1_VPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_1_VPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_1_VSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_1_VSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_1_VSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_1_VSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_1_VSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_1_VSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_1_VSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_1_VSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_1_HPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_1_HPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_1_HPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_1_HPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_1_HPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_1_HPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_1_HPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_1_HPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_1_HSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_1_HSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_1_HSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_1_HSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_1_HSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_1_HSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_1_HSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_1_HSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_2_VPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_2_VPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_2_VPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_2_VPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_2_VPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_2_VPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_2_VPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_2_VPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_2_VSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_2_VSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_2_VSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_2_VSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_2_VSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_2_VSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_2_VSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_2_VSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_2_HPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_2_HPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_2_HPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_2_HPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_2_HPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_2_HPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_2_HPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_2_HPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_2_HSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_2_HSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_2_HSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_2_HSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_2_HSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_2_HSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_2_HSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_2_HSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_3_VPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_3_VPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_3_VPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_3_VPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_3_VPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_3_VPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_3_VPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_3_VPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_3_VSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_3_VSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_3_VSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_3_VSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_3_VSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_3_VSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_3_VSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_3_VSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_3_HPS_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_3_HPS_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_3_HPS_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_3_HPS_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_3_HPS_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_3_HPS_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_3_HPS_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_3_HPS_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_3_HSZ_VAL_SHIFT                                                       (1U)
#define IPIPE_HST_3_HSZ_VAL_MASK                                                        (0x00001ffeU)

#define IPIPE_HST_3_HSZ_RESERVED_SHIFT                                                  (13U)
#define IPIPE_HST_3_HSZ_RESERVED_MASK                                                   (0x0000e000U)

#define IPIPE_HST_3_HSZ_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_3_HSZ_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_3_HSZ_VAL_RESERVED_SHIFT                                              (0U)
#define IPIPE_HST_3_HSZ_VAL_RESERVED_MASK                                               (0x00000001U)

#define IPIPE_HST_TBL_SEL_SHIFT                                                         (0U)
#define IPIPE_HST_TBL_SEL_MASK                                                          (0x00000001U)
#define IPIPE_HST_TBL_SEL_NEWENUM1                                                       (0U)
#define IPIPE_HST_TBL_SEL_NEWENUM2                                                       (1U)

#define IPIPE_HST_TBL_CLR_SHIFT                                                         (1U)
#define IPIPE_HST_TBL_CLR_MASK                                                          (0x00000002U)
#define IPIPE_HST_TBL_CLR_NEWENUM1                                                       (0U)
#define IPIPE_HST_TBL_CLR_NEWENUM2                                                       (1U)

#define IPIPE_HST_TBL_RESERVED_SHIFT                                                    (2U)
#define IPIPE_HST_TBL_RESERVED_MASK                                                     (0x0000fffcU)

#define IPIPE_HST_TBL_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_HST_TBL_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_HST_MUL_R_GAIN_SHIFT                                                      (0U)
#define IPIPE_HST_MUL_R_GAIN_MASK                                                       (0x000000ffU)

#define IPIPE_HST_MUL_R_RESERVED_SHIFT                                                  (8U)
#define IPIPE_HST_MUL_R_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_HST_MUL_R_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_MUL_R_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_HST_MUL_GR_GAIN_SHIFT                                                     (0U)
#define IPIPE_HST_MUL_GR_GAIN_MASK                                                      (0x000000ffU)

#define IPIPE_HST_MUL_GR_RESERVED_SHIFT                                                 (8U)
#define IPIPE_HST_MUL_GR_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_HST_MUL_GR_RESERVED1_SHIFT                                                (16U)
#define IPIPE_HST_MUL_GR_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_HST_MUL_GB_GAIN_SHIFT                                                     (0U)
#define IPIPE_HST_MUL_GB_GAIN_MASK                                                      (0x000000ffU)

#define IPIPE_HST_MUL_GB_RESERVED_SHIFT                                                 (8U)
#define IPIPE_HST_MUL_GB_RESERVED_MASK                                                  (0x0000ff00U)

#define IPIPE_HST_MUL_GB_RESERVED1_SHIFT                                                (16U)
#define IPIPE_HST_MUL_GB_RESERVED1_MASK                                                 (0xffff0000U)

#define IPIPE_HST_MUL_B_GAIN_SHIFT                                                      (0U)
#define IPIPE_HST_MUL_B_GAIN_MASK                                                       (0x000000ffU)

#define IPIPE_HST_MUL_B_RESERVED_SHIFT                                                  (8U)
#define IPIPE_HST_MUL_B_RESERVED_MASK                                                   (0x0000ff00U)

#define IPIPE_HST_MUL_B_RESERVED1_SHIFT                                                 (16U)
#define IPIPE_HST_MUL_B_RESERVED1_MASK                                                  (0xffff0000U)

#define IPIPE_BSC_EN_SHIFT                                                              (0U)
#define IPIPE_BSC_EN_MASK                                                               (0x00000001U)
#define IPIPE_BSC_EN_NEWENUM1                                                            (0U)
#define IPIPE_BSC_EN_NEWENUM2                                                            (1U)

#define IPIPE_BSC_EN_RESERVED_SHIFT                                                     (1U)
#define IPIPE_BSC_EN_RESERVED_MASK                                                      (0x0000fffeU)

#define IPIPE_BSC_EN_RESERVED1_SHIFT                                                    (16U)
#define IPIPE_BSC_EN_RESERVED1_MASK                                                     (0xffff0000U)

#define IPIPE_BSC_MODE_OST_SHIFT                                                        (0U)
#define IPIPE_BSC_MODE_OST_MASK                                                         (0x00000001U)
#define IPIPE_BSC_MODE_OST_NEWENUM1                                                      (0U)
#define IPIPE_BSC_MODE_OST_NEWENUM2                                                      (1U)

#define IPIPE_BSC_MODE_RESERVED_SHIFT                                                   (1U)
#define IPIPE_BSC_MODE_RESERVED_MASK                                                    (0x0000fffeU)

#define IPIPE_BSC_MODE_RESERVED1_SHIFT                                                  (16U)
#define IPIPE_BSC_MODE_RESERVED1_MASK                                                   (0xffff0000U)

#define IPIPE_BSC_TYP_COL_SHIFT                                                         (0U)
#define IPIPE_BSC_TYP_COL_MASK                                                          (0x00000003U)
#define IPIPE_BSC_TYP_COL_NEWENUM1                                                       (0U)
#define IPIPE_BSC_TYP_COL_NEWENUM2                                                       (1U)
#define IPIPE_BSC_TYP_COL_NEWENUM3                                                       (2U)
#define IPIPE_BSC_TYP_COL_NEWENUM4                                                       (3U)

#define IPIPE_BSC_TYP_REN_SHIFT                                                         (2U)
#define IPIPE_BSC_TYP_REN_MASK                                                          (0x00000004U)
#define IPIPE_BSC_TYP_REN_NEWENUM1                                                       (0U)
#define IPIPE_BSC_TYP_REN_NEWENUM2                                                       (1U)

#define IPIPE_BSC_TYP_CEN_SHIFT                                                         (3U)
#define IPIPE_BSC_TYP_CEN_MASK                                                          (0x00000008U)
#define IPIPE_BSC_TYP_CEN_NEWENUM1                                                       (0U)
#define IPIPE_BSC_TYP_CEN_NEWENUM2                                                       (1U)

#define IPIPE_BSC_TYP_RESERVED_SHIFT                                                    (4U)
#define IPIPE_BSC_TYP_RESERVED_MASK                                                     (0x0000fff0U)

#define IPIPE_BSC_TYP_RESERVED1_SHIFT                                                   (16U)
#define IPIPE_BSC_TYP_RESERVED1_MASK                                                    (0xffff0000U)

#define IPIPE_BSC_ROW_VCT_VAL_SHIFT                                                     (0U)
#define IPIPE_BSC_ROW_VCT_VAL_MASK                                                      (0x00000003U)

#define IPIPE_BSC_ROW_VCT_RESERVED_SHIFT                                                (2U)
#define IPIPE_BSC_ROW_VCT_RESERVED_MASK                                                 (0x0000fffcU)

#define IPIPE_BSC_ROW_VCT_RESERVED1_SHIFT                                               (16U)
#define IPIPE_BSC_ROW_VCT_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_BSC_ROW_SHF_VAL_SHIFT                                                     (0U)
#define IPIPE_BSC_ROW_SHF_VAL_MASK                                                      (0x00000007U)

#define IPIPE_BSC_ROW_SHF_RESERVED_SHIFT                                                (3U)
#define IPIPE_BSC_ROW_SHF_RESERVED_MASK                                                 (0x0000fff8U)

#define IPIPE_BSC_ROW_SHF_RESERVED1_SHIFT                                               (16U)
#define IPIPE_BSC_ROW_SHF_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_BSC_ROW_VPOS_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_ROW_VPOS_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_ROW_VPOS_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_ROW_VPOS_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_ROW_VPOS_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_ROW_VPOS_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_ROW_VNUM_VAL_SHIFT                                                    (1U)
#define IPIPE_BSC_ROW_VNUM_VAL_MASK                                                     (0x00001ffeU)

#define IPIPE_BSC_ROW_VNUM_VAL_0_SHIFT                                                  (0U)
#define IPIPE_BSC_ROW_VNUM_VAL_0_MASK                                                   (0x00000001U)

#define IPIPE_BSC_ROW_VNUM_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_ROW_VNUM_RESERVED_MASK                                                (0xffffe000U)

#define IPIPE_BSC_ROW_VSKIP_VAL_SHIFT                                                   (0U)
#define IPIPE_BSC_ROW_VSKIP_VAL_MASK                                                    (0x0000001fU)

#define IPIPE_BSC_ROW_VSKIP_RESERVED_SHIFT                                              (5U)
#define IPIPE_BSC_ROW_VSKIP_RESERVED_MASK                                               (0x0000ffe0U)

#define IPIPE_BSC_ROW_VSKIP_RESERVED1_SHIFT                                             (16U)
#define IPIPE_BSC_ROW_VSKIP_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_BSC_ROW_HPOS_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_ROW_HPOS_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_ROW_HPOS_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_ROW_HPOS_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_ROW_HPOS_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_ROW_HPOS_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_ROW_HNUM_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_ROW_HNUM_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_ROW_HNUM_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_ROW_HNUM_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_ROW_HNUM_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_ROW_HNUM_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_ROW_HSKIP_VAL_SHIFT                                                   (0U)
#define IPIPE_BSC_ROW_HSKIP_VAL_MASK                                                    (0x0000001fU)

#define IPIPE_BSC_ROW_HSKIP_RESERVED_SHIFT                                              (5U)
#define IPIPE_BSC_ROW_HSKIP_RESERVED_MASK                                               (0x0000ffe0U)

#define IPIPE_BSC_ROW_HSKIP_RESERVED1_SHIFT                                             (16U)
#define IPIPE_BSC_ROW_HSKIP_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_BSC_COL_VCT_VAL_SHIFT                                                     (0U)
#define IPIPE_BSC_COL_VCT_VAL_MASK                                                      (0x00000003U)

#define IPIPE_BSC_COL_VCT_RESERVED_SHIFT                                                (2U)
#define IPIPE_BSC_COL_VCT_RESERVED_MASK                                                 (0x0000fffcU)

#define IPIPE_BSC_COL_VCT_RESERVED1_SHIFT                                               (16U)
#define IPIPE_BSC_COL_VCT_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_BSC_COL_SHF_VAL_SHIFT                                                     (0U)
#define IPIPE_BSC_COL_SHF_VAL_MASK                                                      (0x00000007U)

#define IPIPE_BSC_COL_SHF_RESERVED_SHIFT                                                (3U)
#define IPIPE_BSC_COL_SHF_RESERVED_MASK                                                 (0x0000fff8U)

#define IPIPE_BSC_COL_SHF_RESERVED1_SHIFT                                               (16U)
#define IPIPE_BSC_COL_SHF_RESERVED1_MASK                                                (0xffff0000U)

#define IPIPE_BSC_COL_VPOS_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_COL_VPOS_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_COL_VPOS_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_COL_VPOS_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_COL_VPOS_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_COL_VPOS_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_COL_VNUM_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_COL_VNUM_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_COL_VNUM_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_COL_VNUM_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_COL_VNUM_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_COL_VNUM_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_COL_VSKIP_VAL_SHIFT                                                   (0U)
#define IPIPE_BSC_COL_VSKIP_VAL_MASK                                                    (0x0000001fU)

#define IPIPE_BSC_COL_VSKIP_RESERVED_SHIFT                                              (5U)
#define IPIPE_BSC_COL_VSKIP_RESERVED_MASK                                               (0x0000ffe0U)

#define IPIPE_BSC_COL_VSKIP_RESERVED1_SHIFT                                             (16U)
#define IPIPE_BSC_COL_VSKIP_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_BSC_COL_HPOS_VAL_SHIFT                                                    (0U)
#define IPIPE_BSC_COL_HPOS_VAL_MASK                                                     (0x00001fffU)

#define IPIPE_BSC_COL_HPOS_RESERVED1_SHIFT                                              (16U)
#define IPIPE_BSC_COL_HPOS_RESERVED1_MASK                                               (0xffff0000U)

#define IPIPE_BSC_COL_HPOS_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_COL_HPOS_RESERVED_MASK                                                (0x0000e000U)

#define IPIPE_BSC_COL_HNUM_VAL_SHIFT                                                    (1U)
#define IPIPE_BSC_COL_HNUM_VAL_MASK                                                     (0x00001ffeU)

#define IPIPE_BSC_COL_HNUM_VAL_0_SHIFT                                                  (0U)
#define IPIPE_BSC_COL_HNUM_VAL_0_MASK                                                   (0x00000001U)

#define IPIPE_BSC_COL_HNUM_RESERVED_SHIFT                                               (13U)
#define IPIPE_BSC_COL_HNUM_RESERVED_MASK                                                (0xffffe000U)

#define IPIPE_BSC_COL_HSKIP_VAL_SHIFT                                                   (0U)
#define IPIPE_BSC_COL_HSKIP_VAL_MASK                                                    (0x0000001fU)

#define IPIPE_BSC_COL_HSKIP_RESERVED_SHIFT                                              (5U)
#define IPIPE_BSC_COL_HSKIP_RESERVED_MASK                                               (0x0000ffe0U)

#define IPIPE_BSC_COL_HSKIP_RESERVED1_SHIFT                                             (16U)
#define IPIPE_BSC_COL_HSKIP_RESERVED1_MASK                                              (0xffff0000U)

#define IPIPE_YUV_INP_OFST_Y_SHIFT                                                      (0U)
#define IPIPE_YUV_INP_OFST_Y_MASK                                                       (0x000001ffU)

#define IPIPE_YUV_INP_OFST_Y_RESERVED_SHIFT                                             (9U)
#define IPIPE_YUV_INP_OFST_Y_RESERVED_MASK                                              (0xfffffe00U)

#define IPIPE_YUV_INP_OFST_CB_SHIFT                                                     (0U)
#define IPIPE_YUV_INP_OFST_CB_MASK                                                      (0x000001ffU)

#define IPIPE_YUV_INP_OFST_CB_RESERVED_SHIFT                                            (9U)
#define IPIPE_YUV_INP_OFST_CB_RESERVED_MASK                                             (0xfffffe00U)

#define IPIPE_YUV_INP_OFST_CR_SHIFT                                                     (0U)
#define IPIPE_YUV_INP_OFST_CR_MASK                                                      (0x000001ffU)

#define IPIPE_YUV_INP_OFST_CR_RESERVED_SHIFT                                            (9U)
#define IPIPE_YUV_INP_OFST_CR_RESERVED_MASK                                             (0xfffffe00U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_IPIPE_H_ */

