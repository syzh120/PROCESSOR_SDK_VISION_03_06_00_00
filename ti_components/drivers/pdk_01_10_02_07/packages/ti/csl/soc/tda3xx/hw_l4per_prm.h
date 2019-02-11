/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_l4per_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_L4PER_PRM_H_
#define HW_L4PER_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PM_L4PER_PWRSTCTRL                                     (0x0U)
#define PM_L4PER_PWRSTST                                       (0x4U)
#define RM_L4PER2_L4PER2_CONTEXT                                                                            (0xcU)
#define RM_L4PER3_L4PER3_CONTEXT                                                                            (0x14U)
#define PM_L4PER_DCC6_WKDEP                                         (0x28U)
#define RM_L4PER_DCC6_CONTEXT                                       (0x2cU)
#define PM_L4PER_DCC7_WKDEP                                         (0x30U)
#define RM_L4PER_DCC7_CONTEXT                                       (0x34U)
#define PM_L4PER_TIMER2_WKDEP                                       (0x38U)
#define RM_L4PER_TIMER2_CONTEXT                                (0x3cU)
#define PM_L4PER_TIMER3_WKDEP                                       (0x40U)
#define RM_L4PER_TIMER3_CONTEXT                                (0x44U)
#define PM_L4PER_TIMER4_WKDEP                                       (0x48U)
#define RM_L4PER_TIMER4_CONTEXT                                (0x4cU)
#define PM_L4PER_DCC5_WKDEP                                         (0x50U)
#define RM_L4PER_DCC5_CONTEXT                                       (0x54U)
#define RM_L4PER_ELM_CONTEXT                                   (0x5cU)
#define PM_L4PER_GPIO2_WKDEP                                        (0x60U)
#define RM_L4PER_GPIO2_CONTEXT                                 (0x64U)
#define PM_L4PER_GPIO3_WKDEP                                        (0x68U)
#define RM_L4PER_GPIO3_CONTEXT                                 (0x6cU)
#define PM_L4PER_GPIO4_WKDEP                                        (0x70U)
#define RM_L4PER_GPIO4_CONTEXT                                 (0x74U)
#define PM_L4PER_GPIO5_WKDEP                                        (0x78U)
#define RM_L4PER_ESM_CONTEXT                                        (0x8cU)
#define PM_L4PER_I2C1_WKDEP                                         (0xa0U)
#define RM_L4PER_I2C1_CONTEXT                                  (0xa4U)
#define PM_L4PER_I2C2_WKDEP                                         (0xa8U)
#define RM_L4PER_I2C2_CONTEXT                                  (0xacU)
#define RM_L4PER_L4PER1_CONTEXT                                (0xc0U)
#define RM_L4PER2_PWMSS1_CONTEXT                               (0xc4U)
#define PM_L4PER_DCC1_WKDEP                                         (0xc8U)
#define RM_L4PER3_DCC1_CONTEXT                                      (0xccU)
#define PM_L4PER_DCC2_WKDEP                                         (0xd0U)
#define RM_L4PER3_DCC2_CONTEXT                                      (0xd4U)
#define PM_L4PER_DCC3_WKDEP                                         (0xd8U)
#define RM_L4PER3_DCC3_CONTEXT                                      (0xdcU)
#define PM_L4PER_MCSPI1_WKDEP                                       (0xf0U)
#define RM_L4PER_MCSPI1_CONTEXT                                (0xf4U)
#define PM_L4PER_MCSPI2_WKDEP                                       (0xf8U)
#define RM_L4PER_MCSPI2_CONTEXT                                (0xfcU)
#define PM_L4PER_MCSPI3_WKDEP                                       (0x100U)
#define RM_L4PER_MCSPI3_CONTEXT                                (0x104U)
#define PM_L4PER_MCSPI4_WKDEP                                       (0x108U)
#define RM_L4PER_MCSPI4_CONTEXT                                (0x10cU)
#define PM_L4PER_MMC4_WKDEP                                         (0x128U)
#define RM_L4PER_MMC4_CONTEXT                                  (0x12cU)
#define PM_L4PER_DCC4_WKDEP                                         (0x130U)
#define RM_L4PER3_DCC4_CONTEXT                                      (0x134U)
#define PM_L4PER2_QSPI_WKDEP                                        (0x138U)
#define RM_L4PER2_QSPI_CONTEXT                                 (0x13cU)
#define PM_L4PER_UART1_WKDEP                                        (0x140U)
#define RM_L4PER_UART1_CONTEXT                                 (0x144U)
#define PM_L4PER_UART2_WKDEP                                        (0x148U)
#define RM_L4PER_UART2_CONTEXT                                 (0x14cU)
#define PM_L4PER_UART3_WKDEP                                        (0x150U)
#define RM_L4PER_UART3_CONTEXT                                 (0x154U)
#define PM_L4PER2_ADC_WKDEP                                         (0x160U)
#define RM_L4PER2_ADC_CONTEXT                                       (0x164U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT                            (0x1dcU)
#define PM_L4PER2_DCAN2_WKDEP                                       (0x1f0U)
#define RM_L4PER2_DCAN2_CONTEXT                                (0x1f4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_RETSTATE_SHIFT                         (9U)
#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_RETSTATE_MASK                          (0x00000200U)
#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_RETSTATE_MEM_OFF                        (0U)

