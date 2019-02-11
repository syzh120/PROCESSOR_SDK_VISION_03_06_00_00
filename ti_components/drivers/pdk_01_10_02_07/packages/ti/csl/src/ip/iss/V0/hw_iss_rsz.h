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

#ifndef HW_ISS_RSZ_H_
#define HW_ISS_RSZ_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define RSZ_REVISION                                                (0x0U)
#define RSZ_SYSCONFIG                                               (0x4U)
#define RSZ_SYSSTATUS                                               (0x8U)
#define RSZ_IN_FIFO_CTRL                                            (0xcU)
#define RSZ_GNC                                                     (0x10U)
#define RSZ_FRACDIV                                                 (0x14U)
#define RSZ_SRC_EN                                                  (0x20U)
#define RSZ_SRC_MODE                                                (0x24U)
#define RSZ_SRC_FMT0                                                (0x28U)
#define RSZ_SRC_FMT1                                                (0x2cU)
#define RSZ_SRC_VPS                                                 (0x30U)
#define RSZ_SRC_VSZ                                                 (0x34U)
#define RSZ_SRC_HPS                                                 (0x38U)
#define RSZ_SRC_HSZ                                                 (0x3cU)
#define RSZ_DMA_RZA                                                 (0x40U)
#define RSZ_DMA_RZB                                                 (0x44U)
#define RSZ_DMA_STA                                                 (0x48U)
#define RSZ_GCK_MMR                                                 (0x4cU)
#define RSZ_RESERVED                                                (0x50U)
#define RSZ_GCK_SDR                                                 (0x54U)
#define RSZ_IRQ_RZA                                                 (0x58U)
#define RSZ_IRQ_RZB                                                 (0x5cU)
#define RSZ_YUV_Y_MIN                                               (0x60U)
#define RSZ_YUV_Y_MAX                                               (0x64U)
#define RSZ_YUV_C_MIN                                               (0x68U)
#define RSZ_YUV_C_MAX                                               (0x6cU)
#define RSZ_YUV_PHS                                                 (0x70U)
#define RSZ_SEQ                                                     (0x74U)
#define RZA_EN                                                      (0x78U)
#define RZA_MODE                                                    (0x7cU)
#define RZA_420                                                     (0x80U)
#define RZA_I_VPS                                                   (0x84U)
#define RZA_I_HPS                                                   (0x88U)
#define RZA_O_VSZ                                                   (0x8cU)
#define RZA_O_HSZ                                                   (0x90U)
#define RZA_V_PHS_Y                                                 (0x94U)
#define RZA_V_PHS_C                                                 (0x98U)
#define RZA_V_DIF                                                   (0x9cU)
#define RZA_V_TYP                                                   (0xa0U)
#define RZA_V_LPF                                                   (0xa4U)
#define RZA_H_PHS                                                   (0xa8U)
#define RZA_H_PHS_ADJ                                               (0xacU)
#define RZA_H_DIF                                                   (0xb0U)
#define RZA_H_TYP                                                   (0xb4U)
#define RZA_H_LPF                                                   (0xb8U)
#define RZA_DWN_EN                                                  (0xbcU)
#define RZA_DWN_AV                                                  (0xc0U)
#define RZA_RGB_EN                                                  (0xc4U)
#define RZA_RGB_TYP                                                 (0xc8U)
#define RZA_RGB_BLD                                                 (0xccU)
#define RZA_SDR_Y_BAD_H                                             (0xd0U)
#define RZA_SDR_Y_BAD_L                                             (0xd4U)
#define RZA_SDR_Y_SAD_H                                             (0xd8U)
#define RZA_SDR_Y_SAD_L                                             (0xdcU)
#define RZA_SDR_Y_OFT                                               (0xe0U)
#define RZA_SDR_Y_PTR_S                                             (0xe4U)
#define RZA_SDR_Y_PTR_E                                             (0xe8U)
#define RZA_SDR_C_BAD_H                                             (0xecU)
#define RZA_SDR_C_BAD_L                                             (0xf0U)
#define RZA_SDR_C_SAD_H                                             (0xf4U)
#define RZA_SDR_C_SAD_L                                             (0xf8U)
#define RZA_SDR_C_OFT                                               (0xfcU)
#define RZA_SDR_C_PTR_S                                             (0x100U)
#define RZA_SDR_C_PTR_E                                             (0x104U)
#define RZB_EN                                                      (0x108U)
#define RZB_MODE                                                    (0x10cU)
#define RZB_420                                                     (0x110U)
#define RZB_I_VPS                                                   (0x114U)
#define RZB_I_HPS                                                   (0x118U)
#define RZB_O_VSZ                                                   (0x11cU)
#define RZB_O_HSZ                                                   (0x120U)
#define RZB_V_PHS_Y                                                 (0x124U)
#define RZB_V_PHS_C                                                 (0x128U)
#define RZB_V_DIF                                                   (0x12cU)
#define RZB_V_TYP                                                   (0x130U)
#define RZB_V_LPF                                                   (0x134U)
#define RZB_H_PHS                                                   (0x138U)
#define RZB_H_PHS_ADJ                                               (0x13cU)
#define RZB_H_DIF                                                   (0x140U)
#define RZB_H_TYP                                                   (0x144U)
#define RZB_H_LPF                                                   (0x148U)
#define RZB_DWN_EN                                                  (0x14cU)
#define RZB_DWN_AV                                                  (0x150U)
#define RZB_RGB_EN                                                  (0x154U)
#define RZB_RGB_TYP                                                 (0x158U)
#define RZB_RGB_BLD                                                 (0x15cU)
#define RZB_SDR_Y_BAD_H                                             (0x160U)
#define RZB_SDR_Y_BAD_L                                             (0x164U)
#define RZB_SDR_Y_SAD_H                                             (0x168U)
#define RZB_SDR_Y_SAD_L                                             (0x16cU)
#define RZB_SDR_Y_OFT                                               (0x170U)
#define RZB_SDR_Y_PTR_S                                             (0x174U)
#define RZB_SDR_Y_PTR_E                                             (0x178U)
#define RZB_SDR_C_BAD_H                                             (0x17cU)
#define RZB_SDR_C_BAD_L                                             (0x180U)
#define RZB_SDR_C_SAD_H                                             (0x184U)
#define RZB_SDR_C_SAD_L                                             (0x188U)
#define RZB_SDR_C_OFT                                               (0x18cU)
#define RZB_SDR_C_PTR_S                                             (0x190U)
#define RZB_SDR_C_PTR_E                                             (0x194U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define RSZ_REVISION_REV_SHIFT                                                          (0U)
#define RSZ_REVISION_REV_MASK                                                           (0x000000ffU)

#define RSZ_REVISION_RESERVED_SHIFT                                                     (8U)
#define RSZ_REVISION_RESERVED_MASK                                                      (0xffffff00U)

#define RSZ_SYSCONFIG_RSZA_CLK_EN_SHIFT                                                 (8U)
#define RSZ_SYSCONFIG_RSZA_CLK_EN_MASK                                                  (0x00000100U)
#define RSZ_SYSCONFIG_RSZA_CLK_EN_NEWENUM1                                               (0U)
#define RSZ_SYSCONFIG_RSZA_CLK_EN_NEWENUM2                                               (1U)

