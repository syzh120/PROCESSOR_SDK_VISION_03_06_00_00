/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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

#ifndef HW_TESOC_H_
#define HW_TESOC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define TESOC_IP_REVISION                                           (0x0U)
#define TESOC_IP_HWINFO                                             (0x10U)
#define TESOC_IP_SYSCONFIG                                          (0x20U)
#define TESOC_INTR_EOI                                              (0x80U)
#define TESOC_INTR_STATUS_RAW_SET                                   (0x90U)
#define TESOC_INTR_STATUS_ENABLED_CLEAR                             (0xa0U)
#define TESOC_INTR_ENABLE_SET                                       (0xb0U)
#define TESOC_INTR_ENABLE_CLEAR                                     (0xc0U)
#define TESOC_LOCK                                                  (0xd0U)
#define TESOC_ABORT                                                 (0xe0U)
#define TESOC_BUSY                                                  (0xf0U)
#define TESOC_MISC_CONFIG                                           (0x100U)
#define TESOC_DIAG_INFO_0(n)                                        ((uint32_t)0x110 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_1(n)                                        ((uint32_t)0x120 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_2(n)                                        ((uint32_t)0x130 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_3(n)                                        ((uint32_t)0x140 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_4(n)                                        ((uint32_t)0x150 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_5(n)                                        ((uint32_t)0x160 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_6(n)                                        ((uint32_t)0x170 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_7(n)                                        ((uint32_t)0x180 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_8(n)                                        ((uint32_t)0x190 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_9(n)                                        ((uint32_t)0x1a0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_10(n)                                       ((uint32_t)0x1b0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_11(n)                                       ((uint32_t)0x1c0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_12(n)                                       ((uint32_t)0x1d0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_13(n)                                       ((uint32_t)0x1e0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_14(n)                                       ((uint32_t)0x1f0 + ((n) * 0x4U))
#define TESOC_DIAG_INFO_15(n)                                       ((uint32_t)0x200 + ((n) * 0x4U))
#define TESOC_DOMAIN_EN_DOM(n)                                      ((uint32_t)0x210 + ((n) * 0x10U))
#define TESOC_DOMAIN_EN_DOM0                                        (0x210U)
#define TESOC_DOMAIN_EN_DOM1                                        (0x220U)
#define TESOC_DOMAIN_EN_DOM2                                        (0x230U)
#define TESOC_DOMAIN_EN_DOM3                                        (0x240U)
#define TESOC_DOMAIN_EN_DOM4                                        (0x250U)
#define TESOC_SLICE_CONFIG_DOM0(n)                                  ((uint32_t)0x260 + ((n) * 0x4U))
#define TESOC_SLICE_CONFIG_DOM1(n)                                  ((uint32_t)0x280 + ((n) * 0x4U))
#define TESOC_SLICE_CONFIG_DOM2(n)                                  ((uint32_t)0x2a0 + ((n) * 0x4U))
#define TESOC_SLICE_CONFIG_DOM3(n)                                  ((uint32_t)0x2c0 + ((n) * 0x4U))
#define TESOC_SLICE_CONFIG_DOM4(n)                                  ((uint32_t)0x2e0 + ((n) * 0x4U))
#define TESOC_SLICE_STATUS_DOM0(n)                                  ((uint32_t)0x300 + ((n) * 0x4U))
#define TESOC_SLICE_STATUS_DOM1(n)                                  ((uint32_t)0x320 + ((n) * 0x4U))
#define TESOC_SLICE_STATUS_DOM2(n)                                  ((uint32_t)0x340 + ((n) * 0x4U))
#define TESOC_SLICE_STATUS_DOM3(n)                                  ((uint32_t)0x360 + ((n) * 0x4U))
#define TESOC_SLICE_STATUS_DOM4(n)                                  ((uint32_t)0x380 + ((n) * 0x4U))
#define TESOC_SLICE_RESULT_DOM0(n)                                  ((uint32_t)0x3a0 + ((n) * 0x4U))
#define TESOC_SLICE_RESULT_DOM1(n)                                  ((uint32_t)0x3c0 + ((n) * 0x4U))
#define TESOC_SLICE_RESULT_DOM2(n)                                  ((uint32_t)0x3e0 + ((n) * 0x4U))
#define TESOC_SLICE_RESULT_DOM3(n)                                  ((uint32_t)0x400 + ((n) * 0x4U))
#define TESOC_SLICE_RESULT_DOM4(n)                                  ((uint32_t)0x420 + ((n) * 0x4U))
#define TESOC_RAM(n)                                                ((uint32_t)0x500 + ((n) * 0x4U))
#define TESOC_ROM(n)                                                ((uint32_t)0x10500 + ((n) * 0x4U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define TESOC_IP_REVISION_SHIFT                                                         (0U)
#define TESOC_IP_REVISION_MASK                                                          (0xffffffffU)