#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_ONSTATE_SHIFT                          (18U)
#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_ONSTATE_MASK                           (0x000c0000U)
#define PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_ONSTATE_MEM_ON                          (3U)

#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_RETSTATE_SHIFT                            (8U)
#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_RETSTATE_MASK                             (0x00000100U)
#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_RETSTATE_MEM_RET                           (1U)

#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_ONSTATE_SHIFT                             (16U)
#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_ONSTATE_MASK                              (0x00030000U)
#define PM_L4PER_PWRSTCTRL_RETAINED_BANK_ONSTATE_MEM_ON                             (3U)

#define PM_L4PER_PWRSTCTRL_LOGICRETSTATE_SHIFT                                     (2U)
#define PM_L4PER_PWRSTCTRL_LOGICRETSTATE_MASK                                      (0x00000004U)
#define PM_L4PER_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                                  (1U)
#define PM_L4PER_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                                  (0U)

#define PM_L4PER_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                               (4U)
#define PM_L4PER_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                (0x00000010U)
#define PM_L4PER_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                   (1U)
#define PM_L4PER_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                  (0U)

#define PM_L4PER_PWRSTCTRL_POWERSTATE_SHIFT                                        (0U)
#define PM_L4PER_PWRSTCTRL_POWERSTATE_MASK                                         (0x00000003U)
#define PM_L4PER_PWRSTCTRL_POWERSTATE_RESERVED                                      (0U)
#define PM_L4PER_PWRSTCTRL_POWERSTATE_INACT                                         (2U)
#define PM_L4PER_PWRSTCTRL_POWERSTATE_RET                                           (1U)
#define PM_L4PER_PWRSTCTRL_POWERSTATE_ON                                            (3U)

#define PM_L4PER_PWRSTST_INTRANSITION_SHIFT                                        (20U)
#define PM_L4PER_PWRSTST_INTRANSITION_MASK                                         (0x00100000U)
#define PM_L4PER_PWRSTST_INTRANSITION_NO                                            (0U)
#define PM_L4PER_PWRSTST_INTRANSITION_ONGOING                                       (1U)

#define PM_L4PER_PWRSTST_LOGICSTATEST_SHIFT                                        (2U)
#define PM_L4PER_PWRSTST_LOGICSTATEST_MASK                                         (0x00000004U)
#define PM_L4PER_PWRSTST_LOGICSTATEST_ON                                            (1U)
#define PM_L4PER_PWRSTST_LOGICSTATEST_OFF                                           (0U)

#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_SHIFT                               (4U)
#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_MASK                                (0x00000030U)
#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_MEM_ON                               (3U)
#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_MEM_RET                              (1U)
#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_MEM_OFF                              (0U)
#define PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_RESERVED                             (2U)

#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_SHIFT                            (6U)
#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_MASK                             (0x000000c0U)
#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_MEM_ON                            (3U)
#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_RESERVED1                         (1U)
#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_MEM_OFF                           (0U)
#define PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_RESERVED                          (2U)

#define PM_L4PER_PWRSTST_POWERSTATEST_SHIFT                                        (0U)
#define PM_L4PER_PWRSTST_POWERSTATEST_MASK                                         (0x00000003U)
#define PM_L4PER_PWRSTST_POWERSTATEST_ON                                            (3U)
#define PM_L4PER_PWRSTST_POWERSTATEST_RESERVED                                      (0U)
#define PM_L4PER_PWRSTST_POWERSTATEST_RET                                           (1U)
#define PM_L4PER_PWRSTST_POWERSTATEST_INACTIVE                                      (2U)

#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                               (24U)
#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_MASK                                (0x03000000U)
#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_ON                                   (3U)
#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_OFF                                  (0U)
#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_RET                                  (1U)
#define PM_L4PER_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                             (2U)

#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                      (1U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                       (0x00000002U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                        (1U)
#define RM_L4PER2_L4PER2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                  (0U)

#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                      (1U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_RFF_MASK                                                       (0x00000002U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_RFF_LOST                                                        (1U)
#define RM_L4PER3_L4PER3_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                  (0U)

