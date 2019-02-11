/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

#ifndef HW_VIP_H_
#define HW_VIP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define VIP_CLKC_PID                                                                                        (0x0U)
#define VIP_SYSCONFIG                                                                                       (0x10U)
#define VIP_INTC_INTR0_STATUS_RAW0                                                                          (0x20U)
#define VIP_INTC_INTR0_STATUS_RAW1                                                                          (0x24U)
#define VIP_INTC_INTR0_STATUS0                                                                              (0x28U)
#define VIP_INTC_INTR0_STATUS1                                                                              (0x2cU)
#define VIP_INTC_INTR0_ENA_SET0                                                                             (0x30U)
#define VIP_INTC_INTR0_ENA_SET1                                                                             (0x34U)
#define VIP_INTC_INTR0_ENA_CLR0                                                                             (0x38U)
#define VIP_INTC_INTR0_ENA_CLR1                                                                             (0x3cU)
#define VIP_INTC_INTR1_STATUS_RAW0                                                                          (0x40U)
#define VIP_INTC_INTR1_STATUS_RAW1                                                                          (0x44U)
#define VIP_INTC_INTR1_STATUS0                                                                              (0x48U)
#define VIP_INTC_INTR1_STATUS1                                                                              (0x4cU)
#define VIP_INTC_INTR1_ENA_SET0                                                                             (0x50U)
#define VIP_INTC_INTR1_ENA_SET1                                                                             (0x54U)
#define VIP_INTC_INTR1_ENA_CLR0                                                                             (0x58U)
#define VIP_INTC_INTR1_ENA_CLR1                                                                             (0x5cU)
#define VIP_INTC_EOI                                                                                        (0xa0U)
#define VIP_CLKC_CLKEN                                                                                      (0x100U)
#define VIP_CLKC_RST                                                                                        (0x104U)
#define VIP_CLKC_DPS                                                                                        (0x108U)
#define VIP_CLKC_S0_DPS                                                                                     (0x10cU)
#define VIP_CLKC_S1_DPS                                                                                     (0x110U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define VIP_CLKC_PID_SCHEME_SHIFT                                                                           (30U)
#define VIP_CLKC_PID_SCHEME_MASK                                                                            (0xc0000000U)

#define VIP_CLKC_PID_FUNC_SHIFT                                                                             (16U)
#define VIP_CLKC_PID_FUNC_MASK                                                                              (0x0fff0000U)

#define VIP_CLKC_PID_RTL_SHIFT                                                                              (11U)
#define VIP_CLKC_PID_RTL_MASK                                                                               (0x0000f800U)

#define VIP_CLKC_PID_MAJOR_SHIFT                                                                            (8U)
#define VIP_CLKC_PID_MAJOR_MASK                                                                             (0x00000700U)

#define VIP_CLKC_PID_CUSTOM_SHIFT                                                                           (6U)
#define VIP_CLKC_PID_CUSTOM_MASK                                                                            (0x000000c0U)

#define VIP_CLKC_PID_MINOR_SHIFT                                                                            (0U)
#define VIP_CLKC_PID_MINOR_MASK                                                                             (0x0000003fU)

#define VIP_SYSCONFIG_IDLEMODE_SHIFT                                                                        (2U)
#define VIP_SYSCONFIG_IDLEMODE_MASK                                                                         (0x0000000cU)

#define VIP_SYSCONFIG_STANDBYMODE_SHIFT                                                                     (4U)
#define VIP_SYSCONFIG_STANDBYMODE_MASK                                                                      (0x00000030U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                          (0U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_COMPLETE_MASK                                           (0x00000001U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                            (1U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST0_NOTIFY_MASK                                             (0x00000002U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                          (2U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_COMPLETE_MASK                                           (0x00000004U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                            (3U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST1_NOTIFY_MASK                                             (0x00000008U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                          (4U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_COMPLETE_MASK                                           (0x00000010U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                            (5U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST2_NOTIFY_MASK                                             (0x00000020U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                          (6U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_COMPLETE_MASK                                           (0x00000040U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                            (7U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST3_NOTIFY_MASK                                             (0x00000080U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                          (8U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_COMPLETE_MASK                                           (0x00000100U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                            (9U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST4_NOTIFY_MASK                                             (0x00000200U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                          (10U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_COMPLETE_MASK                                           (0x00000400U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                            (11U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST5_NOTIFY_MASK                                             (0x00000800U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                          (12U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_COMPLETE_MASK                                           (0x00001000U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                            (13U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST6_NOTIFY_MASK                                             (0x00002000U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                          (14U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_COMPLETE_MASK                                           (0x00004000U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                            (15U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_LIST7_NOTIFY_MASK                                             (0x00008000U)

#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_DESCRIPTOR_SHIFT                                              (16U)
#define VIP_INTC_INTR0_STATUS_RAW0_VPDMA_INT0_DESCRIPTOR_MASK                                               (0x00010000U)