#define RSZ_SYSCONFIG_RSZB_CLK_EN_SHIFT                                                 (9U)
#define RSZ_SYSCONFIG_RSZB_CLK_EN_MASK                                                  (0x00000200U)
#define RSZ_SYSCONFIG_RSZB_CLK_EN_NEWENUM1                                               (0U)
#define RSZ_SYSCONFIG_RSZB_CLK_EN_NEWENUM2                                               (1U)

#define RSZ_SYSCONFIG_AUTOGATING_SHIFT                                                  (0U)
#define RSZ_SYSCONFIG_AUTOGATING_MASK                                                   (0x00000001U)
#define RSZ_SYSCONFIG_AUTOGATING_NEWENUM1                                                (0U)
#define RSZ_SYSCONFIG_AUTOGATING_NEWENUM2                                                (1U)

#define RSZ_SYSCONFIG_RESERVED_SHIFT                                                    (2U)
#define RSZ_SYSCONFIG_RESERVED_MASK                                                     (0x000000fcU)

#define RSZ_SYSCONFIG_RESERVED1_SHIFT                                                   (10U)
#define RSZ_SYSCONFIG_RESERVED1_MASK                                                    (0xfffffc00U)

#define RSZ_SYSCONFIG_RESERVED2_SHIFT                                                   (1U)
#define RSZ_SYSCONFIG_RESERVED2_MASK                                                    (0x00000002U)

#define RSZ_SYSSTATUS_RESERVED_SHIFT                                                    (1U)
#define RSZ_SYSSTATUS_RESERVED_MASK                                                     (0xfffffffeU)

#define RSZ_SYSSTATUS_RESERVED1_SHIFT                                                   (0U)
#define RSZ_SYSSTATUS_RESERVED1_MASK                                                    (0x00000001U)

#define RSZ_IN_FIFO_CTRL_THRLD_HIGH_SHIFT                                               (0U)
#define RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK                                                (0x00001fffU)

#define RSZ_IN_FIFO_CTRL_THRLD_LOW_SHIFT                                                (16U)
#define RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK                                                 (0x1fff0000U)

#define RSZ_IN_FIFO_CTRL_RESERVED_SHIFT                                                 (13U)
#define RSZ_IN_FIFO_CTRL_RESERVED_MASK                                                  (0x0000e000U)

#define RSZ_IN_FIFO_CTRL_RESERVED1_SHIFT                                                (29U)
#define RSZ_IN_FIFO_CTRL_RESERVED1_MASK                                                 (0xe0000000U)

#define RSZ_GNC_RSZB_MEM_LINE_SIZE_SHIFT                                                (16U)
#define RSZ_GNC_RSZB_MEM_LINE_SIZE_MASK                                                 (0x1fff0000U)

#define RSZ_GNC_RSZA_MEM_LINE_SIZE_SHIFT                                                (0U)
#define RSZ_GNC_RSZA_MEM_LINE_SIZE_MASK                                                 (0x00001fffU)

#define RSZ_GNC_RESERVED_SHIFT                                                          (13U)
#define RSZ_GNC_RESERVED_MASK                                                           (0x0000e000U)

#define RSZ_GNC_RESERVED1_SHIFT                                                         (29U)
#define RSZ_GNC_RESERVED1_MASK                                                          (0xe0000000U)

#define RSZ_FRACDIV_SHIFT                                                               (0U)
#define RSZ_FRACDIV_MASK                                                                (0x0000ffffU)

#define RSZ_FRACDIV_RESERVED_SHIFT                                                      (16U)
#define RSZ_FRACDIV_RESERVED_MASK                                                       (0xffff0000U)

#define RSZ_SRC_EN_SHIFT                                                                (0U)
#define RSZ_SRC_EN_MASK                                                                 (0x00000001U)
#define RSZ_SRC_EN_NEWENUM1                                                              (0U)
#define RSZ_SRC_EN_NEWENUM2                                                              (1U)

#define RSZ_SRC_EN_RESERVED_SHIFT                                                       (1U)
#define RSZ_SRC_EN_RESERVED_MASK                                                        (0xfffffffeU)

#define RSZ_SRC_MODE_OST_SHIFT                                                          (0U)
#define RSZ_SRC_MODE_OST_MASK                                                           (0x00000001U)
#define RSZ_SRC_MODE_OST_NEWENUM1                                                        (0U)
#define RSZ_SRC_MODE_OST_NEWENUM2                                                        (1U)

#define RSZ_SRC_MODE_WRT_SHIFT                                                          (1U)
#define RSZ_SRC_MODE_WRT_MASK                                                           (0x00000002U)
#define RSZ_SRC_MODE_WRT_NEWENUM1                                                        (0U)
#define RSZ_SRC_MODE_WRT_NEWENUM2                                                        (1U)

#define RSZ_SRC_MODE_RESERVED_SHIFT                                                     (2U)
#define RSZ_SRC_MODE_RESERVED_MASK                                                      (0xfffffffcU)

#define RSZ_SRC_FMT0_SEL_SHIFT                                                          (0U)
#define RSZ_SRC_FMT0_SEL_MASK                                                           (0x00000001U)
#define RSZ_SRC_FMT0_SEL_NEWENUM1                                                        (0U)
#define RSZ_SRC_FMT0_SEL                                                                 (1U)

#define RSZ_SRC_FMT0_BYPASS_SHIFT                                                       (1U)
#define RSZ_SRC_FMT0_BYPASS_MASK                                                        (0x00000002U)
#define RSZ_SRC_FMT0_BYPASS_NEWENUM1                                                     (0U)
#define RSZ_SRC_FMT0_BYPASS_NEWENUM2                                                     (1U)

#define RSZ_SRC_FMT0_RESERVED_SHIFT                                                     (2U)
#define RSZ_SRC_FMT0_RESERVED_MASK                                                      (0xfffffffcU)

#define RSZ_SRC_FMT1_RAW_SHIFT                                                          (0U)
#define RSZ_SRC_FMT1_RAW_MASK                                                           (0x00000001U)
#define RSZ_SRC_FMT1_RAW_NEWENUM1                                                        (0U)
#define RSZ_SRC_FMT1_RAW_NEWENUM2                                                        (1U)

#define RSZ_SRC_FMT1_IN420_SHIFT                                                        (1U)
#define RSZ_SRC_FMT1_IN420_MASK                                                         (0x00000002U)
#define RSZ_SRC_FMT1_IN420_NEWENUM1                                                      (0U)
#define RSZ_SRC_FMT1_IN420_NEWENUM2                                                      (1U)

#define RSZ_SRC_FMT1_COL_SHIFT                                                          (2U)
#define RSZ_SRC_FMT1_COL_MASK                                                           (0x00000004U)
#define RSZ_SRC_FMT1_COL_NEWENUM1                                                        (0U)
#define RSZ_SRC_FMT1_COL_NEWENUM2                                                        (1U)

