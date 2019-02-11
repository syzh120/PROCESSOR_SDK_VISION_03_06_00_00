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
 *  \file   hw_ocp_socket_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_OCP_SOCKET_PRM_H_
#define HW_OCP_SOCKET_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define REVISION_PRM                                           (0x0U)
#define PRM_IRQSTATUS_DSP1                                          (0x30U)
#define PRM_IRQENABLE_DSP1                                          (0x38U)
#define CM_PRM_PROFILING_CLKCTRL                               (0x40U)
#define PRM_IRQENABLE_DSP2                                          (0x44U)
#define PRM_IRQENABLE_EVE1                                          (0x48U)
#define PRM_IRQENABLE_IPU1                                          (0x58U)
#define PRM_IRQSTATUS_DSP2                                          (0x5cU)
#define PRM_IRQSTATUS_EVE1                                          (0x60U)
#define PRM_IRQSTATUS_IPU1                                          (0x70U)
#define PRM_DEBUG_CFG1                                         (0xe4U)
#define PRM_DEBUG_CFG2                                         (0xe8U)
#define PRM_DEBUG_CFG3                                         (0xecU)
#define PRM_DEBUG_CFG                                          (0xf0U)
#define PRM_DEBUG_OUT                                          (0xf4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define REVISION_PRM_Y_MINOR_SHIFT                                                 (0U)
#define REVISION_PRM_Y_MINOR_MASK                                                  (0x0000003fU)
#define REVISION_PRM_Y_MINOR_ES1                                                    (0U)
#define REVISION_PRM_Y_MINOR_ES2                                                    (1U)

#define REVISION_PRM_CUSTOM_SHIFT                                                  (6U)
#define REVISION_PRM_CUSTOM_MASK                                                   (0x000000c0U)
#define REVISION_PRM_CUSTOM_STANDARD                                                (0U)

#define REVISION_PRM_R_RTL_SHIFT                                                   (11U)
#define REVISION_PRM_R_RTL_MASK                                                    (0x0000f800U)

#define REVISION_PRM_FUNC_SHIFT                                                    (16U)
#define REVISION_PRM_FUNC_MASK                                                     (0x0fff0000U)

#define REVISION_PRM_SCHEME_SHIFT                                                  (30U)
#define REVISION_PRM_SCHEME_MASK                                                   (0xc0000000U)
#define REVISION_PRM_SCHEME_H08                                                     (1U)
#define REVISION_PRM_SCHEME_LEGACY                                                  (0U)

#define REVISION_PRM_X_MAJOR_SHIFT                                                 (8U)
#define REVISION_PRM_X_MAJOR_MASK                                                  (0x00000700U)
#define REVISION_PRM_X_MAJOR_OMAP4430_ES1_X                                                                  (0U)
#define REVISION_PRM_X_MAJOR_OMAP4430_ES2_X                                                                  (1U)
#define REVISION_PRM_X_MAJOR_OMAP4460                                               (2U)
#define REVISION_PRM_X_MAJOR_OMAP5430                                               (3U)
#define REVISION_PRM_X_MAJOR_OMAP470                                                (4U)

#define PRM_IRQSTATUS_DSP1_DPLL_CORE_RECAL_ST_SHIFT                                     (0U)
#define PRM_IRQSTATUS_DSP1_DPLL_CORE_RECAL_ST_MASK                                      (0x00000001U)
#define PRM_IRQSTATUS_DSP1_DPLL_CORE_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_CORE_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_PER_RECAL_ST_SHIFT                                      (3U)
#define PRM_IRQSTATUS_DSP1_DPLL_PER_RECAL_ST_MASK                                       (0x00000008U)
#define PRM_IRQSTATUS_DSP1_DPLL_PER_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_PER_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_ABE_RECAL_ST_SHIFT                                      (4U)
#define PRM_IRQSTATUS_DSP1_DPLL_ABE_RECAL_ST_MASK                                       (0x00000010U)
#define PRM_IRQSTATUS_DSP1_DPLL_ABE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_ABE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_GMAC_RECAL_ST_SHIFT                                     (5U)
#define PRM_IRQSTATUS_DSP1_DPLL_GMAC_RECAL_ST_MASK                                      (0x00000020U)
#define PRM_IRQSTATUS_DSP1_DPLL_GMAC_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_GMAC_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_GPU_RECAL_ST_SHIFT                                      (6U)
#define PRM_IRQSTATUS_DSP1_DPLL_GPU_RECAL_ST_MASK                                       (0x00000040U)
#define PRM_IRQSTATUS_DSP1_DPLL_GPU_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_GPU_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_DDR_RECAL_ST_SHIFT                                      (7U)
#define PRM_IRQSTATUS_DSP1_DPLL_DDR_RECAL_ST_MASK                                       (0x00000080U)
#define PRM_IRQSTATUS_DSP1_DPLL_DDR_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_DDR_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_IO_ST_SHIFT                                                  (9U)
#define PRM_IRQSTATUS_DSP1_IO_ST_MASK                                                   (0x00000200U)
#define PRM_IRQSTATUS_DSP1_IO_ST_IRQ_TRU                                                 (1U)
#define PRM_IRQSTATUS_DSP1_IO_ST_IRQ_FAL                                                 (0U)