#define VIP_INTC_INTR0_STATUS_RAW0_S0_PARSER_INT_SHIFT                                                      (20U)
#define VIP_INTC_INTR0_STATUS_RAW0_S0_PARSER_INT_MASK                                                       (0x00100000U)

#define VIP_INTC_INTR0_STATUS_RAW0_S1_PARSER_INT_SHIFT                                                      (21U)
#define VIP_INTC_INTR0_STATUS_RAW0_S1_PARSER_INT_MASK                                                       (0x00200000U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                          (0U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                           (0x00000001U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                          (1U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                           (0x00000002U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                          (2U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                           (0x00000004U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                          (3U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                           (0x00000008U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                          (4U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                           (0x00000010U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                          (5U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                           (0x00000020U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP6_SHIFT                                          (6U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CHANNEL_GROUP6_MASK                                           (0x00000040U)

#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CLIENT_SHIFT                                                  (7U)
#define VIP_INTC_INTR0_STATUS_RAW1_VPDMA_INT0_CLIENT_MASK                                                   (0x00000080U)

#define VIP_INTC_INTR0_STATUS_RAW1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                             (22U)
#define VIP_INTC_INTR0_STATUS_RAW1_S0_CHR_DS_0_UV_ERR_INT_MASK                                              (0x00400000U)

#define VIP_INTC_INTR0_STATUS_RAW1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                             (23U)
#define VIP_INTC_INTR0_STATUS_RAW1_S0_CHR_DS_1_UV_ERR_INT_MASK                                              (0x00800000U)

#define VIP_INTC_INTR0_STATUS_RAW1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                             (24U)
#define VIP_INTC_INTR0_STATUS_RAW1_S1_CHR_DS_0_UV_ERR_INT_MASK                                              (0x01000000U)

#define VIP_INTC_INTR0_STATUS_RAW1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                             (25U)
#define VIP_INTC_INTR0_STATUS_RAW1_S1_CHR_DS_1_UV_ERR_INT_MASK                                              (0x02000000U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                              (0U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_COMPLETE_MASK                                               (0x00000001U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                                (1U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                 (0x00000002U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                              (2U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_COMPLETE_MASK                                               (0x00000004U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                                (3U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                 (0x00000008U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                              (4U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_COMPLETE_MASK                                               (0x00000010U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                                (5U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                 (0x00000020U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                              (6U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_COMPLETE_MASK                                               (0x00000040U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                                (7U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                 (0x00000080U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                              (8U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_COMPLETE_MASK                                               (0x00000100U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                                (9U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                 (0x00000200U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                              (10U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_COMPLETE_MASK                                               (0x00000400U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                                (11U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                 (0x00000800U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                              (12U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_COMPLETE_MASK                                               (0x00001000U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                                (13U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                 (0x00002000U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                              (14U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_COMPLETE_MASK                                               (0x00004000U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                                (15U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                 (0x00008000U)

#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                  (16U)
#define VIP_INTC_INTR0_STATUS0_VPDMA_INT0_DESCRIPTOR_MASK                                                   (0x00010000U)

#define VIP_INTC_INTR0_STATUS0_S0_PARSER_INT_SHIFT                                                          (20U)
#define VIP_INTC_INTR0_STATUS0_S0_PARSER_INT_MASK                                                           (0x00100000U)

#define VIP_INTC_INTR0_STATUS0_S1_PARSER_INT_SHIFT                                                          (21U)
#define VIP_INTC_INTR0_STATUS0_S1_PARSER_INT_MASK                                                           (0x00200000U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                              (0U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                               (0x00000001U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                              (1U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                               (0x00000002U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                              (2U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                               (0x00000004U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                              (3U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                               (0x00000008U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                              (4U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                               (0x00000010U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                              (5U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                               (0x00000020U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP6_SHIFT                                              (6U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CHANNEL_GROUP6_MASK                                               (0x00000040U)

#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CLIENT_SHIFT                                                      (7U)
#define VIP_INTC_INTR0_STATUS1_VPDMA_INT0_CLIENT_MASK                                                       (0x00000080U)

#define VIP_INTC_INTR0_STATUS1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                 (22U)
#define VIP_INTC_INTR0_STATUS1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                  (0x00400000U)

#define VIP_INTC_INTR0_STATUS1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                 (23U)
#define VIP_INTC_INTR0_STATUS1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                  (0x00800000U)

#define VIP_INTC_INTR0_STATUS1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                 (24U)
#define VIP_INTC_INTR0_STATUS1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                  (0x01000000U)

#define VIP_INTC_INTR0_STATUS1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                 (25U)
#define VIP_INTC_INTR0_STATUS1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                  (0x02000000U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                             (0U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                               (1U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                             (2U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                               (3U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                             (4U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                               (5U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                             (6U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                               (7U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                             (8U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                               (9U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                             (10U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                               (11U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                             (12U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                               (13U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                             (14U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                               (15U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                 (16U)
#define VIP_INTC_INTR0_ENA_SET0_VPDMA_INT0_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VIP_INTC_INTR0_ENA_SET0_S0_PARSER_INT_SHIFT                                                         (20U)
#define VIP_INTC_INTR0_ENA_SET0_S0_PARSER_INT_MASK                                                          (0x00100000U)

