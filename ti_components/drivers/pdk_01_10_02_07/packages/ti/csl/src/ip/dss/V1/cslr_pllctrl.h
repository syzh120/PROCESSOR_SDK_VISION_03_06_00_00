/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_PLLCTRL_H_V1
#define CSLR_PLLCTRL_H_V1

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 CTRL;
    volatile Uint32 STS;
    volatile Uint32 GO;
    volatile Uint32 CONFIG1;
    volatile Uint32 CONFIG2;
    volatile Uint32 CONFIG3;
    volatile Uint32 SSC_CONFIG1;
    volatile Uint32 SSC_CONFIG2;
    volatile Uint32 CONFIG4;
} CSL_PllCtrlRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This register controls the PLL reset/power and modes */
#define CSL_PLLCTRL_CTRL                                        (0x0U)

/* This register contains the status information */
#define CSL_PLLCTRL_STS                                         (0x4U)

/* This register contains the GO bit */
#define CSL_PLLCTRL_GO                                          (0x8U)

/* This register contains the latched PLL and HSDIVDER configuration bits */
#define CSL_PLLCTRL_CONFIG1                                     (0xCU)

/* This register contains the unlatched PLL and HSDIVDER configuration bits 
 * These bits are "shadowed" when automatic mode is selected */
#define CSL_PLLCTRL_CONFIG2                                     (0x10U)

/* HSDIVIDER configuration bits for the M5 and M6 dividers */
#define CSL_PLLCTRL_CONFIG3                                     (0x14U)

/* Configuration for PLL Spread Spectrum Clocking modulation */
#define CSL_PLLCTRL_SSC_CONFIG1                                 (0x18U)

/* SSC_CONFIG2 */
#define CSL_PLLCTRL_SSC_CONFIG2                                 (0x1CU)

/* Allows setting the fractional M divider and M2 divider for PLL. */
#define CSL_PLLCTRL_CONFIG4                                     (0x20U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CTRL */

#define CSL_PLLCTRL_CTRL_HSDIV_SYSRESETN_MASK                   (0x00000010U)
#define CSL_PLLCTRL_CTRL_HSDIV_SYSRESETN_SHIFT                  (4U)
#define CSL_PLLCTRL_CTRL_HSDIV_SYSRESETN_RESETVAL               (0x00000001U)
#define CSL_PLLCTRL_CTRL_HSDIV_SYSRESETN_HSDIV_OP               (0x00000001U)
#define CSL_PLLCTRL_CTRL_HSDIV_SYSRESETN_HSDIV_SYSRST_ACT       (0x00000000U)

#define CSL_PLLCTRL_CTRL_PLL_AUTOMODE_MASK                      (0x00000001U)
#define CSL_PLLCTRL_CTRL_PLL_AUTOMODE_SHIFT                     (0U)
#define CSL_PLLCTRL_CTRL_PLL_AUTOMODE_RESETVAL                  (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_AUTOMODE_MAN_MODE                  (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_AUTOMODE_AUTO_MODE                 (0x00000001U)

#define CSL_PLLCTRL_CTRL_PLL_SYSRESETN_MASK                     (0x00000008U)
#define CSL_PLLCTRL_CTRL_PLL_SYSRESETN_SHIFT                    (3U)
#define CSL_PLLCTRL_CTRL_PLL_SYSRESETN_RESETVAL                 (0x00000001U)
#define CSL_PLLCTRL_CTRL_PLL_SYSRESETN_PLL_SYSRST_ACT           (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_SYSRESETN_PLL_OP                   (0x00000001U)

#define CSL_PLLCTRL_CTRL_PLL_GATEMODE_MASK                      (0x00000002U)
#define CSL_PLLCTRL_CTRL_PLL_GATEMODE_SHIFT                     (1U)
#define CSL_PLLCTRL_CTRL_PLL_GATEMODE_RESETVAL                  (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_GATEMODE_DSIPHY_CLK_ACT            (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_GATEMODE_DSIPHY_CLK_GATE           (0x00000001U)

#define CSL_PLLCTRL_CTRL_PLL_HALTMODE_MASK                      (0x00000004U)
#define CSL_PLLCTRL_CTRL_PLL_HALTMODE_SHIFT                     (2U)
#define CSL_PLLCTRL_CTRL_PLL_HALTMODE_RESETVAL                  (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_HALTMODE_PLL_RUN                   (0x00000000U)
#define CSL_PLLCTRL_CTRL_PLL_HALTMODE_PLL_HALT                  (0x00000001U)

