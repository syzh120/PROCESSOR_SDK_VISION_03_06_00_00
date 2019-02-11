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

#ifndef HW_ISS_SIMCOP_REGS_H_
#define HW_ISS_SIMCOP_REGS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define SIMCOP_HL_REVISION                                          (0x0U)
#define SIMCOP_HL_HWINFO                                            (0x4U)
#define SIMCOP_HL_SYSCONFIG                                         (0x10U)
#define SIMCOP_HL_IRQ_EOI                                           (0x1cU)
#define SIMCOP_HL_IRQSTATUS_RAW(m)                                  (0x20U + ((m) * (uint32_t)0x10))
#define SIMCOP_HL_IRQSTATUS(m)                                      (0x24U + ((m) * (uint32_t)0x10))
#define SIMCOP_HL_IRQENABLE_SET(m)                                  (0x28U + ((m) * (uint32_t)0x10))
#define SIMCOP_HL_IRQENABLE_CLR(m)                                  (0x2cU + ((m) * (uint32_t)0x10))
#define SIMCOP_CTRL                                                 (0x60U)
#define SIMCOP_CLKCTRL                                              (0x64U)
#define SIMCOP_HWSEQ_CTRL                                           (0x68U)
#define SIMCOP_HWSEQ_STATUS                                         (0x6cU)
#define SIMCOP_HWSEQ_OVERRIDE                                       (0x70U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE                             (0x74U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE                           (0x78U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE                            (0x7cU)
#define SIMCOP_HWSEQ_STEP_SWITCH(m)                                 (0x84U + ((m) * 0x10U))
#define SIMCOP_HWSEQ_STEP_CTRL(m)                                   (0x80U + ((m) * 0x10U))
#define SIMCOP_HWSEQ_STEP_IMX_CTRL(m)                               (0x88U + ((m) * 0x10U))
#define SIMCOP_HWSEQ_STEP_CTRL2(m)                                  (0x8cU + ((m) * 0x10U))
#define SIMCOP_CTRL2                                                (0xfcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define SIMCOP_HL_REVISION_Y_MINOR_SHIFT                                                (0U)
#define SIMCOP_HL_REVISION_Y_MINOR_MASK                                                 (0x0000003fU)

#define SIMCOP_HL_REVISION_CUSTOM_SHIFT                                                 (6U)
#define SIMCOP_HL_REVISION_CUSTOM_MASK                                                  (0x000000c0U)
#define SIMCOP_HL_REVISION_CUSTOM_STANDARD                                               (0U)

#define SIMCOP_HL_REVISION_X_MAJOR_SHIFT                                                (8U)
#define SIMCOP_HL_REVISION_X_MAJOR_MASK                                                 (0x00000700U)

#define SIMCOP_HL_REVISION_R_RTL_SHIFT                                                  (11U)
#define SIMCOP_HL_REVISION_R_RTL_MASK                                                   (0x0000f800U)

#define SIMCOP_HL_REVISION_FUNC_SHIFT                                                   (16U)
#define SIMCOP_HL_REVISION_FUNC_MASK                                                    (0x0fff0000U)

#define SIMCOP_HL_REVISION_RESERVED_SHIFT                                               (28U)
#define SIMCOP_HL_REVISION_RESERVED_MASK                                                (0x30000000U)

#define SIMCOP_HL_REVISION_SCHEME_SHIFT                                                 (30U)
#define SIMCOP_HL_REVISION_SCHEME_MASK                                                  (0xc0000000U)
#define SIMCOP_HL_REVISION_SCHEME_H08                                                    (1U)
#define SIMCOP_HL_REVISION_SCHEME_LEGACY                                                 (0U)

#define SIMCOP_HL_HWINFO_LDC_ENABLE_SHIFT                                               (0U)
#define SIMCOP_HL_HWINFO_LDC_ENABLE_MASK                                                (0x00000001U)
#define SIMCOP_HL_HWINFO_LDC_ENABLE_DISABLE                                              (0U)
#define SIMCOP_HL_HWINFO_LDC_ENABLE                                                      (1U)

#define SIMCOP_HL_HWINFO_DCT_ENABLE_SHIFT                                               (1U)
#define SIMCOP_HL_HWINFO_DCT_ENABLE_MASK                                                (0x00000002U)
#define SIMCOP_HL_HWINFO_DCT_ENABLE                                                      (1U)
#define SIMCOP_HL_HWINFO_DCT_ENABLE_DISABLE                                              (0U)

#define SIMCOP_HL_HWINFO_VLCDJ_ENABLE_SHIFT                                             (2U)
#define SIMCOP_HL_HWINFO_VLCDJ_ENABLE_MASK                                              (0x00000004U)
#define SIMCOP_HL_HWINFO_VLCDJ_ENABLE_DISABLE                                            (0U)
#define SIMCOP_HL_HWINFO_VLCDJ_ENABLE                                                    (1U)

#define SIMCOP_HL_HWINFO_NSF_ENABLE_SHIFT                                               (3U)
#define SIMCOP_HL_HWINFO_NSF_ENABLE_MASK                                                (0x00000008U)
#define SIMCOP_HL_HWINFO_NSF_ENABLE_DISABLE                                              (0U)
#define SIMCOP_HL_HWINFO_NSF_ENABLE                                                      (1U)

#define SIMCOP_HL_HWINFO_IMX_A_ENABLE_SHIFT                                             (4U)
#define SIMCOP_HL_HWINFO_IMX_A_ENABLE_MASK                                              (0x00000010U)
#define SIMCOP_HL_HWINFO_IMX_A_ENABLE_DISABLE                                            (0U)
#define SIMCOP_HL_HWINFO_IMX_A_ENABLE                                                    (1U)

#define SIMCOP_HL_HWINFO_IMX_B_ENABLE_SHIFT                                             (5U)
#define SIMCOP_HL_HWINFO_IMX_B_ENABLE_MASK                                              (0x00000020U)
#define SIMCOP_HL_HWINFO_IMX_B_ENABLE_DISABLE                                            (0U)
#define SIMCOP_HL_HWINFO_IMX_B_ENABLE                                                    (1U)

#define SIMCOP_HL_HWINFO_IMAGE_BUFFERS_SHIFT                                            (8U)
#define SIMCOP_HL_HWINFO_IMAGE_BUFFERS_MASK                                             (0x00000300U)
#define SIMCOP_HL_HWINFO_IMAGE_BUFFERS_IM4                                               (0U)
#define SIMCOP_HL_HWINFO_IMAGE_BUFFERS_IM8                                               (1U)

#define SIMCOP_HL_HWINFO_ROT_A_ENABLE_SHIFT                                             (6U)
#define SIMCOP_HL_HWINFO_ROT_A_ENABLE_MASK                                              (0x00000040U)
#define SIMCOP_HL_HWINFO_ROT_A_ENABLE_DISABLE                                            (0U)
#define SIMCOP_HL_HWINFO_ROT_A_ENABLE                                                    (1U)

#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_SHIFT                                          (14U)
#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_MASK                                           (0x0000c000U)
#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_ZERO                                            (0U)
#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_ONE                                             (1U)
#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_TWO                                             (2U)
#define SIMCOP_HL_HWINFO_LDCIMXNSF_BOOST_THREE                                           (3U)

#define SIMCOP_HL_HWINFO_NSF3_ENABLE_SHIFT                                              (7U)
#define SIMCOP_HL_HWINFO_NSF3_ENABLE_MASK                                               (0x00000080U)
#define SIMCOP_HL_HWINFO_NSF3_ENABLE_DISABLE                                             (0U)
#define SIMCOP_HL_HWINFO_NSF3_ENABLE                                                     (1U)

#define SIMCOP_HL_HWINFO_VTNF_ENABLE_SHIFT                                              (16U)
#define SIMCOP_HL_HWINFO_VTNF_ENABLE_MASK                                               (0x00010000U)

#define SIMCOP_HL_HWINFO_RESERVED_SHIFT                                                 (10U)
#define SIMCOP_HL_HWINFO_RESERVED_MASK                                                  (0x00003c00U)