#define VIP_INTC_INTR0_ENA_SET0_S1_PARSER_INT_SHIFT                                                         (21U)
#define VIP_INTC_INTR0_ENA_SET0_S1_PARSER_INT_MASK                                                          (0x00200000U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP6_SHIFT                                             (6U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CHANNEL_GROUP6_MASK                                              (0x00000040U)

#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CLIENT_SHIFT                                                     (7U)
#define VIP_INTC_INTR0_ENA_SET1_VPDMA_INT0_CLIENT_MASK                                                      (0x00000080U)

#define VIP_INTC_INTR0_ENA_SET1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                (22U)
#define VIP_INTC_INTR0_ENA_SET1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x00400000U)

#define VIP_INTC_INTR0_ENA_SET1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                (23U)
#define VIP_INTC_INTR0_ENA_SET1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x00800000U)

#define VIP_INTC_INTR0_ENA_SET1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                (24U)
#define VIP_INTC_INTR0_ENA_SET1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x01000000U)

#define VIP_INTC_INTR0_ENA_SET1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                (25U)
#define VIP_INTC_INTR0_ENA_SET1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x02000000U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_COMPLETE_SHIFT                                             (0U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_NOTIFY_SHIFT                                               (1U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_COMPLETE_SHIFT                                             (2U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_NOTIFY_SHIFT                                               (3U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_COMPLETE_SHIFT                                             (4U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_NOTIFY_SHIFT                                               (5U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_COMPLETE_SHIFT                                             (6U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_NOTIFY_SHIFT                                               (7U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_COMPLETE_SHIFT                                             (8U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_NOTIFY_SHIFT                                               (9U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_COMPLETE_SHIFT                                             (10U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_NOTIFY_SHIFT                                               (11U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_COMPLETE_SHIFT                                             (12U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_NOTIFY_SHIFT                                               (13U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_COMPLETE_SHIFT                                             (14U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_NOTIFY_SHIFT                                               (15U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_DESCRIPTOR_SHIFT                                                 (16U)
#define VIP_INTC_INTR0_ENA_CLR0_VPDMA_INT0_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VIP_INTC_INTR0_ENA_CLR0_S0_PARSER_INT_SHIFT                                                         (20U)
#define VIP_INTC_INTR0_ENA_CLR0_S0_PARSER_INT_MASK                                                          (0x00100000U)

#define VIP_INTC_INTR0_ENA_CLR0_S1_PARSER_INT_SHIFT                                                         (21U)
#define VIP_INTC_INTR0_ENA_CLR0_S1_PARSER_INT_MASK                                                          (0x00200000U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP6_SHIFT                                             (6U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CHANNEL_GROUP6_MASK                                              (0x00000040U)

#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CLIENT_SHIFT                                                     (7U)
#define VIP_INTC_INTR0_ENA_CLR1_VPDMA_INT0_CLIENT_MASK                                                      (0x00000080U)

#define VIP_INTC_INTR0_ENA_CLR1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                (22U)
#define VIP_INTC_INTR0_ENA_CLR1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x00400000U)

#define VIP_INTC_INTR0_ENA_CLR1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                (23U)
#define VIP_INTC_INTR0_ENA_CLR1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x00800000U)

#define VIP_INTC_INTR0_ENA_CLR1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                (24U)
#define VIP_INTC_INTR0_ENA_CLR1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x01000000U)

#define VIP_INTC_INTR0_ENA_CLR1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                (25U)
#define VIP_INTC_INTR0_ENA_CLR1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x02000000U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST0_COMPLETE_SHIFT                                          (0U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST0_COMPLETE_MASK                                           (0x00000001U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST0_NOTIFY_SHIFT                                            (1U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST0_NOTIFY_MASK                                             (0x00000002U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST1_COMPLETE_SHIFT                                          (2U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST1_COMPLETE_MASK                                           (0x00000004U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST1_NOTIFY_SHIFT                                            (3U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST1_NOTIFY_MASK                                             (0x00000008U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST2_COMPLETE_SHIFT                                          (4U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST2_COMPLETE_MASK                                           (0x00000010U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST2_NOTIFY_SHIFT                                            (5U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST2_NOTIFY_MASK                                             (0x00000020U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST3_COMPLETE_SHIFT                                          (6U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST3_COMPLETE_MASK                                           (0x00000040U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST3_NOTIFY_SHIFT                                            (7U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST3_NOTIFY_MASK                                             (0x00000080U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST4_COMPLETE_SHIFT                                          (8U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST4_COMPLETE_MASK                                           (0x00000100U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST4_NOTIFY_SHIFT                                            (9U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST4_NOTIFY_MASK                                             (0x00000200U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST5_COMPLETE_SHIFT                                          (10U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST5_COMPLETE_MASK                                           (0x00000400U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST5_NOTIFY_SHIFT                                            (11U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST5_NOTIFY_MASK                                             (0x00000800U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST6_COMPLETE_SHIFT                                          (12U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST6_COMPLETE_MASK                                           (0x00001000U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST6_NOTIFY_SHIFT                                            (13U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST6_NOTIFY_MASK                                             (0x00002000U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST7_COMPLETE_SHIFT                                          (14U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST7_COMPLETE_MASK                                           (0x00004000U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST7_NOTIFY_SHIFT                                            (15U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_LIST7_NOTIFY_MASK                                             (0x00008000U)