#define CSL_PLLCTRL_CTRL_RESETVAL                               (0x00000018U)

/* STS */

#define CSL_PLLCTRL_STS_PLLCTRL_RESET_DONE_MASK                 (0x00000001U)
#define CSL_PLLCTRL_STS_PLLCTRL_RESET_DONE_SHIFT                (0U)
#define CSL_PLLCTRL_STS_PLLCTRL_RESET_DONE_RESETVAL             (0x00000000U)
#define CSL_PLLCTRL_STS_PLLCTRL_RESET_DONE_NOTRD                (0x00000000U)
#define CSL_PLLCTRL_STS_PLLCTRL_RESET_DONE_RDONE                (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_RECAL_MASK                          (0x00000004U)
#define CSL_PLLCTRL_STS_PLL_RECAL_SHIFT                         (2U)
#define CSL_PLLCTRL_STS_PLL_RECAL_RESETVAL                      (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_RECAL_RECAL_REQUIRED                (0x00000001U)
#define CSL_PLLCTRL_STS_PLL_RECAL_RECAL_NOT_REQUIRED            (0x00000000U)

#define CSL_PLLCTRL_STS_PLL_LOCK_MASK                           (0x00000002U)
#define CSL_PLLCTRL_STS_PLL_LOCK_SHIFT                          (1U)
#define CSL_PLLCTRL_STS_PLL_LOCK_RESETVAL                       (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LOCK_DSI_PLL_NOLOCK                 (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LOCK_DSI_PLL_LOCK                   (0x00000001U)

#define CSL_PLLCTRL_STS_M5_CLOCK_ACK_MASK                       (0x00000100U)
#define CSL_PLLCTRL_STS_M5_CLOCK_ACK_SHIFT                      (8U)
#define CSL_PLLCTRL_STS_M5_CLOCK_ACK_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_STS_M5_CLOCK_ACK_M5_CLK_ACT                 (0x00000001U)
#define CSL_PLLCTRL_STS_M5_CLOCK_ACK_M5_CLK_INACT               (0x00000000U)

#define CSL_PLLCTRL_STS_M4_CLOCK_ACK_MASK                       (0x00000080U)
#define CSL_PLLCTRL_STS_M4_CLOCK_ACK_SHIFT                      (7U)
#define CSL_PLLCTRL_STS_M4_CLOCK_ACK_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_STS_M4_CLOCK_ACK_M4_CLK_INACT               (0x00000000U)
#define CSL_PLLCTRL_STS_M4_CLOCK_ACK_M4_CLK_ACT                 (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_HIGHJITTER_MASK                     (0x00000020U)
#define CSL_PLLCTRL_STS_PLL_HIGHJITTER_SHIFT                    (5U)
#define CSL_PLLCTRL_STS_PLL_HIGHJITTER_RESETVAL                 (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_HIGHJITTER_NORMAL_JITTER            (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_HIGHJITTER_HIGH_JIITTER             (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_LOSSREF_MASK                        (0x00000008U)
#define CSL_PLLCTRL_STS_PLL_LOSSREF_SHIFT                       (3U)
#define CSL_PLLCTRL_STS_PLL_LOSSREF_RESETVAL                    (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LOSSREF_REF_INP_ACT                 (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LOSSREF_REF_INP_INACT               (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_BYPASS_MASK                         (0x00000040U)
#define CSL_PLLCTRL_STS_PLL_BYPASS_SHIFT                        (6U)
#define CSL_PLLCTRL_STS_PLL_BYPASS_RESETVAL                     (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_BYPASS_BYPASS_IN                    (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_BYPASS_BYPASS_ACT                   (0x00000001U)

#define CSL_PLLCTRL_STS_BYPASSACKZ_MERGED_MASK                  (0x00000200U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_MERGED_SHIFT                 (9U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_MERGED_RESETVAL              (0x00000000U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_MERGED_BYPASS_ACK            (0x00000000U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_MERGED_BYPASS_NAK            (0x00000001U)

