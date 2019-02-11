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

#ifndef HW_ISS_LVDSRX_H_
#define HW_ISS_LVDSRX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define LVDSRX_REVISION                                             (uint32_t)(0x0U)
#define LVDSRX_SYSCONFIG                                            (uint32_t)(0x10U)
#define LVDSRX_CAMCFG                                               (uint32_t)(0x14U)
#define LVDSRX_IRQ_EOI                                              (uint32_t)(0x1cU)
#define LVDSRX_IRQSTATUS_RAW_0                                      (uint32_t)(0x20U)
#define LVDSRX_IRQSTATUS_0                                          (uint32_t)(0x24U)
#define LVDSRX_IRQENABLE_SET_0                                      (uint32_t)(0x28U)
#define LVDSRX_IRQENABLE_CLR_0                                      (uint32_t)(0x2cU)
#define LVDSRX_IRQSTATUS_RAW_1                                      (uint32_t)(0x30U)
#define LVDSRX_IRQSTATUS_1                                          (uint32_t)(0x34U)
#define LVDSRX_IRQENABLE_SET_1                                      (uint32_t)(0x38U)
#define LVDSRX_IRQENABLE_CLR_1                                      (uint32_t)(0x3cU)
#define LVDSRX_IRQSTATUS_RAW2_2                                     (uint32_t)(0x40U)
#define LVDSRX_IRQSTATUS_2                                          (uint32_t)(0x44U)
#define LVDSRX_IRQENABLE_SET_2                                      (uint32_t)(0x48U)
#define LVDSRX_IRQENABLE_CLR_2                                      (uint32_t)(0x4cU)
#define LVDSRX_IRQSTATUS_RAW_3                                      (uint32_t)(0x50U)
#define LVDSRX_IRQSTATUS_3                                          (uint32_t)(0x54U)
#define LVDSRX_IRQENABLE_SET_3                                      (uint32_t)(0x58U)
#define LVDSRX_IRQENABLE_CLR_3                                      (uint32_t)(0x5cU)
#define LVDSRX_CAM1_CFG                                             (uint32_t)(0x60U)
#define LVDSRX_CAM1_FRMSIZE                                         (uint32_t)(0x64U)
#define LVDSRX_CAM1_MAXWIDTH                                        (uint32_t)(0x68U)
#define LVDSRX_CAM1_SYNCSOF                                         (uint32_t)(0x6cU)
#define LVDSRX_CAM1_SYNCEOF                                         (uint32_t)(0x70U)
#define LVDSRX_CAM1_SYNCSOL                                         (uint32_t)(0x74U)
#define LVDSRX_CAM1_SYNCEOL                                         (uint32_t)(0x78U)
#define LVDSRX_CAM1_SYNCSOV                                         (uint32_t)(0x7cU)
#define LVDSRX_CAM2_CFG                                             (uint32_t)(0x80U)
#define LVDSRX_CAM2_FRMSIZE                                         (uint32_t)(0x84U)
#define LVDSRX_CAM2_MAXWIDTH                                        (uint32_t)(0x88U)
#define LVDSRX_CAM2_SYNCSOF                                         (uint32_t)(0x8cU)
#define LVDSRX_CAM2_SYNCEOF                                         (uint32_t)(0x90U)
#define LVDSRX_CAM2_SYNCSOL                                         (uint32_t)(0x94U)
#define LVDSRX_CAM2_SYNCEOL                                         (uint32_t)(0x98U)
#define LVDSRX_CAM2_SYNCSOV                                         (uint32_t)(0x9cU)
#define LVDSRX_CAM3_CFG                                             (uint32_t)(0xa0U)
#define LVDSRX_CAM3_FRMSIZE                                         (uint32_t)(0xa4U)
#define LVDSRX_CAM3_MAXWIDTH                                        (uint32_t)(0xa8U)
#define LVDSRX_CAM3_SYNCSOF                                         (uint32_t)(0xacU)
#define LVDSRX_CAM3_SYNCEOF                                         (uint32_t)(0xb0U)
#define LVDSRX_CAM3_SYNCSOL                                         (uint32_t)(0xb4U)
#define LVDSRX_CAM3_SYNCEOL                                         (uint32_t)(0xb8U)
#define LVDSRX_CAM3_SYNCSOV                                         (uint32_t)(0xbcU)
#define LVDSRX_CAM4_CFG                                             (uint32_t)(0xc0U)
#define LVDSRX_CAM4_FRMSIZE                                         (uint32_t)(0xc4U)
#define LVDSRX_CAM4_MAXWIDTH                                        (uint32_t)(0xc8U)
#define LVDSRX_CAM4_SYNCSOF                                         (uint32_t)(0xccU)
#define LVDSRX_CAM4_SYNCEOF                                         (uint32_t)(0xd0U)
#define LVDSRX_CAM4_SYNCSOL                                         (uint32_t)(0xd4U)
#define LVDSRX_CAM4_SYNCEOL                                         (uint32_t)(0xd8U)
#define LVDSRX_CAM4_SYNCSOV                                         (uint32_t)(0xdcU)
#define LVDSRX_WDRCFG                                               (uint32_t)(0xe0U)
#define LVDSRX_WDRGN                                                (uint32_t)(0xe4U)
#define LVDSRX_WDRKP1                                               (uint32_t)(0xe8U)
#define LVDSRX_WDRKP2                                               (uint32_t)(0xecU)
#define LVDSRX_TEST1                                                (uint32_t)(0x100U)
#define LVDSRX_TEST2                                                (uint32_t)(0x104U)
#define LVDSRX_TEST3                                                (uint32_t)(0x108U)
#define LVDSRX_TEST4                                                (uint32_t)(0x10cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define LVDSRX_REVISION_Y_MINOR_SHIFT                                                   (0U)
#define LVDSRX_REVISION_Y_MINOR_MASK                                                    (0x0000003fU)

