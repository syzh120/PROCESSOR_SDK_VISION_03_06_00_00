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

#ifndef HW_ISS_REGS_H_
#define HW_ISS_REGS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ISS_HL_REVISION                                             (0x0U)
#define ISS_HL_HWINFO                                               (0x4U)
#define ISS_HL_SYSCONFIG                                            (0x10U)
#define ISS_HL_IRQ_EOI                                              (0x1cU)
#define ISS_HL_IRQSTATUS_RAW(m)                                     (0x20U + ((m) * (uint32_t)0x10))
#define ISS_HL_IRQSTATUS(m)                                         (0x24U + ((m) * (uint32_t)0x10))
#define ISS_HL_IRQENABLE_SET(m)                                     (0x28U + ((m) * (uint32_t)0x10))
#define ISS_HL_IRQENABLE_CLR(m)                                     (0x2cU + ((m) * (uint32_t)0x10))
#define ISS_CTRL                                                    (0x080U)
#define ISS_CLKCTRL                                                 (0x084U)
#define ISS_CLKSTAT                                                 (0x088U)
#define ISS_PM_STATUS                                               (0x08cU)
#define ISS_BYS                                                     (0x090U)
#define ISS_CTRL1                                                   (0x094U)
#define ISS_VMUX                                                    (0x098U)
#define ISS_ROUTE1                                                  (0x09cU)
#define ISS_ROUTE2                                                  (0x0a0U)
#define ISS_ROUTE3                                                  (0x0a4U)
#define ISS_EMU_OUT                                                 (0x0a8U)
#define ISS_VMUX_RESET                                              (0x0acU)
#define ISS_VMUX_IRQSTATUS_RAW                                      (0x0b0U)
#define ISS_VMUX_IRQSTATUS                                          (0x0b4U)
#define ISS_VMUX_IRQENABLE_SET                                      (0x0b8U)
#define ISS_VMUX_IRQENABLE_CLR                                      (0x0bcU)
#define TCTRL_REVISION                                              (0x0c0U)
#define TCTRL_SYSCONFIG                                             (0x0c4U)
#define TCTRL_SYSSTATUS                                             (0x0c8U)
#define TCTRL_STRB_LENGTH                                           (0x0d0U)
#define TCTRL_PSTRB_LENGTH                                          (0x0d4U)
#define TCTRL_SHUT_LENGTH                                           (0x0d8U)
#define TCTRL_GRESET_LENGTH                                         (0x0dcU)
#define TCTRL_STRB_DELAY                                            (0x0e0U)
#define TCTRL_PSTRB_DELAY                                           (0x0e4U)
#define TCTRL_SHUT_DELAY                                            (0x0e8U)
#define TCTRL_CTRL                                                  (0x0f0U)
#define TCTRL_PSTRB_REPLAY                                          (0x0f4U)
#define TCTRL_FRAME                                                 (0x0f8U)
#define ISS_ICM_A_TC(m)                                             (0x100U + ((m) * 0x4U))
#define ISS_ICM_A_CME(m)                                            (0x180U + ((m) * 0x4U))
#define ISS_ICM_B_TC(m)                                             (0x200U + ((m) * 0x4U))
#define ISS_REQINFO_MAP0_7                                          (0x300U)
#define ISS_REQINFO_MAP8_15                                         (0x304U)
#define ISS_REQINFO_MAP16_23                                        (0x308U)
#define ISS_REQINFO_MAP24_31                                        (0x30cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISS_HL_REVISION_Y_MINOR_SHIFT                                                   (0U)
#define ISS_HL_REVISION_Y_MINOR_MASK                                                    (0x0000003fU)

#define ISS_HL_REVISION_CUSTOM_SHIFT                                                    (6U)
#define ISS_HL_REVISION_CUSTOM_MASK                                                     (0x000000c0U)
#define ISS_HL_REVISION_CUSTOM_STANDARD                                                  (0U)

#define ISS_HL_REVISION_X_MAJOR_SHIFT                                                   (8U)
#define ISS_HL_REVISION_X_MAJOR_MASK                                                    (0x00000700U)

#define ISS_HL_REVISION_R_RTL_SHIFT                                                     (11U)
#define ISS_HL_REVISION_R_RTL_MASK                                                      (0x0000f800U)

#define ISS_HL_REVISION_FUNC_SHIFT                                                      (16U)
#define ISS_HL_REVISION_FUNC_MASK                                                       (0x0fff0000U)

#define ISS_HL_REVISION_SCHEME_SHIFT                                                    (30U)
#define ISS_HL_REVISION_SCHEME_MASK                                                     (0xc0000000U)
#define ISS_HL_REVISION_SCHEME_H08                                                       (1U)
#define ISS_HL_REVISION_SCHEME_LEGACY                                                    (0U)

#define ISS_HL_REVISION_RESERVED_SHIFT                                                  (28U)
#define ISS_HL_REVISION_RESERVED_MASK                                                   (0x30000000U)

#define ISS_HL_HWINFO_BRIDGE_BUFF_SHIFT                                                 (0U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_MASK                                                  (0x00000007U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_S8                                                     (0U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_S16                                                    (1U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_S32                                                    (2U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_S64                                                    (3U)
#define ISS_HL_HWINFO_BRIDGE_BUFF_S128                                                   (4U)

#define ISS_HL_HWINFO_RESERVED_SHIFT                                                    (3U)
#define ISS_HL_HWINFO_RESERVED_MASK                                                     (0xfffffff8U)

#define ISS_HL_SYSCONFIG_SOFTRESET_SHIFT                                                (0U)
#define ISS_HL_SYSCONFIG_SOFTRESET_MASK                                                 (0x00000001U)
#define ISS_HL_SYSCONFIG_SOFTRESET_DONE                                                  (0U)
#define ISS_HL_SYSCONFIG_SOFTRESET_PENDING                                               (1U)
#define ISS_HL_SYSCONFIG_SOFTRESET_NOACTION                                              (0U)
#define ISS_HL_SYSCONFIG_SOFTRESET_RESET                                                 (1U)

#define ISS_HL_SYSCONFIG_IDLEMODE_SHIFT                                                 (2U)
#define ISS_HL_SYSCONFIG_IDLEMODE_MASK                                                  (0x0000000cU)
#define ISS_HL_SYSCONFIG_IDLEMODE_FORCE                                                  (0U)
#define ISS_HL_SYSCONFIG_IDLEMODE_NO                                                     (1U)
#define ISS_HL_SYSCONFIG_IDLEMODE_SMART1                                                 (2U)
#define ISS_HL_SYSCONFIG_IDLEMODE_SMART2                                                 (3U)

#define ISS_HL_SYSCONFIG_STANDBYMODE_SHIFT                                              (4U)
#define ISS_HL_SYSCONFIG_STANDBYMODE_MASK                                               (0x00000030U)
#define ISS_HL_SYSCONFIG_STANDBYMODE_FORCE                                               (0U)
#define ISS_HL_SYSCONFIG_STANDBYMODE_NO                                                  (1U)
#define ISS_HL_SYSCONFIG_STANDBYMODE_SMART1                                              (2U)
#define ISS_HL_SYSCONFIG_STANDBYMODE_SMART2                                              (3U)

#define ISS_HL_SYSCONFIG_RESERVED_SHIFT                                                 (1U)
#define ISS_HL_SYSCONFIG_RESERVED_MASK                                                  (0x00000002U)

#define ISS_HL_SYSCONFIG_RESERVED1_SHIFT                                                (6U)
#define ISS_HL_SYSCONFIG_RESERVED1_MASK                                                 (0xffffffc0U)

#define ISS_HL_IRQ_EOI_LINE_NUMBER_SHIFT                                                (0U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_MASK                                                 (0x00000007U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_READ0                                                 (0U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI0                                                  (0U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI1                                                  (1U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI2                                                  (2U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI3                                                  (3U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI4                                                  (4U)
#define ISS_HL_IRQ_EOI_LINE_NUMBER_EOI5                                                  (5U)

#define ISS_HL_IRQ_EOI_RESERVED_SHIFT                                                   (3U)
#define ISS_HL_IRQ_EOI_RESERVED_MASK                                                    (0xfffffff8U)

#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ0_SHIFT                                             (0U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ0_MASK                                              (0x00000001U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ0_NOEVENT                                            (0U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ0_PENDING                                            (1U)

#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ1_SHIFT                                             (1U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ1_MASK                                              (0x00000002U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ1_NOEVENT                                            (0U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ1_PENDING                                            (1U)

#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ2_SHIFT                                             (2U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ2_MASK                                              (0x00000004U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ2_NOEVENT                                            (0U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ2_PENDING                                            (1U)

#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ3_SHIFT                                             (3U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ3_MASK                                              (0x00000008U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ3_NOEVENT                                            (0U)
#define ISS_HL_IRQSTATUS_RAW_ISP_IRQ3_PENDING                                            (1U)

#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ0_SHIFT                                            (6U)
#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ0_MASK                                             (0x00000040U)

#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ1_SHIFT                                            (7U)
#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ1_MASK                                             (0x00000080U)

#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ2_SHIFT                                            (8U)
#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ2_MASK                                             (0x00000100U)

#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ3_SHIFT                                            (9U)
#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ3_MASK                                             (0x00000200U)

#define ISS_HL_IRQSTATUS_RAW_CBUFF_IRQ_SHIFT                                            (10U)
#define ISS_HL_IRQSTATUS_RAW_CBUFF_IRQ_MASK                                             (0x00000400U)

#define ISS_HL_IRQSTATUS_RAW_BTE_IRQ_SHIFT                                              (11U)
#define ISS_HL_IRQSTATUS_RAW_BTE_IRQ_MASK                                               (0x00000800U)

#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ0_SHIFT                                          (12U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ0_MASK                                           (0x00001000U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ0_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ0_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ1_SHIFT                                          (13U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ1_MASK                                           (0x00002000U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ1_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ1_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ2_SHIFT                                          (14U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ2_MASK                                           (0x00004000U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ2_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ2_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ3_SHIFT                                          (15U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ3_MASK                                           (0x00008000U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ3_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_SIMCOP_IRQ3_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_SHIFT                                            (17U)
#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_MASK                                             (0x00020000U)
#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_NOACTION                                          (0U)
#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_SET                                               (1U)
#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_NOEVENT                                           (0U)
#define ISS_HL_IRQSTATUS_RAW_HS_VS_IRQ_PENDING                                           (1U)

#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ8_SHIFT                                            (16U)
#define ISS_HL_IRQSTATUS_RAW_CCP2_IRQ8_MASK                                             (0x00010000U)

#define ISS_HL_IRQSTATUS_RAW_BYS_A_IRQ_SHIFT                                            (18U)
#define ISS_HL_IRQSTATUS_RAW_BYS_A_IRQ_MASK                                             (0x00040000U)

#define ISS_HL_IRQSTATUS_RAW_BYS_B_IRQ_SHIFT                                            (20U)
#define ISS_HL_IRQSTATUS_RAW_BYS_B_IRQ_MASK                                             (0x00100000U)

#define ISS_HL_IRQSTATUS_RAW_CAL_A_IRQ_SHIFT                                            (22U)
#define ISS_HL_IRQSTATUS_RAW_CAL_A_IRQ_MASK                                             (0x00400000U)
#define ISS_HL_IRQSTATUS_RAW_CAL_A_IRQ_NOEVENT                                           (0U)
#define ISS_HL_IRQSTATUS_RAW_CAL_A_IRQ_PENDING                                           (1U)

#define ISS_HL_IRQSTATUS_RAW_CAL_B_IRQ_SHIFT                                            (23U)
#define ISS_HL_IRQSTATUS_RAW_CAL_B_IRQ_MASK                                             (0x00800000U)

#define ISS_HL_IRQSTATUS_RAW_ICM_A_IRQ_SHIFT                                            (25U)
#define ISS_HL_IRQSTATUS_RAW_ICM_A_IRQ_MASK                                             (0x02000000U)

#define ISS_HL_IRQSTATUS_RAW_LVDSRX0_IRQ_SHIFT                                          (26U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX0_IRQ_MASK                                           (0x04000000U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX0_IRQ_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX0_IRQ_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_ICM_B_IRQ_SHIFT                                            (24U)
#define ISS_HL_IRQSTATUS_RAW_ICM_B_IRQ_MASK                                             (0x01000000U)

#define ISS_HL_IRQSTATUS_RAW_RESERVED1_SHIFT                                            (4U)
#define ISS_HL_IRQSTATUS_RAW_RESERVED1_MASK                                             (0x00000030U)

#define ISS_HL_IRQSTATUS_RAW_RESERVED3_SHIFT                                            (21U)
#define ISS_HL_IRQSTATUS_RAW_RESERVED3_MASK                                             (0x00200000U)

#define ISS_HL_IRQSTATUS_RAW_LVDSRX1_IRQ_SHIFT                                          (27U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX1_IRQ_MASK                                           (0x08000000U)

#define ISS_HL_IRQSTATUS_RAW_LVDSRX2_IRQ_SHIFT                                          (28U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX2_IRQ_MASK                                           (0x10000000U)

#define ISS_HL_IRQSTATUS_RAW_LVDSRX3_IRQ_SHIFT                                          (29U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX3_IRQ_MASK                                           (0x20000000U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX3_IRQ_NOEVENT                                         (0U)
#define ISS_HL_IRQSTATUS_RAW_LVDSRX3_IRQ_PENDING                                         (1U)

#define ISS_HL_IRQSTATUS_RAW_RESERVED_SHIFT                                             (30U)
#define ISS_HL_IRQSTATUS_RAW_RESERVED_MASK                                              (0xc0000000U)

#define ISS_HL_IRQSTATUS_RAW_VMUX_IRQ_SHIFT                                             (19U)
#define ISS_HL_IRQSTATUS_RAW_VMUX_IRQ_MASK                                              (0x00080000U)
#define ISS_HL_IRQSTATUS_RAW_VMUX_IRQ_NOEVENT                                            (0U)
#define ISS_HL_IRQSTATUS_RAW_VMUX_IRQ_PENDING                                            (1U)