#define TESOC_IP_HWINFO_SHIFT                                                           (0U)
#define TESOC_IP_HWINFO_MASK                                                            (0xffffffffU)

#define TESOC_IP_SYSCONFIG_SHIFT                                                        (0U)
#define TESOC_IP_SYSCONFIG_MASK                                                         (0xffffffffU)

#define TESOC_INTR_EOI_SHIFT                                                            (0U)
#define TESOC_INTR_EOI_MASK                                                             (0xffffffffU)

#define TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_SHIFT                                 (0U)
#define TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_MASK                                  (0x1U)
#define TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_ENABLE                                (0x1U)
#define TESOC_INTR_STATUS_RAW_TEST_COMPLETION_SET_DISABLE                               (0x0U)

#define TESOC_INTR_STATUS_RAW_SET_SHIFT                                                 (1U)
#define TESOC_INTR_STATUS_RAW_SET_MASK                                                  (0xfffffffeU)

#define TESOC_INTR_STATUS_ENABLED_CLEAR_SHIFT                                           (0U)
#define TESOC_INTR_STATUS_ENABLED_CLEAR_MASK                                            (0xffffffffU)

#define TESOC_INTR_ENABLE_SET_SHIFT                                                     (0U)
#define TESOC_INTR_ENABLE_SET_MASK                                                      (0xffffffffU)

#define TESOC_INTR_ENABLE_CLEAR_SHIFT                                                   (0U)
#define TESOC_INTR_ENABLE_CLEAR_MASK                                                    (0xffffffffU)

#define TESOC_LOCK_SHIFT                                                                (0U)
#define TESOC_LOCK_MASK                                                                 (0x0000000fU)
#define TESOC_LOCK_TO_LOCK                                                              (0x5U)
#define TESOC_LOCK_TO_UNLOCK                                                            (0xAU)

#define TESOC_ABORT_SHIFT                                                               (0U)
#define TESOC_ABORT_MASK                                                                (0x0000000fU)
#define TESOC_ABORT_ABORT                                                               (0x5U)

#define TESOC_BUSY_SHIFT                                                                (0U)
#define TESOC_BUSY_MASK                                                                 (0x0000000fU)
#define TESOC_BUSY_BUSY                                                                 (0x5U)

#define TESOC_MISC_CONFIG_SOURCE_CONTROL_SHIFT                                          (0U)
#define TESOC_MISC_CONFIG_SOURCE_CONTROL_MASK                                           (0x0000000fU)
#define TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_RAM                               (0x5U)
#define TESOC_MISC_CONFIG_SOURCE_CONTROL_SLICE_SOURCE_ROM                               (0x0U)

#define TESOC_MISC_CONFIG_DUMMY_TRIGGER17_SHIFT                                         (17U)
#define TESOC_MISC_CONFIG_DUMMY_TRIGGER17_MASK                                          (0x00020000)

#define TESOC_MISC_CONFIG_DUMMY_TRIGGER18_SHIFT                                         (18U)
#define TESOC_MISC_CONFIG_DUMMY_TRIGGER18_MASK                                          (0x00040000)

#define TESOC_MISC_CONFIG_MUX_CONTROL_SHIFT                                             (24U)
#define TESOC_MISC_CONFIG_MUX_CONTROL_MASK                                              (0x01000000)

#define TESOC_DIAG_INFO_0_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_0_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_1_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_1_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_2_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_2_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_3_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_3_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_4_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_4_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_5_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_5_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_6_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_6_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_7_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_7_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_8_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_8_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_9_SHIFT                                                         (0U)
#define TESOC_DIAG_INFO_9_MASK                                                          (0xffffffffU)

#define TESOC_DIAG_INFO_10_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_10_MASK                                                         (0xffffffffU)

#define TESOC_DIAG_INFO_11_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_11_MASK                                                         (0xffffffffU)

#define TESOC_DIAG_INFO_12_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_12_MASK                                                         (0xffffffffU)

#define TESOC_DIAG_INFO_13_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_13_MASK                                                         (0xffffffffU)

#define TESOC_DIAG_INFO_14_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_14_MASK                                                         (0xffffffffU)

#define TESOC_DIAG_INFO_15_SHIFT                                                        (0U)
#define TESOC_DIAG_INFO_15_MASK                                                         (0xffffffffU)

#define TESOC_DOMAIN_EN_DOM_START_SHIFT                                                 (0U)
#define TESOC_DOMAIN_EN_DOM_START_MASK                                                  (0x0000000FU)
#define TESOC_DOMAIN_EN_DOM_START_TO_START                                              (0x5U)