#define PRM_IRQSTATUS_DSP1_FORCEWKUP_ST_SHIFT                                           (10U)
#define PRM_IRQSTATUS_DSP1_FORCEWKUP_ST_MASK                                            (0x00000400U)
#define PRM_IRQSTATUS_DSP1_FORCEWKUP_ST_IRQ_TRU                                          (1U)
#define PRM_IRQSTATUS_DSP1_FORCEWKUP_ST_IRQ_FAL                                          (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_DSP_RECAL_ST_SHIFT                                      (11U)
#define PRM_IRQSTATUS_DSP1_DPLL_DSP_RECAL_ST_MASK                                       (0x00000800U)
#define PRM_IRQSTATUS_DSP1_DPLL_DSP_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_DSP_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_DPLL_EVE_RECAL_ST_SHIFT                                      (12U)
#define PRM_IRQSTATUS_DSP1_DPLL_EVE_RECAL_ST_MASK                                       (0x00001000U)
#define PRM_IRQSTATUS_DSP1_DPLL_EVE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP1_DPLL_EVE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP1_ABB_GPU_DONE_ST_SHIFT                                        (28U)
#define PRM_IRQSTATUS_DSP1_ABB_GPU_DONE_ST_MASK                                         (0x10000000U)
#define PRM_IRQSTATUS_DSP1_ABB_GPU_DONE_ST_IRQ_TRU                                       (1U)
#define PRM_IRQSTATUS_DSP1_ABB_GPU_DONE_ST_IRQ_FAL                                       (0U)

#define PRM_IRQSTATUS_DSP1_ABB_DSPEVE_DONE_ST_SHIFT                                     (29U)
#define PRM_IRQSTATUS_DSP1_ABB_DSPEVE_DONE_ST_MASK                                      (0x20000000U)
#define PRM_IRQSTATUS_DSP1_ABB_DSPEVE_DONE_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP1_ABB_DSPEVE_DONE_ST_IRQ_FAL                                    (0U)

#define PRM_IRQENABLE_DSP1_DPLL_CORE_RECAL_EN_SHIFT                                     (0U)
#define PRM_IRQENABLE_DSP1_DPLL_CORE_RECAL_EN_MASK                                      (0x00000001U)
#define PRM_IRQENABLE_DSP1_DPLL_CORE_RECAL_EN_IRQ_MSK                                    (0U)
#define PRM_IRQENABLE_DSP1_DPLL_CORE_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_DSP1_DPLL_PER_RECAL_EN_SHIFT                                      (3U)
#define PRM_IRQENABLE_DSP1_DPLL_PER_RECAL_EN_MASK                                       (0x00000008U)
#define PRM_IRQENABLE_DSP1_DPLL_PER_RECAL_EN_IRQ_MSK                                     (0U)
#define PRM_IRQENABLE_DSP1_DPLL_PER_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_DPLL_ABE_RECAL_EN_SHIFT                                                          (4U)
#define PRM_IRQENABLE_DSP1_DPLL_ABE_RECAL_EN_MASK                                                           (0x00000010U)
#define PRM_IRQENABLE_DSP1_DPLL_ABE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_ABE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_DPLL_GMAC_RECAL_EN_SHIFT                                                         (5U)
#define PRM_IRQENABLE_DSP1_DPLL_GMAC_RECAL_EN_MASK                                                          (0x00000020U)
#define PRM_IRQENABLE_DSP1_DPLL_GMAC_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_DSP1_DPLL_GMAC_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_DSP1_DPLL_GPU_RECAL_EN_SHIFT                                                          (6U)
#define PRM_IRQENABLE_DSP1_DPLL_GPU_RECAL_EN_MASK                                                           (0x00000040U)
#define PRM_IRQENABLE_DSP1_DPLL_GPU_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_GPU_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_DPLL_DDR_RECAL_EN_SHIFT                                                          (7U)
#define PRM_IRQENABLE_DSP1_DPLL_DDR_RECAL_EN_MASK                                                           (0x00000080U)
#define PRM_IRQENABLE_DSP1_DPLL_DDR_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_DDR_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_IO_EN_SHIFT                                                                      (9U)
#define PRM_IRQENABLE_DSP1_IO_EN_MASK                                                                       (0x00000200U)
#define PRM_IRQENABLE_DSP1_IO_EN_IRQ_EN                                                                      (1U)
#define PRM_IRQENABLE_DSP1_IO_EN_IRQ_MSK                                                                     (0U)

#define PRM_IRQENABLE_DSP1_FORCEWKUP_EN_SHIFT                                                               (10U)
#define PRM_IRQENABLE_DSP1_FORCEWKUP_EN_MASK                                                                (0x00000400U)
#define PRM_IRQENABLE_DSP1_FORCEWKUP_EN_IRQ_EN                                                               (1U)
#define PRM_IRQENABLE_DSP1_FORCEWKUP_EN_IRQ_MSK                                                              (0U)