#define ISS_HL_IRQSTATUS_HS_VS_IRQ_SHIFT                                                (17U)
#define ISS_HL_IRQSTATUS_HS_VS_IRQ_MASK                                                 (0x00020000U)
#define ISS_HL_IRQSTATUS_HS_VS_IRQ_NOACTION                                              (0U)
#define ISS_HL_IRQSTATUS_HS_VS_IRQ_CLEAR                                                 (1U)
#define ISS_HL_IRQSTATUS_HS_VS_IRQ_NOEVENT                                               (0U)
#define ISS_HL_IRQSTATUS_HS_VS_IRQ_PENDING                                               (1U)

#define ISS_HL_IRQSTATUS_ISP_IRQ0_SHIFT                                                 (0U)
#define ISS_HL_IRQSTATUS_ISP_IRQ0_MASK                                                  (0x00000001U)
#define ISS_HL_IRQSTATUS_ISP_IRQ0_NOEVENT                                                (0U)
#define ISS_HL_IRQSTATUS_ISP_IRQ0_PENDING                                                (1U)

#define ISS_HL_IRQSTATUS_ISP_IRQ1_SHIFT                                                 (1U)
#define ISS_HL_IRQSTATUS_ISP_IRQ1_MASK                                                  (0x00000002U)
#define ISS_HL_IRQSTATUS_ISP_IRQ1_NOEVENT                                                (0U)
#define ISS_HL_IRQSTATUS_ISP_IRQ1_PENDING                                                (1U)

#define ISS_HL_IRQSTATUS_ISP_IRQ2_SHIFT                                                 (2U)
#define ISS_HL_IRQSTATUS_ISP_IRQ2_MASK                                                  (0x00000004U)
#define ISS_HL_IRQSTATUS_ISP_IRQ2_NOEVENT                                                (0U)
#define ISS_HL_IRQSTATUS_ISP_IRQ2_PENDING                                                (1U)

#define ISS_HL_IRQSTATUS_ISP_IRQ3_SHIFT                                                 (3U)
#define ISS_HL_IRQSTATUS_ISP_IRQ3_MASK                                                  (0x00000008U)
#define ISS_HL_IRQSTATUS_ISP_IRQ3_NOEVENT                                                (0U)
#define ISS_HL_IRQSTATUS_ISP_IRQ3_PENDING                                                (1U)

#define ISS_HL_IRQSTATUS_CCP2_IRQ0_SHIFT                                                (6U)
#define ISS_HL_IRQSTATUS_CCP2_IRQ0_MASK                                                 (0x00000040U)

#define ISS_HL_IRQSTATUS_CCP2_IRQ1_SHIFT                                                (7U)
#define ISS_HL_IRQSTATUS_CCP2_IRQ1_MASK                                                 (0x00000080U)

#define ISS_HL_IRQSTATUS_CCP2_IRQ2_SHIFT                                                (8U)
#define ISS_HL_IRQSTATUS_CCP2_IRQ2_MASK                                                 (0x00000100U)

#define ISS_HL_IRQSTATUS_CCP2_IRQ3_SHIFT                                                (9U)
#define ISS_HL_IRQSTATUS_CCP2_IRQ3_MASK                                                 (0x00000200U)

#define ISS_HL_IRQSTATUS_CBUFF_IRQ_SHIFT                                                (10U)
#define ISS_HL_IRQSTATUS_CBUFF_IRQ_MASK                                                 (0x00000400U)

#define ISS_HL_IRQSTATUS_BTE_IRQ_SHIFT                                                  (11U)
#define ISS_HL_IRQSTATUS_BTE_IRQ_MASK                                                   (0x00000800U)

#define ISS_HL_IRQSTATUS_SIMCOP_IRQ0_SHIFT                                              (12U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ0_MASK                                               (0x00001000U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ0_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ0_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_SIMCOP_IRQ1_SHIFT                                              (13U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ1_MASK                                               (0x00002000U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ1_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ1_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_SIMCOP_IRQ2_SHIFT                                              (14U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ2_MASK                                               (0x00004000U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ2_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ2_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_SIMCOP_IRQ3_SHIFT                                              (15U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ3_MASK                                               (0x00008000U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ3_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_SIMCOP_IRQ3_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_CCP2_IRQ8_SHIFT                                                (16U)
#define ISS_HL_IRQSTATUS_CCP2_IRQ8_MASK                                                 (0x00010000U)

#define ISS_HL_IRQSTATUS_BYS_A_IRQ_SHIFT                                                (18U)
#define ISS_HL_IRQSTATUS_BYS_A_IRQ_MASK                                                 (0x00040000U)

#define ISS_HL_IRQSTATUS_BYS_B_IRQ_SHIFT                                                (20U)
#define ISS_HL_IRQSTATUS_BYS_B_IRQ_MASK                                                 (0x00100000U)

#define ISS_HL_IRQSTATUS_CAL_A_IRQ_SHIFT                                                (22U)
#define ISS_HL_IRQSTATUS_CAL_A_IRQ_MASK                                                 (0x00400000U)
#define ISS_HL_IRQSTATUS_CAL_A_IRQ_NOEVENT                                               (0U)
#define ISS_HL_IRQSTATUS_CAL_A_IRQ_PENDING                                               (1U)

#define ISS_HL_IRQSTATUS_CAL_B_IRQ_SHIFT                                                (23U)
#define ISS_HL_IRQSTATUS_CAL_B_IRQ_MASK                                                 (0x00800000U)

#define ISS_HL_IRQSTATUS_ICM_A_IRQ_SHIFT                                                (25U)
#define ISS_HL_IRQSTATUS_ICM_A_IRQ_MASK                                                 (0x02000000U)

#define ISS_HL_IRQSTATUS_LVDSRX0_IRQ_SHIFT                                              (26U)
#define ISS_HL_IRQSTATUS_LVDSRX0_IRQ_MASK                                               (0x04000000U)
#define ISS_HL_IRQSTATUS_LVDSRX0_IRQ_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_LVDSRX0_IRQ_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_ICM_B_IRQ_SHIFT                                                (24U)
#define ISS_HL_IRQSTATUS_ICM_B_IRQ_MASK                                                 (0x01000000U)

#define ISS_HL_IRQSTATUS_RESERVED1_SHIFT                                                (4U)
#define ISS_HL_IRQSTATUS_RESERVED1_MASK                                                 (0x00000030U)

#define ISS_HL_IRQSTATUS_RESERVED3_SHIFT                                                (21U)
#define ISS_HL_IRQSTATUS_RESERVED3_MASK                                                 (0x00200000U)

#define ISS_HL_IRQSTATUS_LVDSRX1_IRQ_SHIFT                                              (27U)
#define ISS_HL_IRQSTATUS_LVDSRX1_IRQ_MASK                                               (0x08000000U)

#define ISS_HL_IRQSTATUS_LVDSRX2_IRQ_SHIFT                                              (28U)
#define ISS_HL_IRQSTATUS_LVDSRX2_IRQ_MASK                                               (0x10000000U)

#define ISS_HL_IRQSTATUS_LVDSRX3_IRQ_SHIFT                                              (29U)
#define ISS_HL_IRQSTATUS_LVDSRX3_IRQ_MASK                                               (0x20000000U)
#define ISS_HL_IRQSTATUS_LVDSRX3_IRQ_NOEVENT                                             (0U)
#define ISS_HL_IRQSTATUS_LVDSRX3_IRQ_PENDING                                             (1U)

#define ISS_HL_IRQSTATUS_RESERVED_SHIFT                                                 (30U)
#define ISS_HL_IRQSTATUS_RESERVED_MASK                                                  (0xc0000000U)

#define ISS_HL_IRQSTATUS_VMUX_IRQ_SHIFT                                                 (19U)
#define ISS_HL_IRQSTATUS_VMUX_IRQ_MASK                                                  (0x00080000U)
#define ISS_HL_IRQSTATUS_VMUX_IRQ_NOEVENT                                                (0U)
#define ISS_HL_IRQSTATUS_VMUX_IRQ_PENDING                                                (1U)

#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_SHIFT                                             (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_MASK                                              (0x00000001U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_ENABLE                                             (1U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ0_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_SHIFT                                             (1U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_MASK                                              (0x00000002U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_ENABLE                                             (1U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ1_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_SHIFT                                             (2U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_MASK                                              (0x00000004U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_ENABLE                                             (1U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ2_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_SHIFT                                             (3U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_MASK                                              (0x00000008U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_ENABLE                                             (1U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_SET_ISP_IRQ3_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_SET_CCP2_IRQ0_SHIFT                                            (6U)
#define ISS_HL_IRQENABLE_SET_CCP2_IRQ0_MASK                                             (0x00000040U)

#define ISS_HL_IRQENABLE_SET_CCP2_IRQ1_SHIFT                                            (7U)
#define ISS_HL_IRQENABLE_SET_CCP2_IRQ1_MASK                                             (0x00000080U)

#define ISS_HL_IRQENABLE_SET_CCP2_IRQ2_SHIFT                                            (8U)
#define ISS_HL_IRQENABLE_SET_CCP2_IRQ2_MASK                                             (0x00000100U)

#define ISS_HL_IRQENABLE_SET_CCP2_IRQ3_SHIFT                                            (9U)
#define ISS_HL_IRQENABLE_SET_CCP2_IRQ3_MASK                                             (0x00000200U)

#define ISS_HL_IRQENABLE_SET_CBUFF_IRQ_SHIFT                                            (10U)
#define ISS_HL_IRQENABLE_SET_CBUFF_IRQ_MASK                                             (0x00000400U)

#define ISS_HL_IRQENABLE_SET_BTE_IRQ_SHIFT                                              (11U)
#define ISS_HL_IRQENABLE_SET_BTE_IRQ_MASK                                               (0x00000800U)

#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_SHIFT                                          (12U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_MASK                                           (0x00001000U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ0_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_SHIFT                                          (13U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_MASK                                           (0x00002000U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ1_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_SHIFT                                          (14U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_MASK                                           (0x00004000U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ2_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_SHIFT                                          (15U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_MASK                                           (0x00008000U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_SIMCOP_IRQ3_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_SHIFT                                            (17U)
#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_MASK                                             (0x00020000U)
#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_NOACTION                                          (0U)
#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_ENABLE                                            (1U)
#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_DISABLED                                          (0U)
#define ISS_HL_IRQENABLE_SET_HS_VS_IRQ_ENABLED                                           (1U)

#define ISS_HL_IRQENABLE_SET_CCP2_IRQ8_SHIFT                                            (16U)
#define ISS_HL_IRQENABLE_SET_CCP2_IRQ8_MASK                                             (0x00010000U)

#define ISS_HL_IRQENABLE_SET_BYS_A_IRQ_SHIFT                                            (18U)
#define ISS_HL_IRQENABLE_SET_BYS_A_IRQ_MASK                                             (0x00040000U)

#define ISS_HL_IRQENABLE_SET_BYS_B_IRQ_SHIFT                                            (20U)
#define ISS_HL_IRQENABLE_SET_BYS_B_IRQ_MASK                                             (0x00100000U)

#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_SHIFT                                            (22U)
#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_MASK                                             (0x00400000U)
#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_NOACTION                                          (0U)
#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_ENABLE                                            (1U)
#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_DISABLED                                          (0U)
#define ISS_HL_IRQENABLE_SET_CAL_A_IRQ_ENABLED                                           (1U)

#define ISS_HL_IRQENABLE_SET_CAL_B_IRQ_SHIFT                                            (23U)
#define ISS_HL_IRQENABLE_SET_CAL_B_IRQ_MASK                                             (0x00800000U)

#define ISS_HL_IRQENABLE_SET_ICM_A_IRQ_SHIFT                                            (25U)
#define ISS_HL_IRQENABLE_SET_ICM_A_IRQ_MASK                                             (0x02000000U)

#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_SHIFT                                          (26U)
#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_MASK                                           (0x04000000U)
#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_LVDSRX0_IRQ_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_ICM_B_IRQ_SHIFT                                            (24U)
#define ISS_HL_IRQENABLE_SET_ICM_B_IRQ_MASK                                             (0x01000000U)

#define ISS_HL_IRQENABLE_SET_RESERVED1_SHIFT                                            (4U)
#define ISS_HL_IRQENABLE_SET_RESERVED1_MASK                                             (0x00000030U)

#define ISS_HL_IRQENABLE_SET_RESERVED3_SHIFT                                            (21U)
#define ISS_HL_IRQENABLE_SET_RESERVED3_MASK                                             (0x00200000U)

#define ISS_HL_IRQENABLE_SET_LVDSRX1_IRQ_SHIFT                                          (27U)
#define ISS_HL_IRQENABLE_SET_LVDSRX1_IRQ_MASK                                           (0x08000000U)

#define ISS_HL_IRQENABLE_SET_LVDSRX2_IRQ_SHIFT                                          (28U)
#define ISS_HL_IRQENABLE_SET_LVDSRX2_IRQ_MASK                                           (0x10000000U)

#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_SHIFT                                          (29U)
#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_MASK                                           (0x20000000U)
#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_ENABLE                                          (1U)
#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_SET_LVDSRX3_IRQ_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_SET_RESERVED_SHIFT                                             (30U)
#define ISS_HL_IRQENABLE_SET_RESERVED_MASK                                              (0xc0000000U)

#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_SHIFT                                             (19U)
#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_MASK                                              (0x00080000U)
#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_ENABLE                                             (1U)
#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_SET_VMUX_IRQ_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_SHIFT                                             (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_MASK                                              (0x00000001U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_DISABLE                                            (1U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ0_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_SHIFT                                             (1U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_MASK                                              (0x00000002U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_DISABLE                                            (1U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ1_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_SHIFT                                             (2U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_MASK                                              (0x00000004U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_DISABLE                                            (1U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ2_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_SHIFT                                             (3U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_MASK                                              (0x00000008U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_DISABLE                                            (1U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_CLR_ISP_IRQ3_ENABLED                                            (1U)

#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ0_SHIFT                                            (6U)
#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ0_MASK                                             (0x00000040U)

#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ1_SHIFT                                            (7U)
#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ1_MASK                                             (0x00000080U)

#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ2_SHIFT                                            (8U)
#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ2_MASK                                             (0x00000100U)

#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ3_SHIFT                                            (9U)
#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ3_MASK                                             (0x00000200U)

#define ISS_HL_IRQENABLE_CLR_CBUFF_IRQ_SHIFT                                            (10U)
#define ISS_HL_IRQENABLE_CLR_CBUFF_IRQ_MASK                                             (0x00000400U)

