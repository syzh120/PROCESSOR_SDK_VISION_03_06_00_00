/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2015
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

/**
 *  \file       hw_vpe.h
 *
 *  \brief      register-level header file for VPE
 *
**/

#ifndef HW_VPE_H_
#define HW_VPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define VPE_CLKC_PID                                                                                        (0x0U)
#define VPE_SYSCONFIG                                                                                       (0x10U)
#define VPE_INTC_INTR0_STATUS_RAW0                                                                          (0x20U)
#define VPE_INTC_INTR0_STATUS_RAW1                                                                          (0x24U)
#define VPE_INTC_INTR0_STATUS0                                                                              (0x28U)
#define VPE_INTC_INTR0_STATUS1                                                                              (0x2cU)
#define VPE_INTC_INTR0_ENA_SET0                                                                             (0x30U)
#define VPE_INTC_INTR0_ENA_SET1                                                                             (0x34U)
#define VPE_INTC_INTR0_ENA_CLR0                                                                             (0x38U)
#define VPE_INTC_INTR0_ENA_CLR1                                                                             (0x3cU)
#define VPE_INTC_EOI                                                                                        (0xa0U)
#define VPE_CLKC_CLKEN                                                                                      (0x100U)
#define VPE_CLKC_RST                                                                                        (0x104U)
#define VPE_CLKC_DPS                                                                                        (0x10cU)
#define VPE_RANGE_MAP                                                                                       (0x11cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define VPE_CLKC_PID_SCHEME_SHIFT                                                                           (30U)
#define VPE_CLKC_PID_SCHEME_MASK                                                                            (0xc0000000U)

#define VPE_CLKC_PID_FUNC_SHIFT                                                                             (16U)
#define VPE_CLKC_PID_FUNC_MASK                                                                              (0x0fff0000U)

#define VPE_CLKC_PID_RTL_SHIFT                                                                              (11U)
#define VPE_CLKC_PID_RTL_MASK                                                                               (0x0000f800U)

#define VPE_CLKC_PID_MAJOR_SHIFT                                                                            (8U)
#define VPE_CLKC_PID_MAJOR_MASK                                                                             (0x00000700U)

#define VPE_CLKC_PID_CUSTOM_SHIFT                                                                           (6U)
#define VPE_CLKC_PID_CUSTOM_MASK                                                                            (0x000000c0U)

#define VPE_CLKC_PID_MINOR_SHIFT                                                                            (0U)
#define VPE_CLKC_PID_MINOR_MASK                                                                             (0x0000003fU)

#define VPE_SYSCONFIG_IDLEMODE_SHIFT                                                                        (2U)
#define VPE_SYSCONFIG_IDLEMODE_MASK                                                                         (0x0000000cU)

#define VPE_SYSCONFIG_STANDBYMODE_SHIFT                                                                     (4U)
#define VPE_SYSCONFIG_STANDBYMODE_MASK                                                                      (0x00000030U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                          (0U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_COMPLETE_MASK                                           (0x00000001U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                            (1U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_NOTIFY_MASK                                             (0x00000002U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                          (2U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_COMPLETE_MASK                                           (0x00000004U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                            (3U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_NOTIFY_MASK                                             (0x00000008U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                          (4U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_COMPLETE_MASK                                           (0x00000010U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                            (5U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_NOTIFY_MASK                                             (0x00000020U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                          (6U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_COMPLETE_MASK                                           (0x00000040U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                            (7U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_NOTIFY_MASK                                             (0x00000080U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                          (8U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_COMPLETE_MASK                                           (0x00000100U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                            (9U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_NOTIFY_MASK                                             (0x00000200U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                          (10U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_COMPLETE_MASK                                           (0x00000400U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                            (11U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_NOTIFY_MASK                                             (0x00000800U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                          (12U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_COMPLETE_MASK                                           (0x00001000U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                            (13U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_NOTIFY_MASK                                             (0x00002000U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                          (14U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_COMPLETE_MASK                                           (0x00004000U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                            (15U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_NOTIFY_MASK                                             (0x00008000U)

#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_DESCRIPTOR_SHIFT                                              (16U)
#define VPE_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_DESCRIPTOR_MASK                                               (0x00010000U)

#define VPE_INTC_INTR0_STATUS_RAW0_DEI_FMD_INT_SHIFT                                                        (18U)
#define VPE_INTC_INTR0_STATUS_RAW0_DEI_FMD_INT_MASK                                                         (0x00040000U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                          (0U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                           (0x00000001U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                          (1U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                           (0x00000002U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                          (2U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                           (0x00000004U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                          (3U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                           (0x00000008U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                          (4U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                           (0x00000010U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                          (5U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                           (0x00000020U)

