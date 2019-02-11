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
 *  \file   hw_restore_cm_core_aon.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_RESTORE_CM_CORE_AON_H_
#define HW_RESTORE_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CM_CLKSEL_CORE_RESTORE                                 (0x0U)
#define CM_DIV_M2_DPLL_CORE_RESTORE                            (0x4U)
#define CM_DIV_M3_DPLL_CORE_RESTORE                            (0x8U)
#define CM_DIV_H11_DPLL_CORE_RESTORE                           (0xcU)
#define CM_DIV_H12_DPLL_CORE_RESTORE                           (0x10U)
#define CM_DIV_H13_DPLL_CORE_RESTORE                           (0x14U)
#define CM_DIV_H14_DPLL_CORE_RESTORE                           (0x18U)
#define CM_DIV_H21_DPLL_CORE_RESTORE                           (0x1cU)
#define CM_DIV_H22_DPLL_CORE_RESTORE                           (0x20U)
#define CM_DIV_H23_DPLL_CORE_RESTORE                           (0x24U)
#define CM_DIV_H24_DPLL_CORE_RESTORE                           (0x28U)
#define CM_CLKSEL_DPLL_CORE_RESTORE                            (0x2cU)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE                    (0x30U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE                    (0x34U)
#define CM_CLKMODE_DPLL_CORE_RESTORE                           (0x38U)
#define CM_SHADOW_FREQ_CONFIG2_RESTORE                         (0x3cU)
#define CM_SHADOW_FREQ_CONFIG1_RESTORE                         (0x40U)
#define CM_AUTOIDLE_DPLL_CORE_RESTORE                          (0x44U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE                                                            (0x4cU)
#define CM_DYN_DEP_PRESCAL_RESTORE                             (0x50U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_CLKSEL_CORE_RESTORE_RESTORE_SHIFT                                                                (0U)
#define CM_CLKSEL_CORE_RESTORE_RESTORE_MASK                                                                 (0xffffffffU)

#define CM_DIV_M2_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_DIV_M2_DPLL_CORE_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_DIV_M3_DPLL_CORE_RESTORE_SHIFT                                          (0U)
#define CM_DIV_M3_DPLL_CORE_RESTORE_MASK                                           (0xffffffffU)

#define CM_DIV_H11_DPLL_CORE_RESTORE_SHIFT                                         (0U)
#define CM_DIV_H11_DPLL_CORE_RESTORE_MASK                                          (0xffffffffU)

#define CM_DIV_H12_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H12_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H13_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H13_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H14_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H14_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H21_DPLL_CORE_RESTORE_RESTORE_SHIFT                                         (0U)
#define CM_DIV_H21_DPLL_CORE_RESTORE_RESTORE_MASK                                          (0xffffffffU)

#define CM_DIV_H22_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H22_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H23_DPLL_CORE_RESTORE_RESTORE_SHIFT                                         (0U)
#define CM_DIV_H23_DPLL_CORE_RESTORE_RESTORE_MASK                                          (0xffffffffU)

#define CM_DIV_H24_DPLL_CORE_RESTORE_RESTORE_SHIFT                                         (0U)
#define CM_DIV_H24_DPLL_CORE_RESTORE_RESTORE_MASK                                          (0xffffffffU)

#define CM_CLKSEL_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_CLKSEL_DPLL_CORE_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                   (0U)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE_RESTORE_MASK                                                    (0xffffffffU)

#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                   (0U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE_RESTORE_MASK                                                    (0xffffffffU)

#define CM_CLKMODE_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_CLKMODE_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_SHADOW_FREQ_CONFIG2_RESTORE_RESTORE_SHIFT                                                        (0U)
#define CM_SHADOW_FREQ_CONFIG2_RESTORE_RESTORE_MASK                                                         (0xffffffffU)

#define CM_SHADOW_FREQ_CONFIG1_RESTORE_RESTORE_SHIFT                                                        (0U)
#define CM_SHADOW_FREQ_CONFIG1_RESTORE_RESTORE_MASK                                                         (0xffffffffU)

#define CM_AUTOIDLE_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                         (0U)
#define CM_AUTOIDLE_DPLL_CORE_RESTORE_RESTORE_MASK                                                          (0xffffffffU)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE_RESTORE_SHIFT                                              (0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE_RESTORE_MASK                                               (0xffffffffU)

#define CM_DYN_DEP_PRESCAL_RESTORE_RESTORE_SHIFT                                                            (0U)
#define CM_DYN_DEP_PRESCAL_RESTORE_RESTORE_MASK                                                             (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_RESTORE_CM_CORE_AON_H_ */