#define LVDSRX_REVISION_CUSTOM_SHIFT                                                    (6U)
#define LVDSRX_REVISION_CUSTOM_MASK                                                     (0x000000c0U)
#define LVDSRX_REVISION_CUSTOM_STANDARD                                                  (0U)

#define LVDSRX_REVISION_X_MAJOR_SHIFT                                                   (8U)
#define LVDSRX_REVISION_X_MAJOR_MASK                                                    (0x00000700U)

#define LVDSRX_REVISION_R_RTL_SHIFT                                                     (11U)
#define LVDSRX_REVISION_R_RTL_MASK                                                      (0x0000f800U)

#define LVDSRX_REVISION_FUNC_SHIFT                                                      (16U)
#define LVDSRX_REVISION_FUNC_MASK                                                       (0x0fff0000U)

#define LVDSRX_REVISION_SCHEME_SHIFT                                                    (30U)
#define LVDSRX_REVISION_SCHEME_MASK                                                     (0xc0000000U)
#define LVDSRX_REVISION_SCHEME_LEGACY                                                    (0U)
#define LVDSRX_REVISION_SCHEME_H08                                                       (1U)

#define LVDSRX_REVISION_RESERVED_SHIFT                                                  (28U)
#define LVDSRX_REVISION_RESERVED_MASK                                                   (0x30000000U)

#define LVDSRX_SYSCONFIG_RESERVED_SHIFT                                                 (0U)
#define LVDSRX_SYSCONFIG_RESERVED_MASK                                                  (0x00000001U)
#define LVDSRX_SYSCONFIG_RESERVED_DONE                                                   (0U)
#define LVDSRX_SYSCONFIG_RESERVED_NOACTION                                               (0U)
#define LVDSRX_SYSCONFIG_RESERVED_RESET                                                  (1U)
#define LVDSRX_SYSCONFIG_RESERVED_PENDING                                                (1U)

#define LVDSRX_SYSCONFIG_RESERVED1_SHIFT                                                (1U)
#define LVDSRX_SYSCONFIG_RESERVED1_MASK                                                 (0xfffffffeU)

#define LVDSRX_CAMCFG_CAM1ENA_SHIFT                                                     (0U)
#define LVDSRX_CAMCFG_CAM1ENA_MASK                                                      (0x00000001U)
#define LVDSRX_CAMCFG_CAM1ENA_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM1ENA_ENABLE                                                    (0x00000001U)

#define LVDSRX_CAMCFG_CAM2ENA_SHIFT                                                     (1U)
#define LVDSRX_CAMCFG_CAM2ENA_MASK                                                      (0x00000002U)
#define LVDSRX_CAMCFG_CAM2ENA_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM2ENA_ENABLE                                                    (0x00000002U)

#define LVDSRX_CAMCFG_CAM3ENA_SHIFT                                                     (2U)
#define LVDSRX_CAMCFG_CAM3ENA_MASK                                                      (0x00000004U)
#define LVDSRX_CAMCFG_CAM3ENA_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM3ENA_ENABLE                                                    (0x00000004U)

#define LVDSRX_CAMCFG_CAM4ENA_SHIFT                                                     (3U)
#define LVDSRX_CAMCFG_CAM4ENA_MASK                                                      (0x00000008U)
#define LVDSRX_CAMCFG_CAM4ENA_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM4ENA_ENABLE                                                    (0x00000008U)

#define LVDSRX_CAMCFG_RESERVED2_SHIFT                                                   (20U)
#define LVDSRX_CAMCFG_RESERVED2_MASK                                                    (0xfff00000U)

#define LVDSRX_CAMCFG_CAM1TEST_SHIFT                                                    (16U)
#define LVDSRX_CAMCFG_CAM1TEST_MASK                                                     (0x00010000U)
#define LVDSRX_CAMCFG_CAM1TEST_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM1TEST_ENABLE                                                    (1U)

#define LVDSRX_CAMCFG_CAM2TEST_SHIFT                                                    (17U)
#define LVDSRX_CAMCFG_CAM2TEST_MASK                                                     (0x00020000U)
#define LVDSRX_CAMCFG_CAM2TEST_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM2TEST_ENABLE                                                    (1U)

#define LVDSRX_CAMCFG_CAM3TEST_SHIFT                                                    (18U)
#define LVDSRX_CAMCFG_CAM3TEST_MASK                                                     (0x00040000U)
#define LVDSRX_CAMCFG_CAM3TEST_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM3TEST_ENABLE                                                    (1U)

#define LVDSRX_CAMCFG_CAM4TEST_SHIFT                                                    (19U)
#define LVDSRX_CAMCFG_CAM4TEST_MASK                                                     (0x00080000U)
#define LVDSRX_CAMCFG_CAM4TEST_DIABLE                                                    (0U)
#define LVDSRX_CAMCFG_CAM4TEST_ENABLE                                                    (1U)

#define LVDSRX_CAMCFG_RESERVED1_SHIFT                                                   (4U)
#define LVDSRX_CAMCFG_RESERVED1_MASK                                                    (0x0000fff0U)

#define LVDSRX_IRQ_EOI_LINE_NUMBER_SHIFT                                                (0U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_MASK                                                 (0x00000007U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_EOI1                                                  (1U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_READ0                                                 (0U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_EOI2                                                  (2U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_EOI3                                                  (3U)
#define LVDSRX_IRQ_EOI_LINE_NUMBER_EOI4                                                  (4U)