#define ISS_HL_IRQENABLE_CLR_BTE_IRQ_SHIFT                                              (11U)
#define ISS_HL_IRQENABLE_CLR_BTE_IRQ_MASK                                               (0x00000800U)

#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_SHIFT                                          (12U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_MASK                                           (0x00001000U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ0_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_SHIFT                                          (13U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_MASK                                           (0x00002000U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ1_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_SHIFT                                          (14U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_MASK                                           (0x00004000U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ2_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_SHIFT                                          (15U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_MASK                                           (0x00008000U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_SIMCOP_IRQ3_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_SHIFT                                            (17U)
#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_MASK                                             (0x00020000U)
#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_NOACTION                                          (0U)
#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_DISABLE                                           (1U)
#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_DISABLED                                          (0U)
#define ISS_HL_IRQENABLE_CLR_HS_VS_IRQ_ENABLED                                           (1U)

#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ8_SHIFT                                            (16U)
#define ISS_HL_IRQENABLE_CLR_CCP2_IRQ8_MASK                                             (0x00010000U)

#define ISS_HL_IRQENABLE_CLR_BYS_A_IRQ_SHIFT                                            (18U)
#define ISS_HL_IRQENABLE_CLR_BYS_A_IRQ_MASK                                             (0x00040000U)

#define ISS_HL_IRQENABLE_CLR_BYS_B_IRQ_SHIFT                                            (20U)
#define ISS_HL_IRQENABLE_CLR_BYS_B_IRQ_MASK                                             (0x00100000U)

#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_SHIFT                                            (22U)
#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_MASK                                             (0x00400000U)
#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_NOACTION                                          (0U)
#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_DISABLE                                           (1U)
#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_DISABLED                                          (0U)
#define ISS_HL_IRQENABLE_CLR_CAL_A_IRQ_ENABLED                                           (1U)

#define ISS_HL_IRQENABLE_CLR_CAL_B_IRQ_SHIFT                                            (23U)
#define ISS_HL_IRQENABLE_CLR_CAL_B_IRQ_MASK                                             (0x00800000U)

#define ISS_HL_IRQENABLE_CLR_ICM_A_IRQ_SHIFT                                            (25U)
#define ISS_HL_IRQENABLE_CLR_ICM_A_IRQ_MASK                                             (0x02000000U)

#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_SHIFT                                          (26U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_MASK                                           (0x04000000U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX0_IRQ_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_ICM_B_IRQ_SHIFT                                            (24U)
#define ISS_HL_IRQENABLE_CLR_ICM_B_IRQ_MASK                                             (0x01000000U)

#define ISS_HL_IRQENABLE_CLR_RESERVED1_SHIFT                                            (4U)
#define ISS_HL_IRQENABLE_CLR_RESERVED1_MASK                                             (0x00000030U)

#define ISS_HL_IRQENABLE_CLR_RESERVED3_SHIFT                                            (21U)
#define ISS_HL_IRQENABLE_CLR_RESERVED3_MASK                                             (0x00200000U)

#define ISS_HL_IRQENABLE_CLR_LVDSRX1_IRQ_SHIFT                                          (27U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX1_IRQ_MASK                                           (0x08000000U)

#define ISS_HL_IRQENABLE_CLR_LVDSRX2_IRQ_SHIFT                                          (28U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX2_IRQ_MASK                                           (0x10000000U)

#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_SHIFT                                          (29U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_MASK                                           (0x20000000U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_NOACTION                                        (0U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_DISABLE                                         (1U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_DISABLED                                        (0U)
#define ISS_HL_IRQENABLE_CLR_LVDSRX3_IRQ_ENABLED                                         (1U)

#define ISS_HL_IRQENABLE_CLR_RESERVED_SHIFT                                             (30U)
#define ISS_HL_IRQENABLE_CLR_RESERVED_MASK                                              (0xc0000000U)

#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_SHIFT                                             (19U)
#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_MASK                                              (0x00080000U)
#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_NOACTION                                           (0U)
#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_DISABLE                                            (1U)
#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_DISABLED                                           (0U)
#define ISS_HL_IRQENABLE_CLR_VMUX_IRQ_ENABLED                                            (1U)

#define ISS_CTRL_SYNC_DETECT_SHIFT                                                      (0U)
#define ISS_CTRL_SYNC_DETECT_MASK                                                       (0x00000003U)
#define ISS_CTRL_SYNC_DETECT_HSF                                                         (0U)
#define ISS_CTRL_SYNC_DETECT_HSR                                                         (1U)
#define ISS_CTRL_SYNC_DETECT_VSF                                                         (2U)
#define ISS_CTRL_SYNC_DETECT_VSR                                                         (3U)

#define ISS_CTRL_INPUT_SEL_SHIFT                                                        (2U)
#define ISS_CTRL_INPUT_SEL_MASK                                                         (0x0000000cU)
#define ISS_CTRL_INPUT_SEL_CCP2                                                          (2U)
#define ISS_CTRL_INPUT_SEL_PAR                                                           (3U)
#define ISS_CTRL_INPUT_SEL_RESERVED                                                      (0U)

#define ISS_CTRL_CCP2R_TAG_CNT_SHIFT                                                    (16U)
#define ISS_CTRL_CCP2R_TAG_CNT_MASK                                                     (0x000f0000U)

#define ISS_CTRL_CCP2W_TAG_CNT_SHIFT                                                    (20U)
#define ISS_CTRL_CCP2W_TAG_CNT_MASK                                                     (0x00f00000U)

#define ISS_CTRL_CLK_DIV_SHIFT                                                          (4U)
#define ISS_CTRL_CLK_DIV_MASK                                                           (0x00000030U)
#define ISS_CTRL_CLK_DIV_NONE                                                            (0U)
#define ISS_CTRL_CLK_DIV_DIV2                                                            (1U)
#define ISS_CTRL_CLK_DIV_DIV4                                                            (2U)
#define ISS_CTRL_CLK_DIV_RSZ                                                             (3U)

#define ISS_CTRL_INPUT_SEL2_SHIFT                                                       (6U)
#define ISS_CTRL_INPUT_SEL2_MASK                                                        (0x000000c0U)
#define ISS_CTRL_INPUT_SEL2_NONE                                                         (0U)
#define ISS_CTRL_INPUT_SEL2_CSI3_A                                                       (2U)
#define ISS_CTRL_INPUT_SEL2_RESERVED                                                     (1U)
#define ISS_CTRL_INPUT_SEL2_RESERVED1                                                    (3U)

#define ISS_CTRL_RESERVED_SHIFT                                                         (8U)
#define ISS_CTRL_RESERVED_MASK                                                          (0x0000ff00U)

#define ISS_CTRL_RESERVED1_SHIFT                                                        (24U)
#define ISS_CTRL_RESERVED1_MASK                                                         (0xff000000U)

#define ISS_CLKCTRL_SIMCOP_SHIFT                                                        (0U)
#define ISS_CLKCTRL_SIMCOP_MASK                                                         (0x00000001U)
#define ISS_CLKCTRL_SIMCOP_OFF                                                           (0U)
#define ISS_CLKCTRL_SIMCOP_ON                                                            (1U)

#define ISS_CLKCTRL_ISP_SHIFT                                                           (1U)
#define ISS_CLKCTRL_ISP_MASK                                                            (0x00000002U)
#define ISS_CLKCTRL_ISP_OFF                                                              (0U)
#define ISS_CLKCTRL_ISP_ON                                                               (1U)

#define ISS_CLKCTRL_CCP2_SHIFT                                                          (4U)
#define ISS_CLKCTRL_CCP2_MASK                                                           (0x00000010U)
#define ISS_CLKCTRL_CCP2_OFF                                                             (0U)
#define ISS_CLKCTRL_CCP2_ON                                                              (1U)

#define ISS_CLKCTRL_CCP2_PCLK_SHIFT                                                     (16U)
#define ISS_CLKCTRL_CCP2_PCLK_MASK                                                      (0x00010000U)
#define ISS_CLKCTRL_CCP2_PCLK_ZERO                                                       (0U)
#define ISS_CLKCTRL_CCP2_PCLK_ONE                                                        (1U)

#define ISS_CLKCTRL_BYS_A_SHIFT                                                         (5U)
#define ISS_CLKCTRL_BYS_A_MASK                                                          (0x00000020U)
#define ISS_CLKCTRL_BYS_A_OFF                                                            (0U)
#define ISS_CLKCTRL_BYS_A_ON                                                             (1U)

#define ISS_CLKCTRL_BYS_B_SHIFT                                                         (7U)
#define ISS_CLKCTRL_BYS_B_MASK                                                          (0x00000080U)
#define ISS_CLKCTRL_BYS_B_OFF                                                            (0U)
#define ISS_CLKCTRL_BYS_B_ON                                                             (1U)

#define ISS_CLKCTRL_CAL_A_SHIFT                                                         (9U)
#define ISS_CLKCTRL_CAL_A_MASK                                                          (0x00000200U)
#define ISS_CLKCTRL_CAL_A_OFF                                                            (0U)
#define ISS_CLKCTRL_CAL_A_ON                                                             (1U)

#define ISS_CLKCTRL_CAL_B_SHIFT                                                         (10U)
#define ISS_CLKCTRL_CAL_B_MASK                                                          (0x00000400U)
#define ISS_CLKCTRL_CAL_B_OFF                                                            (0U)
#define ISS_CLKCTRL_CAL_B_ON                                                             (1U)

#define ISS_CLKCTRL_ICM_A_SHIFT                                                         (12U)
#define ISS_CLKCTRL_ICM_A_MASK                                                          (0x00001000U)
#define ISS_CLKCTRL_ICM_A_OFF                                                            (0U)
#define ISS_CLKCTRL_ICM_A_ON                                                             (1U)

#define ISS_CLKCTRL_LVDSRX_SHIFT                                                        (13U)
#define ISS_CLKCTRL_LVDSRX_MASK                                                         (0x00002000U)
#define ISS_CLKCTRL_LVDSRX_OFF                                                           (0U)
#define ISS_CLKCTRL_LVDSRX_ON                                                            (1U)

#define ISS_CLKCTRL_ICM_B_SHIFT                                                         (11U)
#define ISS_CLKCTRL_ICM_B_MASK                                                          (0x00000800U)
#define ISS_CLKCTRL_ICM_B_OFF                                                            (0U)
#define ISS_CLKCTRL_ICM_B_ON                                                             (1U)

#define ISS_CLKCTRL_RESERVED1_SHIFT                                                     (2U)
#define ISS_CLKCTRL_RESERVED1_MASK                                                      (0x0000000cU)

#define ISS_CLKCTRL_RESERVED2_SHIFT                                                     (6U)
#define ISS_CLKCTRL_RESERVED2_MASK                                                      (0x00000040U)

#define ISS_CLKCTRL_RESERVED3_SHIFT                                                     (8U)
#define ISS_CLKCTRL_RESERVED3_MASK                                                      (0x00000100U)

#define ISS_CLKCTRL_CTSET_SHIFT                                                         (14U)
#define ISS_CLKCTRL_CTSET_MASK                                                          (0x00004000U)
#define ISS_CLKCTRL_CTSET_OFF                                                            (0U)
#define ISS_CLKCTRL_CTSET_ON                                                             (1U)

#define ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_SHIFT                                            (17U)
#define ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_MASK                                             (0x00020000U)
#define ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_ZERO                                              (0U)
#define ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_ONE                                               (1U)

#define ISS_CLKCTRL_CAL_A_OUT_PCLK_SHIFT                                                (18U)
#define ISS_CLKCTRL_CAL_A_OUT_PCLK_MASK                                                 (0x00040000U)
#define ISS_CLKCTRL_CAL_A_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_CAL_A_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_SHIFT                                            (19U)
#define ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_MASK                                             (0x00080000U)
#define ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_ZERO                                              (0U)
#define ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_ONE                                               (1U)

#define ISS_CLKCTRL_CAL_B_OUT_PCLK_SHIFT                                                (20U)
#define ISS_CLKCTRL_CAL_B_OUT_PCLK_MASK                                                 (0x00100000U)
#define ISS_CLKCTRL_CAL_B_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_CAL_B_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_PARALLEL_A_PCLK_SHIFT                                               (21U)
#define ISS_CLKCTRL_PARALLEL_A_PCLK_MASK                                                (0x00200000U)
#define ISS_CLKCTRL_PARALLEL_A_PCLK_ZERO                                                 (0U)
#define ISS_CLKCTRL_PARALLEL_A_PCLK_ONE                                                  (1U)

#define ISS_CLKCTRL_BYS_A_OUT_PCLK_SHIFT                                                (22U)
#define ISS_CLKCTRL_BYS_A_OUT_PCLK_MASK                                                 (0x00400000U)
#define ISS_CLKCTRL_BYS_A_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_BYS_A_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_BYS_B_OUT_PCLK_SHIFT                                                (23U)
#define ISS_CLKCTRL_BYS_B_OUT_PCLK_MASK                                                 (0x00800000U)
#define ISS_CLKCTRL_BYS_B_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_BYS_B_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_NSF3V_OUT_PCLK_SHIFT                                                (24U)
#define ISS_CLKCTRL_NSF3V_OUT_PCLK_MASK                                                 (0x01000000U)
#define ISS_CLKCTRL_NSF3V_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_NSF3V_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_GLBCE_OUT_PCLK_SHIFT                                                (25U)
#define ISS_CLKCTRL_GLBCE_OUT_PCLK_MASK                                                 (0x02000000U)
#define ISS_CLKCTRL_GLBCE_OUT_PCLK_ZERO                                                  (0U)
#define ISS_CLKCTRL_GLBCE_OUT_PCLK_ONE                                                   (1U)

#define ISS_CLKCTRL_LVDSRX_OUT0_PCLK_SHIFT                                              (26U)
#define ISS_CLKCTRL_LVDSRX_OUT0_PCLK_MASK                                               (0x04000000U)
#define ISS_CLKCTRL_LVDSRX_OUT0_PCLK_ZERO                                                (0U)
#define ISS_CLKCTRL_LVDSRX_OUT0_PCLK_ONE                                                 (1U)

