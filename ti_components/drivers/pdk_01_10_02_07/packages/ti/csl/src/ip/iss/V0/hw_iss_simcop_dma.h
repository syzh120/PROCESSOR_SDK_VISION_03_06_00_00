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

#ifndef HW_ISS_SIMCOP_DMA_H_
#define HW_ISS_SIMCOP_DMA_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define ISS_SIMCOP_DMA_REVISION                                     (0x0U)
#define ISS_SIMCOP_DMA_HWINFO                                       (0x4U)
#define ISS_SIMCOP_DMA_SYSCONFIG                                    (0x10U)
#define ISS_SIMCOP_DMA_IRQ_EOI                                      (0x18U)
#define ISS_SIMCOP_DMA_CTRL                                         (0x1cU)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW(m)                             (0x20U + ((m) * 0x10U))
#define ISS_SIMCOP_DMA_IRQSTATUS(m)                                 (0x24U + ((m) * 0x10U))
#define ISS_SIMCOP_DMA_IRQENABLE_SET(m)                             (0x28U + ((m) * 0x10U))
#define ISS_SIMCOP_DMA_IRQENABLE_CLR(m)                             (0x2cU + ((m) * 0x10U))
#define ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE(m)                           (0x94U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_SMEM_ADDR(m)                            (0x84U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_SMEM_OFST(m)                            (0x88U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_CTRL(m)                                 (0x80U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_BUF_OFST(m)                             (0x8cU + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_BUF_ADDR(m)                             (0x90U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_FRAME(m)                                (0x98U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_CURRENT_BLOCK(m)                        (0xa0U + ((m) * 0x30U))
#define ISS_SIMCOP_DMA_CHAN_BLOCK_STEP(m)                           (0xa4U + ((m) * 0x30U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISS_SIMCOP_DMA_REVISION_Y_MINOR_SHIFT                                           (0U)
#define ISS_SIMCOP_DMA_REVISION_Y_MINOR_MASK                                            (0x0000003fU)

#define ISS_SIMCOP_DMA_REVISION_CUSTOM_SHIFT                                            (6U)
#define ISS_SIMCOP_DMA_REVISION_CUSTOM_MASK                                             (0x000000c0U)
#define ISS_SIMCOP_DMA_REVISION_CUSTOM_STANDARD                                          (0U)

#define ISS_SIMCOP_DMA_REVISION_X_MAJOR_SHIFT                                           (8U)
#define ISS_SIMCOP_DMA_REVISION_X_MAJOR_MASK                                            (0x00000700U)

#define ISS_SIMCOP_DMA_REVISION_R_RTL_SHIFT                                             (11U)
#define ISS_SIMCOP_DMA_REVISION_R_RTL_MASK                                              (0x0000f800U)

#define ISS_SIMCOP_DMA_REVISION_FUNC_SHIFT                                              (16U)
#define ISS_SIMCOP_DMA_REVISION_FUNC_MASK                                               (0x0fff0000U)

#define ISS_SIMCOP_DMA_REVISION_SCHEME_SHIFT                                            (30U)
#define ISS_SIMCOP_DMA_REVISION_SCHEME_MASK                                             (0xc0000000U)
#define ISS_SIMCOP_DMA_REVISION_SCHEME_H08                                               (1U)
#define ISS_SIMCOP_DMA_REVISION_SCHEME_LEGACY                                            (0U)

#define ISS_SIMCOP_DMA_HWINFO_CONTEXT_SHIFT                                             (0U)
#define ISS_SIMCOP_DMA_HWINFO_CONTEXT_MASK                                              (0x00000003U)
#define ISS_SIMCOP_DMA_HWINFO_CONTEXT_FOUR                                               (0U)
#define ISS_SIMCOP_DMA_HWINFO_CONTEXT_EIGHT                                              (1U)
#define ISS_SIMCOP_DMA_HWINFO_CONTEXT_SIXTEEN                                            (2U)

#define ISS_SIMCOP_DMA_HWINFO_CHAN_SHIFT                                                (2U)
#define ISS_SIMCOP_DMA_HWINFO_CHAN_MASK                                                 (0x00000004U)
#define ISS_SIMCOP_DMA_HWINFO_CHAN_EIGHT                                                 (1U)
#define ISS_SIMCOP_DMA_HWINFO_CHAN_FOUR                                                  (0U)