#define PRM_IRQENABLE_DSP1_DPLL_DSP_RECAL_EN_SHIFT                                                          (11U)
#define PRM_IRQENABLE_DSP1_DPLL_DSP_RECAL_EN_MASK                                                           (0x00000800U)
#define PRM_IRQENABLE_DSP1_DPLL_DSP_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_DSP_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_DPLL_EVE_RECAL_EN_SHIFT                                                          (12U)
#define PRM_IRQENABLE_DSP1_DPLL_EVE_RECAL_EN_MASK                                                           (0x00001000U)
#define PRM_IRQENABLE_DSP1_DPLL_EVE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_EVE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_DPLL_USB_RECAL_EN_SHIFT                                                          (13U)
#define PRM_IRQENABLE_DSP1_DPLL_USB_RECAL_EN_MASK                                                           (0x00002000U)
#define PRM_IRQENABLE_DSP1_DPLL_USB_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP1_DPLL_USB_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP1_ABB_GPU_DONE_EN_SHIFT                                        (28U)
#define PRM_IRQENABLE_DSP1_ABB_GPU_DONE_EN_MASK                                         (0x10000000U)
#define PRM_IRQENABLE_DSP1_ABB_GPU_DONE_EN_IRQ_TRU                                       (1U)
#define PRM_IRQENABLE_DSP1_ABB_GPU_DONE_EN_IRQ_FAL                                       (0U)

#define PRM_IRQENABLE_DSP1_ABB_DSPEVE_DONE_EN_SHIFT                                     (29U)
#define PRM_IRQENABLE_DSP1_ABB_DSPEVE_DONE_EN_MASK                                      (0x20000000U)
#define PRM_IRQENABLE_DSP1_ABB_DSPEVE_DONE_EN_IRQ_TRU                                    (1U)
#define PRM_IRQENABLE_DSP1_ABB_DSPEVE_DONE_EN_IRQ_FAL                                    (0U)

#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_SHIFT                                  (0U)
#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_MASK                                   (0x00000003U)
#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_DISABLED                                (0U)
#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_AUTO                                    (1U)
#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_RESERVED_2                              (2U)
#define CM_PRM_PROFILING_CLKCTRL_MODULEMODE_RESERVED                                (3U)

#define CM_PRM_PROFILING_CLKCTRL_IDLEST_SHIFT                                      (16U)
#define CM_PRM_PROFILING_CLKCTRL_IDLEST_MASK                                       (0x00030000U)
#define CM_PRM_PROFILING_CLKCTRL_IDLEST_DISABLE                                     (3U)
#define CM_PRM_PROFILING_CLKCTRL_IDLEST_IDLE                                        (2U)
#define CM_PRM_PROFILING_CLKCTRL_IDLEST_FUNC                                        (0U)
#define CM_PRM_PROFILING_CLKCTRL_IDLEST_TRANS                                       (1U)

#define PRM_IRQENABLE_DSP2_DPLL_CORE_RECAL_EN_SHIFT                                     (0U)
#define PRM_IRQENABLE_DSP2_DPLL_CORE_RECAL_EN_MASK                                      (0x00000001U)
#define PRM_IRQENABLE_DSP2_DPLL_CORE_RECAL_EN_IRQ_MSK                                    (0U)
#define PRM_IRQENABLE_DSP2_DPLL_CORE_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_DSP2_DPLL_PER_RECAL_EN_SHIFT                                      (3U)
#define PRM_IRQENABLE_DSP2_DPLL_PER_RECAL_EN_MASK                                       (0x00000008U)
#define PRM_IRQENABLE_DSP2_DPLL_PER_RECAL_EN_IRQ_MSK                                     (0U)
#define PRM_IRQENABLE_DSP2_DPLL_PER_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_DPLL_ABE_RECAL_EN_SHIFT                                                          (4U)
#define PRM_IRQENABLE_DSP2_DPLL_ABE_RECAL_EN_MASK                                                           (0x00000010U)
#define PRM_IRQENABLE_DSP2_DPLL_ABE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP2_DPLL_ABE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_DPLL_GMAC_RECAL_EN_SHIFT                                                         (5U)
#define PRM_IRQENABLE_DSP2_DPLL_GMAC_RECAL_EN_MASK                                                          (0x00000020U)
#define PRM_IRQENABLE_DSP2_DPLL_GMAC_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_DSP2_DPLL_GMAC_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_DSP2_DPLL_GPU_RECAL_EN_SHIFT                                                          (6U)
#define PRM_IRQENABLE_DSP2_DPLL_GPU_RECAL_EN_MASK                                                           (0x00000040U)
#define PRM_IRQENABLE_DSP2_DPLL_GPU_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP2_DPLL_GPU_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_DPLL_DDR_RECAL_EN_SHIFT                                                          (7U)
#define PRM_IRQENABLE_DSP2_DPLL_DDR_RECAL_EN_MASK                                                           (0x00000080U)
#define PRM_IRQENABLE_DSP2_DPLL_DDR_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP2_DPLL_DDR_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_IO_EN_SHIFT                                                                      (9U)
#define PRM_IRQENABLE_DSP2_IO_EN_MASK                                                                       (0x00000200U)
#define PRM_IRQENABLE_DSP2_IO_EN_IRQ_EN                                                                      (1U)
#define PRM_IRQENABLE_DSP2_IO_EN_IRQ_MSK                                                                     (0U)

