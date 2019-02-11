/********************************************************************
 * Copyright (C) 2013-2017 Texas Instruments Incorporated.
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
#ifndef CSLR_EPWM_H_
#define CSLR_EPWM_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for ALL
**************************************************************************/
typedef struct {
    volatile Uint16 TBCTL;
    volatile Uint16 TBSTS;
    volatile Uint16 TBPHSHR;
    volatile Uint16 TBPHS;
    volatile Uint16 TBCNT;
    volatile Uint16 TBPRD;
    volatile Uint8  RSVD0[2];
    volatile Uint16 CMPCTL;
    volatile Uint16 CMPAHR;
    volatile Uint16 CMPA;
    volatile Uint16 CMPB;
    volatile Uint16 AQCTLA;
    volatile Uint16 AQCTLB;
    volatile Uint16 AQSFRC;
    volatile Uint16 AQCSFRC;
    volatile Uint16 DBCTL;
    volatile Uint16 DBRED;
    volatile Uint16 DBFED;
    volatile Uint16 TZSEL;
    volatile Uint8  RSVD1[2];
    volatile Uint16 TZCTL;
    volatile Uint16 TZEINT;
    volatile Uint16 TZFLG;
    volatile Uint16 TZCLR;
    volatile Uint16 TZFRC;
    volatile Uint16 ETSEL;
    volatile Uint16 ETPS;
    volatile Uint16 ETFLG;
    volatile Uint16 ETCLR;
    volatile Uint16 ETFRC;
    volatile Uint16 PCCTL;
    volatile Uint8  RSVD2[PWMSS_EPWM_PCCTL_TO_HRCTL_RSVD];
    volatile Uint16 HRCTL;
    volatile Uint8  RSVD3[70];
} CSL_EpwmRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_EPWM_AQCTLA                                         (0x16U)
#define CSL_EPWM_CMPCTL                                         (0xEU)
#define CSL_EPWM_CMPAHR                                         (0x10U)
#define CSL_EPWM_DBFED                                          (0x22U)
#define CSL_EPWM_TBPHSHR                                        (0x4U)
#define CSL_EPWM_PCCTL                                          (0x3CU)
#define CSL_EPWM_DBRED                                          (0x20U)
#define CSL_EPWM_TBCNT                                          (0x8U)
#define CSL_EPWM_ETSEL                                          (0x32U)
#define CSL_EPWM_HRCTL                                          (0x40U)
#define CSL_EPWM_TZEINT                                         (0x2AU)
#define CSL_EPWM_AQSFRC                                         (0x1AU)
#define CSL_EPWM_ETPS                                           (0x34U)
#define CSL_EPWM_CMPA                                           (0x12U)
#define CSL_EPWM_ETCLR                                          (0x38U)
#define CSL_EPWM_AQCSFRC                                        (0x1CU)
#define CSL_EPWM_AQCTLB                                         (0x18U)
#define CSL_EPWM_TBCTL                                          (0x0U)
#define CSL_EPWM_TZFRC                                          (0x30U)
#define CSL_EPWM_TZCTL                                          (0x28U)
#define CSL_EPWM_TBSTS                                          (0x2U)
#define CSL_EPWM_ETFRC                                          (0x3AU)
#define CSL_EPWM_TBPHS                                          (0x6U)
#define CSL_EPWM_TZSEL                                          (0x24U)
#define CSL_EPWM_ETFLG                                          (0x36U)
#define CSL_EPWM_DBCTL                                          (0x1EU)
#define CSL_EPWM_TZFLG                                          (0x2CU)
#define CSL_EPWM_TBPRD                                          (0xAU)
#define CSL_EPWM_CMPB                                           (0x14U)
#define CSL_EPWM_TZCLR                                          (0x2EU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* AQCTLA */

#define CSL_EPWM_AQCTLA_ZRO_MASK                                (0x00000003U)
#define CSL_EPWM_AQCTLA_ZRO_SHIFT                               (0U)
#define CSL_EPWM_AQCTLA_ZRO_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_ZRO_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_ZRO_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_ZRO_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_ZRO_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_PRD_MASK                                (0x0000000CU)
#define CSL_EPWM_AQCTLA_PRD_SHIFT                               (2U)
#define CSL_EPWM_AQCTLA_PRD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_PRD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_PRD_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_PRD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_PRD_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_CAU_MASK                                (0x00000030U)
#define CSL_EPWM_AQCTLA_CAU_SHIFT                               (4U)
#define CSL_EPWM_AQCTLA_CAU_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_CAU_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_CAU_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_CAU_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_CAU_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_CAD_MASK                                (0x000000C0U)
#define CSL_EPWM_AQCTLA_CAD_SHIFT                               (6U)
#define CSL_EPWM_AQCTLA_CAD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_CAD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_CAD_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_CAD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_CAD_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_CBU_MASK                                (0x00000300U)
#define CSL_EPWM_AQCTLA_CBU_SHIFT                               (8U)
#define CSL_EPWM_AQCTLA_CBU_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_CBU_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_CBU_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_CBU_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_CBU_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_CBD_MASK                                (0x00000C00U)
#define CSL_EPWM_AQCTLA_CBD_SHIFT                               (10U)
#define CSL_EPWM_AQCTLA_CBD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLA_CBD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLA_CBD_EN_0X2                              (0x00000002U)
#define CSL_EPWM_AQCTLA_CBD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLA_CBD_EN_0X3                              (0x00000003U)