#define ISS_CLKCTRL_LVDSRX_OUT1_PCLK_SHIFT                                              (27U)
#define ISS_CLKCTRL_LVDSRX_OUT1_PCLK_MASK                                               (0x08000000U)
#define ISS_CLKCTRL_LVDSRX_OUT1_PCLK_ZERO                                                (0U)
#define ISS_CLKCTRL_LVDSRX_OUT1_PCLK_ONE                                                 (1U)

#define ISS_CLKCTRL_LVDSRX_OUT2_PCLK_SHIFT                                              (28U)
#define ISS_CLKCTRL_LVDSRX_OUT2_PCLK_MASK                                               (0x10000000U)
#define ISS_CLKCTRL_LVDSRX_OUT2_PCLK_ZERO                                                (0U)
#define ISS_CLKCTRL_LVDSRX_OUT2_PCLK_ONE                                                 (1U)

#define ISS_CLKCTRL_LVDSRX_OUT3_PCLK_SHIFT                                              (29U)
#define ISS_CLKCTRL_LVDSRX_OUT3_PCLK_MASK                                               (0x20000000U)
#define ISS_CLKCTRL_LVDSRX_OUT3_PCLK_ZERO                                                (0U)
#define ISS_CLKCTRL_LVDSRX_OUT3_PCLK_ONE                                                 (1U)

#define ISS_CLKCTRL_RESERVED5_SHIFT                                                     (30U)
#define ISS_CLKCTRL_RESERVED5_MASK                                                      (0xc0000000U)

#define ISS_CLKCTRL_RESERVED4_SHIFT                                                     (15U)
#define ISS_CLKCTRL_RESERVED4_MASK                                                      (0x00008000U)

#define ISS_CLKSTAT_SIMCOP_SHIFT                                                        (0U)
#define ISS_CLKSTAT_SIMCOP_MASK                                                         (0x00000001U)
#define ISS_CLKSTAT_SIMCOP_OFF                                                           (0U)
#define ISS_CLKSTAT_SIMCOP_ON                                                            (1U)

#define ISS_CLKSTAT_ISP_SHIFT                                                           (1U)
#define ISS_CLKSTAT_ISP_MASK                                                            (0x00000002U)
#define ISS_CLKSTAT_ISP_OFF                                                              (0U)
#define ISS_CLKSTAT_ISP_ON                                                               (1U)

#define ISS_CLKSTAT_CCP2_SHIFT                                                          (4U)
#define ISS_CLKSTAT_CCP2_MASK                                                           (0x00000010U)
#define ISS_CLKSTAT_CCP2_OFF                                                             (0U)
#define ISS_CLKSTAT_CCP2_ON                                                              (1U)

#define ISS_CLKSTAT_BYS_A_SHIFT                                                         (5U)
#define ISS_CLKSTAT_BYS_A_MASK                                                          (0x00000020U)
#define ISS_CLKSTAT_BYS_A_OFF                                                            (0U)
#define ISS_CLKSTAT_BYS_A_ON                                                             (1U)

#define ISS_CLKSTAT_BYS_B_SHIFT                                                         (7U)
#define ISS_CLKSTAT_BYS_B_MASK                                                          (0x00000080U)
#define ISS_CLKSTAT_BYS_B_OFF                                                            (0U)
#define ISS_CLKSTAT_BYS_B_ON                                                             (1U)

#define ISS_CLKSTAT_CAL_A_SHIFT                                                         (9U)
#define ISS_CLKSTAT_CAL_A_MASK                                                          (0x00000200U)
#define ISS_CLKSTAT_CAL_A_OFF                                                            (0U)
#define ISS_CLKSTAT_CAL_A_ON                                                             (1U)

#define ISS_CLKSTAT_CAL_B_SHIFT                                                         (10U)
#define ISS_CLKSTAT_CAL_B_MASK                                                          (0x00000400U)
#define ISS_CLKSTAT_CAL_B_OFF                                                            (0U)
#define ISS_CLKSTAT_CAL_B_ON                                                             (1U)

#define ISS_CLKSTAT_ICM_A_SHIFT                                                         (12U)
#define ISS_CLKSTAT_ICM_A_MASK                                                          (0x00001000U)
#define ISS_CLKSTAT_ICM_A_OFF                                                            (0U)
#define ISS_CLKSTAT_ICM_A_ON                                                             (1U)

#define ISS_CLKSTAT_LVDSRX_SHIFT                                                        (13U)
#define ISS_CLKSTAT_LVDSRX_MASK                                                         (0x00002000U)
#define ISS_CLKSTAT_LVDSRX_OFF                                                           (0U)
#define ISS_CLKSTAT_LVDSRX_ON                                                            (1U)

#define ISS_CLKSTAT_ICM_B_SHIFT                                                         (11U)
#define ISS_CLKSTAT_ICM_B_MASK                                                          (0x00000800U)
#define ISS_CLKSTAT_ICM_B_OFF                                                            (0U)
#define ISS_CLKSTAT_ICM_B_ON                                                             (1U)

#define ISS_CLKSTAT_RESERVED4_SHIFT                                                     (15U)
#define ISS_CLKSTAT_RESERVED4_MASK                                                      (0x00008000U)

#define ISS_CLKSTAT_RESERVED1_SHIFT                                                     (2U)
#define ISS_CLKSTAT_RESERVED1_MASK                                                      (0x0000000cU)

#define ISS_CLKSTAT_RESERVED2_SHIFT                                                     (6U)
#define ISS_CLKSTAT_RESERVED2_MASK                                                      (0x00000040U)

#define ISS_CLKSTAT_RESERVED3_SHIFT                                                     (8U)
#define ISS_CLKSTAT_RESERVED3_MASK                                                      (0x00000100U)

#define ISS_CLKSTAT_CTSET_SHIFT                                                         (14U)
#define ISS_CLKSTAT_CTSET_MASK                                                          (0x00004000U)
#define ISS_CLKSTAT_CTSET_OFF                                                            (0U)
#define ISS_CLKSTAT_CTSET_ON                                                             (1U)

#define ISS_CLKSTAT_CCP2_PCLK_SHIFT                                                     (16U)
#define ISS_CLKSTAT_CCP2_PCLK_MASK                                                      (0x00010000U)
#define ISS_CLKSTAT_CCP2_PCLK_OFF                                                        (0U)
#define ISS_CLKSTAT_CCP2_PCLK_ON                                                         (1U)

#define ISS_CLKSTAT_CAL_A_BYS_OUT_PCLK_SHIFT                                            (17U)
#define ISS_CLKSTAT_CAL_A_BYS_OUT_PCLK_MASK                                             (0x00020000U)
#define ISS_CLKSTAT_CAL_A_BYS_OUT_PCLK_OFF                                               (0U)
#define ISS_CLKSTAT_CAL_A_BYS_OUT_PCLK_ON                                                (1U)

#define ISS_CLKSTAT_CAL_A_OUT_PCLK_SHIFT                                                (18U)
#define ISS_CLKSTAT_CAL_A_OUT_PCLK_MASK                                                 (0x00040000U)
#define ISS_CLKSTAT_CAL_A_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_CAL_A_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_CAL_B_BYS_OUT_PCLK_SHIFT                                            (19U)
#define ISS_CLKSTAT_CAL_B_BYS_OUT_PCLK_MASK                                             (0x00080000U)
#define ISS_CLKSTAT_CAL_B_BYS_OUT_PCLK_OFF                                               (0U)
#define ISS_CLKSTAT_CAL_B_BYS_OUT_PCLK_ON                                                (1U)

#define ISS_CLKSTAT_CAL_B_OUT_PCLK_SHIFT                                                (20U)
#define ISS_CLKSTAT_CAL_B_OUT_PCLK_MASK                                                 (0x00100000U)
#define ISS_CLKSTAT_CAL_B_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_CAL_B_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_PARALLEL_A_PCLK_SHIFT                                               (21U)
#define ISS_CLKSTAT_PARALLEL_A_PCLK_MASK                                                (0x00200000U)
#define ISS_CLKSTAT_PARALLEL_A_PCLK_OFF                                                  (0U)
#define ISS_CLKSTAT_PARALLEL_A_PCLK_ON                                                   (1U)

#define ISS_CLKSTAT_BYS_A_OUT_PCLK_SHIFT                                                (22U)
#define ISS_CLKSTAT_BYS_A_OUT_PCLK_MASK                                                 (0x00400000U)
#define ISS_CLKSTAT_BYS_A_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_BYS_A_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_BYS_B_OUT_PCLK_SHIFT                                                (23U)
#define ISS_CLKSTAT_BYS_B_OUT_PCLK_MASK                                                 (0x00800000U)
#define ISS_CLKSTAT_BYS_B_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_BYS_B_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_NSF3V_OUT_PCLK_SHIFT                                                (24U)
#define ISS_CLKSTAT_NSF3V_OUT_PCLK_MASK                                                 (0x01000000U)
#define ISS_CLKSTAT_NSF3V_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_NSF3V_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_GLBCE_OUT_PCLK_SHIFT                                                (25U)
#define ISS_CLKSTAT_GLBCE_OUT_PCLK_MASK                                                 (0x02000000U)
#define ISS_CLKSTAT_GLBCE_OUT_PCLK_OFF                                                   (0U)
#define ISS_CLKSTAT_GLBCE_OUT_PCLK_ON                                                    (1U)

#define ISS_CLKSTAT_LVDSRX_OUT0_PCLK_SHIFT                                              (26U)
#define ISS_CLKSTAT_LVDSRX_OUT0_PCLK_MASK                                               (0x04000000U)
#define ISS_CLKSTAT_LVDSRX_OUT0_PCLK_OFF                                                 (0U)
#define ISS_CLKSTAT_LVDSRX_OUT0_PCLK_ON                                                  (1U)

#define ISS_CLKSTAT_LVDSRX_OUT1_PCLK_SHIFT                                              (27U)
#define ISS_CLKSTAT_LVDSRX_OUT1_PCLK_MASK                                               (0x08000000U)
#define ISS_CLKSTAT_LVDSRX_OUT1_PCLK_OFF                                                 (0U)
#define ISS_CLKSTAT_LVDSRX_OUT1_PCLK_ON                                                  (1U)

#define ISS_CLKSTAT_LVDSRX_OUT2_PCLK_SHIFT                                              (28U)
#define ISS_CLKSTAT_LVDSRX_OUT2_PCLK_MASK                                               (0x10000000U)
#define ISS_CLKSTAT_LVDSRX_OUT2_PCLK_OFF                                                 (0U)
#define ISS_CLKSTAT_LVDSRX_OUT2_PCLK_ON                                                  (1U)

#define ISS_CLKSTAT_LVDSRX_OUT3_PCLK_SHIFT                                              (29U)
#define ISS_CLKSTAT_LVDSRX_OUT3_PCLK_MASK                                               (0x20000000U)
#define ISS_CLKSTAT_LVDSRX_OUT3_PCLK_OFF                                                 (0U)
#define ISS_CLKSTAT_LVDSRX_OUT3_PCLK_ON                                                  (1U)

#define ISS_CLKSTAT_RESERVED5_SHIFT                                                     (30U)
#define ISS_CLKSTAT_RESERVED5_MASK                                                      (0xc0000000U)

#define ISS_PM_STATUS_CCP2_SHIFT                                                        (4U)
#define ISS_PM_STATUS_CCP2_MASK                                                         (0x00000030U)
#define ISS_PM_STATUS_CCP2_STANDBY                                                       (0U)
#define ISS_PM_STATUS_CCP2_TRANS                                                         (1U)
#define ISS_PM_STATUS_CCP2_FUNC                                                          (2U)

#define ISS_PM_STATUS_ISP_SHIFT                                                         (6U)
#define ISS_PM_STATUS_ISP_MASK                                                          (0x000000c0U)
#define ISS_PM_STATUS_ISP_STANDBY                                                        (0U)
#define ISS_PM_STATUS_ISP_TRANS                                                          (1U)
#define ISS_PM_STATUS_ISP_FUNC                                                           (2U)

#define ISS_PM_STATUS_SIMCOP_SHIFT                                                      (8U)
#define ISS_PM_STATUS_SIMCOP_MASK                                                       (0x00000300U)
#define ISS_PM_STATUS_SIMCOP_STANDBY                                                     (0U)
#define ISS_PM_STATUS_SIMCOP_TRANS                                                       (1U)
#define ISS_PM_STATUS_SIMCOP_FUNC                                                        (2U)

#define ISS_PM_STATUS_BTE_SHIFT                                                         (10U)
#define ISS_PM_STATUS_BTE_MASK                                                          (0x00000c00U)
#define ISS_PM_STATUS_BTE_IDLE                                                           (0U)
#define ISS_PM_STATUS_BTE_TRANS                                                          (1U)
#define ISS_PM_STATUS_BTE_FUNC                                                           (2U)

#define ISS_PM_STATUS_CBUFF_SHIFT                                                       (12U)
#define ISS_PM_STATUS_CBUFF_MASK                                                        (0x00003000U)
#define ISS_PM_STATUS_CBUFF_IDLE                                                         (0U)
#define ISS_PM_STATUS_CBUFF_TRANS                                                        (1U)
#define ISS_PM_STATUS_CBUFF_FUNC                                                         (2U)

#define ISS_PM_STATUS_CAL_A_SHIFT                                                       (18U)
#define ISS_PM_STATUS_CAL_A_MASK                                                        (0x000c0000U)
#define ISS_PM_STATUS_CAL_A_STANDBY                                                      (0U)
#define ISS_PM_STATUS_CAL_A_TRANS                                                        (1U)
#define ISS_PM_STATUS_CAL_A_FUNC                                                         (2U)

#define ISS_PM_STATUS_CAL_B_SHIFT                                                       (20U)
#define ISS_PM_STATUS_CAL_B_MASK                                                        (0x00300000U)
#define ISS_PM_STATUS_CAL_B_STANDBY                                                      (0U)
#define ISS_PM_STATUS_CAL_B_TRANS                                                        (1U)
#define ISS_PM_STATUS_CAL_B_FUNC                                                         (2U)

#define ISS_PM_STATUS_ICM_A_SHIFT                                                       (24U)
#define ISS_PM_STATUS_ICM_A_MASK                                                        (0x03000000U)
#define ISS_PM_STATUS_ICM_A_STANDBY                                                      (0U)
#define ISS_PM_STATUS_ICM_A_TRANS                                                        (1U)
#define ISS_PM_STATUS_ICM_A_FUNC                                                         (2U)

