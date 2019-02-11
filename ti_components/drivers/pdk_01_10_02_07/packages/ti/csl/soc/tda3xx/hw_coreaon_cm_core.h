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
 *  \file   hw_coreaon_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_COREAON_CM_CORE_H_
#define HW_COREAON_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CM_COREAON_CLKSTCTRL                                        (0x0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL                    (0x38U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL                           (0x50U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL                     (0x58U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL                  (0x68U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL                       (0xa0U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL                       (0xb0U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL                       (0xc0U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL                       (0xd0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_SHIFT                                            (0U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_MASK                                             (0x00000003U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                          (0U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_RESERVED                                          (1U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                           (2U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                           (3U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_SHIFT                                             (8U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_MASK                                              (0x00000100U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_INACT                                              (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_ACT                                                (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_SHIFT                         (10U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_MASK                          (0x00000400U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_INACT                          (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_ACT                            (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_SHIFT                        (11U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_MASK                         (0x00000800U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_INACT                         (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_ACT                           (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_SHIFT                                            (12U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_MASK                                             (0x00001000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_INACT                                             (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_ACT                                               (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_IO_SRCOMP_GFCLK_SHIFT                          (14U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_IO_SRCOMP_GFCLK_MASK                           (0x00004000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_IO_SRCOMP_GFCLK_INACT                           (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_IO_SRCOMP_GFCLK_ACT                             (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_SHIFT                      (13U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_MASK                       (0x00002000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_INACT                       (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_ACT                         (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_SHIFT                                (16U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_MASK                                 (0x00010000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_INACT                                 (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_ACT                                   (1U)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_SHIFT                           (16U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_MASK                            (0x00030000U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_DISABLE                          (3U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_IDLE                             (2U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_FUNC                             (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_TRANS                            (1U)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_SHIFT                       (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_MASK                        (0x00000003U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_DISABLED                     (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_RESERVED_1                   (1U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_ENABLE                       (2U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_RESERVED                     (3U)

#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_SHIFT                                                (8U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_MASK                                                 (0x00000100U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_FCLK_DIS                                              (0U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_FCLK_EN                                               (1U)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_SHIFT                            (16U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_MASK                             (0x00030000U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_DISABLE                           (3U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_IDLE                              (2U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_FUNC                              (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_TRANS                             (1U)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_SHIFT                        (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_MASK                         (0x00000003U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_DISABLED                      (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_RESERVED_1                    (1U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_ENABLE                        (2U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_RESERVED                      (3U)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_SHIFT                         (16U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_MASK                          (0x00030000U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_DISABLE                        (3U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_IDLE                           (2U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_FUNC                           (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_TRANS                          (1U)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_SHIFT                     (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_MASK                      (0x00000003U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_DISABLED                   (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_RESERVED_1                 (1U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_ENABLE                     (2U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_RESERVED                   (3U)

#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_SHIFT            (8U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_MASK             (0x00000100U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_FCLK_EN           (1U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_FCLK_DIS          (0U)

#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_SHIFT            (8U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_MASK             (0x00000100U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_FCLK_EN           (1U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_FCLK_DIS          (0U)

#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_SHIFT          (8U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_MASK           (0x00000100U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_FCLK_EN         (1U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_FCLK_DIS        (0U)

#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_SHIFT                 (8U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_MASK                  (0x00000100U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_FCLK_EN                (1U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_FCLK_DIS               (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_COREAON_CM_CORE_H_ */