#define CSL_EPWM_AQCTLA_RESETVAL                                (0x00000000U)

/* CMPCTL */

#define CSL_EPWM_CMPCTL_LOADAMODE_MASK                          (0x00000003U)
#define CSL_EPWM_CMPCTL_LOADAMODE_SHIFT                         (0U)
#define CSL_EPWM_CMPCTL_LOADAMODE_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_LOADAMODE_EN_0X1                        (0x00000001U)
#define CSL_EPWM_CMPCTL_LOADAMODE_EN_0X2                        (0x00000002U)
#define CSL_EPWM_CMPCTL_LOADAMODE_EN_0X0                        (0x00000000U)
#define CSL_EPWM_CMPCTL_LOADAMODE_EN_0X3                        (0x00000003U)

#define CSL_EPWM_CMPCTL_LOADBMODE_MASK                          (0x0000000CU)
#define CSL_EPWM_CMPCTL_LOADBMODE_SHIFT                         (2U)
#define CSL_EPWM_CMPCTL_LOADBMODE_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_LOADBMODE_EN_0X1                        (0x00000001U)
#define CSL_EPWM_CMPCTL_LOADBMODE_EN_0X2                        (0x00000002U)
#define CSL_EPWM_CMPCTL_LOADBMODE_EN_0X0                        (0x00000000U)
#define CSL_EPWM_CMPCTL_LOADBMODE_EN_0X3                        (0x00000003U)

#define CSL_EPWM_CMPCTL_SHDWAMODE_MASK                          (0x00000010U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_SHIFT                         (4U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_EN_0X0                        (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_EN_0X1                        (0x00000001U)

#define CSL_EPWM_CMPCTL_SHDWBMODE_MASK                          (0x00000040U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_SHIFT                         (6U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_EN_0X0                        (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_EN_0X1                        (0x00000001U)

#define CSL_EPWM_CMPCTL_SHDWAFULL_MASK                          (0x00000100U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_SHIFT                         (8U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_EN_0X1                        (0x00000001U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_EN_0X0                        (0x00000000U)

#define CSL_EPWM_CMPCTL_SHDWBFULL_MASK                          (0x00000200U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_SHIFT                         (9U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_RESETVAL                      (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_EN_0X0                        (0x00000000U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_EN_0X1                        (0x00000001U)

#define CSL_EPWM_CMPCTL_RESETVAL                                (0x00000000U)

/* CMPAHR */

#define CSL_EPWM_CMPAHR_CMPAHR_MASK                             (0x0000FF00U)
#define CSL_EPWM_CMPAHR_CMPAHR_SHIFT                            (8U)
#define CSL_EPWM_CMPAHR_CMPAHR_RESETVAL                         (0x00000001U)
#define CSL_EPWM_CMPAHR_CMPAHR_MAX                              (0x000000ffU)

#define CSL_EPWM_CMPAHR_RESETVAL                                (0x00000100U)

/* DBFED */

#define CSL_EPWM_DBFED_DEL_MASK                                 (0x000003FFU)
#define CSL_EPWM_DBFED_DEL_SHIFT                                (0U)
#define CSL_EPWM_DBFED_DEL_RESETVAL                             (0x00000000U)
#define CSL_EPWM_DBFED_DEL_MAX                                  (0x000003ffU)

#define CSL_EPWM_DBFED_RESETVAL                                 (0x00000000U)

/* TBPHSHR */

#define CSL_EPWM_TBPHSHR_TBPHSH_MASK                            (0x0000FF00U)
#define CSL_EPWM_TBPHSHR_TBPHSH_SHIFT                           (8U)
#define CSL_EPWM_TBPHSHR_TBPHSH_RESETVAL                        (0x00000000U)
#define CSL_EPWM_TBPHSHR_TBPHSH_MAX                             (0x000000ffU)

#define CSL_EPWM_TBPHSHR_RESETVAL                               (0x00000000U)

/* PCCTL */

#define CSL_EPWM_PCCTL_CHPEN_MASK                               (0x00000001U)
#define CSL_EPWM_PCCTL_CHPEN_SHIFT                              (0U)
#define CSL_EPWM_PCCTL_CHPEN_RESETVAL                           (0x00000000U)
#define CSL_EPWM_PCCTL_CHPEN_EN_0X0                             (0x00000000U)
#define CSL_EPWM_PCCTL_CHPEN_EN_0X1                             (0x00000001U)

#define CSL_EPWM_PCCTL_OSHTWTH_MASK                             (0x0000001EU)
#define CSL_EPWM_PCCTL_OSHTWTH_SHIFT                            (1U)
#define CSL_EPWM_PCCTL_OSHTWTH_RESETVAL                         (0x00000000U)
#define CSL_EPWM_PCCTL_OSHTWTH_EN_0X1                           (0x00000001U)
#define CSL_EPWM_PCCTL_OSHTWTH_EN_0XF                           (0x0000000fU)
#define CSL_EPWM_PCCTL_OSHTWTH_EN_0X0                           (0x00000000U)
#define CSL_EPWM_PCCTL_OSHTWTH_EN_0X3                           (0x00000003U)
#define CSL_EPWM_PCCTL_OSHTWTH_EN_0X2                           (0x00000002U)
#define CSL_EPWM_PCCTL_OSHTWTH_MAX                              (0x0000000fU)