#define LVDSRX_IRQ_EOI_RESERVED_SHIFT                                                   (3U)
#define LVDSRX_IRQ_EOI_RESERVED_MASK                                                    (0xfffffff8U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_SOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_SOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_RAW_0_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQSTATUS_RAW_0_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR0_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR0_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR1_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR1_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR2_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR2_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR3_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR3_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR4_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR4_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR5_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR5_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR6_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR6_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR7_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_ERR7_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_0_CAM1_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_EOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_0_CAM1_EOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_SOF_SHIFT                                               (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_SOF_MASK                                                (0x00000001U)
#define LVDSRX_IRQSTATUS_0_CAM1_SOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_SOF_PENDING                                              (1U)

#define LVDSRX_IRQSTATUS_0_RESERVED_SHIFT                                               (10U)
#define LVDSRX_IRQSTATUS_0_RESERVED_MASK                                                (0xfffffc00U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR0_SHIFT                                              (2U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR0_MASK                                               (0x00000004U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR0_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR0_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR1_SHIFT                                              (3U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR1_MASK                                               (0x00000008U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR1_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR1_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR2_SHIFT                                              (4U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR2_MASK                                               (0x00000010U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR2_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR2_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR3_SHIFT                                              (5U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR3_MASK                                               (0x00000020U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR3_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR3_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR4_SHIFT                                              (6U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR4_MASK                                               (0x00000040U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR4_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR4_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR5_SHIFT                                              (7U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR5_MASK                                               (0x00000080U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR5_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR5_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR6_SHIFT                                              (8U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR6_MASK                                               (0x00000100U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR6_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR6_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_ERR7_SHIFT                                              (9U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR7_MASK                                               (0x00000200U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR7_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_ERR7_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_0_CAM1_EOF_SHIFT                                               (1U)
#define LVDSRX_IRQSTATUS_0_CAM1_EOF_MASK                                                (0x00000002U)
#define LVDSRX_IRQSTATUS_0_CAM1_EOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_0_CAM1_EOF_PENDING                                              (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_SOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_SET_0_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_SET_0_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR0_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR1_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR2_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR3_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR4_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR5_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR6_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_ERR7_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_0_CAM1_EOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_SOF_DISABLE                                          (1U)

#define LVDSRX_IRQENABLE_CLR_0_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_CLR_0_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR0_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR1_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR2_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR3_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR4_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR5_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR6_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_ERR7_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_0_CAM1_EOF_DISABLE                                          (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_SOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_SOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_RAW_1_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQSTATUS_RAW_1_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR0_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR0_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR1_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR1_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR2_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR2_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR3_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR3_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR4_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR4_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR5_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR5_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR6_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR6_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR7_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_ERR7_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_1_CAM2_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_EOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_1_CAM2_EOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_SOF_SHIFT                                               (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_SOF_MASK                                                (0x00000001U)
#define LVDSRX_IRQSTATUS_1_CAM2_SOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_SOF_PENDING                                              (1U)

#define LVDSRX_IRQSTATUS_1_RESERVED_SHIFT                                               (10U)
#define LVDSRX_IRQSTATUS_1_RESERVED_MASK                                                (0xfffffc00U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR0_SHIFT                                              (2U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR0_MASK                                               (0x00000004U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR0_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR0_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR1_SHIFT                                              (3U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR1_MASK                                               (0x00000008U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR1_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR1_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR2_SHIFT                                              (4U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR2_MASK                                               (0x00000010U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR2_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR2_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR3_SHIFT                                              (5U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR3_MASK                                               (0x00000020U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR3_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR3_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR4_SHIFT                                              (6U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR4_MASK                                               (0x00000040U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR4_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR4_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR5_SHIFT                                              (7U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR5_MASK                                               (0x00000080U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR5_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR5_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR6_SHIFT                                              (8U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR6_MASK                                               (0x00000100U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR6_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR6_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_ERR7_SHIFT                                              (9U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR7_MASK                                               (0x00000200U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR7_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_ERR7_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_1_CAM2_EOF_SHIFT                                               (1U)
#define LVDSRX_IRQSTATUS_1_CAM2_EOF_MASK                                                (0x00000002U)
#define LVDSRX_IRQSTATUS_1_CAM2_EOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_1_CAM2_EOF_PENDING                                              (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_SOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_SET_1_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_SET_1_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR0_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR1_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR2_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR3_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR4_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR5_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR6_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_ERR7_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_1_CAM2_EOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_SOF_DISABLE                                          (1U)

#define LVDSRX_IRQENABLE_CLR_1_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_CLR_1_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR0_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR1_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR2_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR3_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR4_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR5_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR6_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_ERR7_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_1_CAM2_EOF_DISABLE                                          (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_SOF_SHIFT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_SOF_MASK                                           (0x00000001U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_SOF_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_SOF_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_RESERVED_SHIFT                                          (10U)
#define LVDSRX_IRQSTATUS_RAW2_2_RESERVED_MASK                                           (0xfffffc00U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR0_SHIFT                                         (2U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR0_MASK                                          (0x00000004U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR0_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR0_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR1_SHIFT                                         (3U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR1_MASK                                          (0x00000008U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR1_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR1_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR2_SHIFT                                         (4U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR2_MASK                                          (0x00000010U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR2_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR2_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR3_SHIFT                                         (5U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR3_MASK                                          (0x00000020U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR3_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR3_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR4_SHIFT                                         (6U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR4_MASK                                          (0x00000040U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR4_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR4_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR5_SHIFT                                         (7U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR5_MASK                                          (0x00000080U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR5_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR5_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR6_SHIFT                                         (8U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR6_MASK                                          (0x00000100U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR6_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR6_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR7_SHIFT                                         (9U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR7_MASK                                          (0x00000200U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR7_NOEVENT                                        (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_ERR7_PENDING                                        (1U)