#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_DESCRIPTOR_SHIFT                                              (16U)
#define VIP_INTC_INTR1_STATUS_RAW0_VPDMA_INT1_DESCRIPTOR_MASK                                               (0x00010000U)

#define VIP_INTC_INTR1_STATUS_RAW0_S0_PARSER_INT_SHIFT                                                      (20U)
#define VIP_INTC_INTR1_STATUS_RAW0_S0_PARSER_INT_MASK                                                       (0x00100000U)

#define VIP_INTC_INTR1_STATUS_RAW0_S1_PARSER_INT_SHIFT                                                      (21U)
#define VIP_INTC_INTR1_STATUS_RAW0_S1_PARSER_INT_MASK                                                       (0x00200000U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP0_SHIFT                                          (0U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP0_MASK                                           (0x00000001U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP1_SHIFT                                          (1U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP1_MASK                                           (0x00000002U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP2_SHIFT                                          (2U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP2_MASK                                           (0x00000004U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP3_SHIFT                                          (3U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP3_MASK                                           (0x00000008U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP4_SHIFT                                          (4U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP4_MASK                                           (0x00000010U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP5_SHIFT                                          (5U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP5_MASK                                           (0x00000020U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP6_SHIFT                                          (6U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CHANNEL_GROUP6_MASK                                           (0x00000040U)

#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CLIENT_SHIFT                                                  (7U)
#define VIP_INTC_INTR1_STATUS_RAW1_VPDMA_INT1_CLIENT_MASK                                                   (0x00000080U)

#define VIP_INTC_INTR1_STATUS_RAW1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                             (22U)
#define VIP_INTC_INTR1_STATUS_RAW1_S0_CHR_DS_0_UV_ERR_INT_MASK                                              (0x00400000U)

#define VIP_INTC_INTR1_STATUS_RAW1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                             (23U)
#define VIP_INTC_INTR1_STATUS_RAW1_S0_CHR_DS_1_UV_ERR_INT_MASK                                              (0x00800000U)

#define VIP_INTC_INTR1_STATUS_RAW1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                             (24U)
#define VIP_INTC_INTR1_STATUS_RAW1_S1_CHR_DS_0_UV_ERR_INT_MASK                                              (0x01000000U)

#define VIP_INTC_INTR1_STATUS_RAW1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                             (25U)
#define VIP_INTC_INTR1_STATUS_RAW1_S1_CHR_DS_1_UV_ERR_INT_MASK                                              (0x02000000U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST0_COMPLETE_SHIFT                                              (0U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST0_COMPLETE_MASK                                               (0x00000001U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST0_NOTIFY_SHIFT                                                (1U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST0_NOTIFY_MASK                                                 (0x00000002U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST1_COMPLETE_SHIFT                                              (2U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST1_COMPLETE_MASK                                               (0x00000004U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST1_NOTIFY_SHIFT                                                (3U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST1_NOTIFY_MASK                                                 (0x00000008U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST2_COMPLETE_SHIFT                                              (4U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST2_COMPLETE_MASK                                               (0x00000010U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST2_NOTIFY_SHIFT                                                (5U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST2_NOTIFY_MASK                                                 (0x00000020U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST3_COMPLETE_SHIFT                                              (6U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST3_COMPLETE_MASK                                               (0x00000040U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST3_NOTIFY_SHIFT                                                (7U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST3_NOTIFY_MASK                                                 (0x00000080U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST4_COMPLETE_SHIFT                                              (8U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST4_COMPLETE_MASK                                               (0x00000100U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST4_NOTIFY_SHIFT                                                (9U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST4_NOTIFY_MASK                                                 (0x00000200U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST5_COMPLETE_SHIFT                                              (10U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST5_COMPLETE_MASK                                               (0x00000400U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST5_NOTIFY_SHIFT                                                (11U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST5_NOTIFY_MASK                                                 (0x00000800U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST6_COMPLETE_SHIFT                                              (12U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST6_COMPLETE_MASK                                               (0x00001000U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST6_NOTIFY_SHIFT                                                (13U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST6_NOTIFY_MASK                                                 (0x00002000U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST7_COMPLETE_SHIFT                                              (14U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST7_COMPLETE_MASK                                               (0x00004000U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST7_NOTIFY_SHIFT                                                (15U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_LIST7_NOTIFY_MASK                                                 (0x00008000U)