#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_SCC6_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC6_WKDEP_WKUPDEP_DCC6_EVE1_DISABLED                                        (0U)

#define RM_L4PER_DCC6_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                     (0U)
#define RM_L4PER_DCC6_CONTEXT_LOSTCONTEXT_DFF_MASK                                      (0x00000001U)
#define RM_L4PER_DCC6_CONTEXT_LOSTCONTEXT_DFF_LOST                                       (1U)
#define RM_L4PER_DCC6_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                 (0U)

#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC7_WKDEP_WKUPDEP_DCC7_EVE1_DISABLED                                        (0U)

#define RM_L4PER_DCC7_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                     (0U)
#define RM_L4PER_DCC7_CONTEXT_LOSTCONTEXT_DFF_MASK                                      (0x00000001U)
#define RM_L4PER_DCC7_CONTEXT_LOSTCONTEXT_DFF_LOST                                       (1U)
#define RM_L4PER_DCC7_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                 (0U)

#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP1_SHIFT                                                     (2U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP1_MASK                                                      (0x00000004U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_IPU1_SHIFT                                                     (4U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_IPU1_MASK                                                      (0x00000010U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_IPU1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_IPU1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP2_SHIFT                                                     (5U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP2_MASK                                                      (0x00000020U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_DSP2_DISABLED                                                   (0U)

#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_EVE1_SHIFT                                                     (6U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_EVE1_MASK                                                      (0x00000040U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_EVE1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER2_WKDEP_WKUPDEP_TIMER2_EVE1_DISABLED                                                   (0U)

#define RM_L4PER_TIMER2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_TIMER2_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP1_SHIFT                                                     (2U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP1_MASK                                                      (0x00000004U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_IPU1_SHIFT                                                     (4U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_IPU1_MASK                                                      (0x00000010U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_IPU1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_IPU1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP2_SHIFT                                                     (5U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP2_MASK                                                      (0x00000020U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_DSP2_DISABLED                                                   (0U)

#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_EVE1_SHIFT                                                     (6U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_EVE1_MASK                                                      (0x00000040U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_EVE1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER3_WKDEP_WKUPDEP_TIMER3_EVE1_DISABLED                                                   (0U)

#define RM_L4PER_TIMER3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_TIMER3_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_TIMER3_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_TIMER3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP1_SHIFT                                                     (2U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP1_MASK                                                      (0x00000004U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_IPU1_SHIFT                                                     (4U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_IPU1_MASK                                                      (0x00000010U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_IPU1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_IPU1_DISABLED                                                   (0U)

#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP2_SHIFT                                                     (5U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP2_MASK                                                      (0x00000020U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_DSP2_DISABLED                                                   (0U)

#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_EVE1_SHIFT                                                     (6U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_EVE1_MASK                                                      (0x00000040U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_EVE1_ENABLED                                                    (1U)
#define PM_L4PER_TIMER4_WKDEP_WKUPDEP_TIMER4_EVE1_DISABLED                                                   (0U)

#define RM_L4PER_TIMER4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_TIMER4_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_TIMER4_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_TIMER4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC5_WKDEP_WKUPDEP_DCC5_EVE1_DISABLED                                        (0U)

#define RM_L4PER_DCC5_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                     (0U)
#define RM_L4PER_DCC5_CONTEXT_LOSTCONTEXT_DFF_MASK                                      (0x00000001U)
#define RM_L4PER_DCC5_CONTEXT_LOSTCONTEXT_DFF_LOST                                       (1U)
#define RM_L4PER_DCC5_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                 (0U)

#define RM_L4PER_ELM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                 (0U)
#define RM_L4PER_ELM_CONTEXT_LOSTCONTEXT_DFF_MASK                                  (0x00000001U)
#define RM_L4PER_ELM_CONTEXT_LOSTCONTEXT_DFF_LOST                                   (1U)
#define RM_L4PER_ELM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                             (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP1_SHIFT                                                  (2U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP1_MASK                                                   (0x00000004U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_IPU1_SHIFT                                                  (4U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_IPU1_MASK                                                   (0x00000010U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP2_SHIFT                                                  (5U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP2_MASK                                                   (0x00000020U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_EVE1_SHIFT                                                  (6U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_EVE1_MASK                                                   (0x00000040U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ1_EVE1_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP1_SHIFT                                                  (12U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP1_MASK                                                   (0x00001000U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_IPU1_SHIFT                                                  (14U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_IPU1_MASK                                                   (0x00004000U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP2_SHIFT                                                  (15U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP2_MASK                                                   (0x00008000U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_EVE1_SHIFT                                                  (16U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_EVE1_MASK                                                   (0x00010000U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO2_WKDEP_WKUPDEP_GPIO2_IRQ2_EVE1_DISABLED                                                (0U)