#define CSL_PLLCTRL_STS_SSC_EN_ACK_MASK                         (0x00001000U)
#define CSL_PLLCTRL_STS_SSC_EN_ACK_SHIFT                        (12U)
#define CSL_PLLCTRL_STS_SSC_EN_ACK_RESETVAL                     (0x00000000U)
#define CSL_PLLCTRL_STS_SSC_EN_ACK_SSC_INACT                    (0x00000000U)
#define CSL_PLLCTRL_STS_SSC_EN_ACK_SSC_ACT                      (0x00000001U)

#define CSL_PLLCTRL_STS_M6_CLOCK_ACK_MASK                       (0x00000400U)
#define CSL_PLLCTRL_STS_M6_CLOCK_ACK_SHIFT                      (10U)
#define CSL_PLLCTRL_STS_M6_CLOCK_ACK_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_STS_M6_CLOCK_ACK_M6_CLK_ACT                 (0x00000001U)
#define CSL_PLLCTRL_STS_M6_CLOCK_ACK_M6_CLK_INACT               (0x00000000U)

#define CSL_PLLCTRL_STS_M7_CLOCK_ACK_MASK                       (0x00000800U)
#define CSL_PLLCTRL_STS_M7_CLOCK_ACK_SHIFT                      (11U)
#define CSL_PLLCTRL_STS_M7_CLOCK_ACK_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_STS_M7_CLOCK_ACK_M7_CLK_ACT                 (0x00000001U)
#define CSL_PLLCTRL_STS_M7_CLOCK_ACK_M7_CLK_INACT               (0x00000000U)

#define CSL_PLLCTRL_STS_BYPASSACKZ_MASK                         (0x00006000U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_SHIFT                        (13U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_RESETVAL                     (0x00000000U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_BYPASS_ACK                   (0x00000000U)
#define CSL_PLLCTRL_STS_BYPASSACKZ_BYPASS_NAK                   (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_LDOPWDN_MASK                        (0x00008000U)
#define CSL_PLLCTRL_STS_PLL_LDOPWDN_SHIFT                       (15U)
#define CSL_PLLCTRL_STS_PLL_LDOPWDN_RESETVAL                    (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LDOPWDN_LDOPWDN_LOW                 (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_LDOPWDN_LDOPWDN_HIGH                (0x00000001U)

#define CSL_PLLCTRL_STS_PLL_TICOPWDN_MASK                       (0x00010000U)
#define CSL_PLLCTRL_STS_PLL_TICOPWDN_SHIFT                      (16U)
#define CSL_PLLCTRL_STS_PLL_TICOPWDN_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_TICOPWDN_TICOPWDN_LOW               (0x00000000U)
#define CSL_PLLCTRL_STS_PLL_TICOPWDN_TICOPWDN_HIGH              (0x00000001U)

#define CSL_PLLCTRL_STS_RESETVAL                                (0x00000000U)

/* GO */

#define CSL_PLLCTRL_GO_PLL_GO_MASK                              (0x00000001U)
#define CSL_PLLCTRL_GO_PLL_GO_SHIFT                             (0U)
#define CSL_PLLCTRL_GO_PLL_GO_RESETVAL                          (0x00000000U)
#define CSL_PLLCTRL_GO_PLL_GO_DONE                              (0x00000000U)
#define CSL_PLLCTRL_GO_PLL_GO_GO                                (0x00000001U)

#define CSL_PLLCTRL_GO_HSDIVLOAD_MASK                           (0x00000002U)
#define CSL_PLLCTRL_GO_HSDIVLOAD_SHIFT                          (1U)
#define CSL_PLLCTRL_GO_HSDIVLOAD_RESETVAL                       (0x00000000U)
#define CSL_PLLCTRL_GO_HSDIVLOAD_MAX                            (0x00000001U)

#define CSL_PLLCTRL_GO_RESETVAL                                 (0x00000000U)

/* CONFIG1 */

#define CSL_PLLCTRL_CONFIG1_PLL_REGM_MASK                       (0x000FFE00U)
#define CSL_PLLCTRL_CONFIG1_PLL_REGM_SHIFT                      (9U)
#define CSL_PLLCTRL_CONFIG1_PLL_REGM_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_CONFIG1_PLL_REGM_MAX                        (0x000007ffU)