#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_DESCRIPTOR_SHIFT                                                  (16U)
#define VIP_INTC_INTR1_STATUS0_VPDMA_INT1_DESCRIPTOR_MASK                                                   (0x00010000U)

#define VIP_INTC_INTR1_STATUS0_S0_PARSER_INT_SHIFT                                                          (20U)
#define VIP_INTC_INTR1_STATUS0_S0_PARSER_INT_MASK                                                           (0x00100000U)

#define VIP_INTC_INTR1_STATUS0_S1_PARSER_INT_SHIFT                                                          (21U)
#define VIP_INTC_INTR1_STATUS0_S1_PARSER_INT_MASK                                                           (0x00200000U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP0_SHIFT                                              (0U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP0_MASK                                               (0x00000001U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP1_SHIFT                                              (1U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP1_MASK                                               (0x00000002U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP2_SHIFT                                              (2U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP2_MASK                                               (0x00000004U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP3_SHIFT                                              (3U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP3_MASK                                               (0x00000008U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP4_SHIFT                                              (4U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP4_MASK                                               (0x00000010U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP5_SHIFT                                              (5U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP5_MASK                                               (0x00000020U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP6_SHIFT                                              (6U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CHANNEL_GROUP6_MASK                                               (0x00000040U)

#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CLIENT_SHIFT                                                      (7U)
#define VIP_INTC_INTR1_STATUS1_VPDMA_INT1_CLIENT_MASK                                                       (0x00000080U)

#define VIP_INTC_INTR1_STATUS1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                 (22U)
#define VIP_INTC_INTR1_STATUS1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                  (0x00400000U)

#define VIP_INTC_INTR1_STATUS1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                 (23U)
#define VIP_INTC_INTR1_STATUS1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                  (0x00800000U)

#define VIP_INTC_INTR1_STATUS1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                 (24U)
#define VIP_INTC_INTR1_STATUS1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                  (0x01000000U)

#define VIP_INTC_INTR1_STATUS1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                 (25U)
#define VIP_INTC_INTR1_STATUS1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                  (0x02000000U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST0_COMPLETE_SHIFT                                             (0U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST0_NOTIFY_SHIFT                                               (1U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST1_COMPLETE_SHIFT                                             (2U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST1_NOTIFY_SHIFT                                               (3U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST2_COMPLETE_SHIFT                                             (4U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST2_NOTIFY_SHIFT                                               (5U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST3_COMPLETE_SHIFT                                             (6U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST3_NOTIFY_SHIFT                                               (7U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST4_COMPLETE_SHIFT                                             (8U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST4_NOTIFY_SHIFT                                               (9U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST5_COMPLETE_SHIFT                                             (10U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST5_NOTIFY_SHIFT                                               (11U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST6_COMPLETE_SHIFT                                             (12U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST6_NOTIFY_SHIFT                                               (13U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST7_COMPLETE_SHIFT                                             (14U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST7_NOTIFY_SHIFT                                               (15U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_DESCRIPTOR_SHIFT                                                 (16U)
#define VIP_INTC_INTR1_ENA_SET0_VPDMA_INT1_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VIP_INTC_INTR1_ENA_SET0_S0_PARSER_INT_SHIFT                                                         (20U)
#define VIP_INTC_INTR1_ENA_SET0_S0_PARSER_INT_MASK                                                          (0x00100000U)

#define VIP_INTC_INTR1_ENA_SET0_S1_PARSER_INT_SHIFT                                                         (21U)
#define VIP_INTC_INTR1_ENA_SET0_S1_PARSER_INT_MASK                                                          (0x00200000U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP6_SHIFT                                             (6U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CHANNEL_GROUP6_MASK                                              (0x00000040U)

#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CLIENT_SHIFT                                                     (7U)
#define VIP_INTC_INTR1_ENA_SET1_VPDMA_INT1_CLIENT_MASK                                                      (0x00000080U)

#define VIP_INTC_INTR1_ENA_SET1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                (22U)
#define VIP_INTC_INTR1_ENA_SET1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x00400000U)

#define VIP_INTC_INTR1_ENA_SET1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                (23U)
#define VIP_INTC_INTR1_ENA_SET1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x00800000U)

#define VIP_INTC_INTR1_ENA_SET1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                (24U)
#define VIP_INTC_INTR1_ENA_SET1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x01000000U)