#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_EOF_SHIFT                                          (1U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_EOF_MASK                                           (0x00000002U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_EOF_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW2_2_CAM3_EOF_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_SOF_SHIFT                                               (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_SOF_MASK                                                (0x00000001U)
#define LVDSRX_IRQSTATUS_2_CAM3_SOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_SOF_PENDING                                              (1U)

#define LVDSRX_IRQSTATUS_2_RESERVED_SHIFT                                               (10U)
#define LVDSRX_IRQSTATUS_2_RESERVED_MASK                                                (0xfffffc00U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR0_SHIFT                                              (2U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR0_MASK                                               (0x00000004U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR0_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR0_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR1_SHIFT                                              (3U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR1_MASK                                               (0x00000008U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR1_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR1_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR2_SHIFT                                              (4U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR2_MASK                                               (0x00000010U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR2_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR2_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR3_SHIFT                                              (5U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR3_MASK                                               (0x00000020U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR3_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR3_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR4_SHIFT                                              (6U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR4_MASK                                               (0x00000040U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR4_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR4_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR5_SHIFT                                              (7U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR5_MASK                                               (0x00000080U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR5_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR5_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR6_SHIFT                                              (8U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR6_MASK                                               (0x00000100U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR6_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR6_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_ERR7_SHIFT                                              (9U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR7_MASK                                               (0x00000200U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR7_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_ERR7_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_2_CAM3_EOF_SHIFT                                               (1U)
#define LVDSRX_IRQSTATUS_2_CAM3_EOF_MASK                                                (0x00000002U)
#define LVDSRX_IRQSTATUS_2_CAM3_EOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_2_CAM3_EOF_PENDING                                              (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_SOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_SET_2_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_SET_2_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR0_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR1_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR2_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR3_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR4_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR5_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR6_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_ERR7_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_2_CAM3_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_EOF_NOEVENT                                          (0U)
#define LVDSRX_IRQENABLE_SET_2_CAM3_EOF_PENDING                                          (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_SOF_DISABLE                                          (1U)

#define LVDSRX_IRQENABLE_CLR_2_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_CLR_2_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR0_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR1_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR2_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR3_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR4_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR5_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR6_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_ERR7_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_2_CAM3_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_EOF_NOEVENT                                          (0U)
#define LVDSRX_IRQENABLE_CLR_2_CAM3_EOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_SOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_SOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_RAW_3_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQSTATUS_RAW_3_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR0_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR0_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM5_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM5_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM5_ERR1_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM5_ERR1_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR2_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR2_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR3_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR3_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR4_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR4_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR5_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR5_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR6_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR6_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR7_NOEVENT                                         (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_ERR7_PENDING                                         (1U)

#define LVDSRX_IRQSTATUS_RAW_3_CAM4_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_EOF_NOEVENT                                          (0U)
#define LVDSRX_IRQSTATUS_RAW_3_CAM4_EOF_PENDING                                          (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_SOF_SHIFT                                               (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_SOF_MASK                                                (0x00000001U)
#define LVDSRX_IRQSTATUS_3_CAM4_SOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_SOF_PENDING                                              (1U)

#define LVDSRX_IRQSTATUS_3_RESERVED_SHIFT                                               (10U)
#define LVDSRX_IRQSTATUS_3_RESERVED_MASK                                                (0xfffffc00U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR0_SHIFT                                              (2U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR0_MASK                                               (0x00000004U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR0_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR0_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR1_SHIFT                                              (3U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR1_MASK                                               (0x00000008U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR1_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR1_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR2_SHIFT                                              (4U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR2_MASK                                               (0x00000010U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR2_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR2_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR3_SHIFT                                              (5U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR3_MASK                                               (0x00000020U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR3_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR3_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR4_SHIFT                                              (6U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR4_MASK                                               (0x00000040U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR4_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR4_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR5_SHIFT                                              (7U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR5_MASK                                               (0x00000080U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR5_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR5_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR6_SHIFT                                              (8U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR6_MASK                                               (0x00000100U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR6_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR6_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_ERR7_SHIFT                                              (9U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR7_MASK                                               (0x00000200U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR7_NOEVENT                                             (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_ERR7_PENDING                                             (1U)

#define LVDSRX_IRQSTATUS_3_CAM4_EOF_SHIFT                                               (1U)
#define LVDSRX_IRQSTATUS_3_CAM4_EOF_MASK                                                (0x00000002U)
#define LVDSRX_IRQSTATUS_3_CAM4_EOF_NOEVENT                                              (0U)
#define LVDSRX_IRQSTATUS_3_CAM4_EOF_PENDING                                              (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_SOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_SET_3_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_SET_3_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR0_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR1_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR2_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR3_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR4_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR5_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR6_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_ERR7_ENABLE                                          (1U)

#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_SET_3_CAM4_EOF_ENABLE                                           (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_SHIFT                                           (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_MASK                                            (0x00000001U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_SOF_DISABLE                                          (1U)

#define LVDSRX_IRQENABLE_CLR_3_RESERVED_SHIFT                                           (10U)
#define LVDSRX_IRQENABLE_CLR_3_RESERVED_MASK                                            (0xfffffc00U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_SHIFT                                          (2U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_MASK                                           (0x00000004U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR0_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_SHIFT                                          (3U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_MASK                                           (0x00000008U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR1_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_SHIFT                                          (4U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_MASK                                           (0x00000010U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR2_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_SHIFT                                          (5U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_MASK                                           (0x00000020U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR3_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_SHIFT                                          (6U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_MASK                                           (0x00000040U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR4_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_SHIFT                                          (7U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_MASK                                           (0x00000080U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR5_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_SHIFT                                          (8U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_MASK                                           (0x00000100U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR6_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_SHIFT                                          (9U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_MASK                                           (0x00000200U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_NOACTION                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_DISABLED                                        (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_ENABLED                                         (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_ERR7_DISABLE                                         (1U)