#define ISS_PM_STATUS_RESERVED_SHIFT                                                    (28U)
#define ISS_PM_STATUS_RESERVED_MASK                                                     (0xf0000000U)

#define ISS_PM_STATUS_ICM_B_SHIFT                                                       (22U)
#define ISS_PM_STATUS_ICM_B_MASK                                                        (0x00c00000U)
#define ISS_PM_STATUS_ICM_B_STANDBY                                                      (0U)
#define ISS_PM_STATUS_ICM_B_TRANS                                                        (1U)
#define ISS_PM_STATUS_ICM_B_FUNC                                                         (2U)

#define ISS_PM_STATUS_RESERVED1_SHIFT                                                   (0U)
#define ISS_PM_STATUS_RESERVED1_MASK                                                    (0x0000000fU)

#define ISS_PM_STATUS_RESERVED2_SHIFT                                                   (14U)
#define ISS_PM_STATUS_RESERVED2_MASK                                                    (0x0003c000U)

#define ISS_PM_STATUS_CTSET_SHIFT                                                       (26U)
#define ISS_PM_STATUS_CTSET_MASK                                                        (0x0c000000U)
#define ISS_PM_STATUS_CTSET_STANDBY                                                      (0U)
#define ISS_PM_STATUS_CTSET_TRANS                                                        (1U)
#define ISS_PM_STATUS_CTSET_FUNC                                                         (2U)

#define ISS_BYS_BYSA_IN_SHIFT                                                           (0U)
#define ISS_BYS_BYSA_IN_MASK                                                            (0x00000007U)
#define ISS_BYS_BYSA_IN_NONE                                                             (0U)
#define ISS_BYS_BYSA_IN_CSI3_A                                                           (4U)
#define ISS_BYS_BYSA_IN_RESERVED                                                         (1U)
#define ISS_BYS_BYSA_IN_RESERVED1                                                        (5U)

#define ISS_BYS_BYSB_IN_SHIFT                                                           (4U)
#define ISS_BYS_BYSB_IN_MASK                                                            (0x00000070U)
#define ISS_BYS_BYSB_IN_NONE                                                             (0U)
#define ISS_BYS_BYSB_IN_CSI3_A                                                           (4U)
#define ISS_BYS_BYSB_IN_RESERVED                                                         (1U)
#define ISS_BYS_BYSB_IN_RESERVED1                                                        (5U)

#define ISS_BYS_CSI3A_IN_SHIFT                                                          (14U)
#define ISS_BYS_CSI3A_IN_MASK                                                           (0x00004000U)
#define ISS_BYS_CSI3A_IN_A                                                               (0U)
#define ISS_BYS_CSI3A_IN_B                                                               (1U)

#define ISS_BYS_RESERVED_SHIFT                                                          (3U)
#define ISS_BYS_RESERVED_MASK                                                           (0x00000008U)

#define ISS_BYS_RESERVED1_SHIFT                                                         (7U)
#define ISS_BYS_RESERVED1_MASK                                                          (0x00003f80U)

#define ISS_BYS_RESERVED2_SHIFT                                                         (15U)
#define ISS_BYS_RESERVED2_MASK                                                          (0xffff8000U)

#define ISS_CTRL1_ENABLE_VMUX_SHIFT                                                     (4U)
#define ISS_CTRL1_ENABLE_VMUX_MASK                                                      (0x00000010U)
#define ISS_CTRL1_ENABLE_VMUX_LEGACY                                                     (0U)
#define ISS_CTRL1_ENABLE_VMUX                                                            (1U)

#define ISS_CTRL1_BTE_WMEM_SHIFT                                                        (5U)
#define ISS_CTRL1_BTE_WMEM_MASK                                                         (0x00000060U)
#define ISS_CTRL1_BTE_WMEM_ZERO                                                          (0U)
#define ISS_CTRL1_BTE_WMEM_ONE                                                           (1U)

#define ISS_CTRL1_SENSOR_HUB_SYNC_SHIFT                                                 (7U)
#define ISS_CTRL1_SENSOR_HUB_SYNC_MASK                                                  (0x00001f80U)

#define ISS_CTRL1_STALL_MODE_SHIFT                                                      (13U)
#define ISS_CTRL1_STALL_MODE_MASK                                                       (0x0000e000U)

#define ISS_CTRL1_RESERVED1_SHIFT                                                       (2U)
#define ISS_CTRL1_RESERVED1_MASK                                                        (0x0000000cU)

#define ISS_CTRL1_CTSET_EVT_SHIFT                                                       (0U)
#define ISS_CTRL1_CTSET_EVT_MASK                                                        (0x00000003U)

#define ISS_CTRL1_RESERVED_SHIFT                                                        (17U)
#define ISS_CTRL1_RESERVED_MASK                                                         (0xfffe0000U)

#define ISS_CTRL1_PPI_MODE_SHIFT                                                        (16U)
#define ISS_CTRL1_PPI_MODE_MASK                                                         (0x00010000U)
#define ISS_CTRL1_PPI_MODE_BALANCED                                                      (0U)
#define ISS_CTRL1_PPI_MODE_EXTENDED                                                      (1U)

#define ISS_VMUX_CAL_A_BYS_IN_SHIFT                                                     (16U)
#define ISS_VMUX_CAL_A_BYS_IN_MASK                                                      (0x000f0000U)
#define ISS_VMUX_CAL_A_BYS_IN_ZERO                                                       (0U)
#define ISS_VMUX_CAL_A_BYS_IN_OUT                                                        (1U)
#define ISS_VMUX_CAL_A_BYS_IN_B_OUT                                                      (2U)
#define ISS_VMUX_CAL_A_BYS_IN_NSF3V_OUT                                                  (3U)
#define ISS_VMUX_CAL_A_BYS_IN_GLBCE_OUT                                                  (4U)
#define ISS_VMUX_CAL_A_BYS_IN_LVDSRX_OUT0                                                (5U)
#define ISS_VMUX_CAL_A_BYS_IN_LVDSRX_OUT2                                                (8U)
#define ISS_VMUX_CAL_A_BYS_IN_RESERVED                                                   (9U)
#define ISS_VMUX_CAL_A_BYS_IN_RESERVED1                                                  (7U)
#define ISS_VMUX_CAL_A_BYS_IN_LVDSRX_OUT3                                                (6U)

#define ISS_VMUX_CAL_B_BYS_IN_SHIFT                                                     (20U)
#define ISS_VMUX_CAL_B_BYS_IN_MASK                                                      (0x00f00000U)
#define ISS_VMUX_CAL_B_BYS_IN_ZERO                                                       (0U)
#define ISS_VMUX_CAL_B_BYS_IN_A_OUT                                                      (1U)
#define ISS_VMUX_CAL_B_BYS_IN_OUT                                                        (2U)
#define ISS_VMUX_CAL_B_BYS_IN_NSF3V_OUT                                                  (3U)
#define ISS_VMUX_CAL_B_BYS_IN_GLBCE_OUT                                                  (4U)
#define ISS_VMUX_CAL_B_BYS_IN_LVDSRX_OUT1                                                (5U)
#define ISS_VMUX_CAL_B_BYS_IN_LDVSRX_OUT3                                                (8U)
#define ISS_VMUX_CAL_B_BYS_IN_RESERVED                                                   (9U)
#define ISS_VMUX_CAL_B_BYS_IN_RESERVED1                                                  (6U)

#define ISS_VMUX_BYS_A_IN_SHIFT                                                         (24U)
#define ISS_VMUX_BYS_A_IN_MASK                                                          (0x07000000U)
#define ISS_VMUX_BYS_A_IN_ZERO                                                           (0U)
#define ISS_VMUX_BYS_A_IN_CAL_OUT                                                        (1U)
#define ISS_VMUX_BYS_A_IN_CAL_B_OUT                                                      (2U)
#define ISS_VMUX_BYS_A_IN_LVDSRX_OUT0                                                    (3U)
#define ISS_VMUX_BYS_A_IN_LVDSRX_OUT2                                                    (4U)
#define ISS_VMUX_BYS_A_IN_RESERVED                                                       (5U)

#define ISS_VMUX_BYS_B_IN_SHIFT                                                         (28U)
#define ISS_VMUX_BYS_B_IN_MASK                                                          (0x70000000U)
#define ISS_VMUX_BYS_B_IN_ZERO                                                           (0U)
#define ISS_VMUX_BYS_B_IN_CAL_A_OUT                                                      (1U)
#define ISS_VMUX_BYS_B_IN_CAL_OUT                                                        (2U)
#define ISS_VMUX_BYS_B_IN_LVDSRX_OUT1                                                    (3U)
#define ISS_VMUX_BYS_B_IN_LVDSRX_OUT3                                                    (4U)
#define ISS_VMUX_BYS_B_IN_RESERVED                                                       (5U)

#define ISS_VMUX_NSF3V_IN_SHIFT                                                         (4U)
#define ISS_VMUX_NSF3V_IN_MASK                                                          (0x000000f0U)
#define ISS_VMUX_NSF3V_IN_ZERO                                                           (0U)
#define ISS_VMUX_NSF3V_IN_CAL_A_BYS_OUT                                                  (1U)
#define ISS_VMUX_NSF3V_IN_CAL_B_BYS_OUT                                                  (2U)
#define ISS_VMUX_NSF3V_IN_RESERVED                                                       (3U)

#define ISS_VMUX_GLBCE_IN_SHIFT                                                         (8U)
#define ISS_VMUX_GLBCE_IN_MASK                                                          (0x00000f00U)
#define ISS_VMUX_GLBCE_IN_ZERO                                                           (0U)
#define ISS_VMUX_GLBCE_IN_CAL_A_BYS_OUT                                                  (1U)
#define ISS_VMUX_GLBCE_IN_CAL_B_BYS_OUT                                                  (2U)
#define ISS_VMUX_GLBCE_IN_RESERVED                                                       (3U)

#define ISS_VMUX_ISP_IN_SHIFT                                                           (0U)
#define ISS_VMUX_ISP_IN_MASK                                                            (0x0000000fU)
#define ISS_VMUX_ISP_IN_ZERO                                                             (0U)
#define ISS_VMUX_ISP_IN_CAL_A_OUT                                                        (1U)
#define ISS_VMUX_ISP_IN_CAL_B_OUT                                                        (2U)
#define ISS_VMUX_ISP_IN_PARALLEL_A                                                       (3U)
#define ISS_VMUX_ISP_IN_LVDSRX_OUT0                                                      (4U)
#define ISS_VMUX_ISP_IN_LVDSRX_OUT1                                                      (5U)
#define ISS_VMUX_ISP_IN_LVDSRX_OUT2                                                      (6U)
#define ISS_VMUX_ISP_IN_LVDSRX_OUT3                                                      (7U)
#define ISS_VMUX_ISP_IN_CCP2                                                             (8U)

#define ISS_VMUX_RESERVED_SHIFT                                                         (12U)
#define ISS_VMUX_RESERVED_MASK                                                          (0x0000f000U)

#define ISS_VMUX_RESERVED2_SHIFT                                                        (27U)
#define ISS_VMUX_RESERVED2_MASK                                                         (0x08000000U)

#define ISS_VMUX_RESERVED3_SHIFT                                                        (31U)
#define ISS_VMUX_RESERVED3_MASK                                                         (0x80000000U)

#define ISS_ROUTE1_CALA_SHIFT(n)                                                        ((n) * 2U)
#define ISS_ROUTE1_CALA_MASK(n)                                                         ((uint32_t)3U << ((n) * 2U))
#define ISS_ROUTE1_CALA_0_OCPM2                                                          (0U)
#define ISS_ROUTE1_CALA_0_OCPM1                                                          (1U)
#define ISS_ROUTE1_CALA_0_OCPM3                                                          (2U)
#define ISS_ROUTE1_CALA_0_RESERVED                                                       (3U)

#define ISS_ROUTE2_CALB_SHIFT(n)                                                        ((n) * 2U)
#define ISS_ROUTE2_CALB_MASK(n)                                                         ((uint32_t)3U << ((n) * 2U))
#define ISS_ROUTE2_CALB_0_OCPM2                                                          (0U)
#define ISS_ROUTE2_CALB_0_OCPM1                                                          (1U)
#define ISS_ROUTE2_CALB_0_OCPM3                                                          (2U)
#define ISS_ROUTE2_CALB_0_RESERVED                                                       (3U)

#define ISS_ROUTE3_CCP2_RD_SHIFT                                                        (24U)
#define ISS_ROUTE3_CCP2_RD_MASK                                                         (0x03000000U)
#define ISS_ROUTE3_CCP2_RD_OCPM2                                                         (0U)
#define ISS_ROUTE3_CCP2_RD_OCPM1                                                         (1U)
#define ISS_ROUTE3_CCP2_RD_OCPM3                                                         (2U)
#define ISS_ROUTE3_CCP2_RD_RESERVED                                                      (3U)

#define ISS_ROUTE3_CCP2_WR_SHIFT                                                        (26U)
#define ISS_ROUTE3_CCP2_WR_MASK                                                         (0x0c000000U)
#define ISS_ROUTE3_CCP2_WR_OCPM2                                                         (0U)
#define ISS_ROUTE3_CCP2_WR_OCPM1                                                         (1U)
#define ISS_ROUTE3_CCP2_WR_OCPM3                                                         (2U)
#define ISS_ROUTE3_CCP2_WR_RESERVED                                                      (3U)

#define ISS_ROUTE3_ISP_IPIPEIF_SHIFT                                                    (0U)
#define ISS_ROUTE3_ISP_IPIPEIF_MASK                                                     (0x00000003U)
#define ISS_ROUTE3_ISP_IPIPEIF_OCPM2                                                     (0U)
#define ISS_ROUTE3_ISP_IPIPEIF_OCPM1                                                     (1U)
#define ISS_ROUTE3_ISP_IPIPEIF_OCPM3                                                     (2U)
#define ISS_ROUTE3_ISP_IPIPEIF_RESERVED                                                  (3U)