#define VIP_INTC_INTR1_ENA_SET1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                (25U)
#define VIP_INTC_INTR1_ENA_SET1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x02000000U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST0_COMPLETE_SHIFT                                             (0U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST0_COMPLETE_MASK                                              (0x00000001U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST0_NOTIFY_SHIFT                                               (1U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST0_NOTIFY_MASK                                                (0x00000002U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST1_COMPLETE_SHIFT                                             (2U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST1_COMPLETE_MASK                                              (0x00000004U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST1_NOTIFY_SHIFT                                               (3U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST1_NOTIFY_MASK                                                (0x00000008U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST2_COMPLETE_SHIFT                                             (4U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST2_COMPLETE_MASK                                              (0x00000010U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST2_NOTIFY_SHIFT                                               (5U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST2_NOTIFY_MASK                                                (0x00000020U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST3_COMPLETE_SHIFT                                             (6U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST3_COMPLETE_MASK                                              (0x00000040U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST3_NOTIFY_SHIFT                                               (7U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST3_NOTIFY_MASK                                                (0x00000080U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST4_COMPLETE_SHIFT                                             (8U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST4_COMPLETE_MASK                                              (0x00000100U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST4_NOTIFY_SHIFT                                               (9U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST4_NOTIFY_MASK                                                (0x00000200U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST5_COMPLETE_SHIFT                                             (10U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST5_COMPLETE_MASK                                              (0x00000400U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST5_NOTIFY_SHIFT                                               (11U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST5_NOTIFY_MASK                                                (0x00000800U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST6_COMPLETE_SHIFT                                             (12U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST6_COMPLETE_MASK                                              (0x00001000U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST6_NOTIFY_SHIFT                                               (13U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST6_NOTIFY_MASK                                                (0x00002000U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST7_COMPLETE_SHIFT                                             (14U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST7_COMPLETE_MASK                                              (0x00004000U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST7_NOTIFY_SHIFT                                               (15U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_LIST7_NOTIFY_MASK                                                (0x00008000U)

#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_DESCRIPTOR_SHIFT                                                 (16U)
#define VIP_INTC_INTR1_ENA_CLR0_VPDMA_INT1_DESCRIPTOR_MASK                                                  (0x00010000U)

#define VIP_INTC_INTR1_ENA_CLR0_S0_PARSER_INT_SHIFT                                                         (20U)
#define VIP_INTC_INTR1_ENA_CLR0_S0_PARSER_INT_MASK                                                          (0x00100000U)

#define VIP_INTC_INTR1_ENA_CLR0_S1_PARSER_INT_SHIFT                                                         (21U)
#define VIP_INTC_INTR1_ENA_CLR0_S1_PARSER_INT_MASK                                                          (0x00200000U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP0_SHIFT                                             (0U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP0_MASK                                              (0x00000001U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP1_SHIFT                                             (1U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP1_MASK                                              (0x00000002U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP2_SHIFT                                             (2U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP2_MASK                                              (0x00000004U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP3_SHIFT                                             (3U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP3_MASK                                              (0x00000008U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP4_SHIFT                                             (4U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP4_MASK                                              (0x00000010U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP5_SHIFT                                             (5U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP5_MASK                                              (0x00000020U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP6_SHIFT                                             (6U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CHANNEL_GROUP6_MASK                                              (0x00000040U)

#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CLIENT_SHIFT                                                     (7U)
#define VIP_INTC_INTR1_ENA_CLR1_VPDMA_INT1_CLIENT_MASK                                                      (0x00000080U)

#define VIP_INTC_INTR1_ENA_CLR1_S0_CHR_DS_0_UV_ERR_INT_SHIFT                                                (22U)
#define VIP_INTC_INTR1_ENA_CLR1_S0_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x00400000U)

#define VIP_INTC_INTR1_ENA_CLR1_S0_CHR_DS_1_UV_ERR_INT_SHIFT                                                (23U)
#define VIP_INTC_INTR1_ENA_CLR1_S0_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x00800000U)

#define VIP_INTC_INTR1_ENA_CLR1_S1_CHR_DS_0_UV_ERR_INT_SHIFT                                                (24U)
#define VIP_INTC_INTR1_ENA_CLR1_S1_CHR_DS_0_UV_ERR_INT_MASK                                                 (0x01000000U)

#define VIP_INTC_INTR1_ENA_CLR1_S1_CHR_DS_1_UV_ERR_INT_SHIFT                                                (25U)
#define VIP_INTC_INTR1_ENA_CLR1_S1_CHR_DS_1_UV_ERR_INT_MASK                                                 (0x02000000U)

#define VIP_INTC_EOI_EOI_VECTOR_SHIFT                                                                       (0U)
#define VIP_INTC_EOI_EOI_VECTOR_MASK                                                                        (0xffffffffU)

#define VIP_CLKC_CLKEN_S1_DP_EN_SHIFT                                                                       (17U)
#define VIP_CLKC_CLKEN_S1_DP_EN_MASK                                                                        (0x00020000U)