#define RSZ_SRC_FMT1_RESERVED_SHIFT                                                     (4U)
#define RSZ_SRC_FMT1_RESERVED_MASK                                                      (0xfffffff0U)

#define RSZ_SRC_FMT1_CHR_SHIFT                                                          (3U)
#define RSZ_SRC_FMT1_CHR_MASK                                                           (0x00000008U)
#define RSZ_SRC_FMT1_CHR_NORMAL                                                          (0U)
#define RSZ_SRC_FMT1_CHR_FLIPPED                                                         (1U)

#define RSZ_SRC_VPS_SHIFT                                                               (0U)
#define RSZ_SRC_VPS_MASK                                                                (0x0000ffffU)

#define RSZ_SRC_VPS_RESERVED_SHIFT                                                      (16U)
#define RSZ_SRC_VPS_RESERVED_MASK                                                       (0xffff0000U)

#define RSZ_SRC_VSZ_SHIFT                                                               (0U)
#define RSZ_SRC_VSZ_MASK                                                                (0x00001fffU)

#define RSZ_SRC_VSZ_RESERVED_SHIFT                                                      (13U)
#define RSZ_SRC_VSZ_RESERVED_MASK                                                       (0xffffe000U)

#define RSZ_SRC_HPS_SHIFT                                                               (0U)
#define RSZ_SRC_HPS_MASK                                                                (0x0000ffffU)

#define RSZ_SRC_HPS_RESERVED_SHIFT                                                      (16U)
#define RSZ_SRC_HPS_RESERVED_MASK                                                       (0xffff0000U)

#define RSZ_SRC_HSZ_SHIFT                                                               (0U)
#define RSZ_SRC_HSZ_MASK                                                                (0x00001fffU)

#define RSZ_SRC_HSZ_RESERVED1_SHIFT                                                     (13U)
#define RSZ_SRC_HSZ_RESERVED1_MASK                                                      (0xffffe000U)

#define RSZ_DMA_RZA_SHIFT                                                               (0U)
#define RSZ_DMA_RZA_MASK                                                                (0x0000ffffU)

#define RSZ_DMA_RZA_RESERVED_SHIFT                                                      (16U)
#define RSZ_DMA_RZA_RESERVED_MASK                                                       (0xffff0000U)

#define RSZ_DMA_RZB_SHIFT                                                               (0U)
#define RSZ_DMA_RZB_MASK                                                                (0x0000ffffU)

#define RSZ_DMA_RZB_RESERVED_SHIFT                                                      (16U)
#define RSZ_DMA_RZB_RESERVED_MASK                                                       (0xffff0000U)

#define RSZ_DMA_STA_STATUS_SHIFT                                                        (0U)
#define RSZ_DMA_STA_STATUS_MASK                                                         (0x00000001U)
#define RSZ_DMA_STA_STATUS_NEWENUM1                                                      (0U)
#define RSZ_DMA_STA_STATUS_NEWENUM2                                                      (1U)

#define RSZ_DMA_STA_RESERVED_SHIFT                                                      (1U)
#define RSZ_DMA_STA_RESERVED_MASK                                                       (0xfffffffeU)

#define RSZ_GCK_MMR_SHIFT                                                               (0U)
#define RSZ_GCK_MMR_MASK                                                                (0x00000001U)
#define RSZ_GCK_MMR_NEWENUM1                                                             (0U)
#define RSZ_GCK_MMR_NEWENUM2                                                             (1U)

#define RSZ_GCK_MMR_RESERVED_SHIFT                                                      (1U)
#define RSZ_GCK_MMR_RESERVED_MASK                                                       (0xfffffffeU)

#define RSZ_RESERVED_SHIFT                                                              (0U)
#define RSZ_RESERVED_MASK                                                               (0xffffffffU)

#define RSZ_GCK_SDR_CORE_SHIFT                                                          (0U)
#define RSZ_GCK_SDR_CORE_MASK                                                           (0x00000001U)
#define RSZ_GCK_SDR_CORE_NEWENUM1                                                        (0U)
#define RSZ_GCK_SDR_CORE_NEWENUM2                                                        (1U)

#define RSZ_GCK_SDR_RESERVED_SHIFT                                                      (1U)
#define RSZ_GCK_SDR_RESERVED_MASK                                                       (0xfffffffeU)

#define RSZ_IRQ_RZA_SHIFT                                                               (0U)
#define RSZ_IRQ_RZA_MASK                                                                (0x00001fffU)

#define RSZ_IRQ_RZA_ICMA_EN_SHIFT                                                       (16U)
#define RSZ_IRQ_RZA_ICMA_EN_MASK                                                        (0x00010000U)
#define RSZ_IRQ_RZA_ICMA_EN_DISABLE                                                      (0U)
#define RSZ_IRQ_RZA_ICMA_EN_ENABLE                                                       (1U)

#define RSZ_IRQ_RZA_RESERVED_SHIFT                                                      (13U)
#define RSZ_IRQ_RZA_RESERVED_MASK                                                       (0x0000e000U)

#define RSZ_IRQ_RZA_ICMA_EOF_SHIFT                                                      (17U)
#define RSZ_IRQ_RZA_ICMA_EOF_MASK                                                       (0x00020000U)
#define RSZ_IRQ_RZA_ICMA_EOF_DISABLE                                                     (0U)
#define RSZ_IRQ_RZA_ICMA_EOF_ENABLE                                                      (1U)

#define RSZ_IRQ_RZA_ICMA_CHR_EN_SHIFT                                                   (20U)
#define RSZ_IRQ_RZA_ICMA_CHR_EN_MASK                                                    (0x00100000U)
#define RSZ_IRQ_RZA_ICMA_CHR_EN_DISABLE                                                  (0U)
#define RSZ_IRQ_RZA_ICMA_CHR_EN_ENABLE                                                   (1U)

#define RSZ_IRQ_RZA_ICMA_CHR_EOF_SHIFT                                                  (21U)
#define RSZ_IRQ_RZA_ICMA_CHR_EOF_MASK                                                   (0x00200000U)
#define RSZ_IRQ_RZA_ICMA_CHR_EOF_DISABLE                                                 (0U)
#define RSZ_IRQ_RZA_ICMA_CHR_EOF_ENABLE                                                  (1U)

#define RSZ_IRQ_RZA_RESERVED1_SHIFT                                                     (18U)
#define RSZ_IRQ_RZA_RESERVED1_MASK                                                      (0x000c0000U)

#define RSZ_IRQ_RZA_RESERVED2_SHIFT                                                     (22U)
#define RSZ_IRQ_RZA_RESERVED2_MASK                                                      (0x00c00000U)

#define RSZ_IRQ_RZA_ICMA_CTRL_COL_SHIFT                                                 (24U)
#define RSZ_IRQ_RZA_ICMA_CTRL_COL_MASK                                                  (0x01000000U)
#define RSZ_IRQ_RZA_ICMA_CTRL_COL_LUMA                                                   (0U)
#define RSZ_IRQ_RZA_ICMA_CTRL_COL_CHROMA                                                 (1U)