#define SIMCOP_HL_HWINFO_RESERVED1_SHIFT                                                (17U)
#define SIMCOP_HL_HWINFO_RESERVED1_MASK                                                 (0xfffe0000U)

#define SIMCOP_HL_SYSCONFIG_SOFTRESET_SHIFT                                             (0U)
#define SIMCOP_HL_SYSCONFIG_SOFTRESET_MASK                                              (0x00000001U)
#define SIMCOP_HL_SYSCONFIG_SOFTRESET_DONE                                               (0U)
#define SIMCOP_HL_SYSCONFIG_SOFTRESET_PENDING                                            (1U)
#define SIMCOP_HL_SYSCONFIG_SOFTRESET_NOACTION                                           (0U)
#define SIMCOP_HL_SYSCONFIG_SOFTRESET_RESET                                              (1U)

#define SIMCOP_HL_SYSCONFIG_RESERVED_SHIFT                                              (1U)
#define SIMCOP_HL_SYSCONFIG_RESERVED_MASK                                               (0xfffffffeU)

#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_SHIFT                                             (0U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_MASK                                              (0x00000003U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_READ0                                              (0U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_EOI0                                               (0U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_EOI1                                               (1U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_EOI2                                               (2U)
#define SIMCOP_HL_IRQ_EOI_LINE_NUMBER_EOI3                                               (3U)

#define SIMCOP_HL_IRQ_EOI_RESERVED_SHIFT                                                (2U)
#define SIMCOP_HL_IRQ_EOI_RESERVED_MASK                                                 (0xfffffffcU)

#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ0_SHIFT                                          (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ0_MASK                                           (0x00000001U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ0_NOEVENT                                         (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ0_PENDING                                         (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_SHIFT                                     (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_MASK                                      (0x00000002U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_SET                                        (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_NOEVENT                                    (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_FRAME_IRQ_PENDING                                    (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_DCT_IRQ_SHIFT                                           (2U)
#define SIMCOP_HL_IRQSTATUS_RAW_DCT_IRQ_MASK                                            (0x00000004U)

#define SIMCOP_HL_IRQSTATUS_RAW_VLCDJ_BLOC_IRQ_SHIFT                                    (3U)
#define SIMCOP_HL_IRQSTATUS_RAW_VLCDJ_BLOC_IRQ_MASK                                     (0x00000008U)

#define SIMCOP_HL_IRQSTATUS_RAW_NSF_IRQ_SHIFT                                           (4U)
#define SIMCOP_HL_IRQSTATUS_RAW_NSF_IRQ_MASK                                            (0x00000010U)

#define SIMCOP_HL_IRQSTATUS_RAW_IMX_A_IRQ_SHIFT                                         (5U)
#define SIMCOP_HL_IRQSTATUS_RAW_IMX_A_IRQ_MASK                                          (0x00000020U)

#define SIMCOP_HL_IRQSTATUS_RAW_IMX_B_IRQ_SHIFT                                         (6U)
#define SIMCOP_HL_IRQSTATUS_RAW_IMX_B_IRQ_MASK                                          (0x00000040U)

#define SIMCOP_HL_IRQSTATUS_RAW_ROT_A_SHIFT                                             (7U)
#define SIMCOP_HL_IRQSTATUS_RAW_ROT_A_MASK                                              (0x00000080U)

#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_SHIFT                                     (9U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_MASK                                      (0x00000200U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_SET                                        (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_NOEVENT                                    (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_LDC_BLOCK_IRQ_PENDING                                    (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_SHIFT                                         (10U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_MASK                                          (0x00000400U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_SET                                            (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP0_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_SHIFT                                         (11U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_MASK                                          (0x00000800U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_SET                                            (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP1_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_SHIFT                                         (12U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_MASK                                          (0x00001000U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_SET                                            (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP2_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_SHIFT                                         (13U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_MASK                                          (0x00002000U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_SET                                            (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_STEP3_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_SHIFT                                          (14U)
#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_MASK                                           (0x00004000U)
#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_SET                                             (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_NOEVENT                                         (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_DONE_IRQ_PENDING                                         (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_VLCDJ_DECODE_ERR_IRQ_SHIFT                              (15U)
#define SIMCOP_HL_IRQSTATUS_RAW_VLCDJ_DECODE_ERR_IRQ_MASK                               (0x00008000U)

#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_SHIFT                                       (16U)
#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_MASK                                        (0x00010000U)
#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_NOACTION                                     (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_SET                                          (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_NOEVENT                                      (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_OCP_ERR_IRQ_PENDING                                      (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ1_SHIFT                                          (18U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ1_MASK                                           (0x00040000U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ1_NOEVENT                                         (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_DMA_IRQ1_PENDING                                         (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_SHIFT                                (19U)
#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_MASK                                 (0x00080000U)
#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_NOACTION                              (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_SET                                   (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_NOEVENT                               (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_CPU_PROC_START_IRQ_PENDING                               (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_RESERVED_SHIFT                                          (20U)
#define SIMCOP_HL_IRQSTATUS_RAW_RESERVED_MASK                                           (0xfff00000U)

#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_SHIFT                                          (8U)
#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_MASK                                           (0x00000100U)
#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_SET                                             (1U)
#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_NOEVENT                                         (0U)
#define SIMCOP_HL_IRQSTATUS_RAW_VTNF_IRQ_PENDING                                         (1U)

#define SIMCOP_HL_IRQSTATUS_RAW_RESERVED1_SHIFT                                         (17U)
#define SIMCOP_HL_IRQSTATUS_RAW_RESERVED1_MASK                                          (0x00020000U)

#define SIMCOP_HL_IRQSTATUS_DMA_IRQ0_SHIFT                                              (0U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ0_MASK                                               (0x00000001U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ0_NOEVENT                                             (0U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ0_PENDING                                             (1U)

#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_SHIFT                                         (1U)
#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_MASK                                          (0x00000002U)
#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_CLEAR                                          (1U)
#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_LDC_FRAME_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_DCT_IRQ_SHIFT                                               (2U)
#define SIMCOP_HL_IRQSTATUS_DCT_IRQ_MASK                                                (0x00000004U)

#define SIMCOP_HL_IRQSTATUS_VLCDJ_BLOC_IRQ_SHIFT                                        (3U)
#define SIMCOP_HL_IRQSTATUS_VLCDJ_BLOC_IRQ_MASK                                         (0x00000008U)

#define SIMCOP_HL_IRQSTATUS_NSF_IRQ_SHIFT                                               (4U)
#define SIMCOP_HL_IRQSTATUS_NSF_IRQ_MASK                                                (0x00000010U)

#define SIMCOP_HL_IRQSTATUS_IMX_A_IRQ_SHIFT                                             (5U)
#define SIMCOP_HL_IRQSTATUS_IMX_A_IRQ_MASK                                              (0x00000020U)

#define SIMCOP_HL_IRQSTATUS_IMX_B_IRQ_SHIFT                                             (6U)
#define SIMCOP_HL_IRQSTATUS_IMX_B_IRQ_MASK                                              (0x00000040U)

#define SIMCOP_HL_IRQSTATUS_ROT_A_SHIFT                                                 (7U)
#define SIMCOP_HL_IRQSTATUS_ROT_A_MASK                                                  (0x00000080U)

#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_SHIFT                                         (9U)
#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_MASK                                          (0x00000200U)
#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_CLEAR                                          (1U)
#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_NOEVENT                                        (0U)
#define SIMCOP_HL_IRQSTATUS_LDC_BLOCK_IRQ_PENDING                                        (1U)

#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_SHIFT                                             (10U)
#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_MASK                                              (0x00000400U)
#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_NOACTION                                           (0U)
#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_CLEAR                                              (1U)
#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_NOEVENT                                            (0U)
#define SIMCOP_HL_IRQSTATUS_STEP0_IRQ_PENDING                                            (1U)

#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_SHIFT                                             (11U)
#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_MASK                                              (0x00000800U)
#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_NOACTION                                           (0U)
#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_CLEAR                                              (1U)
#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_NOEVENT                                            (0U)
#define SIMCOP_HL_IRQSTATUS_STEP1_IRQ_PENDING                                            (1U)