#define ISS_SIMCOP_DMA_SYSCONFIG_RESET_MASK                                             (1U)

#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_SHIFT                                      (4U)
#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_MASK                                       (0x00000030U)
#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_FORCE                                       (0U)
#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_NO                                          (1U)
#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_SMART1                                      (2U)
#define ISS_SIMCOP_DMA_SYSCONFIG_STANDBYMODE_SMART2                                      (3U)

#define ISS_SIMCOP_DMA_IRQ_EOI_LINE_NUMBER_SHIFT                                        (0U)
#define ISS_SIMCOP_DMA_IRQ_EOI_LINE_NUMBER_MASK                                         (0x00000003U)
#define ISS_SIMCOP_DMA_IRQ_EOI_LINE_NUMBER_READ0                                         (0U)
#define ISS_SIMCOP_DMA_IRQ_EOI_LINE_NUMBER_EOI0                                          (0U)
#define ISS_SIMCOP_DMA_IRQ_EOI_LINE_NUMBER_EOI1                                          (1U)

#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_SHIFT                                        (0U)
#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_MASK                                         (0x00000003U)
#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_ONE                                           (0U)
#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_TWO                                           (1U)
#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_FOUR                                          (2U)
#define ISS_SIMCOP_DMA_CTRL_MAX_BURST_SIZE_EIGHT                                         (3U)

#define ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_SHIFT                                         (3U)
#define ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_MASK                                          (0x00000008U)
#define ISS_SIMCOP_DMA_CTRL_POSTED_WRITES_NON                                            (0U)
#define ISS_SIMCOP_DMA_CTRL_POSTED_WRITES                                                (1U)

#define ISS_SIMCOP_DMA_CTRL_BW_LIMITER_SHIFT                                            (16U)
#define ISS_SIMCOP_DMA_CTRL_BW_LIMITER_MASK                                             (0xffff0000U)