#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CLIENT_SHIFT                                                  (7U)
#define VPE_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CLIENT_MASK                                                   (0x00000080U)

#define VPE_INTC_INTR0_STATUS_RAW1_DEI_ERROR_INT_SHIFT                                                      (16U)
#define VPE_INTC_INTR0_STATUS_RAW1_DEI_ERROR_INT_MASK                                                       (0x00010000U)

#define VPE_INTC_INTR0_STATUS_RAW1_CHR_DS_UV_ERR_INT_SHIFT                                                  (22U)
#define VPE_INTC_INTR0_STATUS_RAW1_CHR_DS_UV_ERR_INT_MASK                                                   (0x00400000U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                              (0U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_COMPLETE_MASK                                               (0x00000001U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                                (1U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                 (0x00000002U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                              (2U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_COMPLETE_MASK                                               (0x00000004U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                                (3U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                 (0x00000008U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                              (4U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_COMPLETE_MASK                                               (0x00000010U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                                (5U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                 (0x00000020U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                              (6U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_COMPLETE_MASK                                               (0x00000040U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                                (7U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                 (0x00000080U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                              (8U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_COMPLETE_MASK                                               (0x00000100U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                                (9U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                 (0x00000200U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                              (10U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_COMPLETE_MASK                                               (0x00000400U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                                (11U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                 (0x00000800U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                              (12U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_COMPLETE_MASK                                               (0x00001000U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                                (13U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                 (0x00002000U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                              (14U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_COMPLETE_MASK                                               (0x00004000U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                                (15U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                 (0x00008000U)

#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                  (16U)
#define VPE_INTC_INTR0_STATUS0_VPDMA_INT0_DESCRIPTOR_MASK                                                   (0x00010000U)

#define VPE_INTC_INTR0_STATUS0_DEI_FMD_INT_SHIFT                                                            (18U)
#define VPE_INTC_INTR0_STATUS0_DEI_FMD_INT_MASK                                                             (0x00040000U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                              (0U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                               (0x00000001U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                              (1U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                               (0x00000002U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                              (2U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                               (0x00000004U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                              (3U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                               (0x00000008U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                              (4U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                               (0x00000010U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                              (5U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                               (0x00000020U)

#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CLIENT_SHIFT                                                      (7U)
#define VPE_INTC_INTR0_STATUS1_VPDMA_INT0_CLIENT_MASK                                                       (0x00000080U)

#define VPE_INTC_INTR0_STATUS1_DEI_ERROR_INT_SHIFT                                                          (16U)
#define VPE_INTC_INTR0_STATUS1_DEI_ERROR_INT_MASK                                                           (0x00010000U)

#define VPE_INTC_INTR0_STATUS1_CHR_DS_UV_ERR_INT_SHIFT                                                      (22U)
#define VPE_INTC_INTR0_STATUS1_CHR_DS_UV_ERR_INT_MASK                                                       (0x00400000U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                             (0U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                               (1U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                             (2U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                               (3U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                             (4U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                               (5U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                             (6U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                               (7U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                             (8U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                               (9U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                             (10U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                               (11U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                             (12U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                               (13U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                             (14U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                               (15U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                 (16U)
#define VPE_INTC_INTR0_ENA_SET0_VPDMA_INT0_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VPE_INTC_INTR0_ENA_SET0_DEI_FMD_INT_SHIFT                                                           (18U)
#define VPE_INTC_INTR0_ENA_SET0_DEI_FMD_INT_MASK                                                            (0x00040000U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CLIENT_SHIFT                                                     (7U)
#define VPE_INTC_INTR0_ENA_SET1_VPDMA_INT0_CLIENT_MASK                                                      (0x00000080U)

#define VPE_INTC_INTR0_ENA_SET1_DEI_ERROR_INT_SHIFT                                                         (16U)
#define VPE_INTC_INTR0_ENA_SET1_DEI_ERROR_INT_MASK                                                          (0x00010000U)