#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_SHIFT                                             (12U)
#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_MASK                                              (0x00001000U)
#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_NOACTION                                           (0U)
#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_CLEAR                                              (1U)
#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_NOEVENT                                            (0U)
#define SIMCOP_HL_IRQSTATUS_STEP2_IRQ_PENDING                                            (1U)

#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_SHIFT                                             (13U)
#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_MASK                                              (0x00002000U)
#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_NOACTION                                           (0U)
#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_CLEAR                                              (1U)
#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_NOEVENT                                            (0U)
#define SIMCOP_HL_IRQSTATUS_STEP3_IRQ_PENDING                                            (1U)

#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_SHIFT                                              (14U)
#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_MASK                                               (0x00004000U)
#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_NOACTION                                            (0U)
#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_CLEAR                                               (1U)
#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_NOEVENT                                             (0U)
#define SIMCOP_HL_IRQSTATUS_DONE_IRQ_PENDING                                             (1U)

#define SIMCOP_HL_IRQSTATUS_VLCDJ_DECODE_ERR_IRQ_SHIFT                                  (15U)
#define SIMCOP_HL_IRQSTATUS_VLCDJ_DECODE_ERR_IRQ_MASK                                   (0x00008000U)

#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_SHIFT                                           (16U)
#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_MASK                                            (0x00010000U)
#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_NOACTION                                         (0U)
#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_CLEAR                                            (1U)
#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_NOEVENT                                          (0U)
#define SIMCOP_HL_IRQSTATUS_OCP_ERR_IRQ_PENDING                                          (1U)

#define SIMCOP_HL_IRQSTATUS_DMA_IRQ1_SHIFT                                              (18U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ1_MASK                                               (0x00040000U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ1_NOEVENT                                             (0U)
#define SIMCOP_HL_IRQSTATUS_DMA_IRQ1_PENDING                                             (1U)

#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_SHIFT                                    (19U)
#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_MASK                                     (0x00080000U)
#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_NOACTION                                  (0U)
#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_CLEAR                                     (1U)
#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_NOEVENT                                   (0U)
#define SIMCOP_HL_IRQSTATUS_CPU_PROC_START_IRQ_PENDING                                   (1U)

#define SIMCOP_HL_IRQSTATUS_RESERVED_SHIFT                                              (20U)
#define SIMCOP_HL_IRQSTATUS_RESERVED_MASK                                               (0xfff00000U)

#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_SHIFT                                              (8U)
#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_MASK                                               (0x00000100U)
#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_NOACTION                                            (0U)
#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_CLEAR                                               (1U)
#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_NOEVENT                                             (0U)
#define SIMCOP_HL_IRQSTATUS_VTNF_IRQ_PENDING                                             (1U)

#define SIMCOP_HL_IRQSTATUS_RESERVED1_SHIFT                                             (17U)
#define SIMCOP_HL_IRQSTATUS_RESERVED1_MASK                                              (0x00020000U)

#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_SHIFT                                          (0U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_MASK                                           (0x00000001U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_ENABLE                                          (1U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ0_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_SHIFT                                     (1U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_MASK                                      (0x00000002U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_ENABLE                                     (1U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_DISABLED                                   (0U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_FRAME_IRQ_ENABLED                                    (1U)

#define SIMCOP_HL_IRQENABLE_SET_DCT_IRQ_SHIFT                                           (2U)
#define SIMCOP_HL_IRQENABLE_SET_DCT_IRQ_MASK                                            (0x00000004U)

#define SIMCOP_HL_IRQENABLE_SET_VLCDJ_BLOC_IRQ_SHIFT                                    (3U)
#define SIMCOP_HL_IRQENABLE_SET_VLCDJ_BLOC_IRQ_MASK                                     (0x00000008U)

#define SIMCOP_HL_IRQENABLE_SET_NSF_IRQ_SHIFT                                           (4U)
#define SIMCOP_HL_IRQENABLE_SET_NSF_IRQ_MASK                                            (0x00000010U)

#define SIMCOP_HL_IRQENABLE_SET_IMX_A_IRQ_SHIFT                                         (5U)
#define SIMCOP_HL_IRQENABLE_SET_IMX_A_IRQ_MASK                                          (0x00000020U)

#define SIMCOP_HL_IRQENABLE_SET_IMX_B_IRQ_SHIFT                                         (6U)
#define SIMCOP_HL_IRQENABLE_SET_IMX_B_IRQ_MASK                                          (0x00000040U)

#define SIMCOP_HL_IRQENABLE_SET_ROT_A_SHIFT                                             (7U)
#define SIMCOP_HL_IRQENABLE_SET_ROT_A_MASK                                              (0x00000080U)

#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_SHIFT                                     (9U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_MASK                                      (0x00000200U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_ENABLE                                     (1U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_DISABLED                                   (0U)
#define SIMCOP_HL_IRQENABLE_SET_LDC_BLOCK_IRQ_ENABLED                                    (1U)

#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_SHIFT                                         (10U)
#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_MASK                                          (0x00000400U)
#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_ENABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP0_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_SHIFT                                         (11U)
#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_MASK                                          (0x00000800U)
#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_ENABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP1_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_SHIFT                                         (12U)
#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_MASK                                          (0x00001000U)
#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_ENABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP2_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_SHIFT                                         (13U)
#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_MASK                                          (0x00002000U)
#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_ENABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_SET_STEP3_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_SHIFT                                          (14U)
#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_MASK                                           (0x00004000U)
#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_ENABLE                                          (1U)
#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DONE_IRQ_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_SET_VLCDJ_DECODE_ERR_IRQ_SHIFT                              (15U)
#define SIMCOP_HL_IRQENABLE_SET_VLCDJ_DECODE_ERR_IRQ_MASK                               (0x00008000U)

#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_SHIFT                                       (16U)
#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_MASK                                        (0x00010000U)
#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_NOACTION                                     (0U)
#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_ENABLE                                       (1U)
#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_DISABLED                                     (0U)
#define SIMCOP_HL_IRQENABLE_SET_OCP_ERR_IRQ_ENABLED                                      (1U)

#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_SHIFT                                          (18U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_MASK                                           (0x00040000U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_ENABLE                                          (1U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_DMA_IRQ1_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_SHIFT                                (19U)
#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_MASK                                 (0x00080000U)
#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_NOACTION                              (0U)
#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_ENABLE                                (1U)
#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_DISABLED                              (0U)
#define SIMCOP_HL_IRQENABLE_SET_CPU_PROC_START_IRQ_ENABLED                               (1U)

#define SIMCOP_HL_IRQENABLE_SET_RESERVED_SHIFT                                          (20U)
#define SIMCOP_HL_IRQENABLE_SET_RESERVED_MASK                                           (0xfff00000U)

#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_SHIFT                                          (8U)
#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_MASK                                           (0x00000100U)
#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_ENABLE                                          (1U)
#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_SET_VTNF_IRQ_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_SET_RESERVED1_SHIFT                                         (17U)
#define SIMCOP_HL_IRQENABLE_SET_RESERVED1_MASK                                          (0x00020000U)

#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_SHIFT                                          (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_MASK                                           (0x00000001U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_DISABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ0_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_SHIFT                                     (1U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_MASK                                      (0x00000002U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_DISABLE                                    (1U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_DISABLED                                   (0U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_FRAME_IRQ_ENABLED                                    (1U)

#define SIMCOP_HL_IRQENABLE_CLR_DCT_IRQ_SHIFT                                           (2U)
#define SIMCOP_HL_IRQENABLE_CLR_DCT_IRQ_MASK                                            (0x00000004U)

#define SIMCOP_HL_IRQENABLE_CLR_VLCDJ_BLOC_IRQ_SHIFT                                    (3U)
#define SIMCOP_HL_IRQENABLE_CLR_VLCDJ_BLOC_IRQ_MASK                                     (0x00000008U)

#define SIMCOP_HL_IRQENABLE_CLR_NSF_IRQ_SHIFT                                           (4U)
#define SIMCOP_HL_IRQENABLE_CLR_NSF_IRQ_MASK                                            (0x00000010U)

