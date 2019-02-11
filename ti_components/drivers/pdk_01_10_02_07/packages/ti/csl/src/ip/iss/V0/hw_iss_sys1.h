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

#ifndef HW_ISS_SYS1_H_
#define HW_ISS_SYS1_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ISP5_REVISION                                      (0x0U)
#define ISP5_HWINFO1                                       (0x4U)
#define ISP5_HWINFO2                                       (0x8U)
#define ISP5_SYSCONFIG                                     (0x10U)
#define ISP5_IRQ_EOI                                       (0x20U)
#define ISP5_IRQSTATUS_RAW(m)                              (0x24U + ((m) * (uint32_t)0x10))
#define ISP5_IRQSTATUS(m)                                  (0x28U + ((m) * (uint32_t)0x10))
#define ISP5_IRQENABLE_SET(m)                              (0x2cU + ((m) * (uint32_t)0x10))
#define ISP5_IRQENABLE_CLR(m)                              (0x30U + ((m) * (uint32_t)0x10))
#define ISP5_DMAENABLE_SET                                 (0x64U)
#define ISP5_DMAENABLE_CLR                                 (0x68U)
#define ISP5_CTRL                                          (0x6cU)
#define ISP5_PG                                            (0x70U)
#define ISP5_PG_PULSE_CTRL                                 (0x74U)
#define ISP5_PG_FRAME_SIZE                                 (0x78U)
#define ISP5_MPSR                                          (0x7cU)
#define ISP5_BL_MTC_1                                      (0x80U)
#define ISP5_BL_MTC_2                                      (0x84U)
#define ISP5_BL_VBUSM                                      (0x88U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISP5_REVISION_Y_MINOR_SHIFT                                            (0U)
#define ISP5_REVISION_Y_MINOR_MASK                                             (0x0000003fU)

#define ISP5_REVISION_CUSTOM_SHIFT                                             (6U)
#define ISP5_REVISION_CUSTOM_MASK                                              (0x000000c0U)
#define ISP5_REVISION_CUSTOM_STANDARD                                           (0x00000000U)

#define ISP5_REVISION_X_MAJOR_SHIFT                                            (8U)
#define ISP5_REVISION_X_MAJOR_MASK                                             (0x00000700U)

#define ISP5_REVISION_R_RTL_SHIFT                                              (11U)
#define ISP5_REVISION_R_RTL_MASK                                               (0x0000f800U)

#define ISP5_REVISION_FUNC_SHIFT                                               (16U)
#define ISP5_REVISION_FUNC_MASK                                                (0x0fff0000U)

#define ISP5_REVISION_SCHEME_SHIFT                                             (30U)
#define ISP5_REVISION_SCHEME_MASK                                              (0xc0000000U)
#define ISP5_REVISION_SCHEME_H08                                                (0x40000000U)
#define ISP5_REVISION_SCHEME_LEGACY                                             (0x00000000U)

#define ISP5_REVISION_RESERVED_SHIFT                                           (28U)
#define ISP5_REVISION_RESERVED_MASK                                            (0x30000000U)

#define ISP5_HWINFO1_IPIPE_LINE_SIZE_SHIFT                                     (0U)
#define ISP5_HWINFO1_IPIPE_LINE_SIZE_MASK                                      (0x00001fffU)

#define ISP5_HWINFO1_ISIF_RFM_LINE_SIZE_SHIFT                                  (16U)
#define ISP5_HWINFO1_ISIF_RFM_LINE_SIZE_MASK                                   (0x1fff0000U)

#define ISP5_HWINFO1_RESERVED_SHIFT                                            (13U)
#define ISP5_HWINFO1_RESERVED_MASK                                             (0x0000e000U)

#define ISP5_HWINFO1_RESERVED1_SHIFT                                           (29U)
#define ISP5_HWINFO1_RESERVED1_MASK                                            (0xe0000000U)

#define ISP5_HWINFO2_H3A_LINE_SIZE_SHIFT                                       (0U)
#define ISP5_HWINFO2_H3A_LINE_SIZE_MASK                                        (0x00001fffU)

#define ISP5_HWINFO2_RESERVED_SHIFT                                            (13U)
#define ISP5_HWINFO2_RESERVED_MASK                                             (0xffffe000U)

#define ISP5_SYSCONFIG_SOFTRESET_SHIFT                                         (1U)
#define ISP5_SYSCONFIG_SOFTRESET_MASK                                          (0x00000002U)
#define ISP5_SYSCONFIG_SOFTRESET_DONE                                           (0x00000000U)
#define ISP5_SYSCONFIG_SOFTRESET_PENDING                                        (0x00000002U)
#define ISP5_SYSCONFIG_SOFTRESET_NOACTION                                       (0x00000000U)
#define ISP5_SYSCONFIG_SOFTRESET_RESET                                          (0x00000002U)

#define ISP5_SYSCONFIG_STANDBYMODE_SHIFT                                       (4U)
#define ISP5_SYSCONFIG_STANDBYMODE_MASK                                        (0x00000030U)
#define ISP5_SYSCONFIG_STANDBYMODE_FORCE                                        (0x00000000U)
#define ISP5_SYSCONFIG_STANDBYMODE_NO                                           (0x00000010U)
#define ISP5_SYSCONFIG_STANDBYMODE_SMART                                        (0x00000020U)
#define ISP5_SYSCONFIG_STANDBYMODE_RESERVED                                     (0x00000030U)

#define ISP5_SYSCONFIG_RESERVED_SHIFT                                          (6U)
#define ISP5_SYSCONFIG_RESERVED_MASK                                           (0xffffffc0U)

#define ISP5_SYSCONFIG_AUTO_IDLE_SHIFT                                         (0U)
#define ISP5_SYSCONFIG_AUTO_IDLE_MASK                                          (0x00000001U)

#define ISP5_SYSCONFIG_RESERVED1_SHIFT                                         (2U)
#define ISP5_SYSCONFIG_RESERVED1_MASK                                          (0x0000000cU)

#define ISP5_IRQ_EOI_LINE_NUMBER_SHIFT                                         (0U)
#define ISP5_IRQ_EOI_LINE_NUMBER_MASK                                          (0x00000003U)
#define ISP5_IRQ_EOI_LINE_NUMBER_READ0                                          (0x00000000U)
#define ISP5_IRQ_EOI_LINE_NUMBER_EOI0                                           (0x00000000U)
#define ISP5_IRQ_EOI_LINE_NUMBER_EOI1                                           (0x00000001U)
#define ISP5_IRQ_EOI_LINE_NUMBER_EOI2                                           (0x00000002U)
#define ISP5_IRQ_EOI_LINE_NUMBER_EOI3                                           (0x00000003U)

#define ISP5_IRQ_EOI_RESERVED_SHIFT                                            (2U)
#define ISP5_IRQ_EOI_RESERVED_MASK                                             (0xfffffffcU)

#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_SHIFT                                    (0U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_MASK                                     (0x00000001U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_NOACTION                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_SET                                       (0x00000001U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_NOEVENT                                   (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_0_PENDING                                   (0x00000001U)

#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_SHIFT                                    (1U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_MASK                                     (0x00000002U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_NOACTION                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_SET                                       (0x00000002U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_NOEVENT                                   (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_1_PENDING                                   (0x00000002U)

#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_SHIFT                                    (2U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_MASK                                     (0x00000004U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_NOACTION                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_SET                                       (0x00000004U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_NOEVENT                                   (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_2_PENDING                                   (0x00000004U)

#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_SHIFT                                    (3U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_MASK                                     (0x00000008U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_NOACTION                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_SET                                       (0x00000008U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_NOEVENT                                   (0x00000000U)
#define ISP5_IRQSTATUS_RAW_ISIF_INT_3_PENDING                                   (0x00000008U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_SHIFT                                 (4U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_MASK                                  (0x00000010U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_SET                                    (0x00000010U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_REG_PENDING                                (0x00000010U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_SHIFT                            (5U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_MASK                             (0x00000020U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_NOACTION                          (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_SET                               (0x00000020U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_NOEVENT                           (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_LAST_PIX_PENDING                           (0x00000020U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_SHIFT                                 (6U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_MASK                                  (0x00000040U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_SET                                    (0x00000040U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DMA_PENDING                                (0x00000040U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_SHIFT                                 (7U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_MASK                                  (0x00000080U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_SET                                    (0x00000080U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_BSC_PENDING                                (0x00000080U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_SHIFT                                 (8U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_MASK                                  (0x00000100U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_SET                                    (0x00000100U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_HST_PENDING                                (0x00000100U)