#define ISS_ROUTE3_ISP_LSC_SHIFT                                                        (2U)
#define ISS_ROUTE3_ISP_LSC_MASK                                                         (0x0000000cU)
#define ISS_ROUTE3_ISP_LSC_OCPM2                                                         (0U)
#define ISS_ROUTE3_ISP_LSC_OCPM1                                                         (1U)
#define ISS_ROUTE3_ISP_LSC_OCPM3                                                         (2U)
#define ISS_ROUTE3_ISP_LSC_RESERVED                                                      (3U)

#define ISS_ROUTE3_ISP_RAW_SHIFT                                                        (4U)
#define ISS_ROUTE3_ISP_RAW_MASK                                                         (0x00000030U)
#define ISS_ROUTE3_ISP_RAW_OCPM2                                                         (0U)
#define ISS_ROUTE3_ISP_RAW_OCPM1                                                         (1U)
#define ISS_ROUTE3_ISP_RAW_OCPM3                                                         (2U)
#define ISS_ROUTE3_ISP_RAW_RESERVED                                                      (3U)

#define ISS_ROUTE3_ISP_BOXCAR_SHIFT                                                     (6U)
#define ISS_ROUTE3_ISP_BOXCAR_MASK                                                      (0x000000c0U)
#define ISS_ROUTE3_ISP_BOXCAR_OCPM2                                                      (0U)
#define ISS_ROUTE3_ISP_BOXCAR_OCPM1                                                      (1U)
#define ISS_ROUTE3_ISP_BOXCAR_OCPM3                                                      (2U)
#define ISS_ROUTE3_ISP_BOXCAR_RESERVED                                                   (3U)

#define ISS_ROUTE3_ISP_H3A_SHIFT                                                        (8U)
#define ISS_ROUTE3_ISP_H3A_MASK                                                         (0x00000300U)
#define ISS_ROUTE3_ISP_H3A_OCPM2                                                         (0U)
#define ISS_ROUTE3_ISP_H3A_OCPM1                                                         (1U)
#define ISS_ROUTE3_ISP_H3A_OCPM3                                                         (2U)
#define ISS_ROUTE3_ISP_H3A_RESERVED                                                      (3U)

#define ISS_ROUTE3_ISP_RSZA_SHIFT                                                       (10U)
#define ISS_ROUTE3_ISP_RSZA_MASK                                                        (0x00000c00U)
#define ISS_ROUTE3_ISP_RSZA_OCPM2                                                        (0U)
#define ISS_ROUTE3_ISP_RSZA_OCPM1                                                        (1U)
#define ISS_ROUTE3_ISP_RSZA_OCPM3                                                        (2U)
#define ISS_ROUTE3_ISP_RSZA_RESERVED                                                     (3U)

#define ISS_ROUTE3_ISP_RSZB_SHIFT                                                       (12U)
#define ISS_ROUTE3_ISP_RSZB_MASK                                                        (0x00003000U)
#define ISS_ROUTE3_ISP_RSZB_OCPM2                                                        (0U)
#define ISS_ROUTE3_ISP_RSZB_OCPM1                                                        (1U)
#define ISS_ROUTE3_ISP_RSZB_OCPM3                                                        (2U)
#define ISS_ROUTE3_ISP_RSZB_RESERVED                                                     (3U)

#define ISS_ROUTE3_ICMA_SHIFT                                                           (16U)
#define ISS_ROUTE3_ICMA_MASK                                                            (0x00030000U)
#define ISS_ROUTE3_ICMA_OCPM2                                                            (0U)
#define ISS_ROUTE3_ICMA_OCPM1                                                            (1U)
#define ISS_ROUTE3_ICMA_OCPM3                                                            (2U)
#define ISS_ROUTE3_ICMA_RESERVED                                                         (3U)

#define ISS_ROUTE3_ICMB_SHIFT                                                           (18U)
#define ISS_ROUTE3_ICMB_MASK                                                            (0x000c0000U)
#define ISS_ROUTE3_ICMB_OCPM2                                                            (0U)
#define ISS_ROUTE3_ICMB_OCPM1                                                            (1U)
#define ISS_ROUTE3_ICMB_OCPM3                                                            (2U)
#define ISS_ROUTE3_ICMB_RESERVED                                                         (3U)

#define ISS_ROUTE3_SDMA_SHIFT                                                           (20U)
#define ISS_ROUTE3_SDMA_MASK                                                            (0x00300000U)
#define ISS_ROUTE3_SDMA_OCPM2                                                            (0U)
#define ISS_ROUTE3_SDMA_OCPM1                                                            (1U)
#define ISS_ROUTE3_SDMA_OCPM3                                                            (2U)
#define ISS_ROUTE3_SDMA_RESERVED                                                         (3U)

#define ISS_ROUTE3_LDC_SHIFT                                                            (22U)
#define ISS_ROUTE3_LDC_MASK                                                             (0x00c00000U)
#define ISS_ROUTE3_LDC_OCPM2                                                             (0U)
#define ISS_ROUTE3_LDC_OCPM1                                                             (1U)
#define ISS_ROUTE3_LDC_OCPM3                                                             (2U)
#define ISS_ROUTE3_LDC_RESERVED                                                          (3U)

#define ISS_ROUTE3_RESERVED_SHIFT                                                       (14U)
#define ISS_ROUTE3_RESERVED_MASK                                                        (0x0000c000U)

#define ISS_ROUTE3_RESERVED1_SHIFT                                                      (28U)
#define ISS_ROUTE3_RESERVED1_MASK                                                       (0xf0000000U)

#define ISS_EMU_OUT_EMU2_L_SHIFT                                                        (0U)
#define ISS_EMU_OUT_EMU2_L_MASK                                                         (0x000000ffU)

#define ISS_EMU_OUT_EMU3_L_SHIFT                                                        (16U)
#define ISS_EMU_OUT_EMU3_L_MASK                                                         (0x00ff0000U)

#define ISS_EMU_OUT_RESERVED_SHIFT                                                      (10U)
#define ISS_EMU_OUT_RESERVED_MASK                                                       (0x0000fc00U)

#define ISS_EMU_OUT_RESERVED1_SHIFT                                                     (26U)
#define ISS_EMU_OUT_RESERVED1_MASK                                                      (0xfc000000U)

#define ISS_EMU_OUT_EMU2_H_SHIFT                                                        (8U)
#define ISS_EMU_OUT_EMU2_H_MASK                                                         (0x00000300U)

#define ISS_EMU_OUT_EMU3_H_SHIFT                                                        (24U)
#define ISS_EMU_OUT_EMU3_H_MASK                                                         (0x03000000U)

#define ISS_VMUX_RESET_W16_64_A_OVR_IRQ_SHIFT                                           (0U)
#define ISS_VMUX_RESET_W16_64_A_OVR_IRQ_MASK                                            (0x00000001U)
#define ISS_VMUX_RESET_W16_64_A_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W16_64_A_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_W16_64_B_OVR_IRQ_SHIFT                                           (1U)
#define ISS_VMUX_RESET_W16_64_B_OVR_IRQ_MASK                                            (0x00000002U)
#define ISS_VMUX_RESET_W16_64_B_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W16_64_B_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_W64_16_A_OVR_IRQ_SHIFT                                           (2U)
#define ISS_VMUX_RESET_W64_16_A_OVR_IRQ_MASK                                            (0x00000004U)
#define ISS_VMUX_RESET_W64_16_A_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W64_16_A_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_W64_16_B_OVR_IRQ_SHIFT                                           (3U)
#define ISS_VMUX_RESET_W64_16_B_OVR_IRQ_MASK                                            (0x00000008U)
#define ISS_VMUX_RESET_W64_16_B_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W64_16_B_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_W32_16_A_OVR_IRQ_SHIFT                                           (4U)
#define ISS_VMUX_RESET_W32_16_A_OVR_IRQ_MASK                                            (0x00000010U)
#define ISS_VMUX_RESET_W32_16_A_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W32_16_A_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_W64_32_A_OVR_IRQ_SHIFT                                           (5U)
#define ISS_VMUX_RESET_W64_32_A_OVR_IRQ_MASK                                            (0x00000020U)
#define ISS_VMUX_RESET_W64_32_A_OVR_IRQ_NOEFFECT                                         (0U)
#define ISS_VMUX_RESET_W64_32_A_OVR_IRQ                                                  (1U)

#define ISS_VMUX_RESET_F426_304_A_OVR_IRQ_SHIFT                                         (6U)
#define ISS_VMUX_RESET_F426_304_A_OVR_IRQ_MASK                                          (0x00000040U)
#define ISS_VMUX_RESET_F426_304_A_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F426_304_A_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F426_304_B_OVR_IRQ_SHIFT                                         (7U)
#define ISS_VMUX_RESET_F426_304_B_OVR_IRQ_MASK                                          (0x00000080U)
#define ISS_VMUX_RESET_F426_304_B_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F426_304_B_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F304_426_A_OVR_IRQ_SHIFT                                         (8U)
#define ISS_VMUX_RESET_F304_426_A_OVR_IRQ_MASK                                          (0x00000100U)
#define ISS_VMUX_RESET_F304_426_A_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_A_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F304_426_B_OVR_IRQ_SHIFT                                         (9U)
#define ISS_VMUX_RESET_F304_426_B_OVR_IRQ_MASK                                          (0x00000200U)
#define ISS_VMUX_RESET_F304_426_B_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_B_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F304_426_C_OVR_IRQ_SHIFT                                         (10U)
#define ISS_VMUX_RESET_F304_426_C_OVR_IRQ_MASK                                          (0x00000400U)
#define ISS_VMUX_RESET_F304_426_C_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_C_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F304_426_D_OVR_IRQ_SHIFT                                         (11U)
#define ISS_VMUX_RESET_F304_426_D_OVR_IRQ_MASK                                          (0x00000800U)
#define ISS_VMUX_RESET_F304_426_D_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_D_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_F304_426_E_OVR_IRQ_SHIFT                                         (12U)
#define ISS_VMUX_RESET_F304_426_E_OVR_IRQ_MASK                                          (0x00001000U)
#define ISS_VMUX_RESET_F304_426_E_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_E_OVR_IRQ                                                (1U)

#define ISS_VMUX_RESET_RESERVED_SHIFT                                                   (14U)
#define ISS_VMUX_RESET_RESERVED_MASK                                                    (0xffffc000U)

#define ISS_VMUX_RESET_F304_426_F_OVR_IRQ_SHIFT                                         (13U)
#define ISS_VMUX_RESET_F304_426_F_OVR_IRQ_MASK                                          (0x00002000U)
#define ISS_VMUX_RESET_F304_426_F_OVR_IRQ_NOEFFECT                                       (0U)
#define ISS_VMUX_RESET_F304_426_F_OVR_IRQ                                                (1U)

#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_SHIFT                                   (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_MASK                                    (0x00000001U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_A_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_SHIFT                                   (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_MASK                                    (0x00000002U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W16_64_B_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_SHIFT                                   (2U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_MASK                                    (0x00000004U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_A_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_SHIFT                                   (3U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_MASK                                    (0x00000008U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_16_B_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_SHIFT                                   (4U)
#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_MASK                                    (0x00000010U)
#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W32_16_A_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_F426_304_A_OVR_IRQ_SHIFT                                 (6U)
#define ISS_VMUX_IRQSTATUS_RAW_F426_304_A_OVR_IRQ_MASK                                  (0x00000040U)

#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_SHIFT                                   (5U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_MASK                                    (0x00000020U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_SET                                      (1U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_NOEVENT                                  (0U)
#define ISS_VMUX_IRQSTATUS_RAW_W64_32_A_OVR_IRQ_PENDING                                  (1U)

#define ISS_VMUX_IRQSTATUS_RAW_F426_304_B_OVR_IRQ_SHIFT                                 (7U)
#define ISS_VMUX_IRQSTATUS_RAW_F426_304_B_OVR_IRQ_MASK                                  (0x00000080U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_A_OVR_IRQ_SHIFT                                 (8U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_A_OVR_IRQ_MASK                                  (0x00000100U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_B_OVR_IRQ_SHIFT                                 (9U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_B_OVR_IRQ_MASK                                  (0x00000200U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_C_OVR_IRQ_SHIFT                                 (10U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_C_OVR_IRQ_MASK                                  (0x00000400U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_D_OVR_IRQ_SHIFT                                 (11U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_D_OVR_IRQ_MASK                                  (0x00000800U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_E_OVR_IRQ_SHIFT                                 (12U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_E_OVR_IRQ_MASK                                  (0x00001000U)

#define ISS_VMUX_IRQSTATUS_RAW_RESERVED_SHIFT                                           (14U)
#define ISS_VMUX_IRQSTATUS_RAW_RESERVED_MASK                                            (0xffffc000U)

#define ISS_VMUX_IRQSTATUS_RAW_F304_426_F_OVR_IRQ_SHIFT                                 (13U)
#define ISS_VMUX_IRQSTATUS_RAW_F304_426_F_OVR_IRQ_MASK                                  (0x00002000U)

#define ISS_VMUX_IRQSTATUS_RESERVED_SHIFT                                               (14U)
#define ISS_VMUX_IRQSTATUS_RESERVED_MASK                                                (0xffffc000U)

#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_SHIFT                                       (0U)
#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_MASK                                        (0x00000001U)
#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W16_64_A_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_SHIFT                                       (1U)
#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_MASK                                        (0x00000002U)
#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W16_64_B_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_SHIFT                                       (2U)
#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_MASK                                        (0x00000004U)
#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W64_16_A_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_SHIFT                                       (3U)
#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_MASK                                        (0x00000008U)
#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W64_16_B_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_SHIFT                                       (4U)
#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_MASK                                        (0x00000010U)
#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W32_16_A_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_SHIFT                                       (5U)
#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_MASK                                        (0x00000020U)
#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_NOACTION                                     (0U)
#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_CLEAR                                        (1U)
#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_NOEVENT                                      (0U)
#define ISS_VMUX_IRQSTATUS_W64_32_A_OVR_IRQ_PENDING                                      (1U)

#define ISS_VMUX_IRQSTATUS_F426_304_A_OVR_IRQ_SHIFT                                     (6U)
#define ISS_VMUX_IRQSTATUS_F426_304_A_OVR_IRQ_MASK                                      (0x00000040U)

#define ISS_VMUX_IRQSTATUS_F426_304_B_OVR_IRQ_SHIFT                                     (7U)
#define ISS_VMUX_IRQSTATUS_F426_304_B_OVR_IRQ_MASK                                      (0x00000080U)