#define SIMCOP_HL_IRQENABLE_CLR_IMX_A_IRQ_SHIFT                                         (5U)
#define SIMCOP_HL_IRQENABLE_CLR_IMX_A_IRQ_MASK                                          (0x00000020U)

#define SIMCOP_HL_IRQENABLE_CLR_IMX_B_IRQ_SHIFT                                         (6U)
#define SIMCOP_HL_IRQENABLE_CLR_IMX_B_IRQ_MASK                                          (0x00000040U)

#define SIMCOP_HL_IRQENABLE_CLR_ROT_A_SHIFT                                             (7U)
#define SIMCOP_HL_IRQENABLE_CLR_ROT_A_MASK                                              (0x00000080U)

#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_SHIFT                                     (9U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_MASK                                      (0x00000200U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_NOACTION                                   (0U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_DISABLE                                    (1U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_DISABLED                                   (0U)
#define SIMCOP_HL_IRQENABLE_CLR_LDC_BLOCK_IRQ_ENABLED                                    (1U)

#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_SHIFT                                         (10U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_MASK                                          (0x00000400U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_DISABLE                                        (1U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP0_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_SHIFT                                         (11U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_MASK                                          (0x00000800U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_DISABLE                                        (1U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP1_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_SHIFT                                         (12U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_MASK                                          (0x00001000U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_DISABLE                                        (1U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP2_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_SHIFT                                         (13U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_MASK                                          (0x00002000U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_NOACTION                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_DISABLE                                        (1U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_DISABLED                                       (0U)
#define SIMCOP_HL_IRQENABLE_CLR_STEP3_IRQ_ENABLED                                        (1U)

#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_SHIFT                                          (14U)
#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_MASK                                           (0x00004000U)
#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_DISABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DONE_IRQ_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_CLR_VLCDJ_DECODE_ERR_IRQ_SHIFT                              (15U)
#define SIMCOP_HL_IRQENABLE_CLR_VLCDJ_DECODE_ERR_IRQ_MASK                               (0x00008000U)

#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_SHIFT                                       (16U)
#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_MASK                                        (0x00010000U)
#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_NOACTION                                     (0U)
#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_DISABLE                                      (1U)
#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_DISABLED                                     (0U)
#define SIMCOP_HL_IRQENABLE_CLR_OCP_ERR_IRQ_ENABLED                                      (1U)

#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_SHIFT                                          (18U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_MASK                                           (0x00040000U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_DISABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_DMA_IRQ1_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_SHIFT                                (19U)
#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_MASK                                 (0x00080000U)
#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_NOACTION                              (0U)
#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_DISABLE                               (1U)
#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_DISABLED                              (0U)
#define SIMCOP_HL_IRQENABLE_CLR_CPU_PROC_START_IRQ_ENABLED                               (1U)

#define SIMCOP_HL_IRQENABLE_CLR_RESERVED_SHIFT                                          (20U)
#define SIMCOP_HL_IRQENABLE_CLR_RESERVED_MASK                                           (0xfff00000U)

#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_SHIFT                                          (8U)
#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_MASK                                           (0x00000100U)
#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_NOACTION                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_DISABLE                                         (1U)
#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_DISABLED                                        (0U)
#define SIMCOP_HL_IRQENABLE_CLR_VTNF_IRQ_ENABLED                                         (1U)

#define SIMCOP_HL_IRQENABLE_CLR_RESERVED1_SHIFT                                         (17U)
#define SIMCOP_HL_IRQENABLE_CLR_RESERVED1_MASK                                          (0x00020000U)

#define SIMCOP_CTRL_NSF_WMEM_SHIFT                                                      (4U)
#define SIMCOP_CTRL_NSF_WMEM_MASK                                                       (0x00000030U)
#define SIMCOP_CTRL_NSF_WMEM_NONE                                                        (0U)
#define SIMCOP_CTRL_NSF_WMEM_COEFF_A                                                     (1U)
#define SIMCOP_CTRL_NSF_WMEM_IMBUFF_2                                                    (2U)
#define SIMCOP_CTRL_NSF_WMEM_IMBUFF_4                                                    (3U)

#define SIMCOP_CTRL_LDC_INPUT_SHIFT                                                     (6U)
#define SIMCOP_CTRL_LDC_INPUT_MASK                                                      (0x000000c0U)
#define SIMCOP_CTRL_LDC_INPUT_NONE                                                       (0U)
#define SIMCOP_CTRL_LDC_INPUT_IMBUF2                                                     (1U)
#define SIMCOP_CTRL_LDC_INPUT_IMBUF4                                                     (2U)
#define SIMCOP_CTRL_LDC_INPUT_PRIVATE                                                    (3U)

#define SIMCOP_CTRL_IMX_B_CMD_SHIFT                                                     (14U)
#define SIMCOP_CTRL_IMX_B_CMD_MASK                                                      (0x00004000U)
#define SIMCOP_CTRL_IMX_B_CMD_COPR                                                       (0U)
#define SIMCOP_CTRL_IMX_B_CMD_IMXB                                                       (1U)

#define SIMCOP_CTRL_IMX_A_CMD_SHIFT                                                     (12U)
#define SIMCOP_CTRL_IMX_A_CMD_MASK                                                      (0x00003000U)
#define SIMCOP_CTRL_IMX_A_CMD_IMXA                                                       (1U)
#define SIMCOP_CTRL_IMX_A_CMD_COPR                                                       (0U)
#define SIMCOP_CTRL_IMX_A_CMD_IMXB                                                       (2U)

#define SIMCOP_CTRL_QUANT_SHIFT                                                         (10U)
#define SIMCOP_CTRL_QUANT_MASK                                                          (0x00000400U)
#define SIMCOP_CTRL_QUANT_COPR                                                           (0U)
#define SIMCOP_CTRL_QUANT_VLCDJ                                                          (1U)

#define SIMCOP_CTRL_HUFF_SHIFT                                                          (11U)
#define SIMCOP_CTRL_HUFF_MASK                                                           (0x00000800U)
#define SIMCOP_CTRL_HUFF_COPR                                                            (0U)
#define SIMCOP_CTRL_HUFF_VLCDJ                                                           (1U)

#define SIMCOP_CTRL_RESERVED5_SHIFT                                                     (8U)
#define SIMCOP_CTRL_RESERVED5_MASK                                                      (0x00000100U)

#define SIMCOP_CTRL_IRQ0_MODE_SHIFT                                                     (0U)
#define SIMCOP_CTRL_IRQ0_MODE_MASK                                                      (0x00000001U)
#define SIMCOP_CTRL_IRQ0_MODE_OR                                                         (0U)
#define SIMCOP_CTRL_IRQ0_MODE_AND                                                        (1U)

#define SIMCOP_CTRL_IRQ1_MODE_SHIFT                                                     (1U)
#define SIMCOP_CTRL_IRQ1_MODE_MASK                                                      (0x00000002U)
#define SIMCOP_CTRL_IRQ1_MODE_OR                                                         (0U)
#define SIMCOP_CTRL_IRQ1_MODE_AND                                                        (1U)

#define SIMCOP_CTRL_IRQ2_MODE_SHIFT                                                     (2U)
#define SIMCOP_CTRL_IRQ2_MODE_MASK                                                      (0x00000004U)
#define SIMCOP_CTRL_IRQ2_MODE_OR                                                         (0U)
#define SIMCOP_CTRL_IRQ2_MODE_AND                                                        (1U)

#define SIMCOP_CTRL_IRQ3_MODE_SHIFT                                                     (3U)
#define SIMCOP_CTRL_IRQ3_MODE_MASK                                                      (0x00000008U)
#define SIMCOP_CTRL_IRQ3_MODE_OR                                                         (0U)
#define SIMCOP_CTRL_IRQ3_MODE_AND                                                        (1U)

#define SIMCOP_CTRL_LDC_R_TAG_OFST_SHIFT                                                (16U)
#define SIMCOP_CTRL_LDC_R_TAG_OFST_MASK                                                 (0x000f0000U)