#define CSL_EPWM_PCCTL_CHPFREQ_MASK                             (0x000000E0U)
#define CSL_EPWM_PCCTL_CHPFREQ_SHIFT                            (5U)
#define CSL_EPWM_PCCTL_CHPFREQ_RESETVAL                         (0x00000000U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X5                           (0x00000005U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X2                           (0x00000002U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X1                           (0x00000001U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X7                           (0x00000007U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X3                           (0x00000003U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X0                           (0x00000000U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X6                           (0x00000006U)
#define CSL_EPWM_PCCTL_CHPFREQ_EN_0X4                           (0x00000004U)

#define CSL_EPWM_PCCTL_CHPDUTY_MASK                             (0x00000700U)
#define CSL_EPWM_PCCTL_CHPDUTY_SHIFT                            (8U)
#define CSL_EPWM_PCCTL_CHPDUTY_RESETVAL                         (0x00000000U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X6                           (0x00000006U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X7                           (0x00000007U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X1                           (0x00000001U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X5                           (0x00000005U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X4                           (0x00000004U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X3                           (0x00000003U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X2                           (0x00000002U)
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X0                           (0x00000000U)

#define CSL_EPWM_PCCTL_RESETVAL                                 (0x00000000U)

/* DBRED */

#define CSL_EPWM_DBRED_DEL_MASK                                 (0x000003FFU)
#define CSL_EPWM_DBRED_DEL_SHIFT                                (0U)
#define CSL_EPWM_DBRED_DEL_RESETVAL                             (0x00000000U)
#define CSL_EPWM_DBRED_DEL_MAX                                  (0x000003ffU)

#define CSL_EPWM_DBRED_RESETVAL                                 (0x00000000U)

/* TBCNT */

#define CSL_EPWM_TBCNT_TBCNT_MASK                               (0x0000FFFFU)
#define CSL_EPWM_TBCNT_TBCNT_SHIFT                              (0U)
#define CSL_EPWM_TBCNT_TBCNT_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBCNT_TBCNT_MAX                                (0x0000ffffU)

#define CSL_EPWM_TBCNT_RESETVAL                                 (0x00000000U)

/* ETSEL */

#define CSL_EPWM_ETSEL_INTSEL_MASK                              (0x00000007U)
#define CSL_EPWM_ETSEL_INTSEL_SHIFT                             (0U)
#define CSL_EPWM_ETSEL_INTSEL_RESETVAL                          (0x00000000U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X6                            (0x00000006U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X0                            (0x00000000U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X5                            (0x00000005U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X1                            (0x00000001U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X2                            (0x00000002U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X4                            (0x00000004U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X3                            (0x00000003U)
#define CSL_EPWM_ETSEL_INTSEL_EN_0X7                            (0x00000007U)

#define CSL_EPWM_ETSEL_INTEN_MASK                               (0x00000008U)
#define CSL_EPWM_ETSEL_INTEN_SHIFT                              (3U)
#define CSL_EPWM_ETSEL_INTEN_RESETVAL                           (0x00000000U)
#define CSL_EPWM_ETSEL_INTEN_EN_0X0                             (0x00000000U)
#define CSL_EPWM_ETSEL_INTEN_EN_0X1                             (0x00000001U)

#define CSL_EPWM_ETSEL_RESETVAL                                 (0x00000000U)

/* HRCTL */

#define CSL_EPWM_HRCTL_DELMODE_MASK                             (0x00000003U)
#define CSL_EPWM_HRCTL_DELMODE_SHIFT                            (0U)
#define CSL_EPWM_HRCTL_DELMODE_RESETVAL                         (0x00000000U)
#define CSL_EPWM_HRCTL_DELMODE_EN_0X2                           (0x00000002U)
#define CSL_EPWM_HRCTL_DELMODE_EN_0X1                           (0x00000001U)
#define CSL_EPWM_HRCTL_DELMODE_EN_0X3                           (0x00000003U)
#define CSL_EPWM_HRCTL_DELMODE_EN_0X0                           (0x00000000U)

#define CSL_EPWM_HRCTL_DELBUSSEL_MASK                           (0x00000004U)
#define CSL_EPWM_HRCTL_DELBUSSEL_SHIFT                          (2U)
#define CSL_EPWM_HRCTL_DELBUSSEL_RESETVAL                       (0x00000000U)
#define CSL_EPWM_HRCTL_DELBUSSEL_EN_0X0                         (0x00000000U)
#define CSL_EPWM_HRCTL_DELBUSSEL_EN_0X1                         (0x00000001U)

#define CSL_EPWM_HRCTL_PULSESEL_MASK                            (0x00000008U)
#define CSL_EPWM_HRCTL_PULSESEL_SHIFT                           (3U)
#define CSL_EPWM_HRCTL_PULSESEL_RESETVAL                        (0x00000000U)
#define CSL_EPWM_HRCTL_PULSESEL_EN_0X1                          (0x00000001U)
#define CSL_EPWM_HRCTL_PULSESEL_EN_0X0                          (0x00000000U)

#define CSL_EPWM_HRCTL_RESETVAL                                 (0x00000000U)

/* TZEINT */

#define CSL_EPWM_TZEINT_CBC_MASK                                (0x00000002U)
#define CSL_EPWM_TZEINT_CBC_SHIFT                               (1U)
#define CSL_EPWM_TZEINT_CBC_RESETVAL                            (0x00000000U)
#define CSL_EPWM_TZEINT_CBC_EN_0X0                              (0x00000000U)
#define CSL_EPWM_TZEINT_CBC_EN_0X1                              (0x00000001U)