#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_SHIFT                                   (9U)
#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_MASK                                    (0x00000200U)
#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_SET                                      (0x00000200U)
#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPEIF_IRQ_PENDING                                  (0x00000200U)

#define ISP5_IRQSTATUS_RAW_AEW_INT_SHIFT                                       (10U)
#define ISP5_IRQSTATUS_RAW_AEW_INT_MASK                                        (0x00000400U)
#define ISP5_IRQSTATUS_RAW_AEW_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_RAW_AEW_INT_SET                                          (0x00000400U)
#define ISP5_IRQSTATUS_RAW_AEW_INT_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_RAW_AEW_INT_PENDING                                      (0x00000400U)

#define ISP5_IRQSTATUS_RAW_AF_INT_SHIFT                                        (11U)
#define ISP5_IRQSTATUS_RAW_AF_INT_MASK                                         (0x00000800U)
#define ISP5_IRQSTATUS_RAW_AF_INT_NOACTION                                      (0x00000000U)
#define ISP5_IRQSTATUS_RAW_AF_INT_SET                                           (0x00000800U)
#define ISP5_IRQSTATUS_RAW_AF_INT_NOEVENT                                       (0x00000000U)
#define ISP5_IRQSTATUS_RAW_AF_INT_PENDING                                       (0x00000800U)

#define ISP5_IRQSTATUS_RAW_H3A_INT_SHIFT                                       (12U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_MASK                                        (0x00001000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_SET                                          (0x00001000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_PENDING                                      (0x00001000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_SHIFT                                   (13U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_MASK                                    (0x00002000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_SET                                      (0x00002000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_REG_PENDING                                  (0x00002000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_SHIFT                              (14U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_MASK                               (0x00004000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_NOACTION                            (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_SET                                 (0x00004000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_NOEVENT                             (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_LAST_PIX_PENDING                             (0x00004000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_SHIFT                                   (15U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_MASK                                    (0x00008000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_SET                                      (0x00008000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_DMA_PENDING                                  (0x00008000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_SHIFT                               (16U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_MASK                                (0x00010000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_NOACTION                             (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_SET                                  (0x00010000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_NOEVENT                              (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZA_PENDING                              (0x00010000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_SHIFT                               (17U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_MASK                                (0x00020000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_NOACTION                             (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_SET                                  (0x00020000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_NOEVENT                              (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_CYC_RZB_PENDING                              (0x00020000U)

#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_SHIFT                                  (18U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_MASK                                   (0x00040000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_NOACTION                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_SET                                     (0x00040000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_NOEVENT                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_OVF_PENDING                                 (0x00040000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_SHIFT                                  (22U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_MASK                                   (0x00400000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_NOACTION                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_SET                                     (0x00400000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_NOEVENT                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF0_PENDING                                 (0x00400000U)

#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_SHIFT                                  (23U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_MASK                                   (0x00800000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_NOACTION                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_SET                                     (0x00800000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_NOEVENT                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_INT_EOF1_PENDING                                 (0x00800000U)

#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_SHIFT                                   (24U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_MASK                                    (0x01000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_SET                                      (0x01000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_H3A_INT_EOF_PENDING                                  (0x01000000U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_SHIFT                                 (25U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_MASK                                  (0x02000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_SET                                    (0x02000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_EOF_PENDING                                (0x02000000U)

#define ISP5_IRQSTATUS_RAW_RESERVED1_SHIFT                                     (26U)
#define ISP5_IRQSTATUS_RAW_RESERVED1_MASK                                      (0x04000000U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_SHIFT                             (27U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_MASK                              (0x08000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_NOACTION                           (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_SET                                (0x08000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_NOEVENT                            (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_INI_PENDING                            (0x08000000U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_SHIFT                           (28U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_MASK                            (0x10000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_NOACTION                         (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_SET                              (0x10000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_NOEVENT                          (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW0_PENDING                          (0x10000000U)

#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_SHIFT                           (29U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_MASK                            (0x20000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_NOACTION                         (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_SET                              (0x20000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_NOEVENT                          (0x00000000U)
#define ISP5_IRQSTATUS_RAW_IPIPE_INT_DPC_RNEW1_PENDING                          (0x20000000U)

#define ISP5_IRQSTATUS_RAW_RESERVED2_SHIFT                                     (30U)
#define ISP5_IRQSTATUS_RAW_RESERVED2_MASK                                      (0x40000000U)

#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_SHIFT                                   (31U)
#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_MASK                                    (0x80000000U)
#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_SET                                      (0x80000000U)
#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RAW_OCP_ERR_IRQ_PENDING                                  (0x80000000U)

#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_SHIFT                           (19U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_MASK                            (0x00080000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_NOACTION                         (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_SET                              (0x00080000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_NOEVENT                          (0x00000000U)
#define ISP5_IRQSTATUS_RAW_RSZ_FIFO_IN_BLK_ERR_PENDING                          (0x00080000U)

#define ISP5_IRQSTATUS_RAW_RESERVED_SHIFT                                      (20U)
#define ISP5_IRQSTATUS_RAW_RESERVED_MASK                                       (0x00300000U)

#define ISP5_IRQSTATUS_ISIF_INT_0_SHIFT                                        (0U)
#define ISP5_IRQSTATUS_ISIF_INT_0_MASK                                         (0x00000001U)
#define ISP5_IRQSTATUS_ISIF_INT_0_NOACTION                                      (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_0_CLEAR                                         (0x00000001U)
#define ISP5_IRQSTATUS_ISIF_INT_0_NOEVENT                                       (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_0_PENDING                                       (0x00000001U)

#define ISP5_IRQSTATUS_ISIF_INT_1_SHIFT                                        (1U)
#define ISP5_IRQSTATUS_ISIF_INT_1_MASK                                         (0x00000002U)
#define ISP5_IRQSTATUS_ISIF_INT_1_NOACTION                                      (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_1_CLEAR                                         (0x00000002U)
#define ISP5_IRQSTATUS_ISIF_INT_1_NOEVENT                                       (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_1_PENDING                                       (0x00000002U)

#define ISP5_IRQSTATUS_ISIF_INT_2_SHIFT                                        (2U)
#define ISP5_IRQSTATUS_ISIF_INT_2_MASK                                         (0x00000004U)
#define ISP5_IRQSTATUS_ISIF_INT_2_NOACTION                                      (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_2_CLEAR                                         (0x00000004U)
#define ISP5_IRQSTATUS_ISIF_INT_2_NOEVENT                                       (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_2_PENDING                                       (0x00000004U)

#define ISP5_IRQSTATUS_ISIF_INT_3_SHIFT                                        (3U)
#define ISP5_IRQSTATUS_ISIF_INT_3_MASK                                         (0x00000008U)
#define ISP5_IRQSTATUS_ISIF_INT_3_NOACTION                                      (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_3_CLEAR                                         (0x00000008U)
#define ISP5_IRQSTATUS_ISIF_INT_3_NOEVENT                                       (0x00000000U)
#define ISP5_IRQSTATUS_ISIF_INT_3_PENDING                                       (0x00000008U)

#define ISP5_IRQSTATUS_IPIPE_INT_REG_SHIFT                                     (4U)
#define ISP5_IRQSTATUS_IPIPE_INT_REG_MASK                                      (0x00000010U)
#define ISP5_IRQSTATUS_IPIPE_INT_REG_NOACTION                                   (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_REG_CLEAR                                      (0x00000010U)
#define ISP5_IRQSTATUS_IPIPE_INT_REG_NOEVENT                                    (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_REG_PENDING                                    (0x00000010U)

#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_SHIFT                                (5U)
#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_MASK                                 (0x00000020U)
#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_NOACTION                              (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_CLEAR                                 (0x00000020U)
#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_NOEVENT                               (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_LAST_PIX_PENDING                               (0x00000020U)

#define ISP5_IRQSTATUS_IPIPE_INT_DMA_SHIFT                                     (6U)
#define ISP5_IRQSTATUS_IPIPE_INT_DMA_MASK                                      (0x00000040U)
#define ISP5_IRQSTATUS_IPIPE_INT_DMA_NOACTION                                   (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DMA_CLEAR                                      (0x00000040U)
#define ISP5_IRQSTATUS_IPIPE_INT_DMA_NOEVENT                                    (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DMA_PENDING                                    (0x00000040U)

