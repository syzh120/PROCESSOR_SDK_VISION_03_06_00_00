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
 *  \file   hw_wkupaon_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_WKUPAON_PRM_H_
#define HW_WKUPAON_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define RM_WKUPAON_L4_WKUP_CONTEXT                             (0x0U)
#define PM_WKUPAON_WD_TIMER1_WKDEP                                  (0x4U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT                           (0x8U)
#define PM_WKUPAON_WD_TIMER2_WKDEP                                  (0xcU)
#define RM_WKUPAON_WD_TIMER2_CONTEXT                           (0x10U)
#define PM_WKUPAON_GPIO1_WKDEP                                      (0x14U)
#define RM_WKUPAON_GPIO1_CONTEXT                               (0x18U)
#define PM_WKUPAON_TIMER1_WKDEP                                     (0x1cU)
#define RM_WKUPAON_TIMER1_CONTEXT                              (0x20U)
#define PM_WKUPAON_TIMER12_WKDEP                                    (0x24U)
#define RM_WKUPAON_TIMER12_CONTEXT                             (0x28U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT                         (0x30U)
#define PM_WKUPAON_KBD_WKDEP                                        (0x54U)
#define RM_WKUPAON_KBD_CONTEXT                                 (0x58U)
#define PM_WKUPAON_UART10_WKDEP                                     (0x5cU)
#define RM_WKUPAON_UART10_CONTEXT                              (0x60U)
#define PM_WKUPAON_DCAN1_WKDEP                                      (0x64U)
#define RM_WKUPAON_DCAN1_CONTEXT                               (0x68U)
#define RM_WKUPAON_SPARE_SAFETY1_CONTEXT                       (0x90U)
#define RM_WKUPAON_RTI1_CONTEXT                                     (0x98U)
#define RM_WKUPAON_RTI2_CONTEXT                                     (0xa0U)
#define RM_WKUPAON_RTI3_CONTEXT                                     (0xa8U)
#define RM_WKUPAON_RTI4_CONTEXT                                     (0xb0U)
#define RM_WKUPAON_RTI5_CONTEXT                                     (0xb8U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_SHIFT                           (0U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_MASK                            (0x00000001U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_LOST                             (1U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                       (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_SHIFT                                             (2U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_MASK                                              (0x00000004U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_SHIFT                                             (4U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_MASK                                              (0x00000010U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_SHIFT                                             (5U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_MASK                                              (0x00000020U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_SHIFT                                             (6U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_MASK                                              (0x00000040U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_DISABLED                                           (0U)

#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                         (0U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MASK                          (0x00000001U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_LOST                           (1U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                     (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_SHIFT                                             (2U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_MASK                                              (0x00000004U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_SHIFT                                             (4U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_MASK                                              (0x00000010U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_SHIFT                                             (5U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_MASK                                              (0x00000020U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_SHIFT                                             (6U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_MASK                                              (0x00000040U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_DISABLED                                           (0U)

#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                         (0U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MASK                          (0x00000001U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_LOST                           (1U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                     (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_SHIFT                                                (2U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_MASK                                                 (0x00000004U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_SHIFT                                                (4U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_MASK                                                 (0x00000010U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_SHIFT                                                (5U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_MASK                                                 (0x00000020U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_SHIFT                                                (6U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_MASK                                                 (0x00000040U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_SHIFT                                                (12U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_MASK                                                 (0x00001000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_SHIFT                                                (14U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_MASK                                                 (0x00004000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_SHIFT                                                (15U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_MASK                                                 (0x00008000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_SHIFT                                                (16U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_MASK                                                 (0x00010000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_DISABLED                                              (0U)

#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                             (0U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_MASK                              (0x00000001U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_LOST                               (1U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                         (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_SHIFT                                      (2U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_MASK                                       (0x00000004U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_ENABLED                                     (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_DISABLED                                    (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_SHIFT                                                   (4U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_MASK                                                    (0x00000010U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_SHIFT                                                   (5U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_MASK                                                    (0x00000020U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_SHIFT                                                   (6U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_MASK                                                    (0x00000040U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_DISABLED                                                 (0U)

#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                            (0U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MASK                             (0x00000001U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_LOST                              (1U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                        (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_SHIFT                                                 (2U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_MASK                                                  (0x00000004U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_SHIFT                                                 (4U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_MASK                                                  (0x00000010U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_SHIFT                                                 (5U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_MASK                                                  (0x00000020U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_SHIFT                                                 (6U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_MASK                                                  (0x00000040U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_DISABLED                                               (0U)