#define ISS_VMUX_IRQSTATUS_F304_426_A_OVR_IRQ_SHIFT                                     (8U)
#define ISS_VMUX_IRQSTATUS_F304_426_A_OVR_IRQ_MASK                                      (0x00000100U)

#define ISS_VMUX_IRQSTATUS_F304_426_B_OVR_IRQ_SHIFT                                     (9U)
#define ISS_VMUX_IRQSTATUS_F304_426_B_OVR_IRQ_MASK                                      (0x00000200U)

#define ISS_VMUX_IRQSTATUS_F304_426_C_OVR_IRQ_SHIFT                                     (10U)
#define ISS_VMUX_IRQSTATUS_F304_426_C_OVR_IRQ_MASK                                      (0x00000400U)

#define ISS_VMUX_IRQSTATUS_F304_426_D_OVR_IRQ_SHIFT                                     (11U)
#define ISS_VMUX_IRQSTATUS_F304_426_D_OVR_IRQ_MASK                                      (0x00000800U)

#define ISS_VMUX_IRQSTATUS_F304_426_E_OVR_IRQ_SHIFT                                     (12U)
#define ISS_VMUX_IRQSTATUS_F304_426_E_OVR_IRQ_MASK                                      (0x00001000U)

#define ISS_VMUX_IRQSTATUS_F304_426_F_OVR_IRQ_SHIFT                                     (13U)
#define ISS_VMUX_IRQSTATUS_F304_426_F_OVR_IRQ_MASK                                      (0x00002000U)

#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_SHIFT                                   (0U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_MASK                                    (0x00000001U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_SHIFT                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_MASK                                    (0x00000002U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W16_64_B_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_SHIFT                                   (2U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_MASK                                    (0x00000004U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_SHIFT                                   (3U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_MASK                                    (0x00000008U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_16_B_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_SHIFT                                   (4U)
#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_MASK                                    (0x00000010U)
#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W32_16_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_SHIFT                                   (5U)
#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_MASK                                    (0x00000020U)
#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_ENABLE                                   (1U)
#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_SET_W64_32_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_SET_F426_304_A_OVR_IRQ_SHIFT                                 (6U)
#define ISS_VMUX_IRQENABLE_SET_F426_304_A_OVR_IRQ_MASK                                  (0x00000040U)

#define ISS_VMUX_IRQENABLE_SET_F426_304_B_OVR_IRQ_SHIFT                                 (7U)
#define ISS_VMUX_IRQENABLE_SET_F426_304_B_OVR_IRQ_MASK                                  (0x00000080U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_A_OVR_IRQ_SHIFT                                 (8U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_A_OVR_IRQ_MASK                                  (0x00000100U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_B_OVR_IRQ_SHIFT                                 (9U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_B_OVR_IRQ_MASK                                  (0x00000200U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_C_OVR_IRQ_SHIFT                                 (10U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_C_OVR_IRQ_MASK                                  (0x00000400U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_D_OVR_IRQ_SHIFT                                 (11U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_D_OVR_IRQ_MASK                                  (0x00000800U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_E_OVR_IRQ_SHIFT                                 (12U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_E_OVR_IRQ_MASK                                  (0x00001000U)

#define ISS_VMUX_IRQENABLE_SET_RESERVED_SHIFT                                           (14U)
#define ISS_VMUX_IRQENABLE_SET_RESERVED_MASK                                            (0xffffc000U)

#define ISS_VMUX_IRQENABLE_SET_F304_426_F_OVR_IRQ_SHIFT                                 (13U)
#define ISS_VMUX_IRQENABLE_SET_F304_426_F_OVR_IRQ_MASK                                  (0x00002000U)

#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_SHIFT                                   (0U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_MASK                                    (0x00000001U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_SHIFT                                   (1U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_MASK                                    (0x00000002U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W16_64_B_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_SHIFT                                   (2U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_MASK                                    (0x00000004U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_SHIFT                                   (3U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_MASK                                    (0x00000008U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_16_B_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_SHIFT                                   (4U)
#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_MASK                                    (0x00000010U)
#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W32_16_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_SHIFT                                   (5U)
#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_MASK                                    (0x00000020U)
#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_NOACTION                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_DISABLE                                  (1U)
#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_DISABLED                                 (0U)
#define ISS_VMUX_IRQENABLE_CLR_W64_32_A_OVR_IRQ_ENABLED                                  (1U)

#define ISS_VMUX_IRQENABLE_CLR_F426_304_A_OVR_IRQ_SHIFT                                 (6U)
#define ISS_VMUX_IRQENABLE_CLR_F426_304_A_OVR_IRQ_MASK                                  (0x00000040U)

#define ISS_VMUX_IRQENABLE_CLR_F426_304_B_OVR_IRQ_SHIFT                                 (7U)
#define ISS_VMUX_IRQENABLE_CLR_F426_304_B_OVR_IRQ_MASK                                  (0x00000080U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_A_OVR_IRQ_SHIFT                                 (8U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_A_OVR_IRQ_MASK                                  (0x00000100U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_B_OVR_IRQ_SHIFT                                 (9U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_B_OVR_IRQ_MASK                                  (0x00000200U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_C_OVR_IRQ_SHIFT                                 (10U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_C_OVR_IRQ_MASK                                  (0x00000400U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_D_OVR_IRQ_SHIFT                                 (11U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_D_OVR_IRQ_MASK                                  (0x00000800U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_E_OVR_IRQ_SHIFT                                 (12U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_E_OVR_IRQ_MASK                                  (0x00001000U)

#define ISS_VMUX_IRQENABLE_CLR_RESERVED_SHIFT                                           (14U)
#define ISS_VMUX_IRQENABLE_CLR_RESERVED_MASK                                            (0xffffc000U)

#define ISS_VMUX_IRQENABLE_CLR_F304_426_F_OVR_IRQ_SHIFT                                 (13U)
#define ISS_VMUX_IRQENABLE_CLR_F304_426_F_OVR_IRQ_MASK                                  (0x00002000U)

#define TCTRL_REVISION_REV_SHIFT                                                        (0U)
#define TCTRL_REVISION_REV_MASK                                                         (0x000000ffU)

#define TCTRL_REVISION_RESERVED_SHIFT                                                   (8U)
#define TCTRL_REVISION_RESERVED_MASK                                                    (0xffffff00U)

#define TCTRL_SYSCONFIG_SOFT_RESET_SHIFT                                                (1U)
#define TCTRL_SYSCONFIG_SOFT_RESET_MASK                                                 (0x00000002U)
#define TCTRL_SYSCONFIG_SOFT_RESET_NORMAL                                                (0U)
#define TCTRL_SYSCONFIG_SOFT_RESET                                                       (1U)

#define TCTRL_SYSCONFIG_AUTO_IDLE_SHIFT                                                 (0U)
#define TCTRL_SYSCONFIG_AUTO_IDLE_MASK                                                  (0x00000001U)
#define TCTRL_SYSCONFIG_AUTO_IDLE_FREE                                                   (0U)
#define TCTRL_SYSCONFIG_AUTO_IDLE_GATED                                                  (1U)

#define TCTRL_SYSCONFIG_RESERVED_SHIFT                                                  (2U)
#define TCTRL_SYSCONFIG_RESERVED_MASK                                                   (0xfffffffcU)

#define TCTRL_SYSSTATUS_RESET_DONE_SHIFT                                                (0U)
#define TCTRL_SYSSTATUS_RESET_DONE_MASK                                                 (0x00000001U)
#define TCTRL_SYSSTATUS_RESET_DONE_ONGOING                                               (0U)
#define TCTRL_SYSSTATUS_RESET_DONE_COMPLETED                                             (1U)

#define TCTRL_SYSSTATUS_RESERVED_SHIFT                                                  (1U)
#define TCTRL_SYSSTATUS_RESERVED_MASK                                                   (0xfffffffeU)

#define TCTRL_STRB_LENGTH_SHIFT                                                         (0U)
#define TCTRL_STRB_LENGTH_MASK                                                          (0x00ffffffU)

#define TCTRL_STRB_LENGTH_RESERVED_SHIFT                                                (24U)
#define TCTRL_STRB_LENGTH_RESERVED_MASK                                                 (0xff000000U)

#define TCTRL_PSTRB_LENGTH_SHIFT                                                        (0U)
#define TCTRL_PSTRB_LENGTH_MASK                                                         (0x00ffffffU)

#define TCTRL_PSTRB_LENGTH_RESERVED_SHIFT                                               (24U)
#define TCTRL_PSTRB_LENGTH_RESERVED_MASK                                                (0xff000000U)

#define TCTRL_SHUT_LENGTH_SHIFT                                                         (0U)
#define TCTRL_SHUT_LENGTH_MASK                                                          (0x00ffffffU)

#define TCTRL_SHUT_LENGTH_RESERVED_SHIFT                                                (24U)
#define TCTRL_SHUT_LENGTH_RESERVED_MASK                                                 (0xff000000U)

#define TCTRL_GRESET_LENGTH_SHIFT                                                       (0U)
#define TCTRL_GRESET_LENGTH_MASK                                                        (0x00ffffffU)

#define TCTRL_GRESET_LENGTH_RESERVED_SHIFT                                              (24U)
#define TCTRL_GRESET_LENGTH_RESERVED_MASK                                               (0xff000000U)

#define TCTRL_STRB_DELAY_SHIFT                                                          (0U)
#define TCTRL_STRB_DELAY_MASK                                                           (0x01ffffffU)

#define TCTRL_STRB_DELAY_RESERVED_SHIFT                                                 (25U)
#define TCTRL_STRB_DELAY_RESERVED_MASK                                                  (0xfe000000U)

#define TCTRL_PSTRB_DELAY_SHIFT                                                         (0U)
#define TCTRL_PSTRB_DELAY_MASK                                                          (0x01ffffffU)

#define TCTRL_PSTRB_DELAY_RESERVED_SHIFT                                                (25U)
#define TCTRL_PSTRB_DELAY_RESERVED_MASK                                                 (0xfe000000U)

#define TCTRL_SHUT_DELAY_SHIFT                                                          (0U)
#define TCTRL_SHUT_DELAY_MASK                                                           (0x01ffffffU)

#define TCTRL_SHUT_DELAY_RESERVED_SHIFT                                                 (25U)
#define TCTRL_SHUT_DELAY_RESERVED_MASK                                                  (0xfe000000U)

#define TCTRL_CTRL_DIVC_SHIFT                                                           (10U)
#define TCTRL_CTRL_DIVC_MASK                                                            (0x0007fc00U)
#define TCTRL_CTRL_DIVC_NOCLOCK                                                          (0U)

#define TCTRL_CTRL_SHUTEN_SHIFT                                                         (21U)
#define TCTRL_CTRL_SHUTEN_MASK                                                          (0x00200000U)

#define TCTRL_CTRL_PSTRBEN_SHIFT                                                        (22U)
#define TCTRL_CTRL_PSTRBEN_MASK                                                         (0x00400000U)

#define TCTRL_CTRL_STRBEN_SHIFT                                                         (23U)
#define TCTRL_CTRL_STRBEN_MASK                                                          (0x00800000U)

#define TCTRL_CTRL_SHUTPOL_SHIFT                                                        (24U)
#define TCTRL_CTRL_SHUTPOL_MASK                                                         (0x01000000U)
#define TCTRL_CTRL_SHUTPOL_HIGH                                                          (0U)
#define TCTRL_CTRL_SHUTPOL_LOW                                                           (1U)

#define TCTRL_CTRL_STRBPSTRBPOL_SHIFT                                                   (26U)
#define TCTRL_CTRL_STRBPSTRBPOL_MASK                                                    (0x04000000U)
#define TCTRL_CTRL_STRBPSTRBPOL_HIGH                                                     (0U)
#define TCTRL_CTRL_STRBPSTRBPOL_LOW                                                      (1U)

#define TCTRL_CTRL_GRESETDIR_SHIFT                                                      (31U)
#define TCTRL_CTRL_GRESETDIR_MASK                                                       (0x80000000U)

#define TCTRL_CTRL_GRESETPOL_SHIFT                                                      (30U)
#define TCTRL_CTRL_GRESETPOL_MASK                                                       (0x40000000U)

#define TCTRL_CTRL_GRESETEN_SHIFT                                                       (29U)
#define TCTRL_CTRL_GRESETEN_MASK                                                        (0x20000000U)

#define TCTRL_CTRL_INSEL_SHIFT                                                          (0U)
#define TCTRL_CTRL_INSEL_MASK                                                           (0x0000003fU)

#define TCTRL_CTRL_RESERVED_SHIFT                                                       (6U)
#define TCTRL_CTRL_RESERVED_MASK                                                        (0x000003c0U)

#define TCTRL_CTRL_RESERVED1_SHIFT                                                      (19U)
#define TCTRL_CTRL_RESERVED1_MASK                                                       (0x00180000U)

#define TCTRL_CTRL_RESERVED2_SHIFT                                                      (25U)
#define TCTRL_CTRL_RESERVED2_MASK                                                       (0x02000000U)

#define TCTRL_CTRL_RESERVED3_SHIFT                                                      (27U)
#define TCTRL_CTRL_RESERVED3_MASK                                                       (0x18000000U)

#define TCTRL_PSTRB_REPLAY_COUNTER_SHIFT                                                (25U)
#define TCTRL_PSTRB_REPLAY_COUNTER_MASK                                                 (0xfe000000U)

#define TCTRL_PSTRB_REPLAY_DELAY_SHIFT                                                  (0U)
#define TCTRL_PSTRB_REPLAY_DELAY_MASK                                                   (0x01ffffffU)

#define TCTRL_FRAME_SHUT_SHIFT                                                          (0U)
#define TCTRL_FRAME_SHUT_MASK                                                           (0x0000003fU)

#define TCTRL_FRAME_PSTRB_SHIFT                                                         (6U)
#define TCTRL_FRAME_PSTRB_MASK                                                          (0x00000fc0U)

#define TCTRL_FRAME_STRB_SHIFT                                                          (12U)
#define TCTRL_FRAME_STRB_MASK                                                           (0x0003f000U)