#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_SHIFT                                           (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_MASK                                            (0x00000002U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_NOACTION                                         (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_DISABLED                                         (0U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_ENABLED                                          (1U)
#define LVDSRX_IRQENABLE_CLR_3_CAM4_EOF_DISABLE                                          (1U)

#define LVDSRX_CAM1_CFG_OP_MODE_SHIFT                                                   (0U)
#define LVDSRX_CAM1_CFG_OP_MODE_MASK                                                    (0x0000000fU)

#define LVDSRX_CAM1_CFG_NUMPHY_SHIFT                                                    (4U)
#define LVDSRX_CAM1_CFG_NUMPHY_MASK                                                     (0x00000070U)

#define LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT                                                 (8U)
#define LVDSRX_CAM1_CFG_PIX_WIDTH_MASK                                                  (0x00000700U)

#define LVDSRX_CAM1_CFG_NUM_LANE1_SHIFT                                                 (16U)
#define LVDSRX_CAM1_CFG_NUM_LANE1_MASK                                                  (0x00070000U)

#define LVDSRX_CAM1_CFG_NUM_LANE2_SHIFT                                                 (20U)
#define LVDSRX_CAM1_CFG_NUM_LANE2_MASK                                                  (0x00700000U)

#define LVDSRX_CAM1_CFG_NUM_LANE3_SHIFT                                                 (24U)
#define LVDSRX_CAM1_CFG_NUM_LANE3_MASK                                                  (0x07000000U)

#define LVDSRX_CAM1_CFG_NUM_LANE4_SHIFT                                                 (28U)
#define LVDSRX_CAM1_CFG_NUM_LANE4_MASK                                                  (0x70000000U)

#define LVDSRX_CAM1_CFG_CRCEN_SHIFT                                                     (12U)
#define LVDSRX_CAM1_CFG_CRCEN_MASK                                                      (0x00001000U)

#define LVDSRX_CAM1_CFG_FILEN_SHIFT                                                     (13U)
#define LVDSRX_CAM1_CFG_FILEN_MASK                                                      (0x00002000U)

#define LVDSRX_CAM1_CFG_DENDIAN_SHIFT                                                   (14U)
#define LVDSRX_CAM1_CFG_DENDIAN_MASK                                                    (0x00004000U)

#define LVDSRX_CAM1_CFG_ALIGN_SHIFT                                                     (15U)
#define LVDSRX_CAM1_CFG_ALIGN_MASK                                                      (0x00008000U)

#define LVDSRX_CAM1_CFG_SENDIAN_SHIFT                                                   (11U)
#define LVDSRX_CAM1_CFG_SENDIAN_MASK                                                    (0x00000800U)

#define LVDSRX_CAM1_CFG_FRSTAT_INIT_SHIFT                                               (7U)
#define LVDSRX_CAM1_CFG_FRSTAT_INIT_MASK                                                (0x00000080U)

#define LVDSRX_CAM1_CFG_RESERVED_SHIFT                                                  (19U)
#define LVDSRX_CAM1_CFG_RESERVED_MASK                                                   (0x00080000U)

#define LVDSRX_CAM1_CFG_RESERVED1_SHIFT                                                 (23U)
#define LVDSRX_CAM1_CFG_RESERVED1_MASK                                                  (0x00800000U)

#define LVDSRX_CAM1_CFG_RESERVED2_SHIFT                                                 (27U)
#define LVDSRX_CAM1_CFG_RESERVED2_MASK                                                  (0x08000000U)

#define LVDSRX_CAM1_CFG_RESERVED3_SHIFT                                                 (31U)
#define LVDSRX_CAM1_CFG_RESERVED3_MASK                                                  (0x80000000U)

#define LVDSRX_CAM1_FRMSIZE_LNWIDTH_SHIFT                                               (0U)
#define LVDSRX_CAM1_FRMSIZE_LNWIDTH_MASK                                                (0x0000ffffU)

#define LVDSRX_CAM1_FRMSIZE_FRWIDTH_SHIFT                                               (16U)
#define LVDSRX_CAM1_FRMSIZE_FRWIDTH_MASK                                                (0xffff0000U)

#define LVDSRX_CAM1_MAXWIDTH_SHIFT                                                      (0U)
#define LVDSRX_CAM1_MAXWIDTH_MASK                                                       (0x0000ffffU)

#define LVDSRX_CAM1_MAXWIDTH_RESERVED_SHIFT                                             (16U)
#define LVDSRX_CAM1_MAXWIDTH_RESERVED_MASK                                              (0xffff0000U)

#define LVDSRX_CAM1_SYNCSOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM1_SYNCSOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM1_SYNCSOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM1_SYNCSOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM1_SYNCEOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM1_SYNCEOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM1_SYNCEOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM1_SYNCEOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM1_SYNCSOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM1_SYNCSOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM1_SYNCSOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM1_SYNCSOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM1_SYNCEOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM1_SYNCEOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM1_SYNCEOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM1_SYNCEOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM1_SYNCSOV_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM1_SYNCSOV_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM1_SYNCSOV_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM1_SYNCSOV_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_CFG_OP_MODE_SHIFT                                                   (0U)
#define LVDSRX_CAM2_CFG_OP_MODE_MASK                                                    (0x0000000fU)

#define LVDSRX_CAM2_CFG_NUMPHY_SHIFT                                                    (4U)
#define LVDSRX_CAM2_CFG_NUMPHY_MASK                                                     (0x00000030U)

#define LVDSRX_CAM2_CFG_PIX_WIDTH_SHIFT                                                 (8U)
#define LVDSRX_CAM2_CFG_PIX_WIDTH_MASK                                                  (0x00000700U)