#define ISP5_IRQSTATUS_IPIPE_INT_BSC_SHIFT                                     (7U)
#define ISP5_IRQSTATUS_IPIPE_INT_BSC_MASK                                      (0x00000080U)
#define ISP5_IRQSTATUS_IPIPE_INT_BSC_NOACTION                                   (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_BSC_CLEAR                                      (0x00000080U)
#define ISP5_IRQSTATUS_IPIPE_INT_BSC_NOEVENT                                    (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_BSC_PENDING                                    (0x00000080U)

#define ISP5_IRQSTATUS_IPIPE_INT_HST_SHIFT                                     (8U)
#define ISP5_IRQSTATUS_IPIPE_INT_HST_MASK                                      (0x00000100U)
#define ISP5_IRQSTATUS_IPIPE_INT_HST_NOACTION                                   (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_HST_CLEAR                                      (0x00000100U)
#define ISP5_IRQSTATUS_IPIPE_INT_HST_NOEVENT                                    (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_HST_PENDING                                    (0x00000100U)

#define ISP5_IRQSTATUS_IPIPEIF_IRQ_SHIFT                                       (9U)
#define ISP5_IRQSTATUS_IPIPEIF_IRQ_MASK                                        (0x00000200U)
#define ISP5_IRQSTATUS_IPIPEIF_IRQ_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_IPIPEIF_IRQ_CLEAR                                        (0x00000200U)
#define ISP5_IRQSTATUS_IPIPEIF_IRQ_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_IPIPEIF_IRQ_PENDING                                      (0x00000200U)

#define ISP5_IRQSTATUS_AEW_INT_SHIFT                                           (10U)
#define ISP5_IRQSTATUS_AEW_INT_MASK                                            (0x00000400U)
#define ISP5_IRQSTATUS_AEW_INT_NOACTION                                         (0x00000000U)
#define ISP5_IRQSTATUS_AEW_INT_CLEAR                                            (0x00000400U)
#define ISP5_IRQSTATUS_AEW_INT_NOEVENT                                          (0x00000000U)
#define ISP5_IRQSTATUS_AEW_INT_PENDING                                          (0x00000400U)

#define ISP5_IRQSTATUS_AF_INT_SHIFT                                            (11U)
#define ISP5_IRQSTATUS_AF_INT_MASK                                             (0x00000800U)
#define ISP5_IRQSTATUS_AF_INT_NOACTION                                          (0x00000000U)
#define ISP5_IRQSTATUS_AF_INT_CLEAR                                             (0x00000800U)
#define ISP5_IRQSTATUS_AF_INT_NOEVENT                                           (0x00000000U)
#define ISP5_IRQSTATUS_AF_INT_PENDING                                           (0x00000800U)

#define ISP5_IRQSTATUS_H3A_INT_SHIFT                                           (12U)
#define ISP5_IRQSTATUS_H3A_INT_MASK                                            (0x00001000U)
#define ISP5_IRQSTATUS_H3A_INT_NOACTION                                         (0x00000000U)
#define ISP5_IRQSTATUS_H3A_INT_CLEAR                                            (0x00001000U)
#define ISP5_IRQSTATUS_H3A_INT_NOEVENT                                          (0x00000000U)
#define ISP5_IRQSTATUS_H3A_INT_PENDING                                          (0x00001000U)

#define ISP5_IRQSTATUS_RSZ_INT_REG_SHIFT                                       (13U)
#define ISP5_IRQSTATUS_RSZ_INT_REG_MASK                                        (0x00002000U)
#define ISP5_IRQSTATUS_RSZ_INT_REG_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_REG_CLEAR                                        (0x00002000U)
#define ISP5_IRQSTATUS_RSZ_INT_REG_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_REG_PENDING                                      (0x00002000U)

#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_SHIFT                                  (14U)
#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_MASK                                   (0x00004000U)
#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_NOACTION                                (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_CLEAR                                   (0x00004000U)
#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_NOEVENT                                 (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_LAST_PIX_PENDING                                 (0x00004000U)

#define ISP5_IRQSTATUS_RSZ_INT_DMA_SHIFT                                       (15U)
#define ISP5_IRQSTATUS_RSZ_INT_DMA_MASK                                        (0x00008000U)
#define ISP5_IRQSTATUS_RSZ_INT_DMA_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_DMA_CLEAR                                        (0x00008000U)
#define ISP5_IRQSTATUS_RSZ_INT_DMA_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_DMA_PENDING                                      (0x00008000U)

#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_SHIFT                                   (16U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_MASK                                    (0x00010000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_CLEAR                                    (0x00010000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZA_PENDING                                  (0x00010000U)

#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_SHIFT                                   (17U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_MASK                                    (0x00020000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_NOACTION                                 (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_CLEAR                                    (0x00020000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_NOEVENT                                  (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_CYC_RZB_PENDING                                  (0x00020000U)

#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_SHIFT                                      (18U)
#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_MASK                                       (0x00040000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_NOACTION                                    (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_CLEAR                                       (0x00040000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_NOEVENT                                     (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_OVF_PENDING                                     (0x00040000U)

#define ISP5_IRQSTATUS_RSZ_INT_EOF0_SHIFT                                      (22U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF0_MASK                                       (0x00400000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF0_NOACTION                                    (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF0_CLEAR                                       (0x00400000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF0_NOEVENT                                     (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF0_PENDING                                     (0x00400000U)

#define ISP5_IRQSTATUS_RSZ_INT_EOF1_SHIFT                                      (23U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF1_MASK                                       (0x00800000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF1_NOACTION                                    (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF1_CLEAR                                       (0x00800000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF1_NOEVENT                                     (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_INT_EOF1_PENDING                                     (0x00800000U)

#define ISP5_IRQSTATUS_H3A_INT_EOF_SHIFT                                       (24U)
#define ISP5_IRQSTATUS_H3A_INT_EOF_MASK                                        (0x01000000U)
#define ISP5_IRQSTATUS_H3A_INT_EOF_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_H3A_INT_EOF_CLEAR                                        (0x01000000U)
#define ISP5_IRQSTATUS_H3A_INT_EOF_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_H3A_INT_EOF_PENDING                                      (0x01000000U)

#define ISP5_IRQSTATUS_IPIPE_INT_EOF_SHIFT                                     (25U)
#define ISP5_IRQSTATUS_IPIPE_INT_EOF_MASK                                      (0x02000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_EOF_NOACTION                                   (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_EOF_CLEAR                                      (0x02000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_EOF_NOEVENT                                    (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_EOF_PENDING                                    (0x02000000U)

#define ISP5_IRQSTATUS_RESERVED1_SHIFT                                         (26U)
#define ISP5_IRQSTATUS_RESERVED1_MASK                                          (0x04000000U)

#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_SHIFT                                 (27U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_MASK                                  (0x08000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_NOACTION                               (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_CLEAR                                  (0x08000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_NOEVENT                                (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_INI_PENDING                                (0x08000000U)

#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_SHIFT                               (28U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_MASK                                (0x10000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_NOACTION                             (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_CLEAR                                (0x10000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_NOEVENT                              (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW0_PENDING                              (0x10000000U)

#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_SHIFT                               (29U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_MASK                                (0x20000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_NOACTION                             (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_CLEAR                                (0x20000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_NOEVENT                              (0x00000000U)
#define ISP5_IRQSTATUS_IPIPE_INT_DPC_RNEW1_PENDING                              (0x20000000U)

#define ISP5_IRQSTATUS_RESERVED2_SHIFT                                         (30U)
#define ISP5_IRQSTATUS_RESERVED2_MASK                                          (0x40000000U)

#define ISP5_IRQSTATUS_OCP_ERR_IRQ_SHIFT                                       (31U)
#define ISP5_IRQSTATUS_OCP_ERR_IRQ_MASK                                        (0x80000000U)
#define ISP5_IRQSTATUS_OCP_ERR_IRQ_NOACTION                                     (0x00000000U)
#define ISP5_IRQSTATUS_OCP_ERR_IRQ_CLEAR                                        (0x80000000U)
#define ISP5_IRQSTATUS_OCP_ERR_IRQ_NOEVENT                                      (0x00000000U)
#define ISP5_IRQSTATUS_OCP_ERR_IRQ_PENDING                                      (0x80000000U)

#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_SHIFT                               (19U)
#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_MASK                                (0x00080000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_NOACTION                             (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_CLEAR                                (0x00080000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_NOEVENT                              (0x00000000U)
#define ISP5_IRQSTATUS_RSZ_FIFO_IN_BLK_ERR_PENDING                              (0x00080000U)

#define ISP5_IRQSTATUS_RESERVED_SHIFT                                          (20U)
#define ISP5_IRQSTATUS_RESERVED_MASK                                           (0x00300000U)