#define RM_L4PER_GPIO2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_GPIO2_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_GPIO2_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_GPIO2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP1_SHIFT                                                  (2U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP1_MASK                                                   (0x00000004U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_IPU1_SHIFT                                                  (4U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_IPU1_MASK                                                   (0x00000010U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP2_SHIFT                                                  (5U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP2_MASK                                                   (0x00000020U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_EVE1_SHIFT                                                  (6U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_EVE1_MASK                                                   (0x00000040U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ1_EVE1_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP1_SHIFT                                                  (12U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP1_MASK                                                   (0x00001000U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_IPU1_SHIFT                                                  (14U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_IPU1_MASK                                                   (0x00004000U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP2_SHIFT                                                  (15U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP2_MASK                                                   (0x00008000U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_EVE1_SHIFT                                                  (16U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_EVE1_MASK                                                   (0x00010000U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO3_WKDEP_WKUPDEP_GPIO3_IRQ2_EVE1_DISABLED                                                (0U)

#define RM_L4PER_GPIO3_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_GPIO3_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_GPIO3_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_GPIO3_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP1_SHIFT                                                  (2U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP1_MASK                                                   (0x00000004U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_IPU1_SHIFT                                                  (4U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_IPU1_MASK                                                   (0x00000010U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP2_SHIFT                                                  (5U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP2_MASK                                                   (0x00000020U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_EVE1_SHIFT                                                  (6U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_EVE1_MASK                                                   (0x00000040U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ1_EVE1_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP1_SHIFT                                                  (12U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP1_MASK                                                   (0x00001000U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_IPU1_SHIFT                                                  (14U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_IPU1_MASK                                                   (0x00004000U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP2_SHIFT                                                  (15U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP2_MASK                                                   (0x00008000U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_EVE1_SHIFT                                                  (16U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_EVE1_MASK                                                   (0x00010000U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO4_WKDEP_WKUPDEP_GPIO4_IRQ2_EVE1_DISABLED                                                (0U)

#define RM_L4PER_GPIO4_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_GPIO4_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_GPIO4_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_GPIO4_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP1_SHIFT                                                  (2U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP1_MASK                                                   (0x00000004U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_IPU1_SHIFT                                                  (4U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_IPU1_MASK                                                   (0x00000010U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP2_SHIFT                                                  (5U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP2_MASK                                                   (0x00000020U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_EVE1_SHIFT                                                  (6U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_EVE1_MASK                                                   (0x00000040U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ1_EVE1_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP1_SHIFT                                                  (12U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP1_MASK                                                   (0x00001000U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP1_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_IPU1_SHIFT                                                  (14U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_IPU1_MASK                                                   (0x00004000U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_IPU1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_IPU1_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP2_SHIFT                                                  (15U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP2_MASK                                                   (0x00008000U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP2_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_DSP2_DISABLED                                                (0U)

#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_EVE1_SHIFT                                                  (16U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_EVE1_MASK                                                   (0x00010000U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_EVE1_ENABLED                                                 (1U)
#define PM_L4PER_GPIO5_WKDEP_WKUPDEP_GPIO5_IRQ2_EVE1_DISABLED                                                (0U)

#define RM_L4PER_ESM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                      (0U)
#define RM_L4PER_ESM_CONTEXT_LOSTCONTEXT_DFF_MASK                                       (0x00000001U)
#define RM_L4PER_ESM_CONTEXT_LOSTCONTEXT_DFF_LOST                                        (1U)
#define RM_L4PER_ESM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                  (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP1_SHIFT                                                     (2U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP1_MASK                                                      (0x00000004U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_IPU1_SHIFT                                                     (4U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_IPU1_MASK                                                      (0x00000010U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_IPU1_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_IPU1_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP2_SHIFT                                                     (5U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP2_MASK                                                      (0x00000020U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_DSP2_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_EVE1_SHIFT                                                     (6U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_EVE1_MASK                                                      (0x00000040U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_EVE1_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_IRQ_EVE1_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP1_SHIFT                                                     (12U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP1_MASK                                                      (0x00001000U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_SDMA_SHIFT                                                     (13U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_SDMA_MASK                                                      (0x00002000U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_SDMA_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_SDMA_DISABLED                                                   (0U)

#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP2_SHIFT                                                     (15U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP2_MASK                                                      (0x00008000U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_I2C1_WKDEP_WKUPDEP_I2C1_DMA_DSP2_DISABLED                                                   (0U)