#define TCTRL_FRAME_RESERVED_SHIFT                                                      (18U)
#define TCTRL_FRAME_RESERVED_MASK                                                       (0xfffc0000U)

#define ISS_ICM_A_TC_SYNC_SHIFT                                                         (0U)
#define ISS_ICM_A_TC_SYNC_MASK                                                          (0x000000ffU)

#define ISS_ICM_A_TC_RESYNC_SHIFT                                                       (16U)
#define ISS_ICM_A_TC_RESYNC_MASK                                                        (0x00ff0000U)

#define ISS_ICM_A_TC_RESERVED_SHIFT                                                     (8U)
#define ISS_ICM_A_TC_RESERVED_MASK                                                      (0x0000ff00U)

#define ISS_ICM_A_TC_RESERVED1_SHIFT                                                    (24U)
#define ISS_ICM_A_TC_RESERVED1_MASK                                                     (0xff000000U)

#define ISS_ICM_A_CME_CONSUMER_SHIFT                                                    (0U)
#define ISS_ICM_A_CME_CONSUMER_MASK                                                     (0x0000003fU)

#define ISS_ICM_A_CME_PRODUCER_SHIFT                                                    (16U)
#define ISS_ICM_A_CME_PRODUCER_MASK                                                     (0x003f0000U)

#define ISS_ICM_A_CME_RESERVED_SHIFT                                                    (6U)
#define ISS_ICM_A_CME_RESERVED_MASK                                                     (0x0000ffc0U)

#define ISS_ICM_A_CME_RESERVED1_SHIFT                                                   (22U)
#define ISS_ICM_A_CME_RESERVED1_MASK                                                    (0xffc00000U)

#define ISS_ICM_B_TC_SYNC_SHIFT                                                         (0U)
#define ISS_ICM_B_TC_SYNC_MASK                                                          (0x000000ffU)

#define ISS_ICM_B_TC_RESERVED_SHIFT                                                     (8U)
#define ISS_ICM_B_TC_RESERVED_MASK                                                      (0x0000ff00U)

#define ISS_ICM_B_TC_RESYNC_SHIFT                                                       (16U)
#define ISS_ICM_B_TC_RESYNC_MASK                                                        (0x00ff0000U)

#define ISS_ICM_B_TC_RESERVED1_SHIFT                                                    (24U)
#define ISS_ICM_B_TC_RESERVED1_MASK                                                     (0xff000000U)

#define ISS_REQINFO_MAP0_7_0_SHIFT                                                      (0U)
#define ISS_REQINFO_MAP0_7_0_MASK                                                       (0x00000007U)

#define ISS_REQINFO_MAP0_7_1_SHIFT                                                      (4U)
#define ISS_REQINFO_MAP0_7_1_MASK                                                       (0x00000070U)

#define ISS_REQINFO_MAP0_7_2_SHIFT                                                      (8U)
#define ISS_REQINFO_MAP0_7_2_MASK                                                       (0x00000700U)

#define ISS_REQINFO_MAP0_7_3_SHIFT                                                      (12U)
#define ISS_REQINFO_MAP0_7_3_MASK                                                       (0x00007000U)

#define ISS_REQINFO_MAP0_7_4_SHIFT                                                      (16U)
#define ISS_REQINFO_MAP0_7_4_MASK                                                       (0x00070000U)

#define ISS_REQINFO_MAP0_7_5_SHIFT                                                      (20U)
#define ISS_REQINFO_MAP0_7_5_MASK                                                       (0x00700000U)

#define ISS_REQINFO_MAP0_7_6_SHIFT                                                      (24U)
#define ISS_REQINFO_MAP0_7_6_MASK                                                       (0x07000000U)

#define ISS_REQINFO_MAP0_7_SHIFT                                                        (28U)
#define ISS_REQINFO_MAP0_7_MASK                                                         (0x70000000U)

#define ISS_REQINFO_MAP0_7_RESERVED_SHIFT                                               (3U)
#define ISS_REQINFO_MAP0_7_RESERVED_MASK                                                (0x00000008U)

#define ISS_REQINFO_MAP0_7_RESERVED1_SHIFT                                              (7U)
#define ISS_REQINFO_MAP0_7_RESERVED1_MASK                                               (0x00000080U)

#define ISS_REQINFO_MAP0_7_RESERVED2_SHIFT                                              (11U)
#define ISS_REQINFO_MAP0_7_RESERVED2_MASK                                               (0x00000800U)

#define ISS_REQINFO_MAP0_7_RESERVED3_SHIFT                                              (15U)
#define ISS_REQINFO_MAP0_7_RESERVED3_MASK                                               (0x00008000U)

#define ISS_REQINFO_MAP0_7_RESERVED4_SHIFT                                              (19U)
#define ISS_REQINFO_MAP0_7_RESERVED4_MASK                                               (0x00080000U)

#define ISS_REQINFO_MAP0_7_RESERVED5_SHIFT                                              (23U)
#define ISS_REQINFO_MAP0_7_RESERVED5_MASK                                               (0x00800000U)

#define ISS_REQINFO_MAP0_7_RESERVED6_SHIFT                                              (27U)
#define ISS_REQINFO_MAP0_7_RESERVED6_MASK                                               (0x08000000U)

#define ISS_REQINFO_MAP0_7_RESERVED7_SHIFT                                              (31U)
#define ISS_REQINFO_MAP0_7_RESERVED7_MASK                                               (0x80000000U)

#define ISS_REQINFO_MAP8_15_8_SHIFT                                                     (0U)
#define ISS_REQINFO_MAP8_15_8_MASK                                                      (0x00000007U)

#define ISS_REQINFO_MAP8_15_9_SHIFT                                                     (4U)
#define ISS_REQINFO_MAP8_15_9_MASK                                                      (0x00000070U)

#define ISS_REQINFO_MAP8_15_10_SHIFT                                                    (8U)
#define ISS_REQINFO_MAP8_15_10_MASK                                                     (0x00000700U)

#define ISS_REQINFO_MAP8_15_11_SHIFT                                                    (12U)
#define ISS_REQINFO_MAP8_15_11_MASK                                                     (0x00007000U)

#define ISS_REQINFO_MAP8_15_12_SHIFT                                                    (16U)
#define ISS_REQINFO_MAP8_15_12_MASK                                                     (0x00070000U)

#define ISS_REQINFO_MAP8_15_13_SHIFT                                                    (20U)
#define ISS_REQINFO_MAP8_15_13_MASK                                                     (0x00700000U)

#define ISS_REQINFO_MAP8_15_14_SHIFT                                                    (24U)
#define ISS_REQINFO_MAP8_15_14_MASK                                                     (0x07000000U)

#define ISS_REQINFO_MAP8_15_SHIFT                                                       (28U)
#define ISS_REQINFO_MAP8_15_MASK                                                        (0x70000000U)

#define ISS_REQINFO_MAP8_15_RESERVED_SHIFT                                              (3U)
#define ISS_REQINFO_MAP8_15_RESERVED_MASK                                               (0x00000008U)

#define ISS_REQINFO_MAP8_15_RESERVED1_SHIFT                                             (7U)
#define ISS_REQINFO_MAP8_15_RESERVED1_MASK                                              (0x00000080U)

#define ISS_REQINFO_MAP8_15_RESERVED2_SHIFT                                             (11U)
#define ISS_REQINFO_MAP8_15_RESERVED2_MASK                                              (0x00000800U)

#define ISS_REQINFO_MAP8_15_RESERVED3_SHIFT                                             (15U)
#define ISS_REQINFO_MAP8_15_RESERVED3_MASK                                              (0x00008000U)

#define ISS_REQINFO_MAP8_15_RESERVED4_SHIFT                                             (19U)
#define ISS_REQINFO_MAP8_15_RESERVED4_MASK                                              (0x00080000U)

#define ISS_REQINFO_MAP8_15_RESERVED5_SHIFT                                             (23U)
#define ISS_REQINFO_MAP8_15_RESERVED5_MASK                                              (0x00800000U)

#define ISS_REQINFO_MAP8_15_RESERVED6_SHIFT                                             (27U)
#define ISS_REQINFO_MAP8_15_RESERVED6_MASK                                              (0x08000000U)

#define ISS_REQINFO_MAP8_15_RESERVED7_SHIFT                                             (31U)
#define ISS_REQINFO_MAP8_15_RESERVED7_MASK                                              (0x80000000U)

#define ISS_REQINFO_MAP16_23_16_SHIFT                                                   (0U)
#define ISS_REQINFO_MAP16_23_16_MASK                                                    (0x00000007U)

#define ISS_REQINFO_MAP16_23_17_SHIFT                                                   (4U)
#define ISS_REQINFO_MAP16_23_17_MASK                                                    (0x00000070U)

#define ISS_REQINFO_MAP16_23_18_SHIFT                                                   (8U)
#define ISS_REQINFO_MAP16_23_18_MASK                                                    (0x00000700U)

#define ISS_REQINFO_MAP16_23_19_SHIFT                                                   (12U)
#define ISS_REQINFO_MAP16_23_19_MASK                                                    (0x00007000U)

#define ISS_REQINFO_MAP16_23_20_SHIFT                                                   (16U)
#define ISS_REQINFO_MAP16_23_20_MASK                                                    (0x00070000U)

#define ISS_REQINFO_MAP16_23_21_SHIFT                                                   (20U)
#define ISS_REQINFO_MAP16_23_21_MASK                                                    (0x00700000U)

#define ISS_REQINFO_MAP16_23_22_SHIFT                                                   (24U)
#define ISS_REQINFO_MAP16_23_22_MASK                                                    (0x07000000U)

#define ISS_REQINFO_MAP16_23_SHIFT                                                      (28U)
#define ISS_REQINFO_MAP16_23_MASK                                                       (0x70000000U)

#define ISS_REQINFO_MAP16_23_RESERVED_SHIFT                                             (3U)
#define ISS_REQINFO_MAP16_23_RESERVED_MASK                                              (0x00000008U)

#define ISS_REQINFO_MAP16_23_RESERVED1_SHIFT                                            (7U)
#define ISS_REQINFO_MAP16_23_RESERVED1_MASK                                             (0x00000080U)

#define ISS_REQINFO_MAP16_23_RESERVED2_SHIFT                                            (11U)
#define ISS_REQINFO_MAP16_23_RESERVED2_MASK                                             (0x00000800U)

#define ISS_REQINFO_MAP16_23_RESERVED3_SHIFT                                            (15U)
#define ISS_REQINFO_MAP16_23_RESERVED3_MASK                                             (0x00008000U)

#define ISS_REQINFO_MAP16_23_RESERVED4_SHIFT                                            (19U)
#define ISS_REQINFO_MAP16_23_RESERVED4_MASK                                             (0x00080000U)

#define ISS_REQINFO_MAP16_23_RESERVED5_SHIFT                                            (23U)
#define ISS_REQINFO_MAP16_23_RESERVED5_MASK                                             (0x00800000U)

#define ISS_REQINFO_MAP16_23_RESERVED6_SHIFT                                            (27U)
#define ISS_REQINFO_MAP16_23_RESERVED6_MASK                                             (0x08000000U)

#define ISS_REQINFO_MAP16_23_RESERVED7_SHIFT                                            (31U)
#define ISS_REQINFO_MAP16_23_RESERVED7_MASK                                             (0x80000000U)

#define ISS_REQINFO_MAP24_31_24_SHIFT                                                   (0U)
#define ISS_REQINFO_MAP24_31_24_MASK                                                    (0x00000007U)

#define ISS_REQINFO_MAP24_31_25_SHIFT                                                   (4U)
#define ISS_REQINFO_MAP24_31_25_MASK                                                    (0x00000070U)

#define ISS_REQINFO_MAP24_31_26_SHIFT                                                   (8U)
#define ISS_REQINFO_MAP24_31_26_MASK                                                    (0x00000700U)

#define ISS_REQINFO_MAP24_31_27_SHIFT                                                   (12U)
#define ISS_REQINFO_MAP24_31_27_MASK                                                    (0x00007000U)

#define ISS_REQINFO_MAP24_31_28_SHIFT                                                   (16U)
#define ISS_REQINFO_MAP24_31_28_MASK                                                    (0x00070000U)

#define ISS_REQINFO_MAP24_31_29_SHIFT                                                   (20U)
#define ISS_REQINFO_MAP24_31_29_MASK                                                    (0x00700000U)

#define ISS_REQINFO_MAP24_31_30_SHIFT                                                   (24U)
#define ISS_REQINFO_MAP24_31_30_MASK                                                    (0x07000000U)

#define ISS_REQINFO_MAP24_31_SHIFT                                                      (28U)
#define ISS_REQINFO_MAP24_31_MASK                                                       (0x70000000U)

#define ISS_REQINFO_MAP24_31_RESERVED_SHIFT                                             (3U)
#define ISS_REQINFO_MAP24_31_RESERVED_MASK                                              (0x00000008U)

#define ISS_REQINFO_MAP24_31_RESERVED1_SHIFT                                            (7U)
#define ISS_REQINFO_MAP24_31_RESERVED1_MASK                                             (0x00000080U)

#define ISS_REQINFO_MAP24_31_RESERVED2_SHIFT                                            (11U)
#define ISS_REQINFO_MAP24_31_RESERVED2_MASK                                             (0x00000800U)

#define ISS_REQINFO_MAP24_31_RESERVED3_SHIFT                                            (15U)
#define ISS_REQINFO_MAP24_31_RESERVED3_MASK                                             (0x00008000U)

#define ISS_REQINFO_MAP24_31_RESERVED4_SHIFT                                            (19U)
#define ISS_REQINFO_MAP24_31_RESERVED4_MASK                                             (0x00080000U)

#define ISS_REQINFO_MAP24_31_RESERVED5_SHIFT                                            (23U)
#define ISS_REQINFO_MAP24_31_RESERVED5_MASK                                             (0x00800000U)

#define ISS_REQINFO_MAP24_31_RESERVED6_SHIFT                                            (27U)
#define ISS_REQINFO_MAP24_31_RESERVED6_MASK                                             (0x08000000U)

#define ISS_REQINFO_MAP24_31_RESERVED7_SHIFT                                            (31U)
#define ISS_REQINFO_MAP24_31_RESERVED7_MASK                                             (0x80000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_REGS_H_ */