#define CSL_EPWM_TZEINT_OST_MASK                                (0x00000004U)
#define CSL_EPWM_TZEINT_OST_SHIFT                               (2U)
#define CSL_EPWM_TZEINT_OST_RESETVAL                            (0x00000000U)
#define CSL_EPWM_TZEINT_OST_EN_0X0                              (0x00000000U)
#define CSL_EPWM_TZEINT_OST_EN_0X1                              (0x00000001U)

#define CSL_EPWM_TZEINT_RESETVAL                                (0x00000000U)

/* AQSFRC */

#define CSL_EPWM_AQSFRC_ACTSFA_MASK                             (0x00000003U)
#define CSL_EPWM_AQSFRC_ACTSFA_SHIFT                            (0U)
#define CSL_EPWM_AQSFRC_ACTSFA_RESETVAL                         (0x00000000U)
#define CSL_EPWM_AQSFRC_ACTSFA_EN_0X2                           (0x00000002U)
#define CSL_EPWM_AQSFRC_ACTSFA_EN_0X1                           (0x00000001U)
#define CSL_EPWM_AQSFRC_ACTSFA_EN_0X0                           (0x00000000U)
#define CSL_EPWM_AQSFRC_ACTSFA_EN_0X3                           (0x00000003U)

#define CSL_EPWM_AQSFRC_OTSFA_MASK                              (0x00000004U)
#define CSL_EPWM_AQSFRC_OTSFA_SHIFT                             (2U)
#define CSL_EPWM_AQSFRC_OTSFA_RESETVAL                          (0x00000000U)
#define CSL_EPWM_AQSFRC_OTSFA_EN_0X0                            (0x00000000U)
#define CSL_EPWM_AQSFRC_OTSFA_EN_0X1                            (0x00000001U)

#define CSL_EPWM_AQSFRC_ACTSFB_MASK                             (0x00000018U)
#define CSL_EPWM_AQSFRC_ACTSFB_SHIFT                            (3U)
#define CSL_EPWM_AQSFRC_ACTSFB_RESETVAL                         (0x00000000U)
#define CSL_EPWM_AQSFRC_ACTSFB_EN_0X0                           (0x00000000U)
#define CSL_EPWM_AQSFRC_ACTSFB_EN_0X2                           (0x00000002U)
#define CSL_EPWM_AQSFRC_ACTSFB_EN_0X1                           (0x00000001U)
#define CSL_EPWM_AQSFRC_ACTSFB_EN_0X3                           (0x00000003U)

#define CSL_EPWM_AQSFRC_OTSFB_MASK                              (0x00000020U)
#define CSL_EPWM_AQSFRC_OTSFB_SHIFT                             (5U)
#define CSL_EPWM_AQSFRC_OTSFB_RESETVAL                          (0x00000000U)
#define CSL_EPWM_AQSFRC_OTSFB_EN_0X0                            (0x00000000U)
#define CSL_EPWM_AQSFRC_OTSFB_EN_0X1                            (0x00000001U)

#define CSL_EPWM_AQSFRC_RLDCSF_MASK                             (0x000000C0U)
#define CSL_EPWM_AQSFRC_RLDCSF_SHIFT                            (6U)
#define CSL_EPWM_AQSFRC_RLDCSF_RESETVAL                         (0x00000000U)
#define CSL_EPWM_AQSFRC_RLDCSF_EN_0X2                           (0x00000002U)
#define CSL_EPWM_AQSFRC_RLDCSF_EN_0X0                           (0x00000000U)
#define CSL_EPWM_AQSFRC_RLDCSF_EN_0X1                           (0x00000001U)
#define CSL_EPWM_AQSFRC_RLDCSF_EN_0X3                           (0x00000003U)

#define CSL_EPWM_AQSFRC_RESETVAL                                (0x00000000U)

/* ETPS */

#define CSL_EPWM_ETPS_INTPRD_MASK                               (0x00000003U)
#define CSL_EPWM_ETPS_INTPRD_SHIFT                              (0U)
#define CSL_EPWM_ETPS_INTPRD_RESETVAL                           (0x00000000U)
#define CSL_EPWM_ETPS_INTPRD_EN_0X0                             (0x00000000U)
#define CSL_EPWM_ETPS_INTPRD_EN_0X3                             (0x00000003U)
#define CSL_EPWM_ETPS_INTPRD_EN_0X2                             (0x00000002U)
#define CSL_EPWM_ETPS_INTPRD_EN_0X1                             (0x00000001U)

#define CSL_EPWM_ETPS_INTCNT_MASK                               (0x0000000CU)
#define CSL_EPWM_ETPS_INTCNT_SHIFT                              (2U)
#define CSL_EPWM_ETPS_INTCNT_RESETVAL                           (0x00000000U)
#define CSL_EPWM_ETPS_INTCNT_EN_0X3                             (0x00000003U)
#define CSL_EPWM_ETPS_INTCNT_EN_0X0                             (0x00000000U)
#define CSL_EPWM_ETPS_INTCNT_EN_0X1                             (0x00000001U)
#define CSL_EPWM_ETPS_INTCNT_EN_0X2                             (0x00000002U)

#define CSL_EPWM_ETPS_RESETVAL                                  (0x00000000U)