#define ISP5_IRQENABLE_SET_ISIF_INT_0_SHIFT                                    (0U)
#define ISP5_IRQENABLE_SET_ISIF_INT_0_MASK                                     (0x00000001U)
#define ISP5_IRQENABLE_SET_ISIF_INT_0_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_0_ENABLE                                    (0x00000001U)
#define ISP5_IRQENABLE_SET_ISIF_INT_0_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_0_ENABLED                                   (0x00000001U)

#define ISP5_IRQENABLE_SET_ISIF_INT_1_SHIFT                                    (1U)
#define ISP5_IRQENABLE_SET_ISIF_INT_1_MASK                                     (0x00000002U)
#define ISP5_IRQENABLE_SET_ISIF_INT_1_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_1_ENABLE                                    (0x00000002U)
#define ISP5_IRQENABLE_SET_ISIF_INT_1_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_1_ENABLED                                   (0x00000002U)

#define ISP5_IRQENABLE_SET_ISIF_INT_2_SHIFT                                    (2U)
#define ISP5_IRQENABLE_SET_ISIF_INT_2_MASK                                     (0x00000004U)
#define ISP5_IRQENABLE_SET_ISIF_INT_2_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_2_ENABLE                                    (0x00000004U)
#define ISP5_IRQENABLE_SET_ISIF_INT_2_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_2_ENABLED                                   (0x00000004U)

#define ISP5_IRQENABLE_SET_ISIF_INT_3_SHIFT                                    (3U)
#define ISP5_IRQENABLE_SET_ISIF_INT_3_MASK                                     (0x00000008U)
#define ISP5_IRQENABLE_SET_ISIF_INT_3_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_3_ENABLE                                    (0x00000008U)
#define ISP5_IRQENABLE_SET_ISIF_INT_3_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_SET_ISIF_INT_3_ENABLED                                   (0x00000008U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_SHIFT                                 (4U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_MASK                                  (0x00000010U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_ENABLE                                 (0x00000010U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_REG_ENABLED                                (0x00000010U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_SHIFT                            (5U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_MASK                             (0x00000020U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_NOACTION                          (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_ENABLE                            (0x00000020U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_DISABLED                          (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_LAST_PIX_ENABLED                           (0x00000020U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_SHIFT                                 (6U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_MASK                                  (0x00000040U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_ENABLE                                 (0x00000040U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DMA_ENABLED                                (0x00000040U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_SHIFT                                 (7U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_MASK                                  (0x00000080U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_ENABLE                                 (0x00000080U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_BSC_ENABLED                                (0x00000080U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_SHIFT                                 (8U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_MASK                                  (0x00000100U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_ENABLE                                 (0x00000100U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_HST_ENABLED                                (0x00000100U)

#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_SHIFT                                   (9U)
#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_MASK                                    (0x00000200U)
#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_ENABLE                                   (0x00000200U)
#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPEIF_IRQ_ENABLED                                  (0x00000200U)

#define ISP5_IRQENABLE_SET_AEW_INT_SHIFT                                       (10U)
#define ISP5_IRQENABLE_SET_AEW_INT_MASK                                        (0x00000400U)
#define ISP5_IRQENABLE_SET_AEW_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQENABLE_SET_AEW_INT_ENABLE                                       (0x00000400U)
#define ISP5_IRQENABLE_SET_AEW_INT_DISABLED                                     (0x00000000U)
#define ISP5_IRQENABLE_SET_AEW_INT_ENABLED                                      (0x00000400U)

#define ISP5_IRQENABLE_SET_AF_INT_SHIFT                                        (11U)
#define ISP5_IRQENABLE_SET_AF_INT_MASK                                         (0x00000800U)
#define ISP5_IRQENABLE_SET_AF_INT_NOACTION                                      (0x00000000U)
#define ISP5_IRQENABLE_SET_AF_INT_ENABLE                                        (0x00000800U)
#define ISP5_IRQENABLE_SET_AF_INT_DISABLED                                      (0x00000000U)
#define ISP5_IRQENABLE_SET_AF_INT_ENABLED                                       (0x00000800U)

#define ISP5_IRQENABLE_SET_H3A_INT_SHIFT                                       (12U)
#define ISP5_IRQENABLE_SET_H3A_INT_MASK                                        (0x00001000U)
#define ISP5_IRQENABLE_SET_H3A_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_ENABLE                                       (0x00001000U)
#define ISP5_IRQENABLE_SET_H3A_INT_DISABLED                                     (0x00000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_ENABLED                                      (0x00001000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_REG_SHIFT                                   (13U)
#define ISP5_IRQENABLE_SET_RSZ_INT_REG_MASK                                    (0x00002000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_REG_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_REG_ENABLE                                   (0x00002000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_REG_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_REG_ENABLED                                  (0x00002000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_SHIFT                              (14U)
#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_MASK                               (0x00004000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_NOACTION                            (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_ENABLE                              (0x00004000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_DISABLED                            (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_LAST_PIX_ENABLED                             (0x00004000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_SHIFT                                   (15U)
#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_MASK                                    (0x00008000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_ENABLE                                   (0x00008000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_DMA_ENABLED                                  (0x00008000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_SHIFT                               (16U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_MASK                                (0x00010000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_NOACTION                             (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_ENABLE                               (0x00010000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_DISABLED                             (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZA_ENABLED                              (0x00010000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_SHIFT                               (17U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_MASK                                (0x00020000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_NOACTION                             (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_ENABLE                               (0x00020000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_DISABLED                             (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_CYC_RZB_ENABLED                              (0x00020000U)

#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_SHIFT                                  (18U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_MASK                                   (0x00040000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_ENABLE                                  (0x00040000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_OVF_ENABLED                                 (0x00040000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_SHIFT                                  (22U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_MASK                                   (0x00400000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_ENABLE                                  (0x00400000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF0_ENABLED                                 (0x00400000U)

#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_SHIFT                                  (23U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_MASK                                   (0x00800000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_ENABLE                                  (0x00800000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_INT_EOF1_ENABLED                                 (0x00800000U)

#define ISP5_IRQENABLE_SET_H3A_INT_EOF_SHIFT                                   (24U)
#define ISP5_IRQENABLE_SET_H3A_INT_EOF_MASK                                    (0x01000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_EOF_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_EOF_ENABLE                                   (0x01000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_EOF_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_H3A_INT_EOF_ENABLED                                  (0x01000000U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_SHIFT                                 (25U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_MASK                                  (0x02000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_ENABLE                                 (0x02000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_EOF_ENABLED                                (0x02000000U)

#define ISP5_IRQENABLE_SET_RESERVED1_SHIFT                                     (26U)
#define ISP5_IRQENABLE_SET_RESERVED1_MASK                                      (0x04000000U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_SHIFT                             (27U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_MASK                              (0x08000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_NOACTION                           (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_ENABLE                             (0x08000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_DISABLED                           (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_INI_ENABLED                            (0x08000000U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_SHIFT                           (28U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_MASK                            (0x10000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_ENABLE                           (0x10000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW0_ENABLED                          (0x10000000U)

#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_SHIFT                           (29U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_MASK                            (0x20000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_ENABLE                           (0x20000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_SET_IPIPE_INT_DPC_RNEW1_ENABLED                          (0x20000000U)

#define ISP5_IRQENABLE_SET_RESERVED2_SHIFT                                     (30U)
#define ISP5_IRQENABLE_SET_RESERVED2_MASK                                      (0x40000000U)

#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_SHIFT                                   (31U)
#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_MASK                                    (0x80000000U)
#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_ENABLE                                   (0x80000000U)
#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_SET_OCP_ERR_IRQ_ENABLED                                  (0x80000000U)

#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_SHIFT                           (19U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_MASK                            (0x00080000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_ENABLE                           (0x00080000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_SET_RSZ_FIFO_IN_BLK_ERR_ENABLED                          (0x00080000U)

#define ISP5_IRQENABLE_SET_RESERVED_SHIFT                                      (20U)
#define ISP5_IRQENABLE_SET_RESERVED_MASK                                       (0x00300000U)

#define ISP5_IRQENABLE_CLR_ISIF_INT_0_SHIFT                                    (0U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_0_MASK                                     (0x00000001U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_0_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_0_DISABLE                                   (0x00000001U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_0_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_0_ENABLED                                   (0x00000001U)

#define ISP5_IRQENABLE_CLR_ISIF_INT_1_SHIFT                                    (1U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_1_MASK                                     (0x00000002U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_1_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_1_DISABLE                                   (0x00000002U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_1_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_1_ENABLED                                   (0x00000002U)