#define SIMCOP_CTRL_LDC_R_TAG_CNT_SHIFT                                                 (21U)
#define SIMCOP_CTRL_LDC_R_TAG_CNT_MASK                                                  (0x01e00000U)

#define SIMCOP_CTRL_RESERVED_SHIFT                                                      (9U)
#define SIMCOP_CTRL_RESERVED_MASK                                                       (0x00000200U)

#define SIMCOP_CTRL_RESERVED1_SHIFT                                                     (15U)
#define SIMCOP_CTRL_RESERVED1_MASK                                                      (0x00008000U)

#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_SHIFT                                        (26U)
#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_MASK                                         (0x0c000000U)
#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_B128                                          (0U)
#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_B96                                           (1U)
#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_B64                                           (2U)
#define SIMCOP_CTRL_LDC_R_MAX_BURST_LENGTH_B32                                           (3U)

#define SIMCOP_CTRL_LDC_R_BURST_BREAK_SHIFT                                             (28U)
#define SIMCOP_CTRL_LDC_R_BURST_BREAK_MASK                                              (0x10000000U)
#define SIMCOP_CTRL_LDC_R_BURST_BREAK_YES                                                (0U)
#define SIMCOP_CTRL_LDC_R_BURST_BREAK_NO                                                 (1U)

#define SIMCOP_CTRL_RESERVED3_SHIFT                                                     (20U)
#define SIMCOP_CTRL_RESERVED3_MASK                                                      (0x00100000U)

#define SIMCOP_CTRL_RESERVED4_SHIFT                                                     (25U)
#define SIMCOP_CTRL_RESERVED4_MASK                                                      (0x02000000U)

#define SIMCOP_CTRL_RESERVED2_SHIFT                                                     (29U)
#define SIMCOP_CTRL_RESERVED2_MASK                                                      (0xe0000000U)

#define SIMCOP_CLKCTRL_DMA_SHIFT                                                        (0U)
#define SIMCOP_CLKCTRL_DMA_MASK                                                         (0x00000001U)
#define SIMCOP_CLKCTRL_DMA_WOFF                                                          (0U)
#define SIMCOP_CLKCTRL_DMA_WON                                                           (1U)
#define SIMCOP_CLKCTRL_DMA_ROFF                                                          (0U)
#define SIMCOP_CLKCTRL_DMA_RON                                                           (1U)

#define SIMCOP_CLKCTRL_LDC_SHIFT                                                        (1U)
#define SIMCOP_CLKCTRL_LDC_MASK                                                         (0x00000002U)
#define SIMCOP_CLKCTRL_LDC_WOFF                                                          (0U)
#define SIMCOP_CLKCTRL_LDC_WON                                                           (1U)
#define SIMCOP_CLKCTRL_LDC_ROFF                                                          (0U)
#define SIMCOP_CLKCTRL_LDC_RON                                                           (1U)

#define SIMCOP_CLKCTRL_DCT_SHIFT                                                        (2U)
#define SIMCOP_CLKCTRL_DCT_MASK                                                         (0x00000004U)
#define SIMCOP_CLKCTRL_DCT_WOFF                                                          (0U)
#define SIMCOP_CLKCTRL_DCT_WON                                                           (1U)
#define SIMCOP_CLKCTRL_DCT_ROFF                                                          (0U)
#define SIMCOP_CLKCTRL_DCT_RON                                                           (1U)

#define SIMCOP_CLKCTRL_VLCDJ_SHIFT                                                      (3U)
#define SIMCOP_CLKCTRL_VLCDJ_MASK                                                       (0x00000008U)
#define SIMCOP_CLKCTRL_VLCDJ_WOFF                                                        (0U)
#define SIMCOP_CLKCTRL_VLCDJ_WON                                                         (1U)
#define SIMCOP_CLKCTRL_VLCDJ_ROFF                                                        (0U)
#define SIMCOP_CLKCTRL_VLCDJ_RON                                                         (1U)

#define SIMCOP_CLKCTRL_NSF2_SHIFT                                                       (4U)
#define SIMCOP_CLKCTRL_NSF2_MASK                                                        (0x00000010U)
#define SIMCOP_CLKCTRL_NSF2_WOFF                                                         (0U)
#define SIMCOP_CLKCTRL_NSF2_WON                                                          (1U)
#define SIMCOP_CLKCTRL_NSF2_ROFF                                                         (0U)
#define SIMCOP_CLKCTRL_NSF2_RON                                                          (1U)

#define SIMCOP_CLKCTRL_IMX_A_SHIFT                                                      (5U)
#define SIMCOP_CLKCTRL_IMX_A_MASK                                                       (0x00000020U)
#define SIMCOP_CLKCTRL_IMX_A_WOFF                                                        (0U)
#define SIMCOP_CLKCTRL_IMX_A_WON                                                         (1U)
#define SIMCOP_CLKCTRL_IMX_A_ROFF                                                        (0U)
#define SIMCOP_CLKCTRL_IMX_A_RON                                                         (1U)

#define SIMCOP_CLKCTRL_ROT_A_SHIFT                                                      (7U)
#define SIMCOP_CLKCTRL_ROT_A_MASK                                                       (0x00000080U)
#define SIMCOP_CLKCTRL_ROT_A_WOFF                                                        (0U)
#define SIMCOP_CLKCTRL_ROT_A_WON                                                         (1U)
#define SIMCOP_CLKCTRL_ROT_A_ROFF                                                        (0U)
#define SIMCOP_CLKCTRL_ROT_A_RON                                                         (1U)

#define SIMCOP_CLKCTRL_IMX_B_SHIFT                                                      (6U)
#define SIMCOP_CLKCTRL_IMX_B_MASK                                                       (0x00000040U)
#define SIMCOP_CLKCTRL_IMX_B_WOFF                                                        (0U)
#define SIMCOP_CLKCTRL_IMX_B_WON                                                         (1U)
#define SIMCOP_CLKCTRL_IMX_B_ROFF                                                        (0U)
#define SIMCOP_CLKCTRL_IMX_B_RON                                                         (1U)

#define SIMCOP_CLKCTRL_VTNF_SHIFT                                                       (9U)
#define SIMCOP_CLKCTRL_VTNF_MASK                                                        (0x00000200U)
#define SIMCOP_CLKCTRL_VTNF_WOFF                                                         (0U)
#define SIMCOP_CLKCTRL_VTNF_WON                                                          (1U)
#define SIMCOP_CLKCTRL_VTNF_ROFF                                                         (0U)
#define SIMCOP_CLKCTRL_VTNF_RON                                                          (1U)

#define SIMCOP_CLKCTRL_RESERVED_SHIFT                                                   (10U)
#define SIMCOP_CLKCTRL_RESERVED_MASK                                                    (0xfffffc00U)

#define SIMCOP_CLKCTRL_RESERVED1_SHIFT                                                  (8U)
#define SIMCOP_CLKCTRL_RESERVED1_MASK                                                   (0x00000100U)

#define SIMCOP_HWSEQ_CTRL_HW_SEQ_START_SHIFT                                            (0U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_START_MASK                                             (0x00000001U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_START                                                   (1U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_START_NOCHANGE                                          (0U)

#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STOP_SHIFT                                             (1U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STOP_MASK                                              (0x00000002U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STOP                                                    (1U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STOP_NOEFFECT                                           (0U)

#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STEP_COUNTER_SHIFT                                     (16U)
#define SIMCOP_HWSEQ_CTRL_HW_SEQ_STEP_COUNTER_MASK                                      (0xffff0000U)

#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_SHIFT                                        (2U)
#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_MASK                                         (0x0000000cU)
#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_B2046                                         (0U)
#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_B1024                                         (1U)
#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_B512                                          (2U)
#define SIMCOP_HWSEQ_CTRL_BITSTR_XFER_SIZE_B256                                          (3U)