#define LVDSRX_CAM2_CFG_CRCEN_SHIFT                                                     (12U)
#define LVDSRX_CAM2_CFG_CRCEN_MASK                                                      (0x00001000U)

#define LVDSRX_CAM2_CFG_FILEN_SHIFT                                                     (13U)
#define LVDSRX_CAM2_CFG_FILEN_MASK                                                      (0x00002000U)

#define LVDSRX_CAM2_CFG_DENDIAN_SHIFT                                                   (14U)
#define LVDSRX_CAM2_CFG_DENDIAN_MASK                                                    (0x00004000U)

#define LVDSRX_CAM2_CFG_ALIGN_SHIFT                                                     (15U)
#define LVDSRX_CAM2_CFG_ALIGN_MASK                                                      (0x00008000U)

#define LVDSRX_CAM2_CFG_NUM_LANE_SHIFT                                                  (16U)
#define LVDSRX_CAM2_CFG_NUM_LANE_MASK                                                   (0x00070000U)

#define LVDSRX_CAM2_CFG_FRSTAT_INIT_SHIFT                                               (7U)
#define LVDSRX_CAM2_CFG_FRSTAT_INIT_MASK                                                (0x00000080U)

#define LVDSRX_CAM2_CFG_SENDIAN_SHIFT                                                   (11U)
#define LVDSRX_CAM2_CFG_SENDIAN_MASK                                                    (0x00000800U)

#define LVDSRX_CAM2_CFG_RESERVED_SHIFT                                                  (6U)
#define LVDSRX_CAM2_CFG_RESERVED_MASK                                                   (0x00000040U)

#define LVDSRX_CAM2_CFG_RESERVED2_SHIFT                                                 (20U)
#define LVDSRX_CAM2_CFG_RESERVED2_MASK                                                  (0x00700000U)

#define LVDSRX_CAM2_CFG_RESERVED4_SHIFT                                                 (24U)
#define LVDSRX_CAM2_CFG_RESERVED4_MASK                                                  (0x07000000U)

#define LVDSRX_CAM2_CFG_RESERVED1_SHIFT                                                 (19U)
#define LVDSRX_CAM2_CFG_RESERVED1_MASK                                                  (0x00080000U)

#define LVDSRX_CAM2_CFG_RESERVED3_SHIFT                                                 (23U)
#define LVDSRX_CAM2_CFG_RESERVED3_MASK                                                  (0x00800000U)

#define LVDSRX_CAM2_CFG_RESERVED5_SHIFT                                                 (27U)
#define LVDSRX_CAM2_CFG_RESERVED5_MASK                                                  (0xf8000000U)

#define LVDSRX_CAM2_FRMSIZE_LNWIDTH_SHIFT                                               (0U)
#define LVDSRX_CAM2_FRMSIZE_LNWIDTH_MASK                                                (0x0000ffffU)

#define LVDSRX_CAM2_FRMSIZE_FRWIDTH_SHIFT                                               (16U)
#define LVDSRX_CAM2_FRMSIZE_FRWIDTH_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_MAXWIDTH_SHIFT                                                      (0U)
#define LVDSRX_CAM2_MAXWIDTH_MASK                                                       (0x0000ffffU)

#define LVDSRX_CAM2_MAXWIDTH_RESERVED_SHIFT                                             (16U)
#define LVDSRX_CAM2_MAXWIDTH_RESERVED_MASK                                              (0xffff0000U)

#define LVDSRX_CAM2_SYNCSOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM2_SYNCSOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM2_SYNCSOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM2_SYNCSOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_SYNCEOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM2_SYNCEOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM2_SYNCEOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM2_SYNCEOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_SYNCSOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM2_SYNCSOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM2_SYNCSOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM2_SYNCSOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_SYNCEOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM2_SYNCEOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM2_SYNCEOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM2_SYNCEOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM2_SYNCSOV_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM2_SYNCSOV_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM2_SYNCSOV_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM2_SYNCSOV_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_CFG_OP_MODE_SHIFT                                                   (0U)
#define LVDSRX_CAM3_CFG_OP_MODE_MASK                                                    (0x0000000fU)

#define LVDSRX_CAM3_CFG_NUMPHY_SHIFT                                                    (4U)
#define LVDSRX_CAM3_CFG_NUMPHY_MASK                                                     (0x00000030U)

#define LVDSRX_CAM3_CFG_PIX_WIDTH_SHIFT                                                 (8U)
#define LVDSRX_CAM3_CFG_PIX_WIDTH_MASK                                                  (0x00000700U)

#define LVDSRX_CAM3_CFG_NUM_LANE1_SHIFT                                                 (16U)
#define LVDSRX_CAM3_CFG_NUM_LANE1_MASK                                                  (0x00070000U)

#define LVDSRX_CAM3_CFG_NUM_LANE2_SHIFT                                                 (20U)
#define LVDSRX_CAM3_CFG_NUM_LANE2_MASK                                                  (0x00700000U)

#define LVDSRX_CAM3_CFG_CRCEN_SHIFT                                                     (12U)
#define LVDSRX_CAM3_CFG_CRCEN_MASK                                                      (0x00001000U)

#define LVDSRX_CAM3_CFG_FILEN_SHIFT                                                     (13U)
#define LVDSRX_CAM3_CFG_FILEN_MASK                                                      (0x00002000U)

#define LVDSRX_CAM3_CFG_DENDIAN_SHIFT                                                   (14U)
#define LVDSRX_CAM3_CFG_DENDIAN_MASK                                                    (0x00004000U)

#define LVDSRX_CAM3_CFG_ALIGN_SHIFT                                                     (15U)
#define LVDSRX_CAM3_CFG_ALIGN_MASK                                                      (0x00008000U)