#define CSL_PLLCTRL_CONFIG1_PLL_REGN_MASK                       (0x000001FEU)
#define CSL_PLLCTRL_CONFIG1_PLL_REGN_SHIFT                      (1U)
#define CSL_PLLCTRL_CONFIG1_PLL_REGN_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_CONFIG1_PLL_REGN_MAX                        (0x000000ffU)

#define CSL_PLLCTRL_CONFIG1_M5_CLOCK_DIV_MASK                   (0x7C000000U)
#define CSL_PLLCTRL_CONFIG1_M5_CLOCK_DIV_SHIFT                  (26U)
#define CSL_PLLCTRL_CONFIG1_M5_CLOCK_DIV_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_CONFIG1_M5_CLOCK_DIV_MAX                    (0x0000001fU)

#define CSL_PLLCTRL_CONFIG1_M4_CLOCK_DIV_MASK                   (0x03E00000U)
#define CSL_PLLCTRL_CONFIG1_M4_CLOCK_DIV_SHIFT                  (21U)
#define CSL_PLLCTRL_CONFIG1_M4_CLOCK_DIV_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_CONFIG1_M4_CLOCK_DIV_MAX                    (0x0000001fU)

#define CSL_PLLCTRL_CONFIG1_RESETVAL                            (0x00000000U)

/* CONFIG2 */

#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_MASK                    (0x00000600U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_SHIFT                   (9U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_PHASELOCK               (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_FREQLOCK                (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOCKSEL_SPARE                   (0x00000002U)

#define CSL_PLLCTRL_CONFIG2_PLL_PLLLPMODE_MASK                  (0x00000020U)
#define CSL_PLLCTRL_CONFIG2_PLL_PLLLPMODE_SHIFT                 (5U)
#define CSL_PLLCTRL_CONFIG2_PLL_PLLLPMODE_RESETVAL              (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_PLLLPMODE_FULL_PERF             (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_PLLLPMODE_REDUCE_PERF           (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PLL_HIGHFREQ_MASK                   (0x00001000U)
#define CSL_PLLCTRL_CONFIG2_PLL_HIGHFREQ_SHIFT                  (12U)
#define CSL_PLLCTRL_CONFIG2_PLL_HIGHFREQ_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_HIGHFREQ_DIV_BY_1               (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_HIGHFREQ_DIV_BY_2               (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PLL_IDLE_MASK                       (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_PLL_IDLE_SHIFT                      (0U)
#define CSL_PLLCTRL_CONFIG2_PLL_IDLE_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_IDLE_IDLE_NOTSEL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_IDLE_IDLE_SEL                   (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PLL_LOWCURRSTBY_MASK                (0x00000040U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOWCURRSTBY_SHIFT               (6U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOWCURRSTBY_RESETVAL            (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOWCURRSTBY_LOWCURRSTBY_SEL     (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_PLL_LOWCURRSTBY_LOWCURRSTBY_NOTSEL  (0x00000000U)

#define CSL_PLLCTRL_CONFIG2_PLL_DRIFTGUARDEN_MASK               (0x00000100U)
#define CSL_PLLCTRL_CONFIG2_PLL_DRIFTGUARDEN_SHIFT              (8U)
#define CSL_PLLCTRL_CONFIG2_PLL_DRIFTGUARDEN_RESETVAL           (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_DRIFTGUARDEN_DRIFT_GUARD_DIS    (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_DRIFTGUARDEN_DRIFT_GUARD_EN     (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PLL_CLKSEL_MASK                     (0x00000800U)
#define CSL_PLLCTRL_CONFIG2_PLL_CLKSEL_SHIFT                    (11U)
#define CSL_PLLCTRL_CONFIG2_PLL_CLKSEL_RESETVAL                 (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_CLKSEL_SYSCLK_REF               (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_CLKSEL_PCLK_REF                 (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PLL_REFEN_MASK                      (0x00002000U)
#define CSL_PLLCTRL_CONFIG2_PLL_REFEN_SHIFT                     (13U)
#define CSL_PLLCTRL_CONFIG2_PLL_REFEN_RESETVAL                  (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_PLL_REFEN_REF_DIS                   (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PLL_REFEN_REF_EN                    (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_M5_CLOCK_EN_MASK                    (0x00040000U)
#define CSL_PLLCTRL_CONFIG2_M5_CLOCK_EN_SHIFT                   (18U)
#define CSL_PLLCTRL_CONFIG2_M5_CLOCK_EN_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_M5_CLOCK_EN_DSIPROTO_CLK_EN         (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_M5_CLOCK_EN_DSIPROTO_CLK_DIS        (0x00000000U)