#define SIMCOP_HWSEQ_CTRL_BITSTREAM_SHIFT                                               (4U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_MASK                                                (0x00000070U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_COPR                                                 (0U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_DMA                                                  (1U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_PINGPONG_ENCODE                                      (5U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_VLCDJ                                                (2U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_PINGPONG_DECODE                                      (6U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_VLCDJ_DMA                                            (4U)
#define SIMCOP_HWSEQ_CTRL_BITSTREAM_DMA_VLCDJ                                            (3U)

#define SIMCOP_HWSEQ_CTRL_BBM_STATUS_SHIFT                                              (7U)
#define SIMCOP_HWSEQ_CTRL_BBM_STATUS_MASK                                               (0x00000080U)
#define SIMCOP_HWSEQ_CTRL_BBM_STATUS_BUSY                                                (1U)
#define SIMCOP_HWSEQ_CTRL_BBM_STATUS_IDLE                                                (0U)

#define SIMCOP_HWSEQ_CTRL_BBM_SYNC_CHAN_SHIFT                                           (8U)
#define SIMCOP_HWSEQ_CTRL_BBM_SYNC_CHAN_MASK                                            (0x00000300U)

#define SIMCOP_HWSEQ_CTRL_CPU_PROC_DONE_SHIFT                                           (10U)
#define SIMCOP_HWSEQ_CTRL_CPU_PROC_DONE_MASK                                            (0x00000400U)
#define SIMCOP_HWSEQ_CTRL_CPU_PROC_DONE_ZERO                                             (0U)
#define SIMCOP_HWSEQ_CTRL_CPU_PROC_DONE_ONE                                              (1U)

#define SIMCOP_HWSEQ_CTRL_STEP_SHIFT                                                    (11U)
#define SIMCOP_HWSEQ_CTRL_STEP_MASK                                                     (0x00001800U)

#define SIMCOP_HWSEQ_CTRL_BBM_LDC_SHIFT                                                 (15U)
#define SIMCOP_HWSEQ_CTRL_BBM_LDC_MASK                                                  (0x00008000U)
#define SIMCOP_HWSEQ_CTRL_BBM_LDC_VLCDJ                                                  (0U)
#define SIMCOP_HWSEQ_CTRL_BBM_LDC_LCD                                                    (1U)

#define SIMCOP_HWSEQ_CTRL_RESERVED_SHIFT                                                (13U)
#define SIMCOP_HWSEQ_CTRL_RESERVED_MASK                                                 (0x00006000U)

#define SIMCOP_HWSEQ_STATUS_STATE_SHIFT                                                 (0U)
#define SIMCOP_HWSEQ_STATUS_STATE_MASK                                                  (0x00000001U)
#define SIMCOP_HWSEQ_STATUS_STATE_IDLE                                                   (0U)
#define SIMCOP_HWSEQ_STATUS_STATE_RUNNING                                                (1U)

#define SIMCOP_HWSEQ_STATUS_HW_SEQ_STEP_COUNTER_SHIFT                                   (16U)
#define SIMCOP_HWSEQ_STATUS_HW_SEQ_STEP_COUNTER_MASK                                    (0xffff0000U)

#define SIMCOP_HWSEQ_STATUS_RESERVED_SHIFT                                              (1U)
#define SIMCOP_HWSEQ_STATUS_RESERVED_MASK                                               (0x0000fffeU)

#define SIMCOP_HWSEQ_OVERRIDE_IMX_A_D_OFST_OVR_SHIFT                                    (0U)
#define SIMCOP_HWSEQ_OVERRIDE_IMX_A_D_OFST_OVR_MASK                                     (0x00000001U)

#define SIMCOP_HWSEQ_OVERRIDE_IMX_B_D_OFST_OVR_SHIFT                                    (1U)
#define SIMCOP_HWSEQ_OVERRIDE_IMX_B_D_OFST_OVR_MASK                                     (0x00000002U)

#define SIMCOP_HWSEQ_OVERRIDE_VLCDJ_IO_OFST_OVR_SHIFT                                   (2U)
#define SIMCOP_HWSEQ_OVERRIDE_VLCDJ_IO_OFST_OVR_MASK                                    (0x00000004U)

#define SIMCOP_HWSEQ_OVERRIDE_DCT_S_OFST_OVR_SHIFT                                      (3U)
#define SIMCOP_HWSEQ_OVERRIDE_DCT_S_OFST_OVR_MASK                                       (0x00000008U)

#define SIMCOP_HWSEQ_OVERRIDE_DCT_F_OFST_OVR_SHIFT                                      (4U)
#define SIMCOP_HWSEQ_OVERRIDE_DCT_F_OFST_OVR_MASK                                       (0x00000010U)

#define SIMCOP_HWSEQ_OVERRIDE_NSF_IO_OFST_OVR_SHIFT                                     (5U)
#define SIMCOP_HWSEQ_OVERRIDE_NSF_IO_OFST_OVR_MASK                                      (0x00000020U)

#define SIMCOP_HWSEQ_OVERRIDE_ROT_I_OFST_OVR_SHIFT                                      (6U)
#define SIMCOP_HWSEQ_OVERRIDE_ROT_I_OFST_OVR_MASK                                       (0x00000040U)

#define SIMCOP_HWSEQ_OVERRIDE_ROT_O_OFST_OVR_SHIFT                                      (7U)
#define SIMCOP_HWSEQ_OVERRIDE_ROT_O_OFST_OVR_MASK                                       (0x00000080U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_A_SHIFT                                            (9U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_A_MASK                                             (0x00000200U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_B_SHIFT                                            (10U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_B_MASK                                             (0x00000400U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_C_SHIFT                                            (11U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_C_MASK                                             (0x00000800U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_D_SHIFT                                            (12U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_D_MASK                                             (0x00001000U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_E_SHIFT                                            (13U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_E_MASK                                             (0x00002000U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_F_SHIFT                                            (14U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_F_MASK                                             (0x00004000U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_G_SHIFT                                            (15U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_G_MASK                                             (0x00008000U)

#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_H_SHIFT                                            (16U)
#define SIMCOP_HWSEQ_OVERRIDE_IMBUFF_H_MASK                                             (0x00010000U)

#define SIMCOP_HWSEQ_OVERRIDE_COEFF_A_SHIFT                                             (17U)
#define SIMCOP_HWSEQ_OVERRIDE_COEFF_A_MASK                                              (0x00020000U)

#define SIMCOP_HWSEQ_OVERRIDE_COEFF_B_SHIFT                                             (18U)
#define SIMCOP_HWSEQ_OVERRIDE_COEFF_B_MASK                                              (0x00040000U)

#define SIMCOP_HWSEQ_OVERRIDE_LDC_O_OFST_OVR_SHIFT                                      (8U)
#define SIMCOP_HWSEQ_OVERRIDE_LDC_O_OFST_OVR_MASK                                       (0x00000100U)

#define SIMCOP_HWSEQ_OVERRIDE_VTNF_IO_OFST_OVR_SHIFT                                    (19U)
#define SIMCOP_HWSEQ_OVERRIDE_VTNF_IO_OFST_OVR_MASK                                     (0x00080000U)