#define RSZ_IRQ_RZA_RESERVED3_SHIFT                                                     (25U)
#define RSZ_IRQ_RZA_RESERVED3_MASK                                                      (0xfe000000U)

#define RSZ_IRQ_RZB_SHIFT                                                               (0U)
#define RSZ_IRQ_RZB_MASK                                                                (0x00001fffU)

#define RSZ_IRQ_RZB_ICMB_EN_SHIFT                                                       (16U)
#define RSZ_IRQ_RZB_ICMB_EN_MASK                                                        (0x00010000U)
#define RSZ_IRQ_RZB_ICMB_EN_DISABLE                                                      (0U)
#define RSZ_IRQ_RZB_ICMB_EN_ENABLE                                                       (1U)

#define RSZ_IRQ_RZB_RESERVED_SHIFT                                                      (13U)
#define RSZ_IRQ_RZB_RESERVED_MASK                                                       (0x0000e000U)

#define RSZ_IRQ_RZB_ICMB_EOF_SHIFT                                                      (17U)
#define RSZ_IRQ_RZB_ICMB_EOF_MASK                                                       (0x00020000U)
#define RSZ_IRQ_RZB_ICMB_EOF_DISABLE                                                     (0U)
#define RSZ_IRQ_RZB_ICMB_EOF_ENABLE                                                      (1U)

#define RSZ_IRQ_RZB_ICMB_CHR_EN_SHIFT                                                   (20U)
#define RSZ_IRQ_RZB_ICMB_CHR_EN_MASK                                                    (0x00100000U)
#define RSZ_IRQ_RZB_ICMB_CHR_EN_DISABLE                                                  (0U)
#define RSZ_IRQ_RZB_ICMB_CHR_EN_ENABLE                                                   (1U)

#define RSZ_IRQ_RZB_ICMB_CHR_EOF_SHIFT                                                  (21U)
#define RSZ_IRQ_RZB_ICMB_CHR_EOF_MASK                                                   (0x00200000U)
#define RSZ_IRQ_RZB_ICMB_CHR_EOF_DISABLE                                                 (0U)
#define RSZ_IRQ_RZB_ICMB_CHR_EOF_ENABLE                                                  (1U)

#define RSZ_IRQ_RZB_RESERVED1_SHIFT                                                     (18U)
#define RSZ_IRQ_RZB_RESERVED1_MASK                                                      (0x000c0000U)

#define RSZ_IRQ_RZB_RESERVED2_SHIFT                                                     (22U)
#define RSZ_IRQ_RZB_RESERVED2_MASK                                                      (0x00c00000U)

#define RSZ_IRQ_RZB_ICMB_CTRL_COL_SHIFT                                                 (24U)
#define RSZ_IRQ_RZB_ICMB_CTRL_COL_MASK                                                  (0x01000000U)
#define RSZ_IRQ_RZB_ICMB_CTRL_COL_LUMA                                                   (0U)
#define RSZ_IRQ_RZB_ICMB_CTRL_COL_CHROMA                                                 (1U)

#define RSZ_IRQ_RZB_RESERVED3_SHIFT                                                     (25U)
#define RSZ_IRQ_RZB_RESERVED3_MASK                                                      (0xfe000000U)

#define RSZ_YUV_Y_MIN_SHIFT                                                             (0U)
#define RSZ_YUV_Y_MIN_MASK                                                              (0x000000ffU)

#define RSZ_YUV_Y_MIN_RESERVED_SHIFT                                                    (8U)
#define RSZ_YUV_Y_MIN_RESERVED_MASK                                                     (0xffffff00U)

#define RSZ_YUV_Y_MAX_SHIFT                                                             (0U)
#define RSZ_YUV_Y_MAX_MASK                                                              (0x000000ffU)

#define RSZ_YUV_Y_MAX_RESERVED_SHIFT                                                    (8U)
#define RSZ_YUV_Y_MAX_RESERVED_MASK                                                     (0xffffff00U)

#define RSZ_YUV_C_MIN_SHIFT                                                             (0U)
#define RSZ_YUV_C_MIN_MASK                                                              (0x000000ffU)

#define RSZ_YUV_C_MIN_RESERVED_SHIFT                                                    (8U)
#define RSZ_YUV_C_MIN_RESERVED_MASK                                                     (0xffffff00U)

#define RSZ_YUV_C_MAX_SHIFT                                                             (0U)
#define RSZ_YUV_C_MAX_MASK                                                              (0x000000ffU)

#define RSZ_YUV_C_MAX_RESERVED_SHIFT                                                    (8U)
#define RSZ_YUV_C_MAX_RESERVED_MASK                                                     (0xffffff00U)

#define RSZ_YUV_PHS_POS_SHIFT                                                           (0U)
#define RSZ_YUV_PHS_POS_MASK                                                            (0x00000001U)
#define RSZ_YUV_PHS_POS_NEWENUM1                                                         (0U)
#define RSZ_YUV_PHS_POS_NEWENUM2                                                         (1U)

#define RSZ_YUV_PHS_RESERVED_SHIFT                                                      (1U)
#define RSZ_YUV_PHS_RESERVED_MASK                                                       (0xfffffffeU)

#define RSZ_SEQ_HRVA_SHIFT                                                              (0U)
#define RSZ_SEQ_HRVA_MASK                                                               (0x00000001U)
#define RSZ_SEQ_HRVA_NEWENUM1                                                            (0U)
#define RSZ_SEQ_HRVA_NEWENUM2                                                            (1U)

#define RSZ_SEQ_VRVA_SHIFT                                                              (1U)
#define RSZ_SEQ_VRVA_MASK                                                               (0x00000002U)
#define RSZ_SEQ_VRVA_NEWENUM1                                                            (0U)
#define RSZ_SEQ_VRVA_NEWENUM2                                                            (1U)

#define RSZ_SEQ_HRVB_SHIFT                                                              (2U)
#define RSZ_SEQ_HRVB_MASK                                                               (0x00000004U)
#define RSZ_SEQ_HRVB_NEWENUM1                                                            (0U)
#define RSZ_SEQ_HRVB_NEWENUM2                                                            (1U)

#define RSZ_SEQ_VRVB_SHIFT                                                              (3U)
#define RSZ_SEQ_VRVB_MASK                                                               (0x00000008U)
#define RSZ_SEQ_VRVB_NEWENUM1                                                            (0U)
#define RSZ_SEQ_VRVB_NEWENUM2                                                            (1U)

#define RSZ_SEQ_CRV_SHIFT                                                               (4U)
#define RSZ_SEQ_CRV_MASK                                                                (0x00000010U)
#define RSZ_SEQ_CRV_NEWENUM1                                                             (0U)
#define RSZ_SEQ_CRV_NEWENUM2                                                             (1U)

#define RSZ_SEQ_RESERVED_SHIFT                                                          (5U)
#define RSZ_SEQ_RESERVED_MASK                                                           (0xffffffe0U)

#define RZA_EN_SHIFT                                                                    (0U)
#define RZA_EN_MASK                                                                     (0x00000001U)
#define RZA_EN_NEWENUM1                                                                  (0U)
#define RZA_EN_NEWENUM2                                                                  (1U)