#define ISP5_IRQENABLE_CLR_ISIF_INT_2_SHIFT                                    (2U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_2_MASK                                     (0x00000004U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_2_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_2_DISABLE                                   (0x00000004U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_2_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_2_ENABLED                                   (0x00000004U)

#define ISP5_IRQENABLE_CLR_ISIF_INT_3_SHIFT                                    (3U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_3_MASK                                     (0x00000008U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_3_NOACTION                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_3_DISABLE                                   (0x00000008U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_3_DISABLED                                  (0x00000000U)
#define ISP5_IRQENABLE_CLR_ISIF_INT_3_ENABLED                                   (0x00000008U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_SHIFT                                 (4U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_MASK                                  (0x00000010U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_DISABLE                                (0x00000010U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_REG_ENABLED                                (0x00000010U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_SHIFT                            (5U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_MASK                             (0x00000020U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_NOACTION                          (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_DISABLE                           (0x00000020U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_DISABLED                          (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_LAST_PIX_ENABLED                           (0x00000020U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_SHIFT                                 (6U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_MASK                                  (0x00000040U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_DISABLE                                (0x00000040U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DMA_ENABLED                                (0x00000040U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_SHIFT                                 (7U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_MASK                                  (0x00000080U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_DISABLE                                (0x00000080U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_BSC_ENABLED                                (0x00000080U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_SHIFT                                 (8U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_MASK                                  (0x00000100U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_DISABLE                                (0x00000100U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_HST_ENABLED                                (0x00000100U)

#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_SHIFT                                   (9U)
#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_MASK                                    (0x00000200U)
#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_DISABLE                                  (0x00000200U)
#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPEIF_IRQ_ENABLED                                  (0x00000200U)

#define ISP5_IRQENABLE_CLR_AEW_INT_SHIFT                                       (10U)
#define ISP5_IRQENABLE_CLR_AEW_INT_MASK                                        (0x00000400U)
#define ISP5_IRQENABLE_CLR_AEW_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQENABLE_CLR_AEW_INT_DISABLE                                      (0x00000400U)
#define ISP5_IRQENABLE_CLR_AEW_INT_DISABLED                                     (0x00000000U)
#define ISP5_IRQENABLE_CLR_AEW_INT_ENABLED                                      (0x00000400U)

#define ISP5_IRQENABLE_CLR_AF_INT_SHIFT                                        (11U)
#define ISP5_IRQENABLE_CLR_AF_INT_MASK                                         (0x00000800U)
#define ISP5_IRQENABLE_CLR_AF_INT_NOACTION                                      (0x00000000U)
#define ISP5_IRQENABLE_CLR_AF_INT_DISABLE                                       (0x00000800U)
#define ISP5_IRQENABLE_CLR_AF_INT_DISABLED                                      (0x00000000U)
#define ISP5_IRQENABLE_CLR_AF_INT_ENABLED                                       (0x00000800U)

#define ISP5_IRQENABLE_CLR_H3A_INT_SHIFT                                       (12U)
#define ISP5_IRQENABLE_CLR_H3A_INT_MASK                                        (0x00001000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_NOACTION                                     (0x00000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_DISABLE                                      (0x00001000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_DISABLED                                     (0x00000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_ENABLED                                      (0x00001000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_SHIFT                                   (13U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_MASK                                    (0x00002000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_DISABLE                                  (0x00002000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_REG_ENABLED                                  (0x00002000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_SHIFT                              (14U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_MASK                               (0x00004000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_NOACTION                            (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_DISABLE                             (0x00004000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_DISABLED                            (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_LAST_PIX_ENABLED                             (0x00004000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_SHIFT                                   (15U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_MASK                                    (0x00008000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_DISABLE                                  (0x00008000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_DMA_ENABLED                                  (0x00008000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_SHIFT                               (16U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_MASK                                (0x00010000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_NOACTION                             (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_DISABLE                              (0x00010000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_DISABLED                             (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZA_ENABLED                              (0x00010000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_SHIFT                               (17U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_MASK                                (0x00020000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_NOACTION                             (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_DISABLE                              (0x00020000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_DISABLED                             (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_CYC_RZB_ENABLED                              (0x00020000U)

#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_SHIFT                                  (18U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_MASK                                   (0x00040000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_DISABLE                                 (0x00040000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_OVF_ENABLED                                 (0x00040000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_SHIFT                                  (22U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_MASK                                   (0x00400000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_DISABLE                                 (0x00400000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF0_ENABLED                                 (0x00400000U)

#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_SHIFT                                  (23U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_MASK                                   (0x00800000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_NOACTION                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_DISABLE                                 (0x00800000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_DISABLED                                (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_INT_EOF1_ENABLED                                 (0x00800000U)

#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_SHIFT                                   (24U)
#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_MASK                                    (0x01000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_DISABLE                                  (0x01000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_H3A_INT_EOF_ENABLED                                  (0x01000000U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_SHIFT                                 (25U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_MASK                                  (0x02000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_NOACTION                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_DISABLE                                (0x02000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_DISABLED                               (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_EOF_ENABLED                                (0x02000000U)

#define ISP5_IRQENABLE_CLR_RESERVED1_SHIFT                                     (26U)
#define ISP5_IRQENABLE_CLR_RESERVED1_MASK                                      (0x04000000U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_SHIFT                             (27U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_MASK                              (0x08000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_NOACTION                           (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_DISABLE                            (0x08000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_DISABLED                           (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_INI_ENABLED                            (0x08000000U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_SHIFT                           (28U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_MASK                            (0x10000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_DISABLE                          (0x10000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW0_ENABLED                          (0x10000000U)

#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_SHIFT                           (29U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_MASK                            (0x20000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_DISABLE                          (0x20000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_IPIPE_INT_DPC_RNEW1_ENABLED                          (0x20000000U)

#define ISP5_IRQENABLE_CLR_RESERVED2_SHIFT                                     (30U)
#define ISP5_IRQENABLE_CLR_RESERVED2_MASK                                      (0x40000000U)

#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_SHIFT                                   (31U)
#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_MASK                                    (0x80000000U)
#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_NOACTION                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_DISABLE                                  (0x80000000U)
#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_DISABLED                                 (0x00000000U)
#define ISP5_IRQENABLE_CLR_OCP_ERR_IRQ_ENABLED                                  (0x80000000U)

#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_SHIFT                           (19U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_MASK                            (0x00080000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_NOACTION                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_DISABLE                          (0x00080000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_DISABLED                         (0x00000000U)
#define ISP5_IRQENABLE_CLR_RSZ_FIFO_IN_BLK_ERR_ENABLED                          (0x00080000U)

#define ISP5_IRQENABLE_CLR_RESERVED_SHIFT                                      (20U)
#define ISP5_IRQENABLE_CLR_RESERVED_MASK                                       (0x00300000U)

#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_SHIFT                                 (0U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_MASK                                  (0x00000001U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_NOACTION                               (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_ENABLE                                 (0x00000001U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_DISABLED                               (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_BSC_ENABLED                                (0x00000001U)

#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_SHIFT                                 (1U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_MASK                                  (0x00000002U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_NOACTION                               (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_ENABLE                                 (0x00000002U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_DISABLED                               (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_HST_ENABLED                                (0x00000002U)

#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_SHIFT                           (2U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_MASK                            (0x00000004U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_NOACTION                         (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_ENABLE                           (0x00000004U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_DISABLED                         (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW0_ENABLED                          (0x00000004U)

#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_SHIFT                            (3U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_MASK                             (0x00000008U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_NOACTION                          (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_ENABLE                            (0x00000008U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_DISABLED                          (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_LAST_PIX_ENABLED                           (0x00000008U)

#define ISP5_DMAENABLE_SET_RESERVED_SHIFT                                      (5U)
#define ISP5_DMAENABLE_SET_RESERVED_MASK                                       (0xffffffe0U)

#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_SHIFT                           (4U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_MASK                            (0x00000010U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_NOACTION                         (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_ENABLE                           (0x00000010U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_DISABLED                         (0x00000000U)
#define ISP5_DMAENABLE_SET_IPIPE_INT_DPC_RNEW1_ENABLED                          (0x00000010U)

#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_SHIFT                                 (0U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_MASK                                  (0x00000001U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_NOACTION                               (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_DISABLE                                (0x00000001U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_DISABLED                               (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_BSC_ENABLED                                (0x00000001U)

#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_SHIFT                                 (1U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_MASK                                  (0x00000002U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_NOACTION                               (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_DISABLE                                (0x00000002U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_DISABLED                               (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_HST_ENABLED                                (0x00000002U)