#define SIMCOP_HWSEQ_OVERRIDE_RESERVED_SHIFT                                            (20U)
#define SIMCOP_HWSEQ_OVERRIDE_RESERVED_MASK                                             (0xfff00000U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_SHIFT                              (11U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_MASK                               (0x00001800U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_ZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_ONE                                 (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_TWO                                 (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_A_D_OFST_THREE                               (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_SHIFT                              (13U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_MASK                               (0x00006000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_ZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_ONE                                 (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_TWO                                 (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_IMX_B_D_OFST_THREE                               (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_SHIFT                             (15U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_MASK                              (0x00038000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_ZERO                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_ONE                                (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_TWO                                (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_THREE                              (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_FOUR                               (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_IO_OFST_FIVE                               (5U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_SHIFT                                (20U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_MASK                                 (0x00700000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_ZERO                                  (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_ONE                                   (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_TWO                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_THREE                                 (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_FOUR                                  (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_F_OFST_FIVE                                  (5U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_SHIFT                                (18U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_MASK                                 (0x000c0000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_ZERO                                  (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_ONE                                   (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_TWO                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_S_OFST_THREE                                 (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_SHIFT                                (24U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_MASK                                 (0x03000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_ZERO                                  (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_ONE                                   (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_TWO                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_I_OFST_THREE                                 (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_SHIFT                                (26U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_MASK                                 (0x0c000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_ZERO                                  (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_ONE                                   (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_TWO                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_O_OFST_THREE                                 (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_SHIFT                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_MASK                                (0x00000001U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_WONE                                 (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_WZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_RZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_LDC_TRIGGER_RONE                                 (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_SHIFT                               (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_MASK                                (0x00000002U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_WONE                                 (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_WZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_RZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DCT_TRIGGER_RONE                                 (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_SHIFT                             (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_MASK                              (0x00000004U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_WONE                               (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_WZERO                              (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_RZERO                              (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VLCDJ_TRIGGER_RONE                               (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_SHIFT                               (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_MASK                                (0x00000008U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_WONE                                 (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_WZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_RZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_NSF_TRIGGER_RONE                                 (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_SHIFT                             (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_MASK                              (0x00000010U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_WONE                               (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_WZERO                              (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_RZERO                              (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_ROT_A_TRIGGER_RONE                               (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_SHIFT                               (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_MASK                                (0x000000e0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_NE                                   (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN0                                (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN1                                (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN2                                (6U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN3                                (7U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN0_1                              (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN0_2                              (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_CHAN0_3                              (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RZERO                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN0                               (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN1                               (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN2                               (6U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN3                               (7U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN0_1                             (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN0_2                             (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_DMA_TRIGGER_RCHAN0_3                             (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED1_SHIFT                                 (23U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED1_MASK                                  (0x00800000U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED2_SHIFT                                 (28U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED2_MASK                                  (0xf0000000U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_SHIFT                              (8U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_MASK                               (0x00000100U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_WONE                                (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_WZERO                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_RZERO                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_VTNF_TRIGGER_RONE                                (1U)

#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED_SHIFT                                  (9U)
#define SIMCOP_HWSEQ_STEP_CTRL_OVERRIDE_RESERVED_MASK                                   (0x00000600U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_SHIFT                                (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_MASK                                 (0x00000007U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_IMX_B                                 (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_IMX                                   (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_VLCDJ_IO                              (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_DCT_F                                 (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_ROT_I                                 (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_A_RSV                                   (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_SHIFT                                (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_MASK                                 (0x00000070U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_IMX                                   (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_IMX_A                                 (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_VLCDJ_IO                              (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_DCT_F                                 (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_ROT_A_I                               (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_B_RSV                                   (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_SHIFT                                (8U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_MASK                                 (0x00000700U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_IMX_B                                 (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_IMX_A                                 (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_VLCDJ_IO                              (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_DCT_F                                 (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_ROT_A_I                               (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_C_RSV                                   (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_SHIFT                                (12U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_MASK                                 (0x00007000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_IMX_B                                 (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_IMX_A                                 (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_VLCDJ_IO                              (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_DCT_F                                 (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_ROT_A_I                               (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_D_RSV                                   (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_SHIFT                                (16U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_MASK                                 (0x000f0000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_LDC_O                                 (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_E_VTNF_IO                               (8U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_SHIFT                                (20U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_MASK                                 (0x00f00000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_LDC_O                                 (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_F_VTNF_IO                               (8U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_SHIFT                                (24U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_MASK                                 (0x0f000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_LDC_O                                 (9U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_G_VTNF_IO                               (10U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_SHIFT                                (28U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_MASK                                 (0xf0000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_COPR                                  (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_DMA                                   (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_LDC_O                                 (9U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_IMBUFF_H_VTNF_IO                               (10U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED_SHIFT                                (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED_MASK                                 (0x00000008U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED1_SHIFT                               (7U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED1_MASK                                (0x00000080U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED2_SHIFT                               (11U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED2_MASK                                (0x00000800U)

#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED3_SHIFT                               (15U)
#define SIMCOP_HWSEQ_STEP_SWITCH_OVERRIDE_RESERVED3_MASK                                (0x00008000U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_SHIFT                                  (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_MASK                                   (0x00000007U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_DCT_F                                   (5U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_VLCDJ_IO                                (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_IMX_B                                   (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_IMX                                     (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_DMA                                     (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_COPR                                    (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_ROT_I                                   (6U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_A_RSV                                     (7U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_SHIFT                                  (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_MASK                                   (0x00000070U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_DCT_F                                   (5U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_VLCDJ_IO                                (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_IMX                                     (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_IMX_A                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_DMA                                     (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_COPR                                    (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_ROT_A_O                                 (6U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_COEFF_B_RSV                                     (7U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_SHIFT                             (10U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_MASK                              (0x00000c00U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_ZERO                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_ONE                                (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_E2                                 (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_NSF2_IO_OFST_E3                                 (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED_SHIFT                                 (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED_MASK                                  (0x00000008U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_SHIFT                               (8U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_MASK                                (0x00000300U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_E0                                   (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_E1                                   (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_E2                                   (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_LDC_O_OFST_E3                                   (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED1_SHIFT                                (7U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED1_MASK                                 (0x00000080U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_SHIFT                             (12U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_MASK                              (0x00003000U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_ZERO                               (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_ONE                                (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_E2                                 (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_VTNF_IO_OFST_E3                                 (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED2_SHIFT                                (14U)
#define SIMCOP_HWSEQ_STEP_CTRL2_OVERRIDE_RESERVED2_MASK                                 (0xffffc000U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_SHIFT                                         (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_MASK                                          (0x00000007U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_COPR                                           (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_IMX_B                                          (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_DMA                                            (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_IMX                                            (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_VLCDJ_IO                                       (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_DCT_F                                          (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_ROT_I                                          (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_A_RSV                                            (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_SHIFT                                         (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_MASK                                          (0x00000070U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_COPR                                           (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_IMX                                            (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_DMA                                            (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_IMX_A                                          (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_VLCDJ_IO                                       (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_DCT_F                                          (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_ROT_A_I                                        (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_B_RSV                                            (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_SHIFT                                         (12U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_MASK                                          (0x00007000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_COPR                                           (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_IMX_B                                          (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_DMA                                            (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_IMX_A                                          (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_VLCDJ_IO                                       (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_DCT_F                                          (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_ROT_A_I                                        (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_D_RSV                                            (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_SHIFT                                         (8U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_MASK                                          (0x00000700U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_COPR                                           (0U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_IMX_B                                          (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_DMA                                            (1U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_IMX_A                                          (2U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_VLCDJ_IO                                       (4U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_DCT_F                                          (5U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_ROT_A_I                                        (6U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_C_RSV                                            (7U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_SHIFT                                         (16U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_MASK                                          (0x000f0000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_COPR                                          (0x00000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_IMX_A                                         (0x00020000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_DMA                                           (0x00010000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_IMX_B                                         (0x00030000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_DCT_S                                         (0x00040000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_NSF_IO                                        (0x00050000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_LDC_O                                         (0x00060000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_ROT_A_O                                       (0x00070000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_E_VTNF_IO                                       (0x00080000U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_SHIFT                                         (20U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_MASK                                          (0x00f00000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_COPR                                          (0x00000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_IMX_A                                         (0x00200000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_DMA                                           (0x00100000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_IMX_B                                         (0x00300000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_DCT_S                                         (0x00400000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_NSF_IO                                        (0x00500000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_LDC_O                                         (0x00600000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_ROT_A_O                                       (0x00700000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_F_VTNF_IO                                       (0x00800000U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_SHIFT                                         (24U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_MASK                                          (0x0f000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_COPR                                          (0x00000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_IMX_A                                         (0x02000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_DMA                                           (0x01000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_IMX_B                                         (0x03000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_DCT_S                                         (0x05000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_VLCDJ_IO                                      (0x04000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_DCT_F                                         (0x06000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_ROT_A_O                                       (0x07000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_NSF_IO                                        (0x08000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_LDC_O                                         (0x09000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_G_VTNF_IO                                       (0x0a000000U)