#define RZA_EN_RESERVED_SHIFT                                                           (1U)
#define RZA_EN_RESERVED_MASK                                                            (0xfffffffeU)

#define RZA_MODE_SHIFT                                                                  (0U)
#define RZA_MODE_MASK                                                                   (0x00000001U)
#define RZA_MODE_NEWENUM1                                                                (0U)
#define RZA_MODE_NEWENUM2                                                                (1U)

#define RZA_MODE_RESERVED_SHIFT                                                         (1U)
#define RZA_MODE_RESERVED_MASK                                                          (0xfffffffeU)

#define RZA_420_YEN_SHIFT                                                               (0U)
#define RZA_420_YEN_MASK                                                                (0x00000001U)
#define RZA_420_YEN_NEWENUM1                                                             (0U)
#define RZA_420_YEN_NEWENUM2                                                             (1U)

#define RZA_420_CEN_SHIFT                                                               (1U)
#define RZA_420_CEN_MASK                                                                (0x00000002U)
#define RZA_420_CEN_NEWENUM1                                                             (0U)
#define RZA_420_CEN_NEWENUM2                                                             (1U)

#define RZA_420_RESERVED_SHIFT                                                          (2U)
#define RZA_420_RESERVED_MASK                                                           (0xfffffffcU)

#define RZA_I_VPS_SHIFT                                                                 (0U)
#define RZA_I_VPS_MASK                                                                  (0x00001fffU)

#define RZA_I_VPS_RESERVED_SHIFT                                                        (13U)
#define RZA_I_VPS_RESERVED_MASK                                                         (0xffffe000U)

#define RZA_I_HPS_SHIFT                                                                 (0U)
#define RZA_I_HPS_MASK                                                                  (0x00001fffU)

#define RZA_I_HPS_RESERVED_SHIFT                                                        (13U)
#define RZA_I_HPS_RESERVED_MASK                                                         (0xffffe000U)

#define RZA_O_VSZ_SHIFT                                                                 (0U)
#define RZA_O_VSZ_MASK                                                                  (0x00001fffU)

#define RZA_O_VSZ_RESERVED_SHIFT                                                        (13U)
#define RZA_O_VSZ_RESERVED_MASK                                                         (0xffffe000U)

#define RZA_O_HSZ_SHIFT                                                                 (1U)
#define RZA_O_HSZ_MASK                                                                  (0x00001ffeU)

#define RZA_O_HSZ_LSB_SHIFT                                                             (0U)
#define RZA_O_HSZ_LSB_MASK                                                              (0x00000001U)

#define RZA_O_HSZ_RESERVED_SHIFT                                                        (13U)
#define RZA_O_HSZ_RESERVED_MASK                                                         (0xffffe000U)

#define RZA_V_PHS_Y_SHIFT                                                               (0U)
#define RZA_V_PHS_Y_MASK                                                                (0x00003fffU)

#define RZA_V_PHS_Y_RESERVED_SHIFT                                                      (14U)
#define RZA_V_PHS_Y_RESERVED_MASK                                                       (0xffffc000U)

#define RZA_V_PHS_C_SHIFT                                                               (0U)
#define RZA_V_PHS_C_MASK                                                                (0x00003fffU)

#define RZA_V_PHS_C_RESERVED_SHIFT                                                      (14U)
#define RZA_V_PHS_C_RESERVED_MASK                                                       (0xffffc000U)

#define RZA_V_DIF_SHIFT                                                                 (0U)
#define RZA_V_DIF_MASK                                                                  (0x00003fffU)

#define RZA_V_DIF_RESERVED_SHIFT                                                        (14U)
#define RZA_V_DIF_RESERVED_MASK                                                         (0xffffc000U)

#define RZA_V_TYP_Y_SHIFT                                                               (0U)
#define RZA_V_TYP_Y_MASK                                                                (0x00000001U)
#define RZA_V_TYP_Y_NEWENUM1                                                             (0U)
#define RZA_V_TYP_Y_NEWENUM2                                                             (1U)

#define RZA_V_TYP_C_SHIFT                                                               (1U)
#define RZA_V_TYP_C_MASK                                                                (0x00000002U)
#define RZA_V_TYP_C_NEWENUM1                                                             (0U)
#define RZA_V_TYP_C_NEWENUM2                                                             (1U)

#define RZA_V_TYP_RESERVED_SHIFT                                                        (2U)
#define RZA_V_TYP_RESERVED_MASK                                                         (0xfffffffcU)

#define RZA_V_LPF_Y_SHIFT                                                               (0U)
#define RZA_V_LPF_Y_MASK                                                                (0x0000003fU)

#define RZA_V_LPF_C_SHIFT                                                               (6U)
#define RZA_V_LPF_C_MASK                                                                (0x00000fc0U)

#define RZA_V_LPF_RESERVED_SHIFT                                                        (12U)
#define RZA_V_LPF_RESERVED_MASK                                                         (0xfffff000U)

#define RZA_H_PHS_SHIFT                                                                 (0U)
#define RZA_H_PHS_MASK                                                                  (0x00003fffU)

#define RZA_H_PHS_RESERVED_SHIFT                                                        (14U)
#define RZA_H_PHS_RESERVED_MASK                                                         (0xffffc000U)

#define RZA_H_PHS_ADJ_SHIFT                                                             (0U)
#define RZA_H_PHS_ADJ_MASK                                                              (0x000001ffU)

#define RZA_H_PHS_ADJ_RESERVED_SHIFT                                                    (9U)
#define RZA_H_PHS_ADJ_RESERVED_MASK                                                     (0xfffffe00U)

#define RZA_H_DIF_SHIFT                                                                 (0U)
#define RZA_H_DIF_MASK                                                                  (0x00003fffU)

#define RZA_H_DIF_RESERVED_SHIFT                                                        (14U)
#define RZA_H_DIF_RESERVED_MASK                                                         (0xffffc000U)

#define RZA_H_TYP_Y_SHIFT                                                               (0U)
#define RZA_H_TYP_Y_MASK                                                                (0x00000001U)
#define RZA_H_TYP_Y_NEWENUM1                                                             (0U)
#define RZA_H_TYP_Y_NEWENUM2                                                             (1U)

#define RZA_H_TYP_C_SHIFT                                                               (1U)
#define RZA_H_TYP_C_MASK                                                                (0x00000002U)
#define RZA_H_TYP_C_NEWENUM1                                                             (0U)
#define RZA_H_TYP_C_NEWENUM2                                                             (1U)

#define RZA_H_TYP_RESERVED_SHIFT                                                        (2U)
#define RZA_H_TYP_RESERVED_MASK                                                         (0xfffffffcU)

#define RZA_H_LPF_Y_SHIFT                                                               (0U)
#define RZA_H_LPF_Y_MASK                                                                (0x0000003fU)

#define RZA_H_LPF_C_SHIFT                                                               (6U)
#define RZA_H_LPF_C_MASK                                                                (0x00000fc0U)

#define RZA_H_LPF_RESERVED_SHIFT                                                        (12U)
#define RZA_H_LPF_RESERVED_MASK                                                         (0xfffff000U)

