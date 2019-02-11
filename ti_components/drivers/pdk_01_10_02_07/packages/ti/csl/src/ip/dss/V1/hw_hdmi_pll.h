/*
* hw_hdmi_pll.h
*
* Register-level header file for HDMI_PLL
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
#ifndef HW_HDMI_PLL_H_
#define HW_HDMI_PLL_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define HDMI_PLL_CONTROL                                        (0x0U)
#define HDMI_PLL_STATUS                                         (0x4U)
#define HDMI_PLL_GO                                             (0x8U)
#define HDMI_PLL_CONFIGURATION1                                 (0xcU)
#define HDMI_PLL_CONFIGURATION2                                 (0x10U)
#define HDMI_PLL_CONFIGURATION3                                 (0x14U)
#define HDMI_PLL_SSC_CONFIGURATION1                             (0x18U)
#define HDMI_PLL_SSC_CONFIGURATION2                             (0x1cU)
#define HDMI_PLL_CONFIGURATION4                                 (0x20U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define HDMI_PLL_CONTROL_HSDIV_SYSRESETN_SHIFT                  (4U)
#define HDMI_PLL_CONTROL_HSDIV_SYSRESETN_MASK                   (0x00000010U)
#define HDMI_PLL_CONTROL_HSDIV_SYSRESETN_SYSRST_ACT              (0U)
#define HDMI_PLL_CONTROL_HSDIV_SYSRESETN_OP                      (1U)

#define HDMI_PLL_CONTROL_AUTOMODE_SHIFT                         (0U)
#define HDMI_PLL_CONTROL_AUTOMODE_MASK                          (0x00000001U)
#define HDMI_PLL_CONTROL_AUTOMODE_MAN_MODE                       (0U)
#define HDMI_PLL_CONTROL_AUTOMODE_AUTO_MODE                      (1U)

#define HDMI_PLL_CONTROL_SYSRESETN_SHIFT                        (3U)
#define HDMI_PLL_CONTROL_SYSRESETN_MASK                         (0x00000008U)
#define HDMI_PLL_CONTROL_SYSRESETN_SYSRST_ACT                    (0U)
#define HDMI_PLL_CONTROL_SYSRESETN_OP                            (1U)

#define HDMI_PLL_CONTROL_GATEMODE_SHIFT                         (1U)
#define HDMI_PLL_CONTROL_GATEMODE_MASK                          (0x00000002U)
#define HDMI_PLL_CONTROL_GATEMODE_DSIPHY_CLK_ACT                 (0U)
#define HDMI_PLL_CONTROL_GATEMODE_DSIPHY_CLK_GATE                (1U)

#define HDMI_PLL_CONTROL_HALTMODE_SHIFT                         (2U)
#define HDMI_PLL_CONTROL_HALTMODE_MASK                          (0x00000004U)
#define HDMI_PLL_CONTROL_HALTMODE_RUN                            (0U)
#define HDMI_PLL_CONTROL_HALTMODE_HALT                           (1U)

#define HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_SHIFT                (0U)
#define HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_MASK                 (0x00000001U)
#define HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_NOTRD                 (0U)
#define HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_RDONE                 (1U)

#define HDMI_PLL_STATUS_RECAL_SHIFT                             (2U)
#define HDMI_PLL_STATUS_RECAL_MASK                              (0x00000004U)
#define HDMI_PLL_STATUS_RECAL_RECAL_REQUIRED                     (1U)
#define HDMI_PLL_STATUS_RECAL_RECAL_NOT_REQUIRED                 (0U)

#define HDMI_PLL_STATUS_LOCK_SHIFT                              (1U)
#define HDMI_PLL_STATUS_LOCK_MASK                               (0x00000002U)
#define HDMI_PLL_STATUS_LOCK_DSI_NOLOCK                          (0U)
#define HDMI_PLL_STATUS_LOCK_DSI_LOCK                            (1U)

#define HDMI_PLL_STATUS_M5_CLOCK_ACK_SHIFT                      (8U)
#define HDMI_PLL_STATUS_M5_CLOCK_ACK_MASK                       (0x00000100U)
#define HDMI_PLL_STATUS_M5_CLOCK_ACK_CLK_ACT                     (1U)
#define HDMI_PLL_STATUS_M5_CLOCK_ACK_CLK_INACT                   (0U)

#define HDMI_PLL_STATUS_M4_CLOCK_ACK_SHIFT                      (7U)
#define HDMI_PLL_STATUS_M4_CLOCK_ACK_MASK                       (0x00000080U)
#define HDMI_PLL_STATUS_M4_CLOCK_ACK_CLK_INACT                   (0U)
#define HDMI_PLL_STATUS_M4_CLOCK_ACK_CLK_ACT                     (1U)

#define HDMI_PLL_STATUS_HIGHJITTER_SHIFT                        (5U)
#define HDMI_PLL_STATUS_HIGHJITTER_MASK                         (0x00000020U)
#define HDMI_PLL_STATUS_HIGHJITTER_NORMAL_JITTER                 (0U)
#define HDMI_PLL_STATUS_HIGHJITTER_HIGH_JIITTER                  (1U)

#define HDMI_PLL_STATUS_LOSSREF_SHIFT                           (3U)
#define HDMI_PLL_STATUS_LOSSREF_MASK                            (0x00000008U)
#define HDMI_PLL_STATUS_LOSSREF_REF_INP_ACT                      (0U)
#define HDMI_PLL_STATUS_LOSSREF_REF_INP_INACT                    (1U)

#define HDMI_PLL_STATUS_BYPASS_SHIFT                            (6U)
#define HDMI_PLL_STATUS_BYPASS_MASK                             (0x00000040U)
#define HDMI_PLL_STATUS_BYPASS_BYPASS_IN                         (0U)
#define HDMI_PLL_STATUS_BYPASS_BYPASS_ACT                        (1U)

#define HDMI_PLL_STATUS_BYPASSACKZ_MERGED_SHIFT                 (9U)
#define HDMI_PLL_STATUS_BYPASSACKZ_MERGED_MASK                  (0x00000200U)
#define HDMI_PLL_STATUS_BYPASSACKZ_MERGED_BYPASS_ACK             (0U)
#define HDMI_PLL_STATUS_BYPASSACKZ_MERGED_BYPASS_NAK             (1U)

#define HDMI_PLL_STATUS_SSC_EN_ACK_SHIFT                        (12U)
#define HDMI_PLL_STATUS_SSC_EN_ACK_MASK                         (0x00001000U)
#define HDMI_PLL_STATUS_SSC_EN_ACK_INACT                         (0U)
#define HDMI_PLL_STATUS_SSC_EN_ACK_ACT                           (1U)

#define HDMI_PLL_STATUS_M6_CLOCK_ACK_SHIFT                      (10U)
#define HDMI_PLL_STATUS_M6_CLOCK_ACK_MASK                       (0x00000400U)
#define HDMI_PLL_STATUS_M6_CLOCK_ACK_CLK_ACT                     (1U)
#define HDMI_PLL_STATUS_M6_CLOCK_ACK_CLK_INACT                   (0U)

#define HDMI_PLL_STATUS_M7_CLOCK_ACK_SHIFT                      (11U)
#define HDMI_PLL_STATUS_M7_CLOCK_ACK_MASK                       (0x00000800U)
#define HDMI_PLL_STATUS_M7_CLOCK_ACK_CLK_ACT                     (1U)
#define HDMI_PLL_STATUS_M7_CLOCK_ACK_CLK_INACT                   (0U)

#define HDMI_PLL_STATUS_BYPASSACKZ_SHIFT                        (13U)
#define HDMI_PLL_STATUS_BYPASSACKZ_MASK                         (0x00006000U)
#define HDMI_PLL_STATUS_BYPASSACKZ_BYPASS_ACK                    (0U)
#define HDMI_PLL_STATUS_BYPASSACKZ_BYPASS_NAK                    (1U)

#define HDMI_PLL_STATUS_LDOPWDN_SHIFT                           (15U)
#define HDMI_PLL_STATUS_LDOPWDN_MASK                            (0x00008000U)
#define HDMI_PLL_STATUS_LDOPWDN_LDOPWDN_LOW                      (0U)
#define HDMI_PLL_STATUS_LDOPWDN_LDOPWDN_HIGH                     (1U)

#define HDMI_PLL_STATUS_TICOPWDN_SHIFT                          (16U)
#define HDMI_PLL_STATUS_TICOPWDN_MASK                           (0x00010000U)
#define HDMI_PLL_STATUS_TICOPWDN_TICOPWDN_LOW                    (0U)
#define HDMI_PLL_STATUS_TICOPWDN_TICOPWDN_HIGH                   (1U)

#define HDMI_PLL_GO_SHIFT                                       (0U)
#define HDMI_PLL_GO_MASK                                        (0x00000001U)
#define HDMI_PLL_GO_DONE                                         (0U)
#define HDMI_PLL_GO_GO                                           (1U)

#define HDMI_PLL_GO_HSDIVLOAD_SHIFT                             (1U)
#define HDMI_PLL_GO_HSDIVLOAD_MASK                              (0x00000002U)

#define HDMI_PLL_CONFIGURATION1_REGM_SHIFT                      (9U)
#define HDMI_PLL_CONFIGURATION1_REGM_MASK                       (0x001ffe00U)

#define HDMI_PLL_CONFIGURATION1_REGN_SHIFT                      (1U)
#define HDMI_PLL_CONFIGURATION1_REGN_MASK                       (0x000001feU)

#define HDMI_PLL_CONFIGURATION1_M5_CLOCK_DIV_SHIFT              (26U)
#define HDMI_PLL_CONFIGURATION1_M5_CLOCK_DIV_MASK               (0x7c000000U)

#define HDMI_PLL_CONFIGURATION1_M4_CLOCK_DIV_SHIFT              (21U)
#define HDMI_PLL_CONFIGURATION1_M4_CLOCK_DIV_MASK               (0x03e00000U)

#define HDMI_PLL_CONFIGURATION2_LOCKSEL_SHIFT                   (9U)
#define HDMI_PLL_CONFIGURATION2_LOCKSEL_MASK                    (0x00000600U)
#define HDMI_PLL_CONFIGURATION2_LOCKSEL_PHASELOCK                (0U)
#define HDMI_PLL_CONFIGURATION2_LOCKSEL_FREQLOCK                 (1U)
#define HDMI_PLL_CONFIGURATION2_LOCKSEL_SPARE                    (2U)

#define HDMI_PLL_CONFIGURATION2_PLLLPMODE_SHIFT                 (5U)
#define HDMI_PLL_CONFIGURATION2_PLLLPMODE_MASK                  (0x00000020U)
#define HDMI_PLL_CONFIGURATION2_PLLLPMODE_FULL_PERF              (0U)
#define HDMI_PLL_CONFIGURATION2_PLLLPMODE_REDUCE_PERF            (1U)

#define HDMI_PLL_CONFIGURATION2_HIGHFREQ_SHIFT                  (12U)
#define HDMI_PLL_CONFIGURATION2_HIGHFREQ_MASK                   (0x00001000U)
#define HDMI_PLL_CONFIGURATION2_HIGHFREQ_DIV_BY_1                (0U)
#define HDMI_PLL_CONFIGURATION2_HIGHFREQ_DIV_BY_2                (1U)

#define HDMI_PLL_CONFIGURATION2_IDLE_SHIFT                      (0U)
#define HDMI_PLL_CONFIGURATION2_IDLE_MASK                       (0x00000001U)
#define HDMI_PLL_CONFIGURATION2_IDLE_NOTSEL                      (0U)
#define HDMI_PLL_CONFIGURATION2_IDLE_SEL                         (1U)

#define HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_SHIFT               (6U)
#define HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_MASK                (0x00000040U)
#define HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_NOTSEL               (0U)
#define HDMI_PLL_CONFIGURATION2_LOWCURRSTBY_SEL                  (1U)

#define HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_SHIFT              (8U)
#define HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_MASK               (0x00000100U)
#define HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_DRIFT_GUARD_DIS     (0U)
#define HDMI_PLL_CONFIGURATION2_DRIFTGUARDEN_DRIFT_GUARD_EN      (1U)

#define HDMI_PLL_CONFIGURATION2_CLKSEL_SHIFT                    (11U)
#define HDMI_PLL_CONFIGURATION2_CLKSEL_MASK                     (0x00000800U)
#define HDMI_PLL_CONFIGURATION2_CLKSEL_SYSCLK_REF                (0U)
#define HDMI_PLL_CONFIGURATION2_CLKSEL_PCLK_REF                  (1U)

#define HDMI_PLL_CONFIGURATION2_REFEN_SHIFT                     (13U)
#define HDMI_PLL_CONFIGURATION2_REFEN_MASK                      (0x00002000U)
#define HDMI_PLL_CONFIGURATION2_REFEN_REF_DIS                    (0U)
#define HDMI_PLL_CONFIGURATION2_REFEN_REF_EN                     (1U)

#define HDMI_PLL_CONFIGURATION2_M5_CLOCK_EN_SHIFT               (18U)
#define HDMI_PLL_CONFIGURATION2_M5_CLOCK_EN_MASK                (0x00040000U)
#define HDMI_PLL_CONFIGURATION2_M5_CLOCK_EN_DSIPROTO_CLK_DIS     (0U)
#define HDMI_PLL_CONFIGURATION2_M5_CLOCK_EN_DSIPROTO_CLK_EN      (1U)

#define HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_SHIFT               (16U)
#define HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_MASK                (0x00010000U)
#define HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_SS_CLK_DIS           (0U)
#define HDMI_PLL_CONFIGURATION2_M4_CLOCK_EN_SS_CLK_EN            (1U)

#define HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_SHIFT               (14U)
#define HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_MASK                (0x00004000U)
#define HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_CLK_DIS              (0U)
#define HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_CLK_EN               (1U)

#define HDMI_PLL_CONFIGURATION2_BYPASSEN_SHIFT                  (15U)
#define HDMI_PLL_CONFIGURATION2_BYPASSEN_MASK                   (0x00008000U)
#define HDMI_PLL_CONFIGURATION2_BYPASSEN_CLK                     (0U)
#define HDMI_PLL_CONFIGURATION2_BYPASSEN_CLK_BYPASS              (1U)

#define HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_SHIFT               (20U)
#define HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_MASK                (0x00100000U)
#define HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_HSDIV_NORMAL         (0U)
#define HDMI_PLL_CONFIGURATION2_HSDIVBYPASS_HSDIV_FORCE_BYP      (1U)

#define HDMI_PLL_CONFIGURATION2_REFSEL_SHIFT                    (21U)
#define HDMI_PLL_CONFIGURATION2_REFSEL_MASK                     (0x00600000U)
#define HDMI_PLL_CONFIGURATION2_REFSEL_REF_PCLK                  (0U)
#define HDMI_PLL_CONFIGURATION2_REFSEL_REF_1                     (1U)
#define HDMI_PLL_CONFIGURATION2_REFSEL_REF_2                     (2U)
#define HDMI_PLL_CONFIGURATION2_REFSEL_REF_SYSCLK                (3U)

#define HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_SHIFT               (23U)
#define HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_MASK                (0x00800000U)
#define HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_CLK_DIS              (0U)
#define HDMI_PLL_CONFIGURATION2_M6_CLOCK_EN_CLK_EN               (1U)

#define HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_SHIFT               (25U)
#define HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_MASK                (0x02000000U)
#define HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_CLK_DIS              (0U)
#define HDMI_PLL_CONFIGURATION2_M7_CLOCK_EN_CLK_EN               (1U)

#define HDMI_PLL_CONFIGURATION2_SELFREQDCO_SHIFT                (1U)
#define HDMI_PLL_CONFIGURATION2_SELFREQDCO_MASK                 (0x0000000eU)

#define HDMI_PLL_CONFIGURATION3_M6_CLOCK_DIV_SHIFT              (0U)
#define HDMI_PLL_CONFIGURATION3_M6_CLOCK_DIV_MASK               (0x0000001fU)

#define HDMI_PLL_CONFIGURATION3_M7_CLOCK_DIV_SHIFT              (5U)
#define HDMI_PLL_CONFIGURATION3_M7_CLOCK_DIV_MASK               (0x000003e0U)

#define HDMI_PLL_CONFIGURATION3_SD_SHIFT                        (10U)
#define HDMI_PLL_CONFIGURATION3_SD_MASK                         (0x0003fc00U)

#define HDMI_PLL_SSC_CONFIGURATION1_EN_SHIFT                    (0U)
#define HDMI_PLL_SSC_CONFIGURATION1_EN_MASK                     (0x00000001U)
#define HDMI_PLL_SSC_CONFIGURATION1_EN_OFF                       (0U)
#define HDMI_PLL_SSC_CONFIGURATION1_EN_ON                        (1U)

#define HDMI_PLL_SSC_CONFIGURATION1_MOD_TYPE_SHIFT              (1U)
#define HDMI_PLL_SSC_CONFIGURATION1_MOD_TYPE_MASK               (0x00000002U)
#define HDMI_PLL_SSC_CONFIGURATION1_MOD_TYPE_MOD                 (0U)
#define HDMI_PLL_SSC_CONFIGURATION1_MOD_TYPE_DITHER_MOD          (1U)

#define HDMI_PLL_SSC_CONFIGURATION1_DOWNSPREAD_SHIFT            (2U)
#define HDMI_PLL_SSC_CONFIGURATION1_DOWNSPREAD_MASK             (0x00000004U)
#define HDMI_PLL_SSC_CONFIGURATION1_DOWNSPREAD_NOTFORCED         (0U)
#define HDMI_PLL_SSC_CONFIGURATION1_DOWNSPREAD_FORCEDOWN         (1U)

#define HDMI_PLL_SSC_CONFIGURATION2_DELTAM_SHIFT                (0U)
#define HDMI_PLL_SSC_CONFIGURATION2_DELTAM_MASK                 (0x000fffffU)

#define HDMI_PLL_SSC_CONFIGURATION2_MODFREQDIVIDER_SHIFT        (20U)
#define HDMI_PLL_SSC_CONFIGURATION2_MODFREQDIVIDER_MASK         (0x3ff00000U)

#define HDMI_PLL_SSC_CONFIGURATION2_DELTAM2_SHIFT               (30U)
#define HDMI_PLL_SSC_CONFIGURATION2_DELTAM2_MASK                (0x40000000U)

#define HDMI_PLL_CONFIGURATION4_REGM_F_SHIFT                    (0U)
#define HDMI_PLL_CONFIGURATION4_REGM_F_MASK                     (0x0003ffffU)

#define HDMI_PLL_CONFIGURATION4_REGM2_SHIFT                     (18U)
#define HDMI_PLL_CONFIGURATION4_REGM2_MASK                      (0x01fc0000U)

#ifdef __cplusplus
}
#endif

#endif /* HW_HDMI_PLL_H_ */