#define RM_L4PER_I2C1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                (1U)
#define RM_L4PER_I2C1_CONTEXT_LOSTCONTEXT_RFF_MASK                                 (0x00000002U)
#define RM_L4PER_I2C1_CONTEXT_LOSTCONTEXT_RFF_LOST                                  (1U)
#define RM_L4PER_I2C1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                            (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP1_SHIFT                                                     (2U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP1_MASK                                                      (0x00000004U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_IPU1_SHIFT                                                     (4U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_IPU1_MASK                                                      (0x00000010U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_IPU1_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_IPU1_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP2_SHIFT                                                     (5U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP2_MASK                                                      (0x00000020U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_DSP2_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_EVE1_SHIFT                                                     (6U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_EVE1_MASK                                                      (0x00000040U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_EVE1_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_IRQ_EVE1_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP1_SHIFT                                                     (12U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP1_MASK                                                      (0x00001000U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP1_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP1_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_SDMA_SHIFT                                                     (13U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_SDMA_MASK                                                      (0x00002000U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_SDMA_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_SDMA_DISABLED                                                   (0U)

#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP2_SHIFT                                                     (15U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP2_MASK                                                      (0x00008000U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP2_ENABLED                                                    (1U)
#define PM_L4PER_I2C2_WKDEP_WKUPDEP_I2C2_DMA_DSP2_DISABLED                                                   (0U)

#define RM_L4PER_I2C2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                (0U)
#define RM_L4PER_I2C2_CONTEXT_LOSTCONTEXT_DFF_MASK                                 (0x00000001U)
#define RM_L4PER_I2C2_CONTEXT_LOSTCONTEXT_DFF_LOST                                  (1U)
#define RM_L4PER_I2C2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                            (0U)

#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                              (1U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_RFF_MASK                               (0x00000002U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_RFF_LOST                                (1U)
#define RM_L4PER_L4PER1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                          (0U)

#define RM_L4PER2_PWMSS1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                             (0U)
#define RM_L4PER2_PWMSS1_CONTEXT_LOSTCONTEXT_DFF_MASK                              (0x00000001U)
#define RM_L4PER2_PWMSS1_CONTEXT_LOSTCONTEXT_DFF_LOST                               (1U)
#define RM_L4PER2_PWMSS1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                         (0U)

#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC1_WKDEP_WKUPDEP_DCC1_EVE1_DISABLED                                        (0U)

#define RM_L4PER3_DCC1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                    (0U)
#define RM_L4PER3_DCC1_CONTEXT_LOSTCONTEXT_DFF_MASK                                     (0x00000001U)
#define RM_L4PER3_DCC1_CONTEXT_LOSTCONTEXT_DFF_LOST                                      (1U)
#define RM_L4PER3_DCC1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                (0U)

#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC2_WKDEP_WKUPDEP_DCC2_EVE1_DISABLED                                        (0U)

#define RM_L4PER3_DCC2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                    (0U)
#define RM_L4PER3_DCC2_CONTEXT_LOSTCONTEXT_DFF_MASK                                     (0x00000001U)
#define RM_L4PER3_DCC2_CONTEXT_LOSTCONTEXT_DFF_LOST                                      (1U)
#define RM_L4PER3_DCC2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                (0U)

#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC3_WKDEP_WKUPDEP_DCC3_EVE1_DISABLED                                        (0U)

#define RM_L4PER3_DCC3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                    (0U)
#define RM_L4PER3_DCC3_CONTEXT_LOSTCONTEXT_DFF_MASK                                     (0x00000001U)
#define RM_L4PER3_DCC3_CONTEXT_LOSTCONTEXT_DFF_LOST                                      (1U)
#define RM_L4PER3_DCC3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                (0U)

#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP1_SHIFT                                        (2U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP1_MASK                                         (0x00000004U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_SDMA_SHIFT                                        (3U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_SDMA_MASK                                         (0x00000008U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_SDMA_ENABLED                                       (1U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_SDMA_DISABLED                                      (0U)

#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_IPU1_SHIFT                                        (4U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_IPU1_MASK                                         (0x00000010U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_IPU1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_IPU1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP2_SHIFT                                        (5U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP2_MASK                                         (0x00000020U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP2_ENABLED                                       (1U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_DSP2_DISABLED                                      (0U)

#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_EVE1_SHIFT                                        (6U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_EVE1_MASK                                         (0x00000040U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_EVE1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI1_WKDEP_WKUPDEP_MCSPI1_EVE1_DISABLED                                      (0U)

#define RM_L4PER_MCSPI1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_MCSPI1_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_MCSPI1_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_MCSPI1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP1_SHIFT                                        (2U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP1_MASK                                         (0x00000004U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_SDMA_SHIFT                                        (3U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_SDMA_MASK                                         (0x00000008U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_SDMA_ENABLED                                       (1U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_SDMA_DISABLED                                      (0U)