#define RZA_DWN_EN_SHIFT                                                                (0U)
#define RZA_DWN_EN_MASK                                                                 (0x00000001U)
#define RZA_DWN_EN_NEWENUM1                                                              (0U)
#define RZA_DWN_EN_NEWENUM2                                                              (1U)

#define RZA_DWN_EN_RESERVED_SHIFT                                                       (1U)
#define RZA_DWN_EN_RESERVED_MASK                                                        (0xfffffffeU)

#define RZA_DWN_AV_H_SHIFT                                                              (0U)
#define RZA_DWN_AV_H_MASK                                                               (0x00000007U)

#define RZA_DWN_AV_V_SHIFT                                                              (3U)
#define RZA_DWN_AV_V_MASK                                                               (0x00000038U)

#define RZA_DWN_AV_RESERVED_SHIFT                                                       (6U)
#define RZA_DWN_AV_RESERVED_MASK                                                        (0xffffffc0U)

#define RZA_RGB_EN_SHIFT                                                                (0U)
#define RZA_RGB_EN_MASK                                                                 (0x00000001U)
#define RZA_RGB_EN_NEWENUM1                                                              (0U)
#define RZA_RGB_EN_NEWENUM2                                                              (1U)

#define RZA_RGB_EN_RESERVED_SHIFT                                                       (1U)
#define RZA_RGB_EN_RESERVED_MASK                                                        (0xfffffffeU)

#define RZA_RGB_TYP_SHIFT                                                               (0U)
#define RZA_RGB_TYP_MASK                                                                (0x00000001U)
#define RZA_RGB_TYP_NEWENUM1                                                             (0U)
#define RZA_RGB_TYP_NEWENUM2                                                             (1U)

#define RZA_RGB_TYP_MSK0_SHIFT                                                          (1U)
#define RZA_RGB_TYP_MSK0_MASK                                                           (0x00000002U)
#define RZA_RGB_TYP_MSK0_NEWENUM1                                                        (0U)
#define RZA_RGB_TYP_MSK0_NEWENUM2                                                        (1U)

#define RZA_RGB_TYP_MSK1_SHIFT                                                          (2U)
#define RZA_RGB_TYP_MSK1_MASK                                                           (0x00000004U)
#define RZA_RGB_TYP_MSK1_NEWENUM1                                                        (0U)
#define RZA_RGB_TYP_MSK1_NEWENUM2                                                        (1U)

#define RZA_RGB_TYP_RESERVED_SHIFT                                                      (3U)
#define RZA_RGB_TYP_RESERVED_MASK                                                       (0xfffffff8U)

#define RZA_RGB_BLD_SHIFT                                                               (0U)
#define RZA_RGB_BLD_MASK                                                                (0x000000ffU)

#define RZA_RGB_BLD_RESERVED_SHIFT                                                      (8U)
#define RZA_RGB_BLD_RESERVED_MASK                                                       (0xffffff00U)

#define RZA_SDR_Y_BAD_H_SHIFT                                                           (0U)
#define RZA_SDR_Y_BAD_H_MASK                                                            (0x0000ffffU)

#define RZA_SDR_Y_BAD_H_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_Y_BAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_Y_BAD_L_SHIFT                                                           (0U)
#define RZA_SDR_Y_BAD_L_MASK                                                            (0x0000ffffU)

#define RZA_SDR_Y_BAD_L_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_Y_BAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_Y_SAD_H_SHIFT                                                           (0U)
#define RZA_SDR_Y_SAD_H_MASK                                                            (0x0000ffffU)

#define RZA_SDR_Y_SAD_H_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_Y_SAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_Y_SAD_L_SHIFT                                                           (0U)
#define RZA_SDR_Y_SAD_L_MASK                                                            (0x0000ffffU)

#define RZA_SDR_Y_SAD_L_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_Y_SAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_Y_OFT_SHIFT                                                             (0U)
#define RZA_SDR_Y_OFT_MASK                                                              (0x0001ffffU)

#define RZA_SDR_Y_OFT_RESERVED_SHIFT                                                    (17U)
#define RZA_SDR_Y_OFT_RESERVED_MASK                                                     (0xfffe0000U)

#define RZA_SDR_Y_PTR_S_SHIFT                                                           (0U)
#define RZA_SDR_Y_PTR_S_MASK                                                            (0x00001fffU)

#define RZA_SDR_Y_PTR_S_RESERVED_SHIFT                                                  (13U)
#define RZA_SDR_Y_PTR_S_RESERVED_MASK                                                   (0xffffe000U)

#define RZA_SDR_Y_PTR_E_SHIFT                                                           (0U)
#define RZA_SDR_Y_PTR_E_MASK                                                            (0x00001fffU)

#define RZA_SDR_Y_PTR_E_RESERVED_SHIFT                                                  (13U)
#define RZA_SDR_Y_PTR_E_RESERVED_MASK                                                   (0xffffe000U)

#define RZA_SDR_C_BAD_H_SHIFT                                                           (0U)
#define RZA_SDR_C_BAD_H_MASK                                                            (0x0000ffffU)

#define RZA_SDR_C_BAD_H_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_C_BAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_C_BAD_L_SHIFT                                                           (0U)
#define RZA_SDR_C_BAD_L_MASK                                                            (0x0000ffffU)

#define RZA_SDR_C_BAD_L_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_C_BAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_C_SAD_H_SHIFT                                                           (0U)
#define RZA_SDR_C_SAD_H_MASK                                                            (0x0000ffffU)

#define RZA_SDR_C_SAD_H_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_C_SAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_C_SAD_L_SHIFT                                                           (0U)
#define RZA_SDR_C_SAD_L_MASK                                                            (0x0000ffffU)

#define RZA_SDR_C_SAD_L_RESERVED_SHIFT                                                  (16U)
#define RZA_SDR_C_SAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZA_SDR_C_OFT_SHIFT                                                             (0U)
#define RZA_SDR_C_OFT_MASK                                                              (0x0001ffffU)

#define RZA_SDR_C_OFT_RESERVED_SHIFT                                                    (17U)
#define RZA_SDR_C_OFT_RESERVED_MASK                                                     (0xfffe0000U)

#define RZA_SDR_C_PTR_S_SHIFT                                                           (0U)
#define RZA_SDR_C_PTR_S_MASK                                                            (0x00001fffU)

#define RZA_SDR_C_PTR_S_RESERVED_SHIFT                                                  (13U)
#define RZA_SDR_C_PTR_S_RESERVED_MASK                                                   (0xffffe000U)

#define RZA_SDR_C_PTR_E_SHIFT                                                           (0U)
#define RZA_SDR_C_PTR_E_MASK                                                            (0x00001fffU)

#define RZA_SDR_C_PTR_E_RESERVED_SHIFT                                                  (13U)
#define RZA_SDR_C_PTR_E_RESERVED_MASK                                                   (0xffffe000U)

#define RZB_EN_SHIFT                                                                    (0U)
#define RZB_EN_MASK                                                                     (0x00000001U)
#define RZB_EN_NEWENUM1                                                                  (0U)
#define RZB_EN_NEWENUM2                                                                  (1U)