#define CSL_PLLCTRL_CONFIG2_M4_CLOCK_EN_MASK                    (0x00010000U)
#define CSL_PLLCTRL_CONFIG2_M4_CLOCK_EN_SHIFT                   (16U)
#define CSL_PLLCTRL_CONFIG2_M4_CLOCK_EN_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_M4_CLOCK_EN_SS_CLK_DIS              (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_M4_CLOCK_EN_SS_CLK_EN               (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_PHY_CLKINEN_MASK                    (0x00004000U)
#define CSL_PLLCTRL_CONFIG2_PHY_CLKINEN_SHIFT                   (14U)
#define CSL_PLLCTRL_CONFIG2_PHY_CLKINEN_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PHY_CLKINEN_PHY_CLK_DIS             (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_PHY_CLKINEN_PHY_CLK_EN              (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_BYPASSEN_MASK                       (0x00008000U)
#define CSL_PLLCTRL_CONFIG2_BYPASSEN_SHIFT                      (15U)
#define CSL_PLLCTRL_CONFIG2_BYPASSEN_RESETVAL                   (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_BYPASSEN_CLK_PLL                    (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_BYPASSEN_CLK_BYPASS                 (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_HSDIVBYPASS_MASK                    (0x00100000U)
#define CSL_PLLCTRL_CONFIG2_HSDIVBYPASS_SHIFT                   (20U)
#define CSL_PLLCTRL_CONFIG2_HSDIVBYPASS_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_HSDIVBYPASS_HSDIV_NORMAL            (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_HSDIVBYPASS_HSDIV_FORCE_BYP         (0x00000001U)

#define CSL_PLLCTRL_CONFIG2_REFSEL_MASK                         (0x00600000U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_SHIFT                        (21U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_RESETVAL                     (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_REF_PCLK                     (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_REF_1                        (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_REF_2                        (0x00000002U)
#define CSL_PLLCTRL_CONFIG2_REFSEL_REF_SYSCLK                   (0x00000003U)

#define CSL_PLLCTRL_CONFIG2_M6_CLOCK_EN_MASK                    (0x00800000U)
#define CSL_PLLCTRL_CONFIG2_M6_CLOCK_EN_SHIFT                   (23U)
#define CSL_PLLCTRL_CONFIG2_M6_CLOCK_EN_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_M6_CLOCK_EN_M6_CLK_EN               (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_M6_CLOCK_EN_M6_CLK_DIS              (0x00000000U)

#define CSL_PLLCTRL_CONFIG2_M7_CLOCK_EN_MASK                    (0x02000000U)
#define CSL_PLLCTRL_CONFIG2_M7_CLOCK_EN_SHIFT                   (25U)
#define CSL_PLLCTRL_CONFIG2_M7_CLOCK_EN_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_CONFIG2_M7_CLOCK_EN_M7_CLK_EN               (0x00000001U)
#define CSL_PLLCTRL_CONFIG2_M7_CLOCK_EN_M7_CLK_DIS              (0x00000000U)

#define CSL_PLLCTRL_CONFIG2_PLL_SELFREQDCO_MASK                 (0x0000000EU)
#define CSL_PLLCTRL_CONFIG2_PLL_SELFREQDCO_SHIFT                (1U)
#define CSL_PLLCTRL_CONFIG2_PLL_SELFREQDCO_RESETVAL             (0x00000004U)
#define CSL_PLLCTRL_CONFIG2_PLL_SELFREQDCO_MAX                  (0x00000007U)

#define CSL_PLLCTRL_CONFIG2_RESETVAL                            (0x00002008U)

/* CONFIG3 */

#define CSL_PLLCTRL_CONFIG3_M6_CLOCK_DIV_MASK                   (0x0000001FU)
#define CSL_PLLCTRL_CONFIG3_M6_CLOCK_DIV_SHIFT                  (0U)
#define CSL_PLLCTRL_CONFIG3_M6_CLOCK_DIV_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_CONFIG3_M6_CLOCK_DIV_MAX                    (0x0000001fU)