#define VIP_CLKC_CLKEN_S0_DP_EN_SHIFT                                                                       (16U)
#define VIP_CLKC_CLKEN_S0_DP_EN_MASK                                                                        (0x00010000U)

#define VIP_CLKC_CLKEN_VPDMA_EN_SHIFT                                                                       (0U)
#define VIP_CLKC_CLKEN_VPDMA_EN_MASK                                                                        (0x00000001U)

#define VIP_CLKC_RST_MAIN_RST_SHIFT                                                                         (31U)
#define VIP_CLKC_RST_MAIN_RST_MASK                                                                          (0x80000000U)

#define VIP_CLKC_RST_S1_DP_RST_SHIFT                                                                        (17U)
#define VIP_CLKC_RST_S1_DP_RST_MASK                                                                         (0x00020000U)

#define VIP_CLKC_RST_S0_DP_RST_SHIFT                                                                        (16U)
#define VIP_CLKC_RST_S0_DP_RST_MASK                                                                         (0x00010000U)

#define VIP_CLKC_RST_VPDMA_RST_SHIFT                                                                        (0U)
#define VIP_CLKC_RST_VPDMA_RST_MASK                                                                         (0x00000001U)

#define VIP_CLKC_RST_S0_PARSER_RST_SHIFT                                                                    (18U)
#define VIP_CLKC_RST_S0_PARSER_RST_MASK                                                                     (0x00040000U)

#define VIP_CLKC_RST_S1_PARSER_RST_SHIFT                                                                    (19U)
#define VIP_CLKC_RST_S1_PARSER_RST_MASK                                                                     (0x00080000U)

#define VIP_CLKC_RST_S0_CSC_RST_SHIFT                                                                       (20U)
#define VIP_CLKC_RST_S0_CSC_RST_MASK                                                                        (0x00100000U)

#define VIP_CLKC_RST_S1_CSC_RST_SHIFT                                                                       (21U)
#define VIP_CLKC_RST_S1_CSC_RST_MASK                                                                        (0x00200000U)

#define VIP_CLKC_RST_S0_SC_RST_SHIFT                                                                        (22U)
#define VIP_CLKC_RST_S0_SC_RST_MASK                                                                         (0x00400000U)

#define VIP_CLKC_RST_S1_SC_RST_SHIFT                                                                        (23U)
#define VIP_CLKC_RST_S1_SC_RST_MASK                                                                         (0x00800000U)

#define VIP_CLKC_RST_S0_CHR_DS_0_RST_SHIFT                                                                  (25U)
#define VIP_CLKC_RST_S0_CHR_DS_0_RST_MASK                                                                   (0x02000000U)

#define VIP_CLKC_RST_S1_CHR_DS_0_RST_SHIFT                                                                  (26U)
#define VIP_CLKC_RST_S1_CHR_DS_0_RST_MASK                                                                   (0x04000000U)

#define VIP_CLKC_RST_S0_CHR_DS_1_RST_SHIFT                                                                  (27U)
#define VIP_CLKC_RST_S0_CHR_DS_1_RST_MASK                                                                   (0x08000000U)

#define VIP_CLKC_RST_S1_CHR_DS_1_RST_SHIFT                                                                  (28U)
#define VIP_CLKC_RST_S1_CHR_DS_1_RST_MASK                                                                   (0x10000000U)

#define VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT_SHIFT                                                            (28U)
#define VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT_MASK                                                             (0xf0000000U)

#define VIP_CLKC_S0_DPS_S0_TESTPORT_A_SELECT_SHIFT                                                          (27U)
#define VIP_CLKC_S0_DPS_S0_TESTPORT_A_SELECT_MASK                                                           (0x08000000U)

#define VIP_CLKC_S0_DPS_S0_TESTPORT_B_SELECT_SHIFT                                                          (26U)
#define VIP_CLKC_S0_DPS_S0_TESTPORT_B_SELECT_MASK                                                           (0x04000000U)

#define VIP_CLKC_S0_DPS_S0_CHR_DS_1_BYPASS_SHIFT                                                            (17U)
#define VIP_CLKC_S0_DPS_S0_CHR_DS_1_BYPASS_MASK                                                             (0x00020000U)

#define VIP_CLKC_S0_DPS_S0_CHR_DS_0_BYPASS_SHIFT                                                            (16U)
#define VIP_CLKC_S0_DPS_S0_CHR_DS_0_BYPASS_MASK                                                             (0x00010000U)

#define VIP_CLKC_S0_DPS_S0_MULTI_CHANNEL_SELECT_SHIFT                                                       (15U)
#define VIP_CLKC_S0_DPS_S0_MULTI_CHANNEL_SELECT_MASK                                                        (0x00008000U)

#define VIP_CLKC_S0_DPS_S0_CHR_DS_1_SRC_SELECT_SHIFT                                                        (12U)
#define VIP_CLKC_S0_DPS_S0_CHR_DS_1_SRC_SELECT_MASK                                                         (0x00007000U)