#define PRM_IRQENABLE_DSP2_FORCEWKUP_EN_SHIFT                                                               (10U)
#define PRM_IRQENABLE_DSP2_FORCEWKUP_EN_MASK                                                                (0x00000400U)
#define PRM_IRQENABLE_DSP2_FORCEWKUP_EN_IRQ_EN                                                               (1U)
#define PRM_IRQENABLE_DSP2_FORCEWKUP_EN_IRQ_MSK                                                              (0U)

#define PRM_IRQENABLE_DSP2_DPLL_DSP_RECAL_EN_SHIFT                                                          (11U)
#define PRM_IRQENABLE_DSP2_DPLL_DSP_RECAL_EN_MASK                                                           (0x00000800U)
#define PRM_IRQENABLE_DSP2_DPLL_DSP_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP2_DPLL_DSP_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_DPLL_EVE_RECAL_EN_SHIFT                                                          (12U)
#define PRM_IRQENABLE_DSP2_DPLL_EVE_RECAL_EN_MASK                                                           (0x00001000U)
#define PRM_IRQENABLE_DSP2_DPLL_EVE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_DSP2_DPLL_EVE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_DSP2_ABB_GPU_DONE_EN_SHIFT                                                            (28U)
#define PRM_IRQENABLE_DSP2_ABB_GPU_DONE_EN_MASK                                                             (0x10000000U)
#define PRM_IRQENABLE_DSP2_ABB_GPU_DONE_EN_IRQ_TRU                                                           (1U)
#define PRM_IRQENABLE_DSP2_ABB_GPU_DONE_EN_IRQ_FAL                                                           (0U)

#define PRM_IRQENABLE_DSP2_ABB_DSPEVE_DONE_EN_SHIFT                                     (29U)
#define PRM_IRQENABLE_DSP2_ABB_DSPEVE_DONE_EN_MASK                                      (0x20000000U)
#define PRM_IRQENABLE_DSP2_ABB_DSPEVE_DONE_EN_IRQ_TRU                                    (1U)
#define PRM_IRQENABLE_DSP2_ABB_DSPEVE_DONE_EN_IRQ_FAL                                    (0U)

#define PRM_IRQENABLE_EVE1_DPLL_CORE_RECAL_EN_SHIFT                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_CORE_RECAL_EN_MASK                                                          (0x00000001U)
#define PRM_IRQENABLE_EVE1_DPLL_CORE_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_EVE1_DPLL_CORE_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_EVE1_DPLL_PER_RECAL_EN_SHIFT                                                          (3U)
#define PRM_IRQENABLE_EVE1_DPLL_PER_RECAL_EN_MASK                                                           (0x00000008U)
#define PRM_IRQENABLE_EVE1_DPLL_PER_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_PER_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_DPLL_ABE_RECAL_EN_SHIFT                                                          (4U)
#define PRM_IRQENABLE_EVE1_DPLL_ABE_RECAL_EN_MASK                                                           (0x00000010U)
#define PRM_IRQENABLE_EVE1_DPLL_ABE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_ABE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_DPLL_GMAC_RECAL_EN_SHIFT                                                         (5U)
#define PRM_IRQENABLE_EVE1_DPLL_GMAC_RECAL_EN_MASK                                                          (0x00000020U)
#define PRM_IRQENABLE_EVE1_DPLL_GMAC_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_EVE1_DPLL_GMAC_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_EVE1_DPLL_GPU_RECAL_EN_SHIFT                                                          (6U)
#define PRM_IRQENABLE_EVE1_DPLL_GPU_RECAL_EN_MASK                                                           (0x00000040U)
#define PRM_IRQENABLE_EVE1_DPLL_GPU_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_GPU_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_DPLL_DDR_RECAL_EN_SHIFT                                                          (7U)
#define PRM_IRQENABLE_EVE1_DPLL_DDR_RECAL_EN_MASK                                                           (0x00000080U)
#define PRM_IRQENABLE_EVE1_DPLL_DDR_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_DDR_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_IO_EN_SHIFT                                                                      (9U)
#define PRM_IRQENABLE_EVE1_IO_EN_MASK                                                                       (0x00000200U)
#define PRM_IRQENABLE_EVE1_IO_EN_IRQ_EN                                                                      (1U)
#define PRM_IRQENABLE_EVE1_IO_EN_IRQ_MSK                                                                     (0U)

#define PRM_IRQENABLE_EVE1_FORCEWKUP_EN_SHIFT                                                               (10U)
#define PRM_IRQENABLE_EVE1_FORCEWKUP_EN_MASK                                                                (0x00000400U)
#define PRM_IRQENABLE_EVE1_FORCEWKUP_EN_IRQ_EN                                                               (1U)
#define PRM_IRQENABLE_EVE1_FORCEWKUP_EN_IRQ_MSK                                                              (0U)