#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_IPU1_SHIFT                                        (4U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_IPU1_MASK                                         (0x00000010U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_IPU1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_IPU1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP2_SHIFT                                        (5U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP2_MASK                                         (0x00000020U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP2_ENABLED                                       (1U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_DSP2_DISABLED                                      (0U)

#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_EVE1_SHIFT                                        (6U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_EVE1_MASK                                         (0x00000040U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_EVE1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI2_WKDEP_WKUPDEP_MCSPI2_EVE1_DISABLED                                      (0U)

#define RM_L4PER_MCSPI2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_MCSPI2_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_MCSPI2_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_MCSPI2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP1_SHIFT                                        (2U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP1_MASK                                         (0x00000004U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_SDMA_SHIFT                                        (3U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_SDMA_MASK                                         (0x00000008U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_SDMA_ENABLED                                       (1U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_SDMA_DISABLED                                      (0U)

#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_IPU1_SHIFT                                        (4U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_IPU1_MASK                                         (0x00000010U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_IPU1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_IPU1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP2_SHIFT                                        (5U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP2_MASK                                         (0x00000020U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP2_ENABLED                                       (1U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_DSP2_DISABLED                                      (0U)

#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_EVE1_SHIFT                                        (6U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_EVE1_MASK                                         (0x00000040U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_EVE1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI3_WKDEP_WKUPDEP_MCSPI3_EVE1_DISABLED                                      (0U)

#define RM_L4PER_MCSPI3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_MCSPI3_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_MCSPI3_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_MCSPI3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP1_SHIFT                                        (2U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP1_MASK                                         (0x00000004U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_SDMA_SHIFT                                        (3U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_SDMA_MASK                                         (0x00000008U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_SDMA_ENABLED                                       (1U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_SDMA_DISABLED                                      (0U)

#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_IPU1_SHIFT                                        (4U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_IPU1_MASK                                         (0x00000010U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_IPU1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_IPU1_DISABLED                                      (0U)

#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP2_SHIFT                                        (5U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP2_MASK                                         (0x00000020U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP2_ENABLED                                       (1U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_DSP2_DISABLED                                      (0U)

#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_EVE1_SHIFT                                        (6U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_EVE1_MASK                                         (0x00000040U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_EVE1_ENABLED                                       (1U)
#define PM_L4PER_MCSPI4_WKDEP_WKUPDEP_MCSPI4_EVE1_DISABLED                                      (0U)

#define RM_L4PER_MCSPI4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER_MCSPI4_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER_MCSPI4_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER_MCSPI4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP1_SHIFT                                          (2U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP1_ENABLED                                         (1U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP1_DISABLED                                        (0U)

#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_SDMA_SHIFT                                          (3U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_SDMA_MASK                                           (0x00000008U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_SDMA_ENABLED                                         (1U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_SDMA_DISABLED                                        (0U)

#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_IPU1_SHIFT                                          (4U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_IPU1_ENABLED                                         (1U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_IPU1_DISABLED                                        (0U)

#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP2_SHIFT                                          (5U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP2_ENABLED                                         (1U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_DSP2_DISABLED                                        (0U)

#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_EVE1_SHIFT                                          (6U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_EVE1_ENABLED                                         (1U)
#define PM_L4PER_MMC4_WKDEP_WKUPDEP_MMC4_EVE1_DISABLED                                        (0U)

#define RM_L4PER_MMC4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                (0U)
#define RM_L4PER_MMC4_CONTEXT_LOSTCONTEXT_DFF_MASK                                 (0x00000001U)
#define RM_L4PER_MMC4_CONTEXT_LOSTCONTEXT_DFF_LOST                                  (1U)
#define RM_L4PER_MMC4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                            (0U)

#define RM_L4PER_MMC4_CONTEXT_LOSTMEM_NONRETAINED_BANK_SHIFT                       (8U)
#define RM_L4PER_MMC4_CONTEXT_LOSTMEM_NONRETAINED_BANK_MASK                        (0x00000100U)
#define RM_L4PER_MMC4_CONTEXT_LOSTMEM_NONRETAINED_BANK_LOST                         (1U)
#define RM_L4PER_MMC4_CONTEXT_LOSTMEM_NONRETAINED_BANK_MAINTAINED                   (0U)

#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP1_SHIFT                                          (2U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP1_MASK                                           (0x00000004U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP1_ENABLED                                         (1U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP1_DISABLED                                        (0U)

#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_IPU1_SHIFT                                          (4U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_IPU1_MASK                                           (0x00000010U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_IPU1_ENABLED                                         (1U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_IPU1_DISABLED                                        (0U)

#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP2_SHIFT                                          (5U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP2_MASK                                           (0x00000020U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP2_ENABLED                                         (1U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_DSP2_DISABLED                                        (0U)