#define LVDSRX_CAM3_CFG_FRSTAT_INIT_SHIFT                                               (7U)
#define LVDSRX_CAM3_CFG_FRSTAT_INIT_MASK                                                (0x00000080U)

#define LVDSRX_CAM3_CFG_SENDIAN_SHIFT                                                   (11U)
#define LVDSRX_CAM3_CFG_SENDIAN_MASK                                                    (0x00000800U)

#define LVDSRX_CAM3_CFG_RESERVED_SHIFT                                                  (6U)
#define LVDSRX_CAM3_CFG_RESERVED_MASK                                                   (0x00000040U)

#define LVDSRX_CAM3_CFG_RESERVED1_SHIFT                                                 (19U)
#define LVDSRX_CAM3_CFG_RESERVED1_MASK                                                  (0x00080000U)

#define LVDSRX_CAM3_CFG_RESERVED2_SHIFT                                                 (23U)
#define LVDSRX_CAM3_CFG_RESERVED2_MASK                                                  (0xff800000U)

#define LVDSRX_CAM3_FRMSIZE_LNWIDTH_SHIFT                                               (0U)
#define LVDSRX_CAM3_FRMSIZE_LNWIDTH_MASK                                                (0x0000ffffU)

#define LVDSRX_CAM3_FRMSIZE_FRWIDTH_SHIFT                                               (16U)
#define LVDSRX_CAM3_FRMSIZE_FRWIDTH_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_MAXWIDTH_SHIFT                                                      (0U)
#define LVDSRX_CAM3_MAXWIDTH_MASK                                                       (0x0000ffffU)

#define LVDSRX_CAM3_MAXWIDTH_RESERVED_SHIFT                                             (16U)
#define LVDSRX_CAM3_MAXWIDTH_RESERVED_MASK                                              (0xffff0000U)

#define LVDSRX_CAM3_SYNCSOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM3_SYNCSOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM3_SYNCSOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM3_SYNCSOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_SYNCEOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM3_SYNCEOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM3_SYNCEOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM3_SYNCEOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_SYNCSOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM3_SYNCSOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM3_SYNCSOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM3_SYNCSOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_SYNCEOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM3_SYNCEOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM3_SYNCEOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM3_SYNCEOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM3_SYNCSOV_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM3_SYNCSOV_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM3_SYNCSOV_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM3_SYNCSOV_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_CFG_OP_MODE_SHIFT                                                   (0U)
#define LVDSRX_CAM4_CFG_OP_MODE_MASK                                                    (0x0000000fU)

#define LVDSRX_CAM4_CFG_NUMPHY_SHIFT                                                    (4U)
#define LVDSRX_CAM4_CFG_NUMPHY_MASK                                                     (0x00000010U)

#define LVDSRX_CAM4_CFG_PIX_WIDTH_SHIFT                                                 (8U)
#define LVDSRX_CAM4_CFG_PIX_WIDTH_MASK                                                  (0x00000700U)

#define LVDSRX_CAM4_CFG_NUM_LANE_SHIFT                                                  (16U)
#define LVDSRX_CAM4_CFG_NUM_LANE_MASK                                                   (0x00070000U)

#define LVDSRX_CAM4_CFG_CRCEN_SHIFT                                                     (12U)
#define LVDSRX_CAM4_CFG_CRCEN_MASK                                                      (0x00001000U)

#define LVDSRX_CAM4_CFG_FILEN_SHIFT                                                     (13U)
#define LVDSRX_CAM4_CFG_FILEN_MASK                                                      (0x00002000U)

#define LVDSRX_CAM4_CFG_DENDIAN_SHIFT                                                   (14U)
#define LVDSRX_CAM4_CFG_DENDIAN_MASK                                                    (0x00004000U)

#define LVDSRX_CAM4_CFG_ALIGN_SHIFT                                                     (15U)
#define LVDSRX_CAM4_CFG_ALIGN_MASK                                                      (0x00008000U)

#define LVDSRX_CAM4_CFG_FRSTAT_INIT_SHIFT                                               (7U)
#define LVDSRX_CAM4_CFG_FRSTAT_INIT_MASK                                                (0x00000080U)

#define LVDSRX_CAM4_CFG_SENDIAN_SHIFT                                                   (11U)
#define LVDSRX_CAM4_CFG_SENDIAN_MASK                                                    (0x00000800U)

#define LVDSRX_CAM4_CFG_RESERVED_SHIFT                                                  (5U)
#define LVDSRX_CAM4_CFG_RESERVED_MASK                                                   (0x00000060U)

#define LVDSRX_CAM4_CFG_RESERVED1_SHIFT                                                 (19U)
#define LVDSRX_CAM4_CFG_RESERVED1_MASK                                                  (0xfff80000U)

#define LVDSRX_CAM4_FRMSIZE_LNWIDTH_SHIFT                                               (0U)
#define LVDSRX_CAM4_FRMSIZE_LNWIDTH_MASK                                                (0x0000ffffU)

#define LVDSRX_CAM4_FRMSIZE_FRWIDTH_SHIFT                                               (16U)
#define LVDSRX_CAM4_FRMSIZE_FRWIDTH_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_MAXWIDTH_SHIFT                                                      (0U)
#define LVDSRX_CAM4_MAXWIDTH_MASK                                                       (0x0000ffffU)

#define LVDSRX_CAM4_MAXWIDTH_RESERVED_SHIFT                                             (16U)
#define LVDSRX_CAM4_MAXWIDTH_RESERVED_MASK                                              (0xffff0000U)