/* CMPA */

#define CSL_EPWM_CMPA_CMPA_MASK                                 (0x0000FFFFU)
#define CSL_EPWM_CMPA_CMPA_SHIFT                                (0U)
#define CSL_EPWM_CMPA_CMPA_RESETVAL                             (0x00000000U)
#define CSL_EPWM_CMPA_CMPA_MAX                                  (0x0000ffffU)

#define CSL_EPWM_CMPA_RESETVAL                                  (0x00000000U)

/* ETCLR */

#define CSL_EPWM_ETCLR_INT_MASK                                 (0x00000001U)
#define CSL_EPWM_ETCLR_INT_SHIFT                                (0U)
#define CSL_EPWM_ETCLR_INT_RESETVAL                             (0x00000000U)
#define CSL_EPWM_ETCLR_INT_EN_0X0                               (0x00000000U)
#define CSL_EPWM_ETCLR_INT_EN_0X1                               (0x00000001U)

#define CSL_EPWM_ETCLR_RESETVAL                                 (0x00000000U)

/* AQCSFRC */

#define CSL_EPWM_AQCSFRC_CSFA_MASK                              (0x00000003U)
#define CSL_EPWM_AQCSFRC_CSFA_SHIFT                             (0U)
#define CSL_EPWM_AQCSFRC_CSFA_RESETVAL                          (0x00000000U)
#define CSL_EPWM_AQCSFRC_CSFA_EN_0X2                            (0x00000002U)
#define CSL_EPWM_AQCSFRC_CSFA_EN_0X0                            (0x00000000U)
#define CSL_EPWM_AQCSFRC_CSFA_EN_0X1                            (0x00000001U)
#define CSL_EPWM_AQCSFRC_CSFA_EN_0X3                            (0x00000003U)

#define CSL_EPWM_AQCSFRC_CSFB_MASK                              (0x0000000CU)
#define CSL_EPWM_AQCSFRC_CSFB_SHIFT                             (2U)
#define CSL_EPWM_AQCSFRC_CSFB_RESETVAL                          (0x00000000U)
#define CSL_EPWM_AQCSFRC_CSFB_EN_0X1                            (0x00000001U)
#define CSL_EPWM_AQCSFRC_CSFB_EN_0X0                            (0x00000000U)
#define CSL_EPWM_AQCSFRC_CSFB_EN_0X3                            (0x00000003U)
#define CSL_EPWM_AQCSFRC_CSFB_EN_0X2                            (0x00000002U)

#define CSL_EPWM_AQCSFRC_RESETVAL                               (0x00000000U)

/* AQCTLB */

#define CSL_EPWM_AQCTLB_ZRO_MASK                                (0x00000003U)
#define CSL_EPWM_AQCTLB_ZRO_SHIFT                               (0U)
#define CSL_EPWM_AQCTLB_ZRO_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_ZRO_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_ZRO_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_ZRO_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_ZRO_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_PRD_MASK                                (0x0000000CU)
#define CSL_EPWM_AQCTLB_PRD_SHIFT                               (2U)
#define CSL_EPWM_AQCTLB_PRD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_PRD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_PRD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_PRD_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_PRD_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_CAU_MASK                                (0x00000030U)
#define CSL_EPWM_AQCTLB_CAU_SHIFT                               (4U)
#define CSL_EPWM_AQCTLB_CAU_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_CAU_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_CAU_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_CAU_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_CAU_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_CAD_MASK                                (0x000000C0U)
#define CSL_EPWM_AQCTLB_CAD_SHIFT                               (6U)
#define CSL_EPWM_AQCTLB_CAD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_CAD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_CAD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_CAD_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_CAD_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_CBU_MASK                                (0x00000300U)
#define CSL_EPWM_AQCTLB_CBU_SHIFT                               (8U)
#define CSL_EPWM_AQCTLB_CBU_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_CBU_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_CBU_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_CBU_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_CBU_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_CBD_MASK                                (0x00000C00U)
#define CSL_EPWM_AQCTLB_CBD_SHIFT                               (10U)
#define CSL_EPWM_AQCTLB_CBD_RESETVAL                            (0x00000000U)
#define CSL_EPWM_AQCTLB_CBD_EN_0X1                              (0x00000001U)
#define CSL_EPWM_AQCTLB_CBD_EN_0X0                              (0x00000000U)
#define CSL_EPWM_AQCTLB_CBD_EN_0X3                              (0x00000003U)
#define CSL_EPWM_AQCTLB_CBD_EN_0X2                              (0x00000002U)

#define CSL_EPWM_AQCTLB_RESETVAL                                (0x00000000U)

/* TBCTL */

#define CSL_EPWM_TBCTL_CTRMODE_MASK                             (0x00000003U)
#define CSL_EPWM_TBCTL_CTRMODE_SHIFT                            (0U)
#define CSL_EPWM_TBCTL_CTRMODE_RESETVAL                         (0x00000000U)
#define CSL_EPWM_TBCTL_CTRMODE_EN_0X3                           (0x00000003U)
#define CSL_EPWM_TBCTL_CTRMODE_EN_0X1                           (0x00000001U)
#define CSL_EPWM_TBCTL_CTRMODE_EN_0X0                           (0x00000000U)
#define CSL_EPWM_TBCTL_CTRMODE_EN_0X2                           (0x00000002U)