#define PRM_IRQENABLE_EVE1_DPLL_DSP_RECAL_EN_SHIFT                                                          (11U)
#define PRM_IRQENABLE_EVE1_DPLL_DSP_RECAL_EN_MASK                                                           (0x00000800U)
#define PRM_IRQENABLE_EVE1_DPLL_DSP_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_DSP_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_DPLL_EVE_RECAL_EN_SHIFT                                                          (12U)
#define PRM_IRQENABLE_EVE1_DPLL_EVE_RECAL_EN_MASK                                                           (0x00001000U)
#define PRM_IRQENABLE_EVE1_DPLL_EVE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_EVE1_DPLL_EVE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_EVE1_ABB_GPU_DONE_EN_SHIFT                                        (28U)
#define PRM_IRQENABLE_EVE1_ABB_GPU_DONE_EN_MASK                                         (0x10000000U)
#define PRM_IRQENABLE_EVE1_ABB_GPU_DONE_EN_IRQ_TRU                                       (1U)
#define PRM_IRQENABLE_EVE1_ABB_GPU_DONE_EN_IRQ_FAL                                       (0U)

#define PRM_IRQENABLE_EVE1_ABB_DSPEVE_DONE_EN_SHIFT                                     (29U)
#define PRM_IRQENABLE_EVE1_ABB_DSPEVE_DONE_EN_MASK                                      (0x20000000U)
#define PRM_IRQENABLE_EVE1_ABB_DSPEVE_DONE_EN_IRQ_TRU                                    (1U)
#define PRM_IRQENABLE_EVE1_ABB_DSPEVE_DONE_EN_IRQ_FAL                                    (0U)

#define PRM_IRQENABLE_IPU1_DPLL_CORE_RECAL_EN_SHIFT                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_CORE_RECAL_EN_MASK                                                          (0x00000001U)
#define PRM_IRQENABLE_IPU1_DPLL_CORE_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_IPU1_DPLL_CORE_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_IPU1_DPLL_PER_RECAL_EN_SHIFT                                                          (3U)
#define PRM_IRQENABLE_IPU1_DPLL_PER_RECAL_EN_MASK                                                           (0x00000008U)
#define PRM_IRQENABLE_IPU1_DPLL_PER_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_PER_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_DPLL_ABE_RECAL_EN_SHIFT                                                          (4U)
#define PRM_IRQENABLE_IPU1_DPLL_ABE_RECAL_EN_MASK                                                           (0x00000010U)
#define PRM_IRQENABLE_IPU1_DPLL_ABE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_ABE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_DPLL_GMAC_RECAL_EN_SHIFT                                                         (5U)
#define PRM_IRQENABLE_IPU1_DPLL_GMAC_RECAL_EN_MASK                                                          (0x00000020U)
#define PRM_IRQENABLE_IPU1_DPLL_GMAC_RECAL_EN_IRQ_MSK                                                        (0U)
#define PRM_IRQENABLE_IPU1_DPLL_GMAC_RECAL_EN_IRQ_EN                                                         (1U)

#define PRM_IRQENABLE_IPU1_DPLL_GPU_RECAL_EN_SHIFT                                                          (6U)
#define PRM_IRQENABLE_IPU1_DPLL_GPU_RECAL_EN_MASK                                                           (0x00000040U)
#define PRM_IRQENABLE_IPU1_DPLL_GPU_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_GPU_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_DPLL_DDR_RECAL_EN_SHIFT                                                          (7U)
#define PRM_IRQENABLE_IPU1_DPLL_DDR_RECAL_EN_MASK                                                           (0x00000080U)
#define PRM_IRQENABLE_IPU1_DPLL_DDR_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_DDR_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_TRANSITION_EN_SHIFT                                                              (8U)
#define PRM_IRQENABLE_IPU1_TRANSITION_EN_MASK                                                               (0x00000100U)
#define PRM_IRQENABLE_IPU1_TRANSITION_EN_IRQ_EN                                                              (1U)
#define PRM_IRQENABLE_IPU1_TRANSITION_EN_IRQ_MSK                                                             (0U)

#define PRM_IRQENABLE_IPU1_IO_EN_SHIFT                                                                      (9U)
#define PRM_IRQENABLE_IPU1_IO_EN_MASK                                                                       (0x00000200U)
#define PRM_IRQENABLE_IPU1_IO_EN_IRQ_EN                                                                      (1U)
#define PRM_IRQENABLE_IPU1_IO_EN_IRQ_MSK                                                                     (0U)

#define PRM_IRQENABLE_IPU1_FORCEWKUP_EN_SHIFT                                                               (10U)
#define PRM_IRQENABLE_IPU1_FORCEWKUP_EN_MASK                                                                (0x00000400U)
#define PRM_IRQENABLE_IPU1_FORCEWKUP_EN_IRQ_EN                                                               (1U)
#define PRM_IRQENABLE_IPU1_FORCEWKUP_EN_IRQ_MSK                                                              (0U)