#define ISS_SIMCOP_DMA_CTRL_TAG_CNT_SHIFT                                               (4U)
#define ISS_SIMCOP_DMA_CTRL_TAG_CNT_MASK                                                (0x000000f0U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_SHIFT                                      (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_MASK                                       (0x00000001U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_NOACTION                                    (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_SET                                         (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_NOEVENT                                     (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_OCP_ERR_PENDING                                     (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_SHIFT                         (16U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_MASK                          (0x00010000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_SHIFT                         (17U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_MASK                          (0x00020000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_SHIFT                         (18U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_MASK                          (0x00040000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_SHIFT                         (19U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_MASK                          (0x00080000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_SHIFT                         (20U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_MASK                          (0x00100000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_SHIFT                         (21U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_MASK                          (0x00200000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_SHIFT                         (22U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_MASK                          (0x00400000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_SHIFT                         (23U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_MASK                          (0x00800000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_BLOCK_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_SHIFT                         (24U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_MASK                          (0x01000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN0_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_SHIFT                         (25U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_MASK                          (0x02000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN1_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_SHIFT                         (26U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_MASK                          (0x04000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN2_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_SHIFT                         (27U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_MASK                          (0x08000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN3_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_SHIFT                         (28U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_MASK                          (0x10000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN4_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_SHIFT                         (29U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_MASK                          (0x20000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN5_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_SHIFT                         (30U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_MASK                          (0x40000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN6_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_SHIFT                         (31U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_MASK                          (0x80000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_SET                            (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_NOEVENT                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_RAW_CHAN7_FRAME_DONE_IRQ_PENDING                        (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_SHIFT                                          (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_MASK                                           (0x00000001U)
#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_NOACTION                                        (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_CLEAR                                           (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_NOEVENT                                         (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_OCP_ERR_PENDING                                         (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_SHIFT                             (16U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_MASK                              (0x00010000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_SHIFT                             (17U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_MASK                              (0x00020000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_SHIFT                             (18U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_MASK                              (0x00040000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_SHIFT                             (19U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_MASK                              (0x00080000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_SHIFT                             (20U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_MASK                              (0x00100000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_SHIFT                             (21U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_MASK                              (0x00200000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_SHIFT                             (22U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_MASK                              (0x00400000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_SHIFT                             (23U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_MASK                              (0x00800000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_BLOCK_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_SHIFT                             (24U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_MASK                              (0x01000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN0_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_SHIFT                             (25U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_MASK                              (0x02000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN1_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_SHIFT                             (26U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_MASK                              (0x04000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN2_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_SHIFT                             (27U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_MASK                              (0x08000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN3_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_SHIFT                             (28U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_MASK                              (0x10000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN4_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_SHIFT                             (29U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_MASK                              (0x20000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN5_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_SHIFT                             (30U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_MASK                              (0x40000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN6_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_SHIFT                             (31U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_MASK                              (0x80000000U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_NOACTION                           (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_CLEAR                              (1U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_NOEVENT                            (0U)
#define ISS_SIMCOP_DMA_IRQSTATUS_CHAN7_FRAME_DONE_IRQ_PENDING                            (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_SHIFT                                      (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_MASK                                       (0x00000001U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_NOACTION                                    (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_ENABLE                                      (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_DISABLED                                    (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_OCP_ERR_ENABLED                                     (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_SHIFT                         (16U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_MASK                          (0x00010000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_SHIFT                         (17U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_MASK                          (0x00020000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_SHIFT                         (18U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_MASK                          (0x00040000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_SHIFT                         (19U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_MASK                          (0x00080000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_SHIFT                         (20U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_MASK                          (0x00100000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_SHIFT                         (21U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_MASK                          (0x00200000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_SHIFT                         (22U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_MASK                          (0x00400000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_SHIFT                         (23U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_MASK                          (0x00800000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_SHIFT                         (24U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_MASK                          (0x01000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN0_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_SHIFT                         (25U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_MASK                          (0x02000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN1_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_SHIFT                         (26U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_MASK                          (0x04000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN2_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_SHIFT                         (27U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_MASK                          (0x08000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN3_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_SHIFT                         (28U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_MASK                          (0x10000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN4_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_SHIFT                         (29U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_MASK                          (0x20000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN5_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_SHIFT                         (30U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_MASK                          (0x40000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN6_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_SHIFT                         (31U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_MASK                          (0x80000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_ENABLE                         (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_SET_CHAN7_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_SHIFT                                      (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_MASK                                       (0x00000001U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_NOACTION                                    (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_DISABLE                                     (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_DISABLED                                    (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_OCP_ERR_ENABLED                                     (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_SHIFT                         (16U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_MASK                          (0x00010000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_SHIFT                         (17U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_MASK                          (0x00020000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_SHIFT                         (18U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_MASK                          (0x00040000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_SHIFT                         (19U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_MASK                          (0x00080000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_SHIFT                         (20U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_MASK                          (0x00100000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_SHIFT                         (21U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_MASK                          (0x00200000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_SHIFT                         (22U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_MASK                          (0x00400000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_SHIFT                         (23U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_MASK                          (0x00800000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_BLOCK_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_SHIFT                         (24U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_MASK                          (0x01000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN0_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_SHIFT                         (25U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_MASK                          (0x02000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN1_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_SHIFT                         (26U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_MASK                          (0x04000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN2_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_SHIFT                         (27U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_MASK                          (0x08000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN3_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_SHIFT                         (28U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_MASK                          (0x10000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN4_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_SHIFT                         (29U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_MASK                          (0x20000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN5_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_SHIFT                         (30U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_MASK                          (0x40000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN6_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_SHIFT                         (31U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_MASK                          (0x80000000U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_NOACTION                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_DISABLE                        (1U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_DISABLED                       (0U)
#define ISS_SIMCOP_DMA_IRQENABLE_CLR_CHAN7_FRAME_DONE_IRQ_ENABLED                        (1U)

#define ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_YNUM_SHIFT                                       (16U)
#define ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_YNUM_MASK                                        (0x1fff0000U)

#define ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_XNUM_SHIFT                                       (4U)
#define ISS_SIMCOP_DMA_CHAN_BLOCK_SIZE_XNUM_MASK                                        (0x00003ff0U)

#define ISS_SIMCOP_DMA_CHAN_SMEM_ADDR_SHIFT                                             (4U)
#define ISS_SIMCOP_DMA_CHAN_SMEM_ADDR_MASK                                              (0xfffffff0U)