#define CSL_EPWM_TBCTL_PHSEN_MASK                               (0x00000004U)
#define CSL_EPWM_TBCTL_PHSEN_SHIFT                              (2U)
#define CSL_EPWM_TBCTL_PHSEN_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBCTL_PHSEN_EN_0X0                             (0x00000000U)
#define CSL_EPWM_TBCTL_PHSEN_EN_0X1                             (0x00000001U)

#define CSL_EPWM_TBCTL_PRDLD_MASK                               (0x00000008U)
#define CSL_EPWM_TBCTL_PRDLD_SHIFT                              (3U)
#define CSL_EPWM_TBCTL_PRDLD_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBCTL_PRDLD_EN_0X1                             (0x00000001U)
#define CSL_EPWM_TBCTL_PRDLD_EN_0X0                             (0x00000000U)

#define CSL_EPWM_TBCTL_SYNCOSEL_MASK                            (0x00000030U)
#define CSL_EPWM_TBCTL_SYNCOSEL_SHIFT                           (4U)
#define CSL_EPWM_TBCTL_SYNCOSEL_RESETVAL                        (0x00000000U)
#define CSL_EPWM_TBCTL_SYNCOSEL_EN_0X1                          (0x00000001U)
#define CSL_EPWM_TBCTL_SYNCOSEL_EN_0X2                          (0x00000002U)
#define CSL_EPWM_TBCTL_SYNCOSEL_EN_0X0                          (0x00000000U)
#define CSL_EPWM_TBCTL_SYNCOSEL_EN_0X3                          (0x00000003U)

#define CSL_EPWM_TBCTL_SWFSYNC_MASK                             (0x00000040U)
#define CSL_EPWM_TBCTL_SWFSYNC_SHIFT                            (6U)
#define CSL_EPWM_TBCTL_SWFSYNC_RESETVAL                         (0x00000000U)
#define CSL_EPWM_TBCTL_SWFSYNC_EN_0X1                           (0x00000001U)
#define CSL_EPWM_TBCTL_SWFSYNC_EN_0X0                           (0x00000000U)

#define CSL_EPWM_TBCTL_HSPCLKDIV_MASK                           (0x00000380U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_SHIFT                          (7U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_RESETVAL                       (0x00000000U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X4                         (0x00000004U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X5                         (0x00000005U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X1                         (0x00000001U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X0                         (0x00000000U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X2                         (0x00000002U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X3                         (0x00000003U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X6                         (0x00000006U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_EN_0X7                         (0x00000007U)

#define CSL_EPWM_TBCTL_CLKDIV_MASK                              (0x00001C00U)
#define CSL_EPWM_TBCTL_CLKDIV_SHIFT                             (10U)
#define CSL_EPWM_TBCTL_CLKDIV_RESETVAL                          (0x00000000U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X1                            (0x00000001U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X3                            (0x00000003U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X5                            (0x00000005U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X6                            (0x00000006U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X4                            (0x00000004U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X2                            (0x00000002U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X0                            (0x00000000U)
#define CSL_EPWM_TBCTL_CLKDIV_EN_0X7                            (0x00000007U)

#define CSL_EPWM_TBCTL_PHSDIR_MASK                              (0x00002000U)
#define CSL_EPWM_TBCTL_PHSDIR_SHIFT                             (13U)
#define CSL_EPWM_TBCTL_PHSDIR_RESETVAL                          (0x00000000U)
#define CSL_EPWM_TBCTL_PHSDIR_EN_0X0                            (0x00000000U)
#define CSL_EPWM_TBCTL_PHSDIR_EN_0X1                            (0x00000001U)

#define CSL_EPWM_TBCTL_FREE_SOFT_MASK                           (0x0000C000U)
#define CSL_EPWM_TBCTL_FREE_SOFT_SHIFT                          (14U)
#define CSL_EPWM_TBCTL_FREE_SOFT_RESETVAL                       (0x00000000U)
#define CSL_EPWM_TBCTL_FREE_SOFT_EN_0X3                         (0x00000003U)
#define CSL_EPWM_TBCTL_FREE_SOFT_EN_0X0                         (0x00000000U)
#define CSL_EPWM_TBCTL_FREE_SOFT_EN_0X2                         (0x00000002U)
#define CSL_EPWM_TBCTL_FREE_SOFT_EN_0X1                         (0x00000001U)

#define CSL_EPWM_TBCTL_RESETVAL                                 (0x00000000U)

/* TZFRC */

#define CSL_EPWM_TZFRC_CBC_MASK                                 (0x00000002U)
#define CSL_EPWM_TZFRC_CBC_SHIFT                                (1U)
#define CSL_EPWM_TZFRC_CBC_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZFRC_CBC_EN_0X1                               (0x00000001U)
#define CSL_EPWM_TZFRC_CBC_EN_0X0                               (0x00000000U)

#define CSL_EPWM_TZFRC_OST_MASK                                 (0x00000004U)
#define CSL_EPWM_TZFRC_OST_SHIFT                                (2U)
#define CSL_EPWM_TZFRC_OST_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZFRC_OST_EN_0X1                               (0x00000001U)
#define CSL_EPWM_TZFRC_OST_EN_0X0                               (0x00000000U)

#define CSL_EPWM_TZFRC_RESETVAL                                 (0x00000000U)

/* TZCTL */