#define VPE_INTC_INTR0_ENA_SET1_CHR_DS_UV_ERR_INT_SHIFT                                                     (22U)
#define VPE_INTC_INTR0_ENA_SET1_CHR_DS_UV_ERR_INT_MASK                                                      (0x00400000U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                             (0U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                               (1U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                             (2U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                               (3U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                             (4U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                               (5U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                             (6U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                               (7U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                             (8U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                               (9U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                             (10U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                               (11U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                             (12U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                               (13U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                             (14U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                               (15U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                 (16U)
#define VPE_INTC_INTR0_ENA_CLR0_VPDMA_INT0_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VPE_INTC_INTR0_ENA_CLR0_DEI_FMD_INT_SHIFT                                                           (18U)
#define VPE_INTC_INTR0_ENA_CLR0_DEI_FMD_INT_MASK                                                            (0x00040000U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CLIENT_SHIFT                                                     (7U)
#define VPE_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CLIENT_MASK                                                      (0x00000080U)

#define VPE_INTC_INTR0_ENA_CLR1_DEI_ERROR_INT_SHIFT                                                         (16U)
#define VPE_INTC_INTR0_ENA_CLR1_DEI_ERROR_INT_MASK                                                          (0x00010000U)

#define VPE_INTC_INTR0_ENA_CLR1_CHR_DS_UV_ERR_INT_SHIFT                                                     (22U)
#define VPE_INTC_INTR0_ENA_CLR1_CHR_DS_UV_ERR_INT_MASK                                                      (0x00400000U)

#define VPE_INTC_EOI_EOI_VECTOR_SHIFT                                                                       (0U)
#define VPE_INTC_EOI_EOI_VECTOR_MASK                                                                        (0xffffffffU)

#define VPE_CLKC_CLKEN_VPDMA_EN_SHIFT                                                                       (0U)
#define VPE_CLKC_CLKEN_VPDMA_EN_MASK                                                                        (0x00000001U)

#define VPE_CLKC_CLKEN_PRIM_DP_EN_SHIFT                                                                     (1U)
#define VPE_CLKC_CLKEN_PRIM_DP_EN_MASK                                                                      (0x00000002U)

#define VPE_CLKC_RST_MAIN_RST_SHIFT                                                                         (31U)
#define VPE_CLKC_RST_MAIN_RST_MASK                                                                          (0x80000000U)

#define VPE_CLKC_RST_PRIM_DP_RST_SHIFT                                                                      (1U)
#define VPE_CLKC_RST_PRIM_DP_RST_MASK                                                                       (0x00000002U)

#define VPE_CLKC_RST_VPDMA_RST_SHIFT                                                                        (0U)
#define VPE_CLKC_RST_VPDMA_RST_MASK                                                                         (0x00000001U)

#define VPE_CLKC_DPS_COLOR_SEPARATE_422_SHIFT                                                               (18U)
#define VPE_CLKC_DPS_COLOR_SEPARATE_422_MASK                                                                (0x00040000U)

#define VPE_CLKC_DPS_CHR_DS_BYPASS_SHIFT                                                                    (16U)
#define VPE_CLKC_DPS_CHR_DS_BYPASS_MASK                                                                     (0x00010000U)

#define VPE_CLKC_DPS_CHR_DS_SRC_SELECT_SHIFT                                                                (9U)
#define VPE_CLKC_DPS_CHR_DS_SRC_SELECT_MASK                                                                 (0x00000e00U)

#define VPE_CLKC_DPS_RGB_OUT_SELECT_SHIFT                                                                   (8U)
#define VPE_CLKC_DPS_RGB_OUT_SELECT_MASK                                                                    (0x00000100U)

#define VPE_CLKC_DPS_CSC_SRC_SELECT_SHIFT                                                                   (0U)
#define VPE_CLKC_DPS_CSC_SRC_SELECT_MASK                                                                    (0x00000007U)

#define VPE_RANGE_MAP_ENABLE_RANGE_REDUCTION_PRIM_SHIFT                                                     (28U)
#define VPE_RANGE_MAP_ENABLE_RANGE_REDUCTION_PRIM_MASK                                                      (0x10000000U)

#define VPE_RANGE_MAP_ENABLE_RANGE_MAP_PRIM_SHIFT                                                           (6U)
#define VPE_RANGE_MAP_ENABLE_RANGE_MAP_PRIM_MASK                                                            (0x00000040U)

#define VPE_RANGE_MAP_RANGE_MAPUV_PRIM_SHIFT                                                                (3U)
#define VPE_RANGE_MAP_RANGE_MAPUV_PRIM_MASK                                                                 (0x00000038U)

#define VPE_RANGE_MAP_RANGE_MAPY_PRIM_SHIFT                                                                 (0U)
#define VPE_RANGE_MAP_RANGE_MAPY_PRIM_MASK                                                                  (0x00000007U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_VPE_H_ */