#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_SHIFT                                         (28U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_MASK                                          (0xf0000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_COPR                                          (0x00000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_IMX_A                                         (0x20000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_DMA                                           (0x10000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_IMX_B                                         (0x30000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_DCT_S                                         (0x50000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_VLCDJ_IO                                      (0x40000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_DCT_F                                         (0x60000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_ROT_A_O                                       (0x70000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_NSF_IO                                        (0x80000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_LDC_O                                         (0x90000000U)
#define SIMCOP_HWSEQ_STEP_SWITCH_IMBUFF_H_VTNF_IO                                       (0xa0000000U)

#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED_SHIFT                                         (3U)
#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED_MASK                                          (0x00000008U)

#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED1_SHIFT                                        (7U)
#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED1_MASK                                         (0x00000080U)

#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED2_SHIFT                                        (11U)
#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED2_MASK                                         (0x00000800U)

#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED3_SHIFT                                        (15U)
#define SIMCOP_HWSEQ_STEP_SWITCH_RESERVED3_MASK                                         (0x00008000U)

#define SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_SHIFT                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_MASK                                            (0x00000001U)
#define SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_ENABLED                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_LDC_SYNC_DISABLED                                         (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_DCT_SYNC_SHIFT                                           (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_SYNC_MASK                                            (0x00000002U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_SYNC_ENABLED                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_SYNC_DISABLED                                         (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_SYNC_SHIFT                                         (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_SYNC_MASK                                          (0x00000004U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_SYNC_ENABLED                                        (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_SYNC_DISABLED                                       (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_NSF_SYNC_SHIFT                                           (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_NSF_SYNC_MASK                                            (0x00000008U)
#define SIMCOP_HWSEQ_STEP_CTRL_NSF_SYNC_ENABLED                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_NSF_SYNC_DISABLED                                         (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_ROT_A_SYNC_SHIFT                                         (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_A_SYNC_MASK                                          (0x00000010U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_A_SYNC_ENABLED                                        (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_A_SYNC_DISABLED                                       (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_SHIFT                                               (9U)
#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_MASK                                                (0x00000600U)
#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_STEP0                                                (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_STEP1                                                (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_STEP2                                                (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_NEXT_STEP3                                                (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_SHIFT                                           (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_MASK                                            (0x000000e0U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_DISABLED                                         (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN0                                            (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN1                                            (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN2                                            (6U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN3                                            (7U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN0_1                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN0_2                                          (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_SYNC_CHAN0_3                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_SHIFT                                       (11U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_MASK                                        (0x00001800U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_ZERO                                         (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_ONE                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_TWO                                          (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_A_D_OFST_THREE                                        (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_SHIFT                                       (13U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_MASK                                        (0x00006000U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_ZERO                                         (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_ONE                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_TWO                                          (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_IMX_B_D_OFST_THREE                                        (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_SHIFT                                      (15U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_MASK                                       (0x00038000U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_ZERO                                        (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_ONE                                         (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_TWO                                         (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_THREE                                       (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_FOUR                                        (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_VLCDJ_IO_OFST_FIVE                                        (5U)

#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_SHIFT                                         (20U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_MASK                                          (0x00700000U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_ZERO                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_ONE                                            (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_TWO                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_THREE                                          (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_FOUR                                           (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_F_OFST_FIVE                                           (5U)

#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_SHIFT                                         (18U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_MASK                                          (0x000c0000U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_ZERO                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_ONE                                            (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_TWO                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_DCT_S_OFST_THREE                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_SHIFT                                         (24U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_MASK                                          (0x03000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_ZERO                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_ONE                                            (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_TWO                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_I_OFST_THREE                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_SHIFT                                         (26U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_MASK                                          (0x0c000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_ZERO                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_ONE                                            (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_TWO                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_ROT_O_OFST_THREE                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_SHIFT                                           (28U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_MASK                                            (0x70000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_ZERO                                             (0U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_ONE                                              (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_TWO                                              (2U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_THREE                                            (3U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_FOUR                                             (4U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_FIVE                                             (5U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_SIX                                              (6U)
#define SIMCOP_HWSEQ_STEP_CTRL_DMA_OFST_SEVEN                                            (7U)

#define SIMCOP_HWSEQ_STEP_CTRL_CPU_SYNC_SHIFT                                           (31U)
#define SIMCOP_HWSEQ_STEP_CTRL_CPU_SYNC_MASK                                            (0x80000000U)
#define SIMCOP_HWSEQ_STEP_CTRL_CPU_SYNC_ENABLED                                          (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_CPU_SYNC_DISABLED                                         (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_SHIFT                                          (8U)
#define SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_MASK                                           (0x00000100U)
#define SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_ENABLED                                         (1U)
#define SIMCOP_HWSEQ_STEP_CTRL_VTNF_SYNC_DISABLED                                        (0U)

#define SIMCOP_HWSEQ_STEP_CTRL_EXT_SYNC_SHIFT                                           (23U)
#define SIMCOP_HWSEQ_STEP_CTRL_EXT_SYNC_MASK                                            (0x00800000U)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_START_SHIFT                                        (0U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_START_MASK                                         (0x00001fffU)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_START_SHIFT                                        (16U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_START_MASK                                         (0x1fff0000U)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_SYNC_SHIFT                                         (15U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_SYNC_MASK                                          (0x00008000U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_SYNC_ENABLED                                        (1U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_A_SYNC_DISABLED                                       (0U)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_SYNC_SHIFT                                         (31U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_SYNC_MASK                                          (0x80000000U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_SYNC_ENABLED                                        (1U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_B_SYNC_DISABLED                                       (0U)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_RESERVED_SHIFT                                       (13U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_RESERVED_MASK                                        (0x00006000U)

#define SIMCOP_HWSEQ_STEP_IMX_CTRL_RESERVED1_SHIFT                                      (29U)
#define SIMCOP_HWSEQ_STEP_IMX_CTRL_RESERVED1_MASK                                       (0x60000000U)

#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_SHIFT                                           (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_MASK                                            (0x00000007U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_DCT_F                                            (5U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_VLCDJ_IO                                         (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_IMX_B                                            (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_IMX                                              (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_DMA                                              (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_COPR                                             (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_ROT_I                                            (6U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_A_RSV                                              (7U)

#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_SHIFT                                           (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_MASK                                            (0x00000070U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_DCT_F                                            (5U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_VLCDJ_IO                                         (4U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_IMX                                              (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_IMX_A                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_DMA                                              (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_COPR                                             (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_ROT_A_O                                          (6U)
#define SIMCOP_HWSEQ_STEP_CTRL2_COEFF_B_RSV                                              (7U)

#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_SHIFT                                        (8U)
#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_MASK                                         (0x00000300U)
#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_E0                                            (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_E1                                            (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_E2                                            (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_LDC_O_OFST_E3                                            (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_SHIFT                                      (10U)
#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_MASK                                       (0x00000c00U)
#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_ZERO                                        (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_ONE                                         (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_E2                                          (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_NSF2_IO_OFST_E3                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED_SHIFT                                          (3U)
#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED_MASK                                           (0x00000008U)

#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED1_SHIFT                                         (7U)
#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED1_MASK                                          (0x00000080U)

#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_SHIFT                                      (12U)
#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_MASK                                       (0x00003000U)
#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_ZERO                                        (0U)
#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_ONE                                         (1U)
#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_E2                                          (2U)
#define SIMCOP_HWSEQ_STEP_CTRL2_VTNF_IO_OFST_E3                                          (3U)

#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED2_SHIFT                                         (14U)
#define SIMCOP_HWSEQ_STEP_CTRL2_RESERVED2_MASK                                          (0xffffc000U)

#define SIMCOP_CTRL2_LDCR_BW_CTRL_SHIFT                                                 (0U)
#define SIMCOP_CTRL2_LDCR_BW_CTRL_MASK                                                  (0x00000fffU)

#define SIMCOP_CTRL2_RESERVED_SHIFT                                                     (12U)
#define SIMCOP_CTRL2_RESERVED_MASK                                                      (0xfffff000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_SIMCOP_REGS_H_ */