#define CSL_EPWM_TZCTL_TZA_MASK                                 (0x00000003U)
#define CSL_EPWM_TZCTL_TZA_SHIFT                                (0U)
#define CSL_EPWM_TZCTL_TZA_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZCTL_TZA_EN_0X2                               (0x00000002U)
#define CSL_EPWM_TZCTL_TZA_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZCTL_TZA_EN_0X1                               (0x00000001U)
#define CSL_EPWM_TZCTL_TZA_EN_0X3                               (0x00000003U)

#define CSL_EPWM_TZCTL_TZB_MASK                                 (0x0000000CU)
#define CSL_EPWM_TZCTL_TZB_SHIFT                                (2U)
#define CSL_EPWM_TZCTL_TZB_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZCTL_TZB_EN_0X2                               (0x00000002U)
#define CSL_EPWM_TZCTL_TZB_EN_0X3                               (0x00000003U)
#define CSL_EPWM_TZCTL_TZB_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZCTL_TZB_EN_0X1                               (0x00000001U)

#define CSL_EPWM_TZCTL_RESETVAL                                 (0x00000000U)

/* TBSTS */

#define CSL_EPWM_TBSTS_CTRDIR_MASK                              (0x00000001U)
#define CSL_EPWM_TBSTS_CTRDIR_SHIFT                             (0U)
#define CSL_EPWM_TBSTS_CTRDIR_RESETVAL                          (0x00000000U)
#define CSL_EPWM_TBSTS_CTRDIR_EN_0X0                            (0x00000000U)
#define CSL_EPWM_TBSTS_CTRDIR_EN_0X1                            (0x00000001U)

#define CSL_EPWM_TBSTS_SYNCI_MASK                               (0x00000002U)
#define CSL_EPWM_TBSTS_SYNCI_SHIFT                              (1U)
#define CSL_EPWM_TBSTS_SYNCI_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBSTS_SYNCI_EN_0X1                             (0x00000001U)
#define CSL_EPWM_TBSTS_SYNCI_EN_0X0                             (0x00000000U)

#define CSL_EPWM_TBSTS_CTRMAX_MASK                              (0x00000004U)
#define CSL_EPWM_TBSTS_CTRMAX_SHIFT                             (2U)
#define CSL_EPWM_TBSTS_CTRMAX_RESETVAL                          (0x00000000U)
#define CSL_EPWM_TBSTS_CTRMAX_EN_0X1                            (0x00000001U)
#define CSL_EPWM_TBSTS_CTRMAX_EN_0X0                            (0x00000000U)

#define CSL_EPWM_TBSTS_RESETVAL                                 (0x00000000U)

/* ETFRC */

#define CSL_EPWM_ETFRC_INT_MASK                                 (0x00000001U)
#define CSL_EPWM_ETFRC_INT_SHIFT                                (0U)
#define CSL_EPWM_ETFRC_INT_RESETVAL                             (0x00000000U)
#define CSL_EPWM_ETFRC_INT_EN_0X0                               (0x00000000U)
#define CSL_EPWM_ETFRC_INT_EN_0X1                               (0x00000001U)

#define CSL_EPWM_ETFRC_RESETVAL                                 (0x00000000U)

/* TBPHS */

#define CSL_EPWM_TBPHS_TBPHS_MASK                               (0x0000FFFFU)
#define CSL_EPWM_TBPHS_TBPHS_SHIFT                              (0U)
#define CSL_EPWM_TBPHS_TBPHS_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBPHS_TBPHS_MAX                                (0x0000ffffU)

#define CSL_EPWM_TBPHS_RESETVAL                                 (0x00000000U)

/* TZSEL */

#define CSL_EPWM_TZSEL_CBCN_MASK                                (0x000000FFU)
#define CSL_EPWM_TZSEL_CBCN_SHIFT                               (0U)
#define CSL_EPWM_TZSEL_CBCN_RESETVAL                            (0x00000000U)
#define CSL_EPWM_TZSEL_CBCN_EN_0X1                              (0x00000001U)
#define CSL_EPWM_TZSEL_CBCN_EN_0X0                              (0x00000000U)
#define CSL_EPWM_TZSEL_CBCN_MAX                                 (0x000000ffU)

#define CSL_EPWM_TZSEL_OSHTN_MASK                               (0x0000FF00U)
#define CSL_EPWM_TZSEL_OSHTN_SHIFT                              (8U)
#define CSL_EPWM_TZSEL_OSHTN_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TZSEL_OSHTN_EN_0X1                             (0x00000001U)
#define CSL_EPWM_TZSEL_OSHTN_EN_0X0                             (0x00000000U)
#define CSL_EPWM_TZSEL_OSHTN_MAX                                (0x000000ffU)

#define CSL_EPWM_TZSEL_RESETVAL                                 (0x00000000U)

/* ETFLG */

#define CSL_EPWM_ETFLG_INT_MASK                                 (0x00000001U)
#define CSL_EPWM_ETFLG_INT_SHIFT                                (0U)
#define CSL_EPWM_ETFLG_INT_RESETVAL                             (0x00000000U)
#define CSL_EPWM_ETFLG_INT_EN_0X1                               (0x00000001U)
#define CSL_EPWM_ETFLG_INT_EN_0X0                               (0x00000000U)

#define CSL_EPWM_ETFLG_RESETVAL                                 (0x00000000U)

/* DBCTL */