#define RZB_EN_RESERVED_SHIFT                                                           (1U)
#define RZB_EN_RESERVED_MASK                                                            (0xfffffffeU)

#define RZB_MODE_SHIFT                                                                  (0U)
#define RZB_MODE_MASK                                                                   (0x00000001U)
#define RZB_MODE_NEWENUM1                                                                (0U)
#define RZB_MODE_NEWENUM2                                                                (1U)

#define RZB_MODE_RESERVED_SHIFT                                                         (1U)
#define RZB_MODE_RESERVED_MASK                                                          (0xfffffffeU)

#define RZB_420_YEN_SHIFT                                                               (0U)
#define RZB_420_YEN_MASK                                                                (0x00000001U)
#define RZB_420_YEN_NEWENUM1                                                             (0U)
#define RZB_420_YEN_NEWENUM2                                                             (1U)

#define RZB_420_CEN_SHIFT                                                               (1U)
#define RZB_420_CEN_MASK                                                                (0x00000002U)
#define RZB_420_CEN_NEWENUM1                                                             (0U)
#define RZB_420_CEN_NEWENUM2                                                             (1U)

#define RZB_420_RESERVED_SHIFT                                                          (2U)
#define RZB_420_RESERVED_MASK                                                           (0xfffffffcU)

#define RZB_I_VPS_SHIFT                                                                 (0U)
#define RZB_I_VPS_MASK                                                                  (0x00001fffU)

#define RZB_I_VPS_RESERVED_SHIFT                                                        (13U)
#define RZB_I_VPS_RESERVED_MASK                                                         (0xffffe000U)

#define RZB_I_HPS_SHIFT                                                                 (0U)
#define RZB_I_HPS_MASK                                                                  (0x00001fffU)

#define RZB_I_HPS_RESERVED_SHIFT                                                        (13U)
#define RZB_I_HPS_RESERVED_MASK                                                         (0xffffe000U)

#define RZB_O_VSZ_SHIFT                                                                 (0U)
#define RZB_O_VSZ_MASK                                                                  (0x00001fffU)

#define RZB_O_VSZ_RESERVED_SHIFT                                                        (13U)
#define RZB_O_VSZ_RESERVED_MASK                                                         (0xffffe000U)

#define RZB_O_HSZ_SHIFT                                                                 (1U)
#define RZB_O_HSZ_MASK                                                                  (0x00001ffeU)

#define RZB_O_HSZ_LSB_SHIFT                                                             (0U)
#define RZB_O_HSZ_LSB_MASK                                                              (0x00000001U)

#define RZB_O_HSZ_RESERVED_SHIFT                                                        (13U)
#define RZB_O_HSZ_RESERVED_MASK                                                         (0xffffe000U)

#define RZB_V_PHS_Y_SHIFT                                                               (0U)
#define RZB_V_PHS_Y_MASK                                                                (0x00003fffU)

#define RZB_V_PHS_Y_RESERVED_SHIFT                                                      (14U)
#define RZB_V_PHS_Y_RESERVED_MASK                                                       (0xffffc000U)

#define RZB_V_PHS_C_SHIFT                                                               (0U)
#define RZB_V_PHS_C_MASK                                                                (0x00003fffU)

#define RZB_V_PHS_C_RESERVED_SHIFT                                                      (14U)
#define RZB_V_PHS_C_RESERVED_MASK                                                       (0xffffc000U)

#define RZB_V_DIF_SHIFT                                                                 (0U)
#define RZB_V_DIF_MASK                                                                  (0x00003fffU)

#define RZB_V_DIF_RESERVED_SHIFT                                                        (14U)
#define RZB_V_DIF_RESERVED_MASK                                                         (0xffffc000U)

#define RZB_V_TYP_Y_SHIFT                                                               (0U)
#define RZB_V_TYP_Y_MASK                                                                (0x00000001U)
#define RZB_V_TYP_Y_NEWENUM1                                                             (0U)
#define RZB_V_TYP_Y_NEWENUM2                                                             (1U)

#define RZB_V_TYP_C_SHIFT                                                               (1U)
#define RZB_V_TYP_C_MASK                                                                (0x00000002U)
#define RZB_V_TYP_C_NEWENUM1                                                             (0U)
#define RZB_V_TYP_C_NEWENUM2                                                             (1U)

#define RZB_V_TYP_RESERVED_SHIFT                                                        (2U)
#define RZB_V_TYP_RESERVED_MASK                                                         (0xfffffffcU)

#define RZB_V_LPF_Y_SHIFT                                                               (0U)
#define RZB_V_LPF_Y_MASK                                                                (0x0000003fU)

#define RZB_V_LPF_C_SHIFT                                                               (6U)
#define RZB_V_LPF_C_MASK                                                                (0x00000fc0U)

#define RZB_V_LPF_RESERVED_SHIFT                                                        (12U)
#define RZB_V_LPF_RESERVED_MASK                                                         (0xfffff000U)

#define RZB_H_PHS_SHIFT                                                                 (0U)
#define RZB_H_PHS_MASK                                                                  (0x00003fffU)

#define RZB_H_PHS_RESERVED_SHIFT                                                        (14U)
#define RZB_H_PHS_RESERVED_MASK                                                         (0xffffc000U)

#define RZB_H_PHS_ADJ_SHIFT                                                             (0U)
#define RZB_H_PHS_ADJ_MASK                                                              (0x000001ffU)

#define RZB_H_PHS_ADJ_RESERVED_SHIFT                                                    (9U)
#define RZB_H_PHS_ADJ_RESERVED_MASK                                                     (0xfffffe00U)

#define RZB_H_DIF_SHIFT                                                                 (0U)
#define RZB_H_DIF_MASK                                                                  (0x00003fffU)

#define RZB_H_DIF_RESERVED_SHIFT                                                        (14U)
#define RZB_H_DIF_RESERVED_MASK                                                         (0xffffc000U)

#define RZB_H_TYP_Y_SHIFT                                                               (0U)
#define RZB_H_TYP_Y_MASK                                                                (0x00000001U)
#define RZB_H_TYP_Y_NEWENUM1                                                             (0U)
#define RZB_H_TYP_Y_NEWENUM2                                                             (1U)

#define RZB_H_TYP_C_SHIFT                                                               (1U)
#define RZB_H_TYP_C_MASK                                                                (0x00000002U)
#define RZB_H_TYP_C_NEWENUM1                                                             (0U)
#define RZB_H_TYP_C_NEWENUM2                                                             (1U)

#define RZB_H_TYP_RESERVED_SHIFT                                                        (2U)
#define RZB_H_TYP_RESERVED_MASK                                                         (0xfffffffcU)

#define RZB_H_LPF_Y_SHIFT                                                               (0U)
#define RZB_H_LPF_Y_MASK                                                                (0x0000003fU)

#define RZB_H_LPF_C_SHIFT                                                               (6U)
#define RZB_H_LPF_C_MASK                                                                (0x00000fc0U)