#define LVDSRX_CAM4_SYNCSOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM4_SYNCSOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM4_SYNCSOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM4_SYNCSOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_SYNCEOF_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM4_SYNCEOF_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM4_SYNCEOF_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM4_SYNCEOF_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_SYNCSOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM4_SYNCSOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM4_SYNCSOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM4_SYNCSOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_SYNCEOL_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM4_SYNCEOL_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM4_SYNCEOL_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM4_SYNCEOL_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_CAM4_SYNCSOV_SOFPTN_SHIFT                                                (0U)
#define LVDSRX_CAM4_SYNCSOV_SOFPTN_MASK                                                 (0x0000ffffU)

#define LVDSRX_CAM4_SYNCSOV_BITMASK_SHIFT                                               (16U)
#define LVDSRX_CAM4_SYNCSOV_BITMASK_MASK                                                (0xffff0000U)

#define LVDSRX_WDRCFG_WDRENA1_SHIFT                                                     (0U)
#define LVDSRX_WDRCFG_WDRENA1_MASK                                                      (0x00000001U)

#define LVDSRX_WDRCFG_WDRENA2_SHIFT                                                     (1U)
#define LVDSRX_WDRCFG_WDRENA2_MASK                                                      (0x00000002U)

#define LVDSRX_WDRCFG_WDRENA3_SHIFT                                                     (2U)
#define LVDSRX_WDRCFG_WDRENA3_MASK                                                      (0x00000004U)

#define LVDSRX_WDRCFG_WDRENA4_SHIFT                                                     (3U)
#define LVDSRX_WDRCFG_WDRENA4_MASK                                                      (0x00000008U)

#define LVDSRX_WDRCFG_WDRMODE_SHIFT                                                     (4U)
#define LVDSRX_WDRCFG_WDRMODE_MASK                                                      (0x00000010U)

#define LVDSRX_WDRCFG_PIX_WIDTH_SHIFT                                                   (8U)
#define LVDSRX_WDRCFG_PIX_WIDTH_MASK                                                    (0x00000f00U)

#define LVDSRX_WDRCFG_RESERVED_SHIFT                                                    (5U)
#define LVDSRX_WDRCFG_RESERVED_MASK                                                     (0x000000e0U)

#define LVDSRX_WDRCFG_RESERVED1_SHIFT                                                   (12U)
#define LVDSRX_WDRCFG_RESERVED1_MASK                                                    (0xfffff000U)

#define LVDSRX_WDRGN_WDRGN2_SHIFT                                                       (0U)
#define LVDSRX_WDRGN_WDRGN2_MASK                                                        (0x0000000fU)

#define LVDSRX_WDRGN_WDRGN3_SHIFT                                                       (4U)
#define LVDSRX_WDRGN_WDRGN3_MASK                                                        (0x000000f0U)

#define LVDSRX_WDRGN_WDRGN4_SHIFT                                                       (8U)
#define LVDSRX_WDRGN_WDRGN4_MASK                                                        (0x00000f00U)

#define LVDSRX_WDRGN_WDRNPXY1_SHIFT                                                     (16U)
#define LVDSRX_WDRGN_WDRNPXY1_MASK                                                      (0x003f0000U)

#define LVDSRX_WDRGN_RESERVED_SHIFT                                                     (12U)
#define LVDSRX_WDRGN_RESERVED_MASK                                                      (0x0000f000U)

#define LVDSRX_WDRGN_RESERVED1_SHIFT                                                    (22U)
#define LVDSRX_WDRGN_RESERVED1_MASK                                                     (0xffc00000U)

#define LVDSRX_WDRKP1_WDRNPY2_SHIFT                                                     (0U)
#define LVDSRX_WDRKP1_WDRNPY2_MASK                                                      (0x000003ffU)

#define LVDSRX_WDRKP1_WDRNPY3_SHIFT                                                     (16U)
#define LVDSRX_WDRKP1_WDRNPY3_MASK                                                      (0x03ff0000U)

#define LVDSRX_WDRKP1_RESERVED_SHIFT                                                    (10U)
#define LVDSRX_WDRKP1_RESERVED_MASK                                                     (0x0000fc00U)

#define LVDSRX_WDRKP1_RESERVED1_SHIFT                                                   (26U)
#define LVDSRX_WDRKP1_RESERVED1_MASK                                                    (0xfc000000U)

#define LVDSRX_WDRKP2_WDRNPX2_SHIFT                                                     (0U)
#define LVDSRX_WDRKP2_WDRNPX2_MASK                                                      (0x00003fffU)

#define LVDSRX_WDRKP2_WDRNPX3_SHIFT                                                     (16U)
#define LVDSRX_WDRKP2_WDRNPX3_MASK                                                      (0x3fff0000U)

#define LVDSRX_WDRKP2_RESERVED_SHIFT                                                    (14U)
#define LVDSRX_WDRKP2_RESERVED_MASK                                                     (0x0000c000U)

#define LVDSRX_WDRKP2_RESERVED1_SHIFT                                                   (30U)
#define LVDSRX_WDRKP2_RESERVED1_MASK                                                    (0xc0000000U)

#define LVDSRX_TEST1_LANE_SHIFT(n)                                                      ((n) * 8U)
#define LVDSRX_TEST1_LANE_MASK(n)                                                       (255U << ((n) * 8U))

#define LVDSRX_TEST2_LANE_SHIFT(n)                                                      ((n) * 8U)
#define LVDSRX_TEST2_LANE_MASK(n)                                                       (255U << ((n) * 8U))

#define LVDSRX_TEST3_LANE_SHIFT(n)                                                      ((n) * 8U)
#define LVDSRX_TEST3_LANE_MASK(n)                                                       (255U << ((n) * 8U))

#define LVDSRX_TEST4_LANE_SHIFT(n)                                                      ((n) * 8U)
#define LVDSRX_TEST4_LANE_MASK(n)                                                       (255U << ((n) * 8U))

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_LVDSRX_H_ */

