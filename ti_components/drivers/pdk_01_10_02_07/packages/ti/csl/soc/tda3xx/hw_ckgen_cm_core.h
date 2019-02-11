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
 *  \file   hw_ckgen_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/


#ifndef HW_CKGEN_CM_CORE_H_
#define HW_CKGEN_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CM_CLKMODE_DPLL_PER                                    (0x40U)
#define CM_IDLEST_DPLL_PER                                     (0x44U)
#define CM_AUTOIDLE_DPLL_PER                                   (0x48U)
#define CM_CLKSEL_DPLL_PER                                     (0x4cU)
#define CM_DIV_M2_DPLL_PER                                     (0x50U)
#define CM_DIV_M3_DPLL_PER                                     (0x54U)
#define CM_DIV_H11_DPLL_PER                                    (0x58U)
#define CM_DIV_H12_DPLL_PER                                    (0x5cU)
#define CM_DIV_H13_DPLL_PER                                    (0x60U)
#define CM_DIV_H14_DPLL_PER                                    (0x64U)
#define CM_SSC_DELTAMSTEP_DPLL_PER                             (0x68U)
#define CM_SSC_MODFREQDIV_DPLL_PER                             (0x6cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_CLKMODE_DPLL_PER_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_PER_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_PER_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_PER_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_PER_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_PER_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_PER_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_PER_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_PER_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_PER_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_PER_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_PER_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_PER_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_PER_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_PER_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_PER_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_PER_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_PER_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_PER_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_PER_DPLL_SSC_TYPE_SQUARE                                                             (1U)


#define CM_IDLEST_DPLL_PER_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)


#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_PER_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_PER_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_CLKSEL_DPLL_PER_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_PER_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_PER_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_PER_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_PER_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_PER_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_PER_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_PER_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_PER_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_PER_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_PER_DCC_EN_DISABLED                                                                   (0U)

#define CM_DIV_M2_DPLL_PER_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_PER_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_PER_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_PER_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_PER_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_PER_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_PER_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_PER_CLKX2ST_SHIFT                                                                    (11U)
#define CM_DIV_M2_DPLL_PER_CLKX2ST_MASK                                                                     (0x00000800U)
#define CM_DIV_M2_DPLL_PER_CLKX2ST_CLK_ENABLED                                                               (1U)
#define CM_DIV_M2_DPLL_PER_CLKX2ST_CLK_GATED                                                                 (0U)

#define CM_DIV_M3_DPLL_PER_DIVHS_SHIFT                                             (0U)
#define CM_DIV_M3_DPLL_PER_DIVHS_MASK                                              (0x0000001fU)
#define CM_DIV_M3_DPLL_PER_DIVHS_RESERVED                                           (0U)

#define CM_DIV_M3_DPLL_PER_CLKST_SHIFT                                             (9U)
#define CM_DIV_M3_DPLL_PER_CLKST_MASK                                              (0x00000200U)
#define CM_DIV_M3_DPLL_PER_CLKST_CLK_ENABLED                                        (1U)
#define CM_DIV_M3_DPLL_PER_CLKST_CLK_GATED                                          (0U)

#define CM_DIV_H11_DPLL_PER_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_H11_DPLL_PER_DIVHS_MASK                                                                      (0x0000003fU)
#define CM_DIV_H11_DPLL_PER_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_H11_DPLL_PER_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_H11_DPLL_PER_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_H11_DPLL_PER_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_H11_DPLL_PER_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_H12_DPLL_PER_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_H12_DPLL_PER_DIVHS_MASK                                                                      (0x0000003fU)
#define CM_DIV_H12_DPLL_PER_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_H12_DPLL_PER_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_H12_DPLL_PER_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_H12_DPLL_PER_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_H12_DPLL_PER_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_H13_DPLL_PER_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_H13_DPLL_PER_DIVHS_MASK                                                                      (0x0000003fU)
#define CM_DIV_H13_DPLL_PER_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_H13_DPLL_PER_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_H13_DPLL_PER_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_H13_DPLL_PER_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_H13_DPLL_PER_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_H14_DPLL_PER_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_H14_DPLL_PER_DIVHS_MASK                                                                      (0x0000003fU)
#define CM_DIV_H14_DPLL_PER_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_H14_DPLL_PER_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_H14_DPLL_PER_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_H14_DPLL_PER_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_H14_DPLL_PER_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_H14_DPLL_PER_RESERVED_SHIFT                                                                  (6U)
#define CM_DIV_H14_DPLL_PER_RESERVED_MASK                                                                   (0x000001c0U)

#define CM_DIV_H14_DPLL_PER_RESERVED1_SHIFT                                                                 (10U)
#define CM_DIV_H14_DPLL_PER_RESERVED1_MASK                                                                  (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_PER_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_PER_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_PER_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_PER_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_PER_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_PER_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_PER_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_PER_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CKGEN_CM_CORE_H_ */