#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_SHIFT                           (2U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_MASK                            (0x00000004U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_NOACTION                         (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_DISABLE                          (0x00000004U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_DISABLED                         (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW0_ENABLED                          (0x00000004U)

#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_SHIFT                            (3U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_MASK                             (0x00000008U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_NOACTION                          (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_DISABLE                           (0x00000008U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_DISABLED                          (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_LAST_PIX_ENABLED                           (0x00000008U)

#define ISP5_DMAENABLE_CLR_RESERVED_SHIFT                                      (5U)
#define ISP5_DMAENABLE_CLR_RESERVED_MASK                                       (0xffffffe0U)

#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_SHIFT                           (4U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_MASK                            (0x00000010U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_NOACTION                         (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_DISABLE                          (0x00000010U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_DISABLED                         (0x00000000U)
#define ISP5_DMAENABLE_CLR_IPIPE_INT_DPC_RNEW1_ENABLED                          (0x00000010U)

#define ISP5_CTRL_OCP_WRNP_SHIFT                                               (0U)
#define ISP5_CTRL_OCP_WRNP_MASK                                                (0x00000001U)
#define ISP5_CTRL_OCP_WRNP_NEWENUM1                                             (0x00000000U)
#define ISP5_CTRL_OCP_WRNP_NEWENUM2                                             (0x00000001U)

#define ISP5_CTRL_PSYNC_CLK_SEL_SHIFT                                          (8U)
#define ISP5_CTRL_PSYNC_CLK_SEL_MASK                                           (0x00000100U)
#define ISP5_CTRL_PSYNC_CLK_SEL_NEWENUM1                                        (0x00000000U)
#define ISP5_CTRL_PSYNC_CLK_SEL_NEWENUM2                                        (0x00000100U)

#define ISP5_CTRL_SYNC_ENABLE_SHIFT                                            (9U)
#define ISP5_CTRL_SYNC_ENABLE_MASK                                             (0x00000200U)
#define ISP5_CTRL_SYNC_ENABLE_NEWENUM1                                          (0x00000000U)
#define ISP5_CTRL_SYNC_ENABLE_NEWENUM2                                          (0x00000200U)

#define ISP5_CTRL_IPIPEIF_CLK_ENABLE_SHIFT                                     (10U)
#define ISP5_CTRL_IPIPEIF_CLK_ENABLE_MASK                                      (0x00000400U)
#define ISP5_CTRL_IPIPEIF_CLK_ENABLE_NEWENUM1                                   (0x00000000U)
#define ISP5_CTRL_IPIPEIF_CLK_ENABLE_NEWENUM2                                   (0x00000400U)

#define ISP5_CTRL_IPIPE_CLK_ENABLE_SHIFT                                       (11U)
#define ISP5_CTRL_IPIPE_CLK_ENABLE_MASK                                        (0x00000800U)
#define ISP5_CTRL_IPIPE_CLK_ENABLE_NEWENUM1                                     (0x00000000U)
#define ISP5_CTRL_IPIPE_CLK_ENABLE_NEWENUM2                                     (0x00000800U)

#define ISP5_CTRL_RSZ_CLK_ENABLE_SHIFT                                         (12U)
#define ISP5_CTRL_RSZ_CLK_ENABLE_MASK                                          (0x00001000U)
#define ISP5_CTRL_RSZ_CLK_ENABLE_NEWENUM1                                       (0x00000000U)
#define ISP5_CTRL_RSZ_CLK_ENABLE_NEWENUM2                                       (0x00001000U)

#define ISP5_CTRL_H3A_CLK_ENABLE_SHIFT                                         (13U)
#define ISP5_CTRL_H3A_CLK_ENABLE_MASK                                          (0x00002000U)
#define ISP5_CTRL_H3A_CLK_ENABLE_NEWENUM1                                       (0x00000000U)
#define ISP5_CTRL_H3A_CLK_ENABLE_NEWENUM2                                       (0x00002000U)

#define ISP5_CTRL_ISIF_CLK_ENABLE_SHIFT                                        (14U)
#define ISP5_CTRL_ISIF_CLK_ENABLE_MASK                                         (0x00004000U)
#define ISP5_CTRL_ISIF_CLK_ENABLE_NEWENUM1                                      (0x00000000U)
#define ISP5_CTRL_ISIF_CLK_ENABLE_NEWENUM2                                      (0x00004000U)

#define ISP5_CTRL_BL_CLK_ENABLE_SHIFT                                          (15U)
#define ISP5_CTRL_BL_CLK_ENABLE_MASK                                           (0x00008000U)
#define ISP5_CTRL_BL_CLK_ENABLE_NEWENUM1                                        (0x00000000U)
#define ISP5_CTRL_BL_CLK_ENABLE_NEWENUM2                                        (0x00008000U)

#define ISP5_CTRL_VBUSM_CPRIORITY_SHIFT                                        (1U)
#define ISP5_CTRL_VBUSM_CPRIORITY_MASK                                         (0x0000000eU)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM1                                      (0x00000000U)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM2                                      (0x00000002U)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM3                                      (0x00000004U)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM4                                      (0x00000006U)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM5                                      (0x00000008U)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM6                                      (0x0000000aU)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM7                                      (0x0000000cU)
#define ISP5_CTRL_VBUSM_CPRIORITY_NEWENUM8                                      (0x0000000eU)

#define ISP5_CTRL_VBUSM_CIDS_SHIFT                                             (4U)
#define ISP5_CTRL_VBUSM_CIDS_MASK                                              (0x000000f0U)

#define ISP5_CTRL_MSTANDBY_SHIFT                                               (24U)
#define ISP5_CTRL_MSTANDBY_MASK                                                (0x01000000U)
#define ISP5_CTRL_MSTANDBY_NEWENUM1                                             (0x00000000U)
#define ISP5_CTRL_MSTANDBY_NEWENUM2                                             (0x01000000U)

#define ISP5_CTRL_VD_PULSE_EXT_SHIFT                                           (23U)
#define ISP5_CTRL_VD_PULSE_EXT_MASK                                            (0x00800000U)
#define ISP5_CTRL_VD_PULSE_EXT_NEWENUM1                                         (0x00000000U)
#define ISP5_CTRL_VD_PULSE_EXT_NEWENUM2                                         (0x00800000U)

#define ISP5_CTRL_PCLK_INV_SHIFT                                               (22U)
#define ISP5_CTRL_PCLK_INV_MASK                                                (0x00400000U)
#define ISP5_CTRL_PCLK_INV_NEWENUM1                                             (0x00000000U)
#define ISP5_CTRL_PCLK_INV_NEWENUM2                                             (0x00400000U)

#define ISP5_CTRL_DMA3_CFG_SHIFT                                               (30U)
#define ISP5_CTRL_DMA3_CFG_MASK                                                (0xc0000000U)
#define ISP5_CTRL_DMA3_CFG_NEWENUM1                                             (0x00000000U)
#define ISP5_CTRL_DMA3_CFG_NEWENUM2                                             (0x40000000U)
#define ISP5_CTRL_DMA3_CFG_NEWENUM3                                             (0x80000000U)
#define ISP5_CTRL_DMA3_CFG_NEWENUM4                                             (0xc0000000U)

#define ISP5_CTRL_RESERVED1_SHIFT                                              (28U)
#define ISP5_CTRL_RESERVED1_MASK                                               (0x30000000U)

#define ISP5_CTRL_MSTANDDBY_WAIT_SHIFT                                         (20U)
#define ISP5_CTRL_MSTANDDBY_WAIT_MASK                                          (0x00100000U)
#define ISP5_CTRL_MSTANDDBY_WAIT_NEWENUM1                                       (0x00000000U)
#define ISP5_CTRL_MSTANDDBY_WAIT_NEWENUM2                                       (0x00100000U)

#define ISP5_CTRL_DPC_EVT_INI_SHIFT                                            (25U)
#define ISP5_CTRL_DPC_EVT_INI_MASK                                             (0x02000000U)
#define ISP5_CTRL_DPC_EVT_INI_NEWENUM1                                          (0x00000000U)
#define ISP5_CTRL_DPC_EVT_INI_NEWENUM2                                          (0x02000000U)

#define ISP5_CTRL_HST_RD_CHK_SHIFT                                             (26U)
#define ISP5_CTRL_HST_RD_CHK_MASK                                              (0x04000000U)
#define ISP5_CTRL_HST_RD_CHK_NEWENUM1                                           (0x00000000U)
#define ISP5_CTRL_HST_RD_CHK_NEWENUM2                                           (0x04000000U)
#define ISP5_CTRL_HST_RD_CHK_NEWENUM3                                           (0x00000000U)
#define ISP5_CTRL_HST_RD_CHK_NEWENUM4                                           (0x04000000U)

