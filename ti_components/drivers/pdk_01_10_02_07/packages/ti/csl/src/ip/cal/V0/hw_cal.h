/*
 * hw_cal.h
 *
 * Register-level header file for CAL
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
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

#ifndef HW_CAL_H_
#define HW_CAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define CAL_HL_REVISION                                             (0x0U)
#define CAL_HL_HWINFO                                               (0x4U)
#define CAL_HL_SYSCONFIG                                            (0x10U)
#define CAL_HL_IRQ_EOI                                              (0x1cU)
#define CAL_HL_IRQSTATUS_RAW(m)                                     ((uint32_t)0x20 + ((m) * (uint32_t)0x10))
#define CAL_HL_IRQSTATUS(m)                                         ((uint32_t)0x24 + ((m) * (uint32_t)0x10))
#define CAL_HL_IRQENABLE_SET(m)                                     ((uint32_t)0x28 + ((m) * (uint32_t)0x10))
#define CAL_HL_IRQENABLE_CLR(m)                                     ((uint32_t)0x2c + ((m) * (uint32_t)0x10))
#define CAL_PIX_PROC(m)                                             ((uint32_t)0xC0 + ((m) * (uint32_t)0x4))
#define CAL_CTRL                                                    (0x100U)
#define CAL_CTRL1                                                   (0x104U)
#define CAL_LINE_NUMBER_EVT                                         (0x108U)
#define CAL_VPORT_CTRL1                                             (0x120U)
#define CAL_VPORT_CTRL2                                             (0x124U)
#define CAL_BYS_CTRL1                                               (0x130U)
#define CAL_BYS_CTRL2                                               (0x134U)
#define CAL_RD_DMA_CTRL                                             (0x140U)
#define CAL_RD_DMA_PIX_ADDR                                         (0x144U)
#define CAL_RD_DMA_PIX_OFST                                         (0x148U)
#define CAL_RD_DMA_XSIZE                                            (0x14cU)
#define CAL_RD_DMA_YSIZE                                            (0x150U)
#define CAL_RD_DMA_INIT_ADDR                                        (0x154U)
#define CAL_RD_DMA_INIT_OFST                                        (0x168U)
#define CAL_RD_DMA_CTRL2                                            (0x16cU)
#define CAL_WR_DMA_CTRL(m)                                          (0x200U + ((m) * 0x10U))
#define CAL_WR_DMA_ADRR(m)                                          (0x204U + ((m) * 0x10U))
#define CAL_WR_DMA_OFST(m)                                          (0x208U + ((m) * 0x10U))
#define CAL_WR_DMA_XSIZE(m)                                         (0x20CU + ((m) * 0x10U))
#define CAL_CSI2_PPI_CTRL(m)                                        (0x300U + ((m) * 0x80U))
#define CAL_CSI2_COMPLEXIO_CFG(m)                                   (0x304U + ((m) * 0x80U))
#define CAL_CSI2_COMPLEXIO_IRQSTATUS(m)                             (0x308U + ((m) * 0x80U))
#define CAL_CSI2_SHORT_PACKET(m)                                    (0x30cU + ((m) * 0x80U))
#define CAL_CSI2_COMPLEXIO_IRQENABLE(m)                             (0x310U + ((m) * 0x80U))
#define CAL_CSI2_TIMING(m)                                          (0x314U + ((m) * 0x80U))
#define CAL_CSI2_VC_IRQENABLE(m)                                    (0x318U + ((m) * 0x80U))
#define CAL_CSI2_VC_IRQSTATUS(m)                                    (0x328U + ((m) * 0x80U))
#define CAL_CSI2_CTX0(m)                                            (0x330U + ((m) * 0x80U))
#define CAL_CSI2_CTX1(m)                                            (0x334U + ((m) * 0x80U))
#define CAL_CSI2_CTX2(m)                                            (0x338U + ((m) * 0x80U))
#define CAL_CSI2_CTX3(m)                                            (0x33cU + ((m) * 0x80U))
#define CAL_CSI2_CTX4(m)                                            (0x340U + ((m) * 0x80U))
#define CAL_CSI2_CTX5(m)                                            (0x344U + ((m) * 0x80U))
#define CAL_CSI2_CTX6(m)                                            (0x348U + ((m) * 0x80U))
#define CAL_CSI2_CTX7(m)                                            (0x34cU + ((m) * 0x80U))
#define CAL_CSI2_STATUS0(m)                                         (0x350U + ((m) * 0x80U))
#define CAL_CSI2_STATUS1(m)                                         (0x354U + ((m) * 0x80U))
#define CAL_CSI2_STATUS2(m)                                         (0x358U + ((m) * 0x80U))
#define CAL_CSI2_STATUS3(m)                                         (0x35cU + ((m) * 0x80U))
#define CAL_CSI2_STATUS4(m)                                         (0x360U + ((m) * 0x80U))
#define CAL_CSI2_STATUS5(m)                                         (0x364U + ((m) * 0x80U))
#define CAL_CSI2_STATUS6(m)                                         (0x368U + ((m) * 0x80U))
#define CAL_CSI2_STATUS7(m)                                         (0x36cU + ((m) * 0x80U))

#define CAL_CSI2_PHY_REG0                                           (0x0U)
#define CAL_CSI2_PHY_REG1                                           (0x4U)
#define CAL_CSI2_PHY_REG2                                           (0x8U)
#define CAL_CSI2_PHY_REG3                                           (0xCU)
#define CAL_CSI2_PHY_REG10                                          (0x28U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CAL_HL_REVISION_Y_MINOR_SHIFT                                                   (0U)
#define CAL_HL_REVISION_Y_MINOR_MASK                                                    (0x0000003fU)

#define CAL_HL_REVISION_CUSTOM_SHIFT                                                    (6U)
#define CAL_HL_REVISION_CUSTOM_MASK                                                     (0x000000c0U)
#define CAL_HL_REVISION_CUSTOM_STANDARD                                                  (0U)

#define CAL_HL_REVISION_X_MAJOR_SHIFT                                                   (8U)
#define CAL_HL_REVISION_X_MAJOR_MASK                                                    (0x00000700U)

#define CAL_HL_REVISION_R_RTL_SHIFT                                                     (11U)
#define CAL_HL_REVISION_R_RTL_MASK                                                      (0x0000f800U)

#define CAL_HL_REVISION_FUNC_SHIFT                                                      (16U)
#define CAL_HL_REVISION_FUNC_MASK                                                       (0x0fff0000U)

#define CAL_HL_REVISION_SCHEME_SHIFT                                                    (30U)
#define CAL_HL_REVISION_SCHEME_MASK                                                     (0xc0000000U)
#define CAL_HL_REVISION_SCHEME_H08                                                       (1U)
#define CAL_HL_REVISION_SCHEME_LEGACY                                                    (0U)

#define CAL_HL_REVISION_RESERVED_SHIFT                                                  (28U)
#define CAL_HL_REVISION_RESERVED_MASK                                                   (0x30000000U)

#define CAL_HL_HWINFO_WFIFO_SHIFT                                                       (0U)
#define CAL_HL_HWINFO_WFIFO_MASK                                                        (0x0000000fU)

#define CAL_HL_HWINFO_RFIFO_SHIFT                                                       (4U)
#define CAL_HL_HWINFO_RFIFO_MASK                                                        (0x000000f0U)

#define CAL_HL_HWINFO_PCTX_SHIFT                                                        (8U)
#define CAL_HL_HWINFO_PCTX_MASK                                                         (0x00001f00U)

#define CAL_HL_HWINFO_WCTX_SHIFT                                                        (13U)
#define CAL_HL_HWINFO_WCTX_MASK                                                         (0x0007e000U)

#define CAL_HL_HWINFO_VFIFO_SHIFT                                                       (19U)
#define CAL_HL_HWINFO_VFIFO_MASK                                                        (0x00780000U)

#define CAL_HL_HWINFO_NCPORT_SHIFT                                                      (23U)
#define CAL_HL_HWINFO_NCPORT_MASK                                                       (0x0f800000U)

#define CAL_HL_HWINFO_NPPI_CONTEXTS0_SHIFT                                              (28U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS0_MASK                                               (0x30000000U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS0_ZERO                                                (0U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS0_FOUR                                                (1U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS0_EIGHT                                               (2U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS0_RESERVED                                            (3U)

#define CAL_HL_HWINFO_NPPI_CONTEXTS1_SHIFT                                              (30U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS1_MASK                                               (0xc0000000U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS1_ZERO                                                (0U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS1_FOUR                                                (1U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS1_EIGHT                                               (2U)
#define CAL_HL_HWINFO_NPPI_CONTEXTS1_RESERVED                                            (3U)

#define CAL_HL_SYSCONFIG_SOFTRESET_SHIFT                                                (0U)
#define CAL_HL_SYSCONFIG_SOFTRESET_MASK                                                 (0x00000001U)
#define CAL_HL_SYSCONFIG_SOFTRESET_DONE                                                  (0U)
#define CAL_HL_SYSCONFIG_SOFTRESET_PENDING                                               (1U)
#define CAL_HL_SYSCONFIG_SOFTRESET_NOACTION                                              (0U)
#define CAL_HL_SYSCONFIG_SOFTRESET_RESET                                                 (1U)

#define CAL_HL_SYSCONFIG_IDLEMODE_SHIFT                                                 (2U)
#define CAL_HL_SYSCONFIG_IDLEMODE_MASK                                                  (0x0000000cU)
#define CAL_HL_SYSCONFIG_IDLEMODE_FORCE                                                  (0U)
#define CAL_HL_SYSCONFIG_IDLEMODE_NO                                                     (1U)
#define CAL_HL_SYSCONFIG_IDLEMODE_SMART1                                                 (2U)
#define CAL_HL_SYSCONFIG_IDLEMODE_SMART2                                                 (3U)

#define CAL_HL_SYSCONFIG_RESERVED_SHIFT                                                 (1U)
#define CAL_HL_SYSCONFIG_RESERVED_MASK                                                  (0x00000002U)

#define CAL_HL_SYSCONFIG_RESERVED1_SHIFT                                                (4U)
#define CAL_HL_SYSCONFIG_RESERVED1_MASK                                                 (0xfffffff0U)

#define CAL_HL_IRQ_EOI_LINE_NUMBER_SHIFT                                                (0U)
#define CAL_HL_IRQ_EOI_LINE_NUMBER_MASK                                                 (0x00000001U)
#define CAL_HL_IRQ_EOI_LINE_NUMBER_READ0                                                 (0U)
#define CAL_HL_IRQ_EOI_LINE_NUMBER_EOI0                                                  (0U)

#define CAL_HL_IRQ_EOI_RESERVED_SHIFT                                                   (1U)
#define CAL_HL_IRQ_EOI_RESERVED_MASK                                                    (0xfffffffeU)

#define CAL_HL_IRQSTATUS_RAW_IRQ0_SHIFT                                                 (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ0_MASK                                                  (0x00000001U)
#define CAL_HL_IRQSTATUS_RAW_IRQ0_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ0_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ0_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ0_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ1_SHIFT                                                 (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ1_MASK                                                  (0x00000002U)
#define CAL_HL_IRQSTATUS_RAW_IRQ1_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ1_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ1_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ1_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ2_SHIFT                                                 (2U)
#define CAL_HL_IRQSTATUS_RAW_IRQ2_MASK                                                  (0x00000004U)
#define CAL_HL_IRQSTATUS_RAW_IRQ2_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ2_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ2_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ2_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ3_SHIFT                                                 (3U)
#define CAL_HL_IRQSTATUS_RAW_IRQ3_MASK                                                  (0x00000008U)
#define CAL_HL_IRQSTATUS_RAW_IRQ3_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ3_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ3_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ3_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ4_SHIFT                                                 (4U)
#define CAL_HL_IRQSTATUS_RAW_IRQ4_MASK                                                  (0x00000010U)
#define CAL_HL_IRQSTATUS_RAW_IRQ4_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ4_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ4_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ4_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ5_SHIFT                                                 (5U)
#define CAL_HL_IRQSTATUS_RAW_IRQ5_MASK                                                  (0x00000020U)
#define CAL_HL_IRQSTATUS_RAW_IRQ5_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ5_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ5_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ5_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ6_SHIFT                                                 (6U)
#define CAL_HL_IRQSTATUS_RAW_IRQ6_MASK                                                  (0x00000040U)
#define CAL_HL_IRQSTATUS_RAW_IRQ6_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ6_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ6_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ6_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ7_SHIFT                                                 (7U)
#define CAL_HL_IRQSTATUS_RAW_IRQ7_MASK                                                  (0x00000080U)
#define CAL_HL_IRQSTATUS_RAW_IRQ7_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ7_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ7_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ7_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ8_SHIFT                                                 (8U)
#define CAL_HL_IRQSTATUS_RAW_IRQ8_MASK                                                  (0x00000100U)
#define CAL_HL_IRQSTATUS_RAW_IRQ8_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ8_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ8_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ8_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ9_SHIFT                                                 (9U)
#define CAL_HL_IRQSTATUS_RAW_IRQ9_MASK                                                  (0x00000200U)
#define CAL_HL_IRQSTATUS_RAW_IRQ9_NOEVENT                                                (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ9_PENDING                                                (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ9_NACT                                                   (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ9_SET                                                    (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ10_SHIFT                                                (10U)
#define CAL_HL_IRQSTATUS_RAW_IRQ10_MASK                                                 (0x00000400U)
#define CAL_HL_IRQSTATUS_RAW_IRQ10_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ10_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ10_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ10_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ11_SHIFT                                                (11U)
#define CAL_HL_IRQSTATUS_RAW_IRQ11_MASK                                                 (0x00000800U)
#define CAL_HL_IRQSTATUS_RAW_IRQ11_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ11_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ11_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ11_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ12_SHIFT                                                (12U)
#define CAL_HL_IRQSTATUS_RAW_IRQ12_MASK                                                 (0x00001000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ12_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ12_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ12_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ12_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ13_SHIFT                                                (13U)
#define CAL_HL_IRQSTATUS_RAW_IRQ13_MASK                                                 (0x00002000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ13_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ13_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ13_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ13_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ14_SHIFT                                                (14U)
#define CAL_HL_IRQSTATUS_RAW_IRQ14_MASK                                                 (0x00004000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ14_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ14_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ14_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ14_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ15_SHIFT                                                (15U)
#define CAL_HL_IRQSTATUS_RAW_IRQ15_MASK                                                 (0x00008000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ15_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ15_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ15_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ15_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ16_SHIFT                                                (16U)
#define CAL_HL_IRQSTATUS_RAW_IRQ16_MASK                                                 (0x00010000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ16_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ16_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ16_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ16_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ17_SHIFT                                                (17U)
#define CAL_HL_IRQSTATUS_RAW_IRQ17_MASK                                                 (0x00020000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ17_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ17_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ17_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ17_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ18_SHIFT                                                (18U)
#define CAL_HL_IRQSTATUS_RAW_IRQ18_MASK                                                 (0x00040000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ18_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ18_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ18_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ18_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ19_SHIFT                                                (19U)
#define CAL_HL_IRQSTATUS_RAW_IRQ19_MASK                                                 (0x00080000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ19_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ19_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ19_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ19_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ20_SHIFT                                                (20U)
#define CAL_HL_IRQSTATUS_RAW_IRQ20_MASK                                                 (0x00100000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ20_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ20_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ20_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ20_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ21_SHIFT                                                (21U)
#define CAL_HL_IRQSTATUS_RAW_IRQ21_MASK                                                 (0x00200000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ21_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ21_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ21_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ21_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ22_SHIFT                                                (22U)
#define CAL_HL_IRQSTATUS_RAW_IRQ22_MASK                                                 (0x00400000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ22_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ22_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ22_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ22_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ23_SHIFT                                                (23U)
#define CAL_HL_IRQSTATUS_RAW_IRQ23_MASK                                                 (0x00800000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ23_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ23_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ23_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ23_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ24_SHIFT                                                (24U)
#define CAL_HL_IRQSTATUS_RAW_IRQ24_MASK                                                 (0x01000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ24_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ24_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ24_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ24_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ25_SHIFT                                                (25U)
#define CAL_HL_IRQSTATUS_RAW_IRQ25_MASK                                                 (0x02000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ25_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ25_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ25_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ25_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ26_SHIFT                                                (26U)
#define CAL_HL_IRQSTATUS_RAW_IRQ26_MASK                                                 (0x04000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ26_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ26_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ26_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ26_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ27_SHIFT                                                (27U)
#define CAL_HL_IRQSTATUS_RAW_IRQ27_MASK                                                 (0x08000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ27_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ27_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ27_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ27_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ28_SHIFT                                                (28U)
#define CAL_HL_IRQSTATUS_RAW_IRQ28_MASK                                                 (0x10000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ28_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ28_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ28_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ28_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ29_SHIFT                                                (29U)
#define CAL_HL_IRQSTATUS_RAW_IRQ29_MASK                                                 (0x20000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ29_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ29_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ29_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ29_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ30_SHIFT                                                (30U)
#define CAL_HL_IRQSTATUS_RAW_IRQ30_MASK                                                 (0x40000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ30_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ30_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ30_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ30_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_RAW_IRQ31_SHIFT                                                (31U)
#define CAL_HL_IRQSTATUS_RAW_IRQ31_MASK                                                 (0x80000000U)
#define CAL_HL_IRQSTATUS_RAW_IRQ31_NOEVENT                                               (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ31_PENDING                                               (1U)
#define CAL_HL_IRQSTATUS_RAW_IRQ31_NACT                                                  (0U)
#define CAL_HL_IRQSTATUS_RAW_IRQ31_SET                                                   (1U)

#define CAL_HL_IRQSTATUS_IRQ0_SHIFT                                                     (0U)
#define CAL_HL_IRQSTATUS_IRQ0_MASK                                                      (0x00000001U)
#define CAL_HL_IRQSTATUS_IRQ0_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ0_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ0_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ0_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ1_SHIFT                                                     (1U)
#define CAL_HL_IRQSTATUS_IRQ1_MASK                                                      (0x00000002U)
#define CAL_HL_IRQSTATUS_IRQ1_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ1_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ1_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ1_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ2_SHIFT                                                     (2U)
#define CAL_HL_IRQSTATUS_IRQ2_MASK                                                      (0x00000004U)
#define CAL_HL_IRQSTATUS_IRQ2_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ2_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ2_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ2_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ3_SHIFT                                                     (3U)
#define CAL_HL_IRQSTATUS_IRQ3_MASK                                                      (0x00000008U)
#define CAL_HL_IRQSTATUS_IRQ3_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ3_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ3_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ3_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ4_SHIFT                                                     (4U)
#define CAL_HL_IRQSTATUS_IRQ4_MASK                                                      (0x00000010U)
#define CAL_HL_IRQSTATUS_IRQ4_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ4_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ4_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ4_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ5_SHIFT                                                     (5U)
#define CAL_HL_IRQSTATUS_IRQ5_MASK                                                      (0x00000020U)
#define CAL_HL_IRQSTATUS_IRQ5_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ5_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ5_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ5_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ6_SHIFT                                                     (6U)
#define CAL_HL_IRQSTATUS_IRQ6_MASK                                                      (0x00000040U)
#define CAL_HL_IRQSTATUS_IRQ6_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ6_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ6_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ6_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ7_SHIFT                                                     (7U)
#define CAL_HL_IRQSTATUS_IRQ7_MASK                                                      (0x00000080U)
#define CAL_HL_IRQSTATUS_IRQ7_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ7_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ7_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ7_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ8_SHIFT                                                     (8U)
#define CAL_HL_IRQSTATUS_IRQ8_MASK                                                      (0x00000100U)
#define CAL_HL_IRQSTATUS_IRQ8_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ8_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ8_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ8_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ9_SHIFT                                                     (9U)
#define CAL_HL_IRQSTATUS_IRQ9_MASK                                                      (0x00000200U)
#define CAL_HL_IRQSTATUS_IRQ9_NOEVENT                                                    (0U)
#define CAL_HL_IRQSTATUS_IRQ9_PENDING                                                    (1U)
#define CAL_HL_IRQSTATUS_IRQ9_NACT                                                       (0U)
#define CAL_HL_IRQSTATUS_IRQ9_CLEAR                                                      (1U)

#define CAL_HL_IRQSTATUS_IRQ10_SHIFT                                                    (10U)
#define CAL_HL_IRQSTATUS_IRQ10_MASK                                                     (0x00000400U)
#define CAL_HL_IRQSTATUS_IRQ10_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ10_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ10_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ10_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ11_SHIFT                                                    (11U)
#define CAL_HL_IRQSTATUS_IRQ11_MASK                                                     (0x00000800U)
#define CAL_HL_IRQSTATUS_IRQ11_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ11_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ11_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ11_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ12_SHIFT                                                    (12U)
#define CAL_HL_IRQSTATUS_IRQ12_MASK                                                     (0x00001000U)
#define CAL_HL_IRQSTATUS_IRQ12_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ12_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ12_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ12_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ13_SHIFT                                                    (13U)
#define CAL_HL_IRQSTATUS_IRQ13_MASK                                                     (0x00002000U)
#define CAL_HL_IRQSTATUS_IRQ13_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ13_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ13_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ13_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ14_SHIFT                                                    (14U)
#define CAL_HL_IRQSTATUS_IRQ14_MASK                                                     (0x00004000U)
#define CAL_HL_IRQSTATUS_IRQ14_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ14_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ14_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ14_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ15_SHIFT                                                    (15U)
#define CAL_HL_IRQSTATUS_IRQ15_MASK                                                     (0x00008000U)
#define CAL_HL_IRQSTATUS_IRQ15_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ15_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ15_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ15_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ16_SHIFT                                                    (16U)
#define CAL_HL_IRQSTATUS_IRQ16_MASK                                                     (0x00010000U)
#define CAL_HL_IRQSTATUS_IRQ16_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ16_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ16_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ16_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ17_SHIFT                                                    (17U)
#define CAL_HL_IRQSTATUS_IRQ17_MASK                                                     (0x00020000U)
#define CAL_HL_IRQSTATUS_IRQ17_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ17_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ17_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ17_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ18_SHIFT                                                    (18U)
#define CAL_HL_IRQSTATUS_IRQ18_MASK                                                     (0x00040000U)
#define CAL_HL_IRQSTATUS_IRQ18_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ18_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ18_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ18_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ19_SHIFT                                                    (19U)
#define CAL_HL_IRQSTATUS_IRQ19_MASK                                                     (0x00080000U)
#define CAL_HL_IRQSTATUS_IRQ19_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ19_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ19_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ19_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ20_SHIFT                                                    (20U)
#define CAL_HL_IRQSTATUS_IRQ20_MASK                                                     (0x00100000U)
#define CAL_HL_IRQSTATUS_IRQ20_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ20_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ20_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ20_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ21_SHIFT                                                    (21U)
#define CAL_HL_IRQSTATUS_IRQ21_MASK                                                     (0x00200000U)
#define CAL_HL_IRQSTATUS_IRQ21_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ21_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ21_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ21_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ22_SHIFT                                                    (22U)
#define CAL_HL_IRQSTATUS_IRQ22_MASK                                                     (0x00400000U)
#define CAL_HL_IRQSTATUS_IRQ22_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ22_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ22_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ22_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ23_SHIFT                                                    (23U)
#define CAL_HL_IRQSTATUS_IRQ23_MASK                                                     (0x00800000U)
#define CAL_HL_IRQSTATUS_IRQ23_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ23_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ23_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ23_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ24_SHIFT                                                    (24U)
#define CAL_HL_IRQSTATUS_IRQ24_MASK                                                     (0x01000000U)
#define CAL_HL_IRQSTATUS_IRQ24_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ24_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ24_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ24_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ25_SHIFT                                                    (25U)
#define CAL_HL_IRQSTATUS_IRQ25_MASK                                                     (0x02000000U)
#define CAL_HL_IRQSTATUS_IRQ25_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ25_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ25_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ25_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ26_SHIFT                                                    (26U)
#define CAL_HL_IRQSTATUS_IRQ26_MASK                                                     (0x04000000U)
#define CAL_HL_IRQSTATUS_IRQ26_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ26_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ26_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ26_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ27_SHIFT                                                    (27U)
#define CAL_HL_IRQSTATUS_IRQ27_MASK                                                     (0x08000000U)
#define CAL_HL_IRQSTATUS_IRQ27_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ27_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ27_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ27_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ28_SHIFT                                                    (28U)
#define CAL_HL_IRQSTATUS_IRQ28_MASK                                                     (0x10000000U)
#define CAL_HL_IRQSTATUS_IRQ28_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ28_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ28_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ28_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ29_SHIFT                                                    (29U)
#define CAL_HL_IRQSTATUS_IRQ29_MASK                                                     (0x20000000U)
#define CAL_HL_IRQSTATUS_IRQ29_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ29_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ29_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ29_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ30_SHIFT                                                    (30U)
#define CAL_HL_IRQSTATUS_IRQ30_MASK                                                     (0x40000000U)
#define CAL_HL_IRQSTATUS_IRQ30_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ30_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ30_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ30_CLEAR                                                     (1U)

#define CAL_HL_IRQSTATUS_IRQ31_SHIFT                                                    (31U)
#define CAL_HL_IRQSTATUS_IRQ31_MASK                                                     (0x80000000U)
#define CAL_HL_IRQSTATUS_IRQ31_NOEVENT                                                   (0U)
#define CAL_HL_IRQSTATUS_IRQ31_PENDING                                                   (1U)
#define CAL_HL_IRQSTATUS_IRQ31_NACT                                                      (0U)
#define CAL_HL_IRQSTATUS_IRQ31_CLEAR                                                     (1U)

#define CAL_HL_IRQENABLE_SET_IRQ0_SHIFT                                                 (0U)
#define CAL_HL_IRQENABLE_SET_IRQ0_MASK                                                  (0x00000001U)
#define CAL_HL_IRQENABLE_SET_IRQ0_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ0_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ0_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ0_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ1_SHIFT                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ1_MASK                                                  (0x00000002U)
#define CAL_HL_IRQENABLE_SET_IRQ1_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ1_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ1_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ1_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ2_SHIFT                                                 (2U)
#define CAL_HL_IRQENABLE_SET_IRQ2_MASK                                                  (0x00000004U)
#define CAL_HL_IRQENABLE_SET_IRQ2_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ2_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ2_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ2_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ3_SHIFT                                                 (3U)
#define CAL_HL_IRQENABLE_SET_IRQ3_MASK                                                  (0x00000008U)
#define CAL_HL_IRQENABLE_SET_IRQ3_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ3_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ3_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ3_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ4_SHIFT                                                 (4U)
#define CAL_HL_IRQENABLE_SET_IRQ4_MASK                                                  (0x00000010U)
#define CAL_HL_IRQENABLE_SET_IRQ4_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ4_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ4_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ4_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ5_SHIFT                                                 (5U)
#define CAL_HL_IRQENABLE_SET_IRQ5_MASK                                                  (0x00000020U)
#define CAL_HL_IRQENABLE_SET_IRQ5_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ5_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ5_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ5_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ6_SHIFT                                                 (6U)
#define CAL_HL_IRQENABLE_SET_IRQ6_MASK                                                  (0x00000040U)
#define CAL_HL_IRQENABLE_SET_IRQ6_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ6_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ6_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ6_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ7_SHIFT                                                 (7U)
#define CAL_HL_IRQENABLE_SET_IRQ7_MASK                                                  (0x00000080U)
#define CAL_HL_IRQENABLE_SET_IRQ7_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ7_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ7_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ7_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ8_SHIFT                                                 (8U)
#define CAL_HL_IRQENABLE_SET_IRQ8_MASK                                                  (0x00000100U)
#define CAL_HL_IRQENABLE_SET_IRQ8_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ8_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ8_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ8_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ9_SHIFT                                                 (9U)
#define CAL_HL_IRQENABLE_SET_IRQ9_MASK                                                  (0x00000200U)
#define CAL_HL_IRQENABLE_SET_IRQ9_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ9_ENABLE                                                 (1U)
#define CAL_HL_IRQENABLE_SET_IRQ9_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_SET_IRQ9_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_SET_IRQ10_SHIFT                                                (10U)
#define CAL_HL_IRQENABLE_SET_IRQ10_MASK                                                 (0x00000400U)
#define CAL_HL_IRQENABLE_SET_IRQ10_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ10_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ10_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ10_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ11_SHIFT                                                (11U)
#define CAL_HL_IRQENABLE_SET_IRQ11_MASK                                                 (0x00000800U)
#define CAL_HL_IRQENABLE_SET_IRQ11_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ11_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ11_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ11_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ12_SHIFT                                                (12U)
#define CAL_HL_IRQENABLE_SET_IRQ12_MASK                                                 (0x00001000U)
#define CAL_HL_IRQENABLE_SET_IRQ12_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ12_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ12_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ12_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ13_SHIFT                                                (13U)
#define CAL_HL_IRQENABLE_SET_IRQ13_MASK                                                 (0x00002000U)
#define CAL_HL_IRQENABLE_SET_IRQ13_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ13_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ13_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ13_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ14_SHIFT                                                (14U)
#define CAL_HL_IRQENABLE_SET_IRQ14_MASK                                                 (0x00004000U)
#define CAL_HL_IRQENABLE_SET_IRQ14_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ14_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ14_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ14_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ15_SHIFT                                                (15U)
#define CAL_HL_IRQENABLE_SET_IRQ15_MASK                                                 (0x00008000U)
#define CAL_HL_IRQENABLE_SET_IRQ15_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ15_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ15_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ15_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ16_SHIFT                                                (16U)
#define CAL_HL_IRQENABLE_SET_IRQ16_MASK                                                 (0x00010000U)
#define CAL_HL_IRQENABLE_SET_IRQ16_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ16_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ16_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ16_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ17_SHIFT                                                (17U)
#define CAL_HL_IRQENABLE_SET_IRQ17_MASK                                                 (0x00020000U)
#define CAL_HL_IRQENABLE_SET_IRQ17_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ17_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ17_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ17_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ18_SHIFT                                                (18U)
#define CAL_HL_IRQENABLE_SET_IRQ18_MASK                                                 (0x00040000U)
#define CAL_HL_IRQENABLE_SET_IRQ18_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ18_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ18_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ18_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ19_SHIFT                                                (19U)
#define CAL_HL_IRQENABLE_SET_IRQ19_MASK                                                 (0x00080000U)
#define CAL_HL_IRQENABLE_SET_IRQ19_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ19_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ19_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ19_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ20_SHIFT                                                (20U)
#define CAL_HL_IRQENABLE_SET_IRQ20_MASK                                                 (0x00100000U)
#define CAL_HL_IRQENABLE_SET_IRQ20_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ20_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ20_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ20_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ21_SHIFT                                                (21U)
#define CAL_HL_IRQENABLE_SET_IRQ21_MASK                                                 (0x00200000U)
#define CAL_HL_IRQENABLE_SET_IRQ21_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ21_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ21_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ21_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ22_SHIFT                                                (22U)
#define CAL_HL_IRQENABLE_SET_IRQ22_MASK                                                 (0x00400000U)
#define CAL_HL_IRQENABLE_SET_IRQ22_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ22_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ22_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ22_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ23_SHIFT                                                (23U)
#define CAL_HL_IRQENABLE_SET_IRQ23_MASK                                                 (0x00800000U)
#define CAL_HL_IRQENABLE_SET_IRQ23_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ23_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ23_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ23_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ24_SHIFT                                                (24U)
#define CAL_HL_IRQENABLE_SET_IRQ24_MASK                                                 (0x01000000U)
#define CAL_HL_IRQENABLE_SET_IRQ24_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ24_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ24_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ24_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ25_SHIFT                                                (25U)
#define CAL_HL_IRQENABLE_SET_IRQ25_MASK                                                 (0x02000000U)
#define CAL_HL_IRQENABLE_SET_IRQ25_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ25_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ25_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ25_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ26_SHIFT                                                (26U)
#define CAL_HL_IRQENABLE_SET_IRQ26_MASK                                                 (0x04000000U)
#define CAL_HL_IRQENABLE_SET_IRQ26_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ26_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ26_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ26_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ27_SHIFT                                                (27U)
#define CAL_HL_IRQENABLE_SET_IRQ27_MASK                                                 (0x08000000U)
#define CAL_HL_IRQENABLE_SET_IRQ27_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ27_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ27_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ27_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ28_SHIFT                                                (28U)
#define CAL_HL_IRQENABLE_SET_IRQ28_MASK                                                 (0x10000000U)
#define CAL_HL_IRQENABLE_SET_IRQ28_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ28_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ28_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ28_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ29_SHIFT                                                (29U)
#define CAL_HL_IRQENABLE_SET_IRQ29_MASK                                                 (0x20000000U)
#define CAL_HL_IRQENABLE_SET_IRQ29_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ29_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ29_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ29_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ30_SHIFT                                                (30U)
#define CAL_HL_IRQENABLE_SET_IRQ30_MASK                                                 (0x40000000U)
#define CAL_HL_IRQENABLE_SET_IRQ30_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ30_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ30_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ30_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_SET_IRQ31_SHIFT                                                (31U)
#define CAL_HL_IRQENABLE_SET_IRQ31_MASK                                                 (0x80000000U)
#define CAL_HL_IRQENABLE_SET_IRQ31_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ31_ENABLE                                                (1U)
#define CAL_HL_IRQENABLE_SET_IRQ31_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_SET_IRQ31_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ0_SHIFT                                                 (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ0_MASK                                                  (0x00000001U)
#define CAL_HL_IRQENABLE_CLR_IRQ0_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ0_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ0_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ0_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ1_SHIFT                                                 (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ1_MASK                                                  (0x00000002U)
#define CAL_HL_IRQENABLE_CLR_IRQ1_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ1_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ1_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ1_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ2_SHIFT                                                 (2U)
#define CAL_HL_IRQENABLE_CLR_IRQ2_MASK                                                  (0x00000004U)
#define CAL_HL_IRQENABLE_CLR_IRQ2_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ2_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ2_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ2_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ3_SHIFT                                                 (3U)
#define CAL_HL_IRQENABLE_CLR_IRQ3_MASK                                                  (0x00000008U)
#define CAL_HL_IRQENABLE_CLR_IRQ3_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ3_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ3_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ3_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ4_SHIFT                                                 (4U)
#define CAL_HL_IRQENABLE_CLR_IRQ4_MASK                                                  (0x00000010U)
#define CAL_HL_IRQENABLE_CLR_IRQ4_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ4_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ4_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ4_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ5_SHIFT                                                 (5U)
#define CAL_HL_IRQENABLE_CLR_IRQ5_MASK                                                  (0x00000020U)
#define CAL_HL_IRQENABLE_CLR_IRQ5_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ5_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ5_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ5_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ6_SHIFT                                                 (6U)
#define CAL_HL_IRQENABLE_CLR_IRQ6_MASK                                                  (0x00000040U)
#define CAL_HL_IRQENABLE_CLR_IRQ6_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ6_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ6_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ6_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ7_SHIFT                                                 (7U)
#define CAL_HL_IRQENABLE_CLR_IRQ7_MASK                                                  (0x00000080U)
#define CAL_HL_IRQENABLE_CLR_IRQ7_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ7_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ7_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ7_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ8_SHIFT                                                 (8U)
#define CAL_HL_IRQENABLE_CLR_IRQ8_MASK                                                  (0x00000100U)
#define CAL_HL_IRQENABLE_CLR_IRQ8_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ8_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ8_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ8_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ9_SHIFT                                                 (9U)
#define CAL_HL_IRQENABLE_CLR_IRQ9_MASK                                                  (0x00000200U)
#define CAL_HL_IRQENABLE_CLR_IRQ9_NOACTION                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ9_DISABLE                                                (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ9_DISABLED                                               (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ9_ENABLED                                                (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ10_SHIFT                                                (10U)
#define CAL_HL_IRQENABLE_CLR_IRQ10_MASK                                                 (0x00000400U)
#define CAL_HL_IRQENABLE_CLR_IRQ10_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ10_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ10_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ10_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ11_SHIFT                                                (11U)
#define CAL_HL_IRQENABLE_CLR_IRQ11_MASK                                                 (0x00000800U)
#define CAL_HL_IRQENABLE_CLR_IRQ11_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ11_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ11_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ11_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ12_SHIFT                                                (12U)
#define CAL_HL_IRQENABLE_CLR_IRQ12_MASK                                                 (0x00001000U)
#define CAL_HL_IRQENABLE_CLR_IRQ12_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ12_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ12_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ12_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ13_SHIFT                                                (13U)
#define CAL_HL_IRQENABLE_CLR_IRQ13_MASK                                                 (0x00002000U)
#define CAL_HL_IRQENABLE_CLR_IRQ13_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ13_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ13_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ13_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ14_SHIFT                                                (14U)
#define CAL_HL_IRQENABLE_CLR_IRQ14_MASK                                                 (0x00004000U)
#define CAL_HL_IRQENABLE_CLR_IRQ14_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ14_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ14_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ14_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ15_SHIFT                                                (15U)
#define CAL_HL_IRQENABLE_CLR_IRQ15_MASK                                                 (0x00008000U)
#define CAL_HL_IRQENABLE_CLR_IRQ15_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ15_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ15_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ15_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ16_SHIFT                                                (16U)
#define CAL_HL_IRQENABLE_CLR_IRQ16_MASK                                                 (0x00010000U)
#define CAL_HL_IRQENABLE_CLR_IRQ16_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ16_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ16_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ16_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ17_SHIFT                                                (17U)
#define CAL_HL_IRQENABLE_CLR_IRQ17_MASK                                                 (0x00020000U)
#define CAL_HL_IRQENABLE_CLR_IRQ17_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ17_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ17_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ17_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ18_SHIFT                                                (18U)
#define CAL_HL_IRQENABLE_CLR_IRQ18_MASK                                                 (0x00040000U)
#define CAL_HL_IRQENABLE_CLR_IRQ18_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ18_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ18_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ18_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ19_SHIFT                                                (19U)
#define CAL_HL_IRQENABLE_CLR_IRQ19_MASK                                                 (0x00080000U)
#define CAL_HL_IRQENABLE_CLR_IRQ19_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ19_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ19_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ19_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ20_SHIFT                                                (20U)
#define CAL_HL_IRQENABLE_CLR_IRQ20_MASK                                                 (0x00100000U)
#define CAL_HL_IRQENABLE_CLR_IRQ20_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ20_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ20_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ20_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ21_SHIFT                                                (21U)
#define CAL_HL_IRQENABLE_CLR_IRQ21_MASK                                                 (0x00200000U)
#define CAL_HL_IRQENABLE_CLR_IRQ21_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ21_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ21_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ21_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ22_SHIFT                                                (22U)
#define CAL_HL_IRQENABLE_CLR_IRQ22_MASK                                                 (0x00400000U)
#define CAL_HL_IRQENABLE_CLR_IRQ22_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ22_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ22_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ22_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ23_SHIFT                                                (23U)
#define CAL_HL_IRQENABLE_CLR_IRQ23_MASK                                                 (0x00800000U)
#define CAL_HL_IRQENABLE_CLR_IRQ23_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ23_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ23_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ23_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ24_SHIFT                                                (24U)
#define CAL_HL_IRQENABLE_CLR_IRQ24_MASK                                                 (0x01000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ24_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ24_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ24_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ24_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ25_SHIFT                                                (25U)
#define CAL_HL_IRQENABLE_CLR_IRQ25_MASK                                                 (0x02000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ25_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ25_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ25_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ25_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ26_SHIFT                                                (26U)
#define CAL_HL_IRQENABLE_CLR_IRQ26_MASK                                                 (0x04000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ26_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ26_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ26_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ26_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ27_SHIFT                                                (27U)
#define CAL_HL_IRQENABLE_CLR_IRQ27_MASK                                                 (0x08000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ27_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ27_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ27_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ27_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ28_SHIFT                                                (28U)
#define CAL_HL_IRQENABLE_CLR_IRQ28_MASK                                                 (0x10000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ28_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ28_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ28_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ28_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ29_SHIFT                                                (29U)
#define CAL_HL_IRQENABLE_CLR_IRQ29_MASK                                                 (0x20000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ29_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ29_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ29_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ29_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ30_SHIFT                                                (30U)
#define CAL_HL_IRQENABLE_CLR_IRQ30_MASK                                                 (0x40000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ30_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ30_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ30_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ30_ENABLED                                               (1U)

#define CAL_HL_IRQENABLE_CLR_IRQ31_SHIFT                                                (31U)
#define CAL_HL_IRQENABLE_CLR_IRQ31_MASK                                                 (0x80000000U)
#define CAL_HL_IRQENABLE_CLR_IRQ31_NOACTION                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ31_DISABLE                                               (1U)
#define CAL_HL_IRQENABLE_CLR_IRQ31_DISABLED                                              (0U)
#define CAL_HL_IRQENABLE_CLR_IRQ31_ENABLED                                               (1U)

#define CAL_PIX_PROC_EXTRACT_SHIFT                                                      (1U)
#define CAL_PIX_PROC_EXTRACT_MASK                                                       (0x0000001eU)
#define CAL_PIX_PROC_EXTRACT_B6                                                          (0U)
#define CAL_PIX_PROC_EXTRACT_B7                                                          (1U)
#define CAL_PIX_PROC_EXTRACT_B8                                                          (2U)
#define CAL_PIX_PROC_EXTRACT_B10                                                         (3U)
#define CAL_PIX_PROC_EXTRACT_B10_MIPI                                                    (4U)
#define CAL_PIX_PROC_EXTRACT_B12                                                         (5U)
#define CAL_PIX_PROC_EXTRACT_B12_MIPI                                                    (6U)
#define CAL_PIX_PROC_EXTRACT_B14                                                         (7U)
#define CAL_PIX_PROC_EXTRACT_B14_MIPI                                                    (8U)
#define CAL_PIX_PROC_EXTRACT_B16_BE                                                      (9U)
#define CAL_PIX_PROC_EXTRACT_B16_LE                                                      (10U)

#define CAL_PIX_PROC_DPCMD_SHIFT                                                        (5U)
#define CAL_PIX_PROC_DPCMD_MASK                                                         (0x000003e0U)
#define CAL_PIX_PROC_DPCMD_BYPASS                                                        (0U)
#define CAL_PIX_PROC_DPCMD_DPCM_10_8_1                                                   (2U)
#define CAL_PIX_PROC_DPCMD_DPCM_12_8_1                                                   (8U)
#define CAL_PIX_PROC_DPCMD_DPCM_10_7_1                                                   (4U)
#define CAL_PIX_PROC_DPCMD_DPCM_10_7_2                                                   (5U)
#define CAL_PIX_PROC_DPCMD_DPCM_10_6_1                                                   (6U)
#define CAL_PIX_PROC_DPCMD_DPCM_10_6_2                                                   (7U)
#define CAL_PIX_PROC_DPCMD_DPCM_12_7_1                                                   (10U)
#define CAL_PIX_PROC_DPCMD_DPCM_12_6_1                                                   (12U)
#define CAL_PIX_PROC_DPCMD_DPCM_14_10                                                    (14U)
#define CAL_PIX_PROC_DPCMD_DPCM_14_8_1                                                   (16U)
#define CAL_PIX_PROC_DPCMD_DPCM_16_12_1                                                  (18U)
#define CAL_PIX_PROC_DPCMD_DPCM_16_10_1                                                  (20U)
#define CAL_PIX_PROC_DPCMD_DPCM_16_8_1                                                   (22U)

#define CAL_PIX_PROC_DPCME_SHIFT                                                        (11U)
#define CAL_PIX_PROC_DPCME_MASK                                                         (0x0000f800U)
#define CAL_PIX_PROC_DPCME_BYPASS                                                        (0U)
#define CAL_PIX_PROC_DPCME_DPCM_10_8_1                                                   (2U)
#define CAL_PIX_PROC_DPCME_DPCM_12_8_1                                                   (8U)
#define CAL_PIX_PROC_DPCME_DPCM_14_10                                                    (14U)
#define CAL_PIX_PROC_DPCME_DPCM_14_8_1                                                   (16U)
#define CAL_PIX_PROC_DPCME_DPCM_16_12_1                                                  (18U)
#define CAL_PIX_PROC_DPCME_DPCM_16_10_1                                                  (20U)
#define CAL_PIX_PROC_DPCME_DPCM_16_8_1                                                   (22U)

#define CAL_PIX_PROC_PACK_SHIFT                                                         (16U)
#define CAL_PIX_PROC_PACK_MASK                                                          (0x00070000U)
#define CAL_PIX_PROC_PACK_B8                                                             (0U)
#define CAL_PIX_PROC_PACK_B10_MIPI                                                       (2U)
#define CAL_PIX_PROC_PACK_B12                                                            (3U)
#define CAL_PIX_PROC_PACK_B12_MIPI                                                       (4U)
#define CAL_PIX_PROC_PACK_B16                                                            (5U)
#define CAL_PIX_PROC_PACK_ARGB                                                           (6U)

#define CAL_PIX_PROC_CPORT_SHIFT                                                        (19U)
#define CAL_PIX_PROC_CPORT_MASK                                                         (0x00f80000U)

#define CAL_PIX_PROC_EN_SHIFT                                                           (0U)
#define CAL_PIX_PROC_EN_MASK                                                            (0x00000001U)
#define CAL_PIX_PROC_EN_DIS                                                              (0U)
#define CAL_PIX_PROC_EN                                                                  (1U)

#define CAL_PIX_PROC_RESERVED_SHIFT                                                     (24U)
#define CAL_PIX_PROC_RESERVED_MASK                                                      (0xff000000U)

#define CAL_PIX_PROC_RESERVED1_SHIFT                                                    (10U)
#define CAL_PIX_PROC_RESERVED1_MASK                                                     (0x00000400U)

#define CAL_CTRL_TAGCNT_SHIFT                                                           (1U)
#define CAL_CTRL_TAGCNT_MASK                                                            (0x0000001eU)

#define CAL_CTRL_BURSTSIZE_SHIFT                                                        (5U)
#define CAL_CTRL_BURSTSIZE_MASK                                                         (0x00000060U)
#define CAL_CTRL_BURSTSIZE_BURST16                                                       (0U)
#define CAL_CTRL_BURSTSIZE_BURST32                                                       (1U)
#define CAL_CTRL_BURSTSIZE_BURST64                                                       (2U)
#define CAL_CTRL_BURSTSIZE_BURST128                                                      (3U)

#define CAL_CTRL_LL_FORCE_STATE_SHIFT                                                   (7U)
#define CAL_CTRL_LL_FORCE_STATE_MASK                                                    (0x00001f80U)

#define CAL_CTRL_POSTED_WRITES_SHIFT                                                    (0U)
#define CAL_CTRL_POSTED_WRITES_MASK                                                     (0x00000001U)
#define CAL_CTRL_POSTED_WRITES_NONPOSTED                                                 (0U)
#define CAL_CTRL_POSTED_WRITES                                                           (1U)

#define CAL_CTRL_MFLAGL_SHIFT                                                           (13U)
#define CAL_CTRL_MFLAGL_MASK                                                            (0x001fe000U)

#define CAL_CTRL_PWRSCPCLK_SHIFT                                                        (21U)
#define CAL_CTRL_PWRSCPCLK_MASK                                                         (0x00200000U)
#define CAL_CTRL_PWRSCPCLK_AUTO                                                          (0U)
#define CAL_CTRL_PWRSCPCLK_FORCE                                                         (1U)

#define CAL_CTRL_RESERVED_SHIFT                                                         (23U)
#define CAL_CTRL_RESERVED_MASK                                                          (0x00800000U)

#define CAL_CTRL_MFLAGH_SHIFT                                                           (24U)
#define CAL_CTRL_MFLAGH_MASK                                                            (0xff000000U)

#define CAL_CTRL_RD_DMA_STALL_SHIFT                                                     (22U)
#define CAL_CTRL_RD_DMA_STALL_MASK                                                      (0x00400000U)
#define CAL_CTRL_RD_DMA_STALL_DIS                                                        (0U)
#define CAL_CTRL_RD_DMA_STALL_EN                                                         (1U)

#define CAL_CTRL1_INTERLEAVE01_SHIFT                                                    (2U)
#define CAL_CTRL1_INTERLEAVE01_MASK                                                     (0x0000000cU)
#define CAL_CTRL1_INTERLEAVE01_DISABLED                                                  (0U)
#define CAL_CTRL1_INTERLEAVE01_PIX1                                                      (1U)
#define CAL_CTRL1_INTERLEAVE01_PIX4                                                      (2U)
#define CAL_CTRL1_INTERLEAVE01_RESERVED                                                  (3U)

#define CAL_CTRL1_PPI_GROUPING_SHIFT                                                    (0U)
#define CAL_CTRL1_PPI_GROUPING_MASK                                                     (0x00000003U)
#define CAL_CTRL1_PPI_GROUPING_DISABLED                                                  (0U)
#define CAL_CTRL1_PPI_GROUPING_RESERVED                                                  (1U)
#define CAL_CTRL1_PPI_GROUPING_0                                                         (2U)
#define CAL_CTRL1_PPI_GROUPING_1                                                         (3U)

#define CAL_CTRL1_INTERLEAVE23_SHIFT                                                    (4U)
#define CAL_CTRL1_INTERLEAVE23_MASK                                                     (0x00000030U)
#define CAL_CTRL1_INTERLEAVE23_DISABLED                                                  (0U)
#define CAL_CTRL1_INTERLEAVE23_PIX1                                                      (1U)
#define CAL_CTRL1_INTERLEAVE23_PIX4                                                      (2U)
#define CAL_CTRL1_INTERLEAVE23_RESERVED                                                  (3U)

#define CAL_CTRL1_RESERVED_SHIFT                                                        (6U)
#define CAL_CTRL1_RESERVED_MASK                                                         (0xffffffc0U)

#define CAL_LINE_NUMBER_EVT_CPORT_SHIFT                                                 (0U)
#define CAL_LINE_NUMBER_EVT_CPORT_MASK                                                  (0x0000001fU)

#define CAL_LINE_NUMBER_EVT_SHIFT                                                       (16U)
#define CAL_LINE_NUMBER_EVT_MASK                                                        (0x3fff0000U)

#define CAL_LINE_NUMBER_EVT_RESERVED_SHIFT                                              (5U)
#define CAL_LINE_NUMBER_EVT_RESERVED_MASK                                               (0x0000ffe0U)

#define CAL_LINE_NUMBER_EVT_RESERVED1_SHIFT                                             (30U)
#define CAL_LINE_NUMBER_EVT_RESERVED1_MASK                                              (0xc0000000U)

#define CAL_VPORT_CTRL1_PCLK_SHIFT                                                      (0U)
#define CAL_VPORT_CTRL1_PCLK_MASK                                                       (0x0001ffffU)

#define CAL_VPORT_CTRL1_XBLK_SHIFT                                                      (17U)
#define CAL_VPORT_CTRL1_XBLK_MASK                                                       (0x01fe0000U)

#define CAL_VPORT_CTRL1_YBLK_SHIFT                                                      (25U)
#define CAL_VPORT_CTRL1_YBLK_MASK                                                       (0x7e000000U)

#define CAL_VPORT_CTRL1_WIDTH_SHIFT                                                     (31U)
#define CAL_VPORT_CTRL1_WIDTH_MASK                                                      (0x80000000U)
#define CAL_VPORT_CTRL1_WIDTH_ONE                                                        (0U)
#define CAL_VPORT_CTRL1_WIDTH_TWO                                                        (1U)

#define CAL_VPORT_CTRL2_CPORT_SHIFT                                                     (0U)
#define CAL_VPORT_CTRL2_CPORT_MASK                                                      (0x0000001fU)

#define CAL_VPORT_CTRL2_RDY_THR_SHIFT                                                   (18U)
#define CAL_VPORT_CTRL2_RDY_THR_MASK                                                    (0xfffc0000U)

#define CAL_VPORT_CTRL2_FSM_RESET_SHIFT                                                 (17U)
#define CAL_VPORT_CTRL2_FSM_RESET_MASK                                                  (0x00020000U)
#define CAL_VPORT_CTRL2_FSM_RESET_NOEFFECT                                               (0U)
#define CAL_VPORT_CTRL2_FSM_RESET                                                        (1U)

#define CAL_VPORT_CTRL2_FS_RESETS_SHIFT                                                 (16U)
#define CAL_VPORT_CTRL2_FS_RESETS_MASK                                                  (0x00010000U)
#define CAL_VPORT_CTRL2_FS_RESETS_NO                                                     (0U)
#define CAL_VPORT_CTRL2_FS_RESETS_YES                                                    (1U)

#define CAL_VPORT_CTRL2_RESERVED_SHIFT                                                  (5U)
#define CAL_VPORT_CTRL2_RESERVED_MASK                                                   (0x00007fe0U)

#define CAL_VPORT_CTRL2_FREERUNNING_SHIFT                                               (15U)
#define CAL_VPORT_CTRL2_FREERUNNING_MASK                                                (0x00008000U)
#define CAL_VPORT_CTRL2_FREERUNNING_GATED                                                (0U)
#define CAL_VPORT_CTRL2_FREERUNNING_FREE                                                 (1U)

#define CAL_BYS_CTRL1_XBLK_SHIFT                                                        (17U)
#define CAL_BYS_CTRL1_XBLK_MASK                                                         (0x01fe0000U)

#define CAL_BYS_CTRL1_YBLK_SHIFT                                                        (25U)
#define CAL_BYS_CTRL1_YBLK_MASK                                                         (0x7e000000U)

#define CAL_BYS_CTRL1_PCLK_SHIFT                                                        (0U)
#define CAL_BYS_CTRL1_PCLK_MASK                                                         (0x0001ffffU)

#define CAL_BYS_CTRL1_BYSINEN_SHIFT                                                     (31U)
#define CAL_BYS_CTRL1_BYSINEN_MASK                                                      (0x80000000U)
#define CAL_BYS_CTRL1_BYSINEN_DIS                                                        (0U)
#define CAL_BYS_CTRL1_BYSINEN_EN                                                         (1U)

#define CAL_BYS_CTRL2_CPORTIN_SHIFT                                                     (0U)
#define CAL_BYS_CTRL2_CPORTIN_MASK                                                      (0x0000001fU)

#define CAL_BYS_CTRL2_CPORTOUT_SHIFT                                                    (5U)
#define CAL_BYS_CTRL2_CPORTOUT_MASK                                                     (0x000003e0U)

#define CAL_BYS_CTRL2_DUPLICATEDDATA_SHIFT                                              (10U)
#define CAL_BYS_CTRL2_DUPLICATEDDATA_MASK                                               (0x00000400U)
#define CAL_BYS_CTRL2_DUPLICATEDDATA_NO                                                  (0U)
#define CAL_BYS_CTRL2_DUPLICATEDDATA_YES                                                 (1U)

#define CAL_BYS_CTRL2_RESERVED_SHIFT                                                    (12U)
#define CAL_BYS_CTRL2_RESERVED_MASK                                                     (0xfffff000U)

#define CAL_BYS_CTRL2_FREERUNNING_SHIFT                                                 (11U)
#define CAL_BYS_CTRL2_FREERUNNING_MASK                                                  (0x00000800U)
#define CAL_BYS_CTRL2_FREERUNNING_NO                                                     (0U)
#define CAL_BYS_CTRL2_FREERUNNING_YES                                                    (1U)

#define CAL_RD_DMA_CTRL_GO_SHIFT                                                        (0U)
#define CAL_RD_DMA_CTRL_GO_MASK                                                         (0x00000001U)
#define CAL_RD_DMA_CTRL_GO_DIS                                                           (0U)
#define CAL_RD_DMA_CTRL_GO_EN                                                            (1U)
#define CAL_RD_DMA_CTRL_GO_IDLE                                                          (0U)
#define CAL_RD_DMA_CTRL_GO_BUSY                                                          (1U)

#define CAL_RD_DMA_CTRL_BW_LIMITER_SHIFT                                                (2U)
#define CAL_RD_DMA_CTRL_BW_LIMITER_MASK                                                 (0x000007fcU)

#define CAL_RD_DMA_CTRL_INIT_SHIFT                                                      (1U)
#define CAL_RD_DMA_CTRL_INIT_MASK                                                       (0x00000002U)
#define CAL_RD_DMA_CTRL_INIT_DIS                                                         (0U)
#define CAL_RD_DMA_CTRL_INIT_EN                                                          (1U)

#define CAL_RD_DMA_CTRL_OCP_TAG_CNT_SHIFT                                               (11U)
#define CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK                                                (0x00007800U)

#define CAL_RD_DMA_CTRL_PCLK_SHIFT                                                      (15U)
#define CAL_RD_DMA_CTRL_PCLK_MASK                                                       (0xffff8000U)

#define CAL_RD_DMA_PIX_ADDR_SHIFT                                                       (3U)
#define CAL_RD_DMA_PIX_ADDR_MASK                                                        (0xfffffff8U)

#define CAL_RD_DMA_PIX_ADDR_RESERVED_SHIFT                                              (0U)
#define CAL_RD_DMA_PIX_ADDR_RESERVED_MASK                                               (0x00000007U)

#define CAL_RD_DMA_PIX_OFST_SHIFT                                                       (4U)
#define CAL_RD_DMA_PIX_OFST_MASK                                                        (0xfffffff0U)

#define CAL_RD_DMA_PIX_OFST_RESERVED_SHIFT                                              (0U)
#define CAL_RD_DMA_PIX_OFST_RESERVED_MASK                                               (0x0000000fU)

#define CAL_RD_DMA_XSIZE_SHIFT                                                          (19U)
#define CAL_RD_DMA_XSIZE_MASK                                                           (0xfff80000U)

#define CAL_RD_DMA_XSIZE_RESERVED_SHIFT                                                 (0U)
#define CAL_RD_DMA_XSIZE_RESERVED_MASK                                                  (0x0007ffffU)

#define CAL_RD_DMA_YSIZE_SHIFT                                                          (16U)
#define CAL_RD_DMA_YSIZE_MASK                                                           (0x3fff0000U)

#define CAL_RD_DMA_YSIZE_RESERVED_SHIFT                                                 (0U)
#define CAL_RD_DMA_YSIZE_RESERVED_MASK                                                  (0x0000ffffU)

#define CAL_RD_DMA_YSIZE_RESERVED1_SHIFT                                                (30U)
#define CAL_RD_DMA_YSIZE_RESERVED1_MASK                                                 (0xc0000000U)

#define CAL_RD_DMA_INIT_ADDR_SHIFT                                                      (3U)
#define CAL_RD_DMA_INIT_ADDR_MASK                                                       (0xfffffff8U)

#define CAL_RD_DMA_INIT_ADDR_RESERVED_SHIFT                                             (0U)
#define CAL_RD_DMA_INIT_ADDR_RESERVED_MASK                                              (0x00000007U)

#define CAL_RD_DMA_INIT_OFST_SHIFT                                                      (3U)
#define CAL_RD_DMA_INIT_OFST_MASK                                                       (0xfffffff8U)

#define CAL_RD_DMA_INIT_OFST_RESERVED_SHIFT                                             (0U)
#define CAL_RD_DMA_INIT_OFST_RESERVED_MASK                                              (0x00000007U)

#define CAL_RD_DMA_CTRL2_CIRC_MODE_SHIFT                                                (0U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_MASK                                                 (0x00000007U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_DIS                                                   (0U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_ONE                                                   (1U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_FOUR                                                  (2U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_SIXTEEN                                               (3U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_SIXTYFOUR                                             (4U)
#define CAL_RD_DMA_CTRL2_CIRC_MODE_RESERVED                                              (5U)

#define CAL_RD_DMA_CTRL2_CIRC_SIZE_SHIFT                                                (16U)
#define CAL_RD_DMA_CTRL2_CIRC_SIZE_MASK                                                 (0x3fff0000U)

#define CAL_RD_DMA_CTRL2_ICM_CSTART_SHIFT                                               (3U)
#define CAL_RD_DMA_CTRL2_ICM_CSTART_MASK                                                (0x00000008U)
#define CAL_RD_DMA_CTRL2_ICM_CSTART_DIS                                                  (0U)
#define CAL_RD_DMA_CTRL2_ICM_CSTART_EN                                                   (1U)

#define CAL_RD_DMA_CTRL2_PATTERN_SHIFT                                                  (4U)
#define CAL_RD_DMA_CTRL2_PATTERN_MASK                                                   (0x00000030U)
#define CAL_RD_DMA_CTRL2_PATTERN_LINEAR                                                  (0U)
#define CAL_RD_DMA_CTRL2_PATTERN_YUV420                                                  (1U)
#define CAL_RD_DMA_CTRL2_PATTERN_RD2SKIP2                                                (2U)
#define CAL_RD_DMA_CTRL2_PATTERN_RD2SKIP4                                                (3U)

#define CAL_RD_DMA_CTRL2_RESERVED_SHIFT                                                 (7U)
#define CAL_RD_DMA_CTRL2_RESERVED_MASK                                                  (0x0000ff80U)

#define CAL_RD_DMA_CTRL2_RESERVED1_SHIFT                                                (30U)
#define CAL_RD_DMA_CTRL2_RESERVED1_MASK                                                 (0xc0000000U)

#define CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_SHIFT                                           (6U)
#define CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_MASK                                            (0x00000040U)
#define CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_FREERUNNING                                      (0U)
#define CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_WAITFORBYSOUT                                    (1U)

#define CAL_CSI2_PPI_CTRL_IF_EN_SHIFT                                                   (0U)
#define CAL_CSI2_PPI_CTRL_IF_EN_MASK                                                    (0x00000001U)
#define CAL_CSI2_PPI_CTRL_IF_EN_DISABLE                                                  (0U)
#define CAL_CSI2_PPI_CTRL_IF_EN_ENABLE                                                   (1U)

#define CAL_CSI2_PPI_CTRL_FRAME_SHIFT                                                   (3U)
#define CAL_CSI2_PPI_CTRL_FRAME_MASK                                                    (0x00000008U)
#define CAL_CSI2_PPI_CTRL_FRAME_IMMEDIATE                                                (0U)
#define CAL_CSI2_PPI_CTRL_FRAME                                                          (1U)

#define CAL_CSI2_PPI_CTRL_ECC_EN_SHIFT                                                  (2U)
#define CAL_CSI2_PPI_CTRL_ECC_EN_MASK                                                   (0x00000004U)
#define CAL_CSI2_PPI_CTRL_ECC_EN_DISABLE                                                 (0U)
#define CAL_CSI2_PPI_CTRL_ECC_EN_ENABLE                                                  (1U)

#define CAL_CSI2_PPI_CTRL_RESERVED_SHIFT                                                (4U)
#define CAL_CSI2_PPI_CTRL_RESERVED_MASK                                                 (0xfffffff0U)

#define CAL_CSI2_PPI_CTRL_RESERVED1_SHIFT                                               (1U)
#define CAL_CSI2_PPI_CTRL_RESERVED1_MASK                                                (0x00000002U)

#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK                                           (0x00000008U)

#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT                                     (0U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK                                      (0x00000007U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_4                                          (4U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_2                                          (2U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_5                                          (5U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_3                                          (3U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_1                                          (1U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_SHIFT                                          (7U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK                                           (0x00000080U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_PLUSMINUS                                       (0U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MINUSPLUS                                       (1U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_SHIFT                                     (8U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK                                      (0x00000700U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_3                                          (3U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_5                                          (5U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_NOT_USED                                   (0U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_2                                          (2U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_4                                          (4U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_1                                          (1U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_SHIFT                                     (16U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK                                      (0x00070000U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_NOT_USED                                   (0U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_2                                          (2U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_5                                          (5U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_3                                          (3U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_1                                          (1U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_4                                          (4U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_SHIFT                                          (11U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK                                           (0x00000800U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MINUSPLUS                                       (1U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_PLUSMINUS                                       (0U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_SHIFT                                     (12U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK                                      (0x00007000U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_1                                          (1U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_4                                          (4U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_2                                          (2U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_5                                          (5U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_NOT_USED                                   (0U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_3                                          (3U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_SHIFT                                     (4U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK                                      (0x00000070U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_3                                          (3U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_4                                          (4U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_1                                          (1U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_2                                          (2U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_5                                          (5U)

#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_SHIFT                                          (3U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK                                           (0x00000008U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_PLUSMINUS                                       (0U)
#define CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MINUSPLUS                                       (1U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_SHIFT                                          (19U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK                                           (0x00080000U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MINUSPLUS                                       (1U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_PLUSMINUS                                       (0U)

#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_SHIFT                                          (15U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK                                           (0x00008000U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_PLUSMINUS                                       (0U)
#define CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MINUSPLUS                                       (1U)

#define CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT                                            (27U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK                                             (0x18000000U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_OFF                                         (0U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON                                          (1U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ULP                                         (2U)

#define CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT                                         (25U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK                                          (0x06000000U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_OFF                                      (0U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ON                                       (1U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ULP                                      (2U)

#define CAL_CSI2_COMPLEXIO_CFG_PWR_AUTO_SHIFT                                           (24U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_AUTO_MASK                                            (0x01000000U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_AUTO_DISABLE                                          (0U)
#define CAL_CSI2_COMPLEXIO_CFG_PWR_AUTO_ENABLE                                           (1U)

#define CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_SHIFT                                         (29U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_MASK                                          (0x20000000U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_RESETCOMPLETED                                 (1U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_RESETONGOING                                   (0U)

#define CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_SHIFT                                         (30U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK                                          (0x40000000U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL                                                (0U)
#define CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_OPERATIONAL                                    (1U)

#define CAL_CSI2_COMPLEXIO_CFG_RESERVED_SHIFT                                           (20U)
#define CAL_CSI2_COMPLEXIO_CFG_RESERVED_MASK                                            (0x00f00000U)

#define CAL_CSI2_COMPLEXIO_CFG_RESERVED1_SHIFT                                          (31U)
#define CAL_CSI2_COMPLEXIO_CFG_RESERVED1_MASK                                           (0x80000000U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_SHIFT                                (8U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_MASK                                 (0x00000100U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_TRUE                                  (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS4_FALSE                                 (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_SHIFT                                    (3U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_MASK                                     (0x00000008U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_FALSE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS4_TRUE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_SHIFT                                    (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_MASK                                     (0x00000002U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_FALSE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS2_TRUE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_SHIFT                                    (4U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_MASK                                     (0x00000010U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_TRUE                                      (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS5_FALSE                                     (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_SHIFT                                (6U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_MASK                                 (0x00000040U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_FALSE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS2_TRUE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_SHIFT                                (7U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_MASK                                 (0x00000080U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_TRUE                                  (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS3_FALSE                                 (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_SHIFT                                (9U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_MASK                                 (0x00000200U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_TRUE                                  (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS5_FALSE                                 (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_SHIFT                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_MASK                                     (0x00000001U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_FALSE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS1_TRUE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_SHIFT                                    (2U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_MASK                                     (0x00000004U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_FALSE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTHS3_TRUE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_SHIFT                                (5U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_MASK                                 (0x00000020U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_FALSE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRSOTSYNCHS1_TRUE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_SHIFT                                      (10U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_MASK                                       (0x00000400U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_TRUE                                        (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC1_FALSE                                       (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_SHIFT                                      (11U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_MASK                                       (0x00000800U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_TRUE                                        (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC2_FALSE                                       (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_SHIFT                                      (12U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_MASK                                       (0x00001000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_TRUE                                        (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC3_FALSE                                       (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_SHIFT                                      (13U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_MASK                                       (0x00002000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_FALSE                                       (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC4_TRUE                                        (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_SHIFT                                      (14U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_MASK                                       (0x00004000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_FALSE                                       (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRESC5_TRUE                                        (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_SHIFT                                  (15U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_MASK                                   (0x00008000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_TRUE                                    (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL1_FALSE                                   (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_SHIFT                                  (16U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_MASK                                   (0x00010000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_FALSE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL2_TRUE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_SHIFT                                  (17U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_MASK                                   (0x00020000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_FALSE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL3_TRUE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_SHIFT                                  (18U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_MASK                                   (0x00040000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_FALSE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL4_TRUE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_SHIFT                                  (19U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_MASK                                   (0x00080000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_FALSE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ERRCONTROL5_TRUE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_SHIFT                                   (20U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_MASK                                    (0x00100000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_FALSE                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM1_TRUE                                     (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_SHIFT                                   (23U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_MASK                                    (0x00800000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_FALSE                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM4_TRUE                                     (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_SHIFT                                   (22U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_MASK                                    (0x00400000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_FALSE                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM3_TRUE                                     (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_SHIFT                                   (21U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_MASK                                    (0x00200000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_FALSE                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM2_TRUE                                     (1U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_SHIFT                                   (24U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_MASK                                    (0x01000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_TRUE                                     (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEULPM5_FALSE                                    (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_SHIFT                            (25U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_MASK                             (0x02000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_TRUE                              (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMENTER_FALSE                             (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_SHIFT                             (26U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_MASK                              (0x04000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_TRUE                               (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_STATEALLULPMEXIT_FALSE                              (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_FIFO_OVR_SHIFT                                     (27U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_FIFO_OVR_MASK                                      (0x08000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_FIFO_OVR_TRUE                                       (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_FIFO_OVR_FALSE                                      (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_SHORT_PACKET_SHIFT                                 (28U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_SHORT_PACKET_MASK                                  (0x10000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_SHORT_PACKET_TRUE                                   (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_SHORT_PACKET_FALSE                                  (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ECC_NO_CORRECTION_SHIFT                            (30U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ECC_NO_CORRECTION_MASK                             (0x40000000U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ECC_NO_CORRECTION_TRUE                              (1U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_ECC_NO_CORRECTION_FALSE                             (0U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_RESERVED_SHIFT                                     (31U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_RESERVED_MASK                                      (0x80000000U)

#define CAL_CSI2_COMPLEXIO_IRQSTATUS_RESERVED1_SHIFT                                    (29U)
#define CAL_CSI2_COMPLEXIO_IRQSTATUS_RESERVED1_MASK                                     (0x20000000U)

#define CAL_CSI2_SHORT_PACKET_RESERVED_SHIFT                                            (24U)
#define CAL_CSI2_SHORT_PACKET_RESERVED_MASK                                             (0xff000000U)

#define CAL_CSI2_SHORT_PACKET_SHIFT                                                     (0U)
#define CAL_CSI2_SHORT_PACKET_MASK                                                      (0x00ffffffU)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC3_SHIFT                                      (12U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC3_MASK                                       (0x00001000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC3_DISABLE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC3_ENABLE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_SHIFT                                (6U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_MASK                                 (0x00000040U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_DISABLE                               (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS2_ENABLE                                (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC1_SHIFT                                      (10U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC1_MASK                                       (0x00000400U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC1_DISABLE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC1_ENABLE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_SHIFT                                    (2U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_MASK                                     (0x00000004U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_DISABLE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS3_ENABLE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC4_SHIFT                                      (13U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC4_MASK                                       (0x00002000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC4_DISABLE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC4_ENABLE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_SHIFT                                  (16U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_MASK                                   (0x00010000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_DISABLE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL2_ENABLE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_SHIFT                                (8U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_MASK                                 (0x00000100U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_DISABLE                               (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS4_ENABLE                                (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_SHIFT                                (7U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_MASK                                 (0x00000080U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_DISABLE                               (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS3_ENABLE                                (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC5_SHIFT                                      (14U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC5_MASK                                       (0x00004000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC5_DISABLE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC5_ENABLE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_SHIFT                                  (19U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_MASK                                   (0x00080000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_DISABLE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL5_ENABLE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC2_SHIFT                                      (11U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC2_MASK                                       (0x00000800U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC2_DISABLE                                     (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRESC2_ENABLE                                      (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_SHIFT                                    (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_MASK                                     (0x00000001U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_DISABLE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS1_ENABLE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_SHIFT                                    (3U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_MASK                                     (0x00000008U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_DISABLE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS4_ENABLE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_SHIFT                                (5U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_MASK                                 (0x00000020U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_DISABLE                               (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS1_ENABLE                                (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_SHIFT                                    (4U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_MASK                                     (0x00000010U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_DISABLE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS5_ENABLE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_SHIFT                                  (17U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_MASK                                   (0x00020000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_DISABLE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL3_ENABLE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_SHIFT                                (9U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_MASK                                 (0x00000200U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_DISABLE                               (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTSYNCHS5_ENABLE                                (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_SHIFT                                  (15U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_MASK                                   (0x00008000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_DISABLE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL1_ENABLE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_SHIFT                                  (18U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_MASK                                   (0x00040000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_DISABLE                                 (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRCONTROL4_ENABLE                                  (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_SHIFT                                    (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_MASK                                     (0x00000002U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_DISABLE                                   (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ERRSOTHS2_ENABLE                                    (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_SHIFT                                   (20U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_MASK                                    (0x00100000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_DISABLE                                  (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM1_ENABLE                                   (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_SHIFT                                   (21U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_MASK                                    (0x00200000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_DISABLE                                  (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM2_ENABLE                                   (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_SHIFT                                   (22U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_MASK                                    (0x00400000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_DISABLE                                  (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM3_ENABLE                                   (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_SHIFT                                   (23U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_MASK                                    (0x00800000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_DISABLE                                  (0U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM4_ENABLE                                   (1U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_SHIFT                                   (24U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_MASK                                    (0x01000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_ENABLE                                   (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEULPM5_DISABLE                                  (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_SHIFT                             (26U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_MASK                              (0x04000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_ENABLE                             (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMEXIT_DISABLE                            (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_SHIFT                            (25U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_MASK                             (0x02000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_ENABLE                            (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_STATEALLULPMENTER_DISABLE                           (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_FIFO_OVR_SHIFT                                     (27U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_FIFO_OVR_MASK                                      (0x08000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_FIFO_OVR_ENABLE                                     (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_FIFO_OVR_DISABLE                                    (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_SHORT_PACKET_SHIFT                                 (28U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_SHORT_PACKET_MASK                                  (0x10000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_SHORT_PACKET_ENABLE                                 (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_SHORT_PACKET_DISABLE                                (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_ECC_NO_CORRECTION_SHIFT                            (30U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ECC_NO_CORRECTION_MASK                             (0x40000000U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ECC_NO_CORRECTION_ENABLE                            (1U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_ECC_NO_CORRECTION_DISABLE                           (0U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_RESERVED_SHIFT                                     (31U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_RESERVED_MASK                                      (0x80000000U)

#define CAL_CSI2_COMPLEXIO_IRQENABLE_RESERVED1_SHIFT                                    (29U)
#define CAL_CSI2_COMPLEXIO_IRQENABLE_RESERVED1_MASK                                     (0x20000000U)

#define CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT                                    (0U)
#define CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK                                     (0x00001fffU)

#define CAL_CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT                                         (13U)
#define CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK                                          (0x00002000U)
#define CAL_CSI2_TIMING_STOP_STATE_X4_IO1_DISABLE                                        (0U)
#define CAL_CSI2_TIMING_STOP_STATE_X4_IO1_ENABLE                                         (1U)

#define CAL_CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT                                        (14U)
#define CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK                                         (0x00004000U)
#define CAL_CSI2_TIMING_STOP_STATE_X16_IO1_DISABLE                                       (0U)
#define CAL_CSI2_TIMING_STOP_STATE_X16_IO1_ENABLE                                        (1U)

#define CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_SHIFT                                         (15U)
#define CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK                                          (0x00008000U)
#define CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_DEASSERTION                                    (0U)
#define CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_ASSERTION                                      (1U)

#define CAL_CSI2_TIMING_RESERVED_SHIFT                                                  (16U)
#define CAL_CSI2_TIMING_RESERVED_MASK                                                   (0xffff0000U)

#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_0_SHIFT                                            (2U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_0_MASK                                             (0x00000004U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_0_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_0_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_0_SHIFT                                            (3U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_0_MASK                                             (0x00000008U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_0_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_0_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_0_SHIFT                                            (0U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_0_MASK                                             (0x00000001U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_0_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_0_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_0_SHIFT                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_0_MASK                                             (0x00000002U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_0_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_0_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_0_SHIFT                                            (4U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_0_MASK                                             (0x00000010U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_0_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_0_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_0_SHIFT                               (5U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_0_MASK                                (0x00000020U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_0_DISABLE                              (0U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_0_ENABLE                               (1U)

#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_1_SHIFT                                            (8U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_1_MASK                                             (0x00000100U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_1_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_1_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_RESERVED_SHIFT                                            (6U)
#define CAL_CSI2_VC_IRQENABLE_RESERVED_MASK                                             (0x000000c0U)

#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_1_SHIFT                                            (9U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_1_MASK                                             (0x00000200U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_1_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_1_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_1_SHIFT                                            (10U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_1_MASK                                             (0x00000400U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_1_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_1_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_1_SHIFT                                            (11U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_1_MASK                                             (0x00000800U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_1_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_1_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_1_SHIFT                                            (12U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_1_MASK                                             (0x00001000U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_1_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_1_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_1_SHIFT                               (13U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_1_MASK                                (0x00002000U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_1_DISABLE                              (0U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_1_ENABLE                               (1U)

#define CAL_CSI2_VC_IRQENABLE_RESERVED1_SHIFT                                           (14U)
#define CAL_CSI2_VC_IRQENABLE_RESERVED1_MASK                                            (0x0000c000U)

#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_2_SHIFT                                            (16U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_2_MASK                                             (0x00010000U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_2_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_2_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_2_SHIFT                                            (17U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_2_MASK                                             (0x00020000U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_2_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_2_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_2_SHIFT                                            (18U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_2_MASK                                             (0x00040000U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_2_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_2_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_2_SHIFT                                            (19U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_2_MASK                                             (0x00080000U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_2_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_2_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_2_SHIFT                                            (20U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_2_MASK                                             (0x00100000U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_2_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_2_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_2_SHIFT                               (21U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_2_MASK                                (0x00200000U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_2_DISABLE                              (0U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_2_ENABLE                               (1U)

#define CAL_CSI2_VC_IRQENABLE_RESERVED2_SHIFT                                           (22U)
#define CAL_CSI2_VC_IRQENABLE_RESERVED2_MASK                                            (0x00c00000U)

#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_3_SHIFT                                            (24U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_3_MASK                                             (0x01000000U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_3_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_FS_IRQ_3_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_3_SHIFT                                            (25U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_3_MASK                                             (0x02000000U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_3_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_FE_IRQ_3_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_3_SHIFT                                            (26U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_3_MASK                                             (0x04000000U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_3_DISABLE                                           (0U)
#define CAL_CSI2_VC_IRQENABLE_LS_IRQ_3_ENABLE                                            (1U)

#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_3_SHIFT                                            (27U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_3_MASK                                             (0x08000000U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_3_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_LE_IRQ_3_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_3_SHIFT                                            (28U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_3_MASK                                             (0x10000000U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_3_ENABLE                                            (1U)
#define CAL_CSI2_VC_IRQENABLE_CS_IRQ_3_DISABLE                                           (0U)

#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_3_SHIFT                               (29U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_3_MASK                                (0x20000000U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_3_DISABLE                              (0U)
#define CAL_CSI2_VC_IRQENABLE_ECC_CORRECTION0_IRQ_3_ENABLE                               (1U)

#define CAL_CSI2_VC_IRQENABLE_RESERVED3_SHIFT                                           (30U)
#define CAL_CSI2_VC_IRQENABLE_RESERVED3_MASK                                            (0xc0000000U)

#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_0_SHIFT                                            (1U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_0_MASK                                             (0x00000002U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_0_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_0_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_0_SHIFT                                            (2U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_0_MASK                                             (0x00000004U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_0_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_0_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_0_SHIFT                                            (0U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_0_MASK                                             (0x00000001U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_0_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_0_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_0_SHIFT                                            (3U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_0_MASK                                             (0x00000008U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_0_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_0_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_0_SHIFT                                            (4U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_0_MASK                                             (0x00000010U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_0_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_0_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_0_SHIFT                                (5U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_0_MASK                                 (0x00000020U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_0_TRUE                                  (1U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_0_FALSE                                 (0U)

#define CAL_CSI2_VC_IRQSTATUS_RESERVED_SHIFT                                            (6U)
#define CAL_CSI2_VC_IRQSTATUS_RESERVED_MASK                                             (0x000000c0U)

#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_1_SHIFT                                            (8U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_1_MASK                                             (0x00000100U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_1_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_1_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_1_SHIFT                                            (9U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_1_MASK                                             (0x00000200U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_1_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_1_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_1_SHIFT                                            (10U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_1_MASK                                             (0x00000400U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_1_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_1_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_1_SHIFT                                            (11U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_1_MASK                                             (0x00000800U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_1_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_1_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_1_SHIFT                                            (12U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_1_MASK                                             (0x00001000U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_1_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_1_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_1_SHIFT                                (13U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_1_MASK                                 (0x00002000U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_1_TRUE                                  (1U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_1_FALSE                                 (0U)

#define CAL_CSI2_VC_IRQSTATUS_RESERVED1_SHIFT                                           (14U)
#define CAL_CSI2_VC_IRQSTATUS_RESERVED1_MASK                                            (0x0000c000U)

#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_2_SHIFT                                            (16U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_2_MASK                                             (0x00010000U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_2_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_2_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_2_SHIFT                                            (17U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_2_MASK                                             (0x00020000U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_2_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_2_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_2_SHIFT                                            (18U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_2_MASK                                             (0x00040000U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_2_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_2_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_2_SHIFT                                            (19U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_2_MASK                                             (0x00080000U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_2_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_2_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_2_SHIFT                                            (20U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_2_MASK                                             (0x00100000U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_2_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_2_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_2_SHIFT                                (21U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_2_MASK                                 (0x00200000U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_2_TRUE                                  (1U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_2_FALSE                                 (0U)

#define CAL_CSI2_VC_IRQSTATUS_RESERVED2_SHIFT                                           (22U)
#define CAL_CSI2_VC_IRQSTATUS_RESERVED2_MASK                                            (0x00c00000U)

#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_3_SHIFT                                            (24U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_3_MASK                                             (0x01000000U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_3_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_FS_IRQ_3_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_3_SHIFT                                            (25U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_3_MASK                                             (0x02000000U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_3_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_FE_IRQ_3_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_3_SHIFT                                            (26U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_3_MASK                                             (0x04000000U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_3_TRUE                                              (1U)
#define CAL_CSI2_VC_IRQSTATUS_LS_IRQ_3_FALSE                                             (0U)

#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_3_SHIFT                                            (27U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_3_MASK                                             (0x08000000U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_3_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_LE_IRQ_3_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_3_SHIFT                                            (28U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_3_MASK                                             (0x10000000U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_3_FALSE                                             (0U)
#define CAL_CSI2_VC_IRQSTATUS_CS_IRQ_3_TRUE                                              (1U)

#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_3_SHIFT                                (29U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_3_MASK                                 (0x20000000U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_3_TRUE                                  (1U)
#define CAL_CSI2_VC_IRQSTATUS_ECC_CORRECTION_IRQ_3_FALSE                                 (0U)

#define CAL_CSI2_VC_IRQSTATUS_RESERVED3_SHIFT                                           (30U)
#define CAL_CSI2_VC_IRQSTATUS_RESERVED3_MASK                                            (0xc0000000U)

#define CAL_CSI2_CTX0_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX0_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX0_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX0_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX0_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX0_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX0_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX0_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX0_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX0_ATT                                                                (1U)

#define CAL_CSI2_CTX0_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX0_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX0_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX0_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX0_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX0_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX0_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX0_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX0_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX0_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX1_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX1_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX1_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX1_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX1_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX1_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX1_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX1_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX1_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX1_ATT                                                                (1U)

#define CAL_CSI2_CTX1_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX1_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX1_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX1_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX1_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX1_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX1_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX1_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX1_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX1_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX2_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX2_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX2_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX2_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX2_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX2_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX2_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX2_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX2_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX2_ATT                                                                (1U)

#define CAL_CSI2_CTX2_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX2_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX2_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX2_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX2_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX2_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX2_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX2_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX2_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX2_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX3_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX3_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX3_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX3_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX3_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX3_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX3_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX3_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX3_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX3_ATT                                                                (1U)

#define CAL_CSI2_CTX3_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX3_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX3_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX3_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX3_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX3_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX3_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX3_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX3_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX3_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX4_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX4_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX4_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX4_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX4_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX4_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX4_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX4_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX4_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX4_ATT                                                                (1U)

#define CAL_CSI2_CTX4_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX4_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX4_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX4_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX4_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX4_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX4_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX4_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX4_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX4_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX5_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX5_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX5_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX5_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX5_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX5_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX5_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX5_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX5_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX5_ATT                                                                (1U)

#define CAL_CSI2_CTX5_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX5_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX5_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX5_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX5_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX5_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX5_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX5_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX5_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX5_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX6_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX6_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX6_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX6_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX6_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX6_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX6_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX6_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX6_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX6_ATT                                                                (1U)

#define CAL_CSI2_CTX6_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX6_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX6_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX6_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX6_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX6_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX6_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX6_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX6_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX6_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_CTX7_CPORT_SHIFT                                                       (8U)
#define CAL_CSI2_CTX7_CPORT_MASK                                                        (0x00001f00U)

#define CAL_CSI2_CTX7_DT_SHIFT                                                          (0U)
#define CAL_CSI2_CTX7_DT_MASK                                                           (0x0000003fU)

#define CAL_CSI2_CTX7_VC_SHIFT                                                          (6U)
#define CAL_CSI2_CTX7_VC_MASK                                                           (0x000000c0U)

#define CAL_CSI2_CTX7_ATT_SHIFT                                                         (13U)
#define CAL_CSI2_CTX7_ATT_MASK                                                          (0x00002000U)
#define CAL_CSI2_CTX7_ATT_PIX                                                            (0U)
#define CAL_CSI2_CTX7_ATT                                                                (1U)

#define CAL_CSI2_CTX7_LINES_SHIFT                                                       (16U)
#define CAL_CSI2_CTX7_LINES_MASK                                                        (0x3fff0000U)

#define CAL_CSI2_CTX7_RESERVED1_SHIFT                                                   (30U)
#define CAL_CSI2_CTX7_RESERVED1_MASK                                                    (0xc0000000U)

#define CAL_CSI2_CTX7_PACK_MODE_SHIFT                                                   (14U)
#define CAL_CSI2_CTX7_PACK_MODE_MASK                                                    (0x00004000U)
#define CAL_CSI2_CTX7_PACK_MODE_LINE                                                     (0U)
#define CAL_CSI2_CTX7_PACK_MODE_FRAME                                                    (1U)

#define CAL_CSI2_CTX7_RESERVED_SHIFT                                                    (15U)
#define CAL_CSI2_CTX7_RESERVED_MASK                                                     (0x00008000U)

#define CAL_CSI2_STATUS0_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS0_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS0_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS0_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS1_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS1_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS1_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS1_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS2_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS2_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS2_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS2_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS3_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS3_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS3_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS3_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS4_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS4_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS4_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS4_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS5_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS5_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS5_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS5_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS6_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS6_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS6_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS6_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_CSI2_STATUS7_FRAME_SHIFT                                                    (0U)
#define CAL_CSI2_STATUS7_FRAME_MASK                                                     (0x0000ffffU)

#define CAL_CSI2_STATUS7_RESERVED_SHIFT                                                 (16U)
#define CAL_CSI2_STATUS7_RESERVED_MASK                                                  (0xffff0000U)

#define CAL_WR_DMA_CTRL_YSIZE_SHIFT                                                     (18U)
#define CAL_WR_DMA_CTRL_YSIZE_MASK                                                      (0xfffc0000U)

#define CAL_WR_DMA_CTRL_STALL_RD_DMA_SHIFT                                              (14U)
#define CAL_WR_DMA_CTRL_STALL_RD_DMA_MASK                                               (0x00004000U)

#define CAL_WR_DMA_CTRL_CPORT_SHIFT                                                     (9U)
#define CAL_WR_DMA_CTRL_CPORT_MASK                                                      (0x00003E00U)

#define CAL_WR_DMA_CTRL_DTAG_SHIFT                                                      (6U)
#define CAL_WR_DMA_CTRL_DTAG_MASK                                                       (0x000001C0U)

#define CAL_WR_DMA_CTRL_WR_PATTERN_SHIFT                                                (3U)
#define CAL_WR_DMA_CTRL_WR_PATTERN_MASK                                                 (0x00000018U)

#define CAL_WR_DMA_CTRL_MODE_MASK                                                       (0x00000007U)

#define CAL_WR_DMA_ADRR_ADDR_SHIFT                                                      (4U)
#define CAL_WR_DMA_ADRR_ADDR_MASK                                                       (0xFFFFFFF0U)

#define CAL_WR_DMA_OFST_OFFST_SHIFT                                                     (4U)
#define CAL_WR_DMA_OFST_OFFST_MASK                                                      (0x0007FFF8U)
#define CAL_WR_DMA_OFST_CIRC_SIZE_MASK                                                  (0xFF000000U)
#define CAL_WR_DMA_OFST_CIRC_MODE_MASK                                                  (0x00C00000U)

#define CAL_WR_DMA_XSIZE_XSIZE_SHIFT                                                    (19U)
#define CAL_WR_DMA_XSIZE_XSIZE_MASK                                                     (0xFFF80000U)

#define CAL_WR_DMA_XSIZE_XSKIP_SHIFT                                                    (3U)
#define CAL_WR_DMA_XSIZE_XSKIP_MASK                                                     (0x0000FFF8U)

#define CAL_CSI2_PHY_REG0_HSCLOCKCONFIG_SHIFT                                           (24U)
#define CAL_CSI2_PHY_REG0_HSCLOCKCONFIG_MASK                                            (0x01000000U)

#define CAL_CSI2_PHY_REG0_THS_TERM_SHIFT                                                (8U)
#define CAL_CSI2_PHY_REG0_THS_TERM_MASK                                                 (0x0000FF00U)

#define CAL_CSI2_PHY_REG0_THS_SETTLE_SHIFT                                              (0U)
#define CAL_CSI2_PHY_REG0_THS_SETTLE_MASK                                               (0x000000FFU)

#define CAL_CSI2_PHY_REG1_TCLK_TERM_MASK                        (0x01FC0000U)
#define CAL_CSI2_PHY_REG1_TCLK_TERM_SHIFT                       (0x18U)
#define CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK                      (0x000000FFU)
#define CAL_CSI2_PHY_REG1_TCLK_SETTLE_SHIFT                     (0x0U)

#define CAL_CSI2_PHY_REG10_LDO_DISABLE_MASK                     (0x00000040U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CAL_H_ */