#define ISS_SIMCOP_DMA_CHAN_SMEM_OFST_SHIFT                                             (4U)
#define ISS_SIMCOP_DMA_CHAN_SMEM_OFST_MASK                                              (0x000ffff0U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE_SHIFT                                           (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE_MASK                                            (0x00000001U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE                                                  (1U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_ENABLE_ZERO                                             (0U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_SHIFT                                           (12U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_MASK                                            (0x0001f000U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN0                                            (16U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_DISABLED                                         (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN1                                            (17U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN2                                            (18U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN3                                            (19U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN4                                            (20U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN5                                            (21U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN6                                            (22U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_LINKED_CHAN7                                            (23U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_SHIFT                                          (17U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_MASK                                           (0x000e0000U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_DISABLED                                        (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_HW0                                             (4U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_HW1                                             (5U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_HW2                                             (6U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTART_HW3                                             (7U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_DIR_SHIFT                                              (5U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DIR_MASK                                               (0x00000020U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DIR_SDR2BUF                                             (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DIR_BUF2SDR                                             (1U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_SWTRIGGER_SHIFT                                        (2U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_SWTRIGGER_MASK                                         (0x00000004U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_SWTRIGGER_ZERO                                          (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_SWTRIGGER_ONE                                           (1U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_DISABLE_SHIFT                                          (1U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DISABLE_MASK                                           (0x00000002U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DISABLE_ZERO                                            (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_DISABLE                                                 (1U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_SHIFT                                           (3U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_MASK                                            (0x00000018U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_IDLE                                             (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_ACTIVE                                           (1U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_PENDING                                          (2U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_STATUS_RUNNING                                          (3U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_SHIFT                                           (20U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_MASK                                            (0x00700000U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_DISABLED                                         (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_HW0                                              (4U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_HW1                                              (5U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_HW2                                              (6U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_HWSTOP_HW3                                              (7U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_TILERMODE_SHIFT                                        (6U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_TILERMODE_MASK                                         (0x00000040U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_TILERMODE_REGULAR                                       (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_TILERMODE_TILER                                         (1U)

#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_SHIFT                                             (7U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_MASK                                              (0x00000180U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_G0                                                 (0U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_G1                                                 (1U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_G2                                                 (2U)
#define ISS_SIMCOP_DMA_CHAN_CTRL_GRID_G3                                                 (3U)

#define ISS_SIMCOP_DMA_CHAN_BUF_OFST_SHIFT                                              (4U)
#define ISS_SIMCOP_DMA_CHAN_BUF_OFST_MASK                                               (0x00fffff0U)

#define ISS_SIMCOP_DMA_CHAN_BUF_ADDR_SHIFT                                              (4U)
#define ISS_SIMCOP_DMA_CHAN_BUF_ADDR_MASK                                               (0x00fffff0U)

#define ISS_SIMCOP_DMA_CHAN_FRAME_XCNT_SHIFT                                            (0U)
#define ISS_SIMCOP_DMA_CHAN_FRAME_XCNT_MASK                                             (0x000003ffU)

#define ISS_SIMCOP_DMA_CHAN_FRAME_YCNT_SHIFT                                            (16U)
#define ISS_SIMCOP_DMA_CHAN_FRAME_YCNT_MASK                                             (0x03ff0000U)

#define ISS_SIMCOP_DMA_CHAN_CURRENT_BLOCK_BY_SHIFT                                      (16U)
#define ISS_SIMCOP_DMA_CHAN_CURRENT_BLOCK_BY_MASK                                       (0x03ff0000U)

#define ISS_SIMCOP_DMA_CHAN_CURRENT_BLOCK_BX_SHIFT                                      (0U)
#define ISS_SIMCOP_DMA_CHAN_CURRENT_BLOCK_BX_MASK                                       (0x000003ffU)

#define ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_XSTEP_SHIFT                                      (4U)
#define ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_XSTEP_MASK                                       (0x00007ff0U)

#define ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_YSTEP_SHIFT                                      (16U)
#define ISS_SIMCOP_DMA_CHAN_BLOCK_STEP_YSTEP_MASK                                       (0x3fff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_SIMCOP_DMA_H_ */