#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_EVE1_SHIFT                                          (6U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_EVE1_MASK                                           (0x00000040U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_EVE1_ENABLED                                         (1U)
#define PM_L4PER_DCC4_WKDEP_WKUPDEP_DCC4_EVE1_DISABLED                                        (0U)

#define RM_L4PER3_DCC4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                    (0U)
#define RM_L4PER3_DCC4_CONTEXT_LOSTCONTEXT_DFF_MASK                                     (0x00000001U)
#define RM_L4PER3_DCC4_CONTEXT_LOSTCONTEXT_DFF_LOST                                      (1U)
#define RM_L4PER3_DCC4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                (0U)

#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP1_SHIFT                                                        (2U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP1_MASK                                                         (0x00000004U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP1_ENABLED                                                       (1U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP1_DISABLED                                                      (0U)

#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_IPU1_SHIFT                                                        (4U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_IPU1_MASK                                                         (0x00000010U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_IPU1_ENABLED                                                       (1U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_IPU1_DISABLED                                                      (0U)

#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP2_SHIFT                                                        (5U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP2_MASK                                                         (0x00000020U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP2_ENABLED                                                       (1U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_DSP2_DISABLED                                                      (0U)

#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_EVE1_SHIFT                                                        (6U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_EVE1_MASK                                                         (0x00000040U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_EVE1_ENABLED                                                       (1U)
#define PM_L4PER2_QSPI_WKDEP_WKUPDEP_QSPI_EVE1_DISABLED                                                      (0U)

#define RM_L4PER2_QSPI_CONTEXT_LOSTCONTEXT_DFF_SHIFT                               (0U)
#define RM_L4PER2_QSPI_CONTEXT_LOSTCONTEXT_DFF_MASK                                (0x00000001U)
#define RM_L4PER2_QSPI_CONTEXT_LOSTCONTEXT_DFF_LOST                                 (1U)
#define RM_L4PER2_QSPI_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                           (0U)

#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP1_SHIFT                                                       (2U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP1_MASK                                                        (0x00000004U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP1_ENABLED                                                      (1U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP1_DISABLED                                                     (0U)

#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_SDMA_SHIFT                                                       (3U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_SDMA_MASK                                                        (0x00000008U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_SDMA_ENABLED                                                      (1U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_SDMA_DISABLED                                                     (0U)

#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_IPU1_SHIFT                                                       (4U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_IPU1_MASK                                                        (0x00000010U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_IPU1_ENABLED                                                      (1U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_IPU1_DISABLED                                                     (0U)

#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP2_SHIFT                                                       (5U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP2_MASK                                                        (0x00000020U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP2_ENABLED                                                      (1U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_DSP2_DISABLED                                                     (0U)

#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_EVE1_SHIFT                                                       (6U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_EVE1_MASK                                                        (0x00000040U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_EVE1_ENABLED                                                      (1U)
#define PM_L4PER_UART1_WKDEP_WKUPDEP_UART1_EVE1_DISABLED                                                     (0U)

#define RM_L4PER_UART1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_UART1_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_UART1_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_UART1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define RM_L4PER_UART1_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                         (8U)
#define RM_L4PER_UART1_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                          (0x00000100U)
#define RM_L4PER_UART1_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                           (1U)
#define RM_L4PER_UART1_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                     (0U)

#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP1_SHIFT                                                       (2U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP1_MASK                                                        (0x00000004U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP1_ENABLED                                                      (1U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP1_DISABLED                                                     (0U)

#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_SDMA_SHIFT                                                       (3U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_SDMA_MASK                                                        (0x00000008U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_SDMA_ENABLED                                                      (1U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_SDMA_DISABLED                                                     (0U)

#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_IPU1_SHIFT                                                       (4U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_IPU1_MASK                                                        (0x00000010U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_IPU1_ENABLED                                                      (1U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_IPU1_DISABLED                                                     (0U)

#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP2_SHIFT                                                       (5U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP2_MASK                                                        (0x00000020U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP2_ENABLED                                                      (1U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_DSP2_DISABLED                                                     (0U)

#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_EVE1_SHIFT                                                       (6U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_EVE1_MASK                                                        (0x00000040U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_EVE1_ENABLED                                                      (1U)
#define PM_L4PER_UART2_WKDEP_WKUPDEP_UART2_EVE1_DISABLED                                                     (0U)

#define RM_L4PER_UART2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_UART2_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_UART2_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_UART2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define RM_L4PER_UART2_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                         (8U)
#define RM_L4PER_UART2_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                          (0x00000100U)
#define RM_L4PER_UART2_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                           (1U)
#define RM_L4PER_UART2_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                     (0U)

#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP1_SHIFT                                                       (2U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP1_MASK                                                        (0x00000004U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP1_ENABLED                                                      (1U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP1_DISABLED                                                     (0U)