#define CSL_EPWM_DBCTL_OUT_MODE_MASK                            (0x00000003U)
#define CSL_EPWM_DBCTL_OUT_MODE_SHIFT                           (0U)
#define CSL_EPWM_DBCTL_OUT_MODE_RESETVAL                        (0x00000000U)
#define CSL_EPWM_DBCTL_OUT_MODE_EN_0X3                          (0x00000003U)
#define CSL_EPWM_DBCTL_OUT_MODE_EN_0X0                          (0x00000000U)
#define CSL_EPWM_DBCTL_OUT_MODE_EN_0X2                          (0x00000002U)
#define CSL_EPWM_DBCTL_OUT_MODE_EN_0X1                          (0x00000001U)

#define CSL_EPWM_DBCTL_POLSEL_MASK                              (0x0000000CU)
#define CSL_EPWM_DBCTL_POLSEL_SHIFT                             (2U)
#define CSL_EPWM_DBCTL_POLSEL_RESETVAL                          (0x00000000U)
#define CSL_EPWM_DBCTL_POLSEL_EN_0X2                            (0x00000002U)
#define CSL_EPWM_DBCTL_POLSEL_EN_0X3                            (0x00000003U)
#define CSL_EPWM_DBCTL_POLSEL_EN_0X0                            (0x00000000U)
#define CSL_EPWM_DBCTL_POLSEL_EN_0X1                            (0x00000001U)

#define CSL_EPWM_DBCTL_IN_MODE_MASK                             (0x00000030U)
#define CSL_EPWM_DBCTL_IN_MODE_SHIFT                            (4U)
#define CSL_EPWM_DBCTL_IN_MODE_RESETVAL                         (0x00000000U)
#define CSL_EPWM_DBCTL_IN_MODE_EN_0X0                           (0x00000000U)
#define CSL_EPWM_DBCTL_IN_MODE_EN_0X2                           (0x00000002U)
#define CSL_EPWM_DBCTL_IN_MODE_EN_0X1                           (0x00000001U)
#define CSL_EPWM_DBCTL_IN_MODE_EN_0X3                           (0x00000003U)

#define CSL_EPWM_DBCTL_RESETVAL                                 (0x00000000U)

/* TZFLG */

#define CSL_EPWM_TZFLG_INT_MASK                                 (0x00000001U)
#define CSL_EPWM_TZFLG_INT_SHIFT                                (0U)
#define CSL_EPWM_TZFLG_INT_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZFLG_INT_EN_0X1                               (0x00000001U)
#define CSL_EPWM_TZFLG_INT_EN_0X0                               (0x00000000U)

#define CSL_EPWM_TZFLG_CBC_MASK                                 (0x00000002U)
#define CSL_EPWM_TZFLG_CBC_SHIFT                                (1U)
#define CSL_EPWM_TZFLG_CBC_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZFLG_CBC_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZFLG_CBC_EN_0X1                               (0x00000001U)

#define CSL_EPWM_TZFLG_OST_MASK                                 (0x00000004U)
#define CSL_EPWM_TZFLG_OST_SHIFT                                (2U)
#define CSL_EPWM_TZFLG_OST_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZFLG_OST_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZFLG_OST_EN_0X1                               (0x00000001U)

#define CSL_EPWM_TZFLG_RESETVAL                                 (0x00000000U)

/* TBPRD */

#define CSL_EPWM_TBPRD_TBPRD_MASK                               (0x0000FFFFU)
#define CSL_EPWM_TBPRD_TBPRD_SHIFT                              (0U)
#define CSL_EPWM_TBPRD_TBPRD_RESETVAL                           (0x00000000U)
#define CSL_EPWM_TBPRD_TBPRD_MAX                                (0x0000ffffU)

#define CSL_EPWM_TBPRD_RESETVAL                                 (0x00000000U)

/* CMPB */

#define CSL_EPWM_CMPB_CMPB_MASK                                 (0x0000FFFFU)
#define CSL_EPWM_CMPB_CMPB_SHIFT                                (0U)
#define CSL_EPWM_CMPB_CMPB_RESETVAL                             (0x00000000U)
#define CSL_EPWM_CMPB_CMPB_MAX                                  (0x0000ffffU)

#define CSL_EPWM_CMPB_RESETVAL                                  (0x00000000U)

/* TZCLR */

#define CSL_EPWM_TZCLR_INT_MASK                                 (0x00000001U)
#define CSL_EPWM_TZCLR_INT_SHIFT                                (0U)
#define CSL_EPWM_TZCLR_INT_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZCLR_INT_EN_0X1                               (0x00000001U)
#define CSL_EPWM_TZCLR_INT_EN_0X0                               (0x00000000U)

#define CSL_EPWM_TZCLR_CBC_MASK                                 (0x00000002U)
#define CSL_EPWM_TZCLR_CBC_SHIFT                                (1U)
#define CSL_EPWM_TZCLR_CBC_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZCLR_CBC_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZCLR_CBC_EN_0X1                               (0x00000001U)

#define CSL_EPWM_TZCLR_OST_MASK                                 (0x00000004U)
#define CSL_EPWM_TZCLR_OST_SHIFT                                (2U)
#define CSL_EPWM_TZCLR_OST_RESETVAL                             (0x00000000U)
#define CSL_EPWM_TZCLR_OST_EN_0X0                               (0x00000000U)
#define CSL_EPWM_TZCLR_OST_EN_0X1                               (0x00000001U)

#define CSL_EPWM_TZCLR_RESETVAL                                 (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