#define ISP5_CTRL_BSC_RD_CHK_SHIFT                                             (27U)
#define ISP5_CTRL_BSC_RD_CHK_MASK                                              (0x08000000U)
#define ISP5_CTRL_BSC_RD_CHK_NEWENUM1                                           (0x00000000U)
#define ISP5_CTRL_BSC_RD_CHK_NEWENUM2                                           (0x08000000U)
#define ISP5_CTRL_BSC_RD_CHK_NEWENUM3                                           (0x00000000U)
#define ISP5_CTRL_BSC_RD_CHK_NEWENUM4                                           (0x08000000U)

#define ISP5_CTRL_MFLAG_SHIFT                                                  (21U)
#define ISP5_CTRL_MFLAG_MASK                                                   (0x00200000U)
#define ISP5_CTRL_MFLAG_NEWENUM1                                                (0x00000000U)
#define ISP5_CTRL_MFLAG_NEWENUM2                                                (0x00200000U)

#define ISP5_CTRL_CNFA_CLK_ENABLE_SHIFT                                        (16U)
#define ISP5_CTRL_CNFA_CLK_ENABLE_MASK                                         (0x00010000U)
#define ISP5_CTRL_CNFA_CLK_ENABLE_NEWENUM1                                      (0x00000000U)
#define ISP5_CTRL_CNFA_CLK_ENABLE_NEWENUM2                                      (0x00010000U)

#define ISP5_CTRL_CNFB_CLK_ENABLE_SHIFT                                        (17U)
#define ISP5_CTRL_CNFB_CLK_ENABLE_MASK                                         (0x00020000U)
#define ISP5_CTRL_CNFB_CLK_ENABLE_NEWENUM1                                      (0x00000000U)
#define ISP5_CTRL_CNFB_CLK_ENABLE_NEWENUM2                                      (0x00020000U)

#define ISP5_CTRL_NSF3V_CLK_ENABLE_SHIFT                                       (18U)
#define ISP5_CTRL_NSF3V_CLK_ENABLE_MASK                                        (0x00040000U)
#define ISP5_CTRL_NSF3V_CLK_ENABLE_NEWENUM1                                     (0x00000000U)
#define ISP5_CTRL_NSF3V_CLK_ENABLE_NEWENUM2                                     (0x00040000U)

#define ISP5_CTRL_GLBCE_CLK_ENABLE_SHIFT                                       (19U)
#define ISP5_CTRL_GLBCE_CLK_ENABLE_MASK                                        (0x00080000U)
#define ISP5_CTRL_GLBCE_CLK_ENABLE_NEWENUM1                                     (0x00000000U)
#define ISP5_CTRL_GLBCE_CLK_ENABLE_NEWENUM2                                     (0x00080000U)

#define ISP5_PG_VDPOL_SHIFT                                                    (0U)
#define ISP5_PG_VDPOL_MASK                                                     (0x00000001U)
#define ISP5_PG_VDPOL_NEWENUM1                                                  (0x00000000U)
#define ISP5_PG_VDPOL_NEWENUM2                                                  (0x00000001U)

#define ISP5_PG_HDPOL_SHIFT                                                    (1U)
#define ISP5_PG_HDPOL_MASK                                                     (0x00000002U)
#define ISP5_PG_HDPOL_NEWENUM1                                                  (0x00000000U)
#define ISP5_PG_HDPOL_NEWENUM2                                                  (0x00000002U)

#define ISP5_PG_WEN_SHIFT                                                      (2U)
#define ISP5_PG_WEN_MASK                                                       (0x00000004U)
#define ISP5_PG_WEN_NEWENUM1                                                    (0x00000000U)
#define ISP5_PG_WEN_NEWENUM2                                                    (0x00000004U)

#define ISP5_PG_EN_SHIFT                                                       (3U)
#define ISP5_PG_EN_MASK                                                        (0x00000008U)
#define ISP5_PG_EN_NEWENUM1                                                     (0x00000000U)
#define ISP5_PG_EN_NEWENUM2                                                     (0x00000008U)

#define ISP5_PG_SRC_SEL_SHIFT                                                  (4U)
#define ISP5_PG_SRC_SEL_MASK                                                   (0x00000030U)
#define ISP5_PG_SRC_SEL_NEWENUM1                                                (0x00000000U)
#define ISP5_PG_SRC_SEL_NEWENUM2                                                (0x00000010U)
#define ISP5_PG_SRC_SEL_NEWENUM3                                                (0x00000020U)
#define ISP5_PG_SRC_SEL_NEWENUM4                                                (0x00000030U)

#define ISP5_PG_RESERVED_SHIFT                                                 (6U)
#define ISP5_PG_RESERVED_MASK                                                  (0xffffffc0U)

#define ISP5_PG_PULSE_CTRL_HDW_SHIFT                                           (0U)
#define ISP5_PG_PULSE_CTRL_HDW_MASK                                            (0x00001fffU)

#define ISP5_PG_PULSE_CTRL_VDW_SHIFT                                           (16U)
#define ISP5_PG_PULSE_CTRL_VDW_MASK                                            (0x0fff0000U)

#define ISP5_PG_PULSE_CTRL_RESERVED_SHIFT                                      (13U)
#define ISP5_PG_PULSE_CTRL_RESERVED_MASK                                       (0x0000e000U)

#define ISP5_PG_PULSE_CTRL_RESERVED1_SHIFT                                     (28U)
#define ISP5_PG_PULSE_CTRL_RESERVED1_MASK                                      (0xf0000000U)

#define ISP5_PG_FRAME_SIZE_HLPFR_SHIFT                                         (0U)
#define ISP5_PG_FRAME_SIZE_HLPFR_MASK                                          (0x0000ffffU)

#define ISP5_PG_FRAME_SIZE_PPLN_SHIFT                                          (16U)
#define ISP5_PG_FRAME_SIZE_PPLN_MASK                                           (0xffff0000U)

#define ISP5_MPSR_ISIF_LIN_TB_SHIFT                                            (1U)
#define ISP5_MPSR_ISIF_LIN_TB_MASK                                             (0x00000002U)
#define ISP5_MPSR_ISIF_LIN_TB_NEWENUM1                                          (0x00000000U)
#define ISP5_MPSR_ISIF_LIN_TB_NEWENUM2                                          (0x00000002U)

#define ISP5_MPSR_ISIF_LSC_TB1_SHIFT                                           (3U)
#define ISP5_MPSR_ISIF_LSC_TB1_MASK                                            (0x00000008U)
#define ISP5_MPSR_ISIF_LSC_TB1_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_ISIF_LSC_TB1_NEWENUM2                                         (0x00000008U)

#define ISP5_MPSR_ISIF_DCLAMP_SHIFT                                            (4U)
#define ISP5_MPSR_ISIF_DCLAMP_MASK                                             (0x00000010U)
#define ISP5_MPSR_ISIF_DCLAMP_NEWENUM1                                          (0x00000000U)
#define ISP5_MPSR_ISIF_DCLAMP_NEWENUM2                                          (0x00000010U)

#define ISP5_MPSR_IPIPE_DPC_TB_SHIFT                                           (5U)
#define ISP5_MPSR_IPIPE_DPC_TB_MASK                                            (0x00000020U)
#define ISP5_MPSR_IPIPE_DPC_TB_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_IPIPE_DPC_TB_NEWENUM2                                         (0x00000020U)

#define ISP5_MPSR_IPIPE_GMM_TBB_SHIFT                                          (6U)
#define ISP5_MPSR_IPIPE_GMM_TBB_MASK                                           (0x00000040U)
#define ISP5_MPSR_IPIPE_GMM_TBB_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_GMM_TBB_NEWENUM2                                        (0x00000040U)

#define ISP5_MPSR_IPIPE_GMM_TBG_SHIFT                                          (7U)
#define ISP5_MPSR_IPIPE_GMM_TBG_MASK                                           (0x00000080U)
#define ISP5_MPSR_IPIPE_GMM_TBG_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_GMM_TBG_NEWENUM2                                        (0x00000080U)

#define ISP5_MPSR_IPIPE_GMM_TBR_SHIFT                                          (8U)
#define ISP5_MPSR_IPIPE_GMM_TBR_MASK                                           (0x00000100U)
#define ISP5_MPSR_IPIPE_GMM_TBR_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_GMM_TBR_NEWENUM2                                        (0x00000100U)