#define VIP_CLKC_S0_DPS_S0_CHR_DS_0_SRC_SELECT_SHIFT                                                        (9U)
#define VIP_CLKC_S0_DPS_S0_CHR_DS_0_SRC_SELECT_MASK                                                         (0x00000e00U)

#define VIP_CLKC_S0_DPS_S0_RGB_OUT_HI_SELECT_SHIFT                                                          (8U)
#define VIP_CLKC_S0_DPS_S0_RGB_OUT_HI_SELECT_MASK                                                           (0x00000100U)

#define VIP_CLKC_S0_DPS_S0_RGB_OUT_LO_SELECT_SHIFT                                                          (7U)
#define VIP_CLKC_S0_DPS_S0_RGB_OUT_LO_SELECT_MASK                                                           (0x00000080U)

#define VIP_CLKC_S0_DPS_S0_RGB_SRC_SELECT_SHIFT                                                             (6U)
#define VIP_CLKC_S0_DPS_S0_RGB_SRC_SELECT_MASK                                                              (0x00000040U)

#define VIP_CLKC_S0_DPS_S0_SC_SRC_SELECT_SHIFT                                                              (3U)
#define VIP_CLKC_S0_DPS_S0_SC_SRC_SELECT_MASK                                                               (0x00000038U)

#define VIP_CLKC_S0_DPS_S0_CSC_SRC_SELECT_SHIFT                                                             (0U)
#define VIP_CLKC_S0_DPS_S0_CSC_SRC_SELECT_MASK                                                              (0x00000007U)

#define VIP_CLKC_S1_DPS_S1_DATAPATH_SELECT_SHIFT                                                            (28U)
#define VIP_CLKC_S1_DPS_S1_DATAPATH_SELECT_MASK                                                             (0xf0000000U)

#define VIP_CLKC_S1_DPS_S1_TESTPORT_A_SELECT_SHIFT                                                          (27U)
#define VIP_CLKC_S1_DPS_S1_TESTPORT_A_SELECT_MASK                                                           (0x08000000U)

#define VIP_CLKC_S1_DPS_VIP1_TESTPORT_B_SELECT_SHIFT                                                        (26U)
#define VIP_CLKC_S1_DPS_VIP1_TESTPORT_B_SELECT_MASK                                                         (0x04000000U)

#define VIP_CLKC_S1_DPS_S1_CHR_DS_1_BYPASS_SHIFT                                                            (17U)
#define VIP_CLKC_S1_DPS_S1_CHR_DS_1_BYPASS_MASK                                                             (0x00020000U)

#define VIP_CLKC_S1_DPS_S1_CHR_DS_0_BYPASS_SHIFT                                                            (16U)
#define VIP_CLKC_S1_DPS_S1_CHR_DS_0_BYPASS_MASK                                                             (0x00010000U)

#define VIP_CLKC_S1_DPS_S1_MULTI_CHANNEL_SELECT_SHIFT                                                       (15U)
#define VIP_CLKC_S1_DPS_S1_MULTI_CHANNEL_SELECT_MASK                                                        (0x00008000U)

#define VIP_CLKC_S1_DPS_S1_CHR_DS_1_SRC_SELECT_SHIFT                                                        (12U)
#define VIP_CLKC_S1_DPS_S1_CHR_DS_1_SRC_SELECT_MASK                                                         (0x00007000U)

#define VIP_CLKC_S1_DPS_S1_CHR_DS_0_SRC_SELECT_SHIFT                                                        (9U)
#define VIP_CLKC_S1_DPS_S1_CHR_DS_0_SRC_SELECT_MASK                                                         (0x00000e00U)

#define VIP_CLKC_S1_DPS_S1_RGB_OUT_HI_SELECT_SHIFT                                                          (8U)
#define VIP_CLKC_S1_DPS_S1_RGB_OUT_HI_SELECT_MASK                                                           (0x00000100U)

#define VIP_CLKC_S1_DPS_S1_RGB_OUT_LO_SELECT_SHIFT                                                          (7U)
#define VIP_CLKC_S1_DPS_S1_RGB_OUT_LO_SELECT_MASK                                                           (0x00000080U)

#define VIP_CLKC_S1_DPS_S1_RGB_SRC_SELECT_SHIFT                                                             (6U)
#define VIP_CLKC_S1_DPS_S1_RGB_SRC_SELECT_MASK                                                              (0x00000040U)

#define VIP_CLKC_S1_DPS_S1_SC_SRC_SELECT_SHIFT                                                              (3U)
#define VIP_CLKC_S1_DPS_S1_SC_SRC_SELECT_MASK                                                               (0x00000038U)

#define VIP_CLKC_S1_DPS_S1_CSC_SRC_SELECT_SHIFT                                                             (0U)
#define VIP_CLKC_S1_DPS_S1_CSC_SRC_SELECT_MASK                                                              (0x00000007U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_VIP_H_ */