#define RZB_H_LPF_RESERVED_SHIFT                                                        (12U)
#define RZB_H_LPF_RESERVED_MASK                                                         (0xfffff000U)

#define RZB_DWN_EN_SHIFT                                                                (0U)
#define RZB_DWN_EN_MASK                                                                 (0x00000001U)
#define RZB_DWN_EN_NEWENUM1                                                              (0U)
#define RZB_DWN_EN_NEWENUM2                                                              (1U)

#define RZB_DWN_EN_RESERVED_SHIFT                                                       (1U)
#define RZB_DWN_EN_RESERVED_MASK                                                        (0xfffffffeU)

#define RZB_DWN_AV_H_SHIFT                                                              (0U)
#define RZB_DWN_AV_H_MASK                                                               (0x00000007U)

#define RZB_DWN_AV_V_SHIFT                                                              (3U)
#define RZB_DWN_AV_V_MASK                                                               (0x00000038U)

#define RZB_DWN_AV_RESERVED_SHIFT                                                       (6U)
#define RZB_DWN_AV_RESERVED_MASK                                                        (0xffffffc0U)

#define RZB_RGB_EN_SHIFT                                                                (0U)
#define RZB_RGB_EN_MASK                                                                 (0x00000001U)
#define RZB_RGB_EN_NEWENUM1                                                              (0U)
#define RZB_RGB_EN_NEWENUM2                                                              (1U)

#define RZB_RGB_EN_RESERVED_SHIFT                                                       (1U)
#define RZB_RGB_EN_RESERVED_MASK                                                        (0xfffffffeU)

#define RZB_RGB_TYP_SHIFT                                                               (0U)
#define RZB_RGB_TYP_MASK                                                                (0x00000001U)
#define RZB_RGB_TYP_NEWENUM1                                                             (0U)
#define RZB_RGB_TYP_NEWENUM2                                                             (1U)

#define RZB_RGB_TYP_MSK0_SHIFT                                                          (1U)
#define RZB_RGB_TYP_MSK0_MASK                                                           (0x00000002U)
#define RZB_RGB_TYP_MSK0_NEWENUM1                                                        (0U)
#define RZB_RGB_TYP_MSK0_NEWENUM2                                                        (1U)

#define RZB_RGB_TYP_MSK1_SHIFT                                                          (2U)
#define RZB_RGB_TYP_MSK1_MASK                                                           (0x00000004U)
#define RZB_RGB_TYP_MSK1_NEWENUM1                                                        (0U)
#define RZB_RGB_TYP_MSK1_NEWENUM2                                                        (1U)

#define RZB_RGB_TYP_RESERVED_SHIFT                                                      (3U)
#define RZB_RGB_TYP_RESERVED_MASK                                                       (0xfffffff8U)

#define RZB_RGB_BLD_SHIFT                                                               (0U)
#define RZB_RGB_BLD_MASK                                                                (0x000000ffU)

#define RZB_RGB_BLD_RESERVED_SHIFT                                                      (8U)
#define RZB_RGB_BLD_RESERVED_MASK                                                       (0xffffff00U)

#define RZB_SDR_Y_BAD_H_SHIFT                                                           (0U)
#define RZB_SDR_Y_BAD_H_MASK                                                            (0x0000ffffU)

#define RZB_SDR_Y_BAD_H_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_Y_BAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_Y_BAD_L_SHIFT                                                           (0U)
#define RZB_SDR_Y_BAD_L_MASK                                                            (0x0000ffffU)

#define RZB_SDR_Y_BAD_L_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_Y_BAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_Y_SAD_H_SHIFT                                                           (0U)
#define RZB_SDR_Y_SAD_H_MASK                                                            (0x0000ffffU)

#define RZB_SDR_Y_SAD_H_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_Y_SAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_Y_SAD_L_SHIFT                                                           (0U)
#define RZB_SDR_Y_SAD_L_MASK                                                            (0x0000ffffU)

#define RZB_SDR_Y_SAD_L_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_Y_SAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_Y_OFT_SHIFT                                                             (0U)
#define RZB_SDR_Y_OFT_MASK                                                              (0x0001ffffU)

#define RZB_SDR_Y_OFT_RESERVED_SHIFT                                                    (17U)
#define RZB_SDR_Y_OFT_RESERVED_MASK                                                     (0xfffe0000U)

#define RZB_SDR_Y_PTR_S_SHIFT                                                           (0U)
#define RZB_SDR_Y_PTR_S_MASK                                                            (0x00001fffU)

#define RZB_SDR_Y_PTR_S_RESERVED_SHIFT                                                  (13U)
#define RZB_SDR_Y_PTR_S_RESERVED_MASK                                                   (0xffffe000U)

#define RZB_SDR_Y_PTR_E_SHIFT                                                           (0U)
#define RZB_SDR_Y_PTR_E_MASK                                                            (0x00001fffU)

#define RZB_SDR_Y_PTR_E_RESERVED_SHIFT                                                  (13U)
#define RZB_SDR_Y_PTR_E_RESERVED_MASK                                                   (0xffffe000U)

#define RZB_SDR_C_BAD_H_SHIFT                                                           (0U)
#define RZB_SDR_C_BAD_H_MASK                                                            (0x0000ffffU)

#define RZB_SDR_C_BAD_H_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_C_BAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_C_BAD_L_SHIFT                                                           (0U)
#define RZB_SDR_C_BAD_L_MASK                                                            (0x0000ffffU)

#define RZB_SDR_C_BAD_L_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_C_BAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_C_SAD_H_SHIFT                                                           (0U)
#define RZB_SDR_C_SAD_H_MASK                                                            (0x0000ffffU)

#define RZB_SDR_C_SAD_H_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_C_SAD_H_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_C_SAD_L_SHIFT                                                           (0U)
#define RZB_SDR_C_SAD_L_MASK                                                            (0x0000ffffU)

#define RZB_SDR_C_SAD_L_RESERVED_SHIFT                                                  (16U)
#define RZB_SDR_C_SAD_L_RESERVED_MASK                                                   (0xffff0000U)

#define RZB_SDR_C_OFT_SHIFT                                                             (0U)
#define RZB_SDR_C_OFT_MASK                                                              (0x0001ffffU)

#define RZB_SDR_C_OFT_RESERVED_SHIFT                                                    (17U)
#define RZB_SDR_C_OFT_RESERVED_MASK                                                     (0xfffe0000U)

#define RZB_SDR_C_PTR_S_SHIFT                                                           (0U)
#define RZB_SDR_C_PTR_S_MASK                                                            (0x00001fffU)

#define RZB_SDR_C_PTR_S_RESERVED_SHIFT                                                  (13U)
#define RZB_SDR_C_PTR_S_RESERVED_MASK                                                   (0xffffe000U)

#define RZB_SDR_C_PTR_E_SHIFT                                                           (0U)
#define RZB_SDR_C_PTR_E_MASK                                                            (0x00001fffU)

#define RZB_SDR_C_PTR_E_RESERVED_SHIFT                                                  (13U)
#define RZB_SDR_C_PTR_E_RESERVED_MASK                                                   (0xffffe000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_RSZ_H_ */