#define ISP5_MPSR_IPIPE_YEE_TB_SHIFT                                           (9U)
#define ISP5_MPSR_IPIPE_YEE_TB_MASK                                            (0x00000200U)
#define ISP5_MPSR_IPIPE_YEE_TB_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_IPIPE_YEE_TB_NEWENUM2                                         (0x00000200U)

#define ISP5_MPSR_IPIPE_GBC_TB_SHIFT                                           (10U)
#define ISP5_MPSR_IPIPE_GBC_TB_MASK                                            (0x00000400U)
#define ISP5_MPSR_IPIPE_GBC_TB_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_IPIPE_GBC_TB_NEWENUM2                                         (0x00000400U)

#define ISP5_MPSR_IPIPE_D3L_TB0_SHIFT                                          (11U)
#define ISP5_MPSR_IPIPE_D3L_TB0_MASK                                           (0x00000800U)
#define ISP5_MPSR_IPIPE_D3L_TB0_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_D3L_TB0_NEWENUM2                                        (0x00000800U)

#define ISP5_MPSR_IPIPE_D3L_TB1_SHIFT                                          (12U)
#define ISP5_MPSR_IPIPE_D3L_TB1_MASK                                           (0x00001000U)
#define ISP5_MPSR_IPIPE_D3L_TB1_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_D3L_TB1_NEWENUM2                                        (0x00001000U)

#define ISP5_MPSR_IPIPE_D3L_TB2_SHIFT                                          (13U)
#define ISP5_MPSR_IPIPE_D3L_TB2_MASK                                           (0x00002000U)
#define ISP5_MPSR_IPIPE_D3L_TB2_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_D3L_TB2_NEWENUM2                                        (0x00002000U)

#define ISP5_MPSR_IPIPE_D3L_TB3_SHIFT                                          (14U)
#define ISP5_MPSR_IPIPE_D3L_TB3_MASK                                           (0x00004000U)
#define ISP5_MPSR_IPIPE_D3L_TB3_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_D3L_TB3_NEWENUM2                                        (0x00004000U)

#define ISP5_MPSR_IPIPE_HST_TB0_SHIFT                                          (15U)
#define ISP5_MPSR_IPIPE_HST_TB0_MASK                                           (0x00008000U)
#define ISP5_MPSR_IPIPE_HST_TB0_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_HST_TB0_NEWENUM2                                        (0x00008000U)

#define ISP5_MPSR_IPIPE_HST_TB1_SHIFT                                          (16U)
#define ISP5_MPSR_IPIPE_HST_TB1_MASK                                           (0x00010000U)
#define ISP5_MPSR_IPIPE_HST_TB1_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_HST_TB1_NEWENUM2                                        (0x00010000U)

#define ISP5_MPSR_IPIPE_HST_TB2_SHIFT                                          (17U)
#define ISP5_MPSR_IPIPE_HST_TB2_MASK                                           (0x00020000U)
#define ISP5_MPSR_IPIPE_HST_TB2_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_HST_TB2_NEWENUM2                                        (0x00020000U)

#define ISP5_MPSR_IPIPE_HST_TB3_SHIFT                                          (18U)
#define ISP5_MPSR_IPIPE_HST_TB3_MASK                                           (0x00040000U)
#define ISP5_MPSR_IPIPE_HST_TB3_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_HST_TB3_NEWENUM2                                        (0x00040000U)

#define ISP5_MPSR_IPIPE_BSC_TB0_SHIFT                                          (19U)
#define ISP5_MPSR_IPIPE_BSC_TB0_MASK                                           (0x00080000U)
#define ISP5_MPSR_IPIPE_BSC_TB0_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_BSC_TB0_NEWENUM2                                        (0x00080000U)

#define ISP5_MPSR_IPIPE_BSC_TB1_SHIFT                                          (20U)
#define ISP5_MPSR_IPIPE_BSC_TB1_MASK                                           (0x00100000U)
#define ISP5_MPSR_IPIPE_BSC_TB1_NEWENUM1                                        (0x00000000U)
#define ISP5_MPSR_IPIPE_BSC_TB1_NEWENUM2                                        (0x00100000U)

#define ISP5_MPSR_IPIPE_GAMMA_RGB_COPY_SHIFT                                   (24U)
#define ISP5_MPSR_IPIPE_GAMMA_RGB_COPY_MASK                                    (0x01000000U)
#define ISP5_MPSR_IPIPE_GAMMA_RGB_COPY_NEWENUM1                                 (0x00000000U)
#define ISP5_MPSR_IPIPE_GAMMA_RGB_COPY_NEWENUM2                                 (0x01000000U)

#define ISP5_MPSR_RESERVED_SHIFT                                               (0U)
#define ISP5_MPSR_RESERVED_MASK                                                (0x00000001U)

#define ISP5_MPSR_RESERVED1_SHIFT                                              (21U)
#define ISP5_MPSR_RESERVED1_MASK                                               (0x00e00000U)

#define ISP5_MPSR_ISIF_LSC_TB0_SHIFT                                           (2U)
#define ISP5_MPSR_ISIF_LSC_TB0_MASK                                            (0x00000004U)
#define ISP5_MPSR_ISIF_LSC_TB0_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_ISIF_LSC_TB0_NEWENUM2                                         (0x00000004U)

#define ISP5_MPSR_ISP_GLBCE_TB_SHIFT                                           (28U)
#define ISP5_MPSR_ISP_GLBCE_TB_MASK                                            (0x10000000U)
#define ISP5_MPSR_ISP_GLBCE_TB_NEWENUM1                                         (0x00000000U)
#define ISP5_MPSR_ISP_GLBCE_TB_NEWENUM2                                         (0x10000000U)

#define ISP5_MPSR_RESERVED2_SHIFT                                              (25U)
#define ISP5_MPSR_RESERVED2_MASK                                               (0x0e000000U)

#define ISP5_MPSR_IPIPEIF_DECMP_LUT0_SHIFT                                     (29U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT0_MASK                                      (0x20000000U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT0_NEWENUM1                                   (0x00000000U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT0_NEWENUM2                                   (0x20000000U)

#define ISP5_MPSR_IPIPEIF_DECMP_LUT1_SHIFT                                     (30U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT1_MASK                                      (0x40000000U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT1_NEWENUM1                                   (0x00000000U)
#define ISP5_MPSR_IPIPEIF_DECMP_LUT1_NEWENUM2                                   (0x40000000U)

#define ISP5_MPSR_IPIPEIF_CMP_LUT2_SHIFT                                       (31U)
#define ISP5_MPSR_IPIPEIF_CMP_LUT2_MASK                                        (0x80000000U)
#define ISP5_MPSR_IPIPEIF_CMP_LUT2_NEWENUM1                                     (0x00000000U)
#define ISP5_MPSR_IPIPEIF_CMP_LUT2_NEWENUM2                                     (0x80000000U)

#define ISP5_BL_MTC_1_IPIPEIF_R_SHIFT                                          (0U)
#define ISP5_BL_MTC_1_IPIPEIF_R_MASK                                           (0x0000ffffU)

#define ISP5_BL_MTC_1_ISIF_R_SHIFT                                             (16U)
#define ISP5_BL_MTC_1_ISIF_R_MASK                                              (0xffff0000U)

#define ISP5_BL_MTC_2_H3A_W_SHIFT                                              (16U)
#define ISP5_BL_MTC_2_H3A_W_MASK                                               (0xffff0000U)

#define ISP5_BL_MTC_2_RESERVED_SHIFT                                           (0U)
#define ISP5_BL_MTC_2_RESERVED_MASK                                            (0x0000ffffU)

#define ISP5_BL_VBUSM_LASTCMD_DLY_SHIFT                                        (0U)
#define ISP5_BL_VBUSM_LASTCMD_DLY_MASK                                         (0x0000001fU)

#define ISP5_BL_VBUSM_MFLAG_THRES_SHIFT                                        (5U)
#define ISP5_BL_VBUSM_MFLAG_THRES_MASK                                         (0x00000020U)
#define ISP5_BL_VBUSM_MFLAG_THRES_NEWENUM1                                      (0x00000000U)
#define ISP5_BL_VBUSM_MFLAG_THRES_NEWENUM2                                      (0x00000020U)

#define ISP5_BL_VBUSM_RESERVED_SHIFT                                           (6U)
#define ISP5_BL_VBUSM_RESERVED_MASK                                            (0xffffffc0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_SYS1_H_ */