#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_SHIFT                           (0U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_MASK                            (0x00000001U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_LOST                             (1U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                       (0U)

#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_SHIFT                       (0U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_MASK                        (0x00000001U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_LOST                         (1U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                   (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_SHIFT                                                         (2U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_MASK                                                          (0x00000004U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_SHIFT                                                         (4U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_MASK                                                          (0x00000010U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_SHIFT                                                         (5U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_MASK                                                          (0x00000020U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_SHIFT                                                         (6U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_MASK                                                          (0x00000040U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_DISABLED                                                       (0U)

#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_SHIFT                               (0U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_MASK                                (0x00000001U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_LOST                                 (1U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                           (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_SHIFT                                                   (2U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_MASK                                                    (0x00000004U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_SHIFT                                                   (3U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_MASK                                                    (0x00000008U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_SHIFT                                                   (4U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_MASK                                                    (0x00000010U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_SHIFT                                                   (5U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_MASK                                                    (0x00000020U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_SHIFT                                                   (6U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_MASK                                                    (0x00000040U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_DISABLED                                                 (0U)

#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                      (8U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                       (0x00000100U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                        (1U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                  (0U)

#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_SHIFT                            (0U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_MASK                             (0x00000001U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_LOST                              (1U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                        (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_SHIFT                                                     (2U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_MASK                                                      (0x00000004U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_SHIFT                                                     (3U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_MASK                                                      (0x00000008U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_SHIFT                                                     (4U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_MASK                                                      (0x00000010U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_SHIFT                                                     (5U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_MASK                                                      (0x00000020U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_SHIFT                                                     (6U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_MASK                                                      (0x00000040U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_DISABLED                                                   (0U)

#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_SHIFT                            (8U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_MASK                             (0x00000100U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_LOST                              (1U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_MAINTAINED                        (0U)

#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                             (0U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_MASK                              (0x00000001U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_LOST                               (1U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                         (0U)

#define RM_WKUPAON_SPARE_SAFETY1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                     (0U)
#define RM_WKUPAON_SPARE_SAFETY1_CONTEXT_LOSTCONTEXT_DFF_MASK                      (0x00000001U)
#define RM_WKUPAON_SPARE_SAFETY1_CONTEXT_LOSTCONTEXT_DFF_LOST                       (1U)
#define RM_WKUPAON_SPARE_SAFETY1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                 (0U)

#define RM_WKUPAON_RTI1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                   (0U)
#define RM_WKUPAON_RTI1_CONTEXT_LOSTCONTEXT_DFF_MASK                                    (0x00000001U)
#define RM_WKUPAON_RTI1_CONTEXT_LOSTCONTEXT_DFF_LOST                                     (1U)
#define RM_WKUPAON_RTI1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                               (0U)

#define RM_WKUPAON_RTI2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                   (0U)
#define RM_WKUPAON_RTI2_CONTEXT_LOSTCONTEXT_DFF_MASK                                    (0x00000001U)
#define RM_WKUPAON_RTI2_CONTEXT_LOSTCONTEXT_DFF_LOST                                     (1U)
#define RM_WKUPAON_RTI2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                               (0U)

#define RM_WKUPAON_RTI3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                   (0U)
#define RM_WKUPAON_RTI3_CONTEXT_LOSTCONTEXT_DFF_MASK                                    (0x00000001U)
#define RM_WKUPAON_RTI3_CONTEXT_LOSTCONTEXT_DFF_LOST                                     (1U)
#define RM_WKUPAON_RTI3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                               (0U)

#define RM_WKUPAON_RTI4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                   (0U)
#define RM_WKUPAON_RTI4_CONTEXT_LOSTCONTEXT_DFF_MASK                                    (0x00000001U)
#define RM_WKUPAON_RTI4_CONTEXT_LOSTCONTEXT_DFF_LOST                                     (1U)
#define RM_WKUPAON_RTI4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                               (0U)

#define RM_WKUPAON_RTI5_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                   (0U)
#define RM_WKUPAON_RTI5_CONTEXT_LOSTCONTEXT_DFF_MASK                                    (0x00000001U)
#define RM_WKUPAON_RTI5_CONTEXT_LOSTCONTEXT_DFF_LOST                                     (1U)
#define RM_WKUPAON_RTI5_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                               (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_WKUPAON_PRM_H_ */