#define CSL_PLLCTRL_CONFIG3_M7_CLOCK_DIV_MASK                   (0x000003E0U)
#define CSL_PLLCTRL_CONFIG3_M7_CLOCK_DIV_SHIFT                  (5U)
#define CSL_PLLCTRL_CONFIG3_M7_CLOCK_DIV_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_CONFIG3_M7_CLOCK_DIV_MAX                    (0x0000001fU)

#define CSL_PLLCTRL_CONFIG3_PLL_SD_MASK                         (0x0003FC00U)
#define CSL_PLLCTRL_CONFIG3_PLL_SD_SHIFT                        (10U)
#define CSL_PLLCTRL_CONFIG3_PLL_SD_RESETVAL                     (0x00000000U)
#define CSL_PLLCTRL_CONFIG3_PLL_SD_MAX                          (0x000000ffU)

#define CSL_PLLCTRL_CONFIG3_RESETVAL                            (0x00000000U)

/* SSC_CONFIG1 */

#define CSL_PLLCTRL_SSC_CONFIG1_EN_SSC_MASK                     (0x00000001U)
#define CSL_PLLCTRL_SSC_CONFIG1_EN_SSC_SHIFT                    (0U)
#define CSL_PLLCTRL_SSC_CONFIG1_EN_SSC_RESETVAL                 (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG1_EN_SSC_SSC_OFF                  (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG1_EN_SSC_SSC_ON                   (0x00000001U)

#define CSL_PLLCTRL_SSC_CONFIG1_MOD_TYPE_MASK                   (0x00000002U)
#define CSL_PLLCTRL_SSC_CONFIG1_MOD_TYPE_SHIFT                  (1U)
#define CSL_PLLCTRL_SSC_CONFIG1_MOD_TYPE_RESETVAL               (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG1_MOD_TYPE_SSC_MOD                (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG1_MOD_TYPE_DITHER_MOD             (0x00000001U)

#define CSL_PLLCTRL_SSC_CONFIG1_DOWNSPREAD_MASK                 (0x00000004U)
#define CSL_PLLCTRL_SSC_CONFIG1_DOWNSPREAD_SHIFT                (2U)
#define CSL_PLLCTRL_SSC_CONFIG1_DOWNSPREAD_RESETVAL             (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG1_DOWNSPREAD_FORCEDOWN            (0x00000001U)
#define CSL_PLLCTRL_SSC_CONFIG1_DOWNSPREAD_NOTFORCED            (0x00000000U)

#define CSL_PLLCTRL_SSC_CONFIG1_RESETVAL                        (0x00000000U)

/* SSC_CONFIG2 */

#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM_MASK                     (0x000FFFFFU)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM_SHIFT                    (0U)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM_RESETVAL                 (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM_MAX                      (0x000fffffU)

#define CSL_PLLCTRL_SSC_CONFIG2_MODFREQDIVIDER_MASK             (0x3FF00000U)
#define CSL_PLLCTRL_SSC_CONFIG2_MODFREQDIVIDER_SHIFT            (20U)
#define CSL_PLLCTRL_SSC_CONFIG2_MODFREQDIVIDER_RESETVAL         (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG2_MODFREQDIVIDER_MAX              (0x000003ffU)

#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM2_MASK                    (0x40000000U)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM2_SHIFT                   (30U)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM2_RESETVAL                (0x00000000U)
#define CSL_PLLCTRL_SSC_CONFIG2_DELTAM2_MAX                     (0x00000001U)

#define CSL_PLLCTRL_SSC_CONFIG2_RESETVAL                        (0x00000000U)

/* CONFIG4 */

#define CSL_PLLCTRL_CONFIG4_PLL_REGM_F_MASK                     (0x0003FFFFU)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM_F_SHIFT                    (0U)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM_F_RESETVAL                 (0x00000000U)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM_F_MAX                      (0x0003ffffU)

#define CSL_PLLCTRL_CONFIG4_PLL_REGM2_MASK                      (0x01FC0000U)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM2_SHIFT                     (18U)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM2_RESETVAL                  (0x00000001U)
#define CSL_PLLCTRL_CONFIG4_PLL_REGM2_MAX                       (0x0000007fU)

#define CSL_PLLCTRL_CONFIG4_RESETVAL                            (0x00040000U)

#ifdef __cplusplus
}
#endif
#endif