#define TESOC_DOMAIN_EN_DOM0_START_SHIFT                                                (0U)
#define TESOC_DOMAIN_EN_DOM0_START_MASK                                                 (0x00000001U)

#define TESOC_DOMAIN_EN_DOM1_START_SHIFT                                                (0U)
#define TESOC_DOMAIN_EN_DOM1_START_MASK                                                 (0x00000001U)

#define TESOC_DOMAIN_EN_DOM2_START_SHIFT                                                (0U)
#define TESOC_DOMAIN_EN_DOM2_START_MASK                                                 (0x00000001U)

#define TESOC_DOMAIN_EN_DOM3_START_SHIFT                                                (0U)
#define TESOC_DOMAIN_EN_DOM3_START_MASK                                                 (0x00000001U)

#define TESOC_DOMAIN_EN_DOM4_START_SHIFT                                                (0U)
#define TESOC_DOMAIN_EN_DOM4_START_MASK                                                 (0x00000001U)

#define TESOC_SLICE_CONFIG_DOM0_REG_21_SHIFT                                            (0U)
#define TESOC_SLICE_CONFIG_DOM0_REG_21_MASK                                             (0xffffffffU)

#define TESOC_SLICE_CONFIG_DOM1_REG_21_SHIFT                                            (0U)
#define TESOC_SLICE_CONFIG_DOM1_REG_21_MASK                                             (0xffffffffU)

#define TESOC_SLICE_CONFIG_DOM2_REG_21_SHIFT                                            (0U)
#define TESOC_SLICE_CONFIG_DOM2_REG_21_MASK                                             (0xffffffffU)

#define TESOC_SLICE_CONFIG_DOM3_REG_21_SHIFT                                            (0U)
#define TESOC_SLICE_CONFIG_DOM3_REG_21_MASK                                             (0xffffffffU)

#define TESOC_SLICE_CONFIG_DOM4_REG_21_SHIFT                                            (0U)
#define TESOC_SLICE_CONFIG_DOM4_REG_21_MASK                                             (0xffffffffU)

#define TESOC_SLICE_STATUS_DOM0_CONFIG_REG_22_SHIFT                                     (0U)
#define TESOC_SLICE_STATUS_DOM0_CONFIG_REG_22_MASK                                      (0xffffffffU)

#define TESOC_SLICE_STATUS_DOM1_CONFIG_REG_22_SHIFT                                     (0U)
#define TESOC_SLICE_STATUS_DOM1_CONFIG_REG_22_MASK                                      (0xffffffffU)

#define TESOC_SLICE_STATUS_DOM2_CONFIG_REG_22_SHIFT                                     (0U)
#define TESOC_SLICE_STATUS_DOM2_CONFIG_REG_22_MASK                                      (0xffffffffU)

#define TESOC_SLICE_STATUS_DOM3_CONFIG_REG_22_SHIFT                                     (0U)
#define TESOC_SLICE_STATUS_DOM3_CONFIG_REG_22_MASK                                      (0xffffffffU)

#define TESOC_SLICE_STATUS_DOM4_CONFIG_REG_22_SHIFT                                     (0U)
#define TESOC_SLICE_STATUS_DOM4_CONFIG_REG_22_MASK                                      (0xffffffffU)

#define TESOC_SLICE_RESULT_DOM0_CONFIG_REG_23_SHIFT                                     (0U)
#define TESOC_SLICE_RESULT_DOM0_CONFIG_REG_23_MASK                                      (0xffffffffU)

#define TESOC_SLICE_RESULT_DOM1_CONFIG_REG_23_SHIFT                                     (0U)
#define TESOC_SLICE_RESULT_DOM1_CONFIG_REG_23_MASK                                      (0xffffffffU)

#define TESOC_SLICE_RESULT_DOM2_CONFIG_REG_23_SHIFT                                     (0U)
#define TESOC_SLICE_RESULT_DOM2_CONFIG_REG_23_MASK                                      (0xffffffffU)

#define TESOC_SLICE_RESULT_DOM3_CONFIG_REG_23_SHIFT                                     (0U)
#define TESOC_SLICE_RESULT_DOM3_CONFIG_REG_23_MASK                                      (0xffffffffU)

#define TESOC_SLICE_RESULT_DOM4_CONFIG_REG_23_SHIFT                                     (0U)
#define TESOC_SLICE_RESULT_DOM4_CONFIG_REG_23_MASK                                      (0xffffffffU)

#define TESOC_RAM_SHIFT                                                                 (0U)
#define TESOC_RAM_MASK                                                                  (0xffffffffU)

#define TESOC_ROM_SHIFT                                                                 (0U)
#define TESOC_ROM_MASK                                                                  (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_TESOC_H_ */