#define PRM_IRQENABLE_IPU1_DPLL_DSP_RECAL_EN_SHIFT                                                          (11U)
#define PRM_IRQENABLE_IPU1_DPLL_DSP_RECAL_EN_MASK                                                           (0x00000800U)
#define PRM_IRQENABLE_IPU1_DPLL_DSP_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_DSP_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_DPLL_EVE_RECAL_EN_SHIFT                                                          (12U)
#define PRM_IRQENABLE_IPU1_DPLL_EVE_RECAL_EN_MASK                                                           (0x00001000U)
#define PRM_IRQENABLE_IPU1_DPLL_EVE_RECAL_EN_IRQ_MSK                                                         (0U)
#define PRM_IRQENABLE_IPU1_DPLL_EVE_RECAL_EN_IRQ_EN                                                          (1U)

#define PRM_IRQENABLE_IPU1_ABB_GPU_DONE_EN_SHIFT                                                            (28U)
#define PRM_IRQENABLE_IPU1_ABB_GPU_DONE_EN_MASK                                                             (0x10000000U)
#define PRM_IRQENABLE_IPU1_ABB_GPU_DONE_EN_IRQ_TRU                                                           (1U)
#define PRM_IRQENABLE_IPU1_ABB_GPU_DONE_EN_IRQ_FAL                                                           (0U)

#define PRM_IRQENABLE_IPU1_ABB_DSPEVE_DONE_EN_SHIFT                                                         (29U)
#define PRM_IRQENABLE_IPU1_ABB_DSPEVE_DONE_EN_MASK                                                          (0x20000000U)
#define PRM_IRQENABLE_IPU1_ABB_DSPEVE_DONE_EN_IRQ_TRU                                                        (1U)
#define PRM_IRQENABLE_IPU1_ABB_DSPEVE_DONE_EN_IRQ_FAL                                                        (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_CORE_RECAL_ST_SHIFT                                     (0U)
#define PRM_IRQSTATUS_DSP2_DPLL_CORE_RECAL_ST_MASK                                      (0x00000001U)
#define PRM_IRQSTATUS_DSP2_DPLL_CORE_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_CORE_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_PER_RECAL_ST_SHIFT                                      (3U)
#define PRM_IRQSTATUS_DSP2_DPLL_PER_RECAL_ST_MASK                                       (0x00000008U)
#define PRM_IRQSTATUS_DSP2_DPLL_PER_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_PER_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_ABE_RECAL_ST_SHIFT                                      (4U)
#define PRM_IRQSTATUS_DSP2_DPLL_ABE_RECAL_ST_MASK                                       (0x00000010U)
#define PRM_IRQSTATUS_DSP2_DPLL_ABE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_ABE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_GMAC_RECAL_ST_SHIFT                                     (5U)
#define PRM_IRQSTATUS_DSP2_DPLL_GMAC_RECAL_ST_MASK                                      (0x00000020U)
#define PRM_IRQSTATUS_DSP2_DPLL_GMAC_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_GMAC_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_GPU_RECAL_ST_SHIFT                                      (6U)
#define PRM_IRQSTATUS_DSP2_DPLL_GPU_RECAL_ST_MASK                                       (0x00000040U)
#define PRM_IRQSTATUS_DSP2_DPLL_GPU_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_GPU_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_DDR_RECAL_ST_SHIFT                                      (7U)
#define PRM_IRQSTATUS_DSP2_DPLL_DDR_RECAL_ST_MASK                                       (0x00000080U)
#define PRM_IRQSTATUS_DSP2_DPLL_DDR_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_DDR_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_IO_ST_SHIFT                                                  (9U)
#define PRM_IRQSTATUS_DSP2_IO_ST_MASK                                                   (0x00000200U)
#define PRM_IRQSTATUS_DSP2_IO_ST_IRQ_TRU                                                 (1U)
#define PRM_IRQSTATUS_DSP2_IO_ST_IRQ_FAL                                                 (0U)

#define PRM_IRQSTATUS_DSP2_FORCEWKUP_ST_SHIFT                                           (10U)
#define PRM_IRQSTATUS_DSP2_FORCEWKUP_ST_MASK                                            (0x00000400U)
#define PRM_IRQSTATUS_DSP2_FORCEWKUP_ST_IRQ_TRU                                          (1U)
#define PRM_IRQSTATUS_DSP2_FORCEWKUP_ST_IRQ_FAL                                          (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_DSP_RECAL_ST_SHIFT                                      (11U)
#define PRM_IRQSTATUS_DSP2_DPLL_DSP_RECAL_ST_MASK                                       (0x00000800U)
#define PRM_IRQSTATUS_DSP2_DPLL_DSP_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_DSP_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_DPLL_EVE_RECAL_ST_SHIFT                                      (12U)
#define PRM_IRQSTATUS_DSP2_DPLL_EVE_RECAL_ST_MASK                                       (0x00001000U)
#define PRM_IRQSTATUS_DSP2_DPLL_EVE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_DSP2_DPLL_EVE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_DSP2_ABB_GPU_DONE_ST_SHIFT                                        (28U)
#define PRM_IRQSTATUS_DSP2_ABB_GPU_DONE_ST_MASK                                         (0x10000000U)
#define PRM_IRQSTATUS_DSP2_ABB_GPU_DONE_ST_IRQ_TRU                                       (1U)
#define PRM_IRQSTATUS_DSP2_ABB_GPU_DONE_ST_IRQ_FAL                                       (0U)

