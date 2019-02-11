/*
* hw_dss_family.h
*
* Register-level header file for DSS
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef HW_DSS_FAMILY_H_
#define HW_DSS_FAMILY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DSS_REVISION                                                                                        (0x0U)
#define DSS_FAMILY_SYSCONFIG                                                                                (0x10U)
#define DSS_SYSSTATUS                                                                                       (0x14U)
#define DSS_CTRL                                                                                            (0x40U)
#define DSS_STATUS                                                                                          (0x5cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_REVISION_REVISION_SHIFT                                                                         (0U)
#define DSS_REVISION_REVISION_MASK                                                                          (0xffffffffU)

#define DSS_SYSSTATUS_RESETDONE_SHIFT                                                                       (0U)
#define DSS_SYSSTATUS_RESETDONE_MASK                                                                        (0x00000001U)
#define DSS_SYSSTATUS_RESETDONE_RSTCOMP                                                                      (1U)
#define DSS_SYSSTATUS_RESETDONE_RSTACT                                                                       (0U)

#define DSS_SYSSTATUS_RESERVED_6_SHIFT                                                                      (1U)
#define DSS_SYSSTATUS_RESERVED_6_MASK                                                                       (0xfffffffeU)

#define DSS_CTRL_LCD1_CLK_SWITCH_SHIFT                                                                      (0U)
#define DSS_CTRL_LCD1_CLK_SWITCH_MASK                                                                       (0x00000001U)
#define DSS_CTRL_LCD1_CLK_SWITCH_DSS_CLK_SEL                                                                 (0U)
#define DSS_CTRL_LCD1_CLK_SWITCH_DPLL_DSI1_A_CLK1_SEL                                                        (1U)

#define DSS_CTRL_DSI1_A_CLK_SWITCH_SHIFT                                                                    (1U)
#define DSS_CTRL_DSI1_A_CLK_SWITCH_MASK                                                                     (0x00000002U)
#define DSS_CTRL_DSI1_A_CLK_SWITCH_DPLL_DSI1_A_CLK2_SEL                                                      (1U)
#define DSS_CTRL_DSI1_A_CLK_SWITCH_DSS_CLK_SEL                                                               (0U)

#define DSS_CTRL_FCK_CLK_SWITCH_SHIFT                                                                       (7U)
#define DSS_CTRL_FCK_CLK_SWITCH_MASK                                                                        (0x00000380U)
#define DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_A_CLK1                                                             (1U)
#define DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_B_CLK1                                                             (2U)
#define DSS_CTRL_FCK_CLK_SWITCH_DPLL_HDMI_CLK1                                                               (3U)
#define DSS_CTRL_FCK_CLK_SWITCH_DSS_CLK                                                                      (0U)
#define DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_C_CLK1                                                             (4U)

#define DSS_CTRL_LCD2_CLK_SWITCH_SHIFT                                                                      (12U)
#define DSS_CTRL_LCD2_CLK_SWITCH_MASK                                                                       (0x00001000U)
#define DSS_CTRL_LCD2_CLK_SWITCH_DSS_CLK_SEL                                                                 (0U)
#define DSS_CTRL_LCD2_CLK_SWITCH_DPLL_DSI1_B_CLK1_SEL                                                        (1U)

#define DSS_CTRL_LCD3_CLK_SWITCH_SHIFT                                                                      (19U)
#define DSS_CTRL_LCD3_CLK_SWITCH_MASK                                                                       (0x00080000U)
#define DSS_CTRL_LCD3_CLK_SWITCH_DSS_CLK_SEL                                                                 (0U)
#define DSS_CTRL_LCD3_CLK_SWITCH_DPLL_DSI1_C_CLK1_SEL                                                        (1U)

#define DSS_CTRL_PARALLEL_SEL_SHIFT                                                                         (16U)
#define DSS_CTRL_PARALLEL_SEL_MASK                                                                          (0x00030000U)
#define DSS_CTRL_PARALLEL_SEL_LCD1                                                                           (1U)
#define DSS_CTRL_PARALLEL_SEL_HDMI                                                                           (0U)
#define DSS_CTRL_PARALLEL_SEL_LCD2                                                                           (2U)
#define DSS_CTRL_PARALLEL_SEL_LCD3                                                                           (3U)

#define DSS_CTRL_RESERVED2_SHIFT                                                                            (11U)
#define DSS_CTRL_RESERVED2_MASK                                                                             (0x00000800U)

#define DSS_CTRL_RESERVED4_SHIFT                                                                            (13U)
#define DSS_CTRL_RESERVED4_MASK                                                                             (0x00002000U)

#define DSS_CTRL_RESERVED1_SHIFT                                                                            (2U)
#define DSS_CTRL_RESERVED1_MASK                                                                             (0x0000007cU)

#define DSS_CTRL_DSI1_C_CLK_SWITCH_SHIFT                                                                    (18U)
#define DSS_CTRL_DSI1_C_CLK_SWITCH_MASK                                                                     (0x00040000U)
#define DSS_CTRL_DSI1_C_CLK_SWITCH_DPLL_DSI1_C_CLK2_SEL                                                      (1U)
#define DSS_CTRL_DSI1_C_CLK_SWITCH_DSS_CLK_SEL                                                               (0U)

#define DSS_CTRL_RESERVED_SHIFT                                                                             (15U)
#define DSS_CTRL_RESERVED_MASK                                                                              (0x00008000U)

#define DSS_CTRL_RESERVED3_SHIFT                                                                            (21U)
#define DSS_CTRL_RESERVED3_MASK                                                                             (0xffe00000U)

#define DSS_CTRL_RESERVED_2_SHIFT                                                                           (10U)
#define DSS_CTRL_RESERVED_2_MASK                                                                            (0x00000400U)

#define DSS_CTRL_RESERVED_3_SHIFT                                                                           (12U)
#define DSS_CTRL_RESERVED_3_MASK                                                                            (0x00001000U)

#define DSS_CTRL_RESERVED_4_SHIFT                                                                           (14U)
#define DSS_CTRL_RESERVED_4_MASK                                                                            (0x00004000U)

#define DSS_CTRL_RESERVED_5_SHIFT                                                                           (19U)
#define DSS_CTRL_RESERVED_5_MASK                                                                            (0x00180000U)

#define DSS_STATUS_LCD1_CLK_STATUS_SHIFT                                                                    (0U)
#define DSS_STATUS_LCD1_CLK_STATUS_MASK                                                                     (0x00000003U)
#define DSS_STATUS_LCD1_CLK_STATUS_DSS_CLK_SEL                                                               (1U)
#define DSS_STATUS_LCD1_CLK_STATUS_DPLL_DSI1_A_CLK1_SEL                                                      (2U)
#define DSS_STATUS_LCD1_CLK_STATUS_LCD1_CLK_TRANSITION                                                       (0U)

#define DSS_STATUS_LCD2_CLK_STATUS_SHIFT                                                                    (11U)
#define DSS_STATUS_LCD2_CLK_STATUS_MASK                                                                     (0x00001800U)
#define DSS_STATUS_LCD2_CLK_STATUS_SEL                                                                       (1U)
#define DSS_STATUS_LCD2_CLK_STATUS_DPLL_DSI1_B_CLK1_SEL                                                      (2U)
#define DSS_STATUS_LCD2_CLK_STATUS_TRANSITION                                                                (0U)

#define DSS_STATUS_LCD3_CLK_STATUS_SHIFT                                                                    (24U)
#define DSS_STATUS_LCD3_CLK_STATUS_MASK                                                                     (0x03000000U)
#define DSS_STATUS_LCD3_CLK_STATUS_SEL                                                                       (1U)
#define DSS_STATUS_LCD3_CLK_STATUS_DPLL_DSI1_C_CLK1_SEL                                                      (2U)
#define DSS_STATUS_LCD3_CLK_STATUS_TRANSITION                                                                (0U)

#define DSS_STATUS_FCK_CLK_STATUS_SHIFT                                                                     (15U)
#define DSS_STATUS_FCK_CLK_STATUS_MASK                                                                      (0x000f8000U)
#define DSS_STATUS_FCK_CLK_STATUS_DSS_CLK_SEL                                                                (1U)
#define DSS_STATUS_FCK_CLK_STATUS_DPLL_DSI1_A_CLK1_SEL                                                       (2U)
#define DSS_STATUS_FCK_CLK_STATUS_DPLL_DSI1_B_CLK1_SEL                                                       (4U)
#define DSS_STATUS_FCK_CLK_STATUS_DPLL_HDMI_CLK1_SEL                                                         (8U)
#define DSS_STATUS_FCK_CLK_STATUS_DSS_CLK_TRANSITION                                                         (0U)
#define DSS_STATUS_FCK_CLK_STATUS_DPLL_DSI1_C_CLK1_SEL                                                       (16U)

#define DSS_STATUS_RESERVED2_SHIFT                                                                          (5U)
#define DSS_STATUS_RESERVED2_MASK                                                                           (0x00000060U)

#define DSS_STATUS_RESERVED3_SHIFT                                                                          (13U)
#define DSS_STATUS_RESERVED3_MASK                                                                           (0x00006000U)

#define DSS_STATUS_RESERVED1_SHIFT                                                                          (26U)
#define DSS_STATUS_RESERVED1_MASK                                                                           (0xfc000000U)

#define DSS_STATUS_RESERVED_2_SHIFT                                                                         (7U)
#define DSS_STATUS_RESERVED_2_MASK                                                                          (0x00001f80U)

#define DSS_STATUS_RESERVED_3_SHIFT                                                                         (20U)
#define DSS_STATUS_RESERVED_3_MASK                                                                          (0x03f00000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_FAMILY_H_ */