#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_SDMA_SHIFT                                                       (3U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_SDMA_MASK                                                        (0x00000008U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_SDMA_ENABLED                                                      (1U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_SDMA_DISABLED                                                     (0U)

#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_IPU1_SHIFT                                                       (4U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_IPU1_MASK                                                        (0x00000010U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_IPU1_ENABLED                                                      (1U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_IPU1_DISABLED                                                     (0U)

#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP2_SHIFT                                                       (5U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP2_MASK                                                        (0x00000020U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP2_ENABLED                                                      (1U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_DSP2_DISABLED                                                     (0U)

#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_EVE1_SHIFT                                                       (6U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_EVE1_MASK                                                        (0x00000040U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_EVE1_ENABLED                                                      (1U)
#define PM_L4PER_UART3_WKDEP_WKUPDEP_UART3_EVE1_DISABLED                                                     (0U)

#define RM_L4PER_UART3_CONTEXT_LOSTCONTEXT_RFF_SHIFT                               (1U)
#define RM_L4PER_UART3_CONTEXT_LOSTCONTEXT_RFF_MASK                                (0x00000002U)
#define RM_L4PER_UART3_CONTEXT_LOSTCONTEXT_RFF_LOST                                 (1U)
#define RM_L4PER_UART3_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                           (0U)

#define RM_L4PER_UART3_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                         (8U)
#define RM_L4PER_UART3_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                          (0x00000100U)
#define RM_L4PER_UART3_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                           (1U)
#define RM_L4PER_UART3_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                     (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP1_SHIFT                                      (2U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP1_MASK                                       (0x00000004U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP1_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP1_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_IPU1_SHIFT                                      (4U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_IPU1_MASK                                       (0x00000010U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_IPU1_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_IPU1_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP2_SHIFT                                      (5U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP2_MASK                                       (0x00000020U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP2_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_DSP2_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_EVE1_SHIFT                                      (6U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_EVE1_MASK                                       (0x00000040U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_EVE1_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_IRQ_EVE1_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_SDMA_SHIFT                                      (13U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_SDMA_MASK                                       (0x00002000U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_SDMA_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_SDMA_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP1_SHIFT                                      (12U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP1_MASK                                       (0x00001000U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP1_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP1_DISABLED                                    (0U)

#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP2_SHIFT                                      (15U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP2_MASK                                       (0x00008000U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP2_ENABLED                                     (1U)
#define PM_L4PER2_ADC_WKDEP_WKUPDEP_ADC_DMA_DSP2_DISABLED                                    (0U)

#define RM_L4PER2_ADC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                     (0U)
#define RM_L4PER2_ADC_CONTEXT_LOSTCONTEXT_DFF_MASK                                      (0x00000001U)
#define RM_L4PER2_ADC_CONTEXT_LOSTCONTEXT_DFF_LOST                                       (1U)
#define RM_L4PER2_ADC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                 (0U)

#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                    (8U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                     (0x00000100U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                      (1U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                (0U)

#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTCONTEXT_RFF_SHIFT                          (1U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTCONTEXT_RFF_MASK                           (0x00000002U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTCONTEXT_RFF_LOST                            (1U)
#define RM_L4SEC_DMA_CRYPTO_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                      (0U)

#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP1_SHIFT                                        (2U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP1_MASK                                         (0x00000004U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP1_ENABLED                                       (1U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP1_DISABLED                                      (0U)

#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_SDMA_SHIFT                                        (3U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_SDMA_MASK                                         (0x00000008U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_SDMA_ENABLED                                       (1U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_SDMA_DISABLED                                      (0U)

#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_IPU1_SHIFT                                        (4U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_IPU1_MASK                                         (0x00000010U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_IPU1_ENABLED                                       (1U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_IPU1_DISABLED                                      (0U)

#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP2_SHIFT                                        (5U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP2_MASK                                         (0x00000020U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP2_ENABLED                                       (1U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_DSP2_DISABLED                                      (0U)

#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_EVE1_SHIFT                                        (6U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_EVE1_MASK                                         (0x00000040U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_EVE1_ENABLED                                       (1U)
#define PM_L4PER2_DCAN2_WKDEP_WKUPDEP_DCAN2_EVE1_DISABLED                                      (0U)

#define RM_L4PER2_DCAN2_CONTEXT_LOSTMEM_DCAN_BANK_SHIFT                            (8U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTMEM_DCAN_BANK_MASK                             (0x00000100U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTMEM_DCAN_BANK_LOST                              (1U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTMEM_DCAN_BANK_MAINTAINED                        (0U)

#define RM_L4PER2_DCAN2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4PER2_DCAN2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4PER_PRM_H_ */