#define PRM_IRQSTATUS_DSP2_ABB_DSPEVE_DONE_ST_SHIFT                                     (29U)
#define PRM_IRQSTATUS_DSP2_ABB_DSPEVE_DONE_ST_MASK                                      (0x20000000U)
#define PRM_IRQSTATUS_DSP2_ABB_DSPEVE_DONE_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_DSP2_ABB_DSPEVE_DONE_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_CORE_RECAL_ST_SHIFT                                     (0U)
#define PRM_IRQSTATUS_EVE1_DPLL_CORE_RECAL_ST_MASK                                      (0x00000001U)
#define PRM_IRQSTATUS_EVE1_DPLL_CORE_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_CORE_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_PER_RECAL_ST_SHIFT                                      (3U)
#define PRM_IRQSTATUS_EVE1_DPLL_PER_RECAL_ST_MASK                                       (0x00000008U)
#define PRM_IRQSTATUS_EVE1_DPLL_PER_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_PER_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_ABE_RECAL_ST_SHIFT                                      (4U)
#define PRM_IRQSTATUS_EVE1_DPLL_ABE_RECAL_ST_MASK                                       (0x00000010U)
#define PRM_IRQSTATUS_EVE1_DPLL_ABE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_ABE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_GMAC_RECAL_ST_SHIFT                                     (5U)
#define PRM_IRQSTATUS_EVE1_DPLL_GMAC_RECAL_ST_MASK                                      (0x00000020U)
#define PRM_IRQSTATUS_EVE1_DPLL_GMAC_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_GMAC_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_GPU_RECAL_ST_SHIFT                                      (6U)
#define PRM_IRQSTATUS_EVE1_DPLL_GPU_RECAL_ST_MASK                                       (0x00000040U)
#define PRM_IRQSTATUS_EVE1_DPLL_GPU_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_GPU_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_DDR_RECAL_ST_SHIFT                                      (7U)
#define PRM_IRQSTATUS_EVE1_DPLL_DDR_RECAL_ST_MASK                                       (0x00000080U)
#define PRM_IRQSTATUS_EVE1_DPLL_DDR_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_DDR_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_IO_ST_SHIFT                                                  (9U)
#define PRM_IRQSTATUS_EVE1_IO_ST_MASK                                                   (0x00000200U)
#define PRM_IRQSTATUS_EVE1_IO_ST_IRQ_TRU                                                 (1U)
#define PRM_IRQSTATUS_EVE1_IO_ST_IRQ_FAL                                                 (0U)

#define PRM_IRQSTATUS_EVE1_FORCEWKUP_ST_SHIFT                                           (10U)
#define PRM_IRQSTATUS_EVE1_FORCEWKUP_ST_MASK                                            (0x00000400U)
#define PRM_IRQSTATUS_EVE1_FORCEWKUP_ST_IRQ_TRU                                          (1U)
#define PRM_IRQSTATUS_EVE1_FORCEWKUP_ST_IRQ_FAL                                          (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_DSP_RECAL_ST_SHIFT                                      (11U)
#define PRM_IRQSTATUS_EVE1_DPLL_DSP_RECAL_ST_MASK                                       (0x00000800U)
#define PRM_IRQSTATUS_EVE1_DPLL_DSP_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_DSP_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_DPLL_EVE_RECAL_ST_SHIFT                                      (12U)
#define PRM_IRQSTATUS_EVE1_DPLL_EVE_RECAL_ST_MASK                                       (0x00001000U)
#define PRM_IRQSTATUS_EVE1_DPLL_EVE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_EVE1_DPLL_EVE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_EVE1_ABB_GPU_DONE_ST_SHIFT                                        (28U)
#define PRM_IRQSTATUS_EVE1_ABB_GPU_DONE_ST_MASK                                         (0x10000000U)
#define PRM_IRQSTATUS_EVE1_ABB_GPU_DONE_ST_IRQ_TRU                                       (1U)
#define PRM_IRQSTATUS_EVE1_ABB_GPU_DONE_ST_IRQ_FAL                                       (0U)

#define PRM_IRQSTATUS_EVE1_ABB_DSPEVE_DONE_ST_SHIFT                                     (29U)
#define PRM_IRQSTATUS_EVE1_ABB_DSPEVE_DONE_ST_MASK                                      (0x20000000U)
#define PRM_IRQSTATUS_EVE1_ABB_DSPEVE_DONE_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_EVE1_ABB_DSPEVE_DONE_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_CORE_RECAL_ST_SHIFT                                     (0U)
#define PRM_IRQSTATUS_IPU1_DPLL_CORE_RECAL_ST_MASK                                      (0x00000001U)
#define PRM_IRQSTATUS_IPU1_DPLL_CORE_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_CORE_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_PER_RECAL_ST_SHIFT                                      (3U)
#define PRM_IRQSTATUS_IPU1_DPLL_PER_RECAL_ST_MASK                                       (0x00000008U)
#define PRM_IRQSTATUS_IPU1_DPLL_PER_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_PER_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_ABE_RECAL_ST_SHIFT                                      (4U)
#define PRM_IRQSTATUS_IPU1_DPLL_ABE_RECAL_ST_MASK                                       (0x00000010U)
#define PRM_IRQSTATUS_IPU1_DPLL_ABE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_ABE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_GMAC_RECAL_ST_SHIFT                                     (5U)
#define PRM_IRQSTATUS_IPU1_DPLL_GMAC_RECAL_ST_MASK                                      (0x00000020U)
#define PRM_IRQSTATUS_IPU1_DPLL_GMAC_RECAL_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_GMAC_RECAL_ST_IRQ_FAL                                    (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_GPU_RECAL_ST_SHIFT                                      (6U)
#define PRM_IRQSTATUS_IPU1_DPLL_GPU_RECAL_ST_MASK                                       (0x00000040U)
#define PRM_IRQSTATUS_IPU1_DPLL_GPU_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_GPU_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_DDR_RECAL_ST_SHIFT                                      (7U)
#define PRM_IRQSTATUS_IPU1_DPLL_DDR_RECAL_ST_MASK                                       (0x00000080U)
#define PRM_IRQSTATUS_IPU1_DPLL_DDR_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_DDR_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_TRANSITION_ST_SHIFT                                          (8U)
#define PRM_IRQSTATUS_IPU1_TRANSITION_ST_MASK                                           (0x00000100U)
#define PRM_IRQSTATUS_IPU1_TRANSITION_ST_IRQ_TRU                                         (1U)
#define PRM_IRQSTATUS_IPU1_TRANSITION_ST_IRQ_FAL                                         (0U)

#define PRM_IRQSTATUS_IPU1_IO_ST_SHIFT                                                  (9U)
#define PRM_IRQSTATUS_IPU1_IO_ST_MASK                                                   (0x00000200U)
#define PRM_IRQSTATUS_IPU1_IO_ST_IRQ_TRU                                                 (1U)
#define PRM_IRQSTATUS_IPU1_IO_ST_IRQ_FAL                                                 (0U)

#define PRM_IRQSTATUS_IPU1_FORCEWKUP_ST_SHIFT                                           (10U)
#define PRM_IRQSTATUS_IPU1_FORCEWKUP_ST_MASK                                            (0x00000400U)
#define PRM_IRQSTATUS_IPU1_FORCEWKUP_ST_IRQ_TRU                                          (1U)
#define PRM_IRQSTATUS_IPU1_FORCEWKUP_ST_IRQ_FAL                                          (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_DSP_RECAL_ST_SHIFT                                      (11U)
#define PRM_IRQSTATUS_IPU1_DPLL_DSP_RECAL_ST_MASK                                       (0x00000800U)
#define PRM_IRQSTATUS_IPU1_DPLL_DSP_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_DSP_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_DPLL_EVE_RECAL_ST_SHIFT                                      (12U)
#define PRM_IRQSTATUS_IPU1_DPLL_EVE_RECAL_ST_MASK                                       (0x00001000U)
#define PRM_IRQSTATUS_IPU1_DPLL_EVE_RECAL_ST_IRQ_TRU                                     (1U)
#define PRM_IRQSTATUS_IPU1_DPLL_EVE_RECAL_ST_IRQ_FAL                                     (0U)

#define PRM_IRQSTATUS_IPU1_ABB_GPU_DONE_ST_SHIFT                                        (28U)
#define PRM_IRQSTATUS_IPU1_ABB_GPU_DONE_ST_MASK                                         (0x10000000U)
#define PRM_IRQSTATUS_IPU1_ABB_GPU_DONE_ST_IRQ_TRU                                       (1U)
#define PRM_IRQSTATUS_IPU1_ABB_GPU_DONE_ST_IRQ_FAL                                       (0U)

#define PRM_IRQSTATUS_IPU1_ABB_DSPEVE_DONE_ST_SHIFT                                     (29U)
#define PRM_IRQSTATUS_IPU1_ABB_DSPEVE_DONE_ST_MASK                                      (0x20000000U)
#define PRM_IRQSTATUS_IPU1_ABB_DSPEVE_DONE_ST_IRQ_TRU                                    (1U)
#define PRM_IRQSTATUS_IPU1_ABB_DSPEVE_DONE_ST_IRQ_FAL                                    (0U)

#define PRM_DEBUG_CFG1_SEL1_SHIFT                                                  (0U)
#define PRM_DEBUG_CFG1_SEL1_MASK                                                   (0x000001ffU)

#define PRM_DEBUG_CFG2_SEL2_SHIFT                                                  (0U)
#define PRM_DEBUG_CFG2_SEL2_MASK                                                   (0x000001ffU)

#define PRM_DEBUG_CFG3_SEL3_SHIFT                                                  (0U)
#define PRM_DEBUG_CFG3_SEL3_MASK                                                   (0x000001ffU)

#define PRM_DEBUG_CFG_SEL0_SHIFT                                                   (0U)
#define PRM_DEBUG_CFG_SEL0_MASK                                                    (0x000001ffU)

#define PRM_DEBUG_OUT_OUTPUT_SHIFT                                                 (0U)
#define PRM_DEBUG_OUT_OUTPUT_MASK                                                  (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_OCP_SOCKET_PRM_H_ */

